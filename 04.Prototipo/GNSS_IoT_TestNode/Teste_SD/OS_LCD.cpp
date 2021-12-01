/*
 * GNSS Lossless Compression Algorithm 
 *
 * Created: 7/6/2021 12:39:59 PM
 * Authors: Rafael Perez & Sérgio Correia
 * Instituto Politécnico de Portalegre
 *
 */ 

/*! \file OS_LCD.cpp */

#include "OpS.h"
#include "BMP.h"

/************************************************************************/
/* GLOBAL Variable Definition                                           */
/************************************************************************/
/*! \brief TFT variable initialization                                  */
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

/************************************************************************/
/* Private Functions		                                            */
/************************************************************************/

/*! \fn void LCD_TextBox(int X, int Y, int W, int H, int V, char* L,char B)
    \brief Writes display text box and writes on it
    \param X x coordinate to begin the Text Box 
    \param Y y coordinate to begin the Text Box 
    \param W width of Text Box
	\param H height of Text Box
	\param V text to be written on the box
	\param L header text to define the type of information of the box 
	\param B background variable in order to define if it is necessary printing the whole set of box or just the text information
*/
void LCD_TextBox(int X, int Y, int W, int H, int V, char* L,char B)
{
	if (B==1)						// Default Backgroud
	{
		//Outline
		tft.drawRect(X,Y,W,H,ST77XX_BLUE);
		tft.drawRect(X+1,Y+1,W-2,H-2,ST77XX_BLUE);
		//Header
		tft.setTextColor(ST77XX_WHITE);
		tft.fillRect(X,Y,W,10,ST77XX_BLUE);
		tft.setTextSize(1);
		tft.setCursor(X+5,Y);
		tft.print(L);
		// Backgroud
		tft.fillRect(X+2,Y+10,W-5,H-2-10,ST77XX_BLACK);
	} else if ( B == 2)				// Text properties for Number of Samples
	{
		//Value
		tft.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
		tft.setCursor(X+15,Y+15);
		tft.setTextSize(3);
		tft.print(V);
	} else{							// Default text properties
		//Value
		tft.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
		tft.setCursor(X+45,Y+15);
		tft.setTextSize(4);
		tft.print(V);
	}
}

/*! \fn void LCD_GraphBox(int X,int Y,int W,int H, int S)
    \brief Draws ON/OFF indication box
    \param X x coordinate to begin the Graph Box 
    \param Y y coordinate to begin the Graph Box 
    \param W width of box
	\param H height of box
	\param S status variable to display current status (ON/OFF)
*/
void LCD_GraphBox(int X,int Y,int W,int H, int S)
{
		char *txt;
		uint16_t bC;
		uint16_t tC;
		char dx;
		
		//Outline
		tft.drawRect(X,Y,W,H,ST77XX_BLUE);
		tft.drawRect(X+1,Y+1,W-2,H-2,ST77XX_BLUE);

		if (S == 0)
		{
			txt = "IDL";
			bC = ST77XX_GREEN;
			tC = ST77XX_WHITE;
			dx = 18;
		} else if (S == 1){
			txt = "ACQ";
			bC = ST77XX_LIME;
			tC = ST77XX_WHITE;
			dx = 18;
		} else if (S == 2){
			txt = "BUF";
			bC = ST77XX_MAGENTA;
			tC = ST77XX_WHITE;
			dx = 18;
		} else if (S == 9){
			txt = "ERR";
			bC = ST77XX_RED;
			tC = ST77XX_WHITE;
			dx = 18;
		}	
		
	    // Display current status
		tft.setTextSize(4);
		tft.setTextColor(tC);
		tft.fillRect(X+2,Y+2,W-4,H-4,bC);
		tft.setCursor(X+dx,Y+10);
		tft.print(txt);
	
};


/*! \fn void LCD_Text(int X, int Y, char* T)
    \brief Write text on display
    \param X x coordinate to begin the text 
    \param Y y coordinate to begin the text
	\param T text to be written on display
*/
void LCD_Text(int X, int Y, char* T)
{
	tft.setCursor(X,Y);
	tft.setTextSize(2);
	tft.setTextColor(ST77XX_WHITE,ST77XX_BLUE);
	tft.print(T);
}

/************************************************************************/
/* Public Functions			                                            */
/************************************************************************/


/*! \fn void LCD_Text(int X, int Y, char* T)
    \brief LCD Initialization
*/
void LCD_Inic(void)
{
	tft.init(TFT_WIDTH,TFT_HEIGHT,SPI_MODE2);
	tft.setRotation(0);								// Display orientation
	tft.fillScreen(ST77XX_BLACK);					// Display default background
	tft.setTextColor(ST77XX_WHITE);					// Display default text color
	tft.setTextWrap(false);							// Do not wrap text -> Let text go "out of the screen". Do not enter new line
}


/*! \fn void LCD_Cross(int X, int Y, int W, int H)
    \brief Draws cross to indicate NOT Status
    \param X x coordinate to start drawing the cross
    \param Y y coordinate to start drawing the cross
    \param W width of cross
	\param H height of cross
*/
void LCD_Cross(int X, int Y, int W, int H)
{
	// Line "\"
	tft.writeLine(X  ,  Y,  X+W,  Y+H,ST77XX_RED);		// Main diagonal
	tft.writeLine(X+1,  Y,  X+W,Y+H-1,ST77XX_RED);		// Diagonal 1 pixel parallel to the right to main diagonal - thickens the line
	tft.writeLine(X  ,Y+1,X+W-1,  Y+H,ST77XX_RED);		// Diagonal 1 pixel parallel below main diagonal - thickens the line
	tft.writeLine(X+2,  Y,  X+W,Y+H-2,ST77XX_RED);		// Diagonal 2 pixels parallel to the right to main diagonal - thickens the line
	tft.writeLine(X  ,Y+2,X+W-2,  Y+H,ST77XX_RED);		// Diagonal 2 pixels parallel below main diagonal - thickens the line
	// Line "/"
	tft.writeLine(X+W  ,  Y,  X,  Y+H,ST77XX_RED);		// Main diagonal
	tft.writeLine(X+W-1,  Y,  X,Y+H-1,ST77XX_RED);		// Diagonal 1 pixel parallel to the left to main diagonal - thickens the line
	tft.writeLine(X+W  ,Y+1,X+1,  Y+H,ST77XX_RED);		// Diagonal 1 pixel parallel below main diagonal - thickens the line
	tft.writeLine(X+W-2,  Y,  X,Y+H-2,ST77XX_RED);		// Diagonal 2 pixels parallel to the left to main diagonal - thickens the line
	tft.writeLine(X+W  ,Y+2,X+2  ,Y+H,ST77XX_RED);		// Diagonal 2 pixels parallel below main diagonal - thickens the line
}


/*! \fn void LCD_Backgroud(void)
    \brief Draw  the screen background and visual components that remain static due all functioning of the system
*/
void LCD_Backgroud(void)
{
	// Header
	tft.fillRect(0,0,TFT_WIDTH,25,ST77XX_BLUE);
	tft.setCursor(40,5);
	tft.setTextSize(2);
	tft.print("IoT Test Node");
	// brief Delimiters 
	tft.drawFastHLine(0, 85,TFT_WIDTH,ST77XX_BLUE);
	tft.drawFastHLine(0,145,TFT_WIDTH,ST77XX_BLUE);
	// brief Footer 
	tft.fillRect(0,215,TFT_WIDTH,25,ST77XX_BLUE);
	// brief Text Boxes
	LCD_TextBox(125,90,100,50, 10,"Samples",1);					// Number of Samples
	LCD_TextBox( 15,90,100,50, 10,"Next Sample",1);				// Time to next sample
	LCD_TextBox(125,150,100,50,10,"Compressed Size",1);			// Original size
	LCD_TextBox( 15,150,100,50,10,"Original Size",1);			// Compressed size
	// brief Text Satellite 
	tft.fillRect(223,58,16,20,ST77XX_BLUE);						// Blue box to display number of satellites currently reachable
	// brief Images STATUS
	LCD_UpdateWIFIStatus(0);
	LCD_UpdateSDStatus(0);
	LCD_UpdateGPSStatus(0);
}


/*! \fn void LCD_UpdateGPSStatus(uint8_t s)
    \brief  Update GPS Status - Validate received gps data and displays information if NOT STATUS
    \param s Bit in order to print cross from LCD_Cross() and indicates NOT STATUS
*/
void LCD_UpdateGPSStatus(uint8_t s)
{
	static uint8_t last_s = 9;
	
	if (last_s != s)
	{
		tft.drawBitmap(195,40,BMP_gps  ,32,32,ST77XX_BLACK,ST77XX_WHITE);
		if (s == 0)
		{
			LCD_Cross(196,41,30,30);
		}
	}
	last_s = s;
}


/*! \fn void LCD_UpdateSDStatus(uint8_t s)
    \brief  Update SD Card Status - Validate SD Card functioning and displays information if NOT STATUS
    \param s Bit in order to print cross from LCD_Cross() and indicates NOT STATUS
*/
void LCD_UpdateSDStatus(uint8_t s)
{
	static uint8_t last_s = 9;

	if (last_s != s)
	{	
		tft.drawBitmap(162,40,BMP_sd   ,32,32,ST77XX_BLACK,ST77XX_WHITE);
		if (s == 0)
		{
			LCD_Cross(163,41,30,30);
		}
	}
	last_s = s;
}


/*! \fn void LCD_UpdateWIFIStatus(uint8_t s)
    \brief  Validate WIFI Status - Validate WiFi connection and displays information if NOT STATUS
    \param s Bit in order to print cross from LCD_Cross() and indicates NOT STATUS
*/
void LCD_UpdateWIFIStatus(uint8_t s)
{
	static uint8_t last_s = 9;
	
	if (last_s != s)
	{
		tft.drawBitmap(125,40,BMP_cloud,32,32,ST77XX_BLACK,ST77XX_WHITE);
		if (s == 0)
		{
			LCD_Cross(125,40,31,31);
		}
	}
	last_s = s;
}


/*! \fn void LCD_UpdateSat(uint8_t s)
    \brief  Update Number of Satellites that are reachable to the GPS Sensor 
    \param s Number of satellites reached by the GPS sensor
*/
void LCD_UpdateSat(uint8_t s)
{
	char sat[3];
	static uint8_t last_s = 9;
	
	if (last_s != s){
		sprintf(sat,"%d",s);
		LCD_Text(226, 61, sat);
	}
	last_s = s;
}



/*! \fn void LCD_UpdateSamples(int V)
    \brief  Update Number of Samples received by GPS sensor and stored 
    \param V Number of samples stored in current set of data
*/
void LCD_UpdateSamples(int V)
{
	static int pV = 0;
	if (pV != V )
	{
		if (V == 0)
		{
			LCD_TextBox(125,90,100,50, 10,"Samples",1);	// Clear TFT NS Box Background
		} else
		LCD_TextBox(125,90,100,50, V,"",2);
	}
	pV = V;
}


/*! \fn void LCD_UpdateNextTime(int V)
    \brief  Update timer to receive a new sample and analyze it
    \param V Time to next sample
*/
void LCD_UpdateNextTime(int V)
{
	static int pV = 0;
	if (pV != V )
	{
		if (V == 0)
		{
			LCD_TextBox(15,90,100,50, 10,"Next Sample",1);	// Clear TFT NS Box Background
		} else
		LCD_TextBox(15,90,100,50, V,"",2);
	}
	pV = V;
}


/*! \fn void LCD_UpdateOriSize(int V)
    \brief Update and display the size of original trajectory file
    \param V Original Data File Size (Bytes)
*/
void LCD_UpdateOriSize(int V)
{
	LCD_TextBox( 15,150,100,50,V,"",2);
}


/*! \fn void LCD_UpdateCompSize(int V)
    \brief Update and display the size of compressed trajectory file
    \param V Compressed Data File Size (Bytes)
*/
void LCD_UpdateCompSize(int V)
{
	LCD_TextBox(125,150,100,50,V,"",2);
}


/*! \fn void LCD_UpdateStatus(int S)
    \brief Update Graphbox that shows if the system is storing data
    \param S Bit in order to set the Graph Box STATUS - ON/OFF
*/
void LCD_UpdateStatus(int S)
{
	static uint8_t last_s = -1;
	
	if (last_s != S)
	{
		LCD_GraphBox(15,30,100,50, S);
	}
	last_s = S;
	
}


/*! \fn void LCD_UpdateDate(uint16_t y, uint8_t m, uint8_t d)
    \brief Update date information received from satellites
    \param y Current year data received from GPS sensor
	\param m Current month data received from GPS sensor
	\param d Current day data received from GPS sensor
*/
void LCD_UpdateDate(uint16_t y, uint8_t m, uint8_t d)
{
	char data[18] = "";
	
	// Once any field of the date is less than 10, the information received would have only one character.
	// In order to standardize the data, a 0 would be added before the number.
	char zyear[2];
	char zmonth[2];
	char zday[2];
	
	
	(y < 10) ? (strcpy(zyear, "0"))  : (strcpy(zyear, ""));
	(m < 10) ? (strcpy(zmonth, "0")) : (strcpy(zmonth, ""));
	(d < 10) ? (strcpy(zday, "0"))   : (strcpy(zday, ""));
	
	sprintf(data,"%s%d/%s%d/%s%d", zyear, y, zmonth, m, zday, d);
	LCD_Text(5, 220, data);
	
}


/*! \fn void LCD_UpdateTime(uint8_t h, uint8_t m, uint8_t s)
    \brief Update time information received from satellites
    \param h Current hour data received from GPS sensor
	\param m Current minute data received from GPS sensor
	\param s Current second data received from GPS sensor
*/
void LCD_UpdateTime(uint8_t h, uint8_t m, uint8_t s)
{
	char hora[18] = "";
	
	// Once any field of the date is less than 10, the information received would have only one character.
	// In order to standardize the data, a 0 would be added before the number.
	char zhour[2];
	char zmin[2];
	char zsec[2];
		
	(h < 10) ? (strcpy(zhour, "0")) : (strcpy(zhour, ""));
	(m < 10) ? (strcpy(zmin, "0")) : (strcpy(zmin, ""));
	(s < 10) ? (strcpy(zsec, "0")) : (strcpy(zsec, ""));
	
	sprintf(hora, "%s%d:%s%d:%s%d", zhour, h, zmin, m, zsec, s);
	LCD_Text(140, 220, hora);
}


// Sizes of compressed and un-compressed data
void LCD_UpdateCompression(int UnComp, int Comp){
	
	LCD_UpdateOriSize(UnComp);
	LCD_UpdateCompSize(Comp);
	
}				
