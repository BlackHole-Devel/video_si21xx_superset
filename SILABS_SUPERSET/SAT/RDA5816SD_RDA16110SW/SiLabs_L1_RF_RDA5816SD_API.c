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
/*                     SILEMBIA Layer 1  SAT RF Tuner RDA5816SD / RDA16110SW functions                       */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains all API functions for the RDA5816SD / RDA16110SW SAT Tuners on the RF board   */
/*     All included functions can be accessed by the higher software level as imports                        */
/*     All RDA5816SD are declared in Silabs_L1_RF_RDA5816SD_API.h                                            */
/*************************************************************************************************************/
/* Change log:

 As from SVN6512: Modified to remove compilation warnings depending on the compiler.

 As from svn 6489:
   Adding L1_RF_RDA5816SD_RSSI_from_AGC. This is called from SiLabs_SAT_Tuner_RSSI_From_AGC (as from SAT tuner wrapper V0.2.7)

 As from svn 5511:
   Initial version: UNTESTED driver
    L1_RF_RDA5816SD_RSSI    not working! (inherited from RDA5816S driver, not reworked by RDA yet)
    L1_RF_RDA5816SD_Wakeup  not tested (inherited from RDA5816S driver, not checked)
    L1_RF_RDA5816SD_Standby not tested (inherited from RDA5816S driver, not checked)

*************************************************************************************************************/
/* RDA change log:
	Filename:		RDA5816sd__*.c
	Description:	RDA5816sd_ Digital Satellite Tuner IC driver.
	version 0.1.beta		The primary version for functional running,  created by Yilei LIU  2013-6-27
	version 0.2.beta		AGC linearity improved.  2013-7-11
	version 0.3.beta		Optimize bandwidth calculation. 2013-8-19
	version 1.0				New AGC configuration for chip verB. 2013-9-26
	version 1.1				Combine AGC configurations for both verA and verB. 2013-10-22
	version 1.2				update AGC configuration of verB for better linearity. 2013-11-04
	version 1.3
	version 1.4				update AGC configuration of verB for better linearity. 2014-06-03
	version 1.4.1				Add 24M crystal application.                                     2014-07-21
*/
/* TAG TAGNAME     */
/*#define RWTRACES */

#define   SiLEVEL          1
#define   SiTAG            context->i2c->tag
#include "SiLabs_L1_RF_RDA5816SD_API.h"

#define RDA5816SD_Sleep system_wait
unsigned int  RDA5816SD_LockStatus            (RDA5816SD_Context *context);

int           RDA5816SD_Communication_Check   (RDA5816SD_Context *context) {
  unsigned char byteBuffer[5];
    if (L0_ReadCommandBytes(context->i2c, 5, byteBuffer) != 5) {
      SiTRACE("RDA5816SD_Communication_Check ERROR reading 5 bytes 0!\n");
      printf ("RDA5816SD_Communication_Check ERROR reading 5 bytes 0!\n");
    /*system("pause");*/
      return 0;
    }
    if (byteBuffer[0] == 0xff) {
      SiTRACE("RDA5816SD_Communication_Check ERROR: first byte 0xff!\n");
      return 0;
    }
    if (byteBuffer[0] == 0x00) {
      SiTRACE("RDA5816SD_Communication_Check ERROR: first byte 0x00!\n");
      return 0;
    }
  return 1;
}
void          RDA5816SD_IIC_Write             (RDA5816SD_Context *context, unsigned char write_index, unsigned char  value) {
  context->bytes[0] = value;
  L0_WriteBytes (context->i2c, write_index, 1, context->bytes);
}
void          RDA5816SD_IIC_Read              (RDA5816SD_Context *context, unsigned char read_index , unsigned char *value) {
  L0_ReadBytes (context->i2c, read_index, 1, value);
}
void          RDA5816SD_Initialize            (RDA5816SD_Context *context) {
  unsigned char buffer;
  RDA5816SD_Sleep(1);/* Wait 1ms. */

	/* Chip register soft reset 	 */
	RDA5816SD_IIC_Write(context, 0x04,0x04);
	RDA5816SD_IIC_Write(context, 0x04,0x05);

	/* Initial configuration start */

	/* pll setting  */
	RDA5816SD_IIC_Write(context, 0x2b,0x97); /*clk_interface_27m=1 */
	RDA5816SD_IIC_Write(context, 0x1a,0x13);
	RDA5816SD_IIC_Write(context, 0x41,0x53);
	RDA5816SD_IIC_Write(context, 0x38,0x9B);
	RDA5816SD_IIC_Write(context, 0x39,0x15);
	RDA5816SD_IIC_Write(context, 0x3A,0x00);
	RDA5816SD_IIC_Write(context, 0x3B,0x00);
	RDA5816SD_IIC_Write(context, 0x3C,0x0c);
	RDA5816SD_IIC_Write(context, 0x0c,0xE2);
	RDA5816SD_IIC_Write(context, 0x2e,0x6F);
	RDA5816SD_IIC_Write(context, 0x5b,0x20);
	RDA5816SD_IIC_Write(context, 0x2f,0x57);
	RDA5816SD_IIC_Write(context, 0x0d,0x70);
	RDA5816SD_IIC_Write(context, 0x16,0x03);
	RDA5816SD_IIC_Write(context, 0x18,0x4B);
	RDA5816SD_IIC_Write(context, 0x30,0xFF);
	RDA5816SD_IIC_Write(context, 0x5c,0xFF);
	RDA5816SD_IIC_Write(context, 0x6c,0xFF);
	RDA5816SD_IIC_Write(context, 0x6e,0xFF);
	RDA5816SD_IIC_Write(context, 0x65,0xD4);		/* v0.1.beta */
	RDA5816SD_IIC_Write(context, 0x70,0x3F);
	RDA5816SD_IIC_Write(context, 0x71,0x3F);
  if (context->xtal == 27) {
/*  #ifdef Xtal_27M	*/
	RDA5816SD_IIC_Write(context, 0x75,0x06);
	RDA5816SD_IIC_Write(context, 0x76,0x40);
	RDA5816SD_IIC_Write(context, 0x77,0x89);
/*	 #endif*/
  }

  if (context->xtal == 24) {
/*	  #ifdef Xtal_24M	*/
	RDA5816SD_IIC_Write(context, 0x75,0x07);
	RDA5816SD_IIC_Write(context, 0x76,0x10);
	RDA5816SD_IIC_Write(context, 0x77,0x9A);
/*     #endif	*/
  }
	RDA5816SD_IIC_Write(context, 0x53,0xA8);
	RDA5816SD_IIC_Write(context, 0x46,0x21);
	RDA5816SD_IIC_Write(context, 0x47,0x84);
	RDA5816SD_IIC_Write(context, 0x48,0x10);
	RDA5816SD_IIC_Write(context, 0x49,0x08);
	RDA5816SD_IIC_Write(context, 0x60,0x80);
	RDA5816SD_IIC_Write(context, 0x61,0x80);
	RDA5816SD_IIC_Write(context, 0x6A,0x08);
	RDA5816SD_IIC_Write(context, 0x6B,0x63);
	RDA5816SD_IIC_Write(context, 0x69,0xF8);
	RDA5816SD_IIC_Write(context, 0x57,0x64);

	RDA5816SD_IIC_Write(context, 0x05,0x55);
	RDA5816SD_IIC_Write(context, 0x06,0x65);
	RDA5816SD_IIC_Write(context, 0x15,0xFF);		/* v0.1.beta */
	RDA5816SD_IIC_Write(context, 0x4a,0xBB);
	RDA5816SD_IIC_Write(context, 0x4b,0xDB);

  if (context->xtal == 27) {
/*  #ifdef Xtal_27M	*/
	RDA5816SD_IIC_Write(context, 0x79,0x04);
	RDA5816SD_IIC_Write(context, 0x7a,0x2A);
	RDA5816SD_IIC_Write(context, 0x7b,0xAA);
	RDA5816SD_IIC_Write(context, 0x7c,0xAB);

	/*th2=1580M    */
	RDA5816SD_IIC_Write(context, 0x72,0x07);
	RDA5816SD_IIC_Write(context, 0x73,0x40);
	RDA5816SD_IIC_Write(context, 0x74,0x74);
/*	 #endif*/
  }

  if (context->xtal == 24) {
/*	  #ifdef Xtal_24M	*/
	/*th1=901M   */
	RDA5816SD_IIC_Write(context, 0x79,0x04);
	RDA5816SD_IIC_Write(context, 0x7a,0xB0);
	RDA5816SD_IIC_Write(context, 0x7b,0x00);
	RDA5816SD_IIC_Write(context, 0x7c,0x00);

	/*th2=1580M    */
	RDA5816SD_IIC_Write(context, 0x72,0x08);
	RDA5816SD_IIC_Write(context, 0x73,0x00);
	RDA5816SD_IIC_Write(context, 0x74,0x80);
/*	 #endif*/
  }


	/*agc setting */

	RDA5816SD_IIC_Write(context, 0x4f,0x40);
	RDA5816SD_IIC_Write(context, 0x5b,0x20);

	RDA5816SD_IIC_Read(context ,0x01, &buffer);		/* v1.1 */

	/* for blocker */
  RDA5816SD_IIC_Write(context, 0x16,0x0C);		/* stage setting */
  RDA5816SD_IIC_Write(context, 0x18,0x0C);
  RDA5816SD_IIC_Write(context, 0x30,0x1C);
  RDA5816SD_IIC_Write(context, 0x5c,0x2C);
  RDA5816SD_IIC_Write(context, 0x6c,0x2C);
  RDA5816SD_IIC_Write(context, 0x6e,0xAC);
  RDA5816SD_IIC_Write(context, 0x1b,0xBC);
  RDA5816SD_IIC_Write(context, 0x1d,0xBD);
  RDA5816SD_IIC_Write(context, 0x1f,0xBD);
  RDA5816SD_IIC_Write(context, 0x21,0xBE);
  RDA5816SD_IIC_Write(context, 0x23,0xFE);
  RDA5816SD_IIC_Write(context, 0x25,0xFE);
  RDA5816SD_IIC_Write(context, 0x27,0xFF);
  RDA5816SD_IIC_Write(context, 0x29,0xFF);
  RDA5816SD_IIC_Write(context, 0xb3,0xFF);
  RDA5816SD_IIC_Write(context, 0xb5,0xFF);

  RDA5816SD_IIC_Write(context, 0x17,0xF0);
  RDA5816SD_IIC_Write(context, 0x19,0xF0);
  RDA5816SD_IIC_Write(context, 0x31,0xF0);
  RDA5816SD_IIC_Write(context, 0x5d,0xF0);
  RDA5816SD_IIC_Write(context, 0x6d,0xF1);
  RDA5816SD_IIC_Write(context, 0x6f,0xF1);
  RDA5816SD_IIC_Write(context, 0x1c,0xF1);
  RDA5816SD_IIC_Write(context, 0x1e,0xF5);
  RDA5816SD_IIC_Write(context, 0x20,0xF6);
  RDA5816SD_IIC_Write(context, 0x22,0xFA);
  RDA5816SD_IIC_Write(context, 0x24,0xFA);
  RDA5816SD_IIC_Write(context, 0x26,0xFB);
  RDA5816SD_IIC_Write(context, 0x28,0xFF);
  RDA5816SD_IIC_Write(context, 0x2a,0xFF);
  RDA5816SD_IIC_Write(context, 0xb4,0xFF);
  RDA5816SD_IIC_Write(context, 0xb6,0xFF);

  RDA5816SD_IIC_Write(context, 0xb7,0x00);		/* start */
  RDA5816SD_IIC_Write(context, 0xb9,0x42);
  RDA5816SD_IIC_Write(context, 0xbb,0x4B);
  RDA5816SD_IIC_Write(context, 0xbd,0x4A);
  RDA5816SD_IIC_Write(context, 0xbf,0x5E);
  RDA5816SD_IIC_Write(context, 0xc1,0x44);
  RDA5816SD_IIC_Write(context, 0xc3,0x45);
  RDA5816SD_IIC_Write(context, 0xc5,0x47);
  RDA5816SD_IIC_Write(context, 0xa3,0x48);
  RDA5816SD_IIC_Write(context, 0xa5,0x46);
  RDA5816SD_IIC_Write(context, 0xa7,0x46);
  RDA5816SD_IIC_Write(context, 0xa9,0x43);
  RDA5816SD_IIC_Write(context, 0xab,0x24);
  RDA5816SD_IIC_Write(context, 0xad,0x34);
  RDA5816SD_IIC_Write(context, 0xaf,0x63);
  RDA5816SD_IIC_Write(context, 0xb1,0x95);

  RDA5816SD_IIC_Write(context, 0xb8,0x43);		/* end */
  RDA5816SD_IIC_Write(context, 0xba,0x78);
  RDA5816SD_IIC_Write(context, 0xbc,0x78);
  RDA5816SD_IIC_Write(context, 0xbe,0x87);
  RDA5816SD_IIC_Write(context, 0xc0,0x8A);
  RDA5816SD_IIC_Write(context, 0xc2,0x72);
  RDA5816SD_IIC_Write(context, 0xc4,0x73);
  RDA5816SD_IIC_Write(context, 0xc6,0x75);
  RDA5816SD_IIC_Write(context, 0xa4,0x76);
  RDA5816SD_IIC_Write(context, 0xa6,0x74);
  RDA5816SD_IIC_Write(context, 0xa8,0x6D);
  RDA5816SD_IIC_Write(context, 0xaa,0x6A);
  RDA5816SD_IIC_Write(context, 0xac,0x35);
  RDA5816SD_IIC_Write(context, 0xae,0x63);
  RDA5816SD_IIC_Write(context, 0xb0,0x95);
  RDA5816SD_IIC_Write(context, 0xb2,0xCA);

  RDA5816SD_IIC_Write(context, 0x81,0x7F);		/* rise */
  RDA5816SD_IIC_Write(context, 0x82,0xA7);
  RDA5816SD_IIC_Write(context, 0x83,0xB6);
  RDA5816SD_IIC_Write(context, 0x84,0xB5);
  RDA5816SD_IIC_Write(context, 0x85,0xB8);
  RDA5816SD_IIC_Write(context, 0x86,0xA3);
  RDA5816SD_IIC_Write(context, 0x87,0xA3);
  RDA5816SD_IIC_Write(context, 0x88,0xA5);
  RDA5816SD_IIC_Write(context, 0x89,0xA6);
  RDA5816SD_IIC_Write(context, 0x8a,0x9E);
  RDA5816SD_IIC_Write(context, 0x8b,0x8A);
  RDA5816SD_IIC_Write(context, 0x8c,0xc1);
  RDA5816SD_IIC_Write(context, 0x8d,0x6A);
  RDA5816SD_IIC_Write(context, 0x8e,0x9C);
  RDA5816SD_IIC_Write(context, 0x8f,0xD1);

  RDA5816SD_IIC_Write(context, 0x90,0x00);		/* fall */
  RDA5816SD_IIC_Write(context, 0x91,0x0A);
  RDA5816SD_IIC_Write(context, 0x92,0x13);
  RDA5816SD_IIC_Write(context, 0x93,0x17);
  RDA5816SD_IIC_Write(context, 0x94,0x0B);
  RDA5816SD_IIC_Write(context, 0x95,0x0C);
  RDA5816SD_IIC_Write(context, 0x96,0x0F);
  RDA5816SD_IIC_Write(context, 0x97,0x10);
  RDA5816SD_IIC_Write(context, 0x98,0x0E);
  RDA5816SD_IIC_Write(context, 0x99,0x0E);
  RDA5816SD_IIC_Write(context, 0x9a,0x14);
  RDA5816SD_IIC_Write(context, 0x9b,0x00);
  RDA5816SD_IIC_Write(context, 0x9c,0x1C);
  RDA5816SD_IIC_Write(context, 0x9d,0x2C);
  RDA5816SD_IIC_Write(context, 0x9e,0x5B);

	RDA5816SD_Sleep(10);	/*Wait 10ms; */

	RDA5816SD_IIC_Write(context, 0x04,0x85);  /* enable current channel of dual-channel tuner */
  context->i2c->address = context->i2c->address^0x02;

	RDA5816SD_IIC_Read (context,0x04,&buffer);
	RDA5816SD_IIC_Write(context,0x04,(buffer|0x80));  /* enable adjacent channel of dual-channel tuner */

  context->i2c->address = context->address_log;

	RDA5816SD_Sleep(10);	/*Wait 10ms; */
}
/*************************************************************************
  Function to Set the RDA5816SD
  fPLL:   Frequency              unit: MHz  from 250 to 2300
  fSym:   SymbolRate             unit: KS/s from 1000 to 45000
*************************************************************************/
long          RDA5816SD_Set                   (RDA5816SD_Context *context, long fPLL_MHz, long lpf_MHz) {
  unsigned char   buffer;
  unsigned int temp_value = 0;
  unsigned char  Filter_bw_control_bit;

  SiTRACE("fPLL_MHz %ld, lpf_MHz %ld\n", fPLL_MHz, lpf_MHz);

  RDA5816SD_IIC_Write(context, 0x04,0xc1);

  /* set frequency start */
  RDA5816SD_IIC_Read (context ,0x65,&buffer);

  context->RF = fPLL_MHz*1000;

	if(fPLL_MHz>1075)
	{ /* Mixer divider = 2 */
		buffer |= 0x10; /* bit 4 (div2_en_mixer) = 1 */
		buffer &= 0xF7; /* bit 3 (div4_en_mixer) = 0 */
		/* fPLL_MHz = fPLL_MHz; */
	}
	else
	{ /* Mixer divider = 4 */
		buffer &= 0xEF; /* bit 4 (div2_en_mixer) = 0 */
		buffer |= 0x08; /* bit 3 (div4_en_mixer) = 1 */
		fPLL_MHz = fPLL_MHz * 2;
	}
  RDA5816SD_IIC_Write(context, 0x65, buffer);

  if (context->xtal == 27) {
/*	  #ifdef Xtal_27M	*/
    temp_value = (unsigned long)fPLL_MHz* 77672;	/*((2^21) / RDA5816SD__XTALFREQ); */
/*	 #endif*/
  }

  if (context->xtal == 24) {
/*	  #ifdef Xtal_24M	*/
    temp_value = (unsigned long)fPLL_MHz* 87381;	/*((2^21) / RDA5816SD__XTALFREQ); */
/*	 #endif*/
  }
  SiTRACE("fPLL_MHz %ld, temp_value %ld 0x%08x\n", fPLL_MHz, temp_value, temp_value);

	buffer = ((unsigned char)((temp_value>>24)&0xff));
	RDA5816SD_IIC_Write(context, 0x07,buffer);
	buffer = ((unsigned char)((temp_value>>16)&0xff));
	RDA5816SD_IIC_Write(context, 0x08,buffer);
	buffer = ((unsigned char)((temp_value>> 8)&0xff));
	RDA5816SD_IIC_Write(context, 0x09,buffer);
	buffer = ((unsigned char)( temp_value&0xff));
	RDA5816SD_IIC_Write(context, 0x0a,buffer);
  /* set frequency end */

  /*  set Filter bandwidth start */
  Filter_bw_control_bit = (unsigned char)(lpf_MHz);
	if(Filter_bw_control_bit<4)
	Filter_bw_control_bit = 4;		/* MHz */
	else if(Filter_bw_control_bit>40)
	Filter_bw_control_bit = 40;	/* MHz */

	Filter_bw_control_bit &= 0x3f;
	Filter_bw_control_bit |= 0x40;
	RDA5816SD_IIC_Write(context, 0x0b,Filter_bw_control_bit);
	/* set Filter bandwidth end */

  RDA5816SD_IIC_Write(context, 0x04,0xc3);

  RDA5816SD_Sleep(5);/* Wait 5ms; */

  return 1;
}
unsigned int  RDA5816SD_LockStatus            (RDA5816SD_Context *context) {
	unsigned char buffer, i ;

	for(i=0; i<100; i++)
	{
		RDA5816SD_IIC_Read(context ,0x03,&buffer);
		if((buffer & 0x03) != 0x03)
		{
			return 0;
		}
	}
	return 1;
}
/************************************************************************
   rf_chn=1 : switch to the same-side      RF_pin
   rf_chn=0 : switch to the different-side RF_pin
*/
unsigned int  L1_RF_RDA5816SD_RfSel           (RDA5816SD_Context *context, unsigned char rf_chn) {
	unsigned char buffer;

	if (rf_chn)		/* Connect the same-side RF_pin, disconnect the different-side RF_pin */
	{
		RDA5816SD_IIC_Read (context ,0x65,&buffer);
		RDA5816SD_IIC_Write(context, 0x65,(buffer | 0x04));

    context->i2c->address = context->i2c->address^0x02;
		RDA5816SD_IIC_Read (context,0x65,&buffer);
		RDA5816SD_IIC_Write(context,0x65,(buffer & 0xFD));
    context->i2c->address = context->address_log;
	}
	else				/* Connect the different-side RF_pin, disconnect the same-side RF_pin */
	{
    context->i2c->address = context->i2c->address^0x02;
		RDA5816SD_IIC_Read (context, 0x65,&buffer);
		RDA5816SD_IIC_Write(context, 0x65,(buffer | 0x02));
    context->i2c->address = context->address_log;

		RDA5816SD_IIC_Read (context, 0x65,&buffer);
		RDA5816SD_IIC_Write(context, 0x65,(buffer & 0xFB));
	}
	return 1;
}
void          L1_RF_RDA5816SD_Init            (RDA5816SD_Context *context, unsigned int add) {
    SiTRACE_X("RDA5816SD_Init starting...\n");
    SiTRACE_X("RDA5816SD Driver: this is untested code which needs to be verified !...\n");
    context->i2c = &(context->i2cObj);
    L0_Init(context->i2c);
    L0_SetAddress(context->i2c, add, 1);
    context->i2c->mustReadWithoutStop =1;
    context->IF                   =                     0;
    context->RF                   =                900000;
    context->minRF                =                900000;
    context->maxRF                =               2200000;
    context->LPF                  =                 38100;
    context->loopthrough          =                     0;
    context->xtal                 =                    27;
    context->address_log          = context->i2c->address;
    context->sub                  =                     0;
    context->rssi_offset          =                     0;
    SiTRACE_X("L1_RF_RDA5816SD_Init complete...\n");
}
int           L1_RF_RDA5816SD_InitAfterReset  (RDA5816SD_Context *context) {
  SiTRACE("L1_RF_RDA5816SD_InitAfterReset starting...\n");
  RDA5816SD_Initialize(context);
  SiTRACE("L1_RF_RDA5816SD_InitAfterReset complete...\n");
  return 0;
}
int           L1_RF_RDA5816SD_Get_RF          (RDA5816SD_Context *context) {
   return context->RF;
}
int           L1_RF_RDA5816SD_Tune            (RDA5816SD_Context *context, int rf_kHz      ) {
   /* Checking limits */
   if (rf_kHz < (context->minRF)) {
     SiERROR("RDA5816SD rf_kHz < minRF \n");
     SiTRACE("rf_kHz %d < minRF %d\n",rf_kHz,context->minRF); return L1_RF_RDA5816SD_Tune(context, context->minRF);
   }
   if (rf_kHz > (context->maxRF)) {
     SiERROR("RDA5816SD rf_kHz > maxRF \n");
     SiTRACE("rf_kHz %d > maxRF %d\n",rf_kHz,context->maxRF); return L1_RF_RDA5816SD_Tune(context, context->maxRF);
   }
   context->i2c->trackRead = context->i2c->trackWrite;
   context->RF = rf_kHz;
   RDA5816SD_Set(context, (context->RF + 500)/1000.0, context->LPF/1000.0);
   return context->RF;
}
int           L1_RF_RDA5816SD_LPF             (RDA5816SD_Context *context, int lpf_khz     ) {
  if (lpf_khz != 0) { /* use '0' to retrieve the current value */
    if ((lpf_khz > 45000)) {
      SiTRACE("RDA5816SD requested lpf_khz %d higher than max, set to max\n", lpf_khz);
      lpf_khz = 45000;
    }
    if ((lpf_khz < 4000)) {
      SiTRACE("RDA5816SD requested lpf_khz %d smaller than min, set to min\n", lpf_khz);
      lpf_khz = 4000;
    }
    context->LPF = (int)((lpf_khz + 500.0));
  }

  SiTRACE("RDA5816SD lpf %d kHz\n", context->LPF);

  RDA5816SD_Set(context, (context->RF + 500)/1000.0, context->LPF/1000.0);
  return context->LPF;
}
int           L1_RF_RDA5816SD_RSSI            (RDA5816SD_Context *context, int other_gain  ) {
/* Gain stage limits
                                             filter-..
                                               i2v--..
                                           post.. --..
                                          st2--.. --..
                                       pre.. --.. --..
                                     st1--.. --.. --..    */
#define RDA5816SD_Gain_Stage__0 0x001 /* '0000 0000 0001' */
#define RDA5816SD_Gain_Stage__1 0x002 /* '0000 0000 0010' */
#define RDA5816SD_Gain_Stage__2 0x003 /* '0000 0000 0011' */
#define RDA5816SD_Gain_Stage__3 0x013 /* '0000 0001 0011' */
#define RDA5816SD_Gain_Stage__4 0x023 /* '0000 0010 0011' */
#define RDA5816SD_Gain_Stage__5 0x027 /* '0000 0010 0111' */
#define RDA5816SD_Gain_Stage__6 0x09b /* '0000 1001 1011' */
#define RDA5816SD_Gain_Stage__7 0x0ab /* '0000 1010 1011' */
#define RDA5816SD_Gain_Stage__8 0x1ab /* '0001 1010 1011' */
#define RDA5816SD_Gain_Stage__9 0x2ab /* '0010 1010 1011' */
#define RDA5816SD_Gain_Stage_10 0x6ab /* '0110 1010 1011' */
#define RDA5816SD_Gain_Stage_11 0x7ab /* '0111 1010 1011' */
#define RDA5816SD_Gain_Stage_12 0xbab /* '1011 1010 1011' */
#define RDA5816SD_Gain_Stage_13 0xfeb /* '1111 1110 1011' */
#define RDA5816SD_Gain_Stage_14 0xfff /* '1111 1111 1111' */
#define RDA5816SD_Gain_Stage_15 0xfff /* '1111 1111 1111' */

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

  RDA5816SD_IIC_Read(context, 0x16, &data16);
  i2v    = (data16&0xc0)>>6;
  filter = (data16&0x30)>>4;
  st1    = (data16&0x0c)>>2;
  st2    = (data16&0x03)>>0;

  RDA5816SD_IIC_Read(context, 0x17, &data17);
  pre    = (data17&0x0c)>>2;
  post   = (data17&0x03)>>0;

  stage_code = (st1<<10) + (pre<<8) + (st2<<6) + (post<<4) + (i2v<<2) + (filter<<0);

       if (stage_code >= RDA5816SD_Gain_Stage_14 ) { gain_stage = 14; }
  else if (stage_code >= RDA5816SD_Gain_Stage_13 ) { gain_stage = 13; }
  else if (stage_code >= RDA5816SD_Gain_Stage_12 ) { gain_stage = 12; }
  else if (stage_code >= RDA5816SD_Gain_Stage_11 ) { gain_stage = 11; }
  else if (stage_code >= RDA5816SD_Gain_Stage_10 ) { gain_stage = 10; }
  else if (stage_code >= RDA5816SD_Gain_Stage__9 ) { gain_stage =  9; }
  else if (stage_code >= RDA5816SD_Gain_Stage__8 ) { gain_stage =  8; }
  else if (stage_code >= RDA5816SD_Gain_Stage__7 ) { gain_stage =  7; }
  else if (stage_code >= RDA5816SD_Gain_Stage__6 ) { gain_stage =  6; }
  else if (stage_code >= RDA5816SD_Gain_Stage__5 ) { gain_stage =  5; }
  else if (stage_code >= RDA5816SD_Gain_Stage__4 ) { gain_stage =  4; }
  else if (stage_code >= RDA5816SD_Gain_Stage__3 ) { gain_stage =  3; }
  else if (stage_code >= RDA5816SD_Gain_Stage__2 ) { gain_stage =  2; }
  else if (stage_code >= RDA5816SD_Gain_Stage__1 ) { gain_stage =  1; }
  else                                            { gain_stage =  0; }

       if (context->RF >= 1990000) { band = 6; }
  else if (context->RF >= 1660000) { band = 5; }
  else if (context->RF >= 1450000) { band = 4; }
  else if (context->RF >= 1280000) { band = 3; }
  else if (context->RF >= 1090000) { band = 2; }
  else                             { band = 1; }

  RDA5816SD_IIC_Read(context, 0xb7, &vga);
  vga_gain = vga*30.0/255;

  total_gain = gain[band-1][gain_stage] + vga_gain;

  if (0) {
    SiTRACE("RDA5816SD stage_code %02x%02x %02x%02x %02x%02x -> stage_code 0x%06x\n", st1, pre, st2, post, i2v, filter, stage_code);
    SiTRACE("RDA5816SD st1 %d, pre %d, st2 %d, post %d, i2v %d, filter %d -> stage_code 0x%06x -> gain_stage %d\n", st1, pre, st2, post, i2v, filter, stage_code, gain_stage);
    SiTRACE("RDA5816SD vga %d -> vga_gain %f\n", vga, vga_gain);
    SiTRACE("RDA5816SD RSSI = gain[%d][%d] + vga_gain = %f + %f = %f\n", band-1, gain_stage, gain[band-1][gain_stage], vga_gain, total_gain);
  }

  return  other_gain-total_gain;
}
int           L1_RF_RDA5816SD_RSSI_from_AGC   (RDA5816SD_Context *context, int if_agc      ) {
/* This is an estimation of RSSI based on the IF_AGC (some dBm of error are possible according to the RF and the input level) */
/* previous   RDA5816SD_agc         []           = {   0,   188,  231,  256}; */
/* previous   RDA5816SD_level_dBm_10[]           = {  45,  -700, -800, -919}; */
  int   RDA5816SD_agc         []           = {    0,   35,   45,  132,  203,  232,  256};
  int   RDA5816SD_level_dBm_10[]           = {  -50,  -50, -120, -500, -750, -780, -899};
  int   RDA5816SD_agc_pre_lna []           = {    0,   32,  202,  238,  256};
  int   RDA5816SD_level_dBm_10_pre_lna[]   = {   50,  20,  -620, -640, -791};

  int   index;
  int   table_length;
  int  *x;
  int  *y;
  int   slope;
  context = context; /* To avoid compiler warning while keeping a common prototype for all tuners */
  if (if_agc>=256) return  context->rssi;
  if (if_agc<   0) return  context->rssi;

  if (context->rssi_offset==0) {
     x = RDA5816SD_agc;
     y = RDA5816SD_level_dBm_10;
     table_length = sizeof(RDA5816SD_agc)/sizeof(int);
  } else {
     x = RDA5816SD_agc_pre_lna;
     y = RDA5816SD_level_dBm_10_pre_lna;
     table_length = sizeof(RDA5816SD_agc_pre_lna)/sizeof(int);
  }
  /* Finding in which segment the if_agc value is */
  for (index = 0; index < table_length; index ++) {if (x[index] > if_agc ) break;}
  /* Computing segment slope */
  slope =  ((y[index]-y[index-1])*1000)/(x[index]-x[index-1]);
  /* Linear approximation of rssi value in segment (rssi values will be in 0.1dBm unit: '-523' means -52.3 dBm) */
  if (context->rssi_offset==8) {
    context->rssi = ((y[index-1] + ((if_agc - x[index-1])*slope + 500)/1000) - 53)/10;
  } else if (context->rssi_offset==18) {
    context->rssi = ((y[index-1] + ((if_agc - x[index-1])*slope + 500)/1000) + 49)/10;
  } else {
    context->rssi = ((y[index-1] + ((if_agc - x[index-1])*slope + 500)/1000))/10;
  }
  SiTRACE("L1_RF_RDA5816SD_RSSI if_agc %3d rssi %5d dBm\n",if_agc ,context->rssi);
  return context->rssi;
}

unsigned char L1_RF_RDA5816SD_Wakeup          (RDA5816SD_Context *context) {
  unsigned char temp;
  SiTRACE("L1_RF_RDA5816SD_Wakeup starting...\n");

  RDA5816SD_IIC_Read (context, 0x04, &temp);
  temp = temp | 0x80;
  RDA5816SD_IIC_Write(context, 0x04,temp);

  SiTRACE("L1_RF_RDA5816SD_Wakeup done\n");
  return 0;
}
unsigned char L1_RF_RDA5816SD_Standby         (RDA5816SD_Context *context) {
  unsigned char temp;
  SiTRACE("L1_RF_RDA5816SD_Standby starting...\n");

  RDA5816SD_IIC_Read (context, 0x04, &temp);
  temp = temp & 0x7F;
  RDA5816SD_IIC_Write(context, 0x04,temp);

  SiTRACE("L1_RF_RDA5816SD_Standby done\n");
  return 0;
}
char*         L1_RF_RDA5816SD_TAG_TEXT        (void) { return (char *)"TAGNAME"; }
void          L1_RF_RDA5816SD_pre_lna_gain    (RDA5816SD_Context *context, int st1) {
  RDA5816SD_Sleep(1); /*Wait 1ms; */
  switch (st1) {
      case 0 : { SiTRACE("RDA5816SD st1= 0: pre_lna gain reduced by around 18dB\n");
              context->rssi_offset = 18;
              RDA5816SD_IIC_Write(context, 0x16,0x00);  /* stage setting */
              RDA5816SD_IIC_Write(context, 0x18,0x00);
              RDA5816SD_IIC_Write(context, 0x30,0x10);
              RDA5816SD_IIC_Write(context, 0x5c,0x20);
              RDA5816SD_IIC_Write(context, 0x6c,0x30);
              RDA5816SD_IIC_Write(context, 0x6e,0x30);
              RDA5816SD_IIC_Write(context, 0x1b,0x70);
              RDA5816SD_IIC_Write(context, 0x1d,0xB1);
              RDA5816SD_IIC_Write(context, 0x1f,0xB1);
              RDA5816SD_IIC_Write(context, 0x21,0xB2);
              RDA5816SD_IIC_Write(context, 0x23,0xB2);
              RDA5816SD_IIC_Write(context, 0x25,0xF2);
              RDA5816SD_IIC_Write(context, 0x27,0xF3);
              RDA5816SD_IIC_Write(context, 0x29,0xF3);
              RDA5816SD_IIC_Write(context, 0xb3,0xF3);
              RDA5816SD_IIC_Write(context, 0xb5,0xF3);
              break;
      }
      case 1 : { SiTRACE("RDA5816SD  st1= 1: pre_lna gain reduced by around 13dB\n");
              context->rssi_offset = 13;
              RDA5816SD_IIC_Write(context, 0x16,0x04);  /* stage setting */
              RDA5816SD_IIC_Write(context, 0x18,0x04);
              RDA5816SD_IIC_Write(context, 0x30,0x14);
              RDA5816SD_IIC_Write(context, 0x5c,0x24);
              RDA5816SD_IIC_Write(context, 0x6c,0x34);
              RDA5816SD_IIC_Write(context, 0x6e,0x34);
              RDA5816SD_IIC_Write(context, 0x1b,0x74);
              RDA5816SD_IIC_Write(context, 0x1d,0xB5);
              RDA5816SD_IIC_Write(context, 0x1f,0xB5);
              RDA5816SD_IIC_Write(context, 0x21,0xB6);
              RDA5816SD_IIC_Write(context, 0x23,0xB6);
              RDA5816SD_IIC_Write(context, 0x25,0xF6);
              RDA5816SD_IIC_Write(context, 0x27,0xF7);
              RDA5816SD_IIC_Write(context, 0x29,0xF7);
              RDA5816SD_IIC_Write(context, 0xb3,0xF7);
              RDA5816SD_IIC_Write(context, 0xb5,0xF7);
              break;
      }
      case 2 : { SiTRACE("RDA5816SD  st1= 2: pre_lna gain reduced by around 8dB\n");
              context->rssi_offset = 8;
              RDA5816SD_IIC_Write(context, 0x16,0x08);  /* stage setting */
              RDA5816SD_IIC_Write(context, 0x18,0x08);
              RDA5816SD_IIC_Write(context, 0x30,0x18);
              RDA5816SD_IIC_Write(context, 0x5c,0x28);
              RDA5816SD_IIC_Write(context, 0x6c,0x38);
              RDA5816SD_IIC_Write(context, 0x6e,0x38);
              RDA5816SD_IIC_Write(context, 0x1b,0x78);
              RDA5816SD_IIC_Write(context, 0x1d,0xB9);
              RDA5816SD_IIC_Write(context, 0x1f,0xB9);
              RDA5816SD_IIC_Write(context, 0x21,0xBA);
              RDA5816SD_IIC_Write(context, 0x23,0xBA);
              RDA5816SD_IIC_Write(context, 0x25,0xFA);
              RDA5816SD_IIC_Write(context, 0x27,0xFB);
              RDA5816SD_IIC_Write(context, 0x29,0xFB);
              RDA5816SD_IIC_Write(context, 0xb3,0xFB);
              RDA5816SD_IIC_Write(context, 0xb5,0xFB);
              break;
      }
      case 3 :
      default: { SiTRACE("RDA5816SD  st1= 3: pre_lna gain not reduced    \n");
              context->rssi_offset = 0;
              RDA5816SD_Initialize(context);
              break;
      }
  }
  if (context->rssi_offset != 0) { SiTRACE("RDA5816SD  st1= %d: pre_lna gain is reduced\n", st1);
      RDA5816SD_IIC_Write(context, 0x17,0xF0);
      RDA5816SD_IIC_Write(context, 0x19,0xF0);
      RDA5816SD_IIC_Write(context, 0x31,0xF0);
      RDA5816SD_IIC_Write(context, 0x5d,0xF0);
      RDA5816SD_IIC_Write(context, 0x6d,0xF0);
      RDA5816SD_IIC_Write(context, 0x6f,0xF1);
      RDA5816SD_IIC_Write(context, 0x1c,0xF5);
      RDA5816SD_IIC_Write(context, 0x1e,0x35);
      RDA5816SD_IIC_Write(context, 0x20,0x79);
      RDA5816SD_IIC_Write(context, 0x22,0x9D);
      RDA5816SD_IIC_Write(context, 0x24,0xBE);
      RDA5816SD_IIC_Write(context, 0x26,0xBE);
      RDA5816SD_IIC_Write(context, 0x28,0xBE);
      RDA5816SD_IIC_Write(context, 0x2a,0xCF);
      RDA5816SD_IIC_Write(context, 0xb4,0xDF);
      RDA5816SD_IIC_Write(context, 0xb6,0x0F);
      RDA5816SD_IIC_Write(context, 0xb7,0x15);  /* start */
      RDA5816SD_IIC_Write(context, 0xb9,0x6C);
      RDA5816SD_IIC_Write(context, 0xbb,0x63);
      RDA5816SD_IIC_Write(context, 0xbd,0x5A);
      RDA5816SD_IIC_Write(context, 0xbf,0x5A);
      RDA5816SD_IIC_Write(context, 0xc1,0x55);
      RDA5816SD_IIC_Write(context, 0xc3,0x55);
      RDA5816SD_IIC_Write(context, 0xc5,0x47);
      RDA5816SD_IIC_Write(context, 0xa3,0x53);
      RDA5816SD_IIC_Write(context, 0xa5,0x4F);
      RDA5816SD_IIC_Write(context, 0xa7,0x4E);
      RDA5816SD_IIC_Write(context, 0xa9,0x4E);
      RDA5816SD_IIC_Write(context, 0xab,0x54);
      RDA5816SD_IIC_Write(context, 0xad,0x31);
      RDA5816SD_IIC_Write(context, 0xaf,0x43);
      RDA5816SD_IIC_Write(context, 0xb1,0x9F);
      RDA5816SD_IIC_Write(context, 0xb8,0x6C);  /* end */
      RDA5816SD_IIC_Write(context, 0xba,0x92);
      RDA5816SD_IIC_Write(context, 0xbc,0x8A);
      RDA5816SD_IIC_Write(context, 0xbe,0x8A);
      RDA5816SD_IIC_Write(context, 0xc0,0x82);
      RDA5816SD_IIC_Write(context, 0xc2,0x93);
      RDA5816SD_IIC_Write(context, 0xc4,0x85);
      RDA5816SD_IIC_Write(context, 0xc6,0x77);
      RDA5816SD_IIC_Write(context, 0xa4,0x82);
      RDA5816SD_IIC_Write(context, 0xa6,0x7E);
      RDA5816SD_IIC_Write(context, 0xa8,0x7D);
      RDA5816SD_IIC_Write(context, 0xaa,0x6F);
      RDA5816SD_IIC_Write(context, 0xac,0x65);
      RDA5816SD_IIC_Write(context, 0xae,0x43);
      RDA5816SD_IIC_Write(context, 0xb0,0x9F);
      RDA5816SD_IIC_Write(context, 0xb2,0xF0);
      RDA5816SD_IIC_Write(context, 0x81,0x92);  /* rise */
      RDA5816SD_IIC_Write(context, 0x82,0xB4);
      RDA5816SD_IIC_Write(context, 0x83,0xB3);
      RDA5816SD_IIC_Write(context, 0x84,0xAC);
      RDA5816SD_IIC_Write(context, 0x85,0xBA);
      RDA5816SD_IIC_Write(context, 0x86,0xBC);
      RDA5816SD_IIC_Write(context, 0x87,0xAF);
      RDA5816SD_IIC_Write(context, 0x88,0xA2);
      RDA5816SD_IIC_Write(context, 0x89,0xAC);
      RDA5816SD_IIC_Write(context, 0x8a,0xA9);
      RDA5816SD_IIC_Write(context, 0x8b,0x9B);
      RDA5816SD_IIC_Write(context, 0x8c,0x7D);
      RDA5816SD_IIC_Write(context, 0x8d,0x74);
      RDA5816SD_IIC_Write(context, 0x8e,0x9F);
      RDA5816SD_IIC_Write(context, 0x8f,0xF0);
      RDA5816SD_IIC_Write(context, 0x90,0x15);  /* fall */
      RDA5816SD_IIC_Write(context, 0x91,0x39);
      RDA5816SD_IIC_Write(context, 0x92,0x30);
      RDA5816SD_IIC_Write(context, 0x93,0x27);
      RDA5816SD_IIC_Write(context, 0x94,0x29);
      RDA5816SD_IIC_Write(context, 0x95,0x0D);
      RDA5816SD_IIC_Write(context, 0x96,0x10);
      RDA5816SD_IIC_Write(context, 0x97,0x1E);
      RDA5816SD_IIC_Write(context, 0x98,0x1A);
      RDA5816SD_IIC_Write(context, 0x99,0x19);
      RDA5816SD_IIC_Write(context, 0x9a,0x19);
      RDA5816SD_IIC_Write(context, 0x9b,0x32);
      RDA5816SD_IIC_Write(context, 0x9c,0x1F);
      RDA5816SD_IIC_Write(context, 0x9d,0x31);
      RDA5816SD_IIC_Write(context, 0x9e,0x43);
      RDA5816SD_Sleep(10);	/*Wait 10ms; */
  }
}
