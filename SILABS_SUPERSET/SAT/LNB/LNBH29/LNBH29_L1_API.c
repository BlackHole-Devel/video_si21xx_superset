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
/*   This source code contains all API Functions for the LNBH29 LNB controller                               */
/*     All functions are declared in LNBH29_L1_API.h                                                         */
/*************************************************************************************************************/
/* Change log:

  As from SVN6308:
    <correction>[status/index>1] L1_LNBH29_RegisterValue modified to cope with iI2CIndex values above 0

  As from SVN3579:
   In L1_LNBH29_Voltage:
    More tolerant to voltage value (previous version only allowed 13 and 18)

  As from SVN3031:
   In L1_LNBH29_InitAfterReset:
    L1_WRITE          (context, dsqin_mode, dsqin_mode_envelope);
    L1_WRITE          (context, tone      , tone_enabled_via_dsqin);
    return 1;

**************************************************************************************************************/

#define Layer1_LNBH29
#include "LNBH29_L1_API.h"

unsigned char status_bytes [3];
         char LNBH29_buffer[1000];

long  L1_LNBH29_RegisterValue (int iI2CIndex, unsigned char offset, unsigned char nbbit, unsigned int isSigned, unsigned char  *registerDataBuffer) {
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
#define LNBH29_REGVAL(register) L1_LNBH29_RegisterValue(register##_ADDRESS, register##_OFFSET, register##_NBBIT, register##_SIGNED, status_bytes)

void  L1_LNBH29_Init           (LNBH29_Context *context, unsigned int add) {
  SiTRACE("L1_LNBH29_Init starting...\n");
  context->i2c = &(context->i2cObj);

  L0_Init      (context->i2c);
  L0_SetAddress(context->i2c, add, 1);

  context->supply          = LNBH29_SUPPLY_OFF;
  context->polarization    = LNBH29_HORIZONTAL;
  context->vout_horizontal = vout_13000_mv;
  context->vout_vertical   = vout_18150_mv;
  SiTRACE("L1_LNBH29_Init complete...\n");
}

int   L1_LNBH29_InitAfterReset (LNBH29_Context *context) {
  SiTRACE("L1_LNBH29_InitAfterReset starting...\n");
  L1_LNBH29_Supply(context,   LNBH29_SUPPLY_OFF);
  L1_LNBH29_Polarity(context, LNBH29_HORIZONTAL);
  SiTRACE("L1_LNBH29_InitAfterReset complete...\n");
  return 1;
}

char *L1_LNBH29_ContextInfo    (LNBH29_Context *context) {

  sprintf(LNBH29_buffer, "LNBH29 context information:\n");

  if (context->supply == LNBH29_SUPPLY_OFF) {sprintf(LNBH29_buffer, "%s supply OFF\n", LNBH29_buffer);}
  else                                      {sprintf(LNBH29_buffer, "%s supply ON\n" , LNBH29_buffer);}

  if      (context->polarization== LNBH29_HORIZONTAL) {sprintf(LNBH29_buffer, "%s polarization 'horizontal'\n", LNBH29_buffer);}
  else if (context->polarization== LNBH29_VERTICAL  ) {sprintf(LNBH29_buffer, "%s polarization 'vertical'\n", LNBH29_buffer);}

  if (context->vout_horizontal == vout_00000_mv) {sprintf(LNBH29_buffer, "%s voltage for 'horizontal'  0.000 V\n", LNBH29_buffer);}
  if (context->vout_horizontal == vout_13000_mv) {sprintf(LNBH29_buffer, "%s voltage for 'horizontal' 13.000 V\n", LNBH29_buffer);}
  if (context->vout_horizontal == vout_13333_mv) {sprintf(LNBH29_buffer, "%s voltage for 'horizontal' 13.333 V\n", LNBH29_buffer);}
  if (context->vout_horizontal == vout_13667_mv) {sprintf(LNBH29_buffer, "%s voltage for 'horizontal' 13.667 V\n", LNBH29_buffer);}
  if (context->vout_horizontal == vout_18150_mv) {sprintf(LNBH29_buffer, "%s voltage for 'horizontal' 18.150 V\n", LNBH29_buffer);}
  if (context->vout_horizontal == vout_18483_mv) {sprintf(LNBH29_buffer, "%s voltage for 'horizontal' 18.483 V\n", LNBH29_buffer);}
  if (context->vout_horizontal == vout_18817_mv) {sprintf(LNBH29_buffer, "%s voltage for 'horizontal' 18.817 V\n", LNBH29_buffer);}

  if (context->vout_vertical   == vout_00000_mv) {sprintf(LNBH29_buffer, "%s voltage for 'vertical'    0.000 V\n", LNBH29_buffer);}
  if (context->vout_vertical   == vout_13000_mv) {sprintf(LNBH29_buffer, "%s voltage for 'vertical'   13.000 V\n", LNBH29_buffer);}
  if (context->vout_vertical   == vout_13333_mv) {sprintf(LNBH29_buffer, "%s voltage for 'vertical'   13.333 V\n", LNBH29_buffer);}
  if (context->vout_vertical   == vout_13667_mv) {sprintf(LNBH29_buffer, "%s voltage for 'vertical'   13.667 V\n", LNBH29_buffer);}
  if (context->vout_vertical   == vout_18150_mv) {sprintf(LNBH29_buffer, "%s voltage for 'vertical'   18.150 V\n", LNBH29_buffer);}
  if (context->vout_vertical   == vout_18483_mv) {sprintf(LNBH29_buffer, "%s voltage for 'vertical'   18.483 V\n", LNBH29_buffer);}
  if (context->vout_vertical   == vout_18817_mv) {sprintf(LNBH29_buffer, "%s voltage for 'vertical'   18.817 V\n", LNBH29_buffer);}

  return LNBH29_buffer;

}

int   L1_LNBH29_Status         (LNBH29_Context *context) {
  int nbBytes;
  unsigned char error_count;
  error_count = 0;

  nbBytes = L0_ReadBytes         (context->i2c, vout_overload_ADDRESS, 3, status_bytes);

  if (nbBytes != 3) {
   SiERROR("LNBH29 Status Error: can not read!!!\n");
   return 0xff;
  }

  context->status_overload             = LNBH29_REGVAL(vout_overload);
  context->status_low_vout_voltage     = LNBH29_REGVAL(vout_monitor);
  context->status_overcurrent          = LNBH29_REGVAL(pull_down_overcurrent);
  context->status_overtemperature      = LNBH29_REGVAL(over_temperature);
  context->status_low_vcc              = LNBH29_REGVAL(low_input_voltage);

  if   (context->status_overload           == vout_overload_triggered       ) {
   SiERROR("LNBH29 Vout overload!!!\n");
   error_count++;
  }

  if (context->status_low_vout_voltage     == vout_monitor_below_threshold  ) {
   SiERROR("LNBH29 Vout below threshold!!!\n");
   error_count++;
  }

  if (context->status_overcurrent          == pull_down_overcurrent_detected) {
   SiERROR("LNBH29 Over current!!!\n");
   error_count++;
  }

  if (context->status_overtemperature      == over_temperature_detected     ) {
   SiERROR("LNBH29 Over temperature!!!\n");
   error_count++;
  }

  if (context->status_low_vcc              == low_input_voltage_detected    ) {
   SiERROR("LNBH29 Low input voltage!!!\n");
   error_count++;
  }

  return error_count;
}

char *L1_LNBH29_StatusInfo     (LNBH29_Context *context) {

  sprintf(LNBH29_buffer, "LNBH29 status information:\n");

  if (context->status_overload             == vout_overload_triggered       ) {sprintf(LNBH29_buffer, "%s Vout overload!!!\n"            , LNBH29_buffer);
   SiERROR("LNBH29 Vout overload!!!\n");
  } else                                                                      {sprintf(LNBH29_buffer, "%s Vout load     OK\n"            , LNBH29_buffer);}
  if (context->status_low_vout_voltage     == vout_monitor_below_threshold  ) {sprintf(LNBH29_buffer, "%s Vout below threshold!!!\n"     , LNBH29_buffer);
   SiERROR("LNBH29 Vout below threshold!!!\n");
  } else                                                                      {sprintf(LNBH29_buffer, "%s Vout voltage  OK\n"            , LNBH29_buffer);}
  if (context->status_overcurrent          == pull_down_overcurrent_detected) {sprintf(LNBH29_buffer, "%s Over current!!!\n"             , LNBH29_buffer);
   SiERROR("LNBH29 Over current!!!\n");
  } else                                                                      {sprintf(LNBH29_buffer, "%s no overcurrent\n"              , LNBH29_buffer);}
  if (context->status_overtemperature      == over_temperature_detected     ) {sprintf(LNBH29_buffer, "%s Over temperature!!!\n"         , LNBH29_buffer);
   SiERROR("LNBH29 Over temperature!!!\n");
  } else                                                                      {sprintf(LNBH29_buffer, "%s temperature   OK\n"            , LNBH29_buffer);}
  if (context->status_low_vcc              == low_input_voltage_detected    ) {sprintf(LNBH29_buffer, "%s Low input voltage!!!\n"        , LNBH29_buffer);
   SiERROR("LNBH29 Low input voltage!!!\n");
  }

  return LNBH29_buffer;

}

void  L1_LNBH29_Supply         (LNBH29_Context *context, unsigned char supply_off_on) {
  if (supply_off_on == LNBH29_SUPPLY_OFF) {
    context->supply  = LNBH29_SUPPLY_OFF;
    context->vout    = vout_00000_mv;
  } else {
    context->supply  = LNBH29_SUPPLY_ON;
  }
  L1_WRITE (context, vout, context->vout);
}

void  L1_LNBH29_Polarity       (LNBH29_Context *context, unsigned char horizontal_vertical) {
  if (horizontal_vertical == LNBH29_HORIZONTAL) {
    context->vout = context->vout_horizontal ;
  } else {
    context->vout = context->vout_vertical;
  }
  if (context->supply     == LNBH29_SUPPLY_ON ) {
    L1_WRITE (context, vout, context->vout);
  }
}

void  L1_LNBH29_Voltage        (LNBH29_Context *context, unsigned char voltage) {
         if (voltage < 12) {
    L1_LNBH29_Supply  (context, LNBH29_SUPPLY_OFF);
  } else if (voltage < 17) {
    context->supply = LNBH29_SUPPLY_ON;
    L1_LNBH29_Polarity(context, LNBH29_VERTICAL);
  } else {
    context->supply = LNBH29_SUPPLY_ON;
    L1_LNBH29_Polarity(context, LNBH29_HORIZONTAL);
  }
}

char *L1_LNBH29_TAG_Text       (void) { return (char*)"TAGNAME"; }

