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
                  Silicon Laboratories Broadcast Si2146 Layer 1 API
   API functions prototypes used by commands and properties
   FILE: Si2146_L1_API.h
   Supported IC : Si2146
   Compiled for ROM 11 firmware 1_1_build_3
   Revision: 0.1
   Date: December 23 2011
**************************************************************************************/
#ifndef    _Si2146_L1_API_H_
#define    _Si2146_L1_API_H_

#include "Silabs_L0_API.h"

#include "Si2146_Commands.h"
#include "Si2146_Properties.h"
#include "Si2146_typedefs.h"
#include "Si2146_Commands_Prototypes.h"

#define NO_Si2146_ERROR                     0x00
#define ERROR_Si2146_PARAMETER_OUT_OF_RANGE 0x01
#define ERROR_Si2146_ALLOCATING_CONTEXT     0x02
#define ERROR_Si2146_SENDING_COMMAND        0x03
#define ERROR_Si2146_CTS_TIMEOUT            0x04
#define ERROR_Si2146_ERR                    0x05
#define ERROR_Si2146_POLLING_CTS            0x06
#define ERROR_Si2146_POLLING_RESPONSE       0x07
#define ERROR_Si2146_LOADING_FIRMWARE       0x08
#define ERROR_Si2146_LOADING_BOOTBLOCK      0x09
#define ERROR_Si2146_STARTING_FIRMWARE      0x0a
#define ERROR_Si2146_SW_RESET               0x0b
#define ERROR_Si2146_INCOMPATIBLE_PART      0x0c
/* _specific_error_value_insertion_start */
#define ERROR_Si2146_TUNINT_TIMEOUT         0x0d
#define ERROR_Si2146_xTVINT_TIMEOUT         0x0e
/* _specific_error_value_insertion_point */

/* define PART_INTEGRITY_CHECKS (here) and the expected part number, chip rev, pmajor, pminor, and romid (in Si2146_L1_API.c) to use integrity checking */
#undef PART_INTEGRITY_CHECKS
/* chip rev constants for integrity checking */
extern const char Si2146_chiprev;
extern const char Si2146_part;
extern const char Si2146_partMajorVersion;
extern const char Si2146_partMinorVersion;
extern const char Si2146_partRomid;

unsigned char Si2146_L1_API_Init      (L1_Si2146_Context *api, int add);
unsigned char Si2146_L1_API_Patch     (L1_Si2146_Context *api, int iNbBytes, unsigned char *pucDataBuffer);
unsigned char Si2146_L1_CheckStatus   (L1_Si2146_Context *api);
char*         Si2146_L1_API_ERROR_TEXT(unsigned char  error_code);
char*         Si2146_L1_API_TAG_TEXT  (void);

#define Si2146_TAG Si2146_L1_API_TAG_TEXT


#ifdef    Si2146_GET_PROPERTY_STRING
void Si2146_L1_FillPropertyStringText(L1_Si2146_Context *api, unsigned int prop_code, char *separator, char *msg);
#endif /* Si2146_GET_PROPERTY_STRING */

#endif /* _Si2146_L1_API_H_ */



