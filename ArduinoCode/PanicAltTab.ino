#include <Keyboard.h>

const int trigPin = 9;
const int echoPin = 10; //Just following the old arduino coding practice
const int THRESHOLD = 30;  

bool Trigger = false;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Keyboard.begin();
}

void loop() {
  long duration, distance;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034 / 2; // Calculate the distance in CM by using the approximate speed of sound (340ms)
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  if (distance < THRESHOLD && !Trigger) {
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_TAB);
    delay(10);
    Keyboard.releaseAll();
    
    Trigger = true;
    
    Serial.println("Sent alt tab");
  }
  else if (distance >= THRESHOLD && Trigger) {
    Trigger = false;
    Serial.println("Trigger resetted");
  }
  delay(50);
}