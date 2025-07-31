#include <Wire.h>
#include <Adafruit_VL53L0X.h>

// match pins chosen above as those are PWM enabled for variable speeds (0-255)
const int motor_left_a = 6;
const int motor_left_b = 9;
const int motor_right_a = 10;
const int motor_right_b = 11;

// ultrasonic sensor right
const int trig_right = 2;
const int echo_right = 5;
float distance_right = 0.0;

// ultrasonic sensor left
const int trig_left = 8;
const int echo_left = 3;
float distance_left = 0.0;

// ir sensors
const int left_ir = 4;
const int right_ir = 7;
float left_ir_reading;
float right_ir_reading;

// time of flight (tof) (VL53L0X) sensor
// Connect: A4 to SDA, A5 to SCL
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// store the start time to enable the initial 5 second delay
unsigned long startTime = 0;  // Variable to store the starting time
unsigned long elapsedTime = 0;

int spin = 0; // default is right







// Basic Movement Functions
void moveForwards() {
    analogWrite(motor_left_a, 255);  // Left wheel forward
    analogWrite(motor_left_b, 0);
  
    analogWrite(motor_right_a, 255); // Right wheel forward
    analogWrite(motor_right_b, 0);
}

void moveBackwards() {
    analogWrite(motor_left_a, 0);
    analogWrite(motor_left_b, 255);  // Left wheel backward
  
    analogWrite(motor_right_a, 0);
    analogWrite(motor_right_b, 255); // Right wheel backward
}

void spinLeft(int speed) {
    analogWrite(motor_left_a, 0);
    analogWrite(motor_left_b, 0);  // Left wheel moves backward
  
    analogWrite(motor_right_a, speed);
    analogWrite(motor_right_b, 0);   // Right wheel moves forward
}

void spinRight(int speed) {
    analogWrite(motor_left_a, speed);
    analogWrite(motor_left_b, 0);    // Left wheel moves forward
  
    analogWrite(motor_right_a, 0);
    analogWrite(motor_right_b, 0); // Right wheel moves backward
}


void circleSpinLeft() { // Move both wheels in the same direction
    
    analogWrite(motor_left_a, 155); // left goes slower than right
    analogWrite(motor_left_b, 0);
  
    analogWrite(motor_right_a, 255);
    analogWrite(motor_right_b, 0);
}

void stop() { // Move both wheels in the same direction
    
    analogWrite(motor_left_a, 255); // left goes slower than right
    analogWrite(motor_left_b, 255);
  
    analogWrite(motor_right_a, 255);
    analogWrite(motor_right_b, 255);
}


// Edge Detected Movements
void rightIRdetectedEdge() {
  moveBackwards();
  delay(100);
  spinLeft(255);
  delay(400); // tune turn angle to roughly 90 degrees
  moveForwards();
  delay(100);
  stop();
}

void leftIRdetectedEdge() {
  moveBackwards();
  delay(100);
  spinRight(255);
  delay(400); // tune turn angle to roughly 90 degrees
  moveForwards();
  delay(100);
  stop();
}


// Ultrasonic Update Distances
void updateUltrasonicLeft() {
  digitalWrite(trig_left, LOW);  // Clear the trig pin
  delay(2);

  digitalWrite(trig_left, HIGH);  // Send out the signal
  delay(10);
  digitalWrite(trig_left, LOW);

  distance_left = pulseIn(echo_left, HIGH) * 0.0343 / 2;  // Set the distances

  Serial.print("Distance Left Ultrasonic: ");   // Print the distance
  Serial.println(distance_left);
}
void updateUltrasonicRight() {
  digitalWrite(trig_right, LOW);  // Clear the trig pin
  delay(2);

  digitalWrite(trig_right, HIGH);  // Send out the signal
  delay(10);
  digitalWrite(trig_right, LOW);

  distance_right = pulseIn(echo_right, HIGH) * 0.0343 / 2;  // Set the distances

  Serial.print("Distance Right Ultrasonic: ");   // Print the distance
  Serial.println(distance_right);
}


// Update IR Sensor Values
void updateIRvalues() {
  left_ir_reading = digitalRead(left_ir);
  right_ir_reading = digitalRead(right_ir);

  Serial.print("Left IR Reading: ");   // Print the distance
  Serial.println(left_ir_reading);
  Serial.print("Right IR Reading: ");
  Serial.println(right_ir_reading);
}







// SETUP AND LOOP FUNCTIONS
void setup() {
    pinMode(motor_left_a, OUTPUT);
    pinMode(motor_left_b, OUTPUT);
    pinMode(motor_right_a, OUTPUT);
    pinMode(motor_right_b, OUTPUT);

    pinMode(trig_left, OUTPUT);
    pinMode(echo_left, INPUT);
    pinMode(trig_right, OUTPUT);
    pinMode(echo_right, INPUT);

    pinMode(left_ir, INPUT);
    pinMode(right_ir, INPUT);

    Serial.println("Motors, IR Sensors, and Ultrasonic Sensors are Ready");


    Serial.begin(115200);
    Wire.begin();

    // Initialize VL53L0X Sensor
    if (!lox.begin()) {
        Serial.println("Failed to initialize VL53L0X TOF Sensor!");
        while (1);
    }

    Serial.println("VL53L0X TOF Sensor is Ready");
}

void search(){
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false);
    updateUltrasonicLeft();
    updateUltrasonicRight();
    //Serial.println(measure.RangeMilliMeter);

    if (measure.RangeStatus != 4 && measure.RangeMilliMeter < 300){ //
      Serial.println(measure.RangeMilliMeter);
      stop();
      moveForwards();
      delay(30);
      return;
    }else if(distance_left<40 || spin == 0){
      spinLeft(200);
    }else if(distance_right<40 || spin == 0){
    spinRight(200);
    }
    spinRight(200);
}

void avoidLine(){
  updateIRvalues();
  if (left_ir_reading == HIGH) { // handle touching the edge
    leftIRdetectedEdge();
    spin = 1;
  }
  else if (right_ir_reading == HIGH) {
    rightIRdetectedEdge();
    spin = 0;
  }
}

void loop() {
  search();
  avoidLine();
    /*
    // update all the sensor readings and print the allocating measurements
    updateIRvalues();

    if (measure.RangeStatus != 4) { 
        Serial.print("TOF Distance: ");
        Serial.println(measure.RangeMilliMeter);
    } else {
        Serial.println("TOF is Out of range");
    }

    // measure.RangeMilliMeter, distance_left, distance_right
    // left_ir_reading, right_ir_reading
            // will be 1 (HIGH) if on the white edge (as lots of light is reflecting back)


    if (left_ir_reading == HIGH) { // handle touching the edge
      leftIRdetectedEdge();
    }
    else if (right_ir_reading == HIGH) {
      rightIRdetectedEdge();
    }
    else if (measure.RangeStatus != 4) {
      moveForwards();
      delay(30);
    }
    else if (distance_left < 50 && distance_left > 2) {
      spinLeft();
      delay(50);
      moveForwards();
      delay(20);
    }
    else if (distance_right < 50 && distance_right > 2) {
      spinRight();
      delay(50);
      moveForwards();
      delay(20);
    }
    else {
      circleSpinLeft();
      delay(50);
    }
  */
}
