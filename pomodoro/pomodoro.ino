#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int switchPin = 6;
int switchState = 0;


unsigned long currentTime = 0;
int prevSwitchState = 0;
unsigned long previousTime = 0;
unsigned long pomodoroInterval = 10000;
unsigned long breakInterval = 5000;
unsigned long interval = 0;
unsigned long currentInterval;
unsigned long startTime;
long timeLeft = pomodoroInterval;


void setup() {
  lcd.begin(16, 2);
  pinMode(switchPin, INPUT);
  startTime = millis();
}

void loop() {
  switchState = digitalRead(switchPin);
  currentTime = millis();
  
  if (switchState == HIGH) {
    interval = pomodoroInterval;
  } else {
    interval = breakInterval;
  }
  
  lcd.setCursor(0,1);
  if(switchState == HIGH) {
    lcd.print("Work Mode");     
  } else {    
    lcd.print("Break Mode");
  }
  
  currentTime = millis() - startTime;
  timeLeft = interval - currentTime;
  
  lcd.setCursor(0,0);
  if(timeLeft < 0) {
    timeLeft = 0.0000;
    if (switchState == HIGH) {
      lcd.print("Time for a break!");
    } else {
      lcd.print("Start work!");
    }
  } else {
    lcd.print("Seconds left: ");
    lcd.print(timeLeft/1000);
    
  }
  
  if(switchState != prevSwitchState) {
    lcd.clear();
    startTime = millis();
  }
  
  prevSwitchState = switchState;
}
