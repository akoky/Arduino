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

int CLK = 13;
int DT = 16;

int rotation;
int value;

int buttonSt = 0;

void setup() {
  Serial.begin(9600);

  delay(1000);

  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);

  rotation = digitalRead(CLK);

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

  //esp running
  pinMode(2, OUTPUT);
  digitalWrite(2,HIGH);
}

void loop() {
  _relaycontrol();
  _encoder();
  _display();
  //Serial.println(Dsecond);
  Serial.println(DRmode);
  delay(1);
}


void _relaycontrol() {
  if (digitalRead(12) == HIGH) {
    digitalWrite(14, LOW);
  }
  else if (digitalRead(12) == LOW) {
    delay(delaycount);
    digitalWrite(14, HIGH);
    delay(relayPeriod);
  }
}

void _encoder() {
  ////////////////// Delay mode //////////////////
  if (DRmode == 0)
  {
    value = digitalRead(CLK);
    if (value != rotation) { // we use the DT pin to find out which way we turning.
      if (digitalRead(DT) != value) {
        // Clockwise
        delaycount = delaycount - 100;
        Dsecond = delaycount / 1000;

      } else {
        //Counterclockwise
        delaycount = delaycount + 100;
        Dsecond = delaycount / 1000;

      }
    }
    rotation = value;

    if (digitalRead(2) == LOW && buttonSt == 0) {
      DRmode = 1;
      buttonSt = 1;
    } else if (digitalRead(2) == HIGH && buttonSt == 1) {
      buttonSt = 0;
    }
  }
  ////////////////// Relay mode //////////////////
  else if (DRmode == 1)
  {
    value = digitalRead(CLK);
    if (value != rotation) { // we use the DT pin to find out which way we turning.
      if (digitalRead(DT) != value) {
        // Clockwise
        relayPeriod = relayPeriod - 100;
        Rsecond = relayPeriod / 1000;

      } else {
        //Counterclockwise
        relayPeriod = relayPeriod + 100;
        Rsecond = relayPeriod / 1000;

      }
    }
    rotation = value;

    if (digitalRead(2) == LOW && buttonSt == 0) {
      DRmode = 0;
      buttonSt = 1;
    } else if (digitalRead(2) == HIGH && buttonSt == 1) {
      buttonSt = 0;
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
