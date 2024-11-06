const int irSensorPin1 = 8;
const int irSensorPin2 = 9;

//ultrasonic sensor stuff
/*const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;
*/

//int enA = 3;
int in1 = 2;
int in2 = 4;

//int enB = 6;
int in3 = 5;
int in4 = 7;

void setup() {
  Serial.begin(9600);
  pinMode(irSensorPin1, INPUT);
  pinMode(irSensorPin2, INPUT);

//ultrsonic sensor
//  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
//  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
//  Serial.begin(9600); // Starts the serial communication

  //pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  //pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}


void loop() {
  int irSensorValue1 = digitalRead(irSensorPin1);
  int irSensorValue2 = digitalRead(irSensorPin2);
  Serial.print("IR Sensor 1 Value: ");
  Serial.println(irSensorValue1);
  Serial.print("IR Sensor 2 Value: ");
  Serial.println(irSensorValue2);
  delay(50);
/*
  digitalWrite(trigPin, LOW);
  delay(100);
  digitalWrite(trigPin, HIGH);
  delay(500);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);
*/
  //forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  //digitalWrite(enA, 255);
  //digitalWrite(enB, 255);

  if (irSensorValue1 == 1 || irSensorValue2 == 1) {
    
    //stop for 0.5 sec
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    //digitalWrite(enA, 0);
   // digitalWrite(enB, 0);
    delay(500);
    
    //backward 0.5 sec
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    //digitalWrite(enA, 100);
    //digitalWrite(enB, 100);
    delay(500);

    //stop for 0.5 sec
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    //digitalWrite(enA, 0);
    //digitalWrite(enB, 0);
    delay(500);

    //right 0.25 sec (90 degree turn)
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    //digitalWrite(enA, 100);
    //digitalWrite(enB, 100);
    delay(250);
  
    //stop for 0.5 sec
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    //digitalWrite(enA, 0);
    //digitalWrite(enB, 0);
    delay(500);
  }
}
