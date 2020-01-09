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
#ifndef _L1_RF_RDA5812_API_H_
#define _L1_RF_RDA5812_API_H_

#include "Silabs_L0_API.h"

#ifdef RWTRACES
    #define RDA5812_WRITE(register, v )    L0_WriteRegisterTrace         (context->i2c, #register, #v, register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE, v)
#else
    #define RDA5812_WRITE(register, v )    L0_WriteRegister              (context->i2c,                register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE, v)
#endif

typedef struct RDA5812_Context {
    L0_Context    *i2c;
    L0_Context     i2cObj;
    int    RF;
    int    IF;
    int    minRF;
    int    maxRF;
    double xtal;
    int    LPF;
    int    tunerBytesCount;
    int    I2CMuxChannel;
    CONNECTION_TYPE connType;
    unsigned char tuner_log[39];
    float rssi;
} RDA5812_Context;

#ifdef Layer1_RDA5812

#define RDA5812_ADDR 0x18      /* physical address of the RDA5812 on the I2c bus */

/* enable                          */
 #define    enable_ADDRESS                 0x04
 #define    enable_OFFSET                     7
 #define    enable_NBBIT                      1
 #define    enable_ALONE                      0
 #define    enable_SIGNED                     0

/* vga_cm_cal_control_bit          */
 #define    vga_cm_cal_control_bit_ADDRESS                 0x04
 #define    vga_cm_cal_control_bit_OFFSET                     6
 #define    vga_cm_cal_control_bit_NBBIT                      1
 #define    vga_cm_cal_control_bit_ALONE                      0
 #define    vga_cm_cal_control_bit_SIGNED                     0

/* rf_bypass_enable_b                          */
 #define    rf_bypass_enable_b_ADDRESS                 0x04
 #define    rf_bypass_enable_b_OFFSET                     5
 #define    rf_bypass_enable_b_NBBIT                      1
 #define    rf_bypass_enable_b_ALONE                      0
 #define    rf_bypass_enable_b_SIGNED                     0

/* agc_en_b                          */
 #define    agc_en_b_ADDRESS                 0x04
 #define    agc_en_b_OFFSET                     2
 #define    agc_en_b_NBBIT                      1
 #define    agc_en_b_ALONE                      0
 #define    agc_en_b_SIGNED                     0

/* rxon                          */
 #define    rxon_ADDRESS                 0x04
 #define    rxon_OFFSET                     1
 #define    rxon_NBBIT                      1
 #define    rxon_ALONE                      0
 #define    rxon_SIGNED                     0

/* soft_resetn                          */
 #define    soft_resetn_ADDRESS                 0x04
 #define    soft_resetn_OFFSET                     0
 #define    soft_resetn_NBBIT                      1
 #define    soft_resetn_ALONE                      0
 #define    soft_resetn_SIGNED                     0

/* filter_bw_control_bit_add                          */
 #define    filter_bw_control_bit_add_ADDRESS                 0x0b
 #define    filter_bw_control_bit_add_OFFSET                     7
 #define    filter_bw_control_bit_add_NBBIT                      1
 #define    filter_bw_control_bit_add_ALONE                      0
 #define    filter_bw_control_bit_add_SIGNED                     0

/* filter_fc_bit_dr                          */
 #define    filter_fc_bit_dr_ADDRESS                 0x0b
 #define    filter_fc_bit_dr_OFFSET                     6
 #define    filter_fc_bit_dr_NBBIT                      1
 #define    filter_fc_bit_dr_ALONE                      0
 #define    filter_fc_bit_dr_SIGNED                     0

/* filter_bw_control_bit                          */
 #define    filter_bw_control_bit_ADDRESS                 0x0b
 #define    filter_bw_control_bit_OFFSET                     0
 #define    filter_bw_control_bit_NBBIT                      6
 #define    filter_bw_control_bit_ALONE                      0
 #define    filter_bw_control_bit_SIGNED                     0

/* div                          */
 #define    div_ADDRESS                  0x07
 #define    div_OFFSET                      0
 #define    div_NBBIT                      30
 #define    div_ALONE                       1
 #define    div_SIGNED                      0

#endif /* Layer1_RDA5812 */

void  L1_RF_RDA5812_Init          (RDA5812_Context *context, unsigned int add);
int   L1_RF_RDA5812_InitAfterReset(RDA5812_Context *context) ;

int   L1_RF_RDA5812_Get_Infos     (RDA5812_Context *context, char** infos);
int   L1_RF_RDA5812_Get_I2cChannel(RDA5812_Context *context);

int   L1_RF_RDA5812_Get_IF        (RDA5812_Context *context);
int   L1_RF_RDA5812_Get_RF        (RDA5812_Context *context);
int   L1_RF_RDA5812_Get_minRF     (RDA5812_Context *context);
int   L1_RF_RDA5812_Get_maxRF     (RDA5812_Context *context);
int   L1_RF_RDA5812_Tune          (RDA5812_Context *context, int rf);
int   L1_RF_RDA5812_Saw           (RDA5812_Context *context, int bw);
int   L1_RF_RDA5812_Get_Saw       (RDA5812_Context *context);
int   L1_RF_RDA5812_LPF           (RDA5812_Context *context, int lpf_khz);
char* L1_RF_RDA5812_TAG_TEXT      (void);

#endif /* _L1_RF_RDA5812_API_H_ */
