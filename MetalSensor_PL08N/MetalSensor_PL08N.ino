// OLED settings
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int value = 0;

long delaycount = 1000;
long relayPeriod = 3000;

int bs = 0;
int bs2 = 0;
int bs3 = 0;
int bs4 = 0;

void setup() {
  Serial.begin(9600);

  delay(1000);

  // OLED Start
  display.begin(i2c_Address, true);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(1);
  display.setCursor(0, 15);
  display.print("SAVEWO");
  display.display();
  delay(1000);

  pinMode(12, OUTPUT); // sensor pin
  digitalWrite(12, HIGH);

  pinMode(14, OUTPUT); // relay control pin
  digitalWrite(14, LOW);

  pinMode(16, OUTPUT); // delay +
  pinMode(10, OUTPUT); // delay -
  pinMode(13, OUTPUT); // relay +
  pinMode(9, OUTPUT); // relay -

  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(16, HIGH);

  //esp running
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
}

void loop() {
  _relaycontrol();
  _button();
  _display();
  delay(1);
}


void _relaycontrol() {
  if (digitalRead(12) == HIGH) {
    //value = 1;
    digitalWrite(14, LOW);
  }
  else if (digitalRead(12) == LOW) {
    //value = 0;
    delay(delaycount);
    digitalWrite(14, HIGH);
    delay(relayPeriod);
  }
  //Serial.println(value);
}

void _button() {
  if (digitalRead(9) == LOW && bs == 0 && relayPeriod > 0) {
    relayPeriod = relayPeriod - 1000;
    bs = 1;
  } else if (digitalRead(9) == HIGH && bs == 1) {
    bs = 0;
  }

  if (digitalRead(10) == LOW && bs2 == 0 && delaycount > 0) {
    delaycount = delaycount - 1000;
    bs2 = 1;
  } else if (digitalRead(10) == HIGH && bs2 == 1) {
    bs2 = 0;
  }

  if (digitalRead(13) == LOW && bs3 == 0) {
    relayPeriod = relayPeriod + 1000;
    bs3 = 1;
  } else if (digitalRead(13) == HIGH && bs3 == 1) {
    bs3 = 0;
  }

  if (digitalRead(16) == LOW && bs4 == 0) {
    delaycount = delaycount + 1000;
    bs4 = 1;
  } else if (digitalRead(16) == HIGH && bs4 == 1) {
    bs4 = 0;
  }
}

void _display() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(0, 10);
  display.print("Delay: ");
  display.print(delaycount);
  display.setCursor(0, 40);
  display.print("Relay: ");
  display.print(relayPeriod);
  display.display();
  delay(1);
}
