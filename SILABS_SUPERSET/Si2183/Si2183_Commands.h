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
                  Silicon Laboratories Broadcast Si2183 Layer 1 API


   API commands structures and functions definitions
   FILE: Si2183_Commands.h
   Supported IC : Si2183
   Compiled for ROM 2 firmware 5_B_build_1
   Revision: V0.3.5.1
   Date: November 06 2015
**************************************************************************************/
/* Change log:

 As from V0.3.0.0:
  <improvement>[minor/unused] now using
    #define  Si2183_DD_TS_PINS_CMD_MASTER_FREQ_MAX         4294967295
    This is only changed by principle, since it's not used anymore (was -1 before)

 As from V0.2.8.0:
  <new_feature>[DVB_T2/stream_type] Adding stream_type in Si2183_DVBT2_STATUS_CMD_REPLY_struct
  <new_feature>[DVB_S2/stream_type] Adding stream_type in Si2183_DVBS2_STATUS_CMD_REPLY_struct

 As from V0.2.1.0:
  <new_feature>[DUALS/Channel_Bonding] Upgrading Si2183_DD_TS_PINS_CMD to allow channel bonding
  <compatibility>{Tizen] In Si2183_DD_SSI_SQI_CMD_struct: adding 'signed' in tuner_rssi definition

 As from V0.1.4.0:
  <new_feature>[DVB-S2X/Gold_Sequences] Adding Si2183_L1_DVBS2_PLS_INIT to allow locking on all Gold Sequences in DVB-S2X
    NB: Not compiled by default. Uncomment the '#define   Si2183_DVBS2_PLS_INIT_CMD' line below to activate it.

 As from V0.1.2.0:
  <improvement>[minor/DEMOD_INFO] DEMOD_INFO RESERVED field coded on 8 bits, as in API description
   (no functional impact).
  <new_feature>[ISDB-T/AC_data] Adding Si2183_ISDBT_AC_BITS_CMD function to retrieve ISDB-T AC data.

 As from V0.1.0.0:
  <new_feature>[DVB-T2/FEF] In CONFIG_PINS: allow using GPIOx for FEF freeze
  <new_feature>[DVB-C2/EWBS] In DVBC2_STATUS: adding ewbs field (for emergency warnings)
  <new_feature>[DVB-C/NO_DVB_C] In DVBC_STATUS: adding notdvbc flag
  <new_feature>[DVB-S2/MULTISTREAM] Adding Si2183_DVBS2_STREAM_INFO and Si2183_DVBS2_STREAM_SELECT commands
  <new_feature>[RECEIVER/GET_REV] In Si2183_GET_REV: adding rx flag (to indicate that the part is a receiver)

 As from V0.0.6.0:
  <new_feature> [DD_RESTART] Adding Si2183_DD_RESTART_EXT_CMD
  <new_feature> [DVB-S2/STATUS] Adding fields in DVBS2_STATUS_CMD_REPLY
      unsigned char   roll_off;
      unsigned char   ccm_acm;
      unsigned char   sis_mis;
      unsigned char   num_is;

 As from V0.0.6.0:
  <new_feature> [ISDBT/MODE] Adding dl_a/dl_b/dl_c to Si2183_ISDBT_STATUS_CMD_REPLY_struct

 As from V0.0.0:
  Initial version (based on Si2164 code V0.3.4)
****************************************************************************************/
#ifndef    Si2183_COMMANDS_H
#define    Si2183_COMMANDS_H


/* STATUS structure definition */
  typedef struct { /* Si2183_COMMON_REPLY_struct */
    unsigned char   ddint;
    unsigned char   scanint;
    unsigned char   err;
    unsigned char   cts;
 }  Si2183_COMMON_REPLY_struct;

/* STATUS fields definition */
  /* STATUS, DDINT field definition (address 0, size 1, lsb 0, unsigned)*/
  #define  Si2183_STATUS_DDINT_LSB         0
  #define  Si2183_STATUS_DDINT_MASK        0x01
   #define Si2183_STATUS_DDINT_NOT_TRIGGERED  0
   #define Si2183_STATUS_DDINT_TRIGGERED      1
  /* STATUS, SCANINT field definition (address 0, size 1, lsb 1, unsigned)*/
  #define  Si2183_STATUS_SCANINT_LSB         1
  #define  Si2183_STATUS_SCANINT_MASK        0x01
   #define Si2183_STATUS_SCANINT_NOT_TRIGGERED  0
   #define Si2183_STATUS_SCANINT_TRIGGERED      1
  /* STATUS, ERR field definition (address 0, size 1, lsb 6, unsigned)*/
  #define  Si2183_STATUS_ERR_LSB         6
  #define  Si2183_STATUS_ERR_MASK        0x01
   #define Si2183_STATUS_ERR_ERROR     1
   #define Si2183_STATUS_ERR_NO_ERROR  0
  /* STATUS, CTS field definition (address 0, size 1, lsb 7, unsigned)*/
  #define  Si2183_STATUS_CTS_LSB         7
  #define  Si2183_STATUS_CTS_MASK        0x01
   #define Si2183_STATUS_CTS_COMPLETED  1
   #define Si2183_STATUS_CTS_WAIT       0


/* Si2183_CONFIG_CLKIO command definition */
#define   Si2183_CONFIG_CLKIO_CMD 0x18

#ifdef    Si2183_CONFIG_CLKIO_CMD
  #define Si2183_CONFIG_CLKIO_CMD_CODE 0x010018

    typedef struct { /* Si2183_CONFIG_CLKIO_CMD_struct */
     unsigned char   output;
     unsigned char   pre_driver_str;
     unsigned char   driver_str;
   } Si2183_CONFIG_CLKIO_CMD_struct;


    typedef struct { /* Si2183_CONFIG_CLKIO_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   mode;
      unsigned char   pre_driver_str;
      unsigned char   driver_str;
   }  Si2183_CONFIG_CLKIO_CMD_REPLY_struct;

   /* CONFIG_CLKIO command, OUTPUT field definition (address 1,size 2, lsb 0, unsigned) */
   #define  Si2183_CONFIG_CLKIO_CMD_OUTPUT_LSB         0
   #define  Si2183_CONFIG_CLKIO_CMD_OUTPUT_MASK        0x03
   #define  Si2183_CONFIG_CLKIO_CMD_OUTPUT_MIN         0
   #define  Si2183_CONFIG_CLKIO_CMD_OUTPUT_MAX         2
    #define Si2183_CONFIG_CLKIO_CMD_OUTPUT_NO_CHANGE  0
    #define Si2183_CONFIG_CLKIO_CMD_OUTPUT_OFF        2
    #define Si2183_CONFIG_CLKIO_CMD_OUTPUT_ON         1
   /* CONFIG_CLKIO command, PRE_DRIVER_STR field definition (address 1,size 2, lsb 2, unsigned) */
   #define  Si2183_CONFIG_CLKIO_CMD_PRE_DRIVER_STR_LSB         2
   #define  Si2183_CONFIG_CLKIO_CMD_PRE_DRIVER_STR_MASK        0x03
   #define  Si2183_CONFIG_CLKIO_CMD_PRE_DRIVER_STR_MIN         0
   #define  Si2183_CONFIG_CLKIO_CMD_PRE_DRIVER_STR_MAX         3
    #define Si2183_CONFIG_CLKIO_CMD_PRE_DRIVER_STR_PRE_DRIVER_MIN  0
    #define Si2183_CONFIG_CLKIO_CMD_PRE_DRIVER_STR_PRE_DRIVER_MAX  3
   /* CONFIG_CLKIO command, DRIVER_STR field definition (address 1,size 4, lsb 4, unsigned) */
   #define  Si2183_CONFIG_CLKIO_CMD_DRIVER_STR_LSB         4
   #define  Si2183_CONFIG_CLKIO_CMD_DRIVER_STR_MASK        0x0f
   #define  Si2183_CONFIG_CLKIO_CMD_DRIVER_STR_MIN         0
   #define  Si2183_CONFIG_CLKIO_CMD_DRIVER_STR_MAX         15
    #define Si2183_CONFIG_CLKIO_CMD_DRIVER_STR_DRIVER_MIN  0
    #define Si2183_CONFIG_CLKIO_CMD_DRIVER_STR_DRIVER_MAX  15
   /* CONFIG_CLKIO command, MODE field definition (address 1, size 2, lsb 0, unsigned)*/
   #define  Si2183_CONFIG_CLKIO_RESPONSE_MODE_LSB         0
   #define  Si2183_CONFIG_CLKIO_RESPONSE_MODE_MASK        0x03
    #define Si2183_CONFIG_CLKIO_RESPONSE_MODE_CLK_INPUT   2
    #define Si2183_CONFIG_CLKIO_RESPONSE_MODE_CLK_OUTPUT  1
    #define Si2183_CONFIG_CLKIO_RESPONSE_MODE_UNUSED      0
   /* CONFIG_CLKIO command, PRE_DRIVER_STR field definition (address 2, size 8, lsb 0, unsigned)*/
   #define  Si2183_CONFIG_CLKIO_RESPONSE_PRE_DRIVER_STR_LSB         0
   #define  Si2183_CONFIG_CLKIO_RESPONSE_PRE_DRIVER_STR_MASK        0xff
   /* CONFIG_CLKIO command, DRIVER_STR field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si2183_CONFIG_CLKIO_RESPONSE_DRIVER_STR_LSB         0
   #define  Si2183_CONFIG_CLKIO_RESPONSE_DRIVER_STR_MASK        0xff

#endif /* Si2183_CONFIG_CLKIO_CMD */

/* Si2183_CONFIG_I2C command definition */
#define   Si2183_CONFIG_I2C_CMD 0xc0

#ifdef    Si2183_CONFIG_I2C_CMD
  #define Si2183_CONFIG_I2C_CMD_CODE 0x0100c0

    typedef struct { /* Si2183_CONFIG_I2C_CMD_struct */
     unsigned char   subcode;
     unsigned char   i2c_broadcast;
   } Si2183_CONFIG_I2C_CMD_struct;


    typedef struct { /* Si2183_CONFIG_I2C_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
   }  Si2183_CONFIG_I2C_CMD_REPLY_struct;

   /* CONFIG_I2C command, SUBCODE field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_CONFIG_I2C_CMD_SUBCODE_LSB         0
   #define  Si2183_CONFIG_I2C_CMD_SUBCODE_MASK        0xff
   #define  Si2183_CONFIG_I2C_CMD_SUBCODE_MIN         15
   #define  Si2183_CONFIG_I2C_CMD_SUBCODE_MAX         15
    #define Si2183_CONFIG_I2C_CMD_SUBCODE_CODE  15
   /* CONFIG_I2C command, I2C_BROADCAST field definition (address 2,size 2, lsb 0, unsigned) */
   #define  Si2183_CONFIG_I2C_CMD_I2C_BROADCAST_LSB         0
   #define  Si2183_CONFIG_I2C_CMD_I2C_BROADCAST_MASK        0x03
   #define  Si2183_CONFIG_I2C_CMD_I2C_BROADCAST_MIN         0
   #define  Si2183_CONFIG_I2C_CMD_I2C_BROADCAST_MAX         1
    #define Si2183_CONFIG_I2C_CMD_I2C_BROADCAST_DISABLED  0
    #define Si2183_CONFIG_I2C_CMD_I2C_BROADCAST_ENABLED   1
#endif /* Si2183_CONFIG_I2C_CMD */

/* Si2183_CONFIG_PINS command definition */
#define   Si2183_CONFIG_PINS_CMD 0x12

#ifdef    Si2183_CONFIG_PINS_CMD
  #define Si2183_CONFIG_PINS_CMD_CODE 0x010012

    typedef struct { /* Si2183_CONFIG_PINS_CMD_struct */
     unsigned char   gpio0_mode;
     unsigned char   gpio0_read;
     unsigned char   gpio1_mode;
     unsigned char   gpio1_read;
   } Si2183_CONFIG_PINS_CMD_struct;


    typedef struct { /* Si2183_CONFIG_PINS_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   gpio0_mode;
      unsigned char   gpio0_state;
      unsigned char   gpio1_mode;
      unsigned char   gpio1_state;
   }  Si2183_CONFIG_PINS_CMD_REPLY_struct;

   /* CONFIG_PINS command, GPIO0_MODE field definition (address 1,size 7, lsb 0, unsigned) */
   #define  Si2183_CONFIG_PINS_CMD_GPIO0_MODE_LSB         0
   #define  Si2183_CONFIG_PINS_CMD_GPIO0_MODE_MASK        0x7f
   #define  Si2183_CONFIG_PINS_CMD_GPIO0_MODE_MIN         0
   #define  Si2183_CONFIG_PINS_CMD_GPIO0_MODE_MAX         8
    #define Si2183_CONFIG_PINS_CMD_GPIO0_MODE_DISABLE    1
    #define Si2183_CONFIG_PINS_CMD_GPIO0_MODE_DRIVE_0    2
    #define Si2183_CONFIG_PINS_CMD_GPIO0_MODE_DRIVE_1    3
    #define Si2183_CONFIG_PINS_CMD_GPIO0_MODE_FEF        5
    #define Si2183_CONFIG_PINS_CMD_GPIO0_MODE_HW_LOCK    8
    #define Si2183_CONFIG_PINS_CMD_GPIO0_MODE_INT_FLAG   7
    #define Si2183_CONFIG_PINS_CMD_GPIO0_MODE_NO_CHANGE  0
    #define Si2183_CONFIG_PINS_CMD_GPIO0_MODE_TS_ERR     4
   /* CONFIG_PINS command, GPIO0_READ field definition (address 1,size 1, lsb 7, unsigned) */
   #define  Si2183_CONFIG_PINS_CMD_GPIO0_READ_LSB         7
   #define  Si2183_CONFIG_PINS_CMD_GPIO0_READ_MASK        0x01
   #define  Si2183_CONFIG_PINS_CMD_GPIO0_READ_MIN         0
   #define  Si2183_CONFIG_PINS_CMD_GPIO0_READ_MAX         1
    #define Si2183_CONFIG_PINS_CMD_GPIO0_READ_DO_NOT_READ  0
    #define Si2183_CONFIG_PINS_CMD_GPIO0_READ_READ         1
   /* CONFIG_PINS command, GPIO1_MODE field definition (address 2,size 7, lsb 0, unsigned) */
   #define  Si2183_CONFIG_PINS_CMD_GPIO1_MODE_LSB         0
   #define  Si2183_CONFIG_PINS_CMD_GPIO1_MODE_MASK        0x7f
   #define  Si2183_CONFIG_PINS_CMD_GPIO1_MODE_MIN         0
   #define  Si2183_CONFIG_PINS_CMD_GPIO1_MODE_MAX         8
    #define Si2183_CONFIG_PINS_CMD_GPIO1_MODE_DISABLE    1
    #define Si2183_CONFIG_PINS_CMD_GPIO1_MODE_DRIVE_0    2
    #define Si2183_CONFIG_PINS_CMD_GPIO1_MODE_DRIVE_1    3
    #define Si2183_CONFIG_PINS_CMD_GPIO1_MODE_FEF        5
    #define Si2183_CONFIG_PINS_CMD_GPIO1_MODE_HW_LOCK    8
    #define Si2183_CONFIG_PINS_CMD_GPIO1_MODE_INT_FLAG   7
    #define Si2183_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE  0
    #define Si2183_CONFIG_PINS_CMD_GPIO1_MODE_TS_ERR     4
   /* CONFIG_PINS command, GPIO1_READ field definition (address 2,size 1, lsb 7, unsigned) */
   #define  Si2183_CONFIG_PINS_CMD_GPIO1_READ_LSB         7
   #define  Si2183_CONFIG_PINS_CMD_GPIO1_READ_MASK        0x01
   #define  Si2183_CONFIG_PINS_CMD_GPIO1_READ_MIN         0
   #define  Si2183_CONFIG_PINS_CMD_GPIO1_READ_MAX         1
    #define Si2183_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ  0
    #define Si2183_CONFIG_PINS_CMD_GPIO1_READ_READ         1
   /* CONFIG_PINS command, GPIO0_MODE field definition (address 1, size 7, lsb 0, unsigned)*/
   #define  Si2183_CONFIG_PINS_RESPONSE_GPIO0_MODE_LSB         0
   #define  Si2183_CONFIG_PINS_RESPONSE_GPIO0_MODE_MASK        0x7f
    #define Si2183_CONFIG_PINS_RESPONSE_GPIO0_MODE_DISABLE   1
    #define Si2183_CONFIG_PINS_RESPONSE_GPIO0_MODE_DRIVE_0   2
    #define Si2183_CONFIG_PINS_RESPONSE_GPIO0_MODE_DRIVE_1   3
    #define Si2183_CONFIG_PINS_RESPONSE_GPIO0_MODE_FEF       5
    #define Si2183_CONFIG_PINS_RESPONSE_GPIO0_MODE_HW_LOCK   8
    #define Si2183_CONFIG_PINS_RESPONSE_GPIO0_MODE_INT_FLAG  7
    #define Si2183_CONFIG_PINS_RESPONSE_GPIO0_MODE_TS_ERR    4
   /* CONFIG_PINS command, GPIO0_STATE field definition (address 1, size 1, lsb 7, unsigned)*/
   #define  Si2183_CONFIG_PINS_RESPONSE_GPIO0_STATE_LSB         7
   #define  Si2183_CONFIG_PINS_RESPONSE_GPIO0_STATE_MASK        0x01
    #define Si2183_CONFIG_PINS_RESPONSE_GPIO0_STATE_READ_0  0
    #define Si2183_CONFIG_PINS_RESPONSE_GPIO0_STATE_READ_1  1
   /* CONFIG_PINS command, GPIO1_MODE field definition (address 2, size 7, lsb 0, unsigned)*/
   #define  Si2183_CONFIG_PINS_RESPONSE_GPIO1_MODE_LSB         0
   #define  Si2183_CONFIG_PINS_RESPONSE_GPIO1_MODE_MASK        0x7f
    #define Si2183_CONFIG_PINS_RESPONSE_GPIO1_MODE_DISABLE   1
    #define Si2183_CONFIG_PINS_RESPONSE_GPIO1_MODE_DRIVE_0   2
    #define Si2183_CONFIG_PINS_RESPONSE_GPIO1_MODE_DRIVE_1   3
    #define Si2183_CONFIG_PINS_RESPONSE_GPIO1_MODE_FEF       5
    #define Si2183_CONFIG_PINS_RESPONSE_GPIO1_MODE_HW_LOCK   8
    #define Si2183_CONFIG_PINS_RESPONSE_GPIO1_MODE_INT_FLAG  7
    #define Si2183_CONFIG_PINS_RESPONSE_GPIO1_MODE_TS_ERR    4
   /* CONFIG_PINS command, GPIO1_STATE field definition (address 2, size 1, lsb 7, unsigned)*/
   #define  Si2183_CONFIG_PINS_RESPONSE_GPIO1_STATE_LSB         7
   #define  Si2183_CONFIG_PINS_RESPONSE_GPIO1_STATE_MASK        0x01
    #define Si2183_CONFIG_PINS_RESPONSE_GPIO1_STATE_READ_0  0
    #define Si2183_CONFIG_PINS_RESPONSE_GPIO1_STATE_READ_1  1

#endif /* Si2183_CONFIG_PINS_CMD */

/* Si2183_DD_BER command definition */
#define   Si2183_DD_BER_CMD 0x82

#ifdef    Si2183_DD_BER_CMD
  #define Si2183_DD_BER_CMD_CODE 0x010082

    typedef struct { /* Si2183_DD_BER_CMD_struct */
     unsigned char   rst;
   } Si2183_DD_BER_CMD_struct;


    typedef struct { /* Si2183_DD_BER_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   exp;
      unsigned char   mant;
   }  Si2183_DD_BER_CMD_REPLY_struct;

   /* DD_BER command, RST field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2183_DD_BER_CMD_RST_LSB         0
   #define  Si2183_DD_BER_CMD_RST_MASK        0x01
   #define  Si2183_DD_BER_CMD_RST_MIN         0
   #define  Si2183_DD_BER_CMD_RST_MAX         1
    #define Si2183_DD_BER_CMD_RST_CLEAR  1
    #define Si2183_DD_BER_CMD_RST_RUN    0
   /* DD_BER command, EXP field definition (address 1, size 4, lsb 0, unsigned)*/
   #define  Si2183_DD_BER_RESPONSE_EXP_LSB         0
   #define  Si2183_DD_BER_RESPONSE_EXP_MASK        0x0f
    #define Si2183_DD_BER_RESPONSE_EXP_EXP_MIN  0
    #define Si2183_DD_BER_RESPONSE_EXP_EXP_MAX  8
   /* DD_BER command, MANT field definition (address 2, size 8, lsb 0, unsigned)*/
   #define  Si2183_DD_BER_RESPONSE_MANT_LSB         0
   #define  Si2183_DD_BER_RESPONSE_MANT_MASK        0xff
    #define Si2183_DD_BER_RESPONSE_MANT_MANT_MIN  0
    #define Si2183_DD_BER_RESPONSE_MANT_MANT_MAX  99

#endif /* Si2183_DD_BER_CMD */

/* Si2183_DD_CBER command definition */
#define   Si2183_DD_CBER_CMD 0x81

#ifdef    Si2183_DD_CBER_CMD
  #define Si2183_DD_CBER_CMD_CODE 0x010081

    typedef struct { /* Si2183_DD_CBER_CMD_struct */
     unsigned char   rst;
   } Si2183_DD_CBER_CMD_struct;


    typedef struct { /* Si2183_DD_CBER_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   exp;
      unsigned char   mant;
   }  Si2183_DD_CBER_CMD_REPLY_struct;

   /* DD_CBER command, RST field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2183_DD_CBER_CMD_RST_LSB         0
   #define  Si2183_DD_CBER_CMD_RST_MASK        0x01
   #define  Si2183_DD_CBER_CMD_RST_MIN         0
   #define  Si2183_DD_CBER_CMD_RST_MAX         1
    #define Si2183_DD_CBER_CMD_RST_CLEAR  1
    #define Si2183_DD_CBER_CMD_RST_RUN    0
   /* DD_CBER command, EXP field definition (address 1, size 4, lsb 0, unsigned)*/
   #define  Si2183_DD_CBER_RESPONSE_EXP_LSB         0
   #define  Si2183_DD_CBER_RESPONSE_EXP_MASK        0x0f
    #define Si2183_DD_CBER_RESPONSE_EXP_EXP_MIN  0
    #define Si2183_DD_CBER_RESPONSE_EXP_EXP_MAX  8
   /* DD_CBER command, MANT field definition (address 2, size 8, lsb 0, unsigned)*/
   #define  Si2183_DD_CBER_RESPONSE_MANT_LSB         0
   #define  Si2183_DD_CBER_RESPONSE_MANT_MASK        0xff
    #define Si2183_DD_CBER_RESPONSE_MANT_MANT_MIN  0
    #define Si2183_DD_CBER_RESPONSE_MANT_MANT_MAX  99

#endif /* Si2183_DD_CBER_CMD */

#ifdef    SATELLITE_FRONT_END
/* Si2183_DD_DISEQC_SEND command definition */
#define   Si2183_DD_DISEQC_SEND_CMD 0x8c

#ifdef    Si2183_DD_DISEQC_SEND_CMD
  #define Si2183_DD_DISEQC_SEND_CMD_CODE 0x01008c

    typedef struct { /* Si2183_DD_DISEQC_SEND_CMD_struct */
     unsigned char   enable;
     unsigned char   cont_tone;
     unsigned char   tone_burst;
     unsigned char   burst_sel;
     unsigned char   end_seq;
     unsigned char   msg_length;
     unsigned char   msg_byte1;
     unsigned char   msg_byte2;
     unsigned char   msg_byte3;
     unsigned char   msg_byte4;
     unsigned char   msg_byte5;
     unsigned char   msg_byte6;
   } Si2183_DD_DISEQC_SEND_CMD_struct;


    typedef struct { /* Si2183_DD_DISEQC_SEND_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
   }  Si2183_DD_DISEQC_SEND_CMD_REPLY_struct;

   /* DD_DISEQC_SEND command, ENABLE field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2183_DD_DISEQC_SEND_CMD_ENABLE_LSB         0
   #define  Si2183_DD_DISEQC_SEND_CMD_ENABLE_MASK        0x01
   #define  Si2183_DD_DISEQC_SEND_CMD_ENABLE_MIN         0
   #define  Si2183_DD_DISEQC_SEND_CMD_ENABLE_MAX         1
    #define Si2183_DD_DISEQC_SEND_CMD_ENABLE_DISABLE  0
    #define Si2183_DD_DISEQC_SEND_CMD_ENABLE_ENABLE   1
   /* DD_DISEQC_SEND command, CONT_TONE field definition (address 1,size 1, lsb 1, unsigned) */
   #define  Si2183_DD_DISEQC_SEND_CMD_CONT_TONE_LSB         1
   #define  Si2183_DD_DISEQC_SEND_CMD_CONT_TONE_MASK        0x01
   #define  Si2183_DD_DISEQC_SEND_CMD_CONT_TONE_MIN         0
   #define  Si2183_DD_DISEQC_SEND_CMD_CONT_TONE_MAX         1
    #define Si2183_DD_DISEQC_SEND_CMD_CONT_TONE_OFF  0
    #define Si2183_DD_DISEQC_SEND_CMD_CONT_TONE_ON   1
   /* DD_DISEQC_SEND command, TONE_BURST field definition (address 1,size 1, lsb 2, unsigned) */
   #define  Si2183_DD_DISEQC_SEND_CMD_TONE_BURST_LSB         2
   #define  Si2183_DD_DISEQC_SEND_CMD_TONE_BURST_MASK        0x01
   #define  Si2183_DD_DISEQC_SEND_CMD_TONE_BURST_MIN         0
   #define  Si2183_DD_DISEQC_SEND_CMD_TONE_BURST_MAX         1
    #define Si2183_DD_DISEQC_SEND_CMD_TONE_BURST_OFF  0
    #define Si2183_DD_DISEQC_SEND_CMD_TONE_BURST_ON   1
   /* DD_DISEQC_SEND command, BURST_SEL field definition (address 1,size 1, lsb 3, unsigned) */
   #define  Si2183_DD_DISEQC_SEND_CMD_BURST_SEL_LSB         3
   #define  Si2183_DD_DISEQC_SEND_CMD_BURST_SEL_MASK        0x01
   #define  Si2183_DD_DISEQC_SEND_CMD_BURST_SEL_MIN         0
   #define  Si2183_DD_DISEQC_SEND_CMD_BURST_SEL_MAX         1
    #define Si2183_DD_DISEQC_SEND_CMD_BURST_SEL_SA  0
    #define Si2183_DD_DISEQC_SEND_CMD_BURST_SEL_SB  1
   /* DD_DISEQC_SEND command, END_SEQ field definition (address 1,size 1, lsb 4, unsigned) */
   #define  Si2183_DD_DISEQC_SEND_CMD_END_SEQ_LSB         4
   #define  Si2183_DD_DISEQC_SEND_CMD_END_SEQ_MASK        0x01
   #define  Si2183_DD_DISEQC_SEND_CMD_END_SEQ_MIN         0
   #define  Si2183_DD_DISEQC_SEND_CMD_END_SEQ_MAX         1
    #define Si2183_DD_DISEQC_SEND_CMD_END_SEQ_END      1
    #define Si2183_DD_DISEQC_SEND_CMD_END_SEQ_NOT_END  0
   /* DD_DISEQC_SEND command, MSG_LENGTH field definition (address 1,size 3, lsb 5, unsigned) */
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_LENGTH_LSB         5
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_LENGTH_MASK        0x07
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_LENGTH_MIN         0
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_LENGTH_MAX         7
   /* DD_DISEQC_SEND command, MSG_BYTE1 field definition (address 2,size 8, lsb 0, unsigned) */
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE1_LSB         0
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE1_MASK        0xff
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE1_MIN         0
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE1_MAX         255
   /* DD_DISEQC_SEND command, MSG_BYTE2 field definition (address 3,size 8, lsb 0, unsigned) */
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE2_LSB         0
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE2_MASK        0xff
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE2_MIN         0
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE2_MAX         255
   /* DD_DISEQC_SEND command, MSG_BYTE3 field definition (address 4,size 8, lsb 0, unsigned) */
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE3_LSB         0
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE3_MASK        0xff
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE3_MIN         0
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE3_MAX         255
   /* DD_DISEQC_SEND command, MSG_BYTE4 field definition (address 5,size 8, lsb 0, unsigned) */
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE4_LSB         0
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE4_MASK        0xff
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE4_MIN         0
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE4_MAX         255
   /* DD_DISEQC_SEND command, MSG_BYTE5 field definition (address 6,size 8, lsb 0, unsigned) */
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE5_LSB         0
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE5_MASK        0xff
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE5_MIN         0
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE5_MAX         255
   /* DD_DISEQC_SEND command, MSG_BYTE6 field definition (address 7,size 8, lsb 0, unsigned) */
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE6_LSB         0
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE6_MASK        0xff
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE6_MIN         0
   #define  Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE6_MAX         255
#endif /* Si2183_DD_DISEQC_SEND_CMD */

/* Si2183_DD_DISEQC_STATUS command definition */
#define   Si2183_DD_DISEQC_STATUS_CMD 0x8d

#ifdef    Si2183_DD_DISEQC_STATUS_CMD
  #define Si2183_DD_DISEQC_STATUS_CMD_CODE 0x01008d

    typedef struct { /* Si2183_DD_DISEQC_STATUS_CMD_struct */
     unsigned char   listen;
   } Si2183_DD_DISEQC_STATUS_CMD_struct;


    typedef struct { /* Si2183_DD_DISEQC_STATUS_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   bus_state;
      unsigned char   reply_status;
      unsigned char   reply_length;
      unsigned char   reply_toggle;
      unsigned char   end_of_reply;
      unsigned char   diseqc_mode;
      unsigned char   reply_byte1;
      unsigned char   reply_byte2;
      unsigned char   reply_byte3;
   }  Si2183_DD_DISEQC_STATUS_CMD_REPLY_struct;

   /* DD_DISEQC_STATUS command, LISTEN field definition (address 1,size 2, lsb 0, unsigned) */
   #define  Si2183_DD_DISEQC_STATUS_CMD_LISTEN_LSB         0
   #define  Si2183_DD_DISEQC_STATUS_CMD_LISTEN_MASK        0x03
   #define  Si2183_DD_DISEQC_STATUS_CMD_LISTEN_MIN         0
   #define  Si2183_DD_DISEQC_STATUS_CMD_LISTEN_MAX         2
    #define Si2183_DD_DISEQC_STATUS_CMD_LISTEN_AUTO       0
    #define Si2183_DD_DISEQC_STATUS_CMD_LISTEN_LISTEN     1
    #define Si2183_DD_DISEQC_STATUS_CMD_LISTEN_NO_CHANGE  2
   /* DD_DISEQC_STATUS command, BUS_STATE field definition (address 1, size 1, lsb 0, unsigned)*/
   #define  Si2183_DD_DISEQC_STATUS_RESPONSE_BUS_STATE_LSB         0
   #define  Si2183_DD_DISEQC_STATUS_RESPONSE_BUS_STATE_MASK        0x01
    #define Si2183_DD_DISEQC_STATUS_RESPONSE_BUS_STATE_BUSY   0
    #define Si2183_DD_DISEQC_STATUS_RESPONSE_BUS_STATE_READY  1
   /* DD_DISEQC_STATUS command, REPLY_STATUS field definition (address 1, size 2, lsb 1, unsigned)*/
   #define  Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_STATUS_LSB         1
   #define  Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_STATUS_MASK        0x03
    #define Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_STATUS_MISSING_BITS  2
    #define Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_STATUS_NO_REPLY      0
    #define Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_STATUS_PARITY_ERROR  1
    #define Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_STATUS_REPLY_OK      3
   /* DD_DISEQC_STATUS command, REPLY_LENGTH field definition (address 1, size 2, lsb 3, unsigned)*/
   #define  Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_LENGTH_LSB         3
   #define  Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_LENGTH_MASK        0x03
   /* DD_DISEQC_STATUS command, REPLY_TOGGLE field definition (address 1, size 1, lsb 5, unsigned)*/
   #define  Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_TOGGLE_LSB         5
   #define  Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_TOGGLE_MASK        0x01
   /* DD_DISEQC_STATUS command, END_OF_REPLY field definition (address 1, size 1, lsb 6, unsigned)*/
   #define  Si2183_DD_DISEQC_STATUS_RESPONSE_END_OF_REPLY_LSB         6
   #define  Si2183_DD_DISEQC_STATUS_RESPONSE_END_OF_REPLY_MASK        0x01
   /* DD_DISEQC_STATUS command, DISEQC_MODE field definition (address 1, size 1, lsb 7, unsigned)*/
   #define  Si2183_DD_DISEQC_STATUS_RESPONSE_DISEQC_MODE_LSB         7
   #define  Si2183_DD_DISEQC_STATUS_RESPONSE_DISEQC_MODE_MASK        0x01
    #define Si2183_DD_DISEQC_STATUS_RESPONSE_DISEQC_MODE_AUTO    0
    #define Si2183_DD_DISEQC_STATUS_RESPONSE_DISEQC_MODE_LISTEN  1
   /* DD_DISEQC_STATUS command, REPLY_BYTE1 field definition (address 2, size 8, lsb 0, unsigned)*/
   #define  Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_BYTE1_LSB         0
   #define  Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_BYTE1_MASK        0xff
   /* DD_DISEQC_STATUS command, REPLY_BYTE2 field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_BYTE2_LSB         0
   #define  Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_BYTE2_MASK        0xff
   /* DD_DISEQC_STATUS command, REPLY_BYTE3 field definition (address 4, size 8, lsb 0, unsigned)*/
   #define  Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_BYTE3_LSB         0
   #define  Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_BYTE3_MASK        0xff

#endif /* Si2183_DD_DISEQC_STATUS_CMD */

/* Si2183_DD_EXT_AGC_SAT command definition */
#define   Si2183_DD_EXT_AGC_SAT_CMD 0x8a

#ifdef    Si2183_DD_EXT_AGC_SAT_CMD
  #define Si2183_DD_EXT_AGC_SAT_CMD_CODE 0x01008a

    typedef struct { /* Si2183_DD_EXT_AGC_SAT_CMD_struct */
     unsigned char   agc_1_mode;
     unsigned char   agc_1_inv;
     unsigned char   agc_2_mode;
     unsigned char   agc_2_inv;
     unsigned char   agc_1_kloop;
     unsigned char   agc_2_kloop;
     unsigned char   agc_1_min;
     unsigned char   agc_2_min;
   } Si2183_DD_EXT_AGC_SAT_CMD_struct;


    typedef struct { /* Si2183_DD_EXT_AGC_SAT_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   agc_1_level;
      unsigned char   agc_2_level;
   }  Si2183_DD_EXT_AGC_SAT_CMD_REPLY_struct;

   /* DD_EXT_AGC_SAT command, AGC_1_MODE field definition (address 1,size 3, lsb 0, unsigned) */
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_LSB         0
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MASK        0x07
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MIN         0
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MAX         5
    #define Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MP_A       2
    #define Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MP_B       3
    #define Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MP_C       4
    #define Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MP_D       5
    #define Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_NOT_USED   1
    #define Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_NO_CHANGE  0
   /* DD_EXT_AGC_SAT command, AGC_1_INV field definition (address 1,size 1, lsb 3, unsigned) */
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_INV_LSB         3
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_INV_MASK        0x01
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_INV_MIN         0
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_INV_MAX         1
    #define Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_INV_INVERTED      1
    #define Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_INV_NOT_INVERTED  0
   /* DD_EXT_AGC_SAT command, AGC_2_MODE field definition (address 1,size 3, lsb 4, unsigned) */
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MODE_LSB         4
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MODE_MASK        0x07
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MODE_MIN         0
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MODE_MAX         5
    #define Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MODE_MP_A       2
    #define Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MODE_MP_B       3
    #define Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MODE_MP_C       4
    #define Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MODE_MP_D       5
    #define Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MODE_NOT_USED   1
    #define Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MODE_NO_CHANGE  0
   /* DD_EXT_AGC_SAT command, AGC_2_INV field definition (address 1,size 1, lsb 7, unsigned) */
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_INV_LSB         7
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_INV_MASK        0x01
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_INV_MIN         0
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_INV_MAX         1
    #define Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_INV_INVERTED      1
    #define Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_INV_NOT_INVERTED  0
   /* DD_EXT_AGC_SAT command, AGC_1_KLOOP field definition (address 2,size 5, lsb 0, unsigned) */
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_KLOOP_LSB         0
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_KLOOP_MASK        0x1f
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_KLOOP_MIN         0
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_KLOOP_MAX         31
   /* DD_EXT_AGC_SAT command, AGC_2_KLOOP field definition (address 3,size 5, lsb 0, unsigned) */
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_KLOOP_LSB         0
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_KLOOP_MASK        0x1f
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_KLOOP_MIN         0
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_KLOOP_MAX         31
   /* DD_EXT_AGC_SAT command, AGC_1_MIN field definition (address 4,size 8, lsb 0, unsigned) */
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MIN_LSB         0
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MIN_MASK        0xff
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MIN_MIN         0
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MIN_MAX         255
   /* DD_EXT_AGC_SAT command, AGC_2_MIN field definition (address 5,size 8, lsb 0, unsigned) */
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MIN_LSB         0
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MIN_MASK        0xff
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MIN_MIN         0
   #define  Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MIN_MAX         255
   /* DD_EXT_AGC_SAT command, AGC_1_LEVEL field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2183_DD_EXT_AGC_SAT_RESPONSE_AGC_1_LEVEL_LSB         0
   #define  Si2183_DD_EXT_AGC_SAT_RESPONSE_AGC_1_LEVEL_MASK        0xff
   /* DD_EXT_AGC_SAT command, AGC_2_LEVEL field definition (address 2, size 8, lsb 0, unsigned)*/
   #define  Si2183_DD_EXT_AGC_SAT_RESPONSE_AGC_2_LEVEL_LSB         0
   #define  Si2183_DD_EXT_AGC_SAT_RESPONSE_AGC_2_LEVEL_MASK        0xff

#endif /* Si2183_DD_EXT_AGC_SAT_CMD */

#endif /* SATELLITE_FRONT_END */

#ifdef    TERRESTRIAL_FRONT_END
/* Si2183_DD_EXT_AGC_TER command definition */
#define   Si2183_DD_EXT_AGC_TER_CMD 0x89

#ifdef    Si2183_DD_EXT_AGC_TER_CMD
  #define Si2183_DD_EXT_AGC_TER_CMD_CODE 0x010089

    typedef struct { /* Si2183_DD_EXT_AGC_TER_CMD_struct */
     unsigned char   agc_1_mode;
     unsigned char   agc_1_inv;
     unsigned char   agc_2_mode;
     unsigned char   agc_2_inv;
     unsigned char   agc_1_kloop;
     unsigned char   agc_2_kloop;
     unsigned char   agc_1_min;
     unsigned char   agc_2_min;
   } Si2183_DD_EXT_AGC_TER_CMD_struct;


    typedef struct { /* Si2183_DD_EXT_AGC_TER_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   agc_1_level;
      unsigned char   agc_2_level;
   }  Si2183_DD_EXT_AGC_TER_CMD_REPLY_struct;

   /* DD_EXT_AGC_TER command, AGC_1_MODE field definition (address 1,size 3, lsb 0, unsigned) */
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MODE_LSB         0
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MODE_MASK        0x07
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MODE_MIN         0
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MODE_MAX         5
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MODE_MP_A       2
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MODE_MP_B       3
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MODE_MP_C       4
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MODE_MP_D       5
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MODE_NOT_USED   1
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MODE_NO_CHANGE  0
   /* DD_EXT_AGC_TER command, AGC_1_INV field definition (address 1,size 1, lsb 3, unsigned) */
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_1_INV_LSB         3
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_1_INV_MASK        0x01
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_1_INV_MIN         0
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_1_INV_MAX         1
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_1_INV_INVERTED      1
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_1_INV_NOT_INVERTED  0
   /* DD_EXT_AGC_TER command, AGC_2_MODE field definition (address 1,size 3, lsb 4, unsigned) */
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_LSB         4
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MASK        0x07
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MIN         0
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MAX         5
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MP_A       2
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MP_B       3
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MP_C       4
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MP_D       5
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_NOT_USED   1
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_NO_CHANGE  0
   /* DD_EXT_AGC_TER command, AGC_2_INV field definition (address 1,size 1, lsb 7, unsigned) */
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_2_INV_LSB         7
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_2_INV_MASK        0x01
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_2_INV_MIN         0
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_2_INV_MAX         1
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_2_INV_INVERTED      1
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_2_INV_NOT_INVERTED  0
   /* DD_EXT_AGC_TER command, AGC_1_KLOOP field definition (address 2,size 5, lsb 0, unsigned) */
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_1_KLOOP_LSB         0
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_1_KLOOP_MASK        0x1f
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_1_KLOOP_MIN         6
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_1_KLOOP_MAX         20
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_1_KLOOP_AGC_1_KLOOP_MIN  6
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_1_KLOOP_AGC_1_KLOOP_MAX  20
   /* DD_EXT_AGC_TER command, AGC_2_KLOOP field definition (address 3,size 5, lsb 0, unsigned) */
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_2_KLOOP_LSB         0
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_2_KLOOP_MASK        0x1f
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_2_KLOOP_MIN         6
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_2_KLOOP_MAX         20
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_2_KLOOP_AGC_2_KLOOP_MIN  6
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_2_KLOOP_AGC_2_KLOOP_MAX  20
   /* DD_EXT_AGC_TER command, AGC_1_MIN field definition (address 4,size 8, lsb 0, unsigned) */
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MIN_LSB         0
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MIN_MASK        0xff
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MIN_MIN         0
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MIN_MAX         255
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MIN_AGC_1_MIN_MIN  0
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MIN_AGC_1_MIN_MAX  255
   /* DD_EXT_AGC_TER command, AGC_2_MIN field definition (address 5,size 8, lsb 0, unsigned) */
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MIN_LSB         0
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MIN_MASK        0xff
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MIN_MIN         0
   #define  Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MIN_MAX         255
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MIN_AGC_2_MIN_MIN  0
    #define Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MIN_AGC_2_MIN_MAX  255
   /* DD_EXT_AGC_TER command, AGC_1_LEVEL field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2183_DD_EXT_AGC_TER_RESPONSE_AGC_1_LEVEL_LSB         0
   #define  Si2183_DD_EXT_AGC_TER_RESPONSE_AGC_1_LEVEL_MASK        0xff
   /* DD_EXT_AGC_TER command, AGC_2_LEVEL field definition (address 2, size 8, lsb 0, unsigned)*/
   #define  Si2183_DD_EXT_AGC_TER_RESPONSE_AGC_2_LEVEL_LSB         0
   #define  Si2183_DD_EXT_AGC_TER_RESPONSE_AGC_2_LEVEL_MASK        0xff

#endif /* Si2183_DD_EXT_AGC_TER_CMD */

#endif /* TERRESTRIAL_FRONT_END */

/* Si2183_DD_FER command definition */
#define   Si2183_DD_FER_CMD 0x86

#ifdef    Si2183_DD_FER_CMD
  #define Si2183_DD_FER_CMD_CODE 0x010086

    typedef struct { /* Si2183_DD_FER_CMD_struct */
     unsigned char   rst;
   } Si2183_DD_FER_CMD_struct;


    typedef struct { /* Si2183_DD_FER_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   exp;
      unsigned char   mant;
   }  Si2183_DD_FER_CMD_REPLY_struct;

   /* DD_FER command, RST field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2183_DD_FER_CMD_RST_LSB         0
   #define  Si2183_DD_FER_CMD_RST_MASK        0x01
   #define  Si2183_DD_FER_CMD_RST_MIN         0
   #define  Si2183_DD_FER_CMD_RST_MAX         1
    #define Si2183_DD_FER_CMD_RST_CLEAR  1
    #define Si2183_DD_FER_CMD_RST_RUN    0
   /* DD_FER command, EXP field definition (address 1, size 4, lsb 0, unsigned)*/
   #define  Si2183_DD_FER_RESPONSE_EXP_LSB         0
   #define  Si2183_DD_FER_RESPONSE_EXP_MASK        0x0f
    #define Si2183_DD_FER_RESPONSE_EXP_EXP_MIN  0
    #define Si2183_DD_FER_RESPONSE_EXP_EXP_MAX  8
   /* DD_FER command, MANT field definition (address 2, size 8, lsb 0, unsigned)*/
   #define  Si2183_DD_FER_RESPONSE_MANT_LSB         0
   #define  Si2183_DD_FER_RESPONSE_MANT_MASK        0xff
    #define Si2183_DD_FER_RESPONSE_MANT_MANT_MIN  0
    #define Si2183_DD_FER_RESPONSE_MANT_MANT_MAX  99

#endif /* Si2183_DD_FER_CMD */

/* Si2183_DD_GET_REG command definition */
#define   Si2183_DD_GET_REG_CMD 0x8f

#ifdef    Si2183_DD_GET_REG_CMD
  #define Si2183_DD_GET_REG_CMD_CODE 0x01008f

    typedef struct { /* Si2183_DD_GET_REG_CMD_struct */
     unsigned char   reg_code_lsb;
     unsigned char   reg_code_mid;
     unsigned char   reg_code_msb;
   } Si2183_DD_GET_REG_CMD_struct;


    typedef struct { /* Si2183_DD_GET_REG_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   data1;
      unsigned char   data2;
      unsigned char   data3;
      unsigned char   data4;
   }  Si2183_DD_GET_REG_CMD_REPLY_struct;

   /* DD_GET_REG command, REG_CODE_LSB field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_DD_GET_REG_CMD_REG_CODE_LSB_LSB         0
   #define  Si2183_DD_GET_REG_CMD_REG_CODE_LSB_MASK        0xff
   #define  Si2183_DD_GET_REG_CMD_REG_CODE_LSB_MIN         0
   #define  Si2183_DD_GET_REG_CMD_REG_CODE_LSB_MAX         255
    #define Si2183_DD_GET_REG_CMD_REG_CODE_LSB_REG_CODE_LSB_MIN  0
    #define Si2183_DD_GET_REG_CMD_REG_CODE_LSB_REG_CODE_LSB_MAX  255
   /* DD_GET_REG command, REG_CODE_MID field definition (address 2,size 8, lsb 0, unsigned) */
   #define  Si2183_DD_GET_REG_CMD_REG_CODE_MID_LSB         0
   #define  Si2183_DD_GET_REG_CMD_REG_CODE_MID_MASK        0xff
   #define  Si2183_DD_GET_REG_CMD_REG_CODE_MID_MIN         0
   #define  Si2183_DD_GET_REG_CMD_REG_CODE_MID_MAX         255
    #define Si2183_DD_GET_REG_CMD_REG_CODE_MID_REG_CODE_MID_MIN  0
    #define Si2183_DD_GET_REG_CMD_REG_CODE_MID_REG_CODE_MID_MAX  255
   /* DD_GET_REG command, REG_CODE_MSB field definition (address 3,size 8, lsb 0, unsigned) */
   #define  Si2183_DD_GET_REG_CMD_REG_CODE_MSB_LSB         0
   #define  Si2183_DD_GET_REG_CMD_REG_CODE_MSB_MASK        0xff
   #define  Si2183_DD_GET_REG_CMD_REG_CODE_MSB_MIN         0
   #define  Si2183_DD_GET_REG_CMD_REG_CODE_MSB_MAX         255
    #define Si2183_DD_GET_REG_CMD_REG_CODE_MSB_REG_CODE_MSB_MIN  0
    #define Si2183_DD_GET_REG_CMD_REG_CODE_MSB_REG_CODE_MSB_MAX  255
   /* DD_GET_REG command, DATA1 field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2183_DD_GET_REG_RESPONSE_DATA1_LSB         0
   #define  Si2183_DD_GET_REG_RESPONSE_DATA1_MASK        0xff
    #define Si2183_DD_GET_REG_RESPONSE_DATA1_DATA1_MIN  0
    #define Si2183_DD_GET_REG_RESPONSE_DATA1_DATA1_MAX  255
   /* DD_GET_REG command, DATA2 field definition (address 2, size 8, lsb 0, unsigned)*/
   #define  Si2183_DD_GET_REG_RESPONSE_DATA2_LSB         0
   #define  Si2183_DD_GET_REG_RESPONSE_DATA2_MASK        0xff
    #define Si2183_DD_GET_REG_RESPONSE_DATA2_DATA2_MIN  0
    #define Si2183_DD_GET_REG_RESPONSE_DATA2_DATA2_MAX  255
   /* DD_GET_REG command, DATA3 field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si2183_DD_GET_REG_RESPONSE_DATA3_LSB         0
   #define  Si2183_DD_GET_REG_RESPONSE_DATA3_MASK        0xff
    #define Si2183_DD_GET_REG_RESPONSE_DATA3_DATA3_MIN  0
    #define Si2183_DD_GET_REG_RESPONSE_DATA3_DATA3_MAX  255
   /* DD_GET_REG command, DATA4 field definition (address 4, size 8, lsb 0, unsigned)*/
   #define  Si2183_DD_GET_REG_RESPONSE_DATA4_LSB         0
   #define  Si2183_DD_GET_REG_RESPONSE_DATA4_MASK        0xff
    #define Si2183_DD_GET_REG_RESPONSE_DATA4_DATA4_MIN  0
    #define Si2183_DD_GET_REG_RESPONSE_DATA4_DATA4_MAX  255

#endif /* Si2183_DD_GET_REG_CMD */

/* Si2183_DD_MP_DEFAULTS command definition */
#define   Si2183_DD_MP_DEFAULTS_CMD 0x88

#ifdef    Si2183_DD_MP_DEFAULTS_CMD
  #define Si2183_DD_MP_DEFAULTS_CMD_CODE 0x010088

    typedef struct { /* Si2183_DD_MP_DEFAULTS_CMD_struct */
     unsigned char   mp_a_mode;
     unsigned char   mp_b_mode;
     unsigned char   mp_c_mode;
     unsigned char   mp_d_mode;
   } Si2183_DD_MP_DEFAULTS_CMD_struct;


    typedef struct { /* Si2183_DD_MP_DEFAULTS_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   mp_a_mode;
      unsigned char   mp_b_mode;
      unsigned char   mp_c_mode;
      unsigned char   mp_d_mode;
   }  Si2183_DD_MP_DEFAULTS_CMD_REPLY_struct;

   /* DD_MP_DEFAULTS command, MP_A_MODE field definition (address 1,size 7, lsb 0, unsigned) */
   #define  Si2183_DD_MP_DEFAULTS_CMD_MP_A_MODE_LSB         0
   #define  Si2183_DD_MP_DEFAULTS_CMD_MP_A_MODE_MASK        0x7f
   #define  Si2183_DD_MP_DEFAULTS_CMD_MP_A_MODE_MIN         0
   #define  Si2183_DD_MP_DEFAULTS_CMD_MP_A_MODE_MAX         3
    #define Si2183_DD_MP_DEFAULTS_CMD_MP_A_MODE_DISABLE    1
    #define Si2183_DD_MP_DEFAULTS_CMD_MP_A_MODE_DRIVE_0    2
    #define Si2183_DD_MP_DEFAULTS_CMD_MP_A_MODE_DRIVE_1    3
    #define Si2183_DD_MP_DEFAULTS_CMD_MP_A_MODE_NO_CHANGE  0
   /* DD_MP_DEFAULTS command, MP_B_MODE field definition (address 2,size 7, lsb 0, unsigned) */
   #define  Si2183_DD_MP_DEFAULTS_CMD_MP_B_MODE_LSB         0
   #define  Si2183_DD_MP_DEFAULTS_CMD_MP_B_MODE_MASK        0x7f
   #define  Si2183_DD_MP_DEFAULTS_CMD_MP_B_MODE_MIN         0
   #define  Si2183_DD_MP_DEFAULTS_CMD_MP_B_MODE_MAX         3
    #define Si2183_DD_MP_DEFAULTS_CMD_MP_B_MODE_DISABLE    1
    #define Si2183_DD_MP_DEFAULTS_CMD_MP_B_MODE_DRIVE_0    2
    #define Si2183_DD_MP_DEFAULTS_CMD_MP_B_MODE_DRIVE_1    3
    #define Si2183_DD_MP_DEFAULTS_CMD_MP_B_MODE_NO_CHANGE  0
   /* DD_MP_DEFAULTS command, MP_C_MODE field definition (address 3,size 7, lsb 0, unsigned) */
   #define  Si2183_DD_MP_DEFAULTS_CMD_MP_C_MODE_LSB         0
   #define  Si2183_DD_MP_DEFAULTS_CMD_MP_C_MODE_MASK        0x7f
   #define  Si2183_DD_MP_DEFAULTS_CMD_MP_C_MODE_MIN         0
   #define  Si2183_DD_MP_DEFAULTS_CMD_MP_C_MODE_MAX         3
    #define Si2183_DD_MP_DEFAULTS_CMD_MP_C_MODE_DISABLE    1
    #define Si2183_DD_MP_DEFAULTS_CMD_MP_C_MODE_DRIVE_0    2
    #define Si2183_DD_MP_DEFAULTS_CMD_MP_C_MODE_DRIVE_1    3
    #define Si2183_DD_MP_DEFAULTS_CMD_MP_C_MODE_NO_CHANGE  0
   /* DD_MP_DEFAULTS command, MP_D_MODE field definition (address 4,size 7, lsb 0, unsigned) */
   #define  Si2183_DD_MP_DEFAULTS_CMD_MP_D_MODE_LSB         0
   #define  Si2183_DD_MP_DEFAULTS_CMD_MP_D_MODE_MASK        0x7f
   #define  Si2183_DD_MP_DEFAULTS_CMD_MP_D_MODE_MIN         0
   #define  Si2183_DD_MP_DEFAULTS_CMD_MP_D_MODE_MAX         3
    #define Si2183_DD_MP_DEFAULTS_CMD_MP_D_MODE_DISABLE    1
    #define Si2183_DD_MP_DEFAULTS_CMD_MP_D_MODE_DRIVE_0    2
    #define Si2183_DD_MP_DEFAULTS_CMD_MP_D_MODE_DRIVE_1    3
    #define Si2183_DD_MP_DEFAULTS_CMD_MP_D_MODE_NO_CHANGE  0
   /* DD_MP_DEFAULTS command, MP_A_MODE field definition (address 1, size 7, lsb 0, unsigned)*/
   #define  Si2183_DD_MP_DEFAULTS_RESPONSE_MP_A_MODE_LSB         0
   #define  Si2183_DD_MP_DEFAULTS_RESPONSE_MP_A_MODE_MASK        0x7f
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_A_MODE_AGC_1           3
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_A_MODE_AGC_1_INVERTED  4
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_A_MODE_AGC_2           5
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_A_MODE_AGC_2_INVERTED  6
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_A_MODE_DISABLE         0
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_A_MODE_DRIVE_0         1
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_A_MODE_DRIVE_1         2
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_A_MODE_FEF             7
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_A_MODE_FEF_INVERTED    8
   /* DD_MP_DEFAULTS command, MP_B_MODE field definition (address 2, size 7, lsb 0, unsigned)*/
   #define  Si2183_DD_MP_DEFAULTS_RESPONSE_MP_B_MODE_LSB         0
   #define  Si2183_DD_MP_DEFAULTS_RESPONSE_MP_B_MODE_MASK        0x7f
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_B_MODE_AGC_1           3
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_B_MODE_AGC_1_INVERTED  4
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_B_MODE_AGC_2           5
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_B_MODE_AGC_2_INVERTED  6
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_B_MODE_DISABLE         0
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_B_MODE_DRIVE_0         1
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_B_MODE_DRIVE_1         2
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_B_MODE_FEF             7
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_B_MODE_FEF_INVERTED    8
   /* DD_MP_DEFAULTS command, MP_C_MODE field definition (address 3, size 7, lsb 0, unsigned)*/
   #define  Si2183_DD_MP_DEFAULTS_RESPONSE_MP_C_MODE_LSB         0
   #define  Si2183_DD_MP_DEFAULTS_RESPONSE_MP_C_MODE_MASK        0x7f
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_C_MODE_AGC_1           3
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_C_MODE_AGC_1_INVERTED  4
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_C_MODE_AGC_2           5
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_C_MODE_AGC_2_INVERTED  6
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_C_MODE_DISABLE         0
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_C_MODE_DRIVE_0         1
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_C_MODE_DRIVE_1         2
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_C_MODE_FEF             7
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_C_MODE_FEF_INVERTED    8
   /* DD_MP_DEFAULTS command, MP_D_MODE field definition (address 4, size 7, lsb 0, unsigned)*/
   #define  Si2183_DD_MP_DEFAULTS_RESPONSE_MP_D_MODE_LSB         0
   #define  Si2183_DD_MP_DEFAULTS_RESPONSE_MP_D_MODE_MASK        0x7f
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_D_MODE_AGC_1           3
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_D_MODE_AGC_1_INVERTED  4
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_D_MODE_AGC_2           5
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_D_MODE_AGC_2_INVERTED  6
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_D_MODE_DISABLE         0
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_D_MODE_DRIVE_0         1
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_D_MODE_DRIVE_1         2
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_D_MODE_FEF             7
    #define Si2183_DD_MP_DEFAULTS_RESPONSE_MP_D_MODE_FEF_INVERTED    8

#endif /* Si2183_DD_MP_DEFAULTS_CMD */

/* Si2183_DD_PER command definition */
#define   Si2183_DD_PER_CMD 0x83

#ifdef    Si2183_DD_PER_CMD
  #define Si2183_DD_PER_CMD_CODE 0x010083

    typedef struct { /* Si2183_DD_PER_CMD_struct */
     unsigned char   rst;
   } Si2183_DD_PER_CMD_struct;


    typedef struct { /* Si2183_DD_PER_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   exp;
      unsigned char   mant;
   }  Si2183_DD_PER_CMD_REPLY_struct;

   /* DD_PER command, RST field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2183_DD_PER_CMD_RST_LSB         0
   #define  Si2183_DD_PER_CMD_RST_MASK        0x01
   #define  Si2183_DD_PER_CMD_RST_MIN         0
   #define  Si2183_DD_PER_CMD_RST_MAX         1
    #define Si2183_DD_PER_CMD_RST_CLEAR  1
    #define Si2183_DD_PER_CMD_RST_RUN    0
   /* DD_PER command, EXP field definition (address 1, size 4, lsb 0, unsigned)*/
   #define  Si2183_DD_PER_RESPONSE_EXP_LSB         0
   #define  Si2183_DD_PER_RESPONSE_EXP_MASK        0x0f
    #define Si2183_DD_PER_RESPONSE_EXP_EXP_MIN  0
    #define Si2183_DD_PER_RESPONSE_EXP_EXP_MAX  8
   /* DD_PER command, MANT field definition (address 2, size 8, lsb 0, unsigned)*/
   #define  Si2183_DD_PER_RESPONSE_MANT_LSB         0
   #define  Si2183_DD_PER_RESPONSE_MANT_MASK        0xff
    #define Si2183_DD_PER_RESPONSE_MANT_MANT_MIN  0
    #define Si2183_DD_PER_RESPONSE_MANT_MANT_MAX  99

#endif /* Si2183_DD_PER_CMD */

/* Si2183_DD_RESTART command definition */
#define   Si2183_DD_RESTART_CMD 0x85

#ifdef    Si2183_DD_RESTART_CMD
  #define Si2183_DD_RESTART_CMD_CODE 0x010085

    typedef struct { /* Si2183_DD_RESTART_CMD_struct */
         unsigned char   nothing;   } Si2183_DD_RESTART_CMD_struct;


    typedef struct { /* Si2183_DD_RESTART_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
   }  Si2183_DD_RESTART_CMD_REPLY_struct;

#endif /* Si2183_DD_RESTART_CMD */

/* Si2183_DD_RESTART_EXT command definition */
#define   Si2183_DD_RESTART_EXT_CMD 0x85

#ifdef    Si2183_DD_RESTART_EXT_CMD
  #define Si2183_DD_RESTART_EXT_CMD_CODE 0x020085

    typedef struct { /* Si2183_DD_RESTART_EXT_CMD_struct */
     unsigned char   freq_plan;
     unsigned char   freq_plan_ts_clk;
     unsigned long   tuned_rf_freq;
   } Si2183_DD_RESTART_EXT_CMD_struct;


    typedef struct { /* Si2183_DD_RESTART_EXT_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
   }  Si2183_DD_RESTART_EXT_CMD_REPLY_struct;

   /* DD_RESTART_EXT command, FREQ_PLAN field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2183_DD_RESTART_EXT_CMD_FREQ_PLAN_LSB         0
   #define  Si2183_DD_RESTART_EXT_CMD_FREQ_PLAN_MASK        0x01
   #define  Si2183_DD_RESTART_EXT_CMD_FREQ_PLAN_MIN         0
   #define  Si2183_DD_RESTART_EXT_CMD_FREQ_PLAN_MAX         1
    #define Si2183_DD_RESTART_EXT_CMD_FREQ_PLAN_DISABLED  0
    #define Si2183_DD_RESTART_EXT_CMD_FREQ_PLAN_ENABLED   1
   /* DD_RESTART_EXT command, FREQ_PLAN_TS_CLK field definition (address 1,size 1, lsb 1, unsigned) */
   #define  Si2183_DD_RESTART_EXT_CMD_FREQ_PLAN_TS_CLK_LSB         1
   #define  Si2183_DD_RESTART_EXT_CMD_FREQ_PLAN_TS_CLK_MASK        0x01
   #define  Si2183_DD_RESTART_EXT_CMD_FREQ_PLAN_TS_CLK_MIN         0
   #define  Si2183_DD_RESTART_EXT_CMD_FREQ_PLAN_TS_CLK_MAX         1
    #define Si2183_DD_RESTART_EXT_CMD_FREQ_PLAN_TS_CLK_DISABLED  0
    #define Si2183_DD_RESTART_EXT_CMD_FREQ_PLAN_TS_CLK_ENABLED   1
   /* DD_RESTART_EXT command, TUNED_RF_FREQ field definition (address 4,size 32, lsb 0, unsigned) */
   #define  Si2183_DD_RESTART_EXT_CMD_TUNED_RF_FREQ_LSB         0
   #define  Si2183_DD_RESTART_EXT_CMD_TUNED_RF_FREQ_MASK        0xffffffff
   #define  Si2183_DD_RESTART_EXT_CMD_TUNED_RF_FREQ_MIN         0
   #define  Si2183_DD_RESTART_EXT_CMD_TUNED_RF_FREQ_MAX         4294967295
    #define Si2183_DD_RESTART_EXT_CMD_TUNED_RF_FREQ_TUNED_RF_FREQ_MIN  0
    #define Si2183_DD_RESTART_EXT_CMD_TUNED_RF_FREQ_TUNED_RF_FREQ_MAX  4294967295
#endif /* Si2183_DD_RESTART_EXT_CMD */

/* Si2183_DD_SET_REG command definition */
#define   Si2183_DD_SET_REG_CMD 0x8e

#ifdef    Si2183_DD_SET_REG_CMD
  #define Si2183_DD_SET_REG_CMD_CODE 0x01008e

    typedef struct { /* Si2183_DD_SET_REG_CMD_struct */
     unsigned char   reg_code_lsb;
     unsigned char   reg_code_mid;
     unsigned char   reg_code_msb;
     unsigned long   value;
   } Si2183_DD_SET_REG_CMD_struct;


    typedef struct { /* Si2183_DD_SET_REG_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
   }  Si2183_DD_SET_REG_CMD_REPLY_struct;

   /* DD_SET_REG command, REG_CODE_LSB field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_DD_SET_REG_CMD_REG_CODE_LSB_LSB         0
   #define  Si2183_DD_SET_REG_CMD_REG_CODE_LSB_MASK        0xff
   #define  Si2183_DD_SET_REG_CMD_REG_CODE_LSB_MIN         0
   #define  Si2183_DD_SET_REG_CMD_REG_CODE_LSB_MAX         255
    #define Si2183_DD_SET_REG_CMD_REG_CODE_LSB_REG_CODE_LSB_MIN  0
    #define Si2183_DD_SET_REG_CMD_REG_CODE_LSB_REG_CODE_LSB_MAX  255
   /* DD_SET_REG command, REG_CODE_MID field definition (address 2,size 8, lsb 0, unsigned) */
   #define  Si2183_DD_SET_REG_CMD_REG_CODE_MID_LSB         0
   #define  Si2183_DD_SET_REG_CMD_REG_CODE_MID_MASK        0xff
   #define  Si2183_DD_SET_REG_CMD_REG_CODE_MID_MIN         0
   #define  Si2183_DD_SET_REG_CMD_REG_CODE_MID_MAX         255
    #define Si2183_DD_SET_REG_CMD_REG_CODE_MID_REG_CODE_MID_MIN  0
    #define Si2183_DD_SET_REG_CMD_REG_CODE_MID_REG_CODE_MID_MAX  255
   /* DD_SET_REG command, REG_CODE_MSB field definition (address 3,size 8, lsb 0, unsigned) */
   #define  Si2183_DD_SET_REG_CMD_REG_CODE_MSB_LSB         0
   #define  Si2183_DD_SET_REG_CMD_REG_CODE_MSB_MASK        0xff
   #define  Si2183_DD_SET_REG_CMD_REG_CODE_MSB_MIN         0
   #define  Si2183_DD_SET_REG_CMD_REG_CODE_MSB_MAX         255
    #define Si2183_DD_SET_REG_CMD_REG_CODE_MSB_REG_CODE_MSB_MIN  0
    #define Si2183_DD_SET_REG_CMD_REG_CODE_MSB_REG_CODE_MSB_MAX  255
   /* DD_SET_REG command, VALUE field definition (address 4,size 32, lsb 0, unsigned) */
   #define  Si2183_DD_SET_REG_CMD_VALUE_LSB         0
   #define  Si2183_DD_SET_REG_CMD_VALUE_MASK        0xffffffff
   #define  Si2183_DD_SET_REG_CMD_VALUE_MIN         0
   #define  Si2183_DD_SET_REG_CMD_VALUE_MAX         4294967295
    #define Si2183_DD_SET_REG_CMD_VALUE_VALUE_MIN  0
    #define Si2183_DD_SET_REG_CMD_VALUE_VALUE_MAX  4294967295
#endif /* Si2183_DD_SET_REG_CMD */

/* Si2183_DD_SSI_SQI command definition */
#define   Si2183_DD_SSI_SQI_CMD 0x8b

#ifdef    Si2183_DD_SSI_SQI_CMD
  #define Si2183_DD_SSI_SQI_CMD_CODE 0x01008b

    typedef struct { /* Si2183_DD_SSI_SQI_CMD_struct */
     signed   char   tuner_rssi;
   } Si2183_DD_SSI_SQI_CMD_struct;


    typedef struct { /* Si2183_DD_SSI_SQI_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   ssi;
               char   sqi;
   }  Si2183_DD_SSI_SQI_CMD_REPLY_struct;

   /* DD_SSI_SQI command, TUNER_RSSI field definition (address 1,size 8, lsb 0, signed) */
   #define  Si2183_DD_SSI_SQI_CMD_TUNER_RSSI_LSB         0
   #define  Si2183_DD_SSI_SQI_CMD_TUNER_RSSI_MASK        0xff
   #define  Si2183_DD_SSI_SQI_CMD_TUNER_RSSI_SHIFT       24
   #define  Si2183_DD_SSI_SQI_CMD_TUNER_RSSI_MIN         -128.0
   #define  Si2183_DD_SSI_SQI_CMD_TUNER_RSSI_MAX         127
   /* DD_SSI_SQI command, SSI field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2183_DD_SSI_SQI_RESPONSE_SSI_LSB         0
   #define  Si2183_DD_SSI_SQI_RESPONSE_SSI_MASK        0xff
    #define Si2183_DD_SSI_SQI_RESPONSE_SSI_SSI_MIN  0
    #define Si2183_DD_SSI_SQI_RESPONSE_SSI_SSI_MAX  100
   /* DD_SSI_SQI command, SQI field definition (address 2, size 8, lsb 0, signed)*/
   #define  Si2183_DD_SSI_SQI_RESPONSE_SQI_LSB         0
   #define  Si2183_DD_SSI_SQI_RESPONSE_SQI_MASK        0xff
   #define  Si2183_DD_SSI_SQI_RESPONSE_SQI_SHIFT       24
    #define Si2183_DD_SSI_SQI_RESPONSE_SQI_SQI_MIN  -1
    #define Si2183_DD_SSI_SQI_RESPONSE_SQI_SQI_MAX  100

#endif /* Si2183_DD_SSI_SQI_CMD */

/* Si2183_DD_STATUS command definition */
#define   Si2183_DD_STATUS_CMD 0x87

#ifdef    Si2183_DD_STATUS_CMD
  #define Si2183_DD_STATUS_CMD_CODE 0x010087

    typedef struct { /* Si2183_DD_STATUS_CMD_struct */
     unsigned char   intack;
   } Si2183_DD_STATUS_CMD_struct;


    typedef struct { /* Si2183_DD_STATUS_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   pclint;
      unsigned char   dlint;
      unsigned char   berint;
      unsigned char   uncorint;
      unsigned char   rsqint_bit5;
      unsigned char   rsqint_bit6;
      unsigned char   rsqint_bit7;
      unsigned char   pcl;
      unsigned char   dl;
      unsigned char   ber;
      unsigned char   uncor;
      unsigned char   rsqstat_bit5;
      unsigned char   rsqstat_bit6;
      unsigned char   rsqstat_bit7;
      unsigned char   modulation;
      unsigned int    ts_bit_rate;
      unsigned int    ts_clk_freq;
   }  Si2183_DD_STATUS_CMD_REPLY_struct;

   /* DD_STATUS command, INTACK field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2183_DD_STATUS_CMD_INTACK_LSB         0
   #define  Si2183_DD_STATUS_CMD_INTACK_MASK        0x01
   #define  Si2183_DD_STATUS_CMD_INTACK_MIN         0
   #define  Si2183_DD_STATUS_CMD_INTACK_MAX         1
    #define Si2183_DD_STATUS_CMD_INTACK_CLEAR  1
    #define Si2183_DD_STATUS_CMD_INTACK_OK     0
   /* DD_STATUS command, PCLINT field definition (address 1, size 1, lsb 1, unsigned)*/
   #define  Si2183_DD_STATUS_RESPONSE_PCLINT_LSB         1
   #define  Si2183_DD_STATUS_RESPONSE_PCLINT_MASK        0x01
    #define Si2183_DD_STATUS_RESPONSE_PCLINT_CHANGED    1
    #define Si2183_DD_STATUS_RESPONSE_PCLINT_NO_CHANGE  0
   /* DD_STATUS command, DLINT field definition (address 1, size 1, lsb 2, unsigned)*/
   #define  Si2183_DD_STATUS_RESPONSE_DLINT_LSB         2
   #define  Si2183_DD_STATUS_RESPONSE_DLINT_MASK        0x01
    #define Si2183_DD_STATUS_RESPONSE_DLINT_CHANGED    1
    #define Si2183_DD_STATUS_RESPONSE_DLINT_NO_CHANGE  0
   /* DD_STATUS command, BERINT field definition (address 1, size 1, lsb 3, unsigned)*/
   #define  Si2183_DD_STATUS_RESPONSE_BERINT_LSB         3
   #define  Si2183_DD_STATUS_RESPONSE_BERINT_MASK        0x01
    #define Si2183_DD_STATUS_RESPONSE_BERINT_CHANGED    1
    #define Si2183_DD_STATUS_RESPONSE_BERINT_NO_CHANGE  0
   /* DD_STATUS command, UNCORINT field definition (address 1, size 1, lsb 4, unsigned)*/
   #define  Si2183_DD_STATUS_RESPONSE_UNCORINT_LSB         4
   #define  Si2183_DD_STATUS_RESPONSE_UNCORINT_MASK        0x01
    #define Si2183_DD_STATUS_RESPONSE_UNCORINT_CHANGED    1
    #define Si2183_DD_STATUS_RESPONSE_UNCORINT_NO_CHANGE  0
   /* DD_STATUS command, RSQINT_BIT5 field definition (address 1, size 1, lsb 5, unsigned)*/
   #define  Si2183_DD_STATUS_RESPONSE_RSQINT_BIT5_LSB         5
   #define  Si2183_DD_STATUS_RESPONSE_RSQINT_BIT5_MASK        0x01
    #define Si2183_DD_STATUS_RESPONSE_RSQINT_BIT5_CHANGED    1
    #define Si2183_DD_STATUS_RESPONSE_RSQINT_BIT5_NO_CHANGE  0
   /* DD_STATUS command, RSQINT_BIT6 field definition (address 1, size 1, lsb 6, unsigned)*/
   #define  Si2183_DD_STATUS_RESPONSE_RSQINT_BIT6_LSB         6
   #define  Si2183_DD_STATUS_RESPONSE_RSQINT_BIT6_MASK        0x01
    #define Si2183_DD_STATUS_RESPONSE_RSQINT_BIT6_CHANGED    1
    #define Si2183_DD_STATUS_RESPONSE_RSQINT_BIT6_NO_CHANGE  0
   /* DD_STATUS command, RSQINT_BIT7 field definition (address 1, size 1, lsb 7, unsigned)*/
   #define  Si2183_DD_STATUS_RESPONSE_RSQINT_BIT7_LSB         7
   #define  Si2183_DD_STATUS_RESPONSE_RSQINT_BIT7_MASK        0x01
    #define Si2183_DD_STATUS_RESPONSE_RSQINT_BIT7_CHANGED    1
    #define Si2183_DD_STATUS_RESPONSE_RSQINT_BIT7_NO_CHANGE  0
   /* DD_STATUS command, PCL field definition (address 2, size 1, lsb 1, unsigned)*/
   #define  Si2183_DD_STATUS_RESPONSE_PCL_LSB         1
   #define  Si2183_DD_STATUS_RESPONSE_PCL_MASK        0x01
    #define Si2183_DD_STATUS_RESPONSE_PCL_LOCKED   1
    #define Si2183_DD_STATUS_RESPONSE_PCL_NO_LOCK  0
   /* DD_STATUS command, DL field definition (address 2, size 1, lsb 2, unsigned)*/
   #define  Si2183_DD_STATUS_RESPONSE_DL_LSB         2
   #define  Si2183_DD_STATUS_RESPONSE_DL_MASK        0x01
    #define Si2183_DD_STATUS_RESPONSE_DL_LOCKED   1
    #define Si2183_DD_STATUS_RESPONSE_DL_NO_LOCK  0
   /* DD_STATUS command, BER field definition (address 2, size 1, lsb 3, unsigned)*/
   #define  Si2183_DD_STATUS_RESPONSE_BER_LSB         3
   #define  Si2183_DD_STATUS_RESPONSE_BER_MASK        0x01
    #define Si2183_DD_STATUS_RESPONSE_BER_BER_ABOVE  1
    #define Si2183_DD_STATUS_RESPONSE_BER_BER_BELOW  0
   /* DD_STATUS command, UNCOR field definition (address 2, size 1, lsb 4, unsigned)*/
   #define  Si2183_DD_STATUS_RESPONSE_UNCOR_LSB         4
   #define  Si2183_DD_STATUS_RESPONSE_UNCOR_MASK        0x01
    #define Si2183_DD_STATUS_RESPONSE_UNCOR_NO_UNCOR_FOUND  0
    #define Si2183_DD_STATUS_RESPONSE_UNCOR_UNCOR_FOUND     1
   /* DD_STATUS command, RSQSTAT_BIT5 field definition (address 2, size 1, lsb 5, unsigned)*/
   #define  Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT5_LSB         5
   #define  Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT5_MASK        0x01
    #define  Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT5_NO_CHANGE 0
    #define  Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT5_CHANGE    1
   /* DD_STATUS command, RSQSTAT_BIT6 field definition (address 2, size 1, lsb 6, unsigned)*/
   #define  Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT6_LSB         6
   #define  Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT6_MASK        0x01
   /* DD_STATUS command, RSQSTAT_BIT7 field definition (address 2, size 1, lsb 7, unsigned)*/
   #define  Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT7_LSB         7
   #define  Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT7_MASK        0x01
   /* DD_STATUS command, MODULATION field definition (address 3, size 4, lsb 0, unsigned)*/
   #define  Si2183_DD_STATUS_RESPONSE_MODULATION_LSB         0
   #define  Si2183_DD_STATUS_RESPONSE_MODULATION_MASK        0x0f
    #define Si2183_DD_STATUS_RESPONSE_MODULATION_DSS    10
    #define Si2183_DD_STATUS_RESPONSE_MODULATION_DVBC   3
    #define Si2183_DD_STATUS_RESPONSE_MODULATION_DVBC2  11
    #define Si2183_DD_STATUS_RESPONSE_MODULATION_DVBS   8
    #define Si2183_DD_STATUS_RESPONSE_MODULATION_DVBS2  9
    #define Si2183_DD_STATUS_RESPONSE_MODULATION_DVBT   2
    #define Si2183_DD_STATUS_RESPONSE_MODULATION_DVBT2  7
    #define Si2183_DD_STATUS_RESPONSE_MODULATION_ISDBT  4
    #define Si2183_DD_STATUS_RESPONSE_MODULATION_MCNS   1
   /* DD_STATUS command, TS_BIT_RATE field definition (address 4, size 16, lsb 0, unsigned)*/
   #define  Si2183_DD_STATUS_RESPONSE_TS_BIT_RATE_LSB         0
   #define  Si2183_DD_STATUS_RESPONSE_TS_BIT_RATE_MASK        0xffff
   /* DD_STATUS command, TS_CLK_FREQ field definition (address 6, size 16, lsb 0, unsigned)*/
   #define  Si2183_DD_STATUS_RESPONSE_TS_CLK_FREQ_LSB         0
   #define  Si2183_DD_STATUS_RESPONSE_TS_CLK_FREQ_MASK        0xffff

#endif /* Si2183_DD_STATUS_CMD */

/* Si2183_DD_TS_PINS command definition */
#define   Si2183_DD_TS_PINS_CMD 0x80

#ifdef    Si2183_DD_TS_PINS_CMD
  #define Si2183_DD_TS_PINS_CMD_CODE 0x010080

    typedef struct { /* Si2183_DD_TS_PINS_CMD_struct */
     unsigned char   primary_ts_mode;
     unsigned char   primary_ts_activity;
     unsigned char   primary_ts_dir;
     unsigned char   secondary_ts_mode;
     unsigned char   secondary_ts_activity;
     unsigned char   secondary_ts_dir;
     unsigned char   demod_role;
     unsigned long   master_freq;
   } Si2183_DD_TS_PINS_CMD_struct;


    typedef struct { /* Si2183_DD_TS_PINS_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   primary_ts_mode;
      unsigned char   primary_ts_activity;
      unsigned char   secondary_ts_mode;
      unsigned char   secondary_ts_activity;
   }  Si2183_DD_TS_PINS_CMD_REPLY_struct;

   /* DD_TS_PINS command, PRIMARY_TS_MODE field definition (address 1,size 3, lsb 0, unsigned) */
   #define  Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_LSB         0
   #define  Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_MASK        0x07
   #define  Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_MIN         0
   #define  Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_MAX         2
    #define Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_DRIVE_TS   2
    #define Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_NOT_USED   1
    #define Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_NO_CHANGE  0
   /* DD_TS_PINS command, PRIMARY_TS_ACTIVITY field definition (address 1,size 1, lsb 3, unsigned) */
   #define  Si2183_DD_TS_PINS_CMD_PRIMARY_TS_ACTIVITY_LSB         3
   #define  Si2183_DD_TS_PINS_CMD_PRIMARY_TS_ACTIVITY_MASK        0x01
   #define  Si2183_DD_TS_PINS_CMD_PRIMARY_TS_ACTIVITY_MIN         0
   #define  Si2183_DD_TS_PINS_CMD_PRIMARY_TS_ACTIVITY_MAX         1
    #define Si2183_DD_TS_PINS_CMD_PRIMARY_TS_ACTIVITY_CLEAR  1
    #define Si2183_DD_TS_PINS_CMD_PRIMARY_TS_ACTIVITY_RUN    0
   /* DD_TS_PINS command, PRIMARY_TS_DIR field definition (address 1,size 1, lsb 4, unsigned) */
   #define  Si2183_DD_TS_PINS_CMD_PRIMARY_TS_DIR_LSB         4
   #define  Si2183_DD_TS_PINS_CMD_PRIMARY_TS_DIR_MASK        0x01
   #define  Si2183_DD_TS_PINS_CMD_PRIMARY_TS_DIR_MIN         0
   #define  Si2183_DD_TS_PINS_CMD_PRIMARY_TS_DIR_MAX         1
    #define Si2183_DD_TS_PINS_CMD_PRIMARY_TS_DIR_INPUT   1
    #define Si2183_DD_TS_PINS_CMD_PRIMARY_TS_DIR_OUTPUT  0
   /* DD_TS_PINS command, SECONDARY_TS_MODE field definition (address 2,size 3, lsb 0, unsigned) */
   #define  Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_LSB         0
   #define  Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_MASK        0x07
   #define  Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_MIN         0
   #define  Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_MAX         2
    #define Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_DRIVE_TS   2
    #define Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_NOT_USED   1
    #define Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_NO_CHANGE  0
   /* DD_TS_PINS command, SECONDARY_TS_ACTIVITY field definition (address 2,size 1, lsb 3, unsigned) */
   #define  Si2183_DD_TS_PINS_CMD_SECONDARY_TS_ACTIVITY_LSB         3
   #define  Si2183_DD_TS_PINS_CMD_SECONDARY_TS_ACTIVITY_MASK        0x01
   #define  Si2183_DD_TS_PINS_CMD_SECONDARY_TS_ACTIVITY_MIN         0
   #define  Si2183_DD_TS_PINS_CMD_SECONDARY_TS_ACTIVITY_MAX         1
    #define Si2183_DD_TS_PINS_CMD_SECONDARY_TS_ACTIVITY_CLEAR  1
    #define Si2183_DD_TS_PINS_CMD_SECONDARY_TS_ACTIVITY_RUN    0
   /* DD_TS_PINS command, SECONDARY_TS_DIR field definition (address 2,size 1, lsb 4, unsigned) */
   #define  Si2183_DD_TS_PINS_CMD_SECONDARY_TS_DIR_LSB         4
   #define  Si2183_DD_TS_PINS_CMD_SECONDARY_TS_DIR_MASK        0x01
   #define  Si2183_DD_TS_PINS_CMD_SECONDARY_TS_DIR_MIN         0
   #define  Si2183_DD_TS_PINS_CMD_SECONDARY_TS_DIR_MAX         1
    #define Si2183_DD_TS_PINS_CMD_SECONDARY_TS_DIR_INPUT   1
    #define Si2183_DD_TS_PINS_CMD_SECONDARY_TS_DIR_OUTPUT  0
   /* DD_TS_PINS command, DEMOD_ROLE field definition (address 3,size 2, lsb 0, unsigned) */
   #define  Si2183_DD_TS_PINS_CMD_DEMOD_ROLE_LSB         0
   #define  Si2183_DD_TS_PINS_CMD_DEMOD_ROLE_MASK        0x03
   #define  Si2183_DD_TS_PINS_CMD_DEMOD_ROLE_MIN         0
   #define  Si2183_DD_TS_PINS_CMD_DEMOD_ROLE_MAX         3
    #define Si2183_DD_TS_PINS_CMD_DEMOD_ROLE_CHANNEL_BONDING_OFF  0
    #define Si2183_DD_TS_PINS_CMD_DEMOD_ROLE_MASTER               1
    #define Si2183_DD_TS_PINS_CMD_DEMOD_ROLE_SLAVE                2
    #define Si2183_DD_TS_PINS_CMD_DEMOD_ROLE_SLAVE_BRIDGE         3
   /* DD_TS_PINS command, MASTER_FREQ field definition (address 4,size 32, lsb 0, unsigned) */
   #define  Si2183_DD_TS_PINS_CMD_MASTER_FREQ_LSB         0
   #define  Si2183_DD_TS_PINS_CMD_MASTER_FREQ_MASK        0xffffffff
   #define  Si2183_DD_TS_PINS_CMD_MASTER_FREQ_MIN         0
   #define  Si2183_DD_TS_PINS_CMD_MASTER_FREQ_MAX         4294967295
    #define Si2183_DD_TS_PINS_CMD_MASTER_FREQ_MASTER_FREQ_MIN  0
    #define Si2183_DD_TS_PINS_CMD_MASTER_FREQ_MASTER_FREQ_MAX  4294967295
   /* DD_TS_PINS command, PRIMARY_TS_MODE field definition (address 1, size 3, lsb 0, unsigned)*/
   #define  Si2183_DD_TS_PINS_RESPONSE_PRIMARY_TS_MODE_LSB         0
   #define  Si2183_DD_TS_PINS_RESPONSE_PRIMARY_TS_MODE_MASK        0x07
    #define Si2183_DD_TS_PINS_RESPONSE_PRIMARY_TS_MODE_DISABLED     1
    #define Si2183_DD_TS_PINS_RESPONSE_PRIMARY_TS_MODE_DRIVING_TS1  2
    #define Si2183_DD_TS_PINS_RESPONSE_PRIMARY_TS_MODE_DRIVING_TS2  3
   /* DD_TS_PINS command, PRIMARY_TS_ACTIVITY field definition (address 1, size 3, lsb 3, unsigned)*/
   #define  Si2183_DD_TS_PINS_RESPONSE_PRIMARY_TS_ACTIVITY_LSB         3
   #define  Si2183_DD_TS_PINS_RESPONSE_PRIMARY_TS_ACTIVITY_MASK        0x07
    #define Si2183_DD_TS_PINS_RESPONSE_PRIMARY_TS_ACTIVITY_ACTIVITY  3
    #define Si2183_DD_TS_PINS_RESPONSE_PRIMARY_TS_ACTIVITY_CONFLICT  2
    #define Si2183_DD_TS_PINS_RESPONSE_PRIMARY_TS_ACTIVITY_DRIVING   0
    #define Si2183_DD_TS_PINS_RESPONSE_PRIMARY_TS_ACTIVITY_QUIET     1
   /* DD_TS_PINS command, SECONDARY_TS_MODE field definition (address 2, size 3, lsb 0, unsigned)*/
   #define  Si2183_DD_TS_PINS_RESPONSE_SECONDARY_TS_MODE_LSB         0
   #define  Si2183_DD_TS_PINS_RESPONSE_SECONDARY_TS_MODE_MASK        0x07
    #define Si2183_DD_TS_PINS_RESPONSE_SECONDARY_TS_MODE_DISABLED     1
    #define Si2183_DD_TS_PINS_RESPONSE_SECONDARY_TS_MODE_DRIVING_TS1  2
    #define Si2183_DD_TS_PINS_RESPONSE_SECONDARY_TS_MODE_DRIVING_TS2  3
   /* DD_TS_PINS command, SECONDARY_TS_ACTIVITY field definition (address 2, size 3, lsb 3, unsigned)*/
   #define  Si2183_DD_TS_PINS_RESPONSE_SECONDARY_TS_ACTIVITY_LSB         3
   #define  Si2183_DD_TS_PINS_RESPONSE_SECONDARY_TS_ACTIVITY_MASK        0x07
    #define Si2183_DD_TS_PINS_RESPONSE_SECONDARY_TS_ACTIVITY_ACTIVITY  3
    #define Si2183_DD_TS_PINS_RESPONSE_SECONDARY_TS_ACTIVITY_CONFLICT  2
    #define Si2183_DD_TS_PINS_RESPONSE_SECONDARY_TS_ACTIVITY_DRIVING   0
    #define Si2183_DD_TS_PINS_RESPONSE_SECONDARY_TS_ACTIVITY_QUIET     1

#endif /* Si2183_DD_TS_PINS_CMD */

/* Si2183_DD_UNCOR command definition */
#define   Si2183_DD_UNCOR_CMD 0x84

#ifdef    Si2183_DD_UNCOR_CMD
  #define Si2183_DD_UNCOR_CMD_CODE 0x010084

    typedef struct { /* Si2183_DD_UNCOR_CMD_struct */
     unsigned char   rst;
   } Si2183_DD_UNCOR_CMD_struct;


    typedef struct { /* Si2183_DD_UNCOR_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   uncor_lsb;
      unsigned char   uncor_msb;
   }  Si2183_DD_UNCOR_CMD_REPLY_struct;

   /* DD_UNCOR command, RST field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2183_DD_UNCOR_CMD_RST_LSB         0
   #define  Si2183_DD_UNCOR_CMD_RST_MASK        0x01
   #define  Si2183_DD_UNCOR_CMD_RST_MIN         0
   #define  Si2183_DD_UNCOR_CMD_RST_MAX         1
    #define Si2183_DD_UNCOR_CMD_RST_CLEAR  1
    #define Si2183_DD_UNCOR_CMD_RST_RUN    0
   /* DD_UNCOR command, UNCOR_LSB field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2183_DD_UNCOR_RESPONSE_UNCOR_LSB_LSB         0
   #define  Si2183_DD_UNCOR_RESPONSE_UNCOR_LSB_MASK        0xff
   /* DD_UNCOR command, UNCOR_MSB field definition (address 2, size 8, lsb 0, unsigned)*/
   #define  Si2183_DD_UNCOR_RESPONSE_UNCOR_MSB_LSB         0
   #define  Si2183_DD_UNCOR_RESPONSE_UNCOR_MSB_MASK        0xff

#endif /* Si2183_DD_UNCOR_CMD */

/* Si2183_DEMOD_INFO command definition */
#define   Si2183_DEMOD_INFO_CMD 0xb7

#ifdef    Si2183_DEMOD_INFO_CMD
  #define Si2183_DEMOD_INFO_CMD_CODE 0x0100b7

    typedef struct { /* Si2183_DEMOD_INFO_CMD_struct */
         unsigned char   nothing;   } Si2183_DEMOD_INFO_CMD_struct;


    typedef struct { /* Si2183_DEMOD_INFO_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   reserved;
      unsigned int    div_a;
      unsigned int    div_b;
   }  Si2183_DEMOD_INFO_CMD_REPLY_struct;

   /* DEMOD_INFO command, RESERVED field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2183_DEMOD_INFO_RESPONSE_RESERVED_LSB         0
   #define  Si2183_DEMOD_INFO_RESPONSE_RESERVED_MASK        0xff
   /* DEMOD_INFO command, DIV_A field definition (address 2, size 16, lsb 0, unsigned)*/
   #define  Si2183_DEMOD_INFO_RESPONSE_DIV_A_LSB         0
   #define  Si2183_DEMOD_INFO_RESPONSE_DIV_A_MASK        0xffff
   /* DEMOD_INFO command, DIV_B field definition (address 4, size 16, lsb 0, unsigned)*/
   #define  Si2183_DEMOD_INFO_RESPONSE_DIV_B_LSB         0
   #define  Si2183_DEMOD_INFO_RESPONSE_DIV_B_MASK        0xffff

#endif /* Si2183_DEMOD_INFO_CMD */

/* Si2183_DOWNLOAD_DATASET_CONTINUE command definition */
#define   Si2183_DOWNLOAD_DATASET_CONTINUE_CMD 0xb9

#ifdef    Si2183_DOWNLOAD_DATASET_CONTINUE_CMD
  #define Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_CODE 0x0100b9

    typedef struct { /* Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_struct */
     unsigned char   data0;
     unsigned char   data1;
     unsigned char   data2;
     unsigned char   data3;
     unsigned char   data4;
     unsigned char   data5;
     unsigned char   data6;
   } Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_struct;


    typedef struct { /* Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
   }  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_REPLY_struct;

   /* DOWNLOAD_DATASET_CONTINUE command, DATA0 field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA0_LSB         0
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA0_MASK        0xff
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA0_MIN         0
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA0_MAX         255
    #define Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA0_DATA0_MIN  0
    #define Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA0_DATA0_MAX  255
   /* DOWNLOAD_DATASET_CONTINUE command, DATA1 field definition (address 2,size 8, lsb 0, unsigned) */
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA1_LSB         0
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA1_MASK        0xff
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA1_MIN         0
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA1_MAX         255
    #define Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA1_DATA1_MIN  0
    #define Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA1_DATA1_MAX  255
   /* DOWNLOAD_DATASET_CONTINUE command, DATA2 field definition (address 3,size 8, lsb 0, unsigned) */
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA2_LSB         0
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA2_MASK        0xff
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA2_MIN         0
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA2_MAX         255
    #define Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA2_DATA2_MIN  0
    #define Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA2_DATA2_MAX  255
   /* DOWNLOAD_DATASET_CONTINUE command, DATA3 field definition (address 4,size 8, lsb 0, unsigned) */
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA3_LSB         0
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA3_MASK        0xff
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA3_MIN         0
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA3_MAX         255
    #define Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA3_DATA3_MIN  0
    #define Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA3_DATA3_MAX  255
   /* DOWNLOAD_DATASET_CONTINUE command, DATA4 field definition (address 5,size 8, lsb 0, unsigned) */
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA4_LSB         0
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA4_MASK        0xff
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA4_MIN         0
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA4_MAX         255
    #define Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA4_DATA4_MIN  0
    #define Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA4_DATA4_MAX  255
   /* DOWNLOAD_DATASET_CONTINUE command, DATA5 field definition (address 6,size 8, lsb 0, unsigned) */
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA5_LSB         0
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA5_MASK        0xff
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA5_MIN         0
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA5_MAX         255
    #define Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA5_DATA5_MIN  0
    #define Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA5_DATA5_MAX  255
   /* DOWNLOAD_DATASET_CONTINUE command, DATA6 field definition (address 7,size 8, lsb 0, unsigned) */
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA6_LSB         0
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA6_MASK        0xff
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA6_MIN         0
   #define  Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA6_MAX         255
    #define Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA6_DATA6_MIN  0
    #define Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA6_DATA6_MAX  255
#endif /* Si2183_DOWNLOAD_DATASET_CONTINUE_CMD */

/* Si2183_DOWNLOAD_DATASET_START command definition */
#define   Si2183_DOWNLOAD_DATASET_START_CMD 0xb8

#ifdef    Si2183_DOWNLOAD_DATASET_START_CMD
  #define Si2183_DOWNLOAD_DATASET_START_CMD_CODE 0x0100b8

    typedef struct { /* Si2183_DOWNLOAD_DATASET_START_CMD_struct */
     unsigned char   dataset_id;
     unsigned char   dataset_checksum;
     unsigned char   data0;
     unsigned char   data1;
     unsigned char   data2;
     unsigned char   data3;
     unsigned char   data4;
   } Si2183_DOWNLOAD_DATASET_START_CMD_struct;


    typedef struct { /* Si2183_DOWNLOAD_DATASET_START_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
   }  Si2183_DOWNLOAD_DATASET_START_CMD_REPLY_struct;

   /* DOWNLOAD_DATASET_START command, DATASET_ID field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATASET_ID_LSB         0
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATASET_ID_MASK        0xff
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATASET_ID_MIN         0
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATASET_ID_MAX         0
    #define Si2183_DOWNLOAD_DATASET_START_CMD_DATASET_ID_RFU  0
   /* DOWNLOAD_DATASET_START command, DATASET_CHECKSUM field definition (address 2,size 8, lsb 0, unsigned) */
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATASET_CHECKSUM_LSB         0
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATASET_CHECKSUM_MASK        0xff
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATASET_CHECKSUM_MIN         0
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATASET_CHECKSUM_MAX         255
    #define Si2183_DOWNLOAD_DATASET_START_CMD_DATASET_CHECKSUM_DATASET_CHECKSUM_MIN  0
    #define Si2183_DOWNLOAD_DATASET_START_CMD_DATASET_CHECKSUM_DATASET_CHECKSUM_MAX  255
   /* DOWNLOAD_DATASET_START command, DATA0 field definition (address 3,size 8, lsb 0, unsigned) */
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATA0_LSB         0
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATA0_MASK        0xff
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATA0_MIN         0
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATA0_MAX         255
    #define Si2183_DOWNLOAD_DATASET_START_CMD_DATA0_DATA0_MIN  0
    #define Si2183_DOWNLOAD_DATASET_START_CMD_DATA0_DATA0_MAX  255
   /* DOWNLOAD_DATASET_START command, DATA1 field definition (address 4,size 8, lsb 0, unsigned) */
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATA1_LSB         0
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATA1_MASK        0xff
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATA1_MIN         0
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATA1_MAX         255
    #define Si2183_DOWNLOAD_DATASET_START_CMD_DATA1_DATA1_MIN  0
    #define Si2183_DOWNLOAD_DATASET_START_CMD_DATA1_DATA1_MAX  255
   /* DOWNLOAD_DATASET_START command, DATA2 field definition (address 5,size 8, lsb 0, unsigned) */
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATA2_LSB         0
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATA2_MASK        0xff
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATA2_MIN         0
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATA2_MAX         255
    #define Si2183_DOWNLOAD_DATASET_START_CMD_DATA2_DATA2_MIN  0
    #define Si2183_DOWNLOAD_DATASET_START_CMD_DATA2_DATA2_MAX  255
   /* DOWNLOAD_DATASET_START command, DATA3 field definition (address 6,size 8, lsb 0, unsigned) */
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATA3_LSB         0
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATA3_MASK        0xff
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATA3_MIN         0
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATA3_MAX         255
    #define Si2183_DOWNLOAD_DATASET_START_CMD_DATA3_DATA3_MIN  0
    #define Si2183_DOWNLOAD_DATASET_START_CMD_DATA3_DATA3_MAX  255
   /* DOWNLOAD_DATASET_START command, DATA4 field definition (address 7,size 8, lsb 0, unsigned) */
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATA4_LSB         0
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATA4_MASK        0xff
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATA4_MIN         0
   #define  Si2183_DOWNLOAD_DATASET_START_CMD_DATA4_MAX         255
    #define Si2183_DOWNLOAD_DATASET_START_CMD_DATA4_DATA4_MIN  0
    #define Si2183_DOWNLOAD_DATASET_START_CMD_DATA4_DATA4_MAX  255
#endif /* Si2183_DOWNLOAD_DATASET_START_CMD */

#ifdef    DEMOD_DVB_C2
/* Si2183_DVBC2_CTRL command definition */
#define   Si2183_DVBC2_CTRL_CMD 0x92

#ifdef    Si2183_DVBC2_CTRL_CMD
  #define Si2183_DVBC2_CTRL_CMD_CODE 0x010092

    typedef struct { /* Si2183_DVBC2_CTRL_CMD_struct */
     unsigned char   action;
     unsigned long   tuned_rf_freq;
   } Si2183_DVBC2_CTRL_CMD_struct;


    typedef struct { /* Si2183_DVBC2_CTRL_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
   }  Si2183_DVBC2_CTRL_CMD_REPLY_struct;

   /* DVBC2_CTRL command, ACTION field definition (address 1,size 4, lsb 0, unsigned) */
   #define  Si2183_DVBC2_CTRL_CMD_ACTION_LSB         0
   #define  Si2183_DVBC2_CTRL_CMD_ACTION_MASK        0x0f
   #define  Si2183_DVBC2_CTRL_CMD_ACTION_MIN         1
   #define  Si2183_DVBC2_CTRL_CMD_ACTION_MAX         3
    #define Si2183_DVBC2_CTRL_CMD_ACTION_ABORT   3
    #define Si2183_DVBC2_CTRL_CMD_ACTION_RESUME  2
    #define Si2183_DVBC2_CTRL_CMD_ACTION_START   1
   /* DVBC2_CTRL command, TUNED_RF_FREQ field definition (address 4,size 32, lsb 0, unsigned) */
   #define  Si2183_DVBC2_CTRL_CMD_TUNED_RF_FREQ_LSB         0
   #define  Si2183_DVBC2_CTRL_CMD_TUNED_RF_FREQ_MASK        0xffffffff
   #define  Si2183_DVBC2_CTRL_CMD_TUNED_RF_FREQ_MIN         0
   #define  Si2183_DVBC2_CTRL_CMD_TUNED_RF_FREQ_MAX         4294967295
    #define Si2183_DVBC2_CTRL_CMD_TUNED_RF_FREQ_TUNED_RF_FREQ_MIN  0
    #define Si2183_DVBC2_CTRL_CMD_TUNED_RF_FREQ_TUNED_RF_FREQ_MAX  4294967295
#endif /* Si2183_DVBC2_CTRL_CMD */

/* Si2183_DVBC2_DS_INFO command definition */
#define   Si2183_DVBC2_DS_INFO_CMD 0x95

#ifdef    Si2183_DVBC2_DS_INFO_CMD
  #define Si2183_DVBC2_DS_INFO_CMD_CODE 0x010095

    typedef struct { /* Si2183_DVBC2_DS_INFO_CMD_struct */
     unsigned char   ds_index_or_id;
     unsigned char   ds_select_index_or_id;
   } Si2183_DVBC2_DS_INFO_CMD_struct;


    typedef struct { /* Si2183_DVBC2_DS_INFO_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   ds_id;
      unsigned char   dslice_num_plp;
      unsigned char   reserved_2;
      unsigned long   dslice_tune_pos_hz;
   }  Si2183_DVBC2_DS_INFO_CMD_REPLY_struct;

   /* DVBC2_DS_INFO command, DS_INDEX_OR_ID field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_DVBC2_DS_INFO_CMD_DS_INDEX_OR_ID_LSB         0
   #define  Si2183_DVBC2_DS_INFO_CMD_DS_INDEX_OR_ID_MASK        0xff
   #define  Si2183_DVBC2_DS_INFO_CMD_DS_INDEX_OR_ID_MIN         0
   #define  Si2183_DVBC2_DS_INFO_CMD_DS_INDEX_OR_ID_MAX         255
   /* DVBC2_DS_INFO command, DS_SELECT_INDEX_OR_ID field definition (address 2,size 1, lsb 0, unsigned) */
   #define  Si2183_DVBC2_DS_INFO_CMD_DS_SELECT_INDEX_OR_ID_LSB         0
   #define  Si2183_DVBC2_DS_INFO_CMD_DS_SELECT_INDEX_OR_ID_MASK        0x01
   #define  Si2183_DVBC2_DS_INFO_CMD_DS_SELECT_INDEX_OR_ID_MIN         0
   #define  Si2183_DVBC2_DS_INFO_CMD_DS_SELECT_INDEX_OR_ID_MAX         1
    #define Si2183_DVBC2_DS_INFO_CMD_DS_SELECT_INDEX_OR_ID_ID     1
    #define Si2183_DVBC2_DS_INFO_CMD_DS_SELECT_INDEX_OR_ID_INDEX  0
   /* DVBC2_DS_INFO command, DS_ID field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBC2_DS_INFO_RESPONSE_DS_ID_LSB         0
   #define  Si2183_DVBC2_DS_INFO_RESPONSE_DS_ID_MASK        0xff
   /* DVBC2_DS_INFO command, DSLICE_NUM_PLP field definition (address 2, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBC2_DS_INFO_RESPONSE_DSLICE_NUM_PLP_LSB         0
   #define  Si2183_DVBC2_DS_INFO_RESPONSE_DSLICE_NUM_PLP_MASK        0xff
   /* DVBC2_DS_INFO command, RESERVED_2 field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBC2_DS_INFO_RESPONSE_RESERVED_2_LSB         0
   #define  Si2183_DVBC2_DS_INFO_RESPONSE_RESERVED_2_MASK        0xff
   /* DVBC2_DS_INFO command, DSLICE_TUNE_POS_HZ field definition (address 4, size 32, lsb 0, unsigned)*/
   #define  Si2183_DVBC2_DS_INFO_RESPONSE_DSLICE_TUNE_POS_HZ_LSB         0
   #define  Si2183_DVBC2_DS_INFO_RESPONSE_DSLICE_TUNE_POS_HZ_MASK        0xffffffff

#endif /* Si2183_DVBC2_DS_INFO_CMD */

/* Si2183_DVBC2_DS_PLP_SELECT command definition */
#define   Si2183_DVBC2_DS_PLP_SELECT_CMD 0x93

#ifdef    Si2183_DVBC2_DS_PLP_SELECT_CMD
  #define Si2183_DVBC2_DS_PLP_SELECT_CMD_CODE 0x010093

    typedef struct { /* Si2183_DVBC2_DS_PLP_SELECT_CMD_struct */
     unsigned char   plp_id;
     unsigned char   id_sel_mode;
     unsigned char   ds_id;
   } Si2183_DVBC2_DS_PLP_SELECT_CMD_struct;


    typedef struct { /* Si2183_DVBC2_DS_PLP_SELECT_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
   }  Si2183_DVBC2_DS_PLP_SELECT_CMD_REPLY_struct;

   /* DVBC2_DS_PLP_SELECT command, PLP_ID field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_DVBC2_DS_PLP_SELECT_CMD_PLP_ID_LSB         0
   #define  Si2183_DVBC2_DS_PLP_SELECT_CMD_PLP_ID_MASK        0xff
   #define  Si2183_DVBC2_DS_PLP_SELECT_CMD_PLP_ID_MIN         0
   #define  Si2183_DVBC2_DS_PLP_SELECT_CMD_PLP_ID_MAX         255
   /* DVBC2_DS_PLP_SELECT command, ID_SEL_MODE field definition (address 2,size 1, lsb 0, unsigned) */
   #define  Si2183_DVBC2_DS_PLP_SELECT_CMD_ID_SEL_MODE_LSB         0
   #define  Si2183_DVBC2_DS_PLP_SELECT_CMD_ID_SEL_MODE_MASK        0x01
   #define  Si2183_DVBC2_DS_PLP_SELECT_CMD_ID_SEL_MODE_MIN         0
   #define  Si2183_DVBC2_DS_PLP_SELECT_CMD_ID_SEL_MODE_MAX         1
    #define Si2183_DVBC2_DS_PLP_SELECT_CMD_ID_SEL_MODE_AUTO    0
    #define Si2183_DVBC2_DS_PLP_SELECT_CMD_ID_SEL_MODE_MANUAL  1
   /* DVBC2_DS_PLP_SELECT command, DS_ID field definition (address 3,size 8, lsb 0, unsigned) */
   #define  Si2183_DVBC2_DS_PLP_SELECT_CMD_DS_ID_LSB         0
   #define  Si2183_DVBC2_DS_PLP_SELECT_CMD_DS_ID_MASK        0xff
   #define  Si2183_DVBC2_DS_PLP_SELECT_CMD_DS_ID_MIN         0
   #define  Si2183_DVBC2_DS_PLP_SELECT_CMD_DS_ID_MAX         255
#endif /* Si2183_DVBC2_DS_PLP_SELECT_CMD */

/* Si2183_DVBC2_PLP_INFO command definition */
#define   Si2183_DVBC2_PLP_INFO_CMD 0x94

#ifdef    Si2183_DVBC2_PLP_INFO_CMD
  #define Si2183_DVBC2_PLP_INFO_CMD_CODE 0x010094

    typedef struct { /* Si2183_DVBC2_PLP_INFO_CMD_struct */
     unsigned char   plp_index;
     unsigned char   plp_info_ds_mode;
     unsigned char   ds_index;
   } Si2183_DVBC2_PLP_INFO_CMD_struct;


    typedef struct { /* Si2183_DVBC2_PLP_INFO_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   plp_id;
      unsigned char   plp_payload_type;
      unsigned char   plp_type;
      unsigned char   plp_bundled;
   }  Si2183_DVBC2_PLP_INFO_CMD_REPLY_struct;

   /* DVBC2_PLP_INFO command, PLP_INDEX field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_DVBC2_PLP_INFO_CMD_PLP_INDEX_LSB         0
   #define  Si2183_DVBC2_PLP_INFO_CMD_PLP_INDEX_MASK        0xff
   #define  Si2183_DVBC2_PLP_INFO_CMD_PLP_INDEX_MIN         0
   #define  Si2183_DVBC2_PLP_INFO_CMD_PLP_INDEX_MAX         255
   /* DVBC2_PLP_INFO command, PLP_INFO_DS_MODE field definition (address 2,size 1, lsb 0, unsigned) */
   #define  Si2183_DVBC2_PLP_INFO_CMD_PLP_INFO_DS_MODE_LSB         0
   #define  Si2183_DVBC2_PLP_INFO_CMD_PLP_INFO_DS_MODE_MASK        0x01
   #define  Si2183_DVBC2_PLP_INFO_CMD_PLP_INFO_DS_MODE_MIN         0
   #define  Si2183_DVBC2_PLP_INFO_CMD_PLP_INFO_DS_MODE_MAX         1
    #define Si2183_DVBC2_PLP_INFO_CMD_PLP_INFO_DS_MODE_ANY       1
    #define Si2183_DVBC2_PLP_INFO_CMD_PLP_INFO_DS_MODE_SELECTED  0
   /* DVBC2_PLP_INFO command, DS_INDEX field definition (address 3,size 8, lsb 0, unsigned) */
   #define  Si2183_DVBC2_PLP_INFO_CMD_DS_INDEX_LSB         0
   #define  Si2183_DVBC2_PLP_INFO_CMD_DS_INDEX_MASK        0xff
   #define  Si2183_DVBC2_PLP_INFO_CMD_DS_INDEX_MIN         0
   #define  Si2183_DVBC2_PLP_INFO_CMD_DS_INDEX_MAX         255
   /* DVBC2_PLP_INFO command, PLP_ID field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_ID_LSB         0
   #define  Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_ID_MASK        0xff
   /* DVBC2_PLP_INFO command, PLP_PAYLOAD_TYPE field definition (address 2, size 5, lsb 0, unsigned)*/
   #define  Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_PAYLOAD_TYPE_LSB         0
   #define  Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_PAYLOAD_TYPE_MASK        0x1f
    #define Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_PAYLOAD_TYPE_GCS   1
    #define Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_PAYLOAD_TYPE_GFPS  0
    #define Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_PAYLOAD_TYPE_GSE   2
    #define Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_PAYLOAD_TYPE_TS    3
   /* DVBC2_PLP_INFO command, PLP_TYPE field definition (address 2, size 2, lsb 5, unsigned)*/
   #define  Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_TYPE_LSB         5
   #define  Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_TYPE_MASK        0x03
    #define Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_TYPE_COMMON    0
    #define Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_TYPE_GROUPED   1
    #define Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_TYPE_NORMAL    2
    #define Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_TYPE_RESERVED  3
   /* DVBC2_PLP_INFO command, PLP_BUNDLED field definition (address 2, size 1, lsb 7, unsigned)*/
   #define  Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_BUNDLED_LSB         7
   #define  Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_BUNDLED_MASK        0x01
    #define Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_BUNDLED_BUNDLED      1
    #define Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_BUNDLED_NOT_BUNDLED  0

#endif /* Si2183_DVBC2_PLP_INFO_CMD */

/* Si2183_DVBC2_STATUS command definition */
#define   Si2183_DVBC2_STATUS_CMD 0x91

#ifdef    Si2183_DVBC2_STATUS_CMD
  #define Si2183_DVBC2_STATUS_CMD_CODE 0x010091

    typedef struct { /* Si2183_DVBC2_STATUS_CMD_struct */
     unsigned char   intack;
   } Si2183_DVBC2_STATUS_CMD_struct;


    typedef struct { /* Si2183_DVBC2_STATUS_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   pclint;
      unsigned char   dlint;
      unsigned char   berint;
      unsigned char   uncorint;
      unsigned char   notdvbc2int;
      unsigned char   reqint;
      unsigned char   ewbsint;
      unsigned char   ds_id;
      unsigned char   plp_id;
      unsigned long   rf_freq;
      unsigned char   pcl;
      unsigned char   dl;
      unsigned char   ber;
      unsigned char   uncor;
      unsigned char   notdvbc2;
      unsigned char   req;
      unsigned char   ewbs;
      unsigned char   cnr;
               int    afc_freq;
               int    timing_offset;
      unsigned char   dvbc2_status;
      unsigned char   constellation;
      unsigned char   sp_inv;
      unsigned char   code_rate;
      unsigned char   guard_int;
   }  Si2183_DVBC2_STATUS_CMD_REPLY_struct;

   /* DVBC2_STATUS command, INTACK field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2183_DVBC2_STATUS_CMD_INTACK_LSB         0
   #define  Si2183_DVBC2_STATUS_CMD_INTACK_MASK        0x01
   #define  Si2183_DVBC2_STATUS_CMD_INTACK_MIN         0
   #define  Si2183_DVBC2_STATUS_CMD_INTACK_MAX         1
    #define Si2183_DVBC2_STATUS_CMD_INTACK_CLEAR  1
    #define Si2183_DVBC2_STATUS_CMD_INTACK_OK     0
   /* DVBC2_STATUS command, PCLINT field definition (address 1, size 1, lsb 1, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_PCLINT_LSB         1
   #define  Si2183_DVBC2_STATUS_RESPONSE_PCLINT_MASK        0x01
    #define Si2183_DVBC2_STATUS_RESPONSE_PCLINT_CHANGED    1
    #define Si2183_DVBC2_STATUS_RESPONSE_PCLINT_NO_CHANGE  0
   /* DVBC2_STATUS command, DLINT field definition (address 1, size 1, lsb 2, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_DLINT_LSB         2
   #define  Si2183_DVBC2_STATUS_RESPONSE_DLINT_MASK        0x01
    #define Si2183_DVBC2_STATUS_RESPONSE_DLINT_CHANGED    1
    #define Si2183_DVBC2_STATUS_RESPONSE_DLINT_NO_CHANGE  0
   /* DVBC2_STATUS command, BERINT field definition (address 1, size 1, lsb 3, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_BERINT_LSB         3
   #define  Si2183_DVBC2_STATUS_RESPONSE_BERINT_MASK        0x01
    #define Si2183_DVBC2_STATUS_RESPONSE_BERINT_CHANGED    1
    #define Si2183_DVBC2_STATUS_RESPONSE_BERINT_NO_CHANGE  0
   /* DVBC2_STATUS command, UNCORINT field definition (address 1, size 1, lsb 4, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_UNCORINT_LSB         4
   #define  Si2183_DVBC2_STATUS_RESPONSE_UNCORINT_MASK        0x01
    #define Si2183_DVBC2_STATUS_RESPONSE_UNCORINT_CHANGED    1
    #define Si2183_DVBC2_STATUS_RESPONSE_UNCORINT_NO_CHANGE  0
   /* DVBC2_STATUS command, NOTDVBC2INT field definition (address 1, size 1, lsb 5, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_NOTDVBC2INT_LSB         5
   #define  Si2183_DVBC2_STATUS_RESPONSE_NOTDVBC2INT_MASK        0x01
    #define Si2183_DVBC2_STATUS_RESPONSE_NOTDVBC2INT_CHANGED    1
    #define Si2183_DVBC2_STATUS_RESPONSE_NOTDVBC2INT_NO_CHANGE  0
   /* DVBC2_STATUS command, REQINT field definition (address 1, size 1, lsb 6, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_REQINT_LSB         6
   #define  Si2183_DVBC2_STATUS_RESPONSE_REQINT_MASK        0x01
    #define Si2183_DVBC2_STATUS_RESPONSE_REQINT_CHANGED    1
    #define Si2183_DVBC2_STATUS_RESPONSE_REQINT_NO_CHANGE  0
   /* DVBC2_STATUS command, EWBSINT field definition (address 1, size 1, lsb 7, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_EWBSINT_LSB         7
   #define  Si2183_DVBC2_STATUS_RESPONSE_EWBSINT_MASK        0x01
    #define Si2183_DVBC2_STATUS_RESPONSE_EWBSINT_CHANGED    1
    #define Si2183_DVBC2_STATUS_RESPONSE_EWBSINT_NO_CHANGE  0
   /* DVBC2_STATUS command, DS_ID field definition (address 10, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_DS_ID_LSB         0
   #define  Si2183_DVBC2_STATUS_RESPONSE_DS_ID_MASK        0xff
   /* DVBC2_STATUS command, PLP_ID field definition (address 11, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_PLP_ID_LSB         0
   #define  Si2183_DVBC2_STATUS_RESPONSE_PLP_ID_MASK        0xff
   /* DVBC2_STATUS command, RF_FREQ field definition (address 12, size 32, lsb 0, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_RF_FREQ_LSB         0
   #define  Si2183_DVBC2_STATUS_RESPONSE_RF_FREQ_MASK        0xffffffff
   /* DVBC2_STATUS command, PCL field definition (address 2, size 1, lsb 1, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_PCL_LSB         1
   #define  Si2183_DVBC2_STATUS_RESPONSE_PCL_MASK        0x01
    #define Si2183_DVBC2_STATUS_RESPONSE_PCL_LOCKED   1
    #define Si2183_DVBC2_STATUS_RESPONSE_PCL_NO_LOCK  0
   /* DVBC2_STATUS command, DL field definition (address 2, size 1, lsb 2, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_DL_LSB         2
   #define  Si2183_DVBC2_STATUS_RESPONSE_DL_MASK        0x01
    #define Si2183_DVBC2_STATUS_RESPONSE_DL_LOCKED   1
    #define Si2183_DVBC2_STATUS_RESPONSE_DL_NO_LOCK  0
   /* DVBC2_STATUS command, BER field definition (address 2, size 1, lsb 3, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_BER_LSB         3
   #define  Si2183_DVBC2_STATUS_RESPONSE_BER_MASK        0x01
    #define Si2183_DVBC2_STATUS_RESPONSE_BER_BER_ABOVE  1
    #define Si2183_DVBC2_STATUS_RESPONSE_BER_BER_BELOW  0
   /* DVBC2_STATUS command, UNCOR field definition (address 2, size 1, lsb 4, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_UNCOR_LSB         4
   #define  Si2183_DVBC2_STATUS_RESPONSE_UNCOR_MASK        0x01
    #define Si2183_DVBC2_STATUS_RESPONSE_UNCOR_NO_UNCOR_FOUND  0
    #define Si2183_DVBC2_STATUS_RESPONSE_UNCOR_UNCOR_FOUND     1
   /* DVBC2_STATUS command, NOTDVBC2 field definition (address 2, size 1, lsb 5, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_NOTDVBC2_LSB         5
   #define  Si2183_DVBC2_STATUS_RESPONSE_NOTDVBC2_MASK        0x01
    #define Si2183_DVBC2_STATUS_RESPONSE_NOTDVBC2_DVBC2      0
    #define Si2183_DVBC2_STATUS_RESPONSE_NOTDVBC2_NOT_DVBC2  1
   /* DVBC2_STATUS command, REQ field definition (address 2, size 1, lsb 6, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_REQ_LSB         6
   #define  Si2183_DVBC2_STATUS_RESPONSE_REQ_MASK        0x01
    #define Si2183_DVBC2_STATUS_RESPONSE_REQ_NO_REQUEST  0
    #define Si2183_DVBC2_STATUS_RESPONSE_REQ_REQUEST     1
   /* DVBC2_STATUS command, EWBS field definition (address 2, size 1, lsb 7, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_EWBS_LSB         7
   #define  Si2183_DVBC2_STATUS_RESPONSE_EWBS_MASK        0x01
    #define Si2183_DVBC2_STATUS_RESPONSE_EWBS_NORMAL   0
    #define Si2183_DVBC2_STATUS_RESPONSE_EWBS_WARNING  1
   /* DVBC2_STATUS command, CNR field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_CNR_LSB         0
   #define  Si2183_DVBC2_STATUS_RESPONSE_CNR_MASK        0xff
   /* DVBC2_STATUS command, AFC_FREQ field definition (address 4, size 16, lsb 0, signed)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_AFC_FREQ_LSB         0
   #define  Si2183_DVBC2_STATUS_RESPONSE_AFC_FREQ_MASK        0xffff
   #define  Si2183_DVBC2_STATUS_RESPONSE_AFC_FREQ_SHIFT       16
   /* DVBC2_STATUS command, TIMING_OFFSET field definition (address 6, size 16, lsb 0, signed)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_TIMING_OFFSET_LSB         0
   #define  Si2183_DVBC2_STATUS_RESPONSE_TIMING_OFFSET_MASK        0xffff
   #define  Si2183_DVBC2_STATUS_RESPONSE_TIMING_OFFSET_SHIFT       16
   /* DVBC2_STATUS command, DVBC2_STATUS field definition (address 8, size 3, lsb 0, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_DVBC2_STATUS_LSB         0
   #define  Si2183_DVBC2_STATUS_RESPONSE_DVBC2_STATUS_MASK        0x07
    #define Si2183_DVBC2_STATUS_RESPONSE_DVBC2_STATUS_IDLE          0
    #define Si2183_DVBC2_STATUS_RESPONSE_DVBC2_STATUS_INVALID_DS    3
    #define Si2183_DVBC2_STATUS_RESPONSE_DVBC2_STATUS_READY         2
    #define Si2183_DVBC2_STATUS_RESPONSE_DVBC2_STATUS_SEARCHING     1
    #define Si2183_DVBC2_STATUS_RESPONSE_DVBC2_STATUS_TUNE_REQUEST  4
   /* DVBC2_STATUS command, CONSTELLATION field definition (address 8, size 4, lsb 3, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_CONSTELLATION_LSB         3
   #define  Si2183_DVBC2_STATUS_RESPONSE_CONSTELLATION_MASK        0x0f
    #define Si2183_DVBC2_STATUS_RESPONSE_CONSTELLATION_QAM1024  13
    #define Si2183_DVBC2_STATUS_RESPONSE_CONSTELLATION_QAM16    7
    #define Si2183_DVBC2_STATUS_RESPONSE_CONSTELLATION_QAM256   11
    #define Si2183_DVBC2_STATUS_RESPONSE_CONSTELLATION_QAM4096  15
    #define Si2183_DVBC2_STATUS_RESPONSE_CONSTELLATION_QAM64    9
   /* DVBC2_STATUS command, SP_INV field definition (address 8, size 1, lsb 7, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_SP_INV_LSB         7
   #define  Si2183_DVBC2_STATUS_RESPONSE_SP_INV_MASK        0x01
    #define Si2183_DVBC2_STATUS_RESPONSE_SP_INV_INVERTED  1
    #define Si2183_DVBC2_STATUS_RESPONSE_SP_INV_NORMAL    0
   /* DVBC2_STATUS command, CODE_RATE field definition (address 9, size 4, lsb 0, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_CODE_RATE_LSB         0
   #define  Si2183_DVBC2_STATUS_RESPONSE_CODE_RATE_MASK        0x0f
    #define Si2183_DVBC2_STATUS_RESPONSE_CODE_RATE_2_3   2
    #define Si2183_DVBC2_STATUS_RESPONSE_CODE_RATE_3_4   3
    #define Si2183_DVBC2_STATUS_RESPONSE_CODE_RATE_4_5   4
    #define Si2183_DVBC2_STATUS_RESPONSE_CODE_RATE_5_6   5
    #define Si2183_DVBC2_STATUS_RESPONSE_CODE_RATE_8_9   8
    #define Si2183_DVBC2_STATUS_RESPONSE_CODE_RATE_9_10  9
   /* DVBC2_STATUS command, GUARD_INT field definition (address 9, size 3, lsb 4, unsigned)*/
   #define  Si2183_DVBC2_STATUS_RESPONSE_GUARD_INT_LSB         4
   #define  Si2183_DVBC2_STATUS_RESPONSE_GUARD_INT_MASK        0x07
    #define Si2183_DVBC2_STATUS_RESPONSE_GUARD_INT_1_128  5
    #define Si2183_DVBC2_STATUS_RESPONSE_GUARD_INT_1_64   0

#endif /* Si2183_DVBC2_STATUS_CMD */

/* Si2183_DVBC2_SYS_INFO command definition */
#define   Si2183_DVBC2_SYS_INFO_CMD 0x96

#ifdef    Si2183_DVBC2_SYS_INFO_CMD
  #define Si2183_DVBC2_SYS_INFO_CMD_CODE 0x010096

    typedef struct { /* Si2183_DVBC2_SYS_INFO_CMD_struct */
         unsigned char   nothing;   } Si2183_DVBC2_SYS_INFO_CMD_struct;


    typedef struct { /* Si2183_DVBC2_SYS_INFO_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   num_dslice;
      unsigned int    c2_system_id;
      unsigned   char   reserved_4_lsb;
      unsigned   char   reserved_4_msb;
      unsigned   char   c2_version;
      unsigned   char   ews;
      unsigned int    network_id;
      unsigned long   c2_bandwidth_hz;
      unsigned long   start_frequency_hz;
   }  Si2183_DVBC2_SYS_INFO_CMD_REPLY_struct;

   /* DVBC2_SYS_INFO command, NUM_DSLICE field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBC2_SYS_INFO_RESPONSE_NUM_DSLICE_LSB         0
   #define  Si2183_DVBC2_SYS_INFO_RESPONSE_NUM_DSLICE_MASK        0xff
   /* DVBC2_SYS_INFO command, C2_SYSTEM_ID field definition (address 12, size 16, lsb 0, unsigned)*/
   #define  Si2183_DVBC2_SYS_INFO_RESPONSE_C2_SYSTEM_ID_LSB         0
   #define  Si2183_DVBC2_SYS_INFO_RESPONSE_C2_SYSTEM_ID_MASK        0xffff
   /* DVBC2_SYS_INFO command, RESERVED_4_LSB field definition (address 14, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBC2_SYS_INFO_RESPONSE_RESERVED_4_LSB_LSB         0
   #define  Si2183_DVBC2_SYS_INFO_RESPONSE_RESERVED_4_LSB_MASK        0xff
   /* DVBC2_SYS_INFO command, RESERVED_4_MSB field definition (address 15, size 3, lsb 0, unsigned)*/
   #define  Si2183_DVBC2_SYS_INFO_RESPONSE_RESERVED_4_MSB_LSB         0
   #define  Si2183_DVBC2_SYS_INFO_RESPONSE_RESERVED_4_MSB_MASK        0x07
   /* DVBC2_SYS_INFO command, C2_VERSION field definition (address 15, size 4, lsb 3, unsigned)*/
   #define  Si2183_DVBC2_SYS_INFO_RESPONSE_C2_VERSION_LSB         3
   #define  Si2183_DVBC2_SYS_INFO_RESPONSE_C2_VERSION_MASK        0x0f
    #define Si2183_DVBC2_SYS_INFO_RESPONSE_C2_VERSION_V1_2_1  0
    #define Si2183_DVBC2_SYS_INFO_RESPONSE_C2_VERSION_V1_3_1  1
   /* DVBC2_SYS_INFO command, EWS field definition (address 15, size 1, lsb 7, unsigned)*/
   #define  Si2183_DVBC2_SYS_INFO_RESPONSE_EWS_LSB         7
   #define  Si2183_DVBC2_SYS_INFO_RESPONSE_EWS_MASK        0x01
   /* DVBC2_SYS_INFO command, NETWORK_ID field definition (address 2, size 16, lsb 0, unsigned)*/
   #define  Si2183_DVBC2_SYS_INFO_RESPONSE_NETWORK_ID_LSB         0
   #define  Si2183_DVBC2_SYS_INFO_RESPONSE_NETWORK_ID_MASK        0xffff
   /* DVBC2_SYS_INFO command, C2_BANDWIDTH_HZ field definition (address 4, size 32, lsb 0, unsigned)*/
   #define  Si2183_DVBC2_SYS_INFO_RESPONSE_C2_BANDWIDTH_HZ_LSB         0
   #define  Si2183_DVBC2_SYS_INFO_RESPONSE_C2_BANDWIDTH_HZ_MASK        0xffffffff
   /* DVBC2_SYS_INFO command, START_FREQUENCY_HZ field definition (address 8, size 32, lsb 0, unsigned)*/
   #define  Si2183_DVBC2_SYS_INFO_RESPONSE_START_FREQUENCY_HZ_LSB         0
   #define  Si2183_DVBC2_SYS_INFO_RESPONSE_START_FREQUENCY_HZ_MASK        0xffffffff

#endif /* Si2183_DVBC2_SYS_INFO_CMD */

#endif /* DEMOD_DVB_C2 */

#ifdef    DEMOD_DVB_C
/* Si2183_DVBC_STATUS command definition */
#define   Si2183_DVBC_STATUS_CMD 0x90

#ifdef    Si2183_DVBC_STATUS_CMD
  #define Si2183_DVBC_STATUS_CMD_CODE 0x010090

    typedef struct { /* Si2183_DVBC_STATUS_CMD_struct */
     unsigned char   intack;
   } Si2183_DVBC_STATUS_CMD_struct;


    typedef struct { /* Si2183_DVBC_STATUS_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   pclint;
      unsigned char   dlint;
      unsigned char   berint;
      unsigned char   uncorint;
      unsigned char   notdvbcint;
      unsigned char   pcl;
      unsigned char   dl;
      unsigned char   ber;
      unsigned char   uncor;
      unsigned char   notdvbc;
      unsigned char   cnr;
               int    afc_freq;
               int    timing_offset;
      unsigned char   constellation;
      unsigned char   sp_inv;
   }  Si2183_DVBC_STATUS_CMD_REPLY_struct;

   /* DVBC_STATUS command, INTACK field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2183_DVBC_STATUS_CMD_INTACK_LSB         0
   #define  Si2183_DVBC_STATUS_CMD_INTACK_MASK        0x01
   #define  Si2183_DVBC_STATUS_CMD_INTACK_MIN         0
   #define  Si2183_DVBC_STATUS_CMD_INTACK_MAX         1
    #define Si2183_DVBC_STATUS_CMD_INTACK_CLEAR  1
    #define Si2183_DVBC_STATUS_CMD_INTACK_OK     0
   /* DVBC_STATUS command, PCLINT field definition (address 1, size 1, lsb 1, unsigned)*/
   #define  Si2183_DVBC_STATUS_RESPONSE_PCLINT_LSB         1
   #define  Si2183_DVBC_STATUS_RESPONSE_PCLINT_MASK        0x01
    #define Si2183_DVBC_STATUS_RESPONSE_PCLINT_CHANGED    1
    #define Si2183_DVBC_STATUS_RESPONSE_PCLINT_NO_CHANGE  0
   /* DVBC_STATUS command, DLINT field definition (address 1, size 1, lsb 2, unsigned)*/
   #define  Si2183_DVBC_STATUS_RESPONSE_DLINT_LSB         2
   #define  Si2183_DVBC_STATUS_RESPONSE_DLINT_MASK        0x01
    #define Si2183_DVBC_STATUS_RESPONSE_DLINT_CHANGED    1
    #define Si2183_DVBC_STATUS_RESPONSE_DLINT_NO_CHANGE  0
   /* DVBC_STATUS command, BERINT field definition (address 1, size 1, lsb 3, unsigned)*/
   #define  Si2183_DVBC_STATUS_RESPONSE_BERINT_LSB         3
   #define  Si2183_DVBC_STATUS_RESPONSE_BERINT_MASK        0x01
    #define Si2183_DVBC_STATUS_RESPONSE_BERINT_CHANGED    1
    #define Si2183_DVBC_STATUS_RESPONSE_BERINT_NO_CHANGE  0
   /* DVBC_STATUS command, UNCORINT field definition (address 1, size 1, lsb 4, unsigned)*/
   #define  Si2183_DVBC_STATUS_RESPONSE_UNCORINT_LSB         4
   #define  Si2183_DVBC_STATUS_RESPONSE_UNCORINT_MASK        0x01
    #define Si2183_DVBC_STATUS_RESPONSE_UNCORINT_CHANGED    1
    #define Si2183_DVBC_STATUS_RESPONSE_UNCORINT_NO_CHANGE  0
   /* DVBC_STATUS command, NOTDVBCINT field definition (address 1, size 1, lsb 5, unsigned)*/
   #define  Si2183_DVBC_STATUS_RESPONSE_NOTDVBCINT_LSB         5
   #define  Si2183_DVBC_STATUS_RESPONSE_NOTDVBCINT_MASK        0x01
    #define Si2183_DVBC_STATUS_RESPONSE_NOTDVBCINT_CHANGED    1
    #define Si2183_DVBC_STATUS_RESPONSE_NOTDVBCINT_NO_CHANGE  0
   /* DVBC_STATUS command, PCL field definition (address 2, size 1, lsb 1, unsigned)*/
   #define  Si2183_DVBC_STATUS_RESPONSE_PCL_LSB         1
   #define  Si2183_DVBC_STATUS_RESPONSE_PCL_MASK        0x01
    #define Si2183_DVBC_STATUS_RESPONSE_PCL_LOCKED   1
    #define Si2183_DVBC_STATUS_RESPONSE_PCL_NO_LOCK  0
   /* DVBC_STATUS command, DL field definition (address 2, size 1, lsb 2, unsigned)*/
   #define  Si2183_DVBC_STATUS_RESPONSE_DL_LSB         2
   #define  Si2183_DVBC_STATUS_RESPONSE_DL_MASK        0x01
    #define Si2183_DVBC_STATUS_RESPONSE_DL_LOCKED   1
    #define Si2183_DVBC_STATUS_RESPONSE_DL_NO_LOCK  0
   /* DVBC_STATUS command, BER field definition (address 2, size 1, lsb 3, unsigned)*/
   #define  Si2183_DVBC_STATUS_RESPONSE_BER_LSB         3
   #define  Si2183_DVBC_STATUS_RESPONSE_BER_MASK        0x01
    #define Si2183_DVBC_STATUS_RESPONSE_BER_BER_ABOVE  1
    #define Si2183_DVBC_STATUS_RESPONSE_BER_BER_BELOW  0
   /* DVBC_STATUS command, UNCOR field definition (address 2, size 1, lsb 4, unsigned)*/
   #define  Si2183_DVBC_STATUS_RESPONSE_UNCOR_LSB         4
   #define  Si2183_DVBC_STATUS_RESPONSE_UNCOR_MASK        0x01
    #define Si2183_DVBC_STATUS_RESPONSE_UNCOR_NO_UNCOR_FOUND  0
    #define Si2183_DVBC_STATUS_RESPONSE_UNCOR_UNCOR_FOUND     1
   /* DVBC_STATUS command, NOTDVBC field definition (address 2, size 1, lsb 5, unsigned)*/
   #define  Si2183_DVBC_STATUS_RESPONSE_NOTDVBC_LSB         5
   #define  Si2183_DVBC_STATUS_RESPONSE_NOTDVBC_MASK        0x01
   /* DVBC_STATUS command, CNR field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBC_STATUS_RESPONSE_CNR_LSB         0
   #define  Si2183_DVBC_STATUS_RESPONSE_CNR_MASK        0xff
   /* DVBC_STATUS command, AFC_FREQ field definition (address 4, size 16, lsb 0, signed)*/
   #define  Si2183_DVBC_STATUS_RESPONSE_AFC_FREQ_LSB         0
   #define  Si2183_DVBC_STATUS_RESPONSE_AFC_FREQ_MASK        0xffff
   #define  Si2183_DVBC_STATUS_RESPONSE_AFC_FREQ_SHIFT       16
   /* DVBC_STATUS command, TIMING_OFFSET field definition (address 6, size 16, lsb 0, signed)*/
   #define  Si2183_DVBC_STATUS_RESPONSE_TIMING_OFFSET_LSB         0
   #define  Si2183_DVBC_STATUS_RESPONSE_TIMING_OFFSET_MASK        0xffff
   #define  Si2183_DVBC_STATUS_RESPONSE_TIMING_OFFSET_SHIFT       16
   /* DVBC_STATUS command, CONSTELLATION field definition (address 8, size 6, lsb 0, unsigned)*/
   #define  Si2183_DVBC_STATUS_RESPONSE_CONSTELLATION_LSB         0
   #define  Si2183_DVBC_STATUS_RESPONSE_CONSTELLATION_MASK        0x3f
    #define Si2183_DVBC_STATUS_RESPONSE_CONSTELLATION_QAM128  10
    #define Si2183_DVBC_STATUS_RESPONSE_CONSTELLATION_QAM16   7
    #define Si2183_DVBC_STATUS_RESPONSE_CONSTELLATION_QAM256  11
    #define Si2183_DVBC_STATUS_RESPONSE_CONSTELLATION_QAM32   8
    #define Si2183_DVBC_STATUS_RESPONSE_CONSTELLATION_QAM64   9
   /* DVBC_STATUS command, SP_INV field definition (address 8, size 1, lsb 6, unsigned)*/
   #define  Si2183_DVBC_STATUS_RESPONSE_SP_INV_LSB         6
   #define  Si2183_DVBC_STATUS_RESPONSE_SP_INV_MASK        0x01
    #define Si2183_DVBC_STATUS_RESPONSE_SP_INV_INVERTED  1
    #define Si2183_DVBC_STATUS_RESPONSE_SP_INV_NORMAL    0

#endif /* Si2183_DVBC_STATUS_CMD */

#endif /* DEMOD_DVB_C */

#ifdef    DEMOD_DVB_S_S2_DSS
/* Si2183_DVBS2_PLS_INIT command definition */
#define   Si2183_DVBS2_PLS_INIT_CMD 0x73

#ifdef    Si2183_DVBS2_PLS_INIT_CMD
  #define Si2183_DVBS2_PLS_INIT_CMD_CODE 0x010073

    typedef struct { /* Si2183_DVBS2_PLS_INIT_CMD_struct */
     unsigned char   pls_detection_mode;
     unsigned long   pls;
   } Si2183_DVBS2_PLS_INIT_CMD_struct;


    typedef struct { /* Si2183_DVBS2_PLS_INIT_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
   }  Si2183_DVBS2_PLS_INIT_CMD_REPLY_struct;

   /* DVBS2_PLS_INIT command, PLS_DETECTION_MODE field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2183_DVBS2_PLS_INIT_CMD_PLS_DETECTION_MODE_LSB         0
   #define  Si2183_DVBS2_PLS_INIT_CMD_PLS_DETECTION_MODE_MASK        0x01
   #define  Si2183_DVBS2_PLS_INIT_CMD_PLS_DETECTION_MODE_MIN         0
   #define  Si2183_DVBS2_PLS_INIT_CMD_PLS_DETECTION_MODE_MAX         1
    #define Si2183_DVBS2_PLS_INIT_CMD_PLS_DETECTION_MODE_AUTO    0
    #define Si2183_DVBS2_PLS_INIT_CMD_PLS_DETECTION_MODE_MANUAL  1
   /* DVBS2_PLS_INIT command, PLS field definition (address 4,size 32, lsb 0, unsigned) */
   #define  Si2183_DVBS2_PLS_INIT_CMD_PLS_LSB         0
   #define  Si2183_DVBS2_PLS_INIT_CMD_PLS_MASK        0xffffffff
   #define  Si2183_DVBS2_PLS_INIT_CMD_PLS_MIN         0
   #define  Si2183_DVBS2_PLS_INIT_CMD_PLS_MAX         262143
    #define Si2183_DVBS2_PLS_INIT_CMD_PLS_PLS_MIN  0
    #define Si2183_DVBS2_PLS_INIT_CMD_PLS_PLS_MAX  262143
#endif /* Si2183_DVBS2_PLS_INIT_CMD */

/* Si2183_DVBS2_STATUS command definition */
#define   Si2183_DVBS2_STATUS_CMD 0x70

#ifdef    Si2183_DVBS2_STATUS_CMD
  #define Si2183_DVBS2_STATUS_CMD_CODE 0x010070

    typedef struct { /* Si2183_DVBS2_STATUS_CMD_struct */
     unsigned char   intack;
   } Si2183_DVBS2_STATUS_CMD_struct;


    typedef struct { /* Si2183_DVBS2_STATUS_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   pclint;
      unsigned char   dlint;
      unsigned char   berint;
      unsigned char   uncorint;
      unsigned char   roll_off;
      unsigned char   ccm_vcm;
      unsigned char   sis_mis;
      unsigned char   stream_type;
      unsigned char   num_is;
      unsigned char   isi_id;
      unsigned char   pcl;
      unsigned char   dl;
      unsigned char   ber;
      unsigned char   uncor;
      unsigned char   cnr;
               int    afc_freq;
               int    timing_offset;
      unsigned char   constellation;
      unsigned char   sp_inv;
      unsigned char   pilots;
      unsigned char   code_rate;
   }  Si2183_DVBS2_STATUS_CMD_REPLY_struct;

   /* DVBS2_STATUS command, INTACK field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2183_DVBS2_STATUS_CMD_INTACK_LSB         0
   #define  Si2183_DVBS2_STATUS_CMD_INTACK_MASK        0x01
   #define  Si2183_DVBS2_STATUS_CMD_INTACK_MIN         0
   #define  Si2183_DVBS2_STATUS_CMD_INTACK_MAX         1
    #define Si2183_DVBS2_STATUS_CMD_INTACK_CLEAR  1
    #define Si2183_DVBS2_STATUS_CMD_INTACK_OK     0
   /* DVBS2_STATUS command, PCLINT field definition (address 1, size 1, lsb 1, unsigned)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_PCLINT_LSB         1
   #define  Si2183_DVBS2_STATUS_RESPONSE_PCLINT_MASK        0x01
    #define Si2183_DVBS2_STATUS_RESPONSE_PCLINT_CHANGED    1
    #define Si2183_DVBS2_STATUS_RESPONSE_PCLINT_NO_CHANGE  0
   /* DVBS2_STATUS command, DLINT field definition (address 1, size 1, lsb 2, unsigned)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_DLINT_LSB         2
   #define  Si2183_DVBS2_STATUS_RESPONSE_DLINT_MASK        0x01
    #define Si2183_DVBS2_STATUS_RESPONSE_DLINT_CHANGED    1
    #define Si2183_DVBS2_STATUS_RESPONSE_DLINT_NO_CHANGE  0
   /* DVBS2_STATUS command, BERINT field definition (address 1, size 1, lsb 3, unsigned)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_BERINT_LSB         3
   #define  Si2183_DVBS2_STATUS_RESPONSE_BERINT_MASK        0x01
    #define Si2183_DVBS2_STATUS_RESPONSE_BERINT_CHANGED    1
    #define Si2183_DVBS2_STATUS_RESPONSE_BERINT_NO_CHANGE  0
   /* DVBS2_STATUS command, UNCORINT field definition (address 1, size 1, lsb 4, unsigned)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_UNCORINT_LSB         4
   #define  Si2183_DVBS2_STATUS_RESPONSE_UNCORINT_MASK        0x01
    #define Si2183_DVBS2_STATUS_RESPONSE_UNCORINT_CHANGED    1
    #define Si2183_DVBS2_STATUS_RESPONSE_UNCORINT_NO_CHANGE  0
   /* DVBS2_STATUS command, ROLL_OFF field definition (address 10, size 3, lsb 0, unsigned)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_ROLL_OFF_LSB         0
   #define  Si2183_DVBS2_STATUS_RESPONSE_ROLL_OFF_MASK        0x07
    #define Si2183_DVBS2_STATUS_RESPONSE_ROLL_OFF_0_05  6
    #define Si2183_DVBS2_STATUS_RESPONSE_ROLL_OFF_0_10  5
    #define Si2183_DVBS2_STATUS_RESPONSE_ROLL_OFF_0_15  4
    #define Si2183_DVBS2_STATUS_RESPONSE_ROLL_OFF_0_20  2
    #define Si2183_DVBS2_STATUS_RESPONSE_ROLL_OFF_0_25  1
    #define Si2183_DVBS2_STATUS_RESPONSE_ROLL_OFF_0_35  0
    #define Si2183_DVBS2_STATUS_RESPONSE_ROLL_OFF_N_A   3
   /* DVBS2_STATUS command, CCM_VCM field definition (address 10, size 1, lsb 3, unsigned)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_CCM_VCM_LSB         3
   #define  Si2183_DVBS2_STATUS_RESPONSE_CCM_VCM_MASK        0x01
    #define Si2183_DVBS2_STATUS_RESPONSE_CCM_VCM_CCM  1
    #define Si2183_DVBS2_STATUS_RESPONSE_CCM_VCM_VCM  0
   /* DVBS2_STATUS command, SIS_MIS field definition (address 10, size 1, lsb 4, unsigned)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_SIS_MIS_LSB         4
   #define  Si2183_DVBS2_STATUS_RESPONSE_SIS_MIS_MASK        0x01
    #define Si2183_DVBS2_STATUS_RESPONSE_SIS_MIS_MIS  0
    #define Si2183_DVBS2_STATUS_RESPONSE_SIS_MIS_SIS  1
   /* DVBS2_STATUS command, STREAM_TYPE field definition (address 10, size 3, lsb 5, unsigned)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_STREAM_TYPE_LSB         5
   #define  Si2183_DVBS2_STATUS_RESPONSE_STREAM_TYPE_MASK        0x07
    #define Si2183_DVBS2_STATUS_RESPONSE_STREAM_TYPE_GCS      1
    #define Si2183_DVBS2_STATUS_RESPONSE_STREAM_TYPE_GFPS     0
    #define Si2183_DVBS2_STATUS_RESPONSE_STREAM_TYPE_GSE      2
    #define Si2183_DVBS2_STATUS_RESPONSE_STREAM_TYPE_TS       3
    #define Si2183_DVBS2_STATUS_RESPONSE_STREAM_TYPE_GSE_LITE 4
   /* DVBS2_STATUS command, NUM_IS field definition (address 11, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_NUM_IS_LSB         0
   #define  Si2183_DVBS2_STATUS_RESPONSE_NUM_IS_MASK        0xff
   /* DVBS2_STATUS command, ISI_ID field definition (address 12, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_ISI_ID_LSB         0
   #define  Si2183_DVBS2_STATUS_RESPONSE_ISI_ID_MASK        0xff
   /* DVBS2_STATUS command, PCL field definition (address 2, size 1, lsb 1, unsigned)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_PCL_LSB         1
   #define  Si2183_DVBS2_STATUS_RESPONSE_PCL_MASK        0x01
    #define Si2183_DVBS2_STATUS_RESPONSE_PCL_LOCKED   1
    #define Si2183_DVBS2_STATUS_RESPONSE_PCL_NO_LOCK  0
   /* DVBS2_STATUS command, DL field definition (address 2, size 1, lsb 2, unsigned)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_DL_LSB         2
   #define  Si2183_DVBS2_STATUS_RESPONSE_DL_MASK        0x01
    #define Si2183_DVBS2_STATUS_RESPONSE_DL_LOCKED   1
    #define Si2183_DVBS2_STATUS_RESPONSE_DL_NO_LOCK  0
   /* DVBS2_STATUS command, BER field definition (address 2, size 1, lsb 3, unsigned)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_BER_LSB         3
   #define  Si2183_DVBS2_STATUS_RESPONSE_BER_MASK        0x01
    #define Si2183_DVBS2_STATUS_RESPONSE_BER_BER_ABOVE  1
    #define Si2183_DVBS2_STATUS_RESPONSE_BER_BER_BELOW  0
   /* DVBS2_STATUS command, UNCOR field definition (address 2, size 1, lsb 4, unsigned)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_UNCOR_LSB         4
   #define  Si2183_DVBS2_STATUS_RESPONSE_UNCOR_MASK        0x01
    #define Si2183_DVBS2_STATUS_RESPONSE_UNCOR_NO_UNCOR_FOUND  0
    #define Si2183_DVBS2_STATUS_RESPONSE_UNCOR_UNCOR_FOUND     1
   /* DVBS2_STATUS command, CNR field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_CNR_LSB         0
   #define  Si2183_DVBS2_STATUS_RESPONSE_CNR_MASK        0xff
   /* DVBS2_STATUS command, AFC_FREQ field definition (address 4, size 16, lsb 0, signed)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_AFC_FREQ_LSB         0
   #define  Si2183_DVBS2_STATUS_RESPONSE_AFC_FREQ_MASK        0xffff
   #define  Si2183_DVBS2_STATUS_RESPONSE_AFC_FREQ_SHIFT       16
   /* DVBS2_STATUS command, TIMING_OFFSET field definition (address 6, size 16, lsb 0, signed)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_TIMING_OFFSET_LSB         0
   #define  Si2183_DVBS2_STATUS_RESPONSE_TIMING_OFFSET_MASK        0xffff
   #define  Si2183_DVBS2_STATUS_RESPONSE_TIMING_OFFSET_SHIFT       16
   /* DVBS2_STATUS command, CONSTELLATION field definition (address 8, size 6, lsb 0, unsigned)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_CONSTELLATION_LSB         0
   #define  Si2183_DVBS2_STATUS_RESPONSE_CONSTELLATION_MASK        0x3f
    #define Si2183_DVBS2_STATUS_RESPONSE_CONSTELLATION_16APSK    20
    #define Si2183_DVBS2_STATUS_RESPONSE_CONSTELLATION_16APSK_L  24
    #define Si2183_DVBS2_STATUS_RESPONSE_CONSTELLATION_32APSK_1  21
    #define Si2183_DVBS2_STATUS_RESPONSE_CONSTELLATION_32APSK_2  26
    #define Si2183_DVBS2_STATUS_RESPONSE_CONSTELLATION_32APSK_L  25
    #define Si2183_DVBS2_STATUS_RESPONSE_CONSTELLATION_8APSK_L   23
    #define Si2183_DVBS2_STATUS_RESPONSE_CONSTELLATION_8PSK      14
    #define Si2183_DVBS2_STATUS_RESPONSE_CONSTELLATION_QPSK      3
   /* DVBS2_STATUS command, SP_INV field definition (address 8, size 1, lsb 6, unsigned)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_SP_INV_LSB         6
   #define  Si2183_DVBS2_STATUS_RESPONSE_SP_INV_MASK        0x01
    #define Si2183_DVBS2_STATUS_RESPONSE_SP_INV_INVERTED  1
    #define Si2183_DVBS2_STATUS_RESPONSE_SP_INV_NORMAL    0
   /* DVBS2_STATUS command, PILOTS field definition (address 8, size 1, lsb 7, unsigned)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_PILOTS_LSB         7
   #define  Si2183_DVBS2_STATUS_RESPONSE_PILOTS_MASK        0x01
    #define Si2183_DVBS2_STATUS_RESPONSE_PILOTS_OFF  0
    #define Si2183_DVBS2_STATUS_RESPONSE_PILOTS_ON   1
   /* DVBS2_STATUS command, CODE_RATE field definition (address 9, size 5, lsb 0, unsigned)*/
   #define  Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_LSB         0
   #define  Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_MASK        0x1f
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_11_15  27
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_11_20  19
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_13_18  26
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_13_45  16
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_1_2    1
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_1_3    10
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_1_4    11
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_23_36  23
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_25_36  24
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_26_45  21
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_28_45  22
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_2_3    2
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_2_5    12
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_32_45  25
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_3_4    3
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_3_5    13
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_4_5    4
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_5_6    5
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_5_9    20
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_77_90  29
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_7_9    28
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_8_15   18
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_8_9    8
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_9_10   9
    #define Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_9_20   17

#endif /* Si2183_DVBS2_STATUS_CMD */

/* Si2183_DVBS2_STREAM_INFO command definition */
#define   Si2183_DVBS2_STREAM_INFO_CMD 0x72

#ifdef    Si2183_DVBS2_STREAM_INFO_CMD
  #define Si2183_DVBS2_STREAM_INFO_CMD_CODE 0x010072

    typedef struct { /* Si2183_DVBS2_STREAM_INFO_CMD_struct */
     unsigned char   isi_index;
   } Si2183_DVBS2_STREAM_INFO_CMD_struct;


    typedef struct { /* Si2183_DVBS2_STREAM_INFO_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned   char   isi_id;
      unsigned   char   isi_constellation;
      unsigned   char   isi_code_rate;
   }  Si2183_DVBS2_STREAM_INFO_CMD_REPLY_struct;

   /* DVBS2_STREAM_INFO command, ISI_INDEX field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_DVBS2_STREAM_INFO_CMD_ISI_INDEX_LSB         0
   #define  Si2183_DVBS2_STREAM_INFO_CMD_ISI_INDEX_MASK        0xff
   #define  Si2183_DVBS2_STREAM_INFO_CMD_ISI_INDEX_MIN         0
   #define  Si2183_DVBS2_STREAM_INFO_CMD_ISI_INDEX_MAX         255
   /* DVBS2_STREAM_INFO command, ISI_ID field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_ID_LSB         0
   #define  Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_ID_MASK        0xff
   /* DVBS2_STREAM_INFO command, ISI_CONSTELLATION field definition (address 2, size 6, lsb 0, unsigned)*/
   #define  Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CONSTELLATION_LSB         0
   #define  Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CONSTELLATION_MASK        0x3f
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CONSTELLATION_16APSK    20
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CONSTELLATION_16APSK_L  24
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CONSTELLATION_32APSK_1  21
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CONSTELLATION_32APSK_2  26
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CONSTELLATION_32APSK_L  25
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CONSTELLATION_8APSK_L   23
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CONSTELLATION_8PSK      14
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CONSTELLATION_QPSK      3
   /* DVBS2_STREAM_INFO command, ISI_CODE_RATE field definition (address 3, size 5, lsb 0, unsigned)*/
   #define  Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_LSB         0
   #define  Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_MASK        0x1f
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_11_15  27
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_11_20  19
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_13_18  26
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_13_45  16
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_1_2    1
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_1_3    10
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_1_4    11
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_23_36  23
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_25_36  24
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_26_45  21
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_28_45  22
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_2_3    2
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_2_5    12
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_32_45  25
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_3_4    3
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_3_5    13
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_4_5    4
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_5_6    5
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_5_9    20
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_77_90  29
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_7_9    28
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_8_15   18
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_8_9    8
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_9_10   9
    #define Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_9_20   17

#endif /* Si2183_DVBS2_STREAM_INFO_CMD */

/* Si2183_DVBS2_STREAM_SELECT command definition */
#define   Si2183_DVBS2_STREAM_SELECT_CMD 0x71

#ifdef    Si2183_DVBS2_STREAM_SELECT_CMD
  #define Si2183_DVBS2_STREAM_SELECT_CMD_CODE 0x010071

    typedef struct { /* Si2183_DVBS2_STREAM_SELECT_CMD_struct */
     unsigned char   stream_id;
     unsigned char   stream_sel_mode;
   } Si2183_DVBS2_STREAM_SELECT_CMD_struct;


    typedef struct { /* Si2183_DVBS2_STREAM_SELECT_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
   }  Si2183_DVBS2_STREAM_SELECT_CMD_REPLY_struct;

   /* DVBS2_STREAM_SELECT command, STREAM_ID field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_ID_LSB         0
   #define  Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_ID_MASK        0xff
   #define  Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_ID_MIN         0
   #define  Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_ID_MAX         255
   /* DVBS2_STREAM_SELECT command, STREAM_SEL_MODE field definition (address 2,size 1, lsb 0, unsigned) */
   #define  Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_SEL_MODE_LSB         0
   #define  Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_SEL_MODE_MASK        0x01
   #define  Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_SEL_MODE_MIN         0
   #define  Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_SEL_MODE_MAX         1
    #define Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_SEL_MODE_AUTO    0
    #define Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_SEL_MODE_MANUAL  1
#endif /* Si2183_DVBS2_STREAM_SELECT_CMD */

/* Si2183_DVBS_STATUS command definition */
#define   Si2183_DVBS_STATUS_CMD 0x60

#ifdef    Si2183_DVBS_STATUS_CMD
  #define Si2183_DVBS_STATUS_CMD_CODE 0x010060

    typedef struct { /* Si2183_DVBS_STATUS_CMD_struct */
     unsigned char   intack;
   } Si2183_DVBS_STATUS_CMD_struct;


    typedef struct { /* Si2183_DVBS_STATUS_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   pclint;
      unsigned char   dlint;
      unsigned char   berint;
      unsigned char   uncorint;
      unsigned char   pcl;
      unsigned char   dl;
      unsigned char   ber;
      unsigned char   uncor;
      unsigned char   cnr;
               int    afc_freq;
               int    timing_offset;
      unsigned char   constellation;
      unsigned char   sp_inv;
      unsigned char   code_rate;
   }  Si2183_DVBS_STATUS_CMD_REPLY_struct;

   /* DVBS_STATUS command, INTACK field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2183_DVBS_STATUS_CMD_INTACK_LSB         0
   #define  Si2183_DVBS_STATUS_CMD_INTACK_MASK        0x01
   #define  Si2183_DVBS_STATUS_CMD_INTACK_MIN         0
   #define  Si2183_DVBS_STATUS_CMD_INTACK_MAX         1
    #define Si2183_DVBS_STATUS_CMD_INTACK_CLEAR  1
    #define Si2183_DVBS_STATUS_CMD_INTACK_OK     0
   /* DVBS_STATUS command, PCLINT field definition (address 1, size 1, lsb 1, unsigned)*/
   #define  Si2183_DVBS_STATUS_RESPONSE_PCLINT_LSB         1
   #define  Si2183_DVBS_STATUS_RESPONSE_PCLINT_MASK        0x01
    #define Si2183_DVBS_STATUS_RESPONSE_PCLINT_CHANGED    1
    #define Si2183_DVBS_STATUS_RESPONSE_PCLINT_NO_CHANGE  0
   /* DVBS_STATUS command, DLINT field definition (address 1, size 1, lsb 2, unsigned)*/
   #define  Si2183_DVBS_STATUS_RESPONSE_DLINT_LSB         2
   #define  Si2183_DVBS_STATUS_RESPONSE_DLINT_MASK        0x01
    #define Si2183_DVBS_STATUS_RESPONSE_DLINT_CHANGED    1
    #define Si2183_DVBS_STATUS_RESPONSE_DLINT_NO_CHANGE  0
   /* DVBS_STATUS command, BERINT field definition (address 1, size 1, lsb 3, unsigned)*/
   #define  Si2183_DVBS_STATUS_RESPONSE_BERINT_LSB         3
   #define  Si2183_DVBS_STATUS_RESPONSE_BERINT_MASK        0x01
    #define Si2183_DVBS_STATUS_RESPONSE_BERINT_CHANGED    1
    #define Si2183_DVBS_STATUS_RESPONSE_BERINT_NO_CHANGE  0
   /* DVBS_STATUS command, UNCORINT field definition (address 1, size 1, lsb 4, unsigned)*/
   #define  Si2183_DVBS_STATUS_RESPONSE_UNCORINT_LSB         4
   #define  Si2183_DVBS_STATUS_RESPONSE_UNCORINT_MASK        0x01
    #define Si2183_DVBS_STATUS_RESPONSE_UNCORINT_CHANGED    1
    #define Si2183_DVBS_STATUS_RESPONSE_UNCORINT_NO_CHANGE  0
   /* DVBS_STATUS command, PCL field definition (address 2, size 1, lsb 1, unsigned)*/
   #define  Si2183_DVBS_STATUS_RESPONSE_PCL_LSB         1
   #define  Si2183_DVBS_STATUS_RESPONSE_PCL_MASK        0x01
    #define Si2183_DVBS_STATUS_RESPONSE_PCL_LOCKED   1
    #define Si2183_DVBS_STATUS_RESPONSE_PCL_NO_LOCK  0
   /* DVBS_STATUS command, DL field definition (address 2, size 1, lsb 2, unsigned)*/
   #define  Si2183_DVBS_STATUS_RESPONSE_DL_LSB         2
   #define  Si2183_DVBS_STATUS_RESPONSE_DL_MASK        0x01
    #define Si2183_DVBS_STATUS_RESPONSE_DL_LOCKED   1
    #define Si2183_DVBS_STATUS_RESPONSE_DL_NO_LOCK  0
   /* DVBS_STATUS command, BER field definition (address 2, size 1, lsb 3, unsigned)*/
   #define  Si2183_DVBS_STATUS_RESPONSE_BER_LSB         3
   #define  Si2183_DVBS_STATUS_RESPONSE_BER_MASK        0x01
    #define Si2183_DVBS_STATUS_RESPONSE_BER_BER_ABOVE  1
    #define Si2183_DVBS_STATUS_RESPONSE_BER_BER_BELOW  0
   /* DVBS_STATUS command, UNCOR field definition (address 2, size 1, lsb 4, unsigned)*/
   #define  Si2183_DVBS_STATUS_RESPONSE_UNCOR_LSB         4
   #define  Si2183_DVBS_STATUS_RESPONSE_UNCOR_MASK        0x01
    #define Si2183_DVBS_STATUS_RESPONSE_UNCOR_NO_UNCOR_FOUND  0
    #define Si2183_DVBS_STATUS_RESPONSE_UNCOR_UNCOR_FOUND     1
   /* DVBS_STATUS command, CNR field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBS_STATUS_RESPONSE_CNR_LSB         0
   #define  Si2183_DVBS_STATUS_RESPONSE_CNR_MASK        0xff
   /* DVBS_STATUS command, AFC_FREQ field definition (address 4, size 16, lsb 0, signed)*/
   #define  Si2183_DVBS_STATUS_RESPONSE_AFC_FREQ_LSB         0
   #define  Si2183_DVBS_STATUS_RESPONSE_AFC_FREQ_MASK        0xffff
   #define  Si2183_DVBS_STATUS_RESPONSE_AFC_FREQ_SHIFT       16
   /* DVBS_STATUS command, TIMING_OFFSET field definition (address 6, size 16, lsb 0, signed)*/
   #define  Si2183_DVBS_STATUS_RESPONSE_TIMING_OFFSET_LSB         0
   #define  Si2183_DVBS_STATUS_RESPONSE_TIMING_OFFSET_MASK        0xffff
   #define  Si2183_DVBS_STATUS_RESPONSE_TIMING_OFFSET_SHIFT       16
   /* DVBS_STATUS command, CONSTELLATION field definition (address 8, size 6, lsb 0, unsigned)*/
   #define  Si2183_DVBS_STATUS_RESPONSE_CONSTELLATION_LSB         0
   #define  Si2183_DVBS_STATUS_RESPONSE_CONSTELLATION_MASK        0x3f
    #define Si2183_DVBS_STATUS_RESPONSE_CONSTELLATION_QPSK  3
   /* DVBS_STATUS command, SP_INV field definition (address 8, size 1, lsb 6, unsigned)*/
   #define  Si2183_DVBS_STATUS_RESPONSE_SP_INV_LSB         6
   #define  Si2183_DVBS_STATUS_RESPONSE_SP_INV_MASK        0x01
    #define Si2183_DVBS_STATUS_RESPONSE_SP_INV_INVERTED  1
    #define Si2183_DVBS_STATUS_RESPONSE_SP_INV_NORMAL    0
   /* DVBS_STATUS command, CODE_RATE field definition (address 9, size 4, lsb 0, unsigned)*/
   #define  Si2183_DVBS_STATUS_RESPONSE_CODE_RATE_LSB         0
   #define  Si2183_DVBS_STATUS_RESPONSE_CODE_RATE_MASK        0x0f
    #define Si2183_DVBS_STATUS_RESPONSE_CODE_RATE_1_2  1
    #define Si2183_DVBS_STATUS_RESPONSE_CODE_RATE_2_3  2
    #define Si2183_DVBS_STATUS_RESPONSE_CODE_RATE_3_4  3
    #define Si2183_DVBS_STATUS_RESPONSE_CODE_RATE_5_6  5
    #define Si2183_DVBS_STATUS_RESPONSE_CODE_RATE_6_7  6
    #define Si2183_DVBS_STATUS_RESPONSE_CODE_RATE_7_8  7

#endif /* Si2183_DVBS_STATUS_CMD */

#endif /* DEMOD_DVB_S_S2_DSS */

#ifdef    DEMOD_DVB_T2
/* Si2183_DVBT2_FEF command definition */
#define   Si2183_DVBT2_FEF_CMD 0x51

#ifdef    Si2183_DVBT2_FEF_CMD
  #define Si2183_DVBT2_FEF_CMD_CODE 0x010051

    typedef struct { /* Si2183_DVBT2_FEF_CMD_struct */
     unsigned char   fef_tuner_flag;
     unsigned char   fef_tuner_flag_inv;
   } Si2183_DVBT2_FEF_CMD_struct;


    typedef struct { /* Si2183_DVBT2_FEF_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   fef_type;
      unsigned long   fef_length;
      unsigned long   fef_repetition;
   }  Si2183_DVBT2_FEF_CMD_REPLY_struct;

   /* DVBT2_FEF command, FEF_TUNER_FLAG field definition (address 1,size 3, lsb 0, unsigned) */
   #define  Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_LSB         0
   #define  Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MASK        0x07
   #define  Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MIN         0
   #define  Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MAX         5
    #define Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MP_A       2
    #define Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MP_B       3
    #define Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MP_C       4
    #define Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MP_D       5
    #define Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_NOT_USED   1
    #define Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_NO_CHANGE  0
   /* DVBT2_FEF command, FEF_TUNER_FLAG_INV field definition (address 1,size 1, lsb 3, unsigned) */
   #define  Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_INV_LSB         3
   #define  Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_INV_MASK        0x01
   #define  Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_INV_MIN         0
   #define  Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_INV_MAX         1
    #define Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_INV_FEF_HIGH  0
    #define Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_INV_FEF_LOW   1
   /* DVBT2_FEF command, FEF_TYPE field definition (address 1, size 4, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_FEF_RESPONSE_FEF_TYPE_LSB         0
   #define  Si2183_DVBT2_FEF_RESPONSE_FEF_TYPE_MASK        0x0f
   /* DVBT2_FEF command, FEF_LENGTH field definition (address 4, size 32, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_FEF_RESPONSE_FEF_LENGTH_LSB         0
   #define  Si2183_DVBT2_FEF_RESPONSE_FEF_LENGTH_MASK        0xffffffff
   /* DVBT2_FEF command, FEF_REPETITION field definition (address 8, size 32, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_FEF_RESPONSE_FEF_REPETITION_LSB         0
   #define  Si2183_DVBT2_FEF_RESPONSE_FEF_REPETITION_MASK        0xffffffff

#endif /* Si2183_DVBT2_FEF_CMD */

/* Si2183_DVBT2_PLP_INFO command definition */
#define   Si2183_DVBT2_PLP_INFO_CMD 0x53

#ifdef    Si2183_DVBT2_PLP_INFO_CMD
  #define Si2183_DVBT2_PLP_INFO_CMD_CODE 0x010053

    typedef struct { /* Si2183_DVBT2_PLP_INFO_CMD_struct */
     unsigned char   plp_index;
   } Si2183_DVBT2_PLP_INFO_CMD_struct;


    typedef struct { /* Si2183_DVBT2_PLP_INFO_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   plp_id;
      unsigned char   reserved_1_1;
      unsigned char   in_band_b_flag;
      unsigned char   in_band_a_flag;
      unsigned char   static_flag;
      unsigned char   plp_mode;
      unsigned char   reserved_1_2;
      unsigned char   static_padding_flag;
      unsigned char   plp_payload_type;
      unsigned char   plp_type;
      unsigned char   first_frame_idx_msb;
      unsigned char   first_rf_idx;
      unsigned char   ff_flag;
      unsigned char   plp_group_id_msb;
      unsigned char   first_frame_idx_lsb;
      unsigned char   plp_mod_msb;
      unsigned char   plp_cod;
      unsigned char   plp_group_id_lsb;
      unsigned char   plp_num_blocks_max_msb;
      unsigned char   plp_fec_type;
      unsigned char   plp_rot;
      unsigned char   plp_mod_lsb;
      unsigned char   frame_interval_msb;
      unsigned char   plp_num_blocks_max_lsb;
      unsigned char   time_il_length_msb;
      unsigned char   frame_interval_lsb;
      unsigned char   time_il_type;
      unsigned char   time_il_length_lsb;
   }  Si2183_DVBT2_PLP_INFO_CMD_REPLY_struct;

   /* DVBT2_PLP_INFO command, PLP_INDEX field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_DVBT2_PLP_INFO_CMD_PLP_INDEX_LSB         0
   #define  Si2183_DVBT2_PLP_INFO_CMD_PLP_INDEX_MASK        0xff
   #define  Si2183_DVBT2_PLP_INFO_CMD_PLP_INDEX_MIN         0
   #define  Si2183_DVBT2_PLP_INFO_CMD_PLP_INDEX_MAX         255
   /* DVBT2_PLP_INFO command, PLP_ID field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_ID_LSB         0
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_ID_MASK        0xff
   /* DVBT2_PLP_INFO command, RESERVED_1_1 field definition (address 10, size 6, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_RESERVED_1_1_LSB         0
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_RESERVED_1_1_MASK        0x3f
   /* DVBT2_PLP_INFO command, IN_BAND_B_FLAG field definition (address 10, size 1, lsb 6, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_IN_BAND_B_FLAG_LSB         6
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_IN_BAND_B_FLAG_MASK        0x01
   /* DVBT2_PLP_INFO command, IN_BAND_A_FLAG field definition (address 10, size 1, lsb 7, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_IN_BAND_A_FLAG_LSB         7
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_IN_BAND_A_FLAG_MASK        0x01
   /* DVBT2_PLP_INFO command, STATIC_FLAG field definition (address 11, size 1, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_STATIC_FLAG_LSB         0
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_STATIC_FLAG_MASK        0x01
   /* DVBT2_PLP_INFO command, PLP_MODE field definition (address 11, size 2, lsb 1, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MODE_LSB         1
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MODE_MASK        0x03
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MODE_HIGH_EFFICIENCY_MODE  2
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MODE_NORMAL_MODE           1
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MODE_NOT_SPECIFIED         0
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MODE_RESERVED              3
   /* DVBT2_PLP_INFO command, RESERVED_1_2 field definition (address 11, size 5, lsb 3, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_RESERVED_1_2_LSB         3
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_RESERVED_1_2_MASK        0x1f
   /* DVBT2_PLP_INFO command, STATIC_PADDING_FLAG field definition (address 12, size 1, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_STATIC_PADDING_FLAG_LSB         0
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_STATIC_PADDING_FLAG_MASK        0x01
   /* DVBT2_PLP_INFO command, PLP_PAYLOAD_TYPE field definition (address 2, size 5, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_PAYLOAD_TYPE_LSB         0
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_PAYLOAD_TYPE_MASK        0x1f
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_PAYLOAD_TYPE_GCS   1
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_PAYLOAD_TYPE_GFPS  0
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_PAYLOAD_TYPE_GSE   2
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_PAYLOAD_TYPE_TS    3
   /* DVBT2_PLP_INFO command, PLP_TYPE field definition (address 2, size 3, lsb 5, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_TYPE_LSB         5
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_TYPE_MASK        0x07
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_TYPE_COMMON      0
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_TYPE_DATA_TYPE1  1
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_TYPE_DATA_TYPE2  2
   /* DVBT2_PLP_INFO command, FIRST_FRAME_IDX_MSB field definition (address 3, size 4, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_FIRST_FRAME_IDX_MSB_LSB         0
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_FIRST_FRAME_IDX_MSB_MASK        0x0f
   /* DVBT2_PLP_INFO command, FIRST_RF_IDX field definition (address 3, size 3, lsb 4, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_FIRST_RF_IDX_LSB         4
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_FIRST_RF_IDX_MASK        0x07
   /* DVBT2_PLP_INFO command, FF_FLAG field definition (address 3, size 1, lsb 7, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_FF_FLAG_LSB         7
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_FF_FLAG_MASK        0x01
   /* DVBT2_PLP_INFO command, PLP_GROUP_ID_MSB field definition (address 4, size 4, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_GROUP_ID_MSB_LSB         0
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_GROUP_ID_MSB_MASK        0x0f
   /* DVBT2_PLP_INFO command, FIRST_FRAME_IDX_LSB field definition (address 4, size 4, lsb 4, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_FIRST_FRAME_IDX_LSB_LSB         4
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_FIRST_FRAME_IDX_LSB_MASK        0x0f
   /* DVBT2_PLP_INFO command, PLP_MOD_MSB field definition (address 5, size 1, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MOD_MSB_LSB         0
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MOD_MSB_MASK        0x01
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MOD_MSB_16QAM   1
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MOD_MSB_256QAM  3
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MOD_MSB_64QAM   2
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MOD_MSB_QPSK    0
   /* DVBT2_PLP_INFO command, PLP_COD field definition (address 5, size 3, lsb 1, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_COD_LSB         1
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_COD_MASK        0x07
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_COD_1_2  0
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_COD_1_3  6
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_COD_2_3  2
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_COD_2_5  7
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_COD_3_4  3
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_COD_3_5  1
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_COD_4_5  4
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_COD_5_6  5
   /* DVBT2_PLP_INFO command, PLP_GROUP_ID_LSB field definition (address 5, size 4, lsb 4, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_GROUP_ID_LSB_LSB         4
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_GROUP_ID_LSB_MASK        0x0f
   /* DVBT2_PLP_INFO command, PLP_NUM_BLOCKS_MAX_MSB field definition (address 6, size 3, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_NUM_BLOCKS_MAX_MSB_LSB         0
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_NUM_BLOCKS_MAX_MSB_MASK        0x07
   /* DVBT2_PLP_INFO command, PLP_FEC_TYPE field definition (address 6, size 2, lsb 3, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_FEC_TYPE_LSB         3
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_FEC_TYPE_MASK        0x03
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_FEC_TYPE_16K_LDPC  0
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_FEC_TYPE_64K_LDPC  1
   /* DVBT2_PLP_INFO command, PLP_ROT field definition (address 6, size 1, lsb 5, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_ROT_LSB         5
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_ROT_MASK        0x01
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_ROT_NOT_ROTATED  0
    #define Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_ROT_ROTATED      1
   /* DVBT2_PLP_INFO command, PLP_MOD_LSB field definition (address 6, size 2, lsb 6, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MOD_LSB_LSB         6
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MOD_LSB_MASK        0x03
   /* DVBT2_PLP_INFO command, FRAME_INTERVAL_MSB field definition (address 7, size 1, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_FRAME_INTERVAL_MSB_LSB         0
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_FRAME_INTERVAL_MSB_MASK        0x01
   /* DVBT2_PLP_INFO command, PLP_NUM_BLOCKS_MAX_LSB field definition (address 7, size 7, lsb 1, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_NUM_BLOCKS_MAX_LSB_LSB         1
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_NUM_BLOCKS_MAX_LSB_MASK        0x7f
   /* DVBT2_PLP_INFO command, TIME_IL_LENGTH_MSB field definition (address 8, size 1, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_TIME_IL_LENGTH_MSB_LSB         0
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_TIME_IL_LENGTH_MSB_MASK        0x01
   /* DVBT2_PLP_INFO command, FRAME_INTERVAL_LSB field definition (address 8, size 7, lsb 1, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_FRAME_INTERVAL_LSB_LSB         1
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_FRAME_INTERVAL_LSB_MASK        0x7f
   /* DVBT2_PLP_INFO command, TIME_IL_TYPE field definition (address 9, size 1, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_TIME_IL_TYPE_LSB         0
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_TIME_IL_TYPE_MASK        0x01
   /* DVBT2_PLP_INFO command, TIME_IL_LENGTH_LSB field definition (address 9, size 7, lsb 1, unsigned)*/
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_TIME_IL_LENGTH_LSB_LSB         1
   #define  Si2183_DVBT2_PLP_INFO_RESPONSE_TIME_IL_LENGTH_LSB_MASK        0x7f

#endif /* Si2183_DVBT2_PLP_INFO_CMD */

/* Si2183_DVBT2_PLP_SELECT command definition */
#define   Si2183_DVBT2_PLP_SELECT_CMD 0x52

#ifdef    Si2183_DVBT2_PLP_SELECT_CMD
  #define Si2183_DVBT2_PLP_SELECT_CMD_CODE 0x010052

    typedef struct { /* Si2183_DVBT2_PLP_SELECT_CMD_struct */
     unsigned char   plp_id;
     unsigned char   plp_id_sel_mode;
   } Si2183_DVBT2_PLP_SELECT_CMD_struct;


    typedef struct { /* Si2183_DVBT2_PLP_SELECT_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
   }  Si2183_DVBT2_PLP_SELECT_CMD_REPLY_struct;

   /* DVBT2_PLP_SELECT command, PLP_ID field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_LSB         0
   #define  Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_MASK        0xff
   #define  Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_MIN         0
   #define  Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_MAX         255
   /* DVBT2_PLP_SELECT command, PLP_ID_SEL_MODE field definition (address 2,size 1, lsb 0, unsigned) */
   #define  Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_LSB         0
   #define  Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MASK        0x01
   #define  Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MIN         0
   #define  Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MAX         1
    #define Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_AUTO    0
    #define Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MANUAL  1
#endif /* Si2183_DVBT2_PLP_SELECT_CMD */

/* Si2183_DVBT2_STATUS command definition */
#define   Si2183_DVBT2_STATUS_CMD 0x50

#ifdef    Si2183_DVBT2_STATUS_CMD
  #define Si2183_DVBT2_STATUS_CMD_CODE 0x010050

    typedef struct { /* Si2183_DVBT2_STATUS_CMD_struct */
     unsigned char   intack;
   } Si2183_DVBT2_STATUS_CMD_struct;


    typedef struct { /* Si2183_DVBT2_STATUS_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   pclint;
      unsigned char   dlint;
      unsigned char   berint;
      unsigned char   uncorint;
      unsigned char   notdvbt2int;
      unsigned char   num_plp;
      unsigned char   pilot_pattern;
      unsigned char   tx_mode;
      unsigned char   rotated;
      unsigned char   short_frame;
      unsigned char   t2_mode;
      unsigned char   code_rate;
      unsigned char   t2_version;
      unsigned char   plp_id;
      unsigned char   stream_type;
      unsigned char   pcl;
      unsigned char   dl;
      unsigned char   ber;
      unsigned char   uncor;
      unsigned char   notdvbt2;
      unsigned char   cnr;
               int    afc_freq;
               int    timing_offset;
      unsigned char   constellation;
      unsigned char   sp_inv;
      unsigned char   fef;
      unsigned char   fft_mode;
      unsigned char   guard_int;
      unsigned char   bw_ext;
   }  Si2183_DVBT2_STATUS_CMD_REPLY_struct;

   /* DVBT2_STATUS command, INTACK field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2183_DVBT2_STATUS_CMD_INTACK_LSB         0
   #define  Si2183_DVBT2_STATUS_CMD_INTACK_MASK        0x01
   #define  Si2183_DVBT2_STATUS_CMD_INTACK_MIN         0
   #define  Si2183_DVBT2_STATUS_CMD_INTACK_MAX         1
    #define Si2183_DVBT2_STATUS_CMD_INTACK_CLEAR  1
    #define Si2183_DVBT2_STATUS_CMD_INTACK_OK     0
   /* DVBT2_STATUS command, PCLINT field definition (address 1, size 1, lsb 1, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_PCLINT_LSB         1
   #define  Si2183_DVBT2_STATUS_RESPONSE_PCLINT_MASK        0x01
    #define Si2183_DVBT2_STATUS_RESPONSE_PCLINT_CHANGED    1
    #define Si2183_DVBT2_STATUS_RESPONSE_PCLINT_NO_CHANGE  0
   /* DVBT2_STATUS command, DLINT field definition (address 1, size 1, lsb 2, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_DLINT_LSB         2
   #define  Si2183_DVBT2_STATUS_RESPONSE_DLINT_MASK        0x01
    #define Si2183_DVBT2_STATUS_RESPONSE_DLINT_CHANGED    1
    #define Si2183_DVBT2_STATUS_RESPONSE_DLINT_NO_CHANGE  0
   /* DVBT2_STATUS command, BERINT field definition (address 1, size 1, lsb 3, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_BERINT_LSB         3
   #define  Si2183_DVBT2_STATUS_RESPONSE_BERINT_MASK        0x01
    #define Si2183_DVBT2_STATUS_RESPONSE_BERINT_CHANGED    1
    #define Si2183_DVBT2_STATUS_RESPONSE_BERINT_NO_CHANGE  0
   /* DVBT2_STATUS command, UNCORINT field definition (address 1, size 1, lsb 4, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_UNCORINT_LSB         4
   #define  Si2183_DVBT2_STATUS_RESPONSE_UNCORINT_MASK        0x01
    #define Si2183_DVBT2_STATUS_RESPONSE_UNCORINT_CHANGED    1
    #define Si2183_DVBT2_STATUS_RESPONSE_UNCORINT_NO_CHANGE  0
   /* DVBT2_STATUS command, NOTDVBT2INT field definition (address 1, size 1, lsb 5, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_NOTDVBT2INT_LSB         5
   #define  Si2183_DVBT2_STATUS_RESPONSE_NOTDVBT2INT_MASK        0x01
    #define Si2183_DVBT2_STATUS_RESPONSE_NOTDVBT2INT_CHANGED    1
    #define Si2183_DVBT2_STATUS_RESPONSE_NOTDVBT2INT_NO_CHANGE  0
   /* DVBT2_STATUS command, NUM_PLP field definition (address 10, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_NUM_PLP_LSB         0
   #define  Si2183_DVBT2_STATUS_RESPONSE_NUM_PLP_MASK        0xff
   /* DVBT2_STATUS command, PILOT_PATTERN field definition (address 11, size 4, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_LSB         0
   #define  Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_MASK        0x0f
    #define Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP1  0
    #define Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP2  1
    #define Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP3  2
    #define Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP4  3
    #define Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP5  4
    #define Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP6  5
    #define Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP7  6
    #define Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_PP8  7
   /* DVBT2_STATUS command, TX_MODE field definition (address 11, size 1, lsb 4, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_TX_MODE_LSB         4
   #define  Si2183_DVBT2_STATUS_RESPONSE_TX_MODE_MASK        0x01
    #define Si2183_DVBT2_STATUS_RESPONSE_TX_MODE_MISO  1
    #define Si2183_DVBT2_STATUS_RESPONSE_TX_MODE_SISO  0
   /* DVBT2_STATUS command, ROTATED field definition (address 11, size 1, lsb 5, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_ROTATED_LSB         5
   #define  Si2183_DVBT2_STATUS_RESPONSE_ROTATED_MASK        0x01
    #define Si2183_DVBT2_STATUS_RESPONSE_ROTATED_NORMAL   0
    #define Si2183_DVBT2_STATUS_RESPONSE_ROTATED_ROTATED  1
   /* DVBT2_STATUS command, SHORT_FRAME field definition (address 11, size 1, lsb 6, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_SHORT_FRAME_LSB         6
   #define  Si2183_DVBT2_STATUS_RESPONSE_SHORT_FRAME_MASK        0x01
    #define Si2183_DVBT2_STATUS_RESPONSE_SHORT_FRAME_16K_LDPC  0
    #define Si2183_DVBT2_STATUS_RESPONSE_SHORT_FRAME_64K_LDPC  1
   /* DVBT2_STATUS command, T2_MODE field definition (address 11, size 1, lsb 7, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_T2_MODE_LSB         7
   #define  Si2183_DVBT2_STATUS_RESPONSE_T2_MODE_MASK        0x01
    #define Si2183_DVBT2_STATUS_RESPONSE_T2_MODE_BASE  0
    #define Si2183_DVBT2_STATUS_RESPONSE_T2_MODE_LITE  1
   /* DVBT2_STATUS command, CODE_RATE field definition (address 12, size 4, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_CODE_RATE_LSB         0
   #define  Si2183_DVBT2_STATUS_RESPONSE_CODE_RATE_MASK        0x0f
    #define Si2183_DVBT2_STATUS_RESPONSE_CODE_RATE_1_2  1
    #define Si2183_DVBT2_STATUS_RESPONSE_CODE_RATE_1_3  10
    #define Si2183_DVBT2_STATUS_RESPONSE_CODE_RATE_2_3  2
    #define Si2183_DVBT2_STATUS_RESPONSE_CODE_RATE_2_5  12
    #define Si2183_DVBT2_STATUS_RESPONSE_CODE_RATE_3_4  3
    #define Si2183_DVBT2_STATUS_RESPONSE_CODE_RATE_3_5  13
    #define Si2183_DVBT2_STATUS_RESPONSE_CODE_RATE_4_5  4
    #define Si2183_DVBT2_STATUS_RESPONSE_CODE_RATE_5_6  5
   /* DVBT2_STATUS command, T2_VERSION field definition (address 12, size 4, lsb 4, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_T2_VERSION_LSB         4
   #define  Si2183_DVBT2_STATUS_RESPONSE_T2_VERSION_MASK        0x0f
    #define Si2183_DVBT2_STATUS_RESPONSE_T2_VERSION_1_1_1  0
    #define Si2183_DVBT2_STATUS_RESPONSE_T2_VERSION_1_2_1  1
    #define Si2183_DVBT2_STATUS_RESPONSE_T2_VERSION_1_3_1  2
   /* DVBT2_STATUS command, PLP_ID field definition (address 13, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_PLP_ID_LSB         0
   #define  Si2183_DVBT2_STATUS_RESPONSE_PLP_ID_MASK        0xff
   /* DVBT2_STATUS command, STREAM_TYPE field definition (address 14, size 2, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_STREAM_TYPE_LSB         0
   #define  Si2183_DVBT2_STATUS_RESPONSE_STREAM_TYPE_MASK        0x03
    #define Si2183_DVBT2_STATUS_RESPONSE_STREAM_TYPE_GCS   1
    #define Si2183_DVBT2_STATUS_RESPONSE_STREAM_TYPE_GFPS  0
    #define Si2183_DVBT2_STATUS_RESPONSE_STREAM_TYPE_GSE   2
    #define Si2183_DVBT2_STATUS_RESPONSE_STREAM_TYPE_TS    3
   /* DVBT2_STATUS command, PCL field definition (address 2, size 1, lsb 1, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_PCL_LSB         1
   #define  Si2183_DVBT2_STATUS_RESPONSE_PCL_MASK        0x01
    #define Si2183_DVBT2_STATUS_RESPONSE_PCL_LOCKED   1
    #define Si2183_DVBT2_STATUS_RESPONSE_PCL_NO_LOCK  0
   /* DVBT2_STATUS command, DL field definition (address 2, size 1, lsb 2, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_DL_LSB         2
   #define  Si2183_DVBT2_STATUS_RESPONSE_DL_MASK        0x01
    #define Si2183_DVBT2_STATUS_RESPONSE_DL_LOCKED   1
    #define Si2183_DVBT2_STATUS_RESPONSE_DL_NO_LOCK  0
   /* DVBT2_STATUS command, BER field definition (address 2, size 1, lsb 3, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_BER_LSB         3
   #define  Si2183_DVBT2_STATUS_RESPONSE_BER_MASK        0x01
    #define Si2183_DVBT2_STATUS_RESPONSE_BER_BER_ABOVE  1
    #define Si2183_DVBT2_STATUS_RESPONSE_BER_BER_BELOW  0
   /* DVBT2_STATUS command, UNCOR field definition (address 2, size 1, lsb 4, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_UNCOR_LSB         4
   #define  Si2183_DVBT2_STATUS_RESPONSE_UNCOR_MASK        0x01
    #define Si2183_DVBT2_STATUS_RESPONSE_UNCOR_NO_UNCOR_FOUND  0
    #define Si2183_DVBT2_STATUS_RESPONSE_UNCOR_UNCOR_FOUND     1
   /* DVBT2_STATUS command, NOTDVBT2 field definition (address 2, size 1, lsb 5, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_NOTDVBT2_LSB         5
   #define  Si2183_DVBT2_STATUS_RESPONSE_NOTDVBT2_MASK        0x01
    #define Si2183_DVBT2_STATUS_RESPONSE_NOTDVBT2_DVBT2      0
    #define Si2183_DVBT2_STATUS_RESPONSE_NOTDVBT2_NOT_DVBT2  1
   /* DVBT2_STATUS command, CNR field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_CNR_LSB         0
   #define  Si2183_DVBT2_STATUS_RESPONSE_CNR_MASK        0xff
   /* DVBT2_STATUS command, AFC_FREQ field definition (address 4, size 16, lsb 0, signed)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_AFC_FREQ_LSB         0
   #define  Si2183_DVBT2_STATUS_RESPONSE_AFC_FREQ_MASK        0xffff
   #define  Si2183_DVBT2_STATUS_RESPONSE_AFC_FREQ_SHIFT       16
   /* DVBT2_STATUS command, TIMING_OFFSET field definition (address 6, size 16, lsb 0, signed)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_TIMING_OFFSET_LSB         0
   #define  Si2183_DVBT2_STATUS_RESPONSE_TIMING_OFFSET_MASK        0xffff
   #define  Si2183_DVBT2_STATUS_RESPONSE_TIMING_OFFSET_SHIFT       16
   /* DVBT2_STATUS command, CONSTELLATION field definition (address 8, size 6, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_CONSTELLATION_LSB         0
   #define  Si2183_DVBT2_STATUS_RESPONSE_CONSTELLATION_MASK        0x3f
    #define Si2183_DVBT2_STATUS_RESPONSE_CONSTELLATION_QAM128  10
    #define Si2183_DVBT2_STATUS_RESPONSE_CONSTELLATION_QAM16   7
    #define Si2183_DVBT2_STATUS_RESPONSE_CONSTELLATION_QAM256  11
    #define Si2183_DVBT2_STATUS_RESPONSE_CONSTELLATION_QAM32   8
    #define Si2183_DVBT2_STATUS_RESPONSE_CONSTELLATION_QAM64   9
    #define Si2183_DVBT2_STATUS_RESPONSE_CONSTELLATION_QPSK    3
   /* DVBT2_STATUS command, SP_INV field definition (address 8, size 1, lsb 6, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_SP_INV_LSB         6
   #define  Si2183_DVBT2_STATUS_RESPONSE_SP_INV_MASK        0x01
    #define Si2183_DVBT2_STATUS_RESPONSE_SP_INV_INVERTED  1
    #define Si2183_DVBT2_STATUS_RESPONSE_SP_INV_NORMAL    0
   /* DVBT2_STATUS command, FEF field definition (address 8, size 1, lsb 7, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_FEF_LSB         7
   #define  Si2183_DVBT2_STATUS_RESPONSE_FEF_MASK        0x01
    #define Si2183_DVBT2_STATUS_RESPONSE_FEF_FEF     1
    #define Si2183_DVBT2_STATUS_RESPONSE_FEF_NO_FEF  0
   /* DVBT2_STATUS command, FFT_MODE field definition (address 9, size 4, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_FFT_MODE_LSB         0
   #define  Si2183_DVBT2_STATUS_RESPONSE_FFT_MODE_MASK        0x0f
    #define Si2183_DVBT2_STATUS_RESPONSE_FFT_MODE_16K  14
    #define Si2183_DVBT2_STATUS_RESPONSE_FFT_MODE_1K   10
    #define Si2183_DVBT2_STATUS_RESPONSE_FFT_MODE_2K   11
    #define Si2183_DVBT2_STATUS_RESPONSE_FFT_MODE_32K  15
    #define Si2183_DVBT2_STATUS_RESPONSE_FFT_MODE_4K   12
    #define Si2183_DVBT2_STATUS_RESPONSE_FFT_MODE_8K   13
   /* DVBT2_STATUS command, GUARD_INT field definition (address 9, size 3, lsb 4, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_LSB         4
   #define  Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_MASK        0x07
    #define Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_19_128  6
    #define Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_19_256  7
    #define Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_1_128   5
    #define Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_1_16    2
    #define Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_1_32    1
    #define Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_1_4     4
    #define Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_1_8     3
   /* DVBT2_STATUS command, BW_EXT field definition (address 9, size 1, lsb 7, unsigned)*/
   #define  Si2183_DVBT2_STATUS_RESPONSE_BW_EXT_LSB         7
   #define  Si2183_DVBT2_STATUS_RESPONSE_BW_EXT_MASK        0x01
    #define Si2183_DVBT2_STATUS_RESPONSE_BW_EXT_EXTENDED  1
    #define Si2183_DVBT2_STATUS_RESPONSE_BW_EXT_NORMAL    0

#endif /* Si2183_DVBT2_STATUS_CMD */

/* Si2183_DVBT2_TX_ID command definition */
#define   Si2183_DVBT2_TX_ID_CMD 0x54

#ifdef    Si2183_DVBT2_TX_ID_CMD
  #define Si2183_DVBT2_TX_ID_CMD_CODE 0x010054

    typedef struct { /* Si2183_DVBT2_TX_ID_CMD_struct */
         unsigned char   nothing;   } Si2183_DVBT2_TX_ID_CMD_struct;


    typedef struct { /* Si2183_DVBT2_TX_ID_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   tx_id_availability;
      unsigned int    cell_id;
      unsigned int    network_id;
      unsigned int    t2_system_id;
   }  Si2183_DVBT2_TX_ID_CMD_REPLY_struct;

   /* DVBT2_TX_ID command, TX_ID_AVAILABILITY field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_TX_ID_RESPONSE_TX_ID_AVAILABILITY_LSB         0
   #define  Si2183_DVBT2_TX_ID_RESPONSE_TX_ID_AVAILABILITY_MASK        0xff
   /* DVBT2_TX_ID command, CELL_ID field definition (address 2, size 16, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_TX_ID_RESPONSE_CELL_ID_LSB         0
   #define  Si2183_DVBT2_TX_ID_RESPONSE_CELL_ID_MASK        0xffff
   /* DVBT2_TX_ID command, NETWORK_ID field definition (address 4, size 16, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_TX_ID_RESPONSE_NETWORK_ID_LSB         0
   #define  Si2183_DVBT2_TX_ID_RESPONSE_NETWORK_ID_MASK        0xffff
   /* DVBT2_TX_ID command, T2_SYSTEM_ID field definition (address 6, size 16, lsb 0, unsigned)*/
   #define  Si2183_DVBT2_TX_ID_RESPONSE_T2_SYSTEM_ID_LSB         0
   #define  Si2183_DVBT2_TX_ID_RESPONSE_T2_SYSTEM_ID_MASK        0xffff

#endif /* Si2183_DVBT2_TX_ID_CMD */

#endif /* DEMOD_DVB_T2 */

#ifdef    DEMOD_DVB_T
/* Si2183_DVBT_STATUS command definition */
#define   Si2183_DVBT_STATUS_CMD 0xa0

#ifdef    Si2183_DVBT_STATUS_CMD
  #define Si2183_DVBT_STATUS_CMD_CODE 0x0100a0

    typedef struct { /* Si2183_DVBT_STATUS_CMD_struct */
     unsigned char   intack;
   } Si2183_DVBT_STATUS_CMD_struct;


    typedef struct { /* Si2183_DVBT_STATUS_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   pclint;
      unsigned char   dlint;
      unsigned char   berint;
      unsigned char   uncorint;
      unsigned char   notdvbtint;
      unsigned char   fft_mode;
      unsigned char   guard_int;
      unsigned char   hierarchy;
               char   tps_length;
      unsigned char   pcl;
      unsigned char   dl;
      unsigned char   ber;
      unsigned char   uncor;
      unsigned char   notdvbt;
      unsigned char   cnr;
               int    afc_freq;
               int    timing_offset;
      unsigned char   constellation;
      unsigned char   sp_inv;
      unsigned char   rate_hp;
      unsigned char   rate_lp;
   }  Si2183_DVBT_STATUS_CMD_REPLY_struct;

   /* DVBT_STATUS command, INTACK field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2183_DVBT_STATUS_CMD_INTACK_LSB         0
   #define  Si2183_DVBT_STATUS_CMD_INTACK_MASK        0x01
   #define  Si2183_DVBT_STATUS_CMD_INTACK_MIN         0
   #define  Si2183_DVBT_STATUS_CMD_INTACK_MAX         1
    #define Si2183_DVBT_STATUS_CMD_INTACK_CLEAR  1
    #define Si2183_DVBT_STATUS_CMD_INTACK_OK     0
   /* DVBT_STATUS command, PCLINT field definition (address 1, size 1, lsb 1, unsigned)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_PCLINT_LSB         1
   #define  Si2183_DVBT_STATUS_RESPONSE_PCLINT_MASK        0x01
    #define Si2183_DVBT_STATUS_RESPONSE_PCLINT_CHANGED    1
    #define Si2183_DVBT_STATUS_RESPONSE_PCLINT_NO_CHANGE  0
   /* DVBT_STATUS command, DLINT field definition (address 1, size 1, lsb 2, unsigned)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_DLINT_LSB         2
   #define  Si2183_DVBT_STATUS_RESPONSE_DLINT_MASK        0x01
    #define Si2183_DVBT_STATUS_RESPONSE_DLINT_CHANGED    1
    #define Si2183_DVBT_STATUS_RESPONSE_DLINT_NO_CHANGE  0
   /* DVBT_STATUS command, BERINT field definition (address 1, size 1, lsb 3, unsigned)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_BERINT_LSB         3
   #define  Si2183_DVBT_STATUS_RESPONSE_BERINT_MASK        0x01
    #define Si2183_DVBT_STATUS_RESPONSE_BERINT_CHANGED    1
    #define Si2183_DVBT_STATUS_RESPONSE_BERINT_NO_CHANGE  0
   /* DVBT_STATUS command, UNCORINT field definition (address 1, size 1, lsb 4, unsigned)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_UNCORINT_LSB         4
   #define  Si2183_DVBT_STATUS_RESPONSE_UNCORINT_MASK        0x01
    #define Si2183_DVBT_STATUS_RESPONSE_UNCORINT_CHANGED    1
    #define Si2183_DVBT_STATUS_RESPONSE_UNCORINT_NO_CHANGE  0
   /* DVBT_STATUS command, NOTDVBTINT field definition (address 1, size 1, lsb 5, unsigned)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_NOTDVBTINT_LSB         5
   #define  Si2183_DVBT_STATUS_RESPONSE_NOTDVBTINT_MASK        0x01
    #define Si2183_DVBT_STATUS_RESPONSE_NOTDVBTINT_CHANGED    1
    #define Si2183_DVBT_STATUS_RESPONSE_NOTDVBTINT_NO_CHANGE  0
   /* DVBT_STATUS command, FFT_MODE field definition (address 10, size 4, lsb 0, unsigned)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_FFT_MODE_LSB         0
   #define  Si2183_DVBT_STATUS_RESPONSE_FFT_MODE_MASK        0x0f
    #define Si2183_DVBT_STATUS_RESPONSE_FFT_MODE_2K  11
    #define Si2183_DVBT_STATUS_RESPONSE_FFT_MODE_4K  12
    #define Si2183_DVBT_STATUS_RESPONSE_FFT_MODE_8K  13
   /* DVBT_STATUS command, GUARD_INT field definition (address 10, size 3, lsb 4, unsigned)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_GUARD_INT_LSB         4
   #define  Si2183_DVBT_STATUS_RESPONSE_GUARD_INT_MASK        0x07
    #define Si2183_DVBT_STATUS_RESPONSE_GUARD_INT_1_16  2
    #define Si2183_DVBT_STATUS_RESPONSE_GUARD_INT_1_32  1
    #define Si2183_DVBT_STATUS_RESPONSE_GUARD_INT_1_4   4
    #define Si2183_DVBT_STATUS_RESPONSE_GUARD_INT_1_8   3
   /* DVBT_STATUS command, HIERARCHY field definition (address 11, size 3, lsb 0, unsigned)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_HIERARCHY_LSB         0
   #define  Si2183_DVBT_STATUS_RESPONSE_HIERARCHY_MASK        0x07
    #define Si2183_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA1  2
    #define Si2183_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA2  3
    #define Si2183_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA4  5
    #define Si2183_DVBT_STATUS_RESPONSE_HIERARCHY_NONE   1
   /* DVBT_STATUS command, TPS_LENGTH field definition (address 12, size 7, lsb 0, signed)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_TPS_LENGTH_LSB         0
   #define  Si2183_DVBT_STATUS_RESPONSE_TPS_LENGTH_MASK        0x7f
   #define  Si2183_DVBT_STATUS_RESPONSE_TPS_LENGTH_SHIFT       25
   /* DVBT_STATUS command, PCL field definition (address 2, size 1, lsb 1, unsigned)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_PCL_LSB         1
   #define  Si2183_DVBT_STATUS_RESPONSE_PCL_MASK        0x01
    #define Si2183_DVBT_STATUS_RESPONSE_PCL_LOCKED   1
    #define Si2183_DVBT_STATUS_RESPONSE_PCL_NO_LOCK  0
   /* DVBT_STATUS command, DL field definition (address 2, size 1, lsb 2, unsigned)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_DL_LSB         2
   #define  Si2183_DVBT_STATUS_RESPONSE_DL_MASK        0x01
    #define Si2183_DVBT_STATUS_RESPONSE_DL_LOCKED   1
    #define Si2183_DVBT_STATUS_RESPONSE_DL_NO_LOCK  0
   /* DVBT_STATUS command, BER field definition (address 2, size 1, lsb 3, unsigned)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_BER_LSB         3
   #define  Si2183_DVBT_STATUS_RESPONSE_BER_MASK        0x01
    #define Si2183_DVBT_STATUS_RESPONSE_BER_BER_ABOVE  1
    #define Si2183_DVBT_STATUS_RESPONSE_BER_BER_BELOW  0
   /* DVBT_STATUS command, UNCOR field definition (address 2, size 1, lsb 4, unsigned)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_UNCOR_LSB         4
   #define  Si2183_DVBT_STATUS_RESPONSE_UNCOR_MASK        0x01
    #define Si2183_DVBT_STATUS_RESPONSE_UNCOR_NO_UNCOR_FOUND  0
    #define Si2183_DVBT_STATUS_RESPONSE_UNCOR_UNCOR_FOUND     1
   /* DVBT_STATUS command, NOTDVBT field definition (address 2, size 1, lsb 5, unsigned)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_NOTDVBT_LSB         5
   #define  Si2183_DVBT_STATUS_RESPONSE_NOTDVBT_MASK        0x01
    #define Si2183_DVBT_STATUS_RESPONSE_NOTDVBT_DVBT      0
    #define Si2183_DVBT_STATUS_RESPONSE_NOTDVBT_NOT_DVBT  1
   /* DVBT_STATUS command, CNR field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_CNR_LSB         0
   #define  Si2183_DVBT_STATUS_RESPONSE_CNR_MASK        0xff
   /* DVBT_STATUS command, AFC_FREQ field definition (address 4, size 16, lsb 0, signed)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_AFC_FREQ_LSB         0
   #define  Si2183_DVBT_STATUS_RESPONSE_AFC_FREQ_MASK        0xffff
   #define  Si2183_DVBT_STATUS_RESPONSE_AFC_FREQ_SHIFT       16
   /* DVBT_STATUS command, TIMING_OFFSET field definition (address 6, size 16, lsb 0, signed)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_TIMING_OFFSET_LSB         0
   #define  Si2183_DVBT_STATUS_RESPONSE_TIMING_OFFSET_MASK        0xffff
   #define  Si2183_DVBT_STATUS_RESPONSE_TIMING_OFFSET_SHIFT       16
   /* DVBT_STATUS command, CONSTELLATION field definition (address 8, size 6, lsb 0, unsigned)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_CONSTELLATION_LSB         0
   #define  Si2183_DVBT_STATUS_RESPONSE_CONSTELLATION_MASK        0x3f
    #define Si2183_DVBT_STATUS_RESPONSE_CONSTELLATION_QAM16  7
    #define Si2183_DVBT_STATUS_RESPONSE_CONSTELLATION_QAM64  9
    #define Si2183_DVBT_STATUS_RESPONSE_CONSTELLATION_QPSK   3
   /* DVBT_STATUS command, SP_INV field definition (address 8, size 1, lsb 6, unsigned)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_SP_INV_LSB         6
   #define  Si2183_DVBT_STATUS_RESPONSE_SP_INV_MASK        0x01
    #define Si2183_DVBT_STATUS_RESPONSE_SP_INV_INVERTED  1
    #define Si2183_DVBT_STATUS_RESPONSE_SP_INV_NORMAL    0
   /* DVBT_STATUS command, RATE_HP field definition (address 9, size 4, lsb 0, unsigned)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_RATE_HP_LSB         0
   #define  Si2183_DVBT_STATUS_RESPONSE_RATE_HP_MASK        0x0f
    #define Si2183_DVBT_STATUS_RESPONSE_RATE_HP_1_2  1
    #define Si2183_DVBT_STATUS_RESPONSE_RATE_HP_2_3  2
    #define Si2183_DVBT_STATUS_RESPONSE_RATE_HP_3_4  3
    #define Si2183_DVBT_STATUS_RESPONSE_RATE_HP_5_6  5
    #define Si2183_DVBT_STATUS_RESPONSE_RATE_HP_7_8  7
   /* DVBT_STATUS command, RATE_LP field definition (address 9, size 4, lsb 4, unsigned)*/
   #define  Si2183_DVBT_STATUS_RESPONSE_RATE_LP_LSB         4
   #define  Si2183_DVBT_STATUS_RESPONSE_RATE_LP_MASK        0x0f
    #define Si2183_DVBT_STATUS_RESPONSE_RATE_LP_1_2  1
    #define Si2183_DVBT_STATUS_RESPONSE_RATE_LP_2_3  2
    #define Si2183_DVBT_STATUS_RESPONSE_RATE_LP_3_4  3
    #define Si2183_DVBT_STATUS_RESPONSE_RATE_LP_5_6  5
    #define Si2183_DVBT_STATUS_RESPONSE_RATE_LP_7_8  7

#endif /* Si2183_DVBT_STATUS_CMD */

/* Si2183_DVBT_TPS_EXTRA command definition */
#define   Si2183_DVBT_TPS_EXTRA_CMD 0xa1

#ifdef    Si2183_DVBT_TPS_EXTRA_CMD
  #define Si2183_DVBT_TPS_EXTRA_CMD_CODE 0x0100a1

    typedef struct { /* Si2183_DVBT_TPS_EXTRA_CMD_struct */
         unsigned char   nothing;   } Si2183_DVBT_TPS_EXTRA_CMD_struct;


    typedef struct { /* Si2183_DVBT_TPS_EXTRA_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   lptimeslice;
      unsigned char   hptimeslice;
      unsigned char   lpmpefec;
      unsigned char   hpmpefec;
      unsigned char   dvbhinter;
               int    cell_id;
      unsigned char   tps_res1;
      unsigned char   tps_res2;
      unsigned char   tps_res3;
      unsigned char   tps_res4;
   }  Si2183_DVBT_TPS_EXTRA_CMD_REPLY_struct;

   /* DVBT_TPS_EXTRA command, LPTIMESLICE field definition (address 1, size 1, lsb 0, unsigned)*/
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_LPTIMESLICE_LSB         0
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_LPTIMESLICE_MASK        0x01
    #define Si2183_DVBT_TPS_EXTRA_RESPONSE_LPTIMESLICE_OFF  0
    #define Si2183_DVBT_TPS_EXTRA_RESPONSE_LPTIMESLICE_ON   1
   /* DVBT_TPS_EXTRA command, HPTIMESLICE field definition (address 1, size 1, lsb 1, unsigned)*/
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_HPTIMESLICE_LSB         1
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_HPTIMESLICE_MASK        0x01
    #define Si2183_DVBT_TPS_EXTRA_RESPONSE_HPTIMESLICE_OFF  0
    #define Si2183_DVBT_TPS_EXTRA_RESPONSE_HPTIMESLICE_ON   1
   /* DVBT_TPS_EXTRA command, LPMPEFEC field definition (address 1, size 1, lsb 2, unsigned)*/
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_LPMPEFEC_LSB         2
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_LPMPEFEC_MASK        0x01
    #define Si2183_DVBT_TPS_EXTRA_RESPONSE_LPMPEFEC_OFF  0
    #define Si2183_DVBT_TPS_EXTRA_RESPONSE_LPMPEFEC_ON   1
   /* DVBT_TPS_EXTRA command, HPMPEFEC field definition (address 1, size 1, lsb 3, unsigned)*/
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_HPMPEFEC_LSB         3
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_HPMPEFEC_MASK        0x01
    #define Si2183_DVBT_TPS_EXTRA_RESPONSE_HPMPEFEC_OFF  0
    #define Si2183_DVBT_TPS_EXTRA_RESPONSE_HPMPEFEC_ON   1
   /* DVBT_TPS_EXTRA command, DVBHINTER field definition (address 1, size 1, lsb 4, unsigned)*/
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_DVBHINTER_LSB         4
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_DVBHINTER_MASK        0x01
    #define Si2183_DVBT_TPS_EXTRA_RESPONSE_DVBHINTER_IN_DEPTH  1
    #define Si2183_DVBT_TPS_EXTRA_RESPONSE_DVBHINTER_NATIVE    0
   /* DVBT_TPS_EXTRA command, CELL_ID field definition (address 2, size 16, lsb 0, signed)*/
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_CELL_ID_LSB         0
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_CELL_ID_MASK        0xffff
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_CELL_ID_SHIFT       16
   /* DVBT_TPS_EXTRA command, TPS_RES1 field definition (address 4, size 4, lsb 0, unsigned)*/
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_TPS_RES1_LSB         0
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_TPS_RES1_MASK        0x0f
   /* DVBT_TPS_EXTRA command, TPS_RES2 field definition (address 4, size 4, lsb 4, unsigned)*/
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_TPS_RES2_LSB         4
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_TPS_RES2_MASK        0x0f
   /* DVBT_TPS_EXTRA command, TPS_RES3 field definition (address 5, size 4, lsb 0, unsigned)*/
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_TPS_RES3_LSB         0
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_TPS_RES3_MASK        0x0f
   /* DVBT_TPS_EXTRA command, TPS_RES4 field definition (address 5, size 4, lsb 4, unsigned)*/
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_TPS_RES4_LSB         4
   #define  Si2183_DVBT_TPS_EXTRA_RESPONSE_TPS_RES4_MASK        0x0f

#endif /* Si2183_DVBT_TPS_EXTRA_CMD */

#endif /* DEMOD_DVB_T */

/* Si2183_EXIT_BOOTLOADER command definition */
#define   Si2183_EXIT_BOOTLOADER_CMD 0x01

#ifdef    Si2183_EXIT_BOOTLOADER_CMD
  #define Si2183_EXIT_BOOTLOADER_CMD_CODE 0x010001

    typedef struct { /* Si2183_EXIT_BOOTLOADER_CMD_struct */
     unsigned char   func;
     unsigned char   ctsien;
   } Si2183_EXIT_BOOTLOADER_CMD_struct;


    typedef struct { /* Si2183_EXIT_BOOTLOADER_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
   }  Si2183_EXIT_BOOTLOADER_CMD_REPLY_struct;

   /* EXIT_BOOTLOADER command, FUNC field definition (address 1,size 7, lsb 0, unsigned) */
   #define  Si2183_EXIT_BOOTLOADER_CMD_FUNC_LSB         0
   #define  Si2183_EXIT_BOOTLOADER_CMD_FUNC_MASK        0x7f
   #define  Si2183_EXIT_BOOTLOADER_CMD_FUNC_MIN         1
   #define  Si2183_EXIT_BOOTLOADER_CMD_FUNC_MAX         1
    #define Si2183_EXIT_BOOTLOADER_CMD_FUNC_NORMAL  1
   /* EXIT_BOOTLOADER command, CTSIEN field definition (address 1,size 1, lsb 7, unsigned) */
   #define  Si2183_EXIT_BOOTLOADER_CMD_CTSIEN_LSB         7
   #define  Si2183_EXIT_BOOTLOADER_CMD_CTSIEN_MASK        0x01
   #define  Si2183_EXIT_BOOTLOADER_CMD_CTSIEN_MIN         0
   #define  Si2183_EXIT_BOOTLOADER_CMD_CTSIEN_MAX         1
    #define Si2183_EXIT_BOOTLOADER_CMD_CTSIEN_OFF  0
    #define Si2183_EXIT_BOOTLOADER_CMD_CTSIEN_ON   1
#endif /* Si2183_EXIT_BOOTLOADER_CMD */

/* Si2183_GET_PROPERTY command definition */
#define   Si2183_GET_PROPERTY_CMD 0x15

#ifdef    Si2183_GET_PROPERTY_CMD
  #define Si2183_GET_PROPERTY_CMD_CODE 0x010015

    typedef struct { /* Si2183_GET_PROPERTY_CMD_struct */
     unsigned char   reserved;
     unsigned int    prop;
   } Si2183_GET_PROPERTY_CMD_struct;


    typedef struct { /* Si2183_GET_PROPERTY_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   reserved;
      unsigned int    data;
   }  Si2183_GET_PROPERTY_CMD_REPLY_struct;

   /* GET_PROPERTY command, RESERVED field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_GET_PROPERTY_CMD_RESERVED_LSB         0
   #define  Si2183_GET_PROPERTY_CMD_RESERVED_MASK        0xff
   #define  Si2183_GET_PROPERTY_CMD_RESERVED_MIN         0
   #define  Si2183_GET_PROPERTY_CMD_RESERVED_MAX         0
    #define Si2183_GET_PROPERTY_CMD_RESERVED_RESERVED_MIN  0
    #define Si2183_GET_PROPERTY_CMD_RESERVED_RESERVED_MAX  0
   /* GET_PROPERTY command, PROP field definition (address 2,size 16, lsb 0, unsigned) */
   #define  Si2183_GET_PROPERTY_CMD_PROP_LSB         0
   #define  Si2183_GET_PROPERTY_CMD_PROP_MASK        0xffff
   #define  Si2183_GET_PROPERTY_CMD_PROP_MIN         0
   #define  Si2183_GET_PROPERTY_CMD_PROP_MAX         65535
    #define Si2183_GET_PROPERTY_CMD_PROP_PROP_MIN  0
    #define Si2183_GET_PROPERTY_CMD_PROP_PROP_MAX  65535
   /* GET_PROPERTY command, RESERVED field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2183_GET_PROPERTY_RESPONSE_RESERVED_LSB         0
   #define  Si2183_GET_PROPERTY_RESPONSE_RESERVED_MASK        0xff
   /* GET_PROPERTY command, DATA field definition (address 2, size 16, lsb 0, unsigned)*/
   #define  Si2183_GET_PROPERTY_RESPONSE_DATA_LSB         0
   #define  Si2183_GET_PROPERTY_RESPONSE_DATA_MASK        0xffff

#endif /* Si2183_GET_PROPERTY_CMD */

/* Si2183_GET_REV command definition */
#define   Si2183_GET_REV_CMD 0x11

#ifdef    Si2183_GET_REV_CMD
  #define Si2183_GET_REV_CMD_CODE 0x010011

    typedef struct { /* Si2183_GET_REV_CMD_struct */
         unsigned char   nothing;   } Si2183_GET_REV_CMD_struct;


    typedef struct { /* Si2183_GET_REV_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   pn;
      unsigned char   rx;
      unsigned char   fwmajor;
      unsigned char   fwminor;
      unsigned int    patch;
      unsigned char   cmpmajor;
      unsigned char   cmpminor;
      unsigned char   cmpbuild;
      unsigned char   chiprev;
      unsigned char   mcm_die;
   }  Si2183_GET_REV_CMD_REPLY_struct;

   /* GET_REV command, PN field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2183_GET_REV_RESPONSE_PN_LSB         0
   #define  Si2183_GET_REV_RESPONSE_PN_MASK        0xff
   /* GET_REV command, RX field definition (address 12, size 1, lsb 7, unsigned)*/
   #define  Si2183_GET_REV_RESPONSE_RX_LSB         7
   #define  Si2183_GET_REV_RESPONSE_RX_MASK        0x01
    #define Si2183_GET_REV_RESPONSE_RX_RX          1
    #define Si2183_GET_REV_RESPONSE_RX_STANDALONE  0
   /* GET_REV command, FWMAJOR field definition (address 2, size 8, lsb 0, unsigned)*/
   #define  Si2183_GET_REV_RESPONSE_FWMAJOR_LSB         0
   #define  Si2183_GET_REV_RESPONSE_FWMAJOR_MASK        0xff
   /* GET_REV command, FWMINOR field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si2183_GET_REV_RESPONSE_FWMINOR_LSB         0
   #define  Si2183_GET_REV_RESPONSE_FWMINOR_MASK        0xff
   /* GET_REV command, PATCH field definition (address 4, size 16, lsb 0, unsigned)*/
   #define  Si2183_GET_REV_RESPONSE_PATCH_LSB         0
   #define  Si2183_GET_REV_RESPONSE_PATCH_MASK        0xffff
   /* GET_REV command, CMPMAJOR field definition (address 6, size 8, lsb 0, unsigned)*/
   #define  Si2183_GET_REV_RESPONSE_CMPMAJOR_LSB         0
   #define  Si2183_GET_REV_RESPONSE_CMPMAJOR_MASK        0xff
   /* GET_REV command, CMPMINOR field definition (address 7, size 8, lsb 0, unsigned)*/
   #define  Si2183_GET_REV_RESPONSE_CMPMINOR_LSB         0
   #define  Si2183_GET_REV_RESPONSE_CMPMINOR_MASK        0xff
   /* GET_REV command, CMPBUILD field definition (address 8, size 8, lsb 0, unsigned)*/
   #define  Si2183_GET_REV_RESPONSE_CMPBUILD_LSB         0
   #define  Si2183_GET_REV_RESPONSE_CMPBUILD_MASK        0xff
    #define Si2183_GET_REV_RESPONSE_CMPBUILD_CMPBUILD_MIN  0
    #define Si2183_GET_REV_RESPONSE_CMPBUILD_CMPBUILD_MAX  255
   /* GET_REV command, CHIPREV field definition (address 9, size 4, lsb 0, unsigned)*/
   #define  Si2183_GET_REV_RESPONSE_CHIPREV_LSB         0
   #define  Si2183_GET_REV_RESPONSE_CHIPREV_MASK        0x0f
    #define Si2183_GET_REV_RESPONSE_CHIPREV_A  1
    #define Si2183_GET_REV_RESPONSE_CHIPREV_B  2
    #define Si2183_GET_REV_RESPONSE_CHIPREV_C  3
    #define Si2183_GET_REV_RESPONSE_CHIPREV_D  4
    #define Si2183_GET_REV_RESPONSE_CHIPREV_E  5
   /* GET_REV command, MCM_DIE field definition (address 9, size 4, lsb 4, unsigned)*/
   #define  Si2183_GET_REV_RESPONSE_MCM_DIE_LSB         4
   #define  Si2183_GET_REV_RESPONSE_MCM_DIE_MASK        0x0f
    #define Si2183_GET_REV_RESPONSE_MCM_DIE_DIE_A   1
    #define Si2183_GET_REV_RESPONSE_MCM_DIE_DIE_B   2
    #define Si2183_GET_REV_RESPONSE_MCM_DIE_SINGLE  0

#endif /* Si2183_GET_REV_CMD */

/* Si2183_I2C_PASSTHROUGH command definition */
#define   Si2183_I2C_PASSTHROUGH_CMD 0xc0

#ifdef    Si2183_I2C_PASSTHROUGH_CMD
  #define Si2183_I2C_PASSTHROUGH_CMD_CODE 0x0200c0

    typedef struct { /* Si2183_I2C_PASSTHROUGH_CMD_struct */
     unsigned char   subcode;
     unsigned char   i2c_passthru;
     unsigned char   reserved;
   } Si2183_I2C_PASSTHROUGH_CMD_struct;


    typedef struct { /* Si2183_I2C_PASSTHROUGH_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
   }  Si2183_I2C_PASSTHROUGH_CMD_REPLY_struct;

   /* I2C_PASSTHROUGH command, SUBCODE field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_I2C_PASSTHROUGH_CMD_SUBCODE_LSB         0
   #define  Si2183_I2C_PASSTHROUGH_CMD_SUBCODE_MASK        0xff
   #define  Si2183_I2C_PASSTHROUGH_CMD_SUBCODE_MIN         13
   #define  Si2183_I2C_PASSTHROUGH_CMD_SUBCODE_MAX         13
    #define Si2183_I2C_PASSTHROUGH_CMD_SUBCODE_CODE  13
   /* I2C_PASSTHROUGH command, I2C_PASSTHRU field definition (address 2,size 1, lsb 0, unsigned) */
   #define  Si2183_I2C_PASSTHROUGH_CMD_I2C_PASSTHRU_LSB         0
   #define  Si2183_I2C_PASSTHROUGH_CMD_I2C_PASSTHRU_MASK        0x01
   #define  Si2183_I2C_PASSTHROUGH_CMD_I2C_PASSTHRU_MIN         0
   #define  Si2183_I2C_PASSTHROUGH_CMD_I2C_PASSTHRU_MAX         1
    #define Si2183_I2C_PASSTHROUGH_CMD_I2C_PASSTHRU_CLOSE  1
    #define Si2183_I2C_PASSTHROUGH_CMD_I2C_PASSTHRU_OPEN   0
   /* I2C_PASSTHROUGH command, RESERVED field definition (address 2,size 7, lsb 1, unsigned) */
   #define  Si2183_I2C_PASSTHROUGH_CMD_RESERVED_LSB         1
   #define  Si2183_I2C_PASSTHROUGH_CMD_RESERVED_MASK        0x7f
   #define  Si2183_I2C_PASSTHROUGH_CMD_RESERVED_MIN         0
   #define  Si2183_I2C_PASSTHROUGH_CMD_RESERVED_MAX         0
    #define Si2183_I2C_PASSTHROUGH_CMD_RESERVED_RESERVED  0
#endif /* Si2183_I2C_PASSTHROUGH_CMD */

#ifdef    DEMOD_ISDB_T
/* Si2183_ISDBT_AC_BITS command definition */
#define   Si2183_ISDBT_AC_BITS_CMD 0xa6

#ifdef    Si2183_ISDBT_AC_BITS_CMD
  #define Si2183_ISDBT_AC_BITS_CMD_CODE 0x0100a6

    typedef struct { /* Si2183_ISDBT_AC_BITS_CMD_struct */
     unsigned char   byte_read_offset;
     unsigned char   freeze_buffer;
   } Si2183_ISDBT_AC_BITS_CMD_struct;


    typedef struct { /* Si2183_ISDBT_AC_BITS_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned   char   data1;
      unsigned   char   data10;
      unsigned   char   data11;
      unsigned   char   data12;
      unsigned   char   data13;
      unsigned   char   data14;
      unsigned   char   data15;
      unsigned   char   data2;
      unsigned   char   data3;
      unsigned   char   data4;
      unsigned   char   data5;
      unsigned   char   data6;
      unsigned   char   data7;
      unsigned   char   data8;
      unsigned   char   data9;
   }  Si2183_ISDBT_AC_BITS_CMD_REPLY_struct;

   /* ISDBT_AC_BITS command, BYTE_READ_OFFSET field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_ISDBT_AC_BITS_CMD_BYTE_READ_OFFSET_LSB         0
   #define  Si2183_ISDBT_AC_BITS_CMD_BYTE_READ_OFFSET_MASK        0xff
   #define  Si2183_ISDBT_AC_BITS_CMD_BYTE_READ_OFFSET_MIN         0
   #define  Si2183_ISDBT_AC_BITS_CMD_BYTE_READ_OFFSET_MAX         255
   /* ISDBT_AC_BITS command, FREEZE_BUFFER field definition (address 2,size 1, lsb 0, unsigned) */
   #define  Si2183_ISDBT_AC_BITS_CMD_FREEZE_BUFFER_LSB         0
   #define  Si2183_ISDBT_AC_BITS_CMD_FREEZE_BUFFER_MASK        0x01
   #define  Si2183_ISDBT_AC_BITS_CMD_FREEZE_BUFFER_MIN         0
   #define  Si2183_ISDBT_AC_BITS_CMD_FREEZE_BUFFER_MAX         1
    #define Si2183_ISDBT_AC_BITS_CMD_FREEZE_BUFFER_FREEZE    1
    #define Si2183_ISDBT_AC_BITS_CMD_FREEZE_BUFFER_UNFREEZE  0
   /* ISDBT_AC_BITS command, DATA1 field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA1_LSB         0
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA1_MASK        0xff
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA1_DATA1_MIN  0
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA1_DATA1_MAX  255
   /* ISDBT_AC_BITS command, DATA10 field definition (address 10, size 8, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA10_LSB         0
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA10_MASK        0xff
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA10_DATA10_MIN  0
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA10_DATA10_MAX  255
   /* ISDBT_AC_BITS command, DATA11 field definition (address 11, size 8, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA11_LSB         0
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA11_MASK        0xff
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA11_DATA11_MIN  0
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA11_DATA11_MAX  255
   /* ISDBT_AC_BITS command, DATA12 field definition (address 12, size 8, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA12_LSB         0
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA12_MASK        0xff
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA12_DATA12_MIN  0
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA12_DATA12_MAX  255
   /* ISDBT_AC_BITS command, DATA13 field definition (address 13, size 8, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA13_LSB         0
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA13_MASK        0xff
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA13_DATA13_MIN  0
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA13_DATA13_MAX  255
   /* ISDBT_AC_BITS command, DATA14 field definition (address 14, size 8, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA14_LSB         0
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA14_MASK        0xff
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA14_DATA14_MIN  0
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA14_DATA14_MAX  255
   /* ISDBT_AC_BITS command, DATA15 field definition (address 15, size 8, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA15_LSB         0
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA15_MASK        0xff
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA15_DATA15_MIN  0
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA15_DATA15_MAX  255
   /* ISDBT_AC_BITS command, DATA2 field definition (address 2, size 8, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA2_LSB         0
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA2_MASK        0xff
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA2_DATA2_MIN  0
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA2_DATA2_MAX  255
   /* ISDBT_AC_BITS command, DATA3 field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA3_LSB         0
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA3_MASK        0xff
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA3_DATA3_MIN  0
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA3_DATA3_MAX  255
   /* ISDBT_AC_BITS command, DATA4 field definition (address 4, size 8, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA4_LSB         0
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA4_MASK        0xff
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA4_DATA4_MIN  0
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA4_DATA4_MAX  255
   /* ISDBT_AC_BITS command, DATA5 field definition (address 5, size 8, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA5_LSB         0
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA5_MASK        0xff
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA5_DATA5_MIN  0
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA5_DATA5_MAX  255
   /* ISDBT_AC_BITS command, DATA6 field definition (address 6, size 8, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA6_LSB         0
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA6_MASK        0xff
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA6_DATA6_MIN  0
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA6_DATA6_MAX  255
   /* ISDBT_AC_BITS command, DATA7 field definition (address 7, size 8, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA7_LSB         0
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA7_MASK        0xff
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA7_DATA7_MIN  0
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA7_DATA7_MAX  255
   /* ISDBT_AC_BITS command, DATA8 field definition (address 8, size 8, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA8_LSB         0
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA8_MASK        0xff
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA8_DATA8_MIN  0
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA8_DATA8_MAX  255
   /* ISDBT_AC_BITS command, DATA9 field definition (address 9, size 8, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA9_LSB         0
   #define  Si2183_ISDBT_AC_BITS_RESPONSE_DATA9_MASK        0xff
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA9_DATA9_MIN  0
    #define Si2183_ISDBT_AC_BITS_RESPONSE_DATA9_DATA9_MAX  255

#endif /* Si2183_ISDBT_AC_BITS_CMD */

/* Si2183_ISDBT_LAYER_INFO command definition */
#define   Si2183_ISDBT_LAYER_INFO_CMD 0xa5

#ifdef    Si2183_ISDBT_LAYER_INFO_CMD
  #define Si2183_ISDBT_LAYER_INFO_CMD_CODE 0x0100a5

    typedef struct { /* Si2183_ISDBT_LAYER_INFO_CMD_struct */
     unsigned char   layer_index;
   } Si2183_ISDBT_LAYER_INFO_CMD_struct;


    typedef struct { /* Si2183_ISDBT_LAYER_INFO_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   constellation;
      unsigned char   code_rate;
      unsigned char   il;
      unsigned char   nb_seg;
   }  Si2183_ISDBT_LAYER_INFO_CMD_REPLY_struct;

   /* ISDBT_LAYER_INFO command, LAYER_INDEX field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_ISDBT_LAYER_INFO_CMD_LAYER_INDEX_LSB         0
   #define  Si2183_ISDBT_LAYER_INFO_CMD_LAYER_INDEX_MASK        0xff
   #define  Si2183_ISDBT_LAYER_INFO_CMD_LAYER_INDEX_MIN         0
   #define  Si2183_ISDBT_LAYER_INFO_CMD_LAYER_INDEX_MAX         2
    #define Si2183_ISDBT_LAYER_INFO_CMD_LAYER_INDEX_A  0
    #define Si2183_ISDBT_LAYER_INFO_CMD_LAYER_INDEX_B  1
    #define Si2183_ISDBT_LAYER_INFO_CMD_LAYER_INDEX_C  2
   /* ISDBT_LAYER_INFO command, CONSTELLATION field definition (address 1, size 4, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_LAYER_INFO_RESPONSE_CONSTELLATION_LSB         0
   #define  Si2183_ISDBT_LAYER_INFO_RESPONSE_CONSTELLATION_MASK        0x0f
    #define Si2183_ISDBT_LAYER_INFO_RESPONSE_CONSTELLATION_DQPSK  4
    #define Si2183_ISDBT_LAYER_INFO_RESPONSE_CONSTELLATION_QAM16  7
    #define Si2183_ISDBT_LAYER_INFO_RESPONSE_CONSTELLATION_QAM64  9
    #define Si2183_ISDBT_LAYER_INFO_RESPONSE_CONSTELLATION_QPSK   3
   /* ISDBT_LAYER_INFO command, CODE_RATE field definition (address 1, size 3, lsb 4, unsigned)*/
   #define  Si2183_ISDBT_LAYER_INFO_RESPONSE_CODE_RATE_LSB         4
   #define  Si2183_ISDBT_LAYER_INFO_RESPONSE_CODE_RATE_MASK        0x07
    #define Si2183_ISDBT_LAYER_INFO_RESPONSE_CODE_RATE_1_2  1
    #define Si2183_ISDBT_LAYER_INFO_RESPONSE_CODE_RATE_2_3  2
    #define Si2183_ISDBT_LAYER_INFO_RESPONSE_CODE_RATE_3_4  3
    #define Si2183_ISDBT_LAYER_INFO_RESPONSE_CODE_RATE_5_6  5
    #define Si2183_ISDBT_LAYER_INFO_RESPONSE_CODE_RATE_7_8  7
   /* ISDBT_LAYER_INFO command, IL field definition (address 2, size 3, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_LAYER_INFO_RESPONSE_IL_LSB         0
   #define  Si2183_ISDBT_LAYER_INFO_RESPONSE_IL_MASK        0x07
   /* ISDBT_LAYER_INFO command, NB_SEG field definition (address 2, size 4, lsb 3, unsigned)*/
   #define  Si2183_ISDBT_LAYER_INFO_RESPONSE_NB_SEG_LSB         3
   #define  Si2183_ISDBT_LAYER_INFO_RESPONSE_NB_SEG_MASK        0x0f

#endif /* Si2183_ISDBT_LAYER_INFO_CMD */

/* Si2183_ISDBT_STATUS command definition */
#define   Si2183_ISDBT_STATUS_CMD 0xa4

#ifdef    Si2183_ISDBT_STATUS_CMD
  #define Si2183_ISDBT_STATUS_CMD_CODE 0x0100a4

    typedef struct { /* Si2183_ISDBT_STATUS_CMD_struct */
     unsigned char   intack;
   } Si2183_ISDBT_STATUS_CMD_struct;


    typedef struct { /* Si2183_ISDBT_STATUS_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   pclint;
      unsigned char   dlint;
      unsigned char   berint;
      unsigned char   uncorint;
      unsigned char   notisdbtint;
      unsigned char   ewbsint;
      unsigned char   nb_seg_c;
      unsigned char   partial_flag;
      unsigned char   syst_id;
      unsigned char   reserved_msb;
      unsigned char   phase_shift_corr;
      unsigned char   emergency_flag;
      unsigned char   reserved_lsb;
      unsigned char   dl_c;
      unsigned char   dl_b;
      unsigned char   dl_a;
      unsigned char   pcl;
      unsigned char   dl;
      unsigned char   ber;
      unsigned char   uncor;
      unsigned char   notisdbt;
      unsigned char   ewbs;
      unsigned char   cnr;
               int    afc_freq;
               int    timing_offset;
      unsigned char   fft_mode;
      unsigned char   guard_int;
      unsigned char   sp_inv;
      unsigned char   nb_seg_a;
      unsigned char   nb_seg_b;
   }  Si2183_ISDBT_STATUS_CMD_REPLY_struct;

   /* ISDBT_STATUS command, INTACK field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2183_ISDBT_STATUS_CMD_INTACK_LSB         0
   #define  Si2183_ISDBT_STATUS_CMD_INTACK_MASK        0x01
   #define  Si2183_ISDBT_STATUS_CMD_INTACK_MIN         0
   #define  Si2183_ISDBT_STATUS_CMD_INTACK_MAX         1
    #define Si2183_ISDBT_STATUS_CMD_INTACK_CLEAR  1
    #define Si2183_ISDBT_STATUS_CMD_INTACK_OK     0
   /* ISDBT_STATUS command, PCLINT field definition (address 1, size 1, lsb 1, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_PCLINT_LSB         1
   #define  Si2183_ISDBT_STATUS_RESPONSE_PCLINT_MASK        0x01
    #define Si2183_ISDBT_STATUS_RESPONSE_PCLINT_CHANGED    1
    #define Si2183_ISDBT_STATUS_RESPONSE_PCLINT_NO_CHANGE  0
   /* ISDBT_STATUS command, DLINT field definition (address 1, size 1, lsb 2, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_DLINT_LSB         2
   #define  Si2183_ISDBT_STATUS_RESPONSE_DLINT_MASK        0x01
    #define Si2183_ISDBT_STATUS_RESPONSE_DLINT_CHANGED    1
    #define Si2183_ISDBT_STATUS_RESPONSE_DLINT_NO_CHANGE  0
   /* ISDBT_STATUS command, BERINT field definition (address 1, size 1, lsb 3, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_BERINT_LSB         3
   #define  Si2183_ISDBT_STATUS_RESPONSE_BERINT_MASK        0x01
    #define Si2183_ISDBT_STATUS_RESPONSE_BERINT_CHANGED    1
    #define Si2183_ISDBT_STATUS_RESPONSE_BERINT_NO_CHANGE  0
   /* ISDBT_STATUS command, UNCORINT field definition (address 1, size 1, lsb 4, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_UNCORINT_LSB         4
   #define  Si2183_ISDBT_STATUS_RESPONSE_UNCORINT_MASK        0x01
    #define Si2183_ISDBT_STATUS_RESPONSE_UNCORINT_CHANGED    1
    #define Si2183_ISDBT_STATUS_RESPONSE_UNCORINT_NO_CHANGE  0
   /* ISDBT_STATUS command, NOTISDBTINT field definition (address 1, size 1, lsb 5, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_NOTISDBTINT_LSB         5
   #define  Si2183_ISDBT_STATUS_RESPONSE_NOTISDBTINT_MASK        0x01
    #define Si2183_ISDBT_STATUS_RESPONSE_NOTISDBTINT_CHANGED    1
    #define Si2183_ISDBT_STATUS_RESPONSE_NOTISDBTINT_NO_CHANGE  0
   /* ISDBT_STATUS command, EWBSINT field definition (address 1, size 1, lsb 7, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_EWBSINT_LSB         7
   #define  Si2183_ISDBT_STATUS_RESPONSE_EWBSINT_MASK        0x01
    #define Si2183_ISDBT_STATUS_RESPONSE_EWBSINT_CHANGED    1
    #define Si2183_ISDBT_STATUS_RESPONSE_EWBSINT_NO_CHANGE  0
   /* ISDBT_STATUS command, NB_SEG_C field definition (address 10, size 4, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_NB_SEG_C_LSB         0
   #define  Si2183_ISDBT_STATUS_RESPONSE_NB_SEG_C_MASK        0x0f
   /* ISDBT_STATUS command, PARTIAL_FLAG field definition (address 10, size 1, lsb 4, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_PARTIAL_FLAG_LSB         4
   #define  Si2183_ISDBT_STATUS_RESPONSE_PARTIAL_FLAG_MASK        0x01
   /* ISDBT_STATUS command, SYST_ID field definition (address 10, size 2, lsb 5, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_SYST_ID_LSB         5
   #define  Si2183_ISDBT_STATUS_RESPONSE_SYST_ID_MASK        0x03
    #define Si2183_ISDBT_STATUS_RESPONSE_SYST_ID_ISDB_T     0
    #define Si2183_ISDBT_STATUS_RESPONSE_SYST_ID_ISDB_T_SB  1
   /* ISDBT_STATUS command, RESERVED_MSB field definition (address 11, size 4, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_RESERVED_MSB_LSB         0
   #define  Si2183_ISDBT_STATUS_RESPONSE_RESERVED_MSB_MASK        0x0f
   /* ISDBT_STATUS command, PHASE_SHIFT_CORR field definition (address 11, size 3, lsb 4, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_PHASE_SHIFT_CORR_LSB         4
   #define  Si2183_ISDBT_STATUS_RESPONSE_PHASE_SHIFT_CORR_MASK        0x07
   /* ISDBT_STATUS command, EMERGENCY_FLAG field definition (address 11, size 1, lsb 7, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_EMERGENCY_FLAG_LSB         7
   #define  Si2183_ISDBT_STATUS_RESPONSE_EMERGENCY_FLAG_MASK        0x01
    #define Si2183_ISDBT_STATUS_RESPONSE_EMERGENCY_FLAG_NORMAL   0
    #define Si2183_ISDBT_STATUS_RESPONSE_EMERGENCY_FLAG_WARNING  1
   /* ISDBT_STATUS command, RESERVED_LSB field definition (address 12, size 8, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_RESERVED_LSB_LSB         0
   #define  Si2183_ISDBT_STATUS_RESPONSE_RESERVED_LSB_MASK        0xff
   /* ISDBT_STATUS command, DL_C field definition (address 13, size 1, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_DL_C_LSB         0
   #define  Si2183_ISDBT_STATUS_RESPONSE_DL_C_MASK        0x01
    #define Si2183_ISDBT_STATUS_RESPONSE_DL_C_LOCKED   1
    #define Si2183_ISDBT_STATUS_RESPONSE_DL_C_NO_LOCK  0
   /* ISDBT_STATUS command, DL_B field definition (address 13, size 1, lsb 1, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_DL_B_LSB         1
   #define  Si2183_ISDBT_STATUS_RESPONSE_DL_B_MASK        0x01
    #define Si2183_ISDBT_STATUS_RESPONSE_DL_B_LOCKED   1
    #define Si2183_ISDBT_STATUS_RESPONSE_DL_B_NO_LOCK  0
   /* ISDBT_STATUS command, DL_A field definition (address 13, size 1, lsb 2, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_DL_A_LSB         2
   #define  Si2183_ISDBT_STATUS_RESPONSE_DL_A_MASK        0x01
    #define Si2183_ISDBT_STATUS_RESPONSE_DL_A_LOCKED   1
    #define Si2183_ISDBT_STATUS_RESPONSE_DL_A_NO_LOCK  0
   /* ISDBT_STATUS command, PCL field definition (address 2, size 1, lsb 1, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_PCL_LSB         1
   #define  Si2183_ISDBT_STATUS_RESPONSE_PCL_MASK        0x01
    #define Si2183_ISDBT_STATUS_RESPONSE_PCL_LOCKED   1
    #define Si2183_ISDBT_STATUS_RESPONSE_PCL_NO_LOCK  0
   /* ISDBT_STATUS command, DL field definition (address 2, size 1, lsb 2, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_DL_LSB         2
   #define  Si2183_ISDBT_STATUS_RESPONSE_DL_MASK        0x01
    #define Si2183_ISDBT_STATUS_RESPONSE_DL_LOCKED   1
    #define Si2183_ISDBT_STATUS_RESPONSE_DL_NO_LOCK  0
   /* ISDBT_STATUS command, BER field definition (address 2, size 1, lsb 3, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_BER_LSB         3
   #define  Si2183_ISDBT_STATUS_RESPONSE_BER_MASK        0x01
    #define Si2183_ISDBT_STATUS_RESPONSE_BER_BER_ABOVE  1
    #define Si2183_ISDBT_STATUS_RESPONSE_BER_BER_BELOW  0
   /* ISDBT_STATUS command, UNCOR field definition (address 2, size 1, lsb 4, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_UNCOR_LSB         4
   #define  Si2183_ISDBT_STATUS_RESPONSE_UNCOR_MASK        0x01
    #define Si2183_ISDBT_STATUS_RESPONSE_UNCOR_NO_UNCOR_FOUND  0
    #define Si2183_ISDBT_STATUS_RESPONSE_UNCOR_UNCOR_FOUND     1
   /* ISDBT_STATUS command, NOTISDBT field definition (address 2, size 1, lsb 5, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_NOTISDBT_LSB         5
   #define  Si2183_ISDBT_STATUS_RESPONSE_NOTISDBT_MASK        0x01
    #define Si2183_ISDBT_STATUS_RESPONSE_NOTISDBT_ISDBT      0
    #define Si2183_ISDBT_STATUS_RESPONSE_NOTISDBT_NOT_ISDBT  1
   /* ISDBT_STATUS command, EWBS field definition (address 2, size 1, lsb 7, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_EWBS_LSB         7
   #define  Si2183_ISDBT_STATUS_RESPONSE_EWBS_MASK        0x01
    #define Si2183_ISDBT_STATUS_RESPONSE_EWBS_NORMAL   0
    #define Si2183_ISDBT_STATUS_RESPONSE_EWBS_WARNING  1
   /* ISDBT_STATUS command, CNR field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_CNR_LSB         0
   #define  Si2183_ISDBT_STATUS_RESPONSE_CNR_MASK        0xff
   /* ISDBT_STATUS command, AFC_FREQ field definition (address 4, size 16, lsb 0, signed)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_AFC_FREQ_LSB         0
   #define  Si2183_ISDBT_STATUS_RESPONSE_AFC_FREQ_MASK        0xffff
   #define  Si2183_ISDBT_STATUS_RESPONSE_AFC_FREQ_SHIFT       16
   /* ISDBT_STATUS command, TIMING_OFFSET field definition (address 6, size 16, lsb 0, signed)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_TIMING_OFFSET_LSB         0
   #define  Si2183_ISDBT_STATUS_RESPONSE_TIMING_OFFSET_MASK        0xffff
   #define  Si2183_ISDBT_STATUS_RESPONSE_TIMING_OFFSET_SHIFT       16
   /* ISDBT_STATUS command, FFT_MODE field definition (address 8, size 4, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_FFT_MODE_LSB         0
   #define  Si2183_ISDBT_STATUS_RESPONSE_FFT_MODE_MASK        0x0f
    #define Si2183_ISDBT_STATUS_RESPONSE_FFT_MODE_2K  11
    #define Si2183_ISDBT_STATUS_RESPONSE_FFT_MODE_4K  12
    #define Si2183_ISDBT_STATUS_RESPONSE_FFT_MODE_8K  13
   /* ISDBT_STATUS command, GUARD_INT field definition (address 8, size 3, lsb 4, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_GUARD_INT_LSB         4
   #define  Si2183_ISDBT_STATUS_RESPONSE_GUARD_INT_MASK        0x07
    #define Si2183_ISDBT_STATUS_RESPONSE_GUARD_INT_1_16  2
    #define Si2183_ISDBT_STATUS_RESPONSE_GUARD_INT_1_32  1
    #define Si2183_ISDBT_STATUS_RESPONSE_GUARD_INT_1_4   4
    #define Si2183_ISDBT_STATUS_RESPONSE_GUARD_INT_1_8   3
   /* ISDBT_STATUS command, SP_INV field definition (address 8, size 1, lsb 7, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_SP_INV_LSB         7
   #define  Si2183_ISDBT_STATUS_RESPONSE_SP_INV_MASK        0x01
    #define Si2183_ISDBT_STATUS_RESPONSE_SP_INV_INVERTED  1
    #define Si2183_ISDBT_STATUS_RESPONSE_SP_INV_NORMAL    0
   /* ISDBT_STATUS command, NB_SEG_A field definition (address 9, size 4, lsb 0, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_NB_SEG_A_LSB         0
   #define  Si2183_ISDBT_STATUS_RESPONSE_NB_SEG_A_MASK        0x0f
   /* ISDBT_STATUS command, NB_SEG_B field definition (address 9, size 4, lsb 4, unsigned)*/
   #define  Si2183_ISDBT_STATUS_RESPONSE_NB_SEG_B_LSB         4
   #define  Si2183_ISDBT_STATUS_RESPONSE_NB_SEG_B_MASK        0x0f

#endif /* Si2183_ISDBT_STATUS_CMD */

#endif /* DEMOD_ISDB_T */

#ifdef    DEMOD_MCNS
/* Si2183_MCNS_STATUS command definition */
#define   Si2183_MCNS_STATUS_CMD 0x98

#ifdef    Si2183_MCNS_STATUS_CMD
  #define Si2183_MCNS_STATUS_CMD_CODE 0x010098

    typedef struct { /* Si2183_MCNS_STATUS_CMD_struct */
     unsigned char   intack;
   } Si2183_MCNS_STATUS_CMD_struct;


    typedef struct { /* Si2183_MCNS_STATUS_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   pclint;
      unsigned char   dlint;
      unsigned char   berint;
      unsigned char   uncorint;
      unsigned char   pcl;
      unsigned char   dl;
      unsigned char   ber;
      unsigned char   uncor;
      unsigned char   cnr;
               int    afc_freq;
               int    timing_offset;
      unsigned char   constellation;
      unsigned char   sp_inv;
      unsigned char   interleaving;
   }  Si2183_MCNS_STATUS_CMD_REPLY_struct;

   /* MCNS_STATUS command, INTACK field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2183_MCNS_STATUS_CMD_INTACK_LSB         0
   #define  Si2183_MCNS_STATUS_CMD_INTACK_MASK        0x01
   #define  Si2183_MCNS_STATUS_CMD_INTACK_MIN         0
   #define  Si2183_MCNS_STATUS_CMD_INTACK_MAX         1
    #define Si2183_MCNS_STATUS_CMD_INTACK_CLEAR  1
    #define Si2183_MCNS_STATUS_CMD_INTACK_OK     0
   /* MCNS_STATUS command, PCLINT field definition (address 1, size 1, lsb 1, unsigned)*/
   #define  Si2183_MCNS_STATUS_RESPONSE_PCLINT_LSB         1
   #define  Si2183_MCNS_STATUS_RESPONSE_PCLINT_MASK        0x01
    #define Si2183_MCNS_STATUS_RESPONSE_PCLINT_CHANGED    1
    #define Si2183_MCNS_STATUS_RESPONSE_PCLINT_NO_CHANGE  0
   /* MCNS_STATUS command, DLINT field definition (address 1, size 1, lsb 2, unsigned)*/
   #define  Si2183_MCNS_STATUS_RESPONSE_DLINT_LSB         2
   #define  Si2183_MCNS_STATUS_RESPONSE_DLINT_MASK        0x01
    #define Si2183_MCNS_STATUS_RESPONSE_DLINT_CHANGED    1
    #define Si2183_MCNS_STATUS_RESPONSE_DLINT_NO_CHANGE  0
   /* MCNS_STATUS command, BERINT field definition (address 1, size 1, lsb 3, unsigned)*/
   #define  Si2183_MCNS_STATUS_RESPONSE_BERINT_LSB         3
   #define  Si2183_MCNS_STATUS_RESPONSE_BERINT_MASK        0x01
    #define Si2183_MCNS_STATUS_RESPONSE_BERINT_CHANGED    1
    #define Si2183_MCNS_STATUS_RESPONSE_BERINT_NO_CHANGE  0
   /* MCNS_STATUS command, UNCORINT field definition (address 1, size 1, lsb 4, unsigned)*/
   #define  Si2183_MCNS_STATUS_RESPONSE_UNCORINT_LSB         4
   #define  Si2183_MCNS_STATUS_RESPONSE_UNCORINT_MASK        0x01
    #define Si2183_MCNS_STATUS_RESPONSE_UNCORINT_CHANGED    1
    #define Si2183_MCNS_STATUS_RESPONSE_UNCORINT_NO_CHANGE  0
   /* MCNS_STATUS command, PCL field definition (address 2, size 1, lsb 1, unsigned)*/
   #define  Si2183_MCNS_STATUS_RESPONSE_PCL_LSB         1
   #define  Si2183_MCNS_STATUS_RESPONSE_PCL_MASK        0x01
    #define Si2183_MCNS_STATUS_RESPONSE_PCL_LOCKED   1
    #define Si2183_MCNS_STATUS_RESPONSE_PCL_NO_LOCK  0
   /* MCNS_STATUS command, DL field definition (address 2, size 1, lsb 2, unsigned)*/
   #define  Si2183_MCNS_STATUS_RESPONSE_DL_LSB         2
   #define  Si2183_MCNS_STATUS_RESPONSE_DL_MASK        0x01
    #define Si2183_MCNS_STATUS_RESPONSE_DL_LOCKED   1
    #define Si2183_MCNS_STATUS_RESPONSE_DL_NO_LOCK  0
   /* MCNS_STATUS command, BER field definition (address 2, size 1, lsb 3, unsigned)*/
   #define  Si2183_MCNS_STATUS_RESPONSE_BER_LSB         3
   #define  Si2183_MCNS_STATUS_RESPONSE_BER_MASK        0x01
    #define Si2183_MCNS_STATUS_RESPONSE_BER_BER_ABOVE  1
    #define Si2183_MCNS_STATUS_RESPONSE_BER_BER_BELOW  0
   /* MCNS_STATUS command, UNCOR field definition (address 2, size 1, lsb 4, unsigned)*/
   #define  Si2183_MCNS_STATUS_RESPONSE_UNCOR_LSB         4
   #define  Si2183_MCNS_STATUS_RESPONSE_UNCOR_MASK        0x01
    #define Si2183_MCNS_STATUS_RESPONSE_UNCOR_NO_UNCOR_FOUND  0
    #define Si2183_MCNS_STATUS_RESPONSE_UNCOR_UNCOR_FOUND     1
   /* MCNS_STATUS command, CNR field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si2183_MCNS_STATUS_RESPONSE_CNR_LSB         0
   #define  Si2183_MCNS_STATUS_RESPONSE_CNR_MASK        0xff
   /* MCNS_STATUS command, AFC_FREQ field definition (address 4, size 16, lsb 0, signed)*/
   #define  Si2183_MCNS_STATUS_RESPONSE_AFC_FREQ_LSB         0
   #define  Si2183_MCNS_STATUS_RESPONSE_AFC_FREQ_MASK        0xffff
   #define  Si2183_MCNS_STATUS_RESPONSE_AFC_FREQ_SHIFT       16
   /* MCNS_STATUS command, TIMING_OFFSET field definition (address 6, size 16, lsb 0, signed)*/
   #define  Si2183_MCNS_STATUS_RESPONSE_TIMING_OFFSET_LSB         0
   #define  Si2183_MCNS_STATUS_RESPONSE_TIMING_OFFSET_MASK        0xffff
   #define  Si2183_MCNS_STATUS_RESPONSE_TIMING_OFFSET_SHIFT       16
   /* MCNS_STATUS command, CONSTELLATION field definition (address 8, size 6, lsb 0, unsigned)*/
   #define  Si2183_MCNS_STATUS_RESPONSE_CONSTELLATION_LSB         0
   #define  Si2183_MCNS_STATUS_RESPONSE_CONSTELLATION_MASK        0x3f
    #define Si2183_MCNS_STATUS_RESPONSE_CONSTELLATION_QAM256  11
    #define Si2183_MCNS_STATUS_RESPONSE_CONSTELLATION_QAM64   9
   /* MCNS_STATUS command, SP_INV field definition (address 8, size 1, lsb 6, unsigned)*/
   #define  Si2183_MCNS_STATUS_RESPONSE_SP_INV_LSB         6
   #define  Si2183_MCNS_STATUS_RESPONSE_SP_INV_MASK        0x01
    #define Si2183_MCNS_STATUS_RESPONSE_SP_INV_INVERTED  1
    #define Si2183_MCNS_STATUS_RESPONSE_SP_INV_NORMAL    0
   /* MCNS_STATUS command, INTERLEAVING field definition (address 9, size 4, lsb 0, unsigned)*/
   #define  Si2183_MCNS_STATUS_RESPONSE_INTERLEAVING_LSB         0
   #define  Si2183_MCNS_STATUS_RESPONSE_INTERLEAVING_MASK        0x0f
    #define Si2183_MCNS_STATUS_RESPONSE_INTERLEAVING_0__128_1      0
    #define Si2183_MCNS_STATUS_RESPONSE_INTERLEAVING_10__128_6     10
    #define Si2183_MCNS_STATUS_RESPONSE_INTERLEAVING_11__RESERVED  11
    #define Si2183_MCNS_STATUS_RESPONSE_INTERLEAVING_12__128_7     12
    #define Si2183_MCNS_STATUS_RESPONSE_INTERLEAVING_13__RESERVED  13
    #define Si2183_MCNS_STATUS_RESPONSE_INTERLEAVING_14__128_8     14
    #define Si2183_MCNS_STATUS_RESPONSE_INTERLEAVING_15__RESERVED  15
    #define Si2183_MCNS_STATUS_RESPONSE_INTERLEAVING_1__128_1      1
    #define Si2183_MCNS_STATUS_RESPONSE_INTERLEAVING_2__128_2      2
    #define Si2183_MCNS_STATUS_RESPONSE_INTERLEAVING_3__64_2       3
    #define Si2183_MCNS_STATUS_RESPONSE_INTERLEAVING_4__128_3      4
    #define Si2183_MCNS_STATUS_RESPONSE_INTERLEAVING_5__32_4       5
    #define Si2183_MCNS_STATUS_RESPONSE_INTERLEAVING_6__128_4      6
    #define Si2183_MCNS_STATUS_RESPONSE_INTERLEAVING_7__16_8       7
    #define Si2183_MCNS_STATUS_RESPONSE_INTERLEAVING_8__128_5      8
    #define Si2183_MCNS_STATUS_RESPONSE_INTERLEAVING_9__8_16       9

#endif /* Si2183_MCNS_STATUS_CMD */

#endif /* DEMOD_MCNS */

/* Si2183_PART_INFO command definition */
#define   Si2183_PART_INFO_CMD 0x02

#ifdef    Si2183_PART_INFO_CMD
  #define Si2183_PART_INFO_CMD_CODE 0x010002

    typedef struct { /* Si2183_PART_INFO_CMD_struct */
         unsigned char   nothing;   } Si2183_PART_INFO_CMD_struct;


    typedef struct { /* Si2183_PART_INFO_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   chiprev;
      unsigned char   romid;
      unsigned char   rx;
      unsigned char   part;
      unsigned char   pmajor;
      unsigned char   pminor;
      unsigned char   pbuild;
      unsigned int    reserved;
      unsigned long   serial;
   }  Si2183_PART_INFO_CMD_REPLY_struct;

   /* PART_INFO command, CHIPREV field definition (address 1, size 4, lsb 0, unsigned)*/
   #define  Si2183_PART_INFO_RESPONSE_CHIPREV_LSB         0
   #define  Si2183_PART_INFO_RESPONSE_CHIPREV_MASK        0x0f
    #define Si2183_PART_INFO_RESPONSE_CHIPREV_A  1
    #define Si2183_PART_INFO_RESPONSE_CHIPREV_B  2
    #define Si2183_PART_INFO_RESPONSE_CHIPREV_C  3
    #define Si2183_PART_INFO_RESPONSE_CHIPREV_D  4
    #define Si2183_PART_INFO_RESPONSE_CHIPREV_E  5
   /* PART_INFO command, ROMID field definition (address 12, size 8, lsb 0, unsigned)*/
   #define  Si2183_PART_INFO_RESPONSE_ROMID_LSB         0
   #define  Si2183_PART_INFO_RESPONSE_ROMID_MASK        0xff
   /* PART_INFO command, RX field definition (address 13, size 1, lsb 7, unsigned)*/
   #define  Si2183_PART_INFO_RESPONSE_RX_LSB         7
   #define  Si2183_PART_INFO_RESPONSE_RX_MASK        0x01
    #define Si2183_PART_INFO_RESPONSE_RX_RX          1
    #define Si2183_PART_INFO_RESPONSE_RX_STANDALONE  0
   /* PART_INFO command, PART field definition (address 2, size 8, lsb 0, unsigned)*/
   #define  Si2183_PART_INFO_RESPONSE_PART_LSB         0
   #define  Si2183_PART_INFO_RESPONSE_PART_MASK        0xff
   /* PART_INFO command, PMAJOR field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si2183_PART_INFO_RESPONSE_PMAJOR_LSB         0
   #define  Si2183_PART_INFO_RESPONSE_PMAJOR_MASK        0xff
   /* PART_INFO command, PMINOR field definition (address 4, size 8, lsb 0, unsigned)*/
   #define  Si2183_PART_INFO_RESPONSE_PMINOR_LSB         0
   #define  Si2183_PART_INFO_RESPONSE_PMINOR_MASK        0xff
   /* PART_INFO command, PBUILD field definition (address 5, size 8, lsb 0, unsigned)*/
   #define  Si2183_PART_INFO_RESPONSE_PBUILD_LSB         0
   #define  Si2183_PART_INFO_RESPONSE_PBUILD_MASK        0xff
   /* PART_INFO command, RESERVED field definition (address 6, size 16, lsb 0, unsigned)*/
   #define  Si2183_PART_INFO_RESPONSE_RESERVED_LSB         0
   #define  Si2183_PART_INFO_RESPONSE_RESERVED_MASK        0xffff
   /* PART_INFO command, SERIAL field definition (address 8, size 32, lsb 0, unsigned)*/
   #define  Si2183_PART_INFO_RESPONSE_SERIAL_LSB         0
   #define  Si2183_PART_INFO_RESPONSE_SERIAL_MASK        0xffffffff

#endif /* Si2183_PART_INFO_CMD */

/* Si2183_POWER_DOWN command definition */
#define   Si2183_POWER_DOWN_CMD 0x13

#ifdef    Si2183_POWER_DOWN_CMD
  #define Si2183_POWER_DOWN_CMD_CODE 0x010013

    typedef struct { /* Si2183_POWER_DOWN_CMD_struct */
         unsigned char   nothing;   } Si2183_POWER_DOWN_CMD_struct;


    typedef struct { /* Si2183_POWER_DOWN_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
   }  Si2183_POWER_DOWN_CMD_REPLY_struct;

#endif /* Si2183_POWER_DOWN_CMD */

/* Si2183_POWER_UP command definition */
#define   Si2183_POWER_UP_CMD 0xc0

#ifdef    Si2183_POWER_UP_CMD
  #define Si2183_POWER_UP_CMD_CODE 0x0300c0

    typedef struct { /* Si2183_POWER_UP_CMD_struct */
     unsigned char   subcode;
     unsigned char   reset;
     unsigned char   reserved2;
     unsigned char   reserved4;
     unsigned char   reserved1;
     unsigned char   addr_mode;
     unsigned char   reserved5;
     unsigned char   func;
     unsigned char   clock_freq;
     unsigned char   ctsien;
     unsigned char   wake_up;
   } Si2183_POWER_UP_CMD_struct;


    typedef struct { /* Si2183_POWER_UP_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
   }  Si2183_POWER_UP_CMD_REPLY_struct;

   /* POWER_UP command, SUBCODE field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_POWER_UP_CMD_SUBCODE_LSB         0
   #define  Si2183_POWER_UP_CMD_SUBCODE_MASK        0xff
   #define  Si2183_POWER_UP_CMD_SUBCODE_MIN         6
   #define  Si2183_POWER_UP_CMD_SUBCODE_MAX         6
    #define Si2183_POWER_UP_CMD_SUBCODE_CODE  6
   /* POWER_UP command, RESET field definition (address 2,size 8, lsb 0, unsigned) */
   #define  Si2183_POWER_UP_CMD_RESET_LSB         0
   #define  Si2183_POWER_UP_CMD_RESET_MASK        0xff
   #define  Si2183_POWER_UP_CMD_RESET_MIN         1
   #define  Si2183_POWER_UP_CMD_RESET_MAX         8
    #define Si2183_POWER_UP_CMD_RESET_RESET   1
    #define Si2183_POWER_UP_CMD_RESET_RESUME  8
   /* POWER_UP command, RESERVED2 field definition (address 3,size 8, lsb 0, unsigned) */
   #define  Si2183_POWER_UP_CMD_RESERVED2_LSB         0
   #define  Si2183_POWER_UP_CMD_RESERVED2_MASK        0xff
   #define  Si2183_POWER_UP_CMD_RESERVED2_MIN         15
   #define  Si2183_POWER_UP_CMD_RESERVED2_MAX         15
    #define Si2183_POWER_UP_CMD_RESERVED2_RESERVED  15
   /* POWER_UP command, RESERVED4 field definition (address 4,size 8, lsb 0, unsigned) */
   #define  Si2183_POWER_UP_CMD_RESERVED4_LSB         0
   #define  Si2183_POWER_UP_CMD_RESERVED4_MASK        0xff
   #define  Si2183_POWER_UP_CMD_RESERVED4_MIN         0
   #define  Si2183_POWER_UP_CMD_RESERVED4_MAX         0
    #define Si2183_POWER_UP_CMD_RESERVED4_RESERVED  0
   /* POWER_UP command, RESERVED1 field definition (address 5,size 4, lsb 0, unsigned) */
   #define  Si2183_POWER_UP_CMD_RESERVED1_LSB         0
   #define  Si2183_POWER_UP_CMD_RESERVED1_MASK        0x0f
   #define  Si2183_POWER_UP_CMD_RESERVED1_MIN         0
   #define  Si2183_POWER_UP_CMD_RESERVED1_MAX         0
    #define Si2183_POWER_UP_CMD_RESERVED1_RESERVED  0
   /* POWER_UP command, ADDR_MODE field definition (address 5,size 1, lsb 4, unsigned) */
   #define  Si2183_POWER_UP_CMD_ADDR_MODE_LSB         4
   #define  Si2183_POWER_UP_CMD_ADDR_MODE_MASK        0x01
   #define  Si2183_POWER_UP_CMD_ADDR_MODE_MIN         0
   #define  Si2183_POWER_UP_CMD_ADDR_MODE_MAX         1
    #define Si2183_POWER_UP_CMD_ADDR_MODE_CAPTURE  1
    #define Si2183_POWER_UP_CMD_ADDR_MODE_CURRENT  0
   /* POWER_UP command, RESERVED5 field definition (address 5,size 1, lsb 5, unsigned) */
   #define  Si2183_POWER_UP_CMD_RESERVED5_LSB         5
   #define  Si2183_POWER_UP_CMD_RESERVED5_MASK        0x01
   #define  Si2183_POWER_UP_CMD_RESERVED5_MIN         1
   #define  Si2183_POWER_UP_CMD_RESERVED5_MAX         1
    #define Si2183_POWER_UP_CMD_RESERVED5_RESERVED  1
   /* POWER_UP command, FUNC field definition (address 6,size 4, lsb 0, unsigned) */
   #define  Si2183_POWER_UP_CMD_FUNC_LSB         0
   #define  Si2183_POWER_UP_CMD_FUNC_MASK        0x0f
   #define  Si2183_POWER_UP_CMD_FUNC_MIN         0
   #define  Si2183_POWER_UP_CMD_FUNC_MAX         1
    #define Si2183_POWER_UP_CMD_FUNC_BOOTLOADER  0
    #define Si2183_POWER_UP_CMD_FUNC_RESERVED    1
   /* POWER_UP command, CLOCK_FREQ field definition (address 6,size 3, lsb 4, unsigned) */
   #define  Si2183_POWER_UP_CMD_CLOCK_FREQ_LSB         4
   #define  Si2183_POWER_UP_CMD_CLOCK_FREQ_MASK        0x07
   #define  Si2183_POWER_UP_CMD_CLOCK_FREQ_MIN         0
   #define  Si2183_POWER_UP_CMD_CLOCK_FREQ_MAX         4
    #define Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_16MHZ  0
    #define Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_24MHZ  2
    #define Si2183_POWER_UP_CMD_CLOCK_FREQ_CLK_27MHZ  3
   /* POWER_UP command, CTSIEN field definition (address 6,size 1, lsb 7, unsigned) */
   #define  Si2183_POWER_UP_CMD_CTSIEN_LSB         7
   #define  Si2183_POWER_UP_CMD_CTSIEN_MASK        0x01
   #define  Si2183_POWER_UP_CMD_CTSIEN_MIN         0
   #define  Si2183_POWER_UP_CMD_CTSIEN_MAX         1
    #define Si2183_POWER_UP_CMD_CTSIEN_DISABLE  0
    #define Si2183_POWER_UP_CMD_CTSIEN_ENABLE   1
   /* POWER_UP command, WAKE_UP field definition (address 7,size 1, lsb 0, unsigned) */
   #define  Si2183_POWER_UP_CMD_WAKE_UP_LSB         0
   #define  Si2183_POWER_UP_CMD_WAKE_UP_MASK        0x01
   #define  Si2183_POWER_UP_CMD_WAKE_UP_MIN         1
   #define  Si2183_POWER_UP_CMD_WAKE_UP_MAX         1
    #define Si2183_POWER_UP_CMD_WAKE_UP_WAKE_UP  1
#endif /* Si2183_POWER_UP_CMD */

/* Si2183_RSSI_ADC command definition */
#define   Si2183_RSSI_ADC_CMD 0x17

#ifdef    Si2183_RSSI_ADC_CMD
  #define Si2183_RSSI_ADC_CMD_CODE 0x010017

    typedef struct { /* Si2183_RSSI_ADC_CMD_struct */
     unsigned char   on_off;
   } Si2183_RSSI_ADC_CMD_struct;


    typedef struct { /* Si2183_RSSI_ADC_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   level;
   }  Si2183_RSSI_ADC_CMD_REPLY_struct;

   /* RSSI_ADC command, ON_OFF field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2183_RSSI_ADC_CMD_ON_OFF_LSB         0
   #define  Si2183_RSSI_ADC_CMD_ON_OFF_MASK        0x01
   #define  Si2183_RSSI_ADC_CMD_ON_OFF_MIN         0
   #define  Si2183_RSSI_ADC_CMD_ON_OFF_MAX         1
    #define Si2183_RSSI_ADC_CMD_ON_OFF_OFF  0
    #define Si2183_RSSI_ADC_CMD_ON_OFF_ON   1
   /* RSSI_ADC command, LEVEL field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2183_RSSI_ADC_RESPONSE_LEVEL_LSB         0
   #define  Si2183_RSSI_ADC_RESPONSE_LEVEL_MASK        0xff

#endif /* Si2183_RSSI_ADC_CMD */

/* Si2183_SCAN_CTRL command definition */
#define   Si2183_SCAN_CTRL_CMD 0x31

#ifdef    Si2183_SCAN_CTRL_CMD
  #define Si2183_SCAN_CTRL_CMD_CODE 0x010031

    typedef struct { /* Si2183_SCAN_CTRL_CMD_struct */
     unsigned char   action;
     unsigned long   tuned_rf_freq;
   } Si2183_SCAN_CTRL_CMD_struct;


    typedef struct { /* Si2183_SCAN_CTRL_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
   }  Si2183_SCAN_CTRL_CMD_REPLY_struct;

   /* SCAN_CTRL command, ACTION field definition (address 1,size 4, lsb 0, unsigned) */
   #define  Si2183_SCAN_CTRL_CMD_ACTION_LSB         0
   #define  Si2183_SCAN_CTRL_CMD_ACTION_MASK        0x0f
   #define  Si2183_SCAN_CTRL_CMD_ACTION_MIN         1
   #define  Si2183_SCAN_CTRL_CMD_ACTION_MAX         3
    #define Si2183_SCAN_CTRL_CMD_ACTION_ABORT   3
    #define Si2183_SCAN_CTRL_CMD_ACTION_RESUME  2
    #define Si2183_SCAN_CTRL_CMD_ACTION_START   1
   /* SCAN_CTRL command, TUNED_RF_FREQ field definition (address 4,size 32, lsb 0, unsigned) */
   #define  Si2183_SCAN_CTRL_CMD_TUNED_RF_FREQ_LSB         0
   #define  Si2183_SCAN_CTRL_CMD_TUNED_RF_FREQ_MASK        0xffffffff
   #define  Si2183_SCAN_CTRL_CMD_TUNED_RF_FREQ_MIN         0
   #define  Si2183_SCAN_CTRL_CMD_TUNED_RF_FREQ_MAX         4294967
    #define Si2183_SCAN_CTRL_CMD_TUNED_RF_FREQ_TUNED_RF_FREQ_MIN  0
    #define Si2183_SCAN_CTRL_CMD_TUNED_RF_FREQ_TUNED_RF_FREQ_MAX  4294967
#endif /* Si2183_SCAN_CTRL_CMD */

/* Si2183_SCAN_STATUS command definition */
#define   Si2183_SCAN_STATUS_CMD 0x30

#ifdef    Si2183_SCAN_STATUS_CMD
  #define Si2183_SCAN_STATUS_CMD_CODE 0x010030

    typedef struct { /* Si2183_SCAN_STATUS_CMD_struct */
     unsigned char   intack;
   } Si2183_SCAN_STATUS_CMD_struct;


    typedef struct { /* Si2183_SCAN_STATUS_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   buzint;
      unsigned char   reqint;
      unsigned char   modulation;
      unsigned char   buz;
      unsigned char   req;
      unsigned char   scan_status;
      unsigned long   rf_freq;
      unsigned int    symb_rate;
   }  Si2183_SCAN_STATUS_CMD_REPLY_struct;

   /* SCAN_STATUS command, INTACK field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2183_SCAN_STATUS_CMD_INTACK_LSB         0
   #define  Si2183_SCAN_STATUS_CMD_INTACK_MASK        0x01
   #define  Si2183_SCAN_STATUS_CMD_INTACK_MIN         0
   #define  Si2183_SCAN_STATUS_CMD_INTACK_MAX         1
    #define Si2183_SCAN_STATUS_CMD_INTACK_CLEAR  1
    #define Si2183_SCAN_STATUS_CMD_INTACK_OK     0
   /* SCAN_STATUS command, BUZINT field definition (address 1, size 1, lsb 0, unsigned)*/
   #define  Si2183_SCAN_STATUS_RESPONSE_BUZINT_LSB         0
   #define  Si2183_SCAN_STATUS_RESPONSE_BUZINT_MASK        0x01
    #define Si2183_SCAN_STATUS_RESPONSE_BUZINT_CHANGED    1
    #define Si2183_SCAN_STATUS_RESPONSE_BUZINT_NO_CHANGE  0
   /* SCAN_STATUS command, REQINT field definition (address 1, size 1, lsb 1, unsigned)*/
   #define  Si2183_SCAN_STATUS_RESPONSE_REQINT_LSB         1
   #define  Si2183_SCAN_STATUS_RESPONSE_REQINT_MASK        0x01
    #define Si2183_SCAN_STATUS_RESPONSE_REQINT_CHANGED    1
    #define Si2183_SCAN_STATUS_RESPONSE_REQINT_NO_CHANGE  0
   /* SCAN_STATUS command, MODULATION field definition (address 10, size 4, lsb 0, unsigned)*/
   #define  Si2183_SCAN_STATUS_RESPONSE_MODULATION_LSB         0
   #define  Si2183_SCAN_STATUS_RESPONSE_MODULATION_MASK        0x0f
    #define Si2183_SCAN_STATUS_RESPONSE_MODULATION_DSS    10
    #define Si2183_SCAN_STATUS_RESPONSE_MODULATION_DVBC   3
    #define Si2183_SCAN_STATUS_RESPONSE_MODULATION_DVBC2  11
    #define Si2183_SCAN_STATUS_RESPONSE_MODULATION_DVBS   8
    #define Si2183_SCAN_STATUS_RESPONSE_MODULATION_DVBS2  9
    #define Si2183_SCAN_STATUS_RESPONSE_MODULATION_DVBT   2
    #define Si2183_SCAN_STATUS_RESPONSE_MODULATION_DVBT2  7
    #define Si2183_SCAN_STATUS_RESPONSE_MODULATION_ISDBT  4
    #define Si2183_SCAN_STATUS_RESPONSE_MODULATION_MCNS   1
   /* SCAN_STATUS command, BUZ field definition (address 2, size 1, lsb 0, unsigned)*/
   #define  Si2183_SCAN_STATUS_RESPONSE_BUZ_LSB         0
   #define  Si2183_SCAN_STATUS_RESPONSE_BUZ_MASK        0x01
    #define Si2183_SCAN_STATUS_RESPONSE_BUZ_BUSY  1
    #define Si2183_SCAN_STATUS_RESPONSE_BUZ_CTS   0
   /* SCAN_STATUS command, REQ field definition (address 2, size 1, lsb 1, unsigned)*/
   #define  Si2183_SCAN_STATUS_RESPONSE_REQ_LSB         1
   #define  Si2183_SCAN_STATUS_RESPONSE_REQ_MASK        0x01
    #define Si2183_SCAN_STATUS_RESPONSE_REQ_NO_REQUEST  0
    #define Si2183_SCAN_STATUS_RESPONSE_REQ_REQUEST     1
   /* SCAN_STATUS command, SCAN_STATUS field definition (address 3, size 6, lsb 0, unsigned)*/
   #define  Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_LSB         0
   #define  Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_MASK        0x3f
    #define Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_ANALOG_CHANNEL_FOUND   6
    #define Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_DEBUG                  63
    #define Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_DIGITAL_CHANNEL_FOUND  5
    #define Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_ENDED                  2
    #define Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_ERROR                  3
    #define Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_IDLE                   0
    #define Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_SEARCHING              1
    #define Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_TUNE_REQUEST           4
   /* SCAN_STATUS command, RF_FREQ field definition (address 4, size 32, lsb 0, unsigned)*/
   #define  Si2183_SCAN_STATUS_RESPONSE_RF_FREQ_LSB         0
   #define  Si2183_SCAN_STATUS_RESPONSE_RF_FREQ_MASK        0xffffffff
   /* SCAN_STATUS command, SYMB_RATE field definition (address 8, size 16, lsb 0, unsigned)*/
   #define  Si2183_SCAN_STATUS_RESPONSE_SYMB_RATE_LSB         0
   #define  Si2183_SCAN_STATUS_RESPONSE_SYMB_RATE_MASK        0xffff

#endif /* Si2183_SCAN_STATUS_CMD */

/* Si2183_SET_PROPERTY command definition */
#define   Si2183_SET_PROPERTY_CMD 0x14

#ifdef    Si2183_SET_PROPERTY_CMD
  #define Si2183_SET_PROPERTY_CMD_CODE 0x010014

    typedef struct { /* Si2183_SET_PROPERTY_CMD_struct */
     unsigned char   reserved;
     unsigned int    prop;
     unsigned int    data;
   } Si2183_SET_PROPERTY_CMD_struct;


    typedef struct { /* Si2183_SET_PROPERTY_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
      unsigned char   reserved;
      unsigned int    data;
   }  Si2183_SET_PROPERTY_CMD_REPLY_struct;

   /* SET_PROPERTY command, RESERVED field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_SET_PROPERTY_CMD_RESERVED_LSB         0
   #define  Si2183_SET_PROPERTY_CMD_RESERVED_MASK        0xff
   #define  Si2183_SET_PROPERTY_CMD_RESERVED_MIN         0
   #define  Si2183_SET_PROPERTY_CMD_RESERVED_MAX         255
   /* SET_PROPERTY command, PROP field definition (address 2,size 16, lsb 0, unsigned) */
   #define  Si2183_SET_PROPERTY_CMD_PROP_LSB         0
   #define  Si2183_SET_PROPERTY_CMD_PROP_MASK        0xffff
   #define  Si2183_SET_PROPERTY_CMD_PROP_MIN         0
   #define  Si2183_SET_PROPERTY_CMD_PROP_MAX         65535
    #define Si2183_SET_PROPERTY_CMD_PROP_PROP_MIN  0
    #define Si2183_SET_PROPERTY_CMD_PROP_PROP_MAX  65535
   /* SET_PROPERTY command, DATA field definition (address 4,size 16, lsb 0, unsigned) */
   #define  Si2183_SET_PROPERTY_CMD_DATA_LSB         0
   #define  Si2183_SET_PROPERTY_CMD_DATA_MASK        0xffff
   #define  Si2183_SET_PROPERTY_CMD_DATA_MIN         0
   #define  Si2183_SET_PROPERTY_CMD_DATA_MAX         65535
    #define Si2183_SET_PROPERTY_CMD_DATA_DATA_MIN  0
    #define Si2183_SET_PROPERTY_CMD_DATA_DATA_MAX  65535
   /* SET_PROPERTY command, RESERVED field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2183_SET_PROPERTY_RESPONSE_RESERVED_LSB         0
   #define  Si2183_SET_PROPERTY_RESPONSE_RESERVED_MASK        0xff
    #define Si2183_SET_PROPERTY_RESPONSE_RESERVED_RESERVED_MIN  0
    #define Si2183_SET_PROPERTY_RESPONSE_RESERVED_RESERVED_MAX  0
   /* SET_PROPERTY command, DATA field definition (address 2, size 16, lsb 0, unsigned)*/
   #define  Si2183_SET_PROPERTY_RESPONSE_DATA_LSB         0
   #define  Si2183_SET_PROPERTY_RESPONSE_DATA_MASK        0xffff

#endif /* Si2183_SET_PROPERTY_CMD */

/* Si2183_SPI_LINK command definition */
#define   Si2183_SPI_LINK_CMD 0xc0

#ifdef    Si2183_SPI_LINK_CMD
  #define Si2183_SPI_LINK_CMD_CODE 0x0400c0

    typedef struct { /* Si2183_SPI_LINK_CMD_struct */
     unsigned char   subcode;
     unsigned char   spi_pbl_key;
     unsigned char   spi_pbl_num;
     unsigned char   spi_conf_clk;
     unsigned char   spi_clk_pola;
     unsigned char   spi_conf_data;
     unsigned char   spi_data_dir;
     unsigned char   spi_enable;
   } Si2183_SPI_LINK_CMD_struct;


    typedef struct { /* Si2183_SPI_LINK_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
   }  Si2183_SPI_LINK_CMD_REPLY_struct;

   /* SPI_LINK command, SUBCODE field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_SPI_LINK_CMD_SUBCODE_LSB         0
   #define  Si2183_SPI_LINK_CMD_SUBCODE_MASK        0xff
   #define  Si2183_SPI_LINK_CMD_SUBCODE_MIN         56
   #define  Si2183_SPI_LINK_CMD_SUBCODE_MAX         56
    #define Si2183_SPI_LINK_CMD_SUBCODE_CODE  56
   /* SPI_LINK command, SPI_PBL_KEY field definition (address 2,size 8, lsb 0, unsigned) */
   #define  Si2183_SPI_LINK_CMD_SPI_PBL_KEY_LSB         0
   #define  Si2183_SPI_LINK_CMD_SPI_PBL_KEY_MASK        0xff
   #define  Si2183_SPI_LINK_CMD_SPI_PBL_KEY_MIN         0
   #define  Si2183_SPI_LINK_CMD_SPI_PBL_KEY_MAX         255
   /* SPI_LINK command, SPI_PBL_NUM field definition (address 3,size 4, lsb 0, unsigned) */
   #define  Si2183_SPI_LINK_CMD_SPI_PBL_NUM_LSB         0
   #define  Si2183_SPI_LINK_CMD_SPI_PBL_NUM_MASK        0x0f
   #define  Si2183_SPI_LINK_CMD_SPI_PBL_NUM_MIN         0
   #define  Si2183_SPI_LINK_CMD_SPI_PBL_NUM_MAX         15
   /* SPI_LINK command, SPI_CONF_CLK field definition (address 4,size 4, lsb 0, unsigned) */
   #define  Si2183_SPI_LINK_CMD_SPI_CONF_CLK_LSB         0
   #define  Si2183_SPI_LINK_CMD_SPI_CONF_CLK_MASK        0x0f
   #define  Si2183_SPI_LINK_CMD_SPI_CONF_CLK_MIN         0
   #define  Si2183_SPI_LINK_CMD_SPI_CONF_CLK_MAX         9
    #define Si2183_SPI_LINK_CMD_SPI_CONF_CLK_DISABLE     0
    #define Si2183_SPI_LINK_CMD_SPI_CONF_CLK_DISEQC_CMD  9
    #define Si2183_SPI_LINK_CMD_SPI_CONF_CLK_DISEQC_IN   7
    #define Si2183_SPI_LINK_CMD_SPI_CONF_CLK_DISEQC_OUT  8
    #define Si2183_SPI_LINK_CMD_SPI_CONF_CLK_GPIO0       5
    #define Si2183_SPI_LINK_CMD_SPI_CONF_CLK_GPIO1       6
    #define Si2183_SPI_LINK_CMD_SPI_CONF_CLK_MP_A        1
    #define Si2183_SPI_LINK_CMD_SPI_CONF_CLK_MP_B        2
    #define Si2183_SPI_LINK_CMD_SPI_CONF_CLK_MP_C        3
    #define Si2183_SPI_LINK_CMD_SPI_CONF_CLK_MP_D        4
   /* SPI_LINK command, SPI_CLK_POLA field definition (address 4,size 1, lsb 4, unsigned) */
   #define  Si2183_SPI_LINK_CMD_SPI_CLK_POLA_LSB         4
   #define  Si2183_SPI_LINK_CMD_SPI_CLK_POLA_MASK        0x01
   #define  Si2183_SPI_LINK_CMD_SPI_CLK_POLA_MIN         0
   #define  Si2183_SPI_LINK_CMD_SPI_CLK_POLA_MAX         1
    #define Si2183_SPI_LINK_CMD_SPI_CLK_POLA_FALLING  1
    #define Si2183_SPI_LINK_CMD_SPI_CLK_POLA_RISING   0
   /* SPI_LINK command, SPI_CONF_DATA field definition (address 5,size 4, lsb 0, unsigned) */
   #define  Si2183_SPI_LINK_CMD_SPI_CONF_DATA_LSB         0
   #define  Si2183_SPI_LINK_CMD_SPI_CONF_DATA_MASK        0x0f
   #define  Si2183_SPI_LINK_CMD_SPI_CONF_DATA_MIN         0
   #define  Si2183_SPI_LINK_CMD_SPI_CONF_DATA_MAX         9
    #define Si2183_SPI_LINK_CMD_SPI_CONF_DATA_DISABLE     0
    #define Si2183_SPI_LINK_CMD_SPI_CONF_DATA_DISEQC_CMD  9
    #define Si2183_SPI_LINK_CMD_SPI_CONF_DATA_DISEQC_IN   7
    #define Si2183_SPI_LINK_CMD_SPI_CONF_DATA_DISEQC_OUT  8
    #define Si2183_SPI_LINK_CMD_SPI_CONF_DATA_GPIO0       5
    #define Si2183_SPI_LINK_CMD_SPI_CONF_DATA_GPIO1       6
    #define Si2183_SPI_LINK_CMD_SPI_CONF_DATA_MP_A        1
    #define Si2183_SPI_LINK_CMD_SPI_CONF_DATA_MP_B        2
    #define Si2183_SPI_LINK_CMD_SPI_CONF_DATA_MP_C        3
    #define Si2183_SPI_LINK_CMD_SPI_CONF_DATA_MP_D        4
   /* SPI_LINK command, SPI_DATA_DIR field definition (address 5,size 1, lsb 4, unsigned) */
   #define  Si2183_SPI_LINK_CMD_SPI_DATA_DIR_LSB         4
   #define  Si2183_SPI_LINK_CMD_SPI_DATA_DIR_MASK        0x01
   #define  Si2183_SPI_LINK_CMD_SPI_DATA_DIR_MIN         0
   #define  Si2183_SPI_LINK_CMD_SPI_DATA_DIR_MAX         1
    #define Si2183_SPI_LINK_CMD_SPI_DATA_DIR_LSB_FIRST  1
    #define Si2183_SPI_LINK_CMD_SPI_DATA_DIR_MSB_FIRST  0
   /* SPI_LINK command, SPI_ENABLE field definition (address 6,size 1, lsb 0, unsigned) */
   #define  Si2183_SPI_LINK_CMD_SPI_ENABLE_LSB         0
   #define  Si2183_SPI_LINK_CMD_SPI_ENABLE_MASK        0x01
   #define  Si2183_SPI_LINK_CMD_SPI_ENABLE_MIN         0
   #define  Si2183_SPI_LINK_CMD_SPI_ENABLE_MAX         1
    #define Si2183_SPI_LINK_CMD_SPI_ENABLE_DISABLE  0
    #define Si2183_SPI_LINK_CMD_SPI_ENABLE_ENABLE   1
#endif /* Si2183_SPI_LINK_CMD */

/* Si2183_SPI_PASSTHROUGH command definition */
#define   Si2183_SPI_PASSTHROUGH_CMD 0xc0

#ifdef    Si2183_SPI_PASSTHROUGH_CMD
  #define Si2183_SPI_PASSTHROUGH_CMD_CODE 0x0500c0

    typedef struct { /* Si2183_SPI_PASSTHROUGH_CMD_struct */
     unsigned char   subcode;
     unsigned char   spi_passthr_clk;
     unsigned char   spi_passth_data;
   } Si2183_SPI_PASSTHROUGH_CMD_struct;


    typedef struct { /* Si2183_SPI_PASSTHROUGH_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
   }  Si2183_SPI_PASSTHROUGH_CMD_REPLY_struct;

   /* SPI_PASSTHROUGH command, SUBCODE field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_SPI_PASSTHROUGH_CMD_SUBCODE_LSB         0
   #define  Si2183_SPI_PASSTHROUGH_CMD_SUBCODE_MASK        0xff
   #define  Si2183_SPI_PASSTHROUGH_CMD_SUBCODE_MIN         64
   #define  Si2183_SPI_PASSTHROUGH_CMD_SUBCODE_MAX         64
    #define Si2183_SPI_PASSTHROUGH_CMD_SUBCODE_CODE  64
   /* SPI_PASSTHROUGH command, SPI_PASSTHR_CLK field definition (address 2,size 4, lsb 0, unsigned) */
   #define  Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTHR_CLK_LSB         0
   #define  Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTHR_CLK_MASK        0x0f
   #define  Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTHR_CLK_MIN         0
   #define  Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTHR_CLK_MAX         10
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTHR_CLK_DISABLE     0
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTHR_CLK_DISEQC_CMD  9
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTHR_CLK_DISEQC_IN   7
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTHR_CLK_DISEQC_OUT  8
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTHR_CLK_GPIO0       5
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTHR_CLK_GPIO1       6
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTHR_CLK_MP_A        1
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTHR_CLK_MP_B        2
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTHR_CLK_MP_C        3
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTHR_CLK_MP_D        4
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTHR_CLK_SCL_MAST    10
   /* SPI_PASSTHROUGH command, SPI_PASSTH_DATA field definition (address 3,size 4, lsb 0, unsigned) */
   #define  Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTH_DATA_LSB         0
   #define  Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTH_DATA_MASK        0x0f
   #define  Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTH_DATA_MIN         0
   #define  Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTH_DATA_MAX         10
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTH_DATA_DISABLE     0
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTH_DATA_DISEQC_CMD  9
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTH_DATA_DISEQC_IN   7
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTH_DATA_DISEQC_OUT  8
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTH_DATA_GPIO0       5
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTH_DATA_GPIO1       6
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTH_DATA_MP_A        1
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTH_DATA_MP_B        2
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTH_DATA_MP_C        3
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTH_DATA_MP_D        4
    #define Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTH_DATA_SDA_MAST    10
#endif /* Si2183_SPI_PASSTHROUGH_CMD */

/* Si2183_START_CLK command definition */
#define   Si2183_START_CLK_CMD 0xc0

#ifdef    Si2183_START_CLK_CMD
  #define Si2183_START_CLK_CMD_CODE 0x0600c0

    typedef struct { /* Si2183_START_CLK_CMD_struct */
     unsigned char   subcode;
     unsigned char   reserved1;
     unsigned char   tune_cap;
     unsigned char   reserved2;
     unsigned int    clk_mode;
     unsigned char   reserved3;
     unsigned char   reserved4;
     unsigned char   start_clk;
   } Si2183_START_CLK_CMD_struct;


    typedef struct { /* Si2183_START_CLK_CMD_REPLY_struct */
       Si2183_COMMON_REPLY_struct * STATUS;
   }  Si2183_START_CLK_CMD_REPLY_struct;

   /* START_CLK command, SUBCODE field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2183_START_CLK_CMD_SUBCODE_LSB         0
   #define  Si2183_START_CLK_CMD_SUBCODE_MASK        0xff
   #define  Si2183_START_CLK_CMD_SUBCODE_MIN         18
   #define  Si2183_START_CLK_CMD_SUBCODE_MAX         18
    #define Si2183_START_CLK_CMD_SUBCODE_CODE  18
   /* START_CLK command, RESERVED1 field definition (address 2,size 8, lsb 0, unsigned) */
   #define  Si2183_START_CLK_CMD_RESERVED1_LSB         0
   #define  Si2183_START_CLK_CMD_RESERVED1_MASK        0xff
   #define  Si2183_START_CLK_CMD_RESERVED1_MIN         0
   #define  Si2183_START_CLK_CMD_RESERVED1_MAX         0
    #define Si2183_START_CLK_CMD_RESERVED1_RESERVED  0
   /* START_CLK command, TUNE_CAP field definition (address 3,size 4, lsb 0, unsigned) */
   #define  Si2183_START_CLK_CMD_TUNE_CAP_LSB         0
   #define  Si2183_START_CLK_CMD_TUNE_CAP_MASK        0x0f
   #define  Si2183_START_CLK_CMD_TUNE_CAP_MIN         0
   #define  Si2183_START_CLK_CMD_TUNE_CAP_MAX         15
    #define Si2183_START_CLK_CMD_TUNE_CAP_10P4     8
    #define Si2183_START_CLK_CMD_TUNE_CAP_11P7     9
    #define Si2183_START_CLK_CMD_TUNE_CAP_13P0     10
    #define Si2183_START_CLK_CMD_TUNE_CAP_14P3     11
    #define Si2183_START_CLK_CMD_TUNE_CAP_15P6     12
    #define Si2183_START_CLK_CMD_TUNE_CAP_16P9     13
    #define Si2183_START_CLK_CMD_TUNE_CAP_18P2     14
    #define Si2183_START_CLK_CMD_TUNE_CAP_19P5     15
    #define Si2183_START_CLK_CMD_TUNE_CAP_1P3      1
    #define Si2183_START_CLK_CMD_TUNE_CAP_2P6      2
    #define Si2183_START_CLK_CMD_TUNE_CAP_3P9      3
    #define Si2183_START_CLK_CMD_TUNE_CAP_5P2      4
    #define Si2183_START_CLK_CMD_TUNE_CAP_6P5      5
    #define Si2183_START_CLK_CMD_TUNE_CAP_7P8      6
    #define Si2183_START_CLK_CMD_TUNE_CAP_9P1      7
    #define Si2183_START_CLK_CMD_TUNE_CAP_EXT_CLK  0
   /* START_CLK command, RESERVED2 field definition (address 3,size 4, lsb 4, unsigned) */
   #define  Si2183_START_CLK_CMD_RESERVED2_LSB         4
   #define  Si2183_START_CLK_CMD_RESERVED2_MASK        0x0f
   #define  Si2183_START_CLK_CMD_RESERVED2_MIN         0
   #define  Si2183_START_CLK_CMD_RESERVED2_MAX         0
    #define Si2183_START_CLK_CMD_RESERVED2_RESERVED  0
   /* START_CLK command, CLK_MODE field definition (address 4,size 12, lsb 0, unsigned) */
   #define  Si2183_START_CLK_CMD_CLK_MODE_LSB         0
   #define  Si2183_START_CLK_CMD_CLK_MODE_MASK        0xfff
   #define  Si2183_START_CLK_CMD_CLK_MODE_MIN         575
   #define  Si2183_START_CLK_CMD_CLK_MODE_MAX         3328
    #define Si2183_START_CLK_CMD_CLK_MODE_CLK_CLKIO    3328
    #define Si2183_START_CLK_CMD_CLK_MODE_CLK_XTAL_IN  1536
    #define Si2183_START_CLK_CMD_CLK_MODE_XTAL         575
   /* START_CLK command, RESERVED3 field definition (address 6,size 8, lsb 0, unsigned) */
   #define  Si2183_START_CLK_CMD_RESERVED3_LSB         0
   #define  Si2183_START_CLK_CMD_RESERVED3_MASK        0xff
   #define  Si2183_START_CLK_CMD_RESERVED3_MIN         22
   #define  Si2183_START_CLK_CMD_RESERVED3_MAX         22
    #define Si2183_START_CLK_CMD_RESERVED3_RESERVED  22
   /* START_CLK command, RESERVED4 field definition (address 7,size 1, lsb 0, unsigned) */
   #define  Si2183_START_CLK_CMD_RESERVED4_LSB         0
   #define  Si2183_START_CLK_CMD_RESERVED4_MASK        0x01
   #define  Si2183_START_CLK_CMD_RESERVED4_MIN         0
   #define  Si2183_START_CLK_CMD_RESERVED4_MAX         0
    #define Si2183_START_CLK_CMD_RESERVED4_RESERVED  0
   /* START_CLK command, START_CLK field definition (address 12,size 1, lsb 0, unsigned) */
   #define  Si2183_START_CLK_CMD_START_CLK_LSB         0
   #define  Si2183_START_CLK_CMD_START_CLK_MASK        0x01
   #define  Si2183_START_CLK_CMD_START_CLK_MIN         0
   #define  Si2183_START_CLK_CMD_START_CLK_MAX         0
    #define Si2183_START_CLK_CMD_START_CLK_START_CLK  0
#endif /* Si2183_START_CLK_CMD */



  /* --------------------------------------------*/
  /* COMMANDS STRUCT                             */
  /* This is used to store all command fields    */
  /* --------------------------------------------*/
  typedef struct { /* Si2183_CmdObj struct */
    #ifdef    Si2183_CONFIG_CLKIO_CMD
              Si2183_CONFIG_CLKIO_CMD_struct               config_clkio;
    #endif /* Si2183_CONFIG_CLKIO_CMD */
    #ifdef    Si2183_CONFIG_I2C_CMD
              Si2183_CONFIG_I2C_CMD_struct                 config_i2c;
    #endif /* Si2183_CONFIG_I2C_CMD */
    #ifdef    Si2183_CONFIG_PINS_CMD
              Si2183_CONFIG_PINS_CMD_struct                config_pins;
    #endif /* Si2183_CONFIG_PINS_CMD */
    #ifdef    Si2183_DD_BER_CMD
              Si2183_DD_BER_CMD_struct                     dd_ber;
    #endif /* Si2183_DD_BER_CMD */
    #ifdef    Si2183_DD_CBER_CMD
              Si2183_DD_CBER_CMD_struct                    dd_cber;
    #endif /* Si2183_DD_CBER_CMD */
#ifdef    SATELLITE_FRONT_END
    #ifdef    Si2183_DD_DISEQC_SEND_CMD
              Si2183_DD_DISEQC_SEND_CMD_struct             dd_diseqc_send;
    #endif /* Si2183_DD_DISEQC_SEND_CMD */
    #ifdef    Si2183_DD_DISEQC_STATUS_CMD
              Si2183_DD_DISEQC_STATUS_CMD_struct           dd_diseqc_status;
    #endif /* Si2183_DD_DISEQC_STATUS_CMD */
    #ifdef    Si2183_DD_EXT_AGC_SAT_CMD
              Si2183_DD_EXT_AGC_SAT_CMD_struct             dd_ext_agc_sat;
    #endif /* Si2183_DD_EXT_AGC_SAT_CMD */
#endif /* SATELLITE_FRONT_END */

#ifdef    TERRESTRIAL_FRONT_END
    #ifdef    Si2183_DD_EXT_AGC_TER_CMD
              Si2183_DD_EXT_AGC_TER_CMD_struct             dd_ext_agc_ter;
    #endif /* Si2183_DD_EXT_AGC_TER_CMD */
#endif /* TERRESTRIAL_FRONT_END */

    #ifdef    Si2183_DD_FER_CMD
              Si2183_DD_FER_CMD_struct                     dd_fer;
    #endif /* Si2183_DD_FER_CMD */
    #ifdef    Si2183_DD_GET_REG_CMD
              Si2183_DD_GET_REG_CMD_struct                 dd_get_reg;
    #endif /* Si2183_DD_GET_REG_CMD */
    #ifdef    Si2183_DD_MP_DEFAULTS_CMD
              Si2183_DD_MP_DEFAULTS_CMD_struct             dd_mp_defaults;
    #endif /* Si2183_DD_MP_DEFAULTS_CMD */
    #ifdef    Si2183_DD_PER_CMD
              Si2183_DD_PER_CMD_struct                     dd_per;
    #endif /* Si2183_DD_PER_CMD */
    #ifdef    Si2183_DD_RESTART_CMD
              Si2183_DD_RESTART_CMD_struct                 dd_restart;
    #endif /* Si2183_DD_RESTART_CMD */
    #ifdef    Si2183_DD_RESTART_EXT_CMD
              Si2183_DD_RESTART_EXT_CMD_struct             dd_restart_ext;
    #endif /* Si2183_DD_RESTART_EXT_CMD */
    #ifdef    Si2183_DD_SET_REG_CMD
              Si2183_DD_SET_REG_CMD_struct                 dd_set_reg;
    #endif /* Si2183_DD_SET_REG_CMD */
    #ifdef    Si2183_DD_SSI_SQI_CMD
              Si2183_DD_SSI_SQI_CMD_struct                 dd_ssi_sqi;
    #endif /* Si2183_DD_SSI_SQI_CMD */
    #ifdef    Si2183_DD_STATUS_CMD
              Si2183_DD_STATUS_CMD_struct                  dd_status;
    #endif /* Si2183_DD_STATUS_CMD */
    #ifdef    Si2183_DD_TS_PINS_CMD
              Si2183_DD_TS_PINS_CMD_struct                 dd_ts_pins;
    #endif /* Si2183_DD_TS_PINS_CMD */
    #ifdef    Si2183_DD_UNCOR_CMD
              Si2183_DD_UNCOR_CMD_struct                   dd_uncor;
    #endif /* Si2183_DD_UNCOR_CMD */
    #ifdef    Si2183_DEMOD_INFO_CMD
              Si2183_DEMOD_INFO_CMD_struct                 demod_info;
    #endif /* Si2183_DEMOD_INFO_CMD */
    #ifdef    Si2183_DOWNLOAD_DATASET_CONTINUE_CMD
              Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_struct  download_dataset_continue;
    #endif /* Si2183_DOWNLOAD_DATASET_CONTINUE_CMD */
    #ifdef    Si2183_DOWNLOAD_DATASET_START_CMD
              Si2183_DOWNLOAD_DATASET_START_CMD_struct     download_dataset_start;
    #endif /* Si2183_DOWNLOAD_DATASET_START_CMD */
#ifdef    DEMOD_DVB_C2
    #ifdef    Si2183_DVBC2_CTRL_CMD
              Si2183_DVBC2_CTRL_CMD_struct                 dvbc2_ctrl;
    #endif /* Si2183_DVBC2_CTRL_CMD */
    #ifdef    Si2183_DVBC2_DS_INFO_CMD
              Si2183_DVBC2_DS_INFO_CMD_struct              dvbc2_ds_info;
    #endif /* Si2183_DVBC2_DS_INFO_CMD */
    #ifdef    Si2183_DVBC2_DS_PLP_SELECT_CMD
              Si2183_DVBC2_DS_PLP_SELECT_CMD_struct        dvbc2_ds_plp_select;
    #endif /* Si2183_DVBC2_DS_PLP_SELECT_CMD */
    #ifdef    Si2183_DVBC2_PLP_INFO_CMD
              Si2183_DVBC2_PLP_INFO_CMD_struct             dvbc2_plp_info;
    #endif /* Si2183_DVBC2_PLP_INFO_CMD */
    #ifdef    Si2183_DVBC2_STATUS_CMD
              Si2183_DVBC2_STATUS_CMD_struct               dvbc2_status;
    #endif /* Si2183_DVBC2_STATUS_CMD */
    #ifdef    Si2183_DVBC2_SYS_INFO_CMD
              Si2183_DVBC2_SYS_INFO_CMD_struct             dvbc2_sys_info;
    #endif /* Si2183_DVBC2_SYS_INFO_CMD */
#endif /* DEMOD_DVB_C2 */

#ifdef    DEMOD_DVB_C
    #ifdef    Si2183_DVBC_STATUS_CMD
              Si2183_DVBC_STATUS_CMD_struct                dvbc_status;
    #endif /* Si2183_DVBC_STATUS_CMD */
#endif /* DEMOD_DVB_C */

#ifdef    DEMOD_DVB_S_S2_DSS
    #ifdef    Si2183_DVBS2_PLS_INIT_CMD
              Si2183_DVBS2_PLS_INIT_CMD_struct             dvbs2_pls_init;
    #endif /* Si2183_DVBS2_PLS_INIT_CMD */
    #ifdef    Si2183_DVBS2_STATUS_CMD
              Si2183_DVBS2_STATUS_CMD_struct               dvbs2_status;
    #endif /* Si2183_DVBS2_STATUS_CMD */
    #ifdef    Si2183_DVBS2_STREAM_INFO_CMD
              Si2183_DVBS2_STREAM_INFO_CMD_struct          dvbs2_stream_info;
    #endif /* Si2183_DVBS2_STREAM_INFO_CMD */
    #ifdef    Si2183_DVBS2_STREAM_SELECT_CMD
              Si2183_DVBS2_STREAM_SELECT_CMD_struct        dvbs2_stream_select;
    #endif /* Si2183_DVBS2_STREAM_SELECT_CMD */
    #ifdef    Si2183_DVBS_STATUS_CMD
              Si2183_DVBS_STATUS_CMD_struct                dvbs_status;
    #endif /* Si2183_DVBS_STATUS_CMD */
#endif /* DEMOD_DVB_S_S2_DSS */

#ifdef    DEMOD_DVB_T2
    #ifdef    Si2183_DVBT2_FEF_CMD
              Si2183_DVBT2_FEF_CMD_struct                  dvbt2_fef;
    #endif /* Si2183_DVBT2_FEF_CMD */
    #ifdef    Si2183_DVBT2_PLP_INFO_CMD
              Si2183_DVBT2_PLP_INFO_CMD_struct             dvbt2_plp_info;
    #endif /* Si2183_DVBT2_PLP_INFO_CMD */
    #ifdef    Si2183_DVBT2_PLP_SELECT_CMD
              Si2183_DVBT2_PLP_SELECT_CMD_struct           dvbt2_plp_select;
    #endif /* Si2183_DVBT2_PLP_SELECT_CMD */
    #ifdef    Si2183_DVBT2_STATUS_CMD
              Si2183_DVBT2_STATUS_CMD_struct               dvbt2_status;
    #endif /* Si2183_DVBT2_STATUS_CMD */
    #ifdef    Si2183_DVBT2_TX_ID_CMD
              Si2183_DVBT2_TX_ID_CMD_struct                dvbt2_tx_id;
    #endif /* Si2183_DVBT2_TX_ID_CMD */
#endif /* DEMOD_DVB_T2 */

#ifdef    DEMOD_DVB_T
    #ifdef    Si2183_DVBT_STATUS_CMD
              Si2183_DVBT_STATUS_CMD_struct                dvbt_status;
    #endif /* Si2183_DVBT_STATUS_CMD */
    #ifdef    Si2183_DVBT_TPS_EXTRA_CMD
              Si2183_DVBT_TPS_EXTRA_CMD_struct             dvbt_tps_extra;
    #endif /* Si2183_DVBT_TPS_EXTRA_CMD */
#endif /* DEMOD_DVB_T */

    #ifdef    Si2183_EXIT_BOOTLOADER_CMD
              Si2183_EXIT_BOOTLOADER_CMD_struct            exit_bootloader;
    #endif /* Si2183_EXIT_BOOTLOADER_CMD */
    #ifdef    Si2183_GET_PROPERTY_CMD
              Si2183_GET_PROPERTY_CMD_struct               get_property;
    #endif /* Si2183_GET_PROPERTY_CMD */
    #ifdef    Si2183_GET_REV_CMD
              Si2183_GET_REV_CMD_struct                    get_rev;
    #endif /* Si2183_GET_REV_CMD */
    #ifdef    Si2183_I2C_PASSTHROUGH_CMD
              Si2183_I2C_PASSTHROUGH_CMD_struct            i2c_passthrough;
    #endif /* Si2183_I2C_PASSTHROUGH_CMD */
#ifdef    DEMOD_ISDB_T
    #ifdef    Si2183_ISDBT_AC_BITS_CMD
              Si2183_ISDBT_AC_BITS_CMD_struct              isdbt_ac_bits;
    #endif /* Si2183_ISDBT_AC_BITS_CMD */
    #ifdef    Si2183_ISDBT_LAYER_INFO_CMD
              Si2183_ISDBT_LAYER_INFO_CMD_struct           isdbt_layer_info;
    #endif /* Si2183_ISDBT_LAYER_INFO_CMD */
    #ifdef    Si2183_ISDBT_STATUS_CMD
              Si2183_ISDBT_STATUS_CMD_struct               isdbt_status;
    #endif /* Si2183_ISDBT_STATUS_CMD */
#endif /* DEMOD_ISDB_T */

#ifdef    DEMOD_MCNS
    #ifdef    Si2183_MCNS_STATUS_CMD
              Si2183_MCNS_STATUS_CMD_struct                mcns_status;
    #endif /* Si2183_MCNS_STATUS_CMD */
#endif /* DEMOD_MCNS */

    #ifdef    Si2183_PART_INFO_CMD
              Si2183_PART_INFO_CMD_struct                  part_info;
    #endif /* Si2183_PART_INFO_CMD */
    #ifdef    Si2183_POWER_DOWN_CMD
              Si2183_POWER_DOWN_CMD_struct                 power_down;
    #endif /* Si2183_POWER_DOWN_CMD */
    #ifdef    Si2183_POWER_UP_CMD
              Si2183_POWER_UP_CMD_struct                   power_up;
    #endif /* Si2183_POWER_UP_CMD */
    #ifdef    Si2183_RSSI_ADC_CMD
              Si2183_RSSI_ADC_CMD_struct                   rssi_adc;
    #endif /* Si2183_RSSI_ADC_CMD */
    #ifdef    Si2183_SCAN_CTRL_CMD
              Si2183_SCAN_CTRL_CMD_struct                  scan_ctrl;
    #endif /* Si2183_SCAN_CTRL_CMD */
    #ifdef    Si2183_SCAN_STATUS_CMD
              Si2183_SCAN_STATUS_CMD_struct                scan_status;
    #endif /* Si2183_SCAN_STATUS_CMD */
    #ifdef    Si2183_SET_PROPERTY_CMD
              Si2183_SET_PROPERTY_CMD_struct               set_property;
    #endif /* Si2183_SET_PROPERTY_CMD */
    #ifdef    Si2183_SPI_LINK_CMD
              Si2183_SPI_LINK_CMD_struct                   spi_link;
    #endif /* Si2183_SPI_LINK_CMD */
    #ifdef    Si2183_SPI_PASSTHROUGH_CMD
              Si2183_SPI_PASSTHROUGH_CMD_struct            spi_passthrough;
    #endif /* Si2183_SPI_PASSTHROUGH_CMD */
    #ifdef    Si2183_START_CLK_CMD
              Si2183_START_CLK_CMD_struct                  start_clk;
    #endif /* Si2183_START_CLK_CMD */
  } Si2183_CmdObj;


  /* --------------------------------------------*/
  /* COMMANDS REPLY STRUCT                       */
  /* This stores all command reply fields        */
  /* --------------------------------------------*/
  typedef struct { /* Si2183_CmdReplyObj struct */
    #ifdef    Si2183_CONFIG_CLKIO_CMD
              Si2183_CONFIG_CLKIO_CMD_REPLY_struct               config_clkio;
    #endif /* Si2183_CONFIG_CLKIO_CMD */
    #ifdef    Si2183_CONFIG_I2C_CMD
              Si2183_CONFIG_I2C_CMD_REPLY_struct                 config_i2c;
    #endif /* Si2183_CONFIG_I2C_CMD */
    #ifdef    Si2183_CONFIG_PINS_CMD
              Si2183_CONFIG_PINS_CMD_REPLY_struct                config_pins;
    #endif /* Si2183_CONFIG_PINS_CMD */
    #ifdef    Si2183_DD_BER_CMD
              Si2183_DD_BER_CMD_REPLY_struct                     dd_ber;
    #endif /* Si2183_DD_BER_CMD */
    #ifdef    Si2183_DD_CBER_CMD
              Si2183_DD_CBER_CMD_REPLY_struct                    dd_cber;
    #endif /* Si2183_DD_CBER_CMD */
#ifdef    SATELLITE_FRONT_END
    #ifdef    Si2183_DD_DISEQC_SEND_CMD
              Si2183_DD_DISEQC_SEND_CMD_REPLY_struct             dd_diseqc_send;
    #endif /* Si2183_DD_DISEQC_SEND_CMD */
    #ifdef    Si2183_DD_DISEQC_STATUS_CMD
              Si2183_DD_DISEQC_STATUS_CMD_REPLY_struct           dd_diseqc_status;
    #endif /* Si2183_DD_DISEQC_STATUS_CMD */
    #ifdef    Si2183_DD_EXT_AGC_SAT_CMD
              Si2183_DD_EXT_AGC_SAT_CMD_REPLY_struct             dd_ext_agc_sat;
    #endif /* Si2183_DD_EXT_AGC_SAT_CMD */
#endif /* SATELLITE_FRONT_END */

#ifdef    TERRESTRIAL_FRONT_END
    #ifdef    Si2183_DD_EXT_AGC_TER_CMD
              Si2183_DD_EXT_AGC_TER_CMD_REPLY_struct             dd_ext_agc_ter;
    #endif /* Si2183_DD_EXT_AGC_TER_CMD */
#endif /* TERRESTRIAL_FRONT_END */

    #ifdef    Si2183_DD_FER_CMD
              Si2183_DD_FER_CMD_REPLY_struct                     dd_fer;
    #endif /* Si2183_DD_FER_CMD */
    #ifdef    Si2183_DD_GET_REG_CMD
              Si2183_DD_GET_REG_CMD_REPLY_struct                 dd_get_reg;
    #endif /* Si2183_DD_GET_REG_CMD */
    #ifdef    Si2183_DD_MP_DEFAULTS_CMD
              Si2183_DD_MP_DEFAULTS_CMD_REPLY_struct             dd_mp_defaults;
    #endif /* Si2183_DD_MP_DEFAULTS_CMD */
    #ifdef    Si2183_DD_PER_CMD
              Si2183_DD_PER_CMD_REPLY_struct                     dd_per;
    #endif /* Si2183_DD_PER_CMD */
    #ifdef    Si2183_DD_RESTART_CMD
              Si2183_DD_RESTART_CMD_REPLY_struct                 dd_restart;
    #endif /* Si2183_DD_RESTART_CMD */
    #ifdef    Si2183_DD_RESTART_EXT_CMD
              Si2183_DD_RESTART_EXT_CMD_REPLY_struct             dd_restart_ext;
    #endif /* Si2183_DD_RESTART_EXT_CMD */
    #ifdef    Si2183_DD_SET_REG_CMD
              Si2183_DD_SET_REG_CMD_REPLY_struct                 dd_set_reg;
    #endif /* Si2183_DD_SET_REG_CMD */
    #ifdef    Si2183_DD_SSI_SQI_CMD
              Si2183_DD_SSI_SQI_CMD_REPLY_struct                 dd_ssi_sqi;
    #endif /* Si2183_DD_SSI_SQI_CMD */
    #ifdef    Si2183_DD_STATUS_CMD
              Si2183_DD_STATUS_CMD_REPLY_struct                  dd_status;
    #endif /* Si2183_DD_STATUS_CMD */
    #ifdef    Si2183_DD_TS_PINS_CMD
              Si2183_DD_TS_PINS_CMD_REPLY_struct                 dd_ts_pins;
    #endif /* Si2183_DD_TS_PINS_CMD */
    #ifdef    Si2183_DD_UNCOR_CMD
              Si2183_DD_UNCOR_CMD_REPLY_struct                   dd_uncor;
    #endif /* Si2183_DD_UNCOR_CMD */
    #ifdef    Si2183_DEMOD_INFO_CMD
              Si2183_DEMOD_INFO_CMD_REPLY_struct                 demod_info;
    #endif /* Si2183_DEMOD_INFO_CMD */
    #ifdef    Si2183_DOWNLOAD_DATASET_CONTINUE_CMD
              Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_REPLY_struct  download_dataset_continue;
    #endif /* Si2183_DOWNLOAD_DATASET_CONTINUE_CMD */
    #ifdef    Si2183_DOWNLOAD_DATASET_START_CMD
              Si2183_DOWNLOAD_DATASET_START_CMD_REPLY_struct     download_dataset_start;
    #endif /* Si2183_DOWNLOAD_DATASET_START_CMD */
#ifdef    DEMOD_DVB_C2
    #ifdef    Si2183_DVBC2_CTRL_CMD
              Si2183_DVBC2_CTRL_CMD_REPLY_struct                 dvbc2_ctrl;
    #endif /* Si2183_DVBC2_CTRL_CMD */
    #ifdef    Si2183_DVBC2_DS_INFO_CMD
              Si2183_DVBC2_DS_INFO_CMD_REPLY_struct              dvbc2_ds_info;
    #endif /* Si2183_DVBC2_DS_INFO_CMD */
    #ifdef    Si2183_DVBC2_DS_PLP_SELECT_CMD
              Si2183_DVBC2_DS_PLP_SELECT_CMD_REPLY_struct        dvbc2_ds_plp_select;
    #endif /* Si2183_DVBC2_DS_PLP_SELECT_CMD */
    #ifdef    Si2183_DVBC2_PLP_INFO_CMD
              Si2183_DVBC2_PLP_INFO_CMD_REPLY_struct             dvbc2_plp_info;
    #endif /* Si2183_DVBC2_PLP_INFO_CMD */
    #ifdef    Si2183_DVBC2_STATUS_CMD
              Si2183_DVBC2_STATUS_CMD_REPLY_struct               dvbc2_status;
    #endif /* Si2183_DVBC2_STATUS_CMD */
    #ifdef    Si2183_DVBC2_SYS_INFO_CMD
              Si2183_DVBC2_SYS_INFO_CMD_REPLY_struct             dvbc2_sys_info;
    #endif /* Si2183_DVBC2_SYS_INFO_CMD */
#endif /* DEMOD_DVB_C2 */

#ifdef    DEMOD_DVB_C
    #ifdef    Si2183_DVBC_STATUS_CMD
              Si2183_DVBC_STATUS_CMD_REPLY_struct                dvbc_status;
    #endif /* Si2183_DVBC_STATUS_CMD */
#endif /* DEMOD_DVB_C */

#ifdef    DEMOD_DVB_S_S2_DSS
    #ifdef    Si2183_DVBS2_PLS_INIT_CMD
              Si2183_DVBS2_PLS_INIT_CMD_REPLY_struct             dvbs2_pls_init;
    #endif /* Si2183_DVBS2_PLS_INIT_CMD */
    #ifdef    Si2183_DVBS2_STATUS_CMD
              Si2183_DVBS2_STATUS_CMD_REPLY_struct               dvbs2_status;
    #endif /* Si2183_DVBS2_STATUS_CMD */
    #ifdef    Si2183_DVBS2_STREAM_INFO_CMD
              Si2183_DVBS2_STREAM_INFO_CMD_REPLY_struct          dvbs2_stream_info;
    #endif /* Si2183_DVBS2_STREAM_INFO_CMD */
    #ifdef    Si2183_DVBS2_STREAM_SELECT_CMD
              Si2183_DVBS2_STREAM_SELECT_CMD_REPLY_struct        dvbs2_stream_select;
    #endif /* Si2183_DVBS2_STREAM_SELECT_CMD */
    #ifdef    Si2183_DVBS_STATUS_CMD
              Si2183_DVBS_STATUS_CMD_REPLY_struct                dvbs_status;
    #endif /* Si2183_DVBS_STATUS_CMD */
#endif /* DEMOD_DVB_S_S2_DSS */

#ifdef    DEMOD_DVB_T2
    #ifdef    Si2183_DVBT2_FEF_CMD
              Si2183_DVBT2_FEF_CMD_REPLY_struct                  dvbt2_fef;
    #endif /* Si2183_DVBT2_FEF_CMD */
    #ifdef    Si2183_DVBT2_PLP_INFO_CMD
              Si2183_DVBT2_PLP_INFO_CMD_REPLY_struct             dvbt2_plp_info;
    #endif /* Si2183_DVBT2_PLP_INFO_CMD */
    #ifdef    Si2183_DVBT2_PLP_SELECT_CMD
              Si2183_DVBT2_PLP_SELECT_CMD_REPLY_struct           dvbt2_plp_select;
    #endif /* Si2183_DVBT2_PLP_SELECT_CMD */
    #ifdef    Si2183_DVBT2_STATUS_CMD
              Si2183_DVBT2_STATUS_CMD_REPLY_struct               dvbt2_status;
    #endif /* Si2183_DVBT2_STATUS_CMD */
    #ifdef    Si2183_DVBT2_TX_ID_CMD
              Si2183_DVBT2_TX_ID_CMD_REPLY_struct                dvbt2_tx_id;
    #endif /* Si2183_DVBT2_TX_ID_CMD */
#endif /* DEMOD_DVB_T2 */

#ifdef    DEMOD_DVB_T
    #ifdef    Si2183_DVBT_STATUS_CMD
              Si2183_DVBT_STATUS_CMD_REPLY_struct                dvbt_status;
    #endif /* Si2183_DVBT_STATUS_CMD */
    #ifdef    Si2183_DVBT_TPS_EXTRA_CMD
              Si2183_DVBT_TPS_EXTRA_CMD_REPLY_struct             dvbt_tps_extra;
    #endif /* Si2183_DVBT_TPS_EXTRA_CMD */
#endif /* DEMOD_DVB_T */

    #ifdef    Si2183_EXIT_BOOTLOADER_CMD
              Si2183_EXIT_BOOTLOADER_CMD_REPLY_struct            exit_bootloader;
    #endif /* Si2183_EXIT_BOOTLOADER_CMD */
    #ifdef    Si2183_GET_PROPERTY_CMD
              Si2183_GET_PROPERTY_CMD_REPLY_struct               get_property;
    #endif /* Si2183_GET_PROPERTY_CMD */
    #ifdef    Si2183_GET_REV_CMD
              Si2183_GET_REV_CMD_REPLY_struct                    get_rev;
    #endif /* Si2183_GET_REV_CMD */
    #ifdef    Si2183_I2C_PASSTHROUGH_CMD
              Si2183_I2C_PASSTHROUGH_CMD_REPLY_struct            i2c_passthrough;
    #endif /* Si2183_I2C_PASSTHROUGH_CMD */
#ifdef    DEMOD_ISDB_T
    #ifdef    Si2183_ISDBT_AC_BITS_CMD
              Si2183_ISDBT_AC_BITS_CMD_REPLY_struct              isdbt_ac_bits;
    #endif /* Si2183_ISDBT_AC_BITS_CMD */
    #ifdef    Si2183_ISDBT_LAYER_INFO_CMD
              Si2183_ISDBT_LAYER_INFO_CMD_REPLY_struct           isdbt_layer_info;
    #endif /* Si2183_ISDBT_LAYER_INFO_CMD */
    #ifdef    Si2183_ISDBT_STATUS_CMD
              Si2183_ISDBT_STATUS_CMD_REPLY_struct               isdbt_status;
    #endif /* Si2183_ISDBT_STATUS_CMD */
#endif /* DEMOD_ISDB_T */

#ifdef    DEMOD_MCNS
    #ifdef    Si2183_MCNS_STATUS_CMD
              Si2183_MCNS_STATUS_CMD_REPLY_struct                mcns_status;
    #endif /* Si2183_MCNS_STATUS_CMD */
#endif /* DEMOD_MCNS */

    #ifdef    Si2183_PART_INFO_CMD
              Si2183_PART_INFO_CMD_REPLY_struct                  part_info;
    #endif /* Si2183_PART_INFO_CMD */
    #ifdef    Si2183_POWER_DOWN_CMD
              Si2183_POWER_DOWN_CMD_REPLY_struct                 power_down;
    #endif /* Si2183_POWER_DOWN_CMD */
    #ifdef    Si2183_POWER_UP_CMD
              Si2183_POWER_UP_CMD_REPLY_struct                   power_up;
    #endif /* Si2183_POWER_UP_CMD */
    #ifdef    Si2183_RSSI_ADC_CMD
              Si2183_RSSI_ADC_CMD_REPLY_struct                   rssi_adc;
    #endif /* Si2183_RSSI_ADC_CMD */
    #ifdef    Si2183_SCAN_CTRL_CMD
              Si2183_SCAN_CTRL_CMD_REPLY_struct                  scan_ctrl;
    #endif /* Si2183_SCAN_CTRL_CMD */
    #ifdef    Si2183_SCAN_STATUS_CMD
              Si2183_SCAN_STATUS_CMD_REPLY_struct                scan_status;
    #endif /* Si2183_SCAN_STATUS_CMD */
    #ifdef    Si2183_SET_PROPERTY_CMD
              Si2183_SET_PROPERTY_CMD_REPLY_struct               set_property;
    #endif /* Si2183_SET_PROPERTY_CMD */
    #ifdef    Si2183_SPI_LINK_CMD
              Si2183_SPI_LINK_CMD_REPLY_struct                   spi_link;
    #endif /* Si2183_SPI_LINK_CMD */
    #ifdef    Si2183_SPI_PASSTHROUGH_CMD
              Si2183_SPI_PASSTHROUGH_CMD_REPLY_struct            spi_passthrough;
    #endif /* Si2183_SPI_PASSTHROUGH_CMD */
    #ifdef    Si2183_START_CLK_CMD
              Si2183_START_CLK_CMD_REPLY_struct                  start_clk;
    #endif /* Si2183_START_CLK_CMD */
  } Si2183_CmdReplyObj;

#ifdef    Si2183_COMMAND_PROTOTYPES
#define   Si2183_GET_COMMAND_STRINGS
#endif /* Si2183_COMMAND_PROTOTYPES */

#endif /* Si2183_COMMANDS_H */







