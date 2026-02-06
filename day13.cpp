#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_CS 13
#define TFT_DC 18
#define TFT_RST 17
#define TFT_SCLK 15
#define TFT_MOSI 16
#define TFT_BL 14
#define VRx 6
#define VRy 5
#define SW 4

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RST);

int X_Cursor = 0;
int Y_Cursor = 0;

void setup() {
  Serial.begin(115200);  // Start serial, do this once
  SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);
  ledcAttach(TFT_BL, 5000, 8);
  ledcWrite(TFT_BL, 100);
  tft.init(240, 240);
  tft.setRotation(0);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2.75);
  tft.fillScreen(ST77XX_BLACK);
}

void loop() {
  tft.setTextColor(ST77XX_BLACK);
  tft.setCursor(X_Cursor, Y_Cursor);
  tft.print("o");
  tft.setTextColor(ST77XX_WHITE);

  int VRx_input = analogRead(VRx);
  int VRy_input = analogRead(VRy);
  X_Cursor = VRx_input / 18.614;
  Y_Cursor = VRy_input / 18.614;

  tft.setCursor(X_Cursor, Y_Cursor);
  tft.print("o");
  delay(25);
}
