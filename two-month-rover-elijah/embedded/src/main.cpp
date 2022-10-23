#include <Arduino.h>
//Mtion Sensor
#include <Arduino_LSM6DSOX.h>

//Environment Sensor
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_Sensor.h>
#include <Servo.h>
#include <Adafruit_BMP3XX.h>

#define LED_PIN 25
#define left_driver_pwn1 18
#define left_driver_pwn2 19
#define right_driver_pwn1 1
#define right_driver_pwn2 1
Servo armservo;

int servoposition = 0;



/*
|   Environment Sensor
*/
#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11
#define BMP_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)


// Timing Variables
int imu_timer = 0;
int bmp_timer = 0;


//Environment 
Adafruit_BMP3XX bmp;
//Motion


void setup() {
  // Initialize outputs
  pinMode(LED_PIN, OUTPUT);
  pinMode(left_driver_pwn1, OUTPUT);
  pinMode(left_driver_pwn2, OUTPUT);
  pinMode(right_driver_pwn1, OUTPUT);
  pinMode(right_driver_pwn2, OUTPUT);
  armservo.attach(21);
  delay(5000);

  // Turn LED on for initialization
  digitalWrite(LED_PIN, HIGH);

  // Configure serial transport
  Serial.begin(115200);
  delay(100);

  // Turn LED off after serial initialization
  digitalWrite(LED_PIN, LOW);
  Serial.begin(115200);
  
  while (!Serial);
  Serial.println("Adafruit BMP388 / BMP390 test");

  if (!bmp.begin_I2C()) {   // hardware I2C mode, can pass in address & alt Wire
  //if (! bmp.begin_SPI(BMP_CS)) {  // hardware SPI mode  
  //if (! bmp.begin_SPI(BMP_CS, BMP_SCK, BMP_MISO, BMP_MOSI)) {  // software SPI mode
    Serial.println("Could not find a valid BMP3 sensor, check wiring!");
    while (1);
  }

  // Set up oversampling and filter initialization
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);

  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in g's");
  Serial.println("X\tY\tZ");
}

void moveforward(){
  //PWN1 and not PWN2 = forward
  //PWN2 and not PWN1 = backwards
  Serial.println("MOTOR FORWARD");
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
  digitalWrite(right_driver_pwn1, LOW);
  digitalWrite(right_driver_pwn2, HIGH);
}

void armup(){
  if (servoposition == 180){
    Serial.println("MAX UP");
  }
  else {
  servoposition = servoposition + 5;
  armservo.write(servoposition);
  delay(10);
  }
}

void armdown(){
  if (servoposition == 0){
    Serial.println("MAX DOWN");
  }
  else{
  servoposition = servoposition - 5;
  armservo.write(servoposition);
  delay(10);
  }
}

void loop() {
    float x, y, z;

    float acldata = 0.0;

    int tempdata = bmp.temperature;
    long presdata = bmp.pressure / 100.0;
    int altdata = bmp.readAltitude(SEALEVELPRESSURE_HPA);

  if (IMU.accelerationAvailable() && millis() - imu_timer > 250) {
    IMU.readAcceleration(x, y, z);
    acldata = x*100;
    Serial.print("acel");
    Serial.print(acldata);
    Serial.println();
    imu_timer = millis();
  }

if (! bmp.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }

if (millis() - bmp_timer > 1000){
  Serial.print("temp");
  Serial.print(tempdata);
  Serial.println();
  Serial.print("pres");
  Serial.print(presdata);
  Serial.println();
  Serial.print("alti");
  Serial.print(altdata);
  Serial.println();

  bmp_timer = millis();
}


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
      armup();
    } else if (command == "." || command == "l"){
      armdown();
    } else if (command == "Brake"){
      brake();
    }
  }
}