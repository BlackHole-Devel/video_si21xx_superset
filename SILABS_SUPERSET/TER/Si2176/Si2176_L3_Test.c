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
                  Silicon Laboratories Broadcast Si2176 Layer 3 API
   L3 sample application
   FILE: Si2176_L3_Test.c
   Supported IC : Si2176
   Compiled for ROM 13 firmware 3_2_build_6
   Revision: 0.1
   Tag:  TAGNAME
   Date: December 22 2011
  Revision Log:
  Rev 2.0  Adjusted TUNINT time to 70 ms in Si2176_Tune
****************************************************************************************/
#include "Si2176_L3_Test.h"

/* define TUNER_ONLY if using a Si2176 tuner without demod                                                    */
/* (It should be defined at project/makefile level to use 100% identical code for tuner-only and tuner+demod)   */
/* #define TUNER_ONLY */

#ifdef    TUNER_ONLY

/* define SILABS_DEMOD_EVB if used on a tuner_only application on a demod EVB (opens i2c_passthru in main)      */
/* (It should be defined at project/makefile level to use 100% identical code for tuner-only EVB and demod EVB) */
/* #define SILABS_DEMOD_EVB*/

/* define Si2176_COMMAND_LINE_APPLICATION if using this code in console mode                                                     */
/* (Si2176_COMMAND_LINE_APPLICATION should be defined at project/makefile level to use 100% identical code for console and TV )  */
/* #define Si2176_COMMAND_LINE_APPLICATION */

/* define FRONT_END_COUNT 1 for a single tuner application                                                                         */
/* (FRONT_END_COUNT should be defined at project/makefile level to use 100% identical code for single-frontend and multi-frontend) */
#define FRONT_END_COUNT 1

int  commandCount  = 0;
int  fe;

L1_Si2176_Context          FrontEnd_Table   [FRONT_END_COUNT];
L1_Si2176_Context         *Si2176;
L1_Si2176_Context         *front_end;

/* Also init a simple i2c context to allow i2c communication checking */
L0_Context* i2c;
L0_Context  i2c_context;
CONNECTION_TYPE mode;

#ifdef    SILABS_DEMOD_EVB
/* To be able to test this on SiLabs demod EVB, it must be possible to close the i2c passthru in the demod */
typedef struct demod_Context {
  L0_Context    *i2c;
  L0_Context     i2cObj;
} demod_Context;

/* i2c_passthru                   */
 #define    i2c_passthru_ADDRESS               1
 #define    i2c_passthru_OFFSET                0
 #define    i2c_passthru_NBBIT                 1
 #define    i2c_passthru_ALONE                 1
 #define    i2c_passthru_SIGNED                0
  #define           i2c_passthru_disabled                      0
  #define           i2c_passthru_enabled                       1

  demod_Context  demodObj;
  demod_Context *demod;
#endif /* SILABS_DEMOD_EVB */

#ifdef    SiTRACES
/************************************************************************************************************************
  Si2176_UserInput_traces function
  Use:        send a traces configuration message to the L0 SiTRACES functions
              the Si2176_UserInput_traces function asks the user which type of configuration he wishes.
              Then, memorize the message and calls SiTraceConfiguration.
  Returns:    void
  Porting:    Not compiled if SiTRACES is not defined in Silabs_L0_API.h
************************************************************************************************************************/
void Si2176_UserInput_traces               (void)
{
    char *configuration;
    char *msg;
    configuration = (char*)malloc(sizeof(char)*100);
    msg           = (char*)malloc(sizeof(char)*100);
    printf("Enter the traces configuration string (-<param> ,<value>): ");
    gets(configuration);
    sprintf(msg, "traces %s", configuration);
    printf("%s",SiTraceConfiguration (msg));
}
#endif /* SiTRACES */
/************************************************************************************************************************
  Si_I2C_UserInput_read function
  Use:        i2c read test function
              Used to retrieve user input before an i2c read
  Behavior:   split user input on spaces to find the address of the chip, the index of the first byte to read
              and the number of bytes to read, then perform the read and display the resulting bytes.
  Porting:    This is for i2c verification only.
  **********************************************************************************************************************/
void Si_I2C_UserInput_read                 (L0_Context* i2c)
{
    int i;
    int readBytes;
    int loop;
    int nbArgs;
    int indexSize;
    unsigned int address;
    unsigned int uintval;
    unsigned int hexval;
    char *input;
    char *array[50];
    int  bytes[50];
    unsigned int iI2CIndex;
    int iNbBytes;
    unsigned char *pbtDataBuffer;

    input = (char*) malloc(sizeof(char)*1000);
    printf("i2c read ");
    gets(input);

    /* strtok splitting input and storing all items, returning first item */
    array[0] = strtok(input," ");
    if(array[0]==NULL) {return;}
    /* retrieving all remaining items */
    for(loop=1;loop<50;loop++) {
        array[loop] = strtok(NULL," ");
        if(array[loop]==NULL) break;
    }
    nbArgs = loop;
    /* scanning arguments, allowing decimal or hexadecimal input */
    for(loop=0;loop<nbArgs;loop++) {
        hexval=0;
        sscanf(array[loop],"%d", &uintval);
        if (!uintval) sscanf(array[loop],"%x", &hexval);
        bytes[loop] = hexval + uintval;
    }

    address   = bytes[0];
    indexSize = nbArgs - 2;
    if (indexSize <0) return;
    iI2CIndex = 0;
    for (i=1; i<= indexSize; i++) {
        iI2CIndex = iI2CIndex + bytes[i];
    }
    iNbBytes  = bytes[loop-1];
    pbtDataBuffer = (unsigned char*)malloc(sizeof(unsigned char)*iNbBytes);
    L0_SetAddress   (i2c, address, indexSize);
    readBytes = L0_ReadRawBytes (i2c, iI2CIndex, iNbBytes, pbtDataBuffer);
    for (i=0; i<readBytes; i++) { printf ("0x%02x ", pbtDataBuffer[i]); }
    if (readBytes) printf("\n");
}
/************************************************************************************************************************
  Si_I2C_UserInput_write function
  Use:        i2c write test function
              Used to retrieve user input before an i2c write
  Behavior:   split user input on spaces to find the address of the chip and the bytes to write,
              then perform the write.
  Porting:    This is for i2c verification only.
  **********************************************************************************************************************/
void Si_I2C_UserInput_write                (L0_Context* i2c)
{
    int i;
    int writeBytes;
    int loop;
    int nbArgs;
    int indexSize;
    unsigned int address;
    unsigned int uintval;
    unsigned int hexval;
    char *input;
    char *array[50];
    int  bytes[50];
    unsigned int iI2CIndex;
    int iNbBytes;
    unsigned char *pbtDataBuffer;

    input = (char*) malloc(sizeof(char)*1000);
    printf("i2c write ");
    gets(input);

    /* strtok splitting input and storing all items, returning first item */
    array[0] = strtok(input," ");
    if(array[0]==NULL) {return;}
    /* retrieving all remaining items */
    for(loop=1;loop<50;loop++) {
        array[loop] = strtok(NULL," ");
        if(array[loop]==NULL) break;
    }
    nbArgs = loop;
    /* scanning arguments, allowing decimal or hexadecimal input */
    for(loop=0;loop<nbArgs;loop++) {
        hexval=0;
        sscanf(array[loop],"%d", &uintval);
        if (!uintval) sscanf(array[loop],"%x", &hexval);
        bytes[loop] = hexval + uintval;
    }

    address   = bytes[0];
    indexSize = 0;
    if (indexSize <0) return;
    iI2CIndex = 0;
    iNbBytes  = nbArgs-1;
    pbtDataBuffer = (unsigned char*)malloc(sizeof(unsigned char)*iNbBytes);
    for (i=0; i<iNbBytes; i++) { pbtDataBuffer[i] = bytes[i+1]; }
    L0_SetAddress   (i2c, address, indexSize);
    writeBytes = L0_WriteRawBytes (i2c, iI2CIndex, iNbBytes, pbtDataBuffer);
    if (writeBytes) {printf("%d bytes written\n", writeBytes);} else {printf("Write error!\n");}
}
/************************************************************************************************************************
  Si2176_UserInputString function
  Use:        retrieve a string entered by the user
  Parameters: text, a pointer to the string buffer
              max_size, the size allocated by the calling function for the text buffer
  Behavior:   Retrieves the string using fgets to avoid overflows. As fgets keeps the 'carriage return' except
                if the string is longer than max_size, replace it (if present) by the terminating character
  Returns:    the length of the string
************************************************************************************************************************/
int  Si2176_UserInputString                (char* text, int max_size) {
  char *newline;
  if ( fgets(text, max_size, stdin) != NULL ) {
    newline = strchr(text, '\n');             /* search for newline character        */
    if ( newline != NULL ) { *newline = '\0'; /* overwrite trailing newline (if any) */ }
  }
  return (int)(strlen(text));
}
/************************************************************************************************************************
  Si2176_trace function
  Use:        trace toggle function
              Used to toggle tracing for all register accesses, at byte level
  Behavior:   Calls the tracking functions for read and write for both demod and tuner
************************************************************************************************************************/
void Si2176_trace                          (L1_Si2176_Context *api) {
    int trackFlag;
    trackFlag = !api->i2c->trackRead;
    L0_TrackWrite(i2c     , trackFlag);
    L0_TrackRead (i2c     , trackFlag);
    L0_TrackWrite(api->i2c, trackFlag);
    L0_TrackRead (api->i2c, trackFlag);
}
#endif /* TUNER_ONLY */
/************************************************************************************************************************
  NAME: Si2176_configure_i2c_communication
  DESCRIPTION:        Setup USB communication with Si2176 EVB
  Parameter:  Pointer to Si2176 Context (I2C address)
  Returns:    nothing
************************************************************************************************************************/
void Si2176_configure_i2c_communication    (L1_Si2176_Context *api)
{
#ifdef    USB_Capability
    double        retdval;
    char rettxtBuffer[256];
    char *rettxt;
    rettxt = rettxtBuffer;
    L0_Connect (api->i2c, USB);
    L0_Cypress_Configure("-i2c"                 ,"400khz", 0   , &retdval, &rettxt);  /* at 400kHz SCL rate     */
 #ifdef    SILABS_DEMOD_EVB
    L0_Connect (demod->i2c, USB);
 #endif /* SILABS_DEMOD_EVB */
#endif /* USB_Capability */
#ifdef    SILABS_DEMOD_EVB
    L1_WRITE(demod, i2c_passthru, i2c_passthru_enabled);
#endif /* SILABS_DEMOD_EVB */
}
/************************************************************************************************************************
  NAME: Si2176_TunerFrequencyChanged
  DESCRIPTION:  This routine checks to see if the frequency has changed by monitoring the frequency expected and
                the newFrequency global variable.   If they are different then a 1 = changed is returned.
  Parameter:     Si2176 Context (I2C address), Current frequency of the tuner (Hz)
  Returns:      1 if frequency is changed by a new update in the newFrequency variable, else 0.
************************************************************************************************************************/
int Si2176_TunerFrequencyChanged                  (L1_Si2176_Context *api,unsigned long *frequency)
{
	if (api->newFrequency != *frequency)
	{
		*frequency = api->newFrequency;
		return 1;
	}
	else
		return 0;
}
/************************************************************************************
  NAME: Si2176_ProcessAPITopLevelSequence
  DESCRIPTION:  Main entry point into application.  See the enclosed comments on how to modify for your
				application.
  Parameter:  Si2176 Context (I2C address)
  Returns:  Tuner Error
  Programming Guide Reference:    Flowchart A.1 (top level flowchart)

************************************************************************************************************************/
int Si2176_ProcessAPITopLevelSequence             (L1_Si2176_Context *Si2176)
{

	unsigned long frequency;
	/* At this point the chip is ready to be tuned. */
	while (1)
	{
		/*  TODO: set ATVMode flag if in ATV mode */
		if (Si2176->ATVMode)
		{
			/* if the default configuration is changed, then write the new property values to the chip.              */
			/* TODO: If a change is made to any ATV configurations, set this flag (ATVConfigurationChangedFlag =1),  */
			/*       The flag will be cleared after the configuration changes are completed */
			if (Si2176->ATVConfigurationChangedFlag)
			{
				/* Configure the ATV properties based on the data in the prop global variable */
				//Si2176_ATVConfig (&Si2176_L1);
				/* Note: the Common properties and the tuner properties are not likely to change from the
				   startup defaults.   If you do change these you will need to execute CommonConfig(&Si2176_L1)
				   and / or TunerConfig(&Si2176_L1). */

				/* retuning is required to update the ATV Configuration properties */
				Si2176_Tune(Si2176,Si2176_TUNER_TUNE_FREQ_CMD_MODE_ATV,frequency);
				/* Clear the changed Flag */
				Si2176->ATVConfigurationChangedFlag	= 0;

			}
			/* When the frequency is changed, tune to the new frequency */
			/* TODO: If a change is made to the frequency, update the newFrequency global variable. */
			if (Si2176_TunerFrequencyChanged(Si2176,&frequency))
			{
				Si2176_Tune(Si2176,Si2176_TUNER_TUNE_FREQ_CMD_MODE_ATV,frequency);
			}
			/* Now Check the ATV Status */
			/*Programming Guide Reference:    Flowchart A.8 (ATV Status flowchart) */
			/* fetch the Tuner status */
			if (Si2176_L1_TUNER_STATUS (Si2176, Si2176_DTV_STATUS_CMD_INTACK_OK))
			{
				return ERROR_Si2176_SENDING_COMMAND;
			}

			/* TODO: if needed, check the tuner status :
			Parameters available are:
				rsp.tuner_status.tcint
				rsp.tuner_status.rssilint
				rsp.tuner_status.rssihint
				rsp.tuner_status.tc
				rsp.tuner_status.rssil
				rsp.tuner_status.rssi
				rsp.tuner_status.freq
				rsp.tuner_status.mode
				*/

			/* fetch the ATV Status */
           	if (Si2176_L1_ATV_STATUS (Si2176,Si2176_ATV_STATUS_CMD_INTACK_OK))
			{
				return ERROR_Si2176_SENDING_COMMAND;
			}
			/* TODO: if needed, check the atv status :
			Parameters of most interest are:
				rsp.atv_status.pcl			-- picture carrier lock
				rsp.atv_status.chl			-- valid channel flag
				rsp.atv_status.dl			-- demod lock
				rsp.atv_status.rssil		-- rssi > threshold
				rsp.atv_status.snrl			-- SNR not low
				rsp.atv_status.afc_freq		-- afc_frequency (kHz), offset from tuned frequency
				rsp.atv_status.video_snr	-- video SNR (1/2dB)
			*/
		}
		/*  TODO: set DTVMode flag if in DTV mode */
		if (Si2176->DTVMode)
		{
			if (Si2176->DTVConfigurationChangedFlag)
			{
				/* Configure the DTV properties based on the data in the prop global variable */
				//Si2176_DTVConfig (&Si2176_L1);
				/* retuning is required to update the DTV Configuration properties */
				Si2176_Tune(Si2176,Si2176_TUNER_TUNE_FREQ_CMD_MODE_DTV,frequency);
				/* Clear the changed Flag */
				Si2176->DTVConfigurationChangedFlag	= 0;
			}
			/* When the frequency is changed, tune to the new frequency */
			/* TODO: If a change is made to the frequency, update the newFrequency global variable. */
			if (Si2176_TunerFrequencyChanged(Si2176,&frequency))
			{
				Si2176_Tune(Si2176,Si2176_TUNER_TUNE_FREQ_CMD_MODE_DTV,frequency);
			}
			/* Check the DTV Status */
			/*Programming Guide Reference:    Flowchart A.9 (DTV Status flowchart) */
			/* fetch the Tuner status */
			if (Si2176_L1_TUNER_STATUS (Si2176, Si2176_DTV_STATUS_CMD_INTACK_OK))
			{
				return ERROR_Si2176_SENDING_COMMAND;
			}
			/* TODO: if needed, check the tuner status :
			Parameters available are:
				rsp.tuner_status.tcint
				rsp.tuner_status.rssilint
				rsp.tuner_status.rssihint
				rsp.tuner_status.tc
				rsp.tuner_status.rssil
				rsp.tuner_status.rssi
				rsp.tuner_status.freq
				rsp.tuner_status.mode
				*/

			/* fetch the DTV status */
			if (Si2176_L1_DTV_STATUS (Si2176,Si2176_DTV_STATUS_CMD_INTACK_OK))
			{
				return ERROR_Si2176_SENDING_COMMAND;
			}

			/* TODO: if needed, check the dtv status :
			Parameters available are:
				rsp.dtv_status.chlint
				rsp.dtv_status.chl
				rsp.dtv_status.bw
				rsp.dtv_status.modulation
			*/
		}
	}

    return 0;
}

#ifdef Si2176_COMMAND_LINE_APPLICATION
/************************************************************************************************************************
  NAME: Si2176_DisplayStatusByte
  DESCRIPTION:Read Si2176 STATUS byte and display status bits
  Parameter:  Si2176 Context (I2C address)
  Returns:    Si2176/I2C transaction error code
************************************************************************************************************************/
int  Si2176_DisplayStatusByte              (L1_Si2176_Context *api)
{
    int error_code;

    error_code = Si2176_L1_CheckStatus(api);
    if (error_code)
    {
        SiTRACE("Error %d reading STATUS byte\n",error_code);
        printf ("Error %d reading STATUS byte\n",error_code);
        return error_code;
    }

    printf("STATUS: CTS=%d, ERR=%d, DTVINT=%d, ATVINT=%d, TUNINT=%d\n", api->status->cts, api->status->err, api->status->dtvint, api->status->atvint, api->status->tunint);

    return 0;
}
/************************************************************************************************************************
  NAME : Si2176_GetRevision
  DESCRIPTION:  Execute Si2176 GET_REV function and display response fields
  Parameter:  Si2176 Context (I2C address)
  Returns:    I2C transaction error code
************************************************************************************************************************/
int  Si2176_GetRevision                    (L1_Si2176_Context *api)
{
    char message[1000];

    if (Si2176_L1_GET_REV(api) != NO_Si2176_ERROR)          /* execute GET_REV and always read response */
    {
        printf("Error reading GET_REV\n");
        return ERROR_Si2176_SENDING_COMMAND;
    }
    Si2176_L1_GetCommandResponseString(api, Si2176_GET_REV_CMD_CODE,"\n", message);
    printf("%s\n",message);

    return 0;
}
/************************************************************************************************************************
  NAME: Si2176_ATVStatus
  DESCRIPTION:Reports tuner status from ATV_STATUS response
  Parameter:  Pointer to Si2176 Context (I2C address)
  Returns:    I2C transaction error code
************************************************************************************************************************/
int Si2176_ATVStatus (L1_Si2176_Context *Si2176)
{
    char *message=(char *) malloc(BUF_SIZE);

    if (Si2176_L1_ATV_STATUS(Si2176, Si2176_ATV_STATUS_CMD_INTACK_CLEAR) != NO_Si2176_ERROR) { /* execute ATV_STATUS and always read response */
        printf("Error reading ATV_STATUS\n");
        return ERROR_Si2176_SENDING_COMMAND;
    }
   Si2176_L1_GetCommandResponseString(Si2176, Si2176_ATV_STATUS_CMD_CODE, "\n", message);
   printf("%s\n",message);

    return 0;
}
/************************************************************************************************************************
  Si2176_DTVStatus function
  Use:        Reports tuner status from DTV_STATUS response
  Parameter:  Pointer to Si2176 Context (I2C address)
  Returns:    I2C transaction error code
************************************************************************************************************************/
int Si2176_DTVStatus (L1_Si2176_Context *Si2176)
{
    char *message=(char *) malloc(BUF_SIZE);

    if (Si2176_L1_DTV_STATUS(Si2176, Si2176_DTV_STATUS_CMD_INTACK_CLEAR) != 0) { /* execute DTV_STATUS and always read response */
        printf("Error reading DTV_STATUS\n");
        return ERROR_Si2176_SENDING_COMMAND;
    }
  Si2176_L1_GetCommandResponseString(Si2176, Si2176_DTV_STATUS_CMD_CODE,"\n", message);                  /* display results */
  printf("%s\n",message);

    return 0;
}
/************************************************************************************************************************
  NAME: Si2176_TunerStatus
  DESCRIPTION:        Reports tuner status from TUNER_STATUS response
  Parameter:  Pointer to Si2176 Context (I2C address)
  Returns:    I2C transaction error code
************************************************************************************************************************/
int Si2176_TunerStatus (L1_Si2176_Context *Si2176)
{
    char *message=(char *) malloc(BUF_SIZE);

    if (Si2176_L1_TUNER_STATUS(Si2176, Si2176_TUNER_STATUS_CMD_INTACK_CLEAR) != NO_Si2176_ERROR) { /* execute TUNER_STATUS and always read response */
        printf("Error reading TUNER_STATUS\n");
        return ERROR_Si2176_SENDING_COMMAND;
    }
  Si2176_L1_GetCommandResponseString(Si2176, Si2176_TUNER_STATUS_CMD_CODE, "\n", message);
  printf("%s\n",message);/* display results */

    return 0;
}
/************************************************************************************************************************
  NAME: Si2176_GetUserFrequency
  DESCRIPTION: Function to process user input frequency and return an error if invalid.
  Parameter: unsigned long *fIn - returns the user entered frequency in Hz.
  Returns : 1 if an error occurred, 0 otherwise.
************************************************************************************************************************/
int Si2176_GetUserFrequency(unsigned long *fIn)
{
  char entry[MAX_LENGTH];
  fgets(entry,MAX_LENGTH,stdin);
  if (strlen(entry) > 1)
  {
    if (sscanf(entry,"%ld",fIn) < 1)
          { printf ("Error invalid frequency\nPlease press <Enter> to continue\n"); getc(stdin); return 1;}
  }
  else
  { printf ("Error invalid frequency \nPlease press <Enter> to continue\n"); getc(stdin); return 1;}
  SiTRACE("fIn %ld\n",*fIn);
  return 0;
}

/************************************************************************************************************************
  Si2176_help function
  Use:        console application help function
              Used to explain how to init the EVB, tune and scan
************************************************************************************************************************/
int  Si2176_help                           (void) {
    printf("\n\
----------------------------------------------------------------------------\n\
       This is a demonstration application used to illustrate how to use    \n\
            the Si2176 API delivered by Silicon Laboratories                \n\
                                                                            \n\
       It demonstrates a dual front-end case                                \n\
                                                                            \n\
       Most platforms will only have one front-end, therefore               \n\
       the second one will not work correctly                               \n\
                                                                            \n\
                                                                            \n\
    Enter 'help' to display the help.                                       \n\
    Enter 'm'    to display the menu.                                       \n\
                                                                            \n\
----------------------------------------------------------------------------\n");
  return 0;
}
/************************************************************************************************************************
  NAME: Si2176_menu
  DESCRIPTION: Si2176 user menu function
              Used to display the various possibilities offered to the user
  Behavior:   Prints the menu in the console
************************************************************************************************************************/
void Si2176_menu                           (unsigned char full) {
  if (full) {
  printf("\
-----------------------------------------------------------------------\n\
   Console mode Application Menu:\n\
-----------------------------------------------------------------------\n\
 ------  i2c ---------\n\
read           : read bytes from i2c       \n\
write          : write bytes to i2c        \n\
USB            : connect i2c in USB  mode  \n\
CUST           : connect i2c in CUST mode  \n\
trace          : toggle L0 traces\n\
traces         : manage L0 traces (use 'traces' then 'help' for details)\n\
------  Si2176 ------\n\
");
}
  printf("\
InitAndConfig  : Initialize and Configure the Si2176\n\
Status         : Read Si2176 STATUS\n\
GetRevision    : Display revision info\n");
#ifdef USING_ATV_FILTER
printf ("LoadATVVidfilt : Load the ATV videofilter\n");
#endif
#ifdef USING_DLIF_FILTER
printf("LoadDLIFVidfilt : Load the DLIF videofilter\n");
#endif
printf("ATVConfig      : Configure the Properties for ATV mode\n\
DTVConfig      : Configure the Properties for DTV mode\n\
TunerConfig    : Configure the Properties for the Tuner\n\
CommonConfig   : Configure the Common Properties \n\
ATVTune        : Tune an ATV channel\n\
DTVTune        : Tune a DTV channel\n\
TunerStatus    : Display Tuner Status (TC, RSSI, ...)\n\
ATVStatus      : Display ATV Status   (CHL, VSNR, ...)\n\
DTVStatus      : Display DTV Status   (CHL, ...)\n\
ChannelScanM   : Do a channel scan for ATV system M\n\
ChannelScanPal : Do a channel scan for ATV system PAL\n\
Standby        : Put the Part in Standby Mode\n\
Powerdown      : Powerdown the Part\n\
ClockOn        : Turn on BCLK1\n\
ClockOff       : Turn off BCLK1\n\
XOUTOn         : Turn on XOUT\n\
XOUTOff        : Turn off XOUT\n");
  if (full) {
  printf(" ------ console -----\n\
help           : display application help\n\
cls            : clear screen\n\
m              : display this menu\n\
exit           : exit application\n\
");
  }
  printf("----------------------------------------------------------------------------\n");
}
/************************************************************************************************************************
  NAME: Si2176_demoLoop
  DESCRIPTION: Demo application loop function
              Used to call all available demod functions, based on the user's entry
  Behavior:   Wait for the user to enter a string, then calls the selected function
************************************************************************************************************************/
int Si2176_demoLoop (L1_Si2176_Context *Si2176, char* choice) {
    char entry[MAX_LENGTH];
    int errcode;
    unsigned long freq;
    unsigned long  minRange, maxRange;
    int i;
    freq = 0;

    sprintf(entry, "%s", choice);

#ifdef    TUNER_ONLY
    if (fe > FRONT_END_COUNT) return 0;
    Si2176 = &(FrontEnd_Table[fe]);

    if (strlen(choice) > 0) {
        SiTRACE("choice '%s'\n",choice);
    } else {
        printf("\n%04d FrontEnd[%d] Command > ", ++commandCount, fe);
        fgets(entry,MAX_LENGTH,stdin);
        if (strlen(entry) > 0) entry[strlen(entry)-1]='\0';
    }

    /* front end selection */
    if ( (strcmp_nocase(entry, "0")==0) & (FRONT_END_COUNT>0) ) { fe = 0; printf ("Controlling FrontEnd %d\n",fe); return 1;}
    if ( (strcmp_nocase(entry, "1")==0) & (FRONT_END_COUNT>1) ) { fe = 1; printf ("Controlling FrontEnd %d\n",fe); return 1;}
    if ( (strcmp_nocase(entry, "2")==0) & (FRONT_END_COUNT>2) ) { fe = 2; printf ("Controlling FrontEnd %d\n",fe); return 1;}
    if ( (strcmp_nocase(entry, "3")==0) & (FRONT_END_COUNT>3) ) { fe = 3; printf ("Controlling FrontEnd %d\n",fe); return 1;}
#endif /* TUNER_ONLY */

    if (strcmp_nocase(entry, "exit"          )==0) { return 0;}
#ifdef    TUNER_ONLY
#ifdef    SiTRACES
    else if (strcmp_nocase(entry, "traces"   )==0) { Si2176_UserInput_traces();}
#endif /* SiTRACES */
    else if (strcmp_nocase(entry, "read"     )==0) { Si_I2C_UserInput_read (i2c);}
    else if (strcmp_nocase(entry, "write"    )==0) { Si_I2C_UserInput_write(i2c);}
    else if (strcmp_nocase(entry, "usb"           )==0) { mode = USB;}
    else if (strcmp_nocase(entry, "cust"          )==0) { mode = CUSTOMER;}
    else if (strcmp_nocase(entry, "simu"          )==0) { mode = SIMU;}
    else if (strcmp_nocase(entry, "trace"         )==0) { Si2176_trace            (Si2176); }
#endif /* TUNER_ONLY */
    else if (strcmp_nocase(entry, "InitAndConfig"          )==0)
    {
         if (Si2176_Init(Si2176) == 0 ) {
           Si2176_Configure(Si2176);
         } else {
          SiTRACE("\n");
          SiTRACE("ERROR ----------------------------------\n");
          SiTRACE("ERROR initializing the Si2176 at 0x%02x!\n", Si2176->i2c->address );
          SiTRACE("ERROR ----------------------------------\n");
          SiTRACE("\n");
         }
    }
    else if (strcmp_nocase(entry, "Status"        )==0) { Si2176_DisplayStatusByte     (Si2176); }
    else if (strcmp_nocase(entry, "GetRevision"   )==0) { Si2176_GetRevision           (Si2176); }
#ifdef USING_ATV_FILTER
    else if (strcmp_nocase(entry, "LoadATVVidFilt"   )==0) { Si2176_LoadVideofilter(Si2176,ATV_VIDFILT_TABLE,ATV_VIDFILT_LINES); }
#endif
#ifdef USING_DLIF_FILTER
    else if (strcmp_nocase(entry, "LoadDLIFVidFilt"   )==0) { Si2176_LoadVideofilter(Si2176,DLIF_VIDFILT_TABLE,DLIF_VIDFILT_LINES); }
#endif
    else if (stricmp(entry, "ATVConfig"     )==0)
    {
         Si2176_setupATVProperties(Si2176);
         printf("Sending Properties to Si2176\n");
         Si2176_downloadATVProperties(Si2176);
         printf("Done \n");
    }
    else if (stricmp(entry, "DTVConfig"     )==0)
    {
         Si2176_setupDTVProperties(Si2176);
         printf("Sending Properties to Si2176\n");
         Si2176_downloadDTVProperties(Si2176);
         printf("Done \n");
     }
    else if (stricmp(entry, "TunerConfig"   )==0)
    {
         Si2176_setupTUNERProperties(Si2176);
         printf("Sending Properties to Si2176\n");
         Si2176_downloadTUNERProperties(Si2176);
         printf("Done \n");
    }
    else if (stricmp(entry, "CommonConfig"  )==0)
    {
         Si2176_setupCOMMONProperties(Si2176);
         printf("Sending Properties to Si2176\n");
         Si2176_downloadCOMMONProperties(Si2176);
         printf("Done \n");
    }
    else if (stricmp(entry, "ATVTune"       )==0)
    {
        printf("ATV Center Frequency (in Hz)? ");

        if ((errcode=Si2176_GetUserFrequency(&freq)) != NO_Si2176_ERROR) {
           SiTRACE ("Si2176_GetUserFrequency error 0x%02x\n", errcode);
           return errcode;
        }
        Si2176_setupProperty(Si2176,Si2176_PropertyIndex(Si2176,"ATV_VIDEO_MODE"));

        if ((errcode=Si2176_ATVTune (Si2176, freq,  Si2176->prop->atv_video_mode.video_sys,  Si2176->prop->atv_video_mode.trans,  Si2176->prop->atv_video_mode.color, Si2176->prop->atv_video_mode.invert_signal)) != NO_Si2176_ERROR)
          { printf ("Error returned from ATVTune error = %s\nPlease press <Enter> to continue\n",Si2176_L1_API_ERROR_TEXT(errcode)); getc(stdin); return 1;}

  }
  else if (stricmp(entry, "DTVTune"       )==0)
  {
        printf("DTV Center Frequency (in Hz)? ");
        if ((errcode=Si2176_GetUserFrequency(&freq)) != NO_Si2176_ERROR)
           return errcode;
        Si2176_setupProperty(Si2176,Si2176_PropertyIndex(Si2176, "DTV_MODE"));

    if ((errcode=Si2176_DTVTune (Si2176, freq, Si2176->prop->dtv_mode.bw, Si2176->prop->dtv_mode.modulation, Si2176->prop->dtv_mode.invert_spectrum)) != NO_Si2176_ERROR)
      { printf ("Error returned from DTVTune error = %s\nPlease press <Enter> to continue\n",Si2176_L1_API_ERROR_TEXT(errcode)); getc(stdin); return 1;}

  }
    else if (stricmp(entry, "TunerStatus"   )==0) { Si2176_TunerStatus(Si2176);}
    else if (stricmp(entry, "ATVStatus"     )==0) { Si2176_ATVStatus(Si2176); }
    else if (stricmp(entry, "DTVStatus"     )==0) { Si2176_DTVStatus(Si2176);     }
    else if (stricmp(entry, "CLS"           )==0) { system("cls");}
    else if (stricmp(entry, "ClockOn"           )==0) { Si2176_ClockOn(Si2176);}
    else if (stricmp(entry, "ClockOff"           )==0) { Si2176_ClockOff(Si2176);}
    else if (stricmp(entry, "XOUTOn"           )==0) { Si2176_XOUTOn(Si2176);}
    else if (stricmp(entry, "XOUTOff"           )==0) { Si2176_XOUTOff(Si2176);}
    else if (stricmp(entry, "Powerdown"           )==0) { Si2176_Powerdown(Si2176);}
    else if (stricmp(entry, "Standby"           )==0) { Si2176_Standby(Si2176);}

    else if (stricmp(entry, "ChannelScanM"  )==0)
  {
     printf("Frequency Scan Start Hz ? ");
    if ((errcode=Si2176_GetUserFrequency(&minRange)) != NO_Si2176_ERROR)
       return errcode;

    printf("Frequency Scan Stop Hz ? ");
    if ((errcode=Si2176_GetUserFrequency(&maxRange)) != NO_Si2176_ERROR)
       return errcode;

    Si2176_setupProperty(Si2176,Si2176_PropertyIndex(Si2176,"ATV_RSQ_RSSI_THRESHOLD"));
    Si2176_setupProperty(Si2176,Si2176_PropertyIndex(Si2176,"ATV_RSQ_SNR_THRESHOLD"));

    Si2176_ATV_Channel_Scan_M(Si2176,minRange,maxRange, Si2176->prop->atv_rsq_rssi_threshold.lo, Si2176->prop->atv_rsq_rssi_threshold.hi,
      Si2176->prop->atv_rsq_snr_threshold.lo, Si2176->prop->atv_rsq_snr_threshold.hi );
    if ((Si2176->ChannelListSize) > 0)
    {
      printf("Channels Found \n");
      for (i=0; i< Si2176->ChannelListSize;++i)
        printf("%d\t%ld\n",i+1,Si2176->ChannelList[i]);
    }
    else
    {
      printf("No Channels Found \n");
    }
  }
  else if (stricmp(entry, "ChannelScanPal"  )==0)
  {
    printf("Frequency Scan Start Hz ? ");
       if ((errcode=Si2176_GetUserFrequency(&minRange)) != NO_Si2176_ERROR)
       return errcode;


    printf("Frequency Scan Stop Hz ? ");
      if ((errcode=Si2176_GetUserFrequency(&maxRange)) != NO_Si2176_ERROR)
       return errcode;


    Si2176_setupProperty(Si2176,Si2176_PropertyIndex(Si2176,"ATV_RSQ_RSSI_THRESHOLD"));
    Si2176_setupProperty(Si2176,Si2176_PropertyIndex(Si2176,"ATV_RSQ_SNR_THRESHOLD"));

    Si2176_ATV_Channel_Scan_PAL(Si2176,minRange,maxRange,
                                Si2176->prop->atv_rsq_rssi_threshold.lo,
                                Si2176->prop->atv_rsq_rssi_threshold.hi,
                                Si2176->prop->atv_rsq_snr_threshold.lo,
                                Si2176->prop->atv_rsq_snr_threshold.hi );
    if ((Si2176->ChannelListSize) > 0)
    {
      printf("Channels Found \n");
      printf("Num\tType\tChannel \n");
      for (i=0; i< Si2176->ChannelListSize;++i)
        printf("%d\t%s\t%ld\n",i,Si2176->ChannelType[i],Si2176->ChannelList[i]);
    }
    else
    {
      printf("No Channels Found \n");
    }
  }

    else if (strcmp_nocase(entry, "m"             )==0) { Si2176_menu(1);}
    else if (strcmp_nocase(entry, "help"          )==0) { Si2176_help();}
    else if (strcmp_nocase(entry, "cls"           )==0) { system("cls");}
    else                                          { Si2176_menu(1);}

  return 1;
}
#endif  /* Si2176_COMMAND_LINE_APPLICATION  */

#ifdef    TUNER_ONLY
/************************************************************************************************************************
  NAME: main
  DESCRIPTION:  Main Routine
 ************************************************************************************************************************/
int  main(int argc, char *argv[]) {
    argc=argc; /* To avoid compiler warning */
    argv=argv; /* To avoid compiler warning */

    SiTraceDefaultConfiguration();
    SiTraceConfiguration("traces -output file -file on -verbose on -function on -line on\n");

    /* I2C pointer initialization (to allow i2c validation) */
    i2c = &i2c_context;
    L0_Init(i2c);

    #ifdef    SILABS_DEMOD_EVB
      demod = &(demodObj);
      demod->i2c = &(demod->i2cObj);
      demod->i2c->address    = 0xc8;
      demod->i2c->indexSize  = 2;
      demod->i2c->trackWrite = 1;
    #endif /* SILABS_DEMOD_EVB */

    /* Software Init */
    for (fe=0; fe<FRONT_END_COUNT; fe++) {
      front_end = &(FrontEnd_Table[fe]);
      Si2176_L1_API_Init(front_end, Si2176_BASE_ADDRESS+(2*fe));
      front_end->i2c->trackRead = front_end->i2c->trackWrite = 1;
      Si2176_configure_i2c_communication  (front_end);
      if (Si2176_Init(front_end) != 0 ) {
        SiTRACE("\n");
        SiTRACE("ERROR ----------------------------------\n");
        SiTRACE("ERROR initializing the Si2176 at 0x%02x!\n",Si2176_BASE_ADDRESS+(2*fe) );
        SiTRACE("ERROR ----------------------------------\n");
        SiTRACE("\n");
      }
    }

    fe = 0;
    /* Front-end pointers initialization */
    front_end = &(FrontEnd_Table[fe]);

#ifdef    Si2176_COMMAND_LINE_APPLICATION
    while (Si2176_demoLoop(front_end,""));
#else  /* Si2176_COMMAND_LINE_APPLICATION */
    Si2176_ProcessAPITopLevelSequence(front_end);
#endif /* Si2176_COMMAND_LINE_APPLICATION */

    return 0;
}
#endif /* TUNER_ONLY */





