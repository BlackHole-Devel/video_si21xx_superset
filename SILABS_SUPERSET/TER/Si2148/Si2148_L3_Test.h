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
                  Silicon Laboratories Broadcast Si2148 Layer 3 console application


   L3 sample application header
   FILE: Si2148_L3_Test.h
   Supported IC : Si2148
   Compiled for ROM 33 firmware 2_1_build_11
   Revision: 0.2
   Date: March 12 2014
****************************************************************************************/

#ifndef   Si2148_L3_TEST_H
#define   Si2148_L3_TEST_H

#define   Si2148_COMMAND_PROTOTYPES

#include "Si2148_L2_API.h"
#include "Si2148_Commands_Prototypes.h"

#define   Si2148_BASE_ADDRESS 0xc0
#define   SYSTEM_PAUSE system("pause")

void Si2148_configure_i2c_communication    (L1_Si2148_Context *api);

#ifdef    Si2148_COMMAND_LINE_APPLICATION

int  Si2148_DisplayStatusByte              (L1_Si2148_Context *api);
int  Si2148_GetRevision                    (L1_Si2148_Context *api);
int  Si2148_DTVStatus                       (L1_Si2148_Context *Si2148);
int  Si2148_TunerStatus                     (L1_Si2148_Context *Si2148);
int  Si2148_GetUserFrequency                (unsigned long *fIn);
void Si2148_menu                           (unsigned char full);
int  Si2148_demoLoop                       (L1_Si2148_Context *api, char* choice);


#endif /* Si2148_COMMAND_LINE_APPLICATION */

#endif /* Si2148_L3_TEST_H */





