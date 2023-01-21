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

//ultrasonic sensors
int trig=12;
int echo=13;
float duration, distance;

void setup() {
  //LCD (colomns, rows)
  lcd.begin(16,2);
  lcd.print("Distance in cm:");

  //ultrasonic sensor pin mode
  pinMode(trig,OUTPUT);//send out waves 
  pinMode(echo,INPUT);//receive waves
  
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

  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig,LOW);
  delayMicroseconds(10);
  digitalWrite(trig,HIGH);//transmit ultrasonic waves
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  //set to HIGH to only record when goes from 0 to 1 input
  //float data type
  duration=pulseIn(echo,HIGH);//getting time
  
  //0.0343 centimeter/microseconds which is speed of sound 
  //float data type 
  distance=(duration*0.0343)/2;//getting distance in cm 

  //print distance on lcd screen
  lcd.setCursor(0,1);
  lcd.print(distance);
  
  if(distance>=25){
    forward();
  }
  else if(distance<25){
    Stop();
    delay(500);
    reverse();
    delay(500);
    Stop();
    delay(100);
    turn();
    delay(500);

  }
  delay(500);

}

void forward(){
  analogWrite(en34,90);
  analogWrite(en12,85);
  
  digitalWrite(in4,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
}

void reverse(){
  analogWrite(en34,100);
  analogWrite(en12,100);
  
  digitalWrite(in4,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
}
void Stop(){
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
}
void turn(){
  analogWrite(en12,100);
  analogWrite(en34,100);
  
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  
}
