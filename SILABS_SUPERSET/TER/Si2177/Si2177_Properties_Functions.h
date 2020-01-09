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
                  Silicon Laboratories Broadcast Si2177 Layer 1 API


   API properties functions definitions
   FILE: Si2177_Properties_Functions.h
   Supported IC : Si2177
   Compiled for ROM 50 firmware 3_1_build_3
   Revision: 0.1
   Date: June 30 2015
**************************************************************************************/
#ifndef   _Si2177_PROPERTIES_FUNCTIONS_H_
#define   _Si2177_PROPERTIES_FUNCTIONS_H_

void          Si2177_storeUserProperties           (Si2177_PropObj   *prop);
unsigned char Si2177_PackProperty                  (Si2177_PropObj   *prop, unsigned int prop_code, int *data);
unsigned char Si2177_UnpackProperty                (Si2177_PropObj   *prop, unsigned int prop_code, int  data);
void          Si2177_storePropertiesDefaults       (Si2177_PropObj   *prop);

int  Si2177_downloadATVProperties   (L1_Si2177_Context *api);
int  Si2177_downloadCOMMONProperties(L1_Si2177_Context *api);
int  Si2177_downloadDTVProperties   (L1_Si2177_Context *api);
int  Si2177_downloadTUNERProperties (L1_Si2177_Context *api);
int  Si2177_downloadAllProperties   (L1_Si2177_Context *api);

#endif /* _Si2177_PROPERTIES_FUNCTIONS_H_ */







