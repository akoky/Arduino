// OTA settings
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#ifndef STASSID
#define STASSID "Savewo Lab"
#define STAPSK  "KenKen2022-"
#endif
const char* ssid = STASSID;
const char* password = STAPSK;

// OLED settings
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// EEPROM settings
#include <EEPROM.h>

int drop = 0;
int counter = 0; 
int define = 0;
int signalVal = 0;
int sw = 0;
int define_address = 0;
int drop_address = 1;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  EEPROM.begin(512);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  pinMode(2, OUTPUT);
  if(WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! LED off");
    digitalWrite(2, HIGH);
  }else{
    digitalWrite(2, LOW);
  }
  // ArduinoOTA.setPort(8266);
  ArduinoOTA.setHostname("SAVEWO_8266");
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(1000);

  // read eeprom 
  define = EEPROM.read(define_address);
  drop = EEPROM.read(drop_address);
  
  // OLED Start
  display.begin(i2c_Address, true);
  display.clearDisplay();
  display.setTextSize(2);             
  display.setTextColor(1);        
  display.setCursor(0,15); 
  display.print("SAVEWO");
  display.display();
  delay(3000);
  
  // + button 
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH); 
  
  // - button
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH); 
  
  // switch button
  pinMode(14, OUTPUT);
  digitalWrite(14, HIGH);
  
  // Step-
  pinMode(15, OUTPUT);
  digitalWrite(15, HIGH); 

  // DIR-
  pinMode(16, OUTPUT);
  digitalWrite(16, HIGH); 
  
}
 
  
// the loop function runs over and over again forever
void loop() { 
  
  ArduinoOTA.handle();
  
  // 12V_Signal
  signalVal = analogRead(A0);
  //Serial.print("A0 = ");
  //Serial.println(signalVal);

  // drop + 1
  if(digitalRead(12) == LOW && drop < 50){
    delay(300);
    drop++; 
    EEPROM.write(drop_address, drop);
    EEPROM.commit();
    delay(1);
    //Serial.print("drop = ");
    //Serial.println(drop);
  }

  // drop - 1
  if(digitalRead(13) == LOW && drop > 0){
    delay(300);
    drop--;  
    EEPROM.write(drop_address, drop);
    EEPROM.commit();
    delay(1);
    //Serial.print("drop = ");
    //Serial.println(drop);
  }

  // DIR- define switch
  if(digitalRead(14) == LOW && sw == 0){
    // making voltage low to turn led off
    digitalWrite(16, LOW); 
    define = 1;   
    sw = 1;
    EEPROM.write(define_address, define);
    EEPROM.commit();
    delay(300);
    //Serial.println(define);
  }
  else if(digitalRead(14) == LOW && sw == 1){
    // making voltage high to turn led on
    digitalWrite(16, HIGH); 
    define = 0;   
    sw = 0;
    EEPROM.write(define_address, define);
    EEPROM.commit();
    delay(300);
    //Serial.println(define);
  }

  
  // counter = drop when 12V signal received 
  if(signalVal > 500){
    counter = drop;
    //Serial.print("counter = ");
    //Serial.println(counter);
  }


  // counter - 1 when Step- is connected to GND
  if(digitalRead(15) == LOW && counter > 0){
    delay(300);
    counter--; 
    //Serial.print("counter = ");
    //Serial.println(counter);
    }
    
  // switch DIR when 12V signal received and counter = 0
  if(define == 0){
    if(counter > 0){
      digitalWrite(16, HIGH);
    }
    else{
      digitalWrite(16, LOW);
      }
    }
  else if(define == 1){
    if(counter > 0){
      digitalWrite(16, LOW);
    }
    else{
      digitalWrite(16, HIGH);
    }
  }
  
  // display test
  display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(1);        
  display.setCursor(0,10); 
  if(signalVal < 500){
    display.print("Sensor : Waiting");
  }
  if(signalVal > 500){
    display.print("Sensor : DETECTED");      
  }
  display.setCursor(0,22);
  display.print("DIR- define: ");
  display.println(define);
  display.setCursor(0,34);
  display.print("Drop: ");
  display.println(drop);
  display.setCursor(0,46);
  display.print("Counter: ");
  display.println(counter);
  display.display();                  
  delay(1);
}
