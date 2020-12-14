#include "ShiftRegisterPWM.h"

#define dataPin 10
#define latchPin 11
#define clockPin 12

#define backHcTriggPin 9
#define backHcResponsePin 8
#define frontHcTriggPin 7
#define frontHcResponsePin 6
#define frontServoPin 5

const int direcrtionList[11] = {'q','w','e','a','s','d','z','x','c','r','t'};
const bool dQ[8] = {1,0,0,0,1,0,0,0};
const bool dW[8] = {1,0,1,0,1,0,1,0};
const bool dE[8] = {0,0,1,0,0,0,1,0};
const bool dA[8] = {1,0,0,1,1,0,1,1};
const bool dS[8] = {0,0,0,0,0,0,0,0};
const bool dD[8] = {0,1,1,0,0,1,1,0};
const bool dZ[8] = {0,0,0,1,0,0,0,1};
const bool dX[8] = {0,1,0,1,0,1,0,1};
const bool dC[8] = {0,1,0,0,0,1,0,0};
const bool dR[8] = {1,0,0,1,0,1,1,0};
const bool dT[8] = {0,1,1,0,1,0,0,1};
int currentDirection = 's';
int currentSpeed = 0;

ShiftRegisterPWM sr(1, 10);

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
  sr.interrupt(ShiftRegisterPWM::UpdateFrequency::Medium);
}


void goInDirectionPWM()
{
  const bool *arr;
  switch (currentDirection)
  {
    case 'q': arr = dQ; break;
    case 'w': arr = dW; break;
    case 'e': arr = dE; break;
    case 'a': arr = dA; break;
    case 's': arr = dS; break;
    case 'd': arr = dD; break;
    case 'z': arr = dZ; break;
    case 'x': arr = dX; break;
    case 'c': arr = dC; break;
    case 'r': arr = dR; break;
    case 't': arr = dT; break;
  }


  for (int i=0;i<8;i++)
  {
    sr.set(i,currentSpeed*arr[i]);
    Serial.print(arr[i]*currentSpeed);
    Serial.print(" ");
  }
  Serial.println();
  
}


int readInput()
{
  int input = Serial.read();

  for (int i=0; i<11; i++){
    if (input == direcrtionList[i]) currentDirection = input;
  }
  if ((input>='0') && (input<='9')) currentSpeed = (input-48)*(28.34);  
}


void loop() 
{
  int oldDirection = currentDirection;
  int oldSpeed = currentSpeed;
  
  readInput();

  if ((oldDirection != currentDirection) || (oldSpeed != currentSpeed))
  {
    Serial.println();
    Serial.print("Direction: ");
    Serial.print(char(currentDirection));
    Serial.print(" | ");
    Serial.print("Speed: ");
    Serial.println(currentSpeed);
    goInDirectionPWM();
    

  }
  
  delay(10);
}
