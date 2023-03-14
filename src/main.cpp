#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include "KWP2000.h"

#define K_OUT 1       // Tx on Arduino
#define K_IN 0        // Rx on Arduino
#define BIKE Serial   // Serial communication with bike
#define FETCH_RATE 10 // 10 times / s

#define DEBUG_IN 2  // SoftwareSerial Rx
#define DEBUG_OUT 3 // SoftwareSerial Tx

#define LEDSTRIP_PIN 5                 // PWM pin on Arduino Nano
#define LEDSTRIP_PIXELS 7              // 6 gears + neutral
#define COLOR_ACTIVE_GEAR 0x00FF00     // Green
#define COLOR_NON_ACTIVE_GEAR 0x001000 // Light green
#define COLOR_NEUTRAL 0xFF4500         // Orange red

SoftwareSerial debug(DEBUG_IN, DEBUG_OUT);
Adafruit_NeoPixel ledstrip(LEDSTRIP_PIXELS, LEDSTRIP_PIN, NEO_GRB + NEO_KHZ800);

KWP2000 ECU(&BIKE, K_OUT);

int8_t initKline();
void setGearOnLedstrip(uint8_t gear);
void ledstripAnimation();
void terminate();

void setup()
{
  pinMode(K_OUT, OUTPUT); // required?
  pinMode(K_IN, INPUT);   // required?

  ledstrip.begin();
  ledstripAnimation();

  // Test gears display on ledstrip
  /*for (int gear = 0; gear < 7; gear++)
  {
    setGearOnLedstrip(gear);
    delay(1000);
  }*/

  ECU.enableDebug(&debug, DEBUG_LEVEL_VERBOSE, 9600);
  // if initialization is negative, terminate (hardware must be reset).
  if (initKline() < 0)
  {
    terminate();
  }
}

void loop()
{
  int8_t status = ECU.requestGPS();
  if (status)
  {
    uint8_t gear = ECU.getGPS();
    // set LED accordingly
    setGearOnLedstrip(gear);
  }
  else
  {
    if (initKline() < 0)
    {
      terminate();
    }
  }
  delay(1000 / FETCH_RATE);
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

void setGearOnLedstrip(uint8_t gear)
{
  ledstrip.clear();
  if (gear == 0)
  {
    ledstrip.setPixelColor(gear, COLOR_NEUTRAL);
  }
  else
  {
    for (int i = 1; i < gear; i++)
    {
      ledstrip.setPixelColor(i, COLOR_NON_ACTIVE_GEAR);
    }
    ledstrip.setPixelColor(gear, COLOR_ACTIVE_GEAR);
  }
  ledstrip.show();
}

void ledstripAnimation()
{
  for (int i = 0; i < 7; i++)
  {
    ledstrip.setPixelColor(i, COLOR_ACTIVE_GEAR);
    ledstrip.show();
    delay(50);
  }
  for (int i = 6; i >= 0; i--)
  {
    ledstrip.setPixelColor(i, 0x000000);
    ledstrip.show();
    delay(50);
  }
}

void terminate()
{
  ledstrip.clear();
  ledstrip.show();
  Serial.end();
  debug.println("Hardware terminating");
  exit(0);
}