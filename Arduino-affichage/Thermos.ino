// Partie LCD
#include <LiquidCrystal.h>

#define BUZZPIN 6

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int maximum = 25;
int minimum = 25;
int etat = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(BUZZPIN, OUTPUT);
  Serial1.begin(9600);
  Serial.begin(9600);
  etat = 1;
}

String lireClavier() {
  String message = Serial.readStringUntil('\n');
  return message;
}

int lireTemperature() {
  String message = Serial1.readStringUntil('\n');
  return message.toInt();
}

void principalScreen(int temperature) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp. : ");
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.print("* pour Options");
}

void optionScreen(int minimum, int maximum) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1. Minimum: ");
  lcd.print(minimum);
  lcd.setCursor(0, 1);
  lcd.print("2. Maximum: ");
  lcd.print(maximum); 
}

bool temperatureHorsPlage(int temperature, int minimum, int maximum) {
  if (temperature <= minimum || temperature >= maximum) {
      return true;
    }
    return false;
}

void loop() {
  // put your main code here, to run repeatedly:
  int ecran;
  int temperature;

  //Clavier
  if (Serial.available()) {
    String texte = lireClavier();
  }
  if (Serial1.available()) {
    temperature = lireTemperature();
    if (etat < 4) {
      if (temperatureHorsPlage(temperature, minimum, maximum)) {
        etat = 2;
      } else {
        etat = 1;
      }
    }
  }
 

  switch (etat) {
    case 1:
      ecran = 1;
      if (texte == "*") {
        etat = 5;
        ecran = 5;
      }
      break;
    case 2:
      break;
    case 3:
      break;
    case 5:

      break;
    case 6:
      break;
    case 7:
      break;
    default:
      break;
  }

  switch (ecran) {
    case 1:
      principalScreen(temperature);
      break;
    case 2:
      break;
    case 3:
      break;
    case 5:
      optionScreen(minimum, maximum);
      break;
    case 6:
      break;
    case 7:
      break;
    default:
      break;
  }
}
