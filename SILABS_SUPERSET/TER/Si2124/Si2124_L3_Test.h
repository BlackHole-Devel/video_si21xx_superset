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
                  Silicon Laboratories Broadcast Si2124 Layer 3 console application


   L3 sample application header
   FILE: Si2124_L3_Test.h
   Supported IC : Si2124
   Compiled for ROM 62 firmware 2_1_build_5
   Revision: 0.2
   Date: July 24 2017
****************************************************************************************/

#ifndef   Si2124_L3_TEST_H
#define   Si2124_L3_TEST_H

#include "Si2124_L2_API.h"
#include "Si2124_Commands_Prototypes.h"

#define   Si2124_BASE_ADDRESS 0xc0
#define   SYSTEM_PAUSE system("pause")

void Si2124_configure_i2c_communication    (L1_Si2124_Context *api);

#ifdef    Si2124_COMMAND_LINE_APPLICATION

int  Si2124_DisplayStatusByte              (L1_Si2124_Context *api);
int  Si2124_GetRevision                    (L1_Si2124_Context *api);
int  Si2124_TunerStatus                    (L1_Si2124_Context *Si2124);
int  Si2124_GetUserFrequency               (unsigned long *fIn);
int  Si2124_help                           (void);
void Si2124_menu                           (unsigned char full);
int  Si2124_demoLoop                       (L1_Si2124_Context *api, char* choice);

#endif /* Si2124_COMMAND_LINE_APPLICATION */

#endif /* Si2124_L3_TEST_H */







