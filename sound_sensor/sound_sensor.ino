int soundsensor = 2; //digital pin connected to sound sensor
int pb = 4;//digital pin connected to push button 
int pbstate; //to store push button's state
int timer; //to store current time
int maxtime = 20; //max time of listening to sound sensor
int counter = 0; //count number of sound detected by sensor 

void setup(){
  //setup serial monitor 
  Serial.begin(9600);

  //setup push button pin 
  pinMode(pb,INPUT);
  //setup sound sensor pin
  pinMode(soundsensor,INPUT);
}

void loop() {
  //read the push button 
  pbstate = digitalRead(pb);

  //check if push button has been pressed
  if (pbstate == LOW){
    Serial.println("Listening....");

    //delay after push button so sound to avoid unnecessary sound counted
    delay(1000);
    
    //assign the current time in seconds
    timer = millis()/1000;

    //only listen to the sound sensor for 'maxtime' number of seconds
    while(((millis()/1000) - timer) < maxtime){

      //if statement to check if sound pass threshold set by potentiometer
      //if pass, sensor input HIGH
      //otherwise, sensor input LOW
      if(digitalRead(soundsensor) == HIGH){
        //print that sound was detected
        Serial.println("Sound detected!");

        //increase counter by 1
        counter++;

        //must delay after sound is detected
        //due to real time processing, the sensor might think more than 1 sound was detected
        delay(500);
      } 
    }

    //printing the summary
    Serial.print("Number of sounds detected: ");
    Serial.println(counter);
    Serial.println("finished");

    //reset counter 
    counter = 0;
  }

  //delay to avoid more than one push button pressed at a given time 
  delay(500);
}
