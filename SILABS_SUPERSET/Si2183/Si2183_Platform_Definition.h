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
#ifndef    _Si2183_PLATFORM_DEFINITION_H_
#define    _Si2183_PLATFORM_DEFINITION_H_
/* Change log

 As from V0.0.9.0
  <new_feature>[superset] Changing tags to allow SILABS_SUPERSET use (one code, all configs)
    Using TERRESTRIAL_FRONT_END instead of DEMOD_DVB_T         (there are products with ISDB-T and not DVB-T)
    Using SATELLITE_FRONT_END   instead of DEMOD_DVB_S_S2_DSS  (for consistency with the above)

*/

/******************************************************************************/
/* TER Tuner FEF management options */
/******************************************************************************/
#define Si2183_FEF_MODE_SLOW_NORMAL_AGC   0
#define Si2183_FEF_MODE_FREEZE_PIN        1
#define Si2183_FEF_MODE_SLOW_INITIAL_AGC  2
#define Si2183_FEF_MODE_TUNER_AUTO_FREEZE 3

/******************************************************************************/
/* TER Tuner FEF management selection (possible values are defined above) */
/* NB : This selection is the ‘preferred’ solution.                           */
/* The code will use more compilation flags to slect the final mode based     */
/*  on what the TER tuner can actually do.                                    */
/******************************************************************************/
#define Si2183_FEF_MODE    Si2183_FEF_MODE_FREEZE_PIN

/******************************************************************************/
/* Tuners selection (one terrestrial tuner, one satellite tuner )             */
/******************************************************************************/
#ifdef    TERRESTRIAL_FRONT_END

#ifdef    TER_TUNER_SILABS
  #include  "SiLabs_TER_Tuner_API.h"
#endif /* TER_TUNER_SILABS */

#ifndef   TER_TUNER_SILABS

   "If you get a compilation error on this line, it means that no terrestrial tuner has been selected. Define TER_TUNER_xxxx at project-level!";

#endif /* TER_TUNER_SILABS */

#endif /* TERRESTRIAL_FRONT_END */

#ifdef    SATELLITE_FRONT_END
#ifdef    SAT_TUNER_SILABS
  #include  "SiLabs_SAT_Tuner_API.h"
#endif /* SAT_TUNER_SILABS */
#endif /* SATELLITE_FRONT_END */

/******************************************************************************/
/* Clock sources definition (allows using 'clear' names for clock sources)    */
/******************************************************************************/
typedef enum Si2183_CLOCK_SOURCE {
  Si2183_Xtal_clock = 0,
  Si2183_TER_Tuner_clock,
  Si2183_SAT_Tuner_clock
} Si2183_CLOCK_SOURCE;

/******************************************************************************/
/* TER and SAT clock source selection (used by Si2183_switch_to_standard)     */
/* ( possible values are those defined above in Si2183_CLOCK_SOURCE )         */
/******************************************************************************/
#ifdef   SILABS_EVB
  #define Si2183_TER_CLOCK_SOURCE            Si2183_TER_Tuner_clock
  #define Si2183_SAT_CLOCK_SOURCE            Si2183_Xtal_clock
#else
  #define Si2183_TER_CLOCK_SOURCE            Si2183_TER_Tuner_clock
  #define Si2183_SAT_CLOCK_SOURCE            Si2183_SAT_Tuner_clock
#endif /* SILABS_EVB */

#include "Si2183_L1_API.h"
#include "Si2183_Properties_Functions.h"

#endif /* _Si2183_PLATFORM_DEFINITION_H_ */
