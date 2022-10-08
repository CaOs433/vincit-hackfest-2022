#include "Arduino.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "radio.hpp"
#define BUTTON_PIN GPIO6
#define MSG_SIZE 1024

void handler();

HackRadio radio;

char msg[MSG_SIZE];
void setup()
{

  Serial.begin(9600);
  radio = HackRadio{};
  radio.radioSetup();
  Serial.println("SETUP");
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handler, FALLING); // trigger when button pressed, but not when released.

  radio.irq();
}

void handler()
{
  Serial.println(msg);
  radio.sendData(msg);
  radio.irq();
}

void loop()
{
  while (Serial.available() > 0)
  {
    Serial.println("we got available");
    memset(msg, 0, MSG_SIZE);
    Serial.readBytesUntil('\n', msg, MSG_SIZE);
    Serial.println(msg);
    delay(200);
  }
}
