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
#ifdef NO_WIN32
  #define CYPRESS_API /*EMPTY*/
#else
  #define CYPRESS_API /*EMPTY*/
#endif



#ifdef __cplusplus
extern "C" {
#endif

CYPRESS_API int    Cypress_USB_Open     (void);
CYPRESS_API int    Cypress_USB_Close    (void);
CYPRESS_API int    Cypress_USB_LoadFPGA         (const char * sFilename );
CYPRESS_API int    Cypress_USB_LoadSPIoverPortA (unsigned char *SPI_data, unsigned char  length, unsigned short index);
CYPRESS_API int    Cypress_USB_LoadSPIoverGPIF  (unsigned char *SPI_data, int  length);
CYPRESS_API int    Cypress_USB_LoadSPIwaitDONE  (int  timeout_ms);
CYPRESS_API int    Cypress_USB_VendorCmd        (unsigned char  ucVendorCode, unsigned short value, unsigned short index, unsigned char * byteBuffer, int  len);
CYPRESS_API int    Cypress_USB_VendorRead       (unsigned char  ucVendorCode, unsigned short value, unsigned short index, unsigned char * byteBuffer, int *len);

CYPRESS_API int    Cypress_USB_WriteI2C (
            unsigned char   ucPhysAddress,
            unsigned char   ucInternalAddressSize,
            unsigned char * pucInternalAddress,
            unsigned char   ucDataBufferSize,
            unsigned char * pucDataBuffer );

CYPRESS_API int    Cypress_USB_ReadI2C (
            unsigned char   ucPhysAddress,
            unsigned char   ucInternalAddressSize,
            unsigned char * pucInternalAddress,
            unsigned short  usDataBufferSize,
            unsigned char * pucDataBuffer );

CYPRESS_API int    Cypress_USB_Command(char *cmd, char *text, double dval, double *retdval, char **rettxt);
CYPRESS_API int    Cypress_Configure  (char *cmd, char *text, double dval, double *retdval, char **rettxt);
CYPRESS_API int    Cypress_Cget       (char *cmd, char *text, double dval, double *retdval, char **rettxt);
CYPRESS_API char*  Cypress_Help       (void);

#ifdef __cplusplus
}
#endif
