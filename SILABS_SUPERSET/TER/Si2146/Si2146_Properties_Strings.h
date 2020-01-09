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
   API properties strings definitions
   FILE: Si2146_Properties_Strings.h
   Supported IC : Si2146
   Compiled for ROM 11 firmware 1_1_build_3
   Revision: 0.1
   Date: December 23 2011
   Tag: TAGNAME
**************************************************************************************/
#ifndef   _Si2146_PROPERTIES_STRINGS_H_
#define   _Si2146_PROPERTIES_STRINGS_H_

#ifdef Si2146_COMMAND_LINE_APPLICATION

extern Si2146_PropObj Si2146_prop;

typedef enum {
  Si2146_UNSIGNED_CHAR,
  Si2146_SIGNED_CHAR,
  Si2146_UNSIGNED_INT,
  Si2146_SIGNED_INT
} Si2146_datatypeEnum;

typedef struct {
  char *name;
  int   value;
} Si2146_optionStruct;

/* _properties_features_enum_insertion_start */
typedef enum {
  Si2146_COMMON,
  Si2146_DTV,
  Si2146_TUNER,
} Si2146_featureEnum;
/* _properties_features_enum_insertion_point */

typedef struct {
  char         *name;
  Si2146_datatypeEnum  datatype;
  void         *pField;
  int           nbOptions;
  Si2146_optionStruct *option;
} Si2146_fieldDicoStruct;

typedef struct {
  Si2146_featureEnum feature;
  char            *name;
  int              nbFields;
  Si2146_fieldDicoStruct *field;
  unsigned int    propertyCode;
} Si2146_propertyInfoStruct;

/* _properties_strings_extern_insertion_start */

extern Si2146_optionStruct    Si2146_ATV_AFC_RANGE_PROP_RANGE_KHZ[];
extern Si2146_fieldDicoStruct Si2146_ATV_AFC_RANGE_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_ATV_AF_OUT_PROP_VOLUME[];
extern Si2146_fieldDicoStruct Si2146_ATV_AF_OUT_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2146_fieldDicoStruct Si2146_ATV_AGC_SPEED_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_ATV_AUDIO_MODE_PROP_AUDIO_SYS[];
extern Si2146_optionStruct    Si2146_ATV_AUDIO_MODE_PROP_DEMOD_MODE[];
extern Si2146_optionStruct    Si2146_ATV_AUDIO_MODE_PROP_CHAN_BW[];
extern Si2146_fieldDicoStruct Si2146_ATV_AUDIO_MODE_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_ATV_CVBS_OUT_PROP_OFFSET[];
extern Si2146_optionStruct    Si2146_ATV_CVBS_OUT_PROP_AMP[];
extern Si2146_fieldDicoStruct Si2146_ATV_CVBS_OUT_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_ATV_CVBS_OUT_FINE_PROP_OFFSET[];
extern Si2146_optionStruct    Si2146_ATV_CVBS_OUT_FINE_PROP_AMP[];
extern Si2146_fieldDicoStruct Si2146_ATV_CVBS_OUT_FINE_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_ATV_IEN_PROP_CHLIEN[];
extern Si2146_optionStruct    Si2146_ATV_IEN_PROP_PCLIEN[];
extern Si2146_optionStruct    Si2146_ATV_IEN_PROP_DLIEN[];
extern Si2146_optionStruct    Si2146_ATV_IEN_PROP_SNRLIEN[];
extern Si2146_optionStruct    Si2146_ATV_IEN_PROP_SNRHIEN[];
extern Si2146_fieldDicoStruct Si2146_ATV_IEN_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_ATV_INT_SENSE_PROP_CHLNEGEN[];
extern Si2146_optionStruct    Si2146_ATV_INT_SENSE_PROP_PCLNEGEN[];
extern Si2146_optionStruct    Si2146_ATV_INT_SENSE_PROP_DLNEGEN[];
extern Si2146_optionStruct    Si2146_ATV_INT_SENSE_PROP_SNRLNEGEN[];
extern Si2146_optionStruct    Si2146_ATV_INT_SENSE_PROP_SNRHNEGEN[];
extern Si2146_optionStruct    Si2146_ATV_INT_SENSE_PROP_CHLPOSEN[];
extern Si2146_optionStruct    Si2146_ATV_INT_SENSE_PROP_PCLPOSEN[];
extern Si2146_optionStruct    Si2146_ATV_INT_SENSE_PROP_DLPOSEN[];
extern Si2146_optionStruct    Si2146_ATV_INT_SENSE_PROP_SNRLPOSEN[];
extern Si2146_optionStruct    Si2146_ATV_INT_SENSE_PROP_SNRHPOSEN[];
extern Si2146_fieldDicoStruct Si2146_ATV_INT_SENSE_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_ATV_RF_TOP_PROP_ATV_RF_TOP[];
extern Si2146_fieldDicoStruct Si2146_ATV_RF_TOP_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_LO[];
extern Si2146_optionStruct    Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_HI[];
extern Si2146_fieldDicoStruct Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_LO[];
extern Si2146_optionStruct    Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_HI[];
extern Si2146_fieldDicoStruct Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_ATV_SIF_OUT_PROP_OFFSET[];
extern Si2146_optionStruct    Si2146_ATV_SIF_OUT_PROP_AMP[];
extern Si2146_fieldDicoStruct Si2146_ATV_SIF_OUT_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN[];
extern Si2146_optionStruct    Si2146_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN[];
extern Si2146_fieldDicoStruct Si2146_ATV_SOUND_AGC_LIMIT_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L[];
extern Si2146_optionStruct    Si2146_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS[];
extern Si2146_fieldDicoStruct Si2146_ATV_SOUND_AGC_SPEED_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_ATV_VIDEO_EQUALIZER_PROP_SLOPE[];
extern Si2146_fieldDicoStruct Si2146_ATV_VIDEO_EQUALIZER_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_ATV_VIDEO_MODE_PROP_VIDEO_SYS[];
extern Si2146_optionStruct    Si2146_ATV_VIDEO_MODE_PROP_COLOR[];
extern Si2146_optionStruct    Si2146_ATV_VIDEO_MODE_PROP_TRANS[];
extern Si2146_optionStruct    Si2146_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM[];
extern Si2146_optionStruct    Si2146_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL[];
extern Si2146_fieldDicoStruct Si2146_ATV_VIDEO_MODE_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP[];
extern Si2146_fieldDicoStruct Si2146_ATV_VSNR_CAP_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_ATV_VSYNC_TRACKING_PROP_MIN_PULSES_TO_LOCK[];
extern Si2146_optionStruct    Si2146_ATV_VSYNC_TRACKING_PROP_MIN_FIELDS_TO_UNLOCK[];
extern Si2146_fieldDicoStruct Si2146_ATV_VSYNC_TRACKING_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_CRYSTAL_TRIM_PROP_XO_CAP[];
extern Si2146_fieldDicoStruct Si2146_CRYSTAL_TRIM_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_DTV_AGC_FREEZE_INPUT_PROP_LEVEL[];
extern Si2146_optionStruct    Si2146_DTV_AGC_FREEZE_INPUT_PROP_PIN[];
extern Si2146_fieldDicoStruct Si2146_DTV_AGC_FREEZE_INPUT_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2146_optionStruct    Si2146_DTV_AGC_SPEED_PROP_AGC_DECIM[];
extern Si2146_fieldDicoStruct Si2146_DTV_AGC_SPEED_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE[];
extern Si2146_optionStruct    Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE[];
extern Si2146_fieldDicoStruct Si2146_DTV_CONFIG_IF_PORT_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_DTV_EXT_AGC_PROP_MIN_10MV[];
extern Si2146_optionStruct    Si2146_DTV_EXT_AGC_PROP_MAX_10MV[];
extern Si2146_fieldDicoStruct Si2146_DTV_EXT_AGC_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_DTV_IEN_PROP_CHLIEN[];
extern Si2146_fieldDicoStruct Si2146_DTV_IEN_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2146_optionStruct    Si2146_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM[];
extern Si2146_fieldDicoStruct Si2146_DTV_INITIAL_AGC_SPEED_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD[];
extern Si2146_fieldDicoStruct Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_DTV_INT_SENSE_PROP_CHLNEGEN[];
extern Si2146_optionStruct    Si2146_DTV_INT_SENSE_PROP_CHLPOSEN[];
extern Si2146_fieldDicoStruct Si2146_DTV_INT_SENSE_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_DTV_LIF_FREQ_PROP_OFFSET[];
extern Si2146_fieldDicoStruct Si2146_DTV_LIF_FREQ_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_DTV_LIF_OUT_PROP_OFFSET[];
extern Si2146_optionStruct    Si2146_DTV_LIF_OUT_PROP_AMP[];
extern Si2146_fieldDicoStruct Si2146_DTV_LIF_OUT_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_DTV_MODE_PROP_BW[];
extern Si2146_optionStruct    Si2146_DTV_MODE_PROP_MODULATION[];
extern Si2146_optionStruct    Si2146_DTV_MODE_PROP_INVERT_SPECTRUM[];
extern Si2146_fieldDicoStruct Si2146_DTV_MODE_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP[];
extern Si2146_fieldDicoStruct Si2146_DTV_RF_TOP_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_LO[];
extern Si2146_optionStruct    Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_HI[];
extern Si2146_fieldDicoStruct Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_MASTER_IEN_PROP_TUNIEN[];
extern Si2146_optionStruct    Si2146_MASTER_IEN_PROP_ATVIEN[];
extern Si2146_optionStruct    Si2146_MASTER_IEN_PROP_DTVIEN[];
extern Si2146_optionStruct    Si2146_MASTER_IEN_PROP_ERRIEN[];
extern Si2146_optionStruct    Si2146_MASTER_IEN_PROP_CTSIEN[];
extern Si2146_fieldDicoStruct Si2146_MASTER_IEN_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_TUNER_BLOCKED_VCO_PROP_VCO_CODE[];
extern Si2146_fieldDicoStruct Si2146_TUNER_BLOCKED_VCO_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_TUNER_IEN_PROP_TCIEN[];
extern Si2146_optionStruct    Si2146_TUNER_IEN_PROP_RSSILIEN[];
extern Si2146_optionStruct    Si2146_TUNER_IEN_PROP_RSSIHIEN[];
extern Si2146_fieldDicoStruct Si2146_TUNER_IEN_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_TUNER_INT_SENSE_PROP_TCNEGEN[];
extern Si2146_optionStruct    Si2146_TUNER_INT_SENSE_PROP_RSSILNEGEN[];
extern Si2146_optionStruct    Si2146_TUNER_INT_SENSE_PROP_RSSIHNEGEN[];
extern Si2146_optionStruct    Si2146_TUNER_INT_SENSE_PROP_TCPOSEN[];
extern Si2146_optionStruct    Si2146_TUNER_INT_SENSE_PROP_RSSILPOSEN[];
extern Si2146_optionStruct    Si2146_TUNER_INT_SENSE_PROP_RSSIHPOSEN[];
extern Si2146_fieldDicoStruct Si2146_TUNER_INT_SENSE_PROP_FIELDS[];

extern Si2146_optionStruct    Si2146_TUNER_LO_INJECTION_PROP_BAND_1[];
extern Si2146_optionStruct    Si2146_TUNER_LO_INJECTION_PROP_BAND_2[];
extern Si2146_optionStruct    Si2146_TUNER_LO_INJECTION_PROP_BAND_3[];
extern Si2146_optionStruct    Si2146_TUNER_LO_INJECTION_PROP_BAND_4[];
extern Si2146_optionStruct    Si2146_TUNER_LO_INJECTION_PROP_BAND_5[];
extern Si2146_fieldDicoStruct Si2146_TUNER_LO_INJECTION_PROP_FIELDS[];

/* _properties_strings_extern_insertion_point */
extern Si2146_propertyInfoStruct Si2146_propertyDictionary[];

int   Si2146_PropertyNames              (L1_Si2146_Context *api, char *msg);
int   Si2146_PropertyIndex              (L1_Si2146_Context *api, char *property);
int   Si2146_PropertyFields             (L1_Si2146_Context *api, int propIndex, char *msg);
int   Si2146_PropertyFieldIndex         (L1_Si2146_Context *api, int propIndex, char *field);
int   Si2146_PropertyFieldEnums         (L1_Si2146_Context *api, int propIndex, int fieldIndex, char *msg);
int   Si2146_GetValueFromEntry   (L1_Si2146_Context *api, Si2146_fieldDicoStruct field, char *entry, int *value);
char *Si2146_GetEnumFromValue    (L1_Si2146_Context *api, Si2146_fieldDicoStruct field, int iValue);
char *Si2146_GetEnumFromField    (L1_Si2146_Context *api, Si2146_fieldDicoStruct field);
int   Si2146_SetFieldFromEntry   (L1_Si2146_Context *api, Si2146_fieldDicoStruct field, char *entry);
void  Si2146_showProperty               (L1_Si2146_Context *api, int propertyIndex);
void  Si2146_showPropertyNamed          (L1_Si2146_Context *api, char *property);
int   Si2146_showProperties             (L1_Si2146_Context *api, Si2146_featureEnum feature);
void  Si2146_setupProperty              (L1_Si2146_Context *api, int propIndex);
int   Si2146_setupProperties            (L1_Si2146_Context *api, Si2146_featureEnum feature);

#endif /* Si2146_COMMAND_LINE_APPLICATION */

/* _properties_strings_protos_insertion_start */

#ifdef    Si2146_COMMAND_LINE_APPLICATION
int  Si2146_showCOMMONProperties(L1_Si2146_Context *api);
int  Si2146_showDTVProperties   (L1_Si2146_Context *api);
int  Si2146_showTUNERProperties (L1_Si2146_Context *api);


int  Si2146_showAllProperties    (L1_Si2146_Context *api);
#endif /* Si2146_COMMAND_LINE_APPLICATION */
void Si2146_setupCOMMONDefaults         (L1_Si2146_Context *api);
void Si2146_setupDTVDefaults            (L1_Si2146_Context *api);
void Si2146_setupTUNERDefaults          (L1_Si2146_Context *api);

void Si2146_setupAllDefaults            (L1_Si2146_Context *api);

int Si2146_setupCOMMONProperties        (L1_Si2146_Context *api);
int Si2146_setupDTVProperties           (L1_Si2146_Context *api);
int Si2146_setupTUNERProperties         (L1_Si2146_Context *api);
int Si2146_setupAllProperties           (L1_Si2146_Context *api);

int Si2146_downloadCOMMONProperties     (L1_Si2146_Context *api);
int Si2146_downloadDTVProperties        (L1_Si2146_Context *api);
int Si2146_downloadTUNERProperties      (L1_Si2146_Context *api);
int Si2146_downloadAllProperties        (L1_Si2146_Context *api);
/* _properties_strings_protos_insertion_point */

#endif /* _Si2146_PROPERTIES_STRINGS_H_ */






