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
#ifndef _A8293_L1_API_H_
#define _A8293_L1_API_H_

#include "Silabs_L0_API.h"

#ifdef RWTRACES
    #define A8293_WRITE(register, v )    L0_WriteRegisterTrace         (context->i2c, #register, #v, register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE, v)
#else
    #define A8293_WRITE(register, v )    L0_WriteRegister              (context->i2c,                register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE, v)
#endif

#define A8293_SUPPLY_OFF 0
#define A8293_SUPPLY_ON  1

#define A8293_HORIZONTAL 0
#define A8293_VERTICAL   1

typedef struct A8293_Context {
  L0_Context    *i2c;
  L0_Context     i2cObj;
  unsigned char  vsel_voltage;
  unsigned char  overcurrent_disable_timer;
  unsigned char  lnb_output;
  unsigned char  address_b0;
  unsigned char  tone_mode;
  unsigned char  tone_gate;
  unsigned char  address_b1;
  unsigned char  OCP;
  unsigned char  PNG;
  unsigned char  TSD;
  unsigned char  VUV;
  unsigned char A8293_BYTES[4];
} A8293_Context;

void  L1_A8293_Init           (A8293_Context *context, unsigned int add);
int   L1_A8293_InitAfterReset (A8293_Context *context);
void  L1_A8293_Supply         (A8293_Context *context, unsigned char supply_off_on);
void  L1_A8293_Polarity       (A8293_Context *context, unsigned char pola_13_18);
void  L1_A8293_Voltage        (A8293_Context *context, unsigned char voltage);
char *L1_A8293_TAG_Text       (void);

#ifdef    Layer1_A8293

 /* vsel_voltage               (0000h) */
 #define    vsel_voltage_ADDRESS           0
 #define    vsel_voltage_OFFSET            0
 #define    vsel_voltage_NBBIT             4
 #define    vsel_voltage_ALONE             0
 #define    vsel_voltage_SIGNED            0
  #define           vsel_voltage_12709_mV    0
  #define           vsel_voltage_13042_mV    1
  #define           vsel_voltage_13375_mV    2
  #define           vsel_voltage_14042_mV    4
  #define           vsel_voltage_15042_mV    7
  #define           vsel_voltage_18042_mV    8
  #define           vsel_voltage_18709_mV    10
  #define           vsel_voltage_19042_mV    11
   /* overcurrent_disable_timer                       (0000h) */
 #define    overcurrent_disable_timer_ADDRESS                   0
 #define    overcurrent_disable_timer_OFFSET                    4
 #define    overcurrent_disable_timer_NBBIT                     1
 #define    overcurrent_disable_timer_ALONE                     0
 #define    overcurrent_disable_timer_SIGNED                    0
  #define           overcurrent_disable_timer_disabled                 0
  #define           overcurrent_disable_timer_enabled                  1
  /* lnb_output               (0000h) */
 #define    lnb_output_ADDRESS           0
 #define    lnb_output_OFFSET            5
 #define    lnb_output_NBBIT             1
 #define    lnb_output_ALONE             0
 #define    lnb_output_SIGNED            0
  #define           lnb_output_disabled                  0
  #define           lnb_output_enabled                   1
 /* address_b0                    (0000h) */
 #define    address_b0_ADDRESS                0
 #define    address_b0_OFFSET                 6
 #define    address_b0_NBBIT                  2
 #define    address_b0_ALONE                  0
 #define    address_b0_SIGNED                 0
  #define    address_b0_byte0                  0
 /* tone_mode                   (0001h) */
 #define    tone_mode_ADDRESS               1
 #define    tone_mode_OFFSET                0
 #define    tone_mode_NBBIT                 1
 #define    tone_mode_ALONE                 0
 #define    tone_mode_SIGNED                0
  #define           tone_mode_22_khz_input                0
  #define           tone_mode_envelop                     1
 /* tone_gate                   (0001h) */
 #define    tone_gate_ADDRESS               1
 #define    tone_gate_OFFSET                1
 #define    tone_gate_NBBIT                 1
 #define    tone_gate_ALONE                 0
 #define    tone_gate_SIGNED                0
  #define           tone_gate_tone_to_0                   0
  #define           tone_gate_tone_on                     1
 /* address_b1                    (0000h) */
 #define    address_b1_ADDRESS                1
 #define    address_b1_OFFSET                 6
 #define    address_b1_NBBIT                  2
 #define    address_b1_ALONE                  0
 #define    address_b1_SIGNED                 0
  #define    address_b1_byte1                  2

#endif /* Layer1_A8293 */

#endif /* end of _A8293_L1_API_H_ */
