#define BLYNK_TEMPLATE_ID "TMPLvX7-BeyY"
#define BLYNK_DEVICE_NAME "Rice中菱電機"

char auth[] = "WGaDLcWsygq5Pspowz5ADgp9N4xtZCd6";
char ssid[] = "Savewo Lab";
char pass[] = "KenKen2022-";

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

#define MYPORT_RX 4
#define MYPORT_TX 5

SoftwareSerial mySerial; // RX, TX

byte _Reset[] = {0x01, 0x06, 0x20, 0x0E, 0x00, 0x06, 0x63, 0xCB};

byte _LeftSpeedUp[] = {0x01, 0x06, 0x20, 0x80, 0x05 , 0xDC , 0x81, 0x2B}; // Left Speed Up 1500ms
byte _RightSpeedUp[] = {0x01, 0x06, 0x20, 0x81,  0x05 , 0xDC , 0xD0, 0xEB}; // Right Speed Up 1500ms
byte _LeftSpeedDown[] = {0x01, 0x06, 0x20, 0x82,  0x05 , 0xDC , 0x20, 0xEB}; // Left Speed Down 1500ms
byte _RightSpeedDown[] = {0x01, 0x06, 0x20, 0x83,  0x05 , 0xDC , 0x71, 0x2B}; // Right Speed Down 1500ms

byte _EnableMotor[] = {0x01, 0x06, 0x20, 0x0E, 0x00, 0x08, 0xE2, 0x0F};
byte _DisableMotor[] = {0x01, 0x06, 0x20, 0x0E, 0x00, 0x07, 0xA2, 0x0B};

byte _LeftSetSpeed100[] = {0x01, 0x06, 0x20, 0x88, 0x00, 0x64, 0x03, 0xCB}; // Left Set Speed 100rpm
byte _RightSetSpeedN100[] = {0x01, 0x06, 0x20, 0x89, 0xFF, 0x9C, 0x12, 0x79}; // Right Set Speed -100rpm

byte _LeftSetSpeed50[] = {0x01, 0x06, 0x20, 0x88, 0x00, 0x32, 0x83, 0xF5}; // Left Set Speed 50rpm
byte _RightSetSpeedN50[] = {0x01, 0x06, 0x20, 0x89, 0xFF, 0xCE, 0x93, 0x84}; // Right Set Speed -50rpm

byte _LeftSetSpeed20[] = {0x01, 0x06, 0x20, 0x88, 0x00, 0x14, 0x02, 0x2F}; // Left Set Speed 20rpm
byte _RightSetSpeedN20[] = {0x01, 0x06, 0x20, 0x89, 0xFF, 0xEC, 0x13, 0x9D}; // Right Set Speed -20rpm

byte _LeftSetSpeedN20[] = {0x01, 0x06, 0x20, 0x88, 0xFF, 0xEC, 0x42, 0x5D}; // Left Set Speed -20rpm
byte _RightSetSpeed20[] = {0x01, 0x06, 0x20, 0x89, 0x00, 0x14, 0x53, 0xEF}; // Right Set Speed 20rpm

byte _LeftSetSpeedN100[] = {0x01, 0x06, 0x20, 0x88, 0xFF, 0x9C, 0x43, 0xB9}; // Left Set Speed -100rpm
byte _RightSetSpeed100[] = {0x01, 0x06, 0x20, 0x89, 0x00, 0x64, 0x52, 0x0B}; // Right Set Speed 100rpm

byte _LeftSetSpeedN50[] =  {0x01, 0x06, 0x20, 0x88, 0xFF, 0xCE, 0xC2, 0x44}; // Left Set Speed -50rpm
byte _RightSetSpeed50[] = {0x01, 0x06, 0x20, 0x89, 0x00, 0x32, 0xD2, 0x35}; // Right Set Speed 50rpm

byte _LeftSetSpeed0[] = {0x01, 0x06, 0x20, 0x88, 0x00, 0x00, 0x02, 0x20}; // Left Set Speed 0rpm
byte _RightSetSpeed0[] = {0x01, 0x06, 0x20, 0x89, 0x00, 0x00, 0x53, 0xE0}; // Right Set Speed 0rpm

byte _LeftSetSpeed10[] =  {0x01, 0x06, 0x20, 0x88, 0x00, 0x0A, 0x82, 0x27}; // Left Set Speed 10rpm
byte _RightSetSpeedN10[] = {0x01, 0x06, 0x20, 0x89, 0xFF, 0xF6, 0x92, 0x56}; // Right Set Speed -10rpm

byte _LeftSetSpeedN10[] =  {0x01, 0x06, 0x20, 0x88, 0xFF, 0xF6, 0xC3, 0x96}; // Left Set Speed -10rpm
byte _RightSetSpeed10[] = {0x01, 0x06, 0x20, 0x89, 0x00, 0x0A, 0xD3, 0xE7}; // Right Set Speed 10rpm


void setup()
{
  Serial.begin(115200);
  mySerial.begin(115200, SWSERIAL_8N1, MYPORT_RX, MYPORT_TX, false);
  if (!mySerial) {
    Serial.println("SoftwareSerial false");
    while (1) {
      delay(1000);
    }
  }
  Blynk.begin(auth, ssid, pass);

  Serial.println();
  Serial.println("Reset driver");
  mySerial.write(_Reset, sizeof(_Reset));
  Serial.println("Setting Speed Up/Down Time");
  mySerial.write(_LeftSpeedUp, sizeof(_LeftSpeedUp));
  mySerial.write(_RightSpeedUp, sizeof(_RightSpeedUp));
  mySerial.write(_LeftSpeedDown, sizeof(_LeftSpeedDown));
  mySerial.write(_RightSpeedDown, sizeof(_RightSpeedDown));

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
}

// Enable Motor
BLYNK_WRITE(V0)
{
  if (param.asInt() == 1) {
    Serial.println();
    Serial.println("Enable Motor");
    mySerial.write(_EnableMotor, sizeof(_EnableMotor));
  }
}

// Disable Motor
BLYNK_WRITE(V1)
{
  if (param.asInt() == 1) {
    Serial.println();
    Serial.println("Disable Motor");
    mySerial.write(_DisableMotor, sizeof(_DisableMotor));
  }
}

// Forward 20rpm
BLYNK_WRITE(V2)
{
  if (param.asInt() == 1) {
    Serial.println();
    Serial.println("Set Speed 20");
    mySerial.write(_LeftSetSpeed20, sizeof(_LeftSetSpeed20));
    delay(10);
    mySerial.write(_RightSetSpeedN20, sizeof(_RightSetSpeedN20));
    Blynk.syncVirtual(V2);
  }
  else if (param.asInt() == 0){
    Serial.println();
    Serial.println("Set Speed 0");
    mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
    delay(10);
    mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
    delay(10);
    mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
    delay(10);
    mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
  }
  
}

// 0rpm
BLYNK_WRITE(V3)
{
  if (param.asInt() == 1) {
    Serial.println();
    Serial.println("Set Speed 0");
    mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
    delay(1);
    mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
    Blynk.syncVirtual(V3);
  }
}

// Backward 20rpm
BLYNK_WRITE(V4)
{
  if (param.asInt() == 1) {
    Serial.println();
    Serial.println("Set Speed -20");
    mySerial.write(_LeftSetSpeedN20, sizeof(_LeftSetSpeedN20));
    delay(10);
    mySerial.write(_RightSetSpeed20, sizeof(_RightSetSpeed20));
    Blynk.syncVirtual(V4);
  }
  else if (param.asInt() == 0){
    Serial.println();
    Serial.println("Set Speed 0");
    mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
    delay(10);
    mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
    delay(10);
    mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
    delay(10);
    mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
  }
}

// Turn Right 10rpm
BLYNK_WRITE(V5)
{
  if (param.asInt() == 1) {
    Serial.println();
    Serial.println("Turn right 10");
    mySerial.write(_LeftSetSpeedN10, sizeof(_LeftSetSpeedN10));
    delay(10);
    mySerial.write(_RightSetSpeedN10, sizeof(_RightSetSpeedN10));
    Blynk.syncVirtual(V5);
  }
  else if (param.asInt() == 0){
    Serial.println();
    Serial.println("Set Speed 0");
    mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
    delay(10);
    mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
    delay(10);
    mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
    delay(10);
    mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
  }
}

// Turn Left 10rpm
BLYNK_WRITE(V6)
{
  if (param.asInt() == 1) {
    Serial.println();
    Serial.println("Turn left 10");
    mySerial.write(_LeftSetSpeed10, sizeof(_LeftSetSpeed10));
    delay(10);
    mySerial.write(_RightSetSpeed10, sizeof(_RightSetSpeed10));
    Blynk.syncVirtual(V6);
  }
  else if (param.asInt() == 0){
    Serial.println();
    Serial.println("Set Speed 0");
    mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
    delay(10);
    mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
    delay(10);
    mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
    delay(10);
    mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
  }
}

void loop()
{
  if (mySerial.available() > 0) { // wait for a character
    int incomingByte = mySerial.read();
    Serial.print(incomingByte, HEX);
    Serial.print(' ');
  }
  Blynk.run();
}
