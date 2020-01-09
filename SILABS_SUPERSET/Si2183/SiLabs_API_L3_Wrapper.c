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
/*************************************************************************************************************/
/*                                  Silicon Laboratories                                                     */
/*                                  Broadcast Video Group                                                    */
/*                                  SiLabs API Functions                                                     */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains all API functions for a SiLabs digital TV demodulator Evaluation board        */
/*-----------------------------------------------------------------------------------------------------------*/
/* Change log: */
/* Last  changes:

  As from V2.8.0:
    <improvement>[CNR] Correction of CNR reported by demodulator in DVB-T and ISDB-T to better match gaussian CNR level of test equipment.
    <improvement>[SAT/Unicable/Swap] Adding swap_detection_done flag in SILABS_FE_Context (only for SAT and Unicable).

  As from V2.7.9:
    <new_feature>[TER/FW_load] Adding SiLabs_API_Store_TER_TUNER_FW, to allow loading the TER tuner FW from a file
    <compatibility>[SAT/A8297] Defining A8297_COMPATIBLE items in c file (now defined as extern in header file)
    <compatibility>[compiler/warnings] In SiLabs_API_SAT_PLS_Init: moving trace line after all declarations.
    <compatibility>[SSI/SQI] In SiLabs_API_Demod_status_selection: always calling Si2183_L1_SSI_SQI. The drawback is that it will raise an API error with legacy chips.
      This avoid having a difficult to read/support code in the future, when no legacy chips will be used.
    <improvement>[SAT/comments] In SiLabs_API_SAT_read_diseqc_reply comments: removed one unwanted line.
    <cleanup>[SAT/Unicable] Removing unused 'Unicable install'
    <improvement>[TERACOM/BER] In SiLabs_API_Demod_status_selection: Removing dynamic BER settings.
      This is not required anymore to pass Nordig(i.e. Teracom)/DBook tests due to test specification changes
    <new_feature>[TER/DTVTune] Adding SiLabs_API_TER_Tuner_DTV_Tune (For test purposes).
      In DTV mode, tuning should be done via the L2, not directly from L3. This will be used FOR TESTING in Japan on cable networks used for ISDB-T reception.
    <new_feature>[TER/Tuner] Adding SiLabs_API_TER_Tuner_SetProperty and SiLabs_API_TER_Tuner_GetProperty, for test purpose
    <new_feature>[SAT/Unicable] Adding SiLabs_API_SAT_Random_Delay_Init and SiLabs_API_SAT_Random_Delay_Shift to compute the delays required by DiSEqC 1.1 in the DiSEqC collision detection algorithm

  As from V2.7.8:
    <correction>[SAT/UnicableII] In SiLabs_API_SAT_Unicable_Config: setting front_end->Si2183_FE->unicable_mode (new member of Si2183_L2_Context) to allow dynamic selection of the SAT scan bandwidth.
    <correction>[return_value] In SiLabs_API_SAT_Unicable_Swap_Detect: always returning front_end->Si2183_FE->unicable_spectrum_inversion.
    <correction>[Si2165D/C_N]  In SiLabs_API_Demod_status_selection: avoid rounding to 100 in c_n_100 (issue for Si2165D only).
    <compatibility>[Legacy/ROMID/0] In SiLabs_API_Demod_status_selection: only calling Si2183_L1_DD_SSI_SQI for ROM IDs > 0, to avoid an error message in the traces (no impact on the final result).
    <compatibility>[compiler/warnings] In SiLabs_API_Set_Index_and_Tag: tag defined as const char*.
    <compatibility>[compiler/warnings] In SiLabs_API_TS_Mode: ts_mode defined as unsigned int.
    <compatibility>[compiler/warnings] In SiLabs_API_SAT_Unicable_Swap_Detect: lock_end_ms defined as signed int.
    <compatibility>[compiler/warnings] In SiLabs_API_SAT_Gold_Sequence_Init: k defined as signed int.
    <compatibility>[compiler/warnings] In Silabs_API_Test: target, cmd and sub_cmd defined as const char*.
    <compatibility>[compiler/shadowing] In Silabs_API_Test: removing FE_Status and custom_status, now defined at a higher level.

  As from V2.7.7:
   <improvement>[status/uncors] In SiLabs_API_lock_to_carrier: resetting the uncorrs count if lock succeeds.
   <improvements>[standby/tuners] Adding SiLabs_API_SAT_Tuner_Standby and SiLabs_API_TER_Tuner_Standby (only required for DUALS/TRIPLE/QUAD when all frontends are going to standby)
   <improvement>[SAT/Band_polar] In SiLabs_API_lock_to_carrier: storing polarization and band in L3 context for proper display even in Unicable mode.
   <new_feature>[SSI/RSSI_offset]
      Adding TER_RSSI_offset and SAT_RSSI_offset to context, to allow taking into account possible offset on the RF paths (in 1 dB steps)
      In SiLabs_API_Demod_status_selection: Adding TER_RSSI_offset/SAT_RSSI_offset to tuner RSSI
      In Silabs_API_Test: Adding options 'ter_rssi_offset' and 'sat_rssi_offset' to control the RSSI offsets
   <new_feature>[TER/Active_Loop_Through] Adding SiLabs_API_TER_Tuner_Loop_Through to allow controlling the active loop through state with TER tuners supporting this feature.
   <new_feature>[SAT/Unicable] Adding SiLabs_API_SAT_Unicable_Position to allow selecting 'position A/B' using the L3 API (only for Unicable mode).
   <new_feature>[SAT/Unicable[ Adding SiLabs_API_SAT_Unicable_Swap_Detect to detect the value which should be used as unicable_spectrum_inversion in the frontend settings.
      NB: It can also be used to detect the value of spectrum_inversion (for non-Unicable mode), but this is normally easy to detect via a normal lock on a DVB-S signal.

  As from V2.7.6:
   <new_feature>[SAT/RDA16110SW] Adding SiLabs_API_SAT_Tuner_SelectRF to allow controlling the RF switch in RDA5816SD/RDA16110SW

  As from V2.7.5:
   <improvement>[Standards/definitions]
     Adding SILABS_SLEEP(100) and SILABS_OFF(200) cases in Silabs_standardCode and Silabs_Standard_Text
   <new_feature>[BER/monitoring]
     Duplicating status->ber (float) and status->ber_mant/status->ber_exp information in status->ber_count/status->ber_window.
     This closely matches some middleware expectations.
   <new_feature>[ISDB-T/monitoring]
     Adding SiLabs_API_TER_ISDBT_Layer_Info
     Adding layer-specific ISDB-T status fields
     In SiLabs_API_TER_ISDBT_Monitoring_mode, adding a 'loop mode' option (0xABC) to update the status information for all layers.
     In SiLabs_API_Demod_status_selection, updating ISDB-T Layers status in 'loop mode', when they are in use.
       NB: When using all 3 layers, at least 3 calls to SiLabs_API_Demod_status_selection are required to have all status fields updated.
     In SiLabs_API_Text_status_selection: printing all 3 ISDB-T layers status
   <compatibility>[ISDB-T/status]
     In Custom_coderateCode: simplifying the code to deal with ISDB-T code rates.
   <compatibility>[traces/on/off]
     In SiLabs_API_FE_status_selection: returning 'res' with value matching the lock state
   <compatibility>[No_TER] Only declaring i when needed, to avoid compilation errors when not compiling for TER

  As from V2.7.4:
   <new_part>[LNB/TPS65233] Adding compatibility with Texas Instruments TPS65233 SAT LNB controller
   <improvement>[SAT/Unicable] Redefining SiLabs_API_SAT_Unicable_Config to add unicable_spectrum_inversion

  As from V2.7.3:
    <new_feature>[DVB-S2/roll_off] In SiLabs_API_Demod_status_selection: updating roll_off in DVB-DS2
    <new_feature>[SAT/Unicable]
      Adding SiLabs_API_SAT_Unicable_Config to configure Unicable from L3
      In SiLabs_API_SAT_Unicable_Install: adding a trace indicating that using SiLabs_API_SAT_Unicable_Config is preferred to enable Unicable.
      In SiLabs_API_SAT_Unicable_Uninstall: not changing front_end->unicable->installed anymore
      The new behavior is:
        SiLabs_API_SAT_Unicable_Config allows selecting the unicable mode (unused/1/2) in the Unicable context
        SiLabs_API_SAT_Unicable_Install and SiLabs_API_SAT_Unicable_Uninstall control front_end->lnb_type to select Unicable or normal tuning at L3 level.
    <improvement>[Compatibility/No_Traces] In SiLabs_API_FE_status_selection: moving declaration of 'res' to allow compiling without SiTRACES
    <improvement>[Traces]
      In SiLabs_API_FE_status_selection:   Calling SiLabs_API_Text_status_selection with the same status_selection as the one used to refresh the statuses
      In SiLabs_API_Text_status_selection: Tracing only items selected by status_selection
      In SiLabs_API_Set_Index_and_Tag:     Also setting the tag for LNB controllers
    <improvement>[SAT/LNB]
      In SiLabs_API_lock_to_carrier: in SAT, enabling/disabling i2c access to the LNB chips before calling SiLabs_API_SAT_voltage
        This is useful in case the LNB controllers are not on the main I2c bus.
    <improvement>[comments] In SiLabs_API_Channel_Seek_Init comments: correcting freq min/max text for local blindscan
      SiLabs_API_Channel_Seek_Init (front_end, freq-4850000, freq+3150000,8000000, 8000000, 3500000, 7500000, 0, 0, 0, 0);'
    <improvement>[DVB-S2/status]
       In SiLabs_API_Get_Stream_Info: translating isi_constellation and isi_code_rate values to match L3 definitions for constellation and code_rate.

  As from V2.7.2:
    <correction>[S2X/flag]   In SiLabs_API_Demod_status_selection: setting status->s2x correctly.
      The flag was inverted in most cases, and 32APSK cases were missing.
   <new_feature>[DVB-S2/PLS/Init] Adding SiLabs_API_SAT_PLS_Init to allow using other non-standard sequences
   <new_feature>[DVB-S2/PLS/ISI]  In Silabs_API_Test: adding options to test DVB-S2/ISI and DVB-S2/PLS
   <new_part>[LNB/A8304] Adding compatibility with Allegro A8297 SAT LNB controller
   <improvement>[LNB/LNBH25/LNBH26] Transient overcurrent detection with LNBH25/LNBH26 can make it difficult to control LNBs.
      Since this occurs when changing the voltage, the following counter measures are applied:
      In SiLabs_API_SAT_voltage: calling the status function for LNB controllers allowing this feature.
        If a transient overload happens, the traces will indicate it, such that the appropriate measures can be taken (the detection threshold is configurable using external components).
   <improvement>[LOG_Function] Silabs_Log10_10000 improved to work better between 1 and 2
   <improvement>[Debug/Spectrum/Traces]
     In SiLabs_API_SAT_voltage: storing the LNB voltage value in misc_infos[ 7: 0]
     In SiLabs_API_SAT_tone:    storing the LNB tone    value in misc_infos[11: 8]

  As from V2.7.1:
    <new_feature>[DVB-T2/C2/MPLP/Group_id] Adding SiLabs_API_Get_PLP_Group_Id, to allow retrieving the group_id in DVB-T2 or DVB-S2 with multiple PLPs.
    <improvement>[Status/DVB-T/coderate]
      In SiLabs_API_Demod_status_selection: coping status->coderate_hp/status->coderate_lp to status->coderate depending on status->stream,
        in case the application only uses status->coderate.
      In SiLabs_API_Text_status_selection: Using status->coderate also when in DVB-T.
    <improvement>[Comments]
      In SiLabs_API_Demod_status_selection: better comment when setting initial status->num_plp value.

  As from V2.7.0:
    <new_feature>[Config/driveTS] Adding SiLabs_API_TS_Strength_Shape function to allow configuring the TS drive from the configuration macro.
      This is useful when different platforms don't use the same TS drive settings.
    <improvement>[Status/DVB-T-T2_only]
      In Silabs_constelCode: simplifying constellation switch to always return the expected value.
      In Custom_constelCode: simplifying constellation switch to always return the expected value.
        The previous version only returned the proper values for DVB-T when compiled with DVB-C compatibility (QAM16 and QAM64) and DVB-S compatibility (QPSK).
    <improvement>[Status/ISDB-T]
      In Silabs_constelCode:  Adding DQPSK case (for ISDB-T).
      In Custom_constelCode:  Adding DQPSK case (for ISDB-T).
      In Silabs_Constel_Text: Adding DQPSK case (for ISDB-T).

  As from V2.6.9:
    <improvement>[Unicable/I2c] In SiLabs_API_HW_Connect: removing 'connect' for unicable->i2c (not used)
    <improvement>[Config/TS]    In SiLabs_API_HW_Connect: improved comments. Now with the possibility to keep parameters untouched using values different from 0 or 1
    <improvement>[TS/GPIF]      In SiLabs_API_TS_Mode: Improved GPIF control, to avoid testing GPIF and FIFO_SLAVE modes with single and dual EVBs. (only available whith the Cypress USB interface)

  As from V2.6.8:
    <improvement>[T2/C2/MPLP] In SiLabs_API_Select_PLP: now testing modulation against dd_status.modulation.
      This allows using SiLabs_API_Select_PLP in 'AUTO_DETECT/AUTO_T_T2' mode.
    <new_feature>[Config/TS] Adding SiLabs_API_TS_Config function to allow configuring the TS from the configuration macro.
      This is useful when different platforms don't use the same TS settings.

  As from V2.6.7:
    <improvement>[dual/triple/quad/Broadcast_i2c] In SiLabs_API_Demods_Broadcast_I2C: setting Silabs_multiple_front_end_init_done when done, to avoid calling the kickstart function
      when using the broadcast_I2C mode.
    <improvement>[Legacy/SAT_tuner_init] In SiLabs_API_SAT_Tuner_Init: setting SAT_tuner_init_done. NB: this function is normally not used. It's kept for compatibility with some customer MW.
    <improvement>[Legacy/TER_tuner_init] In SiLabs_API_TER_Tuner_Init: setting TER_tuner_init_done. NB: this function is normally not used. It's kept for compatibility with some customer MW.

  As from V2.6.6:
    <correction>[SSI/C/Not_locked/legacy] In SiLabs_API_SSI_SQI: correction constel selection to use 256QAM when not locked.
      NB: This function is only used for 'legacy' products not supporting Si2183_L1_DD_SSI_SQI (FW computed SSI).
      No impact on current products.
    <improvement>[RSSI/SAT] In SiLabs_API_Demod_status_selection: checking return value of SAT_TUNER_RSSI_FROM_IFAGC against -1000 (instead of -1), since -1 can be a valid value.
      NB: This requires an update to the SAT tuner wrapper to V0.2.4, where SAT_TUNER_RSSI_FROM_IFAGC returns -1000 when not supported by the current SAT tuner.

  As from V2.6.5:
    <correction>[RSSI/SAT] In SiLabs_API_Demod_status_selection:
      Checking that SAT_TUNER_RSSI_FROM_IFAGC supports the current SAT tuner before calling it.
      If not, keep the status->RSSI value obtained from SiLabs_SAT_Tuner_Status.
      NB: SAT_TUNER_RSSI_FROM_IFAGC has been introduced with V2.1.0
    <correction>[SSI/C/C2/S/S2/Not_locked] In SiLabs_API_Demod_status_selection:
      Always calling Si2183_L1_DD_SSI_SQI when checking FE_QUALITY, even when not locked. When not locked, SQI will always be 0 but SSI will provide a useful info anyway.
      Previous versions called SiLabs_API_SSI_SQI for C/C2/S/S2 in this case, and the returned SSI value is different from the value returned by Si2183_L1_DD_SSI_SQI.
    <compatibility>[Linux/adapter_nr] In SiLabs_API_SAT_Select_LNB_Chip: Calling L0_SetAddress to set adapter_nr as add[15:8] (only useful if LINUX_I2C_Capability)
    <compatibility>[LINUX/ST_SDK2] Changing type from CUSTOM_Coderate_Enum to signed int in Silabs_coderateCode.

  As from V2.6.4:
    <correction>[S2X/Stream] In SiLabs_API_Select_Stream: stream_id type changed to 'signed   int' to allow
      selection of the 'auto' mode using -1.
    <correction>[S2X/flag]   In SiLabs_API_Demod_status_selection: Adding missing 'break' lines in constellation/code_rate code
      used to set status->s2x.

  As from V2.6.3:
    <correction>[RSSI/SAT/legacy] In SiLabs_API_Demod_status_selection:
      Using status->RSSI instead of status->rssi in calls to SiLabs_API_SSI_SQI.
      Calling SiLabs_API_SSI_SQI in SAT only when DD_SSI_SQI is not supported.
      Only useful under the following combined conditions:
        Using floats is allowed
        Demodulator not supporting DD_SSI_SQI for all standards (legacy demodulators only)
        SAT reception
        SAT tuner with SAT_TUNER_RSSI_FROM_IFAGC capability (leading to status->RSSI being different from status->rssi)
    <new_feature>[DVB-S2X/status] In SiLabs_API_Demod_status_selection: storing some DVB-S2X specific values in the status.
    <improvement>[LINUX/ST_SDK2]
      Changing type from CUSTOM_Standard_Enum to signed int for standard in several functions.
        This is because the ST SDK2 enums used for 'standard' use more than 8 bits, so won't fit into a 'char'.
      In SiLabs_API_Text_status_selection: not using divisions, using only int values for freq and symbol rate, since this is not
        allowed with ST SDK2.

  As from V2.6.2:
    <correction>[FE_status_selection/flags] In SiLabs_API_FE_status_selection: correcting test on flags to make it work as expected.
    <new_part>[LNB/A8304] Adding compatibility with Allegro A8304 SAT LNB controller
    <compatibility>[Xtal/Cap/SUPERSET] Adding SiLabs_API_XTAL_Capacitance to configure the XTAL capacitance value when using a XTAL as the clock source
      The start_clk.tune_cap default value is set in Si2183_L2_SW_Init. Using SiLabs_API_XTAL_Capacitance is useful if different values need to be used
       for different platforms (i.e. when using Xtals with different internal capacitance). Only implemented with Si2183 (SUPERSET).
    <compatibility>[NO_FLOATS] In SiLabs_API_Text_status_selection: changing BW and SR print-out to avoid issues if no floats are allowed.
    <compatibility>[NO_FLOATS] In SiLabs_API_SSI_SQI_no_float: removing traces used during function development, to avoid trace issue if no floats are allowed.
    <compatibility>[Si2165D/ber] In SiLabs_API_Demod_status_selection: setting status->ber by default at '1'. (This is only used with Si2165D)
    <improvement>[DVB-T2/FFT_mode_1k] Adding code for FFT_MODE_1K in Silabs_fftCode/Custom_fftCode/Silabs_FFT_Text
    <improvement>[Si1256D/DVB_T/QPSK] In Silabs_constelCode, Custom_constelCode and : adding DVB-T qpsk case.

  As from V2.6.1:
    <compatibility>[SILABS_SUPERSET/ISDB-T] Adding tags to allow compilation with ISDB-T only in several functions:
     Silabs_fftCode / Silabs_giCode / Custom_fftCode / Custom_giCode
    <compatibility>[SILABS_SUPERSET/SAT_ONLY] Adding tags in SiLabs_API_Broadcast_I2C to allow compiling without TER_TUNER_SILABS
    <compatibility>[SILABS_SUPERSET/SAT_ONLY] Adding tags in SiLabs_API_bytes_trace to allow compiling without TERRESTRIAL_FRONT_END

  As from V2.6.0:
    <new_feature>[TER_Tuner/GPIOS] Adding SiLabs_API_TER_Tuner_GPIOs. Requires having the TER tuner init done, and the i2c pass-through to br controlled.
    <correction>[NO_MATHS/LOG] In Silabs_Log10: Correction of an issue for values between 100 and 199, which all returned as '2'.
    <compatibility>[Linux/Ubuntu] In SiLabs_API_SW_Init and SiLabs_API_Set_Index_and_Tag: minor changes to avoid compiling issues with Linux.
    <compatibility>[VisualStudio] In Silabs_API_TS_Tone_Cancel: moving lines to have all declarations before assignments. Adding a trick to avoid 'set but not used' warning.
    <compatibility>[SILABS_SUPERSET/NO_T2] In SiLabs_API_TER_AutoDetect: adding tags to allow compiling with T and no T2.

*/
/* Older changes:
  As from V2.5.9:
    <compatibility>[Tizen/int&char] explicitly declaring all 'int as 'signed int' and all 'char' as 'signed char'.
      This is because Tizen interprets 'int' as 'unsigned int' and 'char' as 'unsigned char'.
      All other OSs   interpret 'int' as 'signed   int' and 'char as 'signed char', so this change doesn't affect other compilers.
      To compare versions above V2.5.8 with older versions:
        Do not compare whitespace characters
        Either filter 'signed' or replace 'signed   int' with 'signed' and 'signed   char' with 'char' in the newer code first.
          (take care to use 3 spaces in the string to be replaced).
    <new_feature>[DVB-S2X/Gold_Sequences] Adding SiLabs_API_SAT_Gold_Sequence_Init to compute a Gold Sequence initialisation value for a given Gold Sequence index.
    <correction>[export/tags] Correcting tag in SiLabs_API_Get_AC_DATA for proper export without DVB-C2.

  As from V2.5.8:
    <new_feature>[Broadcast_I2c/Multiples/Si2183]
      Adding SiLabs_API_Demods_Broadcast_I2C to load FW in demodulators using the 'broadcast i2c' mode.
      Adding SiLabs_API_Broadcast_I2C to load FW in TER tuners then demodulators using the 'broadcast i2c' mode.
      In SiLabs_API_TER_Broadcast_I2C: Filling a table with the demodulator's TER_Tuner_init_done flags, and setting them all to 1 if TER tuner FW downolad is ok.
    <new_feature>[ISDB-T/AC_data]
      In SiLabs_API_Get_AC_DATA: second release of this function after testing and adding the filtering flag.
    <new_feature>[SAT/Unicable_II]
      In SiLabs_API_SW_Init:
        Adding SiLabs_API_SAT_read_diseqc_reply pointer in call to SiLabs_Unicable_API_Init (If UNICABLE_II_COMPATIBLE is defined)
    <new_feature>[DVB-C2/Seek]:
      In SiLabs_API_Demod_status_selection:
        storing DVB-C2 system information in status
      In SiLabs_API_Text_status_selection:
        removing duplicated lines in text status
    <correction>[DVB-C2]
      In SiLabs_API_Select_PLP:
        Selecting DVB-T2 PLP only in DVB-T2
        Correcting order of fields when selecting DVB-C2 PLPs.
    <correction>[typo/Text_Status]
      In SiLabs_API_Text_status_selection:
        Replacing 'isdbt_system_id by t2_system_id when in DVB-T2
    <correction>[typo/traces]
      In SiLabs_API_Select_Stream:
        Replacing 'PLP' by 'ISI stream' in error trace after calling Si2183_L1_DVBS2_STREAM_SELECT
    <improvement>[traces/typo] In SiLabs_API_Demod_status_selection: correction typo in trace (incorrect function name)
    <improvement>[traces/status]
      In SiLabs_API_Demod_status_selection: returning status_selection, to be used to fill the text status.
        (the status_selection bits may be changed depending on the lock state)
      In SiLabs_API_FE_status_selection: calling SiLabs_API_Text_status_selection and tracing the resulting string (only when SiTRACES are declared).
        This is useful to check the front_end status in traces, we already asked several customer to add similar code, so now it's native.

  As from V2.5.7:
    <new_feature>[ISDB-T/AC_data] Adding SiLabs_API_Get_AC_DATA function to retrieve ISDB-T AC data.
    <improvement>[kickstart] In SiLabs_API_Demods_Kickstart: directly setting demods to their final clock input for all demodulators (previous version only matched Si2183)

  As from V2.5.6:
    <improvement>[DVB_S2/status]   In SiLabs_API_Demod_status_selection: storing status->num_is and status->isi_id when locked in DVB_S2,
                                     setting status->s2x to 1 if locked in a DVB-S2X MODCODE combination
                                   In SiLabs_API_Text_status_selection: filling text with status->num_is and status->isi_id values when locked in DVB_S2

    <improvement>[DVB_S2/NO_S2X]   In Custom_constelCode: moving S2 constellation to have them kept when DEMOD_DVB_S2X is not defined.
    <improvement>[SLEEP/ANALOG]    In SiLabs_API_lock_to_carrier: returning 1 after calling SiLabs_API_switch_to_standard in ANALOG or SLEEP modes.
    <improvement>[SOC_EVB/Si2165D] In SiLabs_API_Demod_status_selection for Si2165D: setting ber_mant/ber_exp based on status->ber, to allow proper BER display
     using SiLabs_API_Text_status_selection.
    <improvement>[GPIF/Cypress] In SiLabs_API_TS_Mode: not using the result of the check on '-gpif', since it doesn't return the proper value.
    <new_feature>[Cypress/streaming] In SiLabs_API_TS_Mode: allowing SILABS_TS_STREAMING option, to configure TS streaming independently from the demod settings
    <new_feature>[SAT/TAG] In Silabs_API_Test: adding 'sat_tag' option

  As from V2.5.5:
    <new_feature>[SILABS_SUPERSET] Adding tags to allow compilation for TER-only/SAT-only/TER+SAT based on the superset code.

  As from V2.5.3:
    <new_feature>[Cypress/TS_SLAVE] In SiLabs_API_TS_Mode: Adding code to support SILABS_TS_SLAVE_FIFO (parallel TS retrieved using Cypress chip)
    <improvement>{sw_options/LNBH29] In SiLabs_API_SAT_Possible_LNB_Chips: Adding text for LNBH29.
    <new_feature>[Cypress/process]  In Silabs_API_Test: Adding acess to L0_Cypress_Process
    <new_part>[LNB/A8302] Adding compatibility with Allegro A8302 SAT LNB controller
    <new_feature>[LNB/index] Adding SiLabs_API_SAT_LNB_Chip_Index, a function used to select the portion of
        an LNB controller is use. (set to 0 or 1 depending on the case). Compatible with LNBH26 and A8302.
    <new_feature>[SAT_TUNER/sub] Adding SiLabs_API_SAT_Tuner_Sub, a funcitonused to select the sub-portion of a dual SAT tuner

  As from V2.5.2:
    <correction>[ATV/TEXT status] In SiLabs_API_TER_Tuner_ATV_Text_status: enabling/disabling i2c to execute TER tuner status
    <improvement>[SAT/LNB] In SiLabs_API_SAT_voltage: calling the L1_xxxx_InitAfterReset function for LNBH25, LNBH26 and LNBH29.
       (other LNB chips don't need this, since all registers are written for each call)
    <new_feature>[TS_spurs]
      Adding SiLabs_API_Get_TS_Dividers to retrieve the TS clock dividers (only supported by Si2183 with recent FWs (above 5_0b13) )
      Adding Silabs_API_TS_Tone_Cancel  to activate the Tone cancellation in the TER tuner (only supported by Si2190B initially)
    <improvement>[Duals/SiLabs_EVBs] In SiLabs_API_SW_Init: surrounding ts_mux related code by USB_Capability, since it's only valid on some SiLabs EVBs

  As from V2.5.1:
    <correction>  [status/BER] In SiLabs_API_Demod_status_selection: Swapping dd_ber_resol exp and mant for Si2164/83 for exp=7 and mant=1 (in place of exp=1 mant=7)
    <improvement>[TERACOM/BER] In SiLabs_API_Demod_status_selection: Changing BER settings when locked in DVB-T (1;6) vs other standards (1;7).
              This is to improve measurement accuracy for BER criteria.
    <improvement> [status/return value] In SiLabs_API_Demod_status_selection: returning 1 when status function meets no problem.
    <new_feature>[TER_Tuner/Config]
      Adding SiLabs_API_TER_Tuner_FEF_Input to allow configuration of the TER tuner FEF input. This needs to be added to the configuration macros.
      The default value is '1' to select GPIO1 on the TER tuner side.
    <improvement>[cleanup] In SiLabs_API_TER_Tuner_ATV_Tune: removing invert_spectrum
   <improvement/compatibility>
	   In SiLabs_API_SAT_Possible_LNB_Chips: Setting i to avoid warning when not used.
     In SiLabs_API_Select_PLP: Setting plp_id and plp_mode to avoid warning when not used.
     In SiLabs_API_TER_Tuner_ATV_Tune: Setting all variables to avoid warnings when not used.
     In Silabs_API_Test: using standard to avoid warning when not used.
    <correction>  [constel/DVB-S2X] In Silabs_constelCode and Custom_constelCode: Adding DVB-S2-X specific constellations.

  As from 2.5.0:
   <improvement>[status/ISDBT] Adding partial_flag in _CUSTOM_Status_Struct
    In SiLabs_API_Demod_status_selection: storing partial flag information in status->partial_flag.
   <new_feature>[Test_Pipe/init_ok] In Silabs_API_Test: adding 'init_ok' to know if demod init is done
   <new feature>[TER_Tuner/Config]
     adding SiLabs_API_TER_Tuner_Block_VCO2 and SiLabs_API_TER_Tuner_Block_VCO3 to allow configuration of
     the TER_Tuner block_VCO2_code and block_VCO3_code
   <new_feature>[I2C/Tuners_Direct] In SiLabs_API_XXX_Tuner_I2C_Enable/SiLabs_API_XXX_Tuner_I2C_Enable: using a special value (100) to allow
    having direct connection to tuners (without demod pass-through).
    API CONFIG in such case:
     SiLabs_API_TER_tuner_I2C_connection(front_end, 100);
     SiLabs_API_SAT_tuner_I2C_connection(front_end, 100);
   <new_feature>[Test_Pipe/LNBH26] In Silabs_API_Test: adding 'lnbh26' 'a_b' '0/1' option to select which LNB controller is used (LNBH26 is a dual)
   <new_feature>[CONFIG/tracing] In all configuration functions: storing all configuration fields in SILABS_FE_Context (to enable configuration checking after init).
      NB: This allows removing some previous code used to avoid compilation warnings, since all fields are not used.
      Adding SiLabs_API_Config_Infos. This function is useful to check the configuration parameters based on the related function name.
        Use "Full" for the function name to get the entire configuration.

  As from V2.4.9:
   <improvement/Duals> Adding demod_die in _CUSTOM_Status_Struct
    In SiLabs_API_Demod_status_selection: storing demod die information in status->demod_die.
    In SiLabs_API_Text_status_selection:  adding die information to status text.
   <typo/T2_lock_mode> In SiLabs_API_lock_to_carrier comments: T2_lock_mode is independent of num_lp.
     Parameter: T2_lock_mode        the DVB-T2 lock mode        (0='ANY', 1='T2-Base', 2='T2-Lite')
     <typo/ISDB-T> In SiLabs_API_lock_to_carrier comments: bandwidth_Hz is also used for ISDB-T
     Parameter: bandwidth_Hz        the channel bandwidth in Hz (only for DVB-T, DVB-T2, ISDB-T)
   <correction/Duals> In SiLabs_API_Demods_Kickstart: directly setting demods to their final clock input.
    NB: For duals (Si216x2), the clock source should not change between TER and SAT, and the clock should be 'always-on':
      In calls to SiLabs_API_TER_Clock/SiLabs_API_SAT_Clock: use identical settings and force 'clock_control = 1'.

  As from V2.4.8:
   <new_part/A8293/LNB_Supply> Compatibility with Allegro's A8293 (needs A8293_COMPATIBLE)

  As from V2.4.7:
   <improvement/Settings> In SiLabs_API_Demod_status_selection: Saving status->IFagc depending on the AGC in use.
                           Previous versions assumed that AGC1 for SAT and AGC2 for TER. This restriction doesn't apply anymore.
   <improvement/compatibility> Changing all C++ comments to C style
                               In SiLabs_API_SAT_Tuner_status:      setting sat_tuner by default to avoid compiler warnings.
                               In SiLabs_API_TER_Tuner_ClockConfig: setting tuner_ter by default to avoid compiler warnings.
                               In SiLabs_API_TS_Mode:               moving SiTRACE after all variables are declared.
                               In SiLabs_API_SAT_AutoDetectCheck :  moving SiTRACE after all variables are declared.
   <improvement/NO_FLOAT> Adding SiLabs_API_SSI_SQI_no_float and Silabs_Log10_10000 to enable SSI and SQI computing when
                            not done by FW and when using floats is not allowed.
   <correction/BER> In SiLabs_API_Demod_status_selection:
                       storing ber_exp+1 in status->ber_exp.
                       storing per_exp+1 in status->per_exp.
                       storing fer_exp+1 in status->fer_exp.
                    In rate_f_mant_exp: exp treated to match the changes in SiLabs_API_Demod_status_selection.
   <correction/RSSI/Si2167B> In SiLabs_API_Demod_status_selection: Calling SAT_TUNER_RSSI_FROM_IFAGC for Si2167B in SAT

  As from V2.4.6:
   <improvement>[TERACOM/BER] In SiLabs_API_Demod_status_selection: Changing BER settings when locked in DVB-T (5;8) vs other standards (1;7). ONLY for Si2183.
   <improvement>[DUALS/XTAL]  In SiLabs_API_Demods_Kickstart: Using TUNE_CAP_15P6 and CLK_MODE_XTAL to make sure demodulators are not pulling
    the clock input pin low.

  As from V2.4.4:
    <new_feature>[TER_Tuner/Config]
     Adding SiLabs_API_TER_Tuner_AGC_Input and SiLabs_API_TER_Tuner_IF_Output to allow configuration of the
       TER tuner IF output and AGC input
    <improvement>[STATUS/selection] In SiLabs_API_Demod_status_selection:
       Forcing flags to 1 if status_selection is 0x00, to allow compatibility for applications calling this
        function directly

  As from V2.4.3:
   <improvement> In SiLabs_API_TS_Mode: removing TS parallel shape setup for Si2183.
                  Only keeping values of '7070' for GPIF mode.
                  GPIF mode is only used with SiLabs EVBs and is never used together with serial or parallel.

  As from V2.4.2
   <correction> [Si2164A/Si2169B/Si2168B/DVBT2_C/N] In SiLabs_API_Demod_status_selection:
   Correctly setting status->c_n to dvbt2_status.cnr/4.0 for the related parts.
   <correction>[TS_Crossbar] TS crossbar feature now working (with duals with this capability) as from FW 4_ab4

  As from V2.4.1
   <improvement>[Si2167B] In Silabs_coderateCode/Custom_coderateCode: tags changed to allow export for Si21652B
   <new_feature> [ISDB-T/LAYER] Adding SiLabs_API_TER_ISDBT_Monitoring_mode property to select the layer used
    for BER, CBER, PER, and UNCOR monitoring in ISDB-T
   <improvement> [TUNER_STATUS] In SiLabs_API_FE_status_selection: only tracing RSSI and freq if tuner status has been done
               Not returning anymore if the standard is unknown, to allow AGC monitoring.

  As from V2.4.0:
   <new_feature> [tag/level] adding tag and level support for Si2167B and derivatives
   <improvement> [Unicable/Multi-Treading/Multiple frontends] In SiLabs_API_SAT_Tuner_Tune: removing I2C pass-through enable/disable.
    This is only called while tuning in Unicable, and the i2c pass-through is already enabled when calling this function.
    The change removes nested i2c pass-through enable/disable calls.
    This is generally not an issue, unless several tuners are using the same i2c address and the application is multi-threading.

  As from V2.3.9:
   <new_parts> Status updated for ISDB-T support

  As from V2.3.8:
    <new_feature> Using STRING_APPEND_SAFE macro (defined in Si_I2C V3.4.5) for Linux compatibility.

  As from V2.3.7:
    <new_parts> [Si2183] Adding Si2183 support
    <new_standard> [ISDB-T] Adding support for ISDB-T
    <new_feature> [DVB-S2X] Adding Constellation and code rate functions for DVB-S2X.
    <new_feature> [TAG/LEVEL] Adding definitions for TAG and level
                Adding SiLabs_API_Set_Index_and_Tag
    <new_feature> Using STRING_APPEND_SAFE macro (defined in Si_I2C V3.4.5) for Linux compatibility.

  As from V2.3.6:
    <correction> [LNBH29] In SiLabs_API_SAT_Select_LNB_Chip: using lnb_code 29 to select LNBH29
    <new_feature> [STATUS/SELECTION] Adding SiLabs_API_Demod_status_selection / SiLabs_API_FE_status_selection / SiLabs_API_Text_status_selection.
            The behavior when calling SiLabs_API_Demod_status / SiLabs_API_FE_status_ / SiLabs_API_Text_status is unchanged, since these call the new functions
              with the value '0x00' which means 'status all items'
            These can be used to status only a portion of the CUSTOM_Status_Struct, depending on a status_selection bit field, using the following bit flags:
              FE_LOCK_STATE     : demod_lock, fec_lock,  uncorrs, TS_bitrate_kHz, TS_clock_kHz
              FE_LEVELS         : RSSI, RFagc, IFagc
              FE_RATES          : BER, PER, FER (depending on standard)
              FE_SPECIFIC       : symbol_rate, stream, constellation, c/n, freq_offset, timing_offset, code_rate, t2_version,
                                  num_plp, plp_id, ds_id, cell_id, etc (generally one function called per standard).
              FE_QUALITY        : SSI, SQI
              FE_FREQ           : freq
    <new_feature> [SW_CONFIG] Adding SiLabs_API_Frontend_Chip / SiLabs_API_TER_tuner_I2C_connection / SiLabs_API_SAT_tuner_I2C_connection
            These will be used instead of direct access to the L3 context values.
            They also allow easier access from the top level, and allow configuring the GUI using script files.
    <improvement> [T2/C2/MPLP/SEEK] In SiLabs_API_Channel_Seek_Next: if locked, updating value of front_end->standard.
            This removes the need to call SiLabs_API_Demod_status to update this value, which is used when retrieving the plp_ids and ds_ids.
    <improvement> [portability] In SiLabs_API_SSI_SQI: moving code after all declarations, because this creates compilation errors with some compilers.
    <improvement> [portability/NO_FLOATS_ALLOWED] In status functions, store information as rate_mant/rate_exp for ber/per/fer,
              and use these instead of the double fields.
    <improvement> [renaming] SiLabs_API_TER_FEF_CONFIG renamed as SiLabs_API_TER_FEF_Config, for consistency with other configuration functions.
    <improvement> [traces] Adding dedicated trace messages to help trace wrapper function calls:
      'API CALL CONFIG' for SW configuration functions, formatted as in configurations macros.
            These will be useful to check the SW configuration in the traces, and create the corresponding configuration macros.
      'API CALL SEEK'   for scan-related functions
      'API CALL INIT'   for init-related functions
      'API CALL LOCK'   for lock-related functions
      'API CALL STATUS' for statusing functions
    <improvement> [DVB-T2] In SiLabs_API_Demod_status: statusing status->t2_system_id
    <improvement> [Si2164/ANALOG] In Silabs_standardCode: Adding 'ANALOG' value for Si2164.

  As from V2.3.5:
    <new_feature> [Si2164/SPI) Adding SiLabs_API_SPI_Setup (Only available with Si2164 derivatives as from today)
       CAUTION1: In any case, this requires updating the following item to support SPI download:
        - SiLabs_L0 source code. The SPI support functions also need to be ported to your platform(s)
       CAUTION2: When used with SiLabs EVBs, this requires updating the following items to support SPI download using the Cypress chip:
        - Cypress FW
        - Cypress DLL
      Adding SiLabs_API_SPI_Setup
    <improvement> [code_checkers] In text-oriented functions using sprintf:
      Replacing sprintf by snprintf with a max size at 1000, as this is safer.
      The only constraint is that the text strings need to be declared with a minimum size of 1000 bytes.
      This should be enough to pass through code checkers.
    <comments> In SiLabs_API_TER_Tuner_ClockConfig: documenting input parameters use

  As from V2.3.4:
    <new_feature> [TER TUNER/Multi-frontend] Adding SiLabs_API_TER_Tuner_ClockConfig, to easily configure the TER tuner clock:
    int   SiLabs_API_TER_Tuner_ClockConfig    (SILABS_FE_Context *front_end, int xtal, int xout);
     xtal = 1: a Xtal is connected to and driven by the TER tuner.
     xtal = 0: a clock signal is connected to the TER tuner, which doesn't drive a Xtal.
     xout = 1: the clock is going out of the TER tuner.
     xout = 0: no  clock is going out of the TER tuner.

  As from V2.3.3:
    <new feature> [handshake] Adding SiLabs_API_Handshake_Setup, to easily control the handshake parameters from the wrapper level
    <new feature> [Si2164] Adding SiLabs_API_TER_T2_lock_mode, to select the T2 lock mode. It can be used to select the T2 lock mode during channel Seek.
                   This avoids the need to add a parameter to Seek_Init

  As from V2.3.2:
    <new feature> [Si21x8 tuners] Adding SiLabs_API_TER_Broadcast_I2C, useful to enable the broadcast i2c feature (only available with Si21x8B tuners)
    <improvement> [AUTO_T_T2] In SiLabs_API_Demod_status: setting front_end->standard to match status->standard when locked.
                   This is useful for SiLabs_API_Get_PLP_ID_and_TYPE when in AUTO_T_T2 and locked on a T2 signal:
                    if front_end->standard is left as 'SILABS_DVB_T' the function returns 0 while it needs to call Si216x_L1_DVBT2_PLP_INFO
    <new feature> [MCNS] In SiLabs_API_Demod_status: adding MCNS support

  As from  V2.3.1:
    <correction>  In SiLabs_API_TS_Mode:
     Correcting the 'SILABS_TS_TRISTATE' case to use the 'TRISTATE' mode
     Adding  SILABS_TS_OFF in CUSTOM_TS_Mode_Enum structure
     Adding 'SILABS_TS_OFF' case for Si2164/Si2167B/Si2169A
    <correction> In SiLabs_API_DEMOD_Status:
      Adding the SILABS_MCNS case
    <new feature> Adding 'int clock_control' to SiLabs_API_TER_Clock and SiLabs_API_SAT_Clock prototypes.
      This is used for multi-frontends applications when a tuner's clock is forwarded to another frontend.
        In this case it needs to be 'ALWAYS_ON'.
        To keep the previous behavior, use '2' (i.e. the 'MANAGED' mode)
      Adding the corresponding code in:
       SiLabs_API_TER_Clock_Options/SiLabs_API_TER_Clock
       SiLabs_API_SAT_Clock_Options/SiLabs_API_SAT_Clock
    <new feature> In SiLabs_API_SAT_Clock_Options: adding Si2167B
    <new_feature> Adding t2_version monitoring and related functions

  As from V2.3.0:
    Reverting changes to constellation type in SiLabs_API_lock_to_carrier function, as this forbids using the value of '-1' as SILABS_QAMAUTO.
    Using 'unsigned char constellation' broke the DVB-C AUTO qam capability.

    SiLabs_API_lock_to_carrier prototype is now:
    int   SiLabs_API_lock_to_carrier (SILABS_FE_Context *front_end,
                                       unsigned char standard,
                                                 int freq,
                                                 int bandwidth_Hz,
                                       unsigned char stream,
                                       unsigned int  symbol_rate_bps,
                                                char constellation,
                                       unsigned char polarization,
                                       unsigned char band,
                                                 int data_slice_id,
                                                 int plp_id,
                                       unsigned char T2_lock_mode);

  As from V2.2.9:
    In Custom_giCode / Silabs_giCode / Silabs_GI_Text:
     Adding 1/64 GI code handling (for DVB-C2)
    Adding lnb_chip_address to SILABS_FE_Context
    Adding SiLabs_API_TER_FEF_Options and SiLabs_API_TER_FEF_Config functions, to allow different FEF configuration depending on the frontend.
     This is required when using dual demodulators, where there are restrictions on MP_x and GPIOx pin usage.
    Changing SiLabs_API_SAT_Select_LNB_Chip function definition to add the lnb chip address.
     This is required for multi-frontend SAT applications.
    Changing SiLabs_API_switch_to_standard and SiLabs_API_set_standard function definitions to use 'unsigned char' instead of 'int' for standard.
    Changing SiLabs_API_lock_to_carrier function definition to use 'unsigned char' instead of 'int' for standard/stream/constellation/polarization/band/T2_lock_Mode.
     This avoids casting the related values to (unsigned int) within the functions.
      data_slice_id and plp_id are kept as 'int', as they may take a value of '-1' at wrapper level to select the corresponding 'auto' modes.
    In SiLabs_API_Demod_status:
     Adding one SiTRACE right after DD_STATUS, to trace the demod address (useful in multi-front-ends), the lock state and the standard.
    In SiLabs_API_Demod_status/SiLabs_API_SAT_Tuner_status/SiLabs_API_SAT_Tuner_Tune/SiLabs_API_TER_Tuner_Init/SiLabs_API_TER_Tuner_Text_status/SiLabs_API_TER_Tuner_ATV_Tune/SiLabs_API_TER_Tuner_Block_VCO:
     Changing I2C Enable/Disable calls to use the TER and SAT indirect i2c enable/disable calls, to allow tuner rssi statusing if INDIRECT_I2C_CONNECTION is used
     In SiLabs_API_SAT_Tuner_I2C_Enable and SiLabs_API_TER_Tuner_I2C_Enable:
      Replacing 'count' by 'fe_count', as 'count' may be a reserved word in some implementations.
     In SiLabs_API_SAT_Tuner_I2C_Enable and SiLabs_API_SAT_Tuner_I2C_Disable:
      Correcting code to properly connect the required i2c pass-through (previously only working for the SAT tuner on frontend 0 only).
    In SiLabs_API_FE_status:
     Directly tracing freq and tuner rssi before calling SiLabs_API_Demod_status.
    In SiLabs_API_Text_status:
     Adding config_code to text status. This is useful to knwo which frontend is statused in multi-frontend applications
    In SiLabs_API_SSI_SQI:
     Correcting SiTRACEs to display entire messages (last parameter wasn't displayed).
    In SiLabs_API_Select_PLP:
     Adding DVB-C2

  As from V2.2.8:
    Adding t2_base_lite in CUSTOM_Status_Struct
    Adding Silabs_T2_Base_Lite_Text function.
    In SiLabs_API_Text_status:
      Adding T2 base/lite text for T2
      Added MCNS in frequency display. MCNS text status didn't fill entirely due to this.
      Reduced code for frequency diplay.
    In SiLabs_API_TER_Clock / SiLabs_API_TER_AGC : adding tags to remove code for non-TER parts
    In SiLabs_API_SAT_Clock / SiLabs_API_SAT_AGC / SiLabs_API_SAT_Spectrum : adding tags to remove code for non-SAT parts

  As from V2.2.7:
    In SiLabs_API_Get_PLP_ID_and_TYPE: comparing standards value to SILABS_DVB_T2.
     (previously using Si2164_DD_MODE_PROP_MODULATION_DVBT2, which is incorrect at wrapper level).
    In SiLabs_API_TER_Clock: correction of Si2165 text related to clock source pin numbers
    In SiLabs_API_TER_AGC: correction of code used for Si2165

  As from V2.2.6:
    In SILABS_FE_Context structure: Adding config_code, used to store the i2c addresses of the TER tuner (bits[23:16]), the SAT tuner (bits[15:8]) the demod (bits[7:0]).
      This is used to know which path is controlled in multi-frontend applications, even when not tracing L0 bytes.
    In SiLabs_API_Channel_Seek_Next:   Adding T2_base_lite flag
    In SiLabs_API_Channel_Seek_Next:   Adding T2_base_lite flag  (indicates whether the locked signal is T2-Base or T2-Lite)
    In SiLabs_API_SAT_Select_LNB_Chip: Returning front_end->lnb_chip if OK, 0 otherwise. This compiles correctly for non-SAT products.
    In SiLabs_API_lock_to_carrier:     Adding T2_lock_mode flag (selects whether to lock on the T2-Base or T2-Lite signal (o='any'))
    In SiLabs_API_Tune:                Compatibility with Si2169B
    In SiLabs_API_Get_PLP_ID_and_TYPE: Adding C2 compatibility (for Si2164)
    Adding SiLabs_API_Get_DS_ID_Num_PLP_Freq function, for DVB-C2 Dataslice handling
    Adding SiLabs_API_Auto_Detect_Demods, for demodulators auto-detection.
    In SiLabs_API_TER_Tuner_Text_status:     Compatibility with SiLabs_TER_Tuner wrapper
    In SiLabs_API_TER_Tuner_ATV_Text_status: Compatibility with SiLabs_TER_Tuner wrapper
    In SiLabs_API_TER_Tuner_DTV_Text_status: Compatibility with SiLabs_TER_Tuner wrapper
    In SiLabs_API_TER_Tuner_ATV_Tune:        Compatibility with SiLabs_TER_Tuner wrapper
    In SiLabs_API_TER_Tuner_Block_VCO:       Compatibility with SiLabs_TER_Tuner wrapper
    WARNING: The latest TER tuners are NOT supported if not using the SiLabs_TER_Tuner wrapper
    In SiLabs_API_SSI_SQI: Adding C2 SSI SQI

  As from V2.2.5:
    In SiLabs_API_SSI_SQI: added DVB-C capability
    In SiLabs_API_Demod_status: calling SiLabs_API_SSI_SQI whenever SSI/SQI values haven't been set earlier.
      (the latest demodulators will have the SSI/SQI feature implemented in FW, and SiLabs_API_Demod_status will use the FW function if this is the case)
      Updating value of status->TS_clock_kHz for Si2165

  As from V2.2.4:
    In SiLabs_API_SAT_Tuner_status: compatibility with SILABS_SAT_TUNER_API

  As from V2.2.3:
    Compatibility with several LNBH controllers in the same application.
     Adding SiLabs_API_SAT_Possible_LNB_Chips and SiLabs_API_SAT_Select_LNB_Chip to allow easy selection of the LNB controller
    Si2167B compatibility with INDIRECT_I2C_CONNECTION
    Si2167B compatibility with TER and SAT configuration

  As from V2.2.2:
   SILABS_SAT_TUNER_API compatibility (the only way to work with Si2164):
    Adding SiLabs_API_Select_SAT_Tuner function, useful to select the SAT tuner for each demodulator
    Adding SiLabs_API_SAT_Address function, useful to set the I2C address of any TER tuner
    Adding SiLabs_API_SAT_Clock and SiLabs_API_SAT_AGC functions, to configure the clock paths (source, input, freq) and AGC.
     NB: This only works if matching functions are added to the demodulator code.
     NB: In this first version, these functions only support SI2164, to keep the 'legacy' device codes untouched

  As from V2.2.1:
   Adding INDIRECT_I2C_CONNECTION control, allowing tuner i2c connection via any demodulator.
    This is used for applications with multiple demodulators
    Adding SiLabs_API_SAT_Tuner_I2C_Enable, SiLabs_API_SAT_Tuner_I2C_Disable,
           SiLabs_API_TER_Tuner_I2C_Enable, SiLabs_API_TER_Tuner_I2C_Disable
      These functions are used for INDIRECT_I2C_CONNECTION control
   SILABS_TER_TUNER_API compatibility (the only way to work with Si2164):
    Adding SiLabs_API_Select_TER_Tuner function, useful to select the TER tuner for each demodulator
    Adding SiLabs_API_TER_Address function, useful to set the I2C address of any TER tuner
    Adding SiLabs_API_TER_Clock and SiLabs_API_SAT_Clock functions, to configure the clock paths (source, input, freq).
     NB: This only works if matching functions are added to the demodulator code.
     NB: In this first version, these functions only support SI2164, to keep the 'legacy' device codes untouched
   In SiLabs_API_TER_Tuner_ATV_Text_status: not implemented for SILABS_TER_TUNER_API (not sure it was ever used)
   In SiLabs_API_Demod_status: tracing front_end->chip code also in hexadecimal.

  As from V2.2.0:
   In SiLabs_API_SAT_Unicable_Install:
    For Si2167: Using ds_sequence_mode 'manual' to select 'no_gap' sequences in Unicable mode
   In SiLabs_API_SAT_Unicable_Uninstall:
    For Si2167: Using ds_sequence_mode 'auto' to select 'gap' sequences in Normal mode

  As from V2.1.9:
   In SiLabs_API_SAT_voltage, for LNBH25 (as this part requires an init):
    if (front_end->lnb_chip_init_done == 0) { front_end->lnb_chip_init_done = L1_LNBH25_InitAfterReset(front_end->lnbh25); }
   Adding SiLabs_API_SAT_Unicable_Uninstall, to allow easily switching between NORMAL and UNICABLE modes
   In SiLabs_API_SAT_Unicable_Install:
    Using new DD_DISEQC_PARAM property to select 'no_gap' sequences in Unicable mode
   In SiLabs_API_SAT_Unicable_Uninstall:
    Using new DD_DISEQC_PARAM property to select 'gap' sequences in Normal mode

  As from V2.1.8:
   In SiLabs_API_SAT_voltage, for LNBH25 (as this part requires an init):
    if (front_end->lnb_chip_init_done == 0) { front_end->lnb_chip_init_done = L1_LNBH25_InitAfterReset(front_end->lnbh25); }
   Adding SiLabs_API_SAT_Unicable_Uninstall, to allow easily switching between NORMAL and UNICABLE modes

  As from V2.1.7:
   Adding SiLabs_API_SAT_voltage and SiLabs_API_SAT_tone, to allow managing the voltage separately from the tone.
     This is mostly interesting for Unicable, where the tone is not used to select the band.
     It's used in the Unicable code as from 2013/03/14 (SVN3657) to save time when sending a Unicable message over the DiSEqC bus
   In SiLabs_API_SAT_prepare_diseqc_sequence:
     Adding Si2164/Si2167B/Si2169
   In SiLabs_API_SAT_trigger_diseqc_sequence:
     Adding Si2164/Si2167B/Si2169

  As from V2.1.6:
   Adding SiLabs_API_SAT_prepare_diseqc_sequence and SiLabs_API_SAT_trigger_diseqc_sequence, to allow preparing the DiSEqC
     message and sending it in two steps. This is required for Unicable with some demodulator (such as Si2167A), as
     otherwise the preparation takes too much time to stay within the Unicable Td specification (4 to 22 ms)
   In SiLabs_API_Demod_status:
    Added comments to differentiate the various status blocks
   In SiLabs_API_SW_Init:
    Adding initialization of two new functions for Unicable:
    SiLabs_API_SAT_prepare_diseqc_sequence
    SiLabs_API_SAT_trigger_diseqc_sequence
   In SiLabs_API_SAT_voltage_and_tone:
    tracing lnb_chip value

  As from V2.1.5:
   In Custom_constelCode and Silabs_Constel_Text: adding QAM1024 and QAM4096 (for DVB C2)
   In SiLabs_API_Demod_status:
    More DVB-C2 statuses

  As from V2.1.4:
   In Silabs_UserInput_demod:
    Compatibility with Si2185
   In SiLabs_API_Demod_status:
    Si2164: first statuses for DVB-C2 added
    Setting BER, PER for Si2185

  As from V2.1.3:
   Compatibility with Si2191
   In Silabs_UserInput_demod:
    Compatibility with Si2185
   In Silabs_API_Test:
   Init of num_data_slice, to avoid compilation warning when not used

  As from V2.1.2:
   Compatibility with Si2164 (first C2 chip):
    data_slice_id added as a parameter for 'lock_to_carrier'
    *num_data_slice' addes as a parameter for 'Seek_Next'
   Adding SiLabs_API_SSI_SQI function (for S/S2 reception only)
   In SiLabs_API_Demod_status:
    Correcting status->uncorrs for all API controlled demodulators: '(uncor_msb<<8) + uncor_lsb' instead of '(uncor_msb<<16) + uncor_lsb'
   In SiLabs_API_SAT_Unicable_Tune:
    Removing one printf
   In SiLabs_API_lock_to_carrier:
    Correcting voltage levels for SAT polarization selection:
     13V is for 'Vertical', 18V is for 'Horizontal'
    Removing copy of front_end polarization and band values to Unicable structure
    (these may use different values)
   In SiLabs_API_Channel_Seek_Next:
    Removing Unicable polarization and band setup (the reference valeus are those in the front_end structure)
   In SiLabs_API_SAT_voltage_and_tone:
     Correcting voltage levels for SAT polarization selection:
     13V is for 'Vertical', 18V is for 'Horizontal'
   In Silabs_API_Test:
    Initializing all variables to avoid warnings when not used
    Adding access to test pipe for Si2165D
    Adding sat_scan_unicable option

  As from V2.1.1:
  In SiLabs_API_Demod_status:
   Setting status->cell_id by default at 0.
   Updating status->cell_id for Si2165, Si2167 and Si2167B
  In SiLabs_API_lock_to_carrier:
   Tracing input parameters with the corresponding names

  As from V2.1.0:
  In SiLabs_API_Demod_status:
   Calling SAT_TUNER_RSSI_FROM_IFAGC if it exists
  In SiLabs_API_SAT_Tuner_status:
   Removed duplicate call to SiLabs_API_Tuner_I2C_Enable

  As from V2.0.9:
  In SiLabs_API_Demod_status:
   For Si2165D:
    status->spectral_inversion = Si2165_L1_DVB_T_get_spectral_inversion (front_end->Si2165_FE->demod);
   For Si2167:
    status->spectral_inversion = Si2167_L1_DVB_T_get_spectral_inversion (front_end->Si2167_FE->demod);
   For Si2169:
    removing duplicate status->num_plp = ... line
  In SiLabs_API_Text_status:
    Comparing 'float' ratios with int values using (int) cast
  In SiLabs_API_Channel_Seek_Next:
    *num_plp     = 0; (the previous code, without the '*', 'erased' the pointer...)
  In Silabs_API_Test:
   Adding easy access to VDAPPS functions (for internal use)

  As from V2.0.8:
   Adding SiLabs_API_Get_DVBT_Hierarchy function, to retrieve the hiearchy information from the wrapper
   In SiLabs_API_TER_Tuner_status & SiLabs_API_SAT_Tuner_status:
    Moving lines for compatibility with VisualStudio (all variables need to be declared before any one is used).
    Without this it can be quite complex to debug, as the compiler message is not really explicit.
   In SiLabs_API_bytes_trace:
    Corrected when trackWrite flag was sent twice, instead of setting trackWrite & trackRead.
   In SiLabs_API_SAT_voltage_and_tone:
    Tracing voltage and tone values

  As from V2.0.7:
   Compatibility with LNBH29
   In SiLabs_API_Channel_Seek_Next:
    Compatibility with 'handshake' feature
   In SiLabs_API_SW_Init:
     Using a compilation flag to set the LNBH controller chip address if not defined at project level.
     It is written to allow the LNBH_I2C_ADDRESS flag to be defined at project level.
     If not defined at project level, it defaults to '#define LNBH_I2C_ADDRESS 0x10'
   In SiLabs_API_SAT_voltage_and_tone:
     Displaying 'in Unicable Mode' trace only when in Unicable mode.
   In SiLabs_API_Channel_Seek_Init: improved function comments

  As from V2.0.6:
   In SiLabs_API_Demod_status:
    For Si2165D:
     status->IFagc = Si2165_L1_Demod_get_IFagc        (front_end->Si2165_FE->demod);
     (previously returning aci_agc_cmd)
    For Si2169:
     Calling Si2169_L1_DVBT2_TX_ID
     status->cell_id            = front_end->Si2169_FE->demod->rsp->dvbt2_tx_id.cell_id;

  As from V2.0.5:
   LNBH init correction:
   In SiLabs_API_SW_Init, front_end->lnb_chip_init_done = 0; to force the flag at '0'.
    (Some compilers may set it randomly, so it needs to be forced to '0' for compatibility reasons.)

  As from V2.0.4:
   ADDED FEATURE: Added SiLabs_API_Channel_Lock_Abort function, to allow aborting a call to SiLabs_API_lock_to_carrier.
   In SiLabs_API_Demod_status:
    Added Si2167 compatibility with TER tuners not from SiLabs

  As from V2.0.3:
   In SiLabs_API_TS_Mode:
    For Si2167B and Si2169: settings ts parallel clock and data shape to 7 for GPIF mode, and back to 2 for parallel mode

  As from V2.0.2:
   In SiLabs_API_Select_PLP:
    For Si2169: if (plp_mode == Si2169_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_AUTO) { Si2169_L1_DD_RESTART(front_end->Si2169_FE->demod); system_wait(300); }

  As from V2.0.1:
   Added lnb_chip_init_done in SILABS_FE_Context
   In SiLabs_API_SAT_voltage_and_tone:
    if (front_end->lnb_chip_init_done == 0) { front_end->lnb_chip_init_done = L1_LNBH25_InitAfterReset(front_end->lnbh25); }
    This is because the LNBH25 requires an init of all registers

  As from V2.0.0:
   In SiLabs_API_Text_status:
    sprintf(formatted_status, "%s TS bitrate       %d kbps\n", status->TS_bitrate_kHz);
    sprintf(formatted_status, "%s TS clock         %d kHz\n" , status->TS_clock_kHz  );
   SiLabs_API_Reset_Uncorrs compatibility with Si2165
   SiLabs_API_Demod_reset   compatibility with Si2165 and Si2167

  As from V1.9.9:
    Adding NO_SAT tags to allow using Si2169 code without SAT features

  As from V1.9.8:
    Compatibility with TER_TUNER_Si2190
    Compatibility with TER_TUNER_CUSTOMTER
    In SiLabs_API_SAT_AutoDetectCheck:
     Adapting Si2169 code to return the current SAT standard when locked, 0 otherwise.
    In Silabs_API_Test:
    adding wrapper/sat_auto_detect option
    Compatibility with SAT_TUNER_RDA5816S

  As from V1.9.7:
    Adding LNB control in the API, to allow driving LNBH25 or LNBH21 easily
    In SiLabs_API_Demod_status: If Si2169, setting plp_id based on rsp.dvbt2_status.plp_id

  As from V1.9.6:
    Passing pointer to LNB function when calling SiLabs_Unicable_API_Init, following the new definition of SiLabs_Unicable_API_Init

  As from V1.9.5:
    Adding SILABS_MCNS, SILABS_DVB-C2 and SILABS_SLEEP possibilities
    Adding MCNS statusing
    In SiLabs_API_Demod_status: no demod status in SLEEP mode

  As from V1.9.4:
    In SiLabs_API_SAT_Get_AGC:
      Corrected value returned for Si2169 SAT AGC
    In Silabs_API_Test:
      Added Unicable test pipe access

  As from V1.9.3:
    adding TS_bitrate_kHz and TS_clock_kHz in demod status

  As from V1.9.2:
    Si2146 ATV and DTV STATUS removed (not in the Si2146 API anymore)

  As from V1.9.1:
    added/moved tags to allow Si2166B export
   In SiLabs_API_Demod_status:
    setting SSi and SQI at 0 by default.
    compatibility with rssi from CUSTOMTER and CUSTOMSAT tuners

  As from V1.9.0:
   In SiLabs_API_SAT_Tuner_status: moving tags to allow export for Si2168
   Wrapper code compatible with Si2167B: checked to be able to lock a Si2169 board when using the Si2167B code with the proper FW.

  As from V1.8.9:
   Tracing Wrapper source code info during init and in SiLabs_API_Infos
   SiLabs_API_SatAutoDetectCheck renamed as SiLabs_API_SAT_AutoDetectCheck for consistency
   Adding Test Pipe feature (only if SILABS_API_TEST_PIPE is defined at project level), using new Silabs_API_Test function
   Adding PLP management (for DVB_T2 only).
   In SiLabs_API_Demod_status:
    updating spectral_inversion for Si2169 in DVB-T and DBVB-T2
   In SiLabs_API_TS_Mode:
    Stopping GPIF clock if using the Cypress USB interface and not using GPIF mode
   In SiLabs_API_Demod_status and SiLabs_API_Text_status:
    Not storing current standard as front_end->standard, to avoid creating problems with standard switching.
    Using status->standard in all switches.
   In SiLabs_API_TER_Tuner_status and SiLabs_API_SAT_Tuner_status:
    Enabling i2c passthru before statusing tuners

  As from V1.8.8:
   In SiLabs_API_Demod_status:
    setting more statuses by default to indicate a no-lock:
      status->c_n                = 0;
      status->freq_offset        = 0;
      status->timing_offset      = 0;
      status->code_rate          = -1;
      status->SSI                = 0;
      status->SQI                = 0;
    For Si2169: returning '0' immediately in case a standard-specific status returns with an error.

  As from V1.8.7:
   Compatibility with Si2167B (coming soon)

  As from V1.8.6:
   Compatibility with Si2148/Si2158

  As from V1.8.5:
   Adding auto-detect functions:
   int   SiLabs_API_SAT_AutoDetect           (SILABS_FE_Context *front_end, int  on_off);
   int   SiLabs_API_TER_AutoDetect           (SILABS_FE_Context *front_end, int  on_off);

  As from V1.8.4:
   In SiLabs_API_SAT_voltage_and_tone: disegBuffer value correction
   Adding UNICABLE functions (compiled if #define UNICABLE_COMPATIBLE).

  As from V1.8.3:
   Compatibility with Si2178

  As from V1.8.2:
   In SiLabs_API_Demod_status:
    setting ber, fer and per by default at '-1' to indicate unavailability if not set later on.
   In SiLabs_API_Text_status:
    ber and per displayed as '--------' when not available

  As from V1.8.1:
   In SiLabs_API_Demod_status:
    (Si2169) Comments correction indicating that the rate checks are done on the exponent
    Comments correction indicating that the rate checks are done on the exponent
   In SiLabs_API_Text_status:
    spectral inversion added to text status

  As from V1.8.0:
   Compatibility with DTT759x (Terrestrial can tuner)
   Checking exponent for rate in SiLabs_API_Demod_status, to return -1 if not available

  As from V1.7.9:
   voltage_and_tone working with Si2167

  As from V1.7.8:
   voltage_and_tone working with LNBH21
   SAT and DVB-C blindscan working for Si2169
   compatibility with NO_TER 'dummy' TER tuner (for lab use)

  As from V1.7.7:
   BER monitored for Si2169 in DVB-T2 and DVB-S2 as well as for all DTV standards (previously not in FW so it was skipped)

  As from V1.7.6:
   2 lines added to allow exporting for demods with no 'STANDBY' or 'CLOCK_ON' feature
   TERRESTRIAL_FRONT_END tag replacing DEMOD_DVB_T to allow exporting for Si2163/Si2113

  As from 1.7.3:
   some lines moved for greater compatibility with Visual Studio

  As from 1.7.2:
   Si2169 agc values retrieved in SiLabs_API_Demod_status

  As from 1.7.0:
   adding WrapperI2C context to allow easy i2c read/write
   added SiLabs_API_ReadString/SiLabs_API_WriteString functions
   For SAT: added voltage/tone and DiSEqC functions

  As from 1.6.9:
   For Si2169: status->stream based on demod->prop->dvbt_hierarchy.stream;

  As from 1.6.7:
   Compatibility with NXP20142 SAT tuner
  API change: using Si2169 DD_SSI_SQI instead of Si2169_DVBT_SSI_SQI (also available in DVB-T2)

  As from 1.6.6:
   Adding missing BER status for Si2169

  As from 1.6.5:
  Using   SATELLITE_FRONT_END and TERRESTRIAL_FRONT_END compilation flags,
   as it makes it easier to handle C-only or T-only exports

  As from 1.6.1:
   Compatibility with TER tuner cans (not using API mode)
   SiLabs_API_TER_Tuner_ATV_Tune compatible with Si2165

  As from 1.6.0:
   Added Si2185 support
   In   SiLabs_API_Demod_status:
     Set to 0 all info used to relock (bandwidth_Hz, symbol_rate, stream, constellation)
   In SiLabs_API_switch_to_standard:
     For Si2169: Checking dd_status.modulation if switch_to_standard fails
   In SiLabs_API_lock_to_carrier:
     Returning 0 if switch_to_standard fails

  As from 1.5.1:
        power_of_n corrected to return the proper value

 *************************************************************************************************************/
/* TAG V2.8.0 */

/* Before including the headers, define SiLevel and SiTAG */
#define   SiLEVEL          3
#define   SiTAG            front_end->tag
#include "SiLabs_API_L3_Wrapper.h"

#ifdef    SATELLITE_FRONT_END
#ifdef    A8297_COMPATIBLE
SILABS_FE_Context *A8297_FE_0;
SILABS_FE_Context *A8297_FE_1;
#endif /* A8297_COMPATIBLE */
#endif /* SATELLITE_FRONT_END */

#ifdef    __cplusplus
extern "C" {
#endif /* __cplusplus */

signed   int   Silabs_init_done = 0;
signed   int   Silabs_multiple_front_end_init_done = 0;
/* Also init a simple i2c context to allow i2c communication checking */
L0_Context* WrapperI2C;
L0_Context  WrapperI2C_context;

       /* Translation functions from 'Custom' values to 'SiLabs' values */
#if 1
signed   int  power_of_n                            (signed   int n, signed   int m) {
  signed   int i;
  signed   int p;
  p = 1;
  for (i=1; i<= m; i++) {
    p = p*n;
  }
  return p;
}
/************************************************************************************************************************
  Silabs_standardCode function
  Use:        standard code function
              Used to retrieve the standard value used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  standard, the value used by the top-level application (configurable in CUSTOM_Standard_Enum)
************************************************************************************************************************/
signed   int  Silabs_standardCode                   (SILABS_FE_Context* front_end,    signed   int                  standard)
{
  front_end = front_end; /* to avoid compiler warning if not used */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    switch (standard) {
#ifdef    DEMOD_DVB_T
      case SILABS_DVB_T : return Si2183_DD_MODE_PROP_MODULATION_DVBT;
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_ISDB_T
      case SILABS_ISDB_T: return Si2183_DD_MODE_PROP_MODULATION_ISDBT;
#endif /* DEMOD_ISDB_T */
#ifdef    DEMOD_DVB_T2
      case SILABS_DVB_T2: return Si2183_DD_MODE_PROP_MODULATION_DVBT2;
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_MCNS
      case SILABS_MCNS  : return Si2183_DD_MODE_PROP_MODULATION_MCNS;
#endif /* DEMOD_MCNS */
#ifdef    DEMOD_DVB_C
      case SILABS_DVB_C : return Si2183_DD_MODE_PROP_MODULATION_DVBC;
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_C2
      case SILABS_DVB_C2: return Si2183_DD_MODE_PROP_MODULATION_DVBC2;
#endif /* DEMOD_DVB_C2 */
#ifdef    DEMOD_DVB_S_S2_DSS
      case SILABS_DVB_S : return Si2183_DD_MODE_PROP_MODULATION_DVBS;
      case SILABS_DVB_S2: return Si2183_DD_MODE_PROP_MODULATION_DVBS2;
      case SILABS_DSS   : return Si2183_DD_MODE_PROP_MODULATION_DSS;
#endif /* DEMOD_DVB_S_S2_DSS */
      case SILABS_ANALOG: return Si2183_DD_MODE_PROP_MODULATION_ANALOG;
      case SILABS_SLEEP : return 100;
      case SILABS_OFF   : return 200;
      default           : return -1;
    }
  }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  Silabs_constelCode function
  Use:        constel code function
              Used to retrieve the constel value used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  constel, the value used by the top-level application (configurable in CUSTOM_Constel_Enum)
************************************************************************************************************************/
signed   int  Silabs_constelCode                    (SILABS_FE_Context* front_end,    CUSTOM_Constel_Enum           constel)
{
  front_end = front_end; /* to avoid compiler warning if not used */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    switch (constel) {
      case SILABS_QAMAUTO : return  0;
      case SILABS_QAM16   : return  7;
      case SILABS_QAM32   : return  8;
      case SILABS_QAM64   : return  9;
      case SILABS_QAM128  : return 10;
      case SILABS_QAM256  : return 11;
      case SILABS_QPSK    : return  3;
      case SILABS_8PSK    : return 14;
      case SILABS_QAM1024 : return 13;
      case SILABS_QAM4096 : return 15;
      case SILABS_8APSK_L : return 23;
      case SILABS_16APSK  : return 20;
      case SILABS_16APSK_L: return 24;
      case SILABS_32APSK_1: return 21;
      case SILABS_32APSK_2: return 26;
      case SILABS_32APSK_L: return 25;
      case SILABS_DQPSK   : return  4;
      default             : return -1;
    }
  }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  Silabs_streamCode function
  Use:        stream code function
              Used to retrieve the stream value used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  stream, the value used by the top-level application (configurable in CUSTOM_Stream_Enum)
************************************************************************************************************************/
signed   int  Silabs_streamCode                     (SILABS_FE_Context* front_end,    CUSTOM_Stream_Enum            stream)
{
  front_end = front_end; /* to avoid compiler warning if not used */
  stream    = stream;    /* to avoid compiler warning if not used */
#ifdef    DEMOD_DVB_T
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    switch (stream) {
      case SILABS_HP : return Si2183_DVBT_HIERARCHY_PROP_STREAM_HP   ;
      case SILABS_LP : return Si2183_DVBT_HIERARCHY_PROP_STREAM_LP   ;
      default           : return -1;
    }
  }
#endif /* Si2183_COMPATIBLE */
#endif /* DEMOD_DVB_T */
  return -1;
}
/************************************************************************************************************************
  Silabs_plptypeCode function
  Use:        plp type code function
              Used to retrieve the plp type value used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  plp_type, the value used by the top-level application (configurable in CUSTOM_T2_PLP_TYPE)
************************************************************************************************************************/
signed   int  Silabs_plptypeCode                    (SILABS_FE_Context* front_end,    CUSTOM_T2_PLP_TYPE            plp_type)
{
  front_end = front_end; /* to avoid compiler warning if not used */
  plp_type  = plp_type ; /* To avoid compiler warning if not used */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    switch (plp_type) {
#ifdef    DEMOD_DVB_T2
      case SILABS_PLP_TYPE_COMMON     : return Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_TYPE_COMMON    ;
      case SILABS_PLP_TYPE_DATA_TYPE1 : return Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_TYPE_DATA_TYPE1;
      case SILABS_PLP_TYPE_DATA_TYPE2 : return Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_TYPE_DATA_TYPE2;
#endif /* DEMOD_DVB_T2 */
      default           : return -1;
    }
  }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  Silabs_fftCode function
  Use:        fft code function
              Used to retrieve the fft value used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  fft, the value used by the top-level application (configurable in CUSTOM_FFT_Mode_Enum)
************************************************************************************************************************/
signed   int  Silabs_fftCode                        (SILABS_FE_Context* front_end,    CUSTOM_FFT_Mode_Enum          fft)
{
  front_end = front_end; /* to avoid compiler warning if not used */
  fft       = fft;       /* to avoid compiler warning if not used */
#ifdef    DEMOD_DVB_T
#endif /* DEMOD_DVB_T */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    switch (fft) {
#ifdef    DEMOD_DVB_T
      case SILABS_FFT_MODE_2K : return Si2183_DVBT_STATUS_RESPONSE_FFT_MODE_2K;
      case SILABS_FFT_MODE_4K : return Si2183_DVBT_STATUS_RESPONSE_FFT_MODE_4K;
      case SILABS_FFT_MODE_8K : return Si2183_DVBT_STATUS_RESPONSE_FFT_MODE_8K;
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_DVB_T2
#ifdef    Si2183_DVBT2_STATUS_RESPONSE_FFT_MODE_16K
      case SILABS_FFT_MODE_1K : return Si2183_DVBT2_STATUS_RESPONSE_FFT_MODE_1K;
      case SILABS_FFT_MODE_16K: return Si2183_DVBT2_STATUS_RESPONSE_FFT_MODE_16K;
      case SILABS_FFT_MODE_32K: return Si2183_DVBT2_STATUS_RESPONSE_FFT_MODE_32K;
#endif /* Si2183_DVBT2_STATUS_RESPONSE_FFT_MODE_16K */
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_ISDB_T
 #ifndef    Si2183_DVBT_STATUS_RESPONSE_FFT_MODE_2K
      case SILABS_FFT_MODE_2K : return Si2183_ISDBT_STATUS_RESPONSE_FFT_MODE_2K;
      case SILABS_FFT_MODE_4K : return Si2183_ISDBT_STATUS_RESPONSE_FFT_MODE_4K;
      case SILABS_FFT_MODE_8K : return Si2183_ISDBT_STATUS_RESPONSE_FFT_MODE_8K;
 #endif /* Si2183_DVBT_STATUS_RESPONSE_FFT_MODE_2K */
#endif /* DEMOD_ISDB_T */
      default           : return -1;
    }
  }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  Silabs_giCode function
  Use:        gi code function
              Used to retrieve the gi value used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  gi, the value used by the top-level application (configurable in CUSTOM_gi_Mode_Enum)
************************************************************************************************************************/
signed   int  Silabs_giCode                         (SILABS_FE_Context* front_end,    CUSTOM_GI_Enum                gi)
{
  front_end = front_end; /* to avoid compiler warning if not used */
  gi        = gi;        /* to avoid compiler warning if not used */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    switch (gi) {
#ifdef    DEMOD_DVB_T
      case SILABS_GUARD_INTERVAL_1_32  : return Si2183_DVBT_STATUS_RESPONSE_GUARD_INT_1_32;
      case SILABS_GUARD_INTERVAL_1_16  : return Si2183_DVBT_STATUS_RESPONSE_GUARD_INT_1_16;
      case SILABS_GUARD_INTERVAL_1_8   : return Si2183_DVBT_STATUS_RESPONSE_GUARD_INT_1_8 ;
      case SILABS_GUARD_INTERVAL_1_4   : return Si2183_DVBT_STATUS_RESPONSE_GUARD_INT_1_4 ;
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_DVB_T2
      case SILABS_GUARD_INTERVAL_1_128 : return Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_1_128 ;
      case SILABS_GUARD_INTERVAL_19_128: return Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_19_128 ;
      case SILABS_GUARD_INTERVAL_19_256: return Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_19_256 ;
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_DVB_C2
 #ifndef    Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_1_128
      case SILABS_GUARD_INTERVAL_1_128 : return Si2183_DVBC2_STATUS_RESPONSE_GUARD_INT_1_128 ;
 #endif  /* Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_1_128 */
      case SILABS_GUARD_INTERVAL_1_64  : return Si2183_DVBC2_STATUS_RESPONSE_GUARD_INT_1_64   ;
#endif /* DEMOD_DVB_C2 */
#ifdef    DEMOD_ISDB_T
 #ifndef    Si2183_DVBT_STATUS_RESPONSE_GUARD_INT_1_32
      case SILABS_GUARD_INTERVAL_1_32  : return Si2183_ISDBT_STATUS_RESPONSE_GUARD_INT_1_32;
      case SILABS_GUARD_INTERVAL_1_16  : return Si2183_ISDBT_STATUS_RESPONSE_GUARD_INT_1_16;
      case SILABS_GUARD_INTERVAL_1_8   : return Si2183_ISDBT_STATUS_RESPONSE_GUARD_INT_1_8 ;
      case SILABS_GUARD_INTERVAL_1_4   : return Si2183_ISDBT_STATUS_RESPONSE_GUARD_INT_1_4 ;
 #endif /* Si2183_DVBT_STATUS_RESPONSE_GUARD_INT_1_32 */
#endif /* DEMOD_ISDB_T */
      default           : return -1;
    }
  }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  Silabs_coderateCode function
  Use:        coderate code function
              Used to retrieve the coderate value used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  coderate, the value used by the top-level application (configurable in CUSTOM_Coderate_Enum)
************************************************************************************************************************/
signed   int  Silabs_coderateCode                   (SILABS_FE_Context* front_end,    signed   int                  coderate)
{
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    switch (coderate) {
#ifdef    DEMOD_DVB_T
      case SILABS_CODERATE_1_2 : return Si2183_DVBT_STATUS_RESPONSE_RATE_HP_1_2;
      case SILABS_CODERATE_2_3 : return Si2183_DVBT_STATUS_RESPONSE_RATE_HP_2_3;
      case SILABS_CODERATE_3_4 : return Si2183_DVBT_STATUS_RESPONSE_RATE_HP_3_4;
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_DVB_S_S2_DSS
      case SILABS_CODERATE_4_5 : return Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_4_5;
#endif /* DEMOD_DVB_S_S2_DSS */
#ifdef    DEMOD_DVB_T
      case SILABS_CODERATE_5_6 : return Si2183_DVBT_STATUS_RESPONSE_RATE_HP_5_6;
      case SILABS_CODERATE_7_8 : return Si2183_DVBT_STATUS_RESPONSE_RATE_HP_7_8;
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_DVB_T2
  #ifndef   Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_4_5
      case SILABS_CODERATE_4_5 : return Si2183_DVBT2_STATUS_RESPONSE_CODE_RATE_4_5;
      case SILABS_CODERATE_1_3 : return Si2183_DVBT2_STATUS_RESPONSE_CODE_RATE_1_3;
      case SILABS_CODERATE_2_5 : return Si2183_DVBT2_STATUS_RESPONSE_CODE_RATE_2_5;
      case SILABS_CODERATE_3_5 : return Si2183_DVBT2_STATUS_RESPONSE_CODE_RATE_3_5;
  #endif /* Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_4_5 */
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_DVB_S_S2_DSS
      case SILABS_CODERATE_8_9 : return Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_8_9;
      case SILABS_CODERATE_9_10: return Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_9_10;
      case SILABS_CODERATE_1_3 : return Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_1_3;
      case SILABS_CODERATE_2_5 : return Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_2_5;
      case SILABS_CODERATE_3_5 : return Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_3_5;
#endif /* DEMOD_DVB_S_S2_DSS */
      default           : return -1;
    }
  }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  Silabs_hierarchyCode function
  Use:        hierarchy code function
              Used to retrieve the hierarchy value used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  hierarchy, the value used by the top-level application (configurable in CUSTOM_Hierarchy_Enum)
************************************************************************************************************************/
signed   int  Silabs_hierarchyCode                  (SILABS_FE_Context* front_end,    CUSTOM_Hierarchy_Enum         hierarchy)
{
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    switch (hierarchy) {
#ifdef    DEMOD_DVB_T
      case SILABS_HIERARCHY_NONE : return Si2183_DVBT_STATUS_RESPONSE_HIERARCHY_NONE;
      case SILABS_HIERARCHY_ALFA1: return Si2183_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA1;
      case SILABS_HIERARCHY_ALFA2: return Si2183_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA2;
      case SILABS_HIERARCHY_ALFA4: return Si2183_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA4;
#endif /* DEMOD_DVB_T */
      default           : return -1;
    }
  }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  Silabs_pilotPatternCode function
  Use:        pilot pattern code function
              Used to retrieve the pilot pattern value used by DVB-T2 demodulators
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  pilot_pattern, the value used by the top-level application (configurable in CUSTOM_Pilot_Pattern_Enum)
************************************************************************************************************************/
signed   int  Silabs_pilotPatternCode               (SILABS_FE_Context* front_end,    CUSTOM_Pilot_Pattern_Enum     pilot_pattern)
{
  front_end->chip = front_end->chip; /* To avoid compiler warning */
  pilot_pattern   = pilot_pattern  ; /* To avoid compiler warning */
#ifdef    Si2183_COMPATIBLE
#ifdef    DEMOD_DVB_T2
  if (front_end->chip ==   0x2183 ) {
    switch (pilot_pattern) {
      case SILABS_PILOT_PATTERN_PP1 : return Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP1;
      case SILABS_PILOT_PATTERN_PP2 : return Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP2;
      case SILABS_PILOT_PATTERN_PP3 : return Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP3;
      case SILABS_PILOT_PATTERN_PP4 : return Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP4;
      case SILABS_PILOT_PATTERN_PP5 : return Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP5;
      case SILABS_PILOT_PATTERN_PP6 : return Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP6;
      case SILABS_PILOT_PATTERN_PP7 : return Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP7;
      case SILABS_PILOT_PATTERN_PP8 : return Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP8;
      default           : return -1;
    }
  }
#endif /* DEMOD_DVB_T2 */
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  Silabs_T2VersionCode function
  Use:        T2 version code function
              Used to retrieve the T2 version value used by DVB-T2 demodulators
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  t2_version, the value used by the top-level application
************************************************************************************************************************/
signed   int  Silabs_T2VersionCode                  (SILABS_FE_Context* front_end,    CUSTOM_Pilot_T2_version_Enum  t2_version)
{
  front_end->chip = front_end->chip; /* To avoid compiler warning */
  t2_version      = t2_version     ; /* To avoid compiler warning */
#ifdef    Si2183_COMPATIBLE
#ifdef    DEMOD_DVB_T2
  if (front_end->chip ==   0x2183 ) {
    switch (t2_version) {
      case SILABS_T2_VERSION_1_1_1 : return Si2183_DVBT2_STATUS_RESPONSE_T2_VERSION_1_1_1;
      case SILABS_T2_VERSION_1_2_1 : return Si2183_DVBT2_STATUS_RESPONSE_T2_VERSION_1_2_1;
      case SILABS_T2_VERSION_1_3_1 : return Si2183_DVBT2_STATUS_RESPONSE_T2_VERSION_1_3_1;
      default                      : return -1;
    }
  }
#endif /* DEMOD_DVB_T2 */
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  Silabs_videoSysCode function
  Use:        analog video system code function
              Used to retrieve the analog video system value used by the tuner in custom format
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  video_sys, the value used by the top-level application (as returned by the tuner)
************************************************************************************************************************/
signed   int  Silabs_videoSysCode                   (SILABS_FE_Context* front_end,    CUSTOM_Video_Sys_Enum         video_sys)
{
  front_end = front_end; /* To avoid compiler warning */
  SiTRACE("Silabs_videoSysCode %d\n", video_sys);
#ifdef    Si2173_COMPATIBLE
  switch (video_sys) {
    case SILABS_VIDEO_SYS_B  : return Si2173_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B;
    case SILABS_VIDEO_SYS_GH : return Si2173_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH;
    case SILABS_VIDEO_SYS_M  : return Si2173_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M;
    case SILABS_VIDEO_SYS_N  : return Si2173_ATV_VIDEO_MODE_PROP_VIDEO_SYS_N;
    case SILABS_VIDEO_SYS_I  : return Si2173_ATV_VIDEO_MODE_PROP_VIDEO_SYS_I;
    case SILABS_VIDEO_SYS_DK : return Si2173_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK;
    case SILABS_VIDEO_SYS_L  : return Si2173_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L;
    case SILABS_VIDEO_SYS_LP : return Si2173_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LP;
    default           : return -1;
  }
#endif /* Si2173_COMPATIBLE */
#ifdef    Si2176_COMPATIBLE
  switch (video_sys) {
    case SILABS_VIDEO_SYS_B  : return Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B;
    case SILABS_VIDEO_SYS_GH : return Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH;
    case SILABS_VIDEO_SYS_M  : return Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M;
    case SILABS_VIDEO_SYS_N  : return Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_N;
    case SILABS_VIDEO_SYS_I  : return Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_I;
    case SILABS_VIDEO_SYS_DK : return Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK;
    case SILABS_VIDEO_SYS_L  : return Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L;
    case SILABS_VIDEO_SYS_LP : return Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LP;
    default           : return -1;
  }
#endif /* Si2176_COMPATIBLE */
#ifdef    Si2178_COMPATIBLE
  switch (video_sys) {
    case SILABS_VIDEO_SYS_B  : return Si2178_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B;
    case SILABS_VIDEO_SYS_GH : return Si2178_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH;
    case SILABS_VIDEO_SYS_M  : return Si2178_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M;
    case SILABS_VIDEO_SYS_N  : return Si2178_ATV_VIDEO_MODE_PROP_VIDEO_SYS_N;
    case SILABS_VIDEO_SYS_I  : return Si2178_ATV_VIDEO_MODE_PROP_VIDEO_SYS_I;
    case SILABS_VIDEO_SYS_DK : return Si2178_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK;
    case SILABS_VIDEO_SYS_L  : return Si2178_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L;
    case SILABS_VIDEO_SYS_LP : return Si2178_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LP;
    default           : return -1;
  }
#endif /* Si2178_COMPATIBLE */
#ifdef    Si2196_COMPATIBLE
  switch (video_sys) {
    case SILABS_VIDEO_SYS_B  : return Si2196_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B;
    case SILABS_VIDEO_SYS_GH : return Si2196_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH;
    case SILABS_VIDEO_SYS_M  : return Si2196_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M;
    case SILABS_VIDEO_SYS_N  : return Si2196_ATV_VIDEO_MODE_PROP_VIDEO_SYS_N;
    case SILABS_VIDEO_SYS_I  : return Si2196_ATV_VIDEO_MODE_PROP_VIDEO_SYS_I;
    case SILABS_VIDEO_SYS_DK : return Si2196_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK;
    case SILABS_VIDEO_SYS_L  : return Si2196_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L;
    case SILABS_VIDEO_SYS_LP : return Si2196_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LP;
    default           : return -1;
  }
#endif /* Si2196_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  Silabs_colorCode function
  Use:        analog video color code function
              Used to retrieve the analog video color value used by the tuner in custom format
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  color, the value used by the top-level application (as returned by the tuner)
************************************************************************************************************************/
signed   int  Silabs_colorCode                      (SILABS_FE_Context* front_end,    CUSTOM_Color_Enum             color)
{
  front_end = front_end; /* To avoid compiler warning */
  SiTRACE("Silabs_colorCode %d\n", color);
#ifdef    Si2173_COMPATIBLE
  switch (color) {
    case SILABS_COLOR_PAL_NTSC : return Si2173_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;
    case SILABS_COLOR_SECAM    : return Si2173_ATV_VIDEO_MODE_PROP_COLOR_SECAM;
    default           : return -1;
  }
#endif /* Si2173_COMPATIBLE */
#ifdef    Si2176_COMPATIBLE
  switch (color) {
    case SILABS_COLOR_PAL_NTSC : return Si2176_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;
    case SILABS_COLOR_SECAM    : return Si2176_ATV_VIDEO_MODE_PROP_COLOR_SECAM;
    default           : return -1;
  }
#endif /* Si2176_COMPATIBLE */
#ifdef    Si2178_COMPATIBLE
  switch (color) {
    case SILABS_COLOR_PAL_NTSC : return Si2178_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;
    case SILABS_COLOR_SECAM    : return Si2178_ATV_VIDEO_MODE_PROP_COLOR_SECAM;
    default           : return -1;
  }
#endif /* Si2178_COMPATIBLE */
#ifdef    Si2196_COMPATIBLE
  switch (color) {
    case SILABS_COLOR_PAL_NTSC : return Si2196_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;
    case SILABS_COLOR_SECAM    : return Si2196_ATV_VIDEO_MODE_PROP_COLOR_SECAM;
    default           : return -1;
  }
#endif /* Si2196_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  Silabs_transmissionCode function
  Use:        analog video transmission code function
              Used to retrieve the analog video transmission value used by the tuner in custom format
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  trans, the value used by the top-level application (as returned by the tuner)
************************************************************************************************************************/
signed   int  Silabs_transmissionCode               (SILABS_FE_Context* front_end,    CUSTOM_Transmission_Mode_Enum trans)
{
  front_end = front_end; /* To avoid compiler warning if not supported */
  trans     = trans;     /* To avoid compiler warning if not supported */
#ifdef    Si2173_COMPATIBLE
  switch (trans) {
    case SILABS_TRANSMISSION_MODE_TERRESTRIAL : return Si2173_ATV_VIDEO_MODE_PROP_TRANS_TERRESTRIAL;
    case SILABS_TRANSMISSION_MODE_CABLE       : return Si2173_ATV_VIDEO_MODE_PROP_TRANS_CABLE;
    default           : return -1;
  }
#endif /* Si2173_COMPATIBLE */
#ifdef    Si2176_COMPATIBLE
  switch (trans) {
    case SILABS_TRANSMISSION_MODE_TERRESTRIAL : return Si2176_ATV_VIDEO_MODE_PROP_TRANS_TERRESTRIAL;
    case SILABS_TRANSMISSION_MODE_CABLE       : return Si2176_ATV_VIDEO_MODE_PROP_TRANS_CABLE;
    default           : return -1;
  }
#endif /* Si2176_COMPATIBLE */
#ifdef    Si2178_COMPATIBLE
  switch (trans) {
 #ifdef   Si2178_ATV_VIDEO_MODE_PROP_TRANS_TERRESTRIAL
    case SILABS_TRANSMISSION_MODE_TERRESTRIAL : return Si2178_ATV_VIDEO_MODE_PROP_TRANS_TERRESTRIAL;
    case SILABS_TRANSMISSION_MODE_CABLE       : return Si2178_ATV_VIDEO_MODE_PROP_TRANS_CABLE;
 #endif /* Si2178_ATV_VIDEO_MODE_PROP_TRANS_TERRESTRIAL */
    default           : return -1;
  }
#endif /* Si2178_COMPATIBLE */
#ifdef    Si2196_COMPATIBLE
  switch (trans) {
    case SILABS_TRANSMISSION_MODE_TERRESTRIAL : return Si2196_ATV_VIDEO_MODE_PROP_TRANS_TERRESTRIAL;
    case SILABS_TRANSMISSION_MODE_CABLE       : return Si2196_ATV_VIDEO_MODE_PROP_TRANS_CABLE;
    default           : return -1;
  }
#endif /* Si2196_COMPATIBLE */
  return -1;
}
#endif /* Translation functions from 'Custom' values to 'SiLabs' values  */
       /* Translation functions from 'SiLabs' values to 'Custom' values */
#if 1
/************************************************************************************************************************
  Custom_standardCode function
  Use:        standard code function
              Used to retrieve the standard value used by the DTV demodulator in custom format
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  standard, the value used by the top-level application (as returned by the demod)
************************************************************************************************************************/
signed   int  Custom_standardCode                   (SILABS_FE_Context* front_end,    signed   int standard)
{
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    switch (standard) {
#ifdef    DEMOD_DVB_T
      case Si2183_DD_MODE_PROP_MODULATION_DVBT : return SILABS_DVB_T ;
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_ISDB_T
      case Si2183_DD_MODE_PROP_MODULATION_ISDBT: return SILABS_ISDB_T;
#endif /* DEMOD_ISDB_T */
#ifdef    DEMOD_DVB_T2
      case Si2183_DD_MODE_PROP_MODULATION_DVBT2: return SILABS_DVB_T2;
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_DVB_C
      case Si2183_DD_MODE_PROP_MODULATION_DVBC : return SILABS_DVB_C ;
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_C2
      case Si2183_DD_MODE_PROP_MODULATION_DVBC2: return SILABS_DVB_C2;
#endif /* DEMOD_DVB_C2 */
#ifdef    DEMOD_MCNS
      case Si2183_DD_MODE_PROP_MODULATION_MCNS : return SILABS_MCNS  ;
#endif /* DEMOD_MCNS */
#ifdef    DEMOD_DVB_S_S2_DSS
      case Si2183_DD_MODE_PROP_MODULATION_DVBS : return SILABS_DVB_S ;
      case Si2183_DD_MODE_PROP_MODULATION_DVBS2: return SILABS_DVB_S2;
      case Si2183_DD_MODE_PROP_MODULATION_DSS  : return SILABS_DSS   ;
#endif /* DEMOD_DVB_S_S2_DSS */
      default                                  : return -1;
    }
  }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  Custom_constelCode function
  Use:        constel code function
              Used to retrieve the constel value  used by the DTV demodulator in custom format
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  constel, the value used by the top-level application (as returned by the demod)
************************************************************************************************************************/
signed   int  Custom_constelCode                    (SILABS_FE_Context* front_end,    signed   int constel)
{
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    switch (constel) {
      case  0: return SILABS_QAMAUTO ;
      case  7: return SILABS_QAM16   ;
      case  8: return SILABS_QAM32   ;
      case  9: return SILABS_QAM64   ;
      case 10: return SILABS_QAM128  ;
      case 11: return SILABS_QAM256  ;
      case  3: return SILABS_QPSK    ;
      case 14: return SILABS_8PSK    ;
      case 13: return SILABS_QAM1024 ;
      case 15: return SILABS_QAM4096 ;
      case 23: return SILABS_8APSK_L ;
      case 20: return SILABS_16APSK  ;
      case 24: return SILABS_16APSK_L;
      case 21: return SILABS_32APSK_1;
      case 26: return SILABS_32APSK_2;
      case 25: return SILABS_32APSK_L;
      case  4: return SILABS_DQPSK   ;
      default: return -1;
    }
  }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  Custom_streamCode function
  Use:        stream code function
              Used to retrieve the stream value used by the DTV demodulator in custom format
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  stream, the value used by the top-level application (as returned by the demod)
************************************************************************************************************************/
signed   int  Custom_streamCode                     (SILABS_FE_Context* front_end,    signed   int stream)
{
  front_end = front_end; /* To avoid compiler warning if not supported */
  stream    = stream;    /* To avoid compiler warning if not supported */
#ifdef    DEMOD_DVB_T
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    switch (stream) {
      case Si2183_DVBT_HIERARCHY_PROP_STREAM_HP: return SILABS_HP;
      case Si2183_DVBT_HIERARCHY_PROP_STREAM_LP: return SILABS_LP;
      default                                  : return -1;
    }
  }
#endif /* Si2183_COMPATIBLE */
#endif /* DEMOD_DVB_T */
  return -1;
}
/************************************************************************************************************************
  Custom_plptypeCode function
  Use:        plp type code function
              Used to retrieve the plp type value used by the DTV demodulator in custom format
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  plp_type, the value used by the top-level application (as returned by the demod)
************************************************************************************************************************/
signed   int  Custom_plptypeCode                    (SILABS_FE_Context* front_end,    signed   int plp_type)
{
  front_end = front_end; /* To avoid compiler warning if not supported */
  plp_type  = plp_type;    /* To avoid compiler warning if not supported */
#ifdef    DEMOD_DVB_T2
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    switch (plp_type) {
      case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_TYPE_COMMON    : return SILABS_PLP_TYPE_COMMON;
      case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_TYPE_DATA_TYPE1: return SILABS_PLP_TYPE_DATA_TYPE1;
      case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_TYPE_DATA_TYPE2: return SILABS_PLP_TYPE_DATA_TYPE2;
      default                                  : return -1;
    }
  }
#endif /* Si2183_COMPATIBLE */
#endif /* DEMOD_DVB_T2 */
  return -1;
}
/************************************************************************************************************************
  Custom_fftCode function
  Use:        fft code function
              Used to retrieve the fft value used by the DTV demodulator in custom format
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  fft, the value used by the top-level application (as returned by the demod)
************************************************************************************************************************/
signed   int  Custom_fftCode                        (SILABS_FE_Context* front_end,    signed   int fft)
{
  front_end = front_end; /* To avoid compiler warning if not supported */
  fft       = fft;       /* To avoid compiler warning if not supported */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    switch (fft) {
#ifdef    DEMOD_DVB_T
      case Si2183_DVBT_STATUS_RESPONSE_FFT_MODE_2K  : return SILABS_FFT_MODE_2K ;
      case Si2183_DVBT_STATUS_RESPONSE_FFT_MODE_4K  : return SILABS_FFT_MODE_4K ;
      case Si2183_DVBT_STATUS_RESPONSE_FFT_MODE_8K  : return SILABS_FFT_MODE_8K ;
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_DVB_T2
      case Si2183_DVBT2_STATUS_RESPONSE_FFT_MODE_1K : return SILABS_FFT_MODE_1K;
      case Si2183_DVBT2_STATUS_RESPONSE_FFT_MODE_16K: return SILABS_FFT_MODE_16K;
      case Si2183_DVBT2_STATUS_RESPONSE_FFT_MODE_32K: return SILABS_FFT_MODE_32K;
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_ISDB_T
 #ifndef    Si2183_DVBT_STATUS_RESPONSE_FFT_MODE_2K
      case Si2183_ISDBT_STATUS_RESPONSE_FFT_MODE_2K  : return SILABS_FFT_MODE_2K ;
      case Si2183_ISDBT_STATUS_RESPONSE_FFT_MODE_4K  : return SILABS_FFT_MODE_4K ;
      case Si2183_ISDBT_STATUS_RESPONSE_FFT_MODE_8K  : return SILABS_FFT_MODE_8K ;
 #endif /* Si2183_DVBT_STATUS_RESPONSE_FFT_MODE_2K */
#endif /* DEMOD_ISDB_T */
      default                                       : return -1;
    }
  }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  Custom_giCode function
  Use:        gi code function
              Used to retrieve the gi value used by the DTV demodulator in custom format
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  gi, the value used by the top-level application (as returned by the demod)
************************************************************************************************************************/
signed   int  Custom_giCode                         (SILABS_FE_Context* front_end,    signed   int gi)
{
  front_end = front_end; /* To avoid compiler warning if not supported */
  gi        = gi;        /* To avoid compiler warning if not supported */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    switch (gi) {
#ifdef    DEMOD_DVB_T
      case Si2183_DVBT_STATUS_RESPONSE_GUARD_INT_1_32   : return SILABS_GUARD_INTERVAL_1_32  ;
      case Si2183_DVBT_STATUS_RESPONSE_GUARD_INT_1_16   : return SILABS_GUARD_INTERVAL_1_16  ;
      case Si2183_DVBT_STATUS_RESPONSE_GUARD_INT_1_8    : return SILABS_GUARD_INTERVAL_1_8   ;
      case Si2183_DVBT_STATUS_RESPONSE_GUARD_INT_1_4    : return SILABS_GUARD_INTERVAL_1_4   ;
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_DVB_T2
      case Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_1_128 : return SILABS_GUARD_INTERVAL_1_128 ;
      case Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_19_128: return SILABS_GUARD_INTERVAL_19_128;
      case Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_19_256: return SILABS_GUARD_INTERVAL_19_256;
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_DVB_C2
#ifndef    Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_1_128
      case Si2183_DVBC2_STATUS_RESPONSE_GUARD_INT_1_128 : return SILABS_GUARD_INTERVAL_1_128 ;
#endif /* Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_1_128 */
      case Si2183_DVBC2_STATUS_RESPONSE_GUARD_INT_1_64  : return SILABS_GUARD_INTERVAL_1_64  ;
#endif /* DEMOD_DVB_C2 */
#ifdef    DEMOD_ISDB_T
 #ifndef    Si2183_DVBT_STATUS_RESPONSE_GUARD_INT_1_32
      case Si2183_ISDBT_STATUS_RESPONSE_GUARD_INT_1_32   : return SILABS_GUARD_INTERVAL_1_32  ;
      case Si2183_ISDBT_STATUS_RESPONSE_GUARD_INT_1_16   : return SILABS_GUARD_INTERVAL_1_16  ;
      case Si2183_ISDBT_STATUS_RESPONSE_GUARD_INT_1_8    : return SILABS_GUARD_INTERVAL_1_8   ;
      case Si2183_ISDBT_STATUS_RESPONSE_GUARD_INT_1_4    : return SILABS_GUARD_INTERVAL_1_4   ;
 #endif /* Si2183_DVBT_STATUS_RESPONSE_GUARD_INT_1_32 */
#endif /* DEMOD_ISDB_T */
      default                                           : return -1;
    }
  }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  Custom_coderateCode function
  Use:        coderate code function
              Used to retrieve the coderate value used by the DTV demodulator in custom format
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  coderate, the value used by the top-level application (as returned by the demod)
************************************************************************************************************************/
signed   int  Custom_coderateCode                   (SILABS_FE_Context* front_end,    signed   int coderate)
{
  front_end = front_end; /* To avoid compiler warning if not supported */
  coderate  = coderate;  /* To avoid compiler warning if not supported */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    switch (coderate) {
      case 1  : return SILABS_CODERATE_1_2;
      case 2  : return SILABS_CODERATE_2_3;
      case 3  : return SILABS_CODERATE_3_4;
      case 4  : return SILABS_CODERATE_4_5;
      case 5  : return SILABS_CODERATE_5_6;
      case 7  : return SILABS_CODERATE_7_8;
      case 8  : return SILABS_CODERATE_8_9;
      case 9  : return SILABS_CODERATE_9_10;
      case 10 : return SILABS_CODERATE_1_3;
      case 11 : return SILABS_CODERATE_1_4;
      case 12 : return SILABS_CODERATE_2_5;
      case 13 : return SILABS_CODERATE_3_5;
      case 16 : return SILABS_CODERATE_13_45;
      case 17 : return SILABS_CODERATE_9_20;
      case 18 : return SILABS_CODERATE_8_15;
      case 19 : return SILABS_CODERATE_11_20;
      case 20 : return SILABS_CODERATE_5_9;
      case 21 : return SILABS_CODERATE_26_45;
      case 22 : return SILABS_CODERATE_28_45;
      case 23 : return SILABS_CODERATE_23_36;
      case 24 : return SILABS_CODERATE_25_36;
      case 25 : return SILABS_CODERATE_32_45;
      case 26 : return SILABS_CODERATE_13_18;
      case 27 : return SILABS_CODERATE_11_15;
      case 28 : return SILABS_CODERATE_7_9;
      case 29 : return SILABS_CODERATE_77_90;
      default : return -1;
    }
  }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  Custom_hierarchyCode function
  Use:        hierarchy code function
              Used to retrieve the hierarchy value used by the DTV demodulator in custom format
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  hierarchy, the value used by the top-level application (as returned by the demod)
************************************************************************************************************************/
signed   int  Custom_hierarchyCode                  (SILABS_FE_Context* front_end,    signed   int hierarchy)
{
  front_end = front_end; /* To avoid compiler warning if not supported */
  hierarchy = hierarchy; /* To avoid compiler warning if not supported */
#ifdef    Si2183_COMPATIBLE
#ifdef    DEMOD_DVB_T
  if (front_end->chip ==   0x2183 ) {
    switch (hierarchy) {
      case Si2183_DVBT_STATUS_RESPONSE_HIERARCHY_NONE : return SILABS_HIERARCHY_NONE;
      case Si2183_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA1: return SILABS_HIERARCHY_ALFA1;
      case Si2183_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA2: return SILABS_HIERARCHY_ALFA2;
      case Si2183_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA4: return SILABS_HIERARCHY_ALFA4;
      default                                         : return -1;
    }
  }
#endif /* DEMOD_DVB_T */
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  Custom_pilotPatternCode function
  Use:        pilot pattern code function
              Used to retrieve the pilot pattern value used by the DVB-T2 demodulator in custom format
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  pilot_pattern, the value used by the top-level application (as returned by the demod)
************************************************************************************************************************/
signed   int  Custom_pilotPatternCode               (SILABS_FE_Context* front_end,    signed   int pilot_pattern)
{
  front_end->chip = front_end->chip; /* To avoid compiler warning if not supported */
  pilot_pattern   = pilot_pattern  ; /* To avoid compiler warning if not supported */
#ifdef    Si2183_COMPATIBLE
#ifdef    DEMOD_DVB_T2
  if (front_end->chip ==   0x2183 ) {
    switch (pilot_pattern) {
      case Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP1: return SILABS_PILOT_PATTERN_PP1;
      case Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP2: return SILABS_PILOT_PATTERN_PP2;
      case Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP3: return SILABS_PILOT_PATTERN_PP3;
      case Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP4: return SILABS_PILOT_PATTERN_PP4;
      case Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP5: return SILABS_PILOT_PATTERN_PP5;
      case Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP6: return SILABS_PILOT_PATTERN_PP6;
      case Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP7: return SILABS_PILOT_PATTERN_PP7;
      case Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP8: return SILABS_PILOT_PATTERN_PP8;
      default                                            : return -1;
    }
  }
#endif /* DEMOD_DVB_T2 */
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  Custom_T2VersionCode function
  Use:        pilot pattern code function
              Used to retrieve the t2_version value used by the DVB-T2 demodulator in custom format
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  t2_version, the value used by the top-level application (as returned by the demod)
************************************************************************************************************************/
signed   int  Custom_T2VersionCode                  (SILABS_FE_Context* front_end,    signed   int t2_version)
{
  front_end->chip = front_end->chip; /* To avoid compiler warning if not supported */
  t2_version      = t2_version     ; /* To avoid compiler warning if not supported */
#ifdef    Si2183_COMPATIBLE
#ifdef    DEMOD_DVB_T2
  if (front_end->chip ==   0x2183 ) {
    switch (t2_version) {
      case Si2183_DVBT2_STATUS_RESPONSE_T2_VERSION_1_1_1: return SILABS_T2_VERSION_1_1_1;
      case Si2183_DVBT2_STATUS_RESPONSE_T2_VERSION_1_2_1: return SILABS_T2_VERSION_1_2_1;
      case Si2183_DVBT2_STATUS_RESPONSE_T2_VERSION_1_3_1: return SILABS_T2_VERSION_1_3_1;
      default                                            : return -1;
    }
  }
#endif /* DEMOD_DVB_T2 */
#endif /* Si2183_COMPATIBLE */
  return -1;
}

#endif /* Translation functions from 'SiLabs' values to 'Custom' values */
       /* Text functions returning strings based on 'Custom' values.    */
#if 1
/************************************************************************************************************************
  Silabs_Standard_Text function
  Use:        standard text retrieval function
              Used to retrieve the standard text used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  standard, the value used by the top-level application (configurable in CUSTOM_Standard_Enum)
************************************************************************************************************************/
char*         Silabs_Standard_Text                  (signed   int               standard)
{
  switch (standard) {
    case SILABS_ANALOG: {return (char *)"ANALOG" ;}
    case SILABS_DVB_T : {return (char *)"DVB-T"  ;}
    case SILABS_DVB_T2: {return (char *)"DVB-T2" ;}
    case SILABS_DVB_C : {return (char *)"DVB-C"  ;}
    case SILABS_DVB_C2: {return (char *)"DVB-C2" ;}
    case SILABS_MCNS  : {return (char *)"MCNS"   ;}
    case SILABS_DVB_S : {return (char *)"DVB-S"  ;}
    case SILABS_DVB_S2: {return (char *)"DVB-S2" ;}
    case SILABS_DSS   : {return (char *)"DSS"    ;}
    case SILABS_ISDB_T: {return (char *)"ISDB-T" ;}
    case SILABS_SLEEP : {return (char *)"SLEEP"  ;}
    case SILABS_OFF   : {return (char *)"OFF"    ;}
    default           : {return (char *)"UNKNOWN";}
  }
}
/************************************************************************************************************************
  Silabs_Standard_Capability function
  Use:        standard capability retrieval function
              Used to know whether the front-end can handle a given standard
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  standard, the value used by the top-level application (configurable in CUSTOM_Standard_Enum)
  Returns  :  1 if the front-end can demodulate the standard
************************************************************************************************************************/
signed   int  Silabs_Standard_Capability            (signed   int               standard)
{
  switch (standard) {
    case SILABS_ANALOG: {return 1;}
#ifdef    DEMOD_DVB_T
    case SILABS_DVB_T : {return 1;}
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_DVB_T2
    case SILABS_DVB_T2: {return 1;}
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_DVB_C
    case SILABS_DVB_C : {return 1;}
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_C2
    case SILABS_DVB_C2: {return 1;}
#endif /* DEMOD_DVB_C2 */
#ifdef    DEMOD_MCNS
    case SILABS_MCNS  : {return 1;}
#endif /* DEMOD_MCNS */
#ifdef    DEMOD_DVB_S_S2_DSS
    case SILABS_DVB_S :
    case SILABS_DVB_S2:
    case SILABS_DSS   : {return 1;}
#endif /* DEMOD_DVB_S_S2_DSS */
#ifdef    DEMOD_ISDB_T
    case SILABS_ISDB_T: {return 1;}
#endif /* DEMOD_ISDB_T */
    default           : {return 0;}
  }
  return 0;
}
/************************************************************************************************************************
  Silabs_Constel_Text function
  Use:        constel text retrieval function
              Used to retrieve the constel text used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  constel, the value used by the top-level application (configurable in CUSTOM_Constel_Enum)
************************************************************************************************************************/
char*         Silabs_Constel_Text                   (CUSTOM_Constel_Enum        constel)
{
  switch (constel) {
    case SILABS_QAMAUTO : { return (char *)"QAMAUTO" ; break;}
    case SILABS_QAM16   : { return (char *)"QAM16"   ; break;}
    case SILABS_QAM32   : { return (char *)"QAM32"   ; break;}
    case SILABS_QAM64   : { return (char *)"QAM64"   ; break;}
    case SILABS_QAM128  : { return (char *)"QAM128"  ; break;}
    case SILABS_QAM256  : { return (char *)"QAM256"  ; break;}
    case SILABS_QPSK    : { return (char *)"QPSK"    ; break;}
    case SILABS_8PSK    : { return (char *)"8PSK"    ; break;}
    case SILABS_QAM1024 : { return (char *)"QAM1024" ; break;}
    case SILABS_QAM4096 : { return (char *)"QAM4096" ; break;}
    case SILABS_8APSK_L : { return (char *)"8APSK"   ; break;}
    case SILABS_16APSK  : { return (char *)"16APSK"  ; break;}
    case SILABS_16APSK_L: { return (char *)"16APSK_L"; break;}
    case SILABS_32APSK_1: { return (char *)"32APSK_1"; break;}
    case SILABS_32APSK_2: { return (char *)"32APSK_2"; break;}
    case SILABS_32APSK_L: { return (char *)"32APSK_L"; break;}
    case SILABS_DQPSK   : { return (char *)"DQPSK"   ; break;}
    default             : { return (char *)"UNKNOWN" ; break;}
  }
}
/************************************************************************************************************************
  Silabs_Polarization_Text function
  Use:        polarization text retrieval function
              Used to retrieve the polarization text used by the front-end
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  polarization, the value used by the top-level application (configurable in CUSTOM_Polarization_Enum)
************************************************************************************************************************/
char*         Silabs_Polarization_Text              (CUSTOM_Polarization_Enum   polarization)
{
  switch (polarization) {
    case SILABS_POLARIZATION_HORIZONTAL    : { return (char *)"Horizontal"; break;}
    case SILABS_POLARIZATION_VERTICAL      : { return (char *)"Vertical"  ; break;}
    case SILABS_POLARIZATION_DO_NOT_CHANGE : { return (char *)"Unchanged" ; break;}
    default                                : { return (char *)"UNKNOWN"   ; break;}
  }
}
/************************************************************************************************************************
  Silabs_Band_Text function
  Use:        polarization text retrieval function
              Used to retrieve the polarization text used by the front-end
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  polarization, the value used by the top-level application (configurable in CUSTOM_Band_Enum)
************************************************************************************************************************/
char*         Silabs_Band_Text                      (CUSTOM_Band_Enum           band)
{
  switch (band) {
    case SILABS_BAND_LOW          : { return (char *)"Low "     ; break;}
    case SILABS_BAND_HIGH         : { return (char *)"High"     ; break;}
    case SILABS_BAND_DO_NOT_CHANGE: { return (char *)"Unchanged"; break;}
    default                       : { return (char *)"UNKNOWN"  ; break;}
  }
}
/************************************************************************************************************************
  Silabs_Stream_Text function
  Use:        stream text retrieval function
              Used to retrieve the stream text used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  stream, the value used by the top-level application (configurable in CUSTOM_Stream_Enum)
************************************************************************************************************************/
char*         Silabs_Stream_Text                    (CUSTOM_Stream_Enum         stream)
{
  switch (stream) {
    case SILABS_HP    : { return (char *)"HP"     ; break;}
    case SILABS_LP    : { return (char *)"LP"     ; break;}
    default           : { return (char *)"UNKNOWN"; break;}
  }
}
/************************************************************************************************************************
  Silabs_TS_Mode_Text function
  Use:        Ts mode text retrieval function
              Used to retrieve the stream text used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  ts_mode, the value used by the top-level application (configurable in CUSTOM_Stream_Enum)
************************************************************************************************************************/
char*         Silabs_TS_Mode_Text                   (CUSTOM_TS_Mode_Enum        ts_mode)
{
  switch (ts_mode) {
#ifdef    USB_Capability
    case SILABS_TS_GPIF      : { return (char *)"GPIF"       ; break;}
    case SILABS_TS_SLAVE_FIFO: { return (char *)"SLAVE_FIFO" ; break;}
#endif /* USB_Capability */
    case SILABS_TS_OFF       : { return (char *)"OFF"        ; break;}
    case SILABS_TS_PARALLEL  : { return (char *)"PARALLEL"   ; break;}
    case SILABS_TS_SERIAL    : { return (char *)"SERIAL"     ; break;}
    case SILABS_TS_TRISTATE  : { return (char *)"TRISTATE"   ; break;}
    default                  : { return (char *)"UNKNOWN"    ; break;}
  }
}
/************************************************************************************************************************
  Silabs_PLPType_Text function
  Use:        plp type text retrieval function
              Used to retrieve the plp type text string
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  plp_type, the value used by the top-level application (configurable in CUSTOM_T2_PLP_TYPE)
************************************************************************************************************************/
char*         Silabs_PLPType_Text                   (CUSTOM_T2_PLP_TYPE         plp_type)
{
  switch (plp_type) {
    case SILABS_PLP_TYPE_COMMON     : { return (char *)"COMMON"     ; break;}
    case SILABS_PLP_TYPE_DATA_TYPE1 : { return (char *)"DATA_TYPE1" ; break;}
    case SILABS_PLP_TYPE_DATA_TYPE2 : { return (char *)"DATA_TYPE2" ; break;}
    default           : { return (char *)"UNKNOWN"; break;}
  }
}
/************************************************************************************************************************
  Silabs_FFT_Text function
  Use:        fft text retrieval function
              Used to retrieve the fft text used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  fft, the value used by the top-level application (configurable in CUSTOM_FFT_Mode_Enum)
************************************************************************************************************************/
char*         Silabs_FFT_Text                       (CUSTOM_FFT_Mode_Enum       fft)
{
  switch (fft) {
    case SILABS_FFT_MODE_1K   : { return (char *)" 1K"    ; break;}
    case SILABS_FFT_MODE_2K   : { return (char *)" 2K"    ; break;}
    case SILABS_FFT_MODE_4K   : { return (char *)" 4K"    ; break;}
    case SILABS_FFT_MODE_8K   : { return (char *)" 8K"    ; break;}
    case SILABS_FFT_MODE_16K  : { return (char *)"16K"    ; break;}
    case SILABS_FFT_MODE_32K  : { return (char *)"32K"    ; break;}
    default                   : { SiTRACE_X("UNKNOWN FFT mode value %d\n", fft); return (char *)"UNKNOWN"; break;}
  }
}
/************************************************************************************************************************
  Silabs_GI_Text function
  Use:        gi text retrieval function
              Used to retrieve the gi text used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  gi, the value used by the top-level application (configurable in CUSTOM_GI_Enum)
************************************************************************************************************************/
char*         Silabs_GI_Text                        (CUSTOM_GI_Enum             gi)
{
  switch (gi) {
    case SILABS_GUARD_INTERVAL_1_32     : { return (char *)"1/32"    ; break;}
    case SILABS_GUARD_INTERVAL_1_16     : { return (char *)"1/16"    ; break;}
    case SILABS_GUARD_INTERVAL_1_8      : { return (char *)"1/8"     ; break;}
    case SILABS_GUARD_INTERVAL_1_4      : { return (char *)"1/4"     ; break;}
    case SILABS_GUARD_INTERVAL_1_128    : { return (char *)"1/128"   ; break;}
    case SILABS_GUARD_INTERVAL_19_128   : { return (char *)"19/128"  ; break;}
    case SILABS_GUARD_INTERVAL_19_256   : { return (char *)"19/256"  ; break;}
    case SILABS_GUARD_INTERVAL_1_64     : { return (char *)"1/64"    ; break;}
    default                             : { SiTRACE_X("UNKNOWN GI value %d\n", gi); return (char *)"UNKNOWN" ; break;}
  }
}
/************************************************************************************************************************
  Silabs_Coderate_Text function
  Use:        coderate text retrieval function
              Used to retrieve the coderate text used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  coderate, the value used by the top-level application (configurable in CUSTOM_Coderate_Enum)
************************************************************************************************************************/
char*         Silabs_Coderate_Text                  (CUSTOM_Coderate_Enum       coderate)
{
  switch (coderate) {
    case SILABS_CODERATE_1_2    : { return (char *)"1/2"    ; break;}
    case SILABS_CODERATE_2_3    : { return (char *)"2/3"    ; break;}
    case SILABS_CODERATE_3_4    : { return (char *)"3/4"    ; break;}
    case SILABS_CODERATE_4_5    : { return (char *)"4/5"    ; break;}
    case SILABS_CODERATE_5_6    : { return (char *)"5/6"    ; break;}
    case SILABS_CODERATE_7_8    : { return (char *)"7/8"    ; break;}
    case SILABS_CODERATE_8_9    : { return (char *)"8/9"    ; break;}
    case SILABS_CODERATE_9_10   : { return (char *)"9/10"   ; break;}
    case SILABS_CODERATE_1_3    : { return (char *)"1/3"    ; break;}
    case SILABS_CODERATE_1_4    : { return (char *)"1/4"    ; break;}
    case SILABS_CODERATE_2_5    : { return (char *)"2/5"    ; break;}
    case SILABS_CODERATE_3_5    : { return (char *)"3/5"    ; break;}
    case SILABS_CODERATE_5_9    : { return (char *)"5/9"    ; break;}
    case SILABS_CODERATE_7_9    : { return (char *)"7/9"    ; break;}
    case SILABS_CODERATE_8_15   : { return (char *)"8/15"   ; break;}
    case SILABS_CODERATE_11_15  : { return (char *)"11/15"  ; break;}
    case SILABS_CODERATE_13_18  : { return (char *)"13/18"  ; break;}
    case SILABS_CODERATE_9_20   : { return (char *)"9/20"   ; break;}
    case SILABS_CODERATE_11_20  : { return (char *)"11/20"  ; break;}
    case SILABS_CODERATE_23_36  : { return (char *)"23/36"  ; break;}
    case SILABS_CODERATE_25_36  : { return (char *)"25/36"  ; break;}
    case SILABS_CODERATE_13_45  : { return (char *)"13/45"  ; break;}
    case SILABS_CODERATE_26_45  : { return (char *)"26/45"  ; break;}
    case SILABS_CODERATE_28_45  : { return (char *)"28/45"  ; break;}
    case SILABS_CODERATE_32_45  : { return (char *)"32/45"  ; break;}
    case SILABS_CODERATE_77_90  : { return (char *)"77/90"  ; break;}
    default                     : { SiTRACE_X("UNKNOWN code rate value %d\n", coderate); return (char *)"UNKNOWN"; break;}
  }
}
/************************************************************************************************************************
  Silabs_Extended_BW_Text function
  Use:        bw_ext text retrieval function
              Used to retrieve the bw_ext text used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  bw_extended, value used by the top-level application (configurable in CUSTOM_T2_BwExtended_Enum)
************************************************************************************************************************/
char*         Silabs_Extended_BW_Text               (signed   int bw_extended)
{
  switch (bw_extended) {
    case 0  : { return (char *)"normal  " ; break;}
    case 1  : { return (char *)"extended" ; break;}
    default : { SiTRACE_X("UNKNOWN bw_extended value %d\n",bw_extended); return (char *)"UNKNOWN" ; break;}
  }
}
/************************************************************************************************************************
  Silabs_Rotated_QAM_Text function
  Use:        rotated text retrieval function
              Used to retrieve the rotated text used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  rotated, a 0/1 flag indicating the QAM rotation (0 = 'normal', 1 = 'rotated')
************************************************************************************************************************/
char*         Silabs_Rotated_QAM_Text               (signed   int rotated)
{
  switch (rotated) {
    case 0  : { return (char *)"normal "     ; break;}
    case 1  : { return (char *)"rotated"     ; break;}
    default : { SiTRACE_X("UNKNOWN QAM rotation value %d\n",rotated); return (char *)"UNKNOWN"; break;}
  }
}
/************************************************************************************************************************
  Silabs_T2_Base_Lite_Text function
  Use:        T2 Base / Lite text retrieval function
              Used to retrieve the 'base/lite' T2 mode used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  t2_base_lite, a 0/1 flag indicating the T2 mode (0 = 'base', 1 = 'lite')
************************************************************************************************************************/
char*         Silabs_T2_Base_Lite_Text              (signed   int t2_base_lite)
{
  switch (t2_base_lite) {
    case 0  : { return (char *)"T2-Base"     ; break;}
    case 1  : { return (char *)"T2-Lite"     ; break;}
    default : { SiTRACE_X("UNKNOWN T2 base/lite value %d\n",t2_base_lite); return (char *)"UNKNOWN"; break;}
  }
}
/************************************************************************************************************************
  Silabs_T2_Version_Text function
  Use:        T2 Version text retrieval function
              Used to retrieve the T2 version used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  t2_version, a value indicating the T2 version
************************************************************************************************************************/
char*         Silabs_T2_Version_Text                (CUSTOM_Pilot_T2_version_Enum t2_version)
{
  switch (t2_version) {
    case SILABS_T2_VERSION_1_1_1  : { return (char *)"1.1.1"     ; break;}
    case SILABS_T2_VERSION_1_2_1  : { return (char *)"1.2.1"     ; break;}
    case SILABS_T2_VERSION_1_3_1  : { return (char *)"1.3.1"     ; break;}
    default : { SiTRACE_X("UNKNOWN T2 version value %d\n",t2_version); return (char *)"UNKNOWN"; break;}
  }
}
/************************************************************************************************************************
  Silabs_FEF_Text function
  Use:        fef text retrieval function
              Used to retrieve the fef text used by the demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  fef, a 0/1 flag indicating the fef presence (0 = 'no fef', 1 = 'fef')
************************************************************************************************************************/
char*         Silabs_FEF_Text                       (signed   int fef)
{
  switch (fef) {
    case 0   : { return (char *)"  no"   ; break;}
    case 1   : { return (char *)"with"   ; break;}
    default  : { SiTRACE_X("UNKNOWN FEF value %d\n",fef); return (char *)"UNKNOWN"; break;}
  }
}
/************************************************************************************************************************
  Silabs_MISO_Text function
  Use:        tx text retrieval function
              Used to retrieve the tx text used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  tx, the value used by the top-level application (1 for MISO, 0 otherwise)
************************************************************************************************************************/
char*         Silabs_MISO_Text                      (signed   int siso_miso)
{
  switch (siso_miso) {
    case 0   : { return (char *)"SISO"  ; break;}
    case 1   : { return (char *)"MISO"  ; break;}
    default  : { SiTRACE_X("UNKNOWN tx_mode %d\n", siso_miso); return (char *)"UNKNOWN"; break;}
  }
}
/************************************************************************************************************************
  Silabs_Pilot_Pattern_Text function
  Use:        pilot_pattern text retrieval function
              Used to retrieve the pilot_pattern text used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  pilot_pattern, the value used by the top-level application (configurable in CUSTOM_Pilot_Pattern_Enum)
************************************************************************************************************************/
char*         Silabs_Pilot_Pattern_Text             (CUSTOM_Pilot_Pattern_Enum    pilot_pattern)
{
  switch (pilot_pattern) {
    case SILABS_PILOT_PATTERN_PP1   : { return (char *)"PP1"  ; break;}
    case SILABS_PILOT_PATTERN_PP2   : { return (char *)"PP2"  ; break;}
    case SILABS_PILOT_PATTERN_PP3   : { return (char *)"PP3"  ; break;}
    case SILABS_PILOT_PATTERN_PP4   : { return (char *)"PP4"  ; break;}
    case SILABS_PILOT_PATTERN_PP5   : { return (char *)"PP5"  ; break;}
    case SILABS_PILOT_PATTERN_PP6   : { return (char *)"PP6"  ; break;}
    case SILABS_PILOT_PATTERN_PP7   : { return (char *)"PP7"  ; break;}
    case SILABS_PILOT_PATTERN_PP8   : { return (char *)"PP8"  ; break;}
    default                         : { SiTRACE_X("UNKNOWN Pilot Pattern %d\n", pilot_pattern); return (char *)"UNKNOWN"; break;}
  }
}
/************************************************************************************************************************
  Silabs_No_Short_Frame_Text function
  Use:        frame text retrieval function
              Used to retrieve the frame text used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  no_short_frame, the value used by the top-level application (0 for 'short frame', 1 for 'normal frame')
************************************************************************************************************************/
char*         Silabs_No_Short_Frame_Text            (signed   int no_short_frame)
{
  switch (no_short_frame) {
    case 0   : { return (char *)"short  "; break;}
    case 1   : { return (char *)"normal "; break;}
    default  : { SiTRACE_X("UNKNOWN short frame value %d\n", no_short_frame); return (char *)"UNKNOWN"; break;}
  }
}
/************************************************************************************************************************
  Silabs_Pilots_Text function
  Use:        frame text retrieval function
              Used to retrieve the frame text used by the DTV demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  pilots, the value used by the top-level application (0 for 'off', 1 for 'on')
************************************************************************************************************************/
char*         Silabs_Pilots_Text                    (signed   int pilots)
{
  switch (pilots) {
    case 0   : { return (char *)"OFF"    ; break;}
    case 1   : { return (char *)"ON "    ; break;}
    default  : { SiTRACE_X("UNKNOWN pilots flag %d\n",pilots); return (char *)"UNKNOWN"; break;}
  }
}

#endif /* Text functions returning strings based on 'Custom' values.    */

/************************************************************************************************************************
  rate_f_mant_exp function
  Use:        rate computing function
              Used to fill the integer/decimal/exponent parts of a scientific-displayed rate depending on
               the mant and exp values returned by the SiLabs API functions (used for BER/PER/FER display)
  Parameter:  mant, the mantissa value
  Parameter:  exp , the exponent value
  Parameter:  *rate_i, a pointer to a char used to store the integer part of the rate
  Parameter:  *rate_d, a pointer to a char used to store the decimal part of the rate
  Parameter:  *rate_e, a pointer to a char used to store the exponent part of the rate
  Returns:    0
************************************************************************************************************************/
signed   int  rate_f_mant_exp                       (signed   int mant, signed   int exp, char *rate_i, char *rate_d, char *rate_e )
{
  if (mant ==  0) {
    *rate_i = *rate_d = *rate_e = 0;
    return 0;
  }
  if (mant >= 10) {
    *rate_i = mant/10;
    *rate_d = mant%10;
    *rate_e = -exp+1;
  } else {
    *rate_i = mant;
    *rate_d = 0;
    *rate_e = -exp;
  }
  return 0;
}
/* Chip detection function (To Be Defined) */
/************************************************************************************************************************
  SiLabs_chip_detect function
  Use:        chip detection function
              Used to detect whether the demodulator is a DTV demodulator
  Behavior:   This function uses raw i2c reads to check the presence of either a Si2167 or a Si2169
  Parameter:  demodAdd, the I2C address of the demod
  Returns:    2167 if there is a Si2167, 2169 if there is a 2169, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_chip_detect                    (signed   int demodAdd)
{
  signed   int chip;
  chip = 0;
  SiTRACE_X("Detecting chip at address 0x%02x\n", demodAdd);
  demodAdd = demodAdd;
#ifdef    Si2183_COMPATIBLE
/* TODO (mdorval#2#): Find a way to detect the presence of a Si2183 */
  chip = 0x2183;
#endif /* Si2183_COMPATIBLE */
  SiTRACE_X("Chip  %d   (%X)\n", chip, chip);
  return chip;
}
/************************************************************************************************************************
  SiLabs_API_Demod_status function
  Use:        demodulator status function
              Used to retrieve the status of the demodulator in a structure
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  status, a pointer to the status structure (configurable in CUSTOM_Status_Struct)
  Return:     1 if successful, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_Demod_status               (SILABS_FE_Context* front_end,    CUSTOM_Status_Struct *status)
{
  SiTRACE("API CALL STATUS: SiLabs_API_Demod_status (front_end, &status);\n");
  return  SiLabs_API_Demod_status_selection ( front_end, status, 0x00);
}
/************************************************************************************************************************
  SiLabs_API_Demod_status_selection function
  Use:        demodulator status function, with control of the status items to be refreshed
              Used to retrieve the status of the demodulator in a structure
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  status, a pointer to the status structure (configurable in CUSTOM_Status_Struct)
  Parameter:  status_selection, an 8 bit field used to control which items to refresh. Use 0x00 for 'all'.
  Return:     1 if successful, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_Demod_status_selection     (SILABS_FE_Context* front_end,    CUSTOM_Status_Struct *status, unsigned char status_selection)
{
  SiTRACE("API CALL STATUS: SiLabs_API_Demod_status_selection %d/%x status_selection 0x%02x);\n", front_end->chip, front_end->chip, status_selection);

  if (status_selection == 0x00  )    { status_selection = FE_LOCK_STATE + FE_LEVELS + FE_RATES + FE_SPECIFIC + FE_QUALITY + FE_FREQ ;}

  /* Set to 0 all info which will be refreshed. This allows the status to be filled in several steps */
  if (status_selection & FE_LOCK_STATE) {
    status->demod_lock         =     0;
    status->fec_lock           =     0;
    status->uncorrs            = 65535; /* Set to max, the value it will take if not locked */
    status->TS_bitrate_kHz     =     0;
    status->TS_clock_kHz       =     0;
    status->s2x                =     0;
  }
  if (status_selection & FE_LEVELS    ) {
    status->RSSI               =  0;
    status->RFagc              =  0;
    status->IFagc              =  0;
  }
  if (status_selection & FE_RATES     ) {
    status->ber_mant           = -1; /* Set to '-1' to signal unavailability if not set later on */
    status->ber_exp            =  0; /* Set to '0'  to signal unavailability if not set later on */
    status->per_mant           = -1; /* Set to '-1' to signal unavailability if not set later on */
    status->per_exp            =  0; /* Set to '0'  to signal unavailability if not set later on */
    status->fer_mant           = -1; /* Set to '-1' to signal unavailability if not set later on */
    status->fer_exp            =  0; /* Set to '0'  to signal unavailability if not set later on */
    #ifndef   NO_FLOATS_ALLOWED
    status->ber                =  1;
    status->per                =  1;
    status->fer                =  1;
    #endif /* NO_FLOATS_ALLOWED */
    status->ber_window         =  1;
  }
  if (status_selection & FE_SPECIFIC  ) {
    status->bandwidth_Hz       =  0;
    status->symbol_rate        =  0;
    status->stream             =  0;
    status->constellation      =  0;
    #ifndef   NO_FLOATS_ALLOWED
    status->c_n                = 0.0;
    #endif /* NO_FLOATS_ALLOWED */
    status->c_n_100            =  0;
    status->freq_offset        =  0;
    status->timing_offset      =  0;
    status->code_rate          = -1;
    status->t2_version         =  0;
    status->num_plp            = -1; /* Will be '-1' if no MPLP mode is supported  */
    status->plp_id             =  0;
    status->isi_id             =  100;
    status->ds_id              =  0;
    status->cell_id            =  0;
    status->roll_off           =  0;
  }
  if (status_selection & FE_QUALITY   ) {
    status->SSI                = -1; /* Set to '-1' to call SiLabs_API_SSI_SQI if not set later on */
    status->SQI                = -1; /* Set to '-1' to call SiLabs_API_SSI_SQI if not set later on */
  }

  if (front_end->standard == SILABS_SLEEP ) {status->standard = SILABS_SLEEP; return 0;}

#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    status->demod_die = front_end->Si2183_FE->demod->rsp->get_rev.mcm_die;
    /* Mimick Si2167 clock_mode register values */
    switch (front_end->Si2183_FE->demod->cmd->start_clk.clk_mode) {
      case Si2183_START_CLK_CMD_CLK_MODE_CLK_CLKIO   : status->clock_mode =  32; break;
      case Si2183_START_CLK_CMD_CLK_MODE_CLK_XTAL_IN : status->clock_mode =  34; break;
      case Si2183_START_CLK_CMD_CLK_MODE_XTAL        : status->clock_mode =  33; break;
      default                                        : status->clock_mode =   0; break;
    }
    if (status_selection & FE_LOCK_STATE) { SiTRACE("Checking FE_LOCK_STATE\n");
      if (Si2183_L1_DD_STATUS (front_end->Si2183_FE->demod, Si2183_DD_STATUS_CMD_INTACK_OK) != NO_Si2183_ERROR) {
        SiERROR("Si2183_L1_DD_STATUS ERROR\n");
        return 0;
      }
      status->standard = Custom_standardCode(front_end, front_end->Si2183_FE->demod->rsp->dd_status.modulation);
      SiTRACE("DD_STATUS 0x%02x: demod_lock %d fec_lock %d, current standard %s\n", front_end->Si2183_FE->demod->i2c->address, front_end->Si2183_FE->demod->rsp->dd_status.pcl, front_end->Si2183_FE->demod->rsp->dd_status.dl, Silabs_Standard_Text((CUSTOM_Standard_Enum)status->standard) );
      /* Retrieving TS  values */
      status->TS_bitrate_kHz  = front_end->Si2183_FE->demod->rsp->dd_status.ts_bit_rate*10;
      status->TS_clock_kHz    = front_end->Si2183_FE->demod->rsp->dd_status.ts_clk_freq*10;
      status->demod_lock      = front_end->Si2183_FE->demod->rsp->dd_status.pcl;
      status->fec_lock        = front_end->Si2183_FE->demod->rsp->dd_status.dl;
      if (status->fec_lock) {
        if ( Si2183_L1_DD_UNCOR  (front_end->Si2183_FE->demod, Si2183_DD_UNCOR_CMD_RST_RUN) != NO_Si2183_ERROR ) return 0;
        status->uncorrs            = (front_end->Si2183_FE->demod->rsp->dd_uncor.uncor_msb<<8) + front_end->Si2183_FE->demod->rsp->dd_uncor.uncor_lsb;
      }
      /* when unlocked, FE_RATES   will return 1 for all rates, so skip FE_RATES if not locked */
      if ((status_selection & FE_RATES    ) && !(status->fec_lock)) {status_selection = status_selection - FE_RATES   ;}
      /* when unlocked, FE_SPECIFIC   will not be valid, so skip FE_SPECIFIC if not locked */
      if ((status_selection & FE_SPECIFIC ) && !(status->fec_lock)) {status_selection = status_selection - FE_SPECIFIC;}
    } else {
      /* if the standard is not refreshed, use the previous value, which is stored in the context */
      status->standard = Custom_standardCode(front_end, front_end->Si2183_FE->demod->prop->dd_mode.modulation);
    }
    /* Retrieving AGC values */
    if (status_selection & FE_LEVELS    ) { SiTRACE("Checking FE_LEVELS\n"    );
      switch (status->standard) {
#ifdef    TERRESTRIAL_FRONT_END
  #ifdef    DEMOD_DVB_T
        case SILABS_DVB_T :
  #endif /* DEMOD_DVB_T */
  #ifdef    DEMOD_DVB_C
        case SILABS_DVB_C :
  #endif /* DEMOD_DVB_C */
  #ifdef    DEMOD_MCNS
        case SILABS_MCNS :
  #endif /* DEMOD_MCNS */
  #ifdef    DEMOD_DVB_C2
        case SILABS_DVB_C2 :
  #endif /* DEMOD_DVB_C2 */
  #ifdef    DEMOD_DVB_T2
        case SILABS_DVB_T2:
  #endif /* DEMOD_DVB_T2 */
  #ifdef    DEMOD_ISDB_T
        case SILABS_ISDB_T:
  #endif /* DEMOD_ISDB_T */
        {
          Si2183_L1_DD_EXT_AGC_TER (front_end->Si2183_FE->demod,
                                    Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MODE_NO_CHANGE,
                                    front_end->Si2183_FE->demod->cmd->dd_ext_agc_ter.agc_1_inv,
                                    Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_NO_CHANGE,
                                    front_end->Si2183_FE->demod->cmd->dd_ext_agc_ter.agc_2_inv,
                                    front_end->Si2183_FE->demod->cmd->dd_ext_agc_ter.agc_1_kloop,
                                    front_end->Si2183_FE->demod->cmd->dd_ext_agc_ter.agc_2_kloop,
                                    front_end->Si2183_FE->demod->cmd->dd_ext_agc_ter.agc_1_min,
                                    front_end->Si2183_FE->demod->cmd->dd_ext_agc_ter.agc_2_min );
          status->RFagc              = 0;
          if (front_end->Si2183_FE->demod->cmd->dd_ext_agc_ter.agc_1_mode  != Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MODE_NOT_USED) {
            status->IFagc              = front_end->Si2183_FE->demod->rsp->dd_ext_agc_ter.agc_1_level;
          } else {
            status->IFagc              = front_end->Si2183_FE->demod->rsp->dd_ext_agc_ter.agc_2_level;
          }
  #ifdef    TUNERTER_API
          status->RSSI               = front_end->Si2183_FE->tuner_ter->rsp->tuner_status.rssi;
  #else  /* TUNERTER_API */
          status->RSSI               = front_end->Si2183_FE->tuner_ter->rssi;
  #endif /* TUNERTER_API */
          status->RSSI = status->RSSI + front_end->TER_RSSI_offset;
        break;
      }
#endif /* TERRESTRIAL_FRONT_END */

#ifdef    SATELLITE_FRONT_END
        case SILABS_DVB_S :
        case SILABS_DVB_S2:
        case SILABS_DSS   :
        {
          Si2183_L1_DD_EXT_AGC_SAT (front_end->Si2183_FE->demod,
                                    Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_NO_CHANGE,
                                    front_end->Si2183_FE->demod->cmd->dd_ext_agc_sat.agc_1_inv,
                                    Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MODE_NO_CHANGE,
                                    front_end->Si2183_FE->demod->cmd->dd_ext_agc_sat.agc_2_inv,
                                    front_end->Si2183_FE->demod->cmd->dd_ext_agc_sat.agc_1_kloop,
                                    front_end->Si2183_FE->demod->cmd->dd_ext_agc_sat.agc_2_kloop,
                                    front_end->Si2183_FE->demod->cmd->dd_ext_agc_sat.agc_1_min,
                                    front_end->Si2183_FE->demod->cmd->dd_ext_agc_sat.agc_2_min );
          status->RFagc              = 0;
          if (front_end->Si2183_FE->demod->cmd->dd_ext_agc_sat.agc_1_mode  != Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_NOT_USED) {
            status->IFagc            = front_end->Si2183_FE->demod->rsp->dd_ext_agc_sat.agc_1_level;
          } else {
            status->IFagc            = front_end->Si2183_FE->demod->rsp->dd_ext_agc_sat.agc_2_level;
          }
  #ifndef   NO_SAT
          status->RSSI               = status->rssi*1; /* dBm conversion of rssi */
          #ifdef   SAT_TUNER_RSSI_FROM_IFAGC
           /* Checking that SAT_TUNER_RSSI_FROM_IFAGC supports the SAT tuner */
          if (SAT_TUNER_RSSI_FROM_IFAGC(front_end->Si2183_FE->tuner_sat, status->IFagc) != -1000) {
            SiLabs_API_SAT_Tuner_I2C_Enable  (front_end);
            status->RSSI             = SAT_TUNER_RSSI_FROM_IFAGC(front_end->Si2183_FE->tuner_sat, status->IFagc);
            SiLabs_API_SAT_Tuner_I2C_Disable (front_end);
          }
          #endif /* SAT_TUNER_RSSI_FROM_IFAGC */
          status->RSSI = status->RSSI + front_end->SAT_RSSI_offset;
  #endif /* NO_SAT */
          break;
        }
#endif /* SATELLITE_FRONT_END */
        default           : {
          status->RFagc              = 0;
          status->IFagc              = 0;
          break;
        }
      }
    }
    /* Retrieving BER/PER/FER values */
    if (status_selection & FE_RATES     ) { SiTRACE("Checking FE_RATES\n"     );
      if (front_end->Si2183_FE->demod->rsp->dd_status.dl == 1) { /* Only check rates when locked */
        switch (status->standard) {
          case SILABS_ANALOG: {
            return 1;
            break;
          }
    #ifdef    DEMOD_DVB_T
          case SILABS_DVB_T :
    #endif /* DEMOD_DVB_T */
    #ifdef    DEMOD_ISDB_T
          case SILABS_ISDB_T :
    #endif /* DEMOD_ISDB_T */
    #ifdef    DEMOD_DVB_C
          case SILABS_DVB_C :
    #endif /* DEMOD_DVB_C */
    #ifdef    DEMOD_MCNS
          case SILABS_MCNS :
    #endif /* DEMOD_MCNS */
    #ifdef    DEMOD_DVB_C2
          case SILABS_DVB_C2:
    #endif /* DEMOD_DVB_C2 */
    #ifdef    DEMOD_DVB_S_S2_DSS
          case SILABS_DVB_S :
          case SILABS_DSS   :
    #endif /* DEMOD_DVB_S_S2_DSS */
          {
            if ( Si2183_L1_DD_BER    (front_end->Si2183_FE->demod, Si2183_DD_BER_CMD_RST_RUN  ) != NO_Si2183_ERROR ) return 0;
            status->ber_window         = power_of_n(10, front_end->Si2183_FE->demod->prop->dd_ber_resol.exp)*front_end->Si2183_FE->demod->prop->dd_ber_resol.mant;
            /* CHECK the exponent value to know if the BER is available or not */
            if(front_end->Si2183_FE->demod->rsp->dd_ber.exp!=0) {
              status->ber_mant           = (front_end->Si2183_FE->demod->rsp->dd_ber.mant);
              status->ber_exp            = (front_end->Si2183_FE->demod->rsp->dd_ber.exp+1);
    #ifndef   NO_FLOATS_ALLOWED
              status->ber                = (front_end->Si2183_FE->demod->rsp->dd_ber.mant/10.0) / power_of_n(10, front_end->Si2183_FE->demod->rsp->dd_ber.exp);
    #endif /* NO_FLOATS_ALLOWED */
              status->ber_count          = power_of_n(10, (front_end->Si2183_FE->demod->prop->dd_ber_resol.exp - status->ber_exp) )*status->ber_mant;
            } else {
              status->ber_count          = status->ber_window;
            }
            if ( Si2183_L1_DD_PER    (front_end->Si2183_FE->demod, Si2183_DD_PER_CMD_RST_RUN  ) != NO_Si2183_ERROR ) return 0;
            /* CHECK the exponent value to know if the PER is available or not*/
            if(front_end->Si2183_FE->demod->rsp->dd_per.exp!=0) {
                  status->per_mant           = (front_end->Si2183_FE->demod->rsp->dd_per.mant);
                  status->per_exp            = (front_end->Si2183_FE->demod->rsp->dd_per.exp+1);
    #ifndef   NO_FLOATS_ALLOWED
              status->per                = (front_end->Si2183_FE->demod->rsp->dd_per.mant/10.0) / power_of_n(10, front_end->Si2183_FE->demod->rsp->dd_per.exp);
    #endif /* NO_FLOATS_ALLOWED */
            }
            break;
          }
    #ifdef    DEMOD_DVB_S_S2_DSS
          case SILABS_DVB_S2:
    #endif /* DEMOD_DVB_S_S2_DSS */
    #ifdef    DEMOD_DVB_T2
          case SILABS_DVB_T2:
    #endif /* DEMOD_DVB_T2 */
           {
            if ( Si2183_L1_DD_BER    (front_end->Si2183_FE->demod, Si2183_DD_BER_CMD_RST_RUN  ) != NO_Si2183_ERROR ) return 0;
            status->ber_window         = power_of_n(10, front_end->Si2183_FE->demod->prop->dd_ber_resol.exp)*front_end->Si2183_FE->demod->prop->dd_ber_resol.mant;
            /* CHECK the exponent value to know if the BER is available or not*/
            if(front_end->Si2183_FE->demod->rsp->dd_ber.exp!=0) {
              status->ber_mant           = (front_end->Si2183_FE->demod->rsp->dd_ber.mant);
              status->ber_exp            = (front_end->Si2183_FE->demod->rsp->dd_ber.exp+1);
    #ifndef   NO_FLOATS_ALLOWED
              status->ber                = (front_end->Si2183_FE->demod->rsp->dd_ber.mant/10.0) / power_of_n(10, front_end->Si2183_FE->demod->rsp->dd_ber.exp);
    #endif /* NO_FLOATS_ALLOWED */
              status->ber_count          = power_of_n(10, (front_end->Si2183_FE->demod->prop->dd_ber_resol.exp - status->ber_exp) )*status->ber_mant;
            } else {
              status->ber_count          = status->ber_window;
            }
            if ( Si2183_L1_DD_FER    (front_end->Si2183_FE->demod, Si2183_DD_FER_CMD_RST_RUN  ) != NO_Si2183_ERROR ) return 0;
            /* CHECK the exponent value to know if the FER is available or not*/
            if(front_end->Si2183_FE->demod->rsp->dd_fer.exp!=0) {
              status->fer_mant           = (front_end->Si2183_FE->demod->rsp->dd_fer.mant);
              status->fer_exp            = (front_end->Si2183_FE->demod->rsp->dd_fer.exp+1);
    #ifndef   NO_FLOATS_ALLOWED
              status->fer                = (front_end->Si2183_FE->demod->rsp->dd_fer.mant/10.0) / power_of_n(10, front_end->Si2183_FE->demod->rsp->dd_fer.exp);
    #endif /* NO_FLOATS_ALLOWED */
            }
            if ( Si2183_L1_DD_PER    (front_end->Si2183_FE->demod, Si2183_DD_PER_CMD_RST_RUN  ) != NO_Si2183_ERROR ) return 0;
            /* CHECK the exponent value to know if the PER is available or not*/
            if(front_end->Si2183_FE->demod->rsp->dd_per.exp!=0) {
              status->per_mant           = (front_end->Si2183_FE->demod->rsp->dd_per.mant);
              status->per_exp            = (front_end->Si2183_FE->demod->rsp->dd_per.exp+1);
    #ifndef   NO_FLOATS_ALLOWED
              status->per                = (front_end->Si2183_FE->demod->rsp->dd_per.mant/10.0) / power_of_n(10, front_end->Si2183_FE->demod->rsp->dd_per.exp);
    #endif /* NO_FLOATS_ALLOWED */
        }
            break;
          }
          default           : { return 0; break; }
        }
      }
    }
    /* Retrieving standard specific values */
    if (status_selection & FE_SPECIFIC  ) { SiTRACE("Checking FE_SPECIFIC\n"  );
      switch (status->standard) {
  #ifdef    DEMOD_DVB_T
        case SILABS_DVB_T  : {
          if (Si2183_L1_DVBT_STATUS    (front_end->Si2183_FE->demod, Si2183_DVBT_STATUS_CMD_INTACK_OK)   != NO_Si2183_ERROR) return 0;
          if (Si2183_L1_DVBT_TPS_EXTRA (front_end->Si2183_FE->demod)                                     != NO_Si2183_ERROR) return 0;
          status->demod_lock         = front_end->Si2183_FE->demod->rsp->dvbt_status.pcl;
          status->fec_lock           = front_end->Si2183_FE->demod->rsp->dvbt_status.dl;
          status->spectral_inversion = front_end->Si2183_FE->demod->rsp->dvbt_status.sp_inv;
          status->freq_offset        = front_end->Si2183_FE->demod->rsp->dvbt_status.afc_freq;
          status->timing_offset      = front_end->Si2183_FE->demod->rsp->dvbt_status.timing_offset;
          status->bandwidth_Hz       = front_end->Si2183_FE->demod->prop->dd_mode.bw*1000000;
          status->stream             = Custom_streamCode   (front_end, front_end->Si2183_FE->demod->prop->dvbt_hierarchy.stream);
          status->fft_mode           = Custom_fftCode      (front_end, front_end->Si2183_FE->demod->rsp->dvbt_status.fft_mode);
          status->guard_interval     = Custom_giCode       (front_end, front_end->Si2183_FE->demod->rsp->dvbt_status.guard_int);
          status->constellation      = Custom_constelCode  (front_end, front_end->Si2183_FE->demod->rsp->dvbt_status.constellation);
          status->hierarchy          = Custom_hierarchyCode(front_end, front_end->Si2183_FE->demod->rsp->dvbt_status.hierarchy);
          status->code_rate_hp       = Custom_coderateCode (front_end, front_end->Si2183_FE->demod->rsp->dvbt_status.rate_hp);
          status->code_rate_lp       = Custom_coderateCode (front_end, front_end->Si2183_FE->demod->rsp->dvbt_status.rate_lp);
          status->code_rate          = status->code_rate_hp;
          if ( (status->hierarchy != SILABS_HIERARCHY_NONE) && (status->stream == SILABS_LP) ) { status->code_rate = status->code_rate_lp; }
          status->symbol_rate        = 0;
          status->cell_id            = front_end->Si2183_FE->demod->rsp->dvbt_tps_extra.cell_id;
      #ifndef   NO_FLOATS_ALLOWED
          status->c_n                = front_end->Si2183_FE->demod->rsp->dvbt_status.cnr/4.0;
          status->c_n                = DVBT_c_n_correction(status->constellation, status->guard_interval, status->code_rate, status->c_n);
      #endif /* NO_FLOATS_ALLOWED */
          status->c_n_100            = front_end->Si2183_FE->demod->rsp->dvbt_status.cnr*25;
          status->c_n_100            = DVBT_c_n_100_corrected(status->constellation, status->guard_interval, status->code_rate, status->c_n_100);
          break;
        }
  #endif /* DEMOD_DVB_T */
  #ifdef    DEMOD_ISDB_T
        case SILABS_ISDB_T : {
          if (Si2183_L1_ISDBT_STATUS   (front_end->Si2183_FE->demod, Si2183_ISDBT_STATUS_CMD_INTACK_OK)  != NO_Si2183_ERROR) return 0;
          status->demod_lock         = front_end->Si2183_FE->demod->rsp->isdbt_status.pcl;
          status->fec_lock           = front_end->Si2183_FE->demod->rsp->isdbt_status.dl;
          status->spectral_inversion = front_end->Si2183_FE->demod->rsp->isdbt_status.sp_inv;
          status->freq_offset        = front_end->Si2183_FE->demod->rsp->isdbt_status.afc_freq;
          status->timing_offset      = front_end->Si2183_FE->demod->rsp->isdbt_status.timing_offset;
          status->bandwidth_Hz       = front_end->Si2183_FE->demod->prop->dd_mode.bw*1000000;
          status->fft_mode           = Custom_fftCode      (front_end, front_end->Si2183_FE->demod->rsp->isdbt_status.fft_mode);
          status->guard_interval     = Custom_giCode       (front_end, front_end->Si2183_FE->demod->rsp->isdbt_status.guard_int);
          status->symbol_rate        = 0;
          status->isdbt_system_id    = front_end->Si2183_FE->demod->rsp->isdbt_status.syst_id;
          status->nb_seg_a           = front_end->Si2183_FE->demod->rsp->isdbt_status.nb_seg_a;
          status->nb_seg_b           = front_end->Si2183_FE->demod->rsp->isdbt_status.nb_seg_b;
          status->nb_seg_c           = front_end->Si2183_FE->demod->rsp->isdbt_status.nb_seg_c;
          status->fec_lock_a         = front_end->Si2183_FE->demod->rsp->isdbt_status.dl_a;
          status->fec_lock_b         = front_end->Si2183_FE->demod->rsp->isdbt_status.dl_b;
          status->fec_lock_c         = front_end->Si2183_FE->demod->rsp->isdbt_status.dl_c;
          status->partial_flag       = front_end->Si2183_FE->demod->rsp->isdbt_status.partial_flag;
          status->emergency_flag     = front_end->Si2183_FE->demod->rsp->isdbt_status.emergency_flag;
          /* Match status constellation and current layer constellation */
          switch (front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon) {
            default                                      :
            case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_A: { Si2183_L1_ISDBT_LAYER_INFO(front_end->Si2183_FE->demod, Si2183_ISDBT_LAYER_INFO_CMD_LAYER_INDEX_A); break; }
            case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_B: { Si2183_L1_ISDBT_LAYER_INFO(front_end->Si2183_FE->demod, Si2183_ISDBT_LAYER_INFO_CMD_LAYER_INDEX_B); break; }
            case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_C: { Si2183_L1_ISDBT_LAYER_INFO(front_end->Si2183_FE->demod, Si2183_ISDBT_LAYER_INFO_CMD_LAYER_INDEX_C); break; }
          }
          status->constellation = Custom_constelCode  (front_end, front_end->Si2183_FE->demod->rsp->isdbt_layer_info.constellation);
          status->code_rate     = Custom_coderateCode (front_end, front_end->Si2183_FE->demod->rsp->isdbt_layer_info.code_rate);
      #ifndef   NO_FLOATS_ALLOWED
          status->c_n                = front_end->Si2183_FE->demod->rsp->isdbt_status.cnr/4.0;
          status->c_n                = ISDB_T_c_n_corrected(front_end, status->constellation, status->guard_interval, status->c_n);
      #endif /* NO_FLOATS_ALLOWED */
          status->c_n_100            = front_end->Si2183_FE->demod->rsp->isdbt_status.cnr*25;
          status->c_n_100            = ISDB_T_c_n_100_corrected(front_end, status->constellation, status->guard_interval, status->c_n_100);
          /* Save ISDB-T infos per layer */
          switch (front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon) {
            default                                      : { break; }
            case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_A: {  status->uncorrs_a       = status->uncorrs;
                                                              status->constellation_a = status->constellation;
                                                              status->code_rate_a     = status->code_rate;
                                                              break; }
            case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_B: {  status->uncorrs_b       = status->uncorrs;
                                                              status->constellation_b = status->constellation;
                                                              status->code_rate_b     = status->code_rate;
                                                              break; }
            case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_C: {  status->uncorrs_c       = status->uncorrs;
                                                              status->constellation_c = status->constellation;
                                                              status->code_rate_c     = status->code_rate;
                                                              break; }
          }
          /* ISDB-T BER management */
          if (status_selection & FE_RATES     ) {
            switch (front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon) { /* Display BER = 1 if not locked */
              default                                      :
              case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_A: { if (status->fec_lock_a == 0 ) { status->ber_count_a = status->ber_window_a = status->ber_window; } break; }
              case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_B: { if (status->fec_lock_b == 0 ) { status->ber_count_b = status->ber_window_b = status->ber_window; } break; }
              case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_C: { if (status->fec_lock_c == 0 ) { status->ber_count_c = status->ber_window_c = status->ber_window; } break; }
            }
      #ifndef   NO_FLOATS_ALLOWED
            switch (front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon) { /* Display BER = 1 if not locked */
              default                                      :
              case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_A: { if (status->fec_lock_a == 0 ) { status->ber = 1.0; } break; }
              case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_B: { if (status->fec_lock_b == 0 ) { status->ber = 1.0; } break; }
              case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_C: { if (status->fec_lock_c == 0 ) { status->ber = 1.0; } break; }
            }
      #endif /* NO_FLOATS_ALLOWED */
            if (( status->nb_seg_a == 13) && (front_end->TER_ISDBT_Monitoring_mode == 0xABC)) { /* If only Layer A is used, force the loop mode to monitor Layer A */
              front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon = Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_A;
              Si2183_L1_SetProperty2(front_end->Si2183_FE->demod, Si2183_ISDBT_MODE_PROP_CODE);
            }
            if (front_end->Si2183_FE->demod->rsp->dd_ber.exp!=0) { /* BER is available for the current layer, store it and change the layer */
              switch (front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon) {
                default                                      :
                case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_A: { if (status->fec_lock_a == 1 ) { status->ber_count_a = status->ber_count; status->ber_window_a = status->ber_window; } break;}
                case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_B: { if (status->fec_lock_b == 1 ) { status->ber_count_b = status->ber_count; status->ber_window_b = status->ber_window; } break;}
                case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_C: { if (status->fec_lock_c == 1 ) { status->ber_count_c = status->ber_count; status->ber_window_c = status->ber_window; } break;}
              }
      #ifndef   NO_FLOATS_ALLOWED
              switch (front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon) {
                default                                      :
                case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_A: { if (status->fec_lock_a == 1 ) { status->ber_a = status->ber ; } break;}
                case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_B: { if (status->fec_lock_b == 1 ) { status->ber_b = status->ber ; } break;}
                case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_C: { if (status->fec_lock_c == 1 ) { status->ber_c = status->ber ; } break;}
              }
      #endif /* NO_FLOATS_ALLOWED */
              SiTRACE("front_end->TER_ISDBT_Monitoring_mode 0x%X, finished monitoring layer '%c'\n", front_end->TER_ISDBT_Monitoring_mode, front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon);
              if (front_end->TER_ISDBT_Monitoring_mode == 0xABC) { /* Manage ISDB-T Loop mode monitoring */
                front_end->TER_ISDBT_Monitoring_layer = front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon;
                switch (front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon) {
                  default                                      : {
                         if ( status->nb_seg_a ) { front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon = Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_A;}
                         break;
                  }
                  case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_A: {
                         if ( status->nb_seg_b ) { front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon = Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_B;}
                    else if ( status->nb_seg_c ) { front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon = Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_C;}
                    break;
                  }
                  case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_B: {
                         if ( status->nb_seg_c ) { front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon = Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_C;}
                    else if ( status->nb_seg_a ) { front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon = Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_A;}
                    break;
                  }
                  case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_C: {
                         if ( status->nb_seg_a ) { front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon = Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_A;}
                    else if ( status->nb_seg_b ) { front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon = Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_B;}
                    break;
                  }
                }
                /* Select the next layer for monitoring and check it's constellation */
                Si2183_L1_SetProperty2(front_end->Si2183_FE->demod, Si2183_ISDBT_MODE_PROP_CODE);
                /* Check the next layer's constellation to adjust the BER depth */
                switch (front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon) {
                  default                                      :
                  case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_A: { Si2183_L1_ISDBT_LAYER_INFO(front_end->Si2183_FE->demod, Si2183_ISDBT_LAYER_INFO_CMD_LAYER_INDEX_A); status->il_a = front_end->Si2183_FE->demod->rsp->isdbt_layer_info.il; break; }
                  case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_B: { Si2183_L1_ISDBT_LAYER_INFO(front_end->Si2183_FE->demod, Si2183_ISDBT_LAYER_INFO_CMD_LAYER_INDEX_B); status->il_b = front_end->Si2183_FE->demod->rsp->isdbt_layer_info.il; break; }
                  case Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_C: { Si2183_L1_ISDBT_LAYER_INFO(front_end->Si2183_FE->demod, Si2183_ISDBT_LAYER_INFO_CMD_LAYER_INDEX_C); status->il_c = front_end->Si2183_FE->demod->rsp->isdbt_layer_info.il; break; }
                }
                /* Adapt the BER depth depending on the constellation */
                front_end->Si2183_FE->demod->prop->dd_ber_resol.mant =     1;
                switch (front_end->Si2183_FE->demod->rsp->isdbt_layer_info.constellation) {
                  default                                      :
                  case Si2183_ISDBT_LAYER_INFO_RESPONSE_CONSTELLATION_QPSK :
                  case Si2183_ISDBT_LAYER_INFO_RESPONSE_CONSTELLATION_DQPSK: { front_end->Si2183_FE->demod->prop->dd_ber_resol.exp  = 5; break; }
                  case Si2183_ISDBT_LAYER_INFO_RESPONSE_CONSTELLATION_QAM16: { front_end->Si2183_FE->demod->prop->dd_ber_resol.exp  = 6; break; }
                  case Si2183_ISDBT_LAYER_INFO_RESPONSE_CONSTELLATION_QAM64: { front_end->Si2183_FE->demod->prop->dd_ber_resol.exp  = 6; break; }
                }
                SiTRACE("ISDB-T Switching to Layer '%c' monitoring. BER depth 10e-%d\n", 0x40 + front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon, front_end->Si2183_FE->demod->prop->dd_ber_resol.exp);
                Si2183_L1_SetProperty2(front_end->Si2183_FE->demod, Si2183_DD_BER_RESOL_PROP);
              }
            }
          }
          break;
        }
  #endif /* DEMOD_ISDB_T */
  #ifdef    DEMOD_DVB_T2
        case SILABS_DVB_T2 : {
          if (Si2183_L1_DVBT2_STATUS   (front_end->Si2183_FE->demod, Si2183_DVBT2_STATUS_CMD_INTACK_OK)  != NO_Si2183_ERROR) return 0;
          status->demod_lock         = front_end->Si2183_FE->demod->rsp->dvbt2_status.pcl;
          status->fec_lock           = front_end->Si2183_FE->demod->rsp->dvbt2_status.dl;
          status->spectral_inversion = front_end->Si2183_FE->demod->rsp->dvbt2_status.sp_inv;
      #ifndef   NO_FLOATS_ALLOWED
          status->c_n                = front_end->Si2183_FE->demod->rsp->dvbt2_status.cnr/4.0;
      #endif /* NO_FLOATS_ALLOWED */
          status->c_n_100            = front_end->Si2183_FE->demod->rsp->dvbt2_status.cnr*25;
          status->freq_offset        = front_end->Si2183_FE->demod->rsp->dvbt2_status.afc_freq;
          status->timing_offset      = front_end->Si2183_FE->demod->rsp->dvbt2_status.timing_offset;
          status->bandwidth_Hz       = front_end->Si2183_FE->demod->prop->dd_mode.bw*1000000;
          status->stream             = Custom_streamCode      (front_end, 0);
          status->fft_mode           = Custom_fftCode         (front_end, front_end->Si2183_FE->demod->rsp->dvbt2_status.fft_mode);
          status->guard_interval     = Custom_giCode          (front_end, front_end->Si2183_FE->demod->rsp->dvbt2_status.guard_int);
          status->constellation      = Custom_constelCode     (front_end, front_end->Si2183_FE->demod->rsp->dvbt2_status.constellation);
          status->code_rate          = Custom_coderateCode    (front_end, front_end->Si2183_FE->demod->rsp->dvbt2_status.code_rate);
          status->num_plp            = front_end->Si2183_FE->demod->rsp->dvbt2_status.num_plp;
          status->rotated            = front_end->Si2183_FE->demod->rsp->dvbt2_status.rotated;
          status->pilot_pattern      = Custom_pilotPatternCode(front_end, front_end->Si2183_FE->demod->rsp->dvbt2_status.pilot_pattern);
          status->bw_ext             = front_end->Si2183_FE->demod->rsp->dvbt2_status.bw_ext;
          status->plp_id             = front_end->Si2183_FE->demod->rsp->dvbt2_status.plp_id;
          status->tx_mode            = front_end->Si2183_FE->demod->rsp->dvbt2_status.tx_mode;
          status->short_frame        = front_end->Si2183_FE->demod->rsp->dvbt2_status.short_frame;
          status->fef                = front_end->Si2183_FE->demod->rsp->dvbt2_status.fef;
          status->t2_base_lite       = front_end->Si2183_FE->demod->rsp->dvbt2_status.t2_mode;
          status->t2_version         = Custom_T2VersionCode   (front_end, front_end->Si2183_FE->demod->rsp->dvbt2_status.t2_version);
          if (Si2183_L1_DVBT2_TX_ID   (front_end->Si2183_FE->demod)                                      != NO_Si2183_ERROR) return 0;
          status->cell_id            = front_end->Si2183_FE->demod->rsp->dvbt2_tx_id.cell_id;
          status->t2_system_id       = front_end->Si2183_FE->demod->rsp->dvbt2_tx_id.t2_system_id;
          status->symbol_rate        = 0;
          break;
        }
  #endif /* DEMOD_DVB_T2 */
  #ifdef    DEMOD_DVB_C
        case SILABS_DVB_C  : {
          if (Si2183_L1_DVBC_STATUS    (front_end->Si2183_FE->demod, Si2183_DVBC_STATUS_CMD_INTACK_OK) != NO_Si2183_ERROR) return 0;
          status->demod_lock         = front_end->Si2183_FE->demod->rsp->dvbc_status.pcl;
          status->fec_lock           = front_end->Si2183_FE->demod->rsp->dvbc_status.dl;
          status->symbol_rate        = front_end->Si2183_FE->demod->prop->dvbc_symbol_rate.rate*1000;
          status->constellation      = Custom_constelCode (front_end, front_end->Si2183_FE->demod->rsp->dvbc_status.constellation);
          status->spectral_inversion = front_end->Si2183_FE->demod->rsp->dvbc_status.sp_inv;
      #ifndef   NO_FLOATS_ALLOWED
          status->c_n                = front_end->Si2183_FE->demod->rsp->dvbc_status.cnr/4.0;
      #endif /* NO_FLOATS_ALLOWED */
          status->c_n_100            = front_end->Si2183_FE->demod->rsp->dvbc_status.cnr*25;
          status->freq_offset        = front_end->Si2183_FE->demod->rsp->dvbc_status.afc_freq;
          status->timing_offset      = front_end->Si2183_FE->demod->rsp->dvbc_status.timing_offset;
          break;
        }
  #endif /* DEMOD_DVB_C */
  #ifdef    DEMOD_MCNS
        case SILABS_MCNS   : {
          if (Si2183_L1_MCNS_STATUS   (front_end->Si2183_FE->demod, Si2183_MCNS_STATUS_CMD_INTACK_OK) != NO_Si2183_ERROR) return 0;
          status->demod_lock         = front_end->Si2183_FE->demod->rsp->mcns_status.pcl;
          status->fec_lock           = front_end->Si2183_FE->demod->rsp->mcns_status.dl;
          status->symbol_rate        = front_end->Si2183_FE->demod->prop->mcns_symbol_rate.rate*1000;
          status->constellation      = Custom_constelCode (front_end, front_end->Si2183_FE->demod->rsp->mcns_status.constellation);
          status->spectral_inversion = front_end->Si2183_FE->demod->rsp->mcns_status.sp_inv;
      #ifndef   NO_FLOATS_ALLOWED
          status->c_n                = front_end->Si2183_FE->demod->rsp->mcns_status.cnr/4.0;
      #endif /* NO_FLOATS_ALLOWED */
          status->c_n_100            = front_end->Si2183_FE->demod->rsp->mcns_status.cnr*25;
          status->freq_offset        = front_end->Si2183_FE->demod->rsp->mcns_status.afc_freq;
          status->timing_offset      = front_end->Si2183_FE->demod->rsp->mcns_status.timing_offset;
          break;
        }
  #endif /* DEMOD_MCNS */
  #ifdef    DEMOD_DVB_C2
        case SILABS_DVB_C2 : {
          if (Si2183_L1_DVBC2_STATUS   (front_end->Si2183_FE->demod, Si2183_DVBC2_STATUS_CMD_INTACK_OK)                                                                       != NO_Si2183_ERROR) return 0;
          if (Si2183_L1_DVBC2_SYS_INFO (front_end->Si2183_FE->demod)                                                                                                          != NO_Si2183_ERROR) return 0;
          if (Si2183_L1_DVBC2_DS_INFO  (front_end->Si2183_FE->demod, front_end->Si2183_FE->demod->rsp->dvbc2_status.ds_id, Si2183_DVBC2_DS_INFO_CMD_DS_SELECT_INDEX_OR_ID_ID) != NO_Si2183_ERROR) return 0;
          status->demod_lock         = front_end->Si2183_FE->demod->rsp->dvbc2_status.pcl;
          status->fec_lock           = front_end->Si2183_FE->demod->rsp->dvbc2_status.dl;
          status->spectral_inversion = front_end->Si2183_FE->demod->rsp->dvbc2_status.sp_inv;
      #ifndef   NO_FLOATS_ALLOWED
          status->c_n                = front_end->Si2183_FE->demod->rsp->dvbc2_status.cnr/4.0;
      #endif /* NO_FLOATS_ALLOWED */
          status->c_n_100            = front_end->Si2183_FE->demod->rsp->dvbc2_status.cnr*25;
          status->freq_offset        = front_end->Si2183_FE->demod->rsp->dvbc2_status.afc_freq;
          status->timing_offset      = front_end->Si2183_FE->demod->rsp->dvbc2_status.timing_offset;
          status->bandwidth_Hz       = front_end->Si2183_FE->demod->prop->dd_mode.bw*1000000;
          status->guard_interval     = Custom_giCode          (front_end, front_end->Si2183_FE->demod->rsp->dvbc2_status.guard_int);
          status->constellation      = Custom_constelCode     (front_end, front_end->Si2183_FE->demod->rsp->dvbc2_status.constellation);
          status->code_rate          = Custom_coderateCode    (front_end, front_end->Si2183_FE->demod->rsp->dvbc2_status.code_rate);
          status->c2_system_id       = front_end->Si2183_FE->demod->rsp->dvbc2_sys_info.c2_system_id;
          status->c2_start_freq_hz   = front_end->Si2183_FE->demod->rsp->dvbc2_sys_info.start_frequency_hz;
          status->c2_system_bw_hz    = front_end->Si2183_FE->demod->rsp->dvbc2_sys_info.c2_bandwidth_hz;
          status->num_data_slice     = front_end->Si2183_FE->demod->rsp->dvbc2_sys_info.num_dslice;
          status->num_plp            = front_end->Si2183_FE->demod->rsp->dvbc2_ds_info.dslice_num_plp;
          status->plp_id             = front_end->Si2183_FE->demod->rsp->dvbc2_status.plp_id;
          status->ds_id              = front_end->Si2183_FE->demod->rsp->dvbc2_status.ds_id;
          status->symbol_rate        = 0;
          break;
        }
  #endif /* DEMOD_DVB_C2 */
  #ifdef    DEMOD_DVB_S_S2_DSS
        case SILABS_DVB_S2 : {
          if (Si2183_L1_DVBS2_STATUS    (front_end->Si2183_FE->demod, Si2183_DVBS2_STATUS_CMD_INTACK_OK) != NO_Si2183_ERROR) return 0;
          status->demod_lock         = front_end->Si2183_FE->demod->rsp->dvbs2_status.pcl;
          status->fec_lock           = front_end->Si2183_FE->demod->rsp->dvbs2_status.dl;
          status->symbol_rate        = front_end->Si2183_FE->demod->prop->dvbs2_symbol_rate.rate*1000;
          status->constellation      = Custom_constelCode  (front_end, front_end->Si2183_FE->demod->rsp->dvbs2_status.constellation);
          status->spectral_inversion = front_end->Si2183_FE->demod->rsp->dvbs2_status.sp_inv;
      #ifndef   NO_FLOATS_ALLOWED
          status->c_n                = front_end->Si2183_FE->demod->rsp->dvbs2_status.cnr/4.0;
      #endif /* NO_FLOATS_ALLOWED */
          status->c_n_100            = front_end->Si2183_FE->demod->rsp->dvbs2_status.cnr*25;
          status->freq_offset        = front_end->Si2183_FE->demod->rsp->dvbs2_status.afc_freq;
          status->timing_offset      = front_end->Si2183_FE->demod->rsp->dvbs2_status.timing_offset;
          status->code_rate          = Custom_coderateCode (front_end, front_end->Si2183_FE->demod->rsp->dvbs2_status.code_rate);
          status->pilots             = front_end->Si2183_FE->demod->rsp->dvbs2_status.pilots;
          status->ccm_vcm            = front_end->Si2183_FE->demod->rsp->dvbs2_status.ccm_vcm;
          status->sis_mis            = front_end->Si2183_FE->demod->rsp->dvbs2_status.sis_mis;
          status->num_is             = front_end->Si2183_FE->demod->rsp->dvbs2_status.num_is;
          status->isi_id             = front_end->Si2183_FE->demod->rsp->dvbs2_status.isi_id;
          status->roll_off           = front_end->Si2183_FE->demod->rsp->dvbs2_status.roll_off;
          if (Si2183_L1_DD_FER          (front_end->Si2183_FE->demod, Si2183_DD_FER_CMD_RST_RUN)         != NO_Si2183_ERROR) return 0;
      #ifndef   NO_FLOATS_ALLOWED
          /* CHECK the exponent value to know if the FER is available or not */
          if(front_end->Si2183_FE->demod->rsp->dd_fer.exp!=0) {
            status->fer                = (front_end->Si2183_FE->demod->rsp->dd_fer.mant/10.0) / power_of_n(10, front_end->Si2183_FE->demod->rsp->dd_fer.exp);
          }
      #endif /* NO_FLOATS_ALLOWED */
          status->fer_mant         = (front_end->Si2183_FE->demod->rsp->dd_fer.mant);
          status->fer_exp          = (front_end->Si2183_FE->demod->rsp->dd_fer.exp+1);
          break;
        }
        case SILABS_DVB_S  :
        case SILABS_DSS    : {
          if (Si2183_L1_DVBS_STATUS     (front_end->Si2183_FE->demod, Si2183_DVBS_STATUS_CMD_INTACK_OK) != NO_Si2183_ERROR) return 0;
          /* Settings for SAT AGC. These settings need to match the HW design for SAT AGCs */
          status->demod_lock         = front_end->Si2183_FE->demod->rsp->dvbs_status.pcl;
          status->fec_lock           = front_end->Si2183_FE->demod->rsp->dvbs_status.dl;
          status->symbol_rate        = front_end->Si2183_FE->demod->prop->dvbs_symbol_rate.rate*1000;
          status->constellation      = Custom_constelCode  (front_end, front_end->Si2183_FE->demod->rsp->dvbs_status.constellation);
          status->spectral_inversion = front_end->Si2183_FE->demod->rsp->dvbs_status.sp_inv;
      #ifndef   NO_FLOATS_ALLOWED
          status->c_n                = front_end->Si2183_FE->demod->rsp->dvbs_status.cnr/4.0;
      #endif /* NO_FLOATS_ALLOWED */
          status->c_n_100            = front_end->Si2183_FE->demod->rsp->dvbs_status.cnr*25;
          status->freq_offset        = front_end->Si2183_FE->demod->rsp->dvbs_status.afc_freq;
          status->timing_offset      = front_end->Si2183_FE->demod->rsp->dvbs_status.timing_offset;
          status->code_rate          = Custom_coderateCode (front_end, front_end->Si2183_FE->demod->rsp->dvbs_status.code_rate);
          break;
        }
  #endif /* DEMOD_DVB_S_S2_DSS */
        default            : {
          return 0;
          break;
        }
      }
    }
    /* Retrieving quality indicators */
    if (status_selection & FE_QUALITY   ) { SiTRACE("Checking FE_QUALITY\n"   );
      if (Si2183_L1_DD_SSI_SQI     (front_end->Si2183_FE->demod, status->RSSI) == NO_Si2183_ERROR) {
        status->SSI                = front_end->Si2183_FE->demod->rsp->dd_ssi_sqi.ssi;
        status->SQI                = front_end->Si2183_FE->demod->rsp->dd_ssi_sqi.sqi;
      }
    }
  }
#endif /* Si2183_COMPATIBLE */
    /* Retrieving SSI and SQI values for DVB-C & SAT, if not previously set */
  #ifndef   NO_FLOATS_ALLOWED
    switch (status->standard) {
#ifdef    DEMOD_MCNS
      case SILABS_MCNS :
#endif /* DEMOD_MCNS */
#ifdef    DEMOD_DVB_C
      case SILABS_DVB_C : {
        if (status->SSI == -1) { /* Some demodulators will have the SSI/SQI feature in FW. Only call SiLabs_API_SSI_SQI if not already set */
          SiLabs_API_SSI_SQI (status->standard, status->fec_lock, status->RSSI, status->constellation, 0, status->c_n, status->ber, &(status->SSI), &(status->SQI));
        }
        break;
      }
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_S_S2_DSS
      case SILABS_DVB_S :
      case SILABS_DVB_S2:
      case SILABS_DSS   : {
        if (status->SSI <= 0) { /* Some demodulators will have the SSI/SQI feature in FW. Only call SiLabs_API_SSI_SQI if not already set */
          SiLabs_API_SSI_SQI (status->standard, status->fec_lock, status->RSSI, status->constellation, status->code_rate, status->c_n, status->ber, &(status->SSI), &(status->SQI));
        }
        break;
      }
#endif /* DEMOD_DVB_S_S2_DSS */
#ifdef    DEMOD_DVB_C2
      case SILABS_DVB_C2: {
        if (status->SSI == -1) { /* Some demodulators will have the SSI/SQI feature in FW. Only call SiLabs_API_SSI_SQI if not already set */
          SiLabs_API_SSI_SQI (status->standard, status->fec_lock, status->RSSI, status->constellation, status->code_rate, status->c_n, status->ber, &(status->SSI), &(status->SQI));
        }
        break;
      }
#endif /* DEMOD_DVB_C2 */
      default           : {
        break;
      }
    }
  #endif /* NO_FLOATS_ALLOWED */

#ifdef   DEMOD_DVB_S2X
  if (status->standard == SILABS_DVB_S2) {
    switch (status->constellation) {
      case SILABS_QPSK:     {
        switch (status->code_rate) {
          case SILABS_CODERATE_1_4:
          case SILABS_CODERATE_1_3:
          case SILABS_CODERATE_2_5:
          case SILABS_CODERATE_1_2:
          case SILABS_CODERATE_3_5:
          case SILABS_CODERATE_2_3:
          case SILABS_CODERATE_3_4:
          case SILABS_CODERATE_4_5:
          case SILABS_CODERATE_5_6:
          case SILABS_CODERATE_8_9:
          case SILABS_CODERATE_9_10: {
            status->s2x = 0;
            break;
          }
          default: {
            status->s2x = 1;
            break;
          }
        }
        break;
      }
      case SILABS_8PSK:     {
        switch (status->code_rate) {
          case SILABS_CODERATE_3_5:
          case SILABS_CODERATE_2_3:
          case SILABS_CODERATE_3_4:
          case SILABS_CODERATE_5_6:
          case SILABS_CODERATE_8_9:
          case SILABS_CODERATE_9_10: {
            status->s2x = 0;
            break;
          }
          default: {
            status->s2x = 1;
            break;
          }
        }
        break;
      }
      case SILABS_8APSK_L:  {
        status->s2x = 1;
        break;
      }
      case SILABS_16APSK:   {
        switch (status->code_rate) {
          case SILABS_CODERATE_2_3:
          case SILABS_CODERATE_3_4:
          case SILABS_CODERATE_4_5:
          case SILABS_CODERATE_5_6:
          case SILABS_CODERATE_8_9:
          case SILABS_CODERATE_9_10: {
            status->s2x = 0;
            break;
          }
          default: {
            status->s2x = 1;
            break;
          }
        }
        break;
      }
      case SILABS_16APSK_L: {
        status->s2x = 1;
        break;
      }
      case SILABS_32APSK_1: {
        switch (status->code_rate) {
          case SILABS_CODERATE_3_4:
          case SILABS_CODERATE_4_5:
          case SILABS_CODERATE_5_6:
          case SILABS_CODERATE_8_9:
          case SILABS_CODERATE_9_10: {
            status->s2x = 0;
            break;
          }
          default: {
            status->s2x = 1;
            break;
          }
        }
        break;
      }
      case SILABS_32APSK_2: {
        status->s2x = 1;
        break;
      }
      case SILABS_32APSK_L: {
        status->s2x = 1;
        break;
      }
      default: {
        status->s2x = 0;
        break;
      }
    }
  }
#endif /* DEMOD_DVB_S2X */

  if (status->SSI == -1) {status->SSI = 0;}
  if (status->SQI == -1) {status->SQI = 0;}

  if (status->fec_lock == 1) { front_end->standard = status->standard; }

  return 1;
}
/************************************************************************************************************************
  SiLabs_API_TER_Tuner_status function
  Use:        Terrestrial tuner status function
              Used to retrieve the status of the TER tuner in a structure
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  status, a pointer to the status structure (configurable in CUSTOM_Status_Struct)
  Return:     1 if successful, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_TER_Tuner_status           (SILABS_FE_Context* front_end,    CUSTOM_Status_Struct *status)
{
#ifdef    TERRESTRIAL_FRONT_END
#ifdef    TER_TUNER_DTT759x
  DTT759x_Context *tuner_ter;
#endif /* TER_TUNER_DTT759x */
#ifdef    TER_TUNER_Si2185
  L1_Si2185_Context *tuner_ter;
#endif /* TER_TUNER_Si2185 */
#ifndef   TER_TUNER_SILABS
  #ifdef    TER_TUNER_CUSTOMTER
    CUSTOMTER_Context *tuner_ter;
  #endif /* TER_TUNER_CUSTOMTER */
  #ifdef    TER_TUNER_Si2146
    L1_Si2146_Context *tuner_ter;
  #endif /* TER_TUNER_Si2146 */
  #ifdef    TER_TUNER_Si2148
    L1_Si2148_Context *tuner_ter;
  #endif /* TER_TUNER_Si2148 */
  #ifdef    TER_TUNER_Si2156
    L1_Si2156_Context *tuner_ter;
  #endif /* TER_TUNER_Si2156 */
  #ifdef    TER_TUNER_Si2158
    L1_Si2158_Context *tuner_ter;
  #endif /* TER_TUNER_Si2158 */
  #ifdef    TER_TUNER_Si2173
    L1_Si2173_Context *tuner_ter;
  #endif /* TER_TUNER_Si2173 */
  #ifdef    TER_TUNER_Si2176
   L1_Si2176_Context *tuner_ter;
  #endif /* TER_TUNER_Si2176 */
  #ifdef    TER_TUNER_Si2178
   L1_Si2178_Context *tuner_ter;
  #endif /* TER_TUNER_Si2178 */
  #ifdef    TER_TUNER_Si2191
    L1_Si2191_Context *tuner_ter;
  #endif /* TER_TUNER_Si2191 */
  #ifdef    TER_TUNER_Si2190
    L1_Si2190_Context *tuner_ter;
  #endif /* TER_TUNER_Si2190 */
  #ifdef    TER_TUNER_Si2196
    L1_Si2196_Context *tuner_ter;
  #endif /* TER_TUNER_Si2196 */
#else  /* TER_TUNER_SILABS */
  SILABS_TER_TUNER_Context *tuner_ter;
#endif /* TER_TUNER_SILABS */
  tuner_ter = NULL;
  SiTRACE("API CALL STATUS: SiLabs_API_TER_Tuner_status (front_end, &status);\n");
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip == 0x2183   ) { tuner_ter = front_end->Si2183_FE->tuner_ter; }
#endif /* Si2183_COMPATIBLE */
  if (tuner_ter == NULL) {
      SiTRACE("No tuner_ter defined, SiLabs_API_TER_Tuner_status can't be executed!\n");
    return 0;
  }
  SiLabs_API_TER_Tuner_I2C_Enable  (front_end);
#ifdef    TER_TUNER_DTT759x
  status->freq     =  tuner_ter->RF;
#endif /* TER_TUNER_DTT759x */
#ifdef    TER_TUNER_SILABS
  SiLabs_TER_Tuner_Status (tuner_ter);
  status->vco_code =  tuner_ter->vco_code;
  status->tc       =  tuner_ter->tc;
  status->rssi     =  tuner_ter->rssi;
  status->freq     =  tuner_ter->freq;
  status->mode     =  tuner_ter->mode;
  status->RSSI     =  status->rssi;
  SiTRACE("SiLabs_API_TER_Tuner_status status->vco_code %5d\n", status->vco_code);
#endif /* TER_TUNER_SILABS */
  SiLabs_API_TER_Tuner_I2C_Disable (front_end);
#endif /* TERRESTRIAL_FRONT_END */
  front_end = front_end; /* To avoid compiler warning */
  status    = status;    /* To avoid compiler warning */
  return 1;
}
/************************************************************************************************************************
  SiLabs_API_TER_Tuner_Loop_Through function
  Use:        Terrestrial tuner active loop through control function
              Used to enable/disable the active loop through
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  enable, a flag used to enable/disable (1/0) the active loop thruogh state for tuners supporting this feature
  Return:     0 if successful, and error code otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_TER_Tuner_Loop_Through     (SILABS_FE_Context* front_end,    signed   int enable)
{
  int return_value;
#ifdef    TERRESTRIAL_FRONT_END
  SILABS_TER_TUNER_Context *tuner_ter;
  tuner_ter = NULL;
  SiTRACE("API CALL STATUS: SiLabs_API_TER_Tuner_Loop_Through (front_end, &status);\n");
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip == 0x2183   ) { tuner_ter = front_end->Si2183_FE->tuner_ter; }
#endif /* Si2183_COMPATIBLE */
  if (tuner_ter == NULL) {
    SiTRACE("No tuner_ter defined, SiLabs_API_TER_Tuner_Loop_Through can't be executed!\n");
    return 0;
  }
  SiLabs_API_TER_Tuner_I2C_Enable  (front_end);
  return_value = SiLabs_TER_Tuner_ACTIVE_LOOP_THROUGH (tuner_ter, enable);
  SiLabs_API_TER_Tuner_I2C_Disable (front_end);
#endif /* TERRESTRIAL_FRONT_END */
  front_end = front_end; /* To avoid compiler warning */
  enable    = enable;    /* To avoid compiler warning */
  return return_value;
}
/************************************************************************************************************************
  SiLabs_API_SAT_Tuner_status function
  Use:        Satellite tuner status function
              Used to retrieve the status of the SAT tuner in a structure
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  status, a pointer to the status structure (configurable in CUSTOM_Status_Struct)
  Return:     1 if successful, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_Tuner_status           (SILABS_FE_Context* front_end,    CUSTOM_Status_Struct *status)
{
#ifdef    SATELLITE_FRONT_END
#ifndef   SAT_TUNER_SILABS
  signed   int ref_level;
#ifndef   NO_SAT
#ifdef    SAT_TUNER_CUSTOMSAT
  SAT_TUNER_CONTEXT *sat_tuner;
#endif /* SAT_TUNER_CUSTOMSAT */
#ifdef    SAT_TUNER_MAX2112
  MAX2112_Context *sat_tuner;
#endif /* SAT_TUNER_MAX2112 */
#ifdef    SAT_TUNER_RDA5812
  RDA5812_Context *sat_tuner;
#endif /* SAT_TUNER_RDA5812 */
#ifdef    SAT_TUNER_RDA5815
  RDA5815_Context *sat_tuner;
#endif /* SAT_TUNER_RDA5815 */
#ifdef    SAT_TUNER_RDA5815M
  RDA5815M_Context *sat_tuner;
#endif /* SAT_TUNER_RDA5815M */
#ifdef    SAT_TUNER_RDA5816S
  RDA5816S_Context *sat_tuner;
#endif /* SAT_TUNER_RDA5816S */
#ifdef    SAT_TUNER_NXP20142
  NXP20142_Context *sat_tuner;
#endif /* SAT_TUNER_NXP20142 */
#endif /* NO_SAT */
#endif /* SAT_TUNER_SILABS */
#ifdef    SAT_TUNER_SILABS
  SILABS_SAT_TUNER_Context *sat_tuner;
  sat_tuner = NULL;
  SiTRACE("API CALL STATUS: SiLabs_API_SAT_Tuner_status (front_end, &status);\n");
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { sat_tuner = front_end->Si2183_FE->tuner_sat; }
#endif /* Si2183_COMPATIBLE */
#endif /* SAT_TUNER_SILABS */
  front_end = front_end; /* To avoid compiler warning */
  status    = status;    /* To avoid compiler warning */
  SiLabs_API_SAT_Tuner_I2C_Enable  (front_end);
  SiTRACE("API CALL STATUS: SiLabs_API_SAT_Tuner_status (front_end, &status)\n");
#ifndef   SAT_TUNER_SILABS
  ref_level = 0;
  status->freq = sat_tuner->RF;
  status->rssi = 0;
  #ifdef    SAT_TUNER_RSSI
  status->rssi = SAT_TUNER_RSSI(sat_tuner, ref_level);
  #endif /* SAT_TUNER_RSSI */
#endif /* SAT_TUNER_SILABS */
#ifdef    SAT_TUNER_SILABS
  SiLabs_SAT_Tuner_Status(sat_tuner);
  status->freq = sat_tuner->RF;
  status->rssi = sat_tuner->rssi;
#ifdef   UNICABLE_COMPATIBLE
  if (front_end->unicable->installed) { status->freq = front_end->unicable->sat_tuner_freq; } /* to have proper RF statusing in Unicable */
#endif /* UNICABLE_COMPATIBLE */
#endif /* SAT_TUNER_SILABS */
  SiLabs_API_SAT_Tuner_I2C_Disable (front_end);
#endif /* SATELLITE_FRONT_END */
  return 1;
}
/************************************************************************************************************************
  SiLabs_API_FE_status function
  Use:        Front-End status function
              Used to retrieve the complete status of the front-end in a structure
  Behavior:   It will call SiLabs_API_FE_status_selection with the status_selection flag corresponding to 'all'
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  status, a pointer to the status structure (configurable in CUSTOM_Status_Struct)
  Return:     1 if successful, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_FE_status                  (SILABS_FE_Context* front_end,    CUSTOM_Status_Struct *status)
{
  SiTRACE("API CALL STATUS: SiLabs_API_FE_status (front_end, &status);\n");
  return SiLabs_API_FE_status_selection (front_end, status, 0x00);
}
/************************************************************************************************************************
  SiLabs_API_FE_status_selection function
  Use:        Front-End status function, with selection of 'all' or partial statuses
              Used to retrieve the status of the front-end in a structure
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  status, a pointer to the status structure (configurable in CUSTOM_Status_Struct)
  Parameter:  status_selection, an 8 bit field used to control which items to refresh. Use 0x00 for 'all'.
  Return:     1 if successful, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_FE_status_selection        (SILABS_FE_Context* front_end,    CUSTOM_Status_Struct *status, unsigned char status_selection)
{
  signed   int tuner_statused;
  signed   int   res;
  #ifdef    SiTRACES
  char  messageBuffer[1000];
  #endif /* SiTRACES */

  SiTRACE("API CALL STATUS: SiLabs_API_FE_status_selection (front_end, &status, status_selection 0x%02x);\n", status_selection);
  SiTRACE("SiLabs_API_FE_status in %s\n", Silabs_Standard_Text(front_end->standard));
  SiTRACE("SiLabs_API_FE_status config_code 0x%06x\n", front_end->config_code);
  tuner_statused = 0;
  if (status_selection == 0x00  )    { status_selection = FE_LOCK_STATE + FE_LEVELS + FE_RATES + FE_SPECIFIC + FE_QUALITY + FE_FREQ ;}

  if (status_selection & FE_LOCK_STATE) { SiTRACE("FE_LOCK_STATE\n"); }
  if (status_selection & FE_LEVELS    ) { SiTRACE("FE_LEVELS\n"    ); }
  if (status_selection & FE_RATES     ) { SiTRACE("FE_RATES\n"     ); }
  if (status_selection & FE_SPECIFIC  ) { SiTRACE("FE_SPECIFIC\n"  ); }
  if (status_selection & FE_QUALITY   ) { SiTRACE("FE_QUALITY\n"   ); }
  if (status_selection & FE_FREQ      ) { SiTRACE("FE_FREQ\n"      ); }

  /* For FE_QUALITY monitoring (SSI), retrieving the rssi from the tuner is required, so we add FE_LEVELS if it's not on */
  if ( (status_selection & FE_QUALITY) && ((status_selection & FE_LEVELS    ) == 0) ) { status_selection = status_selection + FE_LEVELS;     }
  /* For FE_RATES   monitoring (ber/fer/per), the demodulator needs to be locked, so we add FE_LOCK_STATE if it's not on */
  if ( (status_selection & FE_RATES  ) && ((status_selection & FE_LOCK_STATE) == 0) ) { status_selection = status_selection + FE_LOCK_STATE; }
  SiTRACE("SiLabs_API_FE_status status_selection 0x%02x\n", status_selection);

  /* Call SiLabs_API_TER_Tuner_status only if FE_FREQ or FE_LEVELS monitoring */
  if ((status_selection & FE_LEVELS) || (status_selection & FE_FREQ) ) {
    switch (front_end->standard) {
      case SILABS_ANALOG: {
        SiLabs_API_TER_Tuner_status   (front_end, status);
        status->standard = SILABS_ANALOG;
        tuner_statused++;
        break;
      }
      case SILABS_DVB_T :
      case SILABS_ISDB_T:
      case SILABS_DVB_T2:
      case SILABS_DVB_C :
      case SILABS_DVB_C2:
      case SILABS_MCNS  : {
        SiLabs_API_TER_Tuner_status   (front_end, status);
        tuner_statused++;
        break;
      }
      case SILABS_DVB_S :
      case SILABS_DVB_S2:
      case SILABS_DSS   : {
        SiLabs_API_SAT_Tuner_status   (front_end, status);
        tuner_statused++;
        break;
      }
      case SILABS_SLEEP : {
        status->standard = SILABS_SLEEP;
        break;
      }
      default           : { break; }
    }
    if (tuner_statused) { SiTRACE("Tuner freq %ld, tuner rssi %d\n", status->freq, status->rssi); }
  }

  if (front_end->standard == SILABS_ANALOG) {return 1;}

  res = SiLabs_API_Demod_status_selection  (front_end, status, status_selection);

  #ifdef    SiTRACES
    SiLabs_API_Text_status_selection (front_end, status, messageBuffer, status_selection);
    SiTRACE ("\n-----------------------------------------------------------------\n");
    SiTRACE ("%s", messageBuffer);
    SiTRACE ("\n-----------------------------------------------------------------\n");
  #endif /* SiTRACES */
  return res;
}
/************************************************************************************************************************
  SiLabs_API_Text_status function
  Use:        Front-End status function
              Used to retrieve the status of the front-end in a text
  Behavior:   It will call SiLabs_API_Text_status_selection with the status_selection flag corresponding to 'all'
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  status, a pointer to the status structure (configurable in CUSTOM_Status_Struct)
  Parameter:  formatted_string, a text buffer to store the result
  Return:     1 if successful, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_Text_status                (SILABS_FE_Context* front_end,    CUSTOM_Status_Struct *status, char *formatted_status)
{
  SiTRACE("API CALL STATUS: SiLabs_API_Text_status (front_end, &status, &formatted_status);\n");
  return SiLabs_API_Text_status_selection (front_end, status, formatted_status, 0x00);
}
/************************************************************************************************************************
  SiLabs_API_Text_status_selection function
  Use:        Front-End status function, with selection of 'all' or partial statuses
              Used to retrieve the status of the front-end in a text
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  status, a pointer to the status structure (configurable in CUSTOM_Status_Struct)
  Parameter:  formatted_status, a text buffer to store the result
  Parameter:  status_selection, an 8 bit field used to control which items to refresh. Use 0x00 for 'all'.
  Return:     1 if successful, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_Text_status_selection      (SILABS_FE_Context* front_end,    CUSTOM_Status_Struct *status, char *formatted_status, unsigned char status_selection)
{
  char rate_i, rate_d, rate_e;
  SiTRACE("API CALL STATUS: SiLabs_API_Text_status_selection (front_end, &status, &formatted_status, status_selection 0x%02x);\n", status_selection);
  if (status_selection == 0x00  )    { status_selection = FE_LOCK_STATE + FE_LEVELS + FE_RATES + FE_SPECIFIC + FE_QUALITY + FE_FREQ ;}

  rate_i = rate_d = rate_e = 0;
  sprintf(formatted_status, "\nFront_end status:");
  if (status->demod_die == 0) { STRING_APPEND_SAFE(formatted_status,1000, " SINGLE  "); }
  if (status->demod_die == 1) { STRING_APPEND_SAFE(formatted_status,1000, " DEMOD A "); }
  if (status->demod_die == 2) { STRING_APPEND_SAFE(formatted_status,1000, " DEMOD B "); }
  STRING_APPEND_SAFE(formatted_status,1000, " (0x%06x)\n\n", front_end->config_code );
  switch (status->standard)
  {
    case SILABS_ANALOG: { STRING_APPEND_SAFE(formatted_status,1000, " ANALOG MODE\n"          ); return 0 ; break; }
    case SILABS_DVB_T : { STRING_APPEND_SAFE(formatted_status,1000, " standard       DVB-T\n" ); break; }
    case SILABS_DVB_T2: { STRING_APPEND_SAFE(formatted_status,1000, " standard       DVB-T2\n"); break; }
    case SILABS_ISDB_T: { STRING_APPEND_SAFE(formatted_status,1000, " standard       ISDB-T\n"); break; }
    case SILABS_DVB_C : { STRING_APPEND_SAFE(formatted_status,1000, " standard       DVB-C\n" ); break; }
    case SILABS_DVB_C2: { STRING_APPEND_SAFE(formatted_status,1000, " standard       DVB-C2\n"); break; }
    case SILABS_MCNS  : { STRING_APPEND_SAFE(formatted_status,1000, " standard       MCNS\n"  ); break; }
    case SILABS_DVB_S : { STRING_APPEND_SAFE(formatted_status,1000, " standard       DVB-S\n" ); break; }
    case SILABS_DVB_S2: { STRING_APPEND_SAFE(formatted_status,1000, " standard       DVB-S2");
      if (status->s2x)  { STRING_APPEND_SAFE(formatted_status,1000, "X"); }
                          STRING_APPEND_SAFE(formatted_status,1000, "\n");                       break; }
    case SILABS_DSS   : { STRING_APPEND_SAFE(formatted_status,1000, " standard       DSS\n"   ); break; }
    case SILABS_SLEEP : { STRING_APPEND_SAFE(formatted_status,1000, " SLEEP MODE\n"           ); return 0 ; break; }
    default           : { STRING_APPEND_SAFE(formatted_status,1000, " INVALID standard (%d)!\n", status->standard); return 0; break; }
  }
  if (status_selection & FE_FREQ      ) { /* freq vco_code               */
    switch (status->standard)
    {
      case SILABS_ANALOG:
      case SILABS_DVB_T :
      case SILABS_DVB_T2:
      case SILABS_ISDB_T:
      case SILABS_DVB_C :
      case SILABS_DVB_C2:
      case SILABS_MCNS  : {
                            STRING_APPEND_SAFE(formatted_status,1000, " frequency         %ld  Hz  ", status->freq);
                            STRING_APPEND_SAFE(formatted_status,1000, " VCO_CODE %4d\n", status->vco_code);
                            break;
                          }
      case SILABS_DVB_S :
      case SILABS_DVB_S2:
      case SILABS_DSS   : { STRING_APPEND_SAFE(formatted_status,1000, " frequency         %ld kHz\n", status->freq); break; }
      default           : { STRING_APPEND_SAFE(formatted_status,1000, " INVALID standard (%d)!\n", front_end->standard); return 0; break; }
    }
  }
  if (status_selection & FE_LOCK_STATE) { /* demod_lock fec_lock         */
    STRING_APPEND_SAFE(formatted_status,1000, " demod_lock        %d", status->demod_lock);
    if (status->demod_lock) { STRING_APPEND_SAFE(formatted_status,1000, " : locked\n"  );
    } else                  { STRING_APPEND_SAFE(formatted_status,1000, " : unlocked\n");
    }
    STRING_APPEND_SAFE(formatted_status,1000, " fec_lock          %d", status->fec_lock);
    if (status->fec_lock)   { STRING_APPEND_SAFE(formatted_status,1000, " : locked\n"  );
    } else {                  STRING_APPEND_SAFE(formatted_status,1000, " : unlocked\n");
    }
  }
  if (status_selection & FE_SPECIFIC  ) { /* ...                         */
    switch (status->standard)
    {
      case SILABS_ANALOG: {
        STRING_APPEND_SAFE(formatted_status,1000, " standard       ANALOG\n");
        break;
      }
      case SILABS_DVB_T : {
        STRING_APPEND_SAFE(formatted_status,1000, " characteristics     %s ", Silabs_FFT_Text(status->fft_mode));
        STRING_APPEND_SAFE(formatted_status,1000, " %s "                , Silabs_Constel_Text(status->constellation));
        STRING_APPEND_SAFE(formatted_status,1000, " %s "                , Silabs_Coderate_Text(status->code_rate));
        STRING_APPEND_SAFE(formatted_status,1000, " %s "                , Silabs_GI_Text(status->guard_interval));
        STRING_APPEND_SAFE(formatted_status,1000, " %9d Hz\n"           , status->bandwidth_Hz);
        break;
      }
      case SILABS_ISDB_T: {
        if (status->nb_seg_a) {
          STRING_APPEND_SAFE(formatted_status,1000, " Layer A      %-6s "     , Silabs_Constel_Text(status->constellation_a));
          STRING_APPEND_SAFE(formatted_status,1000, " %-6s "                  , Silabs_Coderate_Text(status->code_rate_a));
          STRING_APPEND_SAFE(formatted_status,1000, " il %d "                 , status->il_a );
          STRING_APPEND_SAFE(formatted_status,1000, " nb_segments %d "        , status->nb_seg_a );
          STRING_APPEND_SAFE(formatted_status,1000, " locked %d "             , status->fec_lock_a );
          STRING_APPEND_SAFE(formatted_status,1000, " BER %8d/%8d "           , status->ber_count_a, status->ber_window_a );
          STRING_APPEND_SAFE(formatted_status,1000, " uncorrs %d\n"           , status->uncorrs_a );
        }
        if (status->nb_seg_b) {
          STRING_APPEND_SAFE(formatted_status,1000, " Layer B      %-6s "     , Silabs_Constel_Text(status->constellation_b));
          STRING_APPEND_SAFE(formatted_status,1000, " %-6s "                  , Silabs_Coderate_Text(status->code_rate_b));
          STRING_APPEND_SAFE(formatted_status,1000, " il %d "                 , status->il_b );
          STRING_APPEND_SAFE(formatted_status,1000, " nb_segments %d "        , status->nb_seg_b );
          STRING_APPEND_SAFE(formatted_status,1000, " locked %d "             , status->fec_lock_b );
          STRING_APPEND_SAFE(formatted_status,1000, " BER %8d/%8d "           , status->ber_count_b, status->ber_window_b );
          STRING_APPEND_SAFE(formatted_status,1000, " uncorrs %d\n"           , status->uncorrs_b );
        }
        if (status->nb_seg_c) {
          STRING_APPEND_SAFE(formatted_status,1000, " Layer C      %-6s "     , Silabs_Constel_Text(status->constellation_c));
          STRING_APPEND_SAFE(formatted_status,1000, " %-6s "                  , Silabs_Coderate_Text(status->code_rate_c));
          STRING_APPEND_SAFE(formatted_status,1000, " il %d "                 , status->il_c );
          STRING_APPEND_SAFE(formatted_status,1000, " nb_segments %d "        , status->nb_seg_c );
          STRING_APPEND_SAFE(formatted_status,1000, " locked %d "             , status->fec_lock_c );
          STRING_APPEND_SAFE(formatted_status,1000, " BER %8d/%8d "           , status->ber_count_c, status->ber_window_c );
          STRING_APPEND_SAFE(formatted_status,1000, " uncorrs %d\n"           , status->uncorrs_c );
        }
        STRING_APPEND_SAFE(formatted_status,1000, " monitoring Layer %c\n"   , front_end->TER_ISDBT_Monitoring_layer + 0x40);
        STRING_APPEND_SAFE(formatted_status,1000, " characteristics   GI %s ", Silabs_GI_Text(status->guard_interval));
        STRING_APPEND_SAFE(formatted_status,1000, " %9d Hz "                 , status->bandwidth_Hz);
        STRING_APPEND_SAFE(formatted_status,1000, " system_id:%d  \n"        , status->isdbt_system_id );
        break;
      }
      case SILABS_DVB_C : {
        STRING_APPEND_SAFE(formatted_status,1000, " characteristics     %s " , Silabs_Constel_Text(status->constellation));
        STRING_APPEND_SAFE(formatted_status,1000, " %9d bps\n"               , status->symbol_rate);
        break;
      }
      case SILABS_DVB_C2: {
        STRING_APPEND_SAFE(formatted_status,1000, " characteristics    "   );
        STRING_APPEND_SAFE(formatted_status,1000, " %s "                   , Silabs_Constel_Text(status->constellation));
        STRING_APPEND_SAFE(formatted_status,1000, " %s "                   , Silabs_Coderate_Text(status->code_rate));
        STRING_APPEND_SAFE(formatted_status,1000, " %s "                   , Silabs_GI_Text(status->guard_interval));
        STRING_APPEND_SAFE(formatted_status,1000, " %9d Hz "               , status->bandwidth_Hz);
        STRING_APPEND_SAFE(formatted_status,1000, " ds_id:%d "             , status->ds_id);
        STRING_APPEND_SAFE(formatted_status,1000, " plp_id:%d "            , status->plp_id);
        STRING_APPEND_SAFE(formatted_status,1000, " C2 system_id:%d "      , status->c2_system_id);
        STRING_APPEND_SAFE(formatted_status,1000, " C2 start freq:%d "     , status->c2_start_freq_hz);
        STRING_APPEND_SAFE(formatted_status,1000, " C2 BW:%d "             , status->c2_system_bw_hz);
        STRING_APPEND_SAFE(formatted_status,1000, " num_data_slice:%d "    , status->num_data_slice);
        STRING_APPEND_SAFE(formatted_status,1000, " num_plp:%d "           , status->num_plp);
        STRING_APPEND_SAFE(formatted_status,1000, "\n"                     );
        break;
      }
      case SILABS_MCNS  : {
        STRING_APPEND_SAFE(formatted_status,1000, " characteristics     %s ", Silabs_Constel_Text(status->constellation));
        STRING_APPEND_SAFE(formatted_status,1000, " %9d bps\n"               , status->symbol_rate);
        break;
      }
      case SILABS_DVB_S : {
        STRING_APPEND_SAFE(formatted_status,1000, " characteristics     %s ", Silabs_Constel_Text(status->constellation));
        STRING_APPEND_SAFE(formatted_status,1000, " %9d bps "               , status->symbol_rate);
        STRING_APPEND_SAFE(formatted_status,1000, " %s \n"                  , Silabs_Coderate_Text(status->code_rate));
        break;
      }
      case SILABS_DSS   : {
        STRING_APPEND_SAFE(formatted_status,1000, " characteristics     %s ", Silabs_Constel_Text(status->constellation));
        STRING_APPEND_SAFE(formatted_status,1000, " %9d bps "               , status->symbol_rate);
        STRING_APPEND_SAFE(formatted_status,1000, " %s \n"                  , Silabs_Coderate_Text(status->code_rate));
        break;
      }
      case SILABS_DVB_S2: {
        STRING_APPEND_SAFE(formatted_status,1000, " characteristics     %s ", Silabs_Constel_Text(status->constellation));
        STRING_APPEND_SAFE(formatted_status,1000, " %9d bps "               , status->symbol_rate);
        STRING_APPEND_SAFE(formatted_status,1000, " %s "                    , Silabs_Coderate_Text(status->code_rate));
        STRING_APPEND_SAFE(formatted_status,1000, " %s "                    , Silabs_Pilots_Text(status->pilots));
        STRING_APPEND_SAFE(formatted_status,1000, " s2x %d "                , status->s2x);
        STRING_APPEND_SAFE(formatted_status,1000, " num_is %d "             , status->num_is);
        STRING_APPEND_SAFE(formatted_status,1000, " isi_id %d\n"            , status->isi_id);
        if (status->fer_mant == -1) {
        STRING_APPEND_SAFE(formatted_status,1000, " fer              --------\n");
        } else {
        rate_f_mant_exp(status->fer_mant, status->fer_exp, &rate_i, &rate_d, &rate_e);
        STRING_APPEND_SAFE(formatted_status,1000, " fer                  %d.%de%d\n" , rate_i, rate_d, rate_e);
        }
        break;
      }
      case SILABS_DVB_T2: {
        STRING_APPEND_SAFE(formatted_status,1000, " characteristics     %s", Silabs_FFT_Text(status->fft_mode));
        STRING_APPEND_SAFE(formatted_status,1000, " %s "                   , Silabs_T2_Base_Lite_Text(status->t2_base_lite));
        STRING_APPEND_SAFE(formatted_status,1000, " %s "                   , Silabs_Extended_BW_Text(status->bw_ext));
        STRING_APPEND_SAFE(formatted_status,1000, " %s"                    , Silabs_Constel_Text(status->constellation));
        STRING_APPEND_SAFE(formatted_status,1000, " %s "                   , Silabs_Rotated_QAM_Text(status->rotated));
        STRING_APPEND_SAFE(formatted_status,1000, " %s "                   , Silabs_Coderate_Text(status->code_rate));
        STRING_APPEND_SAFE(formatted_status,1000, " %s "                   , Silabs_GI_Text(status->guard_interval));
        STRING_APPEND_SAFE(formatted_status,1000, " %9d Hz "               , status->bandwidth_Hz);
        STRING_APPEND_SAFE(formatted_status,1000, " %s "                   , Silabs_T2_Version_Text(status->t2_version));
        STRING_APPEND_SAFE(formatted_status,1000, " %s "                   , Silabs_FEF_Text(status->fef));
        STRING_APPEND_SAFE(formatted_status,1000, " %s "                   , Silabs_MISO_Text(status->tx_mode));
        STRING_APPEND_SAFE(formatted_status,1000, " %s "                   , Silabs_Pilot_Pattern_Text(status->pilot_pattern));
        STRING_APPEND_SAFE(formatted_status,1000, " num_plp:%d "           , status->num_plp);
        STRING_APPEND_SAFE(formatted_status,1000, " plp_id:%d "            , status->plp_id);
        STRING_APPEND_SAFE(formatted_status,1000, " system_id:%d "         , status->t2_system_id );
        STRING_APPEND_SAFE(formatted_status,1000, " %s \n"                 , Silabs_No_Short_Frame_Text(status->short_frame));
        if (status->fer_mant == -1) {
        STRING_APPEND_SAFE(formatted_status,1000, " fer              --------\n");
        } else {
        rate_f_mant_exp(status->fer_mant, status->fer_exp, &rate_i, &rate_d, &rate_e);
        STRING_APPEND_SAFE(formatted_status,1000, " fer                  %d.%de%d\n" , rate_i, rate_d, rate_e);
        }
        break;
      }
      default           : {
        STRING_APPEND_SAFE(formatted_status,1000, " INVALID standard (%d)!!!!\n"  , front_end->standard);
        break;
      }
    }
  }
  if (status_selection & FE_RATES     ) { /* ber per                     */
    if (status->ber_mant     == -1) {
      STRING_APPEND_SAFE(formatted_status,1000, " ber              --------\n");
    } else {
      rate_f_mant_exp(status->ber_mant, status->ber_exp, &rate_i, &rate_d, &rate_e);
      STRING_APPEND_SAFE(formatted_status,1000, " ber                  %d.%de%d\n" , rate_i, rate_d, rate_e);
    }

    if (status->per_mant     == -1) {
    STRING_APPEND_SAFE(formatted_status,1000, " per              --------\n");
    } else {
    rate_f_mant_exp(status->per_mant, status->per_exp, &rate_i, &rate_d, &rate_e);
    STRING_APPEND_SAFE(formatted_status,1000, " per                  %d.%de%d\n" , rate_i, rate_d, rate_e);
    }
  }
  if (status_selection & FE_LOCK_STATE) { /* c_n uncorrs                 */
  STRING_APPEND_SAFE(formatted_status,1000, " c_n                 %2d.%02d\n", status->c_n_100/100, (status->c_n_100 - 100*(status->c_n_100/100)) );
  if (status->uncorrs == -1) {
  STRING_APPEND_SAFE(formatted_status,1000, " uncorrs          --------\n");
  } else {
  STRING_APPEND_SAFE(formatted_status,1000, " uncorrs          %8d\n"     , status->uncorrs);
  }
    STRING_APPEND_SAFE(formatted_status,1000, " spectral_invers. %8d\n"         , status->spectral_inversion);
    STRING_APPEND_SAFE(formatted_status,1000, " RFagc            %8d\n"         , status->RFagc);
    STRING_APPEND_SAFE(formatted_status,1000, " IFagc            %8d\n"         , status->IFagc);
    STRING_APPEND_SAFE(formatted_status,1000, " freq_offset      %8ld\n"        , status->freq_offset);
    STRING_APPEND_SAFE(formatted_status,1000, " timing_offset    %8ld\n"        , status->timing_offset);
    STRING_APPEND_SAFE(formatted_status,1000, " RSSI             %8ld\n"        , status->RSSI);
  }
  if (status_selection & FE_QUALITY   ) { /* SSI SQI                     */
    if (status->SQI == -1) status->SQI = 0;
    STRING_APPEND_SAFE(formatted_status,1000, " SSI              %3d <%0*d%*s\n", status->SSI, (status->SSI)+1, 0, 100 - (status->SSI) +1, ">");
    STRING_APPEND_SAFE(formatted_status,1000, " SQI              %3d <%0*d%*s\n", status->SQI, (status->SQI)+1, 0, 100 - (status->SQI) +1, ">");
  }
  if (status_selection & FE_LOCK_STATE) { /* TS_bitrate_kHz TS_clock_kHz */
    STRING_APPEND_SAFE(formatted_status,1000, " TS bitrate       %d kbit/s\n"   , status->TS_bitrate_kHz);
    STRING_APPEND_SAFE(formatted_status,1000, " TS clock         %d kHz\n"      , status->TS_clock_kHz  );
  }
  return status->demod_lock;
}
/*****************************************************************************************/
/*               SiLabs demodulator API functions (demod and tuner)                      */
/*****************************************************************************************/
/* Main SW init function (to be called first)                                            */
/************************************************************************************************************************
  SiLabs_API_SW_Init function
  Use:        software initialization function
              Used to initialize the DTV demodulator and tuner structures
  Behavior:   This function performs all the steps necessary to initialize the demod and tuner instances
  Parameter:  front_end, a pointer to the SILABS_FE_Context context to be initialized
  Parameter:  demodAdd, the I2C address of the demod
  Parameter:  tunerAdd, the I2C address of the tuner
  Comments:     It MUST be called first and once before using any other function.
                It can be used to build a multi-demod/multi-tuner application, if called several times from the upper
                  layer with different pointers and addresses.
                After execution, all demod and tuner functions are accessible.
************************************************************************************************************************/
signed   char SiLabs_API_SW_Init                    (SILABS_FE_Context *front_end,    signed   int demodAdd, signed   int tunerAdd_Ter, signed   int tunerAdd_Sat)
{
  signed   int chip;
  signed   int i;
  chip = i = 0;            /* To avoid compiler warning when not used */

  front_end->TER_Address_add = tunerAdd_Ter;
  front_end->SAT_Address_add = tunerAdd_Sat;
  front_end->demod_add       = demodAdd;

  SiTRACE("API CALL CONFIG: SiLabs_API_SW_Init                       (front_end, 0x%02x, 0x%02x, 0x%02x);\n", demodAdd, tunerAdd_Ter, tunerAdd_Sat);
  SiTRACE("Wrapper              Source code %s\n", SiLabs_API_TAG_TEXT() );
  SiTRACE("tunerAdd_Ter 0x%02x\n", tunerAdd_Ter);
  SiTRACE("tunerAdd_Sat 0x%02x\n", tunerAdd_Sat);
  front_end->config_code = (tunerAdd_Ter<<16) + (tunerAdd_Sat<<8) + (demodAdd<<0);
  SiTRACE("config_code 0x%06x\n", front_end->config_code);
  /* Start by detecting the chip type */
  if (front_end->chip == 0) {
    chip = SiLabs_chip_detect(demodAdd);
  } else {
    chip = front_end->chip;
  }
  SiTRACE("chip '%d' ('%X')\n", chip, chip);
  front_end->standard = -1;
  front_end->active_TS_mode = SILABS_TS_PARALLEL;
#ifdef    USB_Capability
  for (i=0; i< FRONT_END_COUNT; i++) {
    if ( front_end  == &(FrontEnd_Table[i]) ) {
      if ( i == 0 ) { front_end->ts_mux_input = SILABS_TS_MUX_A; }
      if ( i == 1 ) { front_end->ts_mux_input = SILABS_TS_MUX_B; }
    }
  }
#endif /* USB_Capability */
  WrapperI2C = &WrapperI2C_context;
  WrapperI2C->indexSize = 0;
  WrapperI2C->mustReadWithoutStop = 0;
#ifdef    TERRESTRIAL_FRONT_END
  front_end->TER_RSSI_offset      = 0;
#endif /* TERRESTRIAL_FRONT_END */
#ifdef   SiTRACES
  snprintf(front_end->tag, SILABS_TAG_SIZE ,"fe[%d]", front_end->fe_index);
#endif /* SiTRACES */
#ifdef    INDIRECT_I2C_CONNECTION
  SiTRACE("INDIRECT_I2C_CONNECTION allowed.\n");
  for (i=0; i< FRONT_END_COUNT; i++) {
    if ( front_end  == &(FrontEnd_Table[i]) ) {
      front_end->TER_tuner_I2C_connection = i;
      front_end->SAT_tuner_I2C_connection = i;
    }
  }
  SiTRACE("Default front_end->TER_tuner_I2C_connection: %d\n", front_end->TER_tuner_I2C_connection );
  SiTRACE("Default front_end->SAT_tuner_I2C_connection: %d\n", front_end->SAT_tuner_I2C_connection );
#endif /* INDIRECT_I2C_CONNECTION */
#ifdef    SATELLITE_FRONT_END
#ifndef   LNBH_I2C_ADDRESS
  #define LNBH_I2C_ADDRESS 0x10
#endif /* LNBH_I2C_ADDRESS */
#ifdef    UNICABLE_COMPATIBLE
  front_end->unicable = &(front_end->Unicable_Obj);
  front_end->lnb_type = UNICABLE_LNB_TYPE_NORMAL;
  front_end->swap_detection_done           = 0;
  SiLabs_Unicable_API_Init (
           front_end->unicable,
           front_end,
           (void*)&SiLabs_API_SAT_Tuner_Tune,
           (void*)&SiLabs_API_SAT_Get_AGC,
           (void*)&SiLabs_API_SAT_prepare_diseqc_sequence,
           (void*)&SiLabs_API_SAT_trigger_diseqc_sequence,
           (void*)&SiLabs_API_SAT_send_diseqc_sequence,
           (void*)&SiLabs_API_SAT_Tuner_SetLPF,
           (void*)&SiLabs_API_SAT_voltage,
           (void*)&SiLabs_API_SAT_tone
  );
#endif /* UNICABLE_COMPATIBLE */
#ifdef    LNBH21_COMPATIBLE
  front_end->lnb_chip = 21;
  front_end->lnb_chip_init_done = 0;
  front_end->lnbh21 = &(front_end->lnbh21_Obj);
  L1_LNBH21_Init(front_end->lnbh21, LNBH_I2C_ADDRESS);
#endif /* LNBH21_COMPATIBLE */
#ifdef    LNBH25_COMPATIBLE
  front_end->lnb_chip = 25;
  front_end->lnb_chip_init_done = 0;
  front_end->lnbh25 = &(front_end->lnbh25_Obj);
  L1_LNBH25_Init(front_end->lnbh25, LNBH_I2C_ADDRESS);
#endif /* LNBH25_COMPATIBLE */
#ifdef    LNBH26_COMPATIBLE
  front_end->lnb_chip = 26;
  front_end->lnb_chip_init_done = 0;
  front_end->lnbh26 = &(front_end->lnbh26_Obj);
  L1_LNBH26_Init(front_end->lnbh26, LNBH_I2C_ADDRESS);
#endif /* LNBH26_COMPATIBLE */
#ifdef    LNBH29_COMPATIBLE
  front_end->lnb_chip = 29;
  front_end->lnb_chip_init_done = 0;
  front_end->lnbh29 = &(front_end->lnbh29_Obj);
  L1_LNBH29_Init(front_end->lnbh29, LNBH_I2C_ADDRESS);
#endif /* LNBH29_COMPATIBLE */
#ifdef    A8293_COMPATIBLE
  front_end->lnb_chip = 0xA8293;
  front_end->lnb_chip_init_done = 0;
  front_end->A8293 = &(front_end->A8293_Obj);
  L1_A8293_Init(front_end->A8293, LNBH_I2C_ADDRESS);
#endif /* A8293_COMPATIBLE */
#ifdef    A8297_COMPATIBLE
  front_end->lnb_chip = 0xA8297;
  front_end->lnb_chip_init_done = 0;
  front_end->A8297 = &(front_end->A8297_Obj);
  L1_A8297_Init(front_end->A8297, LNBH_I2C_ADDRESS);
#endif /* A8297_COMPATIBLE */
#ifdef    A8302_COMPATIBLE
  front_end->lnb_chip = 0xA8302;
  front_end->lnb_chip_init_done = 0;
  front_end->A8302 = &(front_end->A8302_Obj);
  L1_A8302_Init(front_end->A8302, LNBH_I2C_ADDRESS);
#endif /* A8302_COMPATIBLE */
#ifdef    A8304_COMPATIBLE
  front_end->lnb_chip = 0xA8304;
  front_end->lnb_chip_init_done = 0;
  front_end->A8304 = &(front_end->A8304_Obj);
  L1_A8304_Init(front_end->A8304, LNBH_I2C_ADDRESS);
#endif /* A8304_COMPATIBLE */
#ifdef    TPS65233_COMPATIBLE
  front_end->lnb_chip = 0x65233;
  front_end->lnb_chip_init_done = 0;
  front_end->TPS65233 = &(front_end->TPS65233_Obj);
  L1_TPS65233_Init(front_end->TPS65233, LNBH_I2C_ADDRESS);
#endif /* TPS65233_COMPATIBLE */
  front_end->SAT_Select_LNB_Chip_lnb_index = 0;
  front_end->SAT_RSSI_offset               = 0;
#endif /* SATELLITE_FRONT_END */

#ifdef    Si2183_COMPATIBLE
  if (chip == 0x2183) {
    front_end->Si2183_FE = &(front_end->Si2183_FE_Obj);
    if (Si2183_L2_SW_Init   (front_end->Si2183_FE
                             , demodAdd
#ifdef    TERRESTRIAL_FRONT_END
                             , tunerAdd_Ter
#ifdef    INDIRECT_I2C_CONNECTION
                             ,(void*)&SiLabs_API_TER_Tuner_I2C_Enable
                             ,(void*)&SiLabs_API_TER_Tuner_I2C_Disable
#endif /* INDIRECT_I2C_CONNECTION */
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
                             , tunerAdd_Sat
#ifdef    UNICABLE_COMPATIBLE
                             ,(void*)&SiLabs_API_SAT_Tuner_Tune
                             ,(void*)&SiLabs_API_SAT_Unicable_Tune
#endif /* UNICABLE_COMPATIBLE */
#ifdef    INDIRECT_I2C_CONNECTION
                             ,(void*)&SiLabs_API_SAT_Tuner_I2C_Enable
                             ,(void*)&SiLabs_API_SAT_Tuner_I2C_Disable
#endif /* INDIRECT_I2C_CONNECTION */
#endif /* SATELLITE_FRONT_END */
                             ,(void*)front_end
                             ) ) {
      front_end->chip = chip;
      Silabs_init_done = 1;
      snprintf(front_end->Si2183_FE->demod->i2c->tag, SILABS_TAG_SIZE, "%s DTV", front_end->tag);
      return 1;
    } else {
      SiTRACE("ERROR initializing Si2183 context\n");
      return 0;
    }
  }
#endif /* Si2183_COMPATIBLE */
  SiTRACE("Unknown chip '%d'\n", front_end->chip);
  SiERROR("SiLabs_API_SW_Init: Unknown chip !\n");
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_Set_Index_and_Tag function
  Use:        Front-End index and tag function
              Used to store the frontend index and tag, which will be used in traces called from L3 level
              Behavior:   It will store the front_end index and tag in the SILABS_FE_Context
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  index, the frontend index
  Parameter:  tag,   the frontend tag (a string limited to SILABS_TAG_SIZE characters)
  Return:     the length of the frontend->tag
************************************************************************************************************************/
signed   int  SiLabs_API_Set_Index_and_Tag          (SILABS_FE_Context* front_end,    unsigned char index, const char* tag)
{
  signed   int L2_tag_len;
  L2_tag_len = 0;

  SiTRACE("API CALL CONFIG: SiLabs_API_Set_Index_and_Tag (front_end, %d, %s);\n", index, tag);
  front_end->fe_index = index;
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183  ) { L2_tag_len = Si2183_L2_Set_Index_and_Tag(front_end->Si2183_FE, index, tag); }
#endif /* Si2183_COMPATIBLE */
  snprintf(front_end->tag, SILABS_TAG_SIZE, "%s %*s", tag, (int)(strlen(tag) +1 - L2_tag_len), " ");

#ifdef    SATELLITE_FRONT_END
#ifdef    LNBH21_COMPATIBLE
  if (front_end->lnb_chip ==     21 ) { snprintf(front_end->lnbh21->i2c->tag, SILABS_TAG_SIZE, "%s LNB", tag ); }
#endif /* LNBH21_COMPATIBLE */
#ifdef    LNBH25_COMPATIBLE
  if (front_end->lnb_chip ==     25 ) { snprintf(front_end->lnbh25->i2c->tag, SILABS_TAG_SIZE, "%s LNB", tag ); }
#endif /* LNBH25_COMPATIBLE */
#ifdef    LNBH26_COMPATIBLE
  if (front_end->lnb_chip ==     26 ) { snprintf(front_end->lnbh26->i2c->tag, SILABS_TAG_SIZE, "%s LNB", tag ); }
#endif /* LNBH26_COMPATIBLE */
#ifdef    LNBH29_COMPATIBLE
  if (front_end->lnb_chip ==     29 ) { snprintf(front_end->lnbh29->i2c->tag, SILABS_TAG_SIZE, "%s LNB", tag ); }
#endif /* LNBH29_COMPATIBLE */
#ifdef    A8293_COMPATIBLE
  if (front_end->lnb_chip == 0xA8293) { snprintf(front_end->A8293->i2c->tag , SILABS_TAG_SIZE, "%s LNB", tag ); }
#endif /* A8293_COMPATIBLE */
#ifdef    A8297_COMPATIBLE
  if (front_end->lnb_chip == 0xA8297) { snprintf(front_end->A8297->i2c->tag , SILABS_TAG_SIZE, "%s LNB", tag ); }
#endif /* A8297_COMPATIBLE */
#ifdef    A8302_COMPATIBLE
  if (front_end->lnb_chip == 0xA8302) { snprintf(front_end->A8302->i2c->tag , SILABS_TAG_SIZE, "%s LNB", tag ); }
#endif /* A8302_COMPATIBLE */
#ifdef    A8304_COMPATIBLE
  if (front_end->lnb_chip == 0xA8304) { snprintf(front_end->A8304->i2c->tag , SILABS_TAG_SIZE, "%s LNB", tag ); }
#endif /* A8304_COMPATIBLE */
#ifdef    TPS65233_COMPATIBLE
  if (front_end->lnb_chip == 0x65233) { snprintf(front_end->TPS65233->i2c->tag , SILABS_TAG_SIZE, "%s LNB", tag ); }
#endif /* TPS65233_COMPATIBLE */
#endif /* SATELLITE_FRONT_END */

  return (int)strlen(front_end->tag);
}
/************************************************************************************************************************
  SiLabs_API_Frontend_Chip function
  Use:        demodulator source code selection function
              Used to select which source code will be used to control the demodulator
  Behavior:   This function sets the chip value in the front-end context
  Parameter:  front_end, a pointer to the SILABS_FE_Context context to be initialized
  Parameter:  demod_id, the code to use in the wrapper to select the demodulator code
************************************************************************************************************************/
signed   int  SiLabs_API_Frontend_Chip              (SILABS_FE_Context *front_end,    signed   int demod_id)
{
  front_end->chip = demod_id;
  SiTRACE("API CALL CONFIG: SiLabs_API_Frontend_Chip                 (front_end, 0x%x/%d);\n", demod_id, demod_id);
  return front_end->chip;
}
/************************************************************************************************************************
  SiLabs_API_TER_tuner_I2C_connection function
  Use:        TER tuner I2C passthrough selection function
              Used to select which demodulator passthrough needs to be used to connect with the TER tuner I2C
  Behavior:   This function sets the TER_tuner_I2C_connection value in the front-end context
************************************************************************************************************************/
signed   int  SiLabs_API_TER_tuner_I2C_connection   (SILABS_FE_Context *front_end,    signed   int fe_index)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_TER_tuner_I2C_connection (front_end, %d);\n", fe_index);
  front_end->TER_tuner_I2C_connection = fe_index;
  return front_end->TER_tuner_I2C_connection;
}
/************************************************************************************************************************
  SiLabs_API_SAT_tuner_I2C_connection function
  Use:        SAT tuner I2C passthrough selection function
              Used to select which demodulator passthrough needs to be used to connect with the SAT tuner I2C
  Behavior:   This function sets the SAT_tuner_I2C_connection value in the front-end context
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_tuner_I2C_connection   (SILABS_FE_Context *front_end,    signed   int fe_index)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_SAT_tuner_I2C_connection (front_end, %d);\n", fe_index);
  front_end->SAT_tuner_I2C_connection = fe_index;
  return front_end->SAT_tuner_I2C_connection;
}
/************************************************************************************************************************
  SiLabs_API_Handshake_Setup function
  Use:        handshake setup function
              Used to set the handshake mode and period
  Behavior:   This function sets the handshake mode and period in the demod instance
  Parameter:  front_end, a pointer to the SILABS_FE_Context context to be initialized
  Parameter:  handshake_mode,   (0='OFF', 1='ON')
  Parameter:  handshake_period_ms, the duration of each handshake period in ms
************************************************************************************************************************/
signed   int  SiLabs_API_Handshake_Setup            (SILABS_FE_Context *front_end,    signed   int handshake_mode, signed   int handshake_period_ms)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_Handshake_Setup          (front_end, %d, %d);\n", handshake_mode, handshake_period_ms);
  front_end           = front_end;           /* To avoid compiler warning if not used */
  handshake_mode      = handshake_mode;      /* To avoid compiler warning if not used */
  handshake_period_ms = handshake_period_ms; /* To avoid compiler warning if not used */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183  ) { front_end->Si2183_FE->handshakeUsed  = handshake_mode; front_end->Si2183_FE->handshakePeriod_ms  = handshake_period_ms; return handshake_mode*handshake_period_ms; }
#endif /* Si2183_COMPATIBLE */
  SiTRACE("SiLabs_API_Handshake_Setup not supporting the current chip '%d'/'0x%x'\n", front_end->chip, front_end->chip);
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_SPI_Setup function
  Use:        SPI fw download configuration function
              Used to configure the SPI download
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  send_option: optional SPI configuration byte.
  Parameter:  clk_pin:    where the spi clock signal comes from.
  Parameter:  clk_pola:   the spi clock signal polarity, 'rising' or 'falling'
  Parameter:  data_pin:   where the spi data signal comes from.
  Parameter:  data_order: whether the spi data signal comes in 'LSB first' or 'MSB first'.
      Please refer to the demodulator's code for possible values.
  Returns:    1 if the part supports SPI, 0 otherwise.
************************************************************************************************************************/
signed   int  SiLabs_API_SPI_Setup                  (SILABS_FE_Context *front_end,    unsigned int send_option, unsigned int clk_pin, unsigned int clk_pola, unsigned int data_pin, unsigned int data_order)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_SPI_Setup                (front_end, %d, %d, %d, %d, %d);\n", send_option, clk_pin, clk_pola, data_pin, data_order);
  front_end->SPI_Setup_send_option = send_option;
  front_end->SPI_Setup_clk_pin     = clk_pin;
  front_end->SPI_Setup_clk_pola    = clk_pola;
  front_end->SPI_Setup_data_pin    = data_pin;
  front_end->SPI_Setup_data_order  = data_order;
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    front_end->Si2183_FE->demod->spi_send_option = send_option;
    if (send_option != 0x00) {
      front_end->Si2183_FE->demod->spi_download    = 1;
    }
    front_end->Si2183_FE->demod->spi_clk_pin     = clk_pin;
    front_end->Si2183_FE->demod->spi_clk_pola    = clk_pola;
    front_end->Si2183_FE->demod->spi_data_pin    = data_pin;
    front_end->Si2183_FE->demod->spi_data_order  = data_order;
    return 1;
  }
#endif /* Si2183_COMPATIBLE */
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_Demods_Broadcast_I2C function
  Use:        Demodulators I2C broadcast selection function
              Used to load FW using the broadcast I2C feature in all demodulators
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  phase, a flag indicating the broadcast state
  Parameter:  front_end_count, the number of demodulators to init
************************************************************************************************************************/
signed   int  SiLabs_API_Demods_Broadcast_I2C       (SILABS_FE_Context *front_ends[], signed   int front_end_count)
{
  signed   int i;
#ifdef    Si2183_COMPATIBLE
  L1_Si2183_Context *Si2183_demods[FRONT_END_COUNT];
#endif /* Si2183_COMPATIBLE */
  SiTRACE_X("API CALL INIT  : SiLabs_API_Demods_Broadcast_I2C         (front_ends, %d);\n", front_end_count);
  i = 0;
#ifdef    Si2183_COMPATIBLE
  if (front_ends[0]->chip == 0x2183  ) {
    /* Store all demodulator pointers in a table */
    for ( i=0; i< front_end_count; i++ )  { Si2183_demods[i] = front_ends[i]->Si2183_FE->demod; }
    /* Download FW in all demodulators using 'broadcast i2c' mode */
    if (Si2183_PowerUpUsingBroadcastI2C( Si2183_demods, front_end_count) == 0) {
    /* Set all demodulator flags to avoid FW download when calling 'switch_to_standard' */
      for ( i=0; i< front_end_count; i++ )  {
        front_ends[i]->Si2183_FE->first_init_done     = 1;
        front_ends[i]->Si2183_FE->Si2183_init_done    = 1;
      }
      Silabs_multiple_front_end_init_done = i;
    }
  }
#endif /* Si2183_COMPATIBLE */
  front_ends         = front_ends;         /* To avoid compiler warning if not used */
  front_end_count    = front_end_count;    /* To avoid compiler warning if not used */
  return i;
}
/************************************************************************************************************************
  SiLabs_API_Broadcast_I2C function
  Use:        TER tuners and demodulators I2C broadcast selection function
              Used to enable/disable the broadcast I2C feature of the demodulators in use
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  phase, a flag indicating the broadcast state
  Parameter:  front_end_count, the number of demodulators to init
************************************************************************************************************************/
signed   int  SiLabs_API_Broadcast_I2C              (SILABS_FE_Context *front_ends[], signed   int front_end_count)
{
  #ifdef    SILABS_TER_TUNER_API
  signed   int i;
  #endif /* SILABS_TER_TUNER_API */
  SiTRACE_X("API CALL INIT  : SiLabs_API_Broadcast_I2C         (front_ends, %d);\n", front_end_count);
  #ifdef    SILABS_TER_TUNER_API
  for (i=0; i<front_end_count; i++) {  SiLabs_API_TER_Tuner_I2C_Enable (front_ends[i]);  }
  SiLabs_API_TER_Broadcast_I2C    (front_ends, front_end_count);
  for (i=0; i<front_end_count; i++) {  SiLabs_API_TER_Tuner_I2C_Disable(front_ends[i]);  }
  #endif /* SILABS_TER_TUNER_API */
  SiLabs_API_Demods_Broadcast_I2C (front_ends, front_end_count);
  return front_end_count;
}
/************************************************************************************************************************
  SiLabs_API_XTAL_Capacitance function
  Use:        Xtal capacitance configuration function
              Used to configure the XTAL capacitance value when using a XTAL as the clock source
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  xtal_capacitance:  the value to be used for start_clk.tune_cap in the demodulator API
   Refer to the demodulator's code for possible values
************************************************************************************************************************/
signed   int  SiLabs_API_XTAL_Capacitance           (SILABS_FE_Context *front_end,    signed   int xtal_capacitance)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_XTAL_Capacitance        (front_end, %d);\n", xtal_capacitance);
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183  ) { front_end->Si2183_FE->demod->cmd->start_clk.tune_cap = xtal_capacitance; return 1; }
#endif /* Si2183_COMPATIBLE */
  SiTRACE("SiLabs_API_XTAL_Capacitance not supporting the current chip '%d'/'0x%x'\n", front_end->chip, front_end->chip);
  return 0;
}
/* TER tuner selection and configuration functions (to be used after SiLabs_API_SW_Init) */
/************************************************************************************************************************
  SiLabs_API_TER_Possible_Tuners function
  Use:        TER tuner information function
              Used to know which TER tuners can be used (selected using SiLabs_API_Select_TER_Tuner)
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  tunerList, a string to store the list of TER tuners
************************************************************************************************************************/
signed   int  SiLabs_API_TER_Possible_Tuners        (SILABS_FE_Context *front_end,    char *tunerList)
{
#ifdef   SILABS_TER_TUNER_API
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return SiLabs_TER_Tuner_Possible_Tuners(front_end->Si2183_FE->tuner_ter, tunerList); }
#endif /* Si2183_COMPATIBLE */
#else  /* SILABS_TER_TUNER_API */
  front_end = front_end; /* To avoid compiler warning if not used */
  tunerList = tunerList; /* To avoid compiler warning if not used */
#endif /* SILABS_TER_TUNER_API */
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_Select_TER_Tuner function
  Use:        TER tuner selection function
              Used to select which TER tuner is in use
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  ter_tuner_code, the code used for the TER tuner selection,
   easily readible when in hexadecimal, as it matched the part name, i.e '0x2178b' for Si2178B
  Parameter:  ter_tuner_index, the index of the tuner in the array of the selected tuner,
   in most cases this will be '0'. This is a provision to allow several tuners to be selected during execution
************************************************************************************************************************/
signed   int  SiLabs_API_Select_TER_Tuner           (SILABS_FE_Context *front_end,    signed   int ter_tuner_code, signed   int ter_tuner_index)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_Select_TER_Tuner         (front_end, 0x%02x, %d);\n", ter_tuner_code, ter_tuner_index);
  front_end->Select_TER_Tuner_ter_tuner_code  = ter_tuner_code;
  front_end->Select_TER_Tuner_ter_tuner_index = ter_tuner_index;
#ifdef   SILABS_TER_TUNER_API
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return SiLabs_TER_Tuner_Select_Tuner (front_end->Si2183_FE->tuner_ter,  ter_tuner_code, ter_tuner_index); }
#endif /* Si2183_COMPATIBLE */
#endif /* SILABS_TER_TUNER_API */
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_TER_Tuner function
  Use:        TER tuner pointer retrieval function
              Used to retrieve a pointer to the TER tuner in use
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  returns: The pointer to the selected TER tuner
************************************************************************************************************************/
void*         SiLabs_API_TER_Tuner                  (SILABS_FE_Context *front_end)
{
  SiTRACE("API CALL TER   : SiLabs_API_TER_Tuner         (front_end);\n");
#ifdef   SILABS_TER_TUNER_API
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return front_end->Si2183_FE->tuner_ter; }
#endif /* Si2183_COMPATIBLE */
#else  /* SILABS_TER_TUNER_API */
  front_end = front_end;             /* To avoid compiler warning if not used */
#endif /* SILABS_TER_TUNER_API */
  return NULL;
}
/************************************************************************************************************************
  SiLabs_API_TER_Address function
  Use:        TER tuner address selection function
              Used to set the I2C address of the TER tuner in use (selected using SiLabs_API_Select_TER_Tuner)
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  add, the i2c address of the TER tuner
************************************************************************************************************************/
signed   int  SiLabs_API_TER_Address                (SILABS_FE_Context *front_end,    signed   int add)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_TER_Address         (front_end, add 0x%02x);\n", add);
  front_end->TER_Address_add  = add;
#ifdef   SILABS_TER_TUNER_API
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return SiLabs_TER_Tuner_Set_Address(front_end->Si2183_FE->tuner_ter,  add); }
#endif /* Si2183_COMPATIBLE */
#endif /* SILABS_TER_TUNER_API */
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_TER_Broadcast_I2C function
  Use:        TER tuner I2C broadcast selection function
              Used to enable/disable the broadcast I2C feature of the TER tuner in use (selected using SiLabs_API_Select_TER_Tuner)
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  phase, a flag indicating the broadcast state
  Parameter:  front_end_count, a flag indicating to the tuner if it needs to load fw
************************************************************************************************************************/
signed   int  SiLabs_API_TER_Broadcast_I2C          (SILABS_FE_Context *front_ends[], signed   int front_end_count)
{
#ifdef   SILABS_TER_TUNER_API
  signed   int i;
  signed   int c;
  signed   int res;
  signed   int *TER_tuner_init_done[front_end_count];
  SILABS_TER_TUNER_Context *silabs_tuners[front_end_count];
  SiTRACE_X("API CALL INIT  : SiLabs_API_TER_Broadcast_I2C         (front_ends, %d);\n", front_end_count);
  c = 0;
  for (i = 0; i < front_end_count; i++) {
    SiTRACE_X("SiLabs_API_TER_Broadcast_I2C front_ends[%d]->chip 0x%x\n", i, front_ends[i]->chip);
#ifdef    Si2183_COMPATIBLE
  if (front_ends[i]->chip == 0x2183  ) { silabs_tuners[i] = front_ends[i]->Si2183_FE->tuner_ter; TER_tuner_init_done[i] = &(front_ends[i]->Si2183_FE->TER_tuner_init_done);  c++; }
#endif /* Si2183_COMPATIBLE */
  }
  SiTRACE_X("SiLabs_API_TER_Broadcast_I2C %d tuners found\n", c);
  if (c) {
    if ( (res = SiLabs_TER_Tuner_Broadcast_I2C( silabs_tuners, c) ) == 0) {
      for (i = 0; i < c; i++) { *(TER_tuner_init_done[i]) = 1; }
    }
    return res;
  }
#endif /* SILABS_TER_TUNER_API */
  front_ends         = front_ends;         /* To avoid compiler warning if not used */
  front_end_count    = front_end_count;    /* To avoid compiler warning if not used */
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_TER_Tuner_ClockConfig function
  Use:        TER tuner clock configuration function
              Used to configure the TER tuner clock path
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  xtal:          is the tuner driving a xtal ('0': no xtal(external clock) '1': xtal driven by tuner).
  Parameter:  xout:          the tuner clock output state ('0': off, '1': on).
************************************************************************************************************************/
signed   int  SiLabs_API_TER_Tuner_ClockConfig      (SILABS_FE_Context *front_end,    signed   int xtal, signed   int xout)
{
#ifdef    TERRESTRIAL_FRONT_END
#ifdef    TER_TUNER_SILABS
  SILABS_TER_TUNER_Context *tuner_ter;
  tuner_ter = NULL;
#endif /* TER_TUNER_SILABS */
#endif /* TERRESTRIAL_FRONT_END */
  SiTRACE("API CALL CONFIG: SiLabs_API_TER_Tuner_ClockConfig    (front_end, %d, %d);\n", xtal, xout);
  front_end->TER_Tuner_ClockConfig_xtal      = xtal;
  front_end->TER_Tuner_ClockConfig_xout      = xout;
#ifdef    TERRESTRIAL_FRONT_END
#ifdef    TER_TUNER_SILABS
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { tuner_ter = front_end->Si2183_FE->tuner_ter; }
#endif /* Si2183_COMPATIBLE */
  if (tuner_ter == NULL) {
    SiTRACE("No tuner_ter defined, SiLabs_API_TER_Tuner_ClockConfig can't be executed!\n");
    return 0;
  }
  SiLabs_TER_Tuner_ClockConfig (tuner_ter, xtal, xout);
#endif /* TER_TUNER_SILABS */
#endif /* TERRESTRIAL_FRONT_END */
  return 1;
}
/************************************************************************************************************************
  SiLabs_API_TER_Clock_Options function
  Use:        TER tuner options display function
              Used to known which options are possible for the TER tuner clock path
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  clockOptions:  a string used to sore the options text
  Return: 0 if error, otherwise the tuner code
************************************************************************************************************************/
signed   int  SiLabs_API_TER_Clock_Options          (SILABS_FE_Context *front_end,    char* clockOptions)
{
  front_end     = front_end;    /* To avoid compiler warning if not used */
  clockOptions  = clockOptions; /* To avoid compiler warning if not used */
  snprintf(clockOptions, 1000, "%s", "");
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    snprintf(clockOptions, 1000, "%s", "Si2183 clock options:\n");
    STRING_APPEND_SAFE(clockOptions,1000, "clock_source  (Xtal_clock:%d, TER_Tuner_clock:%d, SAT_Tuner_clock:%d)\n", Si2183_Xtal_clock, Si2183_TER_Tuner_clock, Si2183_SAT_Tuner_clock);
    STRING_APPEND_SAFE(clockOptions,1000, "clock_input   (CLK_CLKIO:%d, CLK_XTAL_IN:%d,  XTAL(driven by the Si2183):%d)\n", 44, 33, 32);
    STRING_APPEND_SAFE(clockOptions,1000, "clock_freq    (CLK_16MHZ:%d, CLK_24MHZ:%d, CLK_27MHZ:%d\n", 16, 24, 27);
    STRING_APPEND_SAFE(clockOptions,1000, "clock_control (ALWAYS_ON:%d,  ALWAYS_OFF:%d, MANAGED:%d\n" ,  1, 0, 2);
    return 0x2183;
  }
#endif /* Si2183_COMPATIBLE */
  SiTRACE("SiLabs_API_TER_Clock_Options not supporting the current chip '%d'/'0x%x'\n", front_end->chip, front_end->chip);
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_TER_Clock function
  Use:        TER tuner clock configuration function, at demodulator level
              Used to configure the TER tuner clock path from TER tuner to demodulator
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  clock_source:  where the clock signal comes from.
  Parameter:  clock_input:   on which pin is the clock received.
  Parameter:  clock_freq:    clock frequency
  Parameter:  clock_control: how to control the clock (always_on/always_off/managed)
   Refer to the demodulator's code for possible values
************************************************************************************************************************/
signed   int  SiLabs_API_TER_Clock                  (SILABS_FE_Context *front_end,    signed   int clock_source, signed   int clock_input, signed   int clock_freq, signed   int clock_control)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_TER_Clock                (front_end, %d, %d, %d, %d);\n", clock_source, clock_input, clock_freq, clock_control);
  front_end->TER_Clock_clock_source  = clock_source;
  front_end->TER_Clock_clock_input   = clock_input;
  front_end->TER_Clock_clock_freq    = clock_freq;
  front_end->TER_Clock_clock_control = clock_control;
#ifdef    TERRESTRIAL_FRONT_END
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183  ) { return Si2183_L2_TER_Clock  (front_end->Si2183_FE , clock_source, clock_input, clock_freq, clock_control); }
#endif /* Si2183_COMPATIBLE */
#endif /* TERRESTRIAL_FRONT_END */
  SiTRACE("SiLabs_API_TER_Clock not supporting the current chip '%d'/'0x%x'\n", front_end->chip, front_end->chip);
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_TER_FEF_Options function
  Use:        TER FEF options display function
              Used to known which options are possible for the TER FEF
  parameter:  front_end, a pointer to the SILABS_FE_Context context
  parameter:  fefOptions:  a string used to store the options text
                It needs to be declared with a length of 1000
************************************************************************************************************************/
signed   int  SiLabs_API_TER_FEF_Options            (SILABS_FE_Context *front_end,    char* fefOptions)
{
  front_end      = front_end;        /* To avoid compiler warning if not used */
  fefOptions     = fefOptions;       /* To avoid compiler warning if not used */
  snprintf(fefOptions,1000, "%s", "");
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    snprintf(fefOptions,1000, "%s", "(Si2183 FEF options)\n");
    STRING_APPEND_SAFE(fefOptions,1000, " fef mode      (SLOW_NORMAL_AGC:0, FREEZE_PIN:1, SLOW_INITIAL_AGC:2)\n");
    STRING_APPEND_SAFE(fefOptions,1000, " fef pin       (Unused:0x0, MP_A:0xa, MP_B:0xb, MP_C:0xc, MP_D:0xd)\n" );
    STRING_APPEND_SAFE(fefOptions,1000, " fef level     (0: active low, 1: active high)\n");
    return 0x2183;
  }
#endif /* Si2183_COMPATIBLE */
  SiTRACE("SiLabs_API_TER_AGC not supporting the current chip '%d'/'0x%x'\n", front_end->chip, front_end->chip);
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_TER_FEF_Config function
  Use:        TER tuner FEF configuration function
              Used to configure the TER tuner FEF
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  fef_mode: how the FEF signal is controlled
  Parameter:  fef_pin:  where the FEF signal comes from.
  Parameter:  fef_level: logical level when active.
   Refer to the demodulator's code for possible values
************************************************************************************************************************/
signed   int  SiLabs_API_TER_FEF_Config             (SILABS_FE_Context *front_end,    signed   int fef_mode, signed   int fef_pin, signed   int fef_level)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_TER_FEF_Config           (front_end, %d, 0x%x, %d);\n", fef_mode, fef_pin, fef_level);
  front_end->TER_FEF_Config_fef_mode       = fef_mode;
  front_end->TER_FEF_Config_fef_pin        = fef_pin;
  front_end->TER_FEF_Config_fef_level      = fef_level;
#ifdef    DEMOD_DVB_T2
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return Si2183_L2_TER_FEF_CONFIG (front_end->Si2183_FE, fef_mode, fef_pin, fef_level); }
#endif /* Si2183_COMPATIBLE */
#endif /* DEMOD_DVB_T2 */
  SiTRACE("SiLabs_API_TER_FEF not supporting the current chip '%d'/'0x%x'\n", front_end->chip, front_end->chip);
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_TER_AGC_Options function
  Use:        TER AGC options display function
              Used to known which options are possible for the TER AGC
  parameter:  front_end, a pointer to the SILABS_FE_Context context
  parameter:  agcOptions:  a string used to store the options text
                It needs to be declared with a length of 1000
************************************************************************************************************************/
signed   int  SiLabs_API_TER_AGC_Options            (SILABS_FE_Context *front_end,    char* agcOptions)
{
  front_end      = front_end;        /* To avoid compiler warning if not used */
  agcOptions     = agcOptions;       /* To avoid compiler warning if not used */
  snprintf(agcOptions,1000, "%s", "");
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    snprintf(agcOptions,1000, "%s", "(Si2183 AGC options)\n");
    STRING_APPEND_SAFE(agcOptions,1000, " agc mode      (Unused:0x0, MP_A:0xa, MP_B:0xb, MP_C:0xc, MP_D:0xd)\n");
    STRING_APPEND_SAFE(agcOptions,1000, " agc inversion (0: not_inverted, 1: inverted)\n");
    return 0x2183;
  }
#endif /* Si2183_COMPATIBLE */
  SiTRACE("SiLabs_API_TER_AGC not supporting the current chip '%d'/'0x%x'\n", front_end->chip, front_end->chip);
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_TER_AGC function
  Use:        TER demod AGC configuration function
              Used to configure the TER AGC in the demod
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  agc1_mode:       not used anymore. Settings will always be applied to AGC2 for TER reception. Always use 0
  Parameter:  agc1_inversion:  not used anymore. Settings will always be applied to AGC2 for TER reception. Always use 0
  Parameter:  agc2_mode:  where the AGC 2 PWM comes from.
  Parameter:  agc2_inversion: 0/1 to indicate if AGC 2 is inverted or not (depends on the TER tuner and HW design)
   Refer to the demodulator's code for possible values
************************************************************************************************************************/
signed   int  SiLabs_API_TER_AGC                    (SILABS_FE_Context *front_end,    signed   int agc1_mode, signed   int agc1_inversion, signed   int agc2_mode, signed   int agc2_inversion)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_TER_AGC                  (front_end, 0x%x, %d, 0x%x, %d);\n", agc1_mode, agc1_inversion, agc2_mode, agc2_inversion);
  front_end->TER_AGC_agc1_mode      = agc1_mode;
  front_end->TER_AGC_agc1_inversion = agc1_inversion;
  front_end->TER_AGC_agc2_mode      = agc2_mode;
  front_end->TER_AGC_agc2_inversion = agc2_inversion;
#ifdef    TERRESTRIAL_FRONT_END
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return Si2183_L2_TER_AGC (front_end->Si2183_FE, agc1_mode, agc1_inversion, agc2_mode, agc2_inversion); }
#endif /* Si2183_COMPATIBLE */
#endif /* TERRESTRIAL_FRONT_END */
  SiTRACE("SiLabs_API_TER_AGC not supporting the current chip '%d'/'0x%x'\n", front_end->chip, front_end->chip);
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_TER_Tuner_AGC_Input function
  Use:        TER tuner AGC configuration function
              Used to configure the TER tuner AGC in the tuner
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  dtv_agc_source: where the AGC 1 PWM enters the TER tuner
   Refer to the TER tuner code for possible values
************************************************************************************************************************/
signed   int  SiLabs_API_TER_Tuner_AGC_Input        (SILABS_FE_Context *front_end,    signed   int dtv_agc_source )
{
  SiTRACE("API CALL CONFIG: SiLabs_API_TER_Tuner_AGC_Input (front_end, 0x%x);\n", dtv_agc_source);
  front_end->TER_Tuner_AGC_Input_dtv_agc_source = dtv_agc_source;
#ifdef    TERRESTRIAL_FRONT_END
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { front_end->Si2183_FE->demod->TER_tuner_agc_input = dtv_agc_source; return 1;}
#endif /* Si2183_COMPATIBLE */
#endif /* TERRESTRIAL_FRONT_END */
  SiTRACE("SiLabs_API_TER_Tuner_AGC_Input not supporting the current chip '%d'/'0x%x'\n", front_end->chip, front_end->chip);
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_TER_Tuner_GPIOs function
  Use:       TER tuner GPIOs configuration function
              Used to configure the TER tuner GPIOs in the tuner
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  gpio1_mode: the value to set the gpio1
  Parameter:  gpio2_mode: the value to set the gpio2
   Refer to the TER tuner code for possible values
************************************************************************************************************************/
signed   int  SiLabs_API_TER_Tuner_GPIOs            (SILABS_FE_Context *front_end,    signed   int gpio1_mode, signed   int gpio2_mode)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_TER_Tuner_GPIOs (front_end, %d, %d);\n", gpio1_mode, gpio2_mode);
#ifdef    TERRESTRIAL_FRONT_END
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { SiLabs_TER_Tuner_GPIOS ( front_end->Si2183_FE->tuner_ter, gpio1_mode, gpio2_mode); return 1;}
#endif /* Si2183_COMPATIBLE */
#endif /* TERRESTRIAL_FRONT_END */
  SiTRACE("SiLabs_API_TER_Tuner_GPIOs not supporting the current chip '%d'/'0x%x'\n", front_end->chip, front_end->chip);
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_TER_Tuner_FEF_Input function
  Use:        TER tuner FEF configuration function
              Used to configure the TER tuner FEF input in the tuner
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  dtv_fef_freeze_input: where the FEF freeze signal enters the TER tuner
   Refer to the TER tuner code for possible values
************************************************************************************************************************/
signed   int  SiLabs_API_TER_Tuner_FEF_Input        (SILABS_FE_Context *front_end,    signed   int dtv_fef_freeze_input )
{
  SiTRACE("API CALL CONFIG: SiLabs_API_TER_Tuner_FEF_Input (front_end, 0x%x);\n", dtv_fef_freeze_input);
  front_end->TER_Tuner_FEF_Input_dtv_fef_freeze_input = dtv_fef_freeze_input;
#ifdef    TERRESTRIAL_FRONT_END
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return SiLabs_TER_Tuner_DTV_FEF_SOURCE(front_end->Si2183_FE->tuner_ter, dtv_fef_freeze_input); }
#endif /* Si2183_COMPATIBLE */
#endif /* TERRESTRIAL_FRONT_END */
  SiTRACE("SiLabs_API_TER_Tuner_FEF_Input not supporting the current chip '%d'/'0x%x'\n", front_end->chip, front_end->chip);
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_TER_Tuner_IF_Output function
  Use:        TER tuner IF configuration function
              Used to configure the TER tuner IF in the tuner
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  dtv_out_type: where the AGC 1 PWM exits the TER tuner from
   Refer to the TER tuner code for possible values
************************************************************************************************************************/
signed   int  SiLabs_API_TER_Tuner_IF_Output        (SILABS_FE_Context *front_end,    signed   int dtv_out_type )
{
  SiTRACE("API CALL CONFIG: SiLabs_API_TER_Tuner_IF_Output (front_end, 0x%x);\n", dtv_out_type);
  front_end->TER_Tuner_IF_Output_dtv_out_type = dtv_out_type;
#ifdef    TERRESTRIAL_FRONT_END
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { front_end->Si2183_FE->demod->TER_tuner_if_output = dtv_out_type; return 1;}
#endif /* Si2183_COMPATIBLE */
#endif /* TERRESTRIAL_FRONT_END */
  SiTRACE("SiLabs_API_TER_Tuner_IF_Output not supporting the current chip '%d'/'0x%x'\n", front_end->chip, front_end->chip);
  return 0;
}
/* SAT tuner selection and configuration functions (to be used after SiLabs_API_SW_Init) */
/************************************************************************************************************************
  SiLabs_API_SAT_Possible_Tuners function
  Use:        SAT tuner information function
              Used to know which SAT tuners can be used (selected using SiLabs_API_Select_SAT_Tuner)
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  tunerList, a string to store the list of SAT tuners
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_Possible_Tuners        (SILABS_FE_Context *front_end,    char *tunerList)
{
#ifdef   SILABS_SAT_TUNER_API
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return SiLabs_SAT_Tuner_Possible_Tuners(front_end->Si2183_FE->tuner_sat, tunerList); }
#endif /* Si2183_COMPATIBLE */
#else  /* SILABS_SAT_TUNER_API */
  front_end = front_end; /* To avoid compiler warning if not used */
  tunerList = tunerList; /* To avoid compiler warning if not used */
#endif /* SILABS_SAT_TUNER_API */
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_Select_SAT_Tuner function
  Use:        SAT tuner selection function
              Used to select which SAT tuner is in use
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  ter_tuner_code, the code used for the SAT tuner selection,
   easily readible when in hexadecimal, as it matched the part name, i.e '0x2178b' for Si2178B
  Parameter:  ter_tuner_index, the index of the tuner in the array of the selected tuner,
   in most cases this will be '0'. This is a provision to allow several tuners to be selected during execution
************************************************************************************************************************/
signed   int  SiLabs_API_Select_SAT_Tuner           (SILABS_FE_Context *front_end,    signed   int sat_tuner_code, signed   int sat_tuner_index)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_Select_SAT_Tuner         (front_end, 0x%x, %d);\n", sat_tuner_code, sat_tuner_index);
  front_end->Select_SAT_Tuner_sat_tuner_code  = sat_tuner_code;
  front_end->Select_SAT_Tuner_sat_tuner_index = sat_tuner_index;
#ifdef   SILABS_SAT_TUNER_API
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return SiLabs_SAT_Tuner_Select_Tuner (front_end->Si2183_FE->tuner_sat,  sat_tuner_code, sat_tuner_index); }
#endif /* Si2183_COMPATIBLE */
#endif /* SILABS_SAT_TUNER_API */
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_SAT_Tuner_Sub function
  Use:        SAT tuner sub-division selection function
              Used to select which part of a SAT tuner to use, when the SAT tuner is a dual.
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  ter_tuner_sub, the flag used in the SAT tuner driver to select between sub-sections
   in most cases this will be '0'. It's only set to 1 for secondary paths in dual SAT tuners
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_Tuner_Sub              (SILABS_FE_Context *front_end,    signed   int sat_tuner_sub)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_SAT_Tuner_Sub            (front_end, %d);\n", sat_tuner_sub);
  front_end->Select_SAT_Tuner_sat_tuner_sub   = sat_tuner_sub;
#ifdef   SILABS_SAT_TUNER_API
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return SiLabs_SAT_Tuner_Sub (front_end->Si2183_FE->tuner_sat,  sat_tuner_sub); }
#endif /* Si2183_COMPATIBLE */
#endif /* SILABS_SAT_TUNER_API */
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_SAT_Address function
  Use:        SAT tuner address selection function
              Used to set the I2C address of the SAT tuner in use (selected using SiLabs_API_Select_SAT_Tuner)
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  add, the i2c address of the SAT tuner
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_Address                (SILABS_FE_Context *front_end,    signed   int add)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_SAT_Address         (front_end, add 0x%02x);\n", add);
  front_end->SAT_Address_add = add;
#ifdef   SILABS_SAT_TUNER_API
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return SiLabs_SAT_Tuner_Set_Address(front_end->Si2183_FE->tuner_sat,  add); }
#endif /* Si2183_COMPATIBLE */
#endif /* SILABS_SAT_TUNER_API */
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_SAT_Clock_Options function
  Use:        SAT tuner options display function
              Used to known which options are possible for the SAT tuner clock path
  parameter:  front_end, a pointer to the SILABS_FE_Context context
  parameter:  clockOptions:  a string used to store the options text
              It needs to be declared with a length of 1000
  Return: 0 if error, otherwise the tuner code
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_Clock_Options          (SILABS_FE_Context *front_end,    char* clockOptions)
{
  front_end     = front_end;    /* To avoid compiler warning if not used */
  clockOptions  = clockOptions; /* To avoid compiler warning if not used */
  snprintf(clockOptions, 1000, "%s", "");
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    snprintf(clockOptions, 1000, "%s", "Si2183 clock options:\n");
    STRING_APPEND_SAFE(clockOptions,1000, "clock_source  (Xtal_clock:%d,  TER_Tuner_clock:%d,  SAT_Tuner_clock:%d)\n", Si2183_Xtal_clock, Si2183_TER_Tuner_clock, Si2183_SAT_Tuner_clock);
    STRING_APPEND_SAFE(clockOptions,1000, "clock_input   (CLK_CLKIO:%d,  CLK_XTAL_IN:%d,  XTAL(driven by the Si283):%d)\n", 44, 33, 32);
    STRING_APPEND_SAFE(clockOptions,1000, "clock_freq    (CLK_16MHZ:%d,  CLK_24MHZ:%d,  CLK_27MHZ:%d\n", 16, 24, 27);
    STRING_APPEND_SAFE(clockOptions,1000, "clock_control (ALWAYS_ON:%d, ALWAYS_OFF:%d, MANAGED:%d\n"   ,  1, 0, 2);
    return 0x2183;
  }
#endif /* Si2183_COMPATIBLE */
  SiTRACE("SiLabs_API_SAT_Clock not supporting the current chip '%d'/'0x%x'\n", front_end->chip, front_end->chip);
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_SAT_Clock function
  Use:        SAT tuner configuration function
              Used to configure the SAT tuner clock path
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  clock_source:  where the clock signal comes from.
  Parameter:  clock_input:   on which pin is the clock received.
  Parameter:  clock_freq:    clock frequency
  Parameter:  clock_control: how to control to clock (always_on/always_off/managed)
   Refer to the demodulator's code for possible values
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_Clock                  (SILABS_FE_Context *front_end,    signed   int clock_source, signed   int clock_input, signed   int clock_freq, signed   int clock_control)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_SAT_Clock                (front_end, %d, %d, %d, %d);\n", clock_source, clock_input, clock_freq, clock_control);
  front_end->SAT_Clock_clock_source  = clock_source;
  front_end->SAT_Clock_clock_input   = clock_input;
  front_end->SAT_Clock_clock_freq    = clock_freq;
  front_end->SAT_Clock_clock_control = clock_control;
#ifdef    SATELLITE_FRONT_END
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183  ) { return Si2183_L2_SAT_Clock  (front_end->Si2183_FE,  clock_source, clock_input, clock_freq, clock_control); }
#endif /* Si2183_COMPATIBLE */
#endif /* SATELLITE_FRONT_END */
  SiTRACE("SiLabs_API_SAT_Clock not supporting the current chip '%d'/'0x%x'\n", front_end->chip, front_end->chip);
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_SAT_AGC_Options function
  Use:        SAT AGC options display function
              Used to known which options are possible for the SAT AGC
  parameter:  front_end, a pointer to the SILABS_FE_Context context
  parameter:  agcOptions:  a string used to store the options text
                It needs to be declared with a length of 1000
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_AGC_Options            (SILABS_FE_Context *front_end,    char* agcOptions)
{
  front_end      = front_end;        /* To avoid compiler warning if not used */
  agcOptions     = agcOptions;       /* To avoid compiler warning if not used */
  snprintf(agcOptions,1000, "%s", "");
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    snprintf(agcOptions,1000, "%s", "(Si2183 AGC options)\n");
    STRING_APPEND_SAFE(agcOptions,1000, " agc mode      (Unused:0x0, MP_A:0xa, MP_B:0xb, MP_C:0xc, MP_D:0xd)\n");
    STRING_APPEND_SAFE(agcOptions,1000, " agc inversion (0: not_inverted, 1: inverted)\n");
    return 0x2183;
  }
#endif /* Si2183_COMPATIBLE */
  SiTRACE("SiLabs_API_SAT_AGC not supporting the current chip '%d'/'0x%x'\n", front_end->chip, front_end->chip);
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_SAT_AGC function
  Use:        SAT tuner AGC configuration function
              Used to configure the SAT tuner AGC
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  agc1_mode:  where the AGC 1 PWM comes from.
  Parameter:  agc1_inversion: 0/1 to indicate if AGC 1 is inverted or not (depends on the SAT tuner and HW design)
  Parameter:  agc2_mode:       not used anymore. Settings will always be applied to AGC1 for SAT reception. Always use 0
  Parameter:  agc2_inversion:  not used anymore. Settings will always be applied to AGC1 for SAT reception. Always use 0
   Refer to the demodulator's code for possible values
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_AGC                    (SILABS_FE_Context *front_end,    signed   int agc1_mode, signed   int agc1_inversion, signed   int agc2_mode, signed   int agc2_inversion)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_SAT_AGC                  (front_end, 0x%x, %d, 0x%x, %d);\n", agc1_mode, agc1_inversion, agc2_mode, agc2_inversion);
  front_end->SAT_AGC_agc1_mode      = agc1_mode;
  front_end->SAT_AGC_agc1_inversion = agc1_inversion;
  front_end->SAT_AGC_agc2_mode      = agc2_mode;
  front_end->SAT_AGC_agc2_inversion = agc2_inversion;
#ifdef    SATELLITE_FRONT_END
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return Si2183_L2_SAT_AGC (front_end->Si2183_FE, agc1_mode, agc1_inversion, agc2_mode, agc2_inversion); }
#endif /* Si2183_COMPATIBLE */
#endif /* SATELLITE_FRONT_END */
  SiTRACE("SiLabs_API_SAT_AGC not supporting the current chip '%d'/'0x%x'\n", front_end->chip, front_end->chip);
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_SAT_Spectrum function
  Use:        SAT spectrum inversion function
              Used to configure the SAT ZIF spectrum inversion
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  spectrum_inversion:   a flag indicating if the SAT signal appears inverted.
               possible values: 0(not_inverted), 1(inverted)
               This situation is possible if there is an I/Q swap in the HW design, for easier routing
               It is perfectly OK to do that to route easily, but the SW needs to be informed of this inversion.
               NB: The additional inversion added by Unicable equipement should not be taken into account here
                    The spectrum_inversion set here corresponds to the 'normal' mode
  Returns:    0 if no error, -1 if not implemented for the current demod
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_Spectrum               (SILABS_FE_Context *front_end,    signed   int spectrum_inversion)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_SAT_Spectrum             (front_end, %d);\n", spectrum_inversion);
  front_end->SAT_Spectrum_spectrum_inversion = spectrum_inversion;
#ifdef    SATELLITE_FRONT_END
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return Si2183_L2_SAT_Spectrum(front_end->Si2183_FE, spectrum_inversion); }
#endif /* Si2183_COMPATIBLE */
#endif /* SATELLITE_FRONT_END */
  SiTRACE("SiLabs_API_SAT_Spectrum not supporting the current chip '%d'/'0x%x'\n", front_end->chip, front_end->chip);
  SiERROR("SiLabs_API_SAT_Spectrum not supporting the current chip\n");
  return -1;
}
/************************************************************************************************************************
  SiLabs_API_SAT_Possible_LNB_Chips function
  Use:        LNB controller information function
              Used to know which LNB controllers can be used (selected using SiLabs_API_Select_LNB_Chip)
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  lnbList, a string to store the list of LNB Controllers
                It needs to be declared with a length of 1000
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_Possible_LNB_Chips     (SILABS_FE_Context *front_end,    char *lnbList)
{
  signed   int i;
  i = 0;
  snprintf(lnbList,1000, "%s", "");
#ifdef    LNBH21_COMPATIBLE
  STRING_APPEND_SAFE(lnbList,1000, " LNBH21"); i++;
#endif /* LNBH21_COMPATIBLE */
#ifdef    LNBH25_COMPATIBLE
  STRING_APPEND_SAFE(lnbList,1000, " LNBH25"); i++;
#endif /* LNBH25_COMPATIBLE */
#ifdef    LNBH26_COMPATIBLE
  STRING_APPEND_SAFE(lnbList,1000, " LNBH26"); i++;
#endif /* LNBH26_COMPATIBLE */
#ifdef    LNBH29_COMPATIBLE
  STRING_APPEND_SAFE(lnbList,1000, " LNBH29"); i++;
#endif /* LNBH29_COMPATIBLE */
#ifdef    A8293_COMPATIBLE
  STRING_APPEND_SAFE(lnbList,1000, " A8293"); i++;
#endif /* A8293_COMPATIBLE */
#ifdef    A8297_COMPATIBLE
  STRING_APPEND_SAFE(lnbList,1000, " A8297"); i++;
#endif /* A8297_COMPATIBLE */
#ifdef    A8302_COMPATIBLE
  STRING_APPEND_SAFE(lnbList,1000, " A8302"); i++;
#endif /* A8302_COMPATIBLE */
#ifdef    A8304_COMPATIBLE
  STRING_APPEND_SAFE(lnbList,1000, " A8304"); i++;
#endif /* A8304_COMPATIBLE */
#ifdef    TPS65233_COMPATIBLE
  STRING_APPEND_SAFE(lnbList,1000, " TPS65233"); i++;
#endif /* TPS65233_COMPATIBLE */
  front_end = front_end; /* To avoid compiler warning if not used */
  lnbList   = lnbList;   /* To avoid compiler warning if not used */
  i         = i;         /* To avoid compiler warning if not used */
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_SAT_Select_LNB_Chip function
  Use:        LNB controller selection function
              Used to select the LNB controller chip
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  lnb_code, an int used to select the LNB Controller
  Parameter:  lnb_chip_address, an int used to select the LNB Controller's i2c address
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_Select_LNB_Chip        (SILABS_FE_Context *front_end,    signed   int lnb_code, signed   int lnb_chip_address)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_SAT_Select_LNB_Chip      (front_end, %d, 0x%02x);\n", lnb_code, lnb_chip_address);
  front_end->SAT_Select_LNB_Chip_lnb_code         = lnb_code;
  front_end->SAT_Select_LNB_Chip_lnb_chip_address = lnb_chip_address;
#ifdef    SATELLITE_FRONT_END
  front_end->lnb_chip = 0;
#ifdef    LNBH21_COMPATIBLE
  if (lnb_code               == 21      ) { front_end->lnb_chip = lnb_code; front_end->lnb_chip_address = lnb_chip_address; L0_SetAddress (front_end->lnbh21->i2c, lnb_chip_address, 1); }
#endif /* LNBH21_COMPATIBLE */
#ifdef    LNBH25_COMPATIBLE
  if (lnb_code               == 25      ) { front_end->lnb_chip = lnb_code; front_end->lnb_chip_address = lnb_chip_address; L0_SetAddress (front_end->lnbh25->i2c, lnb_chip_address, 1); }
#endif /* LNBH25_COMPATIBLE */
#ifdef    LNBH26_COMPATIBLE
  if (lnb_code               == 26      ) { front_end->lnb_chip = lnb_code; front_end->lnb_chip_address = lnb_chip_address; L0_SetAddress (front_end->lnbh26->i2c, lnb_chip_address, 1); }
#endif /* LNBH26_COMPATIBLE */
#ifdef    LNBH29_COMPATIBLE
  if (lnb_code               == 29      ) { front_end->lnb_chip = lnb_code; front_end->lnb_chip_address = lnb_chip_address; L0_SetAddress (front_end->lnbh29->i2c, lnb_chip_address, 1); }
#endif /* LNBH29_COMPATIBLE */
#ifdef    A8293_COMPATIBLE
  if (lnb_code               == 0xA8293 ) { front_end->lnb_chip = lnb_code; front_end->lnb_chip_address = lnb_chip_address; L0_SetAddress (front_end->A8293->i2c , lnb_chip_address, 1); }
#endif /* A8293_COMPATIBLE */
#ifdef    A8297_COMPATIBLE
  if (lnb_code               == 0xA8297 ) { front_end->lnb_chip = lnb_code; front_end->lnb_chip_address = lnb_chip_address; L0_SetAddress (front_end->A8297->i2c , lnb_chip_address, 1); }
#endif /* A8297_COMPATIBLE */
#ifdef    A8302_COMPATIBLE
  if (lnb_code               == 0xA8302 ) { front_end->lnb_chip = lnb_code; front_end->lnb_chip_address = lnb_chip_address; L0_SetAddress (front_end->A8302->i2c , lnb_chip_address, 1); }
#endif /* A8302_COMPATIBLE */
#ifdef    A8304_COMPATIBLE
  if (lnb_code               == 0xA8304 ) { front_end->lnb_chip = lnb_code; front_end->lnb_chip_address = lnb_chip_address; L0_SetAddress (front_end->A8304->i2c , lnb_chip_address, 1); }
#endif /* A8304_COMPATIBLE */
#ifdef    TPS65233_COMPATIBLE
  if (lnb_code               == 0x65233 ) { front_end->lnb_chip = lnb_code; front_end->lnb_chip_address = lnb_chip_address; L0_SetAddress (front_end->TPS65233->i2c , lnb_chip_address, 1); }
#endif /* TPS65233_COMPATIBLE */
  return front_end->lnb_chip;
#endif /* SATELLITE_FRONT_END */
#ifndef   SATELLITE_FRONT_END
  return 0;
#endif /* SATELLITE_FRONT_END */
}
/************************************************************************************************************************
  SiLabs_API_SAT_LNB_Chip_Index function
  Use:        LNB controller index setting function
              Used to select the LNB controller chip index, when using a dual part
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  lnb_code, an int used to select the LNB Controller
  Parameter:  lnb_chip_address, an int used to select the LNB Controller's i2c address
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_LNB_Chip_Index         (SILABS_FE_Context *front_end,    signed   int lnb_index)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_SAT_LNB_Chip_Index       (front_end, %d);\n", lnb_index);
  front_end->SAT_Select_LNB_Chip_lnb_index        = lnb_index;
#ifdef    LNBH26_COMPATIBLE
  if (front_end->lnb_chip ==      26) { if (lnb_index > 0) { front_end->lnbh26->a_b = 1; } else { front_end->lnbh26->a_b = 0;}; return 1; }
#endif /* LNBH26_COMPATIBLE */
#ifdef    A8297_COMPATIBLE
  if (front_end->lnb_chip == 0xA8297) {
    if (lnb_index == 0) { A8297_FE_0 = front_end; }
    if (lnb_index == 1) { A8297_FE_1 = front_end; L1_A8297_MatchBytes (A8297_FE_0->A8297, A8297_FE_1->A8297); }
    return L1_A8297_Index(front_end->A8297, lnb_index);
  }
#endif /* A8297_COMPATIBLE */
#ifdef    A8302_COMPATIBLE
  if (front_end->lnb_chip == 0xA8302) { return L1_A8302_Index(front_end->A8302, lnb_index  );}
#endif /* A8302_COMPATIBLE */
  return 0;
}
/* Front_end info, control and status functions                                          */
/************************************************************************************************************************
  SiLabs_API_Infos  function
  Use:        software information function
              Used to retrieve various information about the front-end code
  Parameter:  front_end, a pointer to the SILABS_FE_Context context to be initialized
  Parameter:  infoString, a text buffer to be filled with the information.
               It must be initialized by the caller with a minimal size of 1000.
  Return:     the length of the information string
************************************************************************************************************************/
signed   int  SiLabs_API_Infos                      (SILABS_FE_Context *front_end,    char *infoString)
{
  front_end = front_end; /* To avoid compiler warning */
  if (infoString       == NULL) return 0;
  if (Silabs_init_done ==    0) {
    snprintf(infoString,1000, "Call SiLabs_API_SW_Init first!\n");
  } else {
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    Si2183_L2_Infos  (front_end->Si2183_FE, infoString);
  }
#endif /* Si2183_COMPATIBLE */
  }
  STRING_APPEND_SAFE(infoString,1000, "Wrapper              Source code %s\n"   , SiLabs_API_TAG_TEXT() );
#ifdef    SATELLITE_FRONT_END
#ifdef    LNBH21_COMPATIBLE
  STRING_APPEND_SAFE(infoString,1000, "LNB CHIP             LNBH21 at 0x%02x\n" , front_end->lnbh21->i2c->address );
  STRING_APPEND_SAFE(infoString,1000, "LNB CHIP             Source code %s\n"   , L1_LNBH21_TAG_Text() );
#endif /* LNBH21_COMPATIBLE */
#ifdef    LNBH25_COMPATIBLE
  STRING_APPEND_SAFE(infoString,1000, "LNB POWER CHIP       LNBH25 at 0x%02x\n" , front_end->lnbh25->i2c->address );
  STRING_APPEND_SAFE(infoString,1000, "LNB POWER CHIP       Source code %s\n"   , L1_LNBH25_TAG_Text() );
#endif /* LNBH25_COMPATIBLE */
#ifdef    LNBH26_COMPATIBLE
  STRING_APPEND_SAFE(infoString,1000, "LNB POWER CHIP       LNBH26 at 0x%02x\n" , front_end->lnbh26->i2c->address );
  STRING_APPEND_SAFE(infoString,1000, "LNB POWER CHIP       Source code %s\n"   , L1_LNBH26_TAG_Text() );
#endif /* LNBH26_COMPATIBLE */
#ifdef    LNBH29_COMPATIBLE
  STRING_APPEND_SAFE(infoString,1000, "LNB POWER CHIP       LNBH29 at 0x%02x\n" , front_end->lnbh29->i2c->address );
  STRING_APPEND_SAFE(infoString,1000, "LNB POWER CHIP       Source code %s\n"   , L1_LNBH29_TAG_Text() );
#endif /* LNBH29_COMPATIBLE */
#ifdef    A8293_COMPATIBLE
  STRING_APPEND_SAFE(infoString,1000, "LNB POWER CHIP       A8293 at 0x%02x\n" , front_end->A8293->i2c->address );
  STRING_APPEND_SAFE(infoString,1000, "LNB POWER CHIP       Source code %s\n"   , L1_A8293_TAG_Text() );
#endif /* A8293_COMPATIBLE */
#ifdef    A8297_COMPATIBLE
  STRING_APPEND_SAFE(infoString,1000, "LNB POWER CHIP       A8297 at 0x%02x\n" , front_end->A8297->i2c->address );
  STRING_APPEND_SAFE(infoString,1000, "LNB POWER CHIP       Source code %s\n"   , L1_A8297_TAG_Text() );
#endif /* A8297_COMPATIBLE */
#ifdef    A8302_COMPATIBLE
  STRING_APPEND_SAFE(infoString,1000, "LNB POWER CHIP       A8302 at 0x%02x\n" , front_end->A8302->i2c->address );
  STRING_APPEND_SAFE(infoString,1000, "LNB POWER CHIP       Source code %s\n"   , L1_A8302_TAG_Text() );
#endif /* A8302_COMPATIBLE */
#ifdef    A8304_COMPATIBLE
  STRING_APPEND_SAFE(infoString,1000, "LNB POWER CHIP       A8304 at 0x%02x\n" , front_end->A8304->i2c->address );
  STRING_APPEND_SAFE(infoString,1000, "LNB POWER CHIP       Source code %s\n"   , L1_A8304_TAG_Text() );
#endif /* A8304_COMPATIBLE */
#ifdef    TPS65233_COMPATIBLE
  STRING_APPEND_SAFE(infoString,1000, "LNB POWER CHIP       TPS65233 at 0x%02x\n", front_end->TPS65233->i2c->address );
  STRING_APPEND_SAFE(infoString,1000, "LNB POWER CHIP       Source code %s\n"    , L1_TPS65233_TAG_Text() );
#endif /* TPS65233_COMPATIBLE */
#endif /* SATELLITE_FRONT_END */
  STRING_APPEND_SAFE(infoString,1000, "--------------------------------------\n");

  return (int)strlen(infoString);
}
/************************************************************************************************************************
  SiLabs_API_Config_Infos  function
  Use:        software configuration information function
              Used to retrieve information about the front-end configuration
  Parameter:  front_end, a pointer to the SILABS_FE_Context context to be initialized
  Parameter:  config_function, the name of the configuration function
  Parameter:  infoString, a text buffer to be filled with the information.
               It must be initialized by the caller with a minimal size of 1000.
  Return:     the length of the information string
************************************************************************************************************************/
signed   int  SiLabs_API_Config_Infos               (SILABS_FE_Context *front_end,    char* config_function, char *infoString)
{
  signed   int   match;
  char  tmp_info_string_buffer[1000];
  char *tmp_info_string;

  if (infoString       == NULL) return 0;
  if (Silabs_init_done ==    0) {
    snprintf(infoString,1000, "Call SiLabs_API_SW_Init first!\n");
    return (int)strlen(infoString);
  }
  match = 0;
  tmp_info_string = &(tmp_info_string_buffer[0]);
  snprintf(infoString,1000, " %-24s ("   , config_function);
  if (strcmp_nocase(config_function, "Frontend_Chip"           ) ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "0x%x"              , front_end->chip );
  }
  if (strcmp_nocase(config_function, "Demod_Address"           ) ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "0x%02x"            , front_end->demod_add );
  }
  if (strcmp_nocase(config_function, "SPI_Setup"               ) ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "%d, %d, %d, %d, %d", front_end->SPI_Setup_send_option, front_end->SPI_Setup_clk_pin, front_end->SPI_Setup_clk_pola, front_end->SPI_Setup_data_pin, front_end->SPI_Setup_data_order );
  }
  if (strcmp_nocase(config_function, "Select_TER_Tuner"        ) ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "0x%x, %d"          , front_end->Select_TER_Tuner_ter_tuner_code, front_end->Select_TER_Tuner_ter_tuner_index );
  }
  if (strcmp_nocase(config_function, "TER_tuner_I2C_connection") ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "%d"                , front_end->TER_tuner_I2C_connection );
  }
  if (strcmp_nocase(config_function, "TER_Address"             ) ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "0x%02x"            , front_end->TER_Address_add );
  }
  if (strcmp_nocase(config_function, "TER_Tuner_ClockConfig"   ) ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "%d, %d"            , front_end->TER_Tuner_ClockConfig_xtal, front_end->TER_Tuner_ClockConfig_xout );
  }
  if (strcmp_nocase(config_function, "TER_Clock"               ) ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "%d, %d, %d, %d"    , front_end->TER_Clock_clock_source, front_end->TER_Clock_clock_input, front_end->TER_Clock_clock_freq, front_end->TER_Clock_clock_control );
  }
  if (strcmp_nocase(config_function, "TER_FEF_Config"          ) ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "%d, %d, %d"        , front_end->TER_FEF_Config_fef_mode, front_end->TER_FEF_Config_fef_pin, front_end->TER_FEF_Config_fef_level );
  }
  if (strcmp_nocase(config_function, "TER_AGC"                 ) ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "0x%x, %d, 0x%x, %d", front_end->TER_AGC_agc1_mode, front_end->TER_AGC_agc1_inversion, front_end->TER_AGC_agc2_mode, front_end->TER_AGC_agc2_inversion );
  }
  if (strcmp_nocase(config_function, "TER_Tuner_AGC_Input"     ) ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "%d"                , front_end->TER_Tuner_AGC_Input_dtv_agc_source );
  }
  if (strcmp_nocase(config_function, "TER_Tuner_FEF_Input"     ) ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "%d"                , front_end->TER_Tuner_FEF_Input_dtv_fef_freeze_input );
  }
  if (strcmp_nocase(config_function, "TER_Tuner_IF_Output"     ) ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "%d"                , front_end->TER_Tuner_IF_Output_dtv_out_type );
  }
  if (strcmp_nocase(config_function, "Select_SAT_Tuner"        ) ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "0x%x, %d"          , front_end->Select_SAT_Tuner_sat_tuner_code, front_end->Select_SAT_Tuner_sat_tuner_index );
  }
  if (strcmp_nocase(config_function, "SAT_tuner_I2C_connection") ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "%d"                , front_end->SAT_tuner_I2C_connection );
  }
  if (strcmp_nocase(config_function, "SAT_Address"             ) ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "0x%02x"            , front_end->SAT_Address_add );
  }
  if (strcmp_nocase(config_function, "SAT_Clock"               ) ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "%d, %d, %d, %d"    , front_end->SAT_Clock_clock_source, front_end->SAT_Clock_clock_input, front_end->SAT_Clock_clock_freq, front_end->SAT_Clock_clock_control );
  }
  if (strcmp_nocase(config_function, "SAT_Spectrum"            ) ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "%d"                , front_end->SAT_Spectrum_spectrum_inversion );
  }
  if (strcmp_nocase(config_function, "SAT_AGC"                 ) ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "0x%x, %d, 0x%x, %d", front_end->SAT_AGC_agc1_mode, front_end->SAT_AGC_agc1_inversion, front_end->SAT_AGC_agc2_mode, front_end->SAT_AGC_agc2_inversion );
  }
  if (strcmp_nocase(config_function, "SAT_Select_LNB_Chip"     ) ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "%d, 0x%02x"        , front_end->SAT_Select_LNB_Chip_lnb_code, front_end->SAT_Select_LNB_Chip_lnb_chip_address );
  }
  if (strcmp_nocase(config_function, "Set_Index_and_Tag"       ) ==0) {
    match ++; STRING_APPEND_SAFE(infoString,1000, "%d, '%s'"        , front_end->fe_index, front_end->tag );
  }
  if (match) {
    STRING_APPEND_SAFE(infoString,1000, ");\n");
  } else {
    STRING_APPEND_SAFE(infoString,1000, "ERROR: unknown '%s' config_function !\n" , config_function);
  }
  if (strcmp_nocase(config_function, "Full"                    ) ==0) {
    snprintf(infoString,1000, "%s", "");
    SiLabs_API_Config_Infos (front_end, (char*)"Frontend_Chip"           , tmp_info_string ); STRING_APPEND_SAFE(infoString,1000, "%s", tmp_info_string );
    SiLabs_API_Config_Infos (front_end, (char*)"Demod_Address"           , tmp_info_string ); STRING_APPEND_SAFE(infoString,1000, "%s", tmp_info_string );
    SiLabs_API_Config_Infos (front_end, (char*)"SPI_Setup"               , tmp_info_string ); STRING_APPEND_SAFE(infoString,1000, "%s", tmp_info_string );
    SiLabs_API_Config_Infos (front_end, (char*)"Select_TER_Tuner"        , tmp_info_string ); STRING_APPEND_SAFE(infoString,1000, "%s", tmp_info_string );
    SiLabs_API_Config_Infos (front_end, (char*)"TER_tuner_I2C_connection", tmp_info_string ); STRING_APPEND_SAFE(infoString,1000, "%s", tmp_info_string );
    SiLabs_API_Config_Infos (front_end, (char*)"TER_Address"             , tmp_info_string ); STRING_APPEND_SAFE(infoString,1000, "%s", tmp_info_string );
    SiLabs_API_Config_Infos (front_end, (char*)"TER_Tuner_ClockConfig"   , tmp_info_string ); STRING_APPEND_SAFE(infoString,1000, "%s", tmp_info_string );
    SiLabs_API_Config_Infos (front_end, (char*)"TER_Clock"               , tmp_info_string ); STRING_APPEND_SAFE(infoString,1000, "%s", tmp_info_string );
    SiLabs_API_Config_Infos (front_end, (char*)"TER_FEF_Config"          , tmp_info_string ); STRING_APPEND_SAFE(infoString,1000, "%s", tmp_info_string );
    SiLabs_API_Config_Infos (front_end, (char*)"TER_AGC"                 , tmp_info_string ); STRING_APPEND_SAFE(infoString,1000, "%s", tmp_info_string );
    SiLabs_API_Config_Infos (front_end, (char*)"TER_Tuner_IF_Output"     , tmp_info_string ); STRING_APPEND_SAFE(infoString,1000, "%s", tmp_info_string );
    SiLabs_API_Config_Infos (front_end, (char*)"TER_Tuner_IF_Output"     , tmp_info_string ); STRING_APPEND_SAFE(infoString,1000, "%s", tmp_info_string );
    SiLabs_API_Config_Infos (front_end, (char*)"Select_SAT_Tuner"        , tmp_info_string ); STRING_APPEND_SAFE(infoString,1000, "%s", tmp_info_string );
    SiLabs_API_Config_Infos (front_end, (char*)"SAT_tuner_I2C_connection", tmp_info_string ); STRING_APPEND_SAFE(infoString,1000, "%s", tmp_info_string );
    SiLabs_API_Config_Infos (front_end, (char*)"SAT_Address"             , tmp_info_string ); STRING_APPEND_SAFE(infoString,1000, "%s", tmp_info_string );
    SiLabs_API_Config_Infos (front_end, (char*)"SAT_Clock"               , tmp_info_string ); STRING_APPEND_SAFE(infoString,1000, "%s", tmp_info_string );
    SiLabs_API_Config_Infos (front_end, (char*)"SAT_Spectrum"            , tmp_info_string ); STRING_APPEND_SAFE(infoString,1000, "%s", tmp_info_string );
    SiLabs_API_Config_Infos (front_end, (char*)"SAT_AGC"                 , tmp_info_string ); STRING_APPEND_SAFE(infoString,1000, "%s", tmp_info_string );
    SiLabs_API_Config_Infos (front_end, (char*)"SAT_Select_LNB_Chip"     , tmp_info_string ); STRING_APPEND_SAFE(infoString,1000, "%s", tmp_info_string );
    SiLabs_API_Config_Infos (front_end, (char*)"Set_Index_and_Tag"       , tmp_info_string ); STRING_APPEND_SAFE(infoString,1000, "%s", tmp_info_string );
    STRING_APPEND_SAFE(infoString,1000, "%s","\n");
  }
  return (int)strlen(infoString);
}
/************************************************************************************************************************
  SiLabs_API_HW_Connect function
  Use:        hardware connection function
              Used to connect the HW in the selected mode
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  connection_mode, the required mode
  Porting:    This function may be removed in the final application. It is useful during development to allow connection in various modes
************************************************************************************************************************/
signed   char  SiLabs_API_HW_Connect                (SILABS_FE_Context *front_end,    CONNECTION_TYPE connection_mode)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_HW_Connect           (front_end, %d);\n", connection_mode);
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { Si2183_L2_HW_Connect (front_end->Si2183_FE, connection_mode); }
#endif /* Si2183_COMPATIBLE */
  L0_Connect(WrapperI2C,    connection_mode);
#ifdef    SATELLITE_FRONT_END
#ifdef    UNICABLE_COMPATIBLE
/*  L0_Connect(front_end->unicable->i2c, connection_mode); */
#endif /* UNICABLE_COMPATIBLE */
#ifdef    LNBH21_COMPATIBLE
  if (front_end->lnb_chip == 21) { L0_Connect(front_end->lnbh21->i2c, connection_mode); }
#endif /* LNBH21_COMPATIBLE */
#ifdef    LNBH25_COMPATIBLE
  if (front_end->lnb_chip == 25) { L0_Connect(front_end->lnbh25->i2c, connection_mode); }
#endif /* LNBH25_COMPATIBLE */
#ifdef    LNBH26_COMPATIBLE
  if (front_end->lnb_chip == 26) { L0_Connect(front_end->lnbh26->i2c, connection_mode); }
#endif /* LNBH26_COMPATIBLE */
#ifdef    LNBH29_COMPATIBLE
  if (front_end->lnb_chip == 29) { L0_Connect(front_end->lnbh29->i2c, connection_mode); }
#endif /* LNBH29_COMPATIBLE */
#ifdef    A8293_COMPATIBLE
  if (front_end->lnb_chip == 0xA8293) { L0_Connect(front_end->A8293->i2c, connection_mode); }
#endif /* A8293_COMPATIBLE */
#ifdef    A8297_COMPATIBLE
  if (front_end->lnb_chip == 0xA8297) { L0_Connect(front_end->A8297->i2c, connection_mode); }
#endif /* A8297_COMPATIBLE */
#ifdef    A8302_COMPATIBLE
  if (front_end->lnb_chip == 0xA8302) { L0_Connect(front_end->A8302->i2c, connection_mode); }
#endif /* A8302_COMPATIBLE */
#ifdef    A8304_COMPATIBLE
  if (front_end->lnb_chip == 0xA8304) { L0_Connect(front_end->A8304->i2c, connection_mode); }
#endif /* A8304_COMPATIBLE */
#ifdef    TPS65233_COMPATIBLE
  if (front_end->lnb_chip == 0x65233) { L0_Connect(front_end->TPS65233->i2c, connection_mode); }
#endif /* TPS65233_COMPATIBLE */
#endif /* SATELLITE_FRONT_END */
  SiTRACE("SiLabs_API_HW_Connect in mode %d\n", connection_mode);
  return 1;
}
/************************************************************************************************************************
  SiLabs_API_ReadString function
  Use:        low-level i2c read function
              Used to easily read i2c bytes from the wrapper
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  readString, the string to be used
  Parameter:  pbtDataBuffer, a buffer to stor ethe read bytes
  Behavior:   Split the input string in tokens (separated by 'space') and read the corresponding bytes
              The chip address is the first byte
              The number of bytes to read is equal to the last token
              The index size if the number of tokens - 2
  Example:    'SiLabs_API_ReadString (front_end, "0xC8 0x12 0x34 5", pbtDataBuffer);' will read 5 bytes from the chip at address 0xc8 starting from index 0x1234
               0xC8 0x12 0x34  5
                |   ---------  |
                |       |      ----> 5 bytes to read
                |       -----------> index 0x1234 (on 2 bytes)
                -------------------> address = 0xc8
  Example:    'SiLabs_API_ReadString (front_end, "0xA0 0x00 5"     , pbtDataBuffer);' will read 5 bytes from the chip at address 0xA0 starting from index 0x00 (This will return the content of the Cypress eeprom)
  Example:    'SiLabs_API_ReadString (front_end, "0xC0 1"          , pbtDataBuffer);' will read 1 byte  from the chip at address 0xC0 (This will return the status byte for a command-mode chip)
  Returns:    The number of bytes written
************************************************************************************************************************/
signed   int  SiLabs_API_ReadString                 (SILABS_FE_Context *front_end,    char *readString, unsigned char *pbtDataBuffer)
{
  front_end = front_end; /* To avoid compiler warning */
  return L0_ReadString (WrapperI2C, readString, pbtDataBuffer);
}
/************************************************************************************************************************
  SiLabs_API_WriteString function
  Use:        low_level i2c write function
              Used to easily write bytes from the wrapper, based on a string input
  Behavior:   Split the input string in tokens (separated by 'space') and write the corresponding bytes
              The chip address is the first byte
              The number of bytes to write is equal to the number of tokens -1
  Example:    'SiLabs_API_WriteString (front_end, "0xC8 0x12 0x34 0x37");' will write '0x37' at index 0x1234 in the chip at address 0xc8
  Returns:    The number of bytes written
************************************************************************************************************************/
signed   char SiLabs_API_WriteString                (SILABS_FE_Context *front_end,    char *writeString)
{
  front_end = front_end; /* To avoid compiler warning */
  return L0_WriteString(WrapperI2C, writeString);
}
/************************************************************************************************************************
  SiLabs_API_bytes_trace function
  Use:        Byte-level tracing function
              Used to toggle the L0 traces
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  track_mode, the required trace mode
  Porting:    This function may be removed in the final application. It is useful during development to check i2c communication
  Returns:    The final track_mode
************************************************************************************************************************/
signed   char SiLabs_API_bytes_trace                (SILABS_FE_Context *front_end,    unsigned char track_mode)
{
  SiTRACE("API CALL TRACE: SiLabs_API_bytes_trace (front_end, %d);\n", track_mode);
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    front_end->Si2183_FE->demod->i2c->trackWrite     = track_mode;
    front_end->Si2183_FE->demod->i2c->trackRead      = track_mode;
#ifdef    TERRESTRIAL_FRONT_END
    front_end->Si2183_FE->tuner_ter->i2c->trackWrite = track_mode;
    front_end->Si2183_FE->tuner_ter->i2c->trackRead  = track_mode;
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
    front_end->Si2183_FE->tuner_sat->i2c->trackWrite = track_mode;
    front_end->Si2183_FE->tuner_sat->i2c->trackRead  = track_mode;
#endif /* SATELLITE_FRONT_END */
  }
#endif /* Si2183_COMPATIBLE */
  WrapperI2C->trackWrite     = track_mode;
  WrapperI2C->trackRead      = track_mode;
#ifdef    SATELLITE_FRONT_END
#ifdef    LNBH21_COMPATIBLE
  front_end->lnbh21->i2c->trackWrite = track_mode;
  front_end->lnbh21->i2c->trackRead  = track_mode;
#endif /* LNBH21_COMPATIBLE */
#ifdef    LNBH25_COMPATIBLE
  front_end->lnbh25->i2c->trackWrite = track_mode;
  front_end->lnbh25->i2c->trackRead  = track_mode;
#endif /* LNBH25_COMPATIBLE */
#ifdef    LNBH26_COMPATIBLE
  front_end->lnbh26->i2c->trackWrite = track_mode;
  front_end->lnbh26->i2c->trackRead  = track_mode;
#endif /* LNBH26_COMPATIBLE */
#ifdef    LNBH29_COMPATIBLE
  front_end->lnbh29->i2c->trackWrite = track_mode;
  front_end->lnbh29->i2c->trackRead  = track_mode;
#endif /* LNBH29_COMPATIBLE */
#ifdef    A8293_COMPATIBLE
  front_end->A8293->i2c->trackWrite = track_mode;
  front_end->A8293->i2c->trackRead  = track_mode;
#endif /* A8293_COMPATIBLE */
#ifdef    A8297_COMPATIBLE
  front_end->A8297->i2c->trackWrite = track_mode;
  front_end->A8297->i2c->trackRead  = track_mode;
#endif /* A8297_COMPATIBLE */
#ifdef    A8302_COMPATIBLE
  front_end->A8302->i2c->trackWrite = track_mode;
  front_end->A8302->i2c->trackRead  = track_mode;
#endif /* A8302_COMPATIBLE */
#ifdef    A8304_COMPATIBLE
  front_end->A8304->i2c->trackWrite = track_mode;
  front_end->A8304->i2c->trackRead  = track_mode;
#endif /* A8304_COMPATIBLE */
#ifdef    TPS65233_COMPATIBLE
  front_end->TPS65233->i2c->trackWrite = track_mode;
  front_end->TPS65233->i2c->trackRead  = track_mode;
#endif /* TPS65233_COMPATIBLE */
#endif /* SATELLITE_FRONT_END */
#ifdef    UNICABLE_COMPATIBLE
  front_end->unicable->i2c->trackWrite = track_mode;
  front_end->unicable->i2c->trackRead  = track_mode;
#endif /* UNICABLE_COMPATIBLE */
  return track_mode;
}
/************************************************************************************************************************
  SiLabs_API_communication_check function
  Use:      Communication check function
            Used to make sure all chips are connected
  Parameter: front_end a pointer to the front-end structure
  Return:    1 if sucessful, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_communication_check        (SILABS_FE_Context *front_end)
{
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return Si2183_L2_communication_check (front_end->Si2183_FE); }
#endif /* Si2183_COMPATIBLE */
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_switch_to_standard function
  Use:      Standard switching function selection
            Used to switch nicely to the wanted standard, taking into account the previous state
  Parameter: new_standard the wanted standard to switch to
  Return:    1 if sucessful, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_switch_to_standard         (SILABS_FE_Context *front_end,    signed   int  standard, unsigned char force_full_init)
{
  front_end->init_ok = 0;
  SiTRACE("API CALL LOCK  : SiLabs_API_switch_to_standard standard %d, force_full_init %d);\n", standard, force_full_init);
  SiTRACE("Wrapper switching to %s\n", Silabs_Standard_Text(standard) );
  SiTRACE("SiLabs_API_switch_to_standard config_code 0x%06x\n", front_end->config_code);
  if (FRONT_END_COUNT > 1) {
    if (Silabs_multiple_front_end_init_done == 0) {
      SiTRACE("SiLabs_API_switch_to_standard calling SiLabs_API_Demods_Kickstart to enable the clocks (only for multiple frontends)\n");
      Silabs_multiple_front_end_init_done = SiLabs_API_Demods_Kickstart ();
  #ifdef    SILABS_TER_TUNER_API
    /*  SiLabs_API_TER_Tuners_Kickstart (); */
  #endif /* SILABS_TER_TUNER_API */
    }
  }
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { front_end->init_ok = Si2183_L2_switch_to_standard (front_end->Si2183_FE , Silabs_standardCode(front_end, standard), force_full_init);}
#endif /* Si2183_COMPATIBLE */
  if (front_end->init_ok == 0) {
    SiTRACE("Problem switching to %s\n", Silabs_Standard_Text(standard));
  } else {
    front_end->standard = standard;
  }
  return front_end->init_ok;
}
/************************************************************************************************************************
  SiLabs_API_set_standard function
  Use:      Standard switching function selection
            Used to change the current standard only
  Behavior:  WARNING: use with caution, this is only used for SAT, where the demod can lock in S2 when set to S (and vice-versa)!
  Parameter: new_standard the wanted standard to switch to
  Return:    1 if sucessful, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_set_standard               (SILABS_FE_Context *front_end,    signed   int  standard)
{
  SiTRACE("API CALL LOCK  : SiLabs_API_set_standard standard %d);\n", standard);
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { if (Si2183_L2_switch_to_standard (front_end->Si2183_FE,        Silabs_standardCode(front_end, (CUSTOM_Standard_Enum)standard), 0)) { front_end->standard = standard; return 1;} }
#endif /* Si2183_COMPATIBLE */
  SiTRACE("Problem switching to %s\n", Silabs_Standard_Text(standard));
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_lock_to_carrier function
  Use:      relocking function
            Used to relock on a channel for the required standard
  Parameter: standard the standard to lock to
  Parameter: freq                the frequency to lock to    (in Hz for TER, in kHz for SAT)
  Parameter: bandwidth_Hz        the channel bandwidth in Hz (only for DVB-T, DVB-T2, ISDB-T)
  Parameter: dvb_t_stream        the HP/LP stream            (only for DVB-T)
  Parameter: symbol_rate_bps     the symbol rate in baud/s   (for DVB-C, MCNS and SAT)
  Parameter: dvb_c_constellation the DVB-C constellation     (only for DVB-C)
  Parameter: data_slice_id       the DATA SLICE Id           (only for DVB-C2 when num_dslice  > 1)
  Parameter: plp_id              the PLP Id                  (only for DVB-T2 and DVB-C2 when num_plp > 1)
  Parameter: T2_lock_mode        the DVB-T2 lock mode        (0='ANY', 1='T2-Base', 2='T2-Lite')
  Return:    1 if locked, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_lock_to_carrier            (SILABS_FE_Context *front_end,    signed   int  standard, signed   int freq, signed   int bandwidth_Hz, unsigned int  stream, unsigned int symbol_rate_bps, unsigned int  constellation, unsigned int  polarization, unsigned int  band, signed   int data_slice_id, signed   int plp_id, unsigned int  T2_lock_mode)
{
  signed   int standard_code;
  signed   int return_value;
#ifdef    DEMOD_DVB_C
  signed   int constel_code;
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_T
  signed   int stream_code;
#endif /* DEMOD_DVB_T */
#ifdef    SATELLITE_FRONT_END
  signed   int voltage;
  signed   int tone;
#endif /* SATELLITE_FRONT_END */
  data_slice_id = data_slice_id; /* to avoid compiler warning if not used */
  plp_id        = plp_id;        /* to avoid compiler warning if not used */

  SiTRACE("API CALL LOCK  : SiLabs_API_lock_to_carrier (front_end, %8d, %d, %d, %2d, %9d, %8d, %10d, %4d, %4d, %4d, %4d);\n", standard, freq, bandwidth_Hz, stream, symbol_rate_bps, constellation, polarization, band, data_slice_id, plp_id, T2_lock_mode);
  SiTRACE("SiLabs_API_lock_to_carrier config_code 0x%06x\n", front_end->config_code);

  standard_code = Silabs_standardCode(front_end, standard);
#ifdef    DEMOD_DVB_C
  constel_code  = Silabs_constelCode (front_end, (CUSTOM_Constel_Enum)constellation);
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_T
  stream_code   = Silabs_streamCode  (front_end, (CUSTOM_Stream_Enum)stream);
#endif /* DEMOD_DVB_T */

  SiTRACE("SiLabs_API_lock_to_carrier (front_end, %8s, %d, %d, %2s, %9d, %8s, %10s, %4s, %4d, %4d, %4d)\n", Silabs_Standard_Text(standard), freq, bandwidth_Hz, Silabs_Stream_Text(stream), symbol_rate_bps, Silabs_Constel_Text(constellation), Silabs_Polarization_Text(polarization), Silabs_Band_Text(band), data_slice_id , plp_id , T2_lock_mode);
  SiTRACE("SiLabs_API_lock_to_carrier (front_end, standard %8s, freq %d, bandwidth_Hz %d, stream %2s, symbol_rate_bps %9d, constellation %8s, polarization %10s, band %4s, data_slice_id %4d, plp_id %4d, T2_lock_mode %4d)\n",
          Silabs_Standard_Text(standard), freq, bandwidth_Hz, Silabs_Stream_Text(stream), symbol_rate_bps, Silabs_Constel_Text(constellation), Silabs_Polarization_Text(polarization), Silabs_Band_Text(band), data_slice_id, plp_id, T2_lock_mode );

  /* Use the API wrapper function to switch standard if required. */
  if (standard != front_end->standard) {
    if (SiLabs_API_switch_to_standard(front_end, standard, 0) == 0) {
      return 0;
    }
  }
  if ( (standard == SILABS_SLEEP) || (standard == SILABS_ANALOG) ) {
    SiTRACE("SiLabs_API_lock_to_carrier %10s: nothing more to do, returning 1\n", Silabs_Standard_Text(standard) );
    return 1;
  }
#ifdef    SATELLITE_FRONT_END
  /* FOR SAT, control LNB voltage and tone before setting the demod */
  switch (standard) {
    case SILABS_DVB_S  :
    case SILABS_DVB_S2 :
    case SILABS_DSS    : {
      voltage = 0;
      tone    = 0;
      SiTRACE("%s %s\n", Silabs_Polarization_Text((CUSTOM_Polarization_Enum)polarization) ,Silabs_Band_Text((CUSTOM_Band_Enum)band) );
      front_end->polarization = polarization;
      front_end->band         = band;
#ifdef    UNICABLE_COMPATIBLE
      if (front_end->unicable->installed) {
        if (polarization == SILABS_POLARIZATION_HORIZONTAL) { front_end->unicable->polarization = UNICABLE_HORIZONTAL; }
        if (polarization == SILABS_POLARIZATION_VERTICAL  ) { front_end->unicable->polarization = UNICABLE_VERTICAL  ; }
        if (band         == SILABS_BAND_LOW               ) { front_end->unicable->band         = UNICABLE_LOW_BAND  ; }
        if (band         == SILABS_BAND_HIGH              ) { front_end->unicable->band         = UNICABLE_HIGH_BAND ; }
      } else {
#endif /* UNICABLE_COMPATIBLE */
      if (polarization == SILABS_POLARIZATION_HORIZONTAL) { voltage = 18; }
      if (polarization == SILABS_POLARIZATION_VERTICAL  ) { voltage = 13; }
      if (polarization != SILABS_POLARIZATION_DO_NOT_CHANGE ) {
        SiLabs_API_SAT_Tuner_I2C_Enable  (front_end);
        SiLabs_API_SAT_voltage           (front_end, voltage);
        SiLabs_API_SAT_Tuner_I2C_Disable (front_end);
      }
      if (band         == SILABS_BAND_LOW  ) { tone    =  0; }
      if (band         == SILABS_BAND_HIGH ) { tone    =  1; }
      if (band         != SILABS_BAND_DO_NOT_CHANGE         ) { SiLabs_API_SAT_tone    (front_end, tone); }
#ifdef    UNICABLE_COMPATIBLE
      }
#endif /* UNICABLE_COMPATIBLE */
      break;
    }
    default            : { break; }
  }
#endif /* SATELLITE_FRONT_END */

#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    return_value = Si2183_L2_lock_to_carrier  (front_end->Si2183_FE, standard_code, freq
                                  , bandwidth_Hz
#ifdef    DEMOD_DVB_T
                                  , stream_code
#endif /* DEMOD_DVB_T */
                                  , symbol_rate_bps
#ifdef    DEMOD_DVB_C
                                  , constel_code
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_C2
                                  , data_slice_id
#endif /* DEMOD_DVB_C2 */
                                  , plp_id
#ifdef    DEMOD_DVB_T2
                                  , T2_lock_mode
#endif /* DEMOD_DVB_T2 */
                                    );
    if (return_value == 1) { SiLabs_API_Reset_Uncorrs(front_end); }
    return return_value;
  }
#endif /* Si2183_COMPATIBLE */
  SiTRACE("Unknown chip '%d'\n", front_end->chip);
  SiERROR("SiLabs_API_lock_to_carrier Unknown chip\n");
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_Tune function
  Use:      tuning function
            Used to tune on a channel for the current standard
  Parameter: freq                the frequency to lock to (in Hz for TER, in kHz for SAT)
  Return:    the tuned freq, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_Tune                       (SILABS_FE_Context *front_end,    signed   int freq)
{
  SiTRACE("API CALL LOCK  : SiLabs_API_Tune (front_end, %10d);\n", freq);
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    return   Si2183_L2_Tune  (front_end->Si2183_FE, freq );
  }
#endif /* Si2183_COMPATIBLE */
  SiTRACE("Unknown chip '%d'\n", front_end->chip);
  SiERROR("SiLabs_API_Tune Unknown chip\n");
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_Demod_Standby function
  Use:      Demodulator standby function
            Used to switch the demodulator in standby mode
  Parameter: front_end, a pointer to the front End
  Returns:    1 if successful, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_Demod_Standby              (SILABS_FE_Context *front_end)
{
  SiTRACE("API CALL LOCK  : SiLabs_API_Demod_Standby (front_end);\n");
  front_end = front_end; /* To avoid compiler warning */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { Si2183_STANDBY       (front_end->Si2183_FE->demod); return 1; }
#endif /* Si2183_COMPATIBLE */
  SiTRACE("Problem switching %d in standby mode\n", front_end->chip);
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_Demod_Silent function
  Use:      Demodulator Silent function
            Used to switch the demodulator in Silent mode
  Parameter: front_end, a pointer to the front End
  Returns:    1 if successful, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_Demod_Silent               (SILABS_FE_Context *front_end,    signed   int silent)
{
  SiTRACE("API CALL LOCK  : SiLabs_API_Demod_Silent (front_end, %d);\n", silent);
  front_end = front_end; /* To avoid compiler warning */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { Si2183_L2_SILENT (front_end->Si2183_FE, silent); return 1; }
#endif /* Si2183_COMPATIBLE */
  SiTRACE("Problem switching %d in Silent mode\n", front_end->chip);
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_Demod_ClockOn function
  Use:      Demodulator clock activation function
            Used to switch the demodulator clock on
  Parameter: front_end, a pointer to the front End
  Returns:    1 if successful, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_Demod_ClockOn              (SILABS_FE_Context *front_end)
{
  SiTRACE("API CALL LOCK  : SiLabs_API_Demod_ClockOn (front_end);\n");
  front_end = front_end; /* To avoid compiler warning */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return 1; }
#endif /* Si2183_COMPATIBLE */
  SiTRACE("Problem switching %d Clock On\n", front_end->chip);
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_Reset_Uncorrs function
  Use:      uncorrectable packets counter reset function
            Used to reset the uncor counter
  Parameter: front_end, a pointer to the front End
  Returns:    1 if successful, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_Reset_Uncorrs              (SILABS_FE_Context *front_end)
{
  SiTRACE("API CALL LOCK  : SiLabs_API_Reset_Uncorrs (front_end);\n");
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { Si2183_L1_DD_UNCOR (front_end->Si2183_FE->demod, Si2183_DD_UNCOR_CMD_RST_CLEAR); return 1;}
#endif /* Si2183_COMPATIBLE */
  SiTRACE("Problem resetting %d uncorrs\n", front_end->chip);
  return -1;
}
/************************************************************************************************************************
  SiLabs_API_TS_Strength_Shape function
  Use:      Transport Stream current configuration function
            Used to set the TS strength and shape values from L3 level.
  Parameter: serial_strength:     0 to 15:applied value            otherwise:NO change
  Parameter: serial_shape:        0 to  3:applied value            otherwise:NO change
  Parameter: parallel_strength:   0 to 15:applied value            otherwise:NO change
  Parameter: parallel_shape:      0 to  3:applied value            otherwise:NO change
************************************************************************************************************************/
signed   int  SiLabs_API_TS_Strength_Shape          (SILABS_FE_Context *front_end,    signed   int serial_strength, signed   int serial_shape, signed   int parallel_strength, signed   int parallel_shape)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_TS_Strength_Shape (front_end, %d, %d, %d, %d);\n", serial_strength, serial_shape, parallel_strength, parallel_shape);
  SiTRACE("SiLabs_API_TS_Strength_Shape serial_strength %d, serial_shape %d, parallel_strength %d, parallel_shape %d\n", serial_strength, serial_shape, parallel_strength, parallel_shape);
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    if (serial_strength   <= 15)  { front_end->Si2183_FE->demod->prop->dd_ts_setup_ser.ts_data_strength     = serial_strength;
                                    front_end->Si2183_FE->demod->prop->dd_ts_setup_ser.ts_clk_strength      = serial_strength;
#ifdef    Si2183_DD_SEC_TS_SETUP_SER_PROP
                                    front_end->Si2183_FE->demod->prop->dd_sec_ts_setup_ser.ts_data_strength = serial_strength;
                                    front_end->Si2183_FE->demod->prop->dd_sec_ts_setup_ser.ts_clk_strength  = serial_strength;
#endif /* Si2183_DD_SEC_TS_SETUP_SER_PROP */
                                }
    if (serial_shape      <= 3 )  { front_end->Si2183_FE->demod->prop->dd_ts_setup_ser.ts_data_shape        = serial_shape;
                                    front_end->Si2183_FE->demod->prop->dd_ts_setup_ser.ts_clk_shape         = serial_shape;
#ifdef    Si2183_DD_SEC_TS_SETUP_SER_PROP
                                    front_end->Si2183_FE->demod->prop->dd_sec_ts_setup_ser.ts_data_shape    = serial_shape;
                                    front_end->Si2183_FE->demod->prop->dd_sec_ts_setup_ser.ts_clk_shape     = serial_shape;
#endif /* Si2183_DD_SEC_TS_SETUP_SER_PROP */
                                }

    if (parallel_strength <= 15)  { front_end->Si2183_FE->demod->prop->dd_ts_setup_par.ts_data_strength     = parallel_strength;
                                    front_end->Si2183_FE->demod->prop->dd_ts_setup_par.ts_clk_strength      = parallel_strength;
#ifdef    Si2183_DD_SEC_TS_SETUP_PAR_PROP
                                    front_end->Si2183_FE->demod->prop->dd_sec_ts_setup_par.ts_data_strength = parallel_strength;
                                    front_end->Si2183_FE->demod->prop->dd_sec_ts_setup_par.ts_clk_strength  = parallel_strength;
#endif /* Si2183_DD_SEC_TS_SETUP_PAR_PROP */
                                }
    if (parallel_shape    <= 3 )  { front_end->Si2183_FE->demod->prop->dd_ts_setup_par.ts_data_shape        = parallel_shape;
                                    front_end->Si2183_FE->demod->prop->dd_ts_setup_par.ts_clk_shape         = parallel_shape;
#ifdef    Si2183_DD_SEC_TS_SETUP_PAR_PROP
                                    front_end->Si2183_FE->demod->prop->dd_sec_ts_setup_par.ts_data_shape    = parallel_shape;
                                    front_end->Si2183_FE->demod->prop->dd_sec_ts_setup_par.ts_clk_shape     = parallel_shape;
#endif /* Si2183_DD_SEC_TS_SETUP_PAR_PROP */
                                }

    if (front_end->Si2183_FE->first_init_done ) {
      Si2183_L1_SetProperty2( front_end->Si2183_FE->demod, Si2183_DD_TS_SETUP_SER_PROP_CODE     );
#ifdef    Si2183_DD_SEC_TS_SETUP_SER_PROP
      if (front_end->Si2183_FE->demod->rsp->get_rev.mcm_die != Si2183_GET_REV_RESPONSE_MCM_DIE_SINGLE) {
        Si2183_L1_SetProperty2( front_end->Si2183_FE->demod, Si2183_DD_SEC_TS_SETUP_SER_PROP_CODE );   }
#endif /* Si2183_DD_SEC_TS_SETUP_SER_PROP */
      Si2183_L1_SetProperty2( front_end->Si2183_FE->demod, Si2183_DD_TS_SETUP_PAR_PROP_CODE     );
#ifdef    Si2183_DD_SEC_TS_SETUP_PAR_PROP
      if (front_end->Si2183_FE->demod->rsp->get_rev.mcm_die != Si2183_GET_REV_RESPONSE_MCM_DIE_SINGLE) {
        Si2183_L1_SetProperty2( front_end->Si2183_FE->demod, Si2183_DD_SEC_TS_SETUP_PAR_PROP_CODE );   }
#endif /* Si2183_DD_SEC_TS_SETUP_PAR_PROP */
    }
    return 1;
  }
#endif /* Si2183_COMPATIBLE */
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_TS_Config function
  Use:      Transport Stream configuration function
            Used to set the TS settings in the desired mode
  Parameter: clock_config:     0:AUTO_ADAPT              1:AUTO_FIXED           otherwise:MANUAL set to clock (in kHz unit)
  Parameter: gapped:           0:Constant clock                          1:gapped clock                       otherwise:NO change
  Parameter: serial_clk_inv:   0:TS serial clock signal non-inverted     1:TS serial clock signal inverted    otherwise:NO change
  Parameter: parallel_clk_inv: 0:TS parallel clock signal non-inverted   1:TS parallel clock signal inverted  otherwise:NO change
  Parameter: ts_err_inv:       0:TS error signal non-inverted            1:TS error signal inverted           otherwise:NO change
  Parameter: serial_pin:         output pin for serial TS (from 0 to 7) otherwise:NO change
************************************************************************************************************************/
signed   int  SiLabs_API_TS_Config                  (SILABS_FE_Context *front_end,    signed   int clock_config, signed   int gapped, signed   int serial_clk_inv, signed   int parallel_clk_inv, signed   int ts_err_inv, signed   int serial_pin)
{
  SiTRACE("API CALL CONFIG: SiLabs_API_TS_Config (front_end, %d, %d, %d, %d, %d, %d);\n", clock_config, gapped, serial_clk_inv, parallel_clk_inv, ts_err_inv, serial_pin);
  SiTRACE("SiLabs_API_TS_Config clock_config %d, gapped %d, serial_clk_inv %d, parallel_clk_inv %d, ts_err_inv %d, serial_pin %d\n", clock_config, gapped, serial_clk_inv, parallel_clk_inv, ts_err_inv, serial_pin);
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
         if (clock_config == 0)     { front_end->Si2183_FE->demod->prop->dd_ts_mode.clock                = Si2183_DD_TS_MODE_PROP_CLOCK_AUTO_ADAPT; }
    else if (clock_config == 1)     { front_end->Si2183_FE->demod->prop->dd_ts_mode.clock                = Si2183_DD_TS_MODE_PROP_CLOCK_AUTO_FIXED; }
    else                            { front_end->Si2183_FE->demod->prop->dd_ts_mode.clock                = Si2183_DD_TS_MODE_PROP_CLOCK_MANUAL;
                                      front_end->Si2183_FE->demod->prop->dd_ts_freq.req_freq_10khz       = clock_config/10;                         }

         if (gapped == 1)           { front_end->Si2183_FE->demod->prop->dd_ts_mode.clk_gapped_en        = Si2183_DD_TS_MODE_PROP_CLK_GAPPED_EN_ENABLED  ; }
    else if (gapped == 0)           { front_end->Si2183_FE->demod->prop->dd_ts_mode.clk_gapped_en        = Si2183_DD_TS_MODE_PROP_CLK_GAPPED_EN_DISABLED ; }

         if (serial_clk_inv == 1)   { front_end->Si2183_FE->demod->prop->dd_ts_setup_ser.ts_clk_invert   = Si2183_DD_TS_SETUP_SER_PROP_TS_CLK_INVERT_INVERTED    ; }
    else if (serial_clk_inv == 0)   { front_end->Si2183_FE->demod->prop->dd_ts_setup_ser.ts_clk_invert   = Si2183_DD_TS_SETUP_SER_PROP_TS_CLK_INVERT_NOT_INVERTED; }

         if (parallel_clk_inv == 1) { front_end->Si2183_FE->demod->prop->dd_ts_setup_par.ts_clk_invert   = Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_INVERT_INVERTED    ; }
    else if (parallel_clk_inv == 0) { front_end->Si2183_FE->demod->prop->dd_ts_setup_par.ts_clk_invert   = Si2183_DD_TS_SETUP_PAR_PROP_TS_CLK_INVERT_NOT_INVERTED; }

         if (ts_err_inv == 1)       { front_end->Si2183_FE->demod->prop->dd_ts_mode.ts_err_polarity      = Si2183_DD_TS_MODE_PROP_TS_ERR_POLARITY_INVERTED     ; }
    else if (ts_err_inv == 0)       { front_end->Si2183_FE->demod->prop->dd_ts_mode.ts_err_polarity      = Si2183_DD_TS_MODE_PROP_TS_ERR_POLARITY_NOT_INVERTED ; }

    if (serial_pin < 8)             { front_end->Si2183_FE->demod->prop->dd_ts_mode.serial_pin_selection = serial_pin; }

    if (front_end->Si2183_FE->first_init_done ) {
      Si2183_L1_SetProperty2( front_end->Si2183_FE->demod, Si2183_DD_TS_FREQ_PROP_CODE      );
      Si2183_L1_SetProperty2( front_end->Si2183_FE->demod, Si2183_DD_TS_MODE_PROP_CODE      );
      Si2183_L1_SetProperty2( front_end->Si2183_FE->demod, Si2183_DD_TS_SETUP_SER_PROP_CODE );
      Si2183_L1_SetProperty2( front_end->Si2183_FE->demod, Si2183_DD_TS_SETUP_PAR_PROP_CODE );
    }
    return 1;
  }
#endif /* Si2183_COMPATIBLE */
  return 0;
}
/************************************************************************************************************************
  SiLabs_API_TS_Mode function
  Use:      Transport Stream control function
            Used to switch the TS output in the desired mode
  Parameter: mode the mode to switch to
************************************************************************************************************************/
signed   int  SiLabs_API_TS_Mode                    (SILABS_FE_Context *front_end,  unsigned   int ts_mode)
{
  signed   int valid_mode;
#ifdef    USB_Capability
  signed   int  streaming_used;
  signed   int  streaming_needed;
  double        retdval;
  char rettxtBuffer[256];
  char *rettxt;
  rettxt = rettxtBuffer;
#endif /* USB_Capability */
  SiTRACE("API CALL LOCK  : SiLabs_API_TS_Mode (front_end, %d);\n", ts_mode);
  valid_mode = 0;
#ifdef    USB_Capability
    switch (front_end->active_TS_mode) {
      case SILABS_TS_SERIAL    :
      case SILABS_TS_PARALLEL  :
      case SILABS_TS_TRISTATE  :
      case SILABS_TS_OFF       :
      default                  : { streaming_used   = 0; break ;}
      case SILABS_TS_GPIF      :
      case SILABS_TS_SLAVE_FIFO:
      case SILABS_TS_STREAMING : { streaming_used   = 1; break ;}
    }
    switch (ts_mode) {
      case SILABS_TS_SERIAL    :
      case SILABS_TS_PARALLEL  :
      case SILABS_TS_TRISTATE  :
      case SILABS_TS_OFF       :
      default                  : { streaming_needed = 0; break ;}
      case SILABS_TS_GPIF      :
      case SILABS_TS_SLAVE_FIFO:
      case SILABS_TS_STREAMING : { streaming_needed = 1; break ;}
    }
    if ( (streaming_used == 1) && (streaming_needed == 0) ) {
      /* First go to tristate when changing between a mode using the cypress chip and any other mode */
      if ( (ts_mode != front_end->active_TS_mode) && (ts_mode != SILABS_TS_TRISTATE) ) {
        SiLabs_API_TS_Mode (front_end, SILABS_TS_TRISTATE);
        front_end->active_TS_mode =    SILABS_TS_TRISTATE;
        streaming_used = 0;
      }
    }
#endif /* USB_Capability */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    switch (ts_mode) {
      case SILABS_TS_SERIAL  : { front_end->Si2183_FE->demod->prop->dd_ts_mode.mode = Si2183_DD_TS_MODE_PROP_MODE_SERIAL  ; break; }
      case SILABS_TS_PARALLEL: { front_end->Si2183_FE->demod->prop->dd_ts_mode.mode = Si2183_DD_TS_MODE_PROP_MODE_PARALLEL;
#ifdef    USB_Capability
                                  SiLabs_API_TS_Strength_Shape ( front_end, 100, 100, 2, 2);
                                  L0_Cypress_Process ("initdata", "gpifctlcfg", 128.0, &retdval, &rettxt); /* On SiLabs EVBs, turn Cypress CTL pins tristate */
#endif /* USB_Capability */
                                 break; }
      case SILABS_TS_TRISTATE: { front_end->Si2183_FE->demod->prop->dd_ts_mode.mode = Si2183_DD_TS_MODE_PROP_MODE_TRISTATE; break; }
      case SILABS_TS_OFF     : { front_end->Si2183_FE->demod->prop->dd_ts_mode.mode = Si2183_DD_TS_MODE_PROP_MODE_OFF;      break; }
#ifdef    USB_Capability
      /* With the cypress fw_version 15.52 and dll_version 15.52 the only transition which will fail
       is going from 'GPIF' on one frontend to 'GPIF' on another frontend. It's required to set the
       active TS in TRISTATE first at application level                                              */
      case SILABS_TS_STREAMING: { break; }
      case SILABS_TS_GPIF    :  { SiLabs_API_TS_Strength_Shape ( front_end, 100, 100, 2, 3);
        if (front_end->Si2183_FE->demod->rsp->get_rev.mcm_die == Si2183_GET_REV_RESPONSE_MCM_DIE_DIE_A) {
          Si2183_L1_DD_SET_REG   ( front_end->Si2183_FE->demod, 33, 147, 1, 0);
        }
        if (front_end->Si2183_FE->demod->rsp->get_rev.mcm_die == Si2183_GET_REV_RESPONSE_MCM_DIE_DIE_B) {
          Si2183_L1_DD_SET_REG   ( front_end->Si2183_FE->demod, 33, 147, 1, 1);
        }
                                 front_end->Si2183_FE->demod->prop->dd_ts_mode.mode = Si2183_DD_TS_MODE_PROP_MODE_GPIF    ;
/*      SiLabs_API_TS_Config   ( front_end, clock_config, gapped, serial_clk_inv, parallel_clk_inv, ts_err_inv, serial_pin); */
        SiLabs_API_TS_Config   ( front_end,            0,      0,              2,                2,          0,          8);
        break;
      }
      case SILABS_TS_SLAVE_FIFO:{ SiLabs_API_TS_Strength_Shape ( front_end, 100, 100, 5, 3);
/*      SiLabs_API_TS_Config   ( front_end, clock_config, gapped, serial_clk_inv, parallel_clk_inv, ts_err_inv, serial_pin); */
        SiLabs_API_TS_Config   ( front_end,        20000,      0,              2,                1,          0,          8);
                                 front_end->Si2183_FE->demod->prop->dd_ts_mode.mode  = Si2183_DD_TS_MODE_PROP_MODE_PARALLEL; break; }
#endif /* USB_Capability */
      default                : { return SiLabs_API_TS_Mode(front_end, SILABS_TS_TRISTATE)                                 ; break; }
    }
    Si2183_L1_SetProperty2(front_end->Si2183_FE->demod, Si2183_DD_TS_MODE_PROP_CODE);
    valid_mode = 1;
  }
#endif /* Si2183_COMPATIBLE */
  if (valid_mode) {
#ifdef    USB_Capability
    if ( (streaming_used == 1) && (streaming_needed == 0) ) {
      SiTRACE ("TS stop\n");
      L0_Cypress_Process  ("ts"                      ,"stop"    ,    0,                   &retdval, &rettxt); /* Starting Cypress TS transfer over USB */
    }
    if (ts_mode == SILABS_TS_GPIF       ) {
      L0_Cypress_Process  ("write_io_port"           ,"a"   , 0x08,                       &retdval, &rettxt); /* Select PA0 = 0, PA3 = 1 : GPIF ON     */
    } else {
      L0_Cypress_Process  ("write_io_port"           ,"a"   , 0x09,                       &retdval, &rettxt); /* Select PA0 = 1, PA3 = 1 : GPIF OFF    */
    }
    if ((ts_mode == SILABS_TS_GPIF ) | (ts_mode == SILABS_TS_SLAVE_FIFO )) {
      L0_Cypress_Process  ("write_io_port"           ,"d"   , front_end->ts_mux_input,    &retdval, &rettxt); /* Select input of Mux for GPIF          */
    } else {
      L0_Cypress_Process  ("write_io_port"           ,"d"   , SILABS_TS_MUX_TRISTATE ,    &retdval, &rettxt); /* Select no input of Mux                */
    }
    L0_Cypress_Process  ("output_enable_io_port"     ,"a"   , 0x09,                       &retdval, &rettxt); /* Enabling port A pins PA0/PA3          */
    L0_Cypress_Process  ("output_enable_io_port"     ,"d"   , 0x0C,                       &retdval, &rettxt); /* Enabling port D pins PD3/PD2          */

    SiTRACE ("TS over USB streaming %d -> %d\n", streaming_used, streaming_needed);
    if ( (streaming_used == 1) && (streaming_needed == 0) ) {
      if (front_end->active_TS_mode == SILABS_TS_GPIF      ) {
        SiTRACE ("GPIF OFF\n");
        L0_Cypress_Configure("-gpif"                 ,"off"     ,    0,                   &retdval, &rettxt); /* Starting Cypress gpif state machine   */
      }
      if (front_end->active_TS_mode == SILABS_TS_SLAVE_FIFO) {
        SiTRACE ("TS_SLAVE OFF\n");
        L0_Cypress_Configure("-ts_slave"             ,"off"     ,    0,                   &retdval, &rettxt); /* Starting Cypress gpif state machine   */
      }
    }
    if ( (streaming_used == 0) && (streaming_needed == 1) ) {
      if (ts_mode == SILABS_TS_GPIF      ) {
        L0_Cypress_Configure("-gpif"                 ,"on"      ,    0,                   &retdval, &rettxt); /* Starting Cypress gpif state machine   */
        L0_Cypress_Configure("-gpif_clk"             ,"on"      ,    0,                   &retdval, &rettxt); /* Starting Cypress gpif clock           */
      }
      if (ts_mode == SILABS_TS_SLAVE_FIFO) {
        L0_Cypress_Configure("-ts_slave"             ,"on"      ,    0,                   &retdval, &rettxt); /* Starting Cypress ts slave fifo mode   */
      }
      SiTRACE ("TS START\n");
      L0_Cypress_Process  ("ts"                      ,"start"   ,    0,                   &retdval, &rettxt); /* Starting Cypress TS transfer over USB */
    }
    if (ts_mode != SILABS_TS_GPIF) {
      L0_Cypress_Configure("-gpif_clk"             ,"tristate"  ,    0,                   &retdval, &rettxt); /* Tristating Cypress gpif clock         */
      L0_Cypress_Process  ("gpif"                  ,"CTL_Tristate",  0,                   &retdval, &rettxt);
    }
#endif /* USB_Capability */
    front_end->active_TS_mode = ts_mode;
    return ts_mode;
  } else {
    return -1;
  }
}
/************************************************************************************************************************
  SiLabs_API_Get_TS_Dividers function
  Use:      retrieving TS clock dividers function
            Used to retrieve the TS clock dividers
  Parameter: front_end, a pointer to the front End
  Parameter: div_a, a pointer to an unsigned int used to store the numerator value
  Parameter: div_b, a pointer to an unsigned int used to store the denominator value
  Returns:    0 if successful, 1 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_Get_TS_Dividers            (SILABS_FE_Context *front_end,    unsigned int *div_a, unsigned int *div_b)
{
  SiTRACE("API CALL INFO : SiLabs_API_Get_TS_Dividers (front_end, &div_a, &div_a);\n");
  *div_a = *div_b = 0;
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    if (Si2183_L1_DEMOD_INFO (front_end->Si2183_FE->demod) == NO_Si2183_ERROR) {
      *div_a = front_end->Si2183_FE->demod->rsp->demod_info.div_a;
      *div_b = front_end->Si2183_FE->demod->rsp->demod_info.div_b;
      return 0;
    } else {
      SiERROR("Error retrieving TS dividers!\n");
      return 1;
    }
  }
#endif /* Si2183_COMPATIBLE */
  SiTRACE("SiLabs_API_Get_TS_Dividers not supporting the current chip '%d'/'0x%x'\n", front_end->chip, front_end->chip);
  return 1;
}
/************************************************************************************************************************
  NAME: Silabs_API_TS_Tone_Cancel
  DESCRIPTION: enables/disables TS spurs transparently
	When tone cancel is disabled DIV_A and DIV_B are set to 0
  Parameter: on_off , 1= on, 0= off
  Returns:    '0' if OK, any other value indicates an error
************************************************************************************************************************/
signed   int  Silabs_API_TS_Tone_Cancel             (SILABS_FE_Context* front_end,    signed   int on_off)
{
    signed   int return_code;
#ifdef    TERRESTRIAL_FRONT_END
    unsigned int DIV_A;
    unsigned int DIV_B;

    DIV_A = DIV_B = 0;

    if (on_off == 1) {
      return_code = SiLabs_API_Get_TS_Dividers(front_end, &DIV_A, &DIV_B );
      if ( return_code != 0) {
        SiERROR("Error: Silabs_TS_Tone_Cancel can't get TS clock dividers from demod\n");
        return return_code;
      }
    }

    SiTRACE("Dividers for Tone canceller, DIV_A=%d, DIV_B=%d\n", DIV_A, DIV_B);
    SiLabs_API_Tuner_I2C_Enable (front_end);
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return_code = SiLabs_TER_Tuner_Tone_Cancel(front_end->Si2183_FE->tuner_ter, DIV_A, DIV_B); }
#endif /* Si2183_COMPATIBLE */
    if (return_code != 0) {
      SiERROR("SiLabs_TER_Tuner_Tone_Cancel failed !\n");
    }
    SiLabs_API_Tuner_I2C_Disable (front_end);
#endif /* TERRESTRIAL_FRONT_END */
    front_end   = front_end;     /* to avoid compiler warning if not used */
    return_code = 1*return_code; /* to avoid compiler warning if not used */
    return return_code;
}
/************************************************************************************************************************
  SiLabs_API_Tuner_I2C_Enable function
  Use:      Demod Loop through control function
            Used to switch the I2C loopthrough on, allowing communication with the tuners
  Return:    the final mode (-1 if not known)
************************************************************************************************************************/
signed   int  SiLabs_API_Tuner_I2C_Enable           (SILABS_FE_Context *front_end)
{
  SiTRACE("API CALL LOCK  : SiLabs_API_Tuner_I2C_Enable (front_end);\n");
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { Si2183_L2_Tuner_I2C_Enable (front_end->Si2183_FE); return 1;}
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  SiLabs_API_Tuner_I2C_Disable function
  Use:      Demod Loop through control function
            Used to switch the I2C loopthrough off, stopping communication with the tuners
  Return:    the final mode (-1 if not known)
************************************************************************************************************************/
signed   int  SiLabs_API_Tuner_I2C_Disable          (SILABS_FE_Context *front_end)
{
  SiTRACE("API CALL LOCK  : SiLabs_API_Tuner_I2C_Disable (front_end);\n");
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { Si2183_L2_Tuner_I2C_Disable (front_end->Si2183_FE); return 0;}
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  NAME: SiLabs_API_Channel_Seek_Init
  DESCRIPTION: logs the seek parameters in the context structure

  Scan algorithm based on the seek feature:

    SiLabs_API_switch_to_standard(front_end, standard, 0);

    SiLabs_API_Channel_Seek_Init (front_end, rangeMin, rangeMax,...);

    While ( SiLabs_API_Channel_Seek_Init (front_end, rangeMin, rangeMax,...) !=0 ) {
      SiLabs_API_TS_Mode (front_end, SILABS_TS_SERIAL/SILABS_TS_PARALLEL);

      the new carrier is at front_end->detected_rf with front_end->detected_sr
      look for PSI/SI information

      SiLabs_API_TS_Mode (front_end, SILABS_TS_TRISTATE);
    }
    SiLabs_API_Channel_Seek_End (front_end);

    Ideal settings for an algorithm based on 'local blindscan by steps of 8 MHz':
      SiLabs_API_Channel_Seek_Init (front_end, freq-4850000, freq+3150000,8000000, 8000000, 3500000, 7500000, 0, 0, 0, 0);

  Parameter:  Pointer to SILABS_FE_Context
  Parameter:  rangeMin starting Frequency (in Hz for TER, in kHz for SAT)
  Parameter:  rangeMax ending   Frequency (in Hz for TER, in kHz for SAT)
  Parameter:  minSRbps minimum SR to detect
  Parameter:  maxSRbps maximum SR to detect
  Parameter:  max RSSI dBm
  Parameter:  min RSSI dBm
  Parameter:  max RSSI dBm
  Parameter:  min SNR 1/2 dB
  Parameter:  max SNR 1/2 dB
  Returns:    0 if successful, otherwise an error.
************************************************************************************************************************/
signed   int  SiLabs_API_Channel_Seek_Init          (SILABS_FE_Context *front_end,
                                            signed   int rangeMin,     signed   int rangeMax,
                                            signed   int seekBWHz,     signed   int seekStepHz,
                                            signed   int minSRbps,     signed   int maxSRbps,
                                            signed   int minRSSIdBm,   signed   int maxRSSIdBm,
                                            signed   int minSNRHalfdB, signed   int maxSNRHalfdB)
{
  SiTRACE("API CALL SEEK  : SiLabs_API_Channel_Seek_Init (front_end, rangeMin %d, rangeMax %d, seekBWHz %d, seekStepHz %d, minSRbps %d, maxSRbps %d, minRSSIdBm %d, maxRSSIdBm %d, minSNRHalfdB %d, maxSNRHalfdB %d);\n", rangeMin, rangeMax, seekBWHz, seekStepHz, minSRbps, maxSRbps, minRSSIdBm, maxRSSIdBm, minSNRHalfdB, maxSNRHalfdB);
#ifdef    UNICABLE_COMPATIBLE
  front_end->unicable->inBlindScan = 1;
#endif // UNICABLE_COMPATIBLE
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return Si2183_L2_Channel_Seek_Init (front_end->Si2183_FE,  rangeMin, rangeMax, seekBWHz, seekStepHz, minSRbps, maxSRbps, minRSSIdBm, maxRSSIdBm, minSNRHalfdB, maxSNRHalfdB); }
#endif /* Si2183_COMPATIBLE */
  SiTRACE("Unknown chip '%d'\n", front_end->chip);
  SiERROR("SiLabs_API_Channel_Seek_Init Unknown chip\n");
  return 1;
}
/************************************************************************************************************************
  NAME: SiLabs_API_Channel_Seek_Next
  DESCRIPTION: Looks for the next channel, starting from the last detected channel
  Parameter:  Pointer to SILABS_FE_Context
  Returns:    1 if channel is found, 0 if abort or end of range, any other value is the handshake duration
************************************************************************************************************************/
signed   int  SiLabs_API_Channel_Seek_Next          (SILABS_FE_Context *front_end,    signed   int *standard, signed   int *freq, signed   int *bandwidth_Hz, signed   int *stream, unsigned int *symbol_rate_bps, signed   int *constellation, signed   int *polarization, signed   int *band, signed   int *num_data_slice, signed   int *num_plp, signed   int *T2_base_lite)
{
  signed   int seek_result;
  num_data_slice = num_data_slice;/* to avoid compiler warning if not used */
  num_plp        = num_plp;       /* to avoid compiler warning if not used */
  bandwidth_Hz   = bandwidth_Hz;  /* to avoid compiler warning if not used */
  polarization   = polarization;  /* to avoid compiler warning if not used */
  band           = band;          /* to avoid compiler warning if not used */
  *num_data_slice = 0;            /* set to '0' by default (to avoid processing DS   for standards not supporting this feature) */
  *num_plp        = 0;            /* set to '0' by default (to avoid processing MPLP for standards not supporting this feature) */
  *T2_base_lite   = 0;            /* set to '0' by default (to avoid processing T2 lite for standards not supporting this feature) */
  seek_result     = -1;
  SiTRACE("API CALL SEEK  : SiLabs_API_Channel_Seek_Next (front_end, &standard, &freq, &bandwidth_Hz, &stream, &symbol_rate_bps, &constellation, &polarization, &band, &num_data_slice, &num_plp, &T2_base_lite);\n");
  SiTRACE("SiLabs_API_Channel_Seek_Next config_code 0x%06x\n", front_end->config_code);

#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
      seek_result = Si2183_L2_Channel_Seek_Next (front_end->Si2183_FE, standard, freq
                                           , bandwidth_Hz
#ifdef    DEMOD_DVB_T
                                           , stream
#endif /* DEMOD_DVB_T*/
                                           , symbol_rate_bps
#ifdef    DEMOD_DVB_C
                                           , constellation
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_C2
                                           , num_data_slice
#endif /* DEMOD_DVB_C2*/
                                           , num_plp
#ifdef    DEMOD_DVB_T2
                                           , T2_base_lite
#endif /* DEMOD_DVB_T2 */
                                           );
  }
#endif /* Si2183_COMPATIBLE */
#ifdef    SATELLITE_FRONT_END
  *polarization = front_end->polarization;
  *band         = front_end->band;
#endif /* SATELLITE_FRONT_END */
  if (seek_result ==  1) {
    *standard = Custom_standardCode(front_end, *standard);
    front_end->standard = *standard;
    /* Translate demod-specific values to CUSTOM values */
    switch (*standard)
    {
      case SILABS_DVB_T : {
        *stream        = Custom_streamCode (front_end, *stream);
        break;
      }
      case SILABS_DVB_C : {
        *constellation = Custom_constelCode(front_end, *constellation);
        break;
      }
      default           : {
        break;
      }
    }
    return 1;
  }
  if (seek_result >   1) {
    return seek_result;
  }
  if (seek_result == -1) {
    SiTRACE("Chip '%d' not handled by SiLabs_API_Channel_Seek_Next\n", front_end->chip);
  }
  return 0;
}
/************************************************************************************************************************
  NAME: SiLabs_API_Channel_Seek_Abort
  DESCRIPTION: aborts the channel seek for the next channel
  Parameter:  Pointer to SILABS_FE_Context
  Returns:    1 if successful, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_Channel_Seek_Abort         (SILABS_FE_Context *front_end)
{
  SiTRACE("API CALL SEEK  : SiLabs_API_Channel_Seek_Abort (front_end);\n");
#ifdef    UNICABLE_COMPATIBLE
  front_end->unicable->inBlindScan = 0;
#endif // UNICABLE_COMPATIBLE
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return Si2183_L2_Channel_Seek_Abort (front_end->Si2183_FE); }
#endif /* Si2183_COMPATIBLE */
  SiTRACE("Unknown chip '%d'\n", front_end->chip);
  SiERROR("SiLabs_API_Channel_Seek_Abort Unknown chip\n");
  return 0;
}
/************************************************************************************************************************
  NAME: SiLabs_API_Channel_Lock_Abort
  DESCRIPTION: aborts the channel lock for the current channel
  Parameter:  Pointer to SILABS_FE_Context
  Returns:    1 if successful, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_Channel_Lock_Abort         (SILABS_FE_Context *front_end)
{
  SiTRACE("API CALL LOCK  : SiLabs_API_Channel_Lock_Abort (front_end);\n");
#ifdef    UNICABLE_COMPATIBLE
  front_end->unicable->inBlindScan = 0;
#endif // UNICABLE_COMPATIBLE
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return Si2183_L2_Channel_Lock_Abort (front_end->Si2183_FE); }
#endif /* Si2183_COMPATIBLE */
  SiTRACE("Unknown chip '%d'\n", front_end->chip);
  SiERROR("SiLabs_API_Channel_Lock_Abort Unknown chip\n");
  return 0;
}
/************************************************************************************************************************
  NAME: SiLabs_API_Channel_Seek_End
  DESCRIPTION: returns the chip back to normal following a seek
  Parameter:  Pointer to SILABS_FE_Context
  Returns:    1 if successful, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_Channel_Seek_End           (SILABS_FE_Context *front_end)
{
  SiTRACE("API CALL SEEK  : SiLabs_API_Channel_Seek_End (front_end);\n");
#ifdef    UNICABLE_COMPATIBLE
  front_end->unicable->inBlindScan = 0;
#endif // UNICABLE_COMPATIBLE
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return Si2183_L2_Channel_Seek_End (front_end->Si2183_FE); }
#endif /* Si2183_COMPATIBLE */
  SiTRACE("Unknown chip '%d'\n", front_end->chip);
  SiERROR("SiLabs_API_Channel_Seek_End Unknown chip\n");
  return 0;
}
#ifdef    SATELLITE_FRONT_END
/************************************************************************************************************************
  NAME: SiLabs_API_SAT_AutoDetectCheck
  DESCRIPTION: check function for the SAT auto detect mode
  Parameter:  Pointer to SILABS_FE_Context
  Returns:    -1 if error, 0 if not locked on SAT, otherwise the current SAT standard code,
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_AutoDetectCheck        (SILABS_FE_Context *front_end)
{
  signed   int detected;
  SiTRACE("API CALL SEEK  : SiLabs_API_SAT_AutoDetectCheck (front_end);\n");
  front_end = front_end; /* To avoid compiler warning if not used */
  detected = -1;
#ifdef    Si2183_COMPATIBLE
 #ifdef    DEMOD_DVB_S_S2_DSS
  if (front_end->chip ==   0x2183 ) {
    if (Si2183_L1_DD_STATUS (front_end->Si2183_FE->demod, Si2183_DD_STATUS_CMD_INTACK_OK) != NO_Si2183_ERROR) {
      SiERROR("Si2183_L1_DD_STATUS ERROR\n");
      return 0;
    }
    if (front_end->Si2183_FE->demod->rsp->dd_status.dl == 0) {return 0;}
    detected = Custom_standardCode(front_end, front_end->Si2183_FE->demod->rsp->dd_status.modulation);
    switch ( detected ) {
      case SILABS_DVB_S :
      case SILABS_DVB_S2: { return detected; break; }
      default:            { return       0 ; break; }
    }
  }
 #endif /* DEMOD_DVB_S_S2_DSS */
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  NAME: SiLabs_API_SAT_AutoDetect
  DESCRIPTION: activation function for the SAT auto detect mode
  Parameter: front_end, Pointer to SILABS_FE_Context
  Parameter: on_off, which is set to '0' to de-activate the SAT auto-detect feature,
              set to '1' to activate it and to any other value to retrieve the current status
  Returns:    the current state of auto_detect_SAT
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_AutoDetect             (SILABS_FE_Context *front_end,    signed   int on_off)
{
  SiTRACE("API CALL SEEK  : SiLabs_API_SAT_AutoDetect (front_end, %d);\n", on_off);
  front_end = front_end; /* To avoid compiler warning if not used */
  on_off    = on_off;    /* To avoid compiler warning if not used */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    if (on_off == 0) { Si2183_SatAutoDetectOff(front_end->Si2183_FE); }
    if (on_off == 1) { Si2183_SatAutoDetect   (front_end->Si2183_FE); }
    return front_end->Si2183_FE->auto_detect_SAT;
  }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  NAME: SiLabs_API_SAT_Tuner_Init
  DESCRIPTION: initialization function for the SAT tuner
  Parameter:  Pointer to SILABS_FE_Context
  Returns:    0 if error, 1 if sucess
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_Tuner_Init             (SILABS_FE_Context *front_end)
{
#ifdef    Si2183_COMPATIBLE
 #ifdef    DEMOD_DVB_S_S2_DSS
  if (front_end->chip ==   0x2183 ) { SAT_TUNER_INIT(front_end->Si2183_FE->tuner_sat); front_end->Si2183_FE->SAT_tuner_init_done = 1; return 1; }
 #endif /* DEMOD_DVB_S_S2_DSS */
#endif /* Si2183_COMPATIBLE */
  SiTRACE("Unknown chip '%d'\n", front_end->chip);
  SiERROR("SiLabs_API_SAT_Tuner_Init Unknown chip\n");
  return -1;
}
/************************************************************************************************************************
  NAME: SiLabs_API_SAT_Tuner_SetLPF
  DESCRIPTION: sets the SAT tuner low pass filter
  Parameter:  Pointer to SILABS_FE_Context
  Parameter:  lpf_khz, the lowpass filter (in khz)
  Returns:    the final lpf value
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_Tuner_SetLPF           (SILABS_FE_Context *front_end,    signed   int lpf_khz)
{
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return Si2183_L2_SAT_LPF (front_end->Si2183_FE , lpf_khz); }
#endif /* Si2183_COMPATIBLE */
  return 0;
}
/************************************************************************************************************************
  NAME: SiLabs_API_SAT_voltage
  DESCRIPTION: sets the LNB supply voltage
  Parameter:  Pointer to SILABS_FE_Context
  Parameter:  voltage, the LNB voltage level (allows 0, 13 or 18)
  Returns:    1 if successful, -1 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_voltage                (SILABS_FE_Context *front_end,    signed   int  voltage)
{
  SiTRACE_X("SiLabs_API_SAT_voltage voltage %d, front_end->lnb_chip %d\n", voltage, front_end->lnb_chip );
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { front_end->Si2183_FE->misc_infos = (front_end->Si2183_FE->misc_infos & 0xffffff00) + (voltage); }
#endif /* Si2183_COMPATIBLE */
#ifdef    LNBH21_COMPATIBLE
  if (front_end->lnb_chip ==     21 ) { L1_LNBH21_Voltage(front_end->lnbh21, voltage  ); return 1;}
#endif /* LNBH21_COMPATIBLE */
#ifdef    LNBH25_COMPATIBLE
  if (front_end->lnb_chip ==     25 ) {
    if (front_end->lnb_chip_init_done == 0) { front_end->lnb_chip_init_done = L1_LNBH25_InitAfterReset(front_end->lnbh25); }
    if (voltage == 18) L1_LNBH25_Voltage(front_end->lnbh25, 13);
    L1_LNBH25_Voltage(front_end->lnbh25, voltage );
    L1_LNBH25_Status (front_end->lnbh25);
    SiTRACE("L1_LNBH25_StatusInfo %s\n", L1_LNBH25_StatusInfo(front_end->lnbh25) );
    return 1;
  }
#endif /* LNBH25_COMPATIBLE */
#ifdef    LNBH26_COMPATIBLE
  if (front_end->lnb_chip ==     26 ) {
    if (front_end->lnb_chip_init_done == 0) { front_end->lnb_chip_init_done = L1_LNBH26_InitAfterReset(front_end->lnbh26); }
    L1_LNBH26_Voltage(front_end->lnbh26, voltage );
    L1_LNBH26_Status (front_end->lnbh26);
    SiTRACE("L1_LNBH26_StatusInfo %s\n", L1_LNBH26_StatusInfo(front_end->lnbh26) );
    return 1;
  }
#endif /* LNBH26_COMPATIBLE */
#ifdef    LNBH29_COMPATIBLE
  if (front_end->lnb_chip ==     29 ) {
    if (front_end->lnb_chip_init_done == 0) { front_end->lnb_chip_init_done = L1_LNBH29_InitAfterReset(front_end->lnbh29); }
    L1_LNBH29_Voltage(front_end->lnbh29, voltage ); return 1;
  }
#endif /* LNBH29_COMPATIBLE */
#ifdef    A8293_COMPATIBLE
  if (front_end->lnb_chip == 0xA8293) { L1_A8293_Voltage(front_end->A8293, voltage  ); return 1;}
#endif /* A8293_COMPATIBLE */
#ifdef    A8297_COMPATIBLE
  if (front_end->lnb_chip == 0xA8297) { L1_A8297_Voltage(front_end->A8297, voltage  ); return 1;}
#endif /* A8297_COMPATIBLE */
#ifdef    A8302_COMPATIBLE
  if (front_end->lnb_chip == 0xA8302) { L1_A8302_Voltage(front_end->A8302, voltage  ); return 1;}
#endif /* A8302_COMPATIBLE */
#ifdef    A8304_COMPATIBLE
  if (front_end->lnb_chip == 0xA8304) { L1_A8304_Voltage(front_end->A8304, voltage  ); return 1;}
#endif /* A8304_COMPATIBLE */
#ifdef    TPS65233_COMPATIBLE
  if (front_end->lnb_chip == 0x65233) { L1_TPS65233_Voltage(front_end->TPS65233, voltage  ); return 1;}
#endif /* TPS65233_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  NAME: SiLabs_API_SAT_and_tone
  DESCRIPTION: sets the LNB 22kHz tone
  Parameter:  Pointer to SILABS_FE_Context
  Parameter:  tone, a flag to enable the 22khz tone (allows 0 or 1)
  Returns:    1 if successful, -1 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_tone                   (SILABS_FE_Context *front_end,    unsigned char tone)
{
  signed   int cont_tone;
  unsigned char  diseqBuffer[1];

  SiTRACE_X("SiLabs_API_SAT_tone, tone %d\n", tone);
  switch (tone   ) {
    case  1: cont_tone = 1; break;
    default: cont_tone = 0; break;
  }
  diseqBuffer[0] = 0x00;
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { front_end->Si2183_FE->misc_infos = (front_end->Si2183_FE->misc_infos & 0xffff00ff) + (tone << 8); }
  if (front_end->chip ==   0x2183 ) { Si2183_L2_send_diseqc_sequence (front_end->Si2183_FE , 0, &diseqBuffer[0], cont_tone, 0, 0, 1); return 1; }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  NAME: SiLabs_API_SAT_voltage_and_tone
  DESCRIPTION: sets the LNB supply voltage and 22kHz tone
  Parameter:  Pointer to SILABS_FE_Context
  Parameter:  voltage, the LNB voltage level (allows 0, 13 or 18)
  Parameter:  tone, a flag to enable the 22khz tone (allows 0 or 1)
  Returns:    1 if successful, -1 otherwise
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_voltage_and_tone       (SILABS_FE_Context *front_end,    signed   int  voltage, unsigned char tone)
{
  SiTRACE("SiLabs_API_SAT_voltage_and_tone voltage %d, tone %d front_end->lnb_chip %d\n", voltage, tone, front_end->lnb_chip );
  if (SiLabs_API_SAT_voltage (front_end, voltage) == -1) {
    SiTRACE("SiLabs_API_SAT_voltage not supporting the current LNB controller (%d)!\n", front_end->lnb_chip);
    SiERROR("SiLabs_API_SAT_voltage not supporting the current LNB controller\n");
    return -1;
  }
  if (SiLabs_API_SAT_tone    (front_end, tone   ) == -1) {
    SiTRACE("SiLabs_API_SAT_tone not supporting the current demodulator (%d)!\n", front_end->chip);
    SiERROR("SiLabs_API_SAT_tone not supporting the current demodulator!\n");
    return -1;
  }
  return 1;
}
/************************************************************************************************************************
  NAME: SiLabs_API_SAT_prepare_diseqc_sequence
  DESCRIPTION: prepare a DiSEqC sequence to be sent on the SAT tuner input
  Parameter:  Pointer to SILABS_FE_Context
  Parameter:  sequence_length, the number of DiSEqC bytes to send
  Parameter:  sequence_buffer, a pointer to the DiSEqC bytes to send
  Parameter:  cont_tone, a flag indicating if the 22khz tone is to be sent
  Parameter:  tone_burst, a flag indicating if a 22khz tone needs to be sent around each DiSEqC message
  Parameter:  burst_sel, a flag indicating which satellite input is addressed by the DiSEqC message
  Parameter:  end_seq, a flag indicating if the current sequence is the last sequence in a series of DiSEqC messages
  Returns:    a value potentially used to call the SiLabs_API_SAT_trigger_diseqc_sequence
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_prepare_diseqc_sequence(SILABS_FE_Context *front_end,    signed   int sequence_length, unsigned char *sequence_buffer, unsigned char cont_tone, unsigned char tone_burst, unsigned char burst_sel, unsigned char end_seq, signed   int *flags)
{
  front_end       = front_end;
  sequence_length = sequence_length;
  sequence_buffer = sequence_buffer;
  cont_tone       = cont_tone;
  tone_burst      = tone_burst;
  burst_sel       = burst_sel;
  end_seq         = end_seq;
  *flags          = 0;
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { if (Si2183_L2_prepare_diseqc_sequence(front_end->Si2183_FE, sequence_length, sequence_buffer, cont_tone, tone_burst, burst_sel, end_seq) != NO_Si2183_ERROR ) {*flags = 0;} else {*flags = 1;} return 1; }
#endif /* Si2183_COMPATIBLE */
  return 0;
}
/************************************************************************************************************************
  NAME: SiLabs_API_SAT_trigger_diseqc_sequence
  DESCRIPTION: send a DiSEqC sequence prepared using SiLabs_API_SAT_prepare_diseqc_sequence on the SAT tuner input
  Parameter:  flags, a value potentially used to call the SiLabs_API_SAT_trigger_diseqc_sequence
  Returns:    0
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_trigger_diseqc_sequence(SILABS_FE_Context *front_end,    signed   int flags)
{
  front_end       = front_end;
  flags           = flags;
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {Si2183_L2_trigger_diseqc_sequence(front_end->Si2183_FE); return 1; }
#endif /* Si2183_COMPATIBLE */
  return 0;
}
/************************************************************************************************************************
  NAME: SiLabs_API_SAT_send_diseqc_sequence
  DESCRIPTION: sends a DiSEqC sequence on the SAT tuner input
  Parameter:  Pointer to SILABS_FE_Context
  Parameter:  sequence_length, the number of DiSEqC bytes to send
  Parameter:  sequence_buffer, a pointer to the DiSEqC bytes to send
  Parameter:  cont_tone, a flag indicating if the 22khz tone is to be sent
  Parameter:  tone_burst, a flag indicating if a 22khz tone needs to be sent around each DiSEqC message
  Parameter:  burst_sel, a flag indicating which satellite input is addressed by the DiSEqC message
  Parameter:  end_seq, a flag indicating if the current sequence is the last sequence in a series of DiSEqC messages
  Returns:    1 if no error
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_send_diseqc_sequence   (SILABS_FE_Context *front_end,    signed   int sequence_length, unsigned char *sequence_buffer, unsigned char cont_tone, unsigned char tone_burst, unsigned char burst_sel, unsigned char end_seq)
{
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { Si2183_L2_send_diseqc_sequence(front_end->Si2183_FE, sequence_length, sequence_buffer, cont_tone, tone_burst, burst_sel, end_seq); return 1; }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  NAME: SiLabs_API_SAT_read_diseqc_reply
  DESCRIPTION: reads a DiSEqC sequence from the SAT tuner input
  Parameter:  Pointer to SILABS_FE_Context
  Parameter:  reply_length, a pointer to the number of DiSEqC bytes read
  Parameter:  reply_buffer, a pointer to store the DiSEqC bytes read
  Returns:    1 if no error
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_read_diseqc_reply      (SILABS_FE_Context *front_end,    signed   int *reply_length  , unsigned char *reply_buffer   )
{
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { Si2183_L2_read_diseqc_reply (front_end->Si2183_FE, reply_length, reply_buffer); return 1; }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
signed   int  SiLabs_API_SAT_Tuner_Tune             (SILABS_FE_Context *front_end,    signed   int freq_kHz)
{
  SiTRACE("SiLabs_API_SAT_Tuner_Tune %d\n", freq_kHz);

#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    L1_RF_SAT_TUNER_Tune(front_end->Si2183_FE->tuner_sat, freq_kHz);
  }
#endif /* Si2183_COMPATIBLE */

  return 1;
}
signed   int  SiLabs_API_SAT_Tuner_Standby          (SILABS_FE_Context *front_end)
{
  SiTRACE("SiLabs_API_SAT_Tuner_Standby\n");

#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    SiLabs_SAT_Tuner_Standby(front_end->Si2183_FE->tuner_sat);
  }
#endif /* Si2183_COMPATIBLE */

  return 1;
}
signed   int  SiLabs_API_SAT_Tuner_SelectRF         (SILABS_FE_Context *front_end,    unsigned char rf_chn)
{
  SiTRACE("SiLabs_API_SAT_Tuner_SelectRF %d\n", rf_chn);
  SiLabs_API_SAT_Tuner_I2C_Enable       (front_end);
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    SiLabs_SAT_Tuner_SelectRF(front_end->Si2183_FE->tuner_sat, rf_chn);
  }
#endif /* Si2183_COMPATIBLE */
  SiLabs_API_SAT_Tuner_I2C_Disable      (front_end);

  return 1;
}
signed   int  SiLabs_API_SAT_Get_AGC                (SILABS_FE_Context *front_end)
{
  signed   int agc;
  agc = -1;
#ifdef    Si2183_COMPATIBLE
    if (front_end->chip ==   0x2183 ) {
      Si2183_L1_DD_EXT_AGC_SAT (front_end->Si2183_FE->demod,
                                Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_NO_CHANGE, 0,
                                Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MODE_NO_CHANGE, 0,
                                0, 0, 0, 0);
      agc =  front_end->Si2183_FE->demod->rsp->dd_ext_agc_sat.agc_1_level;
    }
#endif /* Si2183_COMPATIBLE */
  return agc;
}
#ifdef    UNICABLE_COMPATIBLE
signed   int  SiLabs_API_SAT_Unicable_Config        (SILABS_FE_Context *front_end,    signed  int unicable_mode, signed  int unicable_spectrum_inversion,  unsigned  int ub,  unsigned  int Fub_kHz,  unsigned  int Fo_kHz_low_band,  unsigned  int Fo_kHz_high_band )
{
  SiTRACE("API CALL CONFIG: SiLabs_API_SAT_Unicable_Config (front_end, %d, %d, %d, %d, %d, %d);\n", unicable_mode, unicable_spectrum_inversion, ub, Fub_kHz, Fo_kHz_low_band, Fo_kHz_high_band );
  SiTRACE("API CALL CONFIG: SiLabs_API_SAT_Unicable_Config (front_end, unicable_mode %d, unicable_spectrum_inversion %d, ub %d, Fub_kHz %d, Fo_kHz_low_band %d, Fo_kHz_high_band %d);\n",
                                                                       unicable_mode,    unicable_spectrum_inversion,    ub,    Fub_kHz,    Fo_kHz_low_band,    Fo_kHz_high_band );
  front_end->unicable->installed        = unicable_mode;
  front_end->unicable->ub               = ub;
  front_end->unicable->Fub_kHz          = Fub_kHz;
  front_end->unicable->Fo_kHz_low_band  = Fo_kHz_low_band;
  front_end->unicable->Fo_kHz_high_band = Fo_kHz_high_band;
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    front_end->Si2183_FE->unicable_mode               = unicable_mode;
    front_end->Si2183_FE->unicable_spectrum_inversion = unicable_spectrum_inversion;
  }
#endif /* Si2183_COMPATIBLE */
  return 1;
}
signed   int  SiLabs_API_SAT_Unicable_Install       (SILABS_FE_Context *front_end)
{
  if (front_end->unicable->installed == 0) {
    SiERROR("Unicable not configured yet. Please use SiLabs_API_SAT_Unicable_Config to set the Unicable parameters before calling SiLabs_API_SAT_Unicable_Install;\n");
  } else {
    front_end->lnb_type = UNICABLE_LNB_TYPE_UNICABLE;
    SiTRACE("front_end->lnb_type = UNICABLE_LNB_TYPE_UNICABLE;\n");
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    front_end->Si2183_FE->lnb_type = front_end->lnb_type;
    front_end->Si2183_FE->demod->prop->dd_diseqc_param.sequence_mode = Si2183_DD_DISEQC_PARAM_PROP_SEQUENCE_MODE_NO_GAP;
    Si2183_L1_SetProperty2(front_end->Si2183_FE->demod, Si2183_DD_DISEQC_PARAM_PROP_CODE);
  }
#endif /* Si2183_COMPATIBLE */
  }
  return front_end->unicable->installed;
}
signed   int  SiLabs_API_SAT_Unicable_Uninstall     (SILABS_FE_Context *front_end)
{
  front_end->lnb_type = UNICABLE_LNB_TYPE_NORMAL;
  SiTRACE("front_end->lnb_type = UNICABLE_LNB_TYPE_NORMAL;\n");
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    front_end->Si2183_FE->lnb_type = front_end->lnb_type;
    front_end->Si2183_FE->demod->prop->dd_diseqc_param.sequence_mode = Si2183_DD_DISEQC_PARAM_PROP_SEQUENCE_MODE_GAP;
    Si2183_L1_SetProperty2(front_end->Si2183_FE->demod, Si2183_DD_DISEQC_PARAM_PROP_CODE);
  }
#endif /* Si2183_COMPATIBLE */

  return 0;
}
signed   int  SiLabs_API_SAT_Unicable_Position      (SILABS_FE_Context *front_end, int position)
{
  switch (position) {
    default :
    case UNICABLE_POSITION_A:   front_end->unicable->satellite_position = position; break;
    case UNICABLE_POSITION_B:   front_end->unicable->satellite_position = position; break;
  }
  return 0;
}
signed   int  SiLabs_API_SAT_Unicable_Tune          (SILABS_FE_Context *front_end,    signed   int freq_kHz)
{
  signed   int L_freq;
  L_freq = SiLabs_Unicable_API_Tune(front_end->unicable, freq_kHz);
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    front_end->Si2183_FE->tuner_sat->RF = L_freq;
  }
#endif /* Si2183_COMPATIBLE */
  return L_freq;
}
/************************************************************************************************************************
  SiLabs_API_SAT_Unicable_Swap_Detect   function
  Use:      SAT IQ swap (i.e. entire spectrum inversion) detection function. The inversion is due to full band down conversion design
            Used to check if the reception equipment is inverting the spectrum or not, since this has an impact on blindscan results
            To call within SiLabs_API_SAT_Unicable_Swap_Loop
  Behavior: The function will retune the SAT tuner with a slight offset and relock.
            The sign of the variation of the freq_shift will indicate whether the chunk is inverted or not.
  Return:   -1 if it's not possible to find the chunk inversion (mostly due to lock issues).
            If called with front_end->unicable->installed = 0:
              The value (0 or 1) to use for the spectrum_inversion in the SiLabs_API_SAT_Spectrum function.
            If called with front_end->unicable->installed = 1 or 2:
              The value (0 or 1) to use for the unicable_spectrum_inversion flag used in the SiLabs_API_SAT_Unicable_Config function.
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_Unicable_Swap_Detect   (SILABS_FE_Context *front_end)
{
  signed   int freq_initial;
  signed   int freq_offset_initial;
  signed   int freq_offset_delta;
  signed   int lock_end_ms;
  #define SWAP_DETECT_STEP 100

  CUSTOM_Status_Struct  status_Struct;
  CUSTOM_Status_Struct *status;

  status = &status_Struct;

  SiTRACE("SiLabs_API_SAT_Unicable_Swap_Detect starting\n");

  SiLabs_API_FE_status_selection (front_end, status, 0x00);

  if (status->fec_lock == 0) {
    SiTRACE("Not locked initially, it's not possible to find out if there is a chunk inversion at this frequency\n");
    return -1;
  }

  freq_offset_initial = status->freq_offset;

  if (front_end->unicable->installed) {
    freq_initial        = front_end->unicable->Fub_kHz;
  } else {
    freq_initial        = status->freq;
  }

  SiLabs_API_SAT_Tuner_I2C_Enable  (front_end);
  SiLabs_API_SAT_Tuner_Tune        (front_end, freq_initial + SWAP_DETECT_STEP);
  SiLabs_API_SAT_Tuner_I2C_Disable (front_end);
  system_wait(50);
  Si2183_L1_DD_RESTART            (front_end->Si2183_FE->demod);
  lock_end_ms = system_time() + 2000;
  while (system_time() < lock_end_ms) {
    SiLabs_API_FE_status_selection (front_end, status, FE_LOCK_STATE );
    if (status->fec_lock == 1) break;
    system_wait(200);
  }

  if (status->fec_lock == 0) {
    SiTRACE("Not locked after re-tuning, it's not possible to find out if there is a chunk inversion at this frequency\n");
    return -1;
  }

  SiLabs_API_FE_status_selection (front_end, status, FE_FREQ + FE_LOCK_STATE + FE_SPECIFIC);

  freq_offset_delta = freq_offset_initial - status->freq_offset;

  SiTRACE("SiLabs_API_SAT_Unicable_Swap_Detect Unicable_installed %d | SAT_inv %d | UNI_inv %d | dd_mode.invert_spectrum %d | freq_initial %7d | freq_final %7d | freq_offset_initial %4d | freq_offset_final %4d | freq_offset_delta %4d | ub %2d | Fub_kHz %7d |\n",
           front_end->unicable->installed,
           front_end->Si2183_FE->satellite_spectrum_inversion,
           front_end->Si2183_FE->unicable_spectrum_inversion,
           front_end->Si2183_FE->demod->prop->dd_mode.invert_spectrum,
           freq_initial,
           freq_initial + SWAP_DETECT_STEP,
           freq_offset_initial,
           status->freq_offset,
           freq_offset_delta,
           front_end->unicable->ub,
           front_end->unicable->Fub_kHz
           );

  /* retuning back to initial freq, to return to the normal settings */
  SiLabs_API_SAT_Tuner_I2C_Enable  (front_end);
  SiLabs_API_SAT_Tuner_Tune        (front_end, freq_initial);
  SiLabs_API_SAT_Tuner_I2C_Disable (front_end);

  if (freq_offset_delta == 0) {
    SiTRACE("freq_offset_delta = 0, no possible decision\n");
    return -1;
  }
  if ( (freq_offset_delta < 0) && (freq_offset_delta > -SWAP_DETECT_STEP/2) ) {
    SiTRACE("freq_offset_delta = %d, no possible decision\n", freq_offset_delta);
    return -1;
  }
  if ( (freq_offset_delta > 0) && (freq_offset_delta < SWAP_DETECT_STEP/2) ) {
    SiTRACE("freq_offset_delta = %d, no possible decision\n", freq_offset_delta);
    return -1;
  }

  if        ( front_end->unicable->installed == 0) {
    if ( front_end->Si2183_FE->satellite_spectrum_inversion         == 0) {   /* checked with EVB using Airoha tuner which does not invert spectrum */
        /* Unicable_installed 0 | SAT_inv 0 | UNI_inv x */
      front_end->Si2183_FE->satellite_spectrum_inversion = (freq_offset_delta < 0); /* OK */
    } else {                                                                  /* checked with EVB using RDA tuner which inverts spectrum */
        /* Unicable_installed 0 | SAT_inv 1 | UNI_inv x */
      front_end->Si2183_FE->satellite_spectrum_inversion = (freq_offset_delta > 0); /* OK */
    }
    return front_end->Si2183_FE->satellite_spectrum_inversion;
  } else if ( front_end->unicable->installed == 1) {
    if ( front_end->Si2183_FE->satellite_spectrum_inversion         == 0) {   /* checked with EVB using Airoha tuner which does not invert spectrum */
      if ( front_end->Si2183_FE->unicable_spectrum_inversion          == 0) { /* checked with Unicable I/II DPC-32K  which does not invert spectrum */
        /* Unicable_installed 1 | SAT_inv 0 | UNI_inv 0 */
        front_end->Si2183_FE->unicable_spectrum_inversion = (freq_offset_delta < 0);
      } else {                                                                /* checked with Unicable I AXING SES 56-09 which inverts spectrum */
        /* Unicable_installed 1 | SAT_inv 0 | UNI_inv 1 */
        front_end->Si2183_FE->unicable_spectrum_inversion = (freq_offset_delta < 0);
      }
    } else {                                                                  /* checked with EVB using RDA tuner which inverts spectrum */
      if ( front_end->Si2183_FE->unicable_spectrum_inversion          == 0) { /* checked with Unicable I/II DPC-32K which does not invert spectrum */
        /* Unicable_installed 1 | SAT_inv 1 | UNI_inv 0 */
        front_end->Si2183_FE->unicable_spectrum_inversion = (freq_offset_delta < 0);
      } else {                                                                /* checked with Unicable I AXING SES 56-09 which inverts spectrum */
        /* Unicable_installed 1 | SAT_inv 1 | UNI_inv 1 */
        front_end->Si2183_FE->unicable_spectrum_inversion = (freq_offset_delta < 0);
      }
    }
    return front_end->Si2183_FE->unicable_spectrum_inversion;
  } else if ( front_end->unicable->installed == 2) {                          /* same as front_end->unicable->installed == 1 */
    if ( front_end->Si2183_FE->satellite_spectrum_inversion         == 0) {
      if ( front_end->Si2183_FE->unicable_spectrum_inversion          == 0) {
        /* Unicable_installed 2 | SAT_inv 0 | UNI_inv 0 */
        front_end->Si2183_FE->unicable_spectrum_inversion = (freq_offset_delta < 0);
      } else {
        /* Unicable_installed 2 | SAT_inv 0 | UNI_inv 1 */
        front_end->Si2183_FE->unicable_spectrum_inversion = (freq_offset_delta < 0);
      }
    } else {
      if ( front_end->Si2183_FE->unicable_spectrum_inversion          == 0) {
        /* Unicable_installed 2 | SAT_inv 1 | UNI_inv 0 */
        front_end->Si2183_FE->unicable_spectrum_inversion = (freq_offset_delta < 0);
      } else {
        /* Unicable_installed 2 | SAT_inv 1 | UNI_inv 1 */
        front_end->Si2183_FE->unicable_spectrum_inversion = (freq_offset_delta < 0);
      }
    }
  }
  return front_end->Si2183_FE->unicable_spectrum_inversion;
}
/************************************************************************************************************************
  SiLabs_API_SAT_Unicable_Swap_Loop    function
  Use:      SAT IQ swap (i.e. entire spectrum inversion) detection loop function. The inversion is due to full band down conversion design
            Used to check if the reception equipment is inverting the spectrum or not, since this has an impact on blindscan results
  Behavior: This function will attempt to lock on a SAT signal with blindscan then use blindscan and lock_to_carrier to correctly set spectrum inversion flag.
            Once locked, it will attempt to relock using the blindscan informations (frequency, symbol rate).
            If re-locked, it will attempt to relock on mirrored channel frequency. If locked, current chunk cannot be used to detect spectrum inversion and blindscan is re-started with a frequency offset to lock again on previous channel but no more on mirrored channel.
  Return:   -1 if it's not possible to find the chunk inversion (mostly due to lock issues).
            If called with front_end->unicable->installed = 0:
              The value (0 or 1) to use for the spectrum_inversion in the SiLabs_API_SAT_Spectrum function.
            If called with front_end->unicable->installed = 1 or 2:
              The value (0 or 1) to use for the unicable_spectrum_inversion flag used in the SiLabs_API_SAT_Unicable_Config function.
------------------------------------------------------------------------------------------------------------------------
  Typical use cases:
------------------------------------------------------------------------------------------------------------------------

  //// Once during SW design, to make sure of the value to use in SiLabs_API_SAT_Spectrum:
    SiLabs_API_switch_to_standard       (front_end, SILABS_DVB_S, 0);
    SiLabs_API_SAT_Unicable_Uninstall   (front_end); // Switching to non-Unicable mode
    // At this point the proper value for 'spectrum_inversion' is unknown
    SiLabs_API_SAT_Unicable_Swap_Loop   (front_end, 950000, 2150000);
    // At this point the proper value for 'spectrum_inversion' is known and has been stored in front_end->Si2183_FE->satellite_spectrum_inversion
    // NB: It should be used in the SW configuration call to SiLabs_API_SAT_Spectrum to avoid further detections

  //// During Unicable installation, every time a new Unicable equipment is installed and the installer doesn't know if it generates a spectrum inversion or not
      // NB: We don't expect installers to know this, since it's not indicated on any Unicable equipment
    // The Unicable position/polarization/band must have been selected beforehand, since these are not controlled by the function.
    //   The easiest solution to achieve this is to call:
      SiLabs_API_SAT_Unicable_Position    (front_end, position = UNICABLE_POSITION_<A/B>);
      SiLabs_API_lock_to_carrier          (front_end,
                             SILABS_DVB_S,
                             any_SAT_freq,
                             bandwidth_Hz = 0,
                             stream = 0,
                             any_SAT_symbol_rate_bps,
                             constellation = 0,
                             polarization,
                             band,
                             data_slice_id = 0,
                             plp_id = 0,
                             T2_lock_mode = 0);

    // At this point the position/polarization/band are set on one active input of the Unicable equipment, where SAT channels are present
    SiLabs_API_switch_to_standard       (front_end, SILABS_DVB_S, 0);
    SiLabs_API_SAT_Unicable_Config      (front_end, unicable_mode (1 or 2), unicable_chunk_inversion (0 or 1), ub, Fub_kHz, LO_kHz_low_band, LO_kHz_high_band );
    // NB: detection will be faster if the initial unicable_chunk_inversion value is correct. At the time of writing what we have seen is that:
      // Unicable I  equipment invert the chunk          (preferably start with unicable_chunk_inversion = 1 for Unicable I  equipment)
      // Unicable II equipment doesn't invert the chunk  (preferably start with unicable_chunk_inversion = 0 for Unicable II equipment)
    SiLabs_API_SAT_Unicable_Install     (front_end); // Switching to Unicable mode
    // At this point the proper value for 'unicable_spectrum_inversion' is unknown
    SiLabs_API_SAT_Unicable_Swap_Loop   (front_end, 950000, 2150000);
    // At this point the proper value for 'unicable_spectrum_inversion' is known and has been stored in front_end->Si2183_FE->unicable_spectrum_inversion
    // NB: It should be used in the next calls to SiLabs_API_SAT_Unicable_Config to get good SAT blindscan results
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_Unicable_Swap_Loop     (SILABS_FE_Context *front_end, unsigned int rangeMin, unsigned int rangeMax)
{
  signed   int ret = -1;
  int i;
  int lock;
  int relock;
  int standard;
  int freq;
  int bandwidth_Hz;
  int stream;
  unsigned int symbol_rate_bps;
  int constellation;
  int polarization;
  int band;
  int num_data_slice;
  int num_plp;
  int T2_base_lite;
  int initial_rangeMin;
  int freq_threshold_1 = 2000;
  int freq_threshold_2 = 2000;
  signed   int handshake_mode = 0;
  signed   int handshake_period_ms = 0;
  unsigned int dvbs_afc_range_khz = front_end->Si2183_FE->demod->prop->dvbs_afc_range.range_khz;
  unsigned int dvbs2_afc_range_khz = front_end->Si2183_FE->demod->prop->dvbs2_afc_range.range_khz;
  initial_rangeMin = rangeMin;

  if(front_end->swap_detection_done){
       SiTRACE("Swap detection has already been successfully performed.");
       if (front_end->unicable->installed == 0) {
          SiTRACE("satellite_spectrum_inversion=%d\n", front_end->Si2183_FE->satellite_spectrum_inversion);
          return front_end->Si2183_FE->satellite_spectrum_inversion;
       } else {
          SiTRACE("unicable_spectrum_inversion=%d\n", front_end->Si2183_FE->unicable_spectrum_inversion);
          return front_end->Si2183_FE->unicable_spectrum_inversion;
       }
  }

  // saving API handshake settings before disabling handshake
  if (front_end->Si2183_FE->handshakeUsed == 1) {
      handshake_mode = front_end->Si2183_FE->handshakeUsed;
      handshake_period_ms = front_end->Si2183_FE->handshakePeriod_ms;
  }
  SiLabs_API_Handshake_Setup (front_end, 0, 0);
  // reducing AFC range to reduce probability of lock on both blindscan channel and mirrored channel
  if (front_end->unicable->installed == 1) {
    front_end->Si2183_FE->demod->prop->dvbs_afc_range.range_khz = 3000;
    front_end->Si2183_FE->demod->prop->dvbs2_afc_range.range_khz = 3000;
  } else {
    front_end->Si2183_FE->demod->prop->dvbs_afc_range.range_khz = 2000;
    front_end->Si2183_FE->demod->prop->dvbs2_afc_range.range_khz = 2000;
  }
  Si2183_L1_SetProperty2(front_end->Si2183_FE->demod, Si2183_DVBS_AFC_RANGE_PROP_CODE);
  Si2183_L1_SetProperty2(front_end->Si2183_FE->demod, Si2183_DVBS2_AFC_RANGE_PROP_CODE);

  for (i=0; i<2; i++) {

    seek_init_point:
    //// Running a partial scan (with no handshake) to find what the value of 'unicable_spectrum_inversion' needs to be
    ////   scan only until locked on the very first channel lock, using 20-45 Mb to make it faster and detect high SR carriers
    SiTRACE("SiLabs_API_SAT_Unicable_Swap_Loop run %d, seekInit range %7d/%-7d | Unicable_installed %d | SAT_inv %d | UNI_inv %d | dd_mode.invert_spectrum %d | ub %2d | Fub_kHz %7d \n",
             i,
             rangeMin, rangeMax,
             front_end->unicable->installed,
             front_end->Si2183_FE->satellite_spectrum_inversion,
             front_end->Si2183_FE->unicable_spectrum_inversion,
             front_end->Si2183_FE->demod->prop->dd_mode.invert_spectrum,
             front_end->unicable->ub,
             front_end->unicable->Fub_kHz
             );

    SiLabs_API_Channel_Seek_Init        (front_end, rangeMin, rangeMax, 0,0, 20000000, 45000000, 0,0,0,0);

    lock = SiLabs_API_Channel_Seek_Next   (front_end, &standard, &freq, &bandwidth_Hz, &stream, &symbol_rate_bps, &constellation, &polarization, &band, &num_data_slice, &num_plp, &T2_base_lite);
    SiLabs_API_Channel_Seek_Abort(front_end);

    SiTRACE("SiLabs_API_SAT_Unicable_Swap_Loop lock   %d after seekNext at freq %7d\n", lock, freq);
    if (lock == 0) {
      if (i == 1) {
        SiTRACE("It has been impossible to lock. Please check your signal source and SAT equipment!\n");
      } else {
        if (front_end->unicable->installed == 0) {
          if ( front_end->Si2183_FE->satellite_spectrum_inversion == 0) {
            front_end->Si2183_FE->satellite_spectrum_inversion = 1;
          } else {
            front_end->Si2183_FE->satellite_spectrum_inversion = 0;
          }
          SiTRACE("inverting the satellite_spectrum_inversion flag (now %d) and retrying\n ", front_end->Si2183_FE->satellite_spectrum_inversion);
        } else {
          if ( front_end->Si2183_FE->unicable_spectrum_inversion == 0) {
            front_end->Si2183_FE->unicable_spectrum_inversion = 1;
          } else {
            front_end->Si2183_FE->unicable_spectrum_inversion = 0;
          }
          SiTRACE("inverting the unicable_spectrum_inversion flag (now %d) and retrying\n ", front_end->Si2183_FE->unicable_spectrum_inversion);
        }
        rangeMin = initial_rangeMin;
      }
    }
     // Blindscan locked. Now check if the chunk can be used to find spectrum swap if any
    if (lock == 1) {
      relock = SiLabs_API_lock_to_carrier (front_end, standard, freq, bandwidth_Hz, stream, symbol_rate_bps, constellation, SILABS_POLARIZATION_DO_NOT_CHANGE, SILABS_BAND_DO_NOT_CHANGE, num_data_slice, num_plp, T2_base_lite);
      SiTRACE("SiLabs_API_SAT_Unicable_Swap_Loop Attempt to relock is %d with standard %d,  freq %7d, sr %d, pol %d, band %d\n ", relock, standard, freq, symbol_rate_bps, polarization, band);
      if (relock == 1) {
        // defining area within blindscan chunk which can be used to detect spectrum inversion
        if (front_end->unicable->installed == 2) {
          freq_threshold_1 = 2000;
          freq_threshold_2 = 2000;
        } else {
          if (front_end->Si2183_FE->demod->prop->scan_sat_unicable_bw.scan_sat_unicable_bw < 480) {
            freq_threshold_1 = 5000;
            freq_threshold_2 = 5000;
          } else {
            freq_threshold_1 = 5000;
            freq_threshold_2 = 10000;
          }
        }
        // if current chunk cannot be used, chunk boundaries are modified to detect again channel Fc
        if ((((freq - front_end->Si2183_FE->rangeMin) >= 0) & ((freq - front_end->Si2183_FE->rangeMin) <= freq_threshold_1)) | (((front_end->Si2183_FE->rangeMin -freq) >= 0) & ((front_end->Si2183_FE->rangeMin -freq) <= freq_threshold_2))) {
          SiTRACE("Channel Fc is too close to blindscan tune request.RangeMin-freq= %7dkHz\n", front_end->Si2183_FE->rangeMin - freq);
          rangeMin = front_end->Si2183_FE->rangeMin - front_end->Si2183_FE->demod->prop->scan_sat_unicable_bw.scan_sat_unicable_bw * 50 + freq_threshold_1;
          if (rangeMin < rangeMax) {
           SiTRACE("Analyzing chunk starting at freq %7d.\n", rangeMin);
           goto seek_init_point;
          } else {
            i = 1;
            SiTRACE("It has been impossible to find a chunk allowing to find spectrum swap if any.\n");
            break;
          }
        } else {
          // At this point we know what the value for 'spectrum_inversion' needs to be
          if (front_end->unicable->installed == 0) {
            ret = front_end->Si2183_FE->satellite_spectrum_inversion;
            SiTRACE("satellite_spectrum_inversion is %d.\n ", ret);
          } else {
            ret = front_end->Si2183_FE->unicable_spectrum_inversion;
            SiTRACE("unicable_spectrum_inversion  is %d.\n ", ret);
          }
          front_end->swap_detection_done = 1;
            break;
        }
      }
      SiTRACE("No relock. Changing unicable spectrum inversion and checking again\n ");
      if (front_end->unicable->installed == 0) {
        front_end->Si2183_FE->satellite_spectrum_inversion = 1 - front_end->Si2183_FE->satellite_spectrum_inversion;
      } else {
        front_end->Si2183_FE->unicable_spectrum_inversion = 1 - front_end->Si2183_FE->unicable_spectrum_inversion;
      }
      if (initial_rangeMin > (front_end->Si2183_FE->rangeMin - front_end->Si2183_FE->demod->prop->scan_sat_unicable_bw.scan_sat_unicable_bw * 50)) {
        rangeMin = initial_rangeMin;
      } else {
        rangeMin = front_end->Si2183_FE->rangeMin - front_end->Si2183_FE->demod->prop->scan_sat_unicable_bw.scan_sat_unicable_bw * 50;
      }
      goto seek_init_point;
    }
  }
  // restoring  API handshake settings
  SiLabs_API_Handshake_Setup (front_end, handshake_mode, handshake_period_ms);
  // restoring AFC range for normal use
  front_end->Si2183_FE->demod->prop->dvbs_afc_range.range_khz = dvbs_afc_range_khz;
  front_end->Si2183_FE->demod->prop->dvbs2_afc_range.range_khz = dvbs2_afc_range_khz;
  Si2183_L1_SetProperty2(front_end->Si2183_FE->demod, Si2183_DVBS_AFC_RANGE_PROP_CODE);
  Si2183_L1_SetProperty2(front_end->Si2183_FE->demod, Si2183_DVBS2_AFC_RANGE_PROP_CODE);
  Si2183_L1_DD_RESTART            (front_end->Si2183_FE->demod);

  // restore default unicable spectrum inversion if not successful
  if(-1 == ret){
      if (front_end->unicable->installed == 1) {
        front_end->Si2183_FE->unicable_spectrum_inversion = 1;
      }
	  else
      if (front_end->unicable->installed == 2) {
        front_end->Si2183_FE->unicable_spectrum_inversion = 0;
      }
  }

  return ret;
}
/************************************************************************************************************************
  NAME: SiLabs_API_SAT_Random_Delay_Init
  DESCRIPTION: PRBS sequence init for SAT DiSEqC random delay generation
                This is used to re-send a DiSEqC sequence when a DiSEqC collision is detected,
                as defined by EN50494:2007 in 'Traffic collision management rules'
                NB: At demodulator level, only 'absence of corrupted packets' can be implemented.
  Parameter: front_end, Pointer to SILABS_FE_Context
  Parameter:  UB, the index of the Unicable User Band in use
  Returns:    the final value on 10 bits
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_Random_Delay_Init      (SILABS_FE_Context *front_end,    signed   char UB)
{
  unsigned int   i;
  signed   int   x;
  unsigned char *PRBS;

  PRBS = front_end->PRBS;

  for (i=0; i<10; i++) { PRBS[i] = 0; }
  for (i=0; i<=3; i++) { PRBS[9-i] = PRBS[4-i] = (UB>>(3-i))&0x1; }

  x = 0; for (i=0; i<10; i++) {  x = x + (PRBS[i]<<i); }

  SiTRACE("API CALL LOCK  : SiLabs_API_SAT_Random_Delay_Init (front_end, %d); x = %3d\n", UB, x);
  return x;
}
/************************************************************************************************************************
  NAME: SiLabs_API_SAT_Random_Delay_Shift
  DESCRIPTION: PRBS sequence shift for SAT DiSEqC random delay generation
                This is used to re-send a DiSEqC sequence when a DiSEqC collision is detected,
                as defined by EN50494:2007 in 'Traffic collision management rules'.
                NB: At demodulator level, only 'absence of corrupted packets' can be implemented.
  Parameter: front_end, Pointer to SILABS_FE_Context
  Parameter:  shift, the number of time the loop must be ran
  Returns:    the final value on 10 bits
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_Random_Delay_Shift     (SILABS_FE_Context *front_end,    signed   char shift)
{
  unsigned int i;
  unsigned int s;
  signed   int x;
  signed char  P10;
  unsigned char *PRBS;

  PRBS = front_end->PRBS;

  for (s=0; s<shift; s++) {
    P10 = (PRBS[7] + PRBS[0] + 1 )%2;
    for (i=0; i< 9; i++) { PRBS[i] = PRBS[i+1]; }
    PRBS[9] = P10;
  }

  x = 0; for (i=0; i<10; i++) {  x = x + (PRBS[i]<<i); } ;

  SiTRACE("API CALL LOCK  : SiLabs_API_SAT_Random_Delay_Shift(front_end, %d); x = %3d\n", shift, x);
  return x;
}
#endif /* UNICABLE_COMPATIBLE */
/************************************************************************************************************************
  SiLabs_API_SAT_Tuner_I2C_Enable function
  Use:      Demod Loop through control function,
            Used to switch the I2C loopthrough on, allowing communication with the SAT tuner
            This function can control the I2C passthrough for any front-end in the front-end table,
             and is useful mainly in multi-front-end applications with dual tuners or dual demodulators,
             when the SAT tuner I2C is not directly connected to the corresponding demodulator.
  Return:    the final mode (-1 if not known)
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_Tuner_I2C_Enable       (SILABS_FE_Context *front_end)
{
#ifdef    INDIRECT_I2C_CONNECTION
  signed   int fe;
  signed   int requester;
  signed   int connecter;
  signed   int fe_count;
  fe_count = FRONT_END_COUNT;
  for (fe=0; fe< fe_count; fe++) {
    if ( front_end  == &(FrontEnd_Table[fe]) ) {
      requester = fe;
      connecter = front_end->SAT_tuner_I2C_connection;
      if (connecter == 100) {
        /* 100 is a special value to allow having tuners connected directly.                                   */
        /* If tuners are connected directly, the i2c pass-through should NOT be closed, to avoid i2c deadlock. */
        return 1;
      }
      SiTRACE("-- I2C -- SiLabs_API_SAT_Tuner_I2C_Enable  request for front_end %d via front_end %d\n", requester, connecter);
      if (connecter < fe_count) {
        if (requester != connecter) {
      SiTRACE("-- I2C -- Enabling  indirect SAT tuner connection  for front_end %d via front_end %d\n", requester, connecter);
        }
        return SiLabs_API_Tuner_I2C_Enable(&(FrontEnd_Table[connecter]) );
      }
      break;
    }
  }
  SiTRACE("-- I2C -- SiLabs_API_SAT_Tuner_I2C_Enable  request failed! Unable to find a match for the caller front_end! (0x%08x)\n", (int)front_end);
  SiERROR("-- I2C -- SiLabs_API_SAT_Tuner_I2C_Enable  request failed! Unable to find a match for the caller front_end!\n");
  return 0;
#endif /* INDIRECT_I2C_CONNECTION */
  return SiLabs_API_Tuner_I2C_Enable(front_end);
}
/************************************************************************************************************************
  SiLabs_API_SAT_Tuner_I2C_Disable function
  Use:      Demod Loop through control function,
            Used to switch the I2C loopthrough off, disabling communication with the SAT tuner
            This function can control the I2C passthrough for any front-end in the front-end table,
             and is useful mainly in multi-front-end applications with dual tuners or dual demodulators,
             when the SAT tuner I2C is not directly connected to the corresponding demodulator.
  Return:    the final mode (-1 if not known)
************************************************************************************************************************/
signed   int  SiLabs_API_SAT_Tuner_I2C_Disable      (SILABS_FE_Context *front_end)
{
#ifdef    INDIRECT_I2C_CONNECTION
  signed   int fe;
  signed   int requester;
  signed   int connecter;
  signed   int fe_count;
  fe_count = FRONT_END_COUNT;
  for (fe=0; fe< fe_count; fe++) {
    if ( front_end  == &(FrontEnd_Table[fe]) ) {
      requester = fe;
      connecter = front_end->SAT_tuner_I2C_connection;
      if (connecter == 100) {
        /* 100 is a special value to allow having tuners connected directly.                                   */
        /* If tuners are connected directly, the i2c pass-through should NOT be closed, to avoid i2c deadlock. */
        return 1;
      }
      SiTRACE("-- I2C -- SiLabs_API_SAT_Tuner_I2C_Disable request for front_end %d via front_end %d\n", requester, connecter);
      if (connecter < fe_count) {
        if (requester != connecter) {
      SiTRACE("-- I2C -- Disabling indirect TER tuner connection for front_end %d via front_end %d\n", requester, connecter);
        }
        return SiLabs_API_Tuner_I2C_Disable(&(FrontEnd_Table[connecter]) );
      }
      break;
    }
  }
  SiTRACE("-- I2C -- SiLabs_API_SAT_Tuner_I2C_Disable request failed! Unable to find a match for the caller front_end! (0x%08x)\n", (int)front_end);
  SiERROR("-- I2C -- SiLabs_API_SAT_Tuner_I2C_Disable request failed! Unable to find a match for the caller front_end!\n");
  return 0;
#endif /* INDIRECT_I2C_CONNECTION */
  return SiLabs_API_Tuner_I2C_Disable(front_end);
}
/************************************************************************************************************************
  NAME: SiLabs_API_Get_Stream_Info
  DESCRIPTION: Stream info function for DVB-S2X
  Parameter: front_end, Pointer to SILABS_FE_Context
  Parameter:  isi_index, the data slice id containing the plp (if applicable, initially only used for DVB-C2),
  Parameter:  isi_index, the index of the required ISI,
  Parameter: *isi_id, a pointer to the isi id,
  Parameter: *isi_constellation, a pointer to the isi constellation,
  Parameter: *isi_code_rate, a pointer to the isi code_rate,
  Returns:    0 if no error value, -1 in case of an error
************************************************************************************************************************/
signed   int  SiLabs_API_Get_Stream_Info            (SILABS_FE_Context *front_end,    signed   int  isi_index, signed   int *isi_id, signed   int *isi_constellation, signed   int *isi_code_rate )
{
  front_end         = front_end        ; /* To avoid compiler warning if not used */
  isi_index         = isi_index        ; /* To avoid compiler warning if not used */
  isi_id            = isi_id           ; /* To avoid compiler warning if not used */
  isi_constellation = isi_constellation; /* To avoid compiler warning if not used */
  isi_code_rate     = isi_code_rate    ; /* To avoid compiler warning if not used */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
#ifdef    DEMOD_DVB_S2X
    if (front_end->standard == SILABS_DVB_S2) {
      if (Si2183_L1_DVBS2_STREAM_INFO(front_end->Si2183_FE->demod, isi_index) != NO_Si2183_ERROR) {
        SiTRACE("Si2183_L1_DVBS2_STREAM_INFO error when checking ISI index %d!\n", isi_index);
        SiERROR("Si2183_L1_DVBS2_STREAM_INFO error!\n");
        return -1;
      }
      *isi_id            = front_end->Si2183_FE->demod->rsp->dvbs2_stream_info.isi_id;
      *isi_constellation = Custom_constelCode (front_end, front_end->Si2183_FE->demod->rsp->dvbs2_stream_info.isi_constellation);
      *isi_code_rate     = Custom_coderateCode(front_end, front_end->Si2183_FE->demod->rsp->dvbs2_stream_info.isi_code_rate);
    }
#endif /* DEMOD_DVB_S2X */
    return 0;
  }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  NAME: SiLabs_API_Select_Stream
  DESCRIPTION: Stream selection function for DVB-S2X
  Parameter: front_end, Pointer to SILABS_FE_Context
  Parameter:  stream_id, the STREAM id of the required ISI (must be lower than num_is for the selected carrier)
                Use '-1' for auto selection,
  Returns:    0 if no error value, -1 in case of an error
************************************************************************************************************************/
signed   int  SiLabs_API_Select_Stream              (SILABS_FE_Context *front_end,    signed   int stream_id)
{
  signed   int stream_sel_mode;
  SiTRACE("API CALL LOCK  : SiLabs_API_Select_Stream (front_end, %d);\n", stream_id);
  front_end       = front_end;        /* To avoid compiler warning if not used */
  stream_id       = stream_id   ; /* To avoid compiler warning if not used */
  stream_sel_mode = 0;
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
#ifdef    DEMOD_DVB_S2X
    if (stream_id < 0) {
      stream_sel_mode = Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_SEL_MODE_AUTO;
    } else {
      stream_sel_mode = Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_SEL_MODE_MANUAL;
    }
    if (Si2183_L1_DVBS2_STREAM_SELECT(front_end->Si2183_FE->demod, stream_id, stream_sel_mode) != NO_Si2183_ERROR) {
      SiTRACE("Si2183_L1_DVBS2_STREAM_SELECT error when selecting ISI stream %d!\n", stream_id);
      SiERROR("Si2183_L1_DVBS2_STREAM_SELECT error!\n");
      return -1;
    }
/*    if (stream_sel_mode == Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_SEL_MODE_AUTO) { Si2183_L1_DD_RESTART(front_end->Si2183_FE->demod); system_wait(300); }*/
#endif /* DEMOD_DVB_S2X */
    return 0;
  }
#endif /* Si2183_COMPATIBLE */
  stream_id = stream_sel_mode; /* to avoid compiler warning when not used */
  return -1;
}
#endif /* SATELLITE_FRONT_END */
#ifdef    TERRESTRIAL_FRONT_END
#ifdef    DEMOD_DVB_T
/************************************************************************************************************************
  NAME: SiLabs_API_Get_DVBT_Hierarchy
  DESCRIPTION: Hierarchy info function for DVB-T
  Parameter: front_end, Pointer to SILABS_FE_Context
  Parameter: *hierarchy, a pointer to the hierarchy,
  Returns:    0 if no error value, -1 in case of an error
************************************************************************************************************************/
signed   int  SiLabs_API_Get_DVBT_Hierarchy         (SILABS_FE_Context *front_end,    signed   int *hierarchy)
{
  front_end = front_end;        /* To avoid compiler warning if not used */
  hierarchy = hierarchy;        /* To avoid compiler warning if not used */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    if (Si2183_L1_DVBT_STATUS(front_end->Si2183_FE->demod, Si2183_DVBT_STATUS_CMD_INTACK_OK) != NO_Si2183_ERROR) {
      SiTRACE("Si2183_L1_DVBT_STATUS error when checking DVB-T hierarchy!\n");
      SiERROR("Si2183_L1_DVBT_STATUS error!\n");
      return -1;
    }
    *hierarchy   = Custom_hierarchyCode(front_end, front_end->Si2183_FE->demod->rsp->dvbt_status.hierarchy);
    return 0;
  }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
#endif /* DEMOD_DVB_T */
/************************************************************************************************************************
  NAME: SiLabs_API_Get_DS_ID_Num_PLP_Freq
  DESCRIPTION: Dataslice ID, Num PLP and Frequency info function for DVB-C2.
             In a C2 system the initial parameter is the number of dataslices.
             For each dataslice (selected by its index), this function retrieves the
  Parameter: front_end, Pointer to SILABS_FE_Context
  Parameter:  ds_index, the index of the data slice in the C2 system,
  Parameter: *data_slice_id, a pointer to the dataslice Id,
  Parameter: *num_plp, a pointer to the number of PLPs in the dataslice,
  Parameter: *freq, a pointer to the dataslice frequency, in Hz,
  Returns:    0 if no error value, -1 in case of an error
************************************************************************************************************************/
signed   int  SiLabs_API_Get_DS_ID_Num_PLP_Freq     (SILABS_FE_Context *front_end,    signed   int ds_index, signed   int *ds_id, signed   int *num_plp, signed   int *freq_hz)
{
  front_end = front_end; /* To avoid compiler warning if not used */
  ds_index  = ds_index ; /* To avoid compiler warning if not used */
  ds_id     = ds_id    ; /* To avoid compiler warning if not used */
  num_plp   = num_plp  ; /* To avoid compiler warning if not used */
  freq_hz   = freq_hz  ; /* To avoid compiler warning if not used */
#ifdef    DEMOD_DVB_C2
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    if (front_end->standard == SILABS_DVB_C2) {
      if (Si2183_L1_DVBC2_DS_INFO(front_end->Si2183_FE->demod, ds_index, Si2183_DVBC2_DS_INFO_CMD_DS_SELECT_INDEX_OR_ID_INDEX) != NO_Si2183_ERROR) {
        SiTRACE("Si2183_L1_DVBC2_DS_INFO error when checking DS index %d!\n", ds_index);
        SiERROR("Si2183_L1_DVBC2_DS_INFO error!\n");
        return -1;
      }
      *ds_id    = front_end->Si2183_FE->demod->rsp->dvbc2_ds_info.ds_id;
      *num_plp  = front_end->Si2183_FE->demod->rsp->dvbc2_ds_info.dslice_num_plp;
      *freq_hz  = front_end->Si2183_FE->demod->rsp->dvbc2_ds_info.dslice_tune_pos_hz;
    }
    SiTRACE("DS index %3d: DS ID %3d, Num PLP %3d, Freq %d Hz\n", ds_index, *ds_id, *num_plp, *freq_hz);
    return 0;
  }
#endif /* Si2183_COMPATIBLE */
#endif /* DEMOD_DVB_C2 */
  return -1;
}
/************************************************************************************************************************
  NAME: SiLabs_API_Get_PLP_ID_and_TYPE
  DESCRIPTION: PLP ID and TYPE info function for DVB-T2 and DVB-C2
  Parameter: front_end, Pointer to SILABS_FE_Context
  Parameter:  ds_id, the data slice id containing the plp (if applicable, initially only used for DVB-C2),
  Parameter:  plp_index, the index of the required PLP (must be lower than num_plp for the selected carrier),
  Parameter: *plp_id, a pointer to the plp id,
  Parameter: *plp_type, a pointer to the plp type,
  Returns:    0 if no error value, -1 in case of an error
************************************************************************************************************************/
signed   int  SiLabs_API_Get_PLP_ID_and_TYPE        (SILABS_FE_Context *front_end,    signed   int  ds_id, signed   int plp_index, signed   int *plp_id, signed   int *plp_type)
{
  front_end = front_end; /* To avoid compiler warning if not used */
  plp_index = plp_index; /* To avoid compiler warning if not used */
  ds_id     = ds_id    ; /* To avoid compiler warning if not used */
  plp_id    = plp_id   ; /* To avoid compiler warning if not used */
  plp_type  = plp_type ; /* To avoid compiler warning if not used */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
#ifdef    DEMOD_DVB_C2
    if (front_end->standard == SILABS_DVB_C2) {
      if (Si2183_L1_DVBC2_PLP_INFO(front_end->Si2183_FE->demod, plp_index, Si2183_DVBC2_PLP_INFO_CMD_PLP_INFO_DS_MODE_ANY, ds_id) != NO_Si2183_ERROR) {
        SiTRACE("Si2183_L1_DVBC2_PLP_INFO error when checking PLP index %d!\n", plp_index);
        SiERROR("Si2183_L1_DVBC2_PLP_INFO error!\n");
        return -1;
      }
      *plp_id   = front_end->Si2183_FE->demod->rsp->dvbc2_plp_info.plp_id;
      *plp_type = front_end->Si2183_FE->demod->rsp->dvbc2_plp_info.plp_type;
    }
#endif /* DEMOD_DVB_C2 */
#ifdef    DEMOD_DVB_T2
    if (front_end->standard == SILABS_DVB_T2) {
      if (Si2183_L1_DVBT2_PLP_INFO(front_end->Si2183_FE->demod, plp_index) != NO_Si2183_ERROR) {
        SiTRACE("Si2183_L1_DVBT2_PLP_INFO error when checking PLP index %d!\n", plp_index);
        SiERROR("Si2183_L1_DVBT2_PLP_INFO error!\n");
        return -1;
      }
      *plp_id   = front_end->Si2183_FE->demod->rsp->dvbt2_plp_info.plp_id;
      *plp_type = front_end->Si2183_FE->demod->rsp->dvbt2_plp_info.plp_type;
    }
    SiTRACE("PLP index %3d: PLP ID %3d, PLP TYPE %d\n", plp_index, *plp_id, *plp_type);
#endif /* DEMOD_DVB_T2 */
    return 0;
  }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  NAME: SiLabs_API_Get_PLP_Group_Id
  DESCRIPTION: PLP ID and Goup_id info function for DVB-T2
  Parameter: front_end, Pointer to SILABS_FE_Context
  Parameter:  recall,   a flag to avoid calling Si2183_L1_DVBT2_PLP_INFO again, in case SiLabs_API_Get_PLP_ID_and_TYPE has just been called
                         for the same plp_index (set to 1 to avoid calling the PLP_INFO command twice),
  Parameter:  plp_index, the index of the required PLP (must be lower than num_plp for the selected carrier),
  Parameter: *group_id, a pointer to the group id
  Returns:    0 if no error value, -1 in case of an error
************************************************************************************************************************/
signed   int  SiLabs_API_Get_PLP_Group_Id           (SILABS_FE_Context *front_end,    signed   int recall, signed   int plp_index, signed   int *group_id)
{
  front_end = front_end; /* To avoid compiler warning if not used */
  plp_index = plp_index; /* To avoid compiler warning if not used */
  group_id  = group_id ; /* To avoid compiler warning if not used */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
#ifdef    DEMOD_DVB_T2
    if (front_end->standard == SILABS_DVB_T2) {
      if (recall) {
        if (Si2183_L1_DVBT2_PLP_INFO(front_end->Si2183_FE->demod, plp_index) != NO_Si2183_ERROR) {
          SiTRACE("Si2183_L1_DVBT2_PLP_INFO error when checking PLP index %d!\n", plp_index);
          SiERROR("Si2183_L1_DVBT2_PLP_INFO error!\n");
          return -1;
        }
      }
      *group_id    =(front_end->Si2183_FE->demod->rsp->dvbt2_plp_info.plp_group_id_msb << 4) + front_end->Si2183_FE->demod->rsp->dvbt2_plp_info.plp_group_id_lsb;
    }
    SiTRACE("PLP index %3d: Group ID %3d\n", plp_index, *group_id);
#endif /* DEMOD_DVB_T2 */
    return 0;
  }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  NAME: SiLabs_API_Select_PLP
  DESCRIPTION: PLP selection function for DVB-T2
  Parameter: front_end, Pointer to SILABS_FE_Context
  Parameter:  plp_id, the PLP id of the required PLP (must be lower than num_plp for the selected carrier)
                Use '-1' for auto selection,
  Returns:    0 if no error value, -1 in case of an error
************************************************************************************************************************/
signed   int  SiLabs_API_Select_PLP                 (SILABS_FE_Context *front_end,    signed   int plp_id)
{
  signed   int plp_mode;
  SiTRACE("API CALL LOCK  : SiLabs_API_Select_PLP (front_end, %d);\n", plp_id);
  front_end = front_end;        /* To avoid compiler warning if not used */
  plp_id    = plp_id   ; /* To avoid compiler warning if not used */
  plp_mode  = 0;
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
#ifdef    DEMOD_DVB_T2
    if (front_end->Si2183_FE->demod->rsp->dd_status.modulation == Si2183_DD_STATUS_RESPONSE_MODULATION_DVBT2) {
      if (plp_id < 0) {
        plp_mode = Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_AUTO;
      } else {
        plp_mode = Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MANUAL;
      }
      if (Si2183_L1_DVBT2_PLP_SELECT(front_end->Si2183_FE->demod, plp_id, plp_mode) != NO_Si2183_ERROR) {
        SiTRACE("Si2183_L1_DVBT2_PLP_SELECT error when selecting PLP %d!\n", plp_id);
        SiERROR("Si2183_L1_DVBT2_PLP_SELECT error!\n");
        return -1;
      }
      if (plp_mode == Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_AUTO) { Si2183_L1_DD_RESTART(front_end->Si2183_FE->demod); system_wait(300); }
    }
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_DVB_C2
    if (front_end->Si2183_FE->demod->rsp->dd_status.modulation == Si2183_DD_STATUS_RESPONSE_MODULATION_DVBC2) {
      if (plp_id < 0) {
        front_end->Si2183_FE->demod->cmd->dvbc2_ds_plp_select.id_sel_mode = Si2183_DVBC2_DS_PLP_SELECT_CMD_ID_SEL_MODE_AUTO;
        front_end->Si2183_FE->demod->cmd->dvbc2_ds_plp_select.plp_id      = 0;
      } else {
        front_end->Si2183_FE->demod->cmd->dvbc2_ds_plp_select.id_sel_mode = Si2183_DVBC2_DS_PLP_SELECT_CMD_ID_SEL_MODE_MANUAL;
        front_end->Si2183_FE->demod->cmd->dvbc2_ds_plp_select.plp_id      = plp_id;
      }
      if (Si2183_L1_DVBC2_DS_PLP_SELECT(front_end->Si2183_FE->demod,
                                        front_end->Si2183_FE->demod->cmd->dvbc2_ds_plp_select.ds_id,
                                        front_end->Si2183_FE->demod->cmd->dvbc2_ds_plp_select.id_sel_mode,
                                        front_end->Si2183_FE->demod->cmd->dvbc2_ds_plp_select.plp_id) != NO_Si2183_ERROR) {
        SiTRACE("Si2183_L1_DVBC2_DS_PLP_SELECT error when selecting PLP %d!\n", plp_id);
        SiERROR("Si2183_L1_DVBT2_DS_PLP_SELECT error!\n");
        return -1;
      }
      if (plp_mode == Si2183_DVBC2_DS_PLP_SELECT_CMD_ID_SEL_MODE_AUTO) { Si2183_L1_DD_RESTART(front_end->Si2183_FE->demod); system_wait(300); }
    }
#endif /* DEMOD_DVB_C2 */
    return 0;
  }
#endif /* Si2183_COMPATIBLE */
  plp_id = plp_mode; /* to avoid compiler warning when not used */
  return -1;
}
/************************************************************************************************************************
  NAME: SiLabs_API_Get_AC_DATA
  DESCRIPTION: Auxiliary Channel data retrieval function for ISDB-T
  Parameter: front_end, Pointer to SILABS_FE_Context
  Parameter:  segment_code, the AC data segment selection code,
  Parameter:  read_offset,  the index of the first byte to read,
  Parameter:  bit_count,   the number of bytes to read,
  Parameter: *AC_Data, a pointer to a buffer used to store the AC data bytes.
              It must be declared by the caller with a size greater than 15*( (bit_count/15) +1)
              (it must be a multiple of 15, the number of bytes one can retrieve using Si21xx_L1_ISDBT_AC_BITS)
  Parameter:  freeze_buffer, a flag used to freeze the AC data buffer while reading its content,
  Returns:    the number of AC data bytes, -1 in case of an error
************************************************************************************************************************/
signed   int  SiLabs_API_Get_AC_DATA                (SILABS_FE_Context *front_end,    unsigned char segment, unsigned char filtering, unsigned char read_offset, signed   int bit_count, unsigned char *AC_data)
{
  signed   int freeze_buffer;
  signed   int data_index;
  signed   int bit_index;
  front_end     = front_end    ; /* To avoid compiler warning if not used */
  segment       = segment      ; /* To avoid compiler warning if not used */
  read_offset   = read_offset  ; /* To avoid compiler warning if not used */
  bit_count     = bit_count    ; /* To avoid compiler warning if not used */
  AC_data       = AC_data      ; /* To avoid compiler warning if not used */
  freeze_buffer = 1;
  data_index    = 0;
  bit_index     = 0;
  SiTRACE("SiLabs_API_Get_AC_DATA segment %d, filtering %d, read_offfset %d, bit_count %d\n", segment, filtering, read_offset, bit_count);
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
#ifdef    DEMOD_ISDB_T
    if (front_end->standard == SILABS_ISDB_T ) {
      front_end->Si2183_FE->demod->prop->isdbt_ac_select.segment_sel = segment;
      front_end->Si2183_FE->demod->prop->isdbt_ac_select.filtering   = filtering;
      if (Si2183_L1_SetProperty2(front_end->Si2183_FE->demod, Si2183_ISDBT_AC_SELECT_PROP_CODE) != NO_Si2183_ERROR) {
        SiERROR("SiLabs_API_Get_AC_DATA error when selecting AC data segment!\n");
        return -1;
      }
      while (bit_index < bit_count) {
        if (data_index + 15 >= (bit_count + 7)/8 ) {freeze_buffer = 0;}
        if (Si2183_L1_ISDBT_AC_BITS (front_end->Si2183_FE->demod, read_offset + data_index, freeze_buffer, &(AC_data[data_index]) ) != NO_Si2183_ERROR) {
          SiERROR("SiLabs_API_Get_AC_DATA error when retrieving AC data!\n");
          return -1;
        }
        data_index = data_index + 15;
        bit_index  = data_index * 8;
      }
      /* Limit the return value to the number of bytes required to store all AC bits retrieved */
      if (data_index > (bit_count + 7)/8 ) {data_index = (bit_count + 7)/8;}

      return data_index;
    }
#endif /* DEMOD_ISDB_T */
  }
#endif /* Si2183_COMPATIBLE */
  return -1 + 0*(freeze_buffer*data_index*bit_index); /* Trick to avoid 'set but not used' warning */
}
/************************************************************************************************************************
  NAME: SiLabs_API_TER_AutoDetect
  DESCRIPTION: activation function for the TER auto detect mode
  Parameter: front_end, Pointer to SILABS_FE_Context
  Parameter: on_off, which is set to '0' to de-activate the TER auto-detect feature,
              set to '1' to activate it and to any other value to retrieve the current status
  Returns:    the current state of auto_detect_TER
************************************************************************************************************************/
signed   int  SiLabs_API_TER_AutoDetect             (SILABS_FE_Context *front_end,    signed   int on_off)
{
  front_end = front_end; /* To avoid compiler warning if not used */
  on_off    = on_off;    /* To avoid compiler warning if not used */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
#ifdef    DEMOD_DVB_T2
    if (on_off == 0) { Si2183_TerAutoDetectOff(front_end->Si2183_FE); }
    if (on_off == 1) { Si2183_TerAutoDetect   (front_end->Si2183_FE); }
    return front_end->Si2183_FE->auto_detect_TER;
#endif /* DEMOD_DVB_T2 */
  }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  NAME: SiLabs_API_TER_T2_lock_mode
  DESCRIPTION: selection function for the TER auto detect mode
  Parameter: front_end, Pointer to SILABS_FE_Context
  Parameter: T2_lock_mode        the DVB-T2 lock mode        (0='ANY', 1='T2-Base', 2='T2-Lite')
  Returns:    the current state of the DVB-T2 lock mode (using a value out of the above returns the current value)
************************************************************************************************************************/
signed   int  SiLabs_API_TER_T2_lock_mode           (SILABS_FE_Context *front_end,    signed   int T2_lock_mode)
{
  front_end    = front_end;    /* To avoid compiler warning if not used */
  T2_lock_mode = T2_lock_mode; /* To avoid compiler warning if not used */
#ifdef    Si2183_COMPATIBLE
 #ifdef    DEMOD_DVB_T2
  if (front_end->chip ==   0x2183 ) {
    if (T2_lock_mode == 0) { front_end->Si2183_FE->demod->prop->dvbt2_mode.lock_mode = Si2183_DVBT2_MODE_PROP_LOCK_MODE_ANY;       }
    if (T2_lock_mode == 1) { front_end->Si2183_FE->demod->prop->dvbt2_mode.lock_mode = Si2183_DVBT2_MODE_PROP_LOCK_MODE_BASE_ONLY; }
    if (T2_lock_mode == 2) { front_end->Si2183_FE->demod->prop->dvbt2_mode.lock_mode = Si2183_DVBT2_MODE_PROP_LOCK_MODE_LITE_ONLY; }
    Si2183_L1_SetProperty2(front_end->Si2183_FE->demod, Si2183_DVBT2_MODE_PROP_CODE);
    return front_end->Si2183_FE->demod->prop->dvbt2_mode.lock_mode;
  }
 #endif /* DEMOD_DVB_T2 */
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  NAME: SiLabs_API_TER_ISDBT_Monitoring_mode
  DESCRIPTION: selection function for the TER ISDBT C/N monitoring (the one which will reflect in the c_n status) mode
  Parameter: front_end, Pointer to SILABS_FE_Context
  Parameter: layer_mon        the ISDB-T monitoring mode (0='ALL', 0xA='LAYER_A', 0xB='LAYER_B', 0xC='LAYER_C', 0xABC="loop mode')
  Returns:    the current state of the ISDBT C/N monitoring mode field (using a value out of the above returns the current value)
************************************************************************************************************************/
signed   int  SiLabs_API_TER_ISDBT_Monitoring_mode  (SILABS_FE_Context *front_end,    signed   int layer_mon)
{
  front_end    = front_end; /* To avoid compiler warning if not used */
  layer_mon    = layer_mon; /* To avoid compiler warning if not used */
#ifdef    Si2183_COMPATIBLE
 #ifdef    DEMOD_ISDB_T
  if (front_end->chip ==   0x2183 ) {
    front_end->TER_ISDBT_Monitoring_mode = layer_mon;
    if (layer_mon == 0x0) { front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon = Si2183_ISDBT_MODE_PROP_LAYER_MON_ALL;     }
    if (layer_mon == 0xA) { front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon = Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_A; }
    if (layer_mon == 0xB) { front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon = Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_B; }
    if (layer_mon == 0xC) { front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon = Si2183_ISDBT_MODE_PROP_LAYER_MON_LAYER_C; }
    Si2183_L1_SetProperty2(front_end->Si2183_FE->demod, Si2183_ISDBT_MODE_PROP_CODE);
    return front_end->Si2183_FE->demod->prop->isdbt_mode.layer_mon;
  }
 #endif /* DEMOD_ISDB_T */
#endif /* Si2183_COMPATIBLE */
  return -1;
}
/************************************************************************************************************************
  NAME: SiLabs_API_TER_ISDBT_Layer_Info
  DESCRIPTION: information function for the TER ISDBT Layer information
  Parameter: front_end,    Pointer to SILABS_FE_Context
  Parameter: layer            the ISDB-T Layer to retrieve info about (0xA='LAYER_A', 0xB='LAYER_B', 0xC='LAYER_C')
  Parameter: *constellation   Pointer to the ISDB-T constellation
  Parameter: *code_rate       Pointer to the ISDB-T code rate
  Parameter: *il              Pointer to the ISDB-T interleaving code
  Parameter: *nb_seg          Pointer to the ISDB-T number of segments
  Returns:    0 if OK (-1 otherwise)
************************************************************************************************************************/
signed   int  SiLabs_API_TER_ISDBT_Layer_Info       (SILABS_FE_Context *front_end,    signed   int layer, signed   int *constellation, signed   int *code_rate, signed   int *il, signed   int *nb_seg)
{
  front_end         = front_end; /* To avoid compiler warning if not used */
  *constellation    = 0;         /* To avoid compiler warning if not used */
  *code_rate        = 0;         /* To avoid compiler warning if not used */
  *il               = 0;         /* To avoid compiler warning if not used */
  *nb_seg           = 0;         /* To avoid compiler warning if not used */
#ifdef    Si2183_COMPATIBLE
 #ifdef    DEMOD_ISDB_T
  if (front_end->chip ==   0x2183 ) {
    if (layer == 0xA) { Si2183_L1_ISDBT_LAYER_INFO(front_end->Si2183_FE->demod, Si2183_ISDBT_LAYER_INFO_CMD_LAYER_INDEX_A); }
    if (layer == 0xB) { Si2183_L1_ISDBT_LAYER_INFO(front_end->Si2183_FE->demod, Si2183_ISDBT_LAYER_INFO_CMD_LAYER_INDEX_B); }
    if (layer == 0xC) { Si2183_L1_ISDBT_LAYER_INFO(front_end->Si2183_FE->demod, Si2183_ISDBT_LAYER_INFO_CMD_LAYER_INDEX_C); }
    *constellation = Custom_constelCode  (front_end, front_end->Si2183_FE->demod->rsp->isdbt_layer_info.constellation);
    *code_rate     = Custom_coderateCode (front_end, front_end->Si2183_FE->demod->rsp->isdbt_layer_info.code_rate);
    *il            = front_end->Si2183_FE->demod->rsp->isdbt_layer_info.il;
    *nb_seg        = front_end->Si2183_FE->demod->rsp->isdbt_layer_info.nb_seg;
    return 0;
  }
 #endif /* DEMOD_ISDB_T */
#endif /* Si2183_COMPATIBLE */
  return -1;
}
signed   int  SiLabs_API_TER_Tuner_Fine_Tune        (SILABS_FE_Context *front_end,    signed   int offset_500hz)
{
  front_end    = front_end;    /* To avoid compiler warning if not supported */
  offset_500hz = offset_500hz; /* To avoid compiler warning if not supported */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
   #ifdef    Si2173_L1_FINE_TUNE
    Si2173_L1_FINE_TUNE(front_end->Si2183_FE->tuner_ter, 0, offset_500hz);
   #endif /* Si2173_L1_FINE_TUNE */
   #ifdef    Si2176_L1_FINE_TUNE
    Si2176_L1_FINE_TUNE(front_end->Si2183_FE->tuner_ter, 0, offset_500hz);
   #endif /* Si2176_L1_FINE_TUNE */
   #ifdef    Si2196_L1_FINE_TUNE
    Si2196_L1_FINE_TUNE(front_end->Si2183_FE->tuner_ter, 0, offset_500hz);
   #endif /* Si2196_L1_FINE_TUNE */
    return 1;
  }
#endif /* Si2183_COMPATIBLE */
  return -1;
}
signed   int  SiLabs_API_TER_Tuner_Init             (SILABS_FE_Context *front_end)
{
  front_end = front_end; /* To avoid compiler warning if not supported */
#ifdef    TER_TUNER_INIT
  SiLabs_API_TER_Tuner_I2C_Enable (front_end);
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { TER_TUNER_INIT(front_end->Si2183_FE->tuner_ter); front_end->Si2183_FE->TER_tuner_init_done = 1; return 1; }
#endif /* Si2183_COMPATIBLE */
  SiLabs_API_TER_Tuner_I2C_Disable(front_end);
#endif /* TER_TUNER_INIT */
  return -1;
}
signed   int  SiLabs_API_TER_Tuner_SetMFT           (SILABS_FE_Context *front_end,    signed   int nStep)
{
  signed   int           nCriteriaStep;
  signed   int           nLeftMax;
  signed   int           nRightMax;
  signed   int           nReal_Step;
  signed   int           nBeforeStep;
  front_end = front_end; /* To avoid compiler warning if not supported */
  nStep     = nStep;     /* To avoid compiler warning if not supported */

  nCriteriaStep = front_end->TER_Tuner_Cfg.nCriteriaStep;
  nLeftMax      = front_end->TER_Tuner_Cfg.nLeftMax;
  nRightMax     = front_end->TER_Tuner_Cfg.nReal_Step;
  nReal_Step    = front_end->TER_Tuner_Cfg.nReal_Step;
  nBeforeStep   = front_end->TER_Tuner_Cfg.nBeforeStep;

  if      (nStep == 32 && nBeforeStep == -32){
    SiLabs_API_TER_Tuner_Fine_Tune (front_end, -4000);
    nReal_Step = nRightMax - nCriteriaStep;
  }else if(nStep == -32 && nBeforeStep == 32){
    SiLabs_API_TER_Tuner_Fine_Tune (front_end,  4000);
    nReal_Step = nLeftMax - nCriteriaStep;
  }else{
    if (nCriteriaStep<0) nCriteriaStep = -nCriteriaStep;
    if(nStep > nRightMax)
      nReal_Step = nRightMax + nCriteriaStep;
    else if(nStep < nLeftMax)
      nReal_Step = nLeftMax  - nCriteriaStep;
    else
      nReal_Step = nStep - nCriteriaStep;

    if(nReal_Step > 32)
      nReal_Step = 32;
    else if(nReal_Step < -32)
      nReal_Step = -32;
  }

  SiLabs_API_TER_Tuner_Fine_Tune (front_end, -(125*nReal_Step));

  nBeforeStep = nStep;

  return 1;
}
signed   int  SiLabs_API_TER_Tuner_Text_status      (SILABS_FE_Context *front_end,    char *separator, char *msg)
{
  front_end = front_end; /* To avoid compiler warning */
  separator = separator; /* To avoid compiler warning */
  msg       = msg;       /* To avoid compiler warning */
  SiLabs_API_TER_Tuner_I2C_Enable (front_end);
#ifdef    TER_TUNER_SILABS
  #ifdef    Si2183_COMPATIBLE
    if (front_end->chip ==   0x2183 ) { return SiLabs_TER_Tuner_Text_STATUS (front_end->Si2183_FE->tuner_ter , separator, msg); }
  #endif /* Si2183_COMPATIBLE */
#endif  /* TER_TUNER_SILABS */
  SiLabs_API_TER_Tuner_I2C_Disable(front_end);
  return -1;
}
signed   int  SiLabs_API_TER_Tuner_ATV_Text_status  (SILABS_FE_Context *front_end,    char *separator, char *msg)
{
  front_end = front_end; /* To avoid compiler warning if not used */
  separator = separator; /* To avoid compiler warning if not used */
  msg       = msg      ; /* To avoid compiler warning if not used */
  SiLabs_API_TER_Tuner_I2C_Enable (front_end);
#ifdef    TER_TUNER_SILABS
  #ifdef    Si2183_COMPATIBLE
    if (front_end->chip ==   0x2183 ) { return SiLabs_TER_Tuner_ATV_Text_STATUS (front_end->Si2183_FE->tuner_ter , separator, msg); }
  #endif /* Si2183_COMPATIBLE */
#endif /* TER_TUNER_SILABS */
  SiLabs_API_TER_Tuner_I2C_Disable(front_end);
  return -1;
}
signed   int  SiLabs_API_TER_Tuner_DTV_Text_status  (SILABS_FE_Context *front_end,    char *separator, char *msg)
{
  front_end = front_end; /* To avoid compiler warning */
  separator = separator; /* To avoid compiler warning */
  msg       = msg;       /* To avoid compiler warning */
#ifdef    TER_TUNER_SILABS
  #ifdef    Si2183_COMPATIBLE
    if (front_end->chip ==   0x2183 ) { return SiLabs_TER_Tuner_DTV_Text_STATUS (front_end->Si2183_FE->tuner_ter , separator, msg); }
  #endif /* Si2183_COMPATIBLE */
#endif /* TER_TUNER_SILABS */
  return -1;
}
signed   int  SiLabs_API_TER_Tuner_ATV_Tune         (SILABS_FE_Context *front_end)
{
  unsigned long freq;
  unsigned char video_sys;
  unsigned char trans;
  unsigned char color;
  unsigned char invert_signal;
  unsigned char invert_spectrum;

  freq            = front_end->Carrier_Cfg.freq;
  video_sys       = Silabs_videoSysCode    (front_end, front_end->Analog_Cfg.video_sys);
  trans           = Silabs_transmissionCode(front_end, front_end->Analog_Cfg.trans);
  color           = Silabs_colorCode       (front_end, front_end->Analog_Cfg.color);
  invert_signal   = front_end->Analog_Cfg.invert_signal;
  invert_spectrum = front_end->Analog_Cfg.invert_spectrum;

  SiTRACE("freq %ld, video_sys %d, trans %d\n", freq, video_sys, trans);

  /* Using Center frequency for ATV */
  switch (video_sys) {
    case SILABS_VIDEO_SYS_B  :
      freq += 2250000;
      break;
    case SILABS_VIDEO_SYS_M  :
    case SILABS_VIDEO_SYS_N  :
      freq += 1750000;
      break;
    case SILABS_VIDEO_SYS_GH :
    case SILABS_VIDEO_SYS_I  :
    case SILABS_VIDEO_SYS_DK :
    case SILABS_VIDEO_SYS_L  :
      freq += 2750000;
      break;
    case SILABS_VIDEO_SYS_LP :
      freq -= 2750000;
      break;
    default: {
      SiERROR("SiLabs_API_TER_Tuner_ATV_Tune: unknown video_sys\n");
      return -1;
    }
  }
  /* Center frequency end */

  SiLabs_API_TER_Tuner_I2C_Enable (front_end);
#ifdef    TER_TUNER_SILABS
  #ifdef    Si2183_COMPATIBLE
    if (front_end->chip == 0x2183 ) { SiLabs_TER_Tuner_ATVTune (front_end->Si2183_FE->tuner_ter , freq, video_sys, trans, color, invert_signal); }
  #endif /* Si2183_COMPATIBLE */
#endif /* TER_TUNER_SILABS */
  SiLabs_API_TER_Tuner_I2C_Disable(front_end);
  freq = invert_signal = invert_spectrum = color = trans = video_sys = -1; /* Setting all variables to avoid warning when not used */
  return freq;
}
signed   int  SiLabs_API_TER_Tuner_DTV_Tune         (SILABS_FE_Context *front_end,    unsigned long freq, unsigned char bw, unsigned char modulation)
{
  SiLabs_API_TER_Tuner_I2C_Enable (front_end);
#ifdef    TER_TUNER_SILABS
  #ifdef    Si2183_COMPATIBLE
    if (front_end->chip == 0x2183 ) { SiLabs_TER_Tuner_DTVTune (front_end->Si2183_FE->tuner_ter , freq, bw, modulation); }
  #endif /* Si2183_COMPATIBLE */
#endif /* TER_TUNER_SILABS */
  SiLabs_API_TER_Tuner_I2C_Disable(front_end);
  freq = bw = modulation = -1; /* Setting all variables to avoid warning when not used */
  return freq;
}
signed   int  SiLabs_API_TER_Tuner_SetProperty      (SILABS_FE_Context *front_end,    unsigned int prop_code, int   data)
{
  int res = 0;
  SiLabs_API_TER_Tuner_I2C_Enable (front_end);
#ifdef    TER_TUNER_SILABS
  #ifdef    Si2183_COMPATIBLE
    if (front_end->chip == 0x2183 ) { res = SiLabs_TER_Tuner_Set_Property (front_end->Si2183_FE->tuner_ter , prop_code, data); }
  #endif /* Si2183_COMPATIBLE */
#endif /* TER_TUNER_SILABS */
  SiLabs_API_TER_Tuner_I2C_Disable(front_end);
  prop_code = data = -1; /* Setting all variables to avoid warning when not used */
  return res;
}
signed   int  SiLabs_API_TER_Tuner_GetProperty      (SILABS_FE_Context *front_end,    unsigned int prop_code, int  *data)
{
  int res;
  *data = prop_code;
  res = -1; /* Setting data to avoid warning when not used */
  SiLabs_API_TER_Tuner_I2C_Enable (front_end);
#ifdef    TER_TUNER_SILABS
  #ifdef    Si2183_COMPATIBLE
    if (front_end->chip == 0x2183 ) { res = SiLabs_TER_Tuner_Get_Property (front_end->Si2183_FE->tuner_ter , prop_code, data); }
  #endif /* Si2183_COMPATIBLE */
#endif /* TER_TUNER_SILABS */
  SiLabs_API_TER_Tuner_I2C_Disable(front_end);
  if (res == -1) {*data = -1;}
  return res;
}
signed   int  SiLabs_API_TER_Tuner_Block_VCO        (SILABS_FE_Context *front_end,    signed   int vco_code)
{
  front_end = front_end; /* To avoid compiler warning */
  vco_code  = vco_code;  /* To avoid compiler warning */
  SiLabs_API_TER_Tuner_I2C_Enable (front_end);
#ifdef    TER_TUNER_SILABS
  #ifdef    Si2183_COMPATIBLE
    if (front_end->chip ==   0x2183 ) { SiLabs_TER_Tuner_Block_VCO_Code (front_end->Si2183_FE->tuner_ter , vco_code); }
  #endif /* Si2183_COMPATIBLE */
#endif /* TER_TUNER_SILABS */
  SiLabs_API_TER_Tuner_I2C_Disable(front_end);
  return 1;
}
signed   int  SiLabs_API_TER_Tuner_Block_VCO2       (SILABS_FE_Context *front_end,    signed   int vco_code)
{
  front_end = front_end; /* To avoid compiler warning */
  vco_code  = vco_code;  /* To avoid compiler warning */
  SiLabs_API_TER_Tuner_I2C_Enable (front_end);
#ifdef    TER_TUNER_SILABS
  #ifdef    Si2183_COMPATIBLE
    if (front_end->chip ==   0x2183 ) { SiLabs_TER_Tuner_Block_VCO2_Code (front_end->Si2183_FE->tuner_ter , vco_code); }
  #endif /* Si2183_COMPATIBLE */
#endif /* TER_TUNER_SILABS */
  SiLabs_API_TER_Tuner_I2C_Disable(front_end);
  return 1;
}
signed   int  SiLabs_API_TER_Tuner_Block_VCO3       (SILABS_FE_Context *front_end,    signed   int vco_code)
{
  front_end = front_end; /* To avoid compiler warning */
  vco_code  = vco_code;  /* To avoid compiler warning */
  SiLabs_API_TER_Tuner_I2C_Enable (front_end);
#ifdef    TER_TUNER_SILABS
  #ifdef    Si2183_COMPATIBLE
    if (front_end->chip ==   0x2183 ) { SiLabs_TER_Tuner_Block_VCO3_Code (front_end->Si2183_FE->tuner_ter , vco_code); }
  #endif /* Si2183_COMPATIBLE */
#endif /* TER_TUNER_SILABS */
  SiLabs_API_TER_Tuner_I2C_Disable(front_end);
  return 1;
}
signed   int  SiLabs_API_TER_Tuner_Standby          (SILABS_FE_Context *front_end)
{
  SiTRACE("SiLabs_API_TER_Tuner_Standby\n");

#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    SiLabs_TER_Tuner_Standby(front_end->Si2183_FE->tuner_ter);
  }
#endif /* Si2183_COMPATIBLE */

  return 1;
}
/************************************************************************************************************************
  SiLabs_API_TER_Tuner_I2C_Enable function
  Use:      Demod Loop through control function,
            Used to switch the I2C loopthrough on, allowing communication with the tuners
            This function can control the I2C passthrough for any front-end in the front-end table,
             and is useful mainly in multi-front-end applications with dual tuners or dual demodulators,
             when the TER tuner I2C is not directly connected to the corresponding demodulator.
  Return:    the final mode (-1 if not known)
************************************************************************************************************************/
signed   int  SiLabs_API_TER_Tuner_I2C_Enable       (SILABS_FE_Context *front_end)
{
#ifdef    INDIRECT_I2C_CONNECTION
  signed   int fe;
  signed   int requester;
  signed   int connecter;
  signed   int fe_count;
  fe_count = FRONT_END_COUNT;
  for (fe=0; fe< fe_count; fe++) {
    if ( front_end  == &(FrontEnd_Table[fe]) ) {
      requester = fe;
      connecter = front_end->TER_tuner_I2C_connection;
      if (connecter == 100) {
        /* 100 is a special value to allow having tuners connected directly.                                   */
        /* If tuners are connected directly, the i2c pass-through should NOT be closed, to avoid i2c deadlock. */
        return 1;
      }
      SiTRACE("-- I2C -- SiLabs_API_TER_Tuner_I2C_Enable  request for front_end %d via front_end %d\n", requester, connecter);
      if (connecter < fe_count) {
        if (requester != connecter) {
      SiTRACE("-- I2C -- Enabling  indirect TER tuner connection  for front_end %d via front_end %d\n", requester, connecter);
        }
        return SiLabs_API_Tuner_I2C_Enable(&(FrontEnd_Table[connecter]) );
      }
      break;
    }
  }
  SiTRACE("-- I2C -- SiLabs_API_TER_Tuner_I2C_Enable  request failed! Unable to find a match for the caller front_end! (0x%08x)\n", (int)front_end);
  SiERROR("-- I2C -- SiLabs_API_TER_Tuner_I2C_Enable  request failed! Unable to find a match for the caller front_end!\n");
  return 0;
#endif /* INDIRECT_I2C_CONNECTION */
  return SiLabs_API_Tuner_I2C_Enable(front_end);
}
/************************************************************************************************************************
  SiLabs_API_TER_Tuner_I2C_Disable function
  Use:      Demod Loop through control function,
            Used to switch the I2C loopthrough off, disabling communication with the TER tuner
            This function can control the I2C passthrough for any front-end in the front-end table,
             and is useful mainly in multi-front-end applications with dual tuners or dual demodulators,
             when the TER tuner I2C is not directly connected to the corresponding demodulator.
  Return:    the final mode (-1 if not known)
************************************************************************************************************************/
signed   int  SiLabs_API_TER_Tuner_I2C_Disable      (SILABS_FE_Context *front_end)
{
#ifdef    INDIRECT_I2C_CONNECTION
  signed   int fe;
  signed   int requester;
  signed   int connecter;
  signed   int fe_count;
  fe_count = FRONT_END_COUNT;
  for (fe=0; fe< fe_count; fe++) {
    if ( front_end  == &(FrontEnd_Table[fe]) ) {
      requester = fe;
      connecter = front_end->TER_tuner_I2C_connection;
      if (connecter == 100) {
        /* 100 is a special value to allow having tuners connected directly.                                   */
        /* If tuners are connected directly, the i2c pass-through should NOT be closed, to avoid i2c deadlock. */
        return 1;
      }
      SiTRACE("-- I2C -- SiLabs_API_TER_Tuner_I2C_Disable request for front_end %d via front_end %d\n", requester, connecter);
      if (connecter < fe_count) {
        if (requester != connecter) {
      SiTRACE("-- I2C -- Disabling indirect TER tuner connection  for front_end %d via front_end %d\n", requester, connecter);
        }
        return SiLabs_API_Tuner_I2C_Disable(&(FrontEnd_Table[connecter]) );
      }
      break;
    }
  }
  SiTRACE("-- I2C -- SiLabs_API_TER_Tuner_I2C_Disable request failed! Unable to find a match for the caller front_end! (0x%08x)\n", (int)front_end);
  SiERROR("-- I2C -- SiLabs_API_TER_Tuner_I2C_Disable request failed! Unable to find a match for the caller front_end!\n");
  return 0;
#endif /* INDIRECT_I2C_CONNECTION */
  return SiLabs_API_Tuner_I2C_Disable(front_end);
}
#endif /* TERRESTRIAL_FRONT_END */
#ifndef   NO_FLOATS_ALLOWED
#ifndef    log10
/***********************************************************************************************************************
  Silabs_Log10 function
  Use:        using log values without the need for math.h
              Used to avoid the inclusion of the C math functions header
  Porting:    If more accuracy is required, insert additional values in the valx and log10x tables and increase table sizes accordingly.
              For example, if the accuracy between 1.1 and 1.3 is not sufficient, add 1.2 between 1.1 and 1.3 in valx
              Knowing that log10(1.2) = 7.9181e-2, add  7.9181e-2 between 4.1393e-2 and 1.1394e-1 in log10x.
  Returns:    a float value corresponding to log10(x)
  Returns:    -1000 if error (negative or null input value)
 ***********************************************************************************************************************/
double        Silabs_Log10                          (double x)
{
    double valx[10]   = {1.0        , 1.1      , 1.3      , 1.7      , 2.5      , 4.1      , 5.9       , 7.3      , 8.7      , 10.0 };
    double log10x[10] = {0          , 4.1393e-2, 1.1394e-1, 2.3045e-1, 3.9794e-1, 6.1278e-1, 7.7085e-1 , 8.6332e-1, 9.3951e-1,  1.0  };
    signed   int   c;
    signed   int   logindex;
    if (x<=0) return -1000;
    c = 0;
    if (x<1) {
        while (x<1) {
            x = x*10.0;
            c--;
        }
    } else if ((int)(x - 1.0)==0) {
        return 0;
    } else {
        while (x>=10) {
            x = x/10.0;
            c++;
        }
    }

    if ((int)(x*100000 - 100000.0)==0) return c;

    /* At this stage, 1 < x < 10, with : x = x_initial*10^c ==> log10(x_initial) = c + log10(x) */
    for (logindex = 0; logindex < 8; logindex ++) {if (valx[logindex] >= x) break;}

    return  c + log10x[logindex-1] + (x-valx[logindex-1])/(valx[logindex]-valx[logindex-1])*(log10x[logindex]-log10x[logindex-1]);
}
#define   log10   Silabs_Log10
#endif /* log10 */
#endif /* NO_FLOATS_ALLOWED */
/***********************************************************************************************************************
  Silabs_Log10_10000 function
  Use:        using log values without the need for math.h or use of floats
              Used to avoid the inclusion of the C math functions header
              x must be between 10 and 99
  Porting:    If more accuracy is required, insert additional values in the valx and log10x tables and increase table sizes accordingly.
              For example, if the accuracy between 11 and 13 is not sufficient, add 12 between 11 and 13 in valx
              Knowing that log10(12) = 1.079181, add  10792 between 10414 and 11394 in log10x_1000.
  Returns:    an int value corresponding to log10(x)*10000
  Returns:    -1 if error (negative or null input value)
 ***********************************************************************************************************************/
signed   int  Silabs_Log10_10000                    (signed   int x)
{
    signed   int   valx[11]        = { 9   , 10   , 11   , 13   , 17   , 25   , 41   , 59   , 73   , 87   , 100   };
    signed   int   log10x_1000[11] = {9542 , 10000, 10414, 11139, 12304, 13979, 16127, 17708, 18633, 19395, 20000 };
    signed   int   c;
    signed   int   logindex;
    signed   int   res;

    if (x<10) return -1000;
    c = 0;
    if (x>100) {
      while (x>100) {
        x = (x+5)/10;
        c++;
      }
    }

    /* At this stage, 10 < x < 100, with : x_initial = x*10^c ==> log10(x_initial) = c + log10(x) */
    for (logindex = 1; logindex < 8; logindex ++) {if (valx[logindex] >= x) break;}
    res = (c*10000 + log10x_1000[logindex-1] + ((log10x_1000[logindex]-log10x_1000[logindex-1])*(x-valx[logindex-1]))/(valx[logindex]-valx[logindex-1]));

    return res;
}
#ifndef   NO_FLOATS_ALLOWED
signed   int  SiLabs_API_SSI_SQI                    (signed   int standard, signed   int locked, signed   int Prec, signed   int constellation, signed   int code_rate, double CNrec, double ber, signed   int *ssi, signed   int *sqi)
{
  signed   int constel;
  signed   int rate;
  signed   int ber_sqi;
  double Prel;
  double CNrel;

    signed   int    Pref_DVBC  [5] =  /* DVB-C reference levels for each constellation */
/* QAM         16    32    64   128   256  */
/* LEVEL */{  -78,  -75,  -72,  -69,  -65  };
    double CNref_DVBC [5] =
/* QAM         16    32    64   128   256  */
/* LEVEL */{  20.0, 23.0, 26.0, 29.0, 32.0 };

    signed   int    Pref_DVBS  [1][5] = {
/*            1/2  2/3  3/4  5/6  7/8    */
/* QPSK  */{  -85, -83, -82, -81, -80 },
    };
    double CNref_DVBS [1][5] = {
/*            1/2  2/3  3/4  5/6  7/8    */
/* QPSK  */{  3.8, 5.6, 6.7, 7.7, 8.4 },
    };
    signed   int    Pref_DVBS2 [2][8] = {
/*            1/2  3/5  2/3  3/4  4/5  5/6  8/9  9/10 */
/* QPSK  */{  -85, -84, -83, -82, -81, -81, -80, -80 },
/* 8PSK  */{    0, -80, -79, -78,   0, -77, -76, -76 }
    };
    double CNref_DVBS2[2][8] = {
/*            1/2  3/5  2/3  3/4  4/5  5/6  8/9  9/10 */
/* QPSK  */{  2.0, 3.2, 4.1, 5.0, 5.7, 6.2, 7.2, 7.4 },
/* 8PSK  */{    0, 6.5, 7.6, 8.9,   0,10.4,11.7,12.0 }
    };
    signed   int    Pref_DVBC2 [5][6] = {
/*              2/3  3/4  4/5  5/6  8/9  9/10 */
/* QAM16   */{    0,   0, -83,   0, -81, -81 },
/* QAM64   */{  -80,   0, -77,   0, -75, -75 },
/* QAM256  */{    0, -73,   0, -71, -69, -69 },
/* QAM1024 */{    0, -68,   0, -65, -62, -62 },
/* QAM4096 */{  -59, -59, -59, -59, -53, -53 },
    };
    double CNref_DVBC2[5][7] = {
/*              2/3  3/4  4/5  5/6  8/9  9/10 */
/* QPAM16  */{    0,   0,12.7,   0,14.6,14.8 },
/* QAM64   */{ 15.4,   0,18.0,   0,20.4,20.5 },
/* QAM256  */{    0,22.0,   0,24.1,26.2,26.3 },
/* QAM1024 */{    0,27.1,   0,30.1,33.2,33.3 },
/* QAM4096 */{    0,   0,   0,36.4,42.4,42.8 },
    };

  *ssi = *sqi = 0;

  /* The API returns '-1' when BER is not available, so set ber to 1.0 in this case */
  if (ber < 0.0) {ber = 1.0;}

  SiTRACE_X("SiLabs_API_SSI_SQI standard %8d, constellation %8d, code_rate %8d, Prec %3d, CNrec %6.3f, ber %5.2e\n"
          , standard
          , constellation
          , code_rate
          , Prec
          , CNrec
          , ber);
  SiTRACE_X("SiLabs_API_SSI_SQI standard %8s, constellation %8s, code_rate %8s, Prec %3d, CNrec %6.3f, ber %5.2e\n"
          , Silabs_Standard_Text((CUSTOM_Standard_Enum) standard     )
          , Silabs_Constel_Text ((CUSTOM_Constel_Enum)  constellation)
          , Silabs_Coderate_Text((CUSTOM_Coderate_Enum) code_rate    )
          , Prec
          , CNrec
          , ber);

    switch (standard) {
      case SILABS_MCNS:
      case SILABS_DVB_C : {
        if (locked) {
          switch (constellation) {
            case SILABS_QAM16 :  constel = 0; break;
            case SILABS_QAM32 :  constel = 1; break;
            case SILABS_QAM64 :  constel = 2; break;
            case SILABS_QAM128:  constel = 3; break;
            case SILABS_QAM256:  constel = 4; break;
            default:             constel = 4; break;
          }
        } else {
          constel = 4;
        }
        /* Compute DVB-C SSI */
        Prel = Prec - Pref_DVBC[constel];
        if (locked) {
          SiTRACE_X("DVBC SSI: Prel  = Prec  - Pref[%d] = %6.2f dBm + %6.2f dB = %6.2f dBm\n",            constel, 1.0*Prec, -1.0*Pref_DVBC[constel], Prel);
        } else {
          SiTRACE_X("DVBC SSI: Prel  = Prec  - Pref[%d] = %6.2f dBm + %6.2f dB = %6.2f dBm (unlocked)\n", constel, 1.0*Prec, -1.0*Pref_DVBC[constel], Prel);
        }
               if (Prel < -15) {
          *ssi = 0;
        } else if (Prel < 0)  {
          *ssi = (int)((Prel + 15.0)*2.0/3.0);
        } else if (Prel < 20) {
          *ssi = (int)(Prel*4 + 10.0);
        } else if (Prel < 35) {
          *ssi = (int)((Prel -20.0)*2.0/3.0 + 90);
        } else                {
          *ssi = 100;
        }
        /* Compute DVB-C SQI */
        if (locked) {
          CNrel = CNrec - CNref_DVBC[constel];
          SiTRACE_X("DVBC SQI: CNrel = CNrec - CNref[%d] = %6.2f dB - %6.2f dB = %6.2f dB \n", constel, CNrec,  1.0*CNref_DVBC[constel], CNrel);
          if (CNrel < -7) {
            *sqi = 0;
          } else {
            if (ber < 1e-7) {
              ber_sqi = 100;
            } else if (ber < 1e-3) {
              ber_sqi = (int)(-20*log10(ber) -40);
            } else    {
              ber_sqi = 0;
            }
            if (CNrel < 3) {
              *sqi = (int)(((CNrel -3.0)/10.0 + 1.0)*ber_sqi);
            } else                {
              *sqi = ber_sqi;
            }
          }
        } else {
          SiTRACE_X("DVBC SQI: unlocked: SQI = 0\n");
          *sqi = 0;
        }
        break;
      }
      case SILABS_DVB_C2: {
        switch (constellation) {
          case SILABS_QAM16  :  constel = 0; break;
          case SILABS_QAM64  :  constel = 1; break;
          case SILABS_QAM256 :  constel = 2; break;
          case SILABS_QAM1024:  constel = 3; break;
          case SILABS_QAM4096:  constel = 4; break;
          default:              constel = 4; break;
        }
        switch (code_rate)     {
          case SILABS_CODERATE_2_3: rate = 0; break;
          case SILABS_CODERATE_3_4: rate = 1; break;
          case SILABS_CODERATE_4_5: rate = 2; break;
          case SILABS_CODERATE_5_6: rate = 3; break;
          case SILABS_CODERATE_8_9: rate = 4; break;
          case SILABS_CODERATE_9_10:rate = 5; break;
          default:                  rate = 0; break;
        }
        /* Compute DVB-C2 SSI */
        if (Pref_DVBC2[constel][rate] == 0) {
            SiTRACE_X("DVBC2 SQI: invalid Pref_DVBC2[%d][%d] : %d\n", constel, rate, Pref_DVBC2[constel][rate]);
          *ssi = 0;
        } else {
          Prel = Prec - Pref_DVBC2[constel][rate];
          if (locked) {
            SiTRACE_X("DVBC2 SSI: Prel  = Prec  - Pref[%d] = %6.2f dBm + %6.2f dB = %6.2f dB\n",            constel, 1.0*Prec, -1.0*Pref_DVBC2[constel][rate], Prel);
          } else {
            SiTRACE_X("DVBC2 SSI: Prel  = Prec  - Pref[%d] = %6.2f dBm + %6.2f dB = %6.2f dB (unlocked)\n", constel, 1.0*Prec, -1.0*Pref_DVBC2[constel][rate], Prel);
          }
                 if (Prel < -15) {
            *ssi = 0;
          } else if (Prel < 0)  {
            *ssi = (int)((Prel + 15.0)*2.0/3.0);
          } else if (Prel < 20) {
            *ssi = (int)(Prel*4 + 10.0);
          } else if (Prel < 35) {
            *ssi = (int)((Prel -20.0)*2.0/3.0 + 90);
          } else                {
            *ssi = 100;
          }
        }
        /* Compute DVB-C2 SQI */
        if (locked) {
          if ( CNref_DVBC2[constel][rate] == 0) {
            SiTRACE_X("DVBC2 SQI: invalid CNref_DVBC2[%d][%d] : %f\n", constel, rate, CNref_DVBC2[constel][rate]);
            *sqi = 0;
          } else {
            CNrel = CNrec - CNref_DVBC2[constel][rate];
            SiTRACE_X("DVBC2 SQI: CNrel = CNrec - CNref[%d] = %6.2f dB - %6.2f dB = %6.2f dB \n", constel, CNrec,  1.0*CNref_DVBC2[constel][rate], CNrel);
            if (CNrel < -3) {
              *sqi = 0;
            } else {
              if (ber < 1e-7) {
                ber_sqi = 100/6;
              } else if (ber < 1e-4) {
                ber_sqi = (int)(100/15);
              } else    {
                ber_sqi = 0;
              }
              if (CNrel < 3) {
                *sqi = (int)((CNrel +3.0)*ber_sqi);
              } else                {
                *sqi = 100;
              }
            }
          }
        } else {
          SiTRACE_X("DVBC2 SQI: unlocked: SQI = 0\n");
          *sqi = 0;
        }
        break;
      }
      case SILABS_DVB_S : {
        switch (constellation) {
          case SILABS_QPSK:  constel = 0; break;
          default:           constel = 0; break;
        }
        switch (code_rate)     {
          case SILABS_CODERATE_1_2: rate = 0; break;
          case SILABS_CODERATE_2_3: rate = 1; break;
          case SILABS_CODERATE_3_4: rate = 2; break;
          case SILABS_CODERATE_5_6: rate = 3; break;
          case SILABS_CODERATE_7_8: rate = 4; break;
          default:                  rate = 0; break;
        }
        /* Compute DVB-S SSI */
        if (locked) {
          Prel = Prec - Pref_DVBS[constel][rate];
          SiTRACE_X("DVBS SSI: Prel  = Prec  - Pref[%d][%d]  = %6.2f dBm + %6.2f dB  = %6.2f dB\n", constel, rate, 1.0*Prec, -1.0*Pref_DVBS[constel][rate], Prel);
        } else {
          Prel = Prec - Pref_DVBS[0][4];
          SiTRACE_X("DVBS SSI: Prel  = Prec  - Pref[%d][%d]  = %6.2f dBm + %6.2f dB  = %6.2f dB (unlocked)\n", constel, rate, 1.0*Prec, -1.0*Pref_DVBS[constel][rate], Prel);
        }
               if (Prel < -15) {
          *ssi = 0;
        } else if (Prel < 0)  {
          *ssi = (int)((Prel + 15.0)*2.0/3.0);
        } else if (Prel < 20) {
          *ssi = (int)(Prel*4 + 10.0);
        } else if (Prel < 35) {
          *ssi = (int)((Prel -20.0)*2.0/3.0 + 90);
        } else                {
          *ssi = 100;
        }
        /* Compute DVB-S SQI */
        if (locked) {
          CNrel = CNrec - CNref_DVBS[constel][rate];
          SiTRACE_X("DVBS SQI: CNrel = CNrec - CNref[%d][%d] = %6.2f dB - %6.2f dB = %6.2f dB \n", constel, rate, CNrec,  1.0*CNref_DVBS[constel][rate], CNrel);
          if (CNrel < -7) {
            *sqi = 0;
          } else {
            if (ber < 1e-7) {
              ber_sqi = 100;
            } else if (ber < 1e-3) {
              ber_sqi = (int)(-20*log10(ber) -40);
            } else    {
              ber_sqi = 0;
            }
            if (CNrel < 3) {
              *sqi = (int)(((CNrel -3.0)/10.0 + 1.0)*ber_sqi);
            } else                {
              *sqi = ber_sqi;
            }
          }
        } else {
          SiTRACE_X("DVBS SQI: unlocked: SQI = 0\n");
          *sqi = 0;
        }
        break;
      }
      case SILABS_DVB_S2: {
        switch (constellation) {
          case SILABS_QPSK:  constel = 0; break;
          case SILABS_8PSK:  constel = 1; break;
          default:           constel = 0; break;
        }
        switch (code_rate)     {
          case SILABS_CODERATE_1_2: rate = 0; break;
          case SILABS_CODERATE_3_5: rate = 1; break;
          case SILABS_CODERATE_2_3: rate = 2; break;
          case SILABS_CODERATE_3_4: rate = 3; break;
          case SILABS_CODERATE_4_5: rate = 4; break;
          case SILABS_CODERATE_5_6: rate = 5; break;
          case SILABS_CODERATE_8_9: rate = 6; break;
          case SILABS_CODERATE_9_10:rate = 7; break;
          default:                  rate = 0; break;
        }
        /* Compute DVB-S2 SSI */
        if (locked){
          Prel = Prec - Pref_DVBS2[constel][rate];
          SiTRACE_X("DVBS2 SSI: Prel  = Prec  - Pref[%d][%d]  = %6.2f dBm + %6.2f dB = %6.2f dB\n", constel, rate, 1.0*Prec, -1.0*Pref_DVBS2[constel][rate], Prel);
        } else {
          Prel = Prec - Pref_DVBS2[0][7];
          SiTRACE_X("DVBS2 SSI: Prel  = Prec  - Pref[%d][%d]  = %6.2f dBm + %6.2f dB = %6.2f dB (unlocked)\n", constel, rate, 1.0*Prec, -1.0*Pref_DVBS2[constel][rate], Prel);
        }
               if (Prel < -15) {
          *ssi = 0;
        } else if (Prel < 0)  {
          *ssi = (int)((Prel + 15.0)*2.0/3.0);
        } else if (Prel < 20) {
          *ssi = (int)(Prel*4 + 10.0);
        } else if (Prel < 35) {
          *ssi = (int)((Prel -20.0)*2.0/3.0 + 90);
        } else                {
          *ssi = 100;
        }
        /* Compute DVB-S2 SQI */
        if (locked) {
          CNrel = CNrec - CNref_DVBS2[constel][rate];
          SiTRACE_X("DVBS2 SQI: CNrel = CNrec - CNref[%d][%d] = %6.2f dB  - %6.2f dB = %6.2f dB\n", constel, rate, CNrec, 1.0*CNref_DVBS2[constel][rate], CNrel);
                 if (CNrel < -3) {
            *sqi = 0;
          } else if (CNrel < 3) {
            if (ber < 1e-7) {
              ber_sqi = 100/6;
            } else if (ber < 1e-4) {
              ber_sqi = 100/15;
            } else    {
              ber_sqi = 0;
            }
            *sqi = (int)((CNrel + 3 )*ber_sqi);
          } else                {
            *sqi = 100;
          }
        } else {
          SiTRACE_X("DVBS2 SQI: unlocked: SQI = 0\n");
          *sqi = 0;
        }
        break;
      }
      default           : {
        SiTRACE_X("SiLabs_API_SSI_SQI does not work for standard %2d (%s)\n", standard, Silabs_Standard_Text((CUSTOM_Standard_Enum)standard));
        break;
      }
    }
    SiTRACE_X("SiLabs_API_SSI_SQI SSI %3d, SQI %3d\n", *ssi, *sqi);
    return 1;
}

double   ISDB_T_c_n_corrected(SILABS_FE_Context *front_end, int constellation, int guard_interval, double c_n) {
 /* maximum c_n value reported is 35dB as demodulator register cn saturates for tester C/N more than 35dB*/
 /* minimum reported value is 4dB as register cn remains at 5 for tester C/N less than 4dB */
 /* accuracy is expected within +/-1dB for tester C/N between max(6dB, C/N at picture failure) and 30dB */

  int ligne = 18;
  int constel;
  double c_n_raw;
  double correction_in_dB;
  double Comp_CNR [19][3] = {/* ISDB-T compensation for each constellation based on demodulator register cn */
            /*           thr    Ah     Bh  */
            /* QPSK */ { 2000, 0.0019,  3.30},
            /* QPSK */ {  933, 0.0013,  2.10},
            /* QPSK */ {   18, 0.0010,  1.82},
            /* QPSK */ {   11, 0.0190,  2.15},
            /* QPSK */ {    7, 0.0900,  2.92},
            /* QPSK */ {    0, 0.0000,  4.04},
            /* 16QAM */{  975, 0.0020,  2.59},
            /* 16QAM */{  133, 0.0012,  1.81},
            /* 16QAM */{   57, 0.0018,  1.89},
            /* 16QAM */{   31, 0.0190,  2.87},
            /* 16QAM */{   21, 0.1650,  7.41},
            /* 16QAM */{    0, 0.4800, 14.11},
            /* 64QAM */{ 1520, 0.0017,  2.68},
            /* 64QAM */{  279, 0.0012,  1.92},
            /* 64QAM */{  146, 0.0040,  2.70},
            /* 64QAM */{  104, 0.0320,  6.78},
            /* 64QAM */{   89, 0.0700, 10.75},
            /* 64QAM */{    0, 0.1500, 17.89},
            /*default*/{    0,      0,     0},
                };
  SiTRACE_X("c_n_correction, constellation %8s, c_n %6.3f\n"
          , Silabs_Constel_Text ((CUSTOM_Constel_Enum)  constellation)
          , c_n);
 switch (constellation) {
         case SILABS_QPSK   :  constel = 0;  break;
         case SILABS_QAM16  :  constel = 6;  break;
         case SILABS_QAM64  :  constel = 12; break;
         default:              constel = 12; break;
 }
 /* find table line */
 c_n = Si2183_L2_GET_REG(front_end->Si2183_FE, 23, 4, 7);
 if (c_n >= 0) {
     if (c_n > Comp_CNR [constel][0]) {   ligne = constel;}
     else if (c_n > Comp_CNR [constel+1][0]) {   ligne = constel+1;}
     else if (c_n > Comp_CNR [constel+2][0]) {   ligne = constel+2;}
     else if (c_n > Comp_CNR [constel+3][0]) {   ligne = constel+3;}
     else if (c_n > Comp_CNR [constel+4][0]) {   ligne = constel+4;}
     else if (c_n > Comp_CNR [constel+5][0]) {   ligne = constel+5;}
 } else {SiTRACE_X("c_n_correction not applied because of negative c_n value %6.2f\n", c_n);}

/* Compute c_n correction */
 c_n_raw = c_n;
 switch ((int)c_n) { /* specific cases where cn equals 5, 6 and 7, achievable in QPSK */
         case 5  :  correction_in_dB = 4.04;  break;
         case 6  :  correction_in_dB = 2.98;  break;
         case 7  :  correction_in_dB = 2.5;   break;
         default: {
                    correction_in_dB = -Comp_CNR [ligne][1] * c_n_raw + Comp_CNR [ligne][2];
                    break;
             }
 }
 switch (guard_interval) {
         case SILABS_GUARD_INTERVAL_1_32 :  correction_in_dB = correction_in_dB - 0.6;  break;
         case SILABS_GUARD_INTERVAL_1_16 :  correction_in_dB = correction_in_dB - 0.4;  break;
         case SILABS_GUARD_INTERVAL_1_8  :  correction_in_dB = correction_in_dB - 0.2;  break;
         case SILABS_GUARD_INTERVAL_1_4  :
         default: break;
 }
  c_n_raw = 10.0*log10(c_n);
 c_n = c_n_raw - correction_in_dB;
 SiTRACE_X("CNR corrected = %6.4f - %6.4f = %6.4f dB\n", c_n_raw, correction_in_dB, c_n);
 if (c_n > 35) {
    SiTRACE_X("CNR saturated to 35dB\n");
    c_n = 35.0;
 }
return c_n;
}
double   DVBT_c_n_correction(int constellation, int guard_interval, int code_rate, double c_n) {
  int ligne;
  int constel;
  int rate;
  double c_n_raw;
  double correction_gi_in_dB;
  double Comp_DVBT [15][5] = {/* DVB-T compensation for each constellation and code rate for Si218x/Si2164B/Si2168C/69C */
            /*             thr    Ah    Bh    Ai    Bi */
            /* QPSK  1/2 */{ 9.75, 1,    -1.80,1,    -3.30 },
            /* QPSK  2/3 */{ 9.25, 1,    -1.90,1,    -3.45 },
            /* QPSK  3/4 */{ 14,   1,    -1.70,1,    -2.80 },
            /* QPSK  5/6 */{ 29.75,1,    -1.45,1,    -2.50 },
            /* QPSK  7/8 */{ 29.75,1,    -1.45,1,    -2.20 },
            /* 16QAM 1/2 */{ 16.25,1,    -1.55,1,    -3.20 },
            /* 16QAM 2/3 */{ 15.5, 1,    -1.50,1,    -3.40 },
            /* 16QAM 3/4 */{ 18.25,1,    -1.40,1,    -2.80 },
            /* 16QAM 5/6 */{ 30.25,1,    -1.30,1,    -2.30 },
            /* 16QAM 7/8 */{ 29.5, 1,    -1.35,1,    -2.05 },
            /* 64QAM 1/2 */{ 21.25,1,    -2.00,1,    -3.85 },
            /* 64QAM 2/3 */{ 21.5, 1,    -1.75,1,    -3.70 },
            /* 64QAM 3/4 */{ 25,   1,    -1.80,1,    -2.90 },
            /* 64QAM 5/6 */{ 29,   1,    -1.60,1,    -2.40 },
            /* 64QAM 7/8 */{ 30,   1,    -1.60,1,    -2.20 }
                };
  if (c_n >= 34.50) {
    SiTRACE_X("no CNR correction, c_n= %6.3f dB\n", c_n);
 } else {
  SiTRACE_X("DVBT_c_n_correction constellation %8s, code_rate %8s, guard interval %8s, c_n %6.3f\n"
          , Silabs_Constel_Text ((CUSTOM_Constel_Enum)  constellation)
          , Silabs_Coderate_Text((CUSTOM_Coderate_Enum) code_rate    )
         ,  Silabs_GI_Text      ((CUSTOM_GI_Enum) guard_interval     )
          , c_n);
  switch (constellation) {
    case SILABS_QPSK   :  constel = 0;  break;
    case SILABS_QAM16  :  constel = 5;  break;
    case SILABS_QAM64  :  constel = 10; break;
    default:              constel = 10; break;
  }
  switch (code_rate)     {
    case SILABS_CODERATE_1_2: rate = 0; break;
    case SILABS_CODERATE_2_3: rate = 1; break;
    case SILABS_CODERATE_3_4: rate = 2; break;
    case SILABS_CODERATE_5_6: rate = 3; break;
    case SILABS_CODERATE_7_8: rate = 4; break;
    default:                  rate = 2; break;
  }
  switch (guard_interval) {
    case SILABS_GUARD_INTERVAL_1_32 :  correction_gi_in_dB = 0.8;  break;
    case SILABS_GUARD_INTERVAL_1_16 :  correction_gi_in_dB = 0.75;  break;
    case SILABS_GUARD_INTERVAL_1_8  :  correction_gi_in_dB = 0.25;  break;
    case SILABS_GUARD_INTERVAL_1_4  :
    default:                           correction_gi_in_dB = 0;   break;
  }
  /* Compute c_n correction */
   ligne = constel + rate;
   c_n_raw = c_n;
   if (c_n > Comp_DVBT [ligne][0]) {
       c_n = Comp_DVBT [ligne][1] * c_n + Comp_DVBT [ligne][2] + correction_gi_in_dB;
       SiTRACE_X("DVBT corrected C_N = %6.2f * %6.2f + %6.2f + %6.2f = %6.2f dB\n", Comp_DVBT [ligne][1], c_n_raw, Comp_DVBT [ligne][2], correction_gi_in_dB, c_n);
   } else {
       c_n = Comp_DVBT [ligne][3] * c_n + Comp_DVBT [ligne][4] + correction_gi_in_dB;
       SiTRACE_X("DVBT corrected C_N = %6.2f * %6.2f + %6.2f + %6.2f = %6.2f dB\n", Comp_DVBT [ligne][3], c_n_raw, Comp_DVBT [ligne][4], correction_gi_in_dB, c_n);
   }
 }
 return c_n;
}
#endif /* NO_FLOATS_ALLOWED */
signed   int  SiLabs_API_SSI_SQI_no_float           (signed   int standard, signed   int locked, signed   int Prec, signed   int constellation, signed   int code_rate, signed   int c_n_100, signed   int ber_mant, signed   int ber_exp, signed   int *ssi, signed   int *sqi)
{
  signed   int constel;
  signed   int rate;
  signed   int ber_sqi;
  signed   int Prel;
  signed   int CNrel_100;

    signed   int Pref_DVBC  [5] =  /* DVB-C reference levels for each constellation */
/* QAM         16    32    64   128   256  */
/* LEVEL */{  -78,  -75,  -72,  -69,  -65  };
    signed   int CNref_DVBC [5] =
/* QAM         16    32    64   128   256  */
/* LEVEL */{  200,  230,  260,  290,  320 };

    signed   int Pref_DVBS  [1][5] = {
/*            1/2  2/3  3/4  5/6  7/8    */
/* QPSK  */{  -85, -83, -82, -81, -80 },
    };
    signed   int CNref_DVBS [1][5] = {
/*            1/2  2/3  3/4  5/6  7/8    */
/* QPSK  */{   38,  56,  67,  77,  84 },
    };
    signed   int Pref_DVBS2 [2][8] = {
/*            1/2  3/5  2/3  3/4  4/5  5/6  8/9  9/10 */
/* QPSK  */{  -85, -84, -83, -82, -81, -81, -80, -80 },
/* 8PSK  */{    0, -80, -79, -78,   0, -77, -76, -76 }
    };
    signed   int CNref_DVBS2[2][8] = {
/*            1/2  3/5  2/3  3/4  4/5  5/6  8/9  9/10 */
/* QPSK  */{   20,  32,  41,  50,  57,  62,  72,  74 },
/* 8PSK  */{    0,  65,  76,  89,   0, 104, 117, 120 }
    };

  *ssi = *sqi = 0;

  /* The API returns '-1' when BER is not available, so set ber to 1 in this case */
  if (ber_exp == 0) {ber_mant = 1;}

  SiTRACE_X("SiLabs_API_SSI_SQI standard %8d, constellation %8d, code_rate %8d, Prec %3d, c_n_100 %3d, ber_mant %2d, ber_exp %2d\n"
          , standard
          , constellation
          , code_rate
          , Prec
          , c_n_100
          , ber_mant
          , ber_exp);
  SiTRACE_X("SiLabs_API_SSI_SQI standard %8s, constellation %8s, code_rate %8s, Prec %3d, c_n_100 %3d, ber_mant %2d, ber_exp %2d\n"
          , Silabs_Standard_Text((CUSTOM_Standard_Enum) standard     )
          , Silabs_Constel_Text ((CUSTOM_Constel_Enum)  constellation)
          , Silabs_Coderate_Text((CUSTOM_Coderate_Enum) code_rate    )
          , Prec
          , c_n_100
          , ber_mant
          , ber_exp);

    switch (standard) {
      case SILABS_MCNS:
      case SILABS_DVB_C : {
        switch (constellation) {
          case SILABS_QAM16 :  constel = 0; break;
          case SILABS_QAM32 :  constel = 1; break;
          case SILABS_QAM64 :  constel = 2; break;
          case SILABS_QAM128:  constel = 3; break;
          case SILABS_QAM256:  constel = 4; break;
          default:             constel = 4; break;
        }
        /* Compute DVB-C SSI */
        Prel = Prec - Pref_DVBC[constel];
        if (locked) {
          SiTRACE_X("DVBC SSI: Prel  = Prec  - Pref[%d] = %3d dBm + %3d dB = %3d dBm\n",            constel, 1*Prec, -1*Pref_DVBC[constel], Prel);
        } else {
          SiTRACE_X("DVBC SSI: Prel  = Prec  - Pref[%d] = %3d dBm + %3d dB = %3d dBm (unlocked)\n", constel, 1*Prec, -1*Pref_DVBC[constel], Prel);
        }
               if (Prel < -15) {
          *ssi = 0;
        } else if (Prel < 0)  {
          *ssi = (int)(((Prel + 15)*2)/3);
        } else if (Prel < 20) {
          *ssi = (int)(Prel*4 + 10);
        } else if (Prel < 35) {
          *ssi = (int)((((Prel -20)*2) + 3*90)/3);
        } else                {
          *ssi = 100;
        }
        /* Compute DVB-C SQI */
        if (locked) {
          CNrel_100 = c_n_100 - 10*CNref_DVBC[constel];
          if (CNrel_100 < -700) {
            *sqi = 0;
          } else {
            if ( (ber_mant == 0) | (ber_exp > 8) ) {
              ber_sqi = 100;
            } else if (ber_exp > 4) {
              ber_sqi = (int)((-20*(Silabs_Log10_10000(ber_mant) - ber_exp*10000) -400000)/10000);
            } else    {
              ber_sqi = 0;
            }
            if (CNrel_100 < 300) {
              *sqi = (int)(((CNrel_100 - 300 + 1000)*ber_sqi)/1000);
            } else {
              *sqi = ber_sqi;
            }
          }
        } else {
          *sqi = 0;
        }
        break;
      }
      case SILABS_DVB_S : {
        switch (constellation) {
          case SILABS_QPSK:  constel = 0; break;
          default:           constel = 0; break;
        }
        switch (code_rate)     {
          case SILABS_CODERATE_1_2: rate = 0; break;
          case SILABS_CODERATE_2_3: rate = 1; break;
          case SILABS_CODERATE_3_4: rate = 2; break;
          case SILABS_CODERATE_5_6: rate = 3; break;
          case SILABS_CODERATE_7_8: rate = 4; break;
          default:                  rate = 0; break;
        }
        /* Compute DVB-S SSI */
        if (locked) {
          Prel = Prec - Pref_DVBS[constel][rate];
        } else {
          Prel = Prec - Pref_DVBS[0][4];
        }
               if (Prel < -15) {
          *ssi = 0;
        } else if (Prel < 0)  {
          *ssi = (int)(((Prel + 15)*2)/3);
        } else if (Prel < 20) {
          *ssi = (int)(Prel*4 + 10);
        } else if (Prel < 35) {
          *ssi = (int)((Prel -20)*2 + 3*90)/3;
        } else                {
          *ssi = 100;
        }
        /* Compute DVB-S SQI */
        if (locked) {
          CNrel_100 = c_n_100 - 10*CNref_DVBS[constel][rate];
          if (CNrel_100 < -700) {
            *sqi = 0;
          } else {
            if ( (ber_mant == 0) | (ber_exp > 8) ) {
              ber_sqi = 100;
            } else if (ber_exp > 4) {
              ber_sqi = (int)((-20*(Silabs_Log10_10000(ber_mant) - ber_exp*10000) -400000)/10000);
            } else    {
              ber_sqi = 0;
            }
            if (CNrel_100 < 300) {
              *sqi = (int)(((CNrel_100 -300 + 1000)*ber_sqi)/1000);
            } else                {
              *sqi = ber_sqi;
            }
          }
        } else {
          SiTRACE_X("DVBS SQI: unlocked: SQI = 0\n");
          *sqi = 0;
        }
        break;
      }
      case SILABS_DVB_S2: {
        switch (constellation) {
          case SILABS_QPSK:  constel = 0; break;
          case SILABS_8PSK:  constel = 1; break;
          default:           constel = 0; break;
        }
        switch (code_rate)     {
          case SILABS_CODERATE_1_2: rate = 0; break;
          case SILABS_CODERATE_3_5: rate = 1; break;
          case SILABS_CODERATE_2_3: rate = 2; break;
          case SILABS_CODERATE_3_4: rate = 3; break;
          case SILABS_CODERATE_4_5: rate = 4; break;
          case SILABS_CODERATE_5_6: rate = 5; break;
          case SILABS_CODERATE_8_9: rate = 6; break;
          case SILABS_CODERATE_9_10:rate = 7; break;
          default:                  rate = 0; break;
        }
        /* Compute DVB-S2 SSI */
        if (locked){
          Prel = Prec - Pref_DVBS2[constel][rate];
        } else {
          Prel = Prec - Pref_DVBS2[0][7];
        }
               if (Prel < -15) {
          *ssi = 0;
        } else if (Prel < 0)  {
          *ssi = (int)(((Prel + 15)*2)/3);
        } else if (Prel < 20) {
          *ssi = (int)(Prel*4 + 10);
        } else if (Prel < 35) {
          *ssi = (int)((((Prel -20)*2) + 3*90)/3);
        } else                {
          *ssi = 100;
        }
        /* Compute DVB-S2 SQI */
        if (locked) {
          CNrel_100 = c_n_100 - 10*CNref_DVBS2[constel][rate];
                 if (CNrel_100 < -300) {
            *sqi = 0;
          } else if (CNrel_100 < 300) {
            if ( (ber_mant == 0) | (ber_exp > 8) ) {
              ber_sqi = 10000/6;
            } else if (ber_exp > 4) {
              ber_sqi = 10000/15;
            } else    {
              ber_sqi = 0;
            }
            *sqi = ((CNrel_100 + 300 )*ber_sqi)/100;
          } else                {
            *sqi = 100;
          }
        } else {
          SiTRACE_X("DVBS2 SQI: unlocked: SQI = 0\n");
          *sqi = 0;
        }
        break;
      }
      default           : {
        SiTRACE_X("SiLabs_API_SSI_SQI does not work for standard %2d (%s)\n", standard, Silabs_Standard_Text((CUSTOM_Standard_Enum)standard));
        break;
      }
    }
    SiTRACE_X("SiLabs_API_SSI_SQI SSI %3d, SQI %3d\n", *ssi, *sqi);
    return 1;
}
signed int   ISDB_T_c_n_100_corrected(SILABS_FE_Context *front_end, int constellation, int guard_interval, signed int c_n_100) {
 /* maximum c_n value reported is 35dB as demodulator register cn saturates for tester C/N more than 35dB*/
 /* minimum reported value is 4dB as register cn remains at 5 for tester C/N less than 4dB */
 /* accuracy is expected within +/-1dB for tester C/N between max(6dB, C/N at picture failure) and 30dB */
  int ligne = 18;
  int constel;
  signed int c_n_100_raw;
  signed int correction_in_100th_dB;
  long int Comp_CNR [19][3] = {/* ISDB-T compensation for each constellation based on demodulator register cn */
            /*           thr    Ah     Bh  */
            /* QPSK */ { 2000,   19,  33000},
            /* QPSK */ {  933,   13,  21000},
            /* QPSK */ {   18,   10,  18200},
            /* QPSK */ {   11,  190,  21500},
            /* QPSK */ {    7,  900,  29200},
            /* QPSK */ {    0,    0,  40400},
            /* 16QAM */{  975,   20,  25900},
            /* 16QAM */{  133,   12,  18100},
            /* 16QAM */{   57,   18,  18900},
            /* 16QAM */{   31,  190,  28700},
            /* 16QAM */{   21, 1650,  74100},
            /* 16QAM */{    0, 4800, 141100},
            /* 64QAM */{ 1520,   17,  26800},
            /* 64QAM */{  279,   12,  19200},
            /* 64QAM */{  146,   40,  27000},
            /* 64QAM */{  104,  320,  67800},
            /* 64QAM */{   89,  700, 107500},
            /* 64QAM */{    0, 1500, 178900},
            /*default*/{    0,    0,      0},
                };
 SiTRACE_X("c_n_100_correction, constellation %8s, c_n %8d\n"
          , Silabs_Constel_Text ((CUSTOM_Constel_Enum)  constellation)
          , c_n_100);
 switch (constellation) {
         case SILABS_QPSK   :  constel = 0;  break;
         case SILABS_QAM16  :  constel = 6;  break;
         case SILABS_QAM64  :  constel = 12; break;
         default:              constel = 12; break;
 }
 /* find table line */
 c_n_100 = Si2183_L2_GET_REG(front_end->Si2183_FE, 23, 4, 7);
 if (c_n_100 >= 0) {
     if (c_n_100 > Comp_CNR [constel][0]) {   ligne = constel;}
     else if (c_n_100 > Comp_CNR [constel+1][0]) {   ligne = constel+1;}
     else if (c_n_100 > Comp_CNR [constel+2][0]) {   ligne = constel+2;}
     else if (c_n_100 > Comp_CNR [constel+3][0]) {   ligne = constel+3;}
     else if (c_n_100 > Comp_CNR [constel+4][0]) {   ligne = constel+4;}
     else if (c_n_100 > Comp_CNR [constel+5][0]) {   ligne = constel+5;}
 } else {SiTRACE_X("c_n_correction not applied because of negative c_n value %8d\n", c_n_100);}

 /* Compute c_n_100 correction */
 c_n_100_raw = c_n_100;
 switch (c_n_100) { /* specific cases where cn equals 5, 6 and 7, achievable in QPSK */
         case 5  :  correction_in_100th_dB = 404;  break;
         case 6  :  correction_in_100th_dB = 298;  break;
         case 7  :  correction_in_100th_dB = 250;  break;
         default: {
                    /* Compute c_n correction */
                    correction_in_100th_dB = (signed int) ((-Comp_CNR [ligne][1] * c_n_100_raw + Comp_CNR [ligne][2])/100);
                    break;
             }
 }
 switch (guard_interval) {
         case SILABS_GUARD_INTERVAL_1_32 :  correction_in_100th_dB = correction_in_100th_dB - 60;  break;
         case SILABS_GUARD_INTERVAL_1_16 :  correction_in_100th_dB = correction_in_100th_dB - 40;  break;
         case SILABS_GUARD_INTERVAL_1_8  :  correction_in_100th_dB = correction_in_100th_dB - 20;  break;
         case SILABS_GUARD_INTERVAL_1_4  :
         default: break;
 }
 /* overcome limitation of function Silabs_Log10_10000(x) for x less than 10*/
 if (c_n_100_raw <10) {
    c_n_100_raw = (signed int)((Silabs_Log10_10000(c_n_100*10)-10000)/10);
 } else {c_n_100_raw = (signed int)(Silabs_Log10_10000(c_n_100)/10);}
 c_n_100 = c_n_100_raw - correction_in_100th_dB;
 SiTRACE_X("CNR corrected = %8d - %8d = %8d dB\n", c_n_100_raw, correction_in_100th_dB, c_n_100);
 if (c_n_100 > 3500) {
    SiTRACE_X("CNR saturated to 35dB\n");
    c_n_100 = 3500;
 }
 return c_n_100;
}
signed int   DVBT_c_n_100_corrected(int constellation, int guard_interval, int code_rate, signed int c_n_100) {
  int ligne;
  int constel;
  int rate;
  signed int c_n_100_raw;
  signed int correction_gi_in_100th_dB;
  int Comp_DVBT [15][5] = {/* DVB-T compensation for each constellation and code rate for Si218x/Si2164B/Si2168C/69C */
            /*             thr    Ah    Bh    Ai    Bi */
            /* QPSK  1/2 */{ 975,    1,    -180,1,    -330 },
            /* QPSK  2/3 */{ 925,    1,    -190,1,    -345 },
            /* QPSK  3/4 */{ 1400,   1,    -170,1,    -280 },
            /* QPSK  5/6 */{ 2975,   1,    -145,1,    -250 },
            /* QPSK  7/8 */{ 2975,   1,    -145,1,    -220 },
            /* 16QAM 1/2 */{ 1625,   1,    -155,1,    -320 },
            /* 16QAM 2/3 */{ 1550,   1,    -150,1,    -340 },
            /* 16QAM 3/4 */{ 1825,   1,    -140,1,    -280 },
            /* 16QAM 5/6 */{ 3025,   1,    -130,1,    -230 },
            /* 16QAM 7/8 */{ 2950,   1,    -135,1,    -205 },
            /* 64QAM 1/2 */{ 2125,   1,    -200,1,    -385 },
            /* 64QAM 2/3 */{ 2150,   1,    -175,1,    -370 },
            /* 64QAM 3/4 */{ 2500,   1,    -180,1,    -290 },
            /* 64QAM 5/6 */{ 2900,   1,    -160,1,    -240 },
            /* 64QAM 7/8 */{ 3000,   1,    -160,1,    -220 }
                };
  if (c_n_100 >= 3450) {
    SiTRACE_X("no CNR correction, c_n= %8d\n", c_n_100);
 } else {
  SiTRACE_X("DVBT_c_n_100_correction constellation %8s, code_rate %8s, c_n %8d\n"
          , Silabs_Constel_Text ((CUSTOM_Constel_Enum)  constellation)
          , Silabs_Coderate_Text((CUSTOM_Coderate_Enum) code_rate    )
         ,  Silabs_GI_Text      ((CUSTOM_GI_Enum) guard_interval     )
          , c_n_100);
  switch (constellation) {
    case SILABS_QPSK   :  constel = 0;  break;
    case SILABS_QAM16  :  constel = 5;  break;
    case SILABS_QAM64  :  constel = 10; break;
    default:              constel = 10; break;
  }
  switch (code_rate)     {
    case SILABS_CODERATE_1_2: rate = 0; break;
    case SILABS_CODERATE_2_3: rate = 1; break;
    case SILABS_CODERATE_3_4: rate = 2; break;
    case SILABS_CODERATE_5_6: rate = 3; break;
    case SILABS_CODERATE_7_8: rate = 4; break;
    default:                  rate = 2; break;
  }
  switch (guard_interval) {
    case SILABS_GUARD_INTERVAL_1_32 :  correction_gi_in_100th_dB = 80;  break;
    case SILABS_GUARD_INTERVAL_1_16 :  correction_gi_in_100th_dB = 75;  break;
    case SILABS_GUARD_INTERVAL_1_8  :  correction_gi_in_100th_dB = 25;  break;
    case SILABS_GUARD_INTERVAL_1_4  :
    default:                           correction_gi_in_100th_dB = 0;   break;
  }
  /* Compute c_n correction */
  ligne = constel + rate;
  c_n_100_raw = c_n_100;
  if (c_n_100 > Comp_DVBT [ligne][0]) {
      c_n_100 = Comp_DVBT [ligne][1] * c_n_100 + Comp_DVBT [ligne][2] + correction_gi_in_100th_dB;
      SiTRACE_X("DVBT corrected C_N = %d * %d + %d +%d = %d dB\n", Comp_DVBT [ligne][1], c_n_100_raw, Comp_DVBT [ligne][2], correction_gi_in_100th_dB, c_n_100);
  } else {
      c_n_100 = Comp_DVBT [ligne][3] * c_n_100 + Comp_DVBT [ligne][4] + correction_gi_in_100th_dB;
      SiTRACE_X("DVBT corrected C_N = %d * %d + %d +%d = %d dB\n", Comp_DVBT [ligne][3], c_n_100_raw, Comp_DVBT [ligne][4], correction_gi_in_100th_dB, c_n_100);
  }
 }
 return c_n_100;
}
#ifdef    Si2183_DVBS2_PLS_INIT_CMD
signed   int  SiLabs_API_SAT_Gold_Sequence_Init     (signed   int gold_sequence_index)
{
  unsigned int i;
  signed   int k;
  unsigned int x_init;

  unsigned char GOLD_PRBS[19] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  for (k=0; k<gold_sequence_index; k++) {
    GOLD_PRBS[18] = (GOLD_PRBS[0] + GOLD_PRBS[7])%2;
    /* Shifting 18 first values */
    for (i=0; i<18; i++) { GOLD_PRBS[i] = GOLD_PRBS[i+1]; }
  }

  x_init = 0;
  for (i=0; i<18; i++) { x_init = x_init + GOLD_PRBS[i]*(1<<i); }

  return x_init;
}
signed   int  SiLabs_API_SAT_PLS_Init               (SILABS_FE_Context *front_end,    signed   int pls_init)
{
#ifdef    Si2183_COMPATIBLE
  unsigned char   pls_detection_mode;
  unsigned long   pls;
#endif /* Si2183_COMPATIBLE */
  SiTRACE("SiLabs_API_SAT_PLS_Init %d\n", pls_init);
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    if (pls_init < 0) {
      pls_detection_mode = Si2183_DVBS2_PLS_INIT_CMD_PLS_DETECTION_MODE_AUTO  ; pls = 0;
    } else {
      pls_detection_mode = Si2183_DVBS2_PLS_INIT_CMD_PLS_DETECTION_MODE_MANUAL; pls = pls_init;
    }
    if (Si2183_L1_DVBS2_PLS_INIT (front_end->Si2183_FE->demod, pls_detection_mode  , pls  ) != NO_Si2183_ERROR) {
      SiERROR("Si2183_L1_DVBS2_PLS_INIT ERROR\n");
      return 0;
    }
    return 1;
  }
#endif /* Si2183_COMPATIBLE */
  return 0;
}
#endif /* Si2183_DVBS2_PLS_INIT_CMD */
signed   int  SiLabs_API_Demods_Kickstart           (void)
{
  signed   int fe;
  SILABS_FE_Context *front_end;
  SiTRACE_X("API CALL INIT : SiLabs_API_Demods_Kickstart ()\n");
  if (FRONT_END_COUNT == 1) {
    return 1;
  }
  for (fe=0; fe < FRONT_END_COUNT; fe++) {
    front_end  = &(FrontEnd_Table[fe]);
  #ifdef    Si2183_COMPATIBLE
    if (front_end->chip ==   0x2183 ) {
#ifdef    SATELLITE_FRONT_END
      front_end->Si2183_FE->demod->cmd->start_clk.clk_mode = front_end->Si2183_FE->demod->tuner_sat_clock_input;
#endif /* SATELLITE_FRONT_END */
#ifdef    TERRESTRIAL_FRONT_END
      front_end->Si2183_FE->demod->cmd->start_clk.clk_mode = front_end->Si2183_FE->demod->tuner_ter_clock_input;
#endif /* TERRESTRIAL_FRONT_END */
      /* when not using a Xtal, set TUNE_CAP to 'EXT_CLK' (The value for XTAL use is set in Si2183_L2_SW_Init) */
      if (front_end->Si2183_FE->demod->cmd->start_clk.clk_mode != Si2183_START_CLK_CMD_CLK_MODE_XTAL) {
        front_end->Si2183_FE->demod->cmd->start_clk.tune_cap = Si2183_START_CLK_CMD_TUNE_CAP_EXT_CLK;
      }
      Si2183_L1_START_CLK (front_end->Si2183_FE->demod,
        Si2183_START_CLK_CMD_SUBCODE_CODE,
        Si2183_START_CLK_CMD_RESERVED1_RESERVED,
        front_end->Si2183_FE->demod->cmd->start_clk.tune_cap,
        Si2183_START_CLK_CMD_RESERVED2_RESERVED,
        front_end->Si2183_FE->demod->cmd->start_clk.clk_mode,
        Si2183_START_CLK_CMD_RESERVED3_RESERVED,
        Si2183_START_CLK_CMD_RESERVED4_RESERVED,
        Si2183_START_CLK_CMD_START_CLK_START_CLK);
    }
  #endif /* Si2183_COMPATIBLE */
  }
  return fe;
}
signed   int  SiLabs_API_TER_Tuners_Kickstart       (void)
{
  signed   int fe;
#ifdef    TER_TUNER_SILABS
  SILABS_FE_Context *front_end;
  SILABS_TER_TUNER_Context *silabs_tuner;
#endif /* TER_TUNER_SILABS */
  fe = 0;
  SiTRACE_X("API CALL INIT : SiLabs_API_TER_Tuners_Kickstart ()\n");
  if (FRONT_END_COUNT == 1) {
    return 1;
  }
#ifdef    TER_TUNER_SILABS
  for (fe=0; fe < FRONT_END_COUNT; fe++) {
    front_end  = &(FrontEnd_Table[fe]);
    silabs_tuner = SiLabs_API_TER_Tuner(front_end);
    SiTRACE("silabs_tuner 0x%p\n", silabs_tuner);
    if (silabs_tuner != 0) {
      SiLabs_API_TER_Tuner_I2C_Enable  (front_end);
      SiLabs_TER_Tuner_Tuner_kickstart (silabs_tuner);
      SiLabs_API_TER_Tuner_I2C_Disable (front_end);
    }
  }
#endif /* TER_TUNER_SILABS */
  return fe;
}
signed   int  SiLabs_API_Cypress_Ports              (SILABS_FE_Context *front_end,    unsigned char OEA, unsigned char IOA, unsigned char OEB, unsigned char IOB, unsigned char OED, unsigned char IOD )
{
#ifdef    USB_Capability
  double retdval;
  char *entry;
  char  entryBuffer[1000];
  entry = &(entryBuffer[0]);
  SiTRACE("API CALL CONFIG: SiLabs_API_Cypress_Ports        (front_end, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x);\n", OEA, IOA, OEB, IOB, OED, IOD);
  L0_Cypress_Process("output_enable_io_port", "a", (double)OEA, &retdval, &entry);
  L0_Cypress_Process("write_io_port"        , "a", (double)IOA, &retdval, &entry);
  L0_Cypress_Process("output_enable_io_port", "b", (double)OEB, &retdval, &entry);
  L0_Cypress_Process("write_io_port"        , "b", (double)IOB, &retdval, &entry);
  L0_Cypress_Process("output_enable_io_port", "d", (double)OED, &retdval, &entry);
  L0_Cypress_Process("write_io_port"        , "d", (double)IOD, &retdval, &entry);
  return (IOA<<24)+(IOB<<16)+(IOD<<0);
#endif /* USB_Capability */
  front_end = front_end;        /* To avoid compiler warning */
  IOA=OEA=IOB=OEB=IOD=OED=0x00; /* To avoid compiler warning if not used */
  return (IOA<<24)+(IOB<<16)+(IOD<<0);
}
/************************************************************************************************************************
  NAME: SiLabs_API_Demod_reset
  DESCRIPTION: demodulator reset function
  Parameter:  Pointer to SILABS_FE_Context
  Returns:    void
************************************************************************************************************************/
void          SiLabs_API_Demod_reset                (SILABS_FE_Context *front_end)
{
  #ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    if (Si2183_L1_DD_RESTART  (front_end->Si2183_FE->demod)!=0) {
      SiTRACE("Demod reset failed!\n");
    }
  }
  #endif /* Si2183_COMPATIBLE */
}
signed   int  SiLabs_API_Store_FW                   (SILABS_FE_Context *front_end,    firmware_struct fw_table[], signed   int nbLines) {
  signed   int stored, line, i; line = i = stored = 0;
#ifdef    FW_CHANGE_COMPATIBLE
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    front_end->Si2183_FE->demod->nbLines  = nbLines;
    front_end->Si2183_FE->demod->fw_table = (firmware_struct*)realloc(front_end->Si2183_FE->demod->fw_table, sizeof(firmware_struct)*nbLines);
    for (line = 0; line < nbLines; line++) {
      front_end->Si2183_FE->demod->fw_table[line].firmware_len = fw_table[line].firmware_len;
      for (i = 0; i < 16; i++) {    front_end->Si2183_FE->demod->fw_table[line].firmware_table[i] = fw_table[line].firmware_table[i]; }
    }
    stored++;
  }
#endif /* Si2183_COMPATIBLE */
#endif /* FW_CHANGE_COMPATIBLE */
  if (stored) {
    for (line = 0; line < nbLines; line++) {
      if (fw_table[line].firmware_len > 0) {
        SiTRACE ("0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n"
                , fw_table[line].firmware_table[ 0], fw_table[line].firmware_table[ 1], fw_table[line].firmware_table[ 2], fw_table[line].firmware_table[ 3]
                , fw_table[line].firmware_table[ 4], fw_table[line].firmware_table[ 5], fw_table[line].firmware_table[ 6], fw_table[line].firmware_table[ 7]
                , fw_table[line].firmware_table[ 8], fw_table[line].firmware_table[ 9], fw_table[line].firmware_table[10], fw_table[line].firmware_table[11]
                , fw_table[line].firmware_table[12], fw_table[line].firmware_table[13], fw_table[line].firmware_table[14], fw_table[line].firmware_table[15]); }
      if (line== 3         ) {SiTRACE (". . .\n"); SiTraceConfiguration("traces suspend"); }
      if (line==nbLines - 5) {                     SiTraceConfiguration("traces resume" ); }
    }
    SiTraceConfiguration("traces resume");
  }
  return stored*nbLines;
}
signed   int  SiLabs_API_Store_SPI_FW               (SILABS_FE_Context *front_end,    unsigned char spi_table[], signed   int nbBytes) {
  signed   int stored, i; i = stored = 0;
#ifdef    FW_CHANGE_COMPATIBLE
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    front_end->Si2183_FE->demod->nbSpiBytes  = nbBytes;
    front_end->Si2183_FE->demod->spi_table   = (unsigned char*)realloc(front_end->Si2183_FE->demod->spi_table, sizeof(unsigned char)*nbBytes);
    for (i = 0; i < nbBytes; i++) {    front_end->Si2183_FE->demod->spi_table[i] = spi_table[i]; }
    stored++;
  }
#endif /* Si2183_COMPATIBLE */
#endif /* FW_CHANGE_COMPATIBLE */
  if (stored) {
    for (i = 0; i < nbBytes; i++) {
      SiTRACE ("0x%02x ", spi_table[i]);
      if (i%8 == 7)         { SiTRACE (" 0x%02x\n", spi_table[i]); } else { SiTRACE (" 0x%02x", spi_table[i]); }
      if (i == 24         ) {SiTRACE (". . .\n"); SiTraceConfiguration("traces suspend"); }
      if (i==nbBytes - 40 ) {                     SiTraceConfiguration("traces resume" ); }
    }
    SiTraceConfiguration("traces resume");
  }
  return stored*nbBytes;
}
signed   int  SiLabs_API_Store_TER_TUNER_FW         (SILABS_FE_Context *front_end,    firmware_struct fw_table[], signed   int nbLines) {
  signed   int stored; stored = 0;
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { return SiLabs_TER_Tuner_Store_FW(front_end->Si2183_FE->tuner_ter, fw_table, nbLines); }
#endif /* Si2183_COMPATIBLE */
  return stored*nbLines;
}
signed   int  SiLabs_API_Auto_Detect_Demods         (L0_Context* i2c, signed   int *Nb_FrontEnd, signed   int demod_code[4], signed   int demod_add[4], char *demod_string[4]) {
  unsigned char replyBytes[16];
  unsigned char START_CLK_Bytes[13] = { 0xc0, 0x12, 0x00, 0x0c, 0x00, 0x0d, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  unsigned char POWER_UP_Bytes[8]   = { 0xc0, 0x06, 0x01, 0x0f, 0x00, 0x20, 0x20, 0x01 };
  unsigned char PART_INFO_Bytes[1]  = { 0x02 };
  signed   int add;
  signed   int readBytes;
  signed   int CTS;
  signed   int chiprev;
  signed   int part   ;
  signed   int pmajor ;
  signed   int pminor ;
  signed   int pbuild ;
  signed   int romid  ;

  *Nb_FrontEnd = 0;
  i2c->indexSize = 0;
  for (add = 0xC8; add <= 0xCE; add=add+2 ) {
    demod_code[*Nb_FrontEnd] = demod_add[*Nb_FrontEnd] = 0;
    /* SiTRACE("Auto detecting demod at 0x%02X\n", add); */
    i2c->address = add;
    L0_WriteBytes(i2c, 0x00, sizeof(START_CLK_Bytes), START_CLK_Bytes);
    L0_WriteBytes(i2c, 0x00, sizeof(POWER_UP_Bytes),  POWER_UP_Bytes);
    CTS = 0;
    while (CTS == 0) {
      readBytes = L0_ReadBytes (i2c, 0x00, 1, replyBytes);
      if (readBytes == 0) {break;}
      if ( (replyBytes[0] & 0x80) == 0x80 ) { CTS = 1;}
    }
    if (CTS == 0) {
      /* SiTRACE("Read failed at add 0x%02X: no chip at this address\n", add); */
    } else {
      L0_WriteBytes(i2c, 0x00, sizeof(PART_INFO_Bytes),  PART_INFO_Bytes);
      CTS = 0;
      while (CTS == 0) {
        readBytes = L0_ReadBytes (i2c, 0x00, 13, replyBytes);
        if (readBytes == 0) {break;}
        if ( (replyBytes[0] & 0x80) == 0x80 ) { CTS = 1;}
      }
      if (CTS == 0) {
        /* SiTRACE("PART_INFO Read failed at add 0x%02X: no chip at this address\n", add); */
      } else {
        chiprev  =   replyBytes[1] & 0x0f;
        part     =   replyBytes[2] ;
        pmajor   =   replyBytes[3] ;
        pminor   =   replyBytes[4] ;
        pbuild   =   replyBytes[5] ;
        romid    =   replyBytes[12];
        demod_code[*Nb_FrontEnd] = 2100 + part;
        demod_add [*Nb_FrontEnd] = add;
        snprintf (demod_string[*Nb_FrontEnd], 1000, "Add 0x%02X: 'Si21%02d-%c%c%c ROM%x NVM%c_%cb%d'", add, part, chiprev + 0x40, pmajor, pminor, romid, pmajor, pminor, pbuild );
        *Nb_FrontEnd = *Nb_FrontEnd + 1;
      }
    }
  }
  return *Nb_FrontEnd;
}
#ifdef    SILABS_API_TEST_PIPE
 #ifdef   SILABS_API_VDAPPS
  #include "SiLabs_API_VDAPPS.c"
 #endif /* SILABS_API_VDAPPS */
/************************************************************************************************************************
  Silabs_API_Test function
  Use:        Generic test pipe function
              Used to send a generic command to the selected target.
  Returns:    0 if the command is unknow, 1 otherwise
  Porting:    Mostly used for debug during sw development.
************************************************************************************************************************/
signed   int  Silabs_API_Test                       (SILABS_FE_Context *front_end,    const char *target, const char *cmd, const char *sub_cmd, double dval, double *retdval, char **rettxt)
{
  signed   int res;
  signed   int i;
  signed   int start_time_ms;
  signed   int lock_time_ms;
  signed   int voltage_min;
  signed   int voltage_max;
  signed   int voltage;
  signed   int cont_tone_min;
  signed   int cont_tone_max;
  signed   int cont_tone;
  signed   int standard; signed   int freq;  signed   int bandwidth_Hz; signed   int stream; unsigned int symbol_rate_bps; signed   int constellation; signed   int polarization; signed   int band; signed   int num_data_slice; signed   int num_plp; signed   int count; signed   int T2_base_lite;
  front_end = front_end; /* To avoid compiler warning if not used */
  target    = target;    /* To avoid compiler warning if not used */
  cmd       = cmd;       /* To avoid compiler warning if not used */
  sub_cmd   = sub_cmd;   /* To avoid compiler warning if not used */
  dval      = dval;      /* To avoid compiler warning if not used */
  retdval   = retdval;   /* To avoid compiler warning if not used */
  rettxt    = rettxt;    /* To avoid compiler warning if not used */
  res = i = start_time_ms = lock_time_ms = voltage_min = voltage_max = voltage = cont_tone_min = cont_tone_max = cont_tone = 0;
  standard = freq = bandwidth_Hz = stream = symbol_rate_bps = constellation = polarization = band = num_plp = num_data_slice = count = T2_base_lite = 0;
  custom_status = &(FE_Status);
  res = standard = 0;
  voltage = cont_tone = 0;
  start_time_ms = system_time();
  SiTRACE("Silabs_API_Test (front_end, \"%s\", \"%s\", \"%s\", %f, &retdval, &rettxt);\n", target, cmd, sub_cmd, dval);
#ifdef   SILABS_API_VDAPPS
  if (strcmp_nocase(target,"VDAPPS" ) == 0) { SiLabs_API_VDAPPS (front_end, cmd, sub_cmd, dval, retdval, rettxt); return 1; }
#endif /* SILABS_API_VDAPPS */
#ifdef    USB_Capability
  if (strcmp_nocase(target, "ts"       ) == 0) { L0_Cypress_Process  (cmd, sub_cmd, dval, retdval, rettxt); return 1; }
  if (strcmp_nocase(target, "configure") == 0) { L0_Cypress_Configure(cmd, sub_cmd, dval, retdval, rettxt); return 1; }
  if (strcmp_nocase(target, "cget"     ) == 0) { L0_Cypress_Cget     (cmd, sub_cmd, dval, retdval, rettxt); return 1; }
  if (strcmp_nocase(target, "cypress"  ) == 0) { L0_Cypress_Process  (cmd, sub_cmd, dval, retdval, rettxt); return 1; }
  if (strcmp_nocase(target, "process"  ) == 0) { L0_Cypress_Process  (cmd, sub_cmd, dval, retdval, rettxt); return 1; }
#endif /* USB_Capability */
  if (strcmp_nocase(target,"wrapper"   ) == 0) {
    if (strcmp_nocase(cmd ,"c_n_loop"  ) == 0) {
      res =(int)dval;
      *retdval = 0.0;
      if (strcmp_nocase(sub_cmd ,"reset"     ) == 0) { SiLabs_API_Demod_reset(front_end); }
      for (i=0; i< res; i++) {
        SiLabs_API_Demod_status(front_end, custom_status);
        if ((int)(*retdval*100) != custom_status->c_n_100) {
          printf("(%6d) %6d ms: C/N  %8.2f dB\n", i, system_time() - start_time_ms, custom_status->c_n_100/100.0);
        }
        *retdval = custom_status->c_n_100/100.0;
      }
      snprintf(*rettxt, 1000, "C/N  %8.2f dB\n", custom_status->c_n_100/100.0);
      return 1;
    }
    if (strcmp_nocase(cmd ,"lock_loop" ) == 0) {
      res =(int)dval;
      *retdval = 0.0;
      for (i=0; i< res; i++) {
        count = -1;
        start_time_ms = system_time();
        SiLabs_API_Demod_reset(front_end);
        while (count !=2) {
          SiLabs_API_Demod_status_selection(front_end, custom_status, FE_LOCK_STATE);
          if (count != custom_status->demod_lock + custom_status->fec_lock) {
            count = custom_status->demod_lock + custom_status->fec_lock;
            printf("(%6d) %6d ms: demod_lock %d, fec_lock %d (count %d)\n", i, system_time() - start_time_ms, custom_status->demod_lock, custom_status->fec_lock, count);
          }
          if (count == 2) printf("\n");
          *retdval = custom_status->fec_lock;
          system_wait(10);
        }
      }
      snprintf(*rettxt, 1000, "fec_lock  %d\n", custom_status->fec_lock);
      return 1;
    }
    if (strcmp_nocase(cmd ,"init_ok"   ) == 0) {
      *retdval = (double) front_end->init_ok;
      snprintf(*rettxt, 1000, "init_ok %d\n", front_end->init_ok);
      return 1;
    }
#ifdef    TERRESTRIAL_FRONT_END
    if (strcmp_nocase(cmd ,"ter_rssi_offset"  ) == 0) {
      front_end->TER_RSSI_offset      = (int)dval;
      return 1;
    }
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
    if (strcmp_nocase(cmd ,"sat_rssi_offset"  ) == 0) {
      front_end->SAT_RSSI_offset      = (int)dval;
      return 1;
    }
#ifdef    LNBH26_COMPATIBLE
    if (strcmp_nocase(cmd ,"lnbh26" ) == 0) {
      if (strcmp_nocase(sub_cmd ,"a_b" ) == 0) {
        if ((int)dval == 1) {
          front_end->lnbh26->a_b = 1;
        } else              {
          front_end->lnbh26->a_b = 0;
        }
        *retdval = (double)front_end->lnbh26->a_b; sprintf(*rettxt, "a_b %d", (int)*retdval ); return 1;
      }
    }
#endif /* LNBH26_COMPATIBLE */
    if (strcmp_nocase(cmd ,"sat_auto_detect" ) == 0) {
      res = SiLabs_API_SAT_AutoDetectCheck(front_end);
      if (res) {
        snprintf(*rettxt, 1000, "SiLabs_API_SAT_AutoDetectCheck result %d: %s\n", res, Silabs_Standard_Text(res) );
      } else {
        snprintf(*rettxt, 1000, "SiLabs_API_SAT_AutoDetectCheck result %d: unlocked\n", res );
      }
      return 1;
    }
    if (strcmp_nocase(cmd ,"sat_toggle"      ) == 0) {
      res = SiLabs_API_SAT_AutoDetectCheck(front_end);
      if (res) {
        snprintf(*rettxt, 1000, "SiLabs_API_SAT_AutoDetectCheck result %d: %s\n", res, Silabs_Standard_Text(res) );
      } else {
        snprintf(*rettxt, 1000, "SiLabs_API_SAT_AutoDetectCheck result %d: unlocked\n", res );
      }
      return 1;
    }
    if (strcmp_nocase(cmd ,"sat_full_scan"   ) == 0) {
      voltage_min   = 13;
      voltage_max   = 18;
      cont_tone_min =  0;
      cont_tone_max =  1;
      if (strcmp_nocase(sub_cmd ,"vl"   ) == 0) {voltage_max = 13; cont_tone_max = 0; }
      if (strcmp_nocase(sub_cmd ,"hl"   ) == 0) {voltage_min = 18; cont_tone_max = 0; }
      if (strcmp_nocase(sub_cmd ,"vh"   ) == 0) {voltage_max = 13; cont_tone_min = 1; }
      if (strcmp_nocase(sub_cmd ,"hh"   ) == 0) {voltage_min = 18; cont_tone_min = 1; }
      SiLabs_API_switch_to_standard(front_end, SILABS_DVB_S, 0);
      for (i = 1; i<= (int)dval; i++) {
        res = 0;
        for (voltage = voltage_min; voltage <= voltage_max; voltage = voltage + 5) {
          for (cont_tone = cont_tone_min; cont_tone <= cont_tone_max; cont_tone = cont_tone + 1) {
            printf("\nSAT blindscan from %7.0f to %7.0f, sr from %4.1f to %4.1f Mb, voltage %2d cont_tone %d\n\n", 950.0, 2150.0, 1.0, 45.0, voltage, cont_tone);
            count = 0;
            start_time_ms = system_time();
            SiLabs_API_SAT_voltage_and_tone (front_end, voltage, cont_tone);
  #ifdef    UNICABLE_COMPATIBLE
            if (voltage  == 18) {  front_end->unicable->polarization = UNICABLE_HORIZONTAL;  }
            if (voltage  == 13) {  front_end->unicable->polarization = UNICABLE_VERTICAL;    }
            if (cont_tone == 0) {  front_end->unicable->band         = UNICABLE_LOW_BAND;    }
            if (cont_tone == 1) {  front_end->unicable->band         = UNICABLE_HIGH_BAND;   }
            front_end->unicable->bank         = front_end->unicable->satellite_position*4 + front_end->unicable->polarization*2 + front_end->unicable->band;
  #endif /* UNICABLE_COMPATIBLE */
            SiLabs_API_Channel_Seek_Init    (front_end, 950000, 2150000, 8000000, 0, 1000000, 45000000, 0, 0, 0, 0);
            while ( SiLabs_API_Channel_Seek_Next(front_end, &standard, &freq,  &bandwidth_Hz, &stream, &symbol_rate_bps, &constellation, &polarization, &band, &num_data_slice, &num_plp, &T2_base_lite) == 1) {
              count++;
              lock_time_ms = system_time();
              SiLabs_API_FE_status(front_end, custom_status);
              printf("......% 3d .. voltage %2d cont_tone %d count %3d (total %3d): %-6s Channel detected (standard %d, SR %9d). freq L %7d (Ku %8d) "
                     , i, voltage, cont_tone, count, res + count , Silabs_Standard_Text(standard), standard, symbol_rate_bps, freq, freq + 9750000 + (10600000-9750000)*cont_tone);
              printf("%c", 0x07);
              while ((int)(custom_status->c_n_100/100.0) < 100) {
                SiLabs_API_FE_status(front_end, custom_status);
                if (system_time() - lock_time_ms > 5000) break;
              }
              printf(" C/N %8.2f dB (%6.3f s)", custom_status->c_n_100/100.0, (system_time() - lock_time_ms)/1000.0);
              system_wait(2000);
              SiLabs_API_FE_status(front_end, custom_status);
              printf(" C/N %8.2f dB (%6.3f s)", custom_status->c_n_100/100.0, (system_time() - lock_time_ms)/1000.0);
              printf(" SSI %3d SQI %3d", custom_status->SSI, custom_status->SQI);
              printf("\n");
            }
            SiLabs_API_Channel_Seek_End(front_end);
  #ifdef    UNICABLE_COMPATIBLE
            if (front_end->unicable->installed) {
              snprintf(*rettxt, 1000, "Unicable scan, voltage %2d, cont_tone %d, %5d channels found in %6.1f s", voltage, cont_tone, count, (system_time() - start_time_ms)/1000.0 );
            } else {
              snprintf(*rettxt, 1000, "Normal scan,   voltage %2d, cont_tone %d, %5d channels found in %6.1f s", voltage, cont_tone, count, (system_time() - start_time_ms)/1000.0 );
            }
  #else  /* UNICABLE_COMPATIBLE */
            snprintf(*rettxt, 1000, "voltage %2d, cont_tone %d, %5d channels found in %6.1f s", voltage, cont_tone, count, (system_time() - start_time_ms)/1000.0 );
  #endif /* UNICABLE_COMPATIBLE */
            printf ("---------------------- %s -------------------------------------------------------\n\n\n", *rettxt);
            res = res + count;
            system_wait(5000);
          }
        }
  #ifdef    UNICABLE_COMPATIBLE
        if (front_end->unicable->installed) {
          snprintf(*rettxt, 1000, "Unicable full scan %3d: %4d channels found", i, res);
        } else {
          snprintf(*rettxt, 1000, "Normal   full scan %3d: %4d channels found", i, res);
        }
  #else  /* UNICABLE_COMPATIBLE */
        snprintf(*rettxt, 1000, "full scan %3d: %4d channels found", i, res);
  #endif /* UNICABLE_COMPATIBLE */
        printf ("---------------------- %s -------------------------------------------------------\n\n\n", *rettxt);
      }
      return 1;
    }
    if (strcmp_nocase(cmd ,"sat_full_scan"   ) == 0) {
      voltage_min   = 13;
      voltage_max   = 18;
      cont_tone_min =  0;
      cont_tone_max =  1;
      if (strcmp_nocase(sub_cmd ,"vl"   ) == 0) {voltage_max = 13; cont_tone_max = 0; }
      if (strcmp_nocase(sub_cmd ,"hl"   ) == 0) {voltage_min = 18; cont_tone_max = 0; }
      if (strcmp_nocase(sub_cmd ,"vh"   ) == 0) {voltage_max = 13; cont_tone_min = 1; }
      if (strcmp_nocase(sub_cmd ,"hh"   ) == 0) {voltage_min = 18; cont_tone_min = 1; }
      SiLabs_API_switch_to_standard(front_end, SILABS_DVB_S, 0);
      for (i = 1; i<= (int)dval; i++) {
        res = 0;
        for (voltage = voltage_min; voltage <= voltage_max; voltage = voltage + 5) {
          for (cont_tone = cont_tone_min; cont_tone <= cont_tone_max; cont_tone = cont_tone + 1) {
            printf("\nSAT blindscan from %7.0f to %7.0f, sr from %4.1f to %4.1f Mb, voltage %2d cont_tone %d\n\n", 950.0, 2150.0, 1.0, 45.0, voltage, cont_tone);
            count = 0;
            start_time_ms = system_time();
            SiLabs_API_SAT_voltage_and_tone (front_end, voltage, cont_tone);
  #ifdef    UNICABLE_COMPATIBLE
            if (voltage  == 18) {  front_end->unicable->polarization = UNICABLE_HORIZONTAL;  }
            if (voltage  == 13) {  front_end->unicable->polarization = UNICABLE_VERTICAL;    }
            if (cont_tone == 0) {  front_end->unicable->band         = UNICABLE_LOW_BAND;    }
            if (cont_tone == 1) {  front_end->unicable->band         = UNICABLE_HIGH_BAND;   }
            front_end->unicable->bank         = front_end->unicable->satellite_position*4 + front_end->unicable->polarization*2 + front_end->unicable->band;
  #endif /* UNICABLE_COMPATIBLE */
            SiLabs_API_Channel_Seek_Init    (front_end, 950000, 2150000, 8000000, 0, 1000000, 45000000, 0, 0, 0, 0);
            while ( SiLabs_API_Channel_Seek_Next(front_end, &standard, &freq,  &bandwidth_Hz, &stream, &symbol_rate_bps, &constellation, &polarization, &band, &num_data_slice, &num_plp, &T2_base_lite) == 1) {
              count++;
              lock_time_ms = system_time();
              SiLabs_API_FE_status(front_end, custom_status);
              printf("......% 3d .. voltage %2d cont_tone %d count %3d (total %3d): %-6s Channel detected (standard %d, SR %9d). freq L %7d (Ku %8d) "
                     , i, voltage, cont_tone, count, res + count , Silabs_Standard_Text(standard), standard, symbol_rate_bps, freq, freq + 9750000 + (10600000-9750000)*cont_tone);
              printf("%c", 0x07);
              while ((int)(custom_status->c_n_100/100.0) < 1) {
                SiLabs_API_FE_status(front_end, custom_status);
                if (system_time() - lock_time_ms > 5000) break;
              }
              printf(" C/N %8.2f dB (%6.3f s)", custom_status->c_n_100/100.0, (system_time() - lock_time_ms)/1000.0);
              system_wait(2000);
              SiLabs_API_FE_status(front_end, custom_status);
              printf(" C/N %8.2f dB (%6.3f s)", custom_status->c_n_100/100.0, (system_time() - lock_time_ms)/1000.0);
              printf(" SSI %3d SQI %3d", custom_status->SSI, custom_status->SQI);
              printf("\n");
            }
            SiLabs_API_Channel_Seek_End(front_end);
  #ifdef    UNICABLE_COMPATIBLE
            if (front_end->unicable->installed) {
              snprintf(*rettxt, 1000, "Unicable scan, voltage %2d, cont_tone %d, %5d channels found in %6.1f s", voltage, cont_tone, count, (system_time() - start_time_ms)/1000.0 );
            } else {
              snprintf(*rettxt, 1000, "Normal scan,   voltage %2d, cont_tone %d, %5d channels found in %6.1f s", voltage, cont_tone, count, (system_time() - start_time_ms)/1000.0 );
            }
  #else  /* UNICABLE_COMPATIBLE */
            snprintf(*rettxt, 1000, "voltage %2d, cont_tone %d, %5d channels found in %6.1f s", voltage, cont_tone, count, (system_time() - start_time_ms)/1000.0 );
  #endif /* UNICABLE_COMPATIBLE */
            printf ("---------------------- %s -------------------------------------------------------\n\n\n", *rettxt);
            res = res + count;
            system_wait(5000);
          }
        }
  #ifdef    UNICABLE_COMPATIBLE
        if (front_end->unicable->installed) {
          snprintf(*rettxt, 1000, "Unicable full scan %3d: %4d channels found", i, res);
        } else {
          snprintf(*rettxt, 1000, "Normal   full scan %3d: %4d channels found", i, res);
        }
  #else  /* UNICABLE_COMPATIBLE */
        snprintf(*rettxt, 1000, "full scan %3d: %4d channels found", i, res);
  #endif /* UNICABLE_COMPATIBLE */
        printf ("---------------------- %s -------------------------------------------------------\n\n\n", *rettxt);
      }
      return 1;
    }
    if (strcmp_nocase(cmd ,"sat_tag"    ) == 0) {
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { snprintf(*rettxt, 1000, SiLabs_SAT_Tuner_Tag(front_end->Si2183_FE->tuner_sat) ); return 1; }
#endif /* Si2183_COMPATIBLE */
      snprintf(*rettxt, 1000, "Unknown chip" ); return 1;
    }
#ifdef    DEMOD_DVB_S2X
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) {
    if (strcmp_nocase(cmd,"DVB_S2"         ) == 0) {
      if (strcmp_nocase(sub_cmd,"ISI"         ) == 0) {
        Si2183_L1_DVBS2_STATUS(front_end->Si2183_FE->demod, 0);
        for  (i=0; i< front_end->Si2183_FE->demod->rsp->dvbs2_status.num_is; i++) {
          SiLabs_API_Get_Stream_Info (front_end, i, &stream, &constellation , &res);
          SiTRACE("DVB-S2 stream %2d: ID %d, constellation %d, code rate %d\n",i, stream, constellation, res);
        }
      }
      if (strcmp_nocase(sub_cmd,"PLS"         ) == 0) {
        i   = SiLabs_API_SAT_Gold_Sequence_Init((int)dval);
        res = SiLabs_API_SAT_PLS_Init (front_end, i);
        SiTRACE("DVB-S2 Gold_Sequence_Init %8d PLS_Init %8d : %d\n", (int)dval, i, res);
      }
      return 1;
    }
  }
#endif /* Si2183_COMPATIBLE */
#endif /* DEMOD_DVB_S2X */
#ifdef    UNICABLE_COMPATIBLE
    if (strcmp_nocase(cmd ,"sat_scan_unicable" ) == 0) {
      count = 0;
      printf("Unicable scan loop starting (%d loops)...\n", (int)dval);
      front_end->unicable->satellite_position = UNICABLE_POSITION_A;
      front_end->unicable->polarization       = UNICABLE_VERTICAL;
      front_end->polarization                 = SILABS_POLARIZATION_VERTICAL;
      front_end->unicable->band               = UNICABLE_HIGH_BAND;
      front_end->band                         = SILABS_BAND_HIGH;
      front_end->unicable->bank = front_end->unicable->satellite_position*4 + front_end->unicable->polarization*2 + front_end->unicable->band;
      SiLabs_API_switch_to_standard(front_end, SILABS_DVB_S, 0);
      for (res = 0; res < (int)dval; res++) {
        SiLabs_API_Channel_Seek_Init    (front_end, 1820000, 1960000, 8000000, 0, 1000000, 45000000, 0, 0, 0, 0);
        while ( SiLabs_API_Channel_Seek_Next(front_end, &standard, &freq,  &bandwidth_Hz, &stream, &symbol_rate_bps, &constellation, &polarization, &band, &num_data_slice, &num_plp, &T2_base_lite) == 1) {
          printf("\n################ %-6s Channel detected (standard %d, SR %9d). freq %d   ################################\n\n", Silabs_Standard_Text(standard), standard, symbol_rate_bps, freq);
  #ifdef    PLOT_ON_LIMITED_RANGE
          if (freq >= LIMITED_RANGE_MIN_RF/1000) {
            if (freq <= LIMITED_RANGE_MAX_RF/1000) {
  #endif /* PLOT_ON_LIMITED_RANGE */
              printf("%c", 0x07);
              count++;
              system_wait(2000);
  #ifdef    PLOT_ON_LIMITED_RANGE
              }
            }
  #endif /* PLOT_ON_LIMITED_RANGE */
        }
        SiLabs_API_Channel_Seek_End(front_end);
        snprintf(*rettxt, 1000, "%5d loops, channel at 1926 found %5d times", res+1, count);
        printf ("---------------------- %s -------------------------------------------------------\n\n\n", *rettxt);
        system_wait(1000);
        if (count != (res+1) ) {
/*          system("pause"); */
        }
      }
      return 1;
    }
#endif /* UNICABLE_COMPATIBLE */
#endif /* SATELLITE_FRONT_END */
    snprintf(*rettxt, 1000, "no '%s' command implemented for wrapper\n", cmd );
    return 1;
  }
#ifdef    UNICABLE_COMPATIBLE
  if (strcmp_nocase(target,"unicable"  ) == 0) {
    return SiLabs_Unicable_API_Test(front_end->unicable, target, cmd, sub_cmd, dval, retdval, rettxt);
  }
#endif /* UNICABLE_COMPATIBLE */
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { Si2183_L2_Test(front_end->Si2183_FE, target, cmd, sub_cmd, dval, retdval, rettxt); return 1;}
#endif /* Si2183_COMPATIBLE */
  snprintf(*rettxt, 1000, "no command implemented so far for '%s', can not process '%s %s %s %f'\n", cmd, target, cmd, sub_cmd, dval);

  return 0;
}
#endif /* SILABS_API_TEST_PIPE */
/************************************************************************************************************************
  NAME: SiLabs_API_TAG_TEXT
  DESCRIPTION: SiLabs API information function used to retrieve the version information of the SiLabs API wrapper
  Returns:    the SiLabs API version information string
************************************************************************************************************************/
char*         SiLabs_API_TAG_TEXT                   (void) { return (char *)"V2.8.0"; }

#ifdef    __cplusplus
}
#endif /* __cplusplus */
