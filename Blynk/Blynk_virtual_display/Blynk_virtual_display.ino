char auth[] = "NezKCyLgnWkOV4IwMQR68ItpIFxLghqq"; //SAVEWO

char ssid[] = "Savewo Lab";
char pass[] = "KenKen2022-";

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

int _timer = 0;
int _test1;
int _test2;

void setup()
{
  Serial.begin(9600);  
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  _timer++;
  if(_timer >= 2000){
    _test1 = random(100);
    Blynk.virtualWrite(V0, _test1);
    _test2 = random(100);
    Blynk.virtualWrite(V1, _test2);
    _timer = 0;
  }
  delay(1);
}
