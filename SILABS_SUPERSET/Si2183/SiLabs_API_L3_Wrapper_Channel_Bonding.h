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
#ifndef  _SiLabs_API_L3_Wrapper_Channel_Bonding_H_
#define  _SiLabs_API_L3_Wrapper_Channel_Bonding_H_
/* Change log:

  As from V2.9.0:
  <new_feature>[Channel_Bonding/Duals] Adding TS Bonding capability via SiLabs_API_L3_Channel_Bonding.c/.h
        This is only valid for dual demodulators with the TS bonding feature.

 *************************************************************************************************************/

#include "SiLabs_API_L3_Wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

/* possible values for TS Bonding parts selection */
typedef enum  _SILABS_Channel_Bonding_Parts       {
  SILABS_ONE_DUAL    = 2,
  SILABS_DUAL_SINGLE = 3,
  SILABS_DUAL_DUAL   = 4
} SILABS_Channel_Bonding_Parts;

/* possible values for TS Bonding role */
typedef enum  _SILABS_Channel_Bonding_Role        {
  SILABS_TS_CHANNEL_BONDING_OFF = 0,
  SILABS_TS_MASTER              = 1,
  SILABS_TS_SLAVE               = 2,
  SILABS_TS_SLAVE_BRIDGE        = 3
} SILABS_Channel_Bonding_Role;

/* possible values for TS Output */
typedef enum  _SILABS_TS_Bus        {
  SILABS_TS_NO_CONNECTION = 0,
  SILABS_TS_1 = 1,
  SILABS_TS_2 = 2,
} SILABS_TS_BUS;

/* Structure used to store all bonding-related information */
typedef struct _SILABS_Channel_Bonding            {
  unsigned int                  nbFEs;
  SILABS_FE_Context            *fe[4];
  SILABS_FE_Context            *master;
  SILABS_FE_Context            *bridge;
  SILABS_FE_Context            *slave;
  SILABS_FE_Context            *unused;
  SILABS_Channel_Bonding_Parts  parts;
  unsigned int                  first_dual_output;
  unsigned int                  second_dual_input;
} SILABS_Channel_Bonding;

extern SILABS_Channel_Bonding  Channel_Bonding_Context;

// SILABS_Channel_Bonding_Config          ( Channel_Bonding, fe[0], fe[1],  NULL,  NULL, 0, 0);
// SILABS_Channel_Bonding                 ( Channel_Bonding, SILABS_ONE_DUAL,    SILABS_TS_1);

// SILABS_Channel_Bonding_Config          ( Channel_Bonding, fe[0], fe[1], fe[2], fe[3], SILABS_TS_2, SILABS_TS_1);
// SILABS_Channel_Bonding                 ( Channel_Bonding, SILABS_DUAL_DUAL,   SILABS_TS_2);

// SILABS_Channel_Bonding_Config          ( Channel_Bonding, fe[0], fe[1], fe[2],  NULL, SILABS_TS_1, SILABS_TS_2);
// SILABS_Channel_Bonding                 ( Channel_Bonding, SILABS_DUAL_SINGLE, SILABS_TS_1);

signed   int   SiLabs_Channel_Bonding_SW_Init    (SILABS_Channel_Bonding  *Channel_Bonding
                                                , SILABS_FE_Context  *first_dual_die_A
                                                , SILABS_FE_Context  *first_dual_die_B
                                                , SILABS_FE_Context  *second_dual_die_A
                                                , SILABS_FE_Context  *second_dual_die_B
                                                , SILABS_TS_BUS       first_dual_output
                                                , SILABS_TS_BUS       second_dual_input
                                                 );

signed   int   SiLabs_Channel_Bonding_Stop       (SILABS_Channel_Bonding *Channel_Bonding);

signed   int   SiLabs_Channel_Bonding            (SILABS_Channel_Bonding       *Channel_Bonding
                                                , SILABS_Channel_Bonding_Parts  parts
                                                , SILABS_TS_BUS                 TS_output );

#if defined( __cplusplus )
}
#endif

#endif /* _SiLabs_API_L3_Wrapper_Channel_Bonding_H_ */
