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
                  Silicon Laboratories Broadcast Si2146 Layer 2 API
   L2 API header for commands and properties
   FILE: Si2146_L2_API.h
   Supported IC : Si2146
   Compiled for ROM 11 firmware 1_1_build_3
   Revision: 0.1
   Date: December 23 2011
****************************************************************************************/

#ifndef   Si2146_L2_API_H
#define   Si2146_L2_API_H

#include "Si2146_L1_API.h"
#include "Si2146_Properties_Strings.h"

int ProcessAPITopLevelSequence       (L1_Si2146_Context *Si2146);
int  Si2146_Init                      (L1_Si2146_Context *api);
int  Si2146_Configure                 (L1_Si2146_Context *api);
int  Si2146_PowerUpWithPatch          (L1_Si2146_Context *api);
int  Si2146_LoadFirmware              (L1_Si2146_Context *api, unsigned char *fw_table, int lines);
int  Si2146_StartFirmware             (L1_Si2146_Context *api);
int Si2146_Configure                 (L1_Si2146_Context *Si2146);
int Si2146_LoadVideofilter           (L1_Si2146_Context *Si2146, unsigned char* vidfiltTable,int lines);
int Si2146_GetRF                     (L1_Si2146_Context *api);
int Si2146_Tune                      (L1_Si2146_Context *Si2146, unsigned char mode, unsigned long freq );
int Si2146_DTVTune                   (L1_Si2146_Context *Si2146, unsigned long freq, unsigned char bw, unsigned char modulation, unsigned char invert_spectrum);
int Si2146_SetupSomeDefaults         (L1_Si2146_Context *Si2146);
int Si2146_ClockOn                   (L1_Si2146_Context *api);
int Si2146_ClockOff                  (L1_Si2146_Context *api);
#define Si2146_FORCE_NORMAL_AGC       0
#define Si2146_FORCE_MAX_AGC          1
#define Si2146_FORCE_TOP_AGC          2
int Si2146_AGC_Override    (L1_Si2146_Context *Si2146, unsigned char mode );
#endif /* Si2146_L2_API_H */
