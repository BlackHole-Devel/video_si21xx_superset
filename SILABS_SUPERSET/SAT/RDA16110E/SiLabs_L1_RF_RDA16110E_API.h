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
#ifndef _L1_RF_RDA16110E_API_H_
#define _L1_RF_RDA16110E_API_H_

#include "Silabs_L0_API.h"

typedef struct RDA16110E_Context {
    L0_Context    *i2c;
    L0_Context     i2cObj;
    signed   int   RF;
    signed   int   IF;
    signed   int   minRF;
    signed   int   maxRF;
    signed   int   LPF;
    signed   int   xtal;
    signed   int   rssi;
    signed   int   rssi_offset;
    unsigned int   sub;
    unsigned char  Status;
    unsigned char  bytes[40];
    unsigned int   loopthrough;
    unsigned char  address_log;
} RDA16110E_Context;

int           RDA16110E_Communication_Check    (RDA16110E_Context *context);

void          L1_RF_RDA16110E_Init             (RDA16110E_Context *context, unsigned int add);
int           L1_RF_RDA16110E_InitAfterReset   (RDA16110E_Context *context);
int           L1_RF_RDA16110E_Get_RF           (RDA16110E_Context *context);
int           L1_RF_RDA16110E_Tune             (RDA16110E_Context *context, signed   int rf_kHz);
int           L1_RF_RDA16110E_LPF              (RDA16110E_Context *context, signed   int lpf_khz);
int           L1_RF_RDA16110E_RSSI             (RDA16110E_Context *context, signed   int other_gain);
int           L1_RF_RDA16110E_RSSI_from_AGC    (RDA16110E_Context *context, signed   int if_agc);
unsigned int  L1_RF_RDA16110E_RfSel            (RDA16110E_Context *context, unsigned char rf_chn);
unsigned char L1_RF_RDA16110E_Wakeup           (RDA16110E_Context *context);
unsigned char L1_RF_RDA16110E_Standby          (RDA16110E_Context *context);
char*         L1_RF_RDA16110E_TAG_TEXT         (void);

#endif /* _L1_RF_RDA16110E_API_H_ */
