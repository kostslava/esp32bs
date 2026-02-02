#include <Adafruit_NeoPixel.h>


#define rgb 48
#define touch 15

int mode = 1;

int lasttouch = LOW;

Adafruit_NeoPixel pixels(1, rgb, NEO_GRB + NEO_KHZ800);
//doing sm bs with the adafruit

void setup() {
  pinMode(touch, INPUT);
  pixels.begin();
  pixels.setPixelColor(0, 150, 150, 150);
  pixels.show();
}


void loop() {
  int currenttouch = digitalRead(touch);
  
  if (currenttouch == HIGH && lasttouch == LOW) {
    if (mode == 1) {
      mode = 2;
      pixels.setPixelColor(0, 150, 0, 0);  // Red when not touched
      pixels.show();
    }

    else if (mode == 2) {
      mode = 3;
      pixels.setPixelColor(0, 0, 150, 0);  // Green when not touched
      pixels.show();

    }

    else {
      mode = 1;
      pixels.setPixelColor(0, 0, 0, 150);  // Blue when not touched
      pixels.show();
    }
  }
  lasttouch = currenttouch;
}
