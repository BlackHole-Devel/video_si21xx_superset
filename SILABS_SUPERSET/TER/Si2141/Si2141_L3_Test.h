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
                  Silicon Laboratories Broadcast Si2141 Layer 3 console application


   L3 sample application header
   FILE: Si2141_L3_Test.h
   Supported IC : Si2141
   Compiled for ROM 61 firmware 1_1_build_12
   Revision: 0.5
   Date: June 14 2019
****************************************************************************************/

#ifndef   Si2141_L3_TEST_H
#define   Si2141_L3_TEST_H

#define   Si2141_COMMAND_PROTOTYPES

#include "Si2141_L2_API.h"
#include "Si2141_Commands_Prototypes.h"

#define   Si2141_BASE_ADDRESS 0xc0
#define   SYSTEM_PAUSE system("pause")

void Si2141_configure_i2c_communication    (L1_Si2141_Context *api);

#ifdef    Si2141_COMMAND_LINE_APPLICATION

int  Si2141_DisplayStatusByte              (L1_Si2141_Context *api);
int  Si2141_GetRevision                    (L1_Si2141_Context *api);
int  Si2141_TunerStatus                    (L1_Si2141_Context *Si2141);
int  Si2141_GetUserFrequency               (unsigned long *fIn);
int  Si2141_help                           (void);
void Si2141_menu                           (unsigned char full);
int  Si2141_demoLoop                       (L1_Si2141_Context *api, char* choice);

#endif /* Si2141_COMMAND_LINE_APPLICATION */

#endif /* Si2141_L3_TEST_H */







