/*************************************************************************************************************
Copyright 2015-2019, Silicon Laboratories, Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
 *************************************************************************************************************/
/*************************************************************************************
                  Silicon Laboratories Broadcast Si2183 Layer 1 API


   API functions prototypes used by commands and properties
   FILE: Si2183_Commands_Prototypes.h
   Supported IC : Si2183
   Compiled for ROM 2 firmware 5_B_build_1
   Revision: V0.3.5.1
   Date: November 06 2015
**************************************************************************************/
/* Change log:

 As from V0.3.0.0:
  <compatibility>[compiler/warning] Si2183_TRACE_COMMAND_REPLY now using (const char*)" " for the separator

 As from V0.1.4.0:
  <new_feature>[DVB-S2X/Gold_Sequences] Adding Si2183_DVBS2_PLS_INIT to allow locking on all Gold Sequences in DVB-S2X

 As from V0.1.3.0:
  <improvement>[traces/commands_responses] Adding Si2183_TRACE_COMMAND_REPLY (active when SiTRACES and Si2183_GET_COMMAND_STRINGS are both defined)
   This is to add all command response fields to traces and ease debug.
   Defining Si2183_TRACE_COMMAND_REPLY macro.

 As from V0.1.2.0:
  <new_feature>[ISDB-T/AC_data] Adding Si2183_L1_ISDBT_AC_BITS to retrieve ISDB-T AC data.

 As from V0.1.0.0:
  <new_feature>[DVB-S2/MULTISTREAM] Adding Si2183_DVBS2_STREAM_INFO and Si2183_DVBS2_STREAM_SELECT commands

 As from V0.0.0:
  Initial version (based on Si2164 code V0.3.4)
****************************************************************************************/
#ifndef    Si2183_COMMANDS_PROTOTYPES_H
#define    Si2183_COMMANDS_PROTOTYPES_H

unsigned char Si2183_CurrentResponseStatus (L1_Si2183_Context *api, unsigned char ptDataBuffer);
unsigned char Si2183_pollForCTS            (L1_Si2183_Context *api);
unsigned char Si2183_pollForResponse       (L1_Si2183_Context *api, unsigned int nbBytes, unsigned char *pByteBuffer);
unsigned char Si2183_L1_SendCommand2       (L1_Si2183_Context *api, unsigned int cmd_code);
unsigned char Si2183_L1_SetProperty        (L1_Si2183_Context *api, unsigned int prop_code, int  data);
unsigned char Si2183_L1_GetProperty        (L1_Si2183_Context *api, unsigned int prop_code, int *data);
unsigned char Si2183_L1_SetProperty2       (L1_Si2183_Context *api, unsigned int prop_code);
unsigned char Si2183_L1_GetProperty2       (L1_Si2183_Context *api, unsigned int prop_code);

#ifdef    Si2183_GET_PROPERTY_STRING
unsigned char Si2183_L1_GetPropertyString  (L1_Si2183_Context *api, unsigned int prop_code, const char *separator, char *msg);
unsigned char Si2183_L1_PropertyText       (Si2183_PropObj   *prop, unsigned int prop_code, const char *separator, char *msg);
#endif /* Si2183_GET_PROPERTY_STRING */

#ifdef    Si2183_GET_COMMAND_STRINGS
  unsigned char   Si2183_L1_GetCommandResponseString(L1_Si2183_Context *api, unsigned int cmd_code, const char *separator, char *msg);
  #ifdef SiTRACES
    #define   Si2183_TRACE_COMMAND_REPLY(api, cmd_code) Si2183_L1_GetCommandResponseString (api, cmd_code, (const char*)" ", api->msg); SiTRACE("Resp>> %s\n", api->msg);
  #endif /* SiTRACES */
#endif /* Si2183_GET_COMMAND_STRINGS */
#ifndef   Si2183_TRACE_COMMAND_REPLY
  #define   Si2183_TRACE_COMMAND_REPLY(api, cmd_code) /* Do nothing */
#endif /* Si2183_TRACE_COMMAND_REPLY */

#ifdef    Si2183_CONFIG_CLKIO_CMD
unsigned char Si2183_L1_CONFIG_CLKIO              (L1_Si2183_Context *api,
                                                   unsigned char   output,
                                                   unsigned char   pre_driver_str,
                                                   unsigned char   driver_str);
#endif /* Si2183_CONFIG_CLKIO_CMD */
#ifdef    Si2183_CONFIG_I2C_CMD
unsigned char Si2183_L1_CONFIG_I2C                (L1_Si2183_Context *api,
                                                   unsigned char   subcode,
                                                   unsigned char   i2c_broadcast);
#endif /* Si2183_CONFIG_I2C_CMD */
#ifdef    Si2183_CONFIG_PINS_CMD
unsigned char Si2183_L1_CONFIG_PINS               (L1_Si2183_Context *api,
                                                   unsigned char   gpio0_mode,
                                                   unsigned char   gpio0_read,
                                                   unsigned char   gpio1_mode,
                                                   unsigned char   gpio1_read);
#endif /* Si2183_CONFIG_PINS_CMD */
#ifdef    Si2183_DD_BER_CMD
unsigned char Si2183_L1_DD_BER                    (L1_Si2183_Context *api,
                                                   unsigned char   rst);
#endif /* Si2183_DD_BER_CMD */
#ifdef    Si2183_DD_CBER_CMD
unsigned char Si2183_L1_DD_CBER                   (L1_Si2183_Context *api,
                                                   unsigned char   rst);
#endif /* Si2183_DD_CBER_CMD */
#ifdef    SATELLITE_FRONT_END
#ifdef    Si2183_DD_DISEQC_SEND_CMD
unsigned char Si2183_L1_DD_DISEQC_SEND            (L1_Si2183_Context *api,
                                                   unsigned char   enable,
                                                   unsigned char   cont_tone,
                                                   unsigned char   tone_burst,
                                                   unsigned char   burst_sel,
                                                   unsigned char   end_seq,
                                                   unsigned char   msg_length,
                                                   unsigned char   msg_byte1,
                                                   unsigned char   msg_byte2,
                                                   unsigned char   msg_byte3,
                                                   unsigned char   msg_byte4,
                                                   unsigned char   msg_byte5,
                                                   unsigned char   msg_byte6);
#endif /* Si2183_DD_DISEQC_SEND_CMD */
#ifdef    Si2183_DD_DISEQC_STATUS_CMD
unsigned char Si2183_L1_DD_DISEQC_STATUS          (L1_Si2183_Context *api,
                                                   unsigned char   listen);
#endif /* Si2183_DD_DISEQC_STATUS_CMD */
#ifdef    Si2183_DD_EXT_AGC_SAT_CMD
unsigned char Si2183_L1_DD_EXT_AGC_SAT            (L1_Si2183_Context *api,
                                                   unsigned char   agc_1_mode,
                                                   unsigned char   agc_1_inv,
                                                   unsigned char   agc_2_mode,
                                                   unsigned char   agc_2_inv,
                                                   unsigned char   agc_1_kloop,
                                                   unsigned char   agc_2_kloop,
                                                   unsigned char   agc_1_min,
                                                   unsigned char   agc_2_min);
#endif /* Si2183_DD_EXT_AGC_SAT_CMD */
#endif /* SATELLITE_FRONT_END */

#ifdef    TERRESTRIAL_FRONT_END
#ifdef    Si2183_DD_EXT_AGC_TER_CMD
unsigned char Si2183_L1_DD_EXT_AGC_TER            (L1_Si2183_Context *api,
                                                   unsigned char   agc_1_mode,
                                                   unsigned char   agc_1_inv,
                                                   unsigned char   agc_2_mode,
                                                   unsigned char   agc_2_inv,
                                                   unsigned char   agc_1_kloop,
                                                   unsigned char   agc_2_kloop,
                                                   unsigned char   agc_1_min,
                                                   unsigned char   agc_2_min);
#endif /* Si2183_DD_EXT_AGC_TER_CMD */
#endif /* TERRESTRIAL_FRONT_END */

#ifdef    Si2183_DD_FER_CMD
unsigned char Si2183_L1_DD_FER                    (L1_Si2183_Context *api,
                                                   unsigned char   rst);
#endif /* Si2183_DD_FER_CMD */
#ifdef    Si2183_DD_GET_REG_CMD
unsigned char Si2183_L1_DD_GET_REG                (L1_Si2183_Context *api,
                                                   unsigned char   reg_code_lsb,
                                                   unsigned char   reg_code_mid,
                                                   unsigned char   reg_code_msb);
#endif /* Si2183_DD_GET_REG_CMD */
#ifdef    Si2183_DD_MP_DEFAULTS_CMD
unsigned char Si2183_L1_DD_MP_DEFAULTS            (L1_Si2183_Context *api,
                                                   unsigned char   mp_a_mode,
                                                   unsigned char   mp_b_mode,
                                                   unsigned char   mp_c_mode,
                                                   unsigned char   mp_d_mode);
#endif /* Si2183_DD_MP_DEFAULTS_CMD */
#ifdef    Si2183_DD_PER_CMD
unsigned char Si2183_L1_DD_PER                    (L1_Si2183_Context *api,
                                                   unsigned char   rst);
#endif /* Si2183_DD_PER_CMD */
#ifdef    Si2183_DD_RESTART_CMD
unsigned char Si2183_L1_DD_RESTART                (L1_Si2183_Context *api);
#endif /* Si2183_DD_RESTART_CMD */
#ifdef    Si2183_DD_RESTART_EXT_CMD
unsigned char Si2183_L1_DD_RESTART_EXT            (L1_Si2183_Context *api,
                                                   unsigned char   freq_plan,
                                                   unsigned char   freq_plan_ts_clk,
                                                   unsigned long   tuned_rf_freq);
#endif /* Si2183_DD_RESTART_EXT_CMD */
#ifdef    Si2183_DD_SET_REG_CMD
unsigned char Si2183_L1_DD_SET_REG                (L1_Si2183_Context *api,
                                                   unsigned char   reg_code_lsb,
                                                   unsigned char   reg_code_mid,
                                                   unsigned char   reg_code_msb,
                                                   unsigned long   value);
#endif /* Si2183_DD_SET_REG_CMD */
#ifdef    Si2183_DD_SSI_SQI_CMD
unsigned char Si2183_L1_DD_SSI_SQI                (L1_Si2183_Context *api,
                                                             char  tuner_rssi);
#endif /* Si2183_DD_SSI_SQI_CMD */
#ifdef    Si2183_DD_STATUS_CMD
unsigned char Si2183_L1_DD_STATUS                 (L1_Si2183_Context *api,
                                                   unsigned char   intack);
#endif /* Si2183_DD_STATUS_CMD */
#ifdef    Si2183_DD_TS_PINS_CMD
unsigned char Si2183_L1_DD_TS_PINS                (L1_Si2183_Context *api,
                                                   unsigned char   primary_ts_mode,
                                                   unsigned char   primary_ts_activity,
                                                   unsigned char   primary_ts_dir,
                                                   unsigned char   secondary_ts_mode,
                                                   unsigned char   secondary_ts_activity,
                                                   unsigned char   secondary_ts_dir,
                                                   unsigned char   demod_role,
                                                   unsigned long   master_freq);
#endif /* Si2183_DD_TS_PINS_CMD */
#ifdef    Si2183_DD_UNCOR_CMD
unsigned char Si2183_L1_DD_UNCOR                  (L1_Si2183_Context *api,
                                                   unsigned char   rst);
#endif /* Si2183_DD_UNCOR_CMD */
#ifdef    Si2183_DEMOD_INFO_CMD
unsigned char Si2183_L1_DEMOD_INFO                (L1_Si2183_Context *api);
#endif /* Si2183_DEMOD_INFO_CMD */
#ifdef    Si2183_DOWNLOAD_DATASET_CONTINUE_CMD
unsigned char Si2183_L1_DOWNLOAD_DATASET_CONTINUE (L1_Si2183_Context *api,
                                                   unsigned char   data0,
                                                   unsigned char   data1,
                                                   unsigned char   data2,
                                                   unsigned char   data3,
                                                   unsigned char   data4,
                                                   unsigned char   data5,
                                                   unsigned char   data6);
#endif /* Si2183_DOWNLOAD_DATASET_CONTINUE_CMD */
#ifdef    Si2183_DOWNLOAD_DATASET_START_CMD
unsigned char Si2183_L1_DOWNLOAD_DATASET_START    (L1_Si2183_Context *api,
                                                   unsigned char   dataset_id,
                                                   unsigned char   dataset_checksum,
                                                   unsigned char   data0,
                                                   unsigned char   data1,
                                                   unsigned char   data2,
                                                   unsigned char   data3,
                                                   unsigned char   data4);
#endif /* Si2183_DOWNLOAD_DATASET_START_CMD */
#ifdef    DEMOD_DVB_C2
#ifdef    Si2183_DVBC2_CTRL_CMD
unsigned char Si2183_L1_DVBC2_CTRL                (L1_Si2183_Context *api,
                                                   unsigned char   action,
                                                   unsigned long   tuned_rf_freq);
#endif /* Si2183_DVBC2_CTRL_CMD */
#ifdef    Si2183_DVBC2_DS_INFO_CMD
unsigned char Si2183_L1_DVBC2_DS_INFO             (L1_Si2183_Context *api,
                                                   unsigned char   ds_index_or_id,
                                                   unsigned char   ds_select_index_or_id);
#endif /* Si2183_DVBC2_DS_INFO_CMD */
#ifdef    Si2183_DVBC2_DS_PLP_SELECT_CMD
unsigned char Si2183_L1_DVBC2_DS_PLP_SELECT       (L1_Si2183_Context *api,
                                                   unsigned char   plp_id,
                                                   unsigned char   id_sel_mode,
                                                   unsigned char   ds_id);
#endif /* Si2183_DVBC2_DS_PLP_SELECT_CMD */
#ifdef    Si2183_DVBC2_PLP_INFO_CMD
unsigned char Si2183_L1_DVBC2_PLP_INFO            (L1_Si2183_Context *api,
                                                   unsigned char   plp_index,
                                                   unsigned char   plp_info_ds_mode,
                                                   unsigned char   ds_index);
#endif /* Si2183_DVBC2_PLP_INFO_CMD */
#ifdef    Si2183_DVBC2_STATUS_CMD
unsigned char Si2183_L1_DVBC2_STATUS              (L1_Si2183_Context *api,
                                                   unsigned char   intack);
#endif /* Si2183_DVBC2_STATUS_CMD */
#ifdef    Si2183_DVBC2_SYS_INFO_CMD
unsigned char Si2183_L1_DVBC2_SYS_INFO            (L1_Si2183_Context *api);
#endif /* Si2183_DVBC2_SYS_INFO_CMD */
#endif /* DEMOD_DVB_C2 */

#ifdef    DEMOD_DVB_C
#ifdef    Si2183_DVBC_STATUS_CMD
unsigned char Si2183_L1_DVBC_STATUS               (L1_Si2183_Context *api,
                                                   unsigned char   intack);
#endif /* Si2183_DVBC_STATUS_CMD */
#endif /* DEMOD_DVB_C */

#ifdef    DEMOD_DVB_S_S2_DSS
#ifdef    Si2183_DVBS2_PLS_INIT_CMD
unsigned char Si2183_L1_DVBS2_PLS_INIT            (L1_Si2183_Context *api,
                                                   unsigned char   pls_detection_mode,
                                                   unsigned long   pls);
#endif /* Si2183_DVBS2_PLS_INIT_CMD */
#ifdef    Si2183_DVBS2_STATUS_CMD
unsigned char Si2183_L1_DVBS2_STATUS              (L1_Si2183_Context *api,
                                                   unsigned char   intack);
#endif /* Si2183_DVBS2_STATUS_CMD */
#ifdef    Si2183_DVBS2_STREAM_INFO_CMD
unsigned char Si2183_L1_DVBS2_STREAM_INFO         (L1_Si2183_Context *api,
                                                   unsigned char   isi_index);
#endif /* Si2183_DVBS2_STREAM_INFO_CMD */
#ifdef    Si2183_DVBS2_STREAM_SELECT_CMD
unsigned char Si2183_L1_DVBS2_STREAM_SELECT       (L1_Si2183_Context *api,
                                                   unsigned char   stream_id,
                                                   unsigned char   stream_sel_mode);
#endif /* Si2183_DVBS2_STREAM_SELECT_CMD */
#ifdef    Si2183_DVBS_STATUS_CMD
unsigned char Si2183_L1_DVBS_STATUS               (L1_Si2183_Context *api,
                                                   unsigned char   intack);
#endif /* Si2183_DVBS_STATUS_CMD */
#endif /* DEMOD_DVB_S_S2_DSS */

#ifdef    DEMOD_DVB_T2
#ifdef    Si2183_DVBT2_FEF_CMD
unsigned char Si2183_L1_DVBT2_FEF                 (L1_Si2183_Context *api,
                                                   unsigned char   fef_tuner_flag,
                                                   unsigned char   fef_tuner_flag_inv);
#endif /* Si2183_DVBT2_FEF_CMD */
#ifdef    Si2183_DVBT2_PLP_INFO_CMD
unsigned char Si2183_L1_DVBT2_PLP_INFO            (L1_Si2183_Context *api,
                                                   unsigned char   plp_index);
#endif /* Si2183_DVBT2_PLP_INFO_CMD */
#ifdef    Si2183_DVBT2_PLP_SELECT_CMD
unsigned char Si2183_L1_DVBT2_PLP_SELECT          (L1_Si2183_Context *api,
                                                   unsigned char   plp_id,
                                                   unsigned char   plp_id_sel_mode);
#endif /* Si2183_DVBT2_PLP_SELECT_CMD */
#ifdef    Si2183_DVBT2_STATUS_CMD
unsigned char Si2183_L1_DVBT2_STATUS              (L1_Si2183_Context *api,
                                                   unsigned char   intack);
#endif /* Si2183_DVBT2_STATUS_CMD */
#ifdef    Si2183_DVBT2_TX_ID_CMD
unsigned char Si2183_L1_DVBT2_TX_ID               (L1_Si2183_Context *api);
#endif /* Si2183_DVBT2_TX_ID_CMD */
#endif /* DEMOD_DVB_T2 */

#ifdef    DEMOD_DVB_T
#ifdef    Si2183_DVBT_STATUS_CMD
unsigned char Si2183_L1_DVBT_STATUS               (L1_Si2183_Context *api,
                                                   unsigned char   intack);
#endif /* Si2183_DVBT_STATUS_CMD */
#ifdef    Si2183_DVBT_TPS_EXTRA_CMD
unsigned char Si2183_L1_DVBT_TPS_EXTRA            (L1_Si2183_Context *api);
#endif /* Si2183_DVBT_TPS_EXTRA_CMD */
#endif /* DEMOD_DVB_T */

#ifdef    Si2183_EXIT_BOOTLOADER_CMD
unsigned char Si2183_L1_EXIT_BOOTLOADER           (L1_Si2183_Context *api,
                                                   unsigned char   func,
                                                   unsigned char   ctsien);
#endif /* Si2183_EXIT_BOOTLOADER_CMD */
#ifdef    Si2183_GET_PROPERTY_CMD
unsigned char Si2183_L1_GET_PROPERTY              (L1_Si2183_Context *api,
                                                   unsigned char   reserved,
                                                   unsigned int    prop);
#endif /* Si2183_GET_PROPERTY_CMD */
#ifdef    Si2183_GET_REV_CMD
unsigned char Si2183_L1_GET_REV                   (L1_Si2183_Context *api);
#endif /* Si2183_GET_REV_CMD */
#ifdef    Si2183_I2C_PASSTHROUGH_CMD
unsigned char Si2183_L1_I2C_PASSTHROUGH           (L1_Si2183_Context *api,
                                                   unsigned char   subcode,
                                                   unsigned char   i2c_passthru,
                                                   unsigned char   reserved);
#endif /* Si2183_I2C_PASSTHROUGH_CMD */
#ifdef    DEMOD_ISDB_T
#ifdef    Si2183_ISDBT_AC_BITS_CMD
unsigned char Si2183_L1_ISDBT_AC_BITS             (L1_Si2183_Context *api,
                                                   unsigned char   byte_read_offset,
                                                   unsigned char   freeze_buffer,
                                                   unsigned char  *AC_bytes);
#endif /* Si2183_ISDBT_AC_BITS_CMD */
#ifdef    Si2183_ISDBT_LAYER_INFO_CMD
unsigned char Si2183_L1_ISDBT_LAYER_INFO          (L1_Si2183_Context *api,
                                                   unsigned char   layer_index);
#endif /* Si2183_ISDBT_LAYER_INFO_CMD */
#ifdef    Si2183_ISDBT_STATUS_CMD
unsigned char Si2183_L1_ISDBT_STATUS              (L1_Si2183_Context *api,
                                                   unsigned char   intack);
#endif /* Si2183_ISDBT_STATUS_CMD */
#endif /* DEMOD_ISDB_T */

#ifdef    DEMOD_MCNS
#ifdef    Si2183_MCNS_STATUS_CMD
unsigned char Si2183_L1_MCNS_STATUS               (L1_Si2183_Context *api,
                                                   unsigned char   intack);
#endif /* Si2183_MCNS_STATUS_CMD */
#endif /* DEMOD_MCNS */

#ifdef    Si2183_PART_INFO_CMD
unsigned char Si2183_L1_PART_INFO                 (L1_Si2183_Context *api);
#endif /* Si2183_PART_INFO_CMD */
#ifdef    Si2183_POWER_DOWN_CMD
unsigned char Si2183_L1_POWER_DOWN                (L1_Si2183_Context *api);
#endif /* Si2183_POWER_DOWN_CMD */
#ifdef    Si2183_POWER_UP_CMD
unsigned char Si2183_L1_POWER_UP                  (L1_Si2183_Context *api,
                                                   unsigned char   subcode,
                                                   unsigned char   reset,
                                                   unsigned char   reserved2,
                                                   unsigned char   reserved4,
                                                   unsigned char   reserved1,
                                                   unsigned char   addr_mode,
                                                   unsigned char   reserved5,
                                                   unsigned char   func,
                                                   unsigned char   clock_freq,
                                                   unsigned char   ctsien,
                                                   unsigned char   wake_up);
#endif /* Si2183_POWER_UP_CMD */
#ifdef    Si2183_RSSI_ADC_CMD
unsigned char Si2183_L1_RSSI_ADC                  (L1_Si2183_Context *api,
                                                   unsigned char   on_off);
#endif /* Si2183_RSSI_ADC_CMD */
#ifdef    Si2183_SCAN_CTRL_CMD
unsigned char Si2183_L1_SCAN_CTRL                 (L1_Si2183_Context *api,
                                                   unsigned char   action,
                                                   unsigned long   tuned_rf_freq);
#endif /* Si2183_SCAN_CTRL_CMD */
#ifdef    Si2183_SCAN_STATUS_CMD
unsigned char Si2183_L1_SCAN_STATUS               (L1_Si2183_Context *api,
                                                   unsigned char   intack);
#endif /* Si2183_SCAN_STATUS_CMD */
#ifdef    Si2183_SET_PROPERTY_CMD
unsigned char Si2183_L1_SET_PROPERTY              (L1_Si2183_Context *api,
                                                   unsigned char   reserved,
                                                   unsigned int    prop,
                                                   unsigned int    data);
#endif /* Si2183_SET_PROPERTY_CMD */
#ifdef    Si2183_SPI_LINK_CMD
unsigned char Si2183_L1_SPI_LINK                  (L1_Si2183_Context *api,
                                                   unsigned char   subcode,
                                                   unsigned char   spi_pbl_key,
                                                   unsigned char   spi_pbl_num,
                                                   unsigned char   spi_conf_clk,
                                                   unsigned char   spi_clk_pola,
                                                   unsigned char   spi_conf_data,
                                                   unsigned char   spi_data_dir,
                                                   unsigned char   spi_enable);
#endif /* Si2183_SPI_LINK_CMD */
#ifdef    Si2183_SPI_PASSTHROUGH_CMD
unsigned char Si2183_L1_SPI_PASSTHROUGH           (L1_Si2183_Context *api,
                                                   unsigned char   subcode,
                                                   unsigned char   spi_passthr_clk,
                                                   unsigned char   spi_passth_data);
#endif /* Si2183_SPI_PASSTHROUGH_CMD */
#ifdef    Si2183_START_CLK_CMD
unsigned char Si2183_L1_START_CLK                 (L1_Si2183_Context *api,
                                                   unsigned char   subcode,
                                                   unsigned char   reserved1,
                                                   unsigned char   tune_cap,
                                                   unsigned char   reserved2,
                                                   unsigned int    clk_mode,
                                                   unsigned char   reserved3,
                                                   unsigned char   reserved4,
                                                   unsigned char   start_clk);
#endif /* Si2183_START_CLK_CMD */

#endif /* Si2183_COMMANDS_PROTOTYPES_H */













