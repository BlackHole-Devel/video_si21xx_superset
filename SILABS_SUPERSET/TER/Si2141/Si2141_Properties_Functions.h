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
                  Silicon Laboratories Broadcast Si2141 Layer 1 API


   API properties functions definitions
   FILE: Si2141_Properties_Functions.h
   Supported IC : Si2141
   Compiled for ROM 61 firmware 1_1_build_12
   Revision: 0.5
   Date: June 14 2019
**************************************************************************************/
#ifndef   _Si2141_PROPERTIES_FUNCTIONS_H_
#define   _Si2141_PROPERTIES_FUNCTIONS_H_

void          Si2141_storeUserProperties           (Si2141_PropObj   *prop);
unsigned char Si2141_PackProperty                  (Si2141_PropObj   *prop, unsigned int prop_code, int *data);
unsigned char Si2141_UnpackProperty                (Si2141_PropObj   *prop, unsigned int prop_code, int  data);
void          Si2141_storePropertiesDefaults       (Si2141_PropObj   *prop);

int  Si2141_downloadCOMMONProperties(L1_Si2141_Context *api);
int  Si2141_downloadDTVProperties   (L1_Si2141_Context *api);
int  Si2141_downloadTUNERProperties (L1_Si2141_Context *api);
int  Si2141_downloadAllProperties   (L1_Si2141_Context *api);

#endif /* _Si2141_PROPERTIES_FUNCTIONS_H_ */







