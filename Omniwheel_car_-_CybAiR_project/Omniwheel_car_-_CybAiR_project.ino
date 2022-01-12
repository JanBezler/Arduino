#define ShiftRegisterPWM_CUSTOM_INTERRUPT
#include "ShiftRegisterPWM.h"
#include <Servo.h>

////////////// PINS ////////////////

#define dataPin 2
#define clockPin 3
#define latchPin 4

#define frontServoPin 5
#define frontHcTriggPin 6
#define frontHcEchoPin 7

////////////// VARIABLES ////////////////

#define dfAngle 110
#define dlAngle dfAngle - 35
#define drAngle dfAngle + 35

Servo frontServo;
ShiftRegisterPWM sr(1, 32);

int straightSpeed = 0;
int turnSpeed = 0;
bool lookAround = false;
bool autonomous = false;
int distDiff = 0;

unsigned short wheels[8] = {0, 0, 0, 0, 0, 0, 0, 0};

////////////// SETUP ////////////////

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(frontHcTriggPin, OUTPUT);
    pinMode(frontServoPin, OUTPUT);
    pinMode(frontHcEchoPin, INPUT);
    frontServo.attach(frontServoPin);
    //TIMER2_COMPA_vect
    cli();
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2 = 0;
    OCR2A = 38;
    TCCR2B |= (1 << CS22);
    TCCR2A |= (1 << WGM21);
    TIMSK2 |= (1 << OCIE2A);
    sei();

    for (int i = 0; i < 8; i++)
    {
        sr.set(i, 0);
    }
    Serial.setTimeout(10);
}

ISR(TIMER2_COMPA_vect)
{
    cli();
    sr.update();
    sei();
}

////////////// DRIVING WHEELS ////////////////

void setWheelsSpeed()
{
    float v = (101 - abs(turnSpeed)) * (straightSpeed / 100) + straightSpeed;
    float w = (101 - abs(straightSpeed)) * (turnSpeed / 100) + turnSpeed;
    float right = (v + w) * 2.55;
    float left = (v - w) * 2.55;

    if (left > 255)
        left = 255;
    else if (left < -255)
        left = -255;

    if (right > 255)
        right = 255;
    else if (right < -255)
        right = -255;

    if (left < 0)
    {
        left *= -1;
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
        right *= -1;
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

    applyChangesOnWheels();
}

void applyChangesOnWheels()
{
    for (int i = 0; i < 8; i++)
    {
        sr.set(i, wheels[i]);
    }
}

////////////// SENSORS/SERVO ////////////////

int runServo()
{
    frontServo.write(drAngle);
    delay(300);
    int dr = getDistance();

    frontServo.write(dlAngle);
    delay(500);
    int dl = getDistance();

    return dl - dr;
}

float getDistance()
{
    digitalWrite(frontHcTriggPin, LOW);
    delayMicroseconds(2);
    digitalWrite(frontHcTriggPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(frontHcTriggPin, LOW);
    long duration = pulseIn(frontHcEchoPin, HIGH);
    return (duration * 0.034 / 2);
}

////////////// IN/OUT ////////////////

void readInput()
{
    while (Serial.available() > 0)
    {
        String str = Serial.readString();
        String strvalue = "";
        autonomous = false;

        for (int i = 0; i <= 3; i++)
        {
            if (str[i] != ' ')
                strvalue += str[i];
        }
        straightSpeed = strvalue.toInt();

        strvalue = "";

        for (int i = 5; i <= str.length(); i++)
        {
            if (str[i] != ' ')
                strvalue += str[i];
        }
        turnSpeed = strvalue.toInt();

        for (int i = 0; i <= str.length(); i++)
        {
            if (str[i] == 'a')
                autonomous = true;
            if (str[i] == 's')
                autonomous = false;
        }
    }
}

////////////// MAIN LOOP ////////////////

void loop()
{

    readInput();
    lookAround = false;

    if (autonomous)
    {
        straightSpeed = 80;
        turnSpeed = 0;
        int df = getDistance();
        Serial.println(df);

        if (df < 25)
        {
            straightSpeed = 0;
            turnSpeed = 0;

            setWheelsSpeed();
            delay(300);

            lookAround = true;

            if (distDiff > 0)
                turnSpeed = 80;
            else
                turnSpeed = -80;
            frontServo.write(dfAngle);
        }
    }

    setWheelsSpeed();
    if (lookAround)
        delay(800 + random(200));
}
