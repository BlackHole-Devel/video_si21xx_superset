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
                  Silicon Laboratories Broadcast Si2146 Layer 2 API
   L2 API for commands and properties
   FILE: Si2146_L2_API.c
   Supported IC : Si2146
   Compiled for ROM 11 firmware 1_1_build_3
   Revision: 0.1
   Tag:  TAGNAME
   Date: December 23 2011
****************************************************************************************/
#include <string.h>
/* Si2146 API Defines */
/* define this if using the ATV video filter */
#undef USING_ATV_FILTER
/* define this if using the DTV video filter */
#undef USING_DLIF_FILTER
/************************************************************************************************************************/
/* Si2146 API Specific Includes */
#include "Si2146_L2_API.h"               /* Include file for this code */

#ifdef LOAD_PATCH_11b3
#include "Si2146_Firmware_1_1_build_3.h"       /* firmware compatible with Si2146-A10-GM */
#endif

#define Si2146_BYTES_PER_LINE 8
#ifdef USING_ATV_FILTER
#include "write_ATV_video_coeffs.h"   /* .h file from custom Video filter Tool output */
#endif
#ifdef USING_DLIF_FILTER
#include "write_DLIF_video_coeffs.h"   /* .h file from custom Video filter Tool output */
#endif
/************************************************************************************************************************/
/************************************************************************************************************************/
/*chip rev constants for integrity checking */
const char chiprev = 1;
/* Last 2 digits of part number */
const char  part            = 46; /* Change this value if using a chip other than an Si2146 */
const char partRomid        = 0x11;
/* unique serial number for chip */
unsigned long partSerialNumber ;
#define BYTES_PER_LINE 8
/** globals for Top Level routine */
unsigned long newFrequency;
int DTVMode=0;
int DTVConfigurationChangedFlag=0;
/************************************************************************************************************************
  NAME: TunerFrequencyChanged
  DESCRIPTION:  This routine checks to see if the frequency has changed by monitoring the frequency expected and
                the newFrequency global variable.   If they are different then a 1 = changed is returned.
  Parameter:    Current frequency of the tuner (Hz)
  Returns:      1 if frequency is changed by a new update in the newFrequency variable, else 0.
************************************************************************************************************************/
int TunerFrequencyChanged(unsigned long *frequency)
{
	if (newFrequency != *frequency)
	{
		*frequency = newFrequency;
		return 1;
	}
	else
		return 0;
}
/************************************************************************************************************************
  NAME: ProcessAPITopLevelSequence
  DESCRIPTION:  Main entry point into application.  See the enclosed comments on how to modify for your
				application.
  Parameter: none
  Returns:  Tuner Error
  Programming Guide Reference:    Flowchart A.1 (top level flowchart)

************************************************************************************************************************/
int ProcessAPITopLevelSequence(L1_Si2146_Context *Si2146)
{

	unsigned long frequency;

	/* At this point, FW is loaded and started. */
	/* Video Filters downloaded and default property configurations and clocks/pin configurations */

	/* At this point the chip is ready to be tuned. */
	while (1)
	{
		/*  TODO: set DTVMode flag if in DTV mode */
		if (DTVMode)
		{
			if (DTVConfigurationChangedFlag)
			{
				/* Configure the DTV properties based on the data in the prop global variable */
				/* retuning is required to update the DTV Configuration properties */
				Si2146_Tune(Si2146,Si2146_TUNER_TUNE_FREQ_CMD_MODE_DTV,frequency);
				/* Clear the changed Flag */
				DTVConfigurationChangedFlag	= 0;
			}
			/* When the frequency is changed, tune to the new frequency */
			/* TODO: If a change is made to the frequency, update the newFrequency global variable. */
			if (TunerFrequencyChanged(&frequency))
			{
				Si2146_Tune(Si2146,Si2146_TUNER_TUNE_FREQ_CMD_MODE_DTV,frequency);
			}
			/* Check the DTV Status */
			/*Programming Guide Reference:    Flowchart A.9 (DTV Status flowchart) */
			/* fetch the Tuner status */
			if (Si2146_L1_TUNER_STATUS (Si2146, Si2146_DTV_STATUS_CMD_INTACK_OK))
			{
				return ERROR_Si2146_SENDING_COMMAND;
			}
			/* TODO: if needed, check the tuner status :
			Parameters available are:
				Si2146->rsp->rsp.tuner_status.tcint
				Si2146->rsp->rsp.tuner_status.rssilint
				Si2146->rsp->rsp.tuner_status.rssihint
				Si2146->rsp->rsp.tuner_status.tc
				Si2146->rsp->rsp.tuner_status.rssil
				Si2146->rsp->rsp.tuner_status.rssi
				Si2146->rsp->rsp.tuner_status.freq
				Si2146->rsp->rsp.tuner_status.mode
				*/

			/* fetch the DTV status */
			if (Si2146_L1_DTV_STATUS (Si2146, Si2146_DTV_STATUS_CMD_INTACK_OK))
			{
				return ERROR_Si2146_SENDING_COMMAND;
			}

			/* TODO: if needed, check the dtv status :
			Parameters available are:
				Si2146->rsp->rsp.dtv_status.chlint
				Si2146->rsp->rsp.dtv_status.chl
				Si2146->rsp->rsp.dtv_status.bw
				Si2146->rsp->rsp.dtv_status.modulation
			*/
		}
	}

    return 0;
}
/************************************************************************************************************************/

/************************************************************************************************************************
  NAME: Si2146_GetRF
  DESCRIPTIION: Retrieve Si2146 tune freq

  Parameter:  Pointer to Si2146 Context (I2C address)
  Returns  :  frequency (Hz) as an int
************************************************************************************************************************/
int  Si2146_GetRF             (L1_Si2146_Context *api)
{
    Si2146_L1_TUNER_STATUS (api, Si2146_TUNER_STATUS_CMD_INTACK_OK);
    return api->rsp->tuner_status.freq;
}
/************************************************************************************************************************
  NAME: Si2146_Tune
  DESCRIPTIION: Tune Si2146 in DTV mode at center frequency, wait for TUNINT and DTVINT with timeout

  Parameter:  Pointer to Si2146 Context (I2C address)
  Parameter:  Mode only DTV supported on an Si2146 use Si2146_TUNER_TUNE_FREQ_CMD_MODE_DTV constant.
  Parameter:  frequency (Hz) as a unsigned long integer
  Returns:    0 if channel found.  A nonzero value means either an error occurred or channel not locked.
  Programming Guide Reference:    Flowchart A.7 (Tune flowchart)
************************************************************************************************************************/
int  Si2146_Tune              (L1_Si2146_Context *api, unsigned char mode, unsigned long freq)
{
    int start_time  = 0;
    int return_code = 0;

    /* set a timeout of 100 ms for tune complete  */
    int timeout     = 100;

    start_time = system_time();

    if (Si2146_L1_TUNER_TUNE_FREQ (api,
                                   mode,
                                   freq) != 0)
    {
        return ERROR_Si2146_SENDING_COMMAND;
    }

    /* wait for TUNINT, timeout is 100ms */
    while ( (system_time() - start_time) < timeout )
    {
        if ((return_code = Si2146_L1_CheckStatus(api)) != 0)
            return return_code;
        if (api->status->tunint)
            break;
    }
    if (!api->status->tunint)
    {
      SiTRACE("Timeout waiting for TUNINT\n");
      return ERROR_Si2146_TUNINT_TIMEOUT;
    }

    /* wait for DTVINT, timeout is 10 ms  */
    start_time = system_time();
    timeout    =  10;
    while ( (system_time() - start_time) < timeout )
    {
        if ((return_code = Si2146_L1_CheckStatus(api)) != 0)
            return return_code;

         if (api->status->dtvint)
            break;

    }

    if (api->status->dtvint)
    {
      SiTRACE("DTV Tune Successful \n");
      return NO_Si2146_ERROR;
    }
    else
      SiTRACE("Timeout waiting for DTVINT\n");


    return ERROR_Si2146_xTVINT_TIMEOUT;

}
/************************************************************************************************************************
  NAME: Si2146_DTVTune
  DESCRIPTION: Update DTV_MODE and tune DTV mode at center frequency
  Parameter:  Pointer to Si2146 Context (I2C address)
  Parameter:  frequency (Hz)
  Parameter:  bandwidth , 6,7 or 8 MHz
  Parameter:  modulation,  e.g. use constant Si2146_DTV_MODE_PROP_MODULATION_DVBT for DVBT mode
  Parameter:  invert_spectrum,  NORMAL or INVERTED spectrum
  Returns:    I2C transaction error code, 0 if successful
  Programming Guide Reference:    Flowchart A.7 (Tune flowchart)
************************************************************************************************************************/
int  Si2146_DTVTune           (L1_Si2146_Context *Si2146, unsigned long freq, unsigned char bw, unsigned char modulation, unsigned char invert_spectrum)
{
    int return_code;
    return_code = NO_Si2146_ERROR;

    /* update DTV_MODE_PROP property */
    Si2146->prop->dtv_mode.bw = bw;
    Si2146->prop->dtv_mode.invert_spectrum = invert_spectrum;
    Si2146->prop->dtv_mode.modulation = modulation;
    if (Si2146_L1_SetProperty2(Si2146, Si2146_DTV_MODE_PROP) != NO_Si2146_ERROR)
    {
      return ERROR_Si2146_SENDING_COMMAND;
    }

    return_code = Si2146_Tune (Si2146, Si2146_TUNER_TUNE_FREQ_CMD_MODE_DTV, freq);

    return return_code;
}
/************************************************************************************************************************
  NAME: Si2146_SetupSomeDefaults
  DESCRIPTION: Example code on how to set up some needed properties.  You may or may not need to set these depending on your application.
  Parameter:  Pointer to Si2146 Context (I2C address)
  Returns:    I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si2146_SetupSomeDefaults  (L1_Si2146_Context *Si2146)
{
    int return_code;
    return_code = NO_Si2146_ERROR;

/** Setup some DTV Defaults **/
  /* Set the DTV_IEN Properties */
  /* enable CHL to drive DTVINT */
  Si2146->prop->dtv_ien.chlien                           = Si2146_DTV_IEN_PROP_CHLIEN_ENABLE;
  /* send the property setting to the part */
  if ((return_code=Si2146_L1_SetProperty2(Si2146,Si2146_DTV_IEN_PROP)) != NO_Si2146_ERROR)
    return return_code;

  /* Set the DTV_INT_SENSE Properties */
  Si2146->prop->dtv_int_sense.chlnegen                   = Si2146_DTV_INT_SENSE_PROP_CHLNEGEN_DISABLE;
  Si2146->prop->dtv_int_sense.chlposen                   = Si2146_DTV_INT_SENSE_PROP_CHLPOSEN_ENABLE;
  /* send the property setting to the part */
  if ((return_code=Si2146_L1_SetProperty2(Si2146,Si2146_DTV_INT_SENSE_PROP)) != NO_Si2146_ERROR)
    return return_code;

  /* Set the DTV_LIF_FREQ Properties */
  Si2146->prop->dtv_lif_freq.offset                      =  5000;
  /* send the property setting to the part */
  if ((return_code=Si2146_L1_SetProperty2(Si2146,Si2146_DTV_LIF_FREQ_PROP)) != NO_Si2146_ERROR)
    return return_code;

  /* Set the DTV_LIF_OUT Properties */
  Si2146->prop->dtv_lif_out.offset                       =   148;
  Si2146->prop->dtv_lif_out.amp                          =    27;
  /* send the property setting to the part */
  if ((return_code=Si2146_L1_SetProperty2(Si2146,Si2146_DTV_LIF_OUT_PROP)) != NO_Si2146_ERROR)
    return return_code;

  /* Set the DTV_MODE Properties */
  Si2146->prop->dtv_mode.bw                              = Si2146_DTV_MODE_PROP_BW_BW_8MHZ;
  Si2146->prop->dtv_mode.modulation                      = Si2146_DTV_MODE_PROP_MODULATION_DVBT;
  Si2146->prop->dtv_mode.invert_spectrum                 = Si2146_DTV_MODE_PROP_INVERT_SPECTRUM_NORMAL;
  /* send the property setting to the part */
  if ((return_code=Si2146_L1_SetProperty2(Si2146,Si2146_DTV_MODE_PROP)) != NO_Si2146_ERROR)
    return return_code;

  /* Set the DTV_RF_TOP Properties */
  Si2146->prop->dtv_rf_top.dtv_rf_top                    = Si2146_DTV_RF_TOP_PROP_DTV_RF_TOP_AUTO;
  /* send the property setting to the part */
  if ((return_code=Si2146_L1_SetProperty2(Si2146,Si2146_DTV_RF_TOP_PROP)) != NO_Si2146_ERROR)
    return return_code;

  /* Set the DTV_RSQ_RSSI Properties */
  Si2146->prop->dtv_rsq_rssi_threshold.lo                =   -80;
  Si2146->prop->dtv_rsq_rssi_threshold.hi                =     0;
  /* send the property setting to the part */
  if ((return_code=Si2146_L1_SetProperty2(Si2146,Si2146_DTV_RSQ_RSSI_THRESHOLD_PROP)) != NO_Si2146_ERROR)
    return return_code;

/** Setup Some Tuner Defaults **/
  Si2146->prop->tuner_ien.tcien= Si2146_TUNER_IEN_PROP_TCIEN_ENABLE;
  Si2146->prop->tuner_ien.rssihien= Si2146_TUNER_IEN_PROP_RSSIHIEN_DISABLE;
  Si2146->prop->tuner_ien.rssilien= Si2146_TUNER_IEN_PROP_RSSILIEN_DISABLE;
 /* send the property setting to the part */
  if ((return_code=Si2146_L1_SetProperty2(Si2146,Si2146_TUNER_IEN_PROP)) != NO_Si2146_ERROR)
    return return_code;

/** Setup Some Common Defaults **/
  Si2146->prop->crystal_trim.xo_cap = 8;
 /* send the property setting to the part */
  if ((return_code=Si2146_L1_SetProperty2(Si2146,Si2146_CRYSTAL_TRIM_PROP)) != NO_Si2146_ERROR)
    return return_code;

  return return_code;
}

/************************************************************************************************************************
  NAME: Si2146_Configure
  DESCRIPTION: Setup Si2146 video filters, GPIOs/clocks, Common Properties startup, Tuner startup, ATV startup, and DTV startup.
  Parameter:  Pointer to Si2146 Context
  Returns:    I2C transaction error code, NO_Si2146_ERROR if successful
************************************************************************************************************************/
int Si2146_Configure           (L1_Si2146_Context *api)
{
    int return_code;
    return_code = NO_Si2146_ERROR;
  /* load DTV video filter file */
  #ifdef USING_DLIF_FILTER
     if ((return_code = Si2146_LoadVideofilter(api,DLIF_VIDFILT_TABLE,DLIF_VIDFILT_LINES)) != NO_Si2146_ERROR)
       return return_code;
  #endif
    /* _specific_configure_insertion_point */

    /* Set All Properties startup configuration */
   Si2146_setupAllDefaults     (api);
   Si2146_downloadAllProperties(api);

    return return_code;
}
/************************************************************************************************************************
  NAME: Si2146_ClockOn
  Parameter:  Pointer to Si2146 Context
  Returns:    I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si2146_ClockOn           (L1_Si2146_Context *Si2146)
{
    int return_code;
    SiTRACE("Si2146_CLOCK_ON: Turning clock ON\n");

    if ((return_code = Si2146_L1_CONFIG_PINS (Si2146,
                               Si2146_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE,
                               Si2146_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ,
                               Si2146_CONFIG_PINS_CMD_GPIO2_MODE_NO_CHANGE,
                               Si2146_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ,
                               Si2146_CONFIG_PINS_CMD_GPIO3_MODE_NO_CHANGE,
                               Si2146_CONFIG_PINS_CMD_GPIO3_READ_DO_NOT_READ,
                               Si2146_CONFIG_PINS_CMD_BCLK1_MODE_XOUT,
                               Si2146_CONFIG_PINS_CMD_BCLK1_READ_DO_NOT_READ,
                               Si2146_CONFIG_PINS_CMD_XOUT_MODE_DISABLE)) != NO_Si2146_ERROR)
    return return_code;

    return 0;
}
/************************************************************************************************************************
  NAME: Si2146_ClockOff
  Parameter:  Pointer to Si2146 Context (I2C address)
  Returns:    I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si2146_ClockOff         (L1_Si2146_Context *Si2146)
{
    int return_code;
    SiTRACE("Si2146_CLOCK_OFF: Turning clock OFF\n");

    if ((return_code = Si2146_L1_CONFIG_PINS (Si2146,
                               Si2146_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE,
                               Si2146_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ,
                               Si2146_CONFIG_PINS_CMD_GPIO2_MODE_NO_CHANGE,
                               Si2146_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ,
                               Si2146_CONFIG_PINS_CMD_GPIO3_MODE_NO_CHANGE,
                               Si2146_CONFIG_PINS_CMD_GPIO3_READ_DO_NOT_READ,
                               Si2146_CONFIG_PINS_CMD_BCLK1_MODE_DISABLE,
                               Si2146_CONFIG_PINS_CMD_BCLK1_READ_DO_NOT_READ,
                               Si2146_CONFIG_PINS_CMD_XOUT_MODE_DISABLE)) != NO_Si2146_ERROR)
    return return_code;

    return 0;
}
/************************************************************************************************************************
  NAME: Si2146_PowerUpWithPatch
  DESCRIPTION: Send Si2146 API PowerUp Command with PowerUp to bootloader,
  Check the Chip rev and part, and ROMID are compared to expected values.
  Load the Firmware Patch then Start the Firmware.
  Programming Guide Reference:    Flowchart A.2 (POWER_UP with patch flowchart)

  Parameter:  pointer to Si2146 Context
  Returns:    Si2146/I2C transaction error code, NO_Si2146_ERROR if successful
************************************************************************************************************************/
int Si2146_PowerUpWithPatch    (L1_Si2146_Context *api)
{
    int return_code;
    return_code = NO_Si2146_ERROR;

    /* always wait for CTS prior to POWER_UP command */
    if ((return_code = Si2146_pollForCTS  (api)) != NO_Si2146_ERROR) {
        SiTRACE ("Si2146_pollForCTS error 0x%02x\n", return_code);
        return return_code;
    }

    if ((return_code = Si2146_L1_POWER_UP (api,
                          Si2146_POWER_UP_CMD_SUBCODE_CODE,
                          Si2146_POWER_UP_CMD_RESERVED1_RESERVED,
                          Si2146_POWER_UP_CMD_RESERVED2_RESERVED,
                          Si2146_POWER_UP_CMD_RESERVED3_RESERVED,
                          Si2146_POWER_UP_CMD_CLOCK_MODE_XTAL,
                          Si2146_POWER_UP_CMD_CLOCK_FREQ_CLK_24MHZ,
                          Si2146_POWER_UP_CMD_ADDR_MODE_CURRENT,
                          Si2146_POWER_UP_CMD_FUNC_BOOTLOADER,        /* start in bootloader mode */
                          Si2146_POWER_UP_CMD_CTSIEN_DISABLE,
                            Si2146_POWER_UP_CMD_WAKE_UP_WAKE_UP)) != NO_Si2146_ERROR)
    {
      SiTRACE ("Si2146_L1_POWER_UP error 0x%02x: %s\n", return_code, Si2146_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }

    /* Get the Part Info from the chip.   This command is only valid in Bootloader mode */
    if ((return_code = Si2146_L1_PART_INFO(api)) != NO_Si2146_ERROR) {
        SiTRACE ("Si2146_L1_PART_INFO error 0x%02x: %s\n", return_code, Si2146_L1_API_ERROR_TEXT(return_code) );
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
        return_code = ERROR_Si2146_INCOMPATIBLE_PART;
    }
    /* Part Number is represented as the last 2 digits */
    if (api->rsp->part_info.part != api->part) {
        SiTRACE ("INCOMPATIBLE PART error part   %d (expected %d)\n", api->rsp->part_info.part, api->part);
        return_code = ERROR_Si2146_INCOMPATIBLE_PART;
    }
    /* Part Major Version in ASCII */
    if (api->rsp->part_info.pmajor != api->partMajorVersion) {
        SiTRACE ("INCOMPATIBLE PART error pmajor %d (expected %d)\n", api->rsp->part_info.pmajor, api->partMajorVersion);
        return_code = ERROR_Si2146_INCOMPATIBLE_PART;
    }
    /* Part Minor Version in ASCII */
    if (api->rsp->part_info.pminor != api->partMinorVersion) {
        SiTRACE ("INCOMPATIBLE PART error pminor %d (expected %d)\n", api->rsp->part_info.pminor, api->partMinorVersion);
        return_code = ERROR_Si2146_INCOMPATIBLE_PART;
    }
    /* ROMID in byte representation */
    if (api->rsp->part_info.romid != api->partRomid) {
        SiTRACE ("INCOMPATIBLE PART error romid %3d (expected %2d)\n", api->rsp->part_info.romid, api->partRomid);
        return_code = ERROR_Si2146_INCOMPATIBLE_PART;
    }
    if (return_code != NO_Si2146_ERROR) return return_code;
#endif /* PART_INTEGRITY_CHECKS */
      /* Load the if needed */
#ifdef LOAD_PATCH_11b3
    if (api->rsp->part_info.romid == 0x11) {
        /* Load the Firmware */
       if ((return_code = Si2146_LoadFirmware(api, Si2146_FW_1_1b3, FIRMWARE_LINES_1_1b3)) != NO_Si2146_ERROR) {
         SiTRACE ("Si2146_LoadFirmware error 0x%02x: %s\n", return_code, Si2146_L1_API_ERROR_TEXT(return_code) );
           return return_code;
       }
    }
#endif /*LOAD_PATCH_11b3 */
    /*Start the Firmware */
    if ((return_code = Si2146_StartFirmware(api)) != NO_Si2146_ERROR) { /* Start firmware */
        SiTRACE ("Si2146_StartFirmware error 0x%02x: %s\n", return_code, Si2146_L1_API_ERROR_TEXT(return_code) );
       return return_code;
    }

    return NO_Si2146_ERROR;
}
/************************************************************************************************************************
  NAME: Si2146_LoadFirmware
  DESCRIPTON: Load firmware from FIRMWARE_TABLE array in Si2146_Firmware_x_y_build_z.h file into Si2146
              Requires Si2146 to be in bootloader mode after PowerUp
  Programming Guide Reference:    Flowchart A.3 (Download FW PATCH flowchart)

  Parameter:  Si2146 Context (I2C address)
  Parameter:  pointer to firmware table array
  Parameter:  number of lines in firmware table array (size in bytes / BYTES_PER_LINE)
  Returns:    Si2146/I2C transaction error code, NO_Si2146_ERROR if successful
************************************************************************************************************************/
int Si2146_LoadFirmware        (L1_Si2146_Context *api, unsigned char fw_table[], int nbLines)
{
    int return_code;
    int line;
    return_code = NO_Si2146_ERROR;

    SiTRACE ("Si2146_LoadFirmware starting...\n");
    SiTRACE ("Si2146_LoadFirmware nbLines %d\n", nbLines);

    /* for each line in fw_table */
    for (line = 0; line < nbLines; line++)
    {
        /* send Si2146_BYTES_PER_LINE fw bytes to Si2146 */
        if ((return_code = Si2146_L1_API_Patch(api, Si2146_BYTES_PER_LINE, fw_table + Si2146_BYTES_PER_LINE*line)) != NO_Si2146_ERROR)
        {
          SiTRACE("Si2146_LoadFirmware error 0x%02x patching line %d: %s\n", return_code, line, Si2146_L1_API_ERROR_TEXT(return_code) );
          if (line == 0) {
          SiTRACE("The firmware is incompatible with the part!\n");
          }
          return ERROR_Si2146_LOADING_FIRMWARE;
        }
        if (line==3) SiTraceConfiguration("traces -output none");
    }
    SiTraceConfiguration("traces -output file");
    SiTRACE ("Si2146_LoadFirmware complete...\n");
    return NO_Si2146_ERROR;
}
/************************************************************************************************************************
  NAME: Si2146_StartFirmware
  DESCRIPTION: Start Si2146 firmware (put the Si2146 into run mode)
  Parameter:   Si2146 Context (I2C address)
  Parameter (passed by Reference):   ExitBootloadeer Response Status byte : tunint, atvint, dtvint, err, cts
  Returns:     I2C transaction error code, NO_Si2146_ERROR if successful
************************************************************************************************************************/
int Si2146_StartFirmware       (L1_Si2146_Context *api)
{

    if (Si2146_L1_EXIT_BOOTLOADER(api, Si2146_EXIT_BOOTLOADER_CMD_FUNC_TUNER, Si2146_EXIT_BOOTLOADER_CMD_CTSIEN_OFF) != NO_Si2146_ERROR)
  {
        return ERROR_Si2146_STARTING_FIRMWARE;
    }

    return NO_Si2146_ERROR;
}
/************************************************************************************************************************
  NAME: Si2146_LoadVideofilter
  DESCRIPTION:        Load video filters from vidfiltTable in Si2146_write_xTV_video_coeffs.h file into Si2146
  Programming Guide Reference:    Flowchart A.4 (Download Video Filters flowchart)

  Parameter:  Si2146 Context (I2C address)
  Parameter:  pointer to video filter table array
  Parameter:  number of lines in video filter table array (size in bytes / BYTES_PER_LINE)
  Returns:    Si2146/I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si2146_LoadVideofilter    (L1_Si2146_Context *Si2146,unsigned char* vidfiltTable,int lines)
{
    int line;

  /* for each 8 bytes in VIDFILT_TABLE */
    for (line = 0; line < lines; line++)
  {
    /* send that 8 byte I2C command to Si2146 */
        if (Si2146_L1_API_Patch(Si2146, BYTES_PER_LINE, vidfiltTable+BYTES_PER_LINE*line) != NO_Si2146_ERROR)
    {
             return ERROR_Si2146_SENDING_COMMAND;
        }
    }
    return 0;
}
/************************************************************************************************************************
  NAME: Si2146_Init
  DESCRIPTION:Reset and Initialize Si2146
  Parameter:  Si2146 Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2146_ERROR if successful
************************************************************************************************************************/
int Si2146_Init                (L1_Si2146_Context *api)
{
    int return_code;
    SiTRACE("Si2146_Init starting...\n");

    if ((return_code = Si2146_PowerUpWithPatch(api)) != NO_Si2146_ERROR) {   /* PowerUp into bootloader */
        SiTRACE ("Si2146_PowerUpWithPatch error 0x%02x: %s\n", return_code, Si2146_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }
    /* At this point, FW is loaded and started.  */
    Si2146_Configure(api);
    SiTRACE("Si2146_Init complete...\n");
    return NO_Si2146_ERROR;
}
/************************************************************************************************************************
  NAME: Si2146_AGC_Override
  Parameter:  Pointer to Si2146 Context (I2C address)
  Parameter:  Mode 0=Normal, 1= Max, 2=TOP
  Returns:    I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si2146_AGC_Override    (L1_Si2146_Context *Si2146, unsigned char mode )
{
    int return_code;
    SiTRACE("Si2146_AGC_Override: mode = %d\n",mode);
    switch (mode)
    {
        case  Si2146_FORCE_NORMAL_AGC:
            if ((return_code = Si2146_L1_AGC_OVERRIDE (Si2146, Si2146_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_DISABLE,Si2146_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_DISABLE)) != NO_Si2146_ERROR)
                return return_code;
            break;
        case  Si2146_FORCE_MAX_AGC:
            if ((return_code = Si2146_L1_AGC_OVERRIDE (Si2146, Si2146_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_ENABLE,Si2146_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_DISABLE)) != NO_Si2146_ERROR)
                return return_code;
            break;
        case  Si2146_FORCE_TOP_AGC:
            if ((return_code = Si2146_L1_AGC_OVERRIDE (Si2146, Si2146_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_DISABLE,Si2146_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_ENABLE)) != NO_Si2146_ERROR)
                return return_code;
            break;

        default:
            return ERROR_Si2146_PARAMETER_OUT_OF_RANGE;

    }

    return NO_Si2146_ERROR;
}
