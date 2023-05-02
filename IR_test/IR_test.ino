uint8_t my_serial_bytes[5] = {0xA1, 0xF1, 0x80, 0x7F, 0x01};
uint8_t change[5] = {0xA1, 0xF1, 0x80, 0x7F, 0x06};
int incomingByte = 0;   // for incoming serial data
int bsPreset = 0;

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps

  pinMode(14, OUTPUT);
  digitalWrite(14, HIGH);
}

void loop() {


  //Serial.write(my_serial_bytes, sizeof(my_serial_bytes));

  //delay(1000);

  if (digitalRead(14) == LOW && bsPreset == 0) {
    delay(300);
    Serial.write(change, sizeof(change));
    bsPreset = -1;
  }
  else if ( digitalRead(14) == HIGH) {
    bsPreset = 0;
  }

//  if (Serial.available() > 0) {
//    // read the incoming byte:
//    incomingByte = Serial.read();
//
//    // say what you got:
//    Serial.print("I received: ");
//    Serial.println(incomingByte, HEX);
//    delay(1000);        // delay 5sec
//  }
}
