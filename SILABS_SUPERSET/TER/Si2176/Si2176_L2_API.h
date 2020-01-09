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
                  Silicon Laboratories Broadcast Si2176 Layer 2 API
   L2 API header for commands and properties
   FILE: Si2176_L2_API.h
   Supported IC : Si2176
   Compiled for ROM 13 firmware 3_2_build_6
   Revision: 0.1
   Date: December 22 2011
****************************************************************************************/

#ifndef   Si2176_L2_API_H
#define   Si2176_L2_API_H

#include "Si2176_L1_API.h"
#include "Si2176_Properties_Strings.h"

int  Si2176_Init                      (L1_Si2176_Context *api);
int  Si2176_Configure                 (L1_Si2176_Context *api);
int  Si2176_PowerUpWithPatch          (L1_Si2176_Context *api);
int  Si2176_LoadFirmware              (L1_Si2176_Context *api, unsigned char *fw_table, int lines);
int  Si2176_StartFirmware             (L1_Si2176_Context *api);
int Si2176_LoadVideofilter            (L1_Si2176_Context *api, unsigned char* vidfiltTable,int lines) ;
int Si2176_ATVTune                    (L1_Si2176_Context *api, unsigned long freq, unsigned char video_sys, unsigned char trans,unsigned char color,unsigned char invert_signal);
int Si2176_Tune                       (L1_Si2176_Context *api, unsigned char mode, unsigned long freq );
int Si2176_GetRF                      (L1_Si2176_Context *api);
int Si2176_DTVTune                    (L1_Si2176_Context *api, unsigned long freq, unsigned char bw, unsigned char modulation, unsigned char invert_spectrum);
int Si2176_ATV_Channel_Scan_M         (L1_Si2176_Context *api, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm, int minSNRHalfdB, int maxSNRHalfdB);
int Si2176_ATV_Channel_Scan_PAL       (L1_Si2176_Context *api, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm, int minSNRHalfdB, int maxSNRHalfdB);
int Si2176_UpdateChannelScanFrequency       (int freq,int channelsFound);
int Si2176_ClockOn                    (L1_Si2176_Context *api);
int Si2176_ClockOff                   (L1_Si2176_Context *api);
int Si2176_XOUTOn                     (L1_Si2176_Context *api);
int Si2176_XOUTOff                    (L1_Si2176_Context *api);
int Si2176_Standby                    (L1_Si2176_Context *api);
int Si2176_Powerdown                  (L1_Si2176_Context *api);


#endif /* Si2176_L2_API_H */





