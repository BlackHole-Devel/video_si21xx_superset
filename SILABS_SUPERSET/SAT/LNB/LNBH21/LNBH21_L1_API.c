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
/*                     SILEMBIA Layer 1                  RF Tuner Functions                                  */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains all API Functions for the RDA5812 Tuner on the RF board                       */
/*     All included functions can be accessed by the higher software level as imports                        */
/*     All functions are declared in Silabs_L1_RF_RDA5812_API.h                                              */
/*************************************************************************************************************/
/* Change log:

  As from SVN3031:
   In L1_LNBH21_InitAfterReset:
    return 1;

**************************************************************************************************************/
/*#define RWTRACES*/
#define Layer1_lnbh21
#include "LNBH21_L1_API.h"

unsigned char LNBH21_BYTE;

void  L1_LNBH21_Init           (LNBH21_Context *context, unsigned int add) {
  SiTRACE("L1_LNBH21_Init starting...\n");
  context->i2c = &(context->i2cObj);
  L0_Init(context->i2c);
  L0_SetAddress(context->i2c, add, 0);
  context->current_limiting      = 0;
  context->transmit_receive      = 0;
  context->tone_source           = 0;
  context->long_line_compensation= 0;
  context->polarisation          = 0;
  context->lnbh_enable           = 0;
  context->power_block           = 0;
  context->overload              = 0;
  SiTRACE("L1_LNBH21_Init complete...\n");
};
void  L1_LNBH21_WriteByte      (LNBH21_Context *context) {
  LNBH21_BYTE =
   ((context->current_limiting)       << 7)
  +((context->transmit_receive)       << 6)
  +((context->tone_source)            << 5)
  +((context->long_line_compensation) << 4)
  +((context->polarisation)           << 3)
  +((context->lnbh_enable)            << 2)
  +((context->power_block)            << 1)
  +((context->overload)               << 0);
  L0_WriteBytes (context->i2c, 0, 1, &LNBH21_BYTE);
};
int   L1_LNBH21_InitAfterReset (LNBH21_Context *context) {
  SiTRACE("L1_LNBH21_InitAfterRset starting...\n");
  L1_LNBH21_WriteByte(context);
  SiTRACE("L1_LNBH21_InitAfterRset complete...\n");
  return 1;
};
void  L1_LNBH21_Supply         (LNBH21_Context *context, unsigned char supply_off_on) {
  if (supply_off_on == LNBH21_SUPPLY_OFF) {
    context->lnbh_enable  = lnbh_enable_disabled;
  } else {
    context->lnbh_enable  = lnbh_enable_enabled;
  }
  L1_LNBH21_WriteByte(context);
}
void  L1_LNBH21_Polarity       (LNBH21_Context *context, unsigned char horizontal_vertical) {
  if (horizontal_vertical == LNBH21_HORIZONTAL) {
    context->polarisation = polarisation_13_volts_v;
  } else {
    context->polarisation = polarisation_18_volts_h;
  }
  if (context->lnbh_enable == lnbh_enable_enabled ) {
    L1_LNBH21_WriteByte(context);
  }
}
void  L1_LNBH21_Voltage        (LNBH21_Context *context, unsigned char voltage) {
  switch (voltage) {
    case 13: context->polarisation = polarisation_13_volts_v; context->lnbh_enable = lnbh_enable_enabled; break;
    case 18: context->polarisation = polarisation_18_volts_h; context->lnbh_enable = lnbh_enable_enabled; break;
    default: context->lnbh_enable = lnbh_enable_disabled; break;
  }
  L1_LNBH21_WriteByte(context);
}

char *L1_LNBH21_TAG_Text       (void) { return (char*)"SVN3054"; };


