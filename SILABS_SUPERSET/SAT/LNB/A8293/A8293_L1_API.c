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
/*   This source code contains all API Functions for the A8293 LNB controller on the RF board                */
/*     All functions are declared in A8293_L1_API.h                                                          */
/*************************************************************************************************************/
/* Change log:

  As from SVN6567: Adding declaration of L1_A8293_WriteBytes 

  As fom SVN5968:
   Correction of vsel_voltage_NBBIT (4)
   Correction of file header and TAG text

  As from SVN5510:
   Correction of some register values
   Addition of i2c read action to allow starting the part (it's required to read the status byte to clear errors)

  As from SVN3031:
   In L1_A8293_InitAfterReset:
    return 1;

**************************************************************************************************************/
/*#define RWTRACES*/
#define Layer1_A8293
#include "A8293_L1_API.h"

void  L1_A8293_WriteBytes     (A8293_Context *context);

void  L1_A8293_Init           (A8293_Context *context, unsigned int add) {
  SiTRACE("L1_A8293_Init starting...\n");
  context->i2c = &(context->i2cObj);
  L0_Init(context->i2c);
  L0_SetAddress(context->i2c, add, 0);
  context->vsel_voltage               = vsel_voltage_13042_mV;
  context->overcurrent_disable_timer  = overcurrent_disable_timer_enabled;
  context->lnb_output                 = lnb_output_disabled;
  context->address_b0                 = address_b0_byte0;
  context->tone_mode                  = tone_mode_envelop;
  context->tone_gate                  = tone_gate_tone_on;
  context->address_b1                 = address_b1_byte1;
  context->A8293_BYTES[0] = 0x00;
  context->A8293_BYTES[1] = 0x00;
  SiTRACE("L1_A8293_Init complete...\n");
}
void  L1_A8293_WriteBytes     (A8293_Context *context) {
  context->A8293_BYTES[0] =
   ((context->vsel_voltage)              << vsel_voltage_OFFSET)
  +((context->overcurrent_disable_timer) << overcurrent_disable_timer_OFFSET)
  +((context->lnb_output)                << lnb_output_OFFSET)
  +((context->address_b0)                << address_b0_OFFSET);
  context->A8293_BYTES[1] =
  +((context->tone_mode)                << tone_mode_OFFSET)
  +((context->tone_gate)                << tone_gate_OFFSET)
  +((context->address_b1)               << address_b1_OFFSET);

  L0_ReadBytes  (context->i2c, 0, 2, &(context->A8293_BYTES[2]));
  context->OCP = ((context->A8293_BYTES[2])>>2)&0x01;
  context->PNG = ((context->A8293_BYTES[2])>>4)&0x01;
  context->TSD = ((context->A8293_BYTES[2])>>6)&0x01;
  context->VUV = ((context->A8293_BYTES[2])>>7)&0x01;

  SiTRACE("A8293 status byte: 0x%02x OCP %d, PNG %d, TSD %d, VUV %d\n", context->A8293_BYTES[2], context->OCP, context->PNG, context->TSD, context->VUV);
  if (context->OCP == 1) {
    SiTRACE("A8293 ERROR: OCP (OverCurrent)!\n");
  }
  if (context->TSD == 1) {
    SiTRACE("A8293 ERROR: TSD (Thermal Shutdown)!\n");
  }
  if (context->PNG == 1) {
    SiTRACE("A8293 ERROR: PNG (Power Not Good)!\n");
  }
  if (context->VUV == 1) {
    SiTRACE("A8293 ERROR: VUV (Under Voltage Lockout)!\n");
  }

  L0_WriteBytes (context->i2c, 0, 2, context->A8293_BYTES);
}
int   L1_A8293_InitAfterReset (A8293_Context *context) {
  SiTRACE("L1_A8293_InitAfterRset starting...\n");
  L1_A8293_WriteBytes(context);
  SiTRACE("L1_A8293_InitAfterRset complete...\n");
  return 1;
}
void  L1_A8293_Supply         (A8293_Context *context, unsigned char supply_off_on) {
  if (supply_off_on == A8293_SUPPLY_OFF) {
    context->lnb_output                 = lnb_output_disabled;
  } else {
    context->lnb_output                 = lnb_output_enabled;
  }
  L1_A8293_WriteBytes(context);
}
void  L1_A8293_Polarity       (A8293_Context *context, unsigned char horizontal_vertical) {
  if (horizontal_vertical == A8293_HORIZONTAL) {
    context->vsel_voltage               = vsel_voltage_13042_mV;
  } else {
    context->vsel_voltage               = vsel_voltage_18042_mV;
  }
  if (context->lnb_output == lnb_output_enabled ) {
    L1_A8293_WriteBytes(context);
  }
}
void  L1_A8293_Voltage        (A8293_Context *context, unsigned char voltage) {
  switch (voltage) {
    case 13: context->vsel_voltage = vsel_voltage_13042_mV; context->lnb_output = lnb_output_enabled; break;
    case 18: context->vsel_voltage = vsel_voltage_18042_mV; context->lnb_output = lnb_output_enabled; break;
    default: context->lnb_output = lnb_output_disabled; break;
  }
  L1_A8293_WriteBytes(context);
}

char *L1_A8293_TAG_Text       (void) { return (char*)"A8293 V0.0.1 Allegro LNB controller"; }


