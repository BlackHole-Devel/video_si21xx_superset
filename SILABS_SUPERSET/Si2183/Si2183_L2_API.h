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
/***************************************************************************************
                  Silicon Laboratories Broadcast Si2183 Layer 2 API


   L2 API header for commands and properties
   FILE: Si2183_L2_API.h
   Supported IC : Si2183
   Compiled for ROM 0 firmware 5_3_build_3
   Revision: V0.3.5.1
   Date: May 21 2015
**************************************************************************************/
/* Change log:
 As from V0.3.5.1:
    <correction>[prototype] Adding Si2183_L2_Health_Check prototype

 As from V0.3.4.0:
    <improvement>[traces] Moving ddRestartTime in L2 context, to keep track of its value.

 As from V0.3.2.0:
    <correction>[SAT/UnicableII] Adding unicable_mode member in Si2183_L2_Context to allow dynamic selection of the SAT scan bandwidth in Unicable II

 As from V0.2.6.0:
    <compatibility>[compilation/FW_load] Adding tests on 'legacy' flags for FW loading.
      Previous versions required at least one Si2183or Si2180 flag to be defined.

 As from V0.2.3.0:
    <new_feature>[init/force_full_init] Adding new defines to be used in the force_full_init value (instead of using only 0 or 1).

 As from V0.1.3.0:
    <new_feature>[Broadcast_i2c/demods] Adding TER_tuner_config_done in Si2183_L2_Context

 As from V0.1.2.0:
    <improvement>[DVB-C/MCNS/BLINDSCAN] Adding cable_lock_afc_range_khz in Si2183_L2_Context

 As from  V0.1.1.0:
  <improvement>[traces] Adding cumulativeScanTime, cumulativeTimeoutTime, nbTimeouts and nbDecisions to Si2183_L2_Context

 As from V0.0.9.0
  <new_feature>[superset] Changing tags to allow SILABS_SUPERSET use (one code, all configs)
    Using TERRESTRIAL_FRONT_END instead of DEMOD_DVB_T         (there are products with ISDB-T and not DVB-T)
    Using SATELLITE_FRONT_END   instead of DEMOD_DVB_S_S2_DSS  (for consistency with the above)

 As from V0.0.5.0:
   <improvement>[Blindscan/debug] Redefining Si2183_READ and Si2183_WRITE to allow using either "pmajor = '4'" register definitions
     or Si2183 register definitions.

 As from V0.0.4.0:
   <renaming>[config_macros] SW_INIT_Si21682_EVB_Rev1_0_Si2183 renamed as SW_INIT_Si21682_EVB_Rev1_0_41A_83A (for GUI purposes)

 As from V0.0.0.1:
   <improvement>[UNICABLE] redefinition of the return type of the Unicable tune function (from void to int),
    To allow proving the final Unicable tune freq to Seek_Next.

 As from V0.0.0:
  Initial version (based on Si2164 code V0.3.4)
****************************************************************************************/

#ifndef   Si2183_L2_API_H
#define   Si2183_L2_API_H

#define   Si2183_COMMAND_PROTOTYPES
#include "Si2183_Platform_Definition.h"
#include "Si2183_Properties_Functions.h"

#ifndef    Si2183_B60_COMPATIBLE
 #ifndef    Si2183_A55_COMPATIBLE
  #ifndef    Si2183_A50_COMPATIBLE
   #ifndef    Si2183_ES_COMPATIBLE
    #ifndef    Si2180_B60_COMPATIBLE
     #ifndef    Si2180_A55_COMPATIBLE
      #ifndef    Si2180_A50_COMPATIBLE
       #ifndef    Si2167B_22_COMPATIBLE
        #ifndef    Si2167B_20_COMPATIBLE
         #ifndef    Si2169_30_COMPATIBLE
          #ifndef    Si2167_B25_COMPATIBLE
           #ifndef    Si2164_A40_COMPATIBLE
     "If you get a compilation error on these lines, it means that no Si2183 version has been selected.";
        "Please define Si2183_B60_COMPATIBLE, Si2183_A55_COMPATIBLE, Si2183_A50_COMPATIBLE, Si2183_ES_COMPATIBLE,";
                      "Si2180_A55_COMPATIBLE, Si2180_A50_COMPATIBLE,";
                      "Si2167B_22_COMPATIBLE, Si2167B_20_COMPATIBLE, Si2169_30_COMPATIBLE,";
                      "Si2167_B25_COMPATIBLE or Si2164_A40_COMPATIBLE at project level!";
     "Once the flags will be defined, this code will not be visible to the compiler anymore";
     "Do NOT comment these lines, they are here to help, showing if there are missing project flags";
           #endif /* Si2164_A40_COMPATIBLE */
          #endif /* Si2167_B25_COMPATIBLE */
         #endif /* Si2169_30_COMPATIBLE */
        #endif /* Si2167B_20_COMPATIBLE */
       #endif /* Si2167B_22_COMPATIBLE */
      #endif /* Si2180_A50_COMPATIBLE */
     #endif /* Si2180_A55_COMPATIBLE */
    #endif /* Si2180_B60_COMPATIBLE */
   #endif /* Si2183_ES_COMPATIBLE */
  #endif /* Si2183_A50_COMPATIBLE */
 #endif /* Si2183_A55_COMPATIBLE */
#endif /* Si2183_B60_COMPATIBLE */

#ifndef   SILABS_SUPERSET
 #ifndef   TERRESTRIAL_FRONT_END
  #define   TERRESTRIAL_FRONT_END
 #endif /* TERRESTRIAL_FRONT_END */

  #ifndef   SATELLITE_FRONT_END
   #define  SATELLITE_FRONT_END
  #endif /* SATELLITE_FRONT_END */
#endif /* SILABS_SUPERSET */

#ifdef    SATELLITE_FRONT_END
 #ifdef    UNICABLE_COMPATIBLE
  #include "SiLabs_Unicable_API.h"
  typedef void          (*Si2183_WRAPPER_TUNER_TUNE_FUNC )   (void*, signed   int freq_kHz);
  typedef signed   int  (*Si2183_WRAPPER_UNICABLE_TUNE_FUNC) (void*, signed   int freq_kHz);
 #endif /* UNICABLE_COMPATIBLE */
#endif /* SATELLITE_FRONT_END */

#define Si2183_SKIP_DEMOD_INIT      0x02
#define Si2183_FORCE_TER_TUNER_INIT 0x04
#define Si2183_FORCE_SAT_TUNER_INIT 0x08
#define Si2183_FORCE_DEMOD_INIT     0x10
#define Si2183_USE_TER_CLOCK        0x20
#define Si2183_USE_SAT_CLOCK        0x40

#ifdef    INDIRECT_I2C_CONNECTION
  typedef signed   int  (*Si2183_INDIRECT_I2C_FUNC)  (void*);
#endif /* INDIRECT_I2C_CONNECTION */

typedef struct _Si2183_L2_Context {
   L1_Si2183_Context *demod;
#ifdef    TERRESTRIAL_FRONT_END
   TER_TUNER_CONTEXT *tuner_ter;
 #ifdef    INDIRECT_I2C_CONNECTION
   Si2183_INDIRECT_I2C_FUNC  f_TER_tuner_enable;
   Si2183_INDIRECT_I2C_FUNC  f_TER_tuner_disable;
 #endif /* INDIRECT_I2C_CONNECTION */
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
   SAT_TUNER_CONTEXT *tuner_sat;
 #ifdef    INDIRECT_I2C_CONNECTION
   Si2183_INDIRECT_I2C_FUNC  f_SAT_tuner_enable;
   Si2183_INDIRECT_I2C_FUNC  f_SAT_tuner_disable;
 #endif /* INDIRECT_I2C_CONNECTION */
#endif /* SATELLITE_FRONT_END */
   L1_Si2183_Context  demodObj;
#ifdef    TERRESTRIAL_FRONT_END
   TER_TUNER_CONTEXT  tuner_terObj;
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
 #ifndef   NO_SAT
   SAT_TUNER_CONTEXT  tuner_satObj;
 #endif /* NO_SAT */
#endif /* SATELLITE_FRONT_END */
   signed   int                first_init_done;
   signed   int                Si2183_init_done;
#ifdef    TERRESTRIAL_FRONT_END
   signed   int                TER_init_done;
   signed   int                TER_tuner_init_done;
   signed   int                TER_tuner_config_done;
   unsigned char               auto_detect_TER;
   signed   int                cable_lock_afc_range_khz;
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
   signed   int                SAT_init_done;
   signed   int                SAT_tuner_init_done;
   unsigned char               auto_detect_SAT;
   unsigned char               satellite_spectrum_inversion;
 #ifdef    UNICABLE_COMPATIBLE
   unsigned char               lnb_type;
   unsigned char               unicable_mode;
   unsigned char               unicable_spectrum_inversion;
   Si2183_WRAPPER_TUNER_TUNE_FUNC     f_tuner_tune;
   Si2183_WRAPPER_UNICABLE_TUNE_FUNC  f_Unicable_tune;
 #endif /* UNICABLE_COMPATIBLE */
#endif /* SATELLITE_FRONT_END */
   void                       *callback;
   signed   int                standard;
   signed   int                detected_rf;
   signed   int                previous_standard;
   signed   int                tuneUnitHz;
   unsigned int                rangeMin;
   unsigned int                rangeMax;
   signed   int                seekBWHz;
   signed   int                seekStepHz;
   signed   int                minSRbps;
   signed   int                maxSRbps;
   signed   int                minRSSIdBm;
   signed   int                maxRSSIdBm;
   signed   int                minSNRHalfdB;
   signed   int                maxSNRHalfdB;
   signed   int                seekAbort;
   signed   int                lockAbort;
   signed   int                searchStartTime;  /* searchStartTime  is used to trace the time spent trying to detect a channel.                      */
                                                 /* It is set differently from seekStartTime when returning from a handshake                          */
   signed   int                timeoutStartTime; /* timeoutStartTime is used in blind mode to make sure the FW is correctly responding.               */
                                                 /* timeoutStartTime is used in non-blind mode to manage the timeout when trying to lock on a channel */
   signed   int                ddRestartTime;    /* ddRestartTime    is used to trace the time spent between DD_RESTART and the decision              */
   signed   int                handshakeUsed;
   signed   int                handshakeStart_ms;
   signed   int                handshakePeriod_ms;
   signed   int                cumulativeScanTime;
   signed   int                cumulativeTimeoutTime;
   signed   int                nbTimeouts;
   signed   int                nbDecisions;
   unsigned char               handshakeOn;
   signed   int                center_rf;
   unsigned int                misc_infos;
} Si2183_L2_Context;

/* firmware_struct needs to be declared to allow loading the FW in 16 bytes mode */
#ifndef __FIRMWARE_STRUCT__
#define __FIRMWARE_STRUCT__
typedef struct firmware_struct {
  unsigned char firmware_len;
  unsigned char firmware_table[16];
} firmware_struct;
#endif /* __FIRMWARE_STRUCT__ */

signed   int   Si2183_Init                      (L1_Si2183_Context *api);
signed   int   Si2183_Media                     (L1_Si2183_Context *api, signed   int modulation);
signed   int   Si2183_Configure                 (L1_Si2183_Context *api);
signed   int   Si2183_PowerUpWithPatch          (L1_Si2183_Context *api);
signed   int   Si2183_PowerUpUsingBroadcastI2C  (L1_Si2183_Context *demods[], signed   int demod_count );
signed   int   Si2183_LoadFirmware              (L1_Si2183_Context *api, unsigned char  *fw_table,   signed   int lines);
signed   int   Si2183_LoadFirmware_16           (L1_Si2183_Context *api, firmware_struct fw_table[], signed   int nbLines);
#ifdef    FW_DOWNLOAD_OVER_SPI
signed   int   Si2183_LoadFirmwareSPI           (L1_Si2183_Context *api, unsigned char  *fw_table, signed   int nbBytes, unsigned char pbl_key,  unsigned char pbl_num);
signed   int   Si2183_LoadFirmwareSPI_Split     (L1_Si2183_Context *api, unsigned char  *fw_table, signed   int nbBytes, unsigned char pbl_key,  unsigned char pbl_num , unsigned int num_split, unsigned int *split_list);
#endif /* FW_DOWNLOAD_OVER_SPI */
signed   int   Si2183_StartFirmware             (L1_Si2183_Context *api);
signed   int   Si2183_STANDBY                   (L1_Si2183_Context *api);
signed   int   Si2183_WAKEUP                    (L1_Si2183_Context *api);
char          *Si2183_standardName              (signed   int standard);

signed   int   Si2183_L2_SILENT                    (Si2183_L2_Context *front_end, signed   int silent);
/*****************************************************************************************/
/*               SiLabs demodulator API functions (demod and tuner)                      */
/*****************************************************************************************/
    /*  Software info functions */
signed   int   Si2183_L2_Infos                    (Si2183_L2_Context *front_end, char *infoString);

    /*  Software init functions */
char           Si2183_L2_SW_Init                  (Si2183_L2_Context *front_end
                                   , signed   int demodAdd
#ifdef    TERRESTRIAL_FRONT_END
                                   , signed   int tunerAdd_Ter
 #ifdef    INDIRECT_I2C_CONNECTION
                                   , Si2183_INDIRECT_I2C_FUNC           TER_tuner_enable_func
                                   , Si2183_INDIRECT_I2C_FUNC           TER_tuner_disable_func
 #endif /* INDIRECT_I2C_CONNECTION */
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
                                   , signed   int tunerAdd_Sat
#ifdef    UNICABLE_COMPATIBLE
                                   , Si2183_WRAPPER_TUNER_TUNE_FUNC     tuner_tune
                                   , Si2183_WRAPPER_UNICABLE_TUNE_FUNC  unicable_tune
#endif /* UNICABLE_COMPATIBLE */
 #ifdef    INDIRECT_I2C_CONNECTION
                                   , Si2183_INDIRECT_I2C_FUNC           SAT_tuner_enable_func
                                   , Si2183_INDIRECT_I2C_FUNC           SAT_tuner_disable_func
 #endif /* INDIRECT_I2C_CONNECTION */
#endif /* SATELLITE_FRONT_END */
                                   , void *p_context
                                   );
signed   int   Si2183_L2_Set_Index_and_Tag        (Si2183_L2_Context   *front_end, unsigned char index, const char* tag);
void           Si2183_L2_HW_Connect               (Si2183_L2_Context   *front_end, CONNECTION_TYPE mode);
    /*  Locking and status functions */
signed   int   Si2183_L2_switch_to_standard       (Si2183_L2_Context   *front_end, unsigned char new_standard, unsigned char force_full_init);
signed   int   Si2183_L2_lock_to_carrier          (Si2183_L2_Context   *front_end
                                 ,  signed   int  standard
                                 ,  signed   int  freq
                                  , signed   int  ter_bandwidth_hz
#ifdef    DEMOD_DVB_T
                                  , unsigned char dvb_t_stream
#endif /* DEMOD_DVB_T */
                                  , unsigned int  symbol_rate_bps
#ifdef    DEMOD_DVB_C
                                  , unsigned char dvb_c_constellation
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_C2
                                  , signed   int  data_slice_id
#endif /* DEMOD_DVB_C2 */
                                  , signed   int  plp_id
#ifdef    DEMOD_DVB_T2
                                  , unsigned char T2_lock_mode
#endif /* DEMOD_DVB_T2 */
                                    );
signed   int   Si2183_L2_Channel_Lock_Abort       (Si2183_L2_Context   *front_end);
signed   int   Si2183_L2_communication_check      (Si2183_L2_Context   *front_end);
signed   int   Si2183_L2_Part_Check               (Si2183_L2_Context   *front_end);
unsigned char Si2183_L2_Set_Invert_Spectrum       (Si2183_L2_Context   *front_end);
    /*  TS functions */
signed   int   Si2183_L2_TS_mode                  (Si2183_L2_Context   *front_end, signed   int ts_mode);

    /*  Tuner wrapping functions */
signed   int   Si2183_L2_Tune                     (Si2183_L2_Context   *front_end, signed   int rf);
signed   int   Si2183_L2_Get_RF                   (Si2183_L2_Context   *front_end);

#ifdef    SATELLITE_FRONT_END
    /* LNB control and DiSEqC functions */
signed   int   Si2183_L2_prepare_diseqc_sequence  (Si2183_L2_Context   *front_end, signed   int sequence_length, unsigned char *sequenceBuffer, unsigned char cont_tone, unsigned char tone_burst, unsigned char burst_sel, unsigned char end_seq);
signed   int   Si2183_L2_trigger_diseqc_sequence  (Si2183_L2_Context   *front_end);
signed   int   Si2183_L2_send_diseqc_sequence     (Si2183_L2_Context   *front_end, signed   int sequence_length, unsigned char *sequenceBuffer, unsigned char cont_tone, unsigned char tone_burst, unsigned char burst_sel, unsigned char end_seq);
signed   int   Si2183_L2_read_diseqc_reply        (Si2183_L2_Context   *front_end, signed   int *reply_length  , unsigned char *replyBuffer   );
#endif /* SATELLITE_FRONT_END */

    /*  Tuner i2c bus control functions */
unsigned char Si2183_L2_Tuner_I2C_Enable (Si2183_L2_Context   *front_end);
unsigned char Si2183_L2_Tuner_I2C_Disable(Si2183_L2_Context   *front_end);

    /*  Scanning functions */
const char *Si2183_L2_Trace_Scan_Status  (signed   int scan_status);
signed   int   Si2183_L2_Channel_Seek_Init        (Si2183_L2_Context   *front_end,
                                          signed   int rangeMinHz,   signed   int rangeMaxHz,
                                          signed   int seekBWHz,     signed   int seekStepHz,
                                          signed   int minSRbps,     signed   int maxSRbps,
                                          signed   int minRSSIdBm,   signed   int maxRSSIdBm,
                                          signed   int minSNRHalfdB, signed   int maxSNRHalfdB);
signed   int  Si2183_L2_Channel_Seek_Next         (Si2183_L2_Context   *front_end
                                           , signed   int *standard
                                           , signed   int *freq
                                           , signed   int *bandwidth_Hz
#ifdef    DEMOD_DVB_T
                                           , signed   int *stream
#endif /* DEMOD_DVB_T*/
                                           , unsigned int *symbol_rate_bps
#ifdef    DEMOD_DVB_C
                                           , signed   int *constellation
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_C2
                                           , signed   int *num_data_slice
#endif /* DEMOD_DVB_C2*/
                                           , signed   int *num_plp
#ifdef    DEMOD_DVB_T2
                                           , signed   int *T2_base_lite
#endif /* DEMOD_DVB_T2 */
                                           );
signed   int   Si2183_L2_Channel_Seek_End         (Si2183_L2_Context   *front_end);
signed   int   Si2183_L2_Channel_Seek_Abort       (Si2183_L2_Context   *front_end);
#define   AGC_FUNCTIONS
#ifdef    TERRESTRIAL_FRONT_END
signed   int   Si2183_L2_TER_Clock                (Si2183_L2_Context   *front_end, signed   int clock_source, signed   int clock_input, signed   int clock_freq, signed   int clock_control);
signed   int   Si2183_L2_TER_AGC                  (Si2183_L2_Context   *front_end, signed   int agc1_mode, signed   int agc1_inversion, signed   int agc2_mode, signed   int agc2_inversion);
#ifdef    DEMOD_DVB_T2
signed   int   Si2183_L2_TER_FEF_CONFIG           (Si2183_L2_Context   *front_end, signed   int fef_mode, signed   int fef_pin, signed   int fef_level);
signed   int   Si2183_L2_TER_FEF                  (Si2183_L2_Context   *front_end, signed   int fef);
signed   int   Si2183_L2_TER_FEF_SETUP            (Si2183_L2_Context   *front_end, signed   int fef);
#endif /* DEMOD_DVB_T2 */
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
signed   int   Si2183_L2_SAT_Clock                (Si2183_L2_Context   *front_end, signed   int clock_source, signed   int clock_input, signed   int clock_freq, signed   int clock_control);
signed   int   Si2183_L2_SAT_AGC                  (Si2183_L2_Context   *front_end, signed   int agc1_mode, signed   int agc1_inversion, signed   int agc2_mode, signed   int agc2_inversion);
signed   int   Si2183_L2_SAT_Spectrum             (Si2183_L2_Context   *front_end, signed   int spectrum_inversion);
signed   int   Si2183_L2_SAT_LPF                  (Si2183_L2_Context   *front_end, signed   int lpf_khz);
signed   int   Si2183_SatAutoDetect               (Si2183_L2_Context   *front_end);
signed   int   Si2183_SatAutoDetectOff            (Si2183_L2_Context   *front_end);
#endif /* SATELLITE_FRONT_END */
#ifdef    DEMOD_DVB_T2
signed   int   Si2183_TerAutoDetect               (Si2183_L2_Context   *front_end);
signed   int   Si2183_TerAutoDetectOff            (Si2183_L2_Context   *front_end);
#endif /* DEMOD_DVB_T2 */
signed   int   Si2183_L2_Health_Check             (Si2183_L2_Context *front_end);
signed   int   Si2183_L2_GET_REG                  (Si2183_L2_Context *front_end, unsigned char   reg_code_lsb, unsigned char   reg_code_mid, unsigned char   reg_code_msb);

#ifdef    SILABS_API_TEST_PIPE
signed   int   Si2183_L2_Test                     (Si2183_L2_Context *front_end, const char *target, const char *cmd, const char *sub_cmd, double dval, double *retdval, char **rettxt);
#endif /* SILABS_API_TEST_PIPE */

#define Si2183_READ(ptr, register)             if (ptr->rsp->part_info.pmajor == '4' ) { Si2183_L1_DD_GET_REG (ptr, Si2164_##register##_LSB , Si2164_##register##_MID , Si2164_##register##_MSB );}\
                                          else if (ptr->rsp->part_info.pmajor == '2' ) { Si2183_L1_DD_GET_REG (ptr, Si2167B_##register##_LSB, Si2167B_##register##_MID, Si2167B_##register##_MSB);}\
                                          else                                         { Si2183_L1_DD_GET_REG (ptr, Si2183_##register##_LSB , Si2183_##register##_MID , Si2183_##register##_MSB );}\
                                          register = (ptr->rsp->dd_get_reg.data1<<0) + (ptr->rsp->dd_get_reg.data2<<8) + (ptr->rsp->dd_get_reg.data3<<16) + (ptr->rsp->dd_get_reg.data4<<24);
#define Si2183_WRITE(ptr, register, value)  if    (ptr->rsp->part_info.pmajor == '4' ) { Si2183_L1_DD_SET_REG (ptr, Si2164_##register##_LSB , Si2164_##register##_MID , Si2164_##register##_MSB,value );}\
                                          else if (ptr->rsp->part_info.pmajor == '2' ) { Si2183_L1_DD_SET_REG (ptr, Si2167B_##register##_LSB, Si2167B_##register##_MID, Si2167B_##register##_MSB,value);}\
                                          else                                         { Si2183_L1_DD_SET_REG (ptr, Si2183_##register##_LSB , Si2183_##register##_MID , Si2183_##register##_MSB,value );}


#define   MACROS_FOR_SINGLE_USING_Si2183
#ifdef    MACROS_FOR_SINGLE_USING_Si2183

#define SW_INIT_Si216x_EVB_Rev3_0_Si2183\
  /* SW Init for front end 0 */\
  front_end  = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x18);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2178, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 2);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5815, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 25, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 1, 44, 24, 2);\
  SiLabs_API_SAT_Spectrum             (front_end, 1);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 1);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);

  #ifdef    TERRESTRIAL_FRONT_END
#define SW_INIT_Platform_2010_Rev1_0_Si2183\
  /* SW Init for front end 0 */\
  front_end  = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
  SiLabs_API_SW_Init                  (front_end, 0xcc, 0xc0, 0x18);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2176, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 0, 44, 24, 2);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 21, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 2);\
  SiLabs_API_SAT_Spectrum             (front_end, 1);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 1);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  front_end->Si2183_FE->TER_init_done = 1;\
  front_end->Si2183_FE->TER_tuner_init_done = 1;\
  front_end->Si2183_FE->first_init_done     = 1;\
  front_end->standard = SILABS_ISDB_T;\
  front_end->Si2183_FE->previous_standard = Si2183_DD_MODE_PROP_MODULATION_DVBT;\
  SiLabs_API_HW_Connect               (front_end, 1);
  #endif /* TERRESTRIAL_FRONT_END */

#define SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2183\
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x18);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2178, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 2);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 2);\
  SiLabs_API_SAT_Spectrum             (front_end, 1);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 1);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#define SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178B_Si2183\
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x18);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2178B, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 2);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 2);\
  SiLabs_API_SAT_Spectrum             (front_end, 1);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 1);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#define SW_INIT_Si2141_51_DVBT2TC_DC_Rev1_2_Si2168C\
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x18);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2151, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#endif /* MACROS_FOR_SINGLE_USING_Si2183 */

#define   MACROS_FOR_DUAL_USING_Si2183

#ifdef    MACROS_FOR_DUAL_USING_Si2183

#define SW_INIT_Si216x2_EVB_Rev1_x_91A_83A\
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x14);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2191, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xa, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xc, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 2);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xc, 1, 0x0, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);\
  /* SW Init for front end 1 */\
  front_end                    = &(FrontEnd_Table[1]);\
  SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
  SiLabs_API_SW_Init                  (front_end, 0xce, 0xc6, 0x16);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2191, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 0, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 0);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xd, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 0);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 1, "fe[1]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#define SW_INIT_Si216x2_EVB_Rev1_x_Si2178B_Si2183\
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x14);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2178B, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xa, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xc, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xc, 1, 0x0, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);\
  /* SW Init for front end 1 */\
  front_end                    = &(FrontEnd_Table[1]);\
  SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
  SiLabs_API_SW_Init                  (front_end, 0xce, 0xc6, 0x16);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2178B, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 0, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xd, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 1, "fe[1]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#define SW_INIT_Si216x2_EVB_Rev2_0_Si2183\
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x14);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2177, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xa, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xc, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xc, 1, 0x0, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);\
  /* SW Init for front end 1 */\
  front_end                    = &(FrontEnd_Table[1]);\
  SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
  SiLabs_API_SW_Init                  (front_end, 0xce, 0xc6, 0x16);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2157, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 0, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 2);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xd, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 0);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 1, "fe[1]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#define SW_INIT_Si21682_EVB_Rev1_0_41A_83A\
  /* SW Init for front end 0 (TER-ONLY) */\
  front_end                    = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2141, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xa, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xc, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);\
  /* SW Init for front end 1 (TER-ONLY) */\
  front_end                    = &(FrontEnd_Table[1]);\
  SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
  SiLabs_API_SW_Init                  (front_end, 0xce, 0xc6, 0);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2141, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 0, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xd, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 1, "fe[1]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#endif /* MACROS_FOR_DUAL_USING_Si2183 */

 #define   MACROS_FOR_QUAD_USING_Si2183

#ifdef    MACROS_FOR_QUAD_USING_Si2183

  #define SW_INIT_Dual_Si2191_Si216x2_Si2183\
  \
  front_end                    = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x14);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2178B, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xc, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 1);\
  SiLabs_API_SAT_AGC                  (front_end, 0xc, 1, 0x0 , 0);\
  SiLabs_API_HW_Connect               (front_end, 1);\
  \
  front_end                   = &(FrontEnd_Table[1]);\
  SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
  SiLabs_API_SW_Init                  (front_end, 0xca, 0xc6, 0x16);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 1, "fe[1]");\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2178B, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 0, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 0);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xd, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x12);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 1, 44, 24, 0);\
  SiLabs_API_SAT_Spectrum             (front_end, 1);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0 , 0);\
  SiLabs_API_HW_Connect               (front_end, 1);\
  \
  front_end                   = &(FrontEnd_Table[2]);\
  SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
  SiLabs_API_SW_Init                  (front_end, 0xce, 0xc2, 0x00);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 2, "fe[2]");\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2178B, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 2);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xc, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x14);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 2);\
  SiLabs_API_SAT_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 1);\
  SiLabs_API_SAT_AGC                  (front_end, 0x0, 0, 0x0 , 0);\
  SiLabs_API_HW_Connect               (front_end, 1);\
  \
  front_end                   = &(FrontEnd_Table[3]);\
  SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
  SiLabs_API_SW_Init                  (front_end, 0xcc, 0xc4, 0x00);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 3, "fe[3]");\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2178B, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 2);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 0, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 0);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xd, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x16);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 2);\
  SiLabs_API_SAT_Clock                (front_end, 1, 44, 24, 0);\
  SiLabs_API_SAT_Spectrum             (front_end, 1);\
  SiLabs_API_SAT_AGC                  (front_end, 0x0, 0, 0x0 , 0);\
  SiLabs_API_HW_Connect               (front_end, 1);

#endif /* MACROS_FOR_QUAD_USING_Si2183 */

#endif /* Si2183_L2_API_H */







