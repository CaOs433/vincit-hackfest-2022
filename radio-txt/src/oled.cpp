#include "oled.hpp"

void OLED::initDisplay(void) {
  Serial.println("Init display");
  this->display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!this->display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
}

void OLED::refreshDisplay(void) {
  Serial.println("Refresh display");
  this->display.display();
}

void OLED::clearDisplay(void) {
  Serial.println("CLEAR");
  this->display.clearDisplay();
}

void OLED::drawchar(char str[], int16_t x, int16_t y, int size) {
  Serial.println("DRAW CHAR");
  this->display.clearDisplay();

  this->display.setTextSize(1);               // Normal 1:1 pixel scale
  this->display.setTextColor(SSD1306_WHITE);  // Draw white text
  this->display.setCursor(0, 0);              // Start at top-left corner
  this->display.cp437(true);                  // Use full 256 char 'Code Page 437' font

  for(int i=0; i<size;i++) {
    this->display.write(str[i]);
  }
  
  this->display.display();
  delay(2000);
}
