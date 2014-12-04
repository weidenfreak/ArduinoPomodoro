#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int switchPin = 6;
int switchState = 0;
int prevSwitchState = 0;

unsigned long currentTime = 0;
unsigned long pomodoroInterval = 1500000;
unsigned long breakInterval = 300000;
unsigned long interval = 0;
unsigned long startTime;
long timeLeft = 0;

void setup() {
  lcd.begin(16, 2);
  pinMode(switchPin, INPUT);
  startTime = millis();
}

void loop() {
  switchState = digitalRead(switchPin);
  
  lcd.setCursor(0,1);
  if (switchState == HIGH) {
    interval = pomodoroInterval;
    lcd.print("Work Mode");   
  } else {
    interval = breakInterval;
    lcd.print("Break Mode");
  }
  
  currentTime = millis() - startTime;
  timeLeft = interval - currentTime;
  
  lcd.setCursor(0,0);
  if(timeLeft < 0) {
    timeLeft = 0;
    if (switchState == HIGH) {
      lcd.print("Time for a break!");
    } else {
      lcd.print("Start work!      ");
    }
  } else {
    lcd.print("Minutes left: ");
    lcd.print(timeLeft/60000);
  }
  
  if(switchState != prevSwitchState) {
    lcd.clear();
    startTime = millis();
  }
  
  prevSwitchState = switchState;
}
