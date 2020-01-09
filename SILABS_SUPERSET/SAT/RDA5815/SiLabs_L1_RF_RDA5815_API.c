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
/*                     SILEMBIA Layer 1                  RF Tuner RDA5815_functions                                  */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains all API RDA5815_functions for the RDA5815 Tuner on the RF board                       */
/*     All included RDA5815_functions can be accessed by the higher software level as imports                        */
/*     All RDA5815_functions are declared in Silabs_L1_RF_RDA5815_API.h                                              */
/*************************************************************************************************************/
/* Change log:

 As from SVN5296: In RDA5815_Initialize: settings changed to match latest RDA sample code.

 As from SVN4045:
  In RDA5815_Set: allowing using 0 values to avoid either tuning or setting the LPF
  In  L1_RF_RDA5815_Wakeup: New Wakeup sequence, as per RDA on 2013/04/19 (ruicao@rdamicro.com)

 As from TAG 3217:
   In L1_RF_RDA5815_LPF:
    max LPF value is 40 MHz

 As from TAG 2927:
   In RDA5815_Set: wait 80 ms to make sure the AGCs have converged

 As from TAG 2591:
   Adding 'loopthrough' flag in context to manage configuration with/without loopthrough
   RSSI function coded and validated (based on RDA's input)

  As from TAG 2536:
   Storing RF in kHz unit (previously MHz), to use a 1kHz tuning step
   Adding initial  L1_RF_RDA5815_RSSI function (implementation details still under discussion with RDA)

  As from TAG 2277:
   LPF management checked to work with RDA5815s

  As from TAG 1908:
   Corrections in LPF computing (register value is in MHz, from 4 to 40).
   RDA5815 lpf function using kHz values.

 *************************************************************************************************************/
/* TAG TAGNAME     */
/*#define RWTRACES */

#define Layer1_RDA5815
#define   SiLEVEL          1
#define   SiTAG            context->i2c->tag

#include "Silabs_L1_RF_RDA5815_API.h"

int           RDA5815_Communication_Check   (RDA5815_Context *context) {
	unsigned char byteBuffer[5];
    if (L0_ReadCommandBytes(context->i2c, 5, byteBuffer) != 5) {
      SiTRACE("RDA5815_Communication_Check ERROR reading 5 bytes 0!\n");
      printf ("RDA5815_Communication_Check ERROR reading 5 bytes 0!\n");
	  /*system("pause");*/
      return 0;
    }
    if (byteBuffer[0] == 0xff) {
      SiTRACE("RDA5815_Communication_Check ERROR: first byte 0xff!\n");
      return 0;
    }
    if (byteBuffer[0] == 0x00) {
      SiTRACE("RDA5815_Communication_Check ERROR: first byte 0x00!\n");
      return 0;
    }
	return 1;
}
void          RDA5815_IIC_Write             (RDA5815_Context *context, unsigned char write_index, unsigned char  value) {
  context->bytes[0] = value;
  L0_WriteBytes (context->i2c, write_index, 1, context->bytes);
}
void          RDA5815_IIC_Read              (RDA5815_Context *context, unsigned char read_index , unsigned char *value) {
  L0_ReadBytes (context->i2c, read_index, 1, value);
}
void          RDA5815_Initialize            (RDA5815_Context *context) {
	system_wait(1);/* Wait 1ms.*/
	/* Chip register soft reset */
	RDA5815_IIC_Write(context, 0x04,0x04);
	RDA5815_IIC_Write(context, 0x04,0x05);

	/* Initial configuration start */

	/* pll setting */
	RDA5815_IIC_Write(context, 0x1a,0x13);    /* add by rda 2011.5.28     */
	RDA5815_IIC_Write(context, 0x41,0x53);    /* add by rda 2011.12.27    */
	RDA5815_IIC_Write(context, 0x38,0x93);	  /* modify by rda 2012.04.17 */
	RDA5815_IIC_Write(context, 0x39,0x15);
	RDA5815_IIC_Write(context, 0x3A,0x00);
	RDA5815_IIC_Write(context, 0x3B,0x00);
	RDA5815_IIC_Write(context, 0x3C,0x0C);    /* add by rda 2011.8.9 */
	RDA5815_IIC_Write(context, 0x0c,0xE2);
	RDA5815_IIC_Write(context, 0x2e,0x6F);

	RDA5815_IIC_Write(context, 0x72,0x07);		/* 1552~1553 */
	RDA5815_IIC_Write(context, 0x73,0x20);
	RDA5815_IIC_Write(context, 0x74,0x72);
	RDA5815_IIC_Write(context, 0x75,0x06);		/* 1363~1364, 1862~1863 */
	RDA5815_IIC_Write(context, 0x76,0x40);
	RDA5815_IIC_Write(context, 0x77,0x89);
	RDA5815_IIC_Write(context, 0x79,0x04);		/* 1075 */
	RDA5815_IIC_Write(context, 0x7A,0xFA);
	RDA5815_IIC_Write(context, 0x7B,0x12);
	RDA5815_IIC_Write(context, 0x7C,0xF7);

	RDA5815_IIC_Write(context, 0x5b,0x20);
	RDA5815_IIC_Write(context, 0x2f,0x57);
	RDA5815_IIC_Write(context, 0x0d,0x70);
	RDA5815_IIC_Write(context, 0x16,0x03);
	RDA5815_IIC_Write(context, 0x18,0x4B);
	RDA5815_IIC_Write(context, 0x30,0xFF);
	RDA5815_IIC_Write(context, 0x5c,0xFF);
	RDA5815_IIC_Write(context, 0x6c,0xFF);
	RDA5815_IIC_Write(context, 0x6e,0xFF);
	RDA5815_IIC_Write(context, 0x65,0x00);		/* modify by rda 2011.12.27 */
	RDA5815_IIC_Write(context, 0x70,0x3F);
	RDA5815_IIC_Write(context, 0x71,0x3F);
	RDA5815_IIC_Write(context, 0x53,0xA8);
	RDA5815_IIC_Write(context, 0x46,0x21);
	RDA5815_IIC_Write(context, 0x47,0x84);
	RDA5815_IIC_Write(context, 0x48,0x10);
	RDA5815_IIC_Write(context, 0x49,0x08);
	RDA5815_IIC_Write(context, 0x60,0x80);
	RDA5815_IIC_Write(context, 0x61,0x80);
	RDA5815_IIC_Write(context, 0x6A,0x08);
	RDA5815_IIC_Write(context, 0x6B,0x63);
	RDA5815_IIC_Write(context, 0x69,0xF8);
	RDA5815_IIC_Write(context, 0x57,0x64);		/* modify by rda 2011.12.27 */
	RDA5815_IIC_Write(context, 0x05,0x88);
	RDA5815_IIC_Write(context, 0x06,0xF8);		/* modify by rda 2012.8.10  */
	RDA5815_IIC_Write(context, 0x15,0xAE);		/* modify by rda 2011.10.28 */
	RDA5815_IIC_Write(context, 0x4a,0x68);		/* modify by rda 2012.7.18  */
	RDA5815_IIC_Write(context, 0x4b,0x78);		/* modify by rda 2012.7.18  */


	/*agc setting */
	RDA5815_IIC_Write(context, 0x4f,0x40);
	RDA5815_IIC_Write(context, 0x5b,0x20);

	/*for blocker*/
	RDA5815_IIC_Write(context, 0x16,0x10);    /* stage setting */
	RDA5815_IIC_Write(context, 0x18,0x20);
	RDA5815_IIC_Write(context, 0x30,0x30);
	RDA5815_IIC_Write(context, 0x5c,0x30);
	RDA5815_IIC_Write(context, 0x6c,0x30);
	RDA5815_IIC_Write(context, 0x6e,0x70);
	RDA5815_IIC_Write(context, 0x1b,0xB2);
	RDA5815_IIC_Write(context, 0x1d,0xB2);
	RDA5815_IIC_Write(context, 0x1f,0xB2);
	RDA5815_IIC_Write(context, 0x21,0xB2);
	RDA5815_IIC_Write(context, 0x23,0xB6);
	RDA5815_IIC_Write(context, 0x25,0xB6);
	RDA5815_IIC_Write(context, 0x27,0xBA);
	RDA5815_IIC_Write(context, 0x29,0xBF);
	RDA5815_IIC_Write(context, 0xb3,0xFF);
	RDA5815_IIC_Write(context, 0xb5,0xFF);

	RDA5815_IIC_Write(context, 0x17,0xF0);
	RDA5815_IIC_Write(context, 0x19,0xF0);
	RDA5815_IIC_Write(context, 0x31,0xF0);
	RDA5815_IIC_Write(context, 0x5d,0xF1);
	RDA5815_IIC_Write(context, 0x6d,0xF2);
	RDA5815_IIC_Write(context, 0x6f,0xF2);
	RDA5815_IIC_Write(context, 0x1c,0x31);
	RDA5815_IIC_Write(context, 0x1e,0x72);
	RDA5815_IIC_Write(context, 0x20,0x96);
	RDA5815_IIC_Write(context, 0x22,0xBA);
	RDA5815_IIC_Write(context, 0x24,0xBA);
	RDA5815_IIC_Write(context, 0x26,0xBE);
	RDA5815_IIC_Write(context, 0x28,0xCE);
	RDA5815_IIC_Write(context, 0x2a,0xDE);
	RDA5815_IIC_Write(context, 0xb4,0x0F);
	RDA5815_IIC_Write(context, 0xb6,0x0F);

	RDA5815_IIC_Write(context, 0xb7,0x10);	  /* start */
	RDA5815_IIC_Write(context, 0xb9,0x10);
	RDA5815_IIC_Write(context, 0xbb,0x00);
	RDA5815_IIC_Write(context, 0xbd,0x00);
	RDA5815_IIC_Write(context, 0xbf,0x00);
	RDA5815_IIC_Write(context, 0xc1,0x10);
	RDA5815_IIC_Write(context, 0xc3,0x10);
	RDA5815_IIC_Write(context, 0xc5,0x10);
	RDA5815_IIC_Write(context, 0xa3,0x19);
	RDA5815_IIC_Write(context, 0xa5,0x2E);
	RDA5815_IIC_Write(context, 0xa7,0x37);
	RDA5815_IIC_Write(context, 0xa9,0x47);
	RDA5815_IIC_Write(context, 0xab,0x47);
	RDA5815_IIC_Write(context, 0xad,0x3F);
	RDA5815_IIC_Write(context, 0xaf,0x00);
	RDA5815_IIC_Write(context, 0xb1,0x95);		/* modify by rda 2012.1.12    */

	RDA5815_IIC_Write(context, 0xb8,0x47);    /* end */
	RDA5815_IIC_Write(context, 0xba,0x3F);
	RDA5815_IIC_Write(context, 0xbc,0x37);
	RDA5815_IIC_Write(context, 0xbe,0x3F);
	RDA5815_IIC_Write(context, 0xc0,0x3F);
	RDA5815_IIC_Write(context, 0xc2,0x3F);
	RDA5815_IIC_Write(context, 0xc4,0x3F);
	RDA5815_IIC_Write(context, 0xc6,0x3F);
	RDA5815_IIC_Write(context, 0xa4,0x47);
	RDA5815_IIC_Write(context, 0xa6,0x57);
	RDA5815_IIC_Write(context, 0xa8,0x5F);
	RDA5815_IIC_Write(context, 0xaa,0x70);
	RDA5815_IIC_Write(context, 0xac,0x70);
	RDA5815_IIC_Write(context, 0xae,0x68);
	RDA5815_IIC_Write(context, 0xb0,0x95);		/* modify by rda 2012.1.12    */
	RDA5815_IIC_Write(context, 0xb2,0x95);		/* modify by rda 2012.1.12    */

	RDA5815_IIC_Write(context, 0x81,0x77);    /* rise */
	RDA5815_IIC_Write(context, 0x82,0x68);
	RDA5815_IIC_Write(context, 0x83,0x70);
	RDA5815_IIC_Write(context, 0x84,0x68);
	RDA5815_IIC_Write(context, 0x85,0x68);
	RDA5815_IIC_Write(context, 0x86,0x68);
	RDA5815_IIC_Write(context, 0x87,0x70);
	RDA5815_IIC_Write(context, 0x88,0x47);
	RDA5815_IIC_Write(context, 0x89,0x68);
	RDA5815_IIC_Write(context, 0x8a,0x8E);
	RDA5815_IIC_Write(context, 0x8b,0x8E);
	RDA5815_IIC_Write(context, 0x8c,0x8E);
	RDA5815_IIC_Write(context, 0x8d,0x9C);
	RDA5815_IIC_Write(context, 0x8e,0xe0);		/* modify by rda 2012.1.12      */
	RDA5815_IIC_Write(context, 0x8f,0x95);		/* modify by rda 2012.1.12      */

	RDA5815_IIC_Write(context, 0x90,0x00);    /* fall                         */
	RDA5815_IIC_Write(context, 0x91,0x00);
	RDA5815_IIC_Write(context, 0x92,0x00);
	RDA5815_IIC_Write(context, 0x93,0x00);
	RDA5815_IIC_Write(context, 0x94,0x00);
	RDA5815_IIC_Write(context, 0x95,0x00);
	RDA5815_IIC_Write(context, 0x96,0x00);
	RDA5815_IIC_Write(context, 0x97,0x00);
	RDA5815_IIC_Write(context, 0x98,0x00);
	RDA5815_IIC_Write(context, 0x99,0x00);
	RDA5815_IIC_Write(context, 0x9a,0x10);
	RDA5815_IIC_Write(context, 0x9b,0x24);
	RDA5815_IIC_Write(context, 0x9c,0x10);
	RDA5815_IIC_Write(context, 0x9d,0x00);
	RDA5815_IIC_Write(context, 0x9e,0x00);

	system_wait(10); /*Wait 10ms;*/

/* Initial configuration end*/

}
/*************************************************************************
	Function to Set the RDA5815
	fPLL:   Frequency        			unit: MHz  from 250 to 2300
	fSym:   SymbolRate       			unit: KS/s from 1000 to 45000
*************************************************************************/
long          RDA5815_Set                   (RDA5815_Context *context, long fPLL, long lpf_Mhz) {
  unsigned char buffer;
  unsigned long temp_value = 0;
  unsigned char Filter_bw_control_bit;

  SiTRACE("fPLL %ld, lpf_Mhz %ld\n", fPLL, lpf_Mhz);

  /*  RDA5815_Communication_Check(context);*/

  /*  RDA5815_Initialize(context);*/
  if (context->loopthrough == 0) { /* RDA 2_7 version (no   loopthrough) */
    RDA5815_IIC_Write(context, 0x04,0xe1); /*RXON = 0 , change normal working state to idle state*/
  } else {                         /* RDA 3_4 version (with loopthrough) */
    RDA5815_IIC_Write(context, 0x04,0xc1); /*add by rda 2011.8.9,RXON = 0 , change normal working state to idle state */
  }
  if (fPLL !=0) {
  /*set frequency start */
  temp_value = (unsigned long)(fPLL* 77.672);/*((2<<21) / RDA5815_XTALFREQ);*/
  buffer = ((unsigned char)((temp_value>>24)&0xff));
  RDA5815_IIC_Write(context, 0x07,buffer);
  context->RF = (int)(((1.0*temp_value)/77.672)+0.5);
  /*  printf("RDA5815_Set fPLL %ld -> RF %d\n", fPLL, context->RF );*/
  buffer = ((unsigned char)((temp_value>>16)&0xff));
  RDA5815_IIC_Write(context, 0x08,buffer);
  buffer = ((unsigned char)((temp_value>>8)&0xff));
  RDA5815_IIC_Write(context, 0x09,buffer);
  buffer = ((unsigned char)( temp_value&0xff));
  RDA5815_IIC_Write(context, 0x0a,buffer);
  /*set frequency end*/
  /*  printf("fPLL %ld, temp_value 0x%08x\n", fPLL, temp_value);*/
  }
  if (lpf_Mhz != 0) {
  Filter_bw_control_bit = (unsigned char)(lpf_Mhz);
  Filter_bw_control_bit&=0x3f;
  RDA5815_IIC_Write(context, 0x0b,Filter_bw_control_bit);
  /* set Filter bandwidth end */
  }

  if (context->loopthrough == 0) { /* RDA 2_7 version (no   loopthrough) */
    RDA5815_IIC_Write(context, 0x04,0xe3); /*rxon=1,normal working */
  } else {                         /* RDA 3_4 version (with loopthrough) */
    RDA5815_IIC_Write(context, 0x04,0xc3); /*add by rda 2011.8.9,RXON = 0 ,rxon=1,normal working */
  }

	system_wait(80);/*Wait 80ms;*/

  return 1;
}
void          L1_RF_RDA5815_Init            (RDA5815_Context *context, unsigned int add) {
    SiTRACE_X("RDA5815_Init starting...\n");
    context->i2c = &(context->i2cObj);
    L0_Init(context->i2c);
    L0_SetAddress(context->i2c, add, 1);
    context->i2c->mustReadWithoutStop =1;
    context->IF                   =                     0;
    context->RF                   =                950000;
    context->minRF                =                925000;
    context->maxRF                =               2175000;
    context->LPF                  =              38100000;
    context->loopthrough          =                     0;
    SiTRACE_X("L1_RF_RDA5815_Init complete...\n");
}
int           L1_RF_RDA5815_InitAfterReset  (RDA5815_Context *context) {
  SiTRACE("L1_RF_RDA5815_InitAfterReset starting...\n");
  RDA5815_Initialize(context);
  SiTRACE("L1_RF_RDA5815_InitAfterReset complete...\n");
  return 0;
}
int           L1_RF_RDA5815_Get_RF          (RDA5815_Context *context) {
   return context->RF;
}
int           L1_RF_RDA5815_Tune            (RDA5815_Context *context, int rf          ) {
   /* Checking limits */
   if (rf < (context->minRF)) {SiTRACE("rf %d < minRF %d\n",rf,context->minRF); return L1_RF_RDA5815_Tune(context, context->minRF);}
   if (rf > (context->maxRF)) {SiTRACE("rf %d > maxRF %d\n",rf,context->maxRF); return L1_RF_RDA5815_Tune(context, context->maxRF);}
   context->i2c->trackRead = context->i2c->trackWrite;

   context->RF = rf;
   RDA5815_Set(context, context->RF, context->LPF/1000.0);
   return context->RF;
}
int           L1_RF_RDA5815_LPF             (RDA5815_Context *context, int lpf_khz     ) {
  if (lpf_khz != 0) { /* use '0' to retrieve the current value */
    if ((lpf_khz > 40000)) {
      SiTRACE("RDA5815 requested lpf_khz %d higher than max, set to max\n", lpf_khz);
      lpf_khz = 45000;
    }
    if ((lpf_khz < 4000)) {
      SiTRACE("RDA5815 requested lpf_khz %d smaller than min, set to min\n", lpf_khz);
      lpf_khz = 4000;
    }
    context->LPF = (int)((lpf_khz + 500.0));
  } else {
    /* Trick to trigger the state machine, for debug purpose */
    RDA5815_Set(context, 0, 0);
    return 0;
  }

  SiTRACE("RDA5815 lpf %d kHz\n", context->LPF);

  RDA5815_Set(context, 0, context->LPF/1000.0);
  return context->LPF;
}
int           L1_RF_RDA5815_RSSI            (RDA5815_Context *context, int other_gain  ) {
/* Gain stage limits
                                             filter-..
                                               i2v--..
                                           post.. --..
                                          st2--.. --..
                                       pre.. --.. --..
                                     st1--.. --.. --..    */
#define RDA5815_Gain_Stage__0 0x001 /* '0000 0000 0001' */
#define RDA5815_Gain_Stage__1 0x002 /* '0000 0000 0010' */
#define RDA5815_Gain_Stage__2 0x003 /* '0000 0000 0011' */
#define RDA5815_Gain_Stage__3 0x013 /* '0000 0001 0011' */
#define RDA5815_Gain_Stage__4 0x023 /* '0000 0010 0011' */
#define RDA5815_Gain_Stage__5 0x027 /* '0000 0010 0111' */
#define RDA5815_Gain_Stage__6 0x09b /* '0000 1001 1011' */
#define RDA5815_Gain_Stage__7 0x0ab /* '0000 1010 1011' */
#define RDA5815_Gain_Stage__8 0x1ab /* '0001 1010 1011' */
#define RDA5815_Gain_Stage__9 0x2ab /* '0010 1010 1011' */
#define RDA5815_Gain_Stage_10 0x6ab /* '0110 1010 1011' */
#define RDA5815_Gain_Stage_11 0x7ab /* '0111 1010 1011' */
#define RDA5815_Gain_Stage_12 0xbab /* '1011 1010 1011' */
#define RDA5815_Gain_Stage_13 0xfeb /* '1111 1110 1011' */
#define RDA5815_Gain_Stage_14 0xfff /* '1111 1111 1111' */
#define RDA5815_Gain_Stage_15 0xfff /* '1111 1111 1111' */

  unsigned char data16,data17,st1,pre,st2,post,i2v,filter,vga;
  unsigned int  stage_code;
  unsigned char gain_stage;
  unsigned char band;
  double        vga_gain, total_gain;
  /* gain band/gain_stage:    0     1     2     3     4     5     6     7     8     9    10    11    12    13   14&15 */
  double gain[6][15] = {
  /* 1  950= Freq <1090 */ { -9.6, -3.4,  2.6,  8.2, 13.8, 18.6, 24.0, 29.6, 32.7, 36.3, 41.5, 46.3, 51.6, 59.9, 72.0 },
  /* 2 1090= Freq <1280 */ { -7.7, -1.5,  4.5, 10.1, 15.8, 20.5, 25.7, 31.4, 34.3, 37.6, 42.5, 46.9, 51.9, 59.8, 71.7 },
  /* 3 1280= Freq <1450 */ { -5.7,  0.4,  6.4, 12.0, 17.8, 22.5, 27.4, 33.2, 36.0, 39.0, 43.5, 47.4, 52.1, 59.7, 71.9 },
  /* 4 1450= Freq <1660 */ { -3.8,  2.3,  8.3, 13.9, 19.8, 24.5, 29.1, 35.0, 37.6, 40.4, 44.6, 48.1, 52.6, 59.9, 72.2 },
  /* 5 1660= Freq <1990 */ { -2.5,  3.6,  9.6, 15.3, 21.4, 26.1, 30.1, 36.1, 38.5, 41.0, 44.9, 48.2, 52.4, 59.0, 70.9 },
  /* 6 1990= Freq <2150 */ { -2.3,  3.8,  9.8, 15.6, 21.8, 26.5, 30.0, 36.1, 38.3, 40.6, 44.4, 47.6, 51.6, 57.3, 69.2 },
  };

  RDA5815_IIC_Read(context, 0x16, &data16);
  i2v    = (data16&0xc0)>>6;
  filter = (data16&0x30)>>4;
  st1    = (data16&0x0c)>>2;
  st2    = (data16&0x03)>>0;

  RDA5815_IIC_Read(context, 0x17, &data17);
  pre    = (data17&0x0c)>>2;
  post   = (data17&0x03)>>0;

  stage_code = (st1<<10) + (pre<<8) + (st2<<6) + (post<<4) + (i2v<<2) + (filter<<0);

       if (stage_code >= RDA5815_Gain_Stage_14 ) { gain_stage = 14; }
  else if (stage_code >= RDA5815_Gain_Stage_13 ) { gain_stage = 13; }
  else if (stage_code >= RDA5815_Gain_Stage_12 ) { gain_stage = 12; }
  else if (stage_code >= RDA5815_Gain_Stage_11 ) { gain_stage = 11; }
  else if (stage_code >= RDA5815_Gain_Stage_10 ) { gain_stage = 10; }
  else if (stage_code >= RDA5815_Gain_Stage__9 ) { gain_stage =  9; }
  else if (stage_code >= RDA5815_Gain_Stage__8 ) { gain_stage =  8; }
  else if (stage_code >= RDA5815_Gain_Stage__7 ) { gain_stage =  7; }
  else if (stage_code >= RDA5815_Gain_Stage__6 ) { gain_stage =  6; }
  else if (stage_code >= RDA5815_Gain_Stage__5 ) { gain_stage =  5; }
  else if (stage_code >= RDA5815_Gain_Stage__4 ) { gain_stage =  4; }
  else if (stage_code >= RDA5815_Gain_Stage__3 ) { gain_stage =  3; }
  else if (stage_code >= RDA5815_Gain_Stage__2 ) { gain_stage =  2; }
  else if (stage_code >= RDA5815_Gain_Stage__1 ) { gain_stage =  1; }
  else                                           { gain_stage =  0; }

       if (context->RF >= 1990000) { band = 6; }
  else if (context->RF >= 1660000) { band = 5; }
  else if (context->RF >= 1450000) { band = 4; }
  else if (context->RF >= 1280000) { band = 3; }
  else if (context->RF >= 1090000) { band = 2; }
  else                             { band = 1; }

  RDA5815_IIC_Read(context, 0xb7, &vga);
  vga_gain = vga*30.0/255;

  total_gain = gain[band-1][gain_stage] + vga_gain;

  if (0) {
    SiTRACE("RDA5815 stage_code %02x%02x %02x%02x %02x%02x -> stage_code 0x%06x\n", st1, pre, st2, post, i2v, filter, stage_code);
    SiTRACE("RDA5815 st1 %d, pre %d, st2 %d, post %d, i2v %d, filter %d -> stage_code 0x%06x -> gain_stage %d\n", st1, pre, st2, post, i2v, filter, stage_code, gain_stage);
    SiTRACE("RDA5815 vga %d -> vga_gain %f\n", vga, vga_gain);
    SiTRACE("RDA5815 RSSI = gain[%d][%d] + vga_gain = %f + %f = %f\n", band-1, gain_stage, gain[band-1][gain_stage], vga_gain, total_gain);
  }

  return  other_gain-total_gain;
}
unsigned char L1_RF_RDA5815_Wakeup          (RDA5815_Context *context) {
  /* New Wakeup sequence, as per RDA on 2013/04/19 (ruicao@rdamicro.com) */
  RDA5815_IIC_Write(context, 0x04, 0xC3);
  RDA5815_IIC_Write(context, 0x16, 0x10);
  RDA5815_IIC_Write(context, 0x17, 0xf0);

  RDA5815_IIC_Write(context, 0x0f, 0x04);
  RDA5815_IIC_Write(context, 0x2c, 0x42);
  RDA5815_IIC_Write(context, 0x2d, 0x08);
  RDA5815_IIC_Write(context, 0x2e, 0x6F);
    return 0;
}
unsigned char L1_RF_RDA5815_Standby         (RDA5815_Context *context) {
	unsigned char temp;

  /* New Standby sequence, as per RDA on 2013/04/19 (ruicao@rdamicro.com) */
  RDA5815_IIC_Read(context, 0x16, &temp); /* read 0x16 register */
  RDA5815_IIC_Write(context, 0x16, temp); /* write the relue that just be read back to the 0x16 register */
  RDA5815_IIC_Read(context, 0x17, &temp); /* read 0x17 register */
  RDA5815_IIC_Write(context, 0x17, temp); /* write the relue that just be read back to the 0x17 register */
  RDA5815_IIC_Write(context, 0x04, 0xC7);
  RDA5815_IIC_Write(context, 0x0f, 0x44);
  RDA5815_IIC_Write(context, 0x2c, 0xff);
  RDA5815_IIC_Write(context, 0x2d, 0xff);
  RDA5815_IIC_Write(context, 0x2e, 0x70);

    return 0;
}
char*         L1_RF_RDA5815_TAG_TEXT        (void) { return (char *)"TAGNAME"; }
