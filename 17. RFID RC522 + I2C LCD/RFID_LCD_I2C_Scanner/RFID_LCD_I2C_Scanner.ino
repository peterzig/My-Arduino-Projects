#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7);

byte ch0[8]={B11111,B11111,B11111,B11111,B11111,B11111,B11111,0};
byte ch1[8]={B11110,B11110,B11110,B11110,B11110,B11110,B11110,0};
byte ch2[8]={B11100,B11100,B11100,B11100,B11100,B11100,B11100,0};
byte ch3[8]={B11000,B11000,B11000,B11000,B11000,B11000,B11000,0};
byte ch4[8]={B10000,B10000,B10000,B10000,B10000,B10000,B10000,0};
byte ch5[8]={B00000,B00000,B00000,B00000,B00000,B00000,B00000,0};

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);	// Create MFRC522 instance.

void setup() {
	Serial.begin(9600);	// Initialize serial communications with the PC
  lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();	// Init MFRC522 card
	Serial.println("Scan PICC to see UID and type...");
  lcd.home ();
  lcd.print("Skanuj karte");
  lcd.setCursor (0,1);
  lcd.print("frajerze...");
  //-------------------
 lcd.createChar(0, ch0);
 lcd.createChar(1, ch1);
 lcd.createChar(2, ch2);
 lcd.createChar(3, ch3);
 lcd.createChar(4, ch4);
 lcd.createChar(5, ch5);
}

void loop() {
	// Look for new cards
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
   lcd.home ();
  lcd.print("Skanuj karte");
  lcd.setCursor (0,1);
  lcd.print("frajerze...");
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}
 
  int timer = 0;
  lcd.clear ();
  lcd.print("Skanowanie...");
  lcd.setCursor (0,1); 
   for (int i=0; i <= 15; i++)  // print 16 block characters
   {
    lcd.print((char) 0);
    delay(100);
   }
   
	// Dump debug info about the card. PICC_HaltA() is automatically called.
	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  lcd.clear ();
  lcd.print("Zeskanowano.");
  delay(3000);
}
