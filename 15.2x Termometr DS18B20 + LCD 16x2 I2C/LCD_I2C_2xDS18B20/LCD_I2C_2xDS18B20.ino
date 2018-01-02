#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7);
// Data wire is plugged into pin 7 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with ANY OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Set oneWire reference to Dallas Temperature sensor.
DallasTemperature sensors(&oneWire);

void setup(void)
{
Serial.begin(9600);
sensors.begin();
lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
}
void loop(void)
{
sensors.requestTemperatures();
Serial.println("");
delay(500);
Serial.print("Sensor 1: ");
Serial.println(sensors.getTempCByIndex(0));
Serial.print("Sensor 2: ");
Serial.println(sensors.getTempCByIndex(1));// first founded sensor have Index 0
lcd.home (); // set cursor to 0,0
  lcd.print("Temp 1:"); 
  lcd.print(sensors.getTempCByIndex(0)); 
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor (0,1);        // go to start of 2nd line
  lcd.print("Temp 2:"); 
  lcd.print(sensors.getTempCByIndex(1)); 
  lcd.print((char)223);
  lcd.print("C");
  delay(1000);
}
