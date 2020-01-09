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
#ifndef _A8297_L1_API_H_
#define _A8297_L1_API_H_

#include "Silabs_L0_API.h"

#ifdef RWTRACES
    #define A8297_WRITE(register, v )    L0_WriteRegisterTrace         (context->i2c, #register, #v, register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE, v)
#else
    #define A8297_WRITE(register, v )    L0_WriteRegister              (context->i2c,                register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE, v)
#endif

#define A8297_SUPPLY_OFF 0
#define A8297_SUPPLY_ON  1

#define A8297_HORIZONTAL 0
#define A8297_VERTICAL   1

typedef struct A8297_Context {
  L0_Context    *i2c;
  L0_Context     i2cObj;
  unsigned char LNB2;
  /* Controls */
  unsigned char  vsel_voltage;
  unsigned char  lnb_output;
  /* statuses */
  unsigned char lnb_status;
  unsigned char overcurrent;
  unsigned char power;
  unsigned char undervoltage;
  unsigned char thermal_shutdown;
  unsigned char charge_pump;
  unsigned char tone_detect;
  unsigned char trims;

  unsigned char  A8297_BYTES_Array[4];
  unsigned char *A8297_BYTES;
} A8297_Context;

void         L1_A8297_Init           (A8297_Context *context, unsigned int add);
unsigned int L1_A8297_Index          (A8297_Context *context, unsigned int index);
void         L1_A8297_MatchBytes     (A8297_Context *LNB1, A8297_Context *LNB2);
unsigned int L1_A8297_InitAfterReset (A8297_Context *context);
void         L1_A8297_Supply         (A8297_Context *context, unsigned char supply_off_on);
void         L1_A8297_Polarity       (A8297_Context *context, unsigned char pola_13_18);
void         L1_A8297_Voltage        (A8297_Context *context, unsigned char voltage);
char        *L1_A8297_TAG_Text       (void);

#ifdef    Layer1_A8297

 /* vsel_voltage               (0000h) */
 #define    vsel_voltage_ADDRESS           0
 #define    vsel_voltage_OFFSET            0
 #define    vsel_voltage_NBBIT             3
 #define    vsel_voltage_ALONE             0
 #define    vsel_voltage_SIGNED            0
  #define           vsel_voltage_13333_mV    0
  #define           vsel_voltage_13667_mV    1
  #define           vsel_voltage_14000_mV    2
  #define           vsel_voltage_14333_mV    3
  #define           vsel_voltage_18667_mV    4
  #define           vsel_voltage_19000_mV    5
  #define           vsel_voltage_19667_mV    6
  #define           vsel_voltage_20000_mV    7
  /* lnb_output               (0000h) */
 #define    lnb_output_ADDRESS           0
 #define    lnb_output_OFFSET            3
 #define    lnb_output_NBBIT             1
 #define    lnb_output_ALONE             0
 #define    lnb_output_SIGNED            0
  #define           lnb_output_disabled                  0
  #define           lnb_output_enabled                   1

 /*---------------------------------------*/
 /*   A8297 status registers              */
 /*---------------------------------------*/
  /* lnb_status               (0000h) */
 #define    lnb_status_ADDRESS           0
 #define    lnb_status_OFFSET            0
 #define    lnb_status_NBBIT             1
 #define    lnb_status_LNB2_OFFSET            1
  #define           lnb_status_enabled_no_fault       0
  #define           lnb_status_disabled_or_fault      1

  /* overcurrent               (0000h) */
 #define    overcurrent_ADDRESS           0
 #define    overcurrent_OFFSET            2
 #define    overcurrent_NBBIT             1
 #define    overcurrent_LNB2_OFFSET            1
  #define           overcurrent_above_threshold    0
  #define           overcurrent_no_error           1

  /* power              (0000h) */
 #define    power_ADDRESS           0
 #define    power_OFFSET            4
 #define    power_NBBIT             1
 #define    power_LNB2_OFFSET            1
  #define           power_within_range           0
  #define           power_out_of_range           1

  /* undervoltage               (0000h) */
 #define    undervoltage_ADDRESS           0
 #define    undervoltage_OFFSET            6
 #define    undervoltage_NBBIT             1
 #define    undervoltage_LNB2_OFFSET            0
  #define           undervoltage_within_range           0
  #define           undervoltage_out_of_range           1

  /* thermal_shutdown               (0000h) */
 #define    thermal_shutdown_ADDRESS           0
 #define    thermal_shutdown_OFFSET            7
 #define    thermal_shutdown_NBBIT             1
 #define    thermal_shutdown_LNB2_OFFSET            0
  #define           thermal_shutdown_within_range           0
  #define           thermal_shutdown_overtemperature        1

  /* charge_pump               (0001h) */
 #define    charge_pump_ADDRESS           1
 #define    charge_pump_OFFSET            2
 #define    charge_pump_NBBIT             1
 #define    charge_pump_LNB2_OFFSET            1
  #define           charge_pump_error       0
  #define           charge_pump_ok          1

  /* tone_detect               (0001h) */
 #define    tone_detect_ADDRESS           1
 #define    tone_detect_OFFSET            2
 #define    tone_detect_NBBIT             1
 #define    tone_detect_LNB2_OFFSET            1
  #define           tone_detect_no_tone     0
  #define           tone_detect_detected    1

  /* trims               (0001h) */
 #define    trims_ADDRESS           1
 #define    trims_OFFSET            4
 #define    trims_NBBIT             1
 #define    trims_LNB2_OFFSET            0
  #define           trims_above_threshold    0
  #define           trims_no_error           1

#endif /* Layer1_A8297 */

#endif /* end of _A8297_L1_API_H_ */
