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
/*   This source code contains all API Functions for the MAX2112 Tuner on the RF board                       */
/*     All included functions can be accessed by the higher software level as imports                        */
/*     All functions are declared in Emb_L1_RF_MAX2112_API.h                                                 */
/*************************************************************************************************************/
/*
 Change Log:

 As from SVN6512: Modified to remove compilation warnings depending on the compiler.

  As from SVN5402: In L1_RF_MAX2112_LPF: commenting lines with unused f_3dB
*/

#define Layer1_MAX2112

#define   SiLEVEL          1
#define   SiTAG            context->i2c->tag

#include "Silabs_L1_RF_MAX2112_API.h"
#include "math.h"

/*   Assign default values for each register */
unsigned char N_High       = 0x80;
unsigned char N_Low        = 0x23;
unsigned char Frac2        = 0x12;
unsigned char Frac1        = 0xF6;
unsigned char Frac0        = 0x84;
unsigned char Xtal         = 0x01; /*Rdiv = 1*/
unsigned char PLL_Conf     = 0xA8;
unsigned char VCO_Cont     = 0xCC; /*VAS_EN = on,*/
unsigned char BB_LPF       = 0x4B;
unsigned char Standby      = 0x00;
unsigned char Shutdown     = 0x00;
unsigned char Test         = 0x00;
unsigned char Status       = 0x00; /*Read Only Register*/
unsigned char AutoTune     = 0x00; /*Read Only Register*/
unsigned char TrimConfig   = 0x00;
unsigned char BiasTrim     = 0x27;
unsigned char BB_FiltTrim  = 0xd;
unsigned char RF_ContTrim1 = 0x5D;
unsigned char RF_ContTrim2 = 0x05;

/*
MAX2112Write will write to register 'reg_index' the value 'value'
Customer's I2C write function would go in place of this wrapper
function.  This function takes a register index to indicate which register
to read from and a value to put into the register.
See the Max2112 data sheet for the I2C write sequence.
*/
void  Max2112Write                 (MAX2112_Context *context, unsigned char reg_index, unsigned char value) {
    context->tuner_log[reg_index] = value;
}

void  Max2112ProgramTuner          (MAX2112_Context *context) {
    L0_WriteBytes(context->i2c, 0x00, 9, context->tuner_log); /* The last 2 bytes are read_onlys */
}

void  Max2112SetFrequency          (MAX2112_Context *context, double Frequency) {
   double dNpFN;   /*N+Fractional N number.*/
   double dFN,dN;
   long   FRAC_N;
   int    Rdiv;
   long   NDiv;

   Rdiv   = Xtal & 0x1f;  /*Rdiv is Reg 5 Bits D0-D4*/
   /*Set the DIV24 bit, 1 = LO divided by 4, 0 = LO divided by 2.*/
   if ( Frequency <= 1125 ) {PLL_Conf |= 0x80;   /*DIV24 = 1*/
   } else                   {PLL_Conf &= 0x7f;   /*DIV24 = 0*/}

   /*Find the multiplier (N + fracional-N)
   //Example: If Frequency = 925 then dNpFN would = 34.259259259.....*/
   dNpFN  = (Frequency * Rdiv) / (context->xtal);

   /*strip out the Fractional N portion, and N portion, convert the fractional portion to
   //the fractional N value (multiply by 2 to the 20 power).
   // Example dNpFN = 35.259259259 would result in: dN = 35, dFN = 271853.037037037...
   //NDiv would = 34, FRAC_N would = 271853*/
   dFN    = modf(dNpFN,&dN) * (pow(2,20));
   FRAC_N = (long) dFN;   /*drop the decimal portion, leaving the fractional-N divider.*/
   NDiv   = (long)dN;

   /*Split the N and Fractional-N numbers into their prospective register locations.
   //For N_High, preserve the upper bit since it is the FRAC bit.*/
   N_High = (unsigned char)(N_High & 0x80) + ((NDiv & 0x7f00) >> 8); /*Retain the upper bit which is the FRAC Bit.*/
   N_Low  = (unsigned char) NDiv & 0xff;
   Frac2  = (unsigned char)(0x10 + ((FRAC_N & 0xF0000) >> 16));      /*Retain the upper 4 bits, which are the CP bits.*/
   Frac1  = (unsigned char)((FRAC_N & 0xFF00) >> 8);
   Frac0  = (unsigned char)(FRAC_N & 0xFF);

   /*Write the values out to the Max2112 registers:*/
   Max2112Write(context, MAX2112_N_HIGH,   N_High);
   Max2112Write(context, MAX2112_N_LOW,    N_Low);
   Max2112Write(context, MAX2112_CP_FRAC2, Frac2);
   Max2112Write(context, MAX2112_FRAC1,    Frac1);
   Max2112Write(context, MAX2112_FRAC0,    Frac0);
   Max2112Write(context, MAX2112_PLL,      PLL_Conf);
   Max2112ProgramTuner(context);
}

void  MAX2112_WriteRegisterTrace   (MAX2112_Context *context, char* name, char* valname, unsigned int add, unsigned char offset, unsigned char nbbit, unsigned char Value) {
    printf("MAX2112_WriteRegisterTrace %-25s %s %4d (0x%02x)...\n", name, valname, Value, Value);
    MAX2112_WriteRegister(context, add, offset, nbbit, Value);
}

void  MAX2112_WriteRegister        (MAX2112_Context *context,                             unsigned int add, unsigned char offset, unsigned char nbbit, unsigned char Value) {
    unsigned char buffer[1];
    unsigned char prefixByte, postfixByte, currentValue;
    currentValue =   context->tuner_log[add] & 0xff;
    prefixByte   =   currentValue >> (nbbit + offset);
    prefixByte   =   prefixByte   << (nbbit + offset);
    postfixByte  =  (currentValue << (    8 - offset))&0xff;
    postfixByte  =  (postfixByte  >> (    8 - offset))&0xff;
    context->tuner_log[add] = prefixByte + ((Value << offset)&0xff) + postfixByte;
    buffer[0] = context->tuner_log[add];
    L0_WriteBytes(context->i2c, add, 1, buffer);
}

void L1_RF_MAX2112_Init          (MAX2112_Context *context, unsigned int add) {
    SiTRACE_X("L1_RF_MAX2112_Init starting...\n");
    context->i2c = &(context->i2cObj);
    L0_Init(context->i2c);
    L0_SetAddress(context->i2c, add, 1);
    context->i2c->mustReadWithoutStop = 0;
    context->tunerBytesCount      =                    14;
    context->IF                   =                     0;
    context->minRF                =                925000;
    context->maxRF                =               2175000;
    context->xtal                 =                    27;
    context->LPF                  =                  0x88;
    context->rssi = 0;
    SiTRACE_X("L1_RF_MAX2112_Init complete...\n");
}

int  L1_RF_MAX2112_InitAfterReset(MAX2112_Context *context) {
    SiTRACE("L1_RF_MAX2112_InitAfterReset\n");
    context->i2c->trackRead = context->i2c->trackWrite;
    context->tuner_log[MAX2112_N_HIGH     ] =  N_High;
    context->tuner_log[MAX2112_N_LOW      ] =  N_Low;
    context->tuner_log[MAX2112_CP_FRAC2   ] =  Frac2;
    context->tuner_log[MAX2112_FRAC1      ] =  Frac1;
    context->tuner_log[MAX2112_FRAC0      ] =  Frac0;
    context->tuner_log[MAX2112_XTAL       ] =  Xtal;
    context->tuner_log[MAX2112_PLL        ] =  PLL_Conf;
    context->tuner_log[MAX2112_VCOCONT    ] =  VCO_Cont;
    context->tuner_log[MAX2112_BASEBAND   ] =  context->LPF;
    context->tuner_log[MAX2112_STANDBY    ] =  Standby;
    context->tuner_log[MAX2112_SHUTDWN    ] =  Shutdown;
    context->tuner_log[MAX2112_TEST       ] =  Test;
    context->tuner_log[MAX2112_TRIMCONF   ] =  TrimConfig;
    context->tuner_log[MAX2112_BIASTRIM   ] =  BiasTrim;
    context->tuner_log[MAX2112_BBFILTTRIM ] =  BB_FiltTrim;
    Max2112ProgramTuner(context);
    SiTRACE("L1_RF_MAX2112_InitAfterReset done...\n");
    return 1;
}

int  L1_RF_MAX2112_Get_Infos     (MAX2112_Context *context, char **infos) {
    context = context; /* To avoid compiler warning */
    strcpy(*infos,"MAX2112 Maxim Digital Satellite Silicon Tuner for DVB_S2 Applications");
    return 0;
}

int  L1_RF_MAX2112_Get_I2cChannel(MAX2112_Context *context) {
    context = context; /* To avoid compiler warning */
    return 0;
}

int  L1_RF_MAX2112_Get_IF        (MAX2112_Context *context) {
   return context->IF;}

int  L1_RF_MAX2112_Get_RF        (MAX2112_Context *context) {
   return context->RF;}

int  L1_RF_MAX2112_Get_minRF     (MAX2112_Context *context) {
   return context->minRF;}

int  L1_RF_MAX2112_Get_maxRF     (MAX2112_Context *context) {
   return context->maxRF;}

int  L1_RF_MAX2112_Tune          (MAX2112_Context *context, int rf) {
   /* Checking limits */
   if (rf < (context->minRF)) {SiTRACE("rf %d < minRF %d\n",rf,context->minRF); return L1_RF_MAX2112_Tune(context, context->minRF);}
   if (rf > (context->maxRF)) {SiTRACE("rf %d > maxRF %d\n",rf,context->maxRF); return L1_RF_MAX2112_Tune(context, context->maxRF);}
   context->i2c->trackRead = context->i2c->trackWrite;

   Max2112SetFrequency(context, rf/1000.0);

   context->RF = rf;
   return context->RF;}

int  L1_RF_MAX2112_Saw           (MAX2112_Context *context, int bw) {
    context = context; /* To avoid compiler warning */
    bw      = bw;      /* To avoid compiler warning */
   return 0;
}

int  L1_RF_MAX2112_Get_Saw       (MAX2112_Context *context) {
    context = context; /* To avoid compiler warning */
   return 0;
}

int  L1_RF_MAX2112_LPF           (MAX2112_Context *context, int lpf) {
  /*  double f_3dB; */
    if (lpf !=0) {
      if ((lpf > 40000000)) {
        context->LPF   = (int)((40000000.0 - 4000000.0)/290000.0 + 12);
      /*  f_3dB = 4000000.0 + (context->LPF -12)*290000.0; */
        Max2112Write(context, MAX2112_BASEBAND   , context->LPF);
        Max2112ProgramTuner(context);
      } else if ((lpf < 4000000)) {
      /*  f_3dB = 4000000.0 + (context->LPF -12)*290000.0; */
      } else {
        context->LPF   = (int)((lpf - 4000000.0)/290000.0 + 12);
        Max2112Write(context, MAX2112_BASEBAND   , context->LPF);
        Max2112ProgramTuner(context);
      /*  f_3dB = 4000000.0 + (context->LPF -12)*290000.0; */

      }
    }
    return context->LPF;
}

char* L1_RF_MAX2112_TAG_TEXT     (void) { return (char *)"TAGNAME"; }
