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
/*                                  SiLabs API Configuration Macros                                          */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code calls macros allowing easy initialization of SiLabs EVBs                               */
/*    Part-specific macros are defined in the Si21--_L2_API.h file for the part                              */
/*    A 'quad' macro example is defined in SIlabs_API_L3_Config_Macros.h                                     */
/*    These can be used as a example for any new design                                                      */
/*-----------------------------------------------------------------------------------------------------------*/
/* Change log: */
/* Last  changes:

 As from V2.7.9:
   <correction>[traces/tag] Changing the definition of SiTAG to an empty string to allow using SiTRACE in this part of the code.
 
 As from V2.6.2:
  Adding macros:
   DTV_DUAL_TER_SAT_51A
  <compatibility>[No TER] In SiLabs_SW_config_from_macro: using TER_Tuner_count only if compiled for TERRESTRIAL

 As from V2.5.6:
  Adding macros:
   RX_SOCKET_EVB_Rev1_0_647C
   RX_SOCKET_EVB_Rev1_0_817B
   RX_SOCKET_EVB_Rev1_0_804B

 As from V2.5.3:
  Adding macros:
   Si2141_51_DVBT2TC_DC_Rev1_2_Si2168C
   Si2166B_EVB_Rev1_0_66B

 As from V2.5.1:
   Adding calls to SiLabs_API_TER_Tuner_FEF_Input to all macros for TER configurations (by default FE input set on GPIO1)

 As from V2.5.0:
  Renaming macros:
   Si21682_EVB_Rev1_0_Si2164    becomes  Si21682_EVB_Rev1_0_41A_64A
   Si21682_EVB_Rev1_0_Si21652B  becomes  Si21682_EVB_Rev1_0_41A_67B
   Si21682_EVB_Rev1_0_Si2183    becomes  Si21682_EVB_Rev1_0_41A_83A
   Si21662_EVB_Rev1_0_Si2167B   becomes  Si21662_EVB_Rev1_0_67B

 As from V2.4.6:
  Adding macros for EVBs with Airoha tuners
  For dual/triple/quad: Setting clock_control field to '1' to avoid glitches on other front-ends when changing the clock source.

 As from V2.3.9:
   Renaming/adding config macros to differentiate SOC EVB with Si2178 vs Si2178B

  As from V2.3.7:
   <new_feature> [TAG/LEVEL] Adding definitions for TAG and level
   <new_parts> [Si2183] Adding macros for Si2183

  As from V2.3.6:
   <new_feature> [config_macros] Using SiLabs_API_Frontend_Chip / SiLabs_API_TER_tuner_I2C_connection / SiLabs_API_SAT_tuner_I2C_connection
                 functions now that they are available in the wrapper code.
   <new_feature> [Airoha] Adding Si216x_SOC_EVB_Rev1_0_Si2164_Airoha, for test with Airoha tuners

  As from V2.3.5:
   Adding SW_INIT_Si216x2_EVB_Rev2_0_Si2164
   In SiLabs_SW_config_possibilities: sorting macros by 'single/dual/triple/quad',
    with separators, to make finding the proper macro easier in long lists

  As from V2.2.9:
   Adding Si216x2_EVB_Rev1_x_Si2164 macro, for Dual EVB using Si2164 source code

  As from V2.2.8:
   Initial version, with current SiLabs EVBs as from 2013/09/09

*/
/* TAG V2.8.0 */

/* Before including the headers, define SiLevel and SiTAG */
#define   SiLEVEL          3
#define   SiTAG            ""

#define   MACROS_FOR_SINGLE_FRONTENDS
#define   MACROS_FOR_DUAL_FRONTENDS
#define   MACROS_FOR_TRIPLE_FRONTENDS
#define   MACROS_FOR_QUAD_FRONTENDS

#include "SiLabs_API_L3_Config_Macros.h"

extern SILABS_FE_Context    *front_end;
#ifdef    USB_Capability
extern L0_Context* WrapperI2C;
extern L0_Context  WrapperI2C_context;
#endif /* USB_Capability */

#ifdef    __cplusplus
extern "C" {
#endif /* __cplusplus */

/************************************************************************************************************************
  SiLabs_SW_config_from_macro function
  Use:        automatic SW configuration function
              Used to init the SW based on pre-recorder macros
  Returns:    0 if no matching macros is found
************************************************************************************************************************/
signed   int   SiLabs_SW_config_from_macro     (char *macro_name)    {
  SiTRACE("SW configuration attempt for  '%s' ...\n", macro_name);
#ifdef    USB_Capability
  /* Disabling all Cypress ports except PA0, which needs to be driven to 0 to avoid TS conflicts */
  WrapperI2C = &WrapperI2C_context;
  L0_Connect   (WrapperI2C,    USB);
  front_end = &(FrontEnd_Table[0]);
  SiLabs_API_Cypress_Ports            (front_end, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00);
#endif /* USB_Capability */

#ifdef    SILABS_TER_TUNER_API
  TER_Tuner_count = 0;
#endif /* SILABS_TER_TUNER_API */

#ifdef    SELECT_MACRO_FOR_SILABS_EVBs
          SELECT_MACRO_FOR_SILABS_EVBs
#endif /* SELECT_MACRO_FOR_SILABS_EVBs */

#ifdef    MACROS_FOR_SINGLE_FRONTENDS
 #ifdef    SW_INIT_Si2166B_AV2018
  if ( strcmp_nocase( macro_name, "Si2166B_AV2018"            )==0) { SW_INIT_Si2166B_AV2018;          return   0x2167B;  }
 #endif /* SW_INIT_Si2166B_AV2018 */
 #ifdef    SW_INIT_Si2176_DVBTC_DC_Rev1_0
  if ( strcmp_nocase( macro_name, "Si2176_DVBTC_DC_Rev1_0"    )==0) { SW_INIT_Si2176_DVBTC_DC_Rev1_0;          return   2165;  }
 #endif /* SW_INIT_Si2176_DVBTC_DC_Rev1_0 */
 #ifdef    SW_INIT_Si216x_EVB_Rev3_0_Si2164
  if ( strcmp_nocase( macro_name, "Si216x_EVB_Rev3_0_Si2164"          )==0) { SW_INIT_Si216x_EVB_Rev3_0_Si2164;        return 0x2164;  }
 #endif /* SW_INIT_Si216x_EVB_Rev3_0_Si2164 */
 #ifdef    SW_INIT_Si216x_EVB_Rev3_0_Si2167B
  if ( strcmp_nocase( macro_name, "Si216x_EVB_Rev3_0_Si2167B"         )==0) { SW_INIT_Si216x_EVB_Rev3_0_Si2167B;       return 0x2167B;  }
 #endif /* SW_INIT_Si216x_EVB_Rev3_0_Si2167B */
 #ifdef    SW_INIT_Si216x_EVB_Rev3_0_Si2169
  if ( strcmp_nocase( macro_name, "Si216x_EVB_Rev3_0_Si2169"          )==0) { SW_INIT_Si216x_EVB_Rev3_0_Si2169;        return   2169;  }
 #endif /* SW_INIT_Si216x_EVB_Rev3_0_Si2169 */
 #ifdef    SW_INIT_Platform_2010_Rev1_0_Si2183
  if ( strcmp_nocase( macro_name, "Platform_2010_Rev1_0_Si2183"       )==0) { SW_INIT_Platform_2010_Rev1_0_Si2183;        return 0x2183;  }
 #endif /* SW_INIT_Platform_2010_Rev1_0_Si2183 */
 #ifdef    SW_INIT_Si216x_EVB_Rev3_0_Si2183
  if ( strcmp_nocase( macro_name, "Si216x_EVB_Rev3_0_Si2183"          )==0) { SW_INIT_Si216x_EVB_Rev3_0_Si2183;        return 0x2183;  }
 #endif /* SW_INIT_Si216x_EVB_Rev3_0_Si2183 */
 #ifdef    SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2164
  if ( strcmp_nocase( macro_name, "Si216x_SOC_EVB_Rev1_0_Si2178_Si2164"      )==0) { SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2164;    return 0x2164;  }
 #endif /* SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2164 */
 #ifdef    SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178B_Si2164
  if ( strcmp_nocase( macro_name, "Si216x_SOC_EVB_Rev1_0_Si2178B_Si2164"      )==0) { SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178B_Si2164;    return 0x2164;  }
 #endif /* SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178B_Si2164 */
 #ifdef    SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2183
  if ( strcmp_nocase( macro_name, "Si216x_SOC_EVB_Rev1_0_Si2178_Si2183"      )==0) { SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2183;    return 0x2183;  }
 #endif /* SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2183 */
 #ifdef    SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178B_Si2183
  if ( strcmp_nocase( macro_name, "Si216x_SOC_EVB_Rev1_0_Si2178B_Si2183"      )==0) { SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178B_Si2183;    return 0x2183;  }
 #endif /* SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178B_Si2183 */
 #ifdef    SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2164_Airoha
  if ( strcmp_nocase( macro_name, "Si216x_SOC_EVB_Rev1_0_Si2178_Si2164_Airoha"      )==0) { SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2164_Airoha;    return 0x2164;  }
 #endif /* SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2164_Airoha */
 #ifdef    SW_INIT_Si2169_67_76_EVB_Rev1_1_Si2169
  if ( strcmp_nocase( macro_name, "Si2169_67_76_EVB_Rev1_1_Si2169"    )==0) { SW_INIT_Si2169_67_76_EVB_Rev1_1_Si2169;  return   2169;  }
 #endif /* SW_INIT_Si2169_67_76_EVB_Rev1_1_Si2169 */
 #ifdef    SW_INIT_Si2169_67_76_EVB_Rev1_1_Si2167A10
  if ( strcmp_nocase( macro_name, "Si2169_67_76_EVB_Rev1_1_Si2167A10"   )==0) { SW_INIT_Si2169_67_76_EVB_Rev1_1_Si2167A10; return 2167; }
 #endif /* SW_INIT_Si2169_67_76_EVB_Rev1_1_Si2167A10 */
 #ifdef    SW_INIT_Si2169_67_76_EVB_Rev1_1_Si2167B
  if ( strcmp_nocase( macro_name, "Si2169_67_76_EVB_Rev1_1_Si2167B"   )==0) { SW_INIT_Si2169_67_76_EVB_Rev1_1_Si2167B; return 0x2167B; }
 #endif /* SW_INIT_Si2169_67_76_EVB_Rev1_1_Si2167B */
 #ifdef    SW_INIT_Si2169_67_76_EVB_Rev1_1_Si2164
  if ( strcmp_nocase( macro_name, "Si2169_67_76_EVB_Rev1_1_Si2164"    )==0) { SW_INIT_Si2169_67_76_EVB_Rev1_1_Si2164; return 0x2164; }
 #endif /* SW_INIT_Si2169_67_76_EVB_Rev1_1_Si2164 */
 #ifdef    SW_INIT_Si217USB_MB_Rev1_4_Si2168
  if ( strcmp_nocase( macro_name, "Si217USB_MB_Rev1_4_Si2168"    )==0) { SW_INIT_Si217USB_MB_Rev1_4_Si2168; return 2169; }
 #endif /* SW_INIT_Si217USB_MB_Rev1_4_Si2168 */
 #ifdef    SW_INIT_Si2141_51_DVBT2TC_DC_Rev1_2_Si2168C
  if ( strcmp_nocase( macro_name, "Si2141_51_DVBT2TC_DC_Rev1_2_Si2168C"    )==0) { SW_INIT_Si2141_51_DVBT2TC_DC_Rev1_2_Si2168C; return 0x2183; }
 #endif /* SW_INIT_Si2141_51_DVBT2TC_DC_Rev1_2_Si2168C */
 #ifdef    SW_INIT_Si216x_8x_EVB_AIR_Rev1_0_Si2167B
  if ( strcmp_nocase( macro_name, "Si216x_8x_EVB_AIR_Rev1_0_Si2167B"    )==0) { SW_INIT_Si216x_8x_EVB_AIR_Rev1_0_Si2167B; return 0x2167B; }
 #endif /* SW_INIT_Si216x_8x_EVB_AIR_Rev1_0_Si2167B */
 #ifdef    SW_INIT_Si2166B_EVB_Rev1_0_66B
  if ( strcmp_nocase( macro_name, "Si2166B_EVB_Rev1_0_66B"    )==0) { SW_INIT_Si2166B_EVB_Rev1_0_66B; return 0x2167B; }
 #endif /* SW_INIT_Si2166B_EVB_Rev1_0_66B */
 #ifdef    SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2167B_Airoha
  if ( strcmp_nocase( macro_name, "Si216x_SOC_EVB_Rev1_0_Si2178_Si2167B_Airoha"    )==0) { SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2167B_Airoha; return 0x2167B; }
 #endif /* SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2167B_Airoha */
#endif /* MACROS_FOR_SINGLE_FRONTENDS */

#ifdef    MACROS_FOR_DUAL_FRONTENDS
 /* DUAL TER+SAT */
 #ifdef    SW_INIT_Si216x2_EVB_Rev1_x_Si2164
  if ( strcmp_nocase( macro_name, "Si216x2_EVB_Rev1_x_Si2164"         )==0) { SW_INIT_Si216x2_EVB_Rev1_x_Si2164;       return 0x2164;  }
 #endif /* SW_INIT_Si216x2_EVB_Rev1_x_Si2164 */
 #ifdef    SW_INIT_Si216x2_EVB_Rev1_x_Si2178_Si2164
  if ( strcmp_nocase( macro_name, "Si216x2_EVB_Rev1_x_Si2178_Si2164"  )==0) { SW_INIT_Si216x2_EVB_Rev1_x_Si2178_Si2164;         return 0x2164;  }
 #endif /* SW_INIT_Si216x2_EVB_Rev1_x_Si2178_Si2164 */
 #ifdef    SW_INIT_Si216x2_EVB_Rev1_x_Si2178B_Si2164
  if ( strcmp_nocase( macro_name, "Si216x2_EVB_Rev1_x_Si2178B_Si2164" )==0) { SW_INIT_Si216x2_EVB_Rev1_x_Si2178B_Si2164;       return 0x2164;  }
 #endif /* SW_INIT_Si216x2_EVB_Rev1_x_Si2178B_Si2164 */
 #ifdef    SW_INIT_Si216x2_EVB_Rev1_x_91A_83A
  if ( strcmp_nocase( macro_name, "Si216x2_EVB_Rev1_x_91A_83A"  )==0) { SW_INIT_Si216x2_EVB_Rev1_x_91A_83A;         return 0x2183;  }
 #endif /* SW_INIT_Si216x2_EVB_Rev1_x_91A_83A */
 #ifdef    SW_INIT_Si216x2_EVB_Rev1_x_Si2178B_Si2183
  if ( strcmp_nocase( macro_name, "Si216x2_EVB_Rev1_x_Si2178B_Si2183" )==0) { SW_INIT_Si216x2_EVB_Rev1_x_Si2178B_Si2183;       return 0x2183;  }
 #endif /* SW_INIT_Si216x2_EVB_Rev1_x_Si2178B_Si2183 */
 #ifdef    SW_INIT_Si216x2_EVB_Rev1_x_Si2167B
  if ( strcmp_nocase( macro_name, "Si216x2_EVB_Rev1_x_Si2167B"        )==0) { SW_INIT_Si216x2_EVB_Rev1_x_Si2167B;      return 0x2167B; }
 #endif /* SW_INIT_Si216x2_EVB_Rev1_x_Si2167B */
 #ifdef    SW_INIT_Si216x2_EVB_Rev2_0_Si2164
  if ( strcmp_nocase( macro_name, "Si216x2_EVB_Rev2_0_Si2164"         )==0) { SW_INIT_Si216x2_EVB_Rev2_0_Si2164;       return 0x2164;  }
 #endif /* SW_INIT_Si216x2_EVB_Rev2_0_Si2164 */
 #ifdef    SW_INIT_Si216x2_EVB_Rev2_0_Si2183
  if ( strcmp_nocase( macro_name, "Si216x2_EVB_Rev2_0_Si2183"         )==0) { SW_INIT_Si216x2_EVB_Rev2_0_Si2183;       return 0x2183;  }
 #endif /* SW_INIT_Si216x2_EVB_Rev2_0_Si2183 */
 #ifdef    SW_INIT_Si21662_EVB_Rev1_0_67B
  if ( strcmp_nocase( macro_name, "Si21662_EVB_Rev1_0_67B"        )==0) { SW_INIT_Si21662_EVB_Rev1_0_67B;      return 0x2167B; }
 #endif /* SW_INIT_Si21662_EVB_Rev1_0_67B */
 /* DUAL TER-ONLY */
 #ifdef    SW_INIT_Si21682_EVB_Rev1_0_41A_64A
  if ( strcmp_nocase( macro_name, "Si21682_EVB_Rev1_0_41A_64A"         )==0) { SW_INIT_Si21682_EVB_Rev1_0_41A_64A;       return 0x2164;  }
 #endif /* SW_INIT_Si21682_EVB_Rev1_0_41A_64A */
 #ifdef    SW_INIT_Si21682_EVB_Rev1_0_41A_67B
  if ( strcmp_nocase( macro_name, "Si21682_EVB_Rev1_0_41A_67B"       )==0) { SW_INIT_Si21682_EVB_Rev1_0_41A_67B;     return 0x2167B;  }
 #endif /* SW_INIT_Si21682_EVB_Rev1_0_41A_67B */
 #ifdef    SW_INIT_Si21682_EVB_Rev1_0_41A_83A
  if ( strcmp_nocase( macro_name, "Si21682_EVB_Rev1_0_41A_83A"         )==0) { SW_INIT_Si21682_EVB_Rev1_0_41A_83A;       return 0x2183;  }
 #endif /* SW_INIT_Si21682_EVB_Rev1_0_41A_83A */
#endif /* MACROS_FOR_DUAL_FRONTENDS */

#ifdef    MACROS_FOR_TRIPLE_FRONTENDS
#endif /* MACROS_FOR_TRIPLE_FRONTENDS */

#ifdef    MACROS_FOR_QUAD_FRONTENDS
 #ifdef    SW_INIT_Dual_Si2191_Si216x2_Si2164
  if ( strcmp_nocase( macro_name, "Dual_Si2191_Si216x2_Si2164"        )==0) { SW_INIT_Dual_Si2191_Si216x2_Si2164;      return 0x2164;  }
 #endif /* SW_INIT_Dual_Si2191_Si216x2_Si2164 */
 #ifdef    SW_INIT_Dual_Si2191_Si216x2_Si2183
  if ( strcmp_nocase( macro_name, "Dual_Si2191_Si216x2_Si2183"        )==0) { SW_INIT_Dual_Si2191_Si216x2_Si2183;      return  0x2183;  }
 #endif /* SW_INIT_Dual_Si2191_Si216x2_Si2183 */
 #ifdef    SW_INIT_quad_Si2169A
  if ( strcmp_nocase( macro_name, "quad_Si2169A"                      )==0) { SW_INIT_quad_Si2169A;                    return   2169;  }
 #endif /* SW_INIT_quad_Si2169A */
#endif /* MACROS_FOR_QUAD_FRONTENDS */

  SiERROR("invalid command line argument (unknown macro name)\n");

  return 0;
}
/************************************************************************************************************************
  SiLabs_SW_config_possibilities function
  Use:        SW configuration selection function
              Used to init the SW based on pre-recorder macros, follwing a user selection
  Returns:    0 if no matching macros is found
************************************************************************************************************************/
signed   int   SiLabs_SW_config_possibilities  (char *config_macros) {
  signed   int macro_count;
  sprintf(config_macros, "%s", "");
  macro_count = 0;

#ifdef    KNOWN_MACROS_FOR_SILABS_EVBs
  sprintf(config_macros,   "%s\n-----------SiLabs EVB Macros-------"      , config_macros);
          KNOWN_MACROS_FOR_SILABS_EVBs
#endif /* KNOWN_MACROS_FOR_SILABS_EVBs */

#ifdef    MACROS_FOR_SINGLE_FRONTENDS
  sprintf(config_macros,   "%s\n-----------single-----------"      , config_macros);
 #ifdef    SW_INIT_Si2166B_AV2018
  sprintf(config_macros, "%s\n  Si2166B_AV2018"          , config_macros); macro_count++;
 #endif /* SW_INIT_Si2166B_AV2018 */
 #ifdef    SW_INIT_Si2176_DVBTC_DC_Rev1_0
  sprintf(config_macros, "%s\n  Si2176_DVBTC_DC_Rev1_0"          , config_macros); macro_count++;
 #endif /* SW_INIT_Si2176_DVBTC_DC_Rev1_0 */
 #ifdef    SW_INIT_Si216x_EVB_Rev3_0_Si2164
  sprintf(config_macros, "%s\n  Si216x_EVB_Rev3_0_Si2164"        , config_macros); macro_count++;
 #endif /* SW_INIT_Si216x_EVB_Rev3_0_Si2164 */
 #ifdef    SW_INIT_Si216x_EVB_Rev3_0_Si2167B
  sprintf(config_macros, "%s\n  Si216x_EVB_Rev3_0_Si2167B"       , config_macros); macro_count++;
 #endif /* SW_INIT_Si216x_EVB_Rev3_0_Si2167B */
 #ifdef    SW_INIT_Si216x_EVB_Rev3_0_Si2169
  sprintf(config_macros, "%s\n  Si216x_EVB_Rev3_0_Si2169"        , config_macros); macro_count++;
 #endif /* SW_INIT_Si216x_EVB_Rev3_0_Si2169 */
 #ifdef    SW_INIT_Platform_2010_Rev1_0_Si2183
  sprintf(config_macros, "%s\n  Platform_2010_Rev1_0_Si2183"        , config_macros); macro_count++;
 #endif /* SW_INIT_Platform_2010_Rev1_0_Si2183 */
 #ifdef    SW_INIT_Si216x_EVB_Rev3_0_Si2183
  sprintf(config_macros, "%s\n  Si216x_EVB_Rev3_0_Si2183"        , config_macros); macro_count++;
 #endif /* SW_INIT_Si216x_EVB_Rev3_0_Si2183 */
 #ifdef    SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2164
  sprintf(config_macros, "%s\n  Si216x_SOC_EVB_Rev1_0_Si2178_Si2164"    , config_macros); macro_count++;
 #endif /* SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2164 */
 #ifdef    SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178B_Si2164
  sprintf(config_macros, "%s\n  Si216x_SOC_EVB_Rev1_0_Si2178B_Si2164"    , config_macros); macro_count++;
 #endif /* SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178B_Si2164 */
 #ifdef    SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2183
  sprintf(config_macros, "%s\n  Si216x_SOC_EVB_Rev1_0_Si2178_Si2183"    , config_macros); macro_count++;
 #endif /* SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2183 */
 #ifdef    SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178B_Si2183
  sprintf(config_macros, "%s\n  Si216x_SOC_EVB_Rev1_0_Si2178B_Si2183"    , config_macros); macro_count++;
 #endif /* SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178B_Si2183 */
 #ifdef    SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2164_Airoha
  sprintf(config_macros, "%s\n  Si216x_SOC_EVB_Rev1_0_Si2178_Si2164_Airoha"    , config_macros); macro_count++;
 #endif /* SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2164_Airoha */
 #ifdef    SW_INIT_Si2169_67_76_EVB_Rev1_1_Si2169
  sprintf(config_macros, "%s\n  Si2169_67_76_EVB_Rev1_1_Si2169"  , config_macros); macro_count++;
 #endif /* SW_INIT_Si2169_67_76_EVB_Rev1_1_Si2169 */
 #ifdef    SW_INIT_Si2169_67_76_EVB_Rev1_1_Si2167A10
  sprintf(config_macros, "%s\n  Si2169_67_76_EVB_Rev1_1_Si2167A10" , config_macros); macro_count++;
 #endif /* SW_INIT_Si2169_67_76_EVB_Rev1_1_Si2167A10 */
 #ifdef    SW_INIT_Si2169_67_76_EVB_Rev1_1_Si2167B
  sprintf(config_macros, "%s\n  Si2169_67_76_EVB_Rev1_1_Si2167B" , config_macros); macro_count++;
 #endif /* SW_INIT_Si2169_67_76_EVB_Rev1_1_Si2167B */
 #ifdef    SW_INIT_Si2169_67_76_EVB_Rev1_1_Si2164
  sprintf(config_macros, "%s\n  Si2169_67_76_EVB_Rev1_1_Si2164" , config_macros); macro_count++;
 #endif /* SW_INIT_Si2169_67_76_EVB_Rev1_1_Si2164 */
 #ifdef    SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2167B_Airoha
  sprintf(config_macros, "%s\n  Si216x_SOC_EVB_Rev1_0_Si2178_Si2167B_Airoha" , config_macros); macro_count++;
 #endif /* SW_INIT_Si216x_SOC_EVB_Rev1_0_Si2178_Si2167B_Airoha */
 #ifdef    SW_INIT_Si216x_8x_EVB_AIR_Rev1_0_Si2167B
  sprintf(config_macros, "%s\n  Si216x_8x_EVB_AIR_Rev1_0_Si2167B" , config_macros); macro_count++;
 #endif /* SW_INIT_Si216x_8x_EVB_AIR_Rev1_0_Si2167B */
 #ifdef    SW_INIT_Si2166B_EVB_Rev1_0_66B
  sprintf(config_macros, "%s\n  Si2166B_EVB_Rev1_0_66B" , config_macros); macro_count++;
 #endif /* SW_INIT_Si2166B_EVB_Rev1_0_66B */
  sprintf(config_macros,   "%s\n-----------single(TER-only)--"      , config_macros);
 #ifdef    SW_INIT_Si217USB_MB_Rev1_4_Si2168
  sprintf(config_macros, "%s\n  Si217USB_MB_Rev1_4_Si2168"          , config_macros); macro_count++;
 #endif /* SW_INIT_Si217USB_MB_Rev1_4_Si2168 */
 #ifdef    SW_INIT_Si2141_51_DVBT2TC_DC_Rev1_2_Si2168C
  sprintf(config_macros, "%s\n  Si2141_51_DVBT2TC_DC_Rev1_2_Si2168C", config_macros); macro_count++;
 #endif /* SW_INIT_Si2141_51_DVBT2TC_DC_Rev1_2_Si2168C */
#endif /* MACROS_FOR_SINGLE_FRONTENDS */

#ifdef    MACROS_FOR_DUAL_FRONTENDS
  sprintf(config_macros, "%s\n-----------dual (TER+SAT) ---"      , config_macros);
 #ifdef    SW_INIT_Si216x2_EVB_Rev1_x_Si2164
  sprintf(config_macros, "%s\n  Si216x2_EVB_Rev1_x_Si2164"       , config_macros); macro_count++;
 #endif /* SW_INIT_Si216x2_EVB_Rev1_x_Si2164 */
 #ifdef    SW_INIT_Si216x2_EVB_Rev1_x_Si2167B
  sprintf(config_macros, "%s\n  Si216x2_EVB_Rev1_x_Si2167B"      , config_macros); macro_count++;
 #endif /* SW_INIT_Si216x2_EVB_Rev1_x_Si2167B */
 #ifdef    SW_INIT_Si216x2_EVB_Rev1_x_Si2178_Si2164
  sprintf(config_macros, "%s\n  Si216x2_EVB_Rev1_x_Si2178_Si2164" , config_macros); macro_count++;
 #endif /* SW_INIT_Si216x2_EVB_Rev1_x_Si2178_Si2164 */
 #ifdef    SW_INIT_Si216x2_EVB_Rev1_x_Si2178B_Si2164
  sprintf(config_macros, "%s\n  Si216x2_EVB_Rev1_x_Si2178B_Si2164", config_macros); macro_count++;
 #endif /* SW_INIT_Si216x2_EVB_Rev1_x_Si2178B_Si2164 */
 #ifdef    SW_INIT_Si216x2_EVB_Rev1_x_91A_83A
  sprintf(config_macros, "%s\n  Si216x2_EVB_Rev1_x_91A_83A" , config_macros); macro_count++;
 #endif /* SW_INIT_Si216x2_EVB_Rev1_x_91A_83A */
 #ifdef    SW_INIT_Si216x2_EVB_Rev1_x_Si2178B_Si2183
  sprintf(config_macros, "%s\n  Si216x2_EVB_Rev1_x_Si2178B_Si2183", config_macros); macro_count++;
 #endif /* SW_INIT_Si216x2_EVB_Rev1_x_Si2178B_Si2183 */
 #ifdef    SW_INIT_Si216x2_EVB_Rev2_0_Si2164
  sprintf(config_macros, "%s\n  Si216x2_EVB_Rev2_0_Si2164"       , config_macros); macro_count++;
 #endif /* SW_INIT_Si216x2_EVB_Rev2_0_Si2164 */
 #ifdef    SW_INIT_Si216x2_EVB_Rev2_0_Si2183
  sprintf(config_macros, "%s\n  Si216x2_EVB_Rev2_0_Si2183"       , config_macros); macro_count++;
 #endif /* SW_INIT_Si216x2_EVB_Rev2_0_Si2183 */
 #ifdef    SW_INIT_Si21662_EVB_Rev1_0_67B
  sprintf(config_macros, "%s\n  Si21662_EVB_Rev1_0_67B"      , config_macros); macro_count++;
 #endif /* SW_INIT_Si21662_EVB_Rev1_0_67B */

  sprintf(config_macros, "%s\n-----------dual (TER only) -"      , config_macros);
 #ifdef    SW_INIT_Si21682_EVB_Rev1_0_41A_64A
  sprintf(config_macros, "%s\n  Si21682_EVB_Rev1_0_41A_64A"       , config_macros); macro_count++;
 #endif /* SW_INIT_Si21682_EVB_Rev1_0_41A_64A */
 #ifdef    SW_INIT_Si21682_EVB_Rev1_0_41A_67B
  sprintf(config_macros, "%s\n  Si21682_EVB_Rev1_0_41A_67B"     , config_macros); macro_count++;
 #endif /* SW_INIT_Si21682_EVB_Rev1_0_41A_67B */
 #ifdef    SW_INIT_Si21682_EVB_Rev1_0_41A_83A
  sprintf(config_macros, "%s\n  Si21682_EVB_Rev1_0_41A_83A"       , config_macros); macro_count++;
 #endif /* SW_INIT_Si21682_EVB_Rev1_0_41A_83A */

#endif /* MACROS_FOR_DUAL_FRONTENDS */

#ifdef    MACROS_FOR_TRIPLE_FRONTENDS
  sprintf(config_macros, "%s\n-----------triple-----------"      , config_macros);
#endif /* MACROS_FOR_TRIPLE_FRONTENDS */

#ifdef    MACROS_FOR_QUAD_FRONTENDS
  sprintf(config_macros, "%s\n-----------quad-------------"      , config_macros);
 #ifdef    SW_INIT_Dual_Si2191_Si216x2_Si2164
  sprintf(config_macros, "%s\n  Dual_Si2191_Si216x2_Si2164"      , config_macros); macro_count++;
 #endif /* SW_INIT_Dual_Si2191_Si216x2_Si2164 */
 #ifdef    SW_INIT_Dual_Si2191_Si216x2_Si2183
  sprintf(config_macros, "%s\n  Dual_Si2191_Si216x2_Si2183"      , config_macros); macro_count++;
 #endif /* SW_INIT_Dual_Si2191_Si216x2_Si2183 */
 #ifdef    SW_INIT_quad_Si2169A
  sprintf(config_macros, "%s\n  quad_Si2169A"                    , config_macros); macro_count++;
 #endif /* SW_INIT_quad_Si2169A */
#endif /* MACROS_FOR_QUAD_FRONTENDS */

  return macro_count;
}

#ifdef    __cplusplus
}
#endif /* __cplusplus */
