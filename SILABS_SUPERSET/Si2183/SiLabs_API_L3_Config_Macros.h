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

  <improvement>[EVB/macro] In DTV_DUAL_TER_SAT_51A: changing clock settings to use the TER clock.

  As from V2.7.5:
  <improvement>[EVB/macro] In DTV_DUAL_TER_SAT_51A: changing clock settings to use the SAT clock.
                           In TER_SAT_EVB_BR_DUAL: replacing CUSTOMTER_CODE with 0

  As from V2.7.3:
  <improvement>[EVB/macro] TER_SAT_EVB_BR_DUAL macro changes to swap A/B and get A on the left side in GUI.

  As from V2.7.2:
  <improvement>[EVB/macro] Adding DTV_DUAL_TER_SAT_A8297        macro
  <improvement>[EVB/macro] Adding DTV_SINGLE_TER_SAT_Rev2_0_691 macro
  <improvement>[EVB/macro] Adding TER_SAT_EVB_BR_SINGLE         macro
  <improvement>[EVB/macro] Adding TER_SAT_EVB_BR_DUAL           macro

  As from V2.6.5:
  <improvement>[EVB/macro] Adding SiLabs_API_SPI_Setup in DTV_DUAL_TER_SAT_51A macro, to allow testing SPI on a dual

  As from V2.6.4:
  <improvement>[EVB/macro] Adding Si2124 in possible tuners with DTV_SINGLE_TER_SAT_Rev2_0 macro

  As from V2.6.1:
  <improvement>[EVB/macro] Adding Si2165D in possible parts using DTV_SINGLE_TER_SAT_Rev2_0 macro

  As from V2.5.9:
  <improvement>[EVB/macro] Adding Si216x_8x_EVB_RM_Rev1_0 macro

  As from V2.5.6:
   <improvement>[SOC_EVB/Si2165D] Adding Si216x_SOC_EVB_Rev1_0 EVB capability with Si2165D, to allow RMA testing using the same EVB as other demods.

  As from V2.4.4:
  <improvement>[Si2141A/macro] Adding DTV_SINGLE_TER_SAT_Rev1_0 macro for 41A tuner
  <correction/Si216x_SOC_EVB_Rev1_0> SAT Tuner is 0x5815 and not 0x5816
   Adding SiLabs_API_TER_Tuner_AGC_Input and SiLabs_API_TER_Tuner_IF_Output to all macros

  As from V2.2.8:
   Initial version, with current SiLabs EVBs as from 2013/09/09

*/
/* TAG TAGNAME */

#ifndef   _SiLabs_API_L3_Config_Macros_H_
#define   _SiLabs_API_L3_Config_Macros_H_

#include "SiLabs_API_L3_Wrapper.h"

#ifdef    __cplusplus
extern "C" {
#endif /* __cplusplus */

signed   int   SiLabs_SW_config_from_macro     (char *macro_name);
signed   int   SiLabs_SW_config_possibilities  (char *config_macros);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

#ifdef    SILABS_EVB_MACROS

#define MACRO_STRING(s) #s
#define MACRO_NAME_board_demod(board,demod)                                     MACRO_STRING(board##_##demod)
#define MACRO_NAME_board_tuner_demod(board,tuner,demod)                         MACRO_STRING(board##_##tuner##_##demod)

#define MACRO_SPRINTF_board_demod(board,demod)                                  sprintf(config_macros, "%s\n  %s", config_macros, MACRO_NAME_board_demod(board,demod)             ); macro_count++;
#define MACRO_SPRINTF_board_tuner_demod(board,tuner,demod)                      sprintf(config_macros, "%s\n  %s", config_macros, MACRO_NAME_board_tuner_demod(board,tuner,demod) ); macro_count++;

#define MACRO_STRCMP_board_demod(board,demod,chip_code)                         if ( strcmp_nocase( macro_name, MACRO_NAME_board_demod(board,demod))             ==0) { board(chip_code); return chip_code; }
#define MACRO_STRCMP_board(board,chip_code)                                     if ( strcmp_nocase( macro_name, MACRO_STRING(board))                             ==0) { board; return chip_code; }
#define MACRO_STRCMP_board_tuner_demod(board,tuner,tuner_code,demod,chip_code)  if ( strcmp_nocase( macro_name, MACRO_NAME_board_tuner_demod(board,tuner,demod)) ==0) { board(tuner_code,chip_code); return chip_code; }

#ifdef    MACROS_FOR_SINGLE_FRONTENDS

#if 1  /* Definition of Si217USB_MB_Rev1_4(tuner_code,chip_code) */

#define Si217USB_MB_Rev1_4(tuner_code,chip_code) \
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0);\
  SiLabs_API_Select_TER_Tuner         (front_end, tuner_code, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 2);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#ifdef    Si217USB_MB_Rev1_4
 #define  Si217USB_MB_Rev1_4_List(tuner,demod)\
  MACRO_SPRINTF_board_tuner_demod(Si217USB_MB_Rev1_4,tuner,demod);\

 #define  Si217USB_MB_Rev1_4_Selection(tuner,tuner_code,demod,chip_code)\
  MACRO_STRCMP_board_tuner_demod(Si217USB_MB_Rev1_4,tuner,tuner_code,demod,chip_code);\

#else  /* Si217USB_MB_Rev1_4 */

 #define  Si217USB_MB_Rev1_4_List(tuner,demod)                           /* */
 #define  Si217USB_MB_Rev1_4_Selection(tuner,tuner_code,demod,chip_code) /* */

#endif /* Si217USB_MB_Rev1_4 */

#endif /* Definition of Si217USB_MB_Rev1_4 */

#if 1  /* Definition of Si2169_67_76_EVB_REV1_1_76A(chip_code) */

#define Si2169_67_76_EVB_REV1_1_76A(chip_code)\
  /* SW Init for front end 0 */\
  front_end  = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x18);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2176, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 2);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5812, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 21, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 0, 32, 16, 2);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 1);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#ifdef    Si2169_67_76_EVB_REV1_1_76A
 #define  Si2169_67_76_EVB_REV1_1_76A_List(demod)\
  MACRO_SPRINTF_board_demod(Si2169_67_76_EVB_REV1_1_76A,demod);\

 #define  Si2169_67_76_EVB_REV1_1_76A_Selection(demod,chip_code)\
  MACRO_STRCMP_board_demod(Si2169_67_76_EVB_REV1_1_76A,demod,chip_code);\

#else  /* Si2169_67_76_EVB_REV1_1_76A */

 #define  Si2169_67_76_EVB_REV1_1_76A_List(demod)                /* */
 #define  Si2169_67_76_EVB_REV1_1_76A_Selection(demod,chip_code) /* */

#endif /* Si2169_67_76_EVB_REV1_1_76A */

#endif /* Definition of Si216x_EVB_Rev3_0 */

#if 1  /* Definition of Si216x_EVB_Rev3_0(tuner_code,chip_code) */

#define Si216x_EVB_Rev3_0(tuner_code,chip_code)\
  /* SW Init for front end 0 */\
  front_end  = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x18);\
  SiLabs_API_Select_TER_Tuner         (front_end, tuner_code, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 2);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5815, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 25, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 1, 44, 24, 2);\
  SiLabs_API_SAT_Spectrum             (front_end, 1);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 1);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#ifdef    Si216x_EVB_Rev3_0
 #define  Si216x_EVB_Rev3_0_List(demod)\
  MACRO_SPRINTF_board_tuner_demod(Si216x_EVB_Rev3_0,77A,demod);\
  MACRO_SPRINTF_board_tuner_demod(Si216x_EVB_Rev3_0,78A,demod);\
  MACRO_SPRINTF_board_tuner_demod(Si216x_EVB_Rev3_0,78B,demod);\

 #define  Si216x_EVB_Rev3_0_Selection(demod,chip_code)\
  MACRO_STRCMP_board_tuner_demod(Si216x_EVB_Rev3_0,77A,0x2177 ,demod,chip_code);\
  MACRO_STRCMP_board_tuner_demod(Si216x_EVB_Rev3_0,78A,0x2178 ,demod,chip_code);\
  MACRO_STRCMP_board_tuner_demod(Si216x_EVB_Rev3_0,78B,0x2178B,demod,chip_code);\

#else  /* Si216x_EVB_Rev3_0 */

 #define  Si216x_EVB_Rev3_0_List(demod)                /* */
 #define  Si216x_EVB_Rev3_0_Selection(demod,chip_code) /* */

#endif /* Si216x_EVB_Rev3_0 */

#endif /* Definition of Si216x_EVB_Rev3_0 */

#if 1  /* Definition of Si216x_SOC_EVB_Rev1_0(tuner_code,chip_code) */

#define Si216x_SOC_EVB_Rev1_0(tuner_code,chip_code)\
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x18);\
  SiLabs_API_Select_TER_Tuner         (front_end, tuner_code, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 2);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5815, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 2);\
  SiLabs_API_SAT_Spectrum             (front_end, 1);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 1);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#ifdef    Si216x_SOC_EVB_Rev1_0
 #define  Si216x_SOC_EVB_Rev1_0_List(demod)\
  MACRO_SPRINTF_board_tuner_demod(Si216x_SOC_EVB_Rev1_0,78A,demod);\
  MACRO_SPRINTF_board_tuner_demod(Si216x_SOC_EVB_Rev1_0,78B,demod);\

 #define  Si216x_SOC_EVB_Rev1_0_Selection(demod,chip_code)\
  MACRO_STRCMP_board_tuner_demod(Si216x_SOC_EVB_Rev1_0,78A,0x2178 ,demod,chip_code);\
  MACRO_STRCMP_board_tuner_demod(Si216x_SOC_EVB_Rev1_0,78B,0x2178B,demod,chip_code);\

#else  /* Si216x_SOC_EVB_Rev1_0 */

 #define  Si216x_SOC_EVB_Rev1_0_List(demod)                /* */
 #define  Si216x_SOC_EVB_Rev1_0_Selection(demod,chip_code) /* */

#endif /* Si216x_SOC_EVB_Rev1_0 */
#endif /* Definition of Si216x_SOC_EVB_Rev1_0 */

#if 1  /* Definition of Si2168_46_EVB_Rev1_0(tuner_code,chip_code) */

#define Si2168_46_EVB_Rev1_0(tuner_code,chip_code)\
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0);\
  SiLabs_API_Select_TER_Tuner         (front_end, tuner_code, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 2);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#ifdef    Si2168_46_EVB_Rev1_0
 #define  Si2168_46_EVB_Rev1_0_List(demod)\
  MACRO_SPRINTF_board_tuner_demod(Si2168_46_EVB_Rev1_0,46A,demod);\

 #define  Si2168_46_EVB_Rev1_0_Selection(demod,chip_code)\
  MACRO_STRCMP_board_tuner_demod(Si2168_46_EVB_Rev1_0,46A,0x2146 ,demod,chip_code);\

#else  /* Si2168_46_EVB_Rev1_0 */

 #define  Si2168_46_EVB_Rev1_0_List(demod)                /* */
 #define  Si2168_46_EVB_Rev1_0_Selection(demod,chip_code) /* */

#endif /* Si2168_46_EVB_Rev1_0 */
#endif /* Definition of Si2168_46_EVB_Rev1_0 */

#if 1  /* Definition of Si2168_EVB_Rev2_0(tuner_code,chip_code) */

#define Si2168_EVB_Rev2_0(tuner_code,chip_code)\
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0);\
  SiLabs_API_Select_TER_Tuner         (front_end, tuner_code, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 2);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#ifdef    Si2168_EVB_Rev2_0
 #define  Si2168_EVB_Rev2_0_List(demod)\
  MACRO_SPRINTF_board_tuner_demod(Si2168_EVB_Rev2_0,41A,demod);\

 #define  Si2168_EVB_Rev2_0_Selection(demod,chip_code)\
  MACRO_STRCMP_board_tuner_demod(Si2168_EVB_Rev2_0,41A,0x2141 ,demod,chip_code);\

#else  /* Si2168_EVB_Rev2_0 */

 #define  Si2168_EVB_Rev2_0_List(demod)                /* */
 #define  Si2168_EVB_Rev2_0_Selection(demod,chip_code) /* */

#endif /* Si2168_EVB_Rev2_0 */
#endif /* Definition of Si2168_EVB_Rev2_0 */

#if 1  /* Definition of Si2168_57_EVB_Rev1_0(tuner_code,chip_code) */

#define Si2168_57_EVB_Rev1_0(tuner_code,chip_code)\
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0);\
  SiLabs_API_Select_TER_Tuner         (front_end, tuner_code, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 2);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#ifdef    Si2168_57_EVB_Rev1_0
 #define  Si2168_57_EVB_Rev1_0_List(demod)\
  MACRO_SPRINTF_board_tuner_demod(Si2168_57_EVB_Rev1_0,57A,demod);\

 #define  Si2168_57_EVB_Rev1_0_Selection(demod,chip_code)\
  MACRO_STRCMP_board_tuner_demod(Si2168_57_EVB_Rev1_0,57A,0x2157 ,demod,chip_code);\

#else  /* Si2168_57_EVB_Rev1_0 */

 #define  Si2168_57_EVB_Rev1_0_List(demod)                /* */
 #define  Si2168_57_EVB_Rev1_0_Selection(demod,chip_code) /* */

#endif /* Si2168_57_EVB_Rev1_0 */
#endif /* Definition of Si2168_57_EVB_Rev1_0 */

#if 1  /* Definition of Si216x_8x_EVB_AIR_Rev1_0(tuner_code,chip_code) */

#define Si216x_8x_EVB_AIR_Rev1_0(tuner_code,chip_code) \
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0xC6);\
  SiLabs_API_Select_TER_Tuner         (front_end, tuner_code, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0xA2018, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 25, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 1);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#ifdef    Si216x_8x_EVB_AIR_Rev1_0
 #define  Si216x_8x_EVB_AIR_Rev1_0_List(demod)\
  MACRO_SPRINTF_board_tuner_demod(Si216x_8x_EVB_AIR_Rev1_0,77A,demod);\

 #define  Si216x_8x_EVB_AIR_Rev1_0_Selection(demod,chip_code)\
  MACRO_STRCMP_board_tuner_demod(Si216x_8x_EVB_AIR_Rev1_0,77A,0x2177 ,demod,chip_code);\

#else  /* Si216x_8x_EVB_AIR_Rev1_0 */

 #define  Si216x_8x_EVB_AIR_Rev1_0_List(demod)                /* */
 #define  Si216x_8x_EVB_AIR_Rev1_0_Selection(demod,chip_code) /* */

#endif /* Si216x_8x_EVB_AIR_Rev1_0 */
#endif /* Definition of Si216x_8x_EVB_AIR_Rev1_0 */

#if 1  /* Definition of DTV_SINGLE_TER_SAT_Rev1_0(tuner_code,chip_code) */

#define DTV_SINGLE_TER_SAT_Rev1_0(tuner_code,chip_code) \
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0xC6);\
  SiLabs_API_Select_TER_Tuner         (front_end, tuner_code, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0xA2018, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 25, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 1);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#ifdef    DTV_SINGLE_TER_SAT_Rev1_0
 #define  DTV_SINGLE_TER_SAT_Rev1_0_List(demod)\
  MACRO_SPRINTF_board_tuner_demod(DTV_SINGLE_TER_SAT_Rev1_0,41A,demod);\

 #define  DTV_SINGLE_TER_SAT_Rev1_0_Selection(demod,chip_code)\
  MACRO_STRCMP_board_tuner_demod(DTV_SINGLE_TER_SAT_Rev1_0,41A,0x2141 ,demod,chip_code);\

#else  /* DTV_SINGLE_TER_SAT_Rev1_0 */

 #define  DTV_SINGLE_TER_SAT_Rev1_0_List(demod)                /* */
 #define  DTV_SINGLE_TER_SAT_Rev1_0_Selection(demod,chip_code) /* */

#endif /* DTV_SINGLE_TER_SAT_Rev1_0 */
#endif /* Definition of DTV_SINGLE_TER_SAT_Rev1_0 */

#if 1  /* Definition of DTV_SINGLE_TER_SAT_Rev2_0(tuner_code,chip_code) */

#define DTV_SINGLE_TER_SAT_Rev2_0(tuner_code,chip_code) \
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0xC6);\
  SiLabs_API_SPI_Setup                (front_end, 0x00, 5, 0, 9, 1);\
  SiLabs_API_TS_Config                (front_end, 0, 0, 0, 0, 0, 0);\
  SiLabs_API_Select_TER_Tuner         (front_end, tuner_code, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0xA2018, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 25, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 1);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);\
  SiLabs_API_Cypress_Ports            (front_end, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00);\

#ifdef    DTV_SINGLE_TER_SAT_Rev2_0
 #define  DTV_SINGLE_TER_SAT_Rev2_0_List(demod)\
  MACRO_SPRINTF_board_tuner_demod(DTV_SINGLE_TER_SAT_Rev2_0,24A,demod);\
  MACRO_SPRINTF_board_tuner_demod(DTV_SINGLE_TER_SAT_Rev2_0,41A,demod);\
  MACRO_SPRINTF_board_tuner_demod(DTV_SINGLE_TER_SAT_Rev2_0,44A,demod);\
  MACRO_SPRINTF_board_tuner_demod(DTV_SINGLE_TER_SAT_Rev2_0,51A,demod);\

 #define  DTV_SINGLE_TER_SAT_Rev2_0_Selection(demod,chip_code)\
  MACRO_STRCMP_board_tuner_demod(DTV_SINGLE_TER_SAT_Rev2_0,24A,0x2124 ,demod,chip_code);\
  MACRO_STRCMP_board_tuner_demod(DTV_SINGLE_TER_SAT_Rev2_0,41A,0x2141 ,demod,chip_code);\
  MACRO_STRCMP_board_tuner_demod(DTV_SINGLE_TER_SAT_Rev2_0,44A,0x2144 ,demod,chip_code);\
  MACRO_STRCMP_board_tuner_demod(DTV_SINGLE_TER_SAT_Rev2_0,51A,0x2151 ,demod,chip_code);\

#else  /* DTV_SINGLE_TER_SAT_Rev2_0 */

 #define  DTV_SINGLE_TER_SAT_Rev2_0_List(demod)                /* */
 #define  DTV_SINGLE_TER_SAT_Rev2_0_Selection(demod,chip_code) /* */

#endif /* DTV_SINGLE_TER_SAT_Rev2_0 */
#endif /* Definition of DTV_SINGLE_TER_SAT_Rev2_0 */

#if 1  /* Definition of DTV_SINGLE_TER_SAT_Rev2_0_691(tuner_code,chip_code) */

#define DTV_SINGLE_TER_SAT_Rev2_0_691(tuner_code,chip_code) \
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x18);\
  SiLabs_API_TS_Config                (front_end, 0, 0, 0, 0, 0, 0);\
  SiLabs_API_Select_TER_Tuner         (front_end, tuner_code, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 2);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xc, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0xA2018, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 25, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 2);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xc, 1, 0x0, 1);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);\
  SiLabs_API_Cypress_Ports            (front_end, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00);\

#ifdef    DTV_SINGLE_TER_SAT_Rev2_0_691
 #define  DTV_SINGLE_TER_SAT_Rev2_0_691_List(demod)\
  MACRO_SPRINTF_board_tuner_demod(DTV_SINGLE_TER_SAT_Rev2_0,24A,demod);\
  MACRO_SPRINTF_board_tuner_demod(DTV_SINGLE_TER_SAT_Rev2_0,41A,demod);\
  MACRO_SPRINTF_board_tuner_demod(DTV_SINGLE_TER_SAT_Rev2_0,41B,demod);\
  MACRO_SPRINTF_board_tuner_demod(DTV_SINGLE_TER_SAT_Rev2_0,44A,demod);\
  MACRO_SPRINTF_board_tuner_demod(DTV_SINGLE_TER_SAT_Rev2_0,51A,demod);\

 #define  DTV_SINGLE_TER_SAT_Rev2_0_691_Selection(demod,chip_code)\
  MACRO_STRCMP_board_tuner_demod(DTV_SINGLE_TER_SAT_Rev2_0,24A,0x2124 ,demod,chip_code);\
  MACRO_STRCMP_board_tuner_demod(DTV_SINGLE_TER_SAT_Rev2_0,41A,0x2141 ,demod,chip_code);\
  MACRO_STRCMP_board_tuner_demod(DTV_SINGLE_TER_SAT_Rev2_0,41B,0x2141 ,demod,chip_code);\
  MACRO_STRCMP_board_tuner_demod(DTV_SINGLE_TER_SAT_Rev2_0,44A,0x2144 ,demod,chip_code);\
  MACRO_STRCMP_board_tuner_demod(DTV_SINGLE_TER_SAT_Rev2_0,51A,0x2151 ,demod,chip_code);\

#else  /* DTV_SINGLE_TER_SAT_Rev2_0 */

 #define  DTV_SINGLE_TER_SAT_Rev2_0_691_List(demod)                /* */
 #define  DTV_SINGLE_TER_SAT_Rev2_0_691_Selection(demod,chip_code) /* */

#endif /* DTV_SINGLE_TER_SAT_Rev2_0_691 */
#endif /* Definition of DTV_SINGLE_TER_SAT_Rev2_0_691 */

#if 1  /* Definition of Si216x_8x_EVB_RM_Rev1_0(tuner_code,chip_code) */

#define Si216x_8x_EVB_RM_Rev1_0(tuner_code,chip_code) \
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0xC6);\
  SiLabs_API_SPI_Setup                (front_end, 0x00, 5, 0, 9, 1);\
  SiLabs_API_Select_TER_Tuner         (front_end, tuner_code, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x58150, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 25, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 1);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);\
  SiLabs_API_Cypress_Ports            (front_end, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00);\

#ifdef    Si216x_8x_EVB_RM_Rev1_0
 #define  Si216x_8x_EVB_RM_Rev1_0_List(demod)\
  MACRO_SPRINTF_board_tuner_demod(Si216x_8x_EVB_RM_Rev1_0 ,90B,demod);\

 #define  Si216x_8x_EVB_RM_Rev1_0_Selection(demod,chip_code)\
  MACRO_STRCMP_board_tuner_demod(Si216x_8x_EVB_RM_Rev1_0 ,90B,0x2190B ,demod,chip_code);\

#else  /* Si216x_8x_EVB_RM_Rev1_0 */

 #define  Si216x_8x_EVB_RM_Rev1_0_List(demod)                /* */
 #define  Si216x_8x_EVB_RM_Rev1_0_Selection(demod,chip_code) /* */

#endif /* Si216x_8x_EVB_RM_Rev1_0 */
#endif /* Definition of Si216x_8x_EVB_RM_Rev1_0  */

#if 1  /* Definition of RX_SOCKET_EVB_Rev1_0(tuner_code,chip_code) */

#define RX_SOCKET_EVB_Rev1_0(tuner_code,chip_code)\
  /* SW Init for front end 0 */\
  front_end  = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x18);\
  SiLabs_API_Select_TER_Tuner         (front_end, tuner_code, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 100);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 33, 24, 2);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5815, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 25, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 1, 33, 24, 2);\
  SiLabs_API_SAT_Spectrum             (front_end, 1);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 1);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#ifdef    RX_SOCKET_EVB_Rev1_0
 #define  RX_SOCKET_EVB_Rev1_0_List(demod)\
  MACRO_SPRINTF_board_tuner_demod(RX_SOCKET_EVB_Rev1_0,90B,demod);\
  MACRO_SPRINTF_board_tuner_demod(RX_SOCKET_EVB_Rev1_0,41A,demod);\

 #define  RX_SOCKET_EVB_Rev1_0_Selection(demod,chip_code)\
  MACRO_STRCMP_board_tuner_demod(RX_SOCKET_EVB_Rev1_0,90B,0x2190B ,demod,chip_code);\
  MACRO_STRCMP_board_tuner_demod(RX_SOCKET_EVB_Rev1_0,41A,0x2141  ,demod,chip_code);\

#else  /* RX_SOCKET_EVB_Rev1_0 */

 #define  RX_SOCKET_EVB_Rev1_0_List(demod)                /* */
 #define  RX_SOCKET_EVB_Rev1_0_Selection(demod,chip_code) /* */

#endif /* RX_SOCKET_EVB_Rev1_0 */

#endif /* Definition of RX_SOCKET_EVB_Rev1_0 */

#if 1  /* Definition of TER_SAT_TUNER_EVB_Rev1_0(tuner_code,chip_code) */

#define TER_SAT_TUNER_EVB_Rev1_0(tuner_code,chip_code) \
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0xC6);\
  SiLabs_API_SPI_Setup                (front_end, 0x00, 5, 0, 9, 1);\
  SiLabs_API_TS_Config                (front_end, 0, 0, 0, 0, 0, 0);\
  SiLabs_API_Select_TER_Tuner         (front_end, tuner_code, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0xA2017, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 25, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 1);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);\
  SiLabs_API_Cypress_Ports            (front_end, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00);\

#ifdef    TER_SAT_TUNER_EVB_Rev1_0
 #define  TER_SAT_TUNER_EVB_Rev1_0_List(demod)\
  MACRO_SPRINTF_board_tuner_demod(TER_SAT_TUNER_EVB_Rev1_0,90B,demod);\

 #define  TER_SAT_TUNER_EVB_Rev1_0_Selection(demod,chip_code)\
  MACRO_STRCMP_board_tuner_demod(TER_SAT_TUNER_EVB_Rev1_0,90B,0x2190B ,demod,chip_code);\

#else  /* TER_SAT_TUNER_EVB_Rev1_0 */

 #define  TER_SAT_TUNER_EVB_Rev1_0_List(demod)                /* */
 #define  TER_SAT_TUNER_EVB_Rev1_0_Selection(demod,chip_code) /* */

#endif /* TER_SAT_TUNER_EVB_Rev1_0 */
#endif /* Definition of TER_SAT_TUNER_EVB_Rev1_0 */

#if 1  /* Definition of TER_SAT_EVB_BR_SINGLE(chip_code) */

#define TER_SAT_EVB_BR_SINGLE(chip_code)\
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
  SiLabs_API_SW_Init                  (front_end, 0xce, 0xc0, 0xc6);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2141, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xd, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x2017, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 25, 0x10);\
  SiLabs_API_SAT_LNB_Chip_Index       (front_end, 1);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xb, 1, 0x0, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);\
  SiLabs_API_Cypress_Ports            (front_end, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00);\

#ifdef    TER_SAT_EVB_BR_SINGLE
 #define  TER_SAT_EVB_BR_SINGLE_List(demod)\
  MACRO_SPRINTF_board_demod(TER_SAT_EVB_BR_SINGLE,demod);\

 #define  TER_SAT_EVB_BR_SINGLE_Selection(demod,chip_code)\
  MACRO_STRCMP_board_demod(TER_SAT_EVB_BR_SINGLE,demod,chip_code);\

#else  /* TER_SAT_EVB_BR_SINGLE */

 #define  TER_SAT_EVB_BR_SINGLE_List(demod)                /* */
 #define  TER_SAT_EVB_BR_SINGLE_Selection(demod,chip_code) /* */

#endif /* TER_SAT_EVB_BR_SINGLE */

#endif /* Definition of TER_SAT_EVB_BR_SINGLE */



#endif /* MACROS_FOR_SINGLE_FRONTENDS */

#ifdef    MACROS_FOR_DUAL_FRONTENDS

#if 1  /* Definition of Si216x2_EVB_Rev2_0_77A_57A(chip_code) */

#define Si216x2_EVB_Rev2_0_77A_57A(chip_code)\
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x14);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2177, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xa, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xc, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xc, 1, 0x0, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);\
\
  /* SW Init for front end 1 */\
  front_end                   = &(FrontEnd_Table[1]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xce, 0xc6, 0x16);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2157, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 0, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xd, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 1);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 1, "fe[1]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#ifdef    Si216x2_EVB_Rev2_0_77A_57A
 #define  Si216x2_EVB_Rev2_0_77A_57A_List(demod)\
  MACRO_SPRINTF_board_demod(Si216x2_EVB_Rev2_0_77A_57A,demod);\

 #define  Si216x2_EVB_Rev2_0_77A_57A_Selection(demod,chip_code)\
  MACRO_STRCMP_board_demod(Si216x2_EVB_Rev2_0_77A_57A,demod,chip_code);\

#else  /* Si216x2_EVB_Rev2_0_77A_57A */

 #define  Si216x2_EVB_Rev2_0_77A_57A_List(demod)                /* */
 #define  Si216x2_EVB_Rev2_0_77A_57A_Selection(demod,chip_code) /* */

#endif /* Si216x2_EVB_Rev2_0_77A_57A */

#endif /* Definition of Si216x2_EVB_Rev2_0_77A_57A */

#if 1  /* Definition of Si216x2_EVB_Rev1_0_91A(chip_code) */

#define Si216x2_EVB_Rev1_0_91A(chip_code)\
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x14);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2191, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xa, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xc, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 2);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xc, 1, 0x0, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);\
\
  /* SW Init for front end 1 */\
  front_end                   = &(FrontEnd_Table[1]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xce, 0xc6, 0x16);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2191, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 0, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xd, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 1, "fe[1]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#ifdef    Si216x2_EVB_Rev1_0_91A
 #define  Si216x2_EVB_Rev1_0_91A_List(demod)\
  MACRO_SPRINTF_board_demod(Si216x2_EVB_Rev1_0_91A,demod);\

 #define  Si216x2_EVB_Rev1_0_91A_Selection(demod,chip_code)\
  MACRO_STRCMP_board_demod(Si216x2_EVB_Rev1_0_91A,demod,chip_code);\

#else  /* Si216x2_EVB_Rev1_0_91A */

 #define  Si216x2_EVB_Rev1_0_91A_List(demod)                /* */
 #define  Si216x2_EVB_Rev1_0_91A_Selection(demod,chip_code) /* */

#endif /* Si216x2_EVB_Rev1_0_91A */

#endif /* Definition of Si216x2_EVB_Rev1_0_91A */

#if 1  /* Definition of Si216x2_EVB_Rev1_1_91B(chip_code) */

#define Si216x2_EVB_Rev1_1_91B(chip_code)\
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x14);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2148B, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xa, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xc, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 2);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xc, 1, 0x0, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);\
\
  /* SW Init for front end 1 */\
  front_end                   = &(FrontEnd_Table[1]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xce, 0xc6, 0x16);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2148B, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 0, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xd, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 1, "fe[1]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#ifdef    Si216x2_EVB_Rev1_1_91B
 #define  Si216x2_EVB_Rev1_1_91B_List(demod)\
  MACRO_SPRINTF_board_demod(Si216x2_EVB_Rev1_1_91B,demod);\

 #define  Si216x2_EVB_Rev1_1_91B_Selection(demod,chip_code)\
  MACRO_STRCMP_board_demod(Si216x2_EVB_Rev1_1_91B,demod,chip_code);\

#else  /* Si216x2_EVB_Rev1_1_91B */

 #define  Si216x2_EVB_Rev1_1_91B_List(demod)                /* */
 #define  Si216x2_EVB_Rev1_1_91B_Selection(demod,chip_code) /* */

#endif /* Si216x2_EVB_Rev1_1_91B */

#endif /* Definition of Si216x2_EVB_Rev1_1_91B */

#if 1  /* Definition of Si21662_EVB_Rev1_0(chip_code)     */

#define Si21662_EVB_Rev1_0(chip_code)\
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0x00, 0x14);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_LNB_Chip_Index       (front_end, 0);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 44, 27, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xc, 1, 0x0, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);\
\
  /* SW Init for front end 1 */\
  front_end                   = &(FrontEnd_Table[1]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xce, 0x00, 0x16);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x5816, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_LNB_Chip_Index       (front_end, 1);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 44, 27, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xb, 1, 0x0, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 1, "fe[1]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#ifdef    Si21662_EVB_Rev1_0
 #define  Si21662_EVB_Rev1_0_List(demod)\
  MACRO_SPRINTF_board_demod(Si21662_EVB_Rev1_0,demod);\

 #define  Si21662_EVB_Rev1_0_Selection(demod,chip_code)\
  MACRO_STRCMP_board_demod(Si21662_EVB_Rev1_0,demod,chip_code);\

#else  /* Si21662_EVB_Rev1_0 */

 #define  Si21662_EVB_Rev1_0_List(demod)                /* */
 #define  Si21662_EVB_Rev1_0_Selection(demod,chip_code) /* */

#endif /* Si21662_EVB_Rev1_0 */

#endif /* Definition of Si21662_EVB_Rev1_0 */

#if 1  /* Definition of DTV_DUAL_TER_SAT_24A(chip_code) */

#define DTV_DUAL_TER_SAT_24A(chip_code)\
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x14);\
  SiLabs_API_SPI_Setup                (front_end, 0x00, 5, 0, 9, 1);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2124, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x58165D, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xa, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xc, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  front_end->TER_RSSI_offset = -6;\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_LNB_Chip_Index       (front_end, 0);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xc, 1, 0x0, 0);\
  SiLabs_API_HW_Connect               (front_end, 1);\
  SiLabs_API_Cypress_Ports            (front_end, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00);\
\
  /* SW Init for front end 1 */\
  front_end                   = &(FrontEnd_Table[1]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xce, 0xc6, 0x16);\
  SiLabs_API_SPI_Setup                (front_end, 0x00, 5, 0, 9, 1);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2124, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x58165D, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 1, "fe[1]");\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 0, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xd, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  front_end->TER_RSSI_offset = -6;\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_LNB_Chip_Index       (front_end, 1);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 0);\
  SiLabs_API_HW_Connect               (front_end, 1);

#ifdef    DTV_DUAL_TER_SAT_24A
 #define  DTV_DUAL_TER_SAT_24A_List(demod)\
  MACRO_SPRINTF_board_demod(DTV_DUAL_TER_SAT_24A,demod);\

 #define  DTV_DUAL_TER_SAT_24A_Selection(demod,chip_code)\
  MACRO_STRCMP_board_demod(DTV_DUAL_TER_SAT_24A,demod,chip_code);\

#else  /* DTV_DUAL_TER_SAT_24A */

 #define  DTV_DUAL_TER_SAT_24A_List(demod)                /* */
 #define  DTV_DUAL_TER_SAT_24A_Selection(demod,chip_code) /* */

#endif /* DTV_DUAL_TER_SAT_24A */

#endif /* Definition of DTV_DUAL_TER_SAT_24A */

#if 1  /* Definition of DTV_DUAL_TER_SAT_51A(chip_code) */

#define DTV_DUAL_TER_SAT_51A(chip_code)\
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x14);\
  SiLabs_API_SPI_Setup                (front_end, 0x00, 5, 0, 9, 1);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2151, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x58165D, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xa, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xc, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  front_end->TER_RSSI_offset = -6;\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_LNB_Chip_Index       (front_end, 0);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xc, 1, 0x0, 0);\
  SiLabs_API_HW_Connect               (front_end, 1);\
  SiLabs_API_Cypress_Ports            (front_end, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00);\
\
  /* SW Init for front end 1 */\
  front_end                   = &(FrontEnd_Table[1]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xce, 0xc6, 0x16);\
  SiLabs_API_SPI_Setup                (front_end, 0x00, 5, 0, 9, 1);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2151, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x58165D, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 1, "fe[1]");\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 0, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xd, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  front_end->TER_RSSI_offset = -6;\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 26, 0x10);\
  SiLabs_API_SAT_LNB_Chip_Index       (front_end, 1);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 2, 33, 27, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 0);\
  SiLabs_API_HW_Connect               (front_end, 1);

#ifdef    DTV_DUAL_TER_SAT_51A
 #define  DTV_DUAL_TER_SAT_51A_List(demod)\
  MACRO_SPRINTF_board_demod(DTV_DUAL_TER_SAT_51A,demod);\

 #define  DTV_DUAL_TER_SAT_51A_Selection(demod,chip_code)\
  MACRO_STRCMP_board_demod(DTV_DUAL_TER_SAT_51A,demod,chip_code);\

#else  /* DTV_DUAL_TER_SAT_51A */

 #define  DTV_DUAL_TER_SAT_51A_List(demod)                /* */
 #define  DTV_DUAL_TER_SAT_51A_Selection(demod,chip_code) /* */

#endif /* DTV_DUAL_TER_SAT_51A */

#endif /* Definition of DTV_DUAL_TER_SAT_51A */

#if 1  /* Definition of DTV_DUAL_TER_SAT_A8297(chip_code) */

#define DTV_DUAL_TER_SAT_A8297(chip_code)\
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x14);\
  SiLabs_API_SPI_Setup                (front_end, 0x00, 5, 0, 9, 1);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2151, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xa, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xc, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  front_end->TER_RSSI_offset = -6;\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x58165D, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 0xA8297, 0x10);\
  SiLabs_API_SAT_LNB_Chip_Index       (front_end, 0);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xc, 1, 0x0, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
  SiLabs_API_HW_Connect               (front_end, 1);\
  SiLabs_API_Cypress_Ports            (front_end, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00);\
\
  /* SW Init for front end 1 */\
  front_end                   = &(FrontEnd_Table[1]);\
  SiLabs_API_Frontend_Chip            (front_end, chip_code);\
  SiLabs_API_SW_Init                  (front_end, 0xce, 0xc6, 0x16);\
  SiLabs_API_SPI_Setup                (front_end, 0x00, 5, 0, 9, 1);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2151, 0);\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 0, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 1, 0xb, 1);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xd, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  front_end->TER_RSSI_offset = -6;\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x58165D, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 0xA8297, 0x10);\
  SiLabs_API_SAT_LNB_Chip_Index       (front_end, 1);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 1, "fe[1]");\
  SiLabs_API_HW_Connect               (front_end, 1);

#ifdef    DTV_DUAL_TER_SAT_A8297
 #define  DTV_DUAL_TER_SAT_A8297_List(demod)\
  MACRO_SPRINTF_board_demod(DTV_DUAL_TER_SAT_A8297,demod);\

 #define  DTV_DUAL_TER_SAT_A8297_Selection(demod,chip_code)\
  MACRO_STRCMP_board_demod(DTV_DUAL_TER_SAT_A8297,demod,chip_code);\

#else  /* DTV_DUAL_TER_SAT_A8297 */

 #define  DTV_DUAL_TER_SAT_A8297_List(demod)                /* */
 #define  DTV_DUAL_TER_SAT_A8297_Selection(demod,chip_code) /* */

#endif /* DTV_DUAL_TER_SAT_A8297 */

#endif /* Definition of DTV_DUAL_TER_SAT_A8297 */

#if 1  /* Definition of TER_SAT_EVB_BR_DUAL(chip_code) */

#define TER_SAT_EVB_BR_DUAL(chip_code)\
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[0]);\
  SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
  SiLabs_API_SW_Init                  (front_end, 0xce, 0x00, 0xc6);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0x2017, 0);\
  SiLabs_API_SAT_Select_LNB_Chip      (front_end, 25, 0x10);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0/A]");\
  SiLabs_API_SAT_LNB_Chip_Index       (front_end, 0);\
  SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_SAT_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_SAT_Spectrum             (front_end, 0);\
  SiLabs_API_SAT_AGC                  (front_end, 0xb, 1, 0x0, 0);\
  front_end->Si2183_FE->first_init_done     = 1; \
  front_end->Si2183_FE->TER_tuner_init_done = 1; \
  SiLabs_API_HW_Connect               (front_end, 1);\
  /* SW Init for front end 0 */\
  front_end                   = &(FrontEnd_Table[1]);\
  SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
  SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x00);\
  SiLabs_API_Select_TER_Tuner         (front_end, 0x2141, 0);\
  SiLabs_API_Select_SAT_Tuner         (front_end, 0, 0);\
  SiLabs_API_Set_Index_and_Tag        (front_end, 1, "fe[1/B]");\
  SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
  SiLabs_API_TER_Tuner_ClockConfig    (front_end, 1, 1);\
  SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 1);\
  SiLabs_API_TER_FEF_Config           (front_end, 0, 0, 0);\
  SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
  SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
  SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
  SiLabs_API_HW_Connect               (front_end, 1);\
\

#ifdef    TER_SAT_EVB_BR_DUAL
 #define  TER_SAT_EVB_BR_DUAL_List(demod)\
  MACRO_SPRINTF_board_demod(TER_SAT_EVB_BR_DUAL,demod);\

 #define  TER_SAT_EVB_BR_DUAL_Selection(demod,chip_code)\
  MACRO_STRCMP_board_demod(TER_SAT_EVB_BR_DUAL,demod,chip_code);\

#else  /* TER_SAT_EVB_BR_DUAL */

 #define  TER_SAT_EVB_BR_DUAL_List(demod)                /* */
 #define  TER_SAT_EVB_BR_DUAL_Selection(demod,chip_code) /* */

#endif /* TER_SAT_EVB_BR_DUAL */

#endif /* Definition of TER_SAT_EVB_BR_DUAL */

#endif /* MACROS_FOR_DUAL_FRONTENDS */

#define SiLabs_EVBs_List(demod) \
  Si2169_67_76_EVB_REV1_1_76A_List(demod); \
  Si216x_EVB_Rev3_0_List(demod); \
  Si216x_SOC_EVB_Rev1_0_List(demod); \
  Si217USB_MB_Rev1_4_List(24A,demod); \
  Si217USB_MB_Rev1_4_List(44A,demod); \
  Si217USB_MB_Rev1_4_List(51A,demod); \
  Si217USB_MB_Rev1_4_List(90B,demod); \
  Si2168_EVB_Rev2_0_List(demod);\
  Si2168_46_EVB_Rev1_0_List(demod); \
  Si2168_57_EVB_Rev1_0_List(demod); \
  Si216x_8x_EVB_AIR_Rev1_0_List(demod);\
  DTV_SINGLE_TER_SAT_Rev1_0_List(demod); \
  DTV_SINGLE_TER_SAT_Rev2_0_List(demod); \
  TER_SAT_TUNER_EVB_Rev1_0_List(demod); \
  Si216x_8x_EVB_RM_Rev1_0_List(demod); \
  Si216x2_EVB_Rev2_0_77A_57A_List(demod); \
  Si216x2_EVB_Rev1_0_91A_List(demod); \
  Si216x2_EVB_Rev1_1_91B_List(demod); \
  Si21662_EVB_Rev1_0_List(demod); \
  DTV_DUAL_TER_SAT_24A_List(demod); \
  DTV_DUAL_TER_SAT_51A_List(demod); \
  DTV_DUAL_TER_SAT_A8297_List(demod); \
  TER_SAT_EVB_BR_DUAL_List(demod); \
  TER_SAT_EVB_BR_SINGLE_List(demod); \

#define SiLabs_EVBs_Selection(demod,chip_code)  \
  Si2169_67_76_EVB_REV1_1_76A_Selection(demod,chip_code); \
  Si216x_EVB_Rev3_0_Selection(demod,chip_code); \
  Si216x_SOC_EVB_Rev1_0_Selection(demod,chip_code); \
  Si217USB_MB_Rev1_4_Selection(24A,0x2124,demod,chip_code); \
  Si217USB_MB_Rev1_4_Selection(44A,0x2144,demod,chip_code); \
  Si217USB_MB_Rev1_4_Selection(51A,0x2151,demod,chip_code); \
  Si217USB_MB_Rev1_4_Selection(90B,0x2190B,demod,chip_code); \
  Si2168_EVB_Rev2_0_Selection(demod,chip_code);\
  Si2168_46_EVB_Rev1_0_Selection(demod,chip_code); \
  Si2168_57_EVB_Rev1_0_Selection(demod,chip_code); \
  Si216x_8x_EVB_AIR_Rev1_0_Selection(demod,chip_code);\
  DTV_SINGLE_TER_SAT_Rev1_0_Selection(demod,chip_code); \
  DTV_SINGLE_TER_SAT_Rev2_0_Selection(demod,chip_code); \
  TER_SAT_TUNER_EVB_Rev1_0_Selection(demod,chip_code); \
  Si216x_8x_EVB_RM_Rev1_0_Selection(demod,chip_code); \
  Si216x2_EVB_Rev2_0_77A_57A_Selection(demod,chip_code); \
  Si216x2_EVB_Rev1_0_91A_Selection(demod,chip_code); \
  Si216x2_EVB_Rev1_1_91B_Selection(demod,chip_code); \
  Si21662_EVB_Rev1_0_Selection(demod,chip_code); \
  DTV_DUAL_TER_SAT_24A_Selection(demod,chip_code); \
  DTV_DUAL_TER_SAT_51A_Selection(demod,chip_code); \
  DTV_DUAL_TER_SAT_A8297_Selection(demod,chip_code); \
  TER_SAT_EVB_BR_DUAL_Selection(demod,chip_code); \
  TER_SAT_EVB_BR_SINGLE_Selection(demod,chip_code); \

#ifdef    DEMOD_Si2164
  #define SiLabs_EVBs_Si2164A_List        SiLabs_EVBs_List(64A)
  #define SiLabs_EVBs_Si2164A_Selection   SiLabs_EVBs_Selection(64A,0x2164);
#else  /* DEMOD_Si2164 */
  #define SiLabs_EVBs_Si2164A_List       /* */
  #define SiLabs_EVBs_Si2164A_Selection  /* */
#endif /* DEMOD_Si2164 */

#ifdef    DEMOD_Si2165
  #define SiLabs_EVBs_Si2165D_List     \
    Si217USB_MB_Rev1_4_List(76B,65D);\
    Si216x_SOC_EVB_Rev1_0_List(65D);\
    DTV_SINGLE_TER_SAT_Rev2_0_List(65D);

  #define SiLabs_EVBs_Si2165D_Selection \
    Si217USB_MB_Rev1_4_Selection(76B,0x2176,65D,2165); \
    Si216x_SOC_EVB_Rev1_0_Selection(65D,2165);\
    DTV_SINGLE_TER_SAT_Rev2_0_Selection(65D,2165);
#else  /* DEMOD_Si2164 */
  #define SiLabs_EVBs_Si2165D_List       /* */
  #define SiLabs_EVBs_Si2165D_Selection  /* */
#endif /* DEMOD_Si2164 */

#ifdef    DEMOD_Si2167B
  #define SiLabs_EVBs_Si2167B_List        SiLabs_EVBs_List(67B)
  #define SiLabs_EVBs_Si2167B_Selection   SiLabs_EVBs_Selection(67B,0x2167B);
#else  /* DEMOD_Si2167B */
  #define SiLabs_EVBs_Si2167B_List       /* */
  #define SiLabs_EVBs_Si2167B_Selection  /* */
#endif /* DEMOD_Si2167B */

#ifdef    DEMOD_Si2169
  #define SiLabs_EVBs_Si2169A_List        SiLabs_EVBs_List(69A)
  #define SiLabs_EVBs_Si2169A_Selection   SiLabs_EVBs_Selection(69A,2169);
#else  /* DEMOD_Si2169 */
  #define SiLabs_EVBs_Si2169A_List       /* */
  #define SiLabs_EVBs_Si2169A_Selection  /* */
#endif /* DEMOD_Si2169 */

#ifdef    DEMOD_Si2183
  #define SiLabs_EVBs_Si2183A_List        \
    SiLabs_EVBs_List(83A)\
    DTV_SINGLE_TER_SAT_Rev2_0_List(691); \
    RX_SOCKET_EVB_Rev1_0_List(83A);

  #define SiLabs_EVBs_Si2183A_Selection   \
    SiLabs_EVBs_Selection(83A,0x2183)\
    DTV_SINGLE_TER_SAT_Rev2_0_Selection(691,0x2183); \
    RX_SOCKET_EVB_Rev1_0_Selection(83A,0x2183);

#else  /* DEMOD_Si2183 */
  #define SiLabs_EVBs_Si2183A_List       /* */
  #define SiLabs_EVBs_Si2183A_Selection  /* */
#endif /* DEMOD_Si2183 */

#define KNOWN_MACROS_FOR_SILABS_EVBs \
  SiLabs_EVBs_Si2164A_List\
  SiLabs_EVBs_Si2165D_List\
  SiLabs_EVBs_Si2167B_List\
  SiLabs_EVBs_Si2169A_List\
  SiLabs_EVBs_Si2183A_List\

#define SELECT_MACRO_FOR_SILABS_EVBs \
  SiLabs_EVBs_Si2164A_Selection\
  SiLabs_EVBs_Si2165D_Selection\
  SiLabs_EVBs_Si2167B_Selection\
  SiLabs_EVBs_Si2169A_Selection\
  SiLabs_EVBs_Si2183A_Selection\


#endif /* SILABS_EVB_MACROS */

#define SW_INIT_Si2166B_AV2018 /* SW Init for front end 0 */\
front_end                   = &(FrontEnd_Table[0]);\
SiLabs_API_Frontend_Chip            (front_end, 0x2183);\
SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0xc6);\
SiLabs_API_Select_SAT_Tuner         (front_end, 0xa2018, 0);\
SiLabs_API_SAT_Select_LNB_Chip      (front_end, 25, 0x10);\
SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
SiLabs_API_SAT_Clock                (front_end, 1, 44, 24, 2);\
SiLabs_API_SAT_Spectrum             (front_end, 1);\
SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0, 1);\
SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
SiLabs_API_HW_Connect               (front_end, 1);

#define SW_INIT_quad_Si2169A /* SW Init for front end 0 */\
front_end                   = &(FrontEnd_Table[0]);\
SiLabs_API_Frontend_Chip            (front_end, 2169);\
SiLabs_API_SW_Init                  (front_end, 0xc8, 0xc0, 0x14);\
SiLabs_API_Select_TER_Tuner         (front_end, 0x2176, 0);\
SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 2);\
SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
SiLabs_API_Select_SAT_Tuner         (front_end, 0x5812, 0);\
SiLabs_API_SAT_Select_LNB_Chip      (front_end, 25, 0x10);\
SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
SiLabs_API_SAT_Clock                (front_end, 0, 32, 16, 2);\
SiLabs_API_SAT_Spectrum             (front_end, 1);\
SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0 , 0);\
SiLabs_API_Set_Index_and_Tag        (front_end, 0, "fe[0]");\
\
front_end                   = &(FrontEnd_Table[1]);\
SiLabs_API_Frontend_Chip            (front_end, 2169);\
SiLabs_API_SW_Init                  (front_end, 0xca, 0xc2, 0x16);\
SiLabs_API_Select_TER_Tuner         (front_end, 0x2176, 0);\
SiLabs_API_TER_tuner_I2C_connection (front_end, 0);\
SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 2);\
SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
SiLabs_API_Select_SAT_Tuner         (front_end, 0x5812, 0);\
SiLabs_API_SAT_Select_LNB_Chip      (front_end, 25, 0x12);\
SiLabs_API_SAT_tuner_I2C_connection (front_end, 0);\
SiLabs_API_SAT_Clock                (front_end, 1, 44, 24, 2);\
SiLabs_API_SAT_Spectrum             (front_end, 1);\
SiLabs_API_SAT_AGC                  (front_end, 0xd, 1, 0x0 , 0);\
SiLabs_API_Set_Index_and_Tag        (front_end, 1, "fe[1]");\
\
front_end                   = &(FrontEnd_Table[2]);\
SiLabs_API_Frontend_Chip            (front_end, 2169);\
SiLabs_API_SW_Init                  (front_end, 0xcc, 0xc4, 0x00);\
SiLabs_API_Select_TER_Tuner         (front_end, 0x2176, 0);\
SiLabs_API_TER_tuner_I2C_connection (front_end, 2);\
SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 2);\
SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
SiLabs_API_Select_SAT_Tuner         (front_end, 0x5812, 0);\
SiLabs_API_SAT_Select_LNB_Chip      (front_end, 25, 0x14);\
SiLabs_API_SAT_tuner_I2C_connection (front_end, 2);\
SiLabs_API_SAT_Clock                (front_end, 1, 44, 24, 2);\
SiLabs_API_SAT_Spectrum             (front_end, 1);\
SiLabs_API_SAT_AGC                  (front_end, 0x0, 0, 0x0 , 0);\
SiLabs_API_Set_Index_and_Tag        (front_end, 2, "fe[2]");\
\
front_end                   = &(FrontEnd_Table[3]);\
SiLabs_API_Frontend_Chip            (front_end, 2169);\
SiLabs_API_SW_Init                  (front_end, 0xce, 0xc6, 0x00);\
SiLabs_API_Select_TER_Tuner         (front_end, 0x2176, 0);\
SiLabs_API_TER_tuner_I2C_connection (front_end, 2);\
SiLabs_API_TER_Clock                (front_end, 1, 44, 24, 2);\
SiLabs_API_TER_AGC                  (front_end, 0x0, 0, 0xa, 0);\
SiLabs_API_TER_Tuner_AGC_Input      (front_end, 1);\
SiLabs_API_TER_Tuner_FEF_Input      (front_end, 1);\
SiLabs_API_TER_Tuner_IF_Output      (front_end, 0);\
SiLabs_API_Select_SAT_Tuner         (front_end, 0x5812, 0);\
SiLabs_API_SAT_Select_LNB_Chip      (front_end, 25, 0x16);\
SiLabs_API_SAT_tuner_I2C_connection (front_end, 2);\
SiLabs_API_SAT_Clock                (front_end, 1, 44, 24, 2);\
SiLabs_API_SAT_Spectrum             (front_end, 1);\
SiLabs_API_SAT_AGC                  (front_end, 0x0, 0, 0x0 , 0);\
SiLabs_API_Set_Index_and_Tag        (front_end, 3, "fe[3]");\


#endif /* _SiLabs_API_L3_Config_Macros_H_ */
