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
                  Silicon Laboratories Broadcast Si2158B Layer 1 API


   API functions definitions used by commands and properties
   FILE: Si2158B_L1_API.c
   Supported IC : Si2158B
   Compiled for ROM 51 firmware 4_1_build_3
   Revision: 0.1
   Tag:  ROM51_4_1_build_3_V0.1
   Date: June 23 2016
**************************************************************************************/
#define   Si2158B_COMMAND_PROTOTYPES

#include "Si2158B_L1_API.h"


/***********************************************************************************************************************
  Si2158B_L1_API_Init function
  Use:        software initialisation function
              Used to initialize the software context
  Returns:    0 if no error
  Comments:   It should be called first and once only when starting the application
  Parameter:   **ppapi         a pointer to the api context to initialize
  Parameter:  add            the Si2158B I2C address
  Porting:    Allocation errors need to be properly managed.
  Porting:    I2C initialization needs to be adapted to use the available I2C functions
 ***********************************************************************************************************************/
unsigned char    Si2158B_L1_API_Init      (L1_Si2158B_Context *api, int add) {
    api->i2c = &(api->i2cObj);

    L0_Init(api->i2c);
    L0_SetAddress(api->i2c, add, 0);

    api->cmd    = &(api->cmdObj);
    api->rsp    = &(api->rspObj);
    api->prop   = &(api->propObj);
    api->status = &(api->statusObj);
    api->propShadow        = &(api->propShadowObj);
    /* Set the propertyWriteMode to Si2158B_DOWNLOAD_ON_CHANGE to only download property settings on change (recommended) */
    /*      if propertyWriteMode is set to Si2158B_DOWNLOAD_ALWAYS the properties will be downloaded regardless of change */
    api->propertyWriteMode = DOWNLOAD_ON_CHANGE;
    api->load_control = SKIP_NONE;
    return NO_Si2158B_ERROR;
}
/***********************************************************************************************************************
  Si2158B_L1_API_Patch function
  Use:        Patch information function
              Used to send a number of bytes to the Si2158B. Useful to download the firmware.
  Returns:    0 if no error
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
unsigned char    Si2158B_L1_API_Patch     (L1_Si2158B_Context *api, int iNbBytes, unsigned char *pucDataBuffer) {
    int res;
    unsigned char rspByteBuffer[1];

    SiTRACE("Si2158B Patch %d bytes\n",iNbBytes);

    res = L0_WriteCommandBytes(api->i2c, iNbBytes, pucDataBuffer);
    if (res!=iNbBytes) {
      SiTRACE("Si2158B_L1_API_Patch error writing bytes: %s\n", Si2158B_L1_API_ERROR_TEXT(ERROR_Si2158B_LOADING_FIRMWARE) );
      return ERROR_Si2158B_LOADING_FIRMWARE;
    }

        res = Si2158B_pollForResponse(api, 1, rspByteBuffer);
        if (res != NO_Si2158B_ERROR) {
          SiTRACE("Si2158B_L1_API_Patch error 0x%02x polling response: %s\n", res, Si2158B_L1_API_ERROR_TEXT(res) );
          return ERROR_Si2158B_POLLING_RESPONSE;
        }

    return NO_Si2158B_ERROR;
}
/***********************************************************************************************************************
  Si2158B_L1_CheckStatus function
  Use:        Status information function
              Used to retrieve the status byte
  Returns:    0 if no error
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/
unsigned char    Si2158B_L1_CheckStatus   (L1_Si2158B_Context *api) {
    unsigned char rspByteBuffer[1];
    return Si2158B_pollForResponse(api, 1, rspByteBuffer);
}
/***********************************************************************************************************************
  Si2158B_L1_API_ERROR_TEXT function
  Use:        Error information function
              Used to retrieve a text based on an error code
  Returns:    the error text
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
char*            Si2158B_L1_API_ERROR_TEXT(int error_code) {
    switch (error_code) {
        case NO_Si2158B_ERROR                     : return (char *)"No Si2158B error";
        case ERROR_Si2158B_ALLOCATING_CONTEXT     : return (char *)"Error while allocating Si2158B context";
        case ERROR_Si2158B_PARAMETER_OUT_OF_RANGE : return (char *)"Si2158B parameter(s) out of range";
        case ERROR_Si2158B_SENDING_COMMAND        : return (char *)"Error while sending Si2158B command";
        case ERROR_Si2158B_CTS_TIMEOUT            : return (char *)"Si2158B CTS timeout";
        case ERROR_Si2158B_ERR                    : return (char *)"Si2158B Error (status 'err' bit 1)";
        case ERROR_Si2158B_POLLING_CTS            : return (char *)"Si2158B Error while polling CTS";
        case ERROR_Si2158B_POLLING_RESPONSE       : return (char *)"Si2158B Error while polling response";
        case ERROR_Si2158B_LOADING_FIRMWARE       : return (char *)"Si2158B Error while loading firmware";
        case ERROR_Si2158B_LOADING_BOOTBLOCK      : return (char *)"Si2158B Error while loading bootblock";
        case ERROR_Si2158B_STARTING_FIRMWARE      : return (char *)"Si2158B Error while starting firmware";
        case ERROR_Si2158B_SW_RESET               : return (char *)"Si2158B Error during software reset";
        case ERROR_Si2158B_INCOMPATIBLE_PART      : return (char *)"Si2158B Error Incompatible part";
        case ERROR_Si2158B_UNKNOWN_COMMAND        : return (char *)"Si2158B Error unknown command";
        case ERROR_Si2158B_UNKNOWN_PROPERTY       : return (char *)"Si2158B Error unknown property";
        case ERROR_Si2158B_TUNINT_TIMEOUT         : return (char *)"Si2158B Error TUNINT Timeout";
        case ERROR_Si2158B_xTVINT_TIMEOUT         : return (char *)"Si2158B Error xTVINT Timeout";
        default                                  : return (char *)"Unknown Si2158B error code";
    }
}
/***********************************************************************************************************************
  Si2158B_L1_API_TAG_TEXT function
  Use:        Error information function
              Used to retrieve a text containing the TAG information (related to the code version)
  Returns:    the TAG text
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
char*            Si2158B_L1_API_TAG_TEXT(void) { return (char *)"ROM51_4_1_build_3_V0.1";}








