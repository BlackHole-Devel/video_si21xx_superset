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
#ifndef   LNBH29_L1_API_H
#define   LNBH29_L1_API_H

#include "Silabs_L0_API.h"

typedef struct LNBH29_Context {
  L0_Context    *i2c;
  L0_Context     i2cObj;
  unsigned char supply;
  unsigned char polarization;
  unsigned char vout;
  unsigned char vout_horizontal;
  unsigned char vout_vertical;
  unsigned char status_overload;
  unsigned char status_low_vout_voltage;
  unsigned char status_overcurrent;
  unsigned char status_overtemperature;
  unsigned char status_low_vcc;
} LNBH29_Context;

#define LNBH29_SUPPLY_OFF 0
#define LNBH29_SUPPLY_ON  1

#define LNBH29_HORIZONTAL 0
#define LNBH29_VERTICAL   1

#define LNBH29_DISEQC_MODE_22_KHZ     0
#define LNBH29_DISEQC_MODE_ENVELOPE   1

#ifdef RWTRACES
    #define LNBH29_WRITE(register,v)    L0_WriteRegisterTrace         (context->i2c, #register, #v, register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE, v)
    #define LNBH29_READ(register,v)     L0_ReadRegisterTrace          (context->i2c, #register, #v, register##_ADDRESS, register##_OFFSET, register##_NBBIT)
#else
    #define LNBH29_WRITE(register, v )  L0_WriteRegister              (context->i2c,                register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE, v)
    #define LNBH29_READ(register,v)     L0_ReadRegister               (context->i2c,                register##_ADDRESS, register##_OFFSET, register##_NBBIT)
#endif

  #ifdef    Layer1_LNBH29

#define   LNBH29_setup_registers
#ifdef    LNBH29_setup_registers

 /* vout                           (0001h) */
 #define    vout_ADDRESS                       1
 #define    vout_OFFSET                        0
 #define    vout_NBBIT                         3
 #define    vout_ALONE                         0
 #define    vout_SIGNED                        0
  #define           vout_00000_mv                              0
  #define           vout_13000_mv                              1
  #define           vout_13333_mv                              2
  #define           vout_13667_mv                              3
  #define           vout_18150_mv                              5
  #define           vout_18483_mv                              6
  #define           vout_18817_mv                              7
 /* dc_dc_comp                     (0001h) */
 #define    dc_dc_comp_ADDRESS                 1
 #define    dc_dc_comp_OFFSET                  3
 #define    dc_dc_comp_NBBIT                   1
 #define    dc_dc_comp_ALONE                   0
 #define    dc_dc_comp_SIGNED                  0
  #define           dc_dc_comp_high_esr_caps                   1
  #define           dc_dc_comp_low_esr_caps                    0

#endif /* LNBH29_setup_registers */

#define   LNBH29_status_registers
#ifdef    LNBH29_status_registers

 /* vout_overload                  (0000h) */
 #define    vout_overload_ADDRESS              0
 #define    vout_overload_OFFSET               0
 #define    vout_overload_NBBIT                1
 #define    vout_overload_ALONE                0
 #define    vout_overload_SIGNED               0
  #define           vout_overload_triggered                    1
  #define           vout_overload_none                         0
 /* over_temperature               (0000h) */
 #define    over_temperature_ADDRESS           0
 #define    over_temperature_OFFSET            1
 #define    over_temperature_NBBIT             1
 #define    over_temperature_ALONE             0
 #define    over_temperature_SIGNED            0
  #define           over_temperature_detected                  1
  #define           over_temperature_none                      0
 /* vout_monitor                   (0000h) */
 #define    vout_monitor_ADDRESS               0
 #define    vout_monitor_OFFSET                2
 #define    vout_monitor_NBBIT                 1
 #define    vout_monitor_ALONE                 0
 #define    vout_monitor_SIGNED                0
  #define           vout_monitor_within_specs                  0
  #define           vout_monitor_below_threshold               1
 /* low_input_voltage              (0000h) */
 #define    low_input_voltage_ADDRESS          0
 #define    low_input_voltage_OFFSET           3
 #define    low_input_voltage_NBBIT            1
 #define    low_input_voltage_ALONE            0
 #define    low_input_voltage_SIGNED           0
  #define           low_input_voltage_detected                 1
  #define           low_input_voltage_none                     0
 /* pull_down_overcurrent          (0000h) */
 #define    pull_down_overcurrent_ADDRESS      0
 #define    pull_down_overcurrent_OFFSET       4
 #define    pull_down_overcurrent_NBBIT        1
 #define    pull_down_overcurrent_ALONE        0
 #define    pull_down_overcurrent_SIGNED       0
  #define           pull_down_overcurrent_detected             1
  #define           pull_down_overcurrent_none                 0

#endif /* LNBH29_status_registers */

#endif /* Layer1_LNBH29 */

void  L1_LNBH29_Init           (LNBH29_Context *context, unsigned int add);
int   L1_LNBH29_InitAfterReset (LNBH29_Context *context);
void  L1_LNBH29_Supply         (LNBH29_Context *context, unsigned char supply_off_on);
void  L1_LNBH29_Polarity       (LNBH29_Context *context, unsigned char horizontal_vertical);
void  L1_LNBH29_Voltage        (LNBH29_Context *context, unsigned char voltage);

int   L1_LNBH29_Status         (LNBH29_Context *context);

char *L1_LNBH29_ContextInfo    (LNBH29_Context *context);
char *L1_LNBH29_StatusInfo     (LNBH29_Context *context);

char *L1_LNBH29_TAG_Text       (void);

#endif /* LNBH29_L1_API_H */
