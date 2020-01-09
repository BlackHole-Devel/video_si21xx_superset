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
   FILE: Si2177_User_Properties.c
   Supported IC : Si2177
   Compiled for ROM 50 firmware 3_1_build_3
   Revision: 0.1
   Tag:  ROM50_3_1_build_3_V0.1
   Date: June 30 2015
**************************************************************************************/
#include "Si2177_L1_API.h"

/***********************************************************************************************************************
  Si2177_storeUserProperties function
  Use:        property preparation function
              Used to fill the prop structure with user values.
  Parameter: *prop    a property structure to be filled

  Returns:    void
 ***********************************************************************************************************************/
void          Si2177_storeUserProperties    (Si2177_PropObj   *prop) {
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
