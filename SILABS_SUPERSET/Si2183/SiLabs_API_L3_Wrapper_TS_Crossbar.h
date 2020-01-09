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
#ifndef  _SiLabs_API_L3_Wrapper_TS_Crossbar_H_
#define  _SiLabs_API_L3_Wrapper_TS_Crossbar_H_
/* Change log:

  As from V2.4.0:
  <new_feature>[TS_Crossbar/Duals] Adding TS Crossbar capability via SiLabs_API_L3_TS_Crossbar.c/.h
        This is only valid for dual demodulators with the TS crossbar feature.

 *************************************************************************************************************/

#include "SiLabs_API_L3_Wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

/* possible values for TS1/TS2 signal */
typedef enum  _CUSTOM_TS_Crossbar_Enum       {
  SILABS_TS_CROSSBAR_TRISTATE      = 0,
  SILABS_TS_CROSSBAR_TS_A          = 1,
  SILABS_TS_CROSSBAR_TS_B          = 2
} CUSTOM_TS_Crossbar_Enum;

/* TS1/TS2 output configuration structure */
typedef struct _SILABS_TS_Config              {
      CUSTOM_TS_Mode_Enum   ts_mode;                  /* */
      unsigned char         ts_serial_data_strength;
      unsigned char         ts_serial_data_shape;
      unsigned char         ts_serial_clk_strength;
      unsigned char         ts_serial_clk_shape;

      unsigned char         ts_serial_slr_enable;
      unsigned char         ts_serial_clk_slr;
      unsigned char         ts_serial_data_slr;

      unsigned char         ts_parallel_data_strength;
      unsigned char         ts_parallel_data_shape;
      unsigned char         ts_parallel_clk_strength;
      unsigned char         ts_parallel_clk_shape;
} SILABS_TS_Config;

/* Structure used to store all crossbar-related information */
typedef struct _SILABS_TS_Crossbar            {
      SILABS_FE_Context  *fe_A;       /* First  demodulator in the dual demodulator (demod A) */
      SILABS_FE_Context  *fe_B;       /* Second demodulator in the dual demodulator (demod B) */
      SILABS_TS_Config   *ts_1;       /* TS1 output configuration pointer                     */
      SILABS_TS_Config   *ts_2;       /* TS2 output configuration pointer                     */
      SILABS_TS_Config    ts_1_Obj;   /* TS1 output configuration structure                   */
      SILABS_TS_Config    ts_2_Obj;   /* TS2 output configuration structure                   */
      CUSTOM_TS_Crossbar_Enum ts_1_signal;
      CUSTOM_TS_Crossbar_Enum ts_2_signal;
      unsigned char       state_known;/* 0 if current config is unknown, 1 once read from HW  */
} SILABS_TS_Crossbar;

signed   int   SiLabs_TS_Crossbar_SW_Init         (SILABS_TS_Crossbar *ts_crossbar, SILABS_FE_Context  *fe_A, SILABS_FE_Context  *fe_B );
signed   int   SiLabs_TS_Crossbar_TS_Status       (SILABS_TS_Crossbar *ts_crossbar);
char*          SiLabs_TS_Crossbar_Signal_Text     (CUSTOM_TS_Crossbar_Enum  ts_signal);
void           SiLabs_TS_Crossbar_Status_Text     (SILABS_TS_Crossbar *ts_crossbar);
signed   int   SiLabs_TS_Crossbar_TS_Mode         (SILABS_TS_Config   *ts_crossbar_config, CUSTOM_TS_Mode_Enum ts_mode );
signed   int   SiLabs_TS_Crossbar_Serial_Config   (SILABS_TS_Config   *ts_crossbar_settings,
                                                    unsigned char ts_serial_data_strength,   unsigned char ts_serial_data_shape ,
                                                    unsigned char ts_serial_clk_strength ,   unsigned char ts_serial_clk_shape  ,
                                                    unsigned char ts_slr_serial_enable,      unsigned char ts_slr_serial_clk, unsigned char ts_slr_serial_data);
signed   int   SiLabs_TS_Crossbar_Parallel_Config (SILABS_TS_Config   *ts_crossbar_settings,
                                                    unsigned char ts_parallel_data_strength, unsigned char ts_parallel_data_shape ,
                                                    unsigned char ts_parallel_clk_strength , unsigned char ts_parallel_clk_shape  );
signed   int   SiLabs_TS_Crossbar_TS1_Signal      (SILABS_TS_Crossbar *ts_crossbar,  CUSTOM_TS_Crossbar_Enum ts_signal);
signed   int   SiLabs_TS_Crossbar_TS2_Signal      (SILABS_TS_Crossbar *ts_crossbar,  CUSTOM_TS_Crossbar_Enum ts_signal);
signed   int   SiLabs_TS_Crossbar_TS1_TS2         (SILABS_TS_Crossbar *ts_crossbar,
                                                   CUSTOM_TS_Crossbar_Enum  ts_1_signal,
                                                   CUSTOM_TS_Mode_Enum      ts_1_mode  ,
                                                   CUSTOM_TS_Crossbar_Enum  ts_2_signal,
                                                   CUSTOM_TS_Mode_Enum      ts_2_mode );
#if defined( __cplusplus )
}
#endif


#define   MACROS_FOR_DUAL_USING_TS_XBAR

#ifdef    MACROS_FOR_DUAL_USING_TS_XBAR

#define TS_XBAR_INIT_EXAMPLE \
fe_A = &(FrontEnd_Table[0]);\
fe_B = &(FrontEnd_Table[1]);\
SiLabs_TS_Crossbar_SW_Init         (crossbar, fe_A, fe_B);\
SiLabs_TS_Crossbar_TS_Mode         (crossbar->ts_1, SILABS_TS_TRISTATE);\
SiLabs_TS_Crossbar_Serial_Config   (crossbar->ts_1, 7, 0, 7, 0);\
SiLabs_TS_Crossbar_Parallel_Config (crossbar->ts_1, 3, 2, 4, 3);\
SiLabs_TS_Crossbar_TS_Mode         (crossbar->ts_2, SILABS_TS_TRISTATE);\
SiLabs_TS_Crossbar_Serial_Config   (crossbar->ts_2, 7, 1, 7, 1);\
SiLabs_TS_Crossbar_Parallel_Config (crossbar->ts_2, 3, 1, 4, 1);

#endif /* MACROS_FOR_DUAL_USING_TS_XBAR */

#endif /* _SiLabs_API_L3_Wrapper_TS_Crossbar_H_ */
