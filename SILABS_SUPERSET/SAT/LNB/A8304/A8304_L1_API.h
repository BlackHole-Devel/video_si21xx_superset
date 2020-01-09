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
#ifndef _A8304_L1_API_H_
#define _A8304_L1_API_H_

#include "Silabs_L0_API.h"

#ifdef RWTRACES
    #define A8304_WRITE(register, v )    L0_WriteRegisterTrace         (context->i2c, #register, #v, register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE, v)
#else
    #define A8304_WRITE(register, v )    L0_WriteRegister              (context->i2c,                register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE, v)
#endif

#define A8304_SUPPLY_OFF 0
#define A8304_SUPPLY_ON  1

#define A8304_HORIZONTAL 0
#define A8304_VERTICAL   1

typedef struct A8304_Context {
  L0_Context    *i2c;
  L0_Context     i2cObj;
  unsigned char  vsel_voltage;
  unsigned char  lnb_output;
  unsigned char  tone_mode;
  unsigned char  ocp_25;
  unsigned char  sink_dis;
  unsigned char  DIS;
  unsigned char  CPOK;
  unsigned char  OCP;
  unsigned char  PNG;
  unsigned char  TSD;
  unsigned char  UVLO;
  unsigned char A8304_BYTES[2];
} A8304_Context;

void  L1_A8304_Init           (A8304_Context *context, unsigned int add);
int   L1_A8304_InitAfterReset (A8304_Context *context);
void  L1_A8304_Supply         (A8304_Context *context, unsigned char supply_off_on);
void  L1_A8304_Polarity       (A8304_Context *context, unsigned char pola_13_18);
void  L1_A8304_Voltage        (A8304_Context *context, unsigned char voltage);
char *L1_A8304_TAG_Text       (void);

#ifdef    Layer1_A8304

 /* vsel_voltage               (0000h) */
 #define    vsel_voltage_ADDRESS           0
 #define    vsel_voltage_OFFSET            0
 #define    vsel_voltage_NBBIT             4
 #define    vsel_voltage_ALONE             0
 #define    vsel_voltage_SIGNED            0
  #define           vsel_voltage_13333_mV    2
  #define           vsel_voltage_13667_mV    3
  #define           vsel_voltage_14333_mV    5
  #define           vsel_voltage_15667_mV    7
  #define           vsel_voltage_18667_mV    11
  #define           vsel_voltage_19000_mV    12
  #define           vsel_voltage_19333_mV    13
  #define           vsel_voltage_19667_mV    14
  /* lnb_output               (0000h) */
 #define    lnb_output_ADDRESS           0
 #define    lnb_output_OFFSET            4
 #define    lnb_output_NBBIT             1
 #define    lnb_output_ALONE             0
 #define    lnb_output_SIGNED            0
  #define           lnb_output_disabled                  0
  #define           lnb_output_enabled                   1
 /* tone_mode                   (0000h) */
 #define    tone_mode_ADDRESS               0
 #define    tone_mode_OFFSET                5
 #define    tone_mode_NBBIT                 1
 #define    tone_mode_ALONE                 0
 #define    tone_mode_SIGNED                0
  #define           tone_mode_22_khz_input                1
  #define           tone_mode_envelop                     0
 /* ocp_25                   (0000h) */
 #define    ocp_25_ADDRESS               0
 #define    ocp_25_OFFSET                6
 #define    ocp_25_NBBIT                 1
 #define    ocp_25_ALONE                 0
 #define    ocp_25_SIGNED                0
 /* sink_dis                   (0000h) */
 #define    sink_dis_ADDRESS               0
 #define    sink_dis_OFFSET                7
 #define    sink_dis_NBBIT                 1
 #define    sink_dis_ALONE                 0
 #define    sink_dis_SIGNED                0
  #define           sink_dis_disable_internal_sinks 1
  #define           sink_dis_enable_internal_sinks  0

#endif /* Layer1_A8304 */

#endif /* end of _A8304_L1_API_H_ */
