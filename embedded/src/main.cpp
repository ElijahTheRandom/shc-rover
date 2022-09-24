#include <Arduino.h>

#define LED_PIN 25

void setup() {
  // Initialize LED_PIN as an output
  pinMode(LED_PIN, OUTPUT);
  // Turn LED on for initialization
  digitalWrite(LED_PIN, HIGH);

  // Configure serial transport
  Serial.begin(115200);
  delay(2000);

  // Turn LED off after serial initialization
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.write(Serial.read());
}