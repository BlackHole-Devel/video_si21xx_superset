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
                  Silicon Laboratories Broadcast Si2158B Layer 2 API


   L2 API for commands and properties
   FILE: Si2158B_L2_API.c
   Supported IC : Si2158B
   Compiled for ROM 51 firmware 4_1_build_3
   Revision: 0.1
   Tag:  ROM51_4_1_build_3_V0.1
   Date: June 23 2016
****************************************************************************************/
#include <string.h>
/* Si2158B API Defines */
 /* define this if using the ALIF video filter */
#undef USING_ALIF_FILTER
/* define this if using the DTV video filter */
#undef USING_DLIF_FILTER
/************************************************************************************************************************/
/* Si2158B API Specific Includes */
#include "Si2158B_L2_API.h"               /* Include file for this code */
#include "Si2158B_firmware_4_1_build_3.h"   /* firmware compatible with Si2158B-marking */
#include "Si2158B_firmware_0_A_build_15.h"      /*  */
#define Si2158B_BYTES_PER_LINE 8
 #ifdef    USING_ALIF_FILTER
#include "write_ALIF_video_coeffs.h"   /* .h file from custom Video filter Tool output */
#endif /* USING_ALIF_FILTER */
#ifdef USING_DLIF_FILTER
#include "write_DLIF_video_coeffs.h"   /* .h file from custom Video filter Tool output */
#endif
/************************************************************************************************************************
  NAME: Si2158B_Configure
  DESCRIPTION: Setup Si2158B video filters, GPIOs/clocks, Common Properties startup, etc.
  Parameter:  Pointer to Si2158B Context
  Returns:    I2C transaction error code, NO_Si2158B_ERROR if successful
************************************************************************************************************************/
int Si2158B_Configure           (L1_Si2158B_Context *api)
{
    int return_code;
    return_code = NO_Si2158B_ERROR;

 #ifdef USING_ALIF_FILTER
    if ((return_code = Si2158B_LoadVideofilter(api,ALIF_VIDFILT_TABLE,ALIF_VIDFILT_LINES)) != NO_Si2158B_ERROR)
       return return_code;
  #endif /* USING_ALIF_FILTER */
     /* load DTV video filter file */
  #ifdef USING_DLIF_FILTER
     if ((return_code = Si2158B_LoadVideofilter(api,DLIF_VIDFILT_TABLE,DLIF_VIDFILT_LINES)) != NO_Si2158B_ERROR)
       return return_code;
  #endif
    /* Set Properties startup configuration         */
    Si2158B_storePropertiesDefaults (api->propShadow);
    /* Edit the Si2158B_storeUserProperties if you have any properties settings different from the standard defaults */
    Si2158B_storeUserProperties     (api->prop);

    /* Download properties different from 'propShadow' if api->propertyWriteMode = Si2158B_DOWNLOAD_ON_CHANGE */
    /* Download properties in any case                 if api->propertyWriteMode = Si2158B_DOWNLOAD_ALWAYS    */
    Si2158B_downloadAllProperties(api);

    return return_code;
}
/************************************************************************************************************************
  NAME: Si2158B_PowerUpWithPatch
  DESCRIPTION: Send Si2158B API PowerUp Command with PowerUp to bootloader,
  Check the Chip rev and part, and ROMID are compared to expected values.
  Load the Firmware Patch then Start the Firmware.
  Programming Guide Reference:    Flowchart A.2 (POWER_UP with patch flowchart)

  Parameter:  pointer to Si2158B Context
  Returns:    Si2158B/I2C transaction error code, NO_Si2158B_ERROR if successful
************************************************************************************************************************/
int Si2158B_PowerUpWithPatch    (L1_Si2158B_Context *api)
{
    int return_code;
    return_code = NO_Si2158B_ERROR;
    if (!(api->load_control & SKIP_POWERUP))
    {

        /* always wait for CTS prior to POWER_UP command */
        if ((return_code = Si2158B_pollForCTS  (api)) != NO_Si2158B_ERROR) {
            SiTRACE ("Si2158B_pollForCTS error 0x%02x\n", return_code);
            return return_code;
        }

        if ((return_code = Si2158B_L1_POWER_UP (api,
                                Si2158B_POWER_UP_CMD_SUBCODE_CODE,
                                api->cmd->power_up.clock_mode,
                                api->cmd->power_up.en_xout,
                                Si2158B_POWER_UP_CMD_PD_LDO_LDO_POWER_UP,
                                Si2158B_POWER_UP_CMD_RESERVED2_RESERVED,
                                Si2158B_POWER_UP_CMD_RESERVED3_RESERVED,
                                Si2158B_POWER_UP_CMD_RESERVED4_RESERVED,
                                Si2158B_POWER_UP_CMD_RESERVED5_RESERVED,
                                Si2158B_POWER_UP_CMD_RESERVED6_RESERVED,
                                Si2158B_POWER_UP_CMD_RESERVED7_RESERVED,
                                Si2158B_POWER_UP_CMD_RESET_RESET,
                                Si2158B_POWER_UP_CMD_CLOCK_FREQ_CLK_24MHZ,
                                Si2158B_POWER_UP_CMD_RESERVED8_RESERVED,
                                Si2158B_POWER_UP_CMD_FUNC_BOOTLOADER,
                                Si2158B_POWER_UP_CMD_CTSIEN_DISABLE,
                                Si2158B_POWER_UP_CMD_WAKE_UP_WAKE_UP
                                )) != NO_Si2158B_ERROR)
        {
            SiTRACE ("Si2158B_L1_POWER_UP error 0x%02x: %s\n", return_code, Si2158B_L1_API_ERROR_TEXT(return_code) );
            return return_code;
        }

        /* Get the Part Info from the chip.   This command is only valid in Bootloader mode */
        if ((return_code = Si2158B_L1_PART_INFO(api)) != NO_Si2158B_ERROR) {
            SiTRACE ("Si2158B_L1_PART_INFO error 0x%02x: %s\n", return_code, Si2158B_L1_API_ERROR_TEXT(return_code) );
            return return_code;
        }
        SiTRACE("chiprev %d\n",        api->rsp->part_info.chiprev);
        SiTRACE("part    Si21%d\n",    api->rsp->part_info.part   );
		SiTRACE("romid   0x%02x\n",    api->rsp->part_info.romid  );
        SiTRACE("pmajor  %d\n",        api->rsp->part_info.pmajor );
		SiTRACE("pminor  %d\n",        api->rsp->part_info.pminor );
		SiTRACE("pbuild  %d\n",        api->rsp->part_info.pbuild );
        if ((api->rsp->part_info.pmajor >= 0x30) & (api->rsp->part_info.pminor >= 0x30)) {
            SiTRACE("pmajor  '%c'\n",      api->rsp->part_info.pmajor );
            SiTRACE("pminor  '%c'\n",      api->rsp->part_info.pminor );
            SiTRACE("Full Info       'Si21%02d-%c%c%c ROM%x NVM%c_%cb%d'\n\n\n", api->rsp->part_info.part
                                                                               , api->rsp->part_info.chiprev + 0x40
                                                                               , api->rsp->part_info.pmajor
                                                                               , api->rsp->part_info.pminor
                                                                               , api->rsp->part_info.romid
                                                                               , api->rsp->part_info.pmajor
                                                                               , api->rsp->part_info.pminor
                                                                               , api->rsp->part_info.pbuild );
        }
    }
    /* Load the Firmware */
     if (!(api->load_control & SKIP_LOADFIRMWARE))
     {
        if (api->rsp->part_info.romid == 0x51)
        {
          /* Load the Firmware */
           if ((return_code = Si2158B_LoadFirmware_16(api, Si2158B_FW_4_1b3, FIRMWARE_LINES_4_1b3)) != NO_Si2158B_ERROR) {
             SiTRACE ("Si2158B_LoadFirmware error 0x%02x: %s\n", return_code, Si2158B_L1_API_ERROR_TEXT(return_code) );
             return return_code;
           }
        }
        else  if (api->rsp->part_info.romid == 0x50)
        {

           if ((return_code = Si2158B_LoadFirmware_16(api, Si2158B_FW_0_Ab15, FIRMWARE_LINES_0_Ab15)) != NO_Si2158B_ERROR) {
             SiTRACE ("Si2158B_LoadFirmware error 0x%02x: %s\n", return_code, Si2158B_L1_API_ERROR_TEXT(return_code) );
             return return_code;
           }

        }
        else
        {
            SiTRACE ("INCOMPATIBLE PART error ROMID 0x%02x\n", api->rsp->part_info.romid);
            return ERROR_Si2158B_INCOMPATIBLE_PART;
        }
     }
     if (!(api->load_control & SKIP_LOADFIRMWARE))
     {
        /*Start the Firmware */
        if ((return_code = Si2158B_StartFirmware(api)) != NO_Si2158B_ERROR) { /* Start firmware */
            SiTRACE ("Si2158B_StartFirmware error 0x%02x: %s\n", return_code, Si2158B_L1_API_ERROR_TEXT(return_code) );
            return return_code;
        }
        Si2158B_L1_GET_REV (api);
        SiTRACE("Si21%2d Part running 'FW_%c_%cb%d'\n", api->rsp->part_info.part, api->rsp->get_rev.cmpmajor, api->rsp->get_rev.cmpminor, api->rsp->get_rev.cmpbuild );

     }

    return NO_Si2158B_ERROR;
}
/************************************************************************************************************************
  NAME: Si2158B_PowerUpUsingBroadcastI2C
  DESCRIPTION: This is similar to PowerUpWithPatch() for 2 tuners but it uses the I2C Broadcast
  command to allow the firmware download simultaneously to both tuners.

  Parameter:  pointer to Tuner L1 Context array
  Parameter:  tuner_count, the number of tuners in the table
  Returns:    Si2158B/I2C transaction error code, NO_Si2158B_ERROR if successful
************************************************************************************************************************/
int Si2158B_PowerUpUsingBroadcastI2C    (L1_Si2158B_Context *tuners[], int tuner_count )
{
    int return_code;
    int t;
    #define Si2158B_TUNER_BROADCAST_INDEX 0
    unsigned char logged_i2c_address;
    return_code = NO_Si2158B_ERROR;

  /* for each tuner execute the powerup and part_info command but not the firmware download. */
  for (t = 0; t < tuner_count; t++)
  {
      tuners[t]->load_control = SKIP_LOADFIRMWARE | SKIP_STARTFIRMWARE;
      /* Si2158B_PowerUpWithPatch will return right after Si2158B_L1_PART_INFO, because SKIP_LOADFIRMWARE and SKIP_STARTFIRMWARE are set */
      if ( (return_code = Si2158B_PowerUpWithPatch(tuners[t])) != NO_Si2158B_ERROR) {
        SiTRACE ("Tuner %d Si2158B_PowerUpWithPatch error 0x%02x\n", return_code);
        return return_code;
      }
       if ( (return_code = Si2158B_L1_CONFIG_I2C(tuners[t], Si2158B_CONFIG_I2C_CMD_SUBCODE_CODE, Si2158B_CONFIG_I2C_CMD_I2C_BROADCAST_ENABLED)) != NO_Si2158B_ERROR )
       {
          SiTRACE("Tuner %d L1_CONFIG_I2C error 0x%02x\n", t, return_code);
          return return_code;
       }
    }

  /* At this stage, all tuners are connected/powered up and in 'broadcast i2c' mode */

  /* store the address of tuner0 to the broadcast address and restore the original address after we're done.  */
  logged_i2c_address = tuners[Si2158B_TUNER_BROADCAST_INDEX]->i2c->address;
  tuners[Si2158B_TUNER_BROADCAST_INDEX]->i2c->address = Si2158B_BROADCAST_ADDRESS;
  /* set the load_control flag to SKIP_POWERUP so the firmware is downloaded and started on all tuners only */
  tuners[Si2158B_TUNER_BROADCAST_INDEX]->load_control = SKIP_POWERUP;

  /* Si2158B_PowerUpWithPatch will now broadcast the tuner fw and return
      when all is completed, because load_fw is now '1'                               */
  if ( (return_code = Si2158B_PowerUpWithPatch(tuners[Si2158B_TUNER_BROADCAST_INDEX])) != NO_Si2158B_ERROR) {
    SiTRACE("Tuner %d Si2158B_PowerUpWithPatch error 0x%02x\n", return_code);
    return return_code;
  }

  /* At this stage, all tuners have received the patch, and have been issued
     'Si2158B_StartFirmware'                                                          */
     if ((return_code = Si2158B_Configure    (tuners[Si2158B_TUNER_BROADCAST_INDEX])) != NO_Si2158B_ERROR)
     {
         return return_code;
     }

  /* Return the broadcast tuner address to its 'normal' value                         */
  tuners[Si2158B_TUNER_BROADCAST_INDEX]->i2c->address = logged_i2c_address;

  for (t = 0; t < tuner_count; t++)
  {
    if ( (return_code = Si2158B_L1_CONFIG_I2C(tuners[t], Si2158B_CONFIG_I2C_CMD_SUBCODE_CODE, Si2158B_CONFIG_I2C_CMD_I2C_BROADCAST_DISABLED)) != NO_Si2158B_ERROR )
     {
      SiTRACE("Tuner %d L1_CONFIG_I2C error 0x%02x\n", t, return_code);
         return return_code;
     }
  }
  for (t = 0; t < tuner_count; t++)
  {
    /* Set Properties startup configuration         */
    Si2158B_storePropertiesDefaults (tuners[t]->propShadow);
    /* Edit the Si2158B_storeUserProperties if you have any properties settings different from the standard defaults */
    Si2158B_storeUserProperties     (tuners[t]->prop);

   /* Reset the load_control flag to execute all phases of PowerUpWithPatch */
      tuners[t]->load_control =  SKIP_NONE;

 /* Check CTS for all tuners */
    if ( (return_code = Si2158B_pollForCTS(tuners[t])) != NO_Si2158B_ERROR ) {
      SiTRACE("Tuner %d pollForCTS error 0x%02x\n", t, return_code);
      return return_code;
    }

  }
  return NO_Si2158B_ERROR;
}
/************************************************************************************************************************
  NAME: Si2158B_LoadFirmware_16
  DESCRIPTION: Load firmware from firmware_struct array in Si2158B_Firmware_x_y_build_z.h file into Si2158B
              Requires Si2158B to be in bootloader mode after PowerUp
  Programming Guide Reference:    Flowchart A.3 (Download FW PATCH flowchart)

  Parameter:  Si2158B Context (I2C address)
  Parameter:  pointer to firmware_struct array
  Parameter:  number of lines in firmware table array (size in bytes / firmware_struct)
  Returns:    Si2158B/I2C transaction error code, NO_Si2158B_ERROR if successful
************************************************************************************************************************/
int Si2158B_LoadFirmware_16        (L1_Si2158B_Context *api, firmware_struct fw_table[], int nbLines)
{
    int return_code;
    int line;
    return_code = NO_Si2158B_ERROR;

    SiTRACE ("Si2158B_LoadFirmware_16 starting...\n");
    SiTRACE ("Si2158B_LoadFirmware_16 nbLines %d\n", nbLines);

    /* for each line in fw_table */
    for (line = 0; line < nbLines; line++)
    {
		if (fw_table[line].firmware_len > 0)  /* don't download if length is 0 , e.g. dummy firmware */
		{
			/* send firmware_len bytes (up to 16) to Si2158B */
			if ((return_code = Si2158B_L1_API_Patch(api, fw_table[line].firmware_len, fw_table[line].firmware_table)) != NO_Si2158B_ERROR)
			{
			  SiTRACE("Si2158B_LoadFirmware_16 error 0x%02x patching line %d: %s\n", return_code, line, Si2158B_L1_API_ERROR_TEXT(return_code) );
			  if (line == 0) {
			  SiTRACE("The firmware is incompatible with the part!\n");
			  }
          SiTraceConfiguration((char*)"traces resume");
			  return ERROR_Si2158B_LOADING_FIRMWARE;
			}
      if (line==3) SiTraceConfiguration("traces suspend");
		}
    }
    SiTraceConfiguration("traces resume");
    SiTRACE ("Si2158B_LoadFirmware_16 complete...\n");
    return NO_Si2158B_ERROR;
}
/************************************************************************************************************************
*******  Deprecated LoadFirmware Function *******
*******  Please use LoadFirmware_16 replacement *****
  NAME: Si2158B_LoadFirmware
  DESCRIPTON: Load firmware from FIRMWARE_TABLE array in Si2158B_Firmware_x_y_build_z.h file into Si2158B
              Requires Si2158B to be in bootloader mode after PowerUp
  Programming Guide Reference:    Flowchart A.3 (Download FW PATCH flowchart)

  Parameter:  Si2158B Context (I2C address)
  Parameter:  pointer to firmware table array
  Parameter:  number of lines in firmware table array (size in bytes / BYTES_PER_LINE)
  Returns:    Si2158B/I2C transaction error code, NO_Si2158B_ERROR if successful
************************************************************************************************************************/
int Si2158B_LoadFirmware        (L1_Si2158B_Context *api, unsigned char fw_table[], int nbLines)
{
    int return_code;
    int line;
    return_code = NO_Si2158B_ERROR;

    SiTRACE ("Si2158B_LoadFirmware starting...\n");
    SiTRACE ("Si2158B_LoadFirmware nbLines %d\n", nbLines);

    /* for each line in fw_table */
    for (line = 0; line < nbLines; line++)
    {
        /* send Si2158B_BYTES_PER_LINE fw bytes to Si2158B */
        if ((return_code = Si2158B_L1_API_Patch(api, Si2158B_BYTES_PER_LINE, fw_table + Si2158B_BYTES_PER_LINE*line)) != NO_Si2158B_ERROR)
        {
          SiTRACE("Si2158B_LoadFirmware error 0x%02x patching line %d: %s\n", return_code, line, Si2158B_L1_API_ERROR_TEXT(return_code) );
          if (line == 0) {
          SiTRACE("The firmware is incompatible with the part!\n");
          }
          SiTraceConfiguration((char*)"traces resume");
          return ERROR_Si2158B_LOADING_FIRMWARE;
        }
        if (line==3) {SiTraceConfiguration("traces suspend");}
    }
    SiTraceConfiguration("traces resume");
    SiTRACE ("Si2158B_LoadFirmware complete...\n");
    return NO_Si2158B_ERROR;
}
/************************************************************************************************************************
  NAME: Si2158B_StartFirmware
  DESCRIPTION: Start Si2158B firmware (put the Si2158B into run mode)
  Parameter:   Si2158B Context (I2C address)
  Parameter (passed by Reference):   ExitBootloadeer Response Status byte : tunint, atvint, dtvint, err, cts
  Returns:     I2C transaction error code, NO_Si2158B_ERROR if successful
************************************************************************************************************************/
int Si2158B_StartFirmware       (L1_Si2158B_Context *api)
{

    if (Si2158B_L1_EXIT_BOOTLOADER(api, Si2158B_EXIT_BOOTLOADER_CMD_FUNC_TUNER, Si2158B_EXIT_BOOTLOADER_CMD_CTSIEN_OFF) != NO_Si2158B_ERROR)
    {
        return ERROR_Si2158B_STARTING_FIRMWARE;
    }

    return NO_Si2158B_ERROR;
}
/************************************************************************************************************************
  NAME: Si2158B_Init
  DESCRIPTION:Reset and Initialize Si2158B
  Parameter:  Si2158B Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2158B_ERROR if successful
************************************************************************************************************************/
int Si2158B_Init                (L1_Si2158B_Context *api)
{
    int return_code;
    SiTRACE("Si2158B_Init starting...\n");

    if ((return_code = Si2158B_PowerUpWithPatch(api)) != NO_Si2158B_ERROR) {   /* PowerUp into bootloader */
        SiTRACE ("Si2158B_PowerUpWithPatch error 0x%02x: %s\n", return_code, Si2158B_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }
    /* At this point, FW is loaded and started.  */
    Si2158B_Configure(api);
    SiTRACE("Si2158B_Init complete...\n");
    return NO_Si2158B_ERROR;
}
 /************************************************************************************************************************
  NAME: Si2158B_UpdateChannelScanFrequency
  DESCRIPTION:  This routine allows the user to implement an update of the current channel scan operation with
                the current frequency being scanned.
  Parameter:    Current frequency of the scan routine
  Parameter:  channelsFound = 0 if channel not found at that frequency , channelsFound > 0  the number of channels
        currently found( including this frequency )
  Returns:      1 if scan abort requested, 0 if ok.
************************************************************************************************************************/
int Si2158B_UpdateChannelScanFrequency(int freq,int channelsFound)
{
  int abort_scan = 0;
  static int previousFrequency;
/*** Insert user code to display realtime updates of the frequency being scanned and channel status (number found ) **/
/* add check for user abort here */
  if (channelsFound)
  {
    /* Terminate the previous scan message */
    printf("Found Frequency %d\n",freq);
  }
  else
  {
    if (freq==previousFrequency)
      printf("Not Found\n");
    else
      printf("Scanning Frequency %d, ",freq);
  }
  previousFrequency=freq;

  if (abort_scan)
    return 1;
  else
    return 0;
  }
 /************************************************************************************************************************
  NAME: Si2158B_GetRF
  DESCRIPTIION: Retrieve Si2158B tune freq

  Parameter:  Pointer to Si2158B Context (I2C address)
  Returns  :  frequency (Hz) as an int
************************************************************************************************************************/
int  Si2158B_GetRF             (L1_Si2158B_Context *api)
{
    Si2158B_L1_TUNER_STATUS (api, Si2158B_TUNER_STATUS_CMD_INTACK_OK);
        return api->rsp->tuner_status.freq;
}
 /************************************************************************************************************************
  NAME: Si2158B_Tune
  DESCRIPTIION: Tune Si2158B in specified mode (ATV/DTV) at center frequency, wait for TUNINT and xTVINT with timeout

  Parameter:  Pointer to Si2158B Context (I2C address)
  Parameter:  Mode (ATV or DTV) use Si2158B_TUNER_TUNE_FREQ_CMD_MODE_ATV or Si2158B_TUNER_TUNE_FREQ_CMD_MODE_DTV constants
  Parameter:  frequency (Hz) as a unsigned long integer
  Returns:    0 if channel found.  A nonzero value means either an error occurred or channel not locked.
  Programming Guide Reference:    Flowchart A.7 (Tune flowchart)
************************************************************************************************************************/
 int  Si2158B_Tune              (L1_Si2158B_Context *api, unsigned char mode, unsigned long freq)
{
    int start_time  = 0;
    int return_code = 0;
    int timeout     = 36;

    if (Si2158B_L1_TUNER_TUNE_FREQ (api,
                                   mode,
                                   freq) != NO_Si2158B_ERROR)
    {
        return ERROR_Si2158B_SENDING_COMMAND;
    }

    start_time = system_time();

    /* wait for TUNINT, timeout is 36 ms */
    while ( (system_time() - start_time) < timeout )
    {
        if ((return_code = Si2158B_L1_CheckStatus(api)) != NO_Si2158B_ERROR)
            return return_code;
        if (api->status->tunint)
            break;
    }
    if (!api->status->tunint) {
      SiTRACE("Timeout waiting for TUNINT\n");
      return ERROR_Si2158B_TUNINT_TIMEOUT;
    }

    /* wait for xTVINT, timeout is 110ms for ATVINT and 10 ms for DTVINT */
    start_time = system_time();
    timeout    = ((mode==Si2158B_TUNER_TUNE_FREQ_CMD_MODE_ATV) ? 110 : 10);
    while ( (system_time() - start_time) < timeout )
    {
        if ((return_code = Si2158B_L1_CheckStatus(api)) != NO_Si2158B_ERROR)
            return return_code;
        if (mode==Si2158B_TUNER_TUNE_FREQ_CMD_MODE_ATV)
        {
         if (api->status->atvint)
            break;
        }
        else
        {
         if (api->status->dtvint)
            break;
        }
    }

    if (mode==Si2158B_TUNER_TUNE_FREQ_CMD_MODE_ATV)
    {
      if (api->status->atvint)
      {
        SiTRACE("ATV Tune Successful\n");
               return NO_Si2158B_ERROR;
            }
      else
        SiTRACE("Timeout waiting for ATVINT\n");
    }
    else
    {
        if (api->status->dtvint)
        {
          SiTRACE("DTV Tune Successful\n");
          return NO_Si2158B_ERROR;
        }
        else
          SiTRACE("Timeout waiting for DTVINT\n");
    }

    return ERROR_Si2158B_xTVINT_TIMEOUT;
}
 /************************************************************************************************************************
  NAME: Si2158B_ATVTune
  DESCRIPTION:Update ATV_VIDEO_MODE and tune ATV mode at center frequency
  Parameter:  Pointer to Si2158B Context (I2C address)
  Parameter:  frequency (Hz)
  Parameter:  Video system , e.g. use constant Si2158B_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M for system M
  Parameter:  transport,  e.g. use constant Si2158B_ATV_VIDEO_MODE_PROP_TRANS_TERRESTRIAL for terrestrial
  Parameter:  color , e.g. use constant Si2158B_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC for PAL or NTSC
  Parameter:  invert_signal, 0= normal, 1= inverted
  Parameter:  rsp - commandResp structure to returns tune status info.
  Returns:    I2C transaction error code, 0 if successful
  Programming Guide Reference:    Flowchart A.7 (Tune flowchart)
************************************************************************************************************************/
int  Si2158B_ATVTune           (L1_Si2158B_Context *api, unsigned long freq, unsigned char video_sys, unsigned char color, unsigned char invert_spectrum)
{
    /* update ATV_VIDEO_MODE property */
    api->prop->atv_video_mode.video_sys = video_sys;
    api->prop->atv_video_mode.color = color;
    api->prop->atv_video_mode.invert_spectrum=invert_spectrum;
    if (Si2158B_L1_SetProperty2(api, Si2158B_ATV_VIDEO_MODE_PROP) != NO_Si2158B_ERROR)
    {
      return ERROR_Si2158B_SENDING_COMMAND;
    }

    return Si2158B_Tune (api, Si2158B_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq);
}
 /************************************************************************************************************************
  NAME: Si2158B_DTVTune
  DESCRIPTION: Update DTV_MODE and tune DTV mode at center frequency
  Parameter:  Pointer to Si2158B Context (I2C address)
  Parameter:  frequency (Hz)
  Parameter:  bandwidth , 6,7 or 8 MHz
  Parameter:  modulation,  e.g. use constant Si2158B_DTV_MODE_PROP_MODULATION_DVBT for DVBT mode
  Parameter:  rsp - commandResp structure to returns tune status info.
  Returns:    I2C transaction error code, 0 if successful
  Programming Guide Reference:    Flowchart A.7 (Tune flowchart)
************************************************************************************************************************/
int  Si2158B_DTVTune           (L1_Si2158B_Context *api, unsigned long freq, unsigned char bw, unsigned char modulation, unsigned char invert_spectrum)
{
    int return_code;
    return_code = NO_Si2158B_ERROR;

    /* update DTV_MODE_PROP property */
    api->prop->dtv_mode.bw = bw;
    api->prop->dtv_mode.invert_spectrum = invert_spectrum;
    api->prop->dtv_mode.modulation = modulation;
    if (Si2158B_L1_SetProperty2(api, Si2158B_DTV_MODE_PROP) != NO_Si2158B_ERROR)
    {
      return ERROR_Si2158B_SENDING_COMMAND;
    }

    return_code = Si2158B_Tune (api, Si2158B_TUNER_TUNE_FREQ_CMD_MODE_DTV, freq);

    return return_code;
}
/************************************************************************************************************************
  NAME: Si2158B_XoutOn
  Parameter:  Pointer to Si2158B Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2158B_ERROR if successful
************************************************************************************************************************/
int Si2158B_XoutOn             (L1_Si2158B_Context *api)
{
    int return_code;
    SiTRACE("Si2158B_XoutOn:  Turning Xout ON\n");

     if ((return_code = Si2158B_L1_CONFIG_CLOCKS(api,
                                              Si2158B_CONFIG_CLOCKS_CMD_SUBCODE_CODE,
                                              Si2158B_CONFIG_CLOCKS_CMD_CLOCK_MODE_XTAL,
                                              Si2158B_CONFIG_CLOCKS_CMD_EN_XOUT_EN_XOUT)) != NO_Si2158B_ERROR)
    return return_code;

    return NO_Si2158B_ERROR;
}
 /************************************************************************************************************************
  NAME: Si2158B_XoutOff
  Parameter:  Pointer to Si2158B Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2158B_ERROR if successful
************************************************************************************************************************/
int Si2158B_XoutOff            (L1_Si2158B_Context *api)
{
    int return_code;
    SiTRACE("Si2158B_XoutOff:  Turning Xout OFF\n");
    if ((return_code = Si2158B_L1_CONFIG_CLOCKS(api,
                                              Si2158B_CONFIG_CLOCKS_CMD_SUBCODE_CODE,
                                              Si2158B_CONFIG_CLOCKS_CMD_CLOCK_MODE_XTAL,
                                              Si2158B_CONFIG_CLOCKS_CMD_EN_XOUT_DIS_XOUT)) != NO_Si2158B_ERROR)

    return return_code;

    return NO_Si2158B_ERROR;
}
 /************************************************************************************************************************
  NAME: Si2158B_Standby
  Parameter:  Pointer to Si2158B Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2158B_ERROR if successful
************************************************************************************************************************/
int Si2158B_Standby         (L1_Si2158B_Context *api)
{
    int return_code;
    SiTRACE("Si2158B_Standby: Going to Standby. The part will wake on the next command\n");

    if ((return_code = Si2158B_L1_STANDBY(api, Si2158B_STANDBY_CMD_TYPE_LNA_ON)) != NO_Si2158B_ERROR)
    return return_code;

    return NO_Si2158B_ERROR;
}
 /************************************************************************************************************************
  NAME: Si2158B_Powerdown
  Parameter:  Pointer to Si2158B Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2158B_ERROR if successful
************************************************************************************************************************/
int Si2158B_Powerdown         (L1_Si2158B_Context *api)
{
    int return_code;
    SiTRACE("Si2158B_Powerdown: Powering down the part. Select InitAndConfig to reload.\n");

    if ((return_code = Si2158B_L1_POWER_DOWN(api)) != NO_Si2158B_ERROR)
    return return_code;

    return NO_Si2158B_ERROR;
}
 /************************************************************************************************************************
  NAME: Si2158B_LoadVideofilter
  DESCRIPTION:        Load video filters from vidfiltTable in Si2158B_write_xTV_video_coeffs.h file into Si2158B
  Programming Guide Reference:    Flowchart A.4 (Download Video Filters flowchart)

  Parameter:  Si2158B Context (I2C address)
  Parameter:  pointer to video filter table array
  Parameter:  number of lines in video filter table array(size in bytes / atv_vid_filt_struct)
  Returns:    Si2158B/I2C transaction error code, NO_Si2158B_ERROR if successful
************************************************************************************************************************/
int Si2158B_LoadVideofilter     (L1_Si2158B_Context *api, vid_filt_struct vidFiltTable[], int lines)
{
    int line;
     /* for each line in VIDFILT_TABLE (max 16 bytes)  */
    for (line = 0; line < lines; line++)
    {
        /* send up to 16 byte I2C command to Si2158B */
        if (Si2158B_L1_API_Patch(api, vidFiltTable[line].vid_filt_len, vidFiltTable[line].vid_filt_table) != NO_Si2158B_ERROR)
        {
            return ERROR_Si2158B_SENDING_COMMAND;
        }
    }
    return NO_Si2158B_ERROR;
}
 /************************************************************************************************************************
  NAME: Si2158B_ATV_Channel_Scan_M
  DESCRIPTION: Performs a channel scan for NTSC (System M) of the band
  Programming Guide Reference:    Flowchart A.11.0 and A11.1 (ATV Channel Scan flowchart for System M)

  Parameter:  Pointer to Si2158B Context (I2C address)
  Parameter:  starting Frequency Hz
  Parameter:  ending Frequency Hz
  Parameter:  min RSSI dBm
  Parameter:  max RSSI dBm
  Parameter:  min SNR 1/2 dB
  Parameter:  max SNR 1/2 dB
  Returns:    0 if successful, otherwise an error.
************************************************************************************************************************/
int Si2158B_ATV_Channel_Scan_M(L1_Si2158B_Context *Si2158B, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm)
{
    #define SCAN_INTERVAL     1000000
    #define CHANNEL_BANDWIDTH 6000000
    #define CHANNEL_NOT_FOUND       0

    unsigned long freq;
    int i;

    /*Clear the channel list size and channel array */
    Si2158B->ChannelListSize=0;

    for (i=0; i< MAX_POSSIBLE_CHANNELS;i++)
    Si2158B->ChannelList[i]=0;
    /* configure the VideoMode property to System M, NTSC*/
    Si2158B->prop->atv_video_mode.video_sys = Si2158B_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M;    /* M ATV demodulation */
    Si2158B->prop->atv_video_mode.color     = Si2158B_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;    /* PAL_NTSC color system */
    if (Si2158B_L1_SetProperty2(Si2158B, Si2158B_ATV_VIDEO_MODE_PROP) != NO_Si2158B_ERROR)
    {
       return ERROR_Si2158B_SENDING_COMMAND;
    }
    /* configure the RSQ / RSSI threshold properties */
    Si2158B->prop->atv_rsq_rssi_threshold.lo = minRSSIdBm;
    Si2158B->prop->atv_rsq_rssi_threshold.hi = maxRSSIdBm;

    if (Si2158B_L1_SetProperty2(Si2158B, Si2158B_ATV_RSQ_RSSI_THRESHOLD_PROP) != NO_Si2158B_ERROR)
    {
      return ERROR_Si2158B_SENDING_COMMAND;
    }

    /* setup AFC acquistion range property to 1.5MHz for scanning */
    Si2158B->prop->atv_afc_range.range_khz    =  1500;
    if (Si2158B_L1_SetProperty2(Si2158B, Si2158B_ATV_AFC_RANGE_PROP) != NO_Si2158B_ERROR)
    {
       return ERROR_Si2158B_SENDING_COMMAND;
    }
   /* Start Scanning */
    for (freq=rangeMinHz; freq < rangeMaxHz; )
    {

    /* before calling tune provide a callback stub that the user can update the frequency */
    /* if user requested abort then break from the loop */
    if (Si2158B_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
      break;

    /* Call the Tune command to tune the frequency */
    /* if successful (a station was found) then the return value will be 0. */
    if (!Si2158B_Tune (Si2158B, Si2158B_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq))
    {

            /* Get ATV status */
      if (Si2158B_L1_ATV_STATUS (Si2158B, Si2158B_ATV_STATUS_CMD_INTACK_OK))
      {
        return ERROR_Si2158B_SENDING_COMMAND;
      }


      /* Add the afc_freq (khz) to the center frequency and add to the channel list */
      Si2158B->ChannelList[Si2158B->ChannelListSize]= freq + (Si2158B->rsp->atv_status.afc_freq * 1000);
      /* Update the callback to indicate the channel is found */
      /* if user requested abort then break from the loop */
      if (Si2158B_UpdateChannelScanFrequency(freq + (Si2158B->rsp->atv_status.afc_freq * 1000), Si2158B->ChannelListSize+1))
        break;

            freq = Si2158B->ChannelList[Si2158B->ChannelListSize++] + CHANNEL_BANDWIDTH;
         }
         else  /* We didn't find a station at this frequency so increment and move on */
         {
        /* if user requested abort then break from the loop */
      if (Si2158B_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
        break;
      /*  channel not found! **/
             freq += SCAN_INTERVAL;
         }
    }


 return 0;
}
/************************************************************************************************************************
  NAME: Si2158B_ATV_Channel_Scan_PAL
  DESCRIPTION: Performs a channel scan for PAL (Systems B/G, D/K, L/L', and I) of the band
  Programming Guide Reference:    Flowchart A.10.0 - A10.3 (ATV Channel Scan flowchart for PAL)

  NOTE: this function requires an external sound processor to determine the PAL standard.  The user is
  required to implement the functions: L0_InitSoundProcessor(); and L0_AcquireSoundStandard(..);

  Parameter:  Pointer to Si2158B Context (I2C address)
  Parameter:  starting Frequency Hz
  Parameter:  ending Frequency Hz
  Parameter:  min RSSI dBm
  Parameter:  max RSSI dBm
  Parameter:  min SNR 1/2 dB
  Parameter:  max SNR 1/2 dB
  Returns:    0 if successful, otherwise an error.
************************************************************************************************************************/
int Si2158B_ATV_Channel_Scan_PAL(L1_Si2158B_Context *Si2158B, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm)
{

  #define VHF_MAX 300000000
  #define SCAN_INTERVAL 1000000
  #define CHANNEL_NOT_FOUND 0
  char standard = Si2158B_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B;
  unsigned long freq;
  unsigned long channelIncrement;
  char posModulation;  /* flag for pos or neg modulation */
  int i;

  /*Clear the channel list size and channel array */
  Si2158B->ChannelListSize=0;

  for (i=0; i< MAX_POSSIBLE_CHANNELS;i++)
  {
    Si2158B->ChannelList[i]=0;
    Si2158B->ChannelType[i][0]='\0';
  }
    /* configure the RSQ / RSSI threshold properties */
    Si2158B->prop->atv_rsq_rssi_threshold.lo = minRSSIdBm;
    Si2158B->prop->atv_rsq_rssi_threshold.hi = maxRSSIdBm;

    if (Si2158B_L1_SetProperty2(Si2158B, Si2158B_ATV_RSQ_RSSI_THRESHOLD_PROP) != NO_Si2158B_ERROR)
    {
      return ERROR_Si2158B_SENDING_COMMAND;
    }
   /* setup AFC acquistion range property to 1.5MHz for scanning */
    Si2158B->prop->atv_afc_range.range_khz    =  1500;
    if (Si2158B_L1_SetProperty2(Si2158B, Si2158B_ATV_AFC_RANGE_PROP) != NO_Si2158B_ERROR)
    {
       return ERROR_Si2158B_SENDING_COMMAND;
    }
   /* Start Scanning */
    for (freq=rangeMinHz; freq < rangeMaxHz; )
    {
    /* before calling tune provide a callback stub that the user can update the frequency */
    /* if user requested abort then break from the loop */
    if (Si2158B_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
      break;
    /* set the modulation flag to 0 (neg) */
    posModulation=0;
    /* Negative Modulation configure the VideoMode property to System DK, PAL*/
    Si2158B->prop->atv_video_mode.video_sys = Si2158B_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK;    /* M ATV demodulation */
    Si2158B->prop->atv_video_mode.color     = Si2158B_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;    /* PAL_NTSC color system */
    if (Si2158B_L1_SetProperty2(Si2158B, Si2158B_ATV_VIDEO_MODE_PROP) != NO_Si2158B_ERROR)
    {
       return ERROR_Si2158B_SENDING_COMMAND;
    }

    /* Call the Tune command to tune the frequency */
    /* if successful (a station was found) then the return value will be 0. */
    if (!Si2158B_Tune (Si2158B, Si2158B_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq))
    {
      posModulation = 0;
    }
    else  /* We didn't find a station so try positive modulation */
     {
      /* Pos Modulation configure the VideoMode property to System DK, PAL*/
      Si2158B->prop->atv_video_mode.video_sys = Si2158B_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L;    /* L ATV demodulation */
      Si2158B->prop->atv_video_mode.color     = Si2158B_ATV_VIDEO_MODE_PROP_COLOR_SECAM;    /* SECAM color system */
      if (Si2158B_L1_SetProperty2(Si2158B, Si2158B_ATV_VIDEO_MODE_PROP) != NO_Si2158B_ERROR)
      {
         return ERROR_Si2158B_SENDING_COMMAND;
      }
      /* Call the Tune command to tune the frequency */
      /* if successful (a station was found) then the return value will be 0. */
      if (!Si2158B_Tune (Si2158B, Si2158B_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq))
      {
        posModulation=1;
      }
      else
      {
            /* if user requested abort then break from the loop */
          if (Si2158B_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
            break;

        /* we didn't find any channels goto flowchart section B */
        freq += SCAN_INTERVAL;
        continue;
      }
    }
    /* Initialize the sound processor.   This may or may not be required for your application */
/*    L1_InitSoundProcessor();*/
    /* Run the sound processor and return the standard(s) */
    #define SOUND_PROCESSOR_TIMEOUT 10
/*    L1_AcquireSoundStandard(SOUND_PROCESSOR_TIMEOUT , &standard);*/
    if ((standard == Si2158B_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B) || (standard == Si2158B_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH))
      {
      /* check for positive modulation */
      if (posModulation)
    {
          /* if user requested abort then break from the loop */
          if (Si2158B_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
            break;

      /* goto flowchart section B */
      freq += SCAN_INTERVAL;
      continue;
    }
      else
      {
        if (freq < VHF_MAX)
    {
          Si2158B->ChannelType[Si2158B->ChannelListSize][0]='B';
          Si2158B->ChannelType[Si2158B->ChannelListSize][1]='\0';
    }
    else
    {
          Si2158B->ChannelType[Si2158B->ChannelListSize][0]='G';
          Si2158B->ChannelType[Si2158B->ChannelListSize][1]='H';
          Si2158B->ChannelType[Si2158B->ChannelListSize][2]='\0';
    }
    }
    }
    else if (standard == Si2158B_ATV_VIDEO_MODE_PROP_VIDEO_SYS_I)
    {
        if (posModulation)
    {
                /* if user requested abort then break from the loop */
              if (Si2158B_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
                break;

          /* goto flowchart section B */
          freq += SCAN_INTERVAL;
          continue;
    }
        else
    {
          Si2158B->ChannelType[Si2158B->ChannelListSize][0]='I';
          Si2158B->ChannelType[Si2158B->ChannelListSize][1]='\0';
    }
    }
    else if ((standard == Si2158B_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L) || (standard == Si2158B_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK))
    {
        if (posModulation)
    {
          Si2158B->ChannelType[Si2158B->ChannelListSize][0]='L';
          Si2158B->ChannelType[Si2158B->ChannelListSize][1]='\0';
    }
        else
    {
          Si2158B->ChannelType[Si2158B->ChannelListSize][0]='D';
          Si2158B->ChannelType[Si2158B->ChannelListSize][1]='K';
          Si2158B->ChannelType[Si2158B->ChannelListSize][2]='\0';
    }
    }
    else
    {
      /* standard not found */
    /* if user requested abort then break from the loop */
    if (Si2158B_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
      break;

      /* goto flowchart section B */
      freq += SCAN_INTERVAL;
      continue;
    }
    /* if we got here, then we have a valid channel with a channelType */
            /* Get ATV status */
    if (Si2158B_L1_ATV_STATUS (Si2158B, Si2158B_ATV_STATUS_CMD_INTACK_OK))
            {
               return ERROR_Si2158B_SENDING_COMMAND;
            }
    if (Si2158B->ChannelType[Si2158B->ChannelListSize][0]=='B')
              {
            /* Add the afc_freq (khz) to the center frequency and add to the channel list */
      Si2158B->ChannelList[Si2158B->ChannelListSize]= freq + (Si2158B->rsp->atv_status.afc_freq * 1000)-500000;
                  channelIncrement = 7000000;
              }
              else
              {
                /* Add the afc_freq (khz) to the center frequency and add to the channel list */
      Si2158B->ChannelList[Si2158B->ChannelListSize]= freq + (Si2158B->rsp->atv_status.afc_freq * 1000);
                channelIncrement = 8000000;
              }
           /* Update the callback to indicate the channel is found */
            /* if user requested abort then break from the loop */
    if (Si2158B_UpdateChannelScanFrequency(Si2158B->ChannelList[Si2158B->ChannelListSize], Si2158B->ChannelListSize+1))
              break;
            /* go to the next frequency in the loop */
    freq = Si2158B->ChannelList[Si2158B->ChannelListSize++] + channelIncrement;
    }

 return 0;
}
/************************************************************************************************************************
  NAME: Si2158B_AGC_Override
  Parameter:  Pointer to Si2158B Context (I2C address)
  Parameter:  Mode 0=Normal, 1= Max, 2=TOP
  Returns:    I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si2158B_AGC_Override    (L1_Si2158B_Context *Si2158B, unsigned char mode )
{
    int return_code;
    SiTRACE("Si2158B_AGC_Override: mode = %d\n",mode);
    switch (mode)
    {
        case  Si2158B_FORCE_NORMAL_AGC:
            if ((return_code = Si2158B_L1_AGC_OVERRIDE (Si2158B, Si2158B_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_DISABLE,Si2158B_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_DISABLE)) != NO_Si2158B_ERROR)
                return return_code;
            break;
        case  Si2158B_FORCE_MAX_AGC:
            if ((return_code = Si2158B_L1_AGC_OVERRIDE (Si2158B, Si2158B_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_ENABLE,Si2158B_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_DISABLE)) != NO_Si2158B_ERROR)
                return return_code;
            break;
        case  Si2158B_FORCE_TOP_AGC:
            if ((return_code = Si2158B_L1_AGC_OVERRIDE (Si2158B, Si2158B_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_DISABLE,Si2158B_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_ENABLE)) != NO_Si2158B_ERROR)
                return return_code;
            break;

        default:
            return ERROR_Si2158B_PARAMETER_OUT_OF_RANGE;

    }

    return NO_Si2158B_ERROR;
}

/* _specific_code_insertion_point */





