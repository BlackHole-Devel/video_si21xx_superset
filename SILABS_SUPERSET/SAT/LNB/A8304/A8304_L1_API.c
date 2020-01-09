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
/*   This source code contains all API Functions for the A8304 LNB controller on the RF board                */
/*     All functions are declared in A8304_L1_API.h                                                          */
/*************************************************************************************************************/
/* Change log:

  As from V0.0.2.0 (svn6171):
    <correction>[I2c/Read] In L1_A8304_Init: setting addSize to 1 in call to L0_SetAddress(context->i2c, add, 1);
    <improvement>[Traces] In L1_A8304_WriteBytes: removing once occurrence of context->OCP when tracing A8304 status byte

  As from V0.0.1.0:
    Working version, tested on customer platform by Angus Li (SiLabs)

  As from V0.0.0.1:
    Initial UNTESTED version

**************************************************************************************************************/
/*#define RWTRACES*/
#define Layer1_A8304
#include "A8304_L1_API.h"

void  L1_A8304_Init           (A8304_Context *context, unsigned int add) {
  SiTRACE("L1_A8304_Init starting...\n");
  context->i2c = &(context->i2cObj);
  L0_Init(context->i2c);
  L0_SetAddress(context->i2c, add, 1);
  context->vsel_voltage               = vsel_voltage_13333_mV;
  context->lnb_output                 = lnb_output_disabled;
  context->tone_mode                  = tone_mode_envelop;
  context->ocp_25                     = 0;
  context->sink_dis                   = 0;
  context->A8304_BYTES[0] = 0x00;
  SiTRACE("L1_A8304_Init complete...\n");
}
void  L1_A8304_WriteBytes     (A8304_Context *context) {
  context->A8304_BYTES[0] =
   ((context->vsel_voltage)             << vsel_voltage_OFFSET)
  +((context->lnb_output)               << lnb_output_OFFSET)
  +((context->tone_mode)                << tone_mode_OFFSET)
  +((context->ocp_25)                   << ocp_25_OFFSET)
  +((context->sink_dis)                 << sink_dis_OFFSET);

  L0_ReadRawBytes(context->i2c, 0, 1, &(context->A8304_BYTES[1]));
  context->DIS  = ((context->A8304_BYTES[1])>>0)&0x01;
  context->CPOK = ((context->A8304_BYTES[1])>>1)&0x01;
  context->OCP  = ((context->A8304_BYTES[1])>>2)&0x01;
  context->PNG  = ((context->A8304_BYTES[1])>>4)&0x01;
  context->TSD  = ((context->A8304_BYTES[1])>>6)&0x01;
  context->UVLO = ((context->A8304_BYTES[1])>>7)&0x01;

  SiTRACE("A8304 status byte: 0x%02x DIS %d, CPOK %d, OCP %d, PNG %d, TSD %d, UVLO %d\n",
          context->A8304_BYTES[1],
          context->DIS,
          context->CPOK,
          context->OCP,
          context->PNG,
          context->TSD,
          context->UVLO
          );
  if ((context->DIS == 1) && (context->lnb_output == lnb_output_enabled)) {
    SiTRACE("A8304 ERROR: DIS  (Fault)!\n");
  }
  if (context->CPOK == 0) {
    SiTRACE("A8304 ERROR: CPOK (ChargePump)!\n");
  }
  if (context->OCP == 1) {
    SiTRACE("A8304 ERROR: OCP  (OverCurrent)!\n");
  }
  if (context->PNG == 1) {
    SiTRACE("A8304 ERROR: PNG  (Power Not Good)!\n");
  }
  if (context->TSD == 1) {
    SiTRACE("A8304 ERROR: TSD  (Thermal Shutdown)!\n");
  }
  if (context->UVLO == 1) {
    SiTRACE("A8304 ERROR: UVLO  (Under Voltage Lockout)!\n");
  }

  L0_WriteBytes (context->i2c, 0, 1, context->A8304_BYTES);
}
int   L1_A8304_InitAfterReset (A8304_Context *context) {
  SiTRACE("L1_A8304_InitAfterRset starting...\n");
  L1_A8304_WriteBytes(context);
  SiTRACE("L1_A8304_InitAfterRset complete...\n");
  return 1;
}
void  L1_A8304_Supply         (A8304_Context *context, unsigned char supply_off_on) {
  if (supply_off_on == A8304_SUPPLY_OFF) {
    context->lnb_output                 = lnb_output_disabled;
  } else {
    context->lnb_output                 = lnb_output_enabled;
  }
  L1_A8304_WriteBytes(context);
}
void  L1_A8304_Polarity       (A8304_Context *context, unsigned char horizontal_vertical) {
  if (horizontal_vertical == A8304_HORIZONTAL) {
    context->vsel_voltage               = vsel_voltage_13333_mV;
  } else {
    context->vsel_voltage               = vsel_voltage_18667_mV;
  }
  if (context->lnb_output == lnb_output_enabled ) {
    L1_A8304_WriteBytes(context);
  }
}
void  L1_A8304_Voltage        (A8304_Context *context, unsigned char voltage) {
  switch (voltage) {
    case 13: context->vsel_voltage = vsel_voltage_13333_mV; context->lnb_output = lnb_output_enabled; break;
    case 18: context->vsel_voltage = vsel_voltage_18667_mV; context->lnb_output = lnb_output_enabled; break;
    default: context->lnb_output = lnb_output_disabled; break;
  }
  L1_A8304_WriteBytes(context);
}

char *L1_A8304_TAG_Text       (void) { return (char*)"A8304 V0.0.2.0 Allegro LNB controller"; }


