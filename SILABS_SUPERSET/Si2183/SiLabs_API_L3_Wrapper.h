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
#ifndef  _SiLabs_API_L3_Wrapper_H_
#define  _SiLabs_API_L3_Wrapper_H_

/* Change log:

  As from V2.7.5:
   <new_feature>[ISDB-T/Monitoring] Adding TER_ISDBT_Monitoring_layer in SILABS_FE_Context.

  As from V2.7.3:
   <new_feature>[SAT/Unicable] Adding SiLabs_API_SAT_Unicable_Config to configure Unicable from L3
   <new_feature>[DVB-S2/roll_off] Adding roll_off in CUSTOM_Status_Struct

  As from V2.7.2:
    <new_part>[LNB/A8304] Adding compatibility with Allegro A8297 SAT LNB controller
      Since this part is a mixed dual where reading the control byte is not possible, specific pointers to
      the L3 front-ends are added, to enable matching the context bytes in the A8297 driver.
    <cleanup>[Status] Removing unused RFlevel and plp_type values from CUSTOM_Status_Struct

  As from V2.7.0:
    <improvement>[Status/ISDB-T]
      In CUSTOM_Constel_Enum:  Adding SILABS_DQPSK (for ISDB-T).

  As from V2.6.3:
   <improvement>[LINUX/ST_SDK2] Adding some structures to make porting more convenient:
    SiLabs_Lock_Struct
    SiLabs_Seek_Init_Struct
    SiLabs_Seek_Result_Struct
    SiLabs_Params_Struct

  As from V2.6.2:
   <improvement>[DVB-T2/FFT_mode_1k] Adding SILABS_FFT_MODE_1K in CUSTOM_FFT_Mode_Enum

  As from V2.5.8:
   <new_feature>[Broadcast_I2c/Multiples/Si2183]
     Adding SiLabs_API_Demods_Broadcast_I2C
     Adding SiLabs_API_Broadcast_I2C
     Adding 'filtering' to SiLabs_API_Get_AC_DATA
   <new_feature>[DVB-C2/status]
      Adding DVB-C2 system information values in CUSTOM_Status_Struct (c2_system_id, c2_start_freq_hz, c2_system_bw_hz, num_data_slice)

  As from V2.5.3:
   <new_feature>[Cypress/TS_SLAVE] Adding   SILABS_TS_SLAVE_FIFO = 5, in CUSTOM_TS_Mode_Enum;
   <new_part>[LNB/A8302] Adding SAT_Select_LNB_Chip_lnb_index in SILABS_FE_Context, to store the index.
      This flag indicates which part in a dual LNB controller is in use.

  As from V2.5.0:
   <new_feature> Adding ts_mux_input in SILABS_FE_Context struct to associate a mux input to each front end.
   <new feature>[TER_Tuner/Config]
     adding SiLabs_API_TER_Tuner_Block_VCO2 and SiLabs_API_TER_Tuner_Block_VCO3 to allow configuration of
     the TER_Tuner block_VCO2_code and block_VCO3_code
   <new_feature>[CONFIG/tracing] Adding all configuration fields in SILABS_FE_Context (to enable configuration checking after init).

  As from V2.4.7:
  <compatibility/Tizen> SILABS_QAMAUTO: replacing '-1' by '100. This is because Tizen uses 'unsigned char' when 'char foo;' is defined.
    All other OSs use 'signed char' by default and have no issue with this.

  As from V2.4.0:
  <new_feature>[TS_Crossbar/Duals] Adding TS Crossbar capability via SiLabs_API_L3_TS_Crossbar.c/.h
        This is only valid for dual demodulators with the TS crossbar feature.

  As from V2.3.9:
  <new_part> Adding ISDB-T values in CUSTOM_Status_Struct (isdbt_system_id, nb_seg_a, nb_seg_b, nb_seg_c)

  As from V2.3.7:
  <new_feature> [DVB-S2X] Adding Constellation and code rate enums for DVB-S2X.
  <new_feature> [ISDB-T]  Adding support for ISDB-T.

  As from V2.3.6:
  <new_feature> [no_float] Adding c_n_100, ber_mant, ber_exp, per_mant, per_exp, fer_mant, fer_exp in status structure,
                           These are used when the application is not allowed to use floats
  <cleanup>     [NO_SAT/NO_TER] Removing NO_SAT and NO_TER compilation flags

  As from V2.1.9:
   Compatibility with 'generic' TER_TUNER_SILABS API, for easier integration of future SiLabs tuners

  As from V2.1.2:
   Adding SiLabs_API_SSI_SQI prototype

  As from V2.0.9:
   Removing commas on last lines of type declarations, to avoid some ISO-C compiler warnings

 *************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef   SILABS_SUPERSET
/* <porting> Project customization: chips selection                                                    */
/* At project level, define the DEMOD_Si21xx value corresponding to the required digital demodulator   */
#ifdef    DEMOD_Si2164
  #define       Si2164_COMPATIBLE
  #define       DEMOD_DVB_T
  #define       DEMOD_DVB_T2
  #define       DEMOD_DVB_C
  #define       DEMOD_DVB_C2
  #define       DEMOD_DVB_S_S2_DSS
#endif /* DEMOD_Si2164 */
#ifdef    DEMOD_Si2165
  #define       Si2165_COMPATIBLE
  #define       DEMOD_DVB_T
  #define       DEMOD_DVB_C
#endif /* DEMOD_Si2165 */
#ifdef    DEMOD_Si2167
  #define       Si2167_COMPATIBLE
  #define       DEMOD_DVB_T
  #define       DEMOD_DVB_C
  #define       DEMOD_DVB_S_S2_DSS
#endif /* DEMOD_Si2167 */
#ifdef    DEMOD_Si2167B
  #define       Si2167B_COMPATIBLE
  #define       DEMOD_DVB_T
  #define       DEMOD_DVB_C
  #define       DEMOD_DVB_S_S2_DSS
#endif /* DEMOD_Si2167B */
#ifdef    DEMOD_Si2169
  #define       Si2169_COMPATIBLE
  #define       DEMOD_DVB_T
  #define       DEMOD_DVB_T2
  #define       DEMOD_DVB_C
#ifndef   NO_SAT
  #define       DEMOD_DVB_S_S2_DSS
#endif /* NO_SAT */
#endif /* DEMOD_Si2169 */
#ifdef    DEMOD_Si2183
  #define       Si2183_COMPATIBLE
  #define       DEMOD_DVB_T
  #define       DEMOD_DVB_T2
  #define       DEMOD_ISDB_T
  #define       DEMOD_DVB_C
  #define       DEMOD_DVB_C2
  #define       DEMOD_MCNS
  #define       DEMOD_DVB_S_S2_DSS
#endif /* DEMOD_Si2183 */
#ifdef    DEMOD_Si2185
  #define       Si2185_COMPATIBLE
  #define       DEMOD_DVB_T
  #define       DEMOD_DVB_C
  #define       TER_TUNER_Si2185
  #define       Si2185_COMMAND_PROTOTYPES
#endif /* DEMOD_Si2185 */
#endif /* SILABS_SUPERSET */
#ifdef    SILABS_SUPERSET
 #define DEMOD_Si2183
 #define Si2183_COMPATIBLE
#endif /* SILABS_SUPERSET */

#ifdef    DEMOD_DVB_T
 #ifndef   TERRESTRIAL_FRONT_END
  #define   TERRESTRIAL_FRONT_END
 #endif /* TERRESTRIAL_FRONT_END */
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_DVB_C
 #ifndef   TERRESTRIAL_FRONT_END
  #define   TERRESTRIAL_FRONT_END
 #endif /* TERRESTRIAL_FRONT_END */
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_S_S2_DSS
 #ifndef   SATELLITE_FRONT_END
  #define   SATELLITE_FRONT_END
 #endif /* SATELLITE_FRONT_END */
#endif /* DEMOD_DVB_S_S2_DSS */

#ifdef    TERRESTRIAL_FRONT_END
 /* At project level, define the TER_TUNER_Si21xx value corresponding to the required terrestrial tuner */
#ifdef    TER_TUNER_CUSTOMTER
  #define           CUSTOMTER_COMPATIBLE
  #include         "SiLabs_L1_RF_CUSTOMTER_API.h"
#endif /* TER_TUNER_CUSTOMTER */

#ifdef    TER_TUNER_SILABS
  #include         "SiLabs_TER_Tuner_API.h"
#else  /* TER_TUNER_SILABS */
  #ifdef    TER_TUNER_Si2146
    #define           Si2146_COMPATIBLE
    #define           Si2146_COMMAND_PROTOTYPES
    #include         "Si2146_L2_API.h"
  #endif /* TER_TUNER_Si2146 */

  #ifdef    TER_TUNER_Si2148
    #define           Si2148_COMPATIBLE
    #define           Si2148_COMMAND_PROTOTYPES
    #include         "Si2148_L2_API.h"
  #endif /* TER_TUNER_Si2148 */

  #ifdef    TER_TUNER_Si2156
    #define           Si2156_COMPATIBLE
    #define           Si2156_COMMAND_PROTOTYPES
    #include         "Si2156_L2_API.h"
  #endif /* TER_TUNER_Si2156 */

  #ifdef    TER_TUNER_Si2158
    #define           Si2158_COMPATIBLE
    #define           Si2158_COMMAND_PROTOTYPES
    #include         "Si2158_L2_API.h"
  #endif /* TER_TUNER_Si2158 */

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

  #ifdef    TER_TUNER_Si2178
    #define           Si2178_COMPATIBLE
    #define           Si2178_COMMAND_PROTOTYPES
    #include         "Si2178_L2_API.h"
  #endif /* TER_TUNER_Si2178 */

  #ifdef    TER_TUNER_Si2191
    #define           Si2191_COMPATIBLE
    #define           Si2191_COMMAND_PROTOTYPES
    #include         "Si2191_L2_API.h"
  #endif /* TER_TUNER_Si2191 */

  #ifdef    TER_TUNER_Si2190
    #define           Si2190_COMPATIBLE
    #define           Si2190_COMMAND_PROTOTYPES
    #include         "Si2190_L2_API.h"
  #endif /* TER_TUNER_Si2190 */

  #ifdef    TER_TUNER_Si2196
    #define           Si2196_COMPATIBLE
    #define           Si2196_COMMAND_PROTOTYPES
    #include         "Si2196_L2_API.h"
  #endif /* TER_TUNER_Si2196 */
#endif /* TER_TUNER_SILABS */

#endif /* TERRESTRIAL_FRONT_END */

/* Loading the digital demodulator API based on the project-level selection */
#ifdef      Si2183_COMPATIBLE
  #include "Si2183_L2_API.h"
#endif   /* Si2183_COMPATIBLE */

#ifndef   SILABS_SUPERSET

#ifndef   DEMOD_Si2164
 #ifndef   DEMOD_Si2165
  #ifndef   DEMOD_Si2167
   #ifndef   DEMOD_Si2167B
    #ifndef   DEMOD_Si2169
     #ifndef   DEMOD_Si2183
      #ifndef   DEMOD_Si2185
     "If you get a compilation error on this line, it means that no digital demod has been selected. Please define at least one of DEMOD_Si2164, DEMOD_Si2165, DEMOD_Si2167, DEMOD_Si2167B, DEMOD_Si2169, DEMOD_Si2183, DEMOD_Si2185 at project level!";
      #endif /* DEMOD_Si2185 */
     #endif /* DEMOD_Si2183 */
    #endif /* DEMOD_Si2169 */
   #endif /* DEMOD_Si2167B */
  #endif /* DEMOD_Si2167 */
 #endif /* DEMOD_Si2165 */
#endif /* DEMOD_Si2164 */
#endif /* SILABS_SUPERSET */

#ifdef    TERRESTRIAL_FRONT_END
#ifndef   TER_TUNER_CUSTOMTER
 #ifndef   TER_TUNER_DTT759x
  #ifndef   TER_TUNER_SILABS
   #ifndef   TER_TUNER_Si2146
    #ifndef   TER_TUNER_Si2148
     #ifndef   TER_TUNER_Si2156
      #ifndef   TER_TUNER_Si2158
       #ifndef   TER_TUNER_Si2173
        #ifndef   TER_TUNER_Si2176
         #ifndef   TER_TUNER_Si2178
          #ifndef   TER_TUNER_Si2185
           #ifndef   TER_TUNER_Si2190
            #ifndef   TER_TUNER_Si2191
             #ifndef   TER_TUNER_Si2196
              #ifndef   TER_TUNER_NO_TER
     "If you get a compilation error on this line, it means that no terrestrial tuner has been selected. Please define TER_TUNER_Sixxxx at project-level!";
              #endif /* TER_TUNER_NO_TER */
             #endif /* TER_TUNER_Si2196 */
            #endif /* TER_TUNER_Si2191 */
           #endif /* TER_TUNER_Si2190 */
          #endif /* TER_TUNER_Si2185 */
         #endif /* TER_TUNER_Si2178 */
        #endif /* TER_TUNER_Si2176 */
       #endif /* TER_TUNER_Si2173 */
      #endif /* TER_TUNER_Si2158 */
     #endif /* TER_TUNER_Si2156 */
    #endif /* TER_TUNER_Si2148 */
   #endif /* TER_TUNER_Si2146 */
  #endif /* TER_TUNER_SILABS */
 #endif /* TER_TUNER_DTT759x */
#endif /* TER_TUNER_CUSTOMTER*/
#endif /* TERRESTRIAL_FRONT_END */

#ifdef    SATELLITE_FRONT_END
#ifndef   NO_SAT
#ifndef   SAT_TUNER_CUSTOMSAT
 #ifndef   SAT_TUNER_AV2012
  #ifndef   SAT_TUNER_AV2018
   #ifndef   SAT_TUNER_NXP20142
    #ifndef   SAT_TUNER_MAX2112
     #ifndef   SAT_TUNER_RDA5812
      #ifndef   SAT_TUNER_RDA5815
       #ifndef   SAT_TUNER_RDA5816S
     "If you get a compilation error on this line, it means that no satellite tuner has been selected. Please define SAT_TUNER_xxxx at project-level!";
       #endif /* SAT_TUNER_RDA5816S */
      #endif /* SAT_TUNER_RDA5815  */
     #endif /* SAT_TUNER_RDA5812  */
    #endif /* SAT_TUNER_MAX2112  */
   #endif /* SAT_TUNER_NXP20142 */
  #endif /* SAT_TUNER_AV2018   */
 #endif /* SAT_TUNER_AV2012   */
#endif /* SAT_TUNER_CUSTOMSAT*/
#endif /* NO_SAT */
 #ifdef    LNBH21_COMPATIBLE
  #include "LNBH21_L1_API.h"
 #endif /* LNBH21_COMPATIBLE */
 #ifdef    LNBH25_COMPATIBLE
  #include "LNBH25_L1_API.h"
 #endif /* LNBH25_COMPATIBLE */
 #ifdef    LNBH26_COMPATIBLE
  #include "LNBH26_L1_API.h"
 #endif /* LNBH26_COMPATIBLE */
 #ifdef    LNBH29_COMPATIBLE
  #include "LNBH29_L1_API.h"
 #endif /* LNBH29_COMPATIBLE */
 #ifdef    A8293_COMPATIBLE
  #include "A8293_L1_API.h"
 #endif /* A8293_COMPATIBLE */
 #ifdef    A8297_COMPATIBLE
  #include "A8297_L1_API.h"
 #endif /* A8297_COMPATIBLE */
 #ifdef    A8302_COMPATIBLE
  #include "A8302_L1_API.h"
 #endif /* A8302_COMPATIBLE */
 #ifdef    A8304_COMPATIBLE
  #include "A8304_L1_API.h"
 #endif /* A8304_COMPATIBLE */
 #ifdef    TPS65233_COMPATIBLE
  #include "TPS65233_L1_API.h"
 #endif /* TPS65233_COMPATIBLE */
#ifdef    UNICABLE_COMPATIBLE
  #include "SiLabs_Unicable_API.h"
extern  unsigned char                lnb_type;
extern  SILABS_Unicable_Context      Unicable_Obj;
extern  SILABS_Unicable_Context     *unicable;
#endif /* UNICABLE_COMPATIBLE */
#endif /* SATELLITE_FRONT_END */
typedef enum  _STATUS_SELECTION {
  FE_LOCK_STATE     = 0x01, /* demod_lock, fec_lock,  uncorrs, TS_bitrate_kHz, TS_clock_kHz  */
  FE_LEVELS         = 0x02, /* RSSI, RFagc, IFagc                                            */
  FE_RATES          = 0x04, /* BER, PER, FER (depending on standard)                         */
  FE_SPECIFIC       = 0x08, /* symbol_rate, stream, constellation, c/n, freq_offset,
                                 timing_offset, code_rate, t2_version, num_plp, plp_id
                                 ds_id, cell_id, etc. (generally one command per standard)   */
  FE_QUALITY        = 0x10, /* SSI, SQI                                                      */
  FE_FREQ           = 0x20, /* freq                                                          */
} STATUS_SELECTION;

/* Standard code values used by the top-level application               */
/* <porting> set these values to match the top-level application values */
typedef enum   CUSTOM_Standard_Enum          {
  SILABS_ANALOG = 4,
  SILABS_DVB_T  = 0,
  SILABS_DVB_C  = 1,
  SILABS_DVB_S  = 2,
  SILABS_DVB_S2 = 3,
  SILABS_DVB_T2 = 5,
  SILABS_DSS    = 6,
  SILABS_MCNS   = 7,
  SILABS_DVB_C2 = 8,
  SILABS_ISDB_T = 9,
  SILABS_SLEEP  = 100,
  SILABS_OFF    = 200
} CUSTOM_Standard_Enum;

typedef enum   CUSTOM_Constel_Enum           {
  SILABS_QAMAUTO  = 100,
  SILABS_QAM16    =  0,
  SILABS_QAM32    =  1,
  SILABS_QAM64    =  2,
  SILABS_QAM128   =  3,
  SILABS_QAM256   =  4,
  SILABS_QPSK     =  5,
  SILABS_8PSK     =  6,
  SILABS_QAM1024  =  7,
  SILABS_QAM4096  =  8,
  SILABS_8APSK_L  = 10,
  SILABS_16APSK   = 11,
  SILABS_16APSK_L = 12,
  SILABS_32APSK_1 = 13,
  SILABS_32APSK_2 = 14,
  SILABS_32APSK_L = 15,
  SILABS_DQPSK    = 16
} CUSTOM_Constel_Enum;

typedef enum   CUSTOM_Stream_Enum            {
  SILABS_HP = 0,
  SILABS_LP = 1
} CUSTOM_Stream_Enum;

typedef enum   CUSTOM_T2_PLP_TYPE            {
  SILABS_PLP_TYPE_COMMON     = 0,
  SILABS_PLP_TYPE_DATA_TYPE1 = 1,
  SILABS_PLP_TYPE_DATA_TYPE2 = 2
} CUSTOM_T2_PLP_TYPE;

typedef enum   CUSTOM_TS_Mode_Enum           {
  SILABS_TS_TRISTATE = 0,
  SILABS_TS_SERIAL   = 1,
  SILABS_TS_PARALLEL = 2,
  SILABS_TS_GPIF     = 3,
  SILABS_TS_OFF      = 4,
  SILABS_TS_SLAVE_FIFO = 5,
  SILABS_TS_STREAMING  = 6,
} CUSTOM_TS_Mode_Enum;

typedef enum   CUSTOM_FFT_Mode_Enum          {
  SILABS_FFT_MODE_2K  = 0,
  SILABS_FFT_MODE_4K  = 1,
  SILABS_FFT_MODE_8K  = 2,
  SILABS_FFT_MODE_16K = 3,
  SILABS_FFT_MODE_32K = 4,
  SILABS_FFT_MODE_1K  = 5
} CUSTOM_FFT_Mode_Enum;

typedef enum   CUSTOM_GI_Enum                {
  SILABS_GUARD_INTERVAL_1_32    = 0,
  SILABS_GUARD_INTERVAL_1_16    = 1,
  SILABS_GUARD_INTERVAL_1_8     = 2,
  SILABS_GUARD_INTERVAL_1_4     = 3,
  SILABS_GUARD_INTERVAL_1_128   = 4,
  SILABS_GUARD_INTERVAL_19_128  = 5,
  SILABS_GUARD_INTERVAL_19_256  = 6,
  SILABS_GUARD_INTERVAL_1_64    = 7
} CUSTOM_GI_Enum;

typedef enum   CUSTOM_Coderate_Enum          {
  SILABS_CODERATE_1_2   =  0,
  SILABS_CODERATE_2_3   =  1,
  SILABS_CODERATE_3_4   =  2,
  SILABS_CODERATE_4_5   =  3,
  SILABS_CODERATE_5_6   =  4,
  SILABS_CODERATE_7_8   =  5,
  SILABS_CODERATE_8_9   =  6,
  SILABS_CODERATE_9_10  =  7,
  SILABS_CODERATE_1_3   =  8,
  SILABS_CODERATE_1_4   =  9,
  SILABS_CODERATE_2_5   = 10,
  SILABS_CODERATE_3_5   = 11,
  SILABS_CODERATE_5_9   = 12,
  SILABS_CODERATE_7_9   = 13,
  SILABS_CODERATE_8_15  = 14,
  SILABS_CODERATE_11_15 = 15,
  SILABS_CODERATE_13_18 = 16,
  SILABS_CODERATE_9_20  = 17,
  SILABS_CODERATE_11_20 = 18,
  SILABS_CODERATE_23_36 = 19,
  SILABS_CODERATE_25_36 = 20,
  SILABS_CODERATE_13_45 = 21,
  SILABS_CODERATE_26_45 = 22,
  SILABS_CODERATE_28_45 = 23,
  SILABS_CODERATE_32_45 = 24,
  SILABS_CODERATE_77_90 = 25
} CUSTOM_Coderate_Enum;

typedef enum   CUSTOM_Polarization_Enum      {
  SILABS_POLARIZATION_HORIZONTAL  = 0,
  SILABS_POLARIZATION_VERTICAL,
  SILABS_POLARIZATION_DO_NOT_CHANGE
} CUSTOM_Polarization_Enum;

typedef enum   CUSTOM_Band_Enum              {
  SILABS_BAND_LOW  = 0,
  SILABS_BAND_HIGH,
  SILABS_BAND_DO_NOT_CHANGE
} CUSTOM_Band_Enum;

typedef enum   CUSTOM_Hierarchy_Enum         {
  SILABS_HIERARCHY_NONE  = 0,
  SILABS_HIERARCHY_ALFA1 = 1,
  SILABS_HIERARCHY_ALFA2 = 2,
  SILABS_HIERARCHY_ALFA4 = 3
} CUSTOM_Hierarchy_Enum;

typedef enum   CUSTOM_Video_Sys_Enum         {
  SILABS_VIDEO_SYS_B  = 0,
  SILABS_VIDEO_SYS_GH = 1,
  SILABS_VIDEO_SYS_M  = 2,
  SILABS_VIDEO_SYS_N  = 3,
  SILABS_VIDEO_SYS_I  = 4,
  SILABS_VIDEO_SYS_DK = 5,
  SILABS_VIDEO_SYS_L  = 6,
  SILABS_VIDEO_SYS_LP = 7
} CUSTOM_Video_Sys_Enum;

typedef enum   CUSTOM_Transmission_Mode_Enum {
  SILABS_TRANSMISSION_MODE_TERRESTRIAL = 0,
  SILABS_TRANSMISSION_MODE_CABLE       = 1
} CUSTOM_Transmission_Mode_Enum;

typedef enum   CUSTOM_Pilot_Pattern_Enum     {
  SILABS_PILOT_PATTERN_PP1 = 1,
  SILABS_PILOT_PATTERN_PP2 = 2,
  SILABS_PILOT_PATTERN_PP3 = 3,
  SILABS_PILOT_PATTERN_PP4 = 4,
  SILABS_PILOT_PATTERN_PP5 = 5,
  SILABS_PILOT_PATTERN_PP6 = 6,
  SILABS_PILOT_PATTERN_PP7 = 7,
  SILABS_PILOT_PATTERN_PP8 = 8
} CUSTOM_Pilot_Pattern_Enum;

typedef enum   CUSTOM_Pilot_T2_version_Enum  {
  SILABS_T2_VERSION_1_1_1 = 111,
  SILABS_T2_VERSION_1_2_1 = 121,
  SILABS_T2_VERSION_1_3_1 = 131
} CUSTOM_Pilot_T2_version_Enum;

typedef enum   CUSTOM_Color_Enum             {
  SILABS_COLOR_PAL_NTSC  = 0,
  SILABS_COLOR_SECAM     = 1
} CUSTOM_Color_Enum;

typedef enum   CUSTOM_Audio_Sys_Enum         {
  SILABS_AUDIO_SYS_DEFAULT         = 0,
  SILABS_AUDIO_SYS_MONO            = 1,
  SILABS_AUDIO_SYS_MONO_NICAM      = 2,
  SILABS_AUDIO_SYS_A2              = 3,
  SILABS_AUDIO_SYS_A2_DK2          = 4,
  SILABS_AUDIO_SYS_A2_DK3          = 5,
  SILABS_AUDIO_SYS_BTSC            = 6,
  SILABS_AUDIO_SYS_EIAJ            = 7,
  SILABS_AUDIO_SYS_SCAN            = 8,
  SILABS_AUDIO_SYS_A2_DK4          = 9,
  SILABS_AUDIO_SYS_WIDE_SCAN       = 10,
  SILABS_AUDIO_SYS_MONO_NICAM_6DB  = 11,
  SILABS_AUDIO_SYS_MONO_NICAM_10DB = 12
} CUSTOM_Audio_Sys_Enum;

typedef enum   CUSTOM_TS_Mux_Input           {
  SILABS_TS_MUX_A                  = 0x08,
  SILABS_TS_MUX_B                  = 0x04,
  SILABS_TS_MUX_TRISTATE           = 0x0C
} CUSTOM_TS_Mux_Input;

typedef struct _SILABS_TER_TUNER_Config      {
  unsigned char nSel_dtv_out_type;
  unsigned char nSel_dtv_agc_source;
  signed   int  nSel_dtv_lif_freq_offset;
  unsigned char nSel_dtv_mode_bw;
  unsigned char nSel_dtv_mode_invert_spectrum;
  unsigned char nSel_dtv_mode_modulation;
  unsigned char nSel_atv_video_mode_video_sys;
  unsigned char nSel_atv_audio_mode_audio_sys;
  unsigned char nSel_atv_atv_video_mode_tran;
  unsigned char nSel_atv_video_mod_color;
  unsigned char nSel_atv_mode_invert_spectrum;
  unsigned char nSel_atv_mode_invert_signal;
  char          nSel_atv_cvbs_out_fine_amp;
  char          nSel_atv_cvbs_out_fine_offset;
  unsigned char nSel_atv_sif_out_amp;
  unsigned char nSel_atv_sif_out_offset;
  unsigned char if_agc_speed;
  char          nSel_dtv_rf_top;
  char          nSel_atv_rf_top;
  unsigned long nLocked_Freq;
  unsigned long nCenter_Freq;
  signed   int  nCriteriaStep;
  signed   int  nLeftMax;
  signed   int  nRightMax;
  signed   int  nReal_Step;
  signed   int  nBeforeStep;
} SILABS_TER_TUNER_Config;

typedef struct _SILABS_SAT_TUNER_Config       {
    int    RF;
    int    IF;
    int    minRF;
    int    maxRF;
    double xtal;
    double LPF;
    int    tunerBytesCount;
    int    I2CMuxChannel;
    double RefDiv_value;
    int    Mash_Per;
    CONNECTION_TYPE connType;
    unsigned char tuner_log[40];
    unsigned char tuner_read[7];
    char          nSel_att_top;
} SILABS_SAT_TUNER_Config;

typedef struct _SILABS_CARRIER_Config         {
  signed   int       freq;
  signed   int       bandwidth;
  signed   int       stream;
  signed   int       symbol_rate;
  signed   int       constellation;
  signed   int       polarization;
  signed   int       band;
} SILABS_CARRIER_Config;

typedef struct _SILABS_ANALOG_CARRIER_Config  {
  unsigned char      video_sys;
  unsigned char      trans;
  unsigned char      color;
  unsigned char      invert_signal;
  unsigned char      invert_spectrum;
} SILABS_ANALOG_CARRIER_Config;

typedef struct _SILABS_ANALOG_SIF_Config      {
  unsigned char      stereo_sys;
} SILABS_ANALOG_SIF_Config;

typedef struct _SILABS_FE_Context             {
  unsigned int       chip;
  unsigned int       tuner_ter;
  unsigned int       tuner_sat;
  char               tag[SILABS_TAG_SIZE];
  unsigned char      fe_index;
  CUSTOM_TS_Mode_Enum  active_TS_mode;
  CUSTOM_TS_Mux_Input ts_mux_input;
#ifdef    Si2183_COMPATIBLE
  Si2183_L2_Context *Si2183_FE;
  Si2183_L2_Context  Si2183_FE_Obj;
#endif /* Si2183_COMPATIBLE */
  signed   int       standard;
  signed   int       init_ok;
  signed   int       polarization;
  signed   int       band;
  SILABS_TER_TUNER_Config      TER_Tuner_Cfg;
  SILABS_SAT_TUNER_Config      SAT_Tuner_Cfg;
  SILABS_CARRIER_Config        Carrier_Cfg;
  SILABS_ANALOG_CARRIER_Config Analog_Cfg;
  SILABS_ANALOG_SIF_Config     Analog_Sif_Cfg;
  signed   int       TER_tuner_I2C_connection;
  signed   int       SAT_tuner_I2C_connection;
  signed   int       I2C_connected;
  unsigned int       config_code;
#ifdef    SATELLITE_FRONT_END
  signed   int       lnb_chip;
  signed   int       lnb_chip_address;
  signed   int       lnb_chip_init_done;
 #ifdef    LNBH21_COMPATIBLE
  LNBH21_Context               lnbh21_Obj;
  LNBH21_Context              *lnbh21;
 #endif /* LNBH21_COMPATIBLE */
 #ifdef    LNBH25_COMPATIBLE
  LNBH25_Context               lnbh25_Obj;
  LNBH25_Context              *lnbh25;
 #endif /* LNBH25_COMPATIBLE */
 #ifdef    LNBH26_COMPATIBLE
  LNBH26_Context               lnbh26_Obj;
  LNBH26_Context              *lnbh26;
 #endif /* LNBH26_COMPATIBLE */
 #ifdef    LNBH29_COMPATIBLE
  LNBH29_Context               lnbh29_Obj;
  LNBH29_Context              *lnbh29;
 #endif /* LNBH29_COMPATIBLE */
 #ifdef    A8293_COMPATIBLE
  A8293_Context               A8293_Obj;
  A8293_Context              *A8293;
 #endif /* A8293_COMPATIBLE */
 #ifdef    A8297_COMPATIBLE
  A8297_Context               A8297_Obj;
  A8297_Context              *A8297;
 #endif /* A8297_COMPATIBLE */
 #ifdef    A8302_COMPATIBLE
  A8302_Context               A8302_Obj;
  A8302_Context              *A8302;
 #endif /* A8302_COMPATIBLE */
 #ifdef    A8304_COMPATIBLE
  A8304_Context               A8304_Obj;
  A8304_Context              *A8304;
 #endif /* A8304_COMPATIBLE */
 #ifdef    TPS65233_COMPATIBLE
  TPS65233_Context               TPS65233_Obj;
  TPS65233_Context              *TPS65233;
 #endif /* TPS65233_COMPATIBLE */
 #ifdef    UNICABLE_COMPATIBLE
  unsigned char                lnb_type;
  SILABS_Unicable_Context      Unicable_Obj;
  SILABS_Unicable_Context     *unicable;
  signed   int                 swap_detection_done;
 #endif /* UNICABLE_COMPATIBLE */
#endif /* SATELLITE_FRONT_END */
  /* Configuration fields storage */
  signed   int  demod_add;
  unsigned int  SPI_Setup_send_option;
  unsigned int  SPI_Setup_clk_pin;
  unsigned int  SPI_Setup_clk_pola;
  unsigned int  SPI_Setup_data_pin;
  unsigned int  SPI_Setup_data_order;
  signed   int  Select_TER_Tuner_ter_tuner_code;
  signed   int  Select_TER_Tuner_ter_tuner_index;
  signed   int  TER_Address_add;
  signed   int  TER_Tuner_ClockConfig_xtal;
  signed   int  TER_Tuner_ClockConfig_xout;
  signed   int  TER_Clock_clock_source;
  signed   int  TER_Clock_clock_input;
  signed   int  TER_Clock_clock_freq;
  signed   int  TER_Clock_clock_control;
  signed   int  TER_FEF_Config_fef_mode;
  signed   int  TER_FEF_Config_fef_pin;
  signed   int  TER_FEF_Config_fef_level;
  signed   int  TER_AGC_agc1_mode;
  signed   int  TER_AGC_agc1_inversion;
  signed   int  TER_AGC_agc2_mode;
  signed   int  TER_AGC_agc2_inversion;
  signed   int  TER_RSSI_offset;
  signed   int  TER_Tuner_AGC_Input_dtv_agc_source;
  signed   int  TER_Tuner_FEF_Input_dtv_fef_freeze_input;
  signed   int  TER_Tuner_IF_Output_dtv_out_type;
  signed   int  TER_ISDBT_Monitoring_mode;
  signed   int  TER_ISDBT_Monitoring_layer;
  signed   int  Select_SAT_Tuner_sat_tuner_code;
  signed   int  Select_SAT_Tuner_sat_tuner_index;
  signed   int  Select_SAT_Tuner_sat_tuner_sub;
  signed   int  SAT_Address_add;
  signed   int  SAT_Clock_clock_source;
  signed   int  SAT_Clock_clock_input;
  signed   int  SAT_Clock_clock_freq;
  signed   int  SAT_Clock_clock_control;
  signed   int  SAT_AGC_agc1_mode;
  signed   int  SAT_AGC_agc1_inversion;
  signed   int  SAT_AGC_agc2_mode;
  signed   int  SAT_AGC_agc2_inversion;
  signed   int  SAT_RSSI_offset;
  signed   int  SAT_Spectrum_spectrum_inversion;
  signed   int  SAT_Select_LNB_Chip_lnb_code;
  signed   int  SAT_Select_LNB_Chip_lnb_index;
  signed   int  SAT_Select_LNB_Chip_lnb_chip_address;
  unsigned char PRBS[10];
} SILABS_FE_Context;

typedef struct _CUSTOM_Status_Struct          {
/* TODO (mdorval#1#): Add cber in status structure */
  CUSTOM_Standard_Enum standard;
  signed   int  clock_mode;
  signed   int  demod_lock;
  signed   int  fec_lock;
  signed   int  fec_lock_in_range;
  signed   int  demod_die;
  signed   int  ber_window;
  signed   int  ber_count;
#ifndef   NO_FLOATS_ALLOWED
  double        c_n;
  double        ber;
  double        per;
  double        fer;
#endif /* NO_FLOATS_ALLOWED */
  signed   int  c_n_100;
  signed   int  ber_mant;
  signed   int  ber_exp;
  signed   int  per_mant;
  signed   int  per_exp;
  signed   int  fer_mant;
  signed   int  fer_exp;
  signed   int  uncorrs;
  signed   int  RFagc;
  signed   int  IFagc;
  long          freq_offset;
  long          timing_offset;
  signed   int  bandwidth_Hz;
  signed   int  stream;
  signed   int  fft_mode;
  signed   int  guard_interval;
  signed   int  constellation;
  unsigned int  symbol_rate;

  signed   int  roll_off;
  signed   int  code_rate_hp;
  signed   int  code_rate_lp;
  signed   int  hierarchy;
  signed   int  spectral_inversion;
  signed   int  code_rate;
  signed   int  pilots;
  signed   int  cell_id;
  signed long int RSSI;
  signed   int  SSI;
  signed   int  SQI;
  signed   int  tuner_lock;
  signed   int  rotated;
  signed   int  pilot_pattern;
  signed   int  bw_ext;
  signed   int  TS_bitrate_kHz;
  signed   int  TS_clock_kHz;
  /*        T2 specifics (FEF) */
  signed   int  fef_length;
  signed   int  t2_system_id;
  signed   int  t2_base_lite;
  signed   int  t2_version;
  /* End of T2 specifics (FEF) */
  /* Start of ISDB-T specifics   */
  signed   int  isdbt_system_id;
  signed   int  nb_seg_a;
  signed   int  nb_seg_b;
  signed   int  nb_seg_c;
  signed   int  fec_lock_a;
  signed   int  fec_lock_b;
  signed   int  fec_lock_c;
  signed   int  partial_flag;
  signed   int  emergency_flag;
  signed   int  constellation_a;
  signed   int  constellation_b;
  signed   int  constellation_c;
  signed   int  code_rate_a;
  signed   int  code_rate_b;
  signed   int  code_rate_c;
  signed   int  uncorrs_a;
  signed   int  uncorrs_b;
  signed   int  uncorrs_c;
  signed   int  il_a;
  signed   int  il_b;
  signed   int  il_c;
  signed   int  ber_window_a;
  signed   int  ber_window_b;
  signed   int  ber_window_c;
  signed   int  ber_count_a;
  signed   int  ber_count_b;
  signed   int  ber_count_c;
#ifndef   NO_FLOATS_ALLOWED
  double        ber_a;
  double        ber_b;
  double        ber_c;
#endif /* NO_FLOATS_ALLOWED */
  /* End of ISDB-T specifics   */
  /*        T2/C2 specifics (PLP) */
  signed   int  c2_system_id;
  signed   int  c2_start_freq_hz;
  signed   int  c2_system_bw_hz;
  signed   int  num_data_slice;
  signed   int  num_plp;
  signed   int  plp_id;
  signed   int  ds_id;
  signed   int  plp_payload_type;
  /* End of T2/C2 specifics (PLP) */
  /*        S2X   specifics (ISI) */
  signed   int  num_is;
  signed   int  isi_id;
  signed   int  isi_constellation;
  signed   int  isi_code_rate;
  unsigned int  s2x;
  unsigned char ccm_vcm;
  unsigned char sis_mis;
  /* End of S2X   specifics (ISI) */
  signed   int  tx_mode;
  signed   int  short_frame;
  unsigned char attctrl;
  /* TUNER_STATUS */
  unsigned char tcint;
  unsigned char rssilint;
  unsigned char rssihint;
  signed   int  vco_code;
  unsigned char tc;
  unsigned char rssil;
  unsigned char rssih;
  signed   char rssi;
  unsigned long freq;
  unsigned char mode;
  /* ATV_STATUS & DTV_STATUS */
  unsigned char chl;
  /* ATV_STATUS */
  signed   int  ATV_Sync_Lock;
  signed   int  ATV_Master_Lock;
  unsigned char audio_chan_filt_bw;
  unsigned char snrl;
  unsigned char snrh;
  unsigned char video_snr;
  signed   int  afc_freq;
  signed   int  video_sc_spacing;
  unsigned char video_sys;
  unsigned char color;
  unsigned char trans;
  unsigned char audio_sys;
  unsigned char audio_demod_mode;
  /* DTV_STATUS */
  unsigned char chlint;
  unsigned char bw;
  unsigned char modulation;
  unsigned char fef;
  /* MCNS STATUS */
  unsigned char interleaving;
} CUSTOM_Status_Struct;

typedef struct _SiLabs_Lock_Struct            {
  int                  res;
  int                  freq;
  int                  bandwidth_Hz;
  unsigned int         symbol_rate_bps;
  CUSTOM_Constel_Enum  constellation;
  CUSTOM_Stream_Enum   stream;
  int                  standard;
  int                  polarization;
  int                  band;
  int                  data_slice_id;
  int                  plp_id;
  int                  T2_lock_mode;
} SiLabs_Lock_Struct;

typedef struct _SiLabs_Seek_Init_Struct       {
  signed   int  rangeMin;
  signed   int  rangeMax;
  signed   int  seekBWHz;
  signed   int  seekStepHz;
  signed   int  minSRbps;
  signed   int  maxSRbps;
  signed   int  minRSSIdBm;
  signed   int  maxRSSIdBm;
  signed   int  minSNRHalfdB;
  signed   int  maxSNRHalfdB;
} SiLabs_Seek_Init_Struct;

typedef struct _SiLabs_Seek_Result_Struct     {
  signed   int *standard;
  signed   int *freq;
  signed   int *bandwidth_Hz;
  signed   int *stream;
  unsigned int *symbol_rate_bps;
  signed   int *constellation;
  signed   int *polarization;
  signed   int *band;
  signed   int *num_data_slice;
  signed   int *num_plp;
  signed   int *T2_base_lite;
} SiLabs_Seek_Result_Struct;

typedef struct _SiLabs_Params_Struct     {
  SILABS_FE_Context         *front_end;
  SiLabs_Lock_Struct        *lock_to;
  SiLabs_Seek_Init_Struct   *seek_init;
  SiLabs_Seek_Result_Struct *seek_res;
  CUSTOM_Status_Struct      *status;
} SiLabs_Params_Struct;

/* define how many front-ends will be used */
#ifndef   FRONT_END_COUNT
  #define FRONT_END_COUNT  4
#endif /* FRONT_END_COUNT */
extern SILABS_FE_Context     FrontEnd_Table[FRONT_END_COUNT];
//extern SILABS_FE_Context    *front_end;
extern CUSTOM_Status_Struct  FE_Status;
extern CUSTOM_Status_Struct *custom_status;

#ifdef    SATELLITE_FRONT_END
#ifdef    A8297_COMPATIBLE
extern SILABS_FE_Context *A8297_FE_0;
extern SILABS_FE_Context *A8297_FE_1;
#endif /* A8297_COMPATIBLE */
#endif /* SATELLITE_FRONT_END */

#ifdef    TS_CROSSBAR
 #include "SiLabs_API_L3_Wrapper_TS_Crossbar.h"
#endif /* TS_CROSSBAR */

#ifdef    CHANNEL_BONDING
 #include "SiLabs_API_L3_Wrapper_Channel_Bonding.h"
#endif /* CHANNEL_BONDING */

/* Translation functions from 'Custom' values to 'SiLabs' values */

signed   int  Silabs_standardCode                   (SILABS_FE_Context *front_end,    signed   int                  standard);
signed   int  Silabs_constelCode                    (SILABS_FE_Context *front_end,    CUSTOM_Constel_Enum           constel);
signed   int  Silabs_streamCode                     (SILABS_FE_Context *front_end,    CUSTOM_Stream_Enum            stream);
signed   int  Silabs_plptypeCode                    (SILABS_FE_Context *front_end,    CUSTOM_T2_PLP_TYPE            plp_type);
signed   int  Silabs_fftCode                        (SILABS_FE_Context *front_end,    CUSTOM_FFT_Mode_Enum          fft);
signed   int  Silabs_giCode                         (SILABS_FE_Context *front_end,    CUSTOM_GI_Enum                gi);
signed   int  Silabs_coderateCode                   (SILABS_FE_Context *front_end,    signed   int                  coderate);
signed   int  Silabs_hierarchyCode                  (SILABS_FE_Context *front_end,    CUSTOM_Hierarchy_Enum         hierarchy);
signed   int  Silabs_pilotPatternCode               (SILABS_FE_Context *front_end,    CUSTOM_Pilot_Pattern_Enum     pilot_pattern);
signed   int  Silabs_T2VersionCode                  (SILABS_FE_Context* front_end,    CUSTOM_Pilot_T2_version_Enum  t2_version);
signed   int  Silabs_videoSysCode                   (SILABS_FE_Context *front_end,    CUSTOM_Video_Sys_Enum         video_sys);
signed   int  Silabs_colorCode                      (SILABS_FE_Context *front_end,    CUSTOM_Color_Enum             color);
signed   int  Silabs_transmissionCode               (SILABS_FE_Context *front_end,    CUSTOM_Transmission_Mode_Enum trans);

/* Translation functions from 'SiLabs' values to 'Custom' values */

signed   int  Custom_standardCode                   (SILABS_FE_Context *front_end,    signed   int  standard);
signed   int  Custom_constelCode                    (SILABS_FE_Context *front_end,    signed   int  constel);
signed   int  Custom_streamCode                     (SILABS_FE_Context *front_end,    signed   int  stream);
signed   int  Custom_plptypeCode                    (SILABS_FE_Context *front_end,    signed   int  plp_type);
signed   int  Custom_fftCode                        (SILABS_FE_Context *front_end,    signed   int  fft);
signed   int  Custom_giCode                         (SILABS_FE_Context *front_end,    signed   int  gi);
signed   int  Custom_coderateCode                   (SILABS_FE_Context *front_end,    signed   int  coderate);
signed   int  Custom_hierarchyCode                  (SILABS_FE_Context *front_end,    signed   int  hierarchy);
signed   int  Custom_pilotPatternCode               (SILABS_FE_Context *front_end,    signed   int  pilot_pattern);
signed   int  Custom_T2VersionCode                  (SILABS_FE_Context *front_end,    signed   int  t2_version);

/* Text functions returning strings based on 'Custom' values. */

char*         Silabs_Standard_Text                  (signed   int             standard);
signed   int  Silabs_Standard_Capability            (signed   int             standard);
char*         Silabs_Constel_Text                   (CUSTOM_Constel_Enum      constel);
char*         Silabs_Stream_Text                    (CUSTOM_Stream_Enum       stream);
char*         Silabs_TS_Mode_Text                   (CUSTOM_TS_Mode_Enum      ts_mode);
char*         Silabs_PLPType_Text                   (CUSTOM_T2_PLP_TYPE       plp_type);
char*         Silabs_FFT_Text                       (CUSTOM_FFT_Mode_Enum     fft);
char*         Silabs_GI_Text                        (CUSTOM_GI_Enum           gi);
char*         Silabs_Coderate_Text                  (CUSTOM_Coderate_Enum     coderate);
char*         Silabs_Polarization_Text              (CUSTOM_Polarization_Enum polarization);
char*         Silabs_Band_Text                      (CUSTOM_Band_Enum         band);
char*         Silabs_Extended_BW_Text               (signed   int  bw_extended);
char*         Silabs_Rotated_QAM_Text               (signed   int  rotated);
char*         Silabs_T2_Base_Lite_Text              (signed   int  t2_base_lite);
char*         Silabs_FEF_Text                       (signed   int  fef);
char*         Silabs_MISO_Text                      (signed   int  siso_miso);
char*         Silabs_Pilot_Pattern_Text             (CUSTOM_Pilot_Pattern_Enum pilot_pattern);
char*         Silabs_T2_Version_Text                (CUSTOM_Pilot_T2_version_Enum t2_version);
char*         Silabs_No_Short_Frame_Text            (signed   int  no_short_frame);
char*         Silabs_Pilots_Text                    (signed   int  pilots);

/* Chip detection function (To Be Defined) */

signed   int  SiLabs_chip_detect                    (signed   int  demodAdd);

/* Internal functions                      */

signed   int  SiLabs_API_Demod_status               (SILABS_FE_Context *front_end,    CUSTOM_Status_Struct *status);
signed   int  SiLabs_API_Demod_status_selection     (SILABS_FE_Context *front_end,    CUSTOM_Status_Struct *status, unsigned char status_selection);
signed   int  SiLabs_API_TER_Tuner_status           (SILABS_FE_Context *front_end,    CUSTOM_Status_Struct *status);
signed   int  SiLabs_API_TER_Tuner_Loop_Through     (SILABS_FE_Context* front_end,    signed   int enable);
signed   int  SiLabs_API_SAT_Tuner_status           (SILABS_FE_Context *front_end,    CUSTOM_Status_Struct *status);
signed   int  SiLabs_API_FE_status                  (SILABS_FE_Context *front_end,    CUSTOM_Status_Struct *status);
signed   int  SiLabs_API_FE_status_selection        (SILABS_FE_Context *front_end,    CUSTOM_Status_Struct *status, unsigned char status_selection);
signed   int  SiLabs_API_Text_status                (SILABS_FE_Context *front_end,    CUSTOM_Status_Struct *status, char *formatted_status);
signed   int  SiLabs_API_Text_status_selection      (SILABS_FE_Context *front_end,    CUSTOM_Status_Struct *status, char *formatted_status, unsigned char status_selection);

/*****************************************************************************************/
/*               SiLabs demodulator API functions (demod and tuner)                      */
/*****************************************************************************************/
/* Main SW init function (to be called first)                                            */
signed   char SiLabs_API_SW_Init                    (SILABS_FE_Context *front_end,    signed   int  demodAdd, signed   int  tunerAdd_Ter, signed   int  tunerAdd_Sat);
signed   int  SiLabs_API_Set_Index_and_Tag          (SILABS_FE_Context *front_end,    unsigned char index, const char* tag);
signed   int  SiLabs_API_Frontend_Chip              (SILABS_FE_Context *front_end,    signed   int  demod_id);
signed   int  SiLabs_API_Handshake_Setup            (SILABS_FE_Context *front_end,    signed   int  handshake_mode, signed   int  handshake_period_ms);
signed   int  SiLabs_API_SPI_Setup                  (SILABS_FE_Context *front_end,    unsigned int  send_option, unsigned int  clk_pin, unsigned int  clk_pola, unsigned int  data_pin, unsigned int  data_order);
signed   int  SiLabs_API_Demods_Broadcast_I2C       (SILABS_FE_Context *front_ends[], signed   int  front_end_count);
signed   int  SiLabs_API_Broadcast_I2C              (SILABS_FE_Context *front_ends[], signed   int  front_end_count);
signed   int  SiLabs_API_XTAL_Capacitance           (SILABS_FE_Context *front_end,    signed   int xtal_capacitance);
/* TER tuner selection and configuration functions (to be used after SiLabs_API_SW_Init) */
signed   int  SiLabs_API_TER_Possible_Tuners        (SILABS_FE_Context *front_end,    char *tunerList);
signed   int  SiLabs_API_Select_TER_Tuner           (SILABS_FE_Context *front_end,    signed   int  ter_tuner_code, signed   int  ter_tuner_index);
void*         SiLabs_API_TER_Tuner                  (SILABS_FE_Context *front_end);
signed   int  SiLabs_API_TER_tuner_I2C_connection   (SILABS_FE_Context *front_end,    signed   int  fe_index);
signed   int  SiLabs_API_TER_Address                (SILABS_FE_Context *front_end,    signed   int  add);
signed   int  SiLabs_API_TER_Broadcast_I2C          (SILABS_FE_Context *front_ends[], signed   int  front_end_count);
signed   int  SiLabs_API_TER_Tuner_ClockConfig      (SILABS_FE_Context *front_end,    signed   int  xtal, signed   int  xout);
signed   int  SiLabs_API_TER_Clock_Options          (SILABS_FE_Context *front_end,    char *clockOptions);
signed   int  SiLabs_API_TER_Clock                  (SILABS_FE_Context *front_end,    signed   int  clock_source, signed   int  clock_input, signed   int  clock_freq, signed   int  clock_control);
signed   int  SiLabs_API_TER_FEF_Options            (SILABS_FE_Context *front_end,    char* fefOptions);
signed   int  SiLabs_API_TER_FEF_Config             (SILABS_FE_Context *front_end,    signed   int  fef_mode, signed   int  fef_pin, signed   int  fef_level);
signed   int  SiLabs_API_TER_AGC_Options            (SILABS_FE_Context *front_end,    char *agcOptions);
signed   int  SiLabs_API_TER_AGC                    (SILABS_FE_Context *front_end,    signed   int  agc1_mode,    signed   int  agc1_inversion, signed   int  agc2_mode, signed   int  agc2_inversion);
signed   int  SiLabs_API_TER_Tuner_AGC_Input        (SILABS_FE_Context *front_end,    signed   int  dtv_agc_source);
signed   int  SiLabs_API_TER_Tuner_GPIOs            (SILABS_FE_Context *front_end,    signed   int  gpio1_mode, signed   int gpio2_mode);
signed   int  SiLabs_API_TER_Tuner_FEF_Input        (SILABS_FE_Context *front_end,    signed   int  dtv_fef_freeze_input);
signed   int  SiLabs_API_TER_Tuner_IF_Output        (SILABS_FE_Context *front_end,    signed   int  dtv_out_type);
/* SAT tuner selection and configuration functions (to be used after SiLabs_API_SW_Init) */
signed   int  SiLabs_API_SAT_Possible_Tuners        (SILABS_FE_Context *front_end,    char *tunerList);
signed   int  SiLabs_API_Select_SAT_Tuner           (SILABS_FE_Context *front_end,    signed   int  sat_tuner_code, signed   int  sat_tuner_index);
signed   int  SiLabs_API_SAT_Tuner_Sub              (SILABS_FE_Context *front_end,    signed   int  sat_tuner_sub);
signed   int  SiLabs_API_SAT_tuner_I2C_connection   (SILABS_FE_Context *front_end,    signed   int  fe_index);
signed   int  SiLabs_API_SAT_Address                (SILABS_FE_Context *front_end,    signed   int  add);
signed   int  SiLabs_API_SAT_Clock_Options          (SILABS_FE_Context *front_end,    char *clockOptions);
signed   int  SiLabs_API_SAT_Clock                  (SILABS_FE_Context *front_end,    signed   int  clock_source, signed   int  clock_input, signed   int  clock_freq, signed   int  clock_control);
signed   int  SiLabs_API_SAT_AGC_Options            (SILABS_FE_Context *front_end,    char *agcOptions);
signed   int  SiLabs_API_SAT_AGC                    (SILABS_FE_Context *front_end,    signed   int  agc1_mode,    signed   int  agc1_inversion, signed   int  agc2_mode, signed   int  agc2_inversion);
signed   int  SiLabs_API_SAT_Spectrum               (SILABS_FE_Context *front_end,    signed   int  spectrum_inversion);
signed   int  SiLabs_API_SAT_Possible_LNB_Chips     (SILABS_FE_Context *front_end,    char *lnbList);
signed   int  SiLabs_API_SAT_Select_LNB_Chip        (SILABS_FE_Context *front_end,    signed   int  lnb_code, signed   int  lnb_chip_address);
signed   int  SiLabs_API_SAT_LNB_Chip_Index         (SILABS_FE_Context *front_end,    signed   int  lnb_index);

/* Front_end info, control and status functions                                          */
signed   int  SiLabs_API_Infos                      (SILABS_FE_Context *front_end,    char *infoString);
signed   int  SiLabs_API_Config_Infos               (SILABS_FE_Context *front_end,    char* config_function, char *infoString);
signed   char SiLabs_API_HW_Connect                 (SILABS_FE_Context *front_end,    CONNECTION_TYPE connection_mode);
signed   char SiLabs_API_bytes_trace                (SILABS_FE_Context *front_end,    unsigned char track_mode);
signed   int  SiLabs_API_ReadString                 (SILABS_FE_Context *front_end,    char *readString, unsigned char *pbtDataBuffer);
signed   char SiLabs_API_WriteString                (SILABS_FE_Context *front_end,    char *writeString);
signed   int  SiLabs_API_communication_check        (SILABS_FE_Context *front_end);
signed   int  SiLabs_API_switch_to_standard         (SILABS_FE_Context *front_end,    signed   int  standard, unsigned char force_full_init);
signed   int  SiLabs_API_set_standard               (SILABS_FE_Context *front_end,    signed   int  standard);
signed   int  SiLabs_API_lock_to_carrier            (SILABS_FE_Context *front_end,
                                           signed   int  standard,
                                           signed   int  freq,
                                           signed   int  bandwidth_Hz,
                                           unsigned int  stream,
                                           unsigned int  symbol_rate_bps,
                                           unsigned int  constellation,
                                           unsigned int  polarization,
                                           unsigned int  band,
                                           signed   int  data_slice_id,
                                           signed   int  plp_id,
                                           unsigned int  T2_lock_mode
                                           );
signed   int  SiLabs_API_Tune                       (SILABS_FE_Context *front_end,    signed   int  freq);
signed   int  SiLabs_API_Channel_Lock_Abort         (SILABS_FE_Context *front_end);
signed   int  SiLabs_API_Demod_Standby              (SILABS_FE_Context *front_end);
signed   int  SiLabs_API_Demod_Silent               (SILABS_FE_Context *front_end,    signed   int silent);
signed   int  SiLabs_API_Demod_ClockOn              (SILABS_FE_Context *front_end);
signed   int  SiLabs_API_Reset_Uncorrs              (SILABS_FE_Context *front_end);
signed   int  SiLabs_API_TS_Strength_Shape          (SILABS_FE_Context *front_end,    signed   int serial_strength, signed   int serial_shape, signed   int parallel_strength, signed   int parallel_shape);
signed   int  SiLabs_API_TS_Config                  (SILABS_FE_Context *front_end,    signed   int clock_config, signed   int gapped, signed   int serial_clk_inv, signed   int parallel_clk_inv, signed   int ts_err_inv, signed   int serial_pin);
signed   int  SiLabs_API_TS_Mode                    (SILABS_FE_Context *front_end,    unsigned int  ts_mode);
signed   int  SiLabs_API_Get_TS_Dividers            (SILABS_FE_Context *front_end,    unsigned int *div_a, unsigned int *div_b);
signed   int  Silabs_API_TS_Tone_Cancel             (SILABS_FE_Context* front_end,    signed   int  on_off);
signed   int  SiLabs_API_Tuner_I2C_Enable           (SILABS_FE_Context *front_end);
signed   int  SiLabs_API_Tuner_I2C_Disable          (SILABS_FE_Context *front_end);
/* Scan functions                                                                        */
signed   int  SiLabs_API_Channel_Seek_Init          (SILABS_FE_Context *front_end,
                                            signed   int  rangeMin,     signed   int  rangeMax,
                                            signed   int  seekBWHz,     signed   int  seekStepHz,
                                            signed   int  minSRbps,     signed   int  maxSRbps,
                                            signed   int  minRSSIdBm,   signed   int  maxRSSIdBm,
                                            signed   int  minSNRHalfdB, signed   int  maxSNRHalfdB);
signed   int  SiLabs_API_Channel_Seek_Next          (SILABS_FE_Context *front_end,    signed   int *standard, signed   int *freq, signed   int *bandwidth_Hz, signed   int *stream, unsigned int *symbol_rate_bps, signed   int *constellation, signed   int *polarization, signed   int *band, signed   int *num_data_slice, signed   int *num_plp, signed   int *T2_base_lite);
signed   int  SiLabs_API_Channel_Seek_Abort         (SILABS_FE_Context *front_end);
signed   int  SiLabs_API_Channel_Seek_End           (SILABS_FE_Context *front_end);
#ifdef    SATELLITE_FRONT_END
signed   int  SiLabs_API_SAT_AutoDetectCheck        (SILABS_FE_Context *front_end);
signed   int  SiLabs_API_SAT_AutoDetect             (SILABS_FE_Context *front_end,    signed   int on_off);
signed   int  SiLabs_API_SAT_Tuner_Init             (SILABS_FE_Context *front_end);
signed   int  SiLabs_API_SAT_Tuner_SetLPF           (SILABS_FE_Context *front_end,    signed   int lpf_khz);
signed   int  SiLabs_API_SAT_voltage                (SILABS_FE_Context *front_end,    signed   int voltage);
signed   int  SiLabs_API_SAT_tone                   (SILABS_FE_Context *front_end,    unsigned char tone);
signed   int  SiLabs_API_SAT_voltage_and_tone       (SILABS_FE_Context *front_end,    signed   int voltage, unsigned char tone);
signed   int  SiLabs_API_SAT_prepare_diseqc_sequence(SILABS_FE_Context *front_end,    signed   int sequence_length, unsigned char *sequence_buffer, unsigned char cont_tone, unsigned char tone_burst, unsigned char burst_sel, unsigned char end_seq, signed   int *flags);
signed   int  SiLabs_API_SAT_trigger_diseqc_sequence(SILABS_FE_Context *front_end,    signed   int flags);
signed   int  SiLabs_API_SAT_send_diseqc_sequence   (SILABS_FE_Context *front_end,    signed   int sequence_length, unsigned char *sequence_buffer, unsigned char cont_tone, unsigned char tone_burst, unsigned char burst_sel, unsigned char end_seq);
signed   int  SiLabs_API_SAT_read_diseqc_reply      (SILABS_FE_Context *front_end,    signed   int *reply_length  , unsigned char *reply_buffer   );
signed   int  SiLabs_API_SAT_Tuner_Tune             (SILABS_FE_Context *front_end,    signed   int freq_kHz);
signed   int  SiLabs_API_SAT_Tuner_Standby          (SILABS_FE_Context *front_end);
signed   int  SiLabs_API_SAT_Tuner_SelectRF         (SILABS_FE_Context *front_end,    unsigned char rf_chn);
signed   int  SiLabs_API_SAT_Get_AGC                (SILABS_FE_Context *front_end);
#ifdef    UNICABLE_COMPATIBLE
signed   int  SiLabs_API_SAT_Unicable_Config        (SILABS_FE_Context *front_end,    signed   int unicable_mode, signed  int unicable_spectrum_inversion,  unsigned  int ub,  unsigned  int Fub_kHz,  unsigned  int Fo_kHz_low_band,  unsigned  int Fo_kHz_high_band );
signed   int  SiLabs_API_SAT_Unicable_Install       (SILABS_FE_Context *front_end);
signed   int  SiLabs_API_SAT_Unicable_Uninstall     (SILABS_FE_Context *front_end);
signed   int  SiLabs_API_SAT_Unicable_Position      (SILABS_FE_Context *front_end, int position);
signed   int  SiLabs_API_SAT_Unicable_Tune          (SILABS_FE_Context *front_end,    signed   int  freq_kHz);
signed   int  SiLabs_API_SAT_Unicable_Swap_Detect   (SILABS_FE_Context *front_end);
signed   int  SiLabs_API_SAT_Unicable_Swap_Loop     (SILABS_FE_Context *front_end, unsigned int rangeMin, unsigned int rangeMax);
signed   int  SiLabs_API_SAT_Random_Delay_Init      (SILABS_FE_Context *front_end,    signed   char UB);
signed   int  SiLabs_API_SAT_Random_Delay_Shift     (SILABS_FE_Context *front_end,    signed   char shift);
#endif /* UNICABLE_COMPATIBLE */
#endif /* SATELLITE_FRONT_END */
#ifdef    TERRESTRIAL_FRONT_END
#ifdef    DEMOD_DVB_T
signed   int  SiLabs_API_Get_DVBT_Hierarchy         (SILABS_FE_Context *front_end,    signed   int *hierarchy);
#endif /* DEMOD_DVB_T */
signed   int  SiLabs_API_Get_DS_ID_Num_PLP_Freq     (SILABS_FE_Context *front_end,    signed   int ds_index, signed   int *data_slice_id, signed   int *num_plp, signed   int *freq);
signed   int  SiLabs_API_Get_PLP_ID_and_TYPE        (SILABS_FE_Context *front_end,    signed   int ds_id, signed   int plp_index, signed   int *plp_id, signed   int *plp_type);
signed   int  SiLabs_API_Get_PLP_Group_Id           (SILABS_FE_Context *front_end,    signed   int recall, signed   int plp_index, signed   int *group_id);
signed   int  SiLabs_API_Select_PLP                 (SILABS_FE_Context *front_end,    signed   int plp_id);
signed   int  SiLabs_API_Get_AC_DATA                (SILABS_FE_Context *front_end,    unsigned char segment, unsigned char filtering, unsigned char read_offset, signed   intbit_count, unsigned char *AC_data);
signed   int  SiLabs_API_TER_AutoDetect             (SILABS_FE_Context *front_end,    signed   int on_off);
signed   int  SiLabs_API_TER_T2_lock_mode           (SILABS_FE_Context *front_end,    signed   int T2_lock_mode);
signed   int  SiLabs_API_TER_ISDBT_Monitoring_mode  (SILABS_FE_Context *front_end,    signed   int layer_mon);
signed   int  SiLabs_API_TER_ISDBT_Layer_Info       (SILABS_FE_Context *front_end,    signed   int layer, signed   int *constellation, signed   int *code_rate, signed   int *il, signed   int *nb_seg);
signed   int  SiLabs_API_TER_Tuner_Fine_Tune        (SILABS_FE_Context *front_end,    signed   int offset_500hz);
signed   int  SiLabs_API_TER_Tuner_Init             (SILABS_FE_Context *front_end);
signed   int  SiLabs_API_TER_Tuner_SetMFT           (SILABS_FE_Context *front_end,    signed   int  nStep);
signed   int  SiLabs_API_TER_Tuner_Text_status      (SILABS_FE_Context *front_end,    char *separator, char *msg);
signed   int  SiLabs_API_TER_Tuner_ATV_Text_status  (SILABS_FE_Context *front_end,    char *separator, char *msg);
signed   int  SiLabs_API_TER_Tuner_DTV_Text_status  (SILABS_FE_Context *front_end,    char *separator, char *msg);
signed   int  SiLabs_API_TER_Tuner_ATV_Tune         (SILABS_FE_Context *front_end);
signed   int  SiLabs_API_TER_Tuner_DTV_Tune         (SILABS_FE_Context *front_end,    unsigned long freq, unsigned char bw, unsigned char modulation);
signed   int  SiLabs_API_TER_Tuner_SetProperty      (SILABS_FE_Context *front_end,    unsigned int prop_code, int   data);
signed   int  SiLabs_API_TER_Tuner_GetProperty      (SILABS_FE_Context *front_end,    unsigned int prop_code, int  *data);
signed   int  SiLabs_API_TER_Tuner_Block_VCO        (SILABS_FE_Context *front_end,    signed   int  vco_code);
signed   int  SiLabs_API_TER_Tuner_Block_VCO2       (SILABS_FE_Context *front_end,    signed   int  vco_code);
signed   int  SiLabs_API_TER_Tuner_Block_VCO3       (SILABS_FE_Context *front_end,    signed   int  vco_code);
signed   int  SiLabs_API_TER_Tuner_Standby          (SILABS_FE_Context *front_end);
#endif /* TERRESTRIAL_FRONT_END */
#ifndef   NO_FLOATS_ALLOWED
signed   int  SiLabs_API_SSI_SQI                    (signed   int  standard, signed   int  locked, signed   int  Prec, signed   int  constellation, signed   int  code_rate, double CNrec, double ber, signed   int *ssi, signed   int *sqi);
#endif /* NO_FLOATS_ALLOWED */
signed   int  SiLabs_API_SSI_SQI_no_float           (signed   int  standard, signed   int  locked, signed   int  Prec, signed   int  constellation, signed   int  code_rate, signed   int     c_n_100, signed   int  ber_mant, signed   int  ber_exp, signed   int *ssi, signed   int *sqi);
#ifdef    Si2183_DVBS2_PLS_INIT_CMD
signed   int  SiLabs_API_SAT_Gold_Sequence_Init     (signed   int gold_sequence_index);
signed   int  SiLabs_API_SAT_PLS_Init               (SILABS_FE_Context *front_end,    signed   int pls_init);
#endif /* Si2183_DVBS2_PLS_INIT_CMD */
signed   int  SiLabs_API_Demod_Dual_Driving_Xtal    (SILABS_FE_Context  *front_end_driving_xtal, SILABS_FE_Context  *front_end_receiving_xtal);
signed   int  SiLabs_API_Demods_Kickstart           (void);
signed   int  SiLabs_API_TER_Tuners_Kickstart       (void);
signed   int  SiLabs_API_Cypress_Ports              (SILABS_FE_Context *front_end,    unsigned char OEA, unsigned char IOA, unsigned char OEB, unsigned char IOB, unsigned char OED, unsigned char IOD );
signed   int  SiLabs_API_SSI_SQI_no_floats          (signed   int  standard, signed   int  locked, signed   int  Prec, signed   int  constellation, signed   int  code_rate, signed   int  CNrec_1000, signed   int  ber_mant, signed   int  ber_exp, signed   int *ssi, signed   int *sqi);
void          SiLabs_API_Demod_reset                (SILABS_FE_Context *front_end);
#ifndef   NO_FLOATS_ALLOWED
double        ISDB_T_c_n_corrected                  (SILABS_FE_Context *front_end, int constellation, int guard_interval, double c_n);
double        DVBT_c_n_correction                   (int constellation, int guard_interval, int code_rate, double c_n);
#endif /* NO_FLOATS_ALLOWED */
signed   int  ISDB_T_c_n_100_corrected              (SILABS_FE_Context *front_end, int constellation, int guard_interval, int c_n_100);
signed   int  DVBT_c_n_100_corrected                (int constellation, int guard_interval, int code_rate, signed int c_n_100);
signed   int  SiLabs_API_Store_FW                   (SILABS_FE_Context *front_end,    firmware_struct fw_table[], signed   int  nbLines);
signed   int  SiLabs_API_Store_SPI_FW               (SILABS_FE_Context *front_end,    unsigned char   fw_table[], signed   int  nbBytes);

signed   int  SiLabs_API_Auto_Detect_Demods         (L0_Context* i2c, signed   int *Nb_FrontEnd, signed   int  demod_code[4], signed   int  demod_add[4], char *demod_string[4]);

signed   int  SiLabs_API_TER_Tuner_I2C_Enable       (SILABS_FE_Context *front_end);
signed   int  SiLabs_API_TER_Tuner_I2C_Disable      (SILABS_FE_Context *front_end);
signed   int  SiLabs_API_SAT_Tuner_I2C_Enable       (SILABS_FE_Context *front_end);
signed   int  SiLabs_API_SAT_Tuner_I2C_Disable      (SILABS_FE_Context *front_end);
signed   int  SiLabs_API_Get_Stream_Info            (SILABS_FE_Context *front_end,    signed   int isi_index, signed   int *isi_id, signed   int *isi_constellation, signed   int *isi_code_rate);
signed   int  SiLabs_API_Select_Stream              (SILABS_FE_Context *front_end,    signed   int stream_id);

signed   int  SiLabs_API_TER_Tuner_Dual_Driving_Xtal(SILABS_FE_Context  *front_end_driving_xtal, SILABS_FE_Context  *front_end_receiving_xtal);

#ifdef    SILABS_API_TEST_PIPE
signed   int  Silabs_API_Test                       (SILABS_FE_Context *front_end,    const char *target, const char *cmd, const char *sub_cmd, double dval, double *retdval, char **rettxt);
#endif /* SILABS_API_TEST_PIPE */

char*         SiLabs_API_TAG_TEXT                   (void);

#if defined( __cplusplus )
}
#endif

#endif /* _SiLabs_API_L3_Wrapper_H_ */

