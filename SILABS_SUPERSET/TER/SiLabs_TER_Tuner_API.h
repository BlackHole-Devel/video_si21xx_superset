/*************************************************************************************************************
Copyright 2019, Silicon Laboratories, Inc.

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
#ifndef _SiLabs_TER_Tuner_API_H_
#define _SiLabs_TER_Tuner_API_H_

/* Change log:
 As from V0.6.6: '#define L1_RF_TER_TUNER_MODULATION_ISDBT 4' added, for explicit ISDB-T support (previous code used DVB-T modulation settings for ISDB-T).
        This only has an impact on the AUTO settings for DTV_RF_TOP.
        DVB-T uses P5DB while ISDB-T uses P4DB in AUTO mode.
        Note that the recommendation is to use P7DB for ISDB-T, so most applications already have the proper value set in the user property prop->dtv_rf_top.dtv_rf_top.
        All other settings are identical between DVB-T and ISD-T.

 As from V0.5.2: '#define FRONT_END_COUNT  4' if not defined at project level. This is required to declare the 'extern SILABS_TER_TUNER_Context *TER_tuners[FRONT_END_COUNT];' array
  This array is used to store the TER tuner posigned   inters used in the VCO blocking feature. This is only useful for 'multiple' front-end designs (i.e. with FRONT_END_COUNT >= 2)

 As from V0.4.7: replacing #ifdef   TER_TUNER_CUSTOMTER by #ifndef   TER_TUNER_CUSTOMTER

*/

#define SILABS_TER_TUNER_API
#define TUNER_ADDRESS_TER            0xc0

/* Checking Compilation flags to make sure at least one tuner is selected */

#ifdef    TER_TUNER_SILABS
 #ifndef   TER_TUNER_Si2124
  #ifndef   TER_TUNER_Si2141
    #ifndef   TER_TUNER_Si2144
     #ifndef   TER_TUNER_Si2146
      #ifndef   TER_TUNER_Si2147
       #ifndef   TER_TUNER_Si2148
        #ifndef   TER_TUNER_Si2148B
         #ifndef   TER_TUNER_Si2151
          #ifndef   TER_TUNER_Si2156
           #ifndef   TER_TUNER_Si2157
            #ifndef   TER_TUNER_Si2158
             #ifndef   TER_TUNER_Si2158B
              #ifndef   TER_TUNER_Si2173
               #ifndef   TER_TUNER_Si2176
                #ifndef   TER_TUNER_Si2177
                 #ifndef   TER_TUNER_Si2178
                  #ifndef   TER_TUNER_Si2178B
                   #ifndef   TER_TUNER_Si2190
                    #ifndef   TER_TUNER_Si2190B
                     #ifndef   TER_TUNER_Si2191
                      #ifndef   TER_TUNER_Si2191B
                       #ifndef   TER_TUNER_Si2196
   "If you get a compilation error on this line, it means that you compiled with 'TER_TUNER_SILABS' without selecting the tuner(s) you want to use.";
   " Supported options: 'TER_TUNER_' + Si2141/Si2144/Si2146/Si2147/Si2148/Si2151/Si2156/Si2157/Si2158/Si2173/Si2176/Si2177/Si2178/Si2178B/Si2190/Si2190B/Si2191/Si2196/CUSTOMTER";
   " Please define at least one of these at project-level, in addition to TER_TUNER_SILABS.";
   " If required, you may also define Si21xx_TUNER_COUNT to use several tuners of the same type. (it defaults to '1' otherwise)";
                       #endif /* TER_TUNER_Si2196 */
                      #endif /* TER_TUNER_Si2191B */
                     #endif /* TER_TUNER_Si2191 */
                    #endif /* TER_TUNER_Si2190B */
                   #endif /* TER_TUNER_Si2190 */
                  #endif /* TER_TUNER_Si2178B */
                 #endif /* TER_TUNER_Si2178 */
                #endif /* TER_TUNER_Si2177 */
               #endif /* TER_TUNER_Si2176 */
              #endif /* TER_TUNER_Si2173 */
             #endif /* TER_TUNER_Si2158B */
            #endif /* TER_TUNER_Si2158 */
           #endif /* TER_TUNER_Si2157 */
          #endif /* TER_TUNER_Si2156 */
         #endif /* TER_TUNER_Si2151 */
        #endif /* TER_TUNER_Si2148B */
       #endif /* TER_TUNER_Si2148 */
      #endif /* TER_TUNER_Si2147 */
     #endif /* TER_TUNER_Si2146 */
    #endif /* TER_TUNER_Si2144 */
  #endif /* TER_TUNER_Si2141 */
 #endif /* TER_TUNER_Si2124 */
#endif /* TER_TUNER_SILABS */

#include "Silabs_L0_API.h"

#ifndef __VID_FILT_STRUCT__
#define __VID_FILT_STRUCT__
/* struct to read video filter file with varying line lengths */
typedef struct  {
  char vid_filt_len;
  unsigned char vid_filt_table [16];
} vid_filt_struct;
#endif /* __VID_FILT_STRUCT__ */

/* Including header files for selected tuners */
#ifdef    TER_TUNER_CUSTOMTER
  #define           CUSTOMTER_COMPATIBLE
  #include         "Silabs_L1_RF_CUSTOMTER_API.h"
#endif /* TER_TUNER_CUSTOMTER */
#ifdef    TER_TUNER_Si2124
  #define           Si2124_COMPATIBLE
  #define           Si2124_COMMAND_PROTOTYPES
  #include         "Si2124_L2_API.h"
#endif /* TER_TUNER_Si2124 */
#ifdef    TER_TUNER_Si2141
  #define           Si2141_COMPATIBLE
  #define           Si2141_COMMAND_PROTOTYPES
  #include         "Si2141_L2_API.h"
#endif /* TER_TUNER_Si2141 */
#ifdef    TER_TUNER_Si2144
  #define           Si2144_COMPATIBLE
  #define           Si2144_COMMAND_PROTOTYPES
  #include         "Si2144_L2_API.h"
#endif /* TER_TUNER_Si2144 */
#ifdef    TER_TUNER_Si2146
  #define           Si2146_COMPATIBLE
  #define           Si2146_COMMAND_PROTOTYPES
  #include         "Si2146_L2_API.h"
#endif /* TER_TUNER_Si2146 */
#ifdef    TER_TUNER_Si2147
  #define           Si2147_COMPATIBLE
  #define           Si2147_COMMAND_PROTOTYPES
  #include         "Si2147_L2_API.h"
#endif /* TER_TUNER_Si2147 */
#ifdef    TER_TUNER_Si2148
  #define           Si2148_COMPATIBLE
  #define           Si2148_COMMAND_PROTOTYPES
  #include         "Si2148_L2_API.h"
#endif /* TER_TUNER_Si2148 */
#ifdef    TER_TUNER_Si2148B
  #define           Si2148B_COMPATIBLE
  #define           Si2148B_COMMAND_PROTOTYPES
  #include         "Si2148B_L2_API.h"
#endif /* TER_TUNER_Si2148B */
#ifdef    TER_TUNER_Si2151
  #define           Si2151_COMPATIBLE
  #define           Si2151_COMMAND_PROTOTYPES
  #include         "Si2151_L2_API.h"
#endif /* TER_TUNER_Si2151 */
#ifdef    TER_TUNER_Si2156
  #define           Si2156_COMPATIBLE
  #define           Si2156_COMMAND_PROTOTYPES
  #include         "Si2156_L2_API.h"
#endif /* TER_TUNER_Si2156 */
#ifdef    TER_TUNER_Si2157
  #define           Si2157_COMPATIBLE
  #define           Si2157_COMMAND_PROTOTYPES
  #include         "Si2157_L2_API.h"
#endif /* TER_TUNER_Si2157 */
#ifdef    TER_TUNER_Si2158
  #define           Si2158_COMPATIBLE
  #define           Si2158_COMMAND_PROTOTYPES
  #include         "Si2158_L2_API.h"
#endif /* TER_TUNER_Si2158 */
#ifdef    TER_TUNER_Si2158B
  #define           Si2158B_COMPATIBLE
  #define           Si2158B_COMMAND_PROTOTYPES
  #include         "Si2158B_L2_API.h"
#endif /* TER_TUNER_Si2158B */
#ifdef    TER_TUNER_Si2173
  #define           Si2173_COMPATIBLE
  #define           Si2173_COMMAND_PROTOTYPES
  #include         "Si2173_L2_API.h"
#endif /* TER_TUNER_Si2173 */
#ifdef    TER_TUNER_Si2176
  #define           Si2176_COMPATIBLE
  #define           Si2176_COMMAND_PROTOTYPES
  #include         "Si2176_L2_API.h"
#endif /* TER_TUNER_Si2176 */
#ifdef    TER_TUNER_Si2177
  #define           Si2177_COMPATIBLE
  #define           Si2177_COMMAND_PROTOTYPES
  #include         "Si2177_L2_API.h"
#endif /* TER_TUNER_Si2177 */
#ifdef    TER_TUNER_Si2178
  #define           Si2178_COMPATIBLE
  #define           Si2178_COMMAND_PROTOTYPES
  #include         "Si2178_L2_API.h"
#endif /* TER_TUNER_Si2178 */
#ifdef    TER_TUNER_Si2178B
  #define           Si2178B_COMPATIBLE
  #define           Si2178B_COMMAND_PROTOTYPES
  #include         "Si2178B_L2_API.h"
#endif /* TER_TUNER_Si2178B */
#ifdef    TER_TUNER_Si2190
  #define           Si2190_COMPATIBLE
  #define           Si2190_COMMAND_PROTOTYPES
  #include         "Si2190_L2_API.h"
#endif /* TER_TUNER_Si2190 */
#ifdef    TER_TUNER_Si2190B
  #define           Si2190B_COMPATIBLE
  #define           Si2190B_COMMAND_PROTOTYPES
  #include         "Si2190B_L2_API.h"
#endif /* TER_TUNER_Si2190B */
#ifdef    TER_TUNER_Si2191
  #define           Si2191_COMPATIBLE
  #define           Si2191_COMMAND_PROTOTYPES
  #include         "Si2191_L2_API.h"
#endif /* TER_TUNER_Si2191 */
#ifdef    TER_TUNER_Si2191B
  #define           Si2191B_COMPATIBLE
  #define           Si2191B_COMMAND_PROTOTYPES
  #include         "Si2191B_L2_API.h"
#endif /* TER_TUNER_Si2191B */
#ifdef    TER_TUNER_Si2196
  #define           Si2196_COMPATIBLE
  #define           Si2196_COMMAND_PROTOTYPES
  #include         "Si2196_L2_API.h"
#endif /* TER_TUNER_Si2196 */

#define L1_RF_TER_TUNER_MODULATION_DVBC  3
#define L1_RF_TER_TUNER_MODULATION_DVBT  2
#define L1_RF_TER_TUNER_MODULATION_DVBT2 L1_RF_TER_TUNER_MODULATION_DVBT
#define L1_RF_TER_TUNER_MODULATION_ISDBT 4

typedef enum  _SILABS_BW {
    BW_6MHZ   =  6,
    BW_7MHZ   =  7,
    BW_8MHZ   =  8,
    BW_1P7MHZ =  9,
    BW_6P1MHZ = 10
} SILABS_BW;

typedef struct _SILABS_TER_TUNER_version_info {
  unsigned char   major;
  unsigned char   minor;
  unsigned char   build;
  unsigned char   chiprev;
} SILABS_TER_TUNER_version_info;

typedef struct _SILABS_TER_TUNER_Context      {
   signed   int ter_tuner_code;
   signed   int tuner_index;
   L0_Context *i2c;
#ifdef    TER_TUNER_CUSTOMTER
 #ifndef   CUSTOMTER_TUNER_COUNT
 #define   CUSTOMTER_TUNER_COUNT 1
 #endif /* CUSTOMTER_TUNER_COUNT */
 CUSTOMTER_Context *CUSTOMTER_Tuner[CUSTOMTER_TUNER_COUNT];
 CUSTOMTER_Context  CUSTOMTER_TunerObj[CUSTOMTER_TUNER_COUNT];
#endif /* TER_TUNER_CUSTOMTER  */
#ifdef    TER_TUNER_Si2124
 #ifndef   Si2124_TUNER_COUNT
 #define   Si2124_TUNER_COUNT 1
 #endif /* Si2124_TUNER_COUNT */
 L1_Si2124_Context *Si2124_Tuner[Si2124_TUNER_COUNT];
 L1_Si2124_Context  Si2124_TunerObj[Si2124_TUNER_COUNT];
#endif /* TER_TUNER_Si2124  */
#ifdef    TER_TUNER_Si2141
 #ifndef   Si2141_TUNER_COUNT
 #define   Si2141_TUNER_COUNT 1
 #endif /* Si2141_TUNER_COUNT */
 L1_Si2141_Context *Si2141_Tuner[Si2141_TUNER_COUNT];
 L1_Si2141_Context  Si2141_TunerObj[Si2141_TUNER_COUNT];
#endif /* TER_TUNER_Si2141  */
#ifdef    TER_TUNER_Si2144
 #ifndef   Si2144_TUNER_COUNT
 #define   Si2144_TUNER_COUNT 1
 #endif /* Si2144_TUNER_COUNT */
 L1_Si2144_Context *Si2144_Tuner[Si2144_TUNER_COUNT];
 L1_Si2144_Context  Si2144_TunerObj[Si2144_TUNER_COUNT];
#endif /* TER_TUNER_Si2144  */
#ifdef    TER_TUNER_Si2146
 #ifndef   Si2146_TUNER_COUNT
 #define   Si2146_TUNER_COUNT 1
 #endif /* Si2146_TUNER_COUNT */
 L1_Si2146_Context *Si2146_Tuner[Si2146_TUNER_COUNT];
 L1_Si2146_Context  Si2146_TunerObj[Si2146_TUNER_COUNT];
#endif /* TER_TUNER_Si2146  */
#ifdef    TER_TUNER_Si2147
 #ifndef   Si2147_TUNER_COUNT
 #define   Si2147_TUNER_COUNT 1
 #endif /* Si2147_TUNER_COUNT */
 L1_Si2147_Context *Si2147_Tuner[Si2147_TUNER_COUNT];
 L1_Si2147_Context  Si2147_TunerObj[Si2147_TUNER_COUNT];
#endif /* TER_TUNER_Si2147  */
#ifdef    TER_TUNER_Si2148
 #ifndef   Si2148_TUNER_COUNT
 #define   Si2148_TUNER_COUNT 1
 #endif /* Si2148_TUNER_COUNT */
 L1_Si2148_Context *Si2148_Tuner[Si2148_TUNER_COUNT];
 L1_Si2148_Context  Si2148_TunerObj[Si2148_TUNER_COUNT];
#endif /* TER_TUNER_Si2148  */
#ifdef    TER_TUNER_Si2148B
 #ifndef   Si2148B_TUNER_COUNT
 #define   Si2148B_TUNER_COUNT 1
 #endif /* Si2148B_TUNER_COUNT */
 L1_Si2148B_Context *Si2148B_Tuner[Si2148B_TUNER_COUNT];
 L1_Si2148B_Context  Si2148B_TunerObj[Si2148B_TUNER_COUNT];
#endif /* TER_TUNER_Si2148B  */
#ifdef    TER_TUNER_Si2151
 #ifndef   Si2151_TUNER_COUNT
 #define   Si2151_TUNER_COUNT 1
 #endif /* Si2151_TUNER_COUNT */
 L1_Si2151_Context *Si2151_Tuner[Si2151_TUNER_COUNT];
 L1_Si2151_Context  Si2151_TunerObj[Si2151_TUNER_COUNT];
#endif /* TER_TUNER_Si2151  */
#ifdef    TER_TUNER_Si2156
 #ifndef   Si2156_TUNER_COUNT
 #define   Si2156_TUNER_COUNT 1
 #endif /* Si2156_TUNER_COUNT */
 L1_Si2156_Context *Si2156_Tuner[Si2156_TUNER_COUNT];
 L1_Si2156_Context  Si2156_TunerObj[Si2156_TUNER_COUNT];
#endif /* TER_TUNER_Si2156  */
#ifdef    TER_TUNER_Si2157
 #ifndef   Si2157_TUNER_COUNT
 #define   Si2157_TUNER_COUNT 1
 #endif /* Si2157_TUNER_COUNT */
 L1_Si2157_Context *Si2157_Tuner[Si2157_TUNER_COUNT];
 L1_Si2157_Context  Si2157_TunerObj[Si2157_TUNER_COUNT];
#endif /* TER_TUNER_Si2157  */
#ifdef    TER_TUNER_Si2158
 #ifndef   Si2158_TUNER_COUNT
 #define   Si2158_TUNER_COUNT 1
 #endif /* Si2158_TUNER_COUNT */
 L1_Si2158_Context *Si2158_Tuner[Si2158_TUNER_COUNT];
 L1_Si2158_Context  Si2158_TunerObj[Si2158_TUNER_COUNT];
#endif /* TER_TUNER_Si2158  */
#ifdef    TER_TUNER_Si2158B
 #ifndef   Si2158B_TUNER_COUNT
 #define   Si2158B_TUNER_COUNT 1
 #endif /* Si2158B_TUNER_COUNT */
 L1_Si2158B_Context *Si2158B_Tuner[Si2158B_TUNER_COUNT];
 L1_Si2158B_Context  Si2158B_TunerObj[Si2158B_TUNER_COUNT];
#endif /* TER_TUNER_Si2158  */
#ifdef    TER_TUNER_Si2173
 #ifndef   Si2173_TUNER_COUNT
 #define   Si2173_TUNER_COUNT 1
 #endif /* Si2173_TUNER_COUNT */
 L1_Si2173_Context *Si2173_Tuner[Si2173_TUNER_COUNT];
 L1_Si2173_Context  Si2173_TunerObj[Si2173_TUNER_COUNT];
#endif /* TER_TUNER_Si2173  */
#ifdef    TER_TUNER_Si2176
 #ifndef   Si2176_TUNER_COUNT
 #define   Si2176_TUNER_COUNT 1
 #endif /* Si2176_TUNER_COUNT */
 L1_Si2176_Context *Si2176_Tuner[Si2176_TUNER_COUNT];
 L1_Si2176_Context  Si2176_TunerObj[Si2176_TUNER_COUNT];
#endif /* TER_TUNER_Si2176  */
#ifdef    TER_TUNER_Si2177
 #ifndef   Si2177_TUNER_COUNT
 #define   Si2177_TUNER_COUNT 1
 #endif /* Si2177_TUNER_COUNT */
 L1_Si2177_Context *Si2177_Tuner[Si2177_TUNER_COUNT];
 L1_Si2177_Context  Si2177_TunerObj[Si2177_TUNER_COUNT];
#endif /* TER_TUNER_Si2177  */
#ifdef    TER_TUNER_Si2178
 #ifndef   Si2178_TUNER_COUNT
 #define   Si2178_TUNER_COUNT 1
 #endif /* Si2178_TUNER_COUNT */
 L1_Si2178_Context *Si2178_Tuner[Si2178_TUNER_COUNT];
 L1_Si2178_Context  Si2178_TunerObj[Si2178_TUNER_COUNT];
#endif /* TER_TUNER_Si2178  */
#ifdef    TER_TUNER_Si2178B
 #ifndef   Si2178B_TUNER_COUNT
 #define   Si2178B_TUNER_COUNT 1
 #endif /* Si2178B_TUNER_COUNT */
 L1_Si2178B_Context *Si2178B_Tuner[Si2178B_TUNER_COUNT];
 L1_Si2178B_Context  Si2178B_TunerObj[Si2178B_TUNER_COUNT];
#endif /* TER_TUNER_Si2178B  */
#ifdef    TER_TUNER_Si2190
 #ifndef   Si2190_TUNER_COUNT
 #define   Si2190_TUNER_COUNT 1
 #endif /* Si2190_TUNER_COUNT */
 L1_Si2190_Context *Si2190_Tuner[Si2190_TUNER_COUNT];
 L1_Si2190_Context  Si2190_TunerObj[Si2190_TUNER_COUNT];
#endif /* TER_TUNER_Si2190  */
#ifdef    TER_TUNER_Si2190B
 #ifndef   Si2190B_TUNER_COUNT
 #define   Si2190B_TUNER_COUNT 1
 #endif /* Si2190B_TUNER_COUNT */
 L1_Si2190B_Context *Si2190B_Tuner[Si2190B_TUNER_COUNT];
 L1_Si2190B_Context  Si2190B_TunerObj[Si2190B_TUNER_COUNT];
#endif /* TER_TUNER_Si2190B  */
#ifdef    TER_TUNER_Si2191
 #ifndef   Si2191_TUNER_COUNT
 #define   Si2191_TUNER_COUNT 1
 #endif /* Si2191_TUNER_COUNT */
 L1_Si2191_Context *Si2191_Tuner[Si2191_TUNER_COUNT];
 L1_Si2191_Context  Si2191_TunerObj[Si2191_TUNER_COUNT];
#endif /* TER_TUNER_Si2191  */
#ifdef    TER_TUNER_Si2196
 #ifndef   Si2196_TUNER_COUNT
 #define   Si2196_TUNER_COUNT 1
 #endif /* Si2196_TUNER_COUNT */
 L1_Si2196_Context *Si2196_Tuner[Si2196_TUNER_COUNT];
 L1_Si2196_Context  Si2196_TunerObj[Si2196_TUNER_COUNT];
#endif /* TER_TUNER_Si2196  */
           signed   int    vco_code;
           signed   int    fef_level;
           signed   int    fef_freeze_pin;
  unsigned char   tc;
           char   rssi;
  unsigned long   freq;
  unsigned char   mode;
  SILABS_TER_TUNER_version_info part_info;
  SILABS_TER_TUNER_version_info get_rev;
  unsigned char   romid;
  unsigned char   part;
} SILABS_TER_TUNER_Context;

/* define how many front-ends will be used at project level. Otherwise, this piece of code will set it to 4, but it may not be as expected */
#ifndef   FRONT_END_COUNT
  #define FRONT_END_COUNT  4
#endif /* FRONT_END_COUNT */
extern signed   int TER_Tuner_count;
extern SILABS_TER_TUNER_Context *TER_tuners[FRONT_END_COUNT];

/* SiLabs TER Tuner API function prototypes */
signed   int   SiLabs_TER_Tuner_SW_Init              (SILABS_TER_TUNER_Context *silabs_tuner, signed   int add);
signed   int   SiLabs_TER_Tuner_Select_Tuner         (SILABS_TER_TUNER_Context *silabs_tuner, signed   int ter_tuner_code, signed   int tuner_index);
signed   int   SiLabs_TER_Tuner_Set_Address          (SILABS_TER_TUNER_Context *silabs_tuner, signed   int add);
signed   int   SiLabs_TER_Tuner_Store_FW             (SILABS_TER_TUNER_Context *silabs_tuner, firmware_struct fw_table[], signed   int nbLines);
signed   int   SiLabs_TER_Tuner_Broadcast_I2C        (SILABS_TER_TUNER_Context *silabs_tuners[], signed   int tuner_count);
signed   int   SiLabs_TER_Tuner_HW_Init              (SILABS_TER_TUNER_Context *silabs_tuner);
signed   int   SiLabs_TER_Tuner_Tuner_kickstart      (SILABS_TER_TUNER_Context *silabs_tuner);
signed   int   SiLabs_TER_Tuner_HW_Connect           (SILABS_TER_TUNER_Context *silabs_tuner, CONNECTION_TYPE connection_mode);
signed   int   SiLabs_TER_Tuner_bytes_trace          (SILABS_TER_TUNER_Context *silabs_tuner, unsigned char track_mode);
signed   int   SiLabs_TER_Tuner_Part_Info            (SILABS_TER_TUNER_Context *silabs_tuner);
signed   int   SiLabs_TER_Tuner_Get_Rev              (SILABS_TER_TUNER_Context *silabs_tuner);
signed   int   SiLabs_TER_Tuner_Wakeup               (SILABS_TER_TUNER_Context *silabs_tuner);
signed   int   SiLabs_TER_Tuner_PowerUp              (SILABS_TER_TUNER_Context *silabs_tuner, signed   int clock_mode, signed   int en_xout);
signed   int   SiLabs_TER_Tuner_Standby              (SILABS_TER_TUNER_Context *silabs_tuner);
signed   int   SiLabs_TER_Tuner_StandbyWithClk       (SILABS_TER_TUNER_Context *silabs_tuner);
signed   int   SiLabs_TER_Tuner_ClockConfig          (SILABS_TER_TUNER_Context *silabs_tuner, signed   int xtal, signed   int xout);
signed   int   SiLabs_TER_Tuner_ClockOff             (SILABS_TER_TUNER_Context *silabs_tuner);
signed   int   SiLabs_TER_Tuner_ClockOn              (SILABS_TER_TUNER_Context *silabs_tuner);
signed   int   SiLabs_TER_Tuner_PowerDown            (SILABS_TER_TUNER_Context *silabs_tuner);
signed   int   SiLabs_TER_Tuner_Possible_Tuners      (SILABS_TER_TUNER_Context *silabs_tuner, char* tunerList);
const    char *SiLabs_TER_Tuner_ERROR_TEXT           (SILABS_TER_TUNER_Context *silabs_tuner, unsigned char _error_code);
signed   int   SiLabs_TER_Tuner_ATVTune              (SILABS_TER_TUNER_Context *silabs_tuner, unsigned long freq, unsigned char video_sys, unsigned char trans, unsigned char color, unsigned char invert_signal);
signed   int   SiLabs_TER_Tuner_Fine_Tune            (SILABS_TER_TUNER_Context *silabs_tuner, unsigned char persistence, unsigned char apply_to_lif,signed   int offset_500hz);
signed   int   SiLabs_TER_Tuner_DTVTune              (SILABS_TER_TUNER_Context *silabs_tuner, unsigned long freq, unsigned char bw, unsigned char modulation);
signed   int   SiLabs_TER_Tuner_DTV_Bandwidth        (SILABS_TER_TUNER_Context *silabs_tuner, unsigned char bw);
signed   int   SiLabs_TER_Tuner_Block_VCO_Code       (SILABS_TER_TUNER_Context *silabs_tuner, signed   int vco_code);
signed   int   SiLabs_TER_Tuner_Block_VCO2_Code      (SILABS_TER_TUNER_Context *silabs_tuner, signed   int vco_code);
signed   int   SiLabs_TER_Tuner_Block_VCO3_Code      (SILABS_TER_TUNER_Context *silabs_tuner, signed   int vco_code);
signed   int   SiLabs_TER_Tuner_VCO_Blocking_PostTune(SILABS_TER_TUNER_Context *tuners[], signed   int tuner_num, signed   int tuner_count);
signed   int   SiLabs_TER_Tuner_Tone_Cancel          (SILABS_TER_TUNER_Context *silabs_tuner, unsigned   int div_a, unsigned   int div_b);
signed   int   SiLabs_TER_Tuner_Get_RF               (SILABS_TER_TUNER_Context *silabs_tuner);
signed   int   SiLabs_TER_Tuner_Status               (SILABS_TER_TUNER_Context *silabs_tuner);
signed   int   SiLabs_TER_Tuner_Text_STATUS          (SILABS_TER_TUNER_Context *silabs_tuner, char *separator, char *msg);
signed   int   SiLabs_TER_Tuner_ATV_Text_STATUS      (SILABS_TER_TUNER_Context *silabs_tuner, char *separator, char *msg);
signed   int   SiLabs_TER_Tuner_DTV_Text_STATUS      (SILABS_TER_TUNER_Context *silabs_tuner, char *separator, char *msg);
signed   int   SiLabs_TER_Tuner_DTV_AGC_SOURCE       (SILABS_TER_TUNER_Context *silabs_tuner, signed   int dtv_agc_source);
signed   int   SiLabs_TER_Tuner_DTV_FEF_SOURCE       (SILABS_TER_TUNER_Context *silabs_tuner, signed   int dtv_fef_source);
signed   int   SiLabs_TER_Tuner_ACTIVE_LOOP_THROUGH  (SILABS_TER_TUNER_Context *silabs_tuner, signed   int enable );
signed   int   SiLabs_TER_Tuner_DTV_OUT_TYPE         (SILABS_TER_TUNER_Context *silabs_tuner, signed   int dtv_out_type  );
signed   int   SiLabs_TER_Tuner_AGC_External         (SILABS_TER_TUNER_Context *silabs_tuner);
signed   int   SiLabs_TER_Tuner_DTV_LOInjection      (SILABS_TER_TUNER_Context *silabs_tuner);
signed   int   SiLabs_TER_Tuner_DTV_LIF_OUT          (SILABS_TER_TUNER_Context *silabs_tuner, signed   int amp, signed   int offset);
signed   int   SiLabs_TER_Tuner_DTV_LIF_OUT_amp      (SILABS_TER_TUNER_Context *silabs_tuner, unsigned   int amp_index);
signed   int   SiLabs_TER_Tuner_DTV_INTERNAL_ZIF_DVBT(SILABS_TER_TUNER_Context *silabs_tuner, unsigned   int zif_lif);
signed   int   SiLabs_TER_Tuner_ATV_LOInjection      (SILABS_TER_TUNER_Context *silabs_tuner);
signed   int   SiLabs_TER_Tuner_FEF_FREEZE_PIN_SETUP (SILABS_TER_TUNER_Context *silabs_tuner, signed   int fef_level);
signed   int   SiLabs_TER_Tuner_FEF_FREEZE_PIN       (SILABS_TER_TUNER_Context *silabs_tuner, signed   int fef);
signed   int   SiLabs_TER_Tuner_SLOW_INITIAL_AGC     (SILABS_TER_TUNER_Context *silabs_tuner, signed   int fef);
signed   int   SiLabs_TER_Tuner_SLOW_NORMAL_AGC_SETUP(SILABS_TER_TUNER_Context *silabs_tuner, signed   int fef);
signed   int   SiLabs_TER_Tuner_SLOW_NORMAL_AGC      (SILABS_TER_TUNER_Context *silabs_tuner, signed   int fef);
signed   int   SiLabs_TER_Tuner_DTV_AGC_AUTO_FREEZE  (SILABS_TER_TUNER_Context *silabs_tuner, signed   int fef);
signed   int   SiLabs_TER_Tuner_GPIOS                (SILABS_TER_TUNER_Context *silabs_tuner, signed   int gpio1_mode, signed   int gpio2_mode);
signed   int   SiLabs_LoadVideofilter                (SILABS_TER_TUNER_Context *silabs_tuner, vid_filt_struct vidFiltTable[], signed   int lines);
signed   int   SiLabs_ATV_Channel_Scan_M             (SILABS_TER_TUNER_Context *silabs_tuner, unsigned long rangeMinHz, unsigned long rangeMaxHz, signed   int minRSSIdBm, signed   int maxRSSIdBm, signed   int minSNRHalfdB, signed   int maxSNRHalfdB);
signed   int   SiLabs_ATV_Channel_Scan_PAL           (SILABS_TER_TUNER_Context *silabs_tuner, unsigned long rangeMinHz, unsigned long rangeMaxHz, signed   int minRSSIdBm, signed   int maxRSSIdBm, signed   int minSNRHalfdB, signed   int maxSNRHalfdB);
signed   int   SiLabs_AGC_Override                   (SILABS_TER_TUNER_Context *silabs_tuner, unsigned char mode );
signed   int   SiLabs_TER_Tuner_Set_Property         (SILABS_TER_TUNER_Context *silabs_tuner, unsigned int prop_code, int   data);
signed   int   SiLabs_TER_Tuner_Get_Property         (SILABS_TER_TUNER_Context *silabs_tuner, unsigned int prop_code, int  *data);
#ifdef    SILABS_API_TEST_PIPE
signed   int   SiLabs_TER_Tuner_Test                 (SILABS_TER_TUNER_Context *silabs_tuner, const char *target, const char *cmd, const char *sub_cmd, double dval, double *retdval, char **rettxt);
#endif /* SILABS_API_TEST_PIPE */

#define TER_TUNER_CONTEXT                    SILABS_TER_TUNER_Context

/* SiLabs TER Tuner API macros */
#define L1_RF_TER_TUNER_Init(ter_tuner, add)                            SiLabs_TER_Tuner_SW_Init(ter_tuner, add)
#define TER_TUNER_INIT(ter_tuner)                                       SiLabs_TER_Tuner_HW_Init(ter_tuner)
#define TER_TUNER_WAKEUP(ter_tuner)                                     SiLabs_TER_Tuner_Wakeup(ter_tuner)
#define TER_TUNER_STANDBY(ter_tuner)                                    SiLabs_TER_Tuner_Standby(ter_tuner)
#define TER_TUNER_STANDBY_WITH_CLOCK(ter_tuner)                         SiLabs_TER_Tuner_StandbyWithClk(ter_tuner)
#define TER_TUNER_CLOCK_OFF(ter_tuner)                                  SiLabs_TER_Tuner_ClockOff(ter_tuner)
#define TER_TUNER_CLOCK_ON(ter_tuner)                                   SiLabs_TER_Tuner_ClockOn(ter_tuner)
#define TER_TUNER_ERROR_TEXT(error_code)                                SiLabs_TER_Tuner_ERROR_TEXT(front_end->tuner_ter, error_code)
#define TER_TUNER_AGC_EXTERNAL(ter_tuner)                               SiLabs_TER_Tuner_AGC_External(ter_tuner)
#define TER_TUNER_DTV_LO_INJECTION(ter_tuner)                           SiLabs_TER_Tuner_DTV_LOInjection(ter_tuner);
#define TER_TUNER_DTV_LIF_OUT(ter_tuner,amp,offset)                     SiLabs_TER_Tuner_DTV_LIF_OUT(ter_tuner,amp,offset);
#define TER_TUNER_DTV_LIF_OUT_AMP(ter_tuner,amp_index)                  SiLabs_TER_Tuner_DTV_LIF_OUT_amp(ter_tuner,amp_index);
#define TER_TUNER_ATV_LO_INJECTION(ter_tuner)                           SiLabs_TER_Tuner_ATV_LOInjection(ter_tuner);
#define L1_RF_TER_TUNER_Get_RF(ter_tuner)                               SiLabs_TER_Tuner_Get_RF(ter_tuner)
#define L1_RF_TER_TUNER_Tune(ter_tuner,rf)                              SiLabs_TER_Tuner_DTVTune(ter_tuner, rf, bw, modulation);
#define L1_RF_TER_TUNER_FEF_MODE_FREEZE_PIN_SETUP(ter_tuner,fef_level)  SiLabs_TER_Tuner_FEF_FREEZE_PIN_SETUP(ter_tuner,fef_level);
#define L1_RF_TER_TUNER_FEF_MODE_FREEZE_PIN(ter_tuner,fef)              SiLabs_TER_Tuner_FEF_FREEZE_PIN(ter_tuner,fef);
#define L1_RF_TER_TUNER_FEF_MODE_SLOW_INITIAL_AGC_SETUP(ter_tuner,fef)  SiLabs_TER_Tuner_SLOW_INITIAL_AGC(ter_tuner,fef);
#define L1_RF_TER_TUNER_FEF_MODE_SLOW_NORMAL_AGC_SETUP(ter_tuner,fef)   SiLabs_TER_Tuner_SLOW_NORMAL_AGC_SETUP(ter_tuner,fef);
#define L1_RF_TER_TUNER_FEF_MODE_SLOW_NORMAL_AGC(ter_tuner,fef)         SiLabs_TER_Tuner_SLOW_NORMAL_AGC(ter_tuner,fef);
#define L1_RF_TER_TUNER_DTV_AGC_AUTO_FREEZE(ter_tuner,fef)              SiLabs_TER_Tuner_DTV_AGC_AUTO_FREEZE(ter_tuner,fef);

#endif /* _SiLabs_TER_Tuner_API_H_ */
