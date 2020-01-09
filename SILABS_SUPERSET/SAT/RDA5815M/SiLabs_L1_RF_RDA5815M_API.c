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
/*                     SILEMBIA Layer 1                  RF Tuner RDA5815M_functions                         */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains all API RDA5815M_functions for the RDA5815M Tuner on the RF board             */
/*     All included RDA5815M_functions can be accessed by the higher software level as imports               */
/*     All RDA5815M_functions are declared in Silabs_L1_RF_RDA5815M_API.h                                    */
/*     WARNING: UNTESTED on HW by SiLabs (no available HW).                                                  */
/*************************************************************************************************************/
/* Change log:

 As from SVN6757: defaulting to 27MHz clock. Removed unused items. Corrected 30MHz temp_value in RDA5815M_Set

 As from SVN6755: Update based on HW validation and latest RDA info

   27 April 2015: Update RSSI calculation in L1_RF_RDA5815M_RSSI() according to RDA FAE.
         SVNxxxx: Modifed based on RDA5815M_1.6.c file and tested it on RDA5815M module from Xuguang.

 As from SVN6512: Modified to remove compilation warnings depending on the compiler.
 As from SVN5297: Modified to match latest RDA5815M sample code. Still UNTESTED on HW by SiLabs (no available HW).

 As from SVN5000:
  Initial version based on RDA5815 driver plus latest code from RDA

 RDA change log for V1.6.2:
 Filename:		RDA5815M_16112_x.c
 Description:	RDA5815M/RDA16112 - Digital Satellite Tuner IC driver.
version 1.0   The primary version,  created by hongxin wang  2012-8-28
version 1.1   Modify the register 0x38 from 0x93 to 0x 9B for increasing the amplitude of XOUT
version 1.2   Add configuration for Xtal = 30MHz. 2013-04-26
version 1.3   Add configuration for Xtal = 24MHz. 2013-06-09
version 1.4   AGC optimized to enhance max gain. 2013-06-27
version 1.4.1 Code simplified to avoid bugs for modes -- Xtal_24M and Xtal_30M. 2013-07-25
version 1.5   Optimize bandwidth calculation. 2013-8-19
version 1.6   Correct some functions' return value. Add APIs -- "RDA5815_LockStatus", "RDA5815_Sleep", "RDA5815_Wakeup", "RDA5815_RunningStatus". 2013-11-20
version 1.6.2	Add APIs to detect tuner's existing and get RSSI. 2014-05-26

 *************************************************************************************************************/
/* TAG TAGNAME     */
/*#define RWTRACES */

#define Layer1_RDA5815M
#define   SiLEVEL          1
#define   SiTAG            context->i2c->tag

#include "SiLabs_L1_RF_RDA5815M_API.h"

#define Xtal_27M
/*#define Xtal_30M*/
/*#define Xtal_24M*/

int           RDA5815M_Communication_Check   (RDA5815M_Context *context) {
	unsigned char byteBuffer[5];
    if (L0_ReadCommandBytes(context->i2c, 5, byteBuffer) != 5) {
      SiTRACE("RDA5815M_Communication_Check ERROR reading 5 bytes 0!\n");
      printf ("RDA5815M_Communication_Check ERROR reading 5 bytes 0!\n");
	  /*system("pause");*/
      return 0;
    }
    if (byteBuffer[0] == 0xff) {
      SiTRACE("RDA5815M_Communication_Check ERROR: first byte 0xff!\n");
      return 0;
    }
    if (byteBuffer[0] == 0x00) {
      SiTRACE("RDA5815M_Communication_Check ERROR: first byte 0x00!\n");
      return 0;
    }
	return 1;
}
void          RDA5815M_IIC_Write             (RDA5815M_Context *context, unsigned char write_index, unsigned char  value) {
  context->bytes[0] = value;
  L0_WriteBytes (context->i2c, write_index, 1, context->bytes);
}
void          RDA5815M_IIC_Read              (RDA5815M_Context *context, unsigned char read_index , unsigned char *value) {
  L0_ReadBytes (context->i2c, read_index, 1, value);
}
void          RDA5815M_Initialize            (RDA5815M_Context *context) {
	system_wait(1);/* Wait 1ms.*/

	 /* Chip register soft reset */
	RDA5815M_IIC_Write(context, 0x04,0x04);
	RDA5815M_IIC_Write(context, 0x04,0x05);

	/* Initial configuration start */

	/*pll setting  */
	RDA5815M_IIC_Write(context, 0x1a,0x13);
	RDA5815M_IIC_Write(context, 0x41,0x53);
	RDA5815M_IIC_Write(context, 0x38,0x9B);
	RDA5815M_IIC_Write(context, 0x39,0x15);
	RDA5815M_IIC_Write(context, 0x3A,0x00);
	RDA5815M_IIC_Write(context, 0x3B,0x00);
	RDA5815M_IIC_Write(context, 0x3C,0x0c);
	RDA5815M_IIC_Write(context, 0x0c,0xE2);
	RDA5815M_IIC_Write(context, 0x2e,0x6F);

#ifdef Xtal_27M
	RDA5815M_IIC_Write(context, 0x72,0x07);	/* v1.1, 1538~1539 */
	RDA5815M_IIC_Write(context, 0x73,0x10);
	RDA5815M_IIC_Write(context, 0x74,0x71);
	RDA5815M_IIC_Write(context, 0x75,0x06); /* v1.1, 1363~1364, 1862~1863 */
	RDA5815M_IIC_Write(context, 0x76,0x40);
	RDA5815M_IIC_Write(context, 0x77,0x89);
	RDA5815M_IIC_Write(context, 0x79,0x04);	/* v1.1, 900 */
	RDA5815M_IIC_Write(context, 0x7A,0x2A);
	RDA5815M_IIC_Write(context, 0x7B,0xAA);
	RDA5815M_IIC_Write(context, 0x7C,0xAB);
#endif
#ifdef Xtal_30M
	RDA5815M_IIC_Write(context, 0x72,0x06);	/* v1.2, 1544~1545 */
	RDA5815M_IIC_Write(context, 0x73,0x60);
	RDA5815M_IIC_Write(context, 0x74,0x66);
	RDA5815M_IIC_Write(context, 0x75,0x05); /* v1.2, 1364~1365, 1859~1860 */
	RDA5815M_IIC_Write(context, 0x76,0xA0);
	RDA5815M_IIC_Write(context, 0x77,0x7B);
	RDA5815M_IIC_Write(context, 0x79,0x03);	/* v1.2, 901 */
	RDA5815M_IIC_Write(context, 0x7A,0xC0);
	RDA5815M_IIC_Write(context, 0x7B,0x00);
	RDA5815M_IIC_Write(context, 0x7C,0x00);
#endif
#ifdef Xtal_24M
	RDA5815M_IIC_Write(context, 0x72,0x08);	/* v1.3, 1547~1548 */
	RDA5815M_IIC_Write(context, 0x73,0x00);
	RDA5815M_IIC_Write(context, 0x74,0x80);
	RDA5815M_IIC_Write(context, 0x75,0x07); /* v1.3, 1367~1368, 1859~1860 */
	RDA5815M_IIC_Write(context, 0x76,0x10);
	RDA5815M_IIC_Write(context, 0x77,0x9A);
	RDA5815M_IIC_Write(context, 0x79,0x04);	/* v1.3, 901 */
	RDA5815M_IIC_Write(context, 0x7A,0xB0);
	RDA5815M_IIC_Write(context, 0x7B,0x00);
	RDA5815M_IIC_Write(context, 0x7C,0x00);
#endif

	RDA5815M_IIC_Write(context, 0x2f,0x57);
	RDA5815M_IIC_Write(context, 0x0d,0x70);
	RDA5815M_IIC_Write(context, 0x18,0x4B);
	RDA5815M_IIC_Write(context, 0x30,0xFF);
	RDA5815M_IIC_Write(context, 0x5c,0xFF);
	RDA5815M_IIC_Write(context, 0x65,0x00);
	RDA5815M_IIC_Write(context, 0x70,0x3F);
	RDA5815M_IIC_Write(context, 0x71,0x3F);
	RDA5815M_IIC_Write(context, 0x53,0xA8);
	RDA5815M_IIC_Write(context, 0x46,0x21);
	RDA5815M_IIC_Write(context, 0x47,0x84);
	RDA5815M_IIC_Write(context, 0x48,0x10);
	RDA5815M_IIC_Write(context, 0x49,0x08);
	RDA5815M_IIC_Write(context, 0x60,0x80);
	RDA5815M_IIC_Write(context, 0x61,0x80);
	RDA5815M_IIC_Write(context, 0x6A,0x08);
	RDA5815M_IIC_Write(context, 0x6B,0x63);
	RDA5815M_IIC_Write(context, 0x69,0xF8);
	RDA5815M_IIC_Write(context, 0x57,0x64);
	RDA5815M_IIC_Write(context, 0x05,0xaa);
	RDA5815M_IIC_Write(context, 0x06,0xaa);
	RDA5815M_IIC_Write(context, 0x15,0xAE);
	RDA5815M_IIC_Write(context, 0x4a,0x67);
	RDA5815M_IIC_Write(context, 0x4b,0x77);

	/*agc setting */

	RDA5815M_IIC_Write(context, 0x4f,0x40);
	RDA5815M_IIC_Write(context, 0x5b,0x20);

	RDA5815M_IIC_Write(context, 0x16,0x0C);
	RDA5815M_IIC_Write(context, 0x18,0x0C);
	RDA5815M_IIC_Write(context, 0x30,0x1C);
	RDA5815M_IIC_Write(context, 0x5c,0x2C);
	RDA5815M_IIC_Write(context, 0x6c,0x3C);
	RDA5815M_IIC_Write(context, 0x6e,0x3C);
	RDA5815M_IIC_Write(context, 0x1b,0x7C);
	RDA5815M_IIC_Write(context, 0x1d,0xBD);
	RDA5815M_IIC_Write(context, 0x1f,0xBD);
	RDA5815M_IIC_Write(context, 0x21,0xBE);
	RDA5815M_IIC_Write(context, 0x23,0xBE);
	RDA5815M_IIC_Write(context, 0x25,0xFE);
	RDA5815M_IIC_Write(context, 0x27,0xFF);
	RDA5815M_IIC_Write(context, 0x29,0xFF);
	RDA5815M_IIC_Write(context, 0xb3,0xFF);
	RDA5815M_IIC_Write(context, 0xb5,0xFF);

	RDA5815M_IIC_Write(context, 0x17,0xF0);
	RDA5815M_IIC_Write(context, 0x19,0xF0);
	RDA5815M_IIC_Write(context, 0x31,0xF0);
	RDA5815M_IIC_Write(context, 0x5d,0xF0);
	RDA5815M_IIC_Write(context, 0x6d,0xF0);
	RDA5815M_IIC_Write(context, 0x6f,0xF1);
	RDA5815M_IIC_Write(context, 0x1c,0xF5);
	RDA5815M_IIC_Write(context, 0x1e,0x35);
	RDA5815M_IIC_Write(context, 0x20,0x79);
	RDA5815M_IIC_Write(context, 0x22,0x9D);
	RDA5815M_IIC_Write(context, 0x24,0xBE);
	RDA5815M_IIC_Write(context, 0x26,0xBE);
	RDA5815M_IIC_Write(context, 0x28,0xBE);
	RDA5815M_IIC_Write(context, 0x2a,0xCF);
	RDA5815M_IIC_Write(context, 0xb4,0xDF);
	RDA5815M_IIC_Write(context, 0xb6,0x0F);

	RDA5815M_IIC_Write(context, 0xb7,0x15);	/*start */
	RDA5815M_IIC_Write(context, 0xb9,0x6c);
	RDA5815M_IIC_Write(context, 0xbb,0x63);
	RDA5815M_IIC_Write(context, 0xbd,0x5a);
	RDA5815M_IIC_Write(context, 0xbf,0x5a);
	RDA5815M_IIC_Write(context, 0xc1,0x55);
	RDA5815M_IIC_Write(context, 0xc3,0x55);
	RDA5815M_IIC_Write(context, 0xc5,0x47);
	RDA5815M_IIC_Write(context, 0xa3,0x53);
	RDA5815M_IIC_Write(context, 0xa5,0x4f);
	RDA5815M_IIC_Write(context, 0xa7,0x4e);
	RDA5815M_IIC_Write(context, 0xa9,0x4e);
	RDA5815M_IIC_Write(context, 0xab,0x54);
	RDA5815M_IIC_Write(context, 0xad,0x31);
	RDA5815M_IIC_Write(context, 0xaf,0x43);
	RDA5815M_IIC_Write(context, 0xb1,0x9f);

	RDA5815M_IIC_Write(context, 0xb8,0x6c); /*end */
	RDA5815M_IIC_Write(context, 0xba,0x92);
	RDA5815M_IIC_Write(context, 0xbc,0x8a);
	RDA5815M_IIC_Write(context, 0xbe,0x8a);
	RDA5815M_IIC_Write(context, 0xc0,0x82);
	RDA5815M_IIC_Write(context, 0xc2,0x93);
	RDA5815M_IIC_Write(context, 0xc4,0x85);
	RDA5815M_IIC_Write(context, 0xc6,0x77);
	RDA5815M_IIC_Write(context, 0xa4,0x82);
	RDA5815M_IIC_Write(context, 0xa6,0x7e);
	RDA5815M_IIC_Write(context, 0xa8,0x7d);
	RDA5815M_IIC_Write(context, 0xaa,0x6f);
	RDA5815M_IIC_Write(context, 0xac,0x65);
	RDA5815M_IIC_Write(context, 0xae,0x43);
	RDA5815M_IIC_Write(context, 0xb0,0x9f);
	RDA5815M_IIC_Write(context, 0xb2,0xf0);

	RDA5815M_IIC_Write(context, 0x81,0x92); /*rise */
	RDA5815M_IIC_Write(context, 0x82,0xb4);
	RDA5815M_IIC_Write(context, 0x83,0xb3);
	RDA5815M_IIC_Write(context, 0x84,0xac);
	RDA5815M_IIC_Write(context, 0x85,0xba);
	RDA5815M_IIC_Write(context, 0x86,0xbc);
	RDA5815M_IIC_Write(context, 0x87,0xaf);
	RDA5815M_IIC_Write(context, 0x88,0xa2);
	RDA5815M_IIC_Write(context, 0x89,0xac);
	RDA5815M_IIC_Write(context, 0x8a,0xa9);
	RDA5815M_IIC_Write(context, 0x8b,0x9b);
	RDA5815M_IIC_Write(context, 0x8c,0x7d);
	RDA5815M_IIC_Write(context, 0x8d,0x74);
	RDA5815M_IIC_Write(context, 0x8e,0x9f);
	RDA5815M_IIC_Write(context, 0x8f,0xf0);

	RDA5815M_IIC_Write(context, 0x90,0x15); /*fall */
	RDA5815M_IIC_Write(context, 0x91,0x39);
	RDA5815M_IIC_Write(context, 0x92,0x30);
	RDA5815M_IIC_Write(context, 0x93,0x27);
	RDA5815M_IIC_Write(context, 0x94,0x29);
	RDA5815M_IIC_Write(context, 0x95,0x0d);
	RDA5815M_IIC_Write(context, 0x96,0x10);
	RDA5815M_IIC_Write(context, 0x97,0x1e);
	RDA5815M_IIC_Write(context, 0x98,0x1a);
	RDA5815M_IIC_Write(context, 0x99,0x19);
	RDA5815M_IIC_Write(context, 0x9a,0x19);
	RDA5815M_IIC_Write(context, 0x9b,0x32);
	RDA5815M_IIC_Write(context, 0x9c,0x1f);
	RDA5815M_IIC_Write(context, 0x9d,0x31);
	RDA5815M_IIC_Write(context, 0x9e,0x43);

	system_wait(10); /*Wait 10ms;*/

/* Initial configuration end*/

}
/*************************************************************************
	Function to Set the RDA5815M
	fPLL_MHz:   Frequency         unit: MHz  from 250 to 2300
	LPF_KHz:    SymbolRate       	unit: KS/s from 1000 to 45000
*************************************************************************/
long          RDA5815M_Set                   (RDA5815M_Context *context, long fPLL_MHz, long LPF_KHz) {
  unsigned char buffer;
  unsigned long temp_value = 0;
  unsigned char Filter_bw_control_bit;
  unsigned long bw;

  SiTRACE("fPLL_MHz %ld, LPF_KHz %ld\n", fPLL_MHz, LPF_KHz);

  /*  RDA5815M_Communication_Check(context);*/

  /*  RDA5815M_Initialize(context);*/
  RDA5815M_IIC_Write(context, 0x04,0xc1); /*add by rda 2011.8.9,RXON = 0 , change normal working state to idle state */
  RDA5815M_IIC_Write(context, 0x2b,0x95); /*clk_interface_27m=0  add by rda 2012.1.12      */

  if (fPLL_MHz !=0) {
  /*set frequency start */
#ifdef Xtal_27M		/* v1.1 */
	temp_value = (unsigned long)fPLL_MHz* 77672;
#endif
#ifdef Xtal_30M		/* v1.2 */
	temp_value = (unsigned long)fPLL_MHz* 69905;
#endif
#ifdef Xtal_24M		/* v1.3 */
	temp_value = (unsigned long)fPLL_MHz* 87381;
#endif
  buffer = ((unsigned char)((temp_value>>24)&0xff));
  RDA5815M_IIC_Write(context, 0x07,buffer);
  buffer = ((unsigned char)((temp_value>>16)&0xff));
  RDA5815M_IIC_Write(context, 0x08,buffer);
  buffer = ((unsigned char)((temp_value>>8)&0xff));
  RDA5815M_IIC_Write(context, 0x09,buffer);
  buffer = ((unsigned char)( temp_value&0xff));
  RDA5815M_IIC_Write(context, 0x0a,buffer);
  /*set frequency end*/
  }

  if (LPF_KHz != 0) {
	/* set Filter bandwidth start */
	bw = LPF_KHz;
	Filter_bw_control_bit = (unsigned char)((bw*135/200+4000)/1000);

	if(Filter_bw_control_bit<4)
		Filter_bw_control_bit = 4;    /* MHz */
	else if(Filter_bw_control_bit>40)
		Filter_bw_control_bit = 40;   /* MHz */

	Filter_bw_control_bit&=0x3f;
	Filter_bw_control_bit|=0x40;		/*v1.5 */
	RDA5815M_IIC_Write(context, 0x0b,Filter_bw_control_bit);
  /* set Filter bandwidth end */
  }

	RDA5815M_IIC_Write(context, 0x04,0xc3); /*add by rda 2011.8.9,RXON = 0 ,rxon=1,normal working */
  RDA5815M_IIC_Write(context, 0x2b,0x97); /*clk_interface_27m=1  add by rda 2012.1.12   */

	system_wait(5);/*Wait 5ms; */

  return 1;
}
void          L1_RF_RDA5815M_Init            (RDA5815M_Context *context, unsigned int add) {
    SiTRACE_X("RDA5815M_Init starting...\n");
    context->i2c = &(context->i2cObj);
    L0_Init(context->i2c);
    L0_SetAddress(context->i2c, add, 1);
    context->i2c->mustReadWithoutStop =1;
    context->IF                   =                     0;
    context->RF                   =                950000;
    context->minRF                =                900000;
    context->maxRF                =               2200000;
    context->LPF_kHz              =                 38100;
    context->loopthrough          =                     0;
    SiTRACE_X("L1_RF_RDA5815M_Init complete...\n");
}
int           L1_RF_RDA5815M_InitAfterReset  (RDA5815M_Context *context) {
  SiTRACE("L1_RF_RDA5815M_InitAfterReset starting...\n");
  RDA5815M_Initialize(context);
  SiTRACE("L1_RF_RDA5815M_InitAfterReset complete...\n");
  return 0;
}
int           L1_RF_RDA5815M_Get_RF          (RDA5815M_Context *context) {
   return context->RF;
}
int           L1_RF_RDA5815M_Tune            (RDA5815M_Context *context, int rf          ) {
   /* Checking limits */
   if (rf < (context->minRF)) {SiTRACE("rf %d < minRF %d\n",rf,context->minRF); return L1_RF_RDA5815M_Tune(context, context->minRF);}
   if (rf > (context->maxRF)) {SiTRACE("rf %d > maxRF %d\n",rf,context->maxRF); return L1_RF_RDA5815M_Tune(context, context->maxRF);}
   context->i2c->trackRead = context->i2c->trackWrite;

   context->RF = rf;
   RDA5815M_Set(context, context->RF/1000, context->LPF_kHz);

   return context->RF;
}
int           L1_RF_RDA5815M_LPF             (RDA5815M_Context *context, int LPF_kHz     ) {
  if (LPF_kHz != 0) { /* use '0' to retrieve the current value */
    if ((LPF_kHz > 45000)) {
      SiTRACE("RDA5815M requested LPF_kHz %d higher than max, set to max\n", LPF_kHz);
      LPF_kHz = 45000;
    }
    if ((LPF_kHz < 4000)) {
      SiTRACE("RDA5815M requested LPF_kHz %d smaller than min, set to min\n", LPF_kHz);
      LPF_kHz = 4000;
    }
    context->LPF_kHz = (int)((LPF_kHz + 500));
  }

  SiTRACE("RDA5815M LPF_kHz %d kHz\n", context->LPF_kHz);

  RDA5815M_Set(context, 0, context->LPF_kHz);
  return context->LPF_kHz;
}

/********************************************************************************
	Function to Get RSSI
	fPLL:	Frequency		unit: MHz from 250 to 2300
	rssi:	RSSI			range: 0 ~ 255.
********************************************************************************/
int           L1_RF_RDA5815M_RSSI            (RDA5815M_Context *context, int other_gain  ) {
  /* Gain stage limits
                                              filter..
                                               i2v--..
                                           post.. --..
                                          st2--.. --..
                                       pre.. --.. --..
                                     st1--.. --.. --..    */
#define RDA5815_Gain_Stage__0 0xc00 /* '1100 0000 0000' */
#define RDA5815_Gain_Stage__1 0xc00 /* '1100 0000 0000' */
#define RDA5815_Gain_Stage__2 0xc01 /* '1100 0000 0001' */
#define RDA5815_Gain_Stage__3 0xc02 /* '1100 0000 0010' */
#define RDA5815_Gain_Stage__4 0xc03 /* '1100 0000 0011' */
#define RDA5815_Gain_Stage__5 0xc13 /* '1100 0001 0011' */
#define RDA5815_Gain_Stage__6 0xd17 /* '1101 0001 0111' */
#define RDA5815_Gain_Stage__7 0xd5b /* '1101 0101 1011' */
#define RDA5815_Gain_Stage__8 0xe5b /* '1110 0101 1011' */
#define RDA5815_Gain_Stage__9 0xf9b /* '1111 1001 1011' */


#define RDA5815_Gain_Stage_10 0xfab /* '1111 1010 1011' */
#define RDA5815_Gain_Stage_11 0xfaf /* '1111 1010 1111' */
#define RDA5815_Gain_Stage_12 0xfeb /* '1111 1110 1111' */
#define RDA5815_Gain_Stage_13 0xfff /* '1111 1111 1111' */
#define RDA5815_Gain_Stage_14 0xfff /* '1111 1111 1111' */
#define RDA5815_Gain_Stage_15 0xfff /* '1111 1111 1111' */

  unsigned char data16,data17,st1,pre,st2,post,i2v,filter,vga;
  unsigned int  stage_code;
  unsigned char gain_stage;
  unsigned char band;
  int           vga_gain, total_gain;
  /* gain band/gain_stage:    0     1     2     3     4     5     6     7     8     9    10    11    12    13   14&15 */
  static int gain[5][15] = {
  /* 1  950= Freq <1150 */ {-969,	-969,	587,	2117,	3621,	5049,	7472,	9588,	11195,	13158,	14612,	16142,	17187,	18666,	18666 },
  /* 2 1150= Freq <1350 */ {-587,	-587,	944,	2474,	3978,	5406,	7778,	9869,	11297,	13056,	14535,	16065,	17085,	18641,	18641 },
  /* 3 1350= Freq <1550 */ {-128,	-128,	1428,	2984,	4488,	5916,	8186,	10277,	11552,	13184,	14688,	16218,	17187,	18768,	18768 },
  /* 4 1550= Freq <1900 */ { 357,	 357,	1887,	3417,	4947,	6401,	8619,	10685,	11858,	13413,	14969,	16499,	17417,	19049,	19049 },
  /* 5 1900= Freq <2150 */ {-102,	-102,	1454,	2984,	4488,	5993,	8135,	10226,	11271,	12750,	14357,	15887,	16728,	18437,	18437 },
  };

  RDA5815M_IIC_Read(context, 0x16, &data16);
  i2v    = (data16&0xc0)>>6;
  filter = (data16&0x30)>>4;
  st1    = (data16&0x0c)>>2;
  st2    = (data16&0x03)>>0;

  RDA5815M_IIC_Read(context, 0x17, &data17);
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

       if (context->RF >= 1900000) { band = 5; }
  else if (context->RF >= 1550000) { band = 4; }
  else if (context->RF >= 1350000) { band = 3; }
  else if (context->RF >= 1150000) { band = 2; }
  else                             { band = 1; }

  RDA5815M_IIC_Read(context, 0xb7, &vga);
  vga_gain = vga*30;

  total_gain = (gain[band-1][gain_stage] + vga_gain)/255;

  if (0) {
    SiTRACE("RDA5815M stage_code %02x%02x %02x%02x %02x%02x -> stage_code 0x%06x\n", st1, pre, st2, post, i2v, filter, stage_code);
    SiTRACE("RDA5815M st1 %d, pre %d, st2 %d, post %d, i2v %d, filter %d -> stage_code 0x%06x -> gain_stage %d\n", st1, pre, st2, post, i2v, filter, stage_code, gain_stage);
    SiTRACE("RDA5815M vga %d -> vga_gain %d\n", vga, vga_gain);
    SiTRACE("RDA5815M RSSI = gain[%d][%d] + vga_gain = %d + %d = %d\n", band-1, gain_stage, gain[band-1][gain_stage], vga_gain, total_gain);
  }

  return  other_gain-total_gain;
}
/*************************************************************************
	Function to wake up the RDA5815M from sleep status
*************************************************************************/
unsigned char L1_RF_RDA5815M_Wakeup          (RDA5815M_Context *context) {
	return 0;
}
/*************************************************************************
	Function to Set the RDA5815M to sleep status (low power consumption)
*************************************************************************/
unsigned char L1_RF_RDA5815M_Standby         (RDA5815M_Context *context) {
	return 0;
}
char*         L1_RF_RDA5815M_TAG_TEXT        (void) { return (char *)"TAGNAME"; }
