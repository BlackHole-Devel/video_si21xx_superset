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
/***************************************************************************************
                  Silicon Laboratories Broadcast Si2157 Layer 3 console application


   L3 sample application header
   FILE: Si2157_L3_Test.h
   Supported IC : Si2157
   Compiled for ROM 50 firmware 3_1_build_3
   Revision: 0.1
   Date: June 29 2015
****************************************************************************************/

#ifndef   Si2157_L3_TEST_H
#define   Si2157_L3_TEST_H

#define   Si2157_COMMAND_PROTOTYPES

#include "Si2157_L2_API.h"
#include "Si2157_Commands_Prototypes.h"

#define   Si2157_BASE_ADDRESS 0xc0
#define   SYSTEM_PAUSE system("pause")

#ifdef    SILABS_DEMOD_EVB
/* To be able to test this on SiLabs demod EVB, it must be possible to close the i2c passthru in the demod */
typedef struct demod_Context {
  L0_Context    *i2c;
  L0_Context     i2cObj;
} demod_Context;

/* i2c_passthru                   */
 #define    i2c_passthru_ADDRESS               49165
 #define    i2c_passthru_OFFSET                0
 #define    i2c_passthru_NBBIT                 1
 #define    i2c_passthru_ALONE                 1
 #define    i2c_passthru_SIGNED                0
  #define           i2c_passthru_disabled                      0
  #define           i2c_passthru_enabled                       1

  demod_Context  demodObj;
  demod_Context *demod;
#endif /* SILABS_DEMOD_EVB */

void Si2157_configure_i2c_communication    (L1_Si2157_Context *api, demod_Context *demodptr);

#ifdef    Si2157_COMMAND_LINE_APPLICATION

int  Si2157_DisplayStatusByte              (L1_Si2157_Context *api);
int  Si2157_GetRevision                    (L1_Si2157_Context *api);
int  Si2157_ATVStatus                      (L1_Si2157_Context *Si2157);
int  Si2157_DTVStatus                      (L1_Si2157_Context *Si2157);
int  Si2157_TunerStatus                    (L1_Si2157_Context *Si2157);
int  Si2157_GetUserFrequency               (unsigned long *fIn);
int  Si2157_help                           (void);
void Si2157_menu                           (unsigned char full);
int  Si2157_demoLoop                       (L1_Si2157_Context *api, char* choice);

#endif /* Si2157_COMMAND_LINE_APPLICATION */

#endif /* Si2157_L3_TEST_H */







