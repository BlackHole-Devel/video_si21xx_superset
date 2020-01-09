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


   API properties strings definitions
   FILE: Si2124_Properties_Strings.h
   Supported IC : Si2124
   Compiled for ROM 62 firmware 2_1_build_5
   Revision: 0.2
   Date: July 24 2017
   Tag: ROM62_2_1_build_5_V0.2
**************************************************************************************/
#ifndef   _Si2124_PROPERTIES_STRINGS_H_
#define   _Si2124_PROPERTIES_STRINGS_H_

#ifdef Si2124_COMMAND_LINE_APPLICATION

extern Si2124_PropObj Si2124_prop;

typedef enum   {
  Si2124_UNSIGNED_CHAR,
  Si2124_SIGNED_CHAR,
  Si2124_UNSIGNED_INT,
  Si2124_SIGNED_INT
} Si2124_datatypeEnum;

typedef struct {
  const char *name;
  int         value;
} Si2124_optionStruct;

typedef enum {
  Si2124_COMMON,
  Si2124_DTV,
  Si2124_TUNER
} Si2124_featureEnum;

typedef struct {
  const char          *name;
  Si2124_datatypeEnum  datatype;
  void                *pField;
  int                  nbOptions;
  Si2124_optionStruct *option;
} Si2124_fieldDicoStruct;

typedef struct {
  Si2124_featureEnum      feature;
  const char             *name;
  int                     nbFields;
  Si2124_fieldDicoStruct *field;
  unsigned int            propertyCode;
} Si2124_propertyInfoStruct;


extern Si2124_optionStruct    Si2124_ACTIVE_LOOP_THROUGH_PROP_ENABLE[];
extern Si2124_fieldDicoStruct Si2124_ACTIVE_LOOP_THROUGH_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_CRYSTAL_TRIM_PROP_XO_CAP[];
extern Si2124_fieldDicoStruct Si2124_CRYSTAL_TRIM_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_DTV_AGC_AUTO_FREEZE_PROP_THLD[];
extern Si2124_optionStruct    Si2124_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT[];
extern Si2124_fieldDicoStruct Si2124_DTV_AGC_AUTO_FREEZE_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_DTV_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2124_optionStruct    Si2124_DTV_AGC_SPEED_PROP_AGC_DECIM[];
extern Si2124_fieldDicoStruct Si2124_DTV_AGC_SPEED_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE[];
extern Si2124_fieldDicoStruct Si2124_DTV_CONFIG_IF_PORT_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_DTV_EXT_AGC_PROP_MIN_10MV[];
extern Si2124_optionStruct    Si2124_DTV_EXT_AGC_PROP_MAX_10MV[];
extern Si2124_fieldDicoStruct Si2124_DTV_EXT_AGC_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_DTV_IF_AGC_SPEED_PROP_ATTACK[];
extern Si2124_optionStruct    Si2124_DTV_IF_AGC_SPEED_PROP_DECAY[];
extern Si2124_fieldDicoStruct Si2124_DTV_IF_AGC_SPEED_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2124_optionStruct    Si2124_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM[];
extern Si2124_fieldDicoStruct Si2124_DTV_INITIAL_AGC_SPEED_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD[];
extern Si2124_fieldDicoStruct Si2124_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_DTV_INTERNAL_ZIF_PROP_ATSC[];
extern Si2124_optionStruct    Si2124_DTV_INTERNAL_ZIF_PROP_DVBT[];
extern Si2124_optionStruct    Si2124_DTV_INTERNAL_ZIF_PROP_ISDBT[];
extern Si2124_optionStruct    Si2124_DTV_INTERNAL_ZIF_PROP_DTMB[];
extern Si2124_fieldDicoStruct Si2124_DTV_INTERNAL_ZIF_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_DTV_LIF_FREQ_PROP_OFFSET[];
extern Si2124_fieldDicoStruct Si2124_DTV_LIF_FREQ_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_DTV_LIF_OUT_PROP_OFFSET[];
extern Si2124_optionStruct    Si2124_DTV_LIF_OUT_PROP_AMP[];
extern Si2124_fieldDicoStruct Si2124_DTV_LIF_OUT_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_DTV_MODE_PROP_BW[];
extern Si2124_optionStruct    Si2124_DTV_MODE_PROP_MODULATION[];
extern Si2124_optionStruct    Si2124_DTV_MODE_PROP_INVERT_SPECTRUM[];
extern Si2124_fieldDicoStruct Si2124_DTV_MODE_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_DTV_PGA_LIMITS_PROP_MIN[];
extern Si2124_optionStruct    Si2124_DTV_PGA_LIMITS_PROP_MAX[];
extern Si2124_fieldDicoStruct Si2124_DTV_PGA_LIMITS_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_DTV_PGA_TARGET_PROP_PGA_TARGET[];
extern Si2124_optionStruct    Si2124_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE[];
extern Si2124_fieldDicoStruct Si2124_DTV_PGA_TARGET_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_DTV_RF_AGC_SPEED_PROP_ATTACK[];
extern Si2124_optionStruct    Si2124_DTV_RF_AGC_SPEED_PROP_DECAY[];
extern Si2124_fieldDicoStruct Si2124_DTV_RF_AGC_SPEED_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_DTV_RF_TOP_PROP_DTV_RF_TOP[];
extern Si2124_fieldDicoStruct Si2124_DTV_RF_TOP_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_DTV_RSQ_RSSI_THRESHOLD_PROP_LO[];
extern Si2124_fieldDicoStruct Si2124_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_DTV_WB_AGC_SPEED_PROP_ATTACK[];
extern Si2124_optionStruct    Si2124_DTV_WB_AGC_SPEED_PROP_DECAY[];
extern Si2124_fieldDicoStruct Si2124_DTV_WB_AGC_SPEED_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_TUNER_BLOCKED_VCO_PROP_VCO_CODE[];
extern Si2124_fieldDicoStruct Si2124_TUNER_BLOCKED_VCO_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_TUNER_BLOCKED_VCO2_PROP_VCO_CODE[];
extern Si2124_fieldDicoStruct Si2124_TUNER_BLOCKED_VCO2_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_TUNER_BLOCKED_VCO3_PROP_VCO_CODE[];
extern Si2124_fieldDicoStruct Si2124_TUNER_BLOCKED_VCO3_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_TUNER_LO_INJECTION_PROP_BAND_1[];
extern Si2124_optionStruct    Si2124_TUNER_LO_INJECTION_PROP_BAND_2[];
extern Si2124_optionStruct    Si2124_TUNER_LO_INJECTION_PROP_BAND_3[];
extern Si2124_fieldDicoStruct Si2124_TUNER_LO_INJECTION_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_WIDE_BAND_ATT_THRS_PROP_WB_ATT_THRS[];
extern Si2124_fieldDicoStruct Si2124_WIDE_BAND_ATT_THRS_PROP_FIELDS[];

extern Si2124_optionStruct    Si2124_XOUT_PROP_AMP[];
extern Si2124_fieldDicoStruct Si2124_XOUT_PROP_FIELDS[];

extern Si2124_propertyInfoStruct Si2124_propertyDictionary[];

int   Si2124_PropertyNames       (L1_Si2124_Context *api, char *msg);
int   Si2124_PropertyIndex       (L1_Si2124_Context *api, const char *property);
int   Si2124_PropertyFields      (L1_Si2124_Context *api, int propIndex, char *msg);
int   Si2124_PropertyFieldIndex  (L1_Si2124_Context *api, int propIndex, char *field);
int   Si2124_PropertyFieldEnums  (L1_Si2124_Context *api, int propIndex, int fieldIndex, char *msg);
int   Si2124_GetValueFromEntry   (L1_Si2124_Context *api, Si2124_fieldDicoStruct field, char *entry, int *value);
char *Si2124_GetEnumFromValue    (L1_Si2124_Context *api, Si2124_fieldDicoStruct field, int iValue);
char *Si2124_GetEnumFromField    (L1_Si2124_Context *api, Si2124_fieldDicoStruct field);
int   Si2124_SetFieldFromEntry   (L1_Si2124_Context *api, Si2124_fieldDicoStruct field, char *entry);
void  Si2124_showProperty        (L1_Si2124_Context *api, int propertyIndex);
void  Si2124_showPropertyNamed   (L1_Si2124_Context *api, char *property);
int   Si2124_showProperties      (L1_Si2124_Context *api, Si2124_featureEnum feature);
void  Si2124_setupProperty       (L1_Si2124_Context *api, int propIndex);
int   Si2124_setupProperties     (L1_Si2124_Context *api, Si2124_featureEnum feature);

int  Si2124_setupCOMMONProperties(L1_Si2124_Context *api);
int  Si2124_setupDTVProperties   (L1_Si2124_Context *api);
int  Si2124_setupTUNERProperties (L1_Si2124_Context *api);
int  Si2124_setupAllProperties   (L1_Si2124_Context *api);

#endif /* Si2124_COMMAND_LINE_APPLICATION */

#endif /* _Si2124_PROPERTIES_STRINGS_H_ */







