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
                  Silicon Laboratories Broadcast Si2156 Layer 2 API
   L2 API for commands and properties
   FILE: Si2156_L2_API.c
   Supported IC : Si2156
   Compiled for ROM 13 firmware 3_1_build_9
   Revision: 0.3
   Tag:  TAGNAME
   Date: December 22 2011
****************************************************************************************/
#include <string.h>
/* Si2156 API Defines */
/* define this if using the ATV video filter */
#undef USING_ATV_FILTER
/* define this if using the DTV video filter */
#undef USING_DLIF_FILTER
/************************************************************************************************************************/
/* Si2156 API Specific Includes */
#include "Si2156_L2_API.h"               /* Include file for this code */
#include "Si2156_Firmware_3_1_build_9.h"       /* firmware compatible with Si2156-marking */
#define Si2156_BYTES_PER_LINE 8
#ifdef USING_ATV_FILTER
#include "write_ATV_video_coeffs.h"   /* .h file from custom Video filter Tool output */
#endif
#ifdef USING_DLIF_FILTER
#include "write_DLIF_video_coeffs.h"   /* .h file from custom Video filter Tool output */
#endif
/************************************************************************************************************************/
/************************************************************************************************************************
  NAME: Si2156_UpdateChannelScanFrequency
  DESCRIPTION:  This routine allows the user to implement an update of the current channel scan operation with
                the current frequency being scanned.
  Parameter:    Current frequency of the scan routine
  Parameter:	channelsFound = 0 if channel not found at that frequency , channelsFound > 0  the number of channels
				currently found( including this frequency )
  Returns:      1 if scan abort requested, 0 if ok.
************************************************************************************************************************/
int Si2156_UpdateChannelScanFrequency(int freq,int channelsFound)
{
	int abort = 0;
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

	if (abort)
		return 1;
	else
		return 0;
}

/************************************************************************************************************************/
/************************************************************************************************************************
  NAME: Si2156_Tune
  DESCRIPTIION: Tune Si2156 in specified mode (ATV/DTV) at center frequency, wait for TUNINT and xTVINT with timeout

  Parameter:  Pointer to Si2156 Context (I2C address)
  Parameter:  Mode (ATV or DTV) use Si2156_TUNER_TUNE_FREQ_CMD_MODE_ATV or Si2156_TUNER_TUNE_FREQ_CMD_MODE_DTV constants
  Parameter:  frequency (Hz) as a unsigned long integer
  Parameter:  rsp - commandResp structure to returns tune status info.
  Returns:    0 if channel found.  A nonzero value means either an error occurred or channel not locked.
  Programming Guide Reference:    Flowchart A.7 (Tune flowchart)
************************************************************************************************************************/
int Si2156_Tune (L1_Si2156_Context *api, unsigned char mode, unsigned long freq )
{
    int start_time  = 0;
    int return_code = 0;
   /* Note: the timeout of 30 ms is appropriate based on firmware testing.  However the clock() function in used in the */
    /* sample code system_time() function has a low resolution so 50 ms is used for the demonstration.  */
    /* A 30 ms timeout could be used if the  user timer is more accurate */
    int timeout     = 50;

    start_time = system_time();

    if (Si2156_L1_TUNER_TUNE_FREQ (api,
                                   mode,
                                   freq) != 0)
    {
        return ERROR_Si2156_SENDING_COMMAND;
    }

    /* wait for TUNINT, timeout is 30ms */
    while ( (system_time() - start_time) < timeout )
    {
        if ((return_code = Si2156_L1_CheckStatus(api)) != 0)
            return return_code;
        if (api->status->tunint)
            break;
    }
    if (!api->status->tunint) {
      SiTRACE("Timeout waiting for TUNINT\n");
      return ERROR_Si2156_TUNINT_TIMEOUT;
    }
    SiTRACE("TUNINT time = %d\n",system_time()-start_time);
    /* wait for xTVINT, timeout is 150ms for ATVINT and 10 ms for DTVINT */
    start_time = system_time();
    timeout    = ((mode==Si2156_TUNER_TUNE_FREQ_CMD_MODE_ATV) ? 150 : 10);
    while ( (system_time() - start_time) < timeout )
    {
        if ((return_code = Si2156_L1_CheckStatus(api)) != 0)
            return return_code;
        if (mode==Si2156_TUNER_TUNE_FREQ_CMD_MODE_ATV)
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

    if (mode==Si2156_TUNER_TUNE_FREQ_CMD_MODE_ATV)
    {
      if (api->status->atvint)
      {

        SiTRACE("ATV Tune Successful\n");
        return NO_Si2156_ERROR;
      }
      else
        SiTRACE("Timeout waiting for ATVINT\n");
    }
    else
    {
        if (api->status->dtvint)
        {
          SiTRACE("DTV Tune Successful \n");
          return NO_Si2156_ERROR;
        }
        else
          SiTRACE("Timeout waiting for DTVINT\n");
    }

    return ERROR_Si2156_xTVINT_TIMEOUT;
}

/************************************************************************************************************************
  NAME: Si2156_ATVTune
  DESCRIPTION:Update ATV_VIDEO_MODE and tune ATV mode at center frequency
  Parameter:  Pointer to Si2156 Context (I2C address)
  Parameter:  frequency (Hz)
  Parameter:  Video system , e.g. use constant Si2156_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M for system M
  Parameter:  transport,  e.g. use constant Si2156_ATV_VIDEO_MODE_PROP_TRANS_TERRESTRIAL for terrestrial
  Parameter:  color , e.g. use constant Si2156_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC for PAL or NTSC
  Parameter:  invert_spectrum , 0=normal 1=inverted
  Returns:    I2C transaction error code, 0 if successful
  Programming Guide Reference:    Flowchart A.7 (Tune flowchart)
************************************************************************************************************************/
int  Si2156_ATVTune (L1_Si2156_Context *Si2156, unsigned long freq, unsigned char video_sys, unsigned char trans, unsigned char color, unsigned char invert_spectrum)
{
    Si2156->prop->atv_video_mode.video_sys = video_sys;
    Si2156->prop->atv_video_mode.trans = trans;
    Si2156->prop->atv_video_mode.color = color;
    Si2156->prop->atv_video_mode.invert_spectrum = invert_spectrum;
    if (Si2156_L1_SetProperty2(Si2156, Si2156_ATV_VIDEO_MODE_PROP) != NO_Si2156_ERROR)
    {
      return ERROR_Si2156_SENDING_COMMAND;
    }

    return Si2156_Tune (Si2156, Si2156_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq);
}

/************************************************************************************************************************
  NAME: Si2156_DTVTune
  DESCRIPTION: Update DTV_MODE and tune DTV mode at center frequency
  Parameter:  Pointer to Si2156 Context (I2C address)
  Parameter:  frequency (Hz)
  Parameter:  bandwidth , 6,7 or 8 MHz
  Parameter:  modulation,  e.g. use constant Si2156_DTV_MODE_PROP_MODULATION_DVBT for DVBT mode
  Parameter:  invert_spectrum ,  NORMAL (0) or INVERTED (1)
   Returns:    I2C transaction error code, 0 if successful
  Programming Guide Reference:    Flowchart A.7 (Tune flowchart)
************************************************************************************************************************/
int  Si2156_DTVTune           (L1_Si2156_Context *Si2156, unsigned long freq, unsigned char bw, unsigned char modulation, unsigned char invert_spectrum)
{
    int return_code;
    return_code = NO_Si2156_ERROR;

    /* update DTV_MODE_PROP property */
    Si2156->prop->dtv_mode.bw = bw;
    Si2156->prop->dtv_mode.invert_spectrum = invert_spectrum;
    Si2156->prop->dtv_mode.modulation = modulation;
    if (Si2156_L1_SetProperty2(Si2156, Si2156_DTV_MODE_PROP) != NO_Si2156_ERROR)
    {
      return ERROR_Si2156_SENDING_COMMAND;
    }

    return_code = Si2156_Tune (Si2156, Si2156_TUNER_TUNE_FREQ_CMD_MODE_DTV, freq);

    return return_code;
}
/************************************************************************************************************************
  NAME: Si2156_Configure
  DESCRIPTION: Setup Si2156 video filters, GPIOs/clocks, Common Properties startup, Tuner startup, ATV startup, and DTV startup.
  Parameter:  Pointer to Si2156 Context
  Returns:    I2C transaction error code, NO_Si2156_ERROR if successful
************************************************************************************************************************/
int Si2156_Configure           (L1_Si2156_Context *api)
{
    int return_code;
    return_code = NO_Si2156_ERROR;
   /* load ATV video filter file */
  #ifdef USING_ATV_FILTER
    if ((return_code = LoadVideofilter(api,ATV_VIDFILT_TABLE,ATV_VIDFILT_LINES)) != NO_Si2156_ERROR)
       return return_code;
  #endif

  /* load DTV video filter file */
  #ifdef USING_DLIF_FILTER
     if ((return_code = LoadVideofilter(api,DLIF_VIDFILT_TABLE,DLIF_VIDFILT_LINES)) != NO_Si2156_ERROR)
       return return_code;
  #endif
    /* Set All Properties startup configuration */
    Si2156_setupAllDefaults     (api);
    Si2156_downloadAllProperties(api);

    return return_code;
}
/************************************************************************************************************************
  NAME: Si2156_PowerUpWithPatch
  DESCRIPTION: Send Si2156 API PowerUp Command with PowerUp to bootloader,
  Check the Chip rev and part, and ROMID are compared to expected values.
  Load the Firmware Patch then Start the Firmware.
  Programming Guide Reference:    Flowchart A.2 (POWER_UP with patch flowchart)

  Parameter:  pointer to Si2156 Context
  Returns:    Si2156/I2C transaction error code, NO_Si2156_ERROR if successful
************************************************************************************************************************/
int Si2156_PowerUpWithPatch    (L1_Si2156_Context *api)
{
    int return_code;
    return_code = NO_Si2156_ERROR;

    /* always wait for CTS prior to POWER_UP command */
    if ((return_code = Si2156_pollForCTS  (api)) != NO_Si2156_ERROR) {
        SiTRACE ("Si2156_pollForCTS error 0x%02x\n", return_code);
        return return_code;
    }

    if ((return_code = Si2156_L1_POWER_UP (api,
                            Si2156_POWER_UP_CMD_SUBCODE_CODE,
                            Si2156_POWER_UP_CMD_RESERVED1_RESERVED,
                            Si2156_POWER_UP_CMD_RESERVED2_RESERVED,
                            Si2156_POWER_UP_CMD_RESERVED3_RESERVED,
                            Si2156_POWER_UP_CMD_CLOCK_MODE_XTAL,
                            Si2156_POWER_UP_CMD_CLOCK_FREQ_CLK_24MHZ,
                            Si2156_POWER_UP_CMD_ADDR_MODE_CURRENT,
                            Si2156_POWER_UP_CMD_FUNC_BOOTLOADER,        /* start in bootloader mode */
                            Si2156_POWER_UP_CMD_CTSIEN_DISABLE,
                            Si2156_POWER_UP_CMD_WAKE_UP_WAKE_UP)) != NO_Si2156_ERROR)
    {
        SiTRACE ("Si2156_L1_POWER_UP error 0x%02x: %s\n", return_code, Si2156_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }

    /* Get the Part Info from the chip.   This command is only valid in Bootloader mode */
    if ((return_code = Si2156_L1_PART_INFO(api)) != NO_Si2156_ERROR) {
        SiTRACE ("Si2156_L1_PART_INFO error 0x%02x: %s\n", return_code, Si2156_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }
    SiTRACE("chiprev %d\n",        api->rsp->part_info.chiprev);
    SiTRACE("part    Si21%d\n",    api->rsp->part_info.part   );
    SiTRACE("pmajor  %d\n",        api->rsp->part_info.pmajor );
    if (api->rsp->part_info.pmajor >= 0x30) {
    SiTRACE("pmajor '%c'\n",       api->rsp->part_info.pmajor );
    }
    SiTRACE("pminor  %d\n",        api->rsp->part_info.pminor );
    if (api->rsp->part_info.pminor >= 0x30) {
    SiTRACE("pminor '%c'\n",       api->rsp->part_info.pminor );
    }
    SiTRACE("romid %3d/0x%02x\n",  api->rsp->part_info.romid,  api->rsp->part_info.romid );
#ifdef    PART_INTEGRITY_CHECKS
    /* Check the Chip revision, part and ROMID against expected values and report an error if incompatible */
    if (api->rsp->part_info.chiprev != api->chiprev) {
        SiTRACE ("INCOMPATIBLE PART error chiprev %d (expected %d)\n", api->rsp->part_info.chiprev, api->chiprev);
        return_code = ERROR_Si2156_INCOMPATIBLE_PART;
    }
    /* Part Number is represented as the last 2 digits */
    if (api->rsp->part_info.part != api->part) {
        SiTRACE ("INCOMPATIBLE PART error part   %d (expected %d)\n", api->rsp->part_info.part, api->part);
        return_code = ERROR_Si2156_INCOMPATIBLE_PART;
    }
    /* Part Major Version in ASCII */
    if (api->rsp->part_info.pmajor != api->partMajorVersion) {
        SiTRACE ("INCOMPATIBLE PART error pmajor %d (expected %d)\n", api->rsp->part_info.pmajor, api->partMajorVersion);
        return_code = ERROR_Si2156_INCOMPATIBLE_PART;
    }
    /* Part Minor Version in ASCII */
    if (api->rsp->part_info.pminor != api->partMinorVersion) {
        SiTRACE ("INCOMPATIBLE PART error pminor %d (expected %d)\n", api->rsp->part_info.pminor, api->partMinorVersion);
        return_code = ERROR_Si2156_INCOMPATIBLE_PART;
    }
    /* ROMID in byte representation */
    if (api->rsp->part_info.romid != api->partRomid) {
        SiTRACE ("INCOMPATIBLE PART error romid %3d (expected %2d)\n", api->rsp->part_info.romid, api->partRomid);
        return_code = ERROR_Si2156_INCOMPATIBLE_PART;
    }
    if (return_code != NO_Si2156_ERROR) return return_code;
#endif /* PART_INTEGRITY_CHECKS */

    if (api->rsp->part_info.romid == 0x13) {
      /* Load the Firmware */
       if ((return_code = Si2156_LoadFirmware(api, Si2156_FW_3_1b9, FIRMWARE_LINES_3_1b9)) != NO_Si2156_ERROR) {
         SiTRACE ("Si2156_LoadFirmware error 0x%02x: %s\n", return_code, Si2156_L1_API_ERROR_TEXT(return_code) );
         return return_code;
       }
    }

    /*Start the Firmware */
    if ((return_code = Si2156_StartFirmware(api)) != NO_Si2156_ERROR) { /* Start firmware */
        SiTRACE ("Si2156_StartFirmware error 0x%02x: %s\n", return_code, Si2156_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }

    return NO_Si2156_ERROR;
}
/************************************************************************************************************************
  NAME: Si2156_LoadFirmware
  DESCRIPTON: Load firmware from FIRMWARE_TABLE array in Si2156_Firmware_x_y_build_z.h file into Si2156
              Requires Si2156 to be in bootloader mode after PowerUp
  Programming Guide Reference:    Flowchart A.3 (Download FW PATCH flowchart)

  Parameter:  Si2156 Context (I2C address)
  Parameter:  pointer to firmware table array
  Parameter:  number of lines in firmware table array (size in bytes / BYTES_PER_LINE)
  Returns:    Si2156/I2C transaction error code, NO_Si2156_ERROR if successful
************************************************************************************************************************/
int Si2156_LoadFirmware        (L1_Si2156_Context *api, unsigned char fw_table[], int nbLines)
{
    int return_code;
    int line;
    return_code = NO_Si2156_ERROR;

    SiTRACE ("Si2156_LoadFirmware starting...\n");
    SiTRACE ("Si2156_LoadFirmware nbLines %d\n", nbLines);

    /* for each line in fw_table */
    for (line = 0; line < nbLines; line++)
    {
        /* send Si2156_BYTES_PER_LINE fw bytes to Si2156 */
        if ((return_code = Si2156_L1_API_Patch(api, Si2156_BYTES_PER_LINE, fw_table + Si2156_BYTES_PER_LINE*line)) != NO_Si2156_ERROR)
        {
          SiTRACE("Si2156_LoadFirmware error 0x%02x patching line %d: %s\n", return_code, line, Si2156_L1_API_ERROR_TEXT(return_code) );
          if (line == 0) {
          SiTRACE("The firmware is incompatible with the part!\n");
          }
          return ERROR_Si2156_LOADING_FIRMWARE;
        }
        if (line==3) SiTraceConfiguration("traces -output none");
    }
    SiTraceConfiguration("traces -output file");
    SiTRACE ("Si2156_LoadFirmware complete...\n");
    return NO_Si2156_ERROR;
}
/************************************************************************************************************************
  NAME: Si2156_StartFirmware
  DESCRIPTION: Start Si2156 firmware (put the Si2156 into run mode)
  Parameter:   Si2156 Context (I2C address)
  Parameter (passed by Reference):   ExitBootloadeer Response Status byte : tunint, atvint, dtvint, err, cts
  Returns:     I2C transaction error code, NO_Si2156_ERROR if successful
************************************************************************************************************************/
int Si2156_StartFirmware       (L1_Si2156_Context *api)
{

    if (Si2156_L1_EXIT_BOOTLOADER(api, Si2156_EXIT_BOOTLOADER_CMD_FUNC_TUNER, Si2156_EXIT_BOOTLOADER_CMD_CTSIEN_OFF) != NO_Si2156_ERROR)
    {
        return ERROR_Si2156_STARTING_FIRMWARE;
    }

    return NO_Si2156_ERROR;
}
/************************************************************************************************************************
  NAME: Si2156_Init
  DESCRIPTION:Reset and Initialize Si2156
  Parameter:  Si2156 Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2156_ERROR if successful
************************************************************************************************************************/
int Si2156_Init                (L1_Si2156_Context *api)
{
    int return_code;
    SiTRACE("Si2156_Init starting...\n");

    if ((return_code = Si2156_PowerUpWithPatch(api)) != NO_Si2156_ERROR) {   /* PowerUp into bootloader */
        SiTRACE ("Si2156_PowerUpWithPatch error 0x%02x: %s\n", return_code, Si2156_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }
    /* At this point, FW is loaded and started.  */
    Si2156_Configure(api);
    SiTRACE("Si2156_Init complete...\n");
    return NO_Si2156_ERROR;
}
/************************************************************************************************************************
  NAME: Si2156_LoadVideofilter
  DESCRIPTION:        Load video filters from vidfiltTable in Si2156_write_xTV_video_coeffs.h file into Si2156
  Programming Guide Reference:    Flowchart A.4 (Download Video Filters flowchart)

  Parameter:  Si2156 Context (I2C address)
  Parameter:  pointer to video filter table array
  Parameter:  number of lines in video filter table array (size in bytes / BYTES_PER_LINE)
  Returns:    Si2156/I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si2156_LoadVideofilter     (L1_Si2156_Context *api,unsigned char* vidfiltTable,int lines)
{
#define BYTES_PER_LINE 8
    int line;

    /* for each 8 bytes in VIDFILT_TABLE */
    for (line = 0; line < lines; line++)
    {
        /* send that 8 byte I2C command to Si2156 */
        if (Si2156_L1_API_Patch(api, BYTES_PER_LINE, vidfiltTable+BYTES_PER_LINE*line) != 0)
        {
            return ERROR_Si2156_SENDING_COMMAND;
        }
    }
    return NO_Si2156_ERROR;
}
/************************************************************************************************************************
  NAME: Si2156_ClockOn
  Parameter:  Pointer to Si2156 Context (I2C address)
  Returns:    I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si2156_ClockOn             (L1_Si2156_Context *api)
{
    int return_code;
    SiTRACE("Si2156_CLOCK_ON: Turning clock ON\n");

    if ((return_code = Si2156_L1_CONFIG_PINS (api,
                               Si2156_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE,
                               Si2156_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ,
                               Si2156_CONFIG_PINS_CMD_GPIO2_MODE_NO_CHANGE,
                               Si2156_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ,
                               Si2156_CONFIG_PINS_CMD_GPIO3_MODE_NO_CHANGE,
                               Si2156_CONFIG_PINS_CMD_GPIO3_READ_DO_NOT_READ,
                               Si2156_CONFIG_PINS_CMD_BCLK1_MODE_XOUT,
                               Si2156_CONFIG_PINS_CMD_BCLK1_READ_DO_NOT_READ,
                               Si2156_CONFIG_PINS_CMD_XOUT_MODE_DISABLE)) !=0)
    return return_code;

    return NO_Si2156_ERROR;
}
/************************************************************************************************************************
  NAME: Si2156_ClockOff
  Parameter:  Pointer to Si2156 Context (I2C address)
  Returns:    I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si2156_ClockOff            (L1_Si2156_Context *api)
{
    int return_code;
    SiTRACE("Si2156_CLOCK_OFF: Turning clock OFF\n");

    if ((return_code = Si2156_L1_CONFIG_PINS (api,
                               Si2156_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE,
                               Si2156_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ,
                               Si2156_CONFIG_PINS_CMD_GPIO2_MODE_NO_CHANGE,
                               Si2156_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ,
                               Si2156_CONFIG_PINS_CMD_GPIO3_MODE_NO_CHANGE,
                               Si2156_CONFIG_PINS_CMD_GPIO3_READ_DO_NOT_READ,
                               Si2156_CONFIG_PINS_CMD_BCLK1_MODE_DISABLE,
                               Si2156_CONFIG_PINS_CMD_BCLK1_READ_DO_NOT_READ,
                               Si2156_CONFIG_PINS_CMD_XOUT_MODE_DISABLE)) !=0)
    return return_code;

    return NO_Si2156_ERROR;
}
/************************************************************************************************************************
  NAME: Si2156_XOUTOn
  Parameter:  Pointer to Si2156 Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2156_ERROR if successful
************************************************************************************************************************/
int Si2156_XOUTOn           (L1_Si2156_Context *api)
{
    int return_code;
    SiTRACE("Si2156_XOUT_ON: Turning XOUT ON\n");

    if ((return_code = Si2156_L1_CONFIG_PINS (api,
                               Si2156_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE,
                               Si2156_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ,
                               Si2156_CONFIG_PINS_CMD_GPIO2_MODE_NO_CHANGE,
                               Si2156_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ,
                               Si2156_CONFIG_PINS_CMD_GPIO3_MODE_NO_CHANGE,
                               Si2156_CONFIG_PINS_CMD_GPIO3_READ_DO_NOT_READ,
                               Si2156_CONFIG_PINS_CMD_BCLK1_MODE_NO_CHANGE,
                               Si2156_CONFIG_PINS_CMD_BCLK1_READ_DO_NOT_READ,
                               Si2156_CONFIG_PINS_CMD_XOUT_MODE_XOUT)) != NO_Si2156_ERROR)
    return return_code;

    return NO_Si2156_ERROR;
}
/************************************************************************************************************************
  NAME: Si2156_XOUTOff
  Parameter:  Pointer to Si2156 Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2156_ERROR if successful
************************************************************************************************************************/
int Si2156_XOUTOff         (L1_Si2156_Context *api)
{
    int return_code;
    SiTRACE("Si2156_XOUT_OFF: Turning clock OFF\n");

    if ((return_code = Si2156_L1_CONFIG_PINS (api,
                               Si2156_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE,
                               Si2156_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ,
                               Si2156_CONFIG_PINS_CMD_GPIO2_MODE_NO_CHANGE,
                               Si2156_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ,
                               Si2156_CONFIG_PINS_CMD_GPIO3_MODE_NO_CHANGE,
                               Si2156_CONFIG_PINS_CMD_GPIO3_READ_DO_NOT_READ,
                               Si2156_CONFIG_PINS_CMD_BCLK1_MODE_NO_CHANGE,
                               Si2156_CONFIG_PINS_CMD_BCLK1_READ_DO_NOT_READ,
                               Si2156_CONFIG_PINS_CMD_XOUT_MODE_DISABLE)) != NO_Si2156_ERROR)
    return return_code;

    return NO_Si2156_ERROR;
}
/************************************************************************************************************************
  NAME: Si2156_Standby
  Parameter:  Pointer to Si2156 Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2156_ERROR if successful
************************************************************************************************************************/
int Si2156_Standby         (L1_Si2156_Context *api)
{
    int return_code;
    SiTRACE("Si2156_CLOCK_OFF: Turning clock OFF\n");

    if ((return_code = Si2156_L1_STANDBY(api,Si2156_STANDBY_CMD_TYPE_NORMAL)) != NO_Si2156_ERROR)
    return return_code;

    return NO_Si2156_ERROR;
}
/************************************************************************************************************************
  NAME: Si2156_Powerdown
  Parameter:  Pointer to Si2156 Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2156_ERROR if successful
************************************************************************************************************************/
int Si2156_Powerdown         (L1_Si2156_Context *api)
{
    int return_code;
    SiTRACE("Si2156_CLOCK_OFF: Turning clock OFF\n");

    if ((return_code = Si2156_L1_POWER_DOWN(api)) != NO_Si2156_ERROR)
    return return_code;

    return NO_Si2156_ERROR;
}
/************************************************************************************************************************
  NAME: Si2156_ATV_Channel_Scan_M
  DESCRIPTION: Performs a channel scan for NTSC (System M) of the band
  Programming Guide Reference:    Flowchart A.11.0 and A11.1 (ATV Channel Scan flowchart for System M)

  Parameter:  Pointer to Si2156 Context (I2C address)
  Parameter:  starting Frequency Hz
  Parameter:  ending Frequency Hz
  Parameter:  min RSSI dBm
  Parameter:  max RSSI dBm
  Parameter:  min SNR 1/2 dB
  Parameter:  max SNR 1/2 dB
  Returns:    0 if successful, otherwise an error.
************************************************************************************************************************/
int Si2156_ATV_Channel_Scan_M(L1_Si2156_Context *Si2156, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm)
{
     #define SCAN_INTERVAL     1000000
    #define CHANNEL_BANDWIDTH 6000000
    #define CHANNEL_NOT_FOUND       0

    unsigned long freq;
    int i;

    /*Clear the channel list size and channel array */
    Si2156->ChannelListSize=0;

    for (i=0; i< MAX_POSSIBLE_CHANNELS;i++)
    Si2156->ChannelList[i]=0;
    /* configure the VideoMode property to System M, NTSC*/
    Si2156->prop->atv_video_mode.video_sys = Si2156_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M;    /* M ATV demodulation */
    Si2156->prop->atv_video_mode.color     = Si2156_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;    /* PAL_NTSC color system */
    Si2156->prop->atv_video_mode.trans     = Si2156_ATV_VIDEO_MODE_PROP_TRANS_TERRESTRIAL;    /* set trans to Terrestrial */
    if (Si2156_L1_SetProperty2(Si2156, Si2156_ATV_VIDEO_MODE_PROP) != NO_Si2156_ERROR)
    {
       return ERROR_Si2156_SENDING_COMMAND;
    }
    /* configure the RSQ / RSSI threshold properties */
    Si2156->prop->atv_rsq_rssi_threshold.lo = minRSSIdBm;
    Si2156->prop->atv_rsq_rssi_threshold.hi = maxRSSIdBm;

    if (Si2156_L1_SetProperty2(Si2156, Si2156_ATV_RSQ_RSSI_THRESHOLD_PROP) != NO_Si2156_ERROR)
    {
       return ERROR_Si2156_SENDING_COMMAND;
    }

  /* setup IEN properties to enable TUNINT on TC  */
    Si2156->prop->tuner_ien.tcien     =  Si2156_TUNER_IEN_PROP_TCIEN_ENABLE;
    Si2156->prop->tuner_ien.rssilien  =  Si2156_TUNER_IEN_PROP_RSSILIEN_DISABLE;
    Si2156->prop->tuner_ien.rssihien  =  Si2156_TUNER_IEN_PROP_RSSIHIEN_DISABLE;

    if (Si2156_L1_SetProperty2(Si2156, Si2156_TUNER_IEN_PROP) != NO_Si2156_ERROR)
    {
      return ERROR_Si2156_SENDING_COMMAND;
    }

   /* setup IEN properties to enable ATVINT on CHL  */
    Si2156->prop->atv_ien.chlien    =  Si2156_ATV_IEN_PROP_CHLIEN_ENABLE;
    Si2156->prop->atv_ien.pclien    =  Si2156_ATV_IEN_PROP_PCLIEN_DISABLE;
    if (Si2156_L1_SetProperty2(Si2156, Si2156_ATV_IEN_PROP) != NO_Si2156_ERROR)
    {
      return ERROR_Si2156_SENDING_COMMAND;
    }
   /* setup AFC acquistion range property to 1.5MHz for scanning */
    Si2156->prop->atv_afc_range.range_khz    =  1500;
    if (Si2156_L1_SetProperty2(Si2156, Si2156_ATV_AFC_RANGE_PROP) != NO_Si2156_ERROR)
    {
       return ERROR_Si2156_SENDING_COMMAND;
    }
   /* Start Scanning */
    for (freq=rangeMinHz; freq < rangeMaxHz; )
    {

    /* before calling tune provide a callback stub that the user can update the frequency */
    /* if user requested abort then break from the loop */
    if (Si2156_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
      break;

    /* Call the Tune command to tune the frequency */
    /* if successful (a station was found) then the return value will be 0. */
    if (!Si2156_Tune (Si2156, Si2156_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq))
    {

            /* Get ATV status */
      if (Si2156_L1_ATV_STATUS (Si2156, Si2156_ATV_STATUS_CMD_INTACK_OK))
      {
        return ERROR_Si2156_SENDING_COMMAND;
      }


      /* Add the afc_freq (khz) to the center frequency and add to the channel list */
      Si2156->ChannelList[Si2156->ChannelListSize]= freq + (Si2156->rsp->atv_status.afc_freq * 1000);
      /* Update the callback to indicate the channel is found */
      /* if user requested abort then break from the loop */
      if (Si2156_UpdateChannelScanFrequency(freq + (Si2156->rsp->atv_status.afc_freq * 1000), Si2156->ChannelListSize+1))
        break;

            freq = Si2156->ChannelList[Si2156->ChannelListSize++] + CHANNEL_BANDWIDTH;
         }
         else  /* We didn't find a station at this frequency so increment and move on */
         {
        /* if user requested abort then break from the loop */
      if (Si2156_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
        break;
      /*  channel not found! **/
             freq += SCAN_INTERVAL;
         }
    }
    /* Set AFC Range back to 100  */
    Si2156->prop->atv_afc_range.range_khz    =  100;
    if (Si2156_L1_SetProperty2(Si2156, Si2156_ATV_AFC_RANGE_PROP) != NO_Si2156_ERROR)
    {
        return ERROR_Si2156_SENDING_COMMAND;
    }

 return 0;
}
/************************************************************************************************************************
  NAME: Si2156_ATV_Channel_Scan_PAL
  DESCRIPTION: Performs a channel scan for PAL (Systems B/G, D/K, L/L', and I) of the band
  Programming Guide Reference:    Flowchart A.10.0 - A10.3 (ATV Channel Scan flowchart for PAL)

  NOTE: this function requires an external sound processor to determine the PAL standard.  The user is
  required to implement the functions: L0_InitSoundProcessor(); and L0_AcquireSoundStandard(..);

  Parameter:  Pointer to Si2156 Context (I2C address)
  Parameter:  starting Frequency Hz
  Parameter:  ending Frequency Hz
  Parameter:  min RSSI dBm
  Parameter:  max RSSI dBm
  Parameter:  min SNR 1/2 dB
  Parameter:  max SNR 1/2 dB
  Returns:    0 if successful, otherwise an error.
************************************************************************************************************************/
int Si2156_ATV_Channel_Scan_PAL(L1_Si2156_Context *Si2156, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm)
{

  #define VHF_MAX 300000000
  #define SCAN_INTERVAL 1000000
  #define CHANNEL_NOT_FOUND 0
  char standard = Si2156_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B;
  unsigned long freq;
  unsigned long channelIncrement;
  char posModulation;  /* flag for pos or neg modulation */
  int i;

  /*Clear the channel list size and channel array */
  Si2156->ChannelListSize=0;

  for (i=0; i< MAX_POSSIBLE_CHANNELS;i++)
  {
    Si2156->ChannelList[i]=0;
    Si2156->ChannelType[i][0]='\0';
  }
    /* configure the RSQ / RSSI threshold properties */
    Si2156->prop->atv_rsq_rssi_threshold.lo = minRSSIdBm;
    Si2156->prop->atv_rsq_rssi_threshold.hi = maxRSSIdBm;

    if (Si2156_L1_SetProperty2(Si2156, Si2156_ATV_RSQ_RSSI_THRESHOLD_PROP) != NO_Si2156_ERROR)
    {
       return ERROR_Si2156_SENDING_COMMAND;
    }
  /* setup IEN properties to enable TUNINT on TC  */
    Si2156->prop->tuner_ien.tcien     =  Si2156_TUNER_IEN_PROP_TCIEN_ENABLE;
    Si2156->prop->tuner_ien.rssilien  =  Si2156_TUNER_IEN_PROP_RSSILIEN_DISABLE;
    Si2156->prop->tuner_ien.rssihien  =  Si2156_TUNER_IEN_PROP_RSSIHIEN_DISABLE;

    if (Si2156_L1_SetProperty2(Si2156, Si2156_TUNER_IEN_PROP) != NO_Si2156_ERROR)
    {
      return ERROR_Si2156_SENDING_COMMAND;
    }

   /* setup IEN properties to enable ATVINT on CHL  */
    Si2156->prop->atv_ien.chlien    =  Si2156_ATV_IEN_PROP_CHLIEN_ENABLE;
    Si2156->prop->atv_ien.pclien    =  Si2156_ATV_IEN_PROP_PCLIEN_DISABLE;
    if (Si2156_L1_SetProperty2(Si2156, Si2156_ATV_IEN_PROP) != NO_Si2156_ERROR)
    {
      return ERROR_Si2156_SENDING_COMMAND;
    }
   /* setup AFC acquistion range property to 1.5MHz for scanning */
    Si2156->prop->atv_afc_range.range_khz    =  1500;
    if (Si2156_L1_SetProperty2(Si2156, Si2156_ATV_AFC_RANGE_PROP) != NO_Si2156_ERROR)
    {
       return ERROR_Si2156_SENDING_COMMAND;
    }
   /* Start Scanning */
    for (freq=rangeMinHz; freq < rangeMaxHz; )
    {
    /* before calling tune provide a callback stub that the user can update the frequency */
    /* if user requested abort then break from the loop */
    if (Si2156_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
      break;
    /* set the modulation flag to 0 (neg) */
    posModulation=0;
    /* Negative Modulation configure the VideoMode property to System DK, PAL*/
    Si2156->prop->atv_video_mode.video_sys = Si2156_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK;    /* M ATV demodulation */
    Si2156->prop->atv_video_mode.color     = Si2156_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;    /* PAL_NTSC color system */
    Si2156->prop->atv_video_mode.trans     = Si2156_ATV_VIDEO_MODE_PROP_TRANS_TERRESTRIAL;    /* set trans to Terrestrial */
    if (Si2156_L1_SetProperty2(Si2156, Si2156_ATV_VIDEO_MODE_PROP) != NO_Si2156_ERROR)
    {
       return ERROR_Si2156_SENDING_COMMAND;
    }

    /* Call the Tune command to tune the frequency */
    /* if successful (a station was found) then the return value will be 0. */
    if (!Si2156_Tune (Si2156, Si2156_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq))
    {
      posModulation = 0;
         }
         else  /* We didn't find a station so try positive modulation */
         {
      /* Pos Modulation configure the VideoMode property to System DK, PAL*/
      Si2156->prop->atv_video_mode.video_sys = Si2156_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L;    /* L ATV demodulation */
      Si2156->prop->atv_video_mode.color     = Si2156_ATV_VIDEO_MODE_PROP_COLOR_SECAM;    /* SECAM color system */
      Si2156->prop->atv_video_mode.trans     = Si2156_ATV_VIDEO_MODE_PROP_TRANS_TERRESTRIAL;    /* set trans to Terrestrial */
      if (Si2156_L1_SetProperty2(Si2156, Si2156_ATV_VIDEO_MODE_PROP) != NO_Si2156_ERROR)
      {
         return ERROR_Si2156_SENDING_COMMAND;
      }
      /* Call the Tune command to tune the frequency */
      /* if successful (a station was found) then the return value will be 0. */
      if (!Si2156_Tune (Si2156, Si2156_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq))
      {
        posModulation=1;
      }
      else
      {
            /* if user requested abort then break from the loop */
          if (Si2156_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
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
    if ((standard == Si2156_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B) || (standard == Si2156_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH))
    {
      /* check for positive modulation */
      if (posModulation)
      {
            /* if user requested abort then break from the loop */
          if (Si2156_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
            break;

        /* goto flowchart section B */
        freq += SCAN_INTERVAL;
        continue;
      }
      else
      {
        if (freq < VHF_MAX)
        {
          Si2156->ChannelType[Si2156->ChannelListSize][0]='B';
          Si2156->ChannelType[Si2156->ChannelListSize][1]='\0';
        }
        else
        {
          Si2156->ChannelType[Si2156->ChannelListSize][0]='G';
          Si2156->ChannelType[Si2156->ChannelListSize][1]='H';
          Si2156->ChannelType[Si2156->ChannelListSize][2]='\0';
        }
      }
    }
    else if (standard == Si2156_ATV_VIDEO_MODE_PROP_VIDEO_SYS_I)
    {
        if (posModulation)
        {
                /* if user requested abort then break from the loop */
              if (Si2156_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
                break;

          /* goto flowchart section B */
          freq += SCAN_INTERVAL;
          continue;
        }
        else
        {
          Si2156->ChannelType[Si2156->ChannelListSize][0]='I';
          Si2156->ChannelType[Si2156->ChannelListSize][1]='\0';
        }
    }
    else if ((standard == Si2156_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L) || (standard == Si2156_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK))
    {
        if (posModulation)
        {
          Si2156->ChannelType[Si2156->ChannelListSize][0]='L';
          Si2156->ChannelType[Si2156->ChannelListSize][1]='\0';
        }
        else
        {
          Si2156->ChannelType[Si2156->ChannelListSize][0]='D';
          Si2156->ChannelType[Si2156->ChannelListSize][1]='K';
          Si2156->ChannelType[Si2156->ChannelListSize][2]='\0';
        }
    }
    else
    {
      /* standard not found */
            /* if user requested abort then break from the loop */
            if (Si2156_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
          break;

      /* goto flowchart section B */
      freq += SCAN_INTERVAL;
      continue;
    }
    /* if we got here, then we have a valid channel with a channelType */
    /* Get ATV status */
    if (Si2156_L1_ATV_STATUS (Si2156, Si2156_ATV_STATUS_CMD_INTACK_OK))
    {
      return ERROR_Si2156_SENDING_COMMAND;
    }
    if (Si2156->ChannelType[Si2156->ChannelListSize][0]=='B')
    {
      /* Add the afc_freq (khz) to the center frequency and add to the channel list */
      Si2156->ChannelList[Si2156->ChannelListSize]= freq + (Si2156->rsp->atv_status.afc_freq * 1000)-500000;
      channelIncrement = 7000000;
    }
    else
    {
    /* Add the afc_freq (khz) to the center frequency and add to the channel list */
      Si2156->ChannelList[Si2156->ChannelListSize]= freq + (Si2156->rsp->atv_status.afc_freq * 1000);
      channelIncrement = 8000000;
    }
    /* Update the callback to indicate the channel is found */
    /* if user requested abort then break from the loop */
    if (Si2156_UpdateChannelScanFrequency(Si2156->ChannelList[Si2156->ChannelListSize], Si2156->ChannelListSize+1))
      break;
    /* go to the next frequency in the loop */
    freq = Si2156->ChannelList[Si2156->ChannelListSize++] + channelIncrement;
    }
    /* Set AFC Range back to 100  */
    Si2156->prop->atv_afc_range.range_khz    =  100;
    if (Si2156_L1_SetProperty2(Si2156, Si2156_ATV_AFC_RANGE_PROP) != NO_Si2156_ERROR)
    {
        return ERROR_Si2156_SENDING_COMMAND;
    }

 return 0;
}
/************************************************************************************************************************
  NAME: Si2156_AGC_Override
  Parameter:  Pointer to Si2156 Context (I2C address)
  Parameter:  Mode 0=Normal, 1= Max, 2=TOP
  Returns:    I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si2156_AGC_Override    (L1_Si2156_Context *Si2156, unsigned char mode )
{
    int return_code;
    SiTRACE("Si2156_AGC_Override: mode = %d\n",mode);
    switch (mode)
    {
        case  Si2156_FORCE_NORMAL_AGC:
            if ((return_code = Si2156_L1_AGC_OVERRIDE (Si2156, Si2156_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_DISABLE,Si2156_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_DISABLE)) != NO_Si2156_ERROR)
                return return_code;
            break;
        case  Si2156_FORCE_MAX_AGC:
            if ((return_code = Si2156_L1_AGC_OVERRIDE (Si2156, Si2156_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_ENABLE,Si2156_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_DISABLE)) != NO_Si2156_ERROR)
                return return_code;
            break;
        case  Si2156_FORCE_TOP_AGC:
            if ((return_code = Si2156_L1_AGC_OVERRIDE (Si2156, Si2156_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_DISABLE,Si2156_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_ENABLE)) != NO_Si2156_ERROR)
                return return_code;
            break;

        default:
            return ERROR_Si2156_PARAMETER_OUT_OF_RANGE;

    }

    return NO_Si2156_ERROR;
}




