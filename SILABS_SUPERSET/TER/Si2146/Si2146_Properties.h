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
/*************************************************************************************
                  Silicon Laboratories Broadcast Si2146 Layer 1 API
   API properties structures and functions definitions
   FILE: Si2146_Properties.h
   Supported IC : Si2146
   Compiled for ROM 11 firmware 1_1_build_3
   Revision: 0.1
   Date: December 23 2011
**************************************************************************************/
#ifndef   _Si2146_PROPERTIES_H_
#define   _Si2146_PROPERTIES_H_

/* _properties_defines_insertion_start */
/* Si2146 ATV_AFC_RANGE property definition */
#define   Si2146_ATV_AFC_RANGE_PROP 0x0610

#ifdef    Si2146_ATV_AFC_RANGE_PROP
  #define Si2146_ATV_AFC_RANGE_PROP_CODE 0x000610


    typedef struct { /* Si2146_ATV_AFC_RANGE_PROP_struct */
      unsigned int    range_khz;
   } Si2146_ATV_AFC_RANGE_PROP_struct;

   /* ATV_AFC_RANGE property, RANGE_KHZ field definition (NO TITLE)*/
   #define  Si2146_ATV_AFC_RANGE_PROP_RANGE_KHZ_LSB         0
   #define  Si2146_ATV_AFC_RANGE_PROP_RANGE_KHZ_MASK        0xffff
   #define  Si2146_ATV_AFC_RANGE_PROP_RANGE_KHZ_DEFAULT    1000
    #define Si2146_ATV_AFC_RANGE_PROP_RANGE_KHZ_100_KHZ   100
    #define Si2146_ATV_AFC_RANGE_PROP_RANGE_KHZ_500_KHZ   500
    #define Si2146_ATV_AFC_RANGE_PROP_RANGE_KHZ_1000_KHZ  1000
    #define Si2146_ATV_AFC_RANGE_PROP_RANGE_KHZ_1500_KHZ  1500
    #define Si2146_ATV_AFC_RANGE_PROP_RANGE_KHZ_2000_KHZ  2000

#endif /* Si2146_ATV_AFC_RANGE_PROP */

/* Si2146 ATV_AF_OUT property definition */
#define   Si2146_ATV_AF_OUT_PROP 0x060b

#ifdef    Si2146_ATV_AF_OUT_PROP
  #define Si2146_ATV_AF_OUT_PROP_CODE 0x00060b


    typedef struct { /* Si2146_ATV_AF_OUT_PROP_struct */
      unsigned char   volume;
   } Si2146_ATV_AF_OUT_PROP_struct;

   /* ATV_AF_OUT property, VOLUME field definition (NO TITLE)*/
   #define  Si2146_ATV_AF_OUT_PROP_VOLUME_LSB         0
   #define  Si2146_ATV_AF_OUT_PROP_VOLUME_MASK        0x3f
   #define  Si2146_ATV_AF_OUT_PROP_VOLUME_DEFAULT    0
    #define Si2146_ATV_AF_OUT_PROP_VOLUME_VOLUME_MIN  0
    #define Si2146_ATV_AF_OUT_PROP_VOLUME_VOLUME_MAX  63

#endif /* Si2146_ATV_AF_OUT_PROP */

/* Si2146 ATV_AGC_SPEED property definition */
#define   Si2146_ATV_AGC_SPEED_PROP 0x0611

#ifdef    Si2146_ATV_AGC_SPEED_PROP
  #define Si2146_ATV_AGC_SPEED_PROP_CODE 0x000611


    typedef struct { /* Si2146_ATV_AGC_SPEED_PROP_struct */
      unsigned char   if_agc_speed;
   } Si2146_ATV_AGC_SPEED_PROP_struct;

   /* ATV_AGC_SPEED property, IF_AGC_SPEED field definition (NO TITLE)*/
   #define  Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB         0
   #define  Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK        0xff
   #define  Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_DEFAULT    0
    #define Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO  0
    #define Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_89    89
    #define Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_105   105
    #define Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_121   121
    #define Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_137   137
    #define Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_158   158
    #define Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_172   172
    #define Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_185   185
    #define Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_196   196
    #define Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_206   206
    #define Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_216   216
    #define Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_219   219
    #define Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_222   222
    #define Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_248   248
    #define Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_250   250
    #define Si2146_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_251   251

#endif /* Si2146_ATV_AGC_SPEED_PROP */

/* Si2146 ATV_AUDIO_MODE property definition */
#define   Si2146_ATV_AUDIO_MODE_PROP 0x0602

#ifdef    Si2146_ATV_AUDIO_MODE_PROP
  #define Si2146_ATV_AUDIO_MODE_PROP_CODE 0x000602


    typedef struct { /* Si2146_ATV_AUDIO_MODE_PROP_struct */
      unsigned char   audio_sys;
      unsigned char   chan_bw;
      unsigned char   demod_mode;
   } Si2146_ATV_AUDIO_MODE_PROP_struct;

   /* ATV_AUDIO_MODE property, AUDIO_SYS field definition (NO TITLE)*/
   #define  Si2146_ATV_AUDIO_MODE_PROP_AUDIO_SYS_LSB         0
   #define  Si2146_ATV_AUDIO_MODE_PROP_AUDIO_SYS_MASK        0x0f
   #define  Si2146_ATV_AUDIO_MODE_PROP_AUDIO_SYS_DEFAULT    0
    #define Si2146_ATV_AUDIO_MODE_PROP_AUDIO_SYS_DEFAULT     0
    #define Si2146_ATV_AUDIO_MODE_PROP_AUDIO_SYS_MONO        1
    #define Si2146_ATV_AUDIO_MODE_PROP_AUDIO_SYS_MONO_NICAM  2
    #define Si2146_ATV_AUDIO_MODE_PROP_AUDIO_SYS_A2          3
    #define Si2146_ATV_AUDIO_MODE_PROP_AUDIO_SYS_A2_DK2      4
    #define Si2146_ATV_AUDIO_MODE_PROP_AUDIO_SYS_A2_DK3      5
    #define Si2146_ATV_AUDIO_MODE_PROP_AUDIO_SYS_BTSC        6
    #define Si2146_ATV_AUDIO_MODE_PROP_AUDIO_SYS_EIAJ        7
    #define Si2146_ATV_AUDIO_MODE_PROP_AUDIO_SYS_SCAN        8
    #define Si2146_ATV_AUDIO_MODE_PROP_AUDIO_SYS_A2_DK4      9
    #define Si2146_ATV_AUDIO_MODE_PROP_AUDIO_SYS_WIDE_SCAN   10

   /* ATV_AUDIO_MODE property, CHAN_BW field definition (NO TITLE)*/
   #define  Si2146_ATV_AUDIO_MODE_PROP_CHAN_BW_LSB         8
   #define  Si2146_ATV_AUDIO_MODE_PROP_CHAN_BW_MASK        0x0f
   #define  Si2146_ATV_AUDIO_MODE_PROP_CHAN_BW_DEFAULT    0
    #define Si2146_ATV_AUDIO_MODE_PROP_CHAN_BW_DEFAULT         0
    #define Si2146_ATV_AUDIO_MODE_PROP_CHAN_BW_4X_OVERMOD      1
    #define Si2146_ATV_AUDIO_MODE_PROP_CHAN_BW_8X_OVERMOD      2
    #define Si2146_ATV_AUDIO_MODE_PROP_CHAN_BW_12X_OVERMOD     3
    #define Si2146_ATV_AUDIO_MODE_PROP_CHAN_BW_7P5_KHZ_OFFSET  4
    #define Si2146_ATV_AUDIO_MODE_PROP_CHAN_BW_15_KHZ_OFFSET   5
    #define Si2146_ATV_AUDIO_MODE_PROP_CHAN_BW_30_KHZ_OFFSET   6
    #define Si2146_ATV_AUDIO_MODE_PROP_CHAN_BW_75_KHZ_OFFSET   7
    #define Si2146_ATV_AUDIO_MODE_PROP_CHAN_BW_150_KHZ_OFFSET  8

   /* ATV_AUDIO_MODE property, DEMOD_MODE field definition (NO TITLE)*/
   #define  Si2146_ATV_AUDIO_MODE_PROP_DEMOD_MODE_LSB         4
   #define  Si2146_ATV_AUDIO_MODE_PROP_DEMOD_MODE_MASK        0x03
   #define  Si2146_ATV_AUDIO_MODE_PROP_DEMOD_MODE_DEFAULT    0
    #define Si2146_ATV_AUDIO_MODE_PROP_DEMOD_MODE_SIF  0
    #define Si2146_ATV_AUDIO_MODE_PROP_DEMOD_MODE_AM   1
    #define Si2146_ATV_AUDIO_MODE_PROP_DEMOD_MODE_FM1  2
    #define Si2146_ATV_AUDIO_MODE_PROP_DEMOD_MODE_FM2  3

#endif /* Si2146_ATV_AUDIO_MODE_PROP */

/* Si2146 ATV_CVBS_OUT property definition */
#define   Si2146_ATV_CVBS_OUT_PROP 0x0609

#ifdef    Si2146_ATV_CVBS_OUT_PROP
  #define Si2146_ATV_CVBS_OUT_PROP_CODE 0x000609


    typedef struct { /* Si2146_ATV_CVBS_OUT_PROP_struct */
      unsigned char   amp;
      unsigned char   offset;
   } Si2146_ATV_CVBS_OUT_PROP_struct;

   /* ATV_CVBS_OUT property, AMP field definition (NO TITLE)*/
   #define  Si2146_ATV_CVBS_OUT_PROP_AMP_LSB         8
   #define  Si2146_ATV_CVBS_OUT_PROP_AMP_MASK        0xff
   #define  Si2146_ATV_CVBS_OUT_PROP_AMP_DEFAULT    200
    #define Si2146_ATV_CVBS_OUT_PROP_AMP_AMP_MIN  0
    #define Si2146_ATV_CVBS_OUT_PROP_AMP_AMP_MAX  255

   /* ATV_CVBS_OUT property, OFFSET field definition (NO TITLE)*/
   #define  Si2146_ATV_CVBS_OUT_PROP_OFFSET_LSB         0
   #define  Si2146_ATV_CVBS_OUT_PROP_OFFSET_MASK        0xff
   #define  Si2146_ATV_CVBS_OUT_PROP_OFFSET_DEFAULT    25
    #define Si2146_ATV_CVBS_OUT_PROP_OFFSET_OFFSET_MIN  0
    #define Si2146_ATV_CVBS_OUT_PROP_OFFSET_OFFSET_MAX  255

#endif /* Si2146_ATV_CVBS_OUT_PROP */

/* Si2146 ATV_CVBS_OUT_FINE property definition */
#define   Si2146_ATV_CVBS_OUT_FINE_PROP 0x0614

#ifdef    Si2146_ATV_CVBS_OUT_FINE_PROP
  #define Si2146_ATV_CVBS_OUT_FINE_PROP_CODE 0x000614


    typedef struct { /* Si2146_ATV_CVBS_OUT_FINE_PROP_struct */
      unsigned char   amp;
               char   offset;
   } Si2146_ATV_CVBS_OUT_FINE_PROP_struct;

   /* ATV_CVBS_OUT_FINE property, AMP field definition (NO TITLE)*/
   #define  Si2146_ATV_CVBS_OUT_FINE_PROP_AMP_LSB         8
   #define  Si2146_ATV_CVBS_OUT_FINE_PROP_AMP_MASK        0xff
   #define  Si2146_ATV_CVBS_OUT_FINE_PROP_AMP_DEFAULT    100
    #define Si2146_ATV_CVBS_OUT_FINE_PROP_AMP_AMP_MIN  25
    #define Si2146_ATV_CVBS_OUT_FINE_PROP_AMP_AMP_MAX  100

   /* ATV_CVBS_OUT_FINE property, OFFSET field definition (NO TITLE)*/
   #define  Si2146_ATV_CVBS_OUT_FINE_PROP_OFFSET_LSB         0
   #define  Si2146_ATV_CVBS_OUT_FINE_PROP_OFFSET_MASK        0xff
   #define  Si2146_ATV_CVBS_OUT_FINE_PROP_OFFSET_DEFAULT    0
    #define Si2146_ATV_CVBS_OUT_FINE_PROP_OFFSET_OFFSET_MIN  -128
    #define Si2146_ATV_CVBS_OUT_FINE_PROP_OFFSET_OFFSET_MAX  127

#endif /* Si2146_ATV_CVBS_OUT_FINE_PROP */

/* Si2146 ATV_IEN property definition */
#define   Si2146_ATV_IEN_PROP 0x0601

#ifdef    Si2146_ATV_IEN_PROP
  #define Si2146_ATV_IEN_PROP_CODE 0x000601


    typedef struct { /* Si2146_ATV_IEN_PROP_struct */
      unsigned char   chlien;
      unsigned char   dlien;
      unsigned char   pclien;
      unsigned char   snrhien;
      unsigned char   snrlien;
   } Si2146_ATV_IEN_PROP_struct;

   /* ATV_IEN property, CHLIEN field definition (NO TITLE)*/
   #define  Si2146_ATV_IEN_PROP_CHLIEN_LSB         0
   #define  Si2146_ATV_IEN_PROP_CHLIEN_MASK        0x01
   #define  Si2146_ATV_IEN_PROP_CHLIEN_DEFAULT    0
    #define Si2146_ATV_IEN_PROP_CHLIEN_DISABLE  0
    #define Si2146_ATV_IEN_PROP_CHLIEN_ENABLE   1

   /* ATV_IEN property, DLIEN field definition (NO TITLE)*/
   #define  Si2146_ATV_IEN_PROP_DLIEN_LSB         2
   #define  Si2146_ATV_IEN_PROP_DLIEN_MASK        0x01
   #define  Si2146_ATV_IEN_PROP_DLIEN_DEFAULT    0
    #define Si2146_ATV_IEN_PROP_DLIEN_DISABLE  0
    #define Si2146_ATV_IEN_PROP_DLIEN_ENABLE   1

   /* ATV_IEN property, PCLIEN field definition (NO TITLE)*/
   #define  Si2146_ATV_IEN_PROP_PCLIEN_LSB         1
   #define  Si2146_ATV_IEN_PROP_PCLIEN_MASK        0x01
   #define  Si2146_ATV_IEN_PROP_PCLIEN_DEFAULT    0
    #define Si2146_ATV_IEN_PROP_PCLIEN_DISABLE  0
    #define Si2146_ATV_IEN_PROP_PCLIEN_ENABLE   1

   /* ATV_IEN property, SNRHIEN field definition (NO TITLE)*/
   #define  Si2146_ATV_IEN_PROP_SNRHIEN_LSB         4
   #define  Si2146_ATV_IEN_PROP_SNRHIEN_MASK        0x01
   #define  Si2146_ATV_IEN_PROP_SNRHIEN_DEFAULT    0
    #define Si2146_ATV_IEN_PROP_SNRHIEN_DISABLE  0
    #define Si2146_ATV_IEN_PROP_SNRHIEN_ENABLE   1

   /* ATV_IEN property, SNRLIEN field definition (NO TITLE)*/
   #define  Si2146_ATV_IEN_PROP_SNRLIEN_LSB         3
   #define  Si2146_ATV_IEN_PROP_SNRLIEN_MASK        0x01
   #define  Si2146_ATV_IEN_PROP_SNRLIEN_DEFAULT    0
    #define Si2146_ATV_IEN_PROP_SNRLIEN_DISABLE  0
    #define Si2146_ATV_IEN_PROP_SNRLIEN_ENABLE   1

#endif /* Si2146_ATV_IEN_PROP */

/* Si2146 ATV_INT_SENSE property definition */
#define   Si2146_ATV_INT_SENSE_PROP 0x0613

#ifdef    Si2146_ATV_INT_SENSE_PROP
  #define Si2146_ATV_INT_SENSE_PROP_CODE 0x000613


    typedef struct { /* Si2146_ATV_INT_SENSE_PROP_struct */
      unsigned char   chlnegen;
      unsigned char   chlposen;
      unsigned char   dlnegen;
      unsigned char   dlposen;
      unsigned char   pclnegen;
      unsigned char   pclposen;
      unsigned char   snrhnegen;
      unsigned char   snrhposen;
      unsigned char   snrlnegen;
      unsigned char   snrlposen;
   } Si2146_ATV_INT_SENSE_PROP_struct;

   /* ATV_INT_SENSE property, CHLNEGEN field definition (NO TITLE)*/
   #define  Si2146_ATV_INT_SENSE_PROP_CHLNEGEN_LSB         0
   #define  Si2146_ATV_INT_SENSE_PROP_CHLNEGEN_MASK        0x01
   #define  Si2146_ATV_INT_SENSE_PROP_CHLNEGEN_DEFAULT    0
    #define Si2146_ATV_INT_SENSE_PROP_CHLNEGEN_DISABLE  0
    #define Si2146_ATV_INT_SENSE_PROP_CHLNEGEN_ENABLE   1

   /* ATV_INT_SENSE property, CHLPOSEN field definition (NO TITLE)*/
   #define  Si2146_ATV_INT_SENSE_PROP_CHLPOSEN_LSB         8
   #define  Si2146_ATV_INT_SENSE_PROP_CHLPOSEN_MASK        0x01
   #define  Si2146_ATV_INT_SENSE_PROP_CHLPOSEN_DEFAULT    1
    #define Si2146_ATV_INT_SENSE_PROP_CHLPOSEN_DISABLE  0
    #define Si2146_ATV_INT_SENSE_PROP_CHLPOSEN_ENABLE   1

   /* ATV_INT_SENSE property, DLNEGEN field definition (NO TITLE)*/
   #define  Si2146_ATV_INT_SENSE_PROP_DLNEGEN_LSB         2
   #define  Si2146_ATV_INT_SENSE_PROP_DLNEGEN_MASK        0x01
   #define  Si2146_ATV_INT_SENSE_PROP_DLNEGEN_DEFAULT    0
    #define Si2146_ATV_INT_SENSE_PROP_DLNEGEN_DISABLE  0
    #define Si2146_ATV_INT_SENSE_PROP_DLNEGEN_ENABLE   1

   /* ATV_INT_SENSE property, DLPOSEN field definition (NO TITLE)*/
   #define  Si2146_ATV_INT_SENSE_PROP_DLPOSEN_LSB         10
   #define  Si2146_ATV_INT_SENSE_PROP_DLPOSEN_MASK        0x01
   #define  Si2146_ATV_INT_SENSE_PROP_DLPOSEN_DEFAULT    1
    #define Si2146_ATV_INT_SENSE_PROP_DLPOSEN_DISABLE  0
    #define Si2146_ATV_INT_SENSE_PROP_DLPOSEN_ENABLE   1

   /* ATV_INT_SENSE property, PCLNEGEN field definition (NO TITLE)*/
   #define  Si2146_ATV_INT_SENSE_PROP_PCLNEGEN_LSB         1
   #define  Si2146_ATV_INT_SENSE_PROP_PCLNEGEN_MASK        0x01
   #define  Si2146_ATV_INT_SENSE_PROP_PCLNEGEN_DEFAULT    0
    #define Si2146_ATV_INT_SENSE_PROP_PCLNEGEN_DISABLE  0
    #define Si2146_ATV_INT_SENSE_PROP_PCLNEGEN_ENABLE   1

   /* ATV_INT_SENSE property, PCLPOSEN field definition (NO TITLE)*/
   #define  Si2146_ATV_INT_SENSE_PROP_PCLPOSEN_LSB         9
   #define  Si2146_ATV_INT_SENSE_PROP_PCLPOSEN_MASK        0x01
   #define  Si2146_ATV_INT_SENSE_PROP_PCLPOSEN_DEFAULT    1
    #define Si2146_ATV_INT_SENSE_PROP_PCLPOSEN_DISABLE  0
    #define Si2146_ATV_INT_SENSE_PROP_PCLPOSEN_ENABLE   1

   /* ATV_INT_SENSE property, SNRHNEGEN field definition (NO TITLE)*/
   #define  Si2146_ATV_INT_SENSE_PROP_SNRHNEGEN_LSB         4
   #define  Si2146_ATV_INT_SENSE_PROP_SNRHNEGEN_MASK        0x01
   #define  Si2146_ATV_INT_SENSE_PROP_SNRHNEGEN_DEFAULT    0
    #define Si2146_ATV_INT_SENSE_PROP_SNRHNEGEN_DISABLE  0
    #define Si2146_ATV_INT_SENSE_PROP_SNRHNEGEN_ENABLE   1

   /* ATV_INT_SENSE property, SNRHPOSEN field definition (NO TITLE)*/
   #define  Si2146_ATV_INT_SENSE_PROP_SNRHPOSEN_LSB         12
   #define  Si2146_ATV_INT_SENSE_PROP_SNRHPOSEN_MASK        0x01
   #define  Si2146_ATV_INT_SENSE_PROP_SNRHPOSEN_DEFAULT    1
    #define Si2146_ATV_INT_SENSE_PROP_SNRHPOSEN_DISABLE  0
    #define Si2146_ATV_INT_SENSE_PROP_SNRHPOSEN_ENABLE   1

   /* ATV_INT_SENSE property, SNRLNEGEN field definition (NO TITLE)*/
   #define  Si2146_ATV_INT_SENSE_PROP_SNRLNEGEN_LSB         3
   #define  Si2146_ATV_INT_SENSE_PROP_SNRLNEGEN_MASK        0x01
   #define  Si2146_ATV_INT_SENSE_PROP_SNRLNEGEN_DEFAULT    0
    #define Si2146_ATV_INT_SENSE_PROP_SNRLNEGEN_DISABLE  0
    #define Si2146_ATV_INT_SENSE_PROP_SNRLNEGEN_ENABLE   1

   /* ATV_INT_SENSE property, SNRLPOSEN field definition (NO TITLE)*/
   #define  Si2146_ATV_INT_SENSE_PROP_SNRLPOSEN_LSB         11
   #define  Si2146_ATV_INT_SENSE_PROP_SNRLPOSEN_MASK        0x01
   #define  Si2146_ATV_INT_SENSE_PROP_SNRLPOSEN_DEFAULT    1
    #define Si2146_ATV_INT_SENSE_PROP_SNRLPOSEN_DISABLE  0
    #define Si2146_ATV_INT_SENSE_PROP_SNRLPOSEN_ENABLE   1

#endif /* Si2146_ATV_INT_SENSE_PROP */

/* Si2146 ATV_RF_TOP property definition */
#define   Si2146_ATV_RF_TOP_PROP 0x0612

#ifdef    Si2146_ATV_RF_TOP_PROP
  #define Si2146_ATV_RF_TOP_PROP_CODE 0x000612


    typedef struct { /* Si2146_ATV_RF_TOP_PROP_struct */
      unsigned char   atv_rf_top;
   } Si2146_ATV_RF_TOP_PROP_struct;

   /* ATV_RF_TOP property, ATV_RF_TOP field definition (NO TITLE)*/
   #define  Si2146_ATV_RF_TOP_PROP_ATV_RF_TOP_LSB         0
   #define  Si2146_ATV_RF_TOP_PROP_ATV_RF_TOP_MASK        0xff
   #define  Si2146_ATV_RF_TOP_PROP_ATV_RF_TOP_DEFAULT    0
    #define Si2146_ATV_RF_TOP_PROP_ATV_RF_TOP_AUTO   0
    #define Si2146_ATV_RF_TOP_PROP_ATV_RF_TOP_0DB    6
    #define Si2146_ATV_RF_TOP_PROP_ATV_RF_TOP_M1DB   7
    #define Si2146_ATV_RF_TOP_PROP_ATV_RF_TOP_M2DB   8
    #define Si2146_ATV_RF_TOP_PROP_ATV_RF_TOP_M4DB   10
    #define Si2146_ATV_RF_TOP_PROP_ATV_RF_TOP_M5DB   11
    #define Si2146_ATV_RF_TOP_PROP_ATV_RF_TOP_M6DB   12
    #define Si2146_ATV_RF_TOP_PROP_ATV_RF_TOP_M7DB   13
    #define Si2146_ATV_RF_TOP_PROP_ATV_RF_TOP_M8DB   14
    #define Si2146_ATV_RF_TOP_PROP_ATV_RF_TOP_M9DB   15

#endif /* Si2146_ATV_RF_TOP_PROP */

/* Si2146 ATV_RSQ_RSSI_THRESHOLD property definition */
#define   Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP 0x0605

#ifdef    Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP
  #define Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_CODE 0x000605


    typedef struct { /* Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_struct */
               char   hi;
               char   lo;
   } Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_struct;

   /* ATV_RSQ_RSSI_THRESHOLD property, HI field definition (NO TITLE)*/
   #define  Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB         8
   #define  Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK        0xff
   #define  Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_DEFAULT    0
    #define Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_HI_MIN  -128
    #define Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_HI_MAX  127

   /* ATV_RSQ_RSSI_THRESHOLD property, LO field definition (NO TITLE)*/
   #define  Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB         0
   #define  Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK        0xff
   #define  Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_DEFAULT    -70
    #define Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_LO_MIN  -128
    #define Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_LO_MAX  127

#endif /* Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP */

/* Si2146 ATV_RSQ_SNR_THRESHOLD property definition */
#define   Si2146_ATV_RSQ_SNR_THRESHOLD_PROP 0x0606

#ifdef    Si2146_ATV_RSQ_SNR_THRESHOLD_PROP
  #define Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_CODE 0x000606


    typedef struct { /* Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_struct */
      unsigned char   hi;
      unsigned char   lo;
   } Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_struct;

   /* ATV_RSQ_SNR_THRESHOLD property, HI field definition (NO TITLE)*/
   #define  Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_HI_LSB         8
   #define  Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_HI_MASK        0xff
   #define  Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_HI_DEFAULT    45
    #define Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_HI_HI_MIN  0
    #define Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_HI_HI_MAX  255

   /* ATV_RSQ_SNR_THRESHOLD property, LO field definition (NO TITLE)*/
   #define  Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_LO_LSB         0
   #define  Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_LO_MASK        0xff
   #define  Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_LO_DEFAULT    25
    #define Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_LO_LO_MIN  0
    #define Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_LO_LO_MAX  255

#endif /* Si2146_ATV_RSQ_SNR_THRESHOLD_PROP */

/* Si2146 ATV_SIF_OUT property definition */
#define   Si2146_ATV_SIF_OUT_PROP 0x060a

#ifdef    Si2146_ATV_SIF_OUT_PROP
  #define Si2146_ATV_SIF_OUT_PROP_CODE 0x00060a


    typedef struct { /* Si2146_ATV_SIF_OUT_PROP_struct */
      unsigned char   amp;
      unsigned char   offset;
   } Si2146_ATV_SIF_OUT_PROP_struct;

   /* ATV_SIF_OUT property, AMP field definition (NO TITLE)*/
   #define  Si2146_ATV_SIF_OUT_PROP_AMP_LSB         8
   #define  Si2146_ATV_SIF_OUT_PROP_AMP_MASK        0xff
   #define  Si2146_ATV_SIF_OUT_PROP_AMP_DEFAULT    60
    #define Si2146_ATV_SIF_OUT_PROP_AMP_AMP_MIN  0
    #define Si2146_ATV_SIF_OUT_PROP_AMP_AMP_MAX  255

   /* ATV_SIF_OUT property, OFFSET field definition (NO TITLE)*/
   #define  Si2146_ATV_SIF_OUT_PROP_OFFSET_LSB         0
   #define  Si2146_ATV_SIF_OUT_PROP_OFFSET_MASK        0xff
   #define  Si2146_ATV_SIF_OUT_PROP_OFFSET_DEFAULT    135
    #define Si2146_ATV_SIF_OUT_PROP_OFFSET_OFFSET_MIN  0
    #define Si2146_ATV_SIF_OUT_PROP_OFFSET_OFFSET_MAX  255

#endif /* Si2146_ATV_SIF_OUT_PROP */

/* Si2146 ATV_SOUND_AGC_LIMIT property definition */
#define   Si2146_ATV_SOUND_AGC_LIMIT_PROP 0x0618

#ifdef    Si2146_ATV_SOUND_AGC_LIMIT_PROP
  #define Si2146_ATV_SOUND_AGC_LIMIT_PROP_CODE 0x000618


    typedef struct { /* Si2146_ATV_SOUND_AGC_LIMIT_PROP_struct */
               char   max_gain;
               char   min_gain;
   } Si2146_ATV_SOUND_AGC_LIMIT_PROP_struct;

   /* ATV_SOUND_AGC_LIMIT property, MAX_GAIN field definition (NO TITLE)*/
   #define  Si2146_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_LSB         0
   #define  Si2146_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_MASK        0xff
   #define  Si2146_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_DEFAULT    84
    #define Si2146_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_MAX_GAIN_MIN  -84
    #define Si2146_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_MAX_GAIN_MAX  84

   /* ATV_SOUND_AGC_LIMIT property, MIN_GAIN field definition (NO TITLE)*/
   #define  Si2146_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_LSB         8
   #define  Si2146_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_MASK        0xff
   #define  Si2146_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_DEFAULT    -84
    #define Si2146_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_MIN_GAIN_MIN  -84
    #define Si2146_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_MIN_GAIN_MAX  84

#endif /* Si2146_ATV_SOUND_AGC_LIMIT_PROP */

/* Si2146 ATV_SOUND_AGC_SPEED property definition */
#define   Si2146_ATV_SOUND_AGC_SPEED_PROP 0x0619

#ifdef    Si2146_ATV_SOUND_AGC_SPEED_PROP
  #define Si2146_ATV_SOUND_AGC_SPEED_PROP_CODE 0x000619


    typedef struct { /* Si2146_ATV_SOUND_AGC_SPEED_PROP_struct */
      unsigned char   other_systems;
      unsigned char   system_l;
   } Si2146_ATV_SOUND_AGC_SPEED_PROP_struct;

   /* ATV_SOUND_AGC_SPEED property, OTHER_SYSTEMS field definition (NO TITLE)*/
   #define  Si2146_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_LSB         8
   #define  Si2146_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_MASK        0xff
   #define  Si2146_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_DEFAULT    7
    #define Si2146_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_OTHER_SYSTEMS_MIN  0
    #define Si2146_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_OTHER_SYSTEMS_MAX  15

   /* ATV_SOUND_AGC_SPEED property, SYSTEM_L field definition (NO TITLE)*/
   #define  Si2146_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_LSB         0
   #define  Si2146_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_MASK        0xff
   #define  Si2146_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_DEFAULT    8
    #define Si2146_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_SYSTEM_L_MIN  0
    #define Si2146_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_SYSTEM_L_MAX  15

#endif /* Si2146_ATV_SOUND_AGC_SPEED_PROP */

/* Si2146 ATV_VIDEO_EQUALIZER property definition */
#define   Si2146_ATV_VIDEO_EQUALIZER_PROP 0x0608

#ifdef    Si2146_ATV_VIDEO_EQUALIZER_PROP
  #define Si2146_ATV_VIDEO_EQUALIZER_PROP_CODE 0x000608


    typedef struct { /* Si2146_ATV_VIDEO_EQUALIZER_PROP_struct */
               char   slope;
   } Si2146_ATV_VIDEO_EQUALIZER_PROP_struct;

   /* ATV_VIDEO_EQUALIZER property, SLOPE field definition (NO TITLE)*/
   #define  Si2146_ATV_VIDEO_EQUALIZER_PROP_SLOPE_LSB         0
   #define  Si2146_ATV_VIDEO_EQUALIZER_PROP_SLOPE_MASK        0xff
   #define  Si2146_ATV_VIDEO_EQUALIZER_PROP_SLOPE_DEFAULT    0
    #define Si2146_ATV_VIDEO_EQUALIZER_PROP_SLOPE_SLOPE_MIN  -8
    #define Si2146_ATV_VIDEO_EQUALIZER_PROP_SLOPE_SLOPE_MAX  7

#endif /* Si2146_ATV_VIDEO_EQUALIZER_PROP */

/* Si2146 ATV_VIDEO_MODE property definition */
#define   Si2146_ATV_VIDEO_MODE_PROP 0x0604

#ifdef    Si2146_ATV_VIDEO_MODE_PROP
  #define Si2146_ATV_VIDEO_MODE_PROP_CODE 0x000604


    typedef struct { /* Si2146_ATV_VIDEO_MODE_PROP_struct */
      unsigned char   color;
      unsigned char   invert_signal;
      unsigned char   invert_spectrum;
      unsigned char   trans;
      unsigned char   video_sys;
   } Si2146_ATV_VIDEO_MODE_PROP_struct;

   /* ATV_VIDEO_MODE property, COLOR field definition (NO TITLE)*/
   #define  Si2146_ATV_VIDEO_MODE_PROP_COLOR_LSB         4
   #define  Si2146_ATV_VIDEO_MODE_PROP_COLOR_MASK        0x01
   #define  Si2146_ATV_VIDEO_MODE_PROP_COLOR_DEFAULT    0
    #define Si2146_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC  0
    #define Si2146_ATV_VIDEO_MODE_PROP_COLOR_SECAM     1

   /* ATV_VIDEO_MODE property, INVERT_SIGNAL field definition (NO TITLE)*/
   #define  Si2146_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_LSB         10
   #define  Si2146_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_MASK        0x01
   #define  Si2146_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_DEFAULT    0
    #define Si2146_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_NORMAL    0
    #define Si2146_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_INVERTED  1

   /* ATV_VIDEO_MODE property, INVERT_SPECTRUM field definition (NO TITLE)*/
   #define  Si2146_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_LSB         9
   #define  Si2146_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_MASK        0x01
   #define  Si2146_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_DEFAULT    0
    #define Si2146_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_NORMAL    0
    #define Si2146_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED  1

   /* ATV_VIDEO_MODE property, TRANS field definition (NO TITLE)*/
   #define  Si2146_ATV_VIDEO_MODE_PROP_TRANS_LSB         8
   #define  Si2146_ATV_VIDEO_MODE_PROP_TRANS_MASK        0x01
   #define  Si2146_ATV_VIDEO_MODE_PROP_TRANS_DEFAULT    0
    #define Si2146_ATV_VIDEO_MODE_PROP_TRANS_TERRESTRIAL  0
    #define Si2146_ATV_VIDEO_MODE_PROP_TRANS_CABLE        1

   /* ATV_VIDEO_MODE property, VIDEO_SYS field definition (NO TITLE)*/
   #define  Si2146_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LSB         0
   #define  Si2146_ATV_VIDEO_MODE_PROP_VIDEO_SYS_MASK        0x07
   #define  Si2146_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DEFAULT    0
    #define Si2146_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B   0
    #define Si2146_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH  1
    #define Si2146_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M   2
    #define Si2146_ATV_VIDEO_MODE_PROP_VIDEO_SYS_N   3
    #define Si2146_ATV_VIDEO_MODE_PROP_VIDEO_SYS_I   4
    #define Si2146_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK  5
    #define Si2146_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L   6
    #define Si2146_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LP  7

#endif /* Si2146_ATV_VIDEO_MODE_PROP */

/* Si2146 ATV_VSNR_CAP property definition */
#define   Si2146_ATV_VSNR_CAP_PROP 0x0616

#ifdef    Si2146_ATV_VSNR_CAP_PROP
  #define Si2146_ATV_VSNR_CAP_PROP_CODE 0x000616


    typedef struct { /* Si2146_ATV_VSNR_CAP_PROP_struct */
      unsigned char   atv_vsnr_cap;
   } Si2146_ATV_VSNR_CAP_PROP_struct;

   /* ATV_VSNR_CAP property, ATV_VSNR_CAP field definition (NO TITLE)*/
   #define  Si2146_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_LSB         0
   #define  Si2146_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_MASK        0xff
   #define  Si2146_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_DEFAULT    0
    #define Si2146_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_ATV_VSNR_CAP_MIN  0
    #define Si2146_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_ATV_VSNR_CAP_MAX  127

#endif /* Si2146_ATV_VSNR_CAP_PROP */

/* Si2146 ATV_VSYNC_TRACKING property definition */
#define   Si2146_ATV_VSYNC_TRACKING_PROP 0x0615

#ifdef    Si2146_ATV_VSYNC_TRACKING_PROP
  #define Si2146_ATV_VSYNC_TRACKING_PROP_CODE 0x000615


    typedef struct { /* Si2146_ATV_VSYNC_TRACKING_PROP_struct */
      unsigned char   min_fields_to_unlock;
      unsigned char   min_pulses_to_lock;
   } Si2146_ATV_VSYNC_TRACKING_PROP_struct;

   /* ATV_VSYNC_TRACKING property, MIN_FIELDS_TO_UNLOCK field definition (NO TITLE)*/
   #define  Si2146_ATV_VSYNC_TRACKING_PROP_MIN_FIELDS_TO_UNLOCK_LSB         8
   #define  Si2146_ATV_VSYNC_TRACKING_PROP_MIN_FIELDS_TO_UNLOCK_MASK        0xff
   #define  Si2146_ATV_VSYNC_TRACKING_PROP_MIN_FIELDS_TO_UNLOCK_DEFAULT    16
    #define Si2146_ATV_VSYNC_TRACKING_PROP_MIN_FIELDS_TO_UNLOCK_MIN_FIELDS_TO_UNLOCK_MIN  0
    #define Si2146_ATV_VSYNC_TRACKING_PROP_MIN_FIELDS_TO_UNLOCK_MIN_FIELDS_TO_UNLOCK_MAX  255

   /* ATV_VSYNC_TRACKING property, MIN_PULSES_TO_LOCK field definition (NO TITLE)*/
   #define  Si2146_ATV_VSYNC_TRACKING_PROP_MIN_PULSES_TO_LOCK_LSB         0
   #define  Si2146_ATV_VSYNC_TRACKING_PROP_MIN_PULSES_TO_LOCK_MASK        0xff
   #define  Si2146_ATV_VSYNC_TRACKING_PROP_MIN_PULSES_TO_LOCK_DEFAULT    4
    #define Si2146_ATV_VSYNC_TRACKING_PROP_MIN_PULSES_TO_LOCK_MIN_PULSES_TO_LOCK_MIN  0
    #define Si2146_ATV_VSYNC_TRACKING_PROP_MIN_PULSES_TO_LOCK_MIN_PULSES_TO_LOCK_MAX  9

#endif /* Si2146_ATV_VSYNC_TRACKING_PROP */

/* Si2146 CRYSTAL_TRIM property definition */
#define   Si2146_CRYSTAL_TRIM_PROP 0x0402

#ifdef    Si2146_CRYSTAL_TRIM_PROP
  #define Si2146_CRYSTAL_TRIM_PROP_CODE 0x000402


    typedef struct { /* Si2146_CRYSTAL_TRIM_PROP_struct */
      unsigned char   xo_cap;
   } Si2146_CRYSTAL_TRIM_PROP_struct;

   /* CRYSTAL_TRIM property, XO_CAP field definition (NO TITLE)*/
   #define  Si2146_CRYSTAL_TRIM_PROP_XO_CAP_LSB         0
   #define  Si2146_CRYSTAL_TRIM_PROP_XO_CAP_MASK        0x0f
   #define  Si2146_CRYSTAL_TRIM_PROP_XO_CAP_DEFAULT    8
    #define Si2146_CRYSTAL_TRIM_PROP_XO_CAP_XO_CAP_MIN  0
    #define Si2146_CRYSTAL_TRIM_PROP_XO_CAP_XO_CAP_MAX  15

#endif /* Si2146_CRYSTAL_TRIM_PROP */

/* Si2146 DTV_AGC_FREEZE_INPUT property definition */
#ifdef LOAD_PATCH_11b3  /*DTV_AGC_FREEZE_INPUT Property requires 1.1build2 patch */
#define   Si2146_DTV_AGC_FREEZE_INPUT_PROP 0x0711
#endif
#ifdef    Si2146_DTV_AGC_FREEZE_INPUT_PROP
  #define Si2146_DTV_AGC_FREEZE_INPUT_PROP_CODE 0x000711


    typedef struct { /* Si2146_DTV_AGC_FREEZE_INPUT_PROP_struct */
      unsigned char   level;
      unsigned char   pin;
   } Si2146_DTV_AGC_FREEZE_INPUT_PROP_struct;

   /* DTV_AGC_FREEZE_INPUT property, LEVEL field definition (NO TITLE)*/
   #define  Si2146_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LSB         0
   #define  Si2146_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_MASK        0x01
   #define  Si2146_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_DEFAULT    0
    #define Si2146_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LOW   0
    #define Si2146_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_HIGH  1

   /* DTV_AGC_FREEZE_INPUT property, PIN field definition (NO TITLE)*/
   #define  Si2146_DTV_AGC_FREEZE_INPUT_PROP_PIN_LSB         1
   #define  Si2146_DTV_AGC_FREEZE_INPUT_PROP_PIN_MASK        0x03
   #define  Si2146_DTV_AGC_FREEZE_INPUT_PROP_PIN_DEFAULT    0
    #define Si2146_DTV_AGC_FREEZE_INPUT_PROP_PIN_NONE   0
    #define Si2146_DTV_AGC_FREEZE_INPUT_PROP_PIN_GPIO1  1
    #define Si2146_DTV_AGC_FREEZE_INPUT_PROP_PIN_GPIO2  2
    #define Si2146_DTV_AGC_FREEZE_INPUT_PROP_PIN_GPIO3  3

#endif /* Si2146_DTV_AGC_FREEZE_INPUT_PROP */

/* Si2146 DTV_AGC_SPEED property definition */
#define   Si2146_DTV_AGC_SPEED_PROP 0x0708

#ifdef    Si2146_DTV_AGC_SPEED_PROP
  #define Si2146_DTV_AGC_SPEED_PROP_CODE 0x000708


    typedef struct { /* Si2146_DTV_AGC_SPEED_PROP_struct */
      unsigned char   agc_decim;
      unsigned char   if_agc_speed;
   } Si2146_DTV_AGC_SPEED_PROP_struct;

   /* DTV_AGC_SPEED property, AGC_DECIM field definition (NO TITLE)*/
   #define  Si2146_DTV_AGC_SPEED_PROP_AGC_DECIM_LSB         8
   #define  Si2146_DTV_AGC_SPEED_PROP_AGC_DECIM_MASK        0x03
   #define  Si2146_DTV_AGC_SPEED_PROP_AGC_DECIM_DEFAULT    0
    #define Si2146_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF  0
    #define Si2146_DTV_AGC_SPEED_PROP_AGC_DECIM_2    1
    #define Si2146_DTV_AGC_SPEED_PROP_AGC_DECIM_4    2
    #define Si2146_DTV_AGC_SPEED_PROP_AGC_DECIM_8    3

   /* DTV_AGC_SPEED property, IF_AGC_SPEED field definition (NO TITLE)*/
   #define  Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB         0
   #define  Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK        0xff
   #define  Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_DEFAULT    0
    #define Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO  0
    #define Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_39    39
    #define Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_54    54
    #define Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_63    63
    #define Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_89    89
    #define Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_105   105
    #define Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_121   121
    #define Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_137   137
    #define Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_158   158
    #define Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_172   172
    #define Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_185   185
    #define Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_196   196
    #define Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_206   206
    #define Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_216   216
    #define Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_219   219
    #define Si2146_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_222   222

#endif /* Si2146_DTV_AGC_SPEED_PROP */

/* Si2146 DTV_CONFIG_IF_PORT property definition */
#define   Si2146_DTV_CONFIG_IF_PORT_PROP 0x0702

#ifdef    Si2146_DTV_CONFIG_IF_PORT_PROP
  #define Si2146_DTV_CONFIG_IF_PORT_PROP_CODE 0x000702


    typedef struct { /* Si2146_DTV_CONFIG_IF_PORT_PROP_struct */
      unsigned char   dtv_agc_source;
      unsigned char   dtv_out_type;
   } Si2146_DTV_CONFIG_IF_PORT_PROP_struct;

   /* DTV_CONFIG_IF_PORT property, DTV_AGC_SOURCE field definition (NO TITLE)*/
   #define  Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_LSB         8
   #define  Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_MASK        0x07
   #define  Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_DEFAULT    0
    #define Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_INTERNAL       0
    #define Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_DLIF_AGC_3DB   1

   /* DTV_CONFIG_IF_PORT property, DTV_OUT_TYPE field definition (NO TITLE)*/
   #define  Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LSB         0
   #define  Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_MASK        0x0f
   #define  Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_DEFAULT    0
    #define Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_IF1      0
    #define Si2146_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_SE_IF1A  4

#endif /* Si2146_DTV_CONFIG_IF_PORT_PROP */

/* Si2146 DTV_EXT_AGC property definition */
#define   Si2146_DTV_EXT_AGC_PROP 0x0705

#ifdef    Si2146_DTV_EXT_AGC_PROP
  #define Si2146_DTV_EXT_AGC_PROP_CODE 0x000705


    typedef struct { /* Si2146_DTV_EXT_AGC_PROP_struct */
      unsigned char   max_10mv;
      unsigned char   min_10mv;
   } Si2146_DTV_EXT_AGC_PROP_struct;

   /* DTV_EXT_AGC property, MAX_10MV field definition (NO TITLE)*/
   #define  Si2146_DTV_EXT_AGC_PROP_MAX_10MV_LSB         8
   #define  Si2146_DTV_EXT_AGC_PROP_MAX_10MV_MASK        0xff
   #define  Si2146_DTV_EXT_AGC_PROP_MAX_10MV_DEFAULT    200
    #define Si2146_DTV_EXT_AGC_PROP_MAX_10MV_MAX_10MV_MIN  0
    #define Si2146_DTV_EXT_AGC_PROP_MAX_10MV_MAX_10MV_MAX  215

   /* DTV_EXT_AGC property, MIN_10MV field definition (NO TITLE)*/
   #define  Si2146_DTV_EXT_AGC_PROP_MIN_10MV_LSB         0
   #define  Si2146_DTV_EXT_AGC_PROP_MIN_10MV_MASK        0xff
   #define  Si2146_DTV_EXT_AGC_PROP_MIN_10MV_DEFAULT    50
    #define Si2146_DTV_EXT_AGC_PROP_MIN_10MV_MIN_10MV_MIN  0
    #define Si2146_DTV_EXT_AGC_PROP_MIN_10MV_MIN_10MV_MAX  215

#endif /* Si2146_DTV_EXT_AGC_PROP */

/* Si2146 DTV_IEN property definition */
#define   Si2146_DTV_IEN_PROP 0x0701

#ifdef    Si2146_DTV_IEN_PROP
  #define Si2146_DTV_IEN_PROP_CODE 0x000701


    typedef struct { /* Si2146_DTV_IEN_PROP_struct */
      unsigned char   chlien;
   } Si2146_DTV_IEN_PROP_struct;

   /* DTV_IEN property, CHLIEN field definition (NO TITLE)*/
   #define  Si2146_DTV_IEN_PROP_CHLIEN_LSB         0
   #define  Si2146_DTV_IEN_PROP_CHLIEN_MASK        0x01
   #define  Si2146_DTV_IEN_PROP_CHLIEN_DEFAULT    0
    #define Si2146_DTV_IEN_PROP_CHLIEN_DISABLE  0
    #define Si2146_DTV_IEN_PROP_CHLIEN_ENABLE   1

#endif /* Si2146_DTV_IEN_PROP */
/* Si2146 DTV_INITIAL_AGC_SPEED property definition */
#define   Si2146_DTV_INITIAL_AGC_SPEED_PROP 0x070d

#ifdef    Si2146_DTV_INITIAL_AGC_SPEED_PROP
  #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_CODE 0x00070d


    typedef struct { /* Si2146_DTV_INITIAL_AGC_SPEED_PROP_struct */
      unsigned char   agc_decim;
      unsigned char   if_agc_speed;
   } Si2146_DTV_INITIAL_AGC_SPEED_PROP_struct;

   /* DTV_INITIAL_AGC_SPEED property, AGC_DECIM field definition (NO TITLE)*/
   #define  Si2146_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_LSB         8
   #define  Si2146_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_MASK        0x03
   #define  Si2146_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_DEFAULT    0
    #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_OFF  0
    #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_2    1
    #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_4    2
    #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_8    3

   /* DTV_INITIAL_AGC_SPEED property, IF_AGC_SPEED field definition (NO TITLE)*/
   #define  Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_LSB         0
   #define  Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_MASK        0xff
   #define  Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_DEFAULT    0
    #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO  0
    #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_39    39
    #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_54    54
    #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_63    63
    #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_89    89
    #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_105   105
    #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_121   121
    #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_137   137
    #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_158   158
    #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_172   172
    #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_185   185
    #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_196   196
    #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_206   206
    #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_216   216
    #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_219   219
    #define Si2146_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_222   222

#endif /* Si2146_DTV_INITIAL_AGC_SPEED_PROP */

/* Si2146 DTV_INITIAL_AGC_SPEED_PERIOD property definition */
#define   Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP 0x070e

#ifdef    Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
  #define Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE 0x00070e


    typedef struct { /* Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_struct */
      unsigned int    period;
   } Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_struct;

   /* DTV_INITIAL_AGC_SPEED_PERIOD property, PERIOD field definition (NO TITLE)*/
   #define  Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_LSB         0
   #define  Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_MASK        0xffff
   #define  Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_DEFAULT    0
    #define Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_PERIOD_MIN  0
    #define Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_PERIOD_MAX  65535

#endif /* Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */

/* Si2146 DTV_INT_SENSE property definition */
#define   Si2146_DTV_INT_SENSE_PROP 0x070a

#ifdef    Si2146_DTV_INT_SENSE_PROP
  #define Si2146_DTV_INT_SENSE_PROP_CODE 0x00070a


    typedef struct { /* Si2146_DTV_INT_SENSE_PROP_struct */
      unsigned char   chlnegen;
      unsigned char   chlposen;
   } Si2146_DTV_INT_SENSE_PROP_struct;

   /* DTV_INT_SENSE property, CHLNEGEN field definition (NO TITLE)*/
   #define  Si2146_DTV_INT_SENSE_PROP_CHLNEGEN_LSB         0
   #define  Si2146_DTV_INT_SENSE_PROP_CHLNEGEN_MASK        0x01
   #define  Si2146_DTV_INT_SENSE_PROP_CHLNEGEN_DEFAULT    0
    #define Si2146_DTV_INT_SENSE_PROP_CHLNEGEN_DISABLE  0
    #define Si2146_DTV_INT_SENSE_PROP_CHLNEGEN_ENABLE   1

   /* DTV_INT_SENSE property, CHLPOSEN field definition (NO TITLE)*/
   #define  Si2146_DTV_INT_SENSE_PROP_CHLPOSEN_LSB         8
   #define  Si2146_DTV_INT_SENSE_PROP_CHLPOSEN_MASK        0x01
   #define  Si2146_DTV_INT_SENSE_PROP_CHLPOSEN_DEFAULT    1
    #define Si2146_DTV_INT_SENSE_PROP_CHLPOSEN_DISABLE  0
    #define Si2146_DTV_INT_SENSE_PROP_CHLPOSEN_ENABLE   1

#endif /* Si2146_DTV_INT_SENSE_PROP */

/* Si2146 DTV_LIF_FREQ property definition */
#define   Si2146_DTV_LIF_FREQ_PROP 0x0706

#ifdef    Si2146_DTV_LIF_FREQ_PROP
  #define Si2146_DTV_LIF_FREQ_PROP_CODE 0x000706


    typedef struct { /* Si2146_DTV_LIF_FREQ_PROP_struct */
      unsigned int    offset;
   } Si2146_DTV_LIF_FREQ_PROP_struct;

   /* DTV_LIF_FREQ property, OFFSET field definition (NO TITLE)*/
   #define  Si2146_DTV_LIF_FREQ_PROP_OFFSET_LSB         0
   #define  Si2146_DTV_LIF_FREQ_PROP_OFFSET_MASK        0xffff
   #define  Si2146_DTV_LIF_FREQ_PROP_OFFSET_DEFAULT    5000
    #define Si2146_DTV_LIF_FREQ_PROP_OFFSET_OFFSET_MIN  0
    #define Si2146_DTV_LIF_FREQ_PROP_OFFSET_OFFSET_MAX  7000

#endif /* Si2146_DTV_LIF_FREQ_PROP */

/* Si2146 DTV_LIF_OUT property definition */
#define   Si2146_DTV_LIF_OUT_PROP 0x0707

#ifdef    Si2146_DTV_LIF_OUT_PROP
  #define Si2146_DTV_LIF_OUT_PROP_CODE 0x000707


    typedef struct { /* Si2146_DTV_LIF_OUT_PROP_struct */
      unsigned char   amp;
      unsigned char   offset;
   } Si2146_DTV_LIF_OUT_PROP_struct;

   /* DTV_LIF_OUT property, AMP field definition (NO TITLE)*/
   #define  Si2146_DTV_LIF_OUT_PROP_AMP_LSB         8
   #define  Si2146_DTV_LIF_OUT_PROP_AMP_MASK        0xff
   #define  Si2146_DTV_LIF_OUT_PROP_AMP_DEFAULT    27
    #define Si2146_DTV_LIF_OUT_PROP_AMP_AMP_MIN  0
    #define Si2146_DTV_LIF_OUT_PROP_AMP_AMP_MAX  255

   /* DTV_LIF_OUT property, OFFSET field definition (NO TITLE)*/
   #define  Si2146_DTV_LIF_OUT_PROP_OFFSET_LSB         0
   #define  Si2146_DTV_LIF_OUT_PROP_OFFSET_MASK        0xff
   #define  Si2146_DTV_LIF_OUT_PROP_OFFSET_DEFAULT    148
    #define Si2146_DTV_LIF_OUT_PROP_OFFSET_OFFSET_MIN  0
    #define Si2146_DTV_LIF_OUT_PROP_OFFSET_OFFSET_MAX  255

#endif /* Si2146_DTV_LIF_OUT_PROP */

/* Si2146 DTV_MODE property definition */
#define   Si2146_DTV_MODE_PROP 0x0703

#ifdef    Si2146_DTV_MODE_PROP
  #define Si2146_DTV_MODE_PROP_CODE 0x000703


    typedef struct { /* Si2146_DTV_MODE_PROP_struct */
      unsigned char   bw;
      unsigned char   invert_spectrum;
      unsigned char   modulation;
   } Si2146_DTV_MODE_PROP_struct;

   /* DTV_MODE property, BW field definition (NO TITLE)*/
   #define  Si2146_DTV_MODE_PROP_BW_LSB         0
   #define  Si2146_DTV_MODE_PROP_BW_MASK        0x0f
   #define  Si2146_DTV_MODE_PROP_BW_DEFAULT    8
    #define Si2146_DTV_MODE_PROP_BW_BW_6MHZ  6
    #define Si2146_DTV_MODE_PROP_BW_BW_7MHZ  7
    #define Si2146_DTV_MODE_PROP_BW_BW_8MHZ  8

   /* DTV_MODE property, INVERT_SPECTRUM field definition (NO TITLE)*/
   #define  Si2146_DTV_MODE_PROP_INVERT_SPECTRUM_LSB         8
   #define  Si2146_DTV_MODE_PROP_INVERT_SPECTRUM_MASK        0x01
   #define  Si2146_DTV_MODE_PROP_INVERT_SPECTRUM_DEFAULT    0
    #define Si2146_DTV_MODE_PROP_INVERT_SPECTRUM_NORMAL    0
    #define Si2146_DTV_MODE_PROP_INVERT_SPECTRUM_INVERTED  1

   /* DTV_MODE property, MODULATION field definition (NO TITLE)*/
   #define  Si2146_DTV_MODE_PROP_MODULATION_LSB         4
   #define  Si2146_DTV_MODE_PROP_MODULATION_MASK        0x0f
   #define  Si2146_DTV_MODE_PROP_MODULATION_DEFAULT    2
    #define Si2146_DTV_MODE_PROP_MODULATION_ATSC    0
    #define Si2146_DTV_MODE_PROP_MODULATION_QAM_US  1
    #define Si2146_DTV_MODE_PROP_MODULATION_DVBT    2
    #define Si2146_DTV_MODE_PROP_MODULATION_DVBC    3
    #define Si2146_DTV_MODE_PROP_MODULATION_ISDBT   4
    #define Si2146_DTV_MODE_PROP_MODULATION_ISDBC   5
    #define Si2146_DTV_MODE_PROP_MODULATION_DTMB    6

#endif /* Si2146_DTV_MODE_PROP */

/* Si2146 DTV_RF_TOP property definition */
#define   Si2146_DTV_RF_TOP_PROP 0x0709

#ifdef    Si2146_DTV_RF_TOP_PROP
  #define Si2146_DTV_RF_TOP_PROP_CODE 0x000709


    typedef struct { /* Si2146_DTV_RF_TOP_PROP_struct */
      unsigned char   dtv_rf_top;
   } Si2146_DTV_RF_TOP_PROP_struct;

   /* DTV_RF_TOP property, DTV_RF_TOP field definition (NO TITLE)*/
   #define  Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP_LSB         0
   #define  Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP_MASK        0xff
   #define  Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP_DEFAULT    0
    #define Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP_AUTO   0
    #define Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP_0DB    6
    #define Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP_M1DB   7
    #define Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP_M2DB   8
    #define Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP_M4DB   10
    #define Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP_M5DB   11
    #define Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP_M6DB   12
    #define Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP_M7DB   13
    #define Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP_M8DB   14
    #define Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP_M9DB   15

#endif /* Si2146_DTV_RF_TOP_PROP */

/* Si2146 DTV_RSQ_RSSI_THRESHOLD property definition */
#define   Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP 0x0704

#ifdef    Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP
  #define Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_CODE 0x000704


    typedef struct { /* Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_struct */
               char   hi;
               char   lo;
   } Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_struct;

   /* DTV_RSQ_RSSI_THRESHOLD property, HI field definition (NO TITLE)*/
   #define  Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB         8
   #define  Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK        0xff
   #define  Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_DEFAULT    0
    #define Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_HI_MIN  -128
    #define Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_HI_MAX  127

   /* DTV_RSQ_RSSI_THRESHOLD property, LO field definition (NO TITLE)*/
   #define  Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB         0
   #define  Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK        0xff
   #define  Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_DEFAULT    -80
    #define Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_LO_MIN  -128
    #define Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_LO_MAX  127

#endif /* Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP */

/* Si2146 MASTER_IEN property definition */
#define   Si2146_MASTER_IEN_PROP 0x0401

#ifdef    Si2146_MASTER_IEN_PROP
  #define Si2146_MASTER_IEN_PROP_CODE 0x000401


    typedef struct { /* Si2146_MASTER_IEN_PROP_struct */
      unsigned char   atvien;
      unsigned char   ctsien;
      unsigned char   dtvien;
      unsigned char   errien;
      unsigned char   tunien;
   } Si2146_MASTER_IEN_PROP_struct;

   /* MASTER_IEN property, ATVIEN field definition (NO TITLE)*/
   #define  Si2146_MASTER_IEN_PROP_ATVIEN_LSB         1
   #define  Si2146_MASTER_IEN_PROP_ATVIEN_MASK        0x01
   #define  Si2146_MASTER_IEN_PROP_ATVIEN_DEFAULT    0
    #define Si2146_MASTER_IEN_PROP_ATVIEN_OFF  0
    #define Si2146_MASTER_IEN_PROP_ATVIEN_ON   1

   /* MASTER_IEN property, CTSIEN field definition (NO TITLE)*/
   #define  Si2146_MASTER_IEN_PROP_CTSIEN_LSB         7
   #define  Si2146_MASTER_IEN_PROP_CTSIEN_MASK        0x01
   #define  Si2146_MASTER_IEN_PROP_CTSIEN_DEFAULT    0
    #define Si2146_MASTER_IEN_PROP_CTSIEN_OFF  0
    #define Si2146_MASTER_IEN_PROP_CTSIEN_ON   1

   /* MASTER_IEN property, DTVIEN field definition (NO TITLE)*/
   #define  Si2146_MASTER_IEN_PROP_DTVIEN_LSB         2
   #define  Si2146_MASTER_IEN_PROP_DTVIEN_MASK        0x01
   #define  Si2146_MASTER_IEN_PROP_DTVIEN_DEFAULT    0
    #define Si2146_MASTER_IEN_PROP_DTVIEN_OFF  0
    #define Si2146_MASTER_IEN_PROP_DTVIEN_ON   1

   /* MASTER_IEN property, ERRIEN field definition (NO TITLE)*/
   #define  Si2146_MASTER_IEN_PROP_ERRIEN_LSB         6
   #define  Si2146_MASTER_IEN_PROP_ERRIEN_MASK        0x01
   #define  Si2146_MASTER_IEN_PROP_ERRIEN_DEFAULT    0
    #define Si2146_MASTER_IEN_PROP_ERRIEN_OFF  0
    #define Si2146_MASTER_IEN_PROP_ERRIEN_ON   1

   /* MASTER_IEN property, TUNIEN field definition (NO TITLE)*/
   #define  Si2146_MASTER_IEN_PROP_TUNIEN_LSB         0
   #define  Si2146_MASTER_IEN_PROP_TUNIEN_MASK        0x01
   #define  Si2146_MASTER_IEN_PROP_TUNIEN_DEFAULT    0
    #define Si2146_MASTER_IEN_PROP_TUNIEN_OFF  0
    #define Si2146_MASTER_IEN_PROP_TUNIEN_ON   1

#endif /* Si2146_MASTER_IEN_PROP */

/* Si2146 TUNER_BLOCKED_VCO property definition */
#define   Si2146_TUNER_BLOCKED_VCO_PROP 0x0504

#ifdef    Si2146_TUNER_BLOCKED_VCO_PROP
  #define Si2146_TUNER_BLOCKED_VCO_PROP_CODE 0x000504


    typedef struct { /* Si2146_TUNER_BLOCKED_VCO_PROP_struct */
               int    vco_code;
   } Si2146_TUNER_BLOCKED_VCO_PROP_struct;

   /* TUNER_BLOCKED_VCO property, VCO_CODE field definition (NO TITLE)*/
   #define  Si2146_TUNER_BLOCKED_VCO_PROP_VCO_CODE_LSB         0
   #define  Si2146_TUNER_BLOCKED_VCO_PROP_VCO_CODE_MASK        0xffff
   #define  Si2146_TUNER_BLOCKED_VCO_PROP_VCO_CODE_DEFAULT    0x8000
    #define Si2146_TUNER_BLOCKED_VCO_PROP_VCO_CODE_VCO_CODE_MIN  -32768
    #define Si2146_TUNER_BLOCKED_VCO_PROP_VCO_CODE_VCO_CODE_MAX  32767

#endif /* Si2146_TUNER_BLOCKED_VCO_PROP */

/* Si2146 TUNER_IEN property definition */
#define   Si2146_TUNER_IEN_PROP 0x0501

#ifdef    Si2146_TUNER_IEN_PROP
  #define Si2146_TUNER_IEN_PROP_CODE 0x000501


    typedef struct { /* Si2146_TUNER_IEN_PROP_struct */
      unsigned char   rssihien;
      unsigned char   rssilien;
      unsigned char   tcien;
   } Si2146_TUNER_IEN_PROP_struct;

   /* TUNER_IEN property, RSSIHIEN field definition (NO TITLE)*/
   #define  Si2146_TUNER_IEN_PROP_RSSIHIEN_LSB         2
   #define  Si2146_TUNER_IEN_PROP_RSSIHIEN_MASK        0x01
   #define  Si2146_TUNER_IEN_PROP_RSSIHIEN_DEFAULT    0
    #define Si2146_TUNER_IEN_PROP_RSSIHIEN_DISABLE  0
    #define Si2146_TUNER_IEN_PROP_RSSIHIEN_ENABLE   1

   /* TUNER_IEN property, RSSILIEN field definition (NO TITLE)*/
   #define  Si2146_TUNER_IEN_PROP_RSSILIEN_LSB         1
   #define  Si2146_TUNER_IEN_PROP_RSSILIEN_MASK        0x01
   #define  Si2146_TUNER_IEN_PROP_RSSILIEN_DEFAULT    0
    #define Si2146_TUNER_IEN_PROP_RSSILIEN_DISABLE  0
    #define Si2146_TUNER_IEN_PROP_RSSILIEN_ENABLE   1

   /* TUNER_IEN property, TCIEN field definition (NO TITLE)*/
   #define  Si2146_TUNER_IEN_PROP_TCIEN_LSB         0
   #define  Si2146_TUNER_IEN_PROP_TCIEN_MASK        0x01
   #define  Si2146_TUNER_IEN_PROP_TCIEN_DEFAULT    0
    #define Si2146_TUNER_IEN_PROP_TCIEN_DISABLE  0
    #define Si2146_TUNER_IEN_PROP_TCIEN_ENABLE   1

#endif /* Si2146_TUNER_IEN_PROP */

/* Si2146 TUNER_INT_SENSE property definition */
#define   Si2146_TUNER_INT_SENSE_PROP 0x0505

#ifdef    Si2146_TUNER_INT_SENSE_PROP
  #define Si2146_TUNER_INT_SENSE_PROP_CODE 0x000505


    typedef struct { /* Si2146_TUNER_INT_SENSE_PROP_struct */
      unsigned char   rssihnegen;
      unsigned char   rssihposen;
      unsigned char   rssilnegen;
      unsigned char   rssilposen;
      unsigned char   tcnegen;
      unsigned char   tcposen;
   } Si2146_TUNER_INT_SENSE_PROP_struct;

   /* TUNER_INT_SENSE property, RSSIHNEGEN field definition (NO TITLE)*/
   #define  Si2146_TUNER_INT_SENSE_PROP_RSSIHNEGEN_LSB         2
   #define  Si2146_TUNER_INT_SENSE_PROP_RSSIHNEGEN_MASK        0x01
   #define  Si2146_TUNER_INT_SENSE_PROP_RSSIHNEGEN_DEFAULT    0
    #define Si2146_TUNER_INT_SENSE_PROP_RSSIHNEGEN_DISABLE  0
    #define Si2146_TUNER_INT_SENSE_PROP_RSSIHNEGEN_ENABLE   1

   /* TUNER_INT_SENSE property, RSSIHPOSEN field definition (NO TITLE)*/
   #define  Si2146_TUNER_INT_SENSE_PROP_RSSIHPOSEN_LSB         10
   #define  Si2146_TUNER_INT_SENSE_PROP_RSSIHPOSEN_MASK        0x01
   #define  Si2146_TUNER_INT_SENSE_PROP_RSSIHPOSEN_DEFAULT    1
    #define Si2146_TUNER_INT_SENSE_PROP_RSSIHPOSEN_DISABLE  0
    #define Si2146_TUNER_INT_SENSE_PROP_RSSIHPOSEN_ENABLE   1

   /* TUNER_INT_SENSE property, RSSILNEGEN field definition (NO TITLE)*/
   #define  Si2146_TUNER_INT_SENSE_PROP_RSSILNEGEN_LSB         1
   #define  Si2146_TUNER_INT_SENSE_PROP_RSSILNEGEN_MASK        0x01
   #define  Si2146_TUNER_INT_SENSE_PROP_RSSILNEGEN_DEFAULT    0
    #define Si2146_TUNER_INT_SENSE_PROP_RSSILNEGEN_DISABLE  0
    #define Si2146_TUNER_INT_SENSE_PROP_RSSILNEGEN_ENABLE   1

   /* TUNER_INT_SENSE property, RSSILPOSEN field definition (NO TITLE)*/
   #define  Si2146_TUNER_INT_SENSE_PROP_RSSILPOSEN_LSB         9
   #define  Si2146_TUNER_INT_SENSE_PROP_RSSILPOSEN_MASK        0x01
   #define  Si2146_TUNER_INT_SENSE_PROP_RSSILPOSEN_DEFAULT    1
    #define Si2146_TUNER_INT_SENSE_PROP_RSSILPOSEN_DISABLE  0
    #define Si2146_TUNER_INT_SENSE_PROP_RSSILPOSEN_ENABLE   1

   /* TUNER_INT_SENSE property, TCNEGEN field definition (NO TITLE)*/
   #define  Si2146_TUNER_INT_SENSE_PROP_TCNEGEN_LSB         0
   #define  Si2146_TUNER_INT_SENSE_PROP_TCNEGEN_MASK        0x01
   #define  Si2146_TUNER_INT_SENSE_PROP_TCNEGEN_DEFAULT    0
    #define Si2146_TUNER_INT_SENSE_PROP_TCNEGEN_DISABLE  0
    #define Si2146_TUNER_INT_SENSE_PROP_TCNEGEN_ENABLE   1

   /* TUNER_INT_SENSE property, TCPOSEN field definition (NO TITLE)*/
   #define  Si2146_TUNER_INT_SENSE_PROP_TCPOSEN_LSB         8
   #define  Si2146_TUNER_INT_SENSE_PROP_TCPOSEN_MASK        0x01
   #define  Si2146_TUNER_INT_SENSE_PROP_TCPOSEN_DEFAULT    1
    #define Si2146_TUNER_INT_SENSE_PROP_TCPOSEN_DISABLE  0
    #define Si2146_TUNER_INT_SENSE_PROP_TCPOSEN_ENABLE   1

#endif /* Si2146_TUNER_INT_SENSE_PROP */

/* Si2146 TUNER_LO_INJECTION property definition */
#define   Si2146_TUNER_LO_INJECTION_PROP 0x0506

#ifdef    Si2146_TUNER_LO_INJECTION_PROP
  #define Si2146_TUNER_LO_INJECTION_PROP_CODE 0x000506


    typedef struct { /* Si2146_TUNER_LO_INJECTION_PROP_struct */
      unsigned char   band_1;
      unsigned char   band_2;
      unsigned char   band_3;
      unsigned char   band_4;
      unsigned char   band_5;
   } Si2146_TUNER_LO_INJECTION_PROP_struct;

   /* TUNER_LO_INJECTION property, BAND_1 field definition (NO TITLE)*/
   #define  Si2146_TUNER_LO_INJECTION_PROP_BAND_1_LSB         0
   #define  Si2146_TUNER_LO_INJECTION_PROP_BAND_1_MASK        0x01
   #define  Si2146_TUNER_LO_INJECTION_PROP_BAND_1_DEFAULT    1
    #define Si2146_TUNER_LO_INJECTION_PROP_BAND_1_LOW_SIDE   0
    #define Si2146_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE  1

   /* TUNER_LO_INJECTION property, BAND_2 field definition (NO TITLE)*/
   #define  Si2146_TUNER_LO_INJECTION_PROP_BAND_2_LSB         1
   #define  Si2146_TUNER_LO_INJECTION_PROP_BAND_2_MASK        0x01
   #define  Si2146_TUNER_LO_INJECTION_PROP_BAND_2_DEFAULT    0
    #define Si2146_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE   0
    #define Si2146_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE  1

   /* TUNER_LO_INJECTION property, BAND_3 field definition (NO TITLE)*/
   #define  Si2146_TUNER_LO_INJECTION_PROP_BAND_3_LSB         2
   #define  Si2146_TUNER_LO_INJECTION_PROP_BAND_3_MASK        0x01
   #define  Si2146_TUNER_LO_INJECTION_PROP_BAND_3_DEFAULT    0
    #define Si2146_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE   0
    #define Si2146_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE  1

   /* TUNER_LO_INJECTION property, BAND_4 field definition (NO TITLE)*/
   #define  Si2146_TUNER_LO_INJECTION_PROP_BAND_4_LSB         3
   #define  Si2146_TUNER_LO_INJECTION_PROP_BAND_4_MASK        0x01
   #define  Si2146_TUNER_LO_INJECTION_PROP_BAND_4_DEFAULT    0
    #define Si2146_TUNER_LO_INJECTION_PROP_BAND_4_LOW_SIDE   0
    #define Si2146_TUNER_LO_INJECTION_PROP_BAND_4_HIGH_SIDE  1

   /* TUNER_LO_INJECTION property, BAND_5 field definition (NO TITLE)*/
   #define  Si2146_TUNER_LO_INJECTION_PROP_BAND_5_LSB         4
   #define  Si2146_TUNER_LO_INJECTION_PROP_BAND_5_MASK        0x01
   #define  Si2146_TUNER_LO_INJECTION_PROP_BAND_5_DEFAULT    0
    #define Si2146_TUNER_LO_INJECTION_PROP_BAND_5_LOW_SIDE   0
    #define Si2146_TUNER_LO_INJECTION_PROP_BAND_5_HIGH_SIDE  1

#endif /* Si2146_TUNER_LO_INJECTION_PROP */

/* _properties_defines_insertion_point */

/* _properties_struct_insertion_start */

  /* --------------------------------------------*/
  /* PROPERTIES STRUCT                           */
  /* This stores all property fields             */
  /* --------------------------------------------*/
  typedef struct {
    #ifdef    Si2146_ATV_AFC_RANGE_PROP
              Si2146_ATV_AFC_RANGE_PROP_struct                 atv_afc_range;
    #endif /* Si2146_ATV_AFC_RANGE_PROP */
    #ifdef    Si2146_ATV_AF_OUT_PROP
              Si2146_ATV_AF_OUT_PROP_struct                    atv_af_out;
    #endif /* Si2146_ATV_AF_OUT_PROP */
    #ifdef    Si2146_ATV_AGC_SPEED_PROP
              Si2146_ATV_AGC_SPEED_PROP_struct                 atv_agc_speed;
    #endif /* Si2146_ATV_AGC_SPEED_PROP */
    #ifdef    Si2146_ATV_AUDIO_MODE_PROP
              Si2146_ATV_AUDIO_MODE_PROP_struct                atv_audio_mode;
    #endif /* Si2146_ATV_AUDIO_MODE_PROP */
    #ifdef    Si2146_ATV_CVBS_OUT_PROP
              Si2146_ATV_CVBS_OUT_PROP_struct                  atv_cvbs_out;
    #endif /* Si2146_ATV_CVBS_OUT_PROP */
    #ifdef    Si2146_ATV_CVBS_OUT_FINE_PROP
              Si2146_ATV_CVBS_OUT_FINE_PROP_struct             atv_cvbs_out_fine;
    #endif /* Si2146_ATV_CVBS_OUT_FINE_PROP */
    #ifdef    Si2146_ATV_IEN_PROP
              Si2146_ATV_IEN_PROP_struct                       atv_ien;
    #endif /* Si2146_ATV_IEN_PROP */
    #ifdef    Si2146_ATV_INT_SENSE_PROP
              Si2146_ATV_INT_SENSE_PROP_struct                 atv_int_sense;
    #endif /* Si2146_ATV_INT_SENSE_PROP */
    #ifdef    Si2146_ATV_RF_TOP_PROP
              Si2146_ATV_RF_TOP_PROP_struct                    atv_rf_top;
    #endif /* Si2146_ATV_RF_TOP_PROP */
    #ifdef    Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP
              Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP_struct        atv_rsq_rssi_threshold;
    #endif /* Si2146_ATV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef    Si2146_ATV_RSQ_SNR_THRESHOLD_PROP
              Si2146_ATV_RSQ_SNR_THRESHOLD_PROP_struct         atv_rsq_snr_threshold;
    #endif /* Si2146_ATV_RSQ_SNR_THRESHOLD_PROP */
    #ifdef    Si2146_ATV_SIF_OUT_PROP
              Si2146_ATV_SIF_OUT_PROP_struct                   atv_sif_out;
    #endif /* Si2146_ATV_SIF_OUT_PROP */
    #ifdef    Si2146_ATV_SOUND_AGC_LIMIT_PROP
              Si2146_ATV_SOUND_AGC_LIMIT_PROP_struct           atv_sound_agc_limit;
    #endif /* Si2146_ATV_SOUND_AGC_LIMIT_PROP */
    #ifdef    Si2146_ATV_SOUND_AGC_SPEED_PROP
              Si2146_ATV_SOUND_AGC_SPEED_PROP_struct           atv_sound_agc_speed;
    #endif /* Si2146_ATV_SOUND_AGC_SPEED_PROP */
    #ifdef    Si2146_ATV_VIDEO_EQUALIZER_PROP
              Si2146_ATV_VIDEO_EQUALIZER_PROP_struct           atv_video_equalizer;
    #endif /* Si2146_ATV_VIDEO_EQUALIZER_PROP */
    #ifdef    Si2146_ATV_VIDEO_MODE_PROP
              Si2146_ATV_VIDEO_MODE_PROP_struct                atv_video_mode;
    #endif /* Si2146_ATV_VIDEO_MODE_PROP */
    #ifdef    Si2146_ATV_VSNR_CAP_PROP
              Si2146_ATV_VSNR_CAP_PROP_struct                  atv_vsnr_cap;
    #endif /* Si2146_ATV_VSNR_CAP_PROP */
    #ifdef    Si2146_ATV_VSYNC_TRACKING_PROP
              Si2146_ATV_VSYNC_TRACKING_PROP_struct            atv_vsync_tracking;
    #endif /* Si2146_ATV_VSYNC_TRACKING_PROP */
    #ifdef    Si2146_CRYSTAL_TRIM_PROP
              Si2146_CRYSTAL_TRIM_PROP_struct            crystal_trim;
    #endif /* Si2146_CRYSTAL_TRIM_PROP */
    #ifdef    Si2146_DTV_AGC_FREEZE_INPUT_PROP
              Si2146_DTV_AGC_FREEZE_INPUT_PROP_struct          dtv_agc_freeze_input;
    #endif /* Si2146_DTV_AGC_FREEZE_INPUT_PROP */
    #ifdef    Si2146_DTV_AGC_SPEED_PROP
              Si2146_DTV_AGC_SPEED_PROP_struct           dtv_agc_speed;
    #endif /* Si2146_DTV_AGC_SPEED_PROP */
    #ifdef    Si2146_DTV_CONFIG_IF_PORT_PROP
              Si2146_DTV_CONFIG_IF_PORT_PROP_struct      dtv_config_if_port;
    #endif /* Si2146_DTV_CONFIG_IF_PORT_PROP */
    #ifdef    Si2146_DTV_EXT_AGC_PROP
              Si2146_DTV_EXT_AGC_PROP_struct             dtv_ext_agc;
    #endif /* Si2146_DTV_EXT_AGC_PROP */
    #ifdef    Si2146_DTV_IEN_PROP
              Si2146_DTV_IEN_PROP_struct                 dtv_ien;
    #endif /* Si2146_DTV_IEN_PROP */
    #ifdef    Si2146_DTV_INITIAL_AGC_SPEED_PROP
              Si2146_DTV_INITIAL_AGC_SPEED_PROP_struct         dtv_initial_agc_speed;
    #endif /* Si2146_DTV_INITIAL_AGC_SPEED_PROP */
    #ifdef    Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
              Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_struct  dtv_initial_agc_speed_period;
    #endif /* Si2146_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
    #ifdef    Si2146_DTV_INT_SENSE_PROP
              Si2146_DTV_INT_SENSE_PROP_struct           dtv_int_sense;
    #endif /* Si2146_DTV_INT_SENSE_PROP */
    #ifdef    Si2146_DTV_LIF_FREQ_PROP
              Si2146_DTV_LIF_FREQ_PROP_struct            dtv_lif_freq;
    #endif /* Si2146_DTV_LIF_FREQ_PROP */
    #ifdef    Si2146_DTV_LIF_OUT_PROP
              Si2146_DTV_LIF_OUT_PROP_struct             dtv_lif_out;
    #endif /* Si2146_DTV_LIF_OUT_PROP */
    #ifdef    Si2146_DTV_MODE_PROP
              Si2146_DTV_MODE_PROP_struct                dtv_mode;
    #endif /* Si2146_DTV_MODE_PROP */
    #ifdef    Si2146_DTV_RF_TOP_PROP
              Si2146_DTV_RF_TOP_PROP_struct              dtv_rf_top;
    #endif /* Si2146_DTV_RF_TOP_PROP */
    #ifdef    Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP
              Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP_struct  dtv_rsq_rssi_threshold;
    #endif /* Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef    Si2146_MASTER_IEN_PROP
              Si2146_MASTER_IEN_PROP_struct              master_ien;
    #endif /* Si2146_MASTER_IEN_PROP */
    #ifdef    Si2146_TUNER_BLOCKED_VCO_PROP
              Si2146_TUNER_BLOCKED_VCO_PROP_struct       tuner_blocked_vco;
    #endif /* Si2146_TUNER_BLOCKED_VCO_PROP */
    #ifdef    Si2146_TUNER_IEN_PROP
              Si2146_TUNER_IEN_PROP_struct               tuner_ien;
    #endif /* Si2146_TUNER_IEN_PROP */
    #ifdef    Si2146_TUNER_INT_SENSE_PROP
              Si2146_TUNER_INT_SENSE_PROP_struct         tuner_int_sense;
    #endif /* Si2146_TUNER_INT_SENSE_PROP */
    #ifdef    Si2146_TUNER_LO_INJECTION_PROP
              Si2146_TUNER_LO_INJECTION_PROP_struct      tuner_lo_injection;
    #endif /* Si2146_TUNER_LO_INJECTION_PROP */
  } Si2146_PropObj;
/* _properties_struct_insertion_point */

#define   Si2146_GET_PROPERTY_STRING

#endif /* _Si2146_PROPERTIES_H_ */





