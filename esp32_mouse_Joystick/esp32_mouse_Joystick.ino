/**
   This example turns the ESP32 into a Bluetooth LE mouse that continuously moves the mouse.
*/
#include <BleMouse.h>

BleMouse bleMouse;

int button_pin = 5;
int sw = 0;
int x = 0;
int y = 0;

void setup() {
//  Serial.begin(9600);
//  Serial.println("Starting BLE work!");
  bleMouse.begin();

  pinMode(button_pin, OUTPUT);
  digitalWrite(button_pin, HIGH);
}

void loop() {
  if (bleMouse.isConnected()) {
    _button();
    _axis();
  }
  delay(10);
}


void _button() {
  if (digitalRead(button_pin) == LOW && sw == 0) {
    bleMouse.click(MOUSE_LEFT);
    sw = 1;
  }
  else if (digitalRead(button_pin) == HIGH && sw == 1) {
    bleMouse.release(MOUSE_LEFT);
    sw = 0;
  }
}

void _axis() {
  x = analogRead(15);
  y = analogRead(4);

//    Serial.print(x);
//    Serial.print(" , ");
//    Serial.println(y);
  if (x > 3000) {
    bleMouse.move(0, 7.5);
  } else if (x < 1000) {
    bleMouse.move(0, -7.5);
  } else {
  }
  if (y > 3000) {
    bleMouse.move(-7.5, 0);
  } else if (y < 1000) {
    bleMouse.move(7.5, 0);
  } else {
  }

}
