int latchPin = 3;
int dataPin = 2;
int clockPin = 4;

int digit1 = 7;
int digit2 = 8;
int buzzer = 13;

int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34};
int n = sizeof(arr)/ sizeof(arr[0]);
int first, second, which = 0;

void setup() {

  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  Serial.begin(9600);
  randomize (arr, n); 
  printArray(arr, n);

  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT); //dig
  pinMode(7,OUTPUT); //dig
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);

  
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

if (x==0){
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(9, HIGH);}
if (x==1){
  digitalWrite(6, HIGH);
  digitalWrite(A4, HIGH);}
if (x==2){
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(A0, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A1, HIGH);}
if (x==3){
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A0, HIGH);}
if (x==4){
  digitalWrite(9, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(A0, HIGH);
  digitalWrite(A4, HIGH);}
if (x==5){
  digitalWrite(5, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A0, HIGH);}
if (x==6){
  digitalWrite(5, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A0, HIGH);
  digitalWrite(9, HIGH);}
if (x==7){
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(A4, HIGH);}
if (x==8){
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A4, HIGH);}
if (x==9){
  digitalWrite(6, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(A0, HIGH);}
  
delay(2);

 digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(9, LOW);

  }

int showNumbers(int x, int y){
  float t = 0;
  digitalWrite(buzzer, HIGH);
  while (t <= 5000)
   {
    if(t == 300){digitalWrite(buzzer, LOW);}
    if(t == 360){digitalWrite(buzzer, HIGH);}
    if(t == 600){digitalWrite(buzzer, LOW);}
    digitalWrite(digit1, LOW);
    displayD(x);
    delay(10);
    digitalWrite(digit1, HIGH);

    digitalWrite(digit2, LOW);
    displayD(y);
    delay(10);
    digitalWrite(digit2, HIGH);
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
   randomSeed (analogRead(A6));
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
  if(analogRead(A7) < 10)
    {
    split(arr[which]);
    showNumbers(first,second);
    which++;
    if(which == 34){resetFunc();}
    }
    
}

