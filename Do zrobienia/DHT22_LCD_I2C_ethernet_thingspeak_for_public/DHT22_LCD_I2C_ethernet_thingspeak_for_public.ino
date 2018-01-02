// Iot - Temperature / Humidity publish to Thingspeak v 1.0
//
// Created by Kostas Tsirogiannis tsirogk@gmail.com
//
// Based on job made by:
// Ladyada for DHT 22/ 11 monitoring http://www.adafruit.com
// Thingspeak original library http://www.thingspeak.com
// I2C LCD display library by LCDAPI http://playground.arduino.cc/Code/LCDAPI
// Ethernet library as is in Arduino IDE
// I2C to LCD breakout created by http://www.grobotronics.com
// You can find the sketches in fritzing.org

//You also need above libraries to be installed inyour system: DHT - Thingspeak - LCDAPI

#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "ThingSpeak.h"
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};// in case you have the addresss printed on the ethernet shield, just use your own mac address.

// fill in an available IP address on your network here, as it is in your local network
// for manual configuration:
IPAddress ip(192, 168, 1, 177);

// fill in your Domain Name Server address here (usually the IP of your router):
IPAddress myDNS(192, 168, 1, 254);

// fill in your Domain Name Server address here(usually the IP of your router):
IPAddress Gateway(192, 168, 1, 254);

// char server[] = "www.thingspeak.com";//Not really needed, I left it in case I use the original Thingspeak code.
IPAddress server(184, 106, 153, 149);

EthernetClient client;

unsigned long myChannelNumber = 11111; //REMEMBER to change it to YOUR CHANNEL !!!!
const char * myWriteAPIKey = "XXXXXXXXXXXX";//REMEMBER to change it to YOUR API KEY !!!!

LiquidCrystal_I2C lcd(0x39,16,2);  // set the LCD address to 0x39 for a 16 chars and 2 line display
// you have to check the address of your I2C breakout board using the code provided in http://playground.arduino.cc/Main/I2cScanner

#define DHTPIN 2     // what digital pin we're connected to. Don't use the ones used by Ethernet shield e.g for UNO 10, 11, 12 and 13 or SPI


// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);




void setup() {

  pinMode(13, OUTPUT); // just for a blink of the LED to make sure the  sketch has run ok.
  dht.begin();
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600); // You don't really need it.
  delay(10000); // to give enough time for the ethernet shield to boot.
  Ethernet.begin(mac, ip, myDNS, Gateway);
  ThingSpeak.begin(client);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
 
    // clear the screen
 lcd.clear();
 

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again). I had recently one DHT11 sensor destroyed ...
  if (isnan(h) || isnan(t) || isnan(f)) 
  {
    lcd.print("Failed to read from DHT sensor!");
    return;
  }

// Here we have the IoT job done !

ThingSpeak.setField(1,h);
ThingSpeak.setField(2,t); //or instead of t use f for Farenheit.

ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

// And here we have a fancy LCD showing our data.

  lcd.setCursor(0,0);
  lcd.print("Hum:");
  lcd.print(h);
  lcd.print(" %");

  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" *C ");

//  We just blink. Nothing else ...

  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
  delay(15000);
}

