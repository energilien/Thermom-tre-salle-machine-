// Partie LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int reply;

// Partie Keypad
#include <Keypad.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //three columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte rowPins[4] = {22, 23, 24, 25};
byte colPins[4] = {26, 27, 28, 29};

Keypad keypad = Keypad(
  makeKeymap(keys),
  rowPins,
  colPins,
  ROW_NUM,
  COLUMN_NUM
);


unsigned long timeCheckpoint;
float temp = 0;

#define BUZZPIN 6
#define BOUTONPIN 13

void alarm() {
  tone(BUZZPIN, 440);
  while (digitalRead(BOUTONPIN) != HIGH) {}
  noTone(BUZZPIN);
}

void refresh(char key) {
  timeCheckpoint = millis();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp. : ");
  lcd.print(key);
  lcd.setCursor(0,1);
  lcd.print("* pour Options");
}

void setup() {
  // On initialise le lcd
  lcd.begin(16, 2);
  pinMode(BOUTONPIN, INPUT);
  pinMode(BUZZPIN, OUTPUT);
  Serial1.begin(9600);
  Serial.begin(9600);
}

void loop() {
  //char key = keypad.getKey();
  if (Serial1.available()) {
    String message = Serial1.readStringUntil('\n');
    //message.trim();
    int temperature = message.toInt();
    Serial.println(temperature); 
    }
//  if ((timeCheckpoint + 1000) <= millis()) {refresh(key);}
  //refresh(temp);
  delay(1000);
}
