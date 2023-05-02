char auth[] = "GV2cfWeNv0vN8ktHFG0_Mr5dVQgT27al"; //SAVEWO
char ssid[] = "Savewo Lab";
char pass[] = "KenKen2022-";

#define BLYNK_TEMPLATE_ID "TMPLuAehO9zo"
#define BLYNK_DEVICE_NAME "LEDtest"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

void setup()
{
  Serial.begin(9600);  
  pinMode(14, OUTPUT);
  Blynk.begin(auth, ssid, pass);
}

BLYNK_WRITE(V0)
  {
    int i = param.asInt();
    Serial.println(param.asInt());
    if(i==1){
      digitalWrite(14,HIGH);
    }
    else
      digitalWrite(14,LOW);
  }
void loop()
{
  Blynk.run();
  
}
