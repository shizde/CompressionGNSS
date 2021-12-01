/*
 * GNSS Lossless Compression Algorithm 
 *
 * Created: 7/6/2021 12:39:59 PM
 * Authors: Rafael Perez & Sérgio Correia
 * Instituto Politécnico de Portalegre
 *
 */ 

/*! \file AP_GEN.cpp */

#include "AP.h"							// Application Specific Definitions

/*! unsigned long RefreshSTATUS(unsigned long c, unsigned long l)
    \brief	Refresh the system STATUS
*			Checks for the several components of the system STATUS. The function checks
*			for an interval in milliseconds to proceed with calls to the GPS and WiFi STATUS
	\param c Current milliseconds
	\param l Milliseconds corresponding to the last STATUS update
	
	\return Updated milliseconds in case of refresh, maintains last milliseconds otherwise 
*/
unsigned long RefreshSTATUS(unsigned long c, unsigned long l)
{
	unsigned long r;
	if (c - l >=intervalSTATUS) {
		WIFI_RefreshSTATUS();
		GPS_RefreshSTATUS();
		r = c;
	}else r = l;
	return r;
}

/*! void RefreshSTM(void)
    \brief	State Machine Controller
			Checks for the system STATUS. The function controls the State Machine by altering its statuses
			once the conditions for each state is fulfilled.
*/
void RefreshSTM(void){
	
	bool c1 = ST_STM==ACQ;
	bool c2 = BTN_Stop == true;
	bool c3 = VLatitude.size() >= MAXNSAMPLES-1;
	bool c4 = ST_STM == ERR;
	bool c5 = BTN_Stop == true;
	
	// State Machine Logic Control
	if (((ST_STM==IDLE) && (BTN_Start == true)) || ((ST_STM == ERR) && (isST_GPS)))
	{
		SERIALDEBUG.println("ACQUISITION STATE");
		ST_STM = ACQ;
	} else if ((c1) && ((c2) || (c3)) || ((c4) && (c5)))
	{
		SERIALDEBUG.println("BUFFERING STATE");
		ST_STM = BUF;
	} else if ((ST_STM==BUF) && (BTN_Reset == true))
	{
		SERIALDEBUG.println("IDLE STATE");
		ST_STM = IDLE;
	} else if ((ST_STM==ACQ) && (!isST_GPS))
	{
		SERIALDEBUG.println("ERROR STATE");
		ST_STM = ERR;
	}
	
	// Reset Buttons States
	
	if (BTN_Start == true)
	{
		BTN_Start = false;
	}
	if (BTN_Stop == true)
	{
		BTN_Stop = false;
	}
	if (BTN_Reset == true)
	{
		BTN_Reset= false;
	}
		
}

/*! void ActionSTM(unsigned long ACQ_currentMillis)
    \brief	State Machine Trigger
			Controls the State Machine's actions and all the methods that should be called in each state.

*/
void ActionSTM(unsigned long ACQ_currentMillis){
	bool ACQ_Condition = false;
	static long ACQ_lastMillis = 0;
	bool ACQ_CTime;
	
	if ( ACQ_currentMillis - ACQ_lastMillis > ACQ_INTERVAL){
		SERIALDEBUG.print("CUR MILS: ");
		SERIALDEBUG.print(ACQ_currentMillis);
		SERIALDEBUG.print(" | LAST MI: ");
		SERIALDEBUG.println(ACQ_lastMillis);
		ACQ_lastMillis = ACQ_currentMillis;
		ACQ_CTime = true;
	} else {
		ACQ_CTime = false;
	}
	LCD_UpdateNextTime(0);
	// IDLE State
	if (ST_STM == IDLE){
		VLatitude.clear();			// Vector Iterator RESET
		VLongitude.clear();
	} else if (ST_STM == ACQ){
		// ACQUISITION State
		LCD_UpdateNextTime(ACQ_INTERVAL + ACQ_lastMillis - ACQ_currentMillis );
		ACQ_Condition |= ACQ_CTime;
		if ((ACQ_Condition == true)&&(isST_GPS))
		{
			VLatitude.push_back(gps.location.rawLat());
			SERIALDEBUG.print("SIZE OF VECTOR: ");
			SERIALDEBUG.println(VLatitude.size());
			VLongitude.push_back(gps.location.rawLng());
		}
	} else if (ST_STM == BUF){
		
		// BUFFERING State
		if (VLatitude.size()>0){
			SD_SaveData(ALL_DATA);
		}
	
		ST_STM = IDLE;
	} else if (ST_STM == ERR){
		// ERROR State
	}
}
