#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
//#include <WidgetRTC.h>

int counter = 0;
int sw = 0;
int sw2 = 0;
int _timer = 0;

//WidgetRTC rtc;


String GAS_ID = "AKfycbxAOOH2jAE0nHHLdYm4DtFSXuoPjIZ3mFYxcwVIzC-bFp1hGqOL";
char ssid[] = "Savewo Lab";
char pass[] = "KenKen2022-";

const char* host = "script.google.com";
const int httpsPort = 443;


WiFiClientSecure client; //Create a WiFiClientSecure object.

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  
  //rtc.begin();
  delay(2000); 

  client.setInsecure();
  
  // 24V siganl pin
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  // reset button pin
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  Serial.println("Set up finished");
}

void loop() {
    maskcounter();
    button();
    if(_timer == 60000){
      _sendData(counter);
    }else{
      _timer++;
    }
    delay(1);
}

// counter + 1 when 24V signal is shorted
void maskcounter(){
  if(digitalRead(4) == LOW && sw2 == 0){
    delay(300);
    counter++;
    sw2 = 1;
    Serial.println(counter);
  }
  else if(digitalRead(4) == HIGH && sw2 == 1){
    sw2 = 0;
  }
}

// reset counter = 0 when button is pressed

void button(){
  if(digitalRead(2) == LOW && sw == 0){
    delay(300);
    sw = 1;
    counter = 0;
    Serial.println(counter);
    //delay(1000);
  }
  else if(digitalRead(2) == HIGH && sw == 1){
    sw = 0;
  }
}

void _sendData(int num) {

  if (!client.connect(host, httpsPort)) {
   Serial.println("connection failed");
   
    //return;
  }
  String string_counter =  String(num); 
  String url = "/macros/s/" + GAS_ID + "/exec?number=" + string_counter ;
  //+ string_temperature + "&humidity=" + string_humidity;

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");
} 
