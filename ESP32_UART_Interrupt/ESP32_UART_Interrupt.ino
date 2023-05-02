#define RXD2 16
#define TXD2 17

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  pinMode(2, OUTPUT);

}

void loop() {
  
  digitalWrite(2, HIGH);
  delay(5000);
  digitalWrite(2, LOW);
  delay(5000);

  while(Serial2.available()){
    Serial.print(char(Serial2.read()));
  }

}
