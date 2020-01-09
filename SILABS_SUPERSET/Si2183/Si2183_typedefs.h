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


   API types used by commands and properties
   FILE: Si2183_typedefs.h
   Supported IC : Si2183
   Compiled for ROM 2 firmware 5_B_build_1
   Revision: V0.3.5.1
   Date: November 06 2015
**************************************************************************************/
/* Change log:

 As from V0.1.3.0:
  <new_feature>[Broadcast_i2c/demods] Adding '#defines' for broadcast i2c
  <new_feature>[DVB-S2/Multiple_Input_Stream] Adding MIS_capability field in L1_Si2183_Context
  <new_feature>[DVB-C2/Seek] Changing values of DVB-C2 min and max lock times (200 min,  1000 max)

 As from V0.0.9.0
  <new_feature>[FW/From File] Moving definition of FW structure to allow using a pointer to the structure in the L1_Si2183_Context

 As from V0.0.7.0: <new_feature>[SPI/logs] Adding spi_download_ms and i2c_download_ms in Si2183_L1_Context.
    These values will be used to monitor the FW download times in SPI and I2C modes

 As from V0.0.6.0:
    <improvement>[Code_size] Adding a textBuffer in Si2183_L1_Context used when filling text strings

 As from V0.0.1.0:
  Adding TER_tuner_agc_input and TER_tuner_if_output to L1 context,
    to configure the TER IF interface
  Adding comments in L1_Si2183_Context to match first version of Si2183 documentation.
  Removing unused members of L1_Si2183_Context

 As from V0.0.0.0:
  Initial version (based on Si2164 code V0.3.4)
****************************************************************************************/
#ifndef   Si2183_TYPEDEFS_H
#define   Si2183_TYPEDEFS_H

/* _additional_defines_point */
#define Si2183_MAX_LENGTH         80

#define Si2183_DOWNLOAD_ON_CHANGE 1
#define Si2183_DOWNLOAD_ALWAYS    0

  #define Si2183_TERRESTRIAL 1

  #define Si2183_DVBT_MIN_LOCK_TIME    100
  #define Si2183_DVBT_MAX_LOCK_TIME   2000

#ifdef    DEMOD_ISDB_T
  #define Si2183_ISDBT_MIN_LOCK_TIME   100
  #define Si2183_ISDBT_MAX_LOCK_TIME  2000
#endif /* DEMOD_ISDB_T */

#define Si2183_CLOCK_ALWAYS_OFF 0
#define Si2183_CLOCK_ALWAYS_ON  1
#define Si2183_CLOCK_MANAGED    2

#ifdef    DEMOD_DVB_T2
  #define Si2183_DVBT2_MIN_LOCK_TIME       100
  #define Si2183_DVBT2_MAX_LOCK_TIME      2000
#endif /* DEMOD_DVB_T2 */

#ifdef    DEMOD_DVB_C
  #define Si2183_DVBC_MIN_LOCK_TIME     20
  #define Si2183_DVBC_MAX_SEARCH_TIME 5000
  #define Si2183_DVBC_MAX_SCAN_TIME  20000
#endif /* DEMOD_DVB_C */

#ifdef    DEMOD_DVB_C2
  #define Si2183_DVBC2_MIN_LOCK_TIME    200
  #define Si2183_DVBC2_MAX_LOCK_TIME   1000
#endif /* DEMOD_DVB_C2 */

#ifdef    SATELLITE_FRONT_END

  #define Si2183_DVBS_MIN_LOCK_TIME     50
  #define Si2183_DVBS_MAX_LOCK_TIME   1000

  #define Si2183_DVBS2_MIN_LOCK_TIME    50
  #define Si2183_DVBS2_MAX_LOCK_TIME  1000

  #define Si2183_SAT_MAX_SEARCH_TIME 120000

  #define Si2183_SATELLITE   2

#endif /* SATELLITE_FRONT_END */

#ifndef __FIRMWARE_STRUCT__
#define __FIRMWARE_STRUCT__
typedef struct  {
  unsigned char firmware_len;
  unsigned char firmware_table[16];
} firmware_struct;
#endif /* __FIRMWARE_STRUCT__ */

/* The following defines are to allow use of PowerUpWithPatch function with the powerUpUsingBroadcastI2C function. */
#define Si2183_SKIP_NONE          0x00
#define Si2183_SKIP_POWERUP       0x01
#define Si2183_SKIP_LOADFIRMWARE  0x02
#define Si2183_SKIP_STARTFIRMWARE 0x04
/* define the tuner broadcast address for common patch download. */
#define Si2183_BROADCAST_ADDRESS 0xCC

typedef struct _L1_Si2183_Context {
  L0_Context                 *i2c;
  L0_Context                  i2cObj;
  Si2183_CmdObj              *cmd;
  Si2183_CmdObj               cmdObj;
  Si2183_CmdReplyObj         *rsp;
  Si2183_CmdReplyObj          rspObj;
  Si2183_PropObj             *prop;
  Si2183_PropObj              propObj;
  Si2183_PropObj             *propShadow;
  Si2183_PropObj              propShadowObj;
  Si2183_COMMON_REPLY_struct *status;
  Si2183_COMMON_REPLY_struct  statusObj;
  char                        msgBuffer[1000];
  char                       *msg;
  int                         standard;
  int                         media;
  int propertyWriteMode;                 /* Selection of DOWNLOAD_ALWAYS/DOWNLOAD_ON_CHANGE      */
                                         /*  for properties.                                     */
                                         /*  Use ‘DOWNLOAD_ALWAYS’ only for debugging purposes   */
#ifdef    TERRESTRIAL_FRONT_END
  unsigned int  tuner_ter_clock_source;  /* TER clock source configuration                       */
  unsigned int  tuner_ter_clock_freq;    /* TER clock frequency configuration                    */
  unsigned int  tuner_ter_clock_input;   /* TER clock input pin configuration                    */
  unsigned int  tuner_ter_clock_control; /* TER clock management configuration                   */
  unsigned int  tuner_ter_agc_control;   /* TER AGC output and polarity configuration            */
  unsigned int  TER_tuner_agc_input;     /* TER AGC input on tuner side configuration            */
  unsigned int  TER_tuner_if_output;     /* TER IF output on tuner side configuration            */
  unsigned int  fef_selection;           /* Preferred FEF mode. May not be possible              */
  unsigned int  fef_mode;                /* Final FEF mode, taking into account HW limitations   */
  unsigned int  fef_pin;                 /* FEF pin used for TER tuner AGC freeze                */
  unsigned int  fef_level;               /* GPIO state on FEF_pin when used (during FEF periods) */
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    DEMOD_DVB_C
  unsigned int                load_DVB_C_Blindlock_Patch;
#endif /* DEMOD_DVB_C */
#ifdef    SATELLITE_FRONT_END
  unsigned int  tuner_sat_clock_source;  /* SAT clock source configuration                       */
  unsigned int  tuner_sat_clock_freq;    /* SAT clock frequency configuration                    */
  unsigned int  tuner_sat_clock_input;   /* SAT clock input pin configuration                    */
  unsigned int  tuner_sat_clock_control; /* SAT clock management configuration                   */
  unsigned int  MIS_capability;          /* DVB-S2 Multiple Input Stream capability flag         */
#endif /* SATELLITE_FRONT_END */
  unsigned int  spi_download;
  unsigned int  spi_send_option;
  unsigned int  spi_clk_pin;
  unsigned int  spi_clk_pola;
  unsigned int  spi_data_pin;
  unsigned int  spi_data_order;
  unsigned int  spi_buffer_size;
  unsigned int  spi_download_ms;
  unsigned int  i2c_download_ms;
  unsigned char load_control;
  unsigned int        nbLines;
  firmware_struct   *fw_table;
  unsigned int       nbSpiBytes;
  unsigned char     *spi_table;

} L1_Si2183_Context;


#endif /* Si2183_TYPEDEFS_H */







