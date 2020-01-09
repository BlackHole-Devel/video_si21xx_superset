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
/* Change log:

  As from 2018/06/12:
    <improvement>[unicable/install] Adding inBlindScan flag in context.

  As from 2017/06/21:
    <cleanup>[unicable/install] Removing SiLabs_Unicable_API_Install members from context, for clarity.

  As from 2012/10/18 (SVN3186):
   Adding #ifdef SiTRACES tags to allow compiling without SiTRACES
 *************************************************************************************************************/

#ifndef  _SiLabs_UNICABLE_API_H_
#define  _SiLabs_UNICABLE_API_H_

/*****************************************************************************/
/* Common includes                                                           */
/*****************************************************************************/
#include "Silabs_L0_API.h"

#define UNICABLE_TONE_FINE   0
#define UNICABLE_TONE_COARSE 1

#define UNICABLE_NO_TUNING   0

#define UNICABLE_POSITION_A  0
#define UNICABLE_POSITION_B  1
#define UNICABLE_LOW_BAND    0
#define UNICABLE_HIGH_BAND   1
#define UNICABLE_VERTICAL    0
#define UNICABLE_HORIZONTAL  1

#define ODU_DATA1            4
#define ODU_DATA2            5

#define UNICABLE_FRAMING          0xE0
#define UNICABLE_ADDRESS          0x00
#define UNICABLE_NORMAL_OPERATION 0x5A
#define UNICABLE_SPECIAL_MODES    0x5B

#define UNICABLE_FRAMING_INDEX  0
#define UNICABLE_ADDRESS_INDEX  1
#define UNICABLE_COMMAND_INDEX  2
#define UNICABLE_DATA1_INDEX    3
#define UNICABLE_DATA2_INDEX    4

#define UNICABLE_II_ODU_CHANNEL_CHANGE     0x70
#define UNICABLE_II_ODU_CHANNEL_CHANGE_PIN 0x71

#define UNICABLE_II_FRAMING_INDEX   0
#define UNICABLE_II_DATA1_INDEX     1
#define UNICABLE_II_DATA2_INDEX     2
#define UNICABLE_II_DATA3_INDEX     3
#define UNICABLE_II_DATA4_INDEX     4

#define UNICABLE_LNB_TYPE_NORMAL    1
#define UNICABLE_LNB_TYPE_UNICABLE  2

#define ODU_ALL_ON_CODE          0x00
#define ODU_POWER_OFF            0x00
#define ODU_CONFIG_CODE          0x01
#define ODU_FORCE_NO             0xFF
#define ODU_LOFREQ_CODE          0x02

#define UNICABLE_TONE_CHANGE_TIME 500
#define UNICABLE_FINE_RANGE     10000
#define UNICABLE_FINE_STEP        500
#define UNICABLE_MAX_COARSE_TONE   50
#define UNICABLE_COARSE_STEP     5000
#define UNICABLE_MAX_SAMPLES      (2150000 - 950000)/UNICABLE_COARSE_STEP + 1
#define UNICABLE_MAX_FINE_TONE     32

#define UNICABLE_YES                1
#define UNICABLE_NO                 0

#define UNICABLE_TRACES(...) printf(__VA_ARGS__);

  #ifdef   SiTRACES
#define UNICABLE_LOGS(...)  printf(__VA_ARGS__);
  #else  /* SiTRACES */
#define UNICABLE_LOGS(...)  printf(__VA_ARGS__);
  #endif /* SiTRACES */

/* type pointer to function to write byte to diseq bus */
typedef signed int  (*UNICABLE_DISEQ_PREPARE_FUNC) (void*, signed int sequence_length, unsigned char *sequence_buffer, unsigned char cont_tone, unsigned char tone_burst, unsigned char burst_sel, unsigned char end_seq, signed int *flags);
typedef signed int  (*UNICABLE_DISEQ_TRIGGER_FUNC) (void*, signed int flags);
typedef        void (*UNICABLE_DISEQ_WRITE_FUNC)   (void*, signed int sequence_length, unsigned char *sequence_buffer, unsigned char cont_tone, unsigned char tone_burst, unsigned char burst_sel, unsigned char end_seq);
typedef        void (*UNICABLE_DISEQ_READ_FUNC)    (void*, signed int *reply_length   , unsigned char *reply_buffer);
typedef signed int  (*UNICABLE_TUNE_FUNC)          (void*, signed int freq_kHz);
typedef signed int  (*UNICABLE_AGC_FUNC)           (void*);
typedef        void (*UNICABLE_TEST_FUNC)          (void*, signed int number);
typedef        void (*UNICABLE_LPF_FUNC)           (void*, signed int lpf_khz);
typedef signed int  (*UNICABLE_LNB_VOLTAGE_FUNC)   (void*, signed int  voltage);
typedef signed int  (*UNICABLE_LNB_TONE_FUNC)      (void*, unsigned char tone);

typedef struct _SILABS_Unicable_Context  {
  unsigned char      installed;          /* Set to: 0 for non-Unicable tuning, 1 for Unicable I (EN50494), 2 for Unicable II (EN50607) */
  signed int         Fo_kHz_low_band;
  signed int         Fo_kHz_high_band;
  signed int         Fub_kHz;
  signed int         tuner_wait_ms;
  signed int         tone_on_wait_ms;
  unsigned char      ub;
  unsigned char      band;
  unsigned char      polarization;
  unsigned char      bank;
  unsigned char      inBlindScan;
  signed int         T;
  signed int         sat_tuner_freq;
  unsigned char      satellite_position;
  unsigned char      PIN_code;
  unsigned char      trackDiseqc;
  unsigned char      trackDebug;
  L0_Context        *i2c;
  L0_Context         i2cObj;
  void              *callback;
  UNICABLE_TUNE_FUNC          f_tune;
  UNICABLE_AGC_FUNC           f_agc;
  UNICABLE_DISEQ_PREPARE_FUNC f_diseq_prepare;
  UNICABLE_DISEQ_TRIGGER_FUNC f_diseq_trigger;
  UNICABLE_DISEQ_WRITE_FUNC   f_diseq_write;
  UNICABLE_DISEQ_READ_FUNC    f_diseq_read;
  UNICABLE_LPF_FUNC           f_lpf;
  UNICABLE_LNB_VOLTAGE_FUNC   f_lnb_voltage;
  UNICABLE_LNB_TONE_FUNC      f_lnb_tone;
} SILABS_Unicable_Context;

signed int   SiLabs_Unicable_API_Init          (SILABS_Unicable_Context *unicable,
                                                void *p_context,
                                                UNICABLE_TUNE_FUNC          tune,
                                                UNICABLE_AGC_FUNC           agc,
                                                UNICABLE_DISEQ_PREPARE_FUNC diseq_prepare,
                                                UNICABLE_DISEQ_TRIGGER_FUNC diseq_trigger,
                                                UNICABLE_DISEQ_WRITE_FUNC   diseq_write,
                                                UNICABLE_LPF_FUNC           lpf,
                                                UNICABLE_LNB_VOLTAGE_FUNC   lnb_voltage,
                                                UNICABLE_LNB_TONE_FUNC      lnb_tone
                                              );
signed int   SiLabs_Unicable_API_Tune          (SILABS_Unicable_Context *unicable, signed int Freq_kHz);
signed int   SiLabs_Unicable_API_Hardcoded_Tune(SILABS_Unicable_Context *unicable, signed int bank, signed int T, signed int Freq_kHz);
       char *SiLabs_Unicable_API_Tune_Infos    (SILABS_Unicable_Context *unicable, char *textBuffer);
signed int   SiLabs_Unicable_API_All_UBs_on    (SILABS_Unicable_Context *unicable);
signed int   SiLabs_Unicable_API_All_UBs_Off   (SILABS_Unicable_Context *unicable);
signed int   Silabs_Unicable_API_One_UB_off    (SILABS_Unicable_Context *unicable, signed int UB_index);
       char *SiLabs_Unicable_API_Install_Infos (SILABS_Unicable_Context *unicable, char *textBuffer);

#ifdef    SILABS_API_TEST_PIPE
signed int   SiLabs_Unicable_API_Test          (SILABS_Unicable_Context *unicable, const char *target, const char *cmd, const char *sub_cmd, double dval, double *retdval, char **rettxt);
#endif /* SILABS_API_TEST_PIPE */

#endif /* _SiLabs_UNICABLE_API_H_ */
