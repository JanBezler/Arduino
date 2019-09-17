#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 2
#define DIO 3
#define pot A5

int pick = 0;
int sensorValue;
int potValue;
int HzValue;


TM1637Display display(CLK, DIO);

void setup() {
  pinMode(5, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  Serial.begin(9600);
}

void loop() {
  display.setBrightness(0x0f);

  if (analogRead(A6)> 900)
  {
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    
    sensorValue = analogRead(A7);
    sensorValue = map(sensorValue, 255, 1023, 0, 1000);

    if (sensorValue > pick){pick = sensorValue;}
    if (digitalRead(5)== LOW){pick = 0;}

    Serial.println(pick);
    display.showNumberDec(pick, false);
    delay(1);
  }
  else if (analogRead(A6) < 123)
  {
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    
    potValue = analogRead(A5);
    potValue = map(potValue, 0, 1023, 5, 5000);

    //HzValue = map(potValue, 200, 5000, 5000, 200);
    display.showNumberDec(potValue, false);
    Serial.println(potValue);
    
    digitalWrite(6, HIGH);
    delayMicroseconds(potValue/2);
    digitalWrite(6, LOW);
    delayMicroseconds(potValue/2);

  } 
}
