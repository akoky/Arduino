// OLED settings
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int DRmode = 0; // 0 = Delay mode; 1 = Relay mode;

double delaycount = 1000;
double Dsecond = 1.0;
double relayPeriod = 3000;
double Rsecond = 3.0;

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

  pinMode(16, OUTPUT); // +
  digitalWrite(16, HIGH);

  pinMode(10, OUTPUT); // -
  digitalWrite(10, HIGH);

  pinMode(13, OUTPUT); // switch
  digitalWrite(13, HIGH);

  pinMode(2, OUTPUT); 
}

void loop() {
  _relaycontrol();
  _button();
  _display();
  
  //Serial.println(Dsecond);
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
  ////////////////// Delay mode //////////////////
  if (DRmode == 0)
  {
    if (digitalRead(13) == LOW && bs == 0) {
      DRmode = 1;
      bs = 1;
    }
    else if (digitalRead(13) == HIGH && bs == 1) {
      bs = 0;
    }

    if (digitalRead(16) == LOW && bs2 == 0) {
      delaycount = delaycount + 100;
      Dsecond = delaycount/1000;
      bs2 = 1;
    }
    else if (digitalRead(16) == HIGH && bs2 == 1) {
      bs2 = 0;
    }

    if (digitalRead(10) == LOW && delaycount > 0 && bs3 == 0) {
      delaycount = delaycount - 100;
      Dsecond = delaycount/1000;
      bs3 = 1;
    }
    else if (digitalRead(10) == HIGH && bs3 == 1) {
      bs3 = 0;
    }
  }
  ////////////////// Relay mode //////////////////
  else if (DRmode == 1)
  {
    if (digitalRead(13) == LOW && bs == 0) {
      DRmode = 0;
      bs = 1;
    }
    else if (digitalRead(13) == HIGH && bs == 1) {
      bs = 0;
    }

    if (digitalRead(16) == LOW && bs2 == 0) {
      relayPeriod = relayPeriod + 100;
      Rsecond = relayPeriod/1000;
      bs2 = 1;
    }
    else if (digitalRead(16) == HIGH && bs2 == 1) {
      bs2 = 0;
    }

    if (digitalRead(10) == LOW && relayPeriod > 0 && bs3 == 0) {
      relayPeriod = relayPeriod - 100;
      Rsecond = relayPeriod/1000;
      bs3 = 1;
    }
    else if (digitalRead(10) == HIGH && bs3 == 1) {
      bs3 = 0;
    }
  }
}

void _display() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(0, 10);
  display.print("Mode: ");
  if (DRmode == 0) {
    display.print("Delay");
  }
  else if (DRmode == 1) {
    display.print("Relay");
  }
  display.setCursor(0, 30);
  display.print("Delay: ");
  display.print(Dsecond);
  display.print(" s");
  display.setCursor(0, 50);
  display.print("Relay: ");
  display.print(Rsecond);
  display.print(" s");
  display.display();
  delay(1);
}
