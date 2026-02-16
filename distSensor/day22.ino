#define trig 15
#define echo 16

#define led1 4
#define led2 5
#define led3 6
#define led4 7
#define led5 17
#define led6 18

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  int duration = pulseIn(echo, HIGH);
  int distance = duration / 58;

  Serial.print("cm away: ");
  Serial.println(distance);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);

  if (distance <= 15) {
    digitalWrite(led1, HIGH);
  } 
  if (distance <= 12) {
    digitalWrite(led2, HIGH);
  } 
  if (distance <= 9) {
    digitalWrite(led3, HIGH);
  } 
  if (distance <= 6) {
    digitalWrite(led4, HIGH);
  } 
  if (distance <= 4) {
    digitalWrite(led5, HIGH);
  } 
  if (distance <= 2) {
    digitalWrite(led6, HIGH);
  }

  delay(100);
}
