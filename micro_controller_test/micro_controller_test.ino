#include <Servo.h>//Using servo library to control ESC

Servo esc1; //Creating a servo class with name as esc
Servo esc2; //Creating a servo class with name as esc1
Servo esc3;

byte escPin1 = 2; 
byte escPin2 = 3;
byte escPin3 = 4;
int minPulseRate = 1000;
int maxPulseRate = 2000;
int throttleChangeDelay = 100;

int gThrottle = 1500;

void setup()

{
  Serial.begin(9600);
  //Init escs
  initEscs();
  for (int i = 1; i < 8; i++){
    delay(1000);
    Serial.println(i);
  }
  //startup cycle
  startUpMotors();
  //delay(7000);   // Delay for 4 seconds to let ESC power UP correctly
  //while(Serial.available() == 0) { }  //-snip-  // Wait for operator input before going to the loop()


}

void loop()
{

  if (Serial.available() > 0) {
      char command = Serial.read();
      
      switch (command) {
        case 'U':  // Increase throttle
          Serial.println("up");
          gThrottle += 10;
          if (gThrottle > 2000) {
            gThrottle = 2000;
          }
          break;
        case 'D':  // Decrease throttle
          Serial.println("down");
          gThrottle -= 10;
          if (gThrottle < 1000) {
            gThrottle = 1000;
          }
          break;

        case 'R':  // Decrease throttle
          Serial.println("reset");
          gThrottle = 1500;
          if (gThrottle < 1000) {
            gThrottle = 1000;
          }
          break;
      
      }
    }

  writeTo2Escs(gThrottle);
  //Serial.println("looping..");
  delay(throttleChangeDelay);  // delay so we don' t make changes tooo quickly
}

//Change velocity of the 2 escs at the same time
void writeTo2Escs(int throttle) {
  esc1.writeMicroseconds(throttle);
  esc2.writeMicroseconds(throttle);
  esc3.writeMicroseconds(throttle);

}


//Init escs
void initEscs() {
  Serial.println("Initializing motors..");
  esc1.attach(escPin1, minPulseRate, maxPulseRate);
  esc2.attach(escPin2, minPulseRate, maxPulseRate); 
  esc3.attach(escPin3, minPulseRate, maxPulseRate); 
  //Init motors with 0 value
  writeTo2Escs(1500);
}

//Start the motors
void startUpMotors() {
  Serial.println("Starting up motors..");
  delay(1000);
  writeTo2Escs(maxPulseRate);
}