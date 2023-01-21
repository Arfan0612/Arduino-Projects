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

//left sensor
int lsensor=13;
int ldetect;

//right sensor
int rsensor=12;
int rdetect;

//to store time
int timing;

void setup()
{
  lcd.clear(); 
  //LCD (colomns, rows)
  lcd.begin(16,2);
  lcd.print("time (s): ");
  
  //motor pinmode
  pinMode(en12, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  pinMode(en34, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
 
  //sensor
  pinMode(lsensor,INPUT);
  pinMode(rsensor,INPUT);
  //initial state of motor
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);

  Serial.begin(9600);

  delay(1000);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
 
}

void loop()
{
  timing=millis()/1000;
  lcd.setCursor(10,0);
  lcd.print(timing);

  //IR sensor
  ldetect=digitalRead(lsensor);
  rdetect=digitalRead(rsensor);

  lcd.setCursor(0,1);
  lcd.println(ldetect);

  lcd.setCursor(6,1);
  lcd.println(rdetect);
  
  if(rdetect==1 && ldetect==1){
    forward(timing);
  }
  else if(rdetect==0 && ldetect==1){
    right(timing);
  }
  else if(rdetect==1 && ldetect==0){
    left(timing);
  }
  else if(rdetect==0 && ldetect==0){
    Stop();
  }
}


void forward(int timing){
    analogWrite(en12,100);
    analogWrite(en34,100);
  
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);  
}

void right(int timing){ 
  if(timing>12){
    analogWrite(en12,70);
    analogWrite(en34,70);

    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
  }

  else{
    
    analogWrite(en12,100);
    analogWrite(en34,100);
    
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
  }
}
void left(int timing){
  if(timing>12){
    analogWrite(en12,70);
    analogWrite(en34,70);

    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
  }

  else{
    analogWrite(en12,100);
    analogWrite(en34,100);
    
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW); 
  }
}

void Stop(){
  analogWrite(en12,0);
  analogWrite(en34,0); 
}
