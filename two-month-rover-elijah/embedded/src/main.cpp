#include <Arduino.h>

#define LED_PIN 25
#define left_driver_pwn1 26
#define left_driver_pwn2 27
#define right_driver_pwn1 24
#define right_driver_pwn2 25
#define servo 23

void setup() {
  // Initialize outputs
  pinMode(LED_PIN, OUTPUT);
  pinMode(left_driver_pwn1, OUTPUT);
  pinMode(left_driver_pwn2, OUTPUT);
  pinMode(right_driver_pwn1, OUTPUT);
  pinMode(right_driver_pwn2, OUTPUT);
  pinMode(servo, OUTPUT);


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

void armup(){
  //arm moves up
}

void armdown(){
  //arm moves down
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
    } else if (command == "ArrowUp" || command == "w"){
      moveforward();
    } else if (command == "ArrowLeft" || command == "a"){
      moveleft();
    } else if (command == "ArrowRight" || command == "d"){
      moveright();
    } else if (command == "ArrowDown" || command == "s"){
      movebackward();
    } else if (command == "," || command == "o"){
      armraise()
    } else if (command == "." || command == "l"){
      armlower()
    } else if (command == "Brake"){
      brake();
    }
  }
}