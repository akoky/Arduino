/*********************************************************************
  This is an example for our Monochrome OLEDs based on SH110X drivers

  This example is for a 128x64 size display using I2C to communicate
  3 pins are required to interface (2 I2C and one reset)

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada  for Adafruit Industries.
  BSD license, check license.txt for more information
  All text above, and the splash screen must be included in any redistribution

  i2c SH1106 modified by Rupert Hirst  12/09/21
*********************************************************************/



#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display1 = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


int myarray[20];
void setup()   {

  Serial.begin(9600);

  display1.begin(i2c_Address, true);
  display1.clearDisplay();
  display1.setTextSize(2);
  display1.setTextColor(1);
  display1.setCursor(0, 15);
  display1.print("SAVEWO");
  display1.display();
  delay(2000);
  myarray[5] = 3;
  myarray[11] = 4;
  myarray[16] = 1;
  myarray[18] = 7;
  myarray[19] = 8;
}

void loop() {

  // display test
  display1.clearDisplay();
  display1.setTextSize(1);
  display1.setTextColor(1);
  display1.setCursor(0, 5);
  display1.println("Line : 23");
  display1.setCursor(0, 17);
  //  if (signalVal < 500) {
  //    display.print("Sensor : Waiting");
  //  }
  //  if (signalVal > 500) {
  //    display.print("Sensor : DETECTED");
  //  }
  display1.print("Sensor : Waiting");
  display1.setCursor(0, 29);
  display1.print("DIR- define: ");
  // display.println(define);
  display1.println("0");
  display1.setCursor(0, 41);
  display1.print("Drop: ");
  // display.println(drop);
  display1.println("16");
  display1.setCursor(0, 53);
  int i;
  for ( i = 0 ; i < 20; i ++) {
    display1.print(myarray[i]);
  }
  display1.display();
  delay(1);
}
