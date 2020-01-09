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
#ifndef _L1_RF_CUSTOMTER_API_H_
#define _L1_RF_CUSTOMTER_API_H_

#include "Silabs_L0_API.h"

#define CUSTOMTER_ADDR 0xC0

typedef struct CUSTOMTER_Context {
    L0_Context    *i2c;
    L0_Context     i2cObj;
    int    RF;
    int    IF;
    int    minRF;
    int    maxRF;
    double xtal;
    int    sawBW;
    int    tunerBytesCount;
    int    I2CMuxChannel;
    CONNECTION_TYPE connType;
    unsigned char tuner_log[39];
    float rssi;
} CUSTOMTER_Context;

/* CUSTOMTER registers definitions */
/* This allows using the following syntax:
 to set  register foo:             CUSTOMTER_WRITE(foo, foo_on);
 to read register foo: foo_value = CUSTOMTER_READ (foo);

 The above macros handle the necessary reading/masing/shifting for any register from 1 to 32 bits. (Casting may be requred for 32 bit signed registers)

 */
#define foo_ADDRESS  0x00
#define foo_OFFSET   3
#define foo_NBBIT    5
#define foo_ALONE    0
#define foo_SIGNED   0
 #define foo_off   0
 #define foo_on    1

/* Change the definition of CUSTOMTER_CODE to match your tuner */
#define CUSTOMTER_CODE 11111

#define CUSTOMTER_WRITE(register, v )  L0_WriteRegister (context->i2c,                register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE, v)
#define CUSTOMTER_READ(register)       L0_ReadRegister  (context->i2c,                register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_ALONE)

int    L1_RF_CUSTOMTER_Wakeup         (CUSTOMTER_Context *context);
int    L1_RF_CUSTOMTER_Standby        (CUSTOMTER_Context *context);
void   L1_RF_CUSTOMTER_Init           (CUSTOMTER_Context *context, unsigned int add);
int    L1_RF_CUSTOMTER_InitAfterReset (CUSTOMTER_Context *context);
int    L1_RF_CUSTOMTER_Tune           (CUSTOMTER_Context *context, int rf);
int    L1_RF_CUSTOMTER_ClockOn        (CUSTOMTER_Context *context);
int    L1_RF_CUSTOMTER_ClockOff       (CUSTOMTER_Context *context);
int    L1_RF_CUSTOMTER_Get_Infos      (CUSTOMTER_Context *context, char** infos);
char*  L1_RF_CUSTOMTER_TAG_TEXT       (void);
int    L1_RF_CUSTOMTER_Saw            (CUSTOMTER_Context *context, int bw_mhz);
int    L1_RF_CUSTOMTER_Get_IF         (CUSTOMTER_Context *context);
int    L1_RF_CUSTOMTER_Get_RSSI       (CUSTOMTER_Context *context);
int    L1_RF_CUSTOMTER_Get_RF         (CUSTOMTER_Context *context);
int    L1_RF_CUSTOMTER_Get_minRF      (CUSTOMTER_Context *context);
int    L1_RF_CUSTOMTER_Get_maxRF      (CUSTOMTER_Context *context);
char*  L1_RF_CUSTOMTER_Error_TEXT     (int error_code);

#endif /* _L1_RF_CUSTOMTER_API_H_ */
