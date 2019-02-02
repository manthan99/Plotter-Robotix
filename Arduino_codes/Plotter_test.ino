#include<Servo.h>

Servo Pen;
void setup() {
  pinMode(2,OUTPUT); pinMode(3,OUTPUT); pinMode(4,OUTPUT); pinMode(5,OUTPUT); // Horizontal
   pinMode(7,OUTPUT); pinMode(9,OUTPUT); pinMode(8,OUTPUT); pinMode(10,OUTPUT);// Vertical
   pinMode(12,INPUT); pinMode(13,INPUT);   // Limit switches
   pinMode(11,OUTPUT);
  Pen.attach(11);
  Pen.write(0);
   Serial.begin(9600);

}
int CountH=0, CountV=0, flag=0;
////////////////////////////////// Horizontal////////////////////////////////////////
int R(int Delay_ms, int dur)
{
  int count=0;
  unsigned long int t= millis();
  while(millis()-t <= dur)
  {
  digitalWrite(5,1);digitalWrite(2,1);delay(Delay_ms);
 digitalWrite(2,0);digitalWrite(4,1);delay(Delay_ms);
 digitalWrite(5,0);digitalWrite(3,1);delay(Delay_ms);
 digitalWrite(4,0);digitalWrite(2,1);delay(Delay_ms);
 digitalWrite(3,0);
 count++;
  }
  return count;
}

int L(int Delay_ms, int dur)
{
  int count=0;
  unsigned long int t= millis();
  while(millis()-t <=dur)
  {
  digitalWrite(2,1);digitalWrite(3,1);delay(Delay_ms);
  digitalWrite(2,0);digitalWrite(4,1);delay(Delay_ms);
  digitalWrite(3,0);digitalWrite(5,1);delay(Delay_ms);
  digitalWrite(4,0);digitalWrite(2,1);delay(Delay_ms);
  digitalWrite(5,0);
  count++;
  }
  
  return count;
}


///////////////////////////////////////Vertical///////////////////////////////////////////

int U(int Delay_ms, int dur)
{
  int count=0;
  unsigned long int t= millis();
  while(millis()-t <= dur)
  {
  digitalWrite(10,1);digitalWrite(7,1);delay(Delay_ms);
 digitalWrite(7,0);digitalWrite(9,1);delay(Delay_ms);
 digitalWrite(10,0);digitalWrite(8,1);delay(Delay_ms);
 digitalWrite(9,0);digitalWrite(7,1);delay(Delay_ms);
 digitalWrite(8,0);
 count++;
  }
  return count;
}

int D(int Delay_ms, int dur)
{
  int count=0;
  unsigned long int t= millis();
  while(millis()-t <=dur)
  {
  digitalWrite(7,1);digitalWrite(8,1);delay(Delay_ms);
  digitalWrite(7,0);digitalWrite(9,1);delay(Delay_ms);
  digitalWrite(8,0);digitalWrite(10,1);delay(Delay_ms);
  digitalWrite(9,0);digitalWrite(7,1);delay(Delay_ms);
  digitalWrite(10,0);
  count++;
  }
  
  return count;
}

////////////////////////////////Reset//////////////////////////////////
void S()
{
  digitalWrite(2,0); digitalWrite(3,0); digitalWrite(4,0); digitalWrite(5,0);
   digitalWrite(7,0); digitalWrite(8,0); digitalWrite(9,0); digitalWrite(10,0);
   Pen.write(0);
}

//////////////////////////////Homing//////////////////////////////////
void H()
{
  CountV = CountH =0;
  int H = digitalRead(12), V = digitalRead(13);
  S();
  while(H==0)
  {
    CountH += L(2,100);  H = digitalRead(12);    //Serial.print("\tH_val=\t"); Serial.print(H);
  }
  S();
  while(V==0)
  {
     CountV += D(2,100); V = digitalRead(13);
    //Serial.print("\tV_val=\t"); Serial.print(V);
  }
  S();
  Serial.print("H =\t"); Serial.print(CountH); Serial.print("\tV=\t"); Serial.println(CountV);
  CountV = CountH =0;
  
}

////////////////////////Servo/////////////////////////
void P()
{
  Pen.write(30);
  delay(10);
}

void N()
{
  Pen.write(0);
  delay(10);
}

char Cmd='S', Rec='S';
void loop() {
  while(1)
  {
    if (Serial.available())
    {
       Rec = Serial.read();
      
       flag =1;
    }
    if (Rec != '\n' && flag ==1)
    {
     
      Serial.print("H =\t"); Serial.print(CountH); Serial.print("\tV=\t"); Serial.println(CountV);
      CountH=0, CountV=0;      
      Cmd =  Rec;
      flag =0;
    }
    
   
      if (Cmd == 'R')  {CountH += R(2,20);} 
     else if (Cmd == 'L') { CountH += L(2,20);}
      else if(Cmd == 'U') {CountV += U(2,20); } 
      else if(Cmd == 'D') {CountV += D(2,20); }
      else if (Cmd == 'H') { H(); Cmd = S; S();  }
      else if (Cmd == 'P') {P();}
      else if (Cmd == 'N') {N();}
      else {S(); }
  }  
}
