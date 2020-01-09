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
   API properties strings functions definitions
   FILE: Si2146_L1_Properties.c
   Supported IC : Si2146
   Compiled for ROM 11 firmware 1_1_build_3
   Revision: 0.1
   Tag:  TAGNAME
   Date: December 23 2011
**************************************************************************************/
#define   Si2146_COMMAND_PROTOTYPES

#include "Si2146_L1_API.h"
#include "Si2146_Properties_Strings.h"

#ifdef Si2146_COMMAND_LINE_APPLICATION

/* define a local PropObj variable to use for the Property Dictionary initializer */
Si2146_PropObj Si2146_prop;
char optionText[20];

/* _properties_features_text_insertion_start */
char *Si2146_featureText[] =
{
  "COMMON",
  "DTV",
  "TUNER",
};
/* _properties_features_text_insertion_point */

/* _properties_strings_insertion_start */
Si2146_optionStruct    Si2146_CRYSTAL_TRIM_PROP_XO_CAP[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",    15}
};
Si2146_fieldDicoStruct Si2146_CRYSTAL_TRIM_PROP_FIELDS[] =
{
  {"XO_CAP", Si2146_UNSIGNED_CHAR, &Si2146_prop.crystal_trim.xo_cap, sizeof(Si2146_CRYSTAL_TRIM_PROP_XO_CAP)/sizeof(Si2146_optionStruct), Si2146_CRYSTAL_TRIM_PROP_XO_CAP},
};
#ifdef LOAD_PATCH_11b3
Si2146_optionStruct    Si2146_DTV_AGC_FREEZE_INPUT_PROP_LEVEL[] =
{
  {"LOW",      0},
  {"HIGH",     1},
};
Si2146_optionStruct    Si2146_DTV_AGC_FREEZE_INPUT_PROP_PIN[] =
{
  {"NONE",      0},
  {"GPIO1",     1},
  {"GPIO2",     2},
  {"GPIO3",     3},
};
Si2146_fieldDicoStruct Si2146_DTV_AGC_FREEZE_INPUT_PROP_FIELDS[] =
{
  {"LEVEL", Si2146_UNSIGNED_CHAR, &Si2146_prop.dtv_agc_freeze_input.level, sizeof(Si2146_DTV_AGC_FREEZE_INPUT_PROP_LEVEL)/sizeof(Si2146_optionStruct), Si2146_DTV_AGC_FREEZE_INPUT_PROP_LEVEL},
  {"PIN",   Si2146_UNSIGNED_CHAR, &Si2146_prop.dtv_agc_freeze_input.pin  , sizeof(Si2146_DTV_AGC_FREEZE_INPUT_PROP_PIN  )/sizeof(Si2146_optionStruct), Si2146_DTV_AGC_FREEZE_INPUT_PROP_PIN  },
};
#endif

Si2146_optionStruct    Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED[] =
{
  {"AUTO",     0},
  {"39",      39},
  {"54",      54},
  {"63",      63},
  {"89",      89},
  {"105",    105},
  {"121",    121},
  {"137",    137},
  {"158",    158},
  {"172",    172},
  {"185",    185},
  {"196",    196},
  {"206",    206},
  {"216",    216},
  {"219",    219},
  {"222",    222},
};
Si2146_optionStruct    Si2146_DTV_AGC_SPEED_PROP_AGC_DECIM[] =
{
  {"OFF",     0},
  {"2",       1},
  {"4",       2},
  {"8",       3},
};
Si2146_fieldDicoStruct Si2146_DTV_AGC_SPEED_PROP_FIELDS[] =
{
  {"IF_AGC_SPEED", Si2146_UNSIGNED_CHAR, &Si2146_prop.dtv_agc_speed.if_agc_speed, sizeof(Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED)/sizeof(Si2146_optionStruct), Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED},
  {"AGC_DECIM",    Si2146_UNSIGNED_CHAR, &Si2146_prop.dtv_agc_speed.agc_decim   , sizeof(Si2146_DTV_AGC_SPEED_PROP_AGC_DECIM   )/sizeof(Si2146_optionStruct), Si2146_DTV_AGC_SPEED_PROP_AGC_DECIM   },
};

Si2146_optionStruct    Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE[] =
{
  {"LIF_IF1",         0},
  {"LIF_SE_IF1A",     4},
};
Si2146_optionStruct    Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE[] =
{
  {"INTERNAL",          0},
  {"DLIF_AGC_3DB",      1},
  {"DLIF_AGC_FULL",     3},
};
Si2146_fieldDicoStruct Si2146_DTV_CONFIG_IF_PORT_PROP_FIELDS[] =
{
  {"DTV_OUT_TYPE",   Si2146_UNSIGNED_CHAR, &Si2146_prop.dtv_config_if_port.dtv_out_type  , sizeof(Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE  )/sizeof(Si2146_optionStruct), Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE  },
  {"DTV_AGC_SOURCE", Si2146_UNSIGNED_CHAR, &Si2146_prop.dtv_config_if_port.dtv_agc_source, sizeof(Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE)/sizeof(Si2146_optionStruct), Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE},
};

Si2146_optionStruct    Si2146_DTV_EXT_AGC_PROP_MIN_10MV[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   215}
};
Si2146_optionStruct    Si2146_DTV_EXT_AGC_PROP_MAX_10MV[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   215}
};
Si2146_fieldDicoStruct Si2146_DTV_EXT_AGC_PROP_FIELDS[] =
{
  {"MIN_10MV", Si2146_UNSIGNED_CHAR, &Si2146_prop.dtv_ext_agc.min_10mv, sizeof(Si2146_DTV_EXT_AGC_PROP_MIN_10MV)/sizeof(Si2146_optionStruct), Si2146_DTV_EXT_AGC_PROP_MIN_10MV},
  {"MAX_10MV", Si2146_UNSIGNED_CHAR, &Si2146_prop.dtv_ext_agc.max_10mv, sizeof(Si2146_DTV_EXT_AGC_PROP_MAX_10MV)/sizeof(Si2146_optionStruct), Si2146_DTV_EXT_AGC_PROP_MAX_10MV},
};

Si2146_optionStruct    Si2146_DTV_IEN_PROP_CHLIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2146_fieldDicoStruct Si2146_DTV_IEN_PROP_FIELDS[] =
{
  {"CHLIEN", Si2146_UNSIGNED_CHAR, &Si2146_prop.dtv_ien.chlien, sizeof(Si2146_DTV_IEN_PROP_CHLIEN)/sizeof(Si2146_optionStruct), Si2146_DTV_IEN_PROP_CHLIEN},
};

Si2146_optionStruct    Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED[] =
{
  {"AUTO",     0},
  {"39",      39},
  {"54",      54},
  {"63",      63},
  {"89",      89},
  {"105",    105},
  {"121",    121},
  {"137",    137},
  {"158",    158},
  {"172",    172},
  {"185",    185},
  {"196",    196},
  {"206",    206},
  {"216",    216},
  {"219",    219},
  {"222",    222},
};
Si2146_optionStruct    Si2146_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM[] =
{
  {"OFF",     0},
  {"2",       1},
  {"4",       2},
  {"8",       3},
};
Si2146_fieldDicoStruct Si2146_DTV_INITIAL_AGC_SPEED_PROP_FIELDS[] =
{
  {"IF_AGC_SPEED", Si2146_UNSIGNED_CHAR, &Si2146_prop.dtv_initial_agc_speed.if_agc_speed, sizeof(Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED)/sizeof(Si2146_optionStruct), Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED},
  {"AGC_DECIM",    Si2146_UNSIGNED_CHAR, &Si2146_prop.dtv_initial_agc_speed.agc_decim   , sizeof(Si2146_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM   )/sizeof(Si2146_optionStruct), Si2146_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM   },
};

Si2146_optionStruct    Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE", 65535}
};
Si2146_fieldDicoStruct Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS[] =
{
  {"PERIOD", Si2146_UNSIGNED_INT, &Si2146_prop.dtv_initial_agc_speed_period.period, sizeof(Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD)/sizeof(Si2146_optionStruct), Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD},
};

Si2146_optionStruct    Si2146_DTV_INT_SENSE_PROP_CHLNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2146_optionStruct    Si2146_DTV_INT_SENSE_PROP_CHLPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2146_fieldDicoStruct Si2146_DTV_INT_SENSE_PROP_FIELDS[] =
{
  {"CHLNEGEN", Si2146_UNSIGNED_CHAR, &Si2146_prop.dtv_int_sense.chlnegen, sizeof(Si2146_DTV_INT_SENSE_PROP_CHLNEGEN)/sizeof(Si2146_optionStruct), Si2146_DTV_INT_SENSE_PROP_CHLNEGEN},
  {"CHLPOSEN", Si2146_UNSIGNED_CHAR, &Si2146_prop.dtv_int_sense.chlposen, sizeof(Si2146_DTV_INT_SENSE_PROP_CHLPOSEN)/sizeof(Si2146_optionStruct), Si2146_DTV_INT_SENSE_PROP_CHLPOSEN},
};

Si2146_optionStruct    Si2146_DTV_LIF_FREQ_PROP_OFFSET[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",  7000}
};
Si2146_fieldDicoStruct Si2146_DTV_LIF_FREQ_PROP_FIELDS[] =
{
  {"OFFSET", Si2146_UNSIGNED_INT, &Si2146_prop.dtv_lif_freq.offset, sizeof(Si2146_DTV_LIF_FREQ_PROP_OFFSET)/sizeof(Si2146_optionStruct), Si2146_DTV_LIF_FREQ_PROP_OFFSET},
};

Si2146_optionStruct    Si2146_DTV_LIF_OUT_PROP_OFFSET[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2146_optionStruct    Si2146_DTV_LIF_OUT_PROP_AMP[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2146_fieldDicoStruct Si2146_DTV_LIF_OUT_PROP_FIELDS[] =
{
  {"OFFSET", Si2146_UNSIGNED_CHAR, &Si2146_prop.dtv_lif_out.offset, sizeof(Si2146_DTV_LIF_OUT_PROP_OFFSET)/sizeof(Si2146_optionStruct), Si2146_DTV_LIF_OUT_PROP_OFFSET},
  {"AMP",    Si2146_UNSIGNED_CHAR, &Si2146_prop.dtv_lif_out.amp   , sizeof(Si2146_DTV_LIF_OUT_PROP_AMP   )/sizeof(Si2146_optionStruct), Si2146_DTV_LIF_OUT_PROP_AMP   },
};

Si2146_optionStruct    Si2146_DTV_MODE_PROP_BW[] =
{
  {"BW_6MHZ",     6},
  {"BW_7MHZ",     7},
  {"BW_8MHZ",     8},
};
Si2146_optionStruct    Si2146_DTV_MODE_PROP_MODULATION[] =
{
  {"ATSC",       0},
  {"QAM_US",     1},
  {"DVBT",       2},
  {"DVBC",       3},
  {"ISDBT",      4},
  {"ISDBC",      5},
  {"DTMB",       6},
  {"CW",        15},
};
Si2146_optionStruct    Si2146_DTV_MODE_PROP_INVERT_SPECTRUM[] =
{
  {"NORMAL",       0},
  {"INVERTED",     1},
};
Si2146_fieldDicoStruct Si2146_DTV_MODE_PROP_FIELDS[] =
{
  {"BW",              Si2146_UNSIGNED_CHAR, &Si2146_prop.dtv_mode.bw             , sizeof(Si2146_DTV_MODE_PROP_BW             )/sizeof(Si2146_optionStruct), Si2146_DTV_MODE_PROP_BW             },
  {"MODULATION",      Si2146_UNSIGNED_CHAR, &Si2146_prop.dtv_mode.modulation     , sizeof(Si2146_DTV_MODE_PROP_MODULATION     )/sizeof(Si2146_optionStruct), Si2146_DTV_MODE_PROP_MODULATION     },
  {"INVERT_SPECTRUM", Si2146_UNSIGNED_CHAR, &Si2146_prop.dtv_mode.invert_spectrum, sizeof(Si2146_DTV_MODE_PROP_INVERT_SPECTRUM)/sizeof(Si2146_optionStruct), Si2146_DTV_MODE_PROP_INVERT_SPECTRUM},
};

Si2146_optionStruct    Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP[] =
{
  {"AUTO",      0},
  {"0DB",       6},
  {"M1DB",      7},
  {"M2DB",      8},
  {"M3DB",      9},
  {"M4DB",     10},
  {"M5DB",     11},
  {"M6DB",     12},
  {"M7DB",     13},
  {"M8DB",     14},
  {"M9DB",     15},
  {"M10DB",    16},
  {"M11DB",    17},
  {"M12DB",    18},
};
Si2146_fieldDicoStruct Si2146_DTV_RF_TOP_PROP_FIELDS[] =
{
  {"DTV_RF_TOP", Si2146_UNSIGNED_CHAR, &Si2146_prop.dtv_rf_top.dtv_rf_top, sizeof(Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP)/sizeof(Si2146_optionStruct), Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP},
};

Si2146_optionStruct    Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_LO[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si2146_optionStruct    Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_HI[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si2146_fieldDicoStruct Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[] =
{
  {"LO",   Si2146_SIGNED_CHAR, &Si2146_prop.dtv_rsq_rssi_threshold.lo, sizeof(Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_LO)/sizeof(Si2146_optionStruct), Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_LO},
  {"HI",   Si2146_SIGNED_CHAR, &Si2146_prop.dtv_rsq_rssi_threshold.hi, sizeof(Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_HI)/sizeof(Si2146_optionStruct), Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_HI},
};

Si2146_optionStruct    Si2146_MASTER_IEN_PROP_TUNIEN[] =
{
  {"OFF",     0},
  {"ON",      1},
};
Si2146_optionStruct    Si2146_MASTER_IEN_PROP_ATVIEN[] =
{
  {"OFF",     0},
  {"ON",      1},
};
Si2146_optionStruct    Si2146_MASTER_IEN_PROP_DTVIEN[] =
{
  {"OFF",     0},
  {"ON",      1},
};
Si2146_optionStruct    Si2146_MASTER_IEN_PROP_ERRIEN[] =
{
  {"OFF",     0},
  {"ON",      1},
};
Si2146_optionStruct    Si2146_MASTER_IEN_PROP_CTSIEN[] =
{
  {"OFF",     0},
  {"ON",      1},
};
Si2146_fieldDicoStruct Si2146_MASTER_IEN_PROP_FIELDS[] =
{
  {"TUNIEN", Si2146_UNSIGNED_CHAR, &Si2146_prop.master_ien.tunien, sizeof(Si2146_MASTER_IEN_PROP_TUNIEN)/sizeof(Si2146_optionStruct), Si2146_MASTER_IEN_PROP_TUNIEN},
  {"ATVIEN", Si2146_UNSIGNED_CHAR, &Si2146_prop.master_ien.atvien, sizeof(Si2146_MASTER_IEN_PROP_ATVIEN)/sizeof(Si2146_optionStruct), Si2146_MASTER_IEN_PROP_ATVIEN},
  {"DTVIEN", Si2146_UNSIGNED_CHAR, &Si2146_prop.master_ien.dtvien, sizeof(Si2146_MASTER_IEN_PROP_DTVIEN)/sizeof(Si2146_optionStruct), Si2146_MASTER_IEN_PROP_DTVIEN},
  {"ERRIEN", Si2146_UNSIGNED_CHAR, &Si2146_prop.master_ien.errien, sizeof(Si2146_MASTER_IEN_PROP_ERRIEN)/sizeof(Si2146_optionStruct), Si2146_MASTER_IEN_PROP_ERRIEN},
  {"CTSIEN", Si2146_UNSIGNED_CHAR, &Si2146_prop.master_ien.ctsien, sizeof(Si2146_MASTER_IEN_PROP_CTSIEN)/sizeof(Si2146_optionStruct), Si2146_MASTER_IEN_PROP_CTSIEN},
};

Si2146_optionStruct    Si2146_TUNER_BLOCKED_VCO_PROP_VCO_CODE[] =
{
    {"MIN_RANGE",  -32768},
    {"MAX_RANGE",   32767}
};
Si2146_fieldDicoStruct Si2146_TUNER_BLOCKED_VCO_PROP_FIELDS[] =
{
  {"VCO_CODE",   Si2146_SIGNED_INT, &Si2146_prop.tuner_blocked_vco.vco_code, sizeof(Si2146_TUNER_BLOCKED_VCO_PROP_VCO_CODE)/sizeof(Si2146_optionStruct), Si2146_TUNER_BLOCKED_VCO_PROP_VCO_CODE},
};

Si2146_optionStruct    Si2146_TUNER_IEN_PROP_TCIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2146_optionStruct    Si2146_TUNER_IEN_PROP_RSSILIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2146_optionStruct    Si2146_TUNER_IEN_PROP_RSSIHIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2146_fieldDicoStruct Si2146_TUNER_IEN_PROP_FIELDS[] =
{
  {"TCIEN",    Si2146_UNSIGNED_CHAR, &Si2146_prop.tuner_ien.tcien   , sizeof(Si2146_TUNER_IEN_PROP_TCIEN   )/sizeof(Si2146_optionStruct), Si2146_TUNER_IEN_PROP_TCIEN   },
  {"RSSILIEN", Si2146_UNSIGNED_CHAR, &Si2146_prop.tuner_ien.rssilien, sizeof(Si2146_TUNER_IEN_PROP_RSSILIEN)/sizeof(Si2146_optionStruct), Si2146_TUNER_IEN_PROP_RSSILIEN},
  {"RSSIHIEN", Si2146_UNSIGNED_CHAR, &Si2146_prop.tuner_ien.rssihien, sizeof(Si2146_TUNER_IEN_PROP_RSSIHIEN)/sizeof(Si2146_optionStruct), Si2146_TUNER_IEN_PROP_RSSIHIEN},
};

Si2146_optionStruct    Si2146_TUNER_INT_SENSE_PROP_TCNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2146_optionStruct    Si2146_TUNER_INT_SENSE_PROP_RSSILNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2146_optionStruct    Si2146_TUNER_INT_SENSE_PROP_RSSIHNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2146_optionStruct    Si2146_TUNER_INT_SENSE_PROP_TCPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2146_optionStruct    Si2146_TUNER_INT_SENSE_PROP_RSSILPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2146_optionStruct    Si2146_TUNER_INT_SENSE_PROP_RSSIHPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2146_fieldDicoStruct Si2146_TUNER_INT_SENSE_PROP_FIELDS[] =
{
  {"TCNEGEN",    Si2146_UNSIGNED_CHAR, &Si2146_prop.tuner_int_sense.tcnegen   , sizeof(Si2146_TUNER_INT_SENSE_PROP_TCNEGEN   )/sizeof(Si2146_optionStruct), Si2146_TUNER_INT_SENSE_PROP_TCNEGEN   },
  {"RSSILNEGEN", Si2146_UNSIGNED_CHAR, &Si2146_prop.tuner_int_sense.rssilnegen, sizeof(Si2146_TUNER_INT_SENSE_PROP_RSSILNEGEN)/sizeof(Si2146_optionStruct), Si2146_TUNER_INT_SENSE_PROP_RSSILNEGEN},
  {"RSSIHNEGEN", Si2146_UNSIGNED_CHAR, &Si2146_prop.tuner_int_sense.rssihnegen, sizeof(Si2146_TUNER_INT_SENSE_PROP_RSSIHNEGEN)/sizeof(Si2146_optionStruct), Si2146_TUNER_INT_SENSE_PROP_RSSIHNEGEN},
  {"TCPOSEN",    Si2146_UNSIGNED_CHAR, &Si2146_prop.tuner_int_sense.tcposen   , sizeof(Si2146_TUNER_INT_SENSE_PROP_TCPOSEN   )/sizeof(Si2146_optionStruct), Si2146_TUNER_INT_SENSE_PROP_TCPOSEN   },
  {"RSSILPOSEN", Si2146_UNSIGNED_CHAR, &Si2146_prop.tuner_int_sense.rssilposen, sizeof(Si2146_TUNER_INT_SENSE_PROP_RSSILPOSEN)/sizeof(Si2146_optionStruct), Si2146_TUNER_INT_SENSE_PROP_RSSILPOSEN},
  {"RSSIHPOSEN", Si2146_UNSIGNED_CHAR, &Si2146_prop.tuner_int_sense.rssihposen, sizeof(Si2146_TUNER_INT_SENSE_PROP_RSSIHPOSEN)/sizeof(Si2146_optionStruct), Si2146_TUNER_INT_SENSE_PROP_RSSIHPOSEN},
};

Si2146_optionStruct    Si2146_TUNER_LO_INJECTION_PROP_BAND_1[] =
{
  {"LOW_SIDE",      0},
  {"HIGH_SIDE",     1},
};
Si2146_optionStruct    Si2146_TUNER_LO_INJECTION_PROP_BAND_2[] =
{
  {"LOW_SIDE",      0},
  {"HIGH_SIDE",     1},
};
Si2146_optionStruct    Si2146_TUNER_LO_INJECTION_PROP_BAND_3[] =
{
  {"LOW_SIDE",      0},
  {"HIGH_SIDE",     1},
};
Si2146_optionStruct    Si2146_TUNER_LO_INJECTION_PROP_BAND_4[] =
{
  {"LOW_SIDE",      0},
  {"HIGH_SIDE",     1},
};
Si2146_optionStruct    Si2146_TUNER_LO_INJECTION_PROP_BAND_5[] =
{
  {"LOW_SIDE",      0},
  {"HIGH_SIDE",     1},
};
Si2146_fieldDicoStruct Si2146_TUNER_LO_INJECTION_PROP_FIELDS[] =
{
  {"BAND_1", Si2146_UNSIGNED_CHAR, &Si2146_prop.tuner_lo_injection.band_1, sizeof(Si2146_TUNER_LO_INJECTION_PROP_BAND_1)/sizeof(Si2146_optionStruct), Si2146_TUNER_LO_INJECTION_PROP_BAND_1},
  {"BAND_2", Si2146_UNSIGNED_CHAR, &Si2146_prop.tuner_lo_injection.band_2, sizeof(Si2146_TUNER_LO_INJECTION_PROP_BAND_2)/sizeof(Si2146_optionStruct), Si2146_TUNER_LO_INJECTION_PROP_BAND_2},
  {"BAND_3", Si2146_UNSIGNED_CHAR, &Si2146_prop.tuner_lo_injection.band_3, sizeof(Si2146_TUNER_LO_INJECTION_PROP_BAND_3)/sizeof(Si2146_optionStruct), Si2146_TUNER_LO_INJECTION_PROP_BAND_3},
  {"BAND_4", Si2146_UNSIGNED_CHAR, &Si2146_prop.tuner_lo_injection.band_4, sizeof(Si2146_TUNER_LO_INJECTION_PROP_BAND_4)/sizeof(Si2146_optionStruct), Si2146_TUNER_LO_INJECTION_PROP_BAND_4},
  {"BAND_5", Si2146_UNSIGNED_CHAR, &Si2146_prop.tuner_lo_injection.band_5, sizeof(Si2146_TUNER_LO_INJECTION_PROP_BAND_5)/sizeof(Si2146_optionStruct), Si2146_TUNER_LO_INJECTION_PROP_BAND_5},
};

Si2146_propertyInfoStruct Si2146_propertyDictionary[] =
{
  {Si2146_COMMON, "CRYSTAL_TRIM"                , sizeof(Si2146_CRYSTAL_TRIM_PROP_FIELDS                )/sizeof(Si2146_fieldDicoStruct), Si2146_CRYSTAL_TRIM_PROP_FIELDS                 , Si2146_CRYSTAL_TRIM_PROP                 },
  {Si2146_COMMON, "MASTER_IEN"                  , sizeof(Si2146_MASTER_IEN_PROP_FIELDS                  )/sizeof(Si2146_fieldDicoStruct), Si2146_MASTER_IEN_PROP_FIELDS                   , Si2146_MASTER_IEN_PROP                   },
  #ifdef LOAD_PATCH_11b3
  {Si2146_DTV   , "DTV_AGC_FREEZE_INPUT"        , sizeof(Si2146_DTV_AGC_FREEZE_INPUT_PROP_FIELDS        )/sizeof(Si2146_fieldDicoStruct), Si2146_DTV_AGC_FREEZE_INPUT_PROP_FIELDS         , Si2146_DTV_AGC_FREEZE_INPUT_PROP         },
  #endif
  {Si2146_DTV   , "DTV_AGC_SPEED"               , sizeof(Si2146_DTV_AGC_SPEED_PROP_FIELDS               )/sizeof(Si2146_fieldDicoStruct), Si2146_DTV_AGC_SPEED_PROP_FIELDS                , Si2146_DTV_AGC_SPEED_PROP                },
  {Si2146_DTV   , "DTV_CONFIG_IF_PORT"          , sizeof(Si2146_DTV_CONFIG_IF_PORT_PROP_FIELDS          )/sizeof(Si2146_fieldDicoStruct), Si2146_DTV_CONFIG_IF_PORT_PROP_FIELDS           , Si2146_DTV_CONFIG_IF_PORT_PROP           },
  {Si2146_DTV   , "DTV_EXT_AGC"                 , sizeof(Si2146_DTV_EXT_AGC_PROP_FIELDS                 )/sizeof(Si2146_fieldDicoStruct), Si2146_DTV_EXT_AGC_PROP_FIELDS                  , Si2146_DTV_EXT_AGC_PROP                  },
  {Si2146_DTV   , "DTV_IEN"                     , sizeof(Si2146_DTV_IEN_PROP_FIELDS                     )/sizeof(Si2146_fieldDicoStruct), Si2146_DTV_IEN_PROP_FIELDS                      , Si2146_DTV_IEN_PROP                      },
  {Si2146_DTV   , "DTV_INITIAL_AGC_SPEED"       , sizeof(Si2146_DTV_INITIAL_AGC_SPEED_PROP_FIELDS       )/sizeof(Si2146_fieldDicoStruct), Si2146_DTV_INITIAL_AGC_SPEED_PROP_FIELDS        , Si2146_DTV_INITIAL_AGC_SPEED_PROP        },
  {Si2146_DTV   , "DTV_INITIAL_AGC_SPEED_PERIOD", sizeof(Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS)/sizeof(Si2146_fieldDicoStruct), Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS , Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP },
  {Si2146_DTV   , "DTV_INT_SENSE"               , sizeof(Si2146_DTV_INT_SENSE_PROP_FIELDS               )/sizeof(Si2146_fieldDicoStruct), Si2146_DTV_INT_SENSE_PROP_FIELDS                , Si2146_DTV_INT_SENSE_PROP                },
  {Si2146_DTV   , "DTV_LIF_FREQ"                , sizeof(Si2146_DTV_LIF_FREQ_PROP_FIELDS                )/sizeof(Si2146_fieldDicoStruct), Si2146_DTV_LIF_FREQ_PROP_FIELDS                 , Si2146_DTV_LIF_FREQ_PROP                 },
  {Si2146_DTV   , "DTV_LIF_OUT"                 , sizeof(Si2146_DTV_LIF_OUT_PROP_FIELDS                 )/sizeof(Si2146_fieldDicoStruct), Si2146_DTV_LIF_OUT_PROP_FIELDS                  , Si2146_DTV_LIF_OUT_PROP                  },
  {Si2146_DTV   , "DTV_MODE"                    , sizeof(Si2146_DTV_MODE_PROP_FIELDS                    )/sizeof(Si2146_fieldDicoStruct), Si2146_DTV_MODE_PROP_FIELDS                     , Si2146_DTV_MODE_PROP                     },
  {Si2146_DTV   , "DTV_RF_TOP"                  , sizeof(Si2146_DTV_RF_TOP_PROP_FIELDS                  )/sizeof(Si2146_fieldDicoStruct), Si2146_DTV_RF_TOP_PROP_FIELDS                   , Si2146_DTV_RF_TOP_PROP                   },
  {Si2146_DTV   , "DTV_RSQ_RSSI_THRESHOLD"      , sizeof(Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS      )/sizeof(Si2146_fieldDicoStruct), Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS       , Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP       },
  {Si2146_TUNER , "TUNER_BLOCKED_VCO"           , sizeof(Si2146_TUNER_BLOCKED_VCO_PROP_FIELDS           )/sizeof(Si2146_fieldDicoStruct), Si2146_TUNER_BLOCKED_VCO_PROP_FIELDS            , Si2146_TUNER_BLOCKED_VCO_PROP            },
  {Si2146_TUNER , "TUNER_IEN"                   , sizeof(Si2146_TUNER_IEN_PROP_FIELDS                   )/sizeof(Si2146_fieldDicoStruct), Si2146_TUNER_IEN_PROP_FIELDS                    , Si2146_TUNER_IEN_PROP                    },
  {Si2146_TUNER , "TUNER_INT_SENSE"             , sizeof(Si2146_TUNER_INT_SENSE_PROP_FIELDS             )/sizeof(Si2146_fieldDicoStruct), Si2146_TUNER_INT_SENSE_PROP_FIELDS              , Si2146_TUNER_INT_SENSE_PROP              },
  {Si2146_TUNER , "TUNER_LO_INJECTION"          , sizeof(Si2146_TUNER_LO_INJECTION_PROP_FIELDS          )/sizeof(Si2146_fieldDicoStruct), Si2146_TUNER_LO_INJECTION_PROP_FIELDS           , Si2146_TUNER_LO_INJECTION_PROP           },
};

/* _properties_strings_insertion_point */

int   Si2146_PropertyNames          (L1_Si2146_Context *api, char *msg)
{
  int propIndex;
  int size;
  api = api; /* to avoid 'unused parameter' warning */
  size = sizeof(Si2146_propertyDictionary)/sizeof(Si2146_propertyInfoStruct);
  msg[0]='\0';
  for (propIndex=0; propIndex<size; propIndex++)
  {
    strcat(msg,Si2146_propertyDictionary[propIndex].name);
    if (propIndex< (size-1)) strcat(msg," ");
  }
  return propIndex;
};

int   Si2146_PropertyIndex          (L1_Si2146_Context *api, char *property)
{
  int propIndex;
  int size;
  api = api; /* to avoid 'unused parameter' warning */
  size = sizeof(Si2146_propertyDictionary)/sizeof(Si2146_propertyInfoStruct);
  for (propIndex=0; propIndex <size; propIndex++)
  {
    if (strcmp_nocase(property, Si2146_propertyDictionary[propIndex].name)==0)
    {
      return propIndex;
    }
  }
  return -1;
};

int   Si2146_PropertyFields         (L1_Si2146_Context *api, int propIndex, char *msg)
{
  int fieldIndex;
  api = api; /* to avoid 'unused parameter' warning */
  msg[0]='\0';
  for (fieldIndex=0; fieldIndex < Si2146_propertyDictionary[propIndex].nbFields; fieldIndex++)
  {
    strcat(msg, Si2146_propertyDictionary[propIndex].field[fieldIndex].name);
    if (fieldIndex< (Si2146_propertyDictionary[propIndex].nbFields-1)) strcat(msg," ");
  }
  return -1;
};

int   Si2146_PropertyFieldIndex     (L1_Si2146_Context *api, int propIndex, char *field)
{
  int fieldIndex;
  api = api; /* to avoid 'unused parameter' warning */
  for (fieldIndex=0; fieldIndex < Si2146_propertyDictionary[propIndex].nbFields; fieldIndex++)
  {
    if (strcmp_nocase(field, Si2146_propertyDictionary[propIndex].field[fieldIndex].name)==0)
    {
      return fieldIndex;
    }
  }
  return -1;
};

int   Si2146_PropertyFieldEnums     (L1_Si2146_Context *api, int propIndex, int fieldIndex, char *msg)
{
  int enumIndex;
  api = api; /* to avoid 'unused parameter' warning */
  msg[0]='\0';
  for (enumIndex=0; enumIndex < Si2146_propertyDictionary[propIndex].field[fieldIndex].nbOptions; enumIndex++)
  {
    strcat(msg, Si2146_propertyDictionary[propIndex].field[fieldIndex].option[enumIndex].name);
    if (enumIndex < (Si2146_propertyDictionary[propIndex].field[fieldIndex].nbOptions-1)) strcat(msg," ");
  }
  return enumIndex;
};

int   Si2146_PropertyFieldRanges    (L1_Si2146_Context *api, int propIndex, int fieldIndex, char *msg)
{
  int index;
  char buf[10];
  api = api; /* to avoid 'unused parameter' warning */

  msg[0]='\0';
  for (index=0; index < 2; index++)
  {
    itoa(Si2146_propertyDictionary[propIndex].field[fieldIndex].option[index].value,buf,10);
    strcat(msg, buf);
    if (index < 1) strcat(msg," - ");
  }
  return index;
};

int   Si2146_GetValueFromEntry    (L1_Si2146_Context *api, Si2146_fieldDicoStruct field, char *entry, int *value)
{
  int optionIndex;
  api = api; /* to avoid 'unused parameter' warning */

  if (!strcmp_nocase(field.option[0].name,"MIN_RANGE"))
  {
    if (field.datatype== Si2146_UNSIGNED_INT || field.datatype== Si2146_UNSIGNED_CHAR)
    {
      *value = (unsigned int)atoi(entry);
      return 1;
    }
    else if (field.datatype == Si2146_SIGNED_INT || field.datatype == Si2146_SIGNED_CHAR)
    {
      *value = (int)atoi(entry);
      return 1;
    }
  }
  for (optionIndex=0; optionIndex < field.nbOptions; optionIndex++)
  {
    if (strcmp_nocase(entry, field.option[optionIndex].name     )==0)
    {
      *value = field.option[optionIndex].value;
      return 1;
    }
  }
  return 0;
};

char *Si2146_GetEnumFromValue     (L1_Si2146_Context *api, Si2146_fieldDicoStruct field, int iValue)
{
  int optionIndex;
  api = api; /* to avoid 'unused parameter' warning */
  if (field.nbOptions ==0 )
    {
    sprintf(optionText, "%d", iValue);
    return optionText;
  }
  for (optionIndex=0; optionIndex < field.nbOptions; optionIndex++)
  {
    if (iValue == field.option[optionIndex].value)
    {
      return field.option[optionIndex].name;
    }
  }
  return (char*)NULL;
};

int   Si2146_GetValueFromField    (L1_Si2146_Context *api, Si2146_fieldDicoStruct field)
{
  short intValue;
  short *fieldAsInt;
  short iTmp=0;
  fieldAsInt = &intValue;

  if (field.datatype == Si2146_SIGNED_INT   )
  {
      fieldAsInt= (short *) ((field.pField-(void *) &Si2146_prop)+ (void *)api->prop);
  }
  else if (field.datatype == Si2146_UNSIGNED_CHAR)
  {
      iTmp = *((unsigned char *) ((field.pField-(void *) &Si2146_prop)+ (void *)api->prop));
    fieldAsInt = &iTmp;
  }
  else if (field.datatype == Si2146_SIGNED_CHAR)
  {
      iTmp= *((char *) ((field.pField-(void *) &Si2146_prop)+ (void *)api->prop));
    fieldAsInt = &iTmp;
  }
  else /* if (field.datatype == Si2146_UNSIGNED_INT) */
  {
      fieldAsInt = (unsigned short *) ((field.pField-(void *) &Si2146_prop)+ (void *)api->prop);
  }

  return  *fieldAsInt;
};

char *Si2146_GetEnumFromField     (L1_Si2146_Context *api, Si2146_fieldDicoStruct field)
{
  int intValue;
  int *fieldAsInt;
  int iTmp=0;
  fieldAsInt = &intValue;

  if (field.datatype == Si2146_SIGNED_INT   )
  {
      fieldAsInt= (int *) ((field.pField-(void *) &Si2146_prop) + (void *)api->prop);
  }
  else if (field.datatype == Si2146_UNSIGNED_CHAR)
  {
      iTmp = *((unsigned char *) ((field.pField-(void *) &Si2146_prop) + (void *)api->prop));
    fieldAsInt = &iTmp;
  }
  else if (field.datatype == Si2146_SIGNED_CHAR)
  {
      iTmp= *((char *) ((field.pField-(void *) &Si2146_prop) + (void *)api->prop));
    fieldAsInt = &iTmp;
  }
  else /* if (field.datatype == Si2146_UNSIGNED_INT) */
  {
      fieldAsInt = (unsigned int *)((field.pField-(void *) &Si2146_prop) + (void *)api->prop);
  }

  return Si2146_GetEnumFromValue(api, field, *fieldAsInt);
};

int   Si2146_SetFieldFromEntry    (L1_Si2146_Context *api, Si2146_fieldDicoStruct field, char *entry)
{
  int *fieldAsInt;
  int iTmp=0;
  fieldAsInt = &iTmp;
  if (Si2146_GetValueFromEntry(api, field, entry, fieldAsInt) == 0) return 0;
  if (field.datatype == Si2146_SIGNED_INT )
  {
    *( (int *) ((field.pField-(void *) &Si2146_prop) + (void *)api->prop))=iTmp;
  }
  else if (field.datatype == Si2146_UNSIGNED_CHAR)
  {
    *( (unsigned char *) ((field.pField-(void *) &Si2146_prop) + (void *)api->prop))=iTmp;
  }
  else if (field.datatype == Si2146_SIGNED_CHAR)
  {
    *( (char *) ((field.pField-(void *) &Si2146_prop) + (void *)api->prop))=iTmp;
  }
  else /* if (field.datatype == Si2146_UNSIGNED_INT) */
  {
    *( (unsigned int *) ((field.pField-(void *) &Si2146_prop) + (void *)api->prop))=iTmp;
  }

  return 1;
};

void  Si2146_showProperty           (L1_Si2146_Context *api, int propIndex)
{
  int fieldIndex;
  for (fieldIndex=0; fieldIndex<Si2146_propertyDictionary[propIndex].nbFields; fieldIndex++)
  {
    printf("%s:%s:%s = ", Si2146_featureText[Si2146_propertyDictionary[propIndex].feature], Si2146_propertyDictionary[propIndex].name, Si2146_propertyDictionary[propIndex].field[fieldIndex].name);
    printf("<%s>\n", Si2146_GetEnumFromField(api, Si2146_propertyDictionary[propIndex].field[fieldIndex]));
  }

}

void  Si2146_showPropertyNamed      (L1_Si2146_Context *api, char *property)
{
  int propIndex;

  if ((propIndex = Si2146_PropertyIndex(api, property)) >= 0)
  {
    Si2146_showProperty(api, propIndex);
  }
  else
  {
    printf("Unknown property '%s'\n", property);
  }

}

int   Si2146_showProperties         (L1_Si2146_Context *api,  Si2146_featureEnum feature)
{
  int propertyIndex;
  int dictSize;

  dictSize=sizeof(Si2146_propertyDictionary)/sizeof(Si2146_propertyInfoStruct);

  printf("\n%s current properties:\n\n", Si2146_featureText[feature]);

  for (propertyIndex=0; propertyIndex<dictSize; propertyIndex++)
  {
    if (Si2146_propertyDictionary[propertyIndex].feature != feature) continue;
    Si2146_showProperty(api, propertyIndex);
  }
  return 0;
}

void  Si2146_setupProperty          (L1_Si2146_Context *api, int propIndex)
{
  #define LMAX 20
  char entry[LMAX];
  char setup_msg[1000];
  int fieldIndex;
  char isRangeType = 1;

  for (fieldIndex=0; fieldIndex<Si2146_propertyDictionary[propIndex].nbFields; fieldIndex++)
  {
    isRangeType = (strcmp_nocase(Si2146_propertyDictionary[propIndex].field[fieldIndex].option->name,"MIN_RANGE") == 0);

    printf("%s:%s:%s = ", Si2146_featureText[Si2146_propertyDictionary[propIndex].feature], Si2146_propertyDictionary[propIndex].name, Si2146_propertyDictionary[propIndex].field[fieldIndex].name);

    if ( isRangeType )
    {
      printf("<%d>\n", Si2146_GetValueFromField(api, Si2146_propertyDictionary[propIndex].field[fieldIndex]));
      Si2146_PropertyFieldRanges(api, propIndex, fieldIndex, setup_msg);
      printf("Range: <%s>  ",setup_msg);
    }
    else
    {
      Si2146_PropertyFieldEnums(api, propIndex, fieldIndex, setup_msg);
      printf("<%s>\n Options: <%s>\n", Si2146_GetEnumFromField(api, Si2146_propertyDictionary[propIndex].field[fieldIndex]), setup_msg);
    }

    fgets(entry,LMAX,stdin);

    if (strlen(entry) > 1)
    {
      entry[strlen(entry)-1]='\0';
      if (!Si2146_SetFieldFromEntry(api, Si2146_propertyDictionary[propIndex].field[fieldIndex], entry))
      {
        printf("Invalid entry!\n");
      }
    }

    if (isRangeType)
      printf("<%d>\n\n", Si2146_GetValueFromField(api, Si2146_propertyDictionary[propIndex].field[fieldIndex]));
    else
      printf("<%s>\n\n", Si2146_GetEnumFromField (api, Si2146_propertyDictionary[propIndex].field[fieldIndex]));

  }

}

int   Si2146_setupProperties        (L1_Si2146_Context *api, Si2146_featureEnum feature)
{
  int propertyIndex;
  int dictSize;

  dictSize=sizeof(Si2146_propertyDictionary)/sizeof(Si2146_propertyInfoStruct);

  printf("\n%s properties:\n\n", Si2146_featureText[feature]);

  for (propertyIndex=0; propertyIndex<dictSize; propertyIndex++)
  {
    if (Si2146_propertyDictionary[propertyIndex].feature != feature) continue;
    Si2146_setupProperty(api, propertyIndex);
  }
  return 0;
}

#endif /* Si2146_COMMAND_LINE_APPLICATION */

/* _property_string_functions_insertion_start */
#ifdef    Si2146_COMMAND_LINE_APPLICATION
int Si2146_showCOMMONProperties    (L1_Si2146_Context *api)
{
  return Si2146_showProperties(api, Si2146_COMMON);
};

int Si2146_showDTVProperties       (L1_Si2146_Context *api)
{
  return Si2146_showProperties(api, Si2146_DTV);
};

int Si2146_showTUNERProperties     (L1_Si2146_Context *api)
{
  return Si2146_showProperties(api, Si2146_TUNER);
};

int Si2146_showAllProperties       (L1_Si2146_Context *api)
{
  Si2146_showCOMMONProperties    (api);
  Si2146_showDTVProperties       (api);
  Si2146_showTUNERProperties     (api);
  return 0;
};

#endif /* Si2146_COMMAND_LINE_APPLICATION */
void Si2146_setupCOMMONDefaults     (L1_Si2146_Context *api)
{
  SiTRACE("Si2146_setupCOMMONDefaults    \n");
  api->prop->crystal_trim.xo_cap                      =     8;
  api->prop->master_ien.tunien                        = Si2146_MASTER_IEN_PROP_TUNIEN_OFF;
  api->prop->master_ien.atvien                        = Si2146_MASTER_IEN_PROP_ATVIEN_OFF;
  api->prop->master_ien.dtvien                        = Si2146_MASTER_IEN_PROP_DTVIEN_OFF;
  api->prop->master_ien.errien                        = Si2146_MASTER_IEN_PROP_ERRIEN_OFF;
  api->prop->master_ien.ctsien                        = Si2146_MASTER_IEN_PROP_CTSIEN_OFF;
};

void Si2146_setupDTVDefaults        (L1_Si2146_Context *api)
{
  SiTRACE("Si2146_setupDTVDefaults       \n");
#ifdef LOAD_PATCH_11b3
  api->prop->dtv_agc_freeze_input.level               = Si2146_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LOW  ; /* (default 'LOW') */
  api->prop->dtv_agc_freeze_input.pin                 = Si2146_DTV_AGC_FREEZE_INPUT_PROP_PIN_NONE   ; /* (default 'NONE') */
#endif
  api->prop->dtv_agc_speed.if_agc_speed               = Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
  api->prop->dtv_agc_speed.agc_decim                  = Si2146_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
  api->prop->dtv_config_if_port.dtv_out_type          = Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_IF1;
  api->prop->dtv_config_if_port.dtv_agc_source        =     0;
  api->prop->dtv_ext_agc.min_10mv                     =    50;
  api->prop->dtv_ext_agc.max_10mv                     =   200;
  api->prop->dtv_ien.chlien                           = Si2146_DTV_IEN_PROP_CHLIEN_ENABLE;
  api->prop->dtv_initial_agc_speed.if_agc_speed       = Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
  api->prop->dtv_initial_agc_speed.agc_decim          = Si2146_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_OFF;
  api->prop->dtv_initial_agc_speed_period.period      =     0;
  api->prop->dtv_int_sense.chlnegen                   = Si2146_DTV_INT_SENSE_PROP_CHLNEGEN_DISABLE;
  api->prop->dtv_int_sense.chlposen                   = Si2146_DTV_INT_SENSE_PROP_CHLPOSEN_ENABLE;
  api->prop->dtv_lif_freq.offset                      =  5000;
  api->prop->dtv_lif_out.offset                       =   148;
  api->prop->dtv_lif_out.amp                          =    27;
  api->prop->dtv_mode.bw                              = Si2146_DTV_MODE_PROP_BW_BW_8MHZ;
  api->prop->dtv_mode.modulation                      = Si2146_DTV_MODE_PROP_MODULATION_DVBT;
  api->prop->dtv_mode.invert_spectrum                 =     0;
  api->prop->dtv_rf_top.dtv_rf_top                    = Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP_AUTO;
  api->prop->dtv_rsq_rssi_threshold.lo                =   -80;
  api->prop->dtv_rsq_rssi_threshold.hi                =     0;
};

void Si2146_setupTUNERDefaults      (L1_Si2146_Context *api)
{
  SiTRACE("Si2146_setupTUNERDefaults     \n");
  api->prop->tuner_blocked_vco.vco_code               = 0x8000; /* (default 0x8000) */

  api->prop->tuner_ien.tcien                          = Si2146_TUNER_IEN_PROP_TCIEN_ENABLE    ; /* (default 'DISABLE') */
  api->prop->tuner_ien.rssilien                       = Si2146_TUNER_IEN_PROP_RSSILIEN_DISABLE ; /* (default 'DISABLE') */
  api->prop->tuner_ien.rssihien                       = Si2146_TUNER_IEN_PROP_RSSIHIEN_DISABLE ; /* (default 'DISABLE') */

  api->prop->tuner_int_sense.tcnegen                  = Si2146_TUNER_INT_SENSE_PROP_TCNEGEN_DISABLE    ; /* (default 'DISABLE') */
  api->prop->tuner_int_sense.rssilnegen               = Si2146_TUNER_INT_SENSE_PROP_RSSILNEGEN_DISABLE ; /* (default 'DISABLE') */
  api->prop->tuner_int_sense.rssihnegen               = Si2146_TUNER_INT_SENSE_PROP_RSSIHNEGEN_DISABLE ; /* (default 'DISABLE') */
  api->prop->tuner_int_sense.tcposen                  = Si2146_TUNER_INT_SENSE_PROP_TCPOSEN_ENABLE     ; /* (default 'ENABLE') */
  api->prop->tuner_int_sense.rssilposen               = Si2146_TUNER_INT_SENSE_PROP_RSSILPOSEN_ENABLE  ; /* (default 'ENABLE') */
  api->prop->tuner_int_sense.rssihposen               = Si2146_TUNER_INT_SENSE_PROP_RSSIHPOSEN_ENABLE  ; /* (default 'ENABLE') */

  api->prop->tuner_lo_injection.band_1                = Si2146_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE ; /* (default 'HIGH_SIDE') */
  api->prop->tuner_lo_injection.band_2                = Si2146_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE  ; /* (default 'LOW_SIDE') */
  api->prop->tuner_lo_injection.band_3                = Si2146_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE  ; /* (default 'LOW_SIDE') */
  api->prop->tuner_lo_injection.band_4                = Si2146_TUNER_LO_INJECTION_PROP_BAND_4_LOW_SIDE  ; /* (default 'LOW_SIDE') */
  api->prop->tuner_lo_injection.band_5                = Si2146_TUNER_LO_INJECTION_PROP_BAND_5_LOW_SIDE  ; /* (default 'LOW_SIDE') */

};

void Si2146_setupAllDefaults        (L1_Si2146_Context *api)
{
  Si2146_setupCOMMONDefaults    (api);
  Si2146_setupDTVDefaults       (api);
  Si2146_setupTUNERDefaults     (api);
};

int Si2146_setupCOMMONProperties    (L1_Si2146_Context *api)
{
  SiTRACE("Si2146_setupCOMMONProperties    \n");
#ifdef    Si2146_COMMAND_LINE_APPLICATION
  Si2146_setupProperties(api, Si2146_COMMON);
#else  /* Si2146_COMMAND_LINE_APPLICATION */
  Si2146_setupCOMMONDefaults(api);
#endif /* Si2146_COMMAND_LINE_APPLICATION */
  return 0;
};

int Si2146_setupDTVProperties       (L1_Si2146_Context *api)
{
  SiTRACE("Si2146_setupDTVProperties       \n");
#ifdef    Si2146_COMMAND_LINE_APPLICATION
  Si2146_setupProperties(api, Si2146_DTV);
#else  /* Si2146_COMMAND_LINE_APPLICATION */
  Si2146_setupDTVDefaults(api);
#endif /* Si2146_COMMAND_LINE_APPLICATION */
  return 0;
};

int Si2146_setupTUNERProperties     (L1_Si2146_Context *api)
{
  SiTRACE("Si2146_setupTUNERProperties     \n");
#ifdef    Si2146_COMMAND_LINE_APPLICATION
  Si2146_setupProperties(api, Si2146_TUNER);
#else  /* Si2146_COMMAND_LINE_APPLICATION */
  Si2146_setupTUNERDefaults(api);
#endif /* Si2146_COMMAND_LINE_APPLICATION */
  return 0;
};

int Si2146_setupAllProperties       (L1_Si2146_Context *api)
{
  Si2146_setupCOMMONProperties    (api);
  Si2146_setupDTVProperties       (api);
  Si2146_setupTUNERProperties     (api);
  return 0;
};


 /*****************************************************************************************
 NAME: Si2146_downloadCOMMONProperties
  DESCRIPTION: Setup Si2146 COMMON properties configuration
  This function will download all the COMMON configuration properties.
  The function SetupCOMMONDefaults() should be called before the first call to this function.
  Parameter:  Pointer to Si2146 Context
  Returns:    I2C transaction error code, NO_Si2146_ERROR if successful
  Programming Guide Reference:    COMMON setup flowchart
******************************************************************************************/
int Si2146_downloadCOMMONProperties(L1_Si2146_Context *api)
{
  SiTRACE("Si2146_downloadCOMMONProperties     \n");
#ifdef    Si2146_CRYSTAL_TRIM_PROP
  if (Si2146_L1_SetProperty2(api, Si2146_CRYSTAL_TRIM_PROP_CODE                ) != NO_Si2146_ERROR) {return ERROR_Si2146_SENDING_COMMAND;}
#endif /* Si2146_CRYSTAL_TRIM_PROP */
#ifdef    Si2146_MASTER_IEN_PROP
  if (Si2146_L1_SetProperty2(api, Si2146_MASTER_IEN_PROP_CODE                  ) != NO_Si2146_ERROR) {return ERROR_Si2146_SENDING_COMMAND;}
#endif /* Si2146_MASTER_IEN_PROP */
return NO_Si2146_ERROR;
};

 /*****************************************************************************************
 NAME: Si2146_downloadDTVProperties
  DESCRIPTION: Setup Si2146 DTV properties configuration
  This function will download all the DTV configuration properties.
  The function SetupDTVDefaults() should be called before the first call to this function.
  Parameter:  Pointer to Si2146 Context
  Returns:    I2C transaction error code, NO_Si2146_ERROR if successful
  Programming Guide Reference:    DTV setup flowchart
******************************************************************************************/
int Si2146_downloadDTVProperties(L1_Si2146_Context *api)
{
  SiTRACE("Si2146_downloadDTVProperties                  \n");
#ifdef    Si2146_DTV_AGC_FREEZE_INPUT_PROP
  if (Si2146_L1_SetProperty2(api, Si2146_DTV_AGC_FREEZE_INPUT_PROP_CODE        ) != NO_Si2146_ERROR) {return ERROR_Si2146_SENDING_COMMAND;}
#endif /* Si2146_DTV_AGC_FREEZE_INPUT_PROP */
#ifdef    Si2146_DTV_AGC_SPEED_PROP
  if (Si2146_L1_SetProperty2(api, Si2146_DTV_AGC_SPEED_PROP_CODE               ) != NO_Si2146_ERROR) {return ERROR_Si2146_SENDING_COMMAND;}
#endif /* Si2146_DTV_AGC_SPEED_PROP */
#ifdef    Si2146_DTV_CONFIG_IF_PORT_PROP
  if (Si2146_L1_SetProperty2(api, Si2146_DTV_CONFIG_IF_PORT_PROP_CODE          ) != NO_Si2146_ERROR) {return ERROR_Si2146_SENDING_COMMAND;}
#endif /* Si2146_DTV_CONFIG_IF_PORT_PROP */
#ifdef    Si2146_DTV_EXT_AGC_PROP
  if (Si2146_L1_SetProperty2(api, Si2146_DTV_EXT_AGC_PROP_CODE                 ) != NO_Si2146_ERROR) {return ERROR_Si2146_SENDING_COMMAND;}
#endif /* Si2146_DTV_EXT_AGC_PROP */
#ifdef    Si2146_DTV_IEN_PROP
  if (Si2146_L1_SetProperty2(api, Si2146_DTV_IEN_PROP_CODE                     ) != NO_Si2146_ERROR) {return ERROR_Si2146_SENDING_COMMAND;}
#endif /* Si2146_DTV_IEN_PROP */
#ifdef    Si2146_DTV_INITIAL_AGC_SPEED_PROP
  if (Si2146_L1_SetProperty2(api, Si2146_DTV_INITIAL_AGC_SPEED_PROP_CODE       ) != NO_Si2146_ERROR) {return ERROR_Si2146_SENDING_COMMAND;}
#endif /* Si2146_DTV_INITIAL_AGC_SPEED_PROP */
#ifdef    Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
  if (Si2146_L1_SetProperty2(api, Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE) != NO_Si2146_ERROR) {return ERROR_Si2146_SENDING_COMMAND;}
#endif /* Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
#ifdef    Si2146_DTV_INT_SENSE_PROP
  if (Si2146_L1_SetProperty2(api, Si2146_DTV_INT_SENSE_PROP_CODE               ) != NO_Si2146_ERROR) {return ERROR_Si2146_SENDING_COMMAND;}
#endif /* Si2146_DTV_INT_SENSE_PROP */
#ifdef    Si2146_DTV_LIF_FREQ_PROP
  if (Si2146_L1_SetProperty2(api, Si2146_DTV_LIF_FREQ_PROP_CODE                ) != NO_Si2146_ERROR) {return ERROR_Si2146_SENDING_COMMAND;}
#endif /* Si2146_DTV_LIF_FREQ_PROP */
#ifdef    Si2146_DTV_LIF_OUT_PROP
  if (Si2146_L1_SetProperty2(api, Si2146_DTV_LIF_OUT_PROP_CODE                 ) != NO_Si2146_ERROR) {return ERROR_Si2146_SENDING_COMMAND;}
#endif /* Si2146_DTV_LIF_OUT_PROP */
#ifdef    Si2146_DTV_MODE_PROP
  if (Si2146_L1_SetProperty2(api, Si2146_DTV_MODE_PROP_CODE                    ) != NO_Si2146_ERROR) {return ERROR_Si2146_SENDING_COMMAND;}
#endif /* Si2146_DTV_MODE_PROP */
#ifdef    Si2146_DTV_RF_TOP_PROP
  if (Si2146_L1_SetProperty2(api, Si2146_DTV_RF_TOP_PROP_CODE                  ) != NO_Si2146_ERROR) {return ERROR_Si2146_SENDING_COMMAND;}
#endif /* Si2146_DTV_RF_TOP_PROP */
#ifdef    Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP
  if (Si2146_L1_SetProperty2(api, Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_CODE      ) != NO_Si2146_ERROR) {return ERROR_Si2146_SENDING_COMMAND;}
#endif /* Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP */
return NO_Si2146_ERROR;
};

 /*****************************************************************************************
 NAME: Si2146_downloadTUNERProperties
  DESCRIPTION: Setup Si2146 TUNER properties configuration
  This function will download all the TUNER configuration properties.
  The function SetupTUNERDefaults() should be called before the first call to this function.
  Parameter:  Pointer to Si2146 Context
  Returns:    I2C transaction error code, NO_Si2146_ERROR if successful
  Programming Guide Reference:    TUNER setup flowchart
******************************************************************************************/
int Si2146_downloadTUNERProperties(L1_Si2146_Context *api)
{
  SiTRACE("Si2146_downloadTUNERProperties      \n");
#ifdef    Si2146_TUNER_BLOCKED_VCO_PROP
  if (Si2146_L1_SetProperty2(api, Si2146_TUNER_BLOCKED_VCO_PROP_CODE           ) != NO_Si2146_ERROR) {return ERROR_Si2146_SENDING_COMMAND;}
#endif /* Si2146_TUNER_BLOCKED_VCO_PROP */
#ifdef    Si2146_TUNER_IEN_PROP
  if (Si2146_L1_SetProperty2(api, Si2146_TUNER_IEN_PROP_CODE                   ) != NO_Si2146_ERROR) {return ERROR_Si2146_SENDING_COMMAND;}
#endif /* Si2146_TUNER_IEN_PROP */
#ifdef    Si2146_TUNER_INT_SENSE_PROP
  if (Si2146_L1_SetProperty2(api, Si2146_TUNER_INT_SENSE_PROP_CODE             ) != NO_Si2146_ERROR) {return ERROR_Si2146_SENDING_COMMAND;}
#endif /* Si2146_TUNER_INT_SENSE_PROP */
#ifdef    Si2146_TUNER_LO_INJECTION_PROP
  if (Si2146_L1_SetProperty2(api, Si2146_TUNER_LO_INJECTION_PROP_CODE          ) != NO_Si2146_ERROR) {return ERROR_Si2146_SENDING_COMMAND;}
#endif /* Si2146_TUNER_LO_INJECTION_PROP */
return NO_Si2146_ERROR;
};
int Si2146_downloadAllProperties       (L1_Si2146_Context *api)
{
  Si2146_downloadCOMMONProperties    (api);
  Si2146_downloadDTVProperties       (api);
  Si2146_downloadTUNERProperties     (api);
  return 0;
};

/* _property_string_functions_insertion_point */








