/*
 * GNSS Lossless Compression Algorithm 
 *
 * Created: 7/6/2021 12:39:59 PM
 * Authors: Rafael Perez & Sérgio Correia
 * Instituto Politécnico de Portalegre
 *
 */ 

/*! \file AP.h */

#ifndef AP_H_
#define AP_H_

#include "OpS.h"						// Operating System Definitions

/***************************************************************************************/
/* ACQUIRING Definitions											                   */
/***************************************************************************************/
/*! \def ACQ_INTERVAL 
    \brief Time in milliseconds between each sample
*/
/*! \def MAXNSAMPLES
    \brief Maximum number of samples for each analysis.
*/
#define		ACQ_INTERVAL	5000
#define		MAXNSAMPLES		1024
typedef RawDegrees GPS_Data;

extern Vector<GPS_Data> VLatitude;
extern Vector<GPS_Data> VLongitude;

/***************************************************************************************/
/* MACHINE STATES Definitions											               */
/***************************************************************************************/
/*! \def IDLE 
    \brief Initial state. Waits for input to try to acquire samples.
*/
/*! \def ACQ
    \brief Acquiring state. If All components are functioning well and there is GPS Data available, acquires GPS data.
*/
/*! \def BUF
    \brief Buffering state. Once the process of acquiring is finished, in this state the data is stored and analyzed. 
*/
/*! \def ERR
    \brief Error state. When there is any anmaly during the process.
*/
#define IDLE	0						// StandBy STATE
#define ACQ		1						// Acquiring data STATE
#define BUF		2						// Buffering data STATE
#define ERR		9						// Error STATE

/***************************************************************************************/
/* Buffering Definitions															   */
/***************************************************************************************/
/*! \def KML_DATA 
    \brief During the Buffering state, only KML data is generated.
*/
/*! \def JSON_DATA
    \brief During the Buffering state, only JSON data is generated.
*/
/*! \def ALL_DATA
    \brief During the Buffering state, both KML and JSON data are generated. 
*/
/*! \def NO_DATA
    \brief During the Buffering state, no data is generated.
*/

#define KML_DATA	0					// Save only KML Data
#define JSON_DATA	1					// Save only JSON Data
#define ALL_DATA	2					// Save both KML & JSON Data
#define NO_DATA		9					// Does not perform anything


/***************************************************************************************/
/* MACHINE STATES Definitions											               */
/***************************************************************************************/
/*! \def BTN_Start 
    \brief Button presented on the Webpage. 
		   Initializes the ACQUIRING STATE.
*/
/*! \def BTN_Stop
    \brief Button presented on the Webpage. 
		   Stops the ACQUIRING STATE.
		   Initializes the BUFFERING STATE.
*/
/*! \def BTN_Reset
    \brief Button presented on the Webpage.
		   Resets process once there is any problem. 
*/
extern char BTN_Start;					// Web page START button
extern char BTN_Stop;					// Web page STOP button
extern char BTN_Reset;					// Web page RESET button

// Compression Constants
#define NUM_CHAR 256


/***************************************************************************************/
/* FUNCTION Prototypes													               */
/***************************************************************************************/
unsigned long RefreshSTATUS(unsigned long c, unsigned long l);
void RefreshSTM(void);
void ActionSTM(unsigned long currentMillis);
void ProcessWebPage(void);

int compress(String* dataset, char* huffman_name);


/*! \def ST_STM
    \brief Global variable for State Machine.
*/
/*! \def WiFiServer server
    \brief Make web server variable global variable for definition and intializing.
*/
extern uint8_t ST_STM;
extern WiFiServer server;


#endif /* AP_H_ */