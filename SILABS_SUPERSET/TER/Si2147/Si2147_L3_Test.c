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
                  Silicon Laboratories Broadcast Si2147 Layer 3 API


   L3 sample application
   FILE: Si2147_L3_Test.c
   Supported IC : Si2147
   Compiled for ROM 50 firmware 3_1_build_3
   Revision: 0.1
   Tag:  ROM50_3_1_build_3_V0.1
   Date: June 30 2015
****************************************************************************************/
#include "Si2147_L3_Test.h"

/* define TUNER_ONLY if using a Si2147 tuner without demod                                                    */
/* (It should be defined at project/makefile level to use 100% identical code for tuner-only and tuner+demod)   */
/* #define TUNER_ONLY */

#ifdef    TUNER_ONLY

/* define SILABS_DEMOD_EVB if used on a tuner_only application on a demod EVB (opens i2c_passthru in main)      */
/* (It should be defined at project/makefile level to use 100% identical code for tuner-only EVB and demod EVB) */
/* #define SILABS_DEMOD_EVB*/

/* define Si2147_COMMAND_LINE_APPLICATION if using this code in console mode                                                     */
/* (Si2147_COMMAND_LINE_APPLICATION should be defined at project/makefile level to use 100% identical code for console and TV )  */
/* #define Si2147_COMMAND_LINE_APPLICATION */

/* define FRONT_END_COUNT 1 for a single tuner application                                                                         */
/* (FRONT_END_COUNT should be defined at project/makefile level to use 100% identical code for single-frontend and multi-frontend) */
#define FRONT_END_COUNT 1

int  commandCount  = 0;
int  fe;

L1_Si2147_Context          FrontEnd_Table   [FRONT_END_COUNT];
L1_Si2147_Context         *Si2147;
L1_Si2147_Context         *tuners[FRONT_END_COUNT];
L1_Si2147_Context         *front_end;
/* Also init a simple i2c context to allow i2c communication checking */
L0_Context* i2c;
L0_Context  i2c_context;
CONNECTION_TYPE mode;

#ifdef    SiTRACES
/************************************************************************************************************************
  Si2147_UserInput_traces function
  Use:        send a traces configuration message to the L0 SiTRACES functions
              the Si2147_UserInput_traces function asks the user which type of configuration he wishes.
              Then, memorize the message and calls SiTraceConfiguration.
  Returns:    void
  Porting:    Not compiled if SiTRACES is not defined in Silabs_L0_API.h
************************************************************************************************************************/
void Si2147_UserInput_traces               (void)
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
  Si2147_UserInputString function
  Use:        retrieve a string entered by the user
  Parameters: text, a pointer to the string buffer
              max_size, the size allocated by the calling function for the text buffer
  Behavior:   Retrieves the string using fgets to avoid overflows. As fgets keeps the 'carriage return' except
                if the string is longer than max_size, replace it (if present) by the terminating character
  Returns:    the length of the string
************************************************************************************************************************/
int  Si2147_UserInputString                (char* text, int max_size) {
  char *newline;
  if ( fgets(text, max_size, stdin) != NULL ) {
    newline = strchr(text, '\n');             /* search for newline character        */
    if ( newline != NULL ) { *newline = '\0'; /* overwrite trailing newline (if any) */ }
  }
  return (int)(strlen(text));
}
/************************************************************************************************************************
  Si2147_trace function
  Use:        trace toggle function
              Used to toggle tracing for all register accesses, at byte level
  Behavior:   Calls the tracking functions for read and write for both demod and tuner
************************************************************************************************************************/
void Si2147_trace                          (L1_Si2147_Context *api) {
    int trackFlag;
    trackFlag = !api->i2c->trackRead;
    L0_TrackWrite(i2c     , trackFlag);
    L0_TrackRead (i2c     , trackFlag);
    L0_TrackWrite(api->i2c, trackFlag);
    L0_TrackRead (api->i2c, trackFlag);
}
#endif /* TUNER_ONLY */
/************************************************************************************************************************
  NAME: Si2147_configure_i2c_communication
  DESCRIPTION:        Setup USB communication with Si2147 EVB
  Parameter:  Pointer to Si2147 Context (I2C address)
  Returns:    nothing
************************************************************************************************************************/
void Si2147_configure_i2c_communication    (L1_Si2147_Context *api, demod_Context *demodptr)
{
#ifdef    USB_Capability
    double        retdval;
    char rettxtBuffer[256];
    char *rettxt;
    rettxt = rettxtBuffer;
    L0_Connect (api->i2c, USB);
    L0_Cypress_Configure("-i2c"                 ,"400khz", 0   , &retdval, &rettxt);  /* at 400kHz SCL rate     */
 #ifdef    SILABS_DEMOD_EVB
    L0_Connect (demodptr->i2c, USB);
 #endif /* SILABS_DEMOD_EVB */
#endif /* USB_Capability */
#ifdef    SILABS_DEMOD_EVB
    L1_WRITE(demodptr, i2c_passthru, i2c_passthru_enabled);
#endif /* SILABS_DEMOD_EVB */
}

#ifdef Si2147_COMMAND_LINE_APPLICATION
/************************************************************************************************************************
  NAME: Si2147_DisplayStatusByte
  DESCRIPTION:Read Si2147 STATUS byte and display status bits
  Parameter:  Si2147 Context (I2C address)
  Returns:    Si2147/I2C transaction error code
************************************************************************************************************************/
int  Si2147_DisplayStatusByte              (L1_Si2147_Context *api)
{
    int error_code;

    error_code = Si2147_L1_CheckStatus(api);
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
  NAME : Si2147_GetRevision
  DESCRIPTION:  Execute Si2147 GET_REV function and display response fields
  Parameter:  Si2147 Context (I2C address)
  Returns:    I2C transaction error code
************************************************************************************************************************/
int  Si2147_GetRevision                    (L1_Si2147_Context *api)
{
    char message[1000];

    if (Si2147_L1_GET_REV(api) != NO_Si2147_ERROR)          /* execute GET_REV and always read response */
    {
        printf("Error reading GET_REV\n");
        return ERROR_Si2147_SENDING_COMMAND;
    }
    Si2147_L1_GetCommandResponseString(api, Si2147_GET_REV_CMD_CODE,"\n", message);
    printf("%s\n",message);

    return 0;
}
/************************************************************************************************************************
  Si2147_DTVStatus function
  Use:        Reports tuner status from DTV_STATUS response
  Parameter:  Pointer to Si2147 Context (I2C address)
  Returns:    I2C transaction error code
************************************************************************************************************************/
int Si2147_DTVStatus (L1_Si2147_Context *Si2147)
{
    char *message=(char *) malloc(BUF_SIZE);

    if (Si2147_L1_DTV_STATUS(Si2147, Si2147_DTV_STATUS_CMD_INTACK_CLEAR) != 0) { /* execute DTV_STATUS and always read response */
        printf("Error reading DTV_STATUS\n");
        return ERROR_Si2147_SENDING_COMMAND;
    }
  Si2147_L1_GetCommandResponseString(Si2147, Si2147_DTV_STATUS_CMD_CODE,"\n", message);                  /* display results */
  printf("%s\n",message);

    return 0;
}
/************************************************************************************************************************
  NAME: Si2147_TunerStatus
  DESCRIPTION:        Reports tuner status from TUNER_STATUS response
  Parameter:  Pointer to Si2147 Context (I2C address)
  Returns:    I2C transaction error code
************************************************************************************************************************/
int Si2147_TunerStatus (L1_Si2147_Context *Si2147)
{
    char *message=(char *) malloc(BUF_SIZE);

    if (Si2147_L1_TUNER_STATUS(Si2147, Si2147_TUNER_STATUS_CMD_INTACK_CLEAR) != NO_Si2147_ERROR) { /* execute TUNER_STATUS and always read response */
        printf("Error reading TUNER_STATUS\n");
        return ERROR_Si2147_SENDING_COMMAND;
    }
  Si2147_L1_GetCommandResponseString(Si2147, Si2147_TUNER_STATUS_CMD_CODE, "\n", message);
  printf("%s\n",message);/* display results */

    return 0;
}
/************************************************************************************************************************
  NAME: Si2147_GetUserFrequency
  DESCRIPTION: Function to process user input frequency and return an error if invalid.
  Parameter: unsigned long *fIn - returns the user entered frequency in Hz.
  Returns : 1 if an error occurred, 0 otherwise.
************************************************************************************************************************/
int Si2147_GetUserFrequency(unsigned long *fIn)
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
  Si2147_help function
  Use:        console application help function
              Used to explain how to init the EVB, tune and scan
************************************************************************************************************************/
int  Si2147_help                           (void) {
    printf("\n\
----------------------------------------------------------------------------\n\
       This is a demonstration application used to illustrate how to use    \n\
            the Si2147 API delivered by Silicon Laboratories                \n\
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
  NAME: Si2147_menu
  DESCRIPTION: Si2147 user menu function
              Used to display the various possibilities offered to the user
  Behavior:   Prints the menu in the console
************************************************************************************************************************/
void Si2147_menu                           (unsigned char full) {
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
------  Si2147 ------\n\
");
}
  printf("\
InitAndConfig  : Initialize and Configure the Si2147\n\
Status         : Read Si2147 STATUS\n\
GetRevision    : Display revision info\n");
#ifdef USING_ALIF_FILTER
printf ("LoadALIFVidfilt : Load the ALIF videofilter\n");
#endif
#ifdef USING_DLIF_FILTER
printf("LoadDLIFVidfilt : Load the DLIF videofilter\n");
#endif
printf("DTVConfig      : Configure the Properties for DTV mode\n\
TunerConfig    : Configure the Properties for the Tuner\n\
CommonConfig   : Configure the Common Properties \n\
DTVTune        : Tune a DTV channel\n\
TunerStatus    : Display Tuner Status (TC, RSSI, ...)\n\
DTVStatus      : Display DTV Status   (CHL, ...)\n\
AGCOverride    : Override the AGC Control\n\
Standby        : Put the Part in Standby Mode\n\
Powerdown      : Powerdown the Part\n\
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
  NAME: Si2147_demoLoop
  DESCRIPTION: Demo application loop function
              Used to call all available demod functions, based on the user's entry
  Behavior:   Wait for the user to enter a string, then calls the selected function
************************************************************************************************************************/
int Si2147_demoLoop (L1_Si2147_Context *Si2147, char* choice) {
    char entry[MAX_LENGTH];
    int errcode;
    unsigned long freq;
    freq = 0;

    sprintf(entry, "%s", choice);

#ifdef    TUNER_ONLY
    if (fe > FRONT_END_COUNT) return 0;
    Si2147 = &(FrontEnd_Table[fe]);

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
    else if (strcmp_nocase(entry, "traces"   )==0) { Si2147_UserInput_traces();}
#endif /* SiTRACES */
    else if (strcmp_nocase(entry, "read"     )==0) { Si_I2C_UserInput_read (i2c);}
    else if (strcmp_nocase(entry, "write"    )==0) { Si_I2C_UserInput_write(i2c);}
    else if (strcmp_nocase(entry, "usb"      )==0) { mode = USB;}
    else if (strcmp_nocase(entry, "cust"     )==0) { mode = CUSTOMER;}
    else if (strcmp_nocase(entry, "simu"     )==0) { mode = SIMU;}
    else if (strcmp_nocase(entry, "trace"    )==0) { Si2147_trace (Si2147); }
#endif /* TUNER_ONLY */
    else if (strcmp_nocase(entry, "InitAndConfig"          )==0)
    {
         if (Si2147_Init(Si2147) == 0 ) {
           Si2147_Configure(Si2147);
         } else {
          SiTRACE("\n");
          SiTRACE("ERROR ----------------------------------\n");
          SiTRACE("ERROR initializing the Si2147 at 0x%02x!\n", Si2147->i2c->address );
          SiTRACE("ERROR ----------------------------------\n");
          SiTRACE("\n");
         }
    }
    else if (strcmp_nocase(entry, "Status"        )==0) { Si2147_DisplayStatusByte     (Si2147); }
    else if (strcmp_nocase(entry, "GetRevision"   )==0) { Si2147_GetRevision           (Si2147); }
#ifdef USING_DLIF_FILTER
    else if (strcmp_nocase(entry, "LoadDLIFVidFilt"   )==0) { Si2147_LoadVideofilter(Si2147,DLIF_VIDFILT_TABLE,DLIF_VIDFILT_LINES); }
#endif
    else if (stricmp(entry, "DTVConfig"     )==0)
    {
         Si2147_setupDTVProperties(Si2147);
         printf("Sending Properties to Si2147\n");
         Si2147_downloadDTVProperties(Si2147);
         printf("Done \n");
     }
    else if (stricmp(entry, "TunerConfig"   )==0)
    {
         Si2147_setupTUNERProperties(Si2147);
         printf("Sending Properties to Si2147\n");
         Si2147_downloadTUNERProperties(Si2147);
         printf("Done \n");
    }
    else if (stricmp(entry, "CommonConfig"  )==0)
    {
         Si2147_setupCOMMONProperties(Si2147);
         printf("Sending Properties to Si2147\n");
         Si2147_downloadCOMMONProperties(Si2147);
         printf("Done \n");
    }
  else if (stricmp(entry, "DTVTune"       )==0)
  {
        printf("DTV Center Frequency (in Hz)? ");
        if ((errcode=Si2147_GetUserFrequency(&freq)) != NO_Si2147_ERROR)
           return errcode;
        Si2147_setupProperty(Si2147,Si2147_PropertyIndex(Si2147, "DTV_MODE"));

    if ((errcode=Si2147_DTVTune (Si2147, freq, Si2147->prop->dtv_mode.bw, Si2147->prop->dtv_mode.modulation, Si2147->prop->dtv_mode.invert_spectrum)) != NO_Si2147_ERROR)
      { printf ("Error returned from DTVTune error = %s\nPlease press <Enter> to continue\n",Si2147_L1_API_ERROR_TEXT(errcode)); getc(stdin); return 1;}

  }
    else if (stricmp(entry, "TunerStatus"   )==0) { Si2147_TunerStatus(Si2147);}
    else if (stricmp(entry, "DTVStatus"     )==0) { Si2147_DTVStatus(Si2147);     }
    else if (stricmp(entry, "CLS"           )==0) { system("cls");}
    else if (stricmp(entry, "XOUTOn"           )==0) { Si2147_XoutOn(Si2147);}
    else if (stricmp(entry, "XOUTOff"           )==0) { Si2147_XoutOff(Si2147);}
    else if (stricmp(entry, "Powerdown"           )==0) { Si2147_Powerdown(Si2147);}
    else if (stricmp(entry, "Standby"           )==0) { Si2147_Standby(Si2147);}
    else if (stricmp(entry,"AGCOverride"    )==0)
    {
        printf("AGC Override Mode (MAX,TOP,NORMAL)?");
        fgets(entry,MAX_LENGTH,stdin);
        if (strlen(entry) > 0) entry[strlen(entry)-1]='\0';

        if      ( (strcmp_nocase(entry, "MAX")==0) ) { Si2147_AGC_Override(Si2147, Si2147_FORCE_MAX_AGC); }
        else if ( (strcmp_nocase(entry, "TOP")==0) ) { Si2147_AGC_Override(Si2147, Si2147_FORCE_TOP_AGC); }
        else if ( (strcmp_nocase(entry, "NORMAL")==0) ) { Si2147_AGC_Override(Si2147, Si2147_FORCE_NORMAL_AGC); }
        else    { printf ("Error Invalid Choice\nPlease press <Enter> to continue\n"); getc(stdin); return 1;}
    }
    else if (strcmp_nocase(entry, "m"             )==0) { Si2147_menu(1);}
    else if (strcmp_nocase(entry, "help"          )==0) { Si2147_help();}
    else if (strcmp_nocase(entry, "cls"           )==0) { system("cls");}
    else                                          { Si2147_menu(1);}

  return 1;
}
#endif  /* Si2147_COMMAND_LINE_APPLICATION  */

#ifdef    TUNER_ONLY
/************************************************************************************************************************
  NAME: main
  DESCRIPTION:  Main Routine
 ************************************************************************************************************************/
int  main(int argc, char *argv[]) {
    argc=argc; /* To avoid compiler warning */
    argv=argv; /* To avoid compiler warning */

    int tuner_addr[] = {Si2147_BASE_ADDRESS,0xc6};
    int demod_addr[] = {0xc8,0xce};

    SiTraceDefaultConfiguration();
    SiTraceConfiguration("traces -output file -file on -verbose on -function on -line on\n");

    /* I2C pointer initialization (to allow i2c validation) */
    i2c = &i2c_context;
    L0_Init(i2c);

    for (fe=0; fe<FRONT_END_COUNT; fe++)
        tuners[fe]= &(FrontEnd_Table[fe]);

    /* Software Init */
    for (fe=0; fe<FRONT_END_COUNT; fe++)
    {
        #ifdef    SILABS_DEMOD_EVB
        demod = &(demodObj);
        demod->i2c = &(demod->i2cObj);
        demod->i2c->address    = demod_addr[fe];
        demod->i2c->indexSize  = 2;
        demod->i2c->trackWrite = 1;
        #endif /* SILABS_DEMOD_EVB */

      front_end = &(FrontEnd_Table[fe]);
      Si2147_L1_API_Init(front_end, tuner_addr[fe]);
      front_end->i2c->trackRead = front_end->i2c->trackWrite = 1;
      Si2147_configure_i2c_communication  (front_end,demod);

      //use XTAL for 1st tuner and if additional tuners use EXTCLK
      if (fe==0)
      {
          front_end->cmd->power_up.clock_mode =  Si2147_POWER_UP_CMD_CLOCK_MODE_XTAL;
          front_end->cmd->power_up.en_xout    =  Si2147_POWER_UP_CMD_EN_XOUT_EN_XOUT;
          front_end->cmd->config_clocks.clock_mode = Si2147_CONFIG_CLOCKS_CMD_CLOCK_MODE_XTAL;
      }
      else
      {
          front_end->cmd->power_up.clock_mode = Si2147_POWER_UP_CMD_CLOCK_MODE_EXTCLK;
          front_end->cmd->power_up.en_xout    = Si2147_POWER_UP_CMD_EN_XOUT_DIS_XOUT;
          front_end->cmd->config_clocks.clock_mode = Si2147_CONFIG_CLOCKS_CMD_CLOCK_MODE_EXTCLK;
      }

    }

 /* If using 2 tuners (or more) startup both tuners using CONFIG_I2C command to broadcast firmware download */
#if FRONT_END_COUNT > 1

     if (Si2147_PowerUpUsingBroadcastI2C(tuners,FRONT_END_COUNT) != NO_Si2147_ERROR )
      {
        SiTRACE("\n");
        SiTRACE("ERROR ----------------------------------\n");
        SiTRACE("ERROR initializing the Si2147's!\n");
        SiTRACE("ERROR ----------------------------------\n");
        SiTRACE("\n");
      }

#else /* use standard init for a single tuner */
      if (Si2147_Init(&(FrontEnd_Table[0])) != NO_Si2147_ERROR )
      {
        SiTRACE("\n");
        SiTRACE("ERROR ----------------------------------\n");
        SiTRACE("ERROR initializing the Si2147's!\n");
        SiTRACE("ERROR ----------------------------------\n");
        SiTRACE("\n");
      }

#endif
    fe = 0;
    /* Front-end pointers initialization */
    front_end = &(FrontEnd_Table[fe]);

#ifdef    Si2147_COMMAND_LINE_APPLICATION
    while (Si2147_demoLoop(front_end,""));
#endif /* Si2147_COMMAND_LINE_APPLICATION */

    return 0;
}
#endif /* TUNER_ONLY */







