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


   API properties strings definitions
   FILE: Si2177_Properties_Strings.h
   Supported IC : Si2177
   Compiled for ROM 50 firmware 3_1_build_3
   Revision: 0.1
   Date: June 30 2015
   Tag: ROM50_3_1_build_3_V0.1
**************************************************************************************/
#ifndef   _Si2177_PROPERTIES_STRINGS_H_
#define   _Si2177_PROPERTIES_STRINGS_H_

#ifdef Si2177_COMMAND_LINE_APPLICATION

extern Si2177_PropObj Si2177_prop;

typedef enum   {
  Si2177_UNSIGNED_CHAR,
  Si2177_SIGNED_CHAR,
  Si2177_UNSIGNED_INT,
  Si2177_SIGNED_INT
} Si2177_datatypeEnum;

typedef struct {
  const char *name;
  int         value;
} Si2177_optionStruct;

typedef enum {
  Si2177_ATV,
  Si2177_COMMON,
  Si2177_DTV,
  Si2177_TUNER
} Si2177_featureEnum;

typedef struct {
  const char          *name;
  Si2177_datatypeEnum  datatype;
  void                *pField;
  int                  nbOptions;
  Si2177_optionStruct *option;
} Si2177_fieldDicoStruct;

typedef struct {
  Si2177_featureEnum      feature;
  const char             *name;
  int                     nbFields;
  Si2177_fieldDicoStruct *field;
  unsigned int            propertyCode;
} Si2177_propertyInfoStruct;


extern Si2177_optionStruct    Si2177_ATV_AFC_RANGE_PROP_RANGE_KHZ[];
extern Si2177_fieldDicoStruct Si2177_ATV_AFC_RANGE_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_AF_OUT_PROP_VOLUME[];
extern Si2177_optionStruct    Si2177_ATV_AF_OUT_PROP_SOFT_MUTE[];
extern Si2177_fieldDicoStruct Si2177_ATV_AF_OUT_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2177_fieldDicoStruct Si2177_ATV_AGC_SPEED_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED[];
extern Si2177_optionStruct    Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD[];
extern Si2177_fieldDicoStruct Si2177_ATV_AGC_SPEED_LOW_RSSI_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_ARTIFICIAL_SNOW_PROP_GAIN[];
extern Si2177_optionStruct    Si2177_ATV_ARTIFICIAL_SNOW_PROP_SOUND[];
extern Si2177_optionStruct    Si2177_ATV_ARTIFICIAL_SNOW_PROP_PERIOD[];
extern Si2177_optionStruct    Si2177_ATV_ARTIFICIAL_SNOW_PROP_OFFSET[];
extern Si2177_fieldDicoStruct Si2177_ATV_ARTIFICIAL_SNOW_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_AUDIO_MODE_PROP_AUDIO_SYS[];
extern Si2177_optionStruct    Si2177_ATV_AUDIO_MODE_PROP_DEMOD_MODE[];
extern Si2177_optionStruct    Si2177_ATV_AUDIO_MODE_PROP_CHAN_BW[];
extern Si2177_fieldDicoStruct Si2177_ATV_AUDIO_MODE_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE[];
extern Si2177_fieldDicoStruct Si2177_ATV_CONFIG_IF_PORT_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_CVBS_OUT_PROP_OFFSET[];
extern Si2177_optionStruct    Si2177_ATV_CVBS_OUT_PROP_AMP[];
extern Si2177_fieldDicoStruct Si2177_ATV_CVBS_OUT_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_CVBS_OUT_FINE_PROP_OFFSET[];
extern Si2177_optionStruct    Si2177_ATV_CVBS_OUT_FINE_PROP_AMP[];
extern Si2177_fieldDicoStruct Si2177_ATV_CVBS_OUT_FINE_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_HSYNC_OUT_PROP_GPIO_SEL[];
extern Si2177_optionStruct    Si2177_ATV_HSYNC_OUT_PROP_WIDTH[];
extern Si2177_optionStruct    Si2177_ATV_HSYNC_OUT_PROP_OFFSET[];
extern Si2177_fieldDicoStruct Si2177_ATV_HSYNC_OUT_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_IEN_PROP_CHLIEN[];
extern Si2177_optionStruct    Si2177_ATV_IEN_PROP_PCLIEN[];
extern Si2177_optionStruct    Si2177_ATV_IEN_PROP_DLIEN[];
extern Si2177_optionStruct    Si2177_ATV_IEN_PROP_SNRLIEN[];
extern Si2177_optionStruct    Si2177_ATV_IEN_PROP_SNRHIEN[];
extern Si2177_fieldDicoStruct Si2177_ATV_IEN_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_INT_SENSE_PROP_CHLNEGEN[];
extern Si2177_optionStruct    Si2177_ATV_INT_SENSE_PROP_PCLNEGEN[];
extern Si2177_optionStruct    Si2177_ATV_INT_SENSE_PROP_DLNEGEN[];
extern Si2177_optionStruct    Si2177_ATV_INT_SENSE_PROP_SNRLNEGEN[];
extern Si2177_optionStruct    Si2177_ATV_INT_SENSE_PROP_SNRHNEGEN[];
extern Si2177_optionStruct    Si2177_ATV_INT_SENSE_PROP_CHLPOSEN[];
extern Si2177_optionStruct    Si2177_ATV_INT_SENSE_PROP_PCLPOSEN[];
extern Si2177_optionStruct    Si2177_ATV_INT_SENSE_PROP_DLPOSEN[];
extern Si2177_optionStruct    Si2177_ATV_INT_SENSE_PROP_SNRLPOSEN[];
extern Si2177_optionStruct    Si2177_ATV_INT_SENSE_PROP_SNRHPOSEN[];
extern Si2177_fieldDicoStruct Si2177_ATV_INT_SENSE_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_PGA_TARGET_PROP_PGA_TARGET[];
extern Si2177_optionStruct    Si2177_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE[];
extern Si2177_fieldDicoStruct Si2177_ATV_PGA_TARGET_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_RF_TOP_PROP_ATV_RF_TOP[];
extern Si2177_fieldDicoStruct Si2177_ATV_RF_TOP_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP_LO[];
extern Si2177_optionStruct    Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP_HI[];
extern Si2177_fieldDicoStruct Si2177_ATV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_RSQ_SNR_THRESHOLD_PROP_LO[];
extern Si2177_optionStruct    Si2177_ATV_RSQ_SNR_THRESHOLD_PROP_HI[];
extern Si2177_fieldDicoStruct Si2177_ATV_RSQ_SNR_THRESHOLD_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_SIF_OUT_PROP_OFFSET[];
extern Si2177_optionStruct    Si2177_ATV_SIF_OUT_PROP_AMP[];
extern Si2177_fieldDicoStruct Si2177_ATV_SIF_OUT_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN[];
extern Si2177_optionStruct    Si2177_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN[];
extern Si2177_fieldDicoStruct Si2177_ATV_SOUND_AGC_LIMIT_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L[];
extern Si2177_optionStruct    Si2177_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS[];
extern Si2177_fieldDicoStruct Si2177_ATV_SOUND_AGC_SPEED_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_VIDEO_EQUALIZER_PROP_SLOPE[];
extern Si2177_fieldDicoStruct Si2177_ATV_VIDEO_EQUALIZER_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_VIDEO_MODE_PROP_VIDEO_SYS[];
extern Si2177_optionStruct    Si2177_ATV_VIDEO_MODE_PROP_COLOR[];
extern Si2177_optionStruct    Si2177_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL[];
extern Si2177_fieldDicoStruct Si2177_ATV_VIDEO_MODE_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP[];
extern Si2177_fieldDicoStruct Si2177_ATV_VSNR_CAP_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_CRYSTAL_TRIM_PROP_XO_CAP[];
extern Si2177_fieldDicoStruct Si2177_CRYSTAL_TRIM_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_AGC_AUTO_FREEZE_PROP_THLD[];
extern Si2177_optionStruct    Si2177_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT[];
extern Si2177_fieldDicoStruct Si2177_DTV_AGC_AUTO_FREEZE_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_AGC_FREEZE_INPUT_PROP_LEVEL[];
extern Si2177_optionStruct    Si2177_DTV_AGC_FREEZE_INPUT_PROP_PIN[];
extern Si2177_fieldDicoStruct Si2177_DTV_AGC_FREEZE_INPUT_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2177_optionStruct    Si2177_DTV_AGC_SPEED_PROP_AGC_DECIM[];
extern Si2177_fieldDicoStruct Si2177_DTV_AGC_SPEED_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE[];
extern Si2177_optionStruct    Si2177_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE[];
extern Si2177_fieldDicoStruct Si2177_DTV_CONFIG_IF_PORT_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_EXT_AGC_PROP_MIN_10MV[];
extern Si2177_optionStruct    Si2177_DTV_EXT_AGC_PROP_MAX_10MV[];
extern Si2177_fieldDicoStruct Si2177_DTV_EXT_AGC_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_IEN_PROP_CHLIEN[];
extern Si2177_fieldDicoStruct Si2177_DTV_IEN_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_IF_AGC_SPEED_PROP_ATTACK[];
extern Si2177_optionStruct    Si2177_DTV_IF_AGC_SPEED_PROP_DECAY[];
extern Si2177_fieldDicoStruct Si2177_DTV_IF_AGC_SPEED_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2177_optionStruct    Si2177_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM[];
extern Si2177_fieldDicoStruct Si2177_DTV_INITIAL_AGC_SPEED_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD[];
extern Si2177_fieldDicoStruct Si2177_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_INTERNAL_ZIF_PROP_ATSC[];
extern Si2177_optionStruct    Si2177_DTV_INTERNAL_ZIF_PROP_QAM_US[];
extern Si2177_optionStruct    Si2177_DTV_INTERNAL_ZIF_PROP_DVBT[];
extern Si2177_optionStruct    Si2177_DTV_INTERNAL_ZIF_PROP_DVBC[];
extern Si2177_optionStruct    Si2177_DTV_INTERNAL_ZIF_PROP_ISDBT[];
extern Si2177_optionStruct    Si2177_DTV_INTERNAL_ZIF_PROP_ISDBC[];
extern Si2177_optionStruct    Si2177_DTV_INTERNAL_ZIF_PROP_DTMB[];
extern Si2177_fieldDicoStruct Si2177_DTV_INTERNAL_ZIF_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_INT_SENSE_PROP_CHLNEGEN[];
extern Si2177_optionStruct    Si2177_DTV_INT_SENSE_PROP_CHLPOSEN[];
extern Si2177_fieldDicoStruct Si2177_DTV_INT_SENSE_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_LIF_FREQ_PROP_OFFSET[];
extern Si2177_fieldDicoStruct Si2177_DTV_LIF_FREQ_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_LIF_OUT_PROP_OFFSET[];
extern Si2177_optionStruct    Si2177_DTV_LIF_OUT_PROP_AMP[];
extern Si2177_fieldDicoStruct Si2177_DTV_LIF_OUT_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_MODE_PROP_BW[];
extern Si2177_optionStruct    Si2177_DTV_MODE_PROP_MODULATION[];
extern Si2177_optionStruct    Si2177_DTV_MODE_PROP_INVERT_SPECTRUM[];
extern Si2177_fieldDicoStruct Si2177_DTV_MODE_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_PGA_LIMITS_PROP_MIN[];
extern Si2177_optionStruct    Si2177_DTV_PGA_LIMITS_PROP_MAX[];
extern Si2177_fieldDicoStruct Si2177_DTV_PGA_LIMITS_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_PGA_TARGET_PROP_PGA_TARGET[];
extern Si2177_optionStruct    Si2177_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE[];
extern Si2177_fieldDicoStruct Si2177_DTV_PGA_TARGET_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_RF_AGC_SPEED_PROP_ATTACK[];
extern Si2177_optionStruct    Si2177_DTV_RF_AGC_SPEED_PROP_DECAY[];
extern Si2177_fieldDicoStruct Si2177_DTV_RF_AGC_SPEED_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_RF_TOP_PROP_DTV_RF_TOP[];
extern Si2177_fieldDicoStruct Si2177_DTV_RF_TOP_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP_LO[];
extern Si2177_optionStruct    Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP_HI[];
extern Si2177_fieldDicoStruct Si2177_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_WB_AGC_SPEED_PROP_ATTACK[];
extern Si2177_optionStruct    Si2177_DTV_WB_AGC_SPEED_PROP_DECAY[];
extern Si2177_fieldDicoStruct Si2177_DTV_WB_AGC_SPEED_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH[];
extern Si2177_fieldDicoStruct Si2177_DTV_ZIF_DC_CANCELLER_BW_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_MASTER_IEN_PROP_TUNIEN[];
extern Si2177_optionStruct    Si2177_MASTER_IEN_PROP_ATVIEN[];
extern Si2177_optionStruct    Si2177_MASTER_IEN_PROP_DTVIEN[];
extern Si2177_optionStruct    Si2177_MASTER_IEN_PROP_ERRIEN[];
extern Si2177_optionStruct    Si2177_MASTER_IEN_PROP_CTSIEN[];
extern Si2177_fieldDicoStruct Si2177_MASTER_IEN_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_TUNER_BLOCKED_VCO_PROP_VCO_CODE[];
extern Si2177_fieldDicoStruct Si2177_TUNER_BLOCKED_VCO_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_TUNER_IEN_PROP_TCIEN[];
extern Si2177_optionStruct    Si2177_TUNER_IEN_PROP_RSSILIEN[];
extern Si2177_optionStruct    Si2177_TUNER_IEN_PROP_RSSIHIEN[];
extern Si2177_fieldDicoStruct Si2177_TUNER_IEN_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_TUNER_INT_SENSE_PROP_TCNEGEN[];
extern Si2177_optionStruct    Si2177_TUNER_INT_SENSE_PROP_RSSILNEGEN[];
extern Si2177_optionStruct    Si2177_TUNER_INT_SENSE_PROP_RSSIHNEGEN[];
extern Si2177_optionStruct    Si2177_TUNER_INT_SENSE_PROP_TCPOSEN[];
extern Si2177_optionStruct    Si2177_TUNER_INT_SENSE_PROP_RSSILPOSEN[];
extern Si2177_optionStruct    Si2177_TUNER_INT_SENSE_PROP_RSSIHPOSEN[];
extern Si2177_fieldDicoStruct Si2177_TUNER_INT_SENSE_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_TUNER_LO_INJECTION_PROP_BAND_1[];
extern Si2177_optionStruct    Si2177_TUNER_LO_INJECTION_PROP_BAND_2[];
extern Si2177_optionStruct    Si2177_TUNER_LO_INJECTION_PROP_BAND_3[];
extern Si2177_fieldDicoStruct Si2177_TUNER_LO_INJECTION_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_TUNER_RETURN_LOSS_PROP_CONFIG[];
extern Si2177_optionStruct    Si2177_TUNER_RETURN_LOSS_PROP_MODE[];
extern Si2177_fieldDicoStruct Si2177_TUNER_RETURN_LOSS_PROP_FIELDS[];

extern Si2177_optionStruct    Si2177_XOUT_PROP_AMP[];
extern Si2177_fieldDicoStruct Si2177_XOUT_PROP_FIELDS[];

extern Si2177_propertyInfoStruct Si2177_propertyDictionary[];

int   Si2177_PropertyNames       (L1_Si2177_Context *api, char *msg);
int   Si2177_PropertyIndex       (L1_Si2177_Context *api, const char *property);
int   Si2177_PropertyFields      (L1_Si2177_Context *api, int propIndex, char *msg);
int   Si2177_PropertyFieldIndex  (L1_Si2177_Context *api, int propIndex, char *field);
int   Si2177_PropertyFieldEnums  (L1_Si2177_Context *api, int propIndex, int fieldIndex, char *msg);
int   Si2177_GetValueFromEntry   (L1_Si2177_Context *api, Si2177_fieldDicoStruct field, char *entry, int *value);
char *Si2177_GetEnumFromValue    (L1_Si2177_Context *api, Si2177_fieldDicoStruct field, int iValue);
char *Si2177_GetEnumFromField    (L1_Si2177_Context *api, Si2177_fieldDicoStruct field);
int   Si2177_SetFieldFromEntry   (L1_Si2177_Context *api, Si2177_fieldDicoStruct field, char *entry);
void  Si2177_showProperty        (L1_Si2177_Context *api, int propertyIndex);
void  Si2177_showPropertyNamed   (L1_Si2177_Context *api, char *property);
int   Si2177_showProperties      (L1_Si2177_Context *api, Si2177_featureEnum feature);
void  Si2177_setupProperty       (L1_Si2177_Context *api, int propIndex);
int   Si2177_setupProperties     (L1_Si2177_Context *api, Si2177_featureEnum feature);

#endif /* Si2177_COMMAND_LINE_APPLICATION */


int  Si2177_setupATVProperties   (L1_Si2177_Context *api);
int  Si2177_setupCOMMONProperties(L1_Si2177_Context *api);
int  Si2177_setupDTVProperties   (L1_Si2177_Context *api);
int  Si2177_setupTUNERProperties (L1_Si2177_Context *api);
int  Si2177_setupAllProperties   (L1_Si2177_Context *api);

#endif /* _Si2177_PROPERTIES_STRINGS_H_ */







