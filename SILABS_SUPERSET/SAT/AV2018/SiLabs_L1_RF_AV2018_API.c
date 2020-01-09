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
/*                     SiLabs Layer 1                  RF Tuner AV2018                                       */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains all API Functions for the AV2018 Tuner on the RF board                        */
/*     All functions are declared in Silabs_L1_RF_AV2018_API.h                                              */
/*************************************************************************************************************/
/* Change log:
 As from SVN6815:
  <compatibility>[compiler/warning]
	In L1_RF_AV2018_RSSI: fixing out of bound issue when if_agc is equal to 255
 As from SVN6565:
  <compatibility>[compiler/warning]
    In L1_RF_AV2018_RSSI: moving context settings line after all declarations
    Changing some char* to const char* to avoid compilation warnings on some compilers

 As from SVN6512: Modified to remove compilation warnings depending on the compiler.

 As from SVN6467
  <improvement>[RF_LP] Adding L1_RF_AV2018_LoopThrough to control internal loop through

 As from SVN6191
  <improvement>[LPF]
    In L1_RF_AV2018_LPF:
     Removing code from Airoha used with demodulators switching to LIF instead of ZIP above 6 Mb.
     Adding 8% margin on LPF value

 As from SVN6057
  <Compatibility>[RXIQ out/AV2017] Compatibility with AV2017;
    In L1_RF_AV2018_Init:
    set context->RXIQ_out = AV2018_RXIQ_out_single_ended; (default settings) for AV2018
    use context->RXIQ_out = AV2018_RXIQ_out_differential; for AV2017

 As from SVN5948:
  <improvement>[single RXIQ out/RSSI] In L1_RF_AV2018_RSSI:
    Updated tables to match reg[3] settings to 0x54

 As from SVN5946:
  <improvement>[single RXIQ out] In L1_RF_AV2018_Tune:
    Using reg[3]=(char) (((Frac<<7)&0x80) | 0x54); since AV2018 is single ended

 As from SVN5712:
  <improvementt>[Airoha/VDAPPS-367] Comment received from Airoha:
   'Airoha would like to inform you that below register change may help you to have better improved CN performance.
   The variation of improvement will depend on your customized PCB and circuit design, test environment and different TPs.'
   reg[ 8]=(char) (0x3f); ( Updated from 0x0e to 0x3f )
   reg[29]=(char) (0xee); ( Updated from 0x02 to 0xee )
   changes in L1_RF_AV2018_RSSI tables to return correct RSSI due to the above changes

 As from SVN5294:
  <cleanup/blindscan> Removing auto_scan field from context, since this is not used with SiLabs demodulators.
    It has negative effects on SAT blindscan, which requires the BW to be maximum.
  <correction/RSSI> In L1_RF_AV2018_RSSI: returning rssi level based on AGC value, instead of returning internal gain.

 As from SVN5285: <correction/RSSI> In L1_RF_AV2018_RSSI: returning rssi (now int) based on measurements of AGC level. Unit is dBm.

 As from SVN5258: <correction/RSSI> In L1_RF_AV2018_RSSI: inverting test when finding segment, returning value divided by 1000.

 As from SVN5221: <correction>[SAT_blindscan] Keeping context->auto_scan always 0. Otherwise, the SAT spectrum is limited due to LPF limitation to 27MHz
 coming from the original Airoha driver.

 As from SVN4960:
  <improvement> [SW_Startup] In L1_RF_AV2018_Init: Checking i2c read result.
   If it fails, display an error trace, and try all possible addresses to see if one works.
   NB: This is for SW startup purpose. It is not intended to be used as an automatic i2c address detection, since
       it can have negative effects on the application.
      For instance, SiLabs TER tuners use the same i2c address range, and it could generate conflicts.
      If an incorrect i2c address is detected, it MUST be corrected in the SW configuration, and the code needs
       to be rebuilt with the correction.

 *************************************************************************************************************/
#define   SiLEVEL          1
#define   SiTAG            context->i2c->tag

#include "SiLabs_L1_RF_AV2018_API.h"
#define Time_DELAY_MS      system_wait

#define Tuner_I2C_write( index, buffer, count)   L0_WriteBytes (context->i2c, index, count, buffer)
#define Tuner_I2C_read(  index, buffer, count)   L0_ReadBytes  (context->i2c, index, count, buffer)

void  L1_RF_AV2018_Init           (AV2018_Context *context, unsigned int add) {
    SiTRACE_X("L1_RF_AV2018_Init starting...\n");
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
    context->RXIQ_out             = AV2018_RXIQ_out_single_ended;
    /*
    context->RXIQ_out = AV2018_RXIQ_out_single_ended; for AV2018
    context->RXIQ_out = AV2018_RXIQ_out_differential; for AV2017
    */
    context->RFLP_enabled         = 0;
    SiTRACE_X("L1_RF_AV2018_Init complete...\n");
}

int   L1_RF_AV2018_InitAfterReset (AV2018_Context *context) {
  unsigned char *reg;
  unsigned char add;
  reg = context->tuner_log;

  SiTRACE("L1_RF_AV2018_InitAfterReset starting...\n");
  /* Register initial flag. Static constant for first entry */
  /* At Power ON, tuner_initial = 0, will run sequence 1~3 at first call of "Tuner_control(). */
  /* Initial registers R0~R41 */
  /* [Important] Please notice that the default RF registers must be sent in this sequence:
     R0~R11, R13~R41, and then R12. R12 must be sent at last.  */
  if (1) {
  reg[ 0]=(char) (0x38);
  reg[ 1]=(char) (0x00);
  reg[ 2]=(char) (0x00);
  reg[ 3]=(char) (0x50);
  reg[ 4]=(char) (0x1f);
  reg[ 5]=(char) (0xa3);
  reg[ 6]=(char) (0xfd);
  reg[ 7]=(char) (0x58);
  reg[ 8]=(char) (0x3f); /* Updated from 0x0e to 0x3f (VDAPPS-367) */
  reg[ 9]=(char) (0x82);
  reg[10]=(char) (0x88);
  reg[11]=(char) (0xb4);

  if (context->RFLP_enabled ==1) { reg[12]=(char) (0xd6); /* RFLP=ON  at Power on initial */  }
  if (context->RFLP_enabled ==0) { reg[12]=(char) (0x96); /* RFLP=OFF at Power on initial */  }

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
  reg[29]=(char) (0xee); /* Updated from 0x02 to 0xee (VDAPPS-367) */
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
    SiTRACE("AV2018 read  error! Check your i2c implementation and/or i2c address for the AV2018!! (currently 0x%02x)\n", context->i2c->address);
    SiERROR("AV2018 read  error! Check your i2c implementation and/or i2c address for the AV2018!!");
    for (add = 0xc0; add <= 0xc6; add = add +2) { /* try all possible i2c addresses for AV2018 */
      context->i2c->address = add;
      Tuner_I2C_write(12,reg+12,1);
      if (L0_ReadRegister(context->i2c, 12, 0, 8, 0) != reg[12]) {
        SiTRACE("AV2018 READ not working for i2c address 0x%02x...\n", add);
      } else {
        SiTRACE("AV2018 READ working for i2c address 0x%02x. The AV2018 i2c address can be 0x%02x.\n", add, add);
      }
    }
  }

  /* Time delay 4ms */
  Time_DELAY_MS(4);

  L1_RF_AV2018_Tune (context, context->RF);

  SiTRACE("L1_RF_AV2018_InitAfterReset complete...\n");
  return 0;
}

int   L1_RF_AV2018_Get_Infos      (AV2018_Context *context, char **infos) {
  strcpy(*infos,"AV2018 Airoha Digital Satellite Tuner");
  context= context; /* To avoid compiler warning while keeping a common prototype for all tuners */
  return 0;
}

int   L1_RF_AV2018_Wakeup         (AV2018_Context *context) {
  L1_RF_AV2018_InitAfterReset (context);
  return 0;
}

int   L1_RF_AV2018_Standby        (AV2018_Context *context) {
  AV2018_WRITE (context, pd_soft, pd_soft_power_down);
  return 0;
}

int   L1_RF_AV2018_ClockOn        (AV2018_Context *context) {
  AV2018_WRITE (context, xocore_ena, 1);
  return 0;
}

int   L1_RF_AV2018_ClockOff       (AV2018_Context *context) {
  AV2018_WRITE (context, xocore_ena, 0);
  return 0;
}

int   L1_RF_AV2018_Get_IF         (AV2018_Context *context) {
   return context->IF;}

int   L1_RF_AV2018_LoopThrough    (AV2018_Context *context, int loop_through_enabled) {
  if (loop_through_enabled) {
    context->RFLP_enabled = 1; context->tuner_log[12] = 0xd6;
  } else {
    context->RFLP_enabled = 0; context->tuner_log[12] = 0x96;
  }
  Tuner_I2C_write(12, context->tuner_log+12, 1);
  /* Time delay 4ms */
  Time_DELAY_MS(4);
  return context->RFLP_enabled;
}

int   L1_RF_AV2018_Get_RF         (AV2018_Context *context) {
   return context->RF;}

int   L1_RF_AV2018_Get_minRF      (AV2018_Context *context) {
   return context->minRF;}

int   L1_RF_AV2018_Get_maxRF      (AV2018_Context *context) {
   return context->maxRF;}

int   L1_RF_AV2018_Tune           (AV2018_Context *context, int channel_freq_kHz) {
  int Int;
  int Frac;
  int BW_kHz;
  int BF;
  unsigned char *reg;
  BW_kHz  = context->LPF;
  reg = context->tuner_log;

  SiTRACE("L1_RF_AV2018_Tune channel_freq_kHz %8d\n", channel_freq_kHz);

  Int  =  (channel_freq_kHz +      context->tuner_crystal*1000/2)     /(context->tuner_crystal*1000);
  Frac = ((channel_freq_kHz -  Int*context->tuner_crystal*1000  )<<17)/(context->tuner_crystal*1000);
  SiTRACE("L1_RF_AV2018_Tune Channel_freq_kHz %8d, Int %3d, Frac %d\n", channel_freq_kHz, Int, Frac);
  SiTRACE("L1_RF_AV2018_Tune Channel_freq_kHz %8d, Int %3d, Frac %d\n", channel_freq_kHz, Int, Frac);

  reg[0]=(char) (Int & 0xff);
  reg[1]=(char) ((Frac>>9)&0xff);
  reg[2]=(char) ((Frac>>1)&0xff);

  /******************************************************
  reg[3]_D7 is Frac<0>, D6~D0 is 0x50, For differential RXIQ out (AV2017)
  reg[3]_D7 is Frac<0>, D6~D0 is 0x54, For single RXIQ out       (AV2018)
  ******************************************************/
  if (context->RXIQ_out == AV2018_RXIQ_out_single_ended) {
    reg[3]=(char) (((Frac<<7)&0x80) | 0x54);
  } else {
    reg[3]=(char) (((Frac<<7)&0x80) | 0x50);
  }

  /* BF = BW(MHz) * 1.27 / 211KHz */
  BF = (BW_kHz*127 + 21100/2) / (21100);
  SiTRACE("L1_RF_AV2018_Tune Channel_freq_kHz %d LPF %d BW_kHz %d BF %8d\n", channel_freq_kHz, context->LPF, BW_kHz, BF);
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

    /* Make sure the RFAGC do not have a sharp jump.                  */
   /* Disable RFLP at Lock Channel sequence after reg[37] if not used */
    if (context->RFLP_enabled ==0) {
      Tuner_I2C_write(12, reg+12, 1);
      /* Time delay 4ms */
      Time_DELAY_MS(4);
    }

  context->RF = (Int*context->tuner_crystal*1000) + ((Frac*context->tuner_crystal*1000)>>17);
  SiTRACE("L1_RF_AV2018_Tune context->RF %8d, RF_loopThrough %d\n", context->RF, context->RFLP_enabled);
  SiTRACE("L1_RF_AV2018_Tune context->RF - channel_freq_kHz %8d\n", context->RF - channel_freq_kHz);

  return context->RF;
}

int   L1_RF_AV2018_LPF            (AV2018_Context *context, int lpf_khz) {
  if (lpf_khz != 0) { /* use '0' to retrieve the current value */
    if ((lpf_khz > 40000)) {
      SiTRACE("L1_RF_AV2018_LPF requested lpf_khz %d higher than max, set to max (auto_scan mode)\n", lpf_khz);
      lpf_khz = 40000;
    }
    if ((lpf_khz <  4000)) {
      SiTRACE("L1_RF_AV2018_LPF requested lpf_khz %d smaller than min, set to min\n", lpf_khz);
      lpf_khz = 4000;
    }
    /* add 6M when Rs<6.5M for low IF */
/*    if(lpf_khz<6500) { lpf_khz = lpf_khz + 6000; } */
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
  SiTRACE("L1_RF_AV2018_LPF context->LPF %d\n", context->LPF);
  return context->LPF;
}

int   L1_RF_AV2018_RSSI           (AV2018_Context *context, int if_agc ) {
/* This is an estimation of RSSI based on the IF_AGC (some dBm of error are possible according to the RF and the input level) */
  int   AV2018_agc         []           = {   0, 75,  77,   83,  90,   101,  112,  136,  151,  168,  180,  197,  255};
  int   AV2018_level_dBm_10[]           = { 100, 20, -30, -100, -190, -280, -350, -480, -580, -660, -740, -810, -890};

  int   AV2018_agc_2000_2150         [] = {   0, 77,  83,   90,  100,  113,  131,  135,  150,  168,  180,  197,  255};
  int   AV2018_level_dBm_10_2000_2150[] = { 100, 10, -60, -150, -230, -310, -390, -470, -540, -620, -700, -770, -840};

  int   index;
  int   table_length;
  int  *x;
  int  *y;
  int   slope;
  context = context; /* To avoid compiler warning while keeping a common prototype for all tuners */
  if (if_agc>=256) return  context->rssi;
  if (if_agc<   0) return  context->rssi;

  if (context->RF < 2000000) {
    SiTRACE("L1_RF_AV2018_RSSI using first  table (below 2000 MHz)\n");
    x = AV2018_agc;
    y = AV2018_level_dBm_10;
    table_length = sizeof(AV2018_agc)/sizeof(int);
  } else {
    SiTRACE("L1_RF_AV2018_RSSI using second table (above 2000 MHz)\n");
    x = AV2018_agc_2000_2150;
    y = AV2018_level_dBm_10_2000_2150;
    table_length = sizeof(AV2018_agc_2000_2150)/sizeof(int);
  }

  /* Finding in which segment the if_agc value is */
  for (index = 0; index < table_length-1; index ++) {if (x[index] > if_agc ) break;}
  /* Computing segment slope */
  slope =  ((y[index]-y[index-1])*1000)/(x[index]-x[index-1]);
  /* Linear approximation of rssi value in segment (rssi values will be in 0.1dBm unit: '-523' means -52.3 dBm) */
  context->rssi =  ((y[index-1] + ((if_agc - x[index-1])*slope + 500)/1000))/10;
  SiTRACE("L1_RF_AV2018_RSSI if_agc %3d rssi %5d dBm (RF %d)\n",if_agc ,context->rssi, context->RF);
  return (int)(context->rssi);
}

const char* L1_RF_AV2018_TAG_TEXT       (void) {
  /* Set here the version string for the tuner */
  return "AV2018 driver SVN6467";
}
