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
#ifndef   LNBH26_L1_API_H
#define   LNBH26_L1_API_H

#include "Silabs_L0_API.h"

typedef struct LNBH26_Context {
  L0_Context    *i2c;
  L0_Context     i2cObj;
  unsigned char a_b;
  unsigned char supply;
  unsigned char polarization;
  unsigned char vout;
  unsigned char vout_horizontal;
  unsigned char vout_vertical;
  unsigned char diseqc_mode;
  unsigned char status_overload;
  unsigned char status_low_vout_voltage;
  unsigned char status_overcurrent;
  unsigned char status_overtemperature;
  unsigned char status_low_vcc;
  unsigned char status_22khz_tone_detection;
  unsigned char status_22khz_tone_shape;
  unsigned char status_low_vout_current;
} LNBH26_Context;

#define LNBH26_SUPPLY_OFF 0
#define LNBH26_SUPPLY_ON  1

#define LNBH26_HORIZONTAL 0
#define LNBH26_VERTICAL   1

#define LNBH26_DISEQC_MODE_22_KHZ     0
#define LNBH26_DISEQC_MODE_ENVELOPE   1

#define LNBH26_CONTEXT_A 0
#define LNBH26_CONTEXT_B 1

#ifdef RWTRACES
    #define LNBH26_WRITE(register,v)    L0_WriteRegisterTrace         (context->i2c, #register, #v, register##_ADDRESS, register##_OFFSET + (context->a_b*register##_SHIFT), register##_NBBIT, register##_ALONE, v)
    #define LNBH26_READ(register)       L0_ReadRegisterTrace          (context->i2c, #register,     register##_ADDRESS, register##_OFFSET + (context->a_b*register##_SHIFT), register##_NBBIT, register##_SIGNED)
#else
    #define LNBH26_WRITE(register, v )  L0_WriteRegister              (context->i2c,                register##_ADDRESS, register##_OFFSET + (context->a_b*register##_SHIFT), register##_NBBIT, register##_ALONE, v)
    #define LNBH26_READ(register)       L0_ReadRegister               (context->i2c,                register##_ADDRESS, register##_OFFSET + (context->a_b*register##_SHIFT), register##_NBBIT, register##_SIGNED)
#endif

  #ifdef    Layer1_LNBH26

#define   LNBH26_setup_registers
#ifdef    LNBH26_setup_registers
 /* vout                           (0002h) */
 #define    vout_ADDRESS                       2
 #define    vout_OFFSET                        0
 #define    vout_NBBIT                         4
 #define    vout_SHIFT                         4
 #define    vout_ALONE                         0
 #define    vout_SIGNED                        0
  #define           vout_00000_mv                              0
  #define           vout_13000_mv                              1
  #define           vout_13333_mv                              2
  #define           vout_13667_mv                              3
  #define           vout_14000_mv                              4
  #define           vout_14333_mv                              5
  #define           vout_14667_mv                              6
  #define           vout_15000_mv                              7
  #define           vout_18150_mv                              8
  #define           vout_18483_mv                              9
  #define           vout_18817_mv                             10
  #define           vout_19150_mv                             11
  #define           vout_19483_mv                             12
  #define           vout_19817_mv                             13
  #define           vout_20150_mv                             14
  #define           vout_20483_mv                             15
 /* tone                           (0003h) */
 #define    tone_ADDRESS                       3
 #define    tone_OFFSET                        0
 #define    tone_NBBIT                         1
 #define    tone_SHIFT                         4
 #define    tone_ALONE                         0
 #define    tone_SIGNED                        0
  #define           tone_enabled_via_dsqin                     1
  #define           tone_disabled                              0
 /* low_power_mode                 (0003h) */
 #define    low_power_mode_ADDRESS             3
 #define    low_power_mode_OFFSET              1
 #define    low_power_mode_NBBIT               1
 #define    low_power_mode_SHIFT               4
 #define    low_power_mode_ALONE               0
 #define    low_power_mode_SIGNED              0
  #define           low_power_mode_activated                   1
  #define           low_power_mode_deactivated                 0
 /* dsqin_mode                     (0003h) */
 #define    dsqin_mode_ADDRESS                 3
 #define    dsqin_mode_OFFSET                  2
 #define    dsqin_mode_NBBIT                   1
 #define    dsqin_mode_SHIFT                   4
 #define    dsqin_mode_ALONE                   0
 #define    dsqin_mode_SIGNED                  0
  #define           dsqin_mode_22_khz                          1
  #define           dsqin_mode_envelope                        0
 /* current_limit                  (0004h) */
 #define    current_limit_ADDRESS              4
 #define    current_limit_OFFSET               0
 #define    current_limit_NBBIT                1
 #define    current_limit_SHIFT                4
 #define    current_limit_ALONE                0
 #define    current_limit_SIGNED               0
  #define           current_limit_lower_current_range          1
  #define           current_limit_default_range                0
 /* isw_limit                      (0004h) */
 #define    isw_limit_ADDRESS                  4
 #define    isw_limit_OFFSET                   1
 #define    isw_limit_NBBIT                    1
 #define    isw_limit_SHIFT                    4
 #define    isw_limit_ALONE                    0
 #define    isw_limit_SIGNED                   0
  #define           isw_limit_2500_ma                          1
  #define           isw_limit_4000_ma                          0
 /* pcl_limit                      (0004h) */
 #define    pcl_limit_ADDRESS                  4
 #define    pcl_limit_OFFSET                   2
 #define    pcl_limit_NBBIT                    1
 #define    pcl_limit_SHIFT                    4
 #define    pcl_limit_ALONE                    0
 #define    pcl_limit_SIGNED                   0
  #define           pcl_limit_deactivated                      1
  #define           pcl_limit_activated                        0
 /* pcl_timer                      (0004h) */
 #define    pcl_timer_ADDRESS                  4
 #define    pcl_timer_OFFSET                   3
 #define    pcl_timer_NBBIT                    1
 #define    pcl_timer_SHIFT                    4
 #define    pcl_timer_ALONE                    0
 #define    pcl_timer_SIGNED                   0
  #define           pcl_timer_180_ms                           1
  #define           pcl_timer_90_ms                            0
 /* imon                           (0005h) */
 #define    imon_ADDRESS                       5
 #define    imon_OFFSET                        0
 #define    imon_NBBIT                         1
 #define    imon_SHIFT                         4
 #define    imon_ALONE                         0
 #define    imon_SIGNED                        0
  #define           imon_enabled                               1
  #define           imon_disabled                              0
 /* overload_removal               (0005h) */
 #define    overload_removal_ADDRESS           5
 #define    overload_removal_OFFSET            3
 #define    overload_removal_NBBIT             1
 #define    overload_removal_SHIFT             0
 #define    overload_removal_ALONE             0
 #define    overload_removal_SIGNED            0
  #define           overload_removal_set_vout                  1
  #define           overload_removal_auto                      0
 /* thermal_removal                (0005h) */
 #define    thermal_removal_ADDRESS            5
 #define    thermal_removal_OFFSET             6
 #define    thermal_removal_NBBIT              1
 #define    thermal_removal_SHIFT              0
 #define    thermal_removal_ALONE              0
 #define    thermal_removal_SIGNED             0
  #define           thermal_removal_set_vout                   1
  #define           thermal_removal_auto                       0
 /* dc_dc_comp                     (0005h) */
 #define    dc_dc_comp_ADDRESS                 5
 #define    dc_dc_comp_OFFSET                  7
 #define    dc_dc_comp_NBBIT                   1
 #define    dc_dc_comp_SHIFT                   0
 #define    dc_dc_comp_ALONE                   0
 #define    dc_dc_comp_SIGNED                  0
  #define           dc_dc_comp_high_esr_caps                   1
  #define           dc_dc_comp_low_esr_caps                    0

#endif /* LNBH26_setup_registers */

#define   LNBH26_status_registers
#ifdef    LNBH26_status_registers

 /* vout_overload                  (0000h) */
 #define    vout_overload_ADDRESS              0
 #define    vout_overload_OFFSET               0
 #define    vout_overload_NBBIT                1
 #define    vout_overload_SHIFT                1
 #define    vout_overload_ALONE                0
 #define    vout_overload_SIGNED               0
  #define           vout_overload_triggered                    1
  #define           vout_overload_none                         0

 /* vout_monitor                   (0000h) */
 #define    vout_monitor_ADDRESS               0
 #define    vout_monitor_OFFSET                2
 #define    vout_monitor_NBBIT                 1
 #define    vout_monitor_SHIFT                 1
 #define    vout_monitor_ALONE                 0
 #define    vout_monitor_SIGNED                0
  #define           vout_monitor_within_specs                  0
  #define           vout_monitor_below_threshold               1

 /* pull_down_overcurrent          (0000h) */
 #define    pull_down_overcurrent_ADDRESS      0
 #define    pull_down_overcurrent_OFFSET       4
 #define    pull_down_overcurrent_NBBIT        1
 #define    pull_down_overcurrent_SHIFT        1
 #define    pull_down_overcurrent_ALONE        0
 #define    pull_down_overcurrent_SIGNED       0
  #define           pull_down_overcurrent_detected             1
  #define           pull_down_overcurrent_none                 0

 /* over_temperature               (0000h) */
 #define    over_temperature_ADDRESS           0
 #define    over_temperature_OFFSET            6
 #define    over_temperature_NBBIT             1
 #define    over_temperature_SHIFT             0
 #define    over_temperature_ALONE             0
 #define    over_temperature_SIGNED            0
  #define           over_temperature_detected                  1
  #define           over_temperature_none                      0

 /* low_input_voltage              (0000h) */
 #define    low_input_voltage_ADDRESS          0
 #define    low_input_voltage_OFFSET           7
 #define    low_input_voltage_NBBIT            1
 #define    low_input_voltage_SHIFT            0
 #define    low_input_voltage_ALONE            0
 #define    low_input_voltage_SIGNED           0
  #define           low_input_voltage_detected                 1
  #define           low_input_voltage_none                     0

 /* tone_on_detin                  (0001h) */
 #define    tone_on_detin_ADDRESS              1
 #define    tone_on_detin_OFFSET               0
 #define    tone_on_detin_NBBIT                1
 #define    tone_on_detin_SHIFT                1
 #define    tone_on_detin_ALONE                0
 #define    tone_on_detin_SIGNED               0
  #define           tone_on_detin_detected                     1
  #define           tone_on_detin_none                         0

 /* tone_shape                 (0001h) */
 #define    tone_shape_ADDRESS             1
 #define    tone_shape_OFFSET              2
 #define    tone_shape_NBBIT               1
 #define    tone_shape_SHIFT               1
 #define    tone_shape_ALONE               0
 #define    tone_shape_SIGNED              0
  #define           tone_shape_out_of_specs                1
  #define           tone_shape_within_specs                0

 /* low_vout_current               (0001h) */
 #define    low_vout_current_ADDRESS           1
 #define    low_vout_current_OFFSET            4
 #define    low_vout_current_NBBIT             1
 #define    low_vout_current_SHIFT             1
 #define    low_vout_current_ALONE             0
 #define    low_vout_current_SIGNED            0
  #define           low_vout_current_detected                  1
  #define           low_vout_current_none                      0
 #endif /* Layer1_LNBH26 */

#endif /* LNBH26_status_registers */

void  L1_LNBH26_Init           (LNBH26_Context *context, unsigned int add);
int   L1_LNBH26_InitAfterReset (LNBH26_Context *context);
void  L1_LNBH26_Supply         (LNBH26_Context *context, unsigned char supply_off_on);
void  L1_LNBH26_Polarity       (LNBH26_Context *context, unsigned char horizontal_vertical);
void  L1_LNBH26_Voltage        (LNBH26_Context *context, unsigned char voltage);

int   L1_LNBH26_Status         (LNBH26_Context *context);

char *L1_LNBH26_ContextInfo    (LNBH26_Context *context);
char *L1_LNBH26_StatusInfo     (LNBH26_Context *context);

char *L1_LNBH26_TAG_Text       (void);

#endif /* LNBH26_L1_API_H */
