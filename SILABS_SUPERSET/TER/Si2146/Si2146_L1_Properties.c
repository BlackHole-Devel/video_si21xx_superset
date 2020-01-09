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
   API properties definitions
   FILE: Si2146_L1_Properties.c
   Supported IC : Si2146
   Compiled for ROM 11 firmware 1_1_build_3
   Revision: 0.1
   Tag:  TAGNAME
   Date: December 23 2011
**************************************************************************************/
#define   Si2146_COMMAND_PROTOTYPES

#include "Si2146_L1_API.h"

/***********************************************************************************************************************
  Si2146_L1_SetProperty function
  Use:        property set function
              Used to call L1_SET_PROPERTY with the property Id and data provided.
  Parameter: *api     the Si2146 context
  Parameter: prop     the property Id
  Parameter: data     the property bytes
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
unsigned char Si2146_L1_SetProperty(L1_Si2146_Context *api, unsigned int prop, int  data)  {
    unsigned char  reserved          = 0;
    return Si2146_L1_SET_PROPERTY (api, reserved, prop, data);
}

/***********************************************************************************************************************
  Si2146_L1_GetProperty function
  Use:        property get function
              Used to call L1_GET_PROPERTY with the property Id provided.
  Parameter: *api     the Si2146 context
  Parameter: prop     the property Id
  Parameter: *data    a buffer to store the property bytes into
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
unsigned char    Si2146_L1_GetProperty(L1_Si2146_Context *api, unsigned int prop, int *data) {
    unsigned char  reserved          = 0;
    unsigned char res;
    res = Si2146_L1_GET_PROPERTY (api, reserved, prop);
    *data = api->rsp->get_property.data;
    return res;
}

/* _set_property2_insertion_start */

  /* --------------------------------------------*/
  /* SET_PROPERTY2 FUNCTION                      */
  /* --------------------------------------------*/
unsigned char Si2146_L1_SetProperty2(L1_Si2146_Context *api, unsigned int prop_code) {
    int data;
#ifdef    Si2146_GET_PROPERTY_STRING
    char msg[1000];
#endif /* Si2146_GET_PROPERTY_STRING */
    switch (prop_code) {
    #ifdef        Si2146_ATV_AFC_RANGE_PROP
     case         Si2146_ATV_AFC_RANGE_PROP_CODE:
       data = (api->prop->atv_afc_range.range_khz & Si2146_ATV_AFC_RANGE_PROP_RANGE_KHZ_MASK) << Si2146_ATV_AFC_RANGE_PROP_RANGE_KHZ_LSB ;
     break;
    #endif /*     Si2146_ATV_AFC_RANGE_PROP */
    #ifdef        Si2146_ATV_AF_OUT_PROP
     case         Si2146_ATV_AF_OUT_PROP_CODE:
       data = (api->prop->atv_af_out.volume & Si2146_ATV_AF_OUT_PROP_VOLUME_MASK) << Si2146_ATV_AF_OUT_PROP_VOLUME_LSB ;
     break;
    #endif /*     Si2146_ATV_AF_OUT_PROP */
    #ifdef        Si2146_ATV_AGC_SPEED_PROP
     case         Si2146_ATV_AGC_SPEED_PROP_CODE:
       data = (api->prop->atv_agc_speed.if_agc_speed & Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK) << Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB ;
     break;
    #endif /*     Si2146_ATV_AGC_SPEED_PROP */
    #ifdef        Si2146_ATV_AUDIO_MODE_PROP
     case         Si2146_ATV_AUDIO_MODE_PROP_CODE:
       data = (api->prop->atv_audio_mode.audio_sys  & Si2146_ATV_AUDIO_MODE_PROP_AUDIO_SYS_MASK ) << Si2146_ATV_AUDIO_MODE_PROP_AUDIO_SYS_LSB  |
              (api->prop->atv_audio_mode.demod_mode & Si2146_ATV_AUDIO_MODE_PROP_DEMOD_MODE_MASK) << Si2146_ATV_AUDIO_MODE_PROP_DEMOD_MODE_LSB  |
              (api->prop->atv_audio_mode.chan_bw    & Si2146_ATV_AUDIO_MODE_PROP_CHAN_BW_MASK   ) << Si2146_ATV_AUDIO_MODE_PROP_CHAN_BW_LSB ;
     break;
    #endif /*     Si2146_ATV_AUDIO_MODE_PROP */
    #ifdef        Si2146_ATV_CVBS_OUT_PROP
     case         Si2146_ATV_CVBS_OUT_PROP_CODE:
       data = (api->prop->atv_cvbs_out.offset & Si2146_ATV_CVBS_OUT_PROP_OFFSET_MASK) << Si2146_ATV_CVBS_OUT_PROP_OFFSET_LSB  |
              (api->prop->atv_cvbs_out.amp    & Si2146_ATV_CVBS_OUT_PROP_AMP_MASK   ) << Si2146_ATV_CVBS_OUT_PROP_AMP_LSB ;
     break;
    #endif /*     Si2146_ATV_CVBS_OUT_PROP */
    #ifdef        Si2146_ATV_CVBS_OUT_FINE_PROP
     case         Si2146_ATV_CVBS_OUT_FINE_PROP_CODE:
       data = (api->prop->atv_cvbs_out_fine.offset & Si2146_ATV_CVBS_OUT_FINE_PROP_OFFSET_MASK) << Si2146_ATV_CVBS_OUT_FINE_PROP_OFFSET_LSB  |
              (api->prop->atv_cvbs_out_fine.amp    & Si2146_ATV_CVBS_OUT_FINE_PROP_AMP_MASK   ) << Si2146_ATV_CVBS_OUT_FINE_PROP_AMP_LSB ;
     break;
    #endif /*     Si2146_ATV_CVBS_OUT_FINE_PROP */
    #ifdef        Si2146_ATV_IEN_PROP
     case         Si2146_ATV_IEN_PROP_CODE:
       data = (api->prop->atv_ien.chlien  & Si2146_ATV_IEN_PROP_CHLIEN_MASK ) << Si2146_ATV_IEN_PROP_CHLIEN_LSB  |
              (api->prop->atv_ien.pclien  & Si2146_ATV_IEN_PROP_PCLIEN_MASK ) << Si2146_ATV_IEN_PROP_PCLIEN_LSB  |
              (api->prop->atv_ien.dlien   & Si2146_ATV_IEN_PROP_DLIEN_MASK  ) << Si2146_ATV_IEN_PROP_DLIEN_LSB  |
              (api->prop->atv_ien.snrlien & Si2146_ATV_IEN_PROP_SNRLIEN_MASK) << Si2146_ATV_IEN_PROP_SNRLIEN_LSB  |
              (api->prop->atv_ien.snrhien & Si2146_ATV_IEN_PROP_SNRHIEN_MASK) << Si2146_ATV_IEN_PROP_SNRHIEN_LSB ;
     break;
    #endif /*     Si2146_ATV_IEN_PROP */
    #ifdef        Si2146_ATV_INT_SENSE_PROP
     case         Si2146_ATV_INT_SENSE_PROP_CODE:
       data = (api->prop->atv_int_sense.chlnegen  & Si2146_ATV_INT_SENSE_PROP_CHLNEGEN_MASK ) << Si2146_ATV_INT_SENSE_PROP_CHLNEGEN_LSB  |
              (api->prop->atv_int_sense.pclnegen  & Si2146_ATV_INT_SENSE_PROP_PCLNEGEN_MASK ) << Si2146_ATV_INT_SENSE_PROP_PCLNEGEN_LSB  |
              (api->prop->atv_int_sense.dlnegen   & Si2146_ATV_INT_SENSE_PROP_DLNEGEN_MASK  ) << Si2146_ATV_INT_SENSE_PROP_DLNEGEN_LSB  |
              (api->prop->atv_int_sense.snrlnegen & Si2146_ATV_INT_SENSE_PROP_SNRLNEGEN_MASK) << Si2146_ATV_INT_SENSE_PROP_SNRLNEGEN_LSB  |
              (api->prop->atv_int_sense.snrhnegen & Si2146_ATV_INT_SENSE_PROP_SNRHNEGEN_MASK) << Si2146_ATV_INT_SENSE_PROP_SNRHNEGEN_LSB  |
              (api->prop->atv_int_sense.chlposen  & Si2146_ATV_INT_SENSE_PROP_CHLPOSEN_MASK ) << Si2146_ATV_INT_SENSE_PROP_CHLPOSEN_LSB  |
              (api->prop->atv_int_sense.pclposen  & Si2146_ATV_INT_SENSE_PROP_PCLPOSEN_MASK ) << Si2146_ATV_INT_SENSE_PROP_PCLPOSEN_LSB  |
              (api->prop->atv_int_sense.dlposen   & Si2146_ATV_INT_SENSE_PROP_DLPOSEN_MASK  ) << Si2146_ATV_INT_SENSE_PROP_DLPOSEN_LSB  |
              (api->prop->atv_int_sense.snrlposen & Si2146_ATV_INT_SENSE_PROP_SNRLPOSEN_MASK) << Si2146_ATV_INT_SENSE_PROP_SNRLPOSEN_LSB  |
              (api->prop->atv_int_sense.snrhposen & Si2146_ATV_INT_SENSE_PROP_SNRHPOSEN_MASK) << Si2146_ATV_INT_SENSE_PROP_SNRHPOSEN_LSB ;
     break;
    #endif /*     Si2146_ATV_INT_SENSE_PROP */
    #ifdef        Si2146_ATV_RF_TOP_PROP
     case         Si2146_ATV_RF_TOP_PROP_CODE:
       data = (api->prop->atv_rf_top.atv_rf_top & Si2146_ATV_RF_TOP_PROP_ATV_RF_TOP_MASK) << Si2146_ATV_RF_TOP_PROP_ATV_RF_TOP_LSB ;
     break;
    #endif /*     Si2146_ATV_RF_TOP_PROP */
    #ifdef        Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_CODE:
       data = (api->prop->atv_rsq_rssi_threshold.lo & Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK) << Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB  |
              (api->prop->atv_rsq_rssi_threshold.hi & Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK) << Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB ;
     break;
    #endif /*     Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2146_ATV_RSQ_SNR_THRESHOLD_PROP
     case         Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_CODE:
       data = (api->prop->atv_rsq_snr_threshold.lo & Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_LO_MASK) << Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_LO_LSB  |
              (api->prop->atv_rsq_snr_threshold.hi & Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_HI_MASK) << Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_HI_LSB ;
     break;
    #endif /*     Si2146_ATV_RSQ_SNR_THRESHOLD_PROP */
    #ifdef        Si2146_ATV_SIF_OUT_PROP
     case         Si2146_ATV_SIF_OUT_PROP_CODE:
       data = (api->prop->atv_sif_out.offset & Si2146_ATV_SIF_OUT_PROP_OFFSET_MASK) << Si2146_ATV_SIF_OUT_PROP_OFFSET_LSB  |
              (api->prop->atv_sif_out.amp    & Si2146_ATV_SIF_OUT_PROP_AMP_MASK   ) << Si2146_ATV_SIF_OUT_PROP_AMP_LSB ;
     break;
    #endif /*     Si2146_ATV_SIF_OUT_PROP */
    #ifdef        Si2146_ATV_SOUND_AGC_LIMIT_PROP
     case         Si2146_ATV_SOUND_AGC_LIMIT_PROP_CODE:
       data = (api->prop->atv_sound_agc_limit.max_gain & Si2146_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_MASK) << Si2146_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_LSB  |
              (api->prop->atv_sound_agc_limit.min_gain & Si2146_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_MASK) << Si2146_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_LSB ;
     break;
    #endif /*     Si2146_ATV_SOUND_AGC_LIMIT_PROP */
    #ifdef        Si2146_ATV_SOUND_AGC_SPEED_PROP
     case         Si2146_ATV_SOUND_AGC_SPEED_PROP_CODE:
       data = (api->prop->atv_sound_agc_speed.system_l      & Si2146_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_MASK     ) << Si2146_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_LSB  |
              (api->prop->atv_sound_agc_speed.other_systems & Si2146_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_MASK) << Si2146_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_LSB ;
     break;
    #endif /*     Si2146_ATV_SOUND_AGC_SPEED_PROP */
    #ifdef        Si2146_ATV_VIDEO_EQUALIZER_PROP
     case         Si2146_ATV_VIDEO_EQUALIZER_PROP_CODE:
       data = (api->prop->atv_video_equalizer.slope & Si2146_ATV_VIDEO_EQUALIZER_PROP_SLOPE_MASK) << Si2146_ATV_VIDEO_EQUALIZER_PROP_SLOPE_LSB ;
     break;
    #endif /*     Si2146_ATV_VIDEO_EQUALIZER_PROP */
    #ifdef        Si2146_ATV_VIDEO_MODE_PROP
     case         Si2146_ATV_VIDEO_MODE_PROP_CODE:
       data = (api->prop->atv_video_mode.video_sys       & Si2146_ATV_VIDEO_MODE_PROP_VIDEO_SYS_MASK      ) << Si2146_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LSB  |
              (api->prop->atv_video_mode.color           & Si2146_ATV_VIDEO_MODE_PROP_COLOR_MASK          ) << Si2146_ATV_VIDEO_MODE_PROP_COLOR_LSB  |
              (api->prop->atv_video_mode.trans           & Si2146_ATV_VIDEO_MODE_PROP_TRANS_MASK          ) << Si2146_ATV_VIDEO_MODE_PROP_TRANS_LSB  |
              (api->prop->atv_video_mode.invert_spectrum & Si2146_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_MASK) << Si2146_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_LSB  |
              (api->prop->atv_video_mode.invert_signal   & Si2146_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_MASK  ) << Si2146_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_LSB ;
     break;
    #endif /*     Si2146_ATV_VIDEO_MODE_PROP */
    #ifdef        Si2146_ATV_VSNR_CAP_PROP
     case         Si2146_ATV_VSNR_CAP_PROP_CODE:
       data = (api->prop->atv_vsnr_cap.atv_vsnr_cap & Si2146_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_MASK) << Si2146_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_LSB ;
     break;
    #endif /*     Si2146_ATV_VSNR_CAP_PROP */
    #ifdef        Si2146_ATV_VSYNC_TRACKING_PROP
     case         Si2146_ATV_VSYNC_TRACKING_PROP_CODE:
       data = (api->prop->atv_vsync_tracking.min_pulses_to_lock   & Si2146_ATV_VSYNC_TRACKING_PROP_MIN_PULSES_TO_LOCK_MASK  ) << Si2146_ATV_VSYNC_TRACKING_PROP_MIN_PULSES_TO_LOCK_LSB  |
              (api->prop->atv_vsync_tracking.min_fields_to_unlock & Si2146_ATV_VSYNC_TRACKING_PROP_MIN_FIELDS_TO_UNLOCK_MASK) << Si2146_ATV_VSYNC_TRACKING_PROP_MIN_FIELDS_TO_UNLOCK_LSB ;
     break;
    #endif /*     Si2146_ATV_VSYNC_TRACKING_PROP */
    #ifdef        Si2146_CRYSTAL_TRIM_PROP
     case         Si2146_CRYSTAL_TRIM_PROP_CODE:
       data = (api->prop->crystal_trim.xo_cap & Si2146_CRYSTAL_TRIM_PROP_XO_CAP_MASK) << Si2146_CRYSTAL_TRIM_PROP_XO_CAP_LSB ;
     break;
    #endif /*     Si2146_CRYSTAL_TRIM_PROP */
    #ifdef        Si2146_DTV_AGC_FREEZE_INPUT_PROP
     case         Si2146_DTV_AGC_FREEZE_INPUT_PROP_CODE:
       data = (api->prop->dtv_agc_freeze_input.level & Si2146_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_MASK) << Si2146_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LSB  |
              (api->prop->dtv_agc_freeze_input.pin   & Si2146_DTV_AGC_FREEZE_INPUT_PROP_PIN_MASK  ) << Si2146_DTV_AGC_FREEZE_INPUT_PROP_PIN_LSB ;
     break;
    #endif /*     Si2146_DTV_AGC_FREEZE_INPUT_PROP */
    #ifdef        Si2146_DTV_AGC_SPEED_PROP
     case         Si2146_DTV_AGC_SPEED_PROP_CODE:
       data = (api->prop->dtv_agc_speed.if_agc_speed & Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK) << Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB  |
              (api->prop->dtv_agc_speed.agc_decim    & Si2146_DTV_AGC_SPEED_PROP_AGC_DECIM_MASK   ) << Si2146_DTV_AGC_SPEED_PROP_AGC_DECIM_LSB ;
     break;
    #endif /*     Si2146_DTV_AGC_SPEED_PROP */
    #ifdef        Si2146_DTV_CONFIG_IF_PORT_PROP
     case         Si2146_DTV_CONFIG_IF_PORT_PROP_CODE:
       data = (api->prop->dtv_config_if_port.dtv_out_type   & Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_MASK  ) << Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LSB  |
              (api->prop->dtv_config_if_port.dtv_agc_source & Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_MASK) << Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_LSB ;
     break;
    #endif /*     Si2146_DTV_CONFIG_IF_PORT_PROP */
    #ifdef        Si2146_DTV_EXT_AGC_PROP
     case         Si2146_DTV_EXT_AGC_PROP_CODE:
       data = (api->prop->dtv_ext_agc.min_10mv & Si2146_DTV_EXT_AGC_PROP_MIN_10MV_MASK) << Si2146_DTV_EXT_AGC_PROP_MIN_10MV_LSB  |
              (api->prop->dtv_ext_agc.max_10mv & Si2146_DTV_EXT_AGC_PROP_MAX_10MV_MASK) << Si2146_DTV_EXT_AGC_PROP_MAX_10MV_LSB ;
     break;
    #endif /*     Si2146_DTV_EXT_AGC_PROP */
    #ifdef        Si2146_DTV_IEN_PROP
     case         Si2146_DTV_IEN_PROP_CODE:
       data = (api->prop->dtv_ien.chlien & Si2146_DTV_IEN_PROP_CHLIEN_MASK) << Si2146_DTV_IEN_PROP_CHLIEN_LSB ;
     break;
    #endif /*     Si2146_DTV_IEN_PROP */
    #ifdef        Si2146_DTV_INITIAL_AGC_SPEED_PROP
     case         Si2146_DTV_INITIAL_AGC_SPEED_PROP_CODE:
       data = (api->prop->dtv_initial_agc_speed.if_agc_speed & Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_MASK) << Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_LSB  |
              (api->prop->dtv_initial_agc_speed.agc_decim    & Si2146_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_MASK   ) << Si2146_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_LSB ;
     break;
    #endif /*     Si2146_DTV_INITIAL_AGC_SPEED_PROP */
    #ifdef        Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
     case         Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE:
       data = (api->prop->dtv_initial_agc_speed_period.period & Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_MASK) << Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_LSB ;
     break;
    #endif /*     Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
    #ifdef        Si2146_DTV_INT_SENSE_PROP
     case         Si2146_DTV_INT_SENSE_PROP_CODE:
       data = (api->prop->dtv_int_sense.chlnegen & Si2146_DTV_INT_SENSE_PROP_CHLNEGEN_MASK) << Si2146_DTV_INT_SENSE_PROP_CHLNEGEN_LSB  |
              (api->prop->dtv_int_sense.chlposen & Si2146_DTV_INT_SENSE_PROP_CHLPOSEN_MASK) << Si2146_DTV_INT_SENSE_PROP_CHLPOSEN_LSB ;
     break;
    #endif /*     Si2146_DTV_INT_SENSE_PROP */
    #ifdef        Si2146_DTV_LIF_FREQ_PROP
     case         Si2146_DTV_LIF_FREQ_PROP_CODE:
       data = (api->prop->dtv_lif_freq.offset & Si2146_DTV_LIF_FREQ_PROP_OFFSET_MASK) << Si2146_DTV_LIF_FREQ_PROP_OFFSET_LSB ;
     break;
    #endif /*     Si2146_DTV_LIF_FREQ_PROP */
    #ifdef        Si2146_DTV_LIF_OUT_PROP
     case         Si2146_DTV_LIF_OUT_PROP_CODE:
       data = (api->prop->dtv_lif_out.offset & Si2146_DTV_LIF_OUT_PROP_OFFSET_MASK) << Si2146_DTV_LIF_OUT_PROP_OFFSET_LSB  |
              (api->prop->dtv_lif_out.amp    & Si2146_DTV_LIF_OUT_PROP_AMP_MASK   ) << Si2146_DTV_LIF_OUT_PROP_AMP_LSB ;
     break;
    #endif /*     Si2146_DTV_LIF_OUT_PROP */
    #ifdef        Si2146_DTV_MODE_PROP
     case         Si2146_DTV_MODE_PROP_CODE:
       data = (api->prop->dtv_mode.bw              & Si2146_DTV_MODE_PROP_BW_MASK             ) << Si2146_DTV_MODE_PROP_BW_LSB  |
              (api->prop->dtv_mode.modulation      & Si2146_DTV_MODE_PROP_MODULATION_MASK     ) << Si2146_DTV_MODE_PROP_MODULATION_LSB  |
              (api->prop->dtv_mode.invert_spectrum & Si2146_DTV_MODE_PROP_INVERT_SPECTRUM_MASK) << Si2146_DTV_MODE_PROP_INVERT_SPECTRUM_LSB ;
     break;
    #endif /*     Si2146_DTV_MODE_PROP */
    #ifdef        Si2146_DTV_RF_TOP_PROP
     case         Si2146_DTV_RF_TOP_PROP_CODE:
       data = (api->prop->dtv_rf_top.dtv_rf_top & Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP_MASK) << Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP_LSB ;
     break;
    #endif /*     Si2146_DTV_RF_TOP_PROP */
    #ifdef        Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_CODE:
       data = (api->prop->dtv_rsq_rssi_threshold.lo & Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK) << Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB  |
              (api->prop->dtv_rsq_rssi_threshold.hi & Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK) << Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB ;
     break;
    #endif /*     Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2146_MASTER_IEN_PROP
     case         Si2146_MASTER_IEN_PROP_CODE:
       data = (api->prop->master_ien.tunien & Si2146_MASTER_IEN_PROP_TUNIEN_MASK) << Si2146_MASTER_IEN_PROP_TUNIEN_LSB  |
              (api->prop->master_ien.atvien & Si2146_MASTER_IEN_PROP_ATVIEN_MASK) << Si2146_MASTER_IEN_PROP_ATVIEN_LSB  |
              (api->prop->master_ien.dtvien & Si2146_MASTER_IEN_PROP_DTVIEN_MASK) << Si2146_MASTER_IEN_PROP_DTVIEN_LSB  |
              (api->prop->master_ien.errien & Si2146_MASTER_IEN_PROP_ERRIEN_MASK) << Si2146_MASTER_IEN_PROP_ERRIEN_LSB  |
              (api->prop->master_ien.ctsien & Si2146_MASTER_IEN_PROP_CTSIEN_MASK) << Si2146_MASTER_IEN_PROP_CTSIEN_LSB ;
     break;
    #endif /*     Si2146_MASTER_IEN_PROP */
    #ifdef        Si2146_TUNER_BLOCKED_VCO_PROP
     case         Si2146_TUNER_BLOCKED_VCO_PROP_CODE:
       data = (api->prop->tuner_blocked_vco.vco_code & Si2146_TUNER_BLOCKED_VCO_PROP_VCO_CODE_MASK) << Si2146_TUNER_BLOCKED_VCO_PROP_VCO_CODE_LSB ;
     break;
    #endif /*     Si2146_TUNER_BLOCKED_VCO_PROP */
    #ifdef        Si2146_TUNER_IEN_PROP
     case         Si2146_TUNER_IEN_PROP_CODE:
       data = (api->prop->tuner_ien.tcien    & Si2146_TUNER_IEN_PROP_TCIEN_MASK   ) << Si2146_TUNER_IEN_PROP_TCIEN_LSB  |
              (api->prop->tuner_ien.rssilien & Si2146_TUNER_IEN_PROP_RSSILIEN_MASK) << Si2146_TUNER_IEN_PROP_RSSILIEN_LSB  |
              (api->prop->tuner_ien.rssihien & Si2146_TUNER_IEN_PROP_RSSIHIEN_MASK) << Si2146_TUNER_IEN_PROP_RSSIHIEN_LSB ;
     break;
    #endif /*     Si2146_TUNER_IEN_PROP */
    #ifdef        Si2146_TUNER_INT_SENSE_PROP
     case         Si2146_TUNER_INT_SENSE_PROP_CODE:
       data = (api->prop->tuner_int_sense.tcnegen    & Si2146_TUNER_INT_SENSE_PROP_TCNEGEN_MASK   ) << Si2146_TUNER_INT_SENSE_PROP_TCNEGEN_LSB  |
              (api->prop->tuner_int_sense.rssilnegen & Si2146_TUNER_INT_SENSE_PROP_RSSILNEGEN_MASK) << Si2146_TUNER_INT_SENSE_PROP_RSSILNEGEN_LSB  |
              (api->prop->tuner_int_sense.rssihnegen & Si2146_TUNER_INT_SENSE_PROP_RSSIHNEGEN_MASK) << Si2146_TUNER_INT_SENSE_PROP_RSSIHNEGEN_LSB  |
              (api->prop->tuner_int_sense.tcposen    & Si2146_TUNER_INT_SENSE_PROP_TCPOSEN_MASK   ) << Si2146_TUNER_INT_SENSE_PROP_TCPOSEN_LSB  |
              (api->prop->tuner_int_sense.rssilposen & Si2146_TUNER_INT_SENSE_PROP_RSSILPOSEN_MASK) << Si2146_TUNER_INT_SENSE_PROP_RSSILPOSEN_LSB  |
              (api->prop->tuner_int_sense.rssihposen & Si2146_TUNER_INT_SENSE_PROP_RSSIHPOSEN_MASK) << Si2146_TUNER_INT_SENSE_PROP_RSSIHPOSEN_LSB ;
     break;
    #endif /*     Si2146_TUNER_INT_SENSE_PROP */
    #ifdef        Si2146_TUNER_LO_INJECTION_PROP
     case         Si2146_TUNER_LO_INJECTION_PROP_CODE:
       data = (api->prop->tuner_lo_injection.band_1 & Si2146_TUNER_LO_INJECTION_PROP_BAND_1_MASK) << Si2146_TUNER_LO_INJECTION_PROP_BAND_1_LSB  |
              (api->prop->tuner_lo_injection.band_2 & Si2146_TUNER_LO_INJECTION_PROP_BAND_2_MASK) << Si2146_TUNER_LO_INJECTION_PROP_BAND_2_LSB  |
              (api->prop->tuner_lo_injection.band_3 & Si2146_TUNER_LO_INJECTION_PROP_BAND_3_MASK) << Si2146_TUNER_LO_INJECTION_PROP_BAND_3_LSB  |
              (api->prop->tuner_lo_injection.band_4 & Si2146_TUNER_LO_INJECTION_PROP_BAND_4_MASK) << Si2146_TUNER_LO_INJECTION_PROP_BAND_4_LSB  |
              (api->prop->tuner_lo_injection.band_5 & Si2146_TUNER_LO_INJECTION_PROP_BAND_5_MASK) << Si2146_TUNER_LO_INJECTION_PROP_BAND_5_LSB ;
     break;
    #endif /*     Si2146_TUNER_LO_INJECTION_PROP */
   default : break;
    }
#ifdef    Si2146_GET_PROPERTY_STRING
    Si2146_L1_FillPropertyStringText(api, prop_code, (char*)" ", msg);
    SiTRACE("%s\n",msg);
#endif /* Si2146_GET_PROPERTY_STRING */
    return Si2146_L1_SetProperty(api, prop_code & 0xffff , data);
  }

/* _set_property2_insertion_point */

/* _get_property2_insertion_start */

  /* --------------------------------------------*/
  /* GET_PROPERTY2 FUNCTION                       */
  /* --------------------------------------------*/
unsigned char Si2146_L1_GetProperty2(L1_Si2146_Context *api, unsigned int prop_code) {
    int data, res;
    res = Si2146_L1_GetProperty(api,prop_code & 0xffff,&data);
    if (res!=NO_Si2146_ERROR) return res;
    switch (prop_code) {
    #ifdef        Si2146_ATV_AFC_RANGE_PROP
     case         Si2146_ATV_AFC_RANGE_PROP_CODE:
               api->prop->atv_afc_range.range_khz = (data >> Si2146_ATV_AFC_RANGE_PROP_RANGE_KHZ_LSB) & Si2146_ATV_AFC_RANGE_PROP_RANGE_KHZ_MASK;
     break;
    #endif /*     Si2146_ATV_AFC_RANGE_PROP */
    #ifdef        Si2146_ATV_AF_OUT_PROP
     case         Si2146_ATV_AF_OUT_PROP_CODE:
               api->prop->atv_af_out.volume = (data >> Si2146_ATV_AF_OUT_PROP_VOLUME_LSB) & Si2146_ATV_AF_OUT_PROP_VOLUME_MASK;
     break;
    #endif /*     Si2146_ATV_AF_OUT_PROP */
    #ifdef        Si2146_ATV_AGC_SPEED_PROP
     case         Si2146_ATV_AGC_SPEED_PROP_CODE:
               api->prop->atv_agc_speed.if_agc_speed = (data >> Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB) & Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK;
     break;
    #endif /*     Si2146_ATV_AGC_SPEED_PROP */
    #ifdef        Si2146_ATV_AUDIO_MODE_PROP
     case         Si2146_ATV_AUDIO_MODE_PROP_CODE:
               api->prop->atv_audio_mode.audio_sys  = (data >> Si2146_ATV_AUDIO_MODE_PROP_AUDIO_SYS_LSB ) & Si2146_ATV_AUDIO_MODE_PROP_AUDIO_SYS_MASK;
               api->prop->atv_audio_mode.demod_mode = (data >> Si2146_ATV_AUDIO_MODE_PROP_DEMOD_MODE_LSB) & Si2146_ATV_AUDIO_MODE_PROP_DEMOD_MODE_MASK;
               api->prop->atv_audio_mode.chan_bw    = (data >> Si2146_ATV_AUDIO_MODE_PROP_CHAN_BW_LSB   ) & Si2146_ATV_AUDIO_MODE_PROP_CHAN_BW_MASK;
     break;
    #endif /*     Si2146_ATV_AUDIO_MODE_PROP */
    #ifdef        Si2146_ATV_CVBS_OUT_PROP
     case         Si2146_ATV_CVBS_OUT_PROP_CODE:
               api->prop->atv_cvbs_out.offset = (data >> Si2146_ATV_CVBS_OUT_PROP_OFFSET_LSB) & Si2146_ATV_CVBS_OUT_PROP_OFFSET_MASK;
               api->prop->atv_cvbs_out.amp    = (data >> Si2146_ATV_CVBS_OUT_PROP_AMP_LSB   ) & Si2146_ATV_CVBS_OUT_PROP_AMP_MASK;
     break;
    #endif /*     Si2146_ATV_CVBS_OUT_PROP */
    #ifdef        Si2146_ATV_CVBS_OUT_FINE_PROP
     case         Si2146_ATV_CVBS_OUT_FINE_PROP_CODE:
               api->prop->atv_cvbs_out_fine.offset = (data >> Si2146_ATV_CVBS_OUT_FINE_PROP_OFFSET_LSB) & Si2146_ATV_CVBS_OUT_FINE_PROP_OFFSET_MASK;
               api->prop->atv_cvbs_out_fine.amp    = (data >> Si2146_ATV_CVBS_OUT_FINE_PROP_AMP_LSB   ) & Si2146_ATV_CVBS_OUT_FINE_PROP_AMP_MASK;
     break;
    #endif /*     Si2146_ATV_CVBS_OUT_FINE_PROP */
    #ifdef        Si2146_ATV_IEN_PROP
     case         Si2146_ATV_IEN_PROP_CODE:
               api->prop->atv_ien.chlien  = (data >> Si2146_ATV_IEN_PROP_CHLIEN_LSB ) & Si2146_ATV_IEN_PROP_CHLIEN_MASK;
               api->prop->atv_ien.pclien  = (data >> Si2146_ATV_IEN_PROP_PCLIEN_LSB ) & Si2146_ATV_IEN_PROP_PCLIEN_MASK;
               api->prop->atv_ien.dlien   = (data >> Si2146_ATV_IEN_PROP_DLIEN_LSB  ) & Si2146_ATV_IEN_PROP_DLIEN_MASK;
               api->prop->atv_ien.snrlien = (data >> Si2146_ATV_IEN_PROP_SNRLIEN_LSB) & Si2146_ATV_IEN_PROP_SNRLIEN_MASK;
               api->prop->atv_ien.snrhien = (data >> Si2146_ATV_IEN_PROP_SNRHIEN_LSB) & Si2146_ATV_IEN_PROP_SNRHIEN_MASK;
     break;
    #endif /*     Si2146_ATV_IEN_PROP */
    #ifdef        Si2146_ATV_INT_SENSE_PROP
     case         Si2146_ATV_INT_SENSE_PROP_CODE:
               api->prop->atv_int_sense.chlnegen  = (data >> Si2146_ATV_INT_SENSE_PROP_CHLNEGEN_LSB ) & Si2146_ATV_INT_SENSE_PROP_CHLNEGEN_MASK;
               api->prop->atv_int_sense.pclnegen  = (data >> Si2146_ATV_INT_SENSE_PROP_PCLNEGEN_LSB ) & Si2146_ATV_INT_SENSE_PROP_PCLNEGEN_MASK;
               api->prop->atv_int_sense.dlnegen   = (data >> Si2146_ATV_INT_SENSE_PROP_DLNEGEN_LSB  ) & Si2146_ATV_INT_SENSE_PROP_DLNEGEN_MASK;
               api->prop->atv_int_sense.snrlnegen = (data >> Si2146_ATV_INT_SENSE_PROP_SNRLNEGEN_LSB) & Si2146_ATV_INT_SENSE_PROP_SNRLNEGEN_MASK;
               api->prop->atv_int_sense.snrhnegen = (data >> Si2146_ATV_INT_SENSE_PROP_SNRHNEGEN_LSB) & Si2146_ATV_INT_SENSE_PROP_SNRHNEGEN_MASK;
               api->prop->atv_int_sense.chlposen  = (data >> Si2146_ATV_INT_SENSE_PROP_CHLPOSEN_LSB ) & Si2146_ATV_INT_SENSE_PROP_CHLPOSEN_MASK;
               api->prop->atv_int_sense.pclposen  = (data >> Si2146_ATV_INT_SENSE_PROP_PCLPOSEN_LSB ) & Si2146_ATV_INT_SENSE_PROP_PCLPOSEN_MASK;
               api->prop->atv_int_sense.dlposen   = (data >> Si2146_ATV_INT_SENSE_PROP_DLPOSEN_LSB  ) & Si2146_ATV_INT_SENSE_PROP_DLPOSEN_MASK;
               api->prop->atv_int_sense.snrlposen = (data >> Si2146_ATV_INT_SENSE_PROP_SNRLPOSEN_LSB) & Si2146_ATV_INT_SENSE_PROP_SNRLPOSEN_MASK;
               api->prop->atv_int_sense.snrhposen = (data >> Si2146_ATV_INT_SENSE_PROP_SNRHPOSEN_LSB) & Si2146_ATV_INT_SENSE_PROP_SNRHPOSEN_MASK;
     break;
    #endif /*     Si2146_ATV_INT_SENSE_PROP */
    #ifdef        Si2146_ATV_RF_TOP_PROP
     case         Si2146_ATV_RF_TOP_PROP_CODE:
               api->prop->atv_rf_top.atv_rf_top = (data >> Si2146_ATV_RF_TOP_PROP_ATV_RF_TOP_LSB) & Si2146_ATV_RF_TOP_PROP_ATV_RF_TOP_MASK;
     break;
    #endif /*     Si2146_ATV_RF_TOP_PROP */
    #ifdef        Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_CODE:
               api->prop->atv_rsq_rssi_threshold.lo = (data >> Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB) & Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK;
               api->prop->atv_rsq_rssi_threshold.hi = (data >> Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB) & Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK;
     break;
    #endif /*     Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2146_ATV_RSQ_SNR_THRESHOLD_PROP
     case         Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_CODE:
               api->prop->atv_rsq_snr_threshold.lo = (data >> Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_LO_LSB) & Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_LO_MASK;
               api->prop->atv_rsq_snr_threshold.hi = (data >> Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_HI_LSB) & Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_HI_MASK;
     break;
    #endif /*     Si2146_ATV_RSQ_SNR_THRESHOLD_PROP */
    #ifdef        Si2146_ATV_SIF_OUT_PROP
     case         Si2146_ATV_SIF_OUT_PROP_CODE:
               api->prop->atv_sif_out.offset = (data >> Si2146_ATV_SIF_OUT_PROP_OFFSET_LSB) & Si2146_ATV_SIF_OUT_PROP_OFFSET_MASK;
               api->prop->atv_sif_out.amp    = (data >> Si2146_ATV_SIF_OUT_PROP_AMP_LSB   ) & Si2146_ATV_SIF_OUT_PROP_AMP_MASK;
     break;
    #endif /*     Si2146_ATV_SIF_OUT_PROP */
    #ifdef        Si2146_ATV_SOUND_AGC_LIMIT_PROP
     case         Si2146_ATV_SOUND_AGC_LIMIT_PROP_CODE:
               api->prop->atv_sound_agc_limit.max_gain = (data >> Si2146_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_LSB) & Si2146_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_MASK;
               api->prop->atv_sound_agc_limit.min_gain = (data >> Si2146_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_LSB) & Si2146_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_MASK;
     break;
    #endif /*     Si2146_ATV_SOUND_AGC_LIMIT_PROP */
    #ifdef        Si2146_ATV_SOUND_AGC_SPEED_PROP
     case         Si2146_ATV_SOUND_AGC_SPEED_PROP_CODE:
               api->prop->atv_sound_agc_speed.system_l      = (data >> Si2146_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_LSB     ) & Si2146_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_MASK;
               api->prop->atv_sound_agc_speed.other_systems = (data >> Si2146_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_LSB) & Si2146_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_MASK;
     break;
    #endif /*     Si2146_ATV_SOUND_AGC_SPEED_PROP */
    #ifdef        Si2146_ATV_VIDEO_EQUALIZER_PROP
     case         Si2146_ATV_VIDEO_EQUALIZER_PROP_CODE:
               api->prop->atv_video_equalizer.slope = (data >> Si2146_ATV_VIDEO_EQUALIZER_PROP_SLOPE_LSB) & Si2146_ATV_VIDEO_EQUALIZER_PROP_SLOPE_MASK;
     break;
    #endif /*     Si2146_ATV_VIDEO_EQUALIZER_PROP */
    #ifdef        Si2146_ATV_VIDEO_MODE_PROP
     case         Si2146_ATV_VIDEO_MODE_PROP_CODE:
               api->prop->atv_video_mode.video_sys       = (data >> Si2146_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LSB      ) & Si2146_ATV_VIDEO_MODE_PROP_VIDEO_SYS_MASK;
               api->prop->atv_video_mode.color           = (data >> Si2146_ATV_VIDEO_MODE_PROP_COLOR_LSB          ) & Si2146_ATV_VIDEO_MODE_PROP_COLOR_MASK;
               api->prop->atv_video_mode.trans           = (data >> Si2146_ATV_VIDEO_MODE_PROP_TRANS_LSB          ) & Si2146_ATV_VIDEO_MODE_PROP_TRANS_MASK;
               api->prop->atv_video_mode.invert_spectrum = (data >> Si2146_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_LSB) & Si2146_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_MASK;
               api->prop->atv_video_mode.invert_signal   = (data >> Si2146_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_LSB  ) & Si2146_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_MASK;
     break;
    #endif /*     Si2146_ATV_VIDEO_MODE_PROP */
    #ifdef        Si2146_ATV_VSNR_CAP_PROP
     case         Si2146_ATV_VSNR_CAP_PROP_CODE:
               api->prop->atv_vsnr_cap.atv_vsnr_cap = (data >> Si2146_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_LSB) & Si2146_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_MASK;
     break;
    #endif /*     Si2146_ATV_VSNR_CAP_PROP */
    #ifdef        Si2146_ATV_VSYNC_TRACKING_PROP
     case         Si2146_ATV_VSYNC_TRACKING_PROP_CODE:
               api->prop->atv_vsync_tracking.min_pulses_to_lock   = (data >> Si2146_ATV_VSYNC_TRACKING_PROP_MIN_PULSES_TO_LOCK_LSB  ) & Si2146_ATV_VSYNC_TRACKING_PROP_MIN_PULSES_TO_LOCK_MASK;
               api->prop->atv_vsync_tracking.min_fields_to_unlock = (data >> Si2146_ATV_VSYNC_TRACKING_PROP_MIN_FIELDS_TO_UNLOCK_LSB) & Si2146_ATV_VSYNC_TRACKING_PROP_MIN_FIELDS_TO_UNLOCK_MASK;
     break;
    #endif /*     Si2146_ATV_VSYNC_TRACKING_PROP */
    #ifdef        Si2146_CRYSTAL_TRIM_PROP
     case         Si2146_CRYSTAL_TRIM_PROP_CODE:
               api->prop->crystal_trim.xo_cap = (data >> Si2146_CRYSTAL_TRIM_PROP_XO_CAP_LSB) & Si2146_CRYSTAL_TRIM_PROP_XO_CAP_MASK;
     break;
    #endif /*     Si2146_CRYSTAL_TRIM_PROP */
    #ifdef        Si2146_DTV_AGC_FREEZE_INPUT_PROP
     case         Si2146_DTV_AGC_FREEZE_INPUT_PROP_CODE:
               api->prop->dtv_agc_freeze_input.level = (data >> Si2146_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LSB) & Si2146_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_MASK;
               api->prop->dtv_agc_freeze_input.pin   = (data >> Si2146_DTV_AGC_FREEZE_INPUT_PROP_PIN_LSB  ) & Si2146_DTV_AGC_FREEZE_INPUT_PROP_PIN_MASK;
     break;
    #endif /*     Si2146_DTV_AGC_FREEZE_INPUT_PROP */
    #ifdef        Si2146_DTV_AGC_SPEED_PROP
     case         Si2146_DTV_AGC_SPEED_PROP_CODE:
               api->prop->dtv_agc_speed.if_agc_speed = (data >> Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB) & Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK;
               api->prop->dtv_agc_speed.agc_decim    = (data >> Si2146_DTV_AGC_SPEED_PROP_AGC_DECIM_LSB   ) & Si2146_DTV_AGC_SPEED_PROP_AGC_DECIM_MASK;
     break;
    #endif /*     Si2146_DTV_AGC_SPEED_PROP */
    #ifdef        Si2146_DTV_CONFIG_IF_PORT_PROP
     case         Si2146_DTV_CONFIG_IF_PORT_PROP_CODE:
               api->prop->dtv_config_if_port.dtv_out_type   = (data >> Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LSB  ) & Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_MASK;
               api->prop->dtv_config_if_port.dtv_agc_source = (data >> Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_LSB) & Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_MASK;
     break;
    #endif /*     Si2146_DTV_CONFIG_IF_PORT_PROP */
    #ifdef        Si2146_DTV_EXT_AGC_PROP
     case         Si2146_DTV_EXT_AGC_PROP_CODE:
               api->prop->dtv_ext_agc.min_10mv = (data >> Si2146_DTV_EXT_AGC_PROP_MIN_10MV_LSB) & Si2146_DTV_EXT_AGC_PROP_MIN_10MV_MASK;
               api->prop->dtv_ext_agc.max_10mv = (data >> Si2146_DTV_EXT_AGC_PROP_MAX_10MV_LSB) & Si2146_DTV_EXT_AGC_PROP_MAX_10MV_MASK;
     break;
    #endif /*     Si2146_DTV_EXT_AGC_PROP */
    #ifdef        Si2146_DTV_IEN_PROP
     case         Si2146_DTV_IEN_PROP_CODE:
               api->prop->dtv_ien.chlien = (data >> Si2146_DTV_IEN_PROP_CHLIEN_LSB) & Si2146_DTV_IEN_PROP_CHLIEN_MASK;
     break;
    #endif /*     Si2146_DTV_IEN_PROP */
     #ifdef        Si2146_DTV_INITIAL_AGC_SPEED_PROP
     case         Si2146_DTV_INITIAL_AGC_SPEED_PROP_CODE:
               api->prop->dtv_initial_agc_speed.if_agc_speed = (data >> Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_LSB) & Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_MASK;
               api->prop->dtv_initial_agc_speed.agc_decim    = (data >> Si2146_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_LSB   ) & Si2146_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_MASK;
     break;
    #endif /*     Si2146_DTV_INITIAL_AGC_SPEED_PROP */
    #ifdef        Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
     case         Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE:
               api->prop->dtv_initial_agc_speed_period.period = (data >> Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_LSB) & Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_MASK;
     break;
    #endif /*     Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
    #ifdef        Si2146_DTV_INT_SENSE_PROP
     case         Si2146_DTV_INT_SENSE_PROP_CODE:
               api->prop->dtv_int_sense.chlnegen = (data >> Si2146_DTV_INT_SENSE_PROP_CHLNEGEN_LSB) & Si2146_DTV_INT_SENSE_PROP_CHLNEGEN_MASK;
               api->prop->dtv_int_sense.chlposen = (data >> Si2146_DTV_INT_SENSE_PROP_CHLPOSEN_LSB) & Si2146_DTV_INT_SENSE_PROP_CHLPOSEN_MASK;
     break;
    #endif /*     Si2146_DTV_INT_SENSE_PROP */
    #ifdef        Si2146_DTV_LIF_FREQ_PROP
     case         Si2146_DTV_LIF_FREQ_PROP_CODE:
               api->prop->dtv_lif_freq.offset = (data >> Si2146_DTV_LIF_FREQ_PROP_OFFSET_LSB) & Si2146_DTV_LIF_FREQ_PROP_OFFSET_MASK;
     break;
    #endif /*     Si2146_DTV_LIF_FREQ_PROP */
    #ifdef        Si2146_DTV_LIF_OUT_PROP
     case         Si2146_DTV_LIF_OUT_PROP_CODE:
               api->prop->dtv_lif_out.offset = (data >> Si2146_DTV_LIF_OUT_PROP_OFFSET_LSB) & Si2146_DTV_LIF_OUT_PROP_OFFSET_MASK;
               api->prop->dtv_lif_out.amp    = (data >> Si2146_DTV_LIF_OUT_PROP_AMP_LSB   ) & Si2146_DTV_LIF_OUT_PROP_AMP_MASK;
     break;
    #endif /*     Si2146_DTV_LIF_OUT_PROP */
    #ifdef        Si2146_DTV_MODE_PROP
     case         Si2146_DTV_MODE_PROP_CODE:
               api->prop->dtv_mode.bw              = (data >> Si2146_DTV_MODE_PROP_BW_LSB             ) & Si2146_DTV_MODE_PROP_BW_MASK;
               api->prop->dtv_mode.modulation      = (data >> Si2146_DTV_MODE_PROP_MODULATION_LSB     ) & Si2146_DTV_MODE_PROP_MODULATION_MASK;
               api->prop->dtv_mode.invert_spectrum = (data >> Si2146_DTV_MODE_PROP_INVERT_SPECTRUM_LSB) & Si2146_DTV_MODE_PROP_INVERT_SPECTRUM_MASK;
     break;
    #endif /*     Si2146_DTV_MODE_PROP */
    #ifdef        Si2146_DTV_RF_TOP_PROP
     case         Si2146_DTV_RF_TOP_PROP_CODE:
               api->prop->dtv_rf_top.dtv_rf_top = (data >> Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP_LSB) & Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP_MASK;
     break;
    #endif /*     Si2146_DTV_RF_TOP_PROP */
    #ifdef        Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_CODE:
               api->prop->dtv_rsq_rssi_threshold.lo = (data >> Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB) & Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK;
               api->prop->dtv_rsq_rssi_threshold.hi = (data >> Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB) & Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK;
     break;
    #endif /*     Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2146_MASTER_IEN_PROP
     case         Si2146_MASTER_IEN_PROP_CODE:
               api->prop->master_ien.tunien = (data >> Si2146_MASTER_IEN_PROP_TUNIEN_LSB) & Si2146_MASTER_IEN_PROP_TUNIEN_MASK;
               api->prop->master_ien.atvien = (data >> Si2146_MASTER_IEN_PROP_ATVIEN_LSB) & Si2146_MASTER_IEN_PROP_ATVIEN_MASK;
               api->prop->master_ien.dtvien = (data >> Si2146_MASTER_IEN_PROP_DTVIEN_LSB) & Si2146_MASTER_IEN_PROP_DTVIEN_MASK;
               api->prop->master_ien.errien = (data >> Si2146_MASTER_IEN_PROP_ERRIEN_LSB) & Si2146_MASTER_IEN_PROP_ERRIEN_MASK;
               api->prop->master_ien.ctsien = (data >> Si2146_MASTER_IEN_PROP_CTSIEN_LSB) & Si2146_MASTER_IEN_PROP_CTSIEN_MASK;
     break;
    #endif /*     Si2146_MASTER_IEN_PROP */
    #ifdef        Si2146_TUNER_BLOCKED_VCO_PROP
     case         Si2146_TUNER_BLOCKED_VCO_PROP_CODE:
               api->prop->tuner_blocked_vco.vco_code = (data >> Si2146_TUNER_BLOCKED_VCO_PROP_VCO_CODE_LSB) & Si2146_TUNER_BLOCKED_VCO_PROP_VCO_CODE_MASK;
     break;
    #endif /*     Si2146_TUNER_BLOCKED_VCO_PROP */
    #ifdef        Si2146_TUNER_IEN_PROP
     case         Si2146_TUNER_IEN_PROP_CODE:
               api->prop->tuner_ien.tcien    = (data >> Si2146_TUNER_IEN_PROP_TCIEN_LSB   ) & Si2146_TUNER_IEN_PROP_TCIEN_MASK;
               api->prop->tuner_ien.rssilien = (data >> Si2146_TUNER_IEN_PROP_RSSILIEN_LSB) & Si2146_TUNER_IEN_PROP_RSSILIEN_MASK;
               api->prop->tuner_ien.rssihien = (data >> Si2146_TUNER_IEN_PROP_RSSIHIEN_LSB) & Si2146_TUNER_IEN_PROP_RSSIHIEN_MASK;
     break;
    #endif /*     Si2146_TUNER_IEN_PROP */
    #ifdef        Si2146_TUNER_INT_SENSE_PROP
     case         Si2146_TUNER_INT_SENSE_PROP_CODE:
               api->prop->tuner_int_sense.tcnegen    = (data >> Si2146_TUNER_INT_SENSE_PROP_TCNEGEN_LSB   ) & Si2146_TUNER_INT_SENSE_PROP_TCNEGEN_MASK;
               api->prop->tuner_int_sense.rssilnegen = (data >> Si2146_TUNER_INT_SENSE_PROP_RSSILNEGEN_LSB) & Si2146_TUNER_INT_SENSE_PROP_RSSILNEGEN_MASK;
               api->prop->tuner_int_sense.rssihnegen = (data >> Si2146_TUNER_INT_SENSE_PROP_RSSIHNEGEN_LSB) & Si2146_TUNER_INT_SENSE_PROP_RSSIHNEGEN_MASK;
               api->prop->tuner_int_sense.tcposen    = (data >> Si2146_TUNER_INT_SENSE_PROP_TCPOSEN_LSB   ) & Si2146_TUNER_INT_SENSE_PROP_TCPOSEN_MASK;
               api->prop->tuner_int_sense.rssilposen = (data >> Si2146_TUNER_INT_SENSE_PROP_RSSILPOSEN_LSB) & Si2146_TUNER_INT_SENSE_PROP_RSSILPOSEN_MASK;
               api->prop->tuner_int_sense.rssihposen = (data >> Si2146_TUNER_INT_SENSE_PROP_RSSIHPOSEN_LSB) & Si2146_TUNER_INT_SENSE_PROP_RSSIHPOSEN_MASK;
     break;
    #endif /*     Si2146_TUNER_INT_SENSE_PROP */
    #ifdef        Si2146_TUNER_LO_INJECTION_PROP
     case         Si2146_TUNER_LO_INJECTION_PROP_CODE:
               api->prop->tuner_lo_injection.band_1 = (data >> Si2146_TUNER_LO_INJECTION_PROP_BAND_1_LSB) & Si2146_TUNER_LO_INJECTION_PROP_BAND_1_MASK;
               api->prop->tuner_lo_injection.band_2 = (data >> Si2146_TUNER_LO_INJECTION_PROP_BAND_2_LSB) & Si2146_TUNER_LO_INJECTION_PROP_BAND_2_MASK;
               api->prop->tuner_lo_injection.band_3 = (data >> Si2146_TUNER_LO_INJECTION_PROP_BAND_3_LSB) & Si2146_TUNER_LO_INJECTION_PROP_BAND_3_MASK;
               api->prop->tuner_lo_injection.band_4 = (data >> Si2146_TUNER_LO_INJECTION_PROP_BAND_4_LSB) & Si2146_TUNER_LO_INJECTION_PROP_BAND_4_MASK;
               api->prop->tuner_lo_injection.band_5 = (data >> Si2146_TUNER_LO_INJECTION_PROP_BAND_5_LSB) & Si2146_TUNER_LO_INJECTION_PROP_BAND_5_MASK;
     break;
    #endif /*     Si2146_TUNER_LO_INJECTION_PROP */
   default : break;
    }
    return res;
  }
  /* _get_property2_insertion_point */

#ifdef    Si2146_GET_PROPERTY_STRING
/* _get_property_string_insertion_start */

  /* --------------------------------------------*/
  /* GET_PROPERTY_STRING FUNCTION                */
  /* --------------------------------------------*/
unsigned char Si2146_L1_GetPropertyString(L1_Si2146_Context *api, unsigned int prop_code, char *separator, char *msg) {
    int res;
    res = Si2146_L1_GetProperty2(api,prop_code);
    if (res!=NO_Si2146_ERROR) { sprintf(msg, "%s",Si2146_L1_API_ERROR_TEXT(res)); return res; }
    Si2146_L1_FillPropertyStringText(api, prop_code, separator, msg);
    return NO_Si2146_ERROR;
}
  /* --------------------------------------------*/
  /* FillPropertyStringText FUNCTION             */
  /* --------------------------------------------*/
void          Si2146_L1_FillPropertyStringText(L1_Si2146_Context *api, unsigned int prop_code, char *separator, char *msg) {
    switch (prop_code) {
    #ifdef        Si2146_ATV_AFC_RANGE_PROP
     case         Si2146_ATV_AFC_RANGE_PROP_CODE:
      sprintf(msg,"ATV_AFC_RANGE");
       strcat(msg,separator); strcat(msg,"-RANGE_KHZ ");
           if  (api->prop->atv_afc_range.range_khz ==   100) strcat(msg,"100_KHZ  ");
      else if  (api->prop->atv_afc_range.range_khz ==   500) strcat(msg,"500_KHZ  ");
      else if  (api->prop->atv_afc_range.range_khz ==  1000) strcat(msg,"1000_KHZ ");
      else if  (api->prop->atv_afc_range.range_khz ==  1500) strcat(msg,"1500_KHZ ");
      else if  (api->prop->atv_afc_range.range_khz ==  2000) strcat(msg,"2000_KHZ ");
      else                                                  sprintf(msg,"%s%d", msg, api->prop->atv_afc_range.range_khz);
     break;
    #endif /*     Si2146_ATV_AFC_RANGE_PROP */
    #ifdef        Si2146_ATV_AF_OUT_PROP
     case         Si2146_ATV_AF_OUT_PROP_CODE:
      sprintf(msg,"ATV_AF_OUT");
       strcat(msg,separator); strcat(msg,"-VOLUME "); sprintf(msg,"%s%d", msg, api->prop->atv_af_out.volume);
     break;
    #endif /*     Si2146_ATV_AF_OUT_PROP */
    #ifdef        Si2146_ATV_AGC_SPEED_PROP
     case         Si2146_ATV_AGC_SPEED_PROP_CODE:
      sprintf(msg,"ATV_AGC_SPEED");
       strcat(msg,separator); strcat(msg,"-IF_AGC_SPEED ");
           if  (api->prop->atv_agc_speed.if_agc_speed ==     0) strcat(msg,"AUTO ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==    89) strcat(msg,"89   ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   105) strcat(msg,"105  ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   121) strcat(msg,"121  ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   137) strcat(msg,"137  ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   158) strcat(msg,"158  ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   172) strcat(msg,"172  ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   185) strcat(msg,"185  ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   196) strcat(msg,"196  ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   206) strcat(msg,"206  ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   216) strcat(msg,"216  ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   219) strcat(msg,"219  ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   222) strcat(msg,"222  ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   248) strcat(msg,"248  ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   250) strcat(msg,"250  ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   251) strcat(msg,"251  ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->atv_agc_speed.if_agc_speed);
     break;
    #endif /*     Si2146_ATV_AGC_SPEED_PROP */
    #ifdef        Si2146_ATV_AUDIO_MODE_PROP
     case         Si2146_ATV_AUDIO_MODE_PROP_CODE:
      sprintf(msg,"ATV_AUDIO_MODE");
       strcat(msg,separator); strcat(msg,"-AUDIO_SYS ");
           if  (api->prop->atv_audio_mode.audio_sys  ==     0) strcat(msg,"DEFAULT    ");
      else if  (api->prop->atv_audio_mode.audio_sys  ==     1) strcat(msg,"MONO       ");
      else if  (api->prop->atv_audio_mode.audio_sys  ==     2) strcat(msg,"MONO_NICAM ");
      else if  (api->prop->atv_audio_mode.audio_sys  ==     3) strcat(msg,"A2         ");
      else if  (api->prop->atv_audio_mode.audio_sys  ==     4) strcat(msg,"A2_DK2     ");
      else if  (api->prop->atv_audio_mode.audio_sys  ==     5) strcat(msg,"A2_DK3     ");
      else if  (api->prop->atv_audio_mode.audio_sys  ==     6) strcat(msg,"BTSC       ");
      else if  (api->prop->atv_audio_mode.audio_sys  ==     7) strcat(msg,"EIAJ       ");
      else if  (api->prop->atv_audio_mode.audio_sys  ==     8) strcat(msg,"SCAN       ");
      else if  (api->prop->atv_audio_mode.audio_sys  ==     9) strcat(msg,"A2_DK4     ");
      else if  (api->prop->atv_audio_mode.audio_sys  ==    10) strcat(msg,"WIDE_SCAN  ");
      else                                                    sprintf(msg,"%s%d", msg, api->prop->atv_audio_mode.audio_sys);
       strcat(msg,separator); strcat(msg,"-DEMOD_MODE ");
           if  (api->prop->atv_audio_mode.demod_mode ==     0) strcat(msg,"SIF ");
      else if  (api->prop->atv_audio_mode.demod_mode ==     1) strcat(msg,"AM  ");
      else if  (api->prop->atv_audio_mode.demod_mode ==     2) strcat(msg,"FM1 ");
      else if  (api->prop->atv_audio_mode.demod_mode ==     3) strcat(msg,"FM2 ");
      else                                                    sprintf(msg,"%s%d", msg, api->prop->atv_audio_mode.demod_mode);
       strcat(msg,separator); strcat(msg,"-CHAN_BW ");
           if  (api->prop->atv_audio_mode.chan_bw    ==     0) strcat(msg,"DEFAULT        ");
      else if  (api->prop->atv_audio_mode.chan_bw    ==     1) strcat(msg,"4X_OVERMOD     ");
      else if  (api->prop->atv_audio_mode.chan_bw    ==     2) strcat(msg,"8X_OVERMOD     ");
      else if  (api->prop->atv_audio_mode.chan_bw    ==     3) strcat(msg,"12X_OVERMOD    ");
      else if  (api->prop->atv_audio_mode.chan_bw    ==     4) strcat(msg,"7P5_KHZ_OFFSET ");
      else if  (api->prop->atv_audio_mode.chan_bw    ==     5) strcat(msg,"15_KHZ_OFFSET  ");
      else if  (api->prop->atv_audio_mode.chan_bw    ==     6) strcat(msg,"30_KHZ_OFFSET  ");
      else if  (api->prop->atv_audio_mode.chan_bw    ==     7) strcat(msg,"75_KHZ_OFFSET  ");
      else if  (api->prop->atv_audio_mode.chan_bw    ==     8) strcat(msg,"150_KHZ_OFFSET ");
      else                                                    sprintf(msg,"%s%d", msg, api->prop->atv_audio_mode.chan_bw);
     break;
    #endif /*     Si2146_ATV_AUDIO_MODE_PROP */
    #ifdef        Si2146_ATV_CVBS_OUT_PROP
     case         Si2146_ATV_CVBS_OUT_PROP_CODE:
      sprintf(msg,"ATV_CVBS_OUT");
       strcat(msg,separator); strcat(msg,"-OFFSET "); sprintf(msg,"%s%d", msg, api->prop->atv_cvbs_out.offset);
       strcat(msg,separator); strcat(msg,"-AMP "); sprintf(msg,"%s%d", msg, api->prop->atv_cvbs_out.amp);
     break;
    #endif /*     Si2146_ATV_CVBS_OUT_PROP */
    #ifdef        Si2146_ATV_CVBS_OUT_FINE_PROP
     case         Si2146_ATV_CVBS_OUT_FINE_PROP_CODE:
      sprintf(msg,"ATV_CVBS_OUT_FINE");
       strcat(msg,separator); strcat(msg,"-OFFSET "); sprintf(msg,"%s%d", msg, api->prop->atv_cvbs_out_fine.offset);
       strcat(msg,separator); strcat(msg,"-AMP "); sprintf(msg,"%s%d", msg, api->prop->atv_cvbs_out_fine.amp);
     break;
    #endif /*     Si2146_ATV_CVBS_OUT_FINE_PROP */
    #ifdef        Si2146_ATV_IEN_PROP
     case         Si2146_ATV_IEN_PROP_CODE:
      sprintf(msg,"ATV_IEN");
       strcat(msg,separator); strcat(msg,"-CHLIEN ");
           if  (api->prop->atv_ien.chlien  ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_ien.chlien  ==     1) strcat(msg,"ENABLE  ");
      else                                          sprintf(msg,"%s%d", msg, api->prop->atv_ien.chlien);
       strcat(msg,separator); strcat(msg,"-PCLIEN ");
           if  (api->prop->atv_ien.pclien  ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_ien.pclien  ==     1) strcat(msg,"ENABLE  ");
      else                                          sprintf(msg,"%s%d", msg, api->prop->atv_ien.pclien);
       strcat(msg,separator); strcat(msg,"-DLIEN ");
           if  (api->prop->atv_ien.dlien   ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_ien.dlien   ==     1) strcat(msg,"ENABLE  ");
      else                                          sprintf(msg,"%s%d", msg, api->prop->atv_ien.dlien);
       strcat(msg,separator); strcat(msg,"-SNRLIEN ");
           if  (api->prop->atv_ien.snrlien ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_ien.snrlien ==     1) strcat(msg,"ENABLE  ");
      else                                          sprintf(msg,"%s%d", msg, api->prop->atv_ien.snrlien);
       strcat(msg,separator); strcat(msg,"-SNRHIEN ");
           if  (api->prop->atv_ien.snrhien ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_ien.snrhien ==     1) strcat(msg,"ENABLE  ");
      else                                          sprintf(msg,"%s%d", msg, api->prop->atv_ien.snrhien);
     break;
    #endif /*     Si2146_ATV_IEN_PROP */
    #ifdef        Si2146_ATV_INT_SENSE_PROP
     case         Si2146_ATV_INT_SENSE_PROP_CODE:
      sprintf(msg,"ATV_INT_SENSE");
       strcat(msg,separator); strcat(msg,"-CHLNEGEN ");
           if  (api->prop->atv_int_sense.chlnegen  ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_int_sense.chlnegen  ==     1) strcat(msg,"ENABLE  ");
      else                                                  sprintf(msg,"%s%d", msg, api->prop->atv_int_sense.chlnegen);
       strcat(msg,separator); strcat(msg,"-PCLNEGEN ");
           if  (api->prop->atv_int_sense.pclnegen  ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_int_sense.pclnegen  ==     1) strcat(msg,"ENABLE  ");
      else                                                  sprintf(msg,"%s%d", msg, api->prop->atv_int_sense.pclnegen);
       strcat(msg,separator); strcat(msg,"-DLNEGEN ");
           if  (api->prop->atv_int_sense.dlnegen   ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_int_sense.dlnegen   ==     1) strcat(msg,"ENABLE  ");
      else                                                  sprintf(msg,"%s%d", msg, api->prop->atv_int_sense.dlnegen);
       strcat(msg,separator); strcat(msg,"-SNRLNEGEN ");
           if  (api->prop->atv_int_sense.snrlnegen ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_int_sense.snrlnegen ==     1) strcat(msg,"ENABLE  ");
      else                                                  sprintf(msg,"%s%d", msg, api->prop->atv_int_sense.snrlnegen);
       strcat(msg,separator); strcat(msg,"-SNRHNEGEN ");
           if  (api->prop->atv_int_sense.snrhnegen ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_int_sense.snrhnegen ==     1) strcat(msg,"ENABLE  ");
      else                                                  sprintf(msg,"%s%d", msg, api->prop->atv_int_sense.snrhnegen);
       strcat(msg,separator); strcat(msg,"-CHLPOSEN ");
           if  (api->prop->atv_int_sense.chlposen  ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_int_sense.chlposen  ==     1) strcat(msg,"ENABLE  ");
      else                                                  sprintf(msg,"%s%d", msg, api->prop->atv_int_sense.chlposen);
       strcat(msg,separator); strcat(msg,"-PCLPOSEN ");
           if  (api->prop->atv_int_sense.pclposen  ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_int_sense.pclposen  ==     1) strcat(msg,"ENABLE  ");
      else                                                  sprintf(msg,"%s%d", msg, api->prop->atv_int_sense.pclposen);
       strcat(msg,separator); strcat(msg,"-DLPOSEN ");
           if  (api->prop->atv_int_sense.dlposen   ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_int_sense.dlposen   ==     1) strcat(msg,"ENABLE  ");
      else                                                  sprintf(msg,"%s%d", msg, api->prop->atv_int_sense.dlposen);
       strcat(msg,separator); strcat(msg,"-SNRLPOSEN ");
           if  (api->prop->atv_int_sense.snrlposen ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_int_sense.snrlposen ==     1) strcat(msg,"ENABLE  ");
      else                                                  sprintf(msg,"%s%d", msg, api->prop->atv_int_sense.snrlposen);
       strcat(msg,separator); strcat(msg,"-SNRHPOSEN ");
           if  (api->prop->atv_int_sense.snrhposen ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_int_sense.snrhposen ==     1) strcat(msg,"ENABLE  ");
      else                                                  sprintf(msg,"%s%d", msg, api->prop->atv_int_sense.snrhposen);
     break;
    #endif /*     Si2146_ATV_INT_SENSE_PROP */
    #ifdef        Si2146_ATV_RF_TOP_PROP
     case         Si2146_ATV_RF_TOP_PROP_CODE:
      sprintf(msg,"ATV_RF_TOP");
       strcat(msg,separator); strcat(msg,"-ATV_RF_TOP ");
           if  (api->prop->atv_rf_top.atv_rf_top ==     0) strcat(msg,"AUTO  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==     6) strcat(msg,"0DB   ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==     7) strcat(msg,"M1DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==     8) strcat(msg,"M2DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==     9) strcat(msg,"M3DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    10) strcat(msg,"M4DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    11) strcat(msg,"M5DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    12) strcat(msg,"M6DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    13) strcat(msg,"M7DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    14) strcat(msg,"M8DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    15) strcat(msg,"M9DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    16) strcat(msg,"M10DB ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    17) strcat(msg,"M11DB ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    18) strcat(msg,"M12DB ");
      else                                                sprintf(msg,"%s%d", msg, api->prop->atv_rf_top.atv_rf_top);
     break;
    #endif /*     Si2146_ATV_RF_TOP_PROP */
    #ifdef        Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_CODE:
      sprintf(msg,"ATV_RSQ_RSSI_THRESHOLD");
       strcat(msg,separator); strcat(msg,"-LO "); sprintf(msg,"%s%d", msg, api->prop->atv_rsq_rssi_threshold.lo);
       strcat(msg,separator); strcat(msg,"-HI "); sprintf(msg,"%s%d", msg, api->prop->atv_rsq_rssi_threshold.hi);
     break;
    #endif /*     Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2146_ATV_RSQ_SNR_THRESHOLD_PROP
     case         Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_CODE:
      sprintf(msg,"ATV_RSQ_SNR_THRESHOLD");
       strcat(msg,separator); strcat(msg,"-LO "); sprintf(msg,"%s%d", msg, api->prop->atv_rsq_snr_threshold.lo);
       strcat(msg,separator); strcat(msg,"-HI "); sprintf(msg,"%s%d", msg, api->prop->atv_rsq_snr_threshold.hi);
     break;
    #endif /*     Si2146_ATV_RSQ_SNR_THRESHOLD_PROP */
    #ifdef        Si2146_ATV_SIF_OUT_PROP
     case         Si2146_ATV_SIF_OUT_PROP_CODE:
      sprintf(msg,"ATV_SIF_OUT");
       strcat(msg,separator); strcat(msg,"-OFFSET "); sprintf(msg,"%s%d", msg, api->prop->atv_sif_out.offset);
       strcat(msg,separator); strcat(msg,"-AMP "); sprintf(msg,"%s%d", msg, api->prop->atv_sif_out.amp);
     break;
    #endif /*     Si2146_ATV_SIF_OUT_PROP */
    #ifdef        Si2146_ATV_SOUND_AGC_LIMIT_PROP
     case         Si2146_ATV_SOUND_AGC_LIMIT_PROP_CODE:
      sprintf(msg,"ATV_SOUND_AGC_LIMIT");
       strcat(msg,separator); strcat(msg,"-MAX_GAIN "); sprintf(msg,"%s%d", msg, api->prop->atv_sound_agc_limit.max_gain);
       strcat(msg,separator); strcat(msg,"-MIN_GAIN "); sprintf(msg,"%s%d", msg, api->prop->atv_sound_agc_limit.min_gain);
     break;
    #endif /*     Si2146_ATV_SOUND_AGC_LIMIT_PROP */
    #ifdef        Si2146_ATV_SOUND_AGC_SPEED_PROP
     case         Si2146_ATV_SOUND_AGC_SPEED_PROP_CODE:
      sprintf(msg,"ATV_SOUND_AGC_SPEED");
       strcat(msg,separator); strcat(msg,"-SYSTEM_L "); sprintf(msg,"%s%d", msg, api->prop->atv_sound_agc_speed.system_l);
       strcat(msg,separator); strcat(msg,"-OTHER_SYSTEMS "); sprintf(msg,"%s%d", msg, api->prop->atv_sound_agc_speed.other_systems);
     break;
    #endif /*     Si2146_ATV_SOUND_AGC_SPEED_PROP */
    #ifdef        Si2146_ATV_VIDEO_EQUALIZER_PROP
     case         Si2146_ATV_VIDEO_EQUALIZER_PROP_CODE:
      sprintf(msg,"ATV_VIDEO_EQUALIZER");
       strcat(msg,separator); strcat(msg,"-SLOPE "); sprintf(msg,"%s%d", msg, api->prop->atv_video_equalizer.slope);
     break;
    #endif /*     Si2146_ATV_VIDEO_EQUALIZER_PROP */
    #ifdef        Si2146_ATV_VIDEO_MODE_PROP
     case         Si2146_ATV_VIDEO_MODE_PROP_CODE:
      sprintf(msg,"ATV_VIDEO_MODE");
       strcat(msg,separator); strcat(msg,"-VIDEO_SYS ");
           if  (api->prop->atv_video_mode.video_sys       ==     0) strcat(msg,"B  ");
      else if  (api->prop->atv_video_mode.video_sys       ==     1) strcat(msg,"GH ");
      else if  (api->prop->atv_video_mode.video_sys       ==     2) strcat(msg,"M  ");
      else if  (api->prop->atv_video_mode.video_sys       ==     3) strcat(msg,"N  ");
      else if  (api->prop->atv_video_mode.video_sys       ==     4) strcat(msg,"I  ");
      else if  (api->prop->atv_video_mode.video_sys       ==     5) strcat(msg,"DK ");
      else if  (api->prop->atv_video_mode.video_sys       ==     6) strcat(msg,"L  ");
      else if  (api->prop->atv_video_mode.video_sys       ==     7) strcat(msg,"LP ");
      else                                                         sprintf(msg,"%s%d", msg, api->prop->atv_video_mode.video_sys);
       strcat(msg,separator); strcat(msg,"-COLOR ");
           if  (api->prop->atv_video_mode.color           ==     0) strcat(msg,"PAL_NTSC ");
      else if  (api->prop->atv_video_mode.color           ==     1) strcat(msg,"SECAM    ");
      else                                                         sprintf(msg,"%s%d", msg, api->prop->atv_video_mode.color);
       strcat(msg,separator); strcat(msg,"-TRANS ");
           if  (api->prop->atv_video_mode.trans           ==     0) strcat(msg,"TERRESTRIAL ");
      else if  (api->prop->atv_video_mode.trans           ==     1) strcat(msg,"CABLE       ");
      else                                                         sprintf(msg,"%s%d", msg, api->prop->atv_video_mode.trans);
       strcat(msg,separator); strcat(msg,"-INVERT_SPECTRUM ");
           if  (api->prop->atv_video_mode.invert_spectrum ==     0) strcat(msg,"NORMAL   ");
      else if  (api->prop->atv_video_mode.invert_spectrum ==     1) strcat(msg,"INVERTED ");
      else                                                         sprintf(msg,"%s%d", msg, api->prop->atv_video_mode.invert_spectrum);
       strcat(msg,separator); strcat(msg,"-INVERT_SIGNAL ");
           if  (api->prop->atv_video_mode.invert_signal   ==     0) strcat(msg,"NORMAL   ");
      else if  (api->prop->atv_video_mode.invert_signal   ==     1) strcat(msg,"INVERTED ");
      else                                                         sprintf(msg,"%s%d", msg, api->prop->atv_video_mode.invert_signal);
     break;
    #endif /*     Si2146_ATV_VIDEO_MODE_PROP */
    #ifdef        Si2146_ATV_VSNR_CAP_PROP
     case         Si2146_ATV_VSNR_CAP_PROP_CODE:
      sprintf(msg,"ATV_VSNR_CAP");
       strcat(msg,separator); strcat(msg,"-ATV_VSNR_CAP "); sprintf(msg,"%s%d", msg, api->prop->atv_vsnr_cap.atv_vsnr_cap);
     break;
    #endif /*     Si2146_ATV_VSNR_CAP_PROP */
    #ifdef        Si2146_ATV_VSYNC_TRACKING_PROP
     case         Si2146_ATV_VSYNC_TRACKING_PROP_CODE:
      sprintf(msg,"ATV_VSYNC_TRACKING");
       strcat(msg,separator); strcat(msg,"-MIN_PULSES_TO_LOCK "); sprintf(msg,"%s%d", msg, api->prop->atv_vsync_tracking.min_pulses_to_lock);
       strcat(msg,separator); strcat(msg,"-MIN_FIELDS_TO_UNLOCK "); sprintf(msg,"%s%d", msg, api->prop->atv_vsync_tracking.min_fields_to_unlock);
     break;
    #endif /*     Si2146_ATV_VSYNC_TRACKING_PROP */
    #ifdef        Si2146_CRYSTAL_TRIM_PROP
     case         Si2146_CRYSTAL_TRIM_PROP_CODE:
      sprintf(msg,"CRYSTAL_TRIM");
       strcat(msg,separator); strcat(msg,"-XO_CAP "); sprintf(msg,"%s%d", msg, api->prop->crystal_trim.xo_cap);
     break;
    #endif /*     Si2146_CRYSTAL_TRIM_PROP */
    #ifdef        Si2146_DTV_AGC_FREEZE_INPUT_PROP
     case         Si2146_DTV_AGC_FREEZE_INPUT_PROP_CODE:
      sprintf(msg,"DTV_AGC_FREEZE_INPUT");
       strcat(msg,separator); strcat(msg,"-LEVEL ");
           if  (api->prop->dtv_agc_freeze_input.level ==     0) strcat(msg,"LOW  ");
      else if  (api->prop->dtv_agc_freeze_input.level ==     1) strcat(msg,"HIGH ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->dtv_agc_freeze_input.level);
       strcat(msg,separator); strcat(msg,"-PIN ");
           if  (api->prop->dtv_agc_freeze_input.pin   ==     0) strcat(msg,"NONE  ");
      else if  (api->prop->dtv_agc_freeze_input.pin   ==     1) strcat(msg,"GPIO1 ");
      else if  (api->prop->dtv_agc_freeze_input.pin   ==     2) strcat(msg,"GPIO2 ");
      else if  (api->prop->dtv_agc_freeze_input.pin   ==     3) strcat(msg,"GPIO3 ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->dtv_agc_freeze_input.pin);
     break;
    #endif /*     Si2146_DTV_AGC_FREEZE_INPUT_PROP */
    #ifdef        Si2146_DTV_AGC_SPEED_PROP
     case         Si2146_DTV_AGC_SPEED_PROP_CODE:
      sprintf(msg,"DTV_AGC_SPEED");
       strcat(msg,separator); strcat(msg,"-IF_AGC_SPEED ");
           if  (api->prop->dtv_agc_speed.if_agc_speed ==     0) strcat(msg,"AUTO ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==    39) strcat(msg,"39  ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==    54) strcat(msg,"54  ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==    63) strcat(msg,"63  ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==    89) strcat(msg,"89  ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   105) strcat(msg,"105 ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   121) strcat(msg,"121 ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   137) strcat(msg,"137 ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   158) strcat(msg,"158 ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   172) strcat(msg,"172 ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   185) strcat(msg,"185 ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   196) strcat(msg,"196 ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   206) strcat(msg,"206 ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   216) strcat(msg,"216 ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   219) strcat(msg,"219 ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   222) strcat(msg,"222 ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->dtv_agc_speed.if_agc_speed);
       strcat(msg,separator); strcat(msg,"-AGC_DECIM    ");
           if  (api->prop->dtv_agc_speed.agc_decim    ==     0) strcat(msg,"OFF ");
      else if  (api->prop->dtv_agc_speed.agc_decim    ==     1) strcat(msg,"2  ");
      else if  (api->prop->dtv_agc_speed.agc_decim    ==     2) strcat(msg,"4  ");
      else if  (api->prop->dtv_agc_speed.agc_decim    ==     3) strcat(msg,"8  ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->dtv_agc_speed.agc_decim);
     break;
    #endif /*     Si2146_DTV_AGC_SPEED_PROP */
    #ifdef        Si2146_DTV_CONFIG_IF_PORT_PROP
     case         Si2146_DTV_CONFIG_IF_PORT_PROP_CODE:
      sprintf(msg,"DTV_CONFIG_IF_PORT");
       strcat(msg,separator); strcat(msg,"-DTV_OUT_TYPE   ");
           if  (api->prop->dtv_config_if_port.dtv_out_type   ==     0) strcat(msg,"LIF_IF1    ");
      else if  (api->prop->dtv_config_if_port.dtv_out_type   ==     4) strcat(msg,"LIF_SE_IF1A ");
      else                                                            sprintf(msg,"%s%d", msg, api->prop->dtv_config_if_port.dtv_out_type);
       strcat(msg,separator); strcat(msg,"-DTV_AGC_SOURCE ");
           if  (api->prop->dtv_config_if_port.dtv_agc_source ==     0) strcat(msg,"INTERNAL     ");
      else if  (api->prop->dtv_config_if_port.dtv_agc_source ==     1) strcat(msg,"DLIF_AGC_3DB ");
      else if  (api->prop->dtv_config_if_port.dtv_agc_source ==     3) strcat(msg,"DLIF_AGC_FULL ");
      else                                                            sprintf(msg,"%s%d", msg, api->prop->dtv_config_if_port.dtv_agc_source);
     break;
    #endif /*     Si2146_DTV_CONFIG_IF_PORT_PROP */
    #ifdef        Si2146_DTV_EXT_AGC_PROP
     case         Si2146_DTV_EXT_AGC_PROP_CODE:
      sprintf(msg,"DTV_EXT_AGC");
       strcat(msg,separator); strcat(msg,"-MIN_10MV "); sprintf(msg,"%s%d", msg, api->prop->dtv_ext_agc.min_10mv);
       strcat(msg,separator); strcat(msg,"-MAX_10MV "); sprintf(msg,"%s%d", msg, api->prop->dtv_ext_agc.max_10mv);
     break;
    #endif /*     Si2146_DTV_EXT_AGC_PROP */
    #ifdef        Si2146_DTV_IEN_PROP
     case         Si2146_DTV_IEN_PROP_CODE:
      sprintf(msg,"DTV_IEN");
       strcat(msg,separator); strcat(msg,"-CHLIEN ");
           if  (api->prop->dtv_ien.chlien ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->dtv_ien.chlien ==     1) strcat(msg,"ENABLE ");
      else                                         sprintf(msg,"%s%d", msg, api->prop->dtv_ien.chlien);
     break;
    #endif /*     Si2146_DTV_IEN_PROP */
    #ifdef        Si2146_DTV_INITIAL_AGC_SPEED_PROP
     case         Si2146_DTV_INITIAL_AGC_SPEED_PROP_CODE:
      sprintf(msg,"DTV_INITIAL_AGC_SPEED");
       strcat(msg,separator); strcat(msg,"-IF_AGC_SPEED ");
           if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==     0) strcat(msg,"AUTO ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==    39) strcat(msg,"39   ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==    54) strcat(msg,"54   ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==    63) strcat(msg,"63   ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==    89) strcat(msg,"89   ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   105) strcat(msg,"105  ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   121) strcat(msg,"121  ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   137) strcat(msg,"137  ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   158) strcat(msg,"158  ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   172) strcat(msg,"172  ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   185) strcat(msg,"185  ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   196) strcat(msg,"196  ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   206) strcat(msg,"206  ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   216) strcat(msg,"216  ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   219) strcat(msg,"219  ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   222) strcat(msg,"222  ");
      else                                                             sprintf(msg,"%s%d", msg, api->prop->dtv_initial_agc_speed.if_agc_speed);
       strcat(msg,separator); strcat(msg,"-AGC_DECIM ");
           if  (api->prop->dtv_initial_agc_speed.agc_decim    ==     0) strcat(msg,"OFF ");
      else if  (api->prop->dtv_initial_agc_speed.agc_decim    ==     1) strcat(msg,"2   ");
      else if  (api->prop->dtv_initial_agc_speed.agc_decim    ==     2) strcat(msg,"4   ");
      else if  (api->prop->dtv_initial_agc_speed.agc_decim    ==     3) strcat(msg,"8   ");
      else                                                             sprintf(msg,"%s%d", msg, api->prop->dtv_initial_agc_speed.agc_decim);
     break;
    #endif /*     Si2146_DTV_INITIAL_AGC_SPEED_PROP */
    #ifdef        Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
     case         Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE:
      sprintf(msg,"DTV_INITIAL_AGC_SPEED_PERIOD");
       strcat(msg,separator); strcat(msg,"-PERIOD "); sprintf(msg,"%s%d", msg, api->prop->dtv_initial_agc_speed_period.period);
     break;
    #endif /*     Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
    #ifdef        Si2146_DTV_INT_SENSE_PROP
     case         Si2146_DTV_INT_SENSE_PROP_CODE:
      sprintf(msg,"DTV_INT_SENSE");
       strcat(msg,separator); strcat(msg,"-CHLNEGEN ");
           if  (api->prop->dtv_int_sense.chlnegen ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->dtv_int_sense.chlnegen ==     1) strcat(msg,"ENABLE ");
      else                                                 sprintf(msg,"%s%d", msg, api->prop->dtv_int_sense.chlnegen);
       strcat(msg,separator); strcat(msg,"-CHLPOSEN ");
           if  (api->prop->dtv_int_sense.chlposen ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->dtv_int_sense.chlposen ==     1) strcat(msg,"ENABLE ");
      else                                                 sprintf(msg,"%s%d", msg, api->prop->dtv_int_sense.chlposen);
     break;
    #endif /*     Si2146_DTV_INT_SENSE_PROP */
    #ifdef        Si2146_DTV_LIF_FREQ_PROP
     case         Si2146_DTV_LIF_FREQ_PROP_CODE:
      sprintf(msg,"DTV_LIF_FREQ");
       strcat(msg,separator); strcat(msg,"-OFFSET "); sprintf(msg,"%s%d", msg, api->prop->dtv_lif_freq.offset);
     break;
    #endif /*     Si2146_DTV_LIF_FREQ_PROP */
    #ifdef        Si2146_DTV_LIF_OUT_PROP
     case         Si2146_DTV_LIF_OUT_PROP_CODE:
      sprintf(msg,"DTV_LIF_OUT");
       strcat(msg,separator); strcat(msg,"-OFFSET "); sprintf(msg,"%s%d", msg, api->prop->dtv_lif_out.offset);
       strcat(msg,separator); strcat(msg,"-AMP    "); sprintf(msg,"%s%d", msg, api->prop->dtv_lif_out.amp);
     break;
    #endif /*     Si2146_DTV_LIF_OUT_PROP */
    #ifdef        Si2146_DTV_MODE_PROP
     case         Si2146_DTV_MODE_PROP_CODE:
      sprintf(msg,"DTV_MODE");
       strcat(msg,separator); strcat(msg,"-BW              ");
           if  (api->prop->dtv_mode.bw              ==     6) strcat(msg,"BW_6MHZ ");
      else if  (api->prop->dtv_mode.bw              ==     7) strcat(msg,"BW_7MHZ ");
      else if  (api->prop->dtv_mode.bw              ==     8) strcat(msg,"BW_8MHZ ");
      else                                                   sprintf(msg,"%s%d", msg, api->prop->dtv_mode.bw);
       strcat(msg,separator); strcat(msg,"-MODULATION      ");
           if  (api->prop->dtv_mode.modulation      ==     0) strcat(msg,"ATSC  ");
      else if  (api->prop->dtv_mode.modulation      ==     1) strcat(msg,"QAM_US ");
      else if  (api->prop->dtv_mode.modulation      ==     2) strcat(msg,"DVBT  ");
      else if  (api->prop->dtv_mode.modulation      ==     3) strcat(msg,"DVBC  ");
      else if  (api->prop->dtv_mode.modulation      ==     4) strcat(msg,"ISDBT ");
      else if  (api->prop->dtv_mode.modulation      ==     5) strcat(msg,"ISDBC ");
      else if  (api->prop->dtv_mode.modulation      ==     6) strcat(msg,"DTMB  ");
      else if  (api->prop->dtv_mode.modulation      ==    15) strcat(msg,"CW    ");
      else                                                   sprintf(msg,"%s%d", msg, api->prop->dtv_mode.modulation);
       strcat(msg,separator); strcat(msg,"-INVERT_SPECTRUM ");
           if  (api->prop->dtv_mode.invert_spectrum ==     0) strcat(msg,"NORMAL  ");
      else if  (api->prop->dtv_mode.invert_spectrum ==     1) strcat(msg,"INVERTED ");
      else                                                   sprintf(msg,"%s%d", msg, api->prop->dtv_mode.invert_spectrum);
     break;
    #endif /*     Si2146_DTV_MODE_PROP */
    #ifdef        Si2146_DTV_RF_TOP_PROP
     case         Si2146_DTV_RF_TOP_PROP_CODE:
      sprintf(msg,"DTV_RF_TOP");
       strcat(msg,separator); strcat(msg,"-DTV_RF_TOP ");
           if  (api->prop->dtv_rf_top.dtv_rf_top ==     0) strcat(msg,"AUTO ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==     6) strcat(msg,"0DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==     7) strcat(msg,"M1DB ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==     8) strcat(msg,"M2DB ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==     9) strcat(msg,"M3DB ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    10) strcat(msg,"M4DB ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    11) strcat(msg,"M5DB ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    12) strcat(msg,"M6DB ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    13) strcat(msg,"M7DB ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    14) strcat(msg,"M8DB ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    15) strcat(msg,"M9DB ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    16) strcat(msg,"M10DB ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    17) strcat(msg,"M11DB ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    18) strcat(msg,"M12DB ");
      else                                                sprintf(msg,"%s%d", msg, api->prop->dtv_rf_top.dtv_rf_top);
     break;
    #endif /*     Si2146_DTV_RF_TOP_PROP */
    #ifdef        Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_CODE:
      sprintf(msg,"DTV_RSQ_RSSI_THRESHOLD");
       strcat(msg,separator); strcat(msg,"-LO "); sprintf(msg,"%s%d", msg, api->prop->dtv_rsq_rssi_threshold.lo);
       strcat(msg,separator); strcat(msg,"-HI "); sprintf(msg,"%s%d", msg, api->prop->dtv_rsq_rssi_threshold.hi);
     break;
    #endif /*     Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2146_MASTER_IEN_PROP
     case         Si2146_MASTER_IEN_PROP_CODE:
      sprintf(msg,"MASTER_IEN");
       strcat(msg,separator); strcat(msg,"-TUNIEN ");
           if  (api->prop->master_ien.tunien ==     0) strcat(msg,"OFF ");
      else if  (api->prop->master_ien.tunien ==     1) strcat(msg,"ON ");
      else                                            sprintf(msg,"%s%d", msg, api->prop->master_ien.tunien);
       strcat(msg,separator); strcat(msg,"-ATVIEN ");
           if  (api->prop->master_ien.atvien ==     0) strcat(msg,"OFF ");
      else if  (api->prop->master_ien.atvien ==     1) strcat(msg,"ON ");
      else                                            sprintf(msg,"%s%d", msg, api->prop->master_ien.atvien);
       strcat(msg,separator); strcat(msg,"-DTVIEN ");
           if  (api->prop->master_ien.dtvien ==     0) strcat(msg,"OFF ");
      else if  (api->prop->master_ien.dtvien ==     1) strcat(msg,"ON ");
      else                                            sprintf(msg,"%s%d", msg, api->prop->master_ien.dtvien);
       strcat(msg,separator); strcat(msg,"-ERRIEN ");
           if  (api->prop->master_ien.errien ==     0) strcat(msg,"OFF ");
      else if  (api->prop->master_ien.errien ==     1) strcat(msg,"ON ");
      else                                            sprintf(msg,"%s%d", msg, api->prop->master_ien.errien);
       strcat(msg,separator); strcat(msg,"-CTSIEN ");
           if  (api->prop->master_ien.ctsien ==     0) strcat(msg,"OFF ");
      else if  (api->prop->master_ien.ctsien ==     1) strcat(msg,"ON ");
      else                                            sprintf(msg,"%s%d", msg, api->prop->master_ien.ctsien);
     break;
    #endif /*     Si2146_MASTER_IEN_PROP */
    #ifdef        Si2146_TUNER_BLOCKED_VCO_PROP
     case         Si2146_TUNER_BLOCKED_VCO_PROP_CODE:
      sprintf(msg,"TUNER_BLOCKED_VCO");
       strcat(msg,separator); strcat(msg,"-VCO_CODE "); sprintf(msg,"%s%d", msg, api->prop->tuner_blocked_vco.vco_code);
     break;
    #endif /*     Si2146_TUNER_BLOCKED_VCO_PROP */
    #ifdef        Si2146_TUNER_IEN_PROP
     case         Si2146_TUNER_IEN_PROP_CODE:
      sprintf(msg,"TUNER_IEN");
       strcat(msg,separator); strcat(msg,"-TCIEN    ");
           if  (api->prop->tuner_ien.tcien    ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->tuner_ien.tcien    ==     1) strcat(msg,"ENABLE ");
      else                                             sprintf(msg,"%s%d", msg, api->prop->tuner_ien.tcien);
       strcat(msg,separator); strcat(msg,"-RSSILIEN ");
           if  (api->prop->tuner_ien.rssilien ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->tuner_ien.rssilien ==     1) strcat(msg,"ENABLE ");
      else                                             sprintf(msg,"%s%d", msg, api->prop->tuner_ien.rssilien);
       strcat(msg,separator); strcat(msg,"-RSSIHIEN ");
           if  (api->prop->tuner_ien.rssihien ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->tuner_ien.rssihien ==     1) strcat(msg,"ENABLE ");
      else                                             sprintf(msg,"%s%d", msg, api->prop->tuner_ien.rssihien);
     break;
    #endif /*     Si2146_TUNER_IEN_PROP */
    #ifdef        Si2146_TUNER_INT_SENSE_PROP
     case         Si2146_TUNER_INT_SENSE_PROP_CODE:
      sprintf(msg,"TUNER_INT_SENSE");
       strcat(msg,separator); strcat(msg,"-TCNEGEN    ");
           if  (api->prop->tuner_int_sense.tcnegen    ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->tuner_int_sense.tcnegen    ==     1) strcat(msg,"ENABLE ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->tuner_int_sense.tcnegen);
       strcat(msg,separator); strcat(msg,"-RSSILNEGEN ");
           if  (api->prop->tuner_int_sense.rssilnegen ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->tuner_int_sense.rssilnegen ==     1) strcat(msg,"ENABLE ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->tuner_int_sense.rssilnegen);
       strcat(msg,separator); strcat(msg,"-RSSIHNEGEN ");
           if  (api->prop->tuner_int_sense.rssihnegen ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->tuner_int_sense.rssihnegen ==     1) strcat(msg,"ENABLE ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->tuner_int_sense.rssihnegen);
       strcat(msg,separator); strcat(msg,"-TCPOSEN    ");
           if  (api->prop->tuner_int_sense.tcposen    ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->tuner_int_sense.tcposen    ==     1) strcat(msg,"ENABLE ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->tuner_int_sense.tcposen);
       strcat(msg,separator); strcat(msg,"-RSSILPOSEN ");
           if  (api->prop->tuner_int_sense.rssilposen ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->tuner_int_sense.rssilposen ==     1) strcat(msg,"ENABLE ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->tuner_int_sense.rssilposen);
       strcat(msg,separator); strcat(msg,"-RSSIHPOSEN ");
           if  (api->prop->tuner_int_sense.rssihposen ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->tuner_int_sense.rssihposen ==     1) strcat(msg,"ENABLE ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->tuner_int_sense.rssihposen);
     break;
    #endif /*     Si2146_TUNER_INT_SENSE_PROP */
    #ifdef        Si2146_TUNER_LO_INJECTION_PROP
     case         Si2146_TUNER_LO_INJECTION_PROP_CODE:
      sprintf(msg,"TUNER_LO_INJECTION");
       strcat(msg,separator); strcat(msg,"-BAND_1 ");
           if  (api->prop->tuner_lo_injection.band_1 ==     0) strcat(msg,"LOW_SIDE ");
      else if  (api->prop->tuner_lo_injection.band_1 ==     1) strcat(msg,"HIGH_SIDE ");
      else                                                    sprintf(msg,"%s%d", msg, api->prop->tuner_lo_injection.band_1);
       strcat(msg,separator); strcat(msg,"-BAND_2 ");
           if  (api->prop->tuner_lo_injection.band_2 ==     0) strcat(msg,"LOW_SIDE ");
      else if  (api->prop->tuner_lo_injection.band_2 ==     1) strcat(msg,"HIGH_SIDE ");
      else                                                    sprintf(msg,"%s%d", msg, api->prop->tuner_lo_injection.band_2);
       strcat(msg,separator); strcat(msg,"-BAND_3 ");
           if  (api->prop->tuner_lo_injection.band_3 ==     0) strcat(msg,"LOW_SIDE ");
      else if  (api->prop->tuner_lo_injection.band_3 ==     1) strcat(msg,"HIGH_SIDE ");
      else                                                    sprintf(msg,"%s%d", msg, api->prop->tuner_lo_injection.band_3);
       strcat(msg,separator); strcat(msg,"-BAND_4 ");
           if  (api->prop->tuner_lo_injection.band_4 ==     0) strcat(msg,"LOW_SIDE ");
      else if  (api->prop->tuner_lo_injection.band_4 ==     1) strcat(msg,"HIGH_SIDE ");
      else                                                    sprintf(msg,"%s%d", msg, api->prop->tuner_lo_injection.band_4);
       strcat(msg,separator); strcat(msg,"-BAND_5 ");
           if  (api->prop->tuner_lo_injection.band_5 ==     0) strcat(msg,"LOW_SIDE ");
      else if  (api->prop->tuner_lo_injection.band_5 ==     1) strcat(msg,"HIGH_SIDE ");
      else                                                    sprintf(msg,"%s%d", msg, api->prop->tuner_lo_injection.band_5);
     break;
    #endif /*     Si2146_TUNER_LO_INJECTION_PROP */
   default : sprintf(msg,"Unknown property code '0x%06x'\n", prop_code); break;
    }
  }
  /* _get_property_string_insertion_point */
#endif /* Si2146_GET_PROPERTY_STRING */






