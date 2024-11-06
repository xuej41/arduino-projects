#include <dht.h>

dht DHT;

const int DHT11_PIN = 7;
int ledG = 2;
int ledY = 3;
int ledR = 4;

void setup(){
  Serial.begin(9600);
  pinMode (ledG, OUTPUT);
  pinMode (ledY, OUTPUT);
  pinMode (ledR, OUTPUT);
}

void loop(){
  int chk = DHT.read11(DHT11_PIN);
  if (DHT.humidity <= 30)
  {
    digitalWrite(ledG, HIGH);
  }
  else if (DHT.humidity > 30 && DHT.humidity <= 40)
  {
    digitalWrite(ledY, HIGH);
  }
  else if (DHT.humidity > 40)
  {
    digitalWrite(ledR, HIGH);
  }
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(500);
}
