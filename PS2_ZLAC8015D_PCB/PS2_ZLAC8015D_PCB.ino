#include <PS2X_lib.h>

#include <SoftwareSerial.h>

#define MYPORT_RX 8
#define MYPORT_TX 9

SoftwareSerial mySerial(MYPORT_RX, MYPORT_TX); // RX, TX

PS2X ps2x;

int error = 0;
byte type = 0;
byte vibrate = 0;

int AtomizerState = 0;

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

void setup() {
  Serial.begin(115200);

  pinMode(2, OUTPUT); // Blue LED pin

  pinMode(4, OUTPUT); // Atomizer pin
  digitalWrite(4, LOW);


  pinMode(5, OUTPUT); // Push pull pin
  pinMode(6, OUTPUT); // Push pull pin
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);


  pinMode(MYPORT_RX, INPUT);
  pinMode(MYPORT_TX, OUTPUT);

  mySerial.begin(115200);

  delay(2000);

  //////////////////////////////////////////////////////////////////////////////////////////

  error = ps2x.config_gamepad(15, 14, 10, 16, false, true);
  //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

  if (error == 0) {
    Serial.println("Found Controller, configured successful");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Go to www.billporter.info for updates and to report bugs.");
  }

  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  //Serial.print(ps2x.Analog(1), HEX);

  type = ps2x.readType();

  switch (type) {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
    case 2:
      Serial.println("GuitarHero Controller Found");
      break;
  }

  delay(500);
  //////////////////////////////////////////////////////////////////////////////////////////

  Serial.println();
  Serial.println("Reset driver");
  mySerial.write(_Reset, sizeof(_Reset));
  delay(30);
  Serial.println("Setting Speed Up/Down Time");
  mySerial.write(_LeftSpeedUp750, sizeof(_LeftSpeedUp750));
  delay(30);
  mySerial.write(_RightSpeedUp750, sizeof(_RightSpeedUp750));
  delay(30);
  mySerial.write(_LeftSpeedDown750, sizeof(_LeftSpeedDown750));
  delay(30);
  mySerial.write(_RightSpeedDown750, sizeof(_RightSpeedDown750));
  delay(30);

}



void loop() {
  ps2x.read_gamepad(false, vibrate);

  //////////////////////////////////////////////////////////////////////////////////////////
  //if (mode == 0) {


  if (ps2x.ButtonPressed(PSB_RED)) {
    Serial.println();
    Serial.println("Enable Motor");
    mySerial.write(_EnableMotor, sizeof(_EnableMotor));
    digitalWrite(2, HIGH);
  }

  if (ps2x.ButtonPressed(PSB_BLUE)) {
    Serial.println();
    Serial.println("Disable Motor");
    mySerial.write(_DisableMotor, sizeof(_DisableMotor));
    digitalWrite(2, LOW);
  }

  if (ps2x.ButtonPressed(PSB_GREEN) && digitalRead(5) == LOW && digitalRead(6) == LOW) {
    Serial.println();
    Serial.println("Green Down");
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
  }
  else if (ps2x.ButtonReleased(PSB_GREEN)) {
    Serial.println();
    Serial.println("Green UP");
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }

  if (ps2x.ButtonPressed(PSB_PINK) && digitalRead(5) == LOW && digitalRead(6) == LOW) {
    Serial.println();
    Serial.println("PINK Down");
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
  }
  else if (ps2x.ButtonReleased(PSB_PINK)) {
    Serial.println();
    Serial.println("PINK UP");
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }


  if (ps2x.ButtonPressed(PSB_R1) && digitalRead(4) == LOW) {
    Serial.println();
    Serial.println("R1 HIGH");
    digitalWrite(4, HIGH);
  }
  else if (ps2x.ButtonPressed(PSB_R1) && digitalRead(4) == HIGH) {
    Serial.println();
    Serial.println("R1 LOW");
    digitalWrite(4, LOW);
  }

  ////////////////////////////////// Forward /////////////////////////////////////////////////
  if (ps2x.Button(PSB_PAD_UP) && !ps2x.Button(PSB_PAD_LEFT) && !ps2x.Button(PSB_PAD_RIGHT)) {
    Serial.println();
    Serial.println("PAD just pushed");
    Serial.println("Forward 40rpm");
    mySerial.write(_LeftSetSpeed40, sizeof(_LeftSetSpeed40));
    delay(30);
    mySerial.write(_RightSetSpeedN40, sizeof(_RightSetSpeedN40));
  }
  else if (ps2x.ButtonReleased(PSB_PAD_UP)) {
    Serial.println("0rpm");
    mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
    delay(30);
    mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
    delay(500);
  }

  ////////////////////////////////// Backward /////////////////////////////////////////////////
  if (ps2x.Button(PSB_PAD_DOWN) && !ps2x.Button(PSB_PAD_LEFT) && !ps2x.Button(PSB_PAD_RIGHT)) {
    Serial.println();
    Serial.println("PAD just pushed");
    Serial.println("Backward 40rpm");
    mySerial.write(_LeftSetSpeedN40, sizeof(_LeftSetSpeedN40));
    delay(30);
    mySerial.write(_RightSetSpeed40, sizeof(_RightSetSpeed40));
  }
  else if (ps2x.ButtonReleased(PSB_PAD_DOWN)) {
    Serial.println("0rpm");
    mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
    delay(30);
    mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
    delay(500);
  }

  ////////////////////////////////// Left /////////////////////////////////////////////////
  if (ps2x.Button(PSB_PAD_LEFT) && !ps2x.Button(PSB_PAD_UP) && !ps2x.Button(PSB_PAD_DOWN)) {
    Serial.println();
    Serial.println("PAD just pushed");
    Serial.println("Left 20rpm");
    mySerial.write(_LeftSetSpeedN20, sizeof(_LeftSetSpeedN20));
    delay(30);
    mySerial.write(_RightSetSpeedN20, sizeof(_RightSetSpeedN20));
  }
  else if (ps2x.ButtonReleased(PSB_PAD_LEFT)) {
    Serial.println("0rpm");
    mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
    delay(30);
    mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
    delay(500);
  }

  ////////////////////////////////// Right /////////////////////////////////////////////////
  if (ps2x.Button(PSB_PAD_RIGHT) && !ps2x.Button(PSB_PAD_UP) && !ps2x.Button(PSB_PAD_DOWN)) {
    Serial.println();
    Serial.println("PAD just pushed");
    Serial.println("Right 20rpm");
    mySerial.write(_LeftSetSpeed20, sizeof(_LeftSetSpeed20));
    delay(30);
    mySerial.write(_RightSetSpeed20, sizeof(_RightSetSpeed20));
  }
  else if (ps2x.ButtonReleased(PSB_PAD_RIGHT)) {
    Serial.println("0rpm");
    mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
    delay(30);
    mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
    delay(500);
  }
  //}

  //////////////////////////////////////////////////////////////////////////////////////////

  //    if (mode == 1) {
  //
  //      if (ps2x.ButtonPressed(PSB_RED)) {
  //        Serial.println();
  //        Serial.println("O just pressed");
  //        Serial.println("Enable Motor");
  //        mySerial.write(_EnableMotor, sizeof(_EnableMotor));
  //        digitalWrite(3, HIGH);
  //      }
  //
  //      if (ps2x.ButtonPressed(PSB_BLUE)) {
  //        Serial.println();
  //        Serial.println("Disable Motor");
  //        mySerial.write(_DisableMotor, sizeof(_DisableMotor));
  //        digitalWrite(3, LOW);
  //      }
  //
  //      if (ps2x.ButtonPressed(PSB_R1)) {
  //        Serial.println();
  //        Serial.println("R1 just pressed");
  //        Serial.println("Change Speed Mode");
  //        mode = 0;
  //      }
  //
  //      if (ps2x.Button(PSB_PAD_UP)) {
  //        Serial.println();
  //        Serial.println("PAD just pushed");
  //        Serial.println("Forward 100rpm");
  //        mySerial.write(_LeftSetSpeed100, sizeof(_LeftSetSpeed100));
  //        delay(20);
  //        mySerial.write(_RightSetSpeedN100, sizeof(_RightSetSpeedN100));
  //      }
  //      else if (ps2x.ButtonReleased(PSB_PAD_UP)) {
  //        Serial.println("0rpm");
  //        mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
  //        delay(20);
  //        mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
  //        delay(400);
  //      }
  //
  //
  //      if (ps2x.Button(PSB_PAD_DOWN)) {
  //        Serial.println();
  //        Serial.println("PAD just pushed");
  //        Serial.println("Backward 100rpm");
  //        mySerial.write(_LeftSetSpeedN100, sizeof(_LeftSetSpeedN100));
  //        delay(20);
  //        mySerial.write(_RightSetSpeed100, sizeof(_RightSetSpeed100));
  //      }
  //      else if (ps2x.ButtonReleased(PSB_PAD_DOWN)) {
  //        Serial.println("0rpm");
  //        mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
  //        delay(20);
  //        mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
  //        delay(400);
  //      }
  //
  //      if (ps2x.Button(PSB_PAD_LEFT)) {
  //        Serial.println();
  //        Serial.println("PAD just pushed");
  //        Serial.println("Left 50rpm");
  //        mySerial.write(_LeftSetSpeedN50, sizeof(_LeftSetSpeedN50));
  //        delay(20);
  //        mySerial.write(_RightSetSpeedN50, sizeof(_RightSetSpeedN50));
  //      }
  //      else if (ps2x.ButtonReleased(PSB_PAD_LEFT)) {
  //        Serial.println("0rpm");
  //        mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
  //        delay(20);
  //        mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
  //        delay(400);
  //      }
  //
  //      if (ps2x.Button(PSB_PAD_RIGHT)) {
  //        Serial.println();
  //        Serial.println("PAD just pushed");
  //        Serial.println("Right 50rpm");
  //        mySerial.write(_LeftSetSpeed50, sizeof(_LeftSetSpeed50));
  //        delay(20);
  //        mySerial.write(_RightSetSpeed50, sizeof(_RightSetSpeed50));
  //      }
  //      else if (ps2x.ButtonReleased(PSB_PAD_RIGHT)) {
  //        Serial.println("0rpm");
  //        mySerial.write(_LeftSetSpeed0, sizeof(_LeftSetSpeed0));
  //        delay(20);
  //        mySerial.write(_RightSetSpeed0, sizeof(_RightSetSpeed0));
  //        delay(400);
  //      }
  //    }
  //////////////////////////////////////////////////////////////////////////////////////////


  delay(10);


  //  if (mySerial.available() > 0) { // wait for a character
  //    int incomingByte = mySerial.read();
  //    Serial.print(incomingByte, HEX);
  //    Serial.print(' ');
  //  }

}
