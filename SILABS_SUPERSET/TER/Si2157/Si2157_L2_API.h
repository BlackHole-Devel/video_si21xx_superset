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
                  Silicon Laboratories Broadcast Si2157 Layer 2 API


   L2 API header for commands and properties
   FILE: Si2157_L2_API.h
   Supported IC : Si2157
   Compiled for ROM 50 firmware 3_1_build_3
   Revision: 0.1
   Date: June 29 2015
****************************************************************************************/

#ifndef   Si2157_L2_API_H
#define   Si2157_L2_API_H

#include "Si2157_L1_API.h"
#include "Si2157_Properties_Strings.h"

int  Si2157_Init                      (L1_Si2157_Context *api);
int  Si2157_Configure                 (L1_Si2157_Context *api);
int  Si2157_PowerUpWithPatch          (L1_Si2157_Context *api);
int Si2157_PowerUpUsingBroadcastI2C   (L1_Si2157_Context *tuners[], int tuner_count );
int  Si2157_LoadFirmware              (L1_Si2157_Context *api, unsigned char *fw_table, int lines);
int  Si2157_StartFirmware             (L1_Si2157_Context *api);

int Si2157_LoadFirmware_16       (L1_Si2157_Context *api, firmware_struct fw_table[], int nbLines);
int Si2157_UpdateChannelScanFrequency(int freq,int channelsFound);
int Si2157_GetRF                 (L1_Si2157_Context *api);
int Si2157_Tune                  (L1_Si2157_Context *api, unsigned char mode, unsigned long freq);
int Si2157_ATVTune               (L1_Si2157_Context *api, unsigned long freq, unsigned char video_sys, unsigned char color, unsigned char invert_spectrum);
int Si2157_DTVTune               (L1_Si2157_Context *api, unsigned long freq, unsigned char bw, unsigned char modulation, unsigned char invert_signal);
int Si2157_XoutOn                (L1_Si2157_Context *api);
int Si2157_XoutOff               (L1_Si2157_Context *api);
int Si2157_Standby               (L1_Si2157_Context *api);
int Si2157_Powerdown             (L1_Si2157_Context *api);
int Si2157_LoadVideofilter       (L1_Si2157_Context *api, vid_filt_struct vidFiltTable[], int lines);
int Si2157_ATV_Channel_Scan_M    (L1_Si2157_Context *api, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm);
int Si2157_ATV_Channel_Scan_PAL  (L1_Si2157_Context *api, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm);
int Si2157_AGC_Override    (L1_Si2157_Context *api, unsigned char mode );
#define Si2157_FORCE_NORMAL_AGC       0
#define Si2157_FORCE_MAX_AGC          1
#define Si2157_FORCE_TOP_AGC          2

#endif /* Si2157_L2_API_H */







