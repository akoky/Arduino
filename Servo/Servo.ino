char auth[] = "ZQdJlnPJryEIkmyamrZfO4oJcNoOkl0J"; //SAVEWO

char ssid[] = "Savewo Lab";
char pass[] = "KenKen2022-";

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(4);
  servo.write(0);
  Blynk.begin(auth, ssid, pass);

}

BLYNK_WRITE(V0)
  {
    int i = param.asInt();
    Serial.println(param.asInt());
    if(i==1){
      servo.write(180);
    }
    else
      servo.write(0);
  }
void loop()
{
  Blynk.run();
  
}
