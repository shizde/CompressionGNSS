# CompressionGNSS
Lossless GNSS Compression Algorithm for  Embedded Systems 

## Descrição
Este projeto visa estudar, e propor um método de compressão de dados que represente coordenadas geográficas (Global Navigation Satellite System ou GNSS) para comprimir o tamanho de um pacote de dados que descreva uma trajetória, diminuindo o custo energético de uma possível transmissão de informação. O método proposto consiste em utilizar o modelo de coordenadas Degrees/Minutes/Seconds (ou DMS, e ao contrário de Decimal Degrees ou DD) para que seja possível reduzir repetições contidas no mesmo, e aplicar um modelo de compressão efetivo para diminuir seu tamanho. Para estes modelos será analisado o Método de Compressão de Huffman , o método Lempel-Ziv 1977 (LZ77), o método Lempel-Ziv-Welch (LZW) e o método Run-Length Enconding (RLE). Todos os procedimentos serão avaliados com dados de simulação e dados obtidos em ambiente real por uma plataforma desenvolvida para o efeito.

A

## Estrutura

* 01.Analise
  * Sistema de análise dos dados e métodos
* 02.SimulacaoPreCompressao
  * Simulação de um ambiente real e das funcionalidades a serem executadas. 
* 03.SimulacaoPosCompressao
  * Verificação dos dados de simulação 
* 04.Prototipo
  * Desenvolvimento em ambiente real 

## Referências de Análises

## Bibliotecas utilizadas na prototipagem

## Protótipo
<div>
  <a href="https://ibb.co/2dFKKq1"><img src="https://i.ibb.co/SB6vvN4/ESP32-SCHEMATICS.jpg" alt="ESP32-SCHEMATICS" border="0"></a>
  <hr>
  <a href="https://ibb.co/2PBGwB5"><img src="https://i.ibb.co/0Z3Hk3Q/fluxograma.png" alt="fluxograma" border="0"></a>
</div>


## Publicações

* Rafael Perez, Valderi R. Q. Leithardt, Sérgio D. Correia, “Lossless Compression  Scheme for Efficient GNSS Data Transmission on IoT Devices”, Proc. of the International Conference on Electrical, Computer and Energy Technologies (ICECET), 9-10 December 2021, Cape Town-South Africa. 

* Sérgio D. Correia, Rafael Perez, João Matos-Carvalho, Valderi R. Q. Leithardt. “µJSON, a Lightweight Compression Scheme for Embedded GNSS Data Transmission on IoT Nodes”, 5th Conference on Cloud and Internet of Things, March 28-30, 2022, Marrakech, Morocco.
