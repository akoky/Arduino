
char ssid[] = "Savewo Lab";
char pass[] = "KenKen2022-";
char auth[] = "Pyf7tbe1P-6TUgN2zjf8-a_GKP1HVNOB";


#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

WidgetRTC rtc;

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  rtc.begin();
  delay(1000);
}

void loop()
{
  Blynk.run();
  Serial.println(String(hour()) + ":" + minute() + ":" + second()+"  "+day() + " " + month() + " " + year());
  delay(5000);
}
