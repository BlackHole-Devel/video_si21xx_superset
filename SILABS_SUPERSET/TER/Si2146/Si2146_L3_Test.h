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
                  Silicon Laboratories Broadcast Si2146 Layer 3 console application
   L3 sample application header
   FILE: Si2146_L3_Test.h
   Supported IC : Si2146
   Compiled for ROM 11 firmware 1_1_build_3
   Revision: 0.1
   Date: December 23 2011
****************************************************************************************/

#ifndef   Si2146_L3_TEST_H
#define   Si2146_L3_TEST_H

#define   Si2146_COMMAND_PROTOTYPES

#include "Si2146_L2_API.h"
#include "Si2146_Commands_Prototypes.h"

#define   Si2146_BASE_ADDRESS 0xc0
#define   SYSTEM_PAUSE system("pause")

void Si2146_configure_i2c_communication    (L1_Si2146_Context *api) ;

#ifdef    Si2146_COMMAND_LINE_APPLICATION

int  Si2146_DisplayStatusByte              (L1_Si2146_Context *api);
int  Si2146_SetupDTVProperties             (L1_Si2146_Context *api);
int  Si2146_SetupCommonProperties          (L1_Si2146_Context *api);
int  Si2146_SetupTunerProperties           (L1_Si2146_Context *api);
int  Si2146_GetRevision                    (L1_Si2146_Context *api);
int  Si2146_ATVStatus                      (L1_Si2146_Context *api);
int  Si2146_DTVStatus                      (L1_Si2146_Context *api);
int  Si2146_TunerStatus                    (L1_Si2146_Context *api);
int  Si2146_demoLoop                       (L1_Si2146_Context *Si2146, char* choice);
int  Si2146_GetUserFrequency               (unsigned long *fIn);
void Si2146_menu                           (unsigned char full);
int  Si2146_demoLoop                       (L1_Si2146_Context *api, char* choice);

#endif /* Si2146_COMMAND_LINE_APPLICATION */

#endif /* Si2146_L3_TEST_H */
