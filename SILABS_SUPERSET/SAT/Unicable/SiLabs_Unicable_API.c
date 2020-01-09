/*************************************************************************************************************
Copyright 2019, Silicon Laboratories, Inc.

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
/*************************************************************************************************************/
/*                                  Silicon Laboratories                                                     */
/*                                  Broadcast Video Group                                                    */
/*                                  SiLabs API UNICABLE Functions                                            */
/*-----------------------------------------------------------------------------------------------------------*/
/*   This source code contains all SiLabs API functions for UNICABLE                                         */
/*-----------------------------------------------------------------------------------------------------------*/
/* Change log:

  As from 2019/10/30 (V2.5):
    <improvement>[unicable II/bank]
      In SiLabs_Unicable_API_Tune: setting option_bit to 1 if bank > 8 (only possible in Unicable II)

  As from 2018/06/12:
    <improvement>[unicable/install]
      In SiLabs_Unicable_API_Init: Setting initial value of unicable->inBlindScan to 0
    <improvement>[unicable/tune]
      In SiLabs_Unicable_API_Tune: reducing unicable error to 2MHz while tuning (not during blindscan, since it would spoil the FW algorithm)

  As from 2018/01/04:
    <improvement>[unicable/specification> In SiLabs_Unicable_API_send_message: Reducing 'T4+T5' delay from 50 to 30 ms to fit EN50607 timings
    <improvement>,compilation>
      In SiLabs_Unicable_API_Install_Infos: removing unused reference to i
      In SiLabs_Unicable_API_Test: removing unused reference to ret

  As from 2017/11/24:
    <compatibility>[unicable/single_LO] In SiLabs_Unicable_API_Tune: Replacing 'L band/Ku band' detection threshold to 'below C band minus a small margin'
      for compatibility with new generation of Unicable LNBs using a single LO.

  As from 2017/06/21:
    <cleanup>[unicable/install] Removing SiLabs_Unicable_API_Install function (unused) as well as all related functions, to reduce code size

  As from 2017/03/29:
    <compatibility>[compiler/warning] Changing some char* to const char* to avoid compilation warnings on some compilers
    <improvement>[unicableII/read] In SiLabs_Unicable_API_Install: (when SKIP_UNICABLE_INSTALL is not defined) using pointer to Unicable_msg[0] when reading Unicable II bytes

  As from 2016/10/04:
    <improvement>[traces/tune] Identifying Unicable I and Unicable II traces.

  As from 2016/06/16:
    <correction>[Unicable_II/Tune]
      In SiLabs_Unicable_API_Tune:
        Correcting mask for T[10:8] bits (previously 0x03, now 0x07).
          With the previous value, Unicable II tune would only work for T values between 0 and 1023(0x3ff), so between 950 and 1123 MHz.
        Updating f_unicable based on T value, to have it properly reported in the wrapper context
    <improvement>[Unicable_II/Traces]
      In SiLabs_Unicable_API_Tune:
        Adding a trace for Unicable II values
        Tracing the true SAT tuner tune value (=Fub)
    <correction>[Unicable_II/Install]
      In SiLabs_Unicable_API_Install (function generally unused):
        In calls to unicable->f_diseq_read, use &Unicable_msg (instead of &Unicable_msg);
        In a similar way as done for Unicable 1, setting the following values is sufficient to be able to tune in Unicable II mode.
        unicable->Fub_kHz = 1256000;                UB frequency, depending on Unicable II equipment
        unicable->ub = 10;                          UB number (from 0 to 31).
          Caution: In the user interface, EN50607 recommends using values from 1 to 32 for UB numbering.
                   This translates as '0 to 31' in the Unicable II tune bytes.
        unicable->Fo_kHz_low_band  =  9750000;      Local Oscillator (LO) frequency for low  band
        unicable->Fo_kHz_high_band = 10600000;      Local Oscillator (LO) frequency for high band
        unicable->installed        = 2;             To indicate 'unicable II' use
    <compatibility>[No_floats]
      In SiLabs_Unicable_API_Find_Tone_Freq (function generally unused):
        Tracing spectrum drawing time done without using floats
        tone_freq computed without using floats.

  As from 2015/07/15:
    <correction>[typo/Tune/T] In SiLabs_Unicable_API_Tune:
     Correcting the divider used in unicable->T =     (signed int) ( ( Ft - Fo + Fub )/4000 - 350 ); which had been by mistake changed to 400 due to the deletion of a '0'.

  As from 2015/06/01:
    <new_feature>[Unicable_II] Adding Unicable II (EN50607) support. Set unicable->installed to '2' for Unicable II control.
    <compatibility>[Tizen/signed_int] All 'int' variables explicitely redefined as 'signed int'. This is because 'int' for the Tizen OS means 'unsigned int',
       while it means 'signed int' for all other OSs. Using 'signed int' makes the code explicit and compatible with all known OSs.

*/
/* Older changes:

  As from 2014/11/13: removing unused start_time_ms in test functions
   In SiLabs_Unicable_API_AGC_Convergence
   In SiLabs_Unicable_API_Tone_ON_Delay
   In SiLabs_Unicable_API_Tone_Fall_Delay

  As from 2014/09/09:
   Changing all comments to C style
   Adding variable declarations to avoid compiler warnings.

  As from 2013/04/16:
   In SiLabs_Unicable_API_send_message:
    Waiting 5ms after setting the lnb voltage to 18 Volts, as the DiSEqC messages are now sent faster from the demodulators (in 'no_gap' mode)

  As from 2013/03/14:
   Replacing the f_lnb function (initially managing voltage and tone together) by f_lnb_voltage and f_lnb_tone
    This is useful for Unicable to respect the Td delay between the 18 volt level and the start of the DiSEqC message.
    It relies on additions to the API wrapper, which needs to be V2.1.7 and above.
   In SiLabs_Unicable_API_send_message:
    Replacing calls to f_lnb by calls to f_lnb_voltage
   In SiLabs_Unicable_API_Init:
    f_lnb replaced by f_lnb_voltage and f_lnb_tone
   In SiLabs_Unicable_API_Install:
    f_lnb call replaced by a call to f_lnb_voltage plus a call to f_lnb_tone

  As from 2013/03/13:
   In SiLabs_Unicable_API_send_message:
    Allowing the preparation of the Unicable message before setting the voltage at 18 volts
    This may be required for some demodulators, as the Td timing in the Unicable specification says that
     the DiSEqC message should be issued between 4 and 22 ms after the volateg is set to 18 volts.
    With some demodulators sending a DiSEqC message takes some time, so 2 new functions are added
     in the L3 wrapper code to allow the following sequence:
      1- preparation of the DiSEqC message (checking BUS availability, preparing bytes to send)
      2- setting the voltage at 18 volts
      3- triggering the DiSEqC message
    For demodulators where this is not implemented, a call to the preparation and trigger functions
     will return '0' and the usual DiSEqC function is used in this case.

  As from 2013/02/18 (SVN3452):
   In SiLabs_Unicable_API_Install:
    storing Unicable_WideBand_LO_Freqs in LO table, if used

  As from 2013/01/17 (SVN3452):
   In SiLabs_Unicable_API_Install:
    Waiting 1 second after powering the Unicable equipment, as some take some time to startup.

  As from 2013/01/04 (SVN3420):
   In SiLabs_Unicable_API_Init:
    unicable->stop_on_first_tone =        1;
   In SiLabs_Unicable_API_Tune:
    removing polarization value tracing
    removing unicable->polarization settings (already set by the application)
    Tracing SAT position, polarization and band in text
   In SiLabs_Unicable_API_Hardcoded_Tune:
    Tracing SAT position, polarization and band in text

  As from 2012/12/27 (SVN3405):
   In SiLabs_Unicable_API_send_message:
    Tracing ub, band, T from DiSEqC bytes
   In SiLabs_Unicable_API_Tune:
    Tracing polarization value
    Tracing satellite_position
   In SiLabs_Unicable_API_Hardcoded_Tune:
    Correction: taking the input 'bank' value into account.
   In SiLabs_Unicable_API_Tune_Infos:
    Tracing sat, pol, band based on bank value

  As from 2012/11/16 (SVN3302):
    Removing duplicate function prototypes (already present in SiLabs_Inicable_API.h)
    In SiLabs_Unicable_API_Test:
     Avoiding testing float using '==' operator

  As from 2012/10/29 (SVN3216):
    In SiLabs_Unicable_API_Install:
     Adding possibility to skip install, for test purposes
     (This requires proper values to be set according to the Unicable ODU in use)
      #ifdef    SKIP_UNICABLE_INSTALL
        unicable->Fub_kHz = 1076000;
        unicable->ub = 0;
        unicable->Fo_kHz_low_band  =  9750000;
        unicable->Fo_kHz_high_band = 10600000;
        unicable->installed = 1;
        return 1;
      #endif ( SKIP_UNICABLE_INSTALL )

  As from 2012/10/04 (SVN3120):
    In SiLabs_Unicable_API_Tune:
. .  unicable->bank = (unicable->satellite_position<<2) + (unicable->polarization<<1) + unicable->band;

  As from 2012/07/11:
    SiLabs_Unicable_API_voltage removed (now handled i_n 'API' mode in the wrapper)
    In SiLabs_Unicable_API_Find_Tone_Freq:
     Removed some commented lines
     Skipping 'narrow peaks'
    SiLabs_Unicable_API_Tune_Infos prototype changed to fill a text buffer

  As from 2012/06/15:
   Adding SiLabs_Unicable_API_Tones_Selection, for testing tones during development
   SiLabs_Unicable_API_Test function

 As from 2012/04/12:
   Added SiLabs_Unicable_API_Find_Tone_Freq to perform the 'fine' tone detection more accurately

   There are 2 ways to use a Unicable LNB:
    Either the LNB characteristics are already known, and they should be stored as (below is an example):
      unicable->Fub_kHz = 1210152;
      unicable->ub = 0;
      unicable->Fo_kHz_low_band  =  9750000;
      unicable->Fo_kHz_high_band = 10600000;
      And the above layers must be set to use a Unicable LNB (LNB_TYPE = UNICABLE_LNB_TYPE_UNICABLE)
    Or the Unicable parameters must be 'discovered' using SiLabs_Unicable_API_Install

    Once the Unicable install is done (or the parameters properly set), the tuning will be shared between:
     1- The Unicable LNB, which will move the desired Ku frequency as close as possible to the User Band center (Fub_kHz),
         with a 4MHz offset. This is such that the actual final frequency is in the {Fub_kHz-2MHz ; Fub_kHz+2MHz} range
     2- The SAT tuner, which will be tuned at a frequency close to Fub_kHz, with an offset to compensate the 4MHz rounding.

   In SiLabs_Unicable_API_Install:
    Unicable install performing the following steps:
    (as soon as a step fails, it returns '0' to indicate that the LNB is NOT a Unicable LNB)
      1- 'Coarse tones detection':
        a- Storing AGC values from 950 to 2150 Mhz
        b- Setting detection threshold as (min+max)/2, to be robust to tuner changes/LNB changes/Reception conditions
        c- In the stored values, detecting 'coarse tones' when level goes above threshold then below threshold
        During this step, there is no way to know if the LNB is really a Unicable LNB
      2- 'Fine tones detection': (using SiLabs_Unicable_API_Find_Tone_Freq)
        a- Checking levels around each 'coarse tone' at +/- 20MHz
        b- if left  level too close to center level, return 0 (not a Unicable LNB)
        c- if right level too close to center level, return 0 (not a Unicable LNB)
        d- set threshold as (max(left,right) + center)/2, to be robust to tuner changes/LNB changes/Reception conditions
        e- find the 'rise' frequency, moving upwards from center-10MHz
        f- find the 'fall' frequency, moving downwards from center+10MHz
        g- return (rise+fall)/2 as the 'fine tone' frequency.
      3- 'Tone checks' for each 'fine tone': (using SiLabs_Unicable_API_Check_Tone)
        a- Turn all other  tones 'off'. The tone under check should stay on, otherwise it is not a valid Unicable tone.
        b- Turn the current tone 'off'. The tone under check should disappear.
        c- Force a 'NO' reply on the current tone. The tone should disappear and be visible 20MHz higher.
        During these tests, return '0' when the first test fails.
        If all tests succeed:
         The tone under check is a valid available Unicable tone present at the center of a 'free' User Band.
         The tone frequency is the center frequency for the User band
      4- Store the center frequency of the first User Band as the one which is going to be used
        Moving forward, the first tone will be used to perform the remaining 'yes_no' checks.
      5- Check ODU configuration (as is Table 4 - Config_Nb table)
        a- browse the Config_Nb table values and check the 'yes' (tone at center) or 'no' reply (tone at center+20) of the LNB
        b- stop whenever a 'yes' is detected
        The configuration returning a 'yes' is the LNB configuration
       !!! NB: This does not appear to work with our ODU (Inverto). It is probably a 'generic Unicable' LNB. !!!
      6- Find LO frequencies for the selected UB (as is Table 5 - Local Oscillator frequency table in Standard RF)
        a- browse the Local Oscillator frequency table values and check the 'yes' (tone at center) or 'no' reply (tone at center+20) of the LNB
        b- log the corresponding Lo value whenever a 'yes' is detected.
           Store the first one in Fo_kHz_low_band, the second one in Fo_kHz_high_band
           Once 2 Lo values are retrieved, stop and return '1'
        c- If Fo_kHz_low_band > unicable->Fo_kHz_high_band, invert both values
      7- If all these steps succeeded, return '1' to indicate that the LNB is a Unicable LNB.

 As from 2012/03/20:
   Initial version

 *************************************************************************************************************/
/* TAG TAGNAME */

#include "SiLabs_Unicable_API.h"

signed int level[UNICABLE_MAX_SAMPLES];

signed int   SiLabs_Unicable_API_send_message           (SILABS_Unicable_Context *unicable, unsigned char message_length, unsigned char *message_buffer, signed int unicable_change_time)
{
  signed int i;
  signed int start_time;
  signed int diseqc_flags;
  signed int diseqc_prepared;
  signed int diseqc_sent;

  diseqc_sent = 0;

  if (unicable->trackDiseqc) {
    SiTRACE ("UNICABLE DiSEqC data : ");
    for (i=0; i<message_length; i++ ) { SiTRACE("0x%02X ", message_buffer[i]);}
    SiTRACE("\n");
    if (message_length==5) {
      SiTRACE ("UNICABLE ub %2d, bank %2d, T %4d\n", (message_buffer[UNICABLE_DATA1_INDEX]&0xE0)>>5, (message_buffer[UNICABLE_DATA1_INDEX]&0x1C)>>2, ((message_buffer[UNICABLE_DATA1_INDEX]&0x03)<<8) + message_buffer[UNICABLE_DATA2_INDEX]);
    }
  }
  start_time = system_time();
  /* Prepare the DiSEqC message as much as possible, to be able to send it within lesss than 22 ms       */
  /* If this function is not implemented for the demodulator, it will do nothing and return immediately */
  diseqc_prepared = unicable->f_diseq_prepare (unicable->callback, message_length, message_buffer, 0, 0, 0, 0, &diseqc_flags);
  if (diseqc_prepared) {
  SiTRACE("Unicable message prepared    in    %d ms. diseqc_flags 0x%0x2\n", system_time() - start_time , diseqc_flags);
  } else {
  SiTRACE("Unicable message could not be prepared (maybe not implemented)!\n");
  }

  start_time = system_time();
  /* Set LNB voltage to 18 volts, to signal a Unicable message */
  unicable->f_lnb_voltage (unicable->callback, 18);
  SiTRACE("LNB voltage set to 18 volts  after %d ms\n", system_time() - start_time );
  /* EN50494: 4 ms < td < 22 ms              */
  while (system_time() < start_time + 5) {};

  if (diseqc_prepared) {
    /* Trigger the DiSEqC message now                                            */
    /* If this function is not implemented for the demodulator, it will return 0 */
    diseqc_sent = unicable->f_diseq_trigger (unicable->callback, diseqc_flags);
  }
  /* If the trigger function is not implemented for the demodulator, use the DiSEqC write function */
  if (diseqc_sent) {
  SiTRACE("Unicable message triggered   after %d ms\n", system_time() - start_time );
  } else {
    unicable->f_diseq_write (unicable->callback, message_length, message_buffer, 0, 0, 0, 0);
  SiTRACE("Unicable message written     after %d ms\n", system_time() - start_time );
  }
  /* EN61319: each DiSEqC byte lasts 13.5 ms */
  /* EN50494: 2ms < ta < 60 ms               */
  /* EN50607: 2 ms < T4  & T4+T5 < 40 ms     */
  start_time = system_time();
  system_wait(14*message_length + 30);

  unicable->f_lnb_voltage (unicable->callback, 13);
  SiTRACE("LNB voltage set 13 volts     after %d ms\n", system_time() - start_time );

  start_time = system_time();
  /* Wait for the Unicable equipment to react */
  while (system_time() < start_time + unicable_change_time) { /* Wait for the time required by the upper layer */};

  SiTRACE("Unicable message returning   after %d ms\n", system_time() - start_time );
  return 1;
}

signed int   SiLabs_Unicable_API_Init          (SILABS_Unicable_Context *unicable,
                                                void *p_context,
                                                UNICABLE_TUNE_FUNC          tune,
                                                UNICABLE_AGC_FUNC           agc,
                                                UNICABLE_DISEQ_PREPARE_FUNC diseq_prepare,
                                                UNICABLE_DISEQ_TRIGGER_FUNC diseq_trigger,
                                                UNICABLE_DISEQ_WRITE_FUNC   diseq_write,
                                                UNICABLE_LPF_FUNC           lpf,
                                                UNICABLE_LNB_VOLTAGE_FUNC   lnb_voltage,
                                                UNICABLE_LNB_TONE_FUNC      lnb_tone
                                              )
{
  unicable->i2c = &(unicable->i2cObj);
  unicable->Fo_kHz_low_band    =        0;
  unicable->Fo_kHz_high_band   =        0;
  unicable->Fub_kHz            =        0;
  unicable->installed          =        0;
  unicable->ub                 =        0;
  unicable->bank               =        0;
  unicable->satellite_position = UNICABLE_POSITION_A;
  unicable->trackDebug         =        0;
  unicable->trackDiseqc        =        0;
  unicable->tuner_wait_ms      =       80;
  unicable->tone_on_wait_ms    =      300;
  unicable->callback           = p_context;
  unicable->f_tune             = tune;
  unicable->f_agc              = agc;
  unicable->f_diseq_prepare    = diseq_prepare;
  unicable->f_diseq_trigger    = diseq_trigger;
  unicable->f_diseq_write      = diseq_write;
  unicable->f_lpf              = lpf;
  unicable->f_lnb_voltage      = lnb_voltage;
  unicable->f_lnb_tone         = lnb_tone;
  unicable->PIN_code           = 0x00;
  unicable->inBlindScan        = 0;
  SiTRACE("UNICABLE_COMPATIBLE\n");
  SiTRACE("unicable->Fo_kHz_low_band    = %d\n", unicable->Fo_kHz_low_band    );
  SiTRACE("unicable->Fo_kHz_high_band   = %d\n", unicable->Fo_kHz_high_band   );
  SiTRACE("unicable->Fub_kHz            = %d\n", unicable->Fub_kHz            );
  SiTRACE("unicable->ub                 = %d\n", unicable->ub                 );
  SiTRACE("unicable->bank               = %d\n", unicable->bank               );
  SiTRACE("unicable->satellite_position = %d\n", unicable->satellite_position );
  return 1;
}
signed int   SiLabs_Unicable_API_Tune          (SILABS_Unicable_Context *unicable, signed int Freq_kHz)
{
  signed int Fl;
  signed int Ft;
  signed int Fo;
  signed int Fub;
  signed int f_unicable;
  signed int unicable_bytes_count;
  signed int roundingError;
  signed int correction;
  unsigned char option_bit;
  unsigned char position_bit;
  unsigned char polarity_bit;
  unsigned char band_bit;
  unsigned char Unicable_msg[5];

  SiTRACE("\nSiLabs_Unicable_API_Tune at %d\n", Freq_kHz);

  Fub = unicable->Fub_kHz;
  option_bit = 0;
  f_unicable = 0; /* To avoid compilation warning */

  if (Fub == 0) {
    SiTRACE("SiLabs_Unicable_API_Tune ERROR: Unicable Installation not done!\n");
    SiERROR("SiLabs_Unicable_API_Tune ERROR: Unicable Installation not done!\n");
    return 0;
  }
  /* If a L band frequency is provided, it means that the call comes from a demod with an L band value
     In this case, the band and polarization should not be changed
  */
  if (Freq_kHz < 3000000) { /* Limit changed to 'below C band minus a small margin' for compatibility with new generation of Unicable LNBs using a single LO */
    /* L band tuning */
    if (unicable->band == UNICABLE_HIGH_BAND) {
      Ft = Freq_kHz + unicable->Fo_kHz_high_band;
    } else {
      Ft = Freq_kHz + unicable->Fo_kHz_low_band;
    }
  } else {
    /* Ku band tuning */
    Ft = Freq_kHz;
  }

  /* When the Ku freq can be reached with the higher Lo use the higher Lo, to get a lower L Band frequency */
  /*if (Ft > 950000 + unicable->Fo_kHz_high_band) { */
  if (unicable->band == UNICABLE_HIGH_BAND) {
    Fo = unicable->Fo_kHz_high_band;
  } else {
    Fo = unicable->Fo_kHz_low_band;
  }

  Fl = Ft - Fo;

  if(unicable->installed == 1)
  {
      unicable->bank = (unicable->satellite_position<<2) + (unicable->polarization<<1) + unicable->band;
  }
  SiTRACE("unicable->bank %d: ", unicable->bank);

  if (unicable->installed == 2) {
    if (unicable->bank < 8) {
        SiTRACE("OptionA ");
        option_bit = 0;
    } else {
        SiTRACE("OptionB ");
        option_bit = 1;
    }
  }

  if ((unicable->bank & 0x4)>>2 == UNICABLE_POSITION_A) {
    SiTRACE("SatA ");
    position_bit = 0;
  } else {
    SiTRACE("SatB ");
    position_bit = 1;
  }
  if ((unicable->bank & 0x2)>>1 == UNICABLE_VERTICAL  ) {
    SiTRACE("Vertical   ");
    polarity_bit = 0;
  } else {
    SiTRACE("Horizontal ");
    polarity_bit = 1;
  }
  if ((unicable->bank & 0x1)    == UNICABLE_LOW_BAND  ) {
    SiTRACE("Low \n");
    band_bit = 0;
  } else {
    SiTRACE("High\n");
    band_bit = 1;
  }

  if (unicable->installed == 1) { /* for Unicable I  (EN50494) */
    /* Reduce rounding error from 4M to 2M (only when not in blindscan) */
    if(unicable->inBlindScan == 0) { roundingError = 2000; } else { roundingError = 0; }

    unicable->T =     (signed int) ( ( Ft - Fo + Fub + roundingError)/4000 - 350 );

    Unicable_msg[UNICABLE_FRAMING_INDEX] = UNICABLE_FRAMING;
    Unicable_msg[UNICABLE_ADDRESS_INDEX] = UNICABLE_ADDRESS;
    Unicable_msg[UNICABLE_COMMAND_INDEX] = UNICABLE_NORMAL_OPERATION;
    Unicable_msg[UNICABLE_DATA1_INDEX  ] = ((unicable->ub<<5)&0xE0) + ((unicable->bank<<2)&0x1C) + (((unicable->T)>>8)&0x03);
    Unicable_msg[UNICABLE_DATA2_INDEX  ] = ((unicable->T)&0xFF);

    unicable_bytes_count = 5;

    f_unicable  = (unicable->T + 350)*4000 - Fub;

    SiTRACE("UNICABLE I Freq_kHz %8d, Fo %8d, Fl %8d, Fku %8d, Fub_kHz %8d, sat/pol/band '%d%d%d' -> ub %d, bank %d, T = %d (0x%04x) returning at %8d \n",
          Freq_kHz,
          Fo,
          Fl,
          Ft,
          Fub,
          unicable->satellite_position,
          unicable->polarization,
          unicable->band,
          unicable->ub,
          unicable->bank,
          unicable->T,
          unicable->T,
          f_unicable
          );
  }

  if (unicable->installed == 2) { /* for Unicable II (EN50607) */
    unicable->T = (signed int) ( ( Fl/1000 - 100) );
    f_unicable  = (unicable->T + 100)*1000;

    Unicable_msg[UNICABLE_II_FRAMING_INDEX] = UNICABLE_II_ODU_CHANNEL_CHANGE;
    Unicable_msg[UNICABLE_II_DATA1_INDEX  ] = ((unicable->ub<<3)&0xF8) + ((unicable->T>>8)&0x07);
    Unicable_msg[UNICABLE_II_DATA2_INDEX  ] = ((unicable->T)&0xFF);
    Unicable_msg[UNICABLE_II_DATA3_INDEX  ] = ( (0x10) + (option_bit<<3) + (position_bit<<2) + (polarity_bit<<1) + (band_bit<<0) );

    unicable_bytes_count = 4;

    if (unicable->PIN_code != 0x00) {
      Unicable_msg[UNICABLE_II_FRAMING_INDEX] = UNICABLE_II_ODU_CHANNEL_CHANGE_PIN;
      Unicable_msg[UNICABLE_II_DATA4_INDEX  ] = unicable->PIN_code;
      unicable_bytes_count++;
    }

    SiTRACE("UNICABLE II Freq_kHz %8d, Fo %8d, Fl %8d, Fku %8d, Fub_kHz %8d, option_bit/position_bit/polarity_bit/band_bit '%d%d%d%d' -> ub %d, bank %d, T = %d (0x%04x) returning at %8d \n",
          Freq_kHz,
          Fo,
          Fl,
          Ft,
          Fub,
          option_bit,
          position_bit,
          polarity_bit,
          band_bit,
          unicable->ub,
          unicable->bank,
          unicable->T,
          unicable->T,
          f_unicable
          );
  }

  SiLabs_Unicable_API_send_message (unicable, unicable_bytes_count, Unicable_msg, unicable->tone_on_wait_ms);
  correction = 0;
  SiTRACE("unicable->inBlindScan =%d\n", unicable->inBlindScan);
  if((unicable->inBlindScan == 0) && (unicable->installed == 1)){
    correction = ( Ft  - Fo + Fub )  - (unicable->T + 350)*4000;
  }
  SiTRACE("UNICABLE rounding correction applied = %8d kHz, T = %d\n", correction, unicable->T);

/*  UNICABLE_TRACES("UNICABLE tuning SAT tuner at  %8d \n", Fub); */
  unicable->f_tune (unicable->callback, Fub);
  unicable->sat_tuner_freq = f_unicable;

  system_wait(50);

  return f_unicable;
}
signed int   SiLabs_Unicable_API_Hardcoded_Tune(SILABS_Unicable_Context *unicable, signed int bank, signed int T, signed int Freq_kHz)
{
  unsigned char Unicable_msg[5];

  SiTRACE("Hardcoded_Tune bank %d T %d Freq_kHz %d \n", bank, T, Freq_kHz);

  Unicable_msg[UNICABLE_FRAMING_INDEX] = UNICABLE_FRAMING;
  Unicable_msg[UNICABLE_ADDRESS_INDEX] = UNICABLE_ADDRESS;
  Unicable_msg[UNICABLE_COMMAND_INDEX] = UNICABLE_NORMAL_OPERATION;
  Unicable_msg[UNICABLE_DATA1_INDEX  ] = ((unicable->ub<<5)&0xE0) + ((bank<<2)&0x1C) + ((T>>8)&0x03);
  Unicable_msg[UNICABLE_DATA2_INDEX  ] = T&0xFF;

  SiLabs_Unicable_API_send_message (unicable, 5, Unicable_msg, unicable->tone_on_wait_ms);

  if (unicable->band == UNICABLE_HIGH_BAND) {
    UNICABLE_TRACES(" Ft %8d\n", (T+350)*4000 - unicable->Fub_kHz + unicable->Fo_kHz_high_band);
  } else {
    UNICABLE_TRACES(" Ft %8d\n", (T+350)*4000 - unicable->Fub_kHz + unicable->Fo_kHz_low_band );
  }

  unicable->f_tune (unicable->callback, Freq_kHz);
  unicable->sat_tuner_freq = Freq_kHz;
  unicable->T    = T;
  unicable->bank = bank;

  system_wait(50);

  return Freq_kHz;
}
char *SiLabs_Unicable_API_Tune_Infos           (SILABS_Unicable_Context *unicable, char *textBuffer)
{
  sprintf(textBuffer, " Unicable ub %d, bank %d (", unicable->ub, unicable->bank);
  if ((unicable->bank & 0x4)>>2 == UNICABLE_POSITION_A) {
    sprintf(textBuffer, "%s SatA", textBuffer);
  } else {
    sprintf(textBuffer, "%s SatB", textBuffer);
  }
  if ((unicable->bank & 0x2)>>1 == UNICABLE_VERTICAL) {
    sprintf(textBuffer, "%s Vertical", textBuffer);
  } else {
    sprintf(textBuffer, "%s Horizontal", textBuffer);
  }
  if ((unicable->bank & 0x1)   == UNICABLE_LOW_BAND) {
    sprintf(textBuffer, "%s Low ), ", textBuffer);
  } else {
    sprintf(textBuffer, "%s High), ", textBuffer);
  }
  sprintf(textBuffer, "%s T %d, Freq_kHz %d\n", textBuffer, unicable->T, unicable->sat_tuner_freq);
  return textBuffer;
}
char *SiLabs_Unicable_API_Install_Infos        (SILABS_Unicable_Context *unicable, char *textBuffer)
{
  sprintf(textBuffer, "\n");
  sprintf(textBuffer, "%s unicable->installed %d\n"     , textBuffer, unicable->installed);
  sprintf(textBuffer, "%s using ub      %d\n"           , textBuffer, unicable->ub);
  sprintf(textBuffer, "%s Fub_kHz       %d\n"           , textBuffer, unicable->Fub_kHz);
  sprintf(textBuffer, "%s Low  band FO for ub %d %10d\n", textBuffer, unicable->ub, unicable->Fo_kHz_low_band );
  sprintf(textBuffer, "%s High band FO for ub %d %10d\n", textBuffer, unicable->ub, unicable->Fo_kHz_high_band);

  return textBuffer;
}
#ifdef    SILABS_API_TEST_PIPE
/************************************************************************************************************************
  SiLabs_Unicable_API_Test function
  Use:        Generic test pipe function
              Used to send a generic command to the unicable code.
  Returns:    0 if the command is unknow, 1 otherwise
  Porting:    Mostly used for debug during sw development.
************************************************************************************************************************/
signed int   SiLabs_Unicable_API_Test          (SILABS_Unicable_Context *unicable, const char *target, const char *cmd, const char *sub_cmd, double dval, double *retdval, char **rettxt)
{
  unicable = unicable; /* To avoid compiler warning if not used */
  target   = target;   /* To avoid compiler warning if not used */
  cmd      = cmd;      /* To avoid compiler warning if not used */
  sub_cmd  = sub_cmd;  /* To avoid compiler warning if not used */
  dval     = dval;     /* To avoid compiler warning if not used */
  *retdval = 0;
       if (strcmp_nocase(cmd, "help"               ) == 0) {
    sprintf(*rettxt, "\n Possible Unicable test commands:\n\
tones <-1, 0-255>\n\
stop_on_first_tone [<0,1>]\n\
install_infos\n\
Fo_kHz_low_band    [LO freq in kHz]\n\
Fo_kHz_low_band    [LO freq in kHz]\n\
ub                 [<0,8>]\n\
Fub_kHz            [UB freq in kHz]\n\
"); return 1;
  }
  else if (strcmp_nocase(cmd, "install_infos"      ) == 0) {
    SiLabs_Unicable_API_Install_Infos(unicable, *rettxt);
    *retdval = unicable->installed;
    return 1;
  }
  else if (strcmp_nocase(cmd, "installed"          ) == 0) {
    unicable->installed = (signed int)dval;
    *retdval = unicable->installed;
    sprintf(*rettxt,"Unicable  unicable->installed %d\n", unicable->installed);
    return 1;
  }
  else if (strcmp_nocase(cmd, "ub"                 ) == 0) {
    unicable->ub = (signed int)dval;
    *retdval = unicable->ub;
    sprintf(*rettxt,"Unicable  unicable->ub %d\n", unicable->ub);
    return 1;
  }
  else if (strcmp_nocase(cmd, "Fub_kHz"            ) == 0) {
    unicable->Fub_kHz = (signed int)dval;
    *retdval = unicable->Fub_kHz;
    sprintf(*rettxt,"Unicable  unicable->Fub_kHz %d kHz\n", unicable->Fub_kHz);
    return 1;
  }
  else if (strcmp_nocase(cmd, "Fo_kHz_low_band"    ) == 0) {
    unicable->Fo_kHz_low_band = (signed int)dval;
    *retdval = unicable->Fo_kHz_low_band;
    sprintf(*rettxt,"Unicable  unicable->Fo_kHz_low_band %d kHz\n", unicable->Fo_kHz_low_band);
    return 1;
  }
  else if (strcmp_nocase(cmd, "Fo_kHz_high_band"   ) == 0) {
    unicable->Fo_kHz_high_band = (signed int)dval;
    *retdval = unicable->Fo_kHz_high_band;
    sprintf(*rettxt,"Unicable  unicable->Fo_kHz_high_band %d kHz\n", unicable->Fo_kHz_high_band);
    return 1;
  }
  else if (strcmp_nocase(cmd, "trackDebug"         ) == 0) {
    if ( (signed int)dval == 0 ) unicable->trackDebug = 0;
    if ( (signed int)dval == 1 ) unicable->trackDebug = 1;
    *retdval =  (signed int)unicable->trackDebug;
    sprintf(*rettxt,"Unicable  trackDebug %d\n", unicable->trackDebug);
    return 1;
  }
  else if (strcmp_nocase(cmd, "trackDiseqc"        ) == 0) {
    if ( (signed int)dval == 0 ) unicable->trackDiseqc = 0;
    if ( (signed int)dval == 1 ) unicable->trackDiseqc = 1;
    *retdval =  (signed int)unicable->trackDiseqc;
    sprintf(*rettxt,"Unicable  trackDiseqc %d\n", unicable->trackDiseqc);
    return 1;
  }
  return 0;
}
#endif /* SILABS_API_TEST_PIPE */
