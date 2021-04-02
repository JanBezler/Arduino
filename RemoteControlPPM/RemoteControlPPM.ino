#include "PPMEncoder.h"

#define OUTPUT_PIN 10
#define BUZZER_PIN 8

#define Y_PIN A0
#define T_PIN A1
#define R_PIN A2
#define P_PIN A3

#define B1_PIN 2
#define B2_PIN 3
#define B3_PIN 4
#define B4_PIN 5
#define B5_PIN 6
#define B6_PIN 7

#define DISARM 1083
#define HORIZON 1250
#define GPS_HOLD 1417
#define GPS_MISSION 1583
#define GPS_RTH 1750
#define UNDEFINED_YET 1917
   
int deadField = 20;
int currentMode = DISARM;
unsigned long triggerTime = 0;

void setup() {
  pinMode(Y_PIN, INPUT);
  pinMode(T_PIN, INPUT);
  pinMode(R_PIN, INPUT);
  pinMode(P_PIN, INPUT);
  pinMode(B1_PIN, INPUT);
  pinMode(B2_PIN, INPUT);
  pinMode(B3_PIN, INPUT);
  pinMode(B4_PIN, INPUT);
  pinMode(B5_PIN, INPUT);
  pinMode(B6_PIN, INPUT);
  pinMode(OUTPUT_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  ppmEncoder.begin(OUTPUT_PIN);
  Serial.begin(9600);
}

int readAnalog(int pin)
{
  int sensorValue = analogRead(pin);
  sensorValue = map(sensorValue, 0, 1023, 500, 2500);
  
  if (abs(sensorValue - 1500) <= deadField) sensorValue = 0;

  return sensorValue;
}

int readMode()
{
  if (digitalRead(B2_PIN)) return DISARM;
  else if (digitalRead(B3_PIN)) return HORIZON;
  else if (digitalRead(B4_PIN)) return GPS_HOLD;
  else if (digitalRead(B6_PIN)) return GPS_MISSION;
  else if (digitalRead(B5_PIN)) return GPS_RTH;
  //else if (digitalRead(B6_PIN)) return UNDEFINED_YET;
}

void updateMode()
{
  int newMode = readMode();
  if (newMode != currentMode)
  {
    currentMode = newMode;
    triggerTime = millis();
  }
}

void loop() {

  updateMode();
  
  if (millis() - triggerTime < 200) digitalWrite(BUZZER_PIN, true);
  else digitalWrite(BUZZER_PIN, false);
  
  ppmEncoder.setChannel(0, readAnalog(P_PIN));
  ppmEncoder.setChannel(1, readAnalog(R_PIN));
  ppmEncoder.setChannel(2, readAnalog(T_PIN));
  ppmEncoder.setChannel(3, readAnalog(Y_PIN));
  ppmEncoder.setChannel(4, map(currentMode, 1000, 2000, 500, 2500));

  Serial.print(readAnalog(P_PIN));
  Serial.print("  ");
  Serial.print(readAnalog(R_PIN));
  Serial.print("  ");
  Serial.print(readAnalog(T_PIN));
  Serial.print("  ");
  Serial.print(readAnalog(Y_PIN));
  Serial.print(" | ");
  Serial.println(currentMode);

}
