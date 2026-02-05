#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_CS 13
#define TFT_DC 18
#define TFT_RST 17
#define TFT_SCLK 15
#define TFT_MOSI 16
#define BL 14

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);  // Start serial, do this once
  SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);
  pinMode(BL, OUTPUT);
  digitalWrite(BL, HIGH);
  tft.init(240, 240);
  tft.setRotation(0);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.print("H");
  delay(200);
  tft.print("e");
  delay(200);
  tft.print("l");
  delay(200);
  tft.print("l");
  delay(200);
  tft.print("o");
  delay(200);
  tft.print(" ");
  delay(200);
  tft.print("W");
  delay(200);
  tft.print("o");
  delay(200);
  tft.print("r");
  delay(200);
  tft.print("l");
  delay(200);
  tft.print("d");
  delay(200);
  tft.print("!");
  delay(200);
  tft.print("!");
  delay(200);
  tft.println("!");
}


void loop() {
  
}


