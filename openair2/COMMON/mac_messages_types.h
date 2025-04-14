/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.1  (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.openairinterface.org/?page_id=698
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

/*
 * mac_messages_types.h
 *
 *  Created on: Oct 24, 2013
 *      Author: winckel and Navid Nikaein
 */

#ifndef MAC_MESSAGES_TYPES_H_
#define MAC_MESSAGES_TYPES_H_

#include <LTE_DRX-Config.h>
#include "OCTET_STRING.h"

//-------------------------------------------------------------------------------------------//
// Defines to access message fields.
#define RRC_MAC_IN_SYNC_IND(mSGpTR)             (mSGpTR)->ittiMsg.rrc_mac_in_sync_ind
#define RRC_MAC_OUT_OF_SYNC_IND(mSGpTR)         (mSGpTR)->ittiMsg.rrc_mac_out_of_sync_ind
#define NR_RRC_MAC_SYNC_IND(mSGpTR)             (mSGpTR)->ittiMsg.nr_rrc_mac_sync_ind

#define RRC_MAC_BCCH_DATA_REQ(mSGpTR)           (mSGpTR)->ittiMsg.rrc_mac_bcch_data_req
#define RRC_MAC_BCCH_DATA_IND(mSGpTR)           (mSGpTR)->ittiMsg.rrc_mac_bcch_data_ind
#define NR_RRC_MAC_BCCH_DATA_IND(mSGpTR)        (mSGpTR)->ittiMsg.nr_rrc_mac_bcch_data_ind
#define NR_RRC_MAC_SBCCH_DATA_IND(mSGpTR)       (mSGpTR)->ittiMsg.nr_rrc_mac_sbcch_data_ind

#define RRC_MAC_BCCH_MBMS_DATA_REQ(mSGpTR)      (mSGpTR)->ittiMsg.rrc_mac_bcch_mbms_data_req
#define RRC_MAC_BCCH_MBMS_DATA_IND(mSGpTR)      (mSGpTR)->ittiMsg.rrc_mac_bcch_mbms_data_ind

#define RRC_MAC_CCCH_DATA_REQ(mSGpTR)           (mSGpTR)->ittiMsg.rrc_mac_ccch_data_req
#define RRC_MAC_CCCH_DATA_CNF(mSGpTR)           (mSGpTR)->ittiMsg.rrc_mac_ccch_data_cnf
#define RRC_MAC_CCCH_DATA_IND(mSGpTR)           (mSGpTR)->ittiMsg.rrc_mac_ccch_data_ind
#define NR_RRC_MAC_CCCH_DATA_IND(mSGpTR)        (mSGpTR)->ittiMsg.nr_rrc_mac_ccch_data_ind

#define RRC_MAC_MCCH_DATA_REQ(mSGpTR)           (mSGpTR)->ittiMsg.rrc_mac_mcch_data_req
#define RRC_MAC_MCCH_DATA_IND(mSGpTR)           (mSGpTR)->ittiMsg.rrc_mac_mcch_data_ind
#define RRC_MAC_PCCH_DATA_REQ(mSGpTR)           (mSGpTR)->ittiMsg.rrc_mac_pcch_data_req

#define NR_RRC_MAC_RA_IND(mSGpTR)               (mSGpTR)->ittiMsg.nr_rrc_mac_ra_ind
#define NR_RRC_MAC_MSG3_IND(mSGpTR)             (mSGpTR)->ittiMsg.nr_rrc_mac_msg3_ind
#define NR_RRC_MAC_INAC_IND(mSGpTR)             (mSGpTR)->ittiMsg.nr_rrc_mac_inac_ind
#define NR_RRC_MAC_RECONFIGURATION_COMPLETE_REQ(mSGpTR) (mSGpTR)->ittiMsg.nr_rrc_mac_reconfiguration_complete_req

#define RRC_MAC_DRX_CONFIG_REQ(mSGpTR)          (mSGpTR)->ittiMsg.rrc_mac_drx_config_req

// Some constants from "LAYER2/MAC/defs.h"
#define BCCH_SDU_SIZE                           (512)
#define BCCH_SDU_MBMS_SIZE                      (512)
#define CCCH_SDU_SIZE                           (1024)
#define MCCH_SDU_SIZE                           (512)
#define PCCH_SDU_SIZE                           (512)

//-------------------------------------------------------------------------------------------//
// Messages between RRC and MAC layers

typedef struct NRRrcMacRaInd_s {
  bool RA_succeeded;
} NRRrcMacRaInd;

typedef struct NRRrcMacMsg3Ind_s {
  uint16_t rnti;
  int gnb_id;
  bool prepare_payload;
} NRRrcMacMsg3Ind;

typedef struct NRRrcMacInacInd_s {
  bool inactivity_timer_expired; // not to leave the struct empty
} NRRrcMacInacInd;

typedef struct RrcMacInSyncInd_s {
  uint32_t  frame;
  uint8_t   sub_frame;
  uint16_t  enb_index;
} RrcMacInSyncInd;

typedef RrcMacInSyncInd RrcMacOutOfSyncInd;

typedef struct NRRrcMacSyncInd_s {
  uint32_t frame;
  bool in_sync;
} NRRrcMacSyncInd;

typedef struct RrcMacBcchDataReq_s {
  uint32_t  frame;
  uint32_t  sdu_size;
  uint8_t   sdu[BCCH_SDU_SIZE];
  uint8_t   enb_index;
} RrcMacBcchDataReq;

typedef struct RrcMacBcchDataInd_s {
  uint32_t  frame;
  uint8_t   sub_frame;
  uint32_t  sdu_size;
  uint8_t   sdu[BCCH_SDU_SIZE];
  uint8_t   enb_index;
  uint8_t   rsrq;
  uint8_t   rsrp;
} RrcMacBcchDataInd;

typedef struct NRRrcMacBcchDataInd_s {
  uint32_t  frame;
  uint8_t   slot;
  uint32_t  sdu_size;
  uint8_t   sdu[BCCH_SDU_SIZE];
  uint8_t   gnb_index;
  bool      is_bch;
  uint8_t   rsrq;
  uint8_t   rsrp;
  uint32_t  phycellid;
  long      ssb_arfcn;
} NRRrcMacBcchDataInd;

typedef struct NRRrcMacSBcchDataInd_s {
  uint32_t  frame;
  uint8_t   slot;
  uint32_t  sdu_size;
  uint8_t   sdu[BCCH_SDU_SIZE];
  uint8_t   gnb_index;
  uint16_t  rx_slss_id;
  uint8_t   rsrq;
  uint8_t   rsrp;
} NRRrcMacSBcchDataInd;

typedef struct RrcMacBcchMbmsDataReq_s {
  uint32_t  frame;
  uint32_t  sdu_size;
  uint8_t   sdu[BCCH_SDU_MBMS_SIZE];
  uint8_t   enb_index;
} RrcMacBcchMbmsDataReq;

typedef struct RrcMacBcchMbmsDataInd_s {
  uint32_t  frame;
  uint8_t   sub_frame;
  uint32_t  sdu_size;
  uint8_t   sdu[BCCH_SDU_MBMS_SIZE];
  uint8_t   enb_index;
  uint8_t   rsrq;
  uint8_t   rsrp;
} RrcMacBcchMbmsDataInd;


typedef struct RrcMacCcchDataReq_s {
  uint32_t  frame;
  uint32_t  sdu_size;
  uint8_t   sdu[CCCH_SDU_SIZE];
  uint8_t   enb_index;
} RrcMacCcchDataReq;

typedef struct RrcMacCcchDataCnf_s {
  uint8_t   enb_index;
} RrcMacCcchDataCnf;

typedef struct RrcMacCcchDataInd_s {
  uint32_t  frame;
  uint8_t   sub_frame;
  uint16_t  rnti;
  uint32_t  sdu_size;
  uint8_t   sdu[CCCH_SDU_SIZE];
  uint8_t   enb_index;
  int       CC_id;
} RrcMacCcchDataInd;

typedef struct NRRrcMacCcchDataInd_s {
  uint32_t  sdu_size;
  uint8_t   sdu[CCCH_SDU_SIZE];
} NRRrcMacCcchDataInd;

typedef struct RrcMacMcchDataReq_s {
  uint32_t  frame;
  uint32_t  sdu_size;
  uint8_t   sdu[MCCH_SDU_SIZE];
  uint8_t   enb_index;
  uint8_t   mbsfn_sync_area;
} RrcMacMcchDataReq;

typedef struct RrcMacMcchDataInd_s {
  uint32_t  frame;
  uint8_t   sub_frame;
  uint32_t  sdu_size;
  uint8_t   sdu[MCCH_SDU_SIZE];
  uint8_t   enb_index;
  uint8_t   mbsfn_sync_area;
} RrcMacMcchDataInd;

typedef struct RrcMacPcchDataReq_s {
  uint32_t  frame;
  uint32_t  sdu_size;
  uint8_t   sdu[PCCH_SDU_SIZE];
  uint8_t   enb_index;
} RrcMacPcchDataReq;

/* RRC configures DRX context (MAC timers) of a UE */
typedef struct rrc_mac_drx_config_req_s {
  /* UE RNTI to configure */
  rnti_t rnti;

  /* DRX configuration from MacMainConfig to configure UE's local timers */
  LTE_DRX_Config_t * drx_Configuration;
} rrc_mac_drx_config_req_t;

typedef struct rlc_am_status_s {
  boolean_t initialized;
  uint16_t vt_a;
  uint16_t vt_ms;
  uint16_t vt_s;
  uint16_t poll_sn;
  uint16_t vr_r;
  uint16_t vr_mr;
  uint16_t vr_x;
  uint16_t vr_ms;
  uint16_t vr_h;
  boolean_t pdu_retransmission_trigger;
  boolean_t pdu_retransmission_trigger_nack;
  boolean_t status_trigger;
  boolean_t status_trigger_nack;
  boolean_t status_trigger_time_out;
  boolean_t poll_received_trigger_nack;
  boolean_t poll_received_trigger;
  boolean_t poll_trigger_retransmit_pdu;
  boolean_t poll_trigger_poll_sn;
  boolean_t poll_received_trigger_t_status_prohibit;
  boolean_t t_status_prohibit_active;
  boolean_t t_status_prohibit_poll_retransmit_active;
  boolean_t initialized_control_pdu;
  boolean_t retrans_control_pdu;
  boolean_t initialized_data_pdu;
  boolean_t retrans_data_pdu;
} rlc_am_status_t;

///////////////////////////////////
//        RRC => MAC
///////////////////////////////////

typedef struct {
  module_id_t module_id;
  int CC_id;
  rnti_t rnti;
  uint64_t eNB_ue_s1ap_id;
} rrc_mac_enb_index_t;

typedef struct {
  uint8_t  num_pdcch_symbols;
  uint8_t  prach_root;
  uint8_t  prach_config_index;
  uint8_t  prach_high_speed;
  uint8_t  prach_zero_correlation;
  uint8_t  prach_freq_offset;
  uint8_t  pucch_delta_shift;
  uint8_t  pucch_nRB_CQI;
  uint8_t  pucch_nCS_AN;
  uint8_t  pucch_n1_AN;
  uint8_t  pdsch_start;
  uint8_t  ul_bandwidth;
  uint8_t  dl_bandwidth;
  uint8_t  Nid_cell;
  uint8_t  Ncp;
  uint8_t  frame_type;
  uint8_t  tdd_config;
  uint8_t  tdd_config_s;
  uint8_t  mode;
  uint8_t  Nid_cell_mbsfn;
  uint8_t  Ncp_mbsfn;
  uint8_t  num_MBSFN_config;
  // MBSFN subframe configuration
  uint8_t  MBSFN_config[8];
  uint8_t  MBSFN_mode[8];
} rrc_mac_config_req_eNB_t;

typedef struct {
  module_id_t module_id;
  int CC_id;
  rnti_t rnti;
  rnti_t target_rnti;
  uint8_t rrc_status;
} rrc_mac_release_ind_t;

// message structure for RRC MAC IN SYNC/OUT OF SYNC INDICATION
typedef struct {
  int                 frame;
  uint8_t             enb_index;
  uint8_t             in_sync;
} rrc_mac_sync_ind_t;

// message structure for RRC MAC BCCH-CCCH-CTXT-RX-IND
typedef struct {
  module_id_t module_id;
  int CC_id;
  frame_t     frame;
  sub_frame_t sub_frame;
  rnti_t      rnti;
  uint8_t     CE_level;
  uint8_t     *sdu;
  uint8_t     sdu_len;
  uint8_t     enb_index;
  int       rsrq;
  int       rsrp;
  uint8_t   harq_pid;
} rrc_mac_ccch_data_ind_t;

typedef struct {
  eNB_index_t  eNB_index;
  frame_t frame;
  int sync_ind;
} rrc_mac_in_sync_ind_t;

typedef struct {
  eNB_index_t  eNB_index;
  frame_t frame;
  int sync_ind;
} rrc_mac_out_of_sync_ind_t;

typedef struct {
  uint32_t source_ue_id;
  uint32_t source_enb_id;
  uint32_t target_enb_id;
  uint32_t transaction_id;
  uint8_t  rrc_container[1024];
  int      rrc_container_size;
} rrc_x2_HO_req_t;

typedef struct {
  int rnti;
  boolean_t  first_rrcreconfiguration_flag;
} rrc_ue_rrcreconfiguration_state;


typedef struct {
  // True if the UE should skip the RA procedure during reconfiguration
  bool  skip_ra_procedure;
} nr_rrc_mac_reconfiguration_complete_req_t;

typedef struct {
  uint32_t cause;
} nr_mac_rrc_config_reset_req_t;

typedef struct {
  NR_CellGroupConfig_t *cellGroupConfig;
  NR_UE_NR_Capability_t *UE_NR_Capability;
} nr_mac_rrc_config_req_cg_t;

typedef struct {
  NR_BCCH_BCH_Message_t *bcch;
  bool get_sib;
} nr_mac_rrc_config_req_mib_t;

typedef struct {
  NR_SIB1_t *sib1;
  bool can_start_ra;
} nr_mac_rrc_config_req_sib1_t;

typedef struct {
  NR_SIB19_r17_t *sib19;
  bool can_start_ra;
} nr_mac_rrc_config_req_other_sib_t;

///////////////////////////////////
//        MAC => RRC
///////////////////////////////////

//MAC TO RRC Message
typedef struct {
  module_id_t module_id;
  frame_t     frame;
  sub_frame_t sub_frame;
  eNB_index_t eNB_index;
} rrc_mac_bcch_data_req_t;

typedef struct {
  module_id_t module_id;
  frame_t     frame;
  sub_frame_t sub_frame;
  rnti_t      rnti;
  uint8_t     *sdu;
  uint8_t     sdu_len;
  uint8_t     enb_index;
  uint8_t     *sdu2;
  uint8_t     sdu2_len;
  uint8_t     *sdu3;
  uint8_t     sdu3_len;

} rrc_mac_bcch_data_ind_t;

typedef struct {
  module_id_t module_id;
  frame_t     frame;
  sub_frame_t sub_frame;
  uint8_t     mbsfn_sync_area;
  uint8_t     *sdu;
  uint8_t     sdu_len;
} rrc_mac_bcch_mbms_data_ind_t;

typedef struct {
  module_id_t module_id;
  frame_t     frame;
  sub_frame_t sub_frame;
  uint8_t     mbsfn_sync_area;
} rrc_mac_bcch_mbms_data_req_t;

typedef struct {
  module_id_t module_id;
  frame_t frame;
  bool ra_successful;
} nr_rrc_mac_ra_ind_t;

typedef struct {
  module_id_t module_id;
  frame_t frame;
  sub_frame_t sub_frame;
  rnti_t rnti;
  uint8_t *sdu;
  uint8_t sdu_len;
  uint8_t cell_id;
  bool dedicated_rach;
} nr_rrc_mac_msg3_ind_t;

typedef struct {
  module_id_t module_id;
  bool inactivity_timer_expired;
} nr_rrc_mac_inac_ind_t;

typedef struct {
  module_id_t module_id;
  int CC_id;
  frame_t frame;
  uint8_t channel;
} rrc_mac_pcch_data_req_t;

/** @addtogroup _mac_impl_
 * @{
*/
typedef struct {
  rlc_buffer_occupancy_t  rlc_buffer_occupancy; // logical channel id
  struct LTE_LogicalChannelConfig__ul_SpecificParameters ul_SpecificParameters;
} mac_rlc_status_resp_t;
/**@}*/

typedef struct {
  rlc_service_info_t rlc_services;
} rlc_service_info_ue_status_t;

#endif /* MAC_MESSAGES_TYPES_H_ */
