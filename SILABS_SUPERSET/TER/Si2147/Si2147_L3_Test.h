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
                  Silicon Laboratories Broadcast Si2147 Layer 3 console application


   L3 sample application header
   FILE: Si2147_L3_Test.h
   Supported IC : Si2147
   Compiled for ROM 50 firmware 3_1_build_3
   Revision: 0.1
   Date: June 30 2015
****************************************************************************************/

#ifndef   Si2147_L3_TEST_H
#define   Si2147_L3_TEST_H

#define   Si2147_COMMAND_PROTOTYPES

#include "Si2147_L2_API.h"
#include "Si2147_Commands_Prototypes.h"

#define   Si2147_BASE_ADDRESS 0xc0
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

void Si2147_configure_i2c_communication    (L1_Si2147_Context *api, demod_Context *demodptr);

#ifdef    Si2147_COMMAND_LINE_APPLICATION

int  Si2147_DisplayStatusByte              (L1_Si2147_Context *api);
int  Si2147_GetRevision                    (L1_Si2147_Context *api);
int  Si2147_ATVStatus                      (L1_Si2147_Context *Si2147);
int  Si2147_DTVStatus                      (L1_Si2147_Context *Si2147);
int  Si2147_TunerStatus                    (L1_Si2147_Context *Si2147);
int  Si2147_GetUserFrequency               (unsigned long *fIn);
int  Si2147_help                           (void);
void Si2147_menu                           (unsigned char full);
int  Si2147_demoLoop                       (L1_Si2147_Context *api, char* choice);

#endif /* Si2147_COMMAND_LINE_APPLICATION */

#endif /* Si2147_L3_TEST_H */







