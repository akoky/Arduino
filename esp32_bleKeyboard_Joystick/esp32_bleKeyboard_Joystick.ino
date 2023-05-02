#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

int button_pin = 5;
int sw = 0;
int x = 0;
int y = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();

  pinMode(button_pin, OUTPUT);
  digitalWrite(button_pin, HIGH);
}

void loop() {
  if (bleKeyboard.isConnected()) {
    _button(); 
    _axis();
  }
  delay(30);
} 

void _button() {
  if (digitalRead(button_pin) == LOW && sw == 0) {
    bleKeyboard.press(0x20);
    sw = 1;
  }
  else if (digitalRead(button_pin) == HIGH && sw == 1) {
    bleKeyboard.release(0x20);
    sw = 0;
  }  
}

void _axis() {
  x = analogRead(15);
  y = analogRead(4);
  
  Serial.print(x);
  Serial.print(" , ");
  Serial.println(y);

  if (x > 3000) {
    bleKeyboard.press(KEY_LEFT_ARROW);
  } else if (x < 1000) {
    bleKeyboard.press(KEY_RIGHT_ARROW);
  } else {
    bleKeyboard.release(KEY_LEFT_ARROW);
    bleKeyboard.release(KEY_RIGHT_ARROW);
  }
  if (y > 3000) {
    bleKeyboard.press(KEY_DOWN_ARROW);
  } else if (y < 1000) {
    bleKeyboard.press(KEY_UP_ARROW);
  }
  else {
    bleKeyboard.release(KEY_DOWN_ARROW);
    bleKeyboard.release(KEY_UP_ARROW);
  }
}
