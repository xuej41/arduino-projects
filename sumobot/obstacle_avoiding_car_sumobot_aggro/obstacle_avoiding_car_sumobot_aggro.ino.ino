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
 // delay(5000);
}


void loop() {
//ir sensor
  irSensorValue = digitalRead(irSensorPin);
  Serial.print("IR Sensor Value: ");
  Serial.println(irSensorValue);
  delay(20);
//ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delay(20);
  digitalWrite(trigPin, HIGH);
  delay(20);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);

  if (irSensorValue == 1) {
    //backward 0.5 sec
    digitalWrite(in1, 0);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, 0);
    digitalWrite(in4, HIGH);
    delay(600);
    //right 0.4 sec (160 degree turn)
    digitalWrite(in1, HIGH);
    digitalWrite(in2, 0);
    digitalWrite(in3, 0);
    digitalWrite(in4, HIGH);
    delay(700);
  }
  else if (distance <= 20) {
    //right 0.25 sec (90 degree turn)
    digitalWrite(in1, 0);
    digitalWrite(in2, 1);
    digitalWrite(in3, 0);
    digitalWrite(in4, 1);
    delay(500);
  }
  else {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, 0);
    digitalWrite(in3, 0);
    digitalWrite(in4, HIGH);
    delay(250);
  }
  //void forward(int speed) {
      //forward
  
}
