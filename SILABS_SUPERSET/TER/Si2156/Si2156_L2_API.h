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
                  Silicon Laboratories Broadcast Si2156 Layer 2 API
   L2 API header for commands and properties
   FILE: Si2156_L2_API.h
   Supported IC : Si2156
   Compiled for ROM 13 firmware 3_1_build_9
   Revision: 0.3
   Date: December 22 2011
****************************************************************************************/

#ifndef   Si2156_L2_API_H
#define   Si2156_L2_API_H

#include "Si2156_L1_API.h"
#include "Si2156_Properties_Strings.h"

int  Si2156_Init                      (L1_Si2156_Context *api);
int  Si2156_Configure                 (L1_Si2156_Context *api);
int  Si2156_PowerUpWithPatch          (L1_Si2156_Context *api);
int  Si2156_LoadFirmware              (L1_Si2156_Context *api, unsigned char *fw_table, int lines);
int  Si2156_StartFirmware             (L1_Si2156_Context *api);
int Si2156_LoadVideofilter            (L1_Si2156_Context *api, unsigned char* vidfiltTable,int lines) ;
int Si2156_ATVTune                    (L1_Si2156_Context *api, unsigned long freq, unsigned char video_sys, unsigned char trans,unsigned char color,unsigned char invert_signal);
int Si2156_Tune                       (L1_Si2156_Context *api, unsigned char mode, unsigned long freq );
int Si2156_GetRF                      (L1_Si2156_Context *api);
int Si2156_DTVTune                    (L1_Si2156_Context *api, unsigned long freq, unsigned char bw, unsigned char modulation, unsigned char invert_spectrum);
int Si2156_ATV_Channel_Scan_M         (L1_Si2156_Context *api, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm);
int Si2156_ATV_Channel_Scan_PAL       (L1_Si2156_Context *api, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm);
int Si2156_UpdateChannelScanFrequency       (int freq,int channelsFound);
int Si2156_ClockOn                    (L1_Si2156_Context *api);
int Si2156_ClockOff                   (L1_Si2156_Context *api);
int Si2156_XOUTOn                     (L1_Si2156_Context *api);
int Si2156_XOUTOff                    (L1_Si2156_Context *api);
int Si2156_Standby                    (L1_Si2156_Context *api);
int Si2156_Powerdown                  (L1_Si2156_Context *api);
#define Si2156_FORCE_NORMAL_AGC       0
#define Si2156_FORCE_MAX_AGC          1
#define Si2156_FORCE_TOP_AGC          2
int Si2156_AGC_Override    (L1_Si2156_Context *Si2156, unsigned char mode );
#endif /* Si2156_L2_API_H */





