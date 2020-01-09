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
#ifndef _L1_RF_AV2018_API_H_
#define _L1_RF_AV2018_API_H_

#ifndef   DLL_MODE
 #include "Silabs_L0_API.h"
#else  /* DLL_MODE */
 #include "Emb_L0_API.h"
#endif /* DLL_MODE */

typedef struct _AV2018_Context {
    L0_Context    *i2c;
    L0_Context     i2cObj;
    int    RF;
    int    IF;
    int    minRF;
    int    maxRF;
    int    tuner_crystal;
    int    LPF;
    int    tunerBytesCount;
    int    I2CMuxChannel;
    CONNECTION_TYPE connType;
    unsigned char tuner_log[50];
    int     rssi;
    unsigned char RXIQ_out;
    unsigned char RFLP_enabled;
} AV2018_Context;

#define AV2018_RXIQ_out_single_ended 0
#define AV2018_RXIQ_out_differential 1

/* AV2018 registers definitions */
/* This allows using the following syntax:
 to set  register foo:             AV2018_WRITE(foo, foo_on);
 to read register foo: foo_value = AV2018_READ(foo);

 The above macros handle the necessary reading/masing/shifting for any register from 1 to 32 bits. (Casting may be required for 32 bit signed registers)

 */
#define int_ADDRESS  0x00
#define int_OFFSET   0
#define int_NBBIT    7
#define int_ALONE    1
#define int_SIGNED   0

#define frac_reversed_ADDRESS  0x01
#define frac_reversed_OFFSET   0
#define frac_reversed_NBBIT    17
#define frac_reversed_ALONE    0
#define frac_reversed_SIGNED   0

#define bf_ADDRESS  0x05
#define bf_OFFSET   0
#define bf_NBBIT    8
#define bf_ALONE    1
#define bf_SIGNED   0
 #define bf_off   0
 #define bf_on    1

#define gc2_ADDRESS  0x08
#define gc2_OFFSET   3
#define gc2_NBBIT    4
#define gc2_ALONE    0
#define gc2_SIGNED   0
 #define gc2_0_0_dB    0
 #define gc2_1_5_dB    1
 #define gc2_3_0_dB    2
 #define gc2_4_5_dB    3
 #define gc2_6_0_dB    4
 #define gc2_7_5_dB    5
 #define gc2_9_0_dB    6
 #define gc2_10_5_dB   7
 #define gc2_15_5_dB   8

#define pgaout_cs_ADDRESS  0x08
#define pgaout_cs_OFFSET   0
#define pgaout_cs_NBBIT    2
#define pgaout_cs_ALONE    0
#define pgaout_cs_SIGNED   0
  #define pgaout_cs_0_5_mA  0
  #define pgaout_cs_1_0_mA  1
  #define pgaout_cs_1_5_mA  2
  #define pgaout_cs_2_0_mA  3

#define xocore_ct_ADDRESS  0x09
#define xocore_ct_OFFSET   6
#define xocore_ct_NBBIT    2
#define xocore_ct_ALONE    0
#define xocore_ct_SIGNED   0
 #define xocore_ct_min_current  0
 #define xocore_ct_max_current  3

#define bwlf_ADDRESS  0x0b
#define bwlf_OFFSET   1
#define bwlf_NBBIT    1
#define bwlf_ALONE    0
#define bwlf_SIGNED   0
 #define bwlf_unlock   0
 #define bwlf_lock     1

#define chlf_ADDRESS  0x0b
#define chlf_OFFSET   0
#define chlf_NBBIT    1
#define chlf_ALONE    0
#define chlf_SIGNED   0
 #define chlf_unlock   0
 #define chlf_lock    1

#define xocore_ena_ADDRESS  0x0c
#define xocore_ena_OFFSET   7
#define xocore_ena_NBBIT    1
#define xocore_ena_ALONE    0
#define xocore_ena_SIGNED   0

#define rflp_ena_ADDRESS  xocore_ena_ADDRESS
#define rflp_ena_OFFSET   6
#define rflp_ena_NBBIT    1
#define rflp_ena_ALONE    0
#define rflp_ena_SIGNED   0

#define pd_soft_ADDRESS  xocore_ena_ADDRESS
#define pd_soft_OFFSET   5
#define pd_soft_NBBIT    1
#define pd_soft_ALONE    0
#define pd_soft_SIGNED   0
 #define pd_soft_power_up      0
 #define pd_soft_power_down    1

#define ft_block_ADDRESS  0x25
#define ft_block_OFFSET   2
#define ft_block_NBBIT    1
#define ft_block_ALONE    0
#define ft_block_SIGNED   0

#define ft_en_ADDRESS  ft_block_ADDRESS
#define ft_en_OFFSET   1
#define ft_en_NBBIT    1
#define ft_en_ALONE    0
#define ft_en_SIGNED   0

#define ft_hold_ADDRESS  ft_block_ADDRESS
#define ft_hold_OFFSET   0
#define ft_hold_NBBIT    1
#define ft_hold_ALONE    0
#define ft_hold_SIGNED   0

#ifdef RWTRACES
  #define AV2018_WRITE(context, register, v ) L0_WriteRegisterTrace (context->i2c, #register, #v, register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE, v)
  #define AV2018_READ(context,  register)     L0_ReadRegisterTrace  (context->i2c, #register,     register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_SIGNED)
#else
  #define AV2018_WRITE(context, register, v ) L0_WriteRegister      (context->i2c,                register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE, v)
  #define AV2018_READ(context, register)      L0_ReadRegister       (context->i2c,                register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE)
#endif

int    L1_RF_AV2018_Wakeup         (AV2018_Context *context);
int    L1_RF_AV2018_Standby        (AV2018_Context *context);
void   L1_RF_AV2018_Init           (AV2018_Context *context, unsigned int add);
int    L1_RF_AV2018_InitAfterReset (AV2018_Context *context);
int    L1_RF_AV2018_Tune           (AV2018_Context *context, int rf);
int    L1_RF_AV2018_ClockOn        (AV2018_Context *context);
int    L1_RF_AV2018_ClockOff       (AV2018_Context *context);
int    L1_RF_AV2018_Get_Infos      (AV2018_Context *context, char** infos);
const char*  L1_RF_AV2018_TAG_TEXT       (void);
int    L1_RF_AV2018_LPF            (AV2018_Context *context, int lpf_khz);
int    L1_RF_AV2018_Get_IF         (AV2018_Context *context);
int    L1_RF_AV2018_LoopThrough    (AV2018_Context *context, int loop_through_enabled);
int    L1_RF_AV2018_Get_RF         (AV2018_Context *context);
int    L1_RF_AV2018_Get_minRF      (AV2018_Context *context);
int    L1_RF_AV2018_Get_maxRF      (AV2018_Context *context);
int    L1_RF_AV2018_RSSI           (AV2018_Context *context, int if_agc);

#endif /* _L1_RF_AV2018_API_H_ */
