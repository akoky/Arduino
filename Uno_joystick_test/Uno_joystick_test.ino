int buttonPin = 3;
int buttonState = 0;

int dirX = 0;
int dirY = 0;

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, OUTPUT);
  digitalWrite(buttonPin , HIGH);

}

void loop() {
  int x = analogRead(A0);
  int y = analogRead(A1);

  if (x < 100) {
    dirX = 0;
  } else if (x > 1000) {
    dirX = 2;
  } else {
    dirX = 1;
  }

  if (y < 100) {
    dirY = 0;
  } else if (y > 1000) {
    dirY = 2;
  } else {
    dirY = 1;
  }


  if (digitalRead(buttonPin) == LOW && buttonState == 0) {
    buttonState = 1;
  }
  else if (digitalRead(buttonPin) == HIGH && buttonState == 1) {
    buttonState = 0;
  }

  Serial.println(" ");
  Serial.print("Axis X = ");
  Serial.print(dirX);
  Serial.print(" ,");
  Serial.print("Axis Y = ");
  Serial.print(dirY);
  Serial.print(" ,");
  Serial.print("ButtonState = ");
  Serial.println(buttonState);
  delay(1);
}
