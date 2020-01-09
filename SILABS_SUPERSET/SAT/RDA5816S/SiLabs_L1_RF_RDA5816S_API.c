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
/*                     SILEMBIA Layer 1                  RF Tuner RDA5816S_functions                         */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains all API RDA5816S_functions for the RDA5816S Tuner on the RF board             */
/*     All included RDA5816S_functions can be accessed by the higher software level as imports               */
/*     All RDA5816S_functions are declared in Silabs_L1_RF_RDA5816S_API.h                                    */
/*************************************************************************************************************/
/* Change log:

 As from svn 6172:
   <correction> In L1_RF_RDA5816S_Tune: storing frequency value in context before calling RDA5816S_Set

 As from svn 5298:
   Case change when including SiLabs_L1_RF_RDA5816S_API.h (for Linux compatibility)

 As from svn 4240:
   In L1_RF_RDA5816S_Standby:
     Corrected the write line which generated a SW reset.

 As from svn 4024:
   Code upgraded following RDA changes

 As from SVN 2920:
   Initial version: L1_RF_RDA5816S_RSSI not working! (inherited from RDA5815 driver, not reworked by RDA yet)

   RDA5816S possible i2c addresses (this is a dual SAT tuner):
     0x10/0x12(0-0.1VDD   on ADD)
     0x14/0x16(open       on ADD)
     0x1c/0x1E(0.9-1.0VDD on ADD)

*************************************************************************************************************/
/* RDA change log:
  Filename:     RDA5816s_16110d_v*.c
  Description:  RDA5816 Digital Satellite Tuner IC driver.
  version 1.0    The primary version,  created by Hongxin Wang  2012-6-19
  version 1.1    Modify the agc setting. by Rui Cao  2012-7-18
  version 1.2    For RDA5816s_verB.Renew VCOI & PRESC values; Renew VCO range.  by Yilei LIU  2012-11-20
  version 2.1    For RDA5816s_verC.Modify LO regulator value. by LiuYL  2012-12-03
  version 2.2    Xout amplitude enhanced from 0.8 to 1.2 Vpp. Renew VCO & PRESC settings to optimize yield rate of FT. by LiuYL  2013-01-05
  version 2.3    Internal test version, never released.
  version 2.4    Improve VCO-PLL robustness. Add function "RDA5816s_GetLockStatus()".  2013-12-26.
*/
/* TAG TAGNAME     */
/*#define RWTRACES */

#define   SiLEVEL          1
#define   SiTAG            context->i2c->tag
#include "SiLabs_L1_RF_RDA5816S_API.h"

#define RDA5816Sleep system_wait

int           RDA5816S_Communication_Check   (RDA5816S_Context *context) {
  unsigned char byteBuffer[5];
    if (L0_ReadCommandBytes(context->i2c, 5, byteBuffer) != 5) {
      SiTRACE("RDA5816S_Communication_Check ERROR reading 5 bytes 0!\n");
      printf ("RDA5816S_Communication_Check ERROR reading 5 bytes 0!\n");
    /*system("pause");*/
      return 0;
    }
    if (byteBuffer[0] == 0xff) {
      SiTRACE("RDA5816S_Communication_Check ERROR: first byte 0xff!\n");
      return 0;
    }
    if (byteBuffer[0] == 0x00) {
      SiTRACE("RDA5816S_Communication_Check ERROR: first byte 0x00!\n");
      return 0;
    }
  return 1;
}
void          RDA5816S_IIC_Write             (RDA5816S_Context *context, unsigned char write_index, unsigned char  value) {
  context->bytes[0] = value;
  L0_WriteBytes (context->i2c, write_index, 1, context->bytes);
}
void          RDA5816S_IIC_Read              (RDA5816S_Context *context, unsigned char read_index , unsigned char *value) {
  L0_ReadBytes (context->i2c, read_index, 1, value);
}
/************************************************************************
  Function to Get Lock Status of tuner PLL
  Return 0:    Lock;
  Return 1:    Unlock.
************************************************************************/
unsigned char RDA5816s_GetLockStatus         (RDA5816S_Context *context) {
  unsigned char temp, i ;

  for(i=0; i<100; i++)    /* Loop times: 100 is recommanded; at least 30.*/
  {
    RDA5816S_IIC_Read (context,0x03,&temp);
    if((temp & 0x03) != 0x03)
    {
      return 1;  /* status: Unlock*/
    }
  }
  return 0;  /* status: Lock*/
}
void          RDA5816S_Initialize            (RDA5816S_Context *context) {
  unsigned char temp;

  RDA5816Sleep(1);/* Wait 1ms. */

   /* Chip register soft reset  */
  RDA5816S_IIC_Write(context, 0x04,0x04);
  RDA5816S_IIC_Write(context, 0x04,0x05);

  /*  Initial configuration start */

  /* pll setting */
  RDA5816S_IIC_Write(context, 0x2b,0x97); /* clk_interface_27m=1 */
  RDA5816S_IIC_Write(context, 0x1a,0x13);
  RDA5816S_IIC_Write(context, 0x41,0x53);
  RDA5816S_IIC_Write(context, 0x38,0x9B);/* v2.2, RDA_LiuYL  2012-12-28 */
  RDA5816S_IIC_Write(context, 0x39,0x15);
  RDA5816S_IIC_Write(context, 0x3A,0x00);
  RDA5816S_IIC_Write(context, 0x3B,0x00);
  RDA5816S_IIC_Write(context, 0x3C,0x0c);
  RDA5816S_IIC_Write(context, 0x0c,0xE2);
  RDA5816S_IIC_Write(context, 0x2e,0x6F);
  RDA5816S_IIC_Write(context, 0x5b,0x20);
  RDA5816S_IIC_Write(context, 0x2f,0x57);
  RDA5816S_IIC_Write(context, 0x0d,0x70);
  RDA5816S_IIC_Write(context, 0x16,0x03);
  RDA5816S_IIC_Write(context, 0x18,0x4B);
  RDA5816S_IIC_Write(context, 0x30,0xFF);
  RDA5816S_IIC_Write(context, 0x5c,0xFF);
  RDA5816S_IIC_Write(context, 0x6c,0xFF);
  RDA5816S_IIC_Write(context, 0x6e,0xFF);
  RDA5816S_IIC_Write(context, 0x65,0xC0); /*v2.2, RDA_LiuYL  2013-01-05 */
  RDA5816S_IIC_Write(context, 0x70,0x3F);
  RDA5816S_IIC_Write(context, 0x71,0x3F);
  RDA5816S_IIC_Write(context, 0x75,0x06);
  RDA5816S_IIC_Write(context, 0x76,0x40);
  RDA5816S_IIC_Write(context, 0x77,0x89);
  RDA5816S_IIC_Write(context, 0x53,0xA8);
  RDA5816S_IIC_Write(context, 0x46,0x21);
  RDA5816S_IIC_Write(context, 0x47,0x84);
  RDA5816S_IIC_Write(context, 0x48,0x10);
  RDA5816S_IIC_Write(context, 0x49,0x08);
  RDA5816S_IIC_Write(context, 0x60,0x80);
  RDA5816S_IIC_Write(context, 0x61,0x80);
  RDA5816S_IIC_Write(context, 0x6A,0x08);
  RDA5816S_IIC_Write(context, 0x6B,0x63);
  RDA5816S_IIC_Write(context, 0x69,0xF8);
  RDA5816S_IIC_Write(context, 0x57,0x64);

  RDA5816S_IIC_Write(context, 0x05,0x55);  /*v2.2, RDA_LiuYL  2013-01-05*/
  RDA5816S_IIC_Write(context, 0x06,0x65);  /*v1.2, RDA_LiuYL  2012-11-20*/
  RDA5816S_IIC_Write(context, 0x15,0xFD);  /*v2.1, RDA_LiuYL  2012-12-03*/
  RDA5816S_IIC_Write(context, 0x4a,0xBB);  /*v2.2, RDA_LiuYL  2013-01-05*/
  RDA5816S_IIC_Write(context, 0x4b,0xDB);  /*v2.2, RDA_LiuYL  2013-01-05*/

   /* th1=901M  */
  RDA5816S_IIC_Write(context, 0x79,0x04);
  RDA5816S_IIC_Write(context, 0x7a,0x2A);
  RDA5816S_IIC_Write(context, 0x7b,0xAA);
  RDA5816S_IIC_Write(context, 0x7c,0xAB);

  /* th2=1580M   */
  RDA5816S_IIC_Write(context, 0x72,0x07);  /* v1.2, RDA_LiuYL  2012-11-20 */
  RDA5816S_IIC_Write(context, 0x73,0x40);  /* v1.2, RDA_LiuYL  2012-11-20 */
  RDA5816S_IIC_Write(context, 0x74,0x74);  /* v1.2, RDA_LiuYL  2012-11-20 */

  /* agc setting */
  RDA5816S_IIC_Write(context, 0x4f,0x40);
  RDA5816S_IIC_Write(context, 0x5b,0x20);

  /*  for blocker */
  RDA5816S_IIC_Write(context, 0x16,0x10);/* stage setting */
  RDA5816S_IIC_Write(context, 0x18,0x20);
  RDA5816S_IIC_Write(context, 0x30,0x30);
  RDA5816S_IIC_Write(context, 0x5c,0x30);
  RDA5816S_IIC_Write(context, 0x6c,0x30);
  RDA5816S_IIC_Write(context, 0x6e,0x70);
  RDA5816S_IIC_Write(context, 0x1b,0xB2);
  RDA5816S_IIC_Write(context, 0x1d,0xB2);
  RDA5816S_IIC_Write(context, 0x1f,0xB2);
  RDA5816S_IIC_Write(context, 0x21,0xB2);
  RDA5816S_IIC_Write(context, 0x23,0xB6);
  RDA5816S_IIC_Write(context, 0x25,0xB6);
  RDA5816S_IIC_Write(context, 0x27,0xBA);
  RDA5816S_IIC_Write(context, 0x29,0xBF);
  RDA5816S_IIC_Write(context, 0xb3,0xFF);
  RDA5816S_IIC_Write(context, 0xb5,0xFF);

  RDA5816S_IIC_Write(context, 0x17,0xF0);
  RDA5816S_IIC_Write(context, 0x19,0xF0);
  RDA5816S_IIC_Write(context, 0x31,0xF0);
  RDA5816S_IIC_Write(context, 0x5d,0xF1);
  RDA5816S_IIC_Write(context, 0x6d,0xF2);
  RDA5816S_IIC_Write(context, 0x6f,0xF2);
  RDA5816S_IIC_Write(context, 0x1c,0x31);
  RDA5816S_IIC_Write(context, 0x1e,0x72);
  RDA5816S_IIC_Write(context, 0x20,0x96);
  RDA5816S_IIC_Write(context, 0x22,0xBA);
  RDA5816S_IIC_Write(context, 0x24,0xBA);
  RDA5816S_IIC_Write(context, 0x26,0xBE);
  RDA5816S_IIC_Write(context, 0x28,0xCE);
  RDA5816S_IIC_Write(context, 0x2a,0xDE);
  RDA5816S_IIC_Write(context, 0xb4,0x0F);
  RDA5816S_IIC_Write(context, 0xb6,0x0F);

  RDA5816S_IIC_Write(context, 0xb7,0x10);  /* start    */
  RDA5816S_IIC_Write(context, 0xb9,0x10);
  RDA5816S_IIC_Write(context, 0xbb,0x00);
  RDA5816S_IIC_Write(context, 0xbd,0x00);
  RDA5816S_IIC_Write(context, 0xbf,0x00);
  RDA5816S_IIC_Write(context, 0xc1,0x10);
  RDA5816S_IIC_Write(context, 0xc3,0x10);
  RDA5816S_IIC_Write(context, 0xc5,0x10);
  RDA5816S_IIC_Write(context, 0xa3,0x19);
  RDA5816S_IIC_Write(context, 0xa5,0x2E);
  RDA5816S_IIC_Write(context, 0xa7,0x37);
  RDA5816S_IIC_Write(context, 0xa9,0x47);
  RDA5816S_IIC_Write(context, 0xab,0x5E);  /* v1.1, modify by rda 2012.7.30  */
  RDA5816S_IIC_Write(context, 0xad,0x3F);
  RDA5816S_IIC_Write(context, 0xaf,0x00);
  RDA5816S_IIC_Write(context, 0xb1,0x95);  /* v1.0, modify by rda 2012.1.12  */


  RDA5816S_IIC_Write(context, 0xb8,0x47); /* end      */
  RDA5816S_IIC_Write(context, 0xba,0x3F);
  RDA5816S_IIC_Write(context, 0xbc,0x37);
  RDA5816S_IIC_Write(context, 0xbe,0x3F);
  RDA5816S_IIC_Write(context, 0xc0,0x3F);
  RDA5816S_IIC_Write(context, 0xc2,0x3F);
  RDA5816S_IIC_Write(context, 0xc4,0x3F);
  RDA5816S_IIC_Write(context, 0xc6,0x3F);
  RDA5816S_IIC_Write(context, 0xa4,0x47);
  RDA5816S_IIC_Write(context, 0xa6,0x57);
  RDA5816S_IIC_Write(context, 0xa8,0x5F);
  RDA5816S_IIC_Write(context, 0xaa,0x70);
  RDA5816S_IIC_Write(context, 0xac,0x70);
  RDA5816S_IIC_Write(context, 0xae,0x68);
  RDA5816S_IIC_Write(context, 0xb0,0x95); /*  v1.0, modify by rda 2012.1.12              */
  RDA5816S_IIC_Write(context, 0xb2,0x95); /*  v1.0, modify by rda 2012.1.12              */


  RDA5816S_IIC_Write(context, 0x81,0x77);  /* rise     */
  RDA5816S_IIC_Write(context, 0x82,0x54);  /* v1.1, modify by rda 2012.7.30          */
  RDA5816S_IIC_Write(context, 0x83,0x70);
  RDA5816S_IIC_Write(context, 0x84,0x68);
  RDA5816S_IIC_Write(context, 0x85,0x3F);  /* v1.1, modify by rda 2012.7.30          */
  RDA5816S_IIC_Write(context, 0x86,0x42);  /* v1.1, modify by rda 2012.7.30          */
  RDA5816S_IIC_Write(context, 0x87,0x70);
  RDA5816S_IIC_Write(context, 0x88,0x47);
  RDA5816S_IIC_Write(context, 0x89,0x68);
  RDA5816S_IIC_Write(context, 0x8a,0x8E);
  RDA5816S_IIC_Write(context, 0x8b,0x8E);
  RDA5816S_IIC_Write(context, 0x8c,0x70);  /* v1.1, modify by rda 2012.7.30          */
  RDA5816S_IIC_Write(context, 0x8d,0x9C);
  RDA5816S_IIC_Write(context, 0x8e,0xe0);  /* v1.0, modify by rda 2012.1.12          */
  RDA5816S_IIC_Write(context, 0x8f,0x95);  /* v1.0, modify by rda 2012.1.12          */

  RDA5816S_IIC_Write(context, 0x90,0x00);  /* fall     */
  RDA5816S_IIC_Write(context, 0x91,0x00);
  RDA5816S_IIC_Write(context, 0x92,0x00);
  RDA5816S_IIC_Write(context, 0x93,0x00);
  RDA5816S_IIC_Write(context, 0x94,0x00);
  RDA5816S_IIC_Write(context, 0x95,0x00);
  RDA5816S_IIC_Write(context, 0x96,0x00);
  RDA5816S_IIC_Write(context, 0x97,0x00);
  RDA5816S_IIC_Write(context, 0x98,0x00);
  RDA5816S_IIC_Write(context, 0x99,0x00);
  RDA5816S_IIC_Write(context, 0x9a,0x10);
  RDA5816S_IIC_Write(context, 0x9b,0x24);
  RDA5816S_IIC_Write(context, 0x9c,0x10);
  RDA5816S_IIC_Write(context, 0x9d,0x00);
  RDA5816S_IIC_Write(context, 0x9e,0x00);

  RDA5816Sleep(10);/* Wait 10ms;*/
  /*enable both channels*/
  RDA5816S_IIC_Write(context, 0x04,0x85);
  context->i2c->address = context->i2c->address^0x02;
  RDA5816S_IIC_Read (context, 0x04, &temp);
  temp |= 0x80;
  RDA5816S_IIC_Write(context, 0x04,  temp);    /*Enable the other channel*/
  context->i2c->address = context->i2c->address^0x02;
  RDA5816Sleep(10); /*Wait 10ms;*/

}
/*************************************************************************
  Function to Set the RDA5816S
  fPLL:   Frequency              unit: MHz  from  250 to  2300
  fSym:   SymbolRate             unit: KS/s from 1000 to 45000
*************************************************************************/
long          RDA5816S_Set                   (RDA5816S_Context *context, long fPLL_MHz, long lpf_MHz) {
  unsigned char buffer;
  unsigned long temp_value     = 0;
  unsigned char Filter_bw_control_bit;
  unsigned int  vco_bit_buff_1 = 0, vco_bit_buff_2 = 0;
  unsigned char vco_dr;

  RDA5816S_IIC_Read (context, 0x41, &vco_dr);
  RDA5816S_IIC_Write(context, 0x41, (vco_dr & 0xfb));    /* disable vco_bit_dr*/

  RDA5816S_IIC_Write(context, 0x04,0xc1);    /*disable RXON*/

  /*  set Filter bandwidth start */
  Filter_bw_control_bit = (unsigned char)(lpf_MHz);
  if(Filter_bw_control_bit<4)
  Filter_bw_control_bit = 4;    /* MHz*/
  else if(Filter_bw_control_bit>40)
  Filter_bw_control_bit = 40;   /* MHz*/    /*modify by rda 2012.1.12   */

  Filter_bw_control_bit &= 0x3f;
  Filter_bw_control_bit |= 0x40;

  RDA5816S_IIC_Write(context, 0x0b,Filter_bw_control_bit);
  /*  set Filter bandwidth end   */

  SiTRACE("fPLL_MHz %ld, lpf_MHz %ld\n", fPLL_MHz, lpf_MHz);
  /* set frequency start */
  /* get vco_bit value to vco_bit_buff_1, start*/
  temp_value = (unsigned long)(fPLL_MHz*2097152.0/27);
/* ((2<<21) / RDA5816_XTALFREQ); */

  SiTRACE("fPLL_MHz %ld, temp_value %ld 0x%08x\n", fPLL_MHz, temp_value, temp_value);

  buffer = ((unsigned char)((temp_value>>24)&0xff));
  RDA5816S_IIC_Write(context, 0x07,buffer);
  buffer = ((unsigned char)((temp_value>>16)&0xff));
  RDA5816S_IIC_Write(context, 0x08,buffer);
  buffer = ((unsigned char)((temp_value>> 8)&0xff));
  RDA5816S_IIC_Write(context, 0x09,buffer);
  buffer = ((unsigned char)( temp_value&0xff));
  RDA5816S_IIC_Write(context, 0x0a,buffer);

  RDA5816S_IIC_Write(context, 0x04,0xC3);    /* enable RXON*/

  RDA5816S_IIC_Read (context,0x50, &buffer);
  vco_bit_buff_1 = (unsigned int)buffer & 0xff;
  RDA5816S_IIC_Read (context,0x51, &buffer);
  vco_bit_buff_1 = ((vco_bit_buff_1<<8) & 0xff00) | ((unsigned int)buffer & 0xff);

  RDA5816S_IIC_Write(context, 0x04,0xC1);    /* disable RXON*/
  /* get vco_bit value to vco_bit_buff_1, end*/

  /* get vco_bit value to vco_bit_buff_2, start*/
  temp_value = (unsigned long)fPLL_MHz* 77672;/*((2<<21) / RDA5816S_XTALFREQ);*/
  buffer = ((unsigned char)((temp_value>>24)&0xff));
  RDA5816S_IIC_Write(context, 0x07,buffer);
  buffer = ((unsigned char)((temp_value>>16)&0xff));
  RDA5816S_IIC_Write(context, 0x08,buffer);
     buffer = ((unsigned char)((temp_value>>8)&0xff));
  RDA5816S_IIC_Write(context, 0x09,buffer);
     buffer = ((unsigned char)( temp_value&0xff));
  RDA5816S_IIC_Write(context, 0x0a,buffer);
  /*set frequency end*/

  RDA5816S_IIC_Write(context, 0x04,0xC3);    /* enable RXON  */

  RDA5816S_IIC_Read (context,0x50, &buffer);
  vco_bit_buff_2 = (unsigned int)buffer & 0xff;
  RDA5816S_IIC_Read (context,0x51, &buffer);
  vco_bit_buff_2 = ((vco_bit_buff_2<<8) & 0xff00) | ((unsigned int)buffer & 0xff);
  /* get vco_bit value to vco_bit_buff_2, end*/

  if((vco_bit_buff_2 & 0xffc0)==(vco_bit_buff_1 & 0xffc0))
  {
    vco_bit_buff_2 = vco_bit_buff_2 + 0x40;    /* vco_bit + 1*/
    buffer = ((unsigned char)((vco_bit_buff_2>>8)&0xff));
    RDA5816S_IIC_Write(context, 0x50,buffer);
    buffer = ((unsigned char)(vco_bit_buff_2&0xff));
    RDA5816S_IIC_Write(context, 0x51,buffer);

    RDA5816S_IIC_Read (context,0x41,&vco_dr);
    RDA5816S_IIC_Write(context, 0x41,(vco_dr | 0x04));    /* enable vco_bit_dr*/

    if(RDA5816s_GetLockStatus(context) == 1)  /* Tuner Unlock*/
    {
      RDA5816S_IIC_Write(context, 0x41,(vco_dr & 0xfb));  /*disable vco_bit_dr*/
    }

  }

  RDA5816Sleep(5);/*Wait 5ms;*/
  context->RF = fPLL_MHz*1000;

  return 0;
}

void          L1_RF_RDA5816S_Init            (RDA5816S_Context *context, unsigned int add) {
    SiTRACE_X("RDA5816S_Init starting...\n");
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
    SiTRACE_X("L1_RF_RDA5816S_Init complete...\n");
}
int           L1_RF_RDA5816S_InitAfterReset  (RDA5816S_Context *context) {
  SiTRACE("L1_RF_RDA5816S_InitAfterReset starting...\n");
  RDA5816S_Initialize(context);
  SiTRACE("L1_RF_RDA5816S_InitAfterReset complete...\n");
  return 0;
}
int           L1_RF_RDA5816S_Get_RF          (RDA5816S_Context *context) {
   return context->RF;
}
int           L1_RF_RDA5816S_Tune            (RDA5816S_Context *context, int rf_kHz      ) {
   /* Checking limits */
   if (rf_kHz < (context->minRF)) {
     SiERROR("RDA5816S rf_kHz < minRF \n");
     SiTRACE("rf_kHz %d < minRF %d\n",rf_kHz,context->minRF); return L1_RF_RDA5816S_Tune(context, context->minRF);
   }
   if (rf_kHz > (context->maxRF)) {
     SiERROR("RDA5816S rf_kHz > maxRF \n");
     SiTRACE("rf_kHz %d > maxRF %d\n",rf_kHz,context->maxRF); return L1_RF_RDA5816S_Tune(context, context->maxRF);
   }
   context->RF = rf_kHz;
   context->i2c->trackRead = context->i2c->trackWrite;
   RDA5816S_Set(context, (context->RF + 500)/1000.0, context->LPF/1000.0);
   return context->RF;
}
int           L1_RF_RDA5816S_LPF             (RDA5816S_Context *context, int lpf_khz     ) {
  if (lpf_khz != 0) { /* use '0' to retrieve the current value */
    if ((lpf_khz > 45000)) {
      SiTRACE("RDA5816S requested lpf_khz %d higher than max, set to max\n", lpf_khz);
      lpf_khz = 45000;
    }
    if ((lpf_khz < 4000)) {
      SiTRACE("RDA5816S requested lpf_khz %d smaller than min, set to min\n", lpf_khz);
      lpf_khz = 4000;
    }
    context->LPF = (int)((lpf_khz + 500.0));
  }

  SiTRACE("RDA5816S lpf %d kHz\n", context->LPF);

  RDA5816S_Set(context, (context->RF + 500)/1000.0, context->LPF/1000.0);
  return context->LPF;
}
int           L1_RF_RDA5816S_RSSI            (RDA5816S_Context *context, int other_gain  ) {
/* Gain stage limits
                                             filter-..
                                               i2v--..
                                           post.. --..
                                          st2--.. --..
                                       pre.. --.. --..
                                     st1--.. --.. --..    */
#define RDA5816S_Gain_Stage__0 0x001 /* '0000 0000 0001' */
#define RDA5816S_Gain_Stage__1 0x002 /* '0000 0000 0010' */
#define RDA5816S_Gain_Stage__2 0x003 /* '0000 0000 0011' */
#define RDA5816S_Gain_Stage__3 0x013 /* '0000 0001 0011' */
#define RDA5816S_Gain_Stage__4 0x023 /* '0000 0010 0011' */
#define RDA5816S_Gain_Stage__5 0x027 /* '0000 0010 0111' */
#define RDA5816S_Gain_Stage__6 0x09b /* '0000 1001 1011' */
#define RDA5816S_Gain_Stage__7 0x0ab /* '0000 1010 1011' */
#define RDA5816S_Gain_Stage__8 0x1ab /* '0001 1010 1011' */
#define RDA5816S_Gain_Stage__9 0x2ab /* '0010 1010 1011' */
#define RDA5816S_Gain_Stage_10 0x6ab /* '0110 1010 1011' */
#define RDA5816S_Gain_Stage_11 0x7ab /* '0111 1010 1011' */
#define RDA5816S_Gain_Stage_12 0xbab /* '1011 1010 1011' */
#define RDA5816S_Gain_Stage_13 0xfeb /* '1111 1110 1011' */
#define RDA5816S_Gain_Stage_14 0xfff /* '1111 1111 1111' */
#define RDA5816S_Gain_Stage_15 0xfff /* '1111 1111 1111' */

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

  RDA5816S_IIC_Read(context, 0x16, &data16);
  i2v    = (data16&0xc0)>>6;
  filter = (data16&0x30)>>4;
  st1    = (data16&0x0c)>>2;
  st2    = (data16&0x03)>>0;

  RDA5816S_IIC_Read(context, 0x17, &data17);
  pre    = (data17&0x0c)>>2;
  post   = (data17&0x03)>>0;

  stage_code = (st1<<10) + (pre<<8) + (st2<<6) + (post<<4) + (i2v<<2) + (filter<<0);

       if (stage_code >= RDA5816S_Gain_Stage_14 ) { gain_stage = 14; }
  else if (stage_code >= RDA5816S_Gain_Stage_13 ) { gain_stage = 13; }
  else if (stage_code >= RDA5816S_Gain_Stage_12 ) { gain_stage = 12; }
  else if (stage_code >= RDA5816S_Gain_Stage_11 ) { gain_stage = 11; }
  else if (stage_code >= RDA5816S_Gain_Stage_10 ) { gain_stage = 10; }
  else if (stage_code >= RDA5816S_Gain_Stage__9 ) { gain_stage =  9; }
  else if (stage_code >= RDA5816S_Gain_Stage__8 ) { gain_stage =  8; }
  else if (stage_code >= RDA5816S_Gain_Stage__7 ) { gain_stage =  7; }
  else if (stage_code >= RDA5816S_Gain_Stage__6 ) { gain_stage =  6; }
  else if (stage_code >= RDA5816S_Gain_Stage__5 ) { gain_stage =  5; }
  else if (stage_code >= RDA5816S_Gain_Stage__4 ) { gain_stage =  4; }
  else if (stage_code >= RDA5816S_Gain_Stage__3 ) { gain_stage =  3; }
  else if (stage_code >= RDA5816S_Gain_Stage__2 ) { gain_stage =  2; }
  else if (stage_code >= RDA5816S_Gain_Stage__1 ) { gain_stage =  1; }
  else                                            { gain_stage =  0; }

       if (context->RF >= 1990000) { band = 6; }
  else if (context->RF >= 1660000) { band = 5; }
  else if (context->RF >= 1450000) { band = 4; }
  else if (context->RF >= 1280000) { band = 3; }
  else if (context->RF >= 1090000) { band = 2; }
  else                             { band = 1; }

  RDA5816S_IIC_Read(context, 0xb7, &vga);
  vga_gain = vga*30.0/255;

  total_gain = gain[band-1][gain_stage] + vga_gain;

  if (0) {
    SiTRACE("RDA5816S stage_code %02x%02x %02x%02x %02x%02x -> stage_code 0x%06x\n", st1, pre, st2, post, i2v, filter, stage_code);
    SiTRACE("RDA5816S st1 %d, pre %d, st2 %d, post %d, i2v %d, filter %d -> stage_code 0x%06x -> gain_stage %d\n", st1, pre, st2, post, i2v, filter, stage_code, gain_stage);
    SiTRACE("RDA5816S vga %d -> vga_gain %f\n", vga, vga_gain);
    SiTRACE("RDA5816S RSSI = gain[%d][%d] + vga_gain = %f + %f = %f\n", band-1, gain_stage, gain[band-1][gain_stage], vga_gain, total_gain);
  }

  return  other_gain-total_gain;
}
unsigned char L1_RF_RDA5816S_Wakeup          (RDA5816S_Context *context) {
  unsigned char temp;
  SiTRACE("L1_RF_RDA5816S_Wakeup starting...\n");

  RDA5816S_IIC_Read (context, 0x04, &temp);
  temp = temp | 0x80;
  RDA5816S_IIC_Write(context, 0x04,temp);

  SiTRACE("L1_RF_RDA5816S_Wakeup done\n");
  return 0;
}
unsigned char L1_RF_RDA5816S_Standby         (RDA5816S_Context *context) {
  unsigned char temp;
  SiTRACE("L1_RF_RDA5816S_Standby starting...\n");

  RDA5816S_IIC_Read (context, 0x04, &temp);
  temp = temp & 0x7F;
  RDA5816S_IIC_Write(context, 0x04,temp);

  SiTRACE("L1_RF_RDA5816S_Standby done\n");
  return 0;
}
char*         L1_RF_RDA5816S_TAG_TEXT        (void) { return (char *)"RDA5816s_16110d_v2.4"; }
