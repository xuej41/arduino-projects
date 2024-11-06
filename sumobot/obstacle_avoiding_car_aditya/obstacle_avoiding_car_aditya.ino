
// Represents the motor
class Motor {
  private:
  // Port for power
  int powerPort;
  // Port for forward
  int forwardPort;
  // Port for backward
  int reversePort;
  public:
  // Take in power port, forward port, reverse port
  Motor(int powerPort, int forwardPort, int reversePort) {
    // set the fields
    this->powerPort = powerPort;
    this->forwardPort = forwardPort;
    this->reversePort = reversePort;
  }

  void init() {
    // attach ports from hardware to software
    pinMode(powerPort, OUTPUT);
    pinMode(forwardPort, OUTPUT);
    pinMode(reversePort, OUTPUT);
  }

  // Stop spinning
  void stop() {
    // Write the ports
    // Power will be 0
    digitalWrite(powerPort, 0);
    // Forward will be low
    digitalWrite(forwardPort, LOW);
    // Reverse will be low
    digitalWrite(reversePort, LOW);
  }

  // Set power to the motor and set direction
  // Power will be an int from 0 to 100
  // Forward is boolean so either true or false
  void setPower(int power, bool forward = true) {
      // Set the power
      digitalWrite(powerPort, power);
      // if the direction is forward
      if (forward) {
        // Set forward to high
        digitalWrite(forwardPort, HIGH);
        // Set reverse to low
        digitalWrite(reversePort, LOW);
      } else {
        // Set forward to low
        digitalWrite(forwardPort, LOW);
        // Set reverse to high
        digitalWrite(reversePort, HIGH);
      }
  }
};

const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;

// Power port for left motor is 3
// Forward port for left motor is 2
// Reverse port for left motor is 4
Motor left(3, 2, 4);
// Power port for left motor is 6
// Forward port for left motor is 5
// Reverse port for left motor is 7
Motor right(6, 5, 7);

int led = 13;

void setup() {
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication

  left.init();
  right.init();
  
  pinMode(led, OUTPUT);
}


void loop() {
  
  digitalWrite(trigPin, LOW);
  delay(100);
  digitalWrite(trigPin, HIGH);
  delay(500);
  digitalWrite(trigPin, LOW);
  //duration = pulseIn(echoPin, HIGH);
  //distance= duration*0.034/2;
  distance = 26;
  Serial.print("Distance: ");
  Serial.println(distance);

  //forward
  left.setPower(100, true);
  right.setPower(100, true);

  if (distance <= 25) {
    
    //stop for 0.5 sec
    left.stop();
    right.stop();
    delay(500);
    
    //flash led 3 times
    for (int i = 0; i < 3; i++) {
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      delay(100);
    }
    //backward 0.5 sec
    left.setPower(100, false);
    right.setPower(100, false);
    delay(500);

    //stop for 0.5 sec
    left.stop();
    right.stop();
    delay(500);

    //right 0.25 sec (90 degree turn)
    left.setPower(100, true);
    right.setPower(100, false);
    delay(250);
  
    //stop for 0.5 sec
    left.stop();
    right.stop();
    delay(500);
  }
}
