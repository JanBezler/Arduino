#define dataPin 10
#define latchPin 11
#define clockPin 12

#define backHcTriggPin 9
#define backHcResponsePin 8
#define frontHcTriggPin 7
#define frontHcResponsePin 6
#define frontHcServoPin 5


void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
}





void loop() {


}
