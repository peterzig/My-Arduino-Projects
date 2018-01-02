// LCD5110_Graph_Demo 
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// This program is a demo of most of the functions
// in the library.
//
// This program requires a Nokia 5110 LCD module.
//
// It is assumed that the LCD module is connected to
// the following pins:
//      SCK  - Pin 8
//      MOSI - Pin 9
//      DC   - Pin 10
//      RST  - Pin 11
//      CS   - Pin 12
//
#include <LCD5110_Graph.h>
#include "DHT.h"

#define DHTPIN 7                                   // DHT connection pin
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);
LCD5110 myGLCD(8,9,10,11,12);

extern unsigned char SmallFont[];
extern unsigned char TinyFont[];

float y;
uint8_t* bm;
int pacy;

void setup()
{
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  randomSeed(analogRead(7));
  dht.begin();
  Serial.begin(9600);
}

void temp()
{
  int tempdht;
  int humdht;

  humdht = dht.readHumidity();
  tempdht = dht.readTemperature();
   
   Serial.print("Temperatura: "); 
   Serial.print(tempdht);
   Serial.println(" C  ");
   
   Serial.print("Wilgotnosc: ");
   Serial.print(humdht);
   Serial.println(" %");
   delay(1000);
}

void lcd(){
  int tempdht;
  int humdht;
  humdht = dht.readHumidity();
  tempdht = dht.readTemperature();
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("Temp.:", LEFT, 20);
  myGLCD.print("Wilg.pow.: ", LEFT, 30);
  myGLCD.printNumI(tempdht, RIGHT, 20);
  myGLCD.printNumI(humdht, RIGHT, 30);
  myGLCD.setFont(TinyFont);
  myGLCD.print("Termometr DHT11", CENTER, 0);
  myGLCD.print("Peterzig", CENTER, 6);
  myGLCD.print("15-03-2016", CENTER, 12);
  myGLCD.update();
}
void loop()
{
  
  int tempdht;
  int humdht;
  
  humdht = dht.readHumidity();
  tempdht = dht.readTemperature();
  
  myGLCD.clrScr();
  for(int i = 0; i < 2; i++){
  temp();
  }
  delay(500);
  myGLCD.print("Temp.:", LEFT, 20);
  myGLCD.print("Wilg.pow.: ", LEFT, 30);
  myGLCD.printNumI(tempdht, RIGHT, 20);
  myGLCD.printNumI(humdht, RIGHT, 30);
  myGLCD.setFont(TinyFont);
  myGLCD.print("Termometr DHT11", CENTER, 0);
  myGLCD.print("Peterzig", CENTER, 6);
  myGLCD.print("15-03-2016", CENTER, 12);
  myGLCD.update();
  delay(200);
  for(int i = 0; i < 2; i++){
  temp();
  }
  lcd();
  delay(5000);
  for(int i = 0; i < 2; i++){
  temp();
  }
  lcd();
  myGLCD.clrScr();
  for(int i = 0; i < 2; i++){
  temp();
  }
  delay(500);
  for (int c=0; c<6; c++)
  {
    for (int i=0; i<84; i++)
    {
      y=i*0.017453292519943295769236907684886;
      myGLCD.invPixel(i, (sin(y*6)*10)+10);
      myGLCD.print("Temp.:", LEFT, 20);
      myGLCD.printNumI(tempdht, RIGHT, 20);
      myGLCD.print("Wilg.pow.:", LEFT, 30);
      myGLCD.printNumI(humdht, RIGHT, 30);
      myGLCD.setFont(SmallFont);
      myGLCD.update();
      delay(20);
    }
    temp();
  }
  for(int i = 0; i < 2; i++){
  temp();
  }
  delay(500);
  
  myGLCD.clrScr();
  for (int i=0; i<48; i+=2)
  {
    myGLCD.drawLine(0, i, 83, 47-i);
    myGLCD.update();
  }
  for (int i=83; i>=0; i-=2)
  {
    myGLCD.drawLine(i, 0, 83-i, 47);
    myGLCD.update();
  }
  
  delay(2000);
 
  for (int i=0; i<3; i++)
  {
    myGLCD.invert(true);
    delay(1000);
    myGLCD.invert(false);
    delay(1000);
  }
}
  
  
