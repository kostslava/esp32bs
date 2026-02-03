#include <Adafruit_NeoPixel.h>


#define rgb 48
#define touch 14
#define buzzer 16
#define sw 4
#define vry 5
#define vrx 6

int mode = 1;
int lasttouch = LOW;

Adafruit_NeoPixel pixels(1, rgb, NEO_GRB + NEO_KHZ800);
//doing sm bs with the adafruit

void setup() {
  Serial.begin(115200);  // Start serial, do this once
  pinMode(touch, INPUT);
  pixels.begin();
  pixels.setPixelColor(0, 150, 150, 150);
  pixels.show();
  ledcAttach(buzzer, 2000, 8);

}


void loop() {
  int currenttouch = digitalRead(touch);
  int vrx_amt = analogRead(vrx);
  int vry_amt = analogRead(vry);
  
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
  ledcWriteTone(buzzer, vrx_amt);
  delay(100);
  lasttouch = currenttouch;

}
