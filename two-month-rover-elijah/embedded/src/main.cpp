#include <Arduino.h>

#define LED_PIN 25

void setup() {
  // Initialize LED_PIN as an output
  pinMode(LED_PIN, OUTPUT);
  // Turn LED on for initialization
  digitalWrite(LED_PIN, HIGH);

  // Configure serial transport
  Serial.begin(115200);
  delay(100);

  // Turn LED off after serial initialization
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "led_on") {
      digitalWrite(LED_PIN, HIGH);
    } else if (command == "led_off") {
      digitalWrite(LED_PIN, LOW);
    } else if (command == "ping") {
      Serial.println("pong");
    } else if (command == "time") {
      Serial.println(millis());
    } else if (command == "forward"){
      Serial.println("motors forward");
    } else if (command == "left"){
      Serial.println("left motor back, right motor forward");
    } else if (command == "right"){
      Serial.println("left motor forward, right motor back");
    } else if (command == "backward"){
      Serial.println("motors backward");
    }
  }
}