// input
const int throttle_read = A5;
const int left_read = 3;
const int right_read = 2;
const int brake_read = 4;

//output
const int throttle_write = 9;
const int left_write = 5;
const int right_write = 6;
const int brake_write = 7;

//variables
bool left_in = false;
bool right_in = false;
bool left_out = false;
bool right_out = false;
bool brake = true;
int throttle = 127;
int raw_throttle = 0;

unsigned long previousMillis_turn = 0;
unsigned long previousMillis_blink = 0;
unsigned int turn_time = 6000;
unsigned int blink_interval = 500;
bool blink_state = false;

void setup() {
  pinMode(throttle_read, INPUT);
  pinMode(left_read, INPUT);
  pinMode(right_read, INPUT);
  pinMode(brake_read, INPUT);
  
  pinMode(throttle_write, OUTPUT);
  pinMode(left_write, OUTPUT);
  pinMode(right_write, OUTPUT);
  pinMode(brake_write, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  //reading values from pins
  raw_throttle = analogRead(throttle_read);
  right_in = digitalRead(right_read);
  left_in = digitalRead(left_read);
  brake = digitalRead(brake_read);
  
  //computing throttle values
  throttle = map(raw_throttle, 0, 1023, 127, 255);
  if(throttle <= 134){
    brake = true;
  }

  //computing left and right blinking
  if(right_in){
    right_out = true;
    previousMillis_turn = millis();
  }
  if(left_in){
    left_out = true;
    previousMillis_turn = millis();
  }

  if(right_out and left_out){
    right_out = false;
    left_out = false;
  }

  if(right_out or left_out){
    unsigned long currentMillis_turn = millis();
    if (currentMillis_turn - previousMillis_turn >= turn_time) {
    right_out = false;
    left_out = false;
    }

    unsigned long currentMillis_blink = millis();
    if (currentMillis_blink - previousMillis_blink >= blink_interval) {
      previousMillis_blink = currentMillis_blink;
      if (blink_state == LOW) {
        blink_state = HIGH;
      } else {
        blink_state = LOW;
      }
    }
  }

  //controlling
  if(brake){
    digitalWrite(brake_write, HIGH);
    analogWrite(throttle_write, 0);
  } else {
    digitalWrite(brake_write, LOW);
    analogWrite(throttle_write, throttle);
  }
 
  if(blink_state){
    if(left_out){
      digitalWrite(left_write, HIGH);
    }
    if(right_out){
      digitalWrite(right_write, HIGH);
    }
  } else {
    digitalWrite(right_write, LOW);
    digitalWrite(left_write, LOW);
  }

  Serial.println("-----------------");
  Serial.print("read: ");Serial.print(raw_throttle);
  Serial.print("   |   write: ");Serial.println(throttle);

  delay(100);
}
