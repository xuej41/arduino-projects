//ir sensor
const int irSensorPin = 8;
//ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;
//motor
int in1 = 2;
int in2 = 3;
int in3 = 4;
int in4 = 5;
int irSensorValue = digitalRead(irSensorPin);

void setup() {
  Serial.begin(9600);
//ir sensor
  pinMode(irSensorPin, INPUT);
//ultrsonic sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
//motor
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  delay(5000);
}


void loop() {
//ir sensor
  irSensorValue = digitalRead(irSensorPin);
  Serial.print("IR Sensor Value: ");
  Serial.println(irSensorValue);
  delay(5);
//ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delay(5);
  digitalWrite(trigPin, HIGH);
  delay(5);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);

  if (irSensorValue == 1) {
    //backward 0.5 sec
    analogWrite(in1, 0);
    analogWrite(in2, 150);
    analogWrite(in3, 0);
    analogWrite(in4, 150);
    delay(750);
    //right 0.4 sec (160 degree turn)
    analogWrite(in1, 150);
    analogWrite(in2, 0);
    analogWrite(in3, 0);
    analogWrite(in4, 150);
    delay(800);
  }
  else if (distance <= 10) {
    //right 0.25 sec (90 degree turn)
    analogWrite(in1, 0);
    analogWrite(in2, 0);
    analogWrite(in3, 150);
    analogWrite(in4, 0);
    delay(250);
  }
  else {
    analogWrite(in1, 130);
    analogWrite(in2, 0);
    analogWrite(in3, 130);
    analogWrite(in4, 0);
    delay(250);
  }
  //void forward(int speed) {
      //forward
  
}
