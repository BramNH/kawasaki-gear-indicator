﻿# kawasaki-gear-indicator
A custom made gear indicator with a w2812b LED strip and some hardware to read the Gear Position Sensor (GPS) from the Kawasaki Diagnostic System (KDS).

## KWP2000 Library
Most of the work is done by Aster94 through his [KWP2000](https://github.com/aster94/Keyword-Protocol-2000) library, providing an interface to communicate with Suzuki and Kawasaki bikes. Check out that GitHub page for more info about the possible hardware communication possibilities.
I modified the library to limit it for communication with Kawasaki ECUs. Next to this, I added a *SoftwareSerial* debugging to allow debugging on devices that do not provide two Hardware Serial interfaces, e.g. the Atmega328P on the Arduino Uno/Nano.

## Hardware used
- **Arduino Nano**;
- **MC33660**: *IC that converts the two line UART (Tx/Rx) of the Arduino to the single bi-directional K-line, and vice-versa;*
- **FWY-C-4F-B Connector**: *Male KDS connector, I found a cheap one on [AliExpress](https://nl.aliexpress.com/item/1005002438381284.html?spm=a2g0o.order_list.order_list_main.5.186f79d26YG6rV&gatewayAdapt=glo2nld).*
