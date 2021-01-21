#include "ShiftRegisterPWM.h"

#define dataPin 2
#define clockPin 3
#define latchPin 4

#define backHcTriggPin 9
#define backHcResponsePin 8
#define frontHcTriggPin 7
#define frontHcResponsePin 6
#define frontServoPin 5

ShiftRegisterPWM sr(1, 30);

int straightSpeed = 0;
int turnSpeed = 0;
unsigned short wheels[8] = {0,0,0,0,0,0,0,0};

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(backHcTriggPin, OUTPUT);
  pinMode(frontHcTriggPin, OUTPUT);
  pinMode(frontServoPin, OUTPUT);
  pinMode(frontHcResponsePin, INPUT);
  pinMode(backHcResponsePin, INPUT);
  sr.interrupt(ShiftRegisterPWM::UpdateFrequency::SuperFast);
  for (int i=0;i<8;i++)
  {
    sr.set(i,0);
  }
  Serial.setTimeout(10);
}

void setWheelsSpeed()
{
  short left = straightSpeed + turnSpeed;
  short right = straightSpeed - turnSpeed;

  if (left > 255) left = 255;
  else if (left < -255) left = -255; 
  if (right > 255) right = 255;
  else if (right < -255) right = -255; 

  if (left < 0)
  {
      wheels[3] = left;
      wheels[5] = left;
      wheels[2] = 0;
      wheels[4] = 0;
  }
  else
  {
      wheels[2] = left;
      wheels[4] = left;
      wheels[3] = 0;
      wheels[5] = 0;
  }

  if (right < 0)
  {
      wheels[1] = right;
      wheels[7] = right;
      wheels[0] = 0;
      wheels[6] = 0;
  }
  else
  {
      wheels[0] = right;
      wheels[6] = right;
      wheels[1] = 0;
      wheels[7] = 0;
  }
}

void applyChangesOnWheels()
{
   for (int i=0;i<8;i++)
  {
    sr.set(i,wheels[i]);
  }
}

void readInput()
{
  while(Serial.available() > 0 )
  {
    String str = Serial.readString();
    Serial.println(str);
    char typeOfData = str[0];
    String strvalue = "";

    for (int i=0; i<str.length(); i++)
    {
      if (i>0) strvalue += str[i];
    }
    int value = strvalue.toInt();
    
    if(typeOfData == 's') straightSpeed = value;
    else if (typeOfData == 't') turnSpeed = value;
   
  }  
}


void loop() 
{
  readInput();
  setWheelsSpeed();
  applyChangesOnWheels();

}
