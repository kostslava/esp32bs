#define led1 12
#define led2 10
#define led3 46
#define led4 8

#define btn1 14

#define photoinput 17

bool prevstate = HIGH;
bool btnclicked = false;  // ADDED: Toggle state for LED2

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(btn1, INPUT_PULLUP);
}

void loop() {
  bool currentstate = digitalRead(btn1);
  int lightlevel = analogRead(photoinput);

  if (currentstate == LOW && prevstate == HIGH) {
    flashLeds();
  }
  if (lightlevel >= 1500) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }

  if (lightlevel >= 2500) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }

  if (lightlevel >= 3000) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }

  if (lightlevel >= 3500) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
  }

  if (lightlevel >= 3700) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
  }

  prevstate = currentstate;
}


void flashLeds() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  delay(200);

  digitalWrite(led1, HIGH);
  delay(200);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(150);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  delay(200);
  digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH);
  delay(150);
  digitalWrite(led4, LOW);
  digitalWrite(led3, HIGH);
  delay(200);
  digitalWrite(led3, LOW);
  digitalWrite(led2, HIGH);
  delay(250);
  digitalWrite(led2, LOW);
  digitalWrite(led1, HIGH);
  delay(150);
  digitalWrite(led1, LOW);
}
