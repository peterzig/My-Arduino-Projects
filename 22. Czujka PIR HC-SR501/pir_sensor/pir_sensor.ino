#define LED_R 10
#define LED_G 11
#define BUZZER 12

#define PIR 2
 
void setup() {
  pinMode(LED_R, OUTPUT); //Poszczególne piny sterujące diodą jako wyjścia
  pinMode(LED_G, OUTPUT);
  pinMode(BUZZER, OUTPUT);
 
  pinMode(PIR, INPUT_PULLUP); //PIR jako wejście
    
  digitalWrite(LED_R, LOW); //Dioda wyłączona
  digitalWrite(LED_G, LOW);
  digitalWrite(BUZZER, LOW);
}
 
void loop() {
  if (digitalRead(PIR) == LOW) { //Jeśli wykryto ruch
    digitalWrite(BUZZER, LOW);
    digitalWrite(LED_R, LOW); //Stan OK - dioda zielona
    digitalWrite(LED_G, HIGH);
  } else {
    digitalWrite(BUZZER, HIGH);
    digitalWrite(LED_R, HIGH); //Stan ALARM - dioda czerwona
    digitalWrite(LED_G, LOW);
  }
}
