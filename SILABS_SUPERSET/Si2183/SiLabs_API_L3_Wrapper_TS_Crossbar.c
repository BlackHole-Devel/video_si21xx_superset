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
/*                                  SiLabs API TS Crossbar Functions                                         */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains TS Crossbar API functions for dual SiLabs digital TV demodulators             */
/*-----------------------------------------------------------------------------------------------------------*/
/* Change log: */
/* Last  changes:

  As from V2.5.2:
   <improvement>[comments] In SiLabs_TS_Crossbar_TS1_TS2: comment correction

  As from V2.5.1:
   <improvement>[cleanup]
    In SiLabs_TS_Crossbar_TS_Status: removing front_end (unused)
    In SiLabs_TS_Crossbar_TS1_TS2: removing several unused variables

  As from V2.4.7: In SiLabs_TS_Crossbar_TS1_TS2: setting ts_1_source and ts_2_source to NULL to avoid compiler warnings

  As from V2.4.6:
   <improvement/Crossbar> [SW_Init] In SiLabs_TS_Crossbar_SW_Init: removing call to status function, to keep the SW init
    function only managing pointers and structures, with no i2c traffic and no need for prior HW init.
   <improvement/Crossbar> [Default values] In SiLabs_TS_Crossbar_TS_Status: Setting ts_1_source and ts_2_source by default,
    to have them initialized in all cases. There was an issue with the previous version when an invalid configuration was requested.
   <redefinition>[New_TS_Pads] SiLabs_TS_Crossbar_Serial_Config redefined to add support for the new TS pads.
   <improvement>[warning] In SiLabs_TS_Crossbar_TS1_TS2: moving setup of ts1_source and ts2_source to avoid compilation warnings.
   <new_feature>[New_TS_Pads] In SiLabs_TS_Crossbar_TS1_TS2: Setting DD_TS_SLR_SERIAL property when in serial mode

  As from V2.4.2:
   <redefinition> SiLabs_TS_Crossbar_TS_Status redefined to do the status on both demods, to be able to set the TS_1/TS_2 modes
   <correction> In SiLabs_TS_Crossbar_TS1_TS2:
    Corrected test to avoid sending twice the same command when a single source is used for both TS_1 and TS_2.
    Propagating TS drive strength/shape values in secondary TS, not only in primary TS.

  As from V2.4.1:
   <correction> In SiLabs_TS_Crossbar_Serial_Config / SiLabs_TS_Crossbar_Parallel_Config: adding missing shape setup.

  As from V2.4.0:
   <new_feature> [tag/level] adding tag and level support for Si2167B and derivatives

*/
/* Older changes:
 *************************************************************************************************************/
/* TAG V2.8.0 */

#ifndef   TS_CROSSBAR
  "If you get a compilation error on this line, it means that you included the TS_Crossbar code in your project without defining TS_CROSSBAR.";
  "Please define TS_CROSSBAR at project-level (this is also used to include the TS_CROSSBAR properties at L1 level), or remove the TS_Crossbar code from your project";
#endif /* TS_CROSSBAR */

#ifdef    TS_CROSSBAR

/* Before including the headers, define SiLevel and SiTAG */
#define   SiLEVEL          4
#define   SiTAG            "TS Crossbar "
#include "SiLabs_API_L3_Wrapper_TS_Crossbar.h"

#ifdef    __cplusplus
extern "C" {
#endif /* __cplusplus */

char*          SiLabs_TS_Crossbar_Signal_Text     (CUSTOM_TS_Crossbar_Enum  ts_signal) {
  switch (ts_signal) {
    case SILABS_TS_CROSSBAR_TS_A        : { return (char *)"TS_A    "; break;}
    case SILABS_TS_CROSSBAR_TS_B        : { return (char *)"TS_B    "; break;}
    case SILABS_TS_CROSSBAR_TRISTATE    : { return (char *)"TRISTATE"; break;}
    default                             : { SiTRACE_X("UNKNOWN ts_signal value %d\n", ts_signal); return (char *)"UNKNOWN" ; break;}
  }
}
signed   int   SiLabs_TS_Crossbar_SW_Init         (SILABS_TS_Crossbar *ts_crossbar,
                                                   SILABS_FE_Context  *fe_A,
                                                   SILABS_FE_Context  *fe_B )
{
  if (ts_crossbar       == NULL) {
    SiERROR ("no ts_crossbar pointer!\n"      ); return 0;
  }
  SiTRACE("API CALL XBAR : SiLabs_TS_Crossbar_SW_Init (crossbar, %s, %s)\n", fe_A->tag, fe_B->tag );
  ts_crossbar->fe_A = fe_A;
  ts_crossbar->fe_B = fe_B;
  ts_crossbar->ts_1 = &(ts_crossbar->ts_1_Obj);
  ts_crossbar->ts_2 = &(ts_crossbar->ts_2_Obj);

  /* Set DD_TS_PINS 'activity' fields to 'CLEAR' */
  ts_crossbar->fe_A->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_activity   = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_ACTIVITY_CLEAR;
  ts_crossbar->fe_A->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_activity = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_ACTIVITY_CLEAR;
  ts_crossbar->fe_B->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_activity   = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_ACTIVITY_CLEAR;
  ts_crossbar->fe_B->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_activity = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_ACTIVITY_CLEAR;
/* removing TS crossbar status from the SW init function (it's done inside SiLabs_TS_Crossbar_TS1_TS2)
  SiLabs_TS_Crossbar_TS_Status   (ts_crossbar);
  SiLabs_TS_Crossbar_Status_Text (ts_crossbar);
*/
  ts_crossbar->state_known = 0;
  return 1;
}
void  SiLabs_TS_Crossbar_Status_Text     (SILABS_TS_Crossbar *ts_crossbar) {
  SiTRACE ("TS_1 (%s/%s)\n", SiLabs_TS_Crossbar_Signal_Text(ts_crossbar->ts_1_signal), Silabs_TS_Mode_Text(ts_crossbar->ts_1->ts_mode) );
  SiTRACE ("TS_2 (%s/%s)\n", SiLabs_TS_Crossbar_Signal_Text(ts_crossbar->ts_2_signal), Silabs_TS_Mode_Text(ts_crossbar->ts_2->ts_mode) );
}
/************************************************************************************************************************
  SiLabs_TS_Crossbar_TS_Mode function
  Use:      Transport Stream Mode function for TS crossbar
            Used to store the TS mode in a SILABS_TS_Config structure
  Parameter: ts_crossbar_config, the SILABS_TS_Config to fill
  Parameter: ts_mode, the selected TS mode
    possible values:
      SILABS_TS_TRISTATE    TSx is set in tristate
      SILABS_TS_SERIAL      TSx is set in serial
      SILABS_TS_PARALLEL    TSx is set in parallel
      SILABS_TS_GPIF        TSx is set in GPIF mode (only valid on SiLabs EVBs)
      SILABS_TS_OFF         TSx is set off (all pins are frozen)
************************************************************************************************************************/
signed   int   SiLabs_TS_Crossbar_TS_Mode         (SILABS_TS_Config *ts_crossbar_config,
                                                   CUSTOM_TS_Mode_Enum ts_mode )
{
  ts_crossbar_config->ts_mode = ts_mode;
  return 0;
}
/************************************************************************************************************************
  SiLabs_TS_Crossbar_TS_Status function
  Use:      Transport Stream Mode status for TS crossbar
            Used to retrieve the TS crossbar status and store it in the API fields
  Parameter: ts_crossbar, the TS crossbar context
  Returns: 1 if no error (i.e. TS crossbar conflicts), 0 otherwise
************************************************************************************************************************/
signed   int   SiLabs_TS_Crossbar_TS_Status       (SILABS_TS_Crossbar *ts_crossbar)
{
  SILABS_FE_Context *ts_1_source;
  SILABS_FE_Context *ts_2_source;
  signed   int conflicts=0;
  SiTRACE("API CALL XBAR  : SiLabs_TS_Crossbar_TS_Status (ts_crossbar)\n");
#ifdef    Si2183_COMPATIBLE
  if (ts_crossbar->fe_A->chip ==   0x2183 ) {
 #ifdef    Si2183_DD_TS_PINS_CMD

    ts_crossbar->fe_A->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_mode     = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_NO_CHANGE;
    ts_crossbar->fe_A->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_mode   = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_NO_CHANGE;
    ts_crossbar->fe_B->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_mode     = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_NO_CHANGE;
    ts_crossbar->fe_B->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_mode   = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_NO_CHANGE;
    Si2183_L1_SendCommand2 (ts_crossbar->fe_A->Si2183_FE->demod, Si2183_DD_TS_PINS_CMD_CODE );
    Si2183_L1_SendCommand2 (ts_crossbar->fe_B->Si2183_FE->demod, Si2183_DD_TS_PINS_CMD_CODE );

    ts_crossbar->ts_1_signal = SILABS_TS_CROSSBAR_TRISTATE;
    ts_crossbar->ts_2_signal = SILABS_TS_CROSSBAR_TRISTATE;
    ts_1_source = ts_crossbar->fe_A;
    ts_2_source = ts_crossbar->fe_B;

    if (ts_crossbar->fe_A->Si2183_FE->demod->rsp->dd_ts_pins.primary_ts_mode   != Si2183_DD_TS_PINS_RESPONSE_PRIMARY_TS_MODE_DISABLED      ) {
      ts_1_source = ts_crossbar->fe_A;
      ts_crossbar->ts_1_signal = SILABS_TS_CROSSBAR_TS_A;
    }
    if (ts_crossbar->fe_A->Si2183_FE->demod->rsp->dd_ts_pins.secondary_ts_mode != Si2183_DD_TS_PINS_RESPONSE_SECONDARY_TS_MODE_DISABLED    ) {
      ts_2_source = ts_crossbar->fe_A;
      ts_crossbar->ts_2_signal = SILABS_TS_CROSSBAR_TS_A;
    }
    if (ts_crossbar->fe_B->Si2183_FE->demod->rsp->dd_ts_pins.primary_ts_mode   != Si2183_DD_TS_PINS_RESPONSE_PRIMARY_TS_MODE_DISABLED      ) {
      ts_2_source = ts_crossbar->fe_B;
      ts_crossbar->ts_2_signal = SILABS_TS_CROSSBAR_TS_B;
    }
    if (ts_crossbar->fe_B->Si2183_FE->demod->rsp->dd_ts_pins.secondary_ts_mode != Si2183_DD_TS_PINS_RESPONSE_SECONDARY_TS_MODE_DISABLED    ) {
      ts_1_source = ts_crossbar->fe_B;
      ts_crossbar->ts_1_signal = SILABS_TS_CROSSBAR_TS_B;
    }

         if (ts_1_source->Si2183_FE->demod->prop->dd_ts_mode.mode == Si2183_DD_TS_MODE_PROP_MODE_SERIAL   ) { ts_crossbar->ts_1->ts_mode   = SILABS_TS_SERIAL;   }
    else if (ts_1_source->Si2183_FE->demod->prop->dd_ts_mode.mode == Si2183_DD_TS_MODE_PROP_MODE_PARALLEL ) { ts_crossbar->ts_1->ts_mode   = SILABS_TS_PARALLEL; }
    else if (ts_1_source->Si2183_FE->demod->prop->dd_ts_mode.mode == Si2183_DD_TS_MODE_PROP_MODE_TRISTATE ) { ts_crossbar->ts_1->ts_mode   = SILABS_TS_TRISTATE; }

         if (ts_2_source->Si2183_FE->demod->prop->dd_ts_mode.mode == Si2183_DD_TS_MODE_PROP_MODE_SERIAL   ) { ts_crossbar->ts_2->ts_mode   = SILABS_TS_SERIAL;   }
    else if (ts_2_source->Si2183_FE->demod->prop->dd_ts_mode.mode == Si2183_DD_TS_MODE_PROP_MODE_PARALLEL ) { ts_crossbar->ts_2->ts_mode   = SILABS_TS_PARALLEL; }
    else if (ts_2_source->Si2183_FE->demod->prop->dd_ts_mode.mode == Si2183_DD_TS_MODE_PROP_MODE_TRISTATE ) { ts_crossbar->ts_2->ts_mode   = SILABS_TS_TRISTATE; }

    if (ts_1_source->Si2183_FE->demod->rsp->dd_ts_pins.primary_ts_activity   == Si2183_DD_TS_PINS_RESPONSE_PRIMARY_TS_ACTIVITY_CONFLICT  ) {
      SiTRACE("!!! %s primary   TS is in Conflict!\n", ts_1_source->tag);
      conflicts++;
    }
    if (ts_1_source->Si2183_FE->demod->rsp->dd_ts_pins.secondary_ts_activity == Si2183_DD_TS_PINS_RESPONSE_SECONDARY_TS_ACTIVITY_CONFLICT) {
      SiTRACE("!!! %s secondary TS is in Conflict!\n", ts_1_source->tag);
      conflicts++;
    }
    if (ts_2_source->Si2183_FE->demod->rsp->dd_ts_pins.primary_ts_activity   == Si2183_DD_TS_PINS_RESPONSE_PRIMARY_TS_ACTIVITY_CONFLICT  ) {
      SiTRACE("!!! %s primary   TS is in Conflict!\n", ts_2_source->tag);
      conflicts++;
    }
    if (ts_2_source->Si2183_FE->demod->rsp->dd_ts_pins.secondary_ts_activity == Si2183_DD_TS_PINS_RESPONSE_SECONDARY_TS_ACTIVITY_CONFLICT) {
      SiTRACE("!!! %s secondary TS is in Conflict!\n", ts_2_source->tag);
      conflicts++;
    }
    if (conflicts) {
      SiERROR("TS crossbar conflicts detected !\n");
      return 0;
    }
    SiTRACE ("ts_crossbar->ts_1_signal %s\n", SiLabs_TS_Crossbar_Signal_Text(ts_crossbar->ts_1_signal) );
    SiTRACE ("ts_crossbar->ts_2_signal %s\n", SiLabs_TS_Crossbar_Signal_Text(ts_crossbar->ts_2_signal) );
    return 1;
 #endif /* Si2183_DD_TS_PINS_CMD */
  }
#endif /* Si2183_COMPATIBLE */
  SiERROR ("SiLabs_TS_Crossbar_TS_Status not supported by current code!\n");
  return 0;
}
/************************************************************************************************************************
  SiLabs_TS_Crossbar_Serial_Config function
  Use:      Transport Stream Configuration function for Serial
            Used to store the strength and shape for serial TS output in a SILABS_TS_Config structure
  Parameter: ts_crossbar_config, the SILABS_TS_Config to fill
  Parameter: ts_serial_data_strength
  Parameter: ts_serial_data_shape
  Parameter: ts_serial_clk_strength
  Parameter: ts_serial_clk_shape
  Parameter: ts_slr_serial_enable
  Parameter: ts_slr_serial_clk
  Parameter: ts_slr_serial_data
************************************************************************************************************************/
signed   int   SiLabs_TS_Crossbar_Serial_Config   (SILABS_TS_Config *ts_crossbar_config,
                                                    unsigned char ts_serial_data_strength,   unsigned char ts_serial_data_shape ,
                                                    unsigned char ts_serial_clk_strength ,   unsigned char ts_serial_clk_shape  ,
                                                    unsigned char ts_slr_serial_enable,      unsigned char ts_slr_serial_clk, unsigned char ts_slr_serial_data)
{
  ts_crossbar_config->ts_serial_data_strength = ts_serial_data_strength;
  ts_crossbar_config->ts_serial_clk_strength  = ts_serial_clk_strength;
  ts_crossbar_config->ts_serial_data_shape    = ts_serial_data_shape;
  ts_crossbar_config->ts_serial_clk_shape     = ts_serial_clk_shape;
  ts_crossbar_config->ts_serial_slr_enable    = ts_slr_serial_enable;
  ts_crossbar_config->ts_serial_clk_slr       = ts_slr_serial_clk;
  ts_crossbar_config->ts_serial_data_slr      = ts_slr_serial_data;
  return 0;
}
/************************************************************************************************************************
  SiLabs_TS_Crossbar_Parallel_Config function
  Use:      Transport Stream Configuration function for Parallel
            Used to store the strength and shape for parallel TS output in a SILABS_TS_Config structure
  Parameter: ts_crossbar_config, the SILABS_TS_Config to fill
  Parameter: ts_parallel_data_strength
  Parameter: ts_parallel_data_shape
  Parameter: ts_parallel_clk_strength
  Parameter: ts_parallel_clk_shape
************************************************************************************************************************/
signed   int   SiLabs_TS_Crossbar_Parallel_Config (SILABS_TS_Config *ts_crossbar_config,
                                                    unsigned char ts_parallel_data_strength, unsigned char ts_parallel_data_shape ,
                                                    unsigned char ts_parallel_clk_strength , unsigned char ts_parallel_clk_shape  )
{
  ts_crossbar_config->ts_parallel_data_strength = ts_parallel_data_strength;
  ts_crossbar_config->ts_parallel_clk_strength  = ts_parallel_clk_strength;
  ts_crossbar_config->ts_parallel_data_shape    = ts_parallel_data_shape;
  ts_crossbar_config->ts_parallel_clk_shape     = ts_parallel_clk_shape;
  return 0;
}
/************************************************************************************************************************
  SiLabs_TS_Crossbar_TS1_TS2 function
  Use:      Transport Stream crossbar mode selection function for TS1 and TS2
            Used to select the required signal to be output on TS1 and TS2, while checking for configuration conflicts
  Parameter: ts_crossbar, a SILABS_TS_Crossbar structure containing all the required information for the switch
  Parameter: ts1_signal, a CUSTOM_TS_Crossbar_Enum used to select the signal for TS1
  Parameter: ts1_mode,   a CUSTOM_TS_Mode_Enum     used to select the mode   for TS1
  Parameter: ts2_signal, a CUSTOM_TS_Crossbar_Enum used to select the signal for TS2
  Parameter: ts2_mode,   a CUSTOM_TS_Mode_Enum     used to select the mode   for TS2
    Possible ts1_signal/ts2_signal values are:
      SILABS_TS_CROSSBAR_TRISTATE      TSx output is set in tristate
      SILABS_TS_CROSSBAR_TS_A          TSx output is connected to TS_A
      SILABS_TS_CROSSBAR_TS_B          TSx output is connected to TS_B
    Possible ts1_mode/ts2_mode values are:
       SILABS_TS_GPIF
       SILABS_TS_OFF
       SILABS_TS_PARALLEL
       SILABS_TS_SERIAL
       SILABS_TS_TRISTATE
  Behavior:  first checks for potential conflicts in the required TS Crossbar settings.
            In case of conflict in the request, generate a clear SiTRACE describing the conflict,
              then switch both TS1 and TS2 to tristate.
            This is the best way to make sure that conflicts will be immediately detected and corrected
              at application level, since this will only occur during application development,
              until the crossbar management code is all OK.
            If there is no conflict, nicely go through the minimum set of commands to set both TS Crossbar signals as
              required for the application.
  Returns:    1 if successful, 0 otherwise
************************************************************************************************************************/
signed   int   SiLabs_TS_Crossbar_TS1_TS2         (SILABS_TS_Crossbar *ts_crossbar,
                                                   CUSTOM_TS_Crossbar_Enum  ts_1_signal,
                                                   CUSTOM_TS_Mode_Enum      ts_1_mode  ,
                                                   CUSTOM_TS_Crossbar_Enum  ts_2_signal,
                                                   CUSTOM_TS_Mode_Enum      ts_2_mode )
{
  unsigned char ts_1_source_set;
  unsigned char fe_A_pins_change;
  unsigned char fe_B_pins_change;
  SILABS_FE_Context *ts_1_source;
  SILABS_FE_Context *ts_2_source;
  ts_1_source = NULL;
  ts_2_source = NULL;
  SiTRACE("API CALL XBAR  : --------------------------------------------------------------------------------\n");
  SiTRACE("API CALL XBAR  : SiLabs_TS_Crossbar_TS1_TS2 (crossbar, %d, %d, %d, %d)\n", ts_1_signal, ts_1_mode, ts_2_signal, ts_2_mode);
  SiTRACE("SiLabs_TS_Crossbar_TS1_TS2 (crossbar, %s, %s, %s, %s)\n", SiLabs_TS_Crossbar_Signal_Text(ts_1_signal), Silabs_TS_Mode_Text(ts_1_mode), SiLabs_TS_Crossbar_Signal_Text(ts_2_signal), Silabs_TS_Mode_Text(ts_2_mode));

  if (ts_crossbar       == NULL) {SiERROR ("no ts_crossbar pointer!\n"      ); return 0; }
  if (ts_crossbar->fe_A == NULL) {SiERROR ("no ts_crossbar->fe_A pointer!\n"); return 0; }
  if (ts_crossbar->fe_B == NULL) {SiERROR ("no ts_crossbar->fe_B pointer!\n"); return 0; }

  if ( (ts_1_signal == ts_2_signal ) & (ts_1_signal != SILABS_TS_CROSSBAR_TRISTATE) ) {
    /* There is a conflict if TS1 and TS2 are set on the same signal in 2 different 'active' modes */
    if (ts_1_mode != ts_2_mode ) {
      if ( (ts_1_mode != SILABS_TS_TRISTATE ) & (ts_2_mode != SILABS_TS_TRISTATE ) ) {
        SiTRACE("Invalid XBAR configuration: %s can't be at the same time set to %s and %s!\n", SiLabs_TS_Crossbar_Signal_Text(ts_1_signal), Silabs_TS_Mode_Text(ts_1_mode), Silabs_TS_Mode_Text(ts_2_mode) );
        SiTRACE("Invalid XBAR configuration: both TS1 and TS2 forced to tristate!\n");
        SiERROR("Invalid XBAR configuration: both TS1 and TS2 forced to tristate!\n");
        return SiLabs_TS_Crossbar_TS1_TS2 (ts_crossbar, ts_1_signal, SILABS_TS_TRISTATE, ts_2_signal, SILABS_TS_TRISTATE );
      }
    }
  }

  ts_1_source_set     = 0;
  fe_A_pins_change    = 0;
  fe_B_pins_change    = 0;

  if (ts_crossbar->state_known == 0) {
    if (SiLabs_TS_Crossbar_TS_Status (ts_crossbar) == 1) {
      ts_crossbar->state_known = 1;
    }
  }

  SiTRACE ("TS_1 (%s/%s) -> (%s/%-8s)\n", SiLabs_TS_Crossbar_Signal_Text(ts_crossbar->ts_1_signal), Silabs_TS_Mode_Text(ts_crossbar->ts_1->ts_mode), SiLabs_TS_Crossbar_Signal_Text(ts_1_signal), Silabs_TS_Mode_Text(ts_1_mode) );
  SiTRACE ("TS_2 (%s/%s) -> (%s/%-8s)\n", SiLabs_TS_Crossbar_Signal_Text(ts_crossbar->ts_2_signal), Silabs_TS_Mode_Text(ts_crossbar->ts_2->ts_mode), SiLabs_TS_Crossbar_Signal_Text(ts_2_signal), Silabs_TS_Mode_Text(ts_2_mode) );

#ifdef    Si2183_COMPATIBLE
  if (ts_crossbar->fe_A->chip ==   0x2183 ) {
 #ifdef    Si2183_DD_TS_PINS_CMD
    if (ts_crossbar->fe_A->Si2183_FE->demod->rsp->get_rev.mcm_die  == Si2183_GET_REV_RESPONSE_MCM_DIE_SINGLE) {
      SiTRACE("Invalid XBAR use: the part is not a dual demodulator. TS Crossbar is only possible with dual demodulators !\n");
      SiERROR("Invalid XBAR use: the part is not a dual demodulator. TS Crossbar is only possible with dual demodulators !\n");
      return 0;
    }

    /* Check for TS1 signal changes and prepare to set it to tristate if active */
    if ( (ts_1_signal  != ts_crossbar->ts_1_signal) & (ts_crossbar->ts_1_signal  != SILABS_TS_CROSSBAR_TRISTATE) ) {
      if (ts_crossbar->fe_A->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_mode   != Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_NOT_USED   ) {
          ts_crossbar->fe_A->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_mode    = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_NOT_USED;
          SiTRACE ("Preparing to disable fe_A primary ts   (used for TS1)\n");
          fe_A_pins_change++;
      }
      if (ts_crossbar->fe_B->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_mode != Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_NOT_USED ) {
          ts_crossbar->fe_B->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_mode  = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_NOT_USED;
          SiTRACE ("Preparing to disable fe_B secondary ts (used for TS1)\n");
          fe_B_pins_change++;
      }
    }

    /* Check for TS2 signal changes and prepare to set it to tristate if active */
    if ( (ts_2_signal  != ts_crossbar->ts_2_signal) & (ts_crossbar->ts_2_signal  != SILABS_TS_CROSSBAR_TRISTATE) ) {
      if (ts_crossbar->fe_A->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_mode != Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_NOT_USED ) {
          ts_crossbar->fe_A->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_mode  = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_NOT_USED;
          SiTRACE ("Preparing to disable fe_A secondary ts (used for TS2)\n");
          fe_A_pins_change++;
      }
      if (ts_crossbar->fe_B->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_mode   != Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_NOT_USED   ) {
          ts_crossbar->fe_B->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_mode    = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_NOT_USED;
          SiTRACE ("Preparing to disable fe_B primary   ts (used for TS2)\n");
          fe_B_pins_change++;
      }
    }

    /* Tristate TS1 and/or TS2 on fe_A before changing on the source side   */
    if (fe_A_pins_change) {
      SiTRACE ("Disabling fe_A outputs\n");
      if (Si2183_L1_SendCommand2 (ts_crossbar->fe_A->Si2183_FE->demod, Si2183_DD_TS_PINS_CMD_CODE ) != NO_Si2183_ERROR) {
        SiTRACE ("TS Crossbar ERROR when changing fe_A DD_TS_PINS!\n");
        SiERROR ("TS Crossbar ERROR when changing fe_A DD_TS_PINS!\n");
        ts_crossbar->state_known = 0;
      }
    }

    /* Tristate TS1 and/or TS2 on fe_B before changing on the source side   */
    if (fe_B_pins_change) {
      SiTRACE ("Disabling fe_B outputs\n");
      if (Si2183_L1_SendCommand2 (ts_crossbar->fe_B->Si2183_FE->demod, Si2183_DD_TS_PINS_CMD_CODE ) != NO_Si2183_ERROR) {
        SiTRACE ("TS Crossbar ERROR when changing fe_B DD_TS_PINS!\n");
        SiERROR ("TS Crossbar ERROR when changing fe_B DD_TS_PINS!\n");
        ts_crossbar->state_known = 0;
      }
    }

    /* Selecting ts_1_source and prepare to enable it if required           */
           if (ts_1_signal == SILABS_TS_CROSSBAR_TS_A)     {
      ts_1_source = ts_crossbar->fe_A;
      SiTRACE("Preparing to enable fe_A (%s) primary TS\n", ts_crossbar->fe_A->tag);
      ts_crossbar->fe_A->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_mode    = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_DRIVE_TS;
    }
      else if (ts_1_signal == SILABS_TS_CROSSBAR_TS_B)     {
      SiTRACE("Preparing to enable fe_B (%s) secondary TS\n", ts_crossbar->fe_B->tag);
      ts_crossbar->fe_B->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_mode  = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_DRIVE_TS;
    }

    /* Selecting ts_2_source and prepare to enable it if required           */
           if (ts_2_signal == SILABS_TS_CROSSBAR_TS_B)     {
      SiTRACE("Preparing to enable fe_B (%s) primary TS\n", ts_crossbar->fe_B->tag);
      ts_crossbar->fe_B->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_mode    = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_DRIVE_TS;
    }
      else if (ts_2_signal == SILABS_TS_CROSSBAR_TS_A)     {
      SiTRACE("Preparing to enable fe_A (%s) secondary TS\n", ts_crossbar->fe_A->tag);
      ts_crossbar->fe_A->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_mode  = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_DRIVE_TS;
    }

    /* Setting source drive and strength values in ts_1_source if required   */
    if (ts_1_mode != SILABS_TS_TRISTATE) {
      if (ts_1_mode == SILABS_TS_SERIAL  ) {
        if (ts_1_signal == SILABS_TS_CROSSBAR_TS_A) {
          ts_1_source = ts_crossbar->fe_A;
          SiTRACE("Setting  TS_A (%s) primary   TS drives and strengths for serial (if not already set)\n", ts_1_source->tag);
          ts_1_source->Si2183_FE->demod->prop->dd_ts_setup_ser.ts_data_strength = ts_crossbar->ts_1->ts_serial_data_strength;
          ts_1_source->Si2183_FE->demod->prop->dd_ts_setup_ser.ts_data_shape    = ts_crossbar->ts_1->ts_serial_data_shape;
          ts_1_source->Si2183_FE->demod->prop->dd_ts_setup_ser.ts_clk_strength  = ts_crossbar->ts_1->ts_serial_clk_strength;
          ts_1_source->Si2183_FE->demod->prop->dd_ts_setup_ser.ts_clk_shape     = ts_crossbar->ts_1->ts_serial_clk_shape;
          Si2183_L1_SetProperty2(ts_1_source->Si2183_FE->demod, Si2183_DD_TS_SETUP_SER_PROP_CODE );
        }
        if (ts_1_signal == SILABS_TS_CROSSBAR_TS_B) {
          ts_1_source = ts_crossbar->fe_B;
          SiTRACE("Setting  TS_B (%s) secondary TS drives and strengths for serial (if not already set)\n", ts_1_source->tag);
          ts_1_source->Si2183_FE->demod->prop->dd_sec_ts_setup_ser.ts_data_strength = ts_crossbar->ts_1->ts_serial_data_strength;
          ts_1_source->Si2183_FE->demod->prop->dd_sec_ts_setup_ser.ts_data_shape    = ts_crossbar->ts_1->ts_serial_data_shape;
          ts_1_source->Si2183_FE->demod->prop->dd_sec_ts_setup_ser.ts_clk_strength  = ts_crossbar->ts_1->ts_serial_clk_strength;
          ts_1_source->Si2183_FE->demod->prop->dd_sec_ts_setup_ser.ts_clk_shape     = ts_crossbar->ts_1->ts_serial_clk_shape;
          Si2183_L1_SetProperty2(ts_1_source->Si2183_FE->demod, Si2183_DD_SEC_TS_SETUP_SER_PROP_CODE );
        }
        SiTRACE("Setting  ts_1 (%s) TS slr for serial (if not already set)\n", ts_1_source->tag);
        ts_1_source->Si2183_FE->demod->prop->dd_ts_slr_serial.ts_data_slr     = ts_crossbar->ts_1->ts_serial_data_slr;
        ts_1_source->Si2183_FE->demod->prop->dd_ts_slr_serial.ts_data_slr_on  = ts_crossbar->ts_1->ts_serial_slr_enable;
        ts_1_source->Si2183_FE->demod->prop->dd_ts_slr_serial.ts_data1_slr    = ts_crossbar->ts_1->ts_serial_data_slr;
        ts_1_source->Si2183_FE->demod->prop->dd_ts_slr_serial.ts_data1_slr_on = ts_crossbar->ts_1->ts_serial_slr_enable;
        ts_1_source->Si2183_FE->demod->prop->dd_ts_slr_serial.ts_data2_slr    = ts_crossbar->ts_1->ts_serial_data_slr;
        ts_1_source->Si2183_FE->demod->prop->dd_ts_slr_serial.ts_data2_slr_on = ts_crossbar->ts_1->ts_serial_slr_enable;
        ts_1_source->Si2183_FE->demod->prop->dd_ts_slr_serial.ts_clk_slr      = ts_crossbar->ts_1->ts_serial_clk_slr;
        ts_1_source->Si2183_FE->demod->prop->dd_ts_slr_serial.ts_clk_slr_on   = ts_crossbar->ts_1->ts_serial_slr_enable;
        Si2183_L1_SetProperty2(ts_1_source->Si2183_FE->demod, Si2183_DD_TS_SLR_SERIAL_PROP_CODE );
        SiTRACE("Setting  ts_1_source (%s) TS Mode to SERIAL (if not already set)\n", ts_1_source->tag);
        ts_1_source->Si2183_FE->demod->prop->dd_ts_mode.mode  = Si2183_DD_TS_MODE_PROP_MODE_SERIAL;
      }
      if (ts_1_mode == SILABS_TS_PARALLEL) {
        if (ts_1_signal == SILABS_TS_CROSSBAR_TS_A) {
          ts_1_source = ts_crossbar->fe_A;
          SiTRACE("Setting  TS_A (%s) primary   TS drives and strengths for parallel (if not already set)\n", ts_1_source->tag);
          ts_1_source->Si2183_FE->demod->prop->dd_ts_setup_par.ts_data_strength = ts_crossbar->ts_1->ts_parallel_data_strength;
          ts_1_source->Si2183_FE->demod->prop->dd_ts_setup_par.ts_data_shape    = ts_crossbar->ts_1->ts_parallel_data_shape;
          ts_1_source->Si2183_FE->demod->prop->dd_ts_setup_par.ts_clk_strength  = ts_crossbar->ts_1->ts_parallel_clk_strength;
          ts_1_source->Si2183_FE->demod->prop->dd_ts_setup_par.ts_clk_shape     = ts_crossbar->ts_1->ts_parallel_clk_shape;
          Si2183_L1_SetProperty2(ts_1_source->Si2183_FE->demod, Si2183_DD_TS_SETUP_PAR_PROP_CODE );
        }
        if (ts_1_signal == SILABS_TS_CROSSBAR_TS_B) {
          ts_1_source = ts_crossbar->fe_B;
          SiTRACE("Setting  TS_B (%s) secondary TS drives and strengths for parallel (if not already set)\n", ts_1_source->tag);
          ts_1_source->Si2183_FE->demod->prop->dd_sec_ts_setup_par.ts_data_strength = ts_crossbar->ts_1->ts_parallel_data_strength;
          ts_1_source->Si2183_FE->demod->prop->dd_sec_ts_setup_par.ts_data_shape    = ts_crossbar->ts_1->ts_parallel_data_shape;
          ts_1_source->Si2183_FE->demod->prop->dd_sec_ts_setup_par.ts_clk_strength  = ts_crossbar->ts_1->ts_parallel_clk_strength;
          ts_1_source->Si2183_FE->demod->prop->dd_sec_ts_setup_par.ts_clk_shape     = ts_crossbar->ts_1->ts_parallel_clk_shape;
          Si2183_L1_SetProperty2(ts_1_source->Si2183_FE->demod, Si2183_DD_SEC_TS_SETUP_PAR_PROP_CODE );
        }
        SiTRACE("Setting  ts_1_source (%s) TS Mode to PARALLEL\n", ts_1_source->tag);
        ts_1_source->Si2183_FE->demod->prop->dd_ts_mode.mode  = Si2183_DD_TS_MODE_PROP_MODE_PARALLEL;
      }
      Si2183_L1_SetProperty2(ts_1_source->Si2183_FE->demod,   Si2183_DD_TS_MODE_PROP_CODE );
    }

    /* Setting source drive and strength values in ts_2_source if required   */
    if (ts_2_mode != SILABS_TS_TRISTATE) {
      if (ts_2_mode == SILABS_TS_SERIAL  ) {
        if (ts_2_signal == SILABS_TS_CROSSBAR_TS_A) {
          ts_2_source = ts_crossbar->fe_A;
          SiTRACE("Setting  TS_A (%s) secondary TS drives and strengths for serial (if not already set)\n", ts_2_source->tag);
          ts_2_source->Si2183_FE->demod->prop->dd_sec_ts_setup_ser.ts_data_strength = ts_crossbar->ts_2->ts_serial_data_strength;
          ts_2_source->Si2183_FE->demod->prop->dd_sec_ts_setup_ser.ts_data_shape    = ts_crossbar->ts_2->ts_serial_data_shape;
          ts_2_source->Si2183_FE->demod->prop->dd_sec_ts_setup_ser.ts_clk_strength  = ts_crossbar->ts_2->ts_serial_clk_strength;
          ts_2_source->Si2183_FE->demod->prop->dd_sec_ts_setup_ser.ts_clk_shape     = ts_crossbar->ts_2->ts_serial_clk_shape;
          Si2183_L1_SetProperty2(ts_2_source->Si2183_FE->demod, Si2183_DD_SEC_TS_SETUP_SER_PROP_CODE );
        }
        if (ts_2_signal == SILABS_TS_CROSSBAR_TS_B) {
          ts_2_source = ts_crossbar->fe_B;
          SiTRACE("Setting  TS_B (%s) primary   TS drives and strengths for serial (if not already set)\n", ts_2_source->tag);
          ts_2_source->Si2183_FE->demod->prop->dd_ts_setup_ser.ts_data_strength = ts_crossbar->ts_2->ts_serial_data_strength;
          ts_2_source->Si2183_FE->demod->prop->dd_ts_setup_ser.ts_data_shape    = ts_crossbar->ts_2->ts_serial_data_shape;
          ts_2_source->Si2183_FE->demod->prop->dd_ts_setup_ser.ts_clk_strength  = ts_crossbar->ts_2->ts_serial_clk_strength;
          ts_2_source->Si2183_FE->demod->prop->dd_ts_setup_ser.ts_clk_shape     = ts_crossbar->ts_2->ts_serial_clk_shape;
          Si2183_L1_SetProperty2(ts_2_source->Si2183_FE->demod, Si2183_DD_TS_SETUP_SER_PROP_CODE );
        }
        SiTRACE("Setting  ts_2 (%s) TS slr for serial (if not already set)\n", ts_2_source->tag);
        ts_2_source->Si2183_FE->demod->prop->dd_ts_slr_serial.ts_data_slr     = ts_crossbar->ts_1->ts_serial_data_slr;
        ts_2_source->Si2183_FE->demod->prop->dd_ts_slr_serial.ts_data_slr_on  = ts_crossbar->ts_1->ts_serial_slr_enable;
        ts_2_source->Si2183_FE->demod->prop->dd_ts_slr_serial.ts_data1_slr    = ts_crossbar->ts_1->ts_serial_data_slr;
        ts_2_source->Si2183_FE->demod->prop->dd_ts_slr_serial.ts_data1_slr_on = ts_crossbar->ts_1->ts_serial_slr_enable;
        ts_2_source->Si2183_FE->demod->prop->dd_ts_slr_serial.ts_data2_slr    = ts_crossbar->ts_1->ts_serial_data_slr;
        ts_2_source->Si2183_FE->demod->prop->dd_ts_slr_serial.ts_data2_slr_on = ts_crossbar->ts_1->ts_serial_slr_enable;
        ts_2_source->Si2183_FE->demod->prop->dd_ts_slr_serial.ts_clk_slr      = ts_crossbar->ts_1->ts_serial_clk_slr;
        ts_2_source->Si2183_FE->demod->prop->dd_ts_slr_serial.ts_clk_slr_on   = ts_crossbar->ts_1->ts_serial_slr_enable;
        Si2183_L1_SetProperty2(ts_2_source->Si2183_FE->demod, Si2183_DD_TS_SLR_SERIAL_PROP_CODE );
        SiTRACE("Setting  ts_2_source (%s) TS Mode to SERIAL (if not already set)\n", ts_2_source->tag);
        ts_2_source->Si2183_FE->demod->prop->dd_ts_mode.mode  = Si2183_DD_TS_MODE_PROP_MODE_SERIAL;
      }
      if (ts_2_mode == SILABS_TS_PARALLEL) {
        if (ts_2_signal == SILABS_TS_CROSSBAR_TS_A) {
          ts_2_source = ts_crossbar->fe_A;
          SiTRACE("Setting  TS_A (%s) secondary TS drives and strengths for parallel (if not already set)\n", ts_2_source->tag);
          ts_2_source->Si2183_FE->demod->prop->dd_sec_ts_setup_par.ts_data_strength = ts_crossbar->ts_2->ts_parallel_data_strength;
          ts_2_source->Si2183_FE->demod->prop->dd_sec_ts_setup_par.ts_data_shape    = ts_crossbar->ts_2->ts_parallel_data_shape;
          ts_2_source->Si2183_FE->demod->prop->dd_sec_ts_setup_par.ts_clk_strength  = ts_crossbar->ts_2->ts_parallel_clk_strength;
          ts_2_source->Si2183_FE->demod->prop->dd_sec_ts_setup_par.ts_clk_shape     = ts_crossbar->ts_2->ts_parallel_clk_shape;
          Si2183_L1_SetProperty2(ts_2_source->Si2183_FE->demod, Si2183_DD_SEC_TS_SETUP_PAR_PROP_CODE );
        }
        if (ts_2_signal == SILABS_TS_CROSSBAR_TS_B) {
          ts_2_source = ts_crossbar->fe_B;
          SiTRACE("Setting  TS_B (%s) secondary TS drives and strengths for parallel (if not already set)\n", ts_2_source->tag);
          ts_2_source->Si2183_FE->demod->prop->dd_ts_setup_par.ts_data_strength = ts_crossbar->ts_2->ts_parallel_data_strength;
          ts_2_source->Si2183_FE->demod->prop->dd_ts_setup_par.ts_data_shape    = ts_crossbar->ts_2->ts_parallel_data_shape;
          ts_2_source->Si2183_FE->demod->prop->dd_ts_setup_par.ts_clk_strength  = ts_crossbar->ts_2->ts_parallel_clk_strength;
          ts_2_source->Si2183_FE->demod->prop->dd_ts_setup_par.ts_clk_shape     = ts_crossbar->ts_2->ts_parallel_clk_shape;
          Si2183_L1_SetProperty2(ts_2_source->Si2183_FE->demod, Si2183_DD_TS_SETUP_PAR_PROP_CODE );
        }
        SiTRACE("Setting  ts_2_source (%s) TS Mode to PARALLEL\n", ts_2_source->tag);
        ts_2_source->Si2183_FE->demod->prop->dd_ts_mode.mode  = Si2183_DD_TS_MODE_PROP_MODE_PARALLEL;
      }
      Si2183_L1_SetProperty2(ts_2_source->Si2183_FE->demod,   Si2183_DD_TS_MODE_PROP_CODE );
    }

    /* Enable TS1 after setting the TS output as required on the source side */
    if (ts_1_mode != SILABS_TS_TRISTATE) {
      SiTRACE("Enabling ts_1_source (%s) TS output\n", ts_1_source->tag);
      if (Si2183_L1_SendCommand2 (ts_1_source->Si2183_FE->demod, Si2183_DD_TS_PINS_CMD_CODE ) != NO_Si2183_ERROR) {
        SiTRACE ("TS Crossbar ERROR when changing ts_1_source (%s) DD_TS_PINS!\n", ts_1_source->tag);
        SiERROR ("TS Crossbar ERROR when changing ts_1_source DD_TS_PINS!\n");
        ts_crossbar->state_known = 0;
      }
      ts_1_source_set = 1;
    }

    /* Enable TS2 after setting the TS output as required on the source side */
    if (ts_2_mode != SILABS_TS_TRISTATE) {
      if ( (ts_1_source != ts_2_source) | (ts_1_source_set == 0) ) {
        SiTRACE("Enabling ts_2_source (%s) TS output\n", ts_2_source->tag);
        if (Si2183_L1_SendCommand2 (ts_2_source->Si2183_FE->demod, Si2183_DD_TS_PINS_CMD_CODE ) != NO_Si2183_ERROR) {
          SiTRACE ("TS Crossbar ERROR when changing ts_2_source (%s) DD_TS_PINS!\n", ts_2_source->tag);
          SiERROR ("TS Crossbar ERROR when changing ts_2_source DD_TS_PINS!\n");
          ts_crossbar->state_known = 0;
        }
      } else {
        SiTRACE("ts_2_source (%s) already enabled\n", ts_2_source->tag);
      }
    }

    if (ts_crossbar->state_known) {
      ts_crossbar->ts_1_signal   = ts_1_signal;
      ts_crossbar->ts_2_signal   = ts_2_signal;
      ts_crossbar->ts_1->ts_mode = ts_1_mode;
      ts_crossbar->ts_2->ts_mode = ts_2_mode;
    }

    SiLabs_TS_Crossbar_Status_Text (ts_crossbar);

    return 1;
 #endif /* Si2183_DD_TS_PINS_CMD */
  }
#endif /* Si2183_COMPATIBLE */
  SiERROR ("SiLabs_TS_Crossbar_TS2_Signal not supported by current part!\n");
  return 0;
}

#ifdef    __cplusplus
}
#endif /* __cplusplus */

#endif /* TS_CROSSBAR */
