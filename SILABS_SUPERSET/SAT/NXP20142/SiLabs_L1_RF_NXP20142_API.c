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
/*                     SILEMBIA Layer 1                  RF Tuner NXP20142_functions                                  */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains all API NXP20142_functions for the NXP20142 Tuner on the RF board                       */
/*     All included NXP20142_functions can be accessed by the higher software level as imports                        */
/*     All NXP20142_functions are declared in Silabs_L1_RF_NXP20142_API.h                                              */
/*************************************************************************************************************/
/* Change log:

 As from SVN4696:
  Changing comments to C style.

 As from SVN1908:
  Corrections in LPF computing (register value is in MHz, from 4 to 40).
  NXP20142 lpf function using kHz values.
 *************************************************************************************************************/
/* TAG TAGNAME */
/*#define RWTRACES*/
#define Layer1_NXP20142

#define   SiLEVEL          1
#define   SiTAG            context->i2c->tag

#include "Silabs_L1_RF_NXP20142_API.h"

unsigned char  NXP20142_RD       (void* p_context,                        SAT_TUNER_ADDRESS address,                               SAT_TUNER_IOSTATUS status) {
  NXP20142_Context *context;
  unsigned char single_byte;
  context = (NXP20142_Context *)p_context;
  single_byte = 0;
/*  SiTRACE("NXP20142_RD at 0x%02x\n", address); */
  if ( L0_ReadBytes (context->i2c, address, 1, &single_byte) == 1) {
    *status = 0;
  } else {
    *status = 1;
  }
/*  SiTRACE("NXP20142_RD returns 0x%02x (%d)\n",single_byte,single_byte); */
  return single_byte;
}

void           NXP20142_WR       (void* p_context,                        SAT_TUNER_ADDRESS address, unsigned char  single_byte,   SAT_TUNER_IOSTATUS status) {
  NXP20142_Context *context;
  context = (NXP20142_Context *)p_context;
/*  SiTRACE("NXP20142_WR at 0x%02 : 0x%02x\n", address, single_byte); */
  if (L0_WriteBytes (context->i2c, (unsigned int)address, 1, &single_byte) == 1) {
    *status = 0;
  } else {
    *status = 1;
  }
}

void           NXP20142_MULTI_WR (void* p_context, unsigned long nbBytes, SAT_TUNER_ADDRESS address, unsigned char* several_bytes, SAT_TUNER_IOSTATUS status) {
  NXP20142_Context *context;
  context = (NXP20142_Context *)p_context;
/*  SiTRACE("NXP20142_MULTI_WR %d bytes at 0x%02 \n", nbBytes, address); */
  if ((unsigned int)L0_WriteBytes (context->i2c, (unsigned int)address, nbBytes, several_bytes) == nbBytes) {
    *status = 0;
  } else {
    *status = 1;
  }
}

int  NXP20142_Communication_Check (NXP20142_Context *context) {
  char*             pTunerString;
  unsigned long     ulChipVersion;
  unsigned long     ulChipId;
  int bResult;
  bResult = BLACKWIDOW_GetChipInfo( context->NXP20142_Communication, &pTunerString, &ulChipVersion, &ulChipId );
  SiTRACE("BLACKWIDOW_GetChipInfo ChipVersion %ld ChipId %ld '%s' bResult %d\n", ulChipVersion, ulChipId , pTunerString, bResult);
  return 1;
}

void  L1_RF_NXP20142_Init          (NXP20142_Context *context, unsigned int add) {
    SiTRACE_X("NXP20142_Init starting...\n");
    context->i2c = &(context->i2cObj);
    L0_Init(context->i2c);
    L0_SetAddress(context->i2c, add, 1);
    context->i2c->mustReadWithoutStop = 1;
    context->IF                   =                     0;
    context->RF                   =                950000;
    context->minRF                =                925000;
    context->maxRF                =               2175000;
    context->LPF                  =                100000;

    context->NXP20142_Config        = &(context->NXP20142_Config_Obj);
    context->NXP20142_Communication = &(context->NXP20142_Communication_Obj);
    context->NXP20142_Channel       = &(context->NXP20142_Channel_Obj);
    context->NXP20142_Communication->p_handle = (NXP20142_Context *)context;

    context->NXP20142_Communication->read        = &NXP20142_RD;
    context->NXP20142_Communication->write       = &NXP20142_WR;
    context->NXP20142_Communication->multi_write = &NXP20142_MULTI_WR;

    SAT_TUNER_InitIO(sat_generic_rd, sat_generic_wr);

    context->NXP20142_Config->eChipType                  = SAT_TUNER_CHIP_TYPE_TDA20140;
    context->NXP20142_Config->ulCrystalFrequencyHz       = 27000000;

    context->NXP20142_Channel->frequency_khz              = context->RF;
    context->NXP20142_Channel->roll_off                   = SAT_TUNER_ROLLOFF_035;
    context->NXP20142_Channel->symbol_rate_ksps           = (int)(context->LPF*2.0/1.35);
    context->NXP20142_Channel->requested_search_range_khz = 0;
    context->NXP20142_Channel->flags                      = 0;

    SiTRACE_X("L1_RF_NXP20142_Init complete...\n");
}
int   L1_RF_NXP20142_InitAfterReset(NXP20142_Context *context) {
  BLACKWIDOW_ENABLE_BLOCKS ptEnableBlocks;
  SiTRACE("L1_RF_NXP20142_InitAfterReset starting...\n");
  context->i2c->trackRead  = context->i2c->trackWrite;
  SiTRACE("L1_RF_NXP20142_InitAfterReset BLACKWIDOW_Initialize...\n");
  BLACKWIDOW_Initialize (context->NXP20142_Communication, context->NXP20142_Config);
  /* FMA configure NXP gain in mode 2*/
  SiTRACE("L1_RF_NXP20142_InitAfterReset BLACKWIDOW_SetGainMode...\n");
  BLACKWIDOW_SetGainMode (context->NXP20142_Communication, BLACKWIDOW_GAIN_MODE_2);
  SiTRACE("L1_RF_NXP20142_InitAfterReset BLACKWIDOW_GetEnableBlocks...\n");
  BLACKWIDOW_GetEnableBlocks (context->NXP20142_Communication, &ptEnableBlocks);
  ptEnableBlocks.bPowerDetect        = 1;
  SiTRACE("L1_RF_NXP20142_InitAfterReset BLACKWIDOW_SetEnableBlocks (bPowerDetect enabled)...\n");
  BLACKWIDOW_SetEnableBlocks (context->NXP20142_Communication, &ptEnableBlocks);
  SiTRACE("L1_RF_NXP20142_InitAfterReset complete...\n");
  return 0;
}
int   L1_RF_NXP20142_Get_RF        (NXP20142_Context *context) {
   return context->RF;
}

int   L1_RF_NXP20142_Tune          (NXP20142_Context *context, int rf_kHz) {
  /* Checking limits */
  if (rf_kHz < (context->minRF)) {SiTRACE("rf %d < minRF %d\n",rf_kHz ,context->minRF); return L1_RF_NXP20142_Tune(context, context->minRF);}
  if (rf_kHz > (context->maxRF)) {SiTRACE("rf %d > maxRF %d\n",rf_kHz ,context->maxRF); return L1_RF_NXP20142_Tune(context, context->maxRF);}
  context->i2c->trackRead  = context->i2c->trackWrite;

  context->RF = rf_kHz;
  context->NXP20142_Channel->frequency_khz              = context->RF;

  if ( BLACKWIDOW_Tune (context->NXP20142_Communication, context->NXP20142_Channel) != False ) {
    SiTRACE("L1_RF_NXP20142_Tune success at %ld kHz, SR %ld kbps\n", context->NXP20142_Channel->frequency_khz, context->NXP20142_Channel->symbol_rate_ksps);
  } else {
    SiTRACE("L1_RF_NXP20142_Tune failed at %ld kHz, SR %ld kbps\n", context->NXP20142_Channel->frequency_khz, context->NXP20142_Channel->symbol_rate_ksps);
    SiERROR("L1_RF_NXP20142_Tune failed\n");
  }

  return context->RF;
}

int   L1_RF_NXP20142_LPF           (NXP20142_Context *context, int lpf_khz) {
  unsigned long ulFilterRollOffConst;
  if (lpf_khz != 0) { /* use '0' to retrieve the current value */
    if ((lpf_khz > 45000)) {
      SiTRACE("NXP20142 requested lpf_khz %d higher  than max, set to max (45000)\n", lpf_khz);
      lpf_khz = 45000;
    }
    if ((lpf_khz <  4000)) {
      SiTRACE("NXP20142 requested lpf_khz %d smaller than min, set to min (4000) \n", lpf_khz);
      SiERROR("NXP20142 requested lpf_khz smaller than min, set to min (4000) \n");
      lpf_khz = 4000;
    }
    context->LPF = lpf_khz;
    switch( context->NXP20142_Channel->roll_off )
    {
        case SAT_TUNER_ROLLOFF_02:
            ulFilterRollOffConst = 120;
            break;
        case SAT_TUNER_ROLLOFF_025:
            ulFilterRollOffConst = 125;
            break;
        case SAT_TUNER_ROLLOFF_035:
            ulFilterRollOffConst = 135;
            break;
        default:
            ulFilterRollOffConst = 120;
            break;
    }
    context->NXP20142_Channel->symbol_rate_ksps = (int)( ( 72.0*(lpf_khz - 2000UL)/100 - context->NXP20142_Channel->requested_search_range_khz)*200.0/ulFilterRollOffConst );
  }

  SiTRACE("NXP20142 lpf %d kHz symbol_rate_ksps %ld\n", context->LPF, context->NXP20142_Channel->symbol_rate_ksps);

  return context->LPF;
}
/************************************************************************************************************************
  Si21xx_NXP20142_rssi function
  Use:        NXP20142 rssi function
              Used to return the received signal power based on the demodulator's if_agc
  Behavior:   This function uses 2 sets of tables to return a linear estimation of the rssi
              In each set of tables, one table corresponds to the if_agc values and the other to the corresponding input level

              for example, a series of measurements show that:
                When the input level is -92.0 dBm, the if_agc is 189
                When the input level is -74.0 dBm, the if_agc is 151

              These values are entered in the corresponding tables with matching positions in both tables.
              Looking for a function which returns rssi = f(if_agc),
               it is then easy to compute a linear estimation of the rssi for any if_agc value between 189 and 151:
                rssi = -92.0 + (if_agc - 189)*(189-151)/(-92.0 -(-74.0))

              The most complex thing to do is to compute the theoretical rssi values corresponding to
               potential if_agc values of 256 and 0, in order to be compatible with the full if_agc range (0-255)
               This is done with the same slope as in the nearest segment.
                for instance, in the original function:
                 [193 ; 189] and [-100.0 ; -92.0] define a segment which can be continued up to 256 with the same slope -> rssi = -226
                 [ 73 ;  37] and [ -20.0 ;  -9.0] define a segment which can be continued down to 0 with the same slope -> rssi =    2

              Hint: The table values may need to be calibrated to match the HW design and any existing difference with the SiLabs EVBs.
               During this process, it is also possible to increase the accurracy of the rssi level by adding intermediate points in the tables.

  Parameter:  if_agc    , the IF agc value of the demod
  Parameter:  lna_enable, a flag indicating whether the LNA of the NXP20142 is enabled
  Returns:    the rssi value
************************************************************************************************************************/
float Si21xx_NXP20142_rssi         (int if_agc, unsigned char lna_enable)   {
  int   lna_enabled_if_agc  [] = {   256,   193,  189,  185,  174,  151,  133,  129,  123,  113,  110,  103,  100,  98,   95,   86,   81,   77,   75,   74,   69,  37, 0  };
  int   lna_enabled_rssix10 [] = { -2260, -1000, -921, -890, -840, -749, -689, -663, -608, -530, -496, -452, -437,-415, -402, -322, -289, -262, -238, -221, -197, -96, 20 };
  int   lna_disabled_if_agc [] = {  256 ,   98 ,   95,   86,   78,    0  };
  int   lna_disabled_rssix10[] = { -1260,   -90,  -77,    3,   61,  660  };
  int   index;
  int   table_length;
  int  *x;
  int  *y;
  float slope;
  float rssi;

  if (if_agc>256) return -300.0;
  if (if_agc<  0) return  100.0;

  /* Selecting the rssi and if_agc tables depending on lna_enable */
  if (lna_enable) {
    x = lna_enabled_if_agc;
    y = lna_enabled_rssix10;
    table_length = sizeof(lna_enabled_if_agc)/sizeof(int);
  } else {
    x = lna_disabled_if_agc;
    y = lna_disabled_rssix10;
    table_length = sizeof(lna_disabled_if_agc)/sizeof(int);
  }
  /* Finding in which segment the if_agc value is */
  for (index = 0; index < table_length; index ++) {if (if_agc >= x[index] ) break;}
  /* Computing segment slope */
  slope = 1.0*(y[index]-y[index-1])/(x[index]-x[index-1]);
  /* Linear approximation of rssi value in segment */
  rssi  = 0.1*(y[index-1] + (if_agc - x[index-1])*slope);
  return  rssi;
}

float L1_RF_NXP20142_RSSI          (NXP20142_Context *context, int if_agc) {
 	unsigned char byteBuffer[1];
  L0_ReadBytes (context->i2c, 0x06, 1, byteBuffer);
  context->lna_enable = (byteBuffer[0]&0x80)>>7;
  context->rssi = Si21xx_NXP20142_rssi (if_agc, context->lna_enable);
  SiTRACE("L1_RF_NXP20142_RSSI: lna_enable %d , if_agc %4d -> rssi %6.1f\n", context->lna_enable, if_agc, context->rssi);
  return context->rssi;
}

unsigned char L1_RF_NXP20142_Wakeup (NXP20142_Context *context)
{
    context = context;
    return 0;
}

unsigned char L1_RF_NXP20142_Standby(NXP20142_Context *context)
{
    context = context;
    return 0;
}

char* L1_RF_NXP20142_TAG_TEXT     (void) { return (char *)"TAGNAME"; }
