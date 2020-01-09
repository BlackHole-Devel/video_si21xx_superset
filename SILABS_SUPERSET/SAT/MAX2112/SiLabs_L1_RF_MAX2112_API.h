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
#ifndef _L1_RF_MAX2112_API_H_
#define _L1_RF_MAX2112_API_H_

#include "Silabs_L0_API.h"

typedef struct MAX2112_Context {
    L0_Context    *i2c;
    L0_Context     i2cObj;
    int            RF;
    int            IF;
    int            minRF;
    int            maxRF;
    double         xtal;
    int            rssi;
    int            LPF;
    int            tunerBytesCount;
    unsigned char  tuner_log[20];
} MAX2112_Context;

#ifdef Layer1_MAX2112

#define MAX2112_ADDR 0xc0      /*physical address of the MAX2112 on the I2c bus*/

/*Define register offset constants.*/
#define MAX2112_N_HIGH      0x0   /*Register 0 - N_High Divider*/
#define MAX2112_N_LOW       0x1   /*Register 1 - N_Low Divider*/
#define MAX2112_CP_FRAC2    0x2   /*Register 2 - Charge Pump and Fractional Divider 2*/
#define MAX2112_FRAC1       0x3   /*Register 3 - Fractional Divider 1*/
#define MAX2112_FRAC0       0x4   /*Register 4 - Fractional Divider 0*/
#define MAX2112_XTAL        0x5   /*Register 5 - Crystal and Reference Divider*/
#define MAX2112_PLL         0x6   /*Register 6 - PLL Configuration*/
#define MAX2112_VCOCONT     0x7   /*Register 7 - VCO Control*/
#define MAX2112_BASEBAND    0x8   /*Register 8 - BaseBand LPF*/
#define MAX2112_STANDBY     0x9   /*Register 9 - Standby and Baseband Gain*/
#define MAX2112_SHUTDWN     0xa   /*Register 10 - Shutdown*/
#define MAX2112_TEST        0xb   /*Register 11 - Test Modes*/
#define MAX2112_STATUS      0xc   /*Register 12 - Status, Read only*/
#define MAX2112_AUTOTUNER   0xd   /*Register 13- Always set to these defaults*/
#define MAX2112_TRIMCONF    0xe   /*Register 14- Always set to these defaults*/
#define MAX2112_BIASTRIM    0xf   /*Register 15- Always set to these defaults*/
#define MAX2112_BBFILTTRIM  0x10  /*Register 16- Always set to these defaults*/
#define MAX2112_RFCONTTRIM1 0x11  /*Register 17- Always set to these defaults*/
#define MAX2112_RFCONTTRIM2 0x12  /*Register 18- Always set to these defaults*/
#define MAX2112_FUSEREAD    0x13  /*Register 19- Always set to these defaults*/

#define LD_BIT 0x10  /*Lock detect bit position*/

/* n_msb                          */
 #define    ADDRESS_n_msb                      0
 #define    OFFSET__n_msb                      0
 #define    NBBIT___n_msb                      7
 #define    ALONE___n_msb                      0
 #define    SIGNED__n_msb                      0
 /* frac                           */
 #define    ADDRESS_frac                       0
 #define    OFFSET__frac                       7
 #define    NBBIT___frac                       1
 #define    ALONE___frac                       0
 #define    SIGNED__frac                       0
  #define           frac_default                               1
 /* n_lsb                          */
 #define    ADDRESS_n_lsb                      1
 #define    OFFSET__n_lsb                      0
 #define    NBBIT___n_lsb                      8
 #define    ALONE___n_lsb                      1
 #define    SIGNED__n_lsb                      0
 /* f_19_16                        */
 #define    ADDRESS_f_19_16                    2
 #define    OFFSET__f_19_16                    0
 #define    NBBIT___f_19_16                    4
 #define    ALONE___f_19_16                    0
 #define    SIGNED__f_19_16                    0
 /* charge_pump_linearity          */
 #define    ADDRESS_charge_pump_linearity      2
 #define    OFFSET__charge_pump_linearity      4
 #define    NBBIT___charge_pump_linearity      2
 #define    ALONE___charge_pump_linearity      0
 #define    SIGNED__charge_pump_linearity      0
  #define           charge_pump_linearity_default              1
 /* charge_pump_min_width          */
 #define    ADDRESS_charge_pump_min_width      2
 #define    OFFSET__charge_pump_min_width      6
 #define    NBBIT___charge_pump_min_width      2
 #define    ALONE___charge_pump_min_width      0
 #define    SIGNED__charge_pump_min_width      0
  #define           charge_pump_min_width_default              0
 /* f_15_8                         */
 #define    ADDRESS_f_15_8                     3
 #define    OFFSET__f_15_8                     0
 #define    NBBIT___f_15_8                     8
 #define    ALONE___f_15_8                     1
 #define    SIGNED__f_15_8                     0
 /* f_7_0                          */
 #define    ADDRESS_f_7_0                      4
 #define    OFFSET__f_7_0                      0
 #define    NBBIT___f_7_0                      8
 #define    ALONE___f_7_0                      1
 #define    SIGNED__f_7_0                      0
 /* r                              */
 #define    ADDRESS_r                          5
 #define    OFFSET__r                          0
 #define    NBBIT___r                          5
 #define    ALONE___r                          0
 #define    SIGNED__r                          0
  #define           r_divide_by_2                      0
  #define           r_divide_by_4                      1
 /* xd                             */
 #define    ADDRESS_xd                         5
 #define    OFFSET__xd                         5
 #define    NBBIT___xd                         3
 #define    ALONE___xd                         0
 #define    SIGNED__xd                         0
  #define           xd_divide_by_1                             0
  #define           xd_divide_by_2                             1
  #define           xd_divide_by_3                             2
  #define           xd_divide_by_4                             3
  #define           xd_divide_by_5                             4
  #define           xd_divide_by_6                             5
  #define           xd_divide_by_7                             6
  #define           xd_divide_by_8                             7
 /* icp                            */
 #define    ADDRESS_icp                        6
 #define    OFFSET__icp                        5
 #define    NBBIT___icp                        1
 #define    ALONE___icp                        0
 #define    SIGNED__icp                        0
  #define           icp_600ua                                  0
  #define           icp_1200ua                                 1
 /* cps                            */
 #define    ADDRESS_cps                        6
 #define    OFFSET__cps                        6
 #define    NBBIT___cps                        1
 #define    ALONE___cps                        0
 #define    SIGNED__cps                        0
  #define           cps_charge_pump_controlled_by_icp_bit      0
  #define           cps_charge_pump_controlled_by_vas          1
 /* div                            */
 #define    ADDRESS_div                        6
 #define    OFFSET__div                        7
 #define    NBBIT___div                        1
 #define    ALONE___div                        0
 #define    SIGNED__div                        0
  #define           div_divide_by_2                            0
  #define           div_divide_by_4                            1
 /* ade                            */
 #define    ADDRESS_ade                        7
 #define    OFFSET__ade                        0
 #define    NBBIT___ade                        1
 #define    ALONE___ade                        0
 #define    SIGNED__ade                        0
  #define           ade_disabled                               0
  #define           ade_enabled                                1
 /* adl                            */
 #define    ADDRESS_adl                        7
 #define    OFFSET__adl                        1
 #define    NBBIT___adl                        1
 #define    ALONE___adl                        0
 #define    SIGNED__adl                        0
  #define           adl_disabled                               0
  #define           adl_enabled                                1
 /* vas                            */
 #define    ADDRESS_vas                        7
 #define    OFFSET__vas                        2
 #define    NBBIT___vas                        1
 #define    ALONE___vas                        0
 #define    SIGNED__vas                        0
  #define           vas_disabled                               0
  #define           vas_enabled                                1
 /* vco                            */
 #define    ADDRESS_vco                        7
 #define    OFFSET__vco                        3
 #define    NBBIT___vco                        5
 #define    ALONE___vco                        0
 #define    SIGNED__vco                        0
  #define           vco_default                               0x19
 /* lpf                            */
 #define    ADDRESS_lpf                        8
 #define    OFFSET__lpf                        0
 #define    NBBIT___lpf                        8
 #define    ALONE___lpf                        1
 #define    SIGNED__lpf                        0
 /* bbg                            */
 #define    ADDRESS_bbg                        9
 #define    OFFSET__bbg                        0
 #define    NBBIT___bbg                        4
 #define    ALONE___bbg                        0
 #define    SIGNED__bbg                        0
 /* pwdn                           */
 #define    ADDRESS_pwdn                       9
 #define    OFFSET__pwdn                       2
 #define    NBBIT___pwdn                       1
 #define    ALONE___pwdn                       0
 #define    SIGNED__pwdn                       0
  #define           pwdn_normal_mode                           0
  #define           pwdn_standby_mode                          1
 /* stdby                          */
 #define    ADDRESS_stdby                      9
 #define    OFFSET__stdby                      7
 #define    NBBIT___stdby                      1
 #define    ALONE___stdby                      0
 #define    SIGNED__stdby                      0
  #define           stdby_normal_mode                          0
  #define           stdby_standby_mode                         1
 /* fe_shutdown                    */
 #define    ADDRESS_fe_shutdown               10
 #define    OFFSET__fe_shutdown                0
 #define    NBBIT___fe_shutdown                1
 #define    ALONE___fe_shutdown                0
 #define    SIGNED__fe_shutdown                0
 /* rfvga_shutdown                 */
 #define    ADDRESS_rfvga_shutdown            10
 #define    OFFSET__rfvga_shutdown             1
 #define    NBBIT___rfvga_shutdown             1
 #define    ALONE___rfvga_shutdown             0
 #define    SIGNED__rfvga_shutdown             0
 /* rfmix_shutdown                 */
 #define    ADDRESS_rfmix_shutdown            10
 #define    OFFSET__rfmix_shutdown             2
 #define    NBBIT___rfmix_shutdown             1
 #define    ALONE___rfmix_shutdown             0
 #define    SIGNED__rfmix_shutdown             0
 /* bb_shutdown                    */
 #define    ADDRESS_bb_shutdown               10
 #define    OFFSET__bb_shutdown                3
 #define    NBBIT___bb_shutdown                1
 #define    ALONE___bb_shutdown                0
 #define    SIGNED__bb_shutdown                0
 /* vco_shutdown                   */
 #define    ADDRESS_vco_shutdown              10
 #define    OFFSET__vco_shutdown               4
 #define    NBBIT___vco_shutdown               1
 #define    ALONE___vco_shutdown               0
 #define    SIGNED__vco_shutdown               0
 /* div_shutdown                   */
 #define    ADDRESS_div_shutdown              10
 #define    OFFSET__div_shutdown               5
 #define    NBBIT___div_shutdown               1
 #define    ALONE___div_shutdown               0
 #define    SIGNED__div_shutdown               0
 /* pll_shutdown                   */
 #define    ADDRESS_pll_shutdown              10
 #define    OFFSET__pll_shutdown               6
 #define    NBBIT___pll_shutdown               1
 #define    ALONE___pll_shutdown               0
 #define    SIGNED__pll_shutdown               0
 /* ldmux                          */
 #define    ADDRESS_ldmux                     11
 #define    OFFSET__ldmux                      0
 #define    NBBIT___ldmux                      2
 #define    ALONE___ldmux                      0
 #define    SIGNED__ldmux                      0
  #define           ldmux_default                              0
 /* turbo                          */
 #define    ADDRESS_turbo                     11
 #define    OFFSET__turbo                      3
 #define    NBBIT___turbo                      1
 #define    ALONE___turbo                      0
 #define    SIGNED__turbo                      0
  #define           turbo_default_on                           1
 /* cptst                          */
 #define    ADDRESS_cptst                     11
 #define    OFFSET__cptst                      5
 #define    NBBIT___cptst                      3
 #define    ALONE___cptst                      0
 #define    SIGNED__cptst                      0
  #define           cptst_default                              0
 /* ld                             */
 #define    ADDRESS_ld                        12
 #define    OFFSET__ld                         4
 #define    NBBIT___ld                         1
 #define    ALONE___ld                         0
 #define    SIGNED__ld                         0
 /* vase                           */
 #define    ADDRESS_vase                      12
 #define    OFFSET__vase                       5
 #define    NBBIT___vase                       1
 #define    ALONE___vase                       0
 #define    SIGNED__vase                       0
 /* vasa                           */
 #define    ADDRESS_vasa                      12
 #define    OFFSET__vasa                       6
 #define    NBBIT___vasa                       1
 #define    ALONE___vasa                       0
 #define    SIGNED__vasa                       0
 /* por                            */
 #define    ADDRESS_por                       12
 #define    OFFSET__por                        7
 #define    NBBIT___por                        1
 #define    ALONE___por                        0
 #define    SIGNED__por                        0
 /* adc                            */
 #define    ADDRESS_adc                       13
 #define    OFFSET__adc                        0
 #define    NBBIT___adc                        3
 #define    ALONE___adc                        0
 #define    SIGNED__adc                        0
 /* vcosrb                         */
 #define    ADDRESS_vcosrb                    13
 #define    OFFSET__vcosrb                     3
 #define    NBBIT___vcosrb                     5
 #define    ALONE___vcosrb                     0
 #define    SIGNED__vcosrb                     0

void  Max2112Write                 (MAX2112_Context *context, unsigned char reg_index, unsigned char value);
void  Max2112ProgramTuner          (MAX2112_Context *context);
void  Max2112SetFrequency          (MAX2112_Context *context, double Frequency);

void  MAX2112_WriteRegisterTrace   (MAX2112_Context *context, char* name, char* valName, unsigned int add, unsigned char offset, unsigned char nbbit, unsigned char Value);
void  MAX2112_WriteRegister        (MAX2112_Context *context,              unsigned int add, unsigned char offset, unsigned char nbbit, unsigned char Value);

#endif /* Layer1_MAX2112 */

void  L1_RF_MAX2112_Init          (MAX2112_Context *context, unsigned int add);
int   L1_RF_MAX2112_InitAfterReset(MAX2112_Context *context) ;

int   L1_RF_MAX2112_Get_Infos     (MAX2112_Context *context, char** infos);
int   L1_RF_MAX2112_Get_I2cChannel(MAX2112_Context *context);

int   L1_RF_MAX2112_Get_IF        (MAX2112_Context *context);
int   L1_RF_MAX2112_Get_RF        (MAX2112_Context *context);
int   L1_RF_MAX2112_Get_minRF     (MAX2112_Context *context);
int   L1_RF_MAX2112_Get_maxRF     (MAX2112_Context *context);
int   L1_RF_MAX2112_Tune          (MAX2112_Context *context, int rf);
int   L1_RF_MAX2112_Saw           (MAX2112_Context *context, int bw);
int   L1_RF_MAX2112_Get_Saw       (MAX2112_Context *context);
int   L1_RF_MAX2112_LPF           (MAX2112_Context *context, int lpf);
char* L1_RF_MAX2112_TAG_TEXT      (void);

#endif /* _L1_RF_MAX2112_API_H_ */
