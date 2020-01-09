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
                  Silicon Laboratories Broadcast Si2176 Layer 1 API
   API functions definitions used by commands and properties
   FILE: Si2176_L1_API.c
   Supported IC : Si2176
   Compiled for ROM 13 firmware 3_2_build_6
   Revision: 0.1
   Tag:  TAGNAME
   Date: December 22 2011
**************************************************************************************/
#define   Si2176_COMMAND_PROTOTYPES

#include "Si2176_L1_API.h"

/*chip rev constants for integrity checking */
const char Si2176_chiprev          =  2;
/* Last 2 digits of part number */
const char Si2176_part             =  76; /* Change this value if using a chip other than an Si2176 */
const char Si2176_partMajorVersion = '3';
const char Si2176_partMinorVersion = '2';
const char Si2176_partRomid        =  0x13;


/***********************************************************************************************************************
  Si2176_L1_API_Init function
  Use:        software initialisation function
              Used to initialize the software context
  Returns:    0 if no error
  Comments:   It should be called first and once only when starting the application
  Parameter:   **ppapi         a pointer to the api context to initialize
  Parameter:  add            the Si2176 I2C address
  Porting:    Allocation errors need to be properly managed.
  Porting:    I2C initialization needs to be adapted to use the available I2C functions
 ***********************************************************************************************************************/
unsigned char    Si2176_L1_API_Init      (L1_Si2176_Context *api, int add) {
    api->i2c = &(api->i2cObj);

    L0_Init(api->i2c);
    L0_SetAddress(api->i2c, add, 0);

    api->cmd    = &(api->cmdObj);
    api->rsp    = &(api->rspObj);
    api->prop   = &(api->propObj);
    api->status = &(api->statusObj);

    api->part             = Si2176_part;
    api->chiprev          = Si2176_chiprev;
    api->partMajorVersion = Si2176_partMajorVersion;
    api->partMinorVersion = Si2176_partMinorVersion;
    api->partRomid        = Si2176_partRomid;

    return NO_Si2176_ERROR;
}
/***********************************************************************************************************************
  Si2176_L1_API_Patch function
  Use:        Patch information function
              Used to send a number of bytes to the Si2176. Useful to download the firmware.
  Returns:    0 if no error
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
unsigned char    Si2176_L1_API_Patch     (L1_Si2176_Context *api, int iNbBytes, unsigned char *pucDataBuffer) {
    unsigned char res;
    unsigned char rspByteBuffer[1];

    SiTRACE("Si2176 Patch %d bytes\n",iNbBytes);

    res = L0_WriteCommandBytes(api->i2c, iNbBytes, pucDataBuffer);
    if (res!=iNbBytes) {
      SiTRACE("Si2176_L1_API_Patch error 0x%02x writing bytes: %s\n", res, Si2176_L1_API_ERROR_TEXT(res) );
      return res;
    }

    res = Si2176_pollForResponse(api, 1, rspByteBuffer);
    if (res != NO_Si2176_ERROR) {
      SiTRACE("Si2176_L1_API_Patch error 0x%02x polling response: %s\n", res, Si2176_L1_API_ERROR_TEXT(res) );
      return ERROR_Si2176_POLLING_RESPONSE;
    }

    return NO_Si2176_ERROR;
}
/***********************************************************************************************************************
  Si2176_L1_CheckStatus function
  Use:        Status information function
              Used to retrieve the status byte
  Returns:    0 if no error
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/
unsigned char    Si2176_L1_CheckStatus   (L1_Si2176_Context *api) {
    unsigned char rspByteBuffer[1];
    return Si2176_pollForResponse(api, 1, rspByteBuffer);
}
/***********************************************************************************************************************
  Si2176_L1_API_ERROR_TEXT function
  Use:        Error information function
              Used to retrieve a text based on an error code
  Returns:    the error text
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
char*            Si2176_L1_API_ERROR_TEXT(unsigned char error_code) {
    switch (error_code) {
        case NO_Si2176_ERROR                     : return (char *)"No Si2176 error";
        case ERROR_Si2176_ALLOCATING_CONTEXT     : return (char *)"Error while allocating Si2176 context";
        case ERROR_Si2176_PARAMETER_OUT_OF_RANGE : return (char *)"Si2176 parameter(s) out of range";
        case ERROR_Si2176_SENDING_COMMAND        : return (char *)"Error while sending Si2176 command";
        case ERROR_Si2176_CTS_TIMEOUT            : return (char *)"Si2176 CTS timeout";
        case ERROR_Si2176_ERR                    : return (char *)"Si2176 Error (status 'err' bit 1)";
        case ERROR_Si2176_POLLING_CTS            : return (char *)"Si2176 Error while polling CTS";
        case ERROR_Si2176_POLLING_RESPONSE       : return (char *)"Si2176 Error while polling response";
        case ERROR_Si2176_LOADING_FIRMWARE       : return (char *)"Si2176 Error while loading firmware";
        case ERROR_Si2176_LOADING_BOOTBLOCK      : return (char *)"Si2176 Error while loading bootblock";
        case ERROR_Si2176_STARTING_FIRMWARE      : return (char *)"Si2176 Error while starting firmware";
        case ERROR_Si2176_SW_RESET               : return (char *)"Si2176 Error during software reset";
        case ERROR_Si2176_INCOMPATIBLE_PART      : return (char *)"Si2176 Error Incompatible part";
/* _specific_error_text_string_insertion_start */
        case ERROR_Si2176_TUNINT_TIMEOUT         : return (char *)"Si2176 Error TUNINT Timeout";
        case ERROR_Si2176_xTVINT_TIMEOUT         : return (char *)"Si2176 Error xTVINT Timeout";
/* _specific_error_text_string_insertion_point */
        default                                  : return (char *)"Unknown Si2176 error code";
    }
}
/***********************************************************************************************************************
  Si2176_L1_API_TAG_TEXT function
  Use:        Error information function
              Used to retrieve a text containing the TAG information (related to the code version)
  Returns:    the TAG text
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
char*            Si2176_L1_API_TAG_TEXT(void) { return (char *)"TAGNAME";}

/* _specific_code_insertion_start */
/* _specific_code_insertion_point */





