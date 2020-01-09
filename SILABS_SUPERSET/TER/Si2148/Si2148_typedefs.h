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
                  Silicon Laboratories Broadcast Si2148 Layer 1 API


   API types used by commands and properties
   FILE: Si2148_typedefs.h
   Supported IC : Si2148
   Compiled for ROM 33 firmware 2_1_build_11
   Revision: 0.2
   Date: March 12 2014
**************************************************************************************/
#ifndef   Si2148_TYPEDEFS_H
#define   Si2148_TYPEDEFS_H

#define BUF_SIZE 1000
/* define the maximum possible channels (1002MHz - 43MHz) / 6MHz  (required for the channelscan array)*/
#define MAX_POSSIBLE_CHANNELS 160
/* _additional_defines_point */
#define MAX_LENGTH             80

typedef struct L1_Si2148_Context {
  L0_Context                 *i2c;
  L0_Context                  i2cObj;
  Si2148_CmdObj              *cmd;
  Si2148_CmdObj               cmdObj;
  Si2148_CmdReplyObj         *rsp;
  Si2148_CmdReplyObj          rspObj;
  Si2148_PropObj             *prop;
  Si2148_PropObj              propObj;
  Si2148_COMMON_REPLY_struct *status;
  Si2148_COMMON_REPLY_struct  statusObj;
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
/* _additional_struct_members_point */
} L1_Si2148_Context;

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

#endif /* Si2148_TYPEDEFS_H */





