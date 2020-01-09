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


   API properties definitions
   FILE: Si2141_L1_Properties.c
   Supported IC : Si2141
   Compiled for ROM 61 firmware 1_1_build_12
   Revision: 0.5
   Tag:  ROM61_1_1_build_12_V0.5
   Date: June 14 2019
**************************************************************************************/
#define   Si2141_COMMAND_PROTOTYPES

#include "Si2141_L1_API.h"


/***********************************************************************************************************************
  Si2141_storeUserProperties function
  Use:        property preparation function
              Used to fill the prop structure with user values.
  Parameter: *prop    a property structure to be filled

  Returns:    void
 ***********************************************************************************************************************/
void          Si2141_storeUserProperties    (Si2141_PropObj   *prop) {
#ifdef    Si2141_CRYSTAL_TRIM_PROP
  prop->crystal_trim.xo_cap                            = Si2141_CRYSTAL_TRIM_PROP_XO_CAP_6P7PF ; /* (default '6p7pF') */
#endif /* Si2141_CRYSTAL_TRIM_PROP */

#ifdef    Si2141_XOUT_PROP
  prop->xout.amp                                       = Si2141_XOUT_PROP_AMP_HIGH ; /* (default 'HIGH') */
#endif /* Si2141_XOUT_PROP */

#ifdef    Si2141_DTV_AGC_AUTO_FREEZE_PROP
  prop->dtv_agc_auto_freeze.thld                       =   255; /* (default   255) */
  prop->dtv_agc_auto_freeze.timeout                    =     1; /* (default     1) */
#endif /* Si2141_DTV_AGC_AUTO_FREEZE_PROP */

#ifdef    Si2141_DTV_AGC_SPEED_PROP
  prop->dtv_agc_speed.if_agc_speed                     = Si2141_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO ; /* (default 'AUTO') */
  prop->dtv_agc_speed.agc_decim                        = Si2141_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF     ; /* (default 'OFF') */
#endif /* Si2141_DTV_AGC_SPEED_PROP */

#ifdef    Si2141_DTV_CONFIG_IF_PORT_PROP
  prop->dtv_config_if_port.dtv_out_type                = Si2141_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_IF ; /* (default 'LIF_IF') */
#endif /* Si2141_DTV_CONFIG_IF_PORT_PROP */

#ifdef    Si2141_DTV_EXT_AGC_PROP
  prop->dtv_ext_agc.min_10mv                           =    50; /* (default    50) */
  prop->dtv_ext_agc.max_10mv                           =   200; /* (default   200) */
#endif /* Si2141_DTV_EXT_AGC_PROP */

#ifdef    Si2141_DTV_IF_AGC_SPEED_PROP
  prop->dtv_if_agc_speed.attack                        = Si2141_DTV_IF_AGC_SPEED_PROP_ATTACK_AUTO ; /* (default 'AUTO') */
  prop->dtv_if_agc_speed.decay                         = Si2141_DTV_IF_AGC_SPEED_PROP_DECAY_AUTO  ; /* (default 'AUTO') */
#endif /* Si2141_DTV_IF_AGC_SPEED_PROP */

#ifdef    Si2141_DTV_INITIAL_AGC_SPEED_PROP
  prop->dtv_initial_agc_speed.if_agc_speed             = Si2141_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO ; /* (default 'AUTO') */
  prop->dtv_initial_agc_speed.agc_decim                = Si2141_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_OFF     ; /* (default 'OFF') */
#endif /* Si2141_DTV_INITIAL_AGC_SPEED_PROP */

#ifdef    Si2141_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
  prop->dtv_initial_agc_speed_period.period            =     0; /* (default     0) */
#endif /* Si2141_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */

#ifdef    Si2141_DTV_INTERNAL_ZIF_PROP
  prop->dtv_internal_zif.atsc                          = Si2141_DTV_INTERNAL_ZIF_PROP_ATSC_ZIF   ; /* (default 'ZIF') */
  prop->dtv_internal_zif.qam_us                        = Si2141_DTV_INTERNAL_ZIF_PROP_QAM_US_ZIF ; /* (default 'ZIF') */
  prop->dtv_internal_zif.dvbt                          = Si2141_DTV_INTERNAL_ZIF_PROP_DVBT_ZIF   ; /* (default 'ZIF') */
  prop->dtv_internal_zif.dvbc                          = Si2141_DTV_INTERNAL_ZIF_PROP_DVBC_ZIF   ; /* (default 'ZIF') */
  prop->dtv_internal_zif.isdbt                         = Si2141_DTV_INTERNAL_ZIF_PROP_ISDBT_ZIF  ; /* (default 'ZIF') */
  prop->dtv_internal_zif.isdbc                         = Si2141_DTV_INTERNAL_ZIF_PROP_ISDBC_ZIF  ; /* (default 'ZIF') */
  prop->dtv_internal_zif.dtmb                          = Si2141_DTV_INTERNAL_ZIF_PROP_DTMB_LIF   ; /* (default 'LIF') */
#endif /* Si2141_DTV_INTERNAL_ZIF_PROP */

#ifdef    Si2141_DTV_LIF_FREQ_PROP
  prop->dtv_lif_freq.offset                            =  5000; /* (default  5000) */
#endif /* Si2141_DTV_LIF_FREQ_PROP */

#ifdef    Si2141_DTV_LIF_OUT_PROP
  prop->dtv_lif_out.offset                             =   148; /* (default   148) */
  prop->dtv_lif_out.amp                                =    27; /* (default    27) */
#endif /* Si2141_DTV_LIF_OUT_PROP */

#ifdef    Si2141_DTV_MODE_PROP
  prop->dtv_mode.bw                                    = Si2141_DTV_MODE_PROP_BW_BW_8MHZ              ; /* (default 'BW_8MHZ') */
  prop->dtv_mode.modulation                            = Si2141_DTV_MODE_PROP_MODULATION_DVBT         ; /* (default 'DVBT') */
  prop->dtv_mode.invert_spectrum                       = Si2141_DTV_MODE_PROP_INVERT_SPECTRUM_NORMAL  ; /* (default 'NORMAL') */
#endif /* Si2141_DTV_MODE_PROP */

#ifdef    Si2141_DTV_PGA_LIMITS_PROP
  prop->dtv_pga_limits.min                             =    -1; /* (default    -1) */
  prop->dtv_pga_limits.max                             =    -1; /* (default    -1) */
#endif /* Si2141_DTV_PGA_LIMITS_PROP */

#ifdef    Si2141_DTV_PGA_TARGET_PROP
  prop->dtv_pga_target.pga_target                      =     0; /* (default     0) */
  prop->dtv_pga_target.override_enable                 = Si2141_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_DISABLE ; /* (default 'DISABLE') */
#endif /* Si2141_DTV_PGA_TARGET_PROP */

#ifdef    Si2141_DTV_RF_AGC_SPEED_PROP
  prop->dtv_rf_agc_speed.attack                        = Si2141_DTV_RF_AGC_SPEED_PROP_ATTACK_AUTO ; /* (default 'AUTO') */
  prop->dtv_rf_agc_speed.decay                         = Si2141_DTV_RF_AGC_SPEED_PROP_DECAY_AUTO  ; /* (default 'AUTO') */
#endif /* Si2141_DTV_RF_AGC_SPEED_PROP */

#ifdef    Si2141_DTV_RF_TOP_PROP
  prop->dtv_rf_top.dtv_rf_top                          = Si2141_DTV_RF_TOP_PROP_DTV_RF_TOP_AUTO ; /* (default 'AUTO') */
#endif /* Si2141_DTV_RF_TOP_PROP */

#ifdef    Si2141_DTV_RSQ_RSSI_THRESHOLD_PROP
  prop->dtv_rsq_rssi_threshold.lo                      =   -80; /* (default   -80) */
#endif /* Si2141_DTV_RSQ_RSSI_THRESHOLD_PROP */

#ifdef    Si2141_DTV_WB_AGC_SPEED_PROP
  prop->dtv_wb_agc_speed.attack                        = Si2141_DTV_WB_AGC_SPEED_PROP_ATTACK_AUTO ; /* (default 'AUTO') */
  prop->dtv_wb_agc_speed.decay                         = Si2141_DTV_WB_AGC_SPEED_PROP_DECAY_AUTO  ; /* (default 'AUTO') */
#endif /* Si2141_DTV_WB_AGC_SPEED_PROP */

#ifdef    Si2141_TUNER_BLOCKED_VCO_PROP
  /* prop->tuner_blocked_vco.vco_code                  = 0x8000; */ /* (default 0x8000) */
#endif /* Si2141_TUNER_BLOCKED_VCO_PROP */

#ifdef    Si2141_TUNER_BLOCKED_VCO2_PROP
  /* prop->tuner_blocked_vco2.vco_code                 = 0x8000; */ /* (default 0x8000) */
#endif /* Si2141_TUNER_BLOCKED_VCO2_PROP */

#ifdef    Si2141_TUNER_BLOCKED_VCO3_PROP
  /* prop->tuner_blocked_vco3.vco_code                 = 0x8000; */ /* (default 0x8000) */
#endif /* Si2141_TUNER_BLOCKED_VCO3_PROP */

#ifdef    Si2141_TUNER_LO_INJECTION_PROP
  prop->tuner_lo_injection.band_1                      = Si2141_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE ; /* (default 'HIGH_SIDE') */
  prop->tuner_lo_injection.band_2                      = Si2141_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE  ; /* (default 'LOW_SIDE') */
  prop->tuner_lo_injection.band_3                      = Si2141_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE  ; /* (default 'LOW_SIDE') */
#endif /* Si2141_TUNER_LO_INJECTION_PROP */

#ifdef    Si2141_TUNER_RETURN_LOSS_PROP
  prop->tuner_return_loss.config                       = Si2141_TUNER_RETURN_LOSS_PROP_CONFIG_127         ; /* (default '127') */
  prop->tuner_return_loss.mode                         = Si2141_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL   ; /* (default 'TERRESTRIAL') */
  prop->tuner_return_loss.reserved                     = Si2141_TUNER_RETURN_LOSS_PROP_RESERVED_RESERVED    ; /* (default 'RESERVED') */
#endif /* Si2141_TUNER_RETURN_LOSS_PROP */

#ifdef    Si2141_TUNER_TF1_BOUNDARY_OFFSET_PROP
  prop->tuner_tf1_boundary_offset.tf1_boundary_offset  =     0; /* (default     0) */
#endif /* Si2141_TUNER_TF1_BOUNDARY_OFFSET_PROP */

#ifdef    Si2141_WIDE_BAND_ATT_THRS_PROP
  prop->wide_band_att_thrs.wb_att_thrs                 = Si2141_WIDE_BAND_ATT_THRS_PROP_WB_ATT_THRS_AUTO ; /* (default 'AUTO') */
#endif /* Si2141_WIDE_BAND_ATT_THRS_PROP */
}
