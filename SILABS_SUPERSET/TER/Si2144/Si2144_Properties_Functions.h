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
                  Silicon Laboratories Broadcast Si2144 Layer 1 API


   API properties functions definitions
   FILE: Si2144_Properties_Functions.h
   Supported IC : Si2144
   Compiled for ROM 62 firmware 2_1_build_5
   Revision: 0.1
   Date: July 07 2017
**************************************************************************************/
#ifndef   _Si2144_PROPERTIES_FUNCTIONS_H_
#define   _Si2144_PROPERTIES_FUNCTIONS_H_

void          Si2144_storeUserProperties           (Si2144_PropObj   *prop);
unsigned char Si2144_PackProperty                  (Si2144_PropObj   *prop, unsigned int prop_code, signed   int *data);
unsigned char Si2144_UnpackProperty                (Si2144_PropObj   *prop, unsigned int prop_code, signed   int  data);
void          Si2144_storePropertiesDefaults       (Si2144_PropObj   *prop);

signed   int  Si2144_downloadCOMMONProperties(L1_Si2144_Context *api);
signed   int  Si2144_downloadDTVProperties   (L1_Si2144_Context *api);
signed   int  Si2144_downloadTUNERProperties (L1_Si2144_Context *api);
signed   int  Si2144_downloadAllProperties   (L1_Si2144_Context *api);

#endif /* _Si2144_PROPERTIES_FUNCTIONS_H_ */







