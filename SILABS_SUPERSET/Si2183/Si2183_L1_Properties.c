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
                  Silicon Laboratories Broadcast Si2183 Layer 1 API


   API properties definitions
   FILE: Si2183_L1_Properties.c
   Supported IC : Si2183
   Compiled for ROM 2 firmware 5_B_build_1
   Revision: V0.3.5.1
   Tag:  V0.3.5.1
   Date: November 06 2015
**************************************************************************************/
/* Change log:

 As from V0.3.3.0:
    <improvement>[TERACOM/BER] In Si2183_storeUserProperties: Setting BER depth 10e-7.
      This is not required anymore to pass Nordig (i.e. Teracom)/DBook tests due to test specification changes

 As from V0.2.8.0:
   <improvement>[DVB-C2/AFC]
     Changing DVB-C2 AFC range to 100 kHz, to reflect the fact that DVB-C2 has very small AFC offset once tuned (DVB-C2 is a 2-step process)
     prop->dvbc2_afc_range.range_khz  =   100; (default   550)
   <improvement>[ISDB-T/Lock_time] In Si2183_storeUserProperties:
      prop->isdbt_mode.dl_config = Si2183_ISDBT_MODE_PROP_DL_CONFIG_B_AND_C_LOCKED;
      This is to optimize lock time in countries such as Brazil or Japan.

 As from V0.2.7.0:
   <improvement>[Non_Duals]
     In Si2183_downloadDDProperties: testing part_info.pmajor to avoid sending SEC_TS properties in parts not supporting this property.
   <New_feature>[ISDB-T/]
     Adding isdbt_mode.tradeoff field to allow a mode with KEEP_PACKET_ORDER.
   <improvement>[TS/TS_freq]
     dd_ts_freq_max.req_freq_max_10khz is now 14600.

 As from V0.2.5.0:
   <New_feature>[Config/DriveTS] In Si2183_storeUserProperties, TS property drive default values are commented.
     Default values are set in Si2183_L1_API_Init and can be controlled using SiLabs_API_TS_Strength_Shape.

 As from V0.2.5.0:
    <Improvement>[traces] In Si2183_L1_SetProperty: tracing property code and value only if not tracing the property string

 As from V0.2.4.0:
   <New_feature>[Config/TS] In Si2183_storeUserProperties, TS property default values are commented.
     Default values are set in Si2183_L1_API_Init and can be controlled using SiLabs_API_TS_Config.

 As from V0.1.7.0:
  <compatibility>[SILABS_SUPERSET/PROPERTIES] Not returning with an error if a property is unknown in all Si2183_downloadXXProperties functions.
    This is because the code needs to be compatible with older parts not supporting the full property set present in the code.
    If the Si2183_downloadXXProperties returns when a property is unknown, the remaining properties in this function are not set, and we don't want this.
    This makes the code robust to new properties being added to the latest FWs when older parts don't support them.
    Only useful for 'legacy' parts compatibility.

 As from V0.1.6.0:
  <compatibility>[SILABS_SUPERSET/TER/SAT] Replacing tags in several functions  to allow compiling for TER-only or SAT-only
  Si2183_storeUserProperties
  Si2183_downloadSCANProperties
  Si2183_PackProperty
  Si2183_UnpackProperty
  Si2183_L1_GetCommandResponseString
  Si2183_storePropertiesDefaults
  Si2183_L1_PropertyText

 As from V0.1.3.0:
  <new_feature>[ISDB-T/AC_data] Adding 'filtering' to Si2183_ISDBT_AC_SELECT_PROP

 As from V0.1.2.0:
  <improvement>[DVB-C/BLINDSCAN] Setting prop->dvbc_afc_range.range_khz back to 100 kHz in Si2183_storeUserProperties, since this
   needs to be set to 200 only during DVB-C blindscan/blindlock (to improve blindscan/blinlock performance in presence of N-1 ACI).
   This is now handled at L2 level.

 As from V0.1.0.0:
  <improvement>[traces] In Si2183_L1_SetProperty: tracing property fields from prop instead of propShadow,
   to trace the final values of the property fields instead of the previous ones
  <improvement>[DVB-C/BLINDSCAN] setting prop->dvbc_afc_range.range_khz to 200 kHz, to improve blindscan/blinlock performance in presence of N-1 ACI.

 As from V0.0.8.0: <improvement>[SAT/AFC_RANGE] In Si2183_storeUserProperties: SAT afc_range set to 5000 instead of 4000 previously.
  This is to adapt the afc range to the new behavior of the FW, which is now returning 'no lock' as soon as the frequency error is above the selected afc_range.
  (The previous FW behavior lead to a 25% margin on afc_range, so 4000 corresponded to max 5000 in reality.)

 As from V0.0.7.0: <new_feature>[Properties/Traces] In Si2183_L1_SetProperty: tracing property text in all cases, not only when it works.
  This makes it easier to identify properties generating errors.

 As from V0.0.6.0:
  <compatibility>[Duals/Si216x2] In Si2183_downloadDDProperties: Setting 'dual' properties only for Si216x2 parts
  <new_feature>[TS/CLOCK] Adding Si2183_DD_TS_FREQ_MAX_PROP

 As from V0.0.6.0:
  <new_feature>[ISDBT/MODE] Adding isdbt_mode.dl_config to Si2183_ISDBT_MODE property

 As from V0.0.5.0:
  <improvement>[Code_size] Using the textBuffer in Si2183_L1_Context when filling text strings
    In Si2183_L1_SetProperty and Si2183_L1_SetProperty2
  <improvement>[SAT/TONE] In Si2183_storeUserProperties: Setting api->prop->dd_diseqc_freq.freq_hz to 0 to select 'envelop mode'
  <improvement> [TS_spurious/DUAL] In Si2183_storeUserProperties: adapting parallel TS for no TS interference (from field experience):
      prop->dd_sec_ts_setup_par.ts_data_strength                             =     3;
      prop->dd_sec_ts_setup_par.ts_data_shape                                =     2;
      prop->dd_sec_ts_setup_par.ts_clk_strength                              =     3;
      prop->dd_sec_ts_setup_par.ts_clk_shape                                 =     2;

      prop->dd_ts_setup_par.ts_data_strength                                 =     3;
      prop->dd_ts_setup_par.ts_data_shape                                    =     2;
      prop->dd_ts_setup_par.ts_clk_strength                                  =     3;
      prop->dd_ts_setup_par.ts_clk_shape                                     =     2;

 As from V0.0.4.0:
  <improvement>[NOT_a_DUAL] In Si2183_downloadDDProperties: skipping DD_SEC_TS property settings if demod is a single (to avoid raising API unnecessary errors).

 As from V0.0.3.0:
   <improvement>[TERACOM/BER] In Si2183_storeUserProperties: adding caution message to warn the user that BER settings are
   overwritten at L3 Wrapper level
   <new_feature/DISEQC> Adding dd_diseqc_param.input_pin field
   <new_feature/TS_SERIAL/D7> Adding dd_ts_mode.serial_pin_selection, to allow routing serial TS on Dx (DO is used by default)
   <improvement/MCNS> mcns_symbol_rate.rate set by default at 5361, a MCNS-compatible SR.

 As from V0.0.0.3:
   <improvement> [TS_spurious/DUAL] In Si2183_storeUserProperties:
      prop->dd_ts_setup_par.ts_data_strength                                 =     4;
      prop->dd_ts_setup_par.ts_data_shape                                    =     0;
      prop->dd_ts_setup_par.ts_clk_strength                                  =     4;
      prop->dd_ts_setup_par.ts_clk_shape                                     =     0;

      prop->dd_ts_setup_ser.ts_data_strength                                 =     7;
      prop->dd_ts_setup_ser.ts_data_shape                                    =     0;
      prop->dd_ts_setup_ser.ts_clk_strength                                  =     7;
      prop->dd_ts_setup_ser.ts_clk_shape                                     =     0;

   <improvement> [Teracom/BEST_MUX] In Si2183_storeUserProperties: Changing BER resolution
    to match Teracom BEST_MUX test specification
     prop->dd_ber_resol.exp  = 5;
     prop->dd_ber_resol.mant = 8;

   <new_feature> [ISDB-T/LAYER] Adding ISDBT_MODE property to select the layer used
    for BER, CBER, PER, and UNCOR monitoring.

 As from V0.0.0.0:
  Initial version (based on Si2164 code V0.3.4)
****************************************************************************************/

#define   Si2183_COMMAND_PROTOTYPES

/* Before including the headers, define SiLevel and SiTAG */
#define   SiLEVEL          1

#include "Si2183_Platform_Definition.h"

/* Re-definition of SiTRACE for Si2183_PropObj */
#ifdef    SiTRACES
  #undef  SiTRACE
  #define SiTRACE(...)        SiTraceFunction(SiLEVEL, "", __FILE__, __LINE__, __func__     ,__VA_ARGS__)
#endif /* SiTRACES */

/***********************************************************************************************************************
  Si2183_storeUserProperties function
  Use:        property preparation function
              Used to fill the prop structure with user values.
  Parameter: *prop    a property structure to be filled

  Returns:    void
 ***********************************************************************************************************************/
void          Si2183_storeUserProperties    (Si2183_PropObj   *prop) {
#ifdef    Si2183_MASTER_IEN_PROP
  prop->master_ien.ddien                                                 = Si2183_MASTER_IEN_PROP_DDIEN_OFF   ; /* (default 'OFF') */
  prop->master_ien.scanien                                               = Si2183_MASTER_IEN_PROP_SCANIEN_OFF ; /* (default 'OFF') */
  prop->master_ien.errien                                                = Si2183_MASTER_IEN_PROP_ERRIEN_OFF  ; /* (default 'OFF') */
  prop->master_ien.ctsien                                                = Si2183_MASTER_IEN_PROP_CTSIEN_OFF  ; /* (default 'OFF') */
#endif /* Si2183_MASTER_IEN_PROP */

#ifdef    Si2183_DD_BER_RESOL_PROP
  prop->dd_ber_resol.exp                                                 =     7; /* (default     7) */
  prop->dd_ber_resol.mant                                                =     1; /* (default     1) */
#endif /* Si2183_DD_BER_RESOL_PROP */

#ifdef    Si2183_DD_CBER_RESOL_PROP
  prop->dd_cber_resol.exp                                                =     5; /* (default     5) */
  prop->dd_cber_resol.mant                                               =     1; /* (default     1) */
#endif /* Si2183_DD_CBER_RESOL_PROP */

#ifdef    Si2183_DD_DISEQC_FREQ_PROP
  prop->dd_diseqc_freq.freq_hz                                           = 0; /* (default 22000, '0' means 'envelop mode') */
#endif /* Si2183_DD_DISEQC_FREQ_PROP */

#ifdef    Si2183_DD_DISEQC_PARAM_PROP
  prop->dd_diseqc_param.sequence_mode                                    = Si2183_DD_DISEQC_PARAM_PROP_SEQUENCE_MODE_GAP       ; /* (default 'GAP') */
  prop->dd_diseqc_param.input_pin                                        = Si2183_DD_DISEQC_PARAM_PROP_INPUT_PIN_DISEQC_IN     ; /* (default 'DISEQC_IN') */
#endif /* Si2183_DD_DISEQC_PARAM_PROP */

#ifdef    Si2183_DD_FER_RESOL_PROP
  prop->dd_fer_resol.exp                                                 =     3; /* (default     3) */
  prop->dd_fer_resol.mant                                                =     1; /* (default     1) */
#endif /* Si2183_DD_FER_RESOL_PROP */

#ifdef    Si2183_DD_IEN_PROP
  prop->dd_ien.ien_bit0                                                  = Si2183_DD_IEN_PROP_IEN_BIT0_DISABLE ; /* (default 'DISABLE') */
  prop->dd_ien.ien_bit1                                                  = Si2183_DD_IEN_PROP_IEN_BIT1_DISABLE ; /* (default 'DISABLE') */
  prop->dd_ien.ien_bit2                                                  = Si2183_DD_IEN_PROP_IEN_BIT2_DISABLE ; /* (default 'DISABLE') */
  prop->dd_ien.ien_bit3                                                  = Si2183_DD_IEN_PROP_IEN_BIT3_DISABLE ; /* (default 'DISABLE') */
  prop->dd_ien.ien_bit4                                                  = Si2183_DD_IEN_PROP_IEN_BIT4_DISABLE ; /* (default 'DISABLE') */
  prop->dd_ien.ien_bit5                                                  = Si2183_DD_IEN_PROP_IEN_BIT5_DISABLE ; /* (default 'DISABLE') */
  prop->dd_ien.ien_bit6                                                  = Si2183_DD_IEN_PROP_IEN_BIT6_DISABLE ; /* (default 'DISABLE') */
  prop->dd_ien.ien_bit7                                                  = Si2183_DD_IEN_PROP_IEN_BIT7_DISABLE ; /* (default 'DISABLE') */
#endif /* Si2183_DD_IEN_PROP */

#ifdef    Si2183_DD_IF_INPUT_FREQ_PROP
  prop->dd_if_input_freq.offset                                          =  5000; /* (default  5000) */
#endif /* Si2183_DD_IF_INPUT_FREQ_PROP */

#ifdef    Si2183_DD_INT_SENSE_PROP
  prop->dd_int_sense.neg_bit0                                            = Si2183_DD_INT_SENSE_PROP_NEG_BIT0_DISABLE ; /* (default 'DISABLE') */
  prop->dd_int_sense.neg_bit1                                            = Si2183_DD_INT_SENSE_PROP_NEG_BIT1_DISABLE ; /* (default 'DISABLE') */
  prop->dd_int_sense.neg_bit2                                            = Si2183_DD_INT_SENSE_PROP_NEG_BIT2_DISABLE ; /* (default 'DISABLE') */
  prop->dd_int_sense.neg_bit3                                            = Si2183_DD_INT_SENSE_PROP_NEG_BIT3_DISABLE ; /* (default 'DISABLE') */
  prop->dd_int_sense.neg_bit4                                            = Si2183_DD_INT_SENSE_PROP_NEG_BIT4_DISABLE ; /* (default 'DISABLE') */
  prop->dd_int_sense.neg_bit5                                            = Si2183_DD_INT_SENSE_PROP_NEG_BIT5_DISABLE ; /* (default 'DISABLE') */
  prop->dd_int_sense.neg_bit6                                            = Si2183_DD_INT_SENSE_PROP_NEG_BIT6_DISABLE ; /* (default 'DISABLE') */
  prop->dd_int_sense.neg_bit7                                            = Si2183_DD_INT_SENSE_PROP_NEG_BIT7_DISABLE ; /* (default 'DISABLE') */
  prop->dd_int_sense.pos_bit0                                            = Si2183_DD_INT_SENSE_PROP_POS_BIT0_DISABLE  ; /* (default 'ENABLE') */
  prop->dd_int_sense.pos_bit1                                            = Si2183_DD_INT_SENSE_PROP_POS_BIT1_DISABLE  ; /* (default 'ENABLE') */
  prop->dd_int_sense.pos_bit2                                            = Si2183_DD_INT_SENSE_PROP_POS_BIT2_DISABLE  ; /* (default 'ENABLE') */
  prop->dd_int_sense.pos_bit3                                            = Si2183_DD_INT_SENSE_PROP_POS_BIT3_DISABLE  ; /* (default 'ENABLE') */
  prop->dd_int_sense.pos_bit4                                            = Si2183_DD_INT_SENSE_PROP_POS_BIT4_DISABLE  ; /* (default 'ENABLE') */
  prop->dd_int_sense.pos_bit5                                            = Si2183_DD_INT_SENSE_PROP_POS_BIT5_ENABLE  ; /* (default 'ENABLE') */
  prop->dd_int_sense.pos_bit6                                            = Si2183_DD_INT_SENSE_PROP_POS_BIT6_DISABLE  ; /* (default 'ENABLE') */
  prop->dd_int_sense.pos_bit7                                            = Si2183_DD_INT_SENSE_PROP_POS_BIT7_DISABLE  ; /* (default 'ENABLE') */
#endif /* Si2183_DD_INT_SENSE_PROP */

#ifdef    Si2183_DD_MODE_PROP
  prop->dd_mode.bw                                                       = Si2183_DD_MODE_PROP_BW_BW_8MHZ              ; /* (default 'BW_8MHZ') */
  prop->dd_mode.modulation                                               = Si2183_DD_MODE_PROP_MODULATION_DVBT         ; /* (default 'DVBT') */
  prop->dd_mode.invert_spectrum                                          = Si2183_DD_MODE_PROP_INVERT_SPECTRUM_NORMAL  ; /* (default 'NORMAL') */
  prop->dd_mode.auto_detect                                              = Si2183_DD_MODE_PROP_AUTO_DETECT_NONE        ; /* (default 'NONE') */
#endif /* Si2183_DD_MODE_PROP */

#ifdef    Si2183_DD_PER_RESOL_PROP
  prop->dd_per_resol.exp                                                 =     5; /* (default     5) */
  prop->dd_per_resol.mant                                                =     1; /* (default     1) */
#endif /* Si2183_DD_PER_RESOL_PROP */

#ifdef    Si2183_DD_RSQ_BER_THRESHOLD_PROP
  prop->dd_rsq_ber_threshold.exp                                         =     1; /* (default     1) */
  prop->dd_rsq_ber_threshold.mant                                        =    10; /* (default    10) */
#endif /* Si2183_DD_RSQ_BER_THRESHOLD_PROP */

#ifdef    Si2183_DD_SEC_TS_SERIAL_DIFF_PROP
  prop->dd_sec_ts_serial_diff.ts_data1_strength                          =    15; /* (default    15) */
  prop->dd_sec_ts_serial_diff.ts_data1_shape                             =     3; /* (default     3) */
  prop->dd_sec_ts_serial_diff.ts_data2_strength                          =    15; /* (default    15) */
  prop->dd_sec_ts_serial_diff.ts_data2_shape                             =     3; /* (default     3) */
  prop->dd_sec_ts_serial_diff.ts_clkb_on_data1                           = Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_CLKB_ON_DATA1_DISABLE   ; /* (default 'DISABLE') */
  prop->dd_sec_ts_serial_diff.ts_data0b_on_data2                         = Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA0B_ON_DATA2_DISABLE ; /* (default 'DISABLE') */
#endif /* Si2183_DD_SEC_TS_SERIAL_DIFF_PROP */

#ifdef    Si2183_DD_SEC_TS_SETUP_PAR_PROP
/*  prop->dd_sec_ts_setup_par.ts_data_strength                             =     3;*/ /* (default     3) */
/*  prop->dd_sec_ts_setup_par.ts_data_shape                                =     2;*/ /* (default     1) */
/*  prop->dd_sec_ts_setup_par.ts_clk_strength                              =     3;*/ /* (default     3) */
/*  prop->dd_sec_ts_setup_par.ts_clk_shape                                 =     2;*/ /* (default     1) */
#endif /* Si2183_DD_SEC_TS_SETUP_PAR_PROP */

#ifdef    Si2183_DD_SEC_TS_SETUP_SER_PROP
/*  prop->dd_sec_ts_setup_ser.ts_data_strength                             =     7;*/ /* (default     3) */
/*  prop->dd_sec_ts_setup_ser.ts_data_shape                                =     0;*/ /* (default     3) */
/*  prop->dd_sec_ts_setup_ser.ts_clk_strength                              =     7;*/ /* (default    15) */
/*  prop->dd_sec_ts_setup_ser.ts_clk_shape                                 =     0;*/ /* (default     3) */
#endif /* Si2183_DD_SEC_TS_SETUP_SER_PROP */

#ifdef    Si2183_DD_SEC_TS_SLR_SERIAL_PROP
  prop->dd_sec_ts_slr_serial.ts_data_slr                                 =     0; /* (default     0) */
  prop->dd_sec_ts_slr_serial.ts_data_slr_on                              = Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA_SLR_ON_DISABLE  ; /* (default 'DISABLE') */
  prop->dd_sec_ts_slr_serial.ts_data1_slr                                =     0; /* (default     0) */
  prop->dd_sec_ts_slr_serial.ts_data1_slr_on                             = Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA1_SLR_ON_DISABLE ; /* (default 'DISABLE') */
  prop->dd_sec_ts_slr_serial.ts_data2_slr                                =     0; /* (default     0) */
  prop->dd_sec_ts_slr_serial.ts_data2_slr_on                             = Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA2_SLR_ON_DISABLE ; /* (default 'DISABLE') */
  prop->dd_sec_ts_slr_serial.ts_clk_slr                                  =     0; /* (default     0) */
  prop->dd_sec_ts_slr_serial.ts_clk_slr_on                               = Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_CLK_SLR_ON_DISABLE   ; /* (default 'DISABLE') */
#endif /* Si2183_DD_SEC_TS_SLR_SERIAL_PROP */

#ifdef    Si2183_DD_SSI_SQI_PARAM_PROP
  prop->dd_ssi_sqi_param.sqi_average                                     =    30; /* (default     1) */
#endif /* Si2183_DD_SSI_SQI_PARAM_PROP */

#ifdef    Si2183_DD_TS_FREQ_PROP
  prop->dd_ts_freq.req_freq_10khz                                        =   720; /* (default   720) */
#endif /* Si2183_DD_TS_FREQ_PROP */

#ifdef    Si2183_DD_TS_FREQ_MAX_PROP
  prop->dd_ts_freq_max.req_freq_max_10khz                                =  14600; /* (default   14600) */
#endif /* Si2183_DD_TS_FREQ_PROP */

  /* Property fields commented below are set to default values in Si2183_L1_API_Init. These can be overwritten during SW init using SiLabs_API_TS_Config (settings are HW dependent) */
#ifdef    Si2183_DD_TS_MODE_PROP
  prop->dd_ts_mode.mode                                                  = Si2183_DD_TS_MODE_PROP_MODE_TRISTATE                   ; /* (default 'TRISTATE') */
//  prop->dd_ts_mode.clock                                                 = Si2183_DD_TS_MODE_PROP_CLOCK_AUTO_ADAPT                ; /* (default 'AUTO_FIXED') */
//  prop->dd_ts_mode.clk_gapped_en                                         = Si2183_DD_TS_MODE_PROP_CLK_GAPPED_EN_DISABLED          ; /* (default 'DISABLED') */
//  prop->dd_ts_mode.ts_err_polarity                                       = Si2183_DD_TS_MODE_PROP_TS_ERR_POLARITY_NOT_INVERTED    ; /* (default 'NOT_INVERTED') */
  prop->dd_ts_mode.special                                               = Si2183_DD_TS_MODE_PROP_SPECIAL_FULL_TS                 ; /* (default 'FULL_TS') */
  prop->dd_ts_mode.ts_freq_resolution                                    = Si2183_DD_TS_MODE_PROP_TS_FREQ_RESOLUTION_NORMAL       ; /* (default 'NORMAL') */
//  prop->dd_ts_mode.serial_pin_selection                                  = Si2183_DD_TS_MODE_PROP_SERIAL_PIN_SELECTION_D0           ; /* (default 'D0') */
#endif /* Si2183_DD_TS_MODE_PROP */

#ifdef    Si2183_DD_TS_SERIAL_DIFF_PROP
  prop->dd_ts_serial_diff.ts_data1_strength                              =    15; /* (default    15) */
  prop->dd_ts_serial_diff.ts_data1_shape                                 =     3; /* (default     3) */
  prop->dd_ts_serial_diff.ts_data2_strength                              =    15; /* (default    15) */
  prop->dd_ts_serial_diff.ts_data2_shape                                 =     3; /* (default     3) */
  prop->dd_ts_serial_diff.ts_clkb_on_data1                               = Si2183_DD_TS_SERIAL_DIFF_PROP_TS_CLKB_ON_DATA1_DISABLE   ; /* (default 'DISABLE') */
  prop->dd_ts_serial_diff.ts_data0b_on_data2                             = Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA0B_ON_DATA2_DISABLE ; /* (default 'DISABLE') */
#endif /* Si2183_DD_TS_SERIAL_DIFF_PROP */

#ifdef    Si2183_DD_TS_SETUP_PAR_PROP
/*  prop->dd_ts_setup_par.ts_data_strength                                 =     3;*/ /* (default     3) */
/*  prop->dd_ts_setup_par.ts_data_shape                                    =     2;*/ /* (default     1) */
/*  prop->dd_ts_setup_par.ts_clk_strength                                  =     3;*/ /* (default     3) */
/*  prop->dd_ts_setup_par.ts_clk_shape                                     =     2;*/ /* (default     1) */
/*  prop->dd_ts_setup_par.ts_clk_invert                                    = Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_INVERT_INVERTED    ;*/ /* (default 'INVERTED') */
  prop->dd_ts_setup_par.ts_clk_shift                                     =     0; /* (default     0) */
#endif /* Si2183_DD_TS_SETUP_PAR_PROP */

#ifdef    Si2183_DD_TS_SETUP_SER_PROP
/*  prop->dd_ts_setup_ser.ts_data_strength                                 =     7;*/ /* (default    15) */
/*  prop->dd_ts_setup_ser.ts_data_shape                                    =     0;*/ /* (default     3) */
/*  prop->dd_ts_setup_ser.ts_clk_strength                                  =     7;*/ /* (default    15) */
/*  prop->dd_ts_setup_ser.ts_clk_shape                                     =     0;*/ /* (default     3) */
/*  prop->dd_ts_setup_ser.ts_clk_invert                                    = Si2183_DD_TS_SETUP_SER_PROP_TS_CLK_INVERT_INVERTED      ;*/ /* (default 'INVERTED') */
  prop->dd_ts_setup_ser.ts_sync_duration                                 = Si2183_DD_TS_SETUP_SER_PROP_TS_SYNC_DURATION_FIRST_BYTE ; /* (default 'FIRST_BYTE') */
  prop->dd_ts_setup_ser.ts_byte_order                                    = Si2183_DD_TS_SETUP_SER_PROP_TS_BYTE_ORDER_MSB_FIRST     ; /* (default 'MSB_FIRST') */
#endif /* Si2183_DD_TS_SETUP_SER_PROP */

#ifdef    Si2183_DD_TS_SLR_SERIAL_PROP
  prop->dd_ts_slr_serial.ts_data_slr                                     =     0; /* (default     0) */
  prop->dd_ts_slr_serial.ts_data_slr_on                                  = Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA_SLR_ON_DISABLE  ; /* (default 'DISABLE') */
  prop->dd_ts_slr_serial.ts_data1_slr                                    =     0; /* (default     0) */
  prop->dd_ts_slr_serial.ts_data1_slr_on                                 = Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA1_SLR_ON_DISABLE ; /* (default 'DISABLE') */
  prop->dd_ts_slr_serial.ts_data2_slr                                    =     0; /* (default     0) */
  prop->dd_ts_slr_serial.ts_data2_slr_on                                 = Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA2_SLR_ON_DISABLE ; /* (default 'DISABLE') */
  prop->dd_ts_slr_serial.ts_clk_slr                                      =     0; /* (default     0) */
  prop->dd_ts_slr_serial.ts_clk_slr_on                                   = Si2183_DD_TS_SLR_SERIAL_PROP_TS_CLK_SLR_ON_DISABLE   ; /* (default 'DISABLE') */
#endif /* Si2183_DD_TS_SLR_SERIAL_PROP */

#ifdef    DEMOD_DVB_C
#ifdef    Si2183_DVBC_ADC_CREST_FACTOR_PROP
  prop->dvbc_adc_crest_factor.crest_factor                               =   112; /* (default   112) */
#endif /* Si2183_DVBC_ADC_CREST_FACTOR_PROP */

#ifdef    Si2183_DVBC_AFC_RANGE_PROP
  prop->dvbc_afc_range.range_khz                                         =   100; /* (default   100) */
#endif /* Si2183_DVBC_AFC_RANGE_PROP */

#ifdef    Si2183_DVBC_CONSTELLATION_PROP
  prop->dvbc_constellation.constellation                                 = Si2183_DVBC_CONSTELLATION_PROP_CONSTELLATION_AUTO ; /* (default 'AUTO') */
#endif /* Si2183_DVBC_CONSTELLATION_PROP */

#ifdef    Si2183_DVBC_SYMBOL_RATE_PROP
  prop->dvbc_symbol_rate.rate                                            =  6900; /* (default  6900) */
#endif /* Si2183_DVBC_SYMBOL_RATE_PROP */

#endif /* DEMOD_DVB_C */

#ifdef    DEMOD_DVB_C2
#ifdef    Si2183_DVBC2_ADC_CREST_FACTOR_PROP
  prop->dvbc2_adc_crest_factor.crest_factor                              =   130; /* (default   130) */
#endif /* Si2183_DVBC2_ADC_CREST_FACTOR_PROP */

#ifdef    Si2183_DVBC2_AFC_RANGE_PROP
  prop->dvbc2_afc_range.range_khz                                        =   100; /* (default   550) */
#endif /* Si2183_DVBC2_AFC_RANGE_PROP */

#endif /* DEMOD_DVB_C2 */

#ifdef    DEMOD_DVB_S_S2_DSS
#ifdef    Si2183_DVBS_ADC_CREST_FACTOR_PROP
  prop->dvbs_adc_crest_factor.crest_factor                               =   104; /* (default   104) */
#endif /* Si2183_DVBS_ADC_CREST_FACTOR_PROP */

#ifdef    Si2183_DVBS_AFC_RANGE_PROP
  prop->dvbs_afc_range.range_khz                                         =  5000; /* (default  4000) */
#endif /* Si2183_DVBS_AFC_RANGE_PROP */

#ifdef    Si2183_DVBS_SYMBOL_RATE_PROP
  prop->dvbs_symbol_rate.rate                                            = 27500; /* (default 27500) */
#endif /* Si2183_DVBS_SYMBOL_RATE_PROP */

#ifdef    Si2183_DVBS2_ADC_CREST_FACTOR_PROP
  prop->dvbs2_adc_crest_factor.crest_factor                              =   104; /* (default   104) */
#endif /* Si2183_DVBS2_ADC_CREST_FACTOR_PROP */

#ifdef    Si2183_DVBS2_AFC_RANGE_PROP
  prop->dvbs2_afc_range.range_khz                                        =  5000; /* (default  4000) */
#endif /* Si2183_DVBS2_AFC_RANGE_PROP */

#ifdef    Si2183_DVBS2_SYMBOL_RATE_PROP
  prop->dvbs2_symbol_rate.rate                                           = 27500; /* (default 27500) */
#endif /* Si2183_DVBS2_SYMBOL_RATE_PROP */

#endif /* DEMOD_DVB_S_S2_DSS */

#ifdef    DEMOD_DVB_T
#ifdef    Si2183_DVBT_ADC_CREST_FACTOR_PROP
  prop->dvbt_adc_crest_factor.crest_factor                               =   130; /* (default   130) */
#endif /* Si2183_DVBT_ADC_CREST_FACTOR_PROP */

#ifdef    Si2183_DVBT_AFC_RANGE_PROP
  prop->dvbt_afc_range.range_khz                                         =   550; /* (default   550) */
#endif /* Si2183_DVBT_AFC_RANGE_PROP */

#ifdef    Si2183_DVBT_HIERARCHY_PROP
  prop->dvbt_hierarchy.stream                                            = Si2183_DVBT_HIERARCHY_PROP_STREAM_HP ; /* (default 'HP') */
#endif /* Si2183_DVBT_HIERARCHY_PROP */

#endif /* DEMOD_DVB_T */

#ifdef    DEMOD_DVB_T2
#ifdef    Si2183_DVBT2_ADC_CREST_FACTOR_PROP
  prop->dvbt2_adc_crest_factor.crest_factor                              =   130; /* (default   130) */
#endif /* Si2183_DVBT2_ADC_CREST_FACTOR_PROP */

#ifdef    Si2183_DVBT2_AFC_RANGE_PROP
  prop->dvbt2_afc_range.range_khz                                        =   550; /* (default   550) */
#endif /* Si2183_DVBT2_AFC_RANGE_PROP */

#ifdef    Si2183_DVBT2_FEF_TUNER_PROP
  prop->dvbt2_fef_tuner.tuner_delay                                      =     1; /* (default     1) */
  prop->dvbt2_fef_tuner.tuner_freeze_time                                =     1; /* (default     1) */
  prop->dvbt2_fef_tuner.tuner_unfreeze_time                              =     1; /* (default     1) */
#endif /* Si2183_DVBT2_FEF_TUNER_PROP */

#ifdef    Si2183_DVBT2_MODE_PROP
  prop->dvbt2_mode.lock_mode                                             = Si2183_DVBT2_MODE_PROP_LOCK_MODE_ANY ; /* (default 'ANY') */
#endif /* Si2183_DVBT2_MODE_PROP */

#endif /* DEMOD_DVB_T2 */

#ifdef    DEMOD_ISDB_T
#ifdef    Si2183_ISDBT_AC_SELECT_PROP
  prop->isdbt_ac_select.segment_sel                                      = Si2183_ISDBT_AC_SELECT_PROP_SEGMENT_SEL_SEG_0 ; /* (default 'SEG_0') */
  prop->isdbt_ac_select.filtering                                        = Si2183_ISDBT_AC_SELECT_PROP_FILTERING_KEEP_ALL   ; /* (default 'KEEP_ALL') */
#endif /* Si2183_ISDBT_AC_SELECT_PROP */

#ifdef    Si2183_ISDBT_ADC_CREST_FACTOR_PROP
  prop->isdbt_adc_crest_factor.crest_factor                              =   130; /* (default   130) */
#endif /* Si2183_ISDBT_ADC_CREST_FACTOR_PROP */

#ifdef    Si2183_ISDBT_AFC_RANGE_PROP
  prop->isdbt_afc_range.range_khz                                        =   550; /* (default   550) */
#endif /* Si2183_ISDBT_AFC_RANGE_PROP */

#ifdef    Si2183_ISDBT_MODE_PROP
  prop->isdbt_mode.layer_mon                                             = Si2183_ISDBT_MODE_PROP_LAYER_MON_ALL ; /* (default 'ALL') */
  prop->isdbt_mode.dl_config                                             = Si2183_ISDBT_MODE_PROP_DL_CONFIG_B_AND_C_LOCKED ; /* (default 'ALL_LOCKED') */
  prop->isdbt_mode.tradeoff                                              = Si2183_ISDBT_MODE_PROP_TRADEOFF_OPTIMAL_PERFORMANCE  ; /* (default 'OPTIMAL_PERFORMANCE') */
#endif /* Si2183_ISDBT_MODE_PROP */

#endif /* DEMOD_ISDB_T */

#ifdef    DEMOD_MCNS
#ifdef    Si2183_MCNS_ADC_CREST_FACTOR_PROP
  prop->mcns_adc_crest_factor.crest_factor                               =   112; /* (default   112) */
#endif /* Si2183_MCNS_ADC_CREST_FACTOR_PROP */

#ifdef    Si2183_MCNS_AFC_RANGE_PROP
  prop->mcns_afc_range.range_khz                                         =   100; /* (default   100) */
#endif /* Si2183_MCNS_AFC_RANGE_PROP */

#ifdef    Si2183_MCNS_CONSTELLATION_PROP
  prop->mcns_constellation.constellation                                 = Si2183_MCNS_CONSTELLATION_PROP_CONSTELLATION_AUTO ; /* (default 'AUTO') */
#endif /* Si2183_MCNS_CONSTELLATION_PROP */

#ifdef    Si2183_MCNS_SYMBOL_RATE_PROP
  prop->mcns_symbol_rate.rate                                            =  5361; /* (default  5361) */
#endif /* Si2183_MCNS_SYMBOL_RATE_PROP */

#endif /* DEMOD_MCNS */

#ifdef    Si2183_SCAN_FMAX_PROP
  prop->scan_fmax.scan_fmax                                              =     0; /* (default     0) */
#endif /* Si2183_SCAN_FMAX_PROP */

#ifdef    Si2183_SCAN_FMIN_PROP
  prop->scan_fmin.scan_fmin                                              =     0; /* (default     0) */
#endif /* Si2183_SCAN_FMIN_PROP */

#ifdef    Si2183_SCAN_IEN_PROP
  prop->scan_ien.buzien                                                  = Si2183_SCAN_IEN_PROP_BUZIEN_DISABLE ; /* (default 'DISABLE') */
  prop->scan_ien.reqien                                                  = Si2183_SCAN_IEN_PROP_REQIEN_DISABLE ; /* (default 'DISABLE') */
#endif /* Si2183_SCAN_IEN_PROP */

#ifdef    Si2183_SCAN_INT_SENSE_PROP
  prop->scan_int_sense.buznegen                                          = Si2183_SCAN_INT_SENSE_PROP_BUZNEGEN_ENABLE  ; /* (default 'ENABLE') */
  prop->scan_int_sense.reqnegen                                          = Si2183_SCAN_INT_SENSE_PROP_REQNEGEN_DISABLE ; /* (default 'DISABLE') */
  prop->scan_int_sense.buzposen                                          = Si2183_SCAN_INT_SENSE_PROP_BUZPOSEN_DISABLE ; /* (default 'DISABLE') */
  prop->scan_int_sense.reqposen                                          = Si2183_SCAN_INT_SENSE_PROP_REQPOSEN_ENABLE  ; /* (default 'ENABLE') */
#endif /* Si2183_SCAN_INT_SENSE_PROP */

#ifdef    Si2183_SCAN_SAT_CONFIG_PROP
  prop->scan_sat_config.analog_detect                                    = Si2183_SCAN_SAT_CONFIG_PROP_ANALOG_DETECT_DISABLED ; /* (default 'DISABLED') */
  prop->scan_sat_config.reserved1                                        =     0; /* (default     0) */
  prop->scan_sat_config.reserved2                                        =    12; /* (default    12) */
#endif /* Si2183_SCAN_SAT_CONFIG_PROP */

#ifdef    Si2183_SCAN_SAT_UNICABLE_BW_PROP
  prop->scan_sat_unicable_bw.scan_sat_unicable_bw                        =     0; /* (default     0) */
#endif /* Si2183_SCAN_SAT_UNICABLE_BW_PROP */

#ifdef    Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP
  prop->scan_sat_unicable_min_tune_step.scan_sat_unicable_min_tune_step  =    50; /* (default    50) */
#endif /* Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP */

#ifdef    Si2183_SCAN_SYMB_RATE_MAX_PROP
  prop->scan_symb_rate_max.scan_symb_rate_max                            =     0; /* (default     0) */
#endif /* Si2183_SCAN_SYMB_RATE_MAX_PROP */

#ifdef    Si2183_SCAN_SYMB_RATE_MIN_PROP
  prop->scan_symb_rate_min.scan_symb_rate_min                            =     0; /* (default     0) */
#endif /* Si2183_SCAN_SYMB_RATE_MIN_PROP */

#ifdef    TERRESTRIAL_FRONT_END
#ifdef    Si2183_SCAN_TER_CONFIG_PROP
  prop->scan_ter_config.mode                                             = Si2183_SCAN_TER_CONFIG_PROP_MODE_BLIND_SCAN          ; /* (default 'BLIND_SCAN') */
  prop->scan_ter_config.analog_bw                                        = Si2183_SCAN_TER_CONFIG_PROP_ANALOG_BW_8MHZ           ; /* (default '8MHZ') */
  prop->scan_ter_config.search_analog                                    = Si2183_SCAN_TER_CONFIG_PROP_SEARCH_ANALOG_DISABLE    ; /* (default 'DISABLE') */
#endif /* Si2183_SCAN_TER_CONFIG_PROP */
#endif /* TERRESTRIAL_FRONT_END */
}
/* Re-definition of SiTRACE for L1_Si2183_Context */
#ifdef    SiTRACES
  #undef  SiTRACE
  #define SiTRACE(...)        SiTraceFunction(SiLEVEL, api->i2c->tag, __FILE__, __LINE__, __func__     ,__VA_ARGS__)
#endif /* SiTRACES */
/***********************************************************************************************************************
  Si2183_L1_SetProperty function
  Use:        property set function
              Used to call L1_SET_PROPERTY with the property Id and data provided.
  Parameter: *api     the Si2183 context
  Parameter: prop     the property Id
  Parameter: data     the property bytes
  Behavior:  This function will only download the property if required.
               Conditions to download the property are:
                - The property changes
                - The propertyWriteMode is set to Si2183_DOWNLOAD_ALWAYS
                - The property is unknown to Si2183_PackProperty (this may be useful for debug purpose)
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
unsigned char Si2183_L1_SetProperty         (L1_Si2183_Context *api, unsigned int prop_code, signed   int  data) {
    signed   int   shadowData;
    unsigned char  res;
    unsigned char  reserved;

    reserved          = 0;

    res = Si2183_PackProperty(api->propShadow, prop_code, &shadowData);

    /* -- Download property only if required --     */
    if ( ( (data != shadowData)  || (api->propertyWriteMode == Si2183_DOWNLOAD_ALWAYS) ) & ( res != ERROR_Si2183_UNKNOWN_PROPERTY ) ) {
      #ifndef   Si2183_GET_PROPERTY_STRING
      SiTRACE("Si2183_L1_SetProperty: Setting Property 0x%04x to 0x%04x(%d)\n", prop_code,data,data);
      #endif /* Si2183_GET_PROPERTY_STRING */
      res = Si2183_L1_SET_PROPERTY (api, reserved, prop_code, data);
      #ifdef    Si2183_GET_PROPERTY_STRING
      Si2183_L1_PropertyText(api->prop, prop_code, (char*)" ", api->msg);
      SiTRACE("%s\n",api->msg);
      #endif /* Si2183_GET_PROPERTY_STRING */
      if (res != NO_Si2183_ERROR) {
        SiTRACE("\nERROR: Si2183_L1_SetProperty: %s 0x%04x!\n\n", Si2183_L1_API_ERROR_TEXT(res), prop_code);
      } else {
        /* Update propShadow with latest data if correctly set */
        Si2183_UnpackProperty   (api->propShadow, prop_code, data);
      }
    }
  return res;
}
/***********************************************************************************************************************
  Si2183_L1_GetProperty function
  Use:        property get function
              Used to call L1_GET_PROPERTY with the property Id provided.
  Parameter: *api     the Si2183 context
  Parameter: prop     the property Id
  Parameter: *data    a buffer to store the property bytes into
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
unsigned char Si2183_L1_GetProperty         (L1_Si2183_Context *api, unsigned int prop_code, signed   int *data) {
    unsigned char  reserved          = 0;
    unsigned char res;
    res = Si2183_L1_GET_PROPERTY (api, reserved, prop_code);
    *data = api->rsp->get_property.data;
    return res;
}
 /***********************************************************************************************************************
  Si2183_L1_SetProperty2 function
  Use:        Sets the property given the property code.
  Parameter: *api     the Si2183 context
  Parameter: prop     the property Id

  Returns:    NO_Si2183_ERROR if successful.
 ***********************************************************************************************************************/
unsigned char Si2183_L1_SetProperty2        (L1_Si2183_Context *api, unsigned int prop_code) {
    int data, res;
    res = Si2183_PackProperty(api->prop, prop_code, &data);
    if (res != NO_Si2183_ERROR) {
      STRING_APPEND_SAFE(api->msg,1000, "\nSi2183_L1_SetProperty2: %s 0x%04x!\n\n", Si2183_L1_API_ERROR_TEXT(res), prop_code);
      SiTRACE("%s\n", api->msg);
      #ifdef    Si2183_GET_PROPERTY_STRING
      Si2183_L1_PropertyText(api->propShadow, prop_code, (char*)" ", api->msg);
      SiTRACE("%s\n",api->msg);
      #endif /* Si2183_GET_PROPERTY_STRING */
      SiERROR(api->msg);
      return res;
    }
    return Si2183_L1_SetProperty (api, prop_code & 0xffff, data);
  }
 /***********************************************************************************************************************
  Si2183_L1_GetProperty2 function
  Use:        property get function
              Used to call L1_GET_PROPERTY with the property Id provided.
  Parameter: *api     the Si2183 context
  Parameter: prop     the property Id

  Returns:    NO_Si2183_ERROR if successful.
 ***********************************************************************************************************************/
unsigned char Si2183_L1_GetProperty2        (L1_Si2183_Context *api, unsigned int prop_code) {
  int data, res;
  res = Si2183_L1_GetProperty(api, prop_code & 0xffff, &data);
  if (res != NO_Si2183_ERROR) {
    SiTRACE("Si2183_L1_GetProperty2: %s 0x%04x\n", Si2183_L1_API_ERROR_TEXT(res), prop_code);
    SiERROR(Si2183_L1_API_ERROR_TEXT(res));
    return res;
  }
  return Si2183_UnpackProperty(api->prop, prop_code, data);
}
/*****************************************************************************************
 NAME: Si2183_downloadCOMMONProperties
  DESCRIPTION: Setup Si2183 COMMON properties configuration
  This function will download all the COMMON configuration properties.
  The function Si2183_storeUserProperties should be called before the first call to this function.
  Parameter:  Pointer to Si2183 Context
  Returns:    I2C transaction error code, NO_Si2183_ERROR if successful
  Programming Guide Reference:    COMMON setup flowchart
******************************************************************************************/
int  Si2183_downloadCOMMONProperties      (L1_Si2183_Context *api) {
  SiTRACE("Si2183_downloadCOMMONProperties\n");
#ifdef    Si2183_MASTER_IEN_PROP
  Si2183_L1_SetProperty2(api, Si2183_MASTER_IEN_PROP_CODE);
#endif /* Si2183_MASTER_IEN_PROP */
return NO_Si2183_ERROR;
}
/*****************************************************************************************
 NAME: Si2183_downloadDDProperties
  DESCRIPTION: Setup Si2183 DD properties configuration
  This function will download all the DD configuration properties.
  The function Si2183_storeUserProperties should be called before the first call to this function.
  Parameter:  Pointer to Si2183 Context
  Returns:    I2C transaction error code, NO_Si2183_ERROR if successful
  Programming Guide Reference:    DD setup flowchart
******************************************************************************************/
int  Si2183_downloadDDProperties          (L1_Si2183_Context *api) {
  SiTRACE("Si2183_downloadDDProperties\n");
#ifdef    Si2183_DD_BER_RESOL_PROP
  Si2183_L1_SetProperty2(api, Si2183_DD_BER_RESOL_PROP_CODE);
#endif /* Si2183_DD_BER_RESOL_PROP */
#ifdef    Si2183_DD_CBER_RESOL_PROP
  Si2183_L1_SetProperty2(api, Si2183_DD_CBER_RESOL_PROP_CODE);
#endif /* Si2183_DD_CBER_RESOL_PROP */
#ifdef    SATELLITE_FRONT_END
#ifdef    Si2183_DD_DISEQC_FREQ_PROP
  Si2183_L1_SetProperty2(api, Si2183_DD_DISEQC_FREQ_PROP_CODE);
#endif /* Si2183_DD_DISEQC_FREQ_PROP */
#ifdef    Si2183_DD_DISEQC_PARAM_PROP
  Si2183_L1_SetProperty2(api, Si2183_DD_DISEQC_PARAM_PROP_CODE);
#endif /* Si2183_DD_DISEQC_PARAM_PROP */
#endif /* SATELLITE_FRONT_END */

#ifdef    Si2183_DD_FER_RESOL_PROP
  Si2183_L1_SetProperty2(api, Si2183_DD_FER_RESOL_PROP_CODE);
#endif /* Si2183_DD_FER_RESOL_PROP */
#ifdef    Si2183_DD_IEN_PROP
  Si2183_L1_SetProperty2(api, Si2183_DD_IEN_PROP_CODE);
#endif /* Si2183_DD_IEN_PROP */
#ifdef    Si2183_DD_IF_INPUT_FREQ_PROP
  Si2183_L1_SetProperty2(api, Si2183_DD_IF_INPUT_FREQ_PROP_CODE);
#endif /* Si2183_DD_IF_INPUT_FREQ_PROP */
#ifdef    Si2183_DD_INT_SENSE_PROP
  Si2183_L1_SetProperty2(api, Si2183_DD_INT_SENSE_PROP_CODE);
#endif /* Si2183_DD_INT_SENSE_PROP */
#ifdef    Si2183_DD_MODE_PROP
  Si2183_L1_SetProperty2(api, Si2183_DD_MODE_PROP_CODE);
#endif /* Si2183_DD_MODE_PROP */
#ifdef    Si2183_DD_PER_RESOL_PROP
  Si2183_L1_SetProperty2(api, Si2183_DD_PER_RESOL_PROP_CODE);
#endif /* Si2183_DD_PER_RESOL_PROP */
#ifdef    Si2183_DD_RSQ_BER_THRESHOLD_PROP
  Si2183_L1_SetProperty2(api, Si2183_DD_RSQ_BER_THRESHOLD_PROP_CODE);
#endif /* Si2183_DD_RSQ_BER_THRESHOLD_PROP */
  if ( (api->rsp->get_rev.mcm_die != Si2183_GET_REV_RESPONSE_MCM_DIE_SINGLE) && (api->rsp->part_info.pmajor >= '5') ) { /* Only for Si216x2 parts */
#ifdef    Si2183_DD_SEC_TS_SERIAL_DIFF_PROP
    Si2183_L1_SetProperty2(api, Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_CODE);
#endif /* Si2183_DD_SEC_TS_SERIAL_DIFF_PROP */
#ifdef    Si2183_DD_SEC_TS_SETUP_PAR_PROP
    Si2183_L1_SetProperty2(api, Si2183_DD_SEC_TS_SETUP_PAR_PROP_CODE);
#endif /* Si2183_DD_SEC_TS_SETUP_PAR_PROP */
#ifdef    Si2183_DD_SEC_TS_SETUP_SER_PROP
    Si2183_L1_SetProperty2(api, Si2183_DD_SEC_TS_SETUP_SER_PROP_CODE);
#endif /* Si2183_DD_SEC_TS_SETUP_SER_PROP */
#ifdef    Si2183_DD_SEC_TS_SLR_SERIAL_PROP
    Si2183_L1_SetProperty2(api, Si2183_DD_SEC_TS_SLR_SERIAL_PROP_CODE);
#endif /* Si2183_DD_SEC_TS_SLR_SERIAL_PROP */
  }
#ifdef    Si2183_DD_SSI_SQI_PARAM_PROP
  Si2183_L1_SetProperty2(api, Si2183_DD_SSI_SQI_PARAM_PROP_CODE);
#endif /* Si2183_DD_SSI_SQI_PARAM_PROP */
#ifdef    Si2183_DD_TS_FREQ_PROP
  Si2183_L1_SetProperty2(api, Si2183_DD_TS_FREQ_PROP_CODE);
#endif /* Si2183_DD_TS_FREQ_PROP */
#ifdef    Si2183_DD_TS_FREQ_MAX_PROP
  Si2183_L1_SetProperty2(api, Si2183_DD_TS_FREQ_MAX_PROP_CODE);
#endif /* Si2183_DD_TS_FREQ_MAX_PROP */
#ifdef    Si2183_DD_TS_MODE_PROP
  Si2183_L1_SetProperty2(api, Si2183_DD_TS_MODE_PROP_CODE);
#endif /* Si2183_DD_TS_MODE_PROP */
#ifdef    Si2183_DD_TS_SERIAL_DIFF_PROP
  Si2183_L1_SetProperty2(api, Si2183_DD_TS_SERIAL_DIFF_PROP_CODE);
#endif /* Si2183_DD_TS_SERIAL_DIFF_PROP */
#ifdef    Si2183_DD_TS_SETUP_PAR_PROP
  Si2183_L1_SetProperty2(api, Si2183_DD_TS_SETUP_PAR_PROP_CODE);
#endif /* Si2183_DD_TS_SETUP_PAR_PROP */
#ifdef    Si2183_DD_TS_SETUP_SER_PROP
  Si2183_L1_SetProperty2(api, Si2183_DD_TS_SETUP_SER_PROP_CODE);
#endif /* Si2183_DD_TS_SETUP_SER_PROP */
#ifdef    Si2183_DD_TS_SLR_SERIAL_PROP
  Si2183_L1_SetProperty2(api, Si2183_DD_TS_SLR_SERIAL_PROP_CODE);
#endif /* Si2183_DD_TS_SLR_SERIAL_PROP */
return NO_Si2183_ERROR;
}
#ifdef    DEMOD_DVB_C
/*****************************************************************************************
 NAME: Si2183_downloadDVBCProperties
  DESCRIPTION: Setup Si2183 DVBC properties configuration
  This function will download all the DVBC configuration properties.
  The function Si2183_storeUserProperties should be called before the first call to this function.
  Parameter:  Pointer to Si2183 Context
  Returns:    I2C transaction error code, NO_Si2183_ERROR if successful
  Programming Guide Reference:    DVBC setup flowchart
******************************************************************************************/
int  Si2183_downloadDVBCProperties        (L1_Si2183_Context *api) {
  SiTRACE("Si2183_downloadDVBCProperties\n");
#ifdef    Si2183_DVBC_ADC_CREST_FACTOR_PROP
  Si2183_L1_SetProperty2(api, Si2183_DVBC_ADC_CREST_FACTOR_PROP_CODE);
#endif /* Si2183_DVBC_ADC_CREST_FACTOR_PROP */
#ifdef    Si2183_DVBC_AFC_RANGE_PROP
  Si2183_L1_SetProperty2(api, Si2183_DVBC_AFC_RANGE_PROP_CODE);
#endif /* Si2183_DVBC_AFC_RANGE_PROP */
#ifdef    Si2183_DVBC_CONSTELLATION_PROP
  Si2183_L1_SetProperty2(api, Si2183_DVBC_CONSTELLATION_PROP_CODE);
#endif /* Si2183_DVBC_CONSTELLATION_PROP */
#ifdef    Si2183_DVBC_SYMBOL_RATE_PROP
  Si2183_L1_SetProperty2(api, Si2183_DVBC_SYMBOL_RATE_PROP_CODE);
#endif /* Si2183_DVBC_SYMBOL_RATE_PROP */
return NO_Si2183_ERROR;
}
#endif /* DEMOD_DVB_C */

#ifdef    DEMOD_DVB_C2
/*****************************************************************************************
 NAME: Si2183_downloadDVBC2Properties
  DESCRIPTION: Setup Si2183 DVBC2 properties configuration
  This function will download all the DVBC2 configuration properties.
  The function Si2183_storeUserProperties should be called before the first call to this function.
  Parameter:  Pointer to Si2183 Context
  Returns:    I2C transaction error code, NO_Si2183_ERROR if successful
  Programming Guide Reference:    DVBC2 setup flowchart
******************************************************************************************/
int  Si2183_downloadDVBC2Properties       (L1_Si2183_Context *api) {
  SiTRACE("Si2183_downloadDVBC2Properties\n");
#ifdef    Si2183_DVBC2_ADC_CREST_FACTOR_PROP
  Si2183_L1_SetProperty2(api, Si2183_DVBC2_ADC_CREST_FACTOR_PROP_CODE);
#endif /* Si2183_DVBC2_ADC_CREST_FACTOR_PROP */
#ifdef    Si2183_DVBC2_AFC_RANGE_PROP
  Si2183_L1_SetProperty2(api, Si2183_DVBC2_AFC_RANGE_PROP_CODE);
#endif /* Si2183_DVBC2_AFC_RANGE_PROP */
return NO_Si2183_ERROR;
}
#endif /* DEMOD_DVB_C2 */

#ifdef    DEMOD_DVB_S_S2_DSS
/*****************************************************************************************
 NAME: Si2183_downloadDVBSProperties
  DESCRIPTION: Setup Si2183 DVBS properties configuration
  This function will download all the DVBS configuration properties.
  The function Si2183_storeUserProperties should be called before the first call to this function.
  Parameter:  Pointer to Si2183 Context
  Returns:    I2C transaction error code, NO_Si2183_ERROR if successful
  Programming Guide Reference:    DVBS setup flowchart
******************************************************************************************/
int  Si2183_downloadDVBSProperties        (L1_Si2183_Context *api) {
  SiTRACE("Si2183_downloadDVBSProperties\n");
#ifdef    Si2183_DVBS_ADC_CREST_FACTOR_PROP
  Si2183_L1_SetProperty2(api, Si2183_DVBS_ADC_CREST_FACTOR_PROP_CODE);
#endif /* Si2183_DVBS_ADC_CREST_FACTOR_PROP */
#ifdef    Si2183_DVBS_AFC_RANGE_PROP
  Si2183_L1_SetProperty2(api, Si2183_DVBS_AFC_RANGE_PROP_CODE);
#endif /* Si2183_DVBS_AFC_RANGE_PROP */
#ifdef    Si2183_DVBS_SYMBOL_RATE_PROP
  Si2183_L1_SetProperty2(api, Si2183_DVBS_SYMBOL_RATE_PROP_CODE);
#endif /* Si2183_DVBS_SYMBOL_RATE_PROP */
return NO_Si2183_ERROR;
}
/*****************************************************************************************
 NAME: Si2183_downloadDVBS2Properties
  DESCRIPTION: Setup Si2183 DVBS2 properties configuration
  This function will download all the DVBS2 configuration properties.
  The function Si2183_storeUserProperties should be called before the first call to this function.
  Parameter:  Pointer to Si2183 Context
  Returns:    I2C transaction error code, NO_Si2183_ERROR if successful
  Programming Guide Reference:    DVBS2 setup flowchart
******************************************************************************************/
int  Si2183_downloadDVBS2Properties       (L1_Si2183_Context *api) {
  SiTRACE("Si2183_downloadDVBS2Properties\n");
#ifdef    Si2183_DVBS2_ADC_CREST_FACTOR_PROP
  Si2183_L1_SetProperty2(api, Si2183_DVBS2_ADC_CREST_FACTOR_PROP_CODE);
#endif /* Si2183_DVBS2_ADC_CREST_FACTOR_PROP */
#ifdef    Si2183_DVBS2_AFC_RANGE_PROP
  Si2183_L1_SetProperty2(api, Si2183_DVBS2_AFC_RANGE_PROP_CODE);
#endif /* Si2183_DVBS2_AFC_RANGE_PROP */
#ifdef    Si2183_DVBS2_SYMBOL_RATE_PROP
  Si2183_L1_SetProperty2(api, Si2183_DVBS2_SYMBOL_RATE_PROP_CODE);
#endif /* Si2183_DVBS2_SYMBOL_RATE_PROP */
return NO_Si2183_ERROR;
}
#endif /* DEMOD_DVB_S_S2_DSS */

#ifdef    DEMOD_DVB_T
/*****************************************************************************************
 NAME: Si2183_downloadDVBTProperties
  DESCRIPTION: Setup Si2183 DVBT properties configuration
  This function will download all the DVBT configuration properties.
  The function Si2183_storeUserProperties should be called before the first call to this function.
  Parameter:  Pointer to Si2183 Context
  Returns:    I2C transaction error code, NO_Si2183_ERROR if successful
  Programming Guide Reference:    DVBT setup flowchart
******************************************************************************************/
int  Si2183_downloadDVBTProperties        (L1_Si2183_Context *api) {
  SiTRACE("Si2183_downloadDVBTProperties\n");
#ifdef    Si2183_DVBT_ADC_CREST_FACTOR_PROP
  Si2183_L1_SetProperty2(api, Si2183_DVBT_ADC_CREST_FACTOR_PROP_CODE);
#endif /* Si2183_DVBT_ADC_CREST_FACTOR_PROP */
#ifdef    Si2183_DVBT_AFC_RANGE_PROP
  Si2183_L1_SetProperty2(api, Si2183_DVBT_AFC_RANGE_PROP_CODE);
#endif /* Si2183_DVBT_AFC_RANGE_PROP */
#ifdef    Si2183_DVBT_HIERARCHY_PROP
  Si2183_L1_SetProperty2(api, Si2183_DVBT_HIERARCHY_PROP_CODE);
#endif /* Si2183_DVBT_HIERARCHY_PROP */
return NO_Si2183_ERROR;
}
#endif /* DEMOD_DVB_T */

#ifdef    DEMOD_DVB_T2
/*****************************************************************************************
 NAME: Si2183_downloadDVBT2Properties
  DESCRIPTION: Setup Si2183 DVBT2 properties configuration
  This function will download all the DVBT2 configuration properties.
  The function Si2183_storeUserProperties should be called before the first call to this function.
  Parameter:  Pointer to Si2183 Context
  Returns:    I2C transaction error code, NO_Si2183_ERROR if successful
  Programming Guide Reference:    DVBT2 setup flowchart
******************************************************************************************/
int  Si2183_downloadDVBT2Properties       (L1_Si2183_Context *api) {
  SiTRACE("Si2183_downloadDVBT2Properties\n");
#ifdef    Si2183_DVBT2_ADC_CREST_FACTOR_PROP
  Si2183_L1_SetProperty2(api, Si2183_DVBT2_ADC_CREST_FACTOR_PROP_CODE);
#endif /* Si2183_DVBT2_ADC_CREST_FACTOR_PROP */
#ifdef    Si2183_DVBT2_AFC_RANGE_PROP
  Si2183_L1_SetProperty2(api, Si2183_DVBT2_AFC_RANGE_PROP_CODE);
#endif /* Si2183_DVBT2_AFC_RANGE_PROP */
#ifdef    Si2183_DVBT2_FEF_TUNER_PROP
  Si2183_L1_SetProperty2(api, Si2183_DVBT2_FEF_TUNER_PROP_CODE);
#endif /* Si2183_DVBT2_FEF_TUNER_PROP */
#ifdef    Si2183_DVBT2_MODE_PROP
  Si2183_L1_SetProperty2(api, Si2183_DVBT2_MODE_PROP_CODE);
#endif /* Si2183_DVBT2_MODE_PROP */
return NO_Si2183_ERROR;
}
#endif /* DEMOD_DVB_T2 */

#ifdef    DEMOD_ISDB_T
/*****************************************************************************************
 NAME: Si2183_downloadISDBTProperties
  DESCRIPTION: Setup Si2183 ISDBT properties configuration
  This function will download all the ISDBT configuration properties.
  The function Si2183_storeUserProperties should be called before the first call to this function.
  Parameter:  Pointer to Si2183 Context
  Returns:    I2C transaction error code, NO_Si2183_ERROR if successful
  Programming Guide Reference:    ISDBT setup flowchart
******************************************************************************************/
int  Si2183_downloadISDBTProperties       (L1_Si2183_Context *api) {
  SiTRACE("Si2183_downloadISDBTProperties\n");
#ifdef    Si2183_ISDBT_AC_SELECT_PROP
  Si2183_L1_SetProperty2(api, Si2183_ISDBT_AC_SELECT_PROP_CODE);
#endif /* Si2183_ISDBT_AC_SELECT_PROP */
#ifdef    Si2183_ISDBT_ADC_CREST_FACTOR_PROP
  Si2183_L1_SetProperty2(api, Si2183_ISDBT_ADC_CREST_FACTOR_PROP_CODE);
#endif /* Si2183_ISDBT_ADC_CREST_FACTOR_PROP */
#ifdef    Si2183_ISDBT_AFC_RANGE_PROP
  Si2183_L1_SetProperty2(api, Si2183_ISDBT_AFC_RANGE_PROP_CODE);
#endif /* Si2183_ISDBT_AFC_RANGE_PROP */
#ifdef    Si2183_ISDBT_MODE_PROP
  Si2183_L1_SetProperty2(api, Si2183_ISDBT_MODE_PROP_CODE);
#endif /* Si2183_ISDBT_MODE_PROP */
return NO_Si2183_ERROR;
}
#endif /* DEMOD_ISDB_T */

#ifdef    DEMOD_MCNS
/*****************************************************************************************
 NAME: Si2183_downloadMCNSProperties
  DESCRIPTION: Setup Si2183 MCNS properties configuration
  This function will download all the MCNS configuration properties.
  The function Si2183_storeUserProperties should be called before the first call to this function.
  Parameter:  Pointer to Si2183 Context
  Returns:    I2C transaction error code, NO_Si2183_ERROR if successful
  Programming Guide Reference:    MCNS setup flowchart
******************************************************************************************/
int  Si2183_downloadMCNSProperties        (L1_Si2183_Context *api) {
  SiTRACE("Si2183_downloadMCNSProperties\n");
#ifdef    Si2183_MCNS_ADC_CREST_FACTOR_PROP
  Si2183_L1_SetProperty2(api, Si2183_MCNS_ADC_CREST_FACTOR_PROP_CODE);
#endif /* Si2183_MCNS_ADC_CREST_FACTOR_PROP */
#ifdef    Si2183_MCNS_AFC_RANGE_PROP
  Si2183_L1_SetProperty2(api, Si2183_MCNS_AFC_RANGE_PROP_CODE);
#endif /* Si2183_MCNS_AFC_RANGE_PROP */
#ifdef    Si2183_MCNS_CONSTELLATION_PROP
  Si2183_L1_SetProperty2(api, Si2183_MCNS_CONSTELLATION_PROP_CODE);
#endif /* Si2183_MCNS_CONSTELLATION_PROP */
#ifdef    Si2183_MCNS_SYMBOL_RATE_PROP
  Si2183_L1_SetProperty2(api, Si2183_MCNS_SYMBOL_RATE_PROP_CODE);
#endif /* Si2183_MCNS_SYMBOL_RATE_PROP */
return NO_Si2183_ERROR;
}
#endif /* DEMOD_MCNS */

/*****************************************************************************************
 NAME: Si2183_downloadSCANProperties
  DESCRIPTION: Setup Si2183 SCAN properties configuration
  This function will download all the SCAN configuration properties.
  The function Si2183_storeUserProperties should be called before the first call to this function.
  Parameter:  Pointer to Si2183 Context
  Returns:    I2C transaction error code, NO_Si2183_ERROR if successful
  Programming Guide Reference:    SCAN setup flowchart
******************************************************************************************/
int  Si2183_downloadSCANProperties        (L1_Si2183_Context *api) {
  SiTRACE("Si2183_downloadSCANProperties\n");
#ifdef    Si2183_SCAN_FMAX_PROP
  Si2183_L1_SetProperty2(api, Si2183_SCAN_FMAX_PROP_CODE);
#endif /* Si2183_SCAN_FMAX_PROP */
#ifdef    Si2183_SCAN_FMIN_PROP
  Si2183_L1_SetProperty2(api, Si2183_SCAN_FMIN_PROP_CODE);
#endif /* Si2183_SCAN_FMIN_PROP */
#ifdef    Si2183_SCAN_IEN_PROP
  Si2183_L1_SetProperty2(api, Si2183_SCAN_IEN_PROP_CODE);
#endif /* Si2183_SCAN_IEN_PROP */
#ifdef    Si2183_SCAN_INT_SENSE_PROP
  Si2183_L1_SetProperty2(api, Si2183_SCAN_INT_SENSE_PROP_CODE);
#endif /* Si2183_SCAN_INT_SENSE_PROP */
#ifdef    SATELLITE_FRONT_END
#ifdef    Si2183_SCAN_SAT_CONFIG_PROP
  Si2183_L1_SetProperty2(api, Si2183_SCAN_SAT_CONFIG_PROP_CODE);
#endif /* Si2183_SCAN_SAT_CONFIG_PROP */
#ifdef    Si2183_SCAN_SAT_UNICABLE_BW_PROP
  Si2183_L1_SetProperty2(api, Si2183_SCAN_SAT_UNICABLE_BW_PROP_CODE);
#endif /* Si2183_SCAN_SAT_UNICABLE_BW_PROP */
#ifdef    Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP
  Si2183_L1_SetProperty2(api, Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP_CODE);
#endif /* Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP */
#endif /* SATELLITE_FRONT_END */

#ifdef    Si2183_SCAN_SYMB_RATE_MAX_PROP
  Si2183_L1_SetProperty2(api, Si2183_SCAN_SYMB_RATE_MAX_PROP_CODE);
#endif /* Si2183_SCAN_SYMB_RATE_MAX_PROP */
#ifdef    Si2183_SCAN_SYMB_RATE_MIN_PROP
  Si2183_L1_SetProperty2(api, Si2183_SCAN_SYMB_RATE_MIN_PROP_CODE);
#endif /* Si2183_SCAN_SYMB_RATE_MIN_PROP */
#ifdef    TERRESTRIAL_FRONT_END
#ifdef    Si2183_SCAN_TER_CONFIG_PROP
  Si2183_L1_SetProperty2(api, Si2183_SCAN_TER_CONFIG_PROP_CODE);
#endif /* Si2183_SCAN_TER_CONFIG_PROP */
#endif /* TERRESTRIAL_FRONT_END */

return NO_Si2183_ERROR;
}

int  Si2183_downloadAllProperties         (L1_Si2183_Context *api) {
  Si2183_downloadCOMMONProperties      (api);
  Si2183_downloadDDProperties          (api);
#ifdef    DEMOD_DVB_C
  Si2183_downloadDVBCProperties        (api);
#endif /* DEMOD_DVB_C */

#ifdef    DEMOD_DVB_C2
  Si2183_downloadDVBC2Properties       (api);
#endif /* DEMOD_DVB_C2 */

#ifdef    DEMOD_DVB_S_S2_DSS
  Si2183_downloadDVBSProperties        (api);
  Si2183_downloadDVBS2Properties       (api);
#endif /* DEMOD_DVB_S_S2_DSS */

#ifdef    DEMOD_DVB_T
  Si2183_downloadDVBTProperties        (api);
#endif /* DEMOD_DVB_T */

#ifdef    DEMOD_DVB_T2
  Si2183_downloadDVBT2Properties       (api);
#endif /* DEMOD_DVB_T2 */

#ifdef    DEMOD_ISDB_T
  Si2183_downloadISDBTProperties       (api);
#endif /* DEMOD_ISDB_T */

#ifdef    DEMOD_MCNS
  Si2183_downloadMCNSProperties        (api);
#endif /* DEMOD_MCNS */

  Si2183_downloadSCANProperties        (api);
  return 0;
}

/* Re-definition of SiTRACE for Si2183_PropObj */
#ifdef    SiTRACES
  #undef  SiTRACE
  #define SiTRACE(...)        SiTraceFunction(SiLEVEL, "", __FILE__, __LINE__, __func__     ,__VA_ARGS__)
#endif /* SiTRACES */

/***********************************************************************************************************************
  Si2183_PackProperty function
  Use:        This function will pack all the members of a property into an integer for the SetProperty function.

  Parameter: *prop          the Si2183 property context
  Parameter:  prop_code     the property Id
  Parameter:  *data         an int to store the property data

  Returns:    NO_Si2183_ERROR if the property exists.
 ***********************************************************************************************************************/
unsigned char Si2183_PackProperty            (Si2183_PropObj   *prop, unsigned int prop_code, signed   int *data) {
    switch (prop_code) {
    #ifdef        Si2183_DD_BER_RESOL_PROP
     case         Si2183_DD_BER_RESOL_PROP_CODE:
      *data = (prop->dd_ber_resol.exp  & Si2183_DD_BER_RESOL_PROP_EXP_MASK ) << Si2183_DD_BER_RESOL_PROP_EXP_LSB  |
              (prop->dd_ber_resol.mant & Si2183_DD_BER_RESOL_PROP_MANT_MASK) << Si2183_DD_BER_RESOL_PROP_MANT_LSB ;
     break;
    #endif /*     Si2183_DD_BER_RESOL_PROP */
    #ifdef        Si2183_DD_CBER_RESOL_PROP
     case         Si2183_DD_CBER_RESOL_PROP_CODE:
      *data = (prop->dd_cber_resol.exp  & Si2183_DD_CBER_RESOL_PROP_EXP_MASK ) << Si2183_DD_CBER_RESOL_PROP_EXP_LSB  |
              (prop->dd_cber_resol.mant & Si2183_DD_CBER_RESOL_PROP_MANT_MASK) << Si2183_DD_CBER_RESOL_PROP_MANT_LSB ;
     break;
    #endif /*     Si2183_DD_CBER_RESOL_PROP */
#ifdef    DEMOD_DVB_S_S2_DSS
    #ifdef        Si2183_DD_DISEQC_FREQ_PROP
     case         Si2183_DD_DISEQC_FREQ_PROP_CODE:
      *data = (prop->dd_diseqc_freq.freq_hz & Si2183_DD_DISEQC_FREQ_PROP_FREQ_HZ_MASK) << Si2183_DD_DISEQC_FREQ_PROP_FREQ_HZ_LSB ;
     break;
    #endif /*     Si2183_DD_DISEQC_FREQ_PROP */
    #ifdef        Si2183_DD_DISEQC_PARAM_PROP
     case         Si2183_DD_DISEQC_PARAM_PROP_CODE:
      *data = (prop->dd_diseqc_param.sequence_mode & Si2183_DD_DISEQC_PARAM_PROP_SEQUENCE_MODE_MASK) << Si2183_DD_DISEQC_PARAM_PROP_SEQUENCE_MODE_LSB  |
              (prop->dd_diseqc_param.input_pin     & Si2183_DD_DISEQC_PARAM_PROP_INPUT_PIN_MASK    ) << Si2183_DD_DISEQC_PARAM_PROP_INPUT_PIN_LSB ;
     break;
    #endif /*     Si2183_DD_DISEQC_PARAM_PROP */
#endif /* DEMOD_DVB_S_S2_DSS */

    #ifdef        Si2183_DD_FER_RESOL_PROP
     case         Si2183_DD_FER_RESOL_PROP_CODE:
      *data = (prop->dd_fer_resol.exp  & Si2183_DD_FER_RESOL_PROP_EXP_MASK ) << Si2183_DD_FER_RESOL_PROP_EXP_LSB  |
              (prop->dd_fer_resol.mant & Si2183_DD_FER_RESOL_PROP_MANT_MASK) << Si2183_DD_FER_RESOL_PROP_MANT_LSB ;
     break;
    #endif /*     Si2183_DD_FER_RESOL_PROP */
    #ifdef        Si2183_DD_IEN_PROP
     case         Si2183_DD_IEN_PROP_CODE:
      *data = (prop->dd_ien.ien_bit0 & Si2183_DD_IEN_PROP_IEN_BIT0_MASK) << Si2183_DD_IEN_PROP_IEN_BIT0_LSB  |
              (prop->dd_ien.ien_bit1 & Si2183_DD_IEN_PROP_IEN_BIT1_MASK) << Si2183_DD_IEN_PROP_IEN_BIT1_LSB  |
              (prop->dd_ien.ien_bit2 & Si2183_DD_IEN_PROP_IEN_BIT2_MASK) << Si2183_DD_IEN_PROP_IEN_BIT2_LSB  |
              (prop->dd_ien.ien_bit3 & Si2183_DD_IEN_PROP_IEN_BIT3_MASK) << Si2183_DD_IEN_PROP_IEN_BIT3_LSB  |
              (prop->dd_ien.ien_bit4 & Si2183_DD_IEN_PROP_IEN_BIT4_MASK) << Si2183_DD_IEN_PROP_IEN_BIT4_LSB  |
              (prop->dd_ien.ien_bit5 & Si2183_DD_IEN_PROP_IEN_BIT5_MASK) << Si2183_DD_IEN_PROP_IEN_BIT5_LSB  |
              (prop->dd_ien.ien_bit6 & Si2183_DD_IEN_PROP_IEN_BIT6_MASK) << Si2183_DD_IEN_PROP_IEN_BIT6_LSB  |
              (prop->dd_ien.ien_bit7 & Si2183_DD_IEN_PROP_IEN_BIT7_MASK) << Si2183_DD_IEN_PROP_IEN_BIT7_LSB ;
     break;
    #endif /*     Si2183_DD_IEN_PROP */
    #ifdef        Si2183_DD_IF_INPUT_FREQ_PROP
     case         Si2183_DD_IF_INPUT_FREQ_PROP_CODE:
      *data = (prop->dd_if_input_freq.offset & Si2183_DD_IF_INPUT_FREQ_PROP_OFFSET_MASK) << Si2183_DD_IF_INPUT_FREQ_PROP_OFFSET_LSB ;
     break;
    #endif /*     Si2183_DD_IF_INPUT_FREQ_PROP */
    #ifdef        Si2183_DD_INT_SENSE_PROP
     case         Si2183_DD_INT_SENSE_PROP_CODE:
      *data = (prop->dd_int_sense.neg_bit0 & Si2183_DD_INT_SENSE_PROP_NEG_BIT0_MASK) << Si2183_DD_INT_SENSE_PROP_NEG_BIT0_LSB  |
              (prop->dd_int_sense.neg_bit1 & Si2183_DD_INT_SENSE_PROP_NEG_BIT1_MASK) << Si2183_DD_INT_SENSE_PROP_NEG_BIT1_LSB  |
              (prop->dd_int_sense.neg_bit2 & Si2183_DD_INT_SENSE_PROP_NEG_BIT2_MASK) << Si2183_DD_INT_SENSE_PROP_NEG_BIT2_LSB  |
              (prop->dd_int_sense.neg_bit3 & Si2183_DD_INT_SENSE_PROP_NEG_BIT3_MASK) << Si2183_DD_INT_SENSE_PROP_NEG_BIT3_LSB  |
              (prop->dd_int_sense.neg_bit4 & Si2183_DD_INT_SENSE_PROP_NEG_BIT4_MASK) << Si2183_DD_INT_SENSE_PROP_NEG_BIT4_LSB  |
              (prop->dd_int_sense.neg_bit5 & Si2183_DD_INT_SENSE_PROP_NEG_BIT5_MASK) << Si2183_DD_INT_SENSE_PROP_NEG_BIT5_LSB  |
              (prop->dd_int_sense.neg_bit6 & Si2183_DD_INT_SENSE_PROP_NEG_BIT6_MASK) << Si2183_DD_INT_SENSE_PROP_NEG_BIT6_LSB  |
              (prop->dd_int_sense.neg_bit7 & Si2183_DD_INT_SENSE_PROP_NEG_BIT7_MASK) << Si2183_DD_INT_SENSE_PROP_NEG_BIT7_LSB  |
              (prop->dd_int_sense.pos_bit0 & Si2183_DD_INT_SENSE_PROP_POS_BIT0_MASK) << Si2183_DD_INT_SENSE_PROP_POS_BIT0_LSB  |
              (prop->dd_int_sense.pos_bit1 & Si2183_DD_INT_SENSE_PROP_POS_BIT1_MASK) << Si2183_DD_INT_SENSE_PROP_POS_BIT1_LSB  |
              (prop->dd_int_sense.pos_bit2 & Si2183_DD_INT_SENSE_PROP_POS_BIT2_MASK) << Si2183_DD_INT_SENSE_PROP_POS_BIT2_LSB  |
              (prop->dd_int_sense.pos_bit3 & Si2183_DD_INT_SENSE_PROP_POS_BIT3_MASK) << Si2183_DD_INT_SENSE_PROP_POS_BIT3_LSB  |
              (prop->dd_int_sense.pos_bit4 & Si2183_DD_INT_SENSE_PROP_POS_BIT4_MASK) << Si2183_DD_INT_SENSE_PROP_POS_BIT4_LSB  |
              (prop->dd_int_sense.pos_bit5 & Si2183_DD_INT_SENSE_PROP_POS_BIT5_MASK) << Si2183_DD_INT_SENSE_PROP_POS_BIT5_LSB  |
              (prop->dd_int_sense.pos_bit6 & Si2183_DD_INT_SENSE_PROP_POS_BIT6_MASK) << Si2183_DD_INT_SENSE_PROP_POS_BIT6_LSB  |
              (prop->dd_int_sense.pos_bit7 & Si2183_DD_INT_SENSE_PROP_POS_BIT7_MASK) << Si2183_DD_INT_SENSE_PROP_POS_BIT7_LSB ;
     break;
    #endif /*     Si2183_DD_INT_SENSE_PROP */
    #ifdef        Si2183_DD_MODE_PROP
     case         Si2183_DD_MODE_PROP_CODE:
      *data = (prop->dd_mode.bw              & Si2183_DD_MODE_PROP_BW_MASK             ) << Si2183_DD_MODE_PROP_BW_LSB  |
              (prop->dd_mode.modulation      & Si2183_DD_MODE_PROP_MODULATION_MASK     ) << Si2183_DD_MODE_PROP_MODULATION_LSB  |
              (prop->dd_mode.invert_spectrum & Si2183_DD_MODE_PROP_INVERT_SPECTRUM_MASK) << Si2183_DD_MODE_PROP_INVERT_SPECTRUM_LSB  |
              (prop->dd_mode.auto_detect     & Si2183_DD_MODE_PROP_AUTO_DETECT_MASK    ) << Si2183_DD_MODE_PROP_AUTO_DETECT_LSB ;
     break;
    #endif /*     Si2183_DD_MODE_PROP */
    #ifdef        Si2183_DD_PER_RESOL_PROP
     case         Si2183_DD_PER_RESOL_PROP_CODE:
      *data = (prop->dd_per_resol.exp  & Si2183_DD_PER_RESOL_PROP_EXP_MASK ) << Si2183_DD_PER_RESOL_PROP_EXP_LSB  |
              (prop->dd_per_resol.mant & Si2183_DD_PER_RESOL_PROP_MANT_MASK) << Si2183_DD_PER_RESOL_PROP_MANT_LSB ;
     break;
    #endif /*     Si2183_DD_PER_RESOL_PROP */
    #ifdef        Si2183_DD_RSQ_BER_THRESHOLD_PROP
     case         Si2183_DD_RSQ_BER_THRESHOLD_PROP_CODE:
      *data = (prop->dd_rsq_ber_threshold.exp  & Si2183_DD_RSQ_BER_THRESHOLD_PROP_EXP_MASK ) << Si2183_DD_RSQ_BER_THRESHOLD_PROP_EXP_LSB  |
              (prop->dd_rsq_ber_threshold.mant & Si2183_DD_RSQ_BER_THRESHOLD_PROP_MANT_MASK) << Si2183_DD_RSQ_BER_THRESHOLD_PROP_MANT_LSB ;
     break;
    #endif /*     Si2183_DD_RSQ_BER_THRESHOLD_PROP */
    #ifdef        Si2183_DD_SEC_TS_SERIAL_DIFF_PROP
     case         Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_CODE:
      *data = (prop->dd_sec_ts_serial_diff.ts_data1_strength  & Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA1_STRENGTH_MASK ) << Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA1_STRENGTH_LSB  |
              (prop->dd_sec_ts_serial_diff.ts_data1_shape     & Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA1_SHAPE_MASK    ) << Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA1_SHAPE_LSB  |
              (prop->dd_sec_ts_serial_diff.ts_data2_strength  & Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA2_STRENGTH_MASK ) << Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA2_STRENGTH_LSB  |
              (prop->dd_sec_ts_serial_diff.ts_data2_shape     & Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA2_SHAPE_MASK    ) << Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA2_SHAPE_LSB  |
              (prop->dd_sec_ts_serial_diff.ts_clkb_on_data1   & Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_CLKB_ON_DATA1_MASK  ) << Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_CLKB_ON_DATA1_LSB  |
              (prop->dd_sec_ts_serial_diff.ts_data0b_on_data2 & Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA0B_ON_DATA2_MASK) << Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA0B_ON_DATA2_LSB ;
     break;
    #endif /*     Si2183_DD_SEC_TS_SERIAL_DIFF_PROP */
    #ifdef        Si2183_DD_SEC_TS_SETUP_PAR_PROP
     case         Si2183_DD_SEC_TS_SETUP_PAR_PROP_CODE:
      *data = (prop->dd_sec_ts_setup_par.ts_data_strength & Si2183_DD_SEC_TS_SETUP_PAR_PROP_TS_DATA_STRENGTH_MASK) << Si2183_DD_SEC_TS_SETUP_PAR_PROP_TS_DATA_STRENGTH_LSB  |
              (prop->dd_sec_ts_setup_par.ts_data_shape    & Si2183_DD_SEC_TS_SETUP_PAR_PROP_TS_DATA_SHAPE_MASK   ) << Si2183_DD_SEC_TS_SETUP_PAR_PROP_TS_DATA_SHAPE_LSB  |
              (prop->dd_sec_ts_setup_par.ts_clk_strength  & Si2183_DD_SEC_TS_SETUP_PAR_PROP_TS_CLK_STRENGTH_MASK ) << Si2183_DD_SEC_TS_SETUP_PAR_PROP_TS_CLK_STRENGTH_LSB  |
              (prop->dd_sec_ts_setup_par.ts_clk_shape     & Si2183_DD_SEC_TS_SETUP_PAR_PROP_TS_CLK_SHAPE_MASK    ) << Si2183_DD_SEC_TS_SETUP_PAR_PROP_TS_CLK_SHAPE_LSB ;
     break;
    #endif /*     Si2183_DD_SEC_TS_SETUP_PAR_PROP */
    #ifdef        Si2183_DD_SEC_TS_SETUP_SER_PROP
     case         Si2183_DD_SEC_TS_SETUP_SER_PROP_CODE:
      *data = (prop->dd_sec_ts_setup_ser.ts_data_strength & Si2183_DD_SEC_TS_SETUP_SER_PROP_TS_DATA_STRENGTH_MASK) << Si2183_DD_SEC_TS_SETUP_SER_PROP_TS_DATA_STRENGTH_LSB  |
              (prop->dd_sec_ts_setup_ser.ts_data_shape    & Si2183_DD_SEC_TS_SETUP_SER_PROP_TS_DATA_SHAPE_MASK   ) << Si2183_DD_SEC_TS_SETUP_SER_PROP_TS_DATA_SHAPE_LSB  |
              (prop->dd_sec_ts_setup_ser.ts_clk_strength  & Si2183_DD_SEC_TS_SETUP_SER_PROP_TS_CLK_STRENGTH_MASK ) << Si2183_DD_SEC_TS_SETUP_SER_PROP_TS_CLK_STRENGTH_LSB  |
              (prop->dd_sec_ts_setup_ser.ts_clk_shape     & Si2183_DD_SEC_TS_SETUP_SER_PROP_TS_CLK_SHAPE_MASK    ) << Si2183_DD_SEC_TS_SETUP_SER_PROP_TS_CLK_SHAPE_LSB ;
     break;
    #endif /*     Si2183_DD_SEC_TS_SETUP_SER_PROP */
    #ifdef        Si2183_DD_SEC_TS_SLR_SERIAL_PROP
     case         Si2183_DD_SEC_TS_SLR_SERIAL_PROP_CODE:
      *data = (prop->dd_sec_ts_slr_serial.ts_data_slr     & Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA_SLR_MASK    ) << Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA_SLR_LSB  |
              (prop->dd_sec_ts_slr_serial.ts_data_slr_on  & Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA_SLR_ON_MASK ) << Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA_SLR_ON_LSB  |
              (prop->dd_sec_ts_slr_serial.ts_data1_slr    & Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA1_SLR_MASK   ) << Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA1_SLR_LSB  |
              (prop->dd_sec_ts_slr_serial.ts_data1_slr_on & Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA1_SLR_ON_MASK) << Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA1_SLR_ON_LSB  |
              (prop->dd_sec_ts_slr_serial.ts_data2_slr    & Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA2_SLR_MASK   ) << Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA2_SLR_LSB  |
              (prop->dd_sec_ts_slr_serial.ts_data2_slr_on & Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA2_SLR_ON_MASK) << Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA2_SLR_ON_LSB  |
              (prop->dd_sec_ts_slr_serial.ts_clk_slr      & Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_CLK_SLR_MASK     ) << Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_CLK_SLR_LSB  |
              (prop->dd_sec_ts_slr_serial.ts_clk_slr_on   & Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_CLK_SLR_ON_MASK  ) << Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_CLK_SLR_ON_LSB ;
     break;
    #endif /*     Si2183_DD_SEC_TS_SLR_SERIAL_PROP */
    #ifdef        Si2183_DD_SSI_SQI_PARAM_PROP
     case         Si2183_DD_SSI_SQI_PARAM_PROP_CODE:
      *data = (prop->dd_ssi_sqi_param.sqi_average & Si2183_DD_SSI_SQI_PARAM_PROP_SQI_AVERAGE_MASK) << Si2183_DD_SSI_SQI_PARAM_PROP_SQI_AVERAGE_LSB ;
     break;
    #endif /*     Si2183_DD_SSI_SQI_PARAM_PROP */
    #ifdef        Si2183_DD_TS_FREQ_PROP
     case         Si2183_DD_TS_FREQ_PROP_CODE:
      *data = (prop->dd_ts_freq.req_freq_10khz & Si2183_DD_TS_FREQ_PROP_REQ_FREQ_10KHZ_MASK) << Si2183_DD_TS_FREQ_PROP_REQ_FREQ_10KHZ_LSB ;
     break;
    #endif /*     Si2183_DD_TS_FREQ_PROP */
    #ifdef        Si2183_DD_TS_FREQ_MAX_PROP
     case         Si2183_DD_TS_FREQ_MAX_PROP_CODE:
      *data = (prop->dd_ts_freq_max.req_freq_max_10khz & Si2183_DD_TS_FREQ_MAX_PROP_REQ_FREQ_MAX_10KHZ_MASK) << Si2183_DD_TS_FREQ_MAX_PROP_REQ_FREQ_MAX_10KHZ_LSB ;
     break;
    #endif /*     Si2183_DD_TS_FREQ_MAX_PROP */
    #ifdef        Si2183_DD_TS_MODE_PROP
     case         Si2183_DD_TS_MODE_PROP_CODE:
      *data = (prop->dd_ts_mode.mode               & Si2183_DD_TS_MODE_PROP_MODE_MASK              ) << Si2183_DD_TS_MODE_PROP_MODE_LSB  |
              (prop->dd_ts_mode.clock              & Si2183_DD_TS_MODE_PROP_CLOCK_MASK             ) << Si2183_DD_TS_MODE_PROP_CLOCK_LSB  |
              (prop->dd_ts_mode.clk_gapped_en      & Si2183_DD_TS_MODE_PROP_CLK_GAPPED_EN_MASK     ) << Si2183_DD_TS_MODE_PROP_CLK_GAPPED_EN_LSB  |
              (prop->dd_ts_mode.ts_err_polarity    & Si2183_DD_TS_MODE_PROP_TS_ERR_POLARITY_MASK   ) << Si2183_DD_TS_MODE_PROP_TS_ERR_POLARITY_LSB  |
              (prop->dd_ts_mode.special            & Si2183_DD_TS_MODE_PROP_SPECIAL_MASK           ) << Si2183_DD_TS_MODE_PROP_SPECIAL_LSB  |
              (prop->dd_ts_mode.ts_freq_resolution   & Si2183_DD_TS_MODE_PROP_TS_FREQ_RESOLUTION_MASK  ) << Si2183_DD_TS_MODE_PROP_TS_FREQ_RESOLUTION_LSB  |
              (prop->dd_ts_mode.serial_pin_selection & Si2183_DD_TS_MODE_PROP_SERIAL_PIN_SELECTION_MASK) << Si2183_DD_TS_MODE_PROP_SERIAL_PIN_SELECTION_LSB ;
     break;
    #endif /*     Si2183_DD_TS_MODE_PROP */
    #ifdef        Si2183_DD_TS_SERIAL_DIFF_PROP
     case         Si2183_DD_TS_SERIAL_DIFF_PROP_CODE:
      *data = (prop->dd_ts_serial_diff.ts_data1_strength  & Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA1_STRENGTH_MASK ) << Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA1_STRENGTH_LSB  |
              (prop->dd_ts_serial_diff.ts_data1_shape     & Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA1_SHAPE_MASK    ) << Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA1_SHAPE_LSB  |
              (prop->dd_ts_serial_diff.ts_data2_strength  & Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA2_STRENGTH_MASK ) << Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA2_STRENGTH_LSB  |
              (prop->dd_ts_serial_diff.ts_data2_shape     & Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA2_SHAPE_MASK    ) << Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA2_SHAPE_LSB  |
              (prop->dd_ts_serial_diff.ts_clkb_on_data1   & Si2183_DD_TS_SERIAL_DIFF_PROP_TS_CLKB_ON_DATA1_MASK  ) << Si2183_DD_TS_SERIAL_DIFF_PROP_TS_CLKB_ON_DATA1_LSB  |
              (prop->dd_ts_serial_diff.ts_data0b_on_data2 & Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA0B_ON_DATA2_MASK) << Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA0B_ON_DATA2_LSB ;
     break;
    #endif /*     Si2183_DD_TS_SERIAL_DIFF_PROP */
    #ifdef        Si2183_DD_TS_SETUP_PAR_PROP
     case         Si2183_DD_TS_SETUP_PAR_PROP_CODE:
      *data = (prop->dd_ts_setup_par.ts_data_strength & Si2183_DD_TS_SETUP_PAR_PROP_TS_DATA_STRENGTH_MASK) << Si2183_DD_TS_SETUP_PAR_PROP_TS_DATA_STRENGTH_LSB  |
              (prop->dd_ts_setup_par.ts_data_shape    & Si2183_DD_TS_SETUP_PAR_PROP_TS_DATA_SHAPE_MASK   ) << Si2183_DD_TS_SETUP_PAR_PROP_TS_DATA_SHAPE_LSB  |
              (prop->dd_ts_setup_par.ts_clk_strength  & Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_STRENGTH_MASK ) << Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_STRENGTH_LSB  |
              (prop->dd_ts_setup_par.ts_clk_shape     & Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_SHAPE_MASK    ) << Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_SHAPE_LSB  |
              (prop->dd_ts_setup_par.ts_clk_invert    & Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_INVERT_MASK   ) << Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_INVERT_LSB  |
              (prop->dd_ts_setup_par.ts_clk_shift     & Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_SHIFT_MASK    ) << Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_SHIFT_LSB ;
     break;
    #endif /*     Si2183_DD_TS_SETUP_PAR_PROP */
    #ifdef        Si2183_DD_TS_SETUP_SER_PROP
     case         Si2183_DD_TS_SETUP_SER_PROP_CODE:
      *data = (prop->dd_ts_setup_ser.ts_data_strength & Si2183_DD_TS_SETUP_SER_PROP_TS_DATA_STRENGTH_MASK) << Si2183_DD_TS_SETUP_SER_PROP_TS_DATA_STRENGTH_LSB  |
              (prop->dd_ts_setup_ser.ts_data_shape    & Si2183_DD_TS_SETUP_SER_PROP_TS_DATA_SHAPE_MASK   ) << Si2183_DD_TS_SETUP_SER_PROP_TS_DATA_SHAPE_LSB  |
              (prop->dd_ts_setup_ser.ts_clk_strength  & Si2183_DD_TS_SETUP_SER_PROP_TS_CLK_STRENGTH_MASK ) << Si2183_DD_TS_SETUP_SER_PROP_TS_CLK_STRENGTH_LSB  |
              (prop->dd_ts_setup_ser.ts_clk_shape     & Si2183_DD_TS_SETUP_SER_PROP_TS_CLK_SHAPE_MASK    ) << Si2183_DD_TS_SETUP_SER_PROP_TS_CLK_SHAPE_LSB  |
              (prop->dd_ts_setup_ser.ts_clk_invert    & Si2183_DD_TS_SETUP_SER_PROP_TS_CLK_INVERT_MASK   ) << Si2183_DD_TS_SETUP_SER_PROP_TS_CLK_INVERT_LSB  |
              (prop->dd_ts_setup_ser.ts_sync_duration & Si2183_DD_TS_SETUP_SER_PROP_TS_SYNC_DURATION_MASK) << Si2183_DD_TS_SETUP_SER_PROP_TS_SYNC_DURATION_LSB  |
              (prop->dd_ts_setup_ser.ts_byte_order    & Si2183_DD_TS_SETUP_SER_PROP_TS_BYTE_ORDER_MASK   ) << Si2183_DD_TS_SETUP_SER_PROP_TS_BYTE_ORDER_LSB ;
     break;
    #endif /*     Si2183_DD_TS_SETUP_SER_PROP */
    #ifdef        Si2183_DD_TS_SLR_SERIAL_PROP
     case         Si2183_DD_TS_SLR_SERIAL_PROP_CODE:
      *data = (prop->dd_ts_slr_serial.ts_data_slr     & Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA_SLR_MASK    ) << Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA_SLR_LSB  |
              (prop->dd_ts_slr_serial.ts_data_slr_on  & Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA_SLR_ON_MASK ) << Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA_SLR_ON_LSB  |
              (prop->dd_ts_slr_serial.ts_data1_slr    & Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA1_SLR_MASK   ) << Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA1_SLR_LSB  |
              (prop->dd_ts_slr_serial.ts_data1_slr_on & Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA1_SLR_ON_MASK) << Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA1_SLR_ON_LSB  |
              (prop->dd_ts_slr_serial.ts_data2_slr    & Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA2_SLR_MASK   ) << Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA2_SLR_LSB  |
              (prop->dd_ts_slr_serial.ts_data2_slr_on & Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA2_SLR_ON_MASK) << Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA2_SLR_ON_LSB  |
              (prop->dd_ts_slr_serial.ts_clk_slr      & Si2183_DD_TS_SLR_SERIAL_PROP_TS_CLK_SLR_MASK     ) << Si2183_DD_TS_SLR_SERIAL_PROP_TS_CLK_SLR_LSB  |
              (prop->dd_ts_slr_serial.ts_clk_slr_on   & Si2183_DD_TS_SLR_SERIAL_PROP_TS_CLK_SLR_ON_MASK  ) << Si2183_DD_TS_SLR_SERIAL_PROP_TS_CLK_SLR_ON_LSB ;
     break;
    #endif /*     Si2183_DD_TS_SLR_SERIAL_PROP */
#ifdef    DEMOD_DVB_C2
    #ifdef        Si2183_DVBC2_ADC_CREST_FACTOR_PROP
     case         Si2183_DVBC2_ADC_CREST_FACTOR_PROP_CODE:
      *data = (prop->dvbc2_adc_crest_factor.crest_factor & Si2183_DVBC2_ADC_CREST_FACTOR_PROP_CREST_FACTOR_MASK) << Si2183_DVBC2_ADC_CREST_FACTOR_PROP_CREST_FACTOR_LSB ;
     break;
    #endif /*     Si2183_DVBC2_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_DVBC2_AFC_RANGE_PROP
     case         Si2183_DVBC2_AFC_RANGE_PROP_CODE:
      *data = (prop->dvbc2_afc_range.range_khz & Si2183_DVBC2_AFC_RANGE_PROP_RANGE_KHZ_MASK) << Si2183_DVBC2_AFC_RANGE_PROP_RANGE_KHZ_LSB ;
     break;
    #endif /*     Si2183_DVBC2_AFC_RANGE_PROP */
#endif /* DEMOD_DVB_C2 */

#ifdef    DEMOD_DVB_C
    #ifdef        Si2183_DVBC_ADC_CREST_FACTOR_PROP
     case         Si2183_DVBC_ADC_CREST_FACTOR_PROP_CODE:
      *data = (prop->dvbc_adc_crest_factor.crest_factor & Si2183_DVBC_ADC_CREST_FACTOR_PROP_CREST_FACTOR_MASK) << Si2183_DVBC_ADC_CREST_FACTOR_PROP_CREST_FACTOR_LSB ;
     break;
    #endif /*     Si2183_DVBC_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_DVBC_AFC_RANGE_PROP
     case         Si2183_DVBC_AFC_RANGE_PROP_CODE:
      *data = (prop->dvbc_afc_range.range_khz & Si2183_DVBC_AFC_RANGE_PROP_RANGE_KHZ_MASK) << Si2183_DVBC_AFC_RANGE_PROP_RANGE_KHZ_LSB ;
     break;
    #endif /*     Si2183_DVBC_AFC_RANGE_PROP */
    #ifdef        Si2183_DVBC_CONSTELLATION_PROP
     case         Si2183_DVBC_CONSTELLATION_PROP_CODE:
      *data = (prop->dvbc_constellation.constellation & Si2183_DVBC_CONSTELLATION_PROP_CONSTELLATION_MASK) << Si2183_DVBC_CONSTELLATION_PROP_CONSTELLATION_LSB ;
     break;
    #endif /*     Si2183_DVBC_CONSTELLATION_PROP */
    #ifdef        Si2183_DVBC_SYMBOL_RATE_PROP
     case         Si2183_DVBC_SYMBOL_RATE_PROP_CODE:
      *data = (prop->dvbc_symbol_rate.rate & Si2183_DVBC_SYMBOL_RATE_PROP_RATE_MASK) << Si2183_DVBC_SYMBOL_RATE_PROP_RATE_LSB ;
     break;
    #endif /*     Si2183_DVBC_SYMBOL_RATE_PROP */
#endif /* DEMOD_DVB_C */

#ifdef    DEMOD_DVB_S_S2_DSS
    #ifdef        Si2183_DVBS2_ADC_CREST_FACTOR_PROP
     case         Si2183_DVBS2_ADC_CREST_FACTOR_PROP_CODE:
      *data = (prop->dvbs2_adc_crest_factor.crest_factor & Si2183_DVBS2_ADC_CREST_FACTOR_PROP_CREST_FACTOR_MASK) << Si2183_DVBS2_ADC_CREST_FACTOR_PROP_CREST_FACTOR_LSB ;
     break;
    #endif /*     Si2183_DVBS2_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_DVBS2_AFC_RANGE_PROP
     case         Si2183_DVBS2_AFC_RANGE_PROP_CODE:
      *data = (prop->dvbs2_afc_range.range_khz & Si2183_DVBS2_AFC_RANGE_PROP_RANGE_KHZ_MASK) << Si2183_DVBS2_AFC_RANGE_PROP_RANGE_KHZ_LSB ;
     break;
    #endif /*     Si2183_DVBS2_AFC_RANGE_PROP */
    #ifdef        Si2183_DVBS2_SYMBOL_RATE_PROP
     case         Si2183_DVBS2_SYMBOL_RATE_PROP_CODE:
      *data = (prop->dvbs2_symbol_rate.rate & Si2183_DVBS2_SYMBOL_RATE_PROP_RATE_MASK) << Si2183_DVBS2_SYMBOL_RATE_PROP_RATE_LSB ;
     break;
    #endif /*     Si2183_DVBS2_SYMBOL_RATE_PROP */
    #ifdef        Si2183_DVBS_ADC_CREST_FACTOR_PROP
     case         Si2183_DVBS_ADC_CREST_FACTOR_PROP_CODE:
      *data = (prop->dvbs_adc_crest_factor.crest_factor & Si2183_DVBS_ADC_CREST_FACTOR_PROP_CREST_FACTOR_MASK) << Si2183_DVBS_ADC_CREST_FACTOR_PROP_CREST_FACTOR_LSB ;
     break;
    #endif /*     Si2183_DVBS_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_DVBS_AFC_RANGE_PROP
     case         Si2183_DVBS_AFC_RANGE_PROP_CODE:
      *data = (prop->dvbs_afc_range.range_khz & Si2183_DVBS_AFC_RANGE_PROP_RANGE_KHZ_MASK) << Si2183_DVBS_AFC_RANGE_PROP_RANGE_KHZ_LSB ;
     break;
    #endif /*     Si2183_DVBS_AFC_RANGE_PROP */
    #ifdef        Si2183_DVBS_SYMBOL_RATE_PROP
     case         Si2183_DVBS_SYMBOL_RATE_PROP_CODE:
      *data = (prop->dvbs_symbol_rate.rate & Si2183_DVBS_SYMBOL_RATE_PROP_RATE_MASK) << Si2183_DVBS_SYMBOL_RATE_PROP_RATE_LSB ;
     break;
    #endif /*     Si2183_DVBS_SYMBOL_RATE_PROP */
#endif /* DEMOD_DVB_S_S2_DSS */

#ifdef    DEMOD_DVB_T2
    #ifdef        Si2183_DVBT2_ADC_CREST_FACTOR_PROP
     case         Si2183_DVBT2_ADC_CREST_FACTOR_PROP_CODE:
      *data = (prop->dvbt2_adc_crest_factor.crest_factor & Si2183_DVBT2_ADC_CREST_FACTOR_PROP_CREST_FACTOR_MASK) << Si2183_DVBT2_ADC_CREST_FACTOR_PROP_CREST_FACTOR_LSB ;
     break;
    #endif /*     Si2183_DVBT2_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_DVBT2_AFC_RANGE_PROP
     case         Si2183_DVBT2_AFC_RANGE_PROP_CODE:
      *data = (prop->dvbt2_afc_range.range_khz & Si2183_DVBT2_AFC_RANGE_PROP_RANGE_KHZ_MASK) << Si2183_DVBT2_AFC_RANGE_PROP_RANGE_KHZ_LSB ;
     break;
    #endif /*     Si2183_DVBT2_AFC_RANGE_PROP */
    #ifdef        Si2183_DVBT2_FEF_TUNER_PROP
     case         Si2183_DVBT2_FEF_TUNER_PROP_CODE:
      *data = (prop->dvbt2_fef_tuner.tuner_delay         & Si2183_DVBT2_FEF_TUNER_PROP_TUNER_DELAY_MASK        ) << Si2183_DVBT2_FEF_TUNER_PROP_TUNER_DELAY_LSB  |
              (prop->dvbt2_fef_tuner.tuner_freeze_time   & Si2183_DVBT2_FEF_TUNER_PROP_TUNER_FREEZE_TIME_MASK  ) << Si2183_DVBT2_FEF_TUNER_PROP_TUNER_FREEZE_TIME_LSB  |
              (prop->dvbt2_fef_tuner.tuner_unfreeze_time & Si2183_DVBT2_FEF_TUNER_PROP_TUNER_UNFREEZE_TIME_MASK) << Si2183_DVBT2_FEF_TUNER_PROP_TUNER_UNFREEZE_TIME_LSB ;
     break;
    #endif /*     Si2183_DVBT2_FEF_TUNER_PROP */
    #ifdef        Si2183_DVBT2_MODE_PROP
     case         Si2183_DVBT2_MODE_PROP_CODE:
      *data = (prop->dvbt2_mode.lock_mode & Si2183_DVBT2_MODE_PROP_LOCK_MODE_MASK) << Si2183_DVBT2_MODE_PROP_LOCK_MODE_LSB ;
     break;
    #endif /*     Si2183_DVBT2_MODE_PROP */
#endif /* DEMOD_DVB_T2 */

#ifdef    DEMOD_DVB_T
    #ifdef        Si2183_DVBT_ADC_CREST_FACTOR_PROP
     case         Si2183_DVBT_ADC_CREST_FACTOR_PROP_CODE:
      *data = (prop->dvbt_adc_crest_factor.crest_factor & Si2183_DVBT_ADC_CREST_FACTOR_PROP_CREST_FACTOR_MASK) << Si2183_DVBT_ADC_CREST_FACTOR_PROP_CREST_FACTOR_LSB ;
     break;
    #endif /*     Si2183_DVBT_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_DVBT_AFC_RANGE_PROP
     case         Si2183_DVBT_AFC_RANGE_PROP_CODE:
      *data = (prop->dvbt_afc_range.range_khz & Si2183_DVBT_AFC_RANGE_PROP_RANGE_KHZ_MASK) << Si2183_DVBT_AFC_RANGE_PROP_RANGE_KHZ_LSB ;
     break;
    #endif /*     Si2183_DVBT_AFC_RANGE_PROP */
    #ifdef        Si2183_DVBT_HIERARCHY_PROP
     case         Si2183_DVBT_HIERARCHY_PROP_CODE:
      *data = (prop->dvbt_hierarchy.stream & Si2183_DVBT_HIERARCHY_PROP_STREAM_MASK) << Si2183_DVBT_HIERARCHY_PROP_STREAM_LSB ;
     break;
    #endif /*     Si2183_DVBT_HIERARCHY_PROP */
#endif /* DEMOD_DVB_T */

#ifdef    DEMOD_ISDB_T
    #ifdef        Si2183_ISDBT_AC_SELECT_PROP
     case         Si2183_ISDBT_AC_SELECT_PROP_CODE:
      *data = (prop->isdbt_ac_select.segment_sel & Si2183_ISDBT_AC_SELECT_PROP_SEGMENT_SEL_MASK) << Si2183_ISDBT_AC_SELECT_PROP_SEGMENT_SEL_LSB  |
              (prop->isdbt_ac_select.filtering   & Si2183_ISDBT_AC_SELECT_PROP_FILTERING_MASK  ) << Si2183_ISDBT_AC_SELECT_PROP_FILTERING_LSB ;
     break;
    #endif /*     Si2183_ISDBT_AC_SELECT_PROP */
    #ifdef        Si2183_ISDBT_ADC_CREST_FACTOR_PROP
     case         Si2183_ISDBT_ADC_CREST_FACTOR_PROP_CODE:
      *data = (prop->isdbt_adc_crest_factor.crest_factor & Si2183_ISDBT_ADC_CREST_FACTOR_PROP_CREST_FACTOR_MASK) << Si2183_ISDBT_ADC_CREST_FACTOR_PROP_CREST_FACTOR_LSB ;
     break;
    #endif /*     Si2183_ISDBT_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_ISDBT_AFC_RANGE_PROP
     case         Si2183_ISDBT_AFC_RANGE_PROP_CODE:
      *data = (prop->isdbt_afc_range.range_khz & Si2183_ISDBT_AFC_RANGE_PROP_RANGE_KHZ_MASK) << Si2183_ISDBT_AFC_RANGE_PROP_RANGE_KHZ_LSB ;
     break;
    #endif /*     Si2183_ISDBT_AFC_RANGE_PROP */
    #ifdef        Si2183_ISDBT_MODE_PROP
     case         Si2183_ISDBT_MODE_PROP_CODE:
      *data = (prop->isdbt_mode.layer_mon & Si2183_ISDBT_MODE_PROP_LAYER_MON_MASK) << Si2183_ISDBT_MODE_PROP_LAYER_MON_LSB  |
              (prop->isdbt_mode.dl_config & Si2183_ISDBT_MODE_PROP_DL_CONFIG_MASK) << Si2183_ISDBT_MODE_PROP_DL_CONFIG_LSB  |
              (prop->isdbt_mode.tradeoff  & Si2183_ISDBT_MODE_PROP_TRADEOFF_MASK ) << Si2183_ISDBT_MODE_PROP_TRADEOFF_LSB ;
     break;
    #endif /*     Si2183_ISDBT_MODE_PROP */
#endif /* DEMOD_ISDB_T */

    #ifdef        Si2183_MASTER_IEN_PROP
     case         Si2183_MASTER_IEN_PROP_CODE:
      *data = (prop->master_ien.ddien   & Si2183_MASTER_IEN_PROP_DDIEN_MASK  ) << Si2183_MASTER_IEN_PROP_DDIEN_LSB  |
              (prop->master_ien.scanien & Si2183_MASTER_IEN_PROP_SCANIEN_MASK) << Si2183_MASTER_IEN_PROP_SCANIEN_LSB  |
              (prop->master_ien.errien  & Si2183_MASTER_IEN_PROP_ERRIEN_MASK ) << Si2183_MASTER_IEN_PROP_ERRIEN_LSB  |
              (prop->master_ien.ctsien  & Si2183_MASTER_IEN_PROP_CTSIEN_MASK ) << Si2183_MASTER_IEN_PROP_CTSIEN_LSB ;
     break;
    #endif /*     Si2183_MASTER_IEN_PROP */
#ifdef    DEMOD_MCNS
    #ifdef        Si2183_MCNS_ADC_CREST_FACTOR_PROP
     case         Si2183_MCNS_ADC_CREST_FACTOR_PROP_CODE:
      *data = (prop->mcns_adc_crest_factor.crest_factor & Si2183_MCNS_ADC_CREST_FACTOR_PROP_CREST_FACTOR_MASK) << Si2183_MCNS_ADC_CREST_FACTOR_PROP_CREST_FACTOR_LSB ;
     break;
    #endif /*     Si2183_MCNS_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_MCNS_AFC_RANGE_PROP
     case         Si2183_MCNS_AFC_RANGE_PROP_CODE:
      *data = (prop->mcns_afc_range.range_khz & Si2183_MCNS_AFC_RANGE_PROP_RANGE_KHZ_MASK) << Si2183_MCNS_AFC_RANGE_PROP_RANGE_KHZ_LSB ;
     break;
    #endif /*     Si2183_MCNS_AFC_RANGE_PROP */
    #ifdef        Si2183_MCNS_CONSTELLATION_PROP
     case         Si2183_MCNS_CONSTELLATION_PROP_CODE:
      *data = (prop->mcns_constellation.constellation & Si2183_MCNS_CONSTELLATION_PROP_CONSTELLATION_MASK) << Si2183_MCNS_CONSTELLATION_PROP_CONSTELLATION_LSB ;
     break;
    #endif /*     Si2183_MCNS_CONSTELLATION_PROP */
    #ifdef        Si2183_MCNS_SYMBOL_RATE_PROP
     case         Si2183_MCNS_SYMBOL_RATE_PROP_CODE:
      *data = (prop->mcns_symbol_rate.rate & Si2183_MCNS_SYMBOL_RATE_PROP_RATE_MASK) << Si2183_MCNS_SYMBOL_RATE_PROP_RATE_LSB ;
     break;
    #endif /*     Si2183_MCNS_SYMBOL_RATE_PROP */
#endif /* DEMOD_MCNS */

    #ifdef        Si2183_SCAN_FMAX_PROP
     case         Si2183_SCAN_FMAX_PROP_CODE:
      *data = (prop->scan_fmax.scan_fmax & Si2183_SCAN_FMAX_PROP_SCAN_FMAX_MASK) << Si2183_SCAN_FMAX_PROP_SCAN_FMAX_LSB ;
     break;
    #endif /*     Si2183_SCAN_FMAX_PROP */
    #ifdef        Si2183_SCAN_FMIN_PROP
     case         Si2183_SCAN_FMIN_PROP_CODE:
      *data = (prop->scan_fmin.scan_fmin & Si2183_SCAN_FMIN_PROP_SCAN_FMIN_MASK) << Si2183_SCAN_FMIN_PROP_SCAN_FMIN_LSB ;
     break;
    #endif /*     Si2183_SCAN_FMIN_PROP */
    #ifdef        Si2183_SCAN_IEN_PROP
     case         Si2183_SCAN_IEN_PROP_CODE:
      *data = (prop->scan_ien.buzien & Si2183_SCAN_IEN_PROP_BUZIEN_MASK) << Si2183_SCAN_IEN_PROP_BUZIEN_LSB  |
              (prop->scan_ien.reqien & Si2183_SCAN_IEN_PROP_REQIEN_MASK) << Si2183_SCAN_IEN_PROP_REQIEN_LSB ;
     break;
    #endif /*     Si2183_SCAN_IEN_PROP */
    #ifdef        Si2183_SCAN_INT_SENSE_PROP
     case         Si2183_SCAN_INT_SENSE_PROP_CODE:
      *data = (prop->scan_int_sense.buznegen & Si2183_SCAN_INT_SENSE_PROP_BUZNEGEN_MASK) << Si2183_SCAN_INT_SENSE_PROP_BUZNEGEN_LSB  |
              (prop->scan_int_sense.reqnegen & Si2183_SCAN_INT_SENSE_PROP_REQNEGEN_MASK) << Si2183_SCAN_INT_SENSE_PROP_REQNEGEN_LSB  |
              (prop->scan_int_sense.buzposen & Si2183_SCAN_INT_SENSE_PROP_BUZPOSEN_MASK) << Si2183_SCAN_INT_SENSE_PROP_BUZPOSEN_LSB  |
              (prop->scan_int_sense.reqposen & Si2183_SCAN_INT_SENSE_PROP_REQPOSEN_MASK) << Si2183_SCAN_INT_SENSE_PROP_REQPOSEN_LSB ;
     break;
    #endif /*     Si2183_SCAN_INT_SENSE_PROP */
#ifdef    DEMOD_DVB_S_S2_DSS
    #ifdef        Si2183_SCAN_SAT_CONFIG_PROP
     case         Si2183_SCAN_SAT_CONFIG_PROP_CODE:
      *data = (prop->scan_sat_config.analog_detect & Si2183_SCAN_SAT_CONFIG_PROP_ANALOG_DETECT_MASK) << Si2183_SCAN_SAT_CONFIG_PROP_ANALOG_DETECT_LSB  |
              (prop->scan_sat_config.reserved1     & Si2183_SCAN_SAT_CONFIG_PROP_RESERVED1_MASK    ) << Si2183_SCAN_SAT_CONFIG_PROP_RESERVED1_LSB  |
              (prop->scan_sat_config.reserved2     & Si2183_SCAN_SAT_CONFIG_PROP_RESERVED2_MASK    ) << Si2183_SCAN_SAT_CONFIG_PROP_RESERVED2_LSB |
              (prop->scan_sat_config.scan_debug    & Si2183_SCAN_SAT_CONFIG_PROP_SCAN_DEBUG_MASK   ) << Si2183_SCAN_SAT_CONFIG_PROP_SCAN_DEBUG_LSB ;
     break;
    #endif /*     Si2183_SCAN_SAT_CONFIG_PROP */
    #ifdef        Si2183_SCAN_SAT_UNICABLE_BW_PROP
     case         Si2183_SCAN_SAT_UNICABLE_BW_PROP_CODE:
      *data = (prop->scan_sat_unicable_bw.scan_sat_unicable_bw & Si2183_SCAN_SAT_UNICABLE_BW_PROP_SCAN_SAT_UNICABLE_BW_MASK) << Si2183_SCAN_SAT_UNICABLE_BW_PROP_SCAN_SAT_UNICABLE_BW_LSB ;
     break;
    #endif /*     Si2183_SCAN_SAT_UNICABLE_BW_PROP */
    #ifdef        Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP
     case         Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP_CODE:
      *data = (prop->scan_sat_unicable_min_tune_step.scan_sat_unicable_min_tune_step & Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_MASK) << Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_LSB ;
     break;
    #endif /*     Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP */
#endif /* DEMOD_DVB_S_S2_DSS */

    #ifdef        Si2183_SCAN_SYMB_RATE_MAX_PROP
     case         Si2183_SCAN_SYMB_RATE_MAX_PROP_CODE:
      *data = (prop->scan_symb_rate_max.scan_symb_rate_max & Si2183_SCAN_SYMB_RATE_MAX_PROP_SCAN_SYMB_RATE_MAX_MASK) << Si2183_SCAN_SYMB_RATE_MAX_PROP_SCAN_SYMB_RATE_MAX_LSB ;
     break;
    #endif /*     Si2183_SCAN_SYMB_RATE_MAX_PROP */
    #ifdef        Si2183_SCAN_SYMB_RATE_MIN_PROP
     case         Si2183_SCAN_SYMB_RATE_MIN_PROP_CODE:
      *data = (prop->scan_symb_rate_min.scan_symb_rate_min & Si2183_SCAN_SYMB_RATE_MIN_PROP_SCAN_SYMB_RATE_MIN_MASK) << Si2183_SCAN_SYMB_RATE_MIN_PROP_SCAN_SYMB_RATE_MIN_LSB ;
     break;
    #endif /*     Si2183_SCAN_SYMB_RATE_MIN_PROP */
#ifdef    TERRESTRIAL_FRONT_END
    #ifdef        Si2183_SCAN_TER_CONFIG_PROP
     case         Si2183_SCAN_TER_CONFIG_PROP_CODE:
      *data = (prop->scan_ter_config.mode          & Si2183_SCAN_TER_CONFIG_PROP_MODE_MASK         ) << Si2183_SCAN_TER_CONFIG_PROP_MODE_LSB  |
              (prop->scan_ter_config.analog_bw     & Si2183_SCAN_TER_CONFIG_PROP_ANALOG_BW_MASK    ) << Si2183_SCAN_TER_CONFIG_PROP_ANALOG_BW_LSB  |
              (prop->scan_ter_config.search_analog & Si2183_SCAN_TER_CONFIG_PROP_SEARCH_ANALOG_MASK) << Si2183_SCAN_TER_CONFIG_PROP_SEARCH_ANALOG_LSB |
              (prop->scan_ter_config.scan_debug    & Si2183_SCAN_TER_CONFIG_PROP_SCAN_DEBUG_MASK   ) << Si2183_SCAN_TER_CONFIG_PROP_SCAN_DEBUG_LSB ;
     break;
    #endif /*     Si2183_SCAN_TER_CONFIG_PROP */
#endif /* TERRESTRIAL_FRONT_END */

     default : return ERROR_Si2183_UNKNOWN_PROPERTY; break;
    }
    return NO_Si2183_ERROR;
}


/***********************************************************************************************************************
  Si2183_UnpackProperty function
  Use:        This function will unpack all the members of a property from an integer from the GetProperty function.

  Parameter: *prop          the Si2183 property context
  Parameter:  prop_code     the property Id
  Parameter:  data          the property data

  Returns:    NO_Si2183_ERROR if the property exists.
 ***********************************************************************************************************************/
unsigned char Si2183_UnpackProperty          (Si2183_PropObj   *prop, unsigned int prop_code, signed   int  data) {
    switch (prop_code) {
    #ifdef        Si2183_DD_BER_RESOL_PROP
     case         Si2183_DD_BER_RESOL_PROP_CODE:
               prop->dd_ber_resol.exp  = (data >> Si2183_DD_BER_RESOL_PROP_EXP_LSB ) & Si2183_DD_BER_RESOL_PROP_EXP_MASK;
               prop->dd_ber_resol.mant = (data >> Si2183_DD_BER_RESOL_PROP_MANT_LSB) & Si2183_DD_BER_RESOL_PROP_MANT_MASK;
     break;
    #endif /*     Si2183_DD_BER_RESOL_PROP */
    #ifdef        Si2183_DD_CBER_RESOL_PROP
     case         Si2183_DD_CBER_RESOL_PROP_CODE:
               prop->dd_cber_resol.exp  = (data >> Si2183_DD_CBER_RESOL_PROP_EXP_LSB ) & Si2183_DD_CBER_RESOL_PROP_EXP_MASK;
               prop->dd_cber_resol.mant = (data >> Si2183_DD_CBER_RESOL_PROP_MANT_LSB) & Si2183_DD_CBER_RESOL_PROP_MANT_MASK;
     break;
    #endif /*     Si2183_DD_CBER_RESOL_PROP */
#ifdef    DEMOD_DVB_S_S2_DSS
    #ifdef        Si2183_DD_DISEQC_FREQ_PROP
     case         Si2183_DD_DISEQC_FREQ_PROP_CODE:
               prop->dd_diseqc_freq.freq_hz = (data >> Si2183_DD_DISEQC_FREQ_PROP_FREQ_HZ_LSB) & Si2183_DD_DISEQC_FREQ_PROP_FREQ_HZ_MASK;
     break;
    #endif /*     Si2183_DD_DISEQC_FREQ_PROP */
    #ifdef        Si2183_DD_DISEQC_PARAM_PROP
     case         Si2183_DD_DISEQC_PARAM_PROP_CODE:
               prop->dd_diseqc_param.sequence_mode = (data >> Si2183_DD_DISEQC_PARAM_PROP_SEQUENCE_MODE_LSB) & Si2183_DD_DISEQC_PARAM_PROP_SEQUENCE_MODE_MASK;
               prop->dd_diseqc_param.input_pin     = (data >> Si2183_DD_DISEQC_PARAM_PROP_INPUT_PIN_LSB    ) & Si2183_DD_DISEQC_PARAM_PROP_INPUT_PIN_MASK;
     break;
    #endif /*     Si2183_DD_DISEQC_PARAM_PROP */
#endif /* DEMOD_DVB_S_S2_DSS */

    #ifdef        Si2183_DD_FER_RESOL_PROP
     case         Si2183_DD_FER_RESOL_PROP_CODE:
               prop->dd_fer_resol.exp  = (data >> Si2183_DD_FER_RESOL_PROP_EXP_LSB ) & Si2183_DD_FER_RESOL_PROP_EXP_MASK;
               prop->dd_fer_resol.mant = (data >> Si2183_DD_FER_RESOL_PROP_MANT_LSB) & Si2183_DD_FER_RESOL_PROP_MANT_MASK;
     break;
    #endif /*     Si2183_DD_FER_RESOL_PROP */
    #ifdef        Si2183_DD_IEN_PROP
     case         Si2183_DD_IEN_PROP_CODE:
               prop->dd_ien.ien_bit0 = (data >> Si2183_DD_IEN_PROP_IEN_BIT0_LSB) & Si2183_DD_IEN_PROP_IEN_BIT0_MASK;
               prop->dd_ien.ien_bit1 = (data >> Si2183_DD_IEN_PROP_IEN_BIT1_LSB) & Si2183_DD_IEN_PROP_IEN_BIT1_MASK;
               prop->dd_ien.ien_bit2 = (data >> Si2183_DD_IEN_PROP_IEN_BIT2_LSB) & Si2183_DD_IEN_PROP_IEN_BIT2_MASK;
               prop->dd_ien.ien_bit3 = (data >> Si2183_DD_IEN_PROP_IEN_BIT3_LSB) & Si2183_DD_IEN_PROP_IEN_BIT3_MASK;
               prop->dd_ien.ien_bit4 = (data >> Si2183_DD_IEN_PROP_IEN_BIT4_LSB) & Si2183_DD_IEN_PROP_IEN_BIT4_MASK;
               prop->dd_ien.ien_bit5 = (data >> Si2183_DD_IEN_PROP_IEN_BIT5_LSB) & Si2183_DD_IEN_PROP_IEN_BIT5_MASK;
               prop->dd_ien.ien_bit6 = (data >> Si2183_DD_IEN_PROP_IEN_BIT6_LSB) & Si2183_DD_IEN_PROP_IEN_BIT6_MASK;
               prop->dd_ien.ien_bit7 = (data >> Si2183_DD_IEN_PROP_IEN_BIT7_LSB) & Si2183_DD_IEN_PROP_IEN_BIT7_MASK;
     break;
    #endif /*     Si2183_DD_IEN_PROP */
    #ifdef        Si2183_DD_IF_INPUT_FREQ_PROP
     case         Si2183_DD_IF_INPUT_FREQ_PROP_CODE:
               prop->dd_if_input_freq.offset = (data >> Si2183_DD_IF_INPUT_FREQ_PROP_OFFSET_LSB) & Si2183_DD_IF_INPUT_FREQ_PROP_OFFSET_MASK;
     break;
    #endif /*     Si2183_DD_IF_INPUT_FREQ_PROP */
    #ifdef        Si2183_DD_INT_SENSE_PROP
     case         Si2183_DD_INT_SENSE_PROP_CODE:
               prop->dd_int_sense.neg_bit0 = (data >> Si2183_DD_INT_SENSE_PROP_NEG_BIT0_LSB) & Si2183_DD_INT_SENSE_PROP_NEG_BIT0_MASK;
               prop->dd_int_sense.neg_bit1 = (data >> Si2183_DD_INT_SENSE_PROP_NEG_BIT1_LSB) & Si2183_DD_INT_SENSE_PROP_NEG_BIT1_MASK;
               prop->dd_int_sense.neg_bit2 = (data >> Si2183_DD_INT_SENSE_PROP_NEG_BIT2_LSB) & Si2183_DD_INT_SENSE_PROP_NEG_BIT2_MASK;
               prop->dd_int_sense.neg_bit3 = (data >> Si2183_DD_INT_SENSE_PROP_NEG_BIT3_LSB) & Si2183_DD_INT_SENSE_PROP_NEG_BIT3_MASK;
               prop->dd_int_sense.neg_bit4 = (data >> Si2183_DD_INT_SENSE_PROP_NEG_BIT4_LSB) & Si2183_DD_INT_SENSE_PROP_NEG_BIT4_MASK;
               prop->dd_int_sense.neg_bit5 = (data >> Si2183_DD_INT_SENSE_PROP_NEG_BIT5_LSB) & Si2183_DD_INT_SENSE_PROP_NEG_BIT5_MASK;
               prop->dd_int_sense.neg_bit6 = (data >> Si2183_DD_INT_SENSE_PROP_NEG_BIT6_LSB) & Si2183_DD_INT_SENSE_PROP_NEG_BIT6_MASK;
               prop->dd_int_sense.neg_bit7 = (data >> Si2183_DD_INT_SENSE_PROP_NEG_BIT7_LSB) & Si2183_DD_INT_SENSE_PROP_NEG_BIT7_MASK;
               prop->dd_int_sense.pos_bit0 = (data >> Si2183_DD_INT_SENSE_PROP_POS_BIT0_LSB) & Si2183_DD_INT_SENSE_PROP_POS_BIT0_MASK;
               prop->dd_int_sense.pos_bit1 = (data >> Si2183_DD_INT_SENSE_PROP_POS_BIT1_LSB) & Si2183_DD_INT_SENSE_PROP_POS_BIT1_MASK;
               prop->dd_int_sense.pos_bit2 = (data >> Si2183_DD_INT_SENSE_PROP_POS_BIT2_LSB) & Si2183_DD_INT_SENSE_PROP_POS_BIT2_MASK;
               prop->dd_int_sense.pos_bit3 = (data >> Si2183_DD_INT_SENSE_PROP_POS_BIT3_LSB) & Si2183_DD_INT_SENSE_PROP_POS_BIT3_MASK;
               prop->dd_int_sense.pos_bit4 = (data >> Si2183_DD_INT_SENSE_PROP_POS_BIT4_LSB) & Si2183_DD_INT_SENSE_PROP_POS_BIT4_MASK;
               prop->dd_int_sense.pos_bit5 = (data >> Si2183_DD_INT_SENSE_PROP_POS_BIT5_LSB) & Si2183_DD_INT_SENSE_PROP_POS_BIT5_MASK;
               prop->dd_int_sense.pos_bit6 = (data >> Si2183_DD_INT_SENSE_PROP_POS_BIT6_LSB) & Si2183_DD_INT_SENSE_PROP_POS_BIT6_MASK;
               prop->dd_int_sense.pos_bit7 = (data >> Si2183_DD_INT_SENSE_PROP_POS_BIT7_LSB) & Si2183_DD_INT_SENSE_PROP_POS_BIT7_MASK;
     break;
    #endif /*     Si2183_DD_INT_SENSE_PROP */
    #ifdef        Si2183_DD_MODE_PROP
     case         Si2183_DD_MODE_PROP_CODE:
               prop->dd_mode.bw              = (data >> Si2183_DD_MODE_PROP_BW_LSB             ) & Si2183_DD_MODE_PROP_BW_MASK;
               prop->dd_mode.modulation      = (data >> Si2183_DD_MODE_PROP_MODULATION_LSB     ) & Si2183_DD_MODE_PROP_MODULATION_MASK;
               prop->dd_mode.invert_spectrum = (data >> Si2183_DD_MODE_PROP_INVERT_SPECTRUM_LSB) & Si2183_DD_MODE_PROP_INVERT_SPECTRUM_MASK;
               prop->dd_mode.auto_detect     = (data >> Si2183_DD_MODE_PROP_AUTO_DETECT_LSB    ) & Si2183_DD_MODE_PROP_AUTO_DETECT_MASK;
     break;
    #endif /*     Si2183_DD_MODE_PROP */
    #ifdef        Si2183_DD_PER_RESOL_PROP
     case         Si2183_DD_PER_RESOL_PROP_CODE:
               prop->dd_per_resol.exp  = (data >> Si2183_DD_PER_RESOL_PROP_EXP_LSB ) & Si2183_DD_PER_RESOL_PROP_EXP_MASK;
               prop->dd_per_resol.mant = (data >> Si2183_DD_PER_RESOL_PROP_MANT_LSB) & Si2183_DD_PER_RESOL_PROP_MANT_MASK;
     break;
    #endif /*     Si2183_DD_PER_RESOL_PROP */
    #ifdef        Si2183_DD_RSQ_BER_THRESHOLD_PROP
     case         Si2183_DD_RSQ_BER_THRESHOLD_PROP_CODE:
               prop->dd_rsq_ber_threshold.exp  = (data >> Si2183_DD_RSQ_BER_THRESHOLD_PROP_EXP_LSB ) & Si2183_DD_RSQ_BER_THRESHOLD_PROP_EXP_MASK;
               prop->dd_rsq_ber_threshold.mant = (data >> Si2183_DD_RSQ_BER_THRESHOLD_PROP_MANT_LSB) & Si2183_DD_RSQ_BER_THRESHOLD_PROP_MANT_MASK;
     break;
    #endif /*     Si2183_DD_RSQ_BER_THRESHOLD_PROP */
    #ifdef        Si2183_DD_SEC_TS_SERIAL_DIFF_PROP
     case         Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_CODE:
               prop->dd_sec_ts_serial_diff.ts_data1_strength  = (data >> Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA1_STRENGTH_LSB ) & Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA1_STRENGTH_MASK;
               prop->dd_sec_ts_serial_diff.ts_data1_shape     = (data >> Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA1_SHAPE_LSB    ) & Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA1_SHAPE_MASK;
               prop->dd_sec_ts_serial_diff.ts_data2_strength  = (data >> Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA2_STRENGTH_LSB ) & Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA2_STRENGTH_MASK;
               prop->dd_sec_ts_serial_diff.ts_data2_shape     = (data >> Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA2_SHAPE_LSB    ) & Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA2_SHAPE_MASK;
               prop->dd_sec_ts_serial_diff.ts_clkb_on_data1   = (data >> Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_CLKB_ON_DATA1_LSB  ) & Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_CLKB_ON_DATA1_MASK;
               prop->dd_sec_ts_serial_diff.ts_data0b_on_data2 = (data >> Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA0B_ON_DATA2_LSB) & Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA0B_ON_DATA2_MASK;
     break;
    #endif /*     Si2183_DD_SEC_TS_SERIAL_DIFF_PROP */
    #ifdef        Si2183_DD_SEC_TS_SETUP_PAR_PROP
     case         Si2183_DD_SEC_TS_SETUP_PAR_PROP_CODE:
               prop->dd_sec_ts_setup_par.ts_data_strength = (data >> Si2183_DD_SEC_TS_SETUP_PAR_PROP_TS_DATA_STRENGTH_LSB) & Si2183_DD_SEC_TS_SETUP_PAR_PROP_TS_DATA_STRENGTH_MASK;
               prop->dd_sec_ts_setup_par.ts_data_shape    = (data >> Si2183_DD_SEC_TS_SETUP_PAR_PROP_TS_DATA_SHAPE_LSB   ) & Si2183_DD_SEC_TS_SETUP_PAR_PROP_TS_DATA_SHAPE_MASK;
               prop->dd_sec_ts_setup_par.ts_clk_strength  = (data >> Si2183_DD_SEC_TS_SETUP_PAR_PROP_TS_CLK_STRENGTH_LSB ) & Si2183_DD_SEC_TS_SETUP_PAR_PROP_TS_CLK_STRENGTH_MASK;
               prop->dd_sec_ts_setup_par.ts_clk_shape     = (data >> Si2183_DD_SEC_TS_SETUP_PAR_PROP_TS_CLK_SHAPE_LSB    ) & Si2183_DD_SEC_TS_SETUP_PAR_PROP_TS_CLK_SHAPE_MASK;
     break;
    #endif /*     Si2183_DD_SEC_TS_SETUP_PAR_PROP */
    #ifdef        Si2183_DD_SEC_TS_SETUP_SER_PROP
     case         Si2183_DD_SEC_TS_SETUP_SER_PROP_CODE:
               prop->dd_sec_ts_setup_ser.ts_data_strength = (data >> Si2183_DD_SEC_TS_SETUP_SER_PROP_TS_DATA_STRENGTH_LSB) & Si2183_DD_SEC_TS_SETUP_SER_PROP_TS_DATA_STRENGTH_MASK;
               prop->dd_sec_ts_setup_ser.ts_data_shape    = (data >> Si2183_DD_SEC_TS_SETUP_SER_PROP_TS_DATA_SHAPE_LSB   ) & Si2183_DD_SEC_TS_SETUP_SER_PROP_TS_DATA_SHAPE_MASK;
               prop->dd_sec_ts_setup_ser.ts_clk_strength  = (data >> Si2183_DD_SEC_TS_SETUP_SER_PROP_TS_CLK_STRENGTH_LSB ) & Si2183_DD_SEC_TS_SETUP_SER_PROP_TS_CLK_STRENGTH_MASK;
               prop->dd_sec_ts_setup_ser.ts_clk_shape     = (data >> Si2183_DD_SEC_TS_SETUP_SER_PROP_TS_CLK_SHAPE_LSB    ) & Si2183_DD_SEC_TS_SETUP_SER_PROP_TS_CLK_SHAPE_MASK;
     break;
    #endif /*     Si2183_DD_SEC_TS_SETUP_SER_PROP */
    #ifdef        Si2183_DD_SEC_TS_SLR_SERIAL_PROP
     case         Si2183_DD_SEC_TS_SLR_SERIAL_PROP_CODE:
               prop->dd_sec_ts_slr_serial.ts_data_slr     = (data >> Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA_SLR_LSB    ) & Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA_SLR_MASK;
               prop->dd_sec_ts_slr_serial.ts_data_slr_on  = (data >> Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA_SLR_ON_LSB ) & Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA_SLR_ON_MASK;
               prop->dd_sec_ts_slr_serial.ts_data1_slr    = (data >> Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA1_SLR_LSB   ) & Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA1_SLR_MASK;
               prop->dd_sec_ts_slr_serial.ts_data1_slr_on = (data >> Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA1_SLR_ON_LSB) & Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA1_SLR_ON_MASK;
               prop->dd_sec_ts_slr_serial.ts_data2_slr    = (data >> Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA2_SLR_LSB   ) & Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA2_SLR_MASK;
               prop->dd_sec_ts_slr_serial.ts_data2_slr_on = (data >> Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA2_SLR_ON_LSB) & Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA2_SLR_ON_MASK;
               prop->dd_sec_ts_slr_serial.ts_clk_slr      = (data >> Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_CLK_SLR_LSB     ) & Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_CLK_SLR_MASK;
               prop->dd_sec_ts_slr_serial.ts_clk_slr_on   = (data >> Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_CLK_SLR_ON_LSB  ) & Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_CLK_SLR_ON_MASK;
     break;
    #endif /*     Si2183_DD_SEC_TS_SLR_SERIAL_PROP */
    #ifdef        Si2183_DD_SSI_SQI_PARAM_PROP
     case         Si2183_DD_SSI_SQI_PARAM_PROP_CODE:
               prop->dd_ssi_sqi_param.sqi_average = (data >> Si2183_DD_SSI_SQI_PARAM_PROP_SQI_AVERAGE_LSB) & Si2183_DD_SSI_SQI_PARAM_PROP_SQI_AVERAGE_MASK;
     break;
    #endif /*     Si2183_DD_SSI_SQI_PARAM_PROP */
    #ifdef        Si2183_DD_TS_FREQ_PROP
     case         Si2183_DD_TS_FREQ_PROP_CODE:
               prop->dd_ts_freq.req_freq_10khz = (data >> Si2183_DD_TS_FREQ_PROP_REQ_FREQ_10KHZ_LSB) & Si2183_DD_TS_FREQ_PROP_REQ_FREQ_10KHZ_MASK;
     break;
    #endif /*     Si2183_DD_TS_FREQ_PROP */
    #ifdef        Si2183_DD_TS_FREQ_MAX_PROP
     case         Si2183_DD_TS_FREQ_MAX_PROP_CODE:
               prop->dd_ts_freq_max.req_freq_max_10khz = (data >> Si2183_DD_TS_FREQ_MAX_PROP_REQ_FREQ_MAX_10KHZ_LSB) & Si2183_DD_TS_FREQ_MAX_PROP_REQ_FREQ_MAX_10KHZ_MASK;
     break;
    #endif /*     Si2183_DD_TS_FREQ_MAX_PROP */
    #ifdef        Si2183_DD_TS_MODE_PROP
     case         Si2183_DD_TS_MODE_PROP_CODE:
               prop->dd_ts_mode.mode               = (data >> Si2183_DD_TS_MODE_PROP_MODE_LSB              ) & Si2183_DD_TS_MODE_PROP_MODE_MASK;
               prop->dd_ts_mode.clock              = (data >> Si2183_DD_TS_MODE_PROP_CLOCK_LSB             ) & Si2183_DD_TS_MODE_PROP_CLOCK_MASK;
               prop->dd_ts_mode.clk_gapped_en      = (data >> Si2183_DD_TS_MODE_PROP_CLK_GAPPED_EN_LSB     ) & Si2183_DD_TS_MODE_PROP_CLK_GAPPED_EN_MASK;
               prop->dd_ts_mode.ts_err_polarity    = (data >> Si2183_DD_TS_MODE_PROP_TS_ERR_POLARITY_LSB   ) & Si2183_DD_TS_MODE_PROP_TS_ERR_POLARITY_MASK;
               prop->dd_ts_mode.special            = (data >> Si2183_DD_TS_MODE_PROP_SPECIAL_LSB           ) & Si2183_DD_TS_MODE_PROP_SPECIAL_MASK;
               prop->dd_ts_mode.ts_freq_resolution = (data >> Si2183_DD_TS_MODE_PROP_TS_FREQ_RESOLUTION_LSB) & Si2183_DD_TS_MODE_PROP_TS_FREQ_RESOLUTION_MASK;
               prop->dd_ts_mode.serial_pin_selection = (data >> Si2183_DD_TS_MODE_PROP_SERIAL_PIN_SELECTION_LSB) & Si2183_DD_TS_MODE_PROP_SERIAL_PIN_SELECTION_MASK;
     break;
    #endif /*     Si2183_DD_TS_MODE_PROP */
    #ifdef        Si2183_DD_TS_SERIAL_DIFF_PROP
     case         Si2183_DD_TS_SERIAL_DIFF_PROP_CODE:
               prop->dd_ts_serial_diff.ts_data1_strength  = (data >> Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA1_STRENGTH_LSB ) & Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA1_STRENGTH_MASK;
               prop->dd_ts_serial_diff.ts_data1_shape     = (data >> Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA1_SHAPE_LSB    ) & Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA1_SHAPE_MASK;
               prop->dd_ts_serial_diff.ts_data2_strength  = (data >> Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA2_STRENGTH_LSB ) & Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA2_STRENGTH_MASK;
               prop->dd_ts_serial_diff.ts_data2_shape     = (data >> Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA2_SHAPE_LSB    ) & Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA2_SHAPE_MASK;
               prop->dd_ts_serial_diff.ts_clkb_on_data1   = (data >> Si2183_DD_TS_SERIAL_DIFF_PROP_TS_CLKB_ON_DATA1_LSB  ) & Si2183_DD_TS_SERIAL_DIFF_PROP_TS_CLKB_ON_DATA1_MASK;
               prop->dd_ts_serial_diff.ts_data0b_on_data2 = (data >> Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA0B_ON_DATA2_LSB) & Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA0B_ON_DATA2_MASK;
     break;
    #endif /*     Si2183_DD_TS_SERIAL_DIFF_PROP */
    #ifdef        Si2183_DD_TS_SETUP_PAR_PROP
     case         Si2183_DD_TS_SETUP_PAR_PROP_CODE:
               prop->dd_ts_setup_par.ts_data_strength = (data >> Si2183_DD_TS_SETUP_PAR_PROP_TS_DATA_STRENGTH_LSB) & Si2183_DD_TS_SETUP_PAR_PROP_TS_DATA_STRENGTH_MASK;
               prop->dd_ts_setup_par.ts_data_shape    = (data >> Si2183_DD_TS_SETUP_PAR_PROP_TS_DATA_SHAPE_LSB   ) & Si2183_DD_TS_SETUP_PAR_PROP_TS_DATA_SHAPE_MASK;
               prop->dd_ts_setup_par.ts_clk_strength  = (data >> Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_STRENGTH_LSB ) & Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_STRENGTH_MASK;
               prop->dd_ts_setup_par.ts_clk_shape     = (data >> Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_SHAPE_LSB    ) & Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_SHAPE_MASK;
               prop->dd_ts_setup_par.ts_clk_invert    = (data >> Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_INVERT_LSB   ) & Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_INVERT_MASK;
               prop->dd_ts_setup_par.ts_clk_shift     = (data >> Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_SHIFT_LSB    ) & Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_SHIFT_MASK;
     break;
    #endif /*     Si2183_DD_TS_SETUP_PAR_PROP */
    #ifdef        Si2183_DD_TS_SETUP_SER_PROP
     case         Si2183_DD_TS_SETUP_SER_PROP_CODE:
               prop->dd_ts_setup_ser.ts_data_strength = (data >> Si2183_DD_TS_SETUP_SER_PROP_TS_DATA_STRENGTH_LSB) & Si2183_DD_TS_SETUP_SER_PROP_TS_DATA_STRENGTH_MASK;
               prop->dd_ts_setup_ser.ts_data_shape    = (data >> Si2183_DD_TS_SETUP_SER_PROP_TS_DATA_SHAPE_LSB   ) & Si2183_DD_TS_SETUP_SER_PROP_TS_DATA_SHAPE_MASK;
               prop->dd_ts_setup_ser.ts_clk_strength  = (data >> Si2183_DD_TS_SETUP_SER_PROP_TS_CLK_STRENGTH_LSB ) & Si2183_DD_TS_SETUP_SER_PROP_TS_CLK_STRENGTH_MASK;
               prop->dd_ts_setup_ser.ts_clk_shape     = (data >> Si2183_DD_TS_SETUP_SER_PROP_TS_CLK_SHAPE_LSB    ) & Si2183_DD_TS_SETUP_SER_PROP_TS_CLK_SHAPE_MASK;
               prop->dd_ts_setup_ser.ts_clk_invert    = (data >> Si2183_DD_TS_SETUP_SER_PROP_TS_CLK_INVERT_LSB   ) & Si2183_DD_TS_SETUP_SER_PROP_TS_CLK_INVERT_MASK;
               prop->dd_ts_setup_ser.ts_sync_duration = (data >> Si2183_DD_TS_SETUP_SER_PROP_TS_SYNC_DURATION_LSB) & Si2183_DD_TS_SETUP_SER_PROP_TS_SYNC_DURATION_MASK;
               prop->dd_ts_setup_ser.ts_byte_order    = (data >> Si2183_DD_TS_SETUP_SER_PROP_TS_BYTE_ORDER_LSB   ) & Si2183_DD_TS_SETUP_SER_PROP_TS_BYTE_ORDER_MASK;
     break;
    #endif /*     Si2183_DD_TS_SETUP_SER_PROP */
    #ifdef        Si2183_DD_TS_SLR_SERIAL_PROP
     case         Si2183_DD_TS_SLR_SERIAL_PROP_CODE:
               prop->dd_ts_slr_serial.ts_data_slr     = (data >> Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA_SLR_LSB    ) & Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA_SLR_MASK;
               prop->dd_ts_slr_serial.ts_data_slr_on  = (data >> Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA_SLR_ON_LSB ) & Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA_SLR_ON_MASK;
               prop->dd_ts_slr_serial.ts_data1_slr    = (data >> Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA1_SLR_LSB   ) & Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA1_SLR_MASK;
               prop->dd_ts_slr_serial.ts_data1_slr_on = (data >> Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA1_SLR_ON_LSB) & Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA1_SLR_ON_MASK;
               prop->dd_ts_slr_serial.ts_data2_slr    = (data >> Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA2_SLR_LSB   ) & Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA2_SLR_MASK;
               prop->dd_ts_slr_serial.ts_data2_slr_on = (data >> Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA2_SLR_ON_LSB) & Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA2_SLR_ON_MASK;
               prop->dd_ts_slr_serial.ts_clk_slr      = (data >> Si2183_DD_TS_SLR_SERIAL_PROP_TS_CLK_SLR_LSB     ) & Si2183_DD_TS_SLR_SERIAL_PROP_TS_CLK_SLR_MASK;
               prop->dd_ts_slr_serial.ts_clk_slr_on   = (data >> Si2183_DD_TS_SLR_SERIAL_PROP_TS_CLK_SLR_ON_LSB  ) & Si2183_DD_TS_SLR_SERIAL_PROP_TS_CLK_SLR_ON_MASK;
     break;
    #endif /*     Si2183_DD_TS_SLR_SERIAL_PROP */
#ifdef    DEMOD_DVB_C2
    #ifdef        Si2183_DVBC2_ADC_CREST_FACTOR_PROP
     case         Si2183_DVBC2_ADC_CREST_FACTOR_PROP_CODE:
               prop->dvbc2_adc_crest_factor.crest_factor = (data >> Si2183_DVBC2_ADC_CREST_FACTOR_PROP_CREST_FACTOR_LSB) & Si2183_DVBC2_ADC_CREST_FACTOR_PROP_CREST_FACTOR_MASK;
     break;
    #endif /*     Si2183_DVBC2_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_DVBC2_AFC_RANGE_PROP
     case         Si2183_DVBC2_AFC_RANGE_PROP_CODE:
               prop->dvbc2_afc_range.range_khz = (data >> Si2183_DVBC2_AFC_RANGE_PROP_RANGE_KHZ_LSB) & Si2183_DVBC2_AFC_RANGE_PROP_RANGE_KHZ_MASK;
     break;
    #endif /*     Si2183_DVBC2_AFC_RANGE_PROP */
#endif /* DEMOD_DVB_C2 */

#ifdef    DEMOD_DVB_C
    #ifdef        Si2183_DVBC_ADC_CREST_FACTOR_PROP
     case         Si2183_DVBC_ADC_CREST_FACTOR_PROP_CODE:
               prop->dvbc_adc_crest_factor.crest_factor = (data >> Si2183_DVBC_ADC_CREST_FACTOR_PROP_CREST_FACTOR_LSB) & Si2183_DVBC_ADC_CREST_FACTOR_PROP_CREST_FACTOR_MASK;
     break;
    #endif /*     Si2183_DVBC_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_DVBC_AFC_RANGE_PROP
     case         Si2183_DVBC_AFC_RANGE_PROP_CODE:
               prop->dvbc_afc_range.range_khz = (data >> Si2183_DVBC_AFC_RANGE_PROP_RANGE_KHZ_LSB) & Si2183_DVBC_AFC_RANGE_PROP_RANGE_KHZ_MASK;
     break;
    #endif /*     Si2183_DVBC_AFC_RANGE_PROP */
    #ifdef        Si2183_DVBC_CONSTELLATION_PROP
     case         Si2183_DVBC_CONSTELLATION_PROP_CODE:
               prop->dvbc_constellation.constellation = (data >> Si2183_DVBC_CONSTELLATION_PROP_CONSTELLATION_LSB) & Si2183_DVBC_CONSTELLATION_PROP_CONSTELLATION_MASK;
     break;
    #endif /*     Si2183_DVBC_CONSTELLATION_PROP */
    #ifdef        Si2183_DVBC_SYMBOL_RATE_PROP
     case         Si2183_DVBC_SYMBOL_RATE_PROP_CODE:
               prop->dvbc_symbol_rate.rate = (data >> Si2183_DVBC_SYMBOL_RATE_PROP_RATE_LSB) & Si2183_DVBC_SYMBOL_RATE_PROP_RATE_MASK;
     break;
    #endif /*     Si2183_DVBC_SYMBOL_RATE_PROP */
#endif /* DEMOD_DVB_C */

#ifdef    DEMOD_DVB_S_S2_DSS
    #ifdef        Si2183_DVBS2_ADC_CREST_FACTOR_PROP
     case         Si2183_DVBS2_ADC_CREST_FACTOR_PROP_CODE:
               prop->dvbs2_adc_crest_factor.crest_factor = (data >> Si2183_DVBS2_ADC_CREST_FACTOR_PROP_CREST_FACTOR_LSB) & Si2183_DVBS2_ADC_CREST_FACTOR_PROP_CREST_FACTOR_MASK;
     break;
    #endif /*     Si2183_DVBS2_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_DVBS2_AFC_RANGE_PROP
     case         Si2183_DVBS2_AFC_RANGE_PROP_CODE:
               prop->dvbs2_afc_range.range_khz = (data >> Si2183_DVBS2_AFC_RANGE_PROP_RANGE_KHZ_LSB) & Si2183_DVBS2_AFC_RANGE_PROP_RANGE_KHZ_MASK;
     break;
    #endif /*     Si2183_DVBS2_AFC_RANGE_PROP */
    #ifdef        Si2183_DVBS2_SYMBOL_RATE_PROP
     case         Si2183_DVBS2_SYMBOL_RATE_PROP_CODE:
               prop->dvbs2_symbol_rate.rate = (data >> Si2183_DVBS2_SYMBOL_RATE_PROP_RATE_LSB) & Si2183_DVBS2_SYMBOL_RATE_PROP_RATE_MASK;
     break;
    #endif /*     Si2183_DVBS2_SYMBOL_RATE_PROP */
    #ifdef        Si2183_DVBS_ADC_CREST_FACTOR_PROP
     case         Si2183_DVBS_ADC_CREST_FACTOR_PROP_CODE:
               prop->dvbs_adc_crest_factor.crest_factor = (data >> Si2183_DVBS_ADC_CREST_FACTOR_PROP_CREST_FACTOR_LSB) & Si2183_DVBS_ADC_CREST_FACTOR_PROP_CREST_FACTOR_MASK;
     break;
    #endif /*     Si2183_DVBS_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_DVBS_AFC_RANGE_PROP
     case         Si2183_DVBS_AFC_RANGE_PROP_CODE:
               prop->dvbs_afc_range.range_khz = (data >> Si2183_DVBS_AFC_RANGE_PROP_RANGE_KHZ_LSB) & Si2183_DVBS_AFC_RANGE_PROP_RANGE_KHZ_MASK;
     break;
    #endif /*     Si2183_DVBS_AFC_RANGE_PROP */
    #ifdef        Si2183_DVBS_SYMBOL_RATE_PROP
     case         Si2183_DVBS_SYMBOL_RATE_PROP_CODE:
               prop->dvbs_symbol_rate.rate = (data >> Si2183_DVBS_SYMBOL_RATE_PROP_RATE_LSB) & Si2183_DVBS_SYMBOL_RATE_PROP_RATE_MASK;
     break;
    #endif /*     Si2183_DVBS_SYMBOL_RATE_PROP */
#endif /* DEMOD_DVB_S_S2_DSS */

#ifdef    DEMOD_DVB_T2
    #ifdef        Si2183_DVBT2_ADC_CREST_FACTOR_PROP
     case         Si2183_DVBT2_ADC_CREST_FACTOR_PROP_CODE:
               prop->dvbt2_adc_crest_factor.crest_factor = (data >> Si2183_DVBT2_ADC_CREST_FACTOR_PROP_CREST_FACTOR_LSB) & Si2183_DVBT2_ADC_CREST_FACTOR_PROP_CREST_FACTOR_MASK;
     break;
    #endif /*     Si2183_DVBT2_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_DVBT2_AFC_RANGE_PROP
     case         Si2183_DVBT2_AFC_RANGE_PROP_CODE:
               prop->dvbt2_afc_range.range_khz = (data >> Si2183_DVBT2_AFC_RANGE_PROP_RANGE_KHZ_LSB) & Si2183_DVBT2_AFC_RANGE_PROP_RANGE_KHZ_MASK;
     break;
    #endif /*     Si2183_DVBT2_AFC_RANGE_PROP */
    #ifdef        Si2183_DVBT2_FEF_TUNER_PROP
     case         Si2183_DVBT2_FEF_TUNER_PROP_CODE:
               prop->dvbt2_fef_tuner.tuner_delay         = (data >> Si2183_DVBT2_FEF_TUNER_PROP_TUNER_DELAY_LSB        ) & Si2183_DVBT2_FEF_TUNER_PROP_TUNER_DELAY_MASK;
               prop->dvbt2_fef_tuner.tuner_freeze_time   = (data >> Si2183_DVBT2_FEF_TUNER_PROP_TUNER_FREEZE_TIME_LSB  ) & Si2183_DVBT2_FEF_TUNER_PROP_TUNER_FREEZE_TIME_MASK;
               prop->dvbt2_fef_tuner.tuner_unfreeze_time = (data >> Si2183_DVBT2_FEF_TUNER_PROP_TUNER_UNFREEZE_TIME_LSB) & Si2183_DVBT2_FEF_TUNER_PROP_TUNER_UNFREEZE_TIME_MASK;
     break;
    #endif /*     Si2183_DVBT2_FEF_TUNER_PROP */
    #ifdef        Si2183_DVBT2_MODE_PROP
     case         Si2183_DVBT2_MODE_PROP_CODE:
               prop->dvbt2_mode.lock_mode = (data >> Si2183_DVBT2_MODE_PROP_LOCK_MODE_LSB) & Si2183_DVBT2_MODE_PROP_LOCK_MODE_MASK;
     break;
    #endif /*     Si2183_DVBT2_MODE_PROP */
#endif /* DEMOD_DVB_T2 */

#ifdef    DEMOD_DVB_T
    #ifdef        Si2183_DVBT_ADC_CREST_FACTOR_PROP
     case         Si2183_DVBT_ADC_CREST_FACTOR_PROP_CODE:
               prop->dvbt_adc_crest_factor.crest_factor = (data >> Si2183_DVBT_ADC_CREST_FACTOR_PROP_CREST_FACTOR_LSB) & Si2183_DVBT_ADC_CREST_FACTOR_PROP_CREST_FACTOR_MASK;
     break;
    #endif /*     Si2183_DVBT_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_DVBT_AFC_RANGE_PROP
     case         Si2183_DVBT_AFC_RANGE_PROP_CODE:
               prop->dvbt_afc_range.range_khz = (data >> Si2183_DVBT_AFC_RANGE_PROP_RANGE_KHZ_LSB) & Si2183_DVBT_AFC_RANGE_PROP_RANGE_KHZ_MASK;
     break;
    #endif /*     Si2183_DVBT_AFC_RANGE_PROP */
    #ifdef        Si2183_DVBT_HIERARCHY_PROP
     case         Si2183_DVBT_HIERARCHY_PROP_CODE:
               prop->dvbt_hierarchy.stream = (data >> Si2183_DVBT_HIERARCHY_PROP_STREAM_LSB) & Si2183_DVBT_HIERARCHY_PROP_STREAM_MASK;
     break;
    #endif /*     Si2183_DVBT_HIERARCHY_PROP */
#endif /* DEMOD_DVB_T */

#ifdef    DEMOD_ISDB_T
    #ifdef        Si2183_ISDBT_AC_SELECT_PROP
     case         Si2183_ISDBT_AC_SELECT_PROP_CODE:
               prop->isdbt_ac_select.segment_sel = (data >> Si2183_ISDBT_AC_SELECT_PROP_SEGMENT_SEL_LSB) & Si2183_ISDBT_AC_SELECT_PROP_SEGMENT_SEL_MASK;
               prop->isdbt_ac_select.filtering   = (data >> Si2183_ISDBT_AC_SELECT_PROP_FILTERING_LSB  ) & Si2183_ISDBT_AC_SELECT_PROP_FILTERING_MASK;
     break;
    #endif /*     Si2183_ISDBT_AC_SELECT_PROP */
    #ifdef        Si2183_ISDBT_ADC_CREST_FACTOR_PROP
     case         Si2183_ISDBT_ADC_CREST_FACTOR_PROP_CODE:
               prop->isdbt_adc_crest_factor.crest_factor = (data >> Si2183_ISDBT_ADC_CREST_FACTOR_PROP_CREST_FACTOR_LSB) & Si2183_ISDBT_ADC_CREST_FACTOR_PROP_CREST_FACTOR_MASK;
     break;
    #endif /*     Si2183_ISDBT_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_ISDBT_AFC_RANGE_PROP
     case         Si2183_ISDBT_AFC_RANGE_PROP_CODE:
               prop->isdbt_afc_range.range_khz = (data >> Si2183_ISDBT_AFC_RANGE_PROP_RANGE_KHZ_LSB) & Si2183_ISDBT_AFC_RANGE_PROP_RANGE_KHZ_MASK;
     break;
    #endif /*     Si2183_ISDBT_AFC_RANGE_PROP */
    #ifdef        Si2183_ISDBT_MODE_PROP
     case         Si2183_ISDBT_MODE_PROP_CODE:
               prop->isdbt_mode.layer_mon = (data >> Si2183_ISDBT_MODE_PROP_LAYER_MON_LSB) & Si2183_ISDBT_MODE_PROP_LAYER_MON_MASK;
               prop->isdbt_mode.dl_config = (data >> Si2183_ISDBT_MODE_PROP_DL_CONFIG_LSB) & Si2183_ISDBT_MODE_PROP_DL_CONFIG_MASK;
               prop->isdbt_mode.tradeoff  = (data >> Si2183_ISDBT_MODE_PROP_TRADEOFF_LSB ) & Si2183_ISDBT_MODE_PROP_TRADEOFF_MASK;
     break;
    #endif /*     Si2183_ISDBT_MODE_PROP */
#endif /* DEMOD_ISDB_T */

    #ifdef        Si2183_MASTER_IEN_PROP
     case         Si2183_MASTER_IEN_PROP_CODE:
               prop->master_ien.ddien   = (data >> Si2183_MASTER_IEN_PROP_DDIEN_LSB  ) & Si2183_MASTER_IEN_PROP_DDIEN_MASK;
               prop->master_ien.scanien = (data >> Si2183_MASTER_IEN_PROP_SCANIEN_LSB) & Si2183_MASTER_IEN_PROP_SCANIEN_MASK;
               prop->master_ien.errien  = (data >> Si2183_MASTER_IEN_PROP_ERRIEN_LSB ) & Si2183_MASTER_IEN_PROP_ERRIEN_MASK;
               prop->master_ien.ctsien  = (data >> Si2183_MASTER_IEN_PROP_CTSIEN_LSB ) & Si2183_MASTER_IEN_PROP_CTSIEN_MASK;
     break;
    #endif /*     Si2183_MASTER_IEN_PROP */
#ifdef    DEMOD_MCNS
    #ifdef        Si2183_MCNS_ADC_CREST_FACTOR_PROP
     case         Si2183_MCNS_ADC_CREST_FACTOR_PROP_CODE:
               prop->mcns_adc_crest_factor.crest_factor = (data >> Si2183_MCNS_ADC_CREST_FACTOR_PROP_CREST_FACTOR_LSB) & Si2183_MCNS_ADC_CREST_FACTOR_PROP_CREST_FACTOR_MASK;
     break;
    #endif /*     Si2183_MCNS_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_MCNS_AFC_RANGE_PROP
     case         Si2183_MCNS_AFC_RANGE_PROP_CODE:
               prop->mcns_afc_range.range_khz = (data >> Si2183_MCNS_AFC_RANGE_PROP_RANGE_KHZ_LSB) & Si2183_MCNS_AFC_RANGE_PROP_RANGE_KHZ_MASK;
     break;
    #endif /*     Si2183_MCNS_AFC_RANGE_PROP */
    #ifdef        Si2183_MCNS_CONSTELLATION_PROP
     case         Si2183_MCNS_CONSTELLATION_PROP_CODE:
               prop->mcns_constellation.constellation = (data >> Si2183_MCNS_CONSTELLATION_PROP_CONSTELLATION_LSB) & Si2183_MCNS_CONSTELLATION_PROP_CONSTELLATION_MASK;
     break;
    #endif /*     Si2183_MCNS_CONSTELLATION_PROP */
    #ifdef        Si2183_MCNS_SYMBOL_RATE_PROP
     case         Si2183_MCNS_SYMBOL_RATE_PROP_CODE:
               prop->mcns_symbol_rate.rate = (data >> Si2183_MCNS_SYMBOL_RATE_PROP_RATE_LSB) & Si2183_MCNS_SYMBOL_RATE_PROP_RATE_MASK;
     break;
    #endif /*     Si2183_MCNS_SYMBOL_RATE_PROP */
#endif /* DEMOD_MCNS */

    #ifdef        Si2183_SCAN_FMAX_PROP
     case         Si2183_SCAN_FMAX_PROP_CODE:
               prop->scan_fmax.scan_fmax = (data >> Si2183_SCAN_FMAX_PROP_SCAN_FMAX_LSB) & Si2183_SCAN_FMAX_PROP_SCAN_FMAX_MASK;
     break;
    #endif /*     Si2183_SCAN_FMAX_PROP */
    #ifdef        Si2183_SCAN_FMIN_PROP
     case         Si2183_SCAN_FMIN_PROP_CODE:
               prop->scan_fmin.scan_fmin = (data >> Si2183_SCAN_FMIN_PROP_SCAN_FMIN_LSB) & Si2183_SCAN_FMIN_PROP_SCAN_FMIN_MASK;
     break;
    #endif /*     Si2183_SCAN_FMIN_PROP */
    #ifdef        Si2183_SCAN_IEN_PROP
     case         Si2183_SCAN_IEN_PROP_CODE:
               prop->scan_ien.buzien = (data >> Si2183_SCAN_IEN_PROP_BUZIEN_LSB) & Si2183_SCAN_IEN_PROP_BUZIEN_MASK;
               prop->scan_ien.reqien = (data >> Si2183_SCAN_IEN_PROP_REQIEN_LSB) & Si2183_SCAN_IEN_PROP_REQIEN_MASK;
     break;
    #endif /*     Si2183_SCAN_IEN_PROP */
    #ifdef        Si2183_SCAN_INT_SENSE_PROP
     case         Si2183_SCAN_INT_SENSE_PROP_CODE:
               prop->scan_int_sense.buznegen = (data >> Si2183_SCAN_INT_SENSE_PROP_BUZNEGEN_LSB) & Si2183_SCAN_INT_SENSE_PROP_BUZNEGEN_MASK;
               prop->scan_int_sense.reqnegen = (data >> Si2183_SCAN_INT_SENSE_PROP_REQNEGEN_LSB) & Si2183_SCAN_INT_SENSE_PROP_REQNEGEN_MASK;
               prop->scan_int_sense.buzposen = (data >> Si2183_SCAN_INT_SENSE_PROP_BUZPOSEN_LSB) & Si2183_SCAN_INT_SENSE_PROP_BUZPOSEN_MASK;
               prop->scan_int_sense.reqposen = (data >> Si2183_SCAN_INT_SENSE_PROP_REQPOSEN_LSB) & Si2183_SCAN_INT_SENSE_PROP_REQPOSEN_MASK;
     break;
    #endif /*     Si2183_SCAN_INT_SENSE_PROP */
#ifdef    DEMOD_DVB_S_S2_DSS
    #ifdef        Si2183_SCAN_SAT_CONFIG_PROP
     case         Si2183_SCAN_SAT_CONFIG_PROP_CODE:
               prop->scan_sat_config.analog_detect = (data >> Si2183_SCAN_SAT_CONFIG_PROP_ANALOG_DETECT_LSB) & Si2183_SCAN_SAT_CONFIG_PROP_ANALOG_DETECT_MASK;
               prop->scan_sat_config.reserved1     = (data >> Si2183_SCAN_SAT_CONFIG_PROP_RESERVED1_LSB    ) & Si2183_SCAN_SAT_CONFIG_PROP_RESERVED1_MASK;
               prop->scan_sat_config.reserved2     = (data >> Si2183_SCAN_SAT_CONFIG_PROP_RESERVED2_LSB    ) & Si2183_SCAN_SAT_CONFIG_PROP_RESERVED2_MASK;
     break;
    #endif /*     Si2183_SCAN_SAT_CONFIG_PROP */
    #ifdef        Si2183_SCAN_SAT_UNICABLE_BW_PROP
     case         Si2183_SCAN_SAT_UNICABLE_BW_PROP_CODE:
               prop->scan_sat_unicable_bw.scan_sat_unicable_bw = (data >> Si2183_SCAN_SAT_UNICABLE_BW_PROP_SCAN_SAT_UNICABLE_BW_LSB) & Si2183_SCAN_SAT_UNICABLE_BW_PROP_SCAN_SAT_UNICABLE_BW_MASK;
     break;
    #endif /*     Si2183_SCAN_SAT_UNICABLE_BW_PROP */
    #ifdef        Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP
     case         Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP_CODE:
               prop->scan_sat_unicable_min_tune_step.scan_sat_unicable_min_tune_step = (data >> Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_LSB) & Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_MASK;
     break;
    #endif /*     Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP */
#endif /* DEMOD_DVB_S_S2_DSS */

    #ifdef        Si2183_SCAN_SYMB_RATE_MAX_PROP
     case         Si2183_SCAN_SYMB_RATE_MAX_PROP_CODE:
               prop->scan_symb_rate_max.scan_symb_rate_max = (data >> Si2183_SCAN_SYMB_RATE_MAX_PROP_SCAN_SYMB_RATE_MAX_LSB) & Si2183_SCAN_SYMB_RATE_MAX_PROP_SCAN_SYMB_RATE_MAX_MASK;
     break;
    #endif /*     Si2183_SCAN_SYMB_RATE_MAX_PROP */
    #ifdef        Si2183_SCAN_SYMB_RATE_MIN_PROP
     case         Si2183_SCAN_SYMB_RATE_MIN_PROP_CODE:
               prop->scan_symb_rate_min.scan_symb_rate_min = (data >> Si2183_SCAN_SYMB_RATE_MIN_PROP_SCAN_SYMB_RATE_MIN_LSB) & Si2183_SCAN_SYMB_RATE_MIN_PROP_SCAN_SYMB_RATE_MIN_MASK;
     break;
    #endif /*     Si2183_SCAN_SYMB_RATE_MIN_PROP */
#ifdef    TERRESTRIAL_FRONT_END
    #ifdef        Si2183_SCAN_TER_CONFIG_PROP
     case         Si2183_SCAN_TER_CONFIG_PROP_CODE:
               prop->scan_ter_config.mode          = (data >> Si2183_SCAN_TER_CONFIG_PROP_MODE_LSB         ) & Si2183_SCAN_TER_CONFIG_PROP_MODE_MASK;
               prop->scan_ter_config.analog_bw     = (data >> Si2183_SCAN_TER_CONFIG_PROP_ANALOG_BW_LSB    ) & Si2183_SCAN_TER_CONFIG_PROP_ANALOG_BW_MASK;
               prop->scan_ter_config.search_analog = (data >> Si2183_SCAN_TER_CONFIG_PROP_SEARCH_ANALOG_LSB) & Si2183_SCAN_TER_CONFIG_PROP_SEARCH_ANALOG_MASK;
               prop->scan_ter_config.scan_debug    = (data >> Si2183_SCAN_TER_CONFIG_PROP_SCAN_DEBUG_LSB   ) & Si2183_SCAN_TER_CONFIG_PROP_SCAN_DEBUG_MASK;
     break;
    #endif /*     Si2183_SCAN_TER_CONFIG_PROP */
#endif /* TERRESTRIAL_FRONT_END */

     default : return ERROR_Si2183_UNKNOWN_PROPERTY; break;
    }
    return NO_Si2183_ERROR;
}
/***********************************************************************************************************************
  Si2183_storePropertiesDefaults function
  Use:        property defaults function
              Used to fill the propShadow structure with startup values.
  Parameter: *prop     the Si2183_PropObject structure

 |---------------------------------------------------------------------------------------------------------------------|
 | Do NOT change this code unless you really know what you're doing!                                                   |
 | It should reflect the part internal property settings after firmware download                                       |
 |---------------------------------------------------------------------------------------------------------------------|

 Returns:    void
 ***********************************************************************************************************************/
void          Si2183_storePropertiesDefaults (Si2183_PropObj   *prop) {
#ifdef    Si2183_MASTER_IEN_PROP
  prop->master_ien.ddien                                                 = Si2183_MASTER_IEN_PROP_DDIEN_OFF   ; /* (default 'OFF') */
  prop->master_ien.scanien                                               = Si2183_MASTER_IEN_PROP_SCANIEN_OFF ; /* (default 'OFF') */
  prop->master_ien.errien                                                = Si2183_MASTER_IEN_PROP_ERRIEN_OFF  ; /* (default 'OFF') */
  prop->master_ien.ctsien                                                = Si2183_MASTER_IEN_PROP_CTSIEN_OFF  ; /* (default 'OFF') */
#endif /* Si2183_MASTER_IEN_PROP */

#ifdef    Si2183_DD_BER_RESOL_PROP
  prop->dd_ber_resol.exp                                                 =     7; /* (default     7) */
  prop->dd_ber_resol.mant                                                =     1; /* (default     1) */
#endif /* Si2183_DD_BER_RESOL_PROP */

#ifdef    Si2183_DD_CBER_RESOL_PROP
  prop->dd_cber_resol.exp                                                =     5; /* (default     5) */
  prop->dd_cber_resol.mant                                               =     1; /* (default     1) */
#endif /* Si2183_DD_CBER_RESOL_PROP */

#ifdef    Si2183_DD_DISEQC_FREQ_PROP
  prop->dd_diseqc_freq.freq_hz                                           = 22000; /* (default 22000) */
#endif /* Si2183_DD_DISEQC_FREQ_PROP */

#ifdef    Si2183_DD_DISEQC_PARAM_PROP
  prop->dd_diseqc_param.sequence_mode                                    = Si2183_DD_DISEQC_PARAM_PROP_SEQUENCE_MODE_GAP       ; /* (default 'GAP') */
  prop->dd_diseqc_param.input_pin                                        = Si2183_DD_DISEQC_PARAM_PROP_INPUT_PIN_DISEQC_IN     ; /* (default 'DISEQC_IN') */
#endif /* Si2183_DD_DISEQC_PARAM_PROP */

#ifdef    Si2183_DD_FER_RESOL_PROP
  prop->dd_fer_resol.exp                                                 =     3; /* (default     3) */
  prop->dd_fer_resol.mant                                                =     1; /* (default     1) */
#endif /* Si2183_DD_FER_RESOL_PROP */

#ifdef    Si2183_DD_IEN_PROP
  prop->dd_ien.ien_bit0                                                  = Si2183_DD_IEN_PROP_IEN_BIT0_DISABLE ; /* (default 'DISABLE') */
  prop->dd_ien.ien_bit1                                                  = Si2183_DD_IEN_PROP_IEN_BIT1_DISABLE ; /* (default 'DISABLE') */
  prop->dd_ien.ien_bit2                                                  = Si2183_DD_IEN_PROP_IEN_BIT2_DISABLE ; /* (default 'DISABLE') */
  prop->dd_ien.ien_bit3                                                  = Si2183_DD_IEN_PROP_IEN_BIT3_DISABLE ; /* (default 'DISABLE') */
  prop->dd_ien.ien_bit4                                                  = Si2183_DD_IEN_PROP_IEN_BIT4_DISABLE ; /* (default 'DISABLE') */
  prop->dd_ien.ien_bit5                                                  = Si2183_DD_IEN_PROP_IEN_BIT5_DISABLE ; /* (default 'DISABLE') */
  prop->dd_ien.ien_bit6                                                  = Si2183_DD_IEN_PROP_IEN_BIT6_DISABLE ; /* (default 'DISABLE') */
  prop->dd_ien.ien_bit7                                                  = Si2183_DD_IEN_PROP_IEN_BIT7_DISABLE ; /* (default 'DISABLE') */
#endif /* Si2183_DD_IEN_PROP */

#ifdef    Si2183_DD_IF_INPUT_FREQ_PROP
  prop->dd_if_input_freq.offset                                          =  5000; /* (default  5000) */
#endif /* Si2183_DD_IF_INPUT_FREQ_PROP */

#ifdef    Si2183_DD_INT_SENSE_PROP
  prop->dd_int_sense.neg_bit0                                            = Si2183_DD_INT_SENSE_PROP_NEG_BIT0_DISABLE ; /* (default 'DISABLE') */
  prop->dd_int_sense.neg_bit1                                            = Si2183_DD_INT_SENSE_PROP_NEG_BIT1_DISABLE ; /* (default 'DISABLE') */
  prop->dd_int_sense.neg_bit2                                            = Si2183_DD_INT_SENSE_PROP_NEG_BIT2_DISABLE ; /* (default 'DISABLE') */
  prop->dd_int_sense.neg_bit3                                            = Si2183_DD_INT_SENSE_PROP_NEG_BIT3_DISABLE ; /* (default 'DISABLE') */
  prop->dd_int_sense.neg_bit4                                            = Si2183_DD_INT_SENSE_PROP_NEG_BIT4_DISABLE ; /* (default 'DISABLE') */
  prop->dd_int_sense.neg_bit5                                            = Si2183_DD_INT_SENSE_PROP_NEG_BIT5_DISABLE ; /* (default 'DISABLE') */
  prop->dd_int_sense.neg_bit6                                            = Si2183_DD_INT_SENSE_PROP_NEG_BIT6_DISABLE ; /* (default 'DISABLE') */
  prop->dd_int_sense.neg_bit7                                            = Si2183_DD_INT_SENSE_PROP_NEG_BIT7_DISABLE ; /* (default 'DISABLE') */
  prop->dd_int_sense.pos_bit0                                            = Si2183_DD_INT_SENSE_PROP_POS_BIT0_ENABLE  ; /* (default 'ENABLE') */
  prop->dd_int_sense.pos_bit1                                            = Si2183_DD_INT_SENSE_PROP_POS_BIT1_ENABLE  ; /* (default 'ENABLE') */
  prop->dd_int_sense.pos_bit2                                            = Si2183_DD_INT_SENSE_PROP_POS_BIT2_ENABLE  ; /* (default 'ENABLE') */
  prop->dd_int_sense.pos_bit3                                            = Si2183_DD_INT_SENSE_PROP_POS_BIT3_ENABLE  ; /* (default 'ENABLE') */
  prop->dd_int_sense.pos_bit4                                            = Si2183_DD_INT_SENSE_PROP_POS_BIT4_ENABLE  ; /* (default 'ENABLE') */
  prop->dd_int_sense.pos_bit5                                            = Si2183_DD_INT_SENSE_PROP_POS_BIT5_ENABLE  ; /* (default 'ENABLE') */
  prop->dd_int_sense.pos_bit6                                            = Si2183_DD_INT_SENSE_PROP_POS_BIT6_ENABLE  ; /* (default 'ENABLE') */
  prop->dd_int_sense.pos_bit7                                            = Si2183_DD_INT_SENSE_PROP_POS_BIT7_ENABLE  ; /* (default 'ENABLE') */
#endif /* Si2183_DD_INT_SENSE_PROP */

#ifdef    Si2183_DD_MODE_PROP
  prop->dd_mode.bw                                                       = Si2183_DD_MODE_PROP_BW_BW_8MHZ              ; /* (default 'BW_8MHZ') */
  prop->dd_mode.modulation                                               = Si2183_DD_MODE_PROP_MODULATION_DVBT         ; /* (default 'DVBT') */
  prop->dd_mode.invert_spectrum                                          = Si2183_DD_MODE_PROP_INVERT_SPECTRUM_NORMAL  ; /* (default 'NORMAL') */
  prop->dd_mode.auto_detect                                              = Si2183_DD_MODE_PROP_AUTO_DETECT_NONE        ; /* (default 'NONE') */
#endif /* Si2183_DD_MODE_PROP */

#ifdef    Si2183_DD_PER_RESOL_PROP
  prop->dd_per_resol.exp                                                 =     5; /* (default     5) */
  prop->dd_per_resol.mant                                                =     1; /* (default     1) */
#endif /* Si2183_DD_PER_RESOL_PROP */

#ifdef    Si2183_DD_RSQ_BER_THRESHOLD_PROP
  prop->dd_rsq_ber_threshold.exp                                         =     1; /* (default     1) */
  prop->dd_rsq_ber_threshold.mant                                        =    10; /* (default    10) */
#endif /* Si2183_DD_RSQ_BER_THRESHOLD_PROP */

#ifdef    Si2183_DD_SEC_TS_SERIAL_DIFF_PROP
  prop->dd_sec_ts_serial_diff.ts_data1_strength                          =    15; /* (default    15) */
  prop->dd_sec_ts_serial_diff.ts_data1_shape                             =     3; /* (default     3) */
  prop->dd_sec_ts_serial_diff.ts_data2_strength                          =    15; /* (default    15) */
  prop->dd_sec_ts_serial_diff.ts_data2_shape                             =     3; /* (default     3) */
  prop->dd_sec_ts_serial_diff.ts_clkb_on_data1                           = Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_CLKB_ON_DATA1_DISABLE   ; /* (default 'DISABLE') */
  prop->dd_sec_ts_serial_diff.ts_data0b_on_data2                         = Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_TS_DATA0B_ON_DATA2_DISABLE ; /* (default 'DISABLE') */
#endif /* Si2183_DD_SEC_TS_SERIAL_DIFF_PROP */

#ifdef    Si2183_DD_SEC_TS_SETUP_PAR_PROP
  prop->dd_sec_ts_setup_par.ts_data_strength                             =     3; /* (default     3) */
  prop->dd_sec_ts_setup_par.ts_data_shape                                =     1; /* (default     1) */
  prop->dd_sec_ts_setup_par.ts_clk_strength                              =     3; /* (default     3) */
  prop->dd_sec_ts_setup_par.ts_clk_shape                                 =     1; /* (default     1) */
#endif /* Si2183_DD_SEC_TS_SETUP_PAR_PROP */

#ifdef    Si2183_DD_SEC_TS_SETUP_SER_PROP
  prop->dd_sec_ts_setup_ser.ts_data_strength                             =     3; /* (default     3) */
  prop->dd_sec_ts_setup_ser.ts_data_shape                                =     3; /* (default     3) */
  prop->dd_sec_ts_setup_ser.ts_clk_strength                              =    15; /* (default    15) */
  prop->dd_sec_ts_setup_ser.ts_clk_shape                                 =     3; /* (default     3) */
#endif /* Si2183_DD_SEC_TS_SETUP_SER_PROP */

#ifdef    Si2183_DD_SEC_TS_SLR_SERIAL_PROP
  prop->dd_sec_ts_slr_serial.ts_data_slr                                 =     0; /* (default     0) */
  prop->dd_sec_ts_slr_serial.ts_data_slr_on                              = Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA_SLR_ON_DISABLE  ; /* (default 'DISABLE') */
  prop->dd_sec_ts_slr_serial.ts_data1_slr                                =     0; /* (default     0) */
  prop->dd_sec_ts_slr_serial.ts_data1_slr_on                             = Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA1_SLR_ON_DISABLE ; /* (default 'DISABLE') */
  prop->dd_sec_ts_slr_serial.ts_data2_slr                                =     0; /* (default     0) */
  prop->dd_sec_ts_slr_serial.ts_data2_slr_on                             = Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_DATA2_SLR_ON_DISABLE ; /* (default 'DISABLE') */
  prop->dd_sec_ts_slr_serial.ts_clk_slr                                  =     0; /* (default     0) */
  prop->dd_sec_ts_slr_serial.ts_clk_slr_on                               = Si2183_DD_SEC_TS_SLR_SERIAL_PROP_TS_CLK_SLR_ON_DISABLE   ; /* (default 'DISABLE') */
#endif /* Si2183_DD_SEC_TS_SLR_SERIAL_PROP */

#ifdef    Si2183_DD_SSI_SQI_PARAM_PROP
  prop->dd_ssi_sqi_param.sqi_average                                     =     1; /* (default     1) */
#endif /* Si2183_DD_SSI_SQI_PARAM_PROP */

#ifdef    Si2183_DD_TS_FREQ_PROP
  prop->dd_ts_freq.req_freq_10khz                                        =   720; /* (default   720) */
#endif /* Si2183_DD_TS_FREQ_PROP */

#ifdef    Si2183_DD_TS_FREQ_MAX_PROP
  prop->dd_ts_freq_max.req_freq_max_10khz                                = 14600; /* (default 14600) */
#endif /* Si2183_DD_TS_FREQ_MAX_PROP */

#ifdef    Si2183_DD_TS_MODE_PROP
  prop->dd_ts_mode.mode                                                  = Si2183_DD_TS_MODE_PROP_MODE_TRISTATE                   ; /* (default 'TRISTATE') */
  prop->dd_ts_mode.clock                                                 = Si2183_DD_TS_MODE_PROP_CLOCK_AUTO_FIXED                ; /* (default 'AUTO_FIXED') */
  prop->dd_ts_mode.clk_gapped_en                                         = Si2183_DD_TS_MODE_PROP_CLK_GAPPED_EN_DISABLED          ; /* (default 'DISABLED') */
  prop->dd_ts_mode.ts_err_polarity                                       = Si2183_DD_TS_MODE_PROP_TS_ERR_POLARITY_NOT_INVERTED    ; /* (default 'NOT_INVERTED') */
  prop->dd_ts_mode.special                                               = Si2183_DD_TS_MODE_PROP_SPECIAL_FULL_TS                 ; /* (default 'FULL_TS') */
  prop->dd_ts_mode.ts_freq_resolution                                    = Si2183_DD_TS_MODE_PROP_TS_FREQ_RESOLUTION_NORMAL       ; /* (default 'NORMAL') */
  prop->dd_ts_mode.serial_pin_selection                                  = Si2183_DD_TS_MODE_PROP_SERIAL_PIN_SELECTION_D0           ; /* (default 'D0') */
#endif /* Si2183_DD_TS_MODE_PROP */

#ifdef    Si2183_DD_TS_SERIAL_DIFF_PROP
  prop->dd_ts_serial_diff.ts_data1_strength                              =    15; /* (default    15) */
  prop->dd_ts_serial_diff.ts_data1_shape                                 =     3; /* (default     3) */
  prop->dd_ts_serial_diff.ts_data2_strength                              =    15; /* (default    15) */
  prop->dd_ts_serial_diff.ts_data2_shape                                 =     3; /* (default     3) */
  prop->dd_ts_serial_diff.ts_clkb_on_data1                               = Si2183_DD_TS_SERIAL_DIFF_PROP_TS_CLKB_ON_DATA1_DISABLE   ; /* (default 'DISABLE') */
  prop->dd_ts_serial_diff.ts_data0b_on_data2                             = Si2183_DD_TS_SERIAL_DIFF_PROP_TS_DATA0B_ON_DATA2_DISABLE ; /* (default 'DISABLE') */
#endif /* Si2183_DD_TS_SERIAL_DIFF_PROP */

#ifdef    Si2183_DD_TS_SETUP_PAR_PROP
  prop->dd_ts_setup_par.ts_data_strength                                 =     3; /* (default     3) */
  prop->dd_ts_setup_par.ts_data_shape                                    =     1; /* (default     1) */
  prop->dd_ts_setup_par.ts_clk_strength                                  =     3; /* (default     3) */
  prop->dd_ts_setup_par.ts_clk_shape                                     =     1; /* (default     1) */
  prop->dd_ts_setup_par.ts_clk_invert                                    = Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_INVERT_INVERTED    ; /* (default 'INVERTED') */
  prop->dd_ts_setup_par.ts_clk_shift                                     =     0; /* (default     0) */
#endif /* Si2183_DD_TS_SETUP_PAR_PROP */

#ifdef    Si2183_DD_TS_SETUP_SER_PROP
  prop->dd_ts_setup_ser.ts_data_strength                                 =    15; /* (default    15) */
  prop->dd_ts_setup_ser.ts_data_shape                                    =     3; /* (default     3) */
  prop->dd_ts_setup_ser.ts_clk_strength                                  =    15; /* (default    15) */
  prop->dd_ts_setup_ser.ts_clk_shape                                     =     3; /* (default     3) */
  prop->dd_ts_setup_ser.ts_clk_invert                                    = Si2183_DD_TS_SETUP_SER_PROP_TS_CLK_INVERT_INVERTED      ; /* (default 'INVERTED') */
  prop->dd_ts_setup_ser.ts_sync_duration                                 = Si2183_DD_TS_SETUP_SER_PROP_TS_SYNC_DURATION_FIRST_BYTE ; /* (default 'FIRST_BYTE') */
  prop->dd_ts_setup_ser.ts_byte_order                                    = Si2183_DD_TS_SETUP_SER_PROP_TS_BYTE_ORDER_MSB_FIRST     ; /* (default 'MSB_FIRST') */
#endif /* Si2183_DD_TS_SETUP_SER_PROP */

#ifdef    Si2183_DD_TS_SLR_SERIAL_PROP
  prop->dd_ts_slr_serial.ts_data_slr                                     =     0; /* (default     0) */
  prop->dd_ts_slr_serial.ts_data_slr_on                                  = Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA_SLR_ON_DISABLE  ; /* (default 'DISABLE') */
  prop->dd_ts_slr_serial.ts_data1_slr                                    =     0; /* (default     0) */
  prop->dd_ts_slr_serial.ts_data1_slr_on                                 = Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA1_SLR_ON_DISABLE ; /* (default 'DISABLE') */
  prop->dd_ts_slr_serial.ts_data2_slr                                    =     0; /* (default     0) */
  prop->dd_ts_slr_serial.ts_data2_slr_on                                 = Si2183_DD_TS_SLR_SERIAL_PROP_TS_DATA2_SLR_ON_DISABLE ; /* (default 'DISABLE') */
  prop->dd_ts_slr_serial.ts_clk_slr                                      =     0; /* (default     0) */
  prop->dd_ts_slr_serial.ts_clk_slr_on                                   = Si2183_DD_TS_SLR_SERIAL_PROP_TS_CLK_SLR_ON_DISABLE   ; /* (default 'DISABLE') */
#endif /* Si2183_DD_TS_SLR_SERIAL_PROP */

#ifdef    DEMOD_DVB_C
#ifdef    Si2183_DVBC_ADC_CREST_FACTOR_PROP
  prop->dvbc_adc_crest_factor.crest_factor                               =   112; /* (default   112) */
#endif /* Si2183_DVBC_ADC_CREST_FACTOR_PROP */

#ifdef    Si2183_DVBC_AFC_RANGE_PROP
  prop->dvbc_afc_range.range_khz                                         =   100; /* (default   100) */
#endif /* Si2183_DVBC_AFC_RANGE_PROP */

#ifdef    Si2183_DVBC_CONSTELLATION_PROP
  prop->dvbc_constellation.constellation                                 = Si2183_DVBC_CONSTELLATION_PROP_CONSTELLATION_AUTO ; /* (default 'AUTO') */
#endif /* Si2183_DVBC_CONSTELLATION_PROP */

#ifdef    Si2183_DVBC_SYMBOL_RATE_PROP
  prop->dvbc_symbol_rate.rate                                            =  6900; /* (default  6900) */
#endif /* Si2183_DVBC_SYMBOL_RATE_PROP */

#endif /* DEMOD_DVB_C */

#ifdef    DEMOD_DVB_C2
#ifdef    Si2183_DVBC2_ADC_CREST_FACTOR_PROP
  prop->dvbc2_adc_crest_factor.crest_factor                              =   130; /* (default   130) */
#endif /* Si2183_DVBC2_ADC_CREST_FACTOR_PROP */

#ifdef    Si2183_DVBC2_AFC_RANGE_PROP
  prop->dvbc2_afc_range.range_khz                                        =   550; /* (default   550) */
#endif /* Si2183_DVBC2_AFC_RANGE_PROP */

#endif /* DEMOD_DVB_C2 */

#ifdef    DEMOD_DVB_S_S2_DSS
#ifdef    Si2183_DVBS_ADC_CREST_FACTOR_PROP
  prop->dvbs_adc_crest_factor.crest_factor                               =   104; /* (default   104) */
#endif /* Si2183_DVBS_ADC_CREST_FACTOR_PROP */

#ifdef    Si2183_DVBS_AFC_RANGE_PROP
  prop->dvbs_afc_range.range_khz                                         =  4000; /* (default  4000) */
#endif /* Si2183_DVBS_AFC_RANGE_PROP */

#ifdef    Si2183_DVBS_SYMBOL_RATE_PROP
  prop->dvbs_symbol_rate.rate                                            = 27500; /* (default 27500) */
#endif /* Si2183_DVBS_SYMBOL_RATE_PROP */

#ifdef    Si2183_DVBS2_ADC_CREST_FACTOR_PROP
  prop->dvbs2_adc_crest_factor.crest_factor                              =   104; /* (default   104) */
#endif /* Si2183_DVBS2_ADC_CREST_FACTOR_PROP */

#ifdef    Si2183_DVBS2_AFC_RANGE_PROP
  prop->dvbs2_afc_range.range_khz                                        =  4000; /* (default  4000) */
#endif /* Si2183_DVBS2_AFC_RANGE_PROP */

#ifdef    Si2183_DVBS2_SYMBOL_RATE_PROP
  prop->dvbs2_symbol_rate.rate                                           = 27500; /* (default 27500) */
#endif /* Si2183_DVBS2_SYMBOL_RATE_PROP */

#endif /* DEMOD_DVB_S_S2_DSS */

#ifdef    DEMOD_DVB_T
#ifdef    Si2183_DVBT_ADC_CREST_FACTOR_PROP
  prop->dvbt_adc_crest_factor.crest_factor                               =   130; /* (default   130) */
#endif /* Si2183_DVBT_ADC_CREST_FACTOR_PROP */

#ifdef    Si2183_DVBT_AFC_RANGE_PROP
  prop->dvbt_afc_range.range_khz                                         =   550; /* (default   550) */
#endif /* Si2183_DVBT_AFC_RANGE_PROP */

#ifdef    Si2183_DVBT_HIERARCHY_PROP
  prop->dvbt_hierarchy.stream                                            = Si2183_DVBT_HIERARCHY_PROP_STREAM_HP ; /* (default 'HP') */
#endif /* Si2183_DVBT_HIERARCHY_PROP */

#endif /* DEMOD_DVB_T */

#ifdef    DEMOD_DVB_T2
#ifdef    Si2183_DVBT2_ADC_CREST_FACTOR_PROP
  prop->dvbt2_adc_crest_factor.crest_factor                              =   130; /* (default   130) */
#endif /* Si2183_DVBT2_ADC_CREST_FACTOR_PROP */

#ifdef    Si2183_DVBT2_AFC_RANGE_PROP
  prop->dvbt2_afc_range.range_khz                                        =   550; /* (default   550) */
#endif /* Si2183_DVBT2_AFC_RANGE_PROP */

#ifdef    Si2183_DVBT2_FEF_TUNER_PROP
  prop->dvbt2_fef_tuner.tuner_delay                                      =     1; /* (default     1) */
  prop->dvbt2_fef_tuner.tuner_freeze_time                                =     1; /* (default     1) */
  prop->dvbt2_fef_tuner.tuner_unfreeze_time                              =     1; /* (default     1) */
#endif /* Si2183_DVBT2_FEF_TUNER_PROP */

#ifdef    Si2183_DVBT2_MODE_PROP
  prop->dvbt2_mode.lock_mode                                             = Si2183_DVBT2_MODE_PROP_LOCK_MODE_ANY ; /* (default 'ANY') */
#endif /* Si2183_DVBT2_MODE_PROP */

#endif /* DEMOD_DVB_T2 */

#ifdef    DEMOD_ISDB_T
#ifdef    Si2183_ISDBT_AC_SELECT_PROP
  prop->isdbt_ac_select.segment_sel                                      = Si2183_ISDBT_AC_SELECT_PROP_SEGMENT_SEL_SEG_0 ; /* (default 'SEG_0') */
  prop->isdbt_ac_select.filtering                                        = Si2183_ISDBT_AC_SELECT_PROP_FILTERING_KEEP_ALL   ; /* (default 'KEEP_ALL') */
#endif /* Si2183_ISDBT_AC_SELECT_PROP */

#ifdef    Si2183_ISDBT_ADC_CREST_FACTOR_PROP
  prop->isdbt_adc_crest_factor.crest_factor                              =   130; /* (default   130) */
#endif /* Si2183_ISDBT_ADC_CREST_FACTOR_PROP */

#ifdef    Si2183_ISDBT_AFC_RANGE_PROP
  prop->isdbt_afc_range.range_khz                                        =   550; /* (default   550) */
#endif /* Si2183_ISDBT_AFC_RANGE_PROP */

#ifdef    Si2183_ISDBT_MODE_PROP
  prop->isdbt_mode.layer_mon                                             = Si2183_ISDBT_MODE_PROP_LAYER_MON_ALL ; /* (default 'ALL') */
  prop->isdbt_mode.dl_config                                             = Si2183_ISDBT_MODE_PROP_DL_CONFIG_ALL_LOCKED ; /* (default 'ALL_LOCKED') */
  prop->isdbt_mode.tradeoff                                              = Si2183_ISDBT_MODE_PROP_TRADEOFF_OPTIMAL_PERFORMANCE  ; /* (default 'OPTIMAL_PERFORMANCE') */
#endif /* Si2183_ISDBT_MODE_PROP */

#endif /* DEMOD_ISDB_T */

#ifdef    DEMOD_MCNS
#ifdef    Si2183_MCNS_ADC_CREST_FACTOR_PROP
  prop->mcns_adc_crest_factor.crest_factor                               =   112; /* (default   112) */
#endif /* Si2183_MCNS_ADC_CREST_FACTOR_PROP */

#ifdef    Si2183_MCNS_AFC_RANGE_PROP
  prop->mcns_afc_range.range_khz                                         =   100; /* (default   100) */
#endif /* Si2183_MCNS_AFC_RANGE_PROP */

#ifdef    Si2183_MCNS_CONSTELLATION_PROP
  prop->mcns_constellation.constellation                                 = Si2183_MCNS_CONSTELLATION_PROP_CONSTELLATION_AUTO ; /* (default 'AUTO') */
#endif /* Si2183_MCNS_CONSTELLATION_PROP */

#ifdef    Si2183_MCNS_SYMBOL_RATE_PROP
  prop->mcns_symbol_rate.rate                                            =  5361; /* (default  5361) */
#endif /* Si2183_MCNS_SYMBOL_RATE_PROP */

#endif /* DEMOD_MCNS */

#ifdef    Si2183_SCAN_FMAX_PROP
  prop->scan_fmax.scan_fmax                                              =     0; /* (default     0) */
#endif /* Si2183_SCAN_FMAX_PROP */

#ifdef    Si2183_SCAN_FMIN_PROP
  prop->scan_fmin.scan_fmin                                              =     0; /* (default     0) */
#endif /* Si2183_SCAN_FMIN_PROP */

#ifdef    Si2183_SCAN_IEN_PROP
  prop->scan_ien.buzien                                                  = Si2183_SCAN_IEN_PROP_BUZIEN_DISABLE ; /* (default 'DISABLE') */
  prop->scan_ien.reqien                                                  = Si2183_SCAN_IEN_PROP_REQIEN_DISABLE ; /* (default 'DISABLE') */
#endif /* Si2183_SCAN_IEN_PROP */

#ifdef    Si2183_SCAN_INT_SENSE_PROP
  prop->scan_int_sense.buznegen                                          = Si2183_SCAN_INT_SENSE_PROP_BUZNEGEN_ENABLE  ; /* (default 'ENABLE') */
  prop->scan_int_sense.reqnegen                                          = Si2183_SCAN_INT_SENSE_PROP_REQNEGEN_DISABLE ; /* (default 'DISABLE') */
  prop->scan_int_sense.buzposen                                          = Si2183_SCAN_INT_SENSE_PROP_BUZPOSEN_DISABLE ; /* (default 'DISABLE') */
  prop->scan_int_sense.reqposen                                          = Si2183_SCAN_INT_SENSE_PROP_REQPOSEN_ENABLE  ; /* (default 'ENABLE') */
#endif /* Si2183_SCAN_INT_SENSE_PROP */

#ifdef    Si2183_SCAN_SAT_CONFIG_PROP
  prop->scan_sat_config.analog_detect                                    = Si2183_SCAN_SAT_CONFIG_PROP_ANALOG_DETECT_DISABLED ; /* (default 'DISABLED') */
  prop->scan_sat_config.reserved1                                        =     0; /* (default     0) */
  prop->scan_sat_config.reserved2                                        =    12; /* (default    12) */
#endif /* Si2183_SCAN_SAT_CONFIG_PROP */

#ifdef    Si2183_SCAN_SAT_UNICABLE_BW_PROP
  prop->scan_sat_unicable_bw.scan_sat_unicable_bw                        =     0; /* (default     0) */
#endif /* Si2183_SCAN_SAT_UNICABLE_BW_PROP */

#ifdef    Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP
  prop->scan_sat_unicable_min_tune_step.scan_sat_unicable_min_tune_step  =    50; /* (default    50) */
#endif /* Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP */

#ifdef    Si2183_SCAN_SYMB_RATE_MAX_PROP
  prop->scan_symb_rate_max.scan_symb_rate_max                            =     0; /* (default     0) */
#endif /* Si2183_SCAN_SYMB_RATE_MAX_PROP */

#ifdef    Si2183_SCAN_SYMB_RATE_MIN_PROP
  prop->scan_symb_rate_min.scan_symb_rate_min                            =     0; /* (default     0) */
#endif /* Si2183_SCAN_SYMB_RATE_MIN_PROP */

#ifdef    TERRESTRIAL_FRONT_END
#ifdef    Si2183_SCAN_TER_CONFIG_PROP
  prop->scan_ter_config.mode                                             = Si2183_SCAN_TER_CONFIG_PROP_MODE_MAPPING_SCAN        ; /* (default 'BLIND_SCAN') */
  prop->scan_ter_config.analog_bw                                        = Si2183_SCAN_TER_CONFIG_PROP_ANALOG_BW_8MHZ           ; /* (default '8MHZ') */
  prop->scan_ter_config.search_analog                                    = Si2183_SCAN_TER_CONFIG_PROP_SEARCH_ANALOG_DISABLE    ; /* (default 'DISABLE') */
#endif /* Si2183_SCAN_TER_CONFIG_PROP */
#endif /* TERRESTRIAL_FRONT_END */
}
#ifdef    Si2183_GET_PROPERTY_STRING
/***********************************************************************************************************************
  Si2183_L1_PropertyText function
  Use:        property text function
              Used to turn the property data into clear text.
  Parameter: *prop     the Si2183 property structure (containing all properties)
  Parameter: prop_code the property Id (used to know which property to use)
  Parameter: separator the string to use between fields (often either a blank or a newline character)
  Parameter: msg       the string used to store the resulting string
                       It must be declared by the caller with a size of 1000 bytes
  Returns:    NO_Si2183_ERROR if successful.
 ***********************************************************************************************************************/
unsigned char Si2183_L1_PropertyText          (Si2183_PropObj   *prop, unsigned int prop_code, const char *separator, char *msg) {
    switch (prop_code) {
    #ifdef        Si2183_DD_BER_RESOL_PROP
     case         Si2183_DD_BER_RESOL_PROP_CODE:
      snprintf(msg,1000,"DD_BER_RESOL");
       strncat(msg,separator,1000); strncat(msg,"-EXP ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ber_resol.exp);
       strncat(msg,separator,1000); strncat(msg,"-MANT ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ber_resol.mant);
     break;
    #endif /*     Si2183_DD_BER_RESOL_PROP */
    #ifdef        Si2183_DD_CBER_RESOL_PROP
     case         Si2183_DD_CBER_RESOL_PROP_CODE:
      snprintf(msg,1000,"DD_CBER_RESOL");
       strncat(msg,separator,1000); strncat(msg,"-EXP " ,1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_cber_resol.exp);
       strncat(msg,separator,1000); strncat(msg,"-MANT ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_cber_resol.mant);
     break;
    #endif /*     Si2183_DD_CBER_RESOL_PROP */
#ifdef    DEMOD_DVB_S_S2_DSS
    #ifdef        Si2183_DD_DISEQC_FREQ_PROP
     case         Si2183_DD_DISEQC_FREQ_PROP_CODE:
      snprintf(msg,1000,"DD_DISEQC_FREQ");
       strncat(msg,separator,1000); strncat(msg,"-FREQ_HZ ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_diseqc_freq.freq_hz);
     break;
    #endif /*     Si2183_DD_DISEQC_FREQ_PROP */
    #ifdef        Si2183_DD_DISEQC_PARAM_PROP
     case         Si2183_DD_DISEQC_PARAM_PROP_CODE:
      snprintf(msg,1000,"DD_DISEQC_PARAM");
       strncat(msg,separator,1000); strncat(msg,"-SEQUENCE_MODE ",1000);
           if  (prop->dd_diseqc_param.sequence_mode ==     0) strncat(msg,"GAP    ",1000);
      else if  (prop->dd_diseqc_param.sequence_mode ==     1) strncat(msg,"NO_GAP ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_diseqc_param.sequence_mode);
       strncat(msg,separator,1000); strncat(msg,"-INPUT_PIN ",1000);
           if  (prop->dd_diseqc_param.input_pin     ==     0) strncat(msg,"DISEQC_IN  ",1000);
      else if  (prop->dd_diseqc_param.input_pin     ==     1) strncat(msg,"DISEQC_CMD ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_diseqc_param.input_pin);
     break;
    #endif /*     Si2183_DD_DISEQC_PARAM_PROP */
#endif /* DEMOD_DVB_S_S2_DSS */

    #ifdef        Si2183_DD_FER_RESOL_PROP
     case         Si2183_DD_FER_RESOL_PROP_CODE:
      snprintf(msg,1000,"DD_FER_RESOL");
       strncat(msg,separator,1000); strncat(msg,"-EXP ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_fer_resol.exp);
       strncat(msg,separator,1000); strncat(msg,"-MANT ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_fer_resol.mant);
     break;
    #endif /*     Si2183_DD_FER_RESOL_PROP */
    #ifdef        Si2183_DD_IEN_PROP
     case         Si2183_DD_IEN_PROP_CODE:
      snprintf(msg,1000,"DD_IEN");
       strncat(msg,separator,1000); strncat(msg,"-IEN_BIT0 ",1000);
           if  (prop->dd_ien.ien_bit0 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_ien.ien_bit0 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                     STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ien.ien_bit0);
       strncat(msg,separator,1000); strncat(msg,"-IEN_BIT1 ",1000);
           if  (prop->dd_ien.ien_bit1 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_ien.ien_bit1 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                     STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ien.ien_bit1);
       strncat(msg,separator,1000); strncat(msg,"-IEN_BIT2 ",1000);
           if  (prop->dd_ien.ien_bit2 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_ien.ien_bit2 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                     STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ien.ien_bit2);
       strncat(msg,separator,1000); strncat(msg,"-IEN_BIT3 ",1000);
           if  (prop->dd_ien.ien_bit3 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_ien.ien_bit3 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                     STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ien.ien_bit3);
       strncat(msg,separator,1000); strncat(msg,"-IEN_BIT4 ",1000);
           if  (prop->dd_ien.ien_bit4 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_ien.ien_bit4 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                     STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ien.ien_bit4);
       strncat(msg,separator,1000); strncat(msg,"-IEN_BIT5 ",1000);
           if  (prop->dd_ien.ien_bit5 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_ien.ien_bit5 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                     STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ien.ien_bit5);
       strncat(msg,separator,1000); strncat(msg,"-IEN_BIT6 ",1000);
           if  (prop->dd_ien.ien_bit6 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_ien.ien_bit6 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                     STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ien.ien_bit6);
       strncat(msg,separator,1000); strncat(msg,"-IEN_BIT7 ",1000);
           if  (prop->dd_ien.ien_bit7 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_ien.ien_bit7 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                     STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ien.ien_bit7);
     break;
    #endif /*     Si2183_DD_IEN_PROP */
    #ifdef        Si2183_DD_IF_INPUT_FREQ_PROP
     case         Si2183_DD_IF_INPUT_FREQ_PROP_CODE:
      snprintf(msg,1000,"DD_IF_INPUT_FREQ");
       strncat(msg,separator,1000); strncat(msg,"-OFFSET ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_if_input_freq.offset);
     break;
    #endif /*     Si2183_DD_IF_INPUT_FREQ_PROP */
    #ifdef        Si2183_DD_INT_SENSE_PROP
     case         Si2183_DD_INT_SENSE_PROP_CODE:
      snprintf(msg,1000,"DD_INT_SENSE");
       strncat(msg,separator,1000); strncat(msg,"-NEG_BIT0 ",1000);
           if  (prop->dd_int_sense.neg_bit0 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_int_sense.neg_bit0 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                           STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_int_sense.neg_bit0);
       strncat(msg,separator,1000); strncat(msg,"-NEG_BIT1 ",1000);
           if  (prop->dd_int_sense.neg_bit1 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_int_sense.neg_bit1 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                           STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_int_sense.neg_bit1);
       strncat(msg,separator,1000); strncat(msg,"-NEG_BIT2 ",1000);
           if  (prop->dd_int_sense.neg_bit2 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_int_sense.neg_bit2 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                           STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_int_sense.neg_bit2);
       strncat(msg,separator,1000); strncat(msg,"-NEG_BIT3 ",1000);
           if  (prop->dd_int_sense.neg_bit3 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_int_sense.neg_bit3 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                           STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_int_sense.neg_bit3);
       strncat(msg,separator,1000); strncat(msg,"-NEG_BIT4 ",1000);
           if  (prop->dd_int_sense.neg_bit4 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_int_sense.neg_bit4 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                           STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_int_sense.neg_bit4);
       strncat(msg,separator,1000); strncat(msg,"-NEG_BIT5 ",1000);
           if  (prop->dd_int_sense.neg_bit5 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_int_sense.neg_bit5 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                           STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_int_sense.neg_bit5);
       strncat(msg,separator,1000); strncat(msg,"-NEG_BIT6 ",1000);
           if  (prop->dd_int_sense.neg_bit6 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_int_sense.neg_bit6 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                           STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_int_sense.neg_bit6);
       strncat(msg,separator,1000); strncat(msg,"-NEG_BIT7 ",1000);
           if  (prop->dd_int_sense.neg_bit7 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_int_sense.neg_bit7 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                           STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_int_sense.neg_bit7);
       strncat(msg,separator,1000); strncat(msg,"-POS_BIT0 ",1000);
           if  (prop->dd_int_sense.pos_bit0 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_int_sense.pos_bit0 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                           STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_int_sense.pos_bit0);
       strncat(msg,separator,1000); strncat(msg,"-POS_BIT1 ",1000);
           if  (prop->dd_int_sense.pos_bit1 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_int_sense.pos_bit1 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                           STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_int_sense.pos_bit1);
       strncat(msg,separator,1000); strncat(msg,"-POS_BIT2 ",1000);
           if  (prop->dd_int_sense.pos_bit2 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_int_sense.pos_bit2 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                           STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_int_sense.pos_bit2);
       strncat(msg,separator,1000); strncat(msg,"-POS_BIT3 ",1000);
           if  (prop->dd_int_sense.pos_bit3 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_int_sense.pos_bit3 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                           STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_int_sense.pos_bit3);
       strncat(msg,separator,1000); strncat(msg,"-POS_BIT4 ",1000);
           if  (prop->dd_int_sense.pos_bit4 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_int_sense.pos_bit4 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                           STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_int_sense.pos_bit4);
       strncat(msg,separator,1000); strncat(msg,"-POS_BIT5 ",1000);
           if  (prop->dd_int_sense.pos_bit5 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_int_sense.pos_bit5 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                           STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_int_sense.pos_bit5);
       strncat(msg,separator,1000); strncat(msg,"-POS_BIT6 ",1000);
           if  (prop->dd_int_sense.pos_bit6 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_int_sense.pos_bit6 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                           STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_int_sense.pos_bit6);
       strncat(msg,separator,1000); strncat(msg,"-POS_BIT7 ",1000);
           if  (prop->dd_int_sense.pos_bit7 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_int_sense.pos_bit7 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                           STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_int_sense.pos_bit7);
     break;
    #endif /*     Si2183_DD_INT_SENSE_PROP */
    #ifdef        Si2183_DD_MODE_PROP
     case         Si2183_DD_MODE_PROP_CODE:
      snprintf(msg,1000,"DD_MODE");
       strncat(msg,separator,1000); strncat(msg,"-BW ",1000);
           if  (prop->dd_mode.bw              ==     5) strncat(msg,"BW_5MHZ   ",1000);
      else if  (prop->dd_mode.bw              ==     6) strncat(msg,"BW_6MHZ   ",1000);
      else if  (prop->dd_mode.bw              ==     7) strncat(msg,"BW_7MHZ   ",1000);
      else if  (prop->dd_mode.bw              ==     8) strncat(msg,"BW_8MHZ   ",1000);
      else if  (prop->dd_mode.bw              ==     2) strncat(msg,"BW_1D7MHZ ",1000);
      else                                             STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_mode.bw);
       strncat(msg,separator,1000); strncat(msg,"-MODULATION ",1000);
           if  (prop->dd_mode.modulation      ==     1) strncat(msg,"MCNS        ",1000);
      else if  (prop->dd_mode.modulation      ==     2) strncat(msg,"DVBT        ",1000);
      else if  (prop->dd_mode.modulation      ==     3) strncat(msg,"DVBC        ",1000);
      else if  (prop->dd_mode.modulation      ==     4) strncat(msg,"ISDBT       ",1000);
      else if  (prop->dd_mode.modulation      ==     7) strncat(msg,"DVBT2       ",1000);
      else if  (prop->dd_mode.modulation      ==     8) strncat(msg,"DVBS        ",1000);
      else if  (prop->dd_mode.modulation      ==     9) strncat(msg,"DVBS2       ",1000);
      else if  (prop->dd_mode.modulation      ==    10) strncat(msg,"DSS         ",1000);
      else if  (prop->dd_mode.modulation      ==    11) strncat(msg,"DVBC2       ",1000);
      else if  (prop->dd_mode.modulation      ==    15) strncat(msg,"AUTO_DETECT ",1000);
      else                                             STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_mode.modulation);
       strncat(msg,separator,1000); strncat(msg,"-INVERT_SPECTRUM ",1000);
           if  (prop->dd_mode.invert_spectrum ==     0) strncat(msg,"NORMAL   ",1000);
      else if  (prop->dd_mode.invert_spectrum ==     1) strncat(msg,"INVERTED ",1000);
      else                                             STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_mode.invert_spectrum);
       strncat(msg,separator,1000); strncat(msg,"-AUTO_DETECT ",1000);
           if  (prop->dd_mode.auto_detect     ==     0) strncat(msg,"NONE              ",1000);
      else if  (prop->dd_mode.auto_detect     ==     1) strncat(msg,"AUTO_DVB_T_T2     ",1000);
      else if  (prop->dd_mode.auto_detect     ==     2) strncat(msg,"AUTO_DVB_S_S2     ",1000);
      else if  (prop->dd_mode.auto_detect     ==     3) strncat(msg,"AUTO_DVB_S_S2_DSS ",1000);
      else                                             STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_mode.auto_detect);
     break;
    #endif /*     Si2183_DD_MODE_PROP */
    #ifdef        Si2183_DD_PER_RESOL_PROP
     case         Si2183_DD_PER_RESOL_PROP_CODE:
      snprintf(msg,1000,"DD_PER_RESOL");
       strncat(msg,separator,1000); strncat(msg,"-EXP ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_per_resol.exp);
       strncat(msg,separator,1000); strncat(msg,"-MANT ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_per_resol.mant);
     break;
    #endif /*     Si2183_DD_PER_RESOL_PROP */
    #ifdef        Si2183_DD_RSQ_BER_THRESHOLD_PROP
     case         Si2183_DD_RSQ_BER_THRESHOLD_PROP_CODE:
      snprintf(msg,1000,"DD_RSQ_BER_THRESHOLD");
       strncat(msg,separator,1000); strncat(msg,"-EXP ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_rsq_ber_threshold.exp);
       strncat(msg,separator,1000); strncat(msg,"-MANT ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_rsq_ber_threshold.mant);
     break;
    #endif /*     Si2183_DD_RSQ_BER_THRESHOLD_PROP */
    #ifdef        Si2183_DD_SEC_TS_SERIAL_DIFF_PROP
     case         Si2183_DD_SEC_TS_SERIAL_DIFF_PROP_CODE:
      snprintf(msg,1000,"DD_SEC_TS_SERIAL_DIFF");
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA1_STRENGTH ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_serial_diff.ts_data1_strength);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA1_SHAPE ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_serial_diff.ts_data1_shape);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA2_STRENGTH ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_serial_diff.ts_data2_strength);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA2_SHAPE ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_serial_diff.ts_data2_shape);
       strncat(msg,separator,1000); strncat(msg,"-TS_CLKB_ON_DATA1 ",1000);
           if  (prop->dd_sec_ts_serial_diff.ts_clkb_on_data1   ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_sec_ts_serial_diff.ts_clkb_on_data1   ==     1) strncat(msg,"ENABLE  ",1000);
      else                                                              STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_serial_diff.ts_clkb_on_data1);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA0B_ON_DATA2 ",1000);
           if  (prop->dd_sec_ts_serial_diff.ts_data0b_on_data2 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_sec_ts_serial_diff.ts_data0b_on_data2 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                                              STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_serial_diff.ts_data0b_on_data2);
     break;
    #endif /*     Si2183_DD_SEC_TS_SERIAL_DIFF_PROP */
    #ifdef        Si2183_DD_SEC_TS_SETUP_PAR_PROP
     case         Si2183_DD_SEC_TS_SETUP_PAR_PROP_CODE:
      snprintf(msg,1000,"DD_SEC_TS_SETUP_PAR");
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA_STRENGTH ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_setup_par.ts_data_strength);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA_SHAPE ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_setup_par.ts_data_shape);
       strncat(msg,separator,1000); strncat(msg,"-TS_CLK_STRENGTH ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_setup_par.ts_clk_strength);
       strncat(msg,separator,1000); strncat(msg,"-TS_CLK_SHAPE ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_setup_par.ts_clk_shape);
     break;
    #endif /*     Si2183_DD_SEC_TS_SETUP_PAR_PROP */
    #ifdef        Si2183_DD_SEC_TS_SETUP_SER_PROP
     case         Si2183_DD_SEC_TS_SETUP_SER_PROP_CODE:
      snprintf(msg,1000,"DD_SEC_TS_SETUP_SER");
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA_STRENGTH ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_setup_ser.ts_data_strength);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA_SHAPE ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_setup_ser.ts_data_shape);
       strncat(msg,separator,1000); strncat(msg,"-TS_CLK_STRENGTH ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_setup_ser.ts_clk_strength);
       strncat(msg,separator,1000); strncat(msg,"-TS_CLK_SHAPE ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_setup_ser.ts_clk_shape);
     break;
    #endif /*     Si2183_DD_SEC_TS_SETUP_SER_PROP */
    #ifdef        Si2183_DD_SEC_TS_SLR_SERIAL_PROP
     case         Si2183_DD_SEC_TS_SLR_SERIAL_PROP_CODE:
      snprintf(msg,1000,"DD_SEC_TS_SLR_SERIAL");
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA_SLR ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_slr_serial.ts_data_slr);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA_SLR_ON ",1000);
           if  (prop->dd_sec_ts_slr_serial.ts_data_slr_on  ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_sec_ts_slr_serial.ts_data_slr_on  ==     1) strncat(msg,"ENABLE  ",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_slr_serial.ts_data_slr_on);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA1_SLR ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_slr_serial.ts_data1_slr);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA1_SLR_ON ",1000);
           if  (prop->dd_sec_ts_slr_serial.ts_data1_slr_on ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_sec_ts_slr_serial.ts_data1_slr_on ==     1) strncat(msg,"ENABLE  ",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_slr_serial.ts_data1_slr_on);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA2_SLR ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_slr_serial.ts_data2_slr);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA2_SLR_ON ",1000);
           if  (prop->dd_sec_ts_slr_serial.ts_data2_slr_on ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_sec_ts_slr_serial.ts_data2_slr_on ==     1) strncat(msg,"ENABLE  ",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_slr_serial.ts_data2_slr_on);
       strncat(msg,separator,1000); strncat(msg,"-TS_CLK_SLR ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_slr_serial.ts_clk_slr);
       strncat(msg,separator,1000); strncat(msg,"-TS_CLK_SLR_ON ",1000);
           if  (prop->dd_sec_ts_slr_serial.ts_clk_slr_on   ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_sec_ts_slr_serial.ts_clk_slr_on   ==     1) strncat(msg,"ENABLE  ",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_sec_ts_slr_serial.ts_clk_slr_on);
     break;
    #endif /*     Si2183_DD_SEC_TS_SLR_SERIAL_PROP */
    #ifdef        Si2183_DD_SSI_SQI_PARAM_PROP
     case         Si2183_DD_SSI_SQI_PARAM_PROP_CODE:
      snprintf(msg,1000,"DD_SSI_SQI_PARAM");
       strncat(msg,separator,1000); strncat(msg,"-SQI_AVERAGE ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ssi_sqi_param.sqi_average);
     break;
    #endif /*     Si2183_DD_SSI_SQI_PARAM_PROP */
    #ifdef        Si2183_DD_TS_FREQ_PROP
     case         Si2183_DD_TS_FREQ_PROP_CODE:
      snprintf(msg,1000,"DD_TS_FREQ");
       strncat(msg,separator,1000); strncat(msg,"-REQ_FREQ_10KHZ ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_freq.req_freq_10khz);
     break;
    #endif /*     Si2183_DD_TS_FREQ_PROP */
    #ifdef        Si2183_DD_TS_FREQ_MAX_PROP
     case         Si2183_DD_TS_FREQ_MAX_PROP_CODE:
      snprintf(msg,1000,"DD_TS_FREQ_MAX");
       strncat(msg,separator,1000); strncat(msg,"-REQ_FREQ_MAX_10KHZ ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_freq_max.req_freq_max_10khz);
     break;
    #endif /*     Si2183_DD_TS_FREQ_MAX_PROP */
    #ifdef        Si2183_DD_TS_MODE_PROP
     case         Si2183_DD_TS_MODE_PROP_CODE:
      snprintf(msg,1000,"DD_TS_MODE");
       strncat(msg,separator,1000); strncat(msg,"-MODE ",1000);
           if  (prop->dd_ts_mode.mode               ==     0) strncat(msg,"TRISTATE ",1000);
      else if  (prop->dd_ts_mode.mode               ==     1) strncat(msg,"OFF      ",1000);
      else if  (prop->dd_ts_mode.mode               ==     3) strncat(msg,"SERIAL   ",1000);
      else if  (prop->dd_ts_mode.mode               ==     6) strncat(msg,"PARALLEL ",1000);
      else if  (prop->dd_ts_mode.mode               ==     7) strncat(msg,"GPIF     ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_mode.mode);
       strncat(msg,separator,1000); strncat(msg,"-CLOCK ",1000);
           if  (prop->dd_ts_mode.clock              ==     0) strncat(msg,"AUTO_FIXED ",1000);
      else if  (prop->dd_ts_mode.clock              ==     1) strncat(msg,"AUTO_ADAPT ",1000);
      else if  (prop->dd_ts_mode.clock              ==     2) strncat(msg,"MANUAL     ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_mode.clock);
       strncat(msg,separator,1000); strncat(msg,"-CLK_GAPPED_EN ",1000);
           if  (prop->dd_ts_mode.clk_gapped_en      ==     0) strncat(msg,"DISABLED ",1000);
      else if  (prop->dd_ts_mode.clk_gapped_en      ==     1) strncat(msg,"ENABLED  ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_mode.clk_gapped_en);
       strncat(msg,separator,1000); strncat(msg,"-TS_ERR_POLARITY ",1000);
           if  (prop->dd_ts_mode.ts_err_polarity    ==     0) strncat(msg,"NOT_INVERTED ",1000);
      else if  (prop->dd_ts_mode.ts_err_polarity    ==     1) strncat(msg,"INVERTED     ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_mode.ts_err_polarity);
       strncat(msg,separator,1000); strncat(msg,"-SPECIAL ",1000);
           if  (prop->dd_ts_mode.special            ==     0) strncat(msg,"FULL_TS        ",1000);
      else if  (prop->dd_ts_mode.special            ==     1) strncat(msg,"DATAS_TRISTATE ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_mode.special);
       strncat(msg,separator,1000); strncat(msg,"-TS_FREQ_RESOLUTION ",1000);
           if  (prop->dd_ts_mode.ts_freq_resolution ==     0) strncat(msg,"NORMAL ",1000);
      else if  (prop->dd_ts_mode.ts_freq_resolution ==     1) strncat(msg,"FINE   ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_mode.ts_freq_resolution);
       strncat(msg,separator,1000); strncat(msg,"-SERIAL_PIN_SELECTION ",1000);
           if  (prop->dd_ts_mode.serial_pin_selection ==     0) strncat(msg,"D0 ",1000);
      else if  (prop->dd_ts_mode.serial_pin_selection ==     1) strncat(msg,"D1 ",1000);
      else if  (prop->dd_ts_mode.serial_pin_selection ==     2) strncat(msg,"D2 ",1000);
      else if  (prop->dd_ts_mode.serial_pin_selection ==     3) strncat(msg,"D3 ",1000);
      else if  (prop->dd_ts_mode.serial_pin_selection ==     4) strncat(msg,"D4 ",1000);
      else if  (prop->dd_ts_mode.serial_pin_selection ==     5) strncat(msg,"D5 ",1000);
      else if  (prop->dd_ts_mode.serial_pin_selection ==     6) strncat(msg,"D6 ",1000);
      else if  (prop->dd_ts_mode.serial_pin_selection ==     7) strncat(msg,"D7 ",1000);
      else                                                     STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_mode.serial_pin_selection);
     break;
    #endif /*     Si2183_DD_TS_MODE_PROP */
    #ifdef        Si2183_DD_TS_SERIAL_DIFF_PROP
     case         Si2183_DD_TS_SERIAL_DIFF_PROP_CODE:
      snprintf(msg,1000,"DD_TS_SERIAL_DIFF");
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA1_STRENGTH ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_serial_diff.ts_data1_strength);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA1_SHAPE ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_serial_diff.ts_data1_shape);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA2_STRENGTH ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_serial_diff.ts_data2_strength);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA2_SHAPE ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_serial_diff.ts_data2_shape);
       strncat(msg,separator,1000); strncat(msg,"-TS_CLKB_ON_DATA1 ",1000);
           if  (prop->dd_ts_serial_diff.ts_clkb_on_data1   ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_ts_serial_diff.ts_clkb_on_data1   ==     1) strncat(msg,"ENABLE  ",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_serial_diff.ts_clkb_on_data1);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA0B_ON_DATA2 ",1000);
           if  (prop->dd_ts_serial_diff.ts_data0b_on_data2 ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_ts_serial_diff.ts_data0b_on_data2 ==     1) strncat(msg,"ENABLE  ",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_serial_diff.ts_data0b_on_data2);
     break;
    #endif /*     Si2183_DD_TS_SERIAL_DIFF_PROP */
    #ifdef        Si2183_DD_TS_SETUP_PAR_PROP
     case         Si2183_DD_TS_SETUP_PAR_PROP_CODE:
      snprintf(msg,1000,"DD_TS_SETUP_PAR");
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA_STRENGTH ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_setup_par.ts_data_strength);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA_SHAPE ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_setup_par.ts_data_shape);
       strncat(msg,separator,1000); strncat(msg,"-TS_CLK_STRENGTH ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_setup_par.ts_clk_strength);
       strncat(msg,separator,1000); strncat(msg,"-TS_CLK_SHAPE ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_setup_par.ts_clk_shape);
       strncat(msg,separator,1000); strncat(msg,"-TS_CLK_INVERT ",1000);
           if  (prop->dd_ts_setup_par.ts_clk_invert    ==     0) strncat(msg,"NOT_INVERTED ",1000);
      else if  (prop->dd_ts_setup_par.ts_clk_invert    ==     1) strncat(msg,"INVERTED     ",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_setup_par.ts_clk_invert);
       strncat(msg,separator,1000); strncat(msg,"-TS_CLK_SHIFT ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_setup_par.ts_clk_shift);
     break;
    #endif /*     Si2183_DD_TS_SETUP_PAR_PROP */
    #ifdef        Si2183_DD_TS_SETUP_SER_PROP
     case         Si2183_DD_TS_SETUP_SER_PROP_CODE:
      snprintf(msg,1000,"DD_TS_SETUP_SER");
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA_STRENGTH ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_setup_ser.ts_data_strength);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA_SHAPE ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_setup_ser.ts_data_shape);
       strncat(msg,separator,1000); strncat(msg,"-TS_CLK_STRENGTH ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_setup_ser.ts_clk_strength);
       strncat(msg,separator,1000); strncat(msg,"-TS_CLK_SHAPE ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_setup_ser.ts_clk_shape);
       strncat(msg,separator,1000); strncat(msg,"-TS_CLK_INVERT ",1000);
           if  (prop->dd_ts_setup_ser.ts_clk_invert    ==     0) strncat(msg,"NOT_INVERTED ",1000);
      else if  (prop->dd_ts_setup_ser.ts_clk_invert    ==     1) strncat(msg,"INVERTED     ",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_setup_ser.ts_clk_invert);
       strncat(msg,separator,1000); strncat(msg,"-TS_SYNC_DURATION ",1000);
           if  (prop->dd_ts_setup_ser.ts_sync_duration ==     0) strncat(msg,"FIRST_BYTE ",1000);
      else if  (prop->dd_ts_setup_ser.ts_sync_duration ==     1) strncat(msg,"FIRST_BIT  ",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_setup_ser.ts_sync_duration);
       strncat(msg,separator,1000); strncat(msg,"-TS_BYTE_ORDER ",1000);
           if  (prop->dd_ts_setup_ser.ts_byte_order    ==     0) strncat(msg,"MSB_FIRST ",1000);
      else if  (prop->dd_ts_setup_ser.ts_byte_order    ==     1) strncat(msg,"LSB_FIRST ",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_setup_ser.ts_byte_order);
     break;
    #endif /*     Si2183_DD_TS_SETUP_SER_PROP */
    #ifdef        Si2183_DD_TS_SLR_SERIAL_PROP
     case         Si2183_DD_TS_SLR_SERIAL_PROP_CODE:
      snprintf(msg,1000,"DD_TS_SLR_SERIAL");
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA_SLR ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_slr_serial.ts_data_slr);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA_SLR_ON ",1000);
           if  (prop->dd_ts_slr_serial.ts_data_slr_on  ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_ts_slr_serial.ts_data_slr_on  ==     1) strncat(msg,"ENABLE  ",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_slr_serial.ts_data_slr_on);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA1_SLR ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_slr_serial.ts_data1_slr);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA1_SLR_ON ",1000);
           if  (prop->dd_ts_slr_serial.ts_data1_slr_on ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_ts_slr_serial.ts_data1_slr_on ==     1) strncat(msg,"ENABLE  ",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_slr_serial.ts_data1_slr_on);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA2_SLR ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_slr_serial.ts_data2_slr);
       strncat(msg,separator,1000); strncat(msg,"-TS_DATA2_SLR_ON ",1000);
           if  (prop->dd_ts_slr_serial.ts_data2_slr_on ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_ts_slr_serial.ts_data2_slr_on ==     1) strncat(msg,"ENABLE  ",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_slr_serial.ts_data2_slr_on);
       strncat(msg,separator,1000); strncat(msg,"-TS_CLK_SLR ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_slr_serial.ts_clk_slr);
       strncat(msg,separator,1000); strncat(msg,"-TS_CLK_SLR_ON ",1000);
           if  (prop->dd_ts_slr_serial.ts_clk_slr_on   ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->dd_ts_slr_serial.ts_clk_slr_on   ==     1) strncat(msg,"ENABLE  ",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", prop->dd_ts_slr_serial.ts_clk_slr_on);
     break;
    #endif /*     Si2183_DD_TS_SLR_SERIAL_PROP */
#ifdef    DEMOD_DVB_C2
    #ifdef        Si2183_DVBC2_ADC_CREST_FACTOR_PROP
     case         Si2183_DVBC2_ADC_CREST_FACTOR_PROP_CODE:
      snprintf(msg,1000,"DVBC2_ADC_CREST_FACTOR");
       strncat(msg,separator,1000); strncat(msg,"-CREST_FACTOR ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbc2_adc_crest_factor.crest_factor);
     break;
    #endif /*     Si2183_DVBC2_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_DVBC2_AFC_RANGE_PROP
     case         Si2183_DVBC2_AFC_RANGE_PROP_CODE:
      snprintf(msg,1000,"DVBC2_AFC_RANGE");
       strncat(msg,separator,1000); strncat(msg,"-RANGE_KHZ ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbc2_afc_range.range_khz);
     break;
    #endif /*     Si2183_DVBC2_AFC_RANGE_PROP */
#endif /* DEMOD_DVB_C2 */

#ifdef    DEMOD_DVB_C
    #ifdef        Si2183_DVBC_ADC_CREST_FACTOR_PROP
     case         Si2183_DVBC_ADC_CREST_FACTOR_PROP_CODE:
      snprintf(msg,1000,"DVBC_ADC_CREST_FACTOR");
       strncat(msg,separator,1000); strncat(msg,"-CREST_FACTOR ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbc_adc_crest_factor.crest_factor);
     break;
    #endif /*     Si2183_DVBC_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_DVBC_AFC_RANGE_PROP
     case         Si2183_DVBC_AFC_RANGE_PROP_CODE:
      snprintf(msg,1000,"DVBC_AFC_RANGE");
       strncat(msg,separator,1000); strncat(msg,"-RANGE_KHZ ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbc_afc_range.range_khz);
     break;
    #endif /*     Si2183_DVBC_AFC_RANGE_PROP */
    #ifdef        Si2183_DVBC_CONSTELLATION_PROP
     case         Si2183_DVBC_CONSTELLATION_PROP_CODE:
      snprintf(msg,1000,"DVBC_CONSTELLATION");
       strncat(msg,separator,1000); strncat(msg,"-CONSTELLATION ",1000);
           if  (prop->dvbc_constellation.constellation ==     0) strncat(msg,"AUTO   ",1000);
      else if  (prop->dvbc_constellation.constellation ==     7) strncat(msg,"QAM16  ",1000);
      else if  (prop->dvbc_constellation.constellation ==     8) strncat(msg,"QAM32  ",1000);
      else if  (prop->dvbc_constellation.constellation ==     9) strncat(msg,"QAM64  ",1000);
      else if  (prop->dvbc_constellation.constellation ==    10) strncat(msg,"QAM128 ",1000);
      else if  (prop->dvbc_constellation.constellation ==    11) strncat(msg,"QAM256 ",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbc_constellation.constellation);
     break;
    #endif /*     Si2183_DVBC_CONSTELLATION_PROP */
    #ifdef        Si2183_DVBC_SYMBOL_RATE_PROP
     case         Si2183_DVBC_SYMBOL_RATE_PROP_CODE:
      snprintf(msg,1000,"DVBC_SYMBOL_RATE");
       strncat(msg,separator,1000); strncat(msg,"-RATE ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbc_symbol_rate.rate);
     break;
    #endif /*     Si2183_DVBC_SYMBOL_RATE_PROP */
#endif /* DEMOD_DVB_C */

#ifdef    DEMOD_DVB_S_S2_DSS
    #ifdef        Si2183_DVBS2_ADC_CREST_FACTOR_PROP
     case         Si2183_DVBS2_ADC_CREST_FACTOR_PROP_CODE:
      snprintf(msg,1000,"DVBS2_ADC_CREST_FACTOR");
       strncat(msg,separator,1000); strncat(msg,"-CREST_FACTOR ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbs2_adc_crest_factor.crest_factor);
     break;
    #endif /*     Si2183_DVBS2_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_DVBS2_AFC_RANGE_PROP
     case         Si2183_DVBS2_AFC_RANGE_PROP_CODE:
      snprintf(msg,1000,"DVBS2_AFC_RANGE");
       strncat(msg,separator,1000); strncat(msg,"-RANGE_KHZ ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbs2_afc_range.range_khz);
     break;
    #endif /*     Si2183_DVBS2_AFC_RANGE_PROP */
    #ifdef        Si2183_DVBS2_SYMBOL_RATE_PROP
     case         Si2183_DVBS2_SYMBOL_RATE_PROP_CODE:
      snprintf(msg,1000,"DVBS2_SYMBOL_RATE");
       strncat(msg,separator,1000); strncat(msg,"-RATE ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbs2_symbol_rate.rate);
     break;
    #endif /*     Si2183_DVBS2_SYMBOL_RATE_PROP */
    #ifdef        Si2183_DVBS_ADC_CREST_FACTOR_PROP
     case         Si2183_DVBS_ADC_CREST_FACTOR_PROP_CODE:
      snprintf(msg,1000,"DVBS_ADC_CREST_FACTOR");
       strncat(msg,separator,1000); strncat(msg,"-CREST_FACTOR ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbs_adc_crest_factor.crest_factor);
     break;
    #endif /*     Si2183_DVBS_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_DVBS_AFC_RANGE_PROP
     case         Si2183_DVBS_AFC_RANGE_PROP_CODE:
      snprintf(msg,1000,"DVBS_AFC_RANGE");
       strncat(msg,separator,1000); strncat(msg,"-RANGE_KHZ ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbs_afc_range.range_khz);
     break;
    #endif /*     Si2183_DVBS_AFC_RANGE_PROP */
    #ifdef        Si2183_DVBS_SYMBOL_RATE_PROP
     case         Si2183_DVBS_SYMBOL_RATE_PROP_CODE:
      snprintf(msg,1000,"DVBS_SYMBOL_RATE");
       strncat(msg,separator,1000); strncat(msg,"-RATE ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbs_symbol_rate.rate);
     break;
    #endif /*     Si2183_DVBS_SYMBOL_RATE_PROP */
#endif /* DEMOD_DVB_S_S2_DSS */

#ifdef    DEMOD_DVB_T2
    #ifdef        Si2183_DVBT2_ADC_CREST_FACTOR_PROP
     case         Si2183_DVBT2_ADC_CREST_FACTOR_PROP_CODE:
      snprintf(msg,1000,"DVBT2_ADC_CREST_FACTOR");
       strncat(msg,separator,1000); strncat(msg,"-CREST_FACTOR ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbt2_adc_crest_factor.crest_factor);
     break;
    #endif /*     Si2183_DVBT2_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_DVBT2_AFC_RANGE_PROP
     case         Si2183_DVBT2_AFC_RANGE_PROP_CODE:
      snprintf(msg,1000,"DVBT2_AFC_RANGE");
       strncat(msg,separator,1000); strncat(msg,"-RANGE_KHZ ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbt2_afc_range.range_khz);
     break;
    #endif /*     Si2183_DVBT2_AFC_RANGE_PROP */
    #ifdef        Si2183_DVBT2_FEF_TUNER_PROP
     case         Si2183_DVBT2_FEF_TUNER_PROP_CODE:
      snprintf(msg,1000,"DVBT2_FEF_TUNER");
       strncat(msg,separator,1000); strncat(msg,"-TUNER_DELAY ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbt2_fef_tuner.tuner_delay);
       strncat(msg,separator,1000); strncat(msg,"-TUNER_FREEZE_TIME ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbt2_fef_tuner.tuner_freeze_time);
       strncat(msg,separator,1000); strncat(msg,"-TUNER_UNFREEZE_TIME ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbt2_fef_tuner.tuner_unfreeze_time);
     break;
    #endif /*     Si2183_DVBT2_FEF_TUNER_PROP */
    #ifdef        Si2183_DVBT2_MODE_PROP
     case         Si2183_DVBT2_MODE_PROP_CODE:
      snprintf(msg,1000,"DVBT2_MODE");
       strncat(msg,separator,1000); strncat(msg,"-LOCK_MODE ",1000);
           if  (prop->dvbt2_mode.lock_mode ==     0) strncat(msg,"ANY       ",1000);
      else if  (prop->dvbt2_mode.lock_mode ==     1) strncat(msg,"BASE_ONLY ",1000);
      else if  (prop->dvbt2_mode.lock_mode ==     2) strncat(msg,"LITE_ONLY ",1000);
      else if  (prop->dvbt2_mode.lock_mode ==     3) strncat(msg,"RESERVED  ",1000);
      else                                          STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbt2_mode.lock_mode);
     break;
    #endif /*     Si2183_DVBT2_MODE_PROP */
#endif /* DEMOD_DVB_T2 */

#ifdef    DEMOD_DVB_T
    #ifdef        Si2183_DVBT_ADC_CREST_FACTOR_PROP
     case         Si2183_DVBT_ADC_CREST_FACTOR_PROP_CODE:
      snprintf(msg,1000,"DVBT_ADC_CREST_FACTOR");
       strncat(msg,separator,1000); strncat(msg,"-CREST_FACTOR ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbt_adc_crest_factor.crest_factor);
     break;
    #endif /*     Si2183_DVBT_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_DVBT_AFC_RANGE_PROP
     case         Si2183_DVBT_AFC_RANGE_PROP_CODE:
      snprintf(msg,1000,"DVBT_AFC_RANGE");
       strncat(msg,separator,1000); strncat(msg,"-RANGE_KHZ ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbt_afc_range.range_khz);
     break;
    #endif /*     Si2183_DVBT_AFC_RANGE_PROP */
    #ifdef        Si2183_DVBT_HIERARCHY_PROP
     case         Si2183_DVBT_HIERARCHY_PROP_CODE:
      snprintf(msg,1000,"DVBT_HIERARCHY");
       strncat(msg,separator,1000); strncat(msg,"-STREAM ",1000);
           if  (prop->dvbt_hierarchy.stream ==     0) strncat(msg,"HP ",1000);
      else if  (prop->dvbt_hierarchy.stream ==     1) strncat(msg,"LP ",1000);
      else                                           STRING_APPEND_SAFE(msg,1000,"%d", prop->dvbt_hierarchy.stream);
     break;
    #endif /*     Si2183_DVBT_HIERARCHY_PROP */
#endif /* DEMOD_DVB_T */

#ifdef    DEMOD_ISDB_T
    #ifdef        Si2183_ISDBT_AC_SELECT_PROP
     case         Si2183_ISDBT_AC_SELECT_PROP_CODE:
      snprintf(msg,1000,"ISDBT_AC_SELECT");
       strncat(msg,separator,1000); strncat(msg,"-SEGMENT_SEL ",1000);
           if  (prop->isdbt_ac_select.segment_sel ==     0) strncat(msg,"SEG_0  ",1000);
      else if  (prop->isdbt_ac_select.segment_sel ==     1) strncat(msg,"SEG_1  ",1000);
      else if  (prop->isdbt_ac_select.segment_sel ==     2) strncat(msg,"SEG_2  ",1000);
      else if  (prop->isdbt_ac_select.segment_sel ==     3) strncat(msg,"SEG_3  ",1000);
      else if  (prop->isdbt_ac_select.segment_sel ==     4) strncat(msg,"SEG_4  ",1000);
      else if  (prop->isdbt_ac_select.segment_sel ==     5) strncat(msg,"SEG_5  ",1000);
      else if  (prop->isdbt_ac_select.segment_sel ==     6) strncat(msg,"SEG_6  ",1000);
      else if  (prop->isdbt_ac_select.segment_sel ==     7) strncat(msg,"SEG_7  ",1000);
      else if  (prop->isdbt_ac_select.segment_sel ==     8) strncat(msg,"SEG_8  ",1000);
      else if  (prop->isdbt_ac_select.segment_sel ==     9) strncat(msg,"SEG_9  ",1000);
      else if  (prop->isdbt_ac_select.segment_sel ==    10) strncat(msg,"SEG_10 ",1000);
      else if  (prop->isdbt_ac_select.segment_sel ==    11) strncat(msg,"SEG_11 ",1000);
      else if  (prop->isdbt_ac_select.segment_sel ==    12) strncat(msg,"SEG_12 ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", prop->isdbt_ac_select.segment_sel);
       strncat(msg,separator,1000); strncat(msg,"-FILTERING ",1000);
           if  (prop->isdbt_ac_select.filtering   ==     0) strncat(msg,"KEEP_ALL           ",1000);
      else if  (prop->isdbt_ac_select.filtering   ==     1) strncat(msg,"KEEP_SEISMIC_ALERT ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", prop->isdbt_ac_select.filtering);
     break;
    #endif /*     Si2183_ISDBT_AC_SELECT_PROP */
    #ifdef        Si2183_ISDBT_ADC_CREST_FACTOR_PROP
     case         Si2183_ISDBT_ADC_CREST_FACTOR_PROP_CODE:
      snprintf(msg,1000,"ISDBT_ADC_CREST_FACTOR");
       strncat(msg,separator,1000); strncat(msg,"-CREST_FACTOR ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->isdbt_adc_crest_factor.crest_factor);
     break;
    #endif /*     Si2183_ISDBT_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_ISDBT_AFC_RANGE_PROP
     case         Si2183_ISDBT_AFC_RANGE_PROP_CODE:
      snprintf(msg,1000,"ISDBT_AFC_RANGE");
       strncat(msg,separator,1000); strncat(msg,"-RANGE_KHZ ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->isdbt_afc_range.range_khz);
     break;
    #endif /*     Si2183_ISDBT_AFC_RANGE_PROP */
    #ifdef        Si2183_ISDBT_MODE_PROP
     case         Si2183_ISDBT_MODE_PROP_CODE:
      snprintf(msg,1000,"ISDBT_MODE");
       strncat(msg,separator,1000); strncat(msg,"-LAYER_MON ",1000);
           if  (prop->isdbt_mode.layer_mon ==     0) strncat(msg,"ALL     ",1000);
      else if  (prop->isdbt_mode.layer_mon ==     1) strncat(msg,"LAYER_A ",1000);
      else if  (prop->isdbt_mode.layer_mon ==     2) strncat(msg,"LAYER_B ",1000);
      else if  (prop->isdbt_mode.layer_mon ==     3) strncat(msg,"LAYER_C ",1000);
      else                                          STRING_APPEND_SAFE(msg,1000,"%d", prop->isdbt_mode.layer_mon);
       strncat(msg,separator,1000); strncat(msg,"-DL_CONFIG ",1000);
           if  (prop->isdbt_mode.dl_config ==     0) strncat(msg,"ALL_LOCKED           ",1000);
      else if  (prop->isdbt_mode.dl_config ==     1) strncat(msg,"A_AND_B_LOCKED       ",1000);
      else if  (prop->isdbt_mode.dl_config ==     2) strncat(msg,"A_AND_C_LOCKED       ",1000);
      else if  (prop->isdbt_mode.dl_config ==     3) strncat(msg,"A_LOCKED             ",1000);
      else if  (prop->isdbt_mode.dl_config ==     4) strncat(msg,"B_AND_C_LOCKED       ",1000);
      else if  (prop->isdbt_mode.dl_config ==     5) strncat(msg,"B_LOCKED             ",1000);
      else if  (prop->isdbt_mode.dl_config ==     6) strncat(msg,"C_LOCKED             ",1000);
      else if  (prop->isdbt_mode.dl_config ==     8) strncat(msg,"FASTEST_LAYER_LOCKED ",1000);
      else if  (prop->isdbt_mode.dl_config ==     9) strncat(msg,"A_OR_B_LOCKED        ",1000);
      else if  (prop->isdbt_mode.dl_config ==    10) strncat(msg,"A_OR_C_LOCKED        ",1000);
      else if  (prop->isdbt_mode.dl_config ==    12) strncat(msg,"B_OR_C_LOCKED        ",1000);
      else                                          STRING_APPEND_SAFE(msg,1000,"%d", prop->isdbt_mode.dl_config);
       strncat(msg,separator,1000); strncat(msg,"-TRADEOFF ",1000);
           if  (prop->isdbt_mode.tradeoff  ==     0) strncat(msg,"OPTIMAL_PERFORMANCE ",1000);
      else if  (prop->isdbt_mode.tradeoff  ==     1) strncat(msg,"KEEP_PACKET_ORDER   ",1000);
      else                                          STRING_APPEND_SAFE(msg,1000,"%d", prop->isdbt_mode.tradeoff);
     break;
    #endif /*     Si2183_ISDBT_MODE_PROP */
#endif /* DEMOD_ISDB_T */

    #ifdef        Si2183_MASTER_IEN_PROP
     case         Si2183_MASTER_IEN_PROP_CODE:
      snprintf(msg,1000,"MASTER_IEN");
       strncat(msg,separator,1000); strncat(msg,"-DDIEN ",1000);
           if  (prop->master_ien.ddien   ==     0) strncat(msg,"OFF ",1000);
      else if  (prop->master_ien.ddien   ==     1) strncat(msg,"ON  ",1000);
      else                                        STRING_APPEND_SAFE(msg,1000,"%d", prop->master_ien.ddien);
       strncat(msg,separator,1000); strncat(msg,"-SCANIEN ",1000);
           if  (prop->master_ien.scanien ==     0) strncat(msg,"OFF ",1000);
      else if  (prop->master_ien.scanien ==     1) strncat(msg,"ON  ",1000);
      else                                        STRING_APPEND_SAFE(msg,1000,"%d", prop->master_ien.scanien);
       strncat(msg,separator,1000); strncat(msg,"-ERRIEN ",1000);
           if  (prop->master_ien.errien  ==     0) strncat(msg,"OFF ",1000);
      else if  (prop->master_ien.errien  ==     1) strncat(msg,"ON  ",1000);
      else                                        STRING_APPEND_SAFE(msg,1000,"%d", prop->master_ien.errien);
       strncat(msg,separator,1000); strncat(msg,"-CTSIEN ",1000);
           if  (prop->master_ien.ctsien  ==     0) strncat(msg,"OFF ",1000);
      else if  (prop->master_ien.ctsien  ==     1) strncat(msg,"ON  ",1000);
      else                                        STRING_APPEND_SAFE(msg,1000,"%d", prop->master_ien.ctsien);
     break;
    #endif /*     Si2183_MASTER_IEN_PROP */
#ifdef    DEMOD_MCNS
    #ifdef        Si2183_MCNS_ADC_CREST_FACTOR_PROP
     case         Si2183_MCNS_ADC_CREST_FACTOR_PROP_CODE:
      snprintf(msg,1000,"MCNS_ADC_CREST_FACTOR");
       strncat(msg,separator,1000); strncat(msg,"-CREST_FACTOR ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->mcns_adc_crest_factor.crest_factor);
     break;
    #endif /*     Si2183_MCNS_ADC_CREST_FACTOR_PROP */
    #ifdef        Si2183_MCNS_AFC_RANGE_PROP
     case         Si2183_MCNS_AFC_RANGE_PROP_CODE:
      snprintf(msg,1000,"MCNS_AFC_RANGE");
       strncat(msg,separator,1000); strncat(msg,"-RANGE_KHZ ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->mcns_afc_range.range_khz);
     break;
    #endif /*     Si2183_MCNS_AFC_RANGE_PROP */
    #ifdef        Si2183_MCNS_CONSTELLATION_PROP
     case         Si2183_MCNS_CONSTELLATION_PROP_CODE:
      snprintf(msg,1000,"MCNS_CONSTELLATION");
       strncat(msg,separator,1000); strncat(msg,"-CONSTELLATION ",1000);
           if  (prop->mcns_constellation.constellation ==     0) strncat(msg,"AUTO   ",1000);
      else if  (prop->mcns_constellation.constellation ==     9) strncat(msg,"QAM64  ",1000);
      else if  (prop->mcns_constellation.constellation ==    11) strncat(msg,"QAM256 ",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", prop->mcns_constellation.constellation);
     break;
    #endif /*     Si2183_MCNS_CONSTELLATION_PROP */
    #ifdef        Si2183_MCNS_SYMBOL_RATE_PROP
     case         Si2183_MCNS_SYMBOL_RATE_PROP_CODE:
      snprintf(msg,1000,"MCNS_SYMBOL_RATE");
       strncat(msg,separator,1000); strncat(msg,"-RATE ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->mcns_symbol_rate.rate);
     break;
    #endif /*     Si2183_MCNS_SYMBOL_RATE_PROP */
#endif /* DEMOD_MCNS */

    #ifdef        Si2183_SCAN_FMAX_PROP
     case         Si2183_SCAN_FMAX_PROP_CODE:
      snprintf(msg,1000,"SCAN_FMAX");
       strncat(msg,separator,1000); strncat(msg,"-SCAN_FMAX ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->scan_fmax.scan_fmax);
     break;
    #endif /*     Si2183_SCAN_FMAX_PROP */
    #ifdef        Si2183_SCAN_FMIN_PROP
     case         Si2183_SCAN_FMIN_PROP_CODE:
      snprintf(msg,1000,"SCAN_FMIN");
       strncat(msg,separator,1000); strncat(msg,"-SCAN_FMIN ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->scan_fmin.scan_fmin);
     break;
    #endif /*     Si2183_SCAN_FMIN_PROP */
    #ifdef        Si2183_SCAN_IEN_PROP
     case         Si2183_SCAN_IEN_PROP_CODE:
      snprintf(msg,1000,"SCAN_IEN");
       strncat(msg,separator,1000); strncat(msg,"-BUZIEN ",1000);
           if  (prop->scan_ien.buzien ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->scan_ien.buzien ==     1) strncat(msg,"ENABLE  ",1000);
      else                                     STRING_APPEND_SAFE(msg,1000,"%d", prop->scan_ien.buzien);
       strncat(msg,separator,1000); strncat(msg,"-REQIEN ",1000);
           if  (prop->scan_ien.reqien ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->scan_ien.reqien ==     1) strncat(msg,"ENABLE  ",1000);
      else                                     STRING_APPEND_SAFE(msg,1000,"%d", prop->scan_ien.reqien);
     break;
    #endif /*     Si2183_SCAN_IEN_PROP */
    #ifdef        Si2183_SCAN_INT_SENSE_PROP
     case         Si2183_SCAN_INT_SENSE_PROP_CODE:
      snprintf(msg,1000,"SCAN_INT_SENSE");
       strncat(msg,separator,1000); strncat(msg,"-BUZNEGEN ",1000);
           if  (prop->scan_int_sense.buznegen ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->scan_int_sense.buznegen ==     1) strncat(msg,"ENABLE  ",1000);
      else                                             STRING_APPEND_SAFE(msg,1000,"%d", prop->scan_int_sense.buznegen);
       strncat(msg,separator,1000); strncat(msg,"-REQNEGEN ",1000);
           if  (prop->scan_int_sense.reqnegen ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->scan_int_sense.reqnegen ==     1) strncat(msg,"ENABLE  ",1000);
      else                                             STRING_APPEND_SAFE(msg,1000,"%d", prop->scan_int_sense.reqnegen);
       strncat(msg,separator,1000); strncat(msg,"-BUZPOSEN ",1000);
           if  (prop->scan_int_sense.buzposen ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->scan_int_sense.buzposen ==     1) strncat(msg,"ENABLE  ",1000);
      else                                             STRING_APPEND_SAFE(msg,1000,"%d", prop->scan_int_sense.buzposen);
       strncat(msg,separator,1000); strncat(msg,"-REQPOSEN ",1000);
           if  (prop->scan_int_sense.reqposen ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->scan_int_sense.reqposen ==     1) strncat(msg,"ENABLE  ",1000);
      else                                             STRING_APPEND_SAFE(msg,1000,"%d", prop->scan_int_sense.reqposen);
     break;
    #endif /*     Si2183_SCAN_INT_SENSE_PROP */
#ifdef    DEMOD_DVB_S_S2_DSS
    #ifdef        Si2183_SCAN_SAT_CONFIG_PROP
     case         Si2183_SCAN_SAT_CONFIG_PROP_CODE:
      snprintf(msg,1000,"SCAN_SAT_CONFIG");
       strncat(msg,separator,1000); strncat(msg,"-ANALOG_DETECT ",1000);
           if  (prop->scan_sat_config.analog_detect ==     0) strncat(msg,"DISABLED ",1000);
      else if  (prop->scan_sat_config.analog_detect ==     1) strncat(msg,"ENABLED  ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", prop->scan_sat_config.analog_detect);
       strncat(msg,separator,1000); strncat(msg,"-RESERVED1 ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->scan_sat_config.reserved1);
       strncat(msg,separator,1000); strncat(msg,"-RESERVED2 ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->scan_sat_config.reserved2);
     break;
    #endif /*     Si2183_SCAN_SAT_CONFIG_PROP */
    #ifdef        Si2183_SCAN_SAT_UNICABLE_BW_PROP
     case         Si2183_SCAN_SAT_UNICABLE_BW_PROP_CODE:
      snprintf(msg,1000,"SCAN_SAT_UNICABLE_BW");
       strncat(msg,separator,1000); strncat(msg,"-SCAN_SAT_UNICABLE_BW ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->scan_sat_unicable_bw.scan_sat_unicable_bw);
     break;
    #endif /*     Si2183_SCAN_SAT_UNICABLE_BW_PROP */
    #ifdef        Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP
     case         Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP_CODE:
      snprintf(msg,1000,"SCAN_SAT_UNICABLE_MIN_TUNE_STEP");
       strncat(msg,separator,1000); strncat(msg,"-SCAN_SAT_UNICABLE_MIN_TUNE_STEP ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->scan_sat_unicable_min_tune_step.scan_sat_unicable_min_tune_step);
     break;
    #endif /*     Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP */
#endif /* DEMOD_DVB_S_S2_DSS */

    #ifdef        Si2183_SCAN_SYMB_RATE_MAX_PROP
     case         Si2183_SCAN_SYMB_RATE_MAX_PROP_CODE:
      snprintf(msg,1000,"SCAN_SYMB_RATE_MAX");
       strncat(msg,separator,1000); strncat(msg,"-SCAN_SYMB_RATE_MAX ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->scan_symb_rate_max.scan_symb_rate_max);
     break;
    #endif /*     Si2183_SCAN_SYMB_RATE_MAX_PROP */
    #ifdef        Si2183_SCAN_SYMB_RATE_MIN_PROP
     case         Si2183_SCAN_SYMB_RATE_MIN_PROP_CODE:
      snprintf(msg,1000,"SCAN_SYMB_RATE_MIN");
       strncat(msg,separator,1000); strncat(msg,"-SCAN_SYMB_RATE_MIN ",1000); STRING_APPEND_SAFE(msg,1000,"%d", prop->scan_symb_rate_min.scan_symb_rate_min);
     break;
    #endif /*     Si2183_SCAN_SYMB_RATE_MIN_PROP */
#ifdef    TERRESTRIAL_FRONT_END
    #ifdef        Si2183_SCAN_TER_CONFIG_PROP
     case         Si2183_SCAN_TER_CONFIG_PROP_CODE:
      snprintf(msg,1000,"SCAN_TER_CONFIG");
       strncat(msg,separator,1000); strncat(msg,"-MODE ",1000);
           if  (prop->scan_ter_config.mode          ==     0) strncat(msg,"BLIND_SCAN   ",1000);
      else if  (prop->scan_ter_config.mode          ==     1) strncat(msg,"MAPPING_SCAN ",1000);
      else if  (prop->scan_ter_config.mode          ==     2) strncat(msg,"BLIND_LOCK   ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", prop->scan_ter_config.mode);
       strncat(msg,separator,1000); strncat(msg,"-ANALOG_BW ",1000);
           if  (prop->scan_ter_config.analog_bw     ==     1) strncat(msg,"6MHZ ",1000);
      else if  (prop->scan_ter_config.analog_bw     ==     2) strncat(msg,"7MHZ ",1000);
      else if  (prop->scan_ter_config.analog_bw     ==     3) strncat(msg,"8MHZ ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", prop->scan_ter_config.analog_bw);
       strncat(msg,separator,1000); strncat(msg,"-SEARCH_ANALOG ",1000);
           if  (prop->scan_ter_config.search_analog ==     0) strncat(msg,"DISABLE ",1000);
      else if  (prop->scan_ter_config.search_analog ==     1) strncat(msg,"ENABLE  ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", prop->scan_ter_config.search_analog);
     break;
    #endif /*     Si2183_SCAN_TER_CONFIG_PROP */
#endif /* TERRESTRIAL_FRONT_END */

     default : STRING_APPEND_SAFE(msg,1000,"Unknown property code '0x%06x'\n", prop_code); return ERROR_Si2183_UNKNOWN_PROPERTY; break;
  }
  return NO_Si2183_ERROR;
}
/***********************************************************************************************************************
  Si2183_L1_FillPropertyStringText function
  Use:        property text retrieval function
              Used to retrieve the property text for a selected property.
  Parameter: *api      the Si2183 context
  Parameter: prop_code the property Id (used to know which property to use)
  Parameter: separator the string to use between fields (often either a blank or a newline character)
  Parameter: msg       the string used to store the resulting string
                       It must be declared by the caller with a size of 1000 bytes
  Returns:    NO_Si2183_ERROR if successful.
 ***********************************************************************************************************************/
void          Si2183_L1_FillPropertyStringText(L1_Si2183_Context *api, unsigned int prop_code, const char *separator, char *msg) {
  Si2183_L1_PropertyText (api->prop, prop_code, separator, msg);
}
/***********************************************************************************************************************
  Si2183_L1_GetPropertyString function
  Use:        current property text retrieval function
              Used to retrieve the property value from the hardware then retrieve the corresponding property text.
  Parameter: *api      the Si2183 context
  Parameter: prop_code the property Id (used to know which property to use)
  Parameter: separator the string to use between fields (often either a blank or a newline character)
  Parameter: msg       the string used to store the resulting string
                       It must be declared by the caller with a size of 1000 bytes
  Returns:    NO_Si2183_ERROR if successful.
 ***********************************************************************************************************************/
unsigned char Si2183_L1_GetPropertyString     (L1_Si2183_Context *api, unsigned int prop_code, const char *separator, char *msg) {
    int res;
    res = Si2183_L1_GetProperty2(api,prop_code);
    if (res!=NO_Si2183_ERROR) { STRING_APPEND_SAFE(msg,1000, "%s",Si2183_L1_API_ERROR_TEXT(res)); return res; }
    Si2183_L1_PropertyText(api->prop, prop_code, separator, msg);
    return NO_Si2183_ERROR;
}
#endif /* Si2183_GET_PROPERTY_STRING */








