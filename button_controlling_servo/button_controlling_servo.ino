#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int angle = 90;    // initial angle  for servo
int angleAmount = 1;

void setup() {
  Serial.begin(9600);          //  setup serial
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(2,INPUT_PULLUP);
   Serial.println("Robojax Servo Button ");
}

void loop() {
  while(digitalRead(2) == LOW){
  angle += angleAmount;

    // reverse the direction of the moving at the ends of the angle:
    if (angle <= 0 || angle >= 180) {
      angleAmount = -angleAmount;
    }
    myservo.write(angle); // move the servo to desired angle  
    delay(15); // waits for the servo to get there
  }// while
}
