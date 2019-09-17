int latchPin = 3;
int dataPin = 2;
int clockPin = 4;

int digit1 = 12;
int digit2 = 11;
int buzzer = 13;

int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34};
int n = sizeof(arr)/ sizeof(arr[0]);
int first, second, which = 0;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A7, INPUT);
  Serial.begin(9600);
  randomize (arr, n); 
  printArray(arr, n);
}

void(* resetFunc) (void) = 0; 

int digit(int x){
  x==0 ? x=64 : x=x;
  x==1 ? x=121 : x=x;
  x==2 ? x=36 : x=x;
  x==3 ? x=48 : x=x;
  x==4 ? x=25 : x=x;
  x==5 ? x=18 : x=x;
  x==6 ? x=2 : x=x;
  x==7 ? x=120 : x=x;
  x==8 ? x=0 : x=x;
  x==9 ? x=24 : x=x;
  return(x);
  }

void displayD(int x){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit(x));
  digitalWrite(latchPin, HIGH);
  }

int showNumbers(int x, int y){
  float t = 0;
  digitalWrite(buzzer, HIGH);
  while (t <= 5000)
   {
    if(t == 600){digitalWrite(buzzer, LOW);}
    digitalWrite(digit1, HIGH);
    displayD(x);
    delay(10);
    digitalWrite(digit1, LOW);

    digitalWrite(digit2, HIGH);
    displayD(y);
    delay(10);
    digitalWrite(digit2, LOW);
    t+=20;
   }
   return(0);
  }

void swap (int *a, int *b){ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
  } 

void randomize ( int arr[], int n ){
   randomSeed (analogRead(A7));
    for (int i = n-1; i > 0; i--) 
      { 
        int j = random() % (i+1); 
        swap(&arr[i], &arr[j]); 
      } 
   }

void printArray (int arr[], int n){ 
    for (int i = 0; i < n; i++) 
        Serial.println(arr[i]); 
  } 


int split(int z){
  if(z >= 30){
    first = 3;
    second = z - 30;}
  else if(z >= 20){
    first = 2;
    second = z - 20;}
  else if(z >= 10){
    first = 1;
    second = z - 10;}
  else{
    first = 0;
    second = z;}
  }


void loop() 
{ 
  if(analogRead(A0) < 10)
    {
    split(arr[which]);
    showNumbers(first,second);
    which++;
    if(which == 34){resetFunc();}
    }
    
}

