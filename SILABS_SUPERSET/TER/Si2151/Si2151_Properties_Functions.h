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
                  Silicon Laboratories Broadcast Si2151 Layer 1 API


   API properties functions definitions
   FILE: Si2151_Properties_Functions.h
   Supported IC : Si2151
   Compiled for ROM 61 firmware 1_1_build_11
   Revision: 0.6
   Date: October 11 2016
**************************************************************************************/
#ifndef   _Si2151_PROPERTIES_FUNCTIONS_H_
#define   _Si2151_PROPERTIES_FUNCTIONS_H_

void          Si2151_storeUserProperties           (Si2151_PropObj   *prop);
unsigned char Si2151_PackProperty                  (Si2151_PropObj   *prop, unsigned int prop_code, int *data);
unsigned char Si2151_UnpackProperty                (Si2151_PropObj   *prop, unsigned int prop_code, int  data);
void          Si2151_storePropertiesDefaults       (Si2151_PropObj   *prop);

int  Si2151_downloadATVProperties   (L1_Si2151_Context *api);
int  Si2151_downloadCOMMONProperties(L1_Si2151_Context *api);
int  Si2151_downloadDTVProperties   (L1_Si2151_Context *api);
int  Si2151_downloadTUNERProperties (L1_Si2151_Context *api);
int  Si2151_downloadAllProperties   (L1_Si2151_Context *api);

#endif /* _Si2151_PROPERTIES_FUNCTIONS_H_ */







