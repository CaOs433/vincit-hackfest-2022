 #include "LoRaWan_APP.h"
#include "Arduino.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "oled.hpp"



void setup() {
  Serial.begin(9600);
  delay(2000);
Serial.println("SETUP");
  OLED oled{};

  oled.initDisplay();

  // // Show initial display buffer contents on the screen --
  // // the library initializes this with an Adafruit splash screen.
  delay(1000);
  oled.refreshDisplay();

  delay(2000);
  // // Clear the buffer
  oled.clearDisplay();

  oled.refreshDisplay();
  delay(2000);

  oled.drawchar("Moi", 8, 2,3);

}

void loop() {
  delay(2000);
  Serial.println("HELLO WOLR");
}
