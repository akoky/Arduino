#include <Wire.h>
#include "SHTSensor.h"

// Sensor with normal i2c address
// Sensor 1 with address pin pulled to GND
SHTSensor sht1(SHTSensor::SHT3X);

void setup() {
  Wire.begin();
  Serial.begin(9600);
  delay(1000); 
  
  // initialize sensor with normal i2c-address
  sht1.init();

}

void loop() {
  if (sht1.readSample()) {
    Serial.print("SHT1 :\n");
    Serial.print("  RH: ");
    Serial.print(sht1.getHumidity(), 2);
    Serial.print("\n");
    Serial.print("  T:  ");
    Serial.print(sht1.getTemperature(), 2);
    Serial.print("\n");
  } else {
    Serial.print("Sensor 1: Error in readSample()\n");
  }
 
  delay(1000);
}
