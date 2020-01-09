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
                  Silicon Laboratories Broadcast Si2157 Layer 1 API


   API properties functions definitions
   FILE: Si2157_Properties_Functions.h
   Supported IC : Si2157
   Compiled for ROM 50 firmware 3_1_build_3
   Revision: 0.1
   Date: June 29 2015
**************************************************************************************/
#ifndef   _Si2157_PROPERTIES_FUNCTIONS_H_
#define   _Si2157_PROPERTIES_FUNCTIONS_H_

void          Si2157_storeUserProperties           (Si2157_PropObj   *prop);
unsigned char Si2157_PackProperty                  (Si2157_PropObj   *prop, unsigned int prop_code, int *data);
unsigned char Si2157_UnpackProperty                (Si2157_PropObj   *prop, unsigned int prop_code, int  data);
void          Si2157_storePropertiesDefaults       (Si2157_PropObj   *prop);

int  Si2157_downloadATVProperties   (L1_Si2157_Context *api);
int  Si2157_downloadCOMMONProperties(L1_Si2157_Context *api);
int  Si2157_downloadDTVProperties   (L1_Si2157_Context *api);
int  Si2157_downloadTUNERProperties (L1_Si2157_Context *api);
int  Si2157_downloadAllProperties   (L1_Si2157_Context *api);

#endif /* _Si2157_PROPERTIES_FUNCTIONS_H_ */







