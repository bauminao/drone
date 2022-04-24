# GPS-Debugging

# Introduction

* Receive GPS-signal and print via Serial Line

## Schematics

``` asciiart
       _____
      /     \
      | ANT |
      \_____/
        |
        |
  +-----|-------------+  
  |/\   #           /\|  
  |\/               \/|  
  |     +-------+     |  
  |     |NEO-6M |     |  
  |     | G P S |     |  
  |     +-------+     |  
  |                   |  
  |      G     V      |  
  |      N T R C      |  
  |/\    D x x C    /\|  
  |\/    # # # #    \/|  
  +------|-|-|-|------+  
         | | | |
         | | | +---------------------------------+
         | | |           +-------------------+   |
         | | |           |       o o o       |   |
         | | |           |o  Tx  o o o  VIN o|   |
         | | |           |o  Rx         GND o|   |
         | | |           |o RST         RST o|   |
         +-|-|------------x GND          5V x----+
           | |           |o  D2          A7 o| 
           | |           |o  D3  /===\   A6 o| 
           | |           |o  D4  |RST|   A5 o| 
           | |           |o  D5  \===/   A4 o| 
           | |           |o  D6          A3 o| 
           +--------------x  D7  //=\\   A2 o| 
             +------------x  D8 //===\\  A1 o| 
                         |o  D9 \\===//  A0 o| 
                         |o D10  \\=//  REF o| 
                         |o D11         3V3 o| 
                         |o D12  +---+  D13 o| 
                         |       |USB|       | 
                         +-------|   |-------+ 
                                 |   |
```

## additional Libraries:

* NeoGPS-4.2.9
* NeoSWSerial-3.0.5

Needed some adaptions to get it up and running. Mainly about the serial-line and output.

### NeoGPS

**Name: "NeoGPS"**
-  Author: SlashDevin
-  Maintainer: SlashDevin
-  Sentence: NMEA and ublox GPS parser, configurable to use as few as 10 bytes of RAM
-  Paragraph: Faster and smaller than all other GPS parsers
-  Website: https://github.com/SlashDevin/NeoGPS
-  Category: Communication
-  Architecture: avr, samd, sam, esp8266, arc32, esp32
-  Types: Contributed
-  Versions: [3.1.1, 3.1.2, 4.1.0, 4.1.3, 4.1.7, 4.1.8, 4.2.1, 4.2.2, 4.2.3, 4.2.4, 4.2.5, 4.2.6, 4.2.7, 4.2.8, 4.2.9]
-  Provides includes: NMEAGPS.h


### NeoSWSerial

**Name: "NeoSWSerial"**
-  Author: SlashDevin
-  Maintainer: SlashDevin
-  Sentence: An efficient replacement for SoftwareSerial at baud rates 9600, 19200 and 38400.
-  Paragraph: Simultaneous RX & TX, does not require additional TIMERs, interrupts not disabled during RX
-  Website: https://github.com/SlashDevin/NeoSWSerial
-  Category: Communication
-  Architecture: avr
-  Types: Contributed
-  Versions: [3.0.0, 3.0.1, 3.0.2, 3.0.3, 3.0.4, 3.0.5]
-  Provides includes: NeoSWSerial.h

