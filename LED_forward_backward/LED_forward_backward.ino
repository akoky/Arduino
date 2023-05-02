int closetime = 1000;
int delaytime = 25;
void setup() {
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(15, LOW);
  digitalWrite(18, LOW);
  digitalWrite(19, LOW);
  digitalWrite(21, LOW);
  digitalWrite(22, LOW);
  digitalWrite(23, LOW);
  digitalWrite(32, LOW);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
}

void loop() {
  _Forward();
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(15, LOW);
  digitalWrite(18, LOW);
  digitalWrite(19, LOW);
  digitalWrite(21, LOW);
  digitalWrite(22, LOW);
  digitalWrite(23, LOW);
  digitalWrite(32, LOW);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  _Backward();
   digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(15, LOW);
  digitalWrite(18, LOW);
  digitalWrite(19, LOW);
  digitalWrite(21, LOW);
  digitalWrite(22, LOW);
  digitalWrite(23, LOW);
  digitalWrite(32, LOW);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  delay(1);

}

void _Forward() {
  digitalWrite(15, HIGH);
  delay(delaytime);
  digitalWrite(2, HIGH);
  delay(delaytime);
  digitalWrite(4, HIGH);
  delay(delaytime);
  digitalWrite(5, HIGH);
  delay(delaytime);
  digitalWrite(18, HIGH);
  delay(delaytime);
  digitalWrite(19, HIGH);
  delay(delaytime);
  digitalWrite(21, HIGH);
  delay(delaytime);
  digitalWrite(22, HIGH);
  delay(delaytime);
  digitalWrite(23, HIGH);
  delay(delaytime);
  digitalWrite(12, HIGH);
  delay(delaytime);
  digitalWrite(13, HIGH);
  delay(delaytime);
  digitalWrite(32, HIGH);
  delay(delaytime);
}

void _Backward() {
  digitalWrite(32, HIGH);
  delay(delaytime);
  digitalWrite(13, HIGH);
  delay(delaytime);
  digitalWrite(12, HIGH);
  delay(delaytime);
  digitalWrite(23, HIGH);
  delay(delaytime);
  digitalWrite(22, HIGH);
  delay(delaytime);
  digitalWrite(21, HIGH);
  delay(delaytime);
  digitalWrite(19, HIGH);
  delay(delaytime);
  digitalWrite(18, HIGH);
  delay(delaytime);
  digitalWrite(5, HIGH);
  delay(delaytime);
  digitalWrite(4, HIGH);
  delay(delaytime);
  digitalWrite(2, HIGH);
  delay(delaytime);
  digitalWrite(15, HIGH);
  delay(delaytime);
}
