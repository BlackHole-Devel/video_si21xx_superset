/*************************************************************************************************************
Copyright 2019, Silicon Laboratories, Inc.

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
#ifndef _L1_RF_CUSTOMSAT_API_H_
#define _L1_RF_CUSTOMSAT_API_H_

#ifndef   DLL_MODE
 #include "Silabs_L0_API.h"
#else  /* DLL_MODE */
 #include "Emb_L0_API.h"
#endif /* DLL_MODE */

typedef struct CUSTOMSAT_Context {
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
} CUSTOMSAT_Context;

#define SAT_TUNER_CUSTOMSAT_CODE 123456

/* CUSTOMSAT registers definitions */
/* This allows using the following syntax:
 to set  register foo:             CUSTOMSAT_WRITE(foo, foo_on);
 to read register foo: foo_value = CUSTOMSAT_READ(foo);

 The above macros handle the necessary reading/masing/shifting for any register from 1 to 32 bits. (Casting may be required for 32 bit signed registers)

 */
#define foo_ADDRESS  0x00
#define foo_OFFSET   3
#define foo_NBBIT    5
#define foo_ALONE    0
#define foo_SIGNED   0
 #define foo_off   0
 #define foo_on    1

#define CUSTOMSAT_WRITE(register, v )  L0_WriteRegister (context->i2c,                register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE, v)
#define CUSTOMSAT_READ(register)       L0_ReadRegister  (context->i2c,                register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE)

int    L1_RF_CUSTOMSAT_Wakeup         (CUSTOMSAT_Context *context);
int    L1_RF_CUSTOMSAT_Standby        (CUSTOMSAT_Context *context);
void   L1_RF_CUSTOMSAT_Init           (CUSTOMSAT_Context *context, unsigned int add);
int    L1_RF_CUSTOMSAT_InitAfterReset (CUSTOMSAT_Context *context);
int    L1_RF_CUSTOMSAT_Tune           (CUSTOMSAT_Context *context, int rf);
int    L1_RF_CUSTOMSAT_ClockOn        (CUSTOMSAT_Context *context);
int    L1_RF_CUSTOMSAT_ClockOff       (CUSTOMSAT_Context *context);
int    L1_RF_CUSTOMSAT_Get_Infos      (CUSTOMSAT_Context *context, char** infos);
const char*  L1_RF_CUSTOMSAT_TAG_TEXT       (void);
int    L1_RF_CUSTOMSAT_LPF            (CUSTOMSAT_Context *context, int lpf_khz);
int    L1_RF_CUSTOMSAT_Get_IF         (CUSTOMSAT_Context *context);
int    L1_RF_CUSTOMSAT_Get_RF         (CUSTOMSAT_Context *context);
int    L1_RF_CUSTOMSAT_Get_minRF      (CUSTOMSAT_Context *context);
int    L1_RF_CUSTOMSAT_Get_maxRF      (CUSTOMSAT_Context *context);
float  L1_RF_CUSTOMSAT_RSSI           (CUSTOMSAT_Context *context, float ref_level);

#endif /* _L1_RF_CUSTOMSAT_API_H_ */
