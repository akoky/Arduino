#include <SoftwareSerial.h>

#define MYPORT_RX 8
#define MYPORT_TX 9

SoftwareSerial mySerial(8, 9); // RX, TX

int buttonState = 0;
boolean motorState = false;

int dirX = 0;
int dirY = 0;

int counterFwd = 0;
int counterBwd = 0;
int counterLft = 0;
int counterRgt = 0;

//////////////////////////////////////////////////////////////////////////////////////////

byte _Reset[] = {0x01, 0x06, 0x20, 0x0E, 0x00, 0x06, 0x63, 0xCB};

byte _LeftSpeedUp1000[] = {0x01, 0x06, 0x20, 0x80, 0x03 , 0xE8 , 0x83, 0x5C}; // Left Speed Up 1000ms
byte _RightSpeedUp1000[] = {0x01, 0x06, 0x20, 0x81, 0x03 , 0xE8 , 0xD2, 0x9C}; // Right Speed Up 1000ms
byte _LeftSpeedDown1000[] = {0x01, 0x06, 0x20, 0x82, 0x03 , 0xE8 , 0x22, 0x9C}; // Left Speed Down 1000ms
byte _RightSpeedDown1000[] = {0x01, 0x06, 0x20, 0x83, 0x03 , 0xE8 , 0x73, 0x5C}; // Right Speed Down 1000ms

byte _LeftSpeedUp500[] = {0x01, 0x06, 0x20, 0x80, 0x01 , 0xF4 , 0x83, 0xF5}; // Left Speed Up 500ms
byte _RightSpeedUp500[] = {0x01, 0x06, 0x20, 0x81,  0x01 , 0xF4 , 0xD2, 0x35}; // Right Speed Up 500ms
byte _LeftSpeedDown500[] = {0x01, 0x06, 0x20, 0x82,  0x01 , 0xF4 , 0x22, 0x35}; // Left Speed Down 500ms
byte _RightSpeedDown500[] = {0x01, 0x06, 0x20, 0x83,  0x01 , 0xF4 , 0x73, 0xF5}; // Right Speed Down 500ms

byte _EnableMotor[] = {0x01, 0x06, 0x20, 0x0E, 0x00, 0x08, 0xE2, 0x0F};
byte _DisableMotor[] = {0x01, 0x06, 0x20, 0x0E, 0x00, 0x07, 0xA2, 0x0B};

byte _LeftSetSpeed10[] = {0x01, 0x06, 0x20, 0x88, 0x00, 0x0A, 0x82, 0x27}; // Left Set Speed 10rpm
byte _RightSetSpeedN10[] = {0x01, 0x06, 0x20, 0x89, 0xFF, 0xF6, 0x92, 0x56}; // Right Set Speed -10rpm

byte _LeftSetSpeedN10[] = {0x01, 0x06, 0x20, 0x88, 0xFF, 0xF6, 0xC3, 0x96}; // Left Set Speed -10rpm
byte _RightSetSpeed10[] = {0x01, 0x06, 0x20, 0x89, 0x00, 0x0A, 0xD3, 0xE7}; // Right Set Speed 10rpm

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

void setup() {
  Serial.begin(115200);

  mySerial.begin(115200);
  if (!mySerial) {
    Serial.println("SoftwareSerial false");
    while (1) {
      delay(1000);
    }
  }

  delay(2000);

  Serial.println();
  Serial.println("Reset driver");
  mySerial.write(_Reset, sizeof(_Reset));
  delay(20);
  Serial.println("Setting Speed Up/Down Time");
  mySerial.write(_LeftSpeedUp500, sizeof(_LeftSpeedUp500));
  delay(20);
  mySerial.write(_RightSpeedUp500, sizeof(_RightSpeedUp500));
  delay(20);
  mySerial.write(_LeftSpeedDown500, sizeof(_LeftSpeedDown500));
  delay(20);
  mySerial.write(_RightSpeedDown500, sizeof(_RightSpeedDown500));
  delay(20);


  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);

}



void loop() {
  _joystick();
  _serialprinting();
  delay(1);
}

void _joystick() {

  //////////////////////////////////// Joystick Setup //////////////////////////////////////
  int x = analogRead(A0);
  int y = analogRead(A1);

  if (x < 100) {
    dirX = 0;
  } else if (x > 1000) {
    dirX = 2;
  } else {
    dirX = 1;
  }

  if (y < 100) {
    dirY = 0;
  } else if (y > 1000) {
    dirY = 2;
  } else {
    dirY = 1;
  }

  //////////////////////////////////// Enable Motor ////////////////////////////////////////
  if (digitalRead(3) == LOW && buttonState == 0 && motorState == false) {
    buttonState = 1;
    Serial.println();
    Serial.println("Enable Motor");
    mySerial.write(_EnableMotor, sizeof(_EnableMotor));
    delay(20);
    digitalWrite(2,HIGH);
    motorState = true;
  }
  else if (digitalRead(3) == HIGH && buttonState == 1 && motorState == true) {
    buttonState = 0;
  }

  //////////////////////////////////// Disable Motor ///////////////////////////////////////
  if (digitalRead(3) == LOW && buttonState == 0 && motorState == true) {
    buttonState = 1;
    Serial.println();
    Serial.println("Disable Motor");
    mySerial.write(_DisableMotor, sizeof(_DisableMotor));
    delay(20);
    digitalWrite(2,LOW);
    motorState = false;
  }
  else if (digitalRead(3) == HIGH && buttonState == 1 && motorState == false) {
    buttonState = 0;
  }

  ////////////////////////////////////// Foward ////////////////////////////////////////////
  if (dirY == 0 && dirX == 1 && counterFwd == 0) {
    Serial.println();
    Serial.println("Forward 20rpm");
    mySerial.write(_LeftSetSpeed20, sizeof(_LeftSetSpeed20));
    delay(20);
    mySerial.write(_RightSetSpeedN20, sizeof(_RightSetSpeedN20));
    counterFwd = 1;
  }
  else if ( dirY == 1 && dirX == 1 && counterFwd == 1) {
    Serial.println("0rpm");
    mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
    delay(20);
    mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
    counterFwd = 0;
    delay(400);
  }

  /////////////////////////////////////// Backward /////////////////////////////////////////
  if (dirY == 2 && dirX == 1 && counterBwd == 0) {
    Serial.println();
    Serial.println("Backward 20rpm");
    mySerial.write(_LeftSetSpeedN20, sizeof(_LeftSetSpeedN20));
    delay(20);
    mySerial.write(_RightSetSpeed20, sizeof(_RightSetSpeed20));
    counterBwd = 1;
  }
  else if ( dirY == 1 && dirX == 1 && counterBwd == 1) {
    Serial.println("0rpm");
    mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
    delay(20);
    mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
    counterBwd = 0;
    delay(400);
  }

  ///////////////////////////////////////// Left ///////////////////////////////////////////
  if (dirY == 1 && dirX == 0 && counterLft == 0) {
    Serial.println();
    Serial.println("Left 20rpm");
    mySerial.write(_LeftSetSpeedN10, sizeof(_LeftSetSpeedN10));
    delay(20);
    mySerial.write(_RightSetSpeedN10, sizeof(_RightSetSpeedN10));
    counterLft = 1;
  }
  else if ( dirY == 1 && dirX == 1 && counterLft == 1) {
    Serial.println("0rpm");
    mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
    delay(20);
    mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
    counterLft = 0;
    delay(400);
  }

  ///////////////////////////////////////// Right //////////////////////////////////////////
  if (dirY == 1 && dirX == 2 && counterRgt == 0) {
    Serial.println();
    Serial.println("Right 20rpm");
    mySerial.write(_LeftSetSpeed10, sizeof(_LeftSetSpeed10));
    delay(20);
    mySerial.write(_RightSetSpeed10, sizeof(_RightSetSpeed10));
    counterRgt = 1;
  }
  else if ( dirY == 1 && dirX == 1 && counterRgt == 1) {
    Serial.println("0rpm");
    mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
    delay(20);
    mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
    counterRgt = 0;
    delay(400);
  }
  //////////////////////////////////////////////////////////////////////////////////////////

  //  Serial.println(" ");
  //  Serial.print("Axis X = ");
  //  Serial.print(x);
  //  Serial.print(" ,");
  //  Serial.print("Axis Y = ");
  //  Serial.print(y);
  //  Serial.print(" ,");
  //  Serial.print("ButtonState = ");
  //  Serial.println(buttonState);
  delay(1);

}

void _serialprinting() {
  if (mySerial.available() > 0) { // wait for a character
    int incomingByte = mySerial.read();
    Serial.print(incomingByte, HEX);
    Serial.print(' ');
  }
}
