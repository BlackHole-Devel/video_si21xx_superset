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
                  Silicon Laboratories Broadcast Si2176 Layer 1 API
   API commands definitions
   FILE: Si2176_L1_Commands.c
   Supported IC : Si2176
   Compiled for ROM 13 firmware 3_2_build_6
   Revision: 0.1
   Tag:  TAGNAME
   Date: December 22 2011
**************************************************************************************/
#define   Si2176_COMMAND_PROTOTYPES

#include "Si2176_L1_API.h"

/***********************************************************************************************************************
  Si2176_CurrentResponseStatus function
  Use:        status checking function
              Used to fill the Si2176_COMMON_REPLY_struct members with the ptDataBuffer byte's bits
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure helps reducing the code size
  Parameter: ptDataBuffer  a single byte received when reading a command's response (the first byte)
  Returns:   0 if the err bit (bit 6) is unset, 1 otherwise
 ***********************************************************************************************************************/
unsigned char Si2176_CurrentResponseStatus (L1_Si2176_Context *api, unsigned char ptDataBuffer)
{
/* _status_code_insertion_start */
    api->status->tunint = ((ptDataBuffer >> 0 ) & 0x01);
    api->status->atvint = ((ptDataBuffer >> 1 ) & 0x01);
    api->status->dtvint = ((ptDataBuffer >> 2 ) & 0x01);
    api->status->err    = ((ptDataBuffer >> 6 ) & 0x01);
    api->status->cts    = ((ptDataBuffer >> 7 ) & 0x01);
/* _status_code_insertion_point */
  return (api->status->err ? ERROR_Si2176_ERR : NO_Si2176_ERROR);
}

/***********************************************************************************************************************
  Si2176_pollForCTS function
  Use:        CTS checking function
              Used to check the CTS bit until it is set before sending the next command
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure helps reducing the code size
              max timeout = 1000 ms

  Returns:   1 if the CTS bit is set, 0 otherwise
 ***********************************************************************************************************************/
unsigned char Si2176_pollForCTS (L1_Si2176_Context *api)
{
  unsigned char rspByteBuffer[1];
  unsigned int start_time;

  start_time = system_time();

  while (system_time() - start_time <1000)  { /* wait a maximum of 1000ms */
    if (L0_ReadCommandBytes(api->i2c, 1, rspByteBuffer) != 1) {
      SiTRACE("Si2176_pollForCTS ERROR reading byte 0!\n");
      return ERROR_Si2176_POLLING_CTS;
    }
    /* return OK if CTS set */
    if (rspByteBuffer[0] & 0x80) {
      return NO_Si2176_ERROR;
    }
  }

  SiTRACE("Si2176_pollForCTS ERROR CTS Timeout!\n");
  return ERROR_Si2176_CTS_TIMEOUT;
}

/***********************************************************************************************************************
  Si2176_pollForResponse function
  Use:        command response retrieval function
              Used to retrieve the command response in the provided buffer
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure helps reducing the code size
              max timeout = 1000 ms

  Parameter:  nbBytes          the number of response bytes to read
  Parameter:  pByteBuffer      a buffer into which bytes will be stored
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
unsigned char Si2176_pollForResponse (L1_Si2176_Context *api, unsigned int nbBytes, unsigned char *pByteBuffer)
{
  unsigned int start_time;

  start_time = system_time();

  while (system_time() - start_time <1000)  { /* wait a maximum of 1000ms */
    if ((unsigned int)L0_ReadCommandBytes(api->i2c, nbBytes, pByteBuffer) != nbBytes) {
      SiTRACE("Si2176_pollForResponse ERROR reading byte 0!\n");
      return ERROR_Si2176_POLLING_RESPONSE;
    }
    /* return response err flag if CTS set */
    if (pByteBuffer[0] & 0x80)  {
      return Si2176_CurrentResponseStatus(api, pByteBuffer[0]);
    }
  }

  SiTRACE("Si2176_pollForResponse ERROR CTS Timeout!\n");
  return ERROR_Si2176_CTS_TIMEOUT;
}

/* _commands_insertion_start */
#ifdef    Si2176_AGC_OVERRIDE_CMD
 /*---------------------------------------------------*/
/* Si2176_AGC_OVERRIDE COMMAND                     */
/*---------------------------------------------------*/
unsigned char Si2176_L1_AGC_OVERRIDE    (L1_Si2176_Context *api,
                                         unsigned char   force_max_gain,
                                         unsigned char   force_top_gain)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];
    api->rsp->agc_override.STATUS = api->status;

    SiTRACE("Si2176 AGC_OVERRIDE ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((force_max_gain > Si2176_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FORCE_MAX_GAIN %d ", force_max_gain );
    if ((force_top_gain > Si2176_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FORCE_TOP_GAIN %d ", force_top_gain );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2176_AGC_OVERRIDE_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( force_max_gain & Si2176_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_MASK ) << Si2176_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_LSB|
                                         ( force_top_gain & Si2176_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_MASK ) << Si2176_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing AGC_OVERRIDE bytes!\n");
      return ERROR_Si2176_SENDING_COMMAND;
    }

    error_code = Si2176_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling AGC_OVERRIDE response\n");
      return error_code;
    }


    return NO_Si2176_ERROR;
}
#endif /* Si2176_AGC_OVERRIDE_CMD */
#ifdef    Si2176_ATV_RESTART_CMD
 /*---------------------------------------------------*/
/* Si2176_ATV_RESTART COMMAND                      */
/*---------------------------------------------------*/
unsigned char Si2176_L1_ATV_RESTART     (L1_Si2176_Context *api,
                                         unsigned char   mode)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];
    api->rsp->atv_restart.STATUS = api->status;

    SiTRACE("Si2176 ATV_RESTART ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((mode > Si2176_ATV_RESTART_CMD_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("MODE %d ", mode );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2176_ATV_RESTART_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( mode & Si2176_ATV_RESTART_CMD_MODE_MASK ) << Si2176_ATV_RESTART_CMD_MODE_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing ATV_RESTART bytes!\n");
      return ERROR_Si2176_SENDING_COMMAND;
    }

    error_code = Si2176_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling ATV_RESTART response\n");
      return error_code;
    }


    return NO_Si2176_ERROR;
}
#endif /* Si2176_ATV_RESTART_CMD */
#ifdef    Si2176_ATV_STATUS_CMD
 /*---------------------------------------------------*/
/* Si2176_ATV_STATUS COMMAND                       */
/*---------------------------------------------------*/
unsigned char Si2176_L1_ATV_STATUS      (L1_Si2176_Context *api,
                                         unsigned char   intack)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[11];
    api->rsp->atv_status.STATUS = api->status;

    SiTRACE("Si2176 ATV_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((intack > Si2176_ATV_STATUS_CMD_INTACK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("INTACK %d ", intack );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2176_ATV_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si2176_ATV_STATUS_CMD_INTACK_MASK ) << Si2176_ATV_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing ATV_STATUS bytes!\n");
      return ERROR_Si2176_SENDING_COMMAND;
    }

    error_code = Si2176_pollForResponse(api, 11, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling ATV_STATUS response\n");
      return error_code;
    }

    api->rsp->atv_status.chlint           =   (( ( (rspByteBuffer[1]  )) >> Si2176_ATV_STATUS_RESPONSE_CHLINT_LSB           ) & Si2176_ATV_STATUS_RESPONSE_CHLINT_MASK           );
    api->rsp->atv_status.pclint           =   (( ( (rspByteBuffer[1]  )) >> Si2176_ATV_STATUS_RESPONSE_PCLINT_LSB           ) & Si2176_ATV_STATUS_RESPONSE_PCLINT_MASK           );
    api->rsp->atv_status.dlint            =   (( ( (rspByteBuffer[1]  )) >> Si2176_ATV_STATUS_RESPONSE_DLINT_LSB            ) & Si2176_ATV_STATUS_RESPONSE_DLINT_MASK            );
    api->rsp->atv_status.snrlint          =   (( ( (rspByteBuffer[1]  )) >> Si2176_ATV_STATUS_RESPONSE_SNRLINT_LSB          ) & Si2176_ATV_STATUS_RESPONSE_SNRLINT_MASK          );
    api->rsp->atv_status.snrhint          =   (( ( (rspByteBuffer[1]  )) >> Si2176_ATV_STATUS_RESPONSE_SNRHINT_LSB          ) & Si2176_ATV_STATUS_RESPONSE_SNRHINT_MASK          );
    api->rsp->atv_status.chl              =   (( ( (rspByteBuffer[2]  )) >> Si2176_ATV_STATUS_RESPONSE_CHL_LSB              ) & Si2176_ATV_STATUS_RESPONSE_CHL_MASK              );
    api->rsp->atv_status.pcl              =   (( ( (rspByteBuffer[2]  )) >> Si2176_ATV_STATUS_RESPONSE_PCL_LSB              ) & Si2176_ATV_STATUS_RESPONSE_PCL_MASK              );
    api->rsp->atv_status.dl               =   (( ( (rspByteBuffer[2]  )) >> Si2176_ATV_STATUS_RESPONSE_DL_LSB               ) & Si2176_ATV_STATUS_RESPONSE_DL_MASK               );
    api->rsp->atv_status.snrl             =   (( ( (rspByteBuffer[2]  )) >> Si2176_ATV_STATUS_RESPONSE_SNRL_LSB             ) & Si2176_ATV_STATUS_RESPONSE_SNRL_MASK             );
    api->rsp->atv_status.snrh             =   (( ( (rspByteBuffer[2]  )) >> Si2176_ATV_STATUS_RESPONSE_SNRH_LSB             ) & Si2176_ATV_STATUS_RESPONSE_SNRH_MASK             );
    api->rsp->atv_status.video_snr        =   (( ( (rspByteBuffer[3]  )) >> Si2176_ATV_STATUS_RESPONSE_VIDEO_SNR_LSB        ) & Si2176_ATV_STATUS_RESPONSE_VIDEO_SNR_MASK        );
    api->rsp->atv_status.afc_freq         = (((( ( (rspByteBuffer[4]  ) | (rspByteBuffer[5]  << 8 )) >> Si2176_ATV_STATUS_RESPONSE_AFC_FREQ_LSB         ) & Si2176_ATV_STATUS_RESPONSE_AFC_FREQ_MASK) <<Si2176_ATV_STATUS_RESPONSE_AFC_FREQ_SHIFT ) >>Si2176_ATV_STATUS_RESPONSE_AFC_FREQ_SHIFT         );
    api->rsp->atv_status.video_sc_spacing = (((( ( (rspByteBuffer[6]  ) | (rspByteBuffer[7]  << 8 )) >> Si2176_ATV_STATUS_RESPONSE_VIDEO_SC_SPACING_LSB ) & Si2176_ATV_STATUS_RESPONSE_VIDEO_SC_SPACING_MASK) <<Si2176_ATV_STATUS_RESPONSE_VIDEO_SC_SPACING_SHIFT ) >>Si2176_ATV_STATUS_RESPONSE_VIDEO_SC_SPACING_SHIFT );
    api->rsp->atv_status.video_sys        =   (( ( (rspByteBuffer[8]  )) >> Si2176_ATV_STATUS_RESPONSE_VIDEO_SYS_LSB        ) & Si2176_ATV_STATUS_RESPONSE_VIDEO_SYS_MASK        );
    api->rsp->atv_status.color            =   (( ( (rspByteBuffer[8]  )) >> Si2176_ATV_STATUS_RESPONSE_COLOR_LSB            ) & Si2176_ATV_STATUS_RESPONSE_COLOR_MASK            );
    api->rsp->atv_status.trans            =   (( ( (rspByteBuffer[8]  )) >> Si2176_ATV_STATUS_RESPONSE_TRANS_LSB            ) & Si2176_ATV_STATUS_RESPONSE_TRANS_MASK            );
    api->rsp->atv_status.audio_sys        =   (( ( (rspByteBuffer[9]  )) >> Si2176_ATV_STATUS_RESPONSE_AUDIO_SYS_LSB        ) & Si2176_ATV_STATUS_RESPONSE_AUDIO_SYS_MASK        );
    api->rsp->atv_status.audio_demod_mode =   (( ( (rspByteBuffer[9]  )) >> Si2176_ATV_STATUS_RESPONSE_AUDIO_DEMOD_MODE_LSB ) & Si2176_ATV_STATUS_RESPONSE_AUDIO_DEMOD_MODE_MASK );
    api->rsp->atv_status.audio_chan_bw    =   (( ( (rspByteBuffer[10] )) >> Si2176_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_LSB    ) & Si2176_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_MASK    );

    return NO_Si2176_ERROR;
}
#endif /* Si2176_ATV_STATUS_CMD */
#ifdef    Si2176_CONFIG_PINS_CMD
 /*---------------------------------------------------*/
/* Si2176_CONFIG_PINS COMMAND                      */
/*---------------------------------------------------*/
unsigned char Si2176_L1_CONFIG_PINS     (L1_Si2176_Context *api,
                                         unsigned char   gpio1_mode,
                                         unsigned char   gpio1_read,
                                         unsigned char   gpio2_mode,
                                         unsigned char   gpio2_read,
                                         unsigned char   gpio3_mode,
                                         unsigned char   gpio3_read,
                                         unsigned char   bclk1_mode,
                                         unsigned char   bclk1_read,
                                         unsigned char   xout_mode)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[6];
    unsigned char rspByteBuffer[6];
    api->rsp->config_pins.STATUS = api->status;

    SiTRACE("Si2176 CONFIG_PINS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((gpio1_mode > Si2176_CONFIG_PINS_CMD_GPIO1_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO1_MODE %d ", gpio1_mode );
    if ((gpio1_read > Si2176_CONFIG_PINS_CMD_GPIO1_READ_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO1_READ %d ", gpio1_read );
    if ((gpio2_mode > Si2176_CONFIG_PINS_CMD_GPIO2_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO2_MODE %d ", gpio2_mode );
    if ((gpio2_read > Si2176_CONFIG_PINS_CMD_GPIO2_READ_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO2_READ %d ", gpio2_read );
    if ((gpio3_mode > Si2176_CONFIG_PINS_CMD_GPIO3_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO3_MODE %d ", gpio3_mode );
    if ((gpio3_read > Si2176_CONFIG_PINS_CMD_GPIO3_READ_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO3_READ %d ", gpio3_read );
    if ((bclk1_mode > Si2176_CONFIG_PINS_CMD_BCLK1_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("BCLK1_MODE %d ", bclk1_mode );
    if ((bclk1_read > Si2176_CONFIG_PINS_CMD_BCLK1_READ_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("BCLK1_READ %d ", bclk1_read );
    if ((xout_mode  > Si2176_CONFIG_PINS_CMD_XOUT_MODE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("XOUT_MODE %d " , xout_mode  );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2176_CONFIG_PINS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( gpio1_mode & Si2176_CONFIG_PINS_CMD_GPIO1_MODE_MASK ) << Si2176_CONFIG_PINS_CMD_GPIO1_MODE_LSB|
                                         ( gpio1_read & Si2176_CONFIG_PINS_CMD_GPIO1_READ_MASK ) << Si2176_CONFIG_PINS_CMD_GPIO1_READ_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( gpio2_mode & Si2176_CONFIG_PINS_CMD_GPIO2_MODE_MASK ) << Si2176_CONFIG_PINS_CMD_GPIO2_MODE_LSB|
                                         ( gpio2_read & Si2176_CONFIG_PINS_CMD_GPIO2_READ_MASK ) << Si2176_CONFIG_PINS_CMD_GPIO2_READ_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( gpio3_mode & Si2176_CONFIG_PINS_CMD_GPIO3_MODE_MASK ) << Si2176_CONFIG_PINS_CMD_GPIO3_MODE_LSB|
                                         ( gpio3_read & Si2176_CONFIG_PINS_CMD_GPIO3_READ_MASK ) << Si2176_CONFIG_PINS_CMD_GPIO3_READ_LSB);
    cmdByteBuffer[4] = (unsigned char) ( ( bclk1_mode & Si2176_CONFIG_PINS_CMD_BCLK1_MODE_MASK ) << Si2176_CONFIG_PINS_CMD_BCLK1_MODE_LSB|
                                         ( bclk1_read & Si2176_CONFIG_PINS_CMD_BCLK1_READ_MASK ) << Si2176_CONFIG_PINS_CMD_BCLK1_READ_LSB);
    cmdByteBuffer[5] = (unsigned char) ( ( xout_mode  & Si2176_CONFIG_PINS_CMD_XOUT_MODE_MASK  ) << Si2176_CONFIG_PINS_CMD_XOUT_MODE_LSB );

    if (L0_WriteCommandBytes(api->i2c, 6, cmdByteBuffer) != 6) {
      SiTRACE("Error writing CONFIG_PINS bytes!\n");
      return ERROR_Si2176_SENDING_COMMAND;
    }

    error_code = Si2176_pollForResponse(api, 6, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling CONFIG_PINS response\n");
      return error_code;
    }

    api->rsp->config_pins.gpio1_mode  =   (( ( (rspByteBuffer[1]  )) >> Si2176_CONFIG_PINS_RESPONSE_GPIO1_MODE_LSB  ) & Si2176_CONFIG_PINS_RESPONSE_GPIO1_MODE_MASK  );
    api->rsp->config_pins.gpio1_state =   (( ( (rspByteBuffer[1]  )) >> Si2176_CONFIG_PINS_RESPONSE_GPIO1_STATE_LSB ) & Si2176_CONFIG_PINS_RESPONSE_GPIO1_STATE_MASK );
    api->rsp->config_pins.gpio2_mode  =   (( ( (rspByteBuffer[2]  )) >> Si2176_CONFIG_PINS_RESPONSE_GPIO2_MODE_LSB  ) & Si2176_CONFIG_PINS_RESPONSE_GPIO2_MODE_MASK  );
    api->rsp->config_pins.gpio2_state =   (( ( (rspByteBuffer[2]  )) >> Si2176_CONFIG_PINS_RESPONSE_GPIO2_STATE_LSB ) & Si2176_CONFIG_PINS_RESPONSE_GPIO2_STATE_MASK );
    api->rsp->config_pins.gpio3_mode  =   (( ( (rspByteBuffer[3]  )) >> Si2176_CONFIG_PINS_RESPONSE_GPIO3_MODE_LSB  ) & Si2176_CONFIG_PINS_RESPONSE_GPIO3_MODE_MASK  );
    api->rsp->config_pins.gpio3_state =   (( ( (rspByteBuffer[3]  )) >> Si2176_CONFIG_PINS_RESPONSE_GPIO3_STATE_LSB ) & Si2176_CONFIG_PINS_RESPONSE_GPIO3_STATE_MASK );
    api->rsp->config_pins.bclk1_mode  =   (( ( (rspByteBuffer[4]  )) >> Si2176_CONFIG_PINS_RESPONSE_BCLK1_MODE_LSB  ) & Si2176_CONFIG_PINS_RESPONSE_BCLK1_MODE_MASK  );
    api->rsp->config_pins.bclk1_state =   (( ( (rspByteBuffer[4]  )) >> Si2176_CONFIG_PINS_RESPONSE_BCLK1_STATE_LSB ) & Si2176_CONFIG_PINS_RESPONSE_BCLK1_STATE_MASK );
    api->rsp->config_pins.xout_mode   =   (( ( (rspByteBuffer[5]  )) >> Si2176_CONFIG_PINS_RESPONSE_XOUT_MODE_LSB   ) & Si2176_CONFIG_PINS_RESPONSE_XOUT_MODE_MASK   );

    return NO_Si2176_ERROR;
}
#endif /* Si2176_CONFIG_PINS_CMD */
#ifdef    Si2176_DTV_RESTART_CMD
 /*---------------------------------------------------*/
/* Si2176_DTV_RESTART COMMAND                      */
/*---------------------------------------------------*/
unsigned char Si2176_L1_DTV_RESTART     (L1_Si2176_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[1];
    api->rsp->dtv_restart.STATUS = api->status;

    SiTRACE("Si2176 DTV_RESTART ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2176_DTV_RESTART_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing DTV_RESTART bytes!\n");
      return ERROR_Si2176_SENDING_COMMAND;
    }

    error_code = Si2176_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DTV_RESTART response\n");
      return error_code;
    }


    return NO_Si2176_ERROR;
}
#endif /* Si2176_DTV_RESTART_CMD */
#ifdef    Si2176_DTV_STATUS_CMD
 /*---------------------------------------------------*/
/* Si2176_DTV_STATUS COMMAND                       */
/*---------------------------------------------------*/
unsigned char Si2176_L1_DTV_STATUS      (L1_Si2176_Context *api,
                                         unsigned char   intack)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[4];
    api->rsp->dtv_status.STATUS = api->status;

    SiTRACE("Si2176 DTV_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((intack > Si2176_DTV_STATUS_CMD_INTACK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("INTACK %d ", intack );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2176_DTV_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si2176_DTV_STATUS_CMD_INTACK_MASK ) << Si2176_DTV_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing DTV_STATUS bytes!\n");
      return ERROR_Si2176_SENDING_COMMAND;
    }

    error_code = Si2176_pollForResponse(api, 4, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DTV_STATUS response\n");
      return error_code;
    }

    api->rsp->dtv_status.chlint     =   (( ( (rspByteBuffer[1]  )) >> Si2176_DTV_STATUS_RESPONSE_CHLINT_LSB     ) & Si2176_DTV_STATUS_RESPONSE_CHLINT_MASK     );
    api->rsp->dtv_status.chl        =   (( ( (rspByteBuffer[2]  )) >> Si2176_DTV_STATUS_RESPONSE_CHL_LSB        ) & Si2176_DTV_STATUS_RESPONSE_CHL_MASK        );
    api->rsp->dtv_status.bw         =   (( ( (rspByteBuffer[3]  )) >> Si2176_DTV_STATUS_RESPONSE_BW_LSB         ) & Si2176_DTV_STATUS_RESPONSE_BW_MASK         );
    api->rsp->dtv_status.modulation =   (( ( (rspByteBuffer[3]  )) >> Si2176_DTV_STATUS_RESPONSE_MODULATION_LSB ) & Si2176_DTV_STATUS_RESPONSE_MODULATION_MASK );

    return NO_Si2176_ERROR;
}
#endif /* Si2176_DTV_STATUS_CMD */
#ifdef    Si2176_EXIT_BOOTLOADER_CMD
 /*---------------------------------------------------*/
/* Si2176_EXIT_BOOTLOADER COMMAND                  */
/*---------------------------------------------------*/
unsigned char Si2176_L1_EXIT_BOOTLOADER (L1_Si2176_Context *api,
                                         unsigned char   func,
                                         unsigned char   ctsien)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];
    api->rsp->exit_bootloader.STATUS = api->status;

    SiTRACE("Si2176 EXIT_BOOTLOADER ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((func   > Si2176_EXIT_BOOTLOADER_CMD_FUNC_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FUNC %d "  , func   );
    if ((ctsien > Si2176_EXIT_BOOTLOADER_CMD_CTSIEN_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CTSIEN %d ", ctsien );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2176_EXIT_BOOTLOADER_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( func   & Si2176_EXIT_BOOTLOADER_CMD_FUNC_MASK   ) << Si2176_EXIT_BOOTLOADER_CMD_FUNC_LSB  |
                                         ( ctsien & Si2176_EXIT_BOOTLOADER_CMD_CTSIEN_MASK ) << Si2176_EXIT_BOOTLOADER_CMD_CTSIEN_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing EXIT_BOOTLOADER bytes!\n");
      return ERROR_Si2176_SENDING_COMMAND;
    }

    error_code = Si2176_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling EXIT_BOOTLOADER response\n");
      return error_code;
    }


    return NO_Si2176_ERROR;
}
#endif /* Si2176_EXIT_BOOTLOADER_CMD */
#ifdef    Si2176_FINE_TUNE_CMD
 /*---------------------------------------------------*/
/* Si2176_FINE_TUNE COMMAND                        */
/*---------------------------------------------------*/
unsigned char Si2176_L1_FINE_TUNE       (L1_Si2176_Context *api,
                                         unsigned char   persistence,
                                                   int   offset_500hz)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[4];
    unsigned char rspByteBuffer[1];
    api->rsp->fine_tune.STATUS = api->status;

    SiTRACE("Si2176 FINE_TUNE ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((persistence  > Si2176_FINE_TUNE_CMD_PERSISTENCE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("PERSISTENCE %d " , persistence  );
    if ((offset_500hz > Si2176_FINE_TUNE_CMD_OFFSET_500HZ_MAX)  || (offset_500hz < Si2176_FINE_TUNE_CMD_OFFSET_500HZ_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("OFFSET_500HZ %d ", offset_500hz );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2176_FINE_TUNE_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( persistence  & Si2176_FINE_TUNE_CMD_PERSISTENCE_MASK  ) << Si2176_FINE_TUNE_CMD_PERSISTENCE_LSB );
    cmdByteBuffer[2] = (unsigned char) ( ( offset_500hz & Si2176_FINE_TUNE_CMD_OFFSET_500HZ_MASK ) << Si2176_FINE_TUNE_CMD_OFFSET_500HZ_LSB);
    cmdByteBuffer[3] = (unsigned char) ((( offset_500hz & Si2176_FINE_TUNE_CMD_OFFSET_500HZ_MASK ) << Si2176_FINE_TUNE_CMD_OFFSET_500HZ_LSB)>>8);

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing FINE_TUNE bytes!\n");
      return ERROR_Si2176_SENDING_COMMAND;
    }

    error_code = Si2176_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling FINE_TUNE response\n");
      return error_code;
    }


    return NO_Si2176_ERROR;
}
#endif /* Si2176_FINE_TUNE_CMD */
#ifdef    Si2176_GET_PROPERTY_CMD
 /*---------------------------------------------------*/
/* Si2176_GET_PROPERTY COMMAND                     */
/*---------------------------------------------------*/
unsigned char Si2176_L1_GET_PROPERTY    (L1_Si2176_Context *api,
                                         unsigned char   reserved,
                                         unsigned int    prop)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[4];
    unsigned char rspByteBuffer[4];
    api->rsp->get_property.STATUS = api->status;

    SiTRACE("Si2176 GET_PROPERTY ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((reserved > Si2176_GET_PROPERTY_CMD_RESERVED_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED %d ", reserved );
    SiTRACE("PROP %d "    , prop     );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2176_GET_PROPERTY_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( reserved & Si2176_GET_PROPERTY_CMD_RESERVED_MASK ) << Si2176_GET_PROPERTY_CMD_RESERVED_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( prop     & Si2176_GET_PROPERTY_CMD_PROP_MASK     ) << Si2176_GET_PROPERTY_CMD_PROP_LSB    );
    cmdByteBuffer[3] = (unsigned char) ((( prop     & Si2176_GET_PROPERTY_CMD_PROP_MASK     ) << Si2176_GET_PROPERTY_CMD_PROP_LSB    )>>8);

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing GET_PROPERTY bytes!\n");
      return ERROR_Si2176_SENDING_COMMAND;
    }

    error_code = Si2176_pollForResponse(api, 4, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling GET_PROPERTY response\n");
      return error_code;
    }

    api->rsp->get_property.reserved =   (( ( (rspByteBuffer[1]  )) >> Si2176_GET_PROPERTY_RESPONSE_RESERVED_LSB ) & Si2176_GET_PROPERTY_RESPONSE_RESERVED_MASK );
    api->rsp->get_property.data     =   (( ( (rspByteBuffer[2]  ) | (rspByteBuffer[3]  << 8 )) >> Si2176_GET_PROPERTY_RESPONSE_DATA_LSB     ) & Si2176_GET_PROPERTY_RESPONSE_DATA_MASK     );

    return NO_Si2176_ERROR;
}
#endif /* Si2176_GET_PROPERTY_CMD */
#ifdef    Si2176_GET_REV_CMD
 /*---------------------------------------------------*/
/* Si2176_GET_REV COMMAND                          */
/*---------------------------------------------------*/
unsigned char Si2176_L1_GET_REV         (L1_Si2176_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[10];
    api->rsp->get_rev.STATUS = api->status;

    SiTRACE("Si2176 GET_REV ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2176_GET_REV_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing GET_REV bytes!\n");
      return ERROR_Si2176_SENDING_COMMAND;
    }

    error_code = Si2176_pollForResponse(api, 10, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling GET_REV response\n");
      return error_code;
    }

    api->rsp->get_rev.pn       =   (( ( (rspByteBuffer[1]  )) >> Si2176_GET_REV_RESPONSE_PN_LSB       ) & Si2176_GET_REV_RESPONSE_PN_MASK       );
    api->rsp->get_rev.fwmajor  =   (( ( (rspByteBuffer[2]  )) >> Si2176_GET_REV_RESPONSE_FWMAJOR_LSB  ) & Si2176_GET_REV_RESPONSE_FWMAJOR_MASK  );
    api->rsp->get_rev.fwminor  =   (( ( (rspByteBuffer[3]  )) >> Si2176_GET_REV_RESPONSE_FWMINOR_LSB  ) & Si2176_GET_REV_RESPONSE_FWMINOR_MASK  );
    api->rsp->get_rev.patch    =   (( ( (rspByteBuffer[4]  ) | (rspByteBuffer[5]  << 8 )) >> Si2176_GET_REV_RESPONSE_PATCH_LSB    ) & Si2176_GET_REV_RESPONSE_PATCH_MASK    );
    api->rsp->get_rev.cmpmajor =   (( ( (rspByteBuffer[6]  )) >> Si2176_GET_REV_RESPONSE_CMPMAJOR_LSB ) & Si2176_GET_REV_RESPONSE_CMPMAJOR_MASK );
    api->rsp->get_rev.cmpminor =   (( ( (rspByteBuffer[7]  )) >> Si2176_GET_REV_RESPONSE_CMPMINOR_LSB ) & Si2176_GET_REV_RESPONSE_CMPMINOR_MASK );
    api->rsp->get_rev.cmpbuild =   (( ( (rspByteBuffer[8]  )) >> Si2176_GET_REV_RESPONSE_CMPBUILD_LSB ) & Si2176_GET_REV_RESPONSE_CMPBUILD_MASK );
    api->rsp->get_rev.chiprev  =   (( ( (rspByteBuffer[9]  )) >> Si2176_GET_REV_RESPONSE_CHIPREV_LSB  ) & Si2176_GET_REV_RESPONSE_CHIPREV_MASK  );

    return NO_Si2176_ERROR;
}
#endif /* Si2176_GET_REV_CMD */
#ifdef    Si2176_PART_INFO_CMD
 /*---------------------------------------------------*/
/* Si2176_PART_INFO COMMAND                        */
/*---------------------------------------------------*/
unsigned char Si2176_L1_PART_INFO       (L1_Si2176_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[13];
    api->rsp->part_info.STATUS = api->status;

    SiTRACE("Si2176 PART_INFO ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2176_PART_INFO_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing PART_INFO bytes!\n");
      return ERROR_Si2176_SENDING_COMMAND;
    }

    error_code = Si2176_pollForResponse(api, 13, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling PART_INFO response\n");
      return error_code;
    }

    api->rsp->part_info.chiprev  =   (( ( (rspByteBuffer[1]  )) >> Si2176_PART_INFO_RESPONSE_CHIPREV_LSB  ) & Si2176_PART_INFO_RESPONSE_CHIPREV_MASK  );
    api->rsp->part_info.part     =   (( ( (rspByteBuffer[2]  )) >> Si2176_PART_INFO_RESPONSE_PART_LSB     ) & Si2176_PART_INFO_RESPONSE_PART_MASK     );
    api->rsp->part_info.pmajor   =   (( ( (rspByteBuffer[3]  )) >> Si2176_PART_INFO_RESPONSE_PMAJOR_LSB   ) & Si2176_PART_INFO_RESPONSE_PMAJOR_MASK   );
    api->rsp->part_info.pminor   =   (( ( (rspByteBuffer[4]  )) >> Si2176_PART_INFO_RESPONSE_PMINOR_LSB   ) & Si2176_PART_INFO_RESPONSE_PMINOR_MASK   );
    api->rsp->part_info.pbuild   =   (( ( (rspByteBuffer[5]  )) >> Si2176_PART_INFO_RESPONSE_PBUILD_LSB   ) & Si2176_PART_INFO_RESPONSE_PBUILD_MASK   );
    api->rsp->part_info.reserved =   (( ( (rspByteBuffer[6]  ) | (rspByteBuffer[7]  << 8 )) >> Si2176_PART_INFO_RESPONSE_RESERVED_LSB ) & Si2176_PART_INFO_RESPONSE_RESERVED_MASK );
    api->rsp->part_info.serial   =   (( ( (rspByteBuffer[8]  ) | (rspByteBuffer[9]  << 8 ) | (rspByteBuffer[10] << 16 ) | (rspByteBuffer[11] << 24 )) >> Si2176_PART_INFO_RESPONSE_SERIAL_LSB   ) & Si2176_PART_INFO_RESPONSE_SERIAL_MASK   );
    api->rsp->part_info.romid    =   (( ( (rspByteBuffer[12] )) >> Si2176_PART_INFO_RESPONSE_ROMID_LSB    ) & Si2176_PART_INFO_RESPONSE_ROMID_MASK    );

    return NO_Si2176_ERROR;
}
#endif /* Si2176_PART_INFO_CMD */
#ifdef    Si2176_POWER_DOWN_CMD
 /*---------------------------------------------------*/
/* Si2176_POWER_DOWN COMMAND                       */
/*---------------------------------------------------*/
unsigned char Si2176_L1_POWER_DOWN      (L1_Si2176_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[1];
    api->rsp->power_down.STATUS = api->status;

    SiTRACE("Si2176 POWER_DOWN ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2176_POWER_DOWN_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing POWER_DOWN bytes!\n");
      return ERROR_Si2176_SENDING_COMMAND;
    }

    error_code = Si2176_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling POWER_DOWN response\n");
      return error_code;
    }


    return NO_Si2176_ERROR;
}
#endif /* Si2176_POWER_DOWN_CMD */
#ifdef    Si2176_POWER_UP_CMD
 /*---------------------------------------------------*/
/* Si2176_POWER_UP COMMAND                         */
/*---------------------------------------------------*/
unsigned char Si2176_L1_POWER_UP        (L1_Si2176_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   reserved1,
                                         unsigned char   reserved2,
                                         unsigned char   reserved3,
                                         unsigned char   clock_mode,
                                         unsigned char   clock_freq,
                                         unsigned char   addr_mode,
                                         unsigned char   func,
                                         unsigned char   ctsien,
                                         unsigned char   wake_up)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[9];
    unsigned char rspByteBuffer[1];
    api->rsp->power_up.STATUS = api->status;

    SiTRACE("Si2176 POWER_UP ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode    > Si2176_POWER_UP_CMD_SUBCODE_MAX   )  || (subcode    < Si2176_POWER_UP_CMD_SUBCODE_MIN   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "   , subcode    );
    if ((reserved1  > Si2176_POWER_UP_CMD_RESERVED1_MAX )  || (reserved1  < Si2176_POWER_UP_CMD_RESERVED1_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED1 %d " , reserved1  );
    if ((reserved2  > Si2176_POWER_UP_CMD_RESERVED2_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED2 %d " , reserved2  );
    if ((reserved3  > Si2176_POWER_UP_CMD_RESERVED3_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED3 %d " , reserved3  );
    if ((clock_mode > Si2176_POWER_UP_CMD_CLOCK_MODE_MAX)  || (clock_mode < Si2176_POWER_UP_CMD_CLOCK_MODE_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CLOCK_MODE %d ", clock_mode );
    if ((clock_freq > Si2176_POWER_UP_CMD_CLOCK_FREQ_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CLOCK_FREQ %d ", clock_freq );
    if ((addr_mode  > Si2176_POWER_UP_CMD_ADDR_MODE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("ADDR_MODE %d " , addr_mode  );
    if ((func       > Si2176_POWER_UP_CMD_FUNC_MAX      ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FUNC %d "      , func       );
    if ((ctsien     > Si2176_POWER_UP_CMD_CTSIEN_MAX    ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CTSIEN %d "    , ctsien     );
    if ((wake_up    > Si2176_POWER_UP_CMD_WAKE_UP_MAX   )  || (wake_up    < Si2176_POWER_UP_CMD_WAKE_UP_MIN   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("WAKE_UP %d "   , wake_up    );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2176_POWER_UP_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode    & Si2176_POWER_UP_CMD_SUBCODE_MASK    ) << Si2176_POWER_UP_CMD_SUBCODE_LSB   );
    cmdByteBuffer[2] = (unsigned char) ( ( reserved1  & Si2176_POWER_UP_CMD_RESERVED1_MASK  ) << Si2176_POWER_UP_CMD_RESERVED1_LSB );
    cmdByteBuffer[3] = (unsigned char) ( ( reserved2  & Si2176_POWER_UP_CMD_RESERVED2_MASK  ) << Si2176_POWER_UP_CMD_RESERVED2_LSB );
    cmdByteBuffer[4] = (unsigned char) ( ( reserved3  & Si2176_POWER_UP_CMD_RESERVED3_MASK  ) << Si2176_POWER_UP_CMD_RESERVED3_LSB );
    cmdByteBuffer[5] = (unsigned char) ( ( clock_mode & Si2176_POWER_UP_CMD_CLOCK_MODE_MASK ) << Si2176_POWER_UP_CMD_CLOCK_MODE_LSB|
                                         ( clock_freq & Si2176_POWER_UP_CMD_CLOCK_FREQ_MASK ) << Si2176_POWER_UP_CMD_CLOCK_FREQ_LSB);
    cmdByteBuffer[6] = (unsigned char) ( ( addr_mode  & Si2176_POWER_UP_CMD_ADDR_MODE_MASK  ) << Si2176_POWER_UP_CMD_ADDR_MODE_LSB );
    cmdByteBuffer[7] = (unsigned char) ( ( func       & Si2176_POWER_UP_CMD_FUNC_MASK       ) << Si2176_POWER_UP_CMD_FUNC_LSB      |
                                         ( ctsien     & Si2176_POWER_UP_CMD_CTSIEN_MASK     ) << Si2176_POWER_UP_CMD_CTSIEN_LSB    );
    cmdByteBuffer[8] = (unsigned char) ( ( wake_up    & Si2176_POWER_UP_CMD_WAKE_UP_MASK    ) << Si2176_POWER_UP_CMD_WAKE_UP_LSB   );

    if (L0_WriteCommandBytes(api->i2c, 9, cmdByteBuffer) != 9) {
      SiTRACE("Error writing POWER_UP bytes!\n");
      return ERROR_Si2176_SENDING_COMMAND;
    }

    error_code = Si2176_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling POWER_UP response\n");
      return error_code;
    }


    return NO_Si2176_ERROR;
}
#endif /* Si2176_POWER_UP_CMD */
#ifdef    Si2176_SET_PROPERTY_CMD
 /*---------------------------------------------------*/
/* Si2176_SET_PROPERTY COMMAND                     */
/*---------------------------------------------------*/
unsigned char Si2176_L1_SET_PROPERTY    (L1_Si2176_Context *api,
                                         unsigned char   reserved,
                                         unsigned int    prop,
                                         unsigned int    data)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[6];
    unsigned char rspByteBuffer[4];
    api->rsp->set_property.STATUS = api->status;

    SiTRACE("Si2176 SET_PROPERTY ");
  #ifdef   DEBUG_RANGE_CHECK
    SiTRACE("RESERVED %d ", reserved );
    SiTRACE("PROP %d "    , prop     );
    SiTRACE("DATA %d "    , data     );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2176_SET_PROPERTY_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( reserved & Si2176_SET_PROPERTY_CMD_RESERVED_MASK ) << Si2176_SET_PROPERTY_CMD_RESERVED_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( prop     & Si2176_SET_PROPERTY_CMD_PROP_MASK     ) << Si2176_SET_PROPERTY_CMD_PROP_LSB    );
    cmdByteBuffer[3] = (unsigned char) ((( prop     & Si2176_SET_PROPERTY_CMD_PROP_MASK     ) << Si2176_SET_PROPERTY_CMD_PROP_LSB    )>>8);
    cmdByteBuffer[4] = (unsigned char) ( ( data     & Si2176_SET_PROPERTY_CMD_DATA_MASK     ) << Si2176_SET_PROPERTY_CMD_DATA_LSB    );
    cmdByteBuffer[5] = (unsigned char) ((( data     & Si2176_SET_PROPERTY_CMD_DATA_MASK     ) << Si2176_SET_PROPERTY_CMD_DATA_LSB    )>>8);

    if (L0_WriteCommandBytes(api->i2c, 6, cmdByteBuffer) != 6) {
      SiTRACE("Error writing SET_PROPERTY bytes!\n");
      return ERROR_Si2176_SENDING_COMMAND;
    }

    error_code = Si2176_pollForResponse(api, 4, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling SET_PROPERTY response\n");
      return error_code;
    }

    api->rsp->set_property.reserved =   (( ( (rspByteBuffer[1]  )) >> Si2176_SET_PROPERTY_RESPONSE_RESERVED_LSB ) & Si2176_SET_PROPERTY_RESPONSE_RESERVED_MASK );
    api->rsp->set_property.data     =   (( ( (rspByteBuffer[2]  ) | (rspByteBuffer[3]  << 8 )) >> Si2176_SET_PROPERTY_RESPONSE_DATA_LSB     ) & Si2176_SET_PROPERTY_RESPONSE_DATA_MASK     );

    return NO_Si2176_ERROR;
}
#endif /* Si2176_SET_PROPERTY_CMD */
#ifdef    Si2176_STANDBY_CMD
 /*---------------------------------------------------*/
/* Si2176_STANDBY COMMAND                          */
/*---------------------------------------------------*/
unsigned char Si2176_L1_STANDBY         (L1_Si2176_Context *api,
                                         unsigned char   type)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];
    api->rsp->standby.STATUS = api->status;

    SiTRACE("Si2176 STANDBY ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((type > Si2176_STANDBY_CMD_TYPE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("TYPE %d ", type );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2176_STANDBY_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( type & Si2176_STANDBY_CMD_TYPE_MASK ) << Si2176_STANDBY_CMD_TYPE_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing STANDBY bytes!\n");
      return ERROR_Si2176_SENDING_COMMAND;
    }

    error_code = Si2176_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling STANDBY response\n");
      return error_code;
    }


    return NO_Si2176_ERROR;
}
#endif /* Si2176_STANDBY_CMD */
#ifdef    Si2176_TUNER_STATUS_CMD
 /*---------------------------------------------------*/
/* Si2176_TUNER_STATUS COMMAND                     */
/*---------------------------------------------------*/
unsigned char Si2176_L1_TUNER_STATUS    (L1_Si2176_Context *api,
                                         unsigned char   intack)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[12];
    api->rsp->tuner_status.STATUS = api->status;

    SiTRACE("Si2176 TUNER_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((intack > Si2176_TUNER_STATUS_CMD_INTACK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("INTACK %d ", intack );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2176_TUNER_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si2176_TUNER_STATUS_CMD_INTACK_MASK ) << Si2176_TUNER_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing TUNER_STATUS bytes!\n");
      return ERROR_Si2176_SENDING_COMMAND;
    }

    error_code = Si2176_pollForResponse(api, 12, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling TUNER_STATUS response\n");
      return error_code;
    }

    api->rsp->tuner_status.tcint    =   (( ( (rspByteBuffer[1]  )) >> Si2176_TUNER_STATUS_RESPONSE_TCINT_LSB    ) & Si2176_TUNER_STATUS_RESPONSE_TCINT_MASK    );
    api->rsp->tuner_status.rssilint =   (( ( (rspByteBuffer[1]  )) >> Si2176_TUNER_STATUS_RESPONSE_RSSILINT_LSB ) & Si2176_TUNER_STATUS_RESPONSE_RSSILINT_MASK );
    api->rsp->tuner_status.rssihint =   (( ( (rspByteBuffer[1]  )) >> Si2176_TUNER_STATUS_RESPONSE_RSSIHINT_LSB ) & Si2176_TUNER_STATUS_RESPONSE_RSSIHINT_MASK );
    api->rsp->tuner_status.tc       =   (( ( (rspByteBuffer[2]  )) >> Si2176_TUNER_STATUS_RESPONSE_TC_LSB       ) & Si2176_TUNER_STATUS_RESPONSE_TC_MASK       );
    api->rsp->tuner_status.rssil    =   (( ( (rspByteBuffer[2]  )) >> Si2176_TUNER_STATUS_RESPONSE_RSSIL_LSB    ) & Si2176_TUNER_STATUS_RESPONSE_RSSIL_MASK    );
    api->rsp->tuner_status.rssih    =   (( ( (rspByteBuffer[2]  )) >> Si2176_TUNER_STATUS_RESPONSE_RSSIH_LSB    ) & Si2176_TUNER_STATUS_RESPONSE_RSSIH_MASK    );
    api->rsp->tuner_status.rssi     = (((( ( (rspByteBuffer[3]  )) >> Si2176_TUNER_STATUS_RESPONSE_RSSI_LSB     ) & Si2176_TUNER_STATUS_RESPONSE_RSSI_MASK) <<Si2176_TUNER_STATUS_RESPONSE_RSSI_SHIFT ) >>Si2176_TUNER_STATUS_RESPONSE_RSSI_SHIFT     );
    api->rsp->tuner_status.freq     =   (( ( (rspByteBuffer[4]  ) | (rspByteBuffer[5]  << 8 ) | (rspByteBuffer[6]  << 16 ) | (rspByteBuffer[7]  << 24 )) >> Si2176_TUNER_STATUS_RESPONSE_FREQ_LSB     ) & Si2176_TUNER_STATUS_RESPONSE_FREQ_MASK     );
    api->rsp->tuner_status.mode     =   (( ( (rspByteBuffer[8]  )) >> Si2176_TUNER_STATUS_RESPONSE_MODE_LSB     ) & Si2176_TUNER_STATUS_RESPONSE_MODE_MASK     );
    api->rsp->tuner_status.vco_code = (((( ( (rspByteBuffer[10] ) | (rspByteBuffer[11] << 8 )) >> Si2176_TUNER_STATUS_RESPONSE_VCO_CODE_LSB ) & Si2176_TUNER_STATUS_RESPONSE_VCO_CODE_MASK) <<Si2176_TUNER_STATUS_RESPONSE_VCO_CODE_SHIFT ) >>Si2176_TUNER_STATUS_RESPONSE_VCO_CODE_SHIFT );

    return NO_Si2176_ERROR;
}
#endif /* Si2176_TUNER_STATUS_CMD */
#ifdef    Si2176_TUNER_TUNE_FREQ_CMD
 /*---------------------------------------------------*/
/* Si2176_TUNER_TUNE_FREQ COMMAND                  */
/*---------------------------------------------------*/
unsigned char Si2176_L1_TUNER_TUNE_FREQ (L1_Si2176_Context *api,
                                         unsigned char   mode,
                                         unsigned long   freq)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[8];
    unsigned char rspByteBuffer[1];
    api->rsp->tuner_tune_freq.STATUS = api->status;

    SiTRACE("Si2176 TUNER_TUNE_FREQ ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((mode > Si2176_TUNER_TUNE_FREQ_CMD_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("MODE %d ", mode );
    if ((freq > Si2176_TUNER_TUNE_FREQ_CMD_FREQ_MAX)  || (freq < Si2176_TUNER_TUNE_FREQ_CMD_FREQ_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FREQ %d ", freq );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2176_TUNER_TUNE_FREQ_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( mode & Si2176_TUNER_TUNE_FREQ_CMD_MODE_MASK ) << Si2176_TUNER_TUNE_FREQ_CMD_MODE_LSB);
    cmdByteBuffer[2] = (unsigned char)0x00;
    cmdByteBuffer[3] = (unsigned char)0x00;
    cmdByteBuffer[4] = (unsigned char) ( ( freq & Si2176_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si2176_TUNER_TUNE_FREQ_CMD_FREQ_LSB);
    cmdByteBuffer[5] = (unsigned char) ((( freq & Si2176_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si2176_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>8);
    cmdByteBuffer[6] = (unsigned char) ((( freq & Si2176_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si2176_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>16);
    cmdByteBuffer[7] = (unsigned char) ((( freq & Si2176_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si2176_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>24);

    if (L0_WriteCommandBytes(api->i2c, 8, cmdByteBuffer) != 8) {
      SiTRACE("Error writing TUNER_TUNE_FREQ bytes!\n");
      return ERROR_Si2176_SENDING_COMMAND;
    }

    error_code = Si2176_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling TUNER_TUNE_FREQ response\n");
      return error_code;
    }


    return NO_Si2176_ERROR;
}
#endif /* Si2176_TUNER_TUNE_FREQ_CMD */
/* _commands_insertion_point */

/* _send_command2_insertion_start */

  /* --------------------------------------------*/
  /* SEND_COMMAND2 FUNCTION                      */
  /* --------------------------------------------*/
unsigned char   Si2176_L1_SendCommand2(L1_Si2176_Context *api, unsigned int cmd_code) {
    switch (cmd_code) {
    #ifdef        Si2176_AGC_OVERRIDE_CMD
     case         Si2176_AGC_OVERRIDE_CMD_CODE:
       return Si2176_L1_AGC_OVERRIDE (api, api->cmd->agc_override.force_max_gain, api->cmd->agc_override.force_top_gain );
     break;
    #endif /*     Si2176_AGC_OVERRIDE_CMD */
    #ifdef        Si2176_ATV_RESTART_CMD
     case         Si2176_ATV_RESTART_CMD_CODE:
       return Si2176_L1_ATV_RESTART (api, api->cmd->atv_restart.mode );
     break;
    #endif /*     Si2176_ATV_RESTART_CMD */
    #ifdef        Si2176_ATV_STATUS_CMD
     case         Si2176_ATV_STATUS_CMD_CODE:
       return Si2176_L1_ATV_STATUS (api, api->cmd->atv_status.intack );
     break;
    #endif /*     Si2176_ATV_STATUS_CMD */
    #ifdef        Si2176_CONFIG_PINS_CMD
     case         Si2176_CONFIG_PINS_CMD_CODE:
       return Si2176_L1_CONFIG_PINS (api, api->cmd->config_pins.gpio1_mode, api->cmd->config_pins.gpio1_read, api->cmd->config_pins.gpio2_mode, api->cmd->config_pins.gpio2_read, api->cmd->config_pins.gpio3_mode, api->cmd->config_pins.gpio3_read, api->cmd->config_pins.bclk1_mode, api->cmd->config_pins.bclk1_read, api->cmd->config_pins.xout_mode );
     break;
    #endif /*     Si2176_CONFIG_PINS_CMD */
    #ifdef        Si2176_DTV_RESTART_CMD
     case         Si2176_DTV_RESTART_CMD_CODE:
       return Si2176_L1_DTV_RESTART (api );
     break;
    #endif /*     Si2176_DTV_RESTART_CMD */
    #ifdef        Si2176_DTV_STATUS_CMD
     case         Si2176_DTV_STATUS_CMD_CODE:
       return Si2176_L1_DTV_STATUS (api, api->cmd->dtv_status.intack );
     break;
    #endif /*     Si2176_DTV_STATUS_CMD */
    #ifdef        Si2176_EXIT_BOOTLOADER_CMD
     case         Si2176_EXIT_BOOTLOADER_CMD_CODE:
       return Si2176_L1_EXIT_BOOTLOADER (api, api->cmd->exit_bootloader.func, api->cmd->exit_bootloader.ctsien );
     break;
    #endif /*     Si2176_EXIT_BOOTLOADER_CMD */
    #ifdef        Si2176_FINE_TUNE_CMD
     case         Si2176_FINE_TUNE_CMD_CODE:
       return Si2176_L1_FINE_TUNE (api, api->cmd->fine_tune.persistence, api->cmd->fine_tune.offset_500hz );
     break;
    #endif /*     Si2176_FINE_TUNE_CMD */
    #ifdef        Si2176_GET_PROPERTY_CMD
     case         Si2176_GET_PROPERTY_CMD_CODE:
       return Si2176_L1_GET_PROPERTY (api, api->cmd->get_property.reserved, api->cmd->get_property.prop );
     break;
    #endif /*     Si2176_GET_PROPERTY_CMD */
    #ifdef        Si2176_GET_REV_CMD
     case         Si2176_GET_REV_CMD_CODE:
       return Si2176_L1_GET_REV (api );
     break;
    #endif /*     Si2176_GET_REV_CMD */
    #ifdef        Si2176_PART_INFO_CMD
     case         Si2176_PART_INFO_CMD_CODE:
       return Si2176_L1_PART_INFO (api );
     break;
    #endif /*     Si2176_PART_INFO_CMD */
    #ifdef        Si2176_POWER_DOWN_CMD
     case         Si2176_POWER_DOWN_CMD_CODE:
       return Si2176_L1_POWER_DOWN (api );
     break;
    #endif /*     Si2176_POWER_DOWN_CMD */
    #ifdef        Si2176_POWER_UP_CMD
     case         Si2176_POWER_UP_CMD_CODE:
       return Si2176_L1_POWER_UP (api, api->cmd->power_up.subcode, api->cmd->power_up.reserved1, api->cmd->power_up.reserved2, api->cmd->power_up.reserved3, api->cmd->power_up.clock_mode, api->cmd->power_up.clock_freq, api->cmd->power_up.addr_mode, api->cmd->power_up.func, api->cmd->power_up.ctsien, api->cmd->power_up.wake_up );
     break;
    #endif /*     Si2176_POWER_UP_CMD */
    #ifdef        Si2176_SET_PROPERTY_CMD
     case         Si2176_SET_PROPERTY_CMD_CODE:
       return Si2176_L1_SET_PROPERTY (api, api->cmd->set_property.reserved, api->cmd->set_property.prop, api->cmd->set_property.data );
     break;
    #endif /*     Si2176_SET_PROPERTY_CMD */
    #ifdef        Si2176_STANDBY_CMD
     case         Si2176_STANDBY_CMD_CODE:
       return Si2176_L1_STANDBY (api, api->cmd->standby.type );
     break;
    #endif /*     Si2176_STANDBY_CMD */
    #ifdef        Si2176_TUNER_STATUS_CMD
     case         Si2176_TUNER_STATUS_CMD_CODE:
       return Si2176_L1_TUNER_STATUS (api, api->cmd->tuner_status.intack );
     break;
    #endif /*     Si2176_TUNER_STATUS_CMD */
    #ifdef        Si2176_TUNER_TUNE_FREQ_CMD
     case         Si2176_TUNER_TUNE_FREQ_CMD_CODE:
       return Si2176_L1_TUNER_TUNE_FREQ (api, api->cmd->tuner_tune_freq.mode, api->cmd->tuner_tune_freq.freq );
     break;
    #endif /*     Si2176_TUNER_TUNE_FREQ_CMD */
   default : break;
    }
     return 0;
  }
  /* _send_command2_insertion_point */

#ifdef    Si2176_GET_COMMAND_STRINGS
/* _get_command_response_string_insertion_start */

  /* --------------------------------------------*/
  /* GET_COMMAND_RESPONSE_STRING FUNCTION        */
  /* --------------------------------------------*/
unsigned char   Si2176_L1_GetCommandResponseString(L1_Si2176_Context *api, unsigned int cmd_code, char *separator, char *msg) {
    switch (cmd_code) {
    #ifdef        Si2176_AGC_OVERRIDE_CMD
     case         Si2176_AGC_OVERRIDE_CMD_CODE:
      sprintf(msg,"AGC_OVERRIDE ");
       strcat(msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->agc_override.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->agc_override.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->agc_override.STATUS->tunint);
       strcat(msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->agc_override.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->agc_override.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->agc_override.STATUS->atvint);
       strcat(msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->agc_override.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->agc_override.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->agc_override.STATUS->dtvint);
       strcat(msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->agc_override.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->agc_override.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->agc_override.STATUS->err);
       strcat(msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->agc_override.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->agc_override.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->agc_override.STATUS->cts);
     break;
    #endif /*     Si2176_AGC_OVERRIDE_CMD */

    #ifdef        Si2176_ATV_RESTART_CMD
     case         Si2176_ATV_RESTART_CMD_CODE:
      sprintf(msg,"ATV_RESTART ");
       strcat(msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->atv_restart.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_restart.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->atv_restart.STATUS->tunint);
       strcat(msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->atv_restart.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_restart.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->atv_restart.STATUS->atvint);
       strcat(msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->atv_restart.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_restart.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->atv_restart.STATUS->dtvint);
       strcat(msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->atv_restart.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->atv_restart.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->atv_restart.STATUS->err);
       strcat(msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->atv_restart.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->atv_restart.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->atv_restart.STATUS->cts);
     break;
    #endif /*     Si2176_ATV_RESTART_CMD */

    #ifdef        Si2176_ATV_STATUS_CMD
     case         Si2176_ATV_STATUS_CMD_CODE:
      sprintf(msg,"ATV_STATUS ");
       strcat(msg,separator); strcat(msg,"-TUNINT           ");
           if  (api->rsp->atv_status.STATUS->tunint           ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_status.STATUS->tunint           ==     1) strcat(msg,"TRIGGERED    ");
      else                                                             sprintf(msg,"%s%d", msg, api->rsp->atv_status.STATUS->tunint);
       strcat(msg,separator); strcat(msg,"-ATVINT           ");
           if  (api->rsp->atv_status.STATUS->atvint           ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_status.STATUS->atvint           ==     1) strcat(msg,"TRIGGERED    ");
      else                                                             sprintf(msg,"%s%d", msg, api->rsp->atv_status.STATUS->atvint);
       strcat(msg,separator); strcat(msg,"-DTVINT           ");
           if  (api->rsp->atv_status.STATUS->dtvint           ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_status.STATUS->dtvint           ==     1) strcat(msg,"TRIGGERED    ");
      else                                                             sprintf(msg,"%s%d", msg, api->rsp->atv_status.STATUS->dtvint);
       strcat(msg,separator); strcat(msg,"-ERR              ");
           if  (api->rsp->atv_status.STATUS->err              ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->atv_status.STATUS->err              ==     0) strcat(msg,"NO_ERROR");
      else                                                             sprintf(msg,"%s%d", msg, api->rsp->atv_status.STATUS->err);
       strcat(msg,separator); strcat(msg,"-CTS              ");
           if  (api->rsp->atv_status.STATUS->cts              ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->atv_status.STATUS->cts              ==     0) strcat(msg,"WAIT     ");
      else                                                             sprintf(msg,"%s%d", msg, api->rsp->atv_status.STATUS->cts);
       strcat(msg,separator); strcat(msg,"-CHLINT           ");
           if  (api->rsp->atv_status.chlint           ==     1) strcat(msg,"CHANGED  ");
      else if  (api->rsp->atv_status.chlint           ==     0) strcat(msg,"NO_CHANGE");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->atv_status.chlint);
       strcat(msg,separator); strcat(msg,"-PCLINT           ");
           if  (api->rsp->atv_status.pclint           ==     1) strcat(msg,"CHANGED  ");
      else if  (api->rsp->atv_status.pclint           ==     0) strcat(msg,"NO_CHANGE");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->atv_status.pclint);
       strcat(msg,separator); strcat(msg,"-DLINT            ");
           if  (api->rsp->atv_status.dlint            ==     1) strcat(msg,"CHANGED  ");
      else if  (api->rsp->atv_status.dlint            ==     0) strcat(msg,"NO_CHANGE");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->atv_status.dlint);
       strcat(msg,separator); strcat(msg,"-SNRLINT          ");
           if  (api->rsp->atv_status.snrlint          ==     1) strcat(msg,"CHANGED  ");
      else if  (api->rsp->atv_status.snrlint          ==     0) strcat(msg,"NO_CHANGE");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->atv_status.snrlint);
       strcat(msg,separator); strcat(msg,"-SNRHINT          ");
           if  (api->rsp->atv_status.snrhint          ==     1) strcat(msg,"CHANGED  ");
      else if  (api->rsp->atv_status.snrhint          ==     0) strcat(msg,"NO_CHANGE");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->atv_status.snrhint);
       strcat(msg,separator); strcat(msg,"-CHL              ");
           if  (api->rsp->atv_status.chl              ==     1) strcat(msg,"CHANNEL   ");
      else if  (api->rsp->atv_status.chl              ==     0) strcat(msg,"NO_CHANNEL");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->atv_status.chl);
       strcat(msg,separator); strcat(msg,"-PCL              ");
           if  (api->rsp->atv_status.pcl              ==     1) strcat(msg,"LOCKED ");
      else if  (api->rsp->atv_status.pcl              ==     0) strcat(msg,"NO_LOCK");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->atv_status.pcl);
       strcat(msg,separator); strcat(msg,"-DL               ");
           if  (api->rsp->atv_status.dl               ==     1) strcat(msg,"LOCKED ");
      else if  (api->rsp->atv_status.dl               ==     0) strcat(msg,"NO_LOCK");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->atv_status.dl);
       strcat(msg,separator); strcat(msg,"-SNRL             ");
           if  (api->rsp->atv_status.snrl             ==     1) strcat(msg,"SNR_LOW    ");
      else if  (api->rsp->atv_status.snrl             ==     0) strcat(msg,"SNR_NOT_LOW");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->atv_status.snrl);
       strcat(msg,separator); strcat(msg,"-SNRH             ");
           if  (api->rsp->atv_status.snrh             ==     1) strcat(msg,"SNR_HIGH    ");
      else if  (api->rsp->atv_status.snrh             ==     0) strcat(msg,"SNR_NOT_HIGH");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->atv_status.snrh);
       strcat(msg,separator); strcat(msg,"-VIDEO_SNR        "); sprintf(msg,"%s%d", msg, api->rsp->atv_status.video_snr);
       strcat(msg,separator); strcat(msg,"-AFC_FREQ         "); sprintf(msg,"%s%d", msg, api->rsp->atv_status.afc_freq);
       strcat(msg,separator); strcat(msg,"-VIDEO_SC_SPACING "); sprintf(msg,"%s%d", msg, api->rsp->atv_status.video_sc_spacing);
       strcat(msg,separator); strcat(msg,"-VIDEO_SYS        ");
           if  (api->rsp->atv_status.video_sys        ==     0) strcat(msg,"B ");
      else if  (api->rsp->atv_status.video_sys        ==     5) strcat(msg,"DK");
      else if  (api->rsp->atv_status.video_sys        ==     1) strcat(msg,"GH");
      else if  (api->rsp->atv_status.video_sys        ==     4) strcat(msg,"I ");
      else if  (api->rsp->atv_status.video_sys        ==     6) strcat(msg,"L ");
      else if  (api->rsp->atv_status.video_sys        ==     7) strcat(msg,"LP");
      else if  (api->rsp->atv_status.video_sys        ==     2) strcat(msg,"M ");
      else if  (api->rsp->atv_status.video_sys        ==     3) strcat(msg,"N ");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->atv_status.video_sys);
       strcat(msg,separator); strcat(msg,"-COLOR            ");
           if  (api->rsp->atv_status.color            ==     0) strcat(msg,"PAL_NTSC");
      else if  (api->rsp->atv_status.color            ==     1) strcat(msg,"SECAM   ");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->atv_status.color);
       strcat(msg,separator); strcat(msg,"-TRANS            ");
           if  (api->rsp->atv_status.trans            ==     1) strcat(msg,"CABLE      ");
      else if  (api->rsp->atv_status.trans            ==     0) strcat(msg,"TERRESTRIAL");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->atv_status.trans);
       strcat(msg,separator); strcat(msg,"-AUDIO_SYS        ");
           if  (api->rsp->atv_status.audio_sys        ==     3) strcat(msg,"A2             ");
      else if  (api->rsp->atv_status.audio_sys        ==     4) strcat(msg,"A2_DK2         ");
      else if  (api->rsp->atv_status.audio_sys        ==     5) strcat(msg,"A2_DK3         ");
      else if  (api->rsp->atv_status.audio_sys        ==     9) strcat(msg,"A2_DK4         ");
      else if  (api->rsp->atv_status.audio_sys        ==     6) strcat(msg,"BTSC           ");
      else if  (api->rsp->atv_status.audio_sys        ==     7) strcat(msg,"EIAJ           ");
      else if  (api->rsp->atv_status.audio_sys        ==     1) strcat(msg,"MONO           ");
      else if  (api->rsp->atv_status.audio_sys        ==     2) strcat(msg,"MONO_NICAM     ");
      else if  (api->rsp->atv_status.audio_sys        ==    12) strcat(msg,"MONO_NICAM_10DB");
      else if  (api->rsp->atv_status.audio_sys        ==    11) strcat(msg,"MONO_NICAM_6DB ");
      else if  (api->rsp->atv_status.audio_sys        ==     0) strcat(msg,"RSVD           ");
      else if  (api->rsp->atv_status.audio_sys        ==     8) strcat(msg,"SCAN           ");
      else if  (api->rsp->atv_status.audio_sys        ==    10) strcat(msg,"WIDE_SCAN      ");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->atv_status.audio_sys);
       strcat(msg,separator); strcat(msg,"-AUDIO_DEMOD_MODE ");
           if  (api->rsp->atv_status.audio_demod_mode ==     1) strcat(msg,"AM ");
      else if  (api->rsp->atv_status.audio_demod_mode ==     2) strcat(msg,"FM1");
      else if  (api->rsp->atv_status.audio_demod_mode ==     3) strcat(msg,"FM2");
      else if  (api->rsp->atv_status.audio_demod_mode ==     0) strcat(msg,"SIF");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->atv_status.audio_demod_mode);
       strcat(msg,separator); strcat(msg,"-AUDIO_CHAN_BW    ");
           if  (api->rsp->atv_status.audio_chan_bw    ==     3) strcat(msg,"12X_OVERMOD   ");
      else if  (api->rsp->atv_status.audio_chan_bw    ==     8) strcat(msg,"150_KHZ_OFFSET");
      else if  (api->rsp->atv_status.audio_chan_bw    ==     5) strcat(msg,"15_KHZ_OFFSET ");
      else if  (api->rsp->atv_status.audio_chan_bw    ==     6) strcat(msg,"30_KHZ_OFFSET ");
      else if  (api->rsp->atv_status.audio_chan_bw    ==     1) strcat(msg,"4X_OVERMOD    ");
      else if  (api->rsp->atv_status.audio_chan_bw    ==     7) strcat(msg,"75_KHZ_OFFSET ");
      else if  (api->rsp->atv_status.audio_chan_bw    ==     4) strcat(msg,"7P5_KHZ_OFFSET");
      else if  (api->rsp->atv_status.audio_chan_bw    ==     2) strcat(msg,"8X_OVERMOD    ");
      else if  (api->rsp->atv_status.audio_chan_bw    ==     0) strcat(msg,"RSVD          ");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->atv_status.audio_chan_bw);
     break;
    #endif /*     Si2176_ATV_STATUS_CMD */

    #ifdef        Si2176_CONFIG_PINS_CMD
     case         Si2176_CONFIG_PINS_CMD_CODE:
      sprintf(msg,"CONFIG_PINS ");
       strcat(msg,separator); strcat(msg,"-TUNINT      ");
           if  (api->rsp->config_pins.STATUS->tunint      ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_pins.STATUS->tunint      ==     1) strcat(msg,"TRIGGERED    ");
      else                                                         sprintf(msg,"%s%d", msg, api->rsp->config_pins.STATUS->tunint);
       strcat(msg,separator); strcat(msg,"-ATVINT      ");
           if  (api->rsp->config_pins.STATUS->atvint      ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_pins.STATUS->atvint      ==     1) strcat(msg,"TRIGGERED    ");
      else                                                         sprintf(msg,"%s%d", msg, api->rsp->config_pins.STATUS->atvint);
       strcat(msg,separator); strcat(msg,"-DTVINT      ");
           if  (api->rsp->config_pins.STATUS->dtvint      ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_pins.STATUS->dtvint      ==     1) strcat(msg,"TRIGGERED    ");
      else                                                         sprintf(msg,"%s%d", msg, api->rsp->config_pins.STATUS->dtvint);
       strcat(msg,separator); strcat(msg,"-ERR         ");
           if  (api->rsp->config_pins.STATUS->err         ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->config_pins.STATUS->err         ==     0) strcat(msg,"NO_ERROR");
      else                                                         sprintf(msg,"%s%d", msg, api->rsp->config_pins.STATUS->err);
       strcat(msg,separator); strcat(msg,"-CTS         ");
           if  (api->rsp->config_pins.STATUS->cts         ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->config_pins.STATUS->cts         ==     0) strcat(msg,"WAIT     ");
      else                                                         sprintf(msg,"%s%d", msg, api->rsp->config_pins.STATUS->cts);
       strcat(msg,separator); strcat(msg,"-GPIO1_MODE  ");
           if  (api->rsp->config_pins.gpio1_mode  ==     1) strcat(msg,"DISABLE");
      else if  (api->rsp->config_pins.gpio1_mode  ==     2) strcat(msg,"DRIVE_0");
      else if  (api->rsp->config_pins.gpio1_mode  ==     3) strcat(msg,"DRIVE_1");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.gpio1_mode);
       strcat(msg,separator); strcat(msg,"-GPIO1_STATE ");
           if  (api->rsp->config_pins.gpio1_state ==     0) strcat(msg,"READ_0");
      else if  (api->rsp->config_pins.gpio1_state ==     1) strcat(msg,"READ_1");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.gpio1_state);
       strcat(msg,separator); strcat(msg,"-GPIO2_MODE  ");
           if  (api->rsp->config_pins.gpio2_mode  ==     1) strcat(msg,"DISABLE");
      else if  (api->rsp->config_pins.gpio2_mode  ==     2) strcat(msg,"DRIVE_0");
      else if  (api->rsp->config_pins.gpio2_mode  ==     3) strcat(msg,"DRIVE_1");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.gpio2_mode);
       strcat(msg,separator); strcat(msg,"-GPIO2_STATE ");
           if  (api->rsp->config_pins.gpio2_state ==     0) strcat(msg,"READ_0");
      else if  (api->rsp->config_pins.gpio2_state ==     1) strcat(msg,"READ_1");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.gpio2_state);
       strcat(msg,separator); strcat(msg,"-GPIO3_MODE  ");
           if  (api->rsp->config_pins.gpio3_mode  ==     1) strcat(msg,"DISABLE");
      else if  (api->rsp->config_pins.gpio3_mode  ==     2) strcat(msg,"DRIVE_0");
      else if  (api->rsp->config_pins.gpio3_mode  ==     3) strcat(msg,"DRIVE_1");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.gpio3_mode);
       strcat(msg,separator); strcat(msg,"-GPIO3_STATE ");
           if  (api->rsp->config_pins.gpio3_state ==     0) strcat(msg,"READ_0");
      else if  (api->rsp->config_pins.gpio3_state ==     1) strcat(msg,"READ_1");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.gpio3_state);
       strcat(msg,separator); strcat(msg,"-BCLK1_MODE  ");
           if  (api->rsp->config_pins.bclk1_mode  ==     1) strcat(msg,"DISABLE  ");
      else if  (api->rsp->config_pins.bclk1_mode  ==    10) strcat(msg,"XOUT     ");
      else if  (api->rsp->config_pins.bclk1_mode  ==    11) strcat(msg,"XOUT_HIGH");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.bclk1_mode);
       strcat(msg,separator); strcat(msg,"-BCLK1_STATE ");
           if  (api->rsp->config_pins.bclk1_state ==     0) strcat(msg,"READ_0");
      else if  (api->rsp->config_pins.bclk1_state ==     1) strcat(msg,"READ_1");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.bclk1_state);
       strcat(msg,separator); strcat(msg,"-XOUT_MODE   ");
           if  (api->rsp->config_pins.xout_mode   ==     1) strcat(msg,"DISABLE");
      else if  (api->rsp->config_pins.xout_mode   ==    10) strcat(msg,"XOUT   ");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.xout_mode);
     break;
    #endif /*     Si2176_CONFIG_PINS_CMD */

    #ifdef        Si2176_DTV_RESTART_CMD
     case         Si2176_DTV_RESTART_CMD_CODE:
      sprintf(msg,"DTV_RESTART ");
       strcat(msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->dtv_restart.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->dtv_restart.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->dtv_restart.STATUS->tunint);
       strcat(msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->dtv_restart.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->dtv_restart.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->dtv_restart.STATUS->atvint);
       strcat(msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->dtv_restart.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->dtv_restart.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->dtv_restart.STATUS->dtvint);
       strcat(msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->dtv_restart.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->dtv_restart.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->dtv_restart.STATUS->err);
       strcat(msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->dtv_restart.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->dtv_restart.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->dtv_restart.STATUS->cts);
     break;
    #endif /*     Si2176_DTV_RESTART_CMD */

    #ifdef        Si2176_DTV_STATUS_CMD
     case         Si2176_DTV_STATUS_CMD_CODE:
      sprintf(msg,"DTV_STATUS ");
       strcat(msg,separator); strcat(msg,"-TUNINT     ");
           if  (api->rsp->dtv_status.STATUS->tunint     ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->dtv_status.STATUS->tunint     ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->dtv_status.STATUS->tunint);
       strcat(msg,separator); strcat(msg,"-ATVINT     ");
           if  (api->rsp->dtv_status.STATUS->atvint     ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->dtv_status.STATUS->atvint     ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->dtv_status.STATUS->atvint);
       strcat(msg,separator); strcat(msg,"-DTVINT     ");
           if  (api->rsp->dtv_status.STATUS->dtvint     ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->dtv_status.STATUS->dtvint     ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->dtv_status.STATUS->dtvint);
       strcat(msg,separator); strcat(msg,"-ERR        ");
           if  (api->rsp->dtv_status.STATUS->err        ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->dtv_status.STATUS->err        ==     0) strcat(msg,"NO_ERROR");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->dtv_status.STATUS->err);
       strcat(msg,separator); strcat(msg,"-CTS        ");
           if  (api->rsp->dtv_status.STATUS->cts        ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->dtv_status.STATUS->cts        ==     0) strcat(msg,"WAIT     ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->dtv_status.STATUS->cts);
       strcat(msg,separator); strcat(msg,"-CHLINT     ");
           if  (api->rsp->dtv_status.chlint     ==     1) strcat(msg,"CHANGED  ");
      else if  (api->rsp->dtv_status.chlint     ==     0) strcat(msg,"NO_CHANGE");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->dtv_status.chlint);
       strcat(msg,separator); strcat(msg,"-CHL        ");
           if  (api->rsp->dtv_status.chl        ==     1) strcat(msg,"CHANNEL   ");
      else if  (api->rsp->dtv_status.chl        ==     0) strcat(msg,"NO_CHANNEL");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->dtv_status.chl);
       strcat(msg,separator); strcat(msg,"-BW         ");
           if  (api->rsp->dtv_status.bw         ==     6) strcat(msg,"BW_6MHZ");
      else if  (api->rsp->dtv_status.bw         ==     7) strcat(msg,"BW_7MHZ");
      else if  (api->rsp->dtv_status.bw         ==     8) strcat(msg,"BW_8MHZ");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->dtv_status.bw);
       strcat(msg,separator); strcat(msg,"-MODULATION ");
           if  (api->rsp->dtv_status.modulation ==     0) strcat(msg,"ATSC  ");
      else if  (api->rsp->dtv_status.modulation ==    15) strcat(msg,"CW    ");
      else if  (api->rsp->dtv_status.modulation ==     6) strcat(msg,"DTMB  ");
      else if  (api->rsp->dtv_status.modulation ==     3) strcat(msg,"DVBC  ");
      else if  (api->rsp->dtv_status.modulation ==     2) strcat(msg,"DVBT  ");
      else if  (api->rsp->dtv_status.modulation ==     5) strcat(msg,"ISDBC ");
      else if  (api->rsp->dtv_status.modulation ==     4) strcat(msg,"ISDBT ");
      else if  (api->rsp->dtv_status.modulation ==     1) strcat(msg,"QAM_US");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->dtv_status.modulation);
     break;
    #endif /*     Si2176_DTV_STATUS_CMD */

    #ifdef        Si2176_EXIT_BOOTLOADER_CMD
     case         Si2176_EXIT_BOOTLOADER_CMD_CODE:
      sprintf(msg,"EXIT_BOOTLOADER ");
       strcat(msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->exit_bootloader.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->exit_bootloader.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                        sprintf(msg,"%s%d", msg, api->rsp->exit_bootloader.STATUS->tunint);
       strcat(msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->exit_bootloader.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->exit_bootloader.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                        sprintf(msg,"%s%d", msg, api->rsp->exit_bootloader.STATUS->atvint);
       strcat(msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->exit_bootloader.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->exit_bootloader.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                        sprintf(msg,"%s%d", msg, api->rsp->exit_bootloader.STATUS->dtvint);
       strcat(msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->exit_bootloader.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->exit_bootloader.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                        sprintf(msg,"%s%d", msg, api->rsp->exit_bootloader.STATUS->err);
       strcat(msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->exit_bootloader.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->exit_bootloader.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                        sprintf(msg,"%s%d", msg, api->rsp->exit_bootloader.STATUS->cts);
     break;
    #endif /*     Si2176_EXIT_BOOTLOADER_CMD */

    #ifdef        Si2176_FINE_TUNE_CMD
     case         Si2176_FINE_TUNE_CMD_CODE:
      sprintf(msg,"FINE_TUNE ");
       strcat(msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->fine_tune.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->fine_tune.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, api->rsp->fine_tune.STATUS->tunint);
       strcat(msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->fine_tune.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->fine_tune.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, api->rsp->fine_tune.STATUS->atvint);
       strcat(msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->fine_tune.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->fine_tune.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, api->rsp->fine_tune.STATUS->dtvint);
       strcat(msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->fine_tune.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->fine_tune.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                  sprintf(msg,"%s%d", msg, api->rsp->fine_tune.STATUS->err);
       strcat(msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->fine_tune.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->fine_tune.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                  sprintf(msg,"%s%d", msg, api->rsp->fine_tune.STATUS->cts);
     break;
    #endif /*     Si2176_FINE_TUNE_CMD */

    #ifdef        Si2176_GET_PROPERTY_CMD
     case         Si2176_GET_PROPERTY_CMD_CODE:
      sprintf(msg,"GET_PROPERTY ");
       strcat(msg,separator); strcat(msg,"-TUNINT   ");
           if  (api->rsp->get_property.STATUS->tunint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->get_property.STATUS->tunint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->get_property.STATUS->tunint);
       strcat(msg,separator); strcat(msg,"-ATVINT   ");
           if  (api->rsp->get_property.STATUS->atvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->get_property.STATUS->atvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->get_property.STATUS->atvint);
       strcat(msg,separator); strcat(msg,"-DTVINT   ");
           if  (api->rsp->get_property.STATUS->dtvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->get_property.STATUS->dtvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->get_property.STATUS->dtvint);
       strcat(msg,separator); strcat(msg,"-ERR      ");
           if  (api->rsp->get_property.STATUS->err      ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->get_property.STATUS->err      ==     0) strcat(msg,"NO_ERROR");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->get_property.STATUS->err);
       strcat(msg,separator); strcat(msg,"-CTS      ");
           if  (api->rsp->get_property.STATUS->cts      ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->get_property.STATUS->cts      ==     0) strcat(msg,"WAIT     ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->get_property.STATUS->cts);
       strcat(msg,separator); strcat(msg,"-RESERVED "); sprintf(msg,"%s%d", msg, api->rsp->get_property.reserved);
       strcat(msg,separator); strcat(msg,"-DATA     "); sprintf(msg,"%s%d", msg, api->rsp->get_property.data);
     break;
    #endif /*     Si2176_GET_PROPERTY_CMD */

    #ifdef        Si2176_GET_REV_CMD
     case         Si2176_GET_REV_CMD_CODE:
      sprintf(msg,"GET_REV ");
       strcat(msg,separator); strcat(msg,"-TUNINT   ");
           if  (api->rsp->get_rev.STATUS->tunint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->get_rev.STATUS->tunint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, api->rsp->get_rev.STATUS->tunint);
       strcat(msg,separator); strcat(msg,"-ATVINT   ");
           if  (api->rsp->get_rev.STATUS->atvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->get_rev.STATUS->atvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, api->rsp->get_rev.STATUS->atvint);
       strcat(msg,separator); strcat(msg,"-DTVINT   ");
           if  (api->rsp->get_rev.STATUS->dtvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->get_rev.STATUS->dtvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, api->rsp->get_rev.STATUS->dtvint);
       strcat(msg,separator); strcat(msg,"-ERR      ");
           if  (api->rsp->get_rev.STATUS->err      ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->get_rev.STATUS->err      ==     0) strcat(msg,"NO_ERROR");
      else                                                  sprintf(msg,"%s%d", msg, api->rsp->get_rev.STATUS->err);
       strcat(msg,separator); strcat(msg,"-CTS      ");
           if  (api->rsp->get_rev.STATUS->cts      ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->get_rev.STATUS->cts      ==     0) strcat(msg,"WAIT     ");
      else                                                  sprintf(msg,"%s%d", msg, api->rsp->get_rev.STATUS->cts);
       strcat(msg,separator); strcat(msg,"-PN       "); sprintf(msg,"%s%d", msg, api->rsp->get_rev.pn);
       strcat(msg,separator); strcat(msg,"-FWMAJOR  "); sprintf(msg,"%s%d", msg, api->rsp->get_rev.fwmajor);
       strcat(msg,separator); strcat(msg,"-FWMINOR  "); sprintf(msg,"%s%d", msg, api->rsp->get_rev.fwminor);
       strcat(msg,separator); strcat(msg,"-PATCH    "); sprintf(msg,"%s%d", msg, api->rsp->get_rev.patch);
       strcat(msg,separator); strcat(msg,"-CMPMAJOR "); sprintf(msg,"%s%d", msg, api->rsp->get_rev.cmpmajor);
       strcat(msg,separator); strcat(msg,"-CMPMINOR "); sprintf(msg,"%s%d", msg, api->rsp->get_rev.cmpminor);
       strcat(msg,separator); strcat(msg,"-CMPBUILD "); sprintf(msg,"%s%d", msg, api->rsp->get_rev.cmpbuild);
       strcat(msg,separator); strcat(msg,"-CHIPREV  ");
           if  (api->rsp->get_rev.chiprev  ==     1) strcat(msg,"A");
      else if  (api->rsp->get_rev.chiprev  ==     2) strcat(msg,"B");
      else                                          sprintf(msg,"%s%d", msg, api->rsp->get_rev.chiprev);
     break;
    #endif /*     Si2176_GET_REV_CMD */

    #ifdef        Si2176_PART_INFO_CMD
     case         Si2176_PART_INFO_CMD_CODE:
      sprintf(msg,"PART_INFO ");
       strcat(msg,separator); strcat(msg,"-TUNINT   ");
           if  (api->rsp->part_info.STATUS->tunint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->part_info.STATUS->tunint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->part_info.STATUS->tunint);
       strcat(msg,separator); strcat(msg,"-ATVINT   ");
           if  (api->rsp->part_info.STATUS->atvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->part_info.STATUS->atvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->part_info.STATUS->atvint);
       strcat(msg,separator); strcat(msg,"-DTVINT   ");
           if  (api->rsp->part_info.STATUS->dtvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->part_info.STATUS->dtvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->part_info.STATUS->dtvint);
       strcat(msg,separator); strcat(msg,"-ERR      ");
           if  (api->rsp->part_info.STATUS->err      ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->part_info.STATUS->err      ==     0) strcat(msg,"NO_ERROR");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->part_info.STATUS->err);
       strcat(msg,separator); strcat(msg,"-CTS      ");
           if  (api->rsp->part_info.STATUS->cts      ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->part_info.STATUS->cts      ==     0) strcat(msg,"WAIT     ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->part_info.STATUS->cts);
       strcat(msg,separator); strcat(msg,"-CHIPREV  ");
           if  (api->rsp->part_info.chiprev  ==     1) strcat(msg,"A");
      else if  (api->rsp->part_info.chiprev  ==     2) strcat(msg,"B");
      else                                            sprintf(msg,"%s%d", msg, api->rsp->part_info.chiprev);
       strcat(msg,separator); strcat(msg,"-PART     "); sprintf(msg,"%s%d", msg, api->rsp->part_info.part);
       strcat(msg,separator); strcat(msg,"-PMAJOR   "); sprintf(msg,"%s%d", msg, api->rsp->part_info.pmajor);
       strcat(msg,separator); strcat(msg,"-PMINOR   "); sprintf(msg,"%s%d", msg, api->rsp->part_info.pminor);
       strcat(msg,separator); strcat(msg,"-PBUILD   "); sprintf(msg,"%s%d", msg, api->rsp->part_info.pbuild);
       strcat(msg,separator); strcat(msg,"-RESERVED "); sprintf(msg,"%s%d", msg, api->rsp->part_info.reserved);
       strcat(msg,separator); strcat(msg,"-SERIAL   "); sprintf(msg,"%s%ld", msg, api->rsp->part_info.serial);
       strcat(msg,separator); strcat(msg,"-ROMID    "); sprintf(msg,"%s%d", msg, api->rsp->part_info.romid);
     break;
    #endif /*     Si2176_PART_INFO_CMD */

    #ifdef        Si2176_POWER_DOWN_CMD
     case         Si2176_POWER_DOWN_CMD_CODE:
      sprintf(msg,"POWER_DOWN ");
       strcat(msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->power_down.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_down.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                   sprintf(msg,"%s%d", msg, api->rsp->power_down.STATUS->tunint);
       strcat(msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->power_down.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_down.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                   sprintf(msg,"%s%d", msg, api->rsp->power_down.STATUS->atvint);
       strcat(msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->power_down.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_down.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                   sprintf(msg,"%s%d", msg, api->rsp->power_down.STATUS->dtvint);
       strcat(msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->power_down.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->power_down.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                   sprintf(msg,"%s%d", msg, api->rsp->power_down.STATUS->err);
       strcat(msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->power_down.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->power_down.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                   sprintf(msg,"%s%d", msg, api->rsp->power_down.STATUS->cts);
     break;
    #endif /*     Si2176_POWER_DOWN_CMD */

    #ifdef        Si2176_POWER_UP_CMD
     case         Si2176_POWER_UP_CMD_CODE:
      sprintf(msg,"POWER_UP ");
       strcat(msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->power_up.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_up.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->power_up.STATUS->tunint);
       strcat(msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->power_up.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_up.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->power_up.STATUS->atvint);
       strcat(msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->power_up.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_up.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->power_up.STATUS->dtvint);
       strcat(msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->power_up.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->power_up.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->power_up.STATUS->err);
       strcat(msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->power_up.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->power_up.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->power_up.STATUS->cts);
     break;
    #endif /*     Si2176_POWER_UP_CMD */

    #ifdef        Si2176_SET_PROPERTY_CMD
     case         Si2176_SET_PROPERTY_CMD_CODE:
      sprintf(msg,"SET_PROPERTY ");
       strcat(msg,separator); strcat(msg,"-TUNINT   ");
           if  (api->rsp->set_property.STATUS->tunint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->set_property.STATUS->tunint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->set_property.STATUS->tunint);
       strcat(msg,separator); strcat(msg,"-ATVINT   ");
           if  (api->rsp->set_property.STATUS->atvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->set_property.STATUS->atvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->set_property.STATUS->atvint);
       strcat(msg,separator); strcat(msg,"-DTVINT   ");
           if  (api->rsp->set_property.STATUS->dtvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->set_property.STATUS->dtvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->set_property.STATUS->dtvint);
       strcat(msg,separator); strcat(msg,"-ERR      ");
           if  (api->rsp->set_property.STATUS->err      ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->set_property.STATUS->err      ==     0) strcat(msg,"NO_ERROR");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->set_property.STATUS->err);
       strcat(msg,separator); strcat(msg,"-CTS      ");
           if  (api->rsp->set_property.STATUS->cts      ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->set_property.STATUS->cts      ==     0) strcat(msg,"WAIT     ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->set_property.STATUS->cts);
       strcat(msg,separator); strcat(msg,"-RESERVED "); sprintf(msg,"%s%d", msg, api->rsp->set_property.reserved);
       strcat(msg,separator); strcat(msg,"-DATA     "); sprintf(msg,"%s%d", msg, api->rsp->set_property.data);
     break;
    #endif /*     Si2176_SET_PROPERTY_CMD */

    #ifdef        Si2176_STANDBY_CMD
     case         Si2176_STANDBY_CMD_CODE:
      sprintf(msg,"STANDBY ");
       strcat(msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->standby.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->standby.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                sprintf(msg,"%s%d", msg, api->rsp->standby.STATUS->tunint);
       strcat(msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->standby.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->standby.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                sprintf(msg,"%s%d", msg, api->rsp->standby.STATUS->atvint);
       strcat(msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->standby.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->standby.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                sprintf(msg,"%s%d", msg, api->rsp->standby.STATUS->dtvint);
       strcat(msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->standby.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->standby.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                sprintf(msg,"%s%d", msg, api->rsp->standby.STATUS->err);
       strcat(msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->standby.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->standby.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                sprintf(msg,"%s%d", msg, api->rsp->standby.STATUS->cts);
     break;
    #endif /*     Si2176_STANDBY_CMD */

    #ifdef        Si2176_TUNER_STATUS_CMD
     case         Si2176_TUNER_STATUS_CMD_CODE:
      sprintf(msg,"TUNER_STATUS ");
       strcat(msg,separator); strcat(msg,"-TUNINT   ");
           if  (api->rsp->tuner_status.STATUS->tunint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_status.STATUS->tunint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->tuner_status.STATUS->tunint);
       strcat(msg,separator); strcat(msg,"-ATVINT   ");
           if  (api->rsp->tuner_status.STATUS->atvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_status.STATUS->atvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->tuner_status.STATUS->atvint);
       strcat(msg,separator); strcat(msg,"-DTVINT   ");
           if  (api->rsp->tuner_status.STATUS->dtvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_status.STATUS->dtvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->tuner_status.STATUS->dtvint);
       strcat(msg,separator); strcat(msg,"-ERR      ");
           if  (api->rsp->tuner_status.STATUS->err      ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->tuner_status.STATUS->err      ==     0) strcat(msg,"NO_ERROR");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->tuner_status.STATUS->err);
       strcat(msg,separator); strcat(msg,"-CTS      ");
           if  (api->rsp->tuner_status.STATUS->cts      ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->tuner_status.STATUS->cts      ==     0) strcat(msg,"WAIT     ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->tuner_status.STATUS->cts);
       strcat(msg,separator); strcat(msg,"-TCINT    ");
           if  (api->rsp->tuner_status.tcint    ==     1) strcat(msg,"CHANGED  ");
      else if  (api->rsp->tuner_status.tcint    ==     0) strcat(msg,"NO_CHANGE");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->tuner_status.tcint);
       strcat(msg,separator); strcat(msg,"-RSSILINT ");
           if  (api->rsp->tuner_status.rssilint ==     1) strcat(msg,"CHANGED  ");
      else if  (api->rsp->tuner_status.rssilint ==     0) strcat(msg,"NO_CHANGE");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->tuner_status.rssilint);
       strcat(msg,separator); strcat(msg,"-RSSIHINT ");
           if  (api->rsp->tuner_status.rssihint ==     1) strcat(msg,"CHANGED  ");
      else if  (api->rsp->tuner_status.rssihint ==     0) strcat(msg,"NO_CHANGE");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->tuner_status.rssihint);
       strcat(msg,separator); strcat(msg,"-TC       ");
           if  (api->rsp->tuner_status.tc       ==     0) strcat(msg,"BUSY");
      else if  (api->rsp->tuner_status.tc       ==     1) strcat(msg,"DONE");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->tuner_status.tc);
       strcat(msg,separator); strcat(msg,"-RSSIL    ");
           if  (api->rsp->tuner_status.rssil    ==     1) strcat(msg,"LOW");
      else if  (api->rsp->tuner_status.rssil    ==     0) strcat(msg,"OK ");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->tuner_status.rssil);
       strcat(msg,separator); strcat(msg,"-RSSIH    ");
           if  (api->rsp->tuner_status.rssih    ==     1) strcat(msg,"HIGH");
      else if  (api->rsp->tuner_status.rssih    ==     0) strcat(msg,"OK  ");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->tuner_status.rssih);
       strcat(msg,separator); strcat(msg,"-RSSI     "); sprintf(msg,"%s%d", msg, api->rsp->tuner_status.rssi);
       strcat(msg,separator); strcat(msg,"-FREQ     "); sprintf(msg,"%s%ld", msg, api->rsp->tuner_status.freq);
       strcat(msg,separator); strcat(msg,"-MODE     ");
           if  (api->rsp->tuner_status.mode     ==     1) strcat(msg,"ATV");
      else if  (api->rsp->tuner_status.mode     ==     0) strcat(msg,"DTV");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->tuner_status.mode);
       strcat(msg,separator); strcat(msg,"-VCO_CODE "); sprintf(msg,"%s%d", msg, api->rsp->tuner_status.vco_code);
     break;
    #endif /*     Si2176_TUNER_STATUS_CMD */

    #ifdef        Si2176_TUNER_TUNE_FREQ_CMD
     case         Si2176_TUNER_TUNE_FREQ_CMD_CODE:
      sprintf(msg,"TUNER_TUNE_FREQ ");
       strcat(msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->tuner_tune_freq.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_tune_freq.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                        sprintf(msg,"%s%d", msg, api->rsp->tuner_tune_freq.STATUS->tunint);
       strcat(msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->tuner_tune_freq.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_tune_freq.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                        sprintf(msg,"%s%d", msg, api->rsp->tuner_tune_freq.STATUS->atvint);
       strcat(msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->tuner_tune_freq.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_tune_freq.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                        sprintf(msg,"%s%d", msg, api->rsp->tuner_tune_freq.STATUS->dtvint);
       strcat(msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->tuner_tune_freq.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->tuner_tune_freq.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                        sprintf(msg,"%s%d", msg, api->rsp->tuner_tune_freq.STATUS->err);
       strcat(msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->tuner_tune_freq.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->tuner_tune_freq.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                        sprintf(msg,"%s%d", msg, api->rsp->tuner_tune_freq.STATUS->cts);
     break;
    #endif /*     Si2176_TUNER_TUNE_FREQ_CMD */

     default : break;
    }
    return 0;
  }
  /* _get_command_response_string_insertion_point */
#endif /* Si2176_GET_COMMAND_STRINGS */






