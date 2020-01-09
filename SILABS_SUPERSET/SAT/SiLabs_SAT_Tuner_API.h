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
#ifndef _SiLabs_SAT_Tuner_API_H_
#define _SiLabs_SAT_Tuner_API_H_

#define SILABS_SAT_TUNER_API
#define TUNER_ADDRESS_SAT            0x18

/* Checking Compilation flags to make sure at least one tuner is selected */
#ifdef    SAT_TUNER_SILABS
 #ifndef   SAT_TUNER_AV2012
  #ifndef   SAT_TUNER_AV2017
   #ifndef   SAT_TUNER_AV2018
    #ifndef   SAT_TUNER_CUSTOMSAT
     #ifndef   SAT_TUNER_MAX2112
      #ifndef   SAT_TUNER_NXP20142
       #ifndef   SAT_TUNER_RDA5812
        #ifndef   SAT_TUNER_RDA5815
         #ifndef   SAT_TUNER_RDA5815M
          #ifndef   SAT_TUNER_RDA5816S
           #ifndef   SAT_TUNER_RDA5816SD
   "If you get a compilation error on this line, it means that you compiled with 'SAT_TUNER_SILABS' without selecting the tuner(s) you want to use.";
   " Supported options: SAT_TUNER_AV2012 SAT_TUNER_AV2018 SAT_TUNER_CUSTOMSAT, SAT_TUNER_MAX2112, SAT_TUNER_NXP20142, SAT_TUNER_RDA5812, SAT_TUNER_RDA5815, SAT_TUNER_RDA5815M, SAT_TUNER_RDA5816S";
   " Please define at least one of these at project-level, in addition to SAT_TUNER_SILABS.";
   " If required, you may also define xxxx_TUNER_COUNT to use several tuners of the same type. (it defaults to '1' otherwise)";
           #endif /* SAT_TUNER_RDA5816SD */
          #endif /* SAT_TUNER_RDA5816S */
         #endif /* SAT_TUNER_RDA5815M */
        #endif /* SAT_TUNER_RDA5815 */
       #endif /* SAT_TUNER_RDA5812 */
      #endif /* SAT_TUNER_NXP20142 */
     #endif /* SAT_TUNER_MAX2112 */
    #endif /* SAT_TUNER_CUSTOMSAT */
   #endif /* SAT_TUNER_AV2018 */
  #endif /* SAT_TUNER_AV2017 */
 #endif /* SAT_TUNER_AV2012 */
#endif /* SAT_TUNER_SILABS */

#include "Silabs_L0_API.h"

/* Including header files for selected tuners */
#ifdef    SAT_TUNER_AV2012
  #include         "SiLabs_L1_RF_AV2012_API.h"
#endif /* SAT_TUNER_AV2012 */
#ifdef    SAT_TUNER_AV2017
  #include         "SiLabs_L1_RF_AV2017_API.h"
#endif /* SAT_TUNER_AV2017 */
#ifdef    SAT_TUNER_AV2018
  #include         "SiLabs_L1_RF_AV2018_API.h"
#endif /* SAT_TUNER_AV2018 */
#ifdef    SAT_TUNER_CUSTOMSAT
  #include         "SiLabs_L1_RF_CUSTOMSAT_API.h"
#endif /* SAT_TUNER_CUSTOMSAT */
#ifdef    SAT_TUNER_MAX2112
  #include         "SiLabs_L1_RF_MAX2112_API.h"
#endif /* SAT_TUNER_MAX2112 */
#ifdef    SAT_TUNER_NXP20142
  #include         "SiLabs_L1_RF_NXP20142_API.h"
#endif /* SAT_TUNER_NXP20142 */
#ifdef    SAT_TUNER_RDA5812
  #include         "SiLabs_L1_RF_RDA5812_API.h"
#endif /* SAT_TUNER_RDA5812 */
#ifdef    SAT_TUNER_RDA5815
  #include         "SiLabs_L1_RF_RDA5815_API.h"
#endif /* SAT_TUNER_RDA5815 */
#ifdef    SAT_TUNER_RDA5815M
  #include         "SiLabs_L1_RF_RDA5815M_API.h"
#endif /* SAT_TUNER_RDA5815M */
#ifdef    SAT_TUNER_RDA5816S
  #include         "SiLabs_L1_RF_RDA5816S_API.h"
#endif /* SAT_TUNER_RDA5816S */
#ifdef    SAT_TUNER_RDA5816SD
  #include         "SiLabs_L1_RF_RDA5816SD_API.h"
#endif /* SAT_TUNER_RDA5816SD */
#ifdef    SAT_TUNER_RDA16110E
  #include         "SiLabs_L1_RF_RDA16110E_API.h"
#endif /* SAT_TUNER_RDA16110E */

typedef struct SILABS_SAT_TUNER_Context      {
   int sat_tuner_code;
   int tuner_index;
   L0_Context *i2c;
#ifdef    SAT_TUNER_AV2012
 #ifndef   AV2012_TUNER_COUNT
 #define   AV2012_TUNER_COUNT 1
 #endif /* AV2012_TUNER_COUNT */
 AV2012_Context *AV2012_Tuner[AV2012_TUNER_COUNT];
 AV2012_Context  AV2012_TunerObj[AV2012_TUNER_COUNT];
#endif /* SAT_TUNER_AV2012  */
#ifdef    SAT_TUNER_AV2017
 #ifndef   AV2017_TUNER_COUNT
 #define   AV2017_TUNER_COUNT 1
 #endif /* AV2017_TUNER_COUNT */
 AV2017_Context *AV2017_Tuner[AV2017_TUNER_COUNT];
 AV2017_Context  AV2017_TunerObj[AV2017_TUNER_COUNT];
#endif /* SAT_TUNER_AV2017  */
#ifdef    SAT_TUNER_AV2018
 #ifndef   AV2018_TUNER_COUNT
 #define   AV2018_TUNER_COUNT 1
 #endif /* AV2018_TUNER_COUNT */
 AV2018_Context *AV2018_Tuner[AV2018_TUNER_COUNT];
 AV2018_Context  AV2018_TunerObj[AV2018_TUNER_COUNT];
#endif /* SAT_TUNER_AV2018  */
#ifdef    SAT_TUNER_CUSTOMSAT
 #ifndef   CUSTOMSAT_TUNER_COUNT
 #define   CUSTOMSAT_TUNER_COUNT 1
 #endif /* CUSTOMSAT_TUNER_COUNT */
 CUSTOMSAT_Context *CUSTOMSAT_Tuner[CUSTOMSAT_TUNER_COUNT];
 CUSTOMSAT_Context  CUSTOMSAT_TunerObj[CUSTOMSAT_TUNER_COUNT];
#endif /* SAT_TUNER_CUSTOMSAT  */
#ifdef    SAT_TUNER_MAX2112
 #ifndef   MAX2112_TUNER_COUNT
 #define   MAX2112_TUNER_COUNT 1
 #endif /* MAX2112_TUNER_COUNT */
 MAX2112_Context *MAX2112_Tuner[MAX2112_TUNER_COUNT];
 MAX2112_Context  MAX2112_TunerObj[MAX2112_TUNER_COUNT];
#endif /* SAT_TUNER_MAX2112  */
#ifdef    SAT_TUNER_NXP20142
 #ifndef   NXP20142_TUNER_COUNT
 #define   NXP20142_TUNER_COUNT 1
 #endif /* NXP20142_TUNER_COUNT */
 NXP20142_Context *NXP20142_Tuner[NXP20142_TUNER_COUNT];
 NXP20142_Context  NXP20142_TunerObj[NXP20142_TUNER_COUNT];
#endif /* SAT_TUNER_NXP20142  */
#ifdef    SAT_TUNER_RDA5812
 #ifndef   RDA5812_TUNER_COUNT
 #define   RDA5812_TUNER_COUNT 1
 #endif /* RDA5812_TUNER_COUNT */
 RDA5812_Context *RDA5812_Tuner[RDA5812_TUNER_COUNT];
 RDA5812_Context  RDA5812_TunerObj[RDA5812_TUNER_COUNT];
#endif /* SAT_TUNER_RDA5812  */
#ifdef    SAT_TUNER_RDA5815
 #ifndef   RDA5815_TUNER_COUNT
 #define   RDA5815_TUNER_COUNT 1
 #endif /* RDA5815_TUNER_COUNT */
 RDA5815_Context *RDA5815_Tuner[RDA5815_TUNER_COUNT];
 RDA5815_Context  RDA5815_TunerObj[RDA5815_TUNER_COUNT];
#endif /* SAT_TUNER_RDA5815  */
#ifdef    SAT_TUNER_RDA5815M
 #ifndef   RDA5815M_TUNER_COUNT
 #define   RDA5815M_TUNER_COUNT 1
 #endif /* RDA5815M_TUNER_COUNT */
 RDA5815M_Context *RDA5815M_Tuner[RDA5815M_TUNER_COUNT];
 RDA5815M_Context  RDA5815M_TunerObj[RDA5815M_TUNER_COUNT];
#endif /* SAT_TUNER_RDA5815M  */
#ifdef    SAT_TUNER_RDA5816S
 #ifndef   RDA5816S_TUNER_COUNT
 #define   RDA5816S_TUNER_COUNT 1
 #endif /* RDA5816S_TUNER_COUNT */
 RDA5816S_Context *RDA5816S_Tuner[RDA5816S_TUNER_COUNT];
 RDA5816S_Context  RDA5816S_TunerObj[RDA5816S_TUNER_COUNT];
#endif /* SAT_TUNER_RDA5816S  */
#ifdef    SAT_TUNER_RDA5816SD
 #ifndef   RDA5816SD_TUNER_COUNT
 #define   RDA5816SD_TUNER_COUNT 1
 #endif /* RDA5816SD_TUNER_COUNT */
 RDA5816SD_Context *RDA5816SD_Tuner[RDA5816SD_TUNER_COUNT];
 RDA5816SD_Context  RDA5816SD_TunerObj[RDA5816SD_TUNER_COUNT];
#endif /* SAT_TUNER_RDA5816SD  */
#ifdef    SAT_TUNER_RDA16110E
 #ifndef   RDA16110E_TUNER_COUNT
 #define   RDA16110E_TUNER_COUNT 1
 #endif /* RDA16110E_TUNER_COUNT */
 RDA16110E_Context *RDA16110E_Tuner[RDA16110E_TUNER_COUNT];
 RDA16110E_Context  RDA16110E_TunerObj[RDA16110E_TUNER_COUNT];
#endif /* SAT_TUNER_RDA16110E  */
  signed   char   rssi;
  unsigned long   RF;
  unsigned long   lpf_khz;
} SILABS_SAT_TUNER_Context;

/* SiLabs TER Tuner API function prototypes */
signed   int   SiLabs_SAT_Tuner_SW_Init        (SILABS_SAT_TUNER_Context *silabs_tuner, signed   int add);
signed   int   SiLabs_SAT_Tuner_Select_Tuner   (SILABS_SAT_TUNER_Context *silabs_tuner, signed   int sat_tuner_code, signed   int tuner_index);
signed   int   SiLabs_SAT_Tuner_Sub            (SILABS_SAT_TUNER_Context *silabs_tuner, signed   int sat_tuner_sub);
signed   int   SiLabs_SAT_Tuner_Set_Address    (SILABS_SAT_TUNER_Context *silabs_tuner, signed   int add);
signed   int   SiLabs_SAT_Tuner_HW_Init        (SILABS_SAT_TUNER_Context *silabs_tuner);
signed   int   SiLabs_SAT_Tuner_HW_Connect     (SILABS_SAT_TUNER_Context *silabs_tuner, CONNECTION_TYPE connection_mode);
signed   int   SiLabs_SAT_Tuner_bytes_trace    (SILABS_SAT_TUNER_Context *silabs_tuner, unsigned char track_mode);
signed   int   SiLabs_SAT_Tuner_Wakeup         (SILABS_SAT_TUNER_Context *silabs_tuner);
signed   int   SiLabs_SAT_Tuner_Standby        (SILABS_SAT_TUNER_Context *silabs_tuner);
signed   int   SiLabs_SAT_Tuner_StandbyWithClk (SILABS_SAT_TUNER_Context *silabs_tuner);
signed   int   SiLabs_SAT_Tuner_ClockOff       (SILABS_SAT_TUNER_Context *silabs_tuner);
signed   int   SiLabs_SAT_Tuner_ClockOn        (SILABS_SAT_TUNER_Context *silabs_tuner);
signed   int   SiLabs_SAT_Tuner_PowerDown      (SILABS_SAT_TUNER_Context *silabs_tuner);
signed   int   SiLabs_SAT_Tuner_Possible_Tuners(SILABS_SAT_TUNER_Context *silabs_tuner, char* tunerList);
char*          SiLabs_SAT_Tuner_ERROR_TEXT     (SILABS_SAT_TUNER_Context *silabs_tuner, unsigned char  error_code);
signed   int   SiLabs_SAT_Tuner_Tune           (SILABS_SAT_TUNER_Context *silabs_tuner, unsigned long freq_khz);
signed   int   SiLabs_SAT_Tuner_SelectRF       (SILABS_SAT_TUNER_Context *silabs_tuner, unsigned char rf_chn);
signed   int   SiLabs_SAT_Tuner_LPF            (SILABS_SAT_TUNER_Context *silabs_tuner, unsigned long lpf_khz);
signed   int   SiLabs_SAT_Tuner_LoopThrough    (SILABS_SAT_TUNER_Context *silabs_tuner, signed   int  loop_through_enabled);
signed   int   SiLabs_SAT_Tuner_Get_RF         (SILABS_SAT_TUNER_Context *silabs_tuner);
const    char* SiLabs_SAT_Tuner_Tag            (SILABS_SAT_TUNER_Context *silabs_tuner);
signed   int   SiLabs_SAT_Tuner_Status         (SILABS_SAT_TUNER_Context *silabs_tuner);
signed   int   SiLabs_SAT_Tuner_RSSI_From_AGC  (SILABS_SAT_TUNER_Context *silabs_tuner, signed   int agc);

#ifdef    SILABS_API_TEST_PIPE
int   SiLabs_SAT_Tuner_Test           (SILABS_SAT_TUNER_Context *silabs_tuner, const char *target, const char *cmd, const char *sub_cmd, double dval, double *retdval, char **rettxt);
#endif /* SILABS_API_TEST_PIPE */

#define SAT_TUNER_CONTEXT                    SILABS_SAT_TUNER_Context

/* SiLabs TER Tuner API macros */
#define L1_RF_SAT_TUNER_Init(sat_tuner, add)     SiLabs_SAT_Tuner_SW_Init(sat_tuner, add)
#define SAT_TUNER_INIT(sat_tuner)                SiLabs_SAT_Tuner_HW_Init(sat_tuner)
#define SAT_TUNER_WAKEUP(sat_tuner)              SiLabs_SAT_Tuner_Wakeup(sat_tuner)
#define SAT_TUNER_STANDBY(sat_tuner)             SiLabs_SAT_Tuner_Standby(sat_tuner)
#define SAT_TUNER_STANDBY_WITH_CLOCK(sat_tuner)  SiLabs_SAT_Tuner_StandbyWithClk(sat_tuner)
#define SAT_TUNER_CLOCK_OFF(sat_tuner)           SiLabs_SAT_Tuner_ClockOff(sat_tuner)
#define SAT_TUNER_CLOCK_ON(sat_tuner)            SiLabs_SAT_Tuner_ClockOn(sat_tuner)
#define L1_RF_SAT_TUNER_Get_RF(sat_tuner)        SiLabs_SAT_Tuner_Get_RF(sat_tuner)
#define L1_RF_SAT_TUNER_Tune(sat_tuner,rf)       SiLabs_SAT_Tuner_Tune(sat_tuner, rf);
#define L1_RF_SAT_TUNER_LPF(sat_tuner,lpf)       SiLabs_SAT_Tuner_LPF(sat_tuner, lpf)
#define SAT_TUNER_RSSI_FROM_IFAGC(sat_tuner,agc) SiLabs_SAT_Tuner_RSSI_From_AGC(sat_tuner, agc)
#endif /* _SiLabs_SAT_Tuner_API_H_ */




