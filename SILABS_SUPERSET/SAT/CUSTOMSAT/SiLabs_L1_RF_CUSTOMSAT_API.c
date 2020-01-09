/*************************************************************************************************************
Copyright 2019, Silicon Laboratories, Inc.

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
#define   SiLEVEL          1
#define   SiTAG            context->i2c->tag

#include "Silabs_L1_RF_CUSTOMSAT_API.h"

void  L1_RF_CUSTOMSAT_Init           (CUSTOMSAT_Context *context, unsigned int add) {
    SiTRACE_X("L1_RF_CUSTOMSAT_Init starting...\n");
    context->i2c = &(context->i2cObj);
    #ifndef   DLL_MODE
    L0_Init(context->i2c);
    #endif /* DLL_MODE */
    L0_SetAddress(context->i2c, add, 1);
    #ifndef   DLL_MODE
    context->i2c->mustReadWithoutStop =1;
    #endif /* DLL_MODE */
    context->tunerBytesCount      =                    39;
    context->IF                   =                     0;
    context->RF                   =                950000;
    context->minRF                =                925000;
    context->maxRF                =               2175000;
    context->I2CMuxChannel        =                     0;
    context->xtal                 =                    16;
    context->LPF                  =              38100000;
    context->i2c->trackWrite      =                     0;
    SiTRACE_X("L1_RF_CUSTOMSAT_Init complete...\n");
}

int   L1_RF_CUSTOMSAT_InitAfterReset (CUSTOMSAT_Context *context) {
  SiTRACE("L1_RF_CUSTOMSAT_InitAfterReset starting...\n");
  /* Add here whatever is needed to init the tuner following a hw reset */
  /* Add here whatever is needed to init the tuner following a hw reset */
  /* Add here whatever is needed to init the tuner following a hw reset */
  /* Add here whatever is needed to init the tuner following a hw reset */
  /* Add here whatever is needed to init the tuner following a hw reset */
  /* Add here whatever is needed to init the tuner following a hw reset */
  /* Add here whatever is needed to init the tuner following a hw reset */
  /* Add here whatever is needed to init the tuner following a hw reset */
  /* Add here whatever is needed to init the tuner following a hw reset */
  /* Add here whatever is needed to init the tuner following a hw reset */
  /* Add here whatever is needed to init the tuner following a hw reset */
  SiTRACE("L1_RF_STV6111_InitAfterReset complete...\n");
  return 0;
}

int   L1_RF_CUSTOMSAT_Get_Infos      (CUSTOMSAT_Context *context, char **infos) {
  strcpy(*infos,"CUSTOMSAT Digital Satellite Tuner");
  context->RF = context->RF; /* To avoid compiler warning while keeping a common prototype for all tuners */
  return 0;
}

int   L1_RF_CUSTOMSAT_Wakeup         (CUSTOMSAT_Context *context) {
  /* Add here whatever is needed to wakeup the tuner following a standby */
  /* Add here whatever is needed to wakeup the tuner following a standby */
  /* Add here whatever is needed to wakeup the tuner following a standby */
  /* Add here whatever is needed to wakeup the tuner following a standby */
  return 0;
}

int   L1_RF_CUSTOMSAT_Standby        (CUSTOMSAT_Context *context) {
  /* Add here whatever is needed to standby the tuner */
  /* Add here whatever is needed to standby the tuner */
  /* Add here whatever is needed to standby the tuner */
  /* Add here whatever is needed to standby the tuner */
  return 0;
}

int   L1_RF_CUSTOMSAT_ClockOn        (CUSTOMSAT_Context *context) {
  /* Add here whatever is needed to turn the tuner's clock ON */
  /* Add here whatever is needed to turn the tuner's clock ON */
  /* Add here whatever is needed to turn the tuner's clock ON */
  /* Add here whatever is needed to turn the tuner's clock ON */
  return 0;
}

int   L1_RF_CUSTOMSAT_ClockOff       (CUSTOMSAT_Context *context) {
  /* Add here whatever is needed to turn the tuner's clock OFF */
  /* Add here whatever is needed to turn the tuner's clock OFF */
  /* Add here whatever is needed to turn the tuner's clock OFF */
  /* Add here whatever is needed to turn the tuner's clock OFF */
  return 0;
}

int   L1_RF_CUSTOMSAT_Get_IF         (CUSTOMSAT_Context *context) {
   return context->IF;}

int   L1_RF_CUSTOMSAT_Get_RF         (CUSTOMSAT_Context *context) {
   return context->RF;}

int   L1_RF_CUSTOMSAT_Get_minRF      (CUSTOMSAT_Context *context) {
   return context->minRF;}

int   L1_RF_CUSTOMSAT_Get_maxRF      (CUSTOMSAT_Context *context) {
   return context->maxRF;}

int   L1_RF_CUSTOMSAT_Tune           (CUSTOMSAT_Context *context, int rf) {
  /* Add here whatever is needed to tune the tuner to rf (in kHz unit for SAT), while setting the current context->RF and returning this value */
  /* Add here whatever is needed to tune the tuner to rf (in kHz unit for SAT), while setting the current context->RF and returning this value */
  /* Add here whatever is needed to tune the tuner to rf (in kHz unit for SAT), while setting the current context->RF and returning this value */
  /* Add here whatever is needed to tune the tuner to rf (in kHz unit for SAT), while setting the current context->RF and returning this value */
  /* Add here whatever is needed to tune the tuner to rf (in kHz unit for SAT), while setting the current context->RF and returning this value */
  /* Add here whatever is needed to tune the tuner to rf (in kHz unit for SAT), while setting the current context->RF and returning this value */
  /* Add here whatever is needed to tune the tuner to rf (in kHz unit for SAT), while setting the current context->RF and returning this value */
  /* Add here whatever is needed to tune the tuner to rf (in kHz unit for SAT), while setting the current context->RF and returning this value */
  /* Add here whatever is needed to tune the tuner to rf (in kHz unit for SAT), while setting the current context->RF and returning this value */
  /* Add here whatever is needed to tune the tuner to rf (in kHz unit for SAT), while setting the current context->RF and returning this value */
  context->RF = rf;
  return context->RF;
}

int   L1_RF_CUSTOMSAT_LPF            (CUSTOMSAT_Context *context, int lpf_khz) {
  /* Add here whatever is needed to set the tuner's filter bw, using the lpf value in kHz and return context->LPF */
  /* Add here whatever is needed to set the tuner's filter bw, using the lpf value in kHz and return context->LPF */
  /* Add here whatever is needed to set the tuner's filter bw, using the lpf value in kHz and return context->LPF */
  /* Add here whatever is needed to set the tuner's filter bw, using the lpf value in kHz and return context->LPF */
  /* Add here whatever is needed to set the tuner's filter bw, using the lpf value in kHz and return context->LPF */
  /* Add here whatever is needed to set the tuner's filter bw, using the lpf value in kHz and return context->LPF */
  context->LPF = lpf_khz;
  return context->LPF;
}

float L1_RF_CUSTOMSAT_RSSI           (CUSTOMSAT_Context *context, float ref_level) {
  /* Add here whatever is needed to read the tuner's received power return context->rssi */
  /* Add here whatever is needed to read the tuner's received power return context->rssi */
  /* Add here whatever is needed to read the tuner's received power return context->rssi */
  /* Add here whatever is needed to read the tuner's received power return context->rssi */
  /* Add here whatever is needed to read the tuner's received power return context->rssi */
  return context->rssi;
}
const char* L1_RF_CUSTOMSAT_TAG_TEXT       (void) {
  /* Set here the version string for the tuner */
  return (const char *)"TUNERNAME driver Vx.y.z";
}
