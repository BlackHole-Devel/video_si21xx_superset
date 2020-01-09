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
#ifndef _A8302_L1_API_H_
#define _A8302_L1_API_H_

#include "Silabs_L0_API.h"

#ifdef RWTRACES
  #define A8302_WRITE_REG(register, v )    L0_WriteRegisterTrace  (context->i2c, #register, #v, register##_ADDRESS + (context->LNB2)*register##_LNB2_OFFSET, register##_OFFSET, register##_NBBIT, 0, v)
  #define A8302_READ_REG (register    )    L0_WriteRegisterRead   (context->i2c, #register, #v, register##_ADDRESS, register##_OFFSET + (context->LNB2)*register##_LNB2_OFFSET , register##_NBBIT, 0)
#else
  #define A8302_WRITE_REG(register, v )    L0_WriteRegister       (context->i2c,                register##_ADDRESS + (context->LNB2)*register##_LNB2_OFFSET, register##_OFFSET, register##_NBBIT, 0, v)
  #define A8302_READ_REG (register    )    L0_WriteRegister       (context->i2c,                register##_ADDRESS, register##_OFFSET  + (context->LNB2)*register##_LNB2_OFFSET, register##_NBBIT, 0)
#endif

#define A8302_SUPPLY_OFF 0
#define A8302_SUPPLY_ON  1

#define A8302_HORIZONTAL 0
#define A8302_VERTICAL   1

typedef struct A8302_Context {
  L0_Context    *i2c;
  L0_Context     i2cObj;
  unsigned char LNB2;
  unsigned char tone_mode;
  unsigned char overcurrent_disable_timer;
  unsigned char EPF_setting_delay;
  unsigned char frequency;
  unsigned char compensation_network;
  unsigned char fault_restart_mode;
  unsigned char sink;
  unsigned char vsel_voltage;
  unsigned char lnb_output;
  unsigned char bump_up;
  unsigned char SWM_mode;
  unsigned char tone_delay;

  unsigned char lnb_status;
  unsigned char overcurrent;
  unsigned char power;
  unsigned char undervoltage;
  unsigned char thermal_shutdown;
  unsigned char charge_pump;
  unsigned char tone_detect;
  unsigned char EPF_warning;
  unsigned char trims;
  unsigned char cable_boost;

  unsigned char A8302_BYTES[5];

} A8302_Context;

void          L1_A8302_Init           (A8302_Context *context, unsigned int add);
unsigned int  L1_A8302_Index          (A8302_Context *context, unsigned int index);
unsigned int  L1_A8302_InitAfterReset (A8302_Context *context);
void          L1_A8302_Supply         (A8302_Context *context, unsigned char supply_off_on);
void          L1_A8302_Polarity       (A8302_Context *context, unsigned char pola_13_18);
void          L1_A8302_Voltage        (A8302_Context *context, unsigned char voltage);
char *        L1_A8302_TAG_Text       (void);

#ifdef    Layer1_A8302


 /*---------------------------------------*/
 /*   A8302 control registers             */
 /*---------------------------------------*/
 /* tone_mode                   (0000h) */
 #define    tone_mode_ADDRESS               0
 #define    tone_mode_OFFSET                0
 #define    tone_mode_NBBIT                 1
 #define    tone_mode_LNB2_OFFSET           0
  #define           tone_mode_envelop                     0
  #define           tone_mode_22_khz_input                1

  /* overcurrent_disable_timer                       (0000h) */
 #define    overcurrent_disable_timer_ADDRESS                   0
 #define    overcurrent_disable_timer_OFFSET                    1
 #define    overcurrent_disable_timer_NBBIT                     1
 #define    overcurrent_disable_timer_LNB2_OFFSET                    0
  #define           overcurrent_disable_timer_28_ms               0
  #define           overcurrent_disable_timer_45_ms               1

  /* EPF_setting_delay                       (0000h) */
 #define    EPF_setting_delay_ADDRESS                   0
 #define    EPF_setting_delay_OFFSET                    2
 #define    EPF_setting_delay_NBBIT                     2
 #define    EPF_setting_delay_LNB2_OFFSET                    0
  #define           EPF_setting_delay_0_0_ms                0
  #define           EPF_setting_delay_11_5_ms               1
  #define           EPF_setting_delay_46_0_ms               2
  #define           EPF_setting_delay_92_0_ms               3

  /* frequency                       (0000h) */
 #define    frequency_ADDRESS                   0
 #define    frequency_OFFSET                    4
 #define    frequency_NBBIT                     1
 #define    frequency_LNB2_OFFSET                    0
  #define           frequency_563_khz                0
  #define           frequency_939_khz                1

  /* compensation_network                       (0000h) */
 #define    compensation_network_ADDRESS                   0
 #define    compensation_network_OFFSET                    4
 #define    compensation_network_NBBIT                     1
 #define    compensation_network_LNB2_OFFSET                    0
  #define           compensation_network_ceramic                0
  #define           compensation_network_electrolytic           1

  /* fault_restart_mode                       (0000h) */
 #define    fault_restart_mode_ADDRESS                   0
 #define    fault_restart_mode_OFFSET                    6
 #define    fault_restart_mode_NBBIT                     1
 #define    fault_restart_mode_LNB2_OFFSET                    0
  #define           fault_restart_mode_latch                0
  #define           fault_restart_mode_auto                 1

  /* sink                       (0000h) */
 #define    sink_ADDRESS                   0
 #define    sink_OFFSET                    7
 #define    sink_NBBIT                     1
 #define    sink_LNB2_OFFSET                    0
  #define           sink_disabled             0
  #define           sink_enabled              1

 /* vsel_voltage               (0000h) */
 #define    vsel_voltage_ADDRESS           0
 #define    vsel_voltage_OFFSET            0
 #define    vsel_voltage_NBBIT             3
 #define    vsel_voltage_LNB2_OFFSET            1
  #define           vsel_voltage_13333_mV      2
  #define           vsel_voltage_13667_mV      3
  #define           vsel_voltage_14333_mV      5
  #define           vsel_voltage_15667_mV      7
  #define           vsel_voltage_18667_mV    0xb
  #define           vsel_voltage_19000_mV    0xc
  #define           vsel_voltage_19333_mV    0xd
  #define           vsel_voltage_19667_mV    0xe

  /* lnb_output               (0001h) */
 #define    lnb_output_ADDRESS           1
 #define    lnb_output_OFFSET            3
 #define    lnb_output_NBBIT             1
 #define    lnb_output_LNB2_OFFSET            1
  #define           lnb_output_disabled                  0
  #define           lnb_output_enabled                   1

  /* bump_up               (0001h) */
 #define    bump_up_ADDRESS           1
 #define    bump_up_OFFSET            5
 #define    bump_up_NBBIT             1
 #define    bump_up_LNB2_OFFSET            1
  #define           bump_up_off                  0
  #define           bump_up_on                   1

  /* SWM_mode               (0001h) */
 #define    SWM_mode_ADDRESS           1
 #define    SWM_mode_OFFSET            5
 #define    SWM_mode_NBBIT             1
 #define    SWM_mode_LNB2_OFFSET            1
  #define           SWM_mode_70_ma                  0
  #define           SWM_mode_10_ma                  1

  /* tone_delay               (0001h) */
 #define    tone_delay_ADDRESS           1
 #define    tone_delay_OFFSET            5
 #define    tone_delay_NBBIT             1
 #define    tone_delay_LNB2_OFFSET            1
  #define           tone_delay_42_us                  0
  #define           tone_delay_0_us                   1




 /*---------------------------------------*/
 /*   A8302 status registers              */
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
 #define    undervoltage_LNB2_OFFSET            1
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

  /* EPF_warning               (0001h) */
 #define    EPF_warning_ADDRESS           1
 #define    EPF_warning_OFFSET            4
 #define    EPF_warning_NBBIT             1
 #define    EPF_warning_LNB2_OFFSET            0
  #define           EPF_warning_power_ok              0
  #define           EPF_warning_vin_below_threshold   1

  /* trims               (0001h) */
 #define    trims_ADDRESS           1
 #define    trims_OFFSET            5
 #define    trims_NBBIT             1
 #define    trims_LNB2_OFFSET            0
  #define           trims_above_threshold    0
  #define           trims_no_error           1

  /* cable_boost               (0001h) */
 #define    cable_boost_ADDRESS           1
 #define    cable_boost_OFFSET            5
 #define    cable_boost_NBBIT             1
 #define    cable_boost_LNB2_OFFSET            0
  #define           cable_boost_lnb_connected      0
  #define           cable_boost_lnb_disconnected   1


#endif /* Layer1_A8302 */

#endif /* end of _A8302_L1_API_H_ */
