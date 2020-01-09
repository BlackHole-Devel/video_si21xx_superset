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
                  Silicon Laboratories Broadcast Si2147 Layer 1 API


   API properties functions definitions
   FILE: Si2147_Properties_Functions.h
   Supported IC : Si2147
   Compiled for ROM 50 firmware 3_1_build_3
   Revision: 0.1
   Date: June 30 2015
**************************************************************************************/
#ifndef   _Si2147_PROPERTIES_FUNCTIONS_H_
#define   _Si2147_PROPERTIES_FUNCTIONS_H_

void          Si2147_storeUserProperties           (Si2147_PropObj *prop);
int           Si2147_downloadAllProperties         (L1_Si2147_Context *api);

unsigned char Si2147_PackProperty                  (Si2147_PropObj   *prop, unsigned int prop_code, int *data);
unsigned char Si2147_UnpackProperty                (Si2147_PropObj   *prop, unsigned int prop_code, int  data);
void          Si2147_storePropertiesDefaults       (Si2147_PropObj   *prop);

int  Si2147_downloadCOMMONProperties(L1_Si2147_Context *api);
int  Si2147_downloadDTVProperties   (L1_Si2147_Context *api);
int  Si2147_downloadTUNERProperties (L1_Si2147_Context *api);

#endif /* _Si2147_PROPERTIES_FUNCTIONS_H_ */







