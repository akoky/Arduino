char auth[] = "Eqq8-wRAhZvLJ-Kq9gb0JIkeNJUYTpfp"; //SAVEWO
char ssid[] = "Savewo Lab";
char pass[] = "KenKen2022-";

#define BLYNK_TEMPLATE_ID "TMPLCHKHmFun"
#define BLYNK_DEVICE_NAME "SHT3X溫濕"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include "SHTSensor.h"

SHTSensor sht1(SHTSensor::SHT3X);
BlynkTimer timer;

void sendSensor(){
    float t = sht1.getTemperature();
    float h = sht1.getHumidity();
    Serial.println("Temp: ");
    Serial.print(t);
    Serial.print("  Humid: ");
    Serial.print(h);
    if(sht1.readSample()){
      Blynk.virtualWrite(V0,t);
      Blynk.virtualWrite(V1,h);
    }
  }
  
void setup()
{
  Wire.begin();
  Serial.begin(9600);  

  pinMode(2,OUTPUT);
  
  pinMode(14, OUTPUT);
  Blynk.begin(auth, ssid, pass);

  sht1.init();

  timer.setInterval(1000L, sendSensor);

  digitalWrite(2,LOW);
}


void loop()
{
  Blynk.run();
  timer.run(); 
}
