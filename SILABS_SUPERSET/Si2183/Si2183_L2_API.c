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
/***************************************************************************************
                  Silicon Laboratories Broadcast Si2183 Layer 2 API


   L2 API for commands and properties
   FILE: Si2183_L2_API.c
   Supported IC : Si2183
   Compiled for ROM 2 firmware 5_B_build_1
   Revision: V0.3.5.1
   Tag:  V0.3.5.1
   Date: November 06 2015
**************************************************************************************/
/* Change log:
 As from V0.3.5.1:
      <correction>[flags] Re-adding 'endif DEMOD_DVB-T2 ' following Si2183_TerAutoDetectOff (mistakenly removed as from v0.3.1.0)
        No big impact, but this created an inconsistent naming in 'define/endif' sequence, and
                entire removal of SILABS_API_TEST_PIPE was not possible anymore.

 As from V0.3.5.0:
    <improvement>[traces] Adding explicit ISDB-T code in Si2183_L2_Tune.
        Requires SiLabs_TER_Tuner V0.6.6 (with definition of L1_RF_TER_TUNER_MODULATION_ISDBT)
        NB: As stated in SiLabs_TER_Tuner V0.6.6 change log, this is more a cosmetic change, to support ISDB-T in a nicer way.

 As from V0.3.4.0:
    <Wrapper> Wrapper V2.8.0
    <improvement>[SCAN/Traces] In Si2183_L2_SW_Init: activating trylock traces during blindscan (this has no effect unless ALLOW_Si2183_BLINDSCAN_DEBUG is active)
    <improvement>[SCAN/Abort] In Si2183_L2_Channel_Seek_Abort: Calling Si2183_L1_SCAN_CTRL to end a potential scan
    <improvement>[SILENT] In Si2183_L2_SILENT: calling Si2183_Configure to make sure GPIOs are set back to active states

 As from V0.3.3.1:
    <firmware> With FW 5_5b16 on x55 parts
    <firmware> With FW 5_9b6 on  x59 parts
    <firmware> With FW 5_0b19 on x50 parts
    <firmware> With FW 4_0b31 on x40 parts
    <correction> registers address matching -x50,x55 and x60 parts
    <improvement> more registers logged by Si2183_L2_Health_Check(). Function called in case blindscan timeout
    <improvement> demodulator part number and firmware version logged when calling Si2183_L2_Channel_Seek_Init()

 As from V0.3.3.0:
    <improvement>[DVB-T/Checks] Only adding DVB-T2 check code if CHECK_DVB_T2_SIGNALLING is declared
    <firmware> With FW 6_4b7  on x63 parts with    CHANNEL_BONDING
    <firmware> With FW 6_3b6  on x63 parts without CHANNEL_BONDING
    <firmware> With FW 6_0b13 on x60 parts
    <firmware> With FW 5_0b18 on x50 parts
    <firmware> With FW 5_5b15 on x55 parts
    <firmware> With FW 4_0b30 on x40 parts
    <new_feature>[DVB-S2/MIS] In Si2183_L2_Seek_next: calling DVBS2_STATUS and setting num_plp = num_is when locked in DVB-S2
    <improvement>[ATV]
      In Si2183_Media: returning Si2183_TERRESTRIAL for Si2183_DD_MODE_PROP_MODULATION_ANALOG
                       returning 0 for unknown standards
      In Si2183_L2_switch_to_standard: setting front_end->demod->media in all cases (not only when dtv_demod_needed == 1)
      In Si2183_L2_switch_to_standard: always calling TER_TUNER_ATV_LO_INJECTION if new_standard is Si2183_DD_MODE_PROP_MODULATION_ANALOG
    <compatibility>[TRACES/GET_REG] always compiling Si2183_L2_GET_REG
    <improvement>[TER/handshake] Moving ddRestartTime in Si2183_L2_Context, for easier tracking.
    <improvement>[SAT/DISEQC] In Si2183_L2_prepare_diseqc_sequence and Si2183_L2_send_diseqc_sequence: initial value of bus_state set based on a call to Si2183_L1_DD_DISEQC_STATUS.
      This saves 12 ms when the bus is ready.

*/
/* Older changes:

 As from V0.3.2.0:
    <Wrapper> Wrapper V2.7.9
    <firmware> With FW 6_0b11 on x60 parts
    <firmware> With FW 5_5b14 on x55 parts
    <firmware> With FW 5_0b17 on x50 parts
    <correction>[DVB-T2/debug] In Si2183_L2_lock_to_carrier: only checking DVB-T2 misc infos if _DVB_T2_SIGNALLING_H_ is declared (only possible with SiLabs_DVB_T2_Signalling.c/SiLabs_DVB_T2_Signalling.h files added to the project).
    <correction>[SAT/UnicableII] In Si2183_L2_Channel_Seek_Init: using front_end->unicable_mode to set the BW value in Unicable
    <improvement>[Si2183_B63_COMPATIBLE] Adding missing comment around CHANNEL_BONDING tag, to avoid compilation error.
    <improvement>[I2C/Pass-Through] In Si2183_Configure: Setting scl_mast_slr register to avoid reduction of Thd_dat from HOST to MAST
    <compatibility>[compiler/warnings] In Si2183_LoadFirmwareSPI_Split: i defined as unsigned int.
    <compatibility>[compiler/warnings] In Si2183_DVB_C_max_lock_ms: afc_khz defined as signed int to allow comparison with symbol_rate_baud.
    <compatibility>[compiler/warnings] In Si2183_L2_Set_Index_and_Tag: tag defined as const char*.
    <compatibility>[compiler/warnings] In Si2183_L2_Test: target, cmd and sub_cmd declared as const char*.
    <compatibility>[TestPipe/chip_detect] In Si2183_L2_Test: Now returning '83A' for Si2167D parts (only used for macro selection).

 As from V0.3.1.0:
    <improvement>[init/AGC] Forcing the use of AGC2 internal loop for TER and AGC1 internal loop for SAT
      In Si2183_L2_TER_AGC: Forcing TER AGC settings in agc2 internal loop
      In Si2183_L2_SAT_AGC: Forcing SAT AGC settings in agc1 internal loop
    <improvement>[debug/registers] Updating register codes to match Si2183 to allow using Si2183_L2_Health_Check
    <improvement>[DVB-T/No_T2] In Si2183_prepare_DD_MODE: calling Si2183_TerAutoDetect to force front_end->auto_detect_TER if the part doesn't support T2.
      This is only useful when building code with DEMOD_DVB_T2 to be compatible with parts supporting T2 and parts not supporting T2.
    <improvement>[DVB-C/blindscan] Introducing Si2183_DVBC_MAX_SCAN_TIME to handle difficult DVVB-C blindscan cases where the analyzis time is higher than the DVB-C lock time
    <new_feature>[DVB-T2/MPLP] In Si2183_L2_lock_to_carrier: tracing the PLP values in case the signal is DVB-T2/MPLP (only if SiTRACES are defined).
      This can be useful to check the MPLP implementation in the application layer.
    <correction>[Lock_abort/Handshake] Corrected front_end->lockAbort management in Si2183_L2_lock_to_carrier and Si2183_L2_Channel_Lock_Abort (disabled is front_end->lockAbort is set to 0).
      Now only setting front_end->lockAbort to 0 before leaving when front_end->lockAbort = 1.
      This only had an impact on applications calling SiLabs_API_Channel_Seek_Abort while in handshake mode with front_end->handshakePeriod_ms lower
        than 500 ms (the amount of time needed to detect a 'never_lock' situation).
    <new_feature>[test/property] In Si2183_L2_Test: Adding a 'setProperty' option to allow setting any property.

 As from V0.3.0.0:
    <compatibility>[compiler/warnings] In Si2183_plot: modified traces for long int
    <firmware> With FW 6_0b7  on x60 parts when CHANNEL_BONDING is NOT required

 As from V0.2.9.0:
    <Wrapper> Wrapper V2.7.4
    <firmware> With FW 6_3b3  on '80' x60 parts
    <firmware> With FW 6_4b3  on x63 parts when CHANNEL_BONDING is required
    <firmware> With FW 6_3b3  on x63 parts when CHANNEL_BONDING is NOT required
    <firmware> With FW 6_2b2  on x60 parts when CHANNEL_BONDING is required
    <firmware> With FW 6_0b6  on x60 parts when CHANNEL_BONDING is NOT required
    <new_feature>[TS/Duals/Channel_Bonding] For Duals, CHANNEL_BONDING is now possible.
    <correction>[Si2180_B60_COMPATIBLE/ISDB-T/FW] In Si2183_PowerUpWithPatch: Correcting part_info.chiprev test for x80 parts (these are 'B' parts)
    <improvement>[standard_switch]
      Adding Si2183_prepare_DD_MODE to set dd_mode.auto_detect and dd_mode.modulation based on the requested standard
      In Si2183_L2_switch_to_standard: Using Si2183_prepare_DD_MODE to set dd_mode.auto_detect and dd_mode.modulation
      NB: This is because some customers use to call Si2183_L2_switch_to_standard without doing a lock. In this situation the demod could
            be inadvertently set in non-auto mode. With the changes the auto lock mode is preserved.
      NB: Applications using a normal switch/lock sequence don't require these changes (which don't change their behavior when applied).
    <improvement>[compatibility] In Si2183_plot: minor cosmetic changes to avoid compiler warnings with some compilers.

 As from V0.2.8.0:
    <Wrapper> Wrapper V2.7.1
    <new_Part>[x63] In Si2183_PowerUpWithPatch: Adding compatibility with x63 parts.
    <firmware> With FW 6_3b1  on x63 parts
    <firmware> With FW 5_5b13 on x55 parts
    <correction>[MCNS/lock/bw]
      In Si2183_L2_lock_to_carrier: setting MCNS bw as ter_bandwidth_hz/1000000 (previously hardcoded as 8)
    <correction>[DVB-T2/FEF]
      In Si2183_Configure: Correcting the FEF pin settings when NOT in DVB-T2 (when MPs are in 'default' mode).
        (This didn't generate issues because generally the FEF pin is also disabled when not in DVB-T).
    <correction>[SAT/DiSEqC_read]
      In Si2183_L2_read_diseqc_reply: Correcting the test to read DiSEqC bytes.
    <improvement>[ISDB-T/test]
      In Si2183_Configure: removing ISDB-T property settings (used for testing). (No effect on other standards).
    <improvement>[Traces/setup]
      In Si2183_Configure: Tracing the function name when tracing the media.
    <improvement>[traces/blindscan]
      In Si2183_L2_SW_Init: setting front_end->misc_infos = 0x00000000;
        This value can be modified when scan debugging is required.
    <improvement>[DVB-T2/TestPipe]
      In testcode used with SiLabs_DVB_T2_Signalling.h:
        Adding Si2164 and Si2167B register definitions to stay compatible with Si2183_READ/Si2183_WERITE macros (now compatible with legacy parts)
        Using SiTRACE_X instead of SiTRACE whenever required to avoid compilation errors due to tag and level tracing.

 As from V0.2.7.0:
    <firmware> Correction in tags for x5B parts FW loading
    <firmware> With FW 6_0b5  on X60 parts
    <firmware> With FW 5_0b16 on X50 parts
    <improvement>[Blindscan/traces/spectrum]
      In Si2183_plot: adapted for better compatibility with various compilers. Not using floats anymore.
      In Si2183_L2_Channel_Seek_Next: adding traces to help possible blindscan issues on difficult channels.
    <compatibility>[x55/DVB-S2/MIS]
      In Si2183_PowerUpWithPatch: setting MIS_capability field for x55 parts
    <new_feature>[Debug/Spectrum/FFT]
      Adding FFT tracing capability. This can be useful to avoid using a spectrum analyzer to get a view of the channel spectrum.
      NB: This is only active if Si2183_FFT_CAPABILITY is defined.
    <improvement>[Blindscan/SAT/Turksat] Due to low SR closely spaced channels present on Turksat it may happen that some chunks take more than 60s.
      To cope with this, the SAT blindscan timeout (only used in case the FW crhashes, which is not supposed to happen) is increased
        #define Si2183_SAT_MAX_SEARCH_TIME 120000
      NB: This has no impact on the scan duration. It allows the Turksat channels to be detected as expected.
    <improvement>[Debug/Spectrum/Traces]
      Adding front_end->misc_infos in Si2183_L2_Context to pass various parameters from L3.
        This will contain:
          misc_infos[ 7: 0] : LNB control voltage value
          misc_infos[11: 8] : LNB control tone value
          misc_infos[15:12] : Trigger FFT when Si2183_L2_Tune is called
          misc_infos[19:16] : Trace blindscan spectrum
          misc_infos[23:20] : Trace blindscan trylocks
          misc_infos[24]    : Trace DVB-T2 signalling
      In Si2183_L2_Tune:
        If ( front_end->misc_infos & 0x00001000 ) Trigger FFT tracing.
      In Si2183_L2_Channel_Seek_Next:
        Adding current frequency and front_end->misc_infos to blindscan traces.
          This will allow identifying the SAT quadrant currently scanned.
        If ( front_end->misc_infos & 0x00010000 ) Trigger Spectrum tracing.
        If ( front_end->misc_infos & 0x00100000 ) Trigger Trylock tracing.
      Using front_end->cumulativeScanTime to store time spent in Si2183_L2_Channel_Seek_Next (as already done for 'non-blind' scan).

 As from V0.2.6.0:
    <Wrapper> Wrapper V2.7.1
    <firmware> With FW 6_0b3  on X60 parts, to avoid potential DVB-S blindscan misses if checking fec_lock (regression in FW as from 6_0b).
    <firmware> With FW 5_5b11 on X55 parts, to avoid potential DVB-S blindscan misses if checking fec_lock (regression in FW as from 5_5b6).
    <correction>[DVB-S/blindscan/fec_lock] Correction done in FW.
      Background info on the regression: To avoid rare false DVB-S lock on LTE signals, and additional level of lock checking has been implemented.
        The check consists in making sure that at least one valid TS packet has been received (when locked in DVB-S).
        If this is not the case, fec_lock is reported as '0' while demod_lock is '1'.
        This is OK for 'lock_to_carrier' but not for DVB-S blindscan.
        The new FWs correct this, coming back to the previous behavior during SAT blindscan.
      NB: This has an effect on the application only under the following conditions:
        SAT blindscan
        Locked on DVB-S following a call to 'SeekNext' --> 'SeekNext' returns 1.
        The application is calling the status function and then checking status->fec_lock before accepting the channel.
      No issue for applications relying on the return value of 'SeekNext'.
      No issue for applications performing a 'lock_to_carrier' once a carrier has been detected using 'SeekNext'.

 As from V0.2.5.0:
    <improvement>[DVB-C/lock_timeout] In Si2183_DVB_C_max_lock_ms: Changes to avoid value overflow when afc_freq above 192 kHz, while still using no floats.
    <Wrapper> Wrapper V2.7.0
    <firmware> With FW 6_0b2 in SPI mode on X60 parts

 As from V0.2.3.0:
    <wrapper> Wrapper V2.6.6
    <firmware> With FW 6_0b2 on X60 parts.
    <new_feature>[init/force_full_init] In Si2183_L2_switch_to_standard: using new defines for force_full_init (instead of using only 0 or 1).
      This is useful to allow setting up the entire frontend in any mode using a single call to Si2183_L2_switch_to_standard.
        #define Si2183_SKIP_DEMOD_INIT      0x02 (useful if demod already initialized using broadcast_i2c)
        #define Si2183_FORCE_TER_TUNER_INIT 0x04 (useful to initialize the TER tuner while the final standard is SLEEP or a SAT standard)
        #define Si2183_FORCE_SAT_TUNER_INIT 0x08 (useful to initialize the SAT tuner while the final standard is SLEEP or a TER standard)
        #define Si2183_FORCE_DEMOD_INIT     0x10 (useful to initialize the demodulator while the final standard is SLEEP)
        #define Si2183_USE_TER_CLOCK        0x20 (useful with Si2183_FORCE_DEMOD_INIT if using the TER clock)
        #define Si2183_USE_SAT_CLOCK        0x40 (useful with Si2183_FORCE_DEMOD_INIT if using the SAT clock)
      Most changes are only done if force_full_init > 1 (i.e. the new flags are used).
      Other changes consist in only sending tuner commands when tuners are active, to cope with the new features.

      Use cases:
        Normal call with no init:
          SiLabs_API_switch_to_standard  (fe[0], standard, 0 );

        Normal call with init forced (parts actually initialized depend on standard):
          SiLabs_API_switch_to_standard  (fe[0], standard, 1 );

        New: Only going through the demodulator init then putting it in SLEEP mode, assuming that the TER clock is already on:
          SiLabs_API_switch_to_standard  (fe[0], SILABS_SLEEP, Si2183_FORCE_DEMOD_INIT | Si2183_USE_TER_CLOCK );

        New: Dual front_end init using Broadcast_i2c, then putting both frontends in SLEEP after initializing all parts:
          SiLabs_API_Demods_Broadcast_I2C(fes, 2 );
          SiLabs_API_switch_to_standard  (fe[0], SILABS_SLEEP, Si2183_SKIP_DEMOD_INIT | Si2183_FORCE_SAT_TUNER_INIT | Si2183_FORCE_TER_TUNER_INIT );
          SiLabs_API_switch_to_standard  (fe[1], SILABS_SLEEP, Si2183_SKIP_DEMOD_INIT | Si2183_FORCE_SAT_TUNER_INIT | Si2183_FORCE_TER_TUNER_INIT );

    <improvement>[traces]
      In Si2183_standardName: now also returning a string for ANALOG.
      In Si2183_Media: tracing the value of standard when it's unknown.
      In Si2183_L2_switch_to_standard: tracing the state of all parts when complete.

 As from V0.2.2.0:
    <wrapper> Wrapper V2.6.6
    <correction>[dual/triple/quad/broadcast_I2c] In Si2183_PowerUpUsingBroadcastI2C: Only loading FW in broadcast_I2C mode. StartFirmware now done in normal mode.
    <improvements>[traces/dual/triple/quad/broadcast_I2c] In Si2183_PowerUpWithPatch: tracing which parts of the function are skipped when using broadcast_I2C to load FW in several parts at once.
    <improvement>[spectrum/plot] In Si2183_plot: Correcting frequency values displayed in Unicable
    <improvement>[traces/blindscan] In Si2183_L2_Channel_Seek_Next: Tracing symbol rate value when locked
    <improvement>[traces/duals/die] In Si2183_Configure: also tracing the die value (used to identify duals). Mainly useful when using duals.
    <compatibility>[Testpipe/IQ] Making Si2183_L2_Get_Constellation_IQ compatible with all API-controlled parts.

 As from V0.2.0.0:
    <improvement>[Dual/robustness] In Si2183_L2_switch_to_standard: making sure the i2c passthrough is disabled before returning.
      This helps when there are execution errors accessing the TER or SAT tuner (this should not happen, but may occur during development).
      This is to prevent the i2c bus from being stalled in a dual/triple/quad) situation where both pass through should never be enabled
        simultaneously. NB: Using dedicated INDIRECT_I2C _CONNECTION settings the application can avoid this situation (the recommendation is to use a single pass through).

 As from V0.1.9.0:
    <testpipe>[DVB-C2/EWS] In Si2183_L2_Test: adding capability to retrieve the DVB-C2 EWS bit information.
    <improvement>[Traces] In Si2183_PowerUpUsingBroadcastI2C: using SiTRACE_X since the function uses several demods.

 As from V0.1.8.0:
    <wrapper> Wrapper V2.6.2
    <firmware> With FW 6_0b1 on X60 parts, with proper GET_REV return values.
    <improvement>[FW/updating]
        Setting a generic FW name for each part's FW while '#including' the FW file.
      In Si2183_PowerUpWithPatch:
        Hardcoding PMAJOR/PMINOR/PBUILD values used to check against PART_INFO values before loading FW. This removes the need to have these values set in FW files.
        Computing nb of lines to load based on the generic FW name.
        All these changes remove the need to change Si2183_PowerUpWithPatch when updating the FW.
    <improvement>[DVB-C/timeout] In Si2183_DVB_C_max_lock_ms: changing swt formula to better match legacy devices. Changing default swt_coef to 14 (previously 13) and offset back to 100.

 As from V0.1.7.0:
    <wrapper> Wrapper V2.6.2
    <firmware> With FW 6_0b1 on X60 parts
    <firmware> With FW 5_Bb5 on X5A parts
    <firmware> With FW 5_5b7 on X55 parts
    <firmware> With FW 2_2b9 on X22 parts

    <improvement>[power_consumption/Tuner_standby] In Si2183_L2_switch_to_standard: on first init, setting the SAT tuner and TER tuner to STANDBY when they are only used as clock sources, to save power.
      This is done only if SAT_TUNER_STANDBY_WITH_CLOCK and TER_TUNER_STANDBY_WITH_CLOCK are defined, because all tuners may not have the capability to continue driving a clock while in standby.
    <improvement>[DVB-C/timeout] In Si2183_DVB_C_max_lock_ms: changing swt formula to avoid overflows. Changing default swt_coef to 13 (previously 11).
    <improvement>[DVB_T2/MPLP/Seek] In Si2183_L2_Channel_Seek_Next: calling Si2183_L1_DVBT2_PLP_SELECT to set the PLP selection mode to 'auto'.
      The previous version required this to be done at MW level during a DVB-T2 scan with multiple PLPs.
    <compatibility>[Xtal/Cap/SUPERSET]
      In Si2183_L2_SW_Init: setting default value of start_clk.tune_cap
        It can be overwritten later on by calling SiLabs_API_XTAL_Capacitance if different values need to be used
          for different platforms (i.e. when using Xtals with different internal capacitance).
      In Si2183_WAKEUP: only forcing start_clk.tune_cap when not driving a xtal. Otherwise, use the value set in Si2183_L2_SW_Init and possibly overwritten by a call to SiLabs_API_XTAL_Capacitance.

 As from V0.1.6.0:
    <compatibility>[SILABS_SUPERSET/TER/SAT] Replacing tags in several functions  to allow compiling for TER-only or SAT-only
    Si2183_Configure
    Si2183_L2_SW_Init
    Si2183_L2_Set_Index_and_Tag
    Si2183_L2_HW_Connect
    <compatibility>[SILABS_SUPERSET/NO_TER] Removing AGC2 trace in Si2183_L2_Channel_Seek_Next because it uses the TER agc
    <improvement>[DVB-T/T2/ISDB-T/never lock] In Si2183_L2_lock_to_carrier: checking rsqstat_bit5 instead of rsqint_bit5
      rsqstat_nit5 is the 'never lock' flag for DVB-T/T2 and ISDB-T.
      This flag is raised:
      - In DVB-T when correlation with TPS cannot be achieved
      - In DVB-T2 when P1 symbol is not detected
      - In auto_T_T2 when neither P1 nor TPS are detected.
      - In ISDB-T when TMCC correlation cannot be achieved.
      rsqint_bit5 signals the transition from 0 to 1 of rsqstat_bit5, and is cleared using 'INTACK_CLEAR'.
      While checking rsqint_bit5 with 'INTACK_CLEAR' the transition can be cleared inadvertently if it occurs during the execution of DD_STATUS (rate around 4%).
      In this case, Si2183_L2_lock_to_carrier would return 0 (i.e 'not locked') after the timeout instead of on rsqatat_bit5 (i.e. 'never lock') rising.
      No big impact on the application, but may help reduce scan time for customers using 'lock_to_carrier' instead of 'Seek_Init/Seek_Next' for T/T2/ISDB-T installation.

 As from V0.1.5.0:
    <wrapper> Wrapper V2.6.0
    <firmware> With FW 5_Bb3 on X5A parts
    <improvement>[DVB-C2/Seek]
      In Si2183_L2_Channel_Seek_Next:
        DD_RESTART following DVBC2_CTRL/ACTION_START, to completely restart the lock for each new freq.
        Waiting 2 ms to have dvbc2_ctrl.tuned_rf_freq processed by the part before DD_RESTART.
    <improvement>[SILABS_SUPERSET/Standards]
      Replacing 'DEMOD_xyz' by either 'TERRESTRIAL_FRONT_END' or 'SATELLITE_FRONT_END' to better allow
        standard-by-standard compilation when using SILABS_SUPERSET.
      In Si2183_L2_switch_to_standard: Regrouping TER and SAT flags to limit the number of '#ifdef' lines.
        Some 'case' blocks can also be re-written for better readibility, considering that all 'modulation' values are defined even when
        not compiling with all standards, and this doesn't impact the code size a lot.

 As from V0.1.4.0:
    <correction>[Typo/DVB-C2]
    <wrapper> Wrapper V2.5.9
       In Si2183_L2_Channel_Seek_Next: Correcting calls to Si2183_L1_DVBC2_STATUS: using Si2183_DVBC2_STATUS_CMD_INTACK_CLEAR.
    <compatibility>[Tizen/int&char] explicitly declaring all 'int as 'signed int' and all 'char' as 'signed char'.
      This is because Tizen interprets 'int' as 'unsigned int' and 'char' as 'unsigned char'.
      All other OSs   interpret 'int' as 'signed   int' and 'char as 'signed char', so this change doesn't affect other compilers.
      To compare versions above V0.1.3.0 with older versions:
        Do not compare whitespace characters
        Either filter 'signed' or replace 'signed   int' with 'signed' and 'signed   char' with 'char' in the newer code first.
          (take care to use 3 spaces in the string to be replaced)
    <improvement>[DVB-C2/T_T2/TER_Tuner]
      In Si2183_L2_Tune: Selecting internal LIF in TER tuner when in 1.7 MHz or C2. Using ZIF for other cases (T or T2 above 1.7 MHz).
        With the previous code, LIF was selected if using AUTO_DETECT/AUTO_T_T2 after tuning in DVB-C2 (which is using LIF).

 As from V0.1.3.0:
    <wrapper> Wrapper V2.5.8
    <new_feature>[DVB-C2/Seek]
      In Si2183_L2_Channel_Seek_Init:
        Taking into account DVB-C2 case.
      In Si2183_L2_Channel_Seek_Next:
        Improved DVB-C2 scan, with auto BW detection (6 or 8 MHz).
        DVB-C2 Seek now using 'NOT_DVBC2' API flag.
    <new_feature>[DVB-S2/Multiple_Input_Stream]
      In Si2183_PowerUpWithPatch:
        Setting MIS_capability flag to 1 for parts supporting this feature.
      In Si2183_L2_lock_to_carrier:
        Using plp_id input parameter as isi_id when in DVB-S2. (if supporting MIS).
        Setting stream selection to 'auto' if isi_id(i.e. plp_id parameter) is '-1' (same behavior as for plp_id it T2 or C2).
      In Si2183_L2_Channel_Seek_Init:
        Forcing DVB-S2 stream selection to 'auto' (if supporting MIS).
    <new_feature>[Broadcast_i2c/demods]
      Adding Si2183_PowerUpUsingBroadcastI2C to load FW in several demodulators using the broadcast i2c mode. (only used for 'multiple' designs).
      In Si2183_PowerUpWithPatch: using api->load_control to run onliy selected parts of the function, depending on the progress
        of the Si2183_PowerUpUsingBroadcastI2C function.
      In Si2183_L2_SW_Init:
        setting TER_tuner_config_done to 0. This is a new flag used to separate TER tuner init and TER tuner configuration.
      The TER tuner init is identical, but the configuration differs depending on the front_end, so these need to be treated separately.
      In Si2183_L2_switch_to_standard:
        checking TER_tuner_config_done flag to do the TER tuner configuration only when needed (once and after broadcast i2c).
      SiLabs_TER_Tuner_DTV_OUT_TYPE and SiLabs_TER_Tuner_DTV_AGC_SOURCE moved out of the TER tuner init code (this can now be bypassed if using broadcast i2c).
    <improvement>[comments]
      In Si2183_L2_lock_to_carrier:
        Adapting comment to indicate the use of the plp_id for DVB-C2 PLP and DVB-S2 ISI id.
    <improvement>[DVB-C2/Lock]
      In Si2183_L2_lock_to_carrier:
        proper DVB-C2 lock sequence, with reduced traces.

 As from V0.1.2.0:
    <firmware> With FW 4_4b26 on X40 parts
    <wrapper> Wrapper V2.5.7
    <compatibility>[spectrum/plot] in Si2183_plot: function compatible with Si2164_A, Si2167_B, Si2183_A and Si2183_B
    <new_feature>[FEF/FEF_MODE_TUNER_AUTO_FREEZE] Adding code to allow using only 'TUNER_AUTO_FREEZE', when available in the TER tuner.
    <compatibility>[Si2167B/SAT blindscan] In Si2183_L2_Channel_Seek_Init and Si2183_L2_Channel_Seek_End: updates to load dedicated FW
      for SAT blindscan when using Si2167B
    <improvement>[traces] In Si2183_L2_Channel_Seek_Next: scan delays traced with consistent formatting, for easier reading.
    <improvement>[DVB-C/MCNS/BLINDSCAN] In Si2183_L2_Channel_Seek_Init: storing user-selected DVB-C/MCNS afc range and using 200 kHz for DVB-C blindlock/blindscan.
                                        In Si2183_L2_Channel_Seek_End:  reverting to user selected DVB-C/MCNS afc range when ending DVB-C blindlock/blindscan.

 As from V0.1.1.0:
    <firmware> With FW 5_Bb2  on X5A parts
    <firmware> With FW 5_5b5  on X55 parts
    <new_feature>[TER_TUNER/DTV_INTERNAL_ZIF] Adding calls to SiLabs_TER_Tuner_DTV_INTERNAL_ZIF_DVBT to select the best internal IF configuration for the TER tuners
    <new_Part>[chiprev/3] In Si2183_L2_Test: Adding compatibility with ROM2 parts.
    <new_feature>[SPI/split] Adding Si2183_LoadFirmwareSPI_Split to allow sending FW over SPI in smaller portions (min SPI buffer size is currently 1024 bytes)
    <compatibility>[AUTO_T_T2] In Si2183_TerAutoDetect: not setting front_end->auto_detect_TER for parts not supporting DVB-T2.
    <improvement>[traces] In Seek functions: adding dedicated traces to show the delays between DD_RESTART and the decision (lock/never lock) or the timeout as well as the
      cumulative durations corresponding to these.

 As from V0.1.0.0:
    <new_Part>[Si2183_B5A] In Si2183_PowerUpWithPatch: Adding compatibility with Si2183_B5A.
    <wrapper> Wrapper V2.5.6
    <firmware> With FW 6_0b1  on X60 parts
    <firmware> With FW 5_3b4  on Si2180 X50 parts
    <firmware> With FW 5_5b4  on X55 parts (except Si2180)
    <firmware> With FW 5_Bb1  on X5A parts
    <improvement>[traces] In Si2183_PowerUpWithPatch and Si2183_LoadFirmwareSPI: typo correction with proper function name
    <improvement>[SILENT/DUAL] Si2183_L2_SILENT updated to properly handle duals, taking into account pin usage restrictions:
        Die A can control MP_A, MP_C, GPIO1
        Die B can control MP_B, MP_D, GPIO0
    <improvement>[SLEEP/switch_to_standard] In Si2183_L2_switch_to_standard: setting DD_MODE only
        when dtv_demod_needed = 1, to avoid calling this when in SLEEP mode.
    <compatibility>[Si2165D] In Si2183_L2_Test, option 'demod/chip_detect': allowing detection of a
     non API-controlled part, by default considered being Si2165D.
    This assumes that the TER tuner address is 0xC0, to match SiLabs EVBs.
    <new_part> Adding support for Si2167B-22 (requires the compilation flag 'Si2167B_22_COMPATIBLE' )

 As from V0.0.8.0:
    <wrapper> Wrapper V2.5.5
    <firmware> With FW 5_0b15 on X50 parts (full download for ES parts, patch for production parts)
    <firmware> With FW 5_5b3  on X55 parts (except Si2180)
    <new_feature>[FW_from_table] In Si2183_L2_SW_Init/Si2183_PowerUpWithPatch: Adding the capability to load FW from a table, either over I2C or over SPI.
      NB: In Si2183_L2_SW_Init: The corresponding lines using ‘realloc’ need to be commented if dynamic memory allocation is not allowed.

 As from V0.0.7.0:
    <wrapper> Wrapper V2.5.4
    <new_feature>[FW_from_table] Adding the capability to load FW from a table, either over I2C or over SPI.
    <new_feature>[SPI/logs]
     In Si2183_LoadFirmware:    storing the FW download time in I2C mode
     In Si2183_LoadFirmware_16: storing the FW download time in I2C mode
     In Si2183_LoadFirmwareSPI: storing the FW download time in SPI mode
     In Si2183_L2_Test : Adding the "download" "duration" option to display the FW download times
    <improvement>[traces/SPI] In Si2183_PowerUpWithPatch: tracing api->spi_download
    <improvement>[Switch/DSS] In Si2183_L2_switch_to_standard: Setting auto mode to 'AUTO_DVB_S_S2_DSS' only if new_standard is DSS

 As from V0.0.6.0:
    <wrapper> Wrapper V2.5.3
    <new_Part>[Si2166_C55] In Si2183_PowerUpWithPatch: Adding compatibility with Si2167_C55 and Si2166_C55.
    <firmware> With FW 5_0b14 on X50 parts (full download for ES parts, patch for production parts)
    <firmware> With FW 5_5b2  on X55 parts (except Si2180)
    <firmware> With FW 5_3b2  on Si2180 X50 parts
    <improvement>[scan/not_blind] In Si2183_L2_Channel_Seek_Next: Checking front_end->seek_abort flag to allow an abort.
      The previous version only allowed seek aborting when in blind mode (for SAT and DVB-C).
      The previous version only allowed seek aborting when in blind mode (for SAT and DVB-C).
    <improvement>[suspend/resume] In Si2183_L2_send_diseqc_sequence: Storing DiSEqC parameters in L1 context to allow saving them during 'resume'.
    <improvement>[SPI/SPIoverGPIF] In Si2183_LoadFirmwareSPI: using new Cypress feature to load FW in SPI mode using GPIF (typical FW download time below 80 ms).
    <improvement>[DVB-C/timeout] In Si2183_L2_lock_to_carrier; resetting front_end->searchStartTime after tuning is complete (if tuning), to be tuner-independent
      in the lock timeout management.
    <improvement>[DVB-C/porting] In Si2183_DVB_C_max_lock_ms: removing float use.
    <improvement>[SEEK/NO_DVBT2] In Si2183_L2_Channel_Seek_Next:
      Not allowing AUTO_DETECT in DVB-T for parts not supporting DVB-T2.
      This is done using the front_end->auto_detect_TER flag, which should not be '1' for parts not supporting T2.
    <improvement>[SEEK/DSS] In Si2183_L2_Channel_Seek_Next and Si2183_L2_lock_to_carrier
      Added compatibility with DSS, with no impact on AUTO_DVB_S_S2 mode:
       AUTO_DVB_S_S2_DSS is only used if the standard is explicitly DSS.
       This is because otherwise the auto lock is a bit slower, while most platforms don't need to support DSS.

 As from V0.0.5.0:
    <wrapper> Wrapper V2.5.1
    <new_Part>[Si2183_A55] Adding FW download code for X55 parts
    <new_Part>[Si2183_B60] Adding FW download code for X60 parts (which will not be available before mid 2015)
    <firmware> With FW 5_0b12 on X50 parts (full download for ES parts, patch for production parts)
    <firmware> With FW 5_5b1  on X55 parts
    <improvement>[code_checker] adding lines to avoid code checker warnings:
      In Si2183_L2_Channel_Seek_Next: setting flags to 0 by default (overwritten later on in the function)
    <improvement>[Code_size] Using the textBuffer in Si2183_L1_Context when filling text strings
      In Si2183_L2_SW_Init (buffer init)
      In Si2183_L2_switch_to_standard and Si2183_L2_Test
    <improvement>[blindscan/debug] In Si2183_plot: (only when ALLOW_Si2183_BLINDSCAN_DEBUG is declared)
      Spectrum traces now working (register definitions where those of "pmajor = '4'" parts)
      Compatibility with Si2164 parts (with pmajor = '4').
      Removing unused variables.

 As from V0.0.4.0:
    <improvement>[TestPipe/chip_detect] Return 83A in default case for chips not burned
    <firmware> Adding firmware for Si2183 ROM1 / NO NVM (full download)
    <new_feature>[TestPipe/demod] In Si2183_L2_Test for demod adding command chip_detect to return parts and chiprev of the demod
    <firmware> New firmware: FW 5_3b1 (full download for Si2180 parts only, without T2/C2/S2)
    <firmware> New firmware: FW 5_0b10 (full download for ES parts, patch for production parts)
    <correction>[blindscan] In Si2183_L2_Channel_Seek_Next: in blind_mode, when a scan interrupt is triggered and Si2183_L1_SCAN_STATUS is 'BUZY' we wait until Si2183_L1_SCAN_STATUS is not 'BUZY'
    <new_feature>[TestPipe/demod] In Si2183_L2_Test for demod with command part_info adding subcommands part and chiprev
    <new_feature>[TestPipe/demod] In Si2183_L2_Test for demod adding command isdbt-t with subcommand layer_info
    <wrapper> Wrapper V2.5.0
    <firmware> With FW 5_6b1 (full download for Si2180 parts only, without T2/C2/S2)
    <firmware> With FW 5_0b8 (full download for ES parts, patch for production parts)
    <improvement>[code_checker] adding lines to avoid code checker warnings:
      In Si2183_L2_lock_to_carrier:     setting default values for min_lock_time_ms and min_lock_time_ms (overwritten later on in the function)
      In Si2183_L2_Channel_Seek_Init:   returning ERROR_Si2183_ERR in case dd_mode.modulation doesn't match any valid standard (this is not possible by design)
      In Si2183_L2_Channel_Seek_Init:   setting front_end->searchStartTime before leaving the function   (overwritten later on inside Si2183_L2_Channel_Seek_Next)
      In Si2183_L2_Set_Invert_Spectrum: setting inversion to 0 by default (overwritten later on in the function)
    <correction>[lock/MPLP] In Si2183_L2_lock_to_carrier: using plp_id = plp_id to avoid compiler warning when not used while keeping plp_id value.
      (regression introduced in V0.0.3.0 with 'plp_id = 0;')
    <improvement>[TestPipe/No SiTRACES] In Si2183_L2_Read_L1_Post_Data: Incrementing word_index outside the SiTRACE, to make sure it will increase even when SiTRACES are not used.

 As from V0.0.3.0:
    <wrapper> Wrapper V2.4.7
    <firmware> With FW 5_0b7 (full download for ES parts, patch for production parts)
    <correction/TESTPIPE> In Si2183_L2_Read_L1_Misc_Data: storing djb_alarm_comm in the proper field

 As from V0.0.2.0:
    <firmware> With FW 5_0b6 (full download for ES parts, patch for production parts)
    <wrapper> Wrapper V2.4.6
    <new_feature>[SiLOGS] In Si2183_PowerUpWithPatch: Adding new lines for logging the
      build options and some important lines. Requires updating Si_I2C to V3.4.8, otherwise defining SiLOGS as SiTRACE.
    <correction>[LOAD_FW] In Si2183_PowerUpWithPatch: Correcting part_info.pminor check
      (incorrectly compared to Si2183_PATCH16_5_0b4_PMAJOR)

 As from V0.0.1.0:
    <wrapper> Wrapper V2.4.5
    <TER_Tuner_Wrapper> TER Tuner API V0.4.0
    <firmware> With FW 5_0b4 (full download for ES parts, patch for production parts)
    <new_feature>[TER_Tuner/Config] In Si2183_L2_switch_to_standard:
     Calling SiLabs_TER_Tuner_DTV_OUT_TYPE and SiLabs_TER_Tuner_DTV_AGC_SOURCE instead of TER_TUNER_AGC_EXTERNAL
     NB: To take benefit of this modification, update your TER Tuner wrapper to V0.4.1 or above, to get access to
      the SiLabs_TER_Tuner_DTV_OUT_TYPE and SiLabs_TER_Tuner_DTV_AGC_SOURCE functions.
     NB: No change required for existing applications, since this is mostly useful to use LIF_IF1 with SiLabs TER tuners,
      when compared with the previous versions which by default use LIF_IF2.
    <improvement>[SAT blindscan] In Si2183_plot: Adding additional spectrum debug information. SAT blindscan now ready to be
        provided to FW team for debug in their simulation environment.

 As from V0.0.0.4:
    <wrapper> Wrapper V2.4.2
    <firmware> With FW 4_Ab4
     Now prepared to use the 16 bytes download FWs (requires Si2183_A50_COMPATIBLE)
    <TER_Tuner_API>[V0.3.9] Using TER-Tuner API V0.3.9, to benefit from the 1.7 MHz filtering feature (not available with all TER tuners).
    <improvement>[TER_BW/1.7MHz] In Si2183_L2_Tune: now using SILABS_BW enum as defined in SiLABS_TER_TUNER API V0.3.9, to
      use the 1.7 MHz filtering feature in SiLabs TER tuners whenever possible.

 As from V0.0.0.3:
    <wrapper> Wrapper V2.4.1
    <improvement> [Src_code_GUIs] In Si2183_L2_Test: more complete testpipe 'demod help'
    <correction>[Tuner_i2c] In Si2183_L2_Tune: Moving 'UNICABLE_COMPATIBLE' line around the closing
      bracket after disabling the SAT tuner i2c.
      The previous version didn't disable the tuner i2c with the following compilation flags:
      UNICABLE_COMPATIBLE      NOT defined
      INDIRECT_I2C_CONNECTION  defined
    <correction> [SILENT/SLEEP/ANALOG] In Si2183_L2_switch_to_standard: Adding dtv_demod_sleeping flag to
        more easily handle the 'sleep' mode, which can occur upon a clock source change in DTV, or when
        going to 'ANALOG' or 'ATV'. The WAKEUP sequence is required in the first case, not in the second case.
    <improvement> [Unicable/Multi-Treading/Multiple frontends] In Si2183_L2_TER_FEF_SETUP: removing I2C pass-through enable/disable.
    This is only called from switch_to_standard, and the i2c pass-through is already enabled when calling this function.
    The change removes nested i2c pass-through enable/disable calls.
    These had generally no consequences, except for duals when several tuners use the same i2c address.
    <improvement> [BLINDSCAN/DEBUG/SPECTRUM] In Si2183_L2_Channel_Seek_Init:
        front_end->demod->prop->scan_sat_config.scan_debug = 0x03; (the previous value of 0x07 doesn't work anymore)

 As from V0.0.0.1:
 <correction>[Tuner_i2c] In Si2183_L2_Tune: Moving 'ifdef    UNICABLE_COMPATIBLE' line around the closing
  bracket after disabling the SAT tuner i2c.
  The previous version didn't disable the tuner i2c with the following compilation flags:
   UNICABLE_COMPATIBLE NOT defined
  INDIRECT_I2C_CONNECTION  defined

 As from V0.0.0.0:
  Initial version (based on Si2164 code V0.3.4)
****************************************************************************************/

/* Si2183 API Specific Includes */
/* Before including the headers, define SiLevel and SiTAG */
#define   SiLEVEL          2

#include "Si2183_L2_API.h"               /* Include file for this code */

#ifdef    DEMOD_DVB_T2
 #ifdef    SiTRACES
  /* Compile with 'CHECK_DVB_T2_SIGNALLING' to check the DVB-T2 signalling on the first DVB-T2 lock.
      This can be convenient to understand field issues when modulators are set in unexpected ways */
  #ifdef    CHECK_DVB_T2_SIGNALLING
    #include "SiLabs_DVB_T2_Signalling.h"
    int   Si2183_L2_Read_L1_Pre_Data         (Si2183_L2_Context *front_end, SiLabs_T2_L1_Pre_Signalling  *pre );
    int   Si2183_L2_Read_L1_Post_Data        (Si2183_L2_Context *front_end, SiLabs_T2_L1_Post_Signalling *post);
    int   Si2183_L2_Read_L1_Misc_Data        (Si2183_L2_Context *front_end, SiLabs_T2_Misc_Signalling    *misc);
  #endif /* _CHECK_DVB_T2_SIGNALLING_H_ */
 #endif /* SiTRACES */
#endif /* DEMOD_DVB_T2 */

/* Re-definition of SiTRACE for L1_Si2183_Context */
#ifdef    SiTRACES
  #undef  SiTRACE
  #define SiTRACE(...)        SiTraceFunction(SiLEVEL, api->i2c->tag, __FILE__, __LINE__, __func__     ,__VA_ARGS__)
#endif /* SiTRACES */

#ifdef    DEMOD_ISDB_T
#ifdef    Si2180_A55_COMPATIBLE
 /* This is only used for Si2180 parts, since the FW contains no T2/C2/S2 */
 #include "Si2180_ROM1_Patch16_5_8b3.h"     /* firmware compatible with Si2180     (ROM0/NVM 5_1b3), without T2/C2/S2 FW  */
 #define   Si2180_FIRMWARE_FOR_x55_PARTS          Si2180_PATCH16_5_8b3
/* #include "Si2180_ROM1_SPI_5_8b2.h"     */    /* SPI mode compatible with Si2180     (ROM0/NVM 5_1b3), without T2/C2/S2 FW  */
#endif /* Si2180_A55_COMPATIBLE */
#ifdef    Si2180_A50_COMPATIBLE
 /* This is only used for Si2180 parts, since the FW contains no T2/C2/S2 */
 #include "Si2180_ROM0_Patch16_5_3b5.h"     /* firmware compatible with Si2180     (ROM0/NVM 5_0b3), without T2/C2/S2 FW  */
 #define   Si2180_FIRMWARE_FOR_x50_PARTS          Si2180_PATCH16_5_3b5
 /* #include "Si2180_ROM0_SPI_5_3b4.h"    */     /* SPI mode compatible with Si2180     (ROM0/NVM 5_0b3), without T2/C2/S2 FW  */
#endif /* Si2180_A50_COMPATIBLE */
#endif /* DEMOD_ISDB_T */
#ifdef    Si2183_B63_COMPATIBLE
#ifdef    CHANNEL_BONDING
 #include "Si2183_ROM2_Patch16_6_4b7.h"     /* firmware compatible with Si2183     (ROM2/NVM 6_3b1) including channel bonding             */
 #define   Si2183_FIRMWARE_FOR_x63_PARTS           Si2183_PATCH16_6_4b7
#endif /* CHANNEL_BONDING */
#ifndef   CHANNEL_BONDING
 #include "Si2183_ROM2_Patch16_6_3b6.h"     /* firmware compatible with Si2183     (ROM2/NVM 6_3b1) without   channel bonding             */
 #define   Si2183_FIRMWARE_FOR_x63_PARTS           Si2183_PATCH16_6_3b6
#endif /* CHANNEL_BONDING */
#endif /* Si2183_B63_COMPATIBLE */
#ifdef    Si2183_B60_COMPATIBLE
#ifdef    CHANNEL_BONDING
 #include "Si2183_ROM2_Patch16_6_2b2.h"     /* firmware compatible with Si2183     (ROM2/NVM 6_0b1) including channel bonding             */
 #define   Si2183_FIRMWARE_FOR_x60_PARTS           Si2183_PATCH16_6_2b2
#endif /* CHANNEL_BONDING */
#ifndef   CHANNEL_BONDING
 #include "Si2183_ROM2_Patch16_6_0b13.h"     /* firmware compatible with Si2183     (ROM2/NVM 6_0b1) without   channel bonding            */
 #define   Si2183_FIRMWARE_FOR_x60_PARTS           Si2183_PATCH16_6_0b13
#endif /* CHANNEL_BONDING */
/* SPI FW download */
 #ifdef    FW_DOWNLOAD_OVER_SPI
  #include "Si2183_ROM2_SPI_6_0b2.h"
  #define   Si2183_SPI_FIRMWARE_FOR_x60_PARTS      Si2183_SPI_6_0b2
  #define   Si2183_SPI_SPLIT_LIST_FOR_x60_PARTS    Si2183_SPI_6_0b2_SPLIT_LIST
 #endif /* FW_DOWNLOAD_OVER_SPI */
#endif /* Si2183_B60_COMPATIBLE */
#ifdef    Si2183_B5B_COMPATIBLE
 #include "Si2183_ROM2_Firmware_5_Bb5.h"     /* firmware compatible with Si2183     (ROM2/NVM 5_Bb0)                                       */
 #define   Si2183_FIRMWARE_FOR_x5B_PARTS          Si2183_FIRMWARE_5_Bb5
#endif /* Si2183_B5B_COMPATIBLE */
#ifdef    Si2183_A55_COMPATIBLE
 /* When using Si2180 parts, including 'full' FW for all standards is not needed. The 5_6bx FW is smaller (since it contains no T2/C2/S2) */
 #include "Si2183_ROM1_Patch16_5_5b16.h"     /* firmware compatible with Si2183     (ROM1/NVM 5_5b1)                                       */
 #define   Si2183_FIRMWARE_FOR_x55_PARTS          Si2183_PATCH16_5_5b16
/* #include "Si2183_ROM1_SPI_5_5b7.h"       */  /* SPI mode compatible with Si2183     (ROM1/NVM 5_5b1)                                       */
#endif /* Si2183_A55_COMPATIBLE */
#ifdef    Si2183_A50_COMPATIBLE
 /* When using Si2180 parts, including 'full' FW for all standards is not needed. The 5_6bx FW is smaller (since it contains no T2/C2/S2) */
 #include "Si2183_ROM0_Patch16_5_0b19.h"     /* firmware compatible with Si2183     (ROM0/NVM 5_0b3)                                      */
 #define   Si2183_FIRMWARE_FOR_x50_PARTS          Si2183_PATCH16_5_0b19
 #ifdef    FW_DOWNLOAD_OVER_SPI
  #include "Si2183_ROM0_SPI_5_0b15_split_4.h" /* SPI mode compatible with Si2183     (ROM0/NVM 5_0b3)                                      */
 #endif /* FW_DOWNLOAD_OVER_SPI */
#endif /* Si2183_A50_COMPATIBLE */
#ifdef    Si2183_ES_COMPATIBLE
 #include "Si2183_ROM0_Firmware16_5_0b15.h"  /* firmware compatible with Si2183     (ROM0/no NVM)    */
 #define   Si2183_FIRMWARE_FOR_ES_PARTS           Si2183_FIRMWARE16_5_0b15
/* #include "Si2183_ROM1_Firmware16_0_Bb1.h" */    /* non official firmware compatible with Si2183     (ROM1/no NVM)    */
#endif /* Si2183_ES_COMPATIBLE */

/* Allowing compatibility with previous parts (also reflected in Si2183_PowerUpWithPatch) */
#ifdef    Si2164_A40_COMPATIBLE
 #ifdef    DEMOD_DVB_C2
  /* FW with    DVB-C2 (4_4b1 is the minimal patch for Si2164-A40/Si2162-A40/Si2160-A40 NIM production testing) */
//  #include "Si2164_ROM1_Patch16_4_4b26.h"
//  #define   Si2164_DVB_C2_FIRMWARE_FOR_x40_PARTS  Si2164_PATCH16_4_4b26
 #endif /* DEMOD_DVB_C2 */
 /* FW without DVB-C2 (4_0b3 is the minimal patch for Si2169B-A40/Si2169B-40 NIM production testing) */
 /* 16 bytes mode patch compatible with Si2164-A40, Si2169-B40 and Si268-B40 (smaller patch with no DVB-C2) */
   #include "Si2164_ROM1_Patch16_4_0b31.h"
   #define   Si2164_FIRMWARE_FOR_x40_PARTS          Si2164_PATCH16_4_0b31
#endif /* Si2164_A40_COMPATIBLE */
#ifdef    Si2167_B25_COMPATIBLE
 #include "Si2167_ROM0_Patch16_2_5b0.h"     /* firmware compatible with Si2167-B25 (ROM0/NVM 2_5b0) */
 #define   Si2167_FIRMWARE_FOR_x25_PARTS          Si2180_PATCH16_2_5b0
#endif /* Si2167_B25_COMPATIBLE */
#ifdef    Si2169_30_COMPATIBLE
// #include "Si2169_30_ROM3_Patch_3_0b22.h"
// #define   Si2169_FIRMWARE_FOR_x30_PARTS          Si2169_PATCH_3_0b22
#endif /* Si2169_30_COMPATIBLE */
#ifdef    Si2167B_20_COMPATIBLE
 #ifdef    DEMOD_DVB_C
//  #include "Si2167B_ROM0_Patch_2_9b1.h"
//  #define   Si2167B_DVB_C_FIRMWARE_FOR_x20_PARTS  Si2167B_PATCH_2_9b1
 #endif /* DEMOD_DVB_C */
// #include "Si2167B_ROM0_Patch_2_0b29.h"
// #define   Si2167B_FIRMWARE_FOR_x20_PARTS         Si2167B_PATCH_2_0b29
#endif /* Si2167B_20_COMPATIBLE */
#ifdef    Si2167B_22_COMPATIBLE
 #ifdef    DEMOD_DVB_C
//  #include "Si2167B_ROM0_Patch_2_8b1.h"
//  #define   Si2167B_DVB_C_FIRMWARE_FOR_x22_PARTS  Si2167B_PATCH_2_8b1
 #endif /* DEMOD_DVB_C */
 #include "Si2167B_ROM0_Patch_2_2b10.h"
 #define   Si2167B_FIRMWARE_FOR_x22_PARTS         Si2167B_PATCH_2_2b10
#endif /* Si2167B_22_COMPATIBLE */
/* End of   compatibility with previous parts */

#define Si2183_BYTES_PER_LINE 8

/*#define   Si2183_FFT_CAPABILITY*/
#ifdef    Si2183_FFT_CAPABILITY
  #include "Doc/Si_2183_fft.c"
  #define MIN_SPECTRUM_FREQ  470000000
  #define MAX_SPECTRUM_FREQ  480000000
#endif /* Si2183_FFT_CAPABILITY */

#define   ALLOW_Si2183_BLINDSCAN_DEBUG
#ifdef    ALLOW_Si2183_BLINDSCAN_DEBUG
 #ifdef    SiTRACES
  #define Si2183_FORCED_TRACE(...)             SiTraceConfiguration("traces resume"); SiTraceFunction(2,"plot ",__FILE__, __LINE__, __func__,__VA_ARGS__); SiTraceConfiguration("traces suspend");
 #else  /* SiTRACES */
  #define Si2183_FORCED_TRACE                  printf
 #endif /* SiTRACES */
int  inter_carrier_space;
/************************************************************************************************************************
  Si2183_plot function
  Use:        Si2183 plot function for DVB-C and SAT blindscan
              Used to  print trace messages in the console to allow drawing the scan spectrum
  Porting:    Useful to validate the blindscan sw porting. Can be removed once working
  Parameter:  source,  a string to display, also used to select the Si2183_plot mode
************************************************************************************************************************/
void Si2183_plot                             (Si2183_L2_Context   *front_end, const char* source, char signed_val, long currentRF) {
  #ifdef     PLOT_WITH_BACKOFF_INFO
  int nb_channel;
  #endif /* PLOT_WITH_BACKOFF_INFO */
  int nb_word;
  int count;
  int w;
  int blanks;
  int read_data;
  int msb, lsb;
  signed   int trylock_center;
  int trylock_symbol_rate;
  int tune_freq;
  int spectrum_start_freq;
  int spectrum_stop_freq;
  int analysis_bw;
  int analyzis_start_freq;
  int analyzis_stop_freq;
  int standard_specific_spectrum_offset;
  int standard_specific_spectrum_scaling;
  int standard_specific_freq_unit;
  int nb_skip_first_words;
  L1_Si2183_Context *api;

#ifdef   Si2183_READ
  int gp_reg16_0;
  int gp_reg16_1;
  int gp_reg16_2;
  int gp_reg16_3;
  int gp_reg32_0;
  int gp_reg32_1;
  int gp_reg32_2;
  int dcom_read;
  int if_freq_shift;
  int channel_nb0;
  int channel_nb1;
  int channel_nb2;
  int rf_backoff0;
  int rf_backoff1;
  int rf_backoff2;
#define   Si2164_REGISTERS
#ifdef    Si2164_REGISTERS
#define Si2164_en_rst_error_LSB    0
#define Si2164_en_rst_error_MID  244
#define Si2164_en_rst_error_MSB    9

#define Si2164_dcom_control_byte_LSB   31
#define Si2164_dcom_control_byte_MID  252
#define Si2164_dcom_control_byte_MSB    9

#define Si2164_dcom_addr_LSB   31
#define Si2164_dcom_addr_MID    0
#define Si2164_dcom_addr_MSB   10

#define Si2164_dcom_data_LSB   31
#define Si2164_dcom_data_MID    4
#define Si2164_dcom_data_MSB   10

#define Si2164_dcom_read_LSB   31
#define Si2164_dcom_read_MID   44
#define Si2164_dcom_read_MSB   10

#define Si2164_dcom_read_toggle_LSB    0
#define Si2164_dcom_read_toggle_MID   43
#define Si2164_dcom_read_toggle_MSB   10

#define Si2164_gp_reg16_0_LSB   15
#define Si2164_gp_reg16_0_MID   60
#define Si2164_gp_reg16_0_MSB   10

#define Si2164_gp_reg16_1_LSB   15
#define Si2164_gp_reg16_1_MID   62
#define Si2164_gp_reg16_1_MSB   10

#define Si2164_gp_reg16_2_LSB   15
#define Si2164_gp_reg16_2_MID   64
#define Si2164_gp_reg16_2_MSB   10

#define Si2164_gp_reg16_3_LSB   15
#define Si2164_gp_reg16_3_MID   66
#define Si2164_gp_reg16_3_MSB   10

#define Si2164_gp_reg32_0_LSB   31
#define Si2164_gp_reg32_0_MID   48
#define Si2164_gp_reg32_0_MSB   10

#define Si2164_gp_reg32_1_LSB   31
#define Si2164_gp_reg32_1_MID   52
#define Si2164_gp_reg32_1_MSB   10

#define Si2164_gp_reg32_2_LSB   31
#define Si2164_gp_reg32_2_MID   56
#define Si2164_gp_reg32_2_MSB   10

#define Si2164_gp_reg8_3_LSB    7
#define Si2164_gp_reg8_3_MID   71
#define Si2164_gp_reg8_3_MSB   10

#define Si2164_if_freq_shift_LSB   28
#define Si2164_if_freq_shift_MID   92
#define Si2164_if_freq_shift_MSB    4
#endif /* Si2164_REGISTERS */

#define   Si2167B_REGISTERS
#ifdef    Si2167B_REGISTERS
  #define Si2167B_en_rst_error_LSB   0
  #define Si2167B_en_rst_error_MID   220
  #define Si2167B_en_rst_error_MSB   9

  #define Si2167B_dcom_control_byte_LSB   31
  #define Si2167B_dcom_control_byte_MID   228
  #define Si2167B_dcom_control_byte_MSB   9

  #define Si2167B_dcom_addr_LSB   31
  #define Si2167B_dcom_addr_MID   232
  #define Si2167B_dcom_addr_MSB   9

  #define Si2167B_dcom_data_LSB   31
  #define Si2167B_dcom_data_MID   236
  #define Si2167B_dcom_data_MSB   9

  #define Si2167B_dcom_read_LSB   31
  #define Si2167B_dcom_read_MID   20
  #define Si2167B_dcom_read_MSB   10

  #define Si2167B_gp_reg8_3_LSB   7
  #define Si2167B_gp_reg8_3_MID   47
  #define Si2167B_gp_reg8_3_MSB   10

  #define Si2167B_gp_reg16_0_LSB   15
  #define Si2167B_gp_reg16_0_MID   36
  #define Si2167B_gp_reg16_0_MSB   10

  #define Si2167B_gp_reg16_1_LSB   15
  #define Si2167B_gp_reg16_1_MID   38
  #define Si2167B_gp_reg16_1_MSB   10

  #define Si2167B_gp_reg16_2_LSB   15
  #define Si2167B_gp_reg16_2_MID   40
  #define Si2167B_gp_reg16_2_MSB   10

  #define Si2167B_dcom_read_toggle_LSB   0
  #define Si2167B_dcom_read_toggle_MID   19
  #define Si2167B_dcom_read_toggle_MSB   10

  #define Si2167B_gp_reg16_3_LSB   15
  #define Si2167B_gp_reg16_3_MID   42
  #define Si2167B_gp_reg16_3_MSB   10

  #define Si2167B_gp_reg32_0_LSB   31
  #define Si2167B_gp_reg32_0_MID   24
  #define Si2167B_gp_reg32_0_MSB   10

  #define Si2167B_gp_reg32_1_LSB   31
  #define Si2167B_gp_reg32_1_MID   28
  #define Si2167B_gp_reg32_1_MSB   10

  #define Si2167B_gp_reg32_2_LSB   31
  #define Si2167B_gp_reg32_2_MID   32
  #define Si2167B_gp_reg32_2_MSB   10

  #define Si2167B_if_freq_shift_LSB   28
  #define Si2167B_if_freq_shift_MID   92
  #define Si2167B_if_freq_shift_MSB   4

  #define Si2167B_freq_corr_sat_LSB   27
  #define Si2167B_freq_corr_sat_MID   144
  #define Si2167B_freq_corr_sat_MSB   5
#endif /* Si2167B_REGISTERS */

#define   Si2183_REGISTERS
#ifdef    Si2183_REGISTERS
#define Si2183_en_rst_error_LSB   0
#define Si2183_en_rst_error_MID   8
#define Si2183_en_rst_error_MSB   11

#define Si2183_dcom_control_byte_LSB   31
#define Si2183_dcom_control_byte_MID   16
#define Si2183_dcom_control_byte_MSB   11

#define Si2183_dcom_addr_LSB   31
#define Si2183_dcom_addr_MID   20
#define Si2183_dcom_addr_MSB   11

#define Si2183_dcom_data_LSB   31
#define Si2183_dcom_data_MID   24
#define Si2183_dcom_data_MSB   11

#define Si2183_dcom_read_LSB   31
#define Si2183_dcom_read_MID   64
#define Si2183_dcom_read_MSB   11

#define Si2183_dcom_read_toggle_LSB   0
#define Si2183_dcom_read_toggle_MID   63
#define Si2183_dcom_read_toggle_MSB   11

#define Si2183_gp_reg16_0_LSB   15
#define Si2183_gp_reg16_0_MID   80
#define Si2183_gp_reg16_0_MSB   11

#define Si2183_gp_reg16_1_LSB   15
#define Si2183_gp_reg16_1_MID   82
#define Si2183_gp_reg16_1_MSB   11

#define Si2183_gp_reg16_2_LSB   15
#define Si2183_gp_reg16_2_MID   84
#define Si2183_gp_reg16_2_MSB   11

#define Si2183_gp_reg16_3_LSB   15
#define Si2183_gp_reg16_3_MID   86
#define Si2183_gp_reg16_3_MSB   11

#define Si2183_gp_reg32_0_LSB   31
#define Si2183_gp_reg32_0_MID   68
#define Si2183_gp_reg32_0_MSB   11

#define Si2183_gp_reg32_1_LSB   31
#define Si2183_gp_reg32_1_MID   72
#define Si2183_gp_reg32_1_MSB   11

#define Si2183_gp_reg32_2_LSB   31
#define Si2183_gp_reg32_2_MID   76
#define Si2183_gp_reg32_2_MSB   11

#define Si2183_if_freq_shift_LSB   28
#define Si2183_if_freq_shift_MID   92
#define Si2183_if_freq_shift_MSB    4

#define Si2183_gp_reg8_3_LSB   7
#define Si2183_gp_reg8_3_MID   91
#define Si2183_gp_reg8_3_MSB   11

#endif /* Si2183_REGISTERS */
#endif /* Si2183_READ */
  api = front_end->demod;
  tune_freq          = 0;
  spectrum_start_freq= 0;
  spectrum_stop_freq = 0;
  analysis_bw        = 0;
  analyzis_start_freq= 0;
  analyzis_stop_freq = 0;
#ifdef    TERRESTRIAL_FRONT_END
  if (front_end->demod->media == Si2183_TERRESTRIAL) {
    inter_carrier_space = 1000000*64/(7*1024);
    standard_specific_spectrum_offset  =   0;
    standard_specific_spectrum_scaling = 400;
    standard_specific_freq_unit = 1;
    SiTRACE("DVB-C spectrum ");
  }
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
  if (front_end->demod->media == Si2183_SATELLITE) {
    inter_carrier_space = 106600000/2048;
    standard_specific_spectrum_offset  = 650;
    standard_specific_spectrum_scaling =  75;
    standard_specific_freq_unit = 1024;
    SiTRACE("SAT spectrum ");
  }
#endif /* SATELLITE_FRONT_END */
  SiTRACE("inter_carrier_space %d\n", inter_carrier_space);
  SiTRACE("part_info.pmajor '%c'\n", front_end->demod->rsp->part_info.pmajor);
  count = 0;
  SiTraceConfiguration("traces suspend");
  /* Stop Si2183 DSP */
  Si2183_WRITE(front_end->demod, en_rst_error,      0);
  Si2183_WRITE(front_end->demod, dcom_control_byte, 0xc0000000);
  Si2183_WRITE(front_end->demod, dcom_addr,         0x90000000);
  Si2183_WRITE(front_end->demod, dcom_data,         0x000004f0);

  Si2183_READ  (front_end->demod, gp_reg16_0);
  nb_word = gp_reg16_0;

  Si2183_READ  (front_end->demod, gp_reg32_0);
  Si2183_READ  (front_end->demod, gp_reg32_1);
  channel_nb0 =  gp_reg32_1 & 0x000000FF;
  channel_nb1 = (gp_reg32_1 & 0x0000FF00) >> 8;
  channel_nb2 = (gp_reg32_1 & 0x00FF0000) >> 16;
  Si2183_READ  (front_end->demod, gp_reg32_2);
  Si2183_READ  (front_end->demod, gp_reg16_1);
  rf_backoff0 = gp_reg16_1;
  Si2183_READ  (front_end->demod, gp_reg16_2);
  rf_backoff1 = gp_reg16_2;
  Si2183_READ  (front_end->demod, gp_reg16_3);
  rf_backoff2 = gp_reg16_3;
  Si2183_READ  (front_end->demod, if_freq_shift);
#ifdef    TERRESTRIAL_FRONT_END
  if (front_end->demod->media == Si2183_TERRESTRIAL) {
    analysis_bw = 2*nb_word*inter_carrier_space;
    nb_skip_first_words=0;
    tune_freq           = gp_reg32_2*standard_specific_freq_unit;
    analyzis_stop_freq  = tune_freq + analysis_bw/2;
    analyzis_start_freq = tune_freq - analysis_bw/2;
    spectrum_stop_freq  = analyzis_stop_freq;
    spectrum_start_freq = spectrum_stop_freq - inter_carrier_space*2*nb_word;
  }
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
  if (front_end->demod->media == Si2183_SATELLITE) {
    if (front_end->demod->prop->scan_sat_unicable_bw.scan_sat_unicable_bw == 0) {
      analysis_bw = 2*nb_word*inter_carrier_space;
      nb_skip_first_words=0;
      tune_freq           = gp_reg32_2*standard_specific_freq_unit;
      analyzis_stop_freq  = tune_freq + analysis_bw/2;
      analyzis_start_freq = tune_freq - analysis_bw/2;
      spectrum_stop_freq  = analyzis_stop_freq;
      spectrum_start_freq = spectrum_stop_freq - inter_carrier_space*2*nb_word;
    } else {
      analysis_bw = front_end->demod->prop->scan_sat_unicable_bw.scan_sat_unicable_bw*100000;
      nb_skip_first_words=0;
      tune_freq           = gp_reg32_2*standard_specific_freq_unit;
      analyzis_stop_freq  = tune_freq + analysis_bw/2;
      analyzis_start_freq = tune_freq - analysis_bw/2;
      spectrum_stop_freq  = analyzis_stop_freq;
      spectrum_start_freq = spectrum_stop_freq - inter_carrier_space*2*nb_word;
    }
  }
#endif /* SATELLITE_FRONT_END */

  Si2183_FORCED_TRACE(" DEBUG ; channel_nb0 %d, channel_nb1 %d, channel_nb2 %d \n",channel_nb0, channel_nb1, channel_nb2);
  Si2183_FORCED_TRACE(" DEBUG ; rf_backoff0 %d, rf_backoff1 %d, rf_backoff2 %d \n",rf_backoff0, rf_backoff1, rf_backoff2);
  Si2183_FORCED_TRACE("tune_freq %8d, spectrum_start_freq %8d, spectrum_stop_freq %8d, analyzis_start_freq %8d, analyzis_stop_freq %8d, analysis_bw %8d, inter_carrier_space %8d\n", tune_freq, spectrum_start_freq, spectrum_stop_freq, analyzis_start_freq, analyzis_stop_freq, analysis_bw, inter_carrier_space);

  currentRF = spectrum_start_freq;

  if (strcmp(source,"spectrum")==0) {
  #ifdef    PLOT_ON_LIMITED_RANGE
    if (spectrum_stop_freq >= LIMITED_RANGE_MIN_RF) {
      if (spectrum_start_freq <= LIMITED_RANGE_MAX_RF) {
  #endif /* PLOT_ON_LIMITED_RANGE */
        Si2183_FORCED_TRACE("spectrum center %10d (from %ld to %d) nb_word %d nb_skip_first_words %d    {\n", gp_reg32_2/1000, (currentRF)/1000, (gp_reg32_2 + (inter_carrier_space*nb_word/1))/1000, nb_word,nb_skip_first_words );
        Si2183_FORCED_TRACE("if_freq_shift %10d \n", if_freq_shift );
  #ifdef    PLOT_ON_LIMITED_RANGE
      } else {
        Si2183_FORCED_TRACE("not traced because above LIMITED_RANGE_MAX_RF...\n");
  }
    } else {
        Si2183_FORCED_TRACE("not traced because below LIMITED_RANGE_MIN_RF...\n");
    }
  #endif /* PLOT_ON_LIMITED_RANGE */
  }
  if (strcmp(source,"trylock" )==0) {
    if (gp_reg16_1 >> 15) {  gp_reg16_1 = gp_reg16_1 - 0xFFFF -1; }
    if (front_end->demod->media == Si2183_TERRESTRIAL) {
    trylock_center             = gp_reg32_2;
    trylock_symbol_rate        = gp_reg16_0*4096;
    } else {
    trylock_center             = gp_reg32_2*1024/1000;
    trylock_symbol_rate        = gp_reg32_0*1024;
    }
  #ifdef    PLOT_ON_LIMITED_RANGE
          if (trylock_center >= LIMITED_RANGE_MIN_RF) {
            if (trylock_center <= LIMITED_RANGE_MAX_RF) {
  #endif /* PLOT_ON_LIMITED_RANGE */
              Si2183_FORCED_TRACE("blindscan_interaction trylock    center %d / SR %d\n"
           ,  trylock_center
           ,  trylock_symbol_rate
           );
        Si2183_FORCED_TRACE("if_freq_shift %10d \n", if_freq_shift );
        Si2183_FORCED_TRACE("freq_corr_t   %10d \n", if_freq_shift );
    Si2183_FORCED_TRACE("\n");
  #ifdef    PLOT_ON_LIMITED_RANGE
            }
          }
  #endif /* PLOT_ON_LIMITED_RANGE */
  }


  w = 0;
  SiTraceConfiguration("traces suspend");
  if (strcmp(source,"spectrum")==0) {
  /* read spectrum data */
  Si2183_WRITE (front_end->demod, dcom_control_byte, (0x80000000 | (nb_word - 1)) );
  Si2183_WRITE (front_end->demod, dcom_addr        ,  gp_reg32_0);
  while ( w < nb_word ) {
      SiTraceConfiguration("traces suspend");
      Si2183_READ (front_end->demod , dcom_read);
      Si2183_WRITE(front_end->demod , dcom_read_toggle, 1);
      read_data = dcom_read;
      msb = (read_data >> 16) & 0xffff;
      lsb = (read_data >>  0) & 0xffff;
      if (signed_val) {
        if (msb >> 15) { msb = msb - (1<<16); }
        if (lsb >> 15) { lsb = lsb - (1<<16); }
      }
        if ((w < nb_word-0) && (w > nb_skip_first_words)) {
          /* Console spectrum mode */
  #ifdef    PLOT_ON_LIMITED_RANGE
          if (currentRF >= LIMITED_RANGE_MIN_RF) {
            if (currentRF <= LIMITED_RANGE_MAX_RF) {
  #endif /* PLOT_ON_LIMITED_RANGE */
            if ((count%1) ==0 ) {
              blanks = (int)((msb/standard_specific_spectrum_scaling) -standard_specific_spectrum_offset);
              Si2183_FORCED_TRACE("%10ld %8d (%3d) [%4d] |%*s\n", currentRF/1000, (int)(msb), w, blanks, blanks,"*");
              /* DEBUG */
              blanks = (int)((lsb/standard_specific_spectrum_scaling) -standard_specific_spectrum_offset);
              Si2183_FORCED_TRACE("%10ld %8d (%3d) [%4d] |%*s\n", (currentRF + inter_carrier_space)/1000, (int)(lsb), w, blanks, blanks,"*");
/*              if ((currentRF > tune_freq           - 1000000) && (currentRF < tune_freq           + 1000000) ) {Si2183_FORCED_TRACE(" ====== T %4d, correction %6d \n", front_end->unicable->T, front_end->unicable->correction); }*/
/*              if ((currentRF > analyzis_start_freq - 1000000) && (currentRF < analyzis_start_freq + 1000000) ) {Si2183_FORCED_TRACE(" >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");}*/
/*              if ((currentRF > analyzis_stop_freq  - 1000000) && (currentRF < analyzis_stop_freq  + 1000000) ) {Si2183_FORCED_TRACE(" <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");}*/
/*              if ((currentRF > 1610000000          - 1000000) && (currentRF < 1610000000          + 1000000) ) {Si2183_FORCED_TRACE(" --------- 1610 peak ------------ %d %d\n", currentRF + front_end->unicable->correction*1000, currentRF - front_end->unicable->correction*1000 );}*/
            }
  #ifdef    PLOT_ON_LIMITED_RANGE
            }
          }
  #endif /* PLOT_ON_LIMITED_RANGE */
/*          if (0 ==0 ) {printf("%10ld %8d |%*s\n", currentRF, (int)(msb), (int)((msb-50000)/100),"*"); }*/
          currentRF = currentRF + inter_carrier_space;
          currentRF = currentRF + inter_carrier_space;
          count++;
        }
        w++;
        }
      }
  if (strcmp(source,"spectrum")==0) {
  #ifdef    PLOT_ON_LIMITED_RANGE
    if (spectrum_stop_freq >= LIMITED_RANGE_MIN_RF) {
      if (spectrum_start_freq <= LIMITED_RANGE_MAX_RF) {
  #endif /* PLOT_ON_LIMITED_RANGE */
    Si2183_FORCED_TRACE("}\n");
  #ifdef    PLOT_ON_LIMITED_RANGE
  }
    }
  #endif /* PLOT_ON_LIMITED_RANGE */
  }
  SiTraceConfiguration("traces suspend");
  /* for (i=0; i<12; i++) { Si2183_READ(front_end->demod, dcom_read);}*/ /* To (possibly) compensate a dcom issue seen with FPGA boards */

  if (strcmp(source,"spectrum")==0) {
  /*#define   PLOT_WITH_BACKOFF_INFO */ /* DO NOT USE !!! */
  #ifdef    PLOT_WITH_BACKOFF_INFO
    Si2183_FORCED_TRACE("rf_backoff 0: %10d %d (center %d)\n", gp_reg16_1, gp_reg16_1*inter_carrier_space/1000, gp_reg32_2/1000);
    Si2183_FORCED_TRACE("rf_backoff 1: %10d %d (center %d)\n", gp_reg16_2, gp_reg16_2*inter_carrier_space/1000, gp_reg32_2/1000);
    Si2183_FORCED_TRACE("rf_backoff 2: %10d %d (center %d)\n", gp_reg16_3, gp_reg16_3*inter_carrier_space/1000, gp_reg32_2/1000);
    Si2183_FORCED_TRACE("backoff limited to %3d%% (%d MHz) BW %d MHz\n", gp_reg8_3*100/255, (gp_reg8_3/255)*(front_end->demod->prop->scan_sat_unicable_bw.scan_sat_unicable_bw/10), front_end->demod->prop->scan_sat_unicable_bw.scan_sat_unicable_bw/10);
    /* read spectrum additional data tables */
    for (i=0; i< 3; i++) {
      Si2183_WRITE (front_end->demod, dcom_control_byte, (0x80000000 | (48 - 1)) );
      Si2183_WRITE (front_end->demod, dcom_addr        ,  gp_reg32_0 + i*48*4);
      nb_channel = (gp_reg32_1 >> (8*i)) & 0xFF;
      Si2183_FORCED_TRACE("run %d, %3d channels\n", i, nb_channel);
      w = 0;
      while ( w < nb_channel ) {
        Si2183_READ (front_end->demod , dcom_read);
        Si2183_FORCED_TRACE("channel %d, %2d : 0x%08x tune_freq %8d ", i, w, dcom_read, dcom_read);

        Si2183_READ (front_end->demod , dcom_read);
        read_data = dcom_read;
        msb = (read_data >> 16) & 0xffff;
        lsb = (read_data >>  0) & 0xffff;
        Si2183_FORCED_TRACE(" 0x%08x offset %8d sr %8d ", dcom_read, msb, lsb);

        Si2183_READ (front_end->demod , dcom_read);
        Si2183_FORCED_TRACE(" 0x%08x variance %8d \n", dcom_read, dcom_read);

        w++;
      }
      Si2183_FORCED_TRACE("\n");
    }
  #endif /* PLOT_WITH_BACKOFF_INFO */
  }

  SiTraceConfiguration("traces suspend");
  /* Start Si2183 DSP */
  Si2183_WRITE (front_end->demod, dcom_control_byte, 0xc0000000);
  Si2183_WRITE (front_end->demod, dcom_addr,         0x90000000);
  Si2183_WRITE (front_end->demod, dcom_data,         0x00000000);
  #ifdef    PAUSE_FREQ
  if (strcmp(source,"spectrum")==0) {
    if (tune_freq >= PAUSE_FREQ - 50000000) {
      if (tune_freq <= PAUSE_FREQ + 50000000) {
        Si2183_FORCED_TRACE ("please check the spectrum on the spectrum analyser (tuner_freq %8d) and press a key when done...\n", tune_freq);
        system("pause");
      }
    }
  }
  #endif /* PAUSE_FREQ */
  SiTraceConfiguration("traces resume");
}
#endif /* ALLOW_Si2183_BLINDSCAN_DEBUG */
/************************************************************************************************************************
  NAME: Si2183_Configure
  DESCRIPTION: Setup TER and SAT AGCs, Common Properties startup
  Parameter:  Pointer to Si2183 Context
  Returns:    I2C transaction error code, NO_Si2183_ERROR if successful
************************************************************************************************************************/
signed   int Si2183_Configure           (L1_Si2183_Context *api)
{
    signed   int return_code;
    return_code = NO_Si2183_ERROR;

    SiTRACE("Si2183_Configure media %d die %d\n",api->media, api->rsp->get_rev.mcm_die);

    /* AGC settings when not used */
    if        ( api->rsp->get_rev.mcm_die == Si2183_GET_REV_RESPONSE_MCM_DIE_DIE_A) {
      api->cmd->dd_mp_defaults.mp_a_mode   = Si2183_DD_MP_DEFAULTS_CMD_MP_A_MODE_DISABLE;
      api->cmd->dd_mp_defaults.mp_b_mode   = Si2183_DD_MP_DEFAULTS_CMD_MP_B_MODE_NO_CHANGE;
      api->cmd->dd_mp_defaults.mp_c_mode   = Si2183_DD_MP_DEFAULTS_CMD_MP_C_MODE_DISABLE;
      api->cmd->dd_mp_defaults.mp_d_mode   = Si2183_DD_MP_DEFAULTS_CMD_MP_D_MODE_NO_CHANGE;
    } else if ( api->rsp->get_rev.mcm_die == Si2183_GET_REV_RESPONSE_MCM_DIE_DIE_B) {
      api->cmd->dd_mp_defaults.mp_a_mode   = Si2183_DD_MP_DEFAULTS_CMD_MP_A_MODE_NO_CHANGE;
      api->cmd->dd_mp_defaults.mp_b_mode   = Si2183_DD_MP_DEFAULTS_CMD_MP_B_MODE_DISABLE;
      api->cmd->dd_mp_defaults.mp_c_mode   = Si2183_DD_MP_DEFAULTS_CMD_MP_C_MODE_NO_CHANGE;
      api->cmd->dd_mp_defaults.mp_d_mode   = Si2183_DD_MP_DEFAULTS_CMD_MP_D_MODE_DISABLE;
    } else {
      api->cmd->dd_mp_defaults.mp_a_mode   = Si2183_DD_MP_DEFAULTS_CMD_MP_A_MODE_DISABLE;
      api->cmd->dd_mp_defaults.mp_b_mode   = Si2183_DD_MP_DEFAULTS_CMD_MP_B_MODE_DISABLE;
      api->cmd->dd_mp_defaults.mp_c_mode   = Si2183_DD_MP_DEFAULTS_CMD_MP_C_MODE_DISABLE;
      api->cmd->dd_mp_defaults.mp_d_mode   = Si2183_DD_MP_DEFAULTS_CMD_MP_D_MODE_DISABLE;
    }
#ifdef    DEMOD_DVB_T2
    /*  For DVB_T2, if the TER tuner has a FEF freeze input pin, drive this pin to 0 or 1 when NOT in T2 */
    /* if FEF is active high, set the pin to 0 when NOT in T2 */
    /* if FEF is active low,  set the pin to 1 when NOT in T2 */
    if (api->fef_mode == Si2183_FEF_MODE_FREEZE_PIN) {
      switch (api->fef_pin) {
        case 0xA: {
          api->cmd->dvbt2_fef.fef_tuner_flag      = Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MP_A;
          if (api->fef_level == 1) { api->cmd->dd_mp_defaults.mp_a_mode = Si2183_DD_MP_DEFAULTS_CMD_MP_A_MODE_DRIVE_0; }
          else                     { api->cmd->dd_mp_defaults.mp_a_mode = Si2183_DD_MP_DEFAULTS_CMD_MP_A_MODE_DRIVE_1; }
          break;
        }
        case 0xB: {
          api->cmd->dvbt2_fef.fef_tuner_flag      = Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MP_B;
          if (api->fef_level == 1) { api->cmd->dd_mp_defaults.mp_b_mode = Si2183_DD_MP_DEFAULTS_CMD_MP_B_MODE_DRIVE_0; }
          else                     { api->cmd->dd_mp_defaults.mp_b_mode = Si2183_DD_MP_DEFAULTS_CMD_MP_B_MODE_DRIVE_1; }
          break;
        }
        case 0xC: {
          api->cmd->dvbt2_fef.fef_tuner_flag      = Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MP_C;
          if (api->fef_level == 1) { api->cmd->dd_mp_defaults.mp_c_mode = Si2183_DD_MP_DEFAULTS_CMD_MP_C_MODE_DRIVE_0; }
          else                     { api->cmd->dd_mp_defaults.mp_c_mode = Si2183_DD_MP_DEFAULTS_CMD_MP_C_MODE_DRIVE_1; }
          break;
        }
        case 0xD: {
          api->cmd->dvbt2_fef.fef_tuner_flag      = Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MP_D;
          if (api->fef_level == 1) { api->cmd->dd_mp_defaults.mp_d_mode = Si2183_DD_MP_DEFAULTS_CMD_MP_D_MODE_DRIVE_0; }
          else                     { api->cmd->dd_mp_defaults.mp_d_mode = Si2183_DD_MP_DEFAULTS_CMD_MP_D_MODE_DRIVE_1; }
          break;
        }
        default: break;
      }
    }
    Si2183_L1_SendCommand2(api, Si2183_DVBT2_FEF_CMD_CODE);
#endif /* DEMOD_DVB_T2 */
    Si2183_L1_SendCommand2(api, Si2183_DD_MP_DEFAULTS_CMD_CODE);

#ifdef    TERRESTRIAL_FRONT_END
    if (api->media == Si2183_TERRESTRIAL) {
      /* TER AGC pins and inversion are previously selected using Si2183_L2_TER_AGC */
      api->cmd->dd_ext_agc_ter.agc_1_kloop = Si2183_DD_EXT_AGC_TER_CMD_AGC_1_KLOOP_MIN;
      api->cmd->dd_ext_agc_ter.agc_1_min   = Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MIN_MIN;

      api->cmd->dd_ext_agc_ter.agc_2_kloop = 18;
      api->cmd->dd_ext_agc_ter.agc_2_min   = Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MIN_MIN;
      Si2183_L1_SendCommand2(api, Si2183_DD_EXT_AGC_TER_CMD_CODE);
    }
#endif /* TERRESTRIAL_FRONT_END */

#ifdef    SATELLITE_FRONT_END
    if (api->media == Si2183_SATELLITE  ) {
      /* SAT AGC pins and inversion are previously selected using Si2183_L2_SAT_AGC */
      api->cmd->dd_ext_agc_sat.agc_1_kloop = 18;
      api->cmd->dd_ext_agc_sat.agc_1_min   = Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MIN_MIN;

      api->cmd->dd_ext_agc_sat.agc_2_kloop = Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_KLOOP_MIN;
      api->cmd->dd_ext_agc_sat.agc_2_min   = Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MIN_MIN;

      Si2183_L1_SendCommand2(api, Si2183_DD_EXT_AGC_SAT_CMD_CODE);
    }
#endif /* SATELLITE_FRONT_END */

    /* LEDS MANAGEMENT */
    /* set hardware lock on LED */
    if        ( api->rsp->get_rev.mcm_die == Si2183_GET_REV_RESPONSE_MCM_DIE_DIE_A) {
      api->cmd->config_pins.gpio0_mode     = Si2183_CONFIG_PINS_CMD_GPIO0_MODE_NO_CHANGE;
      api->cmd->config_pins.gpio0_read     = Si2183_CONFIG_PINS_CMD_GPIO0_READ_DO_NOT_READ;
      api->cmd->config_pins.gpio1_mode     = Si2183_CONFIG_PINS_CMD_GPIO1_MODE_HW_LOCK;
      api->cmd->config_pins.gpio1_read     = Si2183_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ;
    } else if ( api->rsp->get_rev.mcm_die == Si2183_GET_REV_RESPONSE_MCM_DIE_DIE_B) {
      api->cmd->config_pins.gpio0_mode     = Si2183_CONFIG_PINS_CMD_GPIO0_MODE_HW_LOCK;
      api->cmd->config_pins.gpio0_read     = Si2183_CONFIG_PINS_CMD_GPIO0_READ_DO_NOT_READ;
      api->cmd->config_pins.gpio1_mode     = Si2183_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE;
      api->cmd->config_pins.gpio1_read     = Si2183_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ;
    } else {
      api->cmd->config_pins.gpio0_mode     = Si2183_CONFIG_PINS_CMD_GPIO0_MODE_HW_LOCK;
      api->cmd->config_pins.gpio0_read     = Si2183_CONFIG_PINS_CMD_GPIO0_READ_DO_NOT_READ;
      api->cmd->config_pins.gpio1_mode     = Si2183_CONFIG_PINS_CMD_GPIO1_MODE_TS_ERR;
      api->cmd->config_pins.gpio1_read     = Si2183_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ;
    }
    Si2183_L1_SendCommand2(api, Si2183_CONFIG_PINS_CMD_CODE);

    /* Edit the procedure below if you have any properties settings different from the standard defaults */
    Si2183_storeUserProperties     (api->prop);
    /* Download properties different from 'default' */
    Si2183_downloadAllProperties(api);

    /* debug unicable scan !!! 0 better ; SR/8 default ; > worst */
    /* Si2183_L1_DD_SET_REG  (api, 7 , 71, 10, 0); */

    /* Change demod I2C SCL_MAST pad slew rate to 6.
        Default value is 3, maximum value is 7.
        Value of 6 avoids reduction of Thd_dat from HOST to MAST */
    #define Si2183_scl_mast_slr_LSB   134
    #define Si2183_scl_mast_slr_MID    66
    #define Si2183_scl_mast_slr_MSB     1
    Si2183_L1_DD_SET_REG  (api, Si2183_scl_mast_slr_LSB, Si2183_scl_mast_slr_MID, Si2183_scl_mast_slr_MSB, 6);

#ifdef    USB_Capability
    if        ( api->rsp->get_rev.mcm_die == Si2183_GET_REV_RESPONSE_MCM_DIE_SINGLE) {
      /* Setting GPIF clock to not_inverted to allow TS over USB transfer */
      Si2183_L1_DD_SET_REG  (api, 0 , 35, 1, 0);
    }
#endif /* USB_Capability */
#ifdef    Si2167B_20_COMPATIBLE
    /* This needs to be done for Si2167B (part 67, ROM 0) with the following FW: */
    /*  FW 2_0b23 and above                                     */
    /*  FW 2_2b2  and above                                     */
    if (  (api->rsp->part_info.part     == 67 )
        & (api->rsp->part_info.romid    ==  0 ) ) {
      if ( (
            (api->rsp->get_rev.cmpmajor == '2')
          & (api->rsp->get_rev.cmpminor == '0')
          & (api->rsp->get_rev.cmpbuild >= 23)
         ) | (
            (api->rsp->get_rev.cmpmajor == '2')
          & (api->rsp->get_rev.cmpminor == '2')
          & (api->rsp->get_rev.cmpbuild >=  2)
         ) ) {
        api->cmd->dd_set_reg.reg_code_lsb = 132;
        api->cmd->dd_set_reg.reg_code_mid = 50;
        api->cmd->dd_set_reg.reg_code_msb = 10;
        api->cmd->dd_set_reg.value        = 1;
         /* 0x8e for DVB-C with Si2167B 2_0b23: fw 2.0b23 is able to behave as 2.0b18 for 32QAM lock time with this code. */
        SiTRACE("[SiTRACE]Si2183_Configure: DD_SET_REG  (api, 132, 50, 10, 1) for 32QAM lock time with Si2167B\n");
        Si2183_L1_SendCommand2 (api, Si2183_DD_SET_REG_CMD_CODE);
      }
    }
#endif /* Si2167B_20_COMPATIBLE */

    return return_code;
}
/************************************************************************************************************************
  NAME: Si2183_STANDBY
  DESCRIPTION:
  Parameter:  Pointer to Si2183 Context
  Returns:    I2C transaction error code, NO_Si2183_ERROR if successful
************************************************************************************************************************/
signed   int Si2183_STANDBY             (L1_Si2183_Context *api)
{
    return Si2183_L1_POWER_DOWN (api);
}
/************************************************************************************************************************
  NAME: Si2183_WAKEUP
  DESCRIPTION:
  Parameter:  Pointer to Si2183 Context
  Returns:    I2C transaction error code, NO_Si2183_ERROR if successful
************************************************************************************************************************/
signed   int Si2183_WAKEUP              (L1_Si2183_Context *api)
{
    signed   int return_code;
    signed   int media;

    return_code = NO_Si2183_ERROR;
    media       = Si2183_Media(api, api->standard);
    SiTRACE ("Si2183_WAKEUP: media %d\n", media);

    /* Clock source selection */
    switch (media) {
      default                 :
#ifdef    TERRESTRIAL_FRONT_END
      case Si2183_TERRESTRIAL : {
        api->cmd->start_clk.clk_mode = api->tuner_ter_clock_input;
        break;
      }
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
      case Si2183_SATELLITE   : {
        api->cmd->start_clk.clk_mode = api->tuner_sat_clock_input;
        break;
      }
#endif /* SATELLITE_FRONT_END */
    }
    /* when not using a Xtal, set TUNE_CAP to 'EXT_CLK' (The value for XTAL use is set in Si2183_L2_SW_Init) */
    if (api->cmd->start_clk.clk_mode != Si2183_START_CLK_CMD_CLK_MODE_XTAL) {
      api->cmd->start_clk.tune_cap = Si2183_START_CLK_CMD_TUNE_CAP_EXT_CLK;
    }
    Si2183_L1_START_CLK (api,
                            Si2183_START_CLK_CMD_SUBCODE_CODE,
                            Si2183_START_CLK_CMD_RESERVED1_RESERVED,
                            api->cmd->start_clk.tune_cap,
                            Si2183_START_CLK_CMD_RESERVED2_RESERVED,
                            api->cmd->start_clk.clk_mode,
                            Si2183_START_CLK_CMD_RESERVED3_RESERVED,
                            Si2183_START_CLK_CMD_RESERVED4_RESERVED,
                            Si2183_START_CLK_CMD_START_CLK_START_CLK);
    /* Reference frequency selection */
    switch (media) {
      default                 :
#ifdef    TERRESTRIAL_FRONT_END
      case Si2183_TERRESTRIAL : {
        if (api->tuner_ter_clock_freq == 16) {
          SiTRACE("Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_16MHZ\n");
          api->cmd->power_up.clock_freq = Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_16MHZ;
        } else if (api->tuner_ter_clock_freq == 24) {
          SiTRACE("Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_24MHZ\n");
          api->cmd->power_up.clock_freq = Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_24MHZ;
        } else {
          SiTRACE("Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_27MHZ\n");
          api->cmd->power_up.clock_freq = Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_27MHZ;
        }
        break;
      }
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
      case Si2183_SATELLITE   : {
        if (api->tuner_sat_clock_freq == 16) {
          SiTRACE("Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_16MHZ\n");
          api->cmd->power_up.clock_freq = Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_16MHZ;
        } else if (api->tuner_sat_clock_freq == 24) {
          SiTRACE("Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_24MHZ\n");
          api->cmd->power_up.clock_freq = Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_24MHZ;
        } else {
          SiTRACE("Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_27MHZ\n");
          api->cmd->power_up.clock_freq = Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_27MHZ;
        }
        break;
      }
#endif /* SATELLITE_FRONT_END */
    }

    return_code = Si2183_L1_POWER_UP (api,
                            Si2183_POWER_UP_CMD_SUBCODE_CODE,
                            api->cmd->power_up.reset,
                            Si2183_POWER_UP_CMD_RESERVED2_RESERVED,
                            Si2183_POWER_UP_CMD_RESERVED4_RESERVED,
                            Si2183_POWER_UP_CMD_RESERVED1_RESERVED,
                            Si2183_POWER_UP_CMD_ADDR_MODE_CURRENT,
                            Si2183_POWER_UP_CMD_RESERVED5_RESERVED,
                            api->cmd->power_up.func,
                            api->cmd->power_up.clock_freq,
                            Si2183_POWER_UP_CMD_CTSIEN_DISABLE,
                            Si2183_POWER_UP_CMD_WAKE_UP_WAKE_UP);

         if (api->cmd->start_clk.clk_mode == Si2183_START_CLK_CMD_CLK_MODE_CLK_CLKIO  ) { SiTRACE ("Si2183_START_CLK_CMD_CLK_MODE_CLK_CLKIO\n"  );}
    else if (api->cmd->start_clk.clk_mode == Si2183_START_CLK_CMD_CLK_MODE_CLK_XTAL_IN) { SiTRACE ("Si2183_START_CLK_CMD_CLK_MODE_CLK_XTAL_IN\n");}
    else if (api->cmd->start_clk.clk_mode == Si2183_START_CLK_CMD_CLK_MODE_XTAL       ) { SiTRACE ("Si2183_START_CLK_CMD_CLK_MODE_XTAL\n"       );}

         if (api->cmd->power_up.reset == Si2183_POWER_UP_CMD_RESET_RESET  ) { SiTRACE ("Si2183_POWER_UP_CMD_RESET_RESET\n"  );}
    else if (api->cmd->power_up.reset == Si2183_POWER_UP_CMD_RESET_RESUME ) { SiTRACE ("Si2183_POWER_UP_CMD_RESET_RESUME\n");}

    if (return_code != NO_Si2183_ERROR ) {
      SiTRACE("Si2183_WAKEUP: POWER_UP ERROR!\n");
      SiERROR("Si2183_WAKEUP: POWER_UP ERROR!\n");
      return return_code;
    }
    /* After a successful POWER_UP, set values for 'resume' only */
    api->cmd->power_up.reset = Si2183_POWER_UP_CMD_RESET_RESUME;

    return NO_Si2183_ERROR;
}
/************************************************************************************************************************
  NAME: Si2183_PowerUpWithPatch
  DESCRIPTION: Send Si2183 API PowerUp Command with PowerUp to bootloader,
  Check the Chip rev and part, and ROMID are compared to expected values.
  Load the Firmware Patch then Start the Firmware.
  Programming Guide Reference:    Flowchart A.2 (POWER_UP with patch flowchart)

  Parameter:  pointer to Si2183 Context
  Returns:    Si2183/I2C transaction error code, NO_Si2183_ERROR if successful
************************************************************************************************************************/
signed   int Si2183_PowerUpWithPatch    (L1_Si2183_Context *api)
{
  signed   int return_code;
  signed   int fw_loaded;
  return_code = NO_Si2183_ERROR;
  fw_loaded   = 0;

  if (!(api->load_control & Si2183_SKIP_POWERUP      )) {
    /* Before patching, set POWER_UP values for 'RESET' and 'BOOTLOADER' */
    api->cmd->power_up.reset = Si2183_POWER_UP_CMD_RESET_RESET;
    api->cmd->power_up.func  = Si2183_POWER_UP_CMD_FUNC_BOOTLOADER;

    return_code = Si2183_WAKEUP(api);

    if (return_code != NO_Si2183_ERROR) {
      SiERROR("Si2183_PowerUpWithPatch: WAKEUP error!\n");
        return return_code;
    }

    /* Get the Part Info from the chip.   This command is only valid in Bootloader mode */
    if ((return_code = Si2183_L1_PART_INFO(api)) != NO_Si2183_ERROR) {
        SiTRACE ("Si2183_L1_PART_INFO error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }
    SiTRACE("part    Si21%02d",   api->rsp->part_info.part   );
           if (api->rsp->part_info.chiprev == Si2183_PART_INFO_RESPONSE_CHIPREV_A) {
    SiTRACE("A\n");
    } else if (api->rsp->part_info.chiprev == Si2183_PART_INFO_RESPONSE_CHIPREV_B) {
    SiTRACE("B\n");
    } else if (api->rsp->part_info.chiprev == Si2183_PART_INFO_RESPONSE_CHIPREV_C) {
    SiTRACE("C\n");
    } else if (api->rsp->part_info.chiprev == Si2183_PART_INFO_RESPONSE_CHIPREV_D) {
    SiTRACE("D\n");
    } else if (api->rsp->part_info.chiprev == Si2183_PART_INFO_RESPONSE_CHIPREV_E) {
    SiTRACE("E\n");
    } else {
    SiTRACE("\nchiprev %d\n",        api->rsp->part_info.chiprev);
    }
    SiTRACE("romid   %d\n",        api->rsp->part_info.romid  );
    SiTRACE("pmajor  0x%02x\n",    api->rsp->part_info.pmajor );
    SiTRACE("pminor  0x%02x\n",    api->rsp->part_info.pminor );
    SiTRACE("pbuild  %d\n",        api->rsp->part_info.pbuild );
    SiTRACE("chiprev 0x%02x\n",    api->rsp->part_info.chiprev);
    SiTRACE("chiprev %c\n",        api->rsp->part_info.chiprev + 0x40 );
    if ((api->rsp->part_info.pmajor >= 0x30) & (api->rsp->part_info.pminor >= 0x30)) {
    SiTRACE("Full Info       'Si21%02d-%c%c%c ROM%x NVM%c_%cb%d'\n\n\n", api->rsp->part_info.part, api->rsp->part_info.chiprev + 0x40, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.romid, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
    }
  } else {
    SiTRACE("Si2183_PowerUpWithPatch SKIP_POWERUP\n");
  }
  if (!(api->load_control & Si2183_SKIP_LOADFIRMWARE )) {
    /* Load FW from a table */
    if (api->nbLines) {
      SiTRACE("loading FW from stored table (%d lines))\n", api->nbLines);
      if ( Si2183_LoadFirmware_16(api, api->fw_table, api->nbLines) != NO_Si2183_ERROR ) {
        SiERROR ("Error loading stored FW table (16 Bytes)\n");
      } else {
        fw_loaded++; SiERROR ("Loaded FW table\n");
      }
    }

    SiLOGS ("api->spi_download %d\n",api->spi_download);
    /* Check part info values and load the proper firmware */
#ifdef    DEMOD_ISDB_T
#ifdef    Si2180_A55_COMPATIBLE
    SiLOGS ("Build Option: Si2180_A55_COMPATIBLE (smaller FW without T2/C2/S2)\n");
#ifdef FW_DOWNLOAD_OVER_SPI
    #ifdef    Si2180_SPI_5_8b2_LINES
    if ( (api->spi_download) & (!fw_loaded) ) {
      SiLOGS   ("Checking if we can load Si2180_SPI_5_8b2\n");
      SiTRACE  ("Si2180_SPI_5_8b2_LINES: Is this part a  'Si21%2d_ROM%x_%c_%c_b%d'?\n", Si2180_SPI_5_8b2_PART, Si2180_SPI_5_8b2_ROM, Si2180_SPI_5_8b2_PMAJOR, Si2180_SPI_5_8b2_PMINOR, Si2180_SPI_5_8b2_PBUILD );
      if ((api->rsp->part_info.romid  == Si2180_SPI_5_8b2_ROM   )
        &(
            ((api->rsp->part_info.part == 80 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
        )
          ) {
        SiTRACE("Updating FW via SPI for 'Si21%2d NVM%c_%cb%d'\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
        if ((return_code = Si2183_LoadFirmwareSPI(api, Si2180_SPI_5_8b2, Si2180_SPI_5_8b2_LINES, Si2180_SPI_5_8b2_KEY, Si2180_SPI_5_8b2_NUM )) != NO_Si2183_ERROR) {
          SiTRACE ("Si2183_LoadFirmwareSPI  error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
          return return_code;
        }
        #ifdef    Si2180_SPI_5_8b2_INFOS
          SiERROR(Si2180_SPI_5_8b2_INFOS);
        #endif /* Si2180_SPI_5_8b2_INFOS */
        fw_loaded++;
      }
    }
    #endif /* Si2180_SPI_5_8b2_LINES */
#endif /* FW_DOWNLOAD_OVER_SPI */
    #ifdef    Si2180_FIRMWARE_FOR_x55_PARTS
    if (!fw_loaded) {
      SiTRACE ("Checking if we can load firmware for a Si2180 5_5b3 part\n");
      if   (((api->rsp->part_info.romid  == 1 )
        & (
            ((api->rsp->part_info.part == 80 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
        ) & (
             (api->rsp->part_info.pmajor == '5')
           & (api->rsp->part_info.pminor == '5')
           & (api->rsp->part_info.pbuild ==  1 )
        ) )
        ) {
        SiTRACE("Updating FW for 'Si21%2d NVM%c_%cb%d' (patch)\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
        if ((return_code = Si2183_LoadFirmware_16(api, Si2180_FIRMWARE_FOR_x55_PARTS, sizeof(Si2180_FIRMWARE_FOR_x55_PARTS)/(sizeof(firmware_struct)))) != NO_Si2183_ERROR) {
           SiTRACE ("Si2183_LoadFirmware_16 error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
           return return_code;
         }
        fw_loaded++;
      }
    }
    #endif /* Si2180_FIRMWARE_FOR_x55_PARTS */
#endif /* Si2180_A55_COMPATIBLE */
#ifdef    Si2180_A50_COMPATIBLE
    SiLOGS ("Build Option: Si2180_A50_COMPATIBLE (smaller FW without T2/C2/S2)\n");
#ifdef FW_DOWNLOAD_OVER_SPI
    #ifdef    Si2180_SPI_5_3b4_LINES
    if ( (api->spi_download) & (!fw_loaded) ) {
      SiLOGS   ("Checking if we can load Si2180_SPI_5_3b4\n");
      SiTRACE  ("Si2180_SPI_5_3b4_LINES: Is this part a  'Si21%2d_ROM%x_%c_%c_b%d'?\n", Si2180_SPI_5_3b4_PART, Si2180_SPI_5_3b4_ROM, Si2180_SPI_5_3b4_PMAJOR, Si2180_SPI_5_3b4_PMINOR, Si2180_SPI_5_3b4_PBUILD );
      if ((api->rsp->part_info.romid  == Si2180_SPI_5_3b4_ROM   )
        &(
            ((api->rsp->part_info.part == 80 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
        )
          ) {
        SiTRACE("Updating FW via SPI for 'Si21%2d NVM%c_%cb%d'\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
        if ((return_code = Si2183_LoadFirmwareSPI(api, Si2180_SPI_5_3b4, Si2180_SPI_5_3b4_LINES, Si2180_SPI_5_3b4_KEY, Si2180_SPI_5_3b4_NUM )) != NO_Si2183_ERROR) {
          SiTRACE ("Si2183_LoadFirmwareSPI  error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
          return return_code;
        }
        #ifdef    Si2180_SPI_5_3b4_INFOS
          SiERROR(Si2180_SPI_5_3b4_INFOS);
        #endif /* Si2180_SPI_5_3b4_INFOS */
        fw_loaded++;
      }
    }
#endif /* FW_DOWNLOAD_OVER_SPI */
    #endif /* Si2180_SPI_5_3b4_LINES */
    #ifdef    Si2180_FIRMWARE_FOR_x50_PARTS
    if (!fw_loaded) {
      SiTRACE ("Checking if we can load firmware for a Si2180 5_0b3 part\n");
      if   (((api->rsp->part_info.romid  == 0 )
        & (
            ((api->rsp->part_info.part == 80 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
        ) & (
             (api->rsp->part_info.pmajor == '5')
           & (api->rsp->part_info.pminor == '0')
           & (api->rsp->part_info.pbuild ==  3 )
        ) )
        ) {
        SiTRACE("Updating FW for 'Si21%2d NVM%c_%cb%d' (patch)\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
        if ((return_code = Si2183_LoadFirmware_16(api, Si2180_FIRMWARE_FOR_x50_PARTS, sizeof(Si2180_FIRMWARE_FOR_x50_PARTS)/(sizeof(firmware_struct)))) != NO_Si2183_ERROR) {
           SiTRACE ("Si2183_LoadFirmware_16 error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
           return return_code;
         }
        fw_loaded++;
      }
    }
    #endif /* Si2180_FIRMWARE_FOR_x50_PARTS */
#endif /* Si2180_A50_COMPATIBLE */
#endif /* DEMOD_ISDB_T */
#ifdef    Si2183_B63_COMPATIBLE
    SiLOGS ("Build Option: Si2183_B63_COMPATIBLE\n");
    #ifdef    Si2183_FIRMWARE_FOR_x63_PARTS
    if (!fw_loaded) {
      SiTRACE ("Checking if we can load firmware for a 6_3b1 part\n");
      if   (((api->rsp->part_info.romid == 2 )
        & (
            ((api->rsp->part_info.part == 60 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 62 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 64 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 66 ) & (api->rsp->part_info.chiprev + 0x40 == 'D') )
         || ((api->rsp->part_info.part == 67 ) & (api->rsp->part_info.chiprev + 0x40 == 'D') )
         || ((api->rsp->part_info.part == 68 ) & (api->rsp->part_info.chiprev + 0x40 == 'D') )
         || ((api->rsp->part_info.part == 69 ) & (api->rsp->part_info.chiprev + 0x40 == 'D') )
         || ((api->rsp->part_info.part == 0  ) & (1) )
        ) & (
             (api->rsp->part_info.pmajor == '6')
           & (api->rsp->part_info.pminor == '3')
           & (api->rsp->part_info.pbuild ==  1 )
        ) )
        ) {
        SiTRACE("Updating FW for 'Si21%2d NVM%c_%cb%d' (patch)\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
        if ((return_code = Si2183_LoadFirmware_16(api, Si2183_FIRMWARE_FOR_x63_PARTS, sizeof(Si2183_FIRMWARE_FOR_x63_PARTS)/(sizeof(firmware_struct)))) != NO_Si2183_ERROR) {
           SiTRACE ("Si2183_LoadFirmware_16 for 6_3b1 error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
           return return_code;
         }
        fw_loaded++;
#ifdef    DEMOD_DVB_S_S2_DSS
        api->MIS_capability=1;
#endif /* DEMOD_DVB_S_S2_DSS */
      }
    }
    #endif /* Si2183_FIRMWARE_FOR_x63_PARTS */
#endif /* Si2183_B63_COMPATIBLE */
#ifdef    Si2183_B60_COMPATIBLE
    SiLOGS ("Build Option: Si2183_B60_COMPATIBLE\n");
#ifdef FW_DOWNLOAD_OVER_SPI
    #ifdef    Si2183_SPI_FIRMWARE_FOR_x60_PARTS
    if ( (api->spi_download) & (!fw_loaded) ) {
      SiTRACE ("Checking if we can load firmware for a 6_0b1 part in SPI mode\n");
      if   (((api->rsp->part_info.romid == 2 )
        & (
            ((api->rsp->part_info.part == 60 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 62 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 64 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 66 ) & (api->rsp->part_info.chiprev + 0x40 == 'D') )
         || ((api->rsp->part_info.part == 67 ) & (api->rsp->part_info.chiprev + 0x40 == 'D') )
         || ((api->rsp->part_info.part == 68 ) & (api->rsp->part_info.chiprev + 0x40 == 'D') )
         || ((api->rsp->part_info.part == 69 ) & (api->rsp->part_info.chiprev + 0x40 == 'D') )
         || ((api->rsp->part_info.part == 0  ) & (1) )
#ifdef    DEMOD_ISDB_T
         || ((api->rsp->part_info.part == 80 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 81 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 82 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 83 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
#endif /* DEMOD_ISDB_T */
        ) & (
             (api->rsp->part_info.pmajor == '6')
           & (api->rsp->part_info.pminor == '0')
           & (api->rsp->part_info.pbuild ==  1 )
        ) )
        ) {
        SiTRACE("Updating FW via SPI for 'Si21%2d NVM%c_%cb%d'\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
        if ((return_code = Si2183_LoadFirmwareSPI_Split(api, Si2183_SPI_FIRMWARE_FOR_x60_PARTS, sizeof(Si2183_SPI_FIRMWARE_FOR_x60_PARTS)/(sizeof(unsigned char)), 0xaa, 3, sizeof(Si2183_SPI_SPLIT_LIST_FOR_x60_PARTS)/(sizeof(unsigned int)), Si2183_SPI_SPLIT_LIST_FOR_x60_PARTS )) != NO_Si2183_ERROR) {
          SiTRACE ("Si2183_LoadFirmwareSPI_Split  error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
          return return_code;
        }
#ifdef    DEMOD_DVB_S_S2_DSS
        api->MIS_capability=1;
#endif /* DEMOD_DVB_S_S2_DSS */
        fw_loaded++;
      }
    }
    #endif /* Si2183_SPI_FIRMWARE_FOR_x60_PARTS */
#endif /* FW_DOWNLOAD_OVER_SPI */
    #ifdef    Si2183_FIRMWARE_FOR_x60_PARTS
    if (!fw_loaded) {
      SiTRACE ("Checking if we can load firmware for a 6_0b1 part\n");
      if   (((api->rsp->part_info.romid == 2 )
        & (
            ((api->rsp->part_info.part == 60 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 62 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 64 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 66 ) & (api->rsp->part_info.chiprev + 0x40 == 'D') )
         || ((api->rsp->part_info.part == 67 ) & (api->rsp->part_info.chiprev + 0x40 == 'D') )
         || ((api->rsp->part_info.part == 68 ) & (api->rsp->part_info.chiprev + 0x40 == 'D') )
         || ((api->rsp->part_info.part == 69 ) & (api->rsp->part_info.chiprev + 0x40 == 'D') )
         || ((api->rsp->part_info.part == 0  ) & (1) )
#ifdef    DEMOD_ISDB_T
         || ((api->rsp->part_info.part == 80 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 81 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 82 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 83 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
#endif /* DEMOD_ISDB_T */
        ) & (
             (api->rsp->part_info.pmajor == '6')
           & (api->rsp->part_info.pminor == '0')
           & (api->rsp->part_info.pbuild ==  1 )
        ) )
        ) {
        SiTRACE("Updating FW for 'Si21%2d NVM%c_%cb%d' (patch)\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
        if ((return_code = Si2183_LoadFirmware_16(api, Si2183_FIRMWARE_FOR_x60_PARTS, sizeof(Si2183_FIRMWARE_FOR_x60_PARTS)/(sizeof(firmware_struct)))) != NO_Si2183_ERROR) {
           SiTRACE ("Si2183_LoadFirmware_16 for 6_0b1 error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
           return return_code;
         }
        fw_loaded++;
#ifdef    DEMOD_DVB_S_S2_DSS
        api->MIS_capability=1;
#endif /* DEMOD_DVB_S_S2_DSS */
      }
    }
    #endif /* Si2183_FIRMWARE_FOR_x60_PARTS */
#endif /* Si2183_B60_COMPATIBLE */
#ifdef    Si2183_B5B_COMPATIBLE
    SiLOGS ("Build Option: Si2183_B5B_COMPATIBLE\n");
#ifdef FW_DOWNLOAD_OVER_SPI
    #ifdef    Si2183_SPI_5_Bb5_BYTES
    if ( (api->spi_download) & (!fw_loaded) ) {
      SiLOGS   ("Checking if we can load Si2183_SPI_5_Bb5\n");
      SiTRACE  ("Si2183_SPI_5_Bb5_LINES: Is this part a  'Si21%2d_ROM%x_%c_%c_b%d'?\n", Si2183_SPI_5_Bb5_PART, Si2183_SPI_5_Bb5_ROM, Si2183_SPI_5_Bb5_PMAJOR, Si2183_SPI_5_Bb5_PMINOR, Si2183_SPI_5_Bb5_PBUILD );
      if ((api->rsp->part_info.romid  == Si2183_SPI_5_Bb5_ROM   )
        &(
            ((api->rsp->part_info.part == 69 ) & (api->rsp->part_info.chiprev + 0x40 == 'D') )
         || ((api->rsp->part_info.part == 68 ) & (api->rsp->part_info.chiprev + 0x40 == 'D') )
         || ((api->rsp->part_info.part == 64 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 62 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 60 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ( api->rsp->part_info.part == 0  )
#ifdef    DEMOD_ISDB_T
         || ((api->rsp->part_info.part == 83 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 82 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 81 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 80 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
#endif /* DEMOD_ISDB_T */
        )
          ) {
        SiTRACE("Updating FW via SPI for 'Si21%2d NVM%c_%cb%d'\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
        #ifdef    Si2183_SPI_5_Bb5_SPLITS
        if ((return_code = Si2183_LoadFirmwareSPI_Split(api, Si2183_SPI_5_Bb5, Si2183_SPI_5_Bb5_BYTES, Si2183_SPI_5_Bb5_KEY, Si2183_SPI_5_Bb5_NUM, Si2183_SPI_5_Bb5_SPLITS, Si2183_SPI_5_Bb5_SPLIT_LIST )) != NO_Si2183_ERROR) {
          SiTRACE ("Si2183_LoadFirmwareSPI_Split  error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
          return return_code;
        }
        #else  /* Si2183_SPI_5_Bb5_SPLITS */
        if ((return_code = Si2183_LoadFirmwareSPI(api, Si2183_SPI_5_Bb5, Si2183_SPI_5_Bb5_BYTES, Si2183_SPI_5_Bb5_KEY, Si2183_SPI_5_Bb5_NUM )) != NO_Si2183_ERROR) {
          SiTRACE ("Si2183_LoadFirmwareSPI  error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
          return return_code;
        }
        #endif /* Si2183_SPI_5_Bb5_SPLITS */
        #ifdef    Si2183_SPI_5_Bb5_INFOS
          SiERROR(Si2183_SPI_5_Bb5_INFOS);
        #endif /* Si2183_SPI_5_Bb5_INFOS */
        fw_loaded++;
#ifdef    DEMOD_DVB_S_S2_DSS
        api->MIS_capability=1;
#endif /* DEMOD_DVB_S_S2_DSS */
      }
    }
    #endif /* Si2183_SPI_5_Bb5_BYTES */
#endif /* FW_DOWNLOAD_OVER_SPI */
    #ifdef    Si2183_FIRMWARE_FOR_x5B_PARTS
    if (!fw_loaded) {
      SiTRACE ("Checking if we can load firmware for a 5_Bb0 part\n");
      if   (((api->rsp->part_info.romid == 2 )
        & (
            ((api->rsp->part_info.part == 60 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 62 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 64 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 66 ) & (api->rsp->part_info.chiprev + 0x40 == 'D') )
         || ((api->rsp->part_info.part == 67 ) & (api->rsp->part_info.chiprev + 0x40 == 'D') )
         || ((api->rsp->part_info.part == 68 ) & (api->rsp->part_info.chiprev + 0x40 == 'D') )
         || ((api->rsp->part_info.part == 69 ) & (api->rsp->part_info.chiprev + 0x40 == 'D') )
#ifdef    DEMOD_ISDB_T
         || ((api->rsp->part_info.part == 80 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 81 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 82 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 83 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
#endif /* DEMOD_ISDB_T */
        ) & (
             (api->rsp->part_info.pmajor == '5')
           & (api->rsp->part_info.pminor == 'B')
           & (api->rsp->part_info.pbuild ==  0 )
        ) )
        ) {
        SiTRACE("Updating FW for 'Si21%2d NVM%c_%cb%d' (patch)\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
        if ((return_code = Si2183_LoadFirmware(api, Si2183_FIRMWARE_FOR_x5B_PARTS, sizeof(Si2183_FIRMWARE_FOR_x5B_PARTS)/(8*sizeof(unsigned char)))) != NO_Si2183_ERROR) {
           SiTRACE ("Si2183_LoadFirmware for 5_Bb0 part error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
           return return_code;
         }
        fw_loaded++;
#ifdef    DEMOD_DVB_S_S2_DSS
        api->MIS_capability=1;
#endif /* DEMOD_DVB_S_S2_DSS */
      }
    }
    #endif /* Si2183_FIRMWARE_FOR_x5B_PARTS */
#endif /* Si2183_B5B_COMPATIBLE */
#ifdef    Si2183_A55_COMPATIBLE
    SiLOGS ("Build Option: Si2183_A55_COMPATIBLE\n");
#ifdef FW_DOWNLOAD_OVER_SPI
    #ifdef    Si2183_SPI_5_5b7_BYTES
    if ( (api->spi_download) & (!fw_loaded) ) {
      SiLOGS   ("Checking if we can load Si2183_SPI_5_5b7\n");
      SiTRACE  ("Si2183_SPI_5_5b7_LINES: Is this part a  'Si21%2d_ROM%x_%c_%c_b%d'?\n", Si2183_SPI_5_5b7_PART, Si2183_SPI_5_5b7_ROM, Si2183_SPI_5_5b7_PMAJOR, Si2183_SPI_5_5b7_PMINOR, Si2183_SPI_5_5b7_PBUILD );
      if ((api->rsp->part_info.romid  == Si2183_SPI_5_5b7_ROM   )
        &(
            ((api->rsp->part_info.part == 69 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 68 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 64 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 62 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 60 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ( api->rsp->part_info.part == 0  )
#ifdef    DEMOD_ISDB_T
         || ((api->rsp->part_info.part == 83 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part == 82 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part == 81 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part == 80 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
#endif /* DEMOD_ISDB_T */
        )
          ) {
        SiTRACE("Updating FW via SPI for 'Si21%2d NVM%c_%cb%d'\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
        #ifdef    Si2183_SPI_5_5b7_SPLITS
        if ((return_code = Si2183_LoadFirmwareSPI_Split(api, Si2183_SPI_5_5b7, Si2183_SPI_5_5b7_BYTES, Si2183_SPI_5_5b7_KEY, Si2183_SPI_5_5b7_NUM, Si2183_SPI_5_5b7_SPLITS, Si2183_SPI_5_5b7_SPLIT_LIST )) != NO_Si2183_ERROR) {
          SiTRACE ("Si2183_LoadFirmwareSPI_Split  error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
          return return_code;
        }
        #else  /* Si2183_SPI_5_5b7_SPLITS */
        if ((return_code = Si2183_LoadFirmwareSPI(api, Si2183_SPI_5_5b7, Si2183_SPI_5_5b7_BYTES, Si2183_SPI_5_5b7_KEY, Si2183_SPI_5_5b7_NUM )) != NO_Si2183_ERROR) {
          SiTRACE ("Si2183_LoadFirmwareSPI  error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
          return return_code;
        }
        #endif /* Si2183_SPI_5_5b7_SPLITS */
        #ifdef    Si2183_SPI_5_5b7_INFOS
          SiERROR(Si2183_SPI_5_5b7_INFOS);
        #endif /* Si2183_SPI_5_5b7_INFOS */
        fw_loaded++;
#ifdef    DEMOD_DVB_S_S2_DSS
        api->MIS_capability=1;
#endif /* DEMOD_DVB_S_S2_DSS */
      }
    }
    #endif /* Si2183_SPI_5_5b7_BYTES */
#endif /* FW_DOWNLOAD_OVER_SPI */
    #ifdef    Si2183_FIRMWARE_FOR_x55_PARTS
    if (!fw_loaded) {
      SiTRACE ("Checking if we can load firmware for a 5_5b1 part\n");
      if   (((api->rsp->part_info.romid == 1 )
        & (
            ((api->rsp->part_info.part == 60 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 62 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 64 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 66 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 67 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 68 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 69 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
#ifdef    DEMOD_ISDB_T
         || ((api->rsp->part_info.part == 80 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part == 81 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part == 82 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part == 83 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
#endif /* DEMOD_ISDB_T */
        ) & (
             (api->rsp->part_info.pmajor == '5')
           & (api->rsp->part_info.pminor == '5')
           & (api->rsp->part_info.pbuild ==  1 )
        ) )
        ) {
        SiTRACE("Updating FW for 'Si21%2d NVM%c_%cb%d' (patch)\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
        if ((return_code = Si2183_LoadFirmware_16(api, Si2183_FIRMWARE_FOR_x55_PARTS, sizeof(Si2183_FIRMWARE_FOR_x55_PARTS)/(sizeof(firmware_struct)))) != NO_Si2183_ERROR) {
           SiTRACE ("Si2183_LoadFirmware_16 error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
           return return_code;
         }
        fw_loaded++;
#ifdef    DEMOD_DVB_S_S2_DSS
        api->MIS_capability=1;
#endif /* DEMOD_DVB_S_S2_DSS */
      }
    }
    #endif /* Si2183_FIRMWARE_FOR_x55_PARTS */
#endif /* Si2183_A55_COMPATIBLE */
#ifdef    Si2183_A50_COMPATIBLE
    SiLOGS ("Build Option: Si2183_A50_COMPATIBLE\n");
#ifdef FW_DOWNLOAD_OVER_SPI
    #ifdef    Si2183_SPI_5_0b15_BYTES
    if ( (api->spi_download) & (!fw_loaded) ) {
      SiLOGS   ("Checking if we can load Si2183_SPI_5_0b15\n");
      SiTRACE  ("Si2183_SPI_5_0b15_BYTES: Is this part a  'Si21%2d_ROM%x_%c_%c_b%d'?\n", Si2183_SPI_5_0b15_PART, Si2183_SPI_5_0b15_ROM, Si2183_SPI_5_0b15_PMAJOR, Si2183_SPI_5_0b15_PMINOR, Si2183_SPI_5_0b15_PBUILD );
      if ((api->rsp->part_info.romid  == Si2183_SPI_5_0b15_ROM   )
        &(
            ((api->rsp->part_info.part == 69 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 68 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 64 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 62 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 60 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ( api->rsp->part_info.part == 0  )
#ifdef    DEMOD_ISDB_T
         || ((api->rsp->part_info.part == 83 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part == 82 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part == 81 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part == 80 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
#endif /* DEMOD_ISDB_T */
        )
          ) {
        SiTRACE("Updating FW via SPI for 'Si21%2d NVM%c_%cb%d'\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
        #ifdef    Si2183_SPI_5_0b15_SPLITS
        if ((return_code = Si2183_LoadFirmwareSPI_Split(api, Si2183_SPI_5_0b15, Si2183_SPI_5_0b15_BYTES, Si2183_SPI_5_0b15_KEY, Si2183_SPI_5_0b15_NUM, Si2183_SPI_5_0b15_SPLITS, Si2183_SPI_5_0b15_SPLIT_LIST )) != NO_Si2183_ERROR) {
          SiTRACE ("Si2183_LoadFirmwareSPI_Split  error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
          return return_code;
        }
        #else  /* Si2183_SPI_5_0b15_SPLITS */
        if ((return_code = Si2183_LoadFirmwareSPI(api, Si2183_SPI_5_0b15, Si2183_SPI_5_0b15_BYTES, Si2183_SPI_5_0b15_KEY, Si2183_SPI_5_0b15_NUM )) != NO_Si2183_ERROR) {
          SiTRACE ("Si2183_LoadFirmwareSPI  error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
          return return_code;
        }
        #endif /* Si2183_SPI_5_0b15_SPLITS */
        #ifdef    Si2183_SPI_5_0b15_INFOS
          SiERROR(Si2183_SPI_5_0b15_INFOS);
        #endif /* Si2183_SPI_5_0b15_INFOS */
        fw_loaded++;
      }
    }
    #endif /* Si2183_SPI_5_0b15_BYTES */
#endif /* FW_DOWNLOAD_OVER_SPI */
    #ifdef    Si2183_FIRMWARE_FOR_x50_PARTS
    if (!fw_loaded) {
      SiTRACE ("Checking if we can load firmware for a 5_0b3 part\n");
      if   (((api->rsp->part_info.romid == 0 )
        & (
            ((api->rsp->part_info.part == 60 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 62 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 64 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 66 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 67 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 68 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 69 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
#ifdef    DEMOD_ISDB_T
         || ((api->rsp->part_info.part == 80 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part == 81 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part == 82 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part == 83 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
#endif /* DEMOD_ISDB_T */
        ) & (
             (api->rsp->part_info.pmajor == '5')
           & (api->rsp->part_info.pminor == '0')
           & (api->rsp->part_info.pbuild ==  3 )
        ) )
        ) {
        SiTRACE("Updating FW for 'Si21%2d NVM%c_%cb%d' (patch)\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
        if ((return_code = Si2183_LoadFirmware_16(api, Si2183_FIRMWARE_FOR_x50_PARTS, sizeof(Si2183_FIRMWARE_FOR_x50_PARTS)/(sizeof(firmware_struct)))) != NO_Si2183_ERROR) {
           SiTRACE ("Si2183_LoadFirmware_16 error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
           return return_code;
         }
        fw_loaded++;
      }
    }
    #endif /* Si2183_FIRMWARE_FOR_x50_PARTS */
#endif /* Si2183_A50_COMPATIBLE */
#ifdef    Si2183_ES_COMPATIBLE
    SiLOGS ("Build Option: Si2183_ES_COMPATIBLE\n");
    #ifdef    Si2183_FIRMWARE_FOR_ES_PARTS
    if (!fw_loaded) {
      SiTRACE ("Checking if we can load firmware for an ES part\n");
      if   (((api->rsp->part_info.romid == 0 )
        & (
            ((api->rsp->part_info.part == 60 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 62 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 64 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 66 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 67 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 68 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
         || ((api->rsp->part_info.part == 69 ) & (api->rsp->part_info.chiprev + 0x40 == 'C') )
#ifdef    DEMOD_ISDB_T
         || ((api->rsp->part_info.part == 80 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part == 81 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part == 82 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part == 83 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
#endif /* DEMOD_ISDB_T */
         || ((api->rsp->part_info.part ==  0 ) )
        ) & (
             (api->rsp->part_info.pmajor == '5')
           & (api->rsp->part_info.pminor == '0')
           & (api->rsp->part_info.pbuild ==  3 )
        ) )
        /*  One line for compatibility with early Si2183 and derivatives samples with NO NVM content */
        || ((api->rsp->part_info.romid  == 1   ) & ( api->rsp->part_info.part == 0  ) )
        ) {
        SiTRACE("Updating FW for 'Si21%2d NVM%c_%cb%d' (patch)\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
        if ((return_code = Si2183_LoadFirmware_16(api, Si2183_FIRMWARE_FOR_ES_PARTS, sizeof(Si2183_FIRMWARE_FOR_ES_PARTS)/(sizeof(firmware_struct)))) != NO_Si2183_ERROR) {
           SiTRACE ("Si2183_LoadFirmware_16 error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
           return return_code;
         }
        fw_loaded++;
      }
    }
    #endif /* Si2183_FIRMWARE_FOR_ES_PARTS */
#endif /* Si2183_ES_COMPATIBLE */
#ifdef    Si2167_B25_COMPATIBLE
    SiLOGS ("Build Option: Si2167_B25_COMPATIBLE\n");
    #ifdef    Si2167B_PATCH16_2_5b0_LINES
    if (!fw_loaded) {
      SiTRACE  ("Si2183_PATCH16_2_5b0: Is this part a  'Si21%2d_ROM%x_%c_%c_b%d'?\n", Si2183_PATCH16_2_5b0_PART, Si2183_PATCH16_2_5b0_ROM, Si2183_PATCH16_2_5b0_PMAJOR, Si2183_PATCH16_2_5b0_PMINOR, Si2183_PATCH16_2_5b0_PBUILD );
      if  ((api->rsp->part_info.romid  == Si2183_PATCH16_2_5b0_ROM   )
         & (api->rsp->part_info.part == 67 ) & (api->rsp->part_info.chiprev + 0x40 == 'B')
         & (api->rsp->part_info.pmajor == Si2183_PATCH16_2_5b0_PMAJOR)
         & (api->rsp->part_info.pminor == Si2183_PATCH16_2_5b0_PMAJOR)
         & (api->rsp->part_info.pbuild == Si2183_PATCH16_2_5b0_PBUILD)
        ) {
        SiTRACE("Updating FW for 'Si21%2d NVM%c_%cb%d' (patch)\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
        #ifdef    Si2183_PATCH16_2_5b0_INFOS
          SiERROR(Si2183_PATCH16_2_5b0_INFOS);
        #endif /* Si2183_PATCH16_2_5b0_INFOS */
        if ((return_code = Si2183_LoadFirmware_16(api, Si2183_PATCH16_2_5b0, Si2183_PATCH16_2_5b0_LINES)) != NO_Si2183_ERROR) {
           SiTRACE ("Si2183_LoadFirmware_16 Si2183_PATCH16_2_5b0 error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
           return return_code;
         }
        fw_loaded++;
      }
    }
    #endif /* Si2183_PATCH16_2_5b0_LINES */
#endif /* Si2167_B25_COMPATIBLE */
#ifdef    Si2164_A40_COMPATIBLE
    SiLOGS ("Build Option: Si2164_A40_COMPATIBLE\n");
    #ifdef    Si2164_DVB_C2_FIRMWARE_FOR_x40_PARTS
    if (!fw_loaded) {
      SiTRACE ("Checking if we can load DVB-C2 firmware for a 4_0b2 part\n");
      if   (((api->rsp->part_info.romid  == 1 )
        & (
            ((api->rsp->part_info.part == 60 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part == 62 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part == 64 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
        ) & (
             (api->rsp->part_info.pmajor == '4')
           & (api->rsp->part_info.pminor == '0')
           & (api->rsp->part_info.pbuild ==  2 )
        ) )
        ) {
        SiTRACE("Updating FW for 'Si21%2d NVM%c_%cb%d'\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
        if ((return_code = Si2183_LoadFirmware_16(api, Si2164_DVB_C2_FIRMWARE_FOR_x40_PARTS, sizeof(Si2164_DVB_C2_FIRMWARE_FOR_x40_PARTS)/(sizeof(firmware_struct)) )) != NO_Si2183_ERROR) {
          SiTRACE ("Si2183_LoadFirmware_16 error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
          return return_code;
        }
        fw_loaded++;
      }
    }
    #endif /* Si2164_DVB_C2_FIRMWARE_FOR_x40_PARTS */
    #ifdef    Si2164_FIRMWARE_FOR_x40_PARTS
    if (!fw_loaded) {
      SiTRACE ("Checking if we can load firmware for a 4_0b2 part\n");
      if   (((api->rsp->part_info.romid  == 1 )
        & (
            ((api->rsp->part_info.part == 60 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part == 62 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part == 64 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part == 68 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part == 69 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
        ) & (
             (api->rsp->part_info.pmajor == '4')
           & (api->rsp->part_info.pminor == '0')
           & (api->rsp->part_info.pbuild ==  2 )
        ) )
        ) {
        SiTRACE("Updating FW for 'Si21%2d NVM%c_%cb%d'\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
        if ((return_code = Si2183_LoadFirmware_16(api, Si2164_FIRMWARE_FOR_x40_PARTS, sizeof(Si2164_FIRMWARE_FOR_x40_PARTS)/(sizeof(firmware_struct)) )) != NO_Si2183_ERROR) {
          SiTRACE ("Si2183_LoadFirmware_16 error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
          return return_code;
        }
        fw_loaded++;
      }
    }
    #endif /* Si2164_FIRMWARE_FOR_x40_PARTS */
#endif /* Si2164_A40_COMPATIBLE */
#ifdef    Si2169_30_COMPATIBLE
    SiLOGS ("Build Option: Si2169_30_COMPATIBLE\n");
    #ifdef    Si2169_FIRMWARE_FOR_x30_PARTS
    if (!fw_loaded) {
      SiTRACE ("Checking if we can load firmware for a 6_0b1 part\n");
      if   (((api->rsp->part_info.romid  ==  3 )
        & (
            ((api->rsp->part_info.part   == 69 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
         || ((api->rsp->part_info.part   == 68 ) & (api->rsp->part_info.chiprev + 0x40 == 'A') )
        ) & (
             (api->rsp->part_info.pmajor == '3')
           & (api->rsp->part_info.pminor == '0')
           & (api->rsp->part_info.pbuild ==  2 )
        ) )
        ) {
          SiTRACE("Updating FW for 'Si21%2d_ROM%x %c_%c_b%d'\n", api->rsp->part_info.part, api->rsp->part_info.romid, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
          if ((return_code = Si2183_LoadFirmware(api, Si2169_FIRMWARE_FOR_x30_PARTS, sizeof(Si2169_FIRMWARE_FOR_x30_PARTS)/(8*sizeof(unsigned char)) )) != NO_Si2183_ERROR) {
              SiTRACE ("Si2183_LoadFirmware error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
              return return_code;
          }
          fw_loaded++;
        }
    }
    #endif /* Si2169_FIRMWARE_FOR_x30_PARTS */
#endif /* Si2169_30_COMPATIBLE */
#ifdef    Si2167B_20_COMPATIBLE
    SiLOGS ("Build Option: Si2167B_20_COMPATIBLE\n");
#ifdef    DEMOD_DVB_C
    #ifdef    Si2167B_DVB_C_FIRMWARE_FOR_x20_PARTS
    SiTRACE("api->load_DVB_C_Blindlock_Patch %d\n",api->load_DVB_C_Blindlock_Patch);
    if (api->load_DVB_C_Blindlock_Patch == 1) {
      if (!fw_loaded) {
        SiTRACE ("Checking if we can load DVB-C firmware for a 2_0b5 part\n");
        if  ((api->rsp->part_info.romid  ==  0 )
          &(
            ((api->rsp->part_info.part   == 67 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part   == 66 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part   == 65 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
          )
           & (api->rsp->part_info.pmajor == '2')
           & (api->rsp->part_info.pminor == '0')
           & (api->rsp->part_info.pbuild ==  5 )
          ) {
          SiTRACE("Updating FW for 'Si21%2d_FW_%c_%c_b%d'\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
          if ((return_code = Si2183_LoadFirmware(api, Si2167B_DVB_C_FIRMWARE_FOR_x20_PARTS, sizeof(Si2167B_DVB_C_FIRMWARE_FOR_x20_PARTS)/(8*sizeof(unsigned char)) )) != NO_Si2183_ERROR) {
            SiTRACE ("Si2183_LoadFirmware error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
            return return_code;
          }
          fw_loaded++;
        }
      }
    }
    #endif /* Si2167B_DVB_C_FIRMWARE_FOR_x20_PARTS */
#endif /* DEMOD_DVB_C */
    #ifdef    Si2167B_FIRMWARE_FOR_x20_PARTS
    if (!fw_loaded) {
      SiTRACE ("Checking if we can load firmware for a 2_0b5 part\n");
      if ((api->rsp->part_info.romid  ==  0 )
        &(
          ((api->rsp->part_info.part   == 67 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
       || ((api->rsp->part_info.part   == 66 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
        )
        & (api->rsp->part_info.pmajor == '2')
        & (api->rsp->part_info.pminor == '0')
        & (api->rsp->part_info.pbuild ==  5 )
        ) {
        SiTRACE("Updating FW for 'Si21%2d_FW_%c_%c_b%d'\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
        if ((return_code = Si2183_LoadFirmware(api, Si2167B_FIRMWARE_FOR_x20_PARTS, sizeof(Si2167B_FIRMWARE_FOR_x20_PARTS)/(8*sizeof(unsigned char)) )) != NO_Si2183_ERROR) {
          SiTRACE ("Si2183_LoadFirmware error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
           return return_code;
         }
        fw_loaded++;
      }
    }
    #endif /* Si2167B_FIRMWARE_FOR_x20_PARTS */
#endif /* Si2167B_20_COMPATIBLE */
#ifdef    Si2167B_22_COMPATIBLE
    SiLOGS("Build Option: Si2167B_22_COMPATIBLE\n");
#ifdef    DEMOD_DVB_C
    #ifdef    Si2167B_DVB_C_FIRMWARE_FOR_x22_PARTS
    SiTRACE( "api->load_DVB_C_Blindlock_Patch %d\n",api->load_DVB_C_Blindlock_Patch);
    if (api->load_DVB_C_Blindlock_Patch == 1) {
      if (!fw_loaded) {
        SiTRACE ("Checking if we can load DVB_C firmware for a 2_2b1 part\n");
        if ((api->rsp->part_info.romid   ==  0 )
          &(
            ((api->rsp->part_info.part   == 67 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part   == 66 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
         || ((api->rsp->part_info.part   == 65 ) & (api->rsp->part_info.chiprev + 0x40 == 'B') )
          )
          & (api->rsp->part_info.pmajor == '2')
          & (api->rsp->part_info.pminor == '2')
          & (api->rsp->part_info.pbuild ==  1 )) {
          SiTRACE("Updating FW for 'Si21%2d_FW_%c_%c_b%d'\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
          if ((return_code = Si2183_LoadFirmware(api, Si2167B_DVB_C_FIRMWARE_FOR_x22_PARTS, sizeof(Si2167B_DVB_C_FIRMWARE_FOR_x22_PARTS)/(8*sizeof(unsigned char))) ) != NO_Si2183_ERROR) {
            SiTRACE ("Si2183_LoadPatch error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
            return return_code;
          }
          fw_loaded++;
        }
      }
    }
    #endif /* Si2167B_DVB_C_FIRMWARE_FOR_x22_PARTS */
#endif /* DEMOD_DVB_C */
    #ifdef    Si2167B_FIRMWARE_FOR_x22_PARTS
    if (!fw_loaded) {
      SiTRACE ("Checking if we can load firmware for a 2_2b1 part\n");
      if ((api->rsp->part_info.romid  ==  0 )
        &(
          (api->rsp->part_info.part   == 67 )
       || (api->rsp->part_info.part   == 66 )
       || (api->rsp->part_info.part   == 65 )
       || (api->rsp->part_info.part   ==  0 )
        )
        & (api->rsp->part_info.pmajor == '2')
        & (api->rsp->part_info.pminor == '2')
        & (api->rsp->part_info.pbuild ==  1 )
        ) {
        SiTRACE("Updating FW for 'Si21%2d_FW_%c_%c_b%d'\n", api->rsp->part_info.part, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
        if ((return_code = Si2183_LoadFirmware(api, Si2167B_FIRMWARE_FOR_x22_PARTS, sizeof(Si2167B_FIRMWARE_FOR_x22_PARTS)/(8*sizeof(unsigned char))) ) != NO_Si2183_ERROR) {
          SiTRACE ("Si2183_LoadFirmware error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
          return return_code;
        }
        fw_loaded++;
      }
    }
    #endif /* Si2167B_FIRMWARE_FOR_x22_PARTS */
#endif /* Si2167B_22_COMPATIBLE */
    if (!fw_loaded) {
      SiTRACE ("Si2183_LoadFirmware error: NO Firmware Loaded! Possible part/code/fw incompatibility !\n");
      SiERROR ("Si2183_LoadFirmware error: NO Firmware Loaded! Possible part/code/fw incompatibility !\n");
      return ERROR_Si2183_LOADING_FIRMWARE;
    }
  } else {
    SiTRACE("Si2183_PowerUpWithPatch SKIP_LOADFIRMWARE\n");
  }
  if (!(api->load_control & Si2183_SKIP_STARTFIRMWARE)) {
    /* Start the Firmware */
    if ((return_code = Si2183_StartFirmware(api)) != NO_Si2183_ERROR) {
        /* Start firmware */
        SiTRACE ("Si2183_StartFirmware error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }

    /* Check the FW version */
    if ((return_code = Si2183_L1_GET_REV (api)) != NO_Si2183_ERROR) {
      SiTRACE ("Si2183_L1_GET_REV error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
      if (api->spi_download) {
        api->spi_download = 0;
        SiERROR ("FW download using SPI failed, trying i2c download as fallback solution\n");
        return Si2183_PowerUpWithPatch(api);
      } else {
        return return_code;
      }
    }

    if ((api->rsp->get_rev.mcm_die) != Si2183_GET_REV_RESPONSE_MCM_DIE_SINGLE) {
      SiLOGS ("Si21%2d%d-%c%c%c Die %c Part running 'FW_%c_%cb%d'\n", api->rsp->part_info.part
                                                                    , 2
                                                                    , api->rsp->part_info.chiprev + 0x40
                                                                    , api->rsp->part_info.pmajor
                                                                    , api->rsp->part_info.pminor
                                                                    , api->rsp->get_rev.mcm_die   + 0x40
                                                                    , api->rsp->get_rev.cmpmajor
                                                                    , api->rsp->get_rev.cmpminor
                                                                    , api->rsp->get_rev.cmpbuild );
    } else {
      SiLOGS ("Si21%2d-%c%c%c Part running 'FW_%c_%cb%d'\n", api->rsp->part_info.part
                                                                    , api->rsp->part_info.chiprev + 0x40
                                                                    , api->rsp->part_info.pmajor
                                                                    , api->rsp->part_info.pminor
                                                                    , api->rsp->get_rev.cmpmajor
                                                                    , api->rsp->get_rev.cmpminor
                                                                    , api->rsp->get_rev.cmpbuild );
    }
  } else {
    SiTRACE("Si2183_PowerUpWithPatch SKIP_STARTFIRMWARE\n");
  }

  return NO_Si2183_ERROR;
}
/************************************************************************************************************************
  NAME: Si2183_PowerUpUsingBroadcastI2C
  DESCRIPTION: This is similar to PowerUpWithPatch() for demod_count demods but it uses the I2C Broadcast
  command to allow the firmware download simultaneously to all demods.

  Parameter:  demods, a pointer to a table of L1 Si2183 Contexts
  Parameter:  demod_count, the number of demods in the table
  Returns:    Si2183/I2C transaction error code, NO_Si2183_ERROR if successful
************************************************************************************************************************/
signed   int Si2183_PowerUpUsingBroadcastI2C    (L1_Si2183_Context *demods[], signed   int demod_count )
{
  signed   int return_code;
  signed   int d;
  #define Si2183_DEMOD_BROADCAST_INDEX 0
  unsigned char logged_i2c_address;
  L1_Si2183_Context *api;
  api = demods[0]; /* To avoid compilation warning */
  return_code = NO_Si2183_ERROR;

  /* for each demod execute the powerup and part_info command but not the firmware download. */
  for (d = 0; d < demod_count; d++) {
    api = demods[d];
    demods[d]->load_control = Si2183_SKIP_LOADFIRMWARE | Si2183_SKIP_STARTFIRMWARE;

    /* Si2183_PowerUpWithPatch will return right after Si2183_L1_PART_INFO, because SKIP_LOADFIRMWARE and SKIP_STARTFIRMWARE are set */
    if ( (return_code = Si2183_PowerUpWithPatch(demods[d])) != NO_Si2183_ERROR) {
      SiTRACE ("Demod %d Si2183_PowerUpWithPatch error 0x%02x during 'POWERUP'\n", d, return_code);
      return return_code;
    }
    if ( (return_code = Si2183_L1_CONFIG_I2C(demods[d], Si2183_CONFIG_I2C_CMD_SUBCODE_CODE, Si2183_CONFIG_I2C_CMD_I2C_BROADCAST_ENABLED)) != NO_Si2183_ERROR ) {
      SiTRACE("Demod %d L1_CONFIG_I2C error 0x%02x\n", d, return_code);
      return return_code;
    }
  }

  /* At this stage, all demods are connected/powered up and in 'broadcast i2c' mode */

  /* store the address of demod0 to the broadcast address and restore the original address after we're done.  */
  logged_i2c_address = demods[Si2183_DEMOD_BROADCAST_INDEX]->i2c->address;
  demods[Si2183_DEMOD_BROADCAST_INDEX]->i2c->address = Si2183_BROADCAST_ADDRESS;

  /* set the load_control flag to SKIP_POWERUP so the firmware is downloaded and started on all demods only */
  demods[Si2183_DEMOD_BROADCAST_INDEX]->load_control = Si2183_SKIP_POWERUP | Si2183_SKIP_STARTFIRMWARE;

  /* Si2183_PowerUpWithPatch will now broadcast the demod fw and return
      when all is completed, because load_fw is now '1'                               */
  return_code = Si2183_PowerUpWithPatch(demods[Si2183_DEMOD_BROADCAST_INDEX]);

  /* Return the broadcast demod address to its 'normal' value                         */
  demods[Si2183_DEMOD_BROADCAST_INDEX]->i2c->address = logged_i2c_address;

  if ( return_code != NO_Si2183_ERROR) {
    SiTRACE("Demod %d Si2183_PowerUpWithPatch error 0x%02x during 'LOADFIRMWARE'\n", d,return_code);
    return return_code;
  }

  /* Disable 'broadcast i2c' for all demods */
  for (d = 0; d < demod_count; d++) {
    api = demods[d];
    if ( (return_code = Si2183_L1_CONFIG_I2C(api, Si2183_CONFIG_I2C_CMD_SUBCODE_CODE, Si2183_CONFIG_I2C_CMD_I2C_BROADCAST_DISABLED)) != NO_Si2183_ERROR ) {
      SiTRACE("Demod %d L1_CONFIG_I2C error 0x%02x\n", d, return_code);
      return return_code;
    }
  }

  /* At this stage, all demods have received the patch. Now issue 'Si2183_StartFirmware' */
  /* and complete the init for all demods with their final addresses                     */
  for (d = 0; d < demod_count; d++) {
    demods[d]->load_control = Si2183_SKIP_POWERUP | Si2183_SKIP_LOADFIRMWARE;
    if ( (return_code = Si2183_PowerUpWithPatch(demods[d])) != NO_Si2183_ERROR) {
      SiTRACE("Demod %d Si2183_PowerUpWithPatch error 0x%02x during 'STARTFIRMWARE'\n", d, return_code);
      return return_code;
    }
    api = demods[d];
    /* Set Properties startup configuration         */
    Si2183_storePropertiesDefaults (demods[d]->propShadow);
    /* Edit the Si2183_storeUserProperties if you have any properties settings different from the standard defaults */
    Si2183_storeUserProperties     (demods[d]->prop);
    /* Reset the load_control flag */
    demods[d]->load_control =  Si2183_SKIP_NONE;
    /* Check CTS for all demods */
    if ( (return_code = Si2183_pollForCTS(demods[d])) != NO_Si2183_ERROR ) {
      SiTRACE_X("Demod %d pollForCTS error 0x%02x\n", d, return_code);
      return return_code;
    }
  }
  return NO_Si2183_ERROR;
}
/************************************************************************************************************************
  NAME: Si2183_LoadFirmware
  DESCRIPTON: Load firmware from FIRMWARE_TABLE array in Si2183_Firmware_x_y_build_z.h file into Si2183
              Requires Si2183 to be in bootloader mode after PowerUp
  Programming Guide Reference:    Flowchart A.3 (Download FW PATCH flowchart)

  Parameter:  Si2183 Context (I2C address)
  Parameter:  pointer to firmware table array
  Parameter:  number of lines in firmware table array (size in bytes / BYTES_PER_LINE)
  Returns:    Si2183/I2C transaction error code, NO_Si2183_ERROR if successful
************************************************************************************************************************/
signed   int Si2183_LoadFirmware        (L1_Si2183_Context *api, unsigned char fw_table[], signed   int nbLines)
{
    signed   int return_code;
    signed   int line;
    signed   int load_start_ms;
    return_code = NO_Si2183_ERROR;

    SiTRACE ("Si2183_LoadFirmware starting...\n");
    SiTRACE ("Si2183_LoadFirmware nbLines %d\n", nbLines);
    load_start_ms = system_time();
    /* for each line in fw_table */
    for (line = 0; line < nbLines; line++)
    {
        /* send Si2183_BYTES_PER_LINE fw bytes to Si2183 */
        if ((return_code = Si2183_L1_API_Patch(api, Si2183_BYTES_PER_LINE, fw_table + Si2183_BYTES_PER_LINE*line)) != NO_Si2183_ERROR)
      {
          SiTraceConfiguration((char*)"traces resume");
          SiTRACE("Si2183_LoadFirmware error 0x%02x patching line %d: %s\n", return_code, line, Si2183_L1_API_ERROR_TEXT(return_code) );
          if (line == 0) {
          SiTRACE("The firmware is incompatible with the part!\n");
          }
          SiTraceConfiguration((char*)"traces resume");
          return ERROR_Si2183_LOADING_FIRMWARE;
        }
        if (line==0) {
          if (system_time() - load_start_ms > 200) {
            SiERROR ("Si2183_LoadFirmware line 1 took too much time!\n");
          }
          SiTRACE ("Si2183_LoadFirmware line 1 took %4d ms\n", system_time() - load_start_ms);
      }
        if (line==3) {SiTraceConfiguration((char*)"traces suspend");}
    }
    SiTraceConfiguration((char*)"traces resume");
    api->i2c_download_ms = system_time() - load_start_ms;
    SiTRACE ("Si2183_LoadFirmware took %4d ms\n", api->i2c_download_ms);
    /* Storing Properties startup configuration in propShadow                              */
    /* !! Do NOT change the content of Si2183_storePropertiesDefaults                   !! */
    /* !! It should reflect the part internal property settings after firmware download !! */
    SiTRACE ("Si2183_storePropertiesDefaults\n");
    Si2183_storePropertiesDefaults (api->propShadow);

    SiTRACE ("Si2183_LoadFirmware complete...\n");
    return NO_Si2183_ERROR;
}
/************************************************************************************************************************
  NAME: Si2183_LoadFirmware_16
  DESCRIPTION: Load firmware from firmware_struct array in Si2183_Firmware_x_y_build_z.h file into Si2183
              Requires Si2183 to be in bootloader mode after PowerUp

  Parameter:  Si2183 Context (I2C address)
  Parameter:  pointer to firmware_struct array
  Parameter:  number of lines in firmware table array (size in bytes / firmware_struct)
  Returns:    Si2183/I2C transaction error code, NO_Si2183_ERROR if successful
************************************************************************************************************************/
signed   int Si2183_LoadFirmware_16     (L1_Si2183_Context *api, firmware_struct fw_table[], signed   int nbLines)
{
    signed   int return_code;
    signed   int line;
    signed   int load_start_ms;
    return_code = NO_Si2183_ERROR;

    SiTRACE ("Si2183_LoadFirmware_16 starting...\n");
    SiTRACE ("Si2183_LoadFirmware_16 nbLines %d\n", nbLines);
    load_start_ms = system_time();
    /* for each line in fw_table */
    for (line = 0; line < nbLines; line++) {
      if (fw_table[line].firmware_len > 0)  /* don't download if length is 0 , e.g. dummy firmware */
    {
        /* send firmware_len bytes (up to 16) to Si2183 */
        if ((return_code = Si2183_L1_API_Patch(api, fw_table[line].firmware_len, fw_table[line].firmware_table)) != NO_Si2183_ERROR)
        {
          SiTRACE("Si2183_LoadFirmware_16 error 0x%02x patching line %d: %s\n", return_code, line, Si2183_L1_API_ERROR_TEXT(return_code) );
          if (line == 0) {
          SiTRACE("The firmware is incompatible with the part!\n");
          }
          return ERROR_Si2183_LOADING_FIRMWARE;
        }
        if (line==3) {SiTraceConfiguration("traces suspend");}
    }
    }
    SiTraceConfiguration("traces resume");
    api->i2c_download_ms = system_time() - load_start_ms;
    SiTRACE ("Si2183_LoadFirmware_16 took %4d ms\n", api->i2c_download_ms);
    /* Storing Properties startup configuration in propShadow                              */
    /* !! Do NOT change the content of Si2183_storePropertiesDefaults                   !! */
    /* !! It should reflect the part internal property settings after firmware download !! */
    SiTRACE ("Si2183_storePropertiesDefaults\n");
    Si2183_storePropertiesDefaults (api->propShadow);

    SiTRACE ("Si2183_LoadFirmware_16 complete...\n");
    return NO_Si2183_ERROR;
}
#ifdef    FW_DOWNLOAD_OVER_SPI
/************************************************************************************************************************
  NAME: Si2183_LoadFirmwareSPI
  DESCRIPTON: Load firmware from FIRMWARE_TABLE array in Si2183_Firmware_x_y_build_z.h file into Si2183
              Requires Si2183 to be in bootloader mode after PowerUp
  Programming Guide Reference:    Flowchart A.3 (Download FW PATCH flowchart)

  Parameter:  Si2183 Context (I2C address)
  Parameter:  pointer to firmware table array
  Parameter:  number of lines in firmware table array (size in bytes / BYTES_PER_LINE)
  Returns:    Si2183/I2C transaction error code, NO_Si2183_ERROR if successful
************************************************************************************************************************/
signed   int Si2183_LoadFirmwareSPI     (L1_Si2183_Context *api, unsigned char fw_table[], int nbBytes, unsigned char pbl_key,  unsigned char pbl_num )
{
    #define SPI_MAX_BUFFER_SIZE 64
    signed   int return_code;
    signed   int load_start_ms;
    signed   int fw_index;

//  #define   SPI_DEBUGGING
  #ifdef    SPI_DEBUGGING
    unsigned char spi_bytes[4];
    unsigned char reg_byte [1];
  #endif /* SPI_DEBUGGING */

    unsigned char PATCH_IMAGE_SPI[] = {0x05,0x20,0x00,0x00,0x00,0x00,0x00,0x00};

    return_code = NO_Si2183_ERROR;
    fw_index = 0;

    /* <porting> For SiLabs EVB, no call to L0_EnableSPI is necessary
          because all settings are handled internally to the Cypress FW.
          This needs to be adapted to each SPI setup
    */
    if ( L0_EnableSPI(0x00) == 0) {
      SiERROR ("SPI can't be enabled. It's not supported by the L0!\n");
      return ERROR_Si2183_LOADING_FIRMWARE;
    }

    SiTRACE ("Si2183_LoadFirmwareSPI starting... nbBytes %d\n", nbBytes);

    L0_WriteCommandBytes  (api->i2c, 8, PATCH_IMAGE_SPI);
    Si2183_L1_CheckStatus (api);

    /* Set all spi__link fields to allow SPI download */
    api->cmd->spi_link.subcode       = Si2183_SPI_LINK_CMD_SUBCODE_CODE;
    api->cmd->spi_link.spi_pbl_key   = pbl_key;
    api->cmd->spi_link.spi_pbl_num   = pbl_num;
    api->cmd->spi_link.spi_conf_clk  = api->spi_clk_pin;
    api->cmd->spi_link.spi_clk_pola  = api->spi_clk_pola;
    api->cmd->spi_link.spi_conf_data = api->spi_data_pin;
    api->cmd->spi_link.spi_data_dir  = api->spi_data_order;
    api->cmd->spi_link.spi_enable    = Si2183_SPI_LINK_CMD_SPI_ENABLE_ENABLE;

    Si2183_L1_SendCommand2(api, Si2183_SPI_LINK_CMD_CODE);

    /* Set spi_link fields to prepare disabling SPI download */
    api->cmd->spi_link.spi_pbl_key   =   0;
    api->cmd->spi_link.spi_conf_clk  = Si2183_SPI_LINK_CMD_SPI_CONF_CLK_DISABLE;
    api->cmd->spi_link.spi_conf_data = Si2183_SPI_LINK_CMD_SPI_CONF_DATA_DISABLE;
    api->cmd->spi_link.spi_enable    = Si2183_SPI_LINK_CMD_SPI_ENABLE_DISABLE;

    load_start_ms = system_time();

 #ifdef    SPI_DEBUGGING
    spi_bytes[0] = 0xff; spi_bytes[1] = 0x00; L0_WriteBytes(api->i2c, 0x00, 2, spi_bytes);
    api->i2c->indexSize  = 2; api->i2c->mustReadWithoutStop = 0;

    L0_ReadBytes(api->i2c, 0x57, 1, reg_byte); SiTRACE(" spi_state      %d\n", reg_byte[0]&0x07 );
    L0_ReadBytes(api->i2c, 0x55, 1, reg_byte); SiTRACE(" spi_crc_status %d\n", reg_byte[0]&0x01 );

    for (fw_index = 0; fw_index < 20; fw_index ++) {
      return_code = L0_LoadSPIoverGPIF(fw_table+fw_index,  1);
      L0_ReadBytes(api->i2c, 0x57, 1, reg_byte);  SiTRACE(" spi_state      %d\n", reg_byte[0]&0x07 );
    }
 #endif /* SPI_DEBUGGING */

    return_code = L0_LoadSPIoverGPIF(fw_table+fw_index, nbBytes-fw_index);
    api->spi_download_ms = system_time() - load_start_ms;
    SiTRACE ("L0_LoadSPIoverGPIF     took %4d ms\n", api->spi_download_ms);

 #ifdef    SPI_DEBUGGING
    L0_ReadBytes(api->i2c, 0x57, 1, reg_byte); SiTRACE(" spi_state      %d\n", reg_byte[0]&0x07 );
    L0_ReadBytes(api->i2c, 0x55, 1, reg_byte); SiTRACE(" spi_crc_status %d\n", reg_byte[0]&0x01 );

    api->i2c->indexSize  = 0;
    spi_bytes[0] = 0xfe; spi_bytes[1] = 0x00; L0_WriteBytes(api->i2c, 0x00, 2, spi_bytes);
 #endif /* SPI_DEBUGGING */

    if ( return_code != 0 )
    {
      SiTRACE("Si2183_LoadFirmwareSPI  error 0x%02x loading %d bytes: %s\n", return_code, nbBytes, Si2183_L1_API_ERROR_TEXT(return_code) );
      SiERROR("Si2183_LoadFirmwareSPI  error\n");
      return_code = ERROR_Si2183_LOADING_FIRMWARE;
    } else {
      /* Storing Properties startup configuration in propShadow                              */
      /* !! Do NOT change the content of Si2183_storePropertiesDefaults                   !! */
      /* !! It should reflect the part internal property settings after firmware download !! */
      SiTRACE ("Si2183_storePropertiesDefaults\n");
      Si2183_storePropertiesDefaults (api->propShadow);
      SiTRACE ("Si2183_LoadFirmwareSPI complete...\n");
      return_code = NO_Si2183_ERROR;
    }

    Si2183_L1_SendCommand2(api, Si2183_SPI_LINK_CMD_CODE);

    L0_DisableSPI();

    return return_code;
}
/************************************************************************************************************************
  NAME: Si2183_LoadFirmwareSPI_Split
  DESCRIPTON: Load firmware from FIRMWARE_TABLE array in Si2183_Firmware_x_y_build_z.h file into Si2183
              Requires Si2183 to be in bootloader mode after PowerUp
  Programming Guide Reference:

  Parameter:  Si2183 Context (I2C address)
  Parameter:  fw_table, pointer to firmware table array
  Parameter:  nbBytes, number of bytes in firmware table array
  Parameter:  pbl_key, one byte KEY used to detect the start of a FW sequence
  Parameter:  pbl_num, number of pbl_key bytes used to detect the start of a FW sequence
  Parameter:  num_split, number of portions in the FW_table
  Returns:    split_list, list of split points
************************************************************************************************************************/
signed   int Si2183_LoadFirmwareSPI_Split(L1_Si2183_Context *api, unsigned char *fw_table, int nbBytes, unsigned char pbl_key,  unsigned char pbl_num , unsigned int num_split, unsigned int *split_list)
{
    #define SPI_MAX_BUFFER_SIZE 64
    signed   int return_code;
    signed   int load_start_ms;
    signed   int fw_index;
    unsigned int i;

//  #define   SPI_DEBUGGING
  #ifdef    SPI_DEBUGGING
    unsigned char spi_bytes[4];
    unsigned char reg_byte [1];
  #endif /* SPI_DEBUGGING */

    unsigned char PATCH_IMAGE_SPI[] = {0x05,0x20,0x00,0x00,0x00,0x00,0x00,0x00};

    return_code = NO_Si2183_ERROR;
    fw_index = 0;

    /* <porting> For SiLabs EVB, no call to L0_EnableSPI is necessary
          because all settings are handled internally to the Cypress FW.
          This needs to be adapted to each SPI setup
    */
    if ( L0_EnableSPI(0x00) == 0) {
      SiERROR ("SPI can't be enabled. It's not supported by the L0!\n");
      return ERROR_Si2183_LOADING_FIRMWARE;
    }

    SiTRACE ("Si2183_LoadFirmwareSPI_Split starting... nbBytes %d num_split %d\n", nbBytes, num_split);

    L0_WriteCommandBytes  (api->i2c, 8, PATCH_IMAGE_SPI);
    Si2183_L1_CheckStatus (api);

    /* Set all spi__link fields to allow SPI download */
    api->cmd->spi_link.subcode       = Si2183_SPI_LINK_CMD_SUBCODE_CODE;
    api->cmd->spi_link.spi_pbl_key   = pbl_key;
    api->cmd->spi_link.spi_pbl_num   = pbl_num;
    api->cmd->spi_link.spi_conf_clk  = api->spi_clk_pin;
    api->cmd->spi_link.spi_clk_pola  = api->spi_clk_pola;
    api->cmd->spi_link.spi_conf_data = api->spi_data_pin;
    api->cmd->spi_link.spi_data_dir  = api->spi_data_order;
    api->cmd->spi_link.spi_enable    = Si2183_SPI_LINK_CMD_SPI_ENABLE_ENABLE;

    Si2183_L1_SendCommand2(api, Si2183_SPI_LINK_CMD_CODE);

    /* Set spi_link fields to prepare disabling SPI download */
    api->cmd->spi_link.spi_pbl_key   =   0;
    api->cmd->spi_link.spi_conf_clk  = Si2183_SPI_LINK_CMD_SPI_CONF_CLK_DISABLE;
    api->cmd->spi_link.spi_conf_data = Si2183_SPI_LINK_CMD_SPI_CONF_DATA_DISABLE;
    api->cmd->spi_link.spi_enable    = Si2183_SPI_LINK_CMD_SPI_ENABLE_DISABLE;

    load_start_ms = system_time();

 #ifdef    SPI_DEBUGGING
    spi_bytes[0] = 0xff; spi_bytes[1] = 0x00; L0_WriteBytes(api->i2c, 0x00, 2, spi_bytes);
    api->i2c->indexSize  = 2; api->i2c->mustReadWithoutStop = 0;

    L0_ReadBytes(api->i2c, 0x57, 1, reg_byte); SiTRACE(" spi_state      %d\n", reg_byte[0]&0x07 );
    L0_ReadBytes(api->i2c, 0x55, 1, reg_byte); SiTRACE(" spi_crc_status %d\n", reg_byte[0]&0x01 );

    for (fw_index = 0; fw_index < 20; fw_index ++) {
      return_code = L0_LoadSPIoverGPIF(fw_table+fw_index,  1);
      L0_ReadBytes(api->i2c, 0x57, 1, reg_byte);  SiTRACE(" spi_state      %d\n", reg_byte[0]&0x07 );
    }
 #endif /* SPI_DEBUGGING */

    /* Send SPI bytes, using max available buffer size */
    for (i=0; i< num_split; i++) {
      if (split_list[i]-fw_index > api->spi_buffer_size) {
        return_code = L0_LoadSPIoverGPIF(fw_table+fw_index, split_list[i-1]-fw_index);
        fw_index = split_list[i-1];
      }
    }
     /* Send trailing SPI bytes */
    if (split_list[i-1]-fw_index > 0) {
      return_code = L0_LoadSPIoverGPIF(fw_table+fw_index, split_list[i-1]-fw_index);
    }

    api->spi_download_ms = system_time() - load_start_ms;
    SiTRACE ("L0_LoadSPIoverGPIF     took %4d ms\n", api->spi_download_ms);

 #ifdef    SPI_DEBUGGING
    L0_ReadBytes(api->i2c, 0x57, 1, reg_byte); SiTRACE(" spi_state      %d\n", reg_byte[0]&0x07 );
    L0_ReadBytes(api->i2c, 0x55, 1, reg_byte); SiTRACE(" spi_crc_status %d\n", reg_byte[0]&0x01 );

    api->i2c->indexSize  = 0;
    spi_bytes[0] = 0xfe; spi_bytes[1] = 0x00; L0_WriteBytes(api->i2c, 0x00, 2, spi_bytes);
 #endif /* SPI_DEBUGGING */

    if ( return_code != 0 )
    {
      SiTRACE("Si2183_LoadFirmwareSPI_Split  error 0x%02x loading %d bytes: %s\n", return_code, nbBytes, Si2183_L1_API_ERROR_TEXT(return_code) );
      SiERROR("Si2183_LoadFirmwareSPI_Split  error\n");
      return_code = ERROR_Si2183_LOADING_FIRMWARE;
    } else {
      /* Storing Properties startup configuration in propShadow                              */
      /* !! Do NOT change the content of Si2183_storePropertiesDefaults                   !! */
      /* !! It should reflect the part internal property settings after firmware download !! */
      SiTRACE ("Si2183_storePropertiesDefaults\n");
      Si2183_storePropertiesDefaults (api->propShadow);
      SiTRACE ("Si2183_LoadFirmwareSPI_Split complete...\n");
      return_code = NO_Si2183_ERROR;
    }

    Si2183_L1_SendCommand2(api, Si2183_SPI_LINK_CMD_CODE);

    L0_DisableSPI();

    return return_code;
}
#endif /* FW_DOWNLOAD_OVER_SPI */
/************************************************************************************************************************
  NAME: Si2183_StartFirmware
  DESCRIPTION: Start Si2183 firmware (put the Si2183 into run mode)
  Parameter:   Si2183 Context (I2C address)
  Parameter (passed by Reference):   ExitBootloadeer Response Status byte : tunint, atvint, dtvint, err, cts
  Returns:     I2C transaction error code, NO_Si2183_ERROR if successful
************************************************************************************************************************/
signed   int Si2183_StartFirmware       (L1_Si2183_Context *api)
{
    if (Si2183_L1_EXIT_BOOTLOADER(api, Si2183_EXIT_BOOTLOADER_CMD_FUNC_NORMAL, Si2183_EXIT_BOOTLOADER_CMD_CTSIEN_OFF) != NO_Si2183_ERROR)
    {
        return ERROR_Si2183_STARTING_FIRMWARE;
    }

    return NO_Si2183_ERROR;
}
/************************************************************************************************************************
  NAME: Si2183_Init
  DESCRIPTION:Reset and Initialize Si2183
  Parameter:  Si2183 Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2183_ERROR if successful
************************************************************************************************************************/
signed   int Si2183_Init                (L1_Si2183_Context *api)
{
    signed   int return_code;
    SiTRACE("Si2183_Init starting...\n");

    if ((return_code = Si2183_PowerUpWithPatch(api)) != NO_Si2183_ERROR) {   /* PowerUp into bootloader */
        SiTRACE ("Si2183_PowerUpWithPatch error 0x%02x: %s\n", return_code, Si2183_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }
    /* At this point, FW is loaded and started.  */
    Si2183_Configure(api);
    SiTRACE("Si2183_Init complete...\n");
    return NO_Si2183_ERROR;
}
/************************************************************************************************************************
  Si2183_Media function
  Use:        media retrieval function
              Used to retrieve the media used by the Si2183
************************************************************************************************************************/
signed   int Si2183_Media               (L1_Si2183_Context *api, signed   int modulation)
{
  switch (modulation) {
    case Si2183_DD_MODE_PROP_MODULATION_AUTO_DETECT : {
      switch (api->prop->dd_mode.auto_detect) {
        default             : break;
#ifdef    DEMOD_DVB_T
        case Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_T_T2     : return Si2183_TERRESTRIAL; break;
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_DVB_C2
 /*         case Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_C_C2     : return Si2183_TERRESTRIAL; break; */
#endif /* DEMOD_DVB_C2 */
#ifdef    DEMOD_DVB_S_S2_DSS
        case Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_S_S2     :
        case Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_S_S2_DSS : return Si2183_SATELLITE; break;
#endif /* DEMOD_DVB_S_S2_DSS */
      }
      break;
    }
#ifdef    DEMOD_DVB_T
    case Si2183_DD_MODE_PROP_MODULATION_DVBT : return Si2183_TERRESTRIAL; break;
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_DVB_T2
    case Si2183_DD_MODE_PROP_MODULATION_DVBT2: return Si2183_TERRESTRIAL; break;
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_ISDB_T
    case Si2183_DD_MODE_PROP_MODULATION_ISDBT: return Si2183_TERRESTRIAL; break;
#endif /* DEMOD_ISDB_T */
#ifdef    DEMOD_DVB_C
    case Si2183_DD_MODE_PROP_MODULATION_DVBC : return Si2183_TERRESTRIAL; break;
#endif /* DEMOD_DVB_C  */
#ifdef    DEMOD_DVB_C2
    case Si2183_DD_MODE_PROP_MODULATION_DVBC2: return Si2183_TERRESTRIAL; break;
#endif /* DEMOD_DVB_C2 */
#ifdef    DEMOD_MCNS
    case Si2183_DD_MODE_PROP_MODULATION_MCNS : return Si2183_TERRESTRIAL; break;
#endif /* DEMOD_MCNS */
    case Si2183_DD_MODE_PROP_MODULATION_ANALOG: return Si2183_TERRESTRIAL; break;
#ifdef    DEMOD_DVB_S_S2_DSS
    case Si2183_DD_MODE_PROP_MODULATION_DSS  :
    case Si2183_DD_MODE_PROP_MODULATION_DVBS :
    case Si2183_DD_MODE_PROP_MODULATION_DVBS2: return Si2183_SATELLITE; break;
#endif /* DEMOD_DVB_S_S2_DSS */
    default             : { break;}
  }
  SiTRACE("UNKNOWN media (modulation %d)!\n", modulation);
  return 0;
}
/************************************************************************************************************************
  Si2183_DVB_C_max_lock_ms function
  Use:        DVB-C lock time retrieval function
              Used to know how much time DVB-C lock will take in the worst case
************************************************************************************************************************/
signed   int Si2183_DVB_C_max_lock_ms   (L1_Si2183_Context *api, signed   int constellation, signed   int symbol_rate_baud)
{
#ifdef    DEMOD_DVB_C
  unsigned int   swt;
  signed   int   afc_khz;
  signed   int   swt_coeff;
  /* To avoid division by 0, return 5000 if SR is 0 */
  if (symbol_rate_baud == 0) return 5000;
  afc_khz = api->prop->dvbc_afc_range.range_khz;
  if (afc_khz*1000 > symbol_rate_baud*11/100 ) { afc_khz = symbol_rate_baud*11/100000;}
  switch (constellation) {
    case    Si2183_DVBC_CONSTELLATION_PROP_CONSTELLATION_QAM64  :
    case    Si2183_DVBC_CONSTELLATION_PROP_CONSTELLATION_QAM16  :
    case    Si2183_DVBC_CONSTELLATION_PROP_CONSTELLATION_QAM256 : { swt_coeff =  3; break; }
    case    Si2183_DVBC_CONSTELLATION_PROP_CONSTELLATION_QAM128 : { swt_coeff =  4; break; }
    case    Si2183_DVBC_CONSTELLATION_PROP_CONSTELLATION_AUTO   :
    default                                                     : { swt_coeff = 14; break; }
  }
  /* Step by step swt computing to avoid overflows/underflow over the possible SR and AFC ranges */
  swt  = 11184811/(symbol_rate_baud/10000);
  swt  = swt*afc_khz;
  swt  = swt/(symbol_rate_baud/10000);
  swt  = (swt/100) + 1;
  SiTRACE("symbol_rate_baud %8d, constellation %2d, afc_khz %3d, swt %6d, swt_coeff %2d DVB_C_max_lock_ms %d\n", symbol_rate_baud, constellation, afc_khz, swt, swt_coeff, (int)(720000000/symbol_rate_baud + swt*swt_coeff)+ 100 );
  return (int)(720000000/symbol_rate_baud + swt*swt_coeff)+ 100;
#endif /* DEMOD_DVB_C */
  /* To avoid compilation error when not compiling for DVB_C */
  constellation = symbol_rate_baud = 5000;
  return constellation;
}
/*****************************************************************************************/
/*               SiLabs demodulator API functions (demod and tuner)                      */
/*****************************************************************************************/
/* Allow profiling information during Si2183_switch_to_standard */
#define PROFILING
/************************************************************************************************************************
  Si2183_standardName function
  Use:        standard text retrieval function
              Used to retrieve the standard text used by the Si2183
  Parameter:  standard, the value of the standard
************************************************************************************************************************/
char *Si2183_standardName (int standard)
{
  switch (standard)
  {
#ifdef    DEMOD_DVB_T
    case Si2183_DD_MODE_PROP_MODULATION_DVBT    : {return (char*)"DVB-T"  ;}
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_ISDB_T
    case Si2183_DD_MODE_PROP_MODULATION_ISDBT   : {return (char*)"ISDB-T"  ;}
#endif /* DEMOD_ISDB_T */
#ifdef    DEMOD_DVB_C
    case Si2183_DD_MODE_PROP_MODULATION_MCNS    : {return (char*)"MCNS"   ;}
    case Si2183_DD_MODE_PROP_MODULATION_DVBC    : {return (char*)"DVB-C"  ;}
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_C2
    case Si2183_DD_MODE_PROP_MODULATION_DVBC2   : {return (char*)"DVB-C2" ;}
#endif /* DEMOD_DVB_C2 */
#ifdef    DEMOD_DVB_T2
    case Si2183_DD_MODE_PROP_MODULATION_DVBT2   : {return (char*)"DVB-T2" ;}
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_DVB_S_S2_DSS
    case Si2183_DD_MODE_PROP_MODULATION_DVBS    : {return (char*)"DVB-S"  ;}
    case Si2183_DD_MODE_PROP_MODULATION_DVBS2   : {return (char*)"DVB-S2" ;}
    case Si2183_DD_MODE_PROP_MODULATION_DSS     : {return (char*)"DSS"    ;}
#endif /* DEMOD_DVB_S_S2_DSS */
    case Si2183_DD_MODE_PROP_MODULATION_ANALOG  : {return (char*)"ANALOG" ;}
    default                                     : {return (char*)"UNKNOWN";}
  }
}

/* Re-definition of SiTRACE for Si2183_L2_Context */
#ifdef    SiTRACES
  #undef  SiTRACE
  #define SiTRACE(...)        SiTraceFunction(SiLEVEL, front_end->demod->i2c->tag, __FILE__, __LINE__, __func__     ,__VA_ARGS__)
#endif /* SiTRACES */
/************************************************************************************************************************
  Si2183_prepare_DD_MODE function
************************************************************************************************************************/
signed   int  Si2183_prepare_DD_MODE       (Si2183_L2_Context *front_end, signed   int standard)
{
  front_end->demod->prop->dd_mode.auto_detect   = Si2183_DD_MODE_PROP_AUTO_DETECT_NONE;
#ifdef    TERRESTRIAL_FRONT_END
#ifdef    DEMOD_DVB_T2
  if (front_end->auto_detect_TER) { Si2183_TerAutoDetect(front_end); }
  SiTRACE("   Si2183_prepare_DD_MODE auto_detect_TER %d\n", front_end->auto_detect_TER);
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_DVB_C
  if ( standard == Si2183_DD_MODE_PROP_MODULATION_DVBC ) {
    front_end->demod->prop->dd_mode.modulation      = standard;
  }
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_MCNS
  if ( standard == Si2183_DD_MODE_PROP_MODULATION_MCNS ) {
    front_end->demod->prop->dd_mode.modulation      = standard;
  }
#endif /* DEMOD_MCNS */
#ifdef    DEMOD_DVB_C2
  if ( standard == Si2183_DD_MODE_PROP_MODULATION_DVBC2 ) {
    front_end->demod->prop->dd_mode.modulation      = standard;
  }
#endif /* DEMOD_DVB_C2 */
#ifdef    DEMOD_DVB_T
  if ( standard == Si2183_DD_MODE_PROP_MODULATION_DVBT ) {
    front_end->demod->prop->dd_mode.modulation      = standard;
  }
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_ISDB_T
  if ( standard == Si2183_DD_MODE_PROP_MODULATION_ISDBT ) {
    front_end->demod->prop->dd_mode.modulation      = standard;
  }
#endif /* DEMOD_ISDB_T */
#ifdef    DEMOD_DVB_T2
  if ((standard == Si2183_DD_MODE_PROP_MODULATION_DVBT) || (standard == Si2183_DD_MODE_PROP_MODULATION_DVBT2)) {
    if ( front_end->auto_detect_TER == 0 ) {
      front_end->demod->prop->dd_mode.modulation    = standard;
    }
    if ( front_end->auto_detect_TER == 1 ) {
      front_end->demod->prop->dd_mode.modulation    = Si2183_DD_MODE_PROP_MODULATION_AUTO_DETECT;
      front_end->demod->prop->dd_mode.auto_detect   = Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_T_T2;
    }
  }
#endif /* DEMOD_DVB_T2 */
#endif /* TERRESTRIAL_FRONT_END */

#ifdef    SATELLITE_FRONT_END
  SiTRACE("   Si2183_prepare_DD_MODE auto_detect_SAT %d\n", front_end->auto_detect_SAT);
  if ( front_end->auto_detect_SAT == 0 ) {
    if ( standard == Si2183_DD_MODE_PROP_MODULATION_DVBS ) {
      front_end->demod->prop->dd_mode.modulation      = standard;
    }
    if ( standard == Si2183_DD_MODE_PROP_MODULATION_DVBS2 ) {
      front_end->demod->prop->dd_mode.modulation      = standard;
    }
    if ( standard == Si2183_DD_MODE_PROP_MODULATION_DSS ) {
      front_end->demod->prop->dd_mode.modulation      = standard;
    }
  }
  if ( front_end->auto_detect_SAT == 1 ) {
    if ( standard == Si2183_DD_MODE_PROP_MODULATION_DSS ) {
    front_end->demod->prop->dd_mode.modulation      = Si2183_DD_MODE_PROP_MODULATION_AUTO_DETECT;
    front_end->demod->prop->dd_mode.auto_detect     = Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_S_S2_DSS;
    } else if ((standard == Si2183_DD_MODE_PROP_MODULATION_DVBS ) || (standard == Si2183_DD_MODE_PROP_MODULATION_DVBS2)) {
    front_end->demod->prop->dd_mode.modulation      = Si2183_DD_MODE_PROP_MODULATION_AUTO_DETECT;
    front_end->demod->prop->dd_mode.auto_detect     = Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_S_S2;
    }
  }
#endif /* SATELLITE_FRONT_END */
  SiTRACE("   Si2183_prepare_DD_MODE standard %d (%s) -> dd_mode.auto_detect %3d, dd_mode.modulation %3d \n", standard, Si2183_standardName(standard), front_end->demod->prop->dd_mode.auto_detect, front_end->demod->prop->dd_mode.modulation);
  return (front_end->demod->prop->dd_mode.auto_detect*100) + front_end->demod->prop->dd_mode.modulation;
}
/************************************************************************************************************************
  Si2183_L2_Infos function
  Use:        software information function
              Used to retrieve information about the compilation
  Parameter:  front_end, a pointer to the Si2183_L2_Context context to be initialized
  Parameter:  infoString, a text buffer to be filled with the information.
              It must be initialized by the caller with a size of 1000.
  Return:     the length of the information string
************************************************************************************************************************/
signed   int  Si2183_L2_Infos              (Si2183_L2_Context *front_end, char *infoString)
{
    if (infoString == NULL) return 0;
    if (front_end  == NULL) {
      snprintf(infoString,1000, "Si2183 front-end not initialized yet. Call Si2183_L2_SW_Init first!\n");
      return strlen(infoString);
    }

    snprintf(infoString,1000, "\n");
    STRING_APPEND_SAFE(infoString,1000, "--------------------------------------\n");
    STRING_APPEND_SAFE(infoString,1000, "Si_I2C               Source code %s\n" , Si_I2C_TAG_TEXT() );
    STRING_APPEND_SAFE(infoString,1000, "Demod                Si2183  at 0x%02x\n", front_end->demod->i2c->address);
    STRING_APPEND_SAFE(infoString,1000, "Demod                Source code %s\n"   , Si2183_L1_API_TAG_TEXT() );
#ifdef    TERRESTRIAL_FRONT_END
#ifdef    TER_TUNER_SILABS
    STRING_APPEND_SAFE(infoString,1000, "Terrestrial tuner    SiLabs    at 0x%02x\n", front_end->tuner_ter->i2c->address);
#endif /* TER_TUNER_SILABS */
#ifdef    TER_TUNER_CUSTOMTER
    STRING_APPEND_SAFE(infoString,1000, "Terrestrial tuner    CUSTOMTER  at 0x%02x\n", front_end->tuner_ter->i2c->address);
#endif /* TER_TUNER_CUSTOMTER */
#ifdef    TER_TUNER_NO_TER
    STRING_APPEND_SAFE(infoString,1000, "Terrestrial tuner    NO_TER  at 0x%02x\n", front_end->tuner_ter->i2c->address);
#endif /* TER_TUNER_NO_TER */
#ifdef    TER_TUNER_TAG_TEXT
    STRING_APPEND_SAFE(infoString,1000, "Terrestrial tuner    Source code %s\n"   , TER_TUNER_TAG_TEXT() );
#endif /* TER_TUNER_TAG_TEXT */
#endif /* TERRESTRIAL_FRONT_END */

#ifdef    DEMOD_DVB_S_S2_DSS
/* At project level, define the SAT_TUNER_xxxxxx value corresponding to the required terrestrial tuner */
#ifdef    SAT_TUNER_SILABS
    STRING_APPEND_SAFE(infoString,1000, "Satellite tuner via SiLabs_SAT_Tuner at 0x%02x\n", front_end->tuner_sat->i2c->address);
#endif /* SAT_TUNER_SILABS */
#endif /* DEMOD_DVB_S_S2_DSS */

#ifdef    TERRESTRIAL_FRONT_END
  if ( front_end->demod->tuner_ter_clock_source == Si2183_TER_Tuner_clock) STRING_APPEND_SAFE(infoString,1000, "TER clock from  TER Tuner ");
  if ( front_end->demod->tuner_ter_clock_source == Si2183_SAT_Tuner_clock) STRING_APPEND_SAFE(infoString,1000, "TER clock from  SAT Tuner ");
  if ( front_end->demod->tuner_ter_clock_source == Si2183_Xtal_clock     ) STRING_APPEND_SAFE(infoString,1000, "TER clock from  Xtal      ");
                                                                           STRING_APPEND_SAFE(infoString,1000, "(%d MHz)\n", front_end->demod->tuner_ter_clock_freq);
  if ( front_end->demod->tuner_ter_clock_input  == Si2183_START_CLK_CMD_CLK_MODE_CLK_CLKIO  ) STRING_APPEND_SAFE(infoString,1000, "TER clock input CLKIO\n"  );
  if ( front_end->demod->tuner_ter_clock_input  == Si2183_START_CLK_CMD_CLK_MODE_CLK_XTAL_IN) STRING_APPEND_SAFE(infoString,1000, "TER clock input XTAL_IN\n");
  if ( front_end->demod->tuner_ter_clock_input  == Si2183_START_CLK_CMD_CLK_MODE_XTAL       ) STRING_APPEND_SAFE(infoString,1000, "TER clock input XTAL\n"   );

#ifdef    DEMOD_DVB_T2
  if (front_end->demod->fef_mode                 == Si2183_FEF_MODE_SLOW_NORMAL_AGC          ) STRING_APPEND_SAFE(infoString,1000, "FEF mode 'SLOW NORMAL AGC'"  );
  if (front_end->demod->fef_mode                 == Si2183_FEF_MODE_SLOW_INITIAL_AGC         ) STRING_APPEND_SAFE(infoString,1000, "FEF mode 'SLOW INITIAL AGC'" );
  if (front_end->demod->fef_mode                 == Si2183_FEF_MODE_FREEZE_PIN               ) STRING_APPEND_SAFE(infoString,1000, "FEF mode 'FREEZE PIN'"       );
  if (front_end->demod->fef_mode                 == Si2183_FEF_MODE_TUNER_AUTO_FREEZE        ) STRING_APPEND_SAFE(infoString,1000, "FEF mode 'TUNER AUTO FREEZE'");
  if (front_end->demod->fef_mode                 != front_end->demod->fef_selection          ) STRING_APPEND_SAFE(infoString,1000, "(CHANGED!)"                  );
#endif /* DEMOD_DVB_T2 */
  STRING_APPEND_SAFE(infoString,1000, "\n");
#endif /* TERRESTRIAL_FRONT_END */

#ifdef    DEMOD_DVB_S_S2_DSS
  if ( front_end->demod->tuner_sat_clock_source == Si2183_TER_Tuner_clock) STRING_APPEND_SAFE(infoString,1000, "SAT clock from  TER Tuner ");
  if ( front_end->demod->tuner_sat_clock_source == Si2183_SAT_Tuner_clock) STRING_APPEND_SAFE(infoString,1000, "SAT clock from  SAT Tuner ");
  if ( front_end->demod->tuner_sat_clock_source == Si2183_Xtal_clock     ) STRING_APPEND_SAFE(infoString,1000, "SAT clock from  Xtal      ");
                                                                           STRING_APPEND_SAFE(infoString,1000, "(%d MHz)\n", front_end->demod->tuner_sat_clock_freq);
  if ( front_end->demod->tuner_sat_clock_input  == Si2183_START_CLK_CMD_CLK_MODE_CLK_CLKIO  ) STRING_APPEND_SAFE(infoString,1000, "SAT clock input CLKIO\n"  );
  if ( front_end->demod->tuner_sat_clock_input  == Si2183_START_CLK_CMD_CLK_MODE_CLK_XTAL_IN) STRING_APPEND_SAFE(infoString,1000, "SAT clock input XTAL_IN\n");
  if ( front_end->demod->tuner_sat_clock_input  == Si2183_START_CLK_CMD_CLK_MODE_XTAL       ) STRING_APPEND_SAFE(infoString,1000, "SAT clock input XTAL\n"   );
  #ifdef    UNICABLE_COMPATIBLE
  STRING_APPEND_SAFE(infoString,1000, "Compiled with UNICABLE compatibility\n");
  if (front_end->lnb_type == UNICABLE_LNB_TYPE_UNICABLE) {
    STRING_APPEND_SAFE(infoString,1000, "UNICABLE LNB installed\n"    );
  } else {
    STRING_APPEND_SAFE(infoString,1000, "UNICABLE LNB not installed\n");
  }
  #endif /* UNICABLE_COMPATIBLE */
#endif /* DEMOD_DVB_S_S2_DSS */

  STRING_APPEND_SAFE(infoString,1000, "--------------------------------------\n");
  return strlen(infoString);
}
/************************************************************************************************************************
  Si2183_L2_SW_Init function
  Use:        software initialization function
              Used to initialize the Si2183 and tuner structures
  Behavior:   This function performs all the steps necessary to initialize the Si2183 and tuner instances
  Parameter:  front_end, a pointer to the Si2183_L2_Context context to be initialized
  Parameter:  demodAdd, the I2C address of the demod
  Parameter:  tunerAdd, the I2C address of the tuner
  Comments:     It MUST be called first and once before using any other function.
                It can be used to build a multi-demod/multi-tuner application, if called several times from the upper layer with different pointers and addresses
                After execution, all demod and tuner functions are accessible.
************************************************************************************************************************/
char          Si2183_L2_SW_Init            (Si2183_L2_Context *front_end
                                   , signed   int demodAdd
#ifdef    TERRESTRIAL_FRONT_END
                                   , signed   int tunerAdd_Ter
 #ifdef    INDIRECT_I2C_CONNECTION
                                   , Si2183_INDIRECT_I2C_FUNC           TER_tuner_enable_func
                                   , Si2183_INDIRECT_I2C_FUNC           TER_tuner_disable_func
 #endif /* INDIRECT_I2C_CONNECTION */
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
                                   , signed   int tunerAdd_Sat
#ifdef    UNICABLE_COMPATIBLE
                                   , Si2183_WRAPPER_TUNER_TUNE_FUNC     tuner_tune
                                   , Si2183_WRAPPER_UNICABLE_TUNE_FUNC  unicable_tune
#endif /* UNICABLE_COMPATIBLE */
 #ifdef    INDIRECT_I2C_CONNECTION
                                   , Si2183_INDIRECT_I2C_FUNC           SAT_tuner_enable_func
                                   , Si2183_INDIRECT_I2C_FUNC           SAT_tuner_disable_func
 #endif /* INDIRECT_I2C_CONNECTION */
#endif /* SATELLITE_FRONT_END */
                                   , void *p_context
                                   )
{
    SiTRACE_X("Si2183_L2_SW_Init starting...\n");

    /* Pointers initialization */
    front_end->demod     = &(front_end->demodObj    );
    front_end->Si2183_init_done    = 0;
    front_end->first_init_done     = 0;
    front_end->handshakeUsed       = 0; /* set to '0' by default for compatibility with previous versions */
    front_end->handshakeOn         = 0;
    front_end->handshakePeriod_ms  = 1000;
#ifdef    TERRESTRIAL_FRONT_END
    front_end->tuner_ter = &(front_end->tuner_terObj);
    front_end->TER_init_done        = 0;
    front_end->TER_tuner_init_done  = 0;
    front_end->TER_tuner_config_done= 0;
    front_end->auto_detect_TER      = 1;
 #ifdef    INDIRECT_I2C_CONNECTION
    front_end->f_TER_tuner_enable  = TER_tuner_enable_func;
    front_end->f_TER_tuner_disable = TER_tuner_disable_func;
 #endif /* INDIRECT_I2C_CONNECTION */
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
    front_end->tuner_sat = &(front_end->tuner_satObj);
    front_end->SAT_init_done       = 0;
    front_end->SAT_tuner_init_done = 0;
    front_end->previous_standard   = 0;
    front_end->auto_detect_SAT     = 1;
 #ifdef    INDIRECT_I2C_CONNECTION
    front_end->f_SAT_tuner_enable  = SAT_tuner_enable_func;
    front_end->f_SAT_tuner_disable = SAT_tuner_disable_func;
 #endif /* INDIRECT_I2C_CONNECTION */
#endif /* SATELLITE_FRONT_END */
    /* Calling underlying SW initialization functions */
    Si2183_L1_API_Init      (front_end->demod,     demodAdd);
#ifdef    TERRESTRIAL_FRONT_END
    L1_RF_TER_TUNER_Init    (front_end->tuner_ter, tunerAdd_Ter);
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
    L1_RF_SAT_TUNER_Init    (front_end->tuner_sat, tunerAdd_Sat);
    front_end->satellite_spectrum_inversion = 0;
#ifdef    UNICABLE_COMPATIBLE
    front_end->lnb_type        = UNICABLE_LNB_TYPE_NORMAL;
    front_end->unicable_spectrum_inversion = 1;
    front_end->f_tuner_tune    = tuner_tune;
    front_end->f_Unicable_tune = unicable_tune;
#endif /* UNICABLE_COMPATIBLE */
#endif /* SATELLITE_FRONT_END */
    front_end->callback        = p_context;
#ifdef    SiTRACE
    if (Si2183_L2_Infos(front_end, front_end->demod->msg))  {SiTRACE("%s\n", front_end->demod->msg);}
#endif /* SiTRACE */
    /* <porting> Set here the capacitance value when using a Xtal (this depends on the HW design)                                               */
    /* <porting> This can be overwritten later-on using SiLabs_API_XTAL_Capacitance in case several HW configuration require different settings */
    front_end->demod->cmd->start_clk.tune_cap = Si2183_START_CLK_CMD_TUNE_CAP_15P6;

    front_end->demod->nbLines = 0;
    front_end->demod->fw_table = NULL;
    front_end->demod->nbSpiBytes = 0;
    front_end->demod->spi_table = NULL;
    front_end->demod->spi_buffer_size = 2048;  /* Needs to be at least 1024 for the current FW portions. Contact SiLabs in case you need a smaller size */
    /* <porting> if not allowed to use dynamic memory allocation, comment the following lines. */
    front_end->demod->fw_table = (firmware_struct*)realloc(front_end->demod->fw_table , sizeof(firmware_struct)*front_end->demod->nbLines);
    front_end->demod->spi_table = (unsigned char *)realloc(front_end->demod->spi_table, sizeof(unsigned char)*front_end->demod->nbSpiBytes);
    front_end->misc_infos = 0x00100000; /* trylock traced*/
    /* <porting> end of dynamic memory allocation */
    SiTRACE("Si2183_L2_SW_Init complete\n");
    return 1;
}
/************************************************************************************************************************
  Si2183_L2_Set_Index_and_Tag function
  Use:        Front-End index and tag function
              Used to store the frontend index and tag, which will be used in traces called from L2 level
              Behavior:   It will store the front_end index and tag in the Si2183_L2_Context demod->i2c, adding 'DTV' to the tag
              Behavior:   It will store the front_end index and tag in the Si2183_L2_Context tuner_ter->i2c, adding 'TER' to the tag
              Behavior:   It will store the front_end index and tag in the Si2183_L2_Context tuner_sat->i2c, adding 'SAT' to the tag
  Parameter:  front_end, a pointer to the SILABS_FE_Context context
  Parameter:  index, the frontend index
  Parameter:  tag,   the frontend tag (a string limited to SILABS_TAG_SIZE characters)
  Return:     the length of the demod->i2c->tag
************************************************************************************************************************/
signed   int  Si2183_L2_Set_Index_and_Tag  (Si2183_L2_Context *front_end, unsigned char index, const char* tag)
{
  front_end->demod->i2c->tag_index = index;
  snprintf(front_end->demod->i2c->tag,     SILABS_TAG_SIZE, "%s DTV", tag);
#ifdef    TERRESTRIAL_FRONT_END
  snprintf(front_end->tuner_ter->i2c->tag, SILABS_TAG_SIZE, "%s TER", tag);
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
  snprintf(front_end->tuner_sat->i2c->tag, SILABS_TAG_SIZE, "%s SAT", tag);
#endif /* SATELLITE_FRONT_END */
  return strlen(front_end->demod->i2c->tag);
}
/************************************************************************************************************************
  NAME: Si2183_L2_SILENT
  DESCRIPTION: Turning Demod pins tristate, to allow using another demod
  Parameter:  Pointer to Si2183 Context
  Parameter:  silent, a flag used to select the result: '1' -> go silent, '0' -> return to active mode
  Returns:    I2C transaction error code, NO_Si2183_ERROR if successful
************************************************************************************************************************/
signed   int  Si2183_L2_SILENT             (Si2183_L2_Context *front_end, signed   int silent)
{
  SiTRACE ("Si2183_L2_SILENT: silent %d\n", silent);
  if (silent) {
    /* turn all possible I/Os to tristate, to allow using another demod */
    /* AGC settings when not used */
    if        ( front_end->demod->rsp->get_rev.mcm_die == Si2183_GET_REV_RESPONSE_MCM_DIE_DIE_A) {
      Si2183_L1_DD_MP_DEFAULTS(front_end->demod, Si2183_DD_MP_DEFAULTS_CMD_MP_A_MODE_DISABLE  , Si2183_DD_MP_DEFAULTS_CMD_MP_B_MODE_NO_CHANGE
                                               , Si2183_DD_MP_DEFAULTS_CMD_MP_C_MODE_DISABLE  , Si2183_DD_MP_DEFAULTS_CMD_MP_D_MODE_NO_CHANGE);
    } else if ( front_end->demod->rsp->get_rev.mcm_die == Si2183_GET_REV_RESPONSE_MCM_DIE_DIE_B) {
      Si2183_L1_DD_MP_DEFAULTS(front_end->demod, Si2183_DD_MP_DEFAULTS_CMD_MP_A_MODE_NO_CHANGE, Si2183_DD_MP_DEFAULTS_CMD_MP_B_MODE_DISABLE
                                               , Si2183_DD_MP_DEFAULTS_CMD_MP_C_MODE_NO_CHANGE, Si2183_DD_MP_DEFAULTS_CMD_MP_D_MODE_DISABLE);
    } else {
      Si2183_L1_DD_MP_DEFAULTS(front_end->demod, Si2183_DD_MP_DEFAULTS_CMD_MP_A_MODE_DISABLE  , Si2183_DD_MP_DEFAULTS_CMD_MP_B_MODE_DISABLE
                                               , Si2183_DD_MP_DEFAULTS_CMD_MP_C_MODE_DISABLE  , Si2183_DD_MP_DEFAULTS_CMD_MP_D_MODE_DISABLE);
    }
#ifdef    TERRESTRIAL_FRONT_END
    Si2183_L1_DD_EXT_AGC_TER(front_end->demod, Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MODE_NOT_USED,     front_end->demod->cmd->dd_ext_agc_ter.agc_1_inv
                                             , Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_NOT_USED,     front_end->demod->cmd->dd_ext_agc_ter.agc_2_inv
                                             , front_end->demod->cmd->dd_ext_agc_ter.agc_1_kloop, front_end->demod->cmd->dd_ext_agc_ter.agc_2_kloop
                                             , front_end->demod->cmd->dd_ext_agc_ter.agc_1_min  , front_end->demod->cmd->dd_ext_agc_ter.agc_2_min);
    front_end->TER_init_done = 0;
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
    Si2183_L1_DD_EXT_AGC_SAT(front_end->demod, Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_NOT_USED,     front_end->demod->cmd->dd_ext_agc_sat.agc_1_inv
                                             , Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MODE_NOT_USED,     front_end->demod->cmd->dd_ext_agc_sat.agc_2_inv
                                             , front_end->demod->cmd->dd_ext_agc_sat.agc_1_kloop, front_end->demod->cmd->dd_ext_agc_sat.agc_2_kloop
                                             , front_end->demod->cmd->dd_ext_agc_sat.agc_1_min  , front_end->demod->cmd->dd_ext_agc_sat.agc_2_min);
    front_end->SAT_init_done = 0;
#endif /* SATELLITE_FRONT_END */
    if        ( front_end->demod->rsp->get_rev.mcm_die == Si2183_GET_REV_RESPONSE_MCM_DIE_DIE_A) {
      Si2183_L1_CONFIG_PINS   (front_end->demod, Si2183_CONFIG_PINS_CMD_GPIO0_MODE_NO_CHANGE, Si2183_CONFIG_PINS_CMD_GPIO0_READ_DO_NOT_READ
                                               , Si2183_CONFIG_PINS_CMD_GPIO1_MODE_DISABLE  , Si2183_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ);
    } else if ( front_end->demod->rsp->get_rev.mcm_die == Si2183_GET_REV_RESPONSE_MCM_DIE_DIE_B) {
      Si2183_L1_CONFIG_PINS   (front_end->demod, Si2183_CONFIG_PINS_CMD_GPIO0_MODE_DISABLE  , Si2183_CONFIG_PINS_CMD_GPIO0_READ_DO_NOT_READ
                                               , Si2183_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE, Si2183_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ);
    } else {
      Si2183_L1_CONFIG_PINS   (front_end->demod, Si2183_CONFIG_PINS_CMD_GPIO0_MODE_DISABLE  , Si2183_CONFIG_PINS_CMD_GPIO0_READ_DO_NOT_READ
                                               , Si2183_CONFIG_PINS_CMD_GPIO1_MODE_DISABLE  , Si2183_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ);
    }
    /* turn TS pins to tristate */
    front_end->demod->prop->dd_ts_mode.mode =  Si2183_DD_TS_MODE_PROP_MODE_TRISTATE;
    Si2183_L1_SetProperty2  (front_end->demod, Si2183_DD_TS_MODE_PROP_CODE);
    Si2183_L1_DD_RESTART    (front_end->demod);
    system_wait(8); /* Wait at least 8 ms before issuing POWER_DOWN, to make sure that the AGCs are in tristate. */
  } else {
    /* return to 'active mode' (it will be necessary to turn TS on again after locking) */
    Si2183_WAKEUP        (front_end->demod);
    Si2183_Configure     (front_end->demod);
  }
  return silent;
}
/************************************************************************************************************************
  Si2183_L2_HW_Connect function
  Use:        Front-End connection function
              Specific to SiLabs USB connection!
  Porting:    Remove or replace by the final application corresponding calls
  Behavior:   This function connects the Si2183, and the tuners via the Cypress chip
  Parameter:  *front_end, the front-end handle
  Parameter   mode, the required connection mode
************************************************************************************************************************/
void          Si2183_L2_HW_Connect         (Si2183_L2_Context *front_end, CONNECTION_TYPE mode)
{
    L0_Connect(front_end->demod->i2c,    mode);
#ifdef    TERRESTRIAL_FRONT_END
    L0_Connect(front_end->tuner_ter->i2c,mode);
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
    L0_Connect(front_end->tuner_sat->i2c,mode);
#endif /* SATELLITE_FRONT_END */
}
/************************************************************************************************************************
  NAME: Si2183_L2_Part_Check
  DESCRIPTION:startup and part checking Si2183
  Parameter:  Si2183 Context
  Returns:    the part_info 'part' field value
************************************************************************************************************************/
signed   int  Si2183_L2_Part_Check         (Si2183_L2_Context *front_end)
{
  signed   int start_time_ms;
  front_end->demod->rsp->part_info.part = 0;
  start_time_ms = system_time();
  front_end->demod->cmd->power_up.reset = Si2183_POWER_UP_CMD_RESET_RESET;
  front_end->demod->cmd->power_up.func  = Si2183_POWER_UP_CMD_FUNC_BOOTLOADER;
#ifdef    SiTRACES
    SiTraceConfiguration("traces suspend");
#endif /* SiTRACES */
  Si2183_WAKEUP      (front_end->demod);
  Si2183_L1_PART_INFO(front_end->demod);
#ifdef    SiTRACES
  SiTraceConfiguration("traces resume");
#endif /* SiTRACES */
  SiTRACE("Si2183_Part_Check took %3d ms. Part is Si21%2d\n", system_time() - start_time_ms, front_end->demod->rsp->part_info.part );
  return front_end->demod->rsp->part_info.part;
}
/************************************************************************************************************************
  Si2183_L2_Tuner_I2C_Enable function
  Use:        Tuner i2c bus connection
              Used to allow communication with the tuners
  Parameter:  *front_end, the front-end handle
************************************************************************************************************************/
unsigned char Si2183_L2_Tuner_I2C_Enable   (Si2183_L2_Context *front_end)
{
    return Si2183_L1_I2C_PASSTHROUGH(front_end->demod, Si2183_I2C_PASSTHROUGH_CMD_SUBCODE_CODE, Si2183_I2C_PASSTHROUGH_CMD_I2C_PASSTHRU_CLOSE, Si2183_I2C_PASSTHROUGH_CMD_RESERVED_RESERVED);
}
/************************************************************************************************************************
  Si2183_L2_Tuner_I2C_Disable function
  Use:        Tuner i2c bus connection
              Used to disconnect i2c communication with the tuners
  Parameter:  *front_end, the front-end handle
************************************************************************************************************************/
unsigned char Si2183_L2_Tuner_I2C_Disable  (Si2183_L2_Context *front_end)
{
    return Si2183_L1_I2C_PASSTHROUGH(front_end->demod, Si2183_I2C_PASSTHROUGH_CMD_SUBCODE_CODE, Si2183_I2C_PASSTHROUGH_CMD_I2C_PASSTHRU_OPEN, Si2183_I2C_PASSTHROUGH_CMD_RESERVED_RESERVED);
}
/************************************************************************************************************************
  Si2183_L2_communication_check function
  Use:        Si2183 front i2c bus connection check
              Used to check i2c communication with the demod and the tuners
  Parameter:  *front_end, the front-end handle
************************************************************************************************************************/
signed   int  Si2183_L2_communication_check(Si2183_L2_Context *front_end)
{
  signed   int comm_errors;
  comm_errors=0;
  /* Close i2c Passthru       */
  Si2183_L2_Tuner_I2C_Enable(front_end);
  /* Check i2c Passthru value */
  if ((int)Si2183_L1_CheckStatus(front_end->demod) != NO_Si2183_ERROR) {
    SiTRACE ("DEMOD Communication error ! \n");
    comm_errors++;
  } else {
    SiTRACE ("DEMOD Communication OK\n");
  }
#ifdef    DEMOD_DVB_T
 #ifdef    INDIRECT_I2C_CONNECTION
  front_end->f_TER_tuner_enable(front_end->callback);
 #endif /* INDIRECT_I2C_CONNECTION */
  /* Check TER tuner read     */
    #ifdef    TER_TUNER_COMM_CHECK
  if (TER_TUNER_COMM_CHECK(front_end->tuner_ter) !=1) {
    SiTRACE ("TER tuner Communication error ! \n");
    comm_errors++;
  } else {
    SiTRACE ("TER tuner Communication OK\n");
  }
    #endif /* TER_TUNER_COMM_CHECK */
#endif /* DEMOD_DVB_T */

#ifdef    DEMOD_DVB_S_S2_DSS
 #ifdef    INDIRECT_I2C_CONNECTION
  front_end->f_SAT_tuner_enable(front_end->callback);
 #endif /* INDIRECT_I2C_CONNECTION */
  /* Check SAT tuner read     */
    #ifdef    SAT_TUNER_COMM_CHECK
  if (SAT_TUNER_COMM_CHECK(front_end->tuner_sat) !=1) {
    SiTRACE ("SAT tuner Communication error ! \n");
    comm_errors++;
    comm_errors--; /* This is a trick to avoid returning an error and thus stopping the standard switching */
                   /* It needs to be removed once the RDA5815 can be read back                             */
  } else {
    SiTRACE ("SAT tuner Communication OK\n");
  }
    #endif /* SAT_TUNER_COMM_CHECK */
#endif /* DEMOD_DVB_S_S2_DSS */

  /* Open  i2c Passthru       */
 #ifdef    INDIRECT_I2C_CONNECTION
#ifdef    DEMOD_DVB_T
  front_end->f_TER_tuner_disable(front_end->callback);
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_DVB_S_S2_DSS
  front_end->f_SAT_tuner_disable(front_end->callback);
#endif /* DEMOD_DVB_S_S2_DSS */
 #endif /* INDIRECT_I2C_CONNECTION */
  Si2183_L2_Tuner_I2C_Disable(front_end);

  if (comm_errors) return 0;

  return 1;
}
/************************************************************************************************************************
  Si2183_L2_switch_to_standard function
  Use:      Standard switching function selection
            Used to switch nicely to the wanted standard, taking into account the previous state
  Parameter: new_standard the wanted standard to switch to
  Behavior: This function positions a set of flags to easily decide what needs to be done to
              switch between standards.
************************************************************************************************************************/
signed   int  Si2183_L2_switch_to_standard (Si2183_L2_Context *front_end, unsigned char new_standard, unsigned char force_full_init)
{
  #ifdef    INDIRECT_I2C_CONNECTION
  #ifdef    TERRESTRIAL_FRONT_END
  signed   int ter_i2c_connected      = 0;
  #endif /* TERRESTRIAL_FRONT_END */
  #ifdef    SATELLITE_FRONT_END
  signed   int sat_i2c_connected      = 0;
  #endif /* SATELLITE_FRONT_END */
  #else  /* INDIRECT_I2C_CONNECTION */
  signed   int i2c_connected          = 0;
  #endif /* INDIRECT_I2C_CONNECTION */

  signed   int dtv_demod_already_used = 0;
  signed   int dtv_demod_needed       = 0;
  signed   int dtv_demod_state        = 0;
  signed   int input_standard         = 0;
#ifdef    TERRESTRIAL_FRONT_END
  signed   int ter_tuner_already_used = 0;
  signed   int ter_clock_already_used = 0;
  signed   int ter_tuner_needed       = 0;
  signed   int ter_clock_needed       = 0;
  signed   int ter_tuner_state        = 0;
  signed   int ter_clock_state        = 0;
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
  signed   int sat_tuner_already_used = 0;
  signed   int sat_clock_already_used = 0;
  signed   int sat_tuner_needed       = 0;
  signed   int sat_clock_needed       = 0;
  signed   int sat_tuner_state        = 0;
  signed   int sat_clock_state        = 0;
#endif /* SATELLITE_FRONT_END */

  signed   int dtv_demod_sleep_request= 0;
  signed   int dtv_demod_sleeping     = 0;
  signed   int res;
  signed   int ret;

#ifdef    PROFILING
  signed   int start;
#ifdef    TERRESTRIAL_FRONT_END
  signed   int ter_tuner_delay   = 0;
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
  signed   int sat_tuner_delay   = 0;
#endif /* SATELLITE_FRONT_END */
  signed   int dtv_demod_delay   = 0;
  signed   int switch_start;
  char *sequence;
  sequence = front_end->demod->msg;
#ifdef    TERRESTRIAL_FRONT_END
  #define TER_DELAY  ter_tuner_delay=ter_tuner_delay+system_time()-start;start=system_time();
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
  #define SAT_DELAY  sat_tuner_delay=sat_tuner_delay+system_time()-start;start=system_time();
#endif /* SATELLITE_FRONT_END */
  #define DTV_DELAY  dtv_demod_delay=dtv_demod_delay+system_time()-start;start=system_time();
#else
#ifdef    TERRESTRIAL_FRONT_END
  #define TER_DELAY
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
  #define SAT_DELAY
#endif /* SATELLITE_FRONT_END */
  #define DTV_DELAY
#endif /* PROFILING */
  ret = 1;
#ifdef    PROFILING
  start = switch_start = system_time();
  SiTRACE("%s->%s\n", Si2183_standardName(front_end->previous_standard), Si2183_standardName(new_standard) );
#endif /* PROFILING */

  SiTRACE("Si2183_switch_to_standard starting  %3d -> %3d  force_full_init 0x%02x...\n", front_end->previous_standard, new_standard, force_full_init);
  SiTRACE(" %s-->%s switch starting with Si2183_init_done %d, first_init_done %d\n", Si2183_standardName(front_end->previous_standard), Si2183_standardName(new_standard), front_end->Si2183_init_done, front_end->first_init_done);
#ifdef    TERRESTRIAL_FRONT_END
  SiTRACE("TER flags:    TER_init_done    %d, TER_tuner_init_done %d\n", front_end->TER_init_done, front_end->TER_tuner_init_done);
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
  SiTRACE("SAT flags:    SAT_init_done    %d, SAT_tuner_init_done %d\n", front_end->SAT_init_done, front_end->SAT_tuner_init_done);
#endif /* SATELLITE_FRONT_END */

  input_standard = new_standard;
  /* If the frontend power has been removed       , force a full init */
  if (front_end->previous_standard == 200)                           {force_full_init = 1;}
  /* If this function is called for the first time, force a full init */
  if ( (front_end->first_init_done == 0) && (force_full_init == 0) ) {force_full_init = 1;}
  /* ------------------------------------------------------------ */
  /* Set Previous Flags                                           */
  /* Setting flags representing the previous state                */
  /* NB: Any value not matching a known standard will init as ATV */
  /* Logic applied:                                               */
  /*  dtv demod was used for TERRESTRIAL and SATELLITE reception  */
  /*  ter tuner was used for TERRESTRIAL reception                */
  /*   and for SATELLITE reception if it is the SAT clock source  */
  /*  sat tuner was used for SATELLITE reception                  */
  /*   and for TERRESTRIAL reception if it is the TER clock source*/
  /* ------------------------------------------------------------ */
  switch (front_end->previous_standard) {
#ifdef    TERRESTRIAL_FRONT_END
    case Si2183_DD_MODE_PROP_MODULATION_DVBT :
    case Si2183_DD_MODE_PROP_MODULATION_ISDBT:
    case Si2183_DD_MODE_PROP_MODULATION_DVBT2:
    case Si2183_DD_MODE_PROP_MODULATION_MCNS :
    case Si2183_DD_MODE_PROP_MODULATION_DVBC :
    case Si2183_DD_MODE_PROP_MODULATION_DVBC2:
    {
      dtv_demod_already_used = 1;
      ter_tuner_already_used = 1;
      if ( front_end->demod->tuner_ter_clock_source == Si2183_TER_Tuner_clock) {
        ter_clock_already_used = 1;
      }
#ifdef    SATELLITE_FRONT_END
      if ( front_end->demod->tuner_ter_clock_source == Si2183_SAT_Tuner_clock) {
        sat_tuner_already_used = 1;
        sat_clock_already_used = 1;
      }
#endif /* SATELLITE_FRONT_END */
      break;
    }
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
    case Si2183_DD_MODE_PROP_MODULATION_DVBS :
    case Si2183_DD_MODE_PROP_MODULATION_DVBS2:
    case Si2183_DD_MODE_PROP_MODULATION_DSS  :
    {
      dtv_demod_already_used = 1;
      sat_tuner_already_used = 1;
#ifdef    TERRESTRIAL_FRONT_END
      if ( front_end->demod->tuner_sat_clock_source == Si2183_TER_Tuner_clock) {
        ter_tuner_already_used = 1;
        ter_clock_already_used = 1;
      }
#endif /* TERRESTRIAL_FRONT_END */
      if ( front_end->demod->tuner_sat_clock_source == Si2183_SAT_Tuner_clock) {
        sat_clock_already_used = 1;
      }
      break;
    }
#endif /* SATELLITE_FRONT_END */
#ifdef    TERRESTRIAL_FRONT_END
    case Si2183_DD_MODE_PROP_MODULATION_ANALOG: {
      ter_tuner_already_used = 1;
      dtv_demod_sleeping = 1;
      break;
    }
#endif /* TERRESTRIAL_FRONT_END */
    case 100: /* SLEEP */
    case 200: /* OFF   */
    default :    {
#ifdef    TERRESTRIAL_FRONT_END
      ter_tuner_already_used = 0;
      dtv_demod_sleeping = 1;
#endif /* TERRESTRIAL_FRONT_END */
      front_end->previous_standard = 0;
      break;
    }
  }
  relaunch_after_force_full_init:
  /* ------------------------------------------------------------ */
  /* Set Needed Flags                                             */
  /* Setting flags representing the new state                     */
  /* Logic applied:                                               */
  /*  dtv demod is needed for TERRESTRIAL and SATELLITE reception */
  /*  ter tuner is needed for TERRESTRIAL reception               */
  /*   and for SATELLITE reception if it is the SAT clock source  */
  /*  sat tuner is needed for SATELLITE reception                 */
  /*   and for TERRESTRIAL reception if it is the TER clock source*/
  /* ------------------------------------------------------------ */
  switch (new_standard) {
#ifdef    TERRESTRIAL_FRONT_END
    case Si2183_DD_MODE_PROP_MODULATION_DVBT :
    case Si2183_DD_MODE_PROP_MODULATION_ISDBT:
    case Si2183_DD_MODE_PROP_MODULATION_DVBT2:
    case Si2183_DD_MODE_PROP_MODULATION_MCNS :
    case Si2183_DD_MODE_PROP_MODULATION_DVBC :
    case Si2183_DD_MODE_PROP_MODULATION_DVBC2:
    {
      dtv_demod_needed = 1;
      ter_tuner_needed = 1;
      if ( front_end->demod->tuner_ter_clock_source == Si2183_TER_Tuner_clock) {
        ter_clock_needed = 1;
      }
#ifdef    SATELLITE_FRONT_END
      if ( front_end->demod->tuner_ter_clock_source == Si2183_SAT_Tuner_clock) {
        sat_clock_needed = 1;
        sat_tuner_needed = 1;
      }
#endif /* SATELLITE_FRONT_END */
      break;
    }
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
    case Si2183_DD_MODE_PROP_MODULATION_DVBS :
    case Si2183_DD_MODE_PROP_MODULATION_DVBS2:
    case Si2183_DD_MODE_PROP_MODULATION_DSS  :
    {
      dtv_demod_needed = 1;
      sat_tuner_needed = 1;
#ifdef    TERRESTRIAL_FRONT_END
      if ( front_end->demod->tuner_sat_clock_source == Si2183_TER_Tuner_clock) {
        ter_clock_needed = 1;
        ter_tuner_needed = 1;
      }
#endif /* TERRESTRIAL_FRONT_END */
      if ( front_end->demod->tuner_sat_clock_source == Si2183_SAT_Tuner_clock) {
        sat_clock_needed = 1;
      }
      break;
    }
#endif /* SATELLITE_FRONT_END */
#ifdef    TERRESTRIAL_FRONT_END
    case Si2183_DD_MODE_PROP_MODULATION_ANALOG: {
      ter_tuner_needed = 1;
      break;
    }
#endif /* TERRESTRIAL_FRONT_END */
    default : /* SLEEP */   {
#ifdef    TERRESTRIAL_FRONT_END
      ter_tuner_needed = 0;
#endif /* TERRESTRIAL_FRONT_END */
      new_standard     = 0;
      break;
    }
  }

  /* ------------------------------------------------------------ */
  /* For multiple front-ends: override clock_needed flags         */
  /*  to avoid switching shared clocks                            */
  /* ------------------------------------------------------------ */
  /* For multiple front-ends: override clock_needed flags to avoid switching shared clocks */
#ifdef    TERRESTRIAL_FRONT_END
    if (ter_clock_already_used == 0) {
      if (front_end->TER_tuner_init_done == 1) {
        if ( front_end->demod->tuner_ter_clock_control == Si2183_CLOCK_ALWAYS_ON ) { SiTRACE("forcing ter_clock_already_used = 1\n"); ter_clock_already_used = 1; }
      }
    } else {
      if ( front_end->demod->tuner_ter_clock_control == Si2183_CLOCK_ALWAYS_OFF  ) { SiTRACE("forcing ter_clock_already_used = 0\n"); ter_clock_already_used = 0; }
    }
    if (ter_clock_needed == 0) {
      if ( front_end->demod->tuner_ter_clock_control == Si2183_CLOCK_ALWAYS_ON   ) { SiTRACE("forcing ter_clock_needed = 1\n"); ter_clock_needed = 1; }
    } else {
      if ( front_end->demod->tuner_ter_clock_control == Si2183_CLOCK_ALWAYS_OFF  ) { SiTRACE("forcing ter_clock_needed = 0\n"); ter_clock_needed = 0; }
    }
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
    if (sat_clock_already_used == 0) {
      if (front_end->SAT_tuner_init_done == 1) {
        if ( front_end->demod->tuner_sat_clock_control == Si2183_CLOCK_ALWAYS_ON ) { SiTRACE("forcing sat_clock_already_used = 1\n"); sat_clock_already_used = 1; }
      }
    } else {
      if ( front_end->demod->tuner_sat_clock_control == Si2183_CLOCK_ALWAYS_OFF  ) { SiTRACE("forcing sat_clock_already_used = 0\n"); sat_clock_already_used = 0; }
    }
    if (sat_clock_needed == 0) {
      if ( front_end->demod->tuner_sat_clock_control == Si2183_CLOCK_ALWAYS_ON   ) { SiTRACE("forcing sat_clock_needed = 1\n"); sat_clock_needed = 1; }
    } else {
      if ( front_end->demod->tuner_sat_clock_control == Si2183_CLOCK_ALWAYS_OFF  ) { SiTRACE("forcing sat_clock_needed = 0\n"); sat_clock_needed = 0; }
    }
#endif /* SATELLITE_FRONT_END */

  /* ------------------------------------------------------------ */
  /* if 'force' flag is set, set flags to trigger a full init     */
  /* This can be used to re-init the NIM after a power cycle      */
  /*  or a HW reset                                               */
  /* ------------------------------------------------------------ */
  if (force_full_init) {
    SiTRACE("Forcing full init\n");
    /* set 'init_done' flags to force full init     */
    /* set 'already used' flags to force full init  */
    /* set 'needed' flags to force tuner init if required by the clock control flags */
    if (force_full_init & Si2183_SKIP_DEMOD_INIT) {
      SiTRACE("force_full_init   Si2183_SKIP_DEMOD_INIT\n");
      front_end->first_init_done     = 1;
      front_end->Si2183_init_done    = 1;
    } else {
      if (force_full_init & Si2183_FORCE_DEMOD_INIT  ) {
        SiTRACE("force_full_init   Si2183_FORCE_DEMOD_INIT\n");
        dtv_demod_needed = 1;
        if (front_end->first_init_done == 0) {
           new_standard = 0;
        /* set 'new_standard' to use the proper media in WAKEUP */
#ifdef    TERRESTRIAL_FRONT_END
          if (force_full_init & Si2183_USE_TER_CLOCK  ) {
            SiTRACE("force_full_init   Si2183_USE_TER_CLOCK\n");
            front_end->demod->media = Si2183_TERRESTRIAL;
            /* Setting new_standard to the first TER standard */
#ifdef    DEMOD_DVB_T
            if (new_standard ==0) {new_standard = Si2183_DD_MODE_PROP_MODULATION_DVBT;}
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_DVB_T2
            if (new_standard ==0) { new_standard = Si2183_DD_MODE_PROP_MODULATION_DVBT2; }
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_ISDB_T
            if (new_standard ==0) { new_standard = Si2183_DD_MODE_PROP_MODULATION_ISDBT; }
#endif /* DEMOD_ISDB_T */
#ifdef    DEMOD_DVB_C
            if (new_standard ==0) { new_standard = Si2183_DD_MODE_PROP_MODULATION_DVBC;  }
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_C2
            if (new_standard ==0) { new_standard = Si2183_DD_MODE_PROP_MODULATION_DVBC2; }
#endif /* DEMOD_DVB_C2 */
#ifdef    DEMOD_MCNS
            if (new_standard ==0) { new_standard = Si2183_DD_MODE_PROP_MODULATION_MCNS;  }
#endif /* DEMOD_MCNS */
          }
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
          if (force_full_init & Si2183_USE_SAT_CLOCK  ) {
            SiTRACE("force_full_init   Si2183_USE_SAT_CLOCK\n");
            front_end->demod->media = Si2183_SATELLITE;
#ifdef    DEMOD_DVB_S_S2_DSS
            if (new_standard ==0) { new_standard = Si2183_DD_MODE_PROP_MODULATION_DVBS;  }
#endif /* DEMOD_DVB_S_S2_DSS */
          }
#endif /* SATELLITE_FRONT_END */
        }
      }
      front_end->first_init_done     = 0;
      front_end->Si2183_init_done    = 0;
    }
#ifdef    TERRESTRIAL_FRONT_END
    if (force_full_init & Si2183_FORCE_TER_TUNER_INIT) {
    SiTRACE("force_full_init   Si2183_FORCE_TER_TUNER_INIT\n"); }
    front_end->TER_init_done        = 0;
    front_end->TER_tuner_init_done  = 0;
    front_end->TER_tuner_config_done= 0;
    ter_tuner_already_used = 0;
    if (front_end->demod->tuner_ter_clock_control == Si2183_CLOCK_ALWAYS_ON)         { ter_tuner_needed = 1; SiTRACE("forcing ter_tuner_needed = 1 to activate the TER clock\n");             }
    if ((ter_tuner_needed == 0) && ( force_full_init & Si2183_FORCE_TER_TUNER_INIT)) { ter_tuner_needed = 1; SiTRACE("forcing ter_tuner_needed = 1 due to the FORCE_TER_TUNER_INIT flag \n"); }
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
    if (force_full_init & Si2183_FORCE_SAT_TUNER_INIT) {
    SiTRACE("force_full_init   Si2183_FORCE_SAT_TUNER_INIT\n"); }
    front_end->SAT_init_done       = 0;
    front_end->SAT_tuner_init_done  = 0;
    sat_tuner_already_used = 0;
    if (front_end->demod->tuner_sat_clock_control == Si2183_CLOCK_ALWAYS_ON )        { SiTRACE("forcing sat_tuner_needed = 1 to activate the SAT clock\n");             sat_tuner_needed = 1; }
    if ((sat_tuner_needed == 0) && ( force_full_init & Si2183_FORCE_SAT_TUNER_INIT)) { SiTRACE("forcing sat_tuner_needed = 1 due to the FORCE_SAT_TUNER_INIT flag \n"); sat_tuner_needed = 1; }
#endif /* SATELLITE_FRONT_END */
    dtv_demod_already_used = 0;
  }

  /* ------------------------------------------------------------ */
  /* Request demodulator sleep if its clock will be stopped       */
  /* ------------------------------------------------------------ */
#ifdef    TERRESTRIAL_FRONT_END
  SiTRACE("ter_tuner_already_used %d, ter_tuner_needed %d\n", ter_tuner_already_used,ter_tuner_needed);
  SiTRACE("ter_clock_already_used %d, ter_clock_needed %d\n", ter_clock_already_used,ter_clock_needed);
  if ((ter_tuner_already_used == 1) & (ter_tuner_needed == 0) ) { SiTRACE("TER tuner 1->0 "); }
  if ((ter_tuner_already_used == 0) & (ter_tuner_needed == 1) ) { SiTRACE("TER tuner 0->1 "); }
  if ((ter_clock_already_used == 1) & (ter_clock_needed == 0) ) { SiTRACE("TER clock 1->0 "); dtv_demod_sleep_request = 1; }
  if ((ter_clock_already_used == 0) & (ter_clock_needed == 1) ) { SiTRACE("TER clock 0->1 "); dtv_demod_sleep_request = 1; }
  if ( ter_tuner_needed == ter_tuner_already_used ) { ter_tuner_state = ter_tuner_needed; }
  if ( ter_clock_needed == ter_clock_already_used ) { ter_clock_state = ter_clock_needed; }
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
  SiTRACE("sat_tuner_already_used %d, sat_tuner_needed %d\n", sat_tuner_already_used,sat_tuner_needed);
  SiTRACE("sat_clock_already_used %d, sat_clock_needed %d\n", sat_clock_already_used,sat_clock_needed);
  if ((sat_tuner_already_used == 1) & (sat_tuner_needed == 0) ) { SiTRACE("SAT tuner 1->0 "); }
  if ((sat_tuner_already_used == 0) & (sat_tuner_needed == 1) ) { SiTRACE("SAT tuner 0->1 "); }
  if ((sat_clock_already_used == 1) & (sat_clock_needed == 0) ) { SiTRACE("SAT clock 1->0 "); dtv_demod_sleep_request = 1; }
  if ((sat_clock_already_used == 0) & (sat_clock_needed == 1) ) { SiTRACE("SAT clock 0->1 "); dtv_demod_sleep_request = 1; }
  if ( sat_tuner_needed == sat_tuner_already_used ) { sat_tuner_state = sat_tuner_needed; }
  if ( sat_clock_needed == sat_clock_already_used ) { sat_clock_state = sat_clock_needed; }
#endif /* SATELLITE_FRONT_END */
  SiTRACE("\n");
  /* ------------------------------------------------------------ */
  /* Request demodulator sleep if transition from '1' to '0'      */
  /* ------------------------------------------------------------ */
  if ((dtv_demod_already_used == 1) & (dtv_demod_needed == 0) ) { dtv_demod_sleep_request = 1; }
  SiTRACE(" %s-->%s switch flags    dtv_demod_already_used %d, dtv_demod_needed %d, dtv_demod_sleep_request %d, dtv_demod_sleeping %d\n", Si2183_standardName(front_end->previous_standard), Si2183_standardName(new_standard),
                                    dtv_demod_already_used,    dtv_demod_needed,    dtv_demod_sleep_request,    dtv_demod_sleeping   );
  /* ------------------------------------------------------------ */
  /* Sleep dtv demodulator if requested                           */
  /* ------------------------------------------------------------ */
  if (dtv_demod_sleep_request == 1) {
    SiTRACE("Sleep DTV demod\n");
#ifdef    DEMOD_DVB_T2
    /* To avoid issues with the FEF pin when switching from T2 to ANALOG, set the demodulator for DVB-T/non auto detect reception before POWER_DOWN */
    if (new_standard                       == Si2183_DD_MODE_PROP_MODULATION_ANALOG) {
      if ( ( (front_end->previous_standard == Si2183_DD_MODE_PROP_MODULATION_DVBT  )
           & (front_end->demod->prop->dd_mode.auto_detect == Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_T_T2) )
           | (front_end->previous_standard == Si2183_DD_MODE_PROP_MODULATION_DVBT2 ) ) {
        front_end->demod->prop->dd_mode.modulation  = Si2183_DD_MODE_PROP_MODULATION_DVBT;
        front_end->demod->prop->dd_mode.auto_detect = Si2183_DD_MODE_PROP_AUTO_DETECT_NONE;
        Si2183_L1_SetProperty2(front_end->demod, Si2183_DD_MODE_PROP_CODE);
        Si2183_L1_DD_RESTART  (front_end->demod);
      }
    }
#endif /* DEMOD_DVB_T2 */
    /* If the demod is not needed, it means it's either going to ANALOG or SLEEP   */
    /*  In this case, set the demod silent, putting all possible pins to tristate  */
    /* To nicely recover from this, Si2183_Configure will need to be re-applied    */
    /*  so set the flags to allow this                                             */
    if (dtv_demod_needed == 0) {
      Si2183_L2_SILENT(front_end, 1);
#ifdef    TERRESTRIAL_FRONT_END
      front_end->TER_init_done = 0;
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
      front_end->SAT_init_done = 0;
#endif /* SATELLITE_FRONT_END */
    }
    Si2183_STANDBY (front_end->demod);
    dtv_demod_sleeping = 1;
    dtv_demod_state    = 0;
    SiTRACE(" %s-->%s switch now   dtv_demod_sleeping %d\n", Si2183_standardName(front_end->previous_standard), Si2183_standardName(new_standard), dtv_demod_sleeping   );
    DTV_DELAY
  }

  /* ------------------------------------------------------------ */
  /* Set media for new standard                                   */
  /* ------------------------------------------------------------ */
  if (dtv_demod_needed == 1) {
    Si2183_prepare_DD_MODE (front_end, new_standard);
  }
  front_end->demod->media = Si2183_Media(front_end->demod, new_standard);

  /* ------------------------------------------------------------ */
  /* Allow i2c traffic to reach the tuners                        */
  /* ------------------------------------------------------------ */
   #ifdef    INDIRECT_I2C_CONNECTION
   /* Connection will be done later on, depending on TER/SAT */
   #else  /* INDIRECT_I2C_CONNECTION */
    SiTRACE("Connect tuners i2c\n");
    Si2183_L2_Tuner_I2C_Enable(front_end);
    DTV_DELAY
    i2c_connected = 1;
   #endif /* INDIRECT_I2C_CONNECTION */

#ifdef    SATELLITE_FRONT_END
  /* ------------------------------------------------------------ */
  /* Sleep Sat Tuner                                              */
  /* Sleep satellite   tuner if transition from '1' to '0'        */
  /* ------------------------------------------------------------ */
  if ((sat_tuner_already_used == 1) & (sat_tuner_needed == 0) ) {
   #ifdef    INDIRECT_I2C_CONNECTION
    SiTRACE("Connect SAT tuner i2c to put it in sleep mode?\n");
    if (sat_i2c_connected==0) {
      SiTRACE("-- I2C -- Connect SAT tuner i2c to put it in sleep mode\n");
      front_end->f_SAT_tuner_enable(front_end->callback);
      sat_i2c_connected++;
    }
    DTV_DELAY
   #endif /* INDIRECT_I2C_CONNECTION */
    SiTRACE("Sleep satellite tuner\n");
    #ifdef    SAT_TUNER_CLOCK_OFF
    if (front_end->demod->tuner_sat_clock_control != Si2183_CLOCK_ALWAYS_ON) {
      if (sat_clock_already_used) {
        if ( (res = SAT_TUNER_CLOCK_OFF(front_end->tuner_sat)) !=0 ) {
          SiTRACE("Satellite tuner CLOCK OFF error: 0x%02x\n",res );
          ret = 0; goto return_after_disabling_I2c;
        }
        sat_clock_state = 0;
      }
    }
    #endif /* SAT_TUNER_CLOCK_OFF */
    #ifdef    SAT_TUNER_STANDBY
    if ((res= SAT_TUNER_STANDBY(front_end->tuner_sat)) !=0 ) {
      SiTRACE("Satellite tuner Standby error: 0x%02x\n",res );
      ret = 0; goto return_after_disabling_I2c;
    }
    sat_tuner_state = 0;
    #endif /* SAT_TUNER_STANDBY */
    SAT_DELAY
  }
#endif /* SATELLITE_FRONT_END */
#ifdef    TERRESTRIAL_FRONT_END
  /* ------------------------------------------------------------ */
  /* Sleep Ter Tuner                                              */
  /* Sleep terrestrial tuner  if transition from '1' to '0'       */
  /* ------------------------------------------------------------ */
  if ((ter_tuner_already_used == 1) & (ter_tuner_needed == 0) ) {
   #ifdef    INDIRECT_I2C_CONNECTION
    if (ter_i2c_connected==0) {
      SiTRACE("-- I2C -- Connect TER tuner i2c to sleep it\n");
      front_end->f_TER_tuner_enable(front_end->callback);
      ter_i2c_connected++;
    }
    DTV_DELAY
   #endif /* INDIRECT_I2C_CONNECTION */
    SiTRACE("Sleep terrestrial tuner\n");
    #ifdef    TER_TUNER_CLOCK_OFF
    if (front_end->demod->tuner_ter_clock_control != Si2183_CLOCK_ALWAYS_ON) {
      if (ter_clock_already_used) {
        SiTRACE("Terrestrial tuner clock OFF\n");
        if ((res= TER_TUNER_CLOCK_OFF(front_end->tuner_ter)) !=0 ) {
          SiTRACE("Terrestrial tuner CLOCK OFF error: 0x%02x : %s\n",res, TER_TUNER_ERROR_TEXT(res) );
          SiERROR("Terrestrial tuner CLOCK OFF error!\n");
          ret = 0; goto return_after_disabling_I2c;
        }
        ter_clock_state = 0;
      }
    }
    #endif /* TER_TUNER_CLOCK_OFF */
    #ifdef    TER_TUNER_STANDBY
    SiTRACE("Terrestrial tuner STANDBY\n");
    if ((res= TER_TUNER_STANDBY(front_end->tuner_ter)) !=0 ) {
      SiTRACE("Terrestrial tuner Standby error: 0x%02x : %s\n",res, TER_TUNER_ERROR_TEXT(res) );
      SiERROR("Terrestrial tuner Standby error!\n");
      ret = 0; goto return_after_disabling_I2c;
    }
    ter_tuner_state = 0;
    #endif /* TER_TUNER_STANDBY */
    TER_DELAY
  }
#endif /* TERRESTRIAL_FRONT_END */

#ifdef    SATELLITE_FRONT_END
  /* ------------------------------------------------------------ */
  /* Wakeup Sat Tuner                                             */
  /* Wake up satellite   tuner if transition from '0' to '1'      */
  /* ------------------------------------------------------------ */
  if ((sat_tuner_already_used == 0) & (sat_tuner_needed == 1)) {
   #ifdef    INDIRECT_I2C_CONNECTION
    if (sat_i2c_connected==0) {
      SiTRACE("-- I2C -- Connect SAT tuner i2c to init/wakeup it\n");
      front_end->f_SAT_tuner_enable(front_end->callback);
      sat_i2c_connected++;
    }
    DTV_DELAY
   #endif /* INDIRECT_I2C_CONNECTION */
    if (front_end->SAT_tuner_init_done==0) {
      SiTRACE("Init satellite tuner\n");
      #ifdef    SAT_TUNER_INIT
      if ((res= SAT_TUNER_INIT(front_end->tuner_sat)) !=0) {
        SiTRACE("Satellite tuner HW init error: 0x%02x\n",res );
        ret = 0; goto return_after_disabling_I2c;
      }
      #endif /* SAT_TUNER_INIT */
      front_end->SAT_tuner_init_done = 1;
    } else {
      SiTRACE("Wakeup satellite tuner\n");
      #ifdef    SAT_TUNER_WAKEUP
      if ((res= SAT_TUNER_WAKEUP(front_end->tuner_sat)) !=0) {
        SiTRACE("Satellite tuner wake up error: 0x%02x\n",res );
        ret = 0; goto return_after_disabling_I2c;
      }
      #endif /* SAT_TUNER_WAKEUP */
    }
    sat_tuner_state = 1;
    SAT_DELAY
  }
  /* ------------------------------------------------------------ */
  /* If the satellite tuner's clock is required, activate it      */
  /* ------------------------------------------------------------ */
  SiTRACE("sat_clock_needed %d\n",sat_clock_needed);
  if (sat_clock_needed) {
    #ifdef    SAT_TUNER_CLOCK_ON
     #ifdef    INDIRECT_I2C_CONNECTION
      if (sat_i2c_connected==0) {
        SiTRACE("-- I2C -- Connect SAT tuner i2c to start its clock\n");
        front_end->f_SAT_tuner_enable(front_end->callback);
        sat_i2c_connected++;
      }
      DTV_DELAY
     #endif /* INDIRECT_I2C_CONNECTION */
    if (front_end->demod->tuner_sat_clock_control != Si2183_CLOCK_ALWAYS_OFF) {
      SiTRACE("Turn satellite tuner clock on\n");
      if ((res= SAT_TUNER_CLOCK_ON(front_end->tuner_sat) ) !=0) {
        SiTRACE("Satellite tuner CLOCK ON error: 0x%02x\n",res );
        ret = 0; goto return_after_disabling_I2c;
      }
      sat_clock_state = 1;
      #ifdef    SAT_TUNER_STANDBY_WITH_CLOCK
      if (front_end->demod->media != Si2183_SATELLITE  ) {
        SiTRACE("Satellite tuner STANDBY (if supported by SAT tuner)\n");
        if ( (res = SAT_TUNER_STANDBY_WITH_CLOCK(front_end->tuner_sat)) != -1) {
          SiTRACE("Satellite tuner STANDBY (unused) to save power, while the SAT clock is kept on\n");
        }
        sat_tuner_state = 0;
      }
      #endif /* SAT_TUNER_STANDBY_WITH_CLOCK */
    }
    #endif /* SAT_TUNER_CLOCK_ON */
    SAT_DELAY
  }
#endif /* SATELLITE_FRONT_END */

#ifdef    TERRESTRIAL_FRONT_END
  /* ------------------------------------------------------------ */
  /* Wakeup Ter Tuner                                             */
  /* Wake up terrestrial tuner if transition from '0' to '1'      */
  /* ------------------------------------------------------------ */
  if ((ter_tuner_already_used == 0) & (ter_tuner_needed == 1)) {
   #ifdef    INDIRECT_I2C_CONNECTION
    if (ter_i2c_connected==0) {
      SiTRACE("-- I2C -- Connect TER tuner i2c to init/wakeup it\n");
      front_end->f_TER_tuner_enable(front_end->callback);
      ter_i2c_connected++;
    }
    DTV_DELAY
   #endif /* INDIRECT_I2C_CONNECTION */
    /* Do a full init of the Ter Tuner only if it has not been already done */
    if (front_end->TER_tuner_init_done==0) {
      SiTRACE("Init terrestrial tuner\n");
      #ifdef    TER_TUNER_INIT
      if ((res= TER_TUNER_INIT(front_end->tuner_ter)) !=0) {
        #ifdef    TER_TUNER_ERROR_TEXT
        SiTRACE("Terrestrial tuner HW init error: 0x%02x : %s\n",res, TER_TUNER_ERROR_TEXT(res) );
        #endif /* TER_TUNER_ERROR_TEXT */
        SiERROR("Terrestrial tuner HW init error!\n");
        ret = 0; goto return_after_disabling_I2c;
      }
      #endif /* TER_TUNER_INIT */
      front_end->TER_tuner_init_done =1;
    } else {
      SiTRACE("Wakeup terrestrial tuner\n");
      #ifdef    TER_TUNER_WAKEUP
      if ((res= TER_TUNER_WAKEUP(front_end->tuner_ter)) !=0) {
        SiTRACE("Terrestrial tuner wake up error: 0x%02x : %s\n",res, TER_TUNER_ERROR_TEXT(res) );
        SiERROR("Terrestrial tuner wake up error!\n");
        ret = 0; goto return_after_disabling_I2c;
      }
      #endif /* TER_TUNER_WAKEUP */
    }
    if (front_end->TER_tuner_config_done==0) {
      SiTRACE("Config terrestrial tuner\n");
      SiLabs_TER_Tuner_DTV_OUT_TYPE      (front_end->tuner_ter,front_end->demod->TER_tuner_if_output);
      SiLabs_TER_Tuner_DTV_AGC_SOURCE    (front_end->tuner_ter,front_end->demod->TER_tuner_agc_input);
      front_end->TER_tuner_config_done =1;
    }
    ter_tuner_state = 1;
    TER_DELAY
  }
    /* ------------------------------------------------------------ */
    /* If the terrestrial tuner's clock is required, activate it    */
    /* ------------------------------------------------------------ */
  SiTRACE("ter_clock_needed %d\n",ter_clock_needed);
  if (ter_clock_needed) {
    SiTRACE("Turn terrestrial tuner clock on\n");
    #ifdef    TER_TUNER_CLOCK_ON
     #ifdef    INDIRECT_I2C_CONNECTION
      if (ter_i2c_connected==0) {
        SiTRACE("-- I2C -- Connect TER tuner i2c to start its clock\n");
        front_end->f_TER_tuner_enable(front_end->callback);
        ter_i2c_connected++;
      }
      DTV_DELAY
     #endif /* INDIRECT_I2C_CONNECTION */
    if (front_end->demod->tuner_ter_clock_control != Si2183_CLOCK_ALWAYS_OFF) {
      SiTRACE("Terrestrial tuner CLOCK ON\n");
      if ((res= TER_TUNER_CLOCK_ON(front_end->tuner_ter) ) !=0) {
        SiTRACE("Terrestrial tuner CLOCK ON error: 0x%02x : %s\n",res, TER_TUNER_ERROR_TEXT(res) );
        SiERROR("Terrestrial tuner CLOCK ON error!\n");
        ret = 0; goto return_after_disabling_I2c;
      }
      ter_clock_state = 1;
      #ifdef    TER_TUNER_STANDBY_WITH_CLOCK
      if (front_end->demod->media != Si2183_TERRESTRIAL ) {
        if ( (res = TER_TUNER_STANDBY_WITH_CLOCK(front_end->tuner_ter)) != -1 ) {
          SiTRACE("Terrestrial tuner STANDBY (unused) to save power, while the TER clock is kept on\n");
          ter_tuner_state = 0;
        }
      }
      #endif /* TER_TUNER_STANDBY_WITH_CLOCK */
    }
    #endif /* TER_TUNER_CLOCK_ON */
    TER_DELAY
  }
  if ((front_end->previous_standard != new_standard) && (ter_tuner_state == 1) && (new_standard == Si2183_DD_MODE_PROP_MODULATION_ANALOG)) {
  #ifdef    TER_TUNER_ATV_LO_INJECTION
   TER_TUNER_ATV_LO_INJECTION(front_end->tuner_ter);
  #endif /* TER_TUNER_ATV_LO_INJECTION */
  }
#endif /* TERRESTRIAL_FRONT_END */

  /* ------------------------------------------------------------ */
  /* Change Dtv Demod standard if required                        */
  /* ------------------------------------------------------------ */
  if ((front_end->previous_standard != new_standard) & (dtv_demod_needed == 1)) {
    SiTRACE("Store demod standard (%d)\n", new_standard);
    front_end->demod->standard = new_standard;
    DTV_DELAY
#ifdef    TERRESTRIAL_FRONT_END
    if ( (front_end->demod->media == Si2183_TERRESTRIAL) && (ter_tuner_state == 1) ) {
    #ifdef    TER_TUNER_DTV_LO_INJECTION
     TER_TUNER_DTV_LO_INJECTION(front_end->tuner_ter);
    #endif /* TER_TUNER_DTV_LO_INJECTION */
    #ifdef    TER_TUNER_DTV_LIF_OUT_AMP
    /* Adjusting LIF signal for cable or terrestrial reception */
      switch (new_standard) {
        case Si2183_DD_MODE_PROP_MODULATION_DVBT :
        case Si2183_DD_MODE_PROP_MODULATION_DVBC2:
        case Si2183_DD_MODE_PROP_MODULATION_DVBT2:
        {
          TER_TUNER_DTV_LIF_OUT_AMP(front_end->tuner_ter, 0);
          break;
        }
       case Si2183_DD_MODE_PROP_MODULATION_MCNS :
       case Si2183_DD_MODE_PROP_MODULATION_DVBC : {
          TER_TUNER_DTV_LIF_OUT_AMP(front_end->tuner_ter, 1);
         break;
       }
       default: break;
      }
    #endif /* TER_TUNER_DTV_LIF_OUT_AMP */
    }
#endif /* TERRESTRIAL_FRONT_END */
  }
  /* ------------------------------------------------------------ */
  /* Wakeup Dtv Demod                                             */
  /*  if it has been put in 'standby mode' and is needed          */
  /* ------------------------------------------------------------ */
  if (front_end->Si2183_init_done) {
    SiTRACE("dtv_demod_sleeping %d\n", dtv_demod_sleeping);
    if ((dtv_demod_sleeping == 1) & (dtv_demod_needed == 1) ) {
      if (dtv_demod_already_used == 0) {
        SiTRACE("Take DTV demod out of SILENT mode\n");
        Si2183_L2_SILENT(front_end, 0);
      } else {
        SiTRACE("Wake UP DTV demod\n");
        if (Si2183_WAKEUP (front_end->demod) == NO_Si2183_ERROR) {
          SiTRACE("Wake UP DTV demod OK\n");
        } else {
          SiERROR("Wake UP DTV demod failed!\n");
          SiTRACE("Wake UP DTV demod failed!\n");
          ret = 0; goto return_after_disabling_I2c;
        }
      }
    }
  }
  /* ------------------------------------------------------------ */
  /* Setup Dtv Demod                                              */
  /* Setup dtv demodulator if transition from '0' to '1'          */
  /* ------------------------------------------------------------ */
  if (dtv_demod_needed == 1) {
    /* Do the 'first init' only the first time, plus if requested  */
    /* (when 'force' flag is 1, Si2183_init_done is set to '0')   */
    if (!front_end->Si2183_init_done) {
      SiTRACE("Init demod\n");
      if (Si2183_Init(front_end->demod) == NO_Si2183_ERROR) {
        front_end->Si2183_init_done = 1;
        SiTRACE("Demod init OK\n");
#ifdef    TERRESTRIAL_FRONT_END
        if ( (front_end->demod->rsp->part_info.part == 60) | (front_end->demod->rsp->part_info.part == 80) | (front_end->demod->rsp->part_info.part == 81) ) {
          front_end->auto_detect_TER     = 0; /* auto_detect_TER set to '0' by default for '60', '80' and '81' parts, which don't support DVB_T2 */
        }
#endif /* TERRESTRIAL_FRONT_END */
      } else {
        SiTRACE("Demod init failed!\n");
        SiERROR("Demod init failed!\n");
        ret = 0; goto return_after_disabling_I2c;
      }
    }
    dtv_demod_state = 1;
#ifdef    TERRESTRIAL_FRONT_END
    if (front_end->demod->media == Si2183_TERRESTRIAL) {
      SiTRACE("front_end->demod->media Si2183_TERRESTRIAL\n");
      if (front_end->TER_init_done == 0) {
        SiTRACE("Configure demod for TER\n");
        if (Si2183_Configure(front_end->demod) == NO_Si2183_ERROR) {
          /* set dd_mode.modulation again, as it is overwritten by Si2183_Configure */
          Si2183_prepare_DD_MODE (front_end, new_standard );
          front_end->TER_init_done = 1;
        } else {
          SiTRACE("Demod TER configuration failed !\n");
          SiERROR("Demod TER configuration failed !\n");
          ret = 0; goto return_after_disabling_I2c;
        }
      }
      DTV_DELAY
#ifdef    DEMOD_DVB_T2
      if (ter_tuner_state == 1) {
       #ifdef    INDIRECT_I2C_CONNECTION
        if (ter_i2c_connected==0) {
          SiTRACE("-- I2C -- Connect TER tuner i2c to set the FEF mode\n");
          front_end->f_TER_tuner_enable(front_end->callback);
          ter_i2c_connected++;
        }
        DTV_DELAY
       #endif /* INDIRECT_I2C_CONNECTION */
        /* ------------------------------------------------------------ */
        /* Manage FEF mode in TER tuner                                 */
        /* ------------------------------------------------------------ */
        if (new_standard == Si2183_DD_MODE_PROP_MODULATION_DVBT2) {
          Si2183_L2_TER_FEF_SETUP (front_end, 1);
        } else {
          Si2183_L2_TER_FEF_SETUP (front_end, 0);
        }
      }
#endif /* DEMOD_DVB_T2 */
      TER_DELAY
    }
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
    if (front_end->demod->media == Si2183_SATELLITE  ) {
      SiTRACE("front_end->demod->media Si2183_SATELLITE\n");
      if (front_end->SAT_init_done == 0) {
        SiTRACE("Configure demod for SAT\n");
        if (Si2183_Configure(front_end->demod) == NO_Si2183_ERROR) {
          /* set dd_mode.modulation again, as it is overwritten by Si2183_Configure */
          Si2183_prepare_DD_MODE (front_end, new_standard );
          front_end->SAT_init_done = 1;
        } else {
          SiTRACE("Demod SAT configuration failed !\n");
          SiERROR("Demod SAT configuration failed !\n");
          ret = 0; goto return_after_disabling_I2c;
        }
      }
    }
#endif /* SATELLITE_FRONT_END */
    front_end->demod->prop->dd_mode.invert_spectrum = Si2183_L2_Set_Invert_Spectrum(front_end);
    if (Si2183_L1_SetProperty2(front_end->demod, Si2183_DD_MODE_PROP_CODE)==0) {
      Si2183_L1_DD_RESTART(front_end->demod);
    } else {
      SiTRACE("Demod restart failed !\n");
      ret = 0; goto return_after_disabling_I2c;
    }
  }
  DTV_DELAY

  /* ------------------------------------------------------------ */
  /* update value of previous_standard to prepare next call       */
  /* ------------------------------------------------------------ */
  front_end->previous_standard = new_standard;
  front_end->demod->standard   = new_standard;

  front_end->first_init_done = 1;

#ifdef    TERRESTRIAL_FRONT_END
  SiTRACE("ter_tuner_state %d   ter_clock_state %d\n", ter_tuner_state, ter_clock_state);
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
  SiTRACE("sat_tuner_state %d   sat_clock_state %d\n", sat_tuner_state, sat_clock_state);
#endif /* SATELLITE_FRONT_END */
  SiTRACE("dtv_demod_state %d\n", dtv_demod_state);

  if (force_full_init > 1) {
    SiTRACE("........force_full_init 0x%02x; launching a second run..............\n", force_full_init);
#ifdef    TERRESTRIAL_FRONT_END
    ter_tuner_already_used = ter_tuner_state;
    ter_clock_already_used = ter_clock_state;
    ter_tuner_needed       = 0;
    ter_clock_needed       = 0;
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
    sat_tuner_already_used = sat_tuner_state;
    sat_clock_already_used = sat_clock_state;
    sat_tuner_needed       = 0;
    sat_clock_needed       = 0;
#endif /* SATELLITE_FRONT_END */
    dtv_demod_already_used = dtv_demod_state;
    dtv_demod_needed       = 0;
    force_full_init        = 0x00;
    new_standard           = input_standard;
    goto relaunch_after_force_full_init;
  }

  return_after_disabling_I2c:
  /* ------------------------------------------------------------ */
  /* Forbid i2c traffic to reach the tuners                       */
  /* ------------------------------------------------------------ */
  #ifdef    INDIRECT_I2C_CONNECTION
  #ifdef    SATELLITE_FRONT_END
  if (sat_i2c_connected) {
    SiTRACE("-- I2C -- Disconnect SAT tuner i2c\n");
    front_end->f_SAT_tuner_disable(front_end->callback);
    DTV_DELAY
  }
  #endif /* SATELLITE_FRONT_END */
  #ifdef    TERRESTRIAL_FRONT_END
  if (ter_i2c_connected) {
    SiTRACE("-- I2C -- Disconnect TER tuner i2c\n");
    front_end->f_TER_tuner_disable(front_end->callback);
    DTV_DELAY
  }
  #endif /* TERRESTRIAL_FRONT_END */
  #else  /* INDIRECT_I2C_CONNECTION */
  if (i2c_connected) {
    SiTRACE("Disconnect tuners i2c\n");
    Si2183_L2_Tuner_I2C_Disable(front_end);
    DTV_DELAY
  }
  #endif /* INDIRECT_I2C_CONNECTION */
#ifdef    PROFILING
  snprintf(sequence,1000, "%s","");
#ifdef    TERRESTRIAL_FRONT_END
  STRING_APPEND_SAFE(sequence,1000, "| TER: %4d ms ", ter_tuner_delay);
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
  STRING_APPEND_SAFE(sequence,1000, "| SAT: %4d ms ", sat_tuner_delay);
#endif /* SATELLITE_FRONT_END */
  STRING_APPEND_SAFE(sequence,1000, "| DTV: %4d ms ", dtv_demod_delay);
  STRING_APPEND_SAFE(sequence,1000, "| (%5d ms) "   , system_time()-switch_start);
  SiTRACE("%s\n", sequence);
#endif /* PROFILING */
  SiTRACE("Si2183_switch_to_standard complete\n\n\n");
  return ret;
}
/************************************************************************************************************************
  Si2183_lock_to_carrier function
  Use:      relocking function
            Used to relock on a channel for the current standard
            options:
              if freq = 0, do not tune. This is useful to test the lock time without the tuner delays.
              if freq < 0, do not tune and don't change settings. Just do a DD_RESTART. This is useful to test the relock time upom a reset.
  Parameter: standard the standard to lock to
  Parameter: freq                the frequency to lock to    (in Hz for TER, in kHz for SAT)
  Parameter: dvb_t_bandwidth_hz  the channel bandwidth in Hz (only for DVB-T, DVB-T2, ISDB-T)
  Parameter: dvb_t_stream        the HP/LP stream            (only for DVB-T)
  Parameter: symbol_rate_bps     the symbol rate             (for DVB-C, MCNS and SAT)
  Parameter: dvb_c_constellation the DVB-C constellation     (only for DVB-C)
  Parameter: data_slice_id       the DVB-C2 data slice Id    (only for DVB-C2)
  Parameter: plp_id              the PLP Id  (or ISI Id)     (for DVB-T2, for DVB-C2 when num_dslice  > 1 and for DVB-S2 MIS )
  Parameter: T2_lock_mode        the DVB-T2 lock mode        (0='ANY', 1='T2-Base', 2='T2-Lite')
  Return:    1 if locked, 0 otherwise
************************************************************************************************************************/
signed   int   Si2183_L2_lock_to_carrier   (Si2183_L2_Context *front_end
                                 ,  signed   int  standard
                                 ,  signed   int  freq
                                  , signed   int  ter_bandwidth_hz
#ifdef    DEMOD_DVB_T
                                  , unsigned char dvb_t_stream
#endif /* DEMOD_DVB_T */
                                  , unsigned int  symbol_rate_bps
#ifdef    DEMOD_DVB_C
                                  , unsigned char dvb_c_constellation
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_C2
                                  , signed   int  data_slice_id
#endif /* DEMOD_DVB_C2 */
                                  , signed   int  plp_id
#ifdef    DEMOD_DVB_T2
                                  , unsigned char T2_lock_mode
#endif /* DEMOD_DVB_T2 */
                                  )
{
  signed   int return_code;
  signed   int lockStartTime;       /* lockStartTime is used to trace the time spent in Si2183_L2_lock_to_carrier and is only set at when entering the function                       */
  signed   int startTime;           /* startTime is used to measure internal durations. It is set in various places, whenever required                                                */
  signed   int searchDelay;
  signed   int handshakeDelay;
  signed   int lock;
  signed   int new_lock;
  signed   int max_lock_time_ms;
  signed   int min_lock_time_ms;
#ifdef    DEMOD_DVB_S_S2_DSS
  signed   int isi_id;
  signed   int lpf_khz;
#endif /* DEMOD_DVB_S_S2_DSS */
#ifdef    DEMOD_DVB_T2
  signed int                   plp_index;
#ifdef    _DVB_T2_SIGNALLING_H_
  signed int                   register_value;
  SiLabs_T2_Misc_Signalling    misc;
  SiLabs_T2_L1_Post_Signalling post;
  SiLabs_T2_L1_Pre_Signalling  pre;
#endif /* _DVB_T2_SIGNALLING_H_ */
#endif /* DEMOD_DVB_T2 */

  /* init all flags to avoid compiler warnings */
  return_code      = 0; /* To avoid code checker warning */
  startTime        = 0; /* To avoid code checker warning */
  searchDelay      = 0; /* To avoid code checker warning */
  handshakeDelay   = 0; /* To avoid code checker warning */
  lock             = 0; /* To avoid code checker warning */
  min_lock_time_ms = 0; /* To avoid code checker warning */
  max_lock_time_ms = 0; /* To avoid code checker warning */

#ifdef    DEMOD_DVB_S_S2_DSS
  isi_id           = plp_id;        /* Using isi_id name for DVB-S2 */
#endif /* DEMOD_DVB_S_S2_DSS */
  lockStartTime    = system_time(); /* lockStartTime is used to trace the time spent in Si2183_L2_lock_to_carrier and is only set here */
  new_lock         = 1;

#ifdef    DEMOD_DVB_C2
  data_slice_id = data_slice_id; /* to avoid compiler warning when not used */
#endif /* DEMOD_DVB_C2 */

  SiTRACE ("relock to %s at %d\n", Si2183_standardName(standard), freq);

  if (front_end->handshakeUsed == 0) {
    new_lock = 1;
    front_end->searchStartTime = lockStartTime;
  }
  if (front_end->handshakeUsed == 1) {
    if (front_end->handshakeOn == 1) {
      new_lock = 0;
      SiTRACE("lock_to_carrier_handshake : recalled after   handshake.\n");
    }
    if (front_end->handshakeOn == 0) {
      new_lock = 1;
      front_end->handshakeStart_ms = lockStartTime;
    }
    front_end->searchStartTime = front_end->handshakeStart_ms;
    SiTRACE("lock_to_carrier_handshake : handshake start %d\n", front_end->handshakeStart_ms);
  }

  /* Setting max_lock_time_ms and min_lock_time_ms for locking on required standard */
  switch (standard)
  {
  #ifdef    DEMOD_DVB_T
    case Si2183_DD_MODE_PROP_MODULATION_DVBT : {
      max_lock_time_ms = Si2183_DVBT_MAX_LOCK_TIME;
      min_lock_time_ms = Si2183_DVBT_MIN_LOCK_TIME;
  #ifdef    DEMOD_DVB_T2
      if (front_end->auto_detect_TER) {
        max_lock_time_ms = Si2183_DVBT2_MAX_LOCK_TIME;
      }
  #endif /* DEMOD_DVB_T2 */
      break;
    }
  #endif /* DEMOD_DVB_T */
  #ifdef    DEMOD_DVB_T2
    case Si2183_DD_MODE_PROP_MODULATION_DVBT2: {
      max_lock_time_ms = Si2183_DVBT2_MAX_LOCK_TIME;
      min_lock_time_ms = Si2183_DVBT2_MIN_LOCK_TIME;
      if (front_end->auto_detect_TER) {
        min_lock_time_ms = Si2183_DVBT_MIN_LOCK_TIME;
      }
      break;
    }
  #endif /* DEMOD_DVB_T2 */
  #ifdef    DEMOD_ISDB_T
    case Si2183_DD_MODE_PROP_MODULATION_ISDBT : {
      max_lock_time_ms = Si2183_ISDBT_MAX_LOCK_TIME;
      min_lock_time_ms = Si2183_ISDBT_MIN_LOCK_TIME;
      break;
    }
  #endif /* DEMOD_ISDB_T */
  #ifdef    DEMOD_DVB_C
    case Si2183_DD_MODE_PROP_MODULATION_DVBC : {
      max_lock_time_ms = Si2183_DVB_C_max_lock_ms(front_end->demod, dvb_c_constellation, symbol_rate_bps);
      min_lock_time_ms = Si2183_DVBC_MIN_LOCK_TIME;
      break;
    }
  #endif /* DEMOD_DVB_C */
  #ifdef    DEMOD_DVB_C2
      case Si2183_DD_MODE_PROP_MODULATION_DVBC2 : {
        max_lock_time_ms = Si2183_DVBC2_MAX_LOCK_TIME;
        min_lock_time_ms = Si2183_DVBC2_MIN_LOCK_TIME;
        break;
      }
  #endif /* DEMOD_DVB_C2 */
  #ifdef    DEMOD_MCNS
    case Si2183_DD_MODE_PROP_MODULATION_MCNS : {
      max_lock_time_ms = Si2183_DVB_C_max_lock_ms(front_end->demod, dvb_c_constellation, symbol_rate_bps);
      min_lock_time_ms = Si2183_DVBC_MIN_LOCK_TIME;
      break;
    }
  #endif /* DEMOD_MCNS */
  #ifdef    DEMOD_DVB_S_S2_DSS
      case Si2183_DD_MODE_PROP_MODULATION_DSS  :
      case Si2183_DD_MODE_PROP_MODULATION_DVBS :
      case Si2183_DD_MODE_PROP_MODULATION_DVBS2: {
        if (front_end->auto_detect_SAT) {
          max_lock_time_ms = Si2183_DVBS2_MAX_LOCK_TIME*2;
          min_lock_time_ms = Si2183_DVBS2_MIN_LOCK_TIME;
        } else {
          if ( (standard == Si2183_DD_MODE_PROP_MODULATION_DVBS ) || (standard == Si2183_DD_MODE_PROP_MODULATION_DSS ) ) {
            max_lock_time_ms = Si2183_DVBS_MAX_LOCK_TIME*2;
            min_lock_time_ms = Si2183_DVBS_MIN_LOCK_TIME;
          }
          if   (standard == Si2183_DD_MODE_PROP_MODULATION_DVBS2) {
            max_lock_time_ms = Si2183_DVBS2_MAX_LOCK_TIME*2;
            min_lock_time_ms = Si2183_DVBS2_MIN_LOCK_TIME;
          }
        }
        break;
      }
  #endif /* DEMOD_DVB_S_S2_DSS */
    default : /* ATV */   {
      break;
    }
  }

  /* change settings only if not testing the relock time upon a reset (activated if freq<0) */
  if ( (freq >= 0 ) && (new_lock == 1) ) {
#ifdef    DEMOD_DVB_S_S2_DSS
  if (front_end->demod->media == Si2183_SATELLITE) {
    switch (standard) {
      case Si2183_DD_MODE_PROP_MODULATION_DSS  :
      case Si2183_DD_MODE_PROP_MODULATION_DVBS : {
        SiTRACE("dvbs_afc_range.range_khz = %d\n", front_end->demod->prop->dvbs_afc_range.range_khz);
/*      lpf_khz = (int)((symbol_rate_bps*(1.35/2.0))/1000.0 + front_end->demod->prop->dvbs_afc_range.range_khz); */
        lpf_khz = (((symbol_rate_bps/40000)*27)  + front_end->demod->prop->dvbs_afc_range.range_khz);
        break;
      }
      case Si2183_DD_MODE_PROP_MODULATION_DVBS2: {
        SiTRACE("dvbs2_afc_range.range_khz = %d\n",front_end->demod->prop->dvbs2_afc_range.range_khz);
/*      lpf_khz = (int)((symbol_rate_bps*(1.35/2.0))/1000 + front_end->demod->prop->dvbs2_afc_range.range_khz); */
        lpf_khz = (((symbol_rate_bps/40000)*27)  + front_end->demod->prop->dvbs2_afc_range.range_khz);
        break;
      }
      default: lpf_khz = 63000; break;
    }
    SiTRACE("lpf_khz = %d \n", lpf_khz);
    Si2183_L2_SAT_LPF (front_end, lpf_khz);
  }
#endif /* DEMOD_DVB_S_S2_DSS */
  /* Setting demod for locking on required standard */
    switch (standard)
    {
  #ifdef    DEMOD_DVB_T2
      case Si2183_DD_MODE_PROP_MODULATION_DVBT2:
  #endif /* DEMOD_DVB_T2 */
  #ifdef    DEMOD_DVB_T
      case Si2183_DD_MODE_PROP_MODULATION_DVBT : {
        front_end->demod->prop->dd_mode.bw                = ter_bandwidth_hz/1000000;
        front_end->demod->prop->dvbt_hierarchy.stream = dvb_t_stream;
        return_code = Si2183_L1_SetProperty2(front_end->demod, Si2183_DVBT_HIERARCHY_PROP_CODE);
  #endif /* DEMOD_DVB_T */
  #ifdef    DEMOD_DVB_T2
        if (ter_bandwidth_hz == 1700000) {
          front_end->demod->prop->dd_mode.bw              = Si2183_DD_MODE_PROP_BW_BW_1D7MHZ;
        }
        if (front_end->auto_detect_TER) {
          SiTRACE("DVB-T/T2 auto detect\n");
          if (plp_id != -1) {
            front_end->demod->cmd->dvbt2_plp_select.plp_id_sel_mode = Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MANUAL;
            front_end->demod->cmd->dvbt2_plp_select.plp_id = (unsigned char)plp_id;
          } else {
            front_end->demod->cmd->dvbt2_plp_select.plp_id_sel_mode = Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_AUTO;
            front_end->demod->cmd->dvbt2_plp_select.plp_id = 0;
          }
          Si2183_L1_DVBT2_PLP_SELECT    (front_end->demod, front_end->demod->cmd->dvbt2_plp_select.plp_id , front_end->demod->cmd->dvbt2_plp_select.plp_id_sel_mode);
          front_end->demod->prop->dd_mode.modulation  = Si2183_DD_MODE_PROP_MODULATION_AUTO_DETECT;
          front_end->demod->prop->dd_mode.auto_detect = Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_T_T2;
          front_end->demod->prop->dvbt2_mode.lock_mode= T2_lock_mode;
          Si2183_L1_SetProperty2(front_end->demod, Si2183_DVBT2_MODE_PROP_CODE);
          SiTRACE ("T2_lock_mode %d\n",T2_lock_mode);
        } else {
          if (standard == Si2183_DD_MODE_PROP_MODULATION_DVBT ) {
            front_end->demod->prop->dvbt_hierarchy.stream     = dvb_t_stream;
            return_code = Si2183_L1_SetProperty2(front_end->demod, Si2183_DVBT_HIERARCHY_PROP_CODE);
          }
          if (standard == Si2183_DD_MODE_PROP_MODULATION_DVBT2) {
            if (plp_id != -1) {
              front_end->demod->cmd->dvbt2_plp_select.plp_id_sel_mode = Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MANUAL;
              front_end->demod->cmd->dvbt2_plp_select.plp_id = (unsigned char)plp_id;
            } else {
              front_end->demod->cmd->dvbt2_plp_select.plp_id_sel_mode = Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_AUTO;
              front_end->demod->cmd->dvbt2_plp_select.plp_id = 0;
            }
            Si2183_L1_DVBT2_PLP_SELECT    (front_end->demod, front_end->demod->cmd->dvbt2_plp_select.plp_id , front_end->demod->cmd->dvbt2_plp_select.plp_id_sel_mode);
            front_end->demod->prop->dvbt2_mode.lock_mode= T2_lock_mode;
            Si2183_L1_SetProperty2(front_end->demod, Si2183_DVBT2_MODE_PROP_CODE);
            SiTRACE ("T2_plp_id %d, T2_plp_id_sel_mode %d\n",front_end->demod->cmd->dvbt2_plp_select.plp_id, front_end->demod->cmd->dvbt2_plp_select.plp_id_sel_mode);
            SiTRACE ("T2_lock_mode %d\n",T2_lock_mode);
          }
        }
  #endif /* DEMOD_DVB_T2 */
  #ifdef    DEMOD_DVB_T
        Si2183_L1_SetProperty2(front_end->demod, Si2183_DD_MODE_PROP_CODE);
        SiTRACE("bw %d Hz\n", ter_bandwidth_hz);
        break;
      }
  #endif /* DEMOD_DVB_T */
  #ifdef    DEMOD_ISDB_T
      case Si2183_DD_MODE_PROP_MODULATION_ISDBT: {
        front_end->demod->prop->dd_mode.modulation        = Si2183_DD_MODE_PROP_MODULATION_ISDBT;
        front_end->demod->prop->dd_mode.auto_detect       = Si2183_DD_MODE_PROP_AUTO_DETECT_NONE;
        front_end->demod->prop->dd_mode.bw                = ter_bandwidth_hz/1000000;
        Si2183_L1_SetProperty2(front_end->demod, Si2183_DD_MODE_PROP_CODE);
        SiTRACE("bw %d Hz\n", ter_bandwidth_hz);
        break;
      }
  #endif /* DEMOD_ISDB_T */
  #ifdef    DEMOD_DVB_C
      case Si2183_DD_MODE_PROP_MODULATION_DVBC : {
        front_end->demod->prop->dd_mode.bw                       = 8;
        front_end->demod->prop->dvbc_symbol_rate.rate            = symbol_rate_bps/1000;
        front_end->demod->prop->dvbc_constellation.constellation = dvb_c_constellation;
        Si2183_L1_SetProperty2(front_end->demod, Si2183_DD_MODE_PROP_CODE);
        Si2183_L1_SetProperty2(front_end->demod, Si2183_DVBC_SYMBOL_RATE_PROP_CODE);
        Si2183_L1_SetProperty2(front_end->demod, Si2183_DVBC_CONSTELLATION_PROP_CODE);
        SiTRACE("sr %d bps, constel %d\n", symbol_rate_bps, dvb_c_constellation);
        break;
      }
  #endif /* DEMOD_DVB_C */
  #ifdef    DEMOD_DVB_C2
      case Si2183_DD_MODE_PROP_MODULATION_DVBC2 : {
        if (data_slice_id != -1) {
          front_end->demod->cmd->dvbc2_ds_plp_select.ds_id             = (unsigned char)data_slice_id;
          front_end->demod->cmd->dvbc2_ds_plp_select.plp_id            = (unsigned char)plp_id;
          front_end->demod->cmd->dvbc2_ds_plp_select.id_sel_mode     = Si2183_DVBC2_DS_PLP_SELECT_CMD_ID_SEL_MODE_MANUAL;
        } else {
          front_end->demod->cmd->dvbc2_ds_plp_select.ds_id             = 0;
          front_end->demod->cmd->dvbc2_ds_plp_select.plp_id            = 0;
          front_end->demod->cmd->dvbc2_ds_plp_select.id_sel_mode     = Si2183_DVBC2_DS_PLP_SELECT_CMD_ID_SEL_MODE_AUTO;
        }
        Si2183_L1_DVBC2_DS_PLP_SELECT      (front_end->demod, front_end->demod->cmd->dvbc2_ds_plp_select.plp_id , front_end->demod->cmd->dvbc2_ds_plp_select.id_sel_mode, front_end->demod->cmd->dvbc2_ds_plp_select.ds_id);
        front_end->demod->prop->dd_mode.bw                       = ter_bandwidth_hz/1000000;
        Si2183_L1_SetProperty2(front_end->demod, Si2183_DD_MODE_PROP_CODE);
        Si2183_L1_DD_RESTART            (front_end->demod);
        break;
      }
  #endif /* DEMOD_DVB_C2 */
  #ifdef    DEMOD_MCNS
    case Si2183_DD_MODE_PROP_MODULATION_MCNS : {
      front_end->demod->prop->dd_mode.bw                       = ter_bandwidth_hz/1000000;
      front_end->demod->prop->mcns_symbol_rate.rate            = symbol_rate_bps/1000;
      front_end->demod->prop->mcns_constellation.constellation = dvb_c_constellation;
      Si2183_L1_SetProperty2(front_end->demod, Si2183_DD_MODE_PROP_CODE);
      Si2183_L1_SetProperty2(front_end->demod, Si2183_MCNS_SYMBOL_RATE_PROP_CODE);
      Si2183_L1_SetProperty2(front_end->demod, Si2183_MCNS_CONSTELLATION_PROP_CODE);
      SiTRACE("sr %d bps, constel %d\n", symbol_rate_bps, dvb_c_constellation);
      break;
    }
  #endif /* DEMOD_MCNS */
  #ifdef    DEMOD_DVB_S_S2_DSS
      case Si2183_DD_MODE_PROP_MODULATION_DSS  :
      case Si2183_DD_MODE_PROP_MODULATION_DVBS :
      case Si2183_DD_MODE_PROP_MODULATION_DVBS2: {
        if (front_end->auto_detect_SAT) {
          SiTRACE("DVB-S/S2 auto detect\n");
          if (front_end->demod->MIS_capability) {
            if (isi_id != -1) {
              front_end->demod->cmd->dvbs2_stream_select.stream_sel_mode = Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_SEL_MODE_MANUAL;
              front_end->demod->cmd->dvbs2_stream_select.stream_id       = (unsigned char)isi_id;
            } else {
              front_end->demod->cmd->dvbs2_stream_select.stream_sel_mode = Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_SEL_MODE_AUTO;
              front_end->demod->cmd->dvbs2_stream_select.stream_id       = 0;
            }
            Si2183_L1_DVBS2_STREAM_SELECT (front_end->demod, front_end->demod->cmd->dvbs2_stream_select.stream_id, front_end->demod->cmd->dvbs2_stream_select.stream_sel_mode);
          }
          /* in AUTO_RELOCK, set dvbs2_symbol_rate as it is used as the SAT sr value */
          front_end->demod->prop->dvbs2_symbol_rate.rate           = symbol_rate_bps/1000;
          Si2183_L1_SetProperty2(front_end->demod, Si2183_DVBS2_SYMBOL_RATE_PROP_CODE);
          /* Set dvbs_symbol_rate also because it will be used for monitoring the SR */
          front_end->demod->prop->dvbs_symbol_rate.rate            = symbol_rate_bps/1000;
          front_end->demod->prop->dd_mode.modulation  = Si2183_DD_MODE_PROP_MODULATION_AUTO_DETECT;
          /* Trick to avoid slowing down AUTO SAT mode when not using DSS: */
          /*  AUTO_DVB_S_S2_DSS is only used if the input standard is DSS  */
          if (standard == Si2183_DD_MODE_PROP_MODULATION_DSS) {
            front_end->demod->prop->dd_mode.auto_detect = Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_S_S2_DSS;
          } else {
            front_end->demod->prop->dd_mode.auto_detect = Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_S_S2;
          }
        } else {
          if ( (standard == Si2183_DD_MODE_PROP_MODULATION_DVBS ) || (standard == Si2183_DD_MODE_PROP_MODULATION_DSS ) ) {
            front_end->demod->prop->dvbs_symbol_rate.rate            = symbol_rate_bps/1000;
            Si2183_L1_SetProperty2(front_end->demod, Si2183_DVBS_SYMBOL_RATE_PROP_CODE);
          }
          if   (standard == Si2183_DD_MODE_PROP_MODULATION_DVBS2) {
            front_end->demod->prop->dvbs2_symbol_rate.rate           = symbol_rate_bps/1000;
            Si2183_L1_SetProperty2(front_end->demod, Si2183_DVBS2_SYMBOL_RATE_PROP_CODE);
            if (front_end->demod->MIS_capability) {
              if (isi_id != -1) {
                front_end->demod->cmd->dvbs2_stream_select.stream_sel_mode = Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_SEL_MODE_MANUAL;
                front_end->demod->cmd->dvbs2_stream_select.stream_id       = (unsigned char)isi_id;
              } else {
                front_end->demod->cmd->dvbs2_stream_select.stream_sel_mode = Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_SEL_MODE_AUTO;
                front_end->demod->cmd->dvbs2_stream_select.stream_id       = 0;
              }
              Si2183_L1_DVBS2_STREAM_SELECT (front_end->demod, front_end->demod->cmd->dvbs2_stream_select.stream_id, front_end->demod->cmd->dvbs2_stream_select.stream_sel_mode);
            }
          }
        }
        Si2183_L1_SetProperty2(front_end->demod, Si2183_DD_MODE_PROP_CODE);
        SiTRACE("sr %d bps\n", symbol_rate_bps);
        break;
      }
  #endif /* DEMOD_DVB_S_S2_DSS */
      default : /* ATV */   {
        SiTRACE("'%d' standard (%s) is not managed by Si2183_lock_to_carrier\n", standard, Si2183_standardName(standard));
        return 0;
        break;
      }
    }

    if (front_end->lockAbort) {
      SiTRACE("Si2183_L2_lock_to_carrier : lock aborted before tuning, after %d ms.\n", system_time() - lockStartTime );
      front_end->lockAbort = 0;
      return 0;
    }

    /* Allow using this function without tuning */
    if (freq >  0) {
      startTime = system_time();
      Si2183_L2_Tune                  (front_end,       freq);
      SiTRACE ("Si2183_lock_to_carrier 'tune'  took %3d ms\n", system_time() - startTime);
    }

    startTime = system_time();
  #ifdef    DEMOD_DVB_C2
    /* For standards not DVB-C2, start the lock process using Si2183_L1_DD_RESTART */
    if (standard != Si2183_DD_MODE_PROP_MODULATION_DVBC2) {
  #endif /* DEMOD_DVB_C2 */
      Si2183_L1_DD_RESTART            (front_end->demod);
      SiTRACE   ("Si2183_lock_to_carrier 'reset' took %3d ms\n", system_time() - startTime);
  #ifdef    DEMOD_DVB_C2
    }
  #endif /* DEMOD_DVB_C2 */
  #ifdef    DEMOD_DVB_C2
    /* For DVB-C2, start the lock process using Si2183_L1_DVBC2_CTRL */
    if (standard == Si2183_DD_MODE_PROP_MODULATION_DVBC2) {
      startTime = system_time();
      front_end->demod->cmd->dvbc2_ctrl.action        = Si2183_DVBC2_CTRL_CMD_ACTION_START;
      front_end->demod->cmd->dvbc2_ctrl.tuned_rf_freq = freq;
      Si2183_L1_DVBC2_CTRL (front_end->demod, front_end->demod->cmd->dvbc2_ctrl.action , front_end->demod->cmd->dvbc2_ctrl.tuned_rf_freq);
      SiTRACE   ("Si2183_lock_to_carrier 'dvbc2_ctrl/START' took %3d ms\n", system_time() - startTime);
    }
  #endif /* DEMOD_DVB_C2 */

    /* If tuning, reset the timeout reference time. This is done here to be independent on the tuning time */
    if (freq >  0) {
      front_end->searchStartTime = system_time();
    }

    /* as we will not lock in less than min_lock_time_ms, wait a while..., but check for a possible 'abort' from the application */
    startTime = system_time();
    while (system_time() - startTime < min_lock_time_ms) {
      if (front_end->lockAbort) {
        SiTRACE("Si2183_L2_lock_to_carrier : lock aborted before checking lock status, after %d ms.\n", system_time() - lockStartTime );
        front_end->lockAbort = 0;
        return 0;
      }
      /* Adapt here the minimal 'reaction time' of the application*/
      system_wait(20);
    }
  }
  /* testing the relock time upon a reset (activated if freq<0) */
  if (freq < 0) {
    SiTRACE   ("Si2183_lock_to_carrier 'only_reset'\n");
    Si2183_L1_DD_RESTART (front_end->demod);
  }

  /* The actual lock check loop */
  while (1) {

    searchDelay = system_time() - front_end->searchStartTime;

    /* Check the status for the current modulation */

    switch (standard) {
      default                                   :
#ifdef    DEMOD_DVB_T2
      case Si2183_DD_MODE_PROP_MODULATION_DVBT2 :
#endif /* DEMOD_DVB_T2 */
      case Si2183_DD_MODE_PROP_MODULATION_DVBT  : {
        /* DVB-T/T2 auto detect seek loop, using Si2183_L1_DD_STATUS                                           */
        /* if DL LOCKED                             : demod is locked on a dd_status->modulation signal        */
        /* if DL NO_LOCK and rsqstat_bit5 NO_CHANGE : demod is searching for a DVB-T/T2 signal                 */
        /* if DL NO_LOCK and rsqstat_bit5 CHANGE    : demod says this is not a DVB-T/T2 signal (= 'neverlock') */
        return_code = Si2183_L1_DD_STATUS(front_end->demod, Si2183_DD_STATUS_CMD_INTACK_CLEAR);
        if (return_code != NO_Si2183_ERROR) {
          SiTRACE("Si2183_lock_to_carrier: Si2183_L1_DD_STATUS error\n");
          SiERROR("Si2183_lock_to_carrier: Si2183_L1_DD_STATUS error\n");
          goto exit_lock;
          break;
        }

        if (  front_end->demod->rsp->dd_status.dl  == Si2183_DD_STATUS_RESPONSE_DL_LOCKED   ) {
          /* Return 1 to signal that the Si2183 is locked on a valid DVB-T/T2 channel */
          SiTRACE("Si2183_lock_to_carrier: locked on a %s signal\n", Si2183_standardName(front_end->demod->rsp->dd_status.modulation) );
          lock = 1;
#ifdef    DEMOD_DVB_T2
          /* Make sure FEF mode is ON when locked on a T2 channel */
          if   (front_end->demod->rsp->dd_status.modulation == Si2183_DD_MODE_PROP_MODULATION_DVBT2) {
           #ifdef    INDIRECT_I2C_CONNECTION
            front_end->f_TER_tuner_enable(front_end->callback);
           #else  /* INDIRECT_I2C_CONNECTION */
            Si2183_L2_Tuner_I2C_Enable(front_end);
           #endif /* INDIRECT_I2C_CONNECTION */
            Si2183_L2_TER_FEF(front_end, 1);
           #ifdef    INDIRECT_I2C_CONNECTION
            front_end->f_TER_tuner_disable(front_end->callback);
           #else  /* INDIRECT_I2C_CONNECTION */
            Si2183_L2_Tuner_I2C_Disable(front_end);
           #endif /* INDIRECT_I2C_CONNECTION */
          }
#endif /* DEMOD_DVB_T2 */
          goto exit_lock;
        } else {
          if (  front_end->demod->rsp->dd_status.rsqstat_bit5 == Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT5_CHANGE ) {
          /* Return 0 if firmware signals 'no DVB-T/T2 channel' */
          SiTRACE ("'no DVB-T/T2 channel': not locked after %7d ms\n", searchDelay);
          goto exit_lock;
          }
        }
        break;
      }
#ifdef    DEMOD_ISDB_T
      case Si2183_DD_MODE_PROP_MODULATION_ISDBT : {
        /* ISDB-T auto detect seek loop, using Si2183_L1_DD_STATUS                                             */
        /* if DL LOCKED                             : demod is locked on a dd_status->modulation signal        */
        /* if DL NO_LOCK and rsqstat_bit5 NO_CHANGE : demod is searching for an ISDB-T signal                  */
        /* if DL NO_LOCK and rsqstat_bit5 CHANGE    : demod says this is not an ISDB-T signal (= 'neverlock')  */
        return_code = Si2183_L1_DD_STATUS(front_end->demod, Si2183_DD_STATUS_CMD_INTACK_CLEAR);
        if (return_code != NO_Si2183_ERROR) {
          SiTRACE("Si2183_lock_to_carrier: Si2183_L1_DD_STATUS error\n");
          SiERROR("Si2183_lock_to_carrier: Si2183_L1_DD_STATUS error\n");
          goto exit_lock;
          break;
        }
        if (  front_end->demod->rsp->dd_status.dl  == Si2183_DD_STATUS_RESPONSE_DL_LOCKED   ) {
          /* Return 1 to signal that the Si2183 is locked on a valid DVB-T/T2 channel */
          SiTRACE("Si2183_lock_to_carrier: locked on a %s signal\n", Si2183_standardName(front_end->demod->rsp->dd_status.modulation) );
          lock = 1;
          goto exit_lock;
        } else {
          if (  front_end->demod->rsp->dd_status.rsqstat_bit5 == Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT5_CHANGE ) {
          /* Return 0 if firmware signals 'no ISDB-T channel' */
          SiTRACE ("'no ISDB-T channel': not locked after %7d ms\n", searchDelay);
          goto exit_lock;
          }
        }
        break;
      }
#endif /* DEMOD_ISDB_T */
#ifdef    DEMOD_DVB_S_S2_DSS
      case Si2183_DD_MODE_PROP_MODULATION_DSS   :
      case Si2183_DD_MODE_PROP_MODULATION_DVBS  : {
        return_code = Si2183_L1_DD_STATUS  (front_end->demod, Si2183_DD_STATUS_CMD_INTACK_CLEAR);
        if (return_code != NO_Si2183_ERROR) {
          SiTRACE("Si2183_lock_to_carrier: Si2183_L1_DD_STATUS error\n");
          SiERROR("Si2183_lock_to_carrier: Si2183_L1_DD_STATUS error\n");
          goto exit_lock;
          break;
        }

        if (front_end->demod->rsp->dd_status.dl == Si2183_DD_STATUS_RESPONSE_DL_LOCKED) {
          /* Return 1 to signal that the Si2183 is locked on a valid DVB-S channel */
          lock = 1;
          goto exit_lock;
        }
        break;
      }
      case Si2183_DD_MODE_PROP_MODULATION_DVBS2 : {
        return_code = Si2183_L1_DD_STATUS(front_end->demod, Si2183_DD_STATUS_CMD_INTACK_CLEAR);
        if (return_code != NO_Si2183_ERROR) {
          SiTRACE("Si2183_lock_to_carrier: Si2183_L1_DD_STATUS error\n");
          SiERROR("Si2183_lock_to_carrier: Si2183_L1_DD_STATUS error\n");
          goto exit_lock;
          break;
        }
        if (front_end->demod->rsp->dd_status.dl == Si2183_DD_STATUS_RESPONSE_DL_LOCKED) {
          /* Return 1 to signal that the Si2183 is locked on a valid DVB-S2 channel */
          lock = 1;
          goto exit_lock;
        }
        break;
      }
#endif /* DEMOD_DVB_S_S2_DSS */
#ifdef    DEMOD_DVB_C
      case Si2183_DD_MODE_PROP_MODULATION_DVBC  : {
        return_code = Si2183_L1_DD_STATUS(front_end->demod, Si2183_DD_STATUS_CMD_INTACK_CLEAR);

        if (return_code != NO_Si2183_ERROR) {
          SiTRACE("Si2183_lock_to_carrier: Si2183_L1_DD_STATUS error\n");
          SiERROR("Si2183_lock_to_carrier: Si2183_L1_DD_STATUS error\n");
          goto exit_lock;
          break;
        }

        if ( (front_end->demod->rsp->dd_status.dl    == Si2183_DD_STATUS_RESPONSE_DL_LOCKED     ) ) {
          /* Return 1 to signal that the Si2183 is locked on a valid SAT channel */
          SiTRACE("%s lock\n", Si2183_standardName(front_end->demod->rsp->dd_status.modulation));
          lock = 1;
          goto exit_lock;
        }
        break;
      }
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_C2
      case Si2183_DD_MODE_PROP_MODULATION_DVBC2  : {
        return_code = Si2183_L1_DVBC2_STATUS(front_end->demod, Si2183_DVBC2_STATUS_CMD_INTACK_CLEAR);

        if (return_code != NO_Si2183_ERROR) {
          SiTRACE("Si2183_lock_to_carrier: Si2183_DVBC2_STATUS error\n");
          SiERROR("Si2183_lock_to_carrier: Si2183_DVBC2_STATUS error\n");
          goto exit_lock;
          break;
        }
        if ( (front_end->demod->rsp->dvbc2_status.dvbc2_status == Si2183_DVBC2_STATUS_RESPONSE_DVBC2_STATUS_TUNE_REQUEST ) ) {
          /* Retune to lock to the selected C2 data slice */
          freq = front_end->demod->rsp->dvbc2_status.rf_freq;
          Si2183_L2_Tune                  (front_end,       freq);
          startTime = system_time();
          front_end->demod->cmd->dvbc2_ctrl.action        = Si2183_DVBC2_CTRL_CMD_ACTION_RESUME;
          front_end->demod->cmd->dvbc2_ctrl.tuned_rf_freq = freq;
          /* Resume C2 lock on the new frequency */
          return_code = Si2183_L1_DVBC2_CTRL (front_end->demod, front_end->demod->cmd->dvbc2_ctrl.action , front_end->demod->cmd->dvbc2_ctrl.tuned_rf_freq);
          if (return_code != NO_Si2183_ERROR) {
            SiERROR("Si2183_lock_to_carrier: Si2183_L1_DVBC2_CTRL error (dvbc2_ctrl/RESUME)\n");
            goto exit_lock;
            break;
          }
          system_wait(min_lock_time_ms);
          SiTRACE   ("Si2183_lock_to_carrier 'dvbc2_ctrl/RESUME' at %d took %3d ms\n", freq, system_time() - startTime);
          /* Reset the lock start reference */
          front_end->searchStartTime = system_time();
        } else {
          if ( (front_end->demod->rsp->dvbc2_status.dl    == Si2183_DVBC2_STATUS_RESPONSE_DL_LOCKED     ) ) {
            /* Return 1 to signal that the Si2183 is locked on a valid C2 channel */
            SiTRACE("%s lock on DS_ID %3d, PLP_ID %3d at %d Hz, bw %d MHz\n", Si2183_standardName(front_end->demod->rsp->dd_status.modulation), front_end->demod->rsp->dvbc2_status.ds_id, front_end->demod->rsp->dvbc2_status.plp_id, freq, ter_bandwidth_hz/1000000 );
            lock = 1;
            goto exit_lock;
          }
        }
        break;
      }
#endif /* DEMOD_DVB_C2 */
#ifdef    DEMOD_MCNS
      case Si2183_DD_MODE_PROP_MODULATION_MCNS  : {
        return_code = Si2183_L1_DD_STATUS(front_end->demod, Si2183_DD_STATUS_CMD_INTACK_CLEAR);

        if (return_code != NO_Si2183_ERROR) {
          SiTRACE("Si2183_lock_to_carrier: Si2183_L1_DD_STATUS error\n");
          SiERROR("Si2183_lock_to_carrier: Si2183_L1_DD_STATUS error\n");
          goto exit_lock;
          break;
        }

        if ( (front_end->demod->rsp->dd_status.dl    == Si2183_DD_STATUS_RESPONSE_DL_LOCKED     ) ) {
          /* Return 1 to signal that the Si2183 is locked on a valid SAT channel */
          SiTRACE("%s lock\n", Si2183_standardName(front_end->demod->rsp->dd_status.modulation));
          lock = 1;
          goto exit_lock;
        }
        break;
      }
#endif /* DEMOD_MCNS */
    }

    /* timeout management (this should never happen if timeout values are correctly set) */
    searchDelay = system_time() - front_end->searchStartTime;
    if (searchDelay >= max_lock_time_ms) {
      SiTRACE ("Si2183_lock_to_carrier timeout(%d) after %d ms\n", max_lock_time_ms, searchDelay);
      goto exit_lock;
      break;
    }

    if (front_end->handshakeUsed == 1) {
      handshakeDelay = system_time() - lockStartTime;
      if (handshakeDelay >= front_end->handshakePeriod_ms) {
        SiTRACE ("lock_to_carrier_handshake : handshake after %5d ms (at %10d). (search delay %6d ms)\n\n", handshakeDelay, freq, searchDelay);
        front_end->handshakeOn = 1;
        /* The application will check handshakeStart_ms to know whether the lock is complete or not */
        return searchDelay + 2; /* Make sure we don't return '0' or '1' from here */
      } else {
        SiTRACE ("lock_to_carrier_handshake : no handshake yet. (handshake delay %6d ms, search delay %6d ms)\n", handshakeDelay, searchDelay);
      }
    }

    if (front_end->lockAbort) {
      SiTRACE("Si2183_L2_lock_to_carrier : lock aborted after %d ms.\n", system_time() - lockStartTime);
      front_end->lockAbort = 0;
      goto exit_lock;
    }

    /* Check status every 5 ms */
    system_wait(5);
  }

  exit_lock:

  front_end->handshakeOn = 0;
  searchDelay = system_time() - front_end->searchStartTime;

  if (lock) {
    Si2183_L1_DD_BER  (front_end->demod, Si2183_DD_BER_CMD_RST_CLEAR  );
    Si2183_L1_DD_UNCOR(front_end->demod, Si2183_DD_UNCOR_CMD_RST_CLEAR);
    SiTRACE ("Si2183_lock_to_carrier 'lock'  took %3d ms\n"        , searchDelay);
#ifdef    DEMOD_DVB_T2
    plp_index = plp_index;
#ifdef    SiTRACES
    if (front_end->demod->rsp->dd_status.modulation == Si2183_DD_MODE_PROP_MODULATION_DVBT2) {
      Si2183_L1_DVBT2_STATUS   (front_end->demod, Si2183_DVBT2_STATUS_CMD_INTACK_OK);
      SiTRACE("There are %d PLPs in this stream\n", front_end->demod->rsp->dvbt2_status.num_plp);
      for (plp_index=0; plp_index<front_end->demod->rsp->dvbt2_status.num_plp; plp_index++) {
        Si2183_L1_DVBT2_PLP_INFO (front_end->demod, plp_index);
        if (front_end->demod->rsp->dvbt2_plp_info.plp_type == Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_TYPE_COMMON) {
          SiTRACE("COMMON PLP at index %3d: PLP ID %3d, PLP TYPE %d\n", plp_index, front_end->demod->rsp->dvbt2_plp_info.plp_id, front_end->demod->rsp->dvbt2_plp_info.plp_type);
        } else {
          SiTRACE("DATA   PLP at index %3d: PLP ID %3d, PLP TYPE %d\n", plp_index, front_end->demod->rsp->dvbt2_plp_info.plp_id, front_end->demod->rsp->dvbt2_plp_info.plp_type);
        }
      }
  #ifdef    _DVB_T2_SIGNALLING_H_
      if ( front_end->misc_infos & 0x01000000 ) { /* Trace DVB-T2 signalling */
        SiTRACE("Reading DVB-T2 signalling info\n");
        SiTraceConfiguration("traces -verbose on");
        SiTraceConfiguration("traces suspend");
        Si2183_L2_Read_L1_Pre_Data  (front_end, &pre );
        Si2183_L2_Read_L1_Post_Data (front_end, &post);
        Si2183_L2_Read_L1_Misc_Data (front_end, &misc);
        SiTRACE             ("traces erase");
        SiTraceConfiguration("traces resume");
        SiLabs_L1_Trace             (&pre, &post, &misc, freq);
        #define TRACE_DVB_T2_REGISTER(reg,a,b,c) SiTraceConfiguration("traces suspend"); register_value = Si2183_L1_GET_REG(front_end->demod,  a, b, c); SiTraceConfiguration("traces resume"); SiTRACE(" register  %-30s %d\n", #reg, register_value);
        TRACE_DVB_T2_REGISTER(bbdf_data_issyi_status,  1, 122, 20);
        TRACE_DVB_T2_REGISTER(bbdf_data_npd_active  ,  0, 120, 20);
        TRACE_DVB_T2_REGISTER(ts_rate_in            , 27,  72, 22);
        TRACE_DVB_T2_REGISTER(nco_ts_freq           , 27, 188, 21);
        TRACE_DVB_T2_REGISTER(nco_update_mode       ,  2, 175, 21);
        TRACE_DVB_T2_REGISTER(djb_alarm_data        , 11,  48, 22);
        TRACE_DVB_T2_REGISTER(bbdf_comm_issyi_status,  1, 123, 20);
        TRACE_DVB_T2_REGISTER(bbdf_comm_npd_active  ,  0, 121, 20);
        TRACE_DVB_T2_REGISTER(djb_alarm_comm        , 11,  50, 22);
        TRACE_DVB_T2_REGISTER(djb_alarm_ibs_b       ,  9, 208, 21);
        TRACE_DVB_T2_REGISTER(djb_alarm_others      , 10,  46, 22);
        TRACE_DVB_T2_REGISTER(l1_post_scrambled     ,231,  61, 13);
        TRACE_DVB_T2_REGISTER(pre_l1_mod            ,  3,  31, 13);
        TRACE_DVB_T2_REGISTER(pre_num_data_symbols  , 11,  54, 13);
      }
  #endif /* _DVB_T2_SIGNALLING_H_ */
    }
#endif /* SiTRACES */
#endif /* DEMOD_DVB_T2 */
  } else {
    SiTRACE ("Si2183_lock_to_carrier at %10d (%s) failed after %d ms\n",freq, Si2183_standardName(front_end->demod->rsp->dd_status.modulation), searchDelay);
  }

  return lock;
}
/************************************************************************************************************************
  Si2183_L2_Tune function
  Use:        tuner current frequency retrieval function
              Used to retrieve the current RF from the tuner's driver.
  Porting:    Replace the internal TUNER function calls by the final tuner's corresponding calls
  Comments:   If the tuner is connected via the demodulator's I2C switch, enabling/disabling the i2c_passthru is required before/after tuning.
  Behavior:   This function closes the Si2183's I2C switch then tunes and finally reopens the I2C switch
  Parameter:  *front_end, the front-end handle
  Parameter:  rf, the frequency to tune at
  Returns:    rf
************************************************************************************************************************/
signed   int  Si2183_L2_Tune               (Si2183_L2_Context *front_end, signed   int rf)
{
#ifdef    TUNERTER_API
  #define Si2183_USING_SILABS_TER_TUNER
#else  /* TUNERTER_API */
  #ifdef    SILABS_TER_TUNER_API
    #define Si2183_USING_SILABS_TER_TUNER
  #endif /* SILABS_TER_TUNER_API */
#endif /* TUNERTER_API */

#ifdef    Si2183_USING_SILABS_TER_TUNER
    char bw;
    char modulation;
#endif /* Si2183_USING_SILABS_TER_TUNER */

    SiTRACE("Si2183_L2_Tune at %d\n",rf);

 #ifdef    INDIRECT_I2C_CONNECTION
  /*  I2C connection will be done later on, depending on the media */
 #else  /* INDIRECT_I2C_CONNECTION */
    Si2183_L2_Tuner_I2C_Enable(front_end);
 #endif /* INDIRECT_I2C_CONNECTION */

#ifdef    TERRESTRIAL_FRONT_END
    if (front_end->demod->media == Si2183_TERRESTRIAL) {
 #ifdef    INDIRECT_I2C_CONNECTION
      front_end->f_TER_tuner_enable(front_end->callback);
 #endif /* INDIRECT_I2C_CONNECTION */
#ifdef    DEMOD_DVB_T2
      Si2183_L2_TER_FEF (front_end, 0);
#endif /* DEMOD_DVB_T2 */
#ifdef    Si2183_USING_SILABS_TER_TUNER
      if (front_end->demod->prop->dd_mode.modulation == Si2183_DD_MODE_PROP_MODULATION_DVBC  ) {
        modulation = L1_RF_TER_TUNER_MODULATION_DVBC;
        bw         = 8;
      } else {
        modulation = L1_RF_TER_TUNER_MODULATION_DVBT;
        switch (front_end->demod->prop->dd_mode.bw) {
          case Si2183_DD_MODE_PROP_BW_BW_1D7MHZ   : bw = BW_1P7MHZ; break;
          case Si2183_DD_MODE_PROP_BW_BW_5MHZ     : bw = BW_6MHZ  ; break;
          case Si2183_DD_MODE_PROP_BW_BW_6MHZ     : bw = BW_6MHZ  ; break;
          case Si2183_DD_MODE_PROP_BW_BW_7MHZ     : bw = BW_7MHZ  ; break;
          case Si2183_DD_MODE_PROP_BW_BW_8MHZ     : bw = BW_8MHZ  ; break;
          default: {
            SiTRACE("Si2183_L2_Tune: Invalid dd_mode.bw (%d)\n", front_end->demod->prop->dd_mode.bw);
            SiERROR("Si2183_L2_Tune: Invalid dd_mode.bw\n");
            bw = 8; break;
          }
        }
      }
      if (front_end->demod->prop->dd_mode.bw == Si2183_DD_MODE_PROP_BW_BW_1D7MHZ ) {
          SiLabs_TER_Tuner_DTV_INTERNAL_ZIF_DVBT(front_end->tuner_ter, 1); /* TER tuner dtv_internal_zif.dvbt set to LIF */
      } else {
        if ( (front_end->demod->prop->dd_mode.modulation  == Si2183_DD_MODE_PROP_MODULATION_DVBT )
#ifdef    DEMOD_DVB_T2
           | (front_end->demod->prop->dd_mode.modulation  == Si2183_DD_MODE_PROP_MODULATION_DVBT2)
           | ((front_end->demod->prop->dd_mode.modulation == Si2183_DD_MODE_PROP_MODULATION_AUTO_DETECT   )
            &(front_end->demod->prop->dd_mode.auto_detect == Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_T_T2))
#endif /* DEMOD_DVB_T2 */
          ) {
          SiLabs_TER_Tuner_DTV_INTERNAL_ZIF_DVBT(front_end->tuner_ter, 0); /* TER tuner dtv_internal_zif.dvbt set to ZIF*/
        }
      }
#ifdef    DEMOD_DVB_C2
      if (front_end->demod->prop->dd_mode.modulation == Si2183_DD_MODE_PROP_MODULATION_DVBC2 ) {
          SiLabs_TER_Tuner_DTV_INTERNAL_ZIF_DVBT(front_end->tuner_ter, 1); /* TER tuner dtv_internal_zif.dvbt set to LIF */
      }
#endif /* DEMOD_DVB_C2 */
#ifdef    DEMOD_ISDB_T
      if (front_end->demod->prop->dd_mode.modulation == Si2183_DD_MODE_PROP_MODULATION_ISDBT ) {
          modulation = L1_RF_TER_TUNER_MODULATION_ISDBT;
      }
#endif /* DEMOD_ISDB_T */
#endif /* Si2183_USING_SILABS_TER_TUNER */
      L1_RF_TER_TUNER_Tune       (front_end->tuner_ter , rf);
#ifdef    DEMOD_DVB_T2
      /* Activate FEF management in all cases where the signal can be DVB-T2 */
      if (   (front_end->demod->prop->dd_mode.modulation  == Si2183_DD_MODE_PROP_MODULATION_DVBT2)
          | ((front_end->demod->prop->dd_mode.modulation  == Si2183_DD_MODE_PROP_MODULATION_AUTO_DETECT)
            &(front_end->demod->prop->dd_mode.auto_detect == Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_T_T2))
         ) { Si2183_L2_TER_FEF (front_end, 1); }
#endif /* DEMOD_DVB_T2 */
 #ifdef    INDIRECT_I2C_CONNECTION
      front_end->f_TER_tuner_disable(front_end->callback);
 #endif /* INDIRECT_I2C_CONNECTION */
    }
#endif /* TERRESTRIAL_FRONT_END */

#ifdef    DEMOD_DVB_S_S2_DSS
    if (front_end->demod->media == Si2183_SATELLITE  ) {
 #ifdef    INDIRECT_I2C_CONNECTION
      front_end->f_SAT_tuner_enable(front_end->callback);
 #endif /* INDIRECT_I2C_CONNECTION */
#ifdef    UNICABLE_COMPATIBLE
      if (front_end->lnb_type == UNICABLE_LNB_TYPE_UNICABLE) {
        rf = front_end->f_Unicable_tune(front_end->callback, rf);
        SiTRACE(" Unicable L2_TUNE returning rf=%d\n",rf);
      } else {
#endif /* UNICABLE_COMPATIBLE */
        L1_RF_SAT_TUNER_Tune (front_end->tuner_sat, rf);
#ifdef    UNICABLE_COMPATIBLE
      }
#endif /* UNICABLE_COMPATIBLE */
 #ifdef    INDIRECT_I2C_CONNECTION
      front_end->f_SAT_tuner_disable(front_end->callback);
 #endif /* INDIRECT_I2C_CONNECTION */
    }
#endif /* DEMOD_DVB_S_S2_DSS */

   #ifdef    INDIRECT_I2C_CONNECTION
   #else  /* INDIRECT_I2C_CONNECTION */
    Si2183_L2_Tuner_I2C_Disable(front_end);
   #endif /* INDIRECT_I2C_CONNECTION */
#ifdef   Si2183_FFT_CAPABILITY
    if ( front_end->misc_infos & 0x00001000 ) { Si2183_L2_FFT(front_end, 0, rf); }
#endif /* Si2183_FFT_CAPABILITY */

    return rf;
}
/************************************************************************************************************************
  Si2183_L2_Get_RF function
  Use:        tuner current frequency retrieval function
              Used to retrieve the current RF from the tuner's driver.
  Porting:    Replace the internal TUNER function calls by the final tuner's corresponding calls
  Behavior:   This function does not need to activate the Si2183's I2C switch, as the required value is part of the tuner's structure
  Parameter:  *front_end, the front-end handle
************************************************************************************************************************/
signed   int  Si2183_L2_Get_RF             (Si2183_L2_Context *front_end) {

#ifdef    DEMOD_DVB_T
  if (front_end->demod->media == Si2183_TERRESTRIAL) {
#ifdef    TUNERTER_API
  #ifdef   TUNERTER_SILABS_API
    return (int)L1_RF_TER_TUNER_Get_RF (front_end->tuner_ter);
  #else  /* TUNERTER_SILABS_API */
    return front_end->tuner_ter->cmd->tuner_tune_freq.freq;
  #endif /* TUNERTER_SILABS_API */
#else  /* TUNERTER_API */
    return (int)L1_RF_TER_TUNER_Get_RF (front_end->tuner_ter);
#endif /* TUNERTER_API */
  }
#endif /* DEMOD_DVB_T */

#ifdef    DEMOD_DVB_S_S2_DSS
  if (front_end->demod->media == Si2183_SATELLITE  ) {
    return (int)L1_RF_SAT_TUNER_Get_RF (front_end->tuner_sat);
  }
#endif /* DEMOD_DVB_S_S2_DSS */

  return 0;
}
#ifdef    TERRESTRIAL_FRONT_END
/************************************************************************************************************************
  Si2183_L2_TER_Clock function
  Use:        Terrestrial clock configuration function
              Used to set the terrestrial clock source, input pin and frequency
  Parameter:  clock_source:  where the clock signal comes from.
              possible sources:
                Si2183_Xtal_clock,
                Si2183_TER_Tuner_clock,
                Si2183_SAT_Tuner_clock
  Parameter:  clock_input:   on which pin is the clock received.
              possible inputs:
                44 for Si2183_START_CLK_CMD_CLK_MODE_CLK_CLKIO    (pin 44 for 'single' parts)
                33 for Si2183_START_CLK_CMD_CLK_MODE_CLK_XTAL_IN  (pin 33 for 'single' parts)
                32 for Si2183_START_CLK_CMD_CLK_MODE_XTAL         (Xtal connected on pins 32/33 for 'single' parts, driven by the Si264)
  Parameter:  clock_freq:   clock frequency
              possible frequencies:
                Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_16MHZ
                Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_24MHZ
                Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_27MHZ
  Parameter:  clock_control:   how the TER clock must be controlled
              possible modes:
                Si2183_CLOCK_ALWAYS_ON                             turn clock ON then never switch it off, used when the clock is provided to another part
                Si2183_CLOCK_ALWAYS_OFF                            never switch it on, used when the clock is not going anywhere
                Si2183_CLOCK_MANAGED                               control clock state as before
 ***********************************************************************************************************************/
signed   int  Si2183_L2_TER_Clock          (Si2183_L2_Context *front_end, signed   int clock_source, signed   int clock_input, signed   int clock_freq, signed   int clock_control)
{
  front_end->demod->tuner_ter_clock_source = clock_source;
  switch (clock_input) {
    case 44: {
      front_end->demod->tuner_ter_clock_input  = Si2183_START_CLK_CMD_CLK_MODE_CLK_CLKIO;
      break;
    }
    case 33: {
      front_end->demod->tuner_ter_clock_input  = Si2183_START_CLK_CMD_CLK_MODE_CLK_XTAL_IN;
      break;
    }
    default:
    case 32: {
      front_end->demod->tuner_ter_clock_input  = Si2183_START_CLK_CMD_CLK_MODE_XTAL;
      break;
    }
  }
  front_end->demod->tuner_ter_clock_freq   = clock_freq;
  front_end->demod->tuner_ter_clock_control= clock_control;

  return NO_Si2183_ERROR;
}
/************************************************************************************************************************
  Si2183_L2_TER_AGC function
  Use:        Terrestrial AGC configuration function
              Used to set the terrestrial AGC source, input pin and frequency
  Parameter:  agc1_mode:      not used anymore. Settings will always be applied to AGC2 for TER reception. Always use 0
  Parameter:  agc1_inversion: not used anymore. Settings will always be applied to AGC2 for TER reception. Always use 0
  Parameter:  agc2_mode:  where the TER AGC PWM comes from.
              possible modes:
                0x0: Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_NOT_USED,
                0xA: Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MP_A,
                0xB: Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MP_B,
                0xC: Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MP_C,
                0xD: Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MP_D,
  Parameter:  agc2_inversion: 0/1 to indicate if AGC 2 is inverted or not (depends on the TER tuner and HW design)
  Returns:    0 if no error
 ***********************************************************************************************************************/
signed   int  Si2183_L2_TER_AGC            (Si2183_L2_Context *front_end, signed   int agc1_mode, signed   int agc1_inversion, signed   int agc2_mode, signed   int agc2_inversion)
{
  front_end->demod->cmd->dd_ext_agc_ter.agc_1_mode  = Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MODE_NOT_USED;
  front_end->demod->cmd->dd_ext_agc_ter.agc_1_inv   = Si2183_DD_EXT_AGC_TER_CMD_AGC_1_INV_NOT_INVERTED;
  if (agc2_mode == 0x00) { /* In TER, always use the agc2 internal loop. If settings are on agc1, use them for agc2 (for compatibility purposes with previous versions) */
    switch (agc1_mode) {
      default:
      case 0x0: { front_end->demod->cmd->dd_ext_agc_ter.agc_2_mode  = Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_NOT_USED; break; }
      case 0xA: { front_end->demod->cmd->dd_ext_agc_ter.agc_2_mode  = Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MP_A    ; break; }
      case 0xB: { front_end->demod->cmd->dd_ext_agc_ter.agc_2_mode  = Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MP_B    ; break; }
      case 0xC: { front_end->demod->cmd->dd_ext_agc_ter.agc_2_mode  = Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MP_C    ; break; }
      case 0xD: { front_end->demod->cmd->dd_ext_agc_ter.agc_2_mode  = Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MP_D    ; break; }
    }

    if (agc1_inversion == 0) {
                  front_end->demod->cmd->dd_ext_agc_ter.agc_2_inv   = Si2183_DD_EXT_AGC_TER_CMD_AGC_2_INV_NOT_INVERTED;}
     else {       front_end->demod->cmd->dd_ext_agc_ter.agc_2_inv   = Si2183_DD_EXT_AGC_TER_CMD_AGC_2_INV_INVERTED;    }
  }

  switch (agc2_mode) {
    default:
    case 0x0: { front_end->demod->cmd->dd_ext_agc_ter.agc_2_mode  = Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_NOT_USED; break; }
    case 0xA: { front_end->demod->cmd->dd_ext_agc_ter.agc_2_mode  = Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MP_A    ; break; }
    case 0xB: { front_end->demod->cmd->dd_ext_agc_ter.agc_2_mode  = Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MP_B    ; break; }
    case 0xC: { front_end->demod->cmd->dd_ext_agc_ter.agc_2_mode  = Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MP_C    ; break; }
    case 0xD: { front_end->demod->cmd->dd_ext_agc_ter.agc_2_mode  = Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MP_D    ; break; }
  }
  if (agc2_inversion == 0) {
                front_end->demod->cmd->dd_ext_agc_ter.agc_2_inv   = Si2183_DD_EXT_AGC_TER_CMD_AGC_2_INV_NOT_INVERTED;}
  else {        front_end->demod->cmd->dd_ext_agc_ter.agc_2_inv   = Si2183_DD_EXT_AGC_TER_CMD_AGC_2_INV_INVERTED;}

  if ( (agc1_mode == 0) & (agc2_mode == 0) ) {
    front_end->demod->tuner_ter_agc_control = 0;
  } else {
    front_end->demod->tuner_ter_agc_control = 1;
  }

  return NO_Si2183_ERROR;
}
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    DEMOD_DVB_T2
/************************************************************************************************************************
  Si2183_L2_TER_FEF_CONFIG function
  Use:        TER tuner FEF pin selection function
              Used to select the FEF pin connected to the terrestrial tuner
  Parameter:  *front_end, the front-end handle
  Parameter:  fef_mode, a flag controlling the FEF mode between SLOW_NORMAL_AGC(0), FREEZE_PIN(1)' and SLOW_INITIAL_AGC(2)
  Parameter:  fef_pin: where the FEF signal comes from.
              possible values:
                0x0: Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_NOT_USED
                0xA: Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MP_A
                0xB: Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MP_B
                0xC: Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MP_C
                0xD: Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MP_D
  Parameter:  fef_level, a flag controlling the FEF signal level when active between 'low'(0) and 'high'(1)
  Returns:    1
************************************************************************************************************************/
signed   int   Si2183_L2_TER_FEF_CONFIG    (Si2183_L2_Context  *front_end, signed   int fef_mode, signed   int fef_pin, signed   int fef_level)
{
  switch (fef_mode) {
    default :
    case   0: { front_end->demod->fef_mode = Si2183_FEF_MODE_SLOW_NORMAL_AGC  ; front_end->demod->fef_pin = 0x0    ; front_end->demod->fef_level = 0        ; break; }
    case   1: { front_end->demod->fef_mode = Si2183_FEF_MODE_FREEZE_PIN       ; front_end->demod->fef_pin = fef_pin; front_end->demod->fef_level = fef_level; break; }
    case   2: { front_end->demod->fef_mode = Si2183_FEF_MODE_SLOW_INITIAL_AGC ; front_end->demod->fef_pin = 0x0    ; front_end->demod->fef_level = 0        ; break; }
    case   3: { front_end->demod->fef_mode = Si2183_FEF_MODE_TUNER_AUTO_FREEZE; front_end->demod->fef_pin = 0x0    ; front_end->demod->fef_level = 0        ; break; }
  }
  switch (front_end->demod->fef_pin) {
    default  :
    case 0x0: { front_end->demod->cmd->dvbt2_fef.fef_tuner_flag  = Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_NOT_USED; break; }
    case 0xA: { front_end->demod->cmd->dvbt2_fef.fef_tuner_flag  = Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MP_A    ; break; }
    case 0xB: { front_end->demod->cmd->dvbt2_fef.fef_tuner_flag  = Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MP_B    ; break; }
    case 0xC: { front_end->demod->cmd->dvbt2_fef.fef_tuner_flag  = Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MP_C    ; break; }
    case 0xD: { front_end->demod->cmd->dvbt2_fef.fef_tuner_flag  = Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MP_D    ; break; }
  }
  if (front_end->demod->fef_level == 0) {
                front_end->demod->cmd->dvbt2_fef.fef_tuner_flag_inv  = Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_INV_FEF_LOW ; }
   else {       front_end->demod->cmd->dvbt2_fef.fef_tuner_flag_inv  = Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_INV_FEF_HIGH; }

  return NO_Si2183_ERROR;
}
/************************************************************************************************************************
  Si2183_L2_TER_FEF function
  Use:        TER tuner FEF activation function
              Used to enable/disable the FEF mode in the terrestrial tuner
  Comments:   If the tuner is connected via the demodulator's I2C switch, enabling/disabling the i2c_passthru is required before/after tuning.
  Parameter:  *front_end, the front-end handle
  Parameter:  fef, a flag controlling the selection between FEF 'off'(0) and FEF 'on'(1)
  Returns:    1
************************************************************************************************************************/
signed   int  Si2183_L2_TER_FEF            (Si2183_L2_Context *front_end, signed   int fef)
{
  front_end = front_end; /* To avoid compiler warning if not used */
  SiTRACE("Si2183_L2_TER_FEF %d \n",fef);

  #ifdef    L1_RF_TER_TUNER_DTV_AGC_AUTO_FREEZE
    SiTRACE("TER tuner: AUTO_AGC_FREEZE\n");
    L1_RF_TER_TUNER_DTV_AGC_AUTO_FREEZE(front_end->tuner_ter,fef);
  #endif /* L1_RF_TER_TUNER_DTV_AGC_AUTO_FREEZE */

  #ifdef    L1_RF_TER_TUNER_FEF_MODE_FREEZE_PIN
  if (front_end->demod->fef_mode == Si2183_FEF_MODE_FREEZE_PIN      ) {
    SiTRACE("FEF mode Si2183_FEF_MODE_FREEZE_PIN\n");
    L1_RF_TER_TUNER_FEF_MODE_FREEZE_PIN(front_end->tuner_ter, fef);
  }
  #endif /* L1_RF_TER_TUNER_FEF_MODE_FREEZE_PIN */

  #ifdef    L1_RF_TER_TUNER_FEF_MODE_SLOW_INITIAL_AGC_SETUP
  if (front_end->demod->fef_mode == Si2183_FEF_MODE_SLOW_INITIAL_AGC) {
    SiTRACE("FEF mode Si2183_FEF_MODE_SLOW_INITIAL_AGC (AGC slowed down after tuning)\n");
  }
  #endif /* L1_RF_TER_TUNER_FEF_MODE_SLOW_INITIAL_AGC_SETUP */

  #ifdef    L1_RF_TER_TUNER_FEF_MODE_SLOW_NORMAL_AGC_SETUP
  if (front_end->demod->fef_mode == Si2183_FEF_MODE_SLOW_NORMAL_AGC ) {
    SiTRACE("FEF mode Si2183_FEF_MODE_SLOW_NORMAL_AGC: AGC slowed down\n");
    L1_RF_TER_TUNER_FEF_MODE_SLOW_NORMAL_AGC(front_end->tuner_ter, fef);
  }
  #endif /* L1_RF_TER_TUNER_FEF_MODE_SLOW_NORMAL_AGC_SETUP */
  SiTRACE("Si2183_L2_TER_FEF done\n");
  return 1;
}
/************************************************************************************************************************
  Si2183_L2_TER_FEF_SETUP function
  Use:        TER tuner LPF setting function
              Used to configure the FEF mode in the terrestrial tuner
  Comments:   If the tuner is connected via the demodulator's I2C switch, enabling/disabling the i2c_passthru is required before/after tuning.
  Behavior:   This function closes the Si2183's I2C switch then sets the TER FEF mode and finally reopens the I2C switch
  Parameter:  *front_end, the front-end handle
  Parameter:  fef, a flag controlling the selection between FEF 'off'(0) and FEF 'on'(1)
  Returns:    1
************************************************************************************************************************/
signed   int  Si2183_L2_TER_FEF_SETUP      (Si2183_L2_Context *front_end, signed   int fef)
{
  SiTRACE("Si2183_L2_TER_FEF_SETUP %d\n",fef);

  #ifdef    L1_RF_TER_TUNER_FEF_MODE_FREEZE_PIN_SETUP
  if (front_end->demod->fef_mode == Si2183_FEF_MODE_FREEZE_PIN      ) {
    SiTRACE("FEF mode Si2183_FEF_MODE_FREEZE_PIN\n");
    SiLabs_TER_Tuner_FEF_FREEZE_PIN_SETUP(front_end->tuner_ter, front_end->demod->fef_level);
  }
  #endif /* L1_RF_TER_TUNER_FEF_MODE_FREEZE_PIN_SETUP */

  #ifdef    L1_RF_TER_TUNER_FEF_MODE_SLOW_INITIAL_AGC_SETUP
  if (front_end->demod->fef_mode == Si2183_FEF_MODE_SLOW_INITIAL_AGC) {
    SiTRACE("FEF mode Si2183_FEF_MODE_SLOW_INITIAL_AGC (AGC slowed down after tuning)\n");
    L1_RF_TER_TUNER_FEF_MODE_SLOW_INITIAL_AGC_SETUP(front_end->tuner_ter, fef);
  }
  #endif /* L1_RF_TER_TUNER_FEF_MODE_SLOW_INITIAL_AGC_SETUP */

  #ifdef    L1_RF_TER_TUNER_FEF_MODE_SLOW_NORMAL_AGC_SETUP
  if (front_end->demod->fef_mode == Si2183_FEF_MODE_SLOW_NORMAL_AGC ) {
    SiTRACE("FEF mode Si2183_FEF_MODE_SLOW_NORMAL_AGC: AGC slowed down\n");
    L1_RF_TER_TUNER_FEF_MODE_SLOW_NORMAL_AGC_SETUP(front_end->tuner_ter, fef);
  }
  #endif /* L1_RF_TER_TUNER_FEF_MODE_SLOW_NORMAL_AGC */

  Si2183_L2_TER_FEF(front_end, fef);

  SiTRACE("Si2183_L2_TER_FEF_SETUP done\n");
  return 1;
}
#endif /* DEMOD_DVB_T2 */
#ifdef    SATELLITE_FRONT_END
/************************************************************************************************************************
  Si2183_L2_SAT_Clock function
  Use:        Satellite clock configuration function
              Used to set the satellite clock source, input pin and frequency
  Returns:    0 if no error
  Parameter:  clock_source:  where the clock signal comes from.
              possible sources:
                Si2183_Xtal_clock,
                Si2183_TER_Tuner_clock,
                Si2183_SAT_Tuner_clock
  Parameter:  clock_input:   on which pin is the clock received.
              possible inputs:
                44 for Si2183_START_CLK_CMD_CLK_MODE_CLK_CLKIO    (pin 44 for 'single' parts)
                33 for Si2183_START_CLK_CMD_CLK_MODE_CLK_XTAL_IN  (pin 33 for 'single' parts)
                32 for Si2183_START_CLK_CMD_CLK_MODE_XTAL         (Xtal connected on pins 32/33 for 'single' parts, driven by the Si264)
  Parameter:  clock_freq:   clock frequency
              possible frequencies:
                Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_16MHZ
                Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_24MHZ
                Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_27MHZ
  Parameter:  clock_control:   how the SAT clock must be controlled
              possible modes:
                Si2183_CLOCK_ALWAYS_ON                             turn clock ON then never switch it off, used when the clock is provided to another part
                Si2183_CLOCK_ALWAYS_OFF                            never switch it on, used when the clock is not going anywhere
                Si2183_CLOCK_MANAGED                               control clock state as before
 ***********************************************************************************************************************/
signed   int  Si2183_L2_SAT_Clock          (Si2183_L2_Context *front_end, signed   int clock_source, signed   int clock_input, signed   int clock_freq, signed   int clock_control)
{
  front_end->demod->tuner_sat_clock_source = clock_source;
  front_end->demod->tuner_sat_clock_input  = Si2183_START_CLK_CMD_CLK_MODE_XTAL;
  switch (clock_input) {
    case 44: { /* Si2183_START_CLK_CMD_CLK_MODE_CLK_CLKIO   */
      front_end->demod->tuner_sat_clock_input  = Si2183_START_CLK_CMD_CLK_MODE_CLK_CLKIO;
      break;
    }
    case 33: { /* Si2183_START_CLK_CMD_CLK_MODE_CLK_XTAL_IN */
      front_end->demod->tuner_sat_clock_input  = Si2183_START_CLK_CMD_CLK_MODE_CLK_XTAL_IN;
      break;
    }
    default:
    case 32: { /* Si2183_START_CLK_CMD_CLK_MODE_XTAL        */
      front_end->demod->tuner_sat_clock_input   = Si2183_START_CLK_CMD_CLK_MODE_XTAL;
      break;
    }
  }
  front_end->demod->tuner_sat_clock_freq   = clock_freq;
  front_end->demod->tuner_sat_clock_control= clock_control;

  return NO_Si2183_ERROR;
}
/************************************************************************************************************************
  Si2183_L2_SAT_AGC function
  Use:        Satellite AGC configuration function
              Used to set the Satellite AGC source, input pin and frequency
  Parameter:  agc1_mode:  where the SAT AGC PWM comes from.
              possible modes:
                0x0: Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_NOT_USED,
                0xA: Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MP_A,
                0xB: Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MP_B,
                0xC: Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MP_C,
                0xD: Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MP_D,
  Parameter:  agc1_inversion: 0/1 to indicate if AGC 1 is inverted or not (depends on the SAT tuner and HW design)
  Parameter:  agc2_mode:      not used anymore. Settings will always be applied to AGC1 for SAT reception. Always use 0
  Parameter:  agc2_inversion: not used anymore. Settings will always be applied to AGC1 for SAT reception. Always use 0
  Returns:    0 if no error
 ***********************************************************************************************************************/
signed   int  Si2183_L2_SAT_AGC            (Si2183_L2_Context *front_end, signed   int agc1_mode, signed   int agc1_inversion, signed   int agc2_mode, signed   int agc2_inversion)
{
  front_end->demod->cmd->dd_ext_agc_sat.agc_2_mode  = Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MODE_NOT_USED;
  front_end->demod->cmd->dd_ext_agc_sat.agc_2_inv   = Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_INV_NOT_INVERTED;
  if (agc1_mode == 0x00) { /* In SAT, always use the agc1 internal loop. If settings are on agc2, use them for agc1 (for compatibility purposes with previous versions) */
    switch (agc2_mode) {
      default  :
      case 0x0: { front_end->demod->cmd->dd_ext_agc_sat.agc_1_mode  = Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_NOT_USED; break; }
      case 0xA: { front_end->demod->cmd->dd_ext_agc_sat.agc_1_mode  = Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MP_A    ; break; }
      case 0xB: { front_end->demod->cmd->dd_ext_agc_sat.agc_1_mode  = Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MP_B    ; break; }
      case 0xC: { front_end->demod->cmd->dd_ext_agc_sat.agc_1_mode  = Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MP_C    ; break; }
      case 0xD: { front_end->demod->cmd->dd_ext_agc_sat.agc_1_mode  = Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MP_D    ; break; }
    }
    if (agc2_inversion == 0) {
                  front_end->demod->cmd->dd_ext_agc_sat.agc_1_inv   = Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_INV_NOT_INVERTED; }
    else {        front_end->demod->cmd->dd_ext_agc_sat.agc_1_inv   = Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_INV_INVERTED;     }
  }

  switch (agc1_mode) {
    default  :
    case 0x0: { front_end->demod->cmd->dd_ext_agc_sat.agc_1_mode  = Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_NOT_USED; break; }
    case 0xA: { front_end->demod->cmd->dd_ext_agc_sat.agc_1_mode  = Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MP_A    ; break; }
    case 0xB: { front_end->demod->cmd->dd_ext_agc_sat.agc_1_mode  = Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MP_B    ; break; }
    case 0xC: { front_end->demod->cmd->dd_ext_agc_sat.agc_1_mode  = Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MP_C    ; break; }
    case 0xD: { front_end->demod->cmd->dd_ext_agc_sat.agc_1_mode  = Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MP_D    ; break; }
  }
  if (agc1_inversion == 0) {
                front_end->demod->cmd->dd_ext_agc_sat.agc_1_inv   = Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_INV_NOT_INVERTED; }
  else {        front_end->demod->cmd->dd_ext_agc_sat.agc_1_inv   = Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_INV_INVERTED;     }

  return NO_Si2183_ERROR;
}
/************************************************************************************************************************
  Si2183_L2_SAT_Spectrum function
  Use:        Satellite IF configuration function
              Used to store the satellite spectrum inversion flag
  Parameter:  spectrum_inversion:   a flag indicating if the SAT signal appears inverted.
               This situation is possible if there is an I/Q swap in the HW design, for easier routing
               It is perfectly OK to do that to route easily, but the SW needs to be informed of this inversion.
               NB: The additional inversion added by Unicable equipement should not be taken into account here
                    The spectrum_inversion set here corresponds to the 'normal' mode
  Returns:    0 if no error
 ***********************************************************************************************************************/
signed   int  Si2183_L2_SAT_Spectrum       (Si2183_L2_Context *front_end, signed   int spectrum_inversion)
{
  SiTRACE("Si2183_L2_SAT_Spectrum spectrum_inversion %d\n", spectrum_inversion);
  front_end->satellite_spectrum_inversion   = spectrum_inversion;
  return NO_Si2183_ERROR;
}
/************************************************************************************************************************
  Si2183_L2_SAT_LPF function
  Use:        SAT tuner LPF setting function
              Used to set the satellite low pass filter
  Comments:   If the tuner is connected via the demodulator's I2C switch, enabling/disabling the i2c_passthru is required before/after tuning.
  Behavior:   This function closes the Si2183's I2C switch then sets the SAT lpf and finally reopens the I2C switch
  Parameter:  *front_end, the front-end handle
  Parameter:  lph_khz, the low_pass filter frequency
  Returns:    the final value
************************************************************************************************************************/
signed   int  Si2183_L2_SAT_LPF            (Si2183_L2_Context   *front_end, signed   int lpf_khz)
{
  signed   int ret;
  ret = 0;
  front_end = front_end; /* To avoid compiler warning if not used */
  lpf_khz   = lpf_khz;   /* To avoid compiler warning if not used */
 #ifdef    INDIRECT_I2C_CONNECTION
  front_end->f_SAT_tuner_enable(front_end->callback);
 #else  /* INDIRECT_I2C_CONNECTION */
  Si2183_L2_Tuner_I2C_Enable(front_end);
 #endif /* INDIRECT_I2C_CONNECTION */
  ret  = (int)L1_RF_SAT_TUNER_LPF(front_end->tuner_sat, lpf_khz);
 #ifdef    INDIRECT_I2C_CONNECTION
  front_end->f_SAT_tuner_disable(front_end->callback);
 #else  /* INDIRECT_I2C_CONNECTION */
  Si2183_L2_Tuner_I2C_Disable(front_end);
 #endif /* INDIRECT_I2C_CONNECTION */
  return ret;
}
/***********************************************************************************************************************
  Si2183_L2_prepare_diseqc_sequence function
  Use:      DiSEqC sequence preparation function
            Used to prepare a DiSEqC sequence, checking the bus readiness and preparing all registers
  Returns:      0 if OK
  Parameter:  *front_end, the front-end handle
  Parameter:   sequence_length  the number of bytes to send
  Parameter:   sequenceBuffer   a buffer containing the DiSeqEc bytes
  Parameter:   cont_tone  a flag for continuous tone control: 0 = OFF, 1 = ON. When set to ON, a continuous tone is present before and after the message or the sequence of messages and/or tone burst.
  Parameter:   tone_burst a flag for tone burst control: 0 = OFF, 1 = ON. Used to send a Tone Burst sequence.
  Parameter:   burst_sel  a flag for tone burst selection: 0 = SA, 1 = SB. Selects which satellite is selected in the Tone Burst sequence.
  Parameter:   end_seq    a flag for end of sequence control: 0 = NOT_END, 1 = END. When set to END, Diseqc sequence is resumed after the current message. When set to NOT_END, current message is not the end of the full sequence. It's used in the case of sequence composed of repeated messages
 ***********************************************************************************************************************/
signed   int  Si2183_L2_prepare_diseqc_sequence(Si2183_L2_Context *front_end, signed   int sequence_length, unsigned char *sequenceBuffer, unsigned char cont_tone, unsigned char tone_burst, unsigned char burst_sel, unsigned char end_seq)
{
  unsigned char   msg_byte1;
  unsigned char   msg_byte2;
  unsigned char   msg_byte3;
  unsigned char   msg_byte4;
  unsigned char   msg_byte5;
  unsigned char   msg_byte6;
  signed   int    i;
  signed   int    start_time;
  signed   int    bus_state;

  SiTRACE("Si2183_L2_prepare_diseqc_sequence(front_end->Si2183_FE, sequence_length %d, sequence_buffer, cont_tone %d, tone_burst %d, burst_sel %d, end_seq %d);\n", sequence_length, cont_tone, tone_burst, burst_sel, end_seq);

  /* Waiting for DiSeqC bus readiness for max 72 ms (each DiSEqC byte lasts 12 ms, and the max sequence_length is 6) */
  Si2183_L1_DD_DISEQC_STATUS(front_end->demod, Si2183_DD_DISEQC_STATUS_CMD_LISTEN_NO_CHANGE);
  bus_state = front_end->demod->rsp->dd_diseqc_status.bus_state;
  start_time = system_time();
  while ( bus_state != Si2183_DD_DISEQC_STATUS_RESPONSE_BUS_STATE_READY ) {
    if ((system_time() - start_time) > 200 ) { break; }
    system_wait(12);
    Si2183_L1_DD_DISEQC_STATUS(front_end->demod, Si2183_DD_DISEQC_STATUS_CMD_LISTEN_NO_CHANGE);
    bus_state = front_end->demod->rsp->dd_diseqc_status.bus_state;
  }
  if ( front_end->demod->rsp->dd_diseqc_status.bus_state != Si2183_DD_DISEQC_STATUS_RESPONSE_BUS_STATE_READY ) {
    SiTRACE ("DiSeqC bus not ready to send a message\n");
    SiERROR ("DiSeqC bus not ready to send a message\n");
    return ERROR_Si2183_DISEQC_BUS_NOT_READY;
  }

  i = 0;

  if (i<sequence_length) { msg_byte1 = sequenceBuffer[i++];} else {msg_byte1 = 0x00;}
  if (i<sequence_length) { msg_byte2 = sequenceBuffer[i++];} else {msg_byte2 = 0x00;}
  if (i<sequence_length) { msg_byte3 = sequenceBuffer[i++];} else {msg_byte3 = 0x00;}
  if (i<sequence_length) { msg_byte4 = sequenceBuffer[i++];} else {msg_byte4 = 0x00;}
  if (i<sequence_length) { msg_byte5 = sequenceBuffer[i++];} else {msg_byte5 = 0x00;}
  if (i<sequence_length) { msg_byte6 = sequenceBuffer[i++];} else {msg_byte6 = 0x00;}


  front_end->demod->cmd->dd_diseqc_send.cont_tone  = cont_tone;
  front_end->demod->cmd->dd_diseqc_send.tone_burst = tone_burst;
  front_end->demod->cmd->dd_diseqc_send.burst_sel  = burst_sel;
  front_end->demod->cmd->dd_diseqc_send.end_seq    = end_seq;
  front_end->demod->cmd->dd_diseqc_send.msg_length = sequence_length;
  front_end->demod->cmd->dd_diseqc_send.msg_byte1  = msg_byte1;
  front_end->demod->cmd->dd_diseqc_send.msg_byte2  = msg_byte2;
  front_end->demod->cmd->dd_diseqc_send.msg_byte3  = msg_byte3;
  front_end->demod->cmd->dd_diseqc_send.msg_byte4  = msg_byte4;
  front_end->demod->cmd->dd_diseqc_send.msg_byte5  = msg_byte5;
  front_end->demod->cmd->dd_diseqc_send.msg_byte6  = msg_byte6;

  return NO_Si2183_ERROR;
}
/***********************************************************************************************************************
  Si2183_L2_trigger_diseqc_sequence function
  Use:      DiSEqC sequence send function
            Used to send a DiSEqC sequence prepared using Si2167_L1_Demod_prepare_diseqc_sequence
  Parameter:   *demod          the demod handle
  Porting:     This can be removed in not using SAT standards or not using DiSEqC
  Registers:   ds_send
 ***********************************************************************************************************************/
signed   int  Si2183_L2_trigger_diseqc_sequence(Si2183_L2_Context *front_end)
{
  return Si2183_L1_DD_DISEQC_SEND (front_end->demod, 1,
                            front_end->demod->cmd->dd_diseqc_send.cont_tone,
                            front_end->demod->cmd->dd_diseqc_send.tone_burst,
                            front_end->demod->cmd->dd_diseqc_send.burst_sel,
                            front_end->demod->cmd->dd_diseqc_send.end_seq,
                            front_end->demod->cmd->dd_diseqc_send.msg_length,
                            front_end->demod->cmd->dd_diseqc_send.msg_byte1,
                            front_end->demod->cmd->dd_diseqc_send.msg_byte2,
                            front_end->demod->cmd->dd_diseqc_send.msg_byte3,
                            front_end->demod->cmd->dd_diseqc_send.msg_byte4,
                            front_end->demod->cmd->dd_diseqc_send.msg_byte5,
                            front_end->demod->cmd->dd_diseqc_send.msg_byte6);
}
/***********************************************************************************************************************
  Si2183_L2_send_diseqc_sequence function
  Use:      DiSEqC sequence send function
            Used to send a DiSEqC sequence
  Returns:      0 if OK
  Parameter:  *front_end, the front-end handle
  Parameter:   sequence_length  the number of bytes to send
  Parameter:   sequenceBuffer   a buffer containing the DiSeqEc bytes
  Parameter:   cont_tone  a flag for continuous tone control: 0 = OFF, 1 = ON. When set to ON, a continuous tone is present before and after the message or the sequence of messages and/or tone burst.
  Parameter:   tone_burst a flag for tone burst control: 0 = OFF, 1 = ON. Used to send a Tone Burst sequence.
  Parameter:   burst_sel  a flag for tone burst selection: 0 = SA, 1 = SB. Selects which satellite is selected in the Tone Burst sequence.
  Parameter:   end_seq    a flag for end of sequence control: 0 = NOT_END, 1 = END. When set to END, Diseqc sequence is resumed after the current message. When set to NOT_END, current message is not the end of the full sequence. It's used in the case of sequence composed of repeated messages
 ***********************************************************************************************************************/
signed   int  Si2183_L2_send_diseqc_sequence(Si2183_L2_Context *front_end, signed   int sequence_length, unsigned char *sequenceBuffer, unsigned char cont_tone, unsigned char tone_burst, unsigned char burst_sel, unsigned char end_seq)
{
  signed   int i;
  signed   int start_time;
  signed   int bus_state;

  SiTRACE("Si2183_L2_send_diseqc_sequence(front_end->Si2183_FE, sequence_length %d, sequence_buffer, cont_tone %d, tone_burst %d, burst_sel %d, end_seq %d);\n", sequence_length, cont_tone, tone_burst, burst_sel, end_seq);

  /* Waiting for DiSeqC bus readiness for max 72 ms (each DiSEqC byte lasts 12 ms, and the max sequence_length is 6) */
  Si2183_L1_DD_DISEQC_STATUS(front_end->demod, Si2183_DD_DISEQC_STATUS_CMD_LISTEN_NO_CHANGE);
  bus_state = front_end->demod->rsp->dd_diseqc_status.bus_state;
  start_time = system_time();
  while ( bus_state != Si2183_DD_DISEQC_STATUS_RESPONSE_BUS_STATE_READY ) {
    if ((system_time() - start_time) > 200 ) { break; }
    system_wait(12);
    Si2183_L1_DD_DISEQC_STATUS(front_end->demod, Si2183_DD_DISEQC_STATUS_CMD_LISTEN_NO_CHANGE);
    bus_state = front_end->demod->rsp->dd_diseqc_status.bus_state;
  }
  if ( front_end->demod->rsp->dd_diseqc_status.bus_state != Si2183_DD_DISEQC_STATUS_RESPONSE_BUS_STATE_READY ) {
    SiTRACE ("DiSeqC bus not ready to send a message\n");
    SiERROR ("DiSeqC bus not ready to send a message\n");
    return ERROR_Si2183_DISEQC_BUS_NOT_READY;
  }

  i = 0;

  front_end->demod->cmd->dd_diseqc_send.enable          = 1;
  front_end->demod->cmd->dd_diseqc_send.cont_tone       = cont_tone;
  front_end->demod->cmd->dd_diseqc_send.tone_burst      = tone_burst;
  front_end->demod->cmd->dd_diseqc_send.burst_sel       = burst_sel;
  front_end->demod->cmd->dd_diseqc_send.end_seq         = end_seq;
  front_end->demod->cmd->dd_diseqc_send.msg_length      = sequence_length;

  if (i<sequence_length) { front_end->demod->cmd->dd_diseqc_send.msg_byte1 = sequenceBuffer[i++];} else {front_end->demod->cmd->dd_diseqc_send.msg_byte1 = 0x00;}
  if (i<sequence_length) { front_end->demod->cmd->dd_diseqc_send.msg_byte2 = sequenceBuffer[i++];} else {front_end->demod->cmd->dd_diseqc_send.msg_byte2 = 0x00;}
  if (i<sequence_length) { front_end->demod->cmd->dd_diseqc_send.msg_byte3 = sequenceBuffer[i++];} else {front_end->demod->cmd->dd_diseqc_send.msg_byte3 = 0x00;}
  if (i<sequence_length) { front_end->demod->cmd->dd_diseqc_send.msg_byte4 = sequenceBuffer[i++];} else {front_end->demod->cmd->dd_diseqc_send.msg_byte4 = 0x00;}
  if (i<sequence_length) { front_end->demod->cmd->dd_diseqc_send.msg_byte5 = sequenceBuffer[i++];} else {front_end->demod->cmd->dd_diseqc_send.msg_byte5 = 0x00;}
  if (i<sequence_length) { front_end->demod->cmd->dd_diseqc_send.msg_byte6 = sequenceBuffer[i++];} else {front_end->demod->cmd->dd_diseqc_send.msg_byte6 = 0x00;}

  return Si2183_L1_DD_DISEQC_SEND            (front_end->demod, 1, cont_tone, tone_burst, burst_sel, end_seq, sequence_length, front_end->demod->cmd->dd_diseqc_send.msg_byte1, front_end->demod->cmd->dd_diseqc_send.msg_byte2, front_end->demod->cmd->dd_diseqc_send.msg_byte3, front_end->demod->cmd->dd_diseqc_send.msg_byte4, front_end->demod->cmd->dd_diseqc_send.msg_byte5, front_end->demod->cmd->dd_diseqc_send.msg_byte6);
}
/***********************************************************************************************************************
  Si2183_L2_read_diseqc_reply function
  Use:      DiSEqC reply message read function
            Used to read a DiSEqC message
  Returns:      0 if OK
  Parameter:  *front_end, the front-end handle
  Parameter:  *reply_length a pointer to the number of bytes in the reply
  Parameter:   replyBuffer   a buffer used to store the DiSeqEc bytes
               NOTE: This length being unknown at the time of calling, a 3 bytes buffer MUST be allocated by the caller
 ***********************************************************************************************************************/
signed   int  Si2183_L2_read_diseqc_reply   (Si2183_L2_Context *front_end, signed   int *reply_length, unsigned char *replyBuffer)
{
  signed   int return_code;
  signed   int i;
  i = 0;
  if ( (return_code = Si2183_L1_DD_DISEQC_STATUS(front_end->demod, Si2183_DD_DISEQC_STATUS_CMD_LISTEN_NO_CHANGE) ) == NO_Si2183_ERROR) {
    *reply_length = front_end->demod->rsp->dd_diseqc_status.reply_length;
    if (i<*reply_length) { replyBuffer[i] = front_end->demod->rsp->dd_diseqc_status.reply_byte1; i++;}
    if (i<*reply_length) { replyBuffer[i] = front_end->demod->rsp->dd_diseqc_status.reply_byte2; i++;}
    if (i<*reply_length) { replyBuffer[i] = front_end->demod->rsp->dd_diseqc_status.reply_byte3; i++;}
    return return_code;
  }
  return  -1 /* To Be Defined */;
}
#endif /* SATELLITE_FRONT_END */
/************************************************************************************************************************
  NAME: Si2183_L2_Trace_Scan_Status
  DESCRIPTION: traces the scan_status
  Parameter:  Pointer to Si2183 Context
  Returns:    void
************************************************************************************************************************/
const char *Si2183_L2_Trace_Scan_Status  (signed   int scan_status)
{
    switch (scan_status) {
      case  Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_ANALOG_CHANNEL_FOUND  : { return "ANALOG  CHANNEL_FOUND"; break; }
      case  Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_DIGITAL_CHANNEL_FOUND : { return "DIGITAL CHANNEL_FOUND"; break; }
      case  Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_DEBUG                 : { return "DEBUG"                ; break; }
      case  Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_ERROR                 : { return "ERROR"                ; break; }
      case  Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_ENDED                 : { return "ENDED"                ; break; }
      case  Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_IDLE                  : { return "IDLE"                 ; break; }
      case  Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_SEARCHING             : { return "SEARCHING"            ; break; }
      case  Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_TUNE_REQUEST          : { return "TUNE_REQUEST"         ; break; }
      default                                                             : { return "Unknown!"             ; break; }
    }
}
/************************************************************************************************************************
  NAME: Si2183_L2_Set_Invert_Spectrum
  DESCRIPTION: return the required invert_spectrum value depending on the settings:
              front_end->demod->media
              front_end->satellite_spectrum_inversion
              front_end->lnb_type
              front_end->unicable_spectrum_inversion

  Parameter:  Pointer to Si2183 Context
  Returns:    the required invert_spectrum value
************************************************************************************************************************/
unsigned char Si2183_L2_Set_Invert_Spectrum (Si2183_L2_Context *front_end)
{
  unsigned char inversion;
  inversion = 0; /* to avoid compile error */
#ifdef    TERRESTRIAL_FRONT_END
  if (front_end->demod->media == Si2183_TERRESTRIAL) {
    inversion = Si2183_DD_MODE_PROP_INVERT_SPECTRUM_NORMAL;
  }
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    DEMOD_DVB_S_S2_DSS
  if (front_end->demod->media == Si2183_SATELLITE  ) {
    inversion = front_end->satellite_spectrum_inversion;
#ifdef   UNICABLE_COMPATIBLE
    if (front_end->lnb_type == UNICABLE_LNB_TYPE_UNICABLE) {
      if (front_end->unicable_spectrum_inversion) inversion = !inversion;
    }
#endif /* UNICABLE_COMPATIBLE */
  }
#endif /* DEMOD_DVB_S_S2_DSS */
  return inversion;
}
/************************************************************************************************************************
  NAME: Si2183_L2_Channel_Seek_Init
  DESCRIPTION: logs the seek parameters in the context structure
  Programming Guide Reference:    Flowchart TBD (Channel Scan flowchart)
              standards where the parameter is used:     T   T2    C MCNS   C2    S   S2   DSS  ATV
  Parameter:  front_end Pointer to Si2183 Context        x    x    x    x    x    x    x     x    x
  Parameter:  rangeMin     starting Frequency Hz         x    x    x    x    x    x    x     x    x
  Parameter:  rangeMax     ending Frequency Hz           x    x    x    x    x    x    x     x    x
  Parameter:  seekBWHz     Signal Bandwidth (for T/T2)   x    x
  Parameter:  seekStepHz   Frequency step in Hz          x    x
  Parameter:  minSRbps     minimum symbol rate in Baud             x    x         x    x     x
  Parameter:  maxSRbps     maximum symbol rate in Baud             x    x         x    x     x
  Parameter:  minRSSIdBm   min RSSI dBm                  x    x                                   x
  Parameter:  maxRSSIdBm   max RSSI dBm                  x    x                                   x
  Parameter:  minSNRHalfdB min SNR 1/2 dB                x    x                                   x
  Parameter:  maxSNRHalfdB max SNR 1/2 dB                x    x                                   x
  Returns:    0 if successful, otherwise an error.
************************************************************************************************************************/
signed   int  Si2183_L2_Channel_Seek_Init  (Si2183_L2_Context *front_end, signed   int rangeMin, signed   int rangeMax, signed   int seekBWHz, signed   int seekStepHz, signed   int minSRbps, signed   int maxSRbps, signed   int minRSSIdBm, signed   int maxRSSIdBm, signed   int minSNRHalfdB, signed   int maxSNRHalfdB)
{
  signed   int modulation;
  modulation = 0; /* to avoid compiler error */
  Si2183_L1_GET_REV(front_end->demod);
  SiTRACE("Si21%02d", front_end->demod->rsp->get_rev.pn);
  if ((front_end->demod->rsp->get_rev.mcm_die) != Si2183_GET_REV_RESPONSE_MCM_DIE_SINGLE) {  SiTRACE("2");  }
  if (front_end->demod->rsp->get_rev.chiprev == Si2183_PART_INFO_RESPONSE_CHIPREV_A) {
      SiTRACE(" A");
  } else if (front_end->demod->rsp->get_rev.chiprev == Si2183_PART_INFO_RESPONSE_CHIPREV_B) {
      SiTRACE(" B");
  } else if (front_end->demod->rsp->get_rev.chiprev == Si2183_PART_INFO_RESPONSE_CHIPREV_C) {
      SiTRACE(" C");
  } else if (front_end->demod->rsp->get_rev.chiprev == Si2183_PART_INFO_RESPONSE_CHIPREV_D) {
      SiTRACE(" D");
  } else {
      SiTRACE(" chiprev %d", front_end->demod->rsp->get_rev.chiprev);
  }
  SiTRACE(" ROM %d NVM %c_%cb%d ", front_end->demod->rsp->part_info.romid
         , front_end->demod->rsp->part_info.pmajor
         , front_end->demod->rsp->part_info.pminor
         , front_end->demod->rsp->part_info.pbuild
         );
  if (front_end->demod->rsp->get_rev.mcm_die == Si2183_GET_REV_RESPONSE_MCM_DIE_DIE_A) {
      SiTRACE(" die A");
  } else if (front_end->demod->rsp->get_rev.mcm_die == Si2183_GET_REV_RESPONSE_MCM_DIE_DIE_B) {
      SiTRACE(" die B");
  }
  SiTRACE(" Running FW %c_%cb%d\n", front_end->demod->rsp->get_rev.cmpmajor
         , front_end->demod->rsp->get_rev.cmpminor
         , front_end->demod->rsp->get_rev.cmpbuild
          );
#ifdef    TERRESTRIAL_FRONT_END
  if (front_end->demod->media == Si2183_TERRESTRIAL) {
    SiTRACE("media TERRESTRIAL\n");
    front_end->tuneUnitHz   =    1;
  }
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    DEMOD_DVB_S_S2_DSS
  if (front_end->demod->media == Si2183_SATELLITE  ) {
    SiTRACE("media SATELLITE\n");
    front_end->tuneUnitHz   = 1000;
   /* Set SAT tuner LPF to max to allow blindscan (in kHz) */
    Si2183_L2_SAT_LPF(front_end, 100000);
  }
#endif /* DEMOD_DVB_S_S2_DSS */
  SiTRACE ("blindscan_interaction >> (init  ) Si2183_L1_SCAN_CTRL( front_end->demod, Si2183_SCAN_CTRL_CMD_ACTION_ABORT)\n");
  Si2183_L1_SCAN_CTRL (front_end->demod, Si2183_SCAN_CTRL_CMD_ACTION_ABORT , 0);
  /* Check detection standard based on dd_mode.modulation and dd_mode.auto_detect */
  SiTRACE("standard %d, dd_mode.modulation %d, dd_mode.auto_detect %d\n",  front_end->standard, front_end->demod->prop->dd_mode.modulation, front_end->demod->prop->dd_mode.auto_detect);
  switch (front_end->demod->prop->dd_mode.modulation) {
    case Si2183_DD_MODE_PROP_MODULATION_AUTO_DETECT : {
      switch (front_end->demod->prop->dd_mode.auto_detect) {
#ifdef    DEMOD_DVB_S_S2_DSS
        case Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_S_S2     : {
          modulation = Si2183_DD_MODE_PROP_MODULATION_DVBS2;
          break;
        }
        case Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_S_S2_DSS : {
          modulation = Si2183_DD_MODE_PROP_MODULATION_DSS;
          break;
        }
#endif /* DEMOD_DVB_S_S2_DSS */
#ifdef    DEMOD_DVB_T2
        case Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_T_T2     : {
          modulation = Si2183_DD_MODE_PROP_MODULATION_DVBT2;
          break;
        }
#endif /* DEMOD_DVB_T2 */
        default : {
          SiTRACE("AUTO DETECT '%d' is not managed by Si2183_L2_Channel_Seek_Init\n", front_end->demod->prop->dd_mode.auto_detect);
          break;
        }
      }
      break;
    }
#ifdef    DEMOD_DVB_S_S2_DSS
    case Si2183_DD_MODE_PROP_MODULATION_DSS  :
    case Si2183_DD_MODE_PROP_MODULATION_DVBS :
    case Si2183_DD_MODE_PROP_MODULATION_DVBS2: {
      modulation = front_end->demod->prop->dd_mode.modulation;
      break;
    }
#endif /* DEMOD_DVB_S_S2_DSS */
#ifdef    DEMOD_DVB_C
    case Si2183_DD_MODE_PROP_MODULATION_DVBC :
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_C2
    case Si2183_DD_MODE_PROP_MODULATION_DVBC2:
#endif /* DEMOD_DVB_C2 */
#ifdef    DEMOD_DVB_T2
    case Si2183_DD_MODE_PROP_MODULATION_DVBT2:
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_ISDB_T
    case Si2183_DD_MODE_PROP_MODULATION_ISDBT:
#endif /* DEMOD_ISDB_T */
#ifdef    DEMOD_DVB_T
    case Si2183_DD_MODE_PROP_MODULATION_DVBT : {
      modulation = front_end->demod->prop->dd_mode.modulation;
      break;
    }
#endif /* DEMOD_DVB_T */
    default : {
      SiTRACE("'%d' modulation (%s) is not managed by Si2183_L2_Channel_Seek_Init\n", front_end->demod->prop->dd_mode.modulation, Si2183_standardName(front_end->demod->prop->dd_mode.modulation));
      return ERROR_Si2183_ERR;
      break;
    }
  }
  SiTRACE("Si2183_L2_Channel_Seek_Init for %s (%d)\n", Si2183_standardName(modulation), modulation );
  switch (modulation) {
#ifdef    DEMOD_DVB_S_S2_DSS
    case Si2183_DD_MODE_PROP_MODULATION_DSS  :
    case Si2183_DD_MODE_PROP_MODULATION_DVBS :
    case Si2183_DD_MODE_PROP_MODULATION_DVBS2: {
      if (front_end->auto_detect_SAT==1) {
        front_end->demod->prop->dd_mode.modulation  = Si2183_DD_MODE_PROP_MODULATION_AUTO_DETECT;
        /* Trick to avoid slowing down AUTO SAT mode when not using DSS: */
        /*  AUTO_DVB_S_S2_DSS is only used if the input standard is DSS  */
        if (modulation == Si2183_DD_MODE_PROP_MODULATION_DSS) {
          front_end->demod->prop->dd_mode.auto_detect = Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_S_S2_DSS;
        } else {
          front_end->demod->prop->dd_mode.auto_detect = Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_S_S2;
        }
      }
      if (front_end->demod->MIS_capability) {
        Si2183_L1_DVBS2_STREAM_SELECT  (front_end->demod, 0, Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_SEL_MODE_AUTO);
      }
      SiTRACE("DVB-S AFC range %d DVB-S2 AFC range %d\n", front_end->demod->prop->dvbs_afc_range.range_khz, front_end->demod->prop->dvbs2_afc_range.range_khz );
#ifdef   UNICABLE_COMPATIBLE
      if (front_end->lnb_type == UNICABLE_LNB_TYPE_UNICABLE) {
        if (front_end->unicable_mode == 2) {
          front_end->demod->prop->scan_sat_unicable_bw.scan_sat_unicable_bw  =   360;
        } else {
          front_end->demod->prop->scan_sat_unicable_bw.scan_sat_unicable_bw  =   480;
        }
        front_end->demod->prop->scan_sat_unicable_min_tune_step.scan_sat_unicable_min_tune_step  =  50;
      } else {
        front_end->demod->prop->scan_sat_unicable_bw.scan_sat_unicable_bw  =     0;
        front_end->demod->prop->scan_sat_unicable_min_tune_step.scan_sat_unicable_min_tune_step  =   0;
      }
      Si2183_L1_SetProperty2(front_end->demod, Si2183_SCAN_SAT_UNICABLE_BW_PROP_CODE);
      Si2183_L1_SetProperty2(front_end->demod, Si2183_SCAN_SAT_UNICABLE_MIN_TUNE_STEP_PROP_CODE  );
      front_end->demod->prop->dd_mode.invert_spectrum = Si2183_L2_Set_Invert_Spectrum(front_end);
#endif /* UNICABLE_COMPATIBLE */
      break;
    }
#endif /* DEMOD_DVB_S_S2_DSS */
#ifdef    DEMOD_DVB_C
    case Si2183_DD_MODE_PROP_MODULATION_DVBC :
     /* Forcing BW to 8 MHz for DVB-C */
      seekBWHz = 8000000;
      front_end->demod->prop->dd_mode.modulation  = Si2183_DD_MODE_PROP_MODULATION_DVBC;
      front_end->demod->prop->dd_mode.auto_detect = Si2183_DD_MODE_PROP_AUTO_DETECT_NONE;
#ifdef    Si2167B_BLINDSCAN_PATCH
      if  ((((front_end->demod->rsp->part_info.part == 65 ) & (front_end->demod->rsp->part_info.chiprev + 0x40 == 'B'))
         || ((front_end->demod->rsp->part_info.part == 67 ) & (front_end->demod->rsp->part_info.chiprev + 0x40 == 'B'))
        ) & ((front_end->demod->rsp->part_info.pmajor == '2') & (front_end->demod->rsp->part_info.pminor == '2')) ) {
        front_end->previous_standard = 2;
        front_end->Si2183_init_done  = 0;
        front_end->demod->load_DVB_C_Blindlock_Patch = 1;
        Si2183_L2_switch_to_standard(front_end, Si2183_DD_MODE_PROP_MODULATION_DVBC, 0);
      }
#endif /* Si2167B_BLINDSCAN_PATCH */
      front_end->demod->prop->dvbc_constellation.constellation = Si2183_DVBC_CONSTELLATION_PROP_CONSTELLATION_AUTO;
      Si2183_L1_SetProperty2(front_end->demod, Si2183_DVBC_CONSTELLATION_PROP_CODE);
      front_end->cable_lock_afc_range_khz = front_end->demod->prop->dvbc_afc_range.range_khz;
      front_end->demod->prop->dvbc_afc_range.range_khz = 200;
      Si2183_L1_SetProperty2(front_end->demod, Si2183_DVBC_AFC_RANGE_PROP_CODE);
      SiTRACE("DVB-C AFC range set to %d for blindscan/blindlock\n", front_end->demod->prop->dvbc_afc_range.range_khz);
      break;
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_MCNS
    case Si2183_DD_MODE_PROP_MODULATION_MCNS :
     /* Forcing BW to 8 MHz for MCNS */
      seekBWHz = 8000000;
      front_end->demod->prop->dd_mode.modulation  = Si2183_DD_MODE_PROP_MODULATION_MCNS;
      front_end->demod->prop->dd_mode.auto_detect = Si2183_DD_MODE_PROP_AUTO_DETECT_NONE;
      front_end->demod->prop->mcns_constellation.constellation = Si2183_MCNS_CONSTELLATION_PROP_CONSTELLATION_AUTO;
      Si2183_L1_SetProperty2(front_end->demod, Si2183_MCNS_CONSTELLATION_PROP_CODE);
      front_end->cable_lock_afc_range_khz = front_end->demod->prop->mcns_afc_range.range_khz;
      front_end->demod->prop->mcns_afc_range.range_khz = 200;
      Si2183_L1_SetProperty2(front_end->demod, Si2183_MCNS_AFC_RANGE_PROP_CODE);
      SiTRACE("MCNS AFC range set to %d for blindscan/blindlock\n", front_end->demod->prop->mcns_afc_range.range_khz);
      break;
#endif /* DEMOD_MCNS */
#ifdef    DEMOD_DVB_T2
    case Si2183_DD_MODE_PROP_MODULATION_DVBT2:
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_DVB_T
    case Si2183_DD_MODE_PROP_MODULATION_DVBT :
      front_end->demod->prop->dvbt_hierarchy.stream = Si2183_DVBT_HIERARCHY_PROP_STREAM_HP;
      Si2183_L1_SetProperty2(front_end->demod, Si2183_DVBT_HIERARCHY_PROP_CODE);
      SiTRACE("DVB-T AFC range %d\n", front_end->demod->prop->dvbt_afc_range.range_khz);
#ifdef    DEMOD_DVB_T2
      if (front_end->auto_detect_TER==1) {
        front_end->demod->prop->dd_mode.modulation  = Si2183_DD_MODE_PROP_MODULATION_AUTO_DETECT;
        front_end->demod->prop->dd_mode.auto_detect = Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_T_T2;
      }
      SiTRACE("DVB-T2 AFC range %d\n", front_end->demod->prop->dvbt2_afc_range.range_khz);
      Si2183_L1_DVBT2_PLP_SELECT    (front_end->demod, 0, Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_AUTO);
#endif /* DEMOD_DVB_T2 */
      break;
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_ISDB_T
    case Si2183_DD_MODE_PROP_MODULATION_ISDBT :
      front_end->demod->prop->dd_mode.modulation  = Si2183_DD_MODE_PROP_MODULATION_ISDBT;
      SiTRACE("ISDB-T AFC range %d\n", front_end->demod->prop->isdbt_afc_range.range_khz);
      break;
#endif /* DEMOD_ISDB_T */
#ifdef    DEMOD_DVB_C2
    case Si2183_DD_MODE_PROP_MODULATION_DVBC2:
      front_end->demod->prop->dd_mode.modulation  = Si2183_DD_MODE_PROP_MODULATION_DVBC2;
      front_end->demod->prop->dd_mode.auto_detect = Si2183_DD_MODE_PROP_AUTO_DETECT_NONE;
      front_end->demod->prop->dd_mode.bw          = seekBWHz/1000000;
      SiTRACE("DVB-C2 AFC range %d\n", front_end->demod->prop->dvbc2_afc_range.range_khz);
      break;
#endif /* DEMOD_DVB_C2 */
    default : {
      SiTRACE("'%d' modulation (%s) is not managed by Si2183_L2_Channel_Seek_Init\n", modulation, Si2183_standardName(modulation));
      break;
    }
  }

  front_end->seekBWHz     = seekBWHz;
  front_end->seekStepHz   = seekStepHz;
  front_end->minSRbps     = minSRbps;
  front_end->maxSRbps     = maxSRbps;
  front_end->rangeMin     = rangeMin;
  front_end->rangeMax     = rangeMax;
  front_end->minRSSIdBm   = minRSSIdBm;
  front_end->maxRSSIdBm   = maxRSSIdBm;
  front_end->minSNRHalfdB = minSNRHalfdB;
  front_end->maxSNRHalfdB = maxSNRHalfdB;
  front_end->cumulativeScanTime    = 0;
  front_end->cumulativeTimeoutTime = 0;
  front_end->nbTimeouts   = 0;
  front_end->nbDecisions  = 0;
  front_end->seekAbort    = 0;

  SiTRACE("Si2183_L2_Channel_Seek_Init with %d to  %d, sawBW %d, minSR %d, maxSR %d\n", front_end->rangeMin, front_end->rangeMax, front_end->seekBWHz, front_end->minSRbps, front_end->maxSRbps);
  SiTRACE("spectrum inversion %d\n",front_end->demod->prop->dd_mode.invert_spectrum );
  front_end->demod->prop->scan_fmin.scan_fmin                   = (int)((front_end->rangeMin*front_end->tuneUnitHz)/65536);
  front_end->demod->prop->scan_fmax.scan_fmax                   = (int)((front_end->rangeMax*front_end->tuneUnitHz)/65536);

  front_end->demod->prop->scan_symb_rate_min.scan_symb_rate_min = front_end->minSRbps/1000;
  front_end->demod->prop->scan_symb_rate_max.scan_symb_rate_max = front_end->maxSRbps/1000;

  Si2183_L1_SetProperty2(front_end->demod, Si2183_SCAN_FMIN_PROP_CODE);
  Si2183_L1_SetProperty2(front_end->demod, Si2183_SCAN_FMAX_PROP_CODE);
  Si2183_L1_SetProperty2(front_end->demod, Si2183_SCAN_SYMB_RATE_MIN_PROP_CODE);
  Si2183_L1_SetProperty2(front_end->demod, Si2183_SCAN_SYMB_RATE_MAX_PROP_CODE);



  front_end->demod->prop->scan_ien.buzien           = Si2183_SCAN_IEN_PROP_BUZIEN_ENABLE  ; /* (default 'DISABLE') */
  front_end->demod->prop->scan_ien.reqien           = Si2183_SCAN_IEN_PROP_REQIEN_ENABLE  ; /* (default 'DISABLE') */
  Si2183_L1_SetProperty2(front_end->demod, Si2183_SCAN_IEN_PROP_CODE);

  front_end->demod->prop->scan_int_sense.reqnegen   = Si2183_SCAN_INT_SENSE_PROP_REQNEGEN_DISABLE ; /* (default 'DISABLE') */
  front_end->demod->prop->scan_int_sense.reqposen   = Si2183_SCAN_INT_SENSE_PROP_REQPOSEN_ENABLE  ; /* (default 'ENABLE') */
  Si2183_L1_SetProperty2(front_end->demod, Si2183_SCAN_INT_SENSE_PROP_CODE);


#ifdef    TERRESTRIAL_FRONT_END
#ifdef    ALLOW_Si2183_BLINDSCAN_DEBUG
  front_end->demod->prop->scan_ter_config.scan_debug = 0x0f;
#endif /* ALLOW_Si2183_BLINDSCAN_DEBUG */
  if (front_end->demod->media == Si2183_TERRESTRIAL) {
    front_end->demod->prop->scan_ter_config.analog_bw     = Si2183_SCAN_TER_CONFIG_PROP_ANALOG_BW_8MHZ;
    if ( front_end->rangeMin == front_end->rangeMax ) {
      front_end->demod->prop->scan_ter_config.mode        = Si2183_SCAN_TER_CONFIG_PROP_MODE_BLIND_LOCK;
      SiTRACE("Blindlock < %8d %8d > < %8d %8d >\n", front_end->demod->prop->scan_fmin.scan_fmin, front_end->demod->prop->scan_fmax.scan_fmax, front_end->demod->prop->scan_symb_rate_min.scan_symb_rate_min, front_end->demod->prop->scan_symb_rate_max.scan_symb_rate_max);
    } else {
      front_end->demod->prop->scan_ter_config.mode        = Si2183_SCAN_TER_CONFIG_PROP_MODE_BLIND_SCAN;
      SiTRACE("Blindscan < %8d %8d > < %8d %8d >\n", front_end->demod->prop->scan_fmin.scan_fmin, front_end->demod->prop->scan_fmax.scan_fmax, front_end->demod->prop->scan_symb_rate_min.scan_symb_rate_min, front_end->demod->prop->scan_symb_rate_max.scan_symb_rate_max);
    }
    front_end->demod->prop->scan_ter_config.search_analog = Si2183_SCAN_TER_CONFIG_PROP_SEARCH_ANALOG_DISABLE;
    Si2183_L1_SetProperty2(front_end->demod, Si2183_SCAN_TER_CONFIG_PROP_CODE);
    if (seekBWHz == 1700000) {
      front_end->demod->prop->dd_mode.bw = Si2183_DD_MODE_PROP_BW_BW_1D7MHZ;
    } else {
      front_end->demod->prop->dd_mode.bw = seekBWHz/1000000;
    }
  }
#endif /* TERRESTRIAL_FRONT_END */
  Si2183_L1_SetProperty2(front_end->demod, Si2183_DD_MODE_PROP_CODE);

#ifdef    DEMOD_DVB_S_S2_DSS
#ifdef    ALLOW_Si2183_BLINDSCAN_DEBUG
  front_end->demod->prop->scan_sat_config.scan_debug = 0x03;
#endif /* ALLOW_Si2183_BLINDSCAN_DEBUG */
  if (front_end->demod->media == Si2183_SATELLITE  ) {
    front_end->demod->prop->scan_sat_config.analog_detect = Si2183_SCAN_SAT_CONFIG_PROP_ANALOG_DETECT_ENABLED;
    front_end->demod->prop->scan_sat_config.reserved1     =  0;
    front_end->demod->prop->scan_sat_config.reserved2     = 12;
    Si2183_L1_SetProperty2(front_end->demod, Si2183_SCAN_SAT_CONFIG_PROP_CODE);
  }
#endif /* DEMOD_DVB_S_S2_DSS */
  Si2183_L1_DD_RESTART  (front_end->demod);

  Si2183_L1_SCAN_STATUS (front_end->demod, Si2183_SCAN_STATUS_CMD_INTACK_OK);
  SiTRACE("blindscan_status leaving Seek_Init %s\n", Si2183_L2_Trace_Scan_Status(front_end->demod->rsp->scan_status.scan_status) );
  /* Preparing the next call to Si2183_L1_SCAN_CTRL which needs to be a 'START'*/
  front_end->demod->cmd->scan_ctrl.action = Si2183_SCAN_CTRL_CMD_ACTION_START;
  front_end->handshakeOn       = 0;
  front_end->searchStartTime   = system_time();
  SiTRACE("blindscan_handshake : Seek_Next will return every ~%d ms\n", front_end->handshakePeriod_ms );
  return 0;
}
/************************************************************************************************************************
  NAME: Si2183_L2_Channel_Seek_Next
  DESCRIPTION: Looks for the next channel, starting from the last detected channel
  Programming Guide Reference:    Flowchart TBD (Channel Scan flowchart)

  Parameter:  Pointer to Si2183 Context
  Returns:    1 if channel is found, 0 otherwise (either abort or end of range)
              Any other value represents the time spent searching (if front_end->handshakeUsed == 1)
************************************************************************************************************************/
signed   int  Si2183_L2_Channel_Seek_Next  (Si2183_L2_Context *front_end
                                           , signed   int *standard
                                           , signed   int *freq
                                           , signed   int *bandwidth_Hz
#ifdef    DEMOD_DVB_T
                                           , signed   int *stream
#endif /* DEMOD_DVB_T*/
                                           , unsigned int *symbol_rate_bps
#ifdef    DEMOD_DVB_C
                                           , signed   int *constellation
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_C2
                                           , signed   int *num_data_slice
#endif /* DEMOD_DVB_C2*/
                                           , signed   int *num_plp
#ifdef    DEMOD_DVB_T2
                                           , signed   int *T2_base_lite
#endif /* DEMOD_DVB_T2 */
                                           )
{
    signed   int  return_code;
    unsigned int  seek_freq;
    signed   int  seek_freq_kHz;
    signed   int  channelIncrement;
    signed   int  seekStartTime;    /* seekStartTime    is used to trace the time spent in Si2183_L2_Channel_Seek_Next and is only set when entering the function                            */
    signed   int  buzyStartTime;    /* buzyStartTime    is used to trace the time spent waiting for scan_status.buz to be different from 'BUZY'                                              */
    signed   int  timeoutDelay;
    signed   int  handshakeDelay;
    signed   int  searchDelay;
    signed   int  decisionDelay;
    signed   int  max_lock_time_ms;
    signed   int  min_lock_time_ms;
    signed   int  max_decision_time_ms;
    signed   int  blind_mode;
    signed   int  skip_resume;
    signed   int  start_resume;
    signed   int  previous_scan_status;
    unsigned char jump_to_next_channel;
    L1_Si2183_Context *api;
    /* init all flags to avoid compiler warnings */
    return_code          = 0; /* To avoid code checker warning */
    seek_freq            = 0; /* To avoid code checker warning */
    seek_freq_kHz        = 0; /* To avoid code checker warning */
    channelIncrement     = 0; /* To avoid code checker warning */
    seekStartTime        = 0; /* To avoid code checker warning */
    buzyStartTime        = 0; /* To avoid code checker warning */
    timeoutDelay         = 0; /* To avoid code checker warning */
    handshakeDelay       = 0; /* To avoid code checker warning */
    max_lock_time_ms     = 0; /* To avoid code checker warning */
    min_lock_time_ms     = 0; /* To avoid code checker warning */
    max_decision_time_ms = 0; /* To avoid code checker warning */
    skip_resume          = 0; /* To avoid code checker warning */
    previous_scan_status = 0; /* To avoid code checker warning */
    searchDelay          = 0; /* To avoid code checker warning */
    start_resume         = 0; /* To avoid code checker warning */

    api = front_end->demod;

    blind_mode   = 0;

    /* Clear all return values which may not be used depending on the standard */
    *bandwidth_Hz    = 0;
#ifdef    DEMOD_DVB_T
    *stream          = 0;
#endif /* DEMOD_DVB_T*/
    *symbol_rate_bps = 0;
#ifdef    DEMOD_DVB_C
    *constellation   = 0;
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_T2
     *num_plp        = 0;
     *T2_base_lite   = 0;
#endif /* DEMOD_DVB_T2*/
#ifdef    DEMOD_DVB_C2
#ifndef   DEMOD_DVB_T2
     *num_plp        = 0;
#endif /* DEMOD_DVB_T2*/
     *num_data_slice = 0;
#endif /* DEMOD_DVB_C2*/

    if (front_end->seekAbort) {
      SiTRACE("Si2183_L2_Channel_Seek_Next : previous run aborted. Please Si2183_L2_Channel_Seek_Init to perform a new search.\n");
      return 0;
    }

    SiTRACE("front_end->demod->standard %d (%s)\n",front_end->demod->standard, Si2183_standardName(front_end->demod->standard) );

    /* Setting max and max lock times and blind_mode flag */
    switch ( front_end->demod->standard )
    {
#ifdef    DEMOD_DVB_T2
      /* For T/T2 detection, use the max value between Si2183_DVBT_MAX_LOCK_TIME and Si2183_DVBT2_MAX_LOCK_TIME */
      /* With Si2183-A, it's Si2183_DVBT2_MAX_LOCK_TIME                                                         */
      /* This value will be refined as soon as the standard is known, i.e. when PCL = 1                         */
      case Si2183_DD_MODE_PROP_MODULATION_DVBT2:
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_DVB_T
      case Si2183_DD_MODE_PROP_MODULATION_DVBT: {
        blind_mode = 0;
#ifndef   DEMOD_DVB_T2
        max_lock_time_ms = Si2183_DVBT_MAX_LOCK_TIME;
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_DVB_T2
          max_lock_time_ms = Si2183_DVBT2_MAX_LOCK_TIME;
#endif /* DEMOD_DVB_T2 */
        min_lock_time_ms = Si2183_DVBT_MIN_LOCK_TIME;
        break;
      }
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_ISDB_T
      case Si2183_DD_MODE_PROP_MODULATION_ISDBT: {
        blind_mode = 0;
        max_lock_time_ms = Si2183_ISDBT_MAX_LOCK_TIME;
        min_lock_time_ms = Si2183_ISDBT_MIN_LOCK_TIME;
        break;
      }
#endif /* DEMOD_ISDB_T */
#ifdef    DEMOD_DVB_C
      case Si2183_DD_MODE_PROP_MODULATION_DVBC : {
        blind_mode = 1;
        max_lock_time_ms = Si2183_DVBC_MAX_SCAN_TIME;
        min_lock_time_ms = Si2183_DVBC_MIN_LOCK_TIME;
        break;
      }
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_C2
      case Si2183_DD_MODE_PROP_MODULATION_DVBC2: {
        blind_mode = 0;
        max_lock_time_ms = Si2183_DVBC2_MAX_LOCK_TIME;
        min_lock_time_ms = Si2183_DVBC2_MIN_LOCK_TIME;
        break;
      }
#endif /* DEMOD_DVB_C2 */
#ifdef    DEMOD_DVB_S_S2_DSS
      case Si2183_DD_MODE_PROP_MODULATION_DSS  :
      case Si2183_DD_MODE_PROP_MODULATION_DVBS :
      case Si2183_DD_MODE_PROP_MODULATION_DVBS2: {
        blind_mode = 1;
        max_lock_time_ms = Si2183_SAT_MAX_SEARCH_TIME;
        min_lock_time_ms = Si2183_DVBS_MIN_LOCK_TIME;
        break;
      }
#endif /* DEMOD_DVB_S_S2_DSS */
      default                                  : {
        SiTRACE("'%d' standard (%s) is not managed by Si2183_L2_Channel_Seek_Next\n", front_end->demod->prop->dd_mode.modulation, Si2183_standardName(front_end->demod->prop->dd_mode.modulation));
        front_end->seekAbort = 1;
        return 0;
        break;
      }
    }
    SiTRACE("blindscan : max_lock_time_ms %d\n", max_lock_time_ms);

    seekStartTime = system_time();

    if (front_end->handshakeUsed == 0) {
      start_resume = 1;
      front_end->searchStartTime = seekStartTime;
    }
    if (front_end->handshakeUsed == 1) {
      min_lock_time_ms = 0;
      /* Recalled after handshaking    */
      if (front_end->handshakeOn == 1) {
        /* Skip tuner and demod settings */
        start_resume = 0;
        SiTRACE("blindscan_handshake : recalled after   handshake. Skipping tuner and demod settings\n");
      }
      /* When recalled after a lock */
      if (front_end->handshakeOn == 0) {
        /* Allow tuner and demod settings */
        start_resume = 1;
        if (blind_mode == 1) { /* DVB-C / DVB-S / DVB-S2 / MCNS */
          if (front_end->demod->cmd->scan_ctrl.action == Si2183_SCAN_CTRL_CMD_ACTION_START) {
            SiTRACE("blindscan_handshake : no handshake : starting.\n");
          } else {
            SiTRACE("blindscan_handshake : no handshake : resuming.\n");
          }
        }
        front_end->searchStartTime = seekStartTime;
      }
    }
    front_end->handshakeStart_ms = seekStartTime;

  #ifdef    DEMOD_DVB_T2
    if (start_resume == 1) {
      /* Enabling FEF control for T/T2 */
      switch ( front_end->demod->standard )
      {
        case Si2183_DD_MODE_PROP_MODULATION_DVBT2 :
        case Si2183_DD_MODE_PROP_MODULATION_DVBT  : {
         #ifdef    INDIRECT_I2C_CONNECTION
          front_end->f_TER_tuner_enable(front_end->callback);
         #else  /* INDIRECT_I2C_CONNECTION */
          Si2183_L2_Tuner_I2C_Enable(front_end);
         #endif /* INDIRECT_I2C_CONNECTION */
          Si2183_L2_TER_FEF (front_end,1);
        #ifdef    INDIRECT_I2C_CONNECTION
          front_end->f_TER_tuner_disable(front_end->callback);
        #else  /* INDIRECT_I2C_CONNECTION */
          Si2183_L2_Tuner_I2C_Disable(front_end);
        #endif /* INDIRECT_I2C_CONNECTION */
          Si2183_L1_DVBT2_PLP_SELECT    (front_end->demod, 0, Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_AUTO);
          break;
        }
        default                                   : {
          break;
        }
      }
    }
  #endif /* DEMOD_DVB_T2 */

    max_decision_time_ms = max_lock_time_ms;

    /* Select TER channel increment (this value will only be used for 'TER' scanning) */
    channelIncrement = front_end->seekStepHz;

    /* Start Seeking */
    SiTRACE("Si2183_L2_Channel_Seek_Next front_end->rangeMin %10d,front_end->rangeMax %10d blind_mode %d\n", front_end->rangeMin,front_end->rangeMax, blind_mode);

    seek_freq = front_end->rangeMin;

  if (blind_mode == 0) { /* DVB-T / DVB-T2 / ISDB-T / DVB-C2 */

    while ( seek_freq <= front_end->rangeMax )
    {
      if (start_resume) {
        /* Call the Si2183_L2_Tune command to tune the frequency */
        SiTRACE ("Seek_Next: Si2183_L2_Tune (front_end, %10d)\n", seek_freq);
        if ( (Si2183_L2_Tune (front_end, seek_freq ) - seek_freq) != 0) {
          /* Manage possible tune error */
          SiTRACE("Si2183_L2_Channel_Seek_Next Tune error at %d, aborting (skipped)\n", seek_freq);
          front_end->seekAbort = 1;
          return 0;
        }
        front_end->ddRestartTime = system_time();
      #ifdef    DEMOD_DVB_C2
        if (front_end->demod->standard == Si2183_DD_MODE_PROP_MODULATION_DVBC2) {
        /* For DVB-C2, make sure to store tuned_rf_freq and be in ID_SEL_MODE_AUTO
         (this may have been changed by the application while browsing through Data Slices and PLPs) */
          if (front_end->demod->cmd->dvbc2_ds_plp_select.id_sel_mode != Si2183_DVBC2_DS_PLP_SELECT_CMD_ID_SEL_MODE_AUTO) {
              front_end->demod->cmd->dvbc2_ds_plp_select.id_sel_mode  = Si2183_DVBC2_DS_PLP_SELECT_CMD_ID_SEL_MODE_AUTO;
              front_end->demod->cmd->dvbc2_ds_plp_select.ds_id        = 0;
            Si2183_L1_DVBC2_DS_PLP_SELECT      (front_end->demod,
                                                front_end->demod->cmd->dvbc2_ds_plp_select.plp_id,
                                                front_end->demod->cmd->dvbc2_ds_plp_select.id_sel_mode,
                                                front_end->demod->cmd->dvbc2_ds_plp_select.ds_id);
          }
          front_end->demod->cmd->dvbc2_ctrl.action        = Si2183_DVBC2_CTRL_CMD_ACTION_START;
          front_end->demod->cmd->dvbc2_ctrl.tuned_rf_freq = seek_freq;
        /* For DVB-C2, store tuned_rf_freq in the part using Si2183_L1_DVBC2_CTRL */
          Si2183_L1_DVBC2_CTRL (front_end->demod, front_end->demod->cmd->dvbc2_ctrl.action , front_end->demod->cmd->dvbc2_ctrl.tuned_rf_freq);
          system_wait(2); /* Waiting 2 ms to have dvbc2_ctrl.tuned_rf_freq processed by the part before DD_RESTART */
          SiTRACE   ("Si2183_L2_Channel_Seek_Next 'dvbc2_ctrl/START' took %3d ms\n", system_time() - front_end->ddRestartTime);
        }
      #endif /* DEMOD_DVB_C2 */
        front_end->ddRestartTime = system_time();
        Si2183_L1_DD_RESTART            (front_end->demod);
        SiTRACE   ("Si2183_L2_Channel_Seek_Next 'reset' took %3d ms\n", system_time() - front_end->ddRestartTime);
        /* In non-blind mode, the time-out reference is the last DD_RESTART or DVBC2_CTRL */
        front_end->timeoutStartTime = system_time();
        /* as we will not lock in less than min_lock_time_ms, wait a while... */
        system_wait(min_lock_time_ms);
      }

      jump_to_next_channel = 0;

      while (!jump_to_next_channel) {

#ifdef    DEMOD_DVB_T
        if ((front_end->demod->standard == Si2183_DD_MODE_PROP_MODULATION_DVBT)
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_DVB_T2
          | (front_end->demod->standard == Si2183_DD_MODE_PROP_MODULATION_DVBT2)
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_DVB_T
          ) {
          return_code = Si2183_L1_DD_STATUS(api, Si2183_DD_STATUS_CMD_INTACK_CLEAR);
          if (return_code != NO_Si2183_ERROR) {
            SiTRACE("Si2183_L2_Channel_Seek_Next: Si2183_L1_DD_STATUS (T/T2) error at %d, aborting\n", seek_freq);
            front_end->handshakeOn = 0;
            front_end->seekAbort   = 1;
            return 0;
          }
          Si2183_L1_DD_EXT_AGC_TER (api,
                                    Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MODE_NO_CHANGE,
                                    api->cmd->dd_ext_agc_ter.agc_1_inv,
                                    Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_NO_CHANGE,
                                    api->cmd->dd_ext_agc_ter.agc_2_inv,
                                    api->cmd->dd_ext_agc_ter.agc_1_kloop,
                                    api->cmd->dd_ext_agc_ter.agc_2_kloop,
                                    api->cmd->dd_ext_agc_ter.agc_1_min,
                                    api->cmd->dd_ext_agc_ter.agc_2_min );

          searchDelay = system_time() - front_end->searchStartTime;

          if ( (front_end->demod->rsp->dd_status.dl  == Si2183_DD_STATUS_RESPONSE_DL_NO_LOCK  ) & ( front_end->demod->rsp->dd_status.rsqstat_bit5   == Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT5_NO_CHANGE ) ) {
            /* Check PCL to refine the max_lock_time_ms value if the standard has been detected */
            if   (front_end->demod->rsp->dd_status.pcl        == Si2183_DD_STATUS_RESPONSE_PCL_LOCKED) {
              if (front_end->demod->rsp->dd_status.modulation == Si2183_DD_STATUS_RESPONSE_MODULATION_DVBT ) { max_lock_time_ms = Si2183_DVBT_MAX_LOCK_TIME ;}
            }
          }
          if ( (front_end->demod->rsp->dd_status.dl  == Si2183_DD_STATUS_RESPONSE_DL_NO_LOCK  ) & ( front_end->demod->rsp->dd_status.rsqstat_bit5   == Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT5_CHANGE    ) ) {
            decisionDelay = system_time() - front_end->ddRestartTime; front_end->cumulativeScanTime = front_end->cumulativeScanTime + decisionDelay; front_end->nbDecisions++;
            SiTRACE ("NO DVBT/T2. Jumping from  %10d after %7d ms. Delay from DD_RESTART %4d ms AGC2 %3d\n", seek_freq, searchDelay, decisionDelay, api->rsp->dd_ext_agc_ter.agc_2_level);
            if(seek_freq==front_end->rangeMax) {front_end->rangeMin=seek_freq;}
            seek_freq = seek_freq + channelIncrement;
            jump_to_next_channel = 1;
            start_resume         = 1;
            break;
          }
          if ( (front_end->demod->rsp->dd_status.dl  == Si2183_DD_STATUS_RESPONSE_DL_LOCKED   ) & ( front_end->demod->rsp->dd_status.rsqstat_bit5   == Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT5_NO_CHANGE ) ) {
            *standard     = front_end->demod->rsp->dd_status.modulation;
            if (*standard == Si2183_DD_STATUS_RESPONSE_MODULATION_DVBT ) {
              Si2183_L1_DVBT_STATUS (api, Si2183_DVBT_STATUS_CMD_INTACK_CLEAR);
              front_end->detected_rf = seek_freq + front_end->demod->rsp->dvbt_status.afc_freq*1000;
              if (front_end->demod->rsp->dvbt_status.hierarchy == Si2183_DVBT_STATUS_RESPONSE_HIERARCHY_NONE) {
                *stream       = Si2183_DVBT_HIERARCHY_PROP_STREAM_HP;
              } else {
                *stream       = front_end->demod->prop->dvbt_hierarchy.stream;
              }
              *bandwidth_Hz = front_end->demod->prop->dd_mode.bw*1000000;
              *freq         = front_end->detected_rf;
              decisionDelay = system_time() - front_end->ddRestartTime; front_end->cumulativeScanTime = front_end->cumulativeScanTime + decisionDelay; front_end->nbDecisions++;
              SiTRACE ("DVB-T  lock at %10d after %7d ms. Delay from DD_RESTART %4d ms AGC2 %3d\n", (front_end->detected_rf)/1000, searchDelay, decisionDelay, api->rsp->dd_ext_agc_ter.agc_2_level);
            }
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_DVB_T2
            if (*standard == Si2183_DD_STATUS_RESPONSE_MODULATION_DVBT2) {
           #ifdef    INDIRECT_I2C_CONNECTION
             front_end->f_TER_tuner_enable(front_end->callback);
           #else  /* INDIRECT_I2C_CONNECTION */
             Si2183_L2_Tuner_I2C_Enable(front_end);
           #endif /* INDIRECT_I2C_CONNECTION */
              Si2183_L2_TER_FEF (front_end,1);
           #ifdef    INDIRECT_I2C_CONNECTION
             front_end->f_TER_tuner_disable(front_end->callback);
           #else  /* INDIRECT_I2C_CONNECTION */
             Si2183_L2_Tuner_I2C_Disable(front_end);
           #endif /* INDIRECT_I2C_CONNECTION */
              Si2183_L1_DVBT2_STATUS (api, Si2183_DVBT2_STATUS_CMD_INTACK_CLEAR);
              *num_plp = api->rsp->dvbt2_status.num_plp;
              front_end->detected_rf = seek_freq + front_end->demod->rsp->dvbt2_status.afc_freq*1000;
              decisionDelay = system_time() - front_end->ddRestartTime; front_end->cumulativeScanTime = front_end->cumulativeScanTime + decisionDelay; front_end->nbDecisions++;
              SiTRACE ("DVB-T2 lock at %10d after %7d ms. Delay from DD_RESTART %4d ms AGC2 %3d\n", (front_end->detected_rf)/1000, searchDelay, decisionDelay, api->rsp->dd_ext_agc_ter.agc_2_level);
              switch (front_end->demod->prop->dd_mode.bw) {
                case Si2183_DD_MODE_PROP_BW_BW_1D7MHZ : { *bandwidth_Hz =                                    1700000; break; }
                default                               : { *bandwidth_Hz = front_end->demod->prop->dd_mode.bw*1000000; break; }
              }
              *T2_base_lite = api->rsp->dvbt2_status.t2_mode + 1; /* Adding 1 to match dvbt2_mode.lock_mode values (0='ANY', 1='T2-Base', 2='T2-Lite')*/
              *freq         = front_end->detected_rf;
            }
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_DVB_T
            /* Set min seek_freq for next seek */
            front_end->rangeMin = seek_freq + front_end->seekBWHz;
            /* Return 1 to signal that the Si2183 is locked on a valid channel */
            front_end->handshakeOn = 0;
            return 1;
          }
        }
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_ISDB_T
        if ( front_end->demod->standard == Si2183_DD_MODE_PROP_MODULATION_ISDBT ) {

          return_code = Si2183_L1_DD_STATUS(api, Si2183_DD_STATUS_CMD_INTACK_CLEAR);
          if (return_code != NO_Si2183_ERROR) {
            SiTRACE("Si2183_L2_Channel_Seek_Next: Si2183_L1_DD_STATUS (ISDBT) error at %d, aborting\n", seek_freq);
            front_end->handshakeOn = 0;
            front_end->seekAbort   = 1;
            return 0;
          }

          searchDelay = system_time() - front_end->searchStartTime;

          if ( (front_end->demod->rsp->dd_status.dl  == Si2183_DD_STATUS_RESPONSE_DL_NO_LOCK  ) & ( front_end->demod->rsp->dd_status.rsqstat_bit5   == Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT5_CHANGE   ) ) {
            decisionDelay = system_time() - front_end->ddRestartTime; front_end->cumulativeScanTime = front_end->cumulativeScanTime + decisionDelay; front_end->nbDecisions++;
            SiTRACE ("NO ISDB-T. Jumping from  %10d after %7d ms. Delay from DD_RESTART %4d ms AGC1 %3d AGC2 %3d\n", seek_freq, searchDelay, decisionDelay, api->rsp->dd_ext_agc_ter.agc_1_level, api->rsp->dd_ext_agc_ter.agc_2_level);
            if(seek_freq==front_end->rangeMax) {front_end->rangeMin=seek_freq;}
            seek_freq = seek_freq + channelIncrement;
            jump_to_next_channel = 1;
            start_resume         = 1;
            break;
          }
          if ( (front_end->demod->rsp->dd_status.dl  == Si2183_DD_STATUS_RESPONSE_DL_LOCKED   ) & ( front_end->demod->rsp->dd_status.rsqstat_bit5   == Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT5_NO_CHANGE ) ) {
            *standard     = front_end->demod->rsp->dd_status.modulation;
            if (*standard == Si2183_DD_STATUS_RESPONSE_MODULATION_ISDBT ) {
              Si2183_L1_ISDBT_STATUS (api, Si2183_ISDBT_STATUS_CMD_INTACK_CLEAR);
              front_end->detected_rf = seek_freq + front_end->demod->rsp->isdbt_status.afc_freq*1000;
              *bandwidth_Hz = front_end->demod->prop->dd_mode.bw*1000000;
              *freq         = front_end->detected_rf;
              decisionDelay = system_time() - front_end->ddRestartTime; front_end->cumulativeScanTime = front_end->cumulativeScanTime + decisionDelay; front_end->nbDecisions++;
              SiTRACE ("ISDB-T  lock at %10d after %7d ms. Delay from DD_RESTART %4d ms AGC2 %3d\n", (front_end->detected_rf)/1000, searchDelay, decisionDelay, api->rsp->dd_ext_agc_ter.agc_2_level);
            }
            /* Set min seek_freq for next seek */
            front_end->rangeMin = seek_freq + front_end->seekBWHz;
            /* Return 1 to signal that the Si2183 is locked on a valid channel */
            front_end->handshakeOn = 0;
            return 1;
          }
        }
#endif /* DEMOD_ISDB_T */
#ifdef    DEMOD_DVB_C2
        if ( front_end->demod->standard == Si2183_DD_MODE_PROP_MODULATION_DVBC2 ) {
          return_code = Si2183_L1_DVBC2_STATUS   (api, Si2183_DVBC2_STATUS_CMD_INTACK_CLEAR);
          if (return_code != NO_Si2183_ERROR) {
            SiTRACE("Si2183_L2_Channel_Seek_Next: Si2183_L1_DVBC2_STATUS (DVBC2) error at %d, aborting\n", seek_freq);
            front_end->handshakeOn = 0;
            front_end->seekAbort   = 1;
            return 0;
          }

          searchDelay = system_time() - front_end->searchStartTime;
          if ( ( front_end->demod->rsp->dvbc2_status.notdvbc2 == Si2183_DVBC2_STATUS_RESPONSE_NOTDVBC2_NOT_DVBC2   ) ) {
            decisionDelay = system_time() - front_end->ddRestartTime; front_end->cumulativeScanTime = front_end->cumulativeScanTime + decisionDelay; front_end->nbDecisions++;
            SiTRACE ("NOT DVB-C2 flag set at %10d/%d Mhz after %7d ms. Delay from DD_RESTART %4d ms\n", seek_freq, front_end->demod->prop->dd_mode.bw, searchDelay, decisionDelay);
            if(seek_freq==front_end->rangeMax) {front_end->rangeMin=seek_freq;}
            seek_freq = seek_freq + channelIncrement;
            jump_to_next_channel = 1;
            start_resume         = 1;
            /* No channel detected, increment the frequency */
            decisionDelay = system_time() - front_end->ddRestartTime; front_end->cumulativeScanTime = front_end->cumulativeScanTime + decisionDelay; front_end->nbDecisions++;
            SiTRACE ("Seek_Next jumping  from  %10d to %10d after %7d ms. Delay from DD_RESTART %4d ms\n", seek_freq, seek_freq + channelIncrement, searchDelay, decisionDelay);
            break;
          }
          if ( ( front_end->demod->rsp->dvbc2_status.pcl      == Si2183_DVBC2_STATUS_RESPONSE_PCL_LOCKED           ) ) {
            *standard     = Si2183_DD_MODE_PROP_MODULATION_DVBC2;
            /* Locked on L1 Block, retrieve C2 rf_freq */
            decisionDelay = system_time() - front_end->ddRestartTime; front_end->cumulativeScanTime = front_end->cumulativeScanTime + decisionDelay; front_end->nbDecisions++;
            SiTRACE ("DVB-C2 PCL lock ( = 'C2 signalling detected') at %10d after %7d ms. Delay from DD_RESTART %4d ms\n", seek_freq, searchDelay, decisionDelay);
            Si2183_L1_DVBC2_STATUS   (api, Si2183_DVBC2_STATUS_CMD_INTACK_CLEAR);
            /* If not tuned on rf_freq, retune */
            front_end->detected_rf = front_end->demod->rsp->dvbc2_status.rf_freq;
            if (front_end->demod->rsp->dvbc2_status.rf_freq != seek_freq) {
              seek_freq = front_end->demod->rsp->dvbc2_status.rf_freq;
              Si2183_L2_Tune (front_end, front_end->demod->rsp->dvbc2_status.rf_freq );
              front_end->demod->cmd->dvbc2_ctrl.action        = Si2183_DVBC2_CTRL_CMD_ACTION_START;
              front_end->demod->cmd->dvbc2_ctrl.tuned_rf_freq = seek_freq;
              /* For DVB-C2, start the lock process using Si2183_L1_DVBC2_CTRL */
              Si2183_L1_DVBC2_CTRL (front_end->demod, front_end->demod->cmd->dvbc2_ctrl.action , front_end->demod->cmd->dvbc2_ctrl.tuned_rf_freq);
              SiTRACE   ("Si2183_L2_Channel_Seek_Next retuning at %10d\n", seek_freq);
              front_end->ddRestartTime = system_time();
              /* Wait for relock on rf_freq */
              while (system_time() - front_end->ddRestartTime < max_lock_time_ms) {
                Si2183_L1_DVBC2_STATUS   (api, Si2183_DVBC2_STATUS_CMD_INTACK_CLEAR);
                if (front_end->demod->rsp->dvbc2_status.dl == Si2183_DD_STATUS_RESPONSE_DL_LOCKED) { break; }
              }
            }
            /* Locked on rf_freq, retrieve C2 system num_data_slice */
            Si2183_L1_DVBC2_SYS_INFO (api);
            *num_data_slice = front_end->demod->rsp->dvbc2_sys_info.num_dslice;
            *bandwidth_Hz   = front_end->demod->prop->dd_mode.bw*1000000;
            *freq           = front_end->demod->rsp->dvbc2_status.rf_freq;
            SiTRACE ("DVB-C2  rf_freq %10ld start_frequency_hz %10ld c2_bandwidth_hz %10ld front_end->seekBWHz %d. front_end->rangeMin %10d\n", front_end->demod->rsp->dvbc2_status.rf_freq, front_end->demod->rsp->dvbc2_sys_info.start_frequency_hz, front_end->demod->rsp->dvbc2_sys_info.c2_bandwidth_hz, front_end->seekBWHz, front_end->rangeMin );
            /* Set min seek_freq for next seek */
            front_end->rangeMin = front_end->demod->rsp->dvbc2_sys_info.start_frequency_hz + front_end->demod->rsp->dvbc2_sys_info.c2_bandwidth_hz + front_end->demod->prop->dd_mode.bw*1000000/2;
            /* Return 1 to signal that the Si2183 is locked on a valid channel */
            front_end->handshakeOn = 0;
            return 1;
          }
        }
#endif /* DEMOD_DVB_C2 */

        /* timeout management (this should only trigger if the channel is very difficult, i.e. when pcl = 1 and dl = 0 until the timeout) */
        timeoutDelay = system_time() - front_end->timeoutStartTime;
        if (timeoutDelay >= max_lock_time_ms) {
          decisionDelay = system_time() - front_end->ddRestartTime; front_end->cumulativeTimeoutTime = front_end->cumulativeTimeoutTime + decisionDelay; front_end->nbTimeouts++;
          SiTRACE ("----------- Timeout from  %10d after %7d ms. Delay from DD_RESTART %4d ms\n", seek_freq, timeoutDelay, decisionDelay);
/*          SiERROR ("Timeout (blind_mode = 0)\n");*/
          seek_freq = seek_freq + channelIncrement;
          jump_to_next_channel = 1;
          start_resume         = 1;
          break;
        }

        if (front_end->handshakeUsed) {
          handshakeDelay = system_time() - front_end->handshakeStart_ms;
          if (handshakeDelay >= front_end->handshakePeriod_ms) {
            SiTRACE ("blindscan_handshake : handshake after %5d ms (at %10d). (search delay %6d ms) %*s\n", handshakeDelay, front_end->rangeMin, searchDelay, (searchDelay)/1000,"*");
           *freq                   = seek_freq;
            front_end->rangeMin    = seek_freq;
            front_end->handshakeOn = 1;
            /* The application will check handshakeStart_ms to know whether the blindscan is ended or not */
            return searchDelay + 2; /* Make sure we don't return '0' or '1' from here */
          } else {
            SiTRACE ("blindscan_handshake : no handshake yet. (handshake delay %6d ms, search delay %6d ms)\n", handshakeDelay, searchDelay);
          }
        }
      /* Check seekAbort flag (set in case of timeout or by the top-level application) */

      if (front_end->seekAbort) {
        /* Abort the SCAN loop to allow it to restart with the new rangeMin frequency */
        SiTRACE ("seek_next no blind_mode >> (abort!)    Si2183_L1_SCAN_CTRL( front_end->demod, Si2183_SCAN_CTRL_CMD_ACTION_ABORT)\n");
                  Si2183_L1_SCAN_CTRL (front_end->demod, Si2183_SCAN_CTRL_CMD_ACTION_ABORT , 0);
        front_end->handshakeOn = 0;
        return 0;
        break;
      }
        /* Check status every n ms */
        system_wait(10);
      }
    }
  }

  if (blind_mode == 1) { /* DVB-C / DVB-S / DVB-S2 / MCNS */

    if (front_end->tuneUnitHz == 1) {
      seek_freq_kHz = seek_freq/1000;
    } else {
      seek_freq_kHz = seek_freq;
    }

    previous_scan_status = api->rsp->scan_status.scan_status;

    /* Checking blindscan status before issuing a 'start' or 'resume' */
    Si2183_L1_SCAN_STATUS (front_end->demod, Si2183_SCAN_STATUS_CMD_INTACK_OK);
    SiTRACE("blindscan_status      %s buz %d\n", Si2183_L2_Trace_Scan_Status(front_end->demod->rsp->scan_status.scan_status),front_end->demod->rsp->scan_status.buz );

    if (front_end->demod->rsp->scan_status.scan_status != previous_scan_status) {
      SiTRACE ("scan_status changed from %s to %s\n", Si2183_L2_Trace_Scan_Status(previous_scan_status), Si2183_L2_Trace_Scan_Status(front_end->demod->rsp->scan_status.scan_status));
    }

    if (start_resume) {
      /* Wait for scan_status.buz to be '0' before issuing SCAN_CTRL */
      buzyStartTime = system_time();
      while (front_end->demod->rsp->scan_status.buz == Si2183_SCAN_STATUS_RESPONSE_BUZ_BUSY) {
        Si2183_L1_SCAN_STATUS (front_end->demod, Si2183_SCAN_STATUS_CMD_INTACK_OK);
        SiTRACE ("blindscan_interaction ?? (buzy)   Si2183_L1_SCAN_STATUS scan_status.buz %d after %d ms\n", front_end->demod->rsp->scan_status.buz, system_time() - buzyStartTime);
        if (system_time() - buzyStartTime > 100) {
        SiTRACE ("blindscan_interaction -- (error)  Si2183_L1_SCAN_STATUS is always 'BUZY'\n");
          return 0;
        }
      }
      if (front_end->demod->cmd->scan_ctrl.action == Si2183_SCAN_CTRL_CMD_ACTION_START) {
        SiTRACE ("blindscan_interaction >> (start ) Si2183_L1_SCAN_CTRL( front_end->demod, %d, %8d) \n", front_end->demod->cmd->scan_ctrl.action, seek_freq_kHz);
      } else {
        SiTRACE ("blindscan_interaction >> (resume) Si2183_L1_SCAN_CTRL( front_end->demod, %d, %8d) \n", front_end->demod->cmd->scan_ctrl.action, seek_freq_kHz);
      }
      return_code = Si2183_L1_SCAN_CTRL (front_end->demod,               front_end->demod->cmd->scan_ctrl.action, seek_freq_kHz);
      front_end->demod->cmd->scan_ctrl.action = Si2183_SCAN_CTRL_CMD_ACTION_RESUME;
      if (return_code != NO_Si2183_ERROR) {
        SiTRACE ("blindscan_interaction -- (error1) Si2183_L1_SCAN_CTRL %d      ERROR at %10d (%d)\n!!!!!!!!!!!!!!!!!!!!!!!\n", front_end->demod->cmd->scan_ctrl.action, seek_freq_kHz, front_end->demod->rsp->scan_status.scan_status);
        SiTRACE("scan_status.buz %d\n", front_end->demod->rsp->scan_status.buz);
        return 0;
      }
      /* In blind mode, the timeout reference is the SCAN_CTRL */
      front_end->timeoutStartTime = system_time();
    }
    front_end->demod->cmd->scan_ctrl.action = Si2183_SCAN_CTRL_CMD_ACTION_RESUME;

    /* The actual search loop... */
    while ( 1 ) {

      Si2183_L1_CheckStatus (front_end->demod);

      searchDelay = system_time() - front_end->searchStartTime;

      if ( (front_end->demod->status->scanint == Si2183_STATUS_SCANINT_TRIGGERED) ) {

        /* There is an interaction with the FW, refresh the timeoutStartTime */
        front_end->timeoutStartTime = system_time();

        Si2183_L1_SCAN_STATUS (front_end->demod, Si2183_SCAN_STATUS_CMD_INTACK_CLEAR);
        SiTRACE("blindscan_status      %s\n", Si2183_L2_Trace_Scan_Status(front_end->demod->rsp->scan_status.scan_status) );
        skip_resume = 0;

        buzyStartTime = system_time();
        while (front_end->demod->rsp->scan_status.buz == Si2183_SCAN_STATUS_RESPONSE_BUZ_BUSY) {
          Si2183_L1_SCAN_STATUS (front_end->demod, Si2183_SCAN_STATUS_CMD_INTACK_OK);
          SiTRACE ("blindscan_interaction ?? (buzy)   Si2183_L1_SCAN_STATUS status.scanint %d scan_status.buz %d after %d ms\n", front_end->demod->rsp->scan_status.STATUS->scanint, front_end->demod->rsp->scan_status.buz, system_time() - buzyStartTime);
          if (system_time() - buzyStartTime > 100) {
            SiTRACE ("blindscan_interaction -- (error)  Si2183_L1_SCAN_STATUS is always 'BUZY'\n");
            return 0;
          }
        }

        switch (front_end->demod->rsp->scan_status.scan_status) {
          case  Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_TUNE_REQUEST          : {
            SiTRACE ("blindscan_interaction -- (tune  ) SCAN TUNE_REQUEST at %8ld kHz. misc 0x%08x\n", front_end->demod->rsp->scan_status.rf_freq, front_end->misc_infos);
            if (front_end->tuneUnitHz == 1) {
              seek_freq = Si2183_L2_Tune (front_end, front_end->demod->rsp->scan_status.rf_freq*1000 );
              seek_freq_kHz = seek_freq/1000;
            } else {
              seek_freq = Si2183_L2_Tune (front_end, front_end->demod->rsp->scan_status.rf_freq );
              seek_freq_kHz = seek_freq;
            }
            *freq = front_end->rangeMin = seek_freq;
            /* as we will not lock in less than min_lock_time_ms, wait a while... */
            system_wait(min_lock_time_ms);
            break;
          }
          case  Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_DIGITAL_CHANNEL_FOUND : {
            *standard        = front_end->demod->rsp->scan_status.modulation;
            switch (front_end->demod->rsp->scan_status.modulation) {
#ifdef    DEMOD_DVB_C
              case Si2183_SCAN_STATUS_RESPONSE_MODULATION_DVBC : {
                *freq            = front_end->demod->rsp->scan_status.rf_freq*1000;
                *symbol_rate_bps = front_end->demod->rsp->scan_status.symb_rate*1000;
                Si2183_L1_DVBC_STATUS(front_end->demod, Si2183_DVBC_STATUS_CMD_INTACK_OK);
                front_end->demod->prop->dvbc_symbol_rate.rate = front_end->demod->rsp->scan_status.symb_rate;
                *constellation   = front_end->demod->rsp->dvbc_status.constellation;
                break;
              }
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_MCNS
              case Si2183_SCAN_STATUS_RESPONSE_MODULATION_MCNS : {
                *freq            = front_end->demod->rsp->scan_status.rf_freq*1000;
                *symbol_rate_bps = front_end->demod->rsp->scan_status.symb_rate*1000;
                Si2183_L1_MCNS_STATUS(front_end->demod, Si2183_MCNS_STATUS_CMD_INTACK_OK);
                front_end->demod->prop->mcns_symbol_rate.rate = front_end->demod->rsp->scan_status.symb_rate;
                *constellation   = front_end->demod->rsp->mcns_status.constellation;
                break;
              }
#endif /* DEMOD_MCNS */
#ifdef    DEMOD_DVB_S_S2_DSS
              case Si2183_SCAN_STATUS_RESPONSE_MODULATION_DSS   :
              case Si2183_SCAN_STATUS_RESPONSE_MODULATION_DVBS  :
              case Si2183_SCAN_STATUS_RESPONSE_MODULATION_DVBS2 : {
                *freq            = front_end->demod->rsp->scan_status.rf_freq;
                *symbol_rate_bps = front_end->demod->rsp->scan_status.symb_rate*1000;
                if (*standard == Si2183_SCAN_STATUS_RESPONSE_MODULATION_DVBS ) { front_end->demod->prop->dvbs_symbol_rate.rate  = front_end->demod->rsp->scan_status.symb_rate; }
                if (*standard == Si2183_SCAN_STATUS_RESPONSE_MODULATION_DVBS2) { front_end->demod->prop->dvbs2_symbol_rate.rate = front_end->demod->rsp->scan_status.symb_rate; }
                if (*standard == Si2183_SCAN_STATUS_RESPONSE_MODULATION_DVBS2) {
                    Si2183_L1_DVBS2_STATUS(front_end->demod, 0);
                    *num_plp = front_end->demod->rsp->dvbs2_status.num_is;
                }
                front_end->tuner_sat->RF = *freq;
                break;
              }
#endif /* DEMOD_DVB_S_S2_DSS */
              default : {
                SiTRACE("Si2183_L2_Channel_Seek_Next DIGITAL_CHANNEL_FOUND error at %d: un-handled modulation (%d), aborting (skipped)\n", seek_freq, front_end->demod->rsp->scan_status.modulation);
                front_end->seekAbort = 1;
                return 0;
                break;
              }
            }
            /* When locked, clear scanint before returning from SeekNext, to avoid seeing it again on the 'RESUME', with fast i2c platforms */
            Si2183_L1_SCAN_STATUS (front_end->demod, Si2183_SCAN_STATUS_CMD_INTACK_CLEAR);
            SiTRACE ("blindscan_interaction -- (locked) SCAN DIGITAL lock at %d kHz after %7d ms. modulation %3d (%s). symbol_rate_bps %d. misc 0x%08x\n", *freq, searchDelay, *standard, Si2183_standardName(*standard), *symbol_rate_bps, front_end->misc_infos );
            SiTRACE ("if_freq_shift          %d\n", Si2183_L1_GET_REG (front_end->demod, 28, 92, 4) );
            SiTRACE ("freq_corr_sat          %d\n", Si2183_L1_GET_REG (front_end->demod, 27,232, 5) );
            SiTRACE ("spectral_inv_status_s2 %d\n", Si2183_L1_GET_REG (front_end->demod, 33,175, 5) );
            SiTRACE ("spectral_inv_status_cs %d\n", Si2183_L1_GET_REG (front_end->demod,  0,123,18) );
            front_end->handshakeOn = 0;
            decisionDelay   = system_time() - seekStartTime; front_end->cumulativeScanTime = front_end->cumulativeScanTime + decisionDelay; front_end->nbDecisions++;
            return 1;
            break;
          }
          case  Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_ERROR                 : {
            SiTRACE ("blindscan_interaction -- (error2) SCAN error at %d after %4d ms\n", seek_freq/1000, searchDelay);
            SiERROR ("SCAN status returns 'ERROR'\n");
            front_end->handshakeOn = 0;
            decisionDelay   = system_time() - seekStartTime; front_end->cumulativeScanTime = front_end->cumulativeScanTime + decisionDelay; front_end->nbDecisions++;
            return 0;
            break;
          }
          case  Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_SEARCHING             : {
            SiTRACE("SCAN Searching...\n");
            skip_resume = 1;
            break;
          }
          case  Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_ENDED                 : {
            SiTRACE ("blindscan_interaction -- (ended ) SCAN ENDED at %d. misc 0x%08x\n", seek_freq, front_end->misc_infos );
            Si2183_L1_SCAN_CTRL (front_end->demod, Si2183_SCAN_CTRL_CMD_ACTION_ABORT , 0);
            front_end->handshakeOn = 0;
            decisionDelay   = system_time() - seekStartTime; front_end->cumulativeScanTime = front_end->cumulativeScanTime + decisionDelay; front_end->nbDecisions++;
            return 0;
            break;
          }
#ifdef    ALLOW_Si2183_BLINDSCAN_DEBUG
           case  Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_DEBUG                 : {
            SiTRACE ("blindscan_interaction -- (debug) SCAN DEBUG code %d\n", front_end->demod->rsp->scan_status.symb_rate);
            switch (front_end->demod->rsp->scan_status.symb_rate) {
              case 4: { /* SPECTRUM */
                if ( front_end->misc_infos & 0x00010000 ) { Si2183_plot(front_end, "spectrum", 0, seek_freq); }
                break;
              }
              case 9: { /* TRYLOCK */
                if ( front_end->misc_infos & 0x00100000 ) { Si2183_plot(front_end, "trylock", 0, seek_freq); }
                break;
              }
              default: { break; }
            }
            /* There has been a debug request by the FW, refresh the timeoutStartTime */
            front_end->timeoutStartTime = system_time();
            break;
          }
#else  /* ALLOW_Si2183_BLINDSCAN_DEBUG */
           case  63                 : {
             SiERROR("blindscan_interaction -- (warning) You probably run a DEBUG fw, so you need to define ALLOW_Si2183_BLINDSCAN_DEBUG at project level\n");
             break;
           }
#endif /* ALLOW_Si2183_BLINDSCAN_DEBUG */
          default : {
            SiTRACE("unknown scan_status %d\n", front_end->demod->rsp->scan_status.scan_status);
            skip_resume = 1;
            break;
          }
        }

        if (skip_resume == 0) {
          SiTRACE ("blindscan_interaction >> (resume) Si2183_L1_SCAN_CTRL( front_end->demod, %d, %8d)\n", front_end->demod->cmd->scan_ctrl.action, seek_freq_kHz);
          return_code = Si2183_L1_SCAN_CTRL (front_end->demod,              front_end->demod->cmd->scan_ctrl.action, seek_freq_kHz);
          if (return_code != NO_Si2183_ERROR) {
            SiTRACE ( "Si2183_L1_SCAN_CTRL ERROR at %d (%d)\n!!!!!!!!!!!!!!!!!!!!!!!\n", seek_freq_kHz, front_end->demod->rsp->scan_status.scan_status);
            SiERROR ( "Si2183_L1_SCAN_CTRL 'RESUME' ERROR during seek loop\n");
          }
        }
      }

      /* timeout management (this should never happen if timeout values are correctly set) */
      timeoutDelay = system_time() - front_end->timeoutStartTime;
      if (timeoutDelay >= max_decision_time_ms) {
        SiTRACE ("blindscan_interaction -- (timeout) Scan decision timeout from  %d after %d ms. Check your timeout limits!\n", seek_freq_kHz, timeoutDelay);
        SiERROR ("Scan decision timeout (blind_mode = 1)\n");
        Si2183_L2_Health_Check(front_end);
        front_end->seekAbort   = 1;
        front_end->handshakeOn = 0;
        decisionDelay   = system_time() - seekStartTime; front_end->cumulativeScanTime = front_end->cumulativeScanTime + decisionDelay; front_end->nbDecisions++;
        break;
      }

      if (front_end->handshakeUsed) {
        handshakeDelay = system_time() - front_end->handshakeStart_ms;
        if (handshakeDelay >= front_end->handshakePeriod_ms) {
          SiTRACE ("blindscan_handshake : handshake after %5d ms (at %10d). (search delay %6d ms) %*s\n", handshakeDelay, front_end->rangeMin, searchDelay, (searchDelay)/1000,"*");
         *freq                    = seek_freq;
          front_end->handshakeOn = 1;
          decisionDelay   = system_time() - seekStartTime; front_end->cumulativeScanTime = front_end->cumulativeScanTime + decisionDelay; front_end->nbDecisions++;
          /* The application will check handshakeStart_ms to know whether the blindscan is ended or not */
          return searchDelay + 2; /* Make sure we don't return '0' or '1' from here */
        } else {
          SiTRACE ("blindscan_handshake : no handshake yet. (handshake delay %6d ms, search delay %6d ms)\n", handshakeDelay, searchDelay);
        }
      }

      /* Check seekAbort flag (set in case of timeout or by the top-level application) */
      if (front_end->seekAbort) {
        /* Abort the SCAN loop to allow it to restart with the new rangeMin frequency */
        SiTRACE ("blindscan_interaction >> (abort!) Si2183_L1_SCAN_CTRL( front_end->demod, Si2183_SCAN_CTRL_CMD_ACTION_ABORT)\n");
                  Si2183_L1_SCAN_CTRL (front_end->demod, Si2183_SCAN_CTRL_CMD_ACTION_ABORT , 0);
        front_end->handshakeOn = 0;
        decisionDelay   = system_time() - seekStartTime; front_end->cumulativeScanTime = front_end->cumulativeScanTime + decisionDelay; front_end->nbDecisions++;
        return 0;
        break;
      }

      /* Check status every 100 ms */
      system_wait(100);

    }
  }
  front_end->handshakeOn = 0;
  return 0;
}
/************************************************************************************************************************
  NAME: Si2183_L2_Channel_Seek_Abort
  DESCRIPTION: aborts the seek
  Programming Guide Reference:    Flowchart TBD (Channel Scan flowchart)

  Parameter:  Pointer to Si2183 Context
  Returns:    0 if successful, otherwise an error.
************************************************************************************************************************/
signed   int  Si2183_L2_Channel_Seek_Abort (Si2183_L2_Context *front_end)
{
  front_end->seekAbort   = 1;
  front_end->handshakeOn = 0;
  Si2183_L1_SCAN_CTRL (front_end->demod, Si2183_SCAN_CTRL_CMD_ACTION_ABORT , 0);
  return 0;
}
/************************************************************************************************************************
  NAME: Si2183_L2_Channel_Lock_Abort
  DESCRIPTION: aborts the lock_to_carrier
  Programming Guide Reference:    Flowchart TBD (Channel Lock flowchart)

  Parameter:  Pointer to Si2183 Context
  Returns:    0 if successful, otherwise an error.
************************************************************************************************************************/
signed   int  Si2183_L2_Channel_Lock_Abort (Si2183_L2_Context *front_end)
{
  if (front_end->handshakeUsed == 0 ) {
    front_end->lockAbort   = 1;
  }
  if (front_end->handshakeUsed == 1 ) {
    front_end->handshakeOn = 0;
  }
  return 0;
}
/************************************************************************************************************************
  NAME: Si2183_L2_Channel_Seek_End
  DESCRIPTION: returns the chip back to normal use following a seek sequence
  Programming Guide Reference:    Flowchart TBD (Channel Scan flowchart)

  Parameter:  Pointer to Si2183 Context
  Returns:    0 if successful, otherwise an error.
************************************************************************************************************************/
signed   int  Si2183_L2_Channel_Seek_End   (Si2183_L2_Context *front_end)
{
  front_end = front_end; /* To avoid compiler warning */
#ifdef    DEMOD_DVB_C
#ifdef    Si2167B_BLINDSCAN_PATCH
  if  ((((front_end->demod->rsp->part_info.part == 67 ) & (front_end->demod->rsp->part_info.chiprev + 0x40 == 'B'))
     || ((front_end->demod->rsp->part_info.part == 65 ) & (front_end->demod->rsp->part_info.chiprev + 0x40 == 'B'))
    ) & ((front_end->demod->rsp->part_info.pmajor == '2') & (front_end->demod->rsp->part_info.pminor == '2')) ) {
    switch (front_end->demod->standard)
    {
      case Si2183_DD_MODE_PROP_MODULATION_MCNS    :
      case Si2183_DD_MODE_PROP_MODULATION_DVBC    : {
        front_end->previous_standard = Si2183_DD_MODE_PROP_MODULATION_DVBT;
        front_end->demod->load_DVB_C_Blindlock_Patch = 0;
        front_end->Si2183_init_done = 0;
        Si2183_L2_switch_to_standard(front_end, Si2183_DD_MODE_PROP_MODULATION_DVBC, 0);
        break;
      }
      default: break;
    }
  }
#endif /* Si2167B_BLINDSCAN_PATCH */
#endif /* DEMOD_DVB_C */

  front_end->demod->prop->scan_ien.buzien           = Si2183_SCAN_IEN_PROP_BUZIEN_DISABLE ; /* (default 'DISABLE') */
  front_end->demod->prop->scan_ien.reqien           = Si2183_SCAN_IEN_PROP_REQIEN_DISABLE ; /* (default 'DISABLE') */
  Si2183_L1_SetProperty2(front_end->demod, Si2183_SCAN_IEN_PROP_CODE);
  SiTRACE("front_end->cumulativeScanTime    %d %d'%d'' (%d decisions)\n", front_end->cumulativeScanTime   , front_end->cumulativeScanTime   /60000, (front_end->cumulativeScanTime   /1000)%60, front_end->nbDecisions );
  SiTRACE("front_end->cumulativeTimeoutTime %d %d'%d'' (%d timeouts )\n", front_end->cumulativeTimeoutTime, front_end->cumulativeTimeoutTime/60000, (front_end->cumulativeTimeoutTime/1000)%60, front_end->nbTimeouts  );
  switch (front_end->demod->standard)
  {
#ifdef    DEMOD_DVB_T
    case Si2183_DD_MODE_PROP_MODULATION_DVBT    : { front_end->demod->prop->dd_mode.modulation = Si2183_DD_MODE_PROP_MODULATION_DVBT ; break; }
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_DVB_C
    case Si2183_DD_MODE_PROP_MODULATION_DVBC    : {
      front_end->demod->prop->dvbc_afc_range.range_khz = front_end->cable_lock_afc_range_khz;
      Si2183_L1_SetProperty2(front_end->demod, Si2183_DVBC_AFC_RANGE_PROP_CODE);
      SiTRACE("DVB-C AFC range set back to %d\n", front_end->demod->prop->dvbc_afc_range.range_khz);
      front_end->demod->prop->dd_mode.modulation = Si2183_DD_MODE_PROP_MODULATION_DVBC ; break;
    }
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_MCNS
    case Si2183_DD_MODE_PROP_MODULATION_MCNS    : {
      front_end->demod->prop->mcns_afc_range.range_khz = front_end->cable_lock_afc_range_khz;
      Si2183_L1_SetProperty2(front_end->demod, Si2183_MCNS_AFC_RANGE_PROP_CODE);
      SiTRACE("MCNS  AFC range set back to %d\n", front_end->demod->prop->mcns_afc_range.range_khz);
      front_end->demod->prop->dd_mode.modulation = Si2183_DD_MODE_PROP_MODULATION_MCNS ; break;
    }
#endif /* DEMOD_MCNS */
#ifdef    DEMOD_DVB_T2
    case Si2183_DD_MODE_PROP_MODULATION_DVBT2   : { front_end->demod->prop->dd_mode.modulation = Si2183_DD_MODE_PROP_MODULATION_DVBT2; break; }
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_DVB_S_S2_DSS
    case Si2183_DD_MODE_PROP_MODULATION_DVBS    : { front_end->demod->prop->dd_mode.modulation = Si2183_DD_MODE_PROP_MODULATION_DVBS ; break; }
    case Si2183_DD_MODE_PROP_MODULATION_DVBS2   : { front_end->demod->prop->dd_mode.modulation = Si2183_DD_MODE_PROP_MODULATION_DVBS2; break; }
    case Si2183_DD_MODE_PROP_MODULATION_DSS     : { front_end->demod->prop->dd_mode.modulation = Si2183_DD_MODE_PROP_MODULATION_DSS  ; break; }
#endif /* DEMOD_DVB_S_S2_DSS */
    default                                     : { SiTRACE("UNKNOWN standard %d\n", front_end->demod->standard); break;}
  }

#ifdef    DEMOD_DVB_T2
  SiTRACE("auto_detect_TER %d\n",front_end->auto_detect_TER);
  if (front_end->auto_detect_TER) {
    switch (front_end->demod->standard)
    {
      case Si2183_DD_MODE_PROP_MODULATION_DVBT    :
      case Si2183_DD_MODE_PROP_MODULATION_DVBT2   : {
        front_end->demod->prop->dd_mode.modulation  = Si2183_DD_MODE_PROP_MODULATION_AUTO_DETECT;
        front_end->demod->prop->dd_mode.auto_detect = Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_T_T2;
      }
      default                                     : { break;}
    }
  }
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_DVB_S_S2_DSS
  if (front_end->auto_detect_SAT) {
    switch (front_end->demod->standard)
    {
      case Si2183_DD_MODE_PROP_MODULATION_DSS     :
      case Si2183_DD_MODE_PROP_MODULATION_DVBS    :
      case Si2183_DD_MODE_PROP_MODULATION_DVBS2   : {
        front_end->demod->prop->dd_mode.modulation  = Si2183_DD_MODE_PROP_MODULATION_AUTO_DETECT;
        if (front_end->demod->standard == Si2183_DD_MODE_PROP_MODULATION_DSS) {
          front_end->demod->prop->dd_mode.auto_detect = Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_S_S2_DSS;
        } else {
          front_end->demod->prop->dd_mode.auto_detect = Si2183_DD_MODE_PROP_AUTO_DETECT_AUTO_DVB_S_S2;
        }
      }
      default                                     : { break;}
    }
  }
#endif /* DEMOD_DVB_S_S2_DSS */
  Si2183_L1_SetProperty2(front_end->demod, Si2183_DD_MODE_PROP_CODE);

  return 0;
}
#ifdef    SATELLITE_FRONT_END
/************************************************************************************************************************
  NAME: Si2183_SatAutoDetect
  DESCRIPTION: Set the Si2183 in Sat Auto Detect mode

  Parameter:  Pointer to Si2183 Context
  Returns:    front_end->auto_detect_SAT
************************************************************************************************************************/
signed   int  Si2183_SatAutoDetect         (Si2183_L2_Context *front_end)
{
  front_end->auto_detect_SAT = 1;
  return front_end->auto_detect_SAT;
}
/************************************************************************************************************************
  NAME: Si2183_SatAutoDetectOff
  DESCRIPTION: Set the Si2183 in Sat Auto Detect 'off' mode

  Parameter:  Pointer to Si2183 Context
  Returns:    front_end->auto_detect_SAT
************************************************************************************************************************/
signed   int  Si2183_SatAutoDetectOff      (Si2183_L2_Context *front_end)
{
  front_end->auto_detect_SAT = 0;
  return front_end->auto_detect_SAT;
}
#endif /* SATELLITE_FRONT_END */
#ifdef    DEMOD_DVB_T2
/************************************************************************************************************************
  NAME: Si2183_TerAutoDetect
  DESCRIPTION: Set the Si2183 in Ter Auto Detect mode

  Parameter:  Pointer to Si2183 Context
  Returns:    front_end->auto_detect_TER
************************************************************************************************************************/
signed   int  Si2183_TerAutoDetect         (Si2183_L2_Context *front_end)
{
  if (   (front_end->demod->rsp->part_info.part == 60)
      || (front_end->demod->rsp->part_info.part == 63)
      || (front_end->demod->rsp->part_info.part == 65)
      || (front_end->demod->rsp->part_info.part == 66)
      || (front_end->demod->rsp->part_info.part == 67)
      || (front_end->demod->rsp->part_info.part == 80)
      || (front_end->demod->rsp->part_info.part == 81) ) {
    front_end->auto_detect_TER = 0;
    SiERROR("ERROR: your part doesn't support DVB-T2. auto_detect_TER forced to 0\n");
  } else {
    front_end->auto_detect_TER = 1;
  }
  return front_end->auto_detect_TER;
}
/************************************************************************************************************************
  NAME: Si2183_TerAutoDetectOff
  DESCRIPTION: Set the Si2183 in Ter Auto Detect 'off' mode

  Parameter:  Pointer to Si2183 Context
  Returns:    front_end->auto_detect_TER
************************************************************************************************************************/
signed   int  Si2183_TerAutoDetectOff      (Si2183_L2_Context *front_end)
{
  front_end->auto_detect_TER = 0;
  return front_end->auto_detect_TER;
}
#endif /* DEMOD_DVB_T2 */
signed   int   Si2183_L2_GET_REG           (Si2183_L2_Context *front_end, unsigned char   reg_code_lsb, unsigned char   reg_code_mid, unsigned char   reg_code_msb) {
  int res;
  SiTraceConfiguration("traces suspend");
  if (Si2183_L1_DD_GET_REG  (front_end->demod, reg_code_lsb, reg_code_mid, reg_code_msb) != NO_Si2183_ERROR) {
    SiERROR("Error calling Si2183_L1_DD_GET_REG\n");
    SiTraceConfiguration("traces resume");
    return 0;
  }
  SiTraceConfiguration("traces resume");
  res =  (front_end->demod->rsp->dd_get_reg.data4<<24)
        +(front_end->demod->rsp->dd_get_reg.data3<<16)
        +(front_end->demod->rsp->dd_get_reg.data2<<8 )
        +(front_end->demod->rsp->dd_get_reg.data1<<0 );
  return res;
}
#define get_reg(ptr, register)               SiTRACE("%s %3d  ", #register, Si2183_L2_GET_REG (ptr, Si2183_##register##_LSB, Si2183_##register##_MID, Si2183_##register##_MSB));
#define get_reg_from_code(ptr,register)      SiTRACE("%s %3d  ", #register, Si2183_L2_GET_REG (ptr, Si2183_##register##_CODE));
#if 1  /* Codes for GET_REG */
  #define Si2183_auto_relock_CODE          0,98,11
  #define Si2183_en_rst_error_CODE         0,8,11
  #define Si2183_demod_lock_t_CODE         0,20,9
  #define Si2183_fec_lock_t2_CODE          0,96,21
  #define Si2183_tbd_a_CODE               15,108,11
  #define Si2183_trap_type_CODE            7,10,11
  #define Si2183_firmware_sm_CODE          7,96,11
  #define Si2183_pre_crc_ok_CODE           0,62,13
  #define Si2183_pre_crc_nok_tog_CODE      0,64,13
  #define Si2183_l1_post_crc_ok_CODE       0,250,12
  #define Si2183_l1_post_crc_nok_tog_CODE  0,251,12
  #define Si2183_td_alarms_CODE            8,128,15
  #define Si2183_td_alarms_first_CODE      8,124,15
  #define Si2183_fd_alarms_CODE           31,36,15
  #define Si2183_fd_alarms_first_CODE     31,40,15
  #define Si2183_mp_a_mux_CODE             3,106,1
  #define Si2183_mp_b_mux_CODE             3,109,1
  #define Si2183_mp_c_mux_CODE             3,112,1
  #define Si2183_mp_d_mux_CODE             3,115,1
  #define Si2183_agc1_cmd_CODE             7,38,4
  #define Si2183_agc2_cmd_CODE             7,50,4
  #define Si2183_agc1_pola_CODE           33,36,4
  #define Si2183_agc2_pola_CODE           33,48,4
  #define Si2183_agc1_min_CODE             7,34,4
  #define Si2183_agc1_max_CODE             7,35,4
  #define Si2183_agc1_freeze_CODE          0,36,4
  #define Si2183_agc2_min_CODE             7,46,4
  #define Si2183_agc2_max_CODE             7,47,4
  #define Si2183_agc2_freeze_CODE          0,48,4
  #define Si2183_standard_CODE             5,116,4
  #define Si2183_mailbox61_CODE            7,165,0
  #define Si2183_wdog_error_CODE          66,9,11
  #define Si2183_program_counter_CODE     31,12,11
  #define Si2183_it_reg_CODE             165,103,1
  #define Si2183_it_reg_2_CODE             0,56,11
  #define Si2183_gp_reg_0_CODE            15,236,8
  #define Si2183_gp_reg8_0_CODE            7,88,11
  #define Si2183_gp_reg8_1_CODE            7,89,11
  #define Si2183_gp_reg8_2_CODE            7,90,11
  #define Si2183_gp_reg8_3_CODE            7,91,11
  #define Si2183_gp_reg16_0_CODE          15,80,11
  #define Si2183_gp_reg16_1_CODE          15,82,11
  #define Si2183_gp_reg16_2_CODE          15,84,11
  #define Si2183_gp_reg16_3_CODE          15,86,11
  #define Si2183_gp_reg32_0_CODE          31,68,11
  #define Si2183_gp_reg32_1_CODE          31,72,11
  #define Si2183_gp_reg32_2_CODE          31,76,11

#endif /* Codes for GET_REG */
signed   int   Si2183_L2_Health_Check      (Si2183_L2_Context *front_end) {
  signed   int standard;
  signed   int firmware_sm;
  signed   int mailbox61;
  signed   int tbd_a;
  signed   int wdog_error;
  signed   int trap_type;
  signed   int program_counter;
  signed   int it_reg;
  signed   int it_reg_2;
  signed   int gp_reg;
  signed   int gp_reg_8_0;
  signed   int gp_reg_8_1;
  signed   int gp_reg_8_2;
  signed   int gp_reg_8_3;
  signed   int gp_reg_16_0;
  signed   int gp_reg_16_1;
  signed   int gp_reg_16_2;
  signed   int gp_reg_16_3;
  signed   int gp_reg_32_0;
  signed   int gp_reg_32_1;
  signed   int gp_reg_32_2;

  standard    = Si2183_L2_GET_REG (front_end, Si2183_standard_CODE);
  firmware_sm = Si2183_L2_GET_REG (front_end, Si2183_firmware_sm_CODE);
  tbd_a       = Si2183_L2_GET_REG (front_end, Si2183_tbd_a_CODE);
  mailbox61   = Si2183_L2_GET_REG (front_end, Si2183_mailbox61_CODE);
  wdog_error  = Si2183_L2_GET_REG (front_end, Si2183_wdog_error_CODE);
  trap_type   = Si2183_L2_GET_REG (front_end, Si2183_trap_type_CODE);
  program_counter   = Si2183_L2_GET_REG (front_end, Si2183_program_counter_CODE);
  it_reg            = Si2183_L2_GET_REG (front_end, Si2183_it_reg_CODE);
  it_reg_2          = Si2183_L2_GET_REG (front_end, Si2183_it_reg_2_CODE);

  SiTRACE("std %2d, fw_sm %4d / tbd_a %4d / mb61 %4d / wdog %4d / trap_type %4d / program_counter %4d / it_reg %d / it_reg_2 %d \n", standard, firmware_sm, tbd_a, mailbox61, wdog_error, trap_type, program_counter,it_reg, it_reg_2);

  gp_reg            = Si2183_L2_GET_REG (front_end, Si2183_gp_reg_0_CODE);
  gp_reg_8_0        = Si2183_L2_GET_REG (front_end, Si2183_gp_reg8_0_CODE);
  gp_reg_8_1        = Si2183_L2_GET_REG (front_end, Si2183_gp_reg8_1_CODE);
  gp_reg_8_2        = Si2183_L2_GET_REG (front_end, Si2183_gp_reg8_2_CODE);
  gp_reg_8_3        = Si2183_L2_GET_REG (front_end, Si2183_gp_reg8_3_CODE);
  gp_reg_16_0        = Si2183_L2_GET_REG (front_end, Si2183_gp_reg16_0_CODE);
  gp_reg_16_1        = Si2183_L2_GET_REG (front_end, Si2183_gp_reg16_1_CODE);
  gp_reg_16_2        = Si2183_L2_GET_REG (front_end, Si2183_gp_reg16_2_CODE);
  gp_reg_16_3        = Si2183_L2_GET_REG (front_end, Si2183_gp_reg16_3_CODE);
  gp_reg_32_0        = Si2183_L2_GET_REG (front_end, Si2183_gp_reg32_0_CODE);
  gp_reg_32_1        = Si2183_L2_GET_REG (front_end, Si2183_gp_reg32_1_CODE);
  gp_reg_32_2        = Si2183_L2_GET_REG (front_end, Si2183_gp_reg32_2_CODE);

  SiTRACE("gp_reg %2d, gp_reg_8_0 %d / gp_reg_8_1 %d / gp_reg_8_2 %d / gp_reg_8_3 %d / gp_reg_16_0 %2d / gp_reg_16_1 %2d / gp_reg_16_2 %2d / gp_reg_16_3 %2d \n", gp_reg, gp_reg_8_0, gp_reg_8_1, gp_reg_8_2, gp_reg_8_3, gp_reg_16_0, gp_reg_16_1,gp_reg_16_2, gp_reg_16_3);
  SiTRACE("gp_reg_32_0 %4d / gp_reg_32_1 %4d / gp_reg_32_2 %4d \n", gp_reg_32_0, gp_reg_32_1,gp_reg_32_2);

  return 1;
}
#ifdef    SILABS_API_TEST_PIPE
#ifdef    SiTRACES
#if 1

#define Si2183_get_reg(ptr,register)       Si2183_L2_GET_REG            (ptr, Si2183_##register##_LSB, Si2183_##register##_MID, Si2183_##register##_MSB)

#define Si2183_pre_type_LSB   7
#define Si2183_pre_type_MID   24
#define Si2183_pre_type_MSB   13

#define Si2183_pre_bwt_ext_LSB   0
#define Si2183_pre_bwt_ext_MID   25
#define Si2183_pre_bwt_ext_MSB   13

#define Si2183_pre_s1_LSB   2
#define Si2183_pre_s1_MID   26
#define Si2183_pre_s1_MSB   13

#define Si2183_pre_s2_LSB   3
#define Si2183_pre_s2_MID   27
#define Si2183_pre_s2_MSB   13

#define Si2183_pre_l1_repetition_flag_LSB   0
#define Si2183_pre_l1_repetition_flag_MID   28
#define Si2183_pre_l1_repetition_flag_MSB   13

#define Si2183_pre_guard_interval_LSB   2
#define Si2183_pre_guard_interval_MID   29
#define Si2183_pre_guard_interval_MSB   13

#define Si2183_pre_papr_LSB   3
#define Si2183_pre_papr_MID   30
#define Si2183_pre_papr_MSB   13

#define Si2183_pre_l1_mod_LSB   3
#define Si2183_pre_l1_mod_MID   31
#define Si2183_pre_l1_mod_MSB   13

#define Si2183_pre_l1_cod_LSB   1
#define Si2183_pre_l1_cod_MID   32
#define Si2183_pre_l1_cod_MSB   13

#define Si2183_pre_l1_fec_type_LSB   1
#define Si2183_pre_l1_fec_type_MID   33
#define Si2183_pre_l1_fec_type_MSB   13

#define Si2183_pre_l1_post_size_LSB   17
#define Si2183_pre_l1_post_size_MID   36
#define Si2183_pre_l1_post_size_MSB   13

#define Si2183_pre_l1_post_info_size_LSB   17
#define Si2183_pre_l1_post_info_size_MID   40
#define Si2183_pre_l1_post_info_size_MSB   13

#define Si2183_pre_pilot_pattern_LSB   3
#define Si2183_pre_pilot_pattern_MID   44
#define Si2183_pre_pilot_pattern_MSB   13

#define Si2183_pre_tx_id_availability_LSB   7
#define Si2183_pre_tx_id_availability_MID   45
#define Si2183_pre_tx_id_availability_MSB   13

#define Si2183_pre_cell_id_LSB   15
#define Si2183_pre_cell_id_MID   46
#define Si2183_pre_cell_id_MSB   13

#define Si2183_pre_network_id_LSB   15
#define Si2183_pre_network_id_MID   48
#define Si2183_pre_network_id_MSB   13

#define Si2183_pre_t2_system_id_LSB   15
#define Si2183_pre_t2_system_id_MID   50
#define Si2183_pre_t2_system_id_MSB   13

#define Si2183_pre_num_t2_frames_LSB   7
#define Si2183_pre_num_t2_frames_MID   52
#define Si2183_pre_num_t2_frames_MSB   13

#define Si2183_pre_num_data_symbols_LSB   11
#define Si2183_pre_num_data_symbols_MID   54
#define Si2183_pre_num_data_symbols_MSB   13

#define Si2183_pre_regen_flag_LSB   2
#define Si2183_pre_regen_flag_MID   56
#define Si2183_pre_regen_flag_MSB   13

#define Si2183_pre_l1_post_extension_LSB   0
#define Si2183_pre_l1_post_extension_MID   57
#define Si2183_pre_l1_post_extension_MSB   13

#define Si2183_pre_num_rf_LSB   2
#define Si2183_pre_num_rf_MID   58
#define Si2183_pre_num_rf_MSB   13

#define Si2183_pre_reserved_LSB   5
#define Si2183_pre_reserved_MID   61
#define Si2183_pre_reserved_MSB   13

#define Si2183_num_rf_LSB   2
#define Si2183_num_rf_MID   210
#define Si2183_num_rf_MSB   13

#define Si2183_pre_current_rf_idx_LSB   2
#define Si2183_pre_current_rf_idx_MID   59
#define Si2183_pre_current_rf_idx_MSB   13

#define Si2183_pre_t2_version_LSB   3
#define Si2183_pre_t2_version_MID   60
#define Si2183_pre_t2_version_MSB   13

#define Si2183_bbdf_data_issyi_status_LSB   1
#define Si2183_bbdf_data_issyi_status_MID   122
#define Si2183_bbdf_data_issyi_status_MSB   20

#define Si2183_bbdf_comm_issyi_status_LSB   1
#define Si2183_bbdf_comm_issyi_status_MID   123
#define Si2183_bbdf_comm_issyi_status_MSB   20

#define Si2183_bbdf_data_npd_active_LSB   0
#define Si2183_bbdf_data_npd_active_MID   120
#define Si2183_bbdf_data_npd_active_MSB   20

#define Si2183_bbdf_comm_npd_active_LSB   0
#define Si2183_bbdf_comm_npd_active_MID   121
#define Si2183_bbdf_comm_npd_active_MSB   20

#define Si2183_djb_alarm_data_LSB   11
#define Si2183_djb_alarm_data_MID   48
#define Si2183_djb_alarm_data_MSB   22

#define Si2183_djb_alarm_comm_LSB   11
#define Si2183_djb_alarm_comm_MID   50
#define Si2183_djb_alarm_comm_MSB   22

#define Si2183_ts_rate_in_LSB   27
#define Si2183_ts_rate_in_MID   72
#define Si2183_ts_rate_in_MSB   22

#define Si2183_storing_enable_LSB   0
#define Si2183_storing_enable_MID   72
#define Si2183_storing_enable_MSB   14

#define Si2183_stored_l1_post_nb_LSB   12
#define Si2183_stored_l1_post_nb_MID   74
#define Si2183_stored_l1_post_nb_MSB   14

#define Si2183_start_ibs_storing_data_LSB   10
#define Si2183_start_ibs_storing_data_MID   76
#define Si2183_start_ibs_storing_data_MSB   14

#define Si2183_store_l1_post_en_LSB   33
#define Si2183_store_l1_post_en_MID   72
#define Si2183_store_l1_post_en_MSB   14

#define Si2183_base_read_address_LSB   10
#define Si2183_base_read_address_MID   84
#define Si2183_base_read_address_MSB   14

#define Si2183_read_data_LSB   31
#define Si2183_read_data_MID   88
#define Si2183_read_data_MSB   14

#define Si2183_read_data_latch_LSB   33
#define Si2183_read_data_latch_MID   114
#define Si2183_read_data_latch_MSB   12

#define Si2164_storing_enable_LSB 0
#define Si2164_storing_enable_MID 92
#define Si2164_storing_enable_MSB 13

#define Si2164_stored_l1_post_nb_LSB 12
#define Si2164_stored_l1_post_nb_MID 94
#define Si2164_stored_l1_post_nb_MSB 13

#define Si2164_start_ibs_storing_data_LSB 10
#define Si2164_start_ibs_storing_data_MID 96
#define Si2164_start_ibs_storing_data_MSB 13

#define Si2164_store_l1_post_en_LSB 33
#define Si2164_store_l1_post_en_MID 92
#define Si2164_store_l1_post_en_MSB 13

#define Si2164_base_read_address_LSB 10
#define Si2164_base_read_address_MID 104
#define Si2164_base_read_address_MSB 13

#define Si2164_read_data_LSB 31
#define Si2164_read_data_MID 108
#define Si2164_read_data_MSB 13

#define Si2164_read_data_latch_LSB   33
#define Si2164_read_data_latch_MID  134
#define Si2164_read_data_latch_MSB   11


#define Si2167B_storing_enable_LSB   0
#define Si2167B_storing_enable_MID   72
#define Si2167B_storing_enable_MSB   14

#define Si2167B_stored_l1_post_nb_LSB   12
#define Si2167B_stored_l1_post_nb_MID   74
#define Si2167B_stored_l1_post_nb_MSB   14

#define Si2167B_start_ibs_storing_data_LSB   10
#define Si2167B_start_ibs_storing_data_MID   76
#define Si2167B_start_ibs_storing_data_MSB   14

#define Si2167B_store_l1_post_en_LSB   33
#define Si2167B_store_l1_post_en_MID   72
#define Si2167B_store_l1_post_en_MSB   14

#define Si2167B_base_read_address_LSB   10
#define Si2167B_base_read_address_MID   84
#define Si2167B_base_read_address_MSB   14

#define Si2167B_read_data_LSB   31
#define Si2167B_read_data_MID   88
#define Si2167B_read_data_MSB   14

#define Si2167B_read_data_latch_LSB   33
#define Si2167B_read_data_latch_MID   114
#define Si2167B_read_data_latch_MSB   12

#endif
#ifdef    _DVB_T2_SIGNALLING_H_
unsigned int   Si2183_n_bits             (unsigned int *wordTable, int n, unsigned int *bitIndex) {
  signed   int startByteIndex;
  signed   int stopByteIndex;
  signed   int leftBitShift;
  signed   int bitShift;
  signed   int wordShift;
  signed   int intSize;
  signed   int b;
  unsigned int res;
/*  SiTRACE_X("Si2183_n_bits(wordTable, %2d, %4d) (%d)\n", n, *bitIndex, *bitIndex/8);*/
  intSize        = sizeof(int)*8;
  res            = 0x00000000;
  wordShift      = 0;
  startByteIndex =  *bitIndex/intSize;
  stopByteIndex  = (*bitIndex+n-1)/intSize;
  leftBitShift   = (*bitIndex) - (startByteIndex*intSize);
  bitShift       = ((stopByteIndex+1)*intSize) - (*bitIndex+n);
  *bitIndex      = *bitIndex + n;
  for (b = startByteIndex; b <= stopByteIndex; b++) {
    res = res + (wordTable[b]<<wordShift);
    if (b == startByteIndex) {
      res = res << leftBitShift;
      res = res >> leftBitShift;
    }
    wordShift = wordShift+intSize;
  }
  res = res >> bitShift;
/*  SiTRACE_X("0x%08x (%12d)\n", res, res);*/
  return res;
}
int   Si2183_L2_Read_L1_Misc_Data        (Si2183_L2_Context *front_end, SiLabs_T2_Misc_Signalling    *misc) {
  signed   int issyi_status;
  misc->bw                 = front_end->demod->prop->dd_mode.bw;
  issyi_status             = Si2183_get_reg (front_end, bbdf_data_issyi_status);
       if (issyi_status == 0) {misc->data_issy = 1; misc->data_issy_ts_long  = 1; }
  else if (issyi_status == 1) {misc->data_issy = 1; misc->data_issy_ts_long  = 0; }
  else if (issyi_status == 2) {misc->data_issy = 0; misc->data_issy_ts_long  = 0; }
  misc->data_npd           = Si2183_get_reg (front_end, bbdf_data_npd_active);
  misc->data_ts_rate       = Si2183_get_reg (front_end, ts_rate_in);
  misc->data_djb_alarm     = Si2183_get_reg (front_end, djb_alarm_data);
  issyi_status             = Si2183_get_reg (front_end, bbdf_comm_issyi_status);
       if (issyi_status == 0) {misc->comm_issy = 1; misc->comm_issy_ts_long  = 1; }
  else if (issyi_status == 1) {misc->comm_issy = 1; misc->comm_issy_ts_long  = 0; }
  else if (issyi_status == 2) {misc->comm_issy = 0; misc->comm_issy_ts_long  = 0; }
  misc->comm_npd           = Si2183_get_reg (front_end, bbdf_comm_npd_active);
  misc->comm_ts_rate       = 0;
  misc->comm_djb_alarm     = Si2183_get_reg (front_end, djb_alarm_comm);
  return 1;
}
int   Si2183_L2_Read_L1_Pre_Data         (Si2183_L2_Context *front_end, SiLabs_T2_L1_Pre_Signalling  *pre ) {
  pre->type               = Si2183_get_reg (front_end, pre_type);
  pre->bwt_ext            = Si2183_get_reg (front_end, pre_bwt_ext);
  pre->s1                 = Si2183_get_reg (front_end, pre_s1);
  pre->s2                 = Si2183_get_reg (front_end, pre_s2);
  pre->l1_repetition_flag = Si2183_get_reg (front_end, pre_l1_repetition_flag);
  pre->guard_interval     = Si2183_get_reg (front_end, pre_guard_interval);
  pre->papr               = Si2183_get_reg (front_end, pre_papr);
  pre->l1_mod             = Si2183_get_reg (front_end, pre_l1_mod);
  pre->l1_cod             = Si2183_get_reg (front_end, pre_l1_cod);
  pre->l1_fec_type        = Si2183_get_reg (front_end, pre_l1_fec_type);
  pre->l1_post_size       = Si2183_get_reg (front_end, pre_l1_post_size);
  pre->l1_post_info_size  = Si2183_get_reg (front_end, pre_l1_post_info_size);
  pre->pilot_pattern      = Si2183_get_reg (front_end, pre_pilot_pattern);
  pre->tx_id_availability = Si2183_get_reg (front_end, pre_tx_id_availability);
  pre->cell_id            = Si2183_get_reg (front_end, pre_cell_id);
  pre->network_id         = Si2183_get_reg (front_end, pre_network_id);
  pre->t2_system_id       = Si2183_get_reg (front_end, pre_t2_system_id);
  pre->num_t2_frames      = Si2183_get_reg (front_end, pre_num_t2_frames);
  pre->num_data_symbols   = Si2183_get_reg (front_end, pre_num_data_symbols);
  pre->regen_flag         = Si2183_get_reg (front_end, pre_regen_flag);
  pre->l1_post_extension  = Si2183_get_reg (front_end, pre_l1_post_extension);
  pre->num_rf             = Si2183_get_reg (front_end, pre_num_rf);
  pre->current_rf_idx     = Si2183_get_reg (front_end, pre_current_rf_idx);
  pre->t2_version         = Si2183_get_reg (front_end, pre_t2_version);
  return 1;
}
int   Si2183_L2_Read_L1_Post_Data        (Si2183_L2_Context *front_end, SiLabs_T2_L1_Post_Signalling *post) {
  signed   int stored_l1_post_nb;
  signed   int start_ibs_storing_data;
  signed   int read_data;
  signed   int max_l1_storing;
  signed   int word_index;
  unsigned int i;
  unsigned int bitIndex;
  signed   int storing_enable;
  unsigned int  intTable[2048];
  unsigned int *wordTable;

  wordTable  = &intTable[0];

  /* Read L1 Post table data */
  word_index = 0;
  Si2183_READ(front_end->demod, storing_enable);
  if (storing_enable==0) {
    Si2183_WRITE(front_end->demod, storing_enable, 1);
    system_wait(5000);
  }

  Si2183_READ (front_end->demod, stored_l1_post_nb);
  Si2183_READ (front_end->demod, start_ibs_storing_data);
  max_l1_storing = start_ibs_storing_data;
  Si2183_WRITE(front_end->demod, base_read_address, 0);
  Si2183_WRITE(front_end->demod, read_data_latch, 1);
  SiTRACE("Load L1 signalling (%s) from the storing memory (%d x 32 bits words).\n", Si2183_standardName(front_end->demod->rsp->dd_status.modulation), stored_l1_post_nb);
  SiTRACE("reading until min of %d and %d\n", stored_l1_post_nb-1, max_l1_storing);

  while ( (word_index < stored_l1_post_nb-1) && (word_index < max_l1_storing) ) {
    Si2183_READ (front_end->demod, read_data);
    Si2183_WRITE(front_end->demod, read_data_latch, 1);
    SiTRACE("word %3d = 0x%08x\n", word_index, read_data);
    wordTable[word_index++] = read_data;
  }
  SiTRACE("\n");
  Si2183_WRITE(front_end->demod, store_l1_post_en, 1);

  word_index = 0;
  while ( (word_index < stored_l1_post_nb-1) && (word_index < max_l1_storing) ) {
    SiTRACE("%08x ", wordTable[word_index]);
    word_index++;
  }
  SiTRACE("\n");

  /* Parse L1 Post table data */
  bitIndex = 0;

  post->configurable.num_rf               = Si2183_get_reg (front_end, num_rf);
  post->configurable.s2                   = Si2183_get_reg (front_end, pre_s2);
  post->configurable.sub_slices_per_frame = Si2183_n_bits(wordTable, 15, &bitIndex);
  post->configurable.num_plp              = Si2183_n_bits(wordTable,  8, &bitIndex);
  post->configurable.num_aux              = Si2183_n_bits(wordTable,  4, &bitIndex);
  post->configurable.aux_config_rfu       = Si2183_n_bits(wordTable,  8, &bitIndex);
  for (i=0; i < post->configurable.num_rf; i++) {
  post->configurable.rf[i].rf_idx         = Si2183_n_bits(wordTable,  3, &bitIndex);
  post->configurable.rf[i].frequency      = Si2183_n_bits(wordTable, 32, &bitIndex);
  }
  if ( (post->configurable.s2&0x0f) == 0x01) {
  post->configurable.fef_type             = Si2183_n_bits(wordTable,  4, &bitIndex);
  post->configurable.fef_length           = Si2183_n_bits(wordTable, 22, &bitIndex);
  post->configurable.fef_interval         = Si2183_n_bits(wordTable,  8, &bitIndex);
  }
  for (i = 0; i < post->configurable.num_plp; i++) {
  post->configurable.plp[i].plp_id               = Si2183_n_bits(wordTable,  8, &bitIndex);
  post->configurable.plp[i].plp_type             = Si2183_n_bits(wordTable,  3, &bitIndex);
  post->configurable.plp[i].plp_payload_type     = Si2183_n_bits(wordTable,  5, &bitIndex);
  post->configurable.plp[i].ff_flag              = Si2183_n_bits(wordTable,  1, &bitIndex);
  post->configurable.plp[i].first_rf_idx         = Si2183_n_bits(wordTable,  3, &bitIndex);
  post->configurable.plp[i].first_frame_idx      = Si2183_n_bits(wordTable,  8, &bitIndex);
  post->configurable.plp[i].plp_group_id         = Si2183_n_bits(wordTable,  8, &bitIndex);
  post->configurable.plp[i].plp_cod              = Si2183_n_bits(wordTable,  3, &bitIndex);
  post->configurable.plp[i].plp_mod              = Si2183_n_bits(wordTable,  3, &bitIndex);
  post->configurable.plp[i].plp_rotation         = Si2183_n_bits(wordTable,  1, &bitIndex);
  post->configurable.plp[i].plp_fec_type         = Si2183_n_bits(wordTable,  2, &bitIndex);
  post->configurable.plp[i].plp_num_blocks_max   = Si2183_n_bits(wordTable, 10, &bitIndex);
  post->configurable.plp[i].frame_interval       = Si2183_n_bits(wordTable,  8, &bitIndex);
  post->configurable.plp[i].time_il_length       = Si2183_n_bits(wordTable,  8, &bitIndex);
  post->configurable.plp[i].time_il_type         = Si2183_n_bits(wordTable,  1, &bitIndex);
  post->configurable.plp[i].in_band_a_flag       = Si2183_n_bits(wordTable,  1, &bitIndex);
  post->configurable.plp[i].in_band_b_flag       = Si2183_n_bits(wordTable,  1, &bitIndex);
  post->configurable.plp[i].reserved_1           = Si2183_n_bits(wordTable, 11, &bitIndex);
  post->configurable.plp[i].plp_mode             = Si2183_n_bits(wordTable,  2, &bitIndex);
  post->configurable.plp[i].static_flag          = Si2183_n_bits(wordTable,  1, &bitIndex);
  post->configurable.plp[i].static_padding_flag  = Si2183_n_bits(wordTable,  1, &bitIndex);
  }
  post->configurable.fef_length_msb              = Si2183_n_bits(wordTable,  2, &bitIndex);
  post->configurable.reserved_2                  = Si2183_n_bits(wordTable, 30, &bitIndex);
  for (i=0; i<post->configurable.num_aux; i++) {
  post->configurable.aux[i].aux_stream_type      = Si2183_n_bits(wordTable,  4, &bitIndex);
  post->configurable.aux[i].aux_private_conf     = Si2183_n_bits(wordTable, 28, &bitIndex);
  }
  post->dynamic.frame_idx            = Si2183_n_bits(wordTable,  8, &bitIndex);
  post->dynamic.sub_slice_interval   = Si2183_n_bits(wordTable, 22, &bitIndex);
  post->dynamic.type_2_start         = Si2183_n_bits(wordTable, 22, &bitIndex);
  post->dynamic.l1_change_counter    = Si2183_n_bits(wordTable,  8, &bitIndex);
  post->dynamic.start_rf_idx         = Si2183_n_bits(wordTable,  3, &bitIndex);
  post->dynamic.reserved_1           = Si2183_n_bits(wordTable,  8, &bitIndex);
  for (i=0; i< post->configurable.num_plp; i++) {
  post->dynamic.plp[i].plp_id               = Si2183_n_bits(wordTable,  8, &bitIndex);
  post->dynamic.plp[i].plp_start            = Si2183_n_bits(wordTable, 22, &bitIndex);
  post->dynamic.plp[i].plp_num_blocks       = Si2183_n_bits(wordTable, 10, &bitIndex);
  post->dynamic.plp[i].reserved_2           = Si2183_n_bits(wordTable,  8, &bitIndex);
  }
  post->dynamic.reserved_3           = Si2183_n_bits(wordTable,  8, &bitIndex);
  for (i=0; i <post->configurable.num_aux; i++) {
  post->dynamic.aux_private_dyn[i].msb  = Si2183_n_bits(wordTable, 24, &bitIndex);
  post->dynamic.aux_private_dyn[i].lsb  = Si2183_n_bits(wordTable, 24, &bitIndex);
  }
  return 1;
}
#endif /* _DVB_T2_SIGNALLING_H_ */
#endif /* SiTRACES */
signed   int   Si2183_L2_CheckLoop         (Si2183_L2_Context *front_end) {

  get_reg_from_code(front_end,mp_a_mux);
  get_reg_from_code(front_end,mp_b_mux);
  get_reg_from_code(front_end,mp_c_mux);
  get_reg_from_code(front_end,mp_d_mux);

  get_reg_from_code(front_end,firmware_sm);
  get_reg_from_code(front_end,agc1_min);
  get_reg_from_code(front_end,agc2_min);
  get_reg_from_code(front_end,agc1_max);
  get_reg_from_code(front_end,agc2_max);
  get_reg_from_code(front_end,agc1_pola);
  get_reg_from_code(front_end,agc2_pola);
  get_reg_from_code(front_end,agc1_freeze);
  get_reg_from_code(front_end,agc2_freeze);
  get_reg_from_code(front_end,agc1_cmd);
  get_reg_from_code(front_end,agc2_cmd);

  printf("\n");

  printf("\n");
  return 1;
}
signed   int   Si2183_L2_Test_MPLP           (Si2183_L2_Context *front_end, double freq) {
  signed   int data_plp_count;
#ifdef    DEMOD_DVB_T2
  signed   int num_plp;
  signed   int plp_index;
  signed   int plp_id;
  signed   int plp_type;
  signed   int lock_wait_start_ms;
#endif /* DEMOD_DVB_T2 */
  front_end = front_end;
  freq = freq;
  data_plp_count = 0;
#ifdef    DEMOD_DVB_T2
  lock_wait_start_ms = system_time();
  Si2183_L2_lock_to_carrier (front_end, Si2183_DD_MODE_PROP_MODULATION_DVBT2, freq, 8000000, 0, 0, 0
#ifdef    DEMOD_DVB_C2
                             , 0
#endif /* DEMOD_DVB_C2 */
                             , -1
                             , 0
                             );
  if (front_end->demod->rsp->dd_status.dl == 0) {
    SiTRACE("Demod timeout after %4d ms\n", system_time() -  lock_wait_start_ms);
    return 0;
  }
  /* Locked; Now check DVBT2 status */
  if (Si2183_L1_DVBT2_STATUS    (front_end->demod, Si2183_DVBT2_STATUS_CMD_INTACK_OK) != NO_Si2183_ERROR) {
    SiTRACE("Si2183_L1_DVBT2_STATUS error\n");
    return 0;
  }
  SiTRACE("dvbt2_status.pcl     %d\n", front_end->demod->rsp->dvbt2_status.pcl);
  SiTRACE("dvbt2_status.num_plp %d\n", front_end->demod->rsp->dvbt2_status.num_plp);
  SiTRACE("dvbt2_status.plp_id  %d\n", front_end->demod->rsp->dvbt2_status.plp_id);
  num_plp = front_end->demod->rsp->dvbt2_status.num_plp;
  SiTRACE("There are %d PLPs in this stream\n", num_plp);
  data_plp_count = 0;
  for (plp_index=0; plp_index<num_plp; plp_index++) {
    Si2183_L1_DVBT2_PLP_INFO (front_end->demod, plp_index);
    plp_id   = front_end->demod->rsp->dvbt2_plp_info.plp_id;
    plp_type = front_end->demod->rsp->dvbt2_plp_info.plp_type;
    SiTRACE("PLP index %3d: PLP ID %3d, PLP TYPE %d : ", plp_index, plp_id, plp_type);
    if (plp_type == Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_TYPE_COMMON) {
      SiTRACE("COMMON PLP at index %3d: PLP ID %3d, PLP TYPE %d\n", plp_index, plp_id, plp_type);
    } else {
      SiTRACE("DATA   PLP at index %3d: PLP ID %3d, PLP TYPE %d\n", plp_index, plp_id, plp_type);
      data_plp_count++;
    }
  }
#endif /* DEMOD_DVB_T2 */
  return data_plp_count;
}
unsigned char Si2183_iq_demap = 0;
signed   int   Si2183_L2_Get_Constellation_IQ_rx_type (Si2183_L2_Context   *front_end, unsigned char rx_type_value) {
  signed   int  return_code;
 #if 1  /* Register write for IQ */
  #define Si2183_IQ_WRITE(ptr, register, value)  if (ptr->rsp->part_info.pmajor == '4' ) { return_code = Si2183_L1_DD_SET_REG (ptr, Si2164_##register##_CODE,  value );}\
                                            else if (ptr->rsp->part_info.pmajor == '3' ) { return_code = Si2183_L1_DD_SET_REG (ptr, Si2169_##register##_CODE,  value);}\
                                            else if (ptr->rsp->part_info.pmajor == '2' ) { return_code = Si2183_L1_DD_SET_REG (ptr, Si2167B_##register##_CODE, value);}\
                                            else                                         { return_code = Si2183_L1_DD_SET_REG (ptr, Si2183_##register##_CODE,  value );}

 /* sym_iq_start/stop from 0 to 32767 */
  #define Si2164_symb_iq_start_CODE  14,108,6
  #define Si2164_symb_iq_stop_CODE   14,110,6
  #define Si2164_rx_type_CODE        2,245,13

  #define Si2169_symb_iq_start_CODE  14,64,6
  #define Si2169_symb_iq_stop_CODE   14,66,6
  #define Si2169_rx_type_CODE        199,27,12

  #define Si2167B_symb_iq_start_CODE  14,68,6
  #define Si2167B_symb_iq_stop_CODE   14,70,6
  #define Si2167B_rx_type_CODE        0,0,0

  #define Si2183_symb_iq_start_CODE  14,48,7
  #define Si2183_symb_iq_stop_CODE   14,50,7
  #define Si2183_rx_type_CODE        2,225,14

 #endif /* Register write for IQ */

  #define Si2183_rx_type_l1_pre      0
  #define Si2183_rx_type_l1_post     1
  #define Si2183_rx_type_data_plp    2
  #define Si2183_rx_type_common_plp  3
  #define Si2183_rx_type_all         4
  #define Si2183_rx_type_off         5

  if (rx_type_value  < 6) {
    Si2183_iq_demap = 1;
  } else {
    Si2183_iq_demap = 0;
  }
  Si2183_IQ_WRITE (front_end->demod, rx_type, rx_type_value);
  return return_code;
}
signed   int   Si2183_L2_Get_Constellation_IQ         (Si2183_L2_Context   *front_end, signed   int *i, signed   int *q) {
  signed   int  return_code;
  unsigned int  imask;
  unsigned int  qmask;
  unsigned int  ishift;
  unsigned int  iq_coef;
  unsigned int  limit;
  unsigned int  value;
  unsigned int  sign_bit;
  int  ival;
  int  qval;

  *i = *q = 0;
 #if 1  /* Register read for IQ */
  #define Si2183_IQ_READ(ptr, register)          if (ptr->rsp->part_info.pmajor == '4' ) { return_code = Si2183_L1_DD_GET_REG (ptr, Si2164_##register##_CODE );}\
                                            else if (ptr->rsp->part_info.pmajor == '3' ) { return_code = Si2183_L1_DD_GET_REG (ptr, Si2169_##register##_CODE );}\
                                            else if (ptr->rsp->part_info.pmajor == '2' ) { return_code = Si2183_L1_DD_GET_REG (ptr, Si2167B_##register##_CODE);}\
                                            else                                         { return_code = Si2183_L1_DD_GET_REG (ptr, Si2183_##register##_CODE );}

  #define Si2164_symb_iq_CODE       19,104,6
  #define Si2164_iq_symb_CODE       31,184,7
  #define Si2164_iq_demod_sat_CODE  15,184,5
  #define Si2164_rx_iq_CODE         31,240,13

  #define Si2169_symb_iq_CODE       15,60,6
  #define Si2169_iq_symb_CODE       31,60,7
  #define Si2169_iq_demod_sat_CODE  15,160,5
  #define Si2169_rx_iq_CODE         31,20,12

  #define Si2167B_symb_iq_CODE      15,64,6
  #define Si2167B_iq_symb_CODE      31,160,7
  #define Si2167B_iq_demod_sat_CODE 15,248,5
  #define Si2167B_rx_iq_CODE        0,0,0

  #define Si2183_symb_iq_CODE       19,44,7
  #define Si2183_iq_symb_CODE       31,232,8
  #define Si2183_iq_demod_sat_CODE  15,248,5
  #define Si2183_rx_iq_CODE         31,220,14

  #define Si2183_symb_iq_start_CODE   14,48,7
  #define Si2183_symb_iq_stop_CODE    14,50,7

 #endif /* Register read for IQ */

  switch (front_end->demod->standard)
  {
    case Si2183_DD_MODE_PROP_MODULATION_DVBC2:
    case Si2183_DD_MODE_PROP_MODULATION_DVBT :
    case Si2183_DD_MODE_PROP_MODULATION_ISDBT:
    case Si2183_DD_MODE_PROP_MODULATION_DVBT2: {
      if (Si2183_iq_demap != 0) {
        Si2183_IQ_READ (front_end->demod, rx_iq);
      } else {
        Si2183_IQ_READ (front_end->demod, symb_iq);
      }
      imask = 0x000ffc00 ; qmask = 0x000003ff ; ishift = 10 ; iq_coef = 4; limit = qmask+1;
      break;
    }
    case Si2183_DD_MODE_PROP_MODULATION_MCNS :
    case Si2183_DD_MODE_PROP_MODULATION_DVBC : {
      Si2183_IQ_READ (front_end->demod, iq_symb);
      imask = 0xffff0000 ; qmask = 0x0000ffff ; ishift = 16 ; iq_coef = 2; limit = qmask+1;
      break;
    }
    case Si2183_DD_MODE_PROP_MODULATION_DSS  :
    case Si2183_DD_MODE_PROP_MODULATION_DVBS :
    case Si2183_DD_MODE_PROP_MODULATION_DVBS2: {
      Si2183_IQ_READ (front_end->demod, iq_demod_sat);
      imask = 0x0000ff00 ; qmask = 0x000000ff ; ishift =  8 ; iq_coef = 4; limit = qmask+1;
      break;
    }
    default : {
      SiTRACE("IQ not possible with standard %d\n", front_end->demod->standard);
      SiERROR("IQ not possible with the current standard\n");
      return 0;
      break;
   }
  }

  if (return_code != NO_Si2183_ERROR) return 0;

  value = (front_end->demod->rsp->dd_get_reg.data1<< 0)
        + (front_end->demod->rsp->dd_get_reg.data2<< 8)
        + (front_end->demod->rsp->dd_get_reg.data3<<16)
        + (front_end->demod->rsp->dd_get_reg.data4<<24);

  sign_bit = ishift -1;

  ival = (value & imask) >> ishift;
  if (ival >> sign_bit) { ival = ival - limit; }

  qval = (value & qmask);
  if (qval >> sign_bit) { qval = qval - limit; }

  *i = ival*iq_coef;
  *q = qval*iq_coef;

  return 1;
}
/************************************************************************************************************************
  Si2183_L2_Test function
  Use:        Generic test pipe function
              Used to send a generic command to the selected target.
  Returns:    0 if the command is unknow, 1 otherwise
  Porting:    Mostly used for debug during sw development.
************************************************************************************************************************/
signed   int   Si2183_L2_Test                         (Si2183_L2_Context *front_end, const char *target, const char *cmd, const char *sub_cmd, double dval, double *retdval, char **rettxt)
{
  signed   int i,c,p;
  signed   int passthru_enable;
  unsigned char testBufferBytes[100];
#ifdef    DEMOD_DVB_C2
  char *c2Text;
#endif /* DEMOD_DVB_C2*/
  unsigned char *testBuffer;
  signed   int start_time_ms;
#ifdef    DEMOD_ISDB_T
  signed   int i_constellation;
           char s_constellation [100];
  signed   int i_code_rate;
           char s_code_rate [100];
  signed   int IL;
  signed   int nb_seg;
#endif /* DEMOD_ISDB_T */
#ifdef    DEMOD_DVB_T2
  int    i_plp_id;
  int    i_plp_type;
  int    i_plp_payload_type;
  int    i_group_id;
  int    i_plp_cod;
  int    i_plp_mod;
  int    i_plp_rot;
  int    i_plp_fec_type;
  int    i_plp_num_blocks_max;
  int    i_frame_interval;
  int    i_time_il_length;
  int    i_time_il_type;
  int    i_plp_mode;
  int    i_static_flag;
  int    i_static_padding_flag;
  char  s_plp_type [100];
  char  s_plp_payload_type[100];
  char  s_plp_cod [100];
  char  s_plp_mod [100];
  char  s_plp_rot [100];
  char  s_plp_fec_type [100];
  char  s_plp_mode [100];
  int   tx_id_availability;
  int   cell_id;
  int   network_id;
  int   t2_system_id;
  int   fef_repetition;
  int   fef_type;
  int   fef_length;
#endif /* DEMOD_DVB_T2*/
#ifdef   _DVB_T2_SIGNALLING_H_
  SiLabs_T2_Misc_Signalling    misc;
  SiLabs_T2_L1_Post_Signalling post;
  SiLabs_T2_L1_Pre_Signalling  pre;
#endif /* _DVB_T2_SIGNALLING_H_ */
#ifdef    _Si2183_L2_Get_Echoes_Info_
    int echoes_x[6];
    int echoes_y[6];
#endif /* _Si2183_L2_Get_Echoes_Info_ */
#ifdef    _Si2183_L2_Get_EQ_
    int x_eq[48];
    int y_eq[48];
#endif /* _Si2183_L2_Get_EQ_ */
  testBuffer = &testBufferBytes[0];
#ifdef    DEMOD_DVB_C2
  c2Text     = front_end->demod->msg;
#endif /* DEMOD_DVB_C2*/
  front_end = front_end; /* To avoid compiler warning if not used */
  *retdval = 0;
  start_time_ms = system_time();
  SiTRACE("Si2183_L2_Test %s %s %s %f...\n", target, cmd, sub_cmd, dval);
  sprintf(*rettxt, "%s", "");
       if (strcmp_nocase(target,"help"      ) == 0) {
    sprintf(*rettxt, "\n Possible Si2183 test commands:\n\
demod properties                       : displays ALL current property fields\n\
demod getProperty <prop_code>          : displays current property fields\n\
demod download    <always/on_change>   : selects the property download mode\n\
demod address     <address>            : changes or display i2c address\n\
demod fef     <0-1>                    : set FEF mode\n");
    sprintf(*rettxt, "%s\
demod passthru    <enable/disable/''>  : changes or display i2c passthrough state\n\
demod ber         <mant/exp> <dval/''> : changes ber mant or exp and display their values\n\
demod ber         <loop>               : BER reset followed by BER convergence test\n", *rettxt);
    sprintf(*rettxt, "%s\
demod get_reg     <reg_code>           : call DD_GET_REG and display value\n\
demod set_reg     <reg_code> <dval>    : call DD_SET_REG and display value\n\
demod get_rev                          : display part and fw info\n\
demod part_info                        : displays part info\n\
demod code_version                     : displays code version\n", *rettxt);
    sprintf(*rettxt, "%s\
demod iq          <loop>     <dval>    : read (int)dval constellation points\n\
demod mplp        <freq>               : lock on 'freq' and trace PLP info\n\
demod spi_download <enable/disable> <api_send_option> : enable/disable SPI download (if available)\n\
demod spi_regs                         : displays SPI registers\n\
demod health_check                     : displays registers interesting for health checking\n\
demod handshake  infos                 : displays current handshake settings\n\
demod handshake  used   <0/1>          : controls front_end->handshakeUsed\n\
demod handshake  period <period_ms>    : controls front_end->handshakePeriod\n\
demod clock_mode ter <clock_mode>      : controls front_end->demod->tuner_ter_clock_input\n\
demod clock_mode ter <clock_freq>      : controls front_end->demod->tuner_ter_clock_freq\n\
demod clock_mode ter <clock_mode>      : controls front_end->demod->tuner_sat_clock_input\n\
demod clock_mode sat <clock_freq>      : controls front_end->demod->tuner_sat_clock_freq\n", *rettxt);
    sprintf(*rettxt, "%s\
demod t2 plp_info <plp_index>\n\
demod t2 tx_id\n\
demod t2 fef\n\
demod isdb-t layer_info <layer_index>\n\
demod demod gpif_status\n", *rettxt);
#ifdef    _Si2183_L2_Get_Echoes_Info_
    sprintf(*rettxt, "%s\
demod echoes                           : displays the x and y echo values\n", *rettxt);
#endif /* _Si2183_L2_Get_Echoes_Info_ */
#ifdef    Si2183_L2_DUMP_CODE
    sprintf(*rettxt, "%s\
demod dump                              : dumps all register values\n", *rettxt);
#endif /* Si2183_L2_DUMP_CODE */
#ifdef    _DVB_T2_SIGNALLING_H_
    sprintf(*rettxt, "%s\
demod l1_misc                          : fills the T2 signaling 'L1 misc' structure and displays it\n\
demod l1_pre                           : fills the T2 signaling 'L1 Pre'  structure and displays it\n\
demod l1_post                          : fills the T2 signaling 'L1 Post' structure and displays it\n\
demod dektec                           : uses  the T2 signaling structures to prepare a Dektec configuration string and displays it\n", *rettxt);
#endif /* _DVB_T2_SIGNALLING_H_ */
#ifdef    DEMOD_DVB_C2
    sprintf(*rettxt, "%s\
demod c2 sys_info                      : displaya the C2 system information\n\
demod c2 ds_info  <dataslice_index>    : displaya the C2 dataslice information\n\
demod c2 plp_info <plp_index>          : displaya the C2 plp information\n\
demod c2 all                           : displays the c2 dataslice and plp info for all dataslices and all plps\n\
\n", *rettxt);
#endif /*  DEMOD_DVB_C2 */
 return 1;
  }
  else if (strcmp_nocase(target,"demod"     ) == 0) {
    if (strcmp_nocase(cmd,"help"        ) == 0) { return Si2183_L2_Test(front_end, "help", cmd, sub_cmd, dval, retdval, rettxt); }
    if (strcmp_nocase(cmd,"setProperty" ) == 0) {
      if (sscanf(sub_cmd,"%x",&i) == 0) {
        SiERROR("TestPipe demod setProperty <hex_property_code> <hex_value>\n");
        return 0;
      }
      Si2183_L1_SET_PROPERTY(front_end->demod, 0, i, (int)dval);
      sprintf(*rettxt, "Property 0x%04x set to 0x%04x\n", i, (int)dval);
      return 0;
    }
#ifdef    Si2183_SET_PROPERTY_FIELDS
          Si2183_SET_PROPERTY_FIELDS
#endif /* Si2183_SET_PROPERTY_FIELDS */
#ifdef    Si2183_GET_COMMAND_PARAMETER_FIELDS
          Si2183_GET_COMMAND_PARAMETER_FIELDS
#endif /* Si2183_GET_COMMAND_PARAMETER_FIELDS */
  #ifdef    Si2183_GET_PROPERTY_STRING
    if (strcmp_nocase(cmd,"getProperty" ) == 0) {
       *retdval = (double)Si2183_L1_GetPropertyString(front_end->demod, dval, (char *)" ", *rettxt); return 1;
    }
  #endif /* Si2183_GET_PROPERTY_STRING */
    if (strcmp_nocase(cmd,"address"     ) == 0) {
      if ( (dval >= 0xc8) & (dval <= 0xce) ) {front_end->demod->i2c->address = (int)dval; }
       *retdval = (double)front_end->demod->i2c->address; sprintf(*rettxt, "0x%02x", (int)*retdval ); return 1;
    }
#ifdef    DEMOD_DVB_T2
    if (strcmp_nocase(cmd,"fef"         ) == 0) {
     #ifdef    INDIRECT_I2C_CONNECTION
       front_end->f_TER_tuner_enable(front_end->callback);
     #else  /* INDIRECT_I2C_CONNECTION */
       Si2183_L2_Tuner_I2C_Enable(front_end);
     #endif /* INDIRECT_I2C_CONNECTION */
       *retdval = (double)Si2183_L2_TER_FEF(front_end, dval);
     #ifdef    INDIRECT_I2C_CONNECTION
       front_end->f_TER_tuner_disable(front_end->callback);
     #else  /* INDIRECT_I2C_CONNECTION */
       Si2183_L2_Tuner_I2C_Disable(front_end);
     #endif /* INDIRECT_I2C_CONNECTION */
       sprintf(*rettxt, "FEF %.0f\n", dval);
        return 1;
    }
    if (strcmp_nocase(cmd,"t2"    ) == 0) { /* Kevin */
      if (strcmp_nocase(sub_cmd,"plp_info"   ) == 0) {
        if (Si2183_L1_DVBT2_PLP_INFO(front_end->demod, dval) != NO_Si2183_ERROR) {
          SiTRACE("Si2183_L2_Test plp_info error when checking PLP index %d!\n", dval);
          SiERROR("Si2183_L2_Test plp_info error!\n");
          sprintf(*rettxt, "error when checking PLP index %d\n", (int)dval );

          return 1;
        }

        i_plp_id              = front_end->demod->rsp->dvbt2_plp_info.plp_id;
        i_plp_type            = front_end->demod->rsp->dvbt2_plp_info.plp_type;
        i_plp_payload_type    = front_end->demod->rsp->dvbt2_plp_info.plp_payload_type;
        i_group_id            = front_end->demod->rsp->dvbt2_plp_info.plp_group_id_msb * 16 + front_end->demod->rsp->dvbt2_plp_info.plp_group_id_lsb;
        i_plp_cod             = front_end->demod->rsp->dvbt2_plp_info.plp_cod;
        i_plp_mod             = front_end->demod->rsp->dvbt2_plp_info.plp_mod_lsb;
        i_plp_rot             = front_end->demod->rsp->dvbt2_plp_info.plp_rot;
        i_plp_fec_type        = front_end->demod->rsp->dvbt2_plp_info.plp_fec_type;
        i_plp_num_blocks_max  = front_end->demod->rsp->dvbt2_plp_info.plp_num_blocks_max_msb *128 + front_end->demod->rsp->dvbt2_plp_info.plp_num_blocks_max_lsb;
        i_frame_interval      = front_end->demod->rsp->dvbt2_plp_info.frame_interval_msb * 128 + front_end->demod->rsp->dvbt2_plp_info.frame_interval_lsb;
        i_time_il_length      = front_end->demod->rsp->dvbt2_plp_info.time_il_length_msb * 128 + front_end->demod->rsp->dvbt2_plp_info.time_il_length_lsb;
        i_time_il_type        = front_end->demod->rsp->dvbt2_plp_info.time_il_type;
        i_plp_mode            = front_end->demod->rsp->dvbt2_plp_info.plp_mode;
        i_static_flag         = front_end->demod->rsp->dvbt2_plp_info.static_flag;
        i_static_padding_flag = front_end->demod->rsp->dvbt2_plp_info.static_padding_flag;

        switch (i_plp_type)
        {
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_TYPE_COMMON:
            sprintf(s_plp_type,"Common");
            break;
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_TYPE_DATA_TYPE1:
            sprintf(s_plp_type,"Data_type_1");
            break;
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_TYPE_DATA_TYPE2:
            sprintf(s_plp_type,"Data_type_2");
            break;
          default:
            sprintf(s_plp_type,"unknown");
            break;
        }
        switch (i_plp_payload_type)
        {
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_PAYLOAD_TYPE_GFPS:
            sprintf(s_plp_payload_type,"GFPS");
            break;
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_PAYLOAD_TYPE_GCS:
            sprintf(s_plp_payload_type,"GCS");
            break;
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_PAYLOAD_TYPE_GSE:
            sprintf(s_plp_payload_type,"GSE");
            break;
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_PAYLOAD_TYPE_TS:
            sprintf(s_plp_payload_type,"TS");
            break;
          default:
            sprintf(s_plp_payload_type,"unknown");
            break;
        }
        switch (i_plp_cod)
        {
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_COD_1_2:
            sprintf(s_plp_cod,"1_2");
            break;
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_COD_3_5:
            sprintf(s_plp_cod,"3_5");
            break;
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_COD_2_3:
            sprintf(s_plp_cod,"2_3");
            break;
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_COD_3_4:
            sprintf(s_plp_cod,"3_4");
            break;
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_COD_4_5:
            sprintf(s_plp_cod,"4_5");
            break;
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_COD_5_6:
            sprintf(s_plp_cod,"5_6");
            break;
          default:
            sprintf(s_plp_cod,"unknown");
            break;
        }
        switch (i_plp_mod)
        {
          case 0:
            sprintf(s_plp_mod,"QPSK");
            break;
          case 1:
            sprintf(s_plp_mod,"16QAM");
            break;
          case 2:
            sprintf(s_plp_mod,"64QAM");
            break;
          default :
            sprintf(s_plp_mod,"256QAM");
            break;
        }
        switch (i_plp_rot)
        {
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_ROT_NOT_ROTATED:
            sprintf(s_plp_rot,"not_rotated");
            break;
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_ROT_ROTATED:
            sprintf(s_plp_rot,"rotated");
            break;
          default:
            sprintf(s_plp_rot,"unknown");
            break;
        }
        switch (i_plp_fec_type)
        {
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_FEC_TYPE_16K_LDPC:
            sprintf(s_plp_fec_type,"16K_LDPC");
            break;
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_FEC_TYPE_64K_LDPC:
            sprintf(s_plp_fec_type,"64K_LDPC");
            break;
          default:
            sprintf(s_plp_fec_type,"unknown");
            break;
        }
        switch (i_plp_mode)
        {
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MODE_HIGH_EFFICIENCY_MODE:
            sprintf(s_plp_mode,"high_efficiency_mode");
            break;
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MODE_NORMAL_MODE:
            sprintf(s_plp_mode,"normal_mode");
            break;
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MODE_NOT_SPECIFIED:
            sprintf(s_plp_mode,"not_specified");
            break;
          case Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MODE_RESERVED:
            sprintf(s_plp_mode,"mode_reserved");
            break;
          default:
            sprintf(s_plp_mode,"unknown");
            break;
        }

        sprintf(*rettxt, "plpIndex %d plpId %d plpType %s plpPayloadType %s groupId %d plpCod %s plpMod %s plpRot %s plpFecType %s plpNumBlocksMax %d frameInterval %d timeIlLength %d timeIlType %d plpMode %s staticFlag %d staticPaddingFlag %d\n", (int)dval, i_plp_id, s_plp_type, s_plp_payload_type, i_group_id, s_plp_cod, s_plp_mod, s_plp_rot, s_plp_fec_type, i_plp_num_blocks_max, i_frame_interval, i_time_il_length, i_time_il_type, s_plp_mode, i_static_flag, i_static_padding_flag);
        return 1;

      }
      if (strcmp_nocase(sub_cmd,"tx_id"      ) == 0) {
        if (Si2183_L1_DVBT2_TX_ID(front_end->demod) != NO_Si2183_ERROR) {
          SiTRACE("Si2183_L2_Test tx_id error when checking TX id !\n");
          SiERROR("Si2183_L2_Test tx_id error!\n");
          sprintf(*rettxt, "error when checking TX id\n" );

          return 1;
        }
        tx_id_availability = front_end->demod->rsp->dvbt2_tx_id.tx_id_availability;
        cell_id            = front_end->demod->rsp->dvbt2_tx_id.cell_id;
        network_id         = front_end->demod->rsp->dvbt2_tx_id.network_id;
        t2_system_id       = front_end->demod->rsp->dvbt2_tx_id.t2_system_id;
        sprintf(*rettxt, "txIdAvailability %d cellId %d networkId %d t2SystemId %d\n", tx_id_availability, cell_id, network_id, t2_system_id );
        return 1;
      }
      if (strcmp_nocase(sub_cmd,"fef"      ) == 0) {
        if (Si2183_L1_DVBT2_FEF(front_end->demod, 0, 0) != NO_Si2183_ERROR) {
          SiTRACE("Si2183_L2_Test fef error when checking TX id !\n");
          SiERROR("Si2183_L2_Test fef error!\n");
          sprintf(*rettxt, "error when checking TX id\n" );

          return 1;
        }
        fef_repetition  = front_end->demod->rsp->dvbt2_fef.fef_repetition;
        fef_type        = front_end->demod->rsp->dvbt2_fef.fef_type;
        fef_length      = front_end->demod->rsp->dvbt2_fef.fef_length;
        sprintf(*rettxt, "fefRepetition %d fefType %d fefLength %d\n", fef_repetition, fef_type, fef_length );
        return 1;
      }
    }
#endif /* DEMOD_DVB_T2 */
#ifdef    _Si2183_L2_Get_Echoes_Info_
    if (strcmp_nocase(cmd,"echoes"    ) == 0) {
      *retdval = (double)Si2183_L2_Get_Echoes_Info(front_end, echoes_x, echoes_y);
      c = (int)*retdval;
      *retdval = 6;
      if ((int)*retdval != 0) {
        sprintf(*rettxt, "length %d      max     first     last     max2     max3     max4", c);
        strcat(*rettxt, "\n x_echoes ");
        for (i=0; i<(int)*retdval; i++) { sprintf (*rettxt, "%s%8d ", *rettxt, echoes_x[i]); }
        strcat(*rettxt, "\n y_echoes ");
        for (i=0; i<(int)*retdval; i++) { sprintf (*rettxt, "%s%8d ", *rettxt, echoes_y[i]); }
      }
      return 1;
    }
#endif /* _Si2183_L2_Get_Echoes_Info_ */
    if (strcmp_nocase(cmd,"passthru"    ) == 0) {
      if (strcmp_nocase(sub_cmd,"enable" ) == 0) { Si2183_L2_Tuner_I2C_Enable (front_end); }
      if (strcmp_nocase(sub_cmd,"disable") == 0) { Si2183_L2_Tuner_I2C_Disable(front_end); }
      testBuffer[0] = 0xff;
      testBuffer[1] = 0x00;
      L0_WriteCommandBytes(front_end->demod->i2c, 2, testBuffer);
      testBuffer[0] = 0xc0;
      testBuffer[1] = 0x0d;
      L0_WriteCommandBytes(front_end->demod->i2c, 2, testBuffer);
      L0_ReadBytes        (front_end->demod->i2c, 0xc00d, 1, testBuffer);
      passthru_enable = testBuffer[0]&0x01;
      testBuffer[0] = 0xfe;
      testBuffer[1] = 0x00;
      L0_WriteCommandBytes(front_end->demod->i2c, 2, testBuffer);
      *retdval = (double)passthru_enable;
      sprintf(*rettxt, "passthru enable %d\n", passthru_enable);
      return 1;
    }
    if (strcmp_nocase(cmd,"download"    ) == 0) {
      if (strcmp_nocase(sub_cmd,"duration" ) == 0) {
        sprintf(*rettxt, "I2C download time %d ms, SPI download time %d ms", front_end->demod->i2c_download_ms , front_end->demod->spi_download_ms );
        *retdval = (double)(front_end->demod->i2c_download_ms + front_end->demod->spi_download_ms);
        return 1;
      }
      if (strcmp_nocase(sub_cmd,"always"   ) == 0) { front_end->demod->propertyWriteMode = Si2183_DOWNLOAD_ALWAYS;    }
      if (strcmp_nocase(sub_cmd,"on_change") == 0) { front_end->demod->propertyWriteMode = Si2183_DOWNLOAD_ON_CHANGE; }
      *retdval = (double)front_end->demod->propertyWriteMode;
      if (front_end->demod->propertyWriteMode == Si2183_DOWNLOAD_ALWAYS   ) {sprintf(*rettxt, "download always"   );}
      if (front_end->demod->propertyWriteMode == Si2183_DOWNLOAD_ON_CHANGE) {sprintf(*rettxt, "download on_change");}
      return 1;
    }
    if (strcmp_nocase(cmd,"ber"         ) == 0) {
     if (strcmp_nocase(sub_cmd,"mant" ) == 0) {
      i = (int)dval;
      if (i !=0) {
       front_end->demod->prop->dd_ber_resol.mant                      =     (int) dval;
       Si2183_L1_SetProperty2(front_end->demod, Si2183_DD_BER_RESOL_PROP_CODE);
      }
      *retdval = (double)front_end->demod->prop->dd_ber_resol.mant;
      sprintf(*rettxt, "BER mant %.0f\n", *retdval);
     }
     if (strcmp_nocase(sub_cmd,"exp"  ) == 0) {
      i = (int)dval;
      if (i !=0) {
       front_end->demod->prop->dd_ber_resol.exp                       =     (int) dval;
       Si2183_L1_SetProperty2(front_end->demod, Si2183_DD_BER_RESOL_PROP_CODE);
      }
      *retdval = (double)front_end->demod->prop->dd_ber_resol.exp;
      sprintf(*rettxt, "BER exp  %.0f\n", *retdval);
     }
#ifdef    DEMOD_DVB_T
     if (strcmp_nocase(sub_cmd,"loop" ) == 0) {
       SiTraceConfiguration("traces suspend");
       Si2183_L1_DD_BER(front_end->demod, Si2183_DD_BER_CMD_RST_CLEAR);
       SiTraceConfiguration("traces resume");
       SiTRACE("BER CLEAR\n");
       SiTraceConfiguration("traces suspend");
       for (i=0; i< (int)dval; i++) {
        Si2183_L1_DD_BER(front_end->demod, Si2183_DD_BER_CMD_RST_RUN);
        Si2183_L1_DVBT_STATUS(front_end->demod, Si2183_DVBT_STATUS_CMD_INTACK_OK);
        SiTraceConfiguration("traces resume");
        SiTRACE("%4d: (%6d ms) BER %8.2e C/N_100 %d", i+1, system_time() - start_time_ms, *retdval, front_end->demod->rsp->dvbt_status.cnr*25 );
        if (front_end->demod->rsp->dd_ber.exp!=0) {
         p = 1;
         for (c = 1; c<=front_end->demod->rsp->dd_ber.exp; c++) {p = p*10;}
         *retdval = (front_end->demod->rsp->dd_ber.mant/10.0) / p;
         SiTRACE("%4d: (%6d ms) BER %8.2e", i+1, system_time() - start_time_ms, *retdval);
        } else {
         *retdval = 1.0;
         SiTRACE("%4d: (%6d ms) BER unavailable", i+1, system_time() - start_time_ms);
        }
        SiTRACE("\n");
        SiTraceConfiguration("traces suspend");
        system_wait(20);
       }
       sprintf(*rettxt, "final BER %8.2e\n", *retdval);
     }
     if (strcmp_nocase(sub_cmd,"after_reset" ) == 0) {
       SiTraceConfiguration("traces suspend");
       Si2183_L1_DD_RESTART(front_end->demod);
       SiTraceConfiguration("traces resume");
       SiTRACE("DD_RESTART\n");
       SiTraceConfiguration("traces suspend");
       Si2183_L1_DD_BER(front_end->demod, Si2183_DD_BER_CMD_RST_CLEAR);
       SiTraceConfiguration("traces resume");
       SiTRACE("BER CLEAR\n");
       SiTraceConfiguration("traces suspend");
       for (i=0; i< (int)dval; i++) {
        Si2183_L1_DD_BER(front_end->demod, Si2183_DD_BER_CMD_RST_RUN);
        Si2183_L1_DVBT_STATUS(front_end->demod, Si2183_DVBT_STATUS_CMD_INTACK_OK);
        SiTraceConfiguration("traces resume");
        if (front_end->demod->rsp->dd_ber.exp!=0) {
         p = 1;
         for (c = 1; c<=front_end->demod->rsp->dd_ber.exp; c++) {p = p*10;}
         *retdval = (front_end->demod->rsp->dd_ber.mant/10.0) / p;
          SiTRACE("%4d: (%6d ms) BER %8.2e C/N_100 %d", i+1, system_time() - start_time_ms, *retdval, front_end->demod->rsp->dvbt_status.cnr*25 );
         break;
        } else {
         *retdval = 1.0;
          SiTRACE("%4d: (%6d ms) BER unavailable C/N_100 %d", i+1, system_time() - start_time_ms, front_end->demod->rsp->dvbt_status.cnr*25 );
        }
        SiTRACE("\n");
        system_wait(0);
        SiTraceConfiguration("traces suspend");
       }
       sprintf(*rettxt, "final BER %8.2e\n", *retdval);
     }
#endif /* DEMOD_DVB_T */
     if (strcmp_nocase(sub_cmd,"first_available" ) == 0) {
       SiTraceConfiguration("traces suspend");
       Si2183_L1_DD_BER(front_end->demod, Si2183_DD_BER_CMD_RST_CLEAR);
       SiTraceConfiguration("traces resume");
       SiTRACE("BER CLEAR\n");
       for (i=0; i< (int)dval; i++) {
       SiTraceConfiguration("traces suspend");
        Si2183_L1_DD_BER(front_end->demod, Si2183_DD_BER_CMD_RST_RUN);
        SiTraceConfiguration("traces resume");
        if (front_end->demod->rsp->dd_ber.exp!=0) {
         p = 1;
         for (c = 1; c<=front_end->demod->rsp->dd_ber.exp; c++) {p = p*10;}
         *retdval = (front_end->demod->rsp->dd_ber.mant/10.0) / p;
         SiTRACE("%4d: (%6d ms) BER %8.2e", i+1, system_time() - start_time_ms, *retdval);
         break;
        } else {
         *retdval = 1.0;
         SiTRACE("%4d: (%6d ms) BER unavailable", i+1, system_time() - start_time_ms);
        }
        SiTRACE("\n");
        system_wait(20);
        SiTraceConfiguration("traces suspend");
       }
       sprintf(*rettxt, "final BER %8.2e\n", *retdval);
     }
     return 1;
    }
    if (strcmp_nocase(cmd,"get_reg"     ) == 0) {
       sscanf(sub_cmd, "%d",&c);
       Si2183_L1_DD_GET_REG(front_end->demod, (c>>16)&0xff, (c>>8)&0xff, (c>>0)&0xff );
       sprintf(*rettxt, "%d\n",
                (front_end->demod->rsp->dd_get_reg.data4<<24)
               +(front_end->demod->rsp->dd_get_reg.data3<<16)
               +(front_end->demod->rsp->dd_get_reg.data2<<8 )
               +(front_end->demod->rsp->dd_get_reg.data1<<0 )
        );
        return 1;
    }
    if (strcmp_nocase(cmd,"set_reg"     ) == 0) {
       i = (int)dval;
       sscanf(sub_cmd, "%d",&c);
       Si2183_L1_DD_SET_REG(front_end->demod, (c>>16)&0xff, (c>>8)&0xff, (c>>0)&0xff, i );
       Si2183_L1_DD_GET_REG(front_end->demod, (c>>16)&0xff, (c>>8)&0xff, (c>>0)&0xff );
       sprintf(*rettxt, "%d\n",
                (front_end->demod->rsp->dd_get_reg.data4<<24)
               +(front_end->demod->rsp->dd_get_reg.data3<<16)
               +(front_end->demod->rsp->dd_get_reg.data2<<8 )
               +(front_end->demod->rsp->dd_get_reg.data1<<0 )
        );
        return 1;
    }
    if (strcmp_nocase(cmd,"get_rev"     ) == 0) {
       Si2183_L1_GET_REV(front_end->demod);
       sprintf(*rettxt,"Si21%02d", front_end->demod->rsp->get_rev.pn);
              if ((front_end->demod->rsp->get_rev.mcm_die) != Si2183_GET_REV_RESPONSE_MCM_DIE_SINGLE) {
       sprintf(*rettxt,"%s2", *rettxt);
       }
              if (front_end->demod->rsp->get_rev.chiprev == Si2183_PART_INFO_RESPONSE_CHIPREV_A) {
       sprintf(*rettxt,"%s A", *rettxt);
       } else if (front_end->demod->rsp->get_rev.chiprev == Si2183_PART_INFO_RESPONSE_CHIPREV_B) {
       sprintf(*rettxt,"%s B", *rettxt);
       } else if (front_end->demod->rsp->get_rev.chiprev == Si2183_PART_INFO_RESPONSE_CHIPREV_C) {
       sprintf(*rettxt,"%s C", *rettxt);
       } else if (front_end->demod->rsp->get_rev.chiprev == Si2183_PART_INFO_RESPONSE_CHIPREV_D) {
       sprintf(*rettxt,"%s D", *rettxt);
       } else {
       sprintf(*rettxt,"%s chiprev %d",*rettxt, front_end->demod->rsp->get_rev.chiprev);
       }
       sprintf(*rettxt,"%s ROM %d NVM %c_%cb%d ", *rettxt
              , front_end->demod->rsp->part_info.romid
              , front_end->demod->rsp->part_info.pmajor
              , front_end->demod->rsp->part_info.pminor
              , front_end->demod->rsp->part_info.pbuild
               );
              if (front_end->demod->rsp->get_rev.mcm_die == Si2183_GET_REV_RESPONSE_MCM_DIE_DIE_A) {
       sprintf(*rettxt,"%s die A", *rettxt);
       } else if (front_end->demod->rsp->get_rev.mcm_die == Si2183_GET_REV_RESPONSE_MCM_DIE_DIE_B) {
       sprintf(*rettxt,"%s die B", *rettxt);
       }
       sprintf(*rettxt,"%s Running FW %c_%cb%d\n", *rettxt
              , front_end->demod->rsp->get_rev.cmpmajor
              , front_end->demod->rsp->get_rev.cmpminor
              , front_end->demod->rsp->get_rev.cmpbuild
               );
       return 1;
    }
    if (strcmp_nocase(cmd,"part_info"   ) == 0) {
      if (strcmp_nocase(sub_cmd,"execute" ) == 0) {
        Si2183_L1_PART_INFO(front_end->demod);
      }
      if (strcmp_nocase(sub_cmd,"part"    ) == 0) {
        sprintf(*rettxt, "%02d", front_end->demod->rsp->part_info.part );
        return 1;
      }
      if (strcmp_nocase(sub_cmd,"chiprev" ) == 0) {
        sprintf(*rettxt, "%c", front_end->demod->rsp->part_info.chiprev + 0x40 );
        return 1;
      }
      if ((front_end->demod->rsp->get_rev.mcm_die) != Si2183_GET_REV_RESPONSE_MCM_DIE_SINGLE) {
        sprintf(*rettxt, "Full Info 'Si21%02d%d-%c%c%c ROM%x NVM%c_%cb%d'\n", front_end->demod->rsp->part_info.part, 2, front_end->demod->rsp->part_info.chiprev + 0x40, front_end->demod->rsp->part_info.pmajor, front_end->demod->rsp->part_info.pminor, front_end->demod->rsp->part_info.romid, front_end->demod->rsp->part_info.pmajor, front_end->demod->rsp->part_info.pminor, front_end->demod->rsp->part_info.pbuild );
      } else {
        sprintf(*rettxt, "Full Info 'Si21%02d-%c%c%c ROM%x NVM%c_%cb%d'\n", front_end->demod->rsp->part_info.part, front_end->demod->rsp->part_info.chiprev + 0x40, front_end->demod->rsp->part_info.pmajor, front_end->demod->rsp->part_info.pminor, front_end->demod->rsp->part_info.romid, front_end->demod->rsp->part_info.pmajor, front_end->demod->rsp->part_info.pminor, front_end->demod->rsp->part_info.pbuild );
      }
      return 1;
    }
    if (strcmp_nocase(cmd,"chip_detect" ) == 0) {
      /* Attempt to read from 0xC0 to make sure it's an API-controlled part */
      i = front_end->demod->i2c->address;
 #ifdef    INDIRECT_I2C_CONNECTION
      front_end->f_TER_tuner_enable(front_end->callback);
 #else  /* INDIRECT_I2C_CONNECTION */
      Si2183_L2_Tuner_I2C_Enable(front_end);
 #endif /* INDIRECT_I2C_CONNECTION */

      L0_SetAddress(front_end->demod->i2c, 0xC0, 0);
      c = L0_ReadCommandBytes (front_end->demod->i2c, 1, testBuffer);
      SiTRACE("Bytes read from tuner at 0x%02x using '83A' connection: %d\n", front_end->demod->i2c->address, c);

      if ( c == 0) {
        /* It's not possible to access the tuner, which means that the i2c passthru is not closed */
        /* Try closing the i2c passthru '65D style' and retest */
        L0_SetAddress(front_end->demod->i2c, i, 0);
        testBuffer[0] = 0x00; testBuffer[1] = 0x01; testBuffer[2] = 0x01;
        L0_WriteCommandBytes (front_end->demod->i2c, 3,  testBuffer);

        L0_SetAddress(front_end->demod->i2c, 0xC0, 0);
        c = L0_ReadCommandBytes (front_end->demod->i2c, 1, testBuffer);
        SiTRACE("Bytes read from tuner at 0x%02x using '65D' connection: %d\n", front_end->demod->i2c->address, c);
        L0_SetAddress(front_end->demod->i2c, i, 0);

        if ( c == 1) {
          testBuffer[0] = 0x00; testBuffer[1] = 0x01; testBuffer[2] = 0x00;
          L0_WriteCommandBytes (front_end->demod->i2c, 3,  testBuffer);
          sprintf(*rettxt, "65D" );
          return 1;
        }
      } else {
        SiTRACE("The demod at address 0x%02x is API-controlled\n", i);
      }
      L0_SetAddress(front_end->demod->i2c, i, 0);
 #ifdef    INDIRECT_I2C_CONNECTION
      front_end->f_TER_tuner_disable(front_end->callback);
 #else  /* INDIRECT_I2C_CONNECTION */
      Si2183_L2_Tuner_I2C_Disable(front_end);
 #endif /* INDIRECT_I2C_CONNECTION */
      Si2183_L1_PART_INFO(front_end->demod);
      SiTRACE("part_info.part %d,  part_info.chiprev %d\n",front_end->demod->rsp->part_info.part, front_end->demod->rsp->part_info.chiprev);
      switch (front_end->demod->rsp->part_info.part)
      {
        case 64:
          if        (front_end->demod->rsp->part_info.chiprev == 1) {
            sprintf(*rettxt, "64A" );
          } else if (front_end->demod->rsp->part_info.chiprev >= 2) {
            sprintf(*rettxt, "83A" );
          } else {
            sprintf(*rettxt, "Error: chiprev %02d (%c) unknown for Si21%02d", front_end->demod->rsp->part_info.chiprev, front_end->demod->rsp->part_info.chiprev + 0x40, front_end->demod->rsp->part_info.part );
          }
          break;
        case 65:
        case 67:
          if        (front_end->demod->rsp->part_info.chiprev == 2) {
            sprintf(*rettxt, "67B" );
          } else if (front_end->demod->rsp->part_info.chiprev >= 3) {
            sprintf(*rettxt, "83A" );
          } else {
            sprintf(*rettxt, "Si2183_L2_Test 'TestPipe demod chip_detect' Error: chiprev %02d (%c) unknown for Si21%02d", front_end->demod->rsp->part_info.chiprev, front_end->demod->rsp->part_info.chiprev +0x40, front_end->demod->rsp->part_info.part );
          }
          break;
        case 66:
          if        (front_end->demod->rsp->part_info.chiprev == 1) {
            sprintf(*rettxt, "66A" );
          } else if (front_end->demod->rsp->part_info.chiprev == 2) {
            sprintf(*rettxt, "67B" );
          } else if (front_end->demod->rsp->part_info.chiprev >= 3) {
            sprintf(*rettxt, "83A" );
          } else {
            sprintf(*rettxt, "Si2183_L2_Test 'TestPipe demod chip_detect' Error: chiprev %02d (%c) unknown for Si21%02d", front_end->demod->rsp->part_info.chiprev, front_end->demod->rsp->part_info.chiprev +0x40, front_end->demod->rsp->part_info.part );
          }
          break;
        case 68:
        case 69:
          if        (front_end->demod->rsp->part_info.chiprev == 1) {
            sprintf(*rettxt, "69A" );
          } else if (front_end->demod->rsp->part_info.chiprev == 2) {
            sprintf(*rettxt, "64A" );
          } else if (front_end->demod->rsp->part_info.chiprev >= 3) {
            sprintf(*rettxt, "83A" );
          } else {
            sprintf(*rettxt, "Si2183_L2_Test 'TestPipe demod chip_detect' Error: chiprev %02d (%c) unknown for Si21%02d", front_end->demod->rsp->part_info.chiprev, front_end->demod->rsp->part_info.chiprev +0x40, front_end->demod->rsp->part_info.part );
          }
          break;
        case 80:
        case 81:
        case 82:
        case 83:
          if (front_end->demod->rsp->part_info.chiprev >= 1) {
            sprintf(*rettxt, "83A" );
          } else {
            sprintf(*rettxt, "Si2183_L2_Test 'TestPipe demod chip_detect' Error: chiprev %02d (%c) unknown for Si21%02d", front_end->demod->rsp->part_info.chiprev, front_end->demod->rsp->part_info.chiprev +0x40, front_end->demod->rsp->part_info.part );
          }
          break;
        default:
          sprintf(*rettxt, "83A" );
          break;
      }
      return 1;
    }
    if (strcmp_nocase(cmd,"iq"          ) == 0) {
      sprintf(*rettxt, "  I    Q \n");
      if (strcmp_nocase(sub_cmd,"loop"  ) == 0) {
        for (i=0; i< (int)dval; i++) {
          Si2183_L2_Get_Constellation_IQ(front_end, &c, &p);
          sprintf(*rettxt, "%s %4d %4d\n", *rettxt, c, p );
        }
      } else {
          Si2183_L2_Get_Constellation_IQ(front_end, &c, &p);
          sprintf(*rettxt, "%s %4d %4d\n", *rettxt, c, p );
      }
      return 1;
    }
#ifdef    _Si2183_L2_Get_EQ_
    if (strcmp_nocase(cmd,"eq"          ) == 0) {
      c = Si2183_L2_Get_EQ(front_end, x_eq, y_eq);
      sprintf(*rettxt, "%s", "" );
      for ( i=0; i<c; i++ ) { sprintf(*rettxt, "%s %4d %4d   \n", *rettxt, x_eq[i], y_eq[i] ); }
      return 1;
    }
#endif /* _Si2183_L2_Get_EQ_ */
    if (strcmp_nocase(cmd,"rx_type"     ) == 0) {
      Si2183_L2_Get_Constellation_IQ_rx_type ( front_end, (unsigned char)dval);
      *retdval = (double)Si2183_iq_demap;
      sprintf(*rettxt, "iq_demap %d\n", Si2183_iq_demap);
      return 1;
    }
    if (strcmp_nocase(cmd,"gpif_status" ) == 0) {
      i = Si2183_L1_GET_REG ( front_end->demod, 3,161,23);
      /* Reset ts_alarm if any */
      if (i) { Si2183_L1_DD_SET_REG (front_end->demod, 0,160,23, 1); }
      sprintf(*rettxt, "ts_alarm %d\n", i);
      *retdval = (double)i;
      return 1;
    }
#ifdef    SATELLITE_FRONT_END
    if (strcmp_nocase(cmd,"agc_sat"     ) == 0) {
      i = (int)dval;
      if (strcmp_nocase(sub_cmd,"agc_1_kloop"     ) == 0) {
        if (i>=Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_KLOOP_MIN) { front_end->demod->cmd->dd_ext_agc_sat.agc_1_kloop = i; }
        sprintf(*rettxt, "dd_ext_agc_sat.agc_1_kloop %d\n", front_end->demod->cmd->dd_ext_agc_sat.agc_1_kloop);
      }
      if (strcmp_nocase(sub_cmd,"agc_2_kloop"     ) == 0) {
        if (i>=Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_KLOOP_MIN) { front_end->demod->cmd->dd_ext_agc_sat.agc_2_kloop = i; }
        sprintf(*rettxt, "dd_ext_agc_sat.agc_2_kloop %d\n", front_end->demod->cmd->dd_ext_agc_sat.agc_2_kloop);
      }
      return 1;
    }
    if (strcmp_nocase(cmd,"skip_sat_init") == 0) {
      front_end->first_init_done     = 1;
      front_end->SAT_tuner_init_done = 1;
      sprintf(*rettxt, "front_end->SAT_tuner_init_done %d\n", front_end->SAT_tuner_init_done);
      return 1;
    }
#ifdef   CHANNEL_BONDING
    if (strcmp_nocase(cmd,"bonding"     ) == 0) {
      i = (int)dval;
      if (strcmp_nocase(sub_cmd,"ts_ber_init"    ) == 0) {
        Si2183_L1_DD_SET_REG(front_end->demod,  0, 172, 23,      1 );
        Si2183_L1_DD_SET_REG(front_end->demod,  0, 188, 23,      1 );
        Si2183_L1_DD_SET_REG(front_end->demod, 23, 180, 23, 100000 );
        Si2183_L1_DD_SET_REG(front_end->demod,  0, 177, 23,      1 );
        sprintf(*rettxt, "ts_ber_enable enable, ts_ber_payload_mode 184, ts_ber_bit 100000, ts_ber_rst reset\n");
      }
      if (strcmp_nocase(sub_cmd,"ts_ber_rst"     ) == 0) {
        Si2183_L1_DD_SET_REG(front_end->demod,  0, 177, 23, 1 );
        sprintf(*rettxt, "ts_ber_rst    reset\n");
      }
      if (strcmp_nocase(sub_cmd,"ts_ber_avail"   ) == 0) {
        *retdval = (double)Si2183_L2_GET_REG (front_end,  0, 178, 23);
        sprintf(*rettxt, "ts_ber_avail  %d\n", (int)*retdval);
      }
      if (strcmp_nocase(sub_cmd,"ts_ber_err"     ) == 0) {
        *retdval = (double)Si2183_L2_GET_REG (front_end, 23, 184, 23);
        sprintf(*rettxt, "ts_ber_err    %d\n", (int)*retdval);
      }
      if (strcmp_nocase(sub_cmd,"lock"           ) == 0) {
        *retdval = (double)Si2183_L2_GET_REG (front_end,  0, 96, 21);
        sprintf(*rettxt, "fec_lock_t2c2 %d\n", (int)*retdval);
      }
      return 1;
    }
#endif /* CHANNEL_BONDING */
#endif /* SATELLITE_FRONT_END */
#ifdef    TERRESTRIAL_FRONT_END
    if (strcmp_nocase(cmd,"agc_ter"     ) == 0) {
      i = (int)dval;
      if (strcmp_nocase(sub_cmd,"agc_1_kloop"     ) == 0) {
        if (i>=Si2183_DD_EXT_AGC_TER_CMD_AGC_1_KLOOP_MIN) { front_end->demod->cmd->dd_ext_agc_ter.agc_1_kloop = i; }
        sprintf(*rettxt, "dd_ext_agc_ter.agc_1_kloop %d\n", front_end->demod->cmd->dd_ext_agc_ter.agc_1_kloop);
      }
      if (strcmp_nocase(sub_cmd,"agc_2_kloop"     ) == 0) {
        if (i>=Si2183_DD_EXT_AGC_TER_CMD_AGC_2_KLOOP_MIN) { front_end->demod->cmd->dd_ext_agc_ter.agc_2_kloop = i; }
        sprintf(*rettxt, "dd_ext_agc_ter.agc_2_kloop %d\n", front_end->demod->cmd->dd_ext_agc_ter.agc_2_kloop);
      }
      return 1;
    }
#endif /* TERRESTRIAL_FRONT_END */
    if (strcmp_nocase(cmd,"code_version") == 0) {
     sprintf(*rettxt, "Code %s\n", Si2183_L1_API_TAG_TEXT() );
     return 1;
    }
    if (strcmp_nocase(cmd,"mplp"        ) == 0) {
     i = (int)dval;
     sprintf(*rettxt, "%d DATA streams\n", Si2183_L2_Test_MPLP(front_end, i) );
     return 1;
    }
    if (strcmp_nocase(cmd,"spi_download") == 0) {
      if (strcmp_nocase(sub_cmd,"enable" ) == 0) { front_end->demod->spi_download = 1; front_end->demod->spi_send_option = (int) dval; }
      if (strcmp_nocase(sub_cmd,"disable") == 0) { front_end->demod->spi_download = 0; }
      *retdval = (double)front_end->demod->spi_download;
      sprintf(*rettxt, "spi_download %d\n", front_end->demod->spi_download );
      return 1;
    }
    if (strcmp_nocase(cmd,"spi_regs"    ) == 0) {
      testBuffer[0]=0xff; testBuffer[1]=0x00; L0_WriteCommandBytes(front_end->demod->i2c, 2, testBuffer);
      front_end->demod->i2c->indexSize  = 2;
      sprintf(*rettxt, "spi_crc_status %ld spi_state %ld ", L0_ReadRegister(front_end->demod->i2c, 0x55, 0, 1, 0) , L0_ReadRegister(front_end->demod->i2c, 0x57, 0, 3, 0));
      front_end->demod->i2c->indexSize  = 0;
      testBuffer[0]=0xfe; testBuffer[1]=0x00; L0_WriteCommandBytes(front_end->demod->i2c, 2, testBuffer);
      return 1;
    }
    if (strcmp_nocase(cmd,"health_check") == 0) {
      Si2183_L2_Health_Check(front_end);
      return 1;
    }
    #ifdef    Si2183_L2_DUMP_CODE
    if (strcmp_nocase(cmd,"dump"        ) == 0) {
      Si2183_L2_DUMP(front_end);
      return 1;
    }
    #endif /* Si2183_L2_DUMP_CODE */
    #ifdef    Si2183_L2_FFT_CODE
    if (strcmp_nocase(cmd,"fft"         ) == 0) {
      if (strcmp_nocase(sub_cmd,"fill"  ) == 0) {
        SiTraceConfiguration("traces suspend");
        Si2183_L2_FFT(front_end, (int)dval, 0);
        sprintf(*rettxt, "fft array filled first_freq %d last_freq %d (1400 points)", fft_freq[0], fft_freq[1399]);
        SiTraceConfiguration("traces resume");
        return 1;
      }
      if (strcmp_nocase(sub_cmd,"samples" ) == 0) {
        p = (int)dval;
        if (p+100>1400) {p=0;}
        sprintf(*rettxt, "fft_mag[%d] to fft_mag[%d]", p, p+99);
        for (i=p; i<p+100; i++) { sprintf(*rettxt, "%s %d", *rettxt, fft_mag[i]); }
        *retdval = p*1.0;
        return 1;
      }
      SiTraceConfiguration("traces -output stdout");
      Si2183_L2_FFT(front_end, (int)dval, 0);
      return 1;
    }
    #endif /* Si2183_L2_FFT_CODE */
#ifdef    DEMOD_DVB_C2
    if (strcmp_nocase(cmd,"c2"          ) == 0) {
      if (strcmp_nocase(sub_cmd,"sys_info" ) == 0) {
        Si2183_L1_DVBC2_SYS_INFO (front_end->demod);
        sprintf(*rettxt,"DVB-C2 system     : ");
        strcat (*rettxt,"c2_network_id "        ); sprintf(*rettxt,"%s%d  " , *rettxt, front_end->demod->rsp->dvbc2_sys_info.network_id);
        strcat (*rettxt,"c2_system_id "      ); sprintf(*rettxt,"%s%d  " , *rettxt, front_end->demod->rsp->dvbc2_sys_info.c2_system_id);
        strcat (*rettxt,"c2_version "        );
        if  (front_end->demod->rsp->dvbc2_sys_info.c2_version         ==     0) strcat(*rettxt,"1.2.1 ");
        else if  (front_end->demod->rsp->dvbc2_sys_info.c2_version         ==     1) strcat(*rettxt,"1.3.1 ");
        else    sprintf(*rettxt,"%s%d  " , *rettxt, front_end->demod->rsp->dvbc2_sys_info.c2_version);
        strcat (*rettxt,"c2_ews "               );
        if  (front_end->demod->rsp->dvbc2_sys_info.c2_version         ==     0) strcat(*rettxt,"No_EWS_Field ");
        else if  (front_end->demod->rsp->dvbc2_sys_info.ews         ==     0) strcat(*rettxt,"NotActivated ");
        else if  (front_end->demod->rsp->dvbc2_sys_info.ews         ==     1) strcat(*rettxt,"Activated ");
        else     sprintf(*rettxt,"%s%d  ", *rettxt, front_end->demod->rsp->dvbc2_sys_info.ews);
        strcat (*rettxt,"c2_start_frequency_hz "); sprintf(*rettxt,"%s%ld  ", *rettxt, front_end->demod->rsp->dvbc2_sys_info.start_frequency_hz);
        strcat (*rettxt,"c2_bandwidth_hz "   ); sprintf(*rettxt,"%s%ld  ", *rettxt, front_end->demod->rsp->dvbc2_sys_info.c2_bandwidth_hz);
        strcat (*rettxt,"c2_num_dslice "        ); sprintf(*rettxt,"%s%d  " , *rettxt, front_end->demod->rsp->dvbc2_sys_info.num_dslice);
        strcat (*rettxt,"\n");
      }
      if (strcmp_nocase(sub_cmd,"ds_info"  ) == 0) {
        front_end->demod->cmd->dvbc2_ds_info.ds_index_or_id        = (int)dval;
        front_end->demod->cmd->dvbc2_ds_info.ds_select_index_or_id = Si2183_DVBC2_DS_INFO_CMD_DS_SELECT_INDEX_OR_ID_INDEX;
        Si2183_L1_DVBC2_DS_INFO  (front_end->demod ,front_end->demod->cmd->dvbc2_ds_info.ds_index_or_id , front_end->demod->cmd->dvbc2_ds_info.ds_select_index_or_id);
        sprintf(*rettxt,"DVB-C2  dataslice (ds  index %d): ", front_end->demod->cmd->dvbc2_ds_info.ds_index_or_id);
        strcat (*rettxt,"c2_dsId  "           ); sprintf(*rettxt,"%s%d  " , *rettxt, front_end->demod->rsp->dvbc2_ds_info.ds_id);
        strcat (*rettxt,"c2_dsliceTunePosHz "); sprintf(*rettxt,"%s%ld  ", *rettxt, front_end->demod->rsp->dvbc2_ds_info.dslice_tune_pos_hz);
        strcat (*rettxt,"c2_dsliceNumPlp "   ); sprintf(*rettxt,"%s%d  " , *rettxt, front_end->demod->rsp->dvbc2_ds_info.dslice_num_plp);
        strcat (*rettxt,"\n");
      }
      if (strcmp_nocase(sub_cmd,"plp_info" ) == 0) {
        front_end->demod->cmd->dvbc2_plp_info.plp_info_ds_mode = Si2183_DVBC2_PLP_INFO_CMD_PLP_INFO_DS_MODE_ANY;
        front_end->demod->cmd->dvbc2_plp_info.plp_index        = (int)dval;
        Si2183_L1_DVBC2_PLP_INFO  (front_end->demod, front_end->demod->cmd->dvbc2_plp_info.plp_index, front_end->demod->cmd->dvbc2_plp_info.plp_info_ds_mode, front_end->demod->cmd->dvbc2_ds_info.ds_index_or_id);
        sprintf(*rettxt,"DVB-C2   plp      (plp index %d): ", front_end->demod->cmd->dvbc2_plp_info.plp_index);
        strcat(*rettxt,"c2_plpId "          ); sprintf(*rettxt,"%s%d  ", *rettxt, front_end->demod->rsp->dvbc2_plp_info.plp_id);
        strcat(*rettxt,"c2_plpType "       );
             if  (front_end->demod->rsp->dvbc2_plp_info.plp_type         ==     0) strcat(*rettxt,"COMMON  "    );
        else if  (front_end->demod->rsp->dvbc2_plp_info.plp_type         ==     1) strcat(*rettxt,"Data_Type1  ");
        else if  (front_end->demod->rsp->dvbc2_plp_info.plp_type         ==     2) strcat(*rettxt,"Data_Type2  ");
        else     sprintf(*rettxt,"%s%d  ", *rettxt, front_end->demod->rsp->dvbc2_plp_info.plp_type);
        strcat(*rettxt,"c2_plpPayloadType ");
             if  (front_end->demod->rsp->dvbc2_plp_info.plp_payload_type ==     1) strcat(*rettxt,"GCS  " );
        else if  (front_end->demod->rsp->dvbc2_plp_info.plp_payload_type ==     0) strcat(*rettxt,"GFPS  ");
        else if  (front_end->demod->rsp->dvbc2_plp_info.plp_payload_type ==     2) strcat(*rettxt,"GSE  " );
        else if  (front_end->demod->rsp->dvbc2_plp_info.plp_payload_type ==     3) strcat(*rettxt,"TS   " );
        else     sprintf(*rettxt,"%s%d  ", *rettxt, front_end->demod->rsp->dvbc2_plp_info.plp_payload_type);
        strcat (*rettxt,"\n");
      }
      if (strcmp_nocase(sub_cmd,"all"      ) == 0) {
        Si2183_L2_Test (front_end, "demod", "c2", "sys_info", 0, retdval, rettxt);
        for (i = 0; i < front_end->demod->rsp->dvbc2_sys_info.num_dslice; i++) {
          Si2183_L2_Test (front_end, "demod", "c2", "ds_info", i, retdval, &c2Text);
          strcat(*rettxt, c2Text );
          for (p = 0; p < front_end->demod->rsp->dvbc2_ds_info.dslice_num_plp; p++) {
            Si2183_L2_Test (front_end, "demod", "c2", "plp_info", p, retdval, &c2Text);
            strcat(*rettxt, c2Text );
          }
        }
      }
      return 1;
    }
#endif /* DEMOD_DVB_C2*/
    if (strcmp_nocase(cmd,"handshake"   ) == 0) {
      i = (int)dval;
      if (strcmp_nocase(sub_cmd,"infos" ) != 0) {
        if (strcmp_nocase(sub_cmd,"used"   ) == 0) {
          if (i!=0) {
            front_end->handshakeUsed = 1;
          } else {
            front_end->handshakeUsed = 0;
          }
        }
        if (strcmp_nocase(sub_cmd,"period" ) == 0) {
          if (i!=0) {
            front_end->handshakePeriod_ms = i;
          }
        }
      }
      sprintf(*rettxt, "handshakeUsed %d, handshakePeriod %d \n", front_end->handshakeUsed, front_end->handshakePeriod_ms );
      return 1;
    }
    if (strcmp_nocase(cmd,"clock_mode"  ) == 0) {
      i = (int)dval;
#ifdef    DEMOD_DVB_T
      if (strcmp_nocase(sub_cmd,"ter"   ) == 0) {
        if (i != 0) { front_end->demod->tuner_ter_clock_input = i;}
        sprintf(*rettxt, "front_end->demod->tuner_ter_clock_input %d\n", front_end->demod->tuner_ter_clock_input );
      }
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_DVB_S_S2_DSS
      if (strcmp_nocase(sub_cmd,"sat"   ) == 0) {
        if (i != 0) { front_end->demod->tuner_sat_clock_input = i;}
        sprintf(*rettxt, "front_end->demod->tuner_sat_clock_input %d\n", front_end->demod->tuner_sat_clock_input );
      }
#endif /* DEMOD_DVB_S_S2_DSS */
      return 1;
    }
    if (strcmp_nocase(cmd,"clock_freq"  ) == 0) {
      i = (int)dval;
#ifdef    DEMOD_DVB_T
      if (strcmp_nocase(sub_cmd,"ter"   ) == 0) {
        if (i != 0) { front_end->demod->tuner_ter_clock_freq = i; }
        sprintf(*rettxt, "front_end->demod->tuner_ter_clock_freq %d\n", front_end->demod->tuner_ter_clock_freq );
      }
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_DVB_S_S2_DSS
      if (strcmp_nocase(sub_cmd,"sat"   ) == 0) {
        if (i != 0) { front_end->demod->tuner_sat_clock_freq = i; }
        sprintf(*rettxt, "front_end->demod->tuner_sat_clock_freq %d\n", front_end->demod->tuner_sat_clock_freq );
      }
#endif /* DEMOD_DVB_S_S2_DSS */
      return 1;
    }
    if (strcmp_nocase(cmd,"check_loop"  ) == 0) {
      Si2183_L2_CheckLoop (front_end);
      sprintf(*rettxt, "check_loop complete\n");
      return 1;
    }
#ifdef   _DVB_T2_SIGNALLING_H_
    if (strcmp_nocase(cmd,"mplp"        ) == 0) {
       i = (int)dval;
       sprintf(*rettxt, "%d DATA streams\n", Si2183_L2_Test_MPLP(front_end, i) );
       return 1;
    }
    if (strcmp_nocase(cmd,"l1_misc"     ) == 0) {
       Si2183_L2_Read_L1_Misc_Data (front_end, &misc);
       SiLabs_L1_Misc_Text         (&misc, *rettxt);
       return 1;
    }
    if (strcmp_nocase(cmd,"l1_pre"      ) == 0) {
       Si2183_L2_Read_L1_Pre_Data (front_end, &pre);
       SiLabs_L1_Pre_Text         (&pre, *rettxt);
       return 1;
    }
    if (strcmp_nocase(cmd,"l1_post"     ) == 0) {
       Si2183_L2_Read_L1_Post_Data (front_end, &post);
       SiLabs_L1_Post_Text         (&post, *rettxt);
       return 1;
    }
    if (strcmp_nocase(cmd,"check_T2_signalling") == 0) {
       i = (int)dval;
       if ( i == 0 ) { front_end->misc_infos &= ~0x01000000; }
       if ( i == 1 ) { front_end->misc_infos |=  0x01000000; }
       i = front_end->misc_infos;
       printf("misc_infos 0x%08X\n", front_end->misc_infos );
       return 1;
    }
    if (strcmp_nocase(cmd,"dektec"      ) == 0) {
      if (strcmp_nocase(sub_cmd,"full") == 0) {
        Si2183_L2_Read_L1_Misc_Data (front_end, &misc);
        Si2183_L2_Read_L1_Pre_Data  (front_end, &pre);
        Si2183_L2_Read_L1_Post_Data (front_end, &post);
      }
#ifdef    SILABS_DEKTEC_T2_CONFIGURATION
      if (strcmp_nocase(sub_cmd,"loop") == 0) {
        while (1) {
          Si2183_L2_Read_L1_Misc_Data (front_end, &misc);
          Si2183_L2_Read_L1_Pre_Data  (front_end, &pre);
          Si2183_L2_Read_L1_Post_Data (front_end, &post);
          SiLabs_DekTec_T2_Configuration (&pre, &post, &misc, *rettxt);
          system("cls");
          printf("%s\n", *rettxt);
          system_wait((int)dval);
        }
      }
      SiLabs_DekTec_T2_Configuration (&pre, &post, &misc, *rettxt);
#endif /* SILABS_DEKTEC_T2_CONFIGURATION */
      return 1;
    }
#endif /* _DVB_T2_SIGNALLING_H_ */
#ifdef    DEMOD_ISDB_T
    if (strcmp_nocase(cmd,"isdb-t"      ) == 0) {
      if (strcmp_nocase(sub_cmd,"layer_info"   ) == 0) {
        if ( Si2183_L1_ISDBT_LAYER_INFO(front_end->demod, dval) != NO_Si2183_ERROR ) {
          SiTRACE("Si2183_L1_ISDBT_LAYER_INFO error when checking layer %d!\n", dval);
          SiERROR("Si2183_L1_ISDBT_LAYER_INFO error!\n");
          sprintf(*rettxt, "error when checking layer %d\n", (int)dval );
          return 1;
        }

        i_constellation = front_end->demod->rsp->isdbt_layer_info.constellation;
        i_code_rate     = front_end->demod->rsp->isdbt_layer_info.code_rate    ;
        IL              = front_end->demod->rsp->isdbt_layer_info.il           ;
        nb_seg          = front_end->demod->rsp->isdbt_layer_info.nb_seg       ;

        switch (i_constellation) {
          case Si2183_ISDBT_LAYER_INFO_RESPONSE_CONSTELLATION_QPSK:
            sprintf(s_constellation,"QPSK");
            break;
          case Si2183_ISDBT_LAYER_INFO_RESPONSE_CONSTELLATION_DQPSK:
            sprintf(s_constellation,"DPSK");
            break;
          case Si2183_ISDBT_LAYER_INFO_RESPONSE_CONSTELLATION_QAM16:
            sprintf(s_constellation,"QAM16");
            break;
          case Si2183_ISDBT_LAYER_INFO_RESPONSE_CONSTELLATION_QAM64:
            sprintf(s_constellation,"QAM64");
            break;
          default:
            sprintf(s_constellation,"unknown");
            break;

        }
        switch (i_code_rate)
        {
          case Si2183_ISDBT_LAYER_INFO_RESPONSE_CODE_RATE_1_2:
            sprintf(s_code_rate,"1_2");
            break;
          case Si2183_ISDBT_LAYER_INFO_RESPONSE_CODE_RATE_2_3:
            sprintf(s_code_rate,"2_3");
            break;
          case Si2183_ISDBT_LAYER_INFO_RESPONSE_CODE_RATE_3_4:
            sprintf(s_code_rate,"3_4");
            break;
          case Si2183_ISDBT_LAYER_INFO_RESPONSE_CODE_RATE_5_6:
            sprintf(s_code_rate,"5_6");
            break;
          case Si2183_ISDBT_LAYER_INFO_RESPONSE_CODE_RATE_7_8:
            sprintf(s_code_rate,"7_8");
            break;
          default:
            sprintf(s_code_rate,"unknown");
            break;
        }

        sprintf(*rettxt, "constellation %s codeRate %s il %d nbSeg %d \n", s_constellation, s_code_rate, IL, nb_seg);
        return 1;
      }
    }
#endif    /* DEMOD_ISDB_T */
    sprintf(*rettxt, "unknown '%s' demod command for Si2183, can not process '%s %s %s %f'\n", cmd, target, cmd, sub_cmd, dval);
    return 0;
  }
  else if (strcmp_nocase(target,"ter_tuner" ) == 0) {
#ifdef    DEMOD_DVB_T
   #ifdef    INDIRECT_I2C_CONNECTION
    front_end->f_TER_tuner_enable(front_end->callback);
   #else  /* INDIRECT_I2C_CONNECTION */
    Si2183_L2_Tuner_I2C_Enable(front_end);
   #endif /* INDIRECT_I2C_CONNECTION */
    i = 0;
    if (strcmp_nocase(cmd,"init_done"       ) == 0) { i++;
      if ((int)dval >= 1) {front_end->TER_tuner_init_done = 1;}
      if ((int)dval == 0) {front_end->TER_tuner_init_done = 0;}
      sprintf(*rettxt, "front_end->TER_tuner_init_done %d\n", front_end->TER_tuner_init_done);
    }
    if (strcmp_nocase(cmd,"clock_on"        ) == 0) { i++;
      #ifdef    TER_TUNER_CLOCK_ON
      sprintf(*rettxt, "TER_TUNER_CLOCK_ON %d\n", TER_TUNER_CLOCK_ON(front_end->tuner_ter));
      #endif /* TER_TUNER_CLOCK_ON */
    }
    if (strcmp_nocase(cmd,"clock_off"       ) == 0) { i++;
      #ifdef    TER_TUNER_CLOCK_OFF
      sprintf(*rettxt, "TER_TUNER_CLOCK_OFF %d\n", TER_TUNER_CLOCK_OFF(front_end->tuner_ter));
      #endif /* TER_TUNER_CLOCK_OFF */
    }
    if (strcmp_nocase(cmd,"init_after_reset") == 0) { i++;
      #ifdef    TER_TUNER_INIT
      sprintf(*rettxt, "TER_TUNER_INIT %d\n", TER_TUNER_INIT(front_end->tuner_ter));
      #endif /* TER_TUNER_INIT */
    }
    if (strcmp_nocase(cmd,"init_after_reset") == 0) { i++;
      #ifdef    TER_TUNER_INIT
      sprintf(*rettxt, "TER_TUNER_INIT %d\n", TER_TUNER_INIT(front_end->tuner_ter));
      #endif /* TER_TUNER_INIT */
    }
    if (strcmp_nocase(cmd,"standby"         ) == 0) { i++;
      #ifdef    TER_TUNER_STANDBY
      sprintf(*rettxt, "TER_TUNER_STANDBY %d\n", TER_TUNER_STANDBY(front_end->tuner_ter));
      #endif /* TER_TUNER_STANDBY */
    }
    if (strcmp_nocase(cmd,"wakeup"          ) == 0) { i++;
      #ifdef    TER_TUNER_WAKEUP
      sprintf(*rettxt, "TER_TUNER_WAKEUP %d\n", TER_TUNER_WAKEUP(front_end->tuner_ter));
      #endif /* TER_TUNER_WAKEUP */
    }
  #ifdef    TER_TUNER_SILABS
    if (i==0) {
      SiLabs_TER_Tuner_Test(front_end->tuner_ter, target, cmd, sub_cmd, dval, retdval, rettxt);
    }
  #endif /* TER_TUNER_SILABS */
   #ifdef    INDIRECT_I2C_CONNECTION
    front_end->f_TER_tuner_disable(front_end->callback);
   #else  /* INDIRECT_I2C_CONNECTION */
    Si2183_L2_Tuner_I2C_Disable(front_end);
   #endif /* INDIRECT_I2C_CONNECTION */
    if (strlen(*rettxt)!=0) { return 1; }
#endif /* DEMOD_DVB_T */
    sprintf(*rettxt, "no ter_tuner command implemented so far for Si2183, can not process '%s %s %s %f'\n", target, cmd, sub_cmd, dval);
    return 0;
  }
  else if (strcmp_nocase(target,"sat_tuner" ) == 0) {
#ifdef    DEMOD_DVB_S_S2_DSS
   #ifdef    INDIRECT_I2C_CONNECTION
    front_end->f_SAT_tuner_enable(front_end->callback);
   #else  /* INDIRECT_I2C_CONNECTION */
    Si2183_L2_Tuner_I2C_Enable(front_end);
   #endif /* INDIRECT_I2C_CONNECTION */
    i = 0;
    if (strcmp_nocase(cmd,"init_done"       ) == 0) { i++;
      if ((int)dval >= 1) {front_end->SAT_tuner_init_done = 1;}
      if ((int)dval == 0) {front_end->SAT_tuner_init_done = 0;}
      sprintf(*rettxt, "front_end->SAT_tuner_init_done %d\n", front_end->SAT_tuner_init_done);
    }
    if (strcmp_nocase(cmd,"clock_on"        ) == 0) { i++;
      #ifdef    SAT_TUNER_CLOCK_ON
      sprintf(*rettxt, "SAT_TUNER_CLOCK_ON %d\n", SAT_TUNER_CLOCK_ON(front_end->tuner_sat));
      #endif /* SAT_TUNER_CLOCK_ON */
    }
    if (strcmp_nocase(cmd,"clock_off"       ) == 0) { i++;
      #ifdef    SAT_TUNER_CLOCK_OFF
      sprintf(*rettxt, "SAT_TUNER_CLOCK_OFF %d\n", SAT_TUNER_CLOCK_OFF(front_end->tuner_sat));
      #endif /* SAT_TUNER_CLOCK_OFF */
    }
    if (strcmp_nocase(cmd,"init_after_reset") == 0) { i++;
      #ifdef    SAT_TUNER_INIT
      sprintf(*rettxt, "SAT_TUNER_INIT %d\n", SAT_TUNER_INIT(front_end->tuner_sat));
      #endif /* SAT_TUNER_INIT */
    }
    if (strcmp_nocase(cmd,"standby"         ) == 0) { i++;
      #ifdef    SAT_TUNER_STANDBY
      sprintf(*rettxt, "SAT_TUNER_STANDBY %d\n", SAT_TUNER_STANDBY(front_end->tuner_sat));
      #endif /* SAT_TUNER_STANDBY */
    }
    if (strcmp_nocase(cmd,"wakeup"          ) == 0) { i++;
      #ifdef    SAT_TUNER_WAKEUP
      sprintf(*rettxt, "SAT_TUNER_WAKEUP %d\n", SAT_TUNER_WAKEUP(front_end->tuner_sat));
      #endif /* SAT_TUNER_WAKEUP */
    }
  #ifdef    SAT_TUNER_SILABS
    if (i==0) {
      SiLabs_SAT_Tuner_Test(front_end->tuner_sat, target, cmd, sub_cmd, dval, retdval, rettxt);
    }
  #endif /* SAT_TUNER_SILABS */
   #ifdef    INDIRECT_I2C_CONNECTION
    front_end->f_SAT_tuner_disable(front_end->callback);
   #else  /* INDIRECT_I2C_CONNECTION */
    Si2183_L2_Tuner_I2C_Disable(front_end);
   #endif /* INDIRECT_I2C_CONNECTION */
    if (strlen(*rettxt)!=0) { return 1; }
#endif /* DEMOD_DVB_S_S2_DSS */
    sprintf(*rettxt, "Can not process '%s %s %s %f'\n", target, cmd, sub_cmd, dval);
    return 0;
  }
  else if (strcmp_nocase(target,"lnb_supply") == 0) {
    sprintf(*rettxt, "no lnb_supply command implemented so far for Si2183, can not process '%s %s %s %f'\n", target, cmd, sub_cmd, dval);
    return 0;
  }
  else {
    sprintf(*rettxt, "unknown '%s' command for Si2183, can not process '%s %s %s %f'\n", cmd, target, cmd, sub_cmd, dval);
    SiTRACE(*rettxt);
    SiERROR(*rettxt);
    return 0;
  }
  return 0;
}
#endif /* SILABS_API_TEST_PIPE */

/**/


