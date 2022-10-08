#include "radio.hpp"
#include "oled.hpp"

OLED oled;

void HackRadio::radioSetup()
{
  Serial.println("SETUPING RADIO");
  boardInitMcu();
  RadioEvents.TxDone = onTxDone;
  RadioEvents.TxTimeout = onTxTimeout;
  RadioEvents.RxDone = onRxDone;

  Radio.Init(&RadioEvents);
  Radio.SetChannel(RF_FREQUENCY);
  Radio.SetTxConfig(MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                    LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                    LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                    true, 0, 0, LORA_IQ_INVERSION_ON, 3000);

  Radio.SetRxConfig(MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
                    LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
                    LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
                    0, true, 0, 0, LORA_IQ_INVERSION_ON, true);

  Radio.Rx(0);

  oled = OLED{};
  oled.initDisplay();

  // // Show initial display buffer contents on the screen --
  // // the library initializes this with an Adafruit splash screen.
  oled.refreshDisplay();

  // // Clear the buffer
  oled.clearDisplay();

  oled.refreshDisplay();
}

void HackRadio::irq()
{
  Serial.println("Listening");
  Radio.IrqProcess();
}

void HackRadio::sendData(char str[])
{
  Serial.printf("\r\nsending packet \"%s\" , length %d\r \n", str, strlen(str));
  Radio.Send((uint8_t *)str, strlen(str));
  lowPowerHandler();
}

void onTxDone(void)
{
  Serial.println("TX done");
  Radio.Rx(0);
}

void onTxTimeout(void)
{
  Radio.Sleep();
  Serial.println("TX Timeout");
}
void onRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr)
{
  char received[30];
  memcpy(received, payload, size);
  received[size] = '\0';
  Serial.printf("\r\n\"%s\" Rssi %d  LENGTH %d\r\n", received, rssi, size);

  HackRadio::sendDataToScreen(received, size);
}

void HackRadio::sendDataToScreen(char str[], int size)
{
  Serial.printf("\r\nsending data to display\"%s\" , length %d\r \n", str, strlen(str));
  oled.drawchar(str, 0, 0, size);
}