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
                  Silicon Laboratories Broadcast Si2124 Layer 1 API


   API functions prototypes used by commands and properties
   FILE: Si2124_Commands_Prototypes.h
   Supported IC : Si2124
   Compiled for ROM 62 firmware 2_1_build_5
   Revision: 0.2
   Date: July 24 2017
**************************************************************************************/
#ifndef    Si2124_COMMANDS_PROTOTYPES_H
#define    Si2124_COMMANDS_PROTOTYPES_H

unsigned char Si2124_CurrentResponseStatus (L1_Si2124_Context *api, unsigned char ptDataBuffer);
unsigned char Si2124_pollForResetState     (L1_Si2124_Context *api);
unsigned char Si2124_pollForCTS            (L1_Si2124_Context *api);
unsigned char Si2124_pollForResponse       (L1_Si2124_Context *api, unsigned int nbBytes, unsigned char *pByteBuffer);
unsigned char Si2124_GetStatus             (L1_Si2124_Context *api);
unsigned char Si2124_L1_SendCommand2       (L1_Si2124_Context *api, unsigned int cmd_code);
unsigned char Si2124_L1_SetProperty        (L1_Si2124_Context *api, unsigned int prop_code, signed int  data);
unsigned char Si2124_L1_GetProperty        (L1_Si2124_Context *api, unsigned int prop_code, signed int *data);
unsigned char Si2124_L1_SetProperty2       (L1_Si2124_Context *api, unsigned int prop_code);
unsigned char Si2124_L1_GetProperty2       (L1_Si2124_Context *api, unsigned int prop_code);

#ifdef    Si2124_GET_PROPERTY_STRING
unsigned char Si2124_L1_GetPropertyString  (L1_Si2124_Context *api, unsigned int prop_code, const char *separator, char *msg);
unsigned char Si2124_L1_PropertyText       (Si2124_PropObj   *prop, unsigned int prop_code, const char *separator, char *msg);
#endif /* Si2124_GET_PROPERTY_STRING */

#ifdef    Si2124_GET_COMMAND_STRINGS
unsigned char   Si2124_L1_GetCommandResponseString(L1_Si2124_Context *api, unsigned int cmd_code, const char *separator, char *msg);
#endif /* Si2124_GET_COMMAND_STRINGS */

#ifdef    Si2124_AGC_OVERRIDE_CMD
unsigned char Si2124_L1_AGC_OVERRIDE    (L1_Si2124_Context *api,
                                         unsigned char   force_max_gain,
                                         unsigned char   force_top_gain);
#endif /* Si2124_AGC_OVERRIDE_CMD */
#ifdef    Si2124_CONFIG_CLOCKS_CMD
unsigned char Si2124_L1_CONFIG_CLOCKS   (L1_Si2124_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   clock_mode,
                                         unsigned char   en_xout);
#endif /* Si2124_CONFIG_CLOCKS_CMD */
#ifdef    Si2124_CONFIG_I2C_CMD
unsigned char Si2124_L1_CONFIG_I2C      (L1_Si2124_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   i2c_broadcast);
#endif /* Si2124_CONFIG_I2C_CMD */
#ifdef    Si2124_CONFIG_PINS_CMD
unsigned char Si2124_L1_CONFIG_PINS     (L1_Si2124_Context *api,
                                         unsigned char   gpio1_mode,
                                         unsigned char   gpio1_read,
                                         unsigned char   gpio2_mode,
                                         unsigned char   gpio2_read,
                                         unsigned char   agc1_mode,
                                         unsigned char   agc1_read,
                                         unsigned char   agc2_mode,
                                         unsigned char   agc2_read,
                                         unsigned char   xout_mode);
#endif /* Si2124_CONFIG_PINS_CMD */
#ifdef    Si2124_EXIT_BOOTLOADER_CMD
unsigned char Si2124_L1_EXIT_BOOTLOADER (L1_Si2124_Context *api,
                                         unsigned char   func,
                                         unsigned char   ctsien);
#endif /* Si2124_EXIT_BOOTLOADER_CMD */
#ifdef    Si2124_FINE_TUNE_CMD
unsigned char Si2124_L1_FINE_TUNE       (L1_Si2124_Context *api,
                                         unsigned char   persistence,
                                         signed   int    offset_500hz);
#endif /* Si2124_FINE_TUNE_CMD */
#ifdef    Si2124_GET_PROPERTY_CMD
unsigned char Si2124_L1_GET_PROPERTY    (L1_Si2124_Context *api,
                                         unsigned char   reserved,
                                         unsigned int    prop);
#endif /* Si2124_GET_PROPERTY_CMD */
#ifdef    Si2124_GET_REV_CMD
unsigned char Si2124_L1_GET_REV         (L1_Si2124_Context *api);
#endif /* Si2124_GET_REV_CMD */
#ifdef    Si2124_PART_INFO_CMD
unsigned char Si2124_L1_PART_INFO       (L1_Si2124_Context *api);
#endif /* Si2124_PART_INFO_CMD */
#ifdef    Si2124_PART_INFO2_CMD
unsigned char Si2124_L1_PART_INFO2      (L1_Si2124_Context *api);
#endif /* Si2124_PART_INFO2_CMD */
#ifdef    Si2124_POLL_CTS_CMD
unsigned char Si2124_L1_POLL_CTS        (L1_Si2124_Context *api);
#endif /* Si2124_POLL_CTS_CMD */
#ifdef    Si2124_POWER_DOWN_HW_CMD
unsigned char Si2124_L1_POWER_DOWN_HW   (L1_Si2124_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   pdb_xo_osc,
                                         unsigned char   reserved1,
                                         unsigned char   en_xout,
                                         unsigned char   reserved2,
                                         unsigned char   reserved3,
                                         unsigned char   reserved4,
                                         unsigned char   reserved5,
                                         unsigned char   reserved6,
                                         unsigned char   reserved7,
                                         unsigned char   reserved8,
                                         unsigned char   reserved9);
#endif /* Si2124_POWER_DOWN_HW_CMD */
#ifdef    Si2124_POWER_UP_CMD
unsigned char Si2124_L1_POWER_UP        (L1_Si2124_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   clock_mode,
                                         unsigned char   en_xout,
                                         unsigned char   config_1p8v,
                                         unsigned char   reserved3,
                                         unsigned char   reserved4,
                                         unsigned char   reserved5,
                                         unsigned char   reserved6,
                                         unsigned char   reserved7,
                                         unsigned char   reserved8);
#endif /* Si2124_POWER_UP_CMD */
#ifdef    Si2124_POWER_UP8_1_CMD
unsigned char Si2124_L1_POWER_UP8_1     (L1_Si2124_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   clock_mode,
                                         unsigned char   en_xout,
                                         unsigned char   config_1p8v,
                                         unsigned char   reserved3,
                                         unsigned char   reserved4,
                                         unsigned char   reserved5,
                                         unsigned char   reserved6);
#endif /* Si2124_POWER_UP8_1_CMD */
#ifdef    Si2124_POWER_UP8_2_CMD
unsigned char Si2124_L1_POWER_UP8_2     (L1_Si2124_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   reserved7,
                                         unsigned char   reserved8);
#endif /* Si2124_POWER_UP8_2_CMD */
#ifdef    Si2124_REREAD_REPLY_CMD
unsigned char Si2124_L1_REREAD_REPLY    (L1_Si2124_Context *api,
                                         unsigned char   offset);
#endif /* Si2124_REREAD_REPLY_CMD */
#ifdef    Si2124_RESET_HW_CMD
unsigned char Si2124_L1_RESET_HW        (L1_Si2124_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   reserved1,
                                         unsigned char   reserved2);
#endif /* Si2124_RESET_HW_CMD */
#ifdef    Si2124_SET_PROPERTY_CMD
unsigned char Si2124_L1_SET_PROPERTY    (L1_Si2124_Context *api,
                                         unsigned char   reserved,
                                         unsigned int    prop,
                                         unsigned int    data);
#endif /* Si2124_SET_PROPERTY_CMD */
#ifdef    Si2124_STANDBY_CMD
unsigned char Si2124_L1_STANDBY         (L1_Si2124_Context *api,
                                         unsigned char   type);
#endif /* Si2124_STANDBY_CMD */
#ifdef    Si2124_TUNER_STATUS_CMD
unsigned char Si2124_L1_TUNER_STATUS    (L1_Si2124_Context *api);
#endif /* Si2124_TUNER_STATUS_CMD */
#ifdef    Si2124_TUNER_TUNE_FREQ_CMD
unsigned char Si2124_L1_TUNER_TUNE_FREQ (L1_Si2124_Context *api,
                                         unsigned char   mode,
                                         unsigned long   freq);
#endif /* Si2124_TUNER_TUNE_FREQ_CMD */
#ifdef    Si2124_WAKE_UP_CMD
unsigned char Si2124_L1_WAKE_UP         (L1_Si2124_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   reset,
                                         unsigned char   clock_freq,
                                         unsigned char   reserved9,
                                         unsigned char   func,
                                         unsigned char   wake_up);
#endif /* Si2124_WAKE_UP_CMD */

#endif /* Si2124_COMMANDS_PROTOTYPES_H */













