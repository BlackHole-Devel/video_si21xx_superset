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
                  Silicon Laboratories Broadcast Si2157 Layer 1 API


   API types used by commands and properties
   FILE: Si2157_typedefs.h
   Supported IC : Si2157
   Compiled for ROM 50 firmware 3_1_build_3
   Revision: 0.1
   Date: June 29 2015
**************************************************************************************/
#ifndef   Si2157_TYPEDEFS_H
#define   Si2157_TYPEDEFS_H

 #define BUF_SIZE 1000
/* define the maximum possible channels (1002MHz - 43MHz) / 6MHz  (required for the channelscan array)*/
#define MAX_POSSIBLE_CHANNELS 160
/* _additional_defines_point */
#define MAX_LENGTH             80

#define DOWNLOAD_ON_CHANGE 1
#define DOWNLOAD_ALWAYS 0

/* The following defines are to allow use of PowerUpWithPatch function with the powerUpUsingBroadcastI2C function. */
#define SKIP_NONE 0x00
#define SKIP_POWERUP 0x01
#define SKIP_LOADFIRMWARE 0x02
#define SKIP_STARTFIRMWARE 0x04
/* define the tuner broadcast address for common patch download. */
#define Si2157_BROADCAST_ADDRESS 0xc4

typedef struct L1_Si2157_Context {
  L0_Context                 *i2c;
  L0_Context                  i2cObj;
  Si2157_CmdObj              *cmd;
  Si2157_CmdObj               cmdObj;
  Si2157_CmdReplyObj         *rsp;
  Si2157_CmdReplyObj          rspObj;
  Si2157_PropObj             *prop;
  Si2157_PropObj              propObj;
  Si2157_PropObj             *propShadow;
  Si2157_PropObj              propShadowObj;
  Si2157_COMMON_REPLY_struct *status;
  Si2157_COMMON_REPLY_struct  statusObj;
  /*chip rev constants for integrity checking */
  unsigned char chiprev;
  unsigned char part;
  /* Last 2 digits of part number */
  unsigned char partMajorVersion;
  unsigned char partMinorVersion;
  unsigned char partRomid;
 /* Channel Scan Globals */
  /* Global array to store the list of found channels */
  unsigned long ChannelList[MAX_POSSIBLE_CHANNELS];
  /* ChannelScanPal needs to store the PAL type also so allocate 4 chars each for that */
  char ChannelType[MAX_POSSIBLE_CHANNELS][4];
  /* Number of found channels from a channel scan */
  int ChannelListSize;
  /* global variable for property settings mode.  Can be either DOWNLOAD_ON_CHANGE (recommended) DOWNLOAD_ALWAYS. */
  int propertyWriteMode;
  /* allows reuse of PowerUpWithPatch function by PowerUpUsingBroadcastI2C function */
  char load_control;
/* _additional_struct_members_point */
} L1_Si2157_Context;

/* _additional_definitions_start */
#ifndef __VID_FILT_STRUCT__
#define __VID_FILT_STRUCT__
/* struct to read video filter file with varying line lengths */
typedef struct  {
  char vid_filt_len;
  unsigned char vid_filt_table [16];
} vid_filt_struct;
#endif /* __VID_FILT_STRUCT__ */

#ifndef __FIRMWARE_STRUCT__
#define __FIRMWARE_STRUCT__
typedef struct  {
  unsigned char firmware_len;
  unsigned char firmware_table[16];
} firmware_struct;
#endif /* __FIRMWARE_STRUCT__ */

/* _additional_definitions_point */

#endif /* Si2157_TYPEDEFS_H */





