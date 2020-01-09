# Silicon labs Video Demodulators Superset code

This repository contains the SILABS_SUPERSET source code used to build DTV frontend applications using Silicon Labs DTV demodulators.

This code can be used to support any configuration using the API-controlled Silicon Labs DTV demodulators.

Refer to [<https://github.com/SiliconLabs/video_silabs_superset/blob/SILABS_SUPERSET/Si2183/Doc/USING_SILABS_SUPERSET.pdf> for details related to this code.

## Supported Silicon Labs DTV demodulators

All API-controlled single and dual DTV Demodulators are supported via the Si2183 driver

* Si2160B
* Si21602B
* Si2162B
* Si21622B
* Si2164B
* Si21642B
* Si2166D
* Si2167D
* Si21662C
* Si21672C
* Si2168C
* Si21682C
* Si2169C
* Si21692C
* Si2180
* Si21802
* Si2181
* Si21812
* Si2182
* Si21822
* Si2183
* Si21832

Currently available Silicon Labs Video Demodulators are listed in

* <https://www.silabs.com/tv-and-video/digital-tv-and-satellite-demodulators>

## Supported Silicon Labs TER tuners

The following TER Tuners are supported

* Si2124
* Si2141
* Si2144
* Si2146
* Si2147
* Si2148
* Si2151
* Si2156
* Si2157
* Si2176
* Si2177
* Si2178B

Additional TER tuners can be supported via the CUSTOM_TER wrapper

Currently available Silicon Labs Video Tuners are listed in

* <https://www.silabs.com/tv-and-video/tv-tuners>

## Supported SAT Tuners

This code supports several SAT tuners, such as

* AV2012
* AV2018
* MAX2112
* NXP20142 (refer to NXP to get the underlying driver)
* RDA5812
* RDA5815
* RDA5815S
* RDA16110
* RDA5815M
* RDA16112
* RDA5816
* RDA5816S
* RDA16110D
* RDA16110E
* RDA5816SD
* RDA16110SW

Additional SAT tuners can be supported via the CUSTOM_SAT wrapper

## (SAT) Supported LNB controllers

This code supports several LNB controllers tuners, such as

* A8293
* A8297
* A8302
* A8304
* LNBH21
* LNBH25
* LNBH26
* LNBH29

Additional LNB controllers can be supported using one of the above examples

## (SAT) Unicable support

This code supports Unicable I as well as Unicable II.

The **automatic installation phase** in Unicable II is something we can’t support, because it requires reading 5 DiSEqC bytes, and our HW only allows reading 3 DiSEqC bytes.

> This seems like a big issue, but EN 50607 (i.e. Unicable II specification) specifies that ‘The satellite receiver shall always allow to manually enter
the UB-ID and UB-frequency’ No SIFC (i.e. DiSEqC read) capability is required.
The above means that HW compatible with Unicable I can also handle Unicable II with no HW change.
