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
   API types used by commands and properties
   FILE: Si2176_typedefs.h
   Supported IC : Si2176
   Compiled for ROM 13 firmware 3_2_build_6
   Revision: 0.1
   Date: December 22 2011
**************************************************************************************/
#ifndef   Si2176_TYPEDEFS_H
#define   Si2176_TYPEDEFS_H

#define BUF_SIZE 1000
/* define the maximum possible channels (1002MHz - 43MHz) / 6MHz  (required for the channelscan array)*/
#define MAX_POSSIBLE_CHANNELS 160
#define MAX_LENGTH             80

typedef struct L1_Si2176_Context {
  L0_Context                 *i2c;
  L0_Context                  i2cObj;
  Si2176_CmdObj              *cmd;
  Si2176_CmdObj               cmdObj;
  Si2176_CmdReplyObj         *rsp;
  Si2176_CmdReplyObj          rspObj;
  Si2176_PropObj             *prop;
  Si2176_PropObj              propObj;
  Si2176_COMMON_REPLY_struct *status;
  Si2176_COMMON_REPLY_struct  statusObj;
  char ATVMode;
  char DTVMode;
  char ATVConfigurationChangedFlag;
  char DTVConfigurationChangedFlag;
  unsigned long newFrequency;
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
} L1_Si2176_Context;
#endif /* Si2176_TYPEDEFS_H */





