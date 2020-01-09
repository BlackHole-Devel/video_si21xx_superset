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
#include "Silabs_L1_RF_CUSTOMTER_API.h"
#define Layer1_CUSTOMTER

char  CUSTOMTER_TextBuffer[100];
char *CUSTOMTER_Text;

void   L1_RF_CUSTOMTER_Init           (CUSTOMTER_Context *context, unsigned int add) {
    SiTRACE("L1_RF_CUSTOMTER_Init starting...\n");
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
    context->RF                   =             474000000;
    context->minRF                =             200000000;
    context->maxRF                =             800000000;
    context->xtal                 =                    16;
    context->sawBW                =                     8;
    context->i2c->trackWrite      =                     0;
    CUSTOMTER_Text                = &CUSTOMTER_TextBuffer[0];
    SiTRACE("L1_RF_CUSTOMTER_Init complete...\n");
}

int    L1_RF_CUSTOMTER_InitAfterReset (CUSTOMTER_Context *context) {
  SiTRACE("L1_RF_CUSTOMTER_InitAfterReset starting...\n");
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
  SiTRACE("L1_RF_CUSTOMTER_InitAfterReset complete...\n");
  return 0;
}

int    L1_RF_CUSTOMTER_Get_Infos      (CUSTOMTER_Context *context, char **infos) {
  strcpy(*infos,"CUSTOMTER Digital Terrestrial Tuner");
  context->RF = context->RF; /* To avoid compiler warning while keeping a common prototype for all tuners */
  return 0;
}

int    L1_RF_CUSTOMTER_Wakeup         (CUSTOMTER_Context *context) {
  /* Add here whatever is needed to wakeup the tuner following a standby */
  /* Add here whatever is needed to wakeup the tuner following a standby */
  /* Add here whatever is needed to wakeup the tuner following a standby */
  /* Add here whatever is needed to wakeup the tuner following a standby */
  return 0;
}

int    L1_RF_CUSTOMTER_Standby        (CUSTOMTER_Context *context) {
  /* Add here whatever is needed to standby the tuner */
  /* Add here whatever is needed to standby the tuner */
  /* Add here whatever is needed to standby the tuner */
  /* Add here whatever is needed to standby the tuner */
  return 0;
}

int    L1_RF_CUSTOMTER_ClockOn        (CUSTOMTER_Context *context) {
  /* Add here whatever is needed to turn the tuner's clock ON */
  /* Add here whatever is needed to turn the tuner's clock ON */
  /* Add here whatever is needed to turn the tuner's clock ON */
  /* Add here whatever is needed to turn the tuner's clock ON */
  return 0;
}

int    L1_RF_CUSTOMTER_ClockOff       (CUSTOMTER_Context *context) {
  /* Add here whatever is needed to turn the tuner's clock OFF */
  /* Add here whatever is needed to turn the tuner's clock OFF */
  /* Add here whatever is needed to turn the tuner's clock OFF */
  /* Add here whatever is needed to turn the tuner's clock OFF */
  return 0;
}

int    L1_RF_CUSTOMTER_Get_IF         (CUSTOMTER_Context *context) {
   return context->IF;}

int    L1_RF_CUSTOMTER_Get_RF         (CUSTOMTER_Context *context) {
   return context->RF;}

int    L1_RF_CUSTOMTER_Get_RSSI       (CUSTOMTER_Context *context) {
  /* Add here whatever is needed to return the rssi value */
  /* Add here whatever is needed to return the rssi value */
  /* Add here whatever is needed to return the rssi value */
  /* Add here whatever is needed to return the rssi value */
   return context->rssi;}

int    L1_RF_CUSTOMTER_Get_minRF      (CUSTOMTER_Context *context) {
   return context->minRF;}

int    L1_RF_CUSTOMTER_Get_maxRF      (CUSTOMTER_Context *context) {
   return context->maxRF;}

int    L1_RF_CUSTOMTER_Tune           (CUSTOMTER_Context *context, int rf    ) {
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
  return context->RF;
}

int    L1_RF_CUSTOMTER_Saw            (CUSTOMTER_Context *context, int bw_mhz) {
  /* Add here whatever is needed to set the tuner's SAW BW (unit MHz) */
   switch (bw_mhz) {
      case 8 : context->sawBW = 8; break;
      case 7 : context->sawBW = 7; break;
      default: break;
   }
   return context->sawBW;
}

char*  L1_RF_CUSTOMTER_TAG_TEXT       (void) {
  /* Set here the version string for the tuner */
  return (char *)"CUSTOMTER driver Vx.y.z";
}

char*  L1_RF_CUSTOMTER_Error_TEXT     (int error_code) {
  /* Set here the error text for the input error code */
  sprintf(CUSTOMTER_Text, "CUSTOMTER error code %d", error_code);
  return  CUSTOMTER_Text;
}
