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
#ifndef _L1_RF_NXP20142_API_H_
#define _L1_RF_NXP20142_API_H_

#include "Silabs_L0_API.h"
#include "blackwidow_apil.h"

typedef struct NXP20142_Context {
    L0_Context    *i2c;
    L0_Context     i2cObj;
    int    RF;
    int    IF;
    int    minRF;
    int    maxRF;
    int    LPF;
    float  rssi;
    unsigned int gain;
    unsigned char lna_enable;
    unsigned char lna_gc;
             char lna_gain;
             int power_detect;
    unsigned char Status;
    unsigned char bytes[40];
    BLACKWIDOW_COMMUNICATION  NXP20142_Communication_Obj;
    BLACKWIDOW_COMMUNICATION *NXP20142_Communication;
    BLACKWIDOW_CONFIG         NXP20142_Config_Obj;
    BLACKWIDOW_CONFIG        *NXP20142_Config;
    SAT_TUNER_CHANOBJ         NXP20142_Channel_Obj;
    SAT_TUNER_CHANOBJ        *NXP20142_Channel;
} NXP20142_Context;

int           NXP20142_Communication_Check    (NXP20142_Context *context);
void          L1_RF_NXP20142_Init             (NXP20142_Context *context, unsigned int add);
int           L1_RF_NXP20142_InitAfterReset   (NXP20142_Context *context);
int           L1_RF_NXP20142_Get_RF           (NXP20142_Context *context);
int           L1_RF_NXP20142_Tune             (NXP20142_Context *context, int rf);
int           L1_RF_NXP20142_LPF              (NXP20142_Context *context, int lpf_khz);
float         L1_RF_NXP20142_RSSI             (NXP20142_Context *context, int other_gain);
unsigned char L1_RF_NXP20142_Wakeup           (NXP20142_Context *context);
unsigned char L1_RF_NXP20142_Standby          (NXP20142_Context *context);
char*         L1_RF_NXP20142_TAG_TEXT         (void);
float         Si21xx_NXP20142_rssi            (int if_agc, unsigned char lna_enable);

#endif /* _L1_RF_NXP20142_API_H_ */
