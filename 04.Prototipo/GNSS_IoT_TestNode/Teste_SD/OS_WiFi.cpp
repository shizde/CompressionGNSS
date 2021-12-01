/*
 * GNSS Lossless Compression Algorithm 
 *
 * Created: 7/6/2021 12:39:59 PM
 * Authors: Rafael Perez & Sérgio Correia
 * Instituto Politécnico de Portalegre
 *
 */ 

/*! \file OS_WiFi.cpp */

#include "OpS.h"


/************************************************************************/
/* WiFi Definitions                                                     */
/************************************************************************/
char* ssid = "Shizde";
char* password = "chocolate";
//char* ssid = "NOS-71AF";
//char* password = "ET7HK7WA";
//char* ssid = "cidade";
//char* password = "KanKan123";
//char* ssid = "MEO-Glicinias";
//char* password = "97462BE4E6";



/*! \fn unsigned long WIFI_RefreshSTATUS(unsigned long c, unsigned long l)
    \brief Verify if the WiFi is connected and update status
    \param c Current time clock
    \param l Last updated time clock

*/
void WIFI_RefreshSTATUS(void)
{
	if (WiFi.status() != WL_CONNECTED)					// WiFi with 2 minutes refresh interval
	{	// NOT CONNECTED
		LCD_UpdateWIFIStatus(0);
		sysStatus = resetST_WiFi;						// Reset WiFi STATUS BIT
		SERIALDEBUG.println("WiFi Lost connection");
		WiFi.begin(ssid, password);
		while (WiFi.status() != WL_CONNECTED)			// Waits for a new connection
		{
			delay(500);
			SERIALDEBUG.print(".");
		}
		LCD_UpdateWIFIStatus(1);
		sysStatus = setST_WiFi;							// Set WiFi STATUS BIT
		SERIALDEBUG.println("");
		SERIALDEBUG.println("WiFi reconnected");
		}else 
	{	// CONNECTED
		LCD_UpdateWIFIStatus(1);
		sysStatus = setST_WiFi;							// Set WiFi STATUS BIT
	}
}