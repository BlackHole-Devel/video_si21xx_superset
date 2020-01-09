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
                  Silicon Laboratories Broadcast Si2177 Layer 1 API


   API properties definitions
   FILE: Si2177_L1_Properties.c
   Supported IC : Si2177
   Compiled for ROM 50 firmware 3_1_build_3
   Revision: 0.1
   Tag:  ROM50_3_1_build_3_V0.1
   Date: June 30 2015
**************************************************************************************/
#define   Si2177_COMMAND_PROTOTYPES

#include "Si2177_L1_API.h"


/***********************************************************************************************************************
  Si2177_L1_SetProperty function
  Use:        property set function
              Used to call L1_SET_PROPERTY with the property Id and data provided.
  Parameter: *api     the Si2177 context
  Parameter: prop     the property Id
  Parameter: data     the property bytes
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
unsigned char Si2177_L1_SetProperty         (L1_Si2177_Context *api, unsigned int prop_code, int  data) {
    unsigned char  reserved          = 0;
    return Si2177_L1_SET_PROPERTY (api, reserved, prop_code, data);
}
/***********************************************************************************************************************
  Si2177_L1_GetProperty function
  Use:        property get function
              Used to call L1_GET_PROPERTY with the property Id provided.
  Parameter: *api     the Si2177 context
  Parameter: prop     the property Id
  Parameter: *data    a buffer to store the property bytes into
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
unsigned char Si2177_L1_GetProperty         (L1_Si2177_Context *api, unsigned int prop_code, int *data) {
    unsigned char  reserved          = 0;
    unsigned char res;
    res = Si2177_L1_GET_PROPERTY (api, reserved, prop_code);
    *data = api->rsp->get_property.data;
    return res;
}

/***********************************************************************************************************************
  Si2177_L1_SetProperty2 function
  Use:        Sets the property given the property code.
  Parameter: *api     the Si2177 context
  Parameter: prop     the property Id

  Returns:    NO_Si2177_ERROR if successful.
 ***********************************************************************************************************************/
unsigned char Si2177_L1_SetProperty2        (L1_Si2177_Context *api, unsigned int prop_code) {
    int data, res;
#ifdef    Si2177_GET_PROPERTY_STRING
    char msg[1000];
#endif /* Si2177_GET_PROPERTY_STRING */
    res = Si2177_PackProperty(api->prop, prop_code, &data);
    if (res != NO_Si2177_ERROR) {
      SiTRACE("\nSi2177_L1_SetProperty2: %s 0x%04x!\n\n", Si2177_L1_API_ERROR_TEXT(res), prop_code);
      return res;
    }
#ifdef    Si2177_GET_PROPERTY_STRING
    Si2177_L1_PropertyText(api->prop, prop_code, (char*)" ", msg);
    SiTRACE("%s\n",msg);
#endif /* Si2177_GET_PROPERTY_STRING */
    return Si2177_L1_SetProperty (api, prop_code & 0xffff, data);
  }
/***********************************************************************************************************************
  Si2177_L1_GetProperty2 function
  Use:        property get function
              Used to call L1_GET_PROPERTY with the property Id provided.
  Parameter: *api     the Si2177 context
  Parameter: prop     the property Id

  Returns:    NO_Si2177_ERROR if successful.
 ***********************************************************************************************************************/
unsigned char Si2177_L1_GetProperty2        (L1_Si2177_Context *api, unsigned int prop_code) {
  int data, res;
  res = Si2177_L1_GetProperty(api, prop_code & 0xffff, &data);
  if (res != NO_Si2177_ERROR) {
    SiTRACE("Si2177_L1_GetProperty2: %s 0x%04x\n", Si2177_L1_API_ERROR_TEXT(res), prop_code);
    SiERROR(Si2177_L1_API_ERROR_TEXT(res));
    return res;
  }
  return Si2177_UnpackProperty(api->prop, prop_code, data);
}
/*****************************************************************************************
 NAME: Si2177_downloadATVProperties
  DESCRIPTION: Setup Si2177 ATV properties configuration
  This function will download all the ATV configuration properties.
  The function Si2177_storeUserProperties should be called before the first call to this function.
  Parameter:  Pointer to Si2177 Context
  Returns:    I2C transaction error code, NO_Si2177_ERROR if successful
  Programming Guide Reference:    ATV setup flowchart
******************************************************************************************/
int  Si2177_downloadATVProperties         (L1_Si2177_Context *api) {
  SiTRACE("Si2177_downloadATVProperties\n");
#ifdef    Si2177_ATV_AFC_RANGE_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_AFC_RANGE_PROP_CODE               ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_AFC_RANGE_PROP */
#ifdef    Si2177_ATV_AF_OUT_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_AF_OUT_PROP_CODE                  ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_AF_OUT_PROP */
#ifdef    Si2177_ATV_AGC_SPEED_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_AGC_SPEED_PROP_CODE               ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_AGC_SPEED_PROP */
#ifdef    Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP_CODE      ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP */
#ifdef    Si2177_ATV_ARTIFICIAL_SNOW_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_ARTIFICIAL_SNOW_PROP_CODE         ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_ARTIFICIAL_SNOW_PROP */
#ifdef    Si2177_ATV_AUDIO_MODE_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_AUDIO_MODE_PROP_CODE              ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_AUDIO_MODE_PROP */
#ifdef    Si2177_ATV_CONFIG_IF_PORT_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_CONFIG_IF_PORT_PROP_CODE          ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_CONFIG_IF_PORT_PROP */
#ifdef    Si2177_ATV_CVBS_OUT_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_CVBS_OUT_PROP_CODE                ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_CVBS_OUT_PROP */
#ifdef    Si2177_ATV_CVBS_OUT_FINE_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_CVBS_OUT_FINE_PROP_CODE           ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_CVBS_OUT_FINE_PROP */
#ifdef    Si2177_ATV_HSYNC_OUT_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_HSYNC_OUT_PROP_CODE               ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_HSYNC_OUT_PROP */
#ifdef    Si2177_ATV_IEN_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_IEN_PROP_CODE                     ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_IEN_PROP */
#ifdef    Si2177_ATV_INT_SENSE_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_INT_SENSE_PROP_CODE               ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_INT_SENSE_PROP */
#ifdef    Si2177_ATV_PGA_TARGET_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_PGA_TARGET_PROP_CODE              ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_PGA_TARGET_PROP */
#ifdef    Si2177_ATV_RF_TOP_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_RF_TOP_PROP_CODE                  ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_RF_TOP_PROP */
#ifdef    Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP_CODE      ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP */
#ifdef    Si2177_ATV_RSQ_SNR_THRESHOLD_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_RSQ_SNR_THRESHOLD_PROP_CODE       ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_RSQ_SNR_THRESHOLD_PROP */
#ifdef    Si2177_ATV_SIF_OUT_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_SIF_OUT_PROP_CODE                 ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_SIF_OUT_PROP */
#ifdef    Si2177_ATV_SOUND_AGC_LIMIT_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_SOUND_AGC_LIMIT_PROP_CODE         ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_SOUND_AGC_LIMIT_PROP */
#ifdef    Si2177_ATV_SOUND_AGC_SPEED_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_SOUND_AGC_SPEED_PROP_CODE         ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_SOUND_AGC_SPEED_PROP */
#ifdef    Si2177_ATV_VIDEO_EQUALIZER_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_VIDEO_EQUALIZER_PROP_CODE         ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_VIDEO_EQUALIZER_PROP */
#ifdef    Si2177_ATV_VIDEO_MODE_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_VIDEO_MODE_PROP_CODE              ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_VIDEO_MODE_PROP */
#ifdef    Si2177_ATV_VSNR_CAP_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_ATV_VSNR_CAP_PROP_CODE                ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_ATV_VSNR_CAP_PROP */
return NO_Si2177_ERROR;
}
/*****************************************************************************************
 NAME: Si2177_downloadCOMMONProperties
  DESCRIPTION: Setup Si2177 COMMON properties configuration
  This function will download all the COMMON configuration properties.
  The function Si2177_storeUserProperties should be called before the first call to this function.
  Parameter:  Pointer to Si2177 Context
  Returns:    I2C transaction error code, NO_Si2177_ERROR if successful
  Programming Guide Reference:    COMMON setup flowchart
******************************************************************************************/
int  Si2177_downloadCOMMONProperties      (L1_Si2177_Context *api) {
  SiTRACE("Si2177_downloadCOMMONProperties\n");
#ifdef    Si2177_CRYSTAL_TRIM_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_CRYSTAL_TRIM_PROP_CODE                ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_CRYSTAL_TRIM_PROP */
#ifdef    Si2177_MASTER_IEN_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_MASTER_IEN_PROP_CODE                  ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_MASTER_IEN_PROP */
#ifdef    Si2177_XOUT_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_XOUT_PROP_CODE                        ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_XOUT_PROP */
return NO_Si2177_ERROR;
}
/*****************************************************************************************
 NAME: Si2177_downloadDTVProperties
  DESCRIPTION: Setup Si2177 DTV properties configuration
  This function will download all the DTV configuration properties.
  The function Si2177_storeUserProperties should be called before the first call to this function.
  Parameter:  Pointer to Si2177 Context
  Returns:    I2C transaction error code, NO_Si2177_ERROR if successful
  Programming Guide Reference:    DTV setup flowchart
******************************************************************************************/
int  Si2177_downloadDTVProperties         (L1_Si2177_Context *api) {
  SiTRACE("Si2177_downloadDTVProperties\n");
#ifdef    Si2177_DTV_AGC_AUTO_FREEZE_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_AGC_AUTO_FREEZE_PROP_CODE         ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_AGC_AUTO_FREEZE_PROP */
#ifdef    Si2177_DTV_AGC_FREEZE_INPUT_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_AGC_FREEZE_INPUT_PROP_CODE        ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_AGC_FREEZE_INPUT_PROP */
#ifdef    Si2177_DTV_AGC_SPEED_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_AGC_SPEED_PROP_CODE               ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_AGC_SPEED_PROP */
#ifdef    Si2177_DTV_CONFIG_IF_PORT_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_CONFIG_IF_PORT_PROP_CODE          ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_CONFIG_IF_PORT_PROP */
#ifdef    Si2177_DTV_EXT_AGC_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_EXT_AGC_PROP_CODE                 ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_EXT_AGC_PROP */
#ifdef    Si2177_DTV_IEN_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_IEN_PROP_CODE                     ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_IEN_PROP */
#ifdef    Si2177_DTV_IF_AGC_SPEED_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_IF_AGC_SPEED_PROP_CODE            ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_IF_AGC_SPEED_PROP */
#ifdef    Si2177_DTV_INITIAL_AGC_SPEED_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_INITIAL_AGC_SPEED_PROP_CODE       ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_INITIAL_AGC_SPEED_PROP */
#ifdef    Si2177_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
#ifdef    Si2177_DTV_INTERNAL_ZIF_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_INTERNAL_ZIF_PROP_CODE            ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_INTERNAL_ZIF_PROP */
#ifdef    Si2177_DTV_INT_SENSE_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_INT_SENSE_PROP_CODE               ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_INT_SENSE_PROP */
#ifdef    Si2177_DTV_LIF_FREQ_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_LIF_FREQ_PROP_CODE                ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_LIF_FREQ_PROP */
#ifdef    Si2177_DTV_LIF_OUT_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_LIF_OUT_PROP_CODE                 ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_LIF_OUT_PROP */
#ifdef    Si2177_DTV_MODE_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_MODE_PROP_CODE                    ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_MODE_PROP */
#ifdef    Si2177_DTV_PGA_LIMITS_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_PGA_LIMITS_PROP_CODE              ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_PGA_LIMITS_PROP */
#ifdef    Si2177_DTV_PGA_TARGET_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_PGA_TARGET_PROP_CODE              ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_PGA_TARGET_PROP */
#ifdef    Si2177_DTV_RF_AGC_SPEED_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_RF_AGC_SPEED_PROP_CODE            ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_RF_AGC_SPEED_PROP */
#ifdef    Si2177_DTV_RF_TOP_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_RF_TOP_PROP_CODE                  ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_RF_TOP_PROP */
#ifdef    Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP_CODE      ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP */
#ifdef    Si2177_DTV_WB_AGC_SPEED_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_WB_AGC_SPEED_PROP_CODE            ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_WB_AGC_SPEED_PROP */
#ifdef    Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP_CODE     ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP */
return NO_Si2177_ERROR;
}
/*****************************************************************************************
 NAME: Si2177_downloadTUNERProperties
  DESCRIPTION: Setup Si2177 TUNER properties configuration
  This function will download all the TUNER configuration properties.
  The function Si2177_storeUserProperties should be called before the first call to this function.
  Parameter:  Pointer to Si2177 Context
  Returns:    I2C transaction error code, NO_Si2177_ERROR if successful
  Programming Guide Reference:    TUNER setup flowchart
******************************************************************************************/
int  Si2177_downloadTUNERProperties       (L1_Si2177_Context *api) {
  SiTRACE("Si2177_downloadTUNERProperties\n");
#ifdef    Si2177_TUNER_BLOCKED_VCO_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_TUNER_BLOCKED_VCO_PROP_CODE           ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_TUNER_BLOCKED_VCO_PROP */
#ifdef    Si2177_TUNER_IEN_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_TUNER_IEN_PROP_CODE                   ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_TUNER_IEN_PROP */
#ifdef    Si2177_TUNER_INT_SENSE_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_TUNER_INT_SENSE_PROP_CODE             ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_TUNER_INT_SENSE_PROP */
#ifdef    Si2177_TUNER_LO_INJECTION_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_TUNER_LO_INJECTION_PROP_CODE          ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_TUNER_LO_INJECTION_PROP */
#ifdef    Si2177_TUNER_RETURN_LOSS_PROP
  if (Si2177_L1_SetProperty2(api, Si2177_TUNER_RETURN_LOSS_PROP_CODE           ) != NO_Si2177_ERROR) {return ERROR_Si2177_SENDING_COMMAND;}
#endif /* Si2177_TUNER_RETURN_LOSS_PROP */
return NO_Si2177_ERROR;
}
int  Si2177_downloadAllProperties         (L1_Si2177_Context *api) {
  Si2177_downloadATVProperties         (api);
  Si2177_downloadCOMMONProperties      (api);
  Si2177_downloadDTVProperties         (api);
  Si2177_downloadTUNERProperties       (api);
  return 0;
}
/***********************************************************************************************************************
  Si2177_PackProperty function
  Use:        This function will pack all the members of a property into an integer for the SetProperty function.

  Parameter: *prop          the Si2177 property context
  Parameter:  prop_code     the property Id
  Parameter:  *data         an int to store the property data

  Returns:    NO_Si2177_ERROR if the property exists.
 ***********************************************************************************************************************/
unsigned char Si2177_PackProperty            (Si2177_PropObj   *prop, unsigned int prop_code, int *data) {
    switch (prop_code) {
    #ifdef        Si2177_ATV_AFC_RANGE_PROP
     case         Si2177_ATV_AFC_RANGE_PROP_CODE:
      *data = (prop->atv_afc_range.range_khz & Si2177_ATV_AFC_RANGE_PROP_RANGE_KHZ_MASK) << Si2177_ATV_AFC_RANGE_PROP_RANGE_KHZ_LSB ;
     break;
    #endif /*     Si2177_ATV_AFC_RANGE_PROP */
    #ifdef        Si2177_ATV_AF_OUT_PROP
     case         Si2177_ATV_AF_OUT_PROP_CODE:
      *data = (prop->atv_af_out.volume    & Si2177_ATV_AF_OUT_PROP_VOLUME_MASK   ) << Si2177_ATV_AF_OUT_PROP_VOLUME_LSB  |
              (prop->atv_af_out.soft_mute & Si2177_ATV_AF_OUT_PROP_SOFT_MUTE_MASK) << Si2177_ATV_AF_OUT_PROP_SOFT_MUTE_LSB ;
     break;
    #endif /*     Si2177_ATV_AF_OUT_PROP */
    #ifdef        Si2177_ATV_AGC_SPEED_PROP
     case         Si2177_ATV_AGC_SPEED_PROP_CODE:
      *data = (prop->atv_agc_speed.if_agc_speed & Si2177_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK) << Si2177_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB ;
     break;
    #endif /*     Si2177_ATV_AGC_SPEED_PROP */
    #ifdef        Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP
     case         Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP_CODE:
      *data = (prop->atv_agc_speed_low_rssi.if_agc_speed & Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_MASK) << Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_LSB  |
              (prop->atv_agc_speed_low_rssi.thld         & Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD_MASK        ) << Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD_LSB ;
     break;
    #endif /*     Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP */
    #ifdef        Si2177_ATV_ARTIFICIAL_SNOW_PROP
     case         Si2177_ATV_ARTIFICIAL_SNOW_PROP_CODE:
      *data = (prop->atv_artificial_snow.gain   & Si2177_ATV_ARTIFICIAL_SNOW_PROP_GAIN_MASK  ) << Si2177_ATV_ARTIFICIAL_SNOW_PROP_GAIN_LSB  |
              (prop->atv_artificial_snow.sound  & Si2177_ATV_ARTIFICIAL_SNOW_PROP_SOUND_MASK ) << Si2177_ATV_ARTIFICIAL_SNOW_PROP_SOUND_LSB  |
              (prop->atv_artificial_snow.period & Si2177_ATV_ARTIFICIAL_SNOW_PROP_PERIOD_MASK) << Si2177_ATV_ARTIFICIAL_SNOW_PROP_PERIOD_LSB  |
              (prop->atv_artificial_snow.offset & Si2177_ATV_ARTIFICIAL_SNOW_PROP_OFFSET_MASK) << Si2177_ATV_ARTIFICIAL_SNOW_PROP_OFFSET_LSB ;
     break;
    #endif /*     Si2177_ATV_ARTIFICIAL_SNOW_PROP */
    #ifdef        Si2177_ATV_AUDIO_MODE_PROP
     case         Si2177_ATV_AUDIO_MODE_PROP_CODE:
      *data = (prop->atv_audio_mode.audio_sys  & Si2177_ATV_AUDIO_MODE_PROP_AUDIO_SYS_MASK ) << Si2177_ATV_AUDIO_MODE_PROP_AUDIO_SYS_LSB  |
              (prop->atv_audio_mode.demod_mode & Si2177_ATV_AUDIO_MODE_PROP_DEMOD_MODE_MASK) << Si2177_ATV_AUDIO_MODE_PROP_DEMOD_MODE_LSB  |
              (prop->atv_audio_mode.chan_bw    & Si2177_ATV_AUDIO_MODE_PROP_CHAN_BW_MASK   ) << Si2177_ATV_AUDIO_MODE_PROP_CHAN_BW_LSB ;
     break;
    #endif /*     Si2177_ATV_AUDIO_MODE_PROP */
    #ifdef        Si2177_ATV_CONFIG_IF_PORT_PROP
     case         Si2177_ATV_CONFIG_IF_PORT_PROP_CODE:
      *data = (prop->atv_config_if_port.atv_out_type & Si2177_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_MASK) << Si2177_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_LSB ;
     break;
    #endif /*     Si2177_ATV_CONFIG_IF_PORT_PROP */
    #ifdef        Si2177_ATV_CVBS_OUT_PROP
     case         Si2177_ATV_CVBS_OUT_PROP_CODE:
      *data = (prop->atv_cvbs_out.offset & Si2177_ATV_CVBS_OUT_PROP_OFFSET_MASK) << Si2177_ATV_CVBS_OUT_PROP_OFFSET_LSB  |
              (prop->atv_cvbs_out.amp    & Si2177_ATV_CVBS_OUT_PROP_AMP_MASK   ) << Si2177_ATV_CVBS_OUT_PROP_AMP_LSB ;
     break;
    #endif /*     Si2177_ATV_CVBS_OUT_PROP */
    #ifdef        Si2177_ATV_CVBS_OUT_FINE_PROP
     case         Si2177_ATV_CVBS_OUT_FINE_PROP_CODE:
      *data = (prop->atv_cvbs_out_fine.offset & Si2177_ATV_CVBS_OUT_FINE_PROP_OFFSET_MASK) << Si2177_ATV_CVBS_OUT_FINE_PROP_OFFSET_LSB  |
              (prop->atv_cvbs_out_fine.amp    & Si2177_ATV_CVBS_OUT_FINE_PROP_AMP_MASK   ) << Si2177_ATV_CVBS_OUT_FINE_PROP_AMP_LSB ;
     break;
    #endif /*     Si2177_ATV_CVBS_OUT_FINE_PROP */
    #ifdef        Si2177_ATV_HSYNC_OUT_PROP
     case         Si2177_ATV_HSYNC_OUT_PROP_CODE:
      *data = (prop->atv_hsync_out.gpio_sel & Si2177_ATV_HSYNC_OUT_PROP_GPIO_SEL_MASK) << Si2177_ATV_HSYNC_OUT_PROP_GPIO_SEL_LSB  |
              (prop->atv_hsync_out.width    & Si2177_ATV_HSYNC_OUT_PROP_WIDTH_MASK   ) << Si2177_ATV_HSYNC_OUT_PROP_WIDTH_LSB  |
              (prop->atv_hsync_out.offset   & Si2177_ATV_HSYNC_OUT_PROP_OFFSET_MASK  ) << Si2177_ATV_HSYNC_OUT_PROP_OFFSET_LSB ;
     break;
    #endif /*     Si2177_ATV_HSYNC_OUT_PROP */
    #ifdef        Si2177_ATV_IEN_PROP
     case         Si2177_ATV_IEN_PROP_CODE:
      *data = (prop->atv_ien.chlien  & Si2177_ATV_IEN_PROP_CHLIEN_MASK ) << Si2177_ATV_IEN_PROP_CHLIEN_LSB  |
              (prop->atv_ien.pclien  & Si2177_ATV_IEN_PROP_PCLIEN_MASK ) << Si2177_ATV_IEN_PROP_PCLIEN_LSB  |
              (prop->atv_ien.dlien   & Si2177_ATV_IEN_PROP_DLIEN_MASK  ) << Si2177_ATV_IEN_PROP_DLIEN_LSB  |
              (prop->atv_ien.snrlien & Si2177_ATV_IEN_PROP_SNRLIEN_MASK) << Si2177_ATV_IEN_PROP_SNRLIEN_LSB  |
              (prop->atv_ien.snrhien & Si2177_ATV_IEN_PROP_SNRHIEN_MASK) << Si2177_ATV_IEN_PROP_SNRHIEN_LSB ;
     break;
    #endif /*     Si2177_ATV_IEN_PROP */
    #ifdef        Si2177_ATV_INT_SENSE_PROP
     case         Si2177_ATV_INT_SENSE_PROP_CODE:
      *data = (prop->atv_int_sense.chlnegen  & Si2177_ATV_INT_SENSE_PROP_CHLNEGEN_MASK ) << Si2177_ATV_INT_SENSE_PROP_CHLNEGEN_LSB  |
              (prop->atv_int_sense.pclnegen  & Si2177_ATV_INT_SENSE_PROP_PCLNEGEN_MASK ) << Si2177_ATV_INT_SENSE_PROP_PCLNEGEN_LSB  |
              (prop->atv_int_sense.dlnegen   & Si2177_ATV_INT_SENSE_PROP_DLNEGEN_MASK  ) << Si2177_ATV_INT_SENSE_PROP_DLNEGEN_LSB  |
              (prop->atv_int_sense.snrlnegen & Si2177_ATV_INT_SENSE_PROP_SNRLNEGEN_MASK) << Si2177_ATV_INT_SENSE_PROP_SNRLNEGEN_LSB  |
              (prop->atv_int_sense.snrhnegen & Si2177_ATV_INT_SENSE_PROP_SNRHNEGEN_MASK) << Si2177_ATV_INT_SENSE_PROP_SNRHNEGEN_LSB  |
              (prop->atv_int_sense.chlposen  & Si2177_ATV_INT_SENSE_PROP_CHLPOSEN_MASK ) << Si2177_ATV_INT_SENSE_PROP_CHLPOSEN_LSB  |
              (prop->atv_int_sense.pclposen  & Si2177_ATV_INT_SENSE_PROP_PCLPOSEN_MASK ) << Si2177_ATV_INT_SENSE_PROP_PCLPOSEN_LSB  |
              (prop->atv_int_sense.dlposen   & Si2177_ATV_INT_SENSE_PROP_DLPOSEN_MASK  ) << Si2177_ATV_INT_SENSE_PROP_DLPOSEN_LSB  |
              (prop->atv_int_sense.snrlposen & Si2177_ATV_INT_SENSE_PROP_SNRLPOSEN_MASK) << Si2177_ATV_INT_SENSE_PROP_SNRLPOSEN_LSB  |
              (prop->atv_int_sense.snrhposen & Si2177_ATV_INT_SENSE_PROP_SNRHPOSEN_MASK) << Si2177_ATV_INT_SENSE_PROP_SNRHPOSEN_LSB ;
     break;
    #endif /*     Si2177_ATV_INT_SENSE_PROP */
    #ifdef        Si2177_ATV_PGA_TARGET_PROP
     case         Si2177_ATV_PGA_TARGET_PROP_CODE:
      *data = (prop->atv_pga_target.pga_target      & Si2177_ATV_PGA_TARGET_PROP_PGA_TARGET_MASK     ) << Si2177_ATV_PGA_TARGET_PROP_PGA_TARGET_LSB  |
              (prop->atv_pga_target.override_enable & Si2177_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_MASK) << Si2177_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_LSB ;
     break;
    #endif /*     Si2177_ATV_PGA_TARGET_PROP */
    #ifdef        Si2177_ATV_RF_TOP_PROP
     case         Si2177_ATV_RF_TOP_PROP_CODE:
      *data = (prop->atv_rf_top.atv_rf_top & Si2177_ATV_RF_TOP_PROP_ATV_RF_TOP_MASK) << Si2177_ATV_RF_TOP_PROP_ATV_RF_TOP_LSB ;
     break;
    #endif /*     Si2177_ATV_RF_TOP_PROP */
    #ifdef        Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP_CODE:
      *data = (prop->atv_rsq_rssi_threshold.lo & Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK) << Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB  |
              (prop->atv_rsq_rssi_threshold.hi & Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK) << Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB ;
     break;
    #endif /*     Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2177_ATV_RSQ_SNR_THRESHOLD_PROP
     case         Si2177_ATV_RSQ_SNR_THRESHOLD_PROP_CODE:
      *data = (prop->atv_rsq_snr_threshold.lo & Si2177_ATV_RSQ_SNR_THRESHOLD_PROP_LO_MASK) << Si2177_ATV_RSQ_SNR_THRESHOLD_PROP_LO_LSB  |
              (prop->atv_rsq_snr_threshold.hi & Si2177_ATV_RSQ_SNR_THRESHOLD_PROP_HI_MASK) << Si2177_ATV_RSQ_SNR_THRESHOLD_PROP_HI_LSB ;
     break;
    #endif /*     Si2177_ATV_RSQ_SNR_THRESHOLD_PROP */
    #ifdef        Si2177_ATV_SIF_OUT_PROP
     case         Si2177_ATV_SIF_OUT_PROP_CODE:
      *data = (prop->atv_sif_out.offset & Si2177_ATV_SIF_OUT_PROP_OFFSET_MASK) << Si2177_ATV_SIF_OUT_PROP_OFFSET_LSB  |
              (prop->atv_sif_out.amp    & Si2177_ATV_SIF_OUT_PROP_AMP_MASK   ) << Si2177_ATV_SIF_OUT_PROP_AMP_LSB ;
     break;
    #endif /*     Si2177_ATV_SIF_OUT_PROP */
    #ifdef        Si2177_ATV_SOUND_AGC_LIMIT_PROP
     case         Si2177_ATV_SOUND_AGC_LIMIT_PROP_CODE:
      *data = (prop->atv_sound_agc_limit.max_gain & Si2177_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_MASK) << Si2177_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_LSB  |
              (prop->atv_sound_agc_limit.min_gain & Si2177_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_MASK) << Si2177_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_LSB ;
     break;
    #endif /*     Si2177_ATV_SOUND_AGC_LIMIT_PROP */
    #ifdef        Si2177_ATV_SOUND_AGC_SPEED_PROP
     case         Si2177_ATV_SOUND_AGC_SPEED_PROP_CODE:
      *data = (prop->atv_sound_agc_speed.system_l      & Si2177_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_MASK     ) << Si2177_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_LSB  |
              (prop->atv_sound_agc_speed.other_systems & Si2177_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_MASK) << Si2177_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_LSB ;
     break;
    #endif /*     Si2177_ATV_SOUND_AGC_SPEED_PROP */
    #ifdef        Si2177_ATV_VIDEO_EQUALIZER_PROP
     case         Si2177_ATV_VIDEO_EQUALIZER_PROP_CODE:
      *data = (prop->atv_video_equalizer.slope & Si2177_ATV_VIDEO_EQUALIZER_PROP_SLOPE_MASK) << Si2177_ATV_VIDEO_EQUALIZER_PROP_SLOPE_LSB ;
     break;
    #endif /*     Si2177_ATV_VIDEO_EQUALIZER_PROP */
    #ifdef        Si2177_ATV_VIDEO_MODE_PROP
     case         Si2177_ATV_VIDEO_MODE_PROP_CODE:
      *data = (prop->atv_video_mode.video_sys     & Si2177_ATV_VIDEO_MODE_PROP_VIDEO_SYS_MASK    ) << Si2177_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LSB  |
              (prop->atv_video_mode.color         & Si2177_ATV_VIDEO_MODE_PROP_COLOR_MASK        ) << Si2177_ATV_VIDEO_MODE_PROP_COLOR_LSB  |
              (prop->atv_video_mode.invert_signal & Si2177_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_MASK) << Si2177_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_LSB ;
     break;
    #endif /*     Si2177_ATV_VIDEO_MODE_PROP */
    #ifdef        Si2177_ATV_VSNR_CAP_PROP
     case         Si2177_ATV_VSNR_CAP_PROP_CODE:
      *data = (prop->atv_vsnr_cap.atv_vsnr_cap & Si2177_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_MASK) << Si2177_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_LSB ;
     break;
    #endif /*     Si2177_ATV_VSNR_CAP_PROP */
    #ifdef        Si2177_CRYSTAL_TRIM_PROP
     case         Si2177_CRYSTAL_TRIM_PROP_CODE:
      *data = (prop->crystal_trim.xo_cap & Si2177_CRYSTAL_TRIM_PROP_XO_CAP_MASK) << Si2177_CRYSTAL_TRIM_PROP_XO_CAP_LSB ;
     break;
    #endif /*     Si2177_CRYSTAL_TRIM_PROP */
    #ifdef        Si2177_DTV_AGC_AUTO_FREEZE_PROP
     case         Si2177_DTV_AGC_AUTO_FREEZE_PROP_CODE:
      *data = (prop->dtv_agc_auto_freeze.thld    & Si2177_DTV_AGC_AUTO_FREEZE_PROP_THLD_MASK   ) << Si2177_DTV_AGC_AUTO_FREEZE_PROP_THLD_LSB  |
              (prop->dtv_agc_auto_freeze.timeout & Si2177_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT_MASK) << Si2177_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT_LSB ;
     break;
    #endif /*     Si2177_DTV_AGC_AUTO_FREEZE_PROP */
    #ifdef        Si2177_DTV_AGC_FREEZE_INPUT_PROP
     case         Si2177_DTV_AGC_FREEZE_INPUT_PROP_CODE:
      *data = (prop->dtv_agc_freeze_input.level & Si2177_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_MASK) << Si2177_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LSB  |
              (prop->dtv_agc_freeze_input.pin   & Si2177_DTV_AGC_FREEZE_INPUT_PROP_PIN_MASK  ) << Si2177_DTV_AGC_FREEZE_INPUT_PROP_PIN_LSB ;
     break;
    #endif /*     Si2177_DTV_AGC_FREEZE_INPUT_PROP */
    #ifdef        Si2177_DTV_AGC_SPEED_PROP
     case         Si2177_DTV_AGC_SPEED_PROP_CODE:
      *data = (prop->dtv_agc_speed.if_agc_speed & Si2177_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK) << Si2177_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB  |
              (prop->dtv_agc_speed.agc_decim    & Si2177_DTV_AGC_SPEED_PROP_AGC_DECIM_MASK   ) << Si2177_DTV_AGC_SPEED_PROP_AGC_DECIM_LSB ;
     break;
    #endif /*     Si2177_DTV_AGC_SPEED_PROP */
    #ifdef        Si2177_DTV_CONFIG_IF_PORT_PROP
     case         Si2177_DTV_CONFIG_IF_PORT_PROP_CODE:
      *data = (prop->dtv_config_if_port.dtv_out_type   & Si2177_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_MASK  ) << Si2177_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LSB  |
              (prop->dtv_config_if_port.dtv_agc_source & Si2177_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_MASK) << Si2177_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_LSB ;
     break;
    #endif /*     Si2177_DTV_CONFIG_IF_PORT_PROP */
    #ifdef        Si2177_DTV_EXT_AGC_PROP
     case         Si2177_DTV_EXT_AGC_PROP_CODE:
      *data = (prop->dtv_ext_agc.min_10mv & Si2177_DTV_EXT_AGC_PROP_MIN_10MV_MASK) << Si2177_DTV_EXT_AGC_PROP_MIN_10MV_LSB  |
              (prop->dtv_ext_agc.max_10mv & Si2177_DTV_EXT_AGC_PROP_MAX_10MV_MASK) << Si2177_DTV_EXT_AGC_PROP_MAX_10MV_LSB ;
     break;
    #endif /*     Si2177_DTV_EXT_AGC_PROP */
    #ifdef        Si2177_DTV_IEN_PROP
     case         Si2177_DTV_IEN_PROP_CODE:
      *data = (prop->dtv_ien.chlien & Si2177_DTV_IEN_PROP_CHLIEN_MASK) << Si2177_DTV_IEN_PROP_CHLIEN_LSB ;
     break;
    #endif /*     Si2177_DTV_IEN_PROP */
    #ifdef        Si2177_DTV_IF_AGC_SPEED_PROP
     case         Si2177_DTV_IF_AGC_SPEED_PROP_CODE:
      *data = (prop->dtv_if_agc_speed.attack & Si2177_DTV_IF_AGC_SPEED_PROP_ATTACK_MASK) << Si2177_DTV_IF_AGC_SPEED_PROP_ATTACK_LSB  |
              (prop->dtv_if_agc_speed.decay  & Si2177_DTV_IF_AGC_SPEED_PROP_DECAY_MASK ) << Si2177_DTV_IF_AGC_SPEED_PROP_DECAY_LSB ;
     break;
    #endif /*     Si2177_DTV_IF_AGC_SPEED_PROP */
    #ifdef        Si2177_DTV_INITIAL_AGC_SPEED_PROP
     case         Si2177_DTV_INITIAL_AGC_SPEED_PROP_CODE:
      *data = (prop->dtv_initial_agc_speed.if_agc_speed & Si2177_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_MASK) << Si2177_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_LSB  |
              (prop->dtv_initial_agc_speed.agc_decim    & Si2177_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_MASK   ) << Si2177_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_LSB ;
     break;
    #endif /*     Si2177_DTV_INITIAL_AGC_SPEED_PROP */
    #ifdef        Si2177_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
     case         Si2177_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE:
      *data = (prop->dtv_initial_agc_speed_period.period & Si2177_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_MASK) << Si2177_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_LSB ;
     break;
    #endif /*     Si2177_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
    #ifdef        Si2177_DTV_INTERNAL_ZIF_PROP
     case         Si2177_DTV_INTERNAL_ZIF_PROP_CODE:
      *data = (prop->dtv_internal_zif.atsc   & Si2177_DTV_INTERNAL_ZIF_PROP_ATSC_MASK  ) << Si2177_DTV_INTERNAL_ZIF_PROP_ATSC_LSB  |
              (prop->dtv_internal_zif.qam_us & Si2177_DTV_INTERNAL_ZIF_PROP_QAM_US_MASK) << Si2177_DTV_INTERNAL_ZIF_PROP_QAM_US_LSB  |
              (prop->dtv_internal_zif.dvbt   & Si2177_DTV_INTERNAL_ZIF_PROP_DVBT_MASK  ) << Si2177_DTV_INTERNAL_ZIF_PROP_DVBT_LSB  |
              (prop->dtv_internal_zif.dvbc   & Si2177_DTV_INTERNAL_ZIF_PROP_DVBC_MASK  ) << Si2177_DTV_INTERNAL_ZIF_PROP_DVBC_LSB  |
              (prop->dtv_internal_zif.isdbt  & Si2177_DTV_INTERNAL_ZIF_PROP_ISDBT_MASK ) << Si2177_DTV_INTERNAL_ZIF_PROP_ISDBT_LSB  |
              (prop->dtv_internal_zif.isdbc  & Si2177_DTV_INTERNAL_ZIF_PROP_ISDBC_MASK ) << Si2177_DTV_INTERNAL_ZIF_PROP_ISDBC_LSB  |
              (prop->dtv_internal_zif.dtmb   & Si2177_DTV_INTERNAL_ZIF_PROP_DTMB_MASK  ) << Si2177_DTV_INTERNAL_ZIF_PROP_DTMB_LSB ;
     break;
    #endif /*     Si2177_DTV_INTERNAL_ZIF_PROP */
    #ifdef        Si2177_DTV_INT_SENSE_PROP
     case         Si2177_DTV_INT_SENSE_PROP_CODE:
      *data = (prop->dtv_int_sense.chlnegen & Si2177_DTV_INT_SENSE_PROP_CHLNEGEN_MASK) << Si2177_DTV_INT_SENSE_PROP_CHLNEGEN_LSB  |
              (prop->dtv_int_sense.chlposen & Si2177_DTV_INT_SENSE_PROP_CHLPOSEN_MASK) << Si2177_DTV_INT_SENSE_PROP_CHLPOSEN_LSB ;
     break;
    #endif /*     Si2177_DTV_INT_SENSE_PROP */
    #ifdef        Si2177_DTV_LIF_FREQ_PROP
     case         Si2177_DTV_LIF_FREQ_PROP_CODE:
      *data = (prop->dtv_lif_freq.offset & Si2177_DTV_LIF_FREQ_PROP_OFFSET_MASK) << Si2177_DTV_LIF_FREQ_PROP_OFFSET_LSB ;
     break;
    #endif /*     Si2177_DTV_LIF_FREQ_PROP */
    #ifdef        Si2177_DTV_LIF_OUT_PROP
     case         Si2177_DTV_LIF_OUT_PROP_CODE:
      *data = (prop->dtv_lif_out.offset & Si2177_DTV_LIF_OUT_PROP_OFFSET_MASK) << Si2177_DTV_LIF_OUT_PROP_OFFSET_LSB  |
              (prop->dtv_lif_out.amp    & Si2177_DTV_LIF_OUT_PROP_AMP_MASK   ) << Si2177_DTV_LIF_OUT_PROP_AMP_LSB ;
     break;
    #endif /*     Si2177_DTV_LIF_OUT_PROP */
    #ifdef        Si2177_DTV_MODE_PROP
     case         Si2177_DTV_MODE_PROP_CODE:
      *data = (prop->dtv_mode.bw              & Si2177_DTV_MODE_PROP_BW_MASK             ) << Si2177_DTV_MODE_PROP_BW_LSB  |
              (prop->dtv_mode.modulation      & Si2177_DTV_MODE_PROP_MODULATION_MASK     ) << Si2177_DTV_MODE_PROP_MODULATION_LSB  |
              (prop->dtv_mode.invert_spectrum & Si2177_DTV_MODE_PROP_INVERT_SPECTRUM_MASK) << Si2177_DTV_MODE_PROP_INVERT_SPECTRUM_LSB ;
     break;
    #endif /*     Si2177_DTV_MODE_PROP */
    #ifdef        Si2177_DTV_PGA_LIMITS_PROP
     case         Si2177_DTV_PGA_LIMITS_PROP_CODE:
      *data = (prop->dtv_pga_limits.min & Si2177_DTV_PGA_LIMITS_PROP_MIN_MASK) << Si2177_DTV_PGA_LIMITS_PROP_MIN_LSB  |
              (prop->dtv_pga_limits.max & Si2177_DTV_PGA_LIMITS_PROP_MAX_MASK) << Si2177_DTV_PGA_LIMITS_PROP_MAX_LSB ;
     break;
    #endif /*     Si2177_DTV_PGA_LIMITS_PROP */
    #ifdef        Si2177_DTV_PGA_TARGET_PROP
     case         Si2177_DTV_PGA_TARGET_PROP_CODE:
      *data = (prop->dtv_pga_target.pga_target      & Si2177_DTV_PGA_TARGET_PROP_PGA_TARGET_MASK     ) << Si2177_DTV_PGA_TARGET_PROP_PGA_TARGET_LSB  |
              (prop->dtv_pga_target.override_enable & Si2177_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_MASK) << Si2177_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_LSB ;
     break;
    #endif /*     Si2177_DTV_PGA_TARGET_PROP */
    #ifdef        Si2177_DTV_RF_AGC_SPEED_PROP
     case         Si2177_DTV_RF_AGC_SPEED_PROP_CODE:
      *data = (prop->dtv_rf_agc_speed.attack & Si2177_DTV_RF_AGC_SPEED_PROP_ATTACK_MASK) << Si2177_DTV_RF_AGC_SPEED_PROP_ATTACK_LSB  |
              (prop->dtv_rf_agc_speed.decay  & Si2177_DTV_RF_AGC_SPEED_PROP_DECAY_MASK ) << Si2177_DTV_RF_AGC_SPEED_PROP_DECAY_LSB ;
     break;
    #endif /*     Si2177_DTV_RF_AGC_SPEED_PROP */
    #ifdef        Si2177_DTV_RF_TOP_PROP
     case         Si2177_DTV_RF_TOP_PROP_CODE:
      *data = (prop->dtv_rf_top.dtv_rf_top & Si2177_DTV_RF_TOP_PROP_DTV_RF_TOP_MASK) << Si2177_DTV_RF_TOP_PROP_DTV_RF_TOP_LSB ;
     break;
    #endif /*     Si2177_DTV_RF_TOP_PROP */
    #ifdef        Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP_CODE:
      *data = (prop->dtv_rsq_rssi_threshold.lo & Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK) << Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB  |
              (prop->dtv_rsq_rssi_threshold.hi & Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK) << Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB ;
     break;
    #endif /*     Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2177_DTV_WB_AGC_SPEED_PROP
     case         Si2177_DTV_WB_AGC_SPEED_PROP_CODE:
      *data = (prop->dtv_wb_agc_speed.attack & Si2177_DTV_WB_AGC_SPEED_PROP_ATTACK_MASK) << Si2177_DTV_WB_AGC_SPEED_PROP_ATTACK_LSB  |
              (prop->dtv_wb_agc_speed.decay  & Si2177_DTV_WB_AGC_SPEED_PROP_DECAY_MASK ) << Si2177_DTV_WB_AGC_SPEED_PROP_DECAY_LSB ;
     break;
    #endif /*     Si2177_DTV_WB_AGC_SPEED_PROP */
    #ifdef        Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP
     case         Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP_CODE:
      *data = (prop->dtv_zif_dc_canceller_bw.bandwidth & Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_MASK) << Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_LSB ;
     break;
    #endif /*     Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP */
    #ifdef        Si2177_MASTER_IEN_PROP
     case         Si2177_MASTER_IEN_PROP_CODE:
      *data = (prop->master_ien.tunien & Si2177_MASTER_IEN_PROP_TUNIEN_MASK) << Si2177_MASTER_IEN_PROP_TUNIEN_LSB  |
              (prop->master_ien.atvien & Si2177_MASTER_IEN_PROP_ATVIEN_MASK) << Si2177_MASTER_IEN_PROP_ATVIEN_LSB  |
              (prop->master_ien.dtvien & Si2177_MASTER_IEN_PROP_DTVIEN_MASK) << Si2177_MASTER_IEN_PROP_DTVIEN_LSB  |
              (prop->master_ien.errien & Si2177_MASTER_IEN_PROP_ERRIEN_MASK) << Si2177_MASTER_IEN_PROP_ERRIEN_LSB  |
              (prop->master_ien.ctsien & Si2177_MASTER_IEN_PROP_CTSIEN_MASK) << Si2177_MASTER_IEN_PROP_CTSIEN_LSB ;
     break;
    #endif /*     Si2177_MASTER_IEN_PROP */
    #ifdef        Si2177_TUNER_BLOCKED_VCO_PROP
     case         Si2177_TUNER_BLOCKED_VCO_PROP_CODE:
      *data = (prop->tuner_blocked_vco.vco_code & Si2177_TUNER_BLOCKED_VCO_PROP_VCO_CODE_MASK) << Si2177_TUNER_BLOCKED_VCO_PROP_VCO_CODE_LSB ;
     break;
    #endif /*     Si2177_TUNER_BLOCKED_VCO_PROP */
    #ifdef        Si2177_TUNER_IEN_PROP
     case         Si2177_TUNER_IEN_PROP_CODE:
      *data = (prop->tuner_ien.tcien    & Si2177_TUNER_IEN_PROP_TCIEN_MASK   ) << Si2177_TUNER_IEN_PROP_TCIEN_LSB  |
              (prop->tuner_ien.rssilien & Si2177_TUNER_IEN_PROP_RSSILIEN_MASK) << Si2177_TUNER_IEN_PROP_RSSILIEN_LSB  |
              (prop->tuner_ien.rssihien & Si2177_TUNER_IEN_PROP_RSSIHIEN_MASK) << Si2177_TUNER_IEN_PROP_RSSIHIEN_LSB ;
     break;
    #endif /*     Si2177_TUNER_IEN_PROP */
    #ifdef        Si2177_TUNER_INT_SENSE_PROP
     case         Si2177_TUNER_INT_SENSE_PROP_CODE:
      *data = (prop->tuner_int_sense.tcnegen    & Si2177_TUNER_INT_SENSE_PROP_TCNEGEN_MASK   ) << Si2177_TUNER_INT_SENSE_PROP_TCNEGEN_LSB  |
              (prop->tuner_int_sense.rssilnegen & Si2177_TUNER_INT_SENSE_PROP_RSSILNEGEN_MASK) << Si2177_TUNER_INT_SENSE_PROP_RSSILNEGEN_LSB  |
              (prop->tuner_int_sense.rssihnegen & Si2177_TUNER_INT_SENSE_PROP_RSSIHNEGEN_MASK) << Si2177_TUNER_INT_SENSE_PROP_RSSIHNEGEN_LSB  |
              (prop->tuner_int_sense.tcposen    & Si2177_TUNER_INT_SENSE_PROP_TCPOSEN_MASK   ) << Si2177_TUNER_INT_SENSE_PROP_TCPOSEN_LSB  |
              (prop->tuner_int_sense.rssilposen & Si2177_TUNER_INT_SENSE_PROP_RSSILPOSEN_MASK) << Si2177_TUNER_INT_SENSE_PROP_RSSILPOSEN_LSB  |
              (prop->tuner_int_sense.rssihposen & Si2177_TUNER_INT_SENSE_PROP_RSSIHPOSEN_MASK) << Si2177_TUNER_INT_SENSE_PROP_RSSIHPOSEN_LSB ;
     break;
    #endif /*     Si2177_TUNER_INT_SENSE_PROP */
    #ifdef        Si2177_TUNER_LO_INJECTION_PROP
     case         Si2177_TUNER_LO_INJECTION_PROP_CODE:
      *data = (prop->tuner_lo_injection.band_1 & Si2177_TUNER_LO_INJECTION_PROP_BAND_1_MASK) << Si2177_TUNER_LO_INJECTION_PROP_BAND_1_LSB  |
              (prop->tuner_lo_injection.band_2 & Si2177_TUNER_LO_INJECTION_PROP_BAND_2_MASK) << Si2177_TUNER_LO_INJECTION_PROP_BAND_2_LSB  |
              (prop->tuner_lo_injection.band_3 & Si2177_TUNER_LO_INJECTION_PROP_BAND_3_MASK) << Si2177_TUNER_LO_INJECTION_PROP_BAND_3_LSB ;
     break;
    #endif /*     Si2177_TUNER_LO_INJECTION_PROP */
    #ifdef        Si2177_TUNER_RETURN_LOSS_PROP
     case         Si2177_TUNER_RETURN_LOSS_PROP_CODE:
      *data = (prop->tuner_return_loss.config & Si2177_TUNER_RETURN_LOSS_PROP_CONFIG_MASK) << Si2177_TUNER_RETURN_LOSS_PROP_CONFIG_LSB  |
              (prop->tuner_return_loss.mode   & Si2177_TUNER_RETURN_LOSS_PROP_MODE_MASK  ) << Si2177_TUNER_RETURN_LOSS_PROP_MODE_LSB ;
     break;
    #endif /*     Si2177_TUNER_RETURN_LOSS_PROP */
    #ifdef        Si2177_XOUT_PROP
     case         Si2177_XOUT_PROP_CODE:
      *data = (prop->xout.amp & Si2177_XOUT_PROP_AMP_MASK) << Si2177_XOUT_PROP_AMP_LSB ;
     break;
    #endif /*     Si2177_XOUT_PROP */
     default : return ERROR_Si2177_UNKNOWN_PROPERTY; break;
    }
    return NO_Si2177_ERROR;
}


/***********************************************************************************************************************
  Si2177_UnpackProperty function
  Use:        This function will unpack all the members of a property from an integer from the GetProperty function.

  Parameter: *prop          the Si2177 property context
  Parameter:  prop_code     the property Id
  Parameter:  data          the property data

  Returns:    NO_Si2177_ERROR if the property exists.
 ***********************************************************************************************************************/
unsigned char Si2177_UnpackProperty          (Si2177_PropObj   *prop, unsigned int prop_code, int  data) {
    switch (prop_code) {
    #ifdef        Si2177_ATV_AFC_RANGE_PROP
     case         Si2177_ATV_AFC_RANGE_PROP_CODE:
               prop->atv_afc_range.range_khz = (data >> Si2177_ATV_AFC_RANGE_PROP_RANGE_KHZ_LSB) & Si2177_ATV_AFC_RANGE_PROP_RANGE_KHZ_MASK;
     break;
    #endif /*     Si2177_ATV_AFC_RANGE_PROP */
    #ifdef        Si2177_ATV_AF_OUT_PROP
     case         Si2177_ATV_AF_OUT_PROP_CODE:
               prop->atv_af_out.volume    = (data >> Si2177_ATV_AF_OUT_PROP_VOLUME_LSB   ) & Si2177_ATV_AF_OUT_PROP_VOLUME_MASK;
               prop->atv_af_out.soft_mute = (data >> Si2177_ATV_AF_OUT_PROP_SOFT_MUTE_LSB) & Si2177_ATV_AF_OUT_PROP_SOFT_MUTE_MASK;
     break;
    #endif /*     Si2177_ATV_AF_OUT_PROP */
    #ifdef        Si2177_ATV_AGC_SPEED_PROP
     case         Si2177_ATV_AGC_SPEED_PROP_CODE:
               prop->atv_agc_speed.if_agc_speed = (data >> Si2177_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB) & Si2177_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK;
     break;
    #endif /*     Si2177_ATV_AGC_SPEED_PROP */
    #ifdef        Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP
     case         Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP_CODE:
               prop->atv_agc_speed_low_rssi.if_agc_speed = (data >> Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_LSB) & Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_MASK;
               prop->atv_agc_speed_low_rssi.thld         = (data >> Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD_LSB        ) & Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD_MASK;
     break;
    #endif /*     Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP */
    #ifdef        Si2177_ATV_ARTIFICIAL_SNOW_PROP
     case         Si2177_ATV_ARTIFICIAL_SNOW_PROP_CODE:
               prop->atv_artificial_snow.gain   = (data >> Si2177_ATV_ARTIFICIAL_SNOW_PROP_GAIN_LSB  ) & Si2177_ATV_ARTIFICIAL_SNOW_PROP_GAIN_MASK;
               prop->atv_artificial_snow.sound  = (data >> Si2177_ATV_ARTIFICIAL_SNOW_PROP_SOUND_LSB ) & Si2177_ATV_ARTIFICIAL_SNOW_PROP_SOUND_MASK;
               prop->atv_artificial_snow.period = (data >> Si2177_ATV_ARTIFICIAL_SNOW_PROP_PERIOD_LSB) & Si2177_ATV_ARTIFICIAL_SNOW_PROP_PERIOD_MASK;
               prop->atv_artificial_snow.offset = (data >> Si2177_ATV_ARTIFICIAL_SNOW_PROP_OFFSET_LSB) & Si2177_ATV_ARTIFICIAL_SNOW_PROP_OFFSET_MASK;
     break;
    #endif /*     Si2177_ATV_ARTIFICIAL_SNOW_PROP */
    #ifdef        Si2177_ATV_AUDIO_MODE_PROP
     case         Si2177_ATV_AUDIO_MODE_PROP_CODE:
               prop->atv_audio_mode.audio_sys  = (data >> Si2177_ATV_AUDIO_MODE_PROP_AUDIO_SYS_LSB ) & Si2177_ATV_AUDIO_MODE_PROP_AUDIO_SYS_MASK;
               prop->atv_audio_mode.demod_mode = (data >> Si2177_ATV_AUDIO_MODE_PROP_DEMOD_MODE_LSB) & Si2177_ATV_AUDIO_MODE_PROP_DEMOD_MODE_MASK;
               prop->atv_audio_mode.chan_bw    = (data >> Si2177_ATV_AUDIO_MODE_PROP_CHAN_BW_LSB   ) & Si2177_ATV_AUDIO_MODE_PROP_CHAN_BW_MASK;
     break;
    #endif /*     Si2177_ATV_AUDIO_MODE_PROP */
    #ifdef        Si2177_ATV_CONFIG_IF_PORT_PROP
     case         Si2177_ATV_CONFIG_IF_PORT_PROP_CODE:
               prop->atv_config_if_port.atv_out_type = (data >> Si2177_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_LSB) & Si2177_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_MASK;
     break;
    #endif /*     Si2177_ATV_CONFIG_IF_PORT_PROP */
    #ifdef        Si2177_ATV_CVBS_OUT_PROP
     case         Si2177_ATV_CVBS_OUT_PROP_CODE:
               prop->atv_cvbs_out.offset = (data >> Si2177_ATV_CVBS_OUT_PROP_OFFSET_LSB) & Si2177_ATV_CVBS_OUT_PROP_OFFSET_MASK;
               prop->atv_cvbs_out.amp    = (data >> Si2177_ATV_CVBS_OUT_PROP_AMP_LSB   ) & Si2177_ATV_CVBS_OUT_PROP_AMP_MASK;
     break;
    #endif /*     Si2177_ATV_CVBS_OUT_PROP */
    #ifdef        Si2177_ATV_CVBS_OUT_FINE_PROP
     case         Si2177_ATV_CVBS_OUT_FINE_PROP_CODE:
               prop->atv_cvbs_out_fine.offset = (data >> Si2177_ATV_CVBS_OUT_FINE_PROP_OFFSET_LSB) & Si2177_ATV_CVBS_OUT_FINE_PROP_OFFSET_MASK;
               prop->atv_cvbs_out_fine.amp    = (data >> Si2177_ATV_CVBS_OUT_FINE_PROP_AMP_LSB   ) & Si2177_ATV_CVBS_OUT_FINE_PROP_AMP_MASK;
     break;
    #endif /*     Si2177_ATV_CVBS_OUT_FINE_PROP */
    #ifdef        Si2177_ATV_HSYNC_OUT_PROP
     case         Si2177_ATV_HSYNC_OUT_PROP_CODE:
               prop->atv_hsync_out.gpio_sel = (data >> Si2177_ATV_HSYNC_OUT_PROP_GPIO_SEL_LSB) & Si2177_ATV_HSYNC_OUT_PROP_GPIO_SEL_MASK;
               prop->atv_hsync_out.width    = (data >> Si2177_ATV_HSYNC_OUT_PROP_WIDTH_LSB   ) & Si2177_ATV_HSYNC_OUT_PROP_WIDTH_MASK;
               prop->atv_hsync_out.offset   = (data >> Si2177_ATV_HSYNC_OUT_PROP_OFFSET_LSB  ) & Si2177_ATV_HSYNC_OUT_PROP_OFFSET_MASK;
     break;
    #endif /*     Si2177_ATV_HSYNC_OUT_PROP */
    #ifdef        Si2177_ATV_IEN_PROP
     case         Si2177_ATV_IEN_PROP_CODE:
               prop->atv_ien.chlien  = (data >> Si2177_ATV_IEN_PROP_CHLIEN_LSB ) & Si2177_ATV_IEN_PROP_CHLIEN_MASK;
               prop->atv_ien.pclien  = (data >> Si2177_ATV_IEN_PROP_PCLIEN_LSB ) & Si2177_ATV_IEN_PROP_PCLIEN_MASK;
               prop->atv_ien.dlien   = (data >> Si2177_ATV_IEN_PROP_DLIEN_LSB  ) & Si2177_ATV_IEN_PROP_DLIEN_MASK;
               prop->atv_ien.snrlien = (data >> Si2177_ATV_IEN_PROP_SNRLIEN_LSB) & Si2177_ATV_IEN_PROP_SNRLIEN_MASK;
               prop->atv_ien.snrhien = (data >> Si2177_ATV_IEN_PROP_SNRHIEN_LSB) & Si2177_ATV_IEN_PROP_SNRHIEN_MASK;
     break;
    #endif /*     Si2177_ATV_IEN_PROP */
    #ifdef        Si2177_ATV_INT_SENSE_PROP
     case         Si2177_ATV_INT_SENSE_PROP_CODE:
               prop->atv_int_sense.chlnegen  = (data >> Si2177_ATV_INT_SENSE_PROP_CHLNEGEN_LSB ) & Si2177_ATV_INT_SENSE_PROP_CHLNEGEN_MASK;
               prop->atv_int_sense.pclnegen  = (data >> Si2177_ATV_INT_SENSE_PROP_PCLNEGEN_LSB ) & Si2177_ATV_INT_SENSE_PROP_PCLNEGEN_MASK;
               prop->atv_int_sense.dlnegen   = (data >> Si2177_ATV_INT_SENSE_PROP_DLNEGEN_LSB  ) & Si2177_ATV_INT_SENSE_PROP_DLNEGEN_MASK;
               prop->atv_int_sense.snrlnegen = (data >> Si2177_ATV_INT_SENSE_PROP_SNRLNEGEN_LSB) & Si2177_ATV_INT_SENSE_PROP_SNRLNEGEN_MASK;
               prop->atv_int_sense.snrhnegen = (data >> Si2177_ATV_INT_SENSE_PROP_SNRHNEGEN_LSB) & Si2177_ATV_INT_SENSE_PROP_SNRHNEGEN_MASK;
               prop->atv_int_sense.chlposen  = (data >> Si2177_ATV_INT_SENSE_PROP_CHLPOSEN_LSB ) & Si2177_ATV_INT_SENSE_PROP_CHLPOSEN_MASK;
               prop->atv_int_sense.pclposen  = (data >> Si2177_ATV_INT_SENSE_PROP_PCLPOSEN_LSB ) & Si2177_ATV_INT_SENSE_PROP_PCLPOSEN_MASK;
               prop->atv_int_sense.dlposen   = (data >> Si2177_ATV_INT_SENSE_PROP_DLPOSEN_LSB  ) & Si2177_ATV_INT_SENSE_PROP_DLPOSEN_MASK;
               prop->atv_int_sense.snrlposen = (data >> Si2177_ATV_INT_SENSE_PROP_SNRLPOSEN_LSB) & Si2177_ATV_INT_SENSE_PROP_SNRLPOSEN_MASK;
               prop->atv_int_sense.snrhposen = (data >> Si2177_ATV_INT_SENSE_PROP_SNRHPOSEN_LSB) & Si2177_ATV_INT_SENSE_PROP_SNRHPOSEN_MASK;
     break;
    #endif /*     Si2177_ATV_INT_SENSE_PROP */
    #ifdef        Si2177_ATV_PGA_TARGET_PROP
     case         Si2177_ATV_PGA_TARGET_PROP_CODE:
               prop->atv_pga_target.pga_target      = (data >> Si2177_ATV_PGA_TARGET_PROP_PGA_TARGET_LSB     ) & Si2177_ATV_PGA_TARGET_PROP_PGA_TARGET_MASK;
               prop->atv_pga_target.override_enable = (data >> Si2177_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_LSB) & Si2177_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_MASK;
     break;
    #endif /*     Si2177_ATV_PGA_TARGET_PROP */
    #ifdef        Si2177_ATV_RF_TOP_PROP
     case         Si2177_ATV_RF_TOP_PROP_CODE:
               prop->atv_rf_top.atv_rf_top = (data >> Si2177_ATV_RF_TOP_PROP_ATV_RF_TOP_LSB) & Si2177_ATV_RF_TOP_PROP_ATV_RF_TOP_MASK;
     break;
    #endif /*     Si2177_ATV_RF_TOP_PROP */
    #ifdef        Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP_CODE:
               prop->atv_rsq_rssi_threshold.lo = (data >> Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB) & Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK;
               prop->atv_rsq_rssi_threshold.hi = (data >> Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB) & Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK;
     break;
    #endif /*     Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2177_ATV_RSQ_SNR_THRESHOLD_PROP
     case         Si2177_ATV_RSQ_SNR_THRESHOLD_PROP_CODE:
               prop->atv_rsq_snr_threshold.lo = (data >> Si2177_ATV_RSQ_SNR_THRESHOLD_PROP_LO_LSB) & Si2177_ATV_RSQ_SNR_THRESHOLD_PROP_LO_MASK;
               prop->atv_rsq_snr_threshold.hi = (data >> Si2177_ATV_RSQ_SNR_THRESHOLD_PROP_HI_LSB) & Si2177_ATV_RSQ_SNR_THRESHOLD_PROP_HI_MASK;
     break;
    #endif /*     Si2177_ATV_RSQ_SNR_THRESHOLD_PROP */
    #ifdef        Si2177_ATV_SIF_OUT_PROP
     case         Si2177_ATV_SIF_OUT_PROP_CODE:
               prop->atv_sif_out.offset = (data >> Si2177_ATV_SIF_OUT_PROP_OFFSET_LSB) & Si2177_ATV_SIF_OUT_PROP_OFFSET_MASK;
               prop->atv_sif_out.amp    = (data >> Si2177_ATV_SIF_OUT_PROP_AMP_LSB   ) & Si2177_ATV_SIF_OUT_PROP_AMP_MASK;
     break;
    #endif /*     Si2177_ATV_SIF_OUT_PROP */
    #ifdef        Si2177_ATV_SOUND_AGC_LIMIT_PROP
     case         Si2177_ATV_SOUND_AGC_LIMIT_PROP_CODE:
               prop->atv_sound_agc_limit.max_gain = (data >> Si2177_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_LSB) & Si2177_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_MASK;
               prop->atv_sound_agc_limit.min_gain = (data >> Si2177_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_LSB) & Si2177_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_MASK;
     break;
    #endif /*     Si2177_ATV_SOUND_AGC_LIMIT_PROP */
    #ifdef        Si2177_ATV_SOUND_AGC_SPEED_PROP
     case         Si2177_ATV_SOUND_AGC_SPEED_PROP_CODE:
               prop->atv_sound_agc_speed.system_l      = (data >> Si2177_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_LSB     ) & Si2177_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_MASK;
               prop->atv_sound_agc_speed.other_systems = (data >> Si2177_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_LSB) & Si2177_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_MASK;
     break;
    #endif /*     Si2177_ATV_SOUND_AGC_SPEED_PROP */
    #ifdef        Si2177_ATV_VIDEO_EQUALIZER_PROP
     case         Si2177_ATV_VIDEO_EQUALIZER_PROP_CODE:
               prop->atv_video_equalizer.slope = (data >> Si2177_ATV_VIDEO_EQUALIZER_PROP_SLOPE_LSB) & Si2177_ATV_VIDEO_EQUALIZER_PROP_SLOPE_MASK;
     break;
    #endif /*     Si2177_ATV_VIDEO_EQUALIZER_PROP */
    #ifdef        Si2177_ATV_VIDEO_MODE_PROP
     case         Si2177_ATV_VIDEO_MODE_PROP_CODE:
               prop->atv_video_mode.video_sys     = (data >> Si2177_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LSB    ) & Si2177_ATV_VIDEO_MODE_PROP_VIDEO_SYS_MASK;
               prop->atv_video_mode.color         = (data >> Si2177_ATV_VIDEO_MODE_PROP_COLOR_LSB        ) & Si2177_ATV_VIDEO_MODE_PROP_COLOR_MASK;
               prop->atv_video_mode.invert_signal = (data >> Si2177_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_LSB) & Si2177_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_MASK;
     break;
    #endif /*     Si2177_ATV_VIDEO_MODE_PROP */
    #ifdef        Si2177_ATV_VSNR_CAP_PROP
     case         Si2177_ATV_VSNR_CAP_PROP_CODE:
               prop->atv_vsnr_cap.atv_vsnr_cap = (data >> Si2177_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_LSB) & Si2177_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_MASK;
     break;
    #endif /*     Si2177_ATV_VSNR_CAP_PROP */
    #ifdef        Si2177_CRYSTAL_TRIM_PROP
     case         Si2177_CRYSTAL_TRIM_PROP_CODE:
               prop->crystal_trim.xo_cap = (data >> Si2177_CRYSTAL_TRIM_PROP_XO_CAP_LSB) & Si2177_CRYSTAL_TRIM_PROP_XO_CAP_MASK;
     break;
    #endif /*     Si2177_CRYSTAL_TRIM_PROP */
    #ifdef        Si2177_DTV_AGC_AUTO_FREEZE_PROP
     case         Si2177_DTV_AGC_AUTO_FREEZE_PROP_CODE:
               prop->dtv_agc_auto_freeze.thld    = (data >> Si2177_DTV_AGC_AUTO_FREEZE_PROP_THLD_LSB   ) & Si2177_DTV_AGC_AUTO_FREEZE_PROP_THLD_MASK;
               prop->dtv_agc_auto_freeze.timeout = (data >> Si2177_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT_LSB) & Si2177_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT_MASK;
     break;
    #endif /*     Si2177_DTV_AGC_AUTO_FREEZE_PROP */
    #ifdef        Si2177_DTV_AGC_FREEZE_INPUT_PROP
     case         Si2177_DTV_AGC_FREEZE_INPUT_PROP_CODE:
               prop->dtv_agc_freeze_input.level = (data >> Si2177_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LSB) & Si2177_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_MASK;
               prop->dtv_agc_freeze_input.pin   = (data >> Si2177_DTV_AGC_FREEZE_INPUT_PROP_PIN_LSB  ) & Si2177_DTV_AGC_FREEZE_INPUT_PROP_PIN_MASK;
     break;
    #endif /*     Si2177_DTV_AGC_FREEZE_INPUT_PROP */
    #ifdef        Si2177_DTV_AGC_SPEED_PROP
     case         Si2177_DTV_AGC_SPEED_PROP_CODE:
               prop->dtv_agc_speed.if_agc_speed = (data >> Si2177_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB) & Si2177_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK;
               prop->dtv_agc_speed.agc_decim    = (data >> Si2177_DTV_AGC_SPEED_PROP_AGC_DECIM_LSB   ) & Si2177_DTV_AGC_SPEED_PROP_AGC_DECIM_MASK;
     break;
    #endif /*     Si2177_DTV_AGC_SPEED_PROP */
    #ifdef        Si2177_DTV_CONFIG_IF_PORT_PROP
     case         Si2177_DTV_CONFIG_IF_PORT_PROP_CODE:
               prop->dtv_config_if_port.dtv_out_type   = (data >> Si2177_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LSB  ) & Si2177_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_MASK;
               prop->dtv_config_if_port.dtv_agc_source = (data >> Si2177_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_LSB) & Si2177_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_MASK;
     break;
    #endif /*     Si2177_DTV_CONFIG_IF_PORT_PROP */
    #ifdef        Si2177_DTV_EXT_AGC_PROP
     case         Si2177_DTV_EXT_AGC_PROP_CODE:
               prop->dtv_ext_agc.min_10mv = (data >> Si2177_DTV_EXT_AGC_PROP_MIN_10MV_LSB) & Si2177_DTV_EXT_AGC_PROP_MIN_10MV_MASK;
               prop->dtv_ext_agc.max_10mv = (data >> Si2177_DTV_EXT_AGC_PROP_MAX_10MV_LSB) & Si2177_DTV_EXT_AGC_PROP_MAX_10MV_MASK;
     break;
    #endif /*     Si2177_DTV_EXT_AGC_PROP */
    #ifdef        Si2177_DTV_IEN_PROP
     case         Si2177_DTV_IEN_PROP_CODE:
               prop->dtv_ien.chlien = (data >> Si2177_DTV_IEN_PROP_CHLIEN_LSB) & Si2177_DTV_IEN_PROP_CHLIEN_MASK;
     break;
    #endif /*     Si2177_DTV_IEN_PROP */
    #ifdef        Si2177_DTV_IF_AGC_SPEED_PROP
     case         Si2177_DTV_IF_AGC_SPEED_PROP_CODE:
               prop->dtv_if_agc_speed.attack = (data >> Si2177_DTV_IF_AGC_SPEED_PROP_ATTACK_LSB) & Si2177_DTV_IF_AGC_SPEED_PROP_ATTACK_MASK;
               prop->dtv_if_agc_speed.decay  = (data >> Si2177_DTV_IF_AGC_SPEED_PROP_DECAY_LSB ) & Si2177_DTV_IF_AGC_SPEED_PROP_DECAY_MASK;
     break;
    #endif /*     Si2177_DTV_IF_AGC_SPEED_PROP */
    #ifdef        Si2177_DTV_INITIAL_AGC_SPEED_PROP
     case         Si2177_DTV_INITIAL_AGC_SPEED_PROP_CODE:
               prop->dtv_initial_agc_speed.if_agc_speed = (data >> Si2177_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_LSB) & Si2177_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_MASK;
               prop->dtv_initial_agc_speed.agc_decim    = (data >> Si2177_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_LSB   ) & Si2177_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_MASK;
     break;
    #endif /*     Si2177_DTV_INITIAL_AGC_SPEED_PROP */
    #ifdef        Si2177_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
     case         Si2177_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE:
               prop->dtv_initial_agc_speed_period.period = (data >> Si2177_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_LSB) & Si2177_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_MASK;
     break;
    #endif /*     Si2177_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
    #ifdef        Si2177_DTV_INTERNAL_ZIF_PROP
     case         Si2177_DTV_INTERNAL_ZIF_PROP_CODE:
               prop->dtv_internal_zif.atsc   = (data >> Si2177_DTV_INTERNAL_ZIF_PROP_ATSC_LSB  ) & Si2177_DTV_INTERNAL_ZIF_PROP_ATSC_MASK;
               prop->dtv_internal_zif.qam_us = (data >> Si2177_DTV_INTERNAL_ZIF_PROP_QAM_US_LSB) & Si2177_DTV_INTERNAL_ZIF_PROP_QAM_US_MASK;
               prop->dtv_internal_zif.dvbt   = (data >> Si2177_DTV_INTERNAL_ZIF_PROP_DVBT_LSB  ) & Si2177_DTV_INTERNAL_ZIF_PROP_DVBT_MASK;
               prop->dtv_internal_zif.dvbc   = (data >> Si2177_DTV_INTERNAL_ZIF_PROP_DVBC_LSB  ) & Si2177_DTV_INTERNAL_ZIF_PROP_DVBC_MASK;
               prop->dtv_internal_zif.isdbt  = (data >> Si2177_DTV_INTERNAL_ZIF_PROP_ISDBT_LSB ) & Si2177_DTV_INTERNAL_ZIF_PROP_ISDBT_MASK;
               prop->dtv_internal_zif.isdbc  = (data >> Si2177_DTV_INTERNAL_ZIF_PROP_ISDBC_LSB ) & Si2177_DTV_INTERNAL_ZIF_PROP_ISDBC_MASK;
               prop->dtv_internal_zif.dtmb   = (data >> Si2177_DTV_INTERNAL_ZIF_PROP_DTMB_LSB  ) & Si2177_DTV_INTERNAL_ZIF_PROP_DTMB_MASK;
     break;
    #endif /*     Si2177_DTV_INTERNAL_ZIF_PROP */
    #ifdef        Si2177_DTV_INT_SENSE_PROP
     case         Si2177_DTV_INT_SENSE_PROP_CODE:
               prop->dtv_int_sense.chlnegen = (data >> Si2177_DTV_INT_SENSE_PROP_CHLNEGEN_LSB) & Si2177_DTV_INT_SENSE_PROP_CHLNEGEN_MASK;
               prop->dtv_int_sense.chlposen = (data >> Si2177_DTV_INT_SENSE_PROP_CHLPOSEN_LSB) & Si2177_DTV_INT_SENSE_PROP_CHLPOSEN_MASK;
     break;
    #endif /*     Si2177_DTV_INT_SENSE_PROP */
    #ifdef        Si2177_DTV_LIF_FREQ_PROP
     case         Si2177_DTV_LIF_FREQ_PROP_CODE:
               prop->dtv_lif_freq.offset = (data >> Si2177_DTV_LIF_FREQ_PROP_OFFSET_LSB) & Si2177_DTV_LIF_FREQ_PROP_OFFSET_MASK;
     break;
    #endif /*     Si2177_DTV_LIF_FREQ_PROP */
    #ifdef        Si2177_DTV_LIF_OUT_PROP
     case         Si2177_DTV_LIF_OUT_PROP_CODE:
               prop->dtv_lif_out.offset = (data >> Si2177_DTV_LIF_OUT_PROP_OFFSET_LSB) & Si2177_DTV_LIF_OUT_PROP_OFFSET_MASK;
               prop->dtv_lif_out.amp    = (data >> Si2177_DTV_LIF_OUT_PROP_AMP_LSB   ) & Si2177_DTV_LIF_OUT_PROP_AMP_MASK;
     break;
    #endif /*     Si2177_DTV_LIF_OUT_PROP */
    #ifdef        Si2177_DTV_MODE_PROP
     case         Si2177_DTV_MODE_PROP_CODE:
               prop->dtv_mode.bw              = (data >> Si2177_DTV_MODE_PROP_BW_LSB             ) & Si2177_DTV_MODE_PROP_BW_MASK;
               prop->dtv_mode.modulation      = (data >> Si2177_DTV_MODE_PROP_MODULATION_LSB     ) & Si2177_DTV_MODE_PROP_MODULATION_MASK;
               prop->dtv_mode.invert_spectrum = (data >> Si2177_DTV_MODE_PROP_INVERT_SPECTRUM_LSB) & Si2177_DTV_MODE_PROP_INVERT_SPECTRUM_MASK;
     break;
    #endif /*     Si2177_DTV_MODE_PROP */
    #ifdef        Si2177_DTV_PGA_LIMITS_PROP
     case         Si2177_DTV_PGA_LIMITS_PROP_CODE:
               prop->dtv_pga_limits.min = (data >> Si2177_DTV_PGA_LIMITS_PROP_MIN_LSB) & Si2177_DTV_PGA_LIMITS_PROP_MIN_MASK;
               prop->dtv_pga_limits.max = (data >> Si2177_DTV_PGA_LIMITS_PROP_MAX_LSB) & Si2177_DTV_PGA_LIMITS_PROP_MAX_MASK;
     break;
    #endif /*     Si2177_DTV_PGA_LIMITS_PROP */
    #ifdef        Si2177_DTV_PGA_TARGET_PROP
     case         Si2177_DTV_PGA_TARGET_PROP_CODE:
               prop->dtv_pga_target.pga_target      = (data >> Si2177_DTV_PGA_TARGET_PROP_PGA_TARGET_LSB     ) & Si2177_DTV_PGA_TARGET_PROP_PGA_TARGET_MASK;
               prop->dtv_pga_target.override_enable = (data >> Si2177_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_LSB) & Si2177_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_MASK;
     break;
    #endif /*     Si2177_DTV_PGA_TARGET_PROP */
    #ifdef        Si2177_DTV_RF_AGC_SPEED_PROP
     case         Si2177_DTV_RF_AGC_SPEED_PROP_CODE:
               prop->dtv_rf_agc_speed.attack = (data >> Si2177_DTV_RF_AGC_SPEED_PROP_ATTACK_LSB) & Si2177_DTV_RF_AGC_SPEED_PROP_ATTACK_MASK;
               prop->dtv_rf_agc_speed.decay  = (data >> Si2177_DTV_RF_AGC_SPEED_PROP_DECAY_LSB ) & Si2177_DTV_RF_AGC_SPEED_PROP_DECAY_MASK;
     break;
    #endif /*     Si2177_DTV_RF_AGC_SPEED_PROP */
    #ifdef        Si2177_DTV_RF_TOP_PROP
     case         Si2177_DTV_RF_TOP_PROP_CODE:
               prop->dtv_rf_top.dtv_rf_top = (data >> Si2177_DTV_RF_TOP_PROP_DTV_RF_TOP_LSB) & Si2177_DTV_RF_TOP_PROP_DTV_RF_TOP_MASK;
     break;
    #endif /*     Si2177_DTV_RF_TOP_PROP */
    #ifdef        Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP_CODE:
               prop->dtv_rsq_rssi_threshold.lo = (data >> Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB) & Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK;
               prop->dtv_rsq_rssi_threshold.hi = (data >> Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB) & Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK;
     break;
    #endif /*     Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2177_DTV_WB_AGC_SPEED_PROP
     case         Si2177_DTV_WB_AGC_SPEED_PROP_CODE:
               prop->dtv_wb_agc_speed.attack = (data >> Si2177_DTV_WB_AGC_SPEED_PROP_ATTACK_LSB) & Si2177_DTV_WB_AGC_SPEED_PROP_ATTACK_MASK;
               prop->dtv_wb_agc_speed.decay  = (data >> Si2177_DTV_WB_AGC_SPEED_PROP_DECAY_LSB ) & Si2177_DTV_WB_AGC_SPEED_PROP_DECAY_MASK;
     break;
    #endif /*     Si2177_DTV_WB_AGC_SPEED_PROP */
    #ifdef        Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP
     case         Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP_CODE:
               prop->dtv_zif_dc_canceller_bw.bandwidth = (data >> Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_LSB) & Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_MASK;
     break;
    #endif /*     Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP */
    #ifdef        Si2177_MASTER_IEN_PROP
     case         Si2177_MASTER_IEN_PROP_CODE:
               prop->master_ien.tunien = (data >> Si2177_MASTER_IEN_PROP_TUNIEN_LSB) & Si2177_MASTER_IEN_PROP_TUNIEN_MASK;
               prop->master_ien.atvien = (data >> Si2177_MASTER_IEN_PROP_ATVIEN_LSB) & Si2177_MASTER_IEN_PROP_ATVIEN_MASK;
               prop->master_ien.dtvien = (data >> Si2177_MASTER_IEN_PROP_DTVIEN_LSB) & Si2177_MASTER_IEN_PROP_DTVIEN_MASK;
               prop->master_ien.errien = (data >> Si2177_MASTER_IEN_PROP_ERRIEN_LSB) & Si2177_MASTER_IEN_PROP_ERRIEN_MASK;
               prop->master_ien.ctsien = (data >> Si2177_MASTER_IEN_PROP_CTSIEN_LSB) & Si2177_MASTER_IEN_PROP_CTSIEN_MASK;
     break;
    #endif /*     Si2177_MASTER_IEN_PROP */
    #ifdef        Si2177_TUNER_BLOCKED_VCO_PROP
     case         Si2177_TUNER_BLOCKED_VCO_PROP_CODE:
               prop->tuner_blocked_vco.vco_code = (data >> Si2177_TUNER_BLOCKED_VCO_PROP_VCO_CODE_LSB) & Si2177_TUNER_BLOCKED_VCO_PROP_VCO_CODE_MASK;
     break;
    #endif /*     Si2177_TUNER_BLOCKED_VCO_PROP */
    #ifdef        Si2177_TUNER_IEN_PROP
     case         Si2177_TUNER_IEN_PROP_CODE:
               prop->tuner_ien.tcien    = (data >> Si2177_TUNER_IEN_PROP_TCIEN_LSB   ) & Si2177_TUNER_IEN_PROP_TCIEN_MASK;
               prop->tuner_ien.rssilien = (data >> Si2177_TUNER_IEN_PROP_RSSILIEN_LSB) & Si2177_TUNER_IEN_PROP_RSSILIEN_MASK;
               prop->tuner_ien.rssihien = (data >> Si2177_TUNER_IEN_PROP_RSSIHIEN_LSB) & Si2177_TUNER_IEN_PROP_RSSIHIEN_MASK;
     break;
    #endif /*     Si2177_TUNER_IEN_PROP */
    #ifdef        Si2177_TUNER_INT_SENSE_PROP
     case         Si2177_TUNER_INT_SENSE_PROP_CODE:
               prop->tuner_int_sense.tcnegen    = (data >> Si2177_TUNER_INT_SENSE_PROP_TCNEGEN_LSB   ) & Si2177_TUNER_INT_SENSE_PROP_TCNEGEN_MASK;
               prop->tuner_int_sense.rssilnegen = (data >> Si2177_TUNER_INT_SENSE_PROP_RSSILNEGEN_LSB) & Si2177_TUNER_INT_SENSE_PROP_RSSILNEGEN_MASK;
               prop->tuner_int_sense.rssihnegen = (data >> Si2177_TUNER_INT_SENSE_PROP_RSSIHNEGEN_LSB) & Si2177_TUNER_INT_SENSE_PROP_RSSIHNEGEN_MASK;
               prop->tuner_int_sense.tcposen    = (data >> Si2177_TUNER_INT_SENSE_PROP_TCPOSEN_LSB   ) & Si2177_TUNER_INT_SENSE_PROP_TCPOSEN_MASK;
               prop->tuner_int_sense.rssilposen = (data >> Si2177_TUNER_INT_SENSE_PROP_RSSILPOSEN_LSB) & Si2177_TUNER_INT_SENSE_PROP_RSSILPOSEN_MASK;
               prop->tuner_int_sense.rssihposen = (data >> Si2177_TUNER_INT_SENSE_PROP_RSSIHPOSEN_LSB) & Si2177_TUNER_INT_SENSE_PROP_RSSIHPOSEN_MASK;
     break;
    #endif /*     Si2177_TUNER_INT_SENSE_PROP */
    #ifdef        Si2177_TUNER_LO_INJECTION_PROP
     case         Si2177_TUNER_LO_INJECTION_PROP_CODE:
               prop->tuner_lo_injection.band_1 = (data >> Si2177_TUNER_LO_INJECTION_PROP_BAND_1_LSB) & Si2177_TUNER_LO_INJECTION_PROP_BAND_1_MASK;
               prop->tuner_lo_injection.band_2 = (data >> Si2177_TUNER_LO_INJECTION_PROP_BAND_2_LSB) & Si2177_TUNER_LO_INJECTION_PROP_BAND_2_MASK;
               prop->tuner_lo_injection.band_3 = (data >> Si2177_TUNER_LO_INJECTION_PROP_BAND_3_LSB) & Si2177_TUNER_LO_INJECTION_PROP_BAND_3_MASK;
     break;
    #endif /*     Si2177_TUNER_LO_INJECTION_PROP */
    #ifdef        Si2177_TUNER_RETURN_LOSS_PROP
     case         Si2177_TUNER_RETURN_LOSS_PROP_CODE:
               prop->tuner_return_loss.config = (data >> Si2177_TUNER_RETURN_LOSS_PROP_CONFIG_LSB) & Si2177_TUNER_RETURN_LOSS_PROP_CONFIG_MASK;
               prop->tuner_return_loss.mode   = (data >> Si2177_TUNER_RETURN_LOSS_PROP_MODE_LSB  ) & Si2177_TUNER_RETURN_LOSS_PROP_MODE_MASK;
     break;
    #endif /*     Si2177_TUNER_RETURN_LOSS_PROP */
    #ifdef        Si2177_XOUT_PROP
     case         Si2177_XOUT_PROP_CODE:
               prop->xout.amp = (data >> Si2177_XOUT_PROP_AMP_LSB) & Si2177_XOUT_PROP_AMP_MASK;
     break;
    #endif /*     Si2177_XOUT_PROP */
     default : return ERROR_Si2177_UNKNOWN_PROPERTY; break;
    }
    return NO_Si2177_ERROR;
}
/***********************************************************************************************************************
  Si2177_storePropertiesDefaults function
  Use:        property defaults function
              Used to fill the propShadow structure with startup values.
  Parameter: *prop     the Si2177_PropObject structure

 |---------------------------------------------------------------------------------------------------------------------|
 | Do NOT change this code unless you really know what you're doing!                                                   |
 | It should reflect the part internal property settings after firmware download                                       |
 |---------------------------------------------------------------------------------------------------------------------|

 Returns:    void
 ***********************************************************************************************************************/
void          Si2177_storePropertiesDefaults (Si2177_PropObj   *prop) {
#ifdef    Si2177_ATV_AFC_RANGE_PROP
  prop->atv_afc_range.range_khz              =  1000; /* (default  1000) */
#endif /* Si2177_ATV_AFC_RANGE_PROP */

#ifdef    Si2177_ATV_AF_OUT_PROP
  prop->atv_af_out.volume                    =     0; /* (default     0) */
  prop->atv_af_out.soft_mute                 = Si2177_ATV_AF_OUT_PROP_SOFT_MUTE_DISABLE ; /* (default 'DISABLE') */
#endif /* Si2177_ATV_AF_OUT_PROP */

#ifdef    Si2177_ATV_AGC_SPEED_PROP
  prop->atv_agc_speed.if_agc_speed           = Si2177_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO ; /* (default 'AUTO') */
#endif /* Si2177_ATV_AGC_SPEED_PROP */

#ifdef    Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP
  prop->atv_agc_speed_low_rssi.if_agc_speed  = Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_158 ; /* (default '158') */
  prop->atv_agc_speed_low_rssi.thld          =  -128; /* (default  -128) */
#endif /* Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP */

#ifdef    Si2177_ATV_ARTIFICIAL_SNOW_PROP
  prop->atv_artificial_snow.gain             = Si2177_ATV_ARTIFICIAL_SNOW_PROP_GAIN_AUTO   ; /* (default 'AUTO') */
  prop->atv_artificial_snow.sound            = Si2177_ATV_ARTIFICIAL_SNOW_PROP_SOUND_MUTE  ; /* (default 'MUTE') */
  prop->atv_artificial_snow.period           = Si2177_ATV_ARTIFICIAL_SNOW_PROP_PERIOD_LONG ; /* (default 'LONG') */
  prop->atv_artificial_snow.offset           =     0; /* (default     0) */
#endif /* Si2177_ATV_ARTIFICIAL_SNOW_PROP */

#ifdef    Si2177_ATV_AUDIO_MODE_PROP
  prop->atv_audio_mode.audio_sys             = Si2177_ATV_AUDIO_MODE_PROP_AUDIO_SYS_DEFAULT  ; /* (default 'DEFAULT') */
  prop->atv_audio_mode.demod_mode            = Si2177_ATV_AUDIO_MODE_PROP_DEMOD_MODE_SIF     ; /* (default 'SIF') */
  prop->atv_audio_mode.chan_bw               = Si2177_ATV_AUDIO_MODE_PROP_CHAN_BW_DEFAULT    ; /* (default 'DEFAULT') */
#endif /* Si2177_ATV_AUDIO_MODE_PROP */

#ifdef    Si2177_ATV_CONFIG_IF_PORT_PROP
  prop->atv_config_if_port.atv_out_type      = Si2177_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_CVBS_IF2B_SOUND_IF2A ; /* (default 'CVBS_IF2B_SOUND_IF2A') */
#endif /* Si2177_ATV_CONFIG_IF_PORT_PROP */

#ifdef    Si2177_ATV_CVBS_OUT_PROP
  prop->atv_cvbs_out.offset                  =    25; /* (default    25) */
  prop->atv_cvbs_out.amp                     =   200; /* (default   200) */
#endif /* Si2177_ATV_CVBS_OUT_PROP */

#ifdef    Si2177_ATV_CVBS_OUT_FINE_PROP
  prop->atv_cvbs_out_fine.offset             =     0; /* (default     0) */
  prop->atv_cvbs_out_fine.amp                =   100; /* (default   100) */
#endif /* Si2177_ATV_CVBS_OUT_FINE_PROP */

#ifdef    Si2177_ATV_HSYNC_OUT_PROP
  prop->atv_hsync_out.gpio_sel               = Si2177_ATV_HSYNC_OUT_PROP_GPIO_SEL_NONE ; /* (default 'NONE') */
  prop->atv_hsync_out.width                  =    42; /* (default    42) */
  prop->atv_hsync_out.offset                 =     0; /* (default     0) */
#endif /* Si2177_ATV_HSYNC_OUT_PROP */

#ifdef    Si2177_ATV_IEN_PROP
  prop->atv_ien.chlien                       = Si2177_ATV_IEN_PROP_CHLIEN_ENABLE   ; /* (default 'ENABLE') */
  prop->atv_ien.pclien                       = Si2177_ATV_IEN_PROP_PCLIEN_DISABLE  ; /* (default 'DISABLE') */
  prop->atv_ien.dlien                        = Si2177_ATV_IEN_PROP_DLIEN_DISABLE   ; /* (default 'DISABLE') */
  prop->atv_ien.snrlien                      = Si2177_ATV_IEN_PROP_SNRLIEN_DISABLE ; /* (default 'DISABLE') */
  prop->atv_ien.snrhien                      = Si2177_ATV_IEN_PROP_SNRHIEN_DISABLE ; /* (default 'DISABLE') */
#endif /* Si2177_ATV_IEN_PROP */

#ifdef    Si2177_ATV_INT_SENSE_PROP
  prop->atv_int_sense.chlnegen               = Si2177_ATV_INT_SENSE_PROP_CHLNEGEN_DISABLE  ; /* (default 'DISABLE') */
  prop->atv_int_sense.pclnegen               = Si2177_ATV_INT_SENSE_PROP_PCLNEGEN_DISABLE  ; /* (default 'DISABLE') */
  prop->atv_int_sense.dlnegen                = Si2177_ATV_INT_SENSE_PROP_DLNEGEN_DISABLE   ; /* (default 'DISABLE') */
  prop->atv_int_sense.snrlnegen              = Si2177_ATV_INT_SENSE_PROP_SNRLNEGEN_DISABLE ; /* (default 'DISABLE') */
  prop->atv_int_sense.snrhnegen              = Si2177_ATV_INT_SENSE_PROP_SNRHNEGEN_DISABLE ; /* (default 'DISABLE') */
  prop->atv_int_sense.chlposen               = Si2177_ATV_INT_SENSE_PROP_CHLPOSEN_ENABLE   ; /* (default 'ENABLE') */
  prop->atv_int_sense.pclposen               = Si2177_ATV_INT_SENSE_PROP_PCLPOSEN_ENABLE   ; /* (default 'ENABLE') */
  prop->atv_int_sense.dlposen                = Si2177_ATV_INT_SENSE_PROP_DLPOSEN_ENABLE    ; /* (default 'ENABLE') */
  prop->atv_int_sense.snrlposen              = Si2177_ATV_INT_SENSE_PROP_SNRLPOSEN_ENABLE  ; /* (default 'ENABLE') */
  prop->atv_int_sense.snrhposen              = Si2177_ATV_INT_SENSE_PROP_SNRHPOSEN_ENABLE  ; /* (default 'ENABLE') */
#endif /* Si2177_ATV_INT_SENSE_PROP */

#ifdef    Si2177_ATV_PGA_TARGET_PROP
  prop->atv_pga_target.pga_target            =     0; /* (default     0) */
  prop->atv_pga_target.override_enable       = Si2177_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_DISABLE ; /* (default 'DISABLE') */
#endif /* Si2177_ATV_PGA_TARGET_PROP */

#ifdef    Si2177_ATV_RF_TOP_PROP
  prop->atv_rf_top.atv_rf_top                = Si2177_ATV_RF_TOP_PROP_ATV_RF_TOP_AUTO ; /* (default 'AUTO') */
#endif /* Si2177_ATV_RF_TOP_PROP */

#ifdef    Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP
  prop->atv_rsq_rssi_threshold.lo            =   -70; /* (default   -70) */
  prop->atv_rsq_rssi_threshold.hi            =     0; /* (default     0) */
#endif /* Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP */

#ifdef    Si2177_ATV_RSQ_SNR_THRESHOLD_PROP
  prop->atv_rsq_snr_threshold.lo             =    25; /* (default    25) */
  prop->atv_rsq_snr_threshold.hi             =    45; /* (default    45) */
#endif /* Si2177_ATV_RSQ_SNR_THRESHOLD_PROP */

#ifdef    Si2177_ATV_SIF_OUT_PROP
  prop->atv_sif_out.offset                   =   135; /* (default   135) */
  prop->atv_sif_out.amp                      =    60; /* (default    60) */
#endif /* Si2177_ATV_SIF_OUT_PROP */

#ifdef    Si2177_ATV_SOUND_AGC_LIMIT_PROP
  prop->atv_sound_agc_limit.max_gain         =    84; /* (default    84) */
  prop->atv_sound_agc_limit.min_gain         =   -84; /* (default   -84) */
#endif /* Si2177_ATV_SOUND_AGC_LIMIT_PROP */

#ifdef    Si2177_ATV_SOUND_AGC_SPEED_PROP
  prop->atv_sound_agc_speed.system_l         =     5; /* (default     5) */
  prop->atv_sound_agc_speed.other_systems    =     4; /* (default     4) */
#endif /* Si2177_ATV_SOUND_AGC_SPEED_PROP */

#ifdef    Si2177_ATV_VIDEO_EQUALIZER_PROP
  prop->atv_video_equalizer.slope            =     0; /* (default     0) */
#endif /* Si2177_ATV_VIDEO_EQUALIZER_PROP */

#ifdef    Si2177_ATV_VIDEO_MODE_PROP
  prop->atv_video_mode.video_sys             = Si2177_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B            ; /* (default 'B') */
  prop->atv_video_mode.color                 = Si2177_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC         ; /* (default 'PAL_NTSC') */
  prop->atv_video_mode.invert_signal         = Si2177_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_NORMAL   ; /* (default 'NORMAL') */
#endif /* Si2177_ATV_VIDEO_MODE_PROP */

#ifdef    Si2177_ATV_VSNR_CAP_PROP
  prop->atv_vsnr_cap.atv_vsnr_cap            =     0; /* (default     0) */
#endif /* Si2177_ATV_VSNR_CAP_PROP */

#ifdef    Si2177_CRYSTAL_TRIM_PROP
  prop->crystal_trim.xo_cap                  = Si2177_CRYSTAL_TRIM_PROP_XO_CAP_6P7PF ; /* (default '6p7pF') */
#endif /* Si2177_CRYSTAL_TRIM_PROP */

#ifdef    Si2177_MASTER_IEN_PROP
  prop->master_ien.tunien                    = Si2177_MASTER_IEN_PROP_TUNIEN_OFF ; /* (default 'OFF') */
  prop->master_ien.atvien                    = Si2177_MASTER_IEN_PROP_ATVIEN_OFF ; /* (default 'OFF') */
  prop->master_ien.dtvien                    = Si2177_MASTER_IEN_PROP_DTVIEN_OFF ; /* (default 'OFF') */
  prop->master_ien.errien                    = Si2177_MASTER_IEN_PROP_ERRIEN_OFF ; /* (default 'OFF') */
  prop->master_ien.ctsien                    = Si2177_MASTER_IEN_PROP_CTSIEN_OFF ; /* (default 'OFF') */
#endif /* Si2177_MASTER_IEN_PROP */

#ifdef    Si2177_XOUT_PROP
  prop->xout.amp                             = Si2177_XOUT_PROP_AMP_HIGH ; /* (default 'HIGH') */
#endif /* Si2177_XOUT_PROP */

#ifdef    Si2177_DTV_AGC_AUTO_FREEZE_PROP
  prop->dtv_agc_auto_freeze.thld             =   255; /* (default   255) */
  prop->dtv_agc_auto_freeze.timeout          =     1; /* (default     1) */
#endif /* Si2177_DTV_AGC_AUTO_FREEZE_PROP */

#ifdef    Si2177_DTV_AGC_FREEZE_INPUT_PROP
  prop->dtv_agc_freeze_input.level           = Si2177_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LOW  ; /* (default 'LOW') */
  prop->dtv_agc_freeze_input.pin             = Si2177_DTV_AGC_FREEZE_INPUT_PROP_PIN_NONE   ; /* (default 'NONE') */
#endif /* Si2177_DTV_AGC_FREEZE_INPUT_PROP */

#ifdef    Si2177_DTV_AGC_SPEED_PROP
  prop->dtv_agc_speed.if_agc_speed           = Si2177_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO ; /* (default 'AUTO') */
  prop->dtv_agc_speed.agc_decim              = Si2177_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF     ; /* (default 'OFF') */
#endif /* Si2177_DTV_AGC_SPEED_PROP */

#ifdef    Si2177_DTV_CONFIG_IF_PORT_PROP
  prop->dtv_config_if_port.dtv_out_type      = Si2177_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_IF1    ; /* (default 'LIF_IF1') */
  prop->dtv_config_if_port.dtv_agc_source    = Si2177_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_INTERNAL ; /* (default 'INTERNAL') */
#endif /* Si2177_DTV_CONFIG_IF_PORT_PROP */

#ifdef    Si2177_DTV_EXT_AGC_PROP
  prop->dtv_ext_agc.min_10mv                 =    50; /* (default    50) */
  prop->dtv_ext_agc.max_10mv                 =   200; /* (default   200) */
#endif /* Si2177_DTV_EXT_AGC_PROP */

#ifdef    Si2177_DTV_IEN_PROP
  prop->dtv_ien.chlien                       = Si2177_DTV_IEN_PROP_CHLIEN_ENABLE ; /* (default 'ENABLE') */
#endif /* Si2177_DTV_IEN_PROP */

#ifdef    Si2177_DTV_IF_AGC_SPEED_PROP
  prop->dtv_if_agc_speed.attack              = Si2177_DTV_IF_AGC_SPEED_PROP_ATTACK_AUTO ; /* (default 'AUTO') */
  prop->dtv_if_agc_speed.decay               = Si2177_DTV_IF_AGC_SPEED_PROP_DECAY_AUTO  ; /* (default 'AUTO') */
#endif /* Si2177_DTV_IF_AGC_SPEED_PROP */

#ifdef    Si2177_DTV_INITIAL_AGC_SPEED_PROP
  prop->dtv_initial_agc_speed.if_agc_speed   = Si2177_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO ; /* (default 'AUTO') */
  prop->dtv_initial_agc_speed.agc_decim      = Si2177_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_OFF     ; /* (default 'OFF') */
#endif /* Si2177_DTV_INITIAL_AGC_SPEED_PROP */

#ifdef    Si2177_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
  prop->dtv_initial_agc_speed_period.period  =     0; /* (default     0) */
#endif /* Si2177_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */

#ifdef    Si2177_DTV_INTERNAL_ZIF_PROP
  prop->dtv_internal_zif.atsc                = Si2177_DTV_INTERNAL_ZIF_PROP_ATSC_ZIF   ; /* (default 'ZIF') */
  prop->dtv_internal_zif.qam_us              = Si2177_DTV_INTERNAL_ZIF_PROP_QAM_US_ZIF ; /* (default 'ZIF') */
  prop->dtv_internal_zif.dvbt                = Si2177_DTV_INTERNAL_ZIF_PROP_DVBT_ZIF   ; /* (default 'ZIF') */
  prop->dtv_internal_zif.dvbc                = Si2177_DTV_INTERNAL_ZIF_PROP_DVBC_ZIF   ; /* (default 'ZIF') */
  prop->dtv_internal_zif.isdbt               = Si2177_DTV_INTERNAL_ZIF_PROP_ISDBT_ZIF  ; /* (default 'ZIF') */
  prop->dtv_internal_zif.isdbc               = Si2177_DTV_INTERNAL_ZIF_PROP_ISDBC_ZIF  ; /* (default 'ZIF') */
  prop->dtv_internal_zif.dtmb                = Si2177_DTV_INTERNAL_ZIF_PROP_DTMB_LIF   ; /* (default 'LIF') */
#endif /* Si2177_DTV_INTERNAL_ZIF_PROP */

#ifdef    Si2177_DTV_INT_SENSE_PROP
  prop->dtv_int_sense.chlnegen               = Si2177_DTV_INT_SENSE_PROP_CHLNEGEN_DISABLE ; /* (default 'DISABLE') */
  prop->dtv_int_sense.chlposen               = Si2177_DTV_INT_SENSE_PROP_CHLPOSEN_ENABLE  ; /* (default 'ENABLE') */
#endif /* Si2177_DTV_INT_SENSE_PROP */

#ifdef    Si2177_DTV_LIF_FREQ_PROP
  prop->dtv_lif_freq.offset                  =  5000; /* (default  5000) */
#endif /* Si2177_DTV_LIF_FREQ_PROP */

#ifdef    Si2177_DTV_LIF_OUT_PROP
  prop->dtv_lif_out.offset                   =   148; /* (default   148) */
  prop->dtv_lif_out.amp                      =    27; /* (default    27) */
#endif /* Si2177_DTV_LIF_OUT_PROP */

#ifdef    Si2177_DTV_MODE_PROP
  prop->dtv_mode.bw                          = Si2177_DTV_MODE_PROP_BW_BW_8MHZ              ; /* (default 'BW_8MHZ') */
  prop->dtv_mode.modulation                  = Si2177_DTV_MODE_PROP_MODULATION_DVBT         ; /* (default 'DVBT') */
  prop->dtv_mode.invert_spectrum             = Si2177_DTV_MODE_PROP_INVERT_SPECTRUM_NORMAL  ; /* (default 'NORMAL') */
#endif /* Si2177_DTV_MODE_PROP */

#ifdef    Si2177_DTV_PGA_LIMITS_PROP
  prop->dtv_pga_limits.min                   =    -1; /* (default    -1) */
  prop->dtv_pga_limits.max                   =    -1; /* (default    -1) */
#endif /* Si2177_DTV_PGA_LIMITS_PROP */

#ifdef    Si2177_DTV_PGA_TARGET_PROP
  prop->dtv_pga_target.pga_target            =     0; /* (default     0) */
  prop->dtv_pga_target.override_enable       = Si2177_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_DISABLE ; /* (default 'DISABLE') */
#endif /* Si2177_DTV_PGA_TARGET_PROP */

#ifdef    Si2177_DTV_RF_AGC_SPEED_PROP
  prop->dtv_rf_agc_speed.attack              = Si2177_DTV_RF_AGC_SPEED_PROP_ATTACK_AUTO ; /* (default 'AUTO') */
  prop->dtv_rf_agc_speed.decay               = Si2177_DTV_RF_AGC_SPEED_PROP_DECAY_AUTO  ; /* (default 'AUTO') */
#endif /* Si2177_DTV_RF_AGC_SPEED_PROP */

#ifdef    Si2177_DTV_RF_TOP_PROP
  prop->dtv_rf_top.dtv_rf_top                = Si2177_DTV_RF_TOP_PROP_DTV_RF_TOP_AUTO ; /* (default 'AUTO') */
#endif /* Si2177_DTV_RF_TOP_PROP */

#ifdef    Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP
  prop->dtv_rsq_rssi_threshold.lo            =   -80; /* (default   -80) */
  prop->dtv_rsq_rssi_threshold.hi            =     0; /* (default     0) */
#endif /* Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP */

#ifdef    Si2177_DTV_WB_AGC_SPEED_PROP
  prop->dtv_wb_agc_speed.attack              = Si2177_DTV_WB_AGC_SPEED_PROP_ATTACK_AUTO ; /* (default 'AUTO') */
  prop->dtv_wb_agc_speed.decay               = Si2177_DTV_WB_AGC_SPEED_PROP_DECAY_AUTO  ; /* (default 'AUTO') */
#endif /* Si2177_DTV_WB_AGC_SPEED_PROP */

#ifdef    Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP
  prop->dtv_zif_dc_canceller_bw.bandwidth    = Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_DEFAULT ; /* (default 'DEFAULT') */
#endif /* Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP */

#ifdef    Si2177_TUNER_BLOCKED_VCO_PROP
  prop->tuner_blocked_vco.vco_code           = 0x8000; /* (default 0x8000) */
#endif /* Si2177_TUNER_BLOCKED_VCO_PROP */

#ifdef    Si2177_TUNER_IEN_PROP
  prop->tuner_ien.tcien                      = Si2177_TUNER_IEN_PROP_TCIEN_ENABLE     ; /* (default 'ENABLE') */
  prop->tuner_ien.rssilien                   = Si2177_TUNER_IEN_PROP_RSSILIEN_DISABLE ; /* (default 'DISABLE') */
  prop->tuner_ien.rssihien                   = Si2177_TUNER_IEN_PROP_RSSIHIEN_DISABLE ; /* (default 'DISABLE') */
#endif /* Si2177_TUNER_IEN_PROP */

#ifdef    Si2177_TUNER_INT_SENSE_PROP
  prop->tuner_int_sense.tcnegen              = Si2177_TUNER_INT_SENSE_PROP_TCNEGEN_DISABLE    ; /* (default 'DISABLE') */
  prop->tuner_int_sense.rssilnegen           = Si2177_TUNER_INT_SENSE_PROP_RSSILNEGEN_DISABLE ; /* (default 'DISABLE') */
  prop->tuner_int_sense.rssihnegen           = Si2177_TUNER_INT_SENSE_PROP_RSSIHNEGEN_DISABLE ; /* (default 'DISABLE') */
  prop->tuner_int_sense.tcposen              = Si2177_TUNER_INT_SENSE_PROP_TCPOSEN_ENABLE     ; /* (default 'ENABLE') */
  prop->tuner_int_sense.rssilposen           = Si2177_TUNER_INT_SENSE_PROP_RSSILPOSEN_ENABLE  ; /* (default 'ENABLE') */
  prop->tuner_int_sense.rssihposen           = Si2177_TUNER_INT_SENSE_PROP_RSSIHPOSEN_ENABLE  ; /* (default 'ENABLE') */
#endif /* Si2177_TUNER_INT_SENSE_PROP */

#ifdef    Si2177_TUNER_LO_INJECTION_PROP
  prop->tuner_lo_injection.band_1            = Si2177_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE ; /* (default 'HIGH_SIDE') */
  prop->tuner_lo_injection.band_2            = Si2177_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE  ; /* (default 'LOW_SIDE') */
  prop->tuner_lo_injection.band_3            = Si2177_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE  ; /* (default 'LOW_SIDE') */
#endif /* Si2177_TUNER_LO_INJECTION_PROP */

#ifdef    Si2177_TUNER_RETURN_LOSS_PROP
  prop->tuner_return_loss.config             = Si2177_TUNER_RETURN_LOSS_PROP_CONFIG_127         ; /* (default '127') */
  prop->tuner_return_loss.mode               = Si2177_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL   ; /* (default 'TERRESTRIAL') */
#endif /* Si2177_TUNER_RETURN_LOSS_PROP */

}
#ifdef    Si2177_GET_PROPERTY_STRING
/***********************************************************************************************************************
  Si2177_L1_PropertyText function
  Use:        property text function
              Used to turn the property data into clear text.
  Parameter: *prop     the Si2177 property structure (containing all properties)
  Parameter: prop_code the property Id (used to know which property to use)
  Parameter: separator the string to use between fields (often either a blank or a newline character)
  Parameter: msg       the string used to store the resulting string (usually declared with a size of 1000 bytes)
                       It must be declared by the caller with a size of 1000 bytes
  Returns:    NO_Si2177_ERROR if successful.
 ***********************************************************************************************************************/
unsigned char Si2177_L1_PropertyText          (Si2177_PropObj   *prop, unsigned int prop_code, const char *separator, char *msg) {
    switch (prop_code) {
    #ifdef        Si2177_ATV_AFC_RANGE_PROP
     case         Si2177_ATV_AFC_RANGE_PROP_CODE:
      sprintf(msg,"ATV_AFC_RANGE");
       strcat(msg,separator); strcat(msg,"-RANGE_KHZ "); sprintf(msg,"%s%d", msg, prop->atv_afc_range.range_khz);
     break;
    #endif /*     Si2177_ATV_AFC_RANGE_PROP */
    #ifdef        Si2177_ATV_AF_OUT_PROP
     case         Si2177_ATV_AF_OUT_PROP_CODE:
      sprintf(msg,"ATV_AF_OUT");
       strcat(msg,separator); strcat(msg,"-VOLUME "); sprintf(msg,"%s%d", msg, prop->atv_af_out.volume);
       strcat(msg,separator); strcat(msg,"-MUTE ");
           if  (prop->atv_af_out.soft_mute   ==     0) strcat(msg,"NORMAL ");
      else if  (prop->atv_af_out.soft_mute   ==     1) strcat(msg,"MUTE   ");
      else                                       sprintf(msg,"%s%d", msg, prop->atv_af_out.soft_mute);
     break;
    #endif /*     Si2177_ATV_AF_OUT_PROP */
    #ifdef        Si2177_ATV_AGC_SPEED_PROP
     case         Si2177_ATV_AGC_SPEED_PROP_CODE:
      sprintf(msg,"ATV_AGC_SPEED");
       strcat(msg,separator); strcat(msg,"-IF_AGC_SPEED ");
           if  (prop->atv_agc_speed.if_agc_speed ==     0) strcat(msg,"AUTO   ");
      else if  (prop->atv_agc_speed.if_agc_speed ==    89) strcat(msg,"89     ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   105) strcat(msg,"105    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   121) strcat(msg,"121    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   137) strcat(msg,"137    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   158) strcat(msg,"158    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   172) strcat(msg,"172    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   178) strcat(msg,"178    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   185) strcat(msg,"185    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   196) strcat(msg,"196    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   206) strcat(msg,"206    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   216) strcat(msg,"216    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   219) strcat(msg,"219    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   222) strcat(msg,"222    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   223) strcat(msg,"223    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   248) strcat(msg,"248    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   250) strcat(msg,"250    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   251) strcat(msg,"251    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==     1) strcat(msg,"CUSTOM ");
      else                                                sprintf(msg,"%s%d", msg, prop->atv_agc_speed.if_agc_speed);
     break;
    #endif /*     Si2177_ATV_AGC_SPEED_PROP */
    #ifdef        Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP
     case         Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP_CODE:
      sprintf(msg,"ATV_AGC_SPEED_LOW_RSSI");
       strcat(msg,separator); strcat(msg,"-IF_AGC_SPEED ");
           if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==    89) strcat(msg,"89     ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   105) strcat(msg,"105    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   121) strcat(msg,"121    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   137) strcat(msg,"137    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   158) strcat(msg,"158    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   172) strcat(msg,"172    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   178) strcat(msg,"178    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   185) strcat(msg,"185    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   196) strcat(msg,"196    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   206) strcat(msg,"206    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   216) strcat(msg,"216    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   219) strcat(msg,"219    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   222) strcat(msg,"222    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   223) strcat(msg,"223    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   248) strcat(msg,"248    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   250) strcat(msg,"250    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   251) strcat(msg,"251    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==     1) strcat(msg,"CUSTOM ");
      else                                                         sprintf(msg,"%s%d", msg, prop->atv_agc_speed_low_rssi.if_agc_speed);
       strcat(msg,separator); strcat(msg,"-THLD "); sprintf(msg,"%s%d", msg, prop->atv_agc_speed_low_rssi.thld);
     break;
    #endif /*     Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP */
    #ifdef        Si2177_ATV_ARTIFICIAL_SNOW_PROP
     case         Si2177_ATV_ARTIFICIAL_SNOW_PROP_CODE:
      sprintf(msg,"ATV_ARTIFICIAL_SNOW");
       strcat(msg,separator); strcat(msg,"-GAIN ");
           if  (prop->atv_artificial_snow.gain   ==     0) strcat(msg,"AUTO ");
      else if  (prop->atv_artificial_snow.gain   ==     1) strcat(msg,"0DB  ");
      else if  (prop->atv_artificial_snow.gain   ==     2) strcat(msg,"6DB  ");
      else if  (prop->atv_artificial_snow.gain   ==     3) strcat(msg,"12DB ");
      else if  (prop->atv_artificial_snow.gain   ==     4) strcat(msg,"18DB ");
      else if  (prop->atv_artificial_snow.gain   ==     5) strcat(msg,"24DB ");
      else if  (prop->atv_artificial_snow.gain   ==     6) strcat(msg,"30DB ");
      else if  (prop->atv_artificial_snow.gain   ==     7) strcat(msg,"36DB ");
      else if  (prop->atv_artificial_snow.gain   ==     8) strcat(msg,"42DB ");
      else if  (prop->atv_artificial_snow.gain   ==     9) strcat(msg,"OFF  ");
      else                                                sprintf(msg,"%s%d", msg, prop->atv_artificial_snow.gain);
       strcat(msg,separator); strcat(msg,"-SOUND ");
           if  (prop->atv_artificial_snow.sound  ==     0) strcat(msg,"MUTE         ");
      else if  (prop->atv_artificial_snow.sound  ==     1) strcat(msg,"6DB          ");
      else if  (prop->atv_artificial_snow.sound  ==     2) strcat(msg,"12DB         ");
      else if  (prop->atv_artificial_snow.sound  ==     3) strcat(msg,"18DB         ");
      else if  (prop->atv_artificial_snow.sound  ==     4) strcat(msg,"24DB         ");
      else if  (prop->atv_artificial_snow.sound  ==     5) strcat(msg,"30DB         ");
      else if  (prop->atv_artificial_snow.sound  ==     6) strcat(msg,"36DB         ");
      else if  (prop->atv_artificial_snow.sound  ==     7) strcat(msg,"PASS_THROUGH ");
      else                                                sprintf(msg,"%s%d", msg, prop->atv_artificial_snow.sound);
       strcat(msg,separator); strcat(msg,"-PERIOD ");
           if  (prop->atv_artificial_snow.period ==     0) strcat(msg,"LONG  ");
      else if  (prop->atv_artificial_snow.period ==     1) strcat(msg,"SHORT ");
      else                                                sprintf(msg,"%s%d", msg, prop->atv_artificial_snow.period);
       strcat(msg,separator); strcat(msg,"-OFFSET "); sprintf(msg,"%s%d", msg, prop->atv_artificial_snow.offset);
     break;
    #endif /*     Si2177_ATV_ARTIFICIAL_SNOW_PROP */
    #ifdef        Si2177_ATV_AUDIO_MODE_PROP
     case         Si2177_ATV_AUDIO_MODE_PROP_CODE:
      sprintf(msg,"ATV_AUDIO_MODE");
       strcat(msg,separator); strcat(msg,"-AUDIO_SYS ");
           if  (prop->atv_audio_mode.audio_sys  ==     0) strcat(msg,"DEFAULT         ");
      else if  (prop->atv_audio_mode.audio_sys  ==     1) strcat(msg,"MONO            ");
      else if  (prop->atv_audio_mode.audio_sys  ==     2) strcat(msg,"MONO_NICAM      ");
      else if  (prop->atv_audio_mode.audio_sys  ==     3) strcat(msg,"A2              ");
      else if  (prop->atv_audio_mode.audio_sys  ==     4) strcat(msg,"A2_DK2          ");
      else if  (prop->atv_audio_mode.audio_sys  ==     5) strcat(msg,"A2_DK3          ");
      else if  (prop->atv_audio_mode.audio_sys  ==     6) strcat(msg,"BTSC            ");
      else if  (prop->atv_audio_mode.audio_sys  ==     7) strcat(msg,"EIAJ            ");
      else if  (prop->atv_audio_mode.audio_sys  ==     8) strcat(msg,"SCAN            ");
      else if  (prop->atv_audio_mode.audio_sys  ==     9) strcat(msg,"A2_DK4          ");
      else if  (prop->atv_audio_mode.audio_sys  ==    10) strcat(msg,"WIDE_SCAN       ");
      else if  (prop->atv_audio_mode.audio_sys  ==    11) strcat(msg,"MONO_NICAM_6DB  ");
      else if  (prop->atv_audio_mode.audio_sys  ==    12) strcat(msg,"MONO_NICAM_10DB ");
      else                                               sprintf(msg,"%s%d", msg, prop->atv_audio_mode.audio_sys);
       strcat(msg,separator); strcat(msg,"-DEMOD_MODE ");
           if  (prop->atv_audio_mode.demod_mode ==     0) strcat(msg,"SIF ");
      else if  (prop->atv_audio_mode.demod_mode ==     1) strcat(msg,"AM  ");
      else if  (prop->atv_audio_mode.demod_mode ==     2) strcat(msg,"FM1 ");
      else if  (prop->atv_audio_mode.demod_mode ==     3) strcat(msg,"FM2 ");
      else                                               sprintf(msg,"%s%d", msg, prop->atv_audio_mode.demod_mode);
       strcat(msg,separator); strcat(msg,"-CHAN_BW ");
           if  (prop->atv_audio_mode.chan_bw    ==     0) strcat(msg,"DEFAULT        ");
      else if  (prop->atv_audio_mode.chan_bw    ==     1) strcat(msg,"4X_OVERMOD     ");
      else if  (prop->atv_audio_mode.chan_bw    ==     2) strcat(msg,"8X_OVERMOD     ");
      else if  (prop->atv_audio_mode.chan_bw    ==     3) strcat(msg,"12X_OVERMOD    ");
      else if  (prop->atv_audio_mode.chan_bw    ==     4) strcat(msg,"7P5_KHZ_OFFSET ");
      else if  (prop->atv_audio_mode.chan_bw    ==     5) strcat(msg,"15_KHZ_OFFSET  ");
      else if  (prop->atv_audio_mode.chan_bw    ==     6) strcat(msg,"30_KHZ_OFFSET  ");
      else if  (prop->atv_audio_mode.chan_bw    ==     7) strcat(msg,"75_KHZ_OFFSET  ");
      else if  (prop->atv_audio_mode.chan_bw    ==     8) strcat(msg,"150_KHZ_OFFSET ");
      else if  (prop->atv_audio_mode.chan_bw    ==     9) strcat(msg,"CUSTOM         ");
      else                                               sprintf(msg,"%s%d", msg, prop->atv_audio_mode.chan_bw);
     break;
    #endif /*     Si2177_ATV_AUDIO_MODE_PROP */
    #ifdef        Si2177_ATV_CONFIG_IF_PORT_PROP
     case         Si2177_ATV_CONFIG_IF_PORT_PROP_CODE:
      sprintf(msg,"ATV_CONFIG_IF_PORT");
       strcat(msg,separator); strcat(msg,"-ATV_OUT_TYPE ");
           if  (prop->atv_config_if_port.atv_out_type ==     0) strcat(msg,"CVBS_IF2B_SOUND_IF2A ");
      else if  (prop->atv_config_if_port.atv_out_type ==     8) strcat(msg,"LIF_DIFF_IF1         ");
      else if  (prop->atv_config_if_port.atv_out_type ==    10) strcat(msg,"LIF_DIFF_IF2         ");
      else if  (prop->atv_config_if_port.atv_out_type ==    12) strcat(msg,"LIF_SE_IF1A          ");
      else if  (prop->atv_config_if_port.atv_out_type ==    14) strcat(msg,"LIF_SE_IF2A          ");
      else                                                     sprintf(msg,"%s%d", msg, prop->atv_config_if_port.atv_out_type);
     break;
    #endif /*     Si2177_ATV_CONFIG_IF_PORT_PROP */
    #ifdef        Si2177_ATV_CVBS_OUT_PROP
     case         Si2177_ATV_CVBS_OUT_PROP_CODE:
      sprintf(msg,"ATV_CVBS_OUT");
       strcat(msg,separator); strcat(msg,"-OFFSET "); sprintf(msg,"%s%d", msg, prop->atv_cvbs_out.offset);
       strcat(msg,separator); strcat(msg,"-AMP "); sprintf(msg,"%s%d", msg, prop->atv_cvbs_out.amp);
     break;
    #endif /*     Si2177_ATV_CVBS_OUT_PROP */
    #ifdef        Si2177_ATV_CVBS_OUT_FINE_PROP
     case         Si2177_ATV_CVBS_OUT_FINE_PROP_CODE:
      sprintf(msg,"ATV_CVBS_OUT_FINE");
       strcat(msg,separator); strcat(msg,"-OFFSET "); sprintf(msg,"%s%d", msg, prop->atv_cvbs_out_fine.offset);
       strcat(msg,separator); strcat(msg,"-AMP "); sprintf(msg,"%s%d", msg, prop->atv_cvbs_out_fine.amp);
     break;
    #endif /*     Si2177_ATV_CVBS_OUT_FINE_PROP */
    #ifdef        Si2177_ATV_HSYNC_OUT_PROP
     case         Si2177_ATV_HSYNC_OUT_PROP_CODE:
      sprintf(msg,"ATV_HSYNC_OUT");
       strcat(msg,separator); strcat(msg,"-GPIO_SEL ");
           if  (prop->atv_hsync_out.gpio_sel ==     0) strcat(msg,"NONE  ");
      else if  (prop->atv_hsync_out.gpio_sel ==     1) strcat(msg,"GPIO1 ");
      else if  (prop->atv_hsync_out.gpio_sel ==     2) strcat(msg,"GPIO2 ");
      else                                            sprintf(msg,"%s%d", msg, prop->atv_hsync_out.gpio_sel);
       strcat(msg,separator); strcat(msg,"-WIDTH "); sprintf(msg,"%s%d", msg, prop->atv_hsync_out.width);
       strcat(msg,separator); strcat(msg,"-OFFSET "); sprintf(msg,"%s%d", msg, prop->atv_hsync_out.offset);
     break;
    #endif /*     Si2177_ATV_HSYNC_OUT_PROP */
    #ifdef        Si2177_ATV_IEN_PROP
     case         Si2177_ATV_IEN_PROP_CODE:
      sprintf(msg,"ATV_IEN");
       strcat(msg,separator); strcat(msg,"-CHLIEN ");
           if  (prop->atv_ien.chlien  ==     0) strcat(msg,"DISABLE ");
      else if  (prop->atv_ien.chlien  ==     1) strcat(msg,"ENABLE  ");
      else                                     sprintf(msg,"%s%d", msg, prop->atv_ien.chlien);
       strcat(msg,separator); strcat(msg,"-PCLIEN ");
           if  (prop->atv_ien.pclien  ==     0) strcat(msg,"DISABLE ");
      else if  (prop->atv_ien.pclien  ==     1) strcat(msg,"ENABLE  ");
      else                                     sprintf(msg,"%s%d", msg, prop->atv_ien.pclien);
       strcat(msg,separator); strcat(msg,"-DLIEN ");
           if  (prop->atv_ien.dlien   ==     0) strcat(msg,"DISABLE ");
      else if  (prop->atv_ien.dlien   ==     1) strcat(msg,"ENABLE  ");
      else                                     sprintf(msg,"%s%d", msg, prop->atv_ien.dlien);
       strcat(msg,separator); strcat(msg,"-SNRLIEN ");
           if  (prop->atv_ien.snrlien ==     0) strcat(msg,"DISABLE ");
      else if  (prop->atv_ien.snrlien ==     1) strcat(msg,"ENABLE  ");
      else                                     sprintf(msg,"%s%d", msg, prop->atv_ien.snrlien);
       strcat(msg,separator); strcat(msg,"-SNRHIEN ");
           if  (prop->atv_ien.snrhien ==     0) strcat(msg,"DISABLE ");
      else if  (prop->atv_ien.snrhien ==     1) strcat(msg,"ENABLE  ");
      else                                     sprintf(msg,"%s%d", msg, prop->atv_ien.snrhien);
     break;
    #endif /*     Si2177_ATV_IEN_PROP */
    #ifdef        Si2177_ATV_INT_SENSE_PROP
     case         Si2177_ATV_INT_SENSE_PROP_CODE:
      sprintf(msg,"ATV_INT_SENSE");
       strcat(msg,separator); strcat(msg,"-CHLNEGEN ");
           if  (prop->atv_int_sense.chlnegen  ==     0) strcat(msg,"DISABLE ");
      else if  (prop->atv_int_sense.chlnegen  ==     1) strcat(msg,"ENABLE  ");
      else                                             sprintf(msg,"%s%d", msg, prop->atv_int_sense.chlnegen);
       strcat(msg,separator); strcat(msg,"-PCLNEGEN ");
           if  (prop->atv_int_sense.pclnegen  ==     0) strcat(msg,"DISABLE ");
      else if  (prop->atv_int_sense.pclnegen  ==     1) strcat(msg,"ENABLE  ");
      else                                             sprintf(msg,"%s%d", msg, prop->atv_int_sense.pclnegen);
       strcat(msg,separator); strcat(msg,"-DLNEGEN ");
           if  (prop->atv_int_sense.dlnegen   ==     0) strcat(msg,"DISABLE ");
      else if  (prop->atv_int_sense.dlnegen   ==     1) strcat(msg,"ENABLE  ");
      else                                             sprintf(msg,"%s%d", msg, prop->atv_int_sense.dlnegen);
       strcat(msg,separator); strcat(msg,"-SNRLNEGEN ");
           if  (prop->atv_int_sense.snrlnegen ==     0) strcat(msg,"DISABLE ");
      else if  (prop->atv_int_sense.snrlnegen ==     1) strcat(msg,"ENABLE  ");
      else                                             sprintf(msg,"%s%d", msg, prop->atv_int_sense.snrlnegen);
       strcat(msg,separator); strcat(msg,"-SNRHNEGEN ");
           if  (prop->atv_int_sense.snrhnegen ==     0) strcat(msg,"DISABLE ");
      else if  (prop->atv_int_sense.snrhnegen ==     1) strcat(msg,"ENABLE  ");
      else                                             sprintf(msg,"%s%d", msg, prop->atv_int_sense.snrhnegen);
       strcat(msg,separator); strcat(msg,"-CHLPOSEN ");
           if  (prop->atv_int_sense.chlposen  ==     0) strcat(msg,"DISABLE ");
      else if  (prop->atv_int_sense.chlposen  ==     1) strcat(msg,"ENABLE  ");
      else                                             sprintf(msg,"%s%d", msg, prop->atv_int_sense.chlposen);
       strcat(msg,separator); strcat(msg,"-PCLPOSEN ");
           if  (prop->atv_int_sense.pclposen  ==     0) strcat(msg,"DISABLE ");
      else if  (prop->atv_int_sense.pclposen  ==     1) strcat(msg,"ENABLE  ");
      else                                             sprintf(msg,"%s%d", msg, prop->atv_int_sense.pclposen);
       strcat(msg,separator); strcat(msg,"-DLPOSEN ");
           if  (prop->atv_int_sense.dlposen   ==     0) strcat(msg,"DISABLE ");
      else if  (prop->atv_int_sense.dlposen   ==     1) strcat(msg,"ENABLE  ");
      else                                             sprintf(msg,"%s%d", msg, prop->atv_int_sense.dlposen);
       strcat(msg,separator); strcat(msg,"-SNRLPOSEN ");
           if  (prop->atv_int_sense.snrlposen ==     0) strcat(msg,"DISABLE ");
      else if  (prop->atv_int_sense.snrlposen ==     1) strcat(msg,"ENABLE  ");
      else                                             sprintf(msg,"%s%d", msg, prop->atv_int_sense.snrlposen);
       strcat(msg,separator); strcat(msg,"-SNRHPOSEN ");
           if  (prop->atv_int_sense.snrhposen ==     0) strcat(msg,"DISABLE ");
      else if  (prop->atv_int_sense.snrhposen ==     1) strcat(msg,"ENABLE  ");
      else                                             sprintf(msg,"%s%d", msg, prop->atv_int_sense.snrhposen);
     break;
    #endif /*     Si2177_ATV_INT_SENSE_PROP */
    #ifdef        Si2177_ATV_PGA_TARGET_PROP
     case         Si2177_ATV_PGA_TARGET_PROP_CODE:
      sprintf(msg,"ATV_PGA_TARGET");
       strcat(msg,separator); strcat(msg,"-PGA_TARGET "); sprintf(msg,"%s%d", msg, prop->atv_pga_target.pga_target);
       strcat(msg,separator); strcat(msg,"-OVERRIDE_ENABLE ");
           if  (prop->atv_pga_target.override_enable ==     0) strcat(msg,"DISABLE ");
      else if  (prop->atv_pga_target.override_enable ==     1) strcat(msg,"ENABLE  ");
      else                                                    sprintf(msg,"%s%d", msg, prop->atv_pga_target.override_enable);
     break;
    #endif /*     Si2177_ATV_PGA_TARGET_PROP */
    #ifdef        Si2177_ATV_RF_TOP_PROP
     case         Si2177_ATV_RF_TOP_PROP_CODE:
      sprintf(msg,"ATV_RF_TOP");
       strcat(msg,separator); strcat(msg,"-ATV_RF_TOP ");
           if  (prop->atv_rf_top.atv_rf_top ==     0) strcat(msg,"AUTO  ");
      else if  (prop->atv_rf_top.atv_rf_top ==     1) strcat(msg,"P5DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==     2) strcat(msg,"P4DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==     3) strcat(msg,"P3DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==     4) strcat(msg,"P2DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==     5) strcat(msg,"P1DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==     6) strcat(msg,"0DB   ");
      else if  (prop->atv_rf_top.atv_rf_top ==     7) strcat(msg,"M1DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==     8) strcat(msg,"M2DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==     9) strcat(msg,"M3DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==    10) strcat(msg,"M4DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==    11) strcat(msg,"M5DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==    12) strcat(msg,"M6DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==    13) strcat(msg,"M7DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==    14) strcat(msg,"M8DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==    15) strcat(msg,"M9DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==    16) strcat(msg,"M10DB ");
      else if  (prop->atv_rf_top.atv_rf_top ==    17) strcat(msg,"M11DB ");
      else if  (prop->atv_rf_top.atv_rf_top ==    18) strcat(msg,"M12DB ");
      else if  (prop->atv_rf_top.atv_rf_top ==    19) strcat(msg,"M13DB ");
      else if  (prop->atv_rf_top.atv_rf_top ==    20) strcat(msg,"M14DB ");
      else if  (prop->atv_rf_top.atv_rf_top ==    21) strcat(msg,"M15DB ");
      else if  (prop->atv_rf_top.atv_rf_top ==    22) strcat(msg,"M16DB ");
      else if  (prop->atv_rf_top.atv_rf_top ==    23) strcat(msg,"M17DB ");
      else if  (prop->atv_rf_top.atv_rf_top ==    24) strcat(msg,"M18DB ");
      else                                           sprintf(msg,"%s%d", msg, prop->atv_rf_top.atv_rf_top);
     break;
    #endif /*     Si2177_ATV_RF_TOP_PROP */
    #ifdef        Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP_CODE:
      sprintf(msg,"ATV_RSQ_RSSI_THRESHOLD");
       strcat(msg,separator); strcat(msg,"-LO "); sprintf(msg,"%s%d", msg, prop->atv_rsq_rssi_threshold.lo);
       strcat(msg,separator); strcat(msg,"-HI "); sprintf(msg,"%s%d", msg, prop->atv_rsq_rssi_threshold.hi);
     break;
    #endif /*     Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2177_ATV_RSQ_SNR_THRESHOLD_PROP
     case         Si2177_ATV_RSQ_SNR_THRESHOLD_PROP_CODE:
      sprintf(msg,"ATV_RSQ_SNR_THRESHOLD");
       strcat(msg,separator); strcat(msg,"-LO "); sprintf(msg,"%s%d", msg, prop->atv_rsq_snr_threshold.lo);
       strcat(msg,separator); strcat(msg,"-HI "); sprintf(msg,"%s%d", msg, prop->atv_rsq_snr_threshold.hi);
     break;
    #endif /*     Si2177_ATV_RSQ_SNR_THRESHOLD_PROP */
    #ifdef        Si2177_ATV_SIF_OUT_PROP
     case         Si2177_ATV_SIF_OUT_PROP_CODE:
      sprintf(msg,"ATV_SIF_OUT");
       strcat(msg,separator); strcat(msg,"-OFFSET "); sprintf(msg,"%s%d", msg, prop->atv_sif_out.offset);
       strcat(msg,separator); strcat(msg,"-AMP "); sprintf(msg,"%s%d", msg, prop->atv_sif_out.amp);
     break;
    #endif /*     Si2177_ATV_SIF_OUT_PROP */
    #ifdef        Si2177_ATV_SOUND_AGC_LIMIT_PROP
     case         Si2177_ATV_SOUND_AGC_LIMIT_PROP_CODE:
      sprintf(msg,"ATV_SOUND_AGC_LIMIT");
       strcat(msg,separator); strcat(msg,"-MAX_GAIN "); sprintf(msg,"%s%d", msg, prop->atv_sound_agc_limit.max_gain);
       strcat(msg,separator); strcat(msg,"-MIN_GAIN "); sprintf(msg,"%s%d", msg, prop->atv_sound_agc_limit.min_gain);
     break;
    #endif /*     Si2177_ATV_SOUND_AGC_LIMIT_PROP */
    #ifdef        Si2177_ATV_SOUND_AGC_SPEED_PROP
     case         Si2177_ATV_SOUND_AGC_SPEED_PROP_CODE:
      sprintf(msg,"ATV_SOUND_AGC_SPEED");
       strcat(msg,separator); strcat(msg,"-SYSTEM_L "); sprintf(msg,"%s%d", msg, prop->atv_sound_agc_speed.system_l);
       strcat(msg,separator); strcat(msg,"-OTHER_SYSTEMS "); sprintf(msg,"%s%d", msg, prop->atv_sound_agc_speed.other_systems);
     break;
    #endif /*     Si2177_ATV_SOUND_AGC_SPEED_PROP */
    #ifdef        Si2177_ATV_VIDEO_EQUALIZER_PROP
     case         Si2177_ATV_VIDEO_EQUALIZER_PROP_CODE:
      sprintf(msg,"ATV_VIDEO_EQUALIZER");
       strcat(msg,separator); strcat(msg,"-SLOPE "); sprintf(msg,"%s%d", msg, prop->atv_video_equalizer.slope);
     break;
    #endif /*     Si2177_ATV_VIDEO_EQUALIZER_PROP */
    #ifdef        Si2177_ATV_VIDEO_MODE_PROP
     case         Si2177_ATV_VIDEO_MODE_PROP_CODE:
      sprintf(msg,"ATV_VIDEO_MODE");
       strcat(msg,separator); strcat(msg,"-VIDEO_SYS ");
           if  (prop->atv_video_mode.video_sys     ==     0) strcat(msg,"B  ");
      else if  (prop->atv_video_mode.video_sys     ==     1) strcat(msg,"GH ");
      else if  (prop->atv_video_mode.video_sys     ==     2) strcat(msg,"M  ");
      else if  (prop->atv_video_mode.video_sys     ==     3) strcat(msg,"N  ");
      else if  (prop->atv_video_mode.video_sys     ==     4) strcat(msg,"I  ");
      else if  (prop->atv_video_mode.video_sys     ==     5) strcat(msg,"DK ");
      else if  (prop->atv_video_mode.video_sys     ==     6) strcat(msg,"L  ");
      else if  (prop->atv_video_mode.video_sys     ==     7) strcat(msg,"LP ");
      else                                                  sprintf(msg,"%s%d", msg, prop->atv_video_mode.video_sys);
       strcat(msg,separator); strcat(msg,"-COLOR ");
           if  (prop->atv_video_mode.color         ==     0) strcat(msg,"PAL_NTSC ");
      else if  (prop->atv_video_mode.color         ==     1) strcat(msg,"SECAM    ");
      else                                                  sprintf(msg,"%s%d", msg, prop->atv_video_mode.color);
       strcat(msg,separator); strcat(msg,"-INVERT_SIGNAL ");
           if  (prop->atv_video_mode.invert_signal ==     0) strcat(msg,"NORMAL   ");
      else if  (prop->atv_video_mode.invert_signal ==     1) strcat(msg,"INVERTED ");
      else                                                  sprintf(msg,"%s%d", msg, prop->atv_video_mode.invert_signal);
     break;
    #endif /*     Si2177_ATV_VIDEO_MODE_PROP */
    #ifdef        Si2177_ATV_VSNR_CAP_PROP
     case         Si2177_ATV_VSNR_CAP_PROP_CODE:
      sprintf(msg,"ATV_VSNR_CAP");
       strcat(msg,separator); strcat(msg,"-ATV_VSNR_CAP "); sprintf(msg,"%s%d", msg, prop->atv_vsnr_cap.atv_vsnr_cap);
     break;
    #endif /*     Si2177_ATV_VSNR_CAP_PROP */
    #ifdef        Si2177_CRYSTAL_TRIM_PROP
     case         Si2177_CRYSTAL_TRIM_PROP_CODE:
      sprintf(msg,"CRYSTAL_TRIM");
       strcat(msg,separator); strcat(msg,"-XO_CAP ");
           if  (prop->crystal_trim.xo_cap ==     0) strcat(msg,"4p7pF  ");
      else if  (prop->crystal_trim.xo_cap ==     1) strcat(msg,"4p95pF ");
      else if  (prop->crystal_trim.xo_cap ==     2) strcat(msg,"5p2pF  ");
      else if  (prop->crystal_trim.xo_cap ==     3) strcat(msg,"5p45pF ");
      else if  (prop->crystal_trim.xo_cap ==     4) strcat(msg,"5p7pF  ");
      else if  (prop->crystal_trim.xo_cap ==     5) strcat(msg,"5p95pF ");
      else if  (prop->crystal_trim.xo_cap ==     6) strcat(msg,"6p2pF  ");
      else if  (prop->crystal_trim.xo_cap ==     7) strcat(msg,"6p45pF ");
      else if  (prop->crystal_trim.xo_cap ==     8) strcat(msg,"6p7pF  ");
      else if  (prop->crystal_trim.xo_cap ==     9) strcat(msg,"6p95pF ");
      else if  (prop->crystal_trim.xo_cap ==    10) strcat(msg,"7p2pF  ");
      else if  (prop->crystal_trim.xo_cap ==    11) strcat(msg,"7p45pF ");
      else if  (prop->crystal_trim.xo_cap ==    12) strcat(msg,"7p7pF  ");
      else if  (prop->crystal_trim.xo_cap ==    13) strcat(msg,"7p95pF ");
      else if  (prop->crystal_trim.xo_cap ==    14) strcat(msg,"8p2pF  ");
      else if  (prop->crystal_trim.xo_cap ==    15) strcat(msg,"8p45pF ");
      else                                         sprintf(msg,"%s%d", msg, prop->crystal_trim.xo_cap);
     break;
    #endif /*     Si2177_CRYSTAL_TRIM_PROP */
    #ifdef        Si2177_DTV_AGC_FREEZE_INPUT_PROP
     case         Si2177_DTV_AGC_FREEZE_INPUT_PROP_CODE:
      sprintf(msg,"DTV_AGC_FREEZE_INPUT");
       strcat(msg,separator); strcat(msg,"-LEVEL ");
           if  (prop->dtv_agc_freeze_input.level ==     0) strcat(msg,"LOW  ");
      else if  (prop->dtv_agc_freeze_input.level ==     1) strcat(msg,"HIGH ");
      else                                                sprintf(msg,"%s%d", msg, prop->dtv_agc_freeze_input.level);
       strcat(msg,separator); strcat(msg,"-PIN ");
           if  (prop->dtv_agc_freeze_input.pin   ==     0) strcat(msg,"NONE     ");
      else if  (prop->dtv_agc_freeze_input.pin   ==     1) strcat(msg,"GPIO1    ");
      else if  (prop->dtv_agc_freeze_input.pin   ==     2) strcat(msg,"GPIO2    ");
      else if  (prop->dtv_agc_freeze_input.pin   ==     3) strcat(msg,"RESERVED ");
      else if  (prop->dtv_agc_freeze_input.pin   ==     4) strcat(msg,"AGC1     ");
      else if  (prop->dtv_agc_freeze_input.pin   ==     5) strcat(msg,"AGC2     ");
      else if  (prop->dtv_agc_freeze_input.pin   ==     6) strcat(msg,"LIF1A    ");
      else if  (prop->dtv_agc_freeze_input.pin   ==     7) strcat(msg,"LIF1B    ");
      else                                                sprintf(msg,"%s%d", msg, prop->dtv_agc_freeze_input.pin);
     break;
    #endif /*     Si2177_DTV_AGC_FREEZE_INPUT_PROP */
    #ifdef        Si2177_DTV_AGC_SPEED_PROP
     case         Si2177_DTV_AGC_SPEED_PROP_CODE:
      sprintf(msg,"DTV_AGC_SPEED");
       strcat(msg,separator); strcat(msg,"-IF_AGC_SPEED ");
           if  (prop->dtv_agc_speed.if_agc_speed ==     0) strcat(msg,"AUTO ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==    39) strcat(msg,"39   ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==    54) strcat(msg,"54   ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==    63) strcat(msg,"63   ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==    89) strcat(msg,"89   ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   105) strcat(msg,"105  ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   121) strcat(msg,"121  ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   137) strcat(msg,"137  ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   158) strcat(msg,"158  ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   172) strcat(msg,"172  ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   185) strcat(msg,"185  ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   196) strcat(msg,"196  ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   206) strcat(msg,"206  ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   216) strcat(msg,"216  ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   219) strcat(msg,"219  ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   222) strcat(msg,"222  ");
      else                                                sprintf(msg,"%s%d", msg, prop->dtv_agc_speed.if_agc_speed);
       strcat(msg,separator); strcat(msg,"-AGC_DECIM ");
           if  (prop->dtv_agc_speed.agc_decim    ==     0) strcat(msg,"OFF ");
      else if  (prop->dtv_agc_speed.agc_decim    ==     1) strcat(msg,"2   ");
      else if  (prop->dtv_agc_speed.agc_decim    ==     2) strcat(msg,"4   ");
      else if  (prop->dtv_agc_speed.agc_decim    ==     3) strcat(msg,"8   ");
      else                                                sprintf(msg,"%s%d", msg, prop->dtv_agc_speed.agc_decim);
     break;
    #endif /*     Si2177_DTV_AGC_SPEED_PROP */
    #ifdef        Si2177_DTV_CONFIG_IF_PORT_PROP
     case         Si2177_DTV_CONFIG_IF_PORT_PROP_CODE:
      sprintf(msg,"DTV_CONFIG_IF_PORT");
       strcat(msg,separator); strcat(msg,"-DTV_OUT_TYPE ");
           if  (prop->dtv_config_if_port.dtv_out_type   ==     0) strcat(msg,"LIF_IF1     ");
      else if  (prop->dtv_config_if_port.dtv_out_type   ==     1) strcat(msg,"LIF_IF2     ");
      else if  (prop->dtv_config_if_port.dtv_out_type   ==     4) strcat(msg,"LIF_SE_IF1A ");
      else if  (prop->dtv_config_if_port.dtv_out_type   ==     5) strcat(msg,"LIF_SE_IF2A ");
      else                                                       sprintf(msg,"%s%d", msg, prop->dtv_config_if_port.dtv_out_type);
       strcat(msg,separator); strcat(msg,"-DTV_AGC_SOURCE ");
           if  (prop->dtv_config_if_port.dtv_agc_source ==     0) strcat(msg,"INTERNAL  ");
      else if  (prop->dtv_config_if_port.dtv_agc_source ==     1) strcat(msg,"AGC1_3DB  ");
      else if  (prop->dtv_config_if_port.dtv_agc_source ==     2) strcat(msg,"AGC2_3DB  ");
      else if  (prop->dtv_config_if_port.dtv_agc_source ==     3) strcat(msg,"AGC1_FULL ");
      else if  (prop->dtv_config_if_port.dtv_agc_source ==     4) strcat(msg,"AGC2_FULL ");
      else                                                       sprintf(msg,"%s%d", msg, prop->dtv_config_if_port.dtv_agc_source);
     break;
    #endif /*     Si2177_DTV_CONFIG_IF_PORT_PROP */
    #ifdef        Si2177_DTV_EXT_AGC_PROP
     case         Si2177_DTV_EXT_AGC_PROP_CODE:
      sprintf(msg,"DTV_EXT_AGC");
       strcat(msg,separator); strcat(msg,"-MIN_10MV "); sprintf(msg,"%s%d", msg, prop->dtv_ext_agc.min_10mv);
       strcat(msg,separator); strcat(msg,"-MAX_10MV "); sprintf(msg,"%s%d", msg, prop->dtv_ext_agc.max_10mv);
     break;
    #endif /*     Si2177_DTV_EXT_AGC_PROP */
    #ifdef        Si2177_DTV_IEN_PROP
     case         Si2177_DTV_IEN_PROP_CODE:
      sprintf(msg,"DTV_IEN");
       strcat(msg,separator); strcat(msg,"-CHLIEN ");
           if  (prop->dtv_ien.chlien ==     0) strcat(msg,"DISABLE ");
      else if  (prop->dtv_ien.chlien ==     1) strcat(msg,"ENABLE  ");
      else                                    sprintf(msg,"%s%d", msg, prop->dtv_ien.chlien);
     break;
    #endif /*     Si2177_DTV_IEN_PROP */
    #ifdef        Si2177_DTV_IF_AGC_SPEED_PROP
     case         Si2177_DTV_IF_AGC_SPEED_PROP_CODE:
      sprintf(msg,"%s","DTV_IF_AGC_SPEED");
       strcat(msg,separator); strcat(msg,"-ATTACK ");
           if  (prop->dtv_if_agc_speed.attack ==     0) strcat(msg,"AUTO ");
      else                                             sprintf(msg,"%d", prop->dtv_if_agc_speed.attack);
       strcat(msg,separator); strcat(msg,"-DECAY ");
           if  (prop->dtv_if_agc_speed.decay  ==     0) strcat(msg,"AUTO ");
      else                                             sprintf(msg,"%s%d", msg,prop->dtv_if_agc_speed.decay);
     break;
    #endif /*     Si2177_DTV_IF_AGC_SPEED_PROP */
    #ifdef        Si2177_DTV_INITIAL_AGC_SPEED_PROP
     case         Si2177_DTV_INITIAL_AGC_SPEED_PROP_CODE:
      sprintf(msg,"DTV_INITIAL_AGC_SPEED");
       strcat(msg,separator); strcat(msg,"-IF_AGC_SPEED ");
           if  (prop->dtv_initial_agc_speed.if_agc_speed ==     0) strcat(msg,"AUTO ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==    39) strcat(msg,"39   ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==    54) strcat(msg,"54   ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==    63) strcat(msg,"63   ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==    89) strcat(msg,"89   ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   105) strcat(msg,"105  ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   121) strcat(msg,"121  ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   137) strcat(msg,"137  ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   158) strcat(msg,"158  ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   172) strcat(msg,"172  ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   185) strcat(msg,"185  ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   196) strcat(msg,"196  ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   206) strcat(msg,"206  ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   216) strcat(msg,"216  ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   219) strcat(msg,"219  ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   222) strcat(msg,"222  ");
      else                                                        sprintf(msg,"%s%d", msg, prop->dtv_initial_agc_speed.if_agc_speed);
       strcat(msg,separator); strcat(msg,"-AGC_DECIM ");
           if  (prop->dtv_initial_agc_speed.agc_decim    ==     0) strcat(msg,"OFF ");
      else if  (prop->dtv_initial_agc_speed.agc_decim    ==     1) strcat(msg,"2   ");
      else if  (prop->dtv_initial_agc_speed.agc_decim    ==     2) strcat(msg,"4   ");
      else if  (prop->dtv_initial_agc_speed.agc_decim    ==     3) strcat(msg,"8   ");
      else                                                        sprintf(msg,"%s%d", msg, prop->dtv_initial_agc_speed.agc_decim);
     break;
    #endif /*     Si2177_DTV_INITIAL_AGC_SPEED_PROP */
    #ifdef        Si2177_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
     case         Si2177_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE:
      sprintf(msg,"DTV_INITIAL_AGC_SPEED_PERIOD");
       strcat(msg,separator); strcat(msg,"-PERIOD "); sprintf(msg,"%s%d", msg, prop->dtv_initial_agc_speed_period.period);
     break;
    #endif /*     Si2177_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
    #ifdef        Si2177_DTV_INTERNAL_ZIF_PROP
     case         Si2177_DTV_INTERNAL_ZIF_PROP_CODE:
      sprintf(msg,"DTV_INTERNAL_ZIF");
       strcat(msg,separator); strcat(msg,"-ATSC ");
           if  (prop->dtv_internal_zif.atsc   ==     0) strcat(msg,"LIF ");
      else if  (prop->dtv_internal_zif.atsc   ==     1) strcat(msg,"ZIF ");
      else                                             sprintf(msg,"%s%d", msg, prop->dtv_internal_zif.atsc);
       strcat(msg,separator); strcat(msg,"-QAM_US ");
           if  (prop->dtv_internal_zif.qam_us ==     0) strcat(msg,"LIF ");
      else if  (prop->dtv_internal_zif.qam_us ==     1) strcat(msg,"ZIF ");
      else                                             sprintf(msg,"%s%d", msg, prop->dtv_internal_zif.qam_us);
       strcat(msg,separator); strcat(msg,"-DVBT ");
           if  (prop->dtv_internal_zif.dvbt   ==     0) strcat(msg,"LIF ");
      else if  (prop->dtv_internal_zif.dvbt   ==     1) strcat(msg,"ZIF ");
      else                                             sprintf(msg,"%s%d", msg, prop->dtv_internal_zif.dvbt);
       strcat(msg,separator); strcat(msg,"-DVBC ");
           if  (prop->dtv_internal_zif.dvbc   ==     0) strcat(msg,"LIF ");
      else if  (prop->dtv_internal_zif.dvbc   ==     1) strcat(msg,"ZIF ");
      else                                             sprintf(msg,"%s%d", msg, prop->dtv_internal_zif.dvbc);
       strcat(msg,separator); strcat(msg,"-ISDBT ");
           if  (prop->dtv_internal_zif.isdbt  ==     0) strcat(msg,"LIF ");
      else if  (prop->dtv_internal_zif.isdbt  ==     1) strcat(msg,"ZIF ");
      else                                             sprintf(msg,"%s%d", msg, prop->dtv_internal_zif.isdbt);
       strcat(msg,separator); strcat(msg,"-ISDBC ");
           if  (prop->dtv_internal_zif.isdbc  ==     0) strcat(msg,"LIF ");
      else if  (prop->dtv_internal_zif.isdbc  ==     1) strcat(msg,"ZIF ");
      else                                             sprintf(msg,"%s%d", msg, prop->dtv_internal_zif.isdbc);
       strcat(msg,separator); strcat(msg,"-DTMB ");
           if  (prop->dtv_internal_zif.dtmb   ==     0) strcat(msg,"LIF ");
      else if  (prop->dtv_internal_zif.dtmb   ==     1) strcat(msg,"ZIF ");
      else                                             sprintf(msg,"%s%d", msg, prop->dtv_internal_zif.dtmb);
     break;
    #endif /*     Si2177_DTV_INTERNAL_ZIF_PROP */
    #ifdef        Si2177_DTV_INT_SENSE_PROP
     case         Si2177_DTV_INT_SENSE_PROP_CODE:
      sprintf(msg,"DTV_INT_SENSE");
       strcat(msg,separator); strcat(msg,"-CHLNEGEN ");
           if  (prop->dtv_int_sense.chlnegen ==     0) strcat(msg,"DISABLE ");
      else if  (prop->dtv_int_sense.chlnegen ==     1) strcat(msg,"ENABLE  ");
      else                                            sprintf(msg,"%s%d", msg, prop->dtv_int_sense.chlnegen);
       strcat(msg,separator); strcat(msg,"-CHLPOSEN ");
           if  (prop->dtv_int_sense.chlposen ==     0) strcat(msg,"DISABLE ");
      else if  (prop->dtv_int_sense.chlposen ==     1) strcat(msg,"ENABLE  ");
      else                                            sprintf(msg,"%s%d", msg, prop->dtv_int_sense.chlposen);
     break;
    #endif /*     Si2177_DTV_INT_SENSE_PROP */
    #ifdef        Si2177_DTV_LIF_FREQ_PROP
     case         Si2177_DTV_LIF_FREQ_PROP_CODE:
      sprintf(msg,"DTV_LIF_FREQ");
       strcat(msg,separator); strcat(msg,"-OFFSET "); sprintf(msg,"%s%d", msg, prop->dtv_lif_freq.offset);
     break;
    #endif /*     Si2177_DTV_LIF_FREQ_PROP */
    #ifdef        Si2177_DTV_LIF_OUT_PROP
     case         Si2177_DTV_LIF_OUT_PROP_CODE:
      sprintf(msg,"DTV_LIF_OUT");
       strcat(msg,separator); strcat(msg,"-OFFSET "); sprintf(msg,"%s%d", msg, prop->dtv_lif_out.offset);
       strcat(msg,separator); strcat(msg,"-AMP "); sprintf(msg,"%s%d", msg, prop->dtv_lif_out.amp);
     break;
    #endif /*     Si2177_DTV_LIF_OUT_PROP */
    #ifdef        Si2177_DTV_MODE_PROP
     case         Si2177_DTV_MODE_PROP_CODE:
      sprintf(msg,"DTV_MODE");
       strcat(msg,separator); strcat(msg,"-BW ");
           if  (prop->dtv_mode.bw              ==     6) strcat(msg,"BW_6MHZ   ");
      else if  (prop->dtv_mode.bw              ==     7) strcat(msg,"BW_7MHZ   ");
      else if  (prop->dtv_mode.bw              ==     8) strcat(msg,"BW_8MHZ   ");
      else if  (prop->dtv_mode.bw              ==     9) strcat(msg,"BW_1P7MHZ ");
      else if  (prop->dtv_mode.bw              ==    10) strcat(msg,"BW_6P1MHZ ");
      else                                              sprintf(msg,"%s%d", msg, prop->dtv_mode.bw);
       strcat(msg,separator); strcat(msg,"-MODULATION ");
           if  (prop->dtv_mode.modulation      ==     0) strcat(msg,"ATSC      ");
      else if  (prop->dtv_mode.modulation      ==     1) strcat(msg,"QAM_US    ");
      else if  (prop->dtv_mode.modulation      ==     2) strcat(msg,"DVBT      ");
      else if  (prop->dtv_mode.modulation      ==     3) strcat(msg,"DVBC      ");
      else if  (prop->dtv_mode.modulation      ==     4) strcat(msg,"ISDBT     ");
      else if  (prop->dtv_mode.modulation      ==     5) strcat(msg,"ISDBC     ");
      else if  (prop->dtv_mode.modulation      ==     6) strcat(msg,"DTMB      ");
      else if  (prop->dtv_mode.modulation      ==    14) strcat(msg,"CW_LEGACY ");
      else if  (prop->dtv_mode.modulation      ==    15) strcat(msg,"CW        ");
      else                                              sprintf(msg,"%s%d", msg, prop->dtv_mode.modulation);
       strcat(msg,separator); strcat(msg,"-INVERT_SPECTRUM ");
           if  (prop->dtv_mode.invert_spectrum ==     0) strcat(msg,"NORMAL   ");
      else if  (prop->dtv_mode.invert_spectrum ==     1) strcat(msg,"INVERTED ");
      else                                              sprintf(msg,"%s%d", msg, prop->dtv_mode.invert_spectrum);
     break;
    #endif /*     Si2177_DTV_MODE_PROP */
    #ifdef        Si2177_DTV_PGA_LIMITS_PROP
     case         Si2177_DTV_PGA_LIMITS_PROP_CODE:
      sprintf(msg,"DTV_PGA_LIMITS");
       strcat(msg,separator); strcat(msg,"-MIN "); sprintf(msg,"%s%d", msg, prop->dtv_pga_limits.min);
       strcat(msg,separator); strcat(msg,"-MAX "); sprintf(msg,"%s%d", msg, prop->dtv_pga_limits.max);
     break;
    #endif /*     Si2177_DTV_PGA_LIMITS_PROP */
    #ifdef        Si2177_DTV_PGA_TARGET_PROP
     case         Si2177_DTV_PGA_TARGET_PROP_CODE:
      sprintf(msg,"DTV_PGA_TARGET");
       strcat(msg,separator); strcat(msg,"-PGA_TARGET "); sprintf(msg,"%s%d", msg, prop->dtv_pga_target.pga_target);
       strcat(msg,separator); strcat(msg,"-OVERRIDE_ENABLE ");
           if  (prop->dtv_pga_target.override_enable ==     0) strcat(msg,"DISABLE ");
      else if  (prop->dtv_pga_target.override_enable ==     1) strcat(msg,"ENABLE  ");
      else                                                    sprintf(msg,"%s%d", msg, prop->dtv_pga_target.override_enable);
     break;
    #endif /*     Si2177_DTV_PGA_TARGET_PROP */
    #ifdef        Si2177_DTV_RF_AGC_SPEED_PROP
     case         Si2177_DTV_RF_AGC_SPEED_PROP_CODE:
      sprintf(msg,"%s","DTV_RF_AGC_SPEED");
       strcat(msg,separator); strcat(msg,"-ATTACK ");
           if  (prop->dtv_rf_agc_speed.attack ==     0) strcat(msg,"AUTO ");
      else                                             sprintf(msg,"%s%d", msg,prop->dtv_rf_agc_speed.attack);
       strcat(msg,separator); strcat(msg,"-DECAY ");
           if  (prop->dtv_rf_agc_speed.decay  ==     0) strcat(msg,"AUTO ");
      else                                             sprintf(msg,"%s%d", msg,prop->dtv_rf_agc_speed.decay);
     break;
    #endif /*     Si2177_DTV_RF_AGC_SPEED_PROP */
    #ifdef        Si2177_DTV_RF_TOP_PROP
     case         Si2177_DTV_RF_TOP_PROP_CODE:
      sprintf(msg,"DTV_RF_TOP");
       strcat(msg,separator); strcat(msg,"-DTV_RF_TOP ");
           if  (prop->dtv_rf_top.dtv_rf_top ==     0) strcat(msg,"AUTO    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==     1) strcat(msg,"P10DB   ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==     2) strcat(msg,"P9P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==     3) strcat(msg,"P9DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==     4) strcat(msg,"P8P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==     5) strcat(msg,"P8DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==     6) strcat(msg,"P7P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==     7) strcat(msg,"P7DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==     8) strcat(msg,"P6P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==     9) strcat(msg,"P6DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    10) strcat(msg,"P5P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    11) strcat(msg,"P5DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    12) strcat(msg,"P4P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    13) strcat(msg,"P4DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    14) strcat(msg,"P3P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    15) strcat(msg,"P3DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    16) strcat(msg,"P2P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    17) strcat(msg,"P2DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    18) strcat(msg,"P1P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    19) strcat(msg,"P1DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    20) strcat(msg,"P0P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    21) strcat(msg,"0DB     ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    22) strcat(msg,"M0P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    23) strcat(msg,"M1DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    24) strcat(msg,"M1P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    25) strcat(msg,"M2DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    26) strcat(msg,"M2P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    27) strcat(msg,"M3DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    28) strcat(msg,"M3P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    29) strcat(msg,"M4DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    30) strcat(msg,"M4P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    31) strcat(msg,"M5DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    32) strcat(msg,"M5P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    33) strcat(msg,"M6DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    34) strcat(msg,"M6P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    35) strcat(msg,"M7DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    36) strcat(msg,"M7P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    37) strcat(msg,"M8DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    38) strcat(msg,"M8P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    39) strcat(msg,"M9DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    40) strcat(msg,"M9P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    41) strcat(msg,"M10DB   ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    42) strcat(msg,"M10P5DB ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    43) strcat(msg,"M11DB   ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    44) strcat(msg,"M11P5DB ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    45) strcat(msg,"M12DB   ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    46) strcat(msg,"M12P5DB ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    47) strcat(msg,"M13DB   ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    48) strcat(msg,"M13P5DB ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    49) strcat(msg,"M14DB   ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    50) strcat(msg,"M14P5DB ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    51) strcat(msg,"M15DB   ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    52) strcat(msg,"M15P5DB ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    53) strcat(msg,"M16DB   ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    54) strcat(msg,"M16P5DB ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    55) strcat(msg,"M17DB   ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    56) strcat(msg,"M17P5DB ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    57) strcat(msg,"M18DB   ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    58) strcat(msg,"M18P5DB ");
      else                                           sprintf(msg,"%s%d", msg, prop->dtv_rf_top.dtv_rf_top);
     break;
    #endif /*     Si2177_DTV_RF_TOP_PROP */
    #ifdef        Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP_CODE:
      sprintf(msg,"DTV_RSQ_RSSI_THRESHOLD");
       strcat(msg,separator); strcat(msg,"-LO "); sprintf(msg,"%s%d", msg, prop->dtv_rsq_rssi_threshold.lo);
       strcat(msg,separator); strcat(msg,"-HI "); sprintf(msg,"%s%d", msg, prop->dtv_rsq_rssi_threshold.hi);
     break;
    #endif /*     Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2177_DTV_WB_AGC_SPEED_PROP
     case         Si2177_DTV_WB_AGC_SPEED_PROP_CODE:
      sprintf(msg,"%s","DTV_WB_AGC_SPEED");
       strcat(msg,separator); strcat(msg,"-ATTACK ");
           if  (prop->dtv_wb_agc_speed.attack ==     0) strcat(msg,"AUTO ");
      else                                             sprintf(msg,"%s%d", msg,prop->dtv_wb_agc_speed.attack);
       strcat(msg,separator); strcat(msg,"-DECAY ");
           if  (prop->dtv_wb_agc_speed.decay  ==     0) strcat(msg,"AUTO ");
      else                                             sprintf(msg,"%s%d", msg,prop->dtv_wb_agc_speed.decay);
     break;
    #endif /*     Si2177_DTV_WB_AGC_SPEED_PROP */
    #ifdef        Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP
     case         Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP_CODE:
      sprintf(msg,"DTV_ZIF_DC_CANCELLER_BW");
       strcat(msg,separator); strcat(msg,"-BANDWIDTH ");
           if  (prop->dtv_zif_dc_canceller_bw.bandwidth ==     0) strcat(msg,"4_Hz      ");
      else if  (prop->dtv_zif_dc_canceller_bw.bandwidth ==     1) strcat(msg,"8_Hz      ");
      else if  (prop->dtv_zif_dc_canceller_bw.bandwidth ==     2) strcat(msg,"15_Hz     ");
      else if  (prop->dtv_zif_dc_canceller_bw.bandwidth ==     3) strcat(msg,"30_Hz     ");
      else if  (prop->dtv_zif_dc_canceller_bw.bandwidth ==     4) strcat(msg,"61_Hz     ");
      else if  (prop->dtv_zif_dc_canceller_bw.bandwidth ==     5) strcat(msg,"121_Hz    ");
      else if  (prop->dtv_zif_dc_canceller_bw.bandwidth ==     6) strcat(msg,"243_Hz    ");
      else if  (prop->dtv_zif_dc_canceller_bw.bandwidth ==     7) strcat(msg,"486_Hz    ");
      else if  (prop->dtv_zif_dc_canceller_bw.bandwidth ==     8) strcat(msg,"972_Hz    ");
      else if  (prop->dtv_zif_dc_canceller_bw.bandwidth ==     9) strcat(msg,"1943_Hz   ");
      else if  (prop->dtv_zif_dc_canceller_bw.bandwidth ==    10) strcat(msg,"3888_Hz   ");
      else if  (prop->dtv_zif_dc_canceller_bw.bandwidth ==    11) strcat(msg,"7779_Hz   ");
      else if  (prop->dtv_zif_dc_canceller_bw.bandwidth ==    12) strcat(msg,"15573_Hz  ");
      else if  (prop->dtv_zif_dc_canceller_bw.bandwidth ==    13) strcat(msg,"31207_Hz  ");
      else if  (prop->dtv_zif_dc_canceller_bw.bandwidth ==    14) strcat(msg,"62658_Hz  ");
      else if  (prop->dtv_zif_dc_canceller_bw.bandwidth ==    15) strcat(msg,"126303_Hz ");
      else if  (prop->dtv_zif_dc_canceller_bw.bandwidth ==    16) strcat(msg,"DEFAULT   ");
      else                                                       sprintf(msg,"%s%d", msg, prop->dtv_zif_dc_canceller_bw.bandwidth);
     break;
    #endif /*     Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP */
    #ifdef        Si2177_MASTER_IEN_PROP
     case         Si2177_MASTER_IEN_PROP_CODE:
      sprintf(msg,"MASTER_IEN");
       strcat(msg,separator); strcat(msg,"-TUNIEN ");
           if  (prop->master_ien.tunien ==     0) strcat(msg,"OFF ");
      else if  (prop->master_ien.tunien ==     1) strcat(msg,"ON  ");
      else                                       sprintf(msg,"%s%d", msg, prop->master_ien.tunien);
       strcat(msg,separator); strcat(msg,"-ATVIEN ");
           if  (prop->master_ien.atvien ==     0) strcat(msg,"OFF ");
      else if  (prop->master_ien.atvien ==     1) strcat(msg,"ON  ");
      else                                       sprintf(msg,"%s%d", msg, prop->master_ien.atvien);
       strcat(msg,separator); strcat(msg,"-DTVIEN ");
           if  (prop->master_ien.dtvien ==     0) strcat(msg,"OFF ");
      else if  (prop->master_ien.dtvien ==     1) strcat(msg,"ON  ");
      else                                       sprintf(msg,"%s%d", msg, prop->master_ien.dtvien);
       strcat(msg,separator); strcat(msg,"-ERRIEN ");
           if  (prop->master_ien.errien ==     0) strcat(msg,"OFF ");
      else if  (prop->master_ien.errien ==     1) strcat(msg,"ON  ");
      else                                       sprintf(msg,"%s%d", msg, prop->master_ien.errien);
       strcat(msg,separator); strcat(msg,"-CTSIEN ");
           if  (prop->master_ien.ctsien ==     0) strcat(msg,"OFF ");
      else if  (prop->master_ien.ctsien ==     1) strcat(msg,"ON  ");
      else                                       sprintf(msg,"%s%d", msg, prop->master_ien.ctsien);
     break;
    #endif /*     Si2177_MASTER_IEN_PROP */
    #ifdef        Si2177_TUNER_BLOCKED_VCO_PROP
     case         Si2177_TUNER_BLOCKED_VCO_PROP_CODE:
      sprintf(msg,"TUNER_BLOCKED_VCO");
       strcat(msg,separator); strcat(msg,"-VCO_CODE "); sprintf(msg,"%s%d", msg, prop->tuner_blocked_vco.vco_code);
     break;
    #endif /*     Si2177_TUNER_BLOCKED_VCO_PROP */
    #ifdef        Si2177_TUNER_IEN_PROP
     case         Si2177_TUNER_IEN_PROP_CODE:
      sprintf(msg,"TUNER_IEN");
       strcat(msg,separator); strcat(msg,"-TCIEN ");
           if  (prop->tuner_ien.tcien    ==     0) strcat(msg,"DISABLE ");
      else if  (prop->tuner_ien.tcien    ==     1) strcat(msg,"ENABLE  ");
      else                                        sprintf(msg,"%s%d", msg, prop->tuner_ien.tcien);
       strcat(msg,separator); strcat(msg,"-RSSILIEN ");
           if  (prop->tuner_ien.rssilien ==     0) strcat(msg,"DISABLE ");
      else if  (prop->tuner_ien.rssilien ==     1) strcat(msg,"ENABLE  ");
      else                                        sprintf(msg,"%s%d", msg, prop->tuner_ien.rssilien);
       strcat(msg,separator); strcat(msg,"-RSSIHIEN ");
           if  (prop->tuner_ien.rssihien ==     0) strcat(msg,"DISABLE ");
      else if  (prop->tuner_ien.rssihien ==     1) strcat(msg,"ENABLE  ");
      else                                        sprintf(msg,"%s%d", msg, prop->tuner_ien.rssihien);
     break;
    #endif /*     Si2177_TUNER_IEN_PROP */
    #ifdef        Si2177_TUNER_INT_SENSE_PROP
     case         Si2177_TUNER_INT_SENSE_PROP_CODE:
      sprintf(msg,"TUNER_INT_SENSE");
       strcat(msg,separator); strcat(msg,"-TCNEGEN ");
           if  (prop->tuner_int_sense.tcnegen    ==     0) strcat(msg,"DISABLE ");
      else if  (prop->tuner_int_sense.tcnegen    ==     1) strcat(msg,"ENABLE  ");
      else                                                sprintf(msg,"%s%d", msg, prop->tuner_int_sense.tcnegen);
       strcat(msg,separator); strcat(msg,"-RSSILNEGEN ");
           if  (prop->tuner_int_sense.rssilnegen ==     0) strcat(msg,"DISABLE ");
      else if  (prop->tuner_int_sense.rssilnegen ==     1) strcat(msg,"ENABLE  ");
      else                                                sprintf(msg,"%s%d", msg, prop->tuner_int_sense.rssilnegen);
       strcat(msg,separator); strcat(msg,"-RSSIHNEGEN ");
           if  (prop->tuner_int_sense.rssihnegen ==     0) strcat(msg,"DISABLE ");
      else if  (prop->tuner_int_sense.rssihnegen ==     1) strcat(msg,"ENABLE  ");
      else                                                sprintf(msg,"%s%d", msg, prop->tuner_int_sense.rssihnegen);
       strcat(msg,separator); strcat(msg,"-TCPOSEN ");
           if  (prop->tuner_int_sense.tcposen    ==     0) strcat(msg,"DISABLE ");
      else if  (prop->tuner_int_sense.tcposen    ==     1) strcat(msg,"ENABLE  ");
      else                                                sprintf(msg,"%s%d", msg, prop->tuner_int_sense.tcposen);
       strcat(msg,separator); strcat(msg,"-RSSILPOSEN ");
           if  (prop->tuner_int_sense.rssilposen ==     0) strcat(msg,"DISABLE ");
      else if  (prop->tuner_int_sense.rssilposen ==     1) strcat(msg,"ENABLE  ");
      else                                                sprintf(msg,"%s%d", msg, prop->tuner_int_sense.rssilposen);
       strcat(msg,separator); strcat(msg,"-RSSIHPOSEN ");
           if  (prop->tuner_int_sense.rssihposen ==     0) strcat(msg,"DISABLE ");
      else if  (prop->tuner_int_sense.rssihposen ==     1) strcat(msg,"ENABLE  ");
      else                                                sprintf(msg,"%s%d", msg, prop->tuner_int_sense.rssihposen);
     break;
    #endif /*     Si2177_TUNER_INT_SENSE_PROP */
    #ifdef        Si2177_TUNER_LO_INJECTION_PROP
     case         Si2177_TUNER_LO_INJECTION_PROP_CODE:
      sprintf(msg,"TUNER_LO_INJECTION");
       strcat(msg,separator); strcat(msg,"-BAND_1 ");
           if  (prop->tuner_lo_injection.band_1 ==     0) strcat(msg,"LOW_SIDE  ");
      else if  (prop->tuner_lo_injection.band_1 ==     1) strcat(msg,"HIGH_SIDE ");
      else                                               sprintf(msg,"%s%d", msg, prop->tuner_lo_injection.band_1);
       strcat(msg,separator); strcat(msg,"-BAND_2 ");
           if  (prop->tuner_lo_injection.band_2 ==     0) strcat(msg,"LOW_SIDE  ");
      else if  (prop->tuner_lo_injection.band_2 ==     1) strcat(msg,"HIGH_SIDE ");
      else                                               sprintf(msg,"%s%d", msg, prop->tuner_lo_injection.band_2);
       strcat(msg,separator); strcat(msg,"-BAND_3 ");
           if  (prop->tuner_lo_injection.band_3 ==     0) strcat(msg,"LOW_SIDE  ");
      else if  (prop->tuner_lo_injection.band_3 ==     1) strcat(msg,"HIGH_SIDE ");
      else                                               sprintf(msg,"%s%d", msg, prop->tuner_lo_injection.band_3);
     break;
    #endif /*     Si2177_TUNER_LO_INJECTION_PROP */
    #ifdef        Si2177_TUNER_RETURN_LOSS_PROP
     case         Si2177_TUNER_RETURN_LOSS_PROP_CODE:
      sprintf(msg,"TUNER_RETURN_LOSS");
       strcat(msg,separator); strcat(msg,"-CONFIG ");
           if  (prop->tuner_return_loss.config ==     3) strcat(msg,"3   ");
      else if  (prop->tuner_return_loss.config ==     7) strcat(msg,"7   ");
      else if  (prop->tuner_return_loss.config ==    11) strcat(msg,"11  ");
      else if  (prop->tuner_return_loss.config ==    15) strcat(msg,"15  ");
      else if  (prop->tuner_return_loss.config ==    19) strcat(msg,"19  ");
      else if  (prop->tuner_return_loss.config ==    23) strcat(msg,"23  ");
      else if  (prop->tuner_return_loss.config ==    27) strcat(msg,"27  ");
      else if  (prop->tuner_return_loss.config ==    31) strcat(msg,"31  ");
      else if  (prop->tuner_return_loss.config ==    35) strcat(msg,"35  ");
      else if  (prop->tuner_return_loss.config ==    39) strcat(msg,"39  ");
      else if  (prop->tuner_return_loss.config ==    43) strcat(msg,"43  ");
      else if  (prop->tuner_return_loss.config ==    47) strcat(msg,"47  ");
      else if  (prop->tuner_return_loss.config ==    51) strcat(msg,"51  ");
      else if  (prop->tuner_return_loss.config ==    59) strcat(msg,"59  ");
      else if  (prop->tuner_return_loss.config ==    67) strcat(msg,"67  ");
      else if  (prop->tuner_return_loss.config ==    75) strcat(msg,"75  ");
      else if  (prop->tuner_return_loss.config ==    83) strcat(msg,"83  ");
      else if  (prop->tuner_return_loss.config ==    91) strcat(msg,"91  ");
      else if  (prop->tuner_return_loss.config ==   103) strcat(msg,"103 ");
      else if  (prop->tuner_return_loss.config ==   115) strcat(msg,"115 ");
      else if  (prop->tuner_return_loss.config ==   127) strcat(msg,"127 ");
      else                                              sprintf(msg,"%s%d", msg, prop->tuner_return_loss.config);
       strcat(msg,separator); strcat(msg,"-MODE ");
           if  (prop->tuner_return_loss.mode   ==     0) strcat(msg,"TERRESTRIAL ");
      else if  (prop->tuner_return_loss.mode   ==     1) strcat(msg,"CABLE       ");
      else                                              sprintf(msg,"%s%d", msg, prop->tuner_return_loss.mode);
     break;
    #endif /*     Si2177_TUNER_RETURN_LOSS_PROP */
    #ifdef        Si2177_XOUT_PROP
     case         Si2177_XOUT_PROP_CODE:
      sprintf(msg,"XOUT");
       strcat(msg,separator); strcat(msg,"-AMP ");
           if  (prop->xout.amp ==     0) strcat(msg,"HIGH ");
      else if  (prop->xout.amp ==     1) strcat(msg,"LOW  ");
      else                              sprintf(msg,"%s%d", msg, prop->xout.amp);
     break;
    #endif /*     Si2177_XOUT_PROP */
     default : sprintf(msg,"Unknown property code '0x%06x'\n", prop_code); return ERROR_Si2177_UNKNOWN_PROPERTY; break;
  }
  return NO_Si2177_ERROR;
}
/***********************************************************************************************************************
  Si2177_L1_FillPropertyStringText function
  Use:        property text retrieval function
              Used to retrieve the property text for a selected property.
  Parameter: *api      the Si2177 context
  Parameter: prop_code the property Id (used to know which property to use)
  Parameter: separator the string to use between fields (often either a blank or a newline character)
  Parameter: msg       the string used to store the resulting string (usually declared with a size of 1000 bytes)
  Returns:    NO_Si2177_ERROR if successful.
 ***********************************************************************************************************************/
void          Si2177_L1_FillPropertyStringText(L1_Si2177_Context *api, unsigned int prop_code, const char *separator, char *msg) {
  Si2177_L1_PropertyText (api->prop, prop_code, separator, msg);
}
/***********************************************************************************************************************
  Si2177_L1_GetPropertyString function
  Use:        current property text retrieval function
              Used to retrieve the property value from the hardware then retrieve the corresponding property text.
  Parameter: *api      the Si2177 context
  Parameter: prop_code the property Id (used to know which property to use)
  Parameter: separator the string to use between fields (often either a blank or a newline character)
  Parameter: msg       the string used to store the resulting string (usually declared with a size of 1000 bytes)
  Returns:    NO_Si2177_ERROR if successful.
 ***********************************************************************************************************************/
unsigned char Si2177_L1_GetPropertyString     (L1_Si2177_Context *api, unsigned int prop_code, const char *separator, char *msg) {
    int res;
    res = Si2177_L1_GetProperty2(api,prop_code);
    if (res!=NO_Si2177_ERROR) { sprintf(msg, "%s",Si2177_L1_API_ERROR_TEXT(res)); return res; }
    Si2177_L1_PropertyText(api->prop, prop_code, separator, msg);
    return NO_Si2177_ERROR;
}
#endif /* Si2177_GET_PROPERTY_STRING */








