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
                  Silicon Laboratories Broadcast Si2147 Layer 1 API


   API properties structures and functions definitions
   FILE: Si2147_Properties.h
   Supported IC : Si2147
   Compiled for ROM 50 firmware 3_1_build_3
   Revision: 0.1
   Date: June 30 2015
**************************************************************************************/
#ifndef   _Si2147_PROPERTIES_H_
#define   _Si2147_PROPERTIES_H_

/* Si2147 CRYSTAL_TRIM property definition */
#define   Si2147_CRYSTAL_TRIM_PROP 0x0402

#ifdef    Si2147_CRYSTAL_TRIM_PROP
  #define Si2147_CRYSTAL_TRIM_PROP_CODE 0x000402


    typedef struct { /* Si2147_CRYSTAL_TRIM_PROP_struct */
      unsigned char   xo_cap;
   } Si2147_CRYSTAL_TRIM_PROP_struct;

   /* CRYSTAL_TRIM property, XO_CAP field definition (NO TITLE)*/
   #define  Si2147_CRYSTAL_TRIM_PROP_XO_CAP_LSB         0
   #define  Si2147_CRYSTAL_TRIM_PROP_XO_CAP_MASK        0x0f
   #define  Si2147_CRYSTAL_TRIM_PROP_XO_CAP_DEFAULT    8
    #define Si2147_CRYSTAL_TRIM_PROP_XO_CAP_4P7PF   0
    #define Si2147_CRYSTAL_TRIM_PROP_XO_CAP_5P2PF   2
    #define Si2147_CRYSTAL_TRIM_PROP_XO_CAP_5P7PF   4
    #define Si2147_CRYSTAL_TRIM_PROP_XO_CAP_6P2PF   6
    #define Si2147_CRYSTAL_TRIM_PROP_XO_CAP_6P7PF   8
    #define Si2147_CRYSTAL_TRIM_PROP_XO_CAP_7P2PF   10
    #define Si2147_CRYSTAL_TRIM_PROP_XO_CAP_7P7PF   12
    #define Si2147_CRYSTAL_TRIM_PROP_XO_CAP_8P2PF   14

#endif /* Si2147_CRYSTAL_TRIM_PROP */

/* Si2147 DTV_AGC_AUTO_FREEZE property definition */
#define   Si2147_DTV_AGC_AUTO_FREEZE_PROP 0x0714

#ifdef    Si2147_DTV_AGC_AUTO_FREEZE_PROP
  #define Si2147_DTV_AGC_AUTO_FREEZE_PROP_CODE 0x000714


    typedef struct { /* Si2147_DTV_AGC_AUTO_FREEZE_PROP_struct */
      unsigned char   thld;
      unsigned char   timeout;
   } Si2147_DTV_AGC_AUTO_FREEZE_PROP_struct;

   /* DTV_AGC_AUTO_FREEZE property, THLD field definition (NO TITLE)*/
   #define  Si2147_DTV_AGC_AUTO_FREEZE_PROP_THLD_LSB         0
   #define  Si2147_DTV_AGC_AUTO_FREEZE_PROP_THLD_MASK        0xff
   #define  Si2147_DTV_AGC_AUTO_FREEZE_PROP_THLD_DEFAULT    255
    #define Si2147_DTV_AGC_AUTO_FREEZE_PROP_THLD_THLD_MIN  0
    #define Si2147_DTV_AGC_AUTO_FREEZE_PROP_THLD_THLD_MAX  255

   /* DTV_AGC_AUTO_FREEZE property, TIMEOUT field definition (NO TITLE)*/
   #define  Si2147_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT_LSB         8
   #define  Si2147_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT_MASK        0xff
   #define  Si2147_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT_DEFAULT    1
    #define Si2147_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT_TIMEOUT_MIN  1
    #define Si2147_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT_TIMEOUT_MAX  250

#endif /* Si2147_DTV_AGC_AUTO_FREEZE_PROP */

/* Si2147 DTV_AGC_FREEZE_INPUT property definition */
#define   Si2147_DTV_AGC_FREEZE_INPUT_PROP 0x0711

#ifdef    Si2147_DTV_AGC_FREEZE_INPUT_PROP
  #define Si2147_DTV_AGC_FREEZE_INPUT_PROP_CODE 0x000711


    typedef struct { /* Si2147_DTV_AGC_FREEZE_INPUT_PROP_struct */
      unsigned char   level;
      unsigned char   pin;
   } Si2147_DTV_AGC_FREEZE_INPUT_PROP_struct;

   /* DTV_AGC_FREEZE_INPUT property, LEVEL field definition (NO TITLE)*/
   #define  Si2147_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LSB         0
   #define  Si2147_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_MASK        0x01
   #define  Si2147_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_DEFAULT    0
    #define Si2147_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LOW   0
    #define Si2147_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_HIGH  1

   /* DTV_AGC_FREEZE_INPUT property, PIN field definition (NO TITLE)*/
   #define  Si2147_DTV_AGC_FREEZE_INPUT_PROP_PIN_LSB         1
   #define  Si2147_DTV_AGC_FREEZE_INPUT_PROP_PIN_MASK        0x07
   #define  Si2147_DTV_AGC_FREEZE_INPUT_PROP_PIN_DEFAULT    0
    #define Si2147_DTV_AGC_FREEZE_INPUT_PROP_PIN_NONE      0
    #define Si2147_DTV_AGC_FREEZE_INPUT_PROP_PIN_GPIO1     1
    #define Si2147_DTV_AGC_FREEZE_INPUT_PROP_PIN_GPIO2     2
    #define Si2147_DTV_AGC_FREEZE_INPUT_PROP_PIN_RESERVED  3
    #define Si2147_DTV_AGC_FREEZE_INPUT_PROP_PIN_AGC1      4
    #define Si2147_DTV_AGC_FREEZE_INPUT_PROP_PIN_AGC2      5

#endif /* Si2147_DTV_AGC_FREEZE_INPUT_PROP */

/* Si2147 DTV_AGC_SPEED property definition */
#define   Si2147_DTV_AGC_SPEED_PROP 0x0708

#ifdef    Si2147_DTV_AGC_SPEED_PROP
  #define Si2147_DTV_AGC_SPEED_PROP_CODE 0x000708


    typedef struct { /* Si2147_DTV_AGC_SPEED_PROP_struct */
      unsigned char   agc_decim;
      unsigned char   if_agc_speed;
   } Si2147_DTV_AGC_SPEED_PROP_struct;

   /* DTV_AGC_SPEED property, AGC_DECIM field definition (NO TITLE)*/
   #define  Si2147_DTV_AGC_SPEED_PROP_AGC_DECIM_LSB         8
   #define  Si2147_DTV_AGC_SPEED_PROP_AGC_DECIM_MASK        0x03
   #define  Si2147_DTV_AGC_SPEED_PROP_AGC_DECIM_DEFAULT    0
    #define Si2147_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF  0
    #define Si2147_DTV_AGC_SPEED_PROP_AGC_DECIM_2    1
    #define Si2147_DTV_AGC_SPEED_PROP_AGC_DECIM_4    2
    #define Si2147_DTV_AGC_SPEED_PROP_AGC_DECIM_8    3

   /* DTV_AGC_SPEED property, IF_AGC_SPEED field definition (NO TITLE)*/
   #define  Si2147_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB         0
   #define  Si2147_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK        0xff
   #define  Si2147_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_DEFAULT    0
    #define Si2147_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO  0
    #define Si2147_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_39    39
    #define Si2147_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_54    54
    #define Si2147_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_63    63
    #define Si2147_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_89    89
    #define Si2147_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_105   105
    #define Si2147_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_121   121
    #define Si2147_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_137   137
    #define Si2147_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_158   158
    #define Si2147_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_172   172
    #define Si2147_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_185   185
    #define Si2147_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_196   196
    #define Si2147_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_206   206
    #define Si2147_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_216   216
    #define Si2147_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_219   219
    #define Si2147_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_222   222

#endif /* Si2147_DTV_AGC_SPEED_PROP */

/* Si2147 DTV_CONFIG_IF_PORT property definition */
#define   Si2147_DTV_CONFIG_IF_PORT_PROP 0x0702

#ifdef    Si2147_DTV_CONFIG_IF_PORT_PROP
  #define Si2147_DTV_CONFIG_IF_PORT_PROP_CODE 0x000702


    typedef struct { /* Si2147_DTV_CONFIG_IF_PORT_PROP_struct */
      unsigned char   dtv_agc_source;
      unsigned char   dtv_out_type;
   } Si2147_DTV_CONFIG_IF_PORT_PROP_struct;

   /* DTV_CONFIG_IF_PORT property, DTV_AGC_SOURCE field definition (NO TITLE)*/
   #define  Si2147_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_LSB         8
   #define  Si2147_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_MASK        0x07
   #define  Si2147_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_DEFAULT    0
    #define Si2147_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_INTERNAL   0
    #define Si2147_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_AGC1_3DB   1
    #define Si2147_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_AGC2_3DB   2

   /* DTV_CONFIG_IF_PORT property, DTV_OUT_TYPE field definition (NO TITLE)*/
   #define  Si2147_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LSB         0
   #define  Si2147_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_MASK        0x0f
   #define  Si2147_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_DEFAULT    0
    #define Si2147_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_IF1      0
    #define Si2147_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_IF2      1
    #define Si2147_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_SE_IF1A  4
    #define Si2147_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_SE_IF2A  5

#endif /* Si2147_DTV_CONFIG_IF_PORT_PROP */

/* Si2147 DTV_EXT_AGC property definition */
#define   Si2147_DTV_EXT_AGC_PROP 0x0705

#ifdef    Si2147_DTV_EXT_AGC_PROP
  #define Si2147_DTV_EXT_AGC_PROP_CODE 0x000705


    typedef struct { /* Si2147_DTV_EXT_AGC_PROP_struct */
      unsigned char   max_10mv;
      unsigned char   min_10mv;
   } Si2147_DTV_EXT_AGC_PROP_struct;

   /* DTV_EXT_AGC property, MAX_10MV field definition (NO TITLE)*/
   #define  Si2147_DTV_EXT_AGC_PROP_MAX_10MV_LSB         8
   #define  Si2147_DTV_EXT_AGC_PROP_MAX_10MV_MASK        0xff
   #define  Si2147_DTV_EXT_AGC_PROP_MAX_10MV_DEFAULT    200
    #define Si2147_DTV_EXT_AGC_PROP_MAX_10MV_MAX_10MV_MIN  0
    #define Si2147_DTV_EXT_AGC_PROP_MAX_10MV_MAX_10MV_MAX  255

   /* DTV_EXT_AGC property, MIN_10MV field definition (NO TITLE)*/
   #define  Si2147_DTV_EXT_AGC_PROP_MIN_10MV_LSB         0
   #define  Si2147_DTV_EXT_AGC_PROP_MIN_10MV_MASK        0xff
   #define  Si2147_DTV_EXT_AGC_PROP_MIN_10MV_DEFAULT    50
    #define Si2147_DTV_EXT_AGC_PROP_MIN_10MV_MIN_10MV_MIN  0
    #define Si2147_DTV_EXT_AGC_PROP_MIN_10MV_MIN_10MV_MAX  255

#endif /* Si2147_DTV_EXT_AGC_PROP */

/* Si2147 DTV_IEN property definition */
#define   Si2147_DTV_IEN_PROP 0x0701

#ifdef    Si2147_DTV_IEN_PROP
  #define Si2147_DTV_IEN_PROP_CODE 0x000701


    typedef struct { /* Si2147_DTV_IEN_PROP_struct */
      unsigned char   chlien;
   } Si2147_DTV_IEN_PROP_struct;

   /* DTV_IEN property, CHLIEN field definition (NO TITLE)*/
   #define  Si2147_DTV_IEN_PROP_CHLIEN_LSB         0
   #define  Si2147_DTV_IEN_PROP_CHLIEN_MASK        0x01
   #define  Si2147_DTV_IEN_PROP_CHLIEN_DEFAULT    1
    #define Si2147_DTV_IEN_PROP_CHLIEN_DISABLE  0
    #define Si2147_DTV_IEN_PROP_CHLIEN_ENABLE   1

#endif /* Si2147_DTV_IEN_PROP */

/* Si2147 DTV_IF_AGC_SPEED property definition */
#define   Si2147_DTV_IF_AGC_SPEED_PROP 0x0716

#ifdef    Si2147_DTV_IF_AGC_SPEED_PROP
  #define Si2147_DTV_IF_AGC_SPEED_PROP_CODE 0x000716


    typedef struct { /* Si2147_DTV_IF_AGC_SPEED_PROP_struct */
      unsigned char   attack;
      unsigned char   decay;
   } Si2147_DTV_IF_AGC_SPEED_PROP_struct;

   /* DTV_IF_AGC_SPEED property, ATTACK field definition (NO TITLE)*/
   #define  Si2147_DTV_IF_AGC_SPEED_PROP_ATTACK_LSB         0
   #define  Si2147_DTV_IF_AGC_SPEED_PROP_ATTACK_MASK        0xff
   #define  Si2147_DTV_IF_AGC_SPEED_PROP_ATTACK_DEFAULT    0
    #define Si2147_DTV_IF_AGC_SPEED_PROP_ATTACK_AUTO  0

    #define Si2147_DTV_IF_AGC_SPEED_PROP_ATTACK_ATTACK_MIN  0
    #define Si2147_DTV_IF_AGC_SPEED_PROP_ATTACK_ATTACK_MAX  231

   /* DTV_IF_AGC_SPEED property, DECAY field definition (NO TITLE)*/
   #define  Si2147_DTV_IF_AGC_SPEED_PROP_DECAY_LSB         8
   #define  Si2147_DTV_IF_AGC_SPEED_PROP_DECAY_MASK        0xff
   #define  Si2147_DTV_IF_AGC_SPEED_PROP_DECAY_DEFAULT    0
    #define Si2147_DTV_IF_AGC_SPEED_PROP_DECAY_AUTO  0

    #define Si2147_DTV_IF_AGC_SPEED_PROP_DECAY_DECAY_MIN  0
    #define Si2147_DTV_IF_AGC_SPEED_PROP_DECAY_DECAY_MAX  231

#endif /* Si2147_DTV_IF_AGC_SPEED_PROP */

/* Si2147 DTV_INITIAL_AGC_SPEED property definition */
#define   Si2147_DTV_INITIAL_AGC_SPEED_PROP 0x070d

#ifdef    Si2147_DTV_INITIAL_AGC_SPEED_PROP
  #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_CODE 0x00070d


    typedef struct { /* Si2147_DTV_INITIAL_AGC_SPEED_PROP_struct */
      unsigned char   agc_decim;
      unsigned char   if_agc_speed;
   } Si2147_DTV_INITIAL_AGC_SPEED_PROP_struct;

   /* DTV_INITIAL_AGC_SPEED property, AGC_DECIM field definition (NO TITLE)*/
   #define  Si2147_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_LSB         8
   #define  Si2147_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_MASK        0x03
   #define  Si2147_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_DEFAULT    0
    #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_OFF  0
    #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_2    1
    #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_4    2
    #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_8    3

   /* DTV_INITIAL_AGC_SPEED property, IF_AGC_SPEED field definition (NO TITLE)*/
   #define  Si2147_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_LSB         0
   #define  Si2147_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_MASK        0xff
   #define  Si2147_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_DEFAULT    0
    #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO  0
    #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_39    39
    #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_54    54
    #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_63    63
    #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_89    89
    #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_105   105
    #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_121   121
    #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_137   137
    #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_158   158
    #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_172   172
    #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_185   185
    #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_196   196
    #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_206   206
    #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_216   216
    #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_219   219
    #define Si2147_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_222   222

#endif /* Si2147_DTV_INITIAL_AGC_SPEED_PROP */

/* Si2147 DTV_INITIAL_AGC_SPEED_PERIOD property definition */
#define   Si2147_DTV_INITIAL_AGC_SPEED_PERIOD_PROP 0x070e

#ifdef    Si2147_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
  #define Si2147_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE 0x00070e


    typedef struct { /* Si2147_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_struct */
      unsigned int    period;
   } Si2147_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_struct;

   /* DTV_INITIAL_AGC_SPEED_PERIOD property, PERIOD field definition (NO TITLE)*/
   #define  Si2147_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_LSB         0
   #define  Si2147_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_MASK        0xffff
   #define  Si2147_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_DEFAULT    0
    #define Si2147_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_PERIOD_MIN  0
    #define Si2147_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_PERIOD_MAX  65535

#endif /* Si2147_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */

/* Si2147 DTV_INTERNAL_ZIF property definition */
#define   Si2147_DTV_INTERNAL_ZIF_PROP 0x0710

#ifdef    Si2147_DTV_INTERNAL_ZIF_PROP
  #define Si2147_DTV_INTERNAL_ZIF_PROP_CODE 0x000710


    typedef struct { /* Si2147_DTV_INTERNAL_ZIF_PROP_struct */
      unsigned char   atsc;
      unsigned char   dtmb;
      unsigned char   dvbc;
      unsigned char   dvbt;
      unsigned char   isdbc;
      unsigned char   isdbt;
      unsigned char   qam_us;
   } Si2147_DTV_INTERNAL_ZIF_PROP_struct;

   /* DTV_INTERNAL_ZIF property, ATSC field definition (NO TITLE)*/
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_ATSC_LSB         0
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_ATSC_MASK        0x01
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_ATSC_DEFAULT    1
    #define Si2147_DTV_INTERNAL_ZIF_PROP_ATSC_LIF  0
    #define Si2147_DTV_INTERNAL_ZIF_PROP_ATSC_ZIF  1

   /* DTV_INTERNAL_ZIF property, DTMB field definition (NO TITLE)*/
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_DTMB_LSB         6
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_DTMB_MASK        0x01
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_DTMB_DEFAULT    0
    #define Si2147_DTV_INTERNAL_ZIF_PROP_DTMB_LIF  0
    #define Si2147_DTV_INTERNAL_ZIF_PROP_DTMB_ZIF  1

   /* DTV_INTERNAL_ZIF property, DVBC field definition (NO TITLE)*/
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_DVBC_LSB         3
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_DVBC_MASK        0x01
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_DVBC_DEFAULT    1
    #define Si2147_DTV_INTERNAL_ZIF_PROP_DVBC_LIF  0
    #define Si2147_DTV_INTERNAL_ZIF_PROP_DVBC_ZIF  1

   /* DTV_INTERNAL_ZIF property, DVBT field definition (NO TITLE)*/
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_DVBT_LSB         2
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_DVBT_MASK        0x01
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_DVBT_DEFAULT    1
    #define Si2147_DTV_INTERNAL_ZIF_PROP_DVBT_LIF  0
    #define Si2147_DTV_INTERNAL_ZIF_PROP_DVBT_ZIF  1

   /* DTV_INTERNAL_ZIF property, ISDBC field definition (NO TITLE)*/
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_ISDBC_LSB         5
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_ISDBC_MASK        0x01
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_ISDBC_DEFAULT    1
    #define Si2147_DTV_INTERNAL_ZIF_PROP_ISDBC_LIF  0
    #define Si2147_DTV_INTERNAL_ZIF_PROP_ISDBC_ZIF  1

   /* DTV_INTERNAL_ZIF property, ISDBT field definition (NO TITLE)*/
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_ISDBT_LSB         4
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_ISDBT_MASK        0x01
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_ISDBT_DEFAULT    1
    #define Si2147_DTV_INTERNAL_ZIF_PROP_ISDBT_LIF  0
    #define Si2147_DTV_INTERNAL_ZIF_PROP_ISDBT_ZIF  1

   /* DTV_INTERNAL_ZIF property, QAM_US field definition (NO TITLE)*/
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_QAM_US_LSB         1
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_QAM_US_MASK        0x01
   #define  Si2147_DTV_INTERNAL_ZIF_PROP_QAM_US_DEFAULT    1
    #define Si2147_DTV_INTERNAL_ZIF_PROP_QAM_US_LIF  0
    #define Si2147_DTV_INTERNAL_ZIF_PROP_QAM_US_ZIF  1

#endif /* Si2147_DTV_INTERNAL_ZIF_PROP */

/* Si2147 DTV_INT_SENSE property definition */
#define   Si2147_DTV_INT_SENSE_PROP 0x070a

#ifdef    Si2147_DTV_INT_SENSE_PROP
  #define Si2147_DTV_INT_SENSE_PROP_CODE 0x00070a


    typedef struct { /* Si2147_DTV_INT_SENSE_PROP_struct */
      unsigned char   chlnegen;
      unsigned char   chlposen;
   } Si2147_DTV_INT_SENSE_PROP_struct;

   /* DTV_INT_SENSE property, CHLNEGEN field definition (NO TITLE)*/
   #define  Si2147_DTV_INT_SENSE_PROP_CHLNEGEN_LSB         0
   #define  Si2147_DTV_INT_SENSE_PROP_CHLNEGEN_MASK        0x01
   #define  Si2147_DTV_INT_SENSE_PROP_CHLNEGEN_DEFAULT    0
    #define Si2147_DTV_INT_SENSE_PROP_CHLNEGEN_DISABLE  0
    #define Si2147_DTV_INT_SENSE_PROP_CHLNEGEN_ENABLE   1

   /* DTV_INT_SENSE property, CHLPOSEN field definition (NO TITLE)*/
   #define  Si2147_DTV_INT_SENSE_PROP_CHLPOSEN_LSB         8
   #define  Si2147_DTV_INT_SENSE_PROP_CHLPOSEN_MASK        0x01
   #define  Si2147_DTV_INT_SENSE_PROP_CHLPOSEN_DEFAULT    1
    #define Si2147_DTV_INT_SENSE_PROP_CHLPOSEN_DISABLE  0
    #define Si2147_DTV_INT_SENSE_PROP_CHLPOSEN_ENABLE   1

#endif /* Si2147_DTV_INT_SENSE_PROP */

/* Si2147 DTV_LIF_FREQ property definition */
#define   Si2147_DTV_LIF_FREQ_PROP 0x0706

#ifdef    Si2147_DTV_LIF_FREQ_PROP
  #define Si2147_DTV_LIF_FREQ_PROP_CODE 0x000706


    typedef struct { /* Si2147_DTV_LIF_FREQ_PROP_struct */
      unsigned int    offset;
   } Si2147_DTV_LIF_FREQ_PROP_struct;

   /* DTV_LIF_FREQ property, OFFSET field definition (NO TITLE)*/
   #define  Si2147_DTV_LIF_FREQ_PROP_OFFSET_LSB         0
   #define  Si2147_DTV_LIF_FREQ_PROP_OFFSET_MASK        0xffff
   #define  Si2147_DTV_LIF_FREQ_PROP_OFFSET_DEFAULT    5000
    #define Si2147_DTV_LIF_FREQ_PROP_OFFSET_OFFSET_MIN  0
    #define Si2147_DTV_LIF_FREQ_PROP_OFFSET_OFFSET_MAX  7000

#endif /* Si2147_DTV_LIF_FREQ_PROP */

/* Si2147 DTV_LIF_OUT property definition */
#define   Si2147_DTV_LIF_OUT_PROP 0x0707

#ifdef    Si2147_DTV_LIF_OUT_PROP
  #define Si2147_DTV_LIF_OUT_PROP_CODE 0x000707


    typedef struct { /* Si2147_DTV_LIF_OUT_PROP_struct */
      unsigned char   amp;
      unsigned char   offset;
   } Si2147_DTV_LIF_OUT_PROP_struct;

   /* DTV_LIF_OUT property, AMP field definition (NO TITLE)*/
   #define  Si2147_DTV_LIF_OUT_PROP_AMP_LSB         8
   #define  Si2147_DTV_LIF_OUT_PROP_AMP_MASK        0xff
   #define  Si2147_DTV_LIF_OUT_PROP_AMP_DEFAULT    27
    #define Si2147_DTV_LIF_OUT_PROP_AMP_AMP_MIN  0
    #define Si2147_DTV_LIF_OUT_PROP_AMP_AMP_MAX  255

   /* DTV_LIF_OUT property, OFFSET field definition (NO TITLE)*/
   #define  Si2147_DTV_LIF_OUT_PROP_OFFSET_LSB         0
   #define  Si2147_DTV_LIF_OUT_PROP_OFFSET_MASK        0xff
   #define  Si2147_DTV_LIF_OUT_PROP_OFFSET_DEFAULT    148
    #define Si2147_DTV_LIF_OUT_PROP_OFFSET_OFFSET_MIN  0
    #define Si2147_DTV_LIF_OUT_PROP_OFFSET_OFFSET_MAX  255

#endif /* Si2147_DTV_LIF_OUT_PROP */

/* Si2147 DTV_MODE property definition */
#define   Si2147_DTV_MODE_PROP 0x0703

#ifdef    Si2147_DTV_MODE_PROP
  #define Si2147_DTV_MODE_PROP_CODE 0x000703


    typedef struct { /* Si2147_DTV_MODE_PROP_struct */
      unsigned char   bw;
      unsigned char   invert_spectrum;
      unsigned char   modulation;
   } Si2147_DTV_MODE_PROP_struct;

   /* DTV_MODE property, BW field definition (NO TITLE)*/
   #define  Si2147_DTV_MODE_PROP_BW_LSB         0
   #define  Si2147_DTV_MODE_PROP_BW_MASK        0x0f
   #define  Si2147_DTV_MODE_PROP_BW_DEFAULT    8
    #define Si2147_DTV_MODE_PROP_BW_BW_6MHZ    6
    #define Si2147_DTV_MODE_PROP_BW_BW_7MHZ    7
    #define Si2147_DTV_MODE_PROP_BW_BW_8MHZ    8
    #define Si2147_DTV_MODE_PROP_BW_BW_1P7MHZ  9
    #define Si2147_DTV_MODE_PROP_BW_BW_6P1MHZ  10

   /* DTV_MODE property, INVERT_SPECTRUM field definition (NO TITLE)*/
   #define  Si2147_DTV_MODE_PROP_INVERT_SPECTRUM_LSB         8
   #define  Si2147_DTV_MODE_PROP_INVERT_SPECTRUM_MASK        0x01
   #define  Si2147_DTV_MODE_PROP_INVERT_SPECTRUM_DEFAULT    0
    #define Si2147_DTV_MODE_PROP_INVERT_SPECTRUM_NORMAL    0
    #define Si2147_DTV_MODE_PROP_INVERT_SPECTRUM_INVERTED  1

   /* DTV_MODE property, MODULATION field definition (NO TITLE)*/
   #define  Si2147_DTV_MODE_PROP_MODULATION_LSB         4
   #define  Si2147_DTV_MODE_PROP_MODULATION_MASK        0x0f
   #define  Si2147_DTV_MODE_PROP_MODULATION_DEFAULT    2
    #define Si2147_DTV_MODE_PROP_MODULATION_ATSC       0
    #define Si2147_DTV_MODE_PROP_MODULATION_QAM_US     1
    #define Si2147_DTV_MODE_PROP_MODULATION_DVBT       2
    #define Si2147_DTV_MODE_PROP_MODULATION_DVBC       3
    #define Si2147_DTV_MODE_PROP_MODULATION_ISDBT      4
    #define Si2147_DTV_MODE_PROP_MODULATION_ISDBC      5
    #define Si2147_DTV_MODE_PROP_MODULATION_DTMB       6

#endif /* Si2147_DTV_MODE_PROP */

/* Si2147 DTV_PGA_LIMITS property definition */
#define   Si2147_DTV_PGA_LIMITS_PROP 0x0713

#ifdef    Si2147_DTV_PGA_LIMITS_PROP
  #define Si2147_DTV_PGA_LIMITS_PROP_CODE 0x000713


    typedef struct { /* Si2147_DTV_PGA_LIMITS_PROP_struct */
               char   max;
               char   min;
   } Si2147_DTV_PGA_LIMITS_PROP_struct;

   /* DTV_PGA_LIMITS property, MAX field definition (NO TITLE)*/
   #define  Si2147_DTV_PGA_LIMITS_PROP_MAX_LSB         8
   #define  Si2147_DTV_PGA_LIMITS_PROP_MAX_MASK        0xff
   #define  Si2147_DTV_PGA_LIMITS_PROP_MAX_DEFAULT    -1
    #define Si2147_DTV_PGA_LIMITS_PROP_MAX_MAX_MIN  -1
    #define Si2147_DTV_PGA_LIMITS_PROP_MAX_MAX_MAX  56

   /* DTV_PGA_LIMITS property, MIN field definition (NO TITLE)*/
   #define  Si2147_DTV_PGA_LIMITS_PROP_MIN_LSB         0
   #define  Si2147_DTV_PGA_LIMITS_PROP_MIN_MASK        0xff
   #define  Si2147_DTV_PGA_LIMITS_PROP_MIN_DEFAULT    -1
    #define Si2147_DTV_PGA_LIMITS_PROP_MIN_MIN_MIN  -1
    #define Si2147_DTV_PGA_LIMITS_PROP_MIN_MIN_MAX  56

#endif /* Si2147_DTV_PGA_LIMITS_PROP */

/* Si2147 DTV_PGA_TARGET property definition */
#define   Si2147_DTV_PGA_TARGET_PROP 0x070f

#ifdef    Si2147_DTV_PGA_TARGET_PROP
  #define Si2147_DTV_PGA_TARGET_PROP_CODE 0x00070f


    typedef struct { /* Si2147_DTV_PGA_TARGET_PROP_struct */
      unsigned char   override_enable;
               char   pga_target;
   } Si2147_DTV_PGA_TARGET_PROP_struct;

   /* DTV_PGA_TARGET property, OVERRIDE_ENABLE field definition (NO TITLE)*/
   #define  Si2147_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_LSB         8
   #define  Si2147_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_MASK        0x01
   #define  Si2147_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_DEFAULT    0
    #define Si2147_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_DISABLE  0
    #define Si2147_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_ENABLE   1

   /* DTV_PGA_TARGET property, PGA_TARGET field definition (NO TITLE)*/
   #define  Si2147_DTV_PGA_TARGET_PROP_PGA_TARGET_LSB         0
   #define  Si2147_DTV_PGA_TARGET_PROP_PGA_TARGET_MASK        0xff
   #define  Si2147_DTV_PGA_TARGET_PROP_PGA_TARGET_DEFAULT    0
    #define Si2147_DTV_PGA_TARGET_PROP_PGA_TARGET_PGA_TARGET_MIN  -13
    #define Si2147_DTV_PGA_TARGET_PROP_PGA_TARGET_PGA_TARGET_MAX  7

#endif /* Si2147_DTV_PGA_TARGET_PROP */

/* Si2147 DTV_RF_AGC_SPEED property definition */
#define   Si2147_DTV_RF_AGC_SPEED_PROP 0x0715

#ifdef    Si2147_DTV_RF_AGC_SPEED_PROP
  #define Si2147_DTV_RF_AGC_SPEED_PROP_CODE 0x000715


    typedef struct { /* Si2147_DTV_RF_AGC_SPEED_PROP_struct */
      unsigned char   attack;
      unsigned char   decay;
   } Si2147_DTV_RF_AGC_SPEED_PROP_struct;

   /* DTV_RF_AGC_SPEED property, ATTACK field definition (NO TITLE)*/
   #define  Si2147_DTV_RF_AGC_SPEED_PROP_ATTACK_LSB         0
   #define  Si2147_DTV_RF_AGC_SPEED_PROP_ATTACK_MASK        0xff
   #define  Si2147_DTV_RF_AGC_SPEED_PROP_ATTACK_DEFAULT    0
    #define Si2147_DTV_RF_AGC_SPEED_PROP_ATTACK_AUTO  0

    #define Si2147_DTV_RF_AGC_SPEED_PROP_ATTACK_ATTACK_MIN  0
    #define Si2147_DTV_RF_AGC_SPEED_PROP_ATTACK_ATTACK_MAX  231

   /* DTV_RF_AGC_SPEED property, DECAY field definition (NO TITLE)*/
   #define  Si2147_DTV_RF_AGC_SPEED_PROP_DECAY_LSB         8
   #define  Si2147_DTV_RF_AGC_SPEED_PROP_DECAY_MASK        0xff
   #define  Si2147_DTV_RF_AGC_SPEED_PROP_DECAY_DEFAULT    0
    #define Si2147_DTV_RF_AGC_SPEED_PROP_DECAY_AUTO  0

    #define Si2147_DTV_RF_AGC_SPEED_PROP_DECAY_DECAY_MIN  0
    #define Si2147_DTV_RF_AGC_SPEED_PROP_DECAY_DECAY_MAX  231

#endif /* Si2147_DTV_RF_AGC_SPEED_PROP */

/* Si2147 DTV_RF_TOP property definition */
#define   Si2147_DTV_RF_TOP_PROP 0x0709

#ifdef    Si2147_DTV_RF_TOP_PROP
  #define Si2147_DTV_RF_TOP_PROP_CODE 0x000709


    typedef struct { /* Si2147_DTV_RF_TOP_PROP_struct */
      unsigned char   dtv_rf_top;
   } Si2147_DTV_RF_TOP_PROP_struct;

   /* DTV_RF_TOP property, DTV_RF_TOP field definition (NO TITLE)*/
   #define  Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_LSB         0
   #define  Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_MASK        0xff
   #define  Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_DEFAULT    0
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_AUTO     0
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_P6DB     9
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_P5P5DB   10
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_P5DB     11
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_P4P5DB   12
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_P4DB     13
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_P3P5DB   14
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_P3DB     15
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_P2P5DB   16
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_P2DB     17
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_P1P5DB   18
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_P1DB     19
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_P0P5DB   20
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_0DB      21
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M0P5DB   22
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M1DB     23
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M1P5DB   24
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M2DB     25
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M2P5DB   26
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M3DB     27
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M3P5DB   28
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M4DB     29
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M4P5DB   30
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M5DB     31
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M5P5DB   32
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M6DB     33
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M6P5DB   34
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M7DB     35
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M7P5DB   36
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M8DB     37
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M8P5DB   38
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M9DB     39
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M9P5DB   40
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M10DB    41
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M10P5DB  42
    #define Si2147_DTV_RF_TOP_PROP_DTV_RF_TOP_M11DB    43

#endif /* Si2147_DTV_RF_TOP_PROP */

/* Si2147 DTV_RSQ_RSSI_THRESHOLD property definition */
#define   Si2147_DTV_RSQ_RSSI_THRESHOLD_PROP 0x0704

#ifdef    Si2147_DTV_RSQ_RSSI_THRESHOLD_PROP
  #define Si2147_DTV_RSQ_RSSI_THRESHOLD_PROP_CODE 0x000704


    typedef struct { /* Si2147_DTV_RSQ_RSSI_THRESHOLD_PROP_struct */
               char   hi;
               char   lo;
   } Si2147_DTV_RSQ_RSSI_THRESHOLD_PROP_struct;

   /* DTV_RSQ_RSSI_THRESHOLD property, HI field definition (NO TITLE)*/
   #define  Si2147_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB         8
   #define  Si2147_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK        0xff
   #define  Si2147_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_DEFAULT    0
    #define Si2147_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_HI_MIN  -128
    #define Si2147_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_HI_MAX  127

   /* DTV_RSQ_RSSI_THRESHOLD property, LO field definition (NO TITLE)*/
   #define  Si2147_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB         0
   #define  Si2147_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK        0xff
   #define  Si2147_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_DEFAULT    -80
    #define Si2147_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_LO_MIN  -128
    #define Si2147_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_LO_MAX  127

#endif /* Si2147_DTV_RSQ_RSSI_THRESHOLD_PROP */

/* Si2147 DTV_WB_AGC_SPEED property definition */
#define   Si2147_DTV_WB_AGC_SPEED_PROP 0x0717

#ifdef    Si2147_DTV_WB_AGC_SPEED_PROP
  #define Si2147_DTV_WB_AGC_SPEED_PROP_CODE 0x000717


    typedef struct { /* Si2147_DTV_WB_AGC_SPEED_PROP_struct */
      unsigned char   attack;
      unsigned char   decay;
   } Si2147_DTV_WB_AGC_SPEED_PROP_struct;

   /* DTV_WB_AGC_SPEED property, ATTACK field definition (NO TITLE)*/
   #define  Si2147_DTV_WB_AGC_SPEED_PROP_ATTACK_LSB         0
   #define  Si2147_DTV_WB_AGC_SPEED_PROP_ATTACK_MASK        0xff
   #define  Si2147_DTV_WB_AGC_SPEED_PROP_ATTACK_DEFAULT    0
    #define Si2147_DTV_WB_AGC_SPEED_PROP_ATTACK_AUTO  0

    #define Si2147_DTV_WB_AGC_SPEED_PROP_ATTACK_ATTACK_MIN  0
    #define Si2147_DTV_WB_AGC_SPEED_PROP_ATTACK_ATTACK_MAX  231

   /* DTV_WB_AGC_SPEED property, DECAY field definition (NO TITLE)*/
   #define  Si2147_DTV_WB_AGC_SPEED_PROP_DECAY_LSB         8
   #define  Si2147_DTV_WB_AGC_SPEED_PROP_DECAY_MASK        0xff
   #define  Si2147_DTV_WB_AGC_SPEED_PROP_DECAY_DEFAULT    0
    #define Si2147_DTV_WB_AGC_SPEED_PROP_DECAY_AUTO  0

    #define Si2147_DTV_WB_AGC_SPEED_PROP_DECAY_DECAY_MIN  0
    #define Si2147_DTV_WB_AGC_SPEED_PROP_DECAY_DECAY_MAX  231

#endif /* Si2147_DTV_WB_AGC_SPEED_PROP */

/* Si2147 DTV_ZIF_DC_CANCELLER_BW property definition */
#define   Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP 0x0712

#ifdef    Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP
  #define Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_CODE 0x000712


    typedef struct { /* Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_struct */
      unsigned char   bandwidth;
   } Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_struct;

   /* DTV_ZIF_DC_CANCELLER_BW property, BANDWIDTH field definition (NO TITLE)*/
   #define  Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_LSB         0
   #define  Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_MASK        0xff
   #define  Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_DEFAULT    16
    #define Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_4_HZ       0
    #define Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_8_HZ       1
    #define Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_15_HZ      2
    #define Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_30_HZ      3
    #define Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_61_HZ      4
    #define Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_121_HZ     5
    #define Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_243_HZ     6
    #define Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_486_HZ     7
    #define Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_972_HZ     8
    #define Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_1943_HZ    9
    #define Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_3888_HZ    10
    #define Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_7779_HZ    11
    #define Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_15573_HZ   12
    #define Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_31207_HZ   13
    #define Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_62658_HZ   14
    #define Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_126303_HZ  15
    #define Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_DEFAULT    16

#endif /* Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP */

/* Si2147 MASTER_IEN property definition */
#define   Si2147_MASTER_IEN_PROP 0x0401

#ifdef    Si2147_MASTER_IEN_PROP
  #define Si2147_MASTER_IEN_PROP_CODE 0x000401


    typedef struct { /* Si2147_MASTER_IEN_PROP_struct */
      unsigned char   atvien;
      unsigned char   ctsien;
      unsigned char   dtvien;
      unsigned char   errien;
      unsigned char   tunien;
   } Si2147_MASTER_IEN_PROP_struct;

   /* MASTER_IEN property, ATVIEN field definition (NO TITLE)*/
   #define  Si2147_MASTER_IEN_PROP_ATVIEN_LSB         1
   #define  Si2147_MASTER_IEN_PROP_ATVIEN_MASK        0x01
   #define  Si2147_MASTER_IEN_PROP_ATVIEN_DEFAULT    0
    #define Si2147_MASTER_IEN_PROP_ATVIEN_OFF  0
    #define Si2147_MASTER_IEN_PROP_ATVIEN_ON   1

   /* MASTER_IEN property, CTSIEN field definition (NO TITLE)*/
   #define  Si2147_MASTER_IEN_PROP_CTSIEN_LSB         7
   #define  Si2147_MASTER_IEN_PROP_CTSIEN_MASK        0x01
   #define  Si2147_MASTER_IEN_PROP_CTSIEN_DEFAULT    0
    #define Si2147_MASTER_IEN_PROP_CTSIEN_OFF  0
    #define Si2147_MASTER_IEN_PROP_CTSIEN_ON   1

   /* MASTER_IEN property, DTVIEN field definition (NO TITLE)*/
   #define  Si2147_MASTER_IEN_PROP_DTVIEN_LSB         2
   #define  Si2147_MASTER_IEN_PROP_DTVIEN_MASK        0x01
   #define  Si2147_MASTER_IEN_PROP_DTVIEN_DEFAULT    0
    #define Si2147_MASTER_IEN_PROP_DTVIEN_OFF  0
    #define Si2147_MASTER_IEN_PROP_DTVIEN_ON   1

   /* MASTER_IEN property, ERRIEN field definition (NO TITLE)*/
   #define  Si2147_MASTER_IEN_PROP_ERRIEN_LSB         6
   #define  Si2147_MASTER_IEN_PROP_ERRIEN_MASK        0x01
   #define  Si2147_MASTER_IEN_PROP_ERRIEN_DEFAULT    0
    #define Si2147_MASTER_IEN_PROP_ERRIEN_OFF  0
    #define Si2147_MASTER_IEN_PROP_ERRIEN_ON   1

   /* MASTER_IEN property, TUNIEN field definition (NO TITLE)*/
   #define  Si2147_MASTER_IEN_PROP_TUNIEN_LSB         0
   #define  Si2147_MASTER_IEN_PROP_TUNIEN_MASK        0x01
   #define  Si2147_MASTER_IEN_PROP_TUNIEN_DEFAULT    0
    #define Si2147_MASTER_IEN_PROP_TUNIEN_OFF  0
    #define Si2147_MASTER_IEN_PROP_TUNIEN_ON   1

#endif /* Si2147_MASTER_IEN_PROP */

/* Si2147 TUNER_BLOCKED_VCO property definition */
#define   Si2147_TUNER_BLOCKED_VCO_PROP 0x0504

#ifdef    Si2147_TUNER_BLOCKED_VCO_PROP
  #define Si2147_TUNER_BLOCKED_VCO_PROP_CODE 0x000504


    typedef struct { /* Si2147_TUNER_BLOCKED_VCO_PROP_struct */
               int    vco_code;
   } Si2147_TUNER_BLOCKED_VCO_PROP_struct;

   /* TUNER_BLOCKED_VCO property, VCO_CODE field definition (NO TITLE)*/
   #define  Si2147_TUNER_BLOCKED_VCO_PROP_VCO_CODE_LSB         0
   #define  Si2147_TUNER_BLOCKED_VCO_PROP_VCO_CODE_MASK        0xffff
   #define  Si2147_TUNER_BLOCKED_VCO_PROP_VCO_CODE_DEFAULT    0x8000
    #define Si2147_TUNER_BLOCKED_VCO_PROP_VCO_CODE_VCO_CODE_MIN  -32768
    #define Si2147_TUNER_BLOCKED_VCO_PROP_VCO_CODE_VCO_CODE_MAX  32767

#endif /* Si2147_TUNER_BLOCKED_VCO_PROP */

/* Si2147 TUNER_IEN property definition */
#define   Si2147_TUNER_IEN_PROP 0x0501

#ifdef    Si2147_TUNER_IEN_PROP
  #define Si2147_TUNER_IEN_PROP_CODE 0x000501


    typedef struct { /* Si2147_TUNER_IEN_PROP_struct */
      unsigned char   rssihien;
      unsigned char   rssilien;
      unsigned char   tcien;
   } Si2147_TUNER_IEN_PROP_struct;

   /* TUNER_IEN property, RSSIHIEN field definition (NO TITLE)*/
   #define  Si2147_TUNER_IEN_PROP_RSSIHIEN_LSB         2
   #define  Si2147_TUNER_IEN_PROP_RSSIHIEN_MASK        0x01
   #define  Si2147_TUNER_IEN_PROP_RSSIHIEN_DEFAULT    0
    #define Si2147_TUNER_IEN_PROP_RSSIHIEN_DISABLE  0
    #define Si2147_TUNER_IEN_PROP_RSSIHIEN_ENABLE   1

   /* TUNER_IEN property, RSSILIEN field definition (NO TITLE)*/
   #define  Si2147_TUNER_IEN_PROP_RSSILIEN_LSB         1
   #define  Si2147_TUNER_IEN_PROP_RSSILIEN_MASK        0x01
   #define  Si2147_TUNER_IEN_PROP_RSSILIEN_DEFAULT    0
    #define Si2147_TUNER_IEN_PROP_RSSILIEN_DISABLE  0
    #define Si2147_TUNER_IEN_PROP_RSSILIEN_ENABLE   1

   /* TUNER_IEN property, TCIEN field definition (NO TITLE)*/
   #define  Si2147_TUNER_IEN_PROP_TCIEN_LSB         0
   #define  Si2147_TUNER_IEN_PROP_TCIEN_MASK        0x01
   #define  Si2147_TUNER_IEN_PROP_TCIEN_DEFAULT    1
    #define Si2147_TUNER_IEN_PROP_TCIEN_DISABLE  0
    #define Si2147_TUNER_IEN_PROP_TCIEN_ENABLE   1

#endif /* Si2147_TUNER_IEN_PROP */

/* Si2147 TUNER_INT_SENSE property definition */
#define   Si2147_TUNER_INT_SENSE_PROP 0x0505

#ifdef    Si2147_TUNER_INT_SENSE_PROP
  #define Si2147_TUNER_INT_SENSE_PROP_CODE 0x000505


    typedef struct { /* Si2147_TUNER_INT_SENSE_PROP_struct */
      unsigned char   rssihnegen;
      unsigned char   rssihposen;
      unsigned char   rssilnegen;
      unsigned char   rssilposen;
      unsigned char   tcnegen;
      unsigned char   tcposen;
   } Si2147_TUNER_INT_SENSE_PROP_struct;

   /* TUNER_INT_SENSE property, RSSIHNEGEN field definition (NO TITLE)*/
   #define  Si2147_TUNER_INT_SENSE_PROP_RSSIHNEGEN_LSB         2
   #define  Si2147_TUNER_INT_SENSE_PROP_RSSIHNEGEN_MASK        0x01
   #define  Si2147_TUNER_INT_SENSE_PROP_RSSIHNEGEN_DEFAULT    0
    #define Si2147_TUNER_INT_SENSE_PROP_RSSIHNEGEN_DISABLE  0
    #define Si2147_TUNER_INT_SENSE_PROP_RSSIHNEGEN_ENABLE   1

   /* TUNER_INT_SENSE property, RSSIHPOSEN field definition (NO TITLE)*/
   #define  Si2147_TUNER_INT_SENSE_PROP_RSSIHPOSEN_LSB         10
   #define  Si2147_TUNER_INT_SENSE_PROP_RSSIHPOSEN_MASK        0x01
   #define  Si2147_TUNER_INT_SENSE_PROP_RSSIHPOSEN_DEFAULT    1
    #define Si2147_TUNER_INT_SENSE_PROP_RSSIHPOSEN_DISABLE  0
    #define Si2147_TUNER_INT_SENSE_PROP_RSSIHPOSEN_ENABLE   1

   /* TUNER_INT_SENSE property, RSSILNEGEN field definition (NO TITLE)*/
   #define  Si2147_TUNER_INT_SENSE_PROP_RSSILNEGEN_LSB         1
   #define  Si2147_TUNER_INT_SENSE_PROP_RSSILNEGEN_MASK        0x01
   #define  Si2147_TUNER_INT_SENSE_PROP_RSSILNEGEN_DEFAULT    0
    #define Si2147_TUNER_INT_SENSE_PROP_RSSILNEGEN_DISABLE  0
    #define Si2147_TUNER_INT_SENSE_PROP_RSSILNEGEN_ENABLE   1

   /* TUNER_INT_SENSE property, RSSILPOSEN field definition (NO TITLE)*/
   #define  Si2147_TUNER_INT_SENSE_PROP_RSSILPOSEN_LSB         9
   #define  Si2147_TUNER_INT_SENSE_PROP_RSSILPOSEN_MASK        0x01
   #define  Si2147_TUNER_INT_SENSE_PROP_RSSILPOSEN_DEFAULT    1
    #define Si2147_TUNER_INT_SENSE_PROP_RSSILPOSEN_DISABLE  0
    #define Si2147_TUNER_INT_SENSE_PROP_RSSILPOSEN_ENABLE   1

   /* TUNER_INT_SENSE property, TCNEGEN field definition (NO TITLE)*/
   #define  Si2147_TUNER_INT_SENSE_PROP_TCNEGEN_LSB         0
   #define  Si2147_TUNER_INT_SENSE_PROP_TCNEGEN_MASK        0x01
   #define  Si2147_TUNER_INT_SENSE_PROP_TCNEGEN_DEFAULT    0
    #define Si2147_TUNER_INT_SENSE_PROP_TCNEGEN_DISABLE  0
    #define Si2147_TUNER_INT_SENSE_PROP_TCNEGEN_ENABLE   1

   /* TUNER_INT_SENSE property, TCPOSEN field definition (NO TITLE)*/
   #define  Si2147_TUNER_INT_SENSE_PROP_TCPOSEN_LSB         8
   #define  Si2147_TUNER_INT_SENSE_PROP_TCPOSEN_MASK        0x01
   #define  Si2147_TUNER_INT_SENSE_PROP_TCPOSEN_DEFAULT    1
    #define Si2147_TUNER_INT_SENSE_PROP_TCPOSEN_DISABLE  0
    #define Si2147_TUNER_INT_SENSE_PROP_TCPOSEN_ENABLE   1

#endif /* Si2147_TUNER_INT_SENSE_PROP */

/* Si2147 TUNER_LO_INJECTION property definition */
#define   Si2147_TUNER_LO_INJECTION_PROP 0x0506

#ifdef    Si2147_TUNER_LO_INJECTION_PROP
  #define Si2147_TUNER_LO_INJECTION_PROP_CODE 0x000506


    typedef struct { /* Si2147_TUNER_LO_INJECTION_PROP_struct */
      unsigned char   band_1;
      unsigned char   band_2;
      unsigned char   band_3;
   } Si2147_TUNER_LO_INJECTION_PROP_struct;

   /* TUNER_LO_INJECTION property, BAND_1 field definition (NO TITLE)*/
   #define  Si2147_TUNER_LO_INJECTION_PROP_BAND_1_LSB         0
   #define  Si2147_TUNER_LO_INJECTION_PROP_BAND_1_MASK        0x01
   #define  Si2147_TUNER_LO_INJECTION_PROP_BAND_1_DEFAULT    1
    #define Si2147_TUNER_LO_INJECTION_PROP_BAND_1_LOW_SIDE   0
    #define Si2147_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE  1

   /* TUNER_LO_INJECTION property, BAND_2 field definition (NO TITLE)*/
   #define  Si2147_TUNER_LO_INJECTION_PROP_BAND_2_LSB         1
   #define  Si2147_TUNER_LO_INJECTION_PROP_BAND_2_MASK        0x01
   #define  Si2147_TUNER_LO_INJECTION_PROP_BAND_2_DEFAULT    0
    #define Si2147_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE   0
    #define Si2147_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE  1

   /* TUNER_LO_INJECTION property, BAND_3 field definition (NO TITLE)*/
   #define  Si2147_TUNER_LO_INJECTION_PROP_BAND_3_LSB         2
   #define  Si2147_TUNER_LO_INJECTION_PROP_BAND_3_MASK        0x01
   #define  Si2147_TUNER_LO_INJECTION_PROP_BAND_3_DEFAULT    0
    #define Si2147_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE   0
    #define Si2147_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE  1

#endif /* Si2147_TUNER_LO_INJECTION_PROP */

/* Si2147 TUNER_RETURN_LOSS property definition */
#define   Si2147_TUNER_RETURN_LOSS_PROP 0x0507

#ifdef    Si2147_TUNER_RETURN_LOSS_PROP
  #define Si2147_TUNER_RETURN_LOSS_PROP_CODE 0x000507


    typedef struct { /* Si2147_TUNER_RETURN_LOSS_PROP_struct */
      unsigned char   config;
      unsigned char   mode;
   } Si2147_TUNER_RETURN_LOSS_PROP_struct;

   /* TUNER_RETURN_LOSS property, CONFIG field definition (NO TITLE)*/
   #define  Si2147_TUNER_RETURN_LOSS_PROP_CONFIG_LSB         0
   #define  Si2147_TUNER_RETURN_LOSS_PROP_CONFIG_MASK        0xff
   #define  Si2147_TUNER_RETURN_LOSS_PROP_CONFIG_DEFAULT    127
    #define Si2147_TUNER_RETURN_LOSS_PROP_CONFIG_75   75
    #define Si2147_TUNER_RETURN_LOSS_PROP_CONFIG_83   83
    #define Si2147_TUNER_RETURN_LOSS_PROP_CONFIG_91   91
    #define Si2147_TUNER_RETURN_LOSS_PROP_CONFIG_103  103
    #define Si2147_TUNER_RETURN_LOSS_PROP_CONFIG_115  115
    #define Si2147_TUNER_RETURN_LOSS_PROP_CONFIG_127  127

   /* TUNER_RETURN_LOSS property, MODE field definition (NO TITLE)*/
   #define  Si2147_TUNER_RETURN_LOSS_PROP_MODE_LSB         8
   #define  Si2147_TUNER_RETURN_LOSS_PROP_MODE_MASK        0xff
   #define  Si2147_TUNER_RETURN_LOSS_PROP_MODE_DEFAULT    0
    #define Si2147_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL  0
    #define Si2147_TUNER_RETURN_LOSS_PROP_MODE_CABLE        1

#endif /* Si2147_TUNER_RETURN_LOSS_PROP */

/* Si2147 XOUT property definition */
#define   Si2147_XOUT_PROP 0x0404

#ifdef    Si2147_XOUT_PROP
  #define Si2147_XOUT_PROP_CODE 0x000404


    typedef struct { /* Si2147_XOUT_PROP_struct */
      unsigned char   amp;
   } Si2147_XOUT_PROP_struct;

   /* XOUT property, AMP field definition (NO TITLE)*/
   #define  Si2147_XOUT_PROP_AMP_LSB         0
   #define  Si2147_XOUT_PROP_AMP_MASK        0x01
   #define  Si2147_XOUT_PROP_AMP_DEFAULT    0
    #define Si2147_XOUT_PROP_AMP_HIGH  0
    #define Si2147_XOUT_PROP_AMP_LOW   1

#endif /* Si2147_XOUT_PROP */



  /* --------------------------------------------*/
  /* PROPERTIES STRUCT                           */
  /* This stores all property fields             */
  /* --------------------------------------------*/
  typedef struct {
    #ifdef    Si2147_CRYSTAL_TRIM_PROP
              Si2147_CRYSTAL_TRIM_PROP_struct                  crystal_trim;
    #endif /* Si2147_CRYSTAL_TRIM_PROP */
    #ifdef    Si2147_DTV_AGC_AUTO_FREEZE_PROP
              Si2147_DTV_AGC_AUTO_FREEZE_PROP_struct           dtv_agc_auto_freeze;
    #endif /* Si2147_DTV_AGC_AUTO_FREEZE_PROP */
    #ifdef    Si2147_DTV_AGC_FREEZE_INPUT_PROP
              Si2147_DTV_AGC_FREEZE_INPUT_PROP_struct          dtv_agc_freeze_input;
    #endif /* Si2147_DTV_AGC_FREEZE_INPUT_PROP */
    #ifdef    Si2147_DTV_AGC_SPEED_PROP
              Si2147_DTV_AGC_SPEED_PROP_struct                 dtv_agc_speed;
    #endif /* Si2147_DTV_AGC_SPEED_PROP */
    #ifdef    Si2147_DTV_CONFIG_IF_PORT_PROP
              Si2147_DTV_CONFIG_IF_PORT_PROP_struct            dtv_config_if_port;
    #endif /* Si2147_DTV_CONFIG_IF_PORT_PROP */
    #ifdef    Si2147_DTV_EXT_AGC_PROP
              Si2147_DTV_EXT_AGC_PROP_struct                   dtv_ext_agc;
    #endif /* Si2147_DTV_EXT_AGC_PROP */
    #ifdef    Si2147_DTV_IEN_PROP
              Si2147_DTV_IEN_PROP_struct                       dtv_ien;
    #endif /* Si2147_DTV_IEN_PROP */
    #ifdef    Si2147_DTV_IF_AGC_SPEED_PROP
              Si2147_DTV_IF_AGC_SPEED_PROP_struct              dtv_if_agc_speed;
    #endif /* Si2147_DTV_IF_AGC_SPEED_PROP */
    #ifdef    Si2147_DTV_INITIAL_AGC_SPEED_PROP
              Si2147_DTV_INITIAL_AGC_SPEED_PROP_struct         dtv_initial_agc_speed;
    #endif /* Si2147_DTV_INITIAL_AGC_SPEED_PROP */
    #ifdef    Si2147_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
              Si2147_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_struct  dtv_initial_agc_speed_period;
    #endif /* Si2147_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
    #ifdef    Si2147_DTV_INTERNAL_ZIF_PROP
              Si2147_DTV_INTERNAL_ZIF_PROP_struct              dtv_internal_zif;
    #endif /* Si2147_DTV_INTERNAL_ZIF_PROP */
    #ifdef    Si2147_DTV_INT_SENSE_PROP
              Si2147_DTV_INT_SENSE_PROP_struct                 dtv_int_sense;
    #endif /* Si2147_DTV_INT_SENSE_PROP */
    #ifdef    Si2147_DTV_LIF_FREQ_PROP
              Si2147_DTV_LIF_FREQ_PROP_struct                  dtv_lif_freq;
    #endif /* Si2147_DTV_LIF_FREQ_PROP */
    #ifdef    Si2147_DTV_LIF_OUT_PROP
              Si2147_DTV_LIF_OUT_PROP_struct                   dtv_lif_out;
    #endif /* Si2147_DTV_LIF_OUT_PROP */
    #ifdef    Si2147_DTV_MODE_PROP
              Si2147_DTV_MODE_PROP_struct                      dtv_mode;
    #endif /* Si2147_DTV_MODE_PROP */
    #ifdef    Si2147_DTV_PGA_LIMITS_PROP
              Si2147_DTV_PGA_LIMITS_PROP_struct                dtv_pga_limits;
    #endif /* Si2147_DTV_PGA_LIMITS_PROP */
    #ifdef    Si2147_DTV_PGA_TARGET_PROP
              Si2147_DTV_PGA_TARGET_PROP_struct                dtv_pga_target;
    #endif /* Si2147_DTV_PGA_TARGET_PROP */
    #ifdef    Si2147_DTV_RF_AGC_SPEED_PROP
              Si2147_DTV_RF_AGC_SPEED_PROP_struct              dtv_rf_agc_speed;
    #endif /* Si2147_DTV_RF_AGC_SPEED_PROP */
    #ifdef    Si2147_DTV_RF_TOP_PROP
              Si2147_DTV_RF_TOP_PROP_struct                    dtv_rf_top;
    #endif /* Si2147_DTV_RF_TOP_PROP */
    #ifdef    Si2147_DTV_RSQ_RSSI_THRESHOLD_PROP
              Si2147_DTV_RSQ_RSSI_THRESHOLD_PROP_struct        dtv_rsq_rssi_threshold;
    #endif /* Si2147_DTV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef    Si2147_DTV_WB_AGC_SPEED_PROP
              Si2147_DTV_WB_AGC_SPEED_PROP_struct              dtv_wb_agc_speed;
    #endif /* Si2147_DTV_WB_AGC_SPEED_PROP */
    #ifdef    Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP
              Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP_struct       dtv_zif_dc_canceller_bw;
    #endif /* Si2147_DTV_ZIF_DC_CANCELLER_BW_PROP */
    #ifdef    Si2147_MASTER_IEN_PROP
              Si2147_MASTER_IEN_PROP_struct                    master_ien;
    #endif /* Si2147_MASTER_IEN_PROP */
    #ifdef    Si2147_TUNER_BLOCKED_VCO_PROP
              Si2147_TUNER_BLOCKED_VCO_PROP_struct             tuner_blocked_vco;
    #endif /* Si2147_TUNER_BLOCKED_VCO_PROP */
    #ifdef    Si2147_TUNER_IEN_PROP
              Si2147_TUNER_IEN_PROP_struct                     tuner_ien;
    #endif /* Si2147_TUNER_IEN_PROP */
    #ifdef    Si2147_TUNER_INT_SENSE_PROP
              Si2147_TUNER_INT_SENSE_PROP_struct               tuner_int_sense;
    #endif /* Si2147_TUNER_INT_SENSE_PROP */
    #ifdef    Si2147_TUNER_LO_INJECTION_PROP
              Si2147_TUNER_LO_INJECTION_PROP_struct            tuner_lo_injection;
    #endif /* Si2147_TUNER_LO_INJECTION_PROP */
    #ifdef    Si2147_TUNER_RETURN_LOSS_PROP
              Si2147_TUNER_RETURN_LOSS_PROP_struct             tuner_return_loss;
    #endif /* Si2147_TUNER_RETURN_LOSS_PROP */
    #ifdef    Si2147_XOUT_PROP
              Si2147_XOUT_PROP_struct                          xout;
    #endif /* Si2147_XOUT_PROP */
  } Si2147_PropObj;

/* #define   Si2147_GET_PROPERTY_STRING */

#endif /* _Si2147_PROPERTIES_H_ */







