/*
SMCS 2029 | Grade 10 | Foundations of Technology A
Survivor Island

Block X | Group 2
Group Members: Mayukh Dantuluri, Rowel Mondal, Jiya Rao

Last Edited on 2026-10-15, 19:30 UTC-4
*/

// Arduino Motor Shield Rev3 Pins (Kept from the Roomba Challenge)
const int dirA = 12; // Motor A Direction (right)
const int pwmA = 3;  // Motor A Speed
const int dirB = 8;  // Motor B Direction (left)
const int pwmB = 7;  // Motor B Speed
// pwmB had to be moved from Pin 11 to 7 after we found the RGB preferred pins meant using 11 for blue

// Bumper Pin Constants (Kept from the Roomba Challenge)
const int BUMPER_PIN_LEFT = A4;
const int BUMPER_PIN_RIGHT = A2;

// Light Sensor Pin (Moved to A5 because A0 & A1 don't work apparently)
const int LIGHT_SENSOR_PIN = A5;

// RGB LED Pins
const int LED_R = 9;  // Red
const int LED_G = 10; // Green
const int LED_B = 11; // Blue

// Threshold values based on testing (lighter values = higher numbers)
const int WATER_THRESHOLD = 8; // Below this is water (darker), should triggers ESCAPE MANEUVER
const int SAND_THRESHOLD = 16; // Above this is sand (lighter)
// In between WATER_THRESHOLD and SAND_THRESHOLD is the grassy terrain

void setup() {
  // Initialize Motor Control Pins
  pinMode(dirA, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(dirB, OUTPUT);
  pinMode(pwmB, OUTPUT);

  // Configure RGB LED Pins
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  // Configure Bumper Switches
  pinMode(BUMPER_PIN_RIGHT, INPUT_PULLUP);
  pinMode(BUMPER_PIN_LEFT, INPUT_PULLUP);

  Serial.begin(9600);
}

void setLEDColor(int r, int g, int b) {
  analogWrite(LED_R, r);
  analogWrite(LED_G, g);
  analogWrite(LED_B, b);
}

void moveForward() {
  digitalWrite(pwmA, HIGH);
  digitalWrite(pwmB, HIGH);
  digitalWrite(dirA, HIGH);
  digitalWrite(dirB, LOW);
}

void moveBackward() {
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
  digitalWrite(pwmA, LOW);
  digitalWrite(pwmB, LOW);
}

void escapeWater() {
  stopMotors();
  setLEDColor(0, 0, 255); // Blue LED for water warning
  delay(300);

  // Back up from the water border
  moveBackward();
  delay(1200);

  // Turn around to stay on the island
  turnRight();
  delay(1800);

  stopMotors();
  delay(200);
}

void escapeObjectLeft() {
  stopMotors();
  delay(200);

  moveBackward();
  delay(1000);

  turnLeft();
  delay(1500);

  stopMotors();
  delay(200);
}

void escapeObjectRight() {
  stopMotors();
  delay(200);

  moveBackward();
  delay(1000);

  turnRight();
  delay(1500);
  
  stopMotors();
  delay(200);
}

void loop() {
  int touchStateRight = digitalRead(BUMPER_PIN_RIGHT);
  int touchStateLeft = digitalRead(BUMPER_PIN_LEFT);
  
  // Read and map light sensor values
  int rawLdr = analogRead(LIGHT_SENSOR_PIN);
  int ldrval = map(rawLdr, 0, 1023, 0, 400);

  // Debugging output
  Serial.print("Mapped LDR Value: ");
  Serial.println(ldrval);

  // Always update LED based on current terrain
  if (ldrval <= WATER_THRESHOLD) {
    setLEDColor(0, 0, 255); // Blue = water
  } else if (ldrval >= SAND_THRESHOLD) {
    setLEDColor(255, 0, 0); // Red = sand (Yellow didn't look good with the light sensor we were using)
  } else {
    setLEDColor(0, 255, 0); // Green = grass
  }
  
  // Priority 1: Water Avoidance 
  // (Water is darker, giving lower numbers -> trigger if <= WATER_THRESHOLD)
  if (ldrval <= WATER_THRESHOLD) {
    escapeWater(); 
  }
  // Priority 2: Obstacle Avoidance (Touch Bumpers)
  else if (touchStateRight == LOW) {
    escapeObjectLeft();
  } else if (touchStateLeft == LOW) {
    escapeObjectRight();
  } 
  // Priority 3: Terrain Announcement & Normal Movement
  else {
    moveForward(); 
  }

  delay(100);
}
