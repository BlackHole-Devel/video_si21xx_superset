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
                  Silicon Laboratories Broadcast Si2148 Layer 1 API


   API functions definitions used by commands and properties
   FILE: Si2148_L1_API.c
   Supported IC : Si2148
   Compiled for ROM 33 firmware 2_1_build_11
   Revision: 0.2
   Tag:  Si2148_ROM33_21b11_V0.2
   Date: March 12 2014
**************************************************************************************/
#define   Si2148_COMMAND_PROTOTYPES

#include "Si2148_L1_API.h"


/***********************************************************************************************************************
  Si2148_L1_API_Init function
  Use:        software initialisation function
              Used to initialize the software context
  Returns:    0 if no error
  Comments:   It should be called first and once only when starting the application
  Parameter:   **ppapi         a pointer to the api context to initialize
  Parameter:  add            the Si2148 I2C address
  Porting:    Allocation errors need to be properly managed.
  Porting:    I2C initialization needs to be adapted to use the available I2C functions
 ***********************************************************************************************************************/
unsigned char    Si2148_L1_API_Init      (L1_Si2148_Context *api, int add) {
    api->i2c = &(api->i2cObj);

    L0_Init(api->i2c);
    L0_SetAddress(api->i2c, add, 0);

    api->cmd    = &(api->cmdObj);
    api->rsp    = &(api->rspObj);
    api->prop   = &(api->propObj);
    api->status = &(api->statusObj);

    return NO_Si2148_ERROR;
}
/***********************************************************************************************************************
  Si2148_L1_API_Patch function
  Use:        Patch information function
              Used to send a number of bytes to the Si2148. Useful to download the firmware.
  Returns:    0 if no error
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
unsigned char    Si2148_L1_API_Patch     (L1_Si2148_Context *api, int iNbBytes, unsigned char *pucDataBuffer) {
    int res;
    unsigned char rspByteBuffer[1];

    SiTRACE("Si2148 Patch %d bytes\n",iNbBytes);

    res = L0_WriteCommandBytes(api->i2c, iNbBytes, pucDataBuffer);
    if (res!=iNbBytes) {
      SiTRACE("Si2148_L1_API_Patch error writing bytes: %s\n", Si2148_L1_API_ERROR_TEXT(ERROR_Si2148_LOADING_FIRMWARE) );
      return ERROR_Si2148_LOADING_FIRMWARE;
    }

    res = Si2148_pollForResponse(api, 1, rspByteBuffer);
    if (res != NO_Si2148_ERROR) {
      SiTRACE("Si2148_L1_API_Patch error 0x%02x polling response: %s\n", res, Si2148_L1_API_ERROR_TEXT(res) );
      return ERROR_Si2148_POLLING_RESPONSE;
    }

    return NO_Si2148_ERROR;
}
/***********************************************************************************************************************
  Si2148_L1_CheckStatus function
  Use:        Status information function
              Used to retrieve the status byte
  Returns:    0 if no error
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/
unsigned char    Si2148_L1_CheckStatus   (L1_Si2148_Context *api) {
    unsigned char rspByteBuffer[1];
    return Si2148_pollForResponse(api, 1, rspByteBuffer);
}
/***********************************************************************************************************************
  Si2148_L1_API_ERROR_TEXT function
  Use:        Error information function
              Used to retrieve a text based on an error code
  Returns:    the error text
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
char*            Si2148_L1_API_ERROR_TEXT(int error_code) {
    switch (error_code) {
        case NO_Si2148_ERROR                     : return (char *)"No Si2148 error";
        case ERROR_Si2148_ALLOCATING_CONTEXT     : return (char *)"Error while allocating Si2148 context";
        case ERROR_Si2148_PARAMETER_OUT_OF_RANGE : return (char *)"Si2148 parameter(s) out of range";
        case ERROR_Si2148_SENDING_COMMAND        : return (char *)"Error while sending Si2148 command";
        case ERROR_Si2148_CTS_TIMEOUT            : return (char *)"Si2148 CTS timeout";
        case ERROR_Si2148_ERR                    : return (char *)"Si2148 Error (status 'err' bit 1)";
        case ERROR_Si2148_POLLING_CTS            : return (char *)"Si2148 Error while polling CTS";
        case ERROR_Si2148_POLLING_RESPONSE       : return (char *)"Si2148 Error while polling response";
        case ERROR_Si2148_LOADING_FIRMWARE       : return (char *)"Si2148 Error while loading firmware";
        case ERROR_Si2148_LOADING_BOOTBLOCK      : return (char *)"Si2148 Error while loading bootblock";
        case ERROR_Si2148_STARTING_FIRMWARE      : return (char *)"Si2148 Error while starting firmware";
        case ERROR_Si2148_SW_RESET               : return (char *)"Si2148 Error during software reset";
        case ERROR_Si2148_INCOMPATIBLE_PART      : return (char *)"Si2148 Error Incompatible part";
        case ERROR_Si2148_UNKNOWN_COMMAND        : return (char *)"Si2148 Error unknown command";
        case ERROR_Si2148_UNKNOWN_PROPERTY       : return (char *)"Si2148 Error unknown property";
        case ERROR_Si2148_TUNINT_TIMEOUT         : return (char *)"Si2148 Error TUNINT Timeout";
        case ERROR_Si2148_xTVINT_TIMEOUT         : return (char *)"Si2148 Error xTVINT Timeout";
        case ERROR_Si2148_CRC_CHECK_ERROR        : return (char *)"Si2148 Error CRC Check Error";
        default                                  : return (char *)"Unknown Si2148 error code";
    }
}
/***********************************************************************************************************************
  Si2148_L1_API_TAG_TEXT function
  Use:        Error information function
              Used to retrieve a text containing the TAG information (related to the code version)
  Returns:    the TAG text
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
char*            Si2148_L1_API_TAG_TEXT(void) { return (char *)"Si2148_ROM33_21b11_V0.2";}








