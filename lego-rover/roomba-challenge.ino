/*
SMCS 2029 | Grade 10 | Foundations of Technology A
Roomba Challenge

Block X | Group 2
Group Members: Mayukh Dantuluri, Rowel Mondal, Jiya Rao

Last Edited on 2026-10-05, 10:40 UTC-4
*/

// Arduino Motor Shield Rev3 Pins
const int dirA = 12; // Motor A Direction (right)
const int pwmA = 3;  // Motor A Speed
const int dirB = 8;  // Motor B Direction (left)
const int pwmB = 11; // Motor B Speed

// Bumper Pin Constants (To be updated if connected to a different digital pin)
const int BUMPER_PIN_LEFT = A4;
const int BUMPER_PIN_RIGHT = A2;

void setup() {
  // Initialize Motor Control Pins
  pinMode(dirA, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(dirB, OUTPUT);
  pinMode(pwmB, OUTPUT);

  // Configure Bumper Switch with internal pull-up resistor (Assumes switch connects pin to GND when pressed)
  pinMode(BUMPER_PIN_RIGHT, INPUT_PULLUP);
  pinMode(BUMPER_PIN_LEFT, INPUT_PULLUP);
}

void moveForward() {
  digitalWrite(pwmA, HIGH);
  digitalWrite(pwmB, HIGH);
  // Set direction forward
  digitalWrite(dirA, HIGH);
  digitalWrite(dirB, LOW);
}

void moveBackward() {
  // Set direction reverse
  digitalWrite(pwmA, HIGH);
  digitalWrite(pwmB, HIGH);
  digitalWrite(dirA, LOW);
  digitalWrite(dirB, HIGH);
}

void turnLeft() {
  digitalWrite(pwmA, LOW);
  digitalWrite(pwmB, HIGH);
  digitalWrite(dirA, LOW); 
  digitalWrite(dirB, LOW);
}

void turnRight() {
  digitalWrite(pwmA, HIGH);
  digitalWrite(pwmB, LOW);
  digitalWrite(dirB, HIGH);
  digitalWrite(dirA, HIGH);
}

void stopMotors() {
  // Engage brakes
  digitalWrite(pwmA, LOW);
  digitalWrite(pwmB, LOW);
}

void escapeObjectLeft() {
  // 1. Stop immediately upon collision
  stopMotors();
  delay(200);

  // 2. Back up for 1 second
  moveBackward();
  delay(1000);

  // 3. Turn to clear the obstacle for 1.5 seconds
  turnLeft();
  delay(1500);

  // 4. Brief pause before resuming path
  stopMotors();
  delay(200);
}

void escapeObjectRight() {
  // 1. Stop immediately upon collision
  stopMotors();
  delay(200);

  // 2. Back up for 1 second
  moveBackward();
  delay(1000);

  // 3. Turn to clear the obstacle for 1.5 seconds
  turnRight();
  delay(1500);
  
  // 4. Brief pause before resuming path
  stopMotors();
  delay(200);
}

void loop() {
  int touchStateRight = digitalRead(BUMPER_PIN_RIGHT);
  int touchStateLeft = digitalRead(BUMPER_PIN_LEFT);
  
  // Check if bumper switch is pressed (LOW when wired to ANALOG)
   if (touchStateRight == LOW) {
     escapeObjectLeft();
   } else if (touchStateLeft == LOW) {
     escapeObjectRight();
   } else {
    moveForward(); 
   }
}

/** Code Explanation:
  * The code is based on a conditional statement that runs on loop to constantly check whether or not either bumper sensor is being pressed.
  * Push on sensor makes the rover turn, and then more forward, iterating until an obstacle is avoided.
*/
