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


   API commands definitions
   FILE: Si2183_L1_Commands.c
   Supported IC : Si2183
   Compiled for ROM 2 firmware 5_B_build_1
   Revision: V0.3.5.1
   Tag:  V0.3.5.1
   Date: November 06 2015
**************************************************************************************/
/* Change log:

 As from V0.3.3.1: Adding GSE_LITE value in possible DVBS2_STATUS.STREAM_TYPE values

 As from V0.3.3.0: In Si2183_convert_to_uint and  Si2183_convert_to_int: adding a set of parenthesis to shift all bytes

 As from V0.3.0.0:
   <compatibility>[compiler/warnings] Removing test on DD_TS_PINS MASTER_FREQ (can't overload, since it's a 32 bit)
   <improvement>[debug/reply] In Si2183_pollForResponse: tracing the proper debug text

 As from V0.2.8.0:
   <new_feature>[DVB_T2/stream_type] Retrieving stream_type in Si2183_L1_DVBT2_STATUS
   <new_feature>[DVB_S2/stream_type] Retrieving stream_type in Si2183_L1_DVBS2_STATUS

 As from V0.2.5.0:
    <Improvement>[traces] In Si2183_L1_SET_PROPERTY: not tracing property code and value because it's already traced at L2 level

 As from V0.2.3.0:
  <improvement>[dual/triple/quad/broadcast_i2c] In Si2183_L1_POWER_UP: only check CTS after POWER_UP / RESET.
    This is because after FW download using broadcast_i2c the response will not be 0x80.

 As from V0.2.2.0:
  <comments>[debug bytes] In Si2183_pollForResponse, adding comments related to debug bytes meaning when ERR is raised.
    This can help understand the reason for the error.
    For instance, '0x10' means 'BAD_COMMAND' and will happen when issuing a SAT command while in TER or when issuing a command not supported by the part.

 As from V0.2.1.0:
  <new_feature>[DUALS/Channel_Bonding] Upgrading Si2183_L1_DD_TS_PINS to allow channel bonding
  <traces>[ISDB-T] Si2183_L1_GetCommandResponseString: tracing isdbt_status.emergency_flag

 As from V0.1.9.0:
  <improvement>[traces/SET_PROPERTY] In Si2183_L1_SET_PROPERTY: tracing prop and data values on a single line, to reduce the amount of trace lines.

 As from V0.1.6.0:
  <compatibility>[SILABS_SUPERSET/TER/SAT] Replacing tags in Si2183_L1_SendCommand2 and Si2183_L1_GetCommandResponseString to allow compiling for TER-only or SAT-only

 As from V0.1.4.0:
  <new_feature>[DVB-S2/Gold_Sequences] Adding Si2183_L1_DVBS2_PLS_INIT to allow locking on all Gold Sequences in DVB-S2.
    NB: Not compiled by default.
    Requires
      pls_detection_mode = Si2183_DVBS2_PLS_INIT_CMD_PLS_DETECTION_MODE_MANUAL
      pls                = x_init value returned by the SiLabs_API_SAT_Gold_Sequence_Init function implemented at wrapper level.

As from V0.1.3.0:
  <improvement>[traces/commands_responses]
    In all Commands with response fields: Adding a call to Si2183_TRACE_COMMAND_REPLY to trace command response fields.
    In Si2183_L1_GetCommandResponseString: Reworking the function to trace meaningful fields only:
     Command response fields are meaningful only if CTS is 1 and ERR is 0
     If ERR is 1, trace ERR only
     If CTS is 0, trace CTS only
    This only changes the traces, and has no impact on the API behavior.
  <improvement>[traces/DiSEqC] In Si2183_L1_DD_DISEQC_SEND: tracing DiSEqC bytes on a single line.

 As from V0.1.2.0:
  <new_feature>[ISDB-T/AC_data] Adding Si2183_ISDBT_AC_BITS_CMD function to retrieve ISDB-T AC data.
  <improvement>[traces/SET_REG/GET_REG] In Si2183_L1_DD_GET_REG/Si2183_L1_DD_SET_REG: formatting traces for better text alignment

 As from V0.1.0.0:
  <compatibility>[SILABS_SUPERSET] declaring signed   int  Si2183_L1_GET_REG for all media
  <new_feature>[DVB-S2/MULTISTREAM] Adding Si2183_DVBS2_STREAM_INFO and Si2183_DVBS2_STREAM_SELECT commands

 As from V0.0.8.0:
  <improvement>[DD_RESTART/fast i2c] In Si2183_L1_DD_RESTART: Wait at least 10 ms after DD_RESTART to make sure the DSP is started.
   (otherwise some commands may not succeed, especially when using TS_FREQ_RESOL=FINE).

 As from V0.0.7.0:
  <compatibility>[Si2167B/SAT] In Si2183_L1_DVBS_STATUS: compiling code for SAT FREQ OFFSET workaround only when Si2167B_20_COMPATIBLE is defined
  <new_feature> [DD_RESTART] Adding Si2183_DD_RESTART_EXT_CMD
  <new_feature> [DVB-S2/STATUS] Adding fields in DVBS2_STATUS_CMD_REPLY

 As from V0.0.6.0:
  <new_feature>[ISDBT/MODE] Adding dl_a/dl_b/dl_c to Si2183_ISDBT_STATUS_CMD_REPLY_struct
  <improvement>[DD_RESTART/fast i2c] In Si2183_L1_DD_RESTART: Wait at least 6 ms after DD_RESTART to make sure the DSP is started (otherwise some commands may not succeed).

 As from V0.0.5.0:
  <improvement>[POWER_UP] In Si2183_L1_POWER_UP: adding 10ms delay after a power to be sure the firmware is ready to receive a command
  <improvement>[warnings/Si2167B] In Si2183_L1_DVBS2_STATUS: declaring variables used for FREQ OFFSET workaround only if Si2167B_20_COMPATIBLE is defined
  <improvement>[Code_size] Using the textBuffer in Si2183_L1_Context when filling text strings
    In Si2183_L1_DD_TS_PINS

 As from V0.0.4.0:
  <improvement>[code_checker/Si2167B] In Si2183_L1_DVBS2_STATUS: returning with an error if fe_clk_freq register is read as '0'.
   NB: this would happen only if:
    - Si2167B_20_COMPATIBLE is defined
    - The part is a Si2167B
    - i2c communication is suddenly broken after properly retrieving the DVB-S2 status response.

 As from V0.0.2.0:
  <improvement> In Si2183_L1_DD_EXT_AGC_SAT/Si2183_L1_DD_EXT_AGC_TER: removing range checks on agc1_kloopl/agc2_kloop,
   since these will always be within range due to their type. This may have generated warnings with some compilers
   when DEBUG_RANGE_CHECK is defined.

 As from V0.0.0.3:
  <compatibility> [Compilers] Using conversion functions, to be compatible with 8 bytes processing

 As from V0.0.0.0:
  Initial version (based on Si2164 code V0.3.4)
****************************************************************************************/

/* Before including the headers, define SiLevel and SiTAG */
#define   SiLEVEL          1
#define   SiTAG            api->i2c->tag

#define   Si2183_COMMAND_PROTOTYPES
#define   DEBUG_RANGE_CHECK
#include "Si2183_Platform_Definition.h"

/******   conversion functions, used to fill command response fields ***************************************************
  These functions provide compatibility with 8 bytes processing on some compilers
 ***********************************************************************************************************************/
unsigned char Si2183_convert_to_byte (const unsigned char* buffer, unsigned char shift, unsigned char mask) {
  unsigned int rspBuffer = *buffer;
  return ((rspBuffer >> shift) & mask);
}
unsigned long Si2183_convert_to_ulong(const unsigned char* buffer, unsigned char shift, unsigned long mask) {
  return ((( ( (unsigned long)buffer[0]) | ((unsigned long)buffer[1] << 8) | ((unsigned long)buffer[2]<<16) | ((unsigned long)buffer[3]<<24)) >> shift) & mask );
}
unsigned int  Si2183_convert_to_uint (const unsigned char* buffer, unsigned char shift, unsigned int  mask) {
  return ((( ( (unsigned int)buffer[0]) | (((unsigned int)buffer[1]) << 8)) >> shift) & mask);
}
short         Si2183_convert_to_int  (const unsigned char* buffer, unsigned char shift, unsigned int  mask) {
  return ((( ( (unsigned int)buffer[0]) | (((unsigned int)buffer[1]) << 8)) >> shift) & mask);
}
/***********************************************************************************************************************
  Si2183_CurrentResponseStatus function
  Use:        status checking function
              Used to fill the Si2183_COMMON_REPLY_struct members with the ptDataBuffer byte's bits
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure helps reducing the code size
  Parameter: ptDataBuffer  a single byte received when reading a command's response (the first byte)
  Returns:   0 if the err bit (bit 6) is unset, 1 otherwise
 ***********************************************************************************************************************/
unsigned char Si2183_CurrentResponseStatus (L1_Si2183_Context *api, unsigned char ptDataBuffer)
{
    api->status->ddint   =     Si2183_convert_to_byte(&ptDataBuffer, 0, 0x01);
    api->status->scanint =     Si2183_convert_to_byte(&ptDataBuffer, 1, 0x01);
    api->status->err     =     Si2183_convert_to_byte(&ptDataBuffer, 6, 0x01);
    api->status->cts     =     Si2183_convert_to_byte(&ptDataBuffer, 7, 0x01);
  return (api->status->err ? ERROR_Si2183_ERR : NO_Si2183_ERROR);
}

/***********************************************************************************************************************
  Si2183_pollForCTS function
  Use:        CTS checking function
              Used to check the CTS bit until it is set before sending the next command
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure helps reducing the code size
              max timeout = 1000 ms

  Returns:   1 if the CTS bit is set, 0 otherwise
 ***********************************************************************************************************************/
unsigned char Si2183_pollForCTS (L1_Si2183_Context *api)
{
  unsigned char rspByteBuffer[1];
  unsigned int start_time;

  start_time = system_time();

  while (system_time() - start_time <1000)  { /* wait a maximum of 1000ms */
    if (L0_ReadCommandBytes(api->i2c, 1, rspByteBuffer) != 1) {
      SiTRACE("Si2183_pollForCTS ERROR reading byte 0!\n");
      return ERROR_Si2183_POLLING_CTS;
    }
    /* return OK if CTS set */
    if (rspByteBuffer[0] & 0x80) {
      return NO_Si2183_ERROR;
    }
  }

  SiTRACE("Si2183_pollForCTS ERROR CTS Timeout!\n");
  return ERROR_Si2183_CTS_TIMEOUT;
}

/***********************************************************************************************************************
  Si2183_pollForResponse function
  Use:        command response retrieval function
              Used to retrieve the command response in the provided buffer
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure helps reducing the code size
              max timeout = 1000 ms

  Parameter:  nbBytes          the number of response bytes to read
  Parameter:  pByteBuffer      a buffer into which bytes will be stored
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
unsigned char Si2183_pollForResponse (L1_Si2183_Context *api, unsigned int nbBytes, unsigned char *pByteBuffer)
{
  unsigned char debugBuffer[7];
  unsigned int start_time;

  start_time = system_time();

  while (system_time() - start_time <1000)  { /* wait a maximum of 1000ms */
    if ((unsigned int)L0_ReadCommandBytes(api->i2c, nbBytes, pByteBuffer) != nbBytes) {
      SiTRACE("Si2183_pollForResponse ERROR reading byte 0!\n");
      return ERROR_Si2183_POLLING_RESPONSE;
    }
    /* return response err flag if CTS set */
    if (pByteBuffer[0] & 0x80)  {
      /* for debug purpose, read and trace 2 bytes in case the error bit is set */
      if (pByteBuffer[0] & 0x40)  {
        L0_ReadCommandBytes(api->i2c, 7, &(debugBuffer[0]) );
  #ifdef   SiTRACES
/* debug bytes codes
  STATUS_ERR                   0x40
  ERROR_NONE                   0x00
  ERROR_BAD_COMMAND            0x10
  ERROR_BAD_ARG1               0x11
  ERROR_BAD_ARG2               0x12
  ERROR_BAD_ARG3               0x13
  ERROR_BAD_ARG4               0x14
  ERROR_BAD_ARG5               0x15
  ERROR_BAD_ARG6               0x16
  ERROR_BAD_ARG7               0x17
  ERROR_BAD_STANDARD           0x18
  ERROR_BAD_PROPERTY           0x20
  ERROR_BAD_BOOTMODE           0x30
  ERROR_BAD_PATCH              0x31
  ERROR_BAD_NVM                0x32
*/
        SiTRACE("Si2183 debug bytes 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n", debugBuffer[0], debugBuffer[1], debugBuffer[2], debugBuffer[3], debugBuffer[4], debugBuffer[5], debugBuffer[6]);
        if ( pByteBuffer[1] == 0x10) { SiTRACE("BAD_COMMAND\n");  }
        if ((pByteBuffer[1] >= 0x10) && (pByteBuffer[1] <= 0x17)) { SiTRACE("BAD_ARG%d\n",pByteBuffer[1]&0x0f);            }
        if ( pByteBuffer[1] == 0x18) { SiTRACE("BAD_STANDARD (not supported by part '%02d')\n", api->rsp->part_info.part); }
        if ( pByteBuffer[1] == 0x20) { SiTRACE("BAD_PROPERTY 0x%04x\n", api->cmd->set_property.data); }
        if ( pByteBuffer[1] == 0x30) { SiTRACE("BAD_BOOTMODE\n"); }
        if ( pByteBuffer[1] == 0x31) { SiTRACE("BAD_PATCH\n");    }
        if ( pByteBuffer[1] == 0x32) { SiTRACE("BAD_NVM\n");      }
  #endif /* SiTRACES */
      }
      return Si2183_CurrentResponseStatus(api, pByteBuffer[0]);
    }
  }

  SiTRACE("Si2183_pollForResponse ERROR CTS Timeout!\n");
  return ERROR_Si2183_CTS_TIMEOUT;
}

#ifdef    Si2183_CONFIG_CLKIO_CMD
/*---------------------------------------------------*/
/* Si2183_CONFIG_CLKIO COMMAND                                   */
/*---------------------------------------------------*/
unsigned char Si2183_L1_CONFIG_CLKIO              (L1_Si2183_Context *api,
                                                   unsigned char   output,
                                                   unsigned char   pre_driver_str,
                                                   unsigned char   driver_str)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[4];
    api->rsp->config_clkio.STATUS = api->status;

    SiTRACE("Si2183 CONFIG_CLKIO ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((output         > Si2183_CONFIG_CLKIO_CMD_OUTPUT_MAX        ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("OUTPUT %d "        , output         );
    if ((pre_driver_str > Si2183_CONFIG_CLKIO_CMD_PRE_DRIVER_STR_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("PRE_DRIVER_STR %d ", pre_driver_str );
    if ((driver_str     > Si2183_CONFIG_CLKIO_CMD_DRIVER_STR_MAX    ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("DRIVER_STR %d "    , driver_str     );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_CONFIG_CLKIO_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( output         & Si2183_CONFIG_CLKIO_CMD_OUTPUT_MASK         ) << Si2183_CONFIG_CLKIO_CMD_OUTPUT_LSB        |
                                         ( pre_driver_str & Si2183_CONFIG_CLKIO_CMD_PRE_DRIVER_STR_MASK ) << Si2183_CONFIG_CLKIO_CMD_PRE_DRIVER_STR_LSB|
                                         ( driver_str     & Si2183_CONFIG_CLKIO_CMD_DRIVER_STR_MASK     ) << Si2183_CONFIG_CLKIO_CMD_DRIVER_STR_LSB    );

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing CONFIG_CLKIO bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 4, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling CONFIG_CLKIO response\n");
      return error_code;
    }

    api->rsp->config_clkio.mode           = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_CONFIG_CLKIO_RESPONSE_MODE_LSB            , Si2183_CONFIG_CLKIO_RESPONSE_MODE_MASK           );
    api->rsp->config_clkio.pre_driver_str = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_CONFIG_CLKIO_RESPONSE_PRE_DRIVER_STR_LSB  , Si2183_CONFIG_CLKIO_RESPONSE_PRE_DRIVER_STR_MASK );
    api->rsp->config_clkio.driver_str     = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_CONFIG_CLKIO_RESPONSE_DRIVER_STR_LSB      , Si2183_CONFIG_CLKIO_RESPONSE_DRIVER_STR_MASK     );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_CONFIG_CLKIO_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_CONFIG_CLKIO_CMD */
#ifdef    Si2183_CONFIG_I2C_CMD
/*---------------------------------------------------*/
/* Si2183_CONFIG_I2C COMMAND                                       */
/*---------------------------------------------------*/
unsigned char Si2183_L1_CONFIG_I2C                (L1_Si2183_Context *api,
                                                   unsigned char   subcode,
                                                   unsigned char   i2c_broadcast)
{
  #ifdef    DEBUG_RANGE_CHECK
    unsigned char error_code = 0;
  #endif /* DEBUG_RANGE_CHECK */
    unsigned char cmdByteBuffer[3];
    api->rsp->config_i2c.STATUS = api->status;

    SiTRACE("Si2183 CONFIG_I2C ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode       > Si2183_CONFIG_I2C_CMD_SUBCODE_MAX      )  || (subcode       < Si2183_CONFIG_I2C_CMD_SUBCODE_MIN      ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "      , subcode       );
    if ((i2c_broadcast > Si2183_CONFIG_I2C_CMD_I2C_BROADCAST_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("I2C_BROADCAST %d ", i2c_broadcast );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_CONFIG_I2C_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode       & Si2183_CONFIG_I2C_CMD_SUBCODE_MASK       ) << Si2183_CONFIG_I2C_CMD_SUBCODE_LSB      );
    cmdByteBuffer[2] = (unsigned char) ( ( i2c_broadcast & Si2183_CONFIG_I2C_CMD_I2C_BROADCAST_MASK ) << Si2183_CONFIG_I2C_CMD_I2C_BROADCAST_LSB);

    if (L0_WriteCommandBytes(api->i2c, 3, cmdByteBuffer) != 3) {
      SiTRACE("Error writing CONFIG_I2C bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    return NO_Si2183_ERROR;
}
#endif /* Si2183_CONFIG_I2C_CMD */
#ifdef    Si2183_CONFIG_PINS_CMD
/*---------------------------------------------------*/
/* Si2183_CONFIG_PINS COMMAND                                     */
/*---------------------------------------------------*/
unsigned char Si2183_L1_CONFIG_PINS               (L1_Si2183_Context *api,
                                                   unsigned char   gpio0_mode,
                                                   unsigned char   gpio0_read,
                                                   unsigned char   gpio1_mode,
                                                   unsigned char   gpio1_read)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[3];
    unsigned char rspByteBuffer[3];
    api->rsp->config_pins.STATUS = api->status;

    SiTRACE("Si2183 CONFIG_PINS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((gpio0_mode > Si2183_CONFIG_PINS_CMD_GPIO0_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO0_MODE %d ", gpio0_mode );
    if ((gpio0_read > Si2183_CONFIG_PINS_CMD_GPIO0_READ_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO0_READ %d ", gpio0_read );
    if ((gpio1_mode > Si2183_CONFIG_PINS_CMD_GPIO1_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO1_MODE %d ", gpio1_mode );
    if ((gpio1_read > Si2183_CONFIG_PINS_CMD_GPIO1_READ_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO1_READ %d ", gpio1_read );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_CONFIG_PINS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( gpio0_mode & Si2183_CONFIG_PINS_CMD_GPIO0_MODE_MASK ) << Si2183_CONFIG_PINS_CMD_GPIO0_MODE_LSB|
                                         ( gpio0_read & Si2183_CONFIG_PINS_CMD_GPIO0_READ_MASK ) << Si2183_CONFIG_PINS_CMD_GPIO0_READ_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( gpio1_mode & Si2183_CONFIG_PINS_CMD_GPIO1_MODE_MASK ) << Si2183_CONFIG_PINS_CMD_GPIO1_MODE_LSB|
                                         ( gpio1_read & Si2183_CONFIG_PINS_CMD_GPIO1_READ_MASK ) << Si2183_CONFIG_PINS_CMD_GPIO1_READ_LSB);

    if (L0_WriteCommandBytes(api->i2c, 3, cmdByteBuffer) != 3) {
      SiTRACE("Error writing CONFIG_PINS bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 3, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling CONFIG_PINS response\n");
      return error_code;
    }

    api->rsp->config_pins.gpio0_mode  = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_CONFIG_PINS_RESPONSE_GPIO0_MODE_LSB   , Si2183_CONFIG_PINS_RESPONSE_GPIO0_MODE_MASK  );
    api->rsp->config_pins.gpio0_state = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_CONFIG_PINS_RESPONSE_GPIO0_STATE_LSB  , Si2183_CONFIG_PINS_RESPONSE_GPIO0_STATE_MASK );
    api->rsp->config_pins.gpio1_mode  = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_CONFIG_PINS_RESPONSE_GPIO1_MODE_LSB   , Si2183_CONFIG_PINS_RESPONSE_GPIO1_MODE_MASK  );
    api->rsp->config_pins.gpio1_state = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_CONFIG_PINS_RESPONSE_GPIO1_STATE_LSB  , Si2183_CONFIG_PINS_RESPONSE_GPIO1_STATE_MASK );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_CONFIG_PINS_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_CONFIG_PINS_CMD */
#ifdef    Si2183_DD_BER_CMD
/*---------------------------------------------------*/
/* Si2183_DD_BER COMMAND                                               */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DD_BER                    (L1_Si2183_Context *api,
                                                   unsigned char   rst)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[3];
    api->rsp->dd_ber.STATUS = api->status;

    SiTRACE("Si2183 DD_BER ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((rst > Si2183_DD_BER_CMD_RST_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RST %d ", rst );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DD_BER_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( rst & Si2183_DD_BER_CMD_RST_MASK ) << Si2183_DD_BER_CMD_RST_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing DD_BER bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 3, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DD_BER response\n");
      return error_code;
    }

    api->rsp->dd_ber.exp  = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_BER_RESPONSE_EXP_LSB   , Si2183_DD_BER_RESPONSE_EXP_MASK  );
    api->rsp->dd_ber.mant = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DD_BER_RESPONSE_MANT_LSB  , Si2183_DD_BER_RESPONSE_MANT_MASK );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DD_BER_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DD_BER_CMD */
#ifdef    Si2183_DD_CBER_CMD
/*---------------------------------------------------*/
/* Si2183_DD_CBER COMMAND                                             */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DD_CBER                   (L1_Si2183_Context *api,
                                                   unsigned char   rst)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[3];
    api->rsp->dd_cber.STATUS = api->status;

    SiTRACE("Si2183 DD_CBER ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((rst > Si2183_DD_CBER_CMD_RST_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RST %d ", rst );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DD_CBER_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( rst & Si2183_DD_CBER_CMD_RST_MASK ) << Si2183_DD_CBER_CMD_RST_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing DD_CBER bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 3, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DD_CBER response\n");
      return error_code;
    }

    api->rsp->dd_cber.exp  = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_CBER_RESPONSE_EXP_LSB   , Si2183_DD_CBER_RESPONSE_EXP_MASK  );
    api->rsp->dd_cber.mant = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DD_CBER_RESPONSE_MANT_LSB  , Si2183_DD_CBER_RESPONSE_MANT_MASK );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DD_CBER_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DD_CBER_CMD */
#ifdef    SATELLITE_FRONT_END
#ifdef    Si2183_DD_DISEQC_SEND_CMD
/*---------------------------------------------------*/
/* Si2183_DD_DISEQC_SEND COMMAND                               */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DD_DISEQC_SEND            (L1_Si2183_Context *api,
                                                   unsigned char   enable,
                                                   unsigned char   cont_tone,
                                                   unsigned char   tone_burst,
                                                   unsigned char   burst_sel,
                                                   unsigned char   end_seq,
                                                   unsigned char   msg_length,
                                                   unsigned char   msg_byte1,
                                                   unsigned char   msg_byte2,
                                                   unsigned char   msg_byte3,
                                                   unsigned char   msg_byte4,
                                                   unsigned char   msg_byte5,
                                                   unsigned char   msg_byte6)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[8];
    unsigned char rspByteBuffer[1];
    api->rsp->dd_diseqc_send.STATUS = api->status;

    SiTRACE("Si2183 DD_DISEQC_SEND ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((enable     > Si2183_DD_DISEQC_SEND_CMD_ENABLE_MAX    ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("ENABLE %d "    , enable     );
    if ((cont_tone  > Si2183_DD_DISEQC_SEND_CMD_CONT_TONE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CONT_TONE %d " , cont_tone  );
    if ((tone_burst > Si2183_DD_DISEQC_SEND_CMD_TONE_BURST_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("TONE_BURST %d ", tone_burst );
    if ((burst_sel  > Si2183_DD_DISEQC_SEND_CMD_BURST_SEL_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("BURST_SEL %d " , burst_sel  );
    if ((end_seq    > Si2183_DD_DISEQC_SEND_CMD_END_SEQ_MAX   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("END_SEQ %d "   , end_seq    );
    if ((msg_length > Si2183_DD_DISEQC_SEND_CMD_MSG_LENGTH_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("MSG_LENGTH %d ", msg_length );
    SiTRACE("MSG_BYTES 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x " , msg_byte1, msg_byte2, msg_byte3, msg_byte4, msg_byte5, msg_byte6  );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DD_DISEQC_SEND_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( enable     & Si2183_DD_DISEQC_SEND_CMD_ENABLE_MASK     ) << Si2183_DD_DISEQC_SEND_CMD_ENABLE_LSB    |
                                         ( cont_tone  & Si2183_DD_DISEQC_SEND_CMD_CONT_TONE_MASK  ) << Si2183_DD_DISEQC_SEND_CMD_CONT_TONE_LSB |
                                         ( tone_burst & Si2183_DD_DISEQC_SEND_CMD_TONE_BURST_MASK ) << Si2183_DD_DISEQC_SEND_CMD_TONE_BURST_LSB|
                                         ( burst_sel  & Si2183_DD_DISEQC_SEND_CMD_BURST_SEL_MASK  ) << Si2183_DD_DISEQC_SEND_CMD_BURST_SEL_LSB |
                                         ( end_seq    & Si2183_DD_DISEQC_SEND_CMD_END_SEQ_MASK    ) << Si2183_DD_DISEQC_SEND_CMD_END_SEQ_LSB   |
                                         ( msg_length & Si2183_DD_DISEQC_SEND_CMD_MSG_LENGTH_MASK ) << Si2183_DD_DISEQC_SEND_CMD_MSG_LENGTH_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( msg_byte1  & Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE1_MASK  ) << Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE1_LSB );
    cmdByteBuffer[3] = (unsigned char) ( ( msg_byte2  & Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE2_MASK  ) << Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE2_LSB );
    cmdByteBuffer[4] = (unsigned char) ( ( msg_byte3  & Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE3_MASK  ) << Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE3_LSB );
    cmdByteBuffer[5] = (unsigned char) ( ( msg_byte4  & Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE4_MASK  ) << Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE4_LSB );
    cmdByteBuffer[6] = (unsigned char) ( ( msg_byte5  & Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE5_MASK  ) << Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE5_LSB );
    cmdByteBuffer[7] = (unsigned char) ( ( msg_byte6  & Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE6_MASK  ) << Si2183_DD_DISEQC_SEND_CMD_MSG_BYTE6_LSB );

    if (L0_WriteCommandBytes(api->i2c, 8, cmdByteBuffer) != 8) {
      SiTRACE("Error writing DD_DISEQC_SEND bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DD_DISEQC_SEND response\n");
      return error_code;
    }


    return NO_Si2183_ERROR;
}
#endif /* Si2183_DD_DISEQC_SEND_CMD */
#ifdef    Si2183_DD_DISEQC_STATUS_CMD
/*---------------------------------------------------*/
/* Si2183_DD_DISEQC_STATUS COMMAND                           */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DD_DISEQC_STATUS          (L1_Si2183_Context *api,
                                                   unsigned char   listen)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[5];
    api->rsp->dd_diseqc_status.STATUS = api->status;

    SiTRACE("Si2183 DD_DISEQC_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((listen > Si2183_DD_DISEQC_STATUS_CMD_LISTEN_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("LISTEN %d ", listen );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DD_DISEQC_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( listen & Si2183_DD_DISEQC_STATUS_CMD_LISTEN_MASK ) << Si2183_DD_DISEQC_STATUS_CMD_LISTEN_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing DD_DISEQC_STATUS bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 5, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DD_DISEQC_STATUS response\n");
      return error_code;
    }

    api->rsp->dd_diseqc_status.bus_state    = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_DISEQC_STATUS_RESPONSE_BUS_STATE_LSB     , Si2183_DD_DISEQC_STATUS_RESPONSE_BUS_STATE_MASK    );
    api->rsp->dd_diseqc_status.reply_status = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_STATUS_LSB  , Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_STATUS_MASK );
    api->rsp->dd_diseqc_status.reply_length = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_LENGTH_LSB  , Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_LENGTH_MASK );
    api->rsp->dd_diseqc_status.reply_toggle = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_TOGGLE_LSB  , Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_TOGGLE_MASK );
    api->rsp->dd_diseqc_status.end_of_reply = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_DISEQC_STATUS_RESPONSE_END_OF_REPLY_LSB  , Si2183_DD_DISEQC_STATUS_RESPONSE_END_OF_REPLY_MASK );
    api->rsp->dd_diseqc_status.diseqc_mode  = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_DISEQC_STATUS_RESPONSE_DISEQC_MODE_LSB   , Si2183_DD_DISEQC_STATUS_RESPONSE_DISEQC_MODE_MASK  );
    api->rsp->dd_diseqc_status.reply_byte1  = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_BYTE1_LSB   , Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_BYTE1_MASK  );
    api->rsp->dd_diseqc_status.reply_byte2  = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_BYTE2_LSB   , Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_BYTE2_MASK  );
    api->rsp->dd_diseqc_status.reply_byte3  = Si2183_convert_to_byte  (&rspByteBuffer[ 4] , Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_BYTE3_LSB   , Si2183_DD_DISEQC_STATUS_RESPONSE_REPLY_BYTE3_MASK  );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DD_DISEQC_STATUS_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DD_DISEQC_STATUS_CMD */
#ifdef    Si2183_DD_EXT_AGC_SAT_CMD
/*---------------------------------------------------*/
/* Si2183_DD_EXT_AGC_SAT COMMAND                               */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DD_EXT_AGC_SAT            (L1_Si2183_Context *api,
                                                   unsigned char   agc_1_mode,
                                                   unsigned char   agc_1_inv,
                                                   unsigned char   agc_2_mode,
                                                   unsigned char   agc_2_inv,
                                                   unsigned char   agc_1_kloop,
                                                   unsigned char   agc_2_kloop,
                                                   unsigned char   agc_1_min,
                                                   unsigned char   agc_2_min)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[6];
    unsigned char rspByteBuffer[3];
    api->rsp->dd_ext_agc_sat.STATUS = api->status;

    SiTRACE("Si2183 DD_EXT_AGC_SAT ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((agc_1_mode  > Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("AGC_1_MODE %d " , agc_1_mode  );
    if ((agc_1_inv   > Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_INV_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("AGC_1_INV %d "  , agc_1_inv   );
    if ((agc_2_mode  > Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MODE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("AGC_2_MODE %d " , agc_2_mode  );
    if ((agc_2_inv   > Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_INV_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("AGC_2_INV %d "  , agc_2_inv   );
    SiTRACE("AGC_1_KLOOP %d ", agc_1_kloop );
    SiTRACE("AGC_2_KLOOP %d ", agc_2_kloop );
    SiTRACE("AGC_1_MIN %d "  , agc_1_min   );
    SiTRACE("AGC_2_MIN %d "  , agc_2_min   );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DD_EXT_AGC_SAT_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( agc_1_mode  & Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_MASK  ) << Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MODE_LSB |
                                         ( agc_1_inv   & Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_INV_MASK   ) << Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_INV_LSB  |
                                         ( agc_2_mode  & Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MODE_MASK  ) << Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MODE_LSB |
                                         ( agc_2_inv   & Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_INV_MASK   ) << Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_INV_LSB  );
    cmdByteBuffer[2] = (unsigned char) ( ( agc_1_kloop & Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_KLOOP_MASK ) << Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_KLOOP_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( agc_2_kloop & Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_KLOOP_MASK ) << Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_KLOOP_LSB);
    cmdByteBuffer[4] = (unsigned char) ( ( agc_1_min   & Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MIN_MASK   ) << Si2183_DD_EXT_AGC_SAT_CMD_AGC_1_MIN_LSB  );
    cmdByteBuffer[5] = (unsigned char) ( ( agc_2_min   & Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MIN_MASK   ) << Si2183_DD_EXT_AGC_SAT_CMD_AGC_2_MIN_LSB  );

    if (L0_WriteCommandBytes(api->i2c, 6, cmdByteBuffer) != 6) {
      SiTRACE("Error writing DD_EXT_AGC_SAT bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 3, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DD_EXT_AGC_SAT response\n");
      return error_code;
    }

    api->rsp->dd_ext_agc_sat.agc_1_level = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_EXT_AGC_SAT_RESPONSE_AGC_1_LEVEL_LSB  , Si2183_DD_EXT_AGC_SAT_RESPONSE_AGC_1_LEVEL_MASK );
    api->rsp->dd_ext_agc_sat.agc_2_level = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DD_EXT_AGC_SAT_RESPONSE_AGC_2_LEVEL_LSB  , Si2183_DD_EXT_AGC_SAT_RESPONSE_AGC_2_LEVEL_MASK );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DD_EXT_AGC_SAT_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DD_EXT_AGC_SAT_CMD */
#endif /* SATELLITE_FRONT_END */

#ifdef    TERRESTRIAL_FRONT_END
#ifdef    Si2183_DD_EXT_AGC_TER_CMD
/*---------------------------------------------------*/
/* Si2183_DD_EXT_AGC_TER COMMAND                               */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DD_EXT_AGC_TER            (L1_Si2183_Context *api,
                                                   unsigned char   agc_1_mode,
                                                   unsigned char   agc_1_inv,
                                                   unsigned char   agc_2_mode,
                                                   unsigned char   agc_2_inv,
                                                   unsigned char   agc_1_kloop,
                                                   unsigned char   agc_2_kloop,
                                                   unsigned char   agc_1_min,
                                                   unsigned char   agc_2_min)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[6];
    unsigned char rspByteBuffer[3];
    api->rsp->dd_ext_agc_ter.STATUS = api->status;

    SiTRACE("Si2183 DD_EXT_AGC_TER ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((agc_1_mode  > Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MODE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("AGC_1_MODE %d " , agc_1_mode  );
    if ((agc_1_inv   > Si2183_DD_EXT_AGC_TER_CMD_AGC_1_INV_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("AGC_1_INV %d "  , agc_1_inv   );
    if ((agc_2_mode  > Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("AGC_2_MODE %d " , agc_2_mode  );
    if ((agc_2_inv   > Si2183_DD_EXT_AGC_TER_CMD_AGC_2_INV_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("AGC_2_INV %d "  , agc_2_inv   );
    SiTRACE("AGC_1_KLOOP %d ", agc_1_kloop );
    SiTRACE("AGC_2_KLOOP %d ", agc_2_kloop );
    SiTRACE("AGC_1_MIN %d "  , agc_1_min   );
    SiTRACE("AGC_2_MIN %d "  , agc_2_min   );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DD_EXT_AGC_TER_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( agc_1_mode  & Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MODE_MASK  ) << Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MODE_LSB |
                                         ( agc_1_inv   & Si2183_DD_EXT_AGC_TER_CMD_AGC_1_INV_MASK   ) << Si2183_DD_EXT_AGC_TER_CMD_AGC_1_INV_LSB  |
                                         ( agc_2_mode  & Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_MASK  ) << Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MODE_LSB |
                                         ( agc_2_inv   & Si2183_DD_EXT_AGC_TER_CMD_AGC_2_INV_MASK   ) << Si2183_DD_EXT_AGC_TER_CMD_AGC_2_INV_LSB  );
    cmdByteBuffer[2] = (unsigned char) ( ( agc_1_kloop & Si2183_DD_EXT_AGC_TER_CMD_AGC_1_KLOOP_MASK ) << Si2183_DD_EXT_AGC_TER_CMD_AGC_1_KLOOP_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( agc_2_kloop & Si2183_DD_EXT_AGC_TER_CMD_AGC_2_KLOOP_MASK ) << Si2183_DD_EXT_AGC_TER_CMD_AGC_2_KLOOP_LSB);
    cmdByteBuffer[4] = (unsigned char) ( ( agc_1_min   & Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MIN_MASK   ) << Si2183_DD_EXT_AGC_TER_CMD_AGC_1_MIN_LSB  );
    cmdByteBuffer[5] = (unsigned char) ( ( agc_2_min   & Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MIN_MASK   ) << Si2183_DD_EXT_AGC_TER_CMD_AGC_2_MIN_LSB  );

    if (L0_WriteCommandBytes(api->i2c, 6, cmdByteBuffer) != 6) {
      SiTRACE("Error writing DD_EXT_AGC_TER bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 3, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DD_EXT_AGC_TER response\n");
      return error_code;
    }

    api->rsp->dd_ext_agc_ter.agc_1_level = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_EXT_AGC_TER_RESPONSE_AGC_1_LEVEL_LSB  , Si2183_DD_EXT_AGC_TER_RESPONSE_AGC_1_LEVEL_MASK );
    api->rsp->dd_ext_agc_ter.agc_2_level = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DD_EXT_AGC_TER_RESPONSE_AGC_2_LEVEL_LSB  , Si2183_DD_EXT_AGC_TER_RESPONSE_AGC_2_LEVEL_MASK );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DD_EXT_AGC_TER_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DD_EXT_AGC_TER_CMD */
#endif /* TERRESTRIAL_FRONT_END */

#ifdef    Si2183_DD_FER_CMD
/*---------------------------------------------------*/
/* Si2183_DD_FER COMMAND                                               */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DD_FER                    (L1_Si2183_Context *api,
                                                   unsigned char   rst)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[3];
    api->rsp->dd_fer.STATUS = api->status;

    SiTRACE("Si2183 DD_FER ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((rst > Si2183_DD_FER_CMD_RST_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RST %d ", rst );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DD_FER_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( rst & Si2183_DD_FER_CMD_RST_MASK ) << Si2183_DD_FER_CMD_RST_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing DD_FER bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 3, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DD_FER response\n");
      return error_code;
    }

    api->rsp->dd_fer.exp  = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_FER_RESPONSE_EXP_LSB   , Si2183_DD_FER_RESPONSE_EXP_MASK  );
    api->rsp->dd_fer.mant = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DD_FER_RESPONSE_MANT_LSB  , Si2183_DD_FER_RESPONSE_MANT_MASK );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DD_FER_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DD_FER_CMD */
#ifdef    Si2183_DD_GET_REG_CMD
/*---------------------------------------------------*/
/* Si2183_DD_GET_REG COMMAND                                       */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DD_GET_REG                (L1_Si2183_Context *api,
                                                   unsigned char   reg_code_lsb,
                                                   unsigned char   reg_code_mid,
                                                   unsigned char   reg_code_msb)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[4];
    unsigned char rspByteBuffer[5];
    api->rsp->dd_get_reg.STATUS = api->status;

    SiTRACE("Si2183 DD_GET_REG ");
  #ifdef   DEBUG_RANGE_CHECK
    SiTRACE("REG_CODE_LSB %3d ", reg_code_lsb );
    SiTRACE("REG_CODE_MID %3d ", reg_code_mid );
    SiTRACE("REG_CODE_MSB %3d ", reg_code_msb );
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DD_GET_REG_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( reg_code_lsb & Si2183_DD_GET_REG_CMD_REG_CODE_LSB_MASK ) << Si2183_DD_GET_REG_CMD_REG_CODE_LSB_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( reg_code_mid & Si2183_DD_GET_REG_CMD_REG_CODE_MID_MASK ) << Si2183_DD_GET_REG_CMD_REG_CODE_MID_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( reg_code_msb & Si2183_DD_GET_REG_CMD_REG_CODE_MSB_MASK ) << Si2183_DD_GET_REG_CMD_REG_CODE_MSB_LSB);

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing DD_GET_REG bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 5, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DD_GET_REG response\n");
      return error_code;
    }

    api->rsp->dd_get_reg.data1 = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_GET_REG_RESPONSE_DATA1_LSB  , Si2183_DD_GET_REG_RESPONSE_DATA1_MASK );
    api->rsp->dd_get_reg.data2 = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DD_GET_REG_RESPONSE_DATA2_LSB  , Si2183_DD_GET_REG_RESPONSE_DATA2_MASK );
    api->rsp->dd_get_reg.data3 = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_DD_GET_REG_RESPONSE_DATA3_LSB  , Si2183_DD_GET_REG_RESPONSE_DATA3_MASK );
    api->rsp->dd_get_reg.data4 = Si2183_convert_to_byte  (&rspByteBuffer[ 4] , Si2183_DD_GET_REG_RESPONSE_DATA4_LSB  , Si2183_DD_GET_REG_RESPONSE_DATA4_MASK );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DD_GET_REG_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DD_GET_REG_CMD */
#ifdef    Si2183_DD_MP_DEFAULTS_CMD
/*---------------------------------------------------*/
/* Si2183_DD_MP_DEFAULTS COMMAND                               */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DD_MP_DEFAULTS            (L1_Si2183_Context *api,
                                                   unsigned char   mp_a_mode,
                                                   unsigned char   mp_b_mode,
                                                   unsigned char   mp_c_mode,
                                                   unsigned char   mp_d_mode)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[5];
    unsigned char rspByteBuffer[5];
    api->rsp->dd_mp_defaults.STATUS = api->status;

    SiTRACE("Si2183 DD_MP_DEFAULTS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((mp_a_mode > Si2183_DD_MP_DEFAULTS_CMD_MP_A_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("MP_A_MODE %d ", mp_a_mode );
    if ((mp_b_mode > Si2183_DD_MP_DEFAULTS_CMD_MP_B_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("MP_B_MODE %d ", mp_b_mode );
    if ((mp_c_mode > Si2183_DD_MP_DEFAULTS_CMD_MP_C_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("MP_C_MODE %d ", mp_c_mode );
    if ((mp_d_mode > Si2183_DD_MP_DEFAULTS_CMD_MP_D_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("MP_D_MODE %d ", mp_d_mode );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DD_MP_DEFAULTS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( mp_a_mode & Si2183_DD_MP_DEFAULTS_CMD_MP_A_MODE_MASK ) << Si2183_DD_MP_DEFAULTS_CMD_MP_A_MODE_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( mp_b_mode & Si2183_DD_MP_DEFAULTS_CMD_MP_B_MODE_MASK ) << Si2183_DD_MP_DEFAULTS_CMD_MP_B_MODE_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( mp_c_mode & Si2183_DD_MP_DEFAULTS_CMD_MP_C_MODE_MASK ) << Si2183_DD_MP_DEFAULTS_CMD_MP_C_MODE_LSB);
    cmdByteBuffer[4] = (unsigned char) ( ( mp_d_mode & Si2183_DD_MP_DEFAULTS_CMD_MP_D_MODE_MASK ) << Si2183_DD_MP_DEFAULTS_CMD_MP_D_MODE_LSB);

    if (L0_WriteCommandBytes(api->i2c, 5, cmdByteBuffer) != 5) {
      SiTRACE("Error writing DD_MP_DEFAULTS bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 5, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DD_MP_DEFAULTS response\n");
      return error_code;
    }

    api->rsp->dd_mp_defaults.mp_a_mode = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_MP_DEFAULTS_RESPONSE_MP_A_MODE_LSB  , Si2183_DD_MP_DEFAULTS_RESPONSE_MP_A_MODE_MASK );
    api->rsp->dd_mp_defaults.mp_b_mode = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DD_MP_DEFAULTS_RESPONSE_MP_B_MODE_LSB  , Si2183_DD_MP_DEFAULTS_RESPONSE_MP_B_MODE_MASK );
    api->rsp->dd_mp_defaults.mp_c_mode = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_DD_MP_DEFAULTS_RESPONSE_MP_C_MODE_LSB  , Si2183_DD_MP_DEFAULTS_RESPONSE_MP_C_MODE_MASK );
    api->rsp->dd_mp_defaults.mp_d_mode = Si2183_convert_to_byte  (&rspByteBuffer[ 4] , Si2183_DD_MP_DEFAULTS_RESPONSE_MP_D_MODE_LSB  , Si2183_DD_MP_DEFAULTS_RESPONSE_MP_D_MODE_MASK );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DD_MP_DEFAULTS_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DD_MP_DEFAULTS_CMD */
#ifdef    Si2183_DD_PER_CMD
/*---------------------------------------------------*/
/* Si2183_DD_PER COMMAND                                               */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DD_PER                    (L1_Si2183_Context *api,
                                                   unsigned char   rst)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[3];
    api->rsp->dd_per.STATUS = api->status;

    SiTRACE("Si2183 DD_PER ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((rst > Si2183_DD_PER_CMD_RST_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RST %d ", rst );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DD_PER_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( rst & Si2183_DD_PER_CMD_RST_MASK ) << Si2183_DD_PER_CMD_RST_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing DD_PER bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 3, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DD_PER response\n");
      return error_code;
    }

    api->rsp->dd_per.exp  = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_PER_RESPONSE_EXP_LSB   , Si2183_DD_PER_RESPONSE_EXP_MASK  );
    api->rsp->dd_per.mant = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DD_PER_RESPONSE_MANT_LSB  , Si2183_DD_PER_RESPONSE_MANT_MASK );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DD_PER_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DD_PER_CMD */
#ifdef    Si2183_DD_RESTART_CMD
/*---------------------------------------------------*/
/* Si2183_DD_RESTART COMMAND                                       */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DD_RESTART                (L1_Si2183_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[1];
    api->rsp->dd_restart.STATUS = api->status;

    SiTRACE("Si2183 DD_RESTART ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DD_RESTART_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing DD_RESTART bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    /* Wait at least 10 ms after DD_RESTART to make sure the DSP is started (otherwise some commands may not succeed) */
    system_wait(10);

    error_code = Si2183_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DD_RESTART response\n");
      return error_code;
    }


    return NO_Si2183_ERROR;
}
#endif /* Si2183_DD_RESTART_CMD */
#ifdef    Si2183_DD_RESTART_EXT_CMD
/*---------------------------------------------------*/
/* Si2183_DD_RESTART_EXT COMMAND                               */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DD_RESTART_EXT            (L1_Si2183_Context *api,
                                                   unsigned char   freq_plan,
                                                   unsigned char   freq_plan_ts_clk,
                                                   unsigned long   tuned_rf_freq)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[8];
    unsigned char rspByteBuffer[1];
    api->rsp->dd_restart_ext.STATUS = api->status;

    SiTRACE("Si2183 DD_RESTART_EXT ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((freq_plan        > Si2183_DD_RESTART_EXT_CMD_FREQ_PLAN_MAX       ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FREQ_PLAN %d "       , freq_plan        );
    if ((freq_plan_ts_clk > Si2183_DD_RESTART_EXT_CMD_FREQ_PLAN_TS_CLK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FREQ_PLAN_TS_CLK %d ", freq_plan_ts_clk );
    SiTRACE("TUNED_RF_FREQ %ld "   , tuned_rf_freq    );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DD_RESTART_EXT_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( freq_plan        & Si2183_DD_RESTART_EXT_CMD_FREQ_PLAN_MASK        ) << Si2183_DD_RESTART_EXT_CMD_FREQ_PLAN_LSB       |
                                         ( freq_plan_ts_clk & Si2183_DD_RESTART_EXT_CMD_FREQ_PLAN_TS_CLK_MASK ) << Si2183_DD_RESTART_EXT_CMD_FREQ_PLAN_TS_CLK_LSB);
    cmdByteBuffer[2] = (unsigned char)0x00;
    cmdByteBuffer[3] = (unsigned char)0x00;
    cmdByteBuffer[4] = (unsigned char) ( ( tuned_rf_freq    & Si2183_DD_RESTART_EXT_CMD_TUNED_RF_FREQ_MASK    ) << Si2183_DD_RESTART_EXT_CMD_TUNED_RF_FREQ_LSB   );
    cmdByteBuffer[5] = (unsigned char) ((( tuned_rf_freq    & Si2183_DD_RESTART_EXT_CMD_TUNED_RF_FREQ_MASK    ) << Si2183_DD_RESTART_EXT_CMD_TUNED_RF_FREQ_LSB   )>>8);
    cmdByteBuffer[6] = (unsigned char) ((( tuned_rf_freq    & Si2183_DD_RESTART_EXT_CMD_TUNED_RF_FREQ_MASK    ) << Si2183_DD_RESTART_EXT_CMD_TUNED_RF_FREQ_LSB   )>>16);
    cmdByteBuffer[7] = (unsigned char) ((( tuned_rf_freq    & Si2183_DD_RESTART_EXT_CMD_TUNED_RF_FREQ_MASK    ) << Si2183_DD_RESTART_EXT_CMD_TUNED_RF_FREQ_LSB   )>>24);

    if (L0_WriteCommandBytes(api->i2c, 8, cmdByteBuffer) != 8) {
      SiTRACE("Error writing DD_RESTART_EXT bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DD_RESTART_EXT response\n");
      return error_code;
    }


    return NO_Si2183_ERROR;
}
#endif /* Si2183_DD_RESTART_EXT_CMD */
#ifdef    Si2183_DD_SET_REG_CMD
/*---------------------------------------------------*/
/* Si2183_DD_SET_REG COMMAND                                       */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DD_SET_REG                (L1_Si2183_Context *api,
                                                   unsigned char   reg_code_lsb,
                                                   unsigned char   reg_code_mid,
                                                   unsigned char   reg_code_msb,
                                                   unsigned long   value)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[8];
    unsigned char rspByteBuffer[1];
    api->rsp->dd_set_reg.STATUS = api->status;

    SiTRACE("Si2183 DD_SET_REG ");
  #ifdef   DEBUG_RANGE_CHECK
    SiTRACE("REG_CODE_LSB %3d ", reg_code_lsb );
    SiTRACE("REG_CODE_MID %3d ", reg_code_mid );
    SiTRACE("REG_CODE_MSB %3d ", reg_code_msb );
    SiTRACE("VALUE %9ld "      , value        );
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DD_SET_REG_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( reg_code_lsb & Si2183_DD_SET_REG_CMD_REG_CODE_LSB_MASK ) << Si2183_DD_SET_REG_CMD_REG_CODE_LSB_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( reg_code_mid & Si2183_DD_SET_REG_CMD_REG_CODE_MID_MASK ) << Si2183_DD_SET_REG_CMD_REG_CODE_MID_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( reg_code_msb & Si2183_DD_SET_REG_CMD_REG_CODE_MSB_MASK ) << Si2183_DD_SET_REG_CMD_REG_CODE_MSB_LSB);
    cmdByteBuffer[4] = (unsigned char) ( ( value        & Si2183_DD_SET_REG_CMD_VALUE_MASK        ) << Si2183_DD_SET_REG_CMD_VALUE_LSB       );
    cmdByteBuffer[5] = (unsigned char) ((( value        & Si2183_DD_SET_REG_CMD_VALUE_MASK        ) << Si2183_DD_SET_REG_CMD_VALUE_LSB       )>>8);
    cmdByteBuffer[6] = (unsigned char) ((( value        & Si2183_DD_SET_REG_CMD_VALUE_MASK        ) << Si2183_DD_SET_REG_CMD_VALUE_LSB       )>>16);
    cmdByteBuffer[7] = (unsigned char) ((( value        & Si2183_DD_SET_REG_CMD_VALUE_MASK        ) << Si2183_DD_SET_REG_CMD_VALUE_LSB       )>>24);

    if (L0_WriteCommandBytes(api->i2c, 8, cmdByteBuffer) != 8) {
      SiTRACE("Error writing DD_SET_REG bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DD_SET_REG response\n");
      return error_code;
    }


    return NO_Si2183_ERROR;
}
#endif /* Si2183_DD_SET_REG_CMD */
#ifdef    Si2183_DD_SSI_SQI_CMD
/*---------------------------------------------------*/
/* Si2183_DD_SSI_SQI COMMAND                                       */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DD_SSI_SQI                (L1_Si2183_Context *api,
                                                             char  tuner_rssi)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[3];
    api->rsp->dd_ssi_sqi.STATUS = api->status;

    SiTRACE("Si2183 DD_SSI_SQI TUNER_RSSI %d\n", tuner_rssi);

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DD_SSI_SQI_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( tuner_rssi & Si2183_DD_SSI_SQI_CMD_TUNER_RSSI_MASK ) << Si2183_DD_SSI_SQI_CMD_TUNER_RSSI_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing DD_SSI_SQI bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 3, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DD_SSI_SQI response\n");
      return error_code;
    }

    api->rsp->dd_ssi_sqi.ssi = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_SSI_SQI_RESPONSE_SSI_LSB  , Si2183_DD_SSI_SQI_RESPONSE_SSI_MASK );
    api->rsp->dd_ssi_sqi.sqi = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DD_SSI_SQI_RESPONSE_SQI_LSB  , Si2183_DD_SSI_SQI_RESPONSE_SQI_MASK );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DD_SSI_SQI_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DD_SSI_SQI_CMD */
#ifdef    Si2183_DD_STATUS_CMD
/*---------------------------------------------------*/
/* Si2183_DD_STATUS COMMAND                                         */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DD_STATUS                 (L1_Si2183_Context *api,
                                                   unsigned char   intack)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[8];
    api->rsp->dd_status.STATUS = api->status;

    SiTRACE("Si2183 DD_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((intack > Si2183_DD_STATUS_CMD_INTACK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("INTACK %d ", intack );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DD_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si2183_DD_STATUS_CMD_INTACK_MASK ) << Si2183_DD_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing DD_STATUS bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 8, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DD_STATUS response\n");
      return error_code;
    }

    api->rsp->dd_status.pclint       = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_STATUS_RESPONSE_PCLINT_LSB        , Si2183_DD_STATUS_RESPONSE_PCLINT_MASK       );
    api->rsp->dd_status.dlint        = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_STATUS_RESPONSE_DLINT_LSB         , Si2183_DD_STATUS_RESPONSE_DLINT_MASK        );
    api->rsp->dd_status.berint       = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_STATUS_RESPONSE_BERINT_LSB        , Si2183_DD_STATUS_RESPONSE_BERINT_MASK       );
    api->rsp->dd_status.uncorint     = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_STATUS_RESPONSE_UNCORINT_LSB      , Si2183_DD_STATUS_RESPONSE_UNCORINT_MASK     );
    api->rsp->dd_status.rsqint_bit5  = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_STATUS_RESPONSE_RSQINT_BIT5_LSB   , Si2183_DD_STATUS_RESPONSE_RSQINT_BIT5_MASK  );
    api->rsp->dd_status.rsqint_bit6  = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_STATUS_RESPONSE_RSQINT_BIT6_LSB   , Si2183_DD_STATUS_RESPONSE_RSQINT_BIT6_MASK  );
    api->rsp->dd_status.rsqint_bit7  = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_STATUS_RESPONSE_RSQINT_BIT7_LSB   , Si2183_DD_STATUS_RESPONSE_RSQINT_BIT7_MASK  );
    api->rsp->dd_status.pcl          = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DD_STATUS_RESPONSE_PCL_LSB           , Si2183_DD_STATUS_RESPONSE_PCL_MASK          );
    api->rsp->dd_status.dl           = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DD_STATUS_RESPONSE_DL_LSB            , Si2183_DD_STATUS_RESPONSE_DL_MASK           );
    api->rsp->dd_status.ber          = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DD_STATUS_RESPONSE_BER_LSB           , Si2183_DD_STATUS_RESPONSE_BER_MASK          );
    api->rsp->dd_status.uncor        = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DD_STATUS_RESPONSE_UNCOR_LSB         , Si2183_DD_STATUS_RESPONSE_UNCOR_MASK        );
    api->rsp->dd_status.rsqstat_bit5 = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT5_LSB  , Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT5_MASK );
    api->rsp->dd_status.rsqstat_bit6 = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT6_LSB  , Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT6_MASK );
    api->rsp->dd_status.rsqstat_bit7 = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT7_LSB  , Si2183_DD_STATUS_RESPONSE_RSQSTAT_BIT7_MASK );
    api->rsp->dd_status.modulation   = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_DD_STATUS_RESPONSE_MODULATION_LSB    , Si2183_DD_STATUS_RESPONSE_MODULATION_MASK   );
    api->rsp->dd_status.ts_bit_rate  = Si2183_convert_to_uint  (&rspByteBuffer[ 4] , Si2183_DD_STATUS_RESPONSE_TS_BIT_RATE_LSB   , Si2183_DD_STATUS_RESPONSE_TS_BIT_RATE_MASK  );
    api->rsp->dd_status.ts_clk_freq  = Si2183_convert_to_uint  (&rspByteBuffer[ 6] , Si2183_DD_STATUS_RESPONSE_TS_CLK_FREQ_LSB   , Si2183_DD_STATUS_RESPONSE_TS_CLK_FREQ_MASK  );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DD_STATUS_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DD_STATUS_CMD */
#ifdef    Si2183_DD_TS_PINS_CMD
/*---------------------------------------------------*/
/* Si2183_DD_TS_PINS COMMAND                                       */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DD_TS_PINS                (L1_Si2183_Context *api,
                                                   unsigned char   primary_ts_mode,
                                                   unsigned char   primary_ts_activity,
                                                   unsigned char   primary_ts_dir,
                                                   unsigned char   secondary_ts_mode,
                                                   unsigned char   secondary_ts_activity,
                                                   unsigned char   secondary_ts_dir,
                                                   unsigned char   demod_role,
                                                   unsigned long   master_freq)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[8];
    unsigned char rspByteBuffer[3];
    api->rsp->dd_ts_pins.STATUS = api->status;

    SiTRACE("Si2183 DD_TS_PINS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((primary_ts_mode       > Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_MAX      ) ) {error_code++; SiTRACE("\nOut of range: ");};
      if (primary_ts_mode   == Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_DRIVE_TS   ) { SiTRACE("PRIMARY_TS  DRIVE_TS " ); }
      if (primary_ts_mode   == Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_NOT_USED   ) { SiTRACE("PRIMARY_TS  NOT_USED " ); }
      if (primary_ts_mode   == Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_NO_CHANGE  ) { SiTRACE("PRIMARY_TS  NO_CHANGE" ); }
    if ((primary_ts_activity   > Si2183_DD_TS_PINS_CMD_PRIMARY_TS_ACTIVITY_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");};
//      if (primary_ts_activity  == Si2183_DD_TS_PINS_CMD_PRIMARY_TS_ACTIVITY_CLEAR) { SiTRACE("PRIMARY_TS_ACTIVITY  CLEAR "   ); }
//      if (primary_ts_activity  == Si2183_DD_TS_PINS_CMD_PRIMARY_TS_ACTIVITY_RUN  ) { SiTRACE("PRIMARY_TS_ACTIVITY  RUN   "   ); }
    if ((primary_ts_dir        > Si2183_DD_TS_PINS_CMD_PRIMARY_TS_DIR_MAX       ) ) {error_code++; SiTRACE("\nOut of range: ");};
      if (primary_ts_dir       == Si2183_DD_TS_PINS_CMD_PRIMARY_TS_DIR_INPUT     ) {SiTRACE(" INPUT  "   ); }
      if (primary_ts_dir       == Si2183_DD_TS_PINS_CMD_PRIMARY_TS_DIR_OUTPUT    ) {SiTRACE(" OUTPUT "   ); }
    if ((secondary_ts_mode     > Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_MAX    ) ) {error_code++; SiTRACE("\nOut of range: ");};
      if (secondary_ts_mode == Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_DRIVE_TS ) { SiTRACE("SECONDARY_TS  DRIVE_TS  " ); }
      if (secondary_ts_mode == Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_NOT_USED ) { SiTRACE("SECONDARY_TS  NOT_USED  " ); }
      if (secondary_ts_mode == Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_NO_CHANGE) { SiTRACE("SECONDARY_TS  NO_CHANGE " ); }
    if ((secondary_ts_activity > Si2183_DD_TS_PINS_CMD_SECONDARY_TS_ACTIVITY_MAX) ) {error_code++; SiTRACE("\nOut of range: ");};
//      if (secondary_ts_activity  == Si2183_DD_TS_PINS_CMD_SECONDARY_TS_ACTIVITY_CLEAR) { SiTRACE("SECONDARY_TS_ACTIVITY  CLEAR "   ); }
//      if (secondary_ts_activity  == Si2183_DD_TS_PINS_CMD_SECONDARY_TS_ACTIVITY_RUN  ) { SiTRACE("SECONDARY_TS_ACTIVITY  RUN   "   ); }
    if ((secondary_ts_dir        > Si2183_DD_TS_PINS_CMD_SECONDARY_TS_DIR_MAX     ) ) {error_code++; SiTRACE("\nOut of range: ");};
      if (secondary_ts_dir       == Si2183_DD_TS_PINS_CMD_SECONDARY_TS_DIR_INPUT     ) {SiTRACE(" INPUT  "   ); }
      if (secondary_ts_dir       == Si2183_DD_TS_PINS_CMD_SECONDARY_TS_DIR_OUTPUT    ) {SiTRACE(" OUTPUT "   ); }
    if ((demod_role            > Si2183_DD_TS_PINS_CMD_DEMOD_ROLE_MAX           ) ) {error_code++; SiTRACE("\nOut of range: ");};
      if (demod_role       == Si2183_DD_TS_PINS_CMD_DEMOD_ROLE_MASTER              ) {SiTRACE(" DEMOD_ROLE  MASTER               "   ); }
      if (demod_role       == Si2183_DD_TS_PINS_CMD_DEMOD_ROLE_CHANNEL_BONDING_OFF ) {SiTRACE(" DEMOD_ROLE  CHANNEL_BONDING_OFF  "   ); }
      if (demod_role       == Si2183_DD_TS_PINS_CMD_DEMOD_ROLE_SLAVE               ) {SiTRACE(" DEMOD_ROLE  SLAVE                "   ); }
      if (demod_role       == Si2183_DD_TS_PINS_CMD_DEMOD_ROLE_SLAVE_BRIDGE        ) {SiTRACE(" DEMOD_ROLE  SLAVE_BRIDGE         "   ); }
    SiTRACE("MASTER_FREQ  %ld  ", master_freq);
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    } else {
      SiTRACE("\n");
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DD_TS_PINS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( primary_ts_mode       & Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_MASK       ) << Si2183_DD_TS_PINS_CMD_PRIMARY_TS_MODE_LSB      |
                                         ( primary_ts_activity   & Si2183_DD_TS_PINS_CMD_PRIMARY_TS_ACTIVITY_MASK   ) << Si2183_DD_TS_PINS_CMD_PRIMARY_TS_ACTIVITY_LSB  |
                                         ( primary_ts_dir        & Si2183_DD_TS_PINS_CMD_PRIMARY_TS_DIR_MASK        ) << Si2183_DD_TS_PINS_CMD_PRIMARY_TS_DIR_LSB       );
    cmdByteBuffer[2] = (unsigned char) ( ( secondary_ts_mode     & Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_MASK     ) << Si2183_DD_TS_PINS_CMD_SECONDARY_TS_MODE_LSB    |
                                         ( secondary_ts_activity & Si2183_DD_TS_PINS_CMD_SECONDARY_TS_ACTIVITY_MASK ) << Si2183_DD_TS_PINS_CMD_SECONDARY_TS_ACTIVITY_LSB|
                                         ( secondary_ts_dir      & Si2183_DD_TS_PINS_CMD_SECONDARY_TS_DIR_MASK      ) << Si2183_DD_TS_PINS_CMD_SECONDARY_TS_DIR_LSB     );
    cmdByteBuffer[3] = (unsigned char) ( ( demod_role            & Si2183_DD_TS_PINS_CMD_DEMOD_ROLE_MASK            ) << Si2183_DD_TS_PINS_CMD_DEMOD_ROLE_LSB           );
    cmdByteBuffer[4] = (unsigned char) ( ( master_freq           & Si2183_DD_TS_PINS_CMD_MASTER_FREQ_MASK           ) << Si2183_DD_TS_PINS_CMD_MASTER_FREQ_LSB          );
    cmdByteBuffer[5] = (unsigned char) ((( master_freq           & Si2183_DD_TS_PINS_CMD_MASTER_FREQ_MASK           ) << Si2183_DD_TS_PINS_CMD_MASTER_FREQ_LSB          )>>8);
    cmdByteBuffer[6] = (unsigned char) ((( master_freq           & Si2183_DD_TS_PINS_CMD_MASTER_FREQ_MASK           ) << Si2183_DD_TS_PINS_CMD_MASTER_FREQ_LSB          )>>16);
    cmdByteBuffer[7] = (unsigned char) ((( master_freq           & Si2183_DD_TS_PINS_CMD_MASTER_FREQ_MASK           ) << Si2183_DD_TS_PINS_CMD_MASTER_FREQ_LSB          )>>24);

    if (L0_WriteCommandBytes(api->i2c, 8, cmdByteBuffer) != 8) {
      SiTRACE("Error writing DD_TS_PINS bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 3, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DD_TS_PINS response\n");
      return error_code;
    }

    api->rsp->dd_ts_pins.primary_ts_mode       = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_TS_PINS_RESPONSE_PRIMARY_TS_MODE_LSB        , Si2183_DD_TS_PINS_RESPONSE_PRIMARY_TS_MODE_MASK       );
    api->rsp->dd_ts_pins.primary_ts_activity   = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_TS_PINS_RESPONSE_PRIMARY_TS_ACTIVITY_LSB    , Si2183_DD_TS_PINS_RESPONSE_PRIMARY_TS_ACTIVITY_MASK   );
    api->rsp->dd_ts_pins.secondary_ts_mode     = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DD_TS_PINS_RESPONSE_SECONDARY_TS_MODE_LSB      , Si2183_DD_TS_PINS_RESPONSE_SECONDARY_TS_MODE_MASK     );
    api->rsp->dd_ts_pins.secondary_ts_activity = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DD_TS_PINS_RESPONSE_SECONDARY_TS_ACTIVITY_LSB  , Si2183_DD_TS_PINS_RESPONSE_SECONDARY_TS_ACTIVITY_MASK );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DD_TS_PINS_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DD_TS_PINS_CMD */
#ifdef    Si2183_DD_UNCOR_CMD
/*---------------------------------------------------*/
/* Si2183_DD_UNCOR COMMAND                                           */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DD_UNCOR                  (L1_Si2183_Context *api,
                                                   unsigned char   rst)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[3];
    api->rsp->dd_uncor.STATUS = api->status;

    SiTRACE("Si2183 DD_UNCOR ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((rst > Si2183_DD_UNCOR_CMD_RST_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RST %d ", rst );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DD_UNCOR_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( rst & Si2183_DD_UNCOR_CMD_RST_MASK ) << Si2183_DD_UNCOR_CMD_RST_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing DD_UNCOR bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 3, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DD_UNCOR response\n");
      return error_code;
    }

    api->rsp->dd_uncor.uncor_lsb = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DD_UNCOR_RESPONSE_UNCOR_LSB_LSB  , Si2183_DD_UNCOR_RESPONSE_UNCOR_LSB_MASK );
    api->rsp->dd_uncor.uncor_msb = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DD_UNCOR_RESPONSE_UNCOR_MSB_LSB  , Si2183_DD_UNCOR_RESPONSE_UNCOR_MSB_MASK );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DD_UNCOR_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DD_UNCOR_CMD */
#ifdef    Si2183_DEMOD_INFO_CMD
/*---------------------------------------------------*/
/* Si2183_DEMOD_INFO COMMAND                                       */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DEMOD_INFO                (L1_Si2183_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[6];
    api->rsp->demod_info.STATUS = api->status;

    SiTRACE("Si2183 DEMOD_INFO ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DEMOD_INFO_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing DEMOD_INFO bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 6, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DEMOD_INFO response\n");
      return error_code;
    }

    api->rsp->demod_info.reserved = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DEMOD_INFO_RESPONSE_RESERVED_LSB  , Si2183_DEMOD_INFO_RESPONSE_RESERVED_MASK );
    api->rsp->demod_info.div_a    = Si2183_convert_to_uint  (&rspByteBuffer[ 2] , Si2183_DEMOD_INFO_RESPONSE_DIV_A_LSB     , Si2183_DEMOD_INFO_RESPONSE_DIV_A_MASK );
    api->rsp->demod_info.div_b    = Si2183_convert_to_uint  (&rspByteBuffer[ 4] , Si2183_DEMOD_INFO_RESPONSE_DIV_B_LSB     , Si2183_DEMOD_INFO_RESPONSE_DIV_B_MASK );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DEMOD_INFO_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DEMOD_INFO_CMD */
#ifdef    Si2183_DOWNLOAD_DATASET_CONTINUE_CMD
/*---------------------------------------------------*/
/* Si2183_DOWNLOAD_DATASET_CONTINUE COMMAND         */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DOWNLOAD_DATASET_CONTINUE (L1_Si2183_Context *api,
                                                   unsigned char   data0,
                                                   unsigned char   data1,
                                                   unsigned char   data2,
                                                   unsigned char   data3,
                                                   unsigned char   data4,
                                                   unsigned char   data5,
                                                   unsigned char   data6)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[8];
    unsigned char rspByteBuffer[1];
    api->rsp->download_dataset_continue.STATUS = api->status;

    SiTRACE("Si2183 DOWNLOAD_DATASET_CONTINUE ");
  #ifdef   DEBUG_RANGE_CHECK
    SiTRACE("DATA0 %d ", data0 );
    SiTRACE("DATA1 %d ", data1 );
    SiTRACE("DATA2 %d ", data2 );
    SiTRACE("DATA3 %d ", data3 );
    SiTRACE("DATA4 %d ", data4 );
    SiTRACE("DATA5 %d ", data5 );
    SiTRACE("DATA6 %d ", data6 );
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DOWNLOAD_DATASET_CONTINUE_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( data0 & Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA0_MASK ) << Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA0_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( data1 & Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA1_MASK ) << Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA1_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( data2 & Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA2_MASK ) << Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA2_LSB);
    cmdByteBuffer[4] = (unsigned char) ( ( data3 & Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA3_MASK ) << Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA3_LSB);
    cmdByteBuffer[5] = (unsigned char) ( ( data4 & Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA4_MASK ) << Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA4_LSB);
    cmdByteBuffer[6] = (unsigned char) ( ( data5 & Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA5_MASK ) << Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA5_LSB);
    cmdByteBuffer[7] = (unsigned char) ( ( data6 & Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA6_MASK ) << Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_DATA6_LSB);

    if (L0_WriteCommandBytes(api->i2c, 8, cmdByteBuffer) != 8) {
      SiTRACE("Error writing DOWNLOAD_DATASET_CONTINUE bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DOWNLOAD_DATASET_CONTINUE response\n");
      return error_code;
    }


    return NO_Si2183_ERROR;
}
#endif /* Si2183_DOWNLOAD_DATASET_CONTINUE_CMD */
#ifdef    Si2183_DOWNLOAD_DATASET_START_CMD
/*---------------------------------------------------*/
/* Si2183_DOWNLOAD_DATASET_START COMMAND               */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DOWNLOAD_DATASET_START    (L1_Si2183_Context *api,
                                                   unsigned char   dataset_id,
                                                   unsigned char   dataset_checksum,
                                                   unsigned char   data0,
                                                   unsigned char   data1,
                                                   unsigned char   data2,
                                                   unsigned char   data3,
                                                   unsigned char   data4)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[8];
    unsigned char rspByteBuffer[1];
    api->rsp->download_dataset_start.STATUS = api->status;

    SiTRACE("Si2183 DOWNLOAD_DATASET_START ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((dataset_id       > Si2183_DOWNLOAD_DATASET_START_CMD_DATASET_ID_MAX      ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("DATASET_ID %d "      , dataset_id       );
    SiTRACE("DATASET_CHECKSUM %d ", dataset_checksum );
    SiTRACE("DATA0 %d "           , data0            );
    SiTRACE("DATA1 %d "           , data1            );
    SiTRACE("DATA2 %d "           , data2            );
    SiTRACE("DATA3 %d "           , data3            );
    SiTRACE("DATA4 %d "           , data4            );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DOWNLOAD_DATASET_START_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( dataset_id       & Si2183_DOWNLOAD_DATASET_START_CMD_DATASET_ID_MASK       ) << Si2183_DOWNLOAD_DATASET_START_CMD_DATASET_ID_LSB      );
    cmdByteBuffer[2] = (unsigned char) ( ( dataset_checksum & Si2183_DOWNLOAD_DATASET_START_CMD_DATASET_CHECKSUM_MASK ) << Si2183_DOWNLOAD_DATASET_START_CMD_DATASET_CHECKSUM_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( data0            & Si2183_DOWNLOAD_DATASET_START_CMD_DATA0_MASK            ) << Si2183_DOWNLOAD_DATASET_START_CMD_DATA0_LSB           );
    cmdByteBuffer[4] = (unsigned char) ( ( data1            & Si2183_DOWNLOAD_DATASET_START_CMD_DATA1_MASK            ) << Si2183_DOWNLOAD_DATASET_START_CMD_DATA1_LSB           );
    cmdByteBuffer[5] = (unsigned char) ( ( data2            & Si2183_DOWNLOAD_DATASET_START_CMD_DATA2_MASK            ) << Si2183_DOWNLOAD_DATASET_START_CMD_DATA2_LSB           );
    cmdByteBuffer[6] = (unsigned char) ( ( data3            & Si2183_DOWNLOAD_DATASET_START_CMD_DATA3_MASK            ) << Si2183_DOWNLOAD_DATASET_START_CMD_DATA3_LSB           );
    cmdByteBuffer[7] = (unsigned char) ( ( data4            & Si2183_DOWNLOAD_DATASET_START_CMD_DATA4_MASK            ) << Si2183_DOWNLOAD_DATASET_START_CMD_DATA4_LSB           );

    if (L0_WriteCommandBytes(api->i2c, 8, cmdByteBuffer) != 8) {
      SiTRACE("Error writing DOWNLOAD_DATASET_START bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DOWNLOAD_DATASET_START response\n");
      return error_code;
    }


    return NO_Si2183_ERROR;
}
#endif /* Si2183_DOWNLOAD_DATASET_START_CMD */
#ifdef    DEMOD_DVB_C2
#ifdef    Si2183_DVBC2_CTRL_CMD
/*---------------------------------------------------*/
/* Si2183_DVBC2_CTRL COMMAND                                       */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DVBC2_CTRL                (L1_Si2183_Context *api,
                                                   unsigned char   action,
                                                   unsigned long   tuned_rf_freq)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[8];
    unsigned char rspByteBuffer[1];
    api->rsp->dvbc2_ctrl.STATUS = api->status;

    SiTRACE("Si2183 DVBC2_CTRL ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((action        > Si2183_DVBC2_CTRL_CMD_ACTION_MAX       )  || (action        < Si2183_DVBC2_CTRL_CMD_ACTION_MIN       ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("ACTION %d "       , action        );
    SiTRACE("TUNED_RF_FREQ %ld ", tuned_rf_freq );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DVBC2_CTRL_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( action        & Si2183_DVBC2_CTRL_CMD_ACTION_MASK        ) << Si2183_DVBC2_CTRL_CMD_ACTION_LSB       );
    cmdByteBuffer[2] = (unsigned char)0x00;
    cmdByteBuffer[3] = (unsigned char)0x00;
    cmdByteBuffer[4] = (unsigned char) ( ( tuned_rf_freq & Si2183_DVBC2_CTRL_CMD_TUNED_RF_FREQ_MASK ) << Si2183_DVBC2_CTRL_CMD_TUNED_RF_FREQ_LSB);
    cmdByteBuffer[5] = (unsigned char) ((( tuned_rf_freq & Si2183_DVBC2_CTRL_CMD_TUNED_RF_FREQ_MASK ) << Si2183_DVBC2_CTRL_CMD_TUNED_RF_FREQ_LSB)>>8);
    cmdByteBuffer[6] = (unsigned char) ((( tuned_rf_freq & Si2183_DVBC2_CTRL_CMD_TUNED_RF_FREQ_MASK ) << Si2183_DVBC2_CTRL_CMD_TUNED_RF_FREQ_LSB)>>16);
    cmdByteBuffer[7] = (unsigned char) ((( tuned_rf_freq & Si2183_DVBC2_CTRL_CMD_TUNED_RF_FREQ_MASK ) << Si2183_DVBC2_CTRL_CMD_TUNED_RF_FREQ_LSB)>>24);

    if (L0_WriteCommandBytes(api->i2c, 8, cmdByteBuffer) != 8) {
      SiTRACE("Error writing DVBC2_CTRL bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DVBC2_CTRL response\n");
      return error_code;
    }


    return NO_Si2183_ERROR;
}
#endif /* Si2183_DVBC2_CTRL_CMD */
#ifdef    Si2183_DVBC2_DS_INFO_CMD
/*---------------------------------------------------*/
/* Si2183_DVBC2_DS_INFO COMMAND                                 */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DVBC2_DS_INFO             (L1_Si2183_Context *api,
                                                   unsigned char   ds_index_or_id,
                                                   unsigned char   ds_select_index_or_id)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[3];
    unsigned char rspByteBuffer[8];
    api->rsp->dvbc2_ds_info.STATUS = api->status;

    SiTRACE("Si2183 DVBC2_DS_INFO ");
  #ifdef   DEBUG_RANGE_CHECK
    SiTRACE("DS_INDEX_OR_ID %d "       , ds_index_or_id        );
    if ((ds_select_index_or_id > Si2183_DVBC2_DS_INFO_CMD_DS_SELECT_INDEX_OR_ID_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("DS_SELECT_INDEX_OR_ID %d ", ds_select_index_or_id );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DVBC2_DS_INFO_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( ds_index_or_id        & Si2183_DVBC2_DS_INFO_CMD_DS_INDEX_OR_ID_MASK        ) << Si2183_DVBC2_DS_INFO_CMD_DS_INDEX_OR_ID_LSB       );
    cmdByteBuffer[2] = (unsigned char) ( ( ds_select_index_or_id & Si2183_DVBC2_DS_INFO_CMD_DS_SELECT_INDEX_OR_ID_MASK ) << Si2183_DVBC2_DS_INFO_CMD_DS_SELECT_INDEX_OR_ID_LSB);

    if (L0_WriteCommandBytes(api->i2c, 3, cmdByteBuffer) != 3) {
      SiTRACE("Error writing DVBC2_DS_INFO bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 8, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DVBC2_DS_INFO response\n");
      return error_code;
    }

    api->rsp->dvbc2_ds_info.ds_id              = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBC2_DS_INFO_RESPONSE_DS_ID_LSB               , Si2183_DVBC2_DS_INFO_RESPONSE_DS_ID_MASK              );
    api->rsp->dvbc2_ds_info.dslice_num_plp     = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBC2_DS_INFO_RESPONSE_DSLICE_NUM_PLP_LSB      , Si2183_DVBC2_DS_INFO_RESPONSE_DSLICE_NUM_PLP_MASK     );
    api->rsp->dvbc2_ds_info.reserved_2         = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_DVBC2_DS_INFO_RESPONSE_RESERVED_2_LSB          , Si2183_DVBC2_DS_INFO_RESPONSE_RESERVED_2_MASK         );
    api->rsp->dvbc2_ds_info.dslice_tune_pos_hz = Si2183_convert_to_ulong (&rspByteBuffer[ 4] , Si2183_DVBC2_DS_INFO_RESPONSE_DSLICE_TUNE_POS_HZ_LSB  , Si2183_DVBC2_DS_INFO_RESPONSE_DSLICE_TUNE_POS_HZ_MASK );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DVBC2_DS_INFO_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DVBC2_DS_INFO_CMD */
#ifdef    Si2183_DVBC2_DS_PLP_SELECT_CMD
/*---------------------------------------------------*/
/* Si2183_DVBC2_DS_PLP_SELECT COMMAND                     */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DVBC2_DS_PLP_SELECT       (L1_Si2183_Context *api,
                                                   unsigned char   plp_id,
                                                   unsigned char   id_sel_mode,
                                                   unsigned char   ds_id)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[4];
    unsigned char rspByteBuffer[1];
    api->rsp->dvbc2_ds_plp_select.STATUS = api->status;

    SiTRACE("Si2183 DVBC2_DS_PLP_SELECT ");
  #ifdef   DEBUG_RANGE_CHECK
    SiTRACE("PLP_ID %d "     , plp_id      );
    if ((id_sel_mode > Si2183_DVBC2_DS_PLP_SELECT_CMD_ID_SEL_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("ID_SEL_MODE %d ", id_sel_mode );
    SiTRACE("DS_ID %d "      , ds_id       );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DVBC2_DS_PLP_SELECT_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( plp_id      & Si2183_DVBC2_DS_PLP_SELECT_CMD_PLP_ID_MASK      ) << Si2183_DVBC2_DS_PLP_SELECT_CMD_PLP_ID_LSB     );
    cmdByteBuffer[2] = (unsigned char) ( ( id_sel_mode & Si2183_DVBC2_DS_PLP_SELECT_CMD_ID_SEL_MODE_MASK ) << Si2183_DVBC2_DS_PLP_SELECT_CMD_ID_SEL_MODE_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( ds_id       & Si2183_DVBC2_DS_PLP_SELECT_CMD_DS_ID_MASK       ) << Si2183_DVBC2_DS_PLP_SELECT_CMD_DS_ID_LSB      );

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing DVBC2_DS_PLP_SELECT bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DVBC2_DS_PLP_SELECT response\n");
      return error_code;
    }


    return NO_Si2183_ERROR;
}
#endif /* Si2183_DVBC2_DS_PLP_SELECT_CMD */
#ifdef    Si2183_DVBC2_PLP_INFO_CMD
/*---------------------------------------------------*/
/* Si2183_DVBC2_PLP_INFO COMMAND                               */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DVBC2_PLP_INFO            (L1_Si2183_Context *api,
                                                   unsigned char   plp_index,
                                                   unsigned char   plp_info_ds_mode,
                                                   unsigned char   ds_index)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[4];
    unsigned char rspByteBuffer[3];
    api->rsp->dvbc2_plp_info.STATUS = api->status;

    SiTRACE("Si2183 DVBC2_PLP_INFO ");
  #ifdef   DEBUG_RANGE_CHECK
    SiTRACE("PLP_INDEX %d "       , plp_index        );
    if ((plp_info_ds_mode > Si2183_DVBC2_PLP_INFO_CMD_PLP_INFO_DS_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("PLP_INFO_DS_MODE %d ", plp_info_ds_mode );
    SiTRACE("DS_INDEX %d "        , ds_index         );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DVBC2_PLP_INFO_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( plp_index        & Si2183_DVBC2_PLP_INFO_CMD_PLP_INDEX_MASK        ) << Si2183_DVBC2_PLP_INFO_CMD_PLP_INDEX_LSB       );
    cmdByteBuffer[2] = (unsigned char) ( ( plp_info_ds_mode & Si2183_DVBC2_PLP_INFO_CMD_PLP_INFO_DS_MODE_MASK ) << Si2183_DVBC2_PLP_INFO_CMD_PLP_INFO_DS_MODE_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( ds_index         & Si2183_DVBC2_PLP_INFO_CMD_DS_INDEX_MASK         ) << Si2183_DVBC2_PLP_INFO_CMD_DS_INDEX_LSB        );

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing DVBC2_PLP_INFO bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 3, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DVBC2_PLP_INFO response\n");
      return error_code;
    }

    api->rsp->dvbc2_plp_info.plp_id           = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_ID_LSB            , Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_ID_MASK           );
    api->rsp->dvbc2_plp_info.plp_payload_type = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_PAYLOAD_TYPE_LSB  , Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_PAYLOAD_TYPE_MASK );
    api->rsp->dvbc2_plp_info.plp_type         = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_TYPE_LSB          , Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_TYPE_MASK         );
    api->rsp->dvbc2_plp_info.plp_bundled      = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_BUNDLED_LSB       , Si2183_DVBC2_PLP_INFO_RESPONSE_PLP_BUNDLED_MASK      );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DVBC2_PLP_INFO_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DVBC2_PLP_INFO_CMD */
#ifdef    Si2183_DVBC2_STATUS_CMD
/*---------------------------------------------------*/
/* Si2183_DVBC2_STATUS COMMAND                                   */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DVBC2_STATUS              (L1_Si2183_Context *api,
                                                   unsigned char   intack)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[16];
    api->rsp->dvbc2_status.STATUS = api->status;

    SiTRACE("Si2183 DVBC2_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((intack > Si2183_DVBC2_STATUS_CMD_INTACK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("INTACK %d ", intack );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DVBC2_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si2183_DVBC2_STATUS_CMD_INTACK_MASK ) << Si2183_DVBC2_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing DVBC2_STATUS bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 16, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DVBC2_STATUS response\n");
      return error_code;
    }

    api->rsp->dvbc2_status.pclint        = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBC2_STATUS_RESPONSE_PCLINT_LSB         , Si2183_DVBC2_STATUS_RESPONSE_PCLINT_MASK        );
    api->rsp->dvbc2_status.dlint         = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBC2_STATUS_RESPONSE_DLINT_LSB          , Si2183_DVBC2_STATUS_RESPONSE_DLINT_MASK         );
    api->rsp->dvbc2_status.berint        = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBC2_STATUS_RESPONSE_BERINT_LSB         , Si2183_DVBC2_STATUS_RESPONSE_BERINT_MASK        );
    api->rsp->dvbc2_status.uncorint      = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBC2_STATUS_RESPONSE_UNCORINT_LSB       , Si2183_DVBC2_STATUS_RESPONSE_UNCORINT_MASK      );
    api->rsp->dvbc2_status.notdvbc2int   = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBC2_STATUS_RESPONSE_NOTDVBC2INT_LSB    , Si2183_DVBC2_STATUS_RESPONSE_NOTDVBC2INT_MASK   );
    api->rsp->dvbc2_status.reqint        = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBC2_STATUS_RESPONSE_REQINT_LSB         , Si2183_DVBC2_STATUS_RESPONSE_REQINT_MASK        );
    api->rsp->dvbc2_status.ewbsint       = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBC2_STATUS_RESPONSE_EWBSINT_LSB        , Si2183_DVBC2_STATUS_RESPONSE_EWBSINT_MASK       );
    api->rsp->dvbc2_status.pcl           = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBC2_STATUS_RESPONSE_PCL_LSB            , Si2183_DVBC2_STATUS_RESPONSE_PCL_MASK           );
    api->rsp->dvbc2_status.dl            = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBC2_STATUS_RESPONSE_DL_LSB             , Si2183_DVBC2_STATUS_RESPONSE_DL_MASK            );
    api->rsp->dvbc2_status.ber           = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBC2_STATUS_RESPONSE_BER_LSB            , Si2183_DVBC2_STATUS_RESPONSE_BER_MASK           );
    api->rsp->dvbc2_status.uncor         = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBC2_STATUS_RESPONSE_UNCOR_LSB          , Si2183_DVBC2_STATUS_RESPONSE_UNCOR_MASK         );
    api->rsp->dvbc2_status.notdvbc2      = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBC2_STATUS_RESPONSE_NOTDVBC2_LSB       , Si2183_DVBC2_STATUS_RESPONSE_NOTDVBC2_MASK      );
    api->rsp->dvbc2_status.req           = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBC2_STATUS_RESPONSE_REQ_LSB            , Si2183_DVBC2_STATUS_RESPONSE_REQ_MASK           );
    api->rsp->dvbc2_status.ewbs          = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBC2_STATUS_RESPONSE_EWBS_LSB           , Si2183_DVBC2_STATUS_RESPONSE_EWBS_MASK          );
    api->rsp->dvbc2_status.cnr           = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_DVBC2_STATUS_RESPONSE_CNR_LSB            , Si2183_DVBC2_STATUS_RESPONSE_CNR_MASK           );
    api->rsp->dvbc2_status.afc_freq      = Si2183_convert_to_int   (&rspByteBuffer[ 4] , Si2183_DVBC2_STATUS_RESPONSE_AFC_FREQ_LSB       , Si2183_DVBC2_STATUS_RESPONSE_AFC_FREQ_MASK      );
    api->rsp->dvbc2_status.timing_offset = Si2183_convert_to_int   (&rspByteBuffer[ 6] , Si2183_DVBC2_STATUS_RESPONSE_TIMING_OFFSET_LSB  , Si2183_DVBC2_STATUS_RESPONSE_TIMING_OFFSET_MASK );
    api->rsp->dvbc2_status.dvbc2_status  = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_DVBC2_STATUS_RESPONSE_DVBC2_STATUS_LSB   , Si2183_DVBC2_STATUS_RESPONSE_DVBC2_STATUS_MASK  );
    api->rsp->dvbc2_status.constellation = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_DVBC2_STATUS_RESPONSE_CONSTELLATION_LSB  , Si2183_DVBC2_STATUS_RESPONSE_CONSTELLATION_MASK );
    api->rsp->dvbc2_status.sp_inv        = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_DVBC2_STATUS_RESPONSE_SP_INV_LSB         , Si2183_DVBC2_STATUS_RESPONSE_SP_INV_MASK        );
    api->rsp->dvbc2_status.code_rate     = Si2183_convert_to_byte  (&rspByteBuffer[ 9] , Si2183_DVBC2_STATUS_RESPONSE_CODE_RATE_LSB      , Si2183_DVBC2_STATUS_RESPONSE_CODE_RATE_MASK     );
    api->rsp->dvbc2_status.guard_int     = Si2183_convert_to_byte  (&rspByteBuffer[ 9] , Si2183_DVBC2_STATUS_RESPONSE_GUARD_INT_LSB      , Si2183_DVBC2_STATUS_RESPONSE_GUARD_INT_MASK     );
    api->rsp->dvbc2_status.ds_id         = Si2183_convert_to_byte  (&rspByteBuffer[10] , Si2183_DVBC2_STATUS_RESPONSE_DS_ID_LSB          , Si2183_DVBC2_STATUS_RESPONSE_DS_ID_MASK         );
    api->rsp->dvbc2_status.plp_id        = Si2183_convert_to_byte  (&rspByteBuffer[11] , Si2183_DVBC2_STATUS_RESPONSE_PLP_ID_LSB         , Si2183_DVBC2_STATUS_RESPONSE_PLP_ID_MASK        );
    api->rsp->dvbc2_status.rf_freq       = Si2183_convert_to_ulong (&rspByteBuffer[12] , Si2183_DVBC2_STATUS_RESPONSE_RF_FREQ_LSB        , Si2183_DVBC2_STATUS_RESPONSE_RF_FREQ_MASK       );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DVBC2_STATUS_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DVBC2_STATUS_CMD */
#ifdef    Si2183_DVBC2_SYS_INFO_CMD
/*---------------------------------------------------*/
/* Si2183_DVBC2_SYS_INFO COMMAND                               */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DVBC2_SYS_INFO            (L1_Si2183_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[16];
    api->rsp->dvbc2_sys_info.STATUS = api->status;

    SiTRACE("Si2183 DVBC2_SYS_INFO ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DVBC2_SYS_INFO_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing DVBC2_SYS_INFO bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 16, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DVBC2_SYS_INFO response\n");
      return error_code;
    }

    api->rsp->dvbc2_sys_info.num_dslice         = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBC2_SYS_INFO_RESPONSE_NUM_DSLICE_LSB          , Si2183_DVBC2_SYS_INFO_RESPONSE_NUM_DSLICE_MASK         );
    api->rsp->dvbc2_sys_info.network_id         = Si2183_convert_to_uint  (&rspByteBuffer[ 2] , Si2183_DVBC2_SYS_INFO_RESPONSE_NETWORK_ID_LSB          , Si2183_DVBC2_SYS_INFO_RESPONSE_NETWORK_ID_MASK         );
    api->rsp->dvbc2_sys_info.c2_bandwidth_hz    = Si2183_convert_to_ulong (&rspByteBuffer[ 4] , Si2183_DVBC2_SYS_INFO_RESPONSE_C2_BANDWIDTH_HZ_LSB     , Si2183_DVBC2_SYS_INFO_RESPONSE_C2_BANDWIDTH_HZ_MASK    );
    api->rsp->dvbc2_sys_info.start_frequency_hz = Si2183_convert_to_ulong (&rspByteBuffer[ 8] , Si2183_DVBC2_SYS_INFO_RESPONSE_START_FREQUENCY_HZ_LSB  , Si2183_DVBC2_SYS_INFO_RESPONSE_START_FREQUENCY_HZ_MASK );
    api->rsp->dvbc2_sys_info.c2_system_id       = Si2183_convert_to_uint  (&rspByteBuffer[12] , Si2183_DVBC2_SYS_INFO_RESPONSE_C2_SYSTEM_ID_LSB        , Si2183_DVBC2_SYS_INFO_RESPONSE_C2_SYSTEM_ID_MASK       );
    api->rsp->dvbc2_sys_info.reserved_4_lsb     = Si2183_convert_to_byte  (&rspByteBuffer[14] , Si2183_DVBC2_SYS_INFO_RESPONSE_RESERVED_4_LSB_LSB      , Si2183_DVBC2_SYS_INFO_RESPONSE_RESERVED_4_LSB_MASK     );
    api->rsp->dvbc2_sys_info.reserved_4_msb     = Si2183_convert_to_byte  (&rspByteBuffer[15] , Si2183_DVBC2_SYS_INFO_RESPONSE_RESERVED_4_MSB_LSB      , Si2183_DVBC2_SYS_INFO_RESPONSE_RESERVED_4_MSB_MASK     );
    api->rsp->dvbc2_sys_info.c2_version         = Si2183_convert_to_byte  (&rspByteBuffer[15] , Si2183_DVBC2_SYS_INFO_RESPONSE_C2_VERSION_LSB          , Si2183_DVBC2_SYS_INFO_RESPONSE_C2_VERSION_MASK         );
    api->rsp->dvbc2_sys_info.ews                = Si2183_convert_to_byte  (&rspByteBuffer[15] , Si2183_DVBC2_SYS_INFO_RESPONSE_EWS_LSB                 , Si2183_DVBC2_SYS_INFO_RESPONSE_EWS_MASK                );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DVBC2_SYS_INFO_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DVBC2_SYS_INFO_CMD */
#endif /* DEMOD_DVB_C2 */

#ifdef    DEMOD_DVB_C
#ifdef    Si2183_DVBC_STATUS_CMD
/*---------------------------------------------------*/
/* Si2183_DVBC_STATUS COMMAND                                     */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DVBC_STATUS               (L1_Si2183_Context *api,
                                                   unsigned char   intack)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[9];
    api->rsp->dvbc_status.STATUS = api->status;

    SiTRACE("Si2183 DVBC_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((intack > Si2183_DVBC_STATUS_CMD_INTACK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("INTACK %d ", intack );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DVBC_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si2183_DVBC_STATUS_CMD_INTACK_MASK ) << Si2183_DVBC_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing DVBC_STATUS bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 9, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DVBC_STATUS response\n");
      return error_code;
    }

    api->rsp->dvbc_status.pclint        = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBC_STATUS_RESPONSE_PCLINT_LSB         , Si2183_DVBC_STATUS_RESPONSE_PCLINT_MASK        );
    api->rsp->dvbc_status.dlint         = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBC_STATUS_RESPONSE_DLINT_LSB          , Si2183_DVBC_STATUS_RESPONSE_DLINT_MASK         );
    api->rsp->dvbc_status.berint        = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBC_STATUS_RESPONSE_BERINT_LSB         , Si2183_DVBC_STATUS_RESPONSE_BERINT_MASK        );
    api->rsp->dvbc_status.uncorint      = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBC_STATUS_RESPONSE_UNCORINT_LSB       , Si2183_DVBC_STATUS_RESPONSE_UNCORINT_MASK      );
    api->rsp->dvbc_status.notdvbcint    = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBC_STATUS_RESPONSE_NOTDVBCINT_LSB     , Si2183_DVBC_STATUS_RESPONSE_NOTDVBCINT_MASK    );
    api->rsp->dvbc_status.pcl           = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBC_STATUS_RESPONSE_PCL_LSB            , Si2183_DVBC_STATUS_RESPONSE_PCL_MASK           );
    api->rsp->dvbc_status.dl            = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBC_STATUS_RESPONSE_DL_LSB             , Si2183_DVBC_STATUS_RESPONSE_DL_MASK            );
    api->rsp->dvbc_status.ber           = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBC_STATUS_RESPONSE_BER_LSB            , Si2183_DVBC_STATUS_RESPONSE_BER_MASK           );
    api->rsp->dvbc_status.uncor         = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBC_STATUS_RESPONSE_UNCOR_LSB          , Si2183_DVBC_STATUS_RESPONSE_UNCOR_MASK         );
    api->rsp->dvbc_status.notdvbc       = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBC_STATUS_RESPONSE_NOTDVBC_LSB        , Si2183_DVBC_STATUS_RESPONSE_NOTDVBC_MASK       );
    api->rsp->dvbc_status.cnr           = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_DVBC_STATUS_RESPONSE_CNR_LSB            , Si2183_DVBC_STATUS_RESPONSE_CNR_MASK           );
    api->rsp->dvbc_status.afc_freq      = Si2183_convert_to_int   (&rspByteBuffer[ 4] , Si2183_DVBC_STATUS_RESPONSE_AFC_FREQ_LSB       , Si2183_DVBC_STATUS_RESPONSE_AFC_FREQ_MASK      );
    api->rsp->dvbc_status.timing_offset = Si2183_convert_to_int   (&rspByteBuffer[ 6] , Si2183_DVBC_STATUS_RESPONSE_TIMING_OFFSET_LSB  , Si2183_DVBC_STATUS_RESPONSE_TIMING_OFFSET_MASK );
    api->rsp->dvbc_status.constellation = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_DVBC_STATUS_RESPONSE_CONSTELLATION_LSB  , Si2183_DVBC_STATUS_RESPONSE_CONSTELLATION_MASK );
    api->rsp->dvbc_status.sp_inv        = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_DVBC_STATUS_RESPONSE_SP_INV_LSB         , Si2183_DVBC_STATUS_RESPONSE_SP_INV_MASK        );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DVBC_STATUS_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DVBC_STATUS_CMD */
#endif /* DEMOD_DVB_C */

signed    int Si2183_L1_GET_REG           (L1_Si2183_Context *api, unsigned char   reg_code_lsb, unsigned char   reg_code_mid, unsigned char   reg_code_msb) {
  int res;
  res = 0;
#ifdef    Si2183_DD_GET_REG_CMD
  if (Si2183_L1_DD_GET_REG (api, reg_code_lsb, reg_code_mid, reg_code_msb) != NO_Si2183_ERROR) {
    SiERROR("Error calling Si2183_L1_DD_GET_REG\n");
    return 0;
  }
  res =  (api->rsp->dd_get_reg.data4<<24)
        +(api->rsp->dd_get_reg.data3<<16)
        +(api->rsp->dd_get_reg.data2<<8 )
        +(api->rsp->dd_get_reg.data1<<0 );
#endif /* Si2183_DD_GET_REG_CMD */
  return res;
}

#ifdef    DEMOD_DVB_S_S2_DSS
#ifdef    Si2183_DVBS2_PLS_INIT_CMD
/*---------------------------------------------------*/
/* Si2183_DVBS2_PLS_INIT COMMAND                               */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DVBS2_PLS_INIT            (L1_Si2183_Context *api,
                                                   unsigned char   pls_detection_mode,
                                                   unsigned long   pls)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[8];
    unsigned char rspByteBuffer[1];
    api->rsp->dvbs2_pls_init.STATUS = api->status;

    SiTRACE("Si2183 DVBS2_PLS_INIT ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((pls_detection_mode > Si2183_DVBS2_PLS_INIT_CMD_PLS_DETECTION_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("PLS_DETECTION_MODE %d ", pls_detection_mode );
    if ((pls                > Si2183_DVBS2_PLS_INIT_CMD_PLS_MAX               ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("PLS %ld "               , pls                );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DVBS2_PLS_INIT_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( pls_detection_mode & Si2183_DVBS2_PLS_INIT_CMD_PLS_DETECTION_MODE_MASK ) << Si2183_DVBS2_PLS_INIT_CMD_PLS_DETECTION_MODE_LSB);
    cmdByteBuffer[2] = (unsigned char)0x00;
    cmdByteBuffer[3] = (unsigned char)0x00;
    cmdByteBuffer[4] = (unsigned char) ( ( pls                & Si2183_DVBS2_PLS_INIT_CMD_PLS_MASK                ) << Si2183_DVBS2_PLS_INIT_CMD_PLS_LSB               );
    cmdByteBuffer[5] = (unsigned char) ((( pls                & Si2183_DVBS2_PLS_INIT_CMD_PLS_MASK                ) << Si2183_DVBS2_PLS_INIT_CMD_PLS_LSB               )>>8);
    cmdByteBuffer[6] = (unsigned char) ((( pls                & Si2183_DVBS2_PLS_INIT_CMD_PLS_MASK                ) << Si2183_DVBS2_PLS_INIT_CMD_PLS_LSB               )>>16);
    cmdByteBuffer[7] = (unsigned char) ((( pls                & Si2183_DVBS2_PLS_INIT_CMD_PLS_MASK                ) << Si2183_DVBS2_PLS_INIT_CMD_PLS_LSB               )>>24);

    if (L0_WriteCommandBytes(api->i2c, 8, cmdByteBuffer) != 8) {
      SiTRACE("Error writing DVBS2_PLS_INIT bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DVBS2_PLS_INIT response\n");
      return error_code;
    }


    return NO_Si2183_ERROR;
}
#endif /* Si2183_DVBS2_PLS_INIT_CMD */
#ifdef    Si2183_DVBS2_STATUS_CMD
/*---------------------------------------------------*/
/* Si2183_DVBS2_STATUS COMMAND                                   */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DVBS2_STATUS              (L1_Si2183_Context *api,
                                                   unsigned char   intack)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[13];
#ifdef    Si2167B_20_COMPATIBLE
  /* FREQ OFFSET workaround variables (only for Si2167B/Si2166B compatibility) */
    unsigned int adc_mode;
    unsigned int spectral_inv_status_s2;
    int freq_corr_sat;
    int if_freq_shift;
    int fe_clk_freq;
    int freq_offset_tmp1;
    int freq_offset_tmp2;
    int freq_offset;
  /* end FREQ OFFSET workaround variables */
#endif /* Si2167B_20_COMPATIBLE */
    api->rsp->dvbs2_status.STATUS = api->status;

    SiTRACE("Si2183 DVBS2_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((intack > Si2183_DVBS2_STATUS_CMD_INTACK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("INTACK %d ", intack );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DVBS2_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si2183_DVBS2_STATUS_CMD_INTACK_MASK ) << Si2183_DVBS2_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing DVBS2_STATUS bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 13, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DVBS2_STATUS response\n");
      return error_code;
    }

    api->rsp->dvbs2_status.pclint        = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBS2_STATUS_RESPONSE_PCLINT_LSB         , Si2183_DVBS2_STATUS_RESPONSE_PCLINT_MASK        );
    api->rsp->dvbs2_status.dlint         = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBS2_STATUS_RESPONSE_DLINT_LSB          , Si2183_DVBS2_STATUS_RESPONSE_DLINT_MASK         );
    api->rsp->dvbs2_status.berint        = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBS2_STATUS_RESPONSE_BERINT_LSB         , Si2183_DVBS2_STATUS_RESPONSE_BERINT_MASK        );
    api->rsp->dvbs2_status.uncorint      = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBS2_STATUS_RESPONSE_UNCORINT_LSB       , Si2183_DVBS2_STATUS_RESPONSE_UNCORINT_MASK      );
    api->rsp->dvbs2_status.pcl           = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBS2_STATUS_RESPONSE_PCL_LSB            , Si2183_DVBS2_STATUS_RESPONSE_PCL_MASK           );
    api->rsp->dvbs2_status.dl            = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBS2_STATUS_RESPONSE_DL_LSB             , Si2183_DVBS2_STATUS_RESPONSE_DL_MASK            );
    api->rsp->dvbs2_status.ber           = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBS2_STATUS_RESPONSE_BER_LSB            , Si2183_DVBS2_STATUS_RESPONSE_BER_MASK           );
    api->rsp->dvbs2_status.uncor         = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBS2_STATUS_RESPONSE_UNCOR_LSB          , Si2183_DVBS2_STATUS_RESPONSE_UNCOR_MASK         );
    api->rsp->dvbs2_status.cnr           = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_DVBS2_STATUS_RESPONSE_CNR_LSB            , Si2183_DVBS2_STATUS_RESPONSE_CNR_MASK           );
    api->rsp->dvbs2_status.afc_freq      = Si2183_convert_to_int   (&rspByteBuffer[ 4] , Si2183_DVBS2_STATUS_RESPONSE_AFC_FREQ_LSB       , Si2183_DVBS2_STATUS_RESPONSE_AFC_FREQ_MASK      );
    api->rsp->dvbs2_status.timing_offset = Si2183_convert_to_int   (&rspByteBuffer[ 6] , Si2183_DVBS2_STATUS_RESPONSE_TIMING_OFFSET_LSB  , Si2183_DVBS2_STATUS_RESPONSE_TIMING_OFFSET_MASK );
    api->rsp->dvbs2_status.constellation = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_DVBS2_STATUS_RESPONSE_CONSTELLATION_LSB  , Si2183_DVBS2_STATUS_RESPONSE_CONSTELLATION_MASK );
    api->rsp->dvbs2_status.sp_inv        = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_DVBS2_STATUS_RESPONSE_SP_INV_LSB         , Si2183_DVBS2_STATUS_RESPONSE_SP_INV_MASK        );
    api->rsp->dvbs2_status.pilots        = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_DVBS2_STATUS_RESPONSE_PILOTS_LSB         , Si2183_DVBS2_STATUS_RESPONSE_PILOTS_MASK        );
    api->rsp->dvbs2_status.code_rate     = Si2183_convert_to_byte  (&rspByteBuffer[ 9] , Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_LSB      , Si2183_DVBS2_STATUS_RESPONSE_CODE_RATE_MASK     );
    api->rsp->dvbs2_status.roll_off      = Si2183_convert_to_byte  (&rspByteBuffer[10] , Si2183_DVBS2_STATUS_RESPONSE_ROLL_OFF_LSB       , Si2183_DVBS2_STATUS_RESPONSE_ROLL_OFF_MASK      );
    api->rsp->dvbs2_status.ccm_vcm       = Si2183_convert_to_byte  (&rspByteBuffer[10] , Si2183_DVBS2_STATUS_RESPONSE_CCM_VCM_LSB        , Si2183_DVBS2_STATUS_RESPONSE_CCM_VCM_MASK       );
    api->rsp->dvbs2_status.sis_mis       = Si2183_convert_to_byte  (&rspByteBuffer[10] , Si2183_DVBS2_STATUS_RESPONSE_SIS_MIS_LSB        , Si2183_DVBS2_STATUS_RESPONSE_SIS_MIS_MASK       );
    api->rsp->dvbs2_status.stream_type   = Si2183_convert_to_byte  (&rspByteBuffer[10] , Si2183_DVBS2_STATUS_RESPONSE_STREAM_TYPE_LSB    , Si2183_DVBS2_STATUS_RESPONSE_STREAM_TYPE_MASK   );
    api->rsp->dvbs2_status.num_is        = Si2183_convert_to_byte  (&rspByteBuffer[11] , Si2183_DVBS2_STATUS_RESPONSE_NUM_IS_LSB         , Si2183_DVBS2_STATUS_RESPONSE_NUM_IS_MASK        );
    api->rsp->dvbs2_status.isi_id        = Si2183_convert_to_byte  (&rspByteBuffer[12] , Si2183_DVBS2_STATUS_RESPONSE_ISI_ID_LSB         , Si2183_DVBS2_STATUS_RESPONSE_ISI_ID_MASK        );

#ifdef    Si2167B_20_COMPATIBLE
 /* FREQ OFFSET workaround only for Si2167B */
    if (  (api->rsp->part_info.part     == 67 ) & (api->rsp->part_info.romid    ==  0 ) ) {
    SiTRACE("API      dvbs2_status.afc_freq : %d \n", api->rsp->dvbs2_status.afc_freq);

    /* read adc_mode register */
    adc_mode               = Si2183_L1_GET_REG (api,  1,  40,  1);
    SiTRACE("adc_mode               : %u \n ", adc_mode);
    /* read spectral_inv_status_s2 register */
    spectral_inv_status_s2 = Si2183_L1_GET_REG (api, 33,  87,  5);
    SiTRACE("spectral_inv_status_s2 : %u \n", spectral_inv_status_s2);
    /* read freq_corr_sat register */
    freq_corr_sat          = Si2183_L1_GET_REG (api, 27, 144,  5);
    SiTRACE("freq_corr_sat          : %d \n", freq_corr_sat);
    /* read if_freq_shift register */
    if_freq_shift          = Si2183_L1_GET_REG (api, 28,  92,  4);
    SiTRACE("if_freq_shift          : %d \n", if_freq_shift);
    /* read fe_clk_freq register */
    fe_clk_freq            = Si2183_L1_GET_REG (api, 31, 108, 10);
    SiTRACE("fe_clk_freq            : %d \n", fe_clk_freq);
    if (fe_clk_freq == 0) {SiERROR("Problem reading fe_clk_freq (returning 0)\n"); return ERROR_Si2183_ERR;}

    freq_offset_tmp1 = ( 2*freq_corr_sat+if_freq_shift)/((1<<29)/(fe_clk_freq/1000));
    freq_offset_tmp2 = (-2*freq_corr_sat+if_freq_shift)/((1<<29)/(fe_clk_freq/1000));

    if (adc_mode==1) {
      if (spectral_inv_status_s2==1) {freq_offset = -freq_offset_tmp2;} else {freq_offset = -freq_offset_tmp1;}
    } else {
      if (spectral_inv_status_s2==1) {freq_offset =  freq_offset_tmp2;} else {freq_offset =  freq_offset_tmp1;}
    }
    SiTRACE(" freq_offset1 = %d \n",freq_offset_tmp1);
    SiTRACE(" freq_offset2 = %d \n",freq_offset_tmp2);
    SiTRACE(" freq_offset  = %d \n",freq_offset);

    api->rsp->dvbs2_status.afc_freq = freq_offset;
    SiTRACE("COMPUTED dvbs2_status.afc_freq : %d \n", api->rsp->dvbs2_status.afc_freq);
 /* end FREQ OFFSET workaround */
    }
#endif /* Si2167B_20_COMPATIBLE */

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DVBS2_STATUS_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DVBS2_STATUS_CMD */
#ifdef    Si2183_DVBS2_STREAM_INFO_CMD
/*---------------------------------------------------*/
/* Si2183_DVBS2_STREAM_INFO COMMAND                         */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DVBS2_STREAM_INFO         (L1_Si2183_Context *api,
                                                   unsigned char   isi_index)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[4];
    api->rsp->dvbs2_stream_info.STATUS = api->status;

    SiTRACE("Si2183 DVBS2_STREAM_INFO ");
  #ifdef   DEBUG_RANGE_CHECK
    SiTRACE("ISI_INDEX %d ", isi_index );
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DVBS2_STREAM_INFO_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( isi_index & Si2183_DVBS2_STREAM_INFO_CMD_ISI_INDEX_MASK ) << Si2183_DVBS2_STREAM_INFO_CMD_ISI_INDEX_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing DVBS2_STREAM_INFO bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 4, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DVBS2_STREAM_INFO response\n");
      return error_code;
    }

    api->rsp->dvbs2_stream_info.isi_id            = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_ID_LSB             , Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_ID_MASK            );
    api->rsp->dvbs2_stream_info.isi_constellation = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CONSTELLATION_LSB  , Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CONSTELLATION_MASK );
    api->rsp->dvbs2_stream_info.isi_code_rate     = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_LSB      , Si2183_DVBS2_STREAM_INFO_RESPONSE_ISI_CODE_RATE_MASK     );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DVBS2_STREAM_INFO_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DVBS2_STREAM_INFO_CMD */
#ifdef    Si2183_DVBS2_STREAM_SELECT_CMD
/*---------------------------------------------------*/
/* Si2183_DVBS2_STREAM_SELECT COMMAND                     */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DVBS2_STREAM_SELECT       (L1_Si2183_Context *api,
                                                   unsigned char   stream_id,
                                                   unsigned char   stream_sel_mode)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[3];
    unsigned char rspByteBuffer[1];
    api->rsp->dvbs2_stream_select.STATUS = api->status;

    SiTRACE("Si2183 DVBS2_STREAM_SELECT ");
  #ifdef   DEBUG_RANGE_CHECK
    SiTRACE("STREAM_ID %d "      , stream_id       );
    if ((stream_sel_mode > Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_SEL_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("STREAM_SEL_MODE %d ", stream_sel_mode );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DVBS2_STREAM_SELECT_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( stream_id       & Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_ID_MASK       ) << Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_ID_LSB      );
    cmdByteBuffer[2] = (unsigned char) ( ( stream_sel_mode & Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_SEL_MODE_MASK ) << Si2183_DVBS2_STREAM_SELECT_CMD_STREAM_SEL_MODE_LSB);

    if (L0_WriteCommandBytes(api->i2c, 3, cmdByteBuffer) != 3) {
      SiTRACE("Error writing DVBS2_STREAM_SELECT bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DVBS2_STREAM_SELECT response\n");
      return error_code;
    }


    return NO_Si2183_ERROR;
}
#endif /* Si2183_DVBS2_STREAM_SELECT_CMD */
#ifdef    Si2183_DVBS_STATUS_CMD
/*---------------------------------------------------*/
/* Si2183_DVBS_STATUS COMMAND                                     */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DVBS_STATUS               (L1_Si2183_Context *api,
                                                   unsigned char   intack)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[10];
#ifdef    Si2167B_20_COMPATIBLE
  /* FREQ OFFSET workaround variables  (only for Si2167B/Si2166B compatibility) */
    unsigned int adc_mode;
  /* end FREQ OFFSET workaround variables */
#endif /* Si2167B_20_COMPATIBLE */
    api->rsp->dvbs_status.STATUS = api->status;

    SiTRACE("Si2183 DVBS_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((intack > Si2183_DVBS_STATUS_CMD_INTACK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("INTACK %d ", intack );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DVBS_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si2183_DVBS_STATUS_CMD_INTACK_MASK ) << Si2183_DVBS_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing DVBS_STATUS bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 10, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DVBS_STATUS response\n");
      return error_code;
    }

    api->rsp->dvbs_status.pclint        = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBS_STATUS_RESPONSE_PCLINT_LSB         , Si2183_DVBS_STATUS_RESPONSE_PCLINT_MASK        );
    api->rsp->dvbs_status.dlint         = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBS_STATUS_RESPONSE_DLINT_LSB          , Si2183_DVBS_STATUS_RESPONSE_DLINT_MASK         );
    api->rsp->dvbs_status.berint        = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBS_STATUS_RESPONSE_BERINT_LSB         , Si2183_DVBS_STATUS_RESPONSE_BERINT_MASK        );
    api->rsp->dvbs_status.uncorint      = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBS_STATUS_RESPONSE_UNCORINT_LSB       , Si2183_DVBS_STATUS_RESPONSE_UNCORINT_MASK      );
    api->rsp->dvbs_status.pcl           = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBS_STATUS_RESPONSE_PCL_LSB            , Si2183_DVBS_STATUS_RESPONSE_PCL_MASK           );
    api->rsp->dvbs_status.dl            = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBS_STATUS_RESPONSE_DL_LSB             , Si2183_DVBS_STATUS_RESPONSE_DL_MASK            );
    api->rsp->dvbs_status.ber           = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBS_STATUS_RESPONSE_BER_LSB            , Si2183_DVBS_STATUS_RESPONSE_BER_MASK           );
    api->rsp->dvbs_status.uncor         = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBS_STATUS_RESPONSE_UNCOR_LSB          , Si2183_DVBS_STATUS_RESPONSE_UNCOR_MASK         );
    api->rsp->dvbs_status.cnr           = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_DVBS_STATUS_RESPONSE_CNR_LSB            , Si2183_DVBS_STATUS_RESPONSE_CNR_MASK           );
    api->rsp->dvbs_status.afc_freq      = Si2183_convert_to_int   (&rspByteBuffer[ 4] , Si2183_DVBS_STATUS_RESPONSE_AFC_FREQ_LSB       , Si2183_DVBS_STATUS_RESPONSE_AFC_FREQ_MASK      );
    api->rsp->dvbs_status.timing_offset = Si2183_convert_to_int   (&rspByteBuffer[ 6] , Si2183_DVBS_STATUS_RESPONSE_TIMING_OFFSET_LSB  , Si2183_DVBS_STATUS_RESPONSE_TIMING_OFFSET_MASK );
    api->rsp->dvbs_status.constellation = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_DVBS_STATUS_RESPONSE_CONSTELLATION_LSB  , Si2183_DVBS_STATUS_RESPONSE_CONSTELLATION_MASK );
    api->rsp->dvbs_status.sp_inv        = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_DVBS_STATUS_RESPONSE_SP_INV_LSB         , Si2183_DVBS_STATUS_RESPONSE_SP_INV_MASK        );
    api->rsp->dvbs_status.code_rate     = Si2183_convert_to_byte  (&rspByteBuffer[ 9] , Si2183_DVBS_STATUS_RESPONSE_CODE_RATE_LSB      , Si2183_DVBS_STATUS_RESPONSE_CODE_RATE_MASK     );

#ifdef    Si2167B_20_COMPATIBLE
	/* FREQ OFFSET workaround */
    if (  (api->rsp->part_info.part     == 67 ) & (api->rsp->part_info.romid    ==  0 ) ) {
	  SiTRACE("API      dvbs_status.afc_freq : %d \n", api->rsp->dvbs_status.afc_freq);

	  /* read adc_mode register */
      adc_mode               = Si2183_L1_GET_REG (api,  1,  40,  1);
      SiTRACE("adc_mode               : %u \n ", adc_mode);
	  if (adc_mode==0){
	    api->rsp->dvbs_status.afc_freq = -(api->rsp->dvbs_status.afc_freq);
	  }
	}
#endif /* Si2167B_20_COMPATIBLE */

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DVBS_STATUS_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DVBS_STATUS_CMD */
#endif /* DEMOD_DVB_S_S2_DSS */

#ifdef    DEMOD_DVB_T2
#ifdef    Si2183_DVBT2_FEF_CMD
/*---------------------------------------------------*/
/* Si2183_DVBT2_FEF COMMAND                                         */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DVBT2_FEF                 (L1_Si2183_Context *api,
                                                   unsigned char   fef_tuner_flag,
                                                   unsigned char   fef_tuner_flag_inv)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[12];
    api->rsp->dvbt2_fef.STATUS = api->status;

    SiTRACE("Si2183 DVBT2_FEF ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((fef_tuner_flag     > Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MAX    ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FEF_TUNER_FLAG %d "    , fef_tuner_flag     );
    if ((fef_tuner_flag_inv > Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_INV_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FEF_TUNER_FLAG_INV %d ", fef_tuner_flag_inv );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DVBT2_FEF_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( fef_tuner_flag     & Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_MASK     ) << Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_LSB    |
                                         ( fef_tuner_flag_inv & Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_INV_MASK ) << Si2183_DVBT2_FEF_CMD_FEF_TUNER_FLAG_INV_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing DVBT2_FEF bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 12, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DVBT2_FEF response\n");
      return error_code;
    }

    api->rsp->dvbt2_fef.fef_type       = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBT2_FEF_RESPONSE_FEF_TYPE_LSB        , Si2183_DVBT2_FEF_RESPONSE_FEF_TYPE_MASK       );
    api->rsp->dvbt2_fef.fef_length     = Si2183_convert_to_ulong (&rspByteBuffer[ 4] , Si2183_DVBT2_FEF_RESPONSE_FEF_LENGTH_LSB      , Si2183_DVBT2_FEF_RESPONSE_FEF_LENGTH_MASK     );
    api->rsp->dvbt2_fef.fef_repetition = Si2183_convert_to_ulong (&rspByteBuffer[ 8] , Si2183_DVBT2_FEF_RESPONSE_FEF_REPETITION_LSB  , Si2183_DVBT2_FEF_RESPONSE_FEF_REPETITION_MASK );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DVBT2_FEF_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DVBT2_FEF_CMD */
#ifdef    Si2183_DVBT2_PLP_INFO_CMD
/*---------------------------------------------------*/
/* Si2183_DVBT2_PLP_INFO COMMAND                               */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DVBT2_PLP_INFO            (L1_Si2183_Context *api,
                                                   unsigned char   plp_index)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[13];
    api->rsp->dvbt2_plp_info.STATUS = api->status;

    SiTRACE("Si2183 DVBT2_PLP_INFO ");
  #ifdef   DEBUG_RANGE_CHECK
    SiTRACE("PLP_INDEX %d ", plp_index );
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DVBT2_PLP_INFO_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( plp_index & Si2183_DVBT2_PLP_INFO_CMD_PLP_INDEX_MASK ) << Si2183_DVBT2_PLP_INFO_CMD_PLP_INDEX_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing DVBT2_PLP_INFO bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 13, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DVBT2_PLP_INFO response\n");
      return error_code;
    }

    api->rsp->dvbt2_plp_info.plp_id                 = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_ID_LSB                  , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_ID_MASK                 );
    api->rsp->dvbt2_plp_info.plp_payload_type       = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_PAYLOAD_TYPE_LSB        , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_PAYLOAD_TYPE_MASK       );
    api->rsp->dvbt2_plp_info.plp_type               = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_TYPE_LSB                , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_TYPE_MASK               );
    api->rsp->dvbt2_plp_info.first_frame_idx_msb    = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_DVBT2_PLP_INFO_RESPONSE_FIRST_FRAME_IDX_MSB_LSB     , Si2183_DVBT2_PLP_INFO_RESPONSE_FIRST_FRAME_IDX_MSB_MASK    );
    api->rsp->dvbt2_plp_info.first_rf_idx           = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_DVBT2_PLP_INFO_RESPONSE_FIRST_RF_IDX_LSB            , Si2183_DVBT2_PLP_INFO_RESPONSE_FIRST_RF_IDX_MASK           );
    api->rsp->dvbt2_plp_info.ff_flag                = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_DVBT2_PLP_INFO_RESPONSE_FF_FLAG_LSB                 , Si2183_DVBT2_PLP_INFO_RESPONSE_FF_FLAG_MASK                );
    api->rsp->dvbt2_plp_info.plp_group_id_msb       = Si2183_convert_to_byte  (&rspByteBuffer[ 4] , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_GROUP_ID_MSB_LSB        , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_GROUP_ID_MSB_MASK       );
    api->rsp->dvbt2_plp_info.first_frame_idx_lsb    = Si2183_convert_to_byte  (&rspByteBuffer[ 4] , Si2183_DVBT2_PLP_INFO_RESPONSE_FIRST_FRAME_IDX_LSB_LSB     , Si2183_DVBT2_PLP_INFO_RESPONSE_FIRST_FRAME_IDX_LSB_MASK    );
    api->rsp->dvbt2_plp_info.plp_mod_msb            = Si2183_convert_to_byte  (&rspByteBuffer[ 5] , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MOD_MSB_LSB             , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MOD_MSB_MASK            );
    api->rsp->dvbt2_plp_info.plp_cod                = Si2183_convert_to_byte  (&rspByteBuffer[ 5] , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_COD_LSB                 , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_COD_MASK                );
    api->rsp->dvbt2_plp_info.plp_group_id_lsb       = Si2183_convert_to_byte  (&rspByteBuffer[ 5] , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_GROUP_ID_LSB_LSB        , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_GROUP_ID_LSB_MASK       );
    api->rsp->dvbt2_plp_info.plp_num_blocks_max_msb = Si2183_convert_to_byte  (&rspByteBuffer[ 6] , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_NUM_BLOCKS_MAX_MSB_LSB  , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_NUM_BLOCKS_MAX_MSB_MASK );
    api->rsp->dvbt2_plp_info.plp_fec_type           = Si2183_convert_to_byte  (&rspByteBuffer[ 6] , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_FEC_TYPE_LSB            , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_FEC_TYPE_MASK           );
    api->rsp->dvbt2_plp_info.plp_rot                = Si2183_convert_to_byte  (&rspByteBuffer[ 6] , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_ROT_LSB                 , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_ROT_MASK                );
    api->rsp->dvbt2_plp_info.plp_mod_lsb            = Si2183_convert_to_byte  (&rspByteBuffer[ 6] , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MOD_LSB_LSB             , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MOD_LSB_MASK            );
    api->rsp->dvbt2_plp_info.frame_interval_msb     = Si2183_convert_to_byte  (&rspByteBuffer[ 7] , Si2183_DVBT2_PLP_INFO_RESPONSE_FRAME_INTERVAL_MSB_LSB      , Si2183_DVBT2_PLP_INFO_RESPONSE_FRAME_INTERVAL_MSB_MASK     );
    api->rsp->dvbt2_plp_info.plp_num_blocks_max_lsb = Si2183_convert_to_byte  (&rspByteBuffer[ 7] , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_NUM_BLOCKS_MAX_LSB_LSB  , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_NUM_BLOCKS_MAX_LSB_MASK );
    api->rsp->dvbt2_plp_info.time_il_length_msb     = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_DVBT2_PLP_INFO_RESPONSE_TIME_IL_LENGTH_MSB_LSB      , Si2183_DVBT2_PLP_INFO_RESPONSE_TIME_IL_LENGTH_MSB_MASK     );
    api->rsp->dvbt2_plp_info.frame_interval_lsb     = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_DVBT2_PLP_INFO_RESPONSE_FRAME_INTERVAL_LSB_LSB      , Si2183_DVBT2_PLP_INFO_RESPONSE_FRAME_INTERVAL_LSB_MASK     );
    api->rsp->dvbt2_plp_info.time_il_type           = Si2183_convert_to_byte  (&rspByteBuffer[ 9] , Si2183_DVBT2_PLP_INFO_RESPONSE_TIME_IL_TYPE_LSB            , Si2183_DVBT2_PLP_INFO_RESPONSE_TIME_IL_TYPE_MASK           );
    api->rsp->dvbt2_plp_info.time_il_length_lsb     = Si2183_convert_to_byte  (&rspByteBuffer[ 9] , Si2183_DVBT2_PLP_INFO_RESPONSE_TIME_IL_LENGTH_LSB_LSB      , Si2183_DVBT2_PLP_INFO_RESPONSE_TIME_IL_LENGTH_LSB_MASK     );
    api->rsp->dvbt2_plp_info.reserved_1_1           = Si2183_convert_to_byte  (&rspByteBuffer[10] , Si2183_DVBT2_PLP_INFO_RESPONSE_RESERVED_1_1_LSB            , Si2183_DVBT2_PLP_INFO_RESPONSE_RESERVED_1_1_MASK           );
    api->rsp->dvbt2_plp_info.in_band_b_flag         = Si2183_convert_to_byte  (&rspByteBuffer[10] , Si2183_DVBT2_PLP_INFO_RESPONSE_IN_BAND_B_FLAG_LSB          , Si2183_DVBT2_PLP_INFO_RESPONSE_IN_BAND_B_FLAG_MASK         );
    api->rsp->dvbt2_plp_info.in_band_a_flag         = Si2183_convert_to_byte  (&rspByteBuffer[10] , Si2183_DVBT2_PLP_INFO_RESPONSE_IN_BAND_A_FLAG_LSB          , Si2183_DVBT2_PLP_INFO_RESPONSE_IN_BAND_A_FLAG_MASK         );
    api->rsp->dvbt2_plp_info.static_flag            = Si2183_convert_to_byte  (&rspByteBuffer[11] , Si2183_DVBT2_PLP_INFO_RESPONSE_STATIC_FLAG_LSB             , Si2183_DVBT2_PLP_INFO_RESPONSE_STATIC_FLAG_MASK            );
    api->rsp->dvbt2_plp_info.plp_mode               = Si2183_convert_to_byte  (&rspByteBuffer[11] , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MODE_LSB                , Si2183_DVBT2_PLP_INFO_RESPONSE_PLP_MODE_MASK               );
    api->rsp->dvbt2_plp_info.reserved_1_2           = Si2183_convert_to_byte  (&rspByteBuffer[11] , Si2183_DVBT2_PLP_INFO_RESPONSE_RESERVED_1_2_LSB            , Si2183_DVBT2_PLP_INFO_RESPONSE_RESERVED_1_2_MASK           );
    api->rsp->dvbt2_plp_info.static_padding_flag    = Si2183_convert_to_byte  (&rspByteBuffer[12] , Si2183_DVBT2_PLP_INFO_RESPONSE_STATIC_PADDING_FLAG_LSB     , Si2183_DVBT2_PLP_INFO_RESPONSE_STATIC_PADDING_FLAG_MASK    );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DVBT2_PLP_INFO_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DVBT2_PLP_INFO_CMD */
#ifdef    Si2183_DVBT2_PLP_SELECT_CMD
/*---------------------------------------------------*/
/* Si2183_DVBT2_PLP_SELECT COMMAND                           */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DVBT2_PLP_SELECT          (L1_Si2183_Context *api,
                                                   unsigned char   plp_id,
                                                   unsigned char   plp_id_sel_mode)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[3];
    unsigned char rspByteBuffer[1];
    api->rsp->dvbt2_plp_select.STATUS = api->status;

    SiTRACE("Si2183 DVBT2_PLP_SELECT ");
  #ifdef   DEBUG_RANGE_CHECK
    SiTRACE("PLP_ID %d "         , plp_id          );
    if ((plp_id_sel_mode > Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("PLP_ID_SEL_MODE %d ", plp_id_sel_mode );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DVBT2_PLP_SELECT_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( plp_id          & Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_MASK          ) << Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_LSB         );
    cmdByteBuffer[2] = (unsigned char) ( ( plp_id_sel_mode & Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MASK ) << Si2183_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_LSB);

    if (L0_WriteCommandBytes(api->i2c, 3, cmdByteBuffer) != 3) {
      SiTRACE("Error writing DVBT2_PLP_SELECT bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DVBT2_PLP_SELECT response\n");
      return error_code;
    }


    return NO_Si2183_ERROR;
}
#endif /* Si2183_DVBT2_PLP_SELECT_CMD */
#ifdef    Si2183_DVBT2_STATUS_CMD
/*---------------------------------------------------*/
/* Si2183_DVBT2_STATUS COMMAND                                   */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DVBT2_STATUS              (L1_Si2183_Context *api,
                                                   unsigned char   intack)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[15];
    api->rsp->dvbt2_status.STATUS = api->status;

    SiTRACE("Si2183 DVBT2_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((intack > Si2183_DVBT2_STATUS_CMD_INTACK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("INTACK %d ", intack );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DVBT2_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si2183_DVBT2_STATUS_CMD_INTACK_MASK ) << Si2183_DVBT2_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing DVBT2_STATUS bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 15, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DVBT2_STATUS response\n");
      return error_code;
    }

    api->rsp->dvbt2_status.pclint        = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBT2_STATUS_RESPONSE_PCLINT_LSB         , Si2183_DVBT2_STATUS_RESPONSE_PCLINT_MASK        );
    api->rsp->dvbt2_status.dlint         = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBT2_STATUS_RESPONSE_DLINT_LSB          , Si2183_DVBT2_STATUS_RESPONSE_DLINT_MASK         );
    api->rsp->dvbt2_status.berint        = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBT2_STATUS_RESPONSE_BERINT_LSB         , Si2183_DVBT2_STATUS_RESPONSE_BERINT_MASK        );
    api->rsp->dvbt2_status.uncorint      = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBT2_STATUS_RESPONSE_UNCORINT_LSB       , Si2183_DVBT2_STATUS_RESPONSE_UNCORINT_MASK      );
    api->rsp->dvbt2_status.notdvbt2int   = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBT2_STATUS_RESPONSE_NOTDVBT2INT_LSB    , Si2183_DVBT2_STATUS_RESPONSE_NOTDVBT2INT_MASK   );
    api->rsp->dvbt2_status.pcl           = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBT2_STATUS_RESPONSE_PCL_LSB            , Si2183_DVBT2_STATUS_RESPONSE_PCL_MASK           );
    api->rsp->dvbt2_status.dl            = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBT2_STATUS_RESPONSE_DL_LSB             , Si2183_DVBT2_STATUS_RESPONSE_DL_MASK            );
    api->rsp->dvbt2_status.ber           = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBT2_STATUS_RESPONSE_BER_LSB            , Si2183_DVBT2_STATUS_RESPONSE_BER_MASK           );
    api->rsp->dvbt2_status.uncor         = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBT2_STATUS_RESPONSE_UNCOR_LSB          , Si2183_DVBT2_STATUS_RESPONSE_UNCOR_MASK         );
    api->rsp->dvbt2_status.notdvbt2      = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBT2_STATUS_RESPONSE_NOTDVBT2_LSB       , Si2183_DVBT2_STATUS_RESPONSE_NOTDVBT2_MASK      );
    api->rsp->dvbt2_status.cnr           = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_DVBT2_STATUS_RESPONSE_CNR_LSB            , Si2183_DVBT2_STATUS_RESPONSE_CNR_MASK           );
    api->rsp->dvbt2_status.afc_freq      = Si2183_convert_to_int   (&rspByteBuffer[ 4] , Si2183_DVBT2_STATUS_RESPONSE_AFC_FREQ_LSB       , Si2183_DVBT2_STATUS_RESPONSE_AFC_FREQ_MASK      );
    api->rsp->dvbt2_status.timing_offset = Si2183_convert_to_int   (&rspByteBuffer[ 6] , Si2183_DVBT2_STATUS_RESPONSE_TIMING_OFFSET_LSB  , Si2183_DVBT2_STATUS_RESPONSE_TIMING_OFFSET_MASK );
    api->rsp->dvbt2_status.constellation = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_DVBT2_STATUS_RESPONSE_CONSTELLATION_LSB  , Si2183_DVBT2_STATUS_RESPONSE_CONSTELLATION_MASK );
    api->rsp->dvbt2_status.sp_inv        = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_DVBT2_STATUS_RESPONSE_SP_INV_LSB         , Si2183_DVBT2_STATUS_RESPONSE_SP_INV_MASK        );
    api->rsp->dvbt2_status.fef           = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_DVBT2_STATUS_RESPONSE_FEF_LSB            , Si2183_DVBT2_STATUS_RESPONSE_FEF_MASK           );
    api->rsp->dvbt2_status.fft_mode      = Si2183_convert_to_byte  (&rspByteBuffer[ 9] , Si2183_DVBT2_STATUS_RESPONSE_FFT_MODE_LSB       , Si2183_DVBT2_STATUS_RESPONSE_FFT_MODE_MASK      );
    api->rsp->dvbt2_status.guard_int     = Si2183_convert_to_byte  (&rspByteBuffer[ 9] , Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_LSB      , Si2183_DVBT2_STATUS_RESPONSE_GUARD_INT_MASK     );
    api->rsp->dvbt2_status.bw_ext        = Si2183_convert_to_byte  (&rspByteBuffer[ 9] , Si2183_DVBT2_STATUS_RESPONSE_BW_EXT_LSB         , Si2183_DVBT2_STATUS_RESPONSE_BW_EXT_MASK        );
    api->rsp->dvbt2_status.num_plp       = Si2183_convert_to_byte  (&rspByteBuffer[10] , Si2183_DVBT2_STATUS_RESPONSE_NUM_PLP_LSB        , Si2183_DVBT2_STATUS_RESPONSE_NUM_PLP_MASK       );
    api->rsp->dvbt2_status.pilot_pattern = Si2183_convert_to_byte  (&rspByteBuffer[11] , Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_LSB  , Si2183_DVBT2_STATUS_RESPONSE_PILOT_PATTERN_MASK );
    api->rsp->dvbt2_status.tx_mode       = Si2183_convert_to_byte  (&rspByteBuffer[11] , Si2183_DVBT2_STATUS_RESPONSE_TX_MODE_LSB        , Si2183_DVBT2_STATUS_RESPONSE_TX_MODE_MASK       );
    api->rsp->dvbt2_status.rotated       = Si2183_convert_to_byte  (&rspByteBuffer[11] , Si2183_DVBT2_STATUS_RESPONSE_ROTATED_LSB        , Si2183_DVBT2_STATUS_RESPONSE_ROTATED_MASK       );
    api->rsp->dvbt2_status.short_frame   = Si2183_convert_to_byte  (&rspByteBuffer[11] , Si2183_DVBT2_STATUS_RESPONSE_SHORT_FRAME_LSB    , Si2183_DVBT2_STATUS_RESPONSE_SHORT_FRAME_MASK   );
    api->rsp->dvbt2_status.t2_mode       = Si2183_convert_to_byte  (&rspByteBuffer[11] , Si2183_DVBT2_STATUS_RESPONSE_T2_MODE_LSB        , Si2183_DVBT2_STATUS_RESPONSE_T2_MODE_MASK       );
    api->rsp->dvbt2_status.code_rate     = Si2183_convert_to_byte  (&rspByteBuffer[12] , Si2183_DVBT2_STATUS_RESPONSE_CODE_RATE_LSB      , Si2183_DVBT2_STATUS_RESPONSE_CODE_RATE_MASK     );
    api->rsp->dvbt2_status.t2_version    = Si2183_convert_to_byte  (&rspByteBuffer[12] , Si2183_DVBT2_STATUS_RESPONSE_T2_VERSION_LSB     , Si2183_DVBT2_STATUS_RESPONSE_T2_VERSION_MASK    );
    api->rsp->dvbt2_status.plp_id        = Si2183_convert_to_byte  (&rspByteBuffer[13] , Si2183_DVBT2_STATUS_RESPONSE_PLP_ID_LSB         , Si2183_DVBT2_STATUS_RESPONSE_PLP_ID_MASK        );
    api->rsp->dvbt2_status.stream_type   = Si2183_convert_to_byte  (&rspByteBuffer[14] , Si2183_DVBT2_STATUS_RESPONSE_STREAM_TYPE_LSB    , Si2183_DVBT2_STATUS_RESPONSE_STREAM_TYPE_MASK   );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DVBT2_STATUS_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DVBT2_STATUS_CMD */
#ifdef    Si2183_DVBT2_TX_ID_CMD
/*---------------------------------------------------*/
/* Si2183_DVBT2_TX_ID COMMAND                                     */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DVBT2_TX_ID               (L1_Si2183_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[8];
    api->rsp->dvbt2_tx_id.STATUS = api->status;

    SiTRACE("Si2183 DVBT2_TX_ID ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DVBT2_TX_ID_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing DVBT2_TX_ID bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 8, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DVBT2_TX_ID response\n");
      return error_code;
    }

    api->rsp->dvbt2_tx_id.tx_id_availability = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBT2_TX_ID_RESPONSE_TX_ID_AVAILABILITY_LSB  , Si2183_DVBT2_TX_ID_RESPONSE_TX_ID_AVAILABILITY_MASK );
    api->rsp->dvbt2_tx_id.cell_id            = Si2183_convert_to_uint  (&rspByteBuffer[ 2] , Si2183_DVBT2_TX_ID_RESPONSE_CELL_ID_LSB             , Si2183_DVBT2_TX_ID_RESPONSE_CELL_ID_MASK            );
    api->rsp->dvbt2_tx_id.network_id         = Si2183_convert_to_uint  (&rspByteBuffer[ 4] , Si2183_DVBT2_TX_ID_RESPONSE_NETWORK_ID_LSB          , Si2183_DVBT2_TX_ID_RESPONSE_NETWORK_ID_MASK         );
    api->rsp->dvbt2_tx_id.t2_system_id       = Si2183_convert_to_uint  (&rspByteBuffer[ 6] , Si2183_DVBT2_TX_ID_RESPONSE_T2_SYSTEM_ID_LSB        , Si2183_DVBT2_TX_ID_RESPONSE_T2_SYSTEM_ID_MASK       );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DVBT2_TX_ID_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DVBT2_TX_ID_CMD */
#endif /* DEMOD_DVB_T2 */

#ifdef    DEMOD_DVB_T
#ifdef    Si2183_DVBT_STATUS_CMD
/*---------------------------------------------------*/
/* Si2183_DVBT_STATUS COMMAND                                     */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DVBT_STATUS               (L1_Si2183_Context *api,
                                                   unsigned char   intack)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[13];
    api->rsp->dvbt_status.STATUS = api->status;

    SiTRACE("Si2183 DVBT_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((intack > Si2183_DVBT_STATUS_CMD_INTACK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("INTACK %d ", intack );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DVBT_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si2183_DVBT_STATUS_CMD_INTACK_MASK ) << Si2183_DVBT_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing DVBT_STATUS bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 13, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DVBT_STATUS response\n");
      return error_code;
    }

    api->rsp->dvbt_status.pclint        = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBT_STATUS_RESPONSE_PCLINT_LSB         , Si2183_DVBT_STATUS_RESPONSE_PCLINT_MASK        );
    api->rsp->dvbt_status.dlint         = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBT_STATUS_RESPONSE_DLINT_LSB          , Si2183_DVBT_STATUS_RESPONSE_DLINT_MASK         );
    api->rsp->dvbt_status.berint        = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBT_STATUS_RESPONSE_BERINT_LSB         , Si2183_DVBT_STATUS_RESPONSE_BERINT_MASK        );
    api->rsp->dvbt_status.uncorint      = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBT_STATUS_RESPONSE_UNCORINT_LSB       , Si2183_DVBT_STATUS_RESPONSE_UNCORINT_MASK      );
    api->rsp->dvbt_status.notdvbtint    = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBT_STATUS_RESPONSE_NOTDVBTINT_LSB     , Si2183_DVBT_STATUS_RESPONSE_NOTDVBTINT_MASK    );
    api->rsp->dvbt_status.pcl           = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBT_STATUS_RESPONSE_PCL_LSB            , Si2183_DVBT_STATUS_RESPONSE_PCL_MASK           );
    api->rsp->dvbt_status.dl            = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBT_STATUS_RESPONSE_DL_LSB             , Si2183_DVBT_STATUS_RESPONSE_DL_MASK            );
    api->rsp->dvbt_status.ber           = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBT_STATUS_RESPONSE_BER_LSB            , Si2183_DVBT_STATUS_RESPONSE_BER_MASK           );
    api->rsp->dvbt_status.uncor         = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBT_STATUS_RESPONSE_UNCOR_LSB          , Si2183_DVBT_STATUS_RESPONSE_UNCOR_MASK         );
    api->rsp->dvbt_status.notdvbt       = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_DVBT_STATUS_RESPONSE_NOTDVBT_LSB        , Si2183_DVBT_STATUS_RESPONSE_NOTDVBT_MASK       );
    api->rsp->dvbt_status.cnr           = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_DVBT_STATUS_RESPONSE_CNR_LSB            , Si2183_DVBT_STATUS_RESPONSE_CNR_MASK           );
    api->rsp->dvbt_status.afc_freq      = Si2183_convert_to_int   (&rspByteBuffer[ 4] , Si2183_DVBT_STATUS_RESPONSE_AFC_FREQ_LSB       , Si2183_DVBT_STATUS_RESPONSE_AFC_FREQ_MASK      );
    api->rsp->dvbt_status.timing_offset = Si2183_convert_to_int   (&rspByteBuffer[ 6] , Si2183_DVBT_STATUS_RESPONSE_TIMING_OFFSET_LSB  , Si2183_DVBT_STATUS_RESPONSE_TIMING_OFFSET_MASK );
    api->rsp->dvbt_status.constellation = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_DVBT_STATUS_RESPONSE_CONSTELLATION_LSB  , Si2183_DVBT_STATUS_RESPONSE_CONSTELLATION_MASK );
    api->rsp->dvbt_status.sp_inv        = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_DVBT_STATUS_RESPONSE_SP_INV_LSB         , Si2183_DVBT_STATUS_RESPONSE_SP_INV_MASK        );
    api->rsp->dvbt_status.rate_hp       = Si2183_convert_to_byte  (&rspByteBuffer[ 9] , Si2183_DVBT_STATUS_RESPONSE_RATE_HP_LSB        , Si2183_DVBT_STATUS_RESPONSE_RATE_HP_MASK       );
    api->rsp->dvbt_status.rate_lp       = Si2183_convert_to_byte  (&rspByteBuffer[ 9] , Si2183_DVBT_STATUS_RESPONSE_RATE_LP_LSB        , Si2183_DVBT_STATUS_RESPONSE_RATE_LP_MASK       );
    api->rsp->dvbt_status.fft_mode      = Si2183_convert_to_byte  (&rspByteBuffer[10] , Si2183_DVBT_STATUS_RESPONSE_FFT_MODE_LSB       , Si2183_DVBT_STATUS_RESPONSE_FFT_MODE_MASK      );
    api->rsp->dvbt_status.guard_int     = Si2183_convert_to_byte  (&rspByteBuffer[10] , Si2183_DVBT_STATUS_RESPONSE_GUARD_INT_LSB      , Si2183_DVBT_STATUS_RESPONSE_GUARD_INT_MASK     );
    api->rsp->dvbt_status.hierarchy     = Si2183_convert_to_byte  (&rspByteBuffer[11] , Si2183_DVBT_STATUS_RESPONSE_HIERARCHY_LSB      , Si2183_DVBT_STATUS_RESPONSE_HIERARCHY_MASK     );
    api->rsp->dvbt_status.tps_length    = Si2183_convert_to_byte  (&rspByteBuffer[12] , Si2183_DVBT_STATUS_RESPONSE_TPS_LENGTH_LSB     , Si2183_DVBT_STATUS_RESPONSE_TPS_LENGTH_MASK    );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DVBT_STATUS_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DVBT_STATUS_CMD */
#ifdef    Si2183_DVBT_TPS_EXTRA_CMD
/*---------------------------------------------------*/
/* Si2183_DVBT_TPS_EXTRA COMMAND                               */
/*---------------------------------------------------*/
unsigned char Si2183_L1_DVBT_TPS_EXTRA            (L1_Si2183_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[6];
    api->rsp->dvbt_tps_extra.STATUS = api->status;

    SiTRACE("Si2183 DVBT_TPS_EXTRA ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_DVBT_TPS_EXTRA_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing DVBT_TPS_EXTRA bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 6, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DVBT_TPS_EXTRA response\n");
      return error_code;
    }

    api->rsp->dvbt_tps_extra.lptimeslice = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBT_TPS_EXTRA_RESPONSE_LPTIMESLICE_LSB  , Si2183_DVBT_TPS_EXTRA_RESPONSE_LPTIMESLICE_MASK );
    api->rsp->dvbt_tps_extra.hptimeslice = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBT_TPS_EXTRA_RESPONSE_HPTIMESLICE_LSB  , Si2183_DVBT_TPS_EXTRA_RESPONSE_HPTIMESLICE_MASK );
    api->rsp->dvbt_tps_extra.lpmpefec    = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBT_TPS_EXTRA_RESPONSE_LPMPEFEC_LSB     , Si2183_DVBT_TPS_EXTRA_RESPONSE_LPMPEFEC_MASK    );
    api->rsp->dvbt_tps_extra.hpmpefec    = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBT_TPS_EXTRA_RESPONSE_HPMPEFEC_LSB     , Si2183_DVBT_TPS_EXTRA_RESPONSE_HPMPEFEC_MASK    );
    api->rsp->dvbt_tps_extra.dvbhinter   = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_DVBT_TPS_EXTRA_RESPONSE_DVBHINTER_LSB    , Si2183_DVBT_TPS_EXTRA_RESPONSE_DVBHINTER_MASK   );
    api->rsp->dvbt_tps_extra.cell_id     = Si2183_convert_to_int   (&rspByteBuffer[ 2] , Si2183_DVBT_TPS_EXTRA_RESPONSE_CELL_ID_LSB      , Si2183_DVBT_TPS_EXTRA_RESPONSE_CELL_ID_MASK     );
    api->rsp->dvbt_tps_extra.tps_res1    = Si2183_convert_to_byte  (&rspByteBuffer[ 4] , Si2183_DVBT_TPS_EXTRA_RESPONSE_TPS_RES1_LSB     , Si2183_DVBT_TPS_EXTRA_RESPONSE_TPS_RES1_MASK    );
    api->rsp->dvbt_tps_extra.tps_res2    = Si2183_convert_to_byte  (&rspByteBuffer[ 4] , Si2183_DVBT_TPS_EXTRA_RESPONSE_TPS_RES2_LSB     , Si2183_DVBT_TPS_EXTRA_RESPONSE_TPS_RES2_MASK    );
    api->rsp->dvbt_tps_extra.tps_res3    = Si2183_convert_to_byte  (&rspByteBuffer[ 5] , Si2183_DVBT_TPS_EXTRA_RESPONSE_TPS_RES3_LSB     , Si2183_DVBT_TPS_EXTRA_RESPONSE_TPS_RES3_MASK    );
    api->rsp->dvbt_tps_extra.tps_res4    = Si2183_convert_to_byte  (&rspByteBuffer[ 5] , Si2183_DVBT_TPS_EXTRA_RESPONSE_TPS_RES4_LSB     , Si2183_DVBT_TPS_EXTRA_RESPONSE_TPS_RES4_MASK    );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_DVBT_TPS_EXTRA_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_DVBT_TPS_EXTRA_CMD */
#endif /* DEMOD_DVB_T */

#ifdef    Si2183_EXIT_BOOTLOADER_CMD
/*---------------------------------------------------*/
/* Si2183_EXIT_BOOTLOADER COMMAND                             */
/*---------------------------------------------------*/
unsigned char Si2183_L1_EXIT_BOOTLOADER           (L1_Si2183_Context *api,
                                                   unsigned char   func,
                                                   unsigned char   ctsien)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];
    api->rsp->exit_bootloader.STATUS = api->status;

    SiTRACE("Si2183 EXIT_BOOTLOADER ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((func   > Si2183_EXIT_BOOTLOADER_CMD_FUNC_MAX  )  || (func   < Si2183_EXIT_BOOTLOADER_CMD_FUNC_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FUNC %d "  , func   );
    if ((ctsien > Si2183_EXIT_BOOTLOADER_CMD_CTSIEN_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CTSIEN %d ", ctsien );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_EXIT_BOOTLOADER_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( func   & Si2183_EXIT_BOOTLOADER_CMD_FUNC_MASK   ) << Si2183_EXIT_BOOTLOADER_CMD_FUNC_LSB  |
                                         ( ctsien & Si2183_EXIT_BOOTLOADER_CMD_CTSIEN_MASK ) << Si2183_EXIT_BOOTLOADER_CMD_CTSIEN_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing EXIT_BOOTLOADER bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling EXIT_BOOTLOADER response\n");
      return error_code;
    }


    return NO_Si2183_ERROR;
}
#endif /* Si2183_EXIT_BOOTLOADER_CMD */
#ifdef    Si2183_GET_PROPERTY_CMD
/*---------------------------------------------------*/
/* Si2183_GET_PROPERTY COMMAND                                   */
/*---------------------------------------------------*/
unsigned char Si2183_L1_GET_PROPERTY              (L1_Si2183_Context *api,
                                                   unsigned char   reserved,
                                                   unsigned int    prop)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[4];
    unsigned char rspByteBuffer[4];
    api->rsp->get_property.STATUS = api->status;

    SiTRACE("Si2183 GET_PROPERTY ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((reserved > Si2183_GET_PROPERTY_CMD_RESERVED_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED %d ", reserved );
    SiTRACE("PROP %d "    , prop     );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_GET_PROPERTY_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( reserved & Si2183_GET_PROPERTY_CMD_RESERVED_MASK ) << Si2183_GET_PROPERTY_CMD_RESERVED_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( prop     & Si2183_GET_PROPERTY_CMD_PROP_MASK     ) << Si2183_GET_PROPERTY_CMD_PROP_LSB    );
    cmdByteBuffer[3] = (unsigned char) ((( prop     & Si2183_GET_PROPERTY_CMD_PROP_MASK     ) << Si2183_GET_PROPERTY_CMD_PROP_LSB    )>>8);

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing GET_PROPERTY bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 4, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling GET_PROPERTY response\n");
      return error_code;
    }

    api->rsp->get_property.reserved = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_GET_PROPERTY_RESPONSE_RESERVED_LSB  , Si2183_GET_PROPERTY_RESPONSE_RESERVED_MASK );
    api->rsp->get_property.data     = Si2183_convert_to_uint  (&rspByteBuffer[ 2] , Si2183_GET_PROPERTY_RESPONSE_DATA_LSB      , Si2183_GET_PROPERTY_RESPONSE_DATA_MASK     );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_GET_PROPERTY_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_GET_PROPERTY_CMD */
#ifdef    Si2183_GET_REV_CMD
/*---------------------------------------------------*/
/* Si2183_GET_REV COMMAND                                             */
/*---------------------------------------------------*/
unsigned char Si2183_L1_GET_REV                   (L1_Si2183_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[13];
    api->rsp->get_rev.STATUS = api->status;

    SiTRACE("Si2183 GET_REV ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_GET_REV_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing GET_REV bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 13, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling GET_REV response\n");
      return error_code;
    }

    api->rsp->get_rev.pn       = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_GET_REV_RESPONSE_PN_LSB        , Si2183_GET_REV_RESPONSE_PN_MASK       );
    api->rsp->get_rev.fwmajor  = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_GET_REV_RESPONSE_FWMAJOR_LSB   , Si2183_GET_REV_RESPONSE_FWMAJOR_MASK  );
    api->rsp->get_rev.fwminor  = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_GET_REV_RESPONSE_FWMINOR_LSB   , Si2183_GET_REV_RESPONSE_FWMINOR_MASK  );
    api->rsp->get_rev.patch    = Si2183_convert_to_uint  (&rspByteBuffer[ 4] , Si2183_GET_REV_RESPONSE_PATCH_LSB     , Si2183_GET_REV_RESPONSE_PATCH_MASK    );
    api->rsp->get_rev.cmpmajor = Si2183_convert_to_byte  (&rspByteBuffer[ 6] , Si2183_GET_REV_RESPONSE_CMPMAJOR_LSB  , Si2183_GET_REV_RESPONSE_CMPMAJOR_MASK );
    api->rsp->get_rev.cmpminor = Si2183_convert_to_byte  (&rspByteBuffer[ 7] , Si2183_GET_REV_RESPONSE_CMPMINOR_LSB  , Si2183_GET_REV_RESPONSE_CMPMINOR_MASK );
    api->rsp->get_rev.cmpbuild = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_GET_REV_RESPONSE_CMPBUILD_LSB  , Si2183_GET_REV_RESPONSE_CMPBUILD_MASK );
    api->rsp->get_rev.chiprev  = Si2183_convert_to_byte  (&rspByteBuffer[ 9] , Si2183_GET_REV_RESPONSE_CHIPREV_LSB   , Si2183_GET_REV_RESPONSE_CHIPREV_MASK  );
    api->rsp->get_rev.mcm_die  = Si2183_convert_to_byte  (&rspByteBuffer[ 9] , Si2183_GET_REV_RESPONSE_MCM_DIE_LSB   , Si2183_GET_REV_RESPONSE_MCM_DIE_MASK  );
    api->rsp->get_rev.rx       = Si2183_convert_to_byte  (&rspByteBuffer[12] , Si2183_GET_REV_RESPONSE_RX_LSB        , Si2183_GET_REV_RESPONSE_RX_MASK       );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_GET_REV_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_GET_REV_CMD */
#ifdef    Si2183_I2C_PASSTHROUGH_CMD
/*---------------------------------------------------*/
/* Si2183_I2C_PASSTHROUGH COMMAND                             */
/*---------------------------------------------------*/
unsigned char Si2183_L1_I2C_PASSTHROUGH           (L1_Si2183_Context *api,
                                                   unsigned char   subcode,
                                                   unsigned char   i2c_passthru,
                                                   unsigned char   reserved)
{
  #ifdef   DEBUG_RANGE_CHECK
    unsigned char error_code = 0;
  #endif /* DEBUG_RANGE_CHECK */
    unsigned char cmdByteBuffer[3];
    api->rsp->i2c_passthrough.STATUS = api->status;

    SiTRACE("Si2183 I2C_PASSTHROUGH ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode      > Si2183_I2C_PASSTHROUGH_CMD_SUBCODE_MAX     )  || (subcode      < Si2183_I2C_PASSTHROUGH_CMD_SUBCODE_MIN     ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "     , subcode      );
    if ((i2c_passthru > Si2183_I2C_PASSTHROUGH_CMD_I2C_PASSTHRU_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("I2C_PASSTHRU %d ", i2c_passthru );
    if ((reserved     > Si2183_I2C_PASSTHROUGH_CMD_RESERVED_MAX    ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED %d "    , reserved     );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_I2C_PASSTHROUGH_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode      & Si2183_I2C_PASSTHROUGH_CMD_SUBCODE_MASK      ) << Si2183_I2C_PASSTHROUGH_CMD_SUBCODE_LSB     );
    cmdByteBuffer[2] = (unsigned char) ( ( i2c_passthru & Si2183_I2C_PASSTHROUGH_CMD_I2C_PASSTHRU_MASK ) << Si2183_I2C_PASSTHROUGH_CMD_I2C_PASSTHRU_LSB|
                                         ( reserved     & Si2183_I2C_PASSTHROUGH_CMD_RESERVED_MASK     ) << Si2183_I2C_PASSTHROUGH_CMD_RESERVED_LSB    );

    if (L0_WriteCommandBytes(api->i2c, 3, cmdByteBuffer) != 3) {
      SiTRACE("Error writing I2C_PASSTHROUGH bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    return NO_Si2183_ERROR;
}
#endif /* Si2183_I2C_PASSTHROUGH_CMD */
#ifdef    DEMOD_ISDB_T
#ifdef    Si2183_ISDBT_AC_BITS_CMD
/*---------------------------------------------------*/
/* Si2183_ISDBT_AC_BITS COMMAND                                 */
/*---------------------------------------------------*/
unsigned char Si2183_L1_ISDBT_AC_BITS             (L1_Si2183_Context *api,
                                                   unsigned char   byte_read_offset,
                                                   unsigned char   freeze_buffer,
                                                   unsigned char  *AC_bytes)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[3];
    unsigned char rspByteBuffer[16];
    api->rsp->isdbt_ac_bits.STATUS = api->status;

    SiTRACE("Si2183 ISDBT_AC_BITS ");
  #ifdef   DEBUG_RANGE_CHECK
    SiTRACE("BYTE_READ_OFFSET %d ", byte_read_offset );
    if ((freeze_buffer    > Si2183_ISDBT_AC_BITS_CMD_FREEZE_BUFFER_MAX   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FREEZE_BUFFER %d "   , freeze_buffer    );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_ISDBT_AC_BITS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( byte_read_offset & Si2183_ISDBT_AC_BITS_CMD_BYTE_READ_OFFSET_MASK ) << Si2183_ISDBT_AC_BITS_CMD_BYTE_READ_OFFSET_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( freeze_buffer    & Si2183_ISDBT_AC_BITS_CMD_FREEZE_BUFFER_MASK    ) << Si2183_ISDBT_AC_BITS_CMD_FREEZE_BUFFER_LSB   );

    if (L0_WriteCommandBytes(api->i2c, 3, cmdByteBuffer) != 3) {
      SiTRACE("Error writing ISDBT_AC_BITS bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 16, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling ISDBT_AC_BITS response\n");
      return error_code;
    }

    AC_bytes[ 0] = api->rsp->isdbt_ac_bits.data1  = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_ISDBT_AC_BITS_RESPONSE_DATA1_LSB   , Si2183_ISDBT_AC_BITS_RESPONSE_DATA1_MASK  );
    AC_bytes[ 1] = api->rsp->isdbt_ac_bits.data2  = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_ISDBT_AC_BITS_RESPONSE_DATA2_LSB   , Si2183_ISDBT_AC_BITS_RESPONSE_DATA2_MASK  );
    AC_bytes[ 2] = api->rsp->isdbt_ac_bits.data3  = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_ISDBT_AC_BITS_RESPONSE_DATA3_LSB   , Si2183_ISDBT_AC_BITS_RESPONSE_DATA3_MASK  );
    AC_bytes[ 3] = api->rsp->isdbt_ac_bits.data4  = Si2183_convert_to_byte  (&rspByteBuffer[ 4] , Si2183_ISDBT_AC_BITS_RESPONSE_DATA4_LSB   , Si2183_ISDBT_AC_BITS_RESPONSE_DATA4_MASK  );
    AC_bytes[ 4] = api->rsp->isdbt_ac_bits.data5  = Si2183_convert_to_byte  (&rspByteBuffer[ 5] , Si2183_ISDBT_AC_BITS_RESPONSE_DATA5_LSB   , Si2183_ISDBT_AC_BITS_RESPONSE_DATA5_MASK  );
    AC_bytes[ 5] = api->rsp->isdbt_ac_bits.data6  = Si2183_convert_to_byte  (&rspByteBuffer[ 6] , Si2183_ISDBT_AC_BITS_RESPONSE_DATA6_LSB   , Si2183_ISDBT_AC_BITS_RESPONSE_DATA6_MASK  );
    AC_bytes[ 6] = api->rsp->isdbt_ac_bits.data7  = Si2183_convert_to_byte  (&rspByteBuffer[ 7] , Si2183_ISDBT_AC_BITS_RESPONSE_DATA7_LSB   , Si2183_ISDBT_AC_BITS_RESPONSE_DATA7_MASK  );
    AC_bytes[ 7] = api->rsp->isdbt_ac_bits.data8  = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_ISDBT_AC_BITS_RESPONSE_DATA8_LSB   , Si2183_ISDBT_AC_BITS_RESPONSE_DATA8_MASK  );
    AC_bytes[ 8] = api->rsp->isdbt_ac_bits.data9  = Si2183_convert_to_byte  (&rspByteBuffer[ 9] , Si2183_ISDBT_AC_BITS_RESPONSE_DATA9_LSB   , Si2183_ISDBT_AC_BITS_RESPONSE_DATA9_MASK  );
    AC_bytes[ 9] = api->rsp->isdbt_ac_bits.data10 = Si2183_convert_to_byte  (&rspByteBuffer[10] , Si2183_ISDBT_AC_BITS_RESPONSE_DATA10_LSB  , Si2183_ISDBT_AC_BITS_RESPONSE_DATA10_MASK );
    AC_bytes[10] = api->rsp->isdbt_ac_bits.data11 = Si2183_convert_to_byte  (&rspByteBuffer[11] , Si2183_ISDBT_AC_BITS_RESPONSE_DATA11_LSB  , Si2183_ISDBT_AC_BITS_RESPONSE_DATA11_MASK );
    AC_bytes[11] = api->rsp->isdbt_ac_bits.data12 = Si2183_convert_to_byte  (&rspByteBuffer[12] , Si2183_ISDBT_AC_BITS_RESPONSE_DATA12_LSB  , Si2183_ISDBT_AC_BITS_RESPONSE_DATA12_MASK );
    AC_bytes[12] = api->rsp->isdbt_ac_bits.data13 = Si2183_convert_to_byte  (&rspByteBuffer[13] , Si2183_ISDBT_AC_BITS_RESPONSE_DATA13_LSB  , Si2183_ISDBT_AC_BITS_RESPONSE_DATA13_MASK );
    AC_bytes[13] = api->rsp->isdbt_ac_bits.data14 = Si2183_convert_to_byte  (&rspByteBuffer[14] , Si2183_ISDBT_AC_BITS_RESPONSE_DATA14_LSB  , Si2183_ISDBT_AC_BITS_RESPONSE_DATA14_MASK );
    AC_bytes[14] = api->rsp->isdbt_ac_bits.data15 = Si2183_convert_to_byte  (&rspByteBuffer[15] , Si2183_ISDBT_AC_BITS_RESPONSE_DATA15_LSB  , Si2183_ISDBT_AC_BITS_RESPONSE_DATA15_MASK );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_ISDBT_AC_BITS_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_ISDBT_AC_BITS_CMD */
#ifdef    Si2183_ISDBT_LAYER_INFO_CMD
/*---------------------------------------------------*/
/* Si2183_ISDBT_LAYER_INFO COMMAND                           */
/*---------------------------------------------------*/
unsigned char Si2183_L1_ISDBT_LAYER_INFO          (L1_Si2183_Context *api,
                                                   unsigned char   layer_index)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[3];
    api->rsp->isdbt_layer_info.STATUS = api->status;

    SiTRACE("Si2183 ISDBT_LAYER_INFO ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((layer_index > Si2183_ISDBT_LAYER_INFO_CMD_LAYER_INDEX_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("LAYER_INDEX %d ", layer_index );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_ISDBT_LAYER_INFO_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( layer_index & Si2183_ISDBT_LAYER_INFO_CMD_LAYER_INDEX_MASK ) << Si2183_ISDBT_LAYER_INFO_CMD_LAYER_INDEX_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing ISDBT_LAYER_INFO bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 3, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling ISDBT_LAYER_INFO response\n");
      return error_code;
    }

    api->rsp->isdbt_layer_info.constellation = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_ISDBT_LAYER_INFO_RESPONSE_CONSTELLATION_LSB  , Si2183_ISDBT_LAYER_INFO_RESPONSE_CONSTELLATION_MASK );
    api->rsp->isdbt_layer_info.code_rate     = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_ISDBT_LAYER_INFO_RESPONSE_CODE_RATE_LSB      , Si2183_ISDBT_LAYER_INFO_RESPONSE_CODE_RATE_MASK     );
    api->rsp->isdbt_layer_info.il            = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_ISDBT_LAYER_INFO_RESPONSE_IL_LSB             , Si2183_ISDBT_LAYER_INFO_RESPONSE_IL_MASK            );
    api->rsp->isdbt_layer_info.nb_seg        = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_ISDBT_LAYER_INFO_RESPONSE_NB_SEG_LSB         , Si2183_ISDBT_LAYER_INFO_RESPONSE_NB_SEG_MASK        );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_ISDBT_LAYER_INFO_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_ISDBT_LAYER_INFO_CMD */
#ifdef    Si2183_ISDBT_STATUS_CMD
/*---------------------------------------------------*/
/* Si2183_ISDBT_STATUS COMMAND                                   */
/*---------------------------------------------------*/
unsigned char Si2183_L1_ISDBT_STATUS              (L1_Si2183_Context *api,
                                                   unsigned char   intack)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[14];
    api->rsp->isdbt_status.STATUS = api->status;

    SiTRACE("Si2183 ISDBT_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((intack > Si2183_ISDBT_STATUS_CMD_INTACK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("INTACK %d ", intack );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_ISDBT_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si2183_ISDBT_STATUS_CMD_INTACK_MASK ) << Si2183_ISDBT_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing ISDBT_STATUS bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 14, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling ISDBT_STATUS response\n");
      return error_code;
    }

    api->rsp->isdbt_status.pclint           = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_ISDBT_STATUS_RESPONSE_PCLINT_LSB            , Si2183_ISDBT_STATUS_RESPONSE_PCLINT_MASK           );
    api->rsp->isdbt_status.dlint            = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_ISDBT_STATUS_RESPONSE_DLINT_LSB             , Si2183_ISDBT_STATUS_RESPONSE_DLINT_MASK            );
    api->rsp->isdbt_status.berint           = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_ISDBT_STATUS_RESPONSE_BERINT_LSB            , Si2183_ISDBT_STATUS_RESPONSE_BERINT_MASK           );
    api->rsp->isdbt_status.uncorint         = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_ISDBT_STATUS_RESPONSE_UNCORINT_LSB          , Si2183_ISDBT_STATUS_RESPONSE_UNCORINT_MASK         );
    api->rsp->isdbt_status.notisdbtint      = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_ISDBT_STATUS_RESPONSE_NOTISDBTINT_LSB       , Si2183_ISDBT_STATUS_RESPONSE_NOTISDBTINT_MASK      );
    api->rsp->isdbt_status.ewbsint          = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_ISDBT_STATUS_RESPONSE_EWBSINT_LSB           , Si2183_ISDBT_STATUS_RESPONSE_EWBSINT_MASK          );
    api->rsp->isdbt_status.pcl              = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_ISDBT_STATUS_RESPONSE_PCL_LSB               , Si2183_ISDBT_STATUS_RESPONSE_PCL_MASK              );
    api->rsp->isdbt_status.dl               = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_ISDBT_STATUS_RESPONSE_DL_LSB                , Si2183_ISDBT_STATUS_RESPONSE_DL_MASK               );
    api->rsp->isdbt_status.ber              = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_ISDBT_STATUS_RESPONSE_BER_LSB               , Si2183_ISDBT_STATUS_RESPONSE_BER_MASK              );
    api->rsp->isdbt_status.uncor            = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_ISDBT_STATUS_RESPONSE_UNCOR_LSB             , Si2183_ISDBT_STATUS_RESPONSE_UNCOR_MASK            );
    api->rsp->isdbt_status.notisdbt         = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_ISDBT_STATUS_RESPONSE_NOTISDBT_LSB          , Si2183_ISDBT_STATUS_RESPONSE_NOTISDBT_MASK         );
    api->rsp->isdbt_status.ewbs             = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_ISDBT_STATUS_RESPONSE_EWBS_LSB              , Si2183_ISDBT_STATUS_RESPONSE_EWBS_MASK             );
    api->rsp->isdbt_status.cnr              = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_ISDBT_STATUS_RESPONSE_CNR_LSB               , Si2183_ISDBT_STATUS_RESPONSE_CNR_MASK              );
    api->rsp->isdbt_status.afc_freq         = Si2183_convert_to_int   (&rspByteBuffer[ 4] , Si2183_ISDBT_STATUS_RESPONSE_AFC_FREQ_LSB          , Si2183_ISDBT_STATUS_RESPONSE_AFC_FREQ_MASK         );
    api->rsp->isdbt_status.timing_offset    = Si2183_convert_to_int   (&rspByteBuffer[ 6] , Si2183_ISDBT_STATUS_RESPONSE_TIMING_OFFSET_LSB     , Si2183_ISDBT_STATUS_RESPONSE_TIMING_OFFSET_MASK    );
    api->rsp->isdbt_status.fft_mode         = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_ISDBT_STATUS_RESPONSE_FFT_MODE_LSB          , Si2183_ISDBT_STATUS_RESPONSE_FFT_MODE_MASK         );
    api->rsp->isdbt_status.guard_int        = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_ISDBT_STATUS_RESPONSE_GUARD_INT_LSB         , Si2183_ISDBT_STATUS_RESPONSE_GUARD_INT_MASK        );
    api->rsp->isdbt_status.sp_inv           = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_ISDBT_STATUS_RESPONSE_SP_INV_LSB            , Si2183_ISDBT_STATUS_RESPONSE_SP_INV_MASK           );
    api->rsp->isdbt_status.nb_seg_a         = Si2183_convert_to_byte  (&rspByteBuffer[ 9] , Si2183_ISDBT_STATUS_RESPONSE_NB_SEG_A_LSB          , Si2183_ISDBT_STATUS_RESPONSE_NB_SEG_A_MASK         );
    api->rsp->isdbt_status.nb_seg_b         = Si2183_convert_to_byte  (&rspByteBuffer[ 9] , Si2183_ISDBT_STATUS_RESPONSE_NB_SEG_B_LSB          , Si2183_ISDBT_STATUS_RESPONSE_NB_SEG_B_MASK         );
    api->rsp->isdbt_status.nb_seg_c         = Si2183_convert_to_byte  (&rspByteBuffer[10] , Si2183_ISDBT_STATUS_RESPONSE_NB_SEG_C_LSB          , Si2183_ISDBT_STATUS_RESPONSE_NB_SEG_C_MASK         );
    api->rsp->isdbt_status.partial_flag     = Si2183_convert_to_byte  (&rspByteBuffer[10] , Si2183_ISDBT_STATUS_RESPONSE_PARTIAL_FLAG_LSB      , Si2183_ISDBT_STATUS_RESPONSE_PARTIAL_FLAG_MASK     );
    api->rsp->isdbt_status.syst_id          = Si2183_convert_to_byte  (&rspByteBuffer[10] , Si2183_ISDBT_STATUS_RESPONSE_SYST_ID_LSB           , Si2183_ISDBT_STATUS_RESPONSE_SYST_ID_MASK          );
    api->rsp->isdbt_status.reserved_msb     = Si2183_convert_to_byte  (&rspByteBuffer[11] , Si2183_ISDBT_STATUS_RESPONSE_RESERVED_MSB_LSB      , Si2183_ISDBT_STATUS_RESPONSE_RESERVED_MSB_MASK     );
    api->rsp->isdbt_status.phase_shift_corr = Si2183_convert_to_byte  (&rspByteBuffer[11] , Si2183_ISDBT_STATUS_RESPONSE_PHASE_SHIFT_CORR_LSB  , Si2183_ISDBT_STATUS_RESPONSE_PHASE_SHIFT_CORR_MASK );
    api->rsp->isdbt_status.emergency_flag   = Si2183_convert_to_byte  (&rspByteBuffer[11] , Si2183_ISDBT_STATUS_RESPONSE_EMERGENCY_FLAG_LSB    , Si2183_ISDBT_STATUS_RESPONSE_EMERGENCY_FLAG_MASK   );
    api->rsp->isdbt_status.reserved_lsb     = Si2183_convert_to_byte  (&rspByteBuffer[12] , Si2183_ISDBT_STATUS_RESPONSE_RESERVED_LSB_LSB      , Si2183_ISDBT_STATUS_RESPONSE_RESERVED_LSB_MASK     );
    api->rsp->isdbt_status.dl_c             = Si2183_convert_to_byte  (&rspByteBuffer[13] , Si2183_ISDBT_STATUS_RESPONSE_DL_C_LSB              , Si2183_ISDBT_STATUS_RESPONSE_DL_C_MASK             );
    api->rsp->isdbt_status.dl_b             = Si2183_convert_to_byte  (&rspByteBuffer[13] , Si2183_ISDBT_STATUS_RESPONSE_DL_B_LSB              , Si2183_ISDBT_STATUS_RESPONSE_DL_B_MASK             );
    api->rsp->isdbt_status.dl_a             = Si2183_convert_to_byte  (&rspByteBuffer[13] , Si2183_ISDBT_STATUS_RESPONSE_DL_A_LSB              , Si2183_ISDBT_STATUS_RESPONSE_DL_A_MASK             );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_ISDBT_STATUS_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_ISDBT_STATUS_CMD */
#endif /* DEMOD_ISDB_T */

#ifdef    DEMOD_MCNS
#ifdef    Si2183_MCNS_STATUS_CMD
/*---------------------------------------------------*/
/* Si2183_MCNS_STATUS COMMAND                                     */
/*---------------------------------------------------*/
unsigned char Si2183_L1_MCNS_STATUS               (L1_Si2183_Context *api,
                                                   unsigned char   intack)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[10];
    api->rsp->mcns_status.STATUS = api->status;

    SiTRACE("Si2183 MCNS_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((intack > Si2183_MCNS_STATUS_CMD_INTACK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("INTACK %d ", intack );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_MCNS_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si2183_MCNS_STATUS_CMD_INTACK_MASK ) << Si2183_MCNS_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing MCNS_STATUS bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 10, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling MCNS_STATUS response\n");
      return error_code;
    }

    api->rsp->mcns_status.pclint        = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_MCNS_STATUS_RESPONSE_PCLINT_LSB         , Si2183_MCNS_STATUS_RESPONSE_PCLINT_MASK        );
    api->rsp->mcns_status.dlint         = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_MCNS_STATUS_RESPONSE_DLINT_LSB          , Si2183_MCNS_STATUS_RESPONSE_DLINT_MASK         );
    api->rsp->mcns_status.berint        = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_MCNS_STATUS_RESPONSE_BERINT_LSB         , Si2183_MCNS_STATUS_RESPONSE_BERINT_MASK        );
    api->rsp->mcns_status.uncorint      = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_MCNS_STATUS_RESPONSE_UNCORINT_LSB       , Si2183_MCNS_STATUS_RESPONSE_UNCORINT_MASK      );
    api->rsp->mcns_status.pcl           = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_MCNS_STATUS_RESPONSE_PCL_LSB            , Si2183_MCNS_STATUS_RESPONSE_PCL_MASK           );
    api->rsp->mcns_status.dl            = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_MCNS_STATUS_RESPONSE_DL_LSB             , Si2183_MCNS_STATUS_RESPONSE_DL_MASK            );
    api->rsp->mcns_status.ber           = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_MCNS_STATUS_RESPONSE_BER_LSB            , Si2183_MCNS_STATUS_RESPONSE_BER_MASK           );
    api->rsp->mcns_status.uncor         = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_MCNS_STATUS_RESPONSE_UNCOR_LSB          , Si2183_MCNS_STATUS_RESPONSE_UNCOR_MASK         );
    api->rsp->mcns_status.cnr           = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_MCNS_STATUS_RESPONSE_CNR_LSB            , Si2183_MCNS_STATUS_RESPONSE_CNR_MASK           );
    api->rsp->mcns_status.afc_freq      = Si2183_convert_to_int   (&rspByteBuffer[ 4] , Si2183_MCNS_STATUS_RESPONSE_AFC_FREQ_LSB       , Si2183_MCNS_STATUS_RESPONSE_AFC_FREQ_MASK      );
    api->rsp->mcns_status.timing_offset = Si2183_convert_to_int   (&rspByteBuffer[ 6] , Si2183_MCNS_STATUS_RESPONSE_TIMING_OFFSET_LSB  , Si2183_MCNS_STATUS_RESPONSE_TIMING_OFFSET_MASK );
    api->rsp->mcns_status.constellation = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_MCNS_STATUS_RESPONSE_CONSTELLATION_LSB  , Si2183_MCNS_STATUS_RESPONSE_CONSTELLATION_MASK );
    api->rsp->mcns_status.sp_inv        = Si2183_convert_to_byte  (&rspByteBuffer[ 8] , Si2183_MCNS_STATUS_RESPONSE_SP_INV_LSB         , Si2183_MCNS_STATUS_RESPONSE_SP_INV_MASK        );
    api->rsp->mcns_status.interleaving  = Si2183_convert_to_byte  (&rspByteBuffer[ 9] , Si2183_MCNS_STATUS_RESPONSE_INTERLEAVING_LSB   , Si2183_MCNS_STATUS_RESPONSE_INTERLEAVING_MASK  );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_MCNS_STATUS_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_MCNS_STATUS_CMD */
#endif /* DEMOD_MCNS */

#ifdef    Si2183_PART_INFO_CMD
/*---------------------------------------------------*/
/* Si2183_PART_INFO COMMAND                                         */
/*---------------------------------------------------*/
unsigned char Si2183_L1_PART_INFO                 (L1_Si2183_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[14];
    api->rsp->part_info.STATUS = api->status;

    SiTRACE("Si2183 PART_INFO ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_PART_INFO_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing PART_INFO bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 14, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling PART_INFO response\n");
      return error_code;
    }

    api->rsp->part_info.chiprev  = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_PART_INFO_RESPONSE_CHIPREV_LSB   , Si2183_PART_INFO_RESPONSE_CHIPREV_MASK  );
    api->rsp->part_info.part     = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_PART_INFO_RESPONSE_PART_LSB      , Si2183_PART_INFO_RESPONSE_PART_MASK     );
    api->rsp->part_info.pmajor   = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_PART_INFO_RESPONSE_PMAJOR_LSB    , Si2183_PART_INFO_RESPONSE_PMAJOR_MASK   );
    api->rsp->part_info.pminor   = Si2183_convert_to_byte  (&rspByteBuffer[ 4] , Si2183_PART_INFO_RESPONSE_PMINOR_LSB    , Si2183_PART_INFO_RESPONSE_PMINOR_MASK   );
    api->rsp->part_info.pbuild   = Si2183_convert_to_byte  (&rspByteBuffer[ 5] , Si2183_PART_INFO_RESPONSE_PBUILD_LSB    , Si2183_PART_INFO_RESPONSE_PBUILD_MASK   );
    api->rsp->part_info.reserved = Si2183_convert_to_uint  (&rspByteBuffer[ 6] , Si2183_PART_INFO_RESPONSE_RESERVED_LSB  , Si2183_PART_INFO_RESPONSE_RESERVED_MASK );
    api->rsp->part_info.serial   = Si2183_convert_to_ulong (&rspByteBuffer[ 8] , Si2183_PART_INFO_RESPONSE_SERIAL_LSB    , Si2183_PART_INFO_RESPONSE_SERIAL_MASK   );
    api->rsp->part_info.romid    = Si2183_convert_to_byte  (&rspByteBuffer[12] , Si2183_PART_INFO_RESPONSE_ROMID_LSB     , Si2183_PART_INFO_RESPONSE_ROMID_MASK    );
    api->rsp->part_info.rx       = Si2183_convert_to_byte  (&rspByteBuffer[13] , Si2183_PART_INFO_RESPONSE_RX_LSB        , Si2183_PART_INFO_RESPONSE_RX_MASK       );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_PART_INFO_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_PART_INFO_CMD */
#ifdef    Si2183_POWER_DOWN_CMD
/*---------------------------------------------------*/
/* Si2183_POWER_DOWN COMMAND                                       */
/*---------------------------------------------------*/
unsigned char Si2183_L1_POWER_DOWN                (L1_Si2183_Context *api)
{
    unsigned char cmdByteBuffer[1];
    api->rsp->power_down.STATUS = api->status;

    SiTRACE("Si2183 POWER_DOWN ");
    SiTRACE("\n");

    system_wait(2); /* Make sure that the FW 'main' function has applied any previous settings before going to standby */

    cmdByteBuffer[0] = Si2183_POWER_DOWN_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing POWER_DOWN bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    return NO_Si2183_ERROR;
}
#endif /* Si2183_POWER_DOWN_CMD */
#ifdef    Si2183_POWER_UP_CMD
/*---------------------------------------------------*/
/* Si2183_POWER_UP COMMAND                                           */
/*---------------------------------------------------*/
unsigned char Si2183_L1_POWER_UP                  (L1_Si2183_Context *api,
                                                   unsigned char   subcode,
                                                   unsigned char   reset,
                                                   unsigned char   reserved2,
                                                   unsigned char   reserved4,
                                                   unsigned char   reserved1,
                                                   unsigned char   addr_mode,
                                                   unsigned char   reserved5,
                                                   unsigned char   func,
                                                   unsigned char   clock_freq,
                                                   unsigned char   ctsien,
                                                   unsigned char   wake_up)
{
  #ifdef   DEBUG_RANGE_CHECK
    unsigned char error_code = 0;
  #endif /* DEBUG_RANGE_CHECK */
    unsigned char cmdByteBuffer[8];
    unsigned char rspByteBuffer[1];
    api->rsp->power_up.STATUS = api->status;

    SiTRACE("Si2183 POWER_UP ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode    > Si2183_POWER_UP_CMD_SUBCODE_MAX   )  || (subcode    < Si2183_POWER_UP_CMD_SUBCODE_MIN   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "   , subcode    );
    if ((reset      > Si2183_POWER_UP_CMD_RESET_MAX     )  || (reset      < Si2183_POWER_UP_CMD_RESET_MIN     ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESET %d "     , reset      );
    if ((reserved2  > Si2183_POWER_UP_CMD_RESERVED2_MAX )  || (reserved2  < Si2183_POWER_UP_CMD_RESERVED2_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED2 %d " , reserved2  );
    if ((reserved4  > Si2183_POWER_UP_CMD_RESERVED4_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED4 %d " , reserved4  );
    if ((reserved1  > Si2183_POWER_UP_CMD_RESERVED1_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED1 %d " , reserved1  );
    if ((addr_mode  > Si2183_POWER_UP_CMD_ADDR_MODE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("ADDR_MODE %d " , addr_mode  );
    if ((reserved5  > Si2183_POWER_UP_CMD_RESERVED5_MAX )  || (reserved5  < Si2183_POWER_UP_CMD_RESERVED5_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED5 %d " , reserved5  );
    if ((func       > Si2183_POWER_UP_CMD_FUNC_MAX      ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FUNC %d "      , func       );
    if ((clock_freq > Si2183_POWER_UP_CMD_CLOCK_FREQ_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CLOCK_FREQ %d ", clock_freq );
    if ((ctsien     > Si2183_POWER_UP_CMD_CTSIEN_MAX    ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CTSIEN %d "    , ctsien     );
    if ((wake_up    > Si2183_POWER_UP_CMD_WAKE_UP_MAX   )  || (wake_up    < Si2183_POWER_UP_CMD_WAKE_UP_MIN   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("WAKE_UP %d "   , wake_up    );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_POWER_UP_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode    & Si2183_POWER_UP_CMD_SUBCODE_MASK    ) << Si2183_POWER_UP_CMD_SUBCODE_LSB   );
    cmdByteBuffer[2] = (unsigned char) ( ( reset      & Si2183_POWER_UP_CMD_RESET_MASK      ) << Si2183_POWER_UP_CMD_RESET_LSB     );
    cmdByteBuffer[3] = (unsigned char) ( ( reserved2  & Si2183_POWER_UP_CMD_RESERVED2_MASK  ) << Si2183_POWER_UP_CMD_RESERVED2_LSB );
    cmdByteBuffer[4] = (unsigned char) ( ( reserved4  & Si2183_POWER_UP_CMD_RESERVED4_MASK  ) << Si2183_POWER_UP_CMD_RESERVED4_LSB );
    cmdByteBuffer[5] = (unsigned char) ( ( reserved1  & Si2183_POWER_UP_CMD_RESERVED1_MASK  ) << Si2183_POWER_UP_CMD_RESERVED1_LSB |
                                         ( addr_mode  & Si2183_POWER_UP_CMD_ADDR_MODE_MASK  ) << Si2183_POWER_UP_CMD_ADDR_MODE_LSB |
                                         ( reserved5  & Si2183_POWER_UP_CMD_RESERVED5_MASK  ) << Si2183_POWER_UP_CMD_RESERVED5_LSB );
    cmdByteBuffer[6] = (unsigned char) ( ( func       & Si2183_POWER_UP_CMD_FUNC_MASK       ) << Si2183_POWER_UP_CMD_FUNC_LSB      |
                                         ( clock_freq & Si2183_POWER_UP_CMD_CLOCK_FREQ_MASK ) << Si2183_POWER_UP_CMD_CLOCK_FREQ_LSB|
                                         ( ctsien     & Si2183_POWER_UP_CMD_CTSIEN_MASK     ) << Si2183_POWER_UP_CMD_CTSIEN_LSB    );
    cmdByteBuffer[7] = (unsigned char) ( ( wake_up    & Si2183_POWER_UP_CMD_WAKE_UP_MASK    ) << Si2183_POWER_UP_CMD_WAKE_UP_LSB   );

    if (L0_WriteCommandBytes(api->i2c, 8, cmdByteBuffer) != 8) {
      SiTRACE("Error writing POWER_UP bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    /* only check CTS after POWER_UP / RESET */
    if (reset == Si2183_POWER_UP_CMD_RESET_RESET) {
      error_code = Si2183_pollForResponse(api, 1, rspByteBuffer);
      if (error_code) {
        SiTRACE("Error polling POWER_UP response\n");
        return error_code;
      }
    }

    system_wait(10); /* We have to wait 10ms after a power up to send a command to the firmware*/

    return NO_Si2183_ERROR;
}
#endif /* Si2183_POWER_UP_CMD */
#ifdef    Si2183_RSSI_ADC_CMD
/*---------------------------------------------------*/
/* Si2183_RSSI_ADC COMMAND                                           */
/*---------------------------------------------------*/
unsigned char Si2183_L1_RSSI_ADC                  (L1_Si2183_Context *api,
                                                   unsigned char   on_off)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[2];
    api->rsp->rssi_adc.STATUS = api->status;

    SiTRACE("Si2183 RSSI_ADC ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((on_off > Si2183_RSSI_ADC_CMD_ON_OFF_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("ON_OFF %d ", on_off );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_RSSI_ADC_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( on_off & Si2183_RSSI_ADC_CMD_ON_OFF_MASK ) << Si2183_RSSI_ADC_CMD_ON_OFF_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing RSSI_ADC bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 2, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling RSSI_ADC response\n");
      return error_code;
    }

    api->rsp->rssi_adc.level = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_RSSI_ADC_RESPONSE_LEVEL_LSB  , Si2183_RSSI_ADC_RESPONSE_LEVEL_MASK );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_RSSI_ADC_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_RSSI_ADC_CMD */
#ifdef    Si2183_SCAN_CTRL_CMD
/*---------------------------------------------------*/
/* Si2183_SCAN_CTRL COMMAND                                         */
/*---------------------------------------------------*/
unsigned char Si2183_L1_SCAN_CTRL                 (L1_Si2183_Context *api,
                                                   unsigned char   action,
                                                   unsigned long   tuned_rf_freq)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[8];
    unsigned char rspByteBuffer[1];
    api->rsp->scan_ctrl.STATUS = api->status;

    SiTRACE("Si2183 SCAN_CTRL ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((action        > Si2183_SCAN_CTRL_CMD_ACTION_MAX       )  || (action        < Si2183_SCAN_CTRL_CMD_ACTION_MIN       ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("ACTION %d "       , action        );
    SiTRACE("TUNED_RF_FREQ %ld ", tuned_rf_freq );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_SCAN_CTRL_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( action        & Si2183_SCAN_CTRL_CMD_ACTION_MASK        ) << Si2183_SCAN_CTRL_CMD_ACTION_LSB       );
    cmdByteBuffer[2] = (unsigned char)0x00;
    cmdByteBuffer[3] = (unsigned char)0x00;
    cmdByteBuffer[4] = (unsigned char) ( ( tuned_rf_freq & Si2183_SCAN_CTRL_CMD_TUNED_RF_FREQ_MASK ) << Si2183_SCAN_CTRL_CMD_TUNED_RF_FREQ_LSB);
    cmdByteBuffer[5] = (unsigned char) ((( tuned_rf_freq & Si2183_SCAN_CTRL_CMD_TUNED_RF_FREQ_MASK ) << Si2183_SCAN_CTRL_CMD_TUNED_RF_FREQ_LSB)>>8);
    cmdByteBuffer[6] = (unsigned char) ((( tuned_rf_freq & Si2183_SCAN_CTRL_CMD_TUNED_RF_FREQ_MASK ) << Si2183_SCAN_CTRL_CMD_TUNED_RF_FREQ_LSB)>>16);
    cmdByteBuffer[7] = (unsigned char) ((( tuned_rf_freq & Si2183_SCAN_CTRL_CMD_TUNED_RF_FREQ_MASK ) << Si2183_SCAN_CTRL_CMD_TUNED_RF_FREQ_LSB)>>24);

    if (L0_WriteCommandBytes(api->i2c, 8, cmdByteBuffer) != 8) {
      SiTRACE("Error writing SCAN_CTRL bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling SCAN_CTRL response\n");
      return error_code;
    }

    return NO_Si2183_ERROR;
}
#endif /* Si2183_SCAN_CTRL_CMD */
#ifdef    Si2183_SCAN_STATUS_CMD
/*---------------------------------------------------*/
/* Si2183_SCAN_STATUS COMMAND                                     */
/*---------------------------------------------------*/
unsigned char Si2183_L1_SCAN_STATUS               (L1_Si2183_Context *api,
                                                   unsigned char   intack)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[11];
    api->rsp->scan_status.STATUS = api->status;

    SiTRACE("Si2183 SCAN_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((intack > Si2183_SCAN_STATUS_CMD_INTACK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("INTACK %d ", intack );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_SCAN_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si2183_SCAN_STATUS_CMD_INTACK_MASK ) << Si2183_SCAN_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing SCAN_STATUS bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 11, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling SCAN_STATUS response\n");
      return error_code;
    }

    api->rsp->scan_status.buzint      = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_SCAN_STATUS_RESPONSE_BUZINT_LSB       , Si2183_SCAN_STATUS_RESPONSE_BUZINT_MASK      );
    api->rsp->scan_status.reqint      = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_SCAN_STATUS_RESPONSE_REQINT_LSB       , Si2183_SCAN_STATUS_RESPONSE_REQINT_MASK      );
    api->rsp->scan_status.buz         = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_SCAN_STATUS_RESPONSE_BUZ_LSB          , Si2183_SCAN_STATUS_RESPONSE_BUZ_MASK         );
    api->rsp->scan_status.req         = Si2183_convert_to_byte  (&rspByteBuffer[ 2] , Si2183_SCAN_STATUS_RESPONSE_REQ_LSB          , Si2183_SCAN_STATUS_RESPONSE_REQ_MASK         );
    api->rsp->scan_status.scan_status = Si2183_convert_to_byte  (&rspByteBuffer[ 3] , Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_LSB  , Si2183_SCAN_STATUS_RESPONSE_SCAN_STATUS_MASK );
    api->rsp->scan_status.rf_freq     = Si2183_convert_to_ulong (&rspByteBuffer[ 4] , Si2183_SCAN_STATUS_RESPONSE_RF_FREQ_LSB      , Si2183_SCAN_STATUS_RESPONSE_RF_FREQ_MASK     );
    api->rsp->scan_status.symb_rate   = Si2183_convert_to_uint  (&rspByteBuffer[ 8] , Si2183_SCAN_STATUS_RESPONSE_SYMB_RATE_LSB    , Si2183_SCAN_STATUS_RESPONSE_SYMB_RATE_MASK   );
    api->rsp->scan_status.modulation  = Si2183_convert_to_byte  (&rspByteBuffer[10] , Si2183_SCAN_STATUS_RESPONSE_MODULATION_LSB   , Si2183_SCAN_STATUS_RESPONSE_MODULATION_MASK  );

    Si2183_TRACE_COMMAND_REPLY(api, Si2183_SCAN_STATUS_CMD_CODE);

    return NO_Si2183_ERROR;
}
#endif /* Si2183_SCAN_STATUS_CMD */
#ifdef    Si2183_SET_PROPERTY_CMD
/*---------------------------------------------------*/
/* Si2183_SET_PROPERTY COMMAND                                   */
/*---------------------------------------------------*/
unsigned char Si2183_L1_SET_PROPERTY              (L1_Si2183_Context *api,
                                                   unsigned char   reserved,
                                                   unsigned int    prop,
                                                   unsigned int    data)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[6];
    unsigned char rspByteBuffer[4];
    api->rsp->set_property.STATUS = api->status;

/*    SiTRACE("Si2183 SET_PROPERTY RESERVED %d  PROP 0x%04x  DATA %d\n", reserved, prop, data);*/

    cmdByteBuffer[0] = Si2183_SET_PROPERTY_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( reserved & Si2183_SET_PROPERTY_CMD_RESERVED_MASK ) << Si2183_SET_PROPERTY_CMD_RESERVED_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( prop     & Si2183_SET_PROPERTY_CMD_PROP_MASK     ) << Si2183_SET_PROPERTY_CMD_PROP_LSB    );
    cmdByteBuffer[3] = (unsigned char) ((( prop     & Si2183_SET_PROPERTY_CMD_PROP_MASK     ) << Si2183_SET_PROPERTY_CMD_PROP_LSB    )>>8);
    cmdByteBuffer[4] = (unsigned char) ( ( data     & Si2183_SET_PROPERTY_CMD_DATA_MASK     ) << Si2183_SET_PROPERTY_CMD_DATA_LSB    );
    cmdByteBuffer[5] = (unsigned char) ((( data     & Si2183_SET_PROPERTY_CMD_DATA_MASK     ) << Si2183_SET_PROPERTY_CMD_DATA_LSB    )>>8);

    if (L0_WriteCommandBytes(api->i2c, 6, cmdByteBuffer) != 6) {
      SiTRACE("Error writing SET_PROPERTY bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    error_code = Si2183_pollForResponse(api, 4, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling SET_PROPERTY response\n");
      return error_code;
    }

    api->rsp->set_property.reserved = Si2183_convert_to_byte  (&rspByteBuffer[ 1] , Si2183_SET_PROPERTY_RESPONSE_RESERVED_LSB  , Si2183_SET_PROPERTY_RESPONSE_RESERVED_MASK );
    api->rsp->set_property.data     = Si2183_convert_to_uint  (&rspByteBuffer[ 2] , Si2183_SET_PROPERTY_RESPONSE_DATA_LSB      , Si2183_SET_PROPERTY_RESPONSE_DATA_MASK     );

    return NO_Si2183_ERROR;
}
#endif /* Si2183_SET_PROPERTY_CMD */
#ifdef    Si2183_SPI_LINK_CMD
/*---------------------------------------------------*/
/* Si2183_SPI_LINK COMMAND                                           */
/*---------------------------------------------------*/
unsigned char Si2183_L1_SPI_LINK                  (L1_Si2183_Context *api,
                                                   unsigned char   subcode,
                                                   unsigned char   spi_pbl_key,
                                                   unsigned char   spi_pbl_num,
                                                   unsigned char   spi_conf_clk,
                                                   unsigned char   spi_clk_pola,
                                                   unsigned char   spi_conf_data,
                                                   unsigned char   spi_data_dir,
                                                   unsigned char   spi_enable)
{
  #ifdef   DEBUG_RANGE_CHECK
    unsigned char error_code = 0;
    int i;
  #endif /* DEBUG_RANGE_CHECK */
    unsigned char cmdByteBuffer[7];
    api->rsp->spi_link.STATUS = api->status;

    SiTRACE("Si2183 SPI_LINK ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode       > Si2183_SPI_LINK_CMD_SUBCODE_MAX      )  || (subcode       < Si2183_SPI_LINK_CMD_SUBCODE_MIN      ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "      , subcode       );
    SiTRACE("SPI_PBL_KEY %d "  , spi_pbl_key   );
    if ((spi_pbl_num   > Si2183_SPI_LINK_CMD_SPI_PBL_NUM_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SPI_PBL_NUM %d "  , spi_pbl_num   );
    if ((spi_conf_clk  > Si2183_SPI_LINK_CMD_SPI_CONF_CLK_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SPI_CONF_CLK %d " , spi_conf_clk  );
    if ((spi_clk_pola  > Si2183_SPI_LINK_CMD_SPI_CLK_POLA_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SPI_CLK_POLA %d " , spi_clk_pola  );
    if ((spi_conf_data > Si2183_SPI_LINK_CMD_SPI_CONF_DATA_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SPI_CONF_DATA %d ", spi_conf_data );
    if ((spi_data_dir  > Si2183_SPI_LINK_CMD_SPI_DATA_DIR_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SPI_DATA_DIR %d " , spi_data_dir  );
    if ((spi_enable    > Si2183_SPI_LINK_CMD_SPI_ENABLE_MAX   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SPI_ENABLE %d "   , spi_enable    );
    SiTRACE("\n");
    sprintf(api->msg, "SPI_LINK");\
    sprintf(api->msg, "%s  -SUBCODE", api->msg); i = 0;
      if (api->cmd->spi_link.subcode == 56) { sprintf(api->msg, "%s CODE", api->msg); i++; }
      if (i == 0 ) { sprintf(api->msg, "%s %ld", api->msg, (long int)api->cmd->spi_link.subcode); }
    sprintf(api->msg, "%s  -SPI_PBL_KEY", api->msg); i = 0;
      if (i == 0 ) { sprintf(api->msg, "%s 0x%02x", api->msg, (int)api->cmd->spi_link.spi_pbl_key); }
    sprintf(api->msg, "%s  -SPI_PBL_NUM", api->msg); i = 0;
      if (i == 0 ) { sprintf(api->msg, "%s %ld", api->msg, (long int)api->cmd->spi_link.spi_pbl_num); }
    sprintf(api->msg, "%s  -SPI_CONF_CLK", api->msg); i = 0;
      if (api->cmd->spi_link.spi_conf_clk == 0) { sprintf(api->msg, "%s DISABLE   ", api->msg); i++; }
      if (api->cmd->spi_link.spi_conf_clk == 9) { sprintf(api->msg, "%s DISEQC_CMD", api->msg); i++; }
      if (api->cmd->spi_link.spi_conf_clk == 7) { sprintf(api->msg, "%s DISEQC_IN ", api->msg); i++; }
      if (api->cmd->spi_link.spi_conf_clk == 8) { sprintf(api->msg, "%s DISEQC_OUT", api->msg); i++; }
      if (api->cmd->spi_link.spi_conf_clk == 5) { sprintf(api->msg, "%s GPIO0     ", api->msg); i++; }
      if (api->cmd->spi_link.spi_conf_clk == 6) { sprintf(api->msg, "%s GPIO1     ", api->msg); i++; }
      if (api->cmd->spi_link.spi_conf_clk == 1) { sprintf(api->msg, "%s MP_A      ", api->msg); i++; }
      if (api->cmd->spi_link.spi_conf_clk == 2) { sprintf(api->msg, "%s MP_B      ", api->msg); i++; }
      if (api->cmd->spi_link.spi_conf_clk == 3) { sprintf(api->msg, "%s MP_C      ", api->msg); i++; }
      if (api->cmd->spi_link.spi_conf_clk == 4) { sprintf(api->msg, "%s MP_D      ", api->msg); i++; }
      if (i == 0 ) { sprintf(api->msg, "%s %ld", api->msg, (long int)api->cmd->spi_link.spi_conf_clk); }
    sprintf(api->msg, "%s  -SPI_CLK_POLA", api->msg); i = 0;
      if (api->cmd->spi_link.spi_clk_pola == 1) { sprintf(api->msg, "%s FALLING", api->msg); i++; }
      if (api->cmd->spi_link.spi_clk_pola == 0) { sprintf(api->msg, "%s RISING ", api->msg); i++; }
      if (i == 0 ) { sprintf(api->msg, "%s %ld", api->msg, (long int)api->cmd->spi_link.spi_clk_pola); }
    sprintf(api->msg, "%s  -SPI_CONF_DATA", api->msg); i = 0;
      if (api->cmd->spi_link.spi_conf_data == 0) { sprintf(api->msg, "%s DISABLE   ", api->msg); i++; }
      if (api->cmd->spi_link.spi_conf_data == 9) { sprintf(api->msg, "%s DISEQC_CMD", api->msg); i++; }
      if (api->cmd->spi_link.spi_conf_data == 7) { sprintf(api->msg, "%s DISEQC_IN ", api->msg); i++; }
      if (api->cmd->spi_link.spi_conf_data == 8) { sprintf(api->msg, "%s DISEQC_OUT", api->msg); i++; }
      if (api->cmd->spi_link.spi_conf_data == 5) { sprintf(api->msg, "%s GPIO0     ", api->msg); i++; }
      if (api->cmd->spi_link.spi_conf_data == 6) { sprintf(api->msg, "%s GPIO1     ", api->msg); i++; }
      if (api->cmd->spi_link.spi_conf_data == 1) { sprintf(api->msg, "%s MP_A      ", api->msg); i++; }
      if (api->cmd->spi_link.spi_conf_data == 2) { sprintf(api->msg, "%s MP_B      ", api->msg); i++; }
      if (api->cmd->spi_link.spi_conf_data == 3) { sprintf(api->msg, "%s MP_C      ", api->msg); i++; }
      if (api->cmd->spi_link.spi_conf_data == 4) { sprintf(api->msg, "%s MP_D      ", api->msg); i++; }
      if (i == 0 ) { sprintf(api->msg, "%s %ld", api->msg, (long int)api->cmd->spi_link.spi_conf_data); }
    sprintf(api->msg, "%s  -SPI_DATA_DIR", api->msg); i = 0;
      if (api->cmd->spi_link.spi_data_dir == 1) { sprintf(api->msg, "%s LSB_FIRST", api->msg); i++; }
      if (api->cmd->spi_link.spi_data_dir == 0) { sprintf(api->msg, "%s MSB_FIRST", api->msg); i++; }
      if (i == 0 ) { sprintf(api->msg, "%s %ld", api->msg, (long int)api->cmd->spi_link.spi_data_dir); }
    sprintf(api->msg, "%s  -SPI_ENABLE", api->msg); i = 0;
      if (api->cmd->spi_link.spi_enable == 0) { sprintf(api->msg, "%s DISABLE", api->msg); i++; }
      if (api->cmd->spi_link.spi_enable == 1) { sprintf(api->msg, "%s ENABLE ", api->msg); i++; }
      if (i == 0 ) { sprintf(api->msg, "%s %ld", api->msg, (long int)api->cmd->spi_link.spi_enable); }
      SiTRACE("%s", api->msg);
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_SPI_LINK_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode       & Si2183_SPI_LINK_CMD_SUBCODE_MASK       ) << Si2183_SPI_LINK_CMD_SUBCODE_LSB      );
    cmdByteBuffer[2] = (unsigned char) ( ( spi_pbl_key   & Si2183_SPI_LINK_CMD_SPI_PBL_KEY_MASK   ) << Si2183_SPI_LINK_CMD_SPI_PBL_KEY_LSB  );
    cmdByteBuffer[3] = (unsigned char) ( ( spi_pbl_num   & Si2183_SPI_LINK_CMD_SPI_PBL_NUM_MASK   ) << Si2183_SPI_LINK_CMD_SPI_PBL_NUM_LSB  );
    cmdByteBuffer[4] = (unsigned char) ( ( spi_conf_clk  & Si2183_SPI_LINK_CMD_SPI_CONF_CLK_MASK  ) << Si2183_SPI_LINK_CMD_SPI_CONF_CLK_LSB |
                                         ( spi_clk_pola  & Si2183_SPI_LINK_CMD_SPI_CLK_POLA_MASK  ) << Si2183_SPI_LINK_CMD_SPI_CLK_POLA_LSB );
    cmdByteBuffer[5] = (unsigned char) ( ( spi_conf_data & Si2183_SPI_LINK_CMD_SPI_CONF_DATA_MASK ) << Si2183_SPI_LINK_CMD_SPI_CONF_DATA_LSB|
                                         ( spi_data_dir  & Si2183_SPI_LINK_CMD_SPI_DATA_DIR_MASK  ) << Si2183_SPI_LINK_CMD_SPI_DATA_DIR_LSB );
    cmdByteBuffer[6] = (unsigned char) ( ( spi_enable    & Si2183_SPI_LINK_CMD_SPI_ENABLE_MASK    ) << Si2183_SPI_LINK_CMD_SPI_ENABLE_LSB   );

    if (L0_WriteCommandBytes(api->i2c, 7, cmdByteBuffer) != 7) {
      SiTRACE("Error writing SPI_LINK bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    return NO_Si2183_ERROR;
}
#endif /* Si2183_SPI_LINK_CMD */
#ifdef    Si2183_SPI_PASSTHROUGH_CMD
/*---------------------------------------------------*/
/* Si2183_SPI_PASSTHROUGH COMMAND                             */
/*---------------------------------------------------*/
unsigned char Si2183_L1_SPI_PASSTHROUGH           (L1_Si2183_Context *api,
                                                   unsigned char   subcode,
                                                   unsigned char   spi_passthr_clk,
                                                   unsigned char   spi_passth_data)
{
  #ifdef   DEBUG_RANGE_CHECK
    unsigned char error_code = 0;
  #endif /* DEBUG_RANGE_CHECK */
    unsigned char cmdByteBuffer[4];
    api->rsp->spi_passthrough.STATUS = api->status;

    SiTRACE("Si2183 SPI_PASSTHROUGH ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode         > Si2183_SPI_PASSTHROUGH_CMD_SUBCODE_MAX        )  || (subcode         < Si2183_SPI_PASSTHROUGH_CMD_SUBCODE_MIN        ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "        , subcode         );
    if ((spi_passthr_clk > Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTHR_CLK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SPI_PASSTHR_CLK %d ", spi_passthr_clk );
    if ((spi_passth_data > Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTH_DATA_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SPI_PASSTH_DATA %d ", spi_passth_data );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_SPI_PASSTHROUGH_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode         & Si2183_SPI_PASSTHROUGH_CMD_SUBCODE_MASK         ) << Si2183_SPI_PASSTHROUGH_CMD_SUBCODE_LSB        );
    cmdByteBuffer[2] = (unsigned char) ( ( spi_passthr_clk & Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTHR_CLK_MASK ) << Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTHR_CLK_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( spi_passth_data & Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTH_DATA_MASK ) << Si2183_SPI_PASSTHROUGH_CMD_SPI_PASSTH_DATA_LSB);

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing SPI_PASSTHROUGH bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    return NO_Si2183_ERROR;
}
#endif /* Si2183_SPI_PASSTHROUGH_CMD */
#ifdef    Si2183_START_CLK_CMD
/*---------------------------------------------------*/
/* Si2183_START_CLK COMMAND                                         */
/*---------------------------------------------------*/
unsigned char Si2183_L1_START_CLK                 (L1_Si2183_Context *api,
                                                   unsigned char   subcode,
                                                   unsigned char   reserved1,
                                                   unsigned char   tune_cap,
                                                   unsigned char   reserved2,
                                                   unsigned int    clk_mode,
                                                   unsigned char   reserved3,
                                                   unsigned char   reserved4,
                                                   unsigned char   start_clk)
{
  #ifdef   DEBUG_RANGE_CHECK
    unsigned char error_code = 0;
  #endif /* DEBUG_RANGE_CHECK */
    unsigned char cmdByteBuffer[13];
    api->rsp->start_clk.STATUS = api->status;

    SiTRACE("Si2183 START_CLK ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode   > Si2183_START_CLK_CMD_SUBCODE_MAX  )  || (subcode   < Si2183_START_CLK_CMD_SUBCODE_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "  , subcode   );
    if ((reserved1 > Si2183_START_CLK_CMD_RESERVED1_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED1 %d ", reserved1 );
    if ((tune_cap  > Si2183_START_CLK_CMD_TUNE_CAP_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("TUNE_CAP %d " , tune_cap  );
    if ((reserved2 > Si2183_START_CLK_CMD_RESERVED2_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED2 %d ", reserved2 );
    if ((clk_mode  > Si2183_START_CLK_CMD_CLK_MODE_MAX )  || (clk_mode  < Si2183_START_CLK_CMD_CLK_MODE_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CLK_MODE %d " , clk_mode  );
    if ((reserved3 > Si2183_START_CLK_CMD_RESERVED3_MAX)  || (reserved3 < Si2183_START_CLK_CMD_RESERVED3_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED3 %d ", reserved3 );
    if ((reserved4 > Si2183_START_CLK_CMD_RESERVED4_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED4 %d ", reserved4 );
    if ((start_clk > Si2183_START_CLK_CMD_START_CLK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("START_CLK %d ", start_clk );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2183_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2183_START_CLK_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode   & Si2183_START_CLK_CMD_SUBCODE_MASK   ) << Si2183_START_CLK_CMD_SUBCODE_LSB  );
    cmdByteBuffer[2] = (unsigned char) ( ( reserved1 & Si2183_START_CLK_CMD_RESERVED1_MASK ) << Si2183_START_CLK_CMD_RESERVED1_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( tune_cap  & Si2183_START_CLK_CMD_TUNE_CAP_MASK  ) << Si2183_START_CLK_CMD_TUNE_CAP_LSB |
                                         ( reserved2 & Si2183_START_CLK_CMD_RESERVED2_MASK ) << Si2183_START_CLK_CMD_RESERVED2_LSB);
    cmdByteBuffer[4] = (unsigned char) ( ( clk_mode  & Si2183_START_CLK_CMD_CLK_MODE_MASK  ) << Si2183_START_CLK_CMD_CLK_MODE_LSB );
    cmdByteBuffer[5] = (unsigned char) ((( clk_mode  & Si2183_START_CLK_CMD_CLK_MODE_MASK  ) << Si2183_START_CLK_CMD_CLK_MODE_LSB )>>8);
    cmdByteBuffer[6] = (unsigned char) ( ( reserved3 & Si2183_START_CLK_CMD_RESERVED3_MASK ) << Si2183_START_CLK_CMD_RESERVED3_LSB);
    cmdByteBuffer[7] = (unsigned char) ( ( reserved4 & Si2183_START_CLK_CMD_RESERVED4_MASK ) << Si2183_START_CLK_CMD_RESERVED4_LSB);
    cmdByteBuffer[8] = (unsigned char)0x00;
    cmdByteBuffer[9] = (unsigned char)0x00;
    cmdByteBuffer[10] = (unsigned char)0x00;
    cmdByteBuffer[11] = (unsigned char)0x00;
    cmdByteBuffer[12] = (unsigned char) ( ( start_clk & Si2183_START_CLK_CMD_START_CLK_MASK ) << Si2183_START_CLK_CMD_START_CLK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 13, cmdByteBuffer) != 13) {
      SiTRACE("Error writing START_CLK bytes!\n");
      return ERROR_Si2183_SENDING_COMMAND;
    }

    return NO_Si2183_ERROR;
}
#endif /* Si2183_START_CLK_CMD */


  /* --------------------------------------------*/
  /* SEND_COMMAND2 FUNCTION                      */
  /* --------------------------------------------*/
unsigned char   Si2183_L1_SendCommand2(L1_Si2183_Context *api, unsigned int cmd_code) {
    switch (cmd_code) {
    #ifdef        Si2183_CONFIG_CLKIO_CMD
     case         Si2183_CONFIG_CLKIO_CMD_CODE:
       return Si2183_L1_CONFIG_CLKIO (api, api->cmd->config_clkio.output, api->cmd->config_clkio.pre_driver_str, api->cmd->config_clkio.driver_str );
     break;
    #endif /*     Si2183_CONFIG_CLKIO_CMD */
    #ifdef        Si2183_CONFIG_I2C_CMD
     case         Si2183_CONFIG_I2C_CMD_CODE:
       return Si2183_L1_CONFIG_I2C (api, api->cmd->config_i2c.subcode, api->cmd->config_i2c.i2c_broadcast );
     break;
    #endif /*     Si2183_CONFIG_I2C_CMD */
    #ifdef        Si2183_CONFIG_PINS_CMD
     case         Si2183_CONFIG_PINS_CMD_CODE:
       return Si2183_L1_CONFIG_PINS (api, api->cmd->config_pins.gpio0_mode, api->cmd->config_pins.gpio0_read, api->cmd->config_pins.gpio1_mode, api->cmd->config_pins.gpio1_read );
     break;
    #endif /*     Si2183_CONFIG_PINS_CMD */
    #ifdef        Si2183_DD_BER_CMD
     case         Si2183_DD_BER_CMD_CODE:
       return Si2183_L1_DD_BER (api, api->cmd->dd_ber.rst );
     break;
    #endif /*     Si2183_DD_BER_CMD */
    #ifdef        Si2183_DD_CBER_CMD
     case         Si2183_DD_CBER_CMD_CODE:
       return Si2183_L1_DD_CBER (api, api->cmd->dd_cber.rst );
     break;
    #endif /*     Si2183_DD_CBER_CMD */
#ifdef    SATELLITE_FRONT_END
    #ifdef        Si2183_DD_DISEQC_SEND_CMD
     case         Si2183_DD_DISEQC_SEND_CMD_CODE:
       return Si2183_L1_DD_DISEQC_SEND (api, api->cmd->dd_diseqc_send.enable, api->cmd->dd_diseqc_send.cont_tone, api->cmd->dd_diseqc_send.tone_burst, api->cmd->dd_diseqc_send.burst_sel, api->cmd->dd_diseqc_send.end_seq, api->cmd->dd_diseqc_send.msg_length, api->cmd->dd_diseqc_send.msg_byte1, api->cmd->dd_diseqc_send.msg_byte2, api->cmd->dd_diseqc_send.msg_byte3, api->cmd->dd_diseqc_send.msg_byte4, api->cmd->dd_diseqc_send.msg_byte5, api->cmd->dd_diseqc_send.msg_byte6 );
     break;
    #endif /*     Si2183_DD_DISEQC_SEND_CMD */
    #ifdef        Si2183_DD_DISEQC_STATUS_CMD
     case         Si2183_DD_DISEQC_STATUS_CMD_CODE:
       return Si2183_L1_DD_DISEQC_STATUS (api, api->cmd->dd_diseqc_status.listen );
     break;
    #endif /*     Si2183_DD_DISEQC_STATUS_CMD */
    #ifdef        Si2183_DD_EXT_AGC_SAT_CMD
     case         Si2183_DD_EXT_AGC_SAT_CMD_CODE:
       return Si2183_L1_DD_EXT_AGC_SAT (api, api->cmd->dd_ext_agc_sat.agc_1_mode, api->cmd->dd_ext_agc_sat.agc_1_inv, api->cmd->dd_ext_agc_sat.agc_2_mode, api->cmd->dd_ext_agc_sat.agc_2_inv, api->cmd->dd_ext_agc_sat.agc_1_kloop, api->cmd->dd_ext_agc_sat.agc_2_kloop, api->cmd->dd_ext_agc_sat.agc_1_min, api->cmd->dd_ext_agc_sat.agc_2_min );
     break;
    #endif /*     Si2183_DD_EXT_AGC_SAT_CMD */
#endif /* SATELLITE_FRONT_END */

#ifdef    TERRESTRIAL_FRONT_END
    #ifdef        Si2183_DD_EXT_AGC_TER_CMD
     case         Si2183_DD_EXT_AGC_TER_CMD_CODE:
       return Si2183_L1_DD_EXT_AGC_TER (api, api->cmd->dd_ext_agc_ter.agc_1_mode, api->cmd->dd_ext_agc_ter.agc_1_inv, api->cmd->dd_ext_agc_ter.agc_2_mode, api->cmd->dd_ext_agc_ter.agc_2_inv, api->cmd->dd_ext_agc_ter.agc_1_kloop, api->cmd->dd_ext_agc_ter.agc_2_kloop, api->cmd->dd_ext_agc_ter.agc_1_min, api->cmd->dd_ext_agc_ter.agc_2_min );
     break;
    #endif /*     Si2183_DD_EXT_AGC_TER_CMD */
#endif /* TERRESTRIAL_FRONT_END */

    #ifdef        Si2183_DD_FER_CMD
     case         Si2183_DD_FER_CMD_CODE:
       return Si2183_L1_DD_FER (api, api->cmd->dd_fer.rst );
     break;
    #endif /*     Si2183_DD_FER_CMD */
    #ifdef        Si2183_DD_GET_REG_CMD
     case         Si2183_DD_GET_REG_CMD_CODE:
       return Si2183_L1_DD_GET_REG (api, api->cmd->dd_get_reg.reg_code_lsb, api->cmd->dd_get_reg.reg_code_mid, api->cmd->dd_get_reg.reg_code_msb );
     break;
    #endif /*     Si2183_DD_GET_REG_CMD */
    #ifdef        Si2183_DD_MP_DEFAULTS_CMD
     case         Si2183_DD_MP_DEFAULTS_CMD_CODE:
       return Si2183_L1_DD_MP_DEFAULTS (api, api->cmd->dd_mp_defaults.mp_a_mode, api->cmd->dd_mp_defaults.mp_b_mode, api->cmd->dd_mp_defaults.mp_c_mode, api->cmd->dd_mp_defaults.mp_d_mode );
     break;
    #endif /*     Si2183_DD_MP_DEFAULTS_CMD */
    #ifdef        Si2183_DD_PER_CMD
     case         Si2183_DD_PER_CMD_CODE:
       return Si2183_L1_DD_PER (api, api->cmd->dd_per.rst );
     break;
    #endif /*     Si2183_DD_PER_CMD */
    #ifdef        Si2183_DD_RESTART_CMD
     case         Si2183_DD_RESTART_CMD_CODE:
       return Si2183_L1_DD_RESTART (api );
     break;
    #endif /*     Si2183_DD_RESTART_CMD */
    #ifdef        Si2183_DD_RESTART_EXT_CMD
     case         Si2183_DD_RESTART_EXT_CMD_CODE:
       return Si2183_L1_DD_RESTART_EXT (api, api->cmd->dd_restart_ext.freq_plan, api->cmd->dd_restart_ext.freq_plan_ts_clk, api->cmd->dd_restart_ext.tuned_rf_freq );
     break;
    #endif /*     Si2183_DD_RESTART_EXT_CMD */
    #ifdef        Si2183_DD_SET_REG_CMD
     case         Si2183_DD_SET_REG_CMD_CODE:
       return Si2183_L1_DD_SET_REG (api, api->cmd->dd_set_reg.reg_code_lsb, api->cmd->dd_set_reg.reg_code_mid, api->cmd->dd_set_reg.reg_code_msb, api->cmd->dd_set_reg.value );
     break;
    #endif /*     Si2183_DD_SET_REG_CMD */
    #ifdef        Si2183_DD_SSI_SQI_CMD
     case         Si2183_DD_SSI_SQI_CMD_CODE:
       return Si2183_L1_DD_SSI_SQI (api, api->cmd->dd_ssi_sqi.tuner_rssi );
     break;
    #endif /*     Si2183_DD_SSI_SQI_CMD */
    #ifdef        Si2183_DD_STATUS_CMD
     case         Si2183_DD_STATUS_CMD_CODE:
       return Si2183_L1_DD_STATUS (api, api->cmd->dd_status.intack );
     break;
    #endif /*     Si2183_DD_STATUS_CMD */
    #ifdef        Si2183_DD_TS_PINS_CMD
     case         Si2183_DD_TS_PINS_CMD_CODE:
       return Si2183_L1_DD_TS_PINS (api, api->cmd->dd_ts_pins.primary_ts_mode, api->cmd->dd_ts_pins.primary_ts_activity, api->cmd->dd_ts_pins.primary_ts_dir, api->cmd->dd_ts_pins.secondary_ts_mode, api->cmd->dd_ts_pins.secondary_ts_activity, api->cmd->dd_ts_pins.secondary_ts_dir, api->cmd->dd_ts_pins.demod_role, api->cmd->dd_ts_pins.master_freq );
     break;
    #endif /*     Si2183_DD_TS_PINS_CMD */
    #ifdef        Si2183_DD_UNCOR_CMD
     case         Si2183_DD_UNCOR_CMD_CODE:
       return Si2183_L1_DD_UNCOR (api, api->cmd->dd_uncor.rst );
     break;
    #endif /*     Si2183_DD_UNCOR_CMD */
    #ifdef        Si2183_DEMOD_INFO_CMD
     case         Si2183_DEMOD_INFO_CMD_CODE:
       return Si2183_L1_DEMOD_INFO (api );
     break;
    #endif /*     Si2183_DEMOD_INFO_CMD */
    #ifdef        Si2183_DOWNLOAD_DATASET_CONTINUE_CMD
     case         Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_CODE:
       return Si2183_L1_DOWNLOAD_DATASET_CONTINUE (api, api->cmd->download_dataset_continue.data0, api->cmd->download_dataset_continue.data1, api->cmd->download_dataset_continue.data2, api->cmd->download_dataset_continue.data3, api->cmd->download_dataset_continue.data4, api->cmd->download_dataset_continue.data5, api->cmd->download_dataset_continue.data6 );
     break;
    #endif /*     Si2183_DOWNLOAD_DATASET_CONTINUE_CMD */
    #ifdef        Si2183_DOWNLOAD_DATASET_START_CMD
     case         Si2183_DOWNLOAD_DATASET_START_CMD_CODE:
       return Si2183_L1_DOWNLOAD_DATASET_START (api, api->cmd->download_dataset_start.dataset_id, api->cmd->download_dataset_start.dataset_checksum, api->cmd->download_dataset_start.data0, api->cmd->download_dataset_start.data1, api->cmd->download_dataset_start.data2, api->cmd->download_dataset_start.data3, api->cmd->download_dataset_start.data4 );
     break;
    #endif /*     Si2183_DOWNLOAD_DATASET_START_CMD */
#ifdef    DEMOD_DVB_C2
    #ifdef        Si2183_DVBC2_CTRL_CMD
     case         Si2183_DVBC2_CTRL_CMD_CODE:
       return Si2183_L1_DVBC2_CTRL (api, api->cmd->dvbc2_ctrl.action, api->cmd->dvbc2_ctrl.tuned_rf_freq );
     break;
    #endif /*     Si2183_DVBC2_CTRL_CMD */
    #ifdef        Si2183_DVBC2_DS_INFO_CMD
     case         Si2183_DVBC2_DS_INFO_CMD_CODE:
       return Si2183_L1_DVBC2_DS_INFO (api, api->cmd->dvbc2_ds_info.ds_index_or_id, api->cmd->dvbc2_ds_info.ds_select_index_or_id );
     break;
    #endif /*     Si2183_DVBC2_DS_INFO_CMD */
    #ifdef        Si2183_DVBC2_DS_PLP_SELECT_CMD
     case         Si2183_DVBC2_DS_PLP_SELECT_CMD_CODE:
       return Si2183_L1_DVBC2_DS_PLP_SELECT (api, api->cmd->dvbc2_ds_plp_select.plp_id, api->cmd->dvbc2_ds_plp_select.id_sel_mode, api->cmd->dvbc2_ds_plp_select.ds_id );
     break;
    #endif /*     Si2183_DVBC2_DS_PLP_SELECT_CMD */
    #ifdef        Si2183_DVBC2_PLP_INFO_CMD
     case         Si2183_DVBC2_PLP_INFO_CMD_CODE:
       return Si2183_L1_DVBC2_PLP_INFO (api, api->cmd->dvbc2_plp_info.plp_index, api->cmd->dvbc2_plp_info.plp_info_ds_mode, api->cmd->dvbc2_plp_info.ds_index );
     break;
    #endif /*     Si2183_DVBC2_PLP_INFO_CMD */
    #ifdef        Si2183_DVBC2_STATUS_CMD
     case         Si2183_DVBC2_STATUS_CMD_CODE:
       return Si2183_L1_DVBC2_STATUS (api, api->cmd->dvbc2_status.intack );
     break;
    #endif /*     Si2183_DVBC2_STATUS_CMD */
    #ifdef        Si2183_DVBC2_SYS_INFO_CMD
     case         Si2183_DVBC2_SYS_INFO_CMD_CODE:
       return Si2183_L1_DVBC2_SYS_INFO (api );
     break;
    #endif /*     Si2183_DVBC2_SYS_INFO_CMD */
#endif /* DEMOD_DVB_C2 */

#ifdef    DEMOD_DVB_C
    #ifdef        Si2183_DVBC_STATUS_CMD
     case         Si2183_DVBC_STATUS_CMD_CODE:
       return Si2183_L1_DVBC_STATUS (api, api->cmd->dvbc_status.intack );
     break;
    #endif /*     Si2183_DVBC_STATUS_CMD */
#endif /* DEMOD_DVB_C */

#ifdef    DEMOD_DVB_S_S2_DSS
    #ifdef        Si2183_DVBS2_PLS_INIT_CMD
     case         Si2183_DVBS2_PLS_INIT_CMD_CODE:
       return Si2183_L1_DVBS2_PLS_INIT (api, api->cmd->dvbs2_pls_init.pls_detection_mode, api->cmd->dvbs2_pls_init.pls );
     break;
    #endif /*     Si2183_DVBS2_PLS_INIT_CMD */
    #ifdef        Si2183_DVBS2_STATUS_CMD
     case         Si2183_DVBS2_STATUS_CMD_CODE:
       return Si2183_L1_DVBS2_STATUS (api, api->cmd->dvbs2_status.intack );
     break;
    #endif /*     Si2183_DVBS2_STATUS_CMD */
    #ifdef        Si2183_DVBS2_STREAM_INFO_CMD
     case         Si2183_DVBS2_STREAM_INFO_CMD_CODE:
       return Si2183_L1_DVBS2_STREAM_INFO (api, api->cmd->dvbs2_stream_info.isi_index );
     break;
    #endif /*     Si2183_DVBS2_STREAM_INFO_CMD */
    #ifdef        Si2183_DVBS2_STREAM_SELECT_CMD
     case         Si2183_DVBS2_STREAM_SELECT_CMD_CODE:
       return Si2183_L1_DVBS2_STREAM_SELECT (api, api->cmd->dvbs2_stream_select.stream_id, api->cmd->dvbs2_stream_select.stream_sel_mode );
     break;
    #endif /*     Si2183_DVBS2_STREAM_SELECT_CMD */
    #ifdef        Si2183_DVBS_STATUS_CMD
     case         Si2183_DVBS_STATUS_CMD_CODE:
       return Si2183_L1_DVBS_STATUS (api, api->cmd->dvbs_status.intack );
     break;
    #endif /*     Si2183_DVBS_STATUS_CMD */
#endif /* DEMOD_DVB_S_S2_DSS */

#ifdef    DEMOD_DVB_T2
    #ifdef        Si2183_DVBT2_FEF_CMD
     case         Si2183_DVBT2_FEF_CMD_CODE:
       return Si2183_L1_DVBT2_FEF (api, api->cmd->dvbt2_fef.fef_tuner_flag, api->cmd->dvbt2_fef.fef_tuner_flag_inv );
     break;
    #endif /*     Si2183_DVBT2_FEF_CMD */
    #ifdef        Si2183_DVBT2_PLP_INFO_CMD
     case         Si2183_DVBT2_PLP_INFO_CMD_CODE:
       return Si2183_L1_DVBT2_PLP_INFO (api, api->cmd->dvbt2_plp_info.plp_index );
     break;
    #endif /*     Si2183_DVBT2_PLP_INFO_CMD */
    #ifdef        Si2183_DVBT2_PLP_SELECT_CMD
     case         Si2183_DVBT2_PLP_SELECT_CMD_CODE:
       return Si2183_L1_DVBT2_PLP_SELECT (api, api->cmd->dvbt2_plp_select.plp_id, api->cmd->dvbt2_plp_select.plp_id_sel_mode );
     break;
    #endif /*     Si2183_DVBT2_PLP_SELECT_CMD */
    #ifdef        Si2183_DVBT2_STATUS_CMD
     case         Si2183_DVBT2_STATUS_CMD_CODE:
       return Si2183_L1_DVBT2_STATUS (api, api->cmd->dvbt2_status.intack );
     break;
    #endif /*     Si2183_DVBT2_STATUS_CMD */
    #ifdef        Si2183_DVBT2_TX_ID_CMD
     case         Si2183_DVBT2_TX_ID_CMD_CODE:
       return Si2183_L1_DVBT2_TX_ID (api );
     break;
    #endif /*     Si2183_DVBT2_TX_ID_CMD */
#endif /* DEMOD_DVB_T2 */

#ifdef    DEMOD_DVB_T
    #ifdef        Si2183_DVBT_STATUS_CMD
     case         Si2183_DVBT_STATUS_CMD_CODE:
       return Si2183_L1_DVBT_STATUS (api, api->cmd->dvbt_status.intack );
     break;
    #endif /*     Si2183_DVBT_STATUS_CMD */
    #ifdef        Si2183_DVBT_TPS_EXTRA_CMD
     case         Si2183_DVBT_TPS_EXTRA_CMD_CODE:
       return Si2183_L1_DVBT_TPS_EXTRA (api );
     break;
    #endif /*     Si2183_DVBT_TPS_EXTRA_CMD */
#endif /* DEMOD_DVB_T */

    #ifdef        Si2183_EXIT_BOOTLOADER_CMD
     case         Si2183_EXIT_BOOTLOADER_CMD_CODE:
       return Si2183_L1_EXIT_BOOTLOADER (api, api->cmd->exit_bootloader.func, api->cmd->exit_bootloader.ctsien );
     break;
    #endif /*     Si2183_EXIT_BOOTLOADER_CMD */
    #ifdef        Si2183_GET_PROPERTY_CMD
     case         Si2183_GET_PROPERTY_CMD_CODE:
       return Si2183_L1_GET_PROPERTY (api, api->cmd->get_property.reserved, api->cmd->get_property.prop );
     break;
    #endif /*     Si2183_GET_PROPERTY_CMD */
    #ifdef        Si2183_GET_REV_CMD
     case         Si2183_GET_REV_CMD_CODE:
       return Si2183_L1_GET_REV (api );
     break;
    #endif /*     Si2183_GET_REV_CMD */
    #ifdef        Si2183_I2C_PASSTHROUGH_CMD
     case         Si2183_I2C_PASSTHROUGH_CMD_CODE:
       return Si2183_L1_I2C_PASSTHROUGH (api, api->cmd->i2c_passthrough.subcode, api->cmd->i2c_passthrough.i2c_passthru, api->cmd->i2c_passthrough.reserved );
     break;
    #endif /*     Si2183_I2C_PASSTHROUGH_CMD */
#ifdef    DEMOD_ISDB_T
    #ifdef        Si2183_ISDBT_LAYER_INFO_CMD
     case         Si2183_ISDBT_LAYER_INFO_CMD_CODE:
       return Si2183_L1_ISDBT_LAYER_INFO (api, api->cmd->isdbt_layer_info.layer_index );
     break;
    #endif /*     Si2183_ISDBT_LAYER_INFO_CMD */
    #ifdef        Si2183_ISDBT_STATUS_CMD
     case         Si2183_ISDBT_STATUS_CMD_CODE:
       return Si2183_L1_ISDBT_STATUS (api, api->cmd->isdbt_status.intack );
     break;
    #endif /*     Si2183_ISDBT_STATUS_CMD */
#endif /* DEMOD_ISDB_T */

#ifdef    DEMOD_MCNS
    #ifdef        Si2183_MCNS_STATUS_CMD
     case         Si2183_MCNS_STATUS_CMD_CODE:
       return Si2183_L1_MCNS_STATUS (api, api->cmd->mcns_status.intack );
     break;
    #endif /*     Si2183_MCNS_STATUS_CMD */
#endif /* DEMOD_MCNS */

    #ifdef        Si2183_PART_INFO_CMD
     case         Si2183_PART_INFO_CMD_CODE:
       return Si2183_L1_PART_INFO (api );
     break;
    #endif /*     Si2183_PART_INFO_CMD */
    #ifdef        Si2183_POWER_DOWN_CMD
     case         Si2183_POWER_DOWN_CMD_CODE:
       return Si2183_L1_POWER_DOWN (api );
     break;
    #endif /*     Si2183_POWER_DOWN_CMD */
    #ifdef        Si2183_POWER_UP_CMD
     case         Si2183_POWER_UP_CMD_CODE:
       return Si2183_L1_POWER_UP (api, api->cmd->power_up.subcode, api->cmd->power_up.reset, api->cmd->power_up.reserved2, api->cmd->power_up.reserved4, api->cmd->power_up.reserved1, api->cmd->power_up.addr_mode, api->cmd->power_up.reserved5, api->cmd->power_up.func, api->cmd->power_up.clock_freq, api->cmd->power_up.ctsien, api->cmd->power_up.wake_up );
     break;
    #endif /*     Si2183_POWER_UP_CMD */
    #ifdef        Si2183_RSSI_ADC_CMD
     case         Si2183_RSSI_ADC_CMD_CODE:
       return Si2183_L1_RSSI_ADC (api, api->cmd->rssi_adc.on_off );
     break;
    #endif /*     Si2183_RSSI_ADC_CMD */
    #ifdef        Si2183_SCAN_CTRL_CMD
     case         Si2183_SCAN_CTRL_CMD_CODE:
       return Si2183_L1_SCAN_CTRL (api, api->cmd->scan_ctrl.action, api->cmd->scan_ctrl.tuned_rf_freq );
     break;
    #endif /*     Si2183_SCAN_CTRL_CMD */
    #ifdef        Si2183_SCAN_STATUS_CMD
     case         Si2183_SCAN_STATUS_CMD_CODE:
       return Si2183_L1_SCAN_STATUS (api, api->cmd->scan_status.intack );
     break;
    #endif /*     Si2183_SCAN_STATUS_CMD */
    #ifdef        Si2183_SET_PROPERTY_CMD
     case         Si2183_SET_PROPERTY_CMD_CODE:
       return Si2183_L1_SET_PROPERTY (api, api->cmd->set_property.reserved, api->cmd->set_property.prop, api->cmd->set_property.data );
     break;
    #endif /*     Si2183_SET_PROPERTY_CMD */
    #ifdef        Si2183_SPI_LINK_CMD
     case         Si2183_SPI_LINK_CMD_CODE:
       return Si2183_L1_SPI_LINK (api, api->cmd->spi_link.subcode, api->cmd->spi_link.spi_pbl_key, api->cmd->spi_link.spi_pbl_num, api->cmd->spi_link.spi_conf_clk, api->cmd->spi_link.spi_clk_pola, api->cmd->spi_link.spi_conf_data, api->cmd->spi_link.spi_data_dir, api->cmd->spi_link.spi_enable );
     break;
    #endif /*     Si2183_SPI_LINK_CMD */
    #ifdef        Si2183_SPI_PASSTHROUGH_CMD
     case         Si2183_SPI_PASSTHROUGH_CMD_CODE:
       return Si2183_L1_SPI_PASSTHROUGH (api, api->cmd->spi_passthrough.subcode, api->cmd->spi_passthrough.spi_passthr_clk, api->cmd->spi_passthrough.spi_passth_data );
     break;
    #endif /*     Si2183_SPI_PASSTHROUGH_CMD */
    #ifdef        Si2183_START_CLK_CMD
     case         Si2183_START_CLK_CMD_CODE:
       return Si2183_L1_START_CLK (api, api->cmd->start_clk.subcode, api->cmd->start_clk.reserved1, api->cmd->start_clk.tune_cap, api->cmd->start_clk.reserved2, api->cmd->start_clk.clk_mode, api->cmd->start_clk.reserved3, api->cmd->start_clk.reserved4, api->cmd->start_clk.start_clk );
     break;
    #endif /*     Si2183_START_CLK_CMD */
   default : break;
    }
     return 0;
  }

#ifdef    Si2183_GET_COMMAND_STRINGS

  /* --------------------------------------------*/
  /* GET_COMMAND_RESPONSE_STRING FUNCTION        */
  /* --------------------------------------------*/
unsigned char   Si2183_L1_GetCommandResponseString(L1_Si2183_Context *api, unsigned int cmd_code, const char *separator, char *msg) {
    unsigned char display_CTS;
    unsigned char display_ERR;
    unsigned char display_FIELDS;
    display_CTS = display_ERR = display_FIELDS = 0;
    /* display response fields only when CTS is 1 and ERR = 0 */
    if ( api->status->cts == 1 ) {
      if ( api->status->err == 0 ) {
        display_FIELDS++;
      } else {
      /* display ERR only when CTS is 1 and ERR = 1. */
        display_ERR++;
      }
    } else {
      /* display only CTS when CTS is 0 */
      display_CTS++;
    }
    switch (cmd_code) {
    #ifdef        Si2183_CONFIG_CLKIO_CMD
     case         Si2183_CONFIG_CLKIO_CMD_CODE:
      sprintf(msg,"CONFIG_CLKIO              ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT          ",1000);
           if  (api->rsp->config_clkio.STATUS->ddint          ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->config_clkio.STATUS->ddint          ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                             STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_clkio.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT        ",1000);
           if  (api->rsp->config_clkio.STATUS->scanint        ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->config_clkio.STATUS->scanint        ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                             STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_clkio.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR            ",1000);
           if  (api->rsp->config_clkio.STATUS->err            ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->config_clkio.STATUS->err            ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                             STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_clkio.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS            ",1000);
           if  (api->rsp->config_clkio.STATUS->cts            ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->config_clkio.STATUS->cts            ==     0) strncat(msg,"WAIT     ",1000);
      else                                                             STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_clkio.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-MODE           ",1000);
           if  (api->rsp->config_clkio.mode           ==     2) strncat(msg,"CLK_INPUT ",1000);
      else if  (api->rsp->config_clkio.mode           ==     1) strncat(msg,"CLK_OUTPUT",1000);
      else if  (api->rsp->config_clkio.mode           ==     0) strncat(msg,"UNUSED    ",1000);
      else                                                     STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_clkio.mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PRE_DRIVER_STR ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_clkio.pre_driver_str);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DRIVER_STR     ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_clkio.driver_str);
      }
     break;
    #endif /*     Si2183_CONFIG_CLKIO_CMD */

    #ifdef        Si2183_CONFIG_I2C_CMD
     case         Si2183_CONFIG_I2C_CMD_CODE:
      sprintf(msg,"CONFIG_I2C ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->config_i2c.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->config_i2c.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_i2c.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->config_i2c.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->config_i2c.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_i2c.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->config_i2c.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->config_i2c.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_i2c.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->config_i2c.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->config_i2c.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_i2c.STATUS->cts);
      }
     break;
    #endif /*     Si2183_CONFIG_I2C_CMD */

    #ifdef        Si2183_CONFIG_PINS_CMD
     case         Si2183_CONFIG_PINS_CMD_CODE:
      sprintf(msg,"CONFIG_PINS ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT       ",1000);
           if  (api->rsp->config_pins.STATUS->ddint       ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->config_pins.STATUS->ddint       ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT     ",1000);
           if  (api->rsp->config_pins.STATUS->scanint     ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->config_pins.STATUS->scanint     ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg," -ERR "        ,1000);
           if  (api->rsp->config_pins.STATUS->err         ==     1) strncat(msg,"ERROR"   ,1000);
      else if  (api->rsp->config_pins.STATUS->err         ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg," -CTS "        ,1000);
           if  (api->rsp->config_pins.STATUS->cts         ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->config_pins.STATUS->cts         ==     0) strncat(msg,"WAIT     ",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-GPIO0_MODE  ",1000);
           if  (api->rsp->config_pins.gpio0_mode  ==     1) strncat(msg,"DISABLE ",1000);
      else if  (api->rsp->config_pins.gpio0_mode  ==     2) strncat(msg,"DRIVE_0 ",1000);
      else if  (api->rsp->config_pins.gpio0_mode  ==     3) strncat(msg,"DRIVE_1 ",1000);
      else if  (api->rsp->config_pins.gpio0_mode  ==     5) strncat(msg,"FEF     ",1000);
      else if  (api->rsp->config_pins.gpio0_mode  ==     8) strncat(msg,"HW_LOCK ",1000);
      else if  (api->rsp->config_pins.gpio0_mode  ==     7) strncat(msg,"INT_FLAG",1000);
      else if  (api->rsp->config_pins.gpio0_mode  ==     4) strncat(msg,"TS_ERR  ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.gpio0_mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-GPIO0_STATE ",1000);
           if  (api->rsp->config_pins.gpio0_state ==     0) strncat(msg,"READ_0",1000);
      else if  (api->rsp->config_pins.gpio0_state ==     1) strncat(msg,"READ_1",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.gpio0_state);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-GPIO1_MODE  ",1000);
           if  (api->rsp->config_pins.gpio1_mode  ==     1) strncat(msg,"DISABLE ",1000);
      else if  (api->rsp->config_pins.gpio1_mode  ==     2) strncat(msg,"DRIVE_0 ",1000);
      else if  (api->rsp->config_pins.gpio1_mode  ==     3) strncat(msg,"DRIVE_1 ",1000);
      else if  (api->rsp->config_pins.gpio1_mode  ==     5) strncat(msg,"FEF     ",1000);
      else if  (api->rsp->config_pins.gpio1_mode  ==     8) strncat(msg,"HW_LOCK ",1000);
      else if  (api->rsp->config_pins.gpio1_mode  ==     7) strncat(msg,"INT_FLAG",1000);
      else if  (api->rsp->config_pins.gpio1_mode  ==     4) strncat(msg,"TS_ERR  ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.gpio1_mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-GPIO1_STATE ",1000);
           if  (api->rsp->config_pins.gpio1_state ==     0) strncat(msg,"READ_0",1000);
      else if  (api->rsp->config_pins.gpio1_state ==     1) strncat(msg,"READ_1",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.gpio1_state);
      }
     break;
    #endif /*     Si2183_CONFIG_PINS_CMD */

    #ifdef        Si2183_DD_BER_CMD
     case         Si2183_DD_BER_CMD_CODE:
      sprintf(msg,"DD_BER ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->dd_ber.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_ber.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ber.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->dd_ber.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_ber.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ber.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->dd_ber.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dd_ber.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ber.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->dd_ber.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dd_ber.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ber.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-EXP     ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ber.exp);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-MANT    ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ber.mant);
      }
     break;
    #endif /*     Si2183_DD_BER_CMD */

    #ifdef        Si2183_DD_CBER_CMD
     case         Si2183_DD_CBER_CMD_CODE:
      sprintf(msg,"DD_CBER ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->dd_cber.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_cber.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_cber.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->dd_cber.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_cber.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_cber.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->dd_cber.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dd_cber.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_cber.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->dd_cber.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dd_cber.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_cber.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-EXP     ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_cber.exp);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-MANT    ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_cber.mant);
      }
     break;
    #endif /*     Si2183_DD_CBER_CMD */

#ifdef    SATELLITE_FRONT_END
    #ifdef        Si2183_DD_DISEQC_SEND_CMD
     case         Si2183_DD_DISEQC_SEND_CMD_CODE:
      sprintf(msg,"DD_DISEQC_SEND ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->dd_diseqc_send.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_diseqc_send.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_diseqc_send.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->dd_diseqc_send.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_diseqc_send.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_diseqc_send.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->dd_diseqc_send.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dd_diseqc_send.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_diseqc_send.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->dd_diseqc_send.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dd_diseqc_send.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_diseqc_send.STATUS->cts);
      }
     break;
    #endif /*     Si2183_DD_DISEQC_SEND_CMD */

    #ifdef        Si2183_DD_DISEQC_STATUS_CMD
     case         Si2183_DD_DISEQC_STATUS_CMD_CODE:
      sprintf(msg,"DD_DISEQC_STATUS ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT        ",1000);
           if  (api->rsp->dd_diseqc_status.STATUS->ddint        ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_diseqc_status.STATUS->ddint        ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                               STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_diseqc_status.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT      ",1000);
           if  (api->rsp->dd_diseqc_status.STATUS->scanint      ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_diseqc_status.STATUS->scanint      ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                               STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_diseqc_status.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR          ",1000);
           if  (api->rsp->dd_diseqc_status.STATUS->err          ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dd_diseqc_status.STATUS->err          ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                               STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_diseqc_status.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS          ",1000);
           if  (api->rsp->dd_diseqc_status.STATUS->cts          ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dd_diseqc_status.STATUS->cts          ==     0) strncat(msg,"WAIT     ",1000);
      else                                                               STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_diseqc_status.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BUS_STATE    ",1000);
           if  (api->rsp->dd_diseqc_status.bus_state    ==     0) strncat(msg,"BUSY ",1000);
      else if  (api->rsp->dd_diseqc_status.bus_state    ==     1) strncat(msg,"READY",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_diseqc_status.bus_state);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY_STATUS ",1000);
           if  (api->rsp->dd_diseqc_status.reply_status ==     2) strncat(msg,"MISSING_BITS",1000);
      else if  (api->rsp->dd_diseqc_status.reply_status ==     0) strncat(msg,"NO_REPLY    ",1000);
      else if  (api->rsp->dd_diseqc_status.reply_status ==     1) strncat(msg,"PARITY_ERROR",1000);
      else if  (api->rsp->dd_diseqc_status.reply_status ==     3) strncat(msg,"REPLY_OK    ",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_diseqc_status.reply_status);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY_LENGTH ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_diseqc_status.reply_length);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY_TOGGLE ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_diseqc_status.reply_toggle);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-END_OF_REPLY ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_diseqc_status.end_of_reply);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DISEQC_MODE  ",1000);
           if  (api->rsp->dd_diseqc_status.diseqc_mode  ==     0) strncat(msg,"AUTO  ",1000);
      else if  (api->rsp->dd_diseqc_status.diseqc_mode  ==     1) strncat(msg,"LISTEN",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_diseqc_status.diseqc_mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY_BYTE1  ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_diseqc_status.reply_byte1);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY_BYTE2  ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_diseqc_status.reply_byte2);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY_BYTE3  ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_diseqc_status.reply_byte3);
      }
     break;
    #endif /*     Si2183_DD_DISEQC_STATUS_CMD */

    #ifdef        Si2183_DD_EXT_AGC_SAT_CMD
     case         Si2183_DD_EXT_AGC_SAT_CMD_CODE:
      sprintf(msg,"DD_EXT_AGC_SAT ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT       ",1000);
           if  (api->rsp->dd_ext_agc_sat.STATUS->ddint       ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_ext_agc_sat.STATUS->ddint       ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ext_agc_sat.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT     ",1000);
           if  (api->rsp->dd_ext_agc_sat.STATUS->scanint     ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_ext_agc_sat.STATUS->scanint     ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ext_agc_sat.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR         ",1000);
           if  (api->rsp->dd_ext_agc_sat.STATUS->err         ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dd_ext_agc_sat.STATUS->err         ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ext_agc_sat.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS         ",1000);
           if  (api->rsp->dd_ext_agc_sat.STATUS->cts         ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dd_ext_agc_sat.STATUS->cts         ==     0) strncat(msg,"WAIT     ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ext_agc_sat.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-AGC_1_LEVEL ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ext_agc_sat.agc_1_level);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-AGC_2_LEVEL ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ext_agc_sat.agc_2_level);
      }
     break;
    #endif /*     Si2183_DD_EXT_AGC_SAT_CMD */

#endif /* SATELLITE_FRONT_END */

#ifdef    TERRESTRIAL_FRONT_END
    #ifdef        Si2183_DD_EXT_AGC_TER_CMD
     case         Si2183_DD_EXT_AGC_TER_CMD_CODE:
      sprintf(msg,"DD_EXT_AGC_TER ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT       ",1000);
           if  (api->rsp->dd_ext_agc_ter.STATUS->ddint       ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_ext_agc_ter.STATUS->ddint       ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ext_agc_ter.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT     ",1000);
           if  (api->rsp->dd_ext_agc_ter.STATUS->scanint     ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_ext_agc_ter.STATUS->scanint     ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ext_agc_ter.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR         ",1000);
           if  (api->rsp->dd_ext_agc_ter.STATUS->err         ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dd_ext_agc_ter.STATUS->err         ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ext_agc_ter.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS         ",1000);
           if  (api->rsp->dd_ext_agc_ter.STATUS->cts         ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dd_ext_agc_ter.STATUS->cts         ==     0) strncat(msg,"WAIT     ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ext_agc_ter.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-AGC_1_LEVEL ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ext_agc_ter.agc_1_level);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-AGC_2_LEVEL ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ext_agc_ter.agc_2_level);
      }
     break;
    #endif /*     Si2183_DD_EXT_AGC_TER_CMD */

#endif /* TERRESTRIAL_FRONT_END */

    #ifdef        Si2183_DD_FER_CMD
     case         Si2183_DD_FER_CMD_CODE:
      sprintf(msg,"DD_FER ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->dd_fer.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_fer.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_fer.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->dd_fer.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_fer.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_fer.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->dd_fer.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dd_fer.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_fer.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->dd_fer.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dd_fer.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_fer.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-EXP     ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_fer.exp);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-MANT    ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_fer.mant);
      }
     break;
    #endif /*     Si2183_DD_FER_CMD */

    #ifdef        Si2183_DD_GET_REG_CMD
     case         Si2183_DD_GET_REG_CMD_CODE:
      sprintf(msg,"DD_GET_REG ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->dd_get_reg.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_get_reg.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_get_reg.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->dd_get_reg.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_get_reg.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_get_reg.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->dd_get_reg.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dd_get_reg.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_get_reg.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->dd_get_reg.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dd_get_reg.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_get_reg.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA1   ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_get_reg.data1);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA2   ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_get_reg.data2);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA3   ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_get_reg.data3);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA4   ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_get_reg.data4);
      }
     break;
    #endif /*     Si2183_DD_GET_REG_CMD */

    #ifdef        Si2183_DD_MP_DEFAULTS_CMD
     case         Si2183_DD_MP_DEFAULTS_CMD_CODE:
      sprintf(msg,"DD_MP_DEFAULTS ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT     ",1000);
           if  (api->rsp->dd_mp_defaults.STATUS->ddint     ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_mp_defaults.STATUS->ddint     ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_mp_defaults.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT   ",1000);
           if  (api->rsp->dd_mp_defaults.STATUS->scanint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_mp_defaults.STATUS->scanint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_mp_defaults.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR       ",1000);
           if  (api->rsp->dd_mp_defaults.STATUS->err       ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dd_mp_defaults.STATUS->err       ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_mp_defaults.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS       ",1000);
           if  (api->rsp->dd_mp_defaults.STATUS->cts       ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dd_mp_defaults.STATUS->cts       ==     0) strncat(msg,"WAIT     ",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_mp_defaults.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-MP_A_MODE ",1000);
           if  (api->rsp->dd_mp_defaults.mp_a_mode ==     3) strncat(msg,"AGC_1         ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_a_mode ==     4) strncat(msg,"AGC_1_INVERTED",1000);
      else if  (api->rsp->dd_mp_defaults.mp_a_mode ==     5) strncat(msg,"AGC_2         ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_a_mode ==     6) strncat(msg,"AGC_2_INVERTED",1000);
      else if  (api->rsp->dd_mp_defaults.mp_a_mode ==     0) strncat(msg,"DISABLE       ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_a_mode ==     1) strncat(msg,"DRIVE_0       ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_a_mode ==     2) strncat(msg,"DRIVE_1       ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_a_mode ==     7) strncat(msg,"FEF           ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_a_mode ==     8) strncat(msg,"FEF_INVERTED  ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_mp_defaults.mp_a_mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-MP_B_MODE ",1000);
           if  (api->rsp->dd_mp_defaults.mp_b_mode ==     3) strncat(msg,"AGC_1         ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_b_mode ==     4) strncat(msg,"AGC_1_INVERTED",1000);
      else if  (api->rsp->dd_mp_defaults.mp_b_mode ==     5) strncat(msg,"AGC_2         ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_b_mode ==     6) strncat(msg,"AGC_2_INVERTED",1000);
      else if  (api->rsp->dd_mp_defaults.mp_b_mode ==     0) strncat(msg,"DISABLE       ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_b_mode ==     1) strncat(msg,"DRIVE_0       ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_b_mode ==     2) strncat(msg,"DRIVE_1       ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_b_mode ==     7) strncat(msg,"FEF           ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_b_mode ==     8) strncat(msg,"FEF_INVERTED  ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_mp_defaults.mp_b_mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-MP_C_MODE ",1000);
           if  (api->rsp->dd_mp_defaults.mp_c_mode ==     3) strncat(msg,"AGC_1         ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_c_mode ==     4) strncat(msg,"AGC_1_INVERTED",1000);
      else if  (api->rsp->dd_mp_defaults.mp_c_mode ==     5) strncat(msg,"AGC_2         ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_c_mode ==     6) strncat(msg,"AGC_2_INVERTED",1000);
      else if  (api->rsp->dd_mp_defaults.mp_c_mode ==     0) strncat(msg,"DISABLE       ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_c_mode ==     1) strncat(msg,"DRIVE_0       ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_c_mode ==     2) strncat(msg,"DRIVE_1       ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_c_mode ==     7) strncat(msg,"FEF           ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_c_mode ==     8) strncat(msg,"FEF_INVERTED  ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_mp_defaults.mp_c_mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-MP_D_MODE ",1000);
           if  (api->rsp->dd_mp_defaults.mp_d_mode ==     3) strncat(msg,"AGC_1         ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_d_mode ==     4) strncat(msg,"AGC_1_INVERTED",1000);
      else if  (api->rsp->dd_mp_defaults.mp_d_mode ==     5) strncat(msg,"AGC_2         ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_d_mode ==     6) strncat(msg,"AGC_2_INVERTED",1000);
      else if  (api->rsp->dd_mp_defaults.mp_d_mode ==     0) strncat(msg,"DISABLE       ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_d_mode ==     1) strncat(msg,"DRIVE_0       ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_d_mode ==     2) strncat(msg,"DRIVE_1       ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_d_mode ==     7) strncat(msg,"FEF           ",1000);
      else if  (api->rsp->dd_mp_defaults.mp_d_mode ==     8) strncat(msg,"FEF_INVERTED  ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_mp_defaults.mp_d_mode);
      }
     break;
    #endif /*     Si2183_DD_MP_DEFAULTS_CMD */

    #ifdef        Si2183_DD_PER_CMD
     case         Si2183_DD_PER_CMD_CODE:
      sprintf(msg,"DD_PER ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->dd_per.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_per.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_per.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->dd_per.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_per.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_per.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->dd_per.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dd_per.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_per.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->dd_per.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dd_per.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_per.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-EXP     ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_per.exp);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-MANT    ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_per.mant);
      }
     break;
    #endif /*     Si2183_DD_PER_CMD */

    #ifdef        Si2183_DD_RESTART_CMD
     case         Si2183_DD_RESTART_CMD_CODE:
      sprintf(msg,"DD_RESTART ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->dd_restart.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_restart.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_restart.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->dd_restart.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_restart.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_restart.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->dd_restart.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dd_restart.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_restart.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->dd_restart.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dd_restart.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_restart.STATUS->cts);
      }
     break;
    #endif /*     Si2183_DD_RESTART_CMD */

    #ifdef        Si2183_DD_RESTART_EXT_CMD
     case         Si2183_DD_RESTART_EXT_CMD_CODE:
      sprintf(msg,"DD_RESTART_EXT ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->dd_restart_ext.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_restart_ext.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_restart_ext.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->dd_restart_ext.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_restart_ext.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_restart_ext.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->dd_restart_ext.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dd_restart_ext.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_restart_ext.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->dd_restart_ext.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dd_restart_ext.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_restart_ext.STATUS->cts);
      }
     break;
    #endif /*     Si2183_DD_RESTART_EXT_CMD */

    #ifdef        Si2183_DD_SET_REG_CMD
     case         Si2183_DD_SET_REG_CMD_CODE:
      sprintf(msg,"DD_SET_REG ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->dd_set_reg.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_set_reg.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_set_reg.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->dd_set_reg.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_set_reg.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_set_reg.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->dd_set_reg.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dd_set_reg.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_set_reg.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->dd_set_reg.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dd_set_reg.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_set_reg.STATUS->cts);
      }
     break;
    #endif /*     Si2183_DD_SET_REG_CMD */

    #ifdef        Si2183_DD_SSI_SQI_CMD
     case         Si2183_DD_SSI_SQI_CMD_CODE:
      sprintf(msg,"DD_SSI_SQI ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->dd_ssi_sqi.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_ssi_sqi.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ssi_sqi.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->dd_ssi_sqi.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_ssi_sqi.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ssi_sqi.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->dd_ssi_sqi.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dd_ssi_sqi.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ssi_sqi.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->dd_ssi_sqi.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dd_ssi_sqi.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ssi_sqi.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SSI     ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ssi_sqi.ssi);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SQI     ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ssi_sqi.sqi);
      }
     break;
    #endif /*     Si2183_DD_SSI_SQI_CMD */

    #ifdef        Si2183_DD_STATUS_CMD
     case         Si2183_DD_STATUS_CMD_CODE:
      sprintf(msg,"DD_STATUS ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT        ",1000);
           if  (api->rsp->dd_status.STATUS->ddint        ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_status.STATUS->ddint        ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT      ",1000);
           if  (api->rsp->dd_status.STATUS->scanint      ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_status.STATUS->scanint      ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR          ",1000);
           if  (api->rsp->dd_status.STATUS->err          ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dd_status.STATUS->err          ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS          ",1000);
           if  (api->rsp->dd_status.STATUS->cts          ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dd_status.STATUS->cts          ==     0) strncat(msg,"WAIT     ",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PCLINT       ",1000);
           if  (api->rsp->dd_status.pclint       ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dd_status.pclint       ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.pclint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DLINT        ",1000);
           if  (api->rsp->dd_status.dlint        ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dd_status.dlint        ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.dlint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BERINT       ",1000);
           if  (api->rsp->dd_status.berint       ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dd_status.berint       ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.berint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-UNCORINT     ",1000);
           if  (api->rsp->dd_status.uncorint     ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dd_status.uncorint     ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.uncorint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RSQINT_BIT5  ",1000);
           if  (api->rsp->dd_status.rsqint_bit5  ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dd_status.rsqint_bit5  ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.rsqint_bit5);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RSQINT_BIT6  ",1000);
           if  (api->rsp->dd_status.rsqint_bit6  ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dd_status.rsqint_bit6  ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.rsqint_bit6);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RSQINT_BIT7  ",1000);
           if  (api->rsp->dd_status.rsqint_bit7  ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dd_status.rsqint_bit7  ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.rsqint_bit7);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PCL          ",1000);
           if  (api->rsp->dd_status.pcl          ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->dd_status.pcl          ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.pcl);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DL           ",1000);
           if  (api->rsp->dd_status.dl           ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->dd_status.dl           ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.dl);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BER          ",1000);
           if  (api->rsp->dd_status.ber          ==     1) strncat(msg,"BER_ABOVE",1000);
      else if  (api->rsp->dd_status.ber          ==     0) strncat(msg,"BER_BELOW",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.ber);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-UNCOR        ",1000);
           if  (api->rsp->dd_status.uncor        ==     0) strncat(msg,"NO_UNCOR_FOUND",1000);
      else if  (api->rsp->dd_status.uncor        ==     1) strncat(msg,"UNCOR_FOUND   ",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.uncor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RSQSTAT_BIT5 ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.rsqstat_bit5);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RSQSTAT_BIT6 ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.rsqstat_bit6);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RSQSTAT_BIT7 ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.rsqstat_bit7);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-MODULATION   ",1000);
           if  (api->rsp->dd_status.modulation   ==    10) strncat(msg,"DSS  ",1000);
      else if  (api->rsp->dd_status.modulation   ==     3) strncat(msg,"DVBC ",1000);
      else if  (api->rsp->dd_status.modulation   ==    11) strncat(msg,"DVBC2",1000);
      else if  (api->rsp->dd_status.modulation   ==     8) strncat(msg,"DVBS ",1000);
      else if  (api->rsp->dd_status.modulation   ==     9) strncat(msg,"DVBS2",1000);
      else if  (api->rsp->dd_status.modulation   ==     2) strncat(msg,"DVBT ",1000);
      else if  (api->rsp->dd_status.modulation   ==     7) strncat(msg,"DVBT2",1000);
      else if  (api->rsp->dd_status.modulation   ==     4) strncat(msg,"ISDBT",1000);
      else if  (api->rsp->dd_status.modulation   ==     1) strncat(msg,"MCNS ",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.modulation);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TS_BIT_RATE  ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.ts_bit_rate);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TS_CLK_FREQ  ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_status.ts_clk_freq);
      }
     break;
    #endif /*     Si2183_DD_STATUS_CMD */

    #ifdef        Si2183_DD_TS_PINS_CMD
     case         Si2183_DD_TS_PINS_CMD_CODE:
      sprintf(msg,"DD_TS_PINS ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT                 ",1000);
           if  (api->rsp->dd_ts_pins.STATUS->ddint                 ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_ts_pins.STATUS->ddint                 ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ts_pins.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT               ",1000);
           if  (api->rsp->dd_ts_pins.STATUS->scanint               ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_ts_pins.STATUS->scanint               ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ts_pins.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR ",1000);
           if  (api->rsp->dd_ts_pins.STATUS->err                   ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dd_ts_pins.STATUS->err                   ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ts_pins.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS                   ",1000);
           if  (api->rsp->dd_ts_pins.STATUS->cts                   ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dd_ts_pins.STATUS->cts                   ==     0) strncat(msg,"WAIT     ",1000);
      else                                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ts_pins.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PRIMARY_TS_MODE       ",1000);
           if  (api->rsp->dd_ts_pins.primary_ts_mode       ==     1) strncat(msg,"DISABLED   ",1000);
      else if  (api->rsp->dd_ts_pins.primary_ts_mode       ==     2) strncat(msg,"DRIVING_TS1",1000);
      else if  (api->rsp->dd_ts_pins.primary_ts_mode       ==     3) strncat(msg,"DRIVING_TS2",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ts_pins.primary_ts_mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PRIMARY_TS_ACTIVITY   ",1000);
           if  (api->rsp->dd_ts_pins.primary_ts_activity   ==     3) strncat(msg,"ACTIVITY",1000);
      else if  (api->rsp->dd_ts_pins.primary_ts_activity   ==     2) strncat(msg,"CONFLICT",1000);
      else if  (api->rsp->dd_ts_pins.primary_ts_activity   ==     0) strncat(msg,"DRIVING ",1000);
      else if  (api->rsp->dd_ts_pins.primary_ts_activity   ==     1) strncat(msg,"QUIET   ",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ts_pins.primary_ts_activity);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SECONDARY_TS_MODE     ",1000);
           if  (api->rsp->dd_ts_pins.secondary_ts_mode     ==     1) strncat(msg,"DISABLED   ",1000);
      else if  (api->rsp->dd_ts_pins.secondary_ts_mode     ==     2) strncat(msg,"DRIVING_TS1",1000);
      else if  (api->rsp->dd_ts_pins.secondary_ts_mode     ==     3) strncat(msg,"DRIVING_TS2",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ts_pins.secondary_ts_mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SECONDARY_TS_ACTIVITY ",1000);
           if  (api->rsp->dd_ts_pins.secondary_ts_activity ==     3) strncat(msg,"ACTIVITY",1000);
      else if  (api->rsp->dd_ts_pins.secondary_ts_activity ==     2) strncat(msg,"CONFLICT",1000);
      else if  (api->rsp->dd_ts_pins.secondary_ts_activity ==     0) strncat(msg,"DRIVING ",1000);
      else if  (api->rsp->dd_ts_pins.secondary_ts_activity ==     1) strncat(msg,"QUIET   ",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_ts_pins.secondary_ts_activity);
      }
     break;
    #endif /*     Si2183_DD_TS_PINS_CMD */

    #ifdef        Si2183_DD_UNCOR_CMD
     case         Si2183_DD_UNCOR_CMD_CODE:
      sprintf(msg,"DD_UNCOR ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT     ",1000);
           if  (api->rsp->dd_uncor.STATUS->ddint     ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_uncor.STATUS->ddint     ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_uncor.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT   ",1000);
           if  (api->rsp->dd_uncor.STATUS->scanint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dd_uncor.STATUS->scanint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_uncor.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR       ",1000);
           if  (api->rsp->dd_uncor.STATUS->err       ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dd_uncor.STATUS->err       ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_uncor.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS       ",1000);
           if  (api->rsp->dd_uncor.STATUS->cts       ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dd_uncor.STATUS->cts       ==     0) strncat(msg,"WAIT     ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_uncor.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-UNCOR_LSB ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_uncor.uncor_lsb);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-UNCOR_MSB ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dd_uncor.uncor_msb);
      }
     break;
    #endif /*     Si2183_DD_UNCOR_CMD */

    #ifdef        Si2183_DEMOD_INFO_CMD
     case         Si2183_DEMOD_INFO_CMD_CODE:
      sprintf(msg,"DEMOD_INFO ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->demod_info.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->demod_info.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->demod_info.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->demod_info.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->demod_info.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->demod_info.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->demod_info.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->demod_info.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->demod_info.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->demod_info.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->demod_info.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->demod_info.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RESERVED ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->demod_info.reserved);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DIV_A    ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->demod_info.div_a);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DIV_B    ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->demod_info.div_b);
      }
     break;
    #endif /*     Si2183_DEMOD_INFO_CMD */

    #ifdef        Si2183_DOWNLOAD_DATASET_CONTINUE_CMD
     case         Si2183_DOWNLOAD_DATASET_CONTINUE_CMD_CODE:
      sprintf(msg,"DOWNLOAD_DATASET_CONTINUE ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->download_dataset_continue.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->download_dataset_continue.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->download_dataset_continue.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->download_dataset_continue.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->download_dataset_continue.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->download_dataset_continue.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->download_dataset_continue.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->download_dataset_continue.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->download_dataset_continue.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->download_dataset_continue.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->download_dataset_continue.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->download_dataset_continue.STATUS->cts);
      }
     break;
    #endif /*     Si2183_DOWNLOAD_DATASET_CONTINUE_CMD */

    #ifdef        Si2183_DOWNLOAD_DATASET_START_CMD
     case         Si2183_DOWNLOAD_DATASET_START_CMD_CODE:
      sprintf(msg,"DOWNLOAD_DATASET_START ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->download_dataset_start.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->download_dataset_start.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->download_dataset_start.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->download_dataset_start.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->download_dataset_start.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->download_dataset_start.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->download_dataset_start.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->download_dataset_start.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->download_dataset_start.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->download_dataset_start.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->download_dataset_start.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->download_dataset_start.STATUS->cts);
      }
     break;
    #endif /*     Si2183_DOWNLOAD_DATASET_START_CMD */

#ifdef    DEMOD_DVB_C2
    #ifdef        Si2183_DVBC2_CTRL_CMD
     case         Si2183_DVBC2_CTRL_CMD_CODE:
      sprintf(msg,"DVBC2_CTRL ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->dvbc2_ctrl.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbc2_ctrl.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_ctrl.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->dvbc2_ctrl.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbc2_ctrl.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_ctrl.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->dvbc2_ctrl.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dvbc2_ctrl.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_ctrl.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->dvbc2_ctrl.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dvbc2_ctrl.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_ctrl.STATUS->cts);
      }
     break;
    #endif /*     Si2183_DVBC2_CTRL_CMD */

    #ifdef        Si2183_DVBC2_DS_INFO_CMD
     case         Si2183_DVBC2_DS_INFO_CMD_CODE:
      sprintf(msg,"DVBC2_DS_INFO ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT              ",1000);
           if  (api->rsp->dvbc2_ds_info.STATUS->ddint              ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbc2_ds_info.STATUS->ddint              ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_ds_info.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT            ",1000);
           if  (api->rsp->dvbc2_ds_info.STATUS->scanint            ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbc2_ds_info.STATUS->scanint            ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_ds_info.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR                ",1000);
           if  (api->rsp->dvbc2_ds_info.STATUS->err                ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dvbc2_ds_info.STATUS->err                ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_ds_info.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS                ",1000);
           if  (api->rsp->dvbc2_ds_info.STATUS->cts                ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dvbc2_ds_info.STATUS->cts                ==     0) strncat(msg,"WAIT     ",1000);
      else                                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_ds_info.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DS_ID              ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_ds_info.ds_id);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DSLICE_NUM_PLP     ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_ds_info.dslice_num_plp);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RESERVED_2         ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_ds_info.reserved_2);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DSLICE_TUNE_POS_HZ ",1000); STRING_APPEND_SAFE(msg,1000,"%ld", api->rsp->dvbc2_ds_info.dslice_tune_pos_hz);
      }
     break;
    #endif /*     Si2183_DVBC2_DS_INFO_CMD */

    #ifdef        Si2183_DVBC2_DS_PLP_SELECT_CMD
     case         Si2183_DVBC2_DS_PLP_SELECT_CMD_CODE:
      sprintf(msg,"DVBC2_DS_PLP_SELECT ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->dvbc2_ds_plp_select.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbc2_ds_plp_select.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                             STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_ds_plp_select.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->dvbc2_ds_plp_select.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbc2_ds_plp_select.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                             STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_ds_plp_select.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->dvbc2_ds_plp_select.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dvbc2_ds_plp_select.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                             STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_ds_plp_select.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->dvbc2_ds_plp_select.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dvbc2_ds_plp_select.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                             STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_ds_plp_select.STATUS->cts);
      }
     break;
    #endif /*     Si2183_DVBC2_DS_PLP_SELECT_CMD */

    #ifdef        Si2183_DVBC2_PLP_INFO_CMD
     case         Si2183_DVBC2_PLP_INFO_CMD_CODE:
      sprintf(msg,"DVBC2_PLP_INFO ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT            ",1000);
           if  (api->rsp->dvbc2_plp_info.STATUS->ddint            ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbc2_plp_info.STATUS->ddint            ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_plp_info.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT          ",1000);
           if  (api->rsp->dvbc2_plp_info.STATUS->scanint          ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbc2_plp_info.STATUS->scanint          ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_plp_info.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR              ",1000);
           if  (api->rsp->dvbc2_plp_info.STATUS->err              ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dvbc2_plp_info.STATUS->err              ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_plp_info.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS              ",1000);
           if  (api->rsp->dvbc2_plp_info.STATUS->cts              ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dvbc2_plp_info.STATUS->cts              ==     0) strncat(msg,"WAIT     ",1000);
      else                                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_plp_info.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PLP_ID           ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_plp_info.plp_id);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PLP_PAYLOAD_TYPE ",1000);
           if  (api->rsp->dvbc2_plp_info.plp_payload_type ==     1) strncat(msg,"GCS ",1000);
      else if  (api->rsp->dvbc2_plp_info.plp_payload_type ==     0) strncat(msg,"GFPS",1000);
      else if  (api->rsp->dvbc2_plp_info.plp_payload_type ==     2) strncat(msg,"GSE ",1000);
      else if  (api->rsp->dvbc2_plp_info.plp_payload_type ==     3) strncat(msg,"TS  ",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_plp_info.plp_payload_type);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PLP_TYPE         ",1000);
           if  (api->rsp->dvbc2_plp_info.plp_type         ==     0) strncat(msg,"COMMON  ",1000);
      else if  (api->rsp->dvbc2_plp_info.plp_type         ==     1) strncat(msg,"GROUPED ",1000);
      else if  (api->rsp->dvbc2_plp_info.plp_type         ==     2) strncat(msg,"NORMAL  ",1000);
      else if  (api->rsp->dvbc2_plp_info.plp_type         ==     3) strncat(msg,"RESERVED",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_plp_info.plp_type);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PLP_BUNDLED      ",1000);
           if  (api->rsp->dvbc2_plp_info.plp_bundled      ==     1) strncat(msg,"BUNDLED    ",1000);
      else if  (api->rsp->dvbc2_plp_info.plp_bundled      ==     0) strncat(msg,"NOT_BUNDLED",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_plp_info.plp_bundled);
      }
     break;
    #endif /*     Si2183_DVBC2_PLP_INFO_CMD */

    #ifdef        Si2183_DVBC2_STATUS_CMD
     case         Si2183_DVBC2_STATUS_CMD_CODE:
      sprintf(msg,"DVBC2_STATUS ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT         ",1000);
           if  (api->rsp->dvbc2_status.STATUS->ddint         ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbc2_status.STATUS->ddint         ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT       ",1000);
           if  (api->rsp->dvbc2_status.STATUS->scanint       ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbc2_status.STATUS->scanint       ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR           ",1000);
           if  (api->rsp->dvbc2_status.STATUS->err           ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dvbc2_status.STATUS->err           ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS           ",1000);
           if  (api->rsp->dvbc2_status.STATUS->cts           ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dvbc2_status.STATUS->cts           ==     0) strncat(msg,"WAIT     ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PCLINT        ",1000);
           if  (api->rsp->dvbc2_status.pclint        ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbc2_status.pclint        ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.pclint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DLINT         ",1000);
           if  (api->rsp->dvbc2_status.dlint         ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbc2_status.dlint         ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.dlint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BERINT        ",1000);
           if  (api->rsp->dvbc2_status.berint        ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbc2_status.berint        ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.berint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-UNCORINT      ",1000);
           if  (api->rsp->dvbc2_status.uncorint      ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbc2_status.uncorint      ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.uncorint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-NOTDVBC2INT   ",1000);
           if  (api->rsp->dvbc2_status.notdvbc2int   ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbc2_status.notdvbc2int   ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.notdvbc2int);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REQINT        ",1000);
           if  (api->rsp->dvbc2_status.reqint        ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbc2_status.reqint        ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.reqint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-EWBSINT       ",1000);
           if  (api->rsp->dvbc2_status.ewbsint       ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbc2_status.ewbsint       ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.ewbsint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PCL           ",1000);
           if  (api->rsp->dvbc2_status.pcl           ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->dvbc2_status.pcl           ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.pcl);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DL            ",1000);
           if  (api->rsp->dvbc2_status.dl            ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->dvbc2_status.dl            ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.dl);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BER           ",1000);
           if  (api->rsp->dvbc2_status.ber           ==     1) strncat(msg,"BER_ABOVE",1000);
      else if  (api->rsp->dvbc2_status.ber           ==     0) strncat(msg,"BER_BELOW",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.ber);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-UNCOR         ",1000);
           if  (api->rsp->dvbc2_status.uncor         ==     0) strncat(msg,"NO_UNCOR_FOUND",1000);
      else if  (api->rsp->dvbc2_status.uncor         ==     1) strncat(msg,"UNCOR_FOUND   ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.uncor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-NOTDVBC2      ",1000);
           if  (api->rsp->dvbc2_status.notdvbc2      ==     0) strncat(msg,"DVBC2    ",1000);
      else if  (api->rsp->dvbc2_status.notdvbc2      ==     1) strncat(msg,"NOT_DVBC2",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.notdvbc2);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REQ           ",1000);
           if  (api->rsp->dvbc2_status.req           ==     0) strncat(msg,"NO_REQUEST",1000);
      else if  (api->rsp->dvbc2_status.req           ==     1) strncat(msg,"REQUEST   ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.req);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-EWBS          ",1000);
           if  (api->rsp->dvbc2_status.ewbs          ==     0) strncat(msg,"NORMAL ",1000);
      else if  (api->rsp->dvbc2_status.ewbs          ==     1) strncat(msg,"WARNING",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.ewbs);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CNR           ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.cnr);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-AFC_FREQ      ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.afc_freq);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TIMING_OFFSET ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.timing_offset);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DVBC2_STATUS  ",1000);
           if  (api->rsp->dvbc2_status.dvbc2_status  ==     0) strncat(msg,"IDLE        ",1000);
      else if  (api->rsp->dvbc2_status.dvbc2_status  ==     3) strncat(msg,"INVALID_DS  ",1000);
      else if  (api->rsp->dvbc2_status.dvbc2_status  ==     2) strncat(msg,"READY       ",1000);
      else if  (api->rsp->dvbc2_status.dvbc2_status  ==     1) strncat(msg,"SEARCHING   ",1000);
      else if  (api->rsp->dvbc2_status.dvbc2_status  ==     4) strncat(msg,"TUNE_REQUEST",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.dvbc2_status);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CONSTELLATION ",1000);
           if  (api->rsp->dvbc2_status.constellation ==    13) strncat(msg,"QAM1024",1000);
      else if  (api->rsp->dvbc2_status.constellation ==     7) strncat(msg,"QAM16  ",1000);
      else if  (api->rsp->dvbc2_status.constellation ==    11) strncat(msg,"QAM256 ",1000);
      else if  (api->rsp->dvbc2_status.constellation ==    15) strncat(msg,"QAM4096",1000);
      else if  (api->rsp->dvbc2_status.constellation ==     9) strncat(msg,"QAM64  ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.constellation);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SP_INV        ",1000);
           if  (api->rsp->dvbc2_status.sp_inv        ==     1) strncat(msg,"INVERTED",1000);
      else if  (api->rsp->dvbc2_status.sp_inv        ==     0) strncat(msg,"NORMAL  ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.sp_inv);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CODE_RATE     ",1000);
           if  (api->rsp->dvbc2_status.code_rate     ==     2) strncat(msg,"2_3 ",1000);
      else if  (api->rsp->dvbc2_status.code_rate     ==     3) strncat(msg,"3_4 ",1000);
      else if  (api->rsp->dvbc2_status.code_rate     ==     4) strncat(msg,"4_5 ",1000);
      else if  (api->rsp->dvbc2_status.code_rate     ==     5) strncat(msg,"5_6 ",1000);
      else if  (api->rsp->dvbc2_status.code_rate     ==     8) strncat(msg,"8_9 ",1000);
      else if  (api->rsp->dvbc2_status.code_rate     ==     9) strncat(msg,"9_10",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.code_rate);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-GUARD_INT     ",1000);
           if  (api->rsp->dvbc2_status.guard_int     ==     5) strncat(msg,"1_128",1000);
      else if  (api->rsp->dvbc2_status.guard_int     ==     0) strncat(msg,"1_64 ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.guard_int);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DS_ID         ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.ds_id);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PLP_ID        ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_status.plp_id);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RF_FREQ       ",1000); STRING_APPEND_SAFE(msg,1000,"%ld", api->rsp->dvbc2_status.rf_freq);
      }
     break;
    #endif /*     Si2183_DVBC2_STATUS_CMD */

    #ifdef        Si2183_DVBC2_SYS_INFO_CMD
     case         Si2183_DVBC2_SYS_INFO_CMD_CODE:
      sprintf(msg,"DVBC2_SYS_INFO ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT              ",1000);
           if  (api->rsp->dvbc2_sys_info.STATUS->ddint              ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbc2_sys_info.STATUS->ddint              ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_sys_info.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT            ",1000);
           if  (api->rsp->dvbc2_sys_info.STATUS->scanint            ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbc2_sys_info.STATUS->scanint            ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_sys_info.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR                ",1000);
           if  (api->rsp->dvbc2_sys_info.STATUS->err                ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dvbc2_sys_info.STATUS->err                ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_sys_info.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS                ",1000);
           if  (api->rsp->dvbc2_sys_info.STATUS->cts                ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dvbc2_sys_info.STATUS->cts                ==     0) strncat(msg,"WAIT     ",1000);
      else                                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_sys_info.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-NUM_DSLICE         ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_sys_info.num_dslice);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-NETWORK_ID         ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_sys_info.network_id);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-C2_BANDWIDTH_HZ    ",1000); STRING_APPEND_SAFE(msg,1000,"%ld", api->rsp->dvbc2_sys_info.c2_bandwidth_hz);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-START_FREQUENCY_HZ ",1000); STRING_APPEND_SAFE(msg,1000,"%ld", api->rsp->dvbc2_sys_info.start_frequency_hz);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-C2_SYSTEM_ID       ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_sys_info.c2_system_id);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RESERVED_4_LSB     ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->dvbc2_sys_info.reserved_4_lsb);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RESERVED_4_MSB     ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->dvbc2_sys_info.reserved_4_msb);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-C2_VERSION         ",1000);
           if  (api->rsp->dvbc2_sys_info.c2_version         ==     0) strncat(msg,"V1_2_1",1000);
      else if  (api->rsp->dvbc2_sys_info.c2_version         ==     1) strncat(msg,"V1_3_1",1000);
      else                                                           STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc2_sys_info.c2_version);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-EWS                ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->dvbc2_sys_info.ews);
      }
     break;
    #endif /*     Si2183_DVBC2_SYS_INFO_CMD */

#endif /* DEMOD_DVB_C2 */

#ifdef    DEMOD_DVB_C
    #ifdef        Si2183_DVBC_STATUS_CMD
     case         Si2183_DVBC_STATUS_CMD_CODE:
      sprintf(msg,"DVBC_STATUS ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT         ",1000);
           if  (api->rsp->dvbc_status.STATUS->ddint         ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbc_status.STATUS->ddint         ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                           STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc_status.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT       ",1000);
           if  (api->rsp->dvbc_status.STATUS->scanint       ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbc_status.STATUS->scanint       ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                           STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc_status.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR           ",1000);
           if  (api->rsp->dvbc_status.STATUS->err           ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dvbc_status.STATUS->err           ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                           STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc_status.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS           ",1000);
           if  (api->rsp->dvbc_status.STATUS->cts           ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dvbc_status.STATUS->cts           ==     0) strncat(msg,"WAIT     ",1000);
      else                                                           STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc_status.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PCLINT        ",1000);
           if  (api->rsp->dvbc_status.pclint        ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbc_status.pclint        ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc_status.pclint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DLINT         ",1000);
           if  (api->rsp->dvbc_status.dlint         ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbc_status.dlint         ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc_status.dlint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BERINT        ",1000);
           if  (api->rsp->dvbc_status.berint        ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbc_status.berint        ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc_status.berint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-UNCORINT      ",1000);
           if  (api->rsp->dvbc_status.uncorint      ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbc_status.uncorint      ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc_status.uncorint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-NOTDVBCINT    ",1000);
           if  (api->rsp->dvbc_status.notdvbcint    ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbc_status.notdvbcint    ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc_status.notdvbcint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PCL           ",1000);
           if  (api->rsp->dvbc_status.pcl           ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->dvbc_status.pcl           ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc_status.pcl);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DL            ",1000);
           if  (api->rsp->dvbc_status.dl            ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->dvbc_status.dl            ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc_status.dl);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BER           ",1000);
           if  (api->rsp->dvbc_status.ber           ==     1) strncat(msg,"BER_ABOVE",1000);
      else if  (api->rsp->dvbc_status.ber           ==     0) strncat(msg,"BER_BELOW",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc_status.ber);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-UNCOR         ",1000);
           if  (api->rsp->dvbc_status.uncor         ==     0) strncat(msg,"NO_UNCOR_FOUND",1000);
      else if  (api->rsp->dvbc_status.uncor         ==     1) strncat(msg,"UNCOR_FOUND   ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc_status.uncor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-NOTDVBC       ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->dvbc_status.notdvbc);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CNR           ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc_status.cnr);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-AFC_FREQ      ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc_status.afc_freq);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TIMING_OFFSET ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc_status.timing_offset);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CONSTELLATION ",1000);
           if  (api->rsp->dvbc_status.constellation ==    10) strncat(msg,"QAM128",1000);
      else if  (api->rsp->dvbc_status.constellation ==     7) strncat(msg,"QAM16 ",1000);
      else if  (api->rsp->dvbc_status.constellation ==    11) strncat(msg,"QAM256",1000);
      else if  (api->rsp->dvbc_status.constellation ==     8) strncat(msg,"QAM32 ",1000);
      else if  (api->rsp->dvbc_status.constellation ==     9) strncat(msg,"QAM64 ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc_status.constellation);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SP_INV        ",1000);
           if  (api->rsp->dvbc_status.sp_inv        ==     1) strncat(msg,"INVERTED",1000);
      else if  (api->rsp->dvbc_status.sp_inv        ==     0) strncat(msg,"NORMAL  ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbc_status.sp_inv);
      }
     break;
    #endif /*     Si2183_DVBC_STATUS_CMD */

#endif /* DEMOD_DVB_C */

#ifdef    DEMOD_DVB_S_S2_DSS
    #ifdef        Si2183_DVBS2_PLS_INIT_CMD
     case         Si2183_DVBS2_PLS_INIT_CMD_CODE:
      sprintf(msg,"DVBS2_PLS_INIT            ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg," -DDINT "  ,1000);
           if  (api->rsp->dvbs2_pls_init.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbs2_pls_init.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED"    ,1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_pls_init.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg," -SCANINT ",1000);
           if  (api->rsp->dvbs2_pls_init.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbs2_pls_init.STATUS->scanint ==     1) strncat(msg,"TRIGGERED"    ,1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_pls_init.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg," -ERR "    ,1000);
           if  (api->rsp->dvbs2_pls_init.STATUS->err     ==     1) strncat(msg,"ERROR"   ,1000);
      else if  (api->rsp->dvbs2_pls_init.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_pls_init.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg," -CTS "    ,1000);
           if  (api->rsp->dvbs2_pls_init.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dvbs2_pls_init.STATUS->cts     ==     0) strncat(msg,"WAIT"     ,1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_pls_init.STATUS->cts);
      }
     break;
    #endif /*     Si2183_DVBS2_PLS_INIT_CMD */

    #ifdef        Si2183_DVBS2_STATUS_CMD
     case         Si2183_DVBS2_STATUS_CMD_CODE:
      sprintf(msg,"DVBS2_STATUS ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT         ",1000);
           if  (api->rsp->dvbs2_status.STATUS->ddint         ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbs2_status.STATUS->ddint         ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT       ",1000);
           if  (api->rsp->dvbs2_status.STATUS->scanint       ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbs2_status.STATUS->scanint       ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR           ",1000);
           if  (api->rsp->dvbs2_status.STATUS->err           ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dvbs2_status.STATUS->err           ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS           ",1000);
           if  (api->rsp->dvbs2_status.STATUS->cts           ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dvbs2_status.STATUS->cts           ==     0) strncat(msg,"WAIT     ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PCLINT        ",1000);
           if  (api->rsp->dvbs2_status.pclint        ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbs2_status.pclint        ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.pclint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DLINT         ",1000);
           if  (api->rsp->dvbs2_status.dlint         ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbs2_status.dlint         ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.dlint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BERINT        ",1000);
           if  (api->rsp->dvbs2_status.berint        ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbs2_status.berint        ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.berint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-UNCORINT      ",1000);
           if  (api->rsp->dvbs2_status.uncorint      ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbs2_status.uncorint      ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.uncorint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PCL           ",1000);
           if  (api->rsp->dvbs2_status.pcl           ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->dvbs2_status.pcl           ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.pcl);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DL            ",1000);
           if  (api->rsp->dvbs2_status.dl            ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->dvbs2_status.dl            ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.dl);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BER           ",1000);
           if  (api->rsp->dvbs2_status.ber           ==     1) strncat(msg,"BER_ABOVE",1000);
      else if  (api->rsp->dvbs2_status.ber           ==     0) strncat(msg,"BER_BELOW",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.ber);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-UNCOR         ",1000);
           if  (api->rsp->dvbs2_status.uncor         ==     0) strncat(msg,"NO_UNCOR_FOUND",1000);
      else if  (api->rsp->dvbs2_status.uncor         ==     1) strncat(msg,"UNCOR_FOUND   ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.uncor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CNR           ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.cnr);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-AFC_FREQ      ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.afc_freq);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TIMING_OFFSET ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.timing_offset);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CONSTELLATION ",1000);
           if  (api->rsp->dvbs2_status.constellation ==    20) strncat(msg,"16APSK  ",1000);
      else if  (api->rsp->dvbs2_status.constellation ==    24) strncat(msg,"16APSK_L",1000);
      else if  (api->rsp->dvbs2_status.constellation ==    21) strncat(msg,"32APSK_1",1000);
      else if  (api->rsp->dvbs2_status.constellation ==    26) strncat(msg,"32APSK_2",1000);
      else if  (api->rsp->dvbs2_status.constellation ==    25) strncat(msg,"32APSK_L",1000);
      else if  (api->rsp->dvbs2_status.constellation ==    23) strncat(msg,"8APSK_L ",1000);
      else if  (api->rsp->dvbs2_status.constellation ==    14) strncat(msg,"8PSK    ",1000);
      else if  (api->rsp->dvbs2_status.constellation ==     3) strncat(msg,"QPSK    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.constellation);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SP_INV        ",1000);
           if  (api->rsp->dvbs2_status.sp_inv        ==     1) strncat(msg,"INVERTED",1000);
      else if  (api->rsp->dvbs2_status.sp_inv        ==     0) strncat(msg,"NORMAL  ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.sp_inv);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PILOTS        ",1000);
           if  (api->rsp->dvbs2_status.pilots        ==     0) strncat(msg,"OFF",1000);
      else if  (api->rsp->dvbs2_status.pilots        ==     1) strncat(msg,"ON ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.pilots);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CODE_RATE     ",1000);
           if  (api->rsp->dvbs2_status.code_rate     ==    27) strncat(msg,"11_15",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==    19) strncat(msg,"11_20",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==    26) strncat(msg,"13_18",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==    16) strncat(msg,"13_45",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==     1) strncat(msg,"1_2  ",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==    10) strncat(msg,"1_3  ",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==    11) strncat(msg,"1_4  ",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==    23) strncat(msg,"23_36",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==    24) strncat(msg,"25_36",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==    21) strncat(msg,"26_45",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==    22) strncat(msg,"28_45",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==     2) strncat(msg,"2_3  ",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==    12) strncat(msg,"2_5  ",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==    25) strncat(msg,"32_45",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==     3) strncat(msg,"3_4  ",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==    13) strncat(msg,"3_5  ",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==     4) strncat(msg,"4_5  ",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==     5) strncat(msg,"5_6  ",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==    20) strncat(msg,"5_9  ",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==    29) strncat(msg,"77_90",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==    28) strncat(msg,"7_9  ",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==    18) strncat(msg,"8_15 ",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==     8) strncat(msg,"8_9  ",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==     9) strncat(msg,"9_10 ",1000);
      else if  (api->rsp->dvbs2_status.code_rate     ==    17) strncat(msg,"9_20 ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.code_rate);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ROLL_OFF      ",1000);
           if  (api->rsp->dvbs2_status.roll_off      ==     6) strncat(msg,"0_05",1000);
      else if  (api->rsp->dvbs2_status.roll_off      ==     5) strncat(msg,"0_10",1000);
      else if  (api->rsp->dvbs2_status.roll_off      ==     4) strncat(msg,"0_15",1000);
      else if  (api->rsp->dvbs2_status.roll_off      ==     2) strncat(msg,"0_20",1000);
      else if  (api->rsp->dvbs2_status.roll_off      ==     1) strncat(msg,"0_25",1000);
      else if  (api->rsp->dvbs2_status.roll_off      ==     0) strncat(msg,"0_35",1000);
      else if  (api->rsp->dvbs2_status.roll_off      ==     3) strncat(msg,"N_A ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.roll_off);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CCM_VCM       ",1000);
           if  (api->rsp->dvbs2_status.ccm_vcm       ==     1) strncat(msg,"CCM",1000);
      else if  (api->rsp->dvbs2_status.ccm_vcm       ==     0) strncat(msg,"VCM",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.ccm_vcm);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SIS_MIS       ",1000);
           if  (api->rsp->dvbs2_status.sis_mis       ==     0) strncat(msg,"MIS",1000);
      else if  (api->rsp->dvbs2_status.sis_mis       ==     1) strncat(msg,"SIS",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.sis_mis);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-STREAM_TYPE   ",1000);
           if  (api->rsp->dvbs2_status.stream_type   ==     1) strncat(msg,"GCS ",1000);
      else if  (api->rsp->dvbs2_status.stream_type   ==     0) strncat(msg,"GFPS",1000);
      else if  (api->rsp->dvbs2_status.stream_type   ==     2) strncat(msg,"GSE ",1000);
      else if  (api->rsp->dvbs2_status.stream_type   ==     3) strncat(msg,"TS  ",1000);
      else if  (api->rsp->dvbs2_status.stream_type   ==     4) strncat(msg,"GSE_LITE ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_status.stream_type);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-NUM_IS        ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->dvbs2_status.num_is);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ISI_ID        ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->dvbs2_status.isi_id);
      }
     break;
    #endif /*     Si2183_DVBS2_STATUS_CMD */

    #ifdef        Si2183_DVBS2_STREAM_INFO_CMD
     case         Si2183_DVBS2_STREAM_INFO_CMD_CODE:
      sprintf(msg,"DVBS2_STREAM_INFO ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT             ",1000);
           if  (api->rsp->dvbs2_stream_info.STATUS->ddint             ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbs2_stream_info.STATUS->ddint             ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                                     STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_stream_info.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT           ",1000);
           if  (api->rsp->dvbs2_stream_info.STATUS->scanint           ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbs2_stream_info.STATUS->scanint           ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                                     STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_stream_info.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR               ",1000);
           if  (api->rsp->dvbs2_stream_info.STATUS->err               ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dvbs2_stream_info.STATUS->err               ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                                     STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_stream_info.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS               ",1000);
           if  (api->rsp->dvbs2_stream_info.STATUS->cts               ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dvbs2_stream_info.STATUS->cts               ==     0) strncat(msg,"WAIT     ",1000);
      else                                                                     STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_stream_info.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ISI_ID            ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->dvbs2_stream_info.isi_id);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ISI_CONSTELLATION ",1000);
           if  (api->rsp->dvbs2_stream_info.isi_constellation ==    20) strncat(msg,"16APSK  ",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_constellation ==    24) strncat(msg,"16APSK_L",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_constellation ==    21) strncat(msg,"32APSK_1",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_constellation ==    26) strncat(msg,"32APSK_2",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_constellation ==    25) strncat(msg,"32APSK_L",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_constellation ==    23) strncat(msg,"8APSK_L ",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_constellation ==    14) strncat(msg,"8PSK    ",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_constellation ==     3) strncat(msg,"QPSK    ",1000);
      else                                                             STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_stream_info.isi_constellation);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ISI_CODE_RATE     ",1000);
           if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==    27) strncat(msg,"11_15",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==    19) strncat(msg,"11_20",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==    26) strncat(msg,"13_18",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==    16) strncat(msg,"13_45",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==     1) strncat(msg,"1_2  ",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==    10) strncat(msg,"1_3  ",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==    11) strncat(msg,"1_4  ",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==    23) strncat(msg,"23_36",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==    24) strncat(msg,"25_36",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==    21) strncat(msg,"26_45",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==    22) strncat(msg,"28_45",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==     2) strncat(msg,"2_3  ",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==    12) strncat(msg,"2_5  ",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==    25) strncat(msg,"32_45",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==     3) strncat(msg,"3_4  ",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==    13) strncat(msg,"3_5  ",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==     4) strncat(msg,"4_5  ",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==     5) strncat(msg,"5_6  ",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==    20) strncat(msg,"5_9  ",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==    29) strncat(msg,"77_90",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==    28) strncat(msg,"7_9  ",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==    18) strncat(msg,"8_15 ",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==     8) strncat(msg,"8_9  ",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==     9) strncat(msg,"9_10 ",1000);
      else if  (api->rsp->dvbs2_stream_info.isi_code_rate     ==    17) strncat(msg,"9_20 ",1000);
      else                                                             STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_stream_info.isi_code_rate);
      }
     break;
    #endif /*     Si2183_DVBS2_STREAM_INFO_CMD */

    #ifdef        Si2183_DVBS2_STREAM_SELECT_CMD
     case         Si2183_DVBS2_STREAM_SELECT_CMD_CODE:
      sprintf(msg,"DVBS2_STREAM_SELECT ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->dvbs2_stream_select.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbs2_stream_select.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                             STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_stream_select.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->dvbs2_stream_select.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbs2_stream_select.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                             STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_stream_select.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->dvbs2_stream_select.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dvbs2_stream_select.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                             STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_stream_select.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->dvbs2_stream_select.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dvbs2_stream_select.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                             STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs2_stream_select.STATUS->cts);
      }
     break;
    #endif /*     Si2183_DVBS2_STREAM_SELECT_CMD */

    #ifdef        Si2183_DVBS_STATUS_CMD
     case         Si2183_DVBS_STATUS_CMD_CODE:
      sprintf(msg,"DVBS_STATUS ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT         ",1000);
           if  (api->rsp->dvbs_status.STATUS->ddint         ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbs_status.STATUS->ddint         ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                           STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs_status.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT       ",1000);
           if  (api->rsp->dvbs_status.STATUS->scanint       ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbs_status.STATUS->scanint       ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                           STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs_status.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR           ",1000);
           if  (api->rsp->dvbs_status.STATUS->err           ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dvbs_status.STATUS->err           ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                           STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs_status.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS           ",1000);
           if  (api->rsp->dvbs_status.STATUS->cts           ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dvbs_status.STATUS->cts           ==     0) strncat(msg,"WAIT     ",1000);
      else                                                           STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs_status.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PCLINT        ",1000);
           if  (api->rsp->dvbs_status.pclint        ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbs_status.pclint        ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs_status.pclint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DLINT         ",1000);
           if  (api->rsp->dvbs_status.dlint         ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbs_status.dlint         ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs_status.dlint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BERINT        ",1000);
           if  (api->rsp->dvbs_status.berint        ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbs_status.berint        ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs_status.berint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-UNCORINT      ",1000);
           if  (api->rsp->dvbs_status.uncorint      ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbs_status.uncorint      ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs_status.uncorint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PCL           ",1000);
           if  (api->rsp->dvbs_status.pcl           ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->dvbs_status.pcl           ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs_status.pcl);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DL            ",1000);
           if  (api->rsp->dvbs_status.dl            ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->dvbs_status.dl            ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs_status.dl);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BER           ",1000);
           if  (api->rsp->dvbs_status.ber           ==     1) strncat(msg,"BER_ABOVE",1000);
      else if  (api->rsp->dvbs_status.ber           ==     0) strncat(msg,"BER_BELOW",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs_status.ber);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-UNCOR         ",1000);
           if  (api->rsp->dvbs_status.uncor         ==     0) strncat(msg,"NO_UNCOR_FOUND",1000);
      else if  (api->rsp->dvbs_status.uncor         ==     1) strncat(msg,"UNCOR_FOUND   ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs_status.uncor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CNR           ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs_status.cnr);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-AFC_FREQ      ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs_status.afc_freq);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TIMING_OFFSET ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs_status.timing_offset);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CONSTELLATION ",1000);
           if  (api->rsp->dvbs_status.constellation ==     3) strncat(msg,"QPSK",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs_status.constellation);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SP_INV        ",1000);
           if  (api->rsp->dvbs_status.sp_inv        ==     1) strncat(msg,"INVERTED",1000);
      else if  (api->rsp->dvbs_status.sp_inv        ==     0) strncat(msg,"NORMAL  ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs_status.sp_inv);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CODE_RATE     ",1000);
           if  (api->rsp->dvbs_status.code_rate     ==     1) strncat(msg,"1_2",1000);
      else if  (api->rsp->dvbs_status.code_rate     ==     2) strncat(msg,"2_3",1000);
      else if  (api->rsp->dvbs_status.code_rate     ==     3) strncat(msg,"3_4",1000);
      else if  (api->rsp->dvbs_status.code_rate     ==     5) strncat(msg,"5_6",1000);
      else if  (api->rsp->dvbs_status.code_rate     ==     6) strncat(msg,"6_7",1000);
      else if  (api->rsp->dvbs_status.code_rate     ==     7) strncat(msg,"7_8",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbs_status.code_rate);
      }
     break;
    #endif /*     Si2183_DVBS_STATUS_CMD */

#endif /* DEMOD_DVB_S_S2_DSS */

#ifdef    DEMOD_DVB_T2
    #ifdef        Si2183_DVBT2_FEF_CMD
     case         Si2183_DVBT2_FEF_CMD_CODE:
      sprintf(msg,"DVBT2_FEF ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT          ",1000);
           if  (api->rsp->dvbt2_fef.STATUS->ddint          ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbt2_fef.STATUS->ddint          ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_fef.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT        ",1000);
           if  (api->rsp->dvbt2_fef.STATUS->scanint        ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbt2_fef.STATUS->scanint        ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_fef.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR            ",1000);
           if  (api->rsp->dvbt2_fef.STATUS->err            ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dvbt2_fef.STATUS->err            ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_fef.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS            ",1000);
           if  (api->rsp->dvbt2_fef.STATUS->cts            ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dvbt2_fef.STATUS->cts            ==     0) strncat(msg,"WAIT     ",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_fef.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-FEF_TYPE       ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_fef.fef_type);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-FEF_LENGTH     ",1000); STRING_APPEND_SAFE(msg,1000,"%ld", api->rsp->dvbt2_fef.fef_length);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-FEF_REPETITION ",1000); STRING_APPEND_SAFE(msg,1000,"%ld", api->rsp->dvbt2_fef.fef_repetition);
      }
     break;
    #endif /*     Si2183_DVBT2_FEF_CMD */

    #ifdef        Si2183_DVBT2_PLP_INFO_CMD
     case         Si2183_DVBT2_PLP_INFO_CMD_CODE:
      sprintf(msg,"DVBT2_PLP_INFO ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT                  ",1000);
           if  (api->rsp->dvbt2_plp_info.STATUS->ddint                  ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbt2_plp_info.STATUS->ddint                  ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT                ",1000);
           if  (api->rsp->dvbt2_plp_info.STATUS->scanint                ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbt2_plp_info.STATUS->scanint                ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR                    ",1000);
           if  (api->rsp->dvbt2_plp_info.STATUS->err                    ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dvbt2_plp_info.STATUS->err                    ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS                    ",1000);
           if  (api->rsp->dvbt2_plp_info.STATUS->cts                    ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dvbt2_plp_info.STATUS->cts                    ==     0) strncat(msg,"WAIT     ",1000);
      else                                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PLP_ID                 ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.plp_id);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PLP_PAYLOAD_TYPE       ",1000);
           if  (api->rsp->dvbt2_plp_info.plp_payload_type       ==     1) strncat(msg,"GCS ",1000);
      else if  (api->rsp->dvbt2_plp_info.plp_payload_type       ==     0) strncat(msg,"GFPS",1000);
      else if  (api->rsp->dvbt2_plp_info.plp_payload_type       ==     2) strncat(msg,"GSE ",1000);
      else if  (api->rsp->dvbt2_plp_info.plp_payload_type       ==     3) strncat(msg,"TS  ",1000);
      else                                                               STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.plp_payload_type);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PLP_TYPE               ",1000);
           if  (api->rsp->dvbt2_plp_info.plp_type               ==     0) strncat(msg,"COMMON    ",1000);
      else if  (api->rsp->dvbt2_plp_info.plp_type               ==     1) strncat(msg,"Data_Type1",1000);
      else if  (api->rsp->dvbt2_plp_info.plp_type               ==     2) strncat(msg,"Data_Type2",1000);
      else                                                               STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.plp_type);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-FIRST_FRAME_IDX_MSB    ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.first_frame_idx_msb);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-FIRST_RF_IDX           ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.first_rf_idx);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-FF_FLAG                ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.ff_flag);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PLP_GROUP_ID_MSB       ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.plp_group_id_msb);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-FIRST_FRAME_IDX_LSB    ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.first_frame_idx_lsb);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PLP_MOD_MSB            ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.plp_mod_msb);
           if  (api->rsp->dvbt2_plp_info.plp_mod_msb            ==     1) strncat(msg,"16QAM ",1000);
      else if  (api->rsp->dvbt2_plp_info.plp_mod_msb            ==     3) strncat(msg,"256QAM",1000);
      else if  (api->rsp->dvbt2_plp_info.plp_mod_msb            ==     2) strncat(msg,"64QAM ",1000);
      else if  (api->rsp->dvbt2_plp_info.plp_mod_msb            ==     0) strncat(msg,"QPSK  ",1000);
      else                                                               STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.plp_mod_msb);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PLP_COD                ",1000);
           if  (api->rsp->dvbt2_plp_info.plp_cod                ==     0) strncat(msg,"1_2",1000);
      else if  (api->rsp->dvbt2_plp_info.plp_cod                ==     6) strncat(msg,"1_3",1000);
      else if  (api->rsp->dvbt2_plp_info.plp_cod                ==     2) strncat(msg,"2_3",1000);
      else if  (api->rsp->dvbt2_plp_info.plp_cod                ==     7) strncat(msg,"2_5",1000);
      else if  (api->rsp->dvbt2_plp_info.plp_cod                ==     3) strncat(msg,"3_4",1000);
      else if  (api->rsp->dvbt2_plp_info.plp_cod                ==     1) strncat(msg,"3_5",1000);
      else if  (api->rsp->dvbt2_plp_info.plp_cod                ==     4) strncat(msg,"4_5",1000);
      else if  (api->rsp->dvbt2_plp_info.plp_cod                ==     5) strncat(msg,"5_6",1000);
      else                                                               STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.plp_cod);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PLP_GROUP_ID_LSB       ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.plp_group_id_lsb);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PLP_NUM_BLOCKS_MAX_MSB ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.plp_num_blocks_max_msb);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PLP_FEC_TYPE           ",1000);
           if  (api->rsp->dvbt2_plp_info.plp_fec_type           ==     0) strncat(msg,"16K_LDPC",1000);
      else if  (api->rsp->dvbt2_plp_info.plp_fec_type           ==     1) strncat(msg,"64K_LDPC",1000);
      else                                                               STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.plp_fec_type);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PLP_ROT                ",1000);
           if  (api->rsp->dvbt2_plp_info.plp_rot                ==     0) strncat(msg,"NOT_ROTATED",1000);
      else if  (api->rsp->dvbt2_plp_info.plp_rot                ==     1) strncat(msg,"ROTATED    ",1000);
      else                                                               STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.plp_rot);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PLP_MOD_LSB            ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.plp_mod_lsb);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-FRAME_INTERVAL_MSB     ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.frame_interval_msb);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PLP_NUM_BLOCKS_MAX_LSB ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.plp_num_blocks_max_lsb);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TIME_IL_LENGTH_MSB     ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.time_il_length_msb);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-FRAME_INTERVAL_LSB     ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.frame_interval_lsb);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TIME_IL_TYPE           ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.time_il_type);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TIME_IL_LENGTH_LSB     ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.time_il_length_lsb);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RESERVED_1_1           ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.reserved_1_1);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-IN_BAND_B_FLAG         ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.in_band_b_flag);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-IN_BAND_A_FLAG         ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.in_band_a_flag);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-STATIC_FLAG            ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.static_flag);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PLP_MODE               ",1000);
           if  (api->rsp->dvbt2_plp_info.plp_mode               ==     2) strncat(msg,"HIGH_EFFICIENCY_MODE",1000);
      else if  (api->rsp->dvbt2_plp_info.plp_mode               ==     1) strncat(msg,"NORMAL_MODE         ",1000);
      else if  (api->rsp->dvbt2_plp_info.plp_mode               ==     0) strncat(msg,"NOT_SPECIFIED       ",1000);
      else if  (api->rsp->dvbt2_plp_info.plp_mode               ==     3) strncat(msg,"RESERVED            ",1000);
      else                                                               STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.plp_mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RESERVED_1_2           ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.reserved_1_2);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-STATIC_PADDING_FLAG    ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_info.static_padding_flag);
      }
     break;
    #endif /*     Si2183_DVBT2_PLP_INFO_CMD */

    #ifdef        Si2183_DVBT2_PLP_SELECT_CMD
     case         Si2183_DVBT2_PLP_SELECT_CMD_CODE:
      sprintf(msg,"DVBT2_PLP_SELECT ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->dvbt2_plp_select.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbt2_plp_select.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_select.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->dvbt2_plp_select.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbt2_plp_select.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_select.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->dvbt2_plp_select.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dvbt2_plp_select.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_select.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->dvbt2_plp_select.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dvbt2_plp_select.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                          STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_plp_select.STATUS->cts);
      }
     break;
    #endif /*     Si2183_DVBT2_PLP_SELECT_CMD */

    #ifdef        Si2183_DVBT2_STATUS_CMD
     case         Si2183_DVBT2_STATUS_CMD_CODE:
      sprintf(msg,"DVBT2_STATUS ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT         ",1000);
           if  (api->rsp->dvbt2_status.STATUS->ddint         ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbt2_status.STATUS->ddint         ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT       ",1000);
           if  (api->rsp->dvbt2_status.STATUS->scanint       ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbt2_status.STATUS->scanint       ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR           ",1000);
           if  (api->rsp->dvbt2_status.STATUS->err           ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dvbt2_status.STATUS->err           ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS           ",1000);
           if  (api->rsp->dvbt2_status.STATUS->cts           ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dvbt2_status.STATUS->cts           ==     0) strncat(msg,"WAIT     ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PCLINT        ",1000);
           if  (api->rsp->dvbt2_status.pclint        ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbt2_status.pclint        ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.pclint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DLINT         ",1000);
           if  (api->rsp->dvbt2_status.dlint         ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbt2_status.dlint         ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.dlint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BERINT        ",1000);
           if  (api->rsp->dvbt2_status.berint        ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbt2_status.berint        ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.berint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-UNCORINT      ",1000);
           if  (api->rsp->dvbt2_status.uncorint      ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbt2_status.uncorint      ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.uncorint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-NOTDVBT2INT   ",1000);
           if  (api->rsp->dvbt2_status.notdvbt2int   ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbt2_status.notdvbt2int   ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.notdvbt2int);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PCL           ",1000);
           if  (api->rsp->dvbt2_status.pcl           ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->dvbt2_status.pcl           ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.pcl);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DL            ",1000);
           if  (api->rsp->dvbt2_status.dl            ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->dvbt2_status.dl            ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.dl);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BER           ",1000);
           if  (api->rsp->dvbt2_status.ber           ==     1) strncat(msg,"BER_ABOVE",1000);
      else if  (api->rsp->dvbt2_status.ber           ==     0) strncat(msg,"BER_BELOW",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.ber);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-UNCOR         ",1000);
           if  (api->rsp->dvbt2_status.uncor         ==     0) strncat(msg,"NO_UNCOR_FOUND",1000);
      else if  (api->rsp->dvbt2_status.uncor         ==     1) strncat(msg,"UNCOR_FOUND   ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.uncor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-NOTDVBT2      ",1000);
           if  (api->rsp->dvbt2_status.notdvbt2      ==     0) strncat(msg,"DVBT2    ",1000);
      else if  (api->rsp->dvbt2_status.notdvbt2      ==     1) strncat(msg,"NOT_DVBT2",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.notdvbt2);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CNR           ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.cnr);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-AFC_FREQ      ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.afc_freq);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TIMING_OFFSET ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.timing_offset);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CONSTELLATION ",1000);
           if  (api->rsp->dvbt2_status.constellation ==    10) strncat(msg,"QAM128",1000);
      else if  (api->rsp->dvbt2_status.constellation ==     7) strncat(msg,"QAM16 ",1000);
      else if  (api->rsp->dvbt2_status.constellation ==    11) strncat(msg,"QAM256",1000);
      else if  (api->rsp->dvbt2_status.constellation ==     8) strncat(msg,"QAM32 ",1000);
      else if  (api->rsp->dvbt2_status.constellation ==     9) strncat(msg,"QAM64 ",1000);
      else if  (api->rsp->dvbt2_status.constellation ==     3) strncat(msg,"QPSK  ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.constellation);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SP_INV        ",1000);
           if  (api->rsp->dvbt2_status.sp_inv        ==     1) strncat(msg,"INVERTED",1000);
      else if  (api->rsp->dvbt2_status.sp_inv        ==     0) strncat(msg,"NORMAL  ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.sp_inv);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-FEF           ",1000);
           if  (api->rsp->dvbt2_status.fef           ==     1) strncat(msg,"FEF   ",1000);
      else if  (api->rsp->dvbt2_status.fef           ==     0) strncat(msg,"NO_FEF",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.fef);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-FFT_MODE      ",1000);
           if  (api->rsp->dvbt2_status.fft_mode      ==    14) strncat(msg,"16K",1000);
      else if  (api->rsp->dvbt2_status.fft_mode      ==    10) strncat(msg,"1K ",1000);
      else if  (api->rsp->dvbt2_status.fft_mode      ==    11) strncat(msg,"2K ",1000);
      else if  (api->rsp->dvbt2_status.fft_mode      ==    15) strncat(msg,"32K",1000);
      else if  (api->rsp->dvbt2_status.fft_mode      ==    12) strncat(msg,"4K ",1000);
      else if  (api->rsp->dvbt2_status.fft_mode      ==    13) strncat(msg,"8K ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.fft_mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-GUARD_INT     ",1000);
           if  (api->rsp->dvbt2_status.guard_int     ==     6) strncat(msg,"19_128",1000);
      else if  (api->rsp->dvbt2_status.guard_int     ==     7) strncat(msg,"19_256",1000);
      else if  (api->rsp->dvbt2_status.guard_int     ==     5) strncat(msg,"1_128 ",1000);
      else if  (api->rsp->dvbt2_status.guard_int     ==     2) strncat(msg,"1_16  ",1000);
      else if  (api->rsp->dvbt2_status.guard_int     ==     1) strncat(msg,"1_32  ",1000);
      else if  (api->rsp->dvbt2_status.guard_int     ==     4) strncat(msg,"1_4   ",1000);
      else if  (api->rsp->dvbt2_status.guard_int     ==     3) strncat(msg,"1_8   ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.guard_int);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BW_EXT        ",1000);
           if  (api->rsp->dvbt2_status.bw_ext        ==     1) strncat(msg,"EXTENDED",1000);
      else if  (api->rsp->dvbt2_status.bw_ext        ==     0) strncat(msg,"NORMAL  ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.bw_ext);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-NUM_PLP       ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.num_plp);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PILOT_PATTERN ",1000);
           if  (api->rsp->dvbt2_status.pilot_pattern ==     0) strncat(msg,"PP1",1000);
      else if  (api->rsp->dvbt2_status.pilot_pattern ==     1) strncat(msg,"PP2",1000);
      else if  (api->rsp->dvbt2_status.pilot_pattern ==     2) strncat(msg,"PP3",1000);
      else if  (api->rsp->dvbt2_status.pilot_pattern ==     3) strncat(msg,"PP4",1000);
      else if  (api->rsp->dvbt2_status.pilot_pattern ==     4) strncat(msg,"PP5",1000);
      else if  (api->rsp->dvbt2_status.pilot_pattern ==     5) strncat(msg,"PP6",1000);
      else if  (api->rsp->dvbt2_status.pilot_pattern ==     6) strncat(msg,"PP7",1000);
      else if  (api->rsp->dvbt2_status.pilot_pattern ==     7) strncat(msg,"PP8",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.pilot_pattern);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TX_MODE       ",1000);
           if  (api->rsp->dvbt2_status.tx_mode       ==     1) strncat(msg,"MISO",1000);
      else if  (api->rsp->dvbt2_status.tx_mode       ==     0) strncat(msg,"SISO",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.tx_mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ROTATED       ",1000);
           if  (api->rsp->dvbt2_status.rotated       ==     0) strncat(msg,"NORMAL ",1000);
      else if  (api->rsp->dvbt2_status.rotated       ==     1) strncat(msg,"ROTATED",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.rotated);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SHORT_FRAME   ",1000);
           if  (api->rsp->dvbt2_status.short_frame   ==     0) strncat(msg,"16K_LDPC",1000);
      else if  (api->rsp->dvbt2_status.short_frame   ==     1) strncat(msg,"64K_LDPC",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.short_frame);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-T2_MODE       ",1000);
           if  (api->rsp->dvbt2_status.t2_mode       ==     0) strncat(msg,"BASE",1000);
      else if  (api->rsp->dvbt2_status.t2_mode       ==     1) strncat(msg,"LITE",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.t2_mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CODE_RATE     ",1000);
           if  (api->rsp->dvbt2_status.code_rate     ==     1) strncat(msg,"1_2",1000);
      else if  (api->rsp->dvbt2_status.code_rate     ==    10) strncat(msg,"1_3",1000);
      else if  (api->rsp->dvbt2_status.code_rate     ==     2) strncat(msg,"2_3",1000);
      else if  (api->rsp->dvbt2_status.code_rate     ==    12) strncat(msg,"2_5",1000);
      else if  (api->rsp->dvbt2_status.code_rate     ==     3) strncat(msg,"3_4",1000);
      else if  (api->rsp->dvbt2_status.code_rate     ==    13) strncat(msg,"3_5",1000);
      else if  (api->rsp->dvbt2_status.code_rate     ==     4) strncat(msg,"4_5",1000);
      else if  (api->rsp->dvbt2_status.code_rate     ==     5) strncat(msg,"5_6",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.code_rate);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-T2_VERSION    ",1000);
           if  (api->rsp->dvbt2_status.t2_version    ==     0) strncat(msg,"1_1_1",1000);
      else if  (api->rsp->dvbt2_status.t2_version    ==     1) strncat(msg,"1_2_1",1000);
      else if  (api->rsp->dvbt2_status.t2_version    ==     2) strncat(msg,"1_3_1",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.t2_version);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PLP_ID        ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.plp_id);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-STREAM_TYPE   ",1000);
           if  (api->rsp->dvbt2_status.stream_type   ==     1) strncat(msg,"GCS ",1000);
      else if  (api->rsp->dvbt2_status.stream_type   ==     0) strncat(msg,"GFPS",1000);
      else if  (api->rsp->dvbt2_status.stream_type   ==     2) strncat(msg,"GSE ",1000);
      else if  (api->rsp->dvbt2_status.stream_type   ==     3) strncat(msg,"TS  ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_status.stream_type);
      }
     break;
    #endif /*     Si2183_DVBT2_STATUS_CMD */

    #ifdef        Si2183_DVBT2_TX_ID_CMD
     case         Si2183_DVBT2_TX_ID_CMD_CODE:
      sprintf(msg,"DVBT2_TX_ID ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT              ",1000);
           if  (api->rsp->dvbt2_tx_id.STATUS->ddint              ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbt2_tx_id.STATUS->ddint              ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_tx_id.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT            ",1000);
           if  (api->rsp->dvbt2_tx_id.STATUS->scanint            ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbt2_tx_id.STATUS->scanint            ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_tx_id.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR                ",1000);
           if  (api->rsp->dvbt2_tx_id.STATUS->err                ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dvbt2_tx_id.STATUS->err                ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_tx_id.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS                ",1000);
           if  (api->rsp->dvbt2_tx_id.STATUS->cts                ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dvbt2_tx_id.STATUS->cts                ==     0) strncat(msg,"WAIT     ",1000);
      else                                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_tx_id.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TX_ID_AVAILABILITY ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_tx_id.tx_id_availability);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CELL_ID            ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_tx_id.cell_id);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-NETWORK_ID         ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_tx_id.network_id);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-T2_SYSTEM_ID       ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt2_tx_id.t2_system_id);
      }
     break;
    #endif /*     Si2183_DVBT2_TX_ID_CMD */

#endif /* DEMOD_DVB_T2 */

#ifdef    DEMOD_DVB_T
    #ifdef        Si2183_DVBT_STATUS_CMD
     case         Si2183_DVBT_STATUS_CMD_CODE:
      sprintf(msg,"DVBT_STATUS ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT         ",1000);
           if  (api->rsp->dvbt_status.STATUS->ddint         ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbt_status.STATUS->ddint         ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                           STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT       ",1000);
           if  (api->rsp->dvbt_status.STATUS->scanint       ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbt_status.STATUS->scanint       ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                           STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR           ",1000);
           if  (api->rsp->dvbt_status.STATUS->err           ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dvbt_status.STATUS->err           ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                           STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS           ",1000);
           if  (api->rsp->dvbt_status.STATUS->cts           ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dvbt_status.STATUS->cts           ==     0) strncat(msg,"WAIT     ",1000);
      else                                                           STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PCLINT        ",1000);
           if  (api->rsp->dvbt_status.pclint        ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbt_status.pclint        ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.pclint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DLINT         ",1000);
           if  (api->rsp->dvbt_status.dlint         ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbt_status.dlint         ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.dlint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BERINT        ",1000);
           if  (api->rsp->dvbt_status.berint        ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbt_status.berint        ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.berint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-UNCORINT      ",1000);
           if  (api->rsp->dvbt_status.uncorint      ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbt_status.uncorint      ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.uncorint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-NOTDVBTINT    ",1000);
           if  (api->rsp->dvbt_status.notdvbtint    ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->dvbt_status.notdvbtint    ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.notdvbtint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PCL           ",1000);
           if  (api->rsp->dvbt_status.pcl           ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->dvbt_status.pcl           ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.pcl);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DL            ",1000);
           if  (api->rsp->dvbt_status.dl            ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->dvbt_status.dl            ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.dl);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BER           ",1000);
           if  (api->rsp->dvbt_status.ber           ==     1) strncat(msg,"BER_ABOVE",1000);
      else if  (api->rsp->dvbt_status.ber           ==     0) strncat(msg,"BER_BELOW",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.ber);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-UNCOR         ",1000);
           if  (api->rsp->dvbt_status.uncor         ==     0) strncat(msg,"NO_UNCOR_FOUND",1000);
      else if  (api->rsp->dvbt_status.uncor         ==     1) strncat(msg,"UNCOR_FOUND   ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.uncor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-NOTDVBT       ",1000);
           if  (api->rsp->dvbt_status.notdvbt       ==     0) strncat(msg,"DVBT    ",1000);
      else if  (api->rsp->dvbt_status.notdvbt       ==     1) strncat(msg,"NOT_DVBT",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.notdvbt);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CNR           ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.cnr);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-AFC_FREQ      ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.afc_freq);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TIMING_OFFSET ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.timing_offset);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CONSTELLATION ",1000);
           if  (api->rsp->dvbt_status.constellation ==     7) strncat(msg,"QAM16",1000);
      else if  (api->rsp->dvbt_status.constellation ==     9) strncat(msg,"QAM64",1000);
      else if  (api->rsp->dvbt_status.constellation ==     3) strncat(msg,"QPSK ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.constellation);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SP_INV        ",1000);
           if  (api->rsp->dvbt_status.sp_inv        ==     1) strncat(msg,"INVERTED",1000);
      else if  (api->rsp->dvbt_status.sp_inv        ==     0) strncat(msg,"NORMAL  ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.sp_inv);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RATE_HP       ",1000);
           if  (api->rsp->dvbt_status.rate_hp       ==     1) strncat(msg,"1_2",1000);
      else if  (api->rsp->dvbt_status.rate_hp       ==     2) strncat(msg,"2_3",1000);
      else if  (api->rsp->dvbt_status.rate_hp       ==     3) strncat(msg,"3_4",1000);
      else if  (api->rsp->dvbt_status.rate_hp       ==     5) strncat(msg,"5_6",1000);
      else if  (api->rsp->dvbt_status.rate_hp       ==     7) strncat(msg,"7_8",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.rate_hp);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RATE_LP       ",1000);
           if  (api->rsp->dvbt_status.rate_lp       ==     1) strncat(msg,"1_2",1000);
      else if  (api->rsp->dvbt_status.rate_lp       ==     2) strncat(msg,"2_3",1000);
      else if  (api->rsp->dvbt_status.rate_lp       ==     3) strncat(msg,"3_4",1000);
      else if  (api->rsp->dvbt_status.rate_lp       ==     5) strncat(msg,"5_6",1000);
      else if  (api->rsp->dvbt_status.rate_lp       ==     7) strncat(msg,"7_8",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.rate_lp);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-FFT_MODE      ",1000);
           if  (api->rsp->dvbt_status.fft_mode      ==    11) strncat(msg,"2K",1000);
      else if  (api->rsp->dvbt_status.fft_mode      ==    12) strncat(msg,"4K",1000);
      else if  (api->rsp->dvbt_status.fft_mode      ==    13) strncat(msg,"8K",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.fft_mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-GUARD_INT     ",1000);
           if  (api->rsp->dvbt_status.guard_int     ==     2) strncat(msg,"1_16",1000);
      else if  (api->rsp->dvbt_status.guard_int     ==     1) strncat(msg,"1_32",1000);
      else if  (api->rsp->dvbt_status.guard_int     ==     4) strncat(msg,"1_4 ",1000);
      else if  (api->rsp->dvbt_status.guard_int     ==     3) strncat(msg,"1_8 ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.guard_int);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-HIERARCHY     ",1000);
           if  (api->rsp->dvbt_status.hierarchy     ==     2) strncat(msg,"ALFA1",1000);
      else if  (api->rsp->dvbt_status.hierarchy     ==     3) strncat(msg,"ALFA2",1000);
      else if  (api->rsp->dvbt_status.hierarchy     ==     5) strncat(msg,"ALFA4",1000);
      else if  (api->rsp->dvbt_status.hierarchy     ==     1) strncat(msg,"NONE ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.hierarchy);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TPS_LENGTH    ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_status.tps_length);
      }
     break;
    #endif /*     Si2183_DVBT_STATUS_CMD */

    #ifdef        Si2183_DVBT_TPS_EXTRA_CMD
     case         Si2183_DVBT_TPS_EXTRA_CMD_CODE:
      sprintf(msg,"DVBT_TPS_EXTRA ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT       ",1000);
           if  (api->rsp->dvbt_tps_extra.STATUS->ddint       ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbt_tps_extra.STATUS->ddint       ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_tps_extra.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT     ",1000);
           if  (api->rsp->dvbt_tps_extra.STATUS->scanint     ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->dvbt_tps_extra.STATUS->scanint     ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_tps_extra.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR         ",1000);
           if  (api->rsp->dvbt_tps_extra.STATUS->err         ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->dvbt_tps_extra.STATUS->err         ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_tps_extra.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS         ",1000);
           if  (api->rsp->dvbt_tps_extra.STATUS->cts         ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->dvbt_tps_extra.STATUS->cts         ==     0) strncat(msg,"WAIT     ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_tps_extra.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-LPTIMESLICE ",1000);
           if  (api->rsp->dvbt_tps_extra.lptimeslice ==     0) strncat(msg,"off",1000);
      else if  (api->rsp->dvbt_tps_extra.lptimeslice ==     1) strncat(msg,"on ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_tps_extra.lptimeslice);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-HPTIMESLICE ",1000);
           if  (api->rsp->dvbt_tps_extra.hptimeslice ==     0) strncat(msg,"off",1000);
      else if  (api->rsp->dvbt_tps_extra.hptimeslice ==     1) strncat(msg,"on ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_tps_extra.hptimeslice);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-LPMPEFEC    ",1000);
           if  (api->rsp->dvbt_tps_extra.lpmpefec    ==     0) strncat(msg,"off",1000);
      else if  (api->rsp->dvbt_tps_extra.lpmpefec    ==     1) strncat(msg,"on ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_tps_extra.lpmpefec);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-HPMPEFEC    ",1000);
           if  (api->rsp->dvbt_tps_extra.hpmpefec    ==     0) strncat(msg,"off",1000);
      else if  (api->rsp->dvbt_tps_extra.hpmpefec    ==     1) strncat(msg,"on ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_tps_extra.hpmpefec);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DVBHINTER   ",1000);
           if  (api->rsp->dvbt_tps_extra.dvbhinter   ==     1) strncat(msg,"in_depth",1000);
      else if  (api->rsp->dvbt_tps_extra.dvbhinter   ==     0) strncat(msg,"native  ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_tps_extra.dvbhinter);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CELL_ID     ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_tps_extra.cell_id);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TPS_RES1    ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_tps_extra.tps_res1);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TPS_RES2    ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_tps_extra.tps_res2);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TPS_RES3    ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_tps_extra.tps_res3);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TPS_RES4    ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->dvbt_tps_extra.tps_res4);
      }
     break;
    #endif /*     Si2183_DVBT_TPS_EXTRA_CMD */

#endif /* DEMOD_DVB_T */

    #ifdef        Si2183_EXIT_BOOTLOADER_CMD
     case         Si2183_EXIT_BOOTLOADER_CMD_CODE:
      sprintf(msg,"EXIT_BOOTLOADER ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->exit_bootloader.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->exit_bootloader.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->exit_bootloader.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->exit_bootloader.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->exit_bootloader.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->exit_bootloader.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->exit_bootloader.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->exit_bootloader.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->exit_bootloader.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->exit_bootloader.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->exit_bootloader.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->exit_bootloader.STATUS->cts);
      }
     break;
    #endif /*     Si2183_EXIT_BOOTLOADER_CMD */

    #ifdef        Si2183_GET_PROPERTY_CMD
     case         Si2183_GET_PROPERTY_CMD_CODE:
      sprintf(msg,"GET_PROPERTY ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT    ",1000);
           if  (api->rsp->get_property.STATUS->ddint    ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->get_property.STATUS->ddint    ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_property.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT  ",1000);
           if  (api->rsp->get_property.STATUS->scanint  ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->get_property.STATUS->scanint  ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_property.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR      ",1000);
           if  (api->rsp->get_property.STATUS->err      ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->get_property.STATUS->err      ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_property.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS      ",1000);
           if  (api->rsp->get_property.STATUS->cts      ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->get_property.STATUS->cts      ==     0) strncat(msg,"WAIT     ",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_property.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RESERVED ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_property.reserved);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA     ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_property.data);
      }
     break;
    #endif /*     Si2183_GET_PROPERTY_CMD */

    #ifdef        Si2183_GET_REV_CMD
     case         Si2183_GET_REV_CMD_CODE:
      sprintf(msg,"GET_REV ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT    ",1000);
           if  (api->rsp->get_rev.STATUS->ddint    ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->get_rev.STATUS->ddint    ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_rev.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT  ",1000);
           if  (api->rsp->get_rev.STATUS->scanint  ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->get_rev.STATUS->scanint  ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_rev.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR      ",1000);
           if  (api->rsp->get_rev.STATUS->err      ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->get_rev.STATUS->err      ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_rev.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS      ",1000);
           if  (api->rsp->get_rev.STATUS->cts      ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->get_rev.STATUS->cts      ==     0) strncat(msg,"WAIT     ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_rev.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PN       ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_rev.pn);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-FWMAJOR  ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_rev.fwmajor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-FWMINOR  ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_rev.fwminor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PATCH    ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_rev.patch);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CMPMAJOR ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_rev.cmpmajor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CMPMINOR ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_rev.cmpminor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CMPBUILD ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_rev.cmpbuild);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CHIPREV  ",1000);
           if  (api->rsp->get_rev.chiprev  ==     1) strncat(msg,"A",1000);
      else if  (api->rsp->get_rev.chiprev  ==     2) strncat(msg,"B",1000);
      else if  (api->rsp->get_rev.chiprev  ==     3) strncat(msg,"C",1000);
      else if  (api->rsp->get_rev.chiprev  ==     4) strncat(msg,"D",1000);
      else if  (api->rsp->get_rev.chiprev  ==     5) strncat(msg,"E",1000);
      else                                          STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_rev.chiprev);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-MCM_DIE  ",1000);
           if  (api->rsp->get_rev.mcm_die  ==     1) strncat(msg,"DIE_A ",1000);
      else if  (api->rsp->get_rev.mcm_die  ==     2) strncat(msg,"DIE_B ",1000);
      else if  (api->rsp->get_rev.mcm_die  ==     0) strncat(msg,"SINGLE",1000);
      else                                          STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_rev.mcm_die);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RX       ",1000);
           if  (api->rsp->get_rev.rx       ==     1) strncat(msg,"RX        ",1000);
      else if  (api->rsp->get_rev.rx       ==     0) strncat(msg,"STANDALONE",1000);
      else                                          STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_rev.rx);
      }
     break;
    #endif /*     Si2183_GET_REV_CMD */

    #ifdef        Si2183_I2C_PASSTHROUGH_CMD
     case         Si2183_I2C_PASSTHROUGH_CMD_CODE:
      sprintf(msg,"I2C_PASSTHROUGH ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->i2c_passthrough.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->i2c_passthrough.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->i2c_passthrough.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->i2c_passthrough.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->i2c_passthrough.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->i2c_passthrough.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->i2c_passthrough.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->i2c_passthrough.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->i2c_passthrough.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->i2c_passthrough.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->i2c_passthrough.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->i2c_passthrough.STATUS->cts);
      }
     break;
    #endif /*     Si2183_I2C_PASSTHROUGH_CMD */

#ifdef    DEMOD_ISDB_T
    #ifdef        Si2183_ISDBT_AC_BITS_CMD
     case         Si2183_ISDBT_AC_BITS_CMD_CODE:
      sprintf(msg,"ISDBT_AC_BITS ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->isdbt_ac_bits.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->isdbt_ac_bits.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_ac_bits.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->isdbt_ac_bits.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->isdbt_ac_bits.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_ac_bits.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->isdbt_ac_bits.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->isdbt_ac_bits.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_ac_bits.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->isdbt_ac_bits.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->isdbt_ac_bits.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_ac_bits.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA1   ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->isdbt_ac_bits.data1);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA2   ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->isdbt_ac_bits.data2);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA3   ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->isdbt_ac_bits.data3);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA4   ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->isdbt_ac_bits.data4);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA5   ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->isdbt_ac_bits.data5);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA6   ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->isdbt_ac_bits.data6);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA7   ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->isdbt_ac_bits.data7);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA8   ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->isdbt_ac_bits.data8);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA9   ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->isdbt_ac_bits.data9);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA10  ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->isdbt_ac_bits.data10);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA11  ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->isdbt_ac_bits.data11);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA12  ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->isdbt_ac_bits.data12);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA13  ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->isdbt_ac_bits.data13);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA14  ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->isdbt_ac_bits.data14);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA15  ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->isdbt_ac_bits.data15);
      }
     break;
    #endif /*     Si2183_ISDBT_AC_BITS_CMD */

    #ifdef        Si2183_ISDBT_LAYER_INFO_CMD
     case         Si2183_ISDBT_LAYER_INFO_CMD_CODE:
      sprintf(msg,"ISDBT_LAYER_INFO ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT         ",1000);
           if  (api->rsp->isdbt_layer_info.STATUS->ddint         ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->isdbt_layer_info.STATUS->ddint         ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_layer_info.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT       ",1000);
           if  (api->rsp->isdbt_layer_info.STATUS->scanint       ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->isdbt_layer_info.STATUS->scanint       ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_layer_info.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR           ",1000);
           if  (api->rsp->isdbt_layer_info.STATUS->err           ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->isdbt_layer_info.STATUS->err           ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_layer_info.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS           ",1000);
           if  (api->rsp->isdbt_layer_info.STATUS->cts           ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->isdbt_layer_info.STATUS->cts           ==     0) strncat(msg,"WAIT     ",1000);
      else                                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_layer_info.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CONSTELLATION ",1000);
           if  (api->rsp->isdbt_layer_info.constellation ==     4) strncat(msg,"DQPSK",1000);
      else if  (api->rsp->isdbt_layer_info.constellation ==     7) strncat(msg,"QAM16",1000);
      else if  (api->rsp->isdbt_layer_info.constellation ==     9) strncat(msg,"QAM64",1000);
      else if  (api->rsp->isdbt_layer_info.constellation ==     3) strncat(msg,"QPSK ",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_layer_info.constellation);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CODE_RATE     ",1000);
           if  (api->rsp->isdbt_layer_info.code_rate     ==     1) strncat(msg,"1_2",1000);
      else if  (api->rsp->isdbt_layer_info.code_rate     ==     2) strncat(msg,"2_3",1000);
      else if  (api->rsp->isdbt_layer_info.code_rate     ==     3) strncat(msg,"3_4",1000);
      else if  (api->rsp->isdbt_layer_info.code_rate     ==     5) strncat(msg,"5_6",1000);
      else if  (api->rsp->isdbt_layer_info.code_rate     ==     7) strncat(msg,"7_8",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_layer_info.code_rate);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-IL            ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_layer_info.il);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-NB_SEG        ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_layer_info.nb_seg);
      }
     break;
    #endif /*     Si2183_ISDBT_LAYER_INFO_CMD */

    #ifdef        Si2183_ISDBT_STATUS_CMD
     case         Si2183_ISDBT_STATUS_CMD_CODE:
      sprintf(msg,"ISDBT_STATUS ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT            ",1000);
           if  (api->rsp->isdbt_status.STATUS->ddint            ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->isdbt_status.STATUS->ddint            ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                               STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT          ",1000);
           if  (api->rsp->isdbt_status.STATUS->scanint          ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->isdbt_status.STATUS->scanint          ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                               STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR              ",1000);
           if  (api->rsp->isdbt_status.STATUS->err              ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->isdbt_status.STATUS->err              ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                               STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS              ",1000);
           if  (api->rsp->isdbt_status.STATUS->cts              ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->isdbt_status.STATUS->cts              ==     0) strncat(msg,"WAIT     ",1000);
      else                                                               STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PCLINT           ",1000);
           if  (api->rsp->isdbt_status.pclint           ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->isdbt_status.pclint           ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.pclint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DLINT            ",1000);
           if  (api->rsp->isdbt_status.dlint            ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->isdbt_status.dlint            ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.dlint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BERINT           ",1000);
           if  (api->rsp->isdbt_status.berint           ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->isdbt_status.berint           ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.berint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-UNCORINT         ",1000);
           if  (api->rsp->isdbt_status.uncorint         ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->isdbt_status.uncorint         ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.uncorint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-NOTISDBTINT      ",1000);
           if  (api->rsp->isdbt_status.notisdbtint      ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->isdbt_status.notisdbtint      ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.notisdbtint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-EWBSINT          ",1000);
           if  (api->rsp->isdbt_status.ewbsint          ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->isdbt_status.ewbsint          ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.ewbsint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PCL              ",1000);
           if  (api->rsp->isdbt_status.pcl              ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->isdbt_status.pcl              ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.pcl);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DL               ",1000);
           if  (api->rsp->isdbt_status.dl               ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->isdbt_status.dl               ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.dl);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BER              ",1000);
           if  (api->rsp->isdbt_status.ber              ==     1) strncat(msg,"BER_ABOVE",1000);
      else if  (api->rsp->isdbt_status.ber              ==     0) strncat(msg,"BER_BELOW",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.ber);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-UNCOR            ",1000);
           if  (api->rsp->isdbt_status.uncor            ==     0) strncat(msg,"NO_UNCOR_FOUND",1000);
      else if  (api->rsp->isdbt_status.uncor            ==     1) strncat(msg,"UNCOR_FOUND   ",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.uncor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-NOTISDBT         ",1000);
           if  (api->rsp->isdbt_status.notisdbt         ==     0) strncat(msg,"ISDBT    ",1000);
      else if  (api->rsp->isdbt_status.notisdbt         ==     1) strncat(msg,"NOT_ISDBT",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.notisdbt);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-EWBS             ",1000);
           if  (api->rsp->isdbt_status.ewbs             ==     0) strncat(msg,"NORMAL ",1000);
      else if  (api->rsp->isdbt_status.ewbs             ==     1) strncat(msg,"WARNING",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.ewbs);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CNR              ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.cnr);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-AFC_FREQ         ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.afc_freq);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TIMING_OFFSET    ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.timing_offset);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-FFT_MODE         ",1000);
           if  (api->rsp->isdbt_status.fft_mode         ==    11) strncat(msg,"2K",1000);
      else if  (api->rsp->isdbt_status.fft_mode         ==    12) strncat(msg,"4K",1000);
      else if  (api->rsp->isdbt_status.fft_mode         ==    13) strncat(msg,"8K",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.fft_mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-GUARD_INT        ",1000);
           if  (api->rsp->isdbt_status.guard_int        ==     2) strncat(msg,"1_16",1000);
      else if  (api->rsp->isdbt_status.guard_int        ==     1) strncat(msg,"1_32",1000);
      else if  (api->rsp->isdbt_status.guard_int        ==     4) strncat(msg,"1_4 ",1000);
      else if  (api->rsp->isdbt_status.guard_int        ==     3) strncat(msg,"1_8 ",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.guard_int);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SP_INV           ",1000);
           if  (api->rsp->isdbt_status.sp_inv           ==     1) strncat(msg,"INVERTED",1000);
      else if  (api->rsp->isdbt_status.sp_inv           ==     0) strncat(msg,"NORMAL  ",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.sp_inv);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-NB_SEG_A         ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.nb_seg_a);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-NB_SEG_B         ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.nb_seg_b);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-NB_SEG_C         ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.nb_seg_c);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PARTIAL_FLAG     ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.partial_flag);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SYST_ID          ",1000);
           if  (api->rsp->isdbt_status.syst_id          ==     0) strncat(msg,"ISDB_T   ",1000);
      else if  (api->rsp->isdbt_status.syst_id          ==     1) strncat(msg,"ISDB_T_SB",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.syst_id);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RESERVED_MSB     ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.reserved_msb);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PHASE_SHIFT_CORR ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.phase_shift_corr);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg," -EMERGENCY_FLAG "  ,1000);
           if  (api->rsp->isdbt_status.emergency_flag   ==     0) strncat(msg,"NORMAL" ,1000);
      else if  (api->rsp->isdbt_status.emergency_flag   ==     1) strncat(msg,"WARNING",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.emergency_flag);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RESERVED_LSB     ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.reserved_lsb);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DL_C             ",1000);
           if  (api->rsp->isdbt_status.dl_c             ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->isdbt_status.dl_c             ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.dl_c);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DL_B             ",1000);
           if  (api->rsp->isdbt_status.dl_b             ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->isdbt_status.dl_b             ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.dl_b);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DL_A             ",1000);
           if  (api->rsp->isdbt_status.dl_a             ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->isdbt_status.dl_a             ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->isdbt_status.dl_a);
      }
     break;
    #endif /*     Si2183_ISDBT_STATUS_CMD */

#endif /* DEMOD_ISDB_T */

#ifdef    DEMOD_MCNS
    #ifdef        Si2183_MCNS_STATUS_CMD
     case         Si2183_MCNS_STATUS_CMD_CODE:
      sprintf(msg,"MCNS_STATUS ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT         ",1000);
           if  (api->rsp->mcns_status.STATUS->ddint         ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->mcns_status.STATUS->ddint         ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                           STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->mcns_status.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT       ",1000);
           if  (api->rsp->mcns_status.STATUS->scanint       ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->mcns_status.STATUS->scanint       ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                           STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->mcns_status.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR           ",1000);
           if  (api->rsp->mcns_status.STATUS->err           ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->mcns_status.STATUS->err           ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                           STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->mcns_status.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS           ",1000);
           if  (api->rsp->mcns_status.STATUS->cts           ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->mcns_status.STATUS->cts           ==     0) strncat(msg,"WAIT     ",1000);
      else                                                           STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->mcns_status.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PCLINT        ",1000);
           if  (api->rsp->mcns_status.pclint        ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->mcns_status.pclint        ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->mcns_status.pclint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DLINT         ",1000);
           if  (api->rsp->mcns_status.dlint         ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->mcns_status.dlint         ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->mcns_status.dlint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BERINT        ",1000);
           if  (api->rsp->mcns_status.berint        ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->mcns_status.berint        ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->mcns_status.berint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-UNCORINT      ",1000);
           if  (api->rsp->mcns_status.uncorint      ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->mcns_status.uncorint      ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->mcns_status.uncorint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PCL           ",1000);
           if  (api->rsp->mcns_status.pcl           ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->mcns_status.pcl           ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->mcns_status.pcl);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DL            ",1000);
           if  (api->rsp->mcns_status.dl            ==     1) strncat(msg,"LOCKED ",1000);
      else if  (api->rsp->mcns_status.dl            ==     0) strncat(msg,"NO_LOCK",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->mcns_status.dl);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BER           ",1000);
           if  (api->rsp->mcns_status.ber           ==     1) strncat(msg,"BER_ABOVE",1000);
      else if  (api->rsp->mcns_status.ber           ==     0) strncat(msg,"BER_BELOW",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->mcns_status.ber);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-UNCOR         ",1000);
           if  (api->rsp->mcns_status.uncor         ==     0) strncat(msg,"NO_UNCOR_FOUND",1000);
      else if  (api->rsp->mcns_status.uncor         ==     1) strncat(msg,"UNCOR_FOUND   ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->mcns_status.uncor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CNR           ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->mcns_status.cnr);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-AFC_FREQ      ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->mcns_status.afc_freq);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TIMING_OFFSET ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->mcns_status.timing_offset);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CONSTELLATION ",1000);
           if  (api->rsp->mcns_status.constellation ==    11) strncat(msg,"QAM256",1000);
      else if  (api->rsp->mcns_status.constellation ==     9) strncat(msg,"QAM64 ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->mcns_status.constellation);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SP_INV        ",1000);
           if  (api->rsp->mcns_status.sp_inv        ==     1) strncat(msg,"INVERTED",1000);
      else if  (api->rsp->mcns_status.sp_inv        ==     0) strncat(msg,"NORMAL  ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->mcns_status.sp_inv);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-INTERLEAVING  ",1000);
           if  (api->rsp->mcns_status.interleaving  ==     0) strncat(msg,"0__128_1    ",1000);
      else if  (api->rsp->mcns_status.interleaving  ==    10) strncat(msg,"10__128_6   ",1000);
      else if  (api->rsp->mcns_status.interleaving  ==    11) strncat(msg,"11__RESERVED",1000);
      else if  (api->rsp->mcns_status.interleaving  ==    12) strncat(msg,"12__128_7   ",1000);
      else if  (api->rsp->mcns_status.interleaving  ==    13) strncat(msg,"13__RESERVED",1000);
      else if  (api->rsp->mcns_status.interleaving  ==    14) strncat(msg,"14__128_8   ",1000);
      else if  (api->rsp->mcns_status.interleaving  ==    15) strncat(msg,"15__RESERVED",1000);
      else if  (api->rsp->mcns_status.interleaving  ==     1) strncat(msg,"1__128_1    ",1000);
      else if  (api->rsp->mcns_status.interleaving  ==     2) strncat(msg,"2__128_2    ",1000);
      else if  (api->rsp->mcns_status.interleaving  ==     3) strncat(msg,"3__64_2     ",1000);
      else if  (api->rsp->mcns_status.interleaving  ==     4) strncat(msg,"4__128_3    ",1000);
      else if  (api->rsp->mcns_status.interleaving  ==     5) strncat(msg,"5__32_4     ",1000);
      else if  (api->rsp->mcns_status.interleaving  ==     6) strncat(msg,"6__128_4    ",1000);
      else if  (api->rsp->mcns_status.interleaving  ==     7) strncat(msg,"7__16_8     ",1000);
      else if  (api->rsp->mcns_status.interleaving  ==     8) strncat(msg,"8__128_5    ",1000);
      else if  (api->rsp->mcns_status.interleaving  ==     9) strncat(msg,"9__8_16     ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->mcns_status.interleaving);
      }
     break;
    #endif /*     Si2183_MCNS_STATUS_CMD */

#endif /* DEMOD_MCNS */

    #ifdef        Si2183_PART_INFO_CMD
     case         Si2183_PART_INFO_CMD_CODE:
      sprintf(msg,"PART_INFO ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT    ",1000);
           if  (api->rsp->part_info.STATUS->ddint    ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->part_info.STATUS->ddint    ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT  ",1000);
           if  (api->rsp->part_info.STATUS->scanint  ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->part_info.STATUS->scanint  ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR      ",1000);
           if  (api->rsp->part_info.STATUS->err      ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->part_info.STATUS->err      ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS      ",1000);
           if  (api->rsp->part_info.STATUS->cts      ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->part_info.STATUS->cts      ==     0) strncat(msg,"WAIT     ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CHIPREV  ",1000);
           if  (api->rsp->part_info.chiprev  ==     1) strncat(msg,"A",1000);
      else if  (api->rsp->part_info.chiprev  ==     2) strncat(msg,"B",1000);
      else if  (api->rsp->part_info.chiprev  ==     3) strncat(msg,"C",1000);
      else if  (api->rsp->part_info.chiprev  ==     4) strncat(msg,"D",1000);
      else if  (api->rsp->part_info.chiprev  ==     5) strncat(msg,"E",1000);
      else                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info.chiprev);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PART     ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info.part);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PMAJOR   ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info.pmajor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PMINOR   ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info.pminor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PBUILD   ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info.pbuild);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RESERVED ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info.reserved);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SERIAL   ",1000); STRING_APPEND_SAFE(msg,1000,"%ld", api->rsp->part_info.serial);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ROMID    ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info.romid);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RX       ",1000);
           if  (api->rsp->part_info.rx       ==     1) strncat(msg,"RX        ",1000);
      else if  (api->rsp->part_info.rx       ==     0) strncat(msg,"STANDALONE",1000);
      else                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info.rx);
      }
     break;
    #endif /*     Si2183_PART_INFO_CMD */

    #ifdef        Si2183_POWER_DOWN_CMD
     case         Si2183_POWER_DOWN_CMD_CODE:
      sprintf(msg,"POWER_DOWN ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->power_down.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->power_down.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_down.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->power_down.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->power_down.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_down.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->power_down.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->power_down.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_down.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->power_down.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->power_down.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_down.STATUS->cts);
      }
     break;
    #endif /*     Si2183_POWER_DOWN_CMD */

    #ifdef        Si2183_POWER_UP_CMD
     case         Si2183_POWER_UP_CMD_CODE:
      sprintf(msg,"POWER_UP ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->power_up.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->power_up.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_up.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->power_up.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->power_up.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_up.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->power_up.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->power_up.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_up.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->power_up.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->power_up.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_up.STATUS->cts);
      }
     break;
    #endif /*     Si2183_POWER_UP_CMD */

    #ifdef        Si2183_RSSI_ADC_CMD
     case         Si2183_RSSI_ADC_CMD_CODE:
      sprintf(msg,"RSSI_ADC ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->rssi_adc.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->rssi_adc.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->rssi_adc.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->rssi_adc.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->rssi_adc.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->rssi_adc.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->rssi_adc.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->rssi_adc.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->rssi_adc.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->rssi_adc.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->rssi_adc.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->rssi_adc.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-LEVEL   ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->rssi_adc.level);
      }
     break;
    #endif /*     Si2183_RSSI_ADC_CMD */

    #ifdef        Si2183_SCAN_CTRL_CMD
     case         Si2183_SCAN_CTRL_CMD_CODE:
      sprintf(msg,"SCAN_CTRL ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->scan_ctrl.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->scan_ctrl.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->scan_ctrl.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->scan_ctrl.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->scan_ctrl.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->scan_ctrl.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->scan_ctrl.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->scan_ctrl.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->scan_ctrl.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->scan_ctrl.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->scan_ctrl.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->scan_ctrl.STATUS->cts);
      }
     break;
    #endif /*     Si2183_SCAN_CTRL_CMD */

    #ifdef        Si2183_SCAN_STATUS_CMD
     case         Si2183_SCAN_STATUS_CMD_CODE:
      sprintf(msg,"SCAN_STATUS ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT       ",1000);
           if  (api->rsp->scan_status.STATUS->ddint       ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->scan_status.STATUS->ddint       ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->scan_status.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT     ",1000);
           if  (api->rsp->scan_status.STATUS->scanint     ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->scan_status.STATUS->scanint     ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->scan_status.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR         ",1000);
           if  (api->rsp->scan_status.STATUS->err         ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->scan_status.STATUS->err         ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->scan_status.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS         ",1000);
           if  (api->rsp->scan_status.STATUS->cts         ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->scan_status.STATUS->cts         ==     0) strncat(msg,"WAIT     ",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->scan_status.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BUZINT      ",1000);
           if  (api->rsp->scan_status.buzint      ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->scan_status.buzint      ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->scan_status.buzint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REQINT      ",1000);
           if  (api->rsp->scan_status.reqint      ==     1) strncat(msg,"CHANGED  ",1000);
      else if  (api->rsp->scan_status.reqint      ==     0) strncat(msg,"NO_CHANGE",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->scan_status.reqint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-BUZ         ",1000);
           if  (api->rsp->scan_status.buz         ==     1) strncat(msg,"BUSY",1000);
      else if  (api->rsp->scan_status.buz         ==     0) strncat(msg,"CTS ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->scan_status.buz);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REQ         ",1000);
           if  (api->rsp->scan_status.req         ==     0) strncat(msg,"NO_REQUEST",1000);
      else if  (api->rsp->scan_status.req         ==     1) strncat(msg,"REQUEST   ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->scan_status.req);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCAN_STATUS ",1000);
           if  (api->rsp->scan_status.scan_status ==     6) strncat(msg,"ANALOG_CHANNEL_FOUND ",1000);
      else if  (api->rsp->scan_status.scan_status ==    63) strncat(msg,"DEBUG                ",1000);
      else if  (api->rsp->scan_status.scan_status ==     5) strncat(msg,"DIGITAL_CHANNEL_FOUND",1000);
      else if  (api->rsp->scan_status.scan_status ==     2) strncat(msg,"ENDED                ",1000);
      else if  (api->rsp->scan_status.scan_status ==     3) strncat(msg,"ERROR                ",1000);
      else if  (api->rsp->scan_status.scan_status ==     0) strncat(msg,"IDLE                 ",1000);
      else if  (api->rsp->scan_status.scan_status ==     1) strncat(msg,"SEARCHING            ",1000);
      else if  (api->rsp->scan_status.scan_status ==     4) strncat(msg,"TUNE_REQUEST         ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->scan_status.scan_status);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RF_FREQ     ",1000); STRING_APPEND_SAFE(msg,1000,"%ld", api->rsp->scan_status.rf_freq);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SYMB_RATE   ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->scan_status.symb_rate);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-MODULATION  ",1000);
           if  (api->rsp->scan_status.modulation  ==    10) strncat(msg,"DSS  ",1000);
      else if  (api->rsp->scan_status.modulation  ==     3) strncat(msg,"DVBC ",1000);
      else if  (api->rsp->scan_status.modulation  ==    11) strncat(msg,"DVBC2",1000);
      else if  (api->rsp->scan_status.modulation  ==     8) strncat(msg,"DVBS ",1000);
      else if  (api->rsp->scan_status.modulation  ==     9) strncat(msg,"DVBS2",1000);
      else if  (api->rsp->scan_status.modulation  ==     2) strncat(msg,"DVBT ",1000);
      else if  (api->rsp->scan_status.modulation  ==     7) strncat(msg,"DVBT2",1000);
      else if  (api->rsp->scan_status.modulation  ==     4) strncat(msg,"ISDBT",1000);
      else if  (api->rsp->scan_status.modulation  ==     1) strncat(msg,"MCNS ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->scan_status.modulation);
      }
     break;
    #endif /*     Si2183_SCAN_STATUS_CMD */

    #ifdef        Si2183_SET_PROPERTY_CMD
     case         Si2183_SET_PROPERTY_CMD_CODE:
      sprintf(msg,"SET_PROPERTY ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT    ",1000);
           if  (api->rsp->set_property.STATUS->ddint    ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->set_property.STATUS->ddint    ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->set_property.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT  ",1000);
           if  (api->rsp->set_property.STATUS->scanint  ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->set_property.STATUS->scanint  ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->set_property.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR      ",1000);
           if  (api->rsp->set_property.STATUS->err      ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->set_property.STATUS->err      ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->set_property.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS      ",1000);
           if  (api->rsp->set_property.STATUS->cts      ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->set_property.STATUS->cts      ==     0) strncat(msg,"WAIT     ",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->set_property.STATUS->cts);
      }
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RESERVED ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->set_property.reserved);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA     ",1000); STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->set_property.data);
      }
     break;
    #endif /*     Si2183_SET_PROPERTY_CMD */

    #ifdef        Si2183_SPI_LINK_CMD
     case         Si2183_SPI_LINK_CMD_CODE:
      sprintf(msg,"SPI_LINK ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->spi_link.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->spi_link.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->spi_link.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->spi_link.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->spi_link.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->spi_link.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->spi_link.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->spi_link.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->spi_link.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->spi_link.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->spi_link.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->spi_link.STATUS->cts);
      }
     break;
    #endif /*     Si2183_SPI_LINK_CMD */

    #ifdef        Si2183_SPI_PASSTHROUGH_CMD
     case         Si2183_SPI_PASSTHROUGH_CMD_CODE:
      sprintf(msg,"SPI_PASSTHROUGH ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->spi_passthrough.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->spi_passthrough.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->spi_passthrough.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->spi_passthrough.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->spi_passthrough.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->spi_passthrough.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->spi_passthrough.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->spi_passthrough.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->spi_passthrough.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->spi_passthrough.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->spi_passthrough.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->spi_passthrough.STATUS->cts);
      }
     break;
    #endif /*     Si2183_SPI_PASSTHROUGH_CMD */

    #ifdef        Si2183_START_CLK_CMD
     case         Si2183_START_CLK_CMD_CODE:
      sprintf(msg,"START_CLK ");
      if (display_FIELDS) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DDINT   ",1000);
           if  (api->rsp->start_clk.STATUS->ddint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->start_clk.STATUS->ddint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->start_clk.STATUS->ddint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SCANINT ",1000);
           if  (api->rsp->start_clk.STATUS->scanint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->start_clk.STATUS->scanint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->start_clk.STATUS->scanint);
      }
      if (display_ERR   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->start_clk.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->start_clk.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->start_clk.STATUS->err);
      }
      if (display_CTS   ) {
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->start_clk.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->start_clk.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->start_clk.STATUS->cts);
      }
     break;
    #endif /*     Si2183_START_CLK_CMD */

     default : break;
    }
    return 0;
  }
#endif /* Si2183_GET_COMMAND_STRINGS */








