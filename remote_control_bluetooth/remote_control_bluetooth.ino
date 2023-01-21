#include <LiquidCrystal.h>

//lcd variables
const int rs = 8;
const int en = 9;
const int d4 = 4;
const int d5 = 5;
const int d6 = 6;
const int d7 = 7;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

//motor variables
//motor A
int en34 = 11;
int in4 = A4;
int in3 = A3;

//motor B
int en12 = 3;
int in1 = A1;
int in2 = A2;

//bluetooth
int state;

void setup()
{
  Serial.begin(9600);//bluetooth rate of coms
  
  //LCD (colomns, rows)
  lcd.begin(16,2);
  lcd.print("Movement");
  
  //setup for each motor pin to be output
  pinMode(en34, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  pinMode(en12, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  //initial state of motor
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
 
}

void loop()
{ 
  state=0;
  lcd.setCursor(0,1);
  if(Serial.available()>0){
    
    state=Serial.read();
    switch(state){
      case 1:
      forward();
      lcd.print("F");
      break;

      case 2:
      left();
      lcd.print("L");
      break;

      case 3:
      right();
      lcd.print("R");
      break;
      
      case 4:
      backward();
      lcd.print("B");
      break;
      
      default:
      Stop();
      lcd.print("S"); 
      break;
      
    }
  }
}


void forward(){
  //PWM pin to set motor to max speed
  analogWrite(en12,90);
    analogWrite(en34,90);
  
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
}
void left(){
  //to turn right
  analogWrite(en12,100);
    analogWrite(en34,60);
  
}
void right(){
  //to turn left
  analogWrite(en12,60);
    analogWrite(en34,100);
}
void backward(){
  //PWM pin to set motor to max speed
  analogWrite(en34,100);
  analogWrite(en12,100);

  digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
}

void Stop(){
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
}
