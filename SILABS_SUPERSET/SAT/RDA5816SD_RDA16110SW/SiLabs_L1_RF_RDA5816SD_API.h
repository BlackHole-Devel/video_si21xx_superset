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
#ifndef _L1_RF_RDA5816SD_API_H_
#define _L1_RF_RDA5816SD_API_H_

#include "Silabs_L0_API.h"

typedef struct RDA5816SD_Context {
    L0_Context    *i2c;
    L0_Context     i2cObj;
    int    RF;
    int    IF;
    int    minRF;
    int    maxRF;
    int    LPF;
    int    xtal;
    int    rssi;
    int    rssi_offset;
    unsigned int  sub;
    unsigned char Status;
    unsigned char bytes[40];
    unsigned int loopthrough;
    unsigned char address_log;
} RDA5816SD_Context;

int  RDA5816SD_Communication_Check    (RDA5816SD_Context *context);
void L1_RF_RDA5816SD_Init             (RDA5816SD_Context *context, unsigned int add);
int  L1_RF_RDA5816SD_InitAfterReset   (RDA5816SD_Context *context);
int  L1_RF_RDA5816SD_Get_RF           (RDA5816SD_Context *context);
int  L1_RF_RDA5816SD_Tune             (RDA5816SD_Context *context, int rf_kHz);
int  L1_RF_RDA5816SD_LPF              (RDA5816SD_Context *context, int lpf_khz);
int  L1_RF_RDA5816SD_RSSI             (RDA5816SD_Context *context, int other_gain);
int  L1_RF_RDA5816SD_RSSI_from_AGC    (RDA5816SD_Context *context, int if_agc);
unsigned int  L1_RF_RDA5816SD_RfSel   (RDA5816SD_Context *context, unsigned char rf_chn);
unsigned char L1_RF_RDA5816SD_Wakeup  (RDA5816SD_Context *context);
unsigned char L1_RF_RDA5816SD_Standby (RDA5816SD_Context *context);
void          L1_RF_RDA5816SD_pre_lna_gain  (RDA5816SD_Context *context, int st1);
char*         L1_RF_RDA5816SD_TAG_TEXT      (void);
#endif /* _L1_RF_RDA5816SD_API_H_ */
