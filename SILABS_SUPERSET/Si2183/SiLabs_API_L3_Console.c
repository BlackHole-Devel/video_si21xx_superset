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
/*                              SiLabs API Console Functions                                                 */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains all console functions for a SiLabs digital TV demodulator Evaluation board    */
/*************************************************************************************************************/
/* Change log:

  As from V2.7.9:
   <new_feature>[T2/Signaling] Adding 'T2_signaling_on'/'T2_signaling_off' options to control T2 signaling tracing upon lock.

  As from V2.7.7:
   <new_feature>[demo/option] Adding 'status' option (similar to pressing <return> but can be used in a call to Silabs_demoloop("status"); )
   <new_feature>[SAT/Unicable] Adding Silabs_UserInput_Unicable_Config to allow setting all Unicable options from the console

  As from V2.7.5:
   <new_feature>[DVB-S2/ISI]
    Adding Silabs_UserInput_isi_id to allow selecting the ISI id.
    In Silabs_UserInput_Lock: asking for ISI id if locking in DVB-S2
   <improvement>[demo_loop]
    Adding 'return 1' for several options.

  As from V2.6.5:
    <new_feature>[demod_loop] In Silabs_demoloop: it's now possible to provide a string as an argument to demod_loop,
      in order to execute easily small tests.
    <improvement>[TS/GPIF] In Silabs_UserInput_TS: removing Cypress ports control, since it's now in the wrapper

  As from V2.6.4:
    <compatibility>[TER/No_DVBT] In Silabs_UserInput_SeekNext: adding tags to allow compiling without DVBT

  As from V2.6.3:
    <improvement>[SPI/setup] In Silabs_UserInput_SPI_Setup: not asking for sub fields if SPI is not used

  As from V2.6.2:
    <improvement>[No_DVB-T/BW] In Silabs_UserInput_bw_Hz: setting BW for 'TERRESTRIAL' instead of "DVB-T' to work with ISDB-T

  As from V2.6.0:
    <compatibility>[Linux/Ubuntu] In Silabs_demoloop: minor changes to avoid compiling issues with Linux.

  As from V2.5.9:
    <new_feature>[DVB-C2/Seek]
      In Silabs_UserInput_SeekInit: asking for BW for DVB-C2

  As from V2.5.8:
    <new_feature>[Broadcast_I2c/Multiples/Si2183]
      Adding 'broadcast_demods' and 'broadcast_i2c' options to demo loop
    <new_feature>[ISDB-T/AC_data]
      Adding 'Get_AC_data' to demo loop
    <new_feature>[SAT/Unicable_II]
      Support for Unicable II
      Adding 'unicable_install_II' option in demo_loop
      (requires compiling with UNICABLE_II_COMPATIBLE, in addition to UNICABLE_COMPATIBLE)
    <new_feature>[DVB-C2/Seek]
      In Silabs_UserInput_bw_Hz: supporting DVB-C2 (6 or 8 MHz)
      In Silabs_UserInput_Lock: asking for BW for DVB-C2
      In Silabs_UserInput_SeekInit: asking for Seek_Step for DVB-C2
      In Silabs_UserInput_SeekNext: supporting DVB-C2 (browsing through Data Slices and PLPs)
      In SiLabs_Scan_Table_Carrier_Text: tracing BW in DVB-C2
    <improvement>[traces] In Silabs_UserInput_SeekNext: tracing freq during handshakes

  As from V2.5.6:
   <new_feature>[Auto_Config] In SiLabs_macro_selection: adding auto configuration based on Cypress-contained macro

  As from V2.5.4:
   <new_feature>[SPI/Config] Adding Silabs_UserInput_SPI_Setup
     Adding 'SPI_Config' option in demo_loop
   <new_feature>[Cypress/Ports] Adding Silabs_UserInput_Cypress_Ports
     Adding 'Cypress_Ports' option in demo_loop

  As from V2.5.3:
   <new_feature>[TER_Tuner/Config]
     Adding Silabs_UserInput_TER_Tuner_ClockConfig
     Adding Silabs_UserInput_SAT_Tuner_Sub
     Adding SiLabs_UserInput_SAT_LNB_Chip_Index
     Adding 'TER_Tuner_ClockConfig' option in demo_loop
     Adding Silabs_UserInput_TER_Tuner_AGC_Input, Silabs_UserInput_TER_Tuner_IF_Output
            Silabs_UserInput_TER_Tuner_ClockConfig, Silabs_UserInput_SAT_Tuner_Sub, SiLabs_UserInput_SAT_LNB_Chip_Index
        and Silabs_UserInput_TER_Tuner_ClockConfig calls in manual configuration loop
   <improvement>[no_TER] In Silabs_UserInput_bw_Hz: not compiling code is not a terrestrial frontend

  As from V2.5.2:
   <improvement>[seek/future] in Silabs_UserInput_SeekNext: comparing t2_version >= SILABS_T2_VERSION_1_3_1 to be compliant
         with possible future T2 versions.

  As from V2.5.1:
   <improvement>[cleanup] removing unused variables
    In Silabs_UserInput_Test: removing valid_target
    In Silabs_demoloop: removing dval, num_data_slice, num_plp, symbol_rate_bps, constellation;
    In Silabs_UserInput_SeekNext: setting standard = i = plp_type = plp_id = T2_mode = 0; to avoid warning when not used.


  As from V2.5.0:
   <correction>[T2_lock_mode] In Silabs_UserInput_Lock, using T2_lock_mode in the call to SiLabs_API_lock_to_carrier.
   <improvement>[config/TER_only/SAT_only]: In main: if tuner i2c address is 0x00, skip config for TER or SAT respectively.
   <improvement>[TS/GPIF] In Silabs_UserInput_TS: Adding control of the mux used to select which TS is sent to GPIF

  As from V2.4.7:
   <improvement/compatibility> In Silabs_UserInput_SeekNext:  setting hierarchy to 0 by default to avoid compiler warning.
                               in Silabs_UserInputTSCrossbar: setting variables default values to avoid compiler warnings.

  As from V2.4.6:
   <correction>[RENAMING] renaming Silabs_UserInput_TER_Address for consistency with the rest of the code.
    In 'Silabs_demoloop': adding 'TER_address'
   <new_feature>[TER_Tuner/Config]
     Adding Silabs_UserInput_TER_Tuner_AGC_Input and Silabs_UserInput_TER_Tuner_IF_Output
     Adding 'TER_Tuner_AGC_Input' and 'TER_Tuner_IF_Output' options in demo_loop

  As from V2.4.4:
   <new_feature> [DVB-T2/MPLP] In Silabs_UserInput_SeekNext: DVB-T2 MPLP parsing OK with MPLP in both T2-base and T2-lite

  As from V2.4.3:
   Adding SiLabs_Scan_Check_And_Add_Carrier, used during SeekNext to check signal quality, turn TS on and store the channel information.
    In Silabs_UserInput_SeekNext: checking all hierarchy and PLP information when required, and calling SiLabs_Scan_Check_And_Add_Carrier when locked.
    This shows the recommended behavior when dealing with MPLP and hierarchical channels.
    In the final application, SI/PSI parsing should be done in a function similar to SiLabs_Scan_Check_And_Add_Carrier.

  As from V2.4.2:
    Adding access to all SW configuration functions. This is useful when only a couple parameters are different
     between a new HW and an existing macro.

  As from V2.4.1:
    Adding ISDBT layer monitoring support
    Adding access to SW configuration functions. This allows starting with an existing
     configuration macro, then changing only the minimum parameters to match any HW.
     NB: following this, a 'hwinit' is required.

  As from V2.4.0:
    Adding TS Crossbar support

  As from V2.3.9:
    Channel table, carrier info and user input updated for ISDB-T support

  As from V2.3.7:
    Adding Silabs_UserInput_traceLevel
    In Silabs_UserInput_SeekInit: Adding MCNS case

  As from V2.3.5:
  <new_feature> [SPI] In demo_loop: adding 'spi' option
  <improvement> In SiLabs_Scan_Zap_To_Index: changing printf to use "%s", to avoid compilation errors with some environments.
  <new feature>[GPIF/QUAD] In Silabs_UserInput_TS: controlling GPIF MUX on QUAD EVB (Dual_Si2191_Si216x2_Si2164).
    To make this easy, nb_front_ends has been made global.

  As from V2.3.2:
   Adding Silabs_UserInput_T2_lock_mode
   In Silabs_UserInput_Lock:          calling Silabs_UserInput_T2_lock_mode if required.
   In Silabs_UserInput_SeekInit:      calling Silabs_UserInput_T2_lock_mode if required.
   In SiLabs_Scan_Table_Carrier_Text: displaying T2 mode
   In Silabs_demoloop:                Adding T2_lock_mode and handshake options

  As from V2.3.1:
   In Silabs_UserInput_TS: adding the 'OFF' case.
   In 'main': using clock_control for TER and SAT

  As from V2.2.9:
   Limiting string lengths below 500 in sprintf and printf, to avoid warnings when compiled with '-pedantic'
   In 'main':
     Using unsigned int for values entered as hexa values.during manual configuration.
     Manual configuration now including FEF configuration and LNBH controller address

  As from V2.2.8:
   In Silabs_UserInput_tune: Compatibility with MCNS
   Adding 'simu' and 'close' options in demo_loop
   Separating the init macro management from the console code.
    To enable configuration using macros, add the SiLabs_API_L3_Config_Macros code, and define CONFIG_MACROS at project level.

  As from V2.2.6:
   In Silabs_UserInput_tune: Compatibility with DVB-C2
   In Silabs_UserInput_Lock: Adding T2 Base/Lite flag for T2 in call to SiLabs_API_lock_to_carrier
   In Silabs_UserInput_SeekNext: Compatibility with DVB-C2 (early version)
   In SiLabs_Scan_Table_Carrier_Text: Compatibility with DVB-C2
   Adding T2 Base/Lite flag in channel tables and in function calls
   In Silabs_demoloop:
    Adding 'detect' option
    Adding 'cell_id' option
   In Silabs_help: Adding C2 help

  As from V2.2.2:
    Adding SiLabs_SW_config_from_macro
    Adding SiLabs_SW_config_selection

    In console main:
    SW init via several ways:
      1- init from a batch file, using the first argument as the configuration selector
      2- init from a user-selected configuration
      3- init using manually-entered settings

  As from V2.1.9:
   In Silabs_UserInput_standard:
    Adding 'C2'
   In Silabs_UserInput_demod:
    Using '0x216...' for Si_2164 derivatives, to differentiate 68A/69A from 68B/69B

  As from V2.1.8:
   Replaced 'DEMOD_Si21xx' compilation flags by 'Si21xx_COMPATIBLE', to have unused flags removed during export
   In Silabs_UserInput_SeekNext: 'beep' on each new carrier
   In SiLabs_Scan_Loop: displaying number of carriers found during the last loop instead of the total number of carriers.
   In Silabs_demoloop:  adding 'unicable_install' and 'unicable_uninstall' options

  As from V2.1.6:
   In Silabs_UserInput_data_slice_id:
    Comments improved (removed 'plp id')
   In Silabs_UserInput_VoltageTone:
    Maintaining consistency between Unicable and normal mode settings (for polarization and band)
   In Silabs_UserInput_SeekNext:
    'bell' on a lock only if traces are activated
   In Silabs_demoloop:
    Better Linux compatibility (using "%s" in printf)
    BW forced to 8MHz for 'blindlock'
    'kbit' not possible if not on WIN32

  As from V2.1.3:
  In Silabs_UserInput_demod:
   Compatibility with Si2185
  In Silabs_demoloop:
   Compatibility with DVB-C2

  As from V2.1.2:
  Adding Silabs_UserInput_data_slice_id (for DVB-C2)
  Adding Silabs_UserInput_Position function (for Unicable SAT)
  Moving input functions before Silabs_UserInput_SeekInit (as they are used by SeekInit)
  In Silabs_UserInput_plp_id:
    dvbt_t2_plp_id renamed as plp_id (valid for T2 and C2)
  In Silabs_UserInput_Lock:
   Adding data_slice_id for C2
   Asking for polarization and band only for SAT
  In Silabs_UserInput_SeekInit:
   Asking for SAT voltage and tone for SAT standards
    In Silabs_demoloop:
     Adding 'monitor' option
     Adding 'cell_id' option
     Adding 'T+' and 'T-' options (for Unicable SAT)
     Setting Unicable values according to the user selection
     For 'blindlock' option:
      displaying execution time
  In Silabs_UserInput_SeekNext:
   Adding num_data_slice for C2

  As from V2.1.1:
  Adding Silabs_UserInput_demod, to allow several demods in a single application
  In SiLabs_Scan_Table_Carrier_Text:
   Tracing Ku frequencies for SAT
  In main:
   Calling Silabs_UserInput_demod to select demod

  As from V2.0.9:
  In SiLabs_I2C_UserInput_read & SiLabs_I2C_UserInput_write:
   prototypes changed to 'void', to avoid shadowing the global 'i2c'.
  In Silabs_UserInput_bw_Hz:
   Converting bandwidth_MHz (float) to  bandwidth_Hz (int) for comparing user entry with possible values.
   ('==' operator does not work well on float values, and may provide various results depending on the platform)

  As from V2.0.8:
   In Silabs_UserInput_SeekNext:
    DVB-T: Storing 2 carriers in table when locked on a Hierarchical DVB-T signal
   (similar to what is done on T2 signals for MPLP: storing one carrier per 'DATA' plp_id)
    MPLP management changed for C2 compatibility (which also has MPLP capability).
     The criterion is now 'num_plp>1', to allow DVB-T2/C2 compatibility

  As from V2.0.7:
   In Silabs_UserInput_SeekNext:
    Compatibility with the 'handshake' feature.

  As from V2.0.6:
    In Silabs_demoloop:
      Adding 'tune' option
      Adding 'blindlock' option

  As from V2.0.1:
    main function compatible with dual TER front-end applications where a single xtal is shared between 2 front-end:
     XTAL on FrontEnd_Table[0] TER tuner, provided to:
      FrontEnd_Table[0] Demod
      FrontEnd_Table[1] TER tuner
     clock from FrontEnd_Table[1] TER tuner, provided to:
      FrontEnd_Table[1] Demod

    --------      ---------------  EN_XOUT/CONFIG_CLOCKS:CLOCK_MODE_XTAL                          ---------------
    | XTAL |----->| TER Tuner 0 |---------------------------------------------------------------->|   Demod 0   |
    --------      ---------------  |                                                              ---------------
              CLOCK_MODE_XTAL      |                                                            CLK_MODE_CLK_CLKIO
                                   |
                                   |
                                   |  ---------------  EN_XOUT/CONFIG_CLOCKS:CLOCK_MODE_XTAL      ---------------
                                   -->| TER Tuner 1 |-------------------------------------------->|   Demod 1   |
                                      ---------------                                              ---------------
                                  CLOCK_MODE_EXTCLK                                             CLK_MODE_CLK_CLKIO

    This is provided as an example for Si2158:
    if (fe==0) {
      front_end->Si216x_FE->tuner_ter->cmd->power_up.clock_mode      = Si2158_POWER_UP_CMD_CLOCK_MODE_XTAL;
      front_end->Si216x_FE->tuner_ter->cmd->power_up.en_xout         = Si2158_POWER_UP_CMD_EN_XOUT_EN_XOUT;
      front_end->Si216x_FE->tuner_ter->cmd->config_clocks.clock_mode = Si2158_CONFIG_CLOCKS_CMD_CLOCK_MODE_XTAL;
    }
    if (fe==1) {
      front_end->Si216x_FE->tuner_ter->cmd->power_up.clock_mode      = Si2158_POWER_UP_CMD_CLOCK_MODE_EXTCLK;
      front_end->Si216x_FE->tuner_ter->cmd->power_up.en_xout         = Si2158_POWER_UP_CMD_EN_XOUT_EN_XOUT;
      front_end->Si216x_FE->tuner_ter->cmd->config_clocks.clock_mode = Si2158_CONFIG_CLOCKS_CMD_CLOCK_MODE_EXTCLK;
    }

    It also requires adaptations in the corresponding Si21x8_L2_API.c/Si21x8_PowerUpWithPatch function:
    The clock_mode and en_xout values needs to be set based on the above values:
    (example for Si2158):
      if ((return_code = Si2158_L1_POWER_UP (api,
                            Si2158_POWER_UP_CMD_SUBCODE_CODE,
                            api->cmd->power_up.clock_mode,
                            api->cmd->power_up.en_xout,
                            . . .

  As from V2.0.0:
    Defining FRONT_END_COUNT if not defined at project level.
      This allows setting FRONT_END_COUNT at project level only for multi front-end applications

  As from V1.9.9:
    Adding NO_SAT tags to allow using Si2169 code without SAT features

  As from V1.9.8:
   last_plp_id stored during init as '-1' to indicate auto mode

  As from V1.9.7:
   Handling MCNS in Silabs_UserInput_qam, Silabs_UserInput_standard, Silabs_UserInput_Lock
   Removing TER_TUNER_MENU from Silabs_menu
   Removing TER_TUNER_LOOP from Silabs_demoloop

  As from V1.9.6:
   In main: setting i2c to L0_FastI2C(); by default

  As from V1.9.0:
   In Silabs_demoloop:
    Removing duplicate SATauto options

  As from V1.8.9:
   Treating symbol_rate as unsigned int (for proper display of high SAT SR when scanning)

   Adding Test Pipe feature (only if SILABS_API_TEST_PIPE is defined at project level), using new Silabs_UserInput_Test function
   In Silabs_UserInput_SeekNext:
    Checking num_plp if locked in DVB-T2, check PLP infos for each PLP ID and store one 'channel' per PLP ID
   In SiLabs_Scan_Loop:
    Adding scan duration display

   Adding console options:
    AutoSAT   : SiLabs_API_SAT_AutoDetect(front_end, 1)
    NoAutoSAT : SiLabs_API_SAT_AutoDetect(front_end, 0)
    autocheck : Display auto detect settings
    install   : SiLabs_API_SAT_Unicable_Install
    positionA : unicable->satellite_position = UNICABLE_POSITION_A
    positionB : unicable->satellite_position = UNICABLE_POSITION_B


  As from V1.8.8:
   In Silabs_demoloop: adding 'ATV', 'up' and 'down' options
   Adding functions to manage easily 'up' and 'down' zapping.

  As from V1.8.6:
   Compatibility with export for non 'SATELLITE_FRONT_END'

  As from V1.8.5:
   In Silabs_UserInput_SeekInit: set default bw as 8MHz (for DVB-C)
   In Silabs_UserInput_SeekNext: tracing detected standard as well, to test auto-detect
   In SiLabs_Scan_Table_Carrier_Text: tracing freq un Ku band if Unicable

   Adding console options:
    AutoTER   : SiLabs_API_TER_AutoDetect(front_end, 1)
    NoAutoTER : SiLabs_API_TER_AutoDetect(front_end, 0)
    autocheck : Display auto detect settings
    voltage_and_tone
    AutoSAT   : SiLabs_API_SAT_AutoDetect(front_end, 1)
    NoAutoSAT : SiLabs_API_SAT_AutoDetect(front_end, 0)
    install   : SiLabs_API_SAT_Unicable_Install
    horizontal: unicable->polarization = SILABS_POLARIZATION_HORIZONTAL
    vertical  : unicable->polarization = SILABS_POLARIZATION_VERTICAL
    low       : unicable->band         = UNICABLE_LOW_BAND
    high      : unicable->band         = UNICABLE_HIGH_BAND
    diseqc    : tracing Diseqc data (toggle)
    hardtune  : selecting Unicable values
    unicable  : SiLabs_Unicable_API_Tune_Infos
    tones     : SiLabs_Unicable_API_All_Tones
    tones_off : SiLabs_Unicable_API_All_Off

  As from V1.7.9:
   Adding 'slow' and 'fast' options in demo loop to allow easy testing of several i2c speeds

  As from V1.7.6:
   Some SiTRACE calls surrounded by curly brackets to allow compiling without SITRACES

  As from V1.7.5:
   Silabs_UserInput_qam changed to take text values for constellations

  As from V1.7.3:
    some lines moved for greater compatibility with Visual Studio

  As from V1.6.3:
    compatibility with SAT-only exports in Silabs_UserInput_bw_Hz

  As from V1.5.6:
    Silabs_UserInput_SeekInit uses 8000000 as default seekBWHz
 *************************************************************************************************************/
/* TAG V2.8.0 */

#include "SiLabs_API_L3_Console.h"
signed   int gpif_monitor_with_pulse;
#define MAX_ENTRY_LENGTH 200
signed   int   commandCount  = 0;
signed   int   fe;
signed   int   nb_front_ends;
signed   int   full_menu;
char           entryBuffer[MAX_ENTRY_LENGTH];
char          *userEntry;
char           messageBuffer[10000];
signed   int  last_standard       ;
signed   int  last_freq           ;
signed   int  last_bandwidth_Hz   ;
signed   int  last_stream         ;
unsigned int  last_symbol_rate_bps;
signed   int  last_constellation  ;
signed   int  last_polarization   ;
signed   int  last_band           ;
signed   int  last_num_data_slice ;
signed   int  last_num_plp        ;
signed   int  last_plp_id         ;
signed   int  last_T2_base_lite   ;
signed   int  last_data_slice_id  ;
signed   int  last_carrier_index  ;
signed   int  demod_code[4];
signed   int  demod_add [4];
char          demod_string_0[100];
char          demod_string_1[100];
char          demod_string_2[100];
char          demod_string_3[100];
char         *demod_string[4];
signed   int  clock_source;
signed   int  clock_input;
signed   int  clock_freq;
signed   int  clock_control;
unsigned int  agc1_mode;
signed   int  dtv_agc_source;
signed   int  dtv_out_type;
signed   int  agc1_inversion;
unsigned int  agc2_mode;
signed   int  agc2_inversion;
signed   int  xtal;
signed   int  xout;
signed   int  tag_index;
signed   int  fe_index;
signed   int  demod_id;
signed   int  send_option;
signed   int  clk_pin;
signed   int  clk_pola;
signed   int  data_pin;
signed   int  data_order;
signed   int  loop_counter;
#ifdef    USB_Capability
unsigned int  OEA;
unsigned int  IOA;
unsigned int  OEB;
unsigned int  IOB;
unsigned int  OED;
unsigned int  IOD;
#endif /* USB_Capability */
unsigned int  div_a;
unsigned int  div_b;
signed   int  ter_tuner_address;
signed   int  sat_tuner_address;
signed   int  lnb_chip_address;
#ifdef    TERRESTRIAL_FRONT_END
signed   int  ter_tuner_code;
signed   int  ter_tuner_index;
#ifdef    DEMOD_DVB_T2
signed   int  fef_mode;
unsigned int  fef_pin;
signed   int  fef_level;
#endif /* DEMOD_DVB_T2 */
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
signed   int  lnb_code;
signed   int  lnb_index;
signed   int  sat_tuner_code;
signed   int  sat_tuner_index;
signed   int  sat_tuner_sub;
signed   int  spectrum_inversion;
#ifdef   CHANNEL_BONDING
  SILABS_Channel_Bonding  *Channel_Bonding;
#endif /* CHANNEL_BONDING */
#endif /* SATELLITE_FRONT_END */


SiLabs_Carriers_Struct *Carriers_Table = NULL;

SILABS_FE_Context     FrontEnd_Table[FRONT_END_COUNT];
SILABS_FE_Context    *front_end;
CUSTOM_Status_Struct  FE_Status;
CUSTOM_Status_Struct *custom_status;

#ifdef    TS_CROSSBAR
SILABS_TS_Crossbar    TS_Crossbar_Table[FRONT_END_COUNT/2];
SILABS_TS_Crossbar   *crossbar;
SILABS_FE_Context    *fe_A;
SILABS_FE_Context    *fe_B;
#endif /* TS_CROSSBAR */

/* Also init a simple i2c context to allow i2c communication checking */
L0_Context* i2c;
L0_Context  i2c_context;
CONNECTION_TYPE mode;

/************************************************************************************************************************
  Silabs_UserInputString function
  Use:        retrieve a string entered by the user
  Parameters: text, a pointer to the string buffer
              max_size, the size allocated by the calling function for the text buffer
  Behavior:   Retrieves the string using fgets to avoid overflows. As fgets keeps the 'carriage return' except
                if the string is longer than max_size, replace it (if present) by the terminating character
  Returns:    the length of the string
************************************************************************************************************************/
signed   int  Silabs_UserInputString      (const char* text) {
  char *newline;
  printf("%s",text);
  if ( (newline = fgets(userEntry, MAX_ENTRY_LENGTH, stdin)) != NULL ) {
    newline = strchr(userEntry, '\n');        /* search for newline character        */
    if ( newline != NULL ) { *newline = '\0'; /* overwrite trailing newline (if any) */ }
  }
  return (int)strlen(userEntry);
}
#ifdef    SiTRACES
/************************************************************************************************************************
  Silabs_UserInput_traces function
  Use:        send a traces configuration message to the L0 SiTRACES functions
              the Silabs_UserInput_traces function asks the user which type of configuration he wishes.
              Then, memorize the message and calls SiTraceConfiguration.
  Returns:    void
  Porting:    Not compiled if SiTRACES is not defined in Silabs_L0_API.h
************************************************************************************************************************/
void          Silabs_UserInput_traces     (void) {
    char *configuration;
    char *msg;
    configuration = userEntry;
    msg           = (char*)malloc(sizeof(char)*100);
    Silabs_UserInputString("Enter the traces configuration string (-<param> ,<value>): ");
    sprintf(msg, "traces %s", configuration);
    printf("%s", SiTraceConfiguration (msg));
}
/************************************************************************************************************************
  Silabs_UserInput_traceLevel function
  Use:        calls the L0 traceLevel function
              the Silabs_UserInput_traceLevel function asks the user which level he wishes to trace.
              Then calls traceLevel.
  Returns:    void
  Porting:    Not compiled if SiTRACES is not defined in Silabs_L0_API.h
************************************************************************************************************************/
void          Silabs_UserInput_traceLevel (void) {
    int on_off;
    int level;
    Silabs_UserInputString("Traces level      ( 0 to 31 ) ? ");
    sscanf(userEntry,"%d",&level);
    printf("Level %3d ",   level);
    Silabs_UserInputString("traces on(1)/off(0) ? ");
    sscanf(userEntry,"%d",&on_off);
    if (on_off) {on_off = 1;}
    SiTraceLevel(level, (unsigned char)on_off);
}
#endif /* SiTRACES */
void          SiLabs_I2C_UserInput_read       (void) {
    int i;
    int readBytes;
    int loop;
    int nbArgs;
    int indexSize;
    unsigned int address;
    unsigned int uintval;
    unsigned int hexval;
    char *input;
    char *array[50];
    int   bytes[50];
    unsigned int iI2CIndex;
    int iNbBytes;
    unsigned char *pbtDataBuffer;

    input = userEntry;
    Silabs_UserInputString("SiLabs_I2C_UserInput_read: i2c read ");

    /* strtok splitting input and storing all items, returning first item */
    array[0] = strtok(input," ");
    if(array[0]==NULL) {return;}
    /* retrieving all remaining items */
    for(loop=1;loop<50;loop++) {
        array[loop] = strtok(NULL," ");
        if(array[loop]==NULL) break;
    }
    nbArgs = loop;
    /* scanning arguments, allowing decimal or hexadecimal input */
    for(loop=0;loop<nbArgs;loop++) {
        hexval=0;
        sscanf(array[loop],"%u", &uintval);
        if (!uintval) sscanf(array[loop],"%x", &hexval);
        bytes[loop] = hexval + uintval;
    }

    address   = bytes[0];
    indexSize = nbArgs - 2;
    if (indexSize <0) return;
    iI2CIndex = 0;
    for (i=1; i<= indexSize; i++) {
      iI2CIndex = (iI2CIndex<<8) + bytes[i];
    }
    iNbBytes  = bytes[loop-1];
/*  printf("address 0x%02x, indexSize %d, ",  address,   indexSize); printf("iI2CIndex 0x%02x, iNbBytes %d\n", iI2CIndex, iNbBytes); */
    pbtDataBuffer = (unsigned char*)malloc(sizeof(unsigned char)*iNbBytes);
    L0_SetAddress   (i2c, address, indexSize);
    readBytes = L0_ReadRawBytes (i2c, iI2CIndex, iNbBytes, pbtDataBuffer);
/*  printf("%d bytes read\n", readBytes); */
    for (i=0; i<readBytes; i++) { printf ("0x%02x ", pbtDataBuffer[i]); }
    if (readBytes) printf("\n");
}
void          SiLabs_I2C_UserInput_write      (void) {
    int i;
    int writeBytes;
    int loop;
    int nbArgs;
    int indexSize;
    unsigned int address;
    unsigned int uintval;
    unsigned int hexval;
    char *input;
    char *array[50];
    int  bytes[50];
    unsigned int iI2CIndex;
    int iNbBytes;
    unsigned char *pbtDataBuffer;

    input = userEntry;

    Silabs_UserInputString("i2c write ");

    /* strtok splitting input and storing all items, returning first item */
    array[0] = strtok(input," ");
    if(array[0]==NULL) {return;}
    /* retrieving all remaining items */
    for(loop=1;loop<50;loop++) {
        array[loop] = strtok(NULL," ");
        if(array[loop]==NULL) break;
    }
    nbArgs = loop;
    /* scanning arguments, allowing decimal or hexadecimal input */
    for(loop=0;loop<nbArgs;loop++) {
        hexval=0;
        sscanf(array[loop],"%u", &uintval);
        if (!uintval) sscanf(array[loop],"%x", &hexval);
        bytes[loop] = hexval + uintval;
    }

    address   = bytes[0];
    indexSize = 0;
    if (indexSize <0) return;
    iI2CIndex = 0;
    iNbBytes  = nbArgs-1;
    pbtDataBuffer = (unsigned char*)malloc(sizeof(unsigned char)*iNbBytes);
    for (i=0; i<iNbBytes; i++) { pbtDataBuffer[i] = bytes[i+1]; }
    L0_SetAddress   (i2c, address, indexSize);
    writeBytes = L0_WriteRawBytes (i2c, iI2CIndex, iNbBytes, pbtDataBuffer);
    if (writeBytes) {printf("%d bytes written\n", writeBytes);} else {printf("Write error!\n");}
}
/************************************************************************************************************************
  Silabs_UserInput_freq function
  Use:        user-level frequency entry function, depending on the standard
              Used to have the user enter the desired tuning frequency, in Hz for TER and in kHz for SAT
  Parameter: standard, the current standard
  Behavior:   Asks the user to enter the tune freq
************************************************************************************************************************/
signed   int  Silabs_UserInput_tune          (CUSTOM_Standard_Enum standard)
{
  int   rf;

  switch (standard)
  { /* DVB_T, DVB_T2 and DVB_C treated first, then DVB_S, DVB_S2 and DSS treated as default */
    case SILABS_DVB_C :
    case SILABS_MCNS  :
    case SILABS_DVB_C2:
    case SILABS_DVB_T :
    case SILABS_ISDB_T:
    case SILABS_DVB_T2: {
      printf("tuning frequency (in Hz)? ");
      break;
    }
    default:              { /*  Used by SAT standards */
      printf("tuning frequency (in kHz)? ");
      break;
    }
  }

  Silabs_UserInputString("");

  sscanf(userEntry,"%d",&rf);
  return rf;
}
/************************************************************************************************************************
  Silabs_UserInput_qam function
  Use:        user-level qam selection function, depending on the standard
  Parameter: standard, the current standard
  Behavior:   Asks the user to enter the qam, then return the corresponding code
************************************************************************************************************************/
CUSTOM_Constel_Enum Silabs_UserInput_qam     (CUSTOM_Standard_Enum standard)
{
    char *qam;
    qam = userEntry;
    switch (standard)
    {
      case SILABS_DVB_C  : {
        printf("DVB-C qam (auto qam16 qam32 qam64 qam128 qam256)?  ");
        scanf("%s",qam);
        if (strcmp_nocase(qam,"auto"  )==0) { return SILABS_QAMAUTO;}
        if (strcmp_nocase(qam,"qam16" )==0) { return SILABS_QAM16  ;}
        if (strcmp_nocase(qam,"qam32" )==0) { return SILABS_QAM32  ;}
        if (strcmp_nocase(qam,"qam64" )==0) { return SILABS_QAM64  ;}
        if (strcmp_nocase(qam,"qam128")==0) { return SILABS_QAM128 ;}
        if (strcmp_nocase(qam,"qam256")==0) { return SILABS_QAM256 ;}
        break;
      }
      case SILABS_MCNS   : {
        printf("MCNS qam (auto qam64 qam256)?  ");
        scanf("%s",qam);
        if (strcmp_nocase(qam,"auto"  )==0) { return SILABS_QAMAUTO;}
        if (strcmp_nocase(qam,"qam64" )==0) { return SILABS_QAM64  ;}
        if (strcmp_nocase(qam,"qam256")==0) { return SILABS_QAM256 ;}
        break;
      }
      case SILABS_DVB_S2 : {
        Silabs_UserInputString("DVB-S2 qam (qpsk 8psk)? ");
        if (strcmp_nocase(qam,"qpsk"  )==0) { return SILABS_QPSK   ;}
        if (strcmp_nocase(qam,"8psk"  )==0) { return SILABS_8PSK   ;}
        break;
      }
      default:             {
        printf("No QAM choice for the selected standard");
        break;
      }
    }
    return SILABS_QAMAUTO;
}
/************************************************************************************************************************
  Silabs_UserInput_stream function
  Use:        user-level stream selection function
  Behavior:   Asks the user to enter the qam, then returns the corresponding code
************************************************************************************************************************/
CUSTOM_Stream_Enum  Silabs_UserInput_stream  (void)
{
  Silabs_UserInputString("DVB-T Stream (HP LP)? ");
  if (strcmp_nocase(userEntry,"hp"  )==0) { SiTRACE("HP\n"); return SILABS_HP;}
  if (strcmp_nocase(userEntry,"lp"  )==0) { SiTRACE("HP\n"); return SILABS_LP;}
  return SILABS_HP;
}
/************************************************************************************************************************
  Silabs_UserInput_data_slice_id function
  Use:        user-level DVB-C2 DATASLICE ID selection function
  Behavior:   Asks the user to enter the DATA SLICE ID, then returns the corresponding value
************************************************************************************************************************/
signed   int  Silabs_UserInput_data_slice_id (void)
{
  int data_slice_id;
  Silabs_UserInputString("DATA SLICE ID ('auto' or <0-255>) ? ");
  if (strcmp_nocase(userEntry,"auto"  )==0) { SiTRACE("DATA SLICE AUTO\n"); return -1;}
  sscanf(userEntry,"%d",&data_slice_id);
  if (data_slice_id <   0) {data_slice_id = 0;}
  if (data_slice_id > 255) {data_slice_id = 0;}
  SiTRACE("DATA SLICE ID %d\n", data_slice_id);
  return data_slice_id;
}
/************************************************************************************************************************
  Silabs_UserInput_plp_id function
  Use:        user-level DVB-T2/C2 PLP ID selection function
  Behavior:   Asks the user to enter the PLP ID, then returns the corresponding value
************************************************************************************************************************/
signed   int  Silabs_UserInput_plp_id        (void)
{
  int plp_id;
  Silabs_UserInputString("PLP ID ('auto' or <0-255>) ? ");
  if (strcmp_nocase(userEntry,"auto"  )==0) { SiTRACE("PLP AUTO\n"); return -1;}
  sscanf(userEntry,"%d",&plp_id);
  if (plp_id <   0) {plp_id = 0;}
  if (plp_id > 255) {plp_id = 0;}
  SiTRACE("PLP ID %d\n", plp_id);
  return plp_id;
}
/************************************************************************************************************************
  Silabs_UserInput_isi_id function
  Use:        user-level DVB-S2 ISI ID selection function
  Behavior:   Asks the user to enter the ISI ID, then returns the corresponding value
************************************************************************************************************************/
signed   int  Silabs_UserInput_isi_id        (void)
{
  int isi_id;
  Silabs_UserInputString("ISI ID ('auto' or <0-255>) ? ");
  if (strcmp_nocase(userEntry,"auto"  )==0) { SiTRACE("ISI AUTO\n"); return -1;}
  sscanf(userEntry,"%d",&isi_id);
  if (isi_id <   0) {isi_id = 0;}
  if (isi_id > 255) {isi_id = 0;}
  SiTRACE("ISI ID %d\n", isi_id);
  return isi_id;
}
/************************************************************************************************************************
  Silabs_UserInput_T2_lock_mode function
  Use:        user-level DVB-T2 lock mode selection function
  Behavior:   Asks the user to enter the T2 lock mode (ANY/T2-Base/T2-Lite)
************************************************************************************************************************/
signed   int  Silabs_UserInput_T2_lock_mode  (void)
{
  int T2_lock_mode;
  Silabs_UserInputString("T2 lock mode ('any' 'base' or 'lite') ? ");
  if (strcmp_nocase(userEntry,"any"   )==0) { SiTRACE("T2 lock mode 'ANY'\n");     return 0;}
  if (strcmp_nocase(userEntry,"base"  )==0) { SiTRACE("T2 lock mode 'T2-Base'\n"); return 1;}
  if (strcmp_nocase(userEntry,"lite"  )==0) { SiTRACE("T2 lock mode 'T2-Lite'\n"); return 2;}
  sscanf(userEntry,"%d",&T2_lock_mode);
  if (T2_lock_mode <   0) {T2_lock_mode = 0;}
  if (T2_lock_mode >   2) {T2_lock_mode = 0;}
  SiTRACE("T2 lock mode %d\n", T2_lock_mode);
  return T2_lock_mode;
}
/************************************************************************************************************************
  Silabs_UserInput_ISDBT_Monitoring_mode function
  Use:        user-level DVB-T2 lock mode selection function
  Behavior:   Asks the user to enter the T2 lock mode (ANY/T2-Base/T2-Lite)
************************************************************************************************************************/
signed   int  Silabs_UserInput_ISDBT_Monitoring_mode(void)
{
  Silabs_UserInputString("ISDB-T Monitoring mode ('0(All)' 'A(layer A)' 'B(layer B)' 'C(layer C)' 'L(Loop)' ? ");
  if (strcmp_nocase(userEntry,"a"  )==0) { SiTRACE("ISDB-T Monitoring mode 'Layer A'\n"); return 0xa;}
  if (strcmp_nocase(userEntry,"b"  )==0) { SiTRACE("ISDB-T Monitoring mode 'Layer B'\n"); return 0xb;}
  if (strcmp_nocase(userEntry,"c"  )==0) { SiTRACE("ISDB-T Monitoring mode 'Layer C'\n"); return 0xc;}
  if (strcmp_nocase(userEntry,"l"  )==0) { SiTRACE("ISDB-T Monitoring mode 'Layer C'\n"); return 0xabc;}
  SiTRACE("ISDB-T Monitoring mode 'All'\n"    );
  return 0x0;
}
/************************************************************************************************************************
  Silabs_UserInput_standard function
  Use:        standard selection function
              Used to have the user enter the desired digital TV standard
  Returns: the selected standard, -1 if error
************************************************************************************************************************/
signed   int  Silabs_UserInput_standard      (void)
{
  char *entry;
  entry = userEntry;

  printf("Standard ( ");
#ifdef    DEMOD_DVB_T
  printf("T "  );
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_DVB_T2
  printf("T2 " );
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_ISDB_T
  printf("ISDBT " );
#endif /* DEMOD_ISDB_T */
#ifdef    DEMOD_DVB_C
  printf("C "  );
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_C2
  printf("C2 "  );
#endif /* DEMOD_DVB_C2 */
#ifdef    DEMOD_MCNS
  printf("MCNS "  );
#endif /* DEMOD_MCNS */
#ifdef    DEMOD_DVB_S_S2_DSS
  printf("S "  );
  printf("S2 " );
  printf("DSS ");
#endif /* DEMOD_DVB_S_S2_DSS */
  printf(")? ");
  if ( Silabs_UserInputString("") != 0) {
#ifdef    DEMOD_DVB_T
         if (strcmp_nocase (entry, "T"   )==0) { return SILABS_DVB_T ;}
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_DVB_T2
         if (strcmp_nocase (entry, "T2"  )==0) { return SILABS_DVB_T2;}
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_ISDB_T
         if (strcmp_nocase (entry, "ISDBT")==0) { return SILABS_ISDB_T;}
#endif /* DEMOD_ISDB_T */
#ifdef    DEMOD_DVB_C
         if (strcmp_nocase (entry, "C"   )==0) { return SILABS_DVB_C ;}
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_C2
         if (strcmp_nocase (entry, "C2"  )==0) { return SILABS_DVB_C2;}
#endif /* DEMOD_DVB_C2 */
#ifdef    DEMOD_MCNS
         if (strcmp_nocase (entry, "MCNS")==0) { return SILABS_MCNS  ;}
#endif /* DEMOD_MCNS */
#ifdef    DEMOD_DVB_S_S2_DSS
         if (strcmp_nocase (entry, "S"   )==0) { return SILABS_DVB_S ;}
    else if (strcmp_nocase (entry, "S2"  )==0) { return SILABS_DVB_S2;}
    else if (strcmp_nocase (entry, "DSS" )==0) { return SILABS_DSS   ;}
#endif /* DEMOD_DVB_S_S2_DSS */
  }
  printf("Invalid standard selection !\n");
  return -1;
}
/************************************************************************************************************************
  Silabs_UserInput_bw_Hz function
  Use:        bw selection function
              Used to have the user enter the DVB-T or DVB-T2 bandwidth as desired
  Returns: the selected bw in Hz
************************************************************************************************************************/
signed   int  Silabs_UserInput_bw_Hz         (CUSTOM_Standard_Enum standard)
{
#ifdef    TERRESTRIAL_FRONT_END
  float bandwidth_MHz;
  int   bandwidth_Hz;
  bandwidth_MHz = 0; /* To avoid compiler warning if not used */
  bandwidth_Hz  = 0; /* To avoid compiler warning if not used */

  switch (standard)
  {
    default             : break;
#ifdef    DEMOD_DVB_T2
    case SILABS_DVB_T2  : {
      Silabs_UserInputString("Bandwidth (in MHz) (1.7, 5, 6, 7 or 8)? ");
      sscanf(userEntry,"%f",&bandwidth_MHz);
      bandwidth_Hz = (int)(bandwidth_MHz*1000000);
      if (bandwidth_Hz == 1700000) return 1700000;
      if (bandwidth_Hz == 5000000) return 5000000;
      break;
    }
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_DVB_T
    case SILABS_DVB_T   : {
      Silabs_UserInputString("Bandwidth (in MHz) (6, 7 or 8)?      ");
      sscanf(userEntry,"%f",&bandwidth_MHz);
      bandwidth_Hz = (int)(bandwidth_MHz*1000000);
      break;
    }
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_ISDB_T
    case SILABS_ISDB_T  : {
      Silabs_UserInputString("Bandwidth (in MHz) (6, 7 or 8)?      ");
      sscanf(userEntry,"%f",&bandwidth_MHz);
      bandwidth_Hz = (int)(bandwidth_MHz*1000000);
      break;
    }
#endif /* DEMOD_ISDB_T */
#ifdef    DEMOD_DVB_C2
    case SILABS_DVB_C2  : {
      Silabs_UserInputString("Bandwidth (in MHz) (6 or 8)?         ");
      sscanf(userEntry,"%f",&bandwidth_MHz);
      bandwidth_Hz = (int)(bandwidth_MHz*1000000);
      break;
    }
#endif /* DEMOD_DVB_C2 */
  }

#ifdef    TERRESTRIAL_FRONT_END
  if (bandwidth_Hz == 6000000) return 6000000;
  if (bandwidth_Hz == 7000000) return 7000000;
  if (bandwidth_Hz == 8000000) return 8000000;
#endif /* TERRESTRIAL_FRONT_END */
  printf("\nSilabs_UserInput_bw_Hz : incorrect BW value! Using 8 MHz...\n");
#endif /* TERRESTRIAL_FRONT_END */
  return 800000;
}
/************************************************************************************************************************
  Silabs_UserInput_SR_bps function
  Use:        user-level symbol rate function
              Used to set the symbol rate
  Behavior:   Asks the user to enter the symbol rate in Mbps, then return the value in bps
************************************************************************************************************************/
signed   long Silabs_UserInput_SR_bps        (void)
{
  float sr;
  long sr_bps;
  printf("Symbol rate (in Msymb/s)? ");
  scanf("%f",&sr);
  sr_bps = (long)(sr*1000000);
  printf("     --> SR in baud %ld \n ",sr_bps);
  return sr_bps;
}
/************************************************************************************************************************
  Silabs_UserInput_TS_rate function
  Use:        user-level TS mode selection function
              Used to set the TS mode
  Behavior:   Asks the user to select a TS mode and then call
************************************************************************************************************************/
signed   long Silabs_UserInput_TS            (void)
{
  char *entry;
#ifdef    USB_Capability
  double retdval;
#endif /* USB_Capability */
  entry = userEntry;
  printf("TS mode (OFF SERIAL PARALLEL TRISTATE ");
#ifdef    USB_Capability
  printf("GPIF SLAVE_FIFO");
#endif /* USB_Capability */
  if ( Silabs_UserInputString(")? ") != 0) {
#ifdef    USB_Capability
        if (strcmp_nocase (entry, "GPIF"    )!=0) {
          if (nb_front_ends ==4) { L0_Cypress_Process("write_io_port", "d", 0x3c, &retdval, &entry); }
        }
#endif /* USB_Capability */
         if (strcmp_nocase (entry, "OFF"     )==0) { return SiLabs_API_TS_Mode (front_end, SILABS_TS_OFF     );}
         if (strcmp_nocase (entry, "SERIAL"  )==0) { return SiLabs_API_TS_Mode (front_end, SILABS_TS_SERIAL  );}
    else if (strcmp_nocase (entry, "PARALLEL")==0) { return SiLabs_API_TS_Mode (front_end, SILABS_TS_PARALLEL);}
    else if (strcmp_nocase (entry, "TRISTATE")==0) { return SiLabs_API_TS_Mode (front_end, SILABS_TS_TRISTATE);}
#ifdef    USB_Capability
    else if (strcmp_nocase (entry, "GPIF0"   )==0) { return SiLabs_API_TS_Mode (front_end, SILABS_TS_GPIF    ); }
    else if (strcmp_nocase (entry, "STREAMING")==0) {return SiLabs_API_TS_Mode (front_end, SILABS_TS_STREAMING); }
    else if (strcmp_nocase (entry, "GPIF"    )==0) {
        if (nb_front_ends == 4) { /* for Dual_Si2191_Si216x2_Si2164 EVB */
          printf("Silabs_UserInput_TS controlling port D for fe %d\n", fe);
          L0_Cypress_Process("output_enable_io_port", "d", 0x3c, &retdval, &entry);
          if (fe == 0) L0_Cypress_Process("write_io_port", "d", 0x38, &retdval, &entry);
          if (fe == 1) L0_Cypress_Process("write_io_port", "d", 0x34, &retdval, &entry);
          if (fe == 2) L0_Cypress_Process("write_io_port", "d", 0x2c, &retdval, &entry);
          if (fe == 3) L0_Cypress_Process("write_io_port", "d", 0x1c, &retdval, &entry);
      }
      return SiLabs_API_TS_Mode (front_end, SILABS_TS_GPIF    );
    }
    else if (strcmp_nocase (entry, "SLAVE_FIFO"   )==0) {
      return SiLabs_API_TS_Mode (front_end, SILABS_TS_SLAVE_FIFO );
    }
#endif /* USB_Capability */
  }
  printf("Invalid TS mode selection !\n");
  return 1;
}
#ifdef    TS_CROSSBAR
/************************************************************************************************************************
  Silabs_UserInputTSCrossbar function
  Use:        user-level TS crossbar control function
              Used to set the TS mode on TS1 or TS2
  Behavior:   Asks the user to select a TS mode and then call the corresponding functions
************************************************************************************************************************/
signed   int  Silabs_UserInputTSCrossbar   (void)
{
  char *entry;
  CUSTOM_TS_Crossbar_Enum  ts_1_signal;
  CUSTOM_TS_Crossbar_Enum  ts_2_signal;
  CUSTOM_TS_Mode_Enum      ts_1_mode;
  CUSTOM_TS_Mode_Enum      ts_2_mode;
  ts_1_signal = 0;
  ts_2_signal = 0;
  ts_1_mode   = 0;
  ts_2_mode   = 0;
  entry = userEntry;

  printf("TS1 signal (A B TRISTATE ");
  if ( Silabs_UserInputString(")? ") != 0) {
         if (strcmp_nocase (entry, "A"       )==0) { ts_1_signal = SILABS_TS_CROSSBAR_TS_A     ;}
    else if (strcmp_nocase (entry, "B"       )==0) { ts_1_signal = SILABS_TS_CROSSBAR_TS_B     ;}
    else if (strcmp_nocase (entry, "TRISTATE")==0) { ts_1_signal = SILABS_TS_CROSSBAR_TRISTATE ;}
    else                                           { printf("Invalid TS signal selection !\n"); return 1; }
  }

  printf("TS1 mode (SERIAL PARALLEL TRISTATE ");
  if ( Silabs_UserInputString(")? ") != 0) {
         if (strcmp_nocase (entry, "SERIAL"  )==0) { ts_1_mode = SILABS_TS_SERIAL  ;}
    else if (strcmp_nocase (entry, "PARALLEL")==0) { ts_1_mode = SILABS_TS_PARALLEL;}
    else if (strcmp_nocase (entry, "TRISTATE")==0) { ts_1_mode = SILABS_TS_TRISTATE;}
    else                                           { printf("Invalid TS1 mode selection !\n"); return 1;                 }
  }

  printf("TS2 signal (A B TRISTATE ");
  if ( Silabs_UserInputString(")? ") != 0) {
         if (strcmp_nocase (entry, "A"       )==0) { ts_2_signal = SILABS_TS_CROSSBAR_TS_A     ;}
    else if (strcmp_nocase (entry, "B"       )==0) { ts_2_signal = SILABS_TS_CROSSBAR_TS_B     ;}
    else if (strcmp_nocase (entry, "TRISTATE")==0) { ts_2_signal = SILABS_TS_CROSSBAR_TRISTATE ;}
    else                                           { printf("Invalid TS signal selection !\n"); return 1; }
  }

  printf("TS2 mode (SERIAL PARALLEL TRISTATE ");
  if ( Silabs_UserInputString(")? ") != 0) {
         if (strcmp_nocase (entry, "SERIAL"  )==0) { ts_2_mode = SILABS_TS_SERIAL  ;}
    else if (strcmp_nocase (entry, "PARALLEL")==0) { ts_2_mode = SILABS_TS_PARALLEL;}
    else if (strcmp_nocase (entry, "TRISTATE")==0) { ts_2_mode = SILABS_TS_TRISTATE;}
    else                                           { printf("Invalid TS2 mode selection !\n"); return 1;                 }
  }

  SiLabs_TS_Crossbar_TS1_TS2 (crossbar, ts_1_signal, ts_1_mode, ts_2_signal, ts_2_mode);

  return 1;
}
#endif /* TS_CROSSBAR */
/************************************************************************************************************************
  Silabs_UserInput_Polarization function
  Use:        user-level lnb polarization input function
              Used to ask the user to enter the lnb polarization
  Behavior:   Asks the user to enter the polarization
  Returns:    The final polarization value
************************************************************************************************************************/
signed   int  Silabs_UserInput_Polarization  (void)
{
  printf("\nSAT polarization <h v> (h = 'Horizontal', v = 'Vertical') ? ");
  while ( Silabs_UserInputString("") == 0) {/* */}
  if (strcmp_nocase(userEntry,"h"  )==0) { SiTRACE("Horizontal\n"); return SILABS_POLARIZATION_HORIZONTAL;}
  if (strcmp_nocase(userEntry,"v"  )==0) { SiTRACE("Vertical  \n"); return SILABS_POLARIZATION_VERTICAL  ;}
  SiTRACE("????\n");
  return SILABS_POLARIZATION_HORIZONTAL;
}
/************************************************************************************************************************
  Silabs_UserInput_Band function
  Use:        user-level lnb band input function
              Used to ask the user to enter the lnb band
  Behavior:   Asks the user to enter the band
  Returns:    The final band value
************************************************************************************************************************/
signed   int  Silabs_UserInput_Band          (void)
{
  printf("\nSAT band         <l h> (l = 'Low', h = 'High')            ? ");
  while ( Silabs_UserInputString("") == 0) {/* */}
  if (strcmp_nocase(userEntry,"l"  )==0) { SiTRACE("LOW\n" ); return SILABS_BAND_LOW; }
  if (strcmp_nocase(userEntry,"h"  )==0) { SiTRACE("HIGH\n"); return SILABS_BAND_HIGH;}
  SiTRACE("????\n");
  return SILABS_BAND_LOW;
}
#ifdef    SATELLITE_FRONT_END
#ifdef    UNICABLE_COMPATIBLE
/************************************************************************************************************************
  Silabs_UserInput_Position function
  Use:        user-level SAT position input function
              Used to ask the user to enter the SAT position (Unicable specific)
  Behavior:   Asks the user to enter the position
  Returns:    The final polarization value
************************************************************************************************************************/
signed   int  Silabs_UserInput_Position      (void)
{
  printf("\nSAT position <A B>? ");
  while ( Silabs_UserInputString("") == 0) {/* */}
  if (strcmp_nocase(userEntry,"a"  )==0) { SiTRACE("Position A\n"); return UNICABLE_POSITION_A;}
  if (strcmp_nocase(userEntry,"b"  )==0) { SiTRACE("Position B\n"); return UNICABLE_POSITION_B;}
  SiTRACE("????\n");
  return UNICABLE_POSITION_A;
}
signed   int  Silabs_UserInput_Harcoded_Tune (void)
{
  int  bank;
  int  T;
  int  freq_kHz;

  /* Ask for the bank value */
  printf("Unicable bank <0 3> ? ");
  while (Silabs_UserInputString("") ==0);
  sscanf(userEntry,"%d",&bank);

  /* Ask for the T value */
  printf("Unicable T          ? ");
  while (Silabs_UserInputString("") ==0);
  sscanf(userEntry,"%d",&T);

  /* Ask for the freq_kHz value */
  printf("Unicable freq_kHz (L band for SAT tuner, +/-Ub center freq)  ? ");
  while (Silabs_UserInputString("") ==0);
  sscanf(userEntry,"%d",&freq_kHz);

  SiLabs_Unicable_API_Hardcoded_Tune(front_end->unicable, bank, T, freq_kHz);

  return 0;
}
signed   int  Silabs_UserInput_Unicable_Config(void)
{
  signed   int unicable_mode;
  signed   int unicable_chunk_inversion;
  unsigned int ub;
  unsigned int Fub_kHz;
  unsigned int LO_kHz_low_band;
  unsigned int LO_kHz_high_band;

  /* Ask for the bank value */
  printf("Unicable mode    <0 1 2>         ? ");
  while (Silabs_UserInputString("") ==0);
  sscanf(userEntry,"%d",&unicable_mode);

  /* Ask for the chunk (whole spectrum) inversion value */
  printf("unicable chunk inversion <0 1>   ? ");
  while (Silabs_UserInputString("") ==0);
  sscanf(userEntry,"%d",&unicable_chunk_inversion);

  /* Ask for the ub number  */
       if (unicable_mode == 1) {
  printf("Unicable UB number   <0 to 7>    ? ");
  }
  else if (unicable_mode == 2) {
  printf("Unicable UB number  <0 to 31>    ? ");
  }
  while (Silabs_UserInputString("") ==0);
  sscanf(userEntry,"%d",&ub);

  /* Ask for the ub center freq */
  printf("unicable UB center    freq (kHz) ? ");
  while (Silabs_UserInputString("") ==0);
  sscanf(userEntry,"%d",&Fub_kHz);

  /* Ask for the low band LO freq */
  printf("unicable low  band LO freq (kHz) ? ");
  while (Silabs_UserInputString("") ==0);
  sscanf(userEntry,"%d",&LO_kHz_low_band);

  /* Ask for the high band LO freq */
  printf("unicable high band LO freq (kHz) ? ");
  while (Silabs_UserInputString("") ==0);
  sscanf(userEntry,"%d",&LO_kHz_high_band);

  return SiLabs_API_SAT_Unicable_Config (front_end, unicable_mode, unicable_chunk_inversion, ub, Fub_kHz, LO_kHz_low_band, LO_kHz_high_band );
}
#endif /* UNICABLE_COMPATIBLE */
/************************************************************************************************************************
  Silabs_UserInput_VoltageTone function
  Use:        user-level lnb fields input function
              Used to ask the user to enter required fields to set the lnb band and polarization
  Behavior:   Asks the user to enter the fields, then call SiLabs_API_SeekInit
  Returns:    The final lock status
************************************************************************************************************************/
signed   int  Silabs_UserInput_VoltageTone   (void)
{
  int  voltage;
  int  i_tone;
  unsigned char tone;

#ifdef    UNICABLE_COMPATIBLE
  if (front_end->unicable->installed == 0) {
#endif /* UNICABLE_COMPATIBLE */
    /* Ask for the voltage value */
    printf("SAT LNB voltage <13 18 0> (13 = 'Vertical', 18 = 'Horizontal', 0 = 'off') ? ");
    while (Silabs_UserInputString("") ==0);
    sscanf(userEntry,"%d",&voltage);

    /* Ask for the tone value */
    printf("SAT LNB tone    <0 1>     ( 0 = 'Low', 1 = 'High') ? ");
    while (Silabs_UserInputString("") ==0);
    sscanf(userEntry,"%d",&i_tone);

    if (i_tone) {tone = 1;} else {tone = 0;}

    switch (voltage) {
      case 13: front_end->polarization = SILABS_POLARIZATION_VERTICAL   ; break;
      case 18: front_end->polarization = SILABS_POLARIZATION_HORIZONTAL ; break;
      default: front_end->polarization = SILABS_POLARIZATION_HORIZONTAL ; break;
    }

    switch (tone   ) {
      case  1: front_end->band = SILABS_BAND_HIGH ; break;
      default: front_end->band = SILABS_BAND_LOW  ; break;
    }

#ifdef    UNICABLE_COMPATIBLE
  } else {
    front_end->unicable->satellite_position = Silabs_UserInput_Position();
    if (Silabs_UserInput_Polarization() == SILABS_POLARIZATION_VERTICAL) {
      front_end->unicable->polarization = UNICABLE_VERTICAL;
      front_end->polarization = SILABS_POLARIZATION_VERTICAL;
    } else {
      front_end->unicable->polarization = UNICABLE_HORIZONTAL;
      front_end->polarization = SILABS_POLARIZATION_HORIZONTAL;
    }
    if (Silabs_UserInput_Band()         == SILABS_BAND_LOW) {
      front_end->unicable->band         = UNICABLE_LOW_BAND;
      front_end->band                   = SILABS_BAND_LOW;
    } else {
      front_end->unicable->band         = UNICABLE_HIGH_BAND;
      front_end->band                   = SILABS_BAND_HIGH;
    }
    front_end->unicable->bank = front_end->unicable->satellite_position*4 + front_end->unicable->polarization*2 + front_end->unicable->band;
    return 1;
  }

#endif /* UNICABLE_COMPATIBLE */

  return  SiLabs_API_SAT_voltage_and_tone (front_end, voltage, tone);
}
#endif /* SATELLITE_FRONT_END */
/************************************************************************************************************************
  Silabs_UserInput_lock function
  Use:        user-level lock fields input function
              Used to ask the user to enter required fields to lock on a carrier, depending on the standard
  Behavior:   Asks the user to enter the fields, then call SiLabs_API_lock_to_carrier
  Returns:    The final lock status
************************************************************************************************************************/
signed   int  Silabs_UserInput_Lock          (void)
{
  int                  lock;
  int                  freq;
  int                  bandwidth_Hz;
  unsigned int         symbol_rate_bps;
  CUSTOM_Constel_Enum  constellation;
  CUSTOM_Stream_Enum   stream;
  int                  standard;
  int                  polarization;
  int                  band;
  int                  data_slice_id;
  int                  plp_id;
  int                  isi_id;
  int                  T2_lock_mode;
  polarization = band = T2_lock_mode = 0;

  standard = Silabs_UserInput_standard();
  if (standard < 0 ) return 0;

  /* Ask for the frequency for all standards */
  freq = Silabs_UserInput_tune (standard);

  /* Ask for the bandwidth for DVB-T, DVB-T2, ISDB-T and DVB-C2 */
  switch (standard) {
    case SILABS_DVB_T  :
    case SILABS_DVB_T2 :
    case SILABS_DVB_C2 :
    case SILABS_ISDB_T : { bandwidth_Hz    =  Silabs_UserInput_bw_Hz(standard); break; }
    default:             { bandwidth_Hz    =  0; break; }
  }
  /* Ask for the Stream for DVB-T */
  switch (standard) {
    case SILABS_DVB_T  : { stream          = Silabs_UserInput_stream()        ; break; }
    default:             { stream          = 0                                ; break; }
  }
  /* Ask for the DATA SLICE ID for DVB-C2 */
  switch (standard) {
    case SILABS_DVB_C2 : { data_slice_id   =  Silabs_UserInput_data_slice_id()       ; break; }
    default:             { data_slice_id   =  0; break; }
  }
  /* Ask for the IS ID for DVB-S2 (uisng plp_id as for T2 or C2 to keep the same interface) */
  switch (standard) {
    case SILABS_DVB_S2 : { isi_id   =  Silabs_UserInput_isi_id()   ; break; }
    default:             { isi_id   =  0; break; }
  }
  /* Ask for the PLP ID for DVB-T2/C2 */
  switch (standard) {
    case SILABS_DVB_C2 : { if (data_slice_id == -1) {
                           plp_id = -1;
                          } else {
                           plp_id   =  Silabs_UserInput_plp_id() ;}
                          break; }
    case SILABS_DVB_T2 : { plp_id   =  Silabs_UserInput_plp_id() ; break;   }
    case SILABS_DVB_S2 : { plp_id   =  isi_id ; break;   }
    default:             { plp_id   =  0; break; }
  }
#ifdef    TERRESTRIAL_FRONT_END
  /* Ask for the T2 lock mode for DVB-T2, only if the demod driver supports T2_lock_mode */
  T2_lock_mode   =  SiLabs_API_TER_T2_lock_mode(front_end, 100);
  switch (standard) {
    case SILABS_DVB_T2 : {
      if (T2_lock_mode != -1) {
        T2_lock_mode   =  Silabs_UserInput_T2_lock_mode();
      }
      break;
    }
    default:             { break; }
  }
#endif /* TERRESTRIAL_FRONT_END */
  /* Ask for the symbol rate for DVB-C and all SAT standards*/
  switch (standard) {
    case SILABS_DVB_C  :
    case SILABS_MCNS   :
    case SILABS_DVB_S  :
    case SILABS_DVB_S2 :
    case SILABS_DSS    : { symbol_rate_bps = Silabs_UserInput_SR_bps()        ; break; }
    default:             { symbol_rate_bps = 0                                ; break; }
  }
  /* Ask for the constellation for DVB-C and DVB-S2 */
  switch (standard) {
    case SILABS_DVB_C  : { constellation   = Silabs_UserInput_qam(standard)   ; break; }
    case SILABS_MCNS   : { constellation   = Silabs_UserInput_qam(standard)   ; break; }
    default:             { constellation   = 0                                ; break; }
  }
#ifdef    SATELLITE_FRONT_END
  /* Ask for the polarization and band for SAT */
  switch (standard) {
    case SILABS_DSS    :
    case SILABS_DVB_S  :
    case SILABS_DVB_S2 : {
      Silabs_UserInput_VoltageTone();
      polarization    = front_end->polarization;
      band            = front_end->band;
    }
    default:             { break; }
  }
#endif /* SATELLITE_FRONT_END */

  /* Call SiLabs_API_switch_to_standard, in case the standard is different or the init has not been done yet */
  if (SiLabs_API_switch_to_standard      (front_end, standard, 0) ==0) return 0;

  last_standard        = standard;
  last_freq            = freq;
  last_bandwidth_Hz    = bandwidth_Hz;
  last_stream          = stream;
  last_symbol_rate_bps = symbol_rate_bps;
  last_constellation   = constellation;
  last_polarization    = polarization;
  last_band            = band;
  last_data_slice_id   = data_slice_id;
  last_plp_id          = plp_id;
#ifdef    TERRESTRIAL_FRONT_END
  last_T2_base_lite    = T2_lock_mode;
#endif /* TERRESTRIAL_FRONT_END */
  /* Call SiLabs_API_lock_to_carrier with the fields entered by the user */
  lock = 2;

  while (lock > 1) {
   lock = SiLabs_API_lock_to_carrier (front_end, standard, freq, bandwidth_Hz, stream, symbol_rate_bps, constellation, polarization, band, data_slice_id, plp_id, T2_lock_mode);
   if (lock > 1) {printf("Console Lock: Handshaking after %6d ms\n", lock);}
  }

  return lock;
}
/************************************************************************************************************************
  Silabs_UserInput_SeekInit function
  Use:        user-level seek fields input function
              Used to ask the user to enter required fields to seek for carriers, depending on the standard
  Behavior:   Asks the user to enter the fields, then call SiLabs_API_SeekInit
  Returns:    The final lock status
************************************************************************************************************************/
signed   int  Silabs_UserInput_SeekInit      (void)
{
  unsigned long rangeMin;
  unsigned long rangeMax;
  int           seekBWHz;
  int           seekStepHz;
  int           minSRbps;
  int           maxSRbps;
  int           minRSSIdBm;
  int           maxRSSIdBm;
  int           minSNRHalfdB;
  int           maxSNRHalfdB;
#ifdef    TERRESTRIAL_FRONT_END
  int           T2_lock_mode;
#endif /* TERRESTRIAL_FRONT_END */
  CUSTOM_Standard_Enum standard;

  standard = front_end->standard;

  /* Ask for the Start frequency for all standards */
  printf("standard %d %s \n", standard , Silabs_Standard_Text(standard) );
  printf("Seek Start ");
  rangeMin = Silabs_UserInput_tune(standard);

  /* Ask for the Stop  frequency for all standards */
  printf("Seek Stop  ");
  rangeMax = Silabs_UserInput_tune(standard);

  /* Ask for the bandwidth for DVB-T, DVB-T2, DVB-C2 and ISDB-T */
  switch (standard) {
    case SILABS_DVB_T  :
    case SILABS_DVB_T2 :
    case SILABS_DVB_C2 :
    case SILABS_ISDB_T : { seekBWHz = Silabs_UserInput_bw_Hz(standard); break; }
    default:             { seekBWHz = 8000000 ; break; }
  }

  /* Ask for the step      for DVB-T, DVB-T2, ISDB-T and DVB-C2 */
  switch (standard) {
    case SILABS_DVB_T  :
    case SILABS_DVB_T2 :
    case SILABS_DVB_C2 :
    case SILABS_ISDB_T : { Silabs_UserInputString("Seek Step (in Hz)?                   "); sscanf(userEntry,"%d",&seekStepHz); break; }
    default:             { seekStepHz = 8000000                         ; break; }
  }

  /* Ask for the MIN symbol rate for DVB-C/MCNS and all SAT standards*/
  switch (standard) {
    case SILABS_DVB_C  :
    case SILABS_MCNS   :
    case SILABS_DVB_S  :
    case SILABS_DVB_S2 :
    case SILABS_DSS    : { printf("Min "); minSRbps = Silabs_UserInput_SR_bps(); break; }
    default:             { minSRbps= 0                        ; break; }
  }

  /* Ask for the MAX symbol rate for DVB-C/MCNS and all SAT standards*/
  switch (standard) {
    case SILABS_DVB_C  :
    case SILABS_MCNS   :
    case SILABS_DVB_S  :
    case SILABS_DVB_S2 :
    case SILABS_DSS    : { printf("Max "); maxSRbps = Silabs_UserInput_SR_bps(); break; }
    default:             { maxSRbps= 0                        ; break; }
  }

#ifdef    TERRESTRIAL_FRONT_END
  /* Ask for the T2 lock mode for DVB-T2 */
  switch (standard) {
    case SILABS_DVB_T  :
    case SILABS_DVB_T2 : {
      if (SiLabs_API_TER_T2_lock_mode(front_end,100) != -1) {
        T2_lock_mode   =       Silabs_UserInput_T2_lock_mode();
        SiLabs_API_TER_T2_lock_mode (front_end, T2_lock_mode);
      }
      break;
    }
    default:             { break; }
  }
#endif /* TERRESTRIAL_FRONT_END */

#ifdef    SATELLITE_FRONT_END
  /* Set Polarization and Band for all SAT standards*/
  switch (standard) {
    case SILABS_DVB_S  :
    case SILABS_DVB_S2 :
    case SILABS_DSS    : { Silabs_UserInput_VoltageTone(); break; }
    default:             {                                 break; }
  }
#endif /* SATELLITE_FRONT_END */

  if (front_end->chip == 9999) {
    Silabs_UserInputString("minRSSI (in dBm)? ");
    sscanf(userEntry,"%d",&minRSSIdBm);

    Silabs_UserInputString("maxRSSI (in dBm)? ");
    sscanf(userEntry,"%d",&maxRSSIdBm);

    Silabs_UserInputString("minSNR  (in dB)? ");
    sscanf(userEntry,"%d",&minSNRHalfdB);
    minSNRHalfdB = minSNRHalfdB*2;

    Silabs_UserInputString("maxSNR  (in dB)? ");
    sscanf(userEntry,"%d",&maxSNRHalfdB);
    maxSNRHalfdB = maxSNRHalfdB*2;
  } else {
    minRSSIdBm   = 0;
    maxRSSIdBm   = 0;
    minSNRHalfdB = 0;
    maxSNRHalfdB = 0;
  }
  return  SiLabs_API_Channel_Seek_Init    (front_end, rangeMin, rangeMax, seekBWHz, seekStepHz, minSRbps, maxSRbps, minRSSIdBm, maxRSSIdBm, minSNRHalfdB, maxSNRHalfdB);
}
/************************************************************************************************************************
  Silabs_UserInput_SeekNext   function
  Use:        user-level seek function
              Used to seek for carriers, depending on the standard
  Behavior:   Asks the user to enter the fields, then call SiLabs_API_SeekInit
  Returns:    The final lock status
************************************************************************************************************************/
signed   int  Silabs_UserInput_SeekNext      (void)
{
  int lock;
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
  int carrier_index;
#ifdef    DEMOD_DVB_T
  int hierarchy;
#endif /* DEMOD_DVB_T */
  int data_slice_id;
  int plp_id;
  int plp_type;
  int T2_base_lite;
  int T2_mode;
  int i;
#ifdef    DEMOD_DVB_C2
  int d;
#endif /* DEMOD_DVB_C2 */
#ifdef    DEMOD_DVB_T
  hierarchy     = 0;     /* To avoid compiler warning if not used */
#endif /* DEMOD_DVB_T */
  data_slice_id = 0;     /* To avoid compiler warning if not used */
  plp_id        = 0;     /* To avoid compiler warning if not used */
  plp_type      = 0;     /* To avoid compiler warning if not used */
  T2_base_lite  = 0;     /* To avoid compiler warning if not used */
  T2_mode       = 0;     /* To avoid compiler warning if not used */
  standard = i = plp_type = plp_id = T2_mode = 0;

  lock = SiLabs_API_Channel_Seek_Next(front_end, &standard, &freq,  &bandwidth_Hz, &stream, &symbol_rate_bps, &constellation, &polarization, &band, &num_data_slice, &num_plp, &T2_base_lite);

  if (lock==1) {
    SiTRACE("standard %d, freq %d, bandwidth_Hz %d, stream %d, symbol_rate_bps %d, constellation %d, polarization %d, band %d, num_data_slice %d, num_plp %d, T2_base_lite %d\n", standard, freq, bandwidth_Hz, stream, symbol_rate_bps, constellation, polarization, band, num_data_slice, num_plp, T2_base_lite);
    /* Once locked, turn TS active */
    SiLabs_API_TS_Mode(front_end, front_end->active_TS_mode);
#ifdef    SATELLITE_FRONT_END

#ifdef    UNICABLE_COMPATIBLE
    SiLabs_Unicable_API_Tune_Infos(front_end->unicable, messageBuffer);
#endif /* UNICABLE_COMPATIBLE */
#endif /* SATELLITE_FRONT_END */
    SiLabs_API_FE_status          (front_end, custom_status);
    SiLabs_API_Text_status        (front_end, custom_status, messageBuffer);
#ifdef    DEMOD_DVB_T
    if (standard == SILABS_DVB_T) {
      /* Storing one channel for the current hierarchy (HP,LP) */
      carrier_index = SiLabs_Scan_Check_And_Add_Carrier (front_end, standard, freq, bandwidth_Hz, stream, symbol_rate_bps, constellation, polarization, band, data_slice_id, plp_id, T2_base_lite);
      SiLabs_API_Get_DVBT_Hierarchy (front_end, &hierarchy);
      /* If in hierarchical T, lock on the other stream and store the corresponding channel */
      if (hierarchy != SILABS_HIERARCHY_NONE) {
        /* Turn TS tristate during the lock on the second stream (HP/LP) */
        SiLabs_API_TS_Mode(front_end, SILABS_TS_TRISTATE);
        if (stream == SILABS_HP) { stream = SILABS_LP; } else { stream = SILABS_HP; }
        /* wait for lock on second stream */
        lock = 2;
        while (lock > 1) {
          lock = SiLabs_API_lock_to_carrier (front_end, standard, freq, bandwidth_Hz, stream, symbol_rate_bps, constellation, polarization, band, data_slice_id, plp_id, T2_base_lite);
          if (lock >  1) {printf("Console Lock: Handshaking after %6d ms\n", lock);}
          if (lock == 1) {
            /* Once locked, turn TS active */
            SiLabs_API_TS_Mode(front_end, front_end->active_TS_mode);
            /* Check signal quality and store this channel */
            carrier_index = SiLabs_Scan_Check_And_Add_Carrier (front_end, standard, freq, bandwidth_Hz, stream, symbol_rate_bps, constellation, polarization, band, data_slice_id, plp_id, T2_base_lite);
          }
        }
        /* Turn TS tristate for the next call to SeekNext */
        SiLabs_API_TS_Mode(front_end, SILABS_TS_TRISTATE);
      }
      return 1;
    }
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_DVB_C2
    if (standard == SILABS_DVB_C2) {
      if (num_data_slice > 0) {
#ifdef    Si2183_COMPATIBLE
  if (front_end->chip ==   0x2183 ) { SiTRACE("DVB-C2 locked on Network_Id %3d, C2_System_Id %d, start_frequency %ld\n", front_end->Si2183_FE->demod->rsp->dvbc2_sys_info.network_id, front_end->Si2183_FE->demod->rsp->dvbc2_sys_info.c2_system_id, front_end->Si2183_FE->demod->rsp->dvbc2_sys_info.start_frequency_hz ); }
#endif /* Si2183_COMPATIBLE */
        /* Storing one channel per 'DATA' PLP_ID in each Data Slice (DVB-T2/C2) */
        for (d = 0; d<num_data_slice; d++) {
           /* Retrieving freq and num_plp for current Data Slice         */
          SiLabs_API_Get_DS_ID_Num_PLP_Freq (front_end, d, &data_slice_id, &num_plp, &freq);
           /* Retrieving plp_id for first DATA plp in current Data Slice */
          for (i=0; i<num_plp; i++) {
            SiLabs_API_Get_PLP_ID_and_TYPE   (front_end, d, i, &plp_id, &plp_type);
            /* Skipping COMMON PLPs */
            if (plp_type != SILABS_PLP_TYPE_COMMON) { break; }
          }
          SiTRACE("Silabs_UserInput_SeekNext DVB-C2 data_slice_id %d at %10d Hz: num_plp %d, first data plp_id %d, plp_type %s\n", data_slice_id, freq, num_plp, plp_id, Silabs_PLPType_Text(plp_type));
           /* Locking on 'freq' for current Data Slice on first DATA plp   */
          lock = SiLabs_API_lock_to_carrier (front_end, standard, freq, bandwidth_Hz, stream, symbol_rate_bps, constellation, polarization, band, data_slice_id, plp_id, T2_mode);
          if (lock) {
            if (num_plp > 0) {
              /* DVB-C2 multiple plp case */
              for (i=0; i<num_plp; i++) {
                /* Retrieving plp_id and plp_type, to select and store only DATA plps */
                SiLabs_API_Get_PLP_ID_and_TYPE   (front_end, d, i, &plp_id, &plp_type);
                /* Only logging non-COMMON (i.e. DATA) PLPs */
                if (plp_type != SILABS_PLP_TYPE_COMMON) {
                  SiLabs_API_Select_PLP(front_end, plp_id);
                  /* Storing one carrier per DATA PLP, browse SPI/PSI information using SoC */
                  carrier_index = SiLabs_Scan_Check_And_Add_Carrier (front_end, standard, freq, bandwidth_Hz, stream, symbol_rate_bps, constellation, polarization, band, data_slice_id, plp_id, T2_base_lite);
                  SiLabs_Scan_Table_Carrier_Text(carrier_index, messageBuffer); printf("%s\n", messageBuffer);
                }
              }
            } else {
              /* DVB-C2 single plp case (already locked on the single PLP) */
              /* Storing one carrier for the single PLP */
              carrier_index = SiLabs_Scan_Check_And_Add_Carrier (front_end, standard, freq, bandwidth_Hz, stream, symbol_rate_bps, constellation, polarization, band, data_slice_id, plp_id, T2_base_lite);
              SiLabs_Scan_Table_Carrier_Text(carrier_index, messageBuffer); printf("%s\n", messageBuffer);
            }
          } else {
            SiTRACE("ERROR locking on DVB-C2 at %10d data slice id %3d plp_id %3d. The C2 system info seems incorrect.\n", freq, data_slice_id, plp_id);
            SiERROR("ERROR locking on DVB-C2 Data Slice. The C2 system info seems incorrect.\n");
          }
        }
        return lock;
      }
    }
#endif /* DEMOD_DVB_C2 */
#ifdef    DEMOD_DVB_T2
    if (standard == SILABS_DVB_T2) {
      if (num_plp > 1) {
        /* Storing one channel per 'DATA' PLP_ID in MPLP (DVB-T2/C2) */
        printf ("NUM PLP %d\n", num_plp);
        for (i=0; i<num_plp; i++) {
          SiLabs_API_Get_PLP_ID_and_TYPE   (front_end, 0, i, &plp_id, &plp_type);
          if (plp_id == -1) {
            printf ("ERROR retrieving PLP info for plp index %d\n", i);
            SiERROR("ERROR retrieving PLP info\n");
          } else {
            if (plp_type != SILABS_PLP_TYPE_COMMON) {
              SiLabs_API_Select_PLP(front_end, plp_id);
              carrier_index = SiLabs_Scan_Check_And_Add_Carrier (front_end, standard, freq, bandwidth_Hz, stream, symbol_rate_bps, constellation, polarization, band, data_slice_id, plp_id, T2_base_lite);
              SiLabs_API_TS_Mode(front_end, SILABS_TS_TRISTATE);
            }
          }
        }
      } else {
        carrier_index = SiLabs_Scan_Check_And_Add_Carrier (front_end, standard, freq, bandwidth_Hz, stream, symbol_rate_bps, constellation, polarization, band, data_slice_id, plp_id, T2_base_lite);
        SiLabs_API_TS_Mode(front_end, SILABS_TS_TRISTATE);
      }
      if ( (custom_status->t2_version >= SILABS_T2_VERSION_1_3_1) & (custom_status->fef == 1) ) {
        /* Turn TS tristate during the lock on the second stream (T2-base/T2-lite) */
        SiLabs_API_TS_Mode(front_end, SILABS_TS_TRISTATE);
        if (T2_base_lite == 1) {T2_mode = 2;} else {T2_mode = 1;}
        /* wait for lock on second stream */
        lock = 2;
        plp_id = -1; /* set plp mode to 'auto' for the second lock */
        while (lock > 1) {
          lock = SiLabs_API_lock_to_carrier (front_end, standard, freq, bandwidth_Hz, stream, symbol_rate_bps, constellation, polarization, band, data_slice_id, plp_id, T2_mode);
          if (lock >  1) {printf("Console Lock: Handshaking after %6d ms\n", lock);}
          if (lock == 1) {
            SiLabs_API_FE_status          (front_end, custom_status);
            /* Once locked, turn TS active */
            SiLabs_API_TS_Mode(front_end, front_end->active_TS_mode);
            num_plp = custom_status->num_plp;
            if (num_plp > 1) {
              /* Storing one channel per 'DATA' PLP_ID in MPLP (DVB-T2/C2) */
              printf ("NUM PLP %d\n", num_plp);
              for (i=0; i<num_plp; i++) {
                SiLabs_API_Get_PLP_ID_and_TYPE   (front_end, 0, i, &plp_id, &plp_type);
                if (plp_id == -1) {
                  printf ("ERROR retrieving PLP info for plp index %d\n", i);
                  SiERROR("ERROR retrieving PLP info\n");
                } else {
                  if (plp_type != SILABS_PLP_TYPE_COMMON) {
                    SiLabs_API_Select_PLP(front_end, plp_id);
                    carrier_index = SiLabs_Scan_Check_And_Add_Carrier (front_end, standard, freq, bandwidth_Hz, stream, symbol_rate_bps, constellation, polarization, band, data_slice_id, plp_id, T2_mode);
                    SiLabs_API_TS_Mode(front_end, SILABS_TS_TRISTATE);
                  }
                }
              }
            } else {
              carrier_index = SiLabs_Scan_Check_And_Add_Carrier (front_end, standard, freq, bandwidth_Hz, stream, symbol_rate_bps, constellation, polarization, band, data_slice_id, plp_id, T2_mode);
              SiLabs_API_TS_Mode(front_end, SILABS_TS_TRISTATE);
            }
          }
        }
      }
      SiLabs_API_Select_PLP      (front_end,-1);
      SiLabs_API_TER_T2_lock_mode(front_end, 0);
      return 1;
    }
#endif /* DEMOD_DVB_T2 */
    /* For all standards not treated as particular cases */
    carrier_index = SiLabs_Scan_Check_And_Add_Carrier (front_end, standard, freq, bandwidth_Hz, stream, symbol_rate_bps, constellation, polarization, band, data_slice_id, -1, T2_base_lite);
    SiLabs_Scan_Table_Carrier_Text(carrier_index, messageBuffer); printf("%s\n", messageBuffer);
  }
  else
  {
    if (lock >  1) {
      printf("Console SeekNext: Handshaking after %6d ms. freq %10d\n", lock, freq);
      return lock;
    }
    if (lock == 0) {
      printf("\n   Seek complete  now call SeekEnd to finish properly the scan\n");
    }
  }
  return lock;
}
/************************************************************************************************************************
  Silabs_UserInput_chip function
  Use:        bw selection function
              Used to have the user enter the DVB-T or DVB-T2 bandwidth as desired
  Returns: the selected bw in Hz
************************************************************************************************************************/
signed   int  Silabs_UserInput_demod         (void)
{
  int id;
  sprintf(messageBuffer, " ");
#ifdef    Si2183_COMPATIBLE
  sprintf(messageBuffer, "%s 2183 (for Si2183/82/81/80/69C/68C/67C/66C/65E/64B/63E/62B/60B) ", messageBuffer);
  id = 0x2183;
#endif /* Si2183_COMPATIBLE */

  if (strlen(messageBuffer) > 2) {
    printf("Please select the demodulator in the list below...\n");
    Silabs_UserInputString(messageBuffer);
#ifdef    Si2183_COMPATIBLE
    if (strcmp_nocase(userEntry, "2183"   ) == 0) {id = 0x2183;}
#endif /* Si2183_COMPATIBLE */
  }
  return id;
}
signed   int  Silabs_UserInput_SPI_Setup     (void) {
  clk_pin = clk_pola = data_pin = data_order = 0;
  Silabs_UserInputString("SPI send_option ? (0 if not used)    0x");
  sscanf(userEntry,"%x",&send_option);
  if (send_option != 0) {
    Silabs_UserInputString("SPI clk_pin     ? (check in demod API) ");
    sscanf(userEntry,"%x",&clk_pin);
    Silabs_UserInputString("SPI clk_pola    ? (check in demod API) ");
    sscanf(userEntry,"%x",&clk_pola);
    Silabs_UserInputString("SPI data_pin    ? (check in demod API) ");
    sscanf(userEntry,"%x",&data_pin);
    Silabs_UserInputString("SPI data_order  ? (check in demod API) ");
    sscanf(userEntry,"%x",&data_order);
  }
  SiLabs_API_SPI_Setup (front_end, send_option, clk_pin, clk_pola, data_pin, data_order);
  return 0;
}
#ifdef    USB_Capability
signed   int  Silabs_UserInput_Cypress_Ports (void) {
  Silabs_UserInputString("Cypress Port A output enable (OEA)  ? 0x");
  sscanf(userEntry,"%x",&OEA);
  Silabs_UserInputString("Cypress Port A output value  (IOA)  ? 0x");
  sscanf(userEntry,"%x",&IOA);
  Silabs_UserInputString("Cypress Port B output enable (OEB)  ? 0x");
  sscanf(userEntry,"%x",&OEB);
  Silabs_UserInputString("Cypress Port B output value  (IOB)  ? 0x");
  sscanf(userEntry,"%x",&IOB);
  Silabs_UserInputString("Cypress Port D output enable (OED)  ? 0x");
  sscanf(userEntry,"%x",&OED);
  Silabs_UserInputString("Cypress Port D output value  (IOD)  ? 0x");
  sscanf(userEntry,"%x",&IOD);
  SiLabs_API_Cypress_Ports (front_end, OEA, IOA, OEB, IOB, OED, IOD);
  return 0;
}
#endif /* USB_Capability */
/* TER Console Configuration functions */
#ifdef    TERRESTRIAL_FRONT_END
signed   int  Silabs_UserInput_Select_TER_Tuner         (void) {
#ifdef    SILABS_TER_TUNER_API
    ter_tuner_index = 0;
    SiLabs_API_TER_Possible_Tuners(front_end, messageBuffer);
    printf ("\nPossible TER tuners: %s.\n", messageBuffer);
    Silabs_UserInputString("TER tuner selection? Si");
    sscanf(userEntry,"%x",&ter_tuner_code);
    SiLabs_API_Select_TER_Tuner (front_end, ter_tuner_code, ter_tuner_index);
#endif /* SILABS_TER_TUNER_API */
  return 0;
}
signed   int  Silabs_UserInput_TER_Address              (void) {
  Silabs_UserInputString("TER tuner i2c address ? 0x");
  sscanf(userEntry,"%x",&ter_tuner_address);
  return SiLabs_API_TER_Address (front_end, ter_tuner_address);
}
signed   int  Silabs_UserInput_TER_tuner_I2C_connection (void) {
  printf("Front End %d. ", fe);
  Silabs_UserInputString("TER tuner i2c connection via which front_end? ");
  sscanf(userEntry,"%d",&fe_index);
  SiLabs_API_TER_tuner_I2C_connection (front_end, fe_index);
  return 0;
}
signed   int  Silabs_UserInput_TER_Clock                (void) {
  if (SiLabs_API_TER_Clock_Options(front_end, messageBuffer)!=0) {
    printf ("Possible TER Clock options: %s", messageBuffer);
    Silabs_UserInputString("TER Clock source? "); sscanf(userEntry,"%d",&clock_source);
    Silabs_UserInputString("TER Clock input?  "); sscanf(userEntry,"%d",&clock_input);
    Silabs_UserInputString("TER Clock freq?   "); sscanf(userEntry,"%d",&clock_freq);
    Silabs_UserInputString("TER Clock control?"); sscanf(userEntry,"%d",&clock_control);
    SiLabs_API_TER_Clock        (front_end, clock_source, clock_input, clock_freq, clock_control );
    return 1;
  }
  return 0;
}
signed   int  Silabs_UserInput_TER_Tuner_ClockConfig    (void) {
  Silabs_UserInputString("TER Tuner driving   a XTAL  (0/1) ? "); sscanf(userEntry,"%d",&xtal);
  Silabs_UserInputString("TER Tuner providing a clock (0/1) ? "); sscanf(userEntry,"%d",&xout);
  SiLabs_API_TER_Tuner_ClockConfig (front_end, xtal, xout);
  return 1;
}
signed   int  Silabs_UserInput_TER_AGC                  (void) {
  if (SiLabs_API_TER_AGC_Options(front_end, messageBuffer) != 0) {
    printf ("Possible TER AGC_Options: %s", messageBuffer);
    Silabs_UserInputString("TER AGC 1 mode      ? 0x"); sscanf(userEntry,"%x",&agc1_mode);
    Silabs_UserInputString("TER AGC 1 inversion ? ");   sscanf(userEntry,"%d",&agc1_inversion);
    Silabs_UserInputString("TER AGC 2 mode      ? 0x"); sscanf(userEntry,"%x",&agc2_mode);
    Silabs_UserInputString("TER AGC 2 inversion ? ");   sscanf(userEntry,"%d",&agc2_inversion);
    SiLabs_API_TER_AGC          (front_end, agc1_mode, agc1_inversion, agc2_mode, agc2_inversion);
    return 1;
  }
  return 0;
}
signed   int  Silabs_UserInput_TER_Tuner_AGC_Input      (void) {
  printf ("Possible TER Tuner AGC input: Check TER Tuner API DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE values\n");
  Silabs_UserInputString("TER Tuner AGC input ? "); sscanf(userEntry,"%d",&dtv_agc_source);
  SiLabs_API_TER_Tuner_AGC_Input(front_end, dtv_agc_source);
  return 1;
}
signed   int  Silabs_UserInput_TER_Tuner_IF_Output      (void) {
  printf ("Possible TER Tuner IF Output: Check TER Tuner API DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE values\n");
  Silabs_UserInputString("TER Tuner IF output ? "); sscanf(userEntry,"%d",&dtv_out_type);
  SiLabs_API_TER_Tuner_IF_Output (front_end, dtv_out_type);
  return 1;
}
signed   int  Silabs_UserInput_TER_FEF_Config           (void) {
#ifdef    DEMOD_DVB_T2
    if (SiLabs_API_TER_FEF_Options(front_end, messageBuffer) != 0) {
      printf ("Possible TER FEF_Options: %s", messageBuffer);
      Silabs_UserInputString("TER FEF mode      ?   "); sscanf(userEntry,"%d",&fef_mode);
      Silabs_UserInputString("TER FEF pin       ? 0x"); sscanf(userEntry,"%x",&fef_pin);
      Silabs_UserInputString("TER FEF level     ?   "); sscanf(userEntry,"%d",&fef_level);
      SiLabs_API_TER_FEF_Config   (front_end, fef_mode, fef_pin, fef_level );
      return 1;
    }
#endif /* DEMOD_DVB_T2 */
  return 0;
}
#endif /* TERRESTRIAL_FRONT_END */
/* SAT Console Configuration functions */
#ifdef    SATELLITE_FRONT_END
signed   int  Silabs_UserInput_Select_SAT_Tuner         (void) {
#ifdef    SILABS_SAT_TUNER_API
    sat_tuner_index = 0;
    SiLabs_API_SAT_Possible_Tuners(front_end, messageBuffer);
    printf ("\nPossible SAT tuners: %s.\n", messageBuffer);
    Silabs_UserInputString("SAT tuner selection? ");
    sscanf(userEntry,"%x",&sat_tuner_code);
    SiLabs_API_Select_SAT_Tuner (front_end, sat_tuner_code, sat_tuner_index);
#endif /* SILABS_SAT_TUNER_API */
  return 0;
}
signed   int  Silabs_UserInput_SAT_Tuner_Sub            (void) {
#ifdef    SILABS_SAT_TUNER_API
    sat_tuner_sub = 0;
    Silabs_UserInputString("SAT tuner sub? (0/1) ");
    sscanf(userEntry,"%x",&sat_tuner_sub);
    SiLabs_API_SAT_Tuner_Sub (front_end, sat_tuner_sub);
#endif /* SILABS_SAT_TUNER_API */
  return 0;
}
signed   int  Silabs_UserInput_SAT_Address              (void) {
  Silabs_UserInputString("SAT tuner i2c address ? 0x");
  sscanf(userEntry,"%x",&sat_tuner_address);
  return SiLabs_API_SAT_Address (front_end, sat_tuner_address);
}
signed   int  Silabs_UserInput_SAT_Select_LNB_Chip      (void) {
    SiLabs_API_SAT_Possible_LNB_Chips(front_end, messageBuffer);
    printf ("\nPossible LNB controllers: %s.\n", messageBuffer);
    Silabs_UserInputString("LNB controller selection? LNBH");
    sscanf(userEntry,"%d",&lnb_code);
    printf("LNB controller address?"); Silabs_UserInputString(" 0x");
    sscanf(userEntry,"%x",&lnb_chip_address);
    SiLabs_API_SAT_Select_LNB_Chip(front_end, lnb_code, lnb_chip_address);
  return 0;
}
signed   int  SiLabs_UserInput_SAT_LNB_Chip_Index       (void) {
    Silabs_UserInputString("LNB index? (0/1) ");
    sscanf(userEntry,"%d",&lnb_index);
    SiLabs_API_SAT_LNB_Chip_Index(front_end, lnb_index);
  return 0;
}
signed   int  Silabs_UserInput_SAT_tuner_I2C_connection (void) {
  printf("Front End %d. ", fe);
  Silabs_UserInputString("SAT tuner i2c connection via which front_end? ");
  sscanf(userEntry,"%d",&fe_index);
  SiLabs_API_SAT_tuner_I2C_connection (front_end, fe_index);
  return 0;
}
signed   int  Silabs_UserInput_SAT_Clock                (void) {
  if (SiLabs_API_SAT_Clock_Options(front_end, messageBuffer)!=0) {
    printf ("Possible SAT Clock options: %s", messageBuffer);
    Silabs_UserInputString("SAT Clock source? "); sscanf(userEntry,"%d",&clock_source);
    Silabs_UserInputString("SAT Clock input?  "); sscanf(userEntry,"%d",&clock_input);
    Silabs_UserInputString("SAT Clock freq?   "); sscanf(userEntry,"%d",&clock_freq);
    Silabs_UserInputString("SAT Clock control?"); sscanf(userEntry,"%d",&clock_control);
    SiLabs_API_SAT_Clock        (front_end, clock_source, clock_input, clock_freq, clock_control );
    return 1;
  }
  return 0;
}
signed   int  Silabs_UserInput_SAT_Spectrum             (void) {
  Silabs_UserInputString("SAT Spectrum inversion: (0/1)? ");
  sscanf(userEntry,"%d",&spectrum_inversion);
  SiLabs_API_SAT_Spectrum(front_end, spectrum_inversion);
  return 1;
}
signed   int  Silabs_UserInput_SAT_AGC                  (void) {
  if (SiLabs_API_SAT_AGC_Options(front_end, messageBuffer) != 0) {
    printf ("Possible SAT AGC_Options: %s", messageBuffer);
    Silabs_UserInputString("SAT AGC 1 mode      ? 0x"); sscanf(userEntry,"%x",&agc1_mode);
    Silabs_UserInputString("SAT AGC 1 inversion ? ");   sscanf(userEntry,"%d",&agc1_inversion);
    Silabs_UserInputString("SAT AGC 2 mode      ? 0x"); sscanf(userEntry,"%x",&agc2_mode);
    Silabs_UserInputString("SAT AGC 2 inversion ? ");   sscanf(userEntry,"%d",&agc2_inversion);
    SiLabs_API_SAT_AGC          (front_end, agc1_mode, agc1_inversion, agc2_mode, agc2_inversion);
    return 1;
  }
  return 0;
}
#endif /* SATELLITE_FRONT_END */
signed   int  Silabs_UserInput_Set_Index_and_Tag        (void) {
  Silabs_UserInputString("Front_end index ? "); sscanf(userEntry,"%d",&tag_index);
  Silabs_UserInputString("Front_end TAG   ? ");
  SiLabs_API_Set_Index_and_Tag(front_end, tag_index, userEntry);
  return 1;
}
/************************************************************************************************************************
  SiLabs_Scan_Table_Init function
  Use:      carriers table initialization function
            Used to allocate the carriers table structure
  Returns: 0 if OK (allocation worked or already allocated), -1 if allocation error
************************************************************************************************************************/
signed   int  SiLabs_Scan_Table_Init                    (void)
{
  if (Carriers_Table == NULL) {

    Carriers_Table       = (SiLabs_Carriers_Struct*) malloc(sizeof(SiLabs_Carriers_Struct));
    if (Carriers_Table == NULL) { return -1; }

    Carriers_Table->carriers_count  = 0;
    Carriers_Table->standard        = (int *) malloc(sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->freq            = (int *) malloc(sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->bandwidth_Hz    = (int *) malloc(sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->stream          = (int *) malloc(sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->symbol_rate_bps = (unsigned int *) malloc(sizeof(unsigned int )*Carriers_Table->carriers_count);
    Carriers_Table->constellation   = (int *) malloc(sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->polarization    = (int *) malloc(sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->band            = (int *) malloc(sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->data_slice_id   = (int *) malloc(sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->plp_id          = (int *) malloc(sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->T2_base_lite    = (int *) malloc(sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->SSI             = (int *) malloc(sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->SQI             = (int *) malloc(sizeof(int )*Carriers_Table->carriers_count);
  }
  return 0;
}
/************************************************************************************************************************
  SiLabs_Scan_Table_Clear function
  Use:      carriers table de-initialization function
            Used to clear the carriers table structure
  Returns: 0
************************************************************************************************************************/
signed   int  SiLabs_Scan_Table_Clear                   (void)
{
  if    (Carriers_Table != NULL) {
    free(Carriers_Table->standard        );
    free(Carriers_Table->freq            );
    free(Carriers_Table->bandwidth_Hz    );
    free(Carriers_Table->stream          );
    free(Carriers_Table->symbol_rate_bps );
    free(Carriers_Table->constellation   );
    free(Carriers_Table->polarization    );
    free(Carriers_Table->band            );
    free(Carriers_Table->data_slice_id   );
    free(Carriers_Table->plp_id          );
    free(Carriers_Table->T2_base_lite    );
    free(Carriers_Table->SSI             );
    free(Carriers_Table->SQI             );
    Carriers_Table->carriers_count = 0;
    free(Carriers_Table);
    Carriers_Table = NULL;
  }
  return 0;
}
/************************************************************************************************************************
  SiLabs_Scan_Table_Count function
  Use:      retrieving the number of channels in the carriers table
            Used to know how many carriers are in the carriers table
  Returns: The number of carriers in the table
************************************************************************************************************************/
signed   int  SiLabs_Scan_Table_Count                   (void)
{
  if (SiLabs_Scan_Table_Init() == 0) {
    return Carriers_Table->carriers_count;
  }
  return 0;
}
/************************************************************************************************************************
  SiLabs_Scan_Table_AddOneCarrier function
  Use:      carrier addition function
            Used to add a carrier in the scan table
  Returns: The index of the new carrier (-1 if allocation error)
************************************************************************************************************************/
signed   int  SiLabs_Scan_Table_AddOneCarrier  (                            signed   int  standard, signed   int  freq, signed   int  bandwidth_Hz, signed   int  stream, unsigned int  symbol_rate_bps, signed   int  constellation, signed   int  polarization, signed   int  band, signed   int  data_slice_id, signed   int  plp_id, signed   int  T2_base_lite)
{
  int carrier_index;
  if (SiLabs_Scan_Table_Init() == 0) {
    Carriers_Table->carriers_count  = Carriers_Table->carriers_count +1;
    Carriers_Table->standard        = (int *) realloc(Carriers_Table->standard       , sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->freq            = (int *) realloc(Carriers_Table->freq           , sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->bandwidth_Hz    = (int *) realloc(Carriers_Table->bandwidth_Hz   , sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->stream          = (int *) realloc(Carriers_Table->stream         , sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->symbol_rate_bps = (unsigned int *) realloc(Carriers_Table->symbol_rate_bps, sizeof(unsigned int )*Carriers_Table->carriers_count);
    Carriers_Table->constellation   = (int *) realloc(Carriers_Table->constellation  , sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->polarization    = (int *) realloc(Carriers_Table->polarization   , sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->band            = (int *) realloc(Carriers_Table->band           , sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->data_slice_id   = (int *) realloc(Carriers_Table->data_slice_id  , sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->plp_id          = (int *) realloc(Carriers_Table->plp_id         , sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->T2_base_lite    = (int *) realloc(Carriers_Table->T2_base_lite   , sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->SSI             = (int *) realloc(Carriers_Table->SSI            , sizeof(int )*Carriers_Table->carriers_count);
    Carriers_Table->SQI             = (int *) realloc(Carriers_Table->SQI            , sizeof(int )*Carriers_Table->carriers_count);

    carrier_index = Carriers_Table->carriers_count -1;

    Carriers_Table->standard[carrier_index]        = standard;
    Carriers_Table->freq[carrier_index]            = freq;
    Carriers_Table->bandwidth_Hz[carrier_index]    = bandwidth_Hz;
    Carriers_Table->stream[carrier_index]          = stream;
    Carriers_Table->symbol_rate_bps[carrier_index] = symbol_rate_bps;
    Carriers_Table->constellation[carrier_index]   = constellation;
    Carriers_Table->polarization[carrier_index ]   = polarization;
    Carriers_Table->band[carrier_index]            = band;
    Carriers_Table->data_slice_id[carrier_index]   = data_slice_id;
    Carriers_Table->plp_id[carrier_index]          = plp_id;
    Carriers_Table->T2_base_lite[carrier_index]    = T2_base_lite;
    Carriers_Table->SSI[carrier_index]             = 0;
    Carriers_Table->SQI[carrier_index]             = 0;

    return carrier_index;
  } else {
    SiTRACE("SiLabs_Scan_Table_AddOneCarrier: Carriers_Table allocation error !\n");
    return -1;
  }
}
/************************************************************************************************************************
  SiLabs_Scan_Table_AddCarrierQuality function
  Use:      carrier addition function
            Used to add a carrier in the scan table
  Returns: The index of the new carrier (-1 if allocation error)
************************************************************************************************************************/
signed   int  SiLabs_Scan_Table_AddCarrierQuality (signed   int carrier_index, signed   int  SSI, signed   int SQI)
{
  if (carrier_index < Carriers_Table->carriers_count) {
    Carriers_Table->SSI[carrier_index]             = SSI;
    Carriers_Table->SQI[carrier_index]             = SQI;

    return carrier_index;
  } else {
    SiTRACE("SiLabs_Scan_Table_AddCarrierQuality: Carriers_Table allocation error !\n");
    return -1;
  }
}
/************************************************************************************************************************
  SiLabs_Scan_Table_Carrier_Info function
  Use:      retrieving the carrier parameters from the carriers table
  Parameters: carrier_index, the index of the carrier in the table
              standard, a pointer to the standard integer
              freq    , a pointer to the freq integer (in Hz for TER, in kHz for SAT)
              bandwidth_Hz, a pointer to the bandwidth_Hz integer (in Hz)
              stream, a pointer to the stream integer
              symbol_rate_bps, a pointer to the symbol_rate_bps integer (in bps)
              constellation, a pointer to the constellation integer
              polarization, a pointer to the satellite horizontal/vertical polarization information
              band, a pointer to the satellite band in
  Returns: 1 if OK, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_Scan_Table_Carrier_Info   (signed   int carrier_index, signed   int *standard, signed   int *freq, signed   int *bandwidth_Hz, signed   int *stream, unsigned int *symbol_rate_bps, signed   int *constellation, signed   int *polarization, signed   int *band, signed   int *data_slice_id, signed   int *plp_id, signed   int *T2_base_lite)
{
  /* return immediately if the required index is not in the table */
  if (carrier_index >= SiLabs_Scan_Table_Count()) {return 0;}

  *standard        = Carriers_Table->standard[carrier_index];
  *freq            = Carriers_Table->freq[carrier_index];
  *bandwidth_Hz    = Carriers_Table->bandwidth_Hz[carrier_index];
  *stream          = Carriers_Table->stream[carrier_index];
  *symbol_rate_bps = Carriers_Table->symbol_rate_bps[carrier_index];
  *constellation   = Carriers_Table->constellation[carrier_index];
  *polarization    = Carriers_Table->polarization[carrier_index];
  *band            = Carriers_Table->band[carrier_index];
  *data_slice_id   = Carriers_Table->data_slice_id[carrier_index];
  *plp_id          = Carriers_Table->plp_id[carrier_index];
  *T2_base_lite    = Carriers_Table->T2_base_lite[carrier_index];

  return 1;
}
/************************************************************************************************************************
  SiLabs_Scan_Table_Carrier_Quality function
  Use:      retrieving the carrier quality values from the carriers table
  Parameters: carrier_index, the index of the carrier in the table
              standard, a pointer to the standard integer
              SSI    , a pointer to the SSI integer
              SQI    , a pointer to the SQI integer
  Returns: 1 if OK, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_Scan_Table_Carrier_Quality(signed   int carrier_index, signed   int *SSI, signed   int *SQI)
{
  /* return immediately if the required index is not in the table */
  if (carrier_index >= SiLabs_Scan_Table_Count()) {return 0;}

  *SSI             = Carriers_Table->SSI[carrier_index];
  *SQI             = Carriers_Table->SQI[carrier_index];

  return 1;
}
/************************************************************************************************************************
  SiLabs_Scan_Table_Carrier_Text function
  Use:      retrieving the carrier parameters from the carriers table in a string
  Parameters: carrier_index, the index of the carrier in the table
  Returns: 1 if OK, 0 otherwise
************************************************************************************************************************/
signed   int  SiLabs_Scan_Table_Carrier_Text   (signed   int carrier_index, char *formatted_infos)
{

  /* return immediately if the required index is not in the table */
  if (carrier_index >= SiLabs_Scan_Table_Count()) {return 0;}
  if (carrier_index <  0                        ) {return 0;}

  sprintf(formatted_infos, "Carrier %3d: %-7s", carrier_index, Silabs_Standard_Text(Carriers_Table->standard[carrier_index]));

  switch (Carriers_Table->standard[carrier_index])
  {
    case SILABS_ANALOG:
    case SILABS_DVB_T :
    case SILABS_DVB_T2:
    case SILABS_ISDB_T:
    case SILABS_DVB_C :
    case SILABS_DVB_C2: {
      sprintf(formatted_infos, "%s %9d   Hz", formatted_infos, Carriers_Table->freq[carrier_index]);
      break;
    }
    case SILABS_DVB_S :
    case SILABS_DSS   :
    case SILABS_DVB_S2: {
      sprintf(formatted_infos, "%s %9d kHz" , formatted_infos, Carriers_Table->freq[carrier_index]);
      #ifdef    UNICABLE_COMPATIBLE
      if (front_end->unicable->installed) {
        if (Carriers_Table->freq[carrier_index] < 2200000) {
          if (Carriers_Table->band[carrier_index] == SILABS_BAND_LOW) {
            sprintf(formatted_infos, "%s Ku %9d kHz" , formatted_infos, Carriers_Table->freq[carrier_index] + front_end->unicable->Fo_kHz_low_band);
          } else {
            sprintf(formatted_infos, "%s Ku %9d kHz" , formatted_infos, Carriers_Table->freq[carrier_index] + front_end->unicable->Fo_kHz_high_band);
          }
        }
      } else {
        if (Carriers_Table->band[carrier_index] == SILABS_BAND_LOW) {
          sprintf(formatted_infos, "%s Ku %12d kHz" , formatted_infos, Carriers_Table->freq[carrier_index] +  9750000);
        } else {
          sprintf(formatted_infos, "%s Ku %12d kHz" , formatted_infos, Carriers_Table->freq[carrier_index] + 10600000);
        }
      }
      #endif /* UNICABLE_COMPATIBLE */
      break;
    }
    default           : {
      sprintf(formatted_infos, "%s INVALID standard (%d)!!!!\n"  , formatted_infos, Carriers_Table->standard[carrier_index]);
      return 0;
      break;
    }
  }
  switch (Carriers_Table->standard[carrier_index])
  {
    case SILABS_ANALOG: {
      break;
    }
    case SILABS_DVB_T : {
      sprintf(formatted_infos, "%s  %1.1f MHz,"     , formatted_infos, Carriers_Table->bandwidth_Hz[carrier_index]/1000000.0);
      sprintf(formatted_infos, "%s %s "             , formatted_infos, Silabs_Stream_Text (Carriers_Table->stream[carrier_index])        );
      break;
    }
    case SILABS_ISDB_T: {
      sprintf(formatted_infos, "%s  %1.1f MHz,"     , formatted_infos, Carriers_Table->bandwidth_Hz[carrier_index]/1000000.0);
      break;
    }
    case SILABS_MCNS  :
    case SILABS_DVB_C : {
      sprintf(formatted_infos, "%s %5.2f Mbps"      , formatted_infos, Carriers_Table->symbol_rate_bps[carrier_index]/1000000.0);
      sprintf(formatted_infos, "%s %-8s "           , formatted_infos, Silabs_Constel_Text(Carriers_Table->constellation[carrier_index]) );
      break;
    }
    case SILABS_DVB_C2: {
      sprintf(formatted_infos, "%s  %1.1f MHz"         , formatted_infos, Carriers_Table->bandwidth_Hz[carrier_index]/1000000.0);
      sprintf(formatted_infos, "%s  DATA SLICE ID %3d,", formatted_infos, Carriers_Table->data_slice_id[carrier_index]);
      sprintf(formatted_infos, "%s  PLP ID        %3d,", formatted_infos, Carriers_Table->plp_id[carrier_index]);
      break;
    }
    case SILABS_DVB_S :
    case SILABS_DSS   :
    case SILABS_DVB_S2: {
      sprintf(formatted_infos, "%s %5.2f Mbps"      , formatted_infos, Carriers_Table->symbol_rate_bps[carrier_index]/1000000.0);
      sprintf(formatted_infos, "%s (%s)"            , formatted_infos, Silabs_Polarization_Text(Carriers_Table->polarization[carrier_index]) );
      sprintf(formatted_infos, "%s (%s)"            , formatted_infos, Silabs_Band_Text        (Carriers_Table->band[carrier_index])         );
      break;
    }
    case SILABS_DVB_T2: {
      sprintf(formatted_infos, "%s  %1.1f MHz"     , formatted_infos, Carriers_Table->bandwidth_Hz[carrier_index]/1000000.0);
      if (Carriers_Table->plp_id[carrier_index] == -1) {
        sprintf(formatted_infos, "%s  PLP-ID auto" , formatted_infos);
      } else {
        sprintf(formatted_infos, "%s  PLP-ID %4d"   , formatted_infos, Carriers_Table->plp_id[carrier_index]);
      }
             if (Carriers_Table->T2_base_lite[carrier_index] == 1) {
      sprintf(formatted_infos, "%s  T2-Base"       , formatted_infos);
      } else if (Carriers_Table->T2_base_lite[carrier_index] == 2) {
      sprintf(formatted_infos, "%s  T2-Lite"       , formatted_infos);
      } else  {
      sprintf(formatted_infos, "%s  T2-Any"        , formatted_infos);
      }
      break;
    }
    default           : {
      break;
    }
  }
  sprintf(formatted_infos, "%s  SSI %3d"        , formatted_infos, Carriers_Table->SSI[carrier_index]);
  sprintf(formatted_infos, "%s  SQI %3d"        , formatted_infos, Carriers_Table->SQI[carrier_index]);
  return 1;
}
/************************************************************************************************************************
  SiLabs_Scan_Table_Infos function
  Use:      displaying the channels information in the console
            Used to know how many carriers are in the carriers table, and which values are needed to re-tune them.
  Returns: The number of carriers in the table
************************************************************************************************************************/
signed   int  SiLabs_Scan_Table_Infos          (void)
{
  int i;
  if (Carriers_Table == NULL) {
    printf("No carrier in table.\n");
    return 0;
  }
  for (i=0; i<SiLabs_Scan_Table_Count(); i++) { if (SiLabs_Scan_Table_Carrier_Text(i, messageBuffer)) printf ("%s\n",messageBuffer); }
  return i;
}
/************************************************************************************************************************
  SiLabs_Scan_Check_And_Add_Carrier function
  Use:      Checking lock and storing the carrier in the table if locked
            Used in conjunction with the seek Next to demonstrate
  Returns: The number of carriers in the table
************************************************************************************************************************/
signed   int  SiLabs_Scan_Check_And_Add_Carrier(SILABS_FE_Context *frontend, signed   int  standard, signed   int  freq, signed   int  bandwidth_Hz, signed   int  stream, unsigned int  symbol_rate_bps, signed   int  constellation, signed   int  polarization, signed   int  band, signed   int  data_slice_id, signed   int  plp_id, signed   int  T2_base_lite)
{
  int carrier_index;
  front_end = frontend;
  system_wait(1000);
  SiLabs_API_FE_status_selection   (front_end, custom_status,  FE_LOCK_STATE + FE_FREQ + FE_QUALITY + FE_SPECIFIC);
/*  printf (" SSI %d, SQI %d\n", custom_status->SSI, custom_status->SQI);*/
  if (custom_status->SQI < 100) {
    system_wait(2000);
    SiLabs_API_FE_status_selection   (front_end, custom_status,  FE_LOCK_STATE + FE_FREQ + FE_QUALITY);
/*    printf (" SSI %d, SQI %d\n", custom_status->SSI, custom_status->SQI);*/
  }
  carrier_index = SiLabs_Scan_Table_AddOneCarrier (standard, freq, bandwidth_Hz, stream, symbol_rate_bps, constellation, polarization, band, data_slice_id, plp_id, T2_base_lite);
  SiLabs_Scan_Table_AddCarrierQuality(carrier_index, custom_status->SSI, custom_status->SQI);
  if (custom_status->fec_lock) {
    printf("%c", 0x07);
    SiLabs_API_TS_Mode(front_end, SILABS_TS_PARALLEL);
    /* Check SI/PSI data here, if your HW allows it... */
  }

  return carrier_index;
}
/************************************************************************************************************************
  SiLabs_Scan_Loop function
  Use:      scan the band using SiLabs_API_Channel_Seek_Init and SiLabs_API_Channel_Seek_Next
            Used to fill the carriers table
  Returns: the number of detected channels during this loop
************************************************************************************************************************/
signed   int  SiLabs_Scan_Loop                 (void)
{
  int previous_count;
  int new_count;
  int standard;
  int i;
  int start;

  previous_count = SiLabs_Scan_Table_Count();

  standard = Silabs_UserInput_standard();
  if (standard < 0 ) return 0;


  /* Call SiLabs_API_switch_to_standard, in case the standard is different or the init has not been done yet */
  SiLabs_API_switch_to_standard      (front_end, standard, 0);

  /* Init the scan loop for the user-selected standard */
  Silabs_UserInput_SeekInit();

  start = system_time();

  while (Silabs_UserInput_SeekNext()) { /* call Silabs_UserInput_SeekNext as long as it detects new carriers */ }

  /* Put the demodulator out of scan mode */
  SiLabs_API_Channel_Seek_End(front_end);

  printf("\nScan duration %.3f s\n", (system_time() - start)/1000.0 );

  new_count = SiLabs_Scan_Table_Count();

  if (new_count - previous_count > 0) {printf("There are %d carriers now in the table (%d new carriers)\n", new_count, new_count - previous_count);}

  for (i = previous_count; i < new_count; i++) {
    SiLabs_Scan_Table_Carrier_Text(i, messageBuffer);
    printf("%s\n", messageBuffer);
  }

  return SiLabs_Scan_Table_Count() - previous_count;
}
/************************************************************************************************************************
  SiLabs_Scan_Zap_To_Index function
  Use:      select a carrier in the table and lock on this carrier
            Used to lock to carriers stored in the table
  Parameter: index, the index of the required carrier
  Returns: the lock status
************************************************************************************************************************/
signed   int  SiLabs_Scan_Zap_To_Index         (signed   int carrier_index)
{
  int standard;
  int freq;
  int bandwidth_Hz;
  int stream;
  unsigned int symbol_rate_bps;
  int constellation;
  int polarization;
  int band;
  int data_slice_id;
  int plp_id;
  int T2_base_lite;
  int res;
  int carriers_count;
  res = 0;

  if ((carriers_count = SiLabs_Scan_Table_Count() ) == 0) {printf("Please use 'lock/store' or 'scan' or 'SeekInit/SeekNext/SeekNext/.../SeekEnd' to fill the table\n"); return 0;}

  if (SiLabs_Scan_Table_Carrier_Info  (carrier_index, &standard, &freq, &bandwidth_Hz, &stream, &symbol_rate_bps, &constellation, &polarization, &band, &data_slice_id, &plp_id, &T2_base_lite) ) {
    last_carrier_index = carrier_index;
    res = SiLabs_API_lock_to_carrier  (front_end,      standard,  freq,  bandwidth_Hz,  stream,  symbol_rate_bps,  constellation,  polarization,  band,  data_slice_id,  plp_id, T2_base_lite);
    SiLabs_API_FE_status              (front_end, custom_status);
    SiLabs_API_Text_status            (front_end, custom_status, messageBuffer);
    printf("%s", messageBuffer);
  } else {
    printf ("Invalid index! Please select indexes between %d and %d\n", 0, carriers_count-1);
  }
  return res;
}
/************************************************************************************************************************
  SiLabs_Scan_Zap_Up function
  Use:      select the next carrier in the table and lock on this carrier
            Used to lock to carriers stored in the table
  Returns: the lock status
************************************************************************************************************************/
signed   int  SiLabs_Scan_Zap_Up               (void)
{
  int carriers_count;
  int carrier_index;

  if ((carriers_count = SiLabs_Scan_Table_Count() ) == 0) {printf("Please use 'lock/store' or 'scan' or 'SeekInit/SeekNext/SeekNext/.../SeekEnd' to fill the table\n"); return 0;}

  carrier_index = last_carrier_index+1;

  if (carrier_index >= carriers_count) {carrier_index = 0;}

  printf("Zap on carrier %d\n", carrier_index);

  return SiLabs_Scan_Zap_To_Index    (carrier_index);
}
/************************************************************************************************************************
  SiLabs_Scan_Zap_Down function
  Use:      select the previous carrier in the table and lock on this carrier
            Used to lock to carriers stored in the table
  Returns: the lock status
************************************************************************************************************************/
signed   int  SiLabs_Scan_Zap_Down             (void)
{
  int carriers_count;
  int carrier_index;

  if ((carriers_count = SiLabs_Scan_Table_Count() ) == 0) {printf("Please use 'lock/store' or 'scan' or 'SeekInit/SeekNext/SeekNext/.../SeekEnd' to fill the table\n"); return 0;}

  carrier_index = last_carrier_index-1;

  if (carrier_index < 0) {carrier_index = carriers_count-1;}

  printf("Zap on carrier %d\n", carrier_index);

  return SiLabs_Scan_Zap_To_Index    (carrier_index);
}
/************************************************************************************************************************
  SiLabs_Scan_Zap function
  Use:      select a carrier in the table and lock on this carrier
            Used to lock to carriers stored in the table
  Returns: the lock status
************************************************************************************************************************/
signed   int  SiLabs_Scan_Zap                  (void)
{
  int carriers_count;
  int carrier_index;

  if ((carriers_count = SiLabs_Scan_Table_Infos() ) == 0) {printf("Please use 'lock/store' or 'scan' or 'SeekInit/SeekNext/SeekNext/.../SeekEnd' to fill the table\n"); return 0;}

  sprintf(messageBuffer, "Select a carrier index (%d to %d)? ", 0, carriers_count-1);

  Silabs_UserInputString(messageBuffer);

  sscanf(userEntry,"%d",&carrier_index);

  return SiLabs_Scan_Zap_To_Index    (carrier_index);
}
/************************************************************************************************************************
  Silabs_bytes_trace function
  Use:        console application byte-level trace function
              Used to toggle L0 traces
************************************************************************************************************************/
signed   int  Silabs_bytes_trace               (void)
{
  int i;
  unsigned char trackMode;
  trackMode = !i2c->trackWrite;
  i2c->trackWrite = trackMode;
  i2c->trackRead  = trackMode;
  for (i=0; i<FRONT_END_COUNT; i++) {
      front_end               = &(FrontEnd_Table[i]);
    if (front_end->chip != 0) {
      printf("fe %d L0 traces set to '%d'\n", i, trackMode);
      SiLabs_API_bytes_trace(front_end, trackMode);
    }
  }
  front_end               = &(FrontEnd_Table[fe]);
  return trackMode;
}
/************************************************************************************************************************
  Silabs_help function
  Use:        console application help function
              Used to explain how to init the EVB, tune and scan
************************************************************************************************************************/
signed   int  Silabs_help                      (void)
{
    printf("\n\n\
----------------------------------------------------------------------------\n\
    This is a demonstration application used to illustrate how to use       \n\
       the SiLabs digital TV API delivered by Silicon Laboratories          \n\
                                                                            \n");
    printf("\
    It demonstrates a dual front-end case, and can deal with up to 4        \n\
    NB: Most platforms will only have one front-end, therefore              \n\
        the other ones will not work correctly unless properly wired        \n\
                                                                            \n\
    Front-end selection: '<(0 to 3)>' (default is '0')                      \n\
                                                                            \n");
    printf("\
    Scanning sequences:                                                     \n\
                                                                            \n\
      DVB_T : 'scan' 'T'   <min_freq> <max_freq> <bandwidth> <step>         \n\
      DVB_T2: 'scan' 'T2'  <min_freq> <max_freq> <bandwidth> <step>         \n\
      DVB_C : 'scan' 'C'   <min_freq> <max_freq> <min_SR> <max_SR>          \n\
      DVB_C2: 'scan' 'C2'  <min_freq> <max_freq>                            \n");
    printf("\
      DVB-S : 'scan' 'S'   <min_freq> <max_freq> <min_SR> <max_SR>          \n\
      DVB-S2: 'scan' 'S2'  <min_freq> <max_freq> <min_SR> <max_SR>          \n\
      DSS   : 'scan' 'DSS' <min_freq> <max_freq> <min_SR> <max_SR>          \n\
                                                                            \n");
    printf("\
    Locking sequences:                                                      \n\
                                                                            \n\
      DVB_T : 'lock' 'T'   <frequency> <bandwidth>     <stream>             \n\
      DVB_T2: 'lock' 'T2'  <frequency> <plp_id>        <T2_lock_mode>       \n\
      DVB_C : 'lock' 'C'   <frequency> <symbol_rate>   <qam>                \n");
    printf("\
      DVB_C2: 'lock' 'C2'  <frequency> <data_slice_id> <plp_id>             \n\
      DVB-S : 'lock' 'S'   <frequency> <symbol_rate>                        \n\
      DVB-S2: 'lock' 'S2'  <frequency> <symbol_rate>                        \n\
      DSS   : 'lock' 'DSS' <frequency> <symbol_rate>                        \n\
                                                                            \n\
");
#ifdef    USB_Capability
    printf("\n\
    Connection via the Cypress chip:    'USB'                               \n\
");
#endif /* USB_Capability*/
    printf("\n\
    Connection via the CUSTOM i2c  :    'CUST'                              \n\
    Init after power cycle or HW reset: 'hwinit'                            \n\
                                                                            \n");
    printf("\
    Repeatedly press the return key to update the status                    \n\
    Enter 'help' to display the help.                                       \n\
    Enter 'm'    to display the menu.                                       \n\
----------------------------------------------------------------------------\n\
");
  return 0;
}
/************************************************************************************************************************
  NAME: Silabs_menu
  DESCRIPTION: Silabs user menu function
              Used to display the various possibilities offered to the user
  Behavior:   Prints the menu in the console
************************************************************************************************************************/
void          Silabs_menu                      (unsigned char full)
{
  if (full) {
  printf("\
-----------------------------------------------------------------------\n\
   Console mode Application Menu:\n\
-----------------------------------------------------------------------\n\
");
  printf(" ------  i2c ---------\n\
read           : read bytes from i2c       \n\
write          : write bytes to i2c        \n\
");
#ifdef    USB_Capability
    printf("\n\
USB            : connect i2c in USB  mode  \n\
");
#endif /* USB_Capability*/
    printf("\n\
CUST           : connect i2c in CUST mode  \n\
trace          : toggle L0 traces\n\
traces         : manage L0 traces (use 'traces' then 'help' for details)\n\
");
  printf("\
 ------  Digital TV demodulator ------\n\
");
}
    printf("\
 ...... Locking        ......\n\
lock     : call SiLabs_API_lock_to_carrier    (front_end, standard, freq, bandwidth_Hz, stream, symbol_rate_bps, constellation);\n\
store    : store last carrier info in zap table\n\
 ...... Monitoring     ......\n\
''       : update status\n\
monitor  : monitor status for 1 minute every 200 ms\n");
    printf("\
r        : call SiLabs_API_Demod_reset        (front_end);\n\
u        : call SiLabs_API_Reset_Uncorrs      (front_end);\n\
 ...... TS control     ......\n\
ts       : call SiLabs_API_TS_Mode            (front_end, TS_SERIAL   );\n\
 ...... Scanning       ......\n");
    printf("\
SeekInit : call SiLabs_API_Channel_Seek_Init  (front_end, rangeMin, rangeMax, minRSSIdBm, maxRSSIdBm, minSNRHalfdB, maxSNRHalfdB);\n\
SeekNext : call SiLabs_API_Channel_Seek_Next  (front_end); and display the result.\n\
SeekEnd  : call SiLabs_API_Channel_Seek_End   (front_end);\n");
    printf("\
Get_TS_Dividers : call  Get_TS_Dividers to retrieve the TS dividers div_a / div_b \n\
");
    printf("\
scan     : call 'SeekInit' and then 'SeekNext' until completion, store detected channels in channel table;\n\
count    : display number of channels in the channel table;\n\
channels : display  channels present  in the channel table;\n\
zap      : calls SiLabs_API_lock_to_carrier for a carrier selected in the table;\n\
clear    : clear all channels from the channel table;\n");
#ifdef    DEMOD_DVB_T2
printf("\
AutoTER  : SiLabs_API_TER_AutoDetect(front_end, 1);\n\
NoAutoTER: SiLabs_API_TER_AutoDetect(front_end, 0);\n\
");
printf("\
PLP      : SiLabs_API_Select_PLP    (front_end, plp);\n\
");
#endif /* DEMOD_DVB_T2 */
printf ("\n SW configuration functions:\n\n\
Select_Demod             : select the source branch to use\n\
SPI_setup                : select the SPI pins\n\
");
#ifdef    TERRESTRIAL_FRONT_END
printf (" ------ TER -----\n\
Select_TER_Tuner         : user input for SiLabs_API_Select_TER_Tuner\n\
TER_Address              : user input for SiLabs_API_TER_Address\n\
TER_tuner_I2C_connection : user input for Silabs_API_TER_tuner_I2C_connection\n\
TER_Tuner_ClockConfig    : user input for Silabs_API_TER_tuner_ClockConfig\n\
TER_Clock                : user input for Silabs_API_TER_Clock\n\
TER_Tuner_FEF_Config     : user input for Silabs_API_TER_tuner_FEF_Config\n\
TER_AGC                  : user input for Silabs_API_TER_AGC\n\
TER_Tuner_AGC_Input      : user input for Silabs_API_TER_Tuner_AGC_Input\n\
TER_Tuner_FEF_input      : user input for Silabs_API_TER_Tuner_FEF_Input\n\
TER_Tuner_IF_Output      : user input for Silabs_API_TER_Tuner_IF_Output\n\
");
#ifdef    DEMOD_DVB_T2
printf("\
TER_FEF_Config           : user input for Silabs_UserInput_TER_FEF_Config\n\
");
#endif /* DEMOD_DVB_T2 */
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
printf (" ------ SAT -----\n\
Select_SAT_Tuner         : user input for SiLabs_API_Select_SAT_Tuner\n\
SAT_Address              : user input for SiLabs_API_SAT_Address\n\
SAT_tuner_I2C_connection : user input for Silabs_API_SAT_tuner_I2C_connection\n\
SAT_Clock                : user input for Silabs_API_SAT_Clock\n\
SAT_Spectrum             : user input for Silabs_API_SAT_Spectrum\n\
SAT_AGC                  : user input for Silabs_API_SAT_AGC\n\
");
printf("\
voltage_and_tone         : user input for Silabs_UserInput_VoltageTone\n\
AutoSAT                  : SiLabs_API_SAT_AutoDetect(front_end, 1);\n\
NoAutoSAT                : SiLabs_API_SAT_AutoDetect(front_end, 0);\n\
autocheck                : Display auto detect settings\n\
");
#ifdef    UNICABLE_COMPATIBLE
printf(" ------ Unicable -----\n\
install                  : SiLabs_API_SAT_Unicable_Install\n\
positionA                : unicable->satellite_position = UNICABLE_POSITION_A\n\
positionB                : unicable->satellite_position = UNICABLE_POSITION_B\n\
horizontal               : unicable->polarization       = SILABS_POLARIZATION_HORIZONTAL\n\
vertical                 : unicable->polarization       = SILABS_POLARIZATION_VERTICAL\n");
printf("\
low                      : unicable->band               = UNICABLE_LOW_BAND\n\
high                     : unicable->band               = UNICABLE_HIGH_BAND\n\
diseqc                   : tracing Diseqc data (toggle)\n\
hardtune                 : selecting Unicable values\n\
unicable                 : SiLabs_Unicable_API_Tune_Infos\n\
tones                    : SiLabs_Unicable_API_All_Tones\n\
tones_off                : SiLabs_Unicable_API_All_Off\n\
");
#endif /* UNICABLE_COMPATIBLE */
#endif /* SATELLITE_FRONT_END */
printf("\
Autocheck : Display auto detect settings\n\
");
  if (full) {
  printf(" ------ console -----\n\
help           : display application help\n\
cls            : clear screen\n\
m              : display this menu\n\
exit           : exit application\n\
minimal        : only displays minimal menu\n\
full           : displays full menu\n\
");
  }
  printf("----------------------------------------------------------------------------\n");
}
#ifdef    CONFIG_MACROS
signed   int  SiLabs_macro_selection      (signed   int auto_config)
{
  int len;
  len = SiLabs_SW_config_possibilities(messageBuffer);
  if (len == 0) {
    printf("\n\nMacro Configuration is not possible (no macros available)\n\n");
    return 0;
  }
  if (auto_config) {
#ifdef    USB_Capability
    if (i2c->connectionType != USB) {
      printf("\n\nAuto Configuration is not possible (no connection through a Cypress chip)\n\n");
    } else {
      /* Reading macro from Cypress EEPROM, then attempting auto configuration based on the macro */
      L0_SetAddress (i2c, 0xA0, 1);
      if (L0_ReadBytes  (i2c, 0x09, 50, (unsigned char*)&messageBuffer) == 0) {
        messageBuffer[49] = 0xFF;
        printf("\n\nAuto Configuration is not possible (board not connected)\n\n");
      } else {
        len = (int)strlen(messageBuffer);
        if (len > 50) {
          printf("\n\nAuto Configuration is not possible (undefined macro of len %d)\n\n", len);
        } else {
          printf("macro name (stored in Cypress EEPROM) : %s\n", messageBuffer);
          if (strcmp (messageBuffer + (len - 2) , "XX") == 0) { sprintf  (messageBuffer + (len - 2), "%s", "83A"); }
          if (SiLabs_SW_config_from_macro(messageBuffer)  != 0) {
            printf("\n\nAuto Configuration done using 'SW_INIT_%s' macro\n\n", messageBuffer);
            return 1;
          } else {
            printf("\n\nAuto Configuration is not possible (no macro or unknown '%s' macro)\n\n", messageBuffer);
          }
        }
      }
    }
#endif /* USB_Capability */
  }
  SiLabs_SW_config_possibilities(messageBuffer);
  printf("\nPossible configurations:\n%s\n", messageBuffer); sprintf(messageBuffer, "%s", "");
  Silabs_UserInputString("\n\nPlease select your configuration (press 'enter' for manual settings): ");
  if (strcmp_nocase(userEntry,"")!=0) {
    if (SiLabs_SW_config_from_macro(userEntry)  != 0) {
      printf("\n\nConfiguration done using 'SW_INIT_%s' macro\n\n", userEntry);
      return 1;
    }
  }
  return 0;
}
#endif /* CONFIG_MACROS */
#ifdef    SILABS_API_TEST_PIPE
double Silabs_UserInput_Test   (void)
{
  char  targetBuffer[100];
  char  cmdBuffer[100];
  char  sub_cmdBuffer[100];
  char *rettxt;
  char *target;
  char *cmd;
  char *sub_cmd;
  char *entry;
  double dval;
  double retdval;

  entry   = &entryBuffer[0];
  rettxt  = &messageBuffer[0];
  target  = &targetBuffer[0];
  cmd     = &cmdBuffer[0];
  sub_cmd = &sub_cmdBuffer[0];
  dval    = 0;

  sprintf(cmd,     "%s", "");
  sprintf(sub_cmd, "%s", "");

  Silabs_UserInputString("target  ? "); sprintf(target    , "%s", entry);

  if (strcmp_nocase(target,"help" )!=0) {
    Silabs_UserInputString("cmd     ? "); sprintf(cmd    , "%s" ,  entry);
    Silabs_UserInputString("sub_cmd ? "); sprintf(sub_cmd, "%s" ,  entry);
    Silabs_UserInputString("dval    ? "); sscanf(entry   , "%lf", &dval);
  }

  printf("'%s' '%s' '%s' '%f'...\n", target, cmd, sub_cmd, dval);

  Silabs_API_Test (front_end, target, cmd, sub_cmd, dval, &retdval, &rettxt);
  printf("%s", messageBuffer);
  return retdval;
}
#endif /* SILABS_API_TEST_PIPE */
#ifdef    USB_Capability
int cypress_portdisplay(const char * port_name) {
  unsigned short oe;
  unsigned short io;
  int  i;
  double retdval;
  char  *rettxt;
  char   txtBuffer[1000];
  rettxt   = txtBuffer;
  L0_Cypress_Process("read_output_enable_io_port", port_name, 0.0, &retdval, &rettxt);
  oe = (int)retdval;
  L0_Cypress_Process("read_io_port"              , port_name, 0.0, &retdval, &rettxt);
  io = (int)retdval;
  printf("Port %C: OE%C 0x%02x IO%C 0x%02x  ", port_name[0]-32, port_name[0]-32, oe, port_name[0]-32, io);
  for (i=7;i>=0;i--) { if ( (oe>>i)&0x01 ) { printf(" %d ", (io>>i)&0x01 ); } else { printf("(%d)", (io>>i)&0x01 ); } };
  printf("\n");
  return (oe<<8)+io;
}
#endif /* USB_Capability */
/************************************************************************************************************************
  Silabs_demoloop function
  Use:        Demo application loop function
              Used to call all available demod functions, based on the user's entry
  Behavior:   Wait for the user to enter a string, then calls the selected function (no string will redisplay the demod status)
************************************************************************************************************************/
signed   int  Silabs_demoloop                  (const char *demo_cmd)
{
    char  *entry;
    char   txtBuffer[1000];
    char  *txt;
    int    res;
    int    i;
    int    start_time_ms;
    int    handshake_mode;
    int    handshake_period_ms;
    int    lock;
    double retdval;

    entry   = entryBuffer;
    res     = 0;
    retdval = 0.0; i = (int)retdval;

    if (fe > FRONT_END_COUNT) return 0;

    txt           = txtBuffer;
    front_end     = &(FrontEnd_Table[fe]);
    custom_status = &(FE_Status);

    CHECK_FOR_ERRORS

    printf("\n%04d FrontEnd[%d] Command > ", ++commandCount, fe);
    if (strlen(demo_cmd) > 0) {
      sprintf(entry, demo_cmd);
      printf("%s\n", entry);
    } else {
      Silabs_UserInputString("");
    }

    /* In case the init failed or has not been done, reconnect the board to get a working connection when the board is powered and connected */
    if (front_end->init_ok == 0) {L0_Connect(i2c, mode); SiLabs_API_HW_Connect(front_end, mode);}
    goto demo_loop_start;
    demo_loop_start:
         if (strcmp_nocase(entry, "status" )==0) { sprintf (entry, "%s", ""); }
         /* front end selection */
         if ( (strcmp_nocase(entry, "0")==0) & (FRONT_END_COUNT>0) ) { fe = 0; printf ("Controlling FrontEnd %d\n",fe); return 1;}
         if ( (strcmp_nocase(entry, "1")==0) & (FRONT_END_COUNT>1) ) { fe = 1; printf ("Controlling FrontEnd %d\n",fe); return 1;}
         if ( (strcmp_nocase(entry, "2")==0) & (FRONT_END_COUNT>2) ) { fe = 2; printf ("Controlling FrontEnd %d\n",fe); return 1;}
         if ( (strcmp_nocase(entry, "3")==0) & (FRONT_END_COUNT>3) ) { fe = 3; printf ("Controlling FrontEnd %d\n",fe); return 1;}

         if (strcmp_nocase(entry, ""         )==0) {
           if (front_end->init_ok == 0) { printf("Init not ok. Please use 'lock' or 'scan' to perform the init first!\n"); return 1;}
           printf("Monitoring ...\n");
           SiLabs_API_FE_status          (front_end, custom_status);
           SiLabs_API_Text_status        (front_end, custom_status, messageBuffer);
           printf("%s",messageBuffer);
           return 1;
        }
         if (strcmp_nocase(entry, "hwinit"   )==0) { SiLabs_API_switch_to_standard (front_end, front_end->standard, 1); return 1;}
    else if (strcmp       (entry, "comm"     )==0) { SiLabs_API_communication_check(front_end); return 1;}
    else if (strcmp_nocase(entry, "infos"    )==0) { SiLabs_API_Infos(front_end, txt); printf("%s",txt);}
    else if (strcmp_nocase(entry, "SPI_Setup")==0) { Silabs_UserInput_SPI_Setup();                return 1;}
#ifdef    TERRESTRIAL_FRONT_END
    else if (strcmp_nocase(entry, "Select_TER_Tuner"        )==0) { Silabs_UserInput_Select_TER_Tuner();         return 1;}
    else if (strcmp_nocase(entry, "TER_Address"             )==0) { Silabs_UserInput_TER_Address();              return 1;}
    else if (strcmp_nocase(entry, "TER_tuner_I2C_connection")==0) { Silabs_UserInput_TER_tuner_I2C_connection(); return 1;}
    else if (strcmp_nocase(entry, "TER_Clock"               )==0) { Silabs_UserInput_TER_Clock();                return 1;}
    else if (strcmp_nocase(entry, "TER_AGC"                 )==0) { Silabs_UserInput_TER_AGC();                  return 1;}
    else if (strcmp_nocase(entry, "TER_Tuner_AGC_Input"     )==0) { Silabs_UserInput_TER_Tuner_AGC_Input();      return 1;}
    else if (strcmp_nocase(entry, "TER_Tuner_IF_Output"     )==0) { Silabs_UserInput_TER_Tuner_IF_Output();      return 1;}
#ifdef    DEMOD_DVB_T2
    else if (strcmp_nocase(entry, "TER_FEF_Config"          )==0) { Silabs_UserInput_TER_FEF_Config();           return 1;}
#endif /* DEMOD_DVB_T2 */
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
    else if (strcmp_nocase(entry, "Select_SAT_Tuner"        )==0) { Silabs_UserInput_Select_SAT_Tuner();         return 1;}
    else if (strcmp_nocase(entry, "SAT_tuner_I2C_connection")==0) { Silabs_UserInput_SAT_tuner_I2C_connection(); return 1;}
    else if (strcmp_nocase(entry, "SAT_Clock"               )==0) { Silabs_UserInput_SAT_Clock();                return 1;}
    else if (strcmp_nocase(entry, "SAT_AGC"                 )==0) { Silabs_UserInput_SAT_AGC();                  return 1;}
    else if (strcmp_nocase(entry, "SAT_Address"             )==0) { Silabs_UserInput_SAT_Address();              return 1;}
    else if (strcmp_nocase(entry, "SAT_Spectrum"            )==0) { Silabs_UserInput_SAT_Spectrum();             return 1;}
#ifdef   CHANNEL_BONDING
    else if (strcmp_nocase(entry, "Bonding"       )==0) {
      SiTraceConfiguration("traces -output stdout");
      Silabs_UserInputString("TS Bonding output (1/2) ? "  ); sscanf(userEntry,"%d",&res);
      if (res == 0) {return 1;}
      Channel_Bonding = &(Channel_Bonding_Context);
      SiLabs_Channel_Bonding_SW_Init(Channel_Bonding, &(FrontEnd_Table[0]), &(FrontEnd_Table[1]), NULL, NULL, 0, 0);
      SiLabs_Channel_Bonding_Stop   (Channel_Bonding);
      SiLabs_Channel_Bonding        (Channel_Bonding, 2, res);
      front_end = Channel_Bonding->master;
      SiTraceConfiguration("traces -output none");
      start_time_ms = system_time();
      Silabs_API_Test  (Channel_Bonding->master, "demod", "bonding"    , "ts_ber_init"     , 0.0, &retdval, &txt );
      Silabs_API_Test  (Channel_Bonding->master, "demod", "bonding"    , "ts_ber_rst"      , 0.0, &retdval, &txt );
      handshake_mode = -1;
      while (1) {
        SiLabs_API_Demod_status_selection(Channel_Bonding->master, custom_status, FE_LOCK_STATE);
        SiLabs_API_Demod_status_selection(Channel_Bonding->slave , custom_status, FE_LOCK_STATE + FE_SPECIFIC);
        Silabs_API_Test (Channel_Bonding->master, "demod", "bonding"    , "lock"            , 0.0, &retdval, &txt ); lock = (int)retdval;
        Silabs_API_Test (Channel_Bonding->master, "demod", "bonding"    , "ts_ber_avail"    , 0.0, &retdval, &txt ); i    = (int)retdval;
        Silabs_API_Test (Channel_Bonding->master, "demod", "bonding"    , "ts_ber_err"      , 0.0, &retdval, &txt ); res  = (int)retdval;
        if (handshake_mode != lock+res+i) { printf("%6d ms: SLAVE %s pcl %d, dl %d, isi_id %d. MASTER %s pcl %d, dl %d, isi_id %d Bonding lock %d, avail %d  %s"
                              , system_time() - start_time_ms
                              , Channel_Bonding->slave->Si2183_FE->demod->i2c->tag
                              , Channel_Bonding->slave->Si2183_FE->demod->rsp->dd_status.pcl
                              , Channel_Bonding->slave->Si2183_FE->demod->rsp->dd_status.dl
                              , Channel_Bonding->slave->Si2183_FE->demod->rsp->dvbs2_status.isi_id
                              , Channel_Bonding->master->Si2183_FE->demod->i2c->tag
                              , Channel_Bonding->master->Si2183_FE->demod->rsp->dd_status.pcl
                              , Channel_Bonding->master->Si2183_FE->demod->rsp->dd_status.dl
                              , Channel_Bonding->master->Si2183_FE->demod->rsp->dvbs2_status.isi_id
                              , lock
                              , i
                              , txt
                              );
        }
        handshake_mode = lock+res+i;
        system_wait(200);
#ifdef    _CONIO_H_
        if (kbhit()) return 1;
#endif /* _CONIO_H_ */
      }
      return 1;}

#endif /* CHANNEL_BONDING */
#endif /* SATELLITE_FRONT_END */
#ifdef    SAT_TUNER_RDA5816SD
    else if (strcmp_nocase(entry, "Pre_lna_gain"            )==0) {
      if (front_end->Si2183_FE->tuner_sat->sat_tuner_code == 0x58165D)  {
          Silabs_UserInputString("RDA5816SD Pre_lna_gain st1 ( 0:-17dB, 1:-13dB, 2:-8dB, 3:0dB ) ? ");
          sscanf(userEntry,"%d",&res);
          SiLabs_API_SAT_Tuner_I2C_Enable (front_end);
          L1_RF_RDA5816SD_pre_lna_gain(front_end->Si2183_FE->tuner_sat->RDA5816SD_Tuner[0], res);
          SiLabs_API_SAT_Tuner_I2C_Disable (front_end);
      }
      return 1;
    }
#endif /* SAT_TUNER_RDA5816SD */
    else if (strcmp_nocase(entry, "Select_Demod"            )==0) { front_end->chip = Silabs_UserInput_demod(); return 1; }
    else if (strcmp_nocase(entry, "Set_Index_and_Tag"       )==0) { Silabs_UserInput_Set_Index_and_Tag();       return 1; }
    else if (strcmp_nocase(entry, "Config_Infos"            )==0) { Silabs_UserInputString("Function   ? "); SiLabs_API_Config_Infos(front_end, userEntry, txt); printf("%s",txt); return 1; }
    else if (strcmp_nocase(entry, "Get_TS_Dividers"         )==0) { SiLabs_API_Get_TS_Dividers(front_end, &div_a, &div_b); printf("TS div_a %d div_b %d\n", div_a, div_b)   ; return 1; }
#ifdef    CONFIG_MACROS
    else if (strcmp_nocase(entry, "macros"   )==0) { SiLabs_macro_selection(0); return 1;}
#endif /* CONFIG_MACROS */
#ifdef    DEMOD_DVB_T
    else if (strcmp       (entry, "cell_id"  )==0) { printf("Cell ID %d\n", custom_status->cell_id); return 1;}
    else if (strcmp       (entry, "ATV"      )==0) { SiLabs_API_switch_to_standard (front_end, SILABS_ANALOG, 0); return 1;}
    else if (strcmp       (entry, "T"        )==0) { SiLabs_API_switch_to_standard (front_end, SILABS_DVB_T , 0); return 1;}
#endif /* DEMOD_DVB_T */
#ifdef    DEMOD_ISDB_T
    else if (strcmp       (entry, "ISDBT"    )==0) { SiLabs_API_switch_to_standard (front_end, SILABS_ISDB_T, 0); return 1;}
#endif /* DEMOD_ISDB_T */
#ifdef    DEMOD_DVB_T2
    else if (strcmp       (entry, "T2"       )==0) { SiLabs_API_switch_to_standard (front_end, SILABS_DVB_T2, 0); return 1;}
    else if (strcmp_nocase(entry, "PLP"      )==0) { SiLabs_API_Select_PLP         (front_end, Silabs_UserInput_plp_id() ); return 1;}
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_DVB_C
    else if (strcmp       (entry, "C"        )==0) { SiLabs_API_switch_to_standard (front_end, SILABS_DVB_C , 0); return 1;}
#endif /* DEMOD_DVB_C */
#ifdef    DEMOD_DVB_C2
    else if (strcmp       (entry, "C2"       )==0) { SiLabs_API_switch_to_standard (front_end, SILABS_DVB_C2, 0); return 1;}
#endif /* DEMOD_DVB_C2 */
#ifdef    DEMOD_MCNS
    else if (strcmp       (entry, "MCNS"     )==0) { SiLabs_API_switch_to_standard (front_end, SILABS_MCNS  , 0); return 1;}
#endif /* DEMOD_MCNS */
#ifdef    DEMOD_DVB_S_S2_DSS
    else if (strcmp       (entry, "S"        )==0) { SiLabs_API_switch_to_standard (front_end, SILABS_DVB_S , 0); return 1;}
    else if (strcmp       (entry, "S2"       )==0) { SiLabs_API_switch_to_standard (front_end, SILABS_DVB_S2, 0); return 1;}
    else if (strcmp       (entry, "DSS"      )==0) { SiLabs_API_switch_to_standard (front_end, SILABS_DSS   , 0); return 1;}
    else if (strcmp_nocase(entry, "lpf"      )==0) {
      Silabs_UserInputString("lpf (in kHz)? ");
      sscanf(userEntry,"%d",&i);
      SiLabs_API_SAT_Tuner_SetLPF(front_end, i); return 1;
    }
#endif /* DEMOD_DVB_S_S2_DSS */
    else if (strcmp       (entry, "SLEEP"    )==0) { SiLabs_API_switch_to_standard (front_end, SILABS_SLEEP , 0); return 1;}
    else if (strcmp       (entry, "ANALOG"   )==0) { SiLabs_API_switch_to_standard (front_end, SILABS_ANALOG, 0); return 1;}
    else if (strcmp       (entry, "TA"       )==0) {
      while (1) {
      SiLabs_API_switch_to_standard (front_end, SILABS_DVB_T,  0);
      SiLabs_API_switch_to_standard (front_end, SILABS_ANALOG, 0);
      printf("%6d\r",i++);
      system_wait(0);
#ifdef    _CONIO_H_
    if (kbhit()) return 1;
#endif /* _CONIO_H_ */
      }
    }
    else if (strcmp       (entry, "lock"     )==0) {
      if (Silabs_UserInput_Lock() == 1) {
        SiLabs_API_FE_status          (front_end, custom_status);
        SiLabs_API_Text_status        (front_end, custom_status, messageBuffer);
        printf("%s",messageBuffer);
      }
      return 1;
    }
    else if (strcmp_nocase(entry, "store"    )==0) {
      res = SiLabs_Scan_Table_AddOneCarrier(last_standard, last_freq, last_bandwidth_Hz, last_stream, last_symbol_rate_bps, last_constellation, last_polarization, last_band, last_data_slice_id, last_plp_id, last_T2_base_lite);
      SiLabs_Scan_Table_Carrier_Text(res, messageBuffer);
      printf("Stored %s\n", messageBuffer);
      return 1;
    }
    else if (strcmp_nocase(entry, "SeekInit" )==0) { Silabs_UserInput_SeekInit(); return 1;}
    else if (strcmp_nocase(entry, "SeekNext" )==0) { Silabs_UserInput_SeekNext(); return 1;}
    else if (strcmp_nocase(entry, "SeekEnd"  )==0) { SiLabs_API_Channel_Seek_End (front_end); return 1;}
    else if (strcmp_nocase(entry, "r"        )==0) { SiLabs_API_Demod_reset      (front_end); return 1;}
    else if (strcmp_nocase(entry, "u"        )==0) { SiLabs_API_Reset_Uncorrs    (front_end); return 1;}
    else if (strcmp_nocase(entry, "ts"       )==0) { Silabs_UserInput_TS         ();          return 1;}
    else if (strcmp_nocase(entry, "u"        )==0) { SiLabs_API_Reset_Uncorrs    (front_end); return 1;}
#ifdef    SiTRACES
    else if (strcmp_nocase(entry, "traces"   )==0) { Silabs_UserInput_traces();            return 1;}
    else if (strcmp_nocase(entry, "traceLevel")==0) { Silabs_UserInput_traceLevel();       return 1;}
#endif /* SiTRACES */
    else if (strcmp_nocase(entry, "trace"    )==0) { printf("%d\n", Silabs_bytes_trace()); return 1;}
    else if (strcmp_nocase(entry, "minimal"  )==0) { full_menu = 0; return 1;}
    else if (strcmp_nocase(entry, "full"     )==0) { full_menu = 1; return 1;}
#ifdef    DEMOD_DVB_T2
    else if (strcmp_nocase(entry, "AutoTER"     )==0) { SiLabs_API_TER_AutoDetect  (front_end, 1); return 1;}
    else if (strcmp_nocase(entry, "NoAutoTER"   )==0) { SiLabs_API_TER_AutoDetect  (front_end, 0); return 1;}
    else if (strcmp_nocase(entry, "T2_lock_mode")==0) { printf("%d\n", SiLabs_API_TER_T2_lock_mode(front_end, Silabs_UserInput_T2_lock_mode() ) ); return 1;}
    else if (strcmp_nocase(entry, "T2_signalling_on" )==0) { front_end->Si2183_FE->misc_infos |= 0x01000000; printf("misc_infos 0x%08X\n", front_end->Si2183_FE->misc_infos); return 1;}
    else if (strcmp_nocase(entry, "T2_signalling_off")==0) { front_end->Si2183_FE->misc_infos &= 0xFEFFFFFF; printf("misc_infos 0x%08X\n", front_end->Si2183_FE->misc_infos); return 1;}
#endif /* DEMOD_DVB_T2 */
#ifdef    DEMOD_ISDB_T
    else if (strcmp_nocase(entry, "ISDBT_Monitoring_mode")==0) { printf("%d\n", SiLabs_API_TER_ISDBT_Monitoring_mode(front_end, Silabs_UserInput_ISDBT_Monitoring_mode() ) ); return 1;}
#endif /* DEMOD_ISDB_T */
    else if (strcmp_nocase(entry, "autocheck")==0) {
#ifdef    DEMOD_DVB_T2
      printf("auto_detect TER %d ", SiLabs_API_TER_AutoDetect(front_end, 2));
#endif /* DEMOD_DVB_T2 */
#ifdef    SATELLITE_FRONT_END
      printf("auto_detect_SAT %d ", SiLabs_API_SAT_AutoDetect(front_end, 2));
#endif /* SATELLITE_FRONT_END */
      printf("\n");
    }
    else if (strcmp_nocase(entry, "handshake")==0) {
      handshake_period_ms = 0;
      while (Silabs_UserInputString("handshakeUsed   <0 1> ? ") ==0);
      sscanf(userEntry,"%d",&handshake_mode);
      if (handshake_mode != 0) {
      while (Silabs_UserInputString("handshakePeriod (ms)  ? ") ==0);
      sscanf(userEntry,"%d",&handshake_period_ms);
      }
      printf("%d\n", SiLabs_API_Handshake_Setup (front_end, (unsigned char)handshake_mode, handshake_period_ms) );
      return 1;
    }
    else if (strcmp_nocase(entry, "detect"   )==0) {
      SiLabs_API_Auto_Detect_Demods(i2c, &res, demod_code, demod_add, demod_string); for (i = 0;  i < res; i++) { printf("%s\n", demod_string[i] );} return 1;}
#ifdef    SATELLITE_FRONT_END
    else if (strcmp_nocase(entry, "voltage_and_tone")==0) { Silabs_UserInput_VoltageTone(); return 1;}
    else if (strcmp_nocase(entry, "AutoSAT"  )==0) { SiLabs_API_SAT_AutoDetect(front_end, 1);}
    else if (strcmp_nocase(entry, "NoAutoSAT")==0) { SiLabs_API_SAT_AutoDetect(front_end, 0);}
#ifdef    UNICABLE_COMPATIBLE
    else if (strcmp_nocase(entry, "ub"                 )==0) { while (Silabs_UserInputString("UB ? "     ) ==0); sscanf(userEntry,"%d",&i); front_end->unicable->ub = i&0xFF; return 1; }
    else if (strcmp_nocase(entry, "ub_freq"            )==0) { while (Silabs_UserInputString("Fub_kHz ? ") ==0); sscanf(userEntry,"%d",&front_end->unicable->Fub_kHz); return 1; }
    else if (strcmp_nocase(entry, "horizontal")==0) { front_end->unicable->polarization = UNICABLE_HORIZONTAL;
                                                             front_end->polarization           = SILABS_POLARIZATION_HORIZONTAL;
                                                             front_end->unicable->bank         = front_end->unicable->satellite_position*4 + front_end->unicable->polarization*2 + front_end->unicable->band;
                                                             return 1;}
    else if (strcmp_nocase(entry, "vertical"  )==0) { front_end->unicable->polarization = UNICABLE_VERTICAL;
                                                             front_end->polarization           = SILABS_POLARIZATION_VERTICAL;
                                                             front_end->unicable->bank         = front_end->unicable->satellite_position*4 + front_end->unicable->polarization*2 + front_end->unicable->band;
                                                             return 1;}
    else if (strcmp_nocase(entry, "positionA" )==0) { front_end->unicable->satellite_position = UNICABLE_POSITION_A ;
                                                             front_end->unicable->bank         = front_end->unicable->satellite_position*4 + front_end->unicable->polarization*2 + front_end->unicable->band;
                                                             return 1;}
    else if (strcmp_nocase(entry, "positionB" )==0) { front_end->unicable->satellite_position = UNICABLE_POSITION_B ;
                                                             front_end->unicable->bank         = front_end->unicable->satellite_position*4 + front_end->unicable->polarization*2 + front_end->unicable->band;
                                                             return 1;}
    else if (strcmp_nocase(entry, "low"       )==0) { front_end->unicable->band = front_end->band = UNICABLE_LOW_BAND  ;
                                                             front_end->unicable->bank         = front_end->unicable->satellite_position*4 + front_end->unicable->polarization*2 + front_end->unicable->band;
                                                             return 1;}
    else if (strcmp_nocase(entry, "high"      )==0) { front_end->unicable->band = front_end->band = UNICABLE_HIGH_BAND  ;
                                                             front_end->unicable->bank         = front_end->unicable->satellite_position*4 + front_end->unicable->polarization*2 + front_end->unicable->band;
                                                             return 1;}
    else if (strcmp_nocase(entry, "diseqc"    )==0) { front_end->unicable->trackDiseqc = !front_end->unicable->trackDiseqc; return 1;}
    else if (strcmp_nocase(entry, "hardtune"  )==0) { Silabs_UserInput_Harcoded_Tune ();  return 1;}
    else if (strcmp_nocase(entry, "T+"        )==0) { SiLabs_Unicable_API_Hardcoded_Tune(front_end->unicable, front_end->unicable->bank, (front_end->unicable->T)+1, front_end->unicable->sat_tuner_freq); return 1;}
    else if (strcmp_nocase(entry, "T-"        )==0) { SiLabs_Unicable_API_Hardcoded_Tune(front_end->unicable, front_end->unicable->bank, (front_end->unicable->T)-1, front_end->unicable->sat_tuner_freq); return 1;}
    else if (strcmp_nocase(entry, "unicable"  )==0) { SiLabs_Unicable_API_Tune_Infos (front_end->unicable, txt); printf("%s\n", txt);  return 1;}
#ifdef    SILABS_API_TEST_PIPE
    else if (strcmp_nocase(entry, "tones"    )==0) { Silabs_API_Test (front_end, "unicable", "tones", "on", 0.0, &retdval, &txt); printf("%s\n", txt); return 1;}
    else if (strcmp_nocase(entry, "tones_off")==0) { Silabs_API_Test (front_end, "unicable", "tones", "off" , 0.0, &retdval, &txt); printf("%s\n", txt); return 1;}
#endif /* SILABS_API_TEST_PIPE */
#endif /* UNICABLE_COMPATIBLE */
#endif /* SATELLITE_FRONT_END */
    else if (strcmp_nocase(entry, "m"        )==0) { Silabs_menu(full_menu); return 1;}
    else if (strcmp_nocase(entry, "help"     )==0) { Silabs_help(); return 1;}
    else if (strcmp_nocase(entry, "cls"      )==0) { system("cls");}
    else if (strcmp_nocase(entry, "quit"     )==0) { return 0;}
    else if (strcmp_nocase(entry, "exit"     )==0) { return 0;}
    else if (strcmp_nocase(entry, "read"     )==0) { SiLabs_I2C_UserInput_read ();}
    else if (strcmp_nocase(entry, "write"    )==0) { SiLabs_I2C_UserInput_write();}
    else if (strcmp_nocase(entry, "usb"      )==0) { mode = USB;      L0_Connect(i2c, mode); SiLabs_API_HW_Connect(front_end, mode); return 1;}
    else if (strcmp_nocase(entry, "simu"     )==0) { mode = SIMU;     L0_Connect(i2c, mode); SiLabs_API_HW_Connect(front_end, mode); return 1;}
    else if (strcmp_nocase(entry, "linux_USB")==0) { mode = LINUX_USB;L0_Connect(i2c, mode); SiLabs_API_HW_Connect(front_end, mode); return 1;}
    else if (strcmp_nocase(entry, "customer" )==0) { mode = CUSTOMER; L0_Connect(i2c, mode); SiLabs_API_HW_Connect(front_end, mode); return 1;}
  #ifdef    USB_Capability
    else if (strcmp_nocase(entry, "close"    )==0) { mode = SIMU;     L0_Cypress_Process("close", "", 0.0, &retdval, &txt) ; printf("%s\n", txt); return 1;}
    else if (strcmp_nocase(entry, "cypress_ports")==0) { Silabs_UserInput_Cypress_Ports(); return 1;}
    else if (strcmp_nocase(entry, "OEA"      )==0) { Silabs_UserInputString("OEA  ? 0x"); if (strcmp_nocase(entry, "" )!=0) { sscanf(userEntry,"%x",&i); L0_Cypress_Process("output_enable_io_port", "a", (double)i, &retdval, &entry); }; cypress_portdisplay("a"); return 1; }
    else if (strcmp_nocase(entry, "IOA"      )==0) { Silabs_UserInputString("IOA  ? 0x"); if (strcmp_nocase(entry, "" )!=0) { sscanf(userEntry,"%x",&i); L0_Cypress_Process("write_io_port"        , "a", (double)i, &retdval, &entry); }; cypress_portdisplay("a"); return 1; }
    else if (strcmp_nocase(entry, "OEB"      )==0) { Silabs_UserInputString("OEB  ? 0x"); if (strcmp_nocase(entry, "" )!=0) { sscanf(userEntry,"%x",&i); L0_Cypress_Process("output_enable_io_port", "b", (double)i, &retdval, &entry); }; cypress_portdisplay("b"); return 1; }
    else if (strcmp_nocase(entry, "IOB"      )==0) { Silabs_UserInputString("IOB  ? 0x"); if (strcmp_nocase(entry, "" )!=0) { sscanf(userEntry,"%x",&i); L0_Cypress_Process("write_io_port"        , "b", (double)i, &retdval, &entry); }; cypress_portdisplay("b"); return 1; }
    else if (strcmp_nocase(entry, "OED"      )==0) { Silabs_UserInputString("OED  ? 0x"); if (strcmp_nocase(entry, "" )!=0) { sscanf(userEntry,"%x",&i); L0_Cypress_Process("output_enable_io_port", "d", (double)i, &retdval, &entry); }; cypress_portdisplay("d"); return 1; }
    else if (strcmp_nocase(entry, "IOD"      )==0) { Silabs_UserInputString("IOD  ? 0x"); if (strcmp_nocase(entry, "" )!=0) { sscanf(userEntry,"%x",&i); L0_Cypress_Process("write_io_port"        , "d", (double)i, &retdval, &entry); }; cypress_portdisplay("d"); return 1; }
    else if (strcmp_nocase(entry, "ports"    )==0) {
      cypress_portdisplay("a");
      cypress_portdisplay("b");
      cypress_portdisplay("c");
      cypress_portdisplay("d");
      cypress_portdisplay("e");
    return 1;
    }
  #endif /* USB_Capability */
#ifdef    L0_SLOW_I2C
    else if (strcmp_nocase(entry, "slow"     )==0) { L0_SlowI2C();   return 1;}
    else if (strcmp_nocase(entry, "fast"     )==0) { L0_FastI2C();   return 1;}
#endif /* L0_SLOW_I2C */
    else if (strcmp_nocase(entry, "cust"     )==0) { mode = CUSTOMER; L0_Connect(i2c, mode); SiLabs_API_HW_Connect(front_end, mode); return 1;}
    else if (strcmp_nocase(entry, "scan"     )==0) { SiLabs_Scan_Loop();        return 1;}
    else if (strcmp_nocase(entry, "clear"    )==0) { SiLabs_Scan_Table_Clear(); return 1;}
    else if (strcmp_nocase(entry, "channels" )==0) { SiLabs_Scan_Table_Infos(); return 1;}
    else if (strcmp_nocase(entry, "zap"      )==0) { SiLabs_Scan_Zap();         return 1;}
    else if (strcmp_nocase(entry, "up"       )==0) { SiLabs_Scan_Zap_Up();      return 1;}
    else if (strcmp_nocase(entry, "down"     )==0) { SiLabs_Scan_Zap_Down();    return 1;}
    else if (strcmp_nocase(entry, "tune"     )==0) {
      SiLabs_API_Tune      (front_end, Silabs_UserInput_tune(front_end->standard) );
      return 1;
    }
    else if (strcmp_nocase(entry, "blindlock")==0) {
      if (front_end->standard != SILABS_DVB_C) { SiLabs_API_switch_to_standard(front_end, SILABS_DVB_C, 0); }
      last_freq = SiLabs_API_Tune        (front_end, Silabs_UserInput_tune(front_end->standard) );
      start_time_ms = system_time();
      SiLabs_API_Channel_Seek_Init       (front_end, last_freq, last_freq, 8000000, 0, 1000000, (int)(7000000*1.06), 0, 0, 0, 0);
      lock = SiLabs_API_Channel_Seek_Next(front_end, &last_standard, &last_freq,  &last_bandwidth_Hz, &last_stream, &last_symbol_rate_bps, &last_constellation, &last_polarization, &last_band, &last_data_slice_id, &last_plp_id, &last_T2_base_lite);
      SiLabs_API_Channel_Seek_End        (front_end);
      printf("lock %d after %6.3f ms\n", lock, (system_time() - start_time_ms)/1000.0 );
      if (lock) printf("symbol_rate %d\n", last_symbol_rate_bps);
      return 1;
    }
    else if (strcmp_nocase(entry, "monitor"  )==0) {
      start_time_ms = system_time();
      while (1) {
        SiLabs_API_FE_status          (front_end, custom_status);
        SiLabs_API_Text_status        (front_end, custom_status, messageBuffer);
        system("cls");
        printf("%s",messageBuffer);
        system_wait(200);
#ifdef    _CONIO_H_
    if (kbhit()) return 1;
#endif /* _CONIO_H_ */
      }
      return 1;
    }
#ifdef    TS_CROSSBAR
    else if (strcmp_nocase(entry, "crossbar_init"   )==0) {
      printf("crossbar_init\n");
      fe_A = &(FrontEnd_Table[0]);
      fe_B = &(FrontEnd_Table[1]);
      SiLabs_TS_Crossbar_SW_Init         (crossbar, fe_A, fe_B);
      SiLabs_TS_Crossbar_Serial_Config   (crossbar->ts_1,15, 0,15, 0, 1, 1, 1);
      SiLabs_TS_Crossbar_Parallel_Config (crossbar->ts_1, 4, 0, 4, 0);
      SiLabs_TS_Crossbar_Serial_Config   (crossbar->ts_2,15, 0,15, 0, 1, 1, 1);
      SiLabs_TS_Crossbar_Parallel_Config (crossbar->ts_2, 4, 0, 4, 0);
      return 1;
    }
    else if (strcmp_nocase(entry, "crossbar"        )==0) {
      Silabs_UserInputTSCrossbar();
      return 1;
    }
    else if (strcmp_nocase(entry, "crossbar_status" )==0) {
      SiLabs_TS_Crossbar_TS_Status  (crossbar);
      SiLabs_TS_Crossbar_Status_Text(crossbar);
      return 1;
    }
#endif /* TS_CROSSBAR */
#ifdef    TERRESTRIAL_FRONT_END
    else if (strcmp_nocase(entry, "broadcast_tuners")==0) {
      SILABS_FE_Context    *front_ends[FRONT_END_COUNT];
      for (i=0; i<FRONT_END_COUNT; i++) {
        if (FrontEnd_Table[i].chip != 0) {
          front_ends[i] = &(FrontEnd_Table[i]);
          res++;
        }
      }
      for (i=0; i<res; i++) {  SiLabs_API_TER_Tuner_I2C_Enable (front_ends[i]);  }
      SiLabs_API_TER_Broadcast_I2C    (front_ends, res);
      for (i=0; i<res; i++) {  SiLabs_API_TER_Tuner_I2C_Disable(front_ends[i]);  }
      return 1;
    }
    else if (strcmp_nocase(entry, "Get_AC_Data"     )==0) {
      unsigned char AC_data[26];
      res = SiLabs_API_Get_AC_DATA              (front_end, 0, 0, 0, 203, AC_data);
      printf("%2d bytes of AC data (%3d bits)", res , res*8); for (i=0 ; i < res ; i++ ) { printf(" 0x%02X", AC_data[i] ); } printf ("\n");
      return 1;
    }
#endif /* TERRESTRIAL_FRONT_END */
    else if (strcmp_nocase(entry, "broadcast_demods")==0) {
      SILABS_FE_Context    *front_ends[FRONT_END_COUNT];
      for (i=0; i<FRONT_END_COUNT; i++) {
        if (FrontEnd_Table[i].chip != 0) {
          front_ends[i] = &(FrontEnd_Table[i]);
          res++;
        }
      }
      SiLabs_API_Demods_Broadcast_I2C (front_ends, res);
      return 1;
    }
    else if (strcmp_nocase(entry, "broadcast_i2c"   )==0) {
      SILABS_FE_Context    *front_ends[FRONT_END_COUNT];
      for (i=0; i<FRONT_END_COUNT; i++) {
        if (FrontEnd_Table[i].chip != 0) {
          front_ends[i] = &(FrontEnd_Table[i]);
          res++;
        }
      }
      SiLabs_API_Broadcast_I2C (front_ends, res);
      return 1;
    }
#ifdef    SILABS_API_TEST_PIPE
    else if (strcmp_nocase(entry, "testPipe" )==0) { Silabs_UserInput_Test();   return 1;}
    else if (strcmp_nocase(entry, "spi"      )==0) {
      Silabs_API_Test (front_end, "demod", "spi_download", "enable", 1.0, &retdval, &txt);
/*      SiLabs_API_switch_to_standard (front_end, front_end->standard, 1);*/
      return 1;
    }
#endif /* SILABS_API_TEST_PIPE */
    else {
      Silabs_menu(full_menu);
      printf("\n unknown option '%s'\n", entry);
    }

    return 1;
}
/************************************************************************************************************************
  main function
  Use:        main usage demonstration function
              Used to show how to init the SW and HW, tune and lock on any standard
  Porting:    For demonstration purpose, should be replaced by the final application
  Behavior:   Starts by the EVB initialization, then displays the user menu
************************************************************************************************************************/
signed   int  main (int argc, char *argv[])
{
  int res;
  unsigned int demod_address;
  unsigned char  ucBufferArea[10000];
  unsigned char *ucMyBuffer;
  char iimsgTmpBuffer[1000];
  char iimsgBigBuffer[10000];
  char *iimsg;
  char *init_calls;
  #define II(...) sprintf(iimsg, __VA_ARGS__); strcat(init_calls, iimsg);
  #define II_S    printf("/****************************************************************/\n");
  #define II_P    printf("\n%s\n", init_calls); init_calls = iimsgBigBuffer; sprintf(init_calls, "%s", "");
  iimsg        = iimsgTmpBuffer;
  init_calls   = iimsgBigBuffer;
  ucMyBuffer   = ucBufferArea;
  demod_string[0] = &demod_string_0[0];
  demod_string[1] = &demod_string_1[0];
  demod_string[2] = &demod_string_2[0];
  demod_string[3] = &demod_string_3[0];

  argc=argc; /* To avoid compiler warning */
  argv=argv; /* To avoid compiler warning */
  demod_address = ter_tuner_address = sat_tuner_address   =  lnb_chip_address = 0;
  clock_source = clock_input = clock_freq = 0;
  agc1_mode = agc2_mode = agc1_inversion  = agc2_inversion = 0;

  /* Initial communication mode */
  mode = USB;
  res  = 1;
  nb_front_ends = 1;

  Carriers_Table = NULL;

  SiTraceDefaultConfiguration();

  userEntry = entryBuffer;
  /* I2C pointer initialization (to allow i2c validation) */
  i2c = &i2c_context;
  L0_Init(i2c);
  i2c->mustReadWithoutStop =0;

  Silabs_help();
#ifdef    TS_CROSSBAR
  crossbar = &(TS_Crossbar_Table[0]);
#endif /* TS_CROSSBAR */

  SiTraceConfiguration("traces -output file   -file off -verbose on  -function off -line off -time off \n");
//  SiTraceConfiguration("traces -output file   -file off -verbose on  -function off -line off -time on\n");

#ifdef    CONFIG_MACROS
  if (argc>1) {
    if (SiLabs_SW_config_from_macro(argv[1]) != 0) { goto sw_init_done; }
  } else {
    if (SiLabs_macro_selection(1)            != 0) { goto sw_init_done; }
  }
#endif /* CONFIG_MACROS */

  /* Manual entry of the board configuration */
  Silabs_UserInputString("Manual HW configuration (single dual triple quad)? ");
  if (strcmp_nocase(userEntry,"single" )==0) { nb_front_ends = 1; }
  if (strcmp_nocase(userEntry,"dual"   )==0) { nb_front_ends = 2; }
  if (strcmp_nocase(userEntry,"triple" )==0) { nb_front_ends = 3; }
  if (strcmp_nocase(userEntry,"quad"   )==0) { nb_front_ends = 4; }

printf("/* Allocating %d SILABS_FE_Context structures */\n", nb_front_ends);
II("/* Allocating %d SILABS_FE_Context structures */\n", nb_front_ends);
II("SILABS_FE_Context     FrontEnd_Table[%d];\n"       , nb_front_ends);
II("SILABS_FE_Context     *front_end;\n");
II_S;
II_P;
II_S;

  /* Software Init */
  for (fe=0; fe<nb_front_ends; fe++) {
  II("/* SW Init for front end %d */\n", fe );
    printf("====================================\n");
    printf(" Front End %d configuration:\n",     fe);
    printf("====================================\n");
    front_end               = &(FrontEnd_Table[fe]);
II("front_end                   = &(FrontEnd_Table[%d]);\n", fe);
    front_end->chip = Silabs_UserInput_demod();
II("front_end->chip             = %d; /* (0x%0X) */\n", front_end->chip , front_end->chip );
    printf("DEMODULATOR address for front_end[%d]?", fe); Silabs_UserInputString(" 0x"); sscanf(userEntry,"%x",&demod_address);
#ifdef    TERRESTRIAL_FRONT_END
    printf("TER Tuner   address for front_end[%d]?", fe); Silabs_UserInputString(" 0x"); sscanf(userEntry,"%x",&ter_tuner_address);
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
    printf("SAT Tuner   address for front_end[%d]?", fe); Silabs_UserInputString(" 0x"); sscanf(userEntry,"%x",&sat_tuner_address);
#endif /* SATELLITE_FRONT_END */
II("SiLabs_API_SW_Init                  (front_end, 0x%02x, 0x%02x, 0x%02x);\n", demod_address, ter_tuner_address, sat_tuner_address);
    SiLabs_API_SW_Init          (front_end, demod_address, ter_tuner_address, sat_tuner_address);
    if ( SiLabs_API_SPI_Setup(front_end, 0,0,0,0,0) == 1 ) { /* if SPI download is supported by the part */
      Silabs_UserInput_SPI_Setup();
II("SiLabs_API_SPI_Setup                (front_end, 0x%02x, %d, %d, %d, %d);\n", send_option, clk_pin, clk_pola, data_pin, data_order);
    }
#ifdef    TERRESTRIAL_FRONT_END
  if (ter_tuner_address != 0x00) {
#ifdef    SILABS_TER_TUNER_API
    Silabs_UserInput_Select_TER_Tuner ();
II("SiLabs_API_Select_TER_Tuner         (front_end, 0x%x, %d);\n", ter_tuner_code, ter_tuner_index);
#endif /* SILABS_TER_TUNER_API */
  #ifdef    INDIRECT_I2C_CONNECTION
    Silabs_UserInput_TER_tuner_I2C_connection();
II("SiLabs_API_TER_tuner_I2C_connection (front_end, %d);\n", fe_index);
  #endif /* INDIRECT_I2C_CONNECTION */
    Silabs_UserInput_TER_Tuner_ClockConfig();
II("SiLabs_API_TER_Tuner_ClockConfig    (front_end, %d, %d);\n",  xtal, xout);
    Silabs_UserInput_TER_Clock();
II("SiLabs_API_TER_Clock                (front_end, %d, %d, %d, %d);\n",  clock_source, clock_input, clock_freq, clock_control);
#ifdef    DEMOD_DVB_T2
  Silabs_UserInput_TER_FEF_Config ();
II("SiLabs_API_TER_FEF_Config           (front_end, %d, 0x%x, %d);\n", fef_mode, fef_pin, fef_level );
#endif /* DEMOD_DVB_T2 */
  Silabs_UserInput_TER_AGC();
II("SiLabs_API_TER_AGC                  (front_end, 0x%x, %d, 0x%x, %d);\n", agc1_mode, agc1_inversion, agc2_mode, agc2_inversion );
  Silabs_UserInput_TER_Tuner_AGC_Input();
II("Silabs_API_TER_Tuner_AGC_Input      (front_end, %d);\n",  dtv_agc_source );
    Silabs_UserInput_TER_Tuner_IF_Output();
II("SiLabs_API_TER_Tuner_IF_Output      (front_end, %d);\n",  dtv_out_type);
  }
#endif /* TERRESTRIAL_FRONT_END */
#ifdef    SATELLITE_FRONT_END
  if (sat_tuner_address != 0x00) {
#ifdef    SILABS_SAT_TUNER_API
    Silabs_UserInput_Select_SAT_Tuner ();
II("SiLabs_API_Select_SAT_Tuner         (front_end, 0x%x, %d);\n", sat_tuner_code, sat_tuner_index);
  if (SiLabs_API_SAT_Tuner_Sub(front_end, 0)==1) {
    Silabs_UserInput_SAT_Tuner_Sub    ();
II("SiLabs_API_SAT_Tuner_Sub         (front_end, %d);\n", sat_tuner_sub);
  }
#endif /* SILABS_SAT_TUNER_API */
    Silabs_UserInput_SAT_Select_LNB_Chip();
II("SiLabs_API_SAT_Select_LNB_Chip      (front_end, %d, 0x%02x);\n", res, lnb_chip_address);
    if (nb_front_ends > 1) {
      SiLabs_UserInput_SAT_LNB_Chip_Index();
II("SiLabs_API_SAT_LNB_Chip_Index       (front_end, %d);\n", lnb_index);
    }
  #ifdef    INDIRECT_I2C_CONNECTION
    Silabs_UserInput_SAT_tuner_I2C_connection();
II("SiLabs_API_SAT_tuner_I2C_connection (front_end, %d);\n", fe_index);
  #endif /* INDIRECT_I2C_CONNECTION */
    Silabs_UserInput_SAT_Clock();
II("SiLabs_API_SAT_Clock                (front_end, %d, %d, %d, %d);\n",  clock_source, clock_input, clock_freq, clock_control);
    Silabs_UserInput_SAT_Spectrum();
II("SiLabs_API_SAT_Spectrum             (front_end, %d);\n", spectrum_inversion );
    Silabs_UserInput_SAT_AGC();
II("SiLabs_API_SAT_AGC                  (front_end, 0x%x, %d, 0x%x, %d);\n", agc1_mode, agc1_inversion, agc2_mode, agc2_inversion );
  }
#endif /* SATELLITE_FRONT_END */
II("SiLabs_API_HW_Connect               (front_end, %d);\n", mode);
    SiLabs_API_HW_Connect               (front_end, mode);
    II_S;
    II_P;
    II_S;
  }

  printf("\nManaging %d front-end(s)\n", nb_front_ends);

#ifdef    CONFIG_MACROS
  sw_init_done:
#endif /* CONFIG_MACROS */

#ifdef    SILABS_API_TEST_PIPE
  printf("\nSILABS_API_TEST_PIPE available\n\n");
#endif /* SILABS_API_TEST_PIPE */

  fe = 0;
  front_end     = &(FrontEnd_Table[fe]);

  full_menu = 1;
 /* Setting default values for 'store' parameters */
  last_standard        = SILABS_DVB_T;
  last_freq            = 474166666   ;
  last_bandwidth_Hz    = 8000000;
  last_stream          = SILABS_LP;
  last_symbol_rate_bps = 6900000;
  last_constellation   = SILABS_QAMAUTO;
  last_carrier_index   = -1;
  last_plp_id          = -1; /* auto      */
  last_T2_base_lite    =  1; /* Base only */

  #ifdef    USB_Capability
  /* Checking USB communication with the cypress chip */
  L0_Connect(i2c, USB);
  L0_FastI2C();
  sprintf(messageBuffer, "0xa0 0 5");
  if ((int)L0_ReadString(i2c, messageBuffer , ucMyBuffer) != 5) {
    SiERROR ("Cypress Communication error !\nConnect the EVB, reset the USB interface!\n");
    res = 0;
  } else {
    SiTRACE ("Cypress   Communication OK\n");
    res = 1;
  }
  #endif /* USB_Capability */

  if (res == 1) {
    /* Checking DEMOD communication */
    sprintf(messageBuffer, "0x%02x 1", 0xc8);
    if ((int)L0_ReadString(i2c, messageBuffer , ucMyBuffer) != 1) {
      SiERROR ("Demod Communication error !\n");
      SiERROR ("Connect the EVB to the I2C interface!\n");
    } else {
      SiTRACE ("Demod     Communication OK\n");
      res = 0xc0;
      if (res !=0) {
        /* Checking TER TUNER communication */
        SiLabs_API_Tuner_I2C_Enable(front_end);
        sprintf(messageBuffer, "0x%02x 1", 0xc0);
        if ((int)L0_ReadString(i2c, messageBuffer , ucMyBuffer) != 1) {
          SiERROR ("TER Tuner Communication error !\n");
          res = 0;
        } else {
          SiTRACE ("TER_Tuner Communication OK\n");
          res = 1;
        }
        SiLabs_API_Tuner_I2C_Disable(front_end);
      }
    }
  }

  while (Silabs_demoloop(""));

  exit(0);

  return 0;
}


