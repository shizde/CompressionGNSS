

#ifndef AP_H_
#define AP_H_

#include "OpS.h"						// Operating System Definitions

// WebServer COMMANDs
#define START	1
#define STOP	2
#define RESET	3
#define RESET	9

// State Machine STATEs
#define Idle	0						// StandBy
#define Acq		1						// Acquiring data
#define Buf		2						// Buffering data

extern char BTN_Start;
extern char BTN_Stop;
extern char BTN_Reset;


/***************************************************************************************/
/* FUNCTION Prototypes													               */
/***************************************************************************************/
unsigned long RefreshSTATUS(unsigned long c, unsigned long l);
void RefreshSTM(void);
void ProcessWebPage(void);

/*! \def ST_STM
    \brief Global variable for .
*/
/*! \def CMD
    \brief Global variable for .
*/
/*! \def WiFiServer server
    \brief Make web server variable global variable for definition and intializing.
*/
extern uint8_t ST_STM;
extern uint8_t CMD;
extern WiFiServer server;


#endif /* AP_H_ */