#include <PRIZM.h>
PRIZM prizmObj;

#define STANDARD_DELAY 500
#define DOUBLE_DELAY STANDARD_DELAY*2

void blinkLight(PRIZM prizm, char color, int del);
void morse_s(PRIZM prizm, char color);
void morse_o(PRIZM prizm, char color);
void while_sos(PRIZM prizm, char color);
void for_sos(PRIZM prizm, char color);

void moveServo(PRIZM prizm, int servoNum, int deg, int del);
void servoUp(PRIZM prizm, int servoNum);
void servoDown(PRIZM prizm, int servoNum);
void armWave(PRIZM prizm, int servoNum);

void moveMotors(PRIZM prizm, int speed1, int speed2, int del);
void driveForward(PRIZM prizm, int driveSpeed, int driveTime);
void driveBackward(PRIZM prizm, int driveSpeed, int driveTime);
void driveRight(PRIZM prizm, int driveSpeed, int driveTime);
void driveLeft(PRIZM prizm, int driveSpeed, int driveTime);
void leaveHighway(PRIZM prizm, int driveSpeed);

void setup() {
  prizmObj.PrizmBegin();
  Serial.begin(9600);

  // Set all servos to max speed and positions to 90 degrees
  prizmObj.setServoSpeeds(100, 100, 100, 100, 100, 100);
  prizmObj.setServoPositions(90, 90, 90, 90, 90, 9);

  // Flip motor 2 so driving works properly
  prizmObj.setMotorInvert(1, 1);
}

void loop() {
  // put your main code here, to run repeatedly:

  /*
  // This code is the loop() sos code
  morse_s(prizmObj, 'r');
  morse_s(prizmObj, 'r');
  morse_s(prizmObj, 'r');

  morse_o(prizmObj, 'r');
  morse_o(prizmObj, 'r');
  morse_o(prizmObj, 'r');

  morse_s(prizmObj, 'r');
  morse_s(prizmObj, 'r');
  morse_s(prizmObj, 'r');

  delay(2000);
  */

  // This function does the above code, but in a different function
  // while_sos(prizmObj, 'r');

  // This function uses a for loop to do the morse code
  //for_sos(prizmObj, 'g');

  // Wave the servo up and down
  //armWave(prizmObj, 1);

  // Drive off the highway
  leaveHighway(prizmObj, 100);

}

void blinkLight(PRIZM prizm, char color, int del) {
  switch(color) {
      case('r'):
        prizm.setRedLED(HIGH);
        delay(del);
        prizm.setRedLED(LOW);
        delay(del);
      break;
      case('g'):
        prizm.setGreenLED(HIGH);
        delay(del);
        prizm.setGreenLED(LOW);
        delay(del);
      break;
      default:
        Serial.println("Incorrect parameters passed to blinkLight()");
      return;
    }
}

void morse_s(PRIZM prizm, char color) {
  blinkLight(prizm, color, STANDARD_DELAY);  
}

void morse_o(PRIZM prizm, char color) {
  blinkLight(prizm, color, DOUBLE_DELAY + STANDARD_DELAY);  
}

void while_sos(PRIZM prizm, char color) {
  while(true) { // Infinite loop
      morse_s(prizm, color);
      morse_s(prizm, color);
      morse_s(prizm, color);

      morse_o(prizm, color);
      morse_o(prizm, color);
      morse_o(prizm, color);

      morse_s(prizm, color);
      morse_s(prizm, color);
      morse_s(prizm, color);

      delay(2000);
    }  
}

void for_sos(PRIZM prizm, char color) {
  for(int i = 0; i < 3; i++) {
    morse_s(prizm, color);
  }
  
  for(int i = 0; i < 3; i++) {
    morse_o(prizm, color);
  }
  
  for(int i = 0; i < 3; i++) {
    morse_s(prizm, color);
  }  

  delay(2000);
  
}

void moveServo(PRIZM prizm, int servoNum, int deg, int del) {
  prizm.setServoPosition(servoNum, deg);
  delay(del);
}

void servoUp(PRIZM prizm, int servoNum) {
  moveServo(prizm, servoNum, 180, DOUBLE_DELAY);
}

void servoDown(PRIZM prizm, int servoNum) {
  moveServo(prizm, servoNum, 0, DOUBLE_DELAY);
}

void armWave(PRIZM prizm, int servoNum) {
  servoUp(prizm, servoNum);
  servoDown(prizm, servoNum);  
}

void moveMotors(PRIZM prizm, int speed1, int speed2, int del) {
  prizm.setMotorSpeeds(speed1, speed2);
  delay(del);  
}

void driveForward(PRIZM prizm, int driveSpeed, int driveTime) {
  moveMotors(prizm, driveSpeed, driveSpeed, driveTime);  
}

void driveBackward(PRIZM prizm, int driveSpeed, int driveTime) {
  moveMotors(prizm, -driveSpeed, -driveSpeed, driveTime);  
}

void driveRight(PRIZM prizm, int driveSpeed, int driveTime) {
  moveMotors(prizm, driveSpeed, -driveSpeed, driveTime);  
}

void driveLeft(PRIZM prizm, int driveSpeed, int driveTime) {
  moveMotors(prizm, -driveSpeed, driveSpeed, driveTime);  
}

void leaveHighway(PRIZM prizm, int driveSpeed) {
  driveForward(prizm, driveSpeed, DOUBLE_DELAY * 3);
  moveMotors(prizm, driveSpeed, -driveSpeed / 4, STANDARD_DELAY);
  
  driveForward(prizm, driveSpeed, DOUBLE_DELAY);
  moveMotors(prizm, -driveSpeed / 4, driveSpeed, STANDARD_DELAY);

  // Break for 1 second
  moveMotors(prizm, 125, 125, DOUBLE_DELAY);
  
  prizm.PrizmEnd();
}
