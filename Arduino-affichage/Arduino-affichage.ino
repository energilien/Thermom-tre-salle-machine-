// Partie LCD
#include <LiquidCrystal.h>

#define BUZZPIN 6

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int maximum = 25;
int minimum = 25;
int etat = 0;

void alarm() {
  tone(BUZZPIN, 440);
  while (Serial.read() != '1') {};
  noTone(BUZZPIN);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1. C'est bon ?");
  while (Serial.read() != '1') {};
}

void refresh(int key) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp. : ");
  lcd.print(key);
  lcd.setCursor(0,1);
  lcd.print("* pour Options");
}

void getval(int *val) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Valeur : ");
  lcd.print(*val);
  int newval = 0;
  String strval;
  while (newval == 0) {
    if(Serial.available()) {
      strval = Serial.read();
      newval == strval.toInt();
    }
  }
  *val = newval;
}

void options() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("1. Minimum: ");
  lcd.print(minimum);
  lcd.setCursor(0,1);
  lcd.print("2. Maximum: ");
  lcd.print(maximum);

  char value = '0';
  int* maxoumin;
  while (HIGH) {
    if (Serial.available()) {
      value = Serial.read(); 
    }
    switch (value) {
      case '1':
        maxoumin = &minimum;
        getval(maxoumin);
        return;
        break;
      case '2':
        maxoumin = &maximum;
        getval(maxoumin);
        return;
        break;
      case 'Q':
      case 'q':
        return;
    }
    }

}

void setup() {
  // On initialise le lcd
  lcd.begin(16, 2);
  pinMode(BUZZPIN, OUTPUT);
  Serial1.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    if (Serial.read() == '*') {
        options();
    }

  }

  if (Serial1.available()) {
    String message = Serial1.readStringUntil('\n');
    int temperature = message.toInt();
    refresh(temperature);
    if (temperature <= minimum || temperature >= maximum) {
      alarm();
    }
  }
}
