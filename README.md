# CompressionGNSS
Lossless GNSS Compression Algorithm for  Embedded Systems 

## Description
This project aims to study and propose a method of data compression that represents geographic coordinates (Global Navigation Satellite System or GNSS) to compress the size of a data packet that describes a trajectory, reducing the energy cost of a possible transmission of information. The proposed method is to use the Degrees/Minutes/Seconds (or DMS, and unlike Decimal Degrees or DD) coordinate model so that you can reduce repetitions contained in it, and apply an effective compression model to decrease its size. For these models, the Huffman Compression Method, the Lempel-Ziv 1977 method (LZ77), the Lempel-Ziv-Welch (LZW) method and the Run-Length Enconding (RLE) method will be analyzed. All procedures will be evaluated with simulation data and data obtained in real environment by a platform developed for this purpose.




## Structure

* 01.Analisys
  * Compression methods analisys and results
* 02.SimulacaoPreCompressao
  * Virtual environment simulation 
* 03.SimulacaoPosCompressao
  * Verification of the simulation 
* 04.Prototipo
  * Prototype development 


## Prototype Ressources

### Libraries
* [mySD][1]
* [TinyGPS++][2]
* [ArduinoJson][3]
* [Adafruit_GX][4]
* [Vector][6]
* [WiFi][8]

### Headers
* [Adafruit_ST7789][5]
* [SPI][7]

[1]: https://github.com/nhatuan84/esp32-micro-sdcard "mySD"
[2]: https://github.com/mikalhart/TinyGPSPlus "TinyGPS++"
[3]: https://github.com/bblanchon/ArduinoJson "ArduinoJson"
[4]: https://github.com/adafruit/Adafruit-GFX-Library "Adafruit_GX"
[5]: https://github.com/adafruit/Adafruit-ST7735-Library/blob/master/Adafruit_ST7789.h "Adafruit_ST7789"
[6]: https://github.com/janelia-arduino/Vector "Vector"
[7]: https://github.com/arduino/ArduinoCore-avr/blob/master/libraries/SPI/src/SPI.h "SPI"
[8]: https://github.com/arduino-libraries/WiFi "WiFi"



## Prortype
### Prototype's Schema
<div>
  <a href="https://ibb.co/2dFKKq1"><img src="https://i.ibb.co/SB6vvN4/ESP32-SCHEMATICS.jpg" alt="ESP32-SCHEMATICS" border="0" class="center"></a>
</div>


### Systems Fluxogram
<div>
  <a href="https://ibb.co/2PBGwB5"><img src="https://i.ibb.co/0Z3Hk3Q/fluxograma.png" alt="fluxograma" border="0" class="center"></a>
</div>


## Papers

Cite as:

* Rafael Perez, Valderi R. Q. Leithardt, Sérgio D. Correia, “Lossless Compression  Scheme for Efficient GNSS Data Transmission on IoT Devices”, Proc. of the International Conference on Electrical, Computer and Energy Technologies (ICECET), 9-10 December 2021, Cape Town-South Africa. 

* Sérgio D. Correia, Rafael Perez, João Matos-Carvalho, Valderi R. Q. Leithardt. “µJSON, a Lightweight Compression Scheme for Embedded GNSS Data Transmission on IoT Nodes”, 5th Conference on Cloud and Internet of Things, March 28-30, 2022, Marrakech, Morocco.
