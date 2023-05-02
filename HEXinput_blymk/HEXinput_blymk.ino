#define BLYNK_TEMPLATE_ID "TMPLvX7-BeyY"
#define BLYNK_DEVICE_NAME "Rice中菱電機"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

char auth[] = "WGaDLcWsygq5Pspowz5ADgp9N4xtZCd6";
char ssid[] = "Savewo Lab";
char pass[] = "KenKen2022-";

#define MYPORT_RX 4
#define MYPORT_TX 5

SoftwareSerial mySerial; // RX, TX

byte _ReadSpeed[] = {0x01, 0x03, 0x20, 0x2C, 0x00, 0x01, 0x4E, 0x03};

byte _SpeedMode[] = {0x01, 0x06, 0x20, 0x32, 0x00, 0x03, 0x63, 0xC4};
byte _SpeedUp[] = {0x01, 0x06, 0x20, 0x37, 0x01, 0xF4, 0x33, 0xD3};
byte _SpeedDown[] = {0x01, 0x06, 0x20, 0x38, 0x01, 0xF4, 0x03, 0xD0};
byte _EnableMotor[] = {0x01, 0x06, 0x20, 0x31, 0x00, 0x08, 0xD2, 0x03};
byte _SetSpeed[] = {0x01, 0x06, 0x20, 0x3A, 0x00, 0x64, 0xA3, 0xEC};
byte _DisableMotor[] = {0x01, 0x06, 0x20, 0x31, 0x00, 0x07, 0x92, 0x07};

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  mySerial.begin(115200, SWSERIAL_8N1, MYPORT_RX, MYPORT_TX, false);
  if (!mySerial) {
    Serial.println("SoftwareSerial false");
    while (1) {
      delay(1000);
    }
  }
  delay(1000);

  Serial.println("send HEX [see code]");
  //mySerial.write(_SpeedMode, sizeof(_SpeedMode));
  //mySerial.write(_SpeedUp, sizeof(_SpeedUp));
  //mySerial.write(_SpeedDown, sizeof(_SpeedDown));
  // mySerial.write(_EnableMotor, sizeof(_EnableMotor));
  //  mySerial.write(_SetSpeed, sizeof(_SetSpeed));
  //  mySerial.write(_ReadSpeed, sizeof(_ReadSpeed));
  //  mySerial.write(_DisableMotor, sizeof(_EnableMotor));
  Serial.println("read HEX");
}


BLYNK_WRITE(V0) //SpeedMode
{
  int i = param.asInt();
  if (i == 1) {
    mySerial.write(_SpeedMode, sizeof(_SpeedMode));
  }
  else {
  }
}
BLYNK_WRITE(V1) //SpeedUp
{
  int i = param.asInt();
  if (i == 1) {
    mySerial.write(_SpeedUp, sizeof(_SpeedUp));
  }
  else {
  }
}
BLYNK_WRITE(V3) //SetSpeed
{
  int i = param.asInt();
  if (i == 1) {
    mySerial.write(_SetSpeed, sizeof(_SetSpeed));
  }
  else {
  }
}
BLYNK_WRITE(V2) //EnableMotor
{
  int i = param.asInt();
  if (i == 1) {
    mySerial.write(_EnableMotor, sizeof(_EnableMotor));
  }
  else {
  }
}
BLYNK_WRITE(V4) //SpeedDown
{
  int i = param.asInt();
  if (i == 1) {
    mySerial.write(_SpeedDown, sizeof(_SpeedDown));
  }
  else {
  }
}

// the loop function runs over and over again forever
void loop() {
  Blynk.run();
  for (int i = 0; i < 23; i++) {
    while (!mySerial.available()); // wait for a character
    int incomingByte = mySerial.read();
    Serial.print(incomingByte, HEX);
    Serial.print(' ');
  }
  Serial.println();
}
