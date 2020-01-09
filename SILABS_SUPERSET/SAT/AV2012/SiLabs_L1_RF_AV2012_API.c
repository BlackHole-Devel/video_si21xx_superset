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
/*************************************************************************************************************/
/*                     SiLabs Layer 1                  RF Tuner AV2012                                       */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains all API Functions for the AV2012 Tuner on the RF board                        */
/*     All functions are declared in Silabs_L1_RF_AV2012_API.h                                              */
/*************************************************************************************************************/
/* Change log:

 As from SVN6512: Modified to remove compilation warnings depending on the compiler.

 As from SVN6192
  <improvement>[LPF]
    In L1_RF_AV2012_LPF:
     Removing code from Airoha used with demodulators switching to LIF instead of ZIP above 6 Mb.
     Adding 8% margin on LPF value

 As from SVN5293:
  <new_feature/single_ended> Adding single_ended field in context, to manage single_ended settings.
    By default set to '0' (differential mode).
  <cleanup/blindscan> Removing auto_scan field from context, since this is not used with SiLabs demodulators.
    It has negative effects on SAT blindscan, which requires the BW to be maximum.
  <correction/RSSI> In L1_RF_AV2012_RSSI: returning rssi level based on AGC value, instead of returning internal gain.

 As from SVN5260: <correction/RSSI> In L1_RF_AV2012_RSSI: inverting test when finding segment, returning value divided by 1000.

 As from SVN5221: <correction>[SAT_blindscan] Keeping context->auto_scan always 0. Otherwise, the SAT spectrum is limited due to LPF limitation to 27MHz
 coming from the original Airoha driver.

 As from SVN4960:
  <improvement> [SW_Startup] In L1_RF_AV2012_Init: Checking i2c read result.
   If it fails, display an error trace, and try all possible addresses to see if one works.
   NB: This is for SW startup purpose. It is not intended to be used as an automatic i2c address detection, since
       it can have negative effects on the application.
      For instance, SiLabs TER tuners use the same i2c address range, and it could generate conflicts.
      If an incorrect i2c address is detected, it MUST be corrected in the SW configuration, and the code needs
       to be rebuilt with the correction.

 *************************************************************************************************************/
#define   SiLEVEL          1
#define   SiTAG            context->i2c->tag

#include "Silabs_L1_RF_AV2012_API.h"
#define Time_DELAY_MS      system_wait

#define Tuner_I2C_write( index, buffer, count)   L0_WriteBytes (context->i2c, index, count, buffer)
#define Tuner_I2C_read(  index, buffer, count)   L0_ReadBytes  (context->i2c, index, count, buffer)

void  L1_RF_AV2012_Init           (AV2012_Context *context, unsigned int add) {
    SiTRACE_X("L1_RF_AV2012_Init starting...\n");
    context->i2c = &(context->i2cObj);
    #ifndef   DLL_MODE
    L0_Init(context->i2c);
    #endif /* DLL_MODE */
    L0_SetAddress(context->i2c, add, 1);
    #ifndef   DLL_MODE
    context->i2c->mustReadWithoutStop =1;
    #endif /* DLL_MODE */
    context->tunerBytesCount      =                    50;
    context->IF                   =                     0;
    context->RF                   =                950000;
    context->minRF                =                925000;
    context->maxRF                =               2175000;
    context->I2CMuxChannel        =                     0;
    context->tuner_crystal        =                    27;
    context->LPF                  =              38100000;
    context->i2c->trackWrite      =                     0;
    context->single_ended         =                     0; /* Set this to 1 if using the AV2012 in single_ended mode */
    SiTRACE_X("L1_RF_AV2012_Init complete...\n");
}

int   L1_RF_AV2012_InitAfterReset (AV2012_Context *context) {
  unsigned char *reg;
  unsigned char add;
  reg = context->tuner_log;

  SiTRACE("L1_RF_AV2012_InitAfterReset starting...\n");
  /* Register initial flag. Static constant for first entry */
  /* At Power ON, tuner_initial = 0, will run sequence 1~3 at first call of "Tuner_control(). */
  /* Initial registers R0~R41 */
  /* [Important] Please notice that the default RF registers must be sent in this sequence:
     R0~R11, R13~R41, and then R12. R12 must be sent at last.  */
/******************************************************
  reg[3]_D7 is Frac<0>, D6~D0 is 0x50, For differential RXIQ out
  reg[3]_D7 is Frac<0>, D6~D0 is 0x54, For single RXIQ out
 ******************************************************/
/*  reg[3]=(char) (((Frac<<7)&0x80) | 0x54); */

  if (1) {
  reg[ 0]=(char) (0x38);
  reg[ 1]=(char) (0x00);
  reg[ 2]=(char) (0x00);
  if (context->single_ended == 0) {
  reg[ 3]=(char) (0x50);
  } else {
  reg[ 3]=(char) (0x54);
  }
  reg[ 4]=(char) (0x1f);
  reg[ 5]=(char) (0xa3);
  reg[ 6]=(char) (0xfd);
  reg[ 7]=(char) (0x58);
  if (context->single_ended == 0) {
  reg[ 8]=(char) (0x0e);
  } else {
  reg[ 8]=(char) (0x3f);
  }
  reg[ 9]=(char) (0x82);
  reg[10]=(char) (0x88);
  reg[11]=(char) (0xb4);

  reg[12]=(char) (0xd6); /* RFLP=ON at Power on initial */

  reg[13]=(char) (0x40);
  reg[14]=(char) (0x94);
  reg[15]=(char) (0x4a);
  reg[16]=(char) (0x66);
  reg[17]=(char) (0x40);
  reg[18]=(char) (0x80);
  reg[19]=(char) (0x2b);
  reg[20]=(char) (0x6a);
  reg[21]=(char) (0x50);
  reg[22]=(char) (0x91);
  reg[23]=(char) (0x27);
  reg[24]=(char) (0x8f);
  reg[25]=(char) (0xcc);
  reg[26]=(char) (0x21);
  reg[27]=(char) (0x10);
  reg[28]=(char) (0x80);
  reg[29]=(char) (0x02);
  reg[30]=(char) (0xf5);
  reg[31]=(char) (0x7f);
  reg[32]=(char) (0x4a);
  reg[33]=(char) (0x9b);
  reg[34]=(char) (0xe0);
  reg[35]=(char) (0xe0);
  reg[36]=(char) (0x36);
  reg[37]=(char) (0x00); /* Disable FT function at Power on initial */
  reg[38]=(char) (0xab);
  reg[39]=(char) (0x97);
  reg[40]=(char) (0xc5);
  reg[41]=(char) (0xa8);
  }

  /* Sequence 1 */
  /* Send Reg0 ->Reg11 */
  Tuner_I2C_write(0,reg,12);

  /* Sequence 2 */
  /* Send Reg13 ->Reg24 */
  Tuner_I2C_write(13,reg+13,12);
  /* Send Reg25 ->Reg35 */
  Tuner_I2C_write(25,reg+25,11);
  /* Send Reg36 ->Reg41 */
  Tuner_I2C_write(36,reg+36,6);

  /* Sequence 3 */
  /* send reg12 */
  Tuner_I2C_write(12,reg+12,1);
  /* Making sure the i2c address is correct */
  if (L0_ReadRegister(context->i2c, 12, 0, 8, 0) != reg[12]) {
    SiTRACE("AV2012 read  error! Check your i2c implementation and/or i2c address for the AV2012!! (currently 0x%02x)\n", context->i2c->address);
    SiERROR("AV2012 read  error! Check your i2c implementation and/or i2c address for the AV2012!!");
    for (add = 0xc0; add <= 0xc6; add = add +2) { /* try all possible i2c addresses for AV2012 */
      context->i2c->address = add;
      Tuner_I2C_write(12,reg+12,1);
      if (L0_ReadRegister(context->i2c, 12, 0, 8, 0) != reg[12]) {
        SiTRACE("AV2012 READ not working for i2c address 0x%02x...\n", add);
      } else {
        SiTRACE("AV2012 READ working for i2c address 0x%02x. The AV2012 i2c address can be 0x%02x.\n", add, add);
      }
    }
  }

  /* Time delay 4ms */
  Time_DELAY_MS(4);

  L1_RF_AV2012_Tune (context, context->RF);

  SiTRACE("L1_RF_AV2012_InitAfterReset complete...\n");
  return 0;
}

int   L1_RF_AV2012_Get_Infos      (AV2012_Context *context, char **infos) {
  strcpy(*infos,"AV2012 Airoha Digital Satellite Tuner");
  context= context; /* To avoid compiler warning while keeping a common prototype for all tuners */
  return 0;
}

int   L1_RF_AV2012_Wakeup         (AV2012_Context *context) {
  L1_RF_AV2012_InitAfterReset (context);
  return 0;
}

int   L1_RF_AV2012_Standby        (AV2012_Context *context) {
  AV2012_WRITE (context, pd_soft, pd_soft_power_down);
  return 0;
}

int   L1_RF_AV2012_ClockOn        (AV2012_Context *context) {
  AV2012_WRITE (context, xocore_ena, 1);
  return 0;
}

int   L1_RF_AV2012_ClockOff       (AV2012_Context *context) {
  AV2012_WRITE (context, xocore_ena, 0);
  return 0;
}

int   L1_RF_AV2012_Get_IF         (AV2012_Context *context) {
   return context->IF;}

int   L1_RF_AV2012_Get_RF         (AV2012_Context *context) {
   return context->RF;}

int   L1_RF_AV2012_Get_minRF      (AV2012_Context *context) {
   return context->minRF;}

int   L1_RF_AV2012_Get_maxRF      (AV2012_Context *context) {
   return context->maxRF;}

int   L1_RF_AV2012_Tune           (AV2012_Context *context, int channel_freq_kHz) {
  int Int;
  int Frac;
  int BW_kHz;
  int BF;
  unsigned char *reg;
  BW_kHz  = context->LPF;
  reg = context->tuner_log;

  SiTRACE("L1_RF_AV2012_Tune channel_freq_kHz %8d\n", channel_freq_kHz);

  Int  =  (channel_freq_kHz +      context->tuner_crystal*1000/2)     /(context->tuner_crystal*1000);
  Frac = ((channel_freq_kHz -  Int*context->tuner_crystal*1000  )<<17)/(context->tuner_crystal*1000);
  SiTRACE("L1_RF_AV2012_Tune Channel_freq_kHz %8d, Int %3d, Frac %d\n", channel_freq_kHz, Int, Frac);

  reg[0]=(char) (Int & 0xff);
  reg[1]=(char) ((Frac>>9)&0xff);
  reg[2]=(char) ((Frac>>1)&0xff);

  /******************************************************
  reg[3]_D7 is Frac<0>, D6~D0 is 0x50, For differential RXIQ out
  reg[3]_D7 is Frac<0>, D6~D0 is 0x54, For single RXIQ out
  ******************************************************/
  if (context->single_ended == 0) {
  reg[3]=(char) (((Frac<<7)&0x80) | 0x50);
  } else {
  reg[3]=(char) (((Frac<<7)&0x80) | 0x54);
  }

  /* BF = BW(MHz) * 1.27 / 211KHz */
  BF = (BW_kHz*127 + 21100/2) / (21100);
  SiTRACE("L1_RF_AV2012_Tune Channel_freq_kHz LPF %d BW_kHz %d BF %8d\n", context->LPF, BW_kHz, BF);
  reg[5] = (unsigned char)BF;


    /* Sequence 4 */
    /* Send Reg0 ->Reg4 */
    Tuner_I2C_write(0,reg,4);

    /* Time delay 4ms */
    Time_DELAY_MS(4);

    /* Sequence 5 */
    /* Send Reg5 */
    Tuner_I2C_write(5, reg+5, 1);
    /* Fine-tune Function Control */
    /* Non-auto-scan mode. FT_block=1, FT_EN=1, FT_hold=0 */
    reg[37] = 0x06;
    Tuner_I2C_write(37, reg+37, 1);
    /* Fine-tune function is starting tracking after sending reg[37]. */
    /* Make sure the RFAGC do not have a sharp jump. */
    /* Disable RFLP at Lock Channel sequence after reg[37] if not used */
    reg[12] = 0x96;
    Tuner_I2C_write(12, reg+12, 1);

    /* Time delay 4ms */
    Time_DELAY_MS(4);

  context->RF = (Int*context->tuner_crystal*1000) + ((Frac*context->tuner_crystal*1000)>>17);

  return context->RF;
}

int   L1_RF_AV2012_LPF            (AV2012_Context *context, int lpf_khz) {
  if (lpf_khz != 0) { /* use '0' to retrieve the current value */
    if ((lpf_khz > 40000)) {
      SiTRACE("L1_RF_AV2012_LPF requested lpf_khz %d higher than max, set to max (auto_scan mode)\n", lpf_khz);
      lpf_khz = 40000;
    }
    if ((lpf_khz <  4000)) {
      SiTRACE("L1_RF_AV2012_LPF requested lpf_khz %d smaller than min, set to min\n", lpf_khz);
      lpf_khz = 4000;
    }
    /* add 6M when Rs<6.5M for low IF */
/*    if(lpf_khz<6500) lpf_khz = lpf_khz + 6000; */
    /* add 2M for LNB frequency shifting */
/*    lpf_khz = lpf_khz + 2000; */
    /* add 8% margin since the calculated fc of BB Auto-scanning is not very accurate */
    lpf_khz = lpf_khz*108/100;
    /* Bandwidth can be tuned from 4M to 40M */
    if( lpf_khz< 4000)
    lpf_khz = 4000;
    if( lpf_khz> 40000)
    lpf_khz = 40000;
    context->LPF = (int)((lpf_khz));
  }
  SiTRACE("L1_RF_AV2012_LPF context->LPF %d\n", context->LPF);
  return context->LPF;
}

int   L1_RF_AV2012_RSSI           (AV2012_Context *context, int if_agc) {
/*  int   AV2012_agc  [] = {     0,    27,    44,    58,   129,   143,  170,   182,    201,    224,    255}; */
/*  int   AV2012_gain [] = { 80461, 80410, 79168, 75194, 35690, 25971, 6755, -9000, -15716, -19000, -18697}; */
  int   AV2012_agc         [] = {     0,   115,   145,   160,   179,   195,   211,   255};
  int   AV2012_level_dBm_10[] = {    90,  -288,  -387,  -487,  -587,  -682,  -738,  -890};
  int   index;
  int   table_length;
  int  *x;
  int  *y;
  int   slope;
  context = context; /* To avoid compiler warning while keeping a common prototype for all tuners */
  SiTRACE("L1_RF_AV2012_RSSI if_agc %d\n",if_agc);
  if (if_agc>=256) return  context->rssi;
  if (if_agc<   0) return  context->rssi;

  x = AV2012_agc;
  y = AV2012_level_dBm_10;
  table_length = sizeof(AV2012_agc)/sizeof(int);

  /* Finding in which segment the if_agc value is */
  for (index = 0; index < table_length; index ++) {if (x[index] > if_agc ) break;}
  /* Computing segment slope */
  slope =  ((y[index]-y[index-1])*1000)/(x[index]-x[index-1]);
  /* Linear approximation of rssi value in segment (rssi values will be in 0.1dBm unit: '-523' means -52.3 dBm) */
  context->rssi =  ((y[index-1] + ((if_agc - x[index-1])*slope + 500)/1000))/10;
  SiTRACE("L1_RF_AV2012_RSSI context->rssi %d dBm*10\n",context->rssi);
  return (int)(context->rssi);
}

char* L1_RF_AV2012_TAG_TEXT       (void) {
  /* Set here the version string for the tuner */
  return (char *)"TUNERNAME driver V0.0.1";
}
