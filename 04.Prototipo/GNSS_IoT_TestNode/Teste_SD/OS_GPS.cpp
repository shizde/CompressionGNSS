/*
 * GNSS Lossless Compression Algorithm 
 *
 * Created: 7/6/2021 12:39:59 PM
 * Authors: Rafael Perez & Sérgio Correia
 * Instituto Politécnico de Portalegre
 *
 */ 

/*! \file OS_GPS.cpp */

#include "OpS.h"
#include "AP.h"


/*! \fn void GPS_DataCollection(void)
    \brief Validate if the GPS sensor is functioning, receives GPS data and encode it 
*/
void GPS_DataCollection(void)
{
	// GPS data collection
	while (SERIALGPS.available() > 0){
		gps.encode(SERIALGPS.read());
	}
}

/*! \fn void GPS_RefreshSTATUS(void)
    \brief Refresh GPS Status in order to validate how many satellites are reachable and update informations receveid
*/
void GPS_RefreshSTATUS(void){
	
	// ***** Date *****
	if (gps.date.isValid())								
	{
		sysStatus = setST_GPSDate;
		if (gps.date.isUpdated())
		{
			LCD_UpdateDate(gps.date.year(), gps.date.month(), gps.date.day());
		}
	}
	else
	{
		sysStatus = resetST_GPSDate;
		LCD_UpdateDate(0,0,0);
	}
	
	// ***** Time *****
	if (gps.time.isValid())								
	{
		sysStatus = setST_GPSTime;
		if (gps.time.isUpdated())
		{
			LCD_UpdateTime(gps.time.hour(), gps.time.minute(), gps.time.second());
		}
	}
	else
	{
		sysStatus = resetST_GPSTime;
		LCD_UpdateTime(0,0,0);
	}
	
	// ***** Localization *****
	(gps.location.isValid()) ? (sysStatus = setST_GPSLoc) : (sysStatus = resetST_GPSLoc);
	
	// ***** N. Satellites *****
	if (gps.satellites.isValid())
	{
		if (gps.satellites.isUpdated())
		{
			uint8_t n = gps.satellites.value();
			LCD_UpdateSat(n);
			(n>2) ? (sysStatus = setST_GPSSat) : (sysStatus = resetST_GPSSat);
		}
	}else
	{
		LCD_UpdateSat(0);
		sysStatus = resetST_GPSSat;
	}

	// ***** Global Satellite STATUS *****
	((isST_GPSSat && isST_GPSDate && isST_GPSTime && isST_GPSLoc) == 1) ? (sysStatus = setST_GPS) : (sysStatus = resetST_GPS);
	(isST_GPS == 1) ? (LCD_UpdateGPSStatus(1)) : (LCD_UpdateGPSStatus(0));
		
}