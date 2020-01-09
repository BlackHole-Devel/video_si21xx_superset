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
/*                     SILEMBIA Layer 1                  RF Tuner RDA5812                                    */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains all API Functions for the RDA5812 Tuner on the RF board                       */
/*     All included functions can be accessed by the higher software level as imports                        */
/*     All functions are declared in Silabs_L1_RF_RDA5812_API.h                                              */
/*************************************************************************************************************/
/* Change log:

 As from SVN6512: Modified to remove compilation warnings depending on the compiler.

 As from SVN5295:
  L1_RF_RDA5812_Saw returning BW value.

 As from SVN2929:
  Casting returned strings as (char *)

  As from SVN2195
  In L1_RF_RDA5812_Init: initial LPF value 38 (previously 38100000), as the unit is in MHz

 As from SVN1908:
  Corrections in LPF computing (register value is in MHz, from 4 to 40).

 As from SVN1794:
  RDA5812 lpf function using kHz values.

 *************************************************************************************************************/
/* TAG TAGNAME */
/*#define RWTRACES*/
#define Layer1_RDA5812

#define   SiLEVEL          1
#define   SiTAG            context->i2c->tag

#include "Silabs_L1_RF_RDA5812_API.h"

/*# soft reset */
unsigned char RDA5812_SOFT_RESET_1[3] = {  1, 0x04,0x04};
unsigned char RDA5812_SOFT_RESET_2[3] = {  1, 0x04,0x05};

/*# dc cal register settings */
unsigned char RDA5812_DC_CAL_1[4]     = {  2, 0x30,0x60,0x04};
unsigned char RDA5812_DC_CAL_2[3]     = {  1, 0x38,0x03};
unsigned char RDA5812_DC_CAL_3[5]     = {  3, 0x3A,0x06,0x6B,0x04};
unsigned char RDA5812_DC_CAL_4[3]     = {  1, 0x44,0x55};
unsigned char RDA5812_DC_CAL_5[3]     = {  1, 0x7C,0xC4};

/*# pll register setting*/
unsigned char RDA5812_PLL_01[3] = { 1, 0x39,0xBA};
unsigned char RDA5812_PLL_02[3] = { 1, 0x3E,0x83};
unsigned char RDA5812_PLL_03[3] = { 1, 0x41,0xA2};
unsigned char RDA5812_PLL_04[3] = { 1, 0x4F,0x07};
unsigned char RDA5812_PLL_05[3] = { 1, 0x53,0xAC};
unsigned char RDA5812_PLL_06[5] = { 3, 0x67,0x1C,0x81,0x47};
unsigned char RDA5812_PLL_07[5] = { 3, 0x6B,0x18,0xC6,0x4B};
unsigned char RDA5812_PLL_08[3] = { 1, 0x71,0x8E};
unsigned char RDA5812_AGC_1[ 3] = { 1, 0x04,0x81};
unsigned char RDA5812_AGC_2[ 3] = { 1, 0x05,0x20};
unsigned char RDA5812_AGC_3[ 9] = { 7, 0x15,0x18,0x29,0x3D,0x2E,0x3E,0x3F,0x3F};
unsigned char RDA5812_AGC_4[ 3] = { 1, 0x06,0x00};
unsigned char RDA5812_AGC_5[17] = {15, 0x1C,0x4B,0x18,0x51,0x13,0x4D,0x13,0x4D,0x11,0x4B,0x11,0x33,0x13,0x2F,0x2F,0xAB};
unsigned char RDA5812_AGC_7[16] = {14, 0x81,0x68,0x7E,0x7A,0x5C,0x5C,0x44,0xAB,0x00,0x00,0x00,0x00,0x00,0x0B,0x13};
unsigned char RDA5812_AGC_8[ 4] = { 2, 0x91,0x00,0xBF};

void RDA5812_WriteRegisterTrace  (RDA5812_Context *context, char* name, char* valName, unsigned int add, unsigned char offset, unsigned char nbbit, unsigned char Value);
void RDA5812_WriteRegister       (RDA5812_Context *context,                            unsigned int add, unsigned char offset, unsigned char nbbit, unsigned char Value);

void L1_RF_RDA5812_Init          (RDA5812_Context *context, unsigned int add) {
    SiTRACE_X((char*)"L1_RF_RDA5812_Init starting...\n");
    context->i2c = &(context->i2cObj);
    L0_Init(context->i2c);
    L0_SetAddress(context->i2c, add, 1);
    context->i2c->mustReadWithoutStop =1;
    context->tunerBytesCount      =                    39;
    context->IF                   =                     0;
    context->RF                   =                950000;
    context->minRF                =                925000;
    context->maxRF                =               2175000;
    context->I2CMuxChannel        =                     0;
    context->xtal                 =                    27;
    context->LPF                  =                    38;
    context->i2c->trackWrite      =                     0;
    SiTRACE_X((char*)"L1_RF_RDA5812_Init complete...\n");
}

int  L1_RF_RDA5812_InitAfterReset(RDA5812_Context *context) {
  unsigned char* initline;
  int i;
  SiTRACE((char*)"L1_RF_RDA5812_InitAfterReset starting...\n");
  i=0;
  initline = RDA5812_SOFT_RESET_1;  for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_SOFT_RESET_2;  for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_DC_CAL_1;      for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_DC_CAL_2;      for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_DC_CAL_3;      for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_DC_CAL_4;      for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_DC_CAL_5;      for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_PLL_01;        for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_PLL_02;        for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_PLL_03;        for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_PLL_04;        for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_PLL_05;        for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_PLL_06;        for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_PLL_07;        for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_PLL_08;        for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_AGC_1;         for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_AGC_2;         for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_AGC_3;         for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_AGC_4;         for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_AGC_5;         for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_AGC_7;         for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  initline = RDA5812_AGC_8;         for (i=0; i< initline[0]; i++) {    context->tuner_log[i] = initline[i+2];   }; L0_WriteBytes(context->i2c, initline[1], initline[0], context->tuner_log);
  RDA5812_WRITE(enable,  1);
  L1_RF_RDA5812_Tune(context, context->RF);
  SiTRACE((char*)"L1_RF_RDA5812_InitAfterReset complete...\n");
  return 0;
}

int  L1_RF_RDA5812_Get_Infos     (RDA5812_Context *context, char **infos) {
    strcpy(*infos,"RDA5812 RDA Digital Satellite Silicon Tuner (table 03)");
    context->RF = context->RF; /* To avoid compiler warning while keeping a common prototype for all tuners */
    return 0;
}

int  L1_RF_RDA5812_Get_I2cChannel(RDA5812_Context *context) {
    return context->I2CMuxChannel;

}

int  L1_RF_RDA5812_Get_IF        (RDA5812_Context *context) {
   return context->IF;}

int  L1_RF_RDA5812_Get_RF        (RDA5812_Context *context) {
   return context->RF;}

int  L1_RF_RDA5812_Get_minRF     (RDA5812_Context *context) {
   return context->minRF;}

int  L1_RF_RDA5812_Get_maxRF     (RDA5812_Context *context) {
   return context->maxRF;}

int  L1_RF_RDA5812_Tune          (RDA5812_Context *context, int rf) {
   int DIV,i;
   /* Checking limits */
   if (rf < (context->minRF)) {SiTRACE((char*)"rf %d < minRF %d\n",rf,context->minRF); return L1_RF_RDA5812_Tune(context, context->minRF);}
   if (rf > (context->maxRF)) {SiTRACE((char*)"rf %d > maxRF %d\n",rf,context->maxRF); return L1_RF_RDA5812_Tune(context, context->maxRF);}
   context->i2c->trackRead = context->i2c->trackWrite;

    RDA5812_WRITE(rxon              , 0);
    RDA5812_WRITE(rf_bypass_enable_b, 0);

  /* DIV and K # DIV = expr {int($freq_mhz*pow(2,21)/27)} */
    DIV = (int)( (rf*2097.152)/context->xtal);

    for (i=0; i< 4; i++) { context->tuner_log[i] = (DIV>>(8*(3-i)))&0xff;};

    RDA5812_WRITE(filter_bw_control_bit, context->LPF);
    L0_WriteBytes(context->i2c, div_ADDRESS, 4, context->tuner_log);

    RDA5812_WRITE(rxon              , 1);
    RDA5812_WRITE(rf_bypass_enable_b, 1);

    system_wait(70);

    context->RF = (int)(1.0*(context->xtal*(DIV/2097.152)+0.5));

    SiTRACE((char*)"RDA5812 tuned at %4.3f MHz (lpf %d MHz)\n", context->RF/1000.0, context->LPF );

   return context->RF;
}

int  L1_RF_RDA5812_Saw           (RDA5812_Context *context, int bw) {
   context->RF = context->RF; /* To avoid compiler warning while keeping a common prototype for all tuners */
   bw = 0; /* To avoid compiler warning while keeping a common prototype for all tuners */
   return bw;
}

int  L1_RF_RDA5812_Get_Saw       (RDA5812_Context *context) {
   context->RF = context->RF; /* To avoid compiler warning while keeping a common prototype for all tuners */
   return 0;
}
int  L1_RF_RDA5812_LPF           (RDA5812_Context *context, int lpf_khz) {
    if (lpf_khz !=0) {
      RDA5812_WRITE(rxon,    0);
      RDA5812_WRITE(rf_bypass_enable_b,0);

      if ((lpf_khz > 45000)) {
        SiTRACE((char*)"RDA5812 requested lpf_khz %d higher than max, set to max\n", lpf_khz);
        lpf_khz = 45000;
      }
      if ((lpf_khz < 4000)) {
        SiTRACE((char*)"RDA5812 requested lpf_khz %d smaller than min, set to min\n", lpf_khz);
        lpf_khz = 4000;
      }

      context->LPF = (int)((lpf_khz + 500.0)/1000.0);

      RDA5812_WRITE(filter_bw_control_bit, context->LPF);

      RDA5812_WRITE(rxon,              1);
      RDA5812_WRITE(rf_bypass_enable_b,1);

      SiTRACE((char*)"RDA5812 lpf %d MHz\n", context->LPF);
    }

    return context->LPF;
}
char* L1_RF_RDA5812_TAG_TEXT     (void) { return (char *)"TAGNAME"; }
