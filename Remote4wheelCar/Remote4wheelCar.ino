#include "ShiftRegisterPWM.h"

#define pinB A0
#define pinF A1
#define pinL A2
#define pinR A3

#define dataPin 2  // y
#define clockPin 3 // b
#define latchPin 4 // r

unsigned short wheels[8] = {0, 0, 0, 0, 0, 0, 0, 0};
ShiftRegisterPWM sr(1, 16);

void setup()
{
    pinMode(dataPin, OUTPUT);  // sr data pin
    pinMode(clockPin, OUTPUT); // sr clock pin
    pinMode(latchPin, OUTPUT); // sr latch pin

    Serial.begin(9600);
    sr.interrupt(ShiftRegisterPWM::UpdateFrequency::SuperFast);
}

bool readState(int pin)
{
    short pinValue = analogRead(pin);
    if (pinValue == 0)
        return true;
    else
        return false;
}

enum Heading
{
    STOP = 0,
    FORWARD = 1,
    BACKWARD = 2,
    RIGHT = 3,
    LEFT = 4,
    FORWARD_RIGHT = 5,
    FORWARD_LEFT = 6,
    BACKWARD_RIGHT = 7,
    BACKWARD_LEFT = 8
};

short getHeading()
{
    bool f = readState(pinF);
    bool b = readState(pinB);
    bool r = readState(pinR);
    bool l = readState(pinL);

    if (f && !b && r && !l)
        return Heading::FORWARD_RIGHT;
    else if (f && !b && !r && l)
        return Heading::FORWARD_LEFT;
    else if (!f && b && r && !l)
        return Heading::BACKWARD_RIGHT;
    else if (!f && b && !r && l)
        return Heading::BACKWARD_LEFT;
    else if (f && !b && !r && !l)
        return Heading::FORWARD;
    else if (!f && b && !r && !l)
        return Heading::BACKWARD;
    else if (!f && !b && r && !l)
        return Heading::RIGHT;
    else if (!f && !b && !r && l)
        return Heading::LEFT;
    else
        return Heading::STOP;
}

void setWheelsSpeed(short heading)
{
    short straightSpeed = 255;
    short rotationSpeed = 200;
    float combineRatio = 1;

    for (int w = 0; w < 8; w++)
        wheels[w] = 0;

    switch (heading)
    {
    case Heading::FORWARD:
        wheels[0] = straightSpeed;
        wheels[2] = straightSpeed;
        wheels[4] = straightSpeed;
        wheels[6] = straightSpeed;
        break;
    case Heading::BACKWARD:
        wheels[1] = straightSpeed;
        wheels[3] = straightSpeed;
        wheels[5] = straightSpeed;
        wheels[7] = straightSpeed;
        break;
    case Heading::RIGHT:
        wheels[4] = rotationSpeed;
        wheels[2] = rotationSpeed;
        wheels[1] = rotationSpeed;
        wheels[7] = rotationSpeed;
        break;
    case Heading::LEFT:
        wheels[0] = rotationSpeed;
        wheels[6] = rotationSpeed;
        wheels[3] = rotationSpeed;
        wheels[5] = rotationSpeed;
        break;
    case Heading::FORWARD_RIGHT:
        wheels[4] = straightSpeed;
        wheels[2] = straightSpeed;
        wheels[0] = rotationSpeed * combineRatio;
        wheels[6] = rotationSpeed * combineRatio;
        break;
    case Heading::FORWARD_LEFT:
        wheels[0] = straightSpeed;
        wheels[6] = straightSpeed;
        wheels[4] = rotationSpeed * combineRatio;
        wheels[2] = rotationSpeed * combineRatio;
        break;
    case Heading::BACKWARD_RIGHT:
        wheels[3] = straightSpeed;
        wheels[5] = straightSpeed;
        wheels[7] = rotationSpeed * combineRatio;
        wheels[1] = rotationSpeed * combineRatio;
        break;
    case Heading::BACKWARD_LEFT:
        wheels[7] = straightSpeed;
        wheels[1] = straightSpeed;
        wheels[3] = rotationSpeed * combineRatio;
        wheels[5] = rotationSpeed * combineRatio;
        break;

    default:
        break;
    }

    applyChangesOnWheels();
}

void applyChangesOnWheels()
{
    for (int w = 0; w < 8; w++)
    {
        sr.set(w, wheels[w]);
    }
}

void loop()
{
    short heading = getHeading();
    setWheelsSpeed(heading);
    if (true)
    {
        Serial.print(analogRead(pinF));
        Serial.print("\t");
        Serial.print(analogRead(pinB));
        Serial.print("\t");
        Serial.print(analogRead(pinR));
        Serial.print("\t");
        Serial.print(analogRead(pinL));
        Serial.print("\t");
        Serial.print("heading:");
        Serial.print(heading);
        Serial.print("\n");
    }
    delay(5);
}
