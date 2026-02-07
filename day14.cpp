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

const int xMid = 1950;
const int yMid = 1950;

int xCursor = 0;
int yCursor = 0;
int xIn = 0;
int yIn = 0;
int xDiff = 0;
int yDiff = 0;

void setup() {
  Serial.begin(115200);  // Start serial, do this once
  SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS); //start spi with tft
  ledcAttach(TFT_BL, 5000, 8);
  ledcWrite(TFT_BL, 100);
  tft.init(240, 240);
  tft.setRotation(0);
  tft.fillScreen(ST77XX_BLACK);
}

void loop() {
  //last cursor update erased
  tft.setTextColor(ST77XX_BLACK);
  tft.setTextSize(2.75);
  tft.setCursor(xCursor, yCursor);
  tft.print("o");

  //NEW STUFF: find differences
  xIn = analogRead(VRx);
  yIn = analogRead(VRy);
  xDiff = xMid - xIn;
  yDiff = yMid - yIn;

  if (xDiff > 100 || xDiff < -100) {
    xCursor = xCursor - ((xDiff / 15) / 18);

    if (xCursor > 225 || xCursor < 0) {
      xCursor = xCursor + ((xDiff / 15) / 18);
    }
  }

  if (yDiff > 100 || yDiff < -100) {
    yCursor = yCursor - ((yDiff / 15) / 18);

    if (yCursor > 225 || yCursor < 0) {
      yCursor = yCursor + ((yDiff / 15) / 18);
    } 
  }

  //write the cursor
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(xCursor, yCursor);
  tft.print("o");
  delay(10);
}
