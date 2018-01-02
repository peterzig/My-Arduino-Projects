/*----------------------------------------------------------------------*
 * Display the date and time from a DS1302 RTC every second.            *
 *                                                                      *
 * Set the date and time by entering the following on the Arduino       *
 * serial monitor:                                                      *
 *    year,month,day,hour,minute,second,                                *
 *                                                                      *
 * Where                                                                *
 *    year can be two or four digits,                                   *
 *    month is 1-12,                                                    *
 *    day is 1-31,                                                      *
 *    hour is 0-23, and                                                 *
 *    minute and second are 0-59.                                       *
 *                                                                      *
 * Entering the final comma delimiter (after "second") will avoid a     *
 * one-second timeout and will allow the RTC to be set more accurately. *
 *                                                                      *
 * No validity checking is done, invalid values or incomplete syntax    *
 * in the input will result in an incorrect RTC setting.                *
 *                                                                      *
 * Jack Christensen 08Aug2013                                           *
 *                                                                      *
 * Adopted for DS1302RTC library by Timur Maksimov 2014                 *
 *                                                                      *
 * This work is licensed under the Creative Commons Attribution-        *
 * ShareAlike 3.0 Unported License. To view a copy of this license,     *
 * visit http://creativecommons.org/licenses/by-sa/3.0/ or send a       *
 * letter to Creative Commons, 171 Second Street, Suite 300,            *
 * San Francisco, California, 94105, USA.                               *
 *----------------------------------------------------------------------*/ 
 
#include <DS1302RTC.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Streaming.h>        //http://arduiniana.org/libraries/streaming/
#include <Time.h>             //http://playground.arduino.cc/Code/Time
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

// Data wire is plugged into pin 7 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with ANY OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Set oneWire reference to Dallas Temperature sensor.
DallasTemperature sensors(&oneWire);

byte thermometer[8] = //icon for termometer
{
    B00100,
    B01010,
    B01010,
    B01110,
    B01110,
    B11111,
    B11111,
    B01110
};
// Set pins:  CE, IO,CLK
DS1302RTC RTC(8, 7, 6);
LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7);

// Optional connection for RTC module
void setup()
{
  pinMode(3, OUTPUT);
  lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.createChar(1,thermometer);
  
  Serial.begin(115200);
    
  // Activate RTC module
  
  Serial << F("RTC module activated");
  Serial << endl;
  delay(500);
  
  if (RTC.haltRTC()) {
    Serial << F("The DS1302 is stopped.  Please set time");
    Serial << F("to initialize the time and begin running.");
    Serial << endl;
  }
  if (!RTC.writeEN()) {
    Serial << F("The DS1302 is write protected. This normal.");
    Serial << endl;
  }
  
  delay(5000);
    
  //setSyncProvider() causes the Time library to synchronize with the
  //external RTC by calling RTC.get() every five minutes by default.
  setSyncProvider(RTC.get);

  Serial << F("RTC Sync");
  if (timeStatus() == timeSet)
    Serial << F(" Ok!");
  else
    Serial << F(" FAIL!");
  Serial << endl;
}

void loop()
{
  digitalWrite(3, HIGH);
  sensors.requestTemperatures();
  const char* miesiac[] = {"Gru", "Sty", "Lut", "Mar", "Kwi", "Maj", "Cze", "Lip", "Sie", "Wrz", "Paź", "Lis" };
  digitalWrite(3, HIGH);
    static time_t tLast;
    time_t t;
    tmElements_t tm;

    //check for input to set the RTC, minimum length is 12, i.e. yy,m,d,h,m,s
    if (Serial.available() >= 12) {
        //note that the tmElements_t Year member is an offset from 1970,
        //but the RTC wants the last two digits of the calendar year.
        //use the convenience macros from Time.h to do the conversions.
        int y = Serial.parseInt();
        if (y >= 100 && y < 1000)
            Serial << F("Error: Year must be two digits or four digits!") << endl;
        else {
            if (y >= 1000)
                tm.Year = CalendarYrToTm(y);
            else    //(y < 100)
                tm.Year = y2kYearToTm(y);
            tm.Month = Serial.parseInt();
            tm.Day = Serial.parseInt();
            tm.Hour = Serial.parseInt();
            tm.Minute = Serial.parseInt();
            tm.Second = Serial.parseInt();
            t = makeTime(tm);
	    //use the time_t value to ensure correct weekday is set
            if(RTC.set(t) == 0) { // Success
              setTime(t);
              Serial << F("RTC set to: ");
              printDateTime(t);
              Serial << endl;
	    }
	    else
	      Serial << F("RTC set failed!") << endl;
            //dump any extraneous input
            while (Serial.available() > 0) Serial.read();
        }
    }
    
    t = now();
    if (t != tLast) {
        tLast = t;
        printDateTime(t);
        Serial << endl;
    }
    lcd.home (); // set cursor to 0,0
  lcd.print(day(t)); 
  lcd.print(""); 
  lcd.print(month(t)[miesiac]); 
  lcd.print(""); 
  lcd.print(year(t)); 
  lcd.print(" "); 
  lcd.write(1);
  lcd.print("1:"); 
  lcd.print(sensors.getTempCByIndex(0),0); 
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor (0,1);  // go to start of 2nd line
   if(hour(t)<10){
    lcd.print("0");
    lcd.print(hour(t));
  }
  else{
  lcd.print(hour(t));
  }
  lcd.print(":"); 
  if(minute(t)<10){
    lcd.print("0");
    lcd.print(minute(t));
  }
  else{
  lcd.print(minute(t));
  }
  lcd.print(":"); 
  if(second(t)<10){
    lcd.print("0");
    lcd.print(second(t));
  }
  else{
  lcd.print(second(t));
  }
  delay(200);
  lcd.print(" "); 
  lcd.write(1);
  lcd.print("2:"); 
  lcd.print(sensors.getTempCByIndex(1),0); 
  lcd.print((char)223);
  lcd.print("C");
}


//print date and time to Serial
void printDateTime(time_t t)
{
    printDate(t);
    Serial << ' ';
    printTime(t);
}

//print time to Serial
void printTime(time_t t)
{
    printI00(hour(t), ':');
    printI00(minute(t), ':');
    printI00(second(t), ' ');
}

//print date to Serial
void printDate(time_t t)
{
    printI00(day(t), 0);
    Serial << monthShortStr(month(t)) << _DEC(year(t));
}

//Print an integer in "00" format (with leading zero),
//followed by a delimiter character to Serial.
//Input value assumed to be between 0 and 99.
void printI00(int val, char delim)
{
    if (val < 10) Serial << '0';
    Serial << _DEC(val);
    if (delim > 0) Serial << delim;
    return;
}
