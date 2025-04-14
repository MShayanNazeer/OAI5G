static void handle_itti_msg(void *data) 
{
  itti_msg_t *msg = (itti_msg_t *)data;
  int result;
  NR_UE_MAC_INST_t *mac = get_mac_inst(0);
  nr_uplink_indication_t UL_INFO = {0};
  nr_downlink_indication_t dl_info;
  
  module_id_t module_id = 0; /* TODO: this should come from messaging */
  
  switch(ITTI_MSG_ID(msg))
  {
    case INITIALIZE_MESSAGE:
      LOG_I(MAC, "MAC NR: Received %s\n", ITTI_MSG_NAME(msg));
      mac->if_module->scheduled_response = nr_ue_scheduled_response;
      mac->if_module->phy_config_request = nr_ue_phy_config_request;
      mac->if_module->synch_request = nr_ue_synch_request;
      result = nr_ue_if_module_init(module_id);
      AssertFatal (result == 0, "%s:%d:Error initializing UE interface module", __FILE__, __LINE__);
      // Setup PHY after interface
      result = nr_ue_phy_init(mac, &(mac->phy_config));
      AssertFatal (result == 0, "%s:%d:Error initializing UE PHY", __FILE__, __LINE__);
      break;
      
    case TICK_SYNCH:
      if (msg->msg_id == TICK_SYNCH){
        int is_synched = msg->ittiMsg.tick_synch_request.is_synched;
        uint16_t frame = msg->ittiMsg.tick_synch_request.frame;
        uint16_t slot = msg->ittiMsg.tick_synch_request.slot;
        // TODO: for UL, pass harq information to MAC here
        nr_ue_tick(frame, slot, is_synched);
      }
      break;
      
    case NR_RRC_MAC_CONFIG_RESET:
      nr_rrc_mac_config_req_reset(0, 0);
      break;
      
    case NR_RRC_MAC_CONFIG_CG:
      LOG_I(MAC, "MAC NR: Received %s\n", ITTI_MSG_NAME(msg));
      nr_rrc_mac_config_req_cg(0, 0, NR_MAC_RRC_CONFIG_CG(msg).cellGroupConfig, NR_MAC_RRC_CONFIG_CG(msg).UE_NR_Capability);
      break;
      
    case NR_RRC_MAC_CONFIG_MIB:
      LOG_I(MAC, "MAC NR: Received %s\n", ITTI_MSG_NAME(msg));
      if (!get_softmodem_params()->emulate_l1)
        nr_rrc_mac_config_req_mib(0, 0, NR_MAC_RRC_CONFIG_MIB(msg).bcch->message.choice.mib, NR_MAC_RRC_CONFIG_MIB(msg).get_sib);
      ASN_STRUCT_FREE(asn_DEF_NR_BCCH_BCH_Message, NR_MAC_RRC_CONFIG_MIB(msg).bcch);
      break;

    case NR_RRC_MAC_CONFIG_SIB1:
      LOG_I(MAC, "MAC NR: Received %s\n", ITTI_MSG_NAME(msg));
      if (!get_softmodem_params()->emulate_l1)
        nr_rrc_mac_config_req_sib1(0, 0, NR_MAC_RRC_CONFIG_SIB1(msg).sib1, NR_MAC_RRC_CONFIG_SIB1(msg).can_start_ra);
      SEQUENCE_free(&asn_DEF_NR_SIB1, NR_MAC_RRC_CONFIG_SIB1(msg).sib1, ASFM_FREE_EVERYTHING);
      break;

    case NR_RRC_MAC_CONFIG_OTHER_SIB:
      LOG_I(MAC, "MAC NR: Received %s\n", ITTI_MSG_NAME(msg));
      if (!get_softmodem_params()->emulate_l1) {
        nr_rrc_mac_config_other_sib(0, NR_MAC_RRC_CONFIG_OTHER_SIB(msg).sib19, NR_MAC_RRC_CONFIG_OTHER_SIB(msg).can_start_ra);
        if (NR_MAC_RRC_CONFIG_OTHER_SIB(msg).sib19)
          ASN_STRUCT_FREE(asn_DEF_NR_SIB19_r17, NR_MAC_RRC_CONFIG_OTHER_SIB(msg).sib19);
      }
      break;

    case NR_RRC_MAC_RECONFIGURATION_COMPLETE_REQ:
      LOG_I(MAC, "MAC NR: Received %s\n", ITTI_MSG_NAME(msg));
      if (NR_RRC_MAC_RECONFIGURATION_COMPLETE_REQ(msg).skip_ra_procedure) {
        LOG_I(MAC, "Skipping RACH procedure after reconfiguration as requested\n");
        // Set state to CONNECTED directly
        mac->state = UE_CONNECTED;
        
        // Notify RRC about successful RA procedure
        MessageDef *message_p = itti_alloc_new_message(TASK_MAC_UE, 0, NR_RRC_MAC_RA_IND);
        NR_RRC_MAC_RA_IND(message_p).ra_successful = true;
        itti_send_msg_to_task(TASK_RRC_NRUE, module_id, message_p);
      }
      break;
      
    default:
      LOG_E(MAC, "Unhandled message %s\n", ITTI_MSG_NAME(msg));
      break;
  }
} 

void *mac_rrc_task(void *args_p)
{
  MessageDef *msg_p = NULL;
  itti_mark_task_ready(TASK_MAC_UE);
  
  while(1) {
    itti_receive_msg(TASK_MAC_UE, &msg_p);
    if (msg_p != NULL) {
      handle_itti_msg(msg_p);
      itti_free(ITTI_MSG_ORIGIN_ID(msg_p), msg_p);
    }
  }
}

void nr_ue_init_mac(module_id_t module_id)
{
  NR_UE_MAC_INST_t *mac = get_mac_inst(module_id);
  for (int i = 0; i < MAX_DRBs; i++)
    for (int j = 0; j < MAX_HARQ_PROCESSES; j++) {
      mac->nr_ue_emul_l1.harq[j].active_ul_harq_sfn = -1;
      mac->nr_ue_emul_l1.harq[j].active_ul_harq_slot = -1;
    }

  // Setup process function pointers for UE MAC procedures
  mac->if_module = nr_ue_if_module_init();

  // Starting UE MAC reader thread
  threadCreate(&mac->mac_ue_thread, mac_rrc_task, NULL, "MAC_UE_TASK", -1, OAI_PRIORITY_RT_LOW);
  
  nr_init_mac_rrc_ind_queue();
} 