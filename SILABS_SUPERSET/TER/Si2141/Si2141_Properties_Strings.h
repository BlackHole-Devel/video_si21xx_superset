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
                  Silicon Laboratories Broadcast Si2141 Layer 1 API


   API properties strings definitions
   FILE: Si2141_Properties_Strings.h
   Supported IC : Si2141
   Compiled for ROM 61 firmware 1_1_build_12
   Revision: 0.5
   Date: June 14 2019
   Tag: ROM61_1_1_build_12_V0.5
**************************************************************************************/
#ifndef   _Si2141_PROPERTIES_STRINGS_H_
#define   _Si2141_PROPERTIES_STRINGS_H_

#ifdef Si2141_COMMAND_LINE_APPLICATION

extern Si2141_PropObj Si2141_prop;

typedef enum   {
  Si2141_UNSIGNED_CHAR,
  Si2141_SIGNED_CHAR,
  Si2141_UNSIGNED_INT,
  Si2141_SIGNED_INT
} Si2141_datatypeEnum;

typedef struct {
  const char *name;
  int         value;
} Si2141_optionStruct;

typedef enum {
  Si2141_COMMON,
  Si2141_DTV,
  Si2141_TUNER
} Si2141_featureEnum;

typedef struct {
  const char          *name;
  Si2141_datatypeEnum  datatype;
  void                *pField;
  int                  nbOptions;
  Si2141_optionStruct *option;
} Si2141_fieldDicoStruct;

typedef struct {
  Si2141_featureEnum      feature;
  const char             *name;
  int                     nbFields;
  Si2141_fieldDicoStruct *field;
  unsigned int            propertyCode;
} Si2141_propertyInfoStruct;


extern Si2141_optionStruct    Si2141_CRYSTAL_TRIM_PROP_XO_CAP[];
extern Si2141_fieldDicoStruct Si2141_CRYSTAL_TRIM_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_DTV_AGC_AUTO_FREEZE_PROP_THLD[];
extern Si2141_optionStruct    Si2141_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT[];
extern Si2141_fieldDicoStruct Si2141_DTV_AGC_AUTO_FREEZE_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_DTV_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2141_optionStruct    Si2141_DTV_AGC_SPEED_PROP_AGC_DECIM[];
extern Si2141_fieldDicoStruct Si2141_DTV_AGC_SPEED_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE[];
extern Si2141_fieldDicoStruct Si2141_DTV_CONFIG_IF_PORT_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_DTV_EXT_AGC_PROP_MIN_10MV[];
extern Si2141_optionStruct    Si2141_DTV_EXT_AGC_PROP_MAX_10MV[];
extern Si2141_fieldDicoStruct Si2141_DTV_EXT_AGC_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_DTV_IF_AGC_SPEED_PROP_ATTACK[];
extern Si2141_optionStruct    Si2141_DTV_IF_AGC_SPEED_PROP_DECAY[];
extern Si2141_fieldDicoStruct Si2141_DTV_IF_AGC_SPEED_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2141_optionStruct    Si2141_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM[];
extern Si2141_fieldDicoStruct Si2141_DTV_INITIAL_AGC_SPEED_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD[];
extern Si2141_fieldDicoStruct Si2141_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_DTV_INTERNAL_ZIF_PROP_ATSC[];
extern Si2141_optionStruct    Si2141_DTV_INTERNAL_ZIF_PROP_QAM_US[];
extern Si2141_optionStruct    Si2141_DTV_INTERNAL_ZIF_PROP_DVBT[];
extern Si2141_optionStruct    Si2141_DTV_INTERNAL_ZIF_PROP_DVBC[];
extern Si2141_optionStruct    Si2141_DTV_INTERNAL_ZIF_PROP_ISDBT[];
extern Si2141_optionStruct    Si2141_DTV_INTERNAL_ZIF_PROP_ISDBC[];
extern Si2141_optionStruct    Si2141_DTV_INTERNAL_ZIF_PROP_DTMB[];
extern Si2141_fieldDicoStruct Si2141_DTV_INTERNAL_ZIF_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_DTV_LIF_FREQ_PROP_OFFSET[];
extern Si2141_fieldDicoStruct Si2141_DTV_LIF_FREQ_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_DTV_LIF_OUT_PROP_OFFSET[];
extern Si2141_optionStruct    Si2141_DTV_LIF_OUT_PROP_AMP[];
extern Si2141_fieldDicoStruct Si2141_DTV_LIF_OUT_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_DTV_MODE_PROP_BW[];
extern Si2141_optionStruct    Si2141_DTV_MODE_PROP_MODULATION[];
extern Si2141_optionStruct    Si2141_DTV_MODE_PROP_INVERT_SPECTRUM[];
extern Si2141_fieldDicoStruct Si2141_DTV_MODE_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_DTV_PGA_LIMITS_PROP_MIN[];
extern Si2141_optionStruct    Si2141_DTV_PGA_LIMITS_PROP_MAX[];
extern Si2141_fieldDicoStruct Si2141_DTV_PGA_LIMITS_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_DTV_PGA_TARGET_PROP_PGA_TARGET[];
extern Si2141_optionStruct    Si2141_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE[];
extern Si2141_fieldDicoStruct Si2141_DTV_PGA_TARGET_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_DTV_RF_AGC_SPEED_PROP_ATTACK[];
extern Si2141_optionStruct    Si2141_DTV_RF_AGC_SPEED_PROP_DECAY[];
extern Si2141_fieldDicoStruct Si2141_DTV_RF_AGC_SPEED_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_DTV_RF_TOP_PROP_DTV_RF_TOP[];
extern Si2141_fieldDicoStruct Si2141_DTV_RF_TOP_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_DTV_RSQ_RSSI_THRESHOLD_PROP_LO[];
extern Si2141_fieldDicoStruct Si2141_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_DTV_WB_AGC_SPEED_PROP_ATTACK[];
extern Si2141_optionStruct    Si2141_DTV_WB_AGC_SPEED_PROP_DECAY[];
extern Si2141_fieldDicoStruct Si2141_DTV_WB_AGC_SPEED_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_TUNER_BLOCKED_VCO_PROP_VCO_CODE[];
extern Si2141_fieldDicoStruct Si2141_TUNER_BLOCKED_VCO_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_TUNER_BLOCKED_VCO2_PROP_VCO_CODE[];
extern Si2141_fieldDicoStruct Si2141_TUNER_BLOCKED_VCO2_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_TUNER_BLOCKED_VCO3_PROP_VCO_CODE[];
extern Si2141_fieldDicoStruct Si2141_TUNER_BLOCKED_VCO3_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_TUNER_LO_INJECTION_PROP_BAND_1[];
extern Si2141_optionStruct    Si2141_TUNER_LO_INJECTION_PROP_BAND_2[];
extern Si2141_optionStruct    Si2141_TUNER_LO_INJECTION_PROP_BAND_3[];
extern Si2141_fieldDicoStruct Si2141_TUNER_LO_INJECTION_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_TUNER_RETURN_LOSS_PROP_CONFIG[];
extern Si2141_optionStruct    Si2141_TUNER_RETURN_LOSS_PROP_MODE[];
extern Si2141_optionStruct    Si2141_TUNER_RETURN_LOSS_PROP_RESERVED[];
extern Si2141_fieldDicoStruct Si2141_TUNER_RETURN_LOSS_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_TUNER_TF1_BOUNDARY_OFFSET_PROP_TF1_BOUNDARY_OFFSET[];
extern Si2141_fieldDicoStruct Si2141_TUNER_TF1_BOUNDARY_OFFSET_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_WIDE_BAND_ATT_THRS_PROP_WB_ATT_THRS[];
extern Si2141_fieldDicoStruct Si2141_WIDE_BAND_ATT_THRS_PROP_FIELDS[];

extern Si2141_optionStruct    Si2141_XOUT_PROP_AMP[];
extern Si2141_fieldDicoStruct Si2141_XOUT_PROP_FIELDS[];

extern Si2141_propertyInfoStruct Si2141_propertyDictionary[];

int   Si2141_PropertyNames       (L1_Si2141_Context *api, char *msg);
int   Si2141_PropertyIndex       (L1_Si2141_Context *api, const char *property);
int   Si2141_PropertyFields      (L1_Si2141_Context *api, int propIndex, char *msg);
int   Si2141_PropertyFieldIndex  (L1_Si2141_Context *api, int propIndex, char *field);
int   Si2141_PropertyFieldEnums  (L1_Si2141_Context *api, int propIndex, int fieldIndex, char *msg);
int   Si2141_GetValueFromEntry   (L1_Si2141_Context *api, Si2141_fieldDicoStruct field, char *entry, int *value);
char *Si2141_GetEnumFromValue    (L1_Si2141_Context *api, Si2141_fieldDicoStruct field, int iValue);
char *Si2141_GetEnumFromField    (L1_Si2141_Context *api, Si2141_fieldDicoStruct field);
int   Si2141_SetFieldFromEntry   (L1_Si2141_Context *api, Si2141_fieldDicoStruct field, char *entry);
void  Si2141_showProperty        (L1_Si2141_Context *api, int propertyIndex);
void  Si2141_showPropertyNamed   (L1_Si2141_Context *api, char *property);
int   Si2141_showProperties      (L1_Si2141_Context *api, Si2141_featureEnum feature);
void  Si2141_setupProperty       (L1_Si2141_Context *api, int propIndex);
int   Si2141_setupProperties     (L1_Si2141_Context *api, Si2141_featureEnum feature);

#endif /* Si2141_COMMAND_LINE_APPLICATION */


int  Si2141_setupCOMMONProperties(L1_Si2141_Context *api);
int  Si2141_setupDTVProperties   (L1_Si2141_Context *api);
int  Si2141_setupTUNERProperties (L1_Si2141_Context *api);
int  Si2141_setupAllProperties   (L1_Si2141_Context *api);

#endif /* _Si2141_PROPERTIES_STRINGS_H_ */







