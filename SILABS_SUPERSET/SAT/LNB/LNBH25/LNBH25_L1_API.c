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
/*                     SiLabs Layer 1                  SAT LNB controller Functions                          */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains all API Functions for the LNBH25 LNB controller                               */
/*     All functions are declared in LNBH25_L1_API.h                                                         */
/*************************************************************************************************************/
/* Change log:

  As from SVN6308:
    <correction>[status/index>1] L1_LNBH25_RegisterValue modified to cope with iI2CIndex values above 0

  As from SVN3378:
   In (LNBH25_Context *context):
  if (context->diseqc_mode == LNBH25_DISEQC_MODE_ENVELOPE) {
    L1_WRITE          (context, dsqin_mode, dsqin_mode_envelope);
  } else {
    L1_WRITE          (context, dsqin_mode, dsqin_mode_22_khz);
  }

  As from SVN3031:
   In L1_LNBH25_InitAfterReset:
    L1_WRITE          (context, dsqin_mode, dsqin_mode_envelope);
    L1_WRITE          (context, tone      , tone_enabled_via_dsqin);
    return 1;

**************************************************************************************************************/

#define Layer1_LNBH25
#include "LNBH25_L1_API.h"

unsigned char status_bytes [3];
         char LNBH25_buffer[1000];

long  L1_LNBH25_RegisterValue (int iI2CIndex, unsigned char offset, unsigned char nbbit, unsigned int isSigned, unsigned char  *registerDataBuffer) {
  int iNbBytes, i, iNbPrefixBitsToCancel;
  int lastByteIndex;
  long iVal;
  unsigned char  prefixByte, postfixByte;
  iVal = 0;

  iNbBytes = (nbbit + offset + 7)/8;

  lastByteIndex  = iI2CIndex + iNbBytes -1;

  for (i = iI2CIndex; i <= lastByteIndex; i++) { iVal = iVal + ( registerDataBuffer[i] << (8*(i-iI2CIndex))); }

  prefixByte  = registerDataBuffer[iI2CIndex];
  iNbPrefixBitsToCancel = 8*(iNbBytes) - nbbit - offset;
  prefixByte  = prefixByte  >> (8 - iNbPrefixBitsToCancel);
  prefixByte  = prefixByte  << (8 - iNbPrefixBitsToCancel);
  postfixByte = registerDataBuffer[lastByteIndex];
  postfixByte = postfixByte << (8 - offset);
  postfixByte = postfixByte >> (8 - offset);

  iVal = -( prefixByte << (8*(iNbBytes - 1))) + ( iVal ) - postfixByte ;

  /* sign bit propagation, if required */
  if (isSigned) {
    iVal = (long)iVal >> offset;
    iVal = (long)iVal << (32-nbbit);
    iVal = (long)iVal >> (32-nbbit);
  } else {
    iVal = (unsigned long)iVal >> offset;
  }

  return iVal;
}
#define LNBH25_REGVAL(register) L1_LNBH25_RegisterValue(register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_SIGNED, status_bytes)

void  L1_LNBH25_Init           (LNBH25_Context *context, unsigned int add) {
  SiTRACE("L1_LNBH25_Init starting...\n");
  context->i2c = &(context->i2cObj);

  L0_Init      (context->i2c);
  L0_SetAddress(context->i2c, add, 1);

  context->supply          = LNBH25_SUPPLY_OFF;
  context->polarization    = LNBH25_HORIZONTAL;
  context->vout_horizontal = vout_13000_mv;
  context->vout_vertical   = vout_18150_mv;
  context->diseqc_mode     = LNBH25_DISEQC_MODE_ENVELOPE;
  sprintf(context->i2c->tag, "LNBH25");
  SiTRACE("L1_LNBH25_Init complete...\n");
}

int   L1_LNBH25_InitAfterReset (LNBH25_Context *context) {
  SiTRACE("L1_LNBH25_InitAfterReset starting...\n");
  if (context->diseqc_mode == LNBH25_DISEQC_MODE_ENVELOPE) {
    L1_WRITE          (context, dsqin_mode, dsqin_mode_envelope);
  } else {
    L1_WRITE          (context, dsqin_mode, dsqin_mode_22_khz);
  }
  L1_WRITE          (context, tone      , tone_enabled_via_dsqin);
  L1_LNBH25_Supply(context,   LNBH25_SUPPLY_OFF);
  L1_LNBH25_Polarity(context, LNBH25_HORIZONTAL);
  SiTRACE("L1_LNBH25_InitAfterReset complete...\n");
  return 1;
}

char *L1_LNBH25_ContextInfo    (LNBH25_Context *context) {

  sprintf(LNBH25_buffer, "LNBH25 context information:\n");

  if (context->supply == LNBH25_SUPPLY_OFF) {sprintf(LNBH25_buffer, "%s supply OFF\n", LNBH25_buffer);}
  else                                      {sprintf(LNBH25_buffer, "%s supply ON\n" , LNBH25_buffer);}

  if      (context->polarization== LNBH25_HORIZONTAL) {sprintf(LNBH25_buffer, "%s polarization 'horizontal'\n", LNBH25_buffer);}
  else if (context->polarization== LNBH25_VERTICAL  ) {sprintf(LNBH25_buffer, "%s polarization 'vertical'\n", LNBH25_buffer);}

  if (context->vout_horizontal == vout_00000_mv) {sprintf(LNBH25_buffer, "%s voltage for 'horizontal'  0.000 V\n", LNBH25_buffer);}
  if (context->vout_horizontal == vout_13000_mv) {sprintf(LNBH25_buffer, "%s voltage for 'horizontal' 13.000 V\n", LNBH25_buffer);}
  if (context->vout_horizontal == vout_13333_mv) {sprintf(LNBH25_buffer, "%s voltage for 'horizontal' 13.333 V\n", LNBH25_buffer);}
  if (context->vout_horizontal == vout_13667_mv) {sprintf(LNBH25_buffer, "%s voltage for 'horizontal' 13.667 V\n", LNBH25_buffer);}
  if (context->vout_horizontal == vout_14000_mv) {sprintf(LNBH25_buffer, "%s voltage for 'horizontal' 14.000 V\n", LNBH25_buffer);}
  if (context->vout_horizontal == vout_14333_mv) {sprintf(LNBH25_buffer, "%s voltage for 'horizontal' 14.333 V\n", LNBH25_buffer);}
  if (context->vout_horizontal == vout_14667_mv) {sprintf(LNBH25_buffer, "%s voltage for 'horizontal' 14.667 V\n", LNBH25_buffer);}
  if (context->vout_horizontal == vout_15000_mv) {sprintf(LNBH25_buffer, "%s voltage for 'horizontal' 15.000 V\n", LNBH25_buffer);}
  if (context->vout_horizontal == vout_18150_mv) {sprintf(LNBH25_buffer, "%s voltage for 'horizontal' 18.150 V\n", LNBH25_buffer);}
  if (context->vout_horizontal == vout_18483_mv) {sprintf(LNBH25_buffer, "%s voltage for 'horizontal' 18.483 V\n", LNBH25_buffer);}
  if (context->vout_horizontal == vout_18817_mv) {sprintf(LNBH25_buffer, "%s voltage for 'horizontal' 18.817 V\n", LNBH25_buffer);}
  if (context->vout_horizontal == vout_19150_mv) {sprintf(LNBH25_buffer, "%s voltage for 'horizontal' 19.150 V\n", LNBH25_buffer);}
  if (context->vout_horizontal == vout_19483_mv) {sprintf(LNBH25_buffer, "%s voltage for 'horizontal' 19.483 V\n", LNBH25_buffer);}
  if (context->vout_horizontal == vout_19817_mv) {sprintf(LNBH25_buffer, "%s voltage for 'horizontal' 19.817 V\n", LNBH25_buffer);}
  if (context->vout_horizontal == vout_20150_mv) {sprintf(LNBH25_buffer, "%s voltage for 'horizontal' 20.150 V\n", LNBH25_buffer);}
  if (context->vout_horizontal == vout_20483_mv) {sprintf(LNBH25_buffer, "%s voltage for 'horizontal' 20.483 V\n", LNBH25_buffer);}

  if (context->vout_vertical   == vout_00000_mv) {sprintf(LNBH25_buffer, "%s voltage for 'vertical'    0.000 V\n", LNBH25_buffer);}
  if (context->vout_vertical   == vout_13000_mv) {sprintf(LNBH25_buffer, "%s voltage for 'vertical'   13.000 V\n", LNBH25_buffer);}
  if (context->vout_vertical   == vout_13333_mv) {sprintf(LNBH25_buffer, "%s voltage for 'vertical'   13.333 V\n", LNBH25_buffer);}
  if (context->vout_vertical   == vout_13667_mv) {sprintf(LNBH25_buffer, "%s voltage for 'vertical'   13.667 V\n", LNBH25_buffer);}
  if (context->vout_vertical   == vout_14000_mv) {sprintf(LNBH25_buffer, "%s voltage for 'vertical'   14.000 V\n", LNBH25_buffer);}
  if (context->vout_vertical   == vout_14333_mv) {sprintf(LNBH25_buffer, "%s voltage for 'vertical'   14.333 V\n", LNBH25_buffer);}
  if (context->vout_vertical   == vout_14667_mv) {sprintf(LNBH25_buffer, "%s voltage for 'vertical'   14.667 V\n", LNBH25_buffer);}
  if (context->vout_vertical   == vout_15000_mv) {sprintf(LNBH25_buffer, "%s voltage for 'vertical'   15.000 V\n", LNBH25_buffer);}
  if (context->vout_vertical   == vout_18150_mv) {sprintf(LNBH25_buffer, "%s voltage for 'vertical'   18.150 V\n", LNBH25_buffer);}
  if (context->vout_vertical   == vout_18483_mv) {sprintf(LNBH25_buffer, "%s voltage for 'vertical'   18.483 V\n", LNBH25_buffer);}
  if (context->vout_vertical   == vout_18817_mv) {sprintf(LNBH25_buffer, "%s voltage for 'vertical'   18.817 V\n", LNBH25_buffer);}
  if (context->vout_vertical   == vout_19150_mv) {sprintf(LNBH25_buffer, "%s voltage for 'vertical'   19.150 V\n", LNBH25_buffer);}
  if (context->vout_vertical   == vout_19483_mv) {sprintf(LNBH25_buffer, "%s voltage for 'vertical'   19.483 V\n", LNBH25_buffer);}
  if (context->vout_vertical   == vout_19817_mv) {sprintf(LNBH25_buffer, "%s voltage for 'vertical'   19.817 V\n", LNBH25_buffer);}
  if (context->vout_vertical   == vout_20150_mv) {sprintf(LNBH25_buffer, "%s voltage for 'vertical'   20.150 V\n", LNBH25_buffer);}
  if (context->vout_vertical   == vout_20483_mv) {sprintf(LNBH25_buffer, "%s voltage for 'vertical'   20.483 V\n", LNBH25_buffer);}

  if (context->diseqc_mode     == LNBH25_DISEQC_MODE_ENVELOPE) {sprintf(LNBH25_buffer, "%s DiSEqC mode 'envelope'\n", LNBH25_buffer);}
  if (context->diseqc_mode     == LNBH25_DISEQC_MODE_22_KHZ  ) {sprintf(LNBH25_buffer, "%s DiSEqC mode '22 kHz'\n"  , LNBH25_buffer);}
  return LNBH25_buffer;

}

int   L1_LNBH25_Status         (LNBH25_Context *context) {
  int nbBytes;
  unsigned char error_count;
  error_count = 0;

  nbBytes = L0_ReadBytes         (context->i2c, vout_overload_ADDRESS, 3, status_bytes);

  if (nbBytes != 3) {
   SiERROR("LNBH25 Status Error: can not read!!!\n");
   return 0xff;
  }

  context->status_overload             = LNBH25_REGVAL(vout_overload);
  context->status_low_vout_voltage     = LNBH25_REGVAL(vout_monitor);
  context->status_overcurrent          = LNBH25_REGVAL(pull_down_overcurrent);
  context->status_overtemperature      = LNBH25_REGVAL(over_temperature);
  context->status_low_vcc              = LNBH25_REGVAL(low_input_voltage);
  context->status_22khz_tone_detection = LNBH25_REGVAL(tone_on_detin);
  context->status_22khz_tone_shape     = LNBH25_REGVAL(tone_shape);
  context->status_low_vout_current     = LNBH25_REGVAL(low_vout_current);

  if   (context->status_overload           == vout_overload_triggered       ) {
   SiERROR("LNBH25 Vout overload!!!\n");
   error_count++;
  }

  if (context->status_low_vout_voltage     == vout_monitor_below_threshold  ) {
   SiERROR("LNBH25 Vout below threshold!!!\n");
   error_count++;
  }

  if (context->status_overcurrent          == pull_down_overcurrent_detected) {
   SiERROR("LNBH25 Over current!!!\n");
   error_count++;
  }

  if (context->status_overtemperature      == over_temperature_detected     ) {
   SiERROR("LNBH25 Over temperature!!!\n");
   error_count++;
  }

  if (context->status_low_vcc              == low_input_voltage_detected    ) {
   SiERROR("LNBH25 Low input voltage!!!\n");
   error_count++;
  }

  if (context->status_22khz_tone_detection == tone_on_detin_detected        ) {
    if (context->status_22khz_tone_shape     == tone_shape_out_of_specs       ) {
     SiERROR("LNBH25 Tone shape out of specs!!!\n");
     error_count++;
    }
  }

  return error_count;
}

char *L1_LNBH25_StatusInfo     (LNBH25_Context *context) {

  sprintf(LNBH25_buffer, "LNBH25 status information:\n");

  if (context->status_overload             == vout_overload_triggered       ) {sprintf(LNBH25_buffer, "%s Vout overload!!!\n"            , LNBH25_buffer);
   SiERROR("LNBH25 Vout overload!!!\n");
  } else                                                                      {sprintf(LNBH25_buffer, "%s Vout load     OK\n"            , LNBH25_buffer);}
  if (context->status_low_vout_voltage     == vout_monitor_below_threshold  ) {sprintf(LNBH25_buffer, "%s Vout below threshold!!!\n"     , LNBH25_buffer);
   SiERROR("LNBH25 Vout below threshold!!!\n");
  } else                                                                      {sprintf(LNBH25_buffer, "%s Vout voltage  OK\n"            , LNBH25_buffer);}
  if (context->status_overcurrent          == pull_down_overcurrent_detected) {sprintf(LNBH25_buffer, "%s Over current!!!\n"             , LNBH25_buffer);
   SiERROR("LNBH25 Over current!!!\n");
  } else                                                                      {sprintf(LNBH25_buffer, "%s no overcurrent\n"              , LNBH25_buffer);}
  if (context->status_overtemperature      == over_temperature_detected     ) {sprintf(LNBH25_buffer, "%s Over temperature!!!\n"         , LNBH25_buffer);
   SiERROR("LNBH25 Over temperature!!!\n");
  } else                                                                      {sprintf(LNBH25_buffer, "%s temperature   OK\n"            , LNBH25_buffer);}
  if (context->status_low_vcc              == low_input_voltage_detected    ) {sprintf(LNBH25_buffer, "%s Low input voltage!!!\n"        , LNBH25_buffer);
   SiERROR("LNBH25 Low input voltage!!!\n");
  } else                                                                      {sprintf(LNBH25_buffer, "%s input voltage OK\n"            , LNBH25_buffer);}
  if (context->status_22khz_tone_detection == tone_on_detin_detected        ) {sprintf(LNBH25_buffer, "%s Tone detected\n"               , LNBH25_buffer);
  if (context->status_22khz_tone_shape     == tone_shape_out_of_specs       ) {sprintf(LNBH25_buffer, "%s Tone shape out of specs!!!\n"  , LNBH25_buffer);
   SiERROR("LNBH25 Tone shape out of specs!!!\n");
  } else                                                                      {sprintf(LNBH25_buffer, "%s tone shape    OK\n"               , LNBH25_buffer);}
  } else                                                                      {sprintf(LNBH25_buffer, "%s no tone detected\n"            , LNBH25_buffer);}

  return LNBH25_buffer;

}

void  L1_LNBH25_Supply         (LNBH25_Context *context, unsigned char supply_off_on) {
  if (supply_off_on == LNBH25_SUPPLY_OFF) {
    context->supply  = LNBH25_SUPPLY_OFF;
    context->vout    = vout_00000_mv;
  } else {
    context->supply  = LNBH25_SUPPLY_ON;
  }
  L1_WRITE (context, vout, context->vout);
}

void  L1_LNBH25_Polarity       (LNBH25_Context *context, unsigned char horizontal_vertical) {
  if (horizontal_vertical == LNBH25_HORIZONTAL) {
    context->vout = context->vout_horizontal ;
  } else {
    context->vout = context->vout_vertical;
  }
  if (context->supply     == LNBH25_SUPPLY_ON ) {
    L1_WRITE (context, vout, context->vout);
  }
}

void  L1_LNBH25_Voltage        (LNBH25_Context *context, unsigned char voltage) {
  SiTRACE("L1_LNBH25_Voltage %d\n",voltage);
  switch (voltage) {
    case 13: context->supply = LNBH25_SUPPLY_ON; L1_LNBH25_Polarity(context, LNBH25_HORIZONTAL ); break;
    case 18: context->supply = LNBH25_SUPPLY_ON; L1_LNBH25_Polarity(context, LNBH25_VERTICAL   ); break;
    default: L1_LNBH25_Supply  (context, LNBH25_SUPPLY_OFF); break;
  }
}

char *L1_LNBH25_TAG_Text       (void) { return (char*)"TAGNAME"; }

