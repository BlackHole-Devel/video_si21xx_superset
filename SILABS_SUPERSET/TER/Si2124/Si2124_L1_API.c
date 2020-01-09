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
                  Silicon Laboratories Broadcast Si2124 Layer 1 API


   API functions definitions used by commands and properties
   FILE: Si2124_L1_API.c
   Supported IC : Si2124
   Compiled for ROM 62 firmware 2_1_build_5
   Revision: 0.2
   Tag:  ROM62_2_1_build_5_V0.2
   Date: July 24 2017
**************************************************************************************/
#ifdef    TER_TUNER_SILABS
    /* Before including the headers, define SiLevel and SiTAG */
    #define   SiLEVEL          1
    #define   SiTAG            api->i2c->tag
#endif /* TER_TUNER_SILABS */

#include "Si2124_L1_API.h"


/***********************************************************************************************************************
  Si2124_L1_API_Init function
  Use:        software initialization function
              Used to initialize the software context
  Returns:    0 if no error
  Comments:   It should be called first and once only when starting the application
  Parameter:  *api         a pointer to Si2124 Context
  Parameter:  add          the Si2124 I2C address
  Porting:    Allocation errors need to be properly managed.
  Porting:    I2C initialization needs to be adapted to use the available I2C functions
 ***********************************************************************************************************************/
unsigned char    Si2124_L1_API_Init      (L1_Si2124_Context *api, signed   int add) {
    api->i2c = &(api->i2cObj);

    L0_Init(api->i2c);
    L0_SetAddress(api->i2c, add, 0);

    api->cmd               = &(api->cmdObj);
    api->rsp               = &(api->rspObj);
    api->prop              = &(api->propObj);
    api->status            = &(api->statusObj);
    api->propShadow        = &(api->propShadowObj);
    /* Set the propertyWriteMode to Si2124_DOWNLOAD_ON_CHANGE to only download property settings on change (recommended) */
    /*      if propertyWriteMode is set to Si2124_DOWNLOAD_ALWAYS the properties will be downloaded regardless of change */
    api->propertyWriteMode = DOWNLOAD_ON_CHANGE;
    /* The load_control flag is used to control the interaction between Si2124_PowerUpWithPatch() and Si2124_PowerUpUsingBroadcastI2C().  */
    /* the default is SKIP_NONE */
    api->load_control = SKIP_NONE;
    api->rsp->get_rev.pn = 0;
    #ifdef    Si2124_TUNER_BLOCKED_VCO_PROP
        api->prop->tuner_blocked_vco.vco_code           = 0x8000; /* (default 0x8000) */
    #endif /* Si2124_TUNER_BLOCKED_VCO_PROP */
    #ifdef    Si2124_TUNER_BLOCKED_VCO2_PROP
        api->prop->tuner_blocked_vco2.vco_code          = 0x8000; /* (default 0x8000) */
    #endif /* Si2124_TUNER_BLOCKED_VCO2_PROP */
    #ifdef    Si2124_TUNER_BLOCKED_VCO3_PROP
        api->prop->tuner_blocked_vco3.vco_code          = 0x8000; /* (default 0x8000) */
    #endif /* Si2124_TUNER_BLOCKED_VCO3_PROP */
    return NO_Si2124_ERROR;
}
/***********************************************************************************************************************
  Si2124_L1_API_Patch function
  Use:        Patch information function
              Used to send a number of bytes to the Si2124. Useful to download the firmware.
  Returns:    0 if no error
 ***********************************************************************************************************************/
unsigned char    Si2124_L1_API_Patch     (L1_Si2124_Context *api, signed   int iNbBytes, unsigned char *pucDataBuffer) {
    signed   int res;
    unsigned char rspByteBuffer[1];

    SiTRACE("Si2124 Patch %d bytes\n",iNbBytes);

    res = L0_WriteCommandBytes(api->i2c, iNbBytes, pucDataBuffer);
    if (res!=iNbBytes) {
      SiTRACE("Si2124_L1_API_Patch error writing bytes: %s\n", Si2124_L1_API_ERROR_TEXT(ERROR_Si2124_LOADING_FIRMWARE) );
      return ERROR_Si2124_LOADING_FIRMWARE;
    }

    res = Si2124_pollForResponse(api, 1, rspByteBuffer);
    if (res != NO_Si2124_ERROR) {
      SiTRACE("Si2124_L1_API_Patch error 0x%02x polling response: %s\n", res, Si2124_L1_API_ERROR_TEXT(res) );
      return ERROR_Si2124_POLLING_RESPONSE;
    }

    return NO_Si2124_ERROR;
}
/***********************************************************************************************************************
  Si2124_L1_CheckStatus function
  Use:        Status information function
              Used to retrieve the status byte
  Returns:    0 if no error
 ***********************************************************************************************************************/
unsigned char    Si2124_L1_CheckStatus   (L1_Si2124_Context *api) {
    unsigned char rspByteBuffer[1];
    return Si2124_pollForResponse(api, 1, rspByteBuffer);
}
/***********************************************************************************************************************
  Si2124_L1_API_ERROR_TEXT function
  Use:        Error information function
              Used to retrieve a text based on an error code
  Returns:    the error text
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
char*            Si2124_L1_API_ERROR_TEXT(signed   int error_code) {
    switch (error_code) {
        case NO_Si2124_ERROR                     : return (char *)"No Si2124 error";
        case ERROR_Si2124_ALLOCATING_CONTEXT     : return (char *)"Error while allocating Si2124 context";
        case ERROR_Si2124_PARAMETER_OUT_OF_RANGE : return (char *)"Si2124 parameter(s) out of range";
        case ERROR_Si2124_SENDING_COMMAND        : return (char *)"Error while sending Si2124 command";
        case ERROR_Si2124_CTS_TIMEOUT            : return (char *)"Si2124 CTS timeout";
        case ERROR_Si2124_ERR                    : return (char *)"Si2124 Error (status 'err' bit 1)";
        case ERROR_Si2124_POLLING_CTS            : return (char *)"Si2124 Error while polling CTS";
        case ERROR_Si2124_POLLING_RESPONSE       : return (char *)"Si2124 Error while polling response";
        case ERROR_Si2124_LOADING_FIRMWARE       : return (char *)"Si2124 Error while loading firmware";
        case ERROR_Si2124_LOADING_BOOTBLOCK      : return (char *)"Si2124 Error while loading bootblock";
        case ERROR_Si2124_STARTING_FIRMWARE      : return (char *)"Si2124 Error while starting firmware";
        case ERROR_Si2124_SW_RESET               : return (char *)"Si2124 Error during software reset";
        case ERROR_Si2124_INCOMPATIBLE_PART      : return (char *)"Si2124 Error Incompatible part";
        case ERROR_Si2124_UNKNOWN_COMMAND        : return (char *)"Si2124 Error unknown command";
        case ERROR_Si2124_UNKNOWN_PROPERTY       : return (char *)"Si2124 Error unknown property";
        case ERROR_Si2124_TUNINT_TIMEOUT         : return (char *)"Si2124 Error TUNINT Timeout";
        case ERROR_Si2124_xTVINT_TIMEOUT         : return (char *)"Si2124 Error xTVINT Timeout";
        default                                  : return (char *)"Unknown Si2124 error code";
    }
}
/***********************************************************************************************************************
  Si2124_L1_API_TAG_TEXT function
  Use:        Used to retrieve a text containing the TAG information (related to the code version)
  Returns:    the TAG text
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
char*            Si2124_L1_API_TAG_TEXT(void) { return (char *)"ROM62_2_1_build_5_V0.2";}
