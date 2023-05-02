#include <PS4Controller.h>

//////////////////////////////////////////////////////////////////////////////////////////

byte _Reset[] = {0x01, 0x06, 0x20, 0x0E, 0x00, 0x06, 0x63, 0xCB};

byte _LeftSpeedUp1000[] = {0x01, 0x06, 0x20, 0x80, 0x03 , 0xE8 , 0x83, 0x5C}; // Left Speed Up 1000ms
byte _RightSpeedUp1000[] = {0x01, 0x06, 0x20, 0x81, 0x03 , 0xE8 , 0xD2, 0x9C}; // Right Speed Up 1000ms
byte _LeftSpeedDown1000[] = {0x01, 0x06, 0x20, 0x82, 0x03 , 0xE8 , 0x22, 0x9C}; // Left Speed Down 1000ms
byte _RightSpeedDown1000[] = {0x01, 0x06, 0x20, 0x83, 0x03 , 0xE8 , 0x73, 0x5C}; // Right Speed Down 1000ms

byte _LeftSpeedUp750[] = {0x01, 0x06, 0x20, 0x80, 0x02 , 0xEE , 0x02, 0xCE}; // Left Speed Up 750ms
byte _RightSpeedUp750[] = {0x01, 0x06, 0x20, 0x81,  0x02 , 0xEE , 0x53, 0x0E}; // Right Speed Up 750ms
byte _LeftSpeedDown750[] = {0x01, 0x06, 0x20, 0x82,  0x02 , 0xEE , 0xA3, 0x0E}; // Left Speed Down 750ms
byte _RightSpeedDown750[] = {0x01, 0x06, 0x20, 0x83,  0x02 , 0xEE , 0xF2, 0xCE}; // Right Speed Down 750ms

byte _LeftSpeedUp500[] = {0x01, 0x06, 0x20, 0x80, 0x01 , 0xF4 , 0x83, 0xF5}; // Left Speed Up 500ms
byte _RightSpeedUp500[] = {0x01, 0x06, 0x20, 0x81,  0x01 , 0xF4 , 0xD2, 0x35}; // Right Speed Up 500ms
byte _LeftSpeedDown500[] = {0x01, 0x06, 0x20, 0x82,  0x01 , 0xF4 , 0x22, 0x35}; // Left Speed Down 500ms
byte _RightSpeedDown500[] = {0x01, 0x06, 0x20, 0x83,  0x01 , 0xF4 , 0x73, 0xF5}; // Right Speed Down 500ms

byte _EnableMotor[] = {0x01, 0x06, 0x20, 0x0E, 0x00, 0x08, 0xE2, 0x0F};
byte _DisableMotor[] = {0x01, 0x06, 0x20, 0x0E, 0x00, 0x07, 0xA2, 0x0B};

byte _LeftSetSpeed20[] = {0x01, 0x06, 0x20, 0x88, 0x00, 0x14, 0x02, 0x2F}; // Left Set Speed 20rpm
byte _RightSetSpeedN20[] = {0x01, 0x06, 0x20, 0x89, 0xFF, 0xEC, 0x13, 0x9D}; // Right Set Speed -20rpm

byte _LeftSetSpeedN20[] = {0x01, 0x06, 0x20, 0x88, 0xFF, 0xEC, 0x42, 0x5D}; // Left Set Speed -20rpm
byte _RightSetSpeed20[] = {0x01, 0x06, 0x20, 0x89, 0x00, 0x14, 0x53, 0xEF}; // Right Set Speed 20rpm

byte _LeftSetSpeed40[] = {0x01, 0x06, 0x20, 0x88, 0x00, 0x28, 0x02, 0x3E}; // Left Set Speed 40rpm
byte _RightSetSpeedN40[] = {0x01, 0x06, 0x20, 0x89, 0xFF, 0xD8, 0x12, 0x4A}; // Right Set Speed -40rpm

byte _LeftSetSpeedN40[] = {0x01, 0x06, 0x20, 0x88, 0xFF, 0xD8, 0x43, 0x8A}; // Left Set Speed -40rpm
byte _RightSetSpeed40[] = {0x01, 0x06, 0x20, 0x89, 0x00, 0x28, 0x53, 0xFE}; // Right Set Speed 40rpm

byte _LeftSetSpeed50[] = {0x01, 0x06, 0x20, 0x88, 0x00, 0x32, 0x83, 0xF5}; // Left Set Speed 50rpm
byte _RightSetSpeedN50[] = {0x01, 0x06, 0x20, 0x89, 0xFF, 0xCE, 0x93, 0x84}; // Right Set Speed -50rpm

byte _LeftSetSpeedN50[] =  {0x01, 0x06, 0x20, 0x88, 0xFF, 0xCE, 0xC2, 0x44}; // Left Set Speed -50rpm
byte _RightSetSpeed50[] = {0x01, 0x06, 0x20, 0x89, 0x00, 0x32, 0xD2, 0x35}; // Right Set Speed 50rpm

byte _LeftSetSpeed100[] = {0x01, 0x06, 0x20, 0x88, 0x00, 0x64, 0x03, 0xCB}; // Left Set Speed 100rpm
byte _RightSetSpeedN100[] = {0x01, 0x06, 0x20, 0x89, 0xFF, 0x9C, 0x12, 0x79}; // Right Set Speed -100rpm

byte _LeftSetSpeedN100[] = {0x01, 0x06, 0x20, 0x88, 0xFF, 0x9C, 0x43, 0xB9}; // Left Set Speed -100rpm
byte _RightSetSpeed100[] = {0x01, 0x06, 0x20, 0x89, 0x00, 0x64, 0x52, 0x0B}; // Right Set Speed 100rpm

byte _LeftSetSpeed0[] = {0x01, 0x06, 0x20, 0x88, 0x00, 0x00, 0x02, 0x20}; // Left Set Speed 0rpm
byte _RightSetSpeed0[] = {0x01, 0x06, 0x20, 0x89, 0x00, 0x00, 0x53, 0xE0}; // Right Set Speed 0rpm
//////////////////////////////////////////////////////////////////////////////////////////

#define MYPORT_RX 16
#define MYPORT_TX 17

int CirSt = 0;
int CroSt = 0;
int TriSt = 0;
int SquSt = 0;
int UpSt = 0;
int BackSt = 0;
int LtSt = 0;
int RtSt = 0;

void setup() {
  Serial.begin(115200);
  PS4.begin("24:4c:ab:e2:e5:5e");

  pinMode(MYPORT_RX, INPUT);
  pinMode(MYPORT_TX, OUTPUT);

  pinMode(23, OUTPUT); // POWER pin
  digitalWrite(23, LOW);

  pinMode(18, OUTPUT); // Rod pin A
  digitalWrite(18, LOW);

  pinMode(19, OUTPUT); // Rod pin B
  digitalWrite(19, LOW);

  Serial2.begin(115200, SERIAL_8N1, MYPORT_RX, MYPORT_TX);

  delay(1000);

  Serial.println();
  Serial.println("Reset driver");
  Serial2.write(_Reset, sizeof(_Reset));
  delay(30);

  Serial.println("Setting Speed Up/Down Time");
  Serial2.write(_LeftSpeedUp750, sizeof(_LeftSpeedUp750));
  delay(30);
  Serial2.write(_RightSpeedUp750, sizeof(_RightSpeedUp750));
  delay(30);
  Serial2.write(_LeftSpeedDown750, sizeof(_LeftSpeedDown750));
  delay(30);
  Serial2.write(_RightSpeedDown750, sizeof(_RightSpeedDown750));
  delay(30);

}

void loop() {

  if (PS4.isConnected()) {

    //PS4.event.button_down.circle
    if (PS4.Circle() && CirSt == 0) {
      Serial.println();
      Serial.println("Enable Motor");
      CirSt = 1;
      Serial2.write(_EnableMotor, sizeof(_EnableMotor));
      digitalWrite(23, HIGH);
    }
    else if ( !PS4.Circle() && CirSt == 1) {
      CirSt = 0;
    }

    if (PS4.Cross() && CroSt == 0) {
      Serial.println();
      Serial.println("Disable Motor");
      CroSt = 1;
      Serial2.write(_DisableMotor, sizeof(_DisableMotor));
      digitalWrite(23, LOW);
    } else if (!PS4.Cross() && CroSt == 1) {
      CroSt = 0;
    }

    if (PS4.Square() && SquSt == 0) {
      Serial.println();
      Serial.println("Square Pressed");
      digitalWrite(18, HIGH);
      SquSt = 1;
    } else if (!PS4.Square() && SquSt == 1) {
      Serial.println();
      Serial.println("Square Released");
      digitalWrite(18, LOW);
      SquSt = 0;
    }

    if (PS4.Triangle() && TriSt == 0) {
      Serial.println();
      Serial.println("Triangle Pressed");
      digitalWrite(19, HIGH);
      TriSt = 1;
    } else if (!PS4.Triangle() && TriSt == 1) {
      Serial.println();
      Serial.println("Triangle Released");
      digitalWrite(19, LOW);
      TriSt = 0;
    }

    ////////////////////////////////// Forward /////////////////////////////////////////////////
    if (PS4.Up() && !PS4.Down() && !PS4.Right() && !PS4.Left() && UpSt == 0) {
      Serial.println();
      Serial.println("Up Pressed");
      UpSt = 1;
      Serial2.write(_LeftSetSpeed40, sizeof(_LeftSetSpeed40));
      delay(30);
      Serial2.write(_RightSetSpeedN40, sizeof(_RightSetSpeedN40));
    } else if (!PS4.Up() && UpSt == 1) {
      Serial.println();
      Serial.println("Up Released");
      UpSt = 0;
      Serial2.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
      delay(30);
      Serial2.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
      delay(500);
    }

    ////////////////////////////////// Backward /////////////////////////////////////////////////
    if (!PS4.Up() && PS4.Down() && !PS4.Right() && !PS4.Left() && BackSt == 0) {
      Serial.println();
      Serial.println("Down Pressed");
      BackSt = 1;
      Serial2.write(_LeftSetSpeedN40, sizeof(_LeftSetSpeedN40));
      delay(30);
      Serial2.write(_RightSetSpeed40, sizeof(_RightSetSpeed40));
    } else if (!PS4.Down() && BackSt == 1) {
      Serial.println();
      Serial.println("Down Released");
      BackSt = 0;
      Serial2.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
      delay(30);
      Serial2.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
      delay(500);
    }

    ////////////////////////////////// Left /////////////////////////////////////////////////
    if (!PS4.Up() && !PS4.Down() && !PS4.Right() && PS4.Left() && LtSt == 0) {
      Serial.println();
      Serial.println("Left Pressed");
      LtSt = 1;
      Serial2.write(_LeftSetSpeedN20, sizeof(_LeftSetSpeedN20));
      delay(30);
      Serial2.write(_RightSetSpeedN20, sizeof(_RightSetSpeedN20));
    } else if (!PS4.Left() && LtSt == 1) {
      Serial.println();
      Serial.println("Left Released");
      LtSt = 0;
      Serial2.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
      delay(30);
      Serial2.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
      delay(500);
    }

    ////////////////////////////////// Right /////////////////////////////////////////////////
    if (!PS4.Up() && !PS4.Down() && PS4.Right() && !PS4.Left() && RtSt == 0) {
      Serial.println();
      Serial.println("Right Pressed");
      RtSt = 1;
      Serial2.write(_LeftSetSpeed20, sizeof(_LeftSetSpeed20));
      delay(30);
      Serial2.write(_RightSetSpeed20, sizeof(_RightSetSpeed20));
    } else if (!PS4.Right() && RtSt == 1) {
      Serial.println();
      Serial.println("Right Released");
      RtSt = 0;
      Serial2.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
      delay(30);
      Serial2.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
      delay(500);
    }
  }
}
