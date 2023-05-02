#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

byte _Reset[] = {0x01, 0x06, 0x20, 0x0E, 0x00, 0x06, 0x63, 0xCB};

#define MYPORT_RX 16
#define MYPORT_TX 17

int button = 0;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32"); 

  pinMode(MYPORT_RX, INPUT);
  pinMode(MYPORT_TX, OUTPUT);

  pinMode(23, OUTPUT);
  digitalWrite(23, HIGH);

  Serial2.begin(115200, SERIAL_8N1, MYPORT_RX, MYPORT_TX);

  delay(1000);
}

void loop() {
  if (digitalRead(23) == LOW && button == 0) {
    Serial2.write(_Reset, sizeof(_Reset));
    delay(30);
    button = 1;
  }
  else if ( digitalRead(23) == HIGH && button == 1) {
    button = 0;
  }

  if (Serial2.available()) {
    SerialBT.write(Serial2.read());
  }
  if (SerialBT.available()) {
    Serial2.write(SerialBT.read());
  }
  delay(20);
}
