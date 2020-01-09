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
/*                     Silicon Laboratories Layer 1   RF LNB chip Functions                                  */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains all API Functions for the Allegro A8302 LNB chip on the RF board              */
/*     All included functions can be accessed by the higher software level as imports                        */
/*     All functions are declared in A8302_l1_API.h                                                          */
/*************************************************************************************************************/
/* Change log:

  As from xxxx:
   Initial version, based on A8293 code

**************************************************************************************************************/
/*#define RWTRACES*/
#define Layer1_A8302
#include "A8302_L1_API.h"

void          L1_A8302_Init             (A8302_Context *context, unsigned int add) {
  SiTRACE("L1_A8302_Init starting...\n");
  context->i2c = &(context->i2cObj);
  L0_Init(context->i2c);
  L0_SetAddress(context->i2c, add, 0);

  context->LNB2                       = 0;
  context->tone_mode                  = tone_mode_envelop;
  context->overcurrent_disable_timer  = overcurrent_disable_timer_45_ms;
  context->EPF_setting_delay          = EPF_setting_delay_0_0_ms;
  context->frequency                  = frequency_563_khz;
  context->compensation_network       = compensation_network_ceramic;
  context->fault_restart_mode         = fault_restart_mode_latch;
  context->sink                       = sink_disabled;
  context->vsel_voltage               = vsel_voltage_13333_mV;
  context->lnb_output                 = lnb_output_disabled;
  context->bump_up                    = bump_up_on;
  context->SWM_mode                   = SWM_mode_10_ma;
  context->tone_delay                 = tone_delay_0_us;

  context->A8302_BYTES[0] = 0x00;
  context->A8302_BYTES[1] = 0x00;
  SiTRACE("L1_A8302_Init complete...\n");
}
unsigned int  L1_A8302_Index            (A8302_Context *context, unsigned int index) {
  if (index) {
    context->LNB2                       = 1;
  } else {
    context->LNB2                       = 0;
  }
  return context->LNB2;
}
void          L1_A8302_ControlBytes     (A8302_Context *context) {
  context->A8302_BYTES[0] =
   ((context->tone_mode)                 << tone_mode_OFFSET)
  +((context->overcurrent_disable_timer) << overcurrent_disable_timer_OFFSET)
  +((context->EPF_setting_delay)         << EPF_setting_delay_OFFSET)
  +((context->frequency)                 << frequency_OFFSET)
  +((context->compensation_network)      << compensation_network_OFFSET)
  +((context->fault_restart_mode)        << fault_restart_mode_OFFSET)
  +((context->sink)                      << sink_OFFSET);

  context->A8302_BYTES[1+context->LNB2] =
  +((context->vsel_voltage)              << vsel_voltage_OFFSET)
  +((context->lnb_output)                << lnb_output_OFFSET)
  +((context->bump_up)                   << bump_up_OFFSET)
  +((context->SWM_mode)                  << SWM_mode_OFFSET)
  +((context->tone_delay)                << tone_delay_OFFSET);
}
void          L1_A8302_FillStatus       (A8302_Context *context) {
  unsigned char d;
  d = context->LNB2;
  context->lnb_status        = ((context->A8302_BYTES[3])>>(0+d))&0x01;
  context->overcurrent       = ((context->A8302_BYTES[3])>>(2+d))&0x01;
  context->power             = ((context->A8302_BYTES[3])>>(4+d))&0x01;
  context->undervoltage      = ((context->A8302_BYTES[3])>>(6+d))&0x01;
  context->thermal_shutdown  = ((context->A8302_BYTES[3])>>(7  ))&0x01;

  context->charge_pump       = ((context->A8302_BYTES[4])>>(0+d))&0x01;
  context->tone_detect       = ((context->A8302_BYTES[4])>>(2+d))&0x01;
  context->EPF_warning       = ((context->A8302_BYTES[4])>>(4  ))&0x01;
  context->trims             = ((context->A8302_BYTES[4])>>(5  ))&0x01;
  context->cable_boost       = ((context->A8302_BYTES[4])>>(6+d))&0x01;

  if (context->lnb_status        == lnb_status_disabled_or_fault     ) { SiTRACE("A8302 ERROR: lnb_status_disabled_or_fault!\n"); }
  if (context->power             == power_out_of_range               ) { SiTRACE("A8302 ERROR: power_out_of_range!\n");           }
  if (context->undervoltage      == undervoltage_out_of_range        ) { SiTRACE("A8302 ERROR: undervoltage_out_of_range!\n"); };
  if (context->thermal_shutdown  == thermal_shutdown_overtemperature ) { SiTRACE("A8302 ERROR: thermal_shutdown_overtemperature!\n"); };
  if (context->charge_pump       == charge_pump_error                ) { SiTRACE("A8302 ERROR: charge_pump_error!\n"); };
  if (context->EPF_warning       == EPF_warning_vin_below_threshold  ) { SiTRACE("A8302 ERROR: EPF_warning_vin_below_threshold!\n"); };
  if (context->trims             == trims_above_threshold            ) { SiTRACE("A8302 ERROR: trims_above_threshold!\n"); };
}
void          L1_A8302_Status_And_Write (A8302_Context *context) {
  L0_ReadBytes  (context->i2c, 0, 2, &(context->A8302_BYTES[3]));
  L1_A8302_FillStatus  (context);

  L1_A8302_ControlBytes(context);
  L0_WriteBytes (context->i2c, 0, 1, &(context->A8302_BYTES[0]));
  L0_WriteBytes (context->i2c, 0, 1, &(context->A8302_BYTES[context->LNB2]));

}
unsigned int  L1_A8302_InitAfterReset   (A8302_Context *context) {
  SiTRACE("L1_A8302_InitAfterReset starting LNB%1d...\n", context->LNB2);
  L1_A8302_Status_And_Write(context);
  SiTRACE("L1_A8302_InitAfterRset complete...\n");
  return 1;
}
void          L1_A8302_Supply           (A8302_Context *context, unsigned char supply_off_on) {
  if (supply_off_on == A8302_SUPPLY_OFF) {
    context->lnb_output                 = lnb_output_disabled;
  } else {
    context->lnb_output                 = lnb_output_enabled;
  }
  L1_A8302_Status_And_Write(context);
}
void          L1_A8302_Polarity         (A8302_Context *context, unsigned char horizontal_vertical) {
  if (horizontal_vertical == A8302_HORIZONTAL) {
    context->vsel_voltage               = vsel_voltage_13333_mV;
  } else {
    context->vsel_voltage               = vsel_voltage_18667_mV;
  }
  if (context->lnb_output == lnb_output_enabled ) {
    L1_A8302_Status_And_Write(context);
  }
}
void          L1_A8302_Voltage          (A8302_Context *context, unsigned char voltage) {
  switch (voltage) {
    case 13: context->vsel_voltage = vsel_voltage_13333_mV; context->lnb_output = lnb_output_enabled; break;
    case 18: context->vsel_voltage = vsel_voltage_18667_mV; context->lnb_output = lnb_output_enabled; break;
    default: context->lnb_output = lnb_output_disabled; break;
  }
  L1_A8302_Status_And_Write(context);
}

char *L1_A8302_TAG_Text       (void) { return (char*)"A8302 V0.0.1"; }
