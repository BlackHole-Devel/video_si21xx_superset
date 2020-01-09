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
/*                     SILEMBIA Layer 1  SAT RF Tuner RDA16110E / RDA16110SW functions                       */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains all API functions for the RDA16110E / RDA16110SW SAT Tuners on the RF board   */
/*     All included functions can be accessed by the higher software level as imports                        */
/*     All RDA16110E functions are declared in Silabs_L1_RF_RDA16110E_API.h                                  */
/*************************************************************************************************************/
/* Change log:

  As from SVN6649: AGC settings and RSSI update from (Rui Cao) <ruicao@rdamicro.com>

  As from SVN6607: changing context->maxRF = 2350000;

   Initial version: UNTESTED driver
    L1_RF_RDA16110E_RSSI    not working! (inherited from RDA5816S driver, not reworked by RDA yet)
    L1_RF_RDA16110E_Wakeup  not tested   (inherited from RDA5816S driver, not checked)
    L1_RF_RDA16110E_Standby not tested   (inherited from RDA5816S driver, not checked)

*************************************************************************************************************/
/* RDA change log:
Filename:      RDA16110e_3.6.4b_dvbs.c
Description:    RDA16110e - Digital Satellite Tuner IC driver.

==  Unpdate History  ==
version 1.0    The primary version,  created by Hongxin Wang
            2011-2-22
version 2.0    For B version chip ,  created by Hongxin Wang
            2011-5-27
version 2.1    Add register 0x1a for improving the sensitivity of 1550MHz .
            2011- -
version 2.2    Modify register 0x4a and 0x4b in initial both from 0xbb to 0x88 for improving pll stability .
            2011-06-08
version 2.3    Add register 0x3c in initial for enhance the max level .
            2011-08-11
version 3.1    Modify value of register 0x06 from 0x88 to 0xa8 for enlarge the vco level ;
            Modify value of register 0x4a from 0x88 to 0x48 for decrease presc_1 ;
            Modify value of register 0x4b from 0x88 to 0x58 for decrease presc_3 ;
            Modify value of register 0x15 from 0xaa to 0xae for enlarge buf_ibit_1 ;
            Modify value of register 0x72 from 0x60 to 0x20 and modify value of register 0x73 from 0x76 to 0x72  for change the  pll_sel_vco_freq_th from 1606MHz to 1552MHz ;
            All the change is for pll stability and is necessary.
            2011-10-28
version 3.2    Modify value of register 0x57 from 0x74 to 0x64 for reducing ctsdm_gain2 from 10 to 00 ;
            Modify value of register 0x65 from 0x80 to 0x00 for reducing DC offset ;
            Add register 0x41 in initial  for setting dc_cal_clk to 11 ;
            Both above change is use to enhance the stability of DC .
            2011-12-27
version 3.3    Modify value of register 0x8e from 0x9a to 0xe0 ;
            Modify value of register 0x8f from  0x37 to 0x95 ;
            Modify value of register 0xb0 from 0x37 to 0x95 ;
            Modify value of register 0xb1 from 0x37 to 0x95 ;
            Modify value of register 0xb2 from 0x37 to 0x95 ;
            Both above change is use to enlarge the gain 12dB ;
            Modify the max bandwidth from 45MHz to 40MHz ;
            Add register 0x2b in the rda16110eet  for  improving the pll stability .
            2012-1-12
version 3.4    Modify value of register 0x38 from 0x90 to 0x93 for improving the high temperature performance .
            2012-4-17
version 3.5    Modify value of register 0x4a from 0x48 to 0x68 for enhance pll stability ;
            Modify value of register 0x4b from 0x58 to 0x78 for enhance pll stability .
            2012-7-18
version 3.6    Modify value of register 0x06 from 0xA8 to 0xF8 for enhance pll stability .
            2012-8-10
version 3.6.1    Optimize bandwidth calculation code.
            Add configuration for Xtal = 4MHz, 13.5MHz, 24MHz and 30MHz.
            2013-8-22, by Yilei LIU
version 3.6.2    Optimize bandwidth calculation code.
            2013-11-20, by Yilei LIU
version 3.6.3    Correct a bandwith unit fault. (KSps to MSps)
version 3.6.4           Add RSSI
                                    2015-11-09,by Rui Cao
version 3.6.4b           Set st1pre=1111,specially loopout max for European customer,temporary version
                                    2015-12-11,by Xiaofei Peng
*/
/* TAG RDA16110E SVN6649     */
/*#define RWTRACES */

#define   SiLEVEL          1
#define   SiTAG            context->i2c->tag
#include "SiLabs_L1_RF_RDA16110E_API.h"

#define RDA16110E_Sleep system_wait

int           RDA16110E_Communication_Check   (RDA16110E_Context *context) {
  unsigned char byteBuffer[5];
    if (L0_ReadCommandBytes(context->i2c, 5, byteBuffer) != 5) {
      SiTRACE("RDA16110E_Communication_Check ERROR reading 5 bytes 0!\n");
      printf ("RDA16110E_Communication_Check ERROR reading 5 bytes 0!\n");
    /*system("pause");*/
      return 0;
    }
    if (byteBuffer[0] == 0xff) {
      SiTRACE("RDA16110E_Communication_Check ERROR: first byte 0xff!\n");
      return 0;
    }
    if (byteBuffer[0] == 0x00) {
      SiTRACE("RDA16110E_Communication_Check ERROR: first byte 0x00!\n");
      return 0;
    }
  return 1;
}
void          RDA16110E_IIC_Write             (RDA16110E_Context *context, unsigned char write_index, unsigned char  value) {
  context->bytes[0] = value;
  L0_WriteBytes (context->i2c, write_index, 1, context->bytes);
}
void          RDA16110E_IIC_Read              (RDA16110E_Context *context, unsigned char read_index , unsigned char *value) {
  L0_ReadBytes (context->i2c, read_index, 1, value);
}
void          RDA16110E_Initialize            (RDA16110E_Context *context) {

  RDA16110E_Sleep(1);    /* Wait 1ms. */
  /* Chip register soft reset   */
  RDA16110E_IIC_Write(context, 0x04,0x04);
  RDA16110E_IIC_Write(context, 0x04,0x05);

  /* Initial configuration start */

  /* pll setting */
  RDA16110E_IIC_Write(context, 0x1a,0x13);    /* add by rda 2011.5.28     */
  RDA16110E_IIC_Write(context, 0x41,0x53);    /* add by rda 2011.12.27    */
  RDA16110E_IIC_Write(context, 0x38,0x93);    /* modify by rda 2012.04.17 */
  RDA16110E_IIC_Write(context, 0x39,0x15);
  RDA16110E_IIC_Write(context, 0x3A,0x00);
  RDA16110E_IIC_Write(context, 0x3B,0x00);
  RDA16110E_IIC_Write(context, 0x3C,0x0c);    /* add by rda 2011.8.9 */
  RDA16110E_IIC_Write(context, 0x0c,0xE2);
  RDA16110E_IIC_Write(context, 0x2e,0x6F);

if (context->xtal == 27) {
  RDA16110E_IIC_Write(context, 0x72,0x07);      /* 1552~1553 */
  RDA16110E_IIC_Write(context, 0x73,0x20);
  RDA16110E_IIC_Write(context, 0x74,0x72);
  RDA16110E_IIC_Write(context, 0x75,0x06);      /* 1363~1364, 1862~1863 */
  RDA16110E_IIC_Write(context, 0x76,0x40);
  RDA16110E_IIC_Write(context, 0x77,0x89);
  RDA16110E_IIC_Write(context, 0x79,0x04);      /* 1075 */
  RDA16110E_IIC_Write(context, 0x7A,0xFA);
  RDA16110E_IIC_Write(context, 0x7B,0x12);
  RDA16110E_IIC_Write(context, 0x7C,0xF7);
}
if (context->xtal == 4) {
  RDA16110E_IIC_Write(context, 0x72,0x30);      /* v3.6.1, 1551~1552 */
  RDA16110E_IIC_Write(context, 0x73,0x73);
  RDA16110E_IIC_Write(context, 0x74,0x07);
  RDA16110E_IIC_Write(context, 0x75,0x2A);    /* v3.6.1, 1363~1364, 1863~1864 */
  RDA16110E_IIC_Write(context, 0x76,0x93);
  RDA16110E_IIC_Write(context, 0x77,0xA3);
  RDA16110E_IIC_Write(context, 0x79,0x21);      /* v3.6.1, 1075 */
  RDA16110E_IIC_Write(context, 0x7A,0x98);
  RDA16110E_IIC_Write(context, 0x7B,0x00);
  RDA16110E_IIC_Write(context, 0x7C,0x00);
}
if (context->xtal == 135) {
  RDA16110E_IIC_Write(context, 0x72,0x0E);      /* v3.6.1, 1552~1553 */
  RDA16110E_IIC_Write(context, 0x73,0x50);
  RDA16110E_IIC_Write(context, 0x74,0xE5);
  RDA16110E_IIC_Write(context, 0x75,0x0C);    /* v3.6.1, 1363~1364, 1862~1863 */
  RDA16110E_IIC_Write(context, 0x76,0x91);
  RDA16110E_IIC_Write(context, 0x77,0x13);
  RDA16110E_IIC_Write(context, 0x79,0x09);      /* v3.6.1, 1075 */
  RDA16110E_IIC_Write(context, 0x7A,0xF4);
  RDA16110E_IIC_Write(context, 0x7B,0x25);
  RDA16110E_IIC_Write(context, 0x7C,0xED);
}
if (context->xtal == 24) {
  RDA16110E_IIC_Write(context, 0x72,0x08);      /* v3.6.1, 1547~1548 */
  RDA16110E_IIC_Write(context, 0x73,0x00);
  RDA16110E_IIC_Write(context, 0x74,0x80);
  RDA16110E_IIC_Write(context, 0x75,0x07);      /* v3.6.1, 1367~1368, 1859~1860 */
  RDA16110E_IIC_Write(context, 0x76,0x10);
  RDA16110E_IIC_Write(context, 0x77,0x9A);
  RDA16110E_IIC_Write(context, 0x79,0x05);      /* v3.6.1, 1075 */
  RDA16110E_IIC_Write(context, 0x7A,0x99);
  RDA16110E_IIC_Write(context, 0x7B,0x55);
  RDA16110E_IIC_Write(context, 0x7C,0x55);
}
if (context->xtal == 30) {
  RDA16110E_IIC_Write(context, 0x72,0x06);      /* v3.6.1, 1552~1553 */
  RDA16110E_IIC_Write(context, 0x73,0x60);
  RDA16110E_IIC_Write(context, 0x74,0x66);
  RDA16110E_IIC_Write(context, 0x75,0x05);    /* v3.6.1, 1363~1364, 1862~1863 */
  RDA16110E_IIC_Write(context, 0x76,0xA0);
  RDA16110E_IIC_Write(context, 0x77,0x7B);
  RDA16110E_IIC_Write(context, 0x79,0x04);      /* v3.6.1, 1075 */
  RDA16110E_IIC_Write(context, 0x7A,0x7A);
  RDA16110E_IIC_Write(context, 0x7B,0xAA);
  RDA16110E_IIC_Write(context, 0x7C,0xAA);
}

  RDA16110E_IIC_Write(context, 0x5b,0x20);
  RDA16110E_IIC_Write(context, 0x2f,0x57);
  RDA16110E_IIC_Write(context, 0x0d,0x70);
  RDA16110E_IIC_Write(context, 0x16,0x03);
  RDA16110E_IIC_Write(context, 0x18,0x4B);
  RDA16110E_IIC_Write(context, 0x30,0xFF);
  RDA16110E_IIC_Write(context, 0x5c,0xFF);
  RDA16110E_IIC_Write(context, 0x6c,0xFF);
  RDA16110E_IIC_Write(context, 0x6e,0xFF);
  RDA16110E_IIC_Write(context, 0x65,0x00);    /* modify by rda 2011.12.27 */
  RDA16110E_IIC_Write(context, 0x70,0x3F);
  RDA16110E_IIC_Write(context, 0x71,0x3F);
  RDA16110E_IIC_Write(context, 0x53,0xA8);
  RDA16110E_IIC_Write(context, 0x46,0x21);
  RDA16110E_IIC_Write(context, 0x47,0x84);
  RDA16110E_IIC_Write(context, 0x48,0x10);
  RDA16110E_IIC_Write(context, 0x49,0x08);
  RDA16110E_IIC_Write(context, 0x60,0x80);
  RDA16110E_IIC_Write(context, 0x61,0x80);
  RDA16110E_IIC_Write(context, 0x6A,0x08);
  RDA16110E_IIC_Write(context, 0x6B,0x63);
  RDA16110E_IIC_Write(context, 0x69,0xF8);
  RDA16110E_IIC_Write(context, 0x57,0x64);    /* modify by rda 2011.12.27 */
  RDA16110E_IIC_Write(context, 0x05,0x88);
  RDA16110E_IIC_Write(context, 0x06,0xF8);    /* modify by rda 2012.8.10  */
  RDA16110E_IIC_Write(context, 0x15,0xAE);    /* modify by rda 2011.10.28 */
  RDA16110E_IIC_Write(context, 0x4a,0x68);    /* modify by rda 2012.7.18  */
  RDA16110E_IIC_Write(context, 0x4b,0x78);    /* modify by rda 2012.7.18  */

  /* agc setting */
  RDA16110E_IIC_Write(context, 0x4f,0x40);
  RDA16110E_IIC_Write(context, 0x5b,0x20);

  /*  for blocker */
  RDA16110E_IIC_Write(context, 0x16,0x10);/* stage setting */
  RDA16110E_IIC_Write(context, 0x18,0x20);
  RDA16110E_IIC_Write(context, 0x30,0x30);
  RDA16110E_IIC_Write(context, 0x5c,0x30);
  RDA16110E_IIC_Write(context, 0x6c,0x30);
  RDA16110E_IIC_Write(context, 0x6e,0x70);
  RDA16110E_IIC_Write(context, 0x1b,0xB2);
  RDA16110E_IIC_Write(context, 0x1d,0xB2);
  RDA16110E_IIC_Write(context, 0x1f,0xB2);
  RDA16110E_IIC_Write(context, 0x21,0xB2);
  RDA16110E_IIC_Write(context, 0x23,0xB6);
  RDA16110E_IIC_Write(context, 0x25,0xB6);
  RDA16110E_IIC_Write(context, 0x27,0xBA);
  RDA16110E_IIC_Write(context, 0x29,0xBF);
  RDA16110E_IIC_Write(context, 0xb3,0xFF);
  RDA16110E_IIC_Write(context, 0xb5,0xFF);

  RDA16110E_IIC_Write(context, 0x17,0xF0);
  RDA16110E_IIC_Write(context, 0x19,0xF0);
  RDA16110E_IIC_Write(context, 0x31,0xF0);
  RDA16110E_IIC_Write(context, 0x5d,0xF1);
  RDA16110E_IIC_Write(context, 0x6d,0xF2);
  RDA16110E_IIC_Write(context, 0x6f,0xF2);
  RDA16110E_IIC_Write(context, 0x1c,0x31);
  RDA16110E_IIC_Write(context, 0x1e,0x72);
  RDA16110E_IIC_Write(context, 0x20,0x96);
  RDA16110E_IIC_Write(context, 0x22,0xBA);
  RDA16110E_IIC_Write(context, 0x24,0xBA);
  RDA16110E_IIC_Write(context, 0x26,0xBE);
  RDA16110E_IIC_Write(context, 0x28,0xCE);
  RDA16110E_IIC_Write(context, 0x2a,0xDE);
  RDA16110E_IIC_Write(context, 0xb4,0x0F);
  RDA16110E_IIC_Write(context, 0xb6,0x0F);

  RDA16110E_IIC_Write(context, 0xb7,0x47); /* start     */
  RDA16110E_IIC_Write(context, 0xb9,0x47);
  RDA16110E_IIC_Write(context, 0xbb,0x3F);
  RDA16110E_IIC_Write(context, 0xbd,0x3F);
  RDA16110E_IIC_Write(context, 0xbf,0x3F);
  RDA16110E_IIC_Write(context, 0xc1,0x47);
  RDA16110E_IIC_Write(context, 0xc3,0x47);
  RDA16110E_IIC_Write(context, 0xc5,0x47);
  RDA16110E_IIC_Write(context, 0xa3,0x4f);
  RDA16110E_IIC_Write(context, 0xa5,0x5F);
  RDA16110E_IIC_Write(context, 0xa7,0x68);
  RDA16110E_IIC_Write(context, 0xa9,0x77);
  RDA16110E_IIC_Write(context, 0xab,0x77);
  RDA16110E_IIC_Write(context, 0xad,0x70);
  RDA16110E_IIC_Write(context, 0xaf,0x3F);
  RDA16110E_IIC_Write(context, 0xb1,0x70);


  RDA16110E_IIC_Write(context, 0xb8,0x77); /* end       */
  RDA16110E_IIC_Write(context, 0xba,0x70);
  RDA16110E_IIC_Write(context, 0xbc,0x68);
  RDA16110E_IIC_Write(context, 0xbe,0x70);
  RDA16110E_IIC_Write(context, 0xc0,0x70);
  RDA16110E_IIC_Write(context, 0xc2,0x70);
  RDA16110E_IIC_Write(context, 0xc4,0x70);
  RDA16110E_IIC_Write(context, 0xc6,0x70);
  RDA16110E_IIC_Write(context, 0xa4,0x77);
  RDA16110E_IIC_Write(context, 0xa6,0x87);
  RDA16110E_IIC_Write(context, 0xa8,0x8E);
  RDA16110E_IIC_Write(context, 0xaa,0x9b);
  RDA16110E_IIC_Write(context, 0xac,0x9b);
  RDA16110E_IIC_Write(context, 0xae,0x95);
  RDA16110E_IIC_Write(context, 0xb0,0x70);
  RDA16110E_IIC_Write(context, 0xb2,0x95);


  RDA16110E_IIC_Write(context, 0x81,0xa2); /* rise      */
  RDA16110E_IIC_Write(context, 0x82,0x95);
  RDA16110E_IIC_Write(context, 0x83,0xa2);
  RDA16110E_IIC_Write(context, 0x84,0x95);
  RDA16110E_IIC_Write(context, 0x85,0x8e);
  RDA16110E_IIC_Write(context, 0x86,0x87);
  RDA16110E_IIC_Write(context, 0x87,0xa2);
  RDA16110E_IIC_Write(context, 0x88,0x7f);
  RDA16110E_IIC_Write(context, 0x89,0x9b);
  RDA16110E_IIC_Write(context, 0x8a,0xb7);
  RDA16110E_IIC_Write(context, 0x8b,0xb7);
  RDA16110E_IIC_Write(context, 0x8c,0xb0);
  RDA16110E_IIC_Write(context, 0x8d,0xc4);
  RDA16110E_IIC_Write(context, 0x8e,0xd1);
  RDA16110E_IIC_Write(context, 0x8f,0x95);

  RDA16110E_IIC_Write(context, 0x90,0x10);    /* fall     */
  RDA16110E_IIC_Write(context, 0x91,0x14);
  RDA16110E_IIC_Write(context, 0x92,0x08);
  RDA16110E_IIC_Write(context, 0x93,0x08);
  RDA16110E_IIC_Write(context, 0x94,0x19);
  RDA16110E_IIC_Write(context, 0x95,0x2e);
  RDA16110E_IIC_Write(context, 0x96,0x00);
  RDA16110E_IIC_Write(context, 0x97,0x37);
  RDA16110E_IIC_Write(context, 0x98,0x37);
  RDA16110E_IIC_Write(context, 0x99,0x37);
  RDA16110E_IIC_Write(context, 0x9a,0x3f);
  RDA16110E_IIC_Write(context, 0x9b,0x57);
  RDA16110E_IIC_Write(context, 0x9c,0x37);
  RDA16110E_IIC_Write(context, 0x9d,0x00);
  RDA16110E_IIC_Write(context, 0x9e,0x47);

  RDA16110E_Sleep(10);    /* Wait 10ms; */

/*  Initial configuration end */

}
/*************************************************************************
  Function to Set the RDA16110E
  fPLL:   Frequency              unit: MHz  from  950 to 2150
  fSym:   SymbolRate             unit: KS/s from 1000 to 45000
*************************************************************************/
signed  int   RDA16110E_Set                   (RDA16110E_Context *context, signed  int fPLL_MHz, signed  int lpf_MHz) {
  unsigned char   buffer;
  unsigned int temp_value = 0;
  unsigned char  Filter_bw_control_bit;

  SiTRACE("fPLL_MHz %ld, lpf_MHz %ld\n", fPLL_MHz, lpf_MHz);

  RDA16110E_IIC_Write(context, 0x04,0xc1);    /* add by rda 2011.8.9,RXON = 0 , change normal working state to idle state */
  RDA16110E_IIC_Write(context, 0x2b,0x95);    /* clk_interface_27m=0  add by rda 2012.1.12 */

  /* set frequency start */
  if (context->xtal == 27 ) {
    temp_value = (unsigned long)fPLL_MHz* 77672;    /* ((2^21) / RDA16110e_XTALFREQ); */
  }
  if (context->xtal ==  4 ) {
    temp_value = (unsigned long)fPLL_MHz* 524288;    /* ((2^21) / RDA16110e_XTALFREQ); */
  }
  if (context->xtal == 135) {
    temp_value = (unsigned long)fPLL_MHz* 155345;    /* ((2^21) / RDA16110e_XTALFREQ); */
  }
  if (context->xtal == 24 ) {
    temp_value = (unsigned long)fPLL_MHz* 87381;     /* ((2^21) / RDA16110e_XTALFREQ); */
  }
  if (context->xtal == 30 ) {
    temp_value = (unsigned long)fPLL_MHz* 69905;     /* ((2^21) / RDA16110e_XTALFREQ); */
  }

  buffer = ((unsigned char)((temp_value>>24)&0xff));
  RDA16110E_IIC_Write(context, 0x07,buffer);
  buffer = ((unsigned char)((temp_value>>16)&0xff));
  RDA16110E_IIC_Write(context, 0x08,buffer);
  buffer = ((unsigned char)((temp_value>>8)&0xff));
  RDA16110E_IIC_Write(context, 0x09,buffer);
  buffer = ((unsigned char)( temp_value&0xff));
  RDA16110E_IIC_Write(context, 0x0a,buffer);
  /* set frequency end */

  /*  set Filter bandwidth start */
  Filter_bw_control_bit = (unsigned char)(lpf_MHz);

  if(Filter_bw_control_bit<4)
    Filter_bw_control_bit =  4;
  else if(Filter_bw_control_bit>40)
    Filter_bw_control_bit = 40;

  Filter_bw_control_bit &= 0x3f;
  Filter_bw_control_bit |= 0x40;

  RDA16110E_IIC_Write(context, 0x0b,Filter_bw_control_bit);
  /*  set Filter bandwidth end */

  RDA16110E_IIC_Write(context, 0x04,0xc3);    /* add by rda 2011.8.9,RXON = 0 ,rxon=1,normal working */
  RDA16110E_IIC_Write(context, 0x2b,0x97);    /* clk_interface_27m=1  add by rda 2012.1.12  */
  RDA16110E_Sleep(5);    /* Wait 5ms; */

  return 1;
}
/************************************************************************
   rf_chn=1 : switch to the same-side      RF_pin
   rf_chn=0 : switch to the different-side RF_pin
*/
unsigned int  L1_RF_RDA16110E_RfSel           (RDA16110E_Context *context, unsigned char rf_chn) {
  unsigned char buffer;

  if (rf_chn)    /* Connect the same-side RF_pin, disconnect the different-side RF_pin */
  {
    RDA16110E_IIC_Read (context ,0x65,&buffer);
    RDA16110E_IIC_Write(context, 0x65,(buffer | 0x04));

    context->i2c->address = context->i2c->address^0x02;
    RDA16110E_IIC_Read (context,0x65,&buffer);
    RDA16110E_IIC_Write(context,0x65,(buffer & 0xFD));
    context->i2c->address = context->address_log;
  }
  else        /* Connect the different-side RF_pin, disconnect the same-side RF_pin */
  {
    context->i2c->address = context->i2c->address^0x02;
    RDA16110E_IIC_Read (context, 0x65,&buffer);
    RDA16110E_IIC_Write(context, 0x65,(buffer | 0x02));
    context->i2c->address = context->address_log;

    RDA16110E_IIC_Read (context, 0x65,&buffer);
    RDA16110E_IIC_Write(context, 0x65,(buffer & 0xFB));
  }
  return 1;
}
void          L1_RF_RDA16110E_Init            (RDA16110E_Context *context, unsigned int add) {
    SiTRACE_X("RDA16110E_Init starting...\n");
    SiTRACE_X("RDA16110E Driver: this is untested code which needs to be verified !...\n");
    context->i2c = &(context->i2cObj);
    L0_Init(context->i2c);
    L0_SetAddress(context->i2c, add, 1);
    context->i2c->mustReadWithoutStop =1;
    context->IF                   =                     0;
    context->RF                   =                950000;
    context->minRF                =                950000;
    context->maxRF                =               2350000;
    context->LPF                  =                 38100;
    context->loopthrough          =                     0;
    context->xtal                 =                    27; /* Options: 4 (4 MHz), 135 (13.5 MHz), 24 (24 MHz), 27 (27 MHz), 30 (30 MHz) */
    context->address_log          = context->i2c->address;
    context->sub                  =                     0;
    context->rssi_offset          =                     0;
    SiTRACE_X("L1_RF_RDA16110E_Init complete...\n");
}
int           L1_RF_RDA16110E_InitAfterReset  (RDA16110E_Context *context) {
  SiTRACE("L1_RF_RDA16110E_InitAfterReset starting...\n");
  RDA16110E_Initialize(context);
  SiTRACE("L1_RF_RDA16110E_InitAfterReset complete...\n");
  return 0;
}
int           L1_RF_RDA16110E_Get_RF          (RDA16110E_Context *context) {
   return context->RF;
}
int           L1_RF_RDA16110E_Tune            (RDA16110E_Context *context, signed   int rf_kHz      ) {
   /* Checking limits */
   if (rf_kHz < (context->minRF)) {
     SiERROR("RDA16110E rf_kHz < minRF \n");
     SiTRACE("rf_kHz %d < minRF %d\n",rf_kHz,context->minRF); return L1_RF_RDA16110E_Tune(context, context->minRF);
   }
   if (rf_kHz > (context->maxRF)) {
     SiERROR("RDA16110E rf_kHz > maxRF \n");
     SiTRACE("rf_kHz %d > maxRF %d\n",rf_kHz,context->maxRF); return L1_RF_RDA16110E_Tune(context, context->maxRF);
   }
   context->i2c->trackRead = context->i2c->trackWrite;
   context->RF = rf_kHz;
   RDA16110E_Set(context, (context->RF + 500)/1000, context->LPF/1000);
   return context->RF;
}
int           L1_RF_RDA16110E_LPF             (RDA16110E_Context *context, signed   int lpf_khz     ) {
  if (lpf_khz != 0) { /* use '0' to retrieve the current value */
    if (lpf_khz > 45000) {
      SiTRACE("RDA16110E requested lpf_khz %d higher than max, set to max\n", lpf_khz);
      lpf_khz = 45000;
    }
    if (lpf_khz < 4000) {
      SiTRACE("RDA16110E requested lpf_khz %d smaller than min, set to min\n", lpf_khz);
      lpf_khz = 4000;
    }
    context->LPF = (int)((lpf_khz + 500));
  }

  SiTRACE("RDA16110E lpf %d kHz\n", context->LPF);

  RDA16110E_Set(context, (context->RF + 500)/1000, context->LPF/1000);
  return context->LPF;
}
int           L1_RF_RDA16110E_RSSI            (RDA16110E_Context *context, signed   int other_gain  ) {
  unsigned char gain_stage, freq_band;
  unsigned int buf_reg16, buf_reg17;
  unsigned char buffer;
  signed   int min_stage_gain;
  signed   int max_stage_gain;
  signed   int *all_stage_gains;
  signed   int i;
  signed   int buf_vga, total_gain, buf_rssi;
  signed   int max_vga = 300;  /* unit : 0.1dB */

  signed   int stage_gain[6][15] =
  {
    { -130, -69, -9,  46, 101, 148, 205, 261, 296, 337, 399, 458, 512, 592, 710 },  /*  950~1200 */
    { -96,  -35, 25,  80, 135, 182, 239, 307, 330, 371, 432, 491, 546, 623, 742 },  /* 1200~1400 */
    { -78,  -17, 43,  99, 143, 200, 258, 316, 348, 388, 450, 509, 564, 641, 761 },  /* 1400~1650 */
    { -78,  -18, 45, 100, 144, 200, 255, 314, 344, 389, 451, 509, 565, 642, 763 },  /* 1650~1850 */
    { -70,  -10, 54, 109, 154, 208, 263, 322, 352, 397, 459, 518, 574, 650, 771 },  /* 1850~2100 */
    { -73,  -14, 50, 105, 151, 204, 258, 319, 349, 392, 456, 515, 570, 647, 765 }   /* 2100~2350 */
  };

       if ( context->RF <  950000 )      return 1;
  else if ( context->RF < 1200000 )  freq_band =0;
  else if ( context->RF < 1400000 )  freq_band =1;
  else if ( context->RF < 1650000 )  freq_band =2;
  else if ( context->RF < 1850000 )  freq_band =3;
  else if ( context->RF < 2100000 )  freq_band =4;
  else if ( context->RF < 2350000 )  freq_band =5;
  else          return 1;

  RDA16110E_IIC_Read(context, 0x16,&buffer);
  buf_reg16 = (unsigned int)buffer & 0xff;

  RDA16110E_IIC_Read(context, 0x17,&buffer);
  buf_reg17 = (unsigned int)buffer & 0x0f;

  RDA16110E_IIC_Read(context, 0xB7,&buffer);
  buf_vga   = (unsigned int)buffer & 0xff;

  switch( buf_reg16 | (buf_reg17<<8) )
  {
    case 0x1000:  gain_stage = 0x00;  break;
    case 0x2000:  gain_stage = 0x01;  break;
    case 0x3000:  gain_stage = 0x02;  break;
    case 0x3001:  gain_stage = 0x03;  break;
    case 0x3002:  gain_stage = 0x04;  break;
    case 0x7002:  gain_stage = 0x05;  break;
    case 0xB201:  gain_stage = 0x06;  break;
    case 0xB202:  gain_stage = 0x07;  break;
    case 0xB206:  gain_stage = 0x08;  break;
    case 0xB20A:  gain_stage = 0x09;  break;
    case 0xB60A:  gain_stage = 0x0A;  break;
    case 0xB60E:  gain_stage = 0x0B;  break;
    case 0xBA0E:  gain_stage = 0x0C;  break;
    case 0xBF0E:  gain_stage = 0x0D;  break;
    case 0xFF0F:  gain_stage = 0x0E;  break;

    default:      return 1;
  }

  total_gain = stage_gain[freq_band][gain_stage] + (buf_vga*max_vga/255);  /* unit: 0.1 dB */

  min_stage_gain = 1000;
  max_stage_gain =    0;
  all_stage_gains =  &(stage_gain[0][0]);
  for (i= 0; i< sizeof(stage_gain); i++) {
    if (all_stage_gains[i] < min_stage_gain) min_stage_gain = all_stage_gains[i];
    if (all_stage_gains[i] > max_stage_gain) max_stage_gain = all_stage_gains[i];
  }
  context->rssi = (unsigned char)((total_gain-min_stage_gain)*255/(max_stage_gain+max_vga-min_stage_gain));

  return  context->rssi+context->rssi_offset;
}
int           L1_RF_RDA16110E_RSSI_from_AGC   (RDA16110E_Context *context, signed   int if_agc      ) {
/* This is an estimation of RSSI based on the IF_AGC (some dBm of error are possible according to the RF and the input level) */
  signed   int   RDA16110E_agc         []           = {   0,   188,  231,  256};
  signed   int   RDA16110E_level_dBm_10[]           = {  45,  -700, -800, -919};

  signed   int   index;
  signed   int   table_length;
  signed   int  *x;
  signed   int  *y;
  signed   int   slope;
  context = context; /* To avoid compiler warning while keeping a common prototype for all tuners */
  if (if_agc>=256) return  context->rssi;
  if (if_agc<   0) return  context->rssi;

  x = RDA16110E_agc;
  y = RDA16110E_level_dBm_10;
  table_length = sizeof(RDA16110E_agc)/sizeof(int);

  /* Finding in which segment the if_agc value is */
  for (index = 0; index < table_length; index ++) {if (x[index] > if_agc ) break;}
  /* Computing segment slope */
  slope =  ((y[index]-y[index-1])*1000)/(x[index]-x[index-1]);
  /* Linear approximation of rssi value in segment (rssi values will be in 0.1dBm unit: '-523' means -52.3 dBm) */
  context->rssi = ((y[index-1] + ((if_agc - x[index-1])*slope + 500)/1000))/10;
  SiTRACE("L1_RF_RDA16110E_RSSI if_agc %3d rssi %5d dBm\n",if_agc ,context->rssi);
  return context->rssi;
}

unsigned char L1_RF_RDA16110E_Wakeup          (RDA16110E_Context *context) {
  unsigned char temp;
  SiTRACE("L1_RF_RDA16110E_Wakeup starting...\n");

  SiTRACE("L1_RF_RDA16110E_Wakeup done\n");
  return 0;
}
unsigned char L1_RF_RDA16110E_Standby         (RDA16110E_Context *context) {
  unsigned char temp;
  SiTRACE("L1_RF_RDA16110E_Standby starting...\n");

  SiTRACE("L1_RF_RDA16110E_Standby done\n");
  return 0;
}

char*         L1_RF_RDA16110E_TAG_TEXT        (void) { return (char *)"RDA16110E SVN6649"; }
