#include <LiquidCrystal.h>

int chargePin = A0;
int dischargePin = A1;
int readPin = A2;
int resistance = 10000;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(chargePin, OUTPUT);
  digitalWrite(chargePin, HIGH);  
  pinMode(dischargePin, INPUT);

  lcd.begin(16, 2);
}

void loop(){
  float measureCount = 3;
  float measureSum = 0;
  for (int i = 0; i < measureCount; i++) {
    measureSum += measureCapacity();
  }
  float microFarads = measureSum / measureCount; 

  lcd.clear();       

  lcd.print(microFarads);       
  lcd.print(" uF");         
} 

float measureCapacity() {
  digitalWrite(chargePin, HIGH);  
  int startTime = millis();
  while (analogRead(readPin) < 648) {}

  int elapsedTime = millis() - startTime;
  float microFarads = ((float)elapsedTime / resistance) * 1000;

  digitalWrite(chargePin, LOW);            
  pinMode(dischargePin, OUTPUT);            
  digitalWrite(dischargePin, LOW);          
  while (analogRead(readPin) > 0) {}

  pinMode(dischargePin, INPUT);

  return microFarads;
}
