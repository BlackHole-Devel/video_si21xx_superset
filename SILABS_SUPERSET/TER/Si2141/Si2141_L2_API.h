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
                  Silicon Laboratories Broadcast Si2141 Layer 2 API


   L2 API header for commands and properties
   FILE: Si2141_L2_API.h
   Supported IC : Si2141
   Compiled for ROM 61 firmware 1_1_build_12
   Revision: 0.5
   Date: June 14 2019
****************************************************************************************/

#ifndef   Si2141_L2_API_H
#define   Si2141_L2_API_H

#include "Si2141_L1_API.h"
#include "Si2141_Properties_Strings.h"

#ifdef    TUNER_ONLY
/* define some externals, required for VCO_BLOCKING */
/* only used for TUNER_ONLY mode */
extern int fe;
extern L1_Si2141_Context  FrontEnd_Table[];
#endif // TUNER_ONLY

int  Si2141_Init                      (L1_Si2141_Context *api);
int  Si2141_Configure                 (L1_Si2141_Context *api);
int  Si2141_PowerUpWithPatch          (L1_Si2141_Context *api);
int  Si2141_PowerUpUsingBroadcastI2C  (L1_Si2141_Context *tuners[], int tuner_count );
int  Si2141_PowerUpOnly               (L1_Si2141_Context *api);
signed   int  Si2141_Store_FW         (L1_Si2141_Context *api,    firmware_struct fw_table[], signed   int nbLines);
int  Si2141_LoadFirmware              (L1_Si2141_Context *api, unsigned char *fw_table, int lines);
int  Si2141_StartFirmware             (L1_Si2141_Context *api);

int Si2141_LoadFirmware_16            (L1_Si2141_Context *api, firmware_struct fw_table[], int nbLines);
int Si2141_GetRF                      (L1_Si2141_Context *api);
int Si2141_Tune                       (L1_Si2141_Context *api, unsigned char mode, unsigned long freq);
int Si2141_DTVTune                    (L1_Si2141_Context *api, unsigned long freq, unsigned char bw, unsigned char modulation, unsigned char invert_spectrum);
int Si2141_XoutOn                     (L1_Si2141_Context *api);
int Si2141_XoutOff                    (L1_Si2141_Context *api);
int Si2141_Standby                    (L1_Si2141_Context *api);
int Si2141_Powerdown                  (L1_Si2141_Context *api);
int Si2141_LoadVideofilter            (L1_Si2141_Context *api, vid_filt_struct vidFiltTable[], int lines);
int Si2141_AGC_Override               (L1_Si2141_Context *api, unsigned char mode );
int Si2141_Tuner_Block_VCO            (L1_Si2141_Context *api, int vco_code);
int Si2141_Tuner_Block_VCO2           (L1_Si2141_Context *api, int vco_code);
int Si2141_Tuner_Block_VCO3           (L1_Si2141_Context *api, int vco_code);
int Si2141_L2_VCO_Blocking_PostTune   (L1_Si2141_Context *tuners[], int tuner_num, int tuner_count);
int Si2141_L2_VCO_Blocking_PreTune    (L1_Si2141_Context *tuners[], int tuner_num, int tuner_count);
int Si2141_SetVcoProperties           (L1_Si2141_Context *api);

#define Si2141_FORCE_NORMAL_AGC       0
#define Si2141_FORCE_MAX_AGC          1
#define Si2141_FORCE_TOP_AGC          2

#endif /* Si2141_L2_API_H */







