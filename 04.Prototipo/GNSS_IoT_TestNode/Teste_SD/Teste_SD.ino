/*
 * GNSS Lossless Compression Algorithm 
 *
 * Created: 7/6/2021 12:39:59 PM
 * Authors: Rafael Perez & Sérgio Correia
 * Instituto Politécnico de Portalegre
 *
 */ 

/*! \file Teste_SD.ino */
#include "OpS.h"						// Operating System Definitions
#include "AP.h"							// Application Specific Definitions


/************************************************************************/
/* Custom Objects                                                       */
/************************************************************************/
/*! \brief GPS variable initialization                                  */
TinyGPSPlus gps;
/*! \brief System Error                                                 */
uint16_t sysStatus = 0;
/*! \brief System Status                                                */
uint8_t sysError = 0;
unsigned long lastSTATUS;						// millis of the last STATUS Update
uint8_t ST_STM = IDLE;

/*! \brief Vectors to Receive GNSS Data and Data Type                   */
Vector<GPS_Data> VLatitude;
Vector<GPS_Data> VLongitude;
GPS_Data ALatitude[MAXNSAMPLES];
GPS_Data ALongitude[MAXNSAMPLES];

/*! \brief Size of Files generated                                      */
int CompressedSize;
int UnCompressedSize;


void setup()
{
	//Serial DEBUG
	SERIALDEBUG.begin(DEBUG_BAUD);
		
	//Serial Debugger Header	
	SERIALDEBUG.println("*** IoT Test Node ***");
	
	//TFT Initialization 
	SERIALDEBUG.println("ST7789 LCD Controller");
	SERIALDEBUG.println("240x240 1.8\"");
	SERIALDEBUG.println("");
	SERIALDEBUG.println("TFT Initializing...");	
	LCD_Inic();
	SERIALDEBUG.println("TFT OK");	
	SERIALDEBUG.println("");
	LCD_Backgroud();
	
	//Initialize GLOBAL STATUS
	LCD_UpdateStatus(0);
		
	// SD CARD Initialization
	SERIALDEBUG.print("SD Initializing...");
	while (!SD.begin(SD_SS, SD_MOSI, SD_MISO, SD_CLK))
	{
		SERIALDEBUG.print(".");
		delay(500);
		sysStatus = resetST_SD;
	}
	SERIALDEBUG.println(".");
	SERIALDEBUG.println("SD Card initialized.");
	SERIALDEBUG.println("");
	LCD_UpdateSDStatus(1);
	sysStatus = setST_SD;
	
	// WiFi Initialization
	SERIALDEBUG.print("WiFi Initializing...");
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		SERIALDEBUG.print(".");
	}
	SERIALDEBUG.println(".");
	SERIALDEBUG.print("WiFi connected to "); SERIALDEBUG.println(ssid);
	SERIALDEBUG.print("IP address: "); SERIALDEBUG.println(WiFi.localIP());
	long rssi = WiFi.RSSI();
	SERIALDEBUG.print("RSSI:"); SERIALDEBUG.print(rssi); SERIALDEBUG.println(" dBm");
	WiFi.setAutoReconnect(true);
	WiFi.persistent(true);
	  
	LCD_UpdateWIFIStatus(1);
	sysStatus = setST_WiFi;							// Set WiFi STATUS BIT
	
	//GPS Initialization
	SERIALGPS.begin(GPS_BAUD, SERIAL_8N1);		
	LCD_UpdateDate(0,0,0);
	LCD_UpdateTime(0,0,0);
	LCD_UpdateSat(0);		
		
	lastSTATUS = millis();	
	
	server.begin();
	
	VLatitude.setStorage(ALatitude);
	VLongitude.setStorage(ALongitude);

}



void loop()
{
	// Update GPS Data
	GPS_DataCollection();
	
	StaticJsonDocument<4500> doc;
	
	// Refresh WiFi STATUS
	unsigned long currentMillis = millis();
	lastSTATUS = RefreshSTATUS(currentMillis,lastSTATUS);
	
	// ************************* Updates ERROR Condition
	sysError = !(isST_GPS && isST_WiFi && isST_SD); 

	// WebPage (HTPP Request)
	ProcessWebPage();
	
	
	// State Machine Engine
	RefreshSTM();
	
	// State Machine Clock
	ActionSTM(currentMillis);
	
	// Update Informations on LCD
	LCD_UpdateStatus(ST_STM);									// State Machine Status
	LCD_UpdateSamples(VLatitude.size());						// Current Number of Samples
	LCD_UpdateCompression(UnCompressedSize, CompressedSize);	// Size of Files generated
	
	delay(100);
}
