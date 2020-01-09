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
                  Silicon Laboratories Broadcast Si2158B Layer 3 console application


   L3 sample application header
   FILE: Si2158B_L3_Test.h
   Supported IC : Si2158B
   Compiled for ROM 51 firmware 4_1_build_3
   Revision: 0.1
   Date: June 23 2016
****************************************************************************************/

#ifndef   Si2158B_L3_TEST_H
#define   Si2158B_L3_TEST_H

#define   Si2158B_COMMAND_PROTOTYPES

#include "Si2158B_L2_API.h"
#include "Si2158B_Commands_Prototypes.h"

#define   Si2158B_BASE_ADDRESS 0xc0
#define   SYSTEM_PAUSE system("pause")

void Si2158B_configure_i2c_communication    (L1_Si2158B_Context *api);

#ifdef    Si2158B_COMMAND_LINE_APPLICATION

int  Si2158B_DisplayStatusByte              (L1_Si2158B_Context *api);
int  Si2158B_GetRevision                    (L1_Si2158B_Context *api);
int  Si2158B_ATVStatus (L1_Si2158B_Context *Si2158B);
int  Si2158B_DTVStatus (L1_Si2158B_Context *Si2158B);
int  Si2158B_TunerStatus (L1_Si2158B_Context *Si2158B);
int  Si2158B_GetUserFrequency               (unsigned long *fIn);
int  Si2158B_help                           (void);
void Si2158B_menu                           (unsigned char full);
int  Si2158B_demoLoop                       (L1_Si2158B_Context *api, char* choice);

#endif /* Si2158B_COMMAND_LINE_APPLICATION */

#endif /* Si2158B_L3_TEST_H */







