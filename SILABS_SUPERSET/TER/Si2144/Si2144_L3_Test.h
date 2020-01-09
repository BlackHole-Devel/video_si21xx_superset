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
                  Silicon Laboratories Broadcast Si2144 Layer 3 console application


   L3 sample application header
   FILE: Si2144_L3_Test.h
   Supported IC : Si2144
   Compiled for ROM 62 firmware 2_1_build_5
   Revision: 0.1
   Date: July 07 2017
****************************************************************************************/

#ifndef   Si2144_L3_TEST_H
#define   Si2144_L3_TEST_H

#include "Si2144_L2_API.h"
#include "Si2144_Commands_Prototypes.h"

#define   Si2144_BASE_ADDRESS 0xc0
#define   SYSTEM_PAUSE system("pause")

void Si2144_configure_i2c_communication    (L1_Si2144_Context *api);

#ifdef    Si2144_COMMAND_LINE_APPLICATION

int  Si2144_DisplayStatusByte              (L1_Si2144_Context *api);
int  Si2144_GetRevision                    (L1_Si2144_Context *api);
int  Si2144_TunerStatus                    (L1_Si2144_Context *Si2144);
int  Si2144_GetUserFrequency               (unsigned long *fIn);
int  Si2144_help                           (void);
void Si2144_menu                           (unsigned char full);
int  Si2144_demoLoop                       (L1_Si2144_Context *api, char* choice);

#endif /* Si2144_COMMAND_LINE_APPLICATION */

#endif /* Si2144_L3_TEST_H */







