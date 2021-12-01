/*
 * GNSS Lossless Compression Algorithm 
 *
 * Created: 7/6/2021 12:39:59 PM
 * Authors: Rafael Perez & Sérgio Correia
 * Instituto Politécnico de Portalegre
 *
 */ 

/*! \file OS_SD.cpp */

#include "AP.h"

// INITIALIZING JSON DOCUMENT
StaticJsonDocument<50000> doc;


// CREATING KML FORMAT
const char* xml_header = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";

const String header_file = R"=====( 
<kml xmlns="http://www.opengis.net/kml/2.2" xmlns:gx="http://www.google.com/kml/ext/2.2" xmlns:kml="http://www.opengis.net/kml/2.2" xmlns:atom="http://www.w3.org/2005/Atom">
<Document>
	<name>GPS Lossless System</name>
	<gx:CascadingStyle kml:id="__managed_style_0BD092ABFC148CBF3C8A">
		<Style>
			<IconStyle>
				<scale>1.2</scale>
				<Icon>
					<href>https://earth.google.com/earth/rpc/cc/icon?color=1976d2&amp;id=2000&amp;scale=4</href>
				</Icon>
				<hotSpot x="64" y="128" xunits="pixels" yunits="insetPixels"/>
			</IconStyle>
			<LabelStyle>
			</LabelStyle>
			<LineStyle>
				<color>ff2dc0fb</color>
				<width>6</width>
			</LineStyle>
			<PolyStyle>
				<color>40ffffff</color>
			</PolyStyle>
			<BalloonStyle>
				<displayMode>hide</displayMode>
			</BalloonStyle>
		</Style>
	</gx:CascadingStyle>
	<gx:CascadingStyle kml:id="__managed_style_10C3780B99148CBF3C89">
		<Style>
			<IconStyle>
				<Icon>
					<href>https://earth.google.com/earth/rpc/cc/icon?color=1976d2&amp;id=2000&amp;scale=4</href>
				</Icon>
				<hotSpot x="64" y="128" xunits="pixels" yunits="insetPixels"/>
			</IconStyle>
			<LabelStyle>
			</LabelStyle>
			<LineStyle>
				<color>ff2dc0fb</color>
				<width>4</width>
			</LineStyle>
			<PolyStyle>
				<color>40ffffff</color>
			</PolyStyle>
			<BalloonStyle>
				<displayMode>hide</displayMode>
			</BalloonStyle>
		</Style>
	</gx:CascadingStyle>
	<StyleMap id="__managed_style_095FDB56E3148CBF3C89">
		<Pair>
			<key>normal</key>
			<styleUrl>#__managed_style_10C3780B99148CBF3C89</styleUrl>
		</Pair>
		<Pair>
			<key>highlight</key>
			<styleUrl>#__managed_style_0BD092ABFC148CBF3C8A</styleUrl>
		</Pair>
	</StyleMap>
	<Placemark id="TESTE">
		<name>TESTE</name>
			<styleUrl>#__managed_style_095FDB56E3148CBF3C89</styleUrl>
		<LineString>
			<coordinates> )=====";

const String footer_file = R"=====(	</coordinates>
		</LineString>
	</Placemark>
</Document>
</kml>
)=====";


/*! \fn void SD_SaveRAWData(int B)
    \brief Saves RAW Data from vector into KML/JSON files
    \param B byte to choose if use KML file, JSON file or both
*/

void SD_SaveRAWData(int B){
	char timestr[10], datestr[10];
	char folder_name[10];
	char huf_name[22];
	const char *format_compact = ".huf";
		
		

	String json_data = "";

	sprintf( timestr, "%d", gps.time.value());
	sprintf( datestr, "%d", gps.date.value());
	
	strcpy(folder_name, "/");
	strcat(folder_name, datestr);					// Folder name will be the date stamp

	(!SD.exists(folder_name)) ? (SD.mkdir(datestr)) : (SERIALDEBUG.println("Directory exists."));
			

	
	/************************************************************************/
	/* KML Data Record                                                      */
	/************************************************************************/
	if (B == KML_DATA ||  B == ALL_DATA)
	{
		const char *format_file = ".kml";
		char file_name[20];
		
		strcpy(file_name, folder_name);
		strcat(file_name, "/");
		strcat(file_name, timestr);				// File name will be the time stamp + format
		strcat(file_name, format_file);
		
		
		// Initialize KML File
		File data_file = SD.open(file_name, FILE_WRITE);
		delay(100);

		if (data_file)
		{
			data_file.print(xml_header);
			data_file.print(header_file);
			
			for (int i = 0; i <= VLatitude.size()-1 ; i++)
			{
				data_file.print(VLongitude.at(i).negative ? ("-") : ("") );
				data_file.print(VLongitude.at(i).deg);
				data_file.print(".");
				data_file.print(VLongitude.at(i).billionths);
				data_file.print(",");
				data_file.print(VLatitude.at(i).negative ? ("-") : (""));
				data_file.print(VLatitude.at(i).deg);
				data_file.print(".");
				data_file.print(VLatitude.at(i).billionths);
				data_file.print(",0 ");
			}
			
			data_file.println(footer_file);
			
			SERIALDEBUG.println("KML file written.");
			} else {
			SERIALDEBUG.println("Error saving KML file.");
		}
		data_file.close();
		
	}
	
	
	/************************************************************************/
	/* JSON Data Record                                                     */
	/************************************************************************/
	if (B == JSON_DATA ||  B == ALL_DATA){
		// GPS ITERATION VARIABLES
		int posLat = 2;										// Position
		int cPL = 0;
		int pPL = 0;
		int posLng = 2;
		int cPN = 0;
		int pPN = 0;

		int degreeLat = 99;									// Degrees
		int cDL = 0;
		int pDL = 99;
		int degreeLng = 99;
		int cDN = 0;
		int pDN = 99;

		int cML = 0;										// Minutes
		int pML = 99;
		int cMN = 0;
		int pMN = 99;
		
		// STRUCTURING JSON DOCUMENT
		doc["TS"] = 0;
		doc["NS"] = 0;
		doc["FX"] = 0;
		JsonObject latArray = doc.createNestedObject("lat");
		JsonArray positionLatitude = latArray.createNestedArray("PL");
		JsonArray degreesLatitude = latArray.createNestedArray("DL");
		JsonArray minutesLatitude = latArray.createNestedArray("ML");
		JsonArray secondsLatitude = latArray.createNestedArray("SL");
		JsonObject lngArray = doc.createNestedObject("lng");
		JsonArray positionLongitude = lngArray.createNestedArray("PN");
		JsonArray degreesLongitude = lngArray.createNestedArray("DN");
		JsonArray minutesLongitude = lngArray.createNestedArray("MN");
		JsonArray secondsLongitude = lngArray.createNestedArray("SN");
		
		for (int i = 0; i <= VLatitude.size()-1 ; i++)
		{
			/************************************************************************/
			/* LATITUDE                                                             */
			/************************************************************************/
			//POSITION
				
			if (VLatitude.at(i).negative == 0)
			{
				if (posLat != pPL)
				{
					pPL = posLat;
					cPL++;
				}
			} else if (VLatitude.at(i).negative == 1)
			{
				if (posLat != pPL)
				{
					pPL = posLat;
					cPL++;
				}
			}
			
			// DEGREES
			degreeLat = VLatitude.at(i).deg;
			if (degreeLat != pDL)
			{
				pDL = degreeLat;
				cDL++;
			}
			
			// TRANSFORMATION MINUTE SECONDS
			//MINUTE
			float billLat = VLatitude.at(i).billionths;
			float dmsML = billLat * 60 / 1000000000;
			int minuteLat = (int)dmsML;
			if (minuteLat != pML)
			{
				pML = minuteLat;
				cML++;
			}
			
			/************************************************************************/
			/* LONGITUDE                                                            */
			/************************************************************************/
			//POSITION
						
			if (VLongitude.at(i).negative == 0)
			{
				if (posLng != pPN)
				{
					pPN = posLng;
					cPN++;
				}
			}
			else if (VLongitude.at(i).negative == 1)
			{
				if (posLng != pPN)
				{
					pPN = posLng;
					cPN++;
				}
			}
			
			// DEGREES
			degreeLng = VLongitude.at(i).deg;
			if (degreeLng != pDN)
			{
				pDN = degreeLng;
				cDN++;
			}
			
			// TRANSFORMATION MINUTE SECONDS
			// MINUTE
			float billLng = VLongitude.at(i).billionths;
			float dmsMN = billLng * 60 / 1000000000;
			int minuteLng = (int)dmsMN;
			if (minuteLng != pMN)
			{
				pMN = minuteLng;
				cMN++;
			}		
			
		}
		
		
		// ALL CHECKS TO PERFORM DATA PROCESSING
		
		if (cPL == 1 && cPN == 1)											// Position not changing
		{
			if (cDL == 1 && cDN == 1)										// Degree not changing
			{
				if (cML == 1 && cMN == 1)									// Minutes not changing
				{
					doc["FX"] = 3;
					VLatitude.at(0).negative  ? (positionLatitude.add(0))  : (positionLatitude.add(1)); 
					VLongitude.at(0).negative ? (positionLongitude.add(0)) : (positionLongitude.add(1));
					degreesLatitude.add(VLatitude.at(0).deg);
					degreesLongitude.add(VLongitude.at(0).deg);
					
					float billLat = VLatitude.at(0).billionths;
					float dmsML = billLat * 60 / 1000000000;
					int minuteLat = (int)dmsML;
					minutesLatitude.add(minuteLat);
					
					float billLng = VLongitude.at(0).billionths;
					float dmsMN = billLng * 60 / 1000000000;
					int minuteLng = (int)dmsMN;
					minutesLongitude.add(minuteLng);
					
					
					for (size_t i = 0; i <= VLatitude.size()-1; i++)
					{
						float billLat = VLatitude.at(i).billionths;
						float dmsML = billLat * 60 / 1000000000;
						int minuteLat = (int)dmsML;
						int secondLat = 10000 * (dmsML - minuteLat);
						secondsLatitude.add(secondLat);
						
						float billLng = VLongitude.at(i).billionths;
						float dmsMN = billLng * 60 / 1000000000;
						int minuteLng = (int)dmsMN;
						int secondLng = 10000 * (dmsMN - minuteLng);
						secondsLongitude.add(secondLng);
					}
				} else {	
					doc["FX"] = 2;
					VLatitude.at(0).negative  ? (positionLatitude.add(0))  : (positionLatitude.add(1));
					VLongitude.at(0).negative ? (positionLongitude.add(0)) : (positionLongitude.add(1));
					degreesLatitude.add(VLatitude.at(0).deg);
					degreesLongitude.add(VLongitude.at(0).deg);
				
				
					for (size_t i = 0; i <= VLatitude.size()-1; i++)
					{
						float billLat = VLatitude.at(i).billionths;
						float dmsML = billLat * 60 / 1000000000;
						int minuteLat = (int)dmsML;
						minutesLatitude.add(minuteLat);
						int secondLat = 10000 * (dmsML - minuteLat);
						secondsLatitude.add(secondLat);
					
						float billLng = VLongitude.at(i).billionths;
						float dmsMN = billLng * 60 / 1000000000;
						int minuteLng = (int)dmsMN;
						minutesLongitude.add(minuteLng);
						int secondLng = 10000 * (dmsMN - minuteLng);
						secondsLongitude.add(secondLng);
					}
				}
			} else {		
				doc["FX"] = 1;												// Position not changing
				VLatitude.at(0).negative  ? (positionLatitude.add(0))  : (positionLatitude.add(1));
				VLongitude.at(0).negative ? (positionLongitude.add(0)) : (positionLongitude.add(1));
			
				for (size_t i = 0; i <= VLatitude.size()-1; i++)
				{
					degreesLatitude.add(VLatitude.at(i).deg);
					float billLat = VLatitude.at(i).billionths;
					float dmsML = billLat * 60 / 1000000000;
					int minuteLat = (int)dmsML;
					minutesLatitude.add(minuteLat);
					int secondLat = 10000 * (dmsML - minuteLat);
					secondsLatitude.add(secondLat);
				
					degreesLongitude.add(VLongitude.at(i).deg);
					float billLng = VLongitude.at(i).billionths;
					float dmsMN = billLng * 60 / 1000000000;
					int minuteLng = (int)dmsMN;
					minutesLongitude.add(minuteLng);
					int secondLng = 10000 * (dmsMN - minuteLng);
					secondsLongitude.add(secondLng);
				}
			}
		} else {
			doc["FX"] = 0;
			for (size_t i = 0; i <= VLatitude.size()-1; i++)
			{
				VLatitude.at(i).negative  ? (positionLatitude.add(0))  : (positionLatitude.add(1));
				degreesLatitude.add(VLatitude.at(i).deg);
				float billLat = VLatitude.at(i).billionths;
				float dmsML = billLat * 60 / 1000000000;
				int minuteLat = (int)dmsML;
				minutesLatitude.add(minuteLat);
				int secondLat = 10000 * (dmsML - minuteLat);
				secondsLatitude.add(secondLat);
								
				VLongitude.at(i).negative ? (positionLongitude.add(0)) : (positionLongitude.add(1));
				degreesLongitude.add(VLongitude.at(i).deg);
				float billLng = VLongitude.at(i).billionths;
				float dmsMN = billLng * 60 / 1000000000;
				int minuteLng = (int)dmsMN;
				minutesLongitude.add(minuteLng);
				int secondLng = 10000 * (dmsMN - minuteLng);
				secondsLongitude.add(secondLng);
			}
		}
		doc["TS"] = timestr;
		doc["NS"] = VLatitude.size();
		
		serializeJson(doc, json_data);
		SERIALDEBUG.println(json_data);
		
		const char *format_file = ".jso";
		char json_name[22];
		
		strcpy(json_name, folder_name);
		strcat(json_name, "/");
		strcat(json_name, timestr);
		strcpy(huf_name, json_name);
		strcat(json_name, format_file);
		strcat(huf_name, format_compact);
		
		File json_file = SD.open(json_name, FILE_WRITE);
		delay(100);

		if (json_file)
		{
			json_file.println(json_data);	
			SERIALDEBUG.println("JSON file written.");
			} else {
			SERIALDEBUG.println("Error saving JSON file.");
		}
		json_file.close();
		
	}
	
	/*
	if (B==NO_DATA)
	{	
		// DUMMY DATA FOR TESTS
		strcpy(huf_name, folder_name);
		strcat(huf_name, "/");
		strcat(huf_name, timestr);
		strcat(huf_name, format_compact);
		json_data = "{\"TS\":\"16394200\",\"NS\":5,\"FX\":3,\"lat\":{\"PL\":[1],\"DL\":[39],\"ML\":[17],\"SL\":[2579,2584,2582,2575,2575]},\"lng\":{\"PN\":[0],\"DN\":[7],\"MN\":[25],\"SN\":[737,744,741,725,723]}}";	
	}
	*/
	CompressedSize = compress(&json_data, huf_name);	
	UnCompressedSize = json_data.length();
	
}


/*! \fn void SD_SaveData(int B)
    \brief Public function in order to call the private method of saving data files.
    \param B byte to choose if use KML file, JSON file or both
*/
void SD_SaveData(int B){
	SD_SaveRAWData(B);
}
