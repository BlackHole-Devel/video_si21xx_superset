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
/***************************************************************************************
                  Silicon Laboratories Broadcast SiLabs_SAT_Tuner API
              for easy control of Silicon Laboratories Terrestrial tuners.


   FILE: SiLabs_SAT_Tuner_API.c

  Basically, this is a 'tuner hub' layer, allowing the user to control any supported tuner from a single API.

  To use this layer, add the code to the project and define SAT_TUNER_SILABS
  To include one supported tuner in the application, define SAT_TUNER_xxxx
  To use several different tuners, define several SAT_TUNER_xxxx
  To use several identical tuners, use xxxx_TUNER_COUNT

  The current tuner in use is selectable using
    SiLabs_SAT_Tuner_Select_Tuner (SILABS_SAT_TUNER_Context *silabs_tuner, int sat_tuner_code, int tuner_index);
    Where:
     - sat_tuner_code can be 5812, 5815, 5816 in the initial version.
       (This syntax allows any value which can be expressed in hexadecimal).
     - tuner_index is the index when using several identical tuners of the same type

  __________________________________________________________________________________________________________________________________________

  Example use case for a dual front-end with each front-end supporting a RDA5812 and a RDA5815:
  __________________________________________________________________________________________________________________________________________

   Compilation flags:

     SAT_TUNER_SILABS
     SAT_TUNER_RDA5812
     RDA5812_TUNER_COUNT 2
     SAT_TUNER_RDA5815
     RDA5815_TUNER_COUNT 2

   SW init:

      SILABS_SAT_TUNER_Context  *sat_tuner;
      SILABS_SAT_TUNER_Context   sat_tunerObj;
      sat_tuner = &sat_tunerObj;

      SiLabs_SAT_Tuner_SW_Init (sat_tuner, 0xc0);

      sat_tuner->RDA5812_Tuner[0]->i2c->address = 0x18;
      sat_tuner->RDA5815_Tuner[0]->i2c->address = 0x1a;
      sat_tuner->RDA5812_Tuner[1]->i2c->address = 0x1c;
      sat_tuner->RDA5815_Tuner[1]->i2c->address = 0x1e;

   HW init:

      SiLabs_SAT_Tuner_Select_Tuner (sat_tuner, 0x5812, 0);
      SiLabs_SAT_Tuner_HW_Connect   (sat_tuner, mode);
      SiLabs_SAT_Tuner_HW_Init      (sat_tuner);

      SiLabs_SAT_Tuner_Select_Tuner (sat_tuner, 0x5812, 0);
      SiLabs_SAT_Tuner_HW_Connect   (sat_tuner, mode);
      SiLabs_SAT_Tuner_HW_Init      (sat_tuner);

      SiLabs_SAT_Tuner_Select_Tuner (sat_tuner, 0x5815, 1);
      SiLabs_SAT_Tuner_HW_Connect   (sat_tuner, mode);
      SiLabs_SAT_Tuner_HW_Init      (sat_tuner);

      SiLabs_SAT_Tuner_Select_Tuner (sat_tuner, 0x5815, 1);
      SiLabs_SAT_Tuner_HW_Connect   (sat_tuner, mode);
      SiLabs_SAT_Tuner_HW_Init      (sat_tuner);

   HINT: When using several different tuners, after SiLabs_SAT_Tuner_SW_Init the current tuner is the first one in the arrays

   Tag:  V0.1.1
   Date: June 05 2013
****************************************************************************************/
/* Change log: */
/* Last changes:

 As from V0.2.9:
    Adding RDA SAT tuner support for RDA16110E (compiled if SAT_TUNER_RDA16110E is defined, using '0x16110E' as the sat_tuner_code)
 
 As from V0.2.8:
    Changing some char* to const char* to avoid compilation warnings on some compilers

 As from V0.2.7:
    Declaring rssi as 'signed   char   rssi' in SILABS_SAT_TUNER_Context, to get the proper sign management (rssi values are negative)
    Adding a call to L1_RF_RDA5816SD_RSSI_from_AGC in SiLabs_SAT_Tuner_RSSI_From_AGC (as from RDA5816SD svn6489)

 As from V0.2.6:
    Adding SiLabs_SAT_Tuner_SelectRF to allow controlling the RF switch in RDA5816SD/RDA16110SW
    Adding SiLabs_SAT_Tuner_LoopThrough to allow controlling the Loop Through in AV2012/AV2017/AV2018

 As from V0.2.5:
    Adding Airoha SAT tuner support for AV2017/24MHz (using the new AV2017 driver, using '0xA2017' for selection)
    Adding Airoha SAT tuner support for AV2017/27MHz (using the same driver as AV2018, but using '0xA201727' for selection)

 As from V0.2.4:
    <improvement>[RSSI] In SiLabs_SAT_Tuner_RSSI_From_AGC: returning '-1000' to indicate that the function is not supported by the current tuner.
      NB: This requires an update to the corresponding check in SiLabs_API_Demod_status_selection.

 As from V0.2.3:
    Adding Airoha SAT tuner support for AV2017 (using the same driver as AV2018, but using '0xA2018' for selection)
    <compatibility>[Tizen/int&char] explicitly declaring all 'int as 'signed int' and all 'char' as 'signed char'.
      This is because Tizen interprets 'int' as 'unsigned int' and 'char' as 'unsigned char'.
      All other OSs   interpret 'int' as 'signed   int' and 'char as 'signed char', so this change doesn't affect other compilers.
      To compare versions above V0.2.2 with older versions:
        Do not compare whitespace characters
        Either filter 'signed' or replace 'signed   int' with 'signed' and 'signed   char' with 'char' in the newer code first.
          (take care to use 3 spaces in the string to be replaced).

 As from V0.2.2:
  <compatibility>[Linux/adapter_nr] in SiLabs_SAT_Tuner_Set_Address: Using L0_SetAddress to set adapter_nr as add[15:8] (only if LINUX_I2C_Capability)

 As from V0.2.1:
  Adding SiLabs_SAT_Tuner_StandbyWithClk, to allow setting the SAT tuner in standby while keeping its clock on
   (only for SAT tuners having this capability)
   Only activated for AV2012 and AV2018 in this initial version.
   More tuners can be added if they have this capability.

 As from V0.2.0:
  Adding SiLabs_SAT_Tuner_Tag, to allow checking the tuner code version

 As from V0.1.9:
  Adding SiLabs_SAT_Tuner_Sub (to select sub-portion of dual tuners). Only for RDA5816SD/RDA16110SW.

 As from V0.1.8:
  Adding RDA5816SD/RDA16110SW support (using 0x58165D as SAT tuner code, compiled with SAT_TUNER_RDA5816SD)

 As from V0.1.7: In SiLabs_SAT_Tuner_Test: Using mode and track_mode to avoid warnings.

 As from V0.1.6: In SiLabs_SAT_Tuner_RSSI_From_AGC: Returning the value from the SAT tuner.

 As from V0.1.5:
  Adding MAX5815M support (using 0x58150 as SAT tuner code)

 As from V0.1.4:
  Adding MAX2112 SAT tuner support (using 0x2112 as SAT tuner code)

 As from V0.1.3:
  Adding Airoha SAT tuner support for AV2012/AV2018
  In SiLabs_SAT_Tuner_SW_Init: avoiding tracing SAT tuner address when no SAT tuner has been selected.

 As from V0.1.2:
  Modified to be more directly compatible with the SAT_TUNER_CUSTOMSAT framework.
  replacing 'CUSTOMSAT' all over the files should be enough to get access to a custom SAT tuner.
  The previous naming could have been mixed with the TER_TUNER_CUSTOMTER code.

 As from V0.1.1:
  RDA5812 corrections

 As from V0.0.0:
  SAT tuners supported in initial version:
    RDA5812 RDA5815 RDA5816S

*/

#include "SiLabs_SAT_Tuner_API.h"

#ifdef    SiTRACES
  #undef  SiTRACE
  #define SiTRACE(...)        SiTraceFunction(SiLEVEL, silabs_tuner->i2c->tag, __FILE__, __LINE__, __func__     ,__VA_ARGS__)
#endif /* SiTRACES */

signed   int   SiLabs_SAT_Tuner_SW_Init        (SILABS_SAT_TUNER_Context *silabs_tuner, signed   int add) {
  signed   int i;
  signed   int sat_tuner_code;
  #ifdef    SiTRACES
    char possible[1000];
  #endif /* SiTRACES */
  SiTRACE_X("SiLabs_SAT_Tuner_SW_Init\n");
  sat_tuner_code = 0;
#ifdef    SAT_TUNER_AV2012
  if (sat_tuner_code == 0) {sat_tuner_code = 0xA2012;}
  for (i=0; i< AV2012_TUNER_COUNT; i++) {
    silabs_tuner->AV2012_Tuner[i] = &(silabs_tuner->AV2012_TunerObj[i]);
    L1_RF_AV2012_Init                (silabs_tuner->AV2012_Tuner[i], add);
  }
#endif /* SAT_TUNER_AV2012 */
#ifdef    SAT_TUNER_AV2017
  if (sat_tuner_code == 0) {sat_tuner_code = 0xA2017;}
  for (i=0; i< AV2017_TUNER_COUNT; i++) {
    silabs_tuner->AV2017_Tuner[i] = &(silabs_tuner->AV2017_TunerObj[i]);
    L1_RF_AV2017_Init                (silabs_tuner->AV2017_Tuner[i], add);
  }
#endif /* SAT_TUNER_AV2017 */
#ifdef    SAT_TUNER_AV2018
  if (sat_tuner_code == 0) {sat_tuner_code = 0xA2018;}
  for (i=0; i< AV2018_TUNER_COUNT; i++) {
    silabs_tuner->AV2018_Tuner[i] = &(silabs_tuner->AV2018_TunerObj[i]);
    L1_RF_AV2018_Init                (silabs_tuner->AV2018_Tuner[i], add);
  }
#endif /* SAT_TUNER_AV2018 */
#ifdef    SAT_TUNER_CUSTOMSAT
  if (sat_tuner_code == 0) {sat_tuner_code = SAT_TUNER_CUSTOMSAT_CODE;}
  for (i=0; i< CUSTOMSAT_TUNER_COUNT; i++) {
    silabs_tuner->CUSTOMSAT_Tuner[i] = &(silabs_tuner->CUSTOMSAT_TunerObj[i]);
    L1_RF_CUSTOMSAT_Init                (silabs_tuner->CUSTOMSAT_Tuner[i], add);
  }
#endif /* SAT_TUNER_CUSTOMSAT */
#ifdef    SAT_TUNER_MAX2112
  if (sat_tuner_code == 0) {sat_tuner_code = 0x20142;}
  for (i=0; i< MAX2112_TUNER_COUNT; i++) {
    silabs_tuner->MAX2112_Tuner[i] = &(silabs_tuner->MAX2112_TunerObj[i]);
    L1_RF_MAX2112_Init                (silabs_tuner->MAX2112_Tuner[i], add);
  }
#endif /* SAT_TUNER_MAX2112 */
#ifdef    SAT_TUNER_NXP20142
  if (sat_tuner_code == 0) {sat_tuner_code = 0x20142;}
  for (i=0; i< NXP20142_TUNER_COUNT; i++) {
    silabs_tuner->NXP20142_Tuner[i] = &(silabs_tuner->NXP20142_TunerObj[i]);
    L1_RF_NXP20142_Init                (silabs_tuner->NXP20142_Tuner[i], add);
  }
#endif /* SAT_TUNER_NXP20142 */
#ifdef    SAT_TUNER_RDA5812
  if (sat_tuner_code == 0) {sat_tuner_code = 0x5812;}
  for (i=0; i< RDA5812_TUNER_COUNT; i++) {
    silabs_tuner->RDA5812_Tuner[i] = &(silabs_tuner->RDA5812_TunerObj[i]);
    L1_RF_RDA5812_Init                (silabs_tuner->RDA5812_Tuner[i], add);
  }
#endif /* SAT_TUNER_RDA5812 */
#ifdef    SAT_TUNER_RDA5815
  if (sat_tuner_code == 0) {sat_tuner_code = 0x5815;}
  for (i=0; i< RDA5815_TUNER_COUNT; i++) {
    silabs_tuner->RDA5815_Tuner[i] = &(silabs_tuner->RDA5815_TunerObj[i]);
    L1_RF_RDA5815_Init                (silabs_tuner->RDA5815_Tuner[i], add);
  }
#endif /* SAT_TUNER_RDA5815 */
#ifdef    SAT_TUNER_RDA5815M
  if (sat_tuner_code == 0) {sat_tuner_code = 0x58150;}
  for (i=0; i< RDA5815M_TUNER_COUNT; i++) {
    silabs_tuner->RDA5815M_Tuner[i] = &(silabs_tuner->RDA5815M_TunerObj[i]);
    L1_RF_RDA5815M_Init                (silabs_tuner->RDA5815M_Tuner[i], add);
  }
#endif /* SAT_TUNER_RDA5815M */
#ifdef    SAT_TUNER_RDA5816S
  if (sat_tuner_code == 0) {sat_tuner_code = 0x5816;}
  for (i=0; i< RDA5816S_TUNER_COUNT; i++) {
    silabs_tuner->RDA5816S_Tuner[i] = &(silabs_tuner->RDA5816S_TunerObj[i]);
    L1_RF_RDA5816S_Init                (silabs_tuner->RDA5816S_Tuner[i], add);
  }
#endif /* SAT_TUNER_RDA5816S */
#ifdef    SAT_TUNER_RDA5816SD
  if (sat_tuner_code == 0) {sat_tuner_code = 0x58165D;}
  for (i=0; i< RDA5816SD_TUNER_COUNT; i++) {
    silabs_tuner->RDA5816SD_Tuner[i] = &(silabs_tuner->RDA5816SD_TunerObj[i]);
    L1_RF_RDA5816SD_Init                (silabs_tuner->RDA5816SD_Tuner[i], add);
  }
#endif /* SAT_TUNER_RDA5816SD */
#ifdef    SAT_TUNER_RDA16110E
  if (sat_tuner_code == 0) {sat_tuner_code = 0x16110E;}
  for (i=0; i< RDA16110E_TUNER_COUNT; i++) {
    silabs_tuner->RDA16110E_Tuner[i] = &(silabs_tuner->RDA16110E_TunerObj[i]);
    L1_RF_RDA16110E_Init                (silabs_tuner->RDA16110E_Tuner[i], add);
  }
#endif /* SAT_TUNER_RDA16110E */
  if (sat_tuner_code != 0) {
    SiLabs_SAT_Tuner_Select_Tuner (silabs_tuner, sat_tuner_code, 0);
  } else {
  #ifdef    SiTRACES
    i = SiLabs_SAT_Tuner_Possible_Tuners(silabs_tuner, possible);
    SiTRACE_X("%d possible SAT tuners via SiLabs_SAT_Tuner: %s\n", i, possible);
  #endif /* SiTRACES */
  }
  return 0;
}
signed   int   SiLabs_SAT_Tuner_Select_Tuner   (SILABS_SAT_TUNER_Context *silabs_tuner, signed   int sat_tuner_code, signed   int tuner_index) {
  SiTRACE_X("Select SAT Tuner with code 0x%x[%d]\n", sat_tuner_code, tuner_index);
#ifdef    SAT_TUNER_AV2012
  if (sat_tuner_code               == 0xA2012 ) {
    silabs_tuner->sat_tuner_code = sat_tuner_code;
    silabs_tuner->tuner_index    = tuner_index;
    if (tuner_index > AV2012_TUNER_COUNT) {silabs_tuner->tuner_index = 0;}
    silabs_tuner->i2c            = silabs_tuner->AV2012_Tuner[silabs_tuner->tuner_index]->i2c;
  }
#endif /* SAT_TUNER_AV2012 */
#ifdef    SAT_TUNER_AV2017
  if (sat_tuner_code               == 0xA2017 ) {
    silabs_tuner->sat_tuner_code = sat_tuner_code;
    silabs_tuner->tuner_index    = tuner_index;
    if (tuner_index > AV2017_TUNER_COUNT) {silabs_tuner->tuner_index = 0;}
    silabs_tuner->i2c            = silabs_tuner->AV2017_Tuner[silabs_tuner->tuner_index]->i2c;
  }
#endif /* SAT_TUNER_AV2017 */
#ifdef    SAT_TUNER_AV2018
  if (sat_tuner_code               == 0xA201727 ) {
    SiTRACE("SAT tuner is AV2017 ==> RXIQ_out differential, then using AV2018 driver\n");
    silabs_tuner->AV2018_Tuner[silabs_tuner->tuner_index]->RXIQ_out = AV2018_RXIQ_out_differential;
    sat_tuner_code = 0xA2018;
  }
  if (sat_tuner_code               == 0xA2018 ) {
    silabs_tuner->sat_tuner_code = sat_tuner_code;
    silabs_tuner->tuner_index    = tuner_index;
    if (tuner_index > AV2018_TUNER_COUNT) {silabs_tuner->tuner_index = 0;}
    silabs_tuner->i2c            = silabs_tuner->AV2018_Tuner[silabs_tuner->tuner_index]->i2c;
  }
#endif /* SAT_TUNER_AV2018 */
#ifdef    SAT_TUNER_CUSTOMSAT
  if (sat_tuner_code               == SAT_TUNER_CUSTOMSAT_CODE ) {
    silabs_tuner->sat_tuner_code = sat_tuner_code;
    silabs_tuner->tuner_index    = tuner_index;
    if (tuner_index > CUSTOMSAT_TUNER_COUNT) {silabs_tuner->tuner_index = 0;}
    silabs_tuner->i2c            = silabs_tuner->CUSTOMSAT_Tuner[silabs_tuner->tuner_index]->i2c;
  }
#endif /* SAT_TUNER_CUSTOMSAT */
#ifdef    SAT_TUNER_MAX2112
  if (sat_tuner_code               == 0x2112 ) {
    silabs_tuner->sat_tuner_code = sat_tuner_code;
    silabs_tuner->tuner_index    = tuner_index;
    if (tuner_index > MAX2112_TUNER_COUNT) {silabs_tuner->tuner_index = 0;}
    silabs_tuner->i2c            = silabs_tuner->MAX2112_Tuner[silabs_tuner->tuner_index]->i2c;
  }
#endif /* SAT_TUNER_MAX2112 */
#ifdef    SAT_TUNER_NXP20142
  if (sat_tuner_code               == 0x20142 ) {
    silabs_tuner->sat_tuner_code = sat_tuner_code;
    silabs_tuner->tuner_index    = tuner_index;
    if (tuner_index > NXP20142_TUNER_COUNT) {silabs_tuner->tuner_index = 0;}
    silabs_tuner->i2c            = silabs_tuner->NXP20142_Tuner[silabs_tuner->tuner_index]->i2c;
  }
#endif /* SAT_TUNER_NXP20142 */
#ifdef    SAT_TUNER_RDA5812
  if (sat_tuner_code               == 0x5812 ) {
    silabs_tuner->sat_tuner_code = sat_tuner_code;
    silabs_tuner->tuner_index    = tuner_index;
    if (tuner_index > RDA5812_TUNER_COUNT) {silabs_tuner->tuner_index = 0;}
    silabs_tuner->i2c            = silabs_tuner->RDA5812_Tuner[silabs_tuner->tuner_index]->i2c;
  }
#endif /* SAT_TUNER_RDA5812 */
#ifdef    SAT_TUNER_RDA5815
  if (sat_tuner_code               == 0x5815 ) {
    silabs_tuner->sat_tuner_code = sat_tuner_code;
    silabs_tuner->tuner_index    = tuner_index;
    if (tuner_index > RDA5815_TUNER_COUNT) {silabs_tuner->tuner_index = 0;}
    silabs_tuner->i2c            = silabs_tuner->RDA5815_Tuner[silabs_tuner->tuner_index]->i2c;
  }
#endif /* SAT_TUNER_RDA5815 */
#ifdef    SAT_TUNER_RDA5815M
  if (sat_tuner_code               == 0x58150 ) {
    silabs_tuner->sat_tuner_code = sat_tuner_code;
    silabs_tuner->tuner_index    = tuner_index;
    if (tuner_index > RDA5815M_TUNER_COUNT) {silabs_tuner->tuner_index = 0;}
    silabs_tuner->i2c            = silabs_tuner->RDA5815M_Tuner[silabs_tuner->tuner_index]->i2c;
  }
#endif /* SAT_TUNER_RDA5815M */
#ifdef    SAT_TUNER_RDA5816S
  if (sat_tuner_code               == 0x5816 ) {
    silabs_tuner->sat_tuner_code = sat_tuner_code;
    silabs_tuner->tuner_index    = tuner_index;
    if (tuner_index > RDA5816S_TUNER_COUNT) {silabs_tuner->tuner_index = 0;}
    silabs_tuner->i2c            = silabs_tuner->RDA5816S_Tuner[silabs_tuner->tuner_index]->i2c;
  }
#endif /* SAT_TUNER_RDA5816S */
#ifdef    SAT_TUNER_RDA5816SD
  if (sat_tuner_code               == 0x58165D ) {
    silabs_tuner->sat_tuner_code = sat_tuner_code;
    silabs_tuner->tuner_index    = tuner_index;
    if (tuner_index > RDA5816SD_TUNER_COUNT) {silabs_tuner->tuner_index = 0;}
    silabs_tuner->i2c            = silabs_tuner->RDA5816SD_Tuner[silabs_tuner->tuner_index]->i2c;
  }
#endif /* SAT_TUNER_RDA5816SD */
#ifdef    SAT_TUNER_RDA16110E
  if (sat_tuner_code               == 0x16110E ) {
    silabs_tuner->sat_tuner_code = sat_tuner_code;
    silabs_tuner->tuner_index    = tuner_index;
    if (tuner_index > RDA16110E_TUNER_COUNT) {silabs_tuner->tuner_index = 0;}
    silabs_tuner->i2c            = silabs_tuner->RDA16110E_Tuner[silabs_tuner->tuner_index]->i2c;
  }
#endif /* SAT_TUNER_RDA16110E */
  if (silabs_tuner->sat_tuner_code != 0) {
    SiTRACE("Selected SAT tuner with code %04x[%d] (i2c address 0x%02x)\n", silabs_tuner->sat_tuner_code, silabs_tuner->tuner_index, silabs_tuner->i2c->address);
  } else {
    SiTRACE("NO SAT tuner\n");
  }
  return (silabs_tuner->sat_tuner_code<<8)+silabs_tuner->tuner_index;
}
signed   int   SiLabs_SAT_Tuner_Sub            (SILABS_SAT_TUNER_Context *silabs_tuner, signed   int sat_tuner_sub) {
  SiTRACE_X("Select SAT Tuner sub %d\n", sat_tuner_sub);
#ifdef    SAT_TUNER_RDA5816SD
  if (silabs_tuner->sat_tuner_code == 0x58165D ) {
    if (sat_tuner_sub > 0) {
      silabs_tuner->RDA5816SD_Tuner[silabs_tuner->tuner_index]->sub = 1;
    } else {
      silabs_tuner->RDA5816SD_Tuner[silabs_tuner->tuner_index]->sub = 0;
    }
    return 1;
  }
#endif /* SAT_TUNER_RDA5816SD */
  return 0;
}
signed   int   SiLabs_SAT_Tuner_Set_Address    (SILABS_SAT_TUNER_Context *silabs_tuner, signed   int add) {
  L0_SetAddress(silabs_tuner->i2c, add, 1);
  SiTRACE("SAT tuner with code %04x_Tuner[%d] (i2c address 0x%02x)\n", silabs_tuner->sat_tuner_code, silabs_tuner->tuner_index, silabs_tuner->i2c->address);
  return 1;
}

signed   int   SiLabs_SAT_Tuner_HW_Init        (SILABS_SAT_TUNER_Context *silabs_tuner) {
  signed   int return_code;
  return_code = -1;
  SiTRACE("SiLabs_SAT_Tuner_HW_Init silabs_tuner->sat_tuner_code 0x%x, %ld\n", silabs_tuner->sat_tuner_code,silabs_tuner->sat_tuner_code);
#ifdef    SAT_TUNER_AV2012
  if (silabs_tuner->sat_tuner_code == 0xA2012) {
    SiTRACE("SiLabs_SAT_Tuner_HW_Init for AV2012 at i2c 0x%02x\n", silabs_tuner->AV2012_Tuner[silabs_tuner->tuner_index]->i2c->address);
    return_code = L1_RF_AV2012_InitAfterReset(silabs_tuner->AV2012_Tuner[silabs_tuner->tuner_index]);
  }
#endif /* SAT_TUNER_AV2012 */
#ifdef    SAT_TUNER_AV2017
  if (silabs_tuner->sat_tuner_code == 0xA2017) {
    SiTRACE("SiLabs_SAT_Tuner_HW_Init for AV2017 at i2c 0x%02x\n", silabs_tuner->AV2017_Tuner[silabs_tuner->tuner_index]->i2c->address);
    return_code = L1_RF_AV2017_InitAfterReset(silabs_tuner->AV2017_Tuner[silabs_tuner->tuner_index]);
  }
#endif /* SAT_TUNER_AV2017 */
#ifdef    SAT_TUNER_AV2018
  if (silabs_tuner->sat_tuner_code == 0xA2018) {
    SiTRACE("SiLabs_SAT_Tuner_HW_Init for AV2018 at i2c 0x%02x\n", silabs_tuner->AV2018_Tuner[silabs_tuner->tuner_index]->i2c->address);
    return_code = L1_RF_AV2018_InitAfterReset(silabs_tuner->AV2018_Tuner[silabs_tuner->tuner_index]);
  }
#endif /* SAT_TUNER_AV2018 */
#ifdef    SAT_TUNER_CUSTOMSAT
  if (silabs_tuner->sat_tuner_code == SAT_TUNER_CUSTOMSAT_CODE) {
    SiTRACE("SiLabs_SAT_Tuner_HW_Init for CUSTOMSAT at i2c 0x%02x\n", silabs_tuner->CUSTOMSAT_Tuner[silabs_tuner->tuner_index]->i2c->address);
    return_code = L1_RF_CUSTOMSAT_InitAfterReset(silabs_tuner->CUSTOMSAT_Tuner[silabs_tuner->tuner_index]);
  }
#endif /* SAT_TUNER_CUSTOMSAT */
#ifdef    SAT_TUNER_MAX2112
  if (silabs_tuner->sat_tuner_code == 0x2112) {
    SiTRACE("SiLabs_SAT_Tuner_HW_Init for MAX2112 at i2c 0x%02x\n", silabs_tuner->MAX2112_Tuner[silabs_tuner->tuner_index]->i2c->address);
    return_code = L1_RF_MAX2112_InitAfterReset(silabs_tuner->MAX2112_Tuner[silabs_tuner->tuner_index]);
  }
#endif /* SAT_TUNER_MAX2112 */
#ifdef    SAT_TUNER_NXP20142
  if (silabs_tuner->sat_tuner_code == 0x20142) {
    SiTRACE("SiLabs_SAT_Tuner_HW_Init for NXP20142 at i2c 0x%02x\n", silabs_tuner->NXP20142_Tuner[silabs_tuner->tuner_index]->i2c->address);
    return_code = L1_RF_NXP20142_InitAfterReset(silabs_tuner->NXP20142_Tuner[silabs_tuner->tuner_index]);
  }
#endif /* SAT_TUNER_NXP20142 */
#ifdef    SAT_TUNER_RDA5812
  if (silabs_tuner->sat_tuner_code == 0x5812) {
    SiTRACE("SiLabs_SAT_Tuner_HW_Init for RDA5812 at i2c 0x%02x\n", silabs_tuner->RDA5812_Tuner[silabs_tuner->tuner_index]->i2c->address);
    return_code = L1_RF_RDA5812_InitAfterReset(silabs_tuner->RDA5812_Tuner[silabs_tuner->tuner_index]);
  }
#endif /* SAT_TUNER_RDA5812 */
#ifdef    SAT_TUNER_RDA5815
  if (silabs_tuner->sat_tuner_code == 0x5815) {
    SiTRACE("SiLabs_SAT_Tuner_HW_Init for RDA5815 at i2c 0x%02x\n", silabs_tuner->RDA5815_Tuner[silabs_tuner->tuner_index]->i2c->address);
    return_code = L1_RF_RDA5815_InitAfterReset(silabs_tuner->RDA5815_Tuner[silabs_tuner->tuner_index]);
  }
#endif /* SAT_TUNER_RDA5815 */
#ifdef    SAT_TUNER_RDA5815M
  if (silabs_tuner->sat_tuner_code == 0x58150) {
    SiTRACE("SiLabs_SAT_Tuner_HW_Init for RDA5815M at i2c 0x%02x\n", silabs_tuner->RDA5815M_Tuner[silabs_tuner->tuner_index]->i2c->address);
    return_code = L1_RF_RDA5815M_InitAfterReset(silabs_tuner->RDA5815M_Tuner[silabs_tuner->tuner_index]);
  }
#endif /* SAT_TUNER_RDA5815M */
#ifdef    SAT_TUNER_RDA5816S
  if (silabs_tuner->sat_tuner_code == 0x5816) {
    SiTRACE("SiLabs_SAT_Tuner_HW_Init for RDA5816 at i2c 0x%02x\n", silabs_tuner->RDA5816S_Tuner[silabs_tuner->tuner_index]->i2c->address);
    return_code = L1_RF_RDA5816S_InitAfterReset(silabs_tuner->RDA5816S_Tuner[silabs_tuner->tuner_index]);
  }
#endif /* SAT_TUNER_RDA5816S */
#ifdef    SAT_TUNER_RDA5816SD
  if (silabs_tuner->sat_tuner_code == 0x58165D) {
    SiTRACE("SiLabs_SAT_Tuner_HW_Init for RDA5816 at i2c 0x%02x\n", silabs_tuner->RDA5816SD_Tuner[silabs_tuner->tuner_index]->i2c->address);
    return_code = L1_RF_RDA5816SD_InitAfterReset(silabs_tuner->RDA5816SD_Tuner[silabs_tuner->tuner_index]);
  }
#endif /* SAT_TUNER_RDA5816SD */
#ifdef    SAT_TUNER_RDA16110E
  if (silabs_tuner->sat_tuner_code == 0x16110E) {
    SiTRACE("SiLabs_SAT_Tuner_HW_Init for RDA16110E at i2c 0x%02x\n", silabs_tuner->RDA16110E_Tuner[silabs_tuner->tuner_index]->i2c->address);
    return_code = L1_RF_RDA16110E_InitAfterReset(silabs_tuner->RDA16110E_Tuner[silabs_tuner->tuner_index]);
  }
#endif /* SAT_TUNER_RDA16110E */
  return return_code;
}
signed   int   SiLabs_SAT_Tuner_HW_Connect     (SILABS_SAT_TUNER_Context *silabs_tuner, CONNECTION_TYPE connection_mode) {
#ifdef    SAT_TUNER_AV2012
  if (silabs_tuner->sat_tuner_code == 0xA2012) { return L0_Connect(silabs_tuner->AV2012_Tuner[silabs_tuner->tuner_index]->i2c, connection_mode); }
#endif /* SAT_TUNER_AV2012 */
#ifdef    SAT_TUNER_AV2017
  if (silabs_tuner->sat_tuner_code == 0xA2017) { return L0_Connect(silabs_tuner->AV2017_Tuner[silabs_tuner->tuner_index]->i2c, connection_mode); }
#endif /* SAT_TUNER_AV2017 */
#ifdef    SAT_TUNER_AV2018
  if (silabs_tuner->sat_tuner_code == 0xA2018) { return L0_Connect(silabs_tuner->AV2018_Tuner[silabs_tuner->tuner_index]->i2c, connection_mode); }
#endif /* SAT_TUNER_AV2018 */
#ifdef    SAT_TUNER_CUSTOMSAT
  if (silabs_tuner->sat_tuner_code == SAT_TUNER_CUSTOMSAT_CODE) { return L0_Connect(silabs_tuner->CUSTOMSAT_Tuner[silabs_tuner->tuner_index]->i2c, connection_mode); }
#endif /* SAT_TUNER_CUSTOMSAT */
#ifdef    SAT_TUNER_MAX2112
  if (silabs_tuner->sat_tuner_code == 0x2112) { return L0_Connect(silabs_tuner->MAX2112_Tuner[silabs_tuner->tuner_index]->i2c, connection_mode); }
#endif /* SAT_TUNER_MAX2112 */
#ifdef    SAT_TUNER_NXP20142
  if (silabs_tuner->sat_tuner_code == 0x20142) { return L0_Connect(silabs_tuner->NXP20142_Tuner[silabs_tuner->tuner_index]->i2c, connection_mode); }
#endif /* SAT_TUNER_NXP20142 */
#ifdef    SAT_TUNER_RDA5812
  if (silabs_tuner->sat_tuner_code == 0x5812) { return L0_Connect(silabs_tuner->RDA5812_Tuner[silabs_tuner->tuner_index]->i2c, connection_mode); }
#endif /* SAT_TUNER_RDA5812 */
#ifdef    SAT_TUNER_RDA5815
  if (silabs_tuner->sat_tuner_code == 0x5815) { return L0_Connect(silabs_tuner->RDA5815_Tuner[silabs_tuner->tuner_index]->i2c, connection_mode); }
#endif /* SAT_TUNER_RDA5815 */
#ifdef    SAT_TUNER_RDA5815M
  if (silabs_tuner->sat_tuner_code == 0x58150) { return L0_Connect(silabs_tuner->RDA5815M_Tuner[silabs_tuner->tuner_index]->i2c, connection_mode); }
#endif /* SAT_TUNER_RDA5815M */
#ifdef    SAT_TUNER_RDA5816S
  if (silabs_tuner->sat_tuner_code == 0x5816) { return L0_Connect(silabs_tuner->RDA5816S_Tuner[silabs_tuner->tuner_index]->i2c, connection_mode); }
#endif /* SAT_TUNER_RDA5816S */
#ifdef    SAT_TUNER_RDA5816SD
  if (silabs_tuner->sat_tuner_code == 0x58165D) { return L0_Connect(silabs_tuner->RDA5816SD_Tuner[silabs_tuner->tuner_index]->i2c, connection_mode); }
#endif /* SAT_TUNER_RDA5816SD */
#ifdef    SAT_TUNER_RDA16110E
  if (silabs_tuner->sat_tuner_code == 0x16110E) { return L0_Connect(silabs_tuner->RDA16110E_Tuner[silabs_tuner->tuner_index]->i2c, connection_mode); }
#endif /* SAT_TUNER_RDA16110E */
  return -1;
}
signed   int   SiLabs_SAT_Tuner_bytes_trace    (SILABS_SAT_TUNER_Context *silabs_tuner, unsigned char track_mode) {
#ifdef    SAT_TUNER_AV2012
  if (silabs_tuner->sat_tuner_code == 0xA2012) { return silabs_tuner->AV2012_Tuner[silabs_tuner->tuner_index]->i2c->trackWrite = silabs_tuner->AV2012_Tuner[silabs_tuner->tuner_index]->i2c->trackRead = track_mode; }
#endif /* SAT_TUNER_AV2012 */
#ifdef    SAT_TUNER_AV2017
  if (silabs_tuner->sat_tuner_code == 0xA2017) { return silabs_tuner->AV2017_Tuner[silabs_tuner->tuner_index]->i2c->trackWrite = silabs_tuner->AV2017_Tuner[silabs_tuner->tuner_index]->i2c->trackRead = track_mode; }
#endif /* SAT_TUNER_AV2017 */
#ifdef    SAT_TUNER_AV2018
  if (silabs_tuner->sat_tuner_code == 0xA2018) { return silabs_tuner->AV2018_Tuner[silabs_tuner->tuner_index]->i2c->trackWrite = silabs_tuner->AV2018_Tuner[silabs_tuner->tuner_index]->i2c->trackRead = track_mode; }
#endif /* SAT_TUNER_AV2018 */
#ifdef    SAT_TUNER_CUSTOMSAT
  if (silabs_tuner->sat_tuner_code == SAT_TUNER_CUSTOMSAT_CODE) { return silabs_tuner->CUSTOMSAT_Tuner[silabs_tuner->tuner_index]->i2c->trackWrite = silabs_tuner->CUSTOMSAT_Tuner[silabs_tuner->tuner_index]->i2c->trackRead = track_mode; }
#endif /* SAT_TUNER_CUSTOMSAT */
#ifdef    SAT_TUNER_MAX2112
  if (silabs_tuner->sat_tuner_code == 0x2112) { return silabs_tuner->MAX2112_Tuner[silabs_tuner->tuner_index]->i2c->trackWrite = silabs_tuner->MAX2112_Tuner[silabs_tuner->tuner_index]->i2c->trackRead = track_mode; }
#endif /* SAT_TUNER_MAX2112 */
#ifdef    SAT_TUNER_NXP20142
  if (silabs_tuner->sat_tuner_code == 0x20142) { return silabs_tuner->NXP20142_Tuner[silabs_tuner->tuner_index]->i2c->trackWrite = silabs_tuner->NXP20142_Tuner[silabs_tuner->tuner_index]->i2c->trackRead = track_mode; }
#endif /* SAT_TUNER_NXP20142 */
#ifdef    SAT_TUNER_RDA5812
  if (silabs_tuner->sat_tuner_code == 0x5812) { return silabs_tuner->RDA5812_Tuner[silabs_tuner->tuner_index]->i2c->trackWrite = silabs_tuner->RDA5812_Tuner[silabs_tuner->tuner_index]->i2c->trackRead = track_mode; }
#endif /* SAT_TUNER_RDA5812 */
#ifdef    SAT_TUNER_RDA5815
  if (silabs_tuner->sat_tuner_code == 0x5815) { return silabs_tuner->RDA5815_Tuner[silabs_tuner->tuner_index]->i2c->trackWrite = silabs_tuner->RDA5815_Tuner[silabs_tuner->tuner_index]->i2c->trackRead = track_mode; }
#endif /* SAT_TUNER_RDA5815 */
#ifdef    SAT_TUNER_RDA5815M
  if (silabs_tuner->sat_tuner_code == 0x58150) { return silabs_tuner->RDA5815M_Tuner[silabs_tuner->tuner_index]->i2c->trackWrite = silabs_tuner->RDA5815M_Tuner[silabs_tuner->tuner_index]->i2c->trackRead = track_mode; }
#endif /* SAT_TUNER_RDA5815M */
#ifdef    SAT_TUNER_RDA5816S
  if (silabs_tuner->sat_tuner_code == 0x5816) { return silabs_tuner->RDA5816S_Tuner[silabs_tuner->tuner_index]->i2c->trackWrite = silabs_tuner->RDA5816S_Tuner[silabs_tuner->tuner_index]->i2c->trackRead = track_mode; }
#endif /* SAT_TUNER_RDA5816S */
#ifdef    SAT_TUNER_RDA5816SD
  if (silabs_tuner->sat_tuner_code == 0x58165D) { return silabs_tuner->RDA5816SD_Tuner[silabs_tuner->tuner_index]->i2c->trackWrite = silabs_tuner->RDA5816SD_Tuner[silabs_tuner->tuner_index]->i2c->trackRead = track_mode; }
#endif /* SAT_TUNER_RDA5816SD */
#ifdef    SAT_TUNER_RDA16110E
  if (silabs_tuner->sat_tuner_code == 0x16110E) { return silabs_tuner->RDA16110E_Tuner[silabs_tuner->tuner_index]->i2c->trackWrite = silabs_tuner->RDA16110E_Tuner[silabs_tuner->tuner_index]->i2c->trackRead = track_mode; }
#endif /* SAT_TUNER_RDA16110E */
  return -1;
}
signed   int   SiLabs_SAT_Tuner_Wakeup         (SILABS_SAT_TUNER_Context *silabs_tuner) {
#ifdef    SAT_TUNER_AV2012
  if (silabs_tuner->sat_tuner_code == 0xA2012) { return L1_RF_AV2012_Wakeup(silabs_tuner->AV2012_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_AV2012 */
#ifdef    SAT_TUNER_AV2017
  if (silabs_tuner->sat_tuner_code == 0xA2017) { return L1_RF_AV2017_Wakeup(silabs_tuner->AV2017_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_AV2017 */
#ifdef    SAT_TUNER_AV2018
  if (silabs_tuner->sat_tuner_code == 0xA2018) { return L1_RF_AV2018_Wakeup(silabs_tuner->AV2018_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_AV2018 */
#ifdef    SAT_TUNER_CUSTOMSAT
  if (silabs_tuner->sat_tuner_code == SAT_TUNER_CUSTOMSAT_CODE) { return L1_RF_CUSTOMSAT_Wakeup(silabs_tuner->CUSTOMSAT_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_CUSTOMSAT */
#ifdef    SAT_TUNER_MAX2112
  if (silabs_tuner->sat_tuner_code == 0x2112) { return 0; }
#endif /* SAT_TUNER_MAX2112 */
#ifdef    SAT_TUNER_NXP20142
  if (silabs_tuner->sat_tuner_code == 0x20142) { return L1_RF_NXP20142_Wakeup(silabs_tuner->NXP20142_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_NXP20142 */
#ifdef    SAT_TUNER_RDA5812
  if (silabs_tuner->sat_tuner_code == 0x5812) { return 0; }
#endif /* SAT_TUNER_RDA5812 */
#ifdef    SAT_TUNER_RDA5815
  if (silabs_tuner->sat_tuner_code == 0x5815) { return L1_RF_RDA5815_Wakeup(silabs_tuner->RDA5815_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_RDA5815 */
#ifdef    SAT_TUNER_RDA5815M
  if (silabs_tuner->sat_tuner_code == 0x58150) { return L1_RF_RDA5815M_Wakeup(silabs_tuner->RDA5815M_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_RDA5815M */
#ifdef    SAT_TUNER_RDA5816S
  if (silabs_tuner->sat_tuner_code == 0x5816) { return L1_RF_RDA5816S_Wakeup(silabs_tuner->RDA5816S_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_RDA5816S */
#ifdef    SAT_TUNER_RDA5816SD
  if (silabs_tuner->sat_tuner_code == 0x58165D) { return L1_RF_RDA5816SD_Wakeup(silabs_tuner->RDA5816SD_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_RDA5816SD */
#ifdef    SAT_TUNER_RDA16110E
  if (silabs_tuner->sat_tuner_code == 0x16110E) { return L1_RF_RDA16110E_Wakeup(silabs_tuner->RDA16110E_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_RDA16110E */
  return -1;
}
signed   int   SiLabs_SAT_Tuner_Standby        (SILABS_SAT_TUNER_Context *silabs_tuner) {
#ifdef    SAT_TUNER_AV2012
  if (silabs_tuner->sat_tuner_code == 0xA2012) { return L1_RF_AV2012_Standby(silabs_tuner->AV2012_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_AV2012 */
#ifdef    SAT_TUNER_AV2017
  if (silabs_tuner->sat_tuner_code == 0xA2017) { return L1_RF_AV2017_Standby(silabs_tuner->AV2017_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_AV2017 */
#ifdef    SAT_TUNER_AV2018
  if (silabs_tuner->sat_tuner_code == 0xA2018) { return L1_RF_AV2018_Standby(silabs_tuner->AV2018_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_AV2018 */
#ifdef    SAT_TUNER_CUSTOMSAT
  if (silabs_tuner->sat_tuner_code == SAT_TUNER_CUSTOMSAT_CODE) { return L1_RF_CUSTOMSAT_Standby(silabs_tuner->CUSTOMSAT_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_CUSTOMSAT */
#ifdef    SAT_TUNER_MAX2112
  if (silabs_tuner->sat_tuner_code == 0x2112) { return 0; }
#endif /* SAT_TUNER_MAX2112 */
#ifdef    SAT_TUNER_NXP20142
  if (silabs_tuner->sat_tuner_code == 0x20142) { return L1_RF_NXP20142_Standby(silabs_tuner->NXP20142_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_NXP20142 */
#ifdef    SAT_TUNER_RDA5812
  if (silabs_tuner->sat_tuner_code == 0x5812) { return 0; }
#endif /* SAT_TUNER_RDA5812 */
#ifdef    SAT_TUNER_RDA5815
  if (silabs_tuner->sat_tuner_code == 0x5815) { return L1_RF_RDA5815_Standby(silabs_tuner->RDA5815_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_RDA5815 */
#ifdef    SAT_TUNER_RDA5815M
  if (silabs_tuner->sat_tuner_code == 0x58150) { return L1_RF_RDA5815M_Standby(silabs_tuner->RDA5815M_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_RDA5815M */
#ifdef    SAT_TUNER_RDA5816S
  if (silabs_tuner->sat_tuner_code == 0x5816) { return L1_RF_RDA5816S_Standby(silabs_tuner->RDA5816S_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_RDA5816S */
#ifdef    SAT_TUNER_RDA5816SD
  if (silabs_tuner->sat_tuner_code == 0x58165D) { return L1_RF_RDA5816SD_Standby(silabs_tuner->RDA5816SD_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_RDA5816SD */
#ifdef    SAT_TUNER_RDA16110E
  if (silabs_tuner->sat_tuner_code == 0x16110E) { return L1_RF_RDA16110E_Standby(silabs_tuner->RDA16110E_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_RDA16110E */
  return -1;
}
signed   int   SiLabs_SAT_Tuner_StandbyWithClk (SILABS_SAT_TUNER_Context *silabs_tuner) {
  /* Only call SiLabs_SAT_Tuner_Standby if the SAT tuner can still generate a clock while in standby */
#ifdef    SAT_TUNER_AV2012
  if (silabs_tuner->sat_tuner_code == 0xA2012) { return SiLabs_SAT_Tuner_Standby(silabs_tuner); }
#endif /* SAT_TUNER_AV2012 */
#ifdef    SAT_TUNER_AV2017
  if (silabs_tuner->sat_tuner_code == 0xA2017) { return SiLabs_SAT_Tuner_Standby(silabs_tuner); }
#endif /* SAT_TUNER_AV2017 */
#ifdef    SAT_TUNER_AV2018
  if (silabs_tuner->sat_tuner_code == 0xA2018) { return SiLabs_SAT_Tuner_Standby(silabs_tuner); }
#endif /* SAT_TUNER_AV2018 */
#ifdef    SAT_TUNER_CUSTOMSAT
 /* <porting> Call SiLabs_TER_Tuner_Standby here only if the SAT tuner will keep its clock ON while set to Standby mode. Otherwise, return -1 */
  if (silabs_tuner->sat_tuner_code == SAT_TUNER_CUSTOMSAT_CODE) { return SiLabs_SAT_Tuner_Standby(silabs_tuner); }
#endif /* SAT_TUNER_CUSTOMSAT */
  return -1;
}
signed   int   SiLabs_SAT_Tuner_ClockOff       (SILABS_SAT_TUNER_Context *silabs_tuner) {
#ifdef    SAT_TUNER_AV2012
  if (silabs_tuner->sat_tuner_code == 0xA2012) { return 0; }
#endif /* SAT_TUNER_AV2012 */
#ifdef    SAT_TUNER_AV2017
  if (silabs_tuner->sat_tuner_code == 0xA2017) { return 0; }
#endif /* SAT_TUNER_AV2017 */
#ifdef    SAT_TUNER_AV2018
  if (silabs_tuner->sat_tuner_code == 0xA2018) { return 0; }
#endif /* SAT_TUNER_AV2018 */
#ifdef    SAT_TUNER_CUSTOMSAT
  if (silabs_tuner->sat_tuner_code == SAT_TUNER_CUSTOMSAT_CODE) { return 0; }
#endif /* SAT_TUNER_CUSTOMSAT */
#ifdef    SAT_TUNER_RDA5812
  if (silabs_tuner->sat_tuner_code == 0x5812) { return 0; }
#endif /* SAT_TUNER_RDA5812 */
#ifdef    SAT_TUNER_RDA5815
  if (silabs_tuner->sat_tuner_code == 0x5815) { return 0; }
#endif /* SAT_TUNER_RDA5815 */
#ifdef    SAT_TUNER_RDA5815M
  if (silabs_tuner->sat_tuner_code == 0x58150) { return 0; }
#endif /* SAT_TUNER_RDA5815M */
#ifdef    SAT_TUNER_RDA5816S
  if (silabs_tuner->sat_tuner_code == 0x5816) { return 0; }
#endif /* SAT_TUNER_RDA5816S */
#ifdef    SAT_TUNER_RDA5816SD
  if (silabs_tuner->sat_tuner_code == 0x58165D) { return 0; }
#endif /* SAT_TUNER_RDA5816SD */
#ifdef    SAT_TUNER_RDA16110E
  if (silabs_tuner->sat_tuner_code == 0x16110E) { return 0; }
#endif /* SAT_TUNER_RDA16110E */
  return -1;
}
signed   int   SiLabs_SAT_Tuner_ClockOn        (SILABS_SAT_TUNER_Context *silabs_tuner) {
#ifdef    SAT_TUNER_AV2012
  if (silabs_tuner->sat_tuner_code == 0xA2012) { return 0; }
#endif /* SAT_TUNER_AV2012 */
#ifdef    SAT_TUNER_AV2017
  if (silabs_tuner->sat_tuner_code == 0xA2017) { return 0; }
#endif /* SAT_TUNER_AV2017 */
#ifdef    SAT_TUNER_AV2018
  if (silabs_tuner->sat_tuner_code == 0xA2018) { return 0; }
#endif /* SAT_TUNER_AV2018 */
#ifdef    SAT_TUNER_CUSTOMSAT
  if (silabs_tuner->sat_tuner_code == SAT_TUNER_CUSTOMSAT_CODE) { return 0; }
#endif /* SAT_TUNER_CUSTOMSAT */
#ifdef    SAT_TUNER_MAX2112
  if (silabs_tuner->sat_tuner_code == 0x2112) { return 0; }
#endif /* SAT_TUNER_MAX2112 */
#ifdef    SAT_TUNER_NXP20142
  if (silabs_tuner->sat_tuner_code == 0x20142) { return 0; }
#endif /* SAT_TUNER_NXP20142 */
#ifdef    SAT_TUNER_RDA5812
  if (silabs_tuner->sat_tuner_code == 0x5812) { return 0; }
#endif /* SAT_TUNER_RDA5812 */
#ifdef    SAT_TUNER_RDA5815
  if (silabs_tuner->sat_tuner_code == 0x5815) { return 0; }
#endif /* SAT_TUNER_RDA5815 */
#ifdef    SAT_TUNER_RDA5815M
  if (silabs_tuner->sat_tuner_code == 0x58150) { return 0; }
#endif /* SAT_TUNER_RDA5815M */
#ifdef    SAT_TUNER_RDA5816S
  if (silabs_tuner->sat_tuner_code == 0x5816) { return 0; }
#endif /* SAT_TUNER_RDA5816S */
#ifdef    SAT_TUNER_RDA5816SD
  if (silabs_tuner->sat_tuner_code == 0x58165D) { return 0; }
#endif /* SAT_TUNER_RDA5816SD */
#ifdef    SAT_TUNER_RDA16110E
  if (silabs_tuner->sat_tuner_code == 0x16110E) { return 0; }
#endif /* SAT_TUNER_RDA16110E */
  return -1;
}
signed   int   SiLabs_SAT_Tuner_PowerDown      (SILABS_SAT_TUNER_Context *silabs_tuner) {
#ifdef    SAT_TUNER_AV2012
  if (silabs_tuner->sat_tuner_code == 0xA2012) { return 0; }
#endif /* SAT_TUNER_AV2012 */
#ifdef    SAT_TUNER_AV2017
  if (silabs_tuner->sat_tuner_code == 0xA2017) { return 0; }
#endif /* SAT_TUNER_AV2017 */
#ifdef    SAT_TUNER_AV2018
  if (silabs_tuner->sat_tuner_code == 0xA2018) { return 0; }
#endif /* SAT_TUNER_AV2018 */
#ifdef    SAT_TUNER_CUSTOMSAT
  if (silabs_tuner->sat_tuner_code == SAT_TUNER_CUSTOMSAT_CODE) { return 0; }
#endif /* SAT_TUNER_CUSTOMSAT */
#ifdef    SAT_TUNER_MAX2112
  if (silabs_tuner->sat_tuner_code == 0x2112) { return 0; }
#endif /* SAT_TUNER_MAX2112 */
#ifdef    SAT_TUNER_NXP20142
  if (silabs_tuner->sat_tuner_code == 0x20142) { return 0; }
#endif /* SAT_TUNER_NXP20142 */
#ifdef    SAT_TUNER_RDA5812
  if (silabs_tuner->sat_tuner_code == 0x5812) { return 0; }
#endif /* SAT_TUNER_RDA5812 */
#ifdef    SAT_TUNER_RDA5815
  if (silabs_tuner->sat_tuner_code == 0x5815) { return 0; }
#endif /* SAT_TUNER_RDA5815 */
#ifdef    SAT_TUNER_RDA5815M
  if (silabs_tuner->sat_tuner_code == 0x58150) { return 0; }
#endif /* SAT_TUNER_RDA5815M */
#ifdef    SAT_TUNER_RDA5816S
  if (silabs_tuner->sat_tuner_code == 0x5816) { return 0; }
#endif /* SAT_TUNER_RDA5816S */
#ifdef    SAT_TUNER_RDA5816SD
  if (silabs_tuner->sat_tuner_code == 0x58165D) { return 0; }
#endif /* SAT_TUNER_RDA5816SD */
#ifdef    SAT_TUNER_RDA16110E
  if (silabs_tuner->sat_tuner_code == 0x16110E) { return 0; }
#endif /* SAT_TUNER_RDA16110E */
  return -1;
}
signed   int   SiLabs_SAT_Tuner_Possible_Tuners(SILABS_SAT_TUNER_Context *silabs_tuner, char* tunerList) {
  signed   int i;
  silabs_tuner = silabs_tuner; /* To avoid compiler warning if not used */
  i = 0;
  sprintf(tunerList, "%s", "");
#ifdef    SAT_TUNER_AV2012
  sprintf(tunerList, "%s AV2012[%d]", tunerList, AV2012_TUNER_COUNT); i++;
#endif /* SAT_TUNER_AV2012 */
#ifdef    SAT_TUNER_AV2017
  sprintf(tunerList, "%s AV2017[%d]", tunerList, AV2017_TUNER_COUNT); i++;
#endif /* SAT_TUNER_AV2017 */
#ifdef    SAT_TUNER_AV2018
  sprintf(tunerList, "%s AV2018[%d]", tunerList, AV2018_TUNER_COUNT); i++;
#endif /* SAT_TUNER_AV2018 */
#ifdef    SAT_TUNER_CUSTOMSAT
  sprintf(tunerList, "%s CUSTOMSAT[%d]", tunerList, CUSTOMSAT_TUNER_COUNT); i++;
#endif /* SAT_TUNER_CUSTOMSAT */
#ifdef    SAT_TUNER_MAX2112
  sprintf(tunerList, "%s 20142[%d]", tunerList, MAX2112_TUNER_COUNT); i++;
#endif /* SAT_TUNER_MAX2112 */
#ifdef    SAT_TUNER_NXP20142
  sprintf(tunerList, "%s 20142[%d]", tunerList, NXP20142_TUNER_COUNT); i++;
#endif /* SAT_TUNER_NXP20142 */
#ifdef    SAT_TUNER_RDA5812
  sprintf(tunerList, "%s 5812[%d]" , tunerList, RDA5812_TUNER_COUNT); i++;
#endif /* SAT_TUNER_RDA5812 */
#ifdef    SAT_TUNER_RDA5815
  sprintf(tunerList, "%s 5815[%d]" , tunerList, RDA5815_TUNER_COUNT); i++;
#endif /* SAT_TUNER_RDA5815 */
#ifdef    SAT_TUNER_RDA5815M
  sprintf(tunerList, "%s 5815M(0x58150)[%d]" , tunerList, RDA5815M_TUNER_COUNT); i++;
#endif /* SAT_TUNER_RDA5815M */
#ifdef    SAT_TUNER_RDA5816S
  sprintf(tunerList, "%s 5816[%d]" , tunerList, RDA5816S_TUNER_COUNT); i++;
#endif /* SAT_TUNER_RDA5816S */
#ifdef    SAT_TUNER_RDA5816SD
  sprintf(tunerList, "%s 5816[%d]" , tunerList, RDA5816SD_TUNER_COUNT); i++;
#endif /* SAT_TUNER_RDA5816SD */
#ifdef    SAT_TUNER_RDA16110E
  sprintf(tunerList, "%s 16110[%d]" , tunerList, RDA16110E_TUNER_COUNT); i++;
#endif /* SAT_TUNER_RDA16110E */
  return i;
}
signed   int   SiLabs_SAT_Tuner_Tune           (SILABS_SAT_TUNER_Context *silabs_tuner, unsigned long freq_khz) {
#ifdef    SAT_TUNER_AV2012
  if (silabs_tuner->sat_tuner_code == 0xA2012) { return L1_RF_AV2012_Tune(silabs_tuner->AV2012_Tuner[silabs_tuner->tuner_index], freq_khz);}
#endif /* SAT_TUNER_AV2012 */
#ifdef    SAT_TUNER_AV2017
  if (silabs_tuner->sat_tuner_code == 0xA2017) { return L1_RF_AV2017_Tune(silabs_tuner->AV2017_Tuner[silabs_tuner->tuner_index], freq_khz);}
#endif /* SAT_TUNER_AV2017 */
#ifdef    SAT_TUNER_AV2018
  if (silabs_tuner->sat_tuner_code == 0xA2018) { return L1_RF_AV2018_Tune(silabs_tuner->AV2018_Tuner[silabs_tuner->tuner_index], freq_khz);}
#endif /* SAT_TUNER_AV2018 */
#ifdef    SAT_TUNER_CUSTOMSAT
  if (silabs_tuner->sat_tuner_code == SAT_TUNER_CUSTOMSAT_CODE) { return L1_RF_CUSTOMSAT_Tune(silabs_tuner->CUSTOMSAT_Tuner[silabs_tuner->tuner_index], freq_khz);}
#endif /* SAT_TUNER_CUSTOMSAT */
#ifdef    SAT_TUNER_MAX2112
  if (silabs_tuner->sat_tuner_code == 0x2112) { return L1_RF_MAX2112_Tune(silabs_tuner->MAX2112_Tuner[silabs_tuner->tuner_index], freq_khz);}
#endif /* SAT_TUNER_MAX2112 */
#ifdef    SAT_TUNER_NXP20142
  if (silabs_tuner->sat_tuner_code == 0x20142) { return L1_RF_NXP20142_Tune(silabs_tuner->NXP20142_Tuner[silabs_tuner->tuner_index], freq_khz);}
#endif /* SAT_TUNER_NXP20142 */
#ifdef    SAT_TUNER_RDA5812
  if (silabs_tuner->sat_tuner_code == 0x5812)  { return L1_RF_RDA5812_Tune (silabs_tuner->RDA5812_Tuner[silabs_tuner->tuner_index],  freq_khz);}
#endif /* SAT_TUNER_RDA5812 */
#ifdef    SAT_TUNER_RDA5815
  if (silabs_tuner->sat_tuner_code == 0x5815)  { return L1_RF_RDA5815_Tune (silabs_tuner->RDA5815_Tuner[silabs_tuner->tuner_index],  freq_khz);}
#endif /* SAT_TUNER_RDA5815 */
#ifdef    SAT_TUNER_RDA5815M
  if (silabs_tuner->sat_tuner_code == 0x58150)  { return L1_RF_RDA5815M_Tune (silabs_tuner->RDA5815M_Tuner[silabs_tuner->tuner_index],  freq_khz);}
#endif /* SAT_TUNER_RDA5815M */
#ifdef    SAT_TUNER_RDA5816S
  if (silabs_tuner->sat_tuner_code == 0x5816)  { return L1_RF_RDA5816S_Tune(silabs_tuner->RDA5816S_Tuner[silabs_tuner->tuner_index], freq_khz);}
#endif /* SAT_TUNER_RDA5816S */
#ifdef    SAT_TUNER_RDA5816SD
  if (silabs_tuner->sat_tuner_code == 0x58165D)  { return L1_RF_RDA5816SD_Tune(silabs_tuner->RDA5816SD_Tuner[silabs_tuner->tuner_index], freq_khz);}
#endif /* SAT_TUNER_RDA5816SD */
#ifdef    SAT_TUNER_RDA16110E
  if (silabs_tuner->sat_tuner_code == 0x16110E)  { return L1_RF_RDA16110E_Tune(silabs_tuner->RDA16110E_Tuner[silabs_tuner->tuner_index], freq_khz);}
#endif /* SAT_TUNER_RDA16110E */
  return 0;
}
signed   int   SiLabs_SAT_Tuner_SelectRF       (SILABS_SAT_TUNER_Context *silabs_tuner, unsigned char rf_chn)   {
#ifdef    SAT_TUNER_RDA5816SD
  if (silabs_tuner->sat_tuner_code == 0x58165D)  { return L1_RF_RDA5816SD_RfSel(silabs_tuner->RDA5816SD_Tuner[silabs_tuner->tuner_index], rf_chn);}
#endif /* SAT_TUNER_RDA5816SD */
#ifdef    SAT_TUNER_RDA16110E
  if (silabs_tuner->sat_tuner_code == 0x16110E)  { return L1_RF_RDA16110E_RfSel(silabs_tuner->RDA16110E_Tuner[silabs_tuner->tuner_index], rf_chn);}
#endif /* SAT_TUNER_RDA16110E */
  return 0;
}
signed   int   SiLabs_SAT_Tuner_LPF            (SILABS_SAT_TUNER_Context *silabs_tuner, unsigned long lpf_khz ) {
  SiTRACE("SiLabs_SAT_Tuner_LPF lpf_khz %ld (silabs_tuner->sat_tuner_code 0x%x)\n", lpf_khz, silabs_tuner->sat_tuner_code);
#ifdef    SAT_TUNER_AV2012
  if (silabs_tuner->sat_tuner_code == 0xA2012) { return L1_RF_AV2012_LPF(silabs_tuner->AV2012_Tuner[silabs_tuner->tuner_index], lpf_khz);}
#endif /* SAT_TUNER_AV2012 */
#ifdef    SAT_TUNER_AV2017
  if (silabs_tuner->sat_tuner_code == 0xA2017) { return L1_RF_AV2017_LPF(silabs_tuner->AV2017_Tuner[silabs_tuner->tuner_index], lpf_khz);}
#endif /* SAT_TUNER_AV2017 */
#ifdef    SAT_TUNER_AV2018
  if (silabs_tuner->sat_tuner_code == 0xA2018) { return L1_RF_AV2018_LPF(silabs_tuner->AV2018_Tuner[silabs_tuner->tuner_index], lpf_khz);}
#endif /* SAT_TUNER_AV2018 */
#ifdef    SAT_TUNER_CUSTOMSAT
  if (silabs_tuner->sat_tuner_code == SAT_TUNER_CUSTOMSAT_CODE) { return L1_RF_CUSTOMSAT_LPF(silabs_tuner->CUSTOMSAT_Tuner[silabs_tuner->tuner_index], lpf_khz);}
#endif /* SAT_TUNER_CUSTOMSAT */
#ifdef    SAT_TUNER_MAX2112
  if (silabs_tuner->sat_tuner_code == 0x2112) { return L1_RF_MAX2112_LPF(silabs_tuner->MAX2112_Tuner[silabs_tuner->tuner_index], lpf_khz);}
#endif /* SAT_TUNER_MAX2112 */
#ifdef    SAT_TUNER_NXP20142
  if (silabs_tuner->sat_tuner_code == 0x20142) { return L1_RF_NXP20142_LPF(silabs_tuner->NXP20142_Tuner[silabs_tuner->tuner_index], lpf_khz);}
#endif /* SAT_TUNER_NXP20142 */
#ifdef    SAT_TUNER_RDA5812
  if (silabs_tuner->sat_tuner_code == 0x5812)  { return L1_RF_RDA5812_LPF (silabs_tuner->RDA5812_Tuner[silabs_tuner->tuner_index],  lpf_khz);}
#endif /* SAT_TUNER_RDA5812 */
#ifdef    SAT_TUNER_RDA5815
  if (silabs_tuner->sat_tuner_code == 0x5815)  { return L1_RF_RDA5815_LPF (silabs_tuner->RDA5815_Tuner[silabs_tuner->tuner_index],  lpf_khz);}
#endif /* SAT_TUNER_RDA5815 */
#ifdef    SAT_TUNER_RDA5815M
  if (silabs_tuner->sat_tuner_code == 0x58150)  { return L1_RF_RDA5815M_LPF (silabs_tuner->RDA5815M_Tuner[silabs_tuner->tuner_index],  lpf_khz);}
#endif /* SAT_TUNER_RDA5815M */
#ifdef    SAT_TUNER_RDA5816S
  if (silabs_tuner->sat_tuner_code == 0x5816)  { return L1_RF_RDA5816S_LPF(silabs_tuner->RDA5816S_Tuner[silabs_tuner->tuner_index], lpf_khz);}
#endif /* SAT_TUNER_RDA5816S */
#ifdef    SAT_TUNER_RDA5816SD
  if (silabs_tuner->sat_tuner_code == 0x58165D)  { return L1_RF_RDA5816SD_LPF(silabs_tuner->RDA5816SD_Tuner[silabs_tuner->tuner_index], lpf_khz);}
#endif /* SAT_TUNER_RDA5816SD */
#ifdef    SAT_TUNER_RDA16110E
  if (silabs_tuner->sat_tuner_code == 0x16110E)  { return L1_RF_RDA16110E_LPF(silabs_tuner->RDA16110E_Tuner[silabs_tuner->tuner_index], lpf_khz);}
#endif /* SAT_TUNER_RDA16110E */
  return 0;
}
signed   int   SiLabs_SAT_Tuner_LoopThrough    (SILABS_SAT_TUNER_Context *silabs_tuner, signed   int  loop_through_enabled ) {
  SiTRACE("SiLabs_SAT_Tuner_LoopThrough loop_through_enabled %d (silabs_tuner->sat_tuner_code 0x%x)\n", loop_through_enabled, silabs_tuner->sat_tuner_code);
#ifdef    SAT_TUNER_AV2012_future
  if (silabs_tuner->sat_tuner_code == 0xA2012) { return L1_RF_AV2012_LoopThrough(silabs_tuner->AV2012_Tuner[silabs_tuner->tuner_index], loop_through_enabled);}
#endif /* SAT_TUNER_AV2012 */
#ifdef    SAT_TUNER_AV2017_future
  if (silabs_tuner->sat_tuner_code == 0xA2017) { return L1_RF_AV2017_LoopThrough(silabs_tuner->AV2017_Tuner[silabs_tuner->tuner_index], loop_through_enabled);}
#endif /* SAT_TUNER_AV2017 */
#ifdef    SAT_TUNER_AV2018
  if (silabs_tuner->sat_tuner_code == 0xA2018) { return L1_RF_AV2018_LoopThrough(silabs_tuner->AV2018_Tuner[silabs_tuner->tuner_index], loop_through_enabled);}
#endif /* SAT_TUNER_AV2018 */
  return 0;
}
signed   int   SiLabs_SAT_Tuner_Get_RF         (SILABS_SAT_TUNER_Context *silabs_tuner) {
#ifdef    SAT_TUNER_AV2012
  if (silabs_tuner->sat_tuner_code == 0xA2012) { return L1_RF_AV2012_Get_RF(silabs_tuner->AV2012_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_AV2012 */
#ifdef    SAT_TUNER_AV2017
  if (silabs_tuner->sat_tuner_code == 0xA2017) { return L1_RF_AV2017_Get_RF(silabs_tuner->AV2017_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_AV2017 */
#ifdef    SAT_TUNER_AV2018
  if (silabs_tuner->sat_tuner_code == 0xA2018) { return L1_RF_AV2018_Get_RF(silabs_tuner->AV2018_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_AV2018 */
#ifdef    SAT_TUNER_CUSTOMSAT
  if (silabs_tuner->sat_tuner_code == SAT_TUNER_CUSTOMSAT_CODE) { return L1_RF_CUSTOMSAT_Get_RF(silabs_tuner->CUSTOMSAT_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_CUSTOMSAT */
#ifdef    SAT_TUNER_MAX2112
  if (silabs_tuner->sat_tuner_code == 0x2112) { return L1_RF_MAX2112_Get_RF(silabs_tuner->MAX2112_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_MAX2112 */
#ifdef    SAT_TUNER_NXP20142
  if (silabs_tuner->sat_tuner_code == 0x20142) { return L1_RF_NXP20142_Get_RF(silabs_tuner->NXP20142_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_NXP20142 */
#ifdef    SAT_TUNER_RDA5812
  if (silabs_tuner->sat_tuner_code == 0x5812) { return L1_RF_RDA5812_Get_RF(silabs_tuner->RDA5812_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_RDA5812 */
#ifdef    SAT_TUNER_RDA5815
  if (silabs_tuner->sat_tuner_code == 0x5815) { return L1_RF_RDA5815_Get_RF(silabs_tuner->RDA5815_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_RDA5815 */
#ifdef    SAT_TUNER_RDA5815M
  if (silabs_tuner->sat_tuner_code == 0x58150) { return L1_RF_RDA5815M_Get_RF(silabs_tuner->RDA5815M_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_RDA5815M */
#ifdef    SAT_TUNER_RDA5816S
  if (silabs_tuner->sat_tuner_code == 0x5816) { return L1_RF_RDA5816S_Get_RF(silabs_tuner->RDA5816S_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_RDA5816S */
#ifdef    SAT_TUNER_RDA5816SD
  if (silabs_tuner->sat_tuner_code == 0x58165D) { return L1_RF_RDA5816SD_Get_RF(silabs_tuner->RDA5816SD_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_RDA5816SD */
#ifdef    SAT_TUNER_RDA16110E
  if (silabs_tuner->sat_tuner_code == 0x16110E) { return L1_RF_RDA16110E_Get_RF(silabs_tuner->RDA16110E_Tuner[silabs_tuner->tuner_index]); }
#endif /* SAT_TUNER_RDA16110E */
  return silabs_tuner->RF;
}
signed   int   SiLabs_SAT_Tuner_Status         (SILABS_SAT_TUNER_Context *silabs_tuner) {
  signed   int return_code;
  SiTRACE("SiLabs_SAT_Tuner_Status\n");
  return_code = -1;
#ifdef    SAT_TUNER_AV2012
  if (silabs_tuner->sat_tuner_code == 0xA2012) {
    return_code = 0;
    silabs_tuner->RF       = silabs_tuner->AV2012_Tuner[silabs_tuner->tuner_index]->RF;
    silabs_tuner->lpf_khz  = silabs_tuner->AV2012_Tuner[silabs_tuner->tuner_index]->LPF;
  }
#endif /* SAT_TUNER_AV2012 */
#ifdef    SAT_TUNER_AV2017
  if (silabs_tuner->sat_tuner_code == 0xA2017) {
    return_code = 0;
    silabs_tuner->RF       = silabs_tuner->AV2017_Tuner[silabs_tuner->tuner_index]->RF;
    silabs_tuner->lpf_khz  = silabs_tuner->AV2017_Tuner[silabs_tuner->tuner_index]->LPF;
  }
#endif /* SAT_TUNER_AV2017 */
#ifdef    SAT_TUNER_AV2018
  if (silabs_tuner->sat_tuner_code == 0xA2018) {
    return_code = 0;
    silabs_tuner->RF       = silabs_tuner->AV2018_Tuner[silabs_tuner->tuner_index]->RF;
    silabs_tuner->lpf_khz  = silabs_tuner->AV2018_Tuner[silabs_tuner->tuner_index]->LPF;
  }
#endif /* SAT_TUNER_AV2018 */
#ifdef    SAT_TUNER_CUSTOMSAT
  if (silabs_tuner->sat_tuner_code == SAT_TUNER_CUSTOMSAT_CODE) {
    return_code = 0;
    /* Keep the rssi line below in this code only if the rssi is directly retrieved from the SAT tuner */
    silabs_tuner->rssi     = L1_RF_CUSTOMSAT_RSSI  (silabs_tuner->CUSTOMSAT_Tuner[silabs_tuner->tuner_index], 0);
    silabs_tuner->RF       = silabs_tuner->CUSTOMSAT_Tuner[silabs_tuner->tuner_index]->RF;
    silabs_tuner->lpf_khz  = silabs_tuner->CUSTOMSAT_Tuner[silabs_tuner->tuner_index]->LPF;
  }
#endif /* SAT_TUNER_CUSTOMSAT */
#ifdef    SAT_TUNER_MAX2112
  if (silabs_tuner->sat_tuner_code == 0x2112) {
    return_code = 0;
    silabs_tuner->RF       = silabs_tuner->MAX2112_Tuner[silabs_tuner->tuner_index]->RF;
    silabs_tuner->lpf_khz  = silabs_tuner->MAX2112_Tuner[silabs_tuner->tuner_index]->LPF;
  }
#endif /* SAT_TUNER_MAX2112 */
#ifdef    SAT_TUNER_NXP20142
  if (silabs_tuner->sat_tuner_code == 0x20142) {
    return_code = 0;
    silabs_tuner->rssi     = L1_RF_NXP20142_RSSI  (silabs_tuner->NXP20142_Tuner[silabs_tuner->tuner_index], 0);
    silabs_tuner->RF       = silabs_tuner->NXP20142_Tuner[silabs_tuner->tuner_index]->RF;
    silabs_tuner->lpf_khz  = silabs_tuner->NXP20142_Tuner[silabs_tuner->tuner_index]->LPF;
  }
#endif /* SAT_TUNER_NXP20142 */
#ifdef    SAT_TUNER_RDA5812
  if (silabs_tuner->sat_tuner_code == 0x5812) {
    return_code = 0;
    silabs_tuner->rssi     = 0;
    silabs_tuner->RF       = silabs_tuner->RDA5812_Tuner[silabs_tuner->tuner_index]->RF;
    silabs_tuner->lpf_khz  = silabs_tuner->RDA5812_Tuner[silabs_tuner->tuner_index]->LPF;
  }
#endif /* SAT_TUNER_RDA5812 */
#ifdef    SAT_TUNER_RDA5815
  if (silabs_tuner->sat_tuner_code == 0x5815) {
    return_code = 0;
    silabs_tuner->rssi     = L1_RF_RDA5815_RSSI  (silabs_tuner->RDA5815_Tuner[silabs_tuner->tuner_index], 0);
    silabs_tuner->RF       = silabs_tuner->RDA5815_Tuner[silabs_tuner->tuner_index]->RF;
    silabs_tuner->lpf_khz  = silabs_tuner->RDA5815_Tuner[silabs_tuner->tuner_index]->LPF;
  }
#endif /* SAT_TUNER_RDA5815 */
#ifdef    SAT_TUNER_RDA5815M
  if (silabs_tuner->sat_tuner_code == 0x58150) {
    return_code = 0;
    silabs_tuner->rssi     = L1_RF_RDA5815M_RSSI  (silabs_tuner->RDA5815M_Tuner[silabs_tuner->tuner_index], 0);
    silabs_tuner->RF       = silabs_tuner->RDA5815M_Tuner[silabs_tuner->tuner_index]->RF;
    silabs_tuner->lpf_khz  = silabs_tuner->RDA5815M_Tuner[silabs_tuner->tuner_index]->LPF_kHz;
  }
#endif /* SAT_TUNER_RDA5815M */
#ifdef    SAT_TUNER_RDA5816S
  if (silabs_tuner->sat_tuner_code == 0x5816) {
    return_code = 0;
    silabs_tuner->rssi     = L1_RF_RDA5816S_RSSI  (silabs_tuner->RDA5816S_Tuner[silabs_tuner->tuner_index], 0);
    silabs_tuner->RF       = silabs_tuner->RDA5816S_Tuner[silabs_tuner->tuner_index]->RF;
    silabs_tuner->lpf_khz  = silabs_tuner->RDA5816S_Tuner[silabs_tuner->tuner_index]->LPF;
  }
#endif /* SAT_TUNER_RDA5816S */
#ifdef    SAT_TUNER_RDA5816SD
  if (silabs_tuner->sat_tuner_code == 0x58165D) {
    return_code = 0;
    silabs_tuner->rssi     = L1_RF_RDA5816SD_RSSI  (silabs_tuner->RDA5816SD_Tuner[silabs_tuner->tuner_index], 0);
    silabs_tuner->RF       = silabs_tuner->RDA5816SD_Tuner[silabs_tuner->tuner_index]->RF;
    silabs_tuner->lpf_khz  = silabs_tuner->RDA5816SD_Tuner[silabs_tuner->tuner_index]->LPF;
  }
#endif /* SAT_TUNER_RDA5816SD */
#ifdef    SAT_TUNER_RDA16110E
  if (silabs_tuner->sat_tuner_code == 0x16110E) {
    return_code = 0;
    silabs_tuner->rssi     = L1_RF_RDA16110E_RSSI  (silabs_tuner->RDA16110E_Tuner[silabs_tuner->tuner_index], 0);
    silabs_tuner->RF       = silabs_tuner->RDA16110E_Tuner[silabs_tuner->tuner_index]->RF;
    silabs_tuner->lpf_khz  = silabs_tuner->RDA16110E_Tuner[silabs_tuner->tuner_index]->LPF;
  }
#endif /* SAT_TUNER_RDA16110E */
  if (return_code == -1) {
    SiTRACE("SiLabs_SAT_Tuner_Status: unknown tuner_code 0x%04x\n", silabs_tuner->sat_tuner_code);
    SiERROR("SiLabs_SAT_Tuner_Status: unknown tuner_code\n");
  }
  return return_code;
}
const char*          SiLabs_SAT_Tuner_Tag            (SILABS_SAT_TUNER_Context *silabs_tuner) {
  SiTRACE("SiLabs_SAT_Tuner_Tag\n");
#ifdef    SAT_TUNER_AV2012
  if (silabs_tuner->sat_tuner_code == 0xA2012) { return L1_RF_AV2012_TAG_TEXT(); }
#endif /* SAT_TUNER_AV2012 */
#ifdef    SAT_TUNER_AV2017
  if (silabs_tuner->sat_tuner_code == 0xA2017) { return L1_RF_AV2017_TAG_TEXT(); }
#endif /* SAT_TUNER_AV2017 */
#ifdef    SAT_TUNER_AV2018
  if (silabs_tuner->sat_tuner_code == 0xA2018) { return L1_RF_AV2018_TAG_TEXT(); }
#endif /* SAT_TUNER_AV2018 */
#ifdef    SAT_TUNER_CUSTOMSAT
  if (silabs_tuner->sat_tuner_code == SAT_TUNER_CUSTOMSAT_CODE) { return L1_RF_CUSTOMSAT_TAG_TEXT(); }
#endif /* SAT_TUNER_CUSTOMSAT */
#ifdef    SAT_TUNER_MAX2112
  if (silabs_tuner->sat_tuner_code == 0x2112) { return L1_RF_MAX2112_TAG_TEXT(); }
#endif /* SAT_TUNER_MAX2112 */
#ifdef    SAT_TUNER_NXP20142
  if (silabs_tuner->sat_tuner_code == 0x20142) { return L1_RF_NXP20142_TAG_TEXT(); }
#endif /* SAT_TUNER_NXP20142 */
#ifdef    SAT_TUNER_RDA5812
  if (silabs_tuner->sat_tuner_code == 0x5812) { return L1_RF_RDA5812_TAG_TEXT(); }
#endif /* SAT_TUNER_RDA5812 */
#ifdef    SAT_TUNER_RDA5815
  if (silabs_tuner->sat_tuner_code == 0x5815) { return L1_RF_RDA5815_TAG_TEXT(); }
#endif /* SAT_TUNER_RDA5815 */
#ifdef    SAT_TUNER_RDA5815M
  if (silabs_tuner->sat_tuner_code == 0x58150) { return L1_RF_RDA5815M_TAG_TEXT(); }
#endif /* SAT_TUNER_RDA5815M */
#ifdef    SAT_TUNER_RDA5816S
  if (silabs_tuner->sat_tuner_code == 0x5816) { return L1_RF_RDA5816S_TAG_TEXT(); }
#endif /* SAT_TUNER_RDA5816S */
#ifdef    SAT_TUNER_RDA5816SD
  if (silabs_tuner->sat_tuner_code == 0x58165D) { return L1_RF_RDA5816SD_TAG_TEXT(); }
#endif /* SAT_TUNER_RDA5816SD */
#ifdef    SAT_TUNER_RDA16110E
  if (silabs_tuner->sat_tuner_code == 0x16110E) { return L1_RF_RDA16110E_TAG_TEXT(); }
#endif /* SAT_TUNER_RDA16110E */
  return "unknown tuner_code";
}
signed   int   SiLabs_SAT_Tuner_RSSI_From_AGC  (SILABS_SAT_TUNER_Context *silabs_tuner, signed   int agc) {
  signed   int return_code;
  SiTRACE("SiLabs_SAT_Tuner_RSSI_From_AGC agc %d\n", agc);
  return_code = -1000;
#ifdef    SAT_TUNER_AV2012
  if (silabs_tuner->sat_tuner_code == 0xA2012) {
    silabs_tuner->rssi     = L1_RF_AV2012_RSSI  (silabs_tuner->AV2012_Tuner[silabs_tuner->tuner_index], agc);
    return silabs_tuner->rssi;
  }
#endif /* SAT_TUNER_AV2012 */
#ifdef    SAT_TUNER_AV2017
  if (silabs_tuner->sat_tuner_code == 0xA2017) {
    silabs_tuner->rssi     = L1_RF_AV2017_RSSI  (silabs_tuner->AV2017_Tuner[silabs_tuner->tuner_index], agc);
    return silabs_tuner->rssi;
  }
#endif /* SAT_TUNER_AV2017 */
#ifdef    SAT_TUNER_AV2018
  if (silabs_tuner->sat_tuner_code == 0xA2018) {
    silabs_tuner->rssi     = L1_RF_AV2018_RSSI  (silabs_tuner->AV2018_Tuner[silabs_tuner->tuner_index], agc);
    return silabs_tuner->rssi;
  }
#endif /* SAT_TUNER_AV2018 */
#ifdef    SAT_TUNER_RDA5816SD
  if (silabs_tuner->sat_tuner_code == 0x58165D) {
    silabs_tuner->rssi     = L1_RF_RDA5816SD_RSSI_from_AGC  (silabs_tuner->RDA5816SD_Tuner[silabs_tuner->tuner_index], agc);
    return silabs_tuner->rssi;
  }
#endif /* SAT_TUNER_RDA5816SD */
#ifdef    SAT_TUNER_RDA16110E
  if (silabs_tuner->sat_tuner_code == 0x16110E) {
    silabs_tuner->rssi     = L1_RF_RDA16110E_RSSI_from_AGC  (silabs_tuner->RDA16110E_Tuner[silabs_tuner->tuner_index], agc);
    return silabs_tuner->rssi;
  }
#endif /* SAT_TUNER_RDA16110E */
#ifdef    SAT_TUNER_CUSTOMSAT
  /* Keep this in the code only if the rssi is retrieved based on the agc level. Otherwise, return -1 */
  if (silabs_tuner->sat_tuner_code == SAT_TUNER_CUSTOMSAT_CODE) {
    silabs_tuner->rssi     = L1_RF_CUSTOMSAT_RSSI  (silabs_tuner->CUSTOMSAT_Tuner[silabs_tuner->tuner_index], agc);
    return_code = silabs_tuner->rssi;
  }
#endif /* SAT_TUNER_CUSTOMSAT */
  SiTRACE("SiLabs_SAT_Tuner_RSSI_From_AGC return_code %d\n", return_code);
  return return_code;
}
#ifdef    SILABS_API_TEST_PIPE
/************************************************************************************************************************
  SiLabs_SAT_Tuner_Test function
  Use:        Generic test pipe function
              Used to send a generic command to the selected tuner.
  Returns:    0 if the command is unknow, 1 otherwise
  Porting:    Mostly used for debug during sw development.
************************************************************************************************************************/
signed   int   SiLabs_SAT_Tuner_Test           (SILABS_SAT_TUNER_Context *silabs_tuner, const char *target, const char *cmd, const char *sub_cmd, double dval, double *retdval, char **rettxt)
{
  CONNECTION_TYPE mode;
  signed   int track_mode;
  silabs_tuner = silabs_tuner; /* To avoid compiler warning if not used */
  *retdval   = 0;
  mode       = USB;
  track_mode = 0;
  SiTRACE("\nSiLabs_SAT_Tuner_Test %s %s %s %f...\n", target, cmd, sub_cmd, dval);
       if (strcmp_nocase(target,"help"      ) == 0) {
    sprintf(*rettxt, "\n Possible SiLabs_SAT_Tuner test commands:\n\
sat_tuner address <address>            : set the i2c address. If '0', returns the current address)\n\
");
 return 1;
  }
  else if (strcmp_nocase(target,"sat_tuner" ) == 0) {
    if (strcmp_nocase(cmd,"address"     ) == 0) {
      if ( (dval >= 0x12) & (dval <= 0xc6) ) {silabs_tuner->i2c->address = (int)dval; }
       *retdval = (double)silabs_tuner->i2c->address; sprintf(*rettxt, "0x%02x", (int)*retdval ); return 1;
    }
    if (strcmp_nocase(cmd,"init_example") == 0) {
      SILABS_SAT_TUNER_Context  *sat_tuner;
      SILABS_SAT_TUNER_Context   sat_tunerObj;
      sat_tuner = &sat_tunerObj;
      SiLabs_SAT_Tuner_SW_Init (sat_tuner, 0x18);
      #ifdef    SAT_TUNER_RDA5812
      sat_tuner->RDA5812_Tuner[0]->i2c->address = 0x18;
      #endif /* SAT_TUNER_RDA5812 */
      #ifdef    SAT_TUNER_RDA5815
      sat_tuner->RDA5815_Tuner[0]->i2c->address = 0x1c;
      #endif /* SAT_TUNER_RDA5815 */
      #ifdef    SAT_TUNER_RDA5812
      SiLabs_SAT_Tuner_Select_Tuner (sat_tuner, 0x5812, 0);
      SiLabs_SAT_Tuner_HW_Connect   (sat_tuner, mode);
      SiLabs_SAT_Tuner_bytes_trace  (sat_tuner, track_mode);
      SiLabs_SAT_Tuner_HW_Init      (sat_tuner);
      #endif /* SAT_TUNER_RDA5812 */
      #ifdef    SAT_TUNER_RDA5812
      SiLabs_SAT_Tuner_Select_Tuner (sat_tuner, 0x5812, 1);
      SiLabs_SAT_Tuner_HW_Connect   (sat_tuner, mode);
      SiLabs_SAT_Tuner_bytes_trace  (sat_tuner, track_mode);
      SiLabs_SAT_Tuner_HW_Init      (sat_tuner);
      #endif /* SAT_TUNER_RDA5812 */
      #ifdef    SAT_TUNER_RDA5815
      SiLabs_SAT_Tuner_Select_Tuner (sat_tuner, 0x5815, 0);
      SiLabs_SAT_Tuner_HW_Connect   (sat_tuner, mode);
      SiLabs_SAT_Tuner_bytes_trace  (sat_tuner, track_mode);
      SiLabs_SAT_Tuner_HW_Init      (sat_tuner);
      #endif /* SAT_TUNER_RDA5815 */
      #ifdef    SAT_TUNER_RDA5815
      SiLabs_SAT_Tuner_Select_Tuner (sat_tuner, 0x5815, 1);
      SiLabs_SAT_Tuner_HW_Connect   (sat_tuner, mode);
      SiLabs_SAT_Tuner_bytes_trace  (sat_tuner, track_mode);
      SiLabs_SAT_Tuner_HW_Init      (sat_tuner);
      #endif /* SAT_TUNER_RDA5815 */
      sprintf(*rettxt, "sw_init and hw_init done (mode %d, track_mode %d)\n", mode, track_mode);
      return 1;
    }
  }
  else {
    sprintf(*rettxt, "unknown '%s' command for silabs_tuner, can not process '%s %s %s %f'\n", cmd, target, cmd, sub_cmd, dval);
    SiTRACE(*rettxt);
    SiERROR(*rettxt);
    return 0;
  }
  return 0;
}
#endif /* SILABS_API_TEST_PIPE */
/* End of SiLabs_SAT_Tuner_API.c */

