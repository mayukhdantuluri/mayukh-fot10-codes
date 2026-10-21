/*
SMCS 2029 | Grade 10 | Foundations of Technology A
Rover Around the Table Challenge

Block X | Group 2
Group Members: Mayukh Dantuluri, Rowel Mondal, Jiya Rao

Last Edited on 2026-09-09, 18:00 UTC-4
*/

// Pin constants
const int MOTOR_POWER_A = 3;
const int MOTOR_POWER_B = 11;
const int MOTOR_DIR_A = 12;
const int MOTOR_DIR_B = 13;

void setup() {
  pinMode(MOTOR_POWER_A, OUTPUT);
  pinMode(MOTOR_POWER_B, OUTPUT);
  pinMode(MOTOR_DIR_A, OUTPUT);
  pinMode(MOTOR_DIR_B, OUTPUT);

}

// Loops to perform rover functions repeatedly 
void loop() {
 for (int i = 0; i < 4; i++) {
  // Going straight
  digitalWrite(MOTOR_POWER_A, HIGH); 
  digitalWrite(MOTOR_POWER_B, HIGH);
  digitalWrite(MOTOR_DIR_A, LOW);
  digitalWrite(MOTOR_DIR_B, HIGH);
  delay(11500);
  
  // Turning left
  digitalWrite(MOTOR_POWER_A, HIGH); 
  digitalWrite(MOTOR_POWER_B, HIGH);
  digitalWrite(MOTOR_DIR_A, LOW); // A forward
  digitalWrite(MOTOR_DIR_B, LOW); // B reverse
  delay(1400);
  }

  digitalWrite(MOTOR_POWER_A, LOW); 
  digitalWrite(MOTOR_POWER_B, LOW); 
  while (true); // stop after 4 runs
}
