#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

int counter = 0;
int _timer = 0;
int signalVal = 0;
int sw = 0;
int sw2 = 0;
int sw3 = 0;
int sw4 = 0;
int _passtime = 0;

String GAS_ID = "AKfycbwgaie_-4GgjZGxgpawuh59TgtEh2iODz84ROMXsKnJhAGWnmmU";
char ssid[] = "Savewo Lab";
char pass[] = "KenKen2022-";

const char* host = "script.google.com";
const int httpsPort = 443;

unsigned long previousMillis = 0;
const long period = 300000;

WiFiClientSecure client; //Create a WiFiClientSecure object.

// OLED settings
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);

  delay(2000);

  // OLED Start
  display.begin(i2c_Address, true);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(1);
  display.setCursor(0, 15);
  display.print("SAVEWO");
  display.display();
  delay(2000);

  // 24V siganl pin
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);

  // reset button pin
  pinMode(14, OUTPUT);
  digitalWrite(14, HIGH);
 
  _sendData(0);
  
  Serial.println("Set up finished");
 
 
}

void loop() {
  _maskcounter();
  _button();
  _display();
  _sendDelay();
  _send0();
  delay(1);
}

// counter + 1 when 24V signal is shorted
void _maskcounter() {
  signalVal = analogRead(A0);
  //Serial.println(signalVal);

  if (signalVal > 1000) {
    //Serial.println("24V ON OK");
    if (digitalRead(12) == LOW && sw == 0) {
      delay(1000);
      sw = 1;
      counter++;
      Serial.println(counter);
    }
    else if (digitalRead(12) == HIGH && sw == 1) {
      sw = 0;
    }
  }
  else {
    //Serial.println("NO Signal");
  }
}

// reset counter = 0 when button is pressed
void _button() {
  if (digitalRead(14) == LOW && sw2 == 0) {
    _sendData(counter);
    delay(300);
    sw2 = 1;
    counter = 0;
    Serial.println(counter);
    //delay(1000);
  }
  else if (digitalRead(14) == HIGH && sw2 == 1) {
    sw2 = 0;
  }
}

void _sendData(int num) {

  client.setInsecure();

  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");

    //return;
  }
  String string_counter =  String(num);
  String url = "/macros/s/" + GAS_ID + "/exec?_number=" + string_counter ;

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");
}

void  _display() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(0, 10);
  display.print("Line: 23");
  display.setCursor(0, 30);
  display.print("Mask Produced: ");
  display.println(counter);
  display.setCursor(0, 50);
  if (signalVal >1000) {
    display.print("MAC: ON");
  }
  else {
    display.print("MAC: OFF");
  }
  display.setCursor(60,50);
  display.print(signalVal);
  display.display();
}

void _sendDelay() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= period) {
    previousMillis = currentMillis;
    if (counter != 0) {
      sw3 = 1;
      _sendData(counter);
    }
    else if (counter == 0 && sw3 == 1) {
      sw3 = 0;
    }
  }
}

void _send0() {
  if (counter == 0 && sw4 == 0) {
    _sendData(counter);
    sw4 = 1;
  }
  else if (counter != 0 && sw4 == 1) {
    sw4 = 0;
  }
}
