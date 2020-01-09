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
                  Silicon Laboratories Broadcast Si2156 Layer 1 API
   API properties strings definitions
   FILE: Si2156_Properties_Strings.h
   Supported IC : Si2156
   Compiled for ROM 13 firmware 3_1_build_9
   Revision: 0.3
   Date: December 22 2011
   Tag: TAGNAME
**************************************************************************************/
#ifndef   _Si2156_PROPERTIES_STRINGS_H_
#define   _Si2156_PROPERTIES_STRINGS_H_

#ifdef Si2156_COMMAND_LINE_APPLICATION

extern Si2156_PropObj Si2156_prop;

typedef enum   {
  Si2156_UNSIGNED_CHAR,
  Si2156_SIGNED_CHAR,
  Si2156_UNSIGNED_INT,
  Si2156_SIGNED_INT
} Si2156_datatypeEnum;

typedef struct {
  char *name;
  int   value;
} Si2156_optionStruct;

/* _properties_features_enum_insertion_start */
typedef enum {
  Si2156_ATV,
  Si2156_COMMON,
  Si2156_DTV,
  Si2156_TUNER
} Si2156_featureEnum;
/* _properties_features_enum_insertion_point */

typedef struct {
  char                *name;
  Si2156_datatypeEnum  datatype;
  void                *pField;
  int                  nbOptions;
  Si2156_optionStruct *option;
} Si2156_fieldDicoStruct;

typedef struct {
  Si2156_featureEnum      feature;
  char                   *name;
  int                     nbFields;
  Si2156_fieldDicoStruct *field;
  unsigned int            propertyCode;
} Si2156_propertyInfoStruct;

/* _properties_strings_extern_insertion_start */

extern Si2156_optionStruct    Si2156_ATV_AFC_RANGE_PROP_RANGE_KHZ[];
extern Si2156_fieldDicoStruct Si2156_ATV_AFC_RANGE_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_ATV_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2156_fieldDicoStruct Si2156_ATV_AGC_SPEED_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE[];
extern Si2156_optionStruct    Si2156_ATV_CONFIG_IF_PORT_PROP_ATV_AGC_SOURCE[];
extern Si2156_fieldDicoStruct Si2156_ATV_CONFIG_IF_PORT_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_ATV_EXT_AGC_PROP_MIN_10MV[];
extern Si2156_optionStruct    Si2156_ATV_EXT_AGC_PROP_MAX_10MV[];
extern Si2156_fieldDicoStruct Si2156_ATV_EXT_AGC_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_ATV_IEN_PROP_CHLIEN[];
extern Si2156_optionStruct    Si2156_ATV_IEN_PROP_PCLIEN[];
extern Si2156_fieldDicoStruct Si2156_ATV_IEN_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_ATV_INT_SENSE_PROP_CHLNEGEN[];
extern Si2156_optionStruct    Si2156_ATV_INT_SENSE_PROP_PCLNEGEN[];
extern Si2156_optionStruct    Si2156_ATV_INT_SENSE_PROP_CHLPOSEN[];
extern Si2156_optionStruct    Si2156_ATV_INT_SENSE_PROP_PCLPOSEN[];
extern Si2156_fieldDicoStruct Si2156_ATV_INT_SENSE_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_ATV_LIF_FREQ_PROP_OFFSET[];
extern Si2156_fieldDicoStruct Si2156_ATV_LIF_FREQ_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_ATV_LIF_OUT_PROP_OFFSET[];
extern Si2156_optionStruct    Si2156_ATV_LIF_OUT_PROP_AMP[];
extern Si2156_fieldDicoStruct Si2156_ATV_LIF_OUT_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_ATV_RF_TOP_PROP_ATV_RF_TOP[];
extern Si2156_fieldDicoStruct Si2156_ATV_RF_TOP_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_ATV_RSQ_RSSI_THRESHOLD_PROP_LO[];
extern Si2156_optionStruct    Si2156_ATV_RSQ_RSSI_THRESHOLD_PROP_HI[];
extern Si2156_fieldDicoStruct Si2156_ATV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_ATV_VIDEO_MODE_PROP_VIDEO_SYS[];
extern Si2156_optionStruct    Si2156_ATV_VIDEO_MODE_PROP_COLOR[];
extern Si2156_optionStruct    Si2156_ATV_VIDEO_MODE_PROP_TRANS[];
extern Si2156_optionStruct    Si2156_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM[];
extern Si2156_fieldDicoStruct Si2156_ATV_VIDEO_MODE_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP[];
extern Si2156_fieldDicoStruct Si2156_ATV_VSNR_CAP_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_CRYSTAL_TRIM_PROP_XO_CAP[];
extern Si2156_fieldDicoStruct Si2156_CRYSTAL_TRIM_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_DTV_AGC_FREEZE_INPUT_PROP_LEVEL[];
extern Si2156_optionStruct    Si2156_DTV_AGC_FREEZE_INPUT_PROP_PIN[];
extern Si2156_fieldDicoStruct Si2156_DTV_AGC_FREEZE_INPUT_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_DTV_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2156_optionStruct    Si2156_DTV_AGC_SPEED_PROP_AGC_DECIM[];
extern Si2156_fieldDicoStruct Si2156_DTV_AGC_SPEED_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE[];
extern Si2156_optionStruct    Si2156_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE[];
extern Si2156_fieldDicoStruct Si2156_DTV_CONFIG_IF_PORT_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_DTV_EXT_AGC_PROP_MIN_10MV[];
extern Si2156_optionStruct    Si2156_DTV_EXT_AGC_PROP_MAX_10MV[];
extern Si2156_fieldDicoStruct Si2156_DTV_EXT_AGC_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_DTV_FILTER_SELECT_PROP_FILTER[];
extern Si2156_fieldDicoStruct Si2156_DTV_FILTER_SELECT_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_DTV_IEN_PROP_CHLIEN[];
extern Si2156_fieldDicoStruct Si2156_DTV_IEN_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2156_optionStruct    Si2156_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM[];
extern Si2156_fieldDicoStruct Si2156_DTV_INITIAL_AGC_SPEED_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD[];
extern Si2156_fieldDicoStruct Si2156_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_DTV_INTERNAL_ZIF_PROP_ATSC[];
extern Si2156_optionStruct    Si2156_DTV_INTERNAL_ZIF_PROP_QAM_US[];
extern Si2156_optionStruct    Si2156_DTV_INTERNAL_ZIF_PROP_DVBT[];
extern Si2156_optionStruct    Si2156_DTV_INTERNAL_ZIF_PROP_DVBC[];
extern Si2156_optionStruct    Si2156_DTV_INTERNAL_ZIF_PROP_ISDBT[];
extern Si2156_optionStruct    Si2156_DTV_INTERNAL_ZIF_PROP_ISDBC[];
extern Si2156_optionStruct    Si2156_DTV_INTERNAL_ZIF_PROP_DTMB[];
extern Si2156_fieldDicoStruct Si2156_DTV_INTERNAL_ZIF_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_DTV_INT_SENSE_PROP_CHLNEGEN[];
extern Si2156_optionStruct    Si2156_DTV_INT_SENSE_PROP_CHLPOSEN[];
extern Si2156_fieldDicoStruct Si2156_DTV_INT_SENSE_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_DTV_LIF_FREQ_PROP_OFFSET[];
extern Si2156_fieldDicoStruct Si2156_DTV_LIF_FREQ_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_DTV_LIF_OUT_PROP_OFFSET[];
extern Si2156_optionStruct    Si2156_DTV_LIF_OUT_PROP_AMP[];
extern Si2156_fieldDicoStruct Si2156_DTV_LIF_OUT_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_DTV_MODE_PROP_BW[];
extern Si2156_optionStruct    Si2156_DTV_MODE_PROP_MODULATION[];
extern Si2156_optionStruct    Si2156_DTV_MODE_PROP_INVERT_SPECTRUM[];
extern Si2156_fieldDicoStruct Si2156_DTV_MODE_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_DTV_RF_TOP_PROP_DTV_RF_TOP[];
extern Si2156_fieldDicoStruct Si2156_DTV_RF_TOP_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_DTV_RSQ_RSSI_THRESHOLD_PROP_LO[];
extern Si2156_optionStruct    Si2156_DTV_RSQ_RSSI_THRESHOLD_PROP_HI[];
extern Si2156_fieldDicoStruct Si2156_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_MASTER_IEN_PROP_TUNIEN[];
extern Si2156_optionStruct    Si2156_MASTER_IEN_PROP_ATVIEN[];
extern Si2156_optionStruct    Si2156_MASTER_IEN_PROP_DTVIEN[];
extern Si2156_optionStruct    Si2156_MASTER_IEN_PROP_ERRIEN[];
extern Si2156_optionStruct    Si2156_MASTER_IEN_PROP_CTSIEN[];
extern Si2156_fieldDicoStruct Si2156_MASTER_IEN_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_TUNER_BLOCKED_VCO_PROP_VCO_CODE[];
extern Si2156_fieldDicoStruct Si2156_TUNER_BLOCKED_VCO_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_TUNER_IEN_PROP_TCIEN[];
extern Si2156_optionStruct    Si2156_TUNER_IEN_PROP_RSSILIEN[];
extern Si2156_optionStruct    Si2156_TUNER_IEN_PROP_RSSIHIEN[];
extern Si2156_fieldDicoStruct Si2156_TUNER_IEN_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_TUNER_INT_SENSE_PROP_TCNEGEN[];
extern Si2156_optionStruct    Si2156_TUNER_INT_SENSE_PROP_RSSILNEGEN[];
extern Si2156_optionStruct    Si2156_TUNER_INT_SENSE_PROP_RSSIHNEGEN[];
extern Si2156_optionStruct    Si2156_TUNER_INT_SENSE_PROP_TCPOSEN[];
extern Si2156_optionStruct    Si2156_TUNER_INT_SENSE_PROP_RSSILPOSEN[];
extern Si2156_optionStruct    Si2156_TUNER_INT_SENSE_PROP_RSSIHPOSEN[];
extern Si2156_fieldDicoStruct Si2156_TUNER_INT_SENSE_PROP_FIELDS[];

extern Si2156_optionStruct    Si2156_TUNER_LO_INJECTION_PROP_BAND_1[];
extern Si2156_optionStruct    Si2156_TUNER_LO_INJECTION_PROP_BAND_2[];
extern Si2156_optionStruct    Si2156_TUNER_LO_INJECTION_PROP_BAND_3[];
extern Si2156_optionStruct    Si2156_TUNER_LO_INJECTION_PROP_BAND_4[];
extern Si2156_optionStruct    Si2156_TUNER_LO_INJECTION_PROP_BAND_5[];
extern Si2156_fieldDicoStruct Si2156_TUNER_LO_INJECTION_PROP_FIELDS[];

/* _properties_strings_extern_insertion_point */
extern Si2156_propertyInfoStruct Si2156_propertyDictionary[];

int   Si2156_PropertyNames       (L1_Si2156_Context *api, char *msg);
int   Si2156_PropertyIndex       (L1_Si2156_Context *api, char *property);
int   Si2156_PropertyFields      (L1_Si2156_Context *api, int propIndex, char *msg);
int   Si2156_PropertyFieldIndex  (L1_Si2156_Context *api, int propIndex, char *field);
int   Si2156_PropertyFieldEnums  (L1_Si2156_Context *api, int propIndex, int fieldIndex, char *msg);
int   Si2156_GetValueFromEntry   (L1_Si2156_Context *api, Si2156_fieldDicoStruct field, char *entry, int *value);
char *Si2156_GetEnumFromValue    (L1_Si2156_Context *api, Si2156_fieldDicoStruct field, int iValue);
char *Si2156_GetEnumFromField    (L1_Si2156_Context *api, Si2156_fieldDicoStruct field);
int   Si2156_SetFieldFromEntry   (L1_Si2156_Context *api, Si2156_fieldDicoStruct field, char *entry);
void  Si2156_showProperty        (L1_Si2156_Context *api, int propertyIndex);
void  Si2156_showPropertyNamed   (L1_Si2156_Context *api, char *property);
int   Si2156_showProperties      (L1_Si2156_Context *api, Si2156_featureEnum feature);
void  Si2156_setupProperty       (L1_Si2156_Context *api, int propIndex);
int   Si2156_setupProperties     (L1_Si2156_Context *api, Si2156_featureEnum feature);

#endif /* Si2156_COMMAND_LINE_APPLICATION */

/* _properties_strings_protos_insertion_start */

#ifdef    Si2156_COMMAND_LINE_APPLICATION
int  Si2156_showATVProperties   (L1_Si2156_Context *api);
int  Si2156_showCOMMONProperties(L1_Si2156_Context *api);
int  Si2156_showDTVProperties   (L1_Si2156_Context *api);
int  Si2156_showTUNERProperties (L1_Si2156_Context *api);


int  Si2156_showAllProperties    (L1_Si2156_Context *api);
#endif /* Si2156_COMMAND_LINE_APPLICATION */
void  Si2156_setupATVDefaults   (L1_Si2156_Context *api);
void  Si2156_setupCOMMONDefaults(L1_Si2156_Context *api);
void  Si2156_setupDTVDefaults   (L1_Si2156_Context *api);
void  Si2156_setupTUNERDefaults (L1_Si2156_Context *api);

void  Si2156_setupAllDefaults   (L1_Si2156_Context *api);

int  Si2156_setupATVProperties   (L1_Si2156_Context *api);
int  Si2156_setupCOMMONProperties(L1_Si2156_Context *api);
int  Si2156_setupDTVProperties   (L1_Si2156_Context *api);
int  Si2156_setupTUNERProperties (L1_Si2156_Context *api);
int  Si2156_setupAllProperties   (L1_Si2156_Context *api);

int  Si2156_downloadATVProperties   (L1_Si2156_Context *api);
int  Si2156_downloadCOMMONProperties(L1_Si2156_Context *api);
int  Si2156_downloadDTVProperties   (L1_Si2156_Context *api);
int  Si2156_downloadTUNERProperties (L1_Si2156_Context *api);
int  Si2156_downloadAllProperties   (L1_Si2156_Context *api);
/* _properties_strings_protos_insertion_point */

#endif /* _Si2156_PROPERTIES_STRINGS_H_ */





