int i = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  analogWrite(4, 1024);
}

// the loop function runs over and over again forever
void loop() {
  if (analogRead(4) == 1024) {
    analogWrite(4, 0);
    delay(1000);
  }
  
  if (analogRead(4) == 0) {
    analogWrite(4, 1024);
    delay(1000);
  }
}
