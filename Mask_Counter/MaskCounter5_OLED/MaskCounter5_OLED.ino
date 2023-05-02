#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
//#include <WidgetRTC.h>

int counter = 0;
int sw = 0;
int sw2 = 0;
int sw3 = 0;
int _timer = 0;

//WidgetRTC rtc;


String GAS_ID = "AKfycbxAOOH2jAE0nHHLdYm4DtFSXuoPjIZ3mFYxcwVIzC-bFp1hGqOL";
char ssid[] = "Savewo Lab";
char pass[] = "KenKen2022-";

const char* host = "script.google.com";
const int httpsPort = 443;

unsigned long previousMillis = 0;  
const long period = 15000; 

WiFiClientSecure client; //Create a WiFiClientSecure object.


// OLED settings
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  
  //rtc.begin();
  delay(2000); 

  client.setInsecure();

  // OLED Start
  display.begin(i2c_Address, true);
  display.clearDisplay();
  display.setTextSize(2);             
  display.setTextColor(1);        
  display.setCursor(0,15); 
  display.print("SAVEWO");
  display.display();
  delay(3000);
  
  // 24V siganl pin
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);

  // reset button pin
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  Serial.println("Set up finished");
}

void loop() {
    maskcounter();
    button();
    _display();
    //if(_timer == 10000){
    //  _sendData(counter);
   // }else{
     // _timer++;
    //}
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= period) {
      previousMillis = currentMillis;
      if(counter == 0 && sw3 == 0){
        sw3 = 1;
        _sendData(counter);
      }
      else if(counter != 0 && sw3 == 1){
        sw3 = 0;
        _sendData(counter);
      }
      else if(counter !=0 && sw3 == 0){
        _sendData(counter);
      }
    }

}

// counter + 1 when 24V signal is shorted
void maskcounter(){
  if(digitalRead(12) == LOW && sw2 == 0){
    delay(300);
    counter++;
    sw2 = 1;
    Serial.println(counter);
  }
  else if(digitalRead(12) == HIGH && sw2 == 1){
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
  String url = "/macros/s/" + GAS_ID + "/exec?_number=" + string_counter ;
  //+ string_temperature + "&humidity=" + string_humidity;

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");
} 

void  _display(){
  display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(1);        
  display.setCursor(0,30); 
  display.print("Mask Produced: ");
  display.println(counter);
  display.display();                  
}
