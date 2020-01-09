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
/*                     SiLabs Layer 1                  RF Tuner AV2017                                       */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains all API Functions for the AV2017 Tuner on the RF board                        */
/*     All functions are declared in Silabs_L1_RF_AV2017_API.h                                              */
/*************************************************************************************************************/
/* Change log:

 As from SVN6512: Modified to remove compilation warnings depending on the compiler.

 As from SVN6314:
  In L1_RF_AV2017_Tune: Computing fracN according to latest Airoha code, thus avoiding issues with fracN being 0
  In L1_RF_AV2017_RSSI: Linear approximation of rssi value as RSSI= (280-6*AGC)/10

 As from SVN6191

 *************************************************************************************************************/
#define   SiLEVEL          1
#define   SiTAG            context->i2c->tag

#include "Silabs_L1_RF_AV2017_API.h"
#define Time_DELAY_MS      system_wait

#define Tuner_I2C_write( index, buffer, count)   L0_WriteBytes (context->i2c, index, count, buffer)
#define Tuner_I2C_read(  index, buffer, count)   L0_ReadBytes  (context->i2c, index, count, buffer)

void  L1_RF_AV2017_Init           (AV2017_Context *context, unsigned int add) {
    AV2017_Context *pAVtuner;
    SiTRACE_X("L1_RF_AV2017_Init starting...\n");
    context->i2c = &(context->i2cObj);
    #ifndef   DLL_MODE
    L0_Init(context->i2c);
    #endif /* DLL_MODE */
    L0_SetAddress(context->i2c, add, 1);
    #ifndef   DLL_MODE
    context->i2c->mustReadWithoutStop =1;
    #endif /* DLL_MODE */
    pAVtuner = context;
    context->tunerBytesCount      =                    50;
    context->IF                   =                     0;
    context->RF                   =                950000;
    context->minRF                =                925000;
    context->maxRF                =               2175000;
    context->I2CMuxChannel        =                     0;
    context->tuner_crystal        =                    24;
    context->LPF                  =              38100000;
    context->i2c->trackWrite      =                     0;
    context->RXIQ_out             = AV2017_RXIQ_out_differential;
    /*
    context->RXIQ_out = AV2017_RXIQ_out_single_ended; for AV2018
    context->RXIQ_out = AV2017_RXIQ_out_differential; for AV2017
    */
    pAVtuner->crystal_khz   = context->tuner_crystal*1000; /* (Unit: KHz)Tuner_crystal */
                                                /* 24MHz XO application  */
    pAVtuner->IQmode        = Differential;     /* IQ_MODE               */
    pAVtuner->PGA_Gain      = PGA_1_5dB ;       /* PGA_GAIN              */
    pAVtuner->PGA_Current   = PGA_1_5mA ;       /* PGA_DRIVE_CURRENT     */
    pAVtuner->XO_Current    = HIGH;             /* XO_DRIVE_CURRENT      */
    pAVtuner->XO_EN         = XO_ON;            /* XO_ENABLE Setting     */
    pAVtuner->RFLP_EN       = RFLP_OFF;         /* RFLP_ENABLE Setting   */
    pAVtuner->PD_EN         = Wake_Up;          /* SOFTWARE_POWERDOWN    */
    pAVtuner->FT            = FT_ON;            /* TUNER_Fine_Tune       */
    pAVtuner->blind_scan    = 0;                /* blind_scan            */
    SiTRACE_X("L1_RF_AV2017_Init complete...\n");
}

int   L1_RF_AV2017_InitAfterReset (AV2017_Context *context) {
  unsigned char add;
  int           result;
  unsigned char *reg;
  AV2017_Context *pAVtuner;
  pAVtuner = context;
  reg = context->tuner_log;

  SiTRACE("L1_RF_AV2017_InitAfterReset starting...\n");
  /* Register initial flag. Static constant for first entry */
  /* At Power ON, tuner_initial = 0, will run sequence 1~3 at first call of "Tuner_control(). */
  /* Initial registers R0~R41 */
  /* [Important] Please notice that the default RF registers must be sent in this sequence:
     R0~R11, R13~R41, and then R12. R12 must be sent at last.  */
  if (1) {
  reg[ 0]=(char) (0x5A);   /* initial freq=2150MHz (calculate by 24Mz XO)*/
  reg[ 1]=(char) (0x95);   /* initial freq=2150MHz (calculate by 24Mz XO)*/
  reg[ 2]=(char) (0x55);   /* initial freq=2150MHz (calculate by 24Mz XO)*/
  reg[ 3]=(char) (0x50);   /* initial freq=2150MHz (calculate by 24Mz XO)*/
  reg[ 4]=(char) (0x1f);
  reg[ 5]=(char) (0xa3);
  reg[ 6]=(char) (0xfd);
  reg[ 7]=(char) (0x58);
  reg[ 8]=(char) ((0x04)|(pAVtuner->PGA_Gain <<3)|(pAVtuner->PGA_Current));

  if( pAVtuner->crystal_khz < 25000 )
    reg[ 9]= (0x00)|(pAVtuner->XO_Current<<6); /* ctrl_clk Divider=/1 */
  else
    reg [9]= (0x02)|(pAVtuner->XO_Current<<6); /* ctrl_clk Divider=/2 */

  reg[10]=(char) (0x88);
  reg[11]=(char) (0xb4);
  reg[12]=(char) ((0x16)|(pAVtuner->XO_EN <<7)|(pAVtuner->RFLP_EN <<6)|(pAVtuner->PD_EN <<5));
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
  reg[29]=(char) (0xee); /* Updated from 0x02 to 0xee (VDAPPS-367): To be checked against Airoha driver */
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
  result = Tuner_I2C_write(0,reg,12);  /* Send Reg0 ->Reg11 */
  if(result!=12){ SiERROR("L1_RF_AV2017_InitAfterReset: Write error!\n"); }

  /* Sequence 2 */
  Tuner_I2C_write(13,reg+13,12);  /* Send Reg13 ->Reg24 */
  Tuner_I2C_write(25,reg+25,11);  /* Send Reg25 ->Reg35 */
  Tuner_I2C_write(36,reg+36, 6);  /* Send Reg36 ->Reg41 */

  /* Sequence 3 */
  Tuner_I2C_write(12,reg+12,1);  /* Send reg12 */
  /* Making sure the i2c address is correct */
  if (L0_ReadRegister(context->i2c, 12, 0, 8, 0) != reg[12]) {
    SiTRACE("AV2017 read  error! Check your i2c implementation and/or i2c address for the AV2017!! (currently 0x%02x)\n", context->i2c->address);
    SiERROR("AV2017 read  error! Check your i2c implementation and/or i2c address for the AV2017!!");
    for (add = 0xc0; add <= 0xc6; add = add +2) { /* try all possible i2c addresses for AV2017 */
      context->i2c->address = add;
      Tuner_I2C_write(12,reg+12,1);
      if (L0_ReadRegister(context->i2c, 12, 0, 8, 0) != reg[12]) {
        SiTRACE("AV2017 READ not working for i2c address 0x%02x...\n", add);
      } else {
        SiTRACE("AV2017 READ working for i2c address 0x%02x. The AV2017 i2c address can be 0x%02x.\n", add, add);
      }
    }
  }

  /* Time delay ms */
  Time_DELAY_MS(100);
  /* Reinitial again */
  {
    /* Sequence 1 */
    Tuner_I2C_write(0,reg,12);    /* Send Reg0 ->Reg11 */

    /* Sequence 2 */
    Tuner_I2C_write(13,reg+13,12);/* Send Reg13 ->Reg24 */
    Tuner_I2C_write(25,reg+25,11);/* Send Reg25 ->Reg35 */
    Tuner_I2C_write(36,reg+36,6); /* Send Reg36 ->Reg41 */

    /* Sequence 3 */
     Tuner_I2C_write(12,reg+12,1);/* Send reg12 */
  }
  /* Time delay ms */
  Time_DELAY_MS(5);

  L1_RF_AV2017_Tune (context, context->RF);

  SiTRACE("L1_RF_AV2017_InitAfterReset complete...\n");
  return 0;
}

int   L1_RF_AV2017_Get_Infos      (AV2017_Context *context, char **infos) {
  strcpy(*infos,"AV2017 Airoha Digital Satellite Tuner");
  context= context; /* To avoid compiler warning while keeping a common prototype for all tuners */
  return 0;
}

int   L1_RF_AV2017_Wakeup         (AV2017_Context *context) {
  L1_RF_AV2017_InitAfterReset (context);
  return 0;
}

int   L1_RF_AV2017_Standby        (AV2017_Context *context) {
  AV2017_WRITE (context, pd_soft, pd_soft_power_down);
  return 0;
}

int   L1_RF_AV2017_ClockOn        (AV2017_Context *context) {
  AV2017_WRITE (context, xocore_ena, 1);
  return 0;
}

int   L1_RF_AV2017_ClockOff       (AV2017_Context *context) {
  AV2017_WRITE (context, xocore_ena, 0);
  return 0;
}

int   L1_RF_AV2017_Get_IF         (AV2017_Context *context) {
   return context->IF;}

int   L1_RF_AV2017_Get_RF         (AV2017_Context *context) {
   return context->RF;}

int   L1_RF_AV2017_Get_minRF      (AV2017_Context *context) {
   return context->minRF;}

int   L1_RF_AV2017_Get_maxRF      (AV2017_Context *context) {
   return context->maxRF;}
/*********************************************************************************
* Loopthrough and power-down setting
* Paramter1:    pTunerPara : pointer of Tuner parameter structure
* Return value: TUNER_ErrorCode : error code of definition
* Description:
* 1. reg[12]_D7 is xocore_ena. Enable/disable XO section
* 2. reg[12]_D6 is RFLP_ena.   Enable/disable Loop-through section
* 3. reg[12]_D5 is PD_soft.     Power ON/OFF Receiver,Synthesizer,VCO section
* 4. For tuner model name =1, hardware Power-down is controled by Hardware Pin13, which turn off Receiver,Synthesizer,VCO,XO,Control section.
*   For tuner model name =1, make sure Pin13 is at low when sending registers.
**********************************************************************************/
TUNER_ErrorCode Tuner_Set_RFLP_PD      (AV2017_Context * context)
{
  unsigned char reg12;
  AV2017_Context *pAVtuner;
  TUNER_ErrorCode result;
  result = Tuner_No_Error;
  pAVtuner = context;

  reg12 = (0x16)|( pAVtuner->XO_EN <<7)|(pAVtuner->RFLP_EN <<6)|(pAVtuner->PD_EN <<5);

  result = Tuner_I2C_write(12, &reg12, 1);
     /* Time delay ms*/
  Time_DELAY_MS(5);
  return result;
}
/*********************************************************************************
* RX output baseband programmable gain amplifier setting
* Paramter1:    pTunerPara : pointer of Tuner parameter structure
* Return value: TUNER_ErrorCode : error code of definition
* Description:
* 1. reg[8]_D6~D3 is gc. PGA gain setting
* 2. reg[8]_D1~0  is PGAout_cs. PGA output driving current setting
**********************************************************************************/
TUNER_ErrorCode Tuner_Set_RXout_PGA    (AV2017_Context * context)
{
  AV2017_Context *pAVtuner;
  unsigned char reg8;
  TUNER_ErrorCode result;
  result = Tuner_No_Error;
  pAVtuner = context;

  reg8 = (0x04)|(pAVtuner->PGA_Gain <<3)|(pAVtuner->PGA_Current);

  result = Tuner_I2C_write(8, &reg8, 1);
  return result;
}
/*********************************************************************************
* Channel lock status
* Paramter1:    pTunerPara : pointer of Tuner parameter structure
* Return value: TUNER_ErrorCode : error code of definition
* Description:
* 1. reg[11]_D0 is CHLF. Read-only bit. Lock=1. Unlock=0.
**********************************************************************************/
TUNER_ErrorCode Tuner_Get_Channel_Lock (AV2017_Context * context)
{
  TUNER_ErrorCode result;
  unsigned char lock;
  unsigned char *reg;
  reg = context->tuner_log;
  result = Tuner_No_Error;

  Tuner_I2C_read (11, &reg[11], 1);
  lock = reg[11] &0x01;
  if ( lock != 1)
    result = PLL_Lock_Error;
  return result;
}
/*********************************************************************************
* Filter bandwidth lock status
* Paramter1:    pTunerPara : pointer of Tuner parameter structure
* Return value: TUNER_ErrorCode : error code of definition
* Description:
* 1. reg[11]_D1 is BWLF. Read-only bit. Lock=1. Unlock=0.
**********************************************************************************/
TUNER_ErrorCode Tuner_Get_Filter_Lock  (AV2017_Context * context)
{
  TUNER_ErrorCode result;
  unsigned char lock;
  unsigned char *reg;
  reg = context->tuner_log;
  result = Tuner_No_Error;

  Tuner_I2C_read (11, reg+11, 1);
  lock = (reg[11]>>1) &0x01;
  if ( lock != 1)
    result = Filter_Lock_Error;
  return result;
}
/*********************************************************************************
* Channel frequency setting
* Paramter1:    pTunerPara : pointer of Tuner parameter structure
* Paramter2:    UINT32 : channel frequency (unit: MHz)
* Return value: TUNER_ErrorCode : error code of definition
* Description:
* 1. Send reg3,2,1,0 to set tuner at the channel frequency.
*    reg0 is int<7:0>; reg1 is frac<16:9>; reg2 is frac<8:1>; reg3_D7 is frac<0>
*   For Tuner model name =1, reg3_D2 is IQ mode selection.
* 2. If XO is not default 27MHz, need to manually select VCO Divider.
*    The VCO Divider switching point is freqency=1167.75MHz,
*    and send Reg16 before Reg0~3
**********************************************************************************/
int   L1_RF_AV2017_Tune           (AV2017_Context *context, int freq_khz) {
  int Int;
  int fracN;
  int BW_kHz;
  int BF;
  unsigned char *reg;
  int result;
  unsigned int XO_khz;
  unsigned int ctrl_clk_khz;
  unsigned int BW_CLK_khz;
  unsigned int pre_delay;
  unsigned int post_delay;

  AV2017_Context *pAVtuner;
  pAVtuner = context;

  XO_khz = pAVtuner->crystal_khz;
  pAVtuner = context;
  reg = context->tuner_log;

  SiTRACE("L1_RF_AV2017_Tune freq_khz %8d\n", freq_khz);

  if( XO_khz != 27000 )
  {
    if(freq_khz > 1167750)
       reg[16] = 0x56; /* VCO Divider=/2 */
    else
       reg[16] = 0x46; /* VCO Divider=/4  */
    result=Tuner_I2C_write(16,reg+16,1); /* Send Reg16 */
    if(result!=1){ SiERROR("L1_RF_AV2017_Tune: Write error!\n");  SiTRACE("L1_RF_AV2017_Tune: Write error! (result %d)\n", result); }
  }

  Int      =  ( (freq_khz +      context->tuner_crystal*1000/2)     /(context->tuner_crystal*1000));
  if(Int > 0xff)  Int = 0xff;

  fracN= ((freq_khz/100)<<17)/(context->tuner_crystal*10);
  fracN = fracN & 0x1ffff;
  SiTRACE("L1_RF_AV2017_Tune freq_khz %8d, Int %3d, fracN %d\n", freq_khz, Int, fracN);

  reg[0]=(char) (Int & 0xff);
  reg[1]=(char) ((fracN>>9)&0xff);
  reg[2]=(char) ((fracN>>1)&0xff);

  /*  reg[3]= (0x50)|(fracN<<7)|(pAVtuner->IQmode<<2);*/
  /******************************************************
  reg[3]_D7 is Frac<0>, D6~D0 is 0x50, For differential RXIQ out (AV2018)
  reg[3]_D7 is Frac<0>, D6~D0 is 0x54, For single RXIQ out       (AV2017)
  ******************************************************/
  if (context->RXIQ_out == AV2017_RXIQ_out_single_ended) {
    reg[3]=(char) (((fracN<<7)&0x80) | 0x54);
  } else {
    reg[3]=(char) (((fracN<<7)&0x80) | 0x50);
  }
  Tuner_I2C_write(3,reg+3,1); /* Send Reg3 */
  Tuner_I2C_write(2,reg+2,1); /* Send Reg2 */
  Tuner_I2C_write(1,reg+1,1); /* Send Reg1 */
  Tuner_I2C_write(0,reg+0,1); /* Send Reg0 */
  /* --------------------------retune channel after 100ms on Nov.04.2013--Start-------------------------------*/
  Time_DELAY_MS(100);  /* delay 100ms */
  Tuner_I2C_write(3,reg+3,1); /* Re-Send Reg3 */
  Tuner_I2C_write(2,reg+2,1); /* Re-Send Reg2 */
  Tuner_I2C_write(1,reg+1,1); /* Re-Send Reg1 */
  Tuner_I2C_write(0,reg+0,1); /* Re-Send Reg0 */
  /*---------------------------retune channel after 100ms on Nov.04.2013--End---------------------------------*/
  /* Time delay ms*/
  Time_DELAY_MS(4);

  /*----------Part-1 modification by Airoha Ivan on July.16.2014--------Start-------- */
  if( (freq_khz%XO_khz)==0)
  {
    reg[30] = 0xe5;
  }
  else
  {
    reg[30] = 0xf5;
  }
  Tuner_I2C_write(30,reg+30,1);
  /*----------Part-1 modification by Airoha Ivan on July.16.2014---------End---------  */
  /* Time delay ms */
  Time_DELAY_MS(4);

  /* Tuner_Set_Filter_Bandwith START */
  BW_kHz  = context->LPF;
  if( XO_khz < 25000 )
    ctrl_clk_khz = XO_khz;
  else
    ctrl_clk_khz = XO_khz/2;
  /* Filter Bandwidth reference CLK calculation */
  BW_CLK_khz = (ctrl_clk_khz +64/2)/64;
  /* BF = filter_BW (KHz) * 1.27 / BW_CLK (KHz)*/
  BF = (BW_kHz*127 + 100*BW_CLK_khz/2)/(100*BW_CLK_khz);
  if(BF > 0xff)
     BF = 0xff;
  SiTRACE("L1_RF_AV2017_Tune Channel_freq_kHz %d LPF %d BW_kHz %d BF %8d\n", freq_khz, context->LPF, BW_kHz, BF);

#ifdef    IN_AV2018_DRIVER
    /* Sequence 4 */
    /* Send Reg0 ->Reg4 */
    Tuner_I2C_write(0,reg+0,4);

    /* Time delay 4ms */
    Time_DELAY_MS(4);
#endif /* IN_AV2018_DRIVER */

  reg[5] = (unsigned char)BF;
  /* Sequence 5*/
  /* Send Reg5 */
  Tuner_I2C_write(5, reg+5, 1);
  /* Time delay ms*/
  Time_DELAY_MS(4);

  /* Reset FT after Filter BW setting */
  if (pAVtuner->blind_scan == 1)
  {
    /* choose one for different blind scan mechanism */
    /* pAVtuner->FT = FT_OFF;  */
    /* pAVtuner->FT = FT_Hold; */
    pAVtuner->FT = FT_ON;
  }
  else
  {
    pAVtuner->FT = FT_Delay_ON;
  }
  /* Tuner_Set_Fine_Tune START */
  switch ( pAVtuner->FT )
  {
    case  FT_ON:{
      pre_delay  =  1;
      post_delay =  5;
      break;
    }
    case  FT_Hold:{
      pre_delay  = 10;
      post_delay =  1;
      break;
    }
    case  FT_Delay_ON:{
      pre_delay  =  1;
      post_delay = 15;
      break;
    }
    case   FT_OFF:
    default:{ /* OFF */
      pre_delay  =  1;
      post_delay =  1;
      break;
    }
  }

  reg[37] = pAVtuner->FT;
  /* Time delay ms*/
  Time_DELAY_MS(pre_delay);
  /* Send Fine-tune Function Control*/
  Tuner_I2C_write(37, reg+37, 1);
  /* Time delay ms*/
  Time_DELAY_MS(post_delay);
  /* Tuner_Set_Fine_Tune STOP  */

  /* Tuner_Set_Filter_Bandwith START */
#ifdef    IN_AV2018_DRIVER
    /* Fine-tune function is starting tracking after sending reg[37]. */
    /* Make sure the RFAGC do not have a sharp jump. */
    /* Disable RFLP at Lock Channel sequence after reg[37] if not used */
    reg[12] = 0x96;
    Tuner_I2C_write(12, reg+12, 1);

    /* Time delay 4ms */
    Time_DELAY_MS(4);
#endif /* IN_AV2018_DRIVER */

  context->RF = (Int*context->tuner_crystal*1000) + ((fracN*context->tuner_crystal*1000)>>17);
  SiTRACE("L1_RF_AV2017_Tune context->RF %8d\n", context->RF);
  SiTRACE("L1_RF_AV2017_Tune context->RF - freq_khz %8d\n", context->RF - freq_khz);

  return context->RF;
}

int   L1_RF_AV2017_LPF            (AV2017_Context *context, int lpf_khz ) {
  if (lpf_khz != 0) { /* use '0' to retrieve the current value */
    if ((lpf_khz > 40000)) {
      SiTRACE("L1_RF_AV2017_LPF requested lpf_khz %d higher than max, set to max (auto_scan mode)\n", lpf_khz);
      lpf_khz = 40000;
    }
    if ((lpf_khz <  4000)) {
      SiTRACE("L1_RF_AV2017_LPF requested lpf_khz %d smaller than min, set to min\n", lpf_khz);
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
  SiTRACE("L1_RF_AV2017_LPF context->LPF %d\n", context->LPF);
  return context->LPF;
}

int   L1_RF_AV2017_RSSI           (AV2017_Context *context, int if_agc  ) {
  context = context; /* To avoid compiler warning while keeping a common prototype for all tuners */
  /* Linear approximation of rssi value as RSSI= (280-6*AGC)/10  */
  context->rssi =  (280-6*if_agc)/10;
  SiTRACE("L1_RF_AV2017_RSSI if_agc %3d -> context->rssi %4d dBm\n", if_agc, context->rssi);
  return (int)(context->rssi);
}

const char* L1_RF_AV2017_TAG_TEXT       (void) {
  /* Set here the version string for the tuner */
  return (const char *)"AV2017 driver SVN6314";
}
