#include "Keyboard.h"

int sw = 0;
int x = 0;
int y = 0;

void setup() {
  // open the serial port:
  Serial.begin(9600);
  // initialize control over the keyboard:
  Keyboard.begin();

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
}

void loop() {
  x = analogRead(A0) - 518;
  y = analogRead(A1) - 513;

  //  Serial.print(x);
  //  Serial.print(" , ");
  //  Serial.println(y);

  if (x > 10) {
    Keyboard.press(KEY_LEFT_ARROW);
  } else if (x < -10) {
    Keyboard.press(KEY_RIGHT_ARROW);
  } else {
    Keyboard.release(KEY_LEFT_ARROW);
    Keyboard.release(KEY_RIGHT_ARROW);
  }
  if (y < -10) {
    Keyboard.press(KEY_DOWN_ARROW);
  } else if (y > 10) {
    Keyboard.press(KEY_UP_ARROW);
  }
  else {
    Keyboard.release(KEY_DOWN_ARROW);
    Keyboard.release(KEY_UP_ARROW);
  }

  if (digitalRead(2) == LOW & sw == 0) {
    Keyboard.write('a');
    sw = 1;
  }
  else if (digitalRead(2) == HIGH & sw == 1) {
    sw = 0;
  }
}
