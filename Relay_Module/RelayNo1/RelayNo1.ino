#define BLYNK_TEMPLATE_ID "TMPLmPHyWu3T"
#define BLYNK_DEVICE_NAME "車間繼電器"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "xW5B8804fEfkT38STAeiBrI64DBdVleC";
char ssid[] = "Savewo Lab";
char pass[] = "KenKen2022-";



void setup()
{
  Serial.begin(9600);

  pinMode(2,OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(16, OUTPUT);

  Blynk.begin(auth, ssid, pass);
  if (Blynk.connected() == true){
    digitalWrite(2,LOW);
  }
  else {
    digitalWrite(2,HIGH);
  }
}

BLYNK_WRITE(V0)
{
  int i = param.asInt();
  
  Serial.print(param.asInt());
  Serial.print("  ");
  Serial.print(i);
  Serial.print("  ");
  Serial.println(digitalRead(12));

   if (i == 1) {
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    digitalWrite(14, HIGH);
    digitalWrite(16, HIGH);
  }
  else if (i == 0){
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    digitalWrite(14, LOW);
    digitalWrite(16, LOW);
  }
 
}

void loop()
{
  Blynk.run();
}
