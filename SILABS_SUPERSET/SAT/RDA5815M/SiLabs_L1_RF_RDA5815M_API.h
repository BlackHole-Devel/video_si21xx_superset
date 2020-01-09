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
#ifndef _L1_RF_RDA5815M_API_H_
#define _L1_RF_RDA5815M_API_H_

#include "Silabs_L0_API.h"

typedef struct RDA5815M_Context {
    L0_Context    *i2c;
    L0_Context     i2cObj;
    int    RF;
    int    IF;
    int    minRF;
    int    maxRF;
    int    LPF_kHz;
    int    rssi;
    unsigned char Status;
    unsigned char bytes[40];
    unsigned int loopthrough;
} RDA5815M_Context;

int  RDA5815M_Communication_Check    (RDA5815M_Context *context);
void L1_RF_RDA5815M_Init             (RDA5815M_Context *context, unsigned int add);
int  L1_RF_RDA5815M_InitAfterReset   (RDA5815M_Context *context);
int  L1_RF_RDA5815M_Get_RF           (RDA5815M_Context *context);
int  L1_RF_RDA5815M_Tune             (RDA5815M_Context *context, int rf);
int  L1_RF_RDA5815M_LPF              (RDA5815M_Context *context, int lpf_khz);
int  L1_RF_RDA5815M_RSSI             (RDA5815M_Context *context, int other_gain);
unsigned char L1_RF_RDA5815M_Wakeup  (RDA5815M_Context *context);
unsigned char L1_RF_RDA5815M_Standby (RDA5815M_Context *context);
char*         L1_RF_RDA5815M_TAG_TEXT      (void);

#endif /* _L1_RF_RDA5815M_API_H_ */
