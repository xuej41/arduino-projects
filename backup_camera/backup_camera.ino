const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;
int ledG = 2;
int ledY = 3;
int ledR = 4;
int buzzer = 5;


void setup() {

pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
pinMode(ledG, OUTPUT);
pinMode(ledY, OUTPUT);
pinMode(ledR, OUTPUT);
pinMode (buzzer, OUTPUT);
}


void loop() {
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
Serial.print("Distance: ");
Serial.println(distance);

if (distance <= 5)
  {
  digitalWrite(ledR, HIGH);   // turn the LED on (HIGH is the voltage level)
  tone(buzzer, 1000);
  delay(50);                       // wait for a second
  digitalWrite(ledR, LOW);    // turn the LED off by making the voltage LOW
  noTone(buzzer);
  delay(50);
  }
else if (distance <= 12)
{
    digitalWrite(ledY, HIGH);   // turn the LED on (HIGH is the voltage level)
    tone(buzzer, 1000);
    delay(100);                       // wait for a second
    digitalWrite(ledY, LOW);    // turn the LED off by making the voltage LOW
    noTone(buzzer);
    delay(100);
}
else if (distance <= 25)
{
    digitalWrite(ledG, HIGH);   // turn the LED on (HIGH is the voltage level)
    tone(buzzer, 1000);
    delay(250);                       // wait for a second
    digitalWrite(ledG, LOW);    // turn the LED off by making the voltage LOW
    noTone(buzzer);
    delay(250);
}
}
