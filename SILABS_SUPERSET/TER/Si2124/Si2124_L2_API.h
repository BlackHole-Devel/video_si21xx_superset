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
                  Silicon Laboratories Broadcast Si2124 Layer 2 API


   L2 API header for commands and properties
   FILE: Si2124_L2_API.h
   Supported IC : Si2124
   Compiled for ROM 62 firmware 2_1_build_5
   Revision: 0.2
   Date: July 24 2017
****************************************************************************************/

#ifndef   Si2124_L2_API_H
#define   Si2124_L2_API_H

#include "Si2124_L1_API.h"

#ifdef Si2124_COMMAND_LINE_APPLICATION
    #include "Si2124_Properties_Strings.h"
#endif /* Si2124_COMMAND_LINE_APPLICATION */

#ifdef    TUNER_ONLY
/* define some externals, required for VCO_BLOCKING */
/* only used for TUNER_ONLY mode */
extern signed   int fe;
extern L1_Si2124_Context  FrontEnd_Table[];
#endif /* TUNER_ONLY */

signed   int   Si2124_Init                       (L1_Si2124_Context *api);
signed   int   Si2124_Configure                  (L1_Si2124_Context *api);
signed   int   Si2124_PowerUpWithPatch           (L1_Si2124_Context *api);
signed   int   Si2124_PowerUpUsingBroadcastI2C   (L1_Si2124_Context *tuners[], signed   int tuner_count );
signed   int   Si2124_PowerUpOnly                (L1_Si2124_Context *api);
signed   int   Si2124_LoadFirmware               (L1_Si2124_Context *api, unsigned char *fw_table, signed   int lines);
signed   int   Si2124_StartFirmware              (L1_Si2124_Context *api);

signed   int   Si2124_LoadFirmware_16            (L1_Si2124_Context *api, firmware_struct fw_table[], signed   int nbLines);
signed   int   Si2124_GetRF                      (L1_Si2124_Context *api);
signed   int   Si2124_Tune                       (L1_Si2124_Context *api, unsigned char mode, unsigned long freq);
signed   int   Si2124_DTVTune                    (L1_Si2124_Context *api, unsigned long freq, unsigned char bw, unsigned char modulation, unsigned char invert_spectrum);
signed   int   Si2124_XoutOn                     (L1_Si2124_Context *api);
signed   int   Si2124_XoutOff                    (L1_Si2124_Context *api);
signed   int   Si2124_Standby                    (L1_Si2124_Context *api);
signed   int   Si2124_Powerdown                  (L1_Si2124_Context *api);
signed   int   Si2124_LoadVideofilter            (L1_Si2124_Context *api, vid_filt_struct vidFiltTable[], signed   int lines);
signed   int   Si2124_AGC_Override               (L1_Si2124_Context *api, unsigned char mode );
signed   int   Si2124_Tuner_Block_VCO            (L1_Si2124_Context *api, signed   int vco_code);
signed   int   Si2124_Tuner_Block_VCO2           (L1_Si2124_Context *api, signed   int vco_code);
signed   int   Si2124_Tuner_Block_VCO3           (L1_Si2124_Context *api, signed   int vco_code);
signed   int   Si2124_L2_VCO_Blocking_PostTune   (L1_Si2124_Context *tuners[], signed   int tuner_num, signed   int tuner_count);
signed   int   Si2124_L2_VCO_Blocking_PreTune    (L1_Si2124_Context *tuners[], signed   int tuner_num, signed   int tuner_count);
signed   int   Si2124_SetVcoProperties           (L1_Si2124_Context *api);

#define Si2124_FORCE_NORMAL_AGC       0
#define Si2124_FORCE_MAX_AGC          1
#define Si2124_FORCE_TOP_AGC          2

#endif /* Si2124_L2_API_H */







