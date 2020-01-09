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
#ifndef  _SiLabs_API_L3_Console_H_
#define  _SiLabs_API_L3_Console_H_

#ifdef    WITH_KBHIT
/* library for kbhit: conio.h */
  #include <conio.h>
#endif  /* WITH_KBHIT */

#include "SiLabs_API_L3_Wrapper.h"
#ifdef    CONFIG_MACROS
 #include "SiLabs_API_L3_Config_Macros.h"
#endif /* CONFIG_MACROS */


#ifdef    __cplusplus
 extern "C" {
#endif /* __cplusplus */

typedef struct _SiLabs_Carriers_Struct {
  int            carriers_count ;
  int           *standard       ;
  int           *freq           ;
  int           *bandwidth_Hz   ;
  int           *stream         ;
  unsigned int  *symbol_rate_bps;
  int           *constellation  ;
  int           *polarization   ;
  int           *band           ;
  int           *data_slice_id  ;
  int           *plp_id         ;
  int           *T2_base_lite   ;
  int           *SSI            ;
  int           *SQI            ;
} SiLabs_Carriers_Struct;

extern SiLabs_Carriers_Struct *Carriers_Table;

int   SiLabs_Scan_Table_Init          (void);
int   SiLabs_Scan_Table_Clear         (void);
int   SiLabs_Scan_Table_Count         (void);
int   SiLabs_Scan_Table_AddOneCarrier (                   int  standard, int  freq, int  bandwidth_Hz, int  stream, unsigned int  symbol_rate_bps, int  constellation, int  polarization, int  band, int  data_slice_id, int  plp_id, int  T2_base_lite);
int   SiLabs_Scan_Table_Carrier_Info  (int carrier_index, int *standard, int *freq, int *bandwidth_Hz, int *stream, unsigned int *symbol_rate_bps, int *constellation, int *polarization, int *band, int *data_slice_id, int *plp_id, int *T2_base_lite);
int   SiLabs_Scan_Table_Carrier_Text  (int carrier_index, char *formatted_infos);
int   SiLabs_Scan_Table_Infos         (void);
int  SiLabs_Scan_Check_And_Add_Carrier(SILABS_FE_Context *front_end, int  standard, int  freq, int  bandwidth_Hz, int  stream, unsigned int  symbol_rate_bps, int  constellation, int  polarization, int  band, int  data_slice_id, int  plp_id, int  T2_base_lite);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

#endif /* _SiLabs_API_L3_Console_H_ */
