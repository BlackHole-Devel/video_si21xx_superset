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


   API functions definitions used by commands and properties
   FILE: Si2183_L1_API.c
   Supported IC : Si2183
   Compiled for ROM 2 firmware 5_B_build_1
   Revision: V0.3.5.1
   Tag:  V0.3.5.1
   Date: November 06 2015
**************************************************************************************/
/* Change log:

 As from V0.2.5.0:
   <New_feature>[Config/DriveTS] In Si2183_L1_API_Init: setting TS property default strength and shape values, such that they can be
     controlled using SiLabs_API_TS_Strength_Shape and not get overwritten when calling Si2183_storeUserProperties.
     In Si2183_storeUserProperties, these properties are commented.

 As from V0.2.4.0:
   <New_feature>[Config/TS] In Si2183_L1_API_Init: setting TS property default values, such that they can be
     controlled using SiLabs_API_TS_Config and not get overwritten when calling Si2183_storeUserProperties.
     In Si2183_storeUserProperties, these properties are commented.

 As from V0.1.3.0:
   <new_feature>[Broadcast_i2c/demods]
     In Si2183_L1_API_Init:
       setting api->load_control to Si2183_SKIP_NONE to get the same behavior as previously by default.
     <new_feature>[DVB-S2/Multiple_Input_Stream]
     In Si2183_L1_API_Init: Setting api->MIS_capability to 0 by default.

 As from V0.0.7.0: <new_feature>[SPI/logs] In Si2183_L1_API_Init: setting api->spi_download_ms and api->i2c_download_ms to 0;

 As from V0.0.5.0:
  <improvement>[Code_size] Using the textBuffer in Si2183_L1_Context when filling text strings
    In Si2183_L1_API_Init

 As from V0.0.1.0:
  <new_feature/TESTPIPE> adding access to plp_info and tx_id for demod in T2
  <improvement>[SPI FW download] In Si2183_L1_API_Init: Settings adapted to SiLabs SOCKET EVB
   (which is wired to allow SPI download)

 As from V0.0.0:
  Initial version (based on Si2164 code V0.3.4)
**************************************************************************************/
#define   Si2183_COMMAND_PROTOTYPES

/* Before including the headers, define SiLevel and SiTAG */
#define   SiLEVEL          1
#define   SiTAG            api->i2c->tag
#include "Si2183_Platform_Definition.h"

/***********************************************************************************************************************
  Si2183_L1_API_Init function
  Use:        software initialisation function
              Used to initialize the software context
  Returns:    0 if no error
  Comments:   It should be called first and once only when starting the application
  Parameter:   **ppapi         a pointer to the api context to initialize
  Parameter:  add            the Si2183 I2C address
  Porting:    Allocation errors need to be properly managed.
  Porting:    I2C initialization needs to be adapted to use the available I2C functions
 ***********************************************************************************************************************/
unsigned char    Si2183_L1_API_Init      (L1_Si2183_Context *api, signed   int add) {
    api->i2c = &(api->i2cObj);

    L0_Init(api->i2c);
    L0_SetAddress(api->i2c, add, 0);

    api->cmd               = &(api->cmdObj);
    api->rsp               = &(api->rspObj);
    api->prop              = &(api->propObj);
    api->status            = &(api->statusObj);
    api->propShadow        = &(api->propShadowObj);
    api->msg               = &(api->msgBuffer[0]);
    /* Set the propertyWriteMode to Si2183_DOWNLOAD_ON_CHANGE to only download property settings on change (recommended) */
    /*      if propertyWriteMode is set to Si2183_DOWNLOAD_ALWAYS the properties will be downloaded regardless of change */
    api->propertyWriteMode = Si2183_DOWNLOAD_ON_CHANGE;
    /* SPI download default values */
    api->spi_download    = 0;
    api->spi_download_ms = 0;
    api->i2c_download_ms = 0;
    /* <porting> Set these values to match your SPI HW, or use 'SiLabs_API_SPI_Setup' to set them later on */
    api->spi_send_option = 0x01;
    api->spi_clk_pin     = Si2183_SPI_LINK_CMD_SPI_CONF_CLK_DISEQC_CMD;
    api->spi_clk_pola    = Si2183_SPI_LINK_CMD_SPI_CLK_POLA_RISING;
    api->spi_data_pin    = Si2183_SPI_LINK_CMD_SPI_CONF_DATA_MP_C;
    api->spi_data_order  = Si2183_SPI_LINK_CMD_SPI_DATA_DIR_LSB_FIRST;

    /* By default, we don't use I2C broadcast mode for FW download in demodulators */
    api->load_control    =  Si2183_SKIP_NONE;

#ifdef    DEMOD_DVB_C
    api->load_DVB_C_Blindlock_Patch = 0;
#endif /* DEMOD_DVB_C */
    /* Clock settings as per compilation flags                     */
    /*  For multi-frontend HW, these may be adapted later on,      */
    /*   using Si2183_L1_API_TER_Clock and Si2183_L1_API_SAT_Clock */
#ifdef    TERRESTRIAL_FRONT_END
#ifdef    DEMOD_DVB_T2
  api->cmd->dvbt2_fef.fef_tuner_flag  = Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_NOT_USED;
#endif /* DEMOD_DVB_T2 */
 #ifndef     Si2183_TER_CLOCK_SOURCE
  #define    Si2183_TER_CLOCK_SOURCE            Si2183_TER_Tuner_clock
 #endif   /* Si2183_TER_CLOCK_SOURCE */
    api->tuner_ter_clock_source  = Si2183_TER_CLOCK_SOURCE;
    api->tuner_ter_clock_control = Si2183_CLOCK_MANAGED;
    api->tuner_ter_agc_control   = 1;

 #ifndef     Si2183_CLOCK_MODE_TER
  #define    Si2183_CLOCK_MODE_TER                Si2183_START_CLK_CMD_CLK_MODE_CLK_CLKIO
 #endif   /* Si2183_CLOCK_MODE_TER */
    api->tuner_ter_clock_input = Si2183_CLOCK_MODE_TER;

 #ifndef     Si2183_REF_FREQUENCY_TER
  #define    Si2183_REF_FREQUENCY_TER                                             24
 #endif   /* Si2183_REF_FREQUENCY_TER */
    api->tuner_ter_clock_freq  = Si2183_REF_FREQUENCY_TER;
#endif /* TERRESTRIAL_FRONT_END */

#ifdef    SATELLITE_FRONT_END
 #ifndef     Si2183_SAT_CLOCK_SOURCE
  #define    Si2183_SAT_CLOCK_SOURCE            Si2183_Xtal_clock
 #endif   /* Si2183_SAT_CLOCK_SOURCE */
    api->tuner_sat_clock_source  = Si2183_SAT_CLOCK_SOURCE;
    api->tuner_sat_clock_control = Si2183_CLOCK_MANAGED;
    api->MIS_capability          = 0;

 #ifndef     Si2183_CLOCK_MODE_SAT
  #define    Si2183_CLOCK_MODE_SAT                Si2183_START_CLK_CMD_CLK_MODE_CLK_XTAL_IN
 #endif   /* Si2183_CLOCK_MODE_SAT */
    api->tuner_sat_clock_input = Si2183_CLOCK_MODE_SAT;

 #ifndef     Si2183_REF_FREQUENCY_SAT
  #define    Si2183_REF_FREQUENCY_SAT                                             16
 #endif   /* Si2183_REF_FREQUENCY_SAT */
    api->tuner_sat_clock_freq  = Si2183_REF_FREQUENCY_SAT;
#endif /* SATELLITE_FRONT_END */

#ifdef    Si2183_DD_TS_PINS_CMD
  api->cmd->dd_ts_pins.primary_ts_activity   = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_ACTIVITY_RUN;
  api->cmd->dd_ts_pins.secondary_ts_activity = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_ACTIVITY_RUN;
  api->cmd->dd_ts_pins.primary_ts_mode       = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_NOT_USED;
  api->cmd->dd_ts_pins.secondary_ts_mode     = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_NOT_USED;
#endif /* Si2183_DD_TS_PINS_CMD */
  /* Default settings for TS drive. Possibly overwritten during SW init using SiLabs_API_TS_Strength_Shape */
#ifdef    Si2183_DD_SEC_TS_SETUP_PAR_PROP
  api->prop->dd_sec_ts_setup_par.ts_data_strength                             =     3; /* (default     3) */
  api->prop->dd_sec_ts_setup_par.ts_data_shape                                =     2; /* (default     1) */
  api->prop->dd_sec_ts_setup_par.ts_clk_strength                              =     3; /* (default     3) */
  api->prop->dd_sec_ts_setup_par.ts_clk_shape                                 =     2; /* (default     1) */
#endif /* Si2183_DD_SEC_TS_SETUP_PAR_PROP */

#ifdef    Si2183_DD_SEC_TS_SETUP_SER_PROP
  api->prop->dd_sec_ts_setup_ser.ts_data_strength                             =     7; /* (default     3) */
  api->prop->dd_sec_ts_setup_ser.ts_data_shape                                =     0; /* (default     3) */
  api->prop->dd_sec_ts_setup_ser.ts_clk_strength                              =     7; /* (default    15) */
  api->prop->dd_sec_ts_setup_ser.ts_clk_shape                                 =     0; /* (default     3) */
#endif /* Si2183_DD_SEC_TS_SETUP_SER_PROP */

#ifdef    Si2183_DD_TS_SETUP_PAR_PROP
  api->prop->dd_ts_setup_par.ts_data_strength                                 =     3; /* (default     3) */
  api->prop->dd_ts_setup_par.ts_data_shape                                    =     2; /* (default     1) */
  api->prop->dd_ts_setup_par.ts_clk_strength                                  =     3; /* (default     3) */
  api->prop->dd_ts_setup_par.ts_clk_shape                                     =     2; /* (default     1) */
#endif /* Si2183_DD_TS_SETUP_PAR_PROP */

#ifdef    Si2183_DD_TS_SETUP_SER_PROP
  api->prop->dd_ts_setup_ser.ts_data_strength                                 =     7; /* (default    15) */
  api->prop->dd_ts_setup_ser.ts_data_shape                                    =     0; /* (default     3) */
  api->prop->dd_ts_setup_ser.ts_clk_strength                                  =     7; /* (default    15) */
  api->prop->dd_ts_setup_ser.ts_clk_shape                                     =     0; /* (default     3) */
#endif /* Si2183_DD_TS_SETUP_SER_PROP */

  /* Default settings for TS interface. Possibly overwritten during SW init using SiLabs_API_TS_Config */
  api->prop->dd_ts_mode.clock                = Si2183_DD_TS_MODE_PROP_CLOCK_AUTO_ADAPT                ; /* (default 'AUTO_FIXED') */
  api->prop->dd_ts_mode.clk_gapped_en        = Si2183_DD_TS_MODE_PROP_CLK_GAPPED_EN_DISABLED          ; /* (default 'DISABLED') */
  api->prop->dd_ts_mode.ts_err_polarity      = Si2183_DD_TS_MODE_PROP_TS_ERR_POLARITY_NOT_INVERTED    ; /* (default 'NOT_INVERTED') */
  api->prop->dd_ts_mode.serial_pin_selection = Si2183_DD_TS_MODE_PROP_SERIAL_PIN_SELECTION_D0         ; /* (default 'D0') */
  api->prop->dd_ts_setup_par.ts_clk_invert   = Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_INVERT_INVERTED     ; /* (default 'INVERTED') */
  api->prop->dd_ts_setup_ser.ts_clk_invert   = Si2183_DD_TS_SETUP_SER_PROP_TS_CLK_INVERT_INVERTED     ; /* (default 'INVERTED') */

  /* Initial standard selection based on compilation flags */
  #ifdef    DEMOD_DVB_T
    api->standard =  Si2183_DD_MODE_PROP_MODULATION_DVBT ; goto initial_standard_set;
  #endif /* DEMOD_DVB_T */
  #ifdef    DEMOD_DVB_T2
    api->standard =  Si2183_DD_MODE_PROP_MODULATION_DVBT2; goto initial_standard_set;
  #endif /* DEMOD_DVB_T2 */
  #ifdef    DEMOD_ISDB_T
    api->standard =  Si2183_DD_MODE_PROP_MODULATION_ISDBT; goto initial_standard_set;
  #endif /* DEMOD_ISDB_T */
  #ifdef    DEMOD_DVB_C
    api->standard =  Si2183_DD_MODE_PROP_MODULATION_DVBC ; goto initial_standard_set;
  #endif /* DEMOD_DVB_C  */
  #ifdef    DEMOD_DVB_C2
    api->standard =  Si2183_DD_MODE_PROP_MODULATION_DVBC2; goto initial_standard_set;
  #endif /* DEMOD_DVB_C2 */
  #ifdef    DEMOD_MCNS
    api->standard =  Si2183_DD_MODE_PROP_MODULATION_MCNS ; goto initial_standard_set;
  #endif /* DEMOD_MCNS */
#ifdef    SATELLITE_FRONT_END
    api->standard =  Si2183_DD_MODE_PROP_MODULATION_DVBS ; goto initial_standard_set;
#endif /* SATELLITE_FRONT_END */

    initial_standard_set:

    return NO_Si2183_ERROR;
}
/***********************************************************************************************************************
  Si2183_L1_API_Patch function
  Use:        Patch information function
              Used to send a number of bytes to the Si2183. Useful to download the firmware.
  Returns:    0 if no error
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
unsigned char    Si2183_L1_API_Patch     (L1_Si2183_Context *api, signed   int iNbBytes, unsigned char *pucDataBuffer) {
    signed   int res;
    unsigned char rspByteBuffer[1];

    SiTRACE("Si2183 Patch %d bytes\n",iNbBytes);

    res = L0_WriteCommandBytes(api->i2c, iNbBytes, pucDataBuffer);
    if (res!=iNbBytes) {
      SiTRACE("Si2183_L1_API_Patch error writing bytes: %s\n", Si2183_L1_API_ERROR_TEXT(ERROR_Si2183_LOADING_FIRMWARE) );
      return ERROR_Si2183_LOADING_FIRMWARE;
    }

    res = Si2183_pollForResponse(api, 1, rspByteBuffer);
    if (res != NO_Si2183_ERROR) {
      SiTRACE("Si2183_L1_API_Patch error 0x%02x polling response: %s\n", res, Si2183_L1_API_ERROR_TEXT(res) );
      return ERROR_Si2183_POLLING_RESPONSE;
    }

    return NO_Si2183_ERROR;
}
/***********************************************************************************************************************
  Si2183_L1_CheckStatus function
  Use:        Status information function
              Used to retrieve the status byte
  Returns:    0 if no error
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/
unsigned char    Si2183_L1_CheckStatus   (L1_Si2183_Context *api) {
    unsigned char rspByteBuffer[1];
    return Si2183_pollForResponse(api, 1, rspByteBuffer);
}
/***********************************************************************************************************************
  Si2183_L1_API_ERROR_TEXT function
  Use:        Error information function
              Used to retrieve a text based on an error code
  Returns:    the error text
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
char*            Si2183_L1_API_ERROR_TEXT(signed   int error_code) {
    switch (error_code) {
        case NO_Si2183_ERROR                     : return (char *)"No Si2183 error";
        case ERROR_Si2183_ALLOCATING_CONTEXT     : return (char *)"Error while allocating Si2183 context";
        case ERROR_Si2183_PARAMETER_OUT_OF_RANGE : return (char *)"Si2183 parameter(s) out of range";
        case ERROR_Si2183_SENDING_COMMAND        : return (char *)"Error while sending Si2183 command";
        case ERROR_Si2183_CTS_TIMEOUT            : return (char *)"Si2183 CTS timeout";
        case ERROR_Si2183_ERR                    : return (char *)"Si2183 Error (status 'err' bit 1)";
        case ERROR_Si2183_POLLING_CTS            : return (char *)"Si2183 Error while polling CTS";
        case ERROR_Si2183_POLLING_RESPONSE       : return (char *)"Si2183 Error while polling response";
        case ERROR_Si2183_LOADING_FIRMWARE       : return (char *)"Si2183 Error while loading firmware";
        case ERROR_Si2183_LOADING_BOOTBLOCK      : return (char *)"Si2183 Error while loading bootblock";
        case ERROR_Si2183_STARTING_FIRMWARE      : return (char *)"Si2183 Error while starting firmware";
        case ERROR_Si2183_SW_RESET               : return (char *)"Si2183 Error during software reset";
        case ERROR_Si2183_INCOMPATIBLE_PART      : return (char *)"Si2183 Error Incompatible part";
        case ERROR_Si2183_UNKNOWN_COMMAND        : return (char *)"Si2183 Error unknown command";
        case ERROR_Si2183_UNKNOWN_PROPERTY       : return (char *)"Si2183 Error unknown property";
        default                                  : return (char *)"Unknown Si2183 error code";
    }
}
/***********************************************************************************************************************
  Si2183_L1_API_TAG_TEXT function
  Use:        Error information function
              Used to retrieve a text containing the TAG information (related to the code version)
  Returns:    the TAG text
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
char*            Si2183_L1_API_TAG_TEXT(void) { return (char *)"V0.3.5.1";}

/************************************************************************************************************************
  NAME: Si2183_L1_Status
  DESCRIPTION: Calls the Si2183 global status function (DD_STATUS) and then the standard-specific status functions
  Porting:    Remove the un-necessary functions calls, if any. (Checking the TPS status may not be required)

  Parameter:  Pointer to Si2183 Context
  Returns:    1 if the current modulation is valid, 0 otherwise
************************************************************************************************************************/
int Si2183_L1_Status            (L1_Si2183_Context *api)
{
    /* Call the demod global status function */
    Si2183_L1_DD_STATUS (api, Si2183_DD_STATUS_CMD_INTACK_OK);

    /* Call the standard-specific status function */
    switch (api->rsp->dd_status.modulation)
    {
#ifdef    DEMOD_DVB_T
      case Si2183_DD_STATUS_RESPONSE_MODULATION_DVBT : { Si2183_L1_DVBT_STATUS  (api, Si2183_DVBT_STATUS_CMD_INTACK_OK );
        break;
      }
#endif /* DEMOD_DVB_T */

#ifdef    DEMOD_DVB_T2
      case Si2183_DD_STATUS_RESPONSE_MODULATION_DVBT2: { Si2183_L1_DVBT2_STATUS (api, Si2183_DVBT2_STATUS_CMD_INTACK_OK);
        break;
      }
#endif /* DEMOD_DVB_T2 */

#ifdef    DEMOD_DVB_C
      case Si2183_DD_STATUS_RESPONSE_MODULATION_DVBC : { Si2183_L1_DVBC_STATUS  (api, Si2183_DVBC_STATUS_CMD_INTACK_OK );
        break;
      }
#endif /* DEMOD_DVB_C */

#ifdef    DEMOD_DVB_C2
      case Si2183_DD_STATUS_RESPONSE_MODULATION_DVBC2: { Si2183_L1_DVBC2_STATUS (api, Si2183_DVBC2_STATUS_CMD_INTACK_OK );
        break;
      }
#endif /* DEMOD_DVB_C2 */

#ifdef    DEMOD_DVB_S_S2_DSS
      case Si2183_DD_STATUS_RESPONSE_MODULATION_DSS  :
      case Si2183_DD_STATUS_RESPONSE_MODULATION_DVBS : { Si2183_L1_DVBS_STATUS  (api, Si2183_DVBS_STATUS_CMD_INTACK_OK );
        break;
      }
      case Si2183_DD_STATUS_RESPONSE_MODULATION_DVBS2: { Si2183_L1_DVBS2_STATUS (api, Si2183_DVBS2_STATUS_CMD_INTACK_OK);
        break;
      }
#endif /* DEMOD_DVB_S_S2_DSS */

      default                                  : { return 0; break; }
    }

    switch (api->rsp->dd_status.modulation)
    {
#ifdef    DEMOD_DVB_T2
      case Si2183_DD_STATUS_RESPONSE_MODULATION_DVBT2:
#endif /* DEMOD_DVB_T2 */

#ifdef    DEMOD_DVB_S_S2_DSS
      case Si2183_DD_STATUS_RESPONSE_MODULATION_DVBS2: { Si2183_L1_DD_FER (api, Si2183_DD_FER_CMD_RST_RUN);
        break;
      }
#endif /* DEMOD_DVB_S_S2_DSS */

      default                                  : { Si2183_L1_DD_PER (api, Si2183_DD_PER_CMD_RST_RUN);
        break;
      }
    }
#ifdef    DEMOD_DVB_T
    switch (api->rsp->dd_status.modulation)
    {
      case Si2183_DD_STATUS_RESPONSE_MODULATION_DVBT : {
                                                   Si2183_L1_DVBT_TPS_EXTRA (api);
        break;
      }
      default                                  : { break; }
    }
#endif /* DEMOD_DVB_T */

 return 1;
}







