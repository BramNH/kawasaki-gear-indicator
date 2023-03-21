# Kawasaki W2812B Gear Indicator
A custom made gear indicator with a W2812B LED strip and some hardware to read the Gear Position Sensor (GPS) from the Kawasaki Diagnostic System (KDS).

## KWP2000 Library
Most of the work is done by Aster94 through his [KWP2000](https://github.com/aster94/Keyword-Protocol-2000) library, providing an interface to communicate with Suzuki and Kawasaki bikes. Check out that GitHub page for more info about the possible hardware communication possibilities.
I modified the library to limit it for communication with Kawasaki ECUs. Next to this, I added a *SoftwareSerial* debugging to allow debugging on devices that do not provide two Hardware Serial interfaces, e.g. the Atmega328P on the Arduino Uno/Nano.

## Hardware used
- **Arduino Nano**;
- **MC33660**: *IC that converts the two line UART (Tx/Rx) of the Arduino to the single bi-directional K-line, and vice-versa;*
- **W2812B LED strip**: *LED strip with individually adressable RGB LEDs that is powered from 5V;*
- **FWY-C-4F-B Connector**: *Male KDS connector, I found a cheap one on [AliExpress](https://nl.aliexpress.com/item/1005002438381284.html?spm=a2g0o.order_list.order_list_main.5.186f79d26YG6rV&gatewayAdapt=glo2nld).*

### Diagram
![alt text](https://github.com/BramNH/kawasaki-gear-indicator/blob/main/img/schematic.jpg?raw=true)
Some notes:
- The W2812B LED strip can be powered from the 5V output of the Arduino Nano, this is possible since only 7 LEDs are used, limiting the current draw. It is still better to power the Arduino Nano and W2812B LED strip from an external power source (12v bike battery).
