//sound sensor
int soundsensor=2;

//Ultrasonic sensor
int trig = 6;
int echo = 7;
float duration, distance;
int speed;

//push button
int pb=4;
int pbstate;

//timer and counter
int timer;
int timer_forward;
int timer_left;
int timer_right;
int timer_reverse;
int timer_shadow;
int maxtime=5;
int counter=0;

//LED pins
int led1 = 12;
int led2 = 11;
int led3 = 10;
int led4 = 9;
int led5 = 8;


void setup(){
  //setup serial monitor
  Serial.begin(9600);

  //Setup ultrasonic sensor pins
  pinMode(trig,OUTPUT);//send out waves
  pinMode(echo,INPUT);//receive the waves
  
  //setup pb pin
  pinMode(pb,INPUT);
  
  //setup sound sensor pin
  pinMode(soundsensor,INPUT);
  
  //setup led pins
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
}

void loop(){
  //read the pb
  pbstate=digitalRead(pb);
  
  //check if pb has been pressed
  if(pbstate==LOW){
   Serial.println("Listening...");
   
   //delay after pb to avoid unnecessary sound counted
   delay(1000);

   //assign the current time in sec
   timer=millis()/1000;

   //only listen to the sound sensor for max time number of sec
   while(((millis()/1000)-timer)<maxtime){

    //if statement to check if sound pass threshold by potentiometer
    //if pass,sensor input high
    //otherwise,sensor input low
    if(digitalRead(soundsensor)==HIGH){
      //print that sound was detected
      Serial.println("Sound was detected!");

      //increase counter by 1
      counter++;

      //must delay after sound is detected
      //due to real time processing, the sensor might think more than 1 sound was detected
      delay(500);
    }
   }

   if(counter==1){
    forward();
   }
   else if(counter==2){
    left();
   }
   else if(counter==3){
    right();
   }
   else if(counter==4){
     reverse();
   }
   else if(counter==5){
     shadow();
   }
  else{
    Serial.println("Snaps more than 5 are unavailable now. Please press again!");
  }

   //print the summary
   Serial.print("Number of sounds detected:");
   Serial.println(counter);
   Serial.println("finished");

   //reset counter
   counter=0;
  }

  //delay to avoid more than 1 pb pressed at a given time
  delay(500);
}

//setting total function
void forward(){
  //assign the current time in sec
  timer_forward=millis()/1000;
  
  while(((millis()/1000)-timer_forward)<2){
    forwardLED();
    forwardMotion(150); //set speed directly
    delay(1000);
  }
}

void left(){
  //assign the current time in sec
  timer_left=millis()/1000;
  
  while(((millis()/1000)-timer_left)<2){
    leftLED();
    leftMotion();
    delay(1000);
  }
}

void right(){
  //assign the current time in sec
  timer_right=millis()/1000;
  
  while(((millis()/1000)-timer_right)<2){
    rightLED();
    rightMotion();
    delay(1000);
  }
}

void reverse(){
  //assign the current time in sec
  timer_reverse=millis()/1000;
  
  while(((millis()/1000)-timer_reverse)<2){
    reverseLED();
    reverseMotion(150); //set speed directly
    delay(1000);
  }
}

void shadow(){
  //set the past time
  timer_shadow = millis()/1000;
  
  //only run for the maxtime
  while((millis()/1000-timer_shadow)<maxtime){
  	digitalWrite(trig,LOW);
    delayMicroseconds(10);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    
    duration=pulseIn(echo,HIGH); //calculate time
    
    distance=(duration*0.034)/2;
    
    //print the distance calculated
    Serial.print("Distance:");
    Serial.print(distance);
    Serial.println(" cm");
    
    //distance is directly proportional to speed
    if(distance>4){
      speed=map(distance,4,330,0,255);
      
      //move car forward
      forwardMotion(speed);  
  	}
  
    else{
      speed=map(distance,4,0,0,255);

      reverseMotion(speed);
    }

   delay(1000);

  }
  
  //off motor
  //offmotor();

}

//setting motion functions
void forwardMotion(int speed){
  Serial.println("Moving forward! :D");
  Serial.println();
}

void leftMotion(){
  Serial.println("Moving left! :D");
  Serial.println();
}

void rightMotion(){
  Serial.println("Moving right! :D");
  Serial.println();
}

void reverseMotion(int speed){
  Serial.println("Moving backwards! :D");
  Serial.println();
}

void offmotor(){
  Serial.println("Stop Motor! :D");

}

//motion: forward
void forwardLED(){
  light1();
  delay(100);
  
  light2();
  delay(100);
  
  light3();
  delay(100);
  
  light4();
  delay(100);
  
  light5();
  delay(100);
  
  resetLED();
}
  
//motion: reverse
void reverseLED(){
  light5();
  delay(100);
  
  light4();
  delay(100);
  
  light3();
  delay(100);
  
  light2();
  delay(100);
  
  light1();
  delay(100);
  
  resetLED();
}

//motion: left
void leftLED(){
  light6();
  delay(200);
  
  light7();
  delay(200);
  
  light3();
  delay(200);
  
  resetLED();
}

//motion: right
void rightLED(){
  light3();
  delay(200);
  
  light7();
  delay(200);
  
  light6();
  delay(200);
  
  resetLED();
}

//only to light up the 1st LED
void light1(){
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
}

//only light led2
void light2(){
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
}

//only to light up the 3rd LED
void light3(){
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
}
  
//only to light up the 4th LED
void light4(){
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, LOW);
}
  
//only to light up the 5th LED
void light5(){
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, HIGH);
}

//light 1st and 5th led
void light6(){
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, HIGH);
}

//light 2nd and 4th led
void light7(){
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, LOW);
}

//reset all
void resetLED(){
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
}
