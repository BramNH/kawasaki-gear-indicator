#include <Arduino.h>
#include <SoftwareSerial.h>
#include "KWP2000.h"

#define K_OUT 1 // Tx on Arduino
#define K_IN 0  // Rx on Arduino
#define bike Serial
#define DEBUG_IN 2
#define DEBUG_OUT 3

SoftwareSerial debug(DEBUG_IN, DEBUG_OUT);
KWP2000 ECU(&bike, K_OUT);

void setup()
{
  pinMode(K_OUT, OUTPUT); // required?
  pinMode(K_IN, INPUT);   // required?

  ECU.enableDebug(&debug, DEBUG_LEVEL_DEFAULT, 115200);
  // if initialization is negative, terminate (hardware must be reset).
  if (ECU.initKline() < 0)
  {
    exit(0);
  }
}

void loop()
{
  int8_t status = ECU.requestGPS();
  if (status)
  {
    uint8_t gear = ECU.getGPS();
    // set LED accordingly
  }
  else
  {
    if (ECU.initKline() < 0)
    {
      exit(0);
    }
  }
  delay(100); // fetching GPS 10 times per second.
}

int8_t initKline()
{
  int8_t status = 0;
  // init needs to go through 5 phases
  while (status == 0)
  {
    status = ECU.initKline();
  }
  return status;
}