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
/*                     SiLabs Layer 1                  LNB Controller Functions                              */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains all API Functions for the A8297 LNB controller on the RF board                */
/*     All functions are declared in A8297_L1_API.h                                                          */
/*************************************************************************************************************/
/* Change log:

  As from xxxx:
   Initial version, based on A8302 code. NB: This is UNTESTED on HW! Expect possible issues!

**************************************************************************************************************/
/*#define RWTRACES*/
#define Layer1_A8297
#include "A8297_L1_API.h"

void          L1_A8297_Init             (A8297_Context *context, unsigned int add) {
  SiTRACE("L1_A8297_Init starting...\n");
  context->i2c = &(context->i2cObj);
  L0_Init(context->i2c);
  L0_SetAddress(context->i2c, add, 0);
  context->LNB2                       = 0;
  context->vsel_voltage               = vsel_voltage_13333_mV;
  context->lnb_output                 = lnb_output_disabled;
  context->A8297_BYTES                = &(context->A8297_BYTES_Array[0]);
  SiTRACE("A8297 Init vsel_voltage %d LNB_output %d\n", context->vsel_voltage, context->lnb_output);
  SiTRACE("L1_A8297_Init complete...\n");
}
unsigned int  L1_A8297_Index            (A8297_Context *context, unsigned int index) {
  if (index) {
    context->LNB2                       = 1;
  } else {
    context->LNB2                       = 0;
  }
  return context->LNB2;
}
void          L1_A8297_MatchBytes       (A8297_Context *LNB1, A8297_Context *LNB2) {
  SiTRACE("L1_A8297_MatchBytes : matching bytes for LNB1 at 0x%08x and LNB2 at 0x%08x\n", LNB1, LNB2);
  LNB1->A8297_BYTES = LNB2->A8297_BYTES;
}
void          L1_A8297_ControlBytes     (A8297_Context *context) {
  unsigned char mask;
  if (context->LNB2 == 0) { mask = 0xf0; }
  if (context->LNB2 == 1) { mask = 0x0f; }
  context->A8297_BYTES[0] = (context->A8297_BYTES[0] & mask)
  +((context->vsel_voltage)              << (vsel_voltage_OFFSET + 4*context->LNB2) )
  +((context->lnb_output)                << (lnb_output_OFFSET   + 4*context->LNB2) )
  ;
  SiTRACE("A8297 LNB %d vsel_voltage %d LNB_output %d\n", context->LNB2, context->vsel_voltage, context->lnb_output);
}
void          L1_A8297_FillStatus       (A8297_Context *context) {
  unsigned char d;
  d = context->LNB2;
  context->lnb_status        = ((context->A8297_BYTES[2])>>(0+d))&0x01;
  context->overcurrent       = ((context->A8297_BYTES[2])>>(2+d))&0x01;
  context->power             = ((context->A8297_BYTES[2])>>(4+d))&0x01;
  context->undervoltage      = ((context->A8297_BYTES[2])>>(6+d))&0x01;
  context->thermal_shutdown  = ((context->A8297_BYTES[2])>>(7  ))&0x01;

  context->charge_pump       = ((context->A8297_BYTES[3])>>(0+d))&0x01;
  context->tone_detect       = ((context->A8297_BYTES[3])>>(2+d))&0x01;
  context->trims             = ((context->A8297_BYTES[3])>>(5  ))&0x01;

  if (context->lnb_status        == lnb_status_disabled_or_fault     ) { SiTRACE("A8297 ERROR: lnb_status_disabled_or_fault!\n"); }
  if (context->overcurrent       == overcurrent_above_threshold      ) { SiTRACE("A8297 ERROR: overcurrent_above_threshold!\n"); }
  if (context->power             == power_out_of_range               ) { SiTRACE("A8297 ERROR: power_out_of_range!\n");           }
  if (context->undervoltage      == undervoltage_out_of_range        ) { SiTRACE("A8297 ERROR: undervoltage_out_of_range!\n"); };
  if (context->thermal_shutdown  == thermal_shutdown_overtemperature ) { SiTRACE("A8297 ERROR: thermal_shutdown_overtemperature!\n"); };

  if (context->charge_pump       == charge_pump_error                ) { SiTRACE("A8297 ERROR: charge_pump_error!\n"); };
  if (context->trims             == trims_above_threshold            ) { SiTRACE("A8297 ERROR: trims_above_threshold!\n"); };
  /* Statuses not related to errors */
  if (context->tone_detect       == tone_detect_detected             ) { SiTRACE("A8297 tone_detect_detected\n"); };
}
void          L1_A8297_Status_And_Write (A8297_Context *context) {
  L0_ReadBytes  (context->i2c, 1, 2, &(context->A8297_BYTES[1]));
  L1_A8297_FillStatus  (context);

  L1_A8297_ControlBytes(context);
  L0_WriteBytes (context->i2c, 0, 1, &(context->A8297_BYTES[0]));
}
unsigned int  L1_A8297_InitAfterReset   (A8297_Context *context) {
  SiTRACE("L1_A8297_InitAfterReset starting LNB%1d...\n", context->LNB2);
  L1_A8297_Status_And_Write(context);
  SiTRACE("L1_A8297_InitAfterRset complete...\n");
  return 1;
}
void          L1_A8297_Supply           (A8297_Context *context, unsigned char supply_off_on) {
  if (supply_off_on == A8297_SUPPLY_OFF) {
    context->lnb_output                 = lnb_output_disabled;
  } else {
    context->lnb_output                 = lnb_output_enabled;
  }
  L1_A8297_Status_And_Write(context);
}
void          L1_A8297_Polarity         (A8297_Context *context, unsigned char horizontal_vertical) {
  if (horizontal_vertical == A8297_HORIZONTAL) {
    context->vsel_voltage               = vsel_voltage_13333_mV;
  } else {
    context->vsel_voltage               = vsel_voltage_18667_mV;
  }
  if (context->lnb_output == lnb_output_enabled ) {
    L1_A8297_Status_And_Write(context);
  }
}
void          L1_A8297_Voltage          (A8297_Context *context, unsigned char voltage) {
  switch (voltage) {
    case 13: context->vsel_voltage = vsel_voltage_13333_mV; context->lnb_output = lnb_output_enabled; break;
    case 18: context->vsel_voltage = vsel_voltage_18667_mV; context->lnb_output = lnb_output_enabled; break;
    default: context->lnb_output = lnb_output_disabled; break;
  }
  L1_A8297_Status_And_Write(context);
}
char *L1_A8297_TAG_Text       (void) { return (char*)"A8297 V0.0.1 Allegro LNB controller"; }
