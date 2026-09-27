// Partie LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int switchPin = 6;
int switchState = 0;
int prevSwitchState = 0;
int reply;

unsigned long myllis;

void refresh() {
  myllis = millis();
  lcd.setCursor(0,0);
  lcd.print("Temps : ");
  lcd.write(myllis / 1000);
  lcd.setCursor(0,1);
  lcd.print("A pour Options");
}

void setup() {
  // On initialise le lcd
  lcd.begin(16, 2);
  pinMode(switchPin, INPUT);
  refresh();
}

void loop() {
  if ((myllis + 30000) <= millis()) {refresh();}
}
