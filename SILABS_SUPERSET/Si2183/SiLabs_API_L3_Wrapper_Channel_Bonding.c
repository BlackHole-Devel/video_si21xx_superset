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
/*                                  SiLabs API TS Bonding Functions                                          */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains TS Bonding API functions for dual SiLabs digital TV demodulators              */
/*-----------------------------------------------------------------------------------------------------------*/
/*************************************************************************************************************
 Use case with ONE_DUAL:
    SiLabs_Channel_Bonding_SW_Init         ( Channel_Bonding, fe[0], fe[1],  NULL,  NULL, X, X);
    SILABS_Channel_Bonding_Roles           ( Channel_Bonding, SILABS_ONE_DUAL,    SILABS_TS_1);
    SiLabs_API_lock_to_carrier             ( Channel_Bonding->slave,  SILABS_DVB_S2, freq_slave__kHz, 0, 0, symbol_rate_slave__bps, 0, polarization, band, 0, 0, 0);
    SiLabs_API_lock_to_carrier             ( Channel_Bonding->master, SILABS_DVB_S2, freq_master_kHz, 0, 0, symbol_rate_master_bps, 0, polarization, band, 0, 0, 0);
    SILABS_Channel_Bonding                 ( Channel_Bonding, SILABS_ONE_DUAL,    SILABS_TS_1);


 Use case with DUAL_DUAL:
    SILABS_Channel_Bonding_Config          ( Channel_Bonding, fe[0], fe[1], fe[2], fe[3],    SILABS_TS_2, SILABS_TS_1);
    SiLabs_Channel_Bonding_Roles           ( Channel_Bonding, SILABS_DUAL_DUAL,   X);
    SiLabs_API_switch_to_standard          ( Channel_Bonding->unused, SILABS_SLEEP, 0);
    SiLabs_API_lock_to_carrier             ( Channel_Bonding->slave,  SILABS_DVB_S2, freq_slave__kHz, 0, 0, symbol_rate_slave__bps, 0, polarization, band, 0, 0, 0);
    SiLabs_API_lock_to_carrier             ( Channel_Bonding->bridge, SILABS_DVB_S2, freq_bridge_kHz, 0, 0, symbol_rate_bridge_bps, 0, polarization, band, 0, 0, 0);
    SiLabs_API_lock_to_carrier             ( Channel_Bonding->master, SILABS_DVB_S2, freq_master_kHz, 0, 0, symbol_rate_master_bps, 0, polarization, band, 0, 0, 0);
    SILABS_Channel_Bonding                 ( Channel_Bonding, SILABS_DUAL_DUAL,   X);

 Use case with DUAL_SINGLE:
    SILABS_Channel_Bonding_Config          ( Channel_Bonding, fe[0], fe[1], fe[2],  NULL,    SILABS_TS_1, SILABS_TS_1);
    SiLabs_Channel_Bonding_Roles           ( Channel_Bonding, SILABS_DUAL_SINGLE, SILABS_TS_2);
    SiLabs_API_lock_to_carrier             ( Channel_Bonding->slave,  SILABS_DVB_S2, freq_slave__kHz, 0, 0, symbol_rate_slave__bps, 0, polarization, band, 0, 0, 0);
    SiLabs_API_lock_to_carrier             ( Channel_Bonding->bridge, SILABS_DVB_S2, freq_bridge_kHz, 0, 0, symbol_rate_bridge_bps, 0, polarization, band, 0, 0, 0);
    SiLabs_API_lock_to_carrier             ( Channel_Bonding->master, SILABS_DVB_S2, freq_master_kHz, 0, 0, symbol_rate_master_bps, 0, polarization, band, 0, 0, 0);
    SILABS_Channel_Bonding                 ( Channel_Bonding, SILABS_DUAL_SINGLE, SILABS_TS_2);

**************************************************************************************************************/
/* Change log: */
/* Last  changes:

  As from V2.7.5:
   <correction>[QUAD/pointer] In SiLabs_Channel_Bonding: pointer correction for 'unused' part.

  As from V2.7.4:
   <new_feature>[DUALs/Channel_Bonding] Initial version of Channel_Bonding (2016/07/08)

*/
/* Older changes:
 *************************************************************************************************************/
/* TAG V2.8.0 */

#ifndef   CHANNEL_BONDING
  "If you get a compilation error on this line, it means that you included the Channel_Bonding code in your project without defining CHANNEL_BONDING.";
  "Please define CHANNEL_BONDING at project-level (this is also used to include the CHANNEL_BONDING properties at L1 level), or remove the Channel_Bonding code from your project";
#endif /* CHANNEL_BONDING */

#ifdef    CHANNEL_BONDING

/* Before including the headers, define SiLevel and SiTAG */
#define   SiLEVEL          4
#define   SiTAG            "Bonding  "
#include "SiLabs_API_L3_Wrapper_Channel_Bonding.h"

SILABS_Channel_Bonding  Channel_Bonding_Context;

#ifdef    __cplusplus
extern "C" {
#endif /* __cplusplus */

/************************************************************************************************************************
  SILABS_Channel_Bonding_Config function
  Use:      Transport Stream Bonding Configuration function
            Used to fill the TS_bonding structure
  Parameter: Channel_Bonding, the SILABS_Channel_Bonding structure to fill
  Parameter: first_dual_die_A,  pointer to the frontend using Die A in the first  DUAL demodulator. NULL if not used (Should never be NULL when using TS bonding).
  Parameter: first_dual_die_B,  pointer to the frontend using Die B in the first  DUAL demodulator. NULL if not used (Should never be NULL when using TS bonding).
  Parameter: second_dual_die_A, pointer to the frontend using Die A in the second DUAL demodulator. NULL if not used
  Parameter: second_dual_die_B, pointer to the frontend using Die B in the second DUAL demodulator. NULL if not used
  Parameter: first_dual_output, the TS output from the first DUAL, when bonding 2 or 3 TS.
    Hardware related.
    Possible values: 0:not_used,  1:TS1,  2:TS2 (X for DUAL_DUAL)
  Parameter: second_dual_input, the TS input on the second DUAL (which is receiving the bonded TS from the first DUAL), when bonding 3 TS.
    Hardware related.
    Possible values: 0:not_used,  1:TS1,  2:TS2 (X for DUAL_DUAL)
************************************************************************************************************************/
signed   int   SiLabs_Channel_Bonding_SW_Init    (SILABS_Channel_Bonding       *Channel_Bonding
                                                , SILABS_FE_Context            *first_dual_die_A
                                                , SILABS_FE_Context            *first_dual_die_B
                                                , SILABS_FE_Context            *second_dual_die_A
                                                , SILABS_FE_Context            *second_dual_die_B
                                                , SILABS_TS_BUS                 first_dual_output
                                                , SILABS_TS_BUS                 second_dual_input
                                                 ) {
  signed   int i;
  SILABS_FE_Context           *fe[4];

  SiTRACE_X("SiLabs_Channel_Bonding_SW_Init  first_dual_die_A(0x%08x), first_dual_die_B(0x%08x), second_dual_die_A(0x%08x), second_dual_die_B(0x%08x), first_dual_output %d, second_dual_input %d\n"
                                       ,(int)first_dual_die_A,    (int)first_dual_die_B,    (int)second_dual_die_A,    (int)second_dual_die_B,         first_dual_output,    second_dual_input);

  fe[0] = first_dual_die_A;
  fe[1] = first_dual_die_B;
  fe[2] = second_dual_die_A;
  fe[3] = second_dual_die_B;

  Channel_Bonding = &Channel_Bonding_Context;

  Channel_Bonding->nbFEs = 0;

  Channel_Bonding->fe[0] = first_dual_die_A;
  Channel_Bonding->fe[1] = first_dual_die_B;
  Channel_Bonding->fe[2] = second_dual_die_A;
  Channel_Bonding->fe[3] = second_dual_die_B;

  if (Channel_Bonding->fe[0] != NULL) { Channel_Bonding->nbFEs++; }
  if (Channel_Bonding->fe[1] != NULL) { Channel_Bonding->nbFEs++; }
  if (Channel_Bonding->fe[2] != NULL) { Channel_Bonding->nbFEs++; }
  if (Channel_Bonding->fe[3] != NULL) { Channel_Bonding->nbFEs++; }

  Channel_Bonding->first_dual_output = first_dual_output;
  Channel_Bonding->second_dual_input = second_dual_input;

  SiTRACE_X("SiLabs_Channel_Bonding_SW_Init Channel_Bonding->nbFEs %d\n", Channel_Bonding->nbFEs);

  return Channel_Bonding->nbFEs;
}

/************************************************************************************************************************
  SiLabs_Channel_Bonding_HW_Checks function
  Use:      Used by SiLabs_Channel_Bonding to avoid using the channel bonding when the HW doesn't support it
              and provide meaningfull traces during the checks.
  Parameter: Channel_Bonding, the SILABS_Channel_Bonding structure (previously filled using SiLabs_Channel_Bonding_SW_Init)
************************************************************************************************************************/
signed   int   SiLabs_Channel_Bonding_HW_Checks  (SILABS_Channel_Bonding       *Channel_Bonding) {
  signed   int i;

  for (i=0; i<4; i++) {
    if (Channel_Bonding->fe[i] != NULL) {
      if (Channel_Bonding->fe[i]->Si2183_FE->first_init_done == 0) {
        SiTRACE("!! SiLabs_Channel_Bonding_HW_Checks: fe[%d] is declared but not initialised yet (no FW downloaded), so TS bonding can't be used yet!\n", i);
        SiERROR("!! SiLabs_Channel_Bonding_HW_Checks: some FEs are declared but not initialised yet (no FW downloaded), so TS bonding can't be used yet!\n");
        return -1;
      }
      if (Channel_Bonding->fe[i]->Si2183_FE->demod->rsp->get_rev.mcm_die == 0) {
        SiTRACE("!! SiLabs_Channel_Bonding_HW_Checks: fe[%d] is declared but is not  a DUAL part.  TS bonding is only available for DUAL packages!\n", i);
        SiERROR("!! some FEs are declared but are not   DUAL parts. TS bonding is only available for DUAL packages!\n");
        return -2;
      }
      if ( (i%2 == 0) && (Channel_Bonding->fe[i]->Si2183_FE->demod->rsp->get_rev.mcm_die != Si2183_GET_REV_RESPONSE_MCM_DIE_DIE_A) ) {
        SiTRACE("!! SiLabs_Channel_Bonding_HW_Checks: fe[%d] is declared but is not a die A. Please check the order of the pointers you provided!\n", i);
        SiERROR("!! some fe   is declared but is not a die A. Please check the order of the pointers you provided!\n");
        return -3;
      }
      if ( (i%2 == 1) && (Channel_Bonding->fe[i]->Si2183_FE->demod->rsp->get_rev.mcm_die != Si2183_GET_REV_RESPONSE_MCM_DIE_DIE_B) ) {
        SiTRACE("!! SiLabs_Channel_Bonding_HW_Checks: fe[%d] is declared but is not a die B. Please check the order of the pointers you provided!\n", i);
        SiERROR("!! some fe   is declared but is not a die B. Please check the order of the pointers you provided!\n");
        return -4;
      }
    }
  }
  return 0;
}

/************************************************************************************************************************
  SiLabs_Channel_Bonding_Stop function
  Use:      Transport Stream Bonding de-activation function
            Used to go back to a non-bonding state
  Parameter: Channel_Bonding, the SILABS_Channel_Bonding structure (previously filled using SiLabs_Channel_Bonding_SW_Init)
  Parameter: parts,  the HW configuration used for bonding
    Possible values: 2:ONE_DUAL,  3:DUAL_SINGLE,  4:DUAL_DUAL
  Parameter: TS_output, the TS input on the first DUAL
    Hardware related.
    Possible values: 0:not_used,  1:TS1,  2:TS2  (only in DUAL_DUAL configuration, otherwise X).
************************************************************************************************************************/
signed   int   SiLabs_Channel_Bonding_Stop       (SILABS_Channel_Bonding       *Channel_Bonding) {
  signed   int i;
  if (Channel_Bonding       == NULL) {
    SiERROR ("no Channel_Bonding pointer!\n"      ); return 0;
  }
  for (i=0; i<4; i++) {
    if (Channel_Bonding->fe[i] != NULL) {
      Channel_Bonding->fe[i]->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_dir        = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_DIR_OUTPUT;
      Channel_Bonding->fe[i]->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_mode       = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_NOT_USED;
      Channel_Bonding->fe[i]->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_mode         = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_NOT_USED;
      Channel_Bonding->fe[i]->Si2183_FE->demod->cmd->dd_ts_pins.demod_role              = Si2183_DD_TS_PINS_CMD_DEMOD_ROLE_CHANNEL_BONDING_OFF;
      Si2183_L1_SendCommand2 (Channel_Bonding->fe[i]->Si2183_FE->demod, Si2183_DD_TS_PINS_CMD_CODE);

      Channel_Bonding->fe[i]->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_dir          = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_DIR_OUTPUT;
      Channel_Bonding->fe[i]->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_mode         = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_DRIVE_TS;
      Si2183_L1_SendCommand2 (Channel_Bonding->fe[i]->Si2183_FE->demod, Si2183_DD_TS_PINS_CMD_CODE);

      Si2183_L1_DD_RESTART   (Channel_Bonding->fe[i]->Si2183_FE->demod);
    }
  }
  return 0;
}

/************************************************************************************************************************
  SiLabs_Channel_Bonding_Roles function
  Use:      Transport Stream Bonding roles allocation function
            Called by SILABS_Channel_Bonding to allocate the roles (slave/bridge/master) depending on the HW confiuration
            Can also be used by the application to set up the Channel_Bonding->(slave/bridge/master) pointers before locking on the corresponding channels
  Parameter: Channel_Bonding, the SILABS_Channel_Bonding structure (previously filled using SiLabs_Channel_Bonding_SW_Init)
  Parameter: parts,  the HW configuration used for bonding
    Possible values: 2:ONE_DUAL,  3:DUAL_SINGLE,  4:DUAL_DUAL
  Parameter: TS_output, the TS input on the first DUAL
    Hardware related.
    Possible values: 0:not_used,  1:TS1,  2:TS2  (only in DUAL_DUAL configuration, otherwise X).
************************************************************************************************************************/
signed   int   SiLabs_Channel_Bonding_Roles      (SILABS_Channel_Bonding       *Channel_Bonding
                                                , SILABS_Channel_Bonding_Parts  parts
                                                , SILABS_TS_BUS                 TS_output ) {
  int i;
  int slave_index;
  int bridge_index;
  int master_index;
  int unused_index;
  SiTRACE("SiLabs_Channel_Bonding_Roles   parts %d  TS_output %d\n", parts, TS_output);

  if (Channel_Bonding       == NULL) {
    SiTRACE ("no Channel_Bonding pointer!\n"      );
    SiERROR ("no Channel_Bonding pointer!\n"      ); return -1;
  }

  i = 0;

  Channel_Bonding->slave  = NULL;
  Channel_Bonding->master = NULL;
  Channel_Bonding->bridge = NULL;
  Channel_Bonding->unused = NULL;

  switch (parts) {
    case SILABS_ONE_DUAL   : {
      SiTRACE("SILABS_Channel_Bonding_Roles   SILABS_ONE_DUAL\n");
      switch (TS_output) {
        case SILABS_TS_1: {
          Channel_Bonding->first_dual_output = SILABS_TS_1;
          /* TS_output on TS_1: Die B is the slave, Die A is the master */
          slave_index  = 1;
          master_index = 0;
          break;
        }
        case SILABS_TS_2: {
          Channel_Bonding->first_dual_output = SILABS_TS_2;
          /* TS_output on TS_2: Die A is the slave, Die B is the master */
          slave_index  = 0;
          master_index = 1;
          break;
        }
        default         : {
          SiTRACE  ("SILABS_Channel_Bonding_Roles   Incorrect TS_output value %d!\n", TS_output);
          SiERROR  ("SILABS_Channel_Bonding_Roles   Incorrect TS_output value!\n");
          break;
        }
      }
      Channel_Bonding->slave  = Channel_Bonding->fe[slave_index ]; i++;
      Channel_Bonding->master = Channel_Bonding->fe[master_index]; i++;

      break;
    }
    case SILABS_DUAL_SINGLE: {
      SiTRACE("SiLabs_Channel_Bonding_Roles   SILABS_DUAL_SINGLE\n");
      SiTRACE("SiLabs_Channel_Bonding_Roles   Interconnection from TS_%d to TS_%d\n", Channel_Bonding->first_dual_output, Channel_Bonding->second_dual_input);
      switch (Channel_Bonding->first_dual_output) {
        case SILABS_TS_1: {
          /* first_dual_output on TS_1 (first DUAL): Die A is the bridge, Die B is the slave */
          slave_index  = 1;
          bridge_index = 0;
          break;
        }
        case SILABS_TS_2: {
          /* first_dual_output on TS_2 (first DUAL): Die B is the bridge, Die A is the slave */
          slave_index  = 0;
          bridge_index = 1;
          break;
        }
        default         : {
          SiTRACE  ("SiLabs_Channel_Bonding_Roles   Incorrect first_dual_output value %d!\n", Channel_Bonding->first_dual_output);
          SiERROR  ("SiLabs_Channel_Bonding_Roles   Incorrect first_dual_output value!\n");
          return -1;
          break;
        }
      }
      Channel_Bonding->slave  = Channel_Bonding->fe[slave_index ]; i++;
      Channel_Bonding->bridge = Channel_Bonding->fe[bridge_index]; i++;

      master_index  = 2;
      Channel_Bonding->master = Channel_Bonding->fe[master_index]; i++;

      break;
    }
    case SILABS_DUAL_DUAL  : {
      SiTRACE("SiLabs_Channel_Bonding_Roles   SILABS_DUAL_DUAL\n");
      SiTRACE("SiLabs_Channel_Bonding_Roles   Interconnection from TS_%d to TS_%d\n", Channel_Bonding->first_dual_output, Channel_Bonding->second_dual_input);
      switch (Channel_Bonding->first_dual_output) {
        case SILABS_TS_1: {
          /* first_dual_output on TS_1 (first DUAL): Die A is the bridge, Die B is the slave */
          slave_index  = 1;
          bridge_index = 0;
          break;
        }
        case SILABS_TS_2: {
          /* first_dual_output on TS_2 (first DUAL): Die B is the bridge, Die A is the slave */
          slave_index  = 0;
          bridge_index = 1;
          break;
        }
        default         : {
          SiTRACE  ("SiLabs_Channel_Bonding_Roles   Incorrect first_dual_output value %d!\n", Channel_Bonding->first_dual_output);
          SiERROR  ("SiLabs_Channel_Bonding_Roles   Incorrect first_dual_output value!\n");
          return -1;
          break;
        }
      }
      Channel_Bonding->slave  = Channel_Bonding->fe[slave_index ]; i++;
      Channel_Bonding->bridge = Channel_Bonding->fe[bridge_index]; i++;

      switch (Channel_Bonding->second_dual_input) {
        case SILABS_TS_1: {
          /* second_dual_input on TS_1 (second DUAL): Die B is the master, Die A is unused */
          master_index = 3;
          unused_index = 2;
          break;
        }
        case SILABS_TS_2: {
          /* second_dual_input on TS_2 (second DUAL): Die A is the master, Die B is unused */
          master_index = 2;
          unused_index = 3;
          break;
        }
        default         : {
          SiTRACE  ("SiLabs_Channel_Bonding_Roles   Incorrect second_dual_input value %d!\n", Channel_Bonding->second_dual_input);
          SiERROR  ("SiLabs_Channel_Bonding_Roles   Incorrect second_dual_input value!\n");
          return -2;
          break;
        }
      }
      Channel_Bonding->master = Channel_Bonding->fe[master_index ]; i++;
      Channel_Bonding->unused = Channel_Bonding->fe[unused_index ]; i++;

      break;
    }
    default                : {
      SiTRACE  ("SiLabs_Channel_Bonding_Roles   parts value %d!\n", parts);
      SiERROR  ("SiLabs_Channel_Bonding_Roles   parts value!\n");
      return -4;
      break;
    }
  }
  if (i==2) { SiTRACE("SILABS_Channel_Bonding_Roles   (slave)fe[%d]->(master)fe[%d]->TS_%d\n",                         slave_index, master_index, Channel_Bonding->first_dual_output); }
  if (i==3) { SiTRACE("SILABS_Channel_Bonding_Roles   (slave)fe[%d]->(bridge)fe[%d]->TS_%d->TS_%d->(master)fe[%d]\n" , slave_index, bridge_index, Channel_Bonding->first_dual_output, Channel_Bonding->second_dual_input, master_index); }
  return i;
}

/************************************************************************************************************************
  SILABS_Channel_Bonding function
  Use:      Transport Stream Bonding activation function
            Used to start the channel bonding feature
  Parameter: Channel_Bonding, the SILABS_Channel_Bonding structure (previously filled using SiLabs_Channel_Bonding_SW_Init)
  Parameter: parts,  the HW configuration used for bonding
    Possible values: 2:ONE_DUAL,  3:DUAL_SINGLE,  4:DUAL_DUAL
  Parameter: TS_output, the TS input on the first DUAL
    Hardware related.
    Possible values: 0:not_used,  1:TS1,  2:TS2  (only in DUAL_DUAL configuration, otherwise X).
************************************************************************************************************************/
signed   int   SiLabs_Channel_Bonding            (SILABS_Channel_Bonding       *Channel_Bonding
                                                , SILABS_Channel_Bonding_Parts  parts
                                                , SILABS_TS_BUS                 TS_output ) {
  int i;
  SiTRACE("SILABS_Channel_Bonding         parts %d  TS_output %d\n", parts, TS_output);

  if (Channel_Bonding       == NULL) {
    SiERROR ("no Channel_Bonding pointer!\n"      ); return -1;
  }
  if (SiLabs_Channel_Bonding_HW_Checks(Channel_Bonding) != 0) {
    SiERROR ("There are Channel_Bonding errors!\n"); return -2;
  }

  i = SiLabs_Channel_Bonding_Roles    (Channel_Bonding , parts, TS_output );

  switch (parts) {
    default                :
    case SILABS_ONE_DUAL   : {
      SiTRACE("SILABS_Channel_Bonding         SILABS_ONE_DUAL\n");
      if (i != 2) {
        SiERROR("SILABS_Channel_Bonding         Incorrect number of roles defined!\n");
        return -20;
      }
      break;
    }
    case SILABS_DUAL_SINGLE: {
      SiTRACE_X("SILABS_Channel_Bonding       SILABS_DUAL_SINGLE\n");
      if (i <  3) {
        SiERROR("SILABS_Channel_Bonding         Incorrect number of roles defined!\n");
        return -30;
      }
      if (i >= 3) {
        if (Channel_Bonding->second_dual_input == TS_output) {
          SiERROR("SILABS_Channel_Bonding         for DUAL_SINGLE mode, TS_output must be different from second_dual_input!\n");
          return -41;
        }
      }
      break;
    }
    case SILABS_DUAL_DUAL  : {
      SiTRACE_X("SILABS_Channel_Bonding       SILABS_DUAL_DUAL\n");
      if (i <  3) {
        SiERROR("SILABS_Channel_Bonding         Incorrect number of roles defined!\n");
        return -40;
      }
      if (i >= 3) {
        if (Channel_Bonding->second_dual_input == TS_output) {
          SiERROR("SILABS_Channel_Bonding         for DUAL_DUAL mode, TS_output must be different from second_dual_input!\n");
          return -41;
        }
      }
      break;
    }
  }

  if (i == 4) { SiTRACE("SILABS_Channel_Bonding       setting the UNUSED  (not used  in  TS flow)\n");
    if (Channel_Bonding->unused->Si2183_FE->standard != SILABS_SLEEP) {
      Channel_Bonding->unused->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_activity     = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_ACTIVITY_CLEAR;
      Channel_Bonding->unused->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_activity   = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_ACTIVITY_CLEAR;
      Channel_Bonding->unused->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_mode         = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_NOT_USED;
      Channel_Bonding->unused->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_mode       = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_NOT_USED;
      Channel_Bonding->unused->Si2183_FE->demod->cmd->dd_ts_pins.demod_role              = Si2183_DD_TS_PINS_CMD_DEMOD_ROLE_CHANNEL_BONDING_OFF;
      Si2183_L1_SendCommand2 (Channel_Bonding->unused->Si2183_FE->demod, Si2183_DD_TS_PINS_CMD_CODE);

      Si2183_L1_DD_RESTART   (Channel_Bonding->unused->Si2183_FE->demod);
    }
  }

  if (i >  1) { SiTRACE("SILABS_Channel_Bonding       setting the SLAVE   (source of the TS flow)\n");
    SiLabs_API_TS_Strength_Shape (Channel_Bonding->slave, 100, 100, 4, 100);

    Channel_Bonding->slave->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_activity     = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_ACTIVITY_CLEAR;
    Channel_Bonding->slave->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_activity   = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_ACTIVITY_CLEAR;
    Channel_Bonding->slave->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_mode         = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_NOT_USED;
    Channel_Bonding->slave->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_mode       = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_NOT_USED;
    Si2183_L1_SendCommand2 (Channel_Bonding->slave->Si2183_FE->demod, Si2183_DD_TS_PINS_CMD_CODE);
    Si2183_L1_DD_RESTART   (Channel_Bonding->slave->Si2183_FE->demod);

    Channel_Bonding->slave->Si2183_FE->demod->cmd->dd_ts_pins.demod_role              = Si2183_DD_TS_PINS_CMD_DEMOD_ROLE_SLAVE;
    Channel_Bonding->slave->Si2183_FE->demod->cmd->dd_ts_pins.master_freq             = Channel_Bonding->master->Si2183_FE->demod->prop->dvbs2_symbol_rate.rate;

    Channel_Bonding->slave->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_dir          = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_DIR_OUTPUT;
    Channel_Bonding->slave->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_mode         = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_DRIVE_TS;
    Si2183_L1_SendCommand2 (Channel_Bonding->slave->Si2183_FE->demod, Si2183_DD_TS_PINS_CMD_CODE);

  }

  if (i >= 3) { SiTRACE("SILABS_Channel_Bonding       setting the BRIDGE  (middle of the TS flow)\n");
    SiLabs_API_TS_Strength_Shape (Channel_Bonding->bridge, 100, 100, 4, 100);

    Channel_Bonding->bridge->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_activity     = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_ACTIVITY_CLEAR;
    Channel_Bonding->bridge->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_activity   = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_ACTIVITY_CLEAR;
    Channel_Bonding->bridge->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_mode         = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_NOT_USED;
    Channel_Bonding->bridge->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_mode       = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_NOT_USED;
    Si2183_L1_SendCommand2 (Channel_Bonding->bridge->Si2183_FE->demod, Si2183_DD_TS_PINS_CMD_CODE);
    Si2183_L1_DD_RESTART   (Channel_Bonding->master->Si2183_FE->demod);

    Channel_Bonding->bridge->Si2183_FE->demod->cmd->dd_ts_pins.demod_role              = Si2183_DD_TS_PINS_CMD_DEMOD_ROLE_SLAVE_BRIDGE;
    Channel_Bonding->bridge->Si2183_FE->demod->cmd->dd_ts_pins.master_freq             = Channel_Bonding->master->Si2183_FE->demod->prop->dvbs2_symbol_rate.rate;

    Channel_Bonding->bridge->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_mode       = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_NO_CHANGE;
    Channel_Bonding->master->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_dir          = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_DIR_OUTPUT;
    Channel_Bonding->bridge->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_mode         = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_DRIVE_TS;
    Si2183_L1_SendCommand2 (Channel_Bonding->bridge->Si2183_FE->demod, Si2183_DD_TS_PINS_CMD_CODE);

    Channel_Bonding->bridge->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_dir        = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_DIR_INPUT;
    Channel_Bonding->bridge->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_mode       = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_DRIVE_TS;
    Si2183_L1_SendCommand2 (Channel_Bonding->bridge->Si2183_FE->demod, Si2183_DD_TS_PINS_CMD_CODE);
  }

  if (i >  1) { SiTRACE("SILABS_Channel_Bonding       setting the MASTER  (end    of the TS flow)\n");
    SiLabs_API_TS_Strength_Shape (Channel_Bonding->master, 100, 100, 4, 100);

    Channel_Bonding->master->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_activity     = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_ACTIVITY_CLEAR;
    Channel_Bonding->master->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_activity   = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_ACTIVITY_CLEAR;
    Channel_Bonding->master->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_mode         = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_NOT_USED;
    Channel_Bonding->master->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_mode       = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_NOT_USED;
    Si2183_L1_SendCommand2 (Channel_Bonding->master->Si2183_FE->demod, Si2183_DD_TS_PINS_CMD_CODE);
    Si2183_L1_DD_RESTART   (Channel_Bonding->master->Si2183_FE->demod);

    Channel_Bonding->master->Si2183_FE->demod->cmd->dd_ts_pins.demod_role              = Si2183_DD_TS_PINS_CMD_DEMOD_ROLE_MASTER;
    Channel_Bonding->master->Si2183_FE->demod->cmd->dd_ts_pins.master_freq             = Channel_Bonding->master->Si2183_FE->demod->prop->dvbs2_symbol_rate.rate;

    if ( (parts == SILABS_DUAL_SINGLE) && (Channel_Bonding->second_dual_input == SILABS_TS_2) ) {
      Channel_Bonding->master->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_mode         = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_NO_CHANGE;

      Channel_Bonding->master->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_dir        = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_DIR_OUTPUT;
      Channel_Bonding->master->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_mode       = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_DRIVE_TS;
    }
    else {
      Channel_Bonding->master->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_mode       = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_NO_CHANGE;

      Channel_Bonding->master->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_dir          = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_DIR_OUTPUT;
      Channel_Bonding->master->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_mode         = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_DRIVE_TS;
    }
    Si2183_L1_SendCommand2 (Channel_Bonding->master->Si2183_FE->demod, Si2183_DD_TS_PINS_CMD_CODE);

    if ( (parts == SILABS_DUAL_SINGLE) && (Channel_Bonding->second_dual_input == SILABS_TS_2) ) {
      Channel_Bonding->master->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_dir          = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_DIR_INPUT;
      Channel_Bonding->master->Si2183_FE->demod->cmd->dd_ts_pins.primary_ts_mode         = Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_DRIVE_TS;
    }
    else {
      Channel_Bonding->master->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_dir        = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_DIR_INPUT;
      Channel_Bonding->master->Si2183_FE->demod->cmd->dd_ts_pins.secondary_ts_mode       = Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_DRIVE_TS;
    }
    Si2183_L1_SendCommand2 (Channel_Bonding->master->Si2183_FE->demod, Si2183_DD_TS_PINS_CMD_CODE);

  }

  return i;
}

#ifdef    __cplusplus
}
#endif /* __cplusplus */

#endif /* CHANNEL_BONDING */
