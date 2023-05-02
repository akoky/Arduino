int sw1 = 2;
int sw1Val = 0;
int sw1buttonState = 0;

int sw2 = 3;
int sw2Val = 0;
int sw2buttonState = 0;

int sw3 = 4;
int sw3Val = 0;
int sw3buttonState = 0;

int sw4 = 5;
int sw4Val = 0;
int sw4buttonState = 0;

int sw = 6;
int swVal = 0;
int swbuttonState = 0;

int x = 0;
int y = 0;

int dirX = 0;
int dirY = 0;

void setup() {
  Serial.begin(9600);

  pinMode(sw1, OUTPUT);
  digitalWrite(sw1, HIGH);

  pinMode(sw2, OUTPUT);
  digitalWrite(sw2, HIGH);

  pinMode(sw3, OUTPUT);
  digitalWrite(sw3, HIGH);

  pinMode(sw4, OUTPUT);
  digitalWrite(sw4, HIGH);

  pinMode(sw, OUTPUT);
  digitalWrite(sw, HIGH);
}

void loop() {
  _axis();
  _buttons();
  Serial.println("test");
  Serial.print("S");
  Serial.print(dirX);
  Serial.print(",");
  Serial.print(dirY);
  Serial.print(",");
  Serial.print(swVal);
  Serial.print(",");
  Serial.print(sw1Val);
  Serial.print(",");
  Serial.print(sw2Val);
  Serial.print(",");
  Serial.print(sw3Val);
  Serial.print(",");
  Serial.println(sw4Val);
  delay(10);
}

void _axis() {
  x = analogRead(A0) - 518;
  y = analogRead(A1) - 512;

  if (x < -10) {
    dirX = 0;
  } else if (x > 10) {
    dirX = 2;
  } else {
    dirX = 1;
  }

  if (y < -10) {
    dirY = 0;
  } else if (y > 10) {
    dirY = 2;
  } else {
    dirY = 1;
  }
}

void _buttons() {
  if (digitalRead(sw) == LOW && swbuttonState == 0) {
    swbuttonState = 1;
    swVal = 1;
    delay(200);
  } else if (digitalRead(sw) == HIGH && swbuttonState == 1) {
    swbuttonState = 0;
    swVal = 0;
  }

  if (digitalRead(sw1) == LOW && sw1buttonState == 0) {
    sw1buttonState = 1;
    sw1Val = 1;
    delay(200);
  } else if (digitalRead(sw1) == HIGH && sw1buttonState == 1) {
    sw1buttonState = 0;
    sw1Val = 0;
  }
  if (digitalRead(sw2) == LOW && sw2buttonState == 0) {
    sw2buttonState = 1;
    sw2Val = 1;
    delay(200);
  } else if (digitalRead(sw2) == HIGH && sw2buttonState == 1) {
    sw2buttonState = 0;
    sw2Val = 0;
  }

  if (digitalRead(sw3) == LOW && sw3buttonState == 0) {
    sw3buttonState = 1;
    sw3Val = 1;
    delay(200);
  } else if (digitalRead(sw3) == HIGH && sw3buttonState == 1) {
    sw3buttonState = 0;
    sw3Val = 0;
  }

  if (digitalRead(sw4) == LOW && sw4buttonState == 0) {
    sw4buttonState = 1;
    sw4Val = 1;
    delay(200);
  } else if (digitalRead(sw4) == HIGH && sw4buttonState == 1) {
    sw4buttonState = 0;
    sw4Val = 0;
  }
}


       
