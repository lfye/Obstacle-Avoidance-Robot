//Leif Ekstrom
//Robotics
//Obstacle Avoidance Robot
//Winter Tri 2019-2020
#include <Servo.h>        
#include <NewPing.h>      

// L293N or SN744410  IC
const int LeftMotorForward = 6;
const int LeftMotorBackward = 7;
const int RightMotorForward = 4;
const int RightMotorBackward = 5;

const int TRIGGER = 9;  // Arduino pin tied to trigger pin on the ultrasonic sensor.
const int ECHO = 8;  // Arduino pin tied to echo pin on the ultrasonic sensor.

Servo servo_motor;  // Servo's name

boolean goesForward = false;
int distance = 100;

//values for servo orientation
const int centerAng = 97;
const int rightAng = 0;
const int leftAng = 180;
int currentAng;
int servoIncrement = 3;

NewPing sonar(TRIGGER, ECHO, distance); //sensor function

void setup(){
  // Set L293N Control Pins as Output
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  servo_motor.attach(10);   // Attaches the servo on pin 10 to servo object.
  servo_motor.write(centerAng);   // Set at 180 degrees.
  currentAng = centerAng;
  delay(2000);              // Wait for 2s.
  distance = readPing();    // Get Ping Distance.
  delay(100);               // Wait for 100ms.
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop(){
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  if (distance <= 25){
    moveStop();
    delay(300);
    moveBackward();
    delay(250);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);
    if (distanceRight >= distanceLeft){
      turnRight();
      delay(215);
      moveStop();
    }else{
      turnLeft();
      delay(215);
      moveStop();
    }
  }else{
    moveForward();
  }
  distance = readPing();
}

//Look Right Function for Servo
int lookRight(){     
  //while the current angle of the servo is greater than that of the right angle,
  //incrementally turn right
  //this incremental turn is used so that wires are not 
  //jerked detached from ultrasonic sensor by turning too fast 
  while(currentAng > rightAng){
    currentAng -= servoIncrement;
    if(currentAng < rightAng) 
      currentAng = rightAng;
    servo_motor.write(currentAng);
    delay(15);
    }
  delay(300);
  int distance = readPing();
  delay(100);
  //incrementally return to center angle
  while(currentAng < centerAng){
    currentAng += servoIncrement;
    if(currentAng > centerAng) 
      currentAng = centerAng;
    servo_motor.write(currentAng);
    delay(15);
    }
  delay(150);
  return distance;
}

// Look Left Function for Servo Motor
int lookLeft(){
  while(currentAng < leftAng){
    currentAng += servoIncrement;
    if(currentAng > leftAng) 
      currentAng = leftAng;
    servo_motor.write(currentAng);
    delay(15);
    }
  delay(300);
  int distance = readPing();
  delay(100);
  while(currentAng > centerAng){
    currentAng -= servoIncrement;
    if(currentAng < centerAng) 
      currentAng = centerAng;
    servo_motor.write(currentAng);
    delay(15);
    }
   delay(150);
  return distance;
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) 
    cm = 250;
  return cm;
}

//Move Stop Function for Motor Driver
void moveStop(){       .
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

//Move Forward Function for Motor Driver
void moveForward(){    
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
}

//Move Backward Function for Motor Driver
void moveBackward(){   
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
}

//Turn Right Function for Motor Driver
void turnRight(){      
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
}

// Turn Left Function for Motor Driver
void turnLeft(){       
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
}
