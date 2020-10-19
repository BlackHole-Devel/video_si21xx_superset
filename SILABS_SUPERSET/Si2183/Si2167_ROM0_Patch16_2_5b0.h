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
#ifndef _Si2167_PATCH16_2_5b0_TABLE_H_
#define _Si2167_PATCH16_2_5b0_TABLE_H_

#define Si2167_PATCH16_2_5b0_PART    67
#define Si2167_PATCH16_2_5b0_ROM      0
#define Si2167_PATCH16_2_5b0_PMAJOR  '5'
#define Si2167_PATCH16_2_5b0_PMINOR  '0'
#define Si2167_PATCH16_2_5b0_PBUILD   3

/* 47 bytes in Si2167_PATCH16_2_5b0 */


#ifndef __FIRMWARE_STRUCT__
#define __FIRMWARE_STRUCT__
typedef struct firmware_struct {
  unsigned char firmware_len;
  unsigned char firmware_table[16];
} firmware_struct;
#endif /* __FIRMWARE_STRUCT__ */

firmware_struct Si2167_PATCH16_2_5b0[] = {
{  8 , { 0x05,0x00,0x67,0xD2,0x09,0x5A,0x00,0x00 } },
{  8 , { 0x0C,0x2C,0xFD,0x33,0x37,0x92,0x64,0x21 } },
{  3 , { 0x42,0xB2,0x4D } },
{  8 , { 0x0C,0xD5,0xF8,0xAC,0x40,0x55,0x57,0x64 } },
{  4 , { 0x43,0x51,0xDE,0x46 } },
{  8 , { 0x09,0xF7,0x26,0xD6,0x0D,0x04,0xDB,0x90 } },
{  8 , { 0x0C,0xC7,0x13,0x99,0x33,0x05,0xE7,0xC7 } },
};

#define Si2167_PATCH16_2_5b0_LINES (sizeof(Si2167_PATCH16_2_5b0)/(sizeof(firmware_struct)))

#endif /* _Si2167_PATCH16_2_5b0_TABLE_H_ */

