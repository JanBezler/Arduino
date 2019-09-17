int potpin = A0;
int val;
///////////////////////////////////////////////////////////
void setup() {
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(A3,OUTPUT);
pinMode(A4,OUTPUT);
pinMode(A5,OUTPUT);
Serial.begin(9600);
}
/////////////////////////////////////////////////////////////

void c0()//{2,3,4,5,6,7};
{
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);
  digitalWrite(6, HIGH);
}
void c1()//{3,4};
{
  digitalWrite(7, HIGH);
  digitalWrite(3, HIGH);
}
void c2()//{2,3,8,6,5};
{
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A5, HIGH);
  digitalWrite(A4, HIGH);
}
void c3()//{2,3,8,4,5};
{
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A3, HIGH);
}
void c4()//{3,4,7,8};
{
  digitalWrite(3, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(A3, HIGH);
}
void c5()//{2,7,8,4,5};
{
  digitalWrite(2, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(A3, HIGH);
}
void c6()//{2,4,5,6,7,8};
{
  digitalWrite(2, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(A3, HIGH);
}
void c7()//{2,3,4};
{
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(7, HIGH);
}
void c8()//{2,3,4,5,6,7,8};
{
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(6, HIGH);
}
void c9()//{2,3,4,5,7,8};
{
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(A3, HIGH);
}
////////////////////////////////////////////////
void clean()
{
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(7, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
}
//////////////////////////////////////////////////////////////////////////////
void secondDigit()
{
  delay(5);
  clean();
  int mod = val%10;
  digitalWrite(5, LOW);
  if(mod == 0){c0();}
  else if(mod == 1){c1();}
  else if(mod == 2){c2();}
  else if(mod == 3){c3();}
  else if(mod == 4){c4();}
  else if(mod == 5){c5();}
  else if(mod == 6){c6();}
  else if(mod == 7){c7();}
  else if(mod == 8){c8();}
  else if(mod == 9){c9();}
  delay(5);
}

//////////////////////////////////////////////
void loop() {
  val = analogRead(potpin);
  val = map(val, 0, 1023, 0, 300);
  Serial.println(val);

  if(val > 99)
  {
    clean();
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(A3, HIGH);
  }
  else if(val > 89)
  {
    clean();
    digitalWrite(4, LOW);
    c9();
    secondDigit();
    
  }
  else if(val > 79)
  {
    clean();
    digitalWrite(4, LOW);
    c8();
    secondDigit();
  }
  else if(val > 69)
  {
    clean();
    digitalWrite(4, LOW);
    c7();
    secondDigit();
  }
  else if(val > 59)
  {
    clean();
    digitalWrite(4, LOW);
    c6();
    secondDigit();
  }
  else if(val > 49)
  {
    clean();
    digitalWrite(4, LOW);
    c5();
    secondDigit();
  }
  else if(val > 39)
  {
    clean();
    digitalWrite(4, LOW);
    c4();
    secondDigit();
  }
  else if(val > 29)
  {
    clean();
    digitalWrite(4, LOW);
    c3();
    secondDigit();
  }
  else if(val > 19)
  {
    clean();
    digitalWrite(4, LOW);
    c2();
    secondDigit();
  }
  else if(val > 9)
  {
    clean();
    digitalWrite(4, LOW);
    c1();
    secondDigit();
  }
  else if(val > -1)
  {
    clean();
    digitalWrite(4, LOW);
    c0();
    secondDigit();
  }
  delay(2);
}
