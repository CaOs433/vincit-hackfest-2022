#include "oled.hpp"

void OLED::initDisplay(void) {
  this->display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!this->display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
}

void OLED::refreshDisplay(void) {
  this->display.display();
}

void OLED::clearDisplay(void) {
  this->display.clearDisplay();
}

void OLED::drawchar(String str, int16_t x, int16_t y) {
  this->display.clearDisplay();

  this->display.setTextSize(2);               // Normal 1:1 pixel scale
  this->display.setTextColor(SSD1306_WHITE);  // Draw white text
  this->display.setCursor(0, 0);              // Start at top-left corner
  this->display.cp437(true);                  // Use full 256 char 'Code Page 437' font

  for(char& c : str) {
    this->display.write(c);
  }
  
  this->display.display();
  delay(2000);
}
