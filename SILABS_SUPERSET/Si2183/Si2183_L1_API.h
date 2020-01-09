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


   API functions prototypes used by commands and properties
   FILE: Si2183_L1_API.h
   Supported IC : Si2183
   Compiled for ROM 2 firmware 5_B_build_1
   Revision: V0.3.5.1
   Date: November 06 2015
**************************************************************************************/
/* Change log:
 As from V0.9.0.0:
  <new_feature>[superset] Adding tags to allow SILABS_SUPERSET use (one code, all configs)

 As from V0.0.0:
  Initial version (based on Si2164 code V0.3.4)
****************************************************************************************/
#ifndef    _Si2183_L1_API_H_
#define    _Si2183_L1_API_H_

#include "Silabs_L0_API.h"

#ifndef   SiLOGS
  #define SiLOGS   SiTRACE
#endif /* SiLOGS */

#ifndef   SILABS_SUPERSET
#ifdef    DEMOD_Si2183
  #define DEMOD_DVB_C
  #define DEMOD_DVB_C2
  #define DEMOD_DVB_S_S2_DSS
  #define DEMOD_DVB_T
  #define DEMOD_DVB_T2
  #define DEMOD_ISDB_T
  #define DEMOD_MCNS
  #define DEMOD_DVB_S2X
#endif /* DEMOD_Si2183 */
#endif /* SILABS_SUPERSET */

#include "Si2183_Commands.h"
#include "Si2183_Properties.h"
#include "Si2183_typedefs.h"
#include "Si2183_Commands_Prototypes.h"
#include "Si2183_Properties_Functions.h"

#define NO_Si2183_ERROR                     0x00
#define ERROR_Si2183_PARAMETER_OUT_OF_RANGE 0x01
#define ERROR_Si2183_ALLOCATING_CONTEXT     0x02
#define ERROR_Si2183_SENDING_COMMAND        0x03
#define ERROR_Si2183_CTS_TIMEOUT            0x04
#define ERROR_Si2183_ERR                    0x05
#define ERROR_Si2183_POLLING_CTS            0x06
#define ERROR_Si2183_POLLING_RESPONSE       0x07
#define ERROR_Si2183_LOADING_FIRMWARE       0x08
#define ERROR_Si2183_LOADING_BOOTBLOCK      0x09
#define ERROR_Si2183_STARTING_FIRMWARE      0x0a
#define ERROR_Si2183_SW_RESET               0x0b
#define ERROR_Si2183_INCOMPATIBLE_PART      0x0c
#define ERROR_Si2183_DISEQC_BUS_NOT_READY   0x0d
#define ERROR_Si2183_UNKNOWN_COMMAND        0xf0
#define ERROR_Si2183_UNKNOWN_PROPERTY       0xf1


unsigned char Si2183_L1_API_Init    (L1_Si2183_Context *api, signed   int add);
unsigned char Si2183_L1_API_Patch   (L1_Si2183_Context *api, signed   int iNbBytes, unsigned char *pucDataBuffer);
unsigned char Si2183_L1_CheckStatus (L1_Si2183_Context *api);
char*         Si2183_L1_API_ERROR_TEXT(signed   int error_code);
char*         Si2183_L1_API_TAG_TEXT  (void);
signed   int  Si2183_L1_GET_REG      (L1_Si2183_Context *api, unsigned char   reg_code_lsb, unsigned char   reg_code_mid, unsigned char   reg_code_msb);

#define Si2183_TAG Si2183_L1_API_TAG_TEXT


#ifdef    Si2183_GET_PROPERTY_STRING
void Si2183_L1_FillPropertyStringText(L1_Si2183_Context *api, unsigned int prop_code, const char *separator, char *msg);
#endif /* Si2183_GET_PROPERTY_STRING */

#endif /* _Si2183_L1_API_H_ */








