#include <LiquidCrystal.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Adafruit_BMP085 bmp;

byte strzalka[8] = {
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100
};

byte cisnienie[8] = {
  0b01110,
  0b11111,
  0b11111,
  0b01010,
  0b00000,
  0b01001,
  0b10010,
  0b00100
};

void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
  // set up the LCD's number of columns and rows:
  lcd.begin(8, 2);
  // Print a message to the LCD.
  lcd.print("Peterzig");
  delay(1000);
  lcd.clear();
  lcd.print("16-06-16");
  delay(1000);
  lcd.clear();
  lcd.createChar(1,cisnienie);
  lcd.createChar(2,strzalka);
}

void loop() {
  // Turn on the display:
  lcd.display();
    lcd.setCursor(0, 0);
    lcd.write(1);
    if(bmp.readPressure()<100000){
    lcd.print(bmp.readPressure()/100);
    lcd.println(" hPa ");
    }
    if(bmp.readPressure()==100000){
    lcd.print(bmp.readPressure()/100);
    lcd.println("hPa ");
    }
    if(bmp.readPressure()>100000){
    lcd.print(bmp.readPressure()/100);
    lcd.println("hPa ");
    }
    lcd.setCursor(1, 1);
    if(bmp.readAltitude()>100){
    lcd.write(2);
    lcd.print(bmp.readAltitude(),0);
    lcd.println(" m ");
    }
    if(bmp.readAltitude()==100){
    lcd.write(2);
    lcd.print(bmp.readAltitude(),0);
    lcd.println(" m ");
    }
    if(bmp.readAltitude()<100){
    lcd.write(2);
    lcd.print(bmp.readAltitude(),0);
    lcd.println(" m  ");
    }
    delay(500);
}
