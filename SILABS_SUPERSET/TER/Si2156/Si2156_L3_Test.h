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
                  Silicon Laboratories Broadcast Si2156 Layer 3 console application
   L3 sample application header
   FILE: Si2156_L3_Test.h
   Supported IC : Si2156
   Compiled for ROM 13 firmware 3_1_build_9
   Revision: 0.3
   Date: December 22 2011
****************************************************************************************/

#ifndef   Si2156_L3_TEST_H
#define   Si2156_L3_TEST_H

#define   Si2156_COMMAND_PROTOTYPES

#include "Si2156_L2_API.h"
#include "Si2156_Commands_Prototypes.h"

#define   Si2156_BASE_ADDRESS 0xc0
#define   SYSTEM_PAUSE system("pause")

void Si2156_configure_i2c_communication    (L1_Si2156_Context *api);

#ifdef    Si2156_COMMAND_LINE_APPLICATION

int  Si2156_DisplayStatusByte              (L1_Si2156_Context *api);
int  Si2156_GetRevision                    (L1_Si2156_Context *api);
int  Si2156_ATVStatus                      (L1_Si2156_Context *api);
int  Si2156_DTVStatus                      (L1_Si2156_Context *api);
int  Si2156_TunerStatus                    (L1_Si2156_Context *api);
void Si2156_menu                           (unsigned char full);
int  Si2156_demoLoop                       (L1_Si2156_Context *api, char* choice);

#endif /* Si2156_COMMAND_LINE_APPLICATION */

#endif /* Si2156_L3_TEST_H */





