#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

void setup() {
  pinMode(A5, INPUT);
  
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  
}

void loop() {
  motor1.setSpeed(analogRead(A5) * 255/1023);
  motor2.setSpeed(analogRead(A5) * 255/1023);
  
  motor1.run(FORWARD);
  motor2.run(BACKWARD);

 
 
}
