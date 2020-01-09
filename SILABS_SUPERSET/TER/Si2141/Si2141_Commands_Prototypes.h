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
                  Silicon Laboratories Broadcast Si2141 Layer 1 API


   API functions prototypes used by commands and properties
   FILE: Si2141_Commands_Prototypes.h
   Supported IC : Si2141
   Compiled for ROM 61 firmware 1_1_build_12
   Revision: 0.5
   Date: June 14 2019
**************************************************************************************/
#ifndef    Si2141_COMMANDS_PROTOTYPES_H
#define    Si2141_COMMANDS_PROTOTYPES_H

unsigned char Si2141_CurrentResponseStatus (L1_Si2141_Context *api, unsigned char ptDataBuffer);
unsigned char Si2141_pollForResetState     (L1_Si2141_Context *api);
unsigned char Si2141_GetStatus             (L1_Si2141_Context *api);
unsigned char Si2141_pollForCTS            (L1_Si2141_Context *api);
unsigned char Si2141_pollForResponse       (L1_Si2141_Context *api, unsigned int nbBytes, unsigned char *pByteBuffer);
unsigned char Si2141_L1_SendCommand2       (L1_Si2141_Context *api, unsigned int cmd_code);
unsigned char Si2141_L1_SetProperty        (L1_Si2141_Context *api, unsigned int prop_code, int  data);
unsigned char Si2141_L1_GetProperty        (L1_Si2141_Context *api, unsigned int prop_code, int *data);
unsigned char Si2141_L1_SetProperty2       (L1_Si2141_Context *api, unsigned int prop_code);
unsigned char Si2141_L1_GetProperty2       (L1_Si2141_Context *api, unsigned int prop_code);

#ifdef    Si2141_GET_PROPERTY_STRING
unsigned char Si2141_L1_GetPropertyString  (L1_Si2141_Context *api, unsigned int prop_code, const char *separator, char *msg);
unsigned char Si2141_L1_PropertyText       (Si2141_PropObj   *prop, unsigned int prop_code, const char *separator, char *msg);
#endif /* Si2141_GET_PROPERTY_STRING */

#ifdef    Si2141_GET_COMMAND_STRINGS
  unsigned char   Si2141_L1_GetCommandResponseString(L1_Si2141_Context *api, unsigned int cmd_code, const char *separator, char *msg);
#endif /* Si2141_GET_COMMAND_STRINGS */

#ifdef    Si2141_AGC_OVERRIDE_CMD
unsigned char Si2141_L1_AGC_OVERRIDE    (L1_Si2141_Context *api,
                                         unsigned char   force_max_gain,
                                         unsigned char   force_top_gain);
#endif /* Si2141_AGC_OVERRIDE_CMD */
#ifdef    Si2141_CONFIG_CLOCKS_CMD
unsigned char Si2141_L1_CONFIG_CLOCKS   (L1_Si2141_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   clock_mode,
                                         unsigned char   en_xout);
#endif /* Si2141_CONFIG_CLOCKS_CMD */
#ifdef    Si2141_CONFIG_I2C_CMD
unsigned char Si2141_L1_CONFIG_I2C      (L1_Si2141_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   i2c_broadcast);
#endif /* Si2141_CONFIG_I2C_CMD */
#ifdef    Si2141_CONFIG_PINS_CMD
unsigned char Si2141_L1_CONFIG_PINS     (L1_Si2141_Context *api,
                                         unsigned char   gpio1_mode,
                                         unsigned char   gpio1_read,
                                         unsigned char   gpio2_mode,
                                         unsigned char   gpio2_read,
                                         unsigned char   agc1_mode,
                                         unsigned char   agc1_read,
                                         unsigned char   agc2_mode,
                                         unsigned char   agc2_read,
                                         unsigned char   xout_mode);
#endif /* Si2141_CONFIG_PINS_CMD */
#ifdef    Si2141_EXIT_BOOTLOADER_CMD
unsigned char Si2141_L1_EXIT_BOOTLOADER (L1_Si2141_Context *api,
                                         unsigned char   func,
                                         unsigned char   ctsien);
#endif /* Si2141_EXIT_BOOTLOADER_CMD */
#ifdef    Si2141_FINE_TUNE_CMD
unsigned char Si2141_L1_FINE_TUNE       (L1_Si2141_Context *api,
                                         unsigned char   persistence,
                                                   int   offset_500hz);
#endif /* Si2141_FINE_TUNE_CMD */
#ifdef    Si2141_GET_PROPERTY_CMD
unsigned char Si2141_L1_GET_PROPERTY    (L1_Si2141_Context *api,
                                         unsigned char   reserved,
                                         unsigned int    prop);
#endif /* Si2141_GET_PROPERTY_CMD */
#ifdef    Si2141_GET_REV_CMD
unsigned char Si2141_L1_GET_REV         (L1_Si2141_Context *api);
#endif /* Si2141_GET_REV_CMD */
#ifdef    Si2141_PART_INFO_CMD
unsigned char Si2141_L1_PART_INFO       (L1_Si2141_Context *api);
#endif /* Si2141_PART_INFO_CMD */
#ifdef    Si2141_PART_INFO2_CMD
unsigned char Si2141_L1_PART_INFO2      (L1_Si2141_Context *api);
#endif /* Si2141_PART_INFO2_CMD */
#ifdef    Si2141_POWER_DOWN_HW_CMD
unsigned char Si2141_L1_POWER_DOWN_HW   (L1_Si2141_Context *api,
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
#endif /* Si2141_POWER_DOWN_HW_CMD */
#ifdef    Si2141_POWER_UP_CMD
unsigned char Si2141_L1_POWER_UP        (L1_Si2141_Context *api,
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
#endif /* Si2141_POWER_UP_CMD */
#ifdef    Si2141_POWER_UP8_1_CMD
unsigned char Si2141_L1_POWER_UP8_1     (L1_Si2141_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   clock_mode,
                                         unsigned char   en_xout,
                                         unsigned char   config_1p8v,
                                         unsigned char   reserved3,
                                         unsigned char   reserved4,
                                         unsigned char   reserved5,
                                         unsigned char   reserved6);
#endif /* Si2141_POWER_UP8_1_CMD */
#ifdef    Si2141_POWER_UP8_2_CMD
unsigned char Si2141_L1_POWER_UP8_2     (L1_Si2141_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   reserved7,
                                         unsigned char   reserved8);
#endif /* Si2141_POWER_UP8_2_CMD */
#ifdef    Si2141_REREAD_REPLY_CMD
unsigned char Si2141_L1_REREAD_REPLY    (L1_Si2141_Context *api,
                                         unsigned char   offset);
#endif /* Si2141_REREAD_REPLY_CMD */
#ifdef    Si2141_RESET_HW_CMD
unsigned char Si2141_L1_RESET_HW        (L1_Si2141_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   reserved1,
                                         unsigned char   reserved2);
#endif /* Si2141_RESET_HW_CMD */
#ifdef    Si2141_SET_PROPERTY_CMD
unsigned char Si2141_L1_SET_PROPERTY    (L1_Si2141_Context *api,
                                         unsigned char   reserved,
                                         unsigned int    prop,
                                         unsigned int    data);
#endif /* Si2141_SET_PROPERTY_CMD */
#ifdef    Si2141_STANDBY_CMD
unsigned char Si2141_L1_STANDBY         (L1_Si2141_Context *api,
                                         unsigned char   type);
#endif /* Si2141_STANDBY_CMD */
#ifdef    Si2141_TUNER_STATUS_CMD
unsigned char Si2141_L1_TUNER_STATUS    (L1_Si2141_Context *api);
#endif /* Si2141_TUNER_STATUS_CMD */
#ifdef    Si2141_TUNER_TUNE_FREQ_CMD
unsigned char Si2141_L1_TUNER_TUNE_FREQ (L1_Si2141_Context *api,
                                         unsigned char   mode,
                                         unsigned long   freq);
#endif /* Si2141_TUNER_TUNE_FREQ_CMD */
#ifdef    Si2141_WAKE_UP_CMD
unsigned char Si2141_L1_WAKE_UP         (L1_Si2141_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   reset,
                                         unsigned char   clock_freq,
                                         unsigned char   reserved9,
                                         unsigned char   func,
                                         unsigned char   wake_up);
#endif /* Si2141_WAKE_UP_CMD */

#endif /* Si2141_COMMANDS_PROTOTYPES_H */













