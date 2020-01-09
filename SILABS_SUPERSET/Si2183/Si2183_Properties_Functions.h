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
/*************************************************************************************
                  Silicon Laboratories Broadcast Si2183 Layer 1 API


   API properties functions definitions
   FILE: Si2183_Properties_Functions.h
   Supported IC : Si2183
   Compiled for ROM 2 firmware 5_B_build_1
   Revision: V0.3.5.1
   Date: November 06 2015
**************************************************************************************/
/* Change log:
 As from V0.0.0:
  Initial version (based on Si2164 code V0.3.4)
****************************************************************************************/
#ifndef   _Si2183_PROPERTIES_FUNCTIONS_H_
#define   _Si2183_PROPERTIES_FUNCTIONS_H_

void          Si2183_storeUserProperties           (Si2183_PropObj   *prop);
unsigned char Si2183_PackProperty                  (Si2183_PropObj   *prop, unsigned int prop_code, signed   int *data);
unsigned char Si2183_UnpackProperty                (Si2183_PropObj   *prop, unsigned int prop_code, signed   int  data);
void          Si2183_storePropertiesDefaults       (Si2183_PropObj   *prop);

int  Si2183_downloadCOMMONProperties(L1_Si2183_Context *api);
int  Si2183_downloadDDProperties    (L1_Si2183_Context *api);
#ifdef    DEMOD_DVB_C
int  Si2183_downloadDVBCProperties  (L1_Si2183_Context *api);
#endif /* DEMOD_DVB_C */

#ifdef    DEMOD_DVB_C2
int  Si2183_downloadDVBC2Properties (L1_Si2183_Context *api);
#endif /* DEMOD_DVB_C2 */

#ifdef    DEMOD_DVB_S_S2_DSS
int  Si2183_downloadDVBSProperties  (L1_Si2183_Context *api);
int  Si2183_downloadDVBS2Properties (L1_Si2183_Context *api);
#endif /* DEMOD_DVB_S_S2_DSS */

#ifdef    DEMOD_DVB_T
int  Si2183_downloadDVBTProperties  (L1_Si2183_Context *api);
#endif /* DEMOD_DVB_T */

#ifdef    DEMOD_DVB_T2
int  Si2183_downloadDVBT2Properties (L1_Si2183_Context *api);
#endif /* DEMOD_DVB_T2 */

#ifdef    DEMOD_ISDB_T
int  Si2183_downloadISDBTProperties (L1_Si2183_Context *api);
#endif /* DEMOD_ISDB_T */

#ifdef    DEMOD_MCNS
int  Si2183_downloadMCNSProperties  (L1_Si2183_Context *api);
#endif /* DEMOD_MCNS */

int  Si2183_downloadSCANProperties  (L1_Si2183_Context *api);
int  Si2183_downloadAllProperties   (L1_Si2183_Context *api);

#endif /* _Si2183_PROPERTIES_FUNCTIONS_H_ */







