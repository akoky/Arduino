#include <SoftwareSerial.h>

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
byte _RunningMode[8] ={0x01, 0x06, 0x20, 0x31, 0x00, 0x10, 0xD2, 0x09};

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  mySerial.begin(115200, SWSERIAL_8N1, MYPORT_RX, MYPORT_TX, false);
  if (!mySerial) {
    Serial.println("SoftwareSerial false");
    while (1) {
      delay(1000);
    }
  }
  delay(1000);

  Serial.println("send HEX [see code]");
//  mySerial.write(_RunningMode, sizeof(_RunningMode));
//  mySerial.write(_SpeedMode, sizeof(_SpeedMode));
// mySerial.write(_SpeedUp, sizeof(_SpeedUp));
//  mySerial.write(_SpeedDown, sizeof(_SpeedDown));

//mySerial.write(_EnableMotor, sizeof(_EnableMotor));
//  mySerial.write(_SetSpeed, sizeof(_SetSpeed));
//  mySerial.write(_ReadSpeed, sizeof(_ReadSpeed));
  mySerial.write(_DisableMotor, sizeof(_EnableMotor));

  Serial.println("read HEX");
}

// the loop function runs over and over again forever
void loop() {
  for (int i=0; i<23; i++) {
      while(!mySerial.available()); // wait for a character
    int incomingByte = mySerial.read();
    Serial.print(incomingByte,HEX);
    Serial.print(' ');
    }
    Serial.println();
}
