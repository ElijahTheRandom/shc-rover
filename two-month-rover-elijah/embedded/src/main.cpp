#include <Arduino.h>

int const LED_PIN = 25, left_driver_pwn1 = 26, left_driver_pwn2 = 27, right_driver_pwn1 = 24, right_driver_pwn2 = 25;

void setup() {
  // Initialize outputs
  pinMode(LED_PIN, OUTPUT);
  pinMode(left_driver_pwn1, OUTPUT);
  pinMode(left_driver_pwn2, OUTPUT);
  pinMode(right_driver_pwn1, OUTPUT);
  pinMode(right_driver_pwn2, OUTPUT);


  // Turn LED on for initialization
  digitalWrite(LED_PIN, HIGH);

  // Configure serial transport
  Serial.begin(115200);
  delay(100);

  // Turn LED off after serial initialization
  digitalWrite(LED_PIN, LOW);
}

void moveforward(){
  //PWN1 and not PWN2 = forward
  //PWN2 and not PWN1 = backwards
  digitalWrite(left_driver_pwn1, HIGH);
  digitalWrite(left_driver_pwn2, LOW);
  digitalWrite(right_driver_pwn1, HIGH);
  digitalWrite(right_driver_pwn2, LOW);
}

void movebackward(){
  //PWN1 and not PWN2 = forward
  //PWN2 and not PWN1 = backwards
  digitalWrite(left_driver_pwn1, LOW);
  digitalWrite(left_driver_pwn2, HIGH);
  digitalWrite(right_driver_pwn1, LOW);
  digitalWrite(right_driver_pwn2, HIGH);
}

void brake(){
  //PWN1 and not PWN2 = forward
  //PWN2 and not PWN1 = backwards
  digitalWrite(left_driver_pwn1, LOW);
  digitalWrite(left_driver_pwn2, LOW);
  digitalWrite(right_driver_pwn1, LOW);
  digitalWrite(right_driver_pwn2, LOW);
}

void moveleft(){
  //PWN1 and not PWN2 = forward
  //PWN2 and not PWN1 = backwards
  digitalWrite(left_driver_pwn1, LOW);
  digitalWrite(left_driver_pwn2, HIGH);
  digitalWrite(right_driver_pwn1, HIGH);
  digitalWrite(right_driver_pwn2, LOW);
}

void moveright(){
  //PWN1 and not PWN2 = forward
  //PWN2 and not PWN1 = backwards
  digitalWrite(left_driver_pwn1, HIGH);
  digitalWrite(left_driver_pwn2, LOW);
  digitalWrite(left_driver_pwn1, LOW);
  digitalWrite(left_driver_pwn2, HIGH);
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
    } else if (command == "ArrowUp"){
      moveforward();
    } else if (command == "ArrowLeft"){
      moveleft();
    } else if (command == "ArrowRight"){
      moveright();
    } else if (command == "ArrowDown"){
      movebackward();
    } else if (command == "Brake"){
      brake();
    }
  }
}