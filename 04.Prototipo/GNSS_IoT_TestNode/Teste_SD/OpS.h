/*
 * GNSS Lossless Compression Algorithm 
 *
 * Created: 7/6/2021 12:39:59 PM
 * Authors: Rafael Perez & Sérgio Correia
 * Instituto Politécnico de Portalegre
 *
 */ 

/*! \file OpS.h */


#ifndef OS_H_
#define OS_H_

/***************************************************************************************/
/* External Libraries										                           */
/***************************************************************************************/

#include <SPI.h>
#include <Adafruit_GFX.h>							// Core graphics library
#include <Adafruit_ST7789.h>						// Hardware-specific library for ST7789
#include <mySD.h>									// SD Card
#include <TinyGPS++.h>								// GPS NEO-7M
#include <ArduinoJson.h>							// ArduinoJson
#include <Vector.h>									// Vectors
#include <WiFi.h>									// WiFi

/***************************************************************************************/
/* DEBUG Definitions											                       */
/***************************************************************************************/
/*! \def DEBUG_BAUD 
    \brief The baud rate for Serial Monitor.
*/
/*! \def SERIALDEBUG
    \brief Specify the serial port in use for Serial Monitor.
*/
#define		DEBUG_BAUD	115200
#define		SERIALDEBUG	Serial

#define		ST77XX_LIME 0x07E0

/***************************************************************************************/
/* TFT Definitions											                           */
/***************************************************************************************/
/*! \def TFT_CS
    \brief Chip Selector for TFT Module. As it is not necessary, setted as \a -1 .
*/
/*! \def TFT_DC
    \brief Data/Command pin for TFT Module. Pin used: \a 2 .
*/
/*! \def TFT_RST
    \brief Reset pin for TFT Module. Pin used: \a 4 .
*/
/*! \def TFT_WIDTH
    \brief Value for TFT screen width. Value: \a 240 .
*/
/*! \def TFT_HEIGHT
    \brief Value for TFT screen height. Value: \a 240 .
*/


#define TFT_CS		-1			// define chip select pin
#define TFT_DC		 2			// define data/command pin
#define TFT_RST		 4			// define reset pin, or se
#define	TFT_WIDTH	240
#define	TFT_HEIGHT	240

/***************************************************************************************/
/* SD Card															                   */
/***************************************************************************************/
/*! \def SD_SS
    \brief Slave Select pin used for SD Card. Pin used: \a 5 .
*/
/*! \def SD_CLK
    \brief Clock pin for SD Card. Pin used: \a 21 .
*/
/*! \def SD_MISO
    \brief Master Input/Slave Output pin for SD Card. Pin used: \a 19 .
*/
/*! \def SD_MOSI
    \brief Master Output /Slave Input pin for SD Card. Pin used: \a 22 .
*/
/*! \def SD_FILE
    \brief Name of SD Card file for storing data.
*/
#define		SD_SS		5
#define		SD_CLK		21
#define		SD_MISO		19
#define		SD_MOSI		22
#define		SD_FILE		"/InitTest.txt"

/***************************************************************************************/
/* GPS Definitions										                               */
/***************************************************************************************/
/*! \def GPS_BAUD
    \brief Baud rate used for GPS Serial.
*/
/*! \def SERIALGPS
    \brief Serial in use for GPS.
*/
/*! \def SAMPLES
    \brief Max of samples accepted per file.
*/
#define		GPS_BAUD	9600
#define		SERIALGPS	Serial2
//#define		SAMPLES		30

/***************************************************************************************/
/* GLOBAL Variable Declaration					                                       */
/***************************************************************************************/
extern Adafruit_ST7789 tft;							// Adafruit TFT class for ST7789
extern char* ssid;									// WiFi Credencials 
extern char* password;
extern TinyGPSPlus gps;								// TinyGPS class for data processing
extern uint16_t sysStatus;							// Global STATUS Word
extern uint8_t sysError;
extern int CompressedSize;							// Compressed Size data for LCD update
extern int UnCompressedSize;						// un-Compressed Size data for LCD update

/***************************************************************************************/
/* Status WORD								                                           */
/***************************************************************************************/
/*! \def stGPS
    \brief Error status word.
*/
/*! \def stGPSDate
    \brief Error status word.
*/
/*! \def stGPSTime
    \brief Error status word.
*/
/*! \def stGPSLoc
    \brief Error status word.
*/
/*! \def stGPSSat
    \brief Error status word.
*/
/*! \def setSTGPSDate
    \brief Error status word.
*/
/*! \def resetSTGPSDate
    \brief Error status word.
*/
/*! \def setSTGPSTime
    \brief Error status word.
*/
/*! \def resetSTGPSTime
    \brief Error status word.
*/
/*! \def setSTGPSLoc
    \brief Error status word.
*/
/*! \def resetSTGPSLoc
    \brief Error status word.
*/
/*! \def setSTGPSSat
    \brief Error status word.
*/
/*! \def resetSTGPSSat
    \brief Error status word.
*/
/*! \def intervalSTATUS
    \brief Time interval between connections.
*/


#define intervalSTATUS	1000

#define isST_SD			((sysStatus & 0b0001000000000000) >> 12)
#define setST_SD		(sysStatus |  0b0001000000000000)
#define resetST_SD		(sysStatus & ~0b0001000000000000)

#define isST_WiFi		((sysStatus & 0b0000000010000000) >> 7)
#define setST_WiFi		(sysStatus |  0b0000000010000000)
#define resetST_WiFi 	(sysStatus & ~0b0000000010000000)

#define isST_GPS		((sysStatus & 0b0000000001000000) >> 6)
#define setST_GPS		(sysStatus |  0b0000000001000000)
#define resetST_GPS		(sysStatus & ~0b0000000001000000)

#define isST_GPSSat		((sysStatus & 0b0000000000001000) >> 3)
#define setST_GPSSat	(sysStatus |  0b0000000000001000)
#define resetST_GPSSat	(sysStatus & ~0b0000000000001000)

#define isST_GPSLoc		((sysStatus & 0b0000000000000100) >> 2)
#define setST_GPSLoc	(sysStatus |  0b0000000000000100)
#define resetST_GPSLoc	(sysStatus & ~0b0000000000000100)

#define isST_GPSTime	((sysStatus & 0b0000000000000010) >> 1)
#define setST_GPSTime	(sysStatus |  0b0000000000000010)
#define resetST_GPSTime	(sysStatus & ~0b0000000000000010)

#define isST_GPSDate	((sysStatus & 0b0000000000000001) >> 0)
#define setST_GPSDate	(sysStatus |  0b0000000000000001)
#define resetST_GPSDate	(sysStatus & ~0b0000000000000001)

/***************************************************************************************/
/* FUNCTION Prototypes													               */
/***************************************************************************************/
void LCD_Inic(void);								// LCD Initialization
void LCD_Backgroud(void);							// Draw  the screen background
void LCD_UpdateStatus(int);
void LCD_UpdateSamples(int);						// Updates the no. samples value
void LCD_UpdateNextTime(int);						// Time to the next acquisition 
void LCD_UpdateOriSize(int);						// Original size (NO compression)
void LCD_UpdateCompSize(int);						// Compressed data size
void LCD_UpdateDate(uint16_t, uint8_t, uint8_t);	// Updates footer data
void LCD_UpdateTime(uint8_t, uint8_t, uint8_t);		// Updates footer time
void LCD_UpdateSat(uint8_t s);						// Update no. of visible satellites
void LCD_UpdateWIFIStatus(uint8_t s);
void LCD_UpdateSDStatus(uint8_t s);
void LCD_UpdateGPSStatus(uint8_t s);
void LCD_UpdateCompression(int, int);				// Sizes of compressed and un-compressed data

void WIFI_RefreshSTATUS(void);

void GPS_DataCollection(void);
void GPS_RefreshSTATUS(void);

void SD_SaveData(int B);


#endif /* OS_H_ */



	
