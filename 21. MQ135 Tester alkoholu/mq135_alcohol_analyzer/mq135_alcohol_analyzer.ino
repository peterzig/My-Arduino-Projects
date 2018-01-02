#define led 2
#define led2 3
#define led3 4

int sensorPin = A0;
int sensorValue = 0;

void setup() {
 Serial.begin(9600);
 pinMode(sensorPin, INPUT);
 pinMode(led, OUTPUT);
 pinMode(led2, OUTPUT);
 pinMode(led3, OUTPUT);
}

void loop() {
 sensorValue = analogRead(sensorPin);
 Serial.println(sensorValue);
 if(sensorValue < 160){
  digitalWrite(led, HIGH);
  // green LED on, it's ready to go
 }
 if(sensorValue > 160 && sensorValue < 300){
  digitalWrite(led2, HIGH);
  //green and yellow LED on, something is weird, maybe you have bad breath ;)
 }
  if(sensorValue > 300){
  digitalWrite(led3, HIGH);
  //red LED on, definitely after (max>x>=1) beers
 }
}
