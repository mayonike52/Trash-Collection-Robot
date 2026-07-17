#include <Servo.h>
#include <stdlib.h>

char t;
const int trigPin = 6;
const int echoPin = 7;
const int servoPin = 5;
Servo myServo;

// robotic arm servos
Servo servoUpDown;
Servo servoOpenClose;
Servo servoExtend;
Servo servoLeftRight;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  myServo.attach(servoPin);
  myServo.write(90);
  
  servoUpDown.attach(3);
  servoOpenClose.attach(4);
  servoExtend.attach(5);
  servoLeftRight.attach(8);

  Serial.begin(9600);
  randomSeed(analogRead(0));
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 20000);
  if (duration == 0) return 999;
  return duration * 0.034 / 2;
}

void stopMotors() {
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
}

void moveForward() {
  digitalWrite(13, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(10, LOW);
}

void moveBackward() {
  digitalWrite(12, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(11, LOW);
}

void turnLeft() {
  digitalWrite(11, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(10, LOW);
}

void turnRight() {
  digitalWrite(13, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(10, LOW);
}

void moveServo(Servo &servo, int angle) {
  Serial.print("moving servo to: ");
  Serial.println(angle);
  servo.write(angle);
  delay(150); 
}

void moveLeftRightServo(int angle) {
  servoLeftRight.write(angle);
  delay(300); // move for a short duration
  servoLeftRight.write(90); // Stop
}

void loop() {
  if (Serial.available()) {
    t = Serial.read();
    Serial.println(t);
  }

  if (t == 'S') {
    stopMotors();
    t = '\0';
    return;
  }

  myServo.write(0);
  delay(100);
  long leftDistance = getDistance();
  
  myServo.write(90);
  delay(100);
  long centerDistance = getDistance();
  
  myServo.write(180);
  delay(100);
  long rightDistance = getDistance();
  
  myServo.write(90);

  Serial.print("Left: ");
  Serial.print(leftDistance);
  Serial.print(" cm | Center: ");
  Serial.print(centerDistance);
  Serial.print(" cm | Right: ");
  Serial.println(rightDistance);

  if (centerDistance < 25 && centerDistance != 999) {
    Serial.println("Obstacle detected. Stopping.");
    stopMotors();
    delay(300);
    moveBackward();
    delay(600);

    if (abs(leftDistance - rightDistance) < 5) {
      if (random(2) == 0) {
        Serial.println("Randomly choosing to turn left.");
        turnLeft();
      } else {
        Serial.println("Randomly choosing to turn right.");
        turnRight();
      }
    } else if (leftDistance > rightDistance) {
      Serial.println("Turning left.");
      turnLeft();
    } else {
      Serial.println("Turning right.");
      turnRight();
    }
    delay(600);
    stopMotors();
    delay(200);
    moveForward();
  } else {
    switch (t) {
      case 'F': moveForward(); break;
      case 'B': moveBackward(); break;
      case 'L': turnLeft(); break;
      case 'R': turnRight(); break;
      case 'W': digitalWrite(8, HIGH); break;
      case 'w': digitalWrite(8, LOW); break;
      case 'D': digitalWrite(9, HIGH); break;
      case 'd': digitalWrite(9, LOW); break;
      
      case 'U': moveServo(servoUpDown, 140); break;
      case 'X': moveServo(servoUpDown, 50); break;
      case 'P': moveServo(servoOpenClose, 120); break;
      case 'G': moveServo(servoOpenClose, 0); break;
      case 'E': moveServo(servoExtend, 160); break;
      case 'C': moveServo(servoExtend, 50); break;
      case 'I': moveLeftRightServo(0); break;  // Move left briefly
      case 'M': moveLeftRightServo(90); break; 
      case 'O': moveLeftRightServo(180); break; // Move right briefly
    }
    
  }
}


#include <Servo.h>
#include <stdlib.h>

char t;
const int trigPin = 6;
const int echoPin = 7;
const int servoPin = 5;
Servo myServo;

// robotic Arm Servos
Servo servoUpDown;
Servo servoOpenClose;
Servo servoExtend;
Servo servoLeftRight;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  myServo.attach(servoPin);
  myServo.write(90);
  
  servoUpDown.attach(3);
  servoOpenClose.attach(4);
  servoExtend.attach(5);
  servoLeftRight.attach(8);

  Serial.begin(9600);
  randomSeed(analogRead(0));
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 20000);
  if (duration == 0) return 999;
  return duration * 0.034 / 2;
}

void stopMotors() {
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
}

void moveForward() {
  digitalWrite(13, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(10, LOW);
}

void moveBackward() {
  digitalWrite(12, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(11, LOW);
}

void turnLeft() {
  digitalWrite(11, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(10, LOW);
}

void turnRight() {
  digitalWrite(13, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(10, LOW);
}

void moveServo(Servo &servo, int angle) {
  Serial.print("moving servo to: ");
  Serial.println(angle);
  servo.write(angle);
  delay(150); 
}

void moveLeftRightServo(int angle) {
  servoLeftRight.write(angle);
  delay(300); // move for a short duration
  servoLeftRight.write(90); // Stop
}

void loop() {
  if (Serial.available()) {
    t = Serial.read();
    Serial.println(t);
  }

  if (t == 'S') {
    stopMotors();
    t = '\0';
    return;
  }

  myServo.write(0);
  delay(100);
  long leftDistance = getDistance();
  
  myServo.write(90);
  delay(100);
  long centerDistance = getDistance();
  
  myServo.write(180);
  delay(100);
  long rightDistance = getDistance();
  
  myServo.write(90);

  Serial.print("Left: ");
  Serial.print(leftDistance);
  Serial.print(" cm | Center: ");
  Serial.print(centerDistance);
  Serial.print(" cm | Right: ");
  Serial.println(rightDistance);

  if (centerDistance < 25 && centerDistance != 999) {
    Serial.println("Obstacle detected. Stopping.");
    stopMotors();
    delay(300);
    moveBackward();
    delay(600);

    if (abs(leftDistance - rightDistance) < 5) {
      if (random(2) == 0) {
        Serial.println("Randomly choosing to turn left.");
        turnLeft();
      } else {
        Serial.println("Randomly choosing to turn right.");
        turnRight();
      }
    } else if (leftDistance > rightDistance) {
      Serial.println("Turning left.");
      turnLeft();
    } else {
      Serial.println("Turning right.");
      turnRight();
    }
    delay(600);
    stopMotors();
    delay(200);
    moveForward();
  } else {
    switch (t) {
      case 'F': moveForward(); break;
      case 'B': moveBackward(); break;
      case 'L': turnLeft(); break;
      case 'R': turnRight(); break;
      case 'W': digitalWrite(8, HIGH); break;
      case 'w': digitalWrite(8, LOW); break;
      case 'D': digitalWrite(9, HIGH); break;
      case 'd': digitalWrite(9, LOW); break;
      
      case 'U': moveServo(servoUpDown, 140); break;
      case 'X': moveServo(servoUpDown, 50); break;
      case 'P': moveServo(servoOpenClose, 120); break;
      case 'G': moveServo(servoOpenClose, 0); break;
      case 'E': moveServo(servoExtend, 160); break;
      case 'C': moveServo(servoExtend, 50); break;
      case 'I': moveLeftRightServo(0); break;  // Move left briefly
      case 'M': moveLeftRightServo(90); break; 
      case 'O': moveLeftRightServo(180); break; // Move right briefly
    }
    
  }
}


