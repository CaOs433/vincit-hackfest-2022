#include "oled.hpp"

void setup() {
  Serial.begin(9600);

  OLED oled{};

  oled.initDisplay();

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  oled.refreshDisplay();
  delay(2000);

  // Clear the buffer
  oled.clearDisplay();

  oled.refreshDisplay();
  delay(2000);

  oled.drawchar("Moi", 8, 2);

  // Invert and restore display, pausing in-between
  //display.invertDisplay(true);
  //delay(1000);
  //display.invertDisplay(false);
  //delay(1000);

}

void loop() {
}
