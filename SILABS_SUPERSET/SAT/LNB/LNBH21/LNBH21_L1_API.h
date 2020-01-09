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
#ifndef _LNBH21_L1_API_H_
#define _LNBH21_L1_API_H_

#include "Silabs_L0_API.h"

#ifdef RWTRACES
    #define LNBH21_WRITE(register, v )    L0_WriteRegisterTrace         (context->i2c, #register, #v, register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE, v)
#else
    #define LNBH21_WRITE(register, v )    L0_WriteRegister              (context->i2c,                register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE, v)
#endif

#define LNBH21_SUPPLY_OFF 0
#define LNBH21_SUPPLY_ON  1

#define LNBH21_HORIZONTAL 0
#define LNBH21_VERTICAL   1

typedef struct LNBH21_Context {
  L0_Context    *i2c;
  L0_Context     i2cObj;
  unsigned char  current_limiting;
  unsigned char  transmit_receive;
  unsigned char  tone_source;
  unsigned char  long_line_compensation;
  unsigned char  polarisation;
  unsigned char  lnbh_enable;
  unsigned char  power_block;
  unsigned char  overload;
} LNBH21_Context;

void  L1_LNBH21_Init           (LNBH21_Context *context, unsigned int add);
int   L1_LNBH21_InitAfterReset (LNBH21_Context *context);
void  L1_LNBH21_Supply         (LNBH21_Context *context, unsigned char supply_off_on);
void  L1_LNBH21_Polarity       (LNBH21_Context *context, unsigned char pola_13_18);
void  L1_LNBH21_Voltage        (LNBH21_Context *context, unsigned char voltage);
char *L1_LNBH21_TAG_Text       (void);

#ifdef    Layer1_lnbh21

 /* current_limiting               (0000h) */
 #define    current_limiting_ADDRESS           0
 #define    current_limiting_OFFSET            7
 #define    current_limiting_NBBIT             1
 #define    current_limiting_ALONE             0
 #define    current_limiting_SIGNED            0
  #define           current_limiting_static                    0
  #define           current_limiting_dynamic                   1
  /* transmit_receive               (0000h) */
 #define    transmit_receive_ADDRESS           0
 #define    transmit_receive_OFFSET            6
 #define    transmit_receive_NBBIT             1
 #define    transmit_receive_ALONE             0
 #define    transmit_receive_SIGNED            0
  #define           transmit_receive_reception                 0
  #define           transmit_receive_transmission              1
 /* tone_source                    (0000h) */
 #define    tone_source_ADDRESS                0
 #define    tone_source_OFFSET                 5
 #define    tone_source_NBBIT                  1
 #define    tone_source_ALONE                  0
 #define    tone_source_SIGNED                 0
  #define           tone_source_dsqin                          0
  #define           tone_source_internal                       1
 /* long_line_compensation         (0000h) */
 #define    long_line_compensation_ADDRESS     0
 #define    long_line_compensation_OFFSET      4
 #define    long_line_compensation_NBBIT       1
 #define    long_line_compensation_ALONE       0
 #define    long_line_compensation_SIGNED      0
  #define           long_line_compensation_off                 0
  #define           long_line_compensation_on                  1
 /* polarisation                   (0000h) */
 #define    polarisation_ADDRESS               0
 #define    polarisation_OFFSET                3
 #define    polarisation_NBBIT                 1
 #define    polarisation_ALONE                 0
 #define    polarisation_SIGNED                0
  #define           polarisation_13_volts_v                    0
  #define           polarisation_18_volts_h                    1
 /* lnbh_enable                    (0000h) */
 #define    lnbh_enable_ADDRESS                0
 #define    lnbh_enable_OFFSET                 2
 #define    lnbh_enable_NBBIT                  1
 #define    lnbh_enable_ALONE                  0
 #define    lnbh_enable_SIGNED                 0
  #define           lnbh_enable_disabled                       0
  #define           lnbh_enable_enabled                        1
 /* power_block                    (0000h) */
 #define    power_block_ADDRESS                0
 #define    power_block_OFFSET                 1
 #define    power_block_NBBIT                  1
 #define    power_block_ALONE                  0
 #define    power_block_SIGNED                 0
  #define           power_block_normal_operation               0
  #define           power_block_disabled                       1
 /* overload                       (0000h) */
 #define    overload_ADDRESS                   0
 #define    overload_OFFSET                    0
 #define    overload_NBBIT                     1
 #define    overload_ALONE                     0
 #define    overload_SIGNED                    0
  #define           overload_normal_operation                  0
  #define           overload_protection_mode                   1

#endif /* Layer1_lnbh21 */

#endif /* end of _LNBH21_L1_API_H_ */
