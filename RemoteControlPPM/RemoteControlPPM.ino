#include "PPMEncoder.h"

#define MAX 1950
#define MIN 980
#define MID (MAX-MIN)/2+MIN

#define OUTPUT_PIN 10
#define BUZZER_PIN 8

#define Y_PIN A0
#define T_PIN A2
#define R_PIN A1
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
   
int deadField = 0;
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
  
  ppmEncoder.setChannel(0, MID);
  ppmEncoder.setChannel(1, MID);
  ppmEncoder.setChannel(2, MID);
  ppmEncoder.setChannel(3, MID);
  ppmEncoder.setChannel(4, DISARM);
}

int readAnalog(int pin, bool reverse)
{
  int sensorValue = analogRead(pin);
  if (reverse) sensorValue = map(sensorValue, 0, 1023, MAX, MIN);
  else sensorValue = map(sensorValue, 0, 1023, MIN, MAX);
  
  if (abs(sensorValue - MID) <= deadField) sensorValue = MID;

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

  ppmEncoder.setChannel(0, readAnalog(R_PIN, true)+1);
  ppmEncoder.setChannel(1, readAnalog(P_PIN, false)+72);
  ppmEncoder.setChannel(2, readAnalog(T_PIN, false)-9);
  ppmEncoder.setChannel(3, readAnalog(Y_PIN, false)+1);
  ppmEncoder.setChannel(4, map(currentMode, 1000, 2000, MIN, MAX)+30);

}
