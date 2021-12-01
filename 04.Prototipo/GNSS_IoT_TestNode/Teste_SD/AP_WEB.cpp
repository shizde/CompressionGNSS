/*
 * AP_WEB.cpp
 *
 * Created: 14/08/2021 17:28:15
 *  Author: scorr
 */ 

/*! \file AP_WEB.cpp */

#include "AP.h"				// Definitions
#include "WebPage.h"		// WebPage HTML content

  
// Auxiliar variables to store the current output state
String outputStartButton = "off";
String outputStopButton = "off";
String outputResetButton = "off";
char BTN_Start = false;
char BTN_Stop = false;
char BTN_Reset = false;

/*! \brief Definition of timeout limit                                  */
#define timeoutTime	2000

/*! \brief Declaration of server initialized on port 80 (HTTP)          */
WiFiServer server(80);

/*! \fn void ProcessWebPage
    \brief Generates webclient and serves the HTML webpage 
*/
void ProcessWebPage(void){
  WiFiClient client = server.available();										 
  static unsigned long previousTime = 0;
  unsigned long	currentTime = millis();
  static String header;


  if (client) {																	 
	  previousTime = currentTime;
	  String currentLine = "";													 
	  while (client.connected() && currentTime - previousTime <= timeoutTime) {  
		  currentTime = millis();
		  if (client.available()) {												 
			  char c = client.read();											 
			  header += c;
			  if (c == '\n') {												
				  if (currentLine.length() == 0) {
					  client.flush();
					  client.println("HTTP/1.1 200 OK");
					  client.println("Content-type:text/html");
					  client.println("Connection: close");
					  
					client.println(html_init);

					client.print(html_header);
					
					// WiFi STATUS
					client.print( html_wifi1 );
					(isST_WiFi) ? (client.print( html_ON )) : (client.print( html_OFF ));
					client.print( html_wifi2 );
					
					// GPS STATUS
					client.print( html_gps1 );
					(isST_GPS) ? (client.print( html_ON )) : (client.print( html_OFF ));
					client.print( html_gps2 );	
									
					// SD Card STATUS
					client.print( html_sd1 );
					(isST_SD) ? (client.print( html_ON )) : (client.print( html_OFF ));
					client.print( html_sd2 );
					
					// Satellites STATUS
				    client.print( html_sat1 );
					(isST_GPSSat) ? (client.print( html_ON )) : (client.print( html_OFF ));
					client.print( html_sat2 );
					client.print( gps.satellites.value() );
					client.print( html_sat3 );
					
					// Localization STATUS
				    client.print( html_loc1 );
					(isST_GPSLoc) ? (client.print( html_ON )) : (client.print( html_OFF ));
					client.print( html_loc2 );
					
					// GPS Time STATUS
					client.print( html_time1 );
					(isST_GPSTime) ? (client.print( html_ON )) : (client.print( html_OFF ));
					client.print( html_time2 );
					
					// GPS Date STATUS
					client.print( html_date1 );
					(isST_GPSDate) ? (client.print( html_ON )) : (client.print( html_OFF ));
					client.print( html_date2 );		
					
					/*======== START BUTTON ============*/
					if (header.indexOf("GET /start") >= 0) {
					BTN_Start = true;
					client.print("<HEAD>");
					client.print("<meta http-equiv=\"refresh\" content=\"0;url=/\">");
					client.print("</head>");
		            }
					client.println("<div><blc><p><a href=\"/start\"><button class=\"button\">Start</button></a></p></blc>"); 

					/*======== STOP BUTTON ============*/
					if (header.indexOf("GET /stop") >= 0) {
					BTN_Stop = true;
					client.print("<HEAD>");
					client.print("<meta http-equiv=\"refresh\" content=\"0;url=/\">");
					client.print("</head>");

					} 
					client.println("<blc><p><a href=\"/stop\"><button class=\"button\">Stop</button></a></p></blc>");
						

					/*======== RESET BUTTON ============*/
					if (header.indexOf("GET /reset") >= 0) {
					BTN_Reset = true;
					client.print("<HEAD>");
					client.print("<meta http-equiv=\"refresh\" content=\"0;url=/\">");
					client.print("</head>");
					} 
					client.println("<blc><p><a href=\"/reset\"><button class=\"button\">Reset</button></a></p></blc></div>");
					
					// State Machine Status1
					client.print(html_state_machine1);
					if ( ST_STM == IDLE)
					{
						client.print(html_state_idle);
						client.print(html_state_machine2);
						client.print("IDLE");
					} else if ( ST_STM == ACQ)
					{
						client.print(html_state_acquisition);
						client.print(html_state_machine2);
						client.print("ACQUISITION");
					} else if ( ST_STM == ERR )
					{
						client.print(html_state_error);
						client.print(html_state_machine2);
						client.print("ERROR");
					} else if ( ST_STM == BUF )
					{
						client.print(html_state_buffering);
						client.print(html_state_machine2);
						client.print("BUFFERING");
					}
					
					client.print(html_state_machine3);
					
					// Number of Samples
					client.print( html_num_sample1 );
					client.print( VLatitude.size() );
					client.print( html_num_sample2 );
					
					// Original File Size
					client.print( html_ori_size1 );
					client.print( UnCompressedSize );
					client.print( html_ori_size2 );
					
					// Original File Size
					client.print( html_comp_size1  );
					client.print( CompressedSize );
					client.print( html_comp_size2  );
					
					// GPS Timer HTML
					client.print( html_footer_time_init );
					if (gps.time.hour() < 10) { client.print("0"); }
					client.print( gps.time.hour() );
					client.print(":");
					if (gps.time.minute() < 10) { client.print("0"); }
					client.print( gps.time.minute() );	
					client.print( html_footer_time_end);
					
					// GPS Date HTML
					client.print( html_footer_date_init );
					if ( gps.date.day() < 10 ) { client.print("0"); } 
					client.print( gps.date.day() );
					client.print("/");
					if ( gps.date.month() < 10 ) { client.print("0"); }
					client.print( gps.date.month() );
					client.print("/");
					client.print( gps.date.year() );
					client.print( html_footer_date_end);			  
					  
					client.print( html_closing );
					  
					  
				   // The HTTP response ends with another blank line
				   client.println();
				   // Break out of the while loop
				   break;
				  } else
				  {  
					  currentLine = "";
				  }
			  } else
			  if (c != '\r') {													
				  currentLine += c;												
			  }
		  }
	  }
	  // Clear the header variable
	  header = "";
	  // Close the connection
	  client.stop();
  }
}