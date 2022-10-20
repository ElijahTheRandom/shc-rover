/*______________________________________________________________________________________________
 *                                                                                              |
 *                                                                                              |
 *                                   Important Shit Here                                        |
 *                                                                                              |
 *                                                                                              |
 *                                                                                              |
 *                                    10.4.150.9:9090                                           |
 *                                                                                              |
 *                                                                                              |
 *                                                                                              |
 *______________________________________________________________________________________________|
 */





#include <Arduino.h>
//Mtion Sensor
#include <Adafruit_ISM330DHCX.h>

//Environment Sensor
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"
#include <SPI.h>
#include <Servo.h>



//Demo
#define LED_PIN 25
#define left_driver_pwn1 26
#define left_driver_pwn2 27
#define right_driver_pwn1 24
#define right_driver_pwn2 25
Servo armservo;

int servoposition = 0;


/*
|   Motion Sensor
*/
// For SPI mode, we need a CS pin
#define LSM_CS 10
// For software-SPI mode we need SCK/MOSI/MISO pins
#define LSM_SCK 13
#define LSM_MISO 12
#define LSM_MOSI 11







/*
|   Environment Sensor
*/
#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11
#define BMP_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)






//Environment 
Adafruit_BMP3XX bmp;
//Motion
Adafruit_ISM330DHCX ism330dhcx;

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

pinMode(LED_PIN, OUTPUT);
  pinMode(left_driver_pwn1, OUTPUT);
  pinMode(left_driver_pwn2, OUTPUT);
  pinMode(right_driver_pwn1, OUTPUT);
  pinMode(right_driver_pwn2, OUTPUT);
  armservo.attach(21);


/*
|   Environment Sensor                                                                              **********************
*/


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

/*
|   Motion Sensor                                                                                   ******************************
*/

  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit ISM330DHCX test!");

  if (!ism330dhcx.begin_I2C()) {
    // if (!ism330dhcx.begin_SPI(LSM_CS)) {
    // if (!ism330dhcx.begin_SPI(LSM_CS, LSM_SCK, LSM_MISO, LSM_MOSI)) {
    Serial.println("Failed to find ISM330DHCX chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("ISM330DHCX Found!");

  // ism330dhcx.setAccelRange(LSM6DS_ACCEL_RANGE_2_G);
  Serial.print("Accelerometer range set to: ");
  switch (ism330dhcx.getAccelRange()) {
  case LSM6DS_ACCEL_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case LSM6DS_ACCEL_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case LSM6DS_ACCEL_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case LSM6DS_ACCEL_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }

  // ism330dhcx.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS);
  Serial.print("Gyro range set to: ");
  switch (ism330dhcx.getGyroRange()) {
  case LSM6DS_GYRO_RANGE_125_DPS:
    Serial.println("125 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_250_DPS:
    Serial.println("250 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_500_DPS:
    Serial.println("500 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_1000_DPS:
    Serial.println("1000 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_2000_DPS:
    Serial.println("2000 degrees/s");
    break;
  case ISM330DHCX_GYRO_RANGE_4000_DPS:
    Serial.println("4000 degrees/s");
    break;
  }

  // ism330dhcx.setAccelDataRate(LSM6DS_RATE_12_5_HZ);
  Serial.print("Accelerometer data rate set to: ");
  switch (ism330dhcx.getAccelDataRate()) {
  case LSM6DS_RATE_SHUTDOWN:
    Serial.println("0 Hz");
    break;
  case LSM6DS_RATE_12_5_HZ:
    Serial.println("12.5 Hz");
    break;
  case LSM6DS_RATE_26_HZ:
    Serial.println("26 Hz");
    break;
  case LSM6DS_RATE_52_HZ:
    Serial.println("52 Hz");
    break;
  case LSM6DS_RATE_104_HZ:
    Serial.println("104 Hz");
    break;
  case LSM6DS_RATE_208_HZ:
    Serial.println("208 Hz");
    break;
  case LSM6DS_RATE_416_HZ:
    Serial.println("416 Hz");
    break;
  case LSM6DS_RATE_833_HZ:
    Serial.println("833 Hz");
    break;
  case LSM6DS_RATE_1_66K_HZ:
    Serial.println("1.66 KHz");
    break;
  case LSM6DS_RATE_3_33K_HZ:
    Serial.println("3.33 KHz");
    break;
  case LSM6DS_RATE_6_66K_HZ:
    Serial.println("6.66 KHz");
    break;
  }

  // ism330dhcx.setGyroDataRate(LSM6DS_RATE_12_5_HZ);
  Serial.print("Gyro data rate set to: ");
  switch (ism330dhcx.getGyroDataRate()) {
  case LSM6DS_RATE_SHUTDOWN:
    Serial.println("0 Hz");
    break;
  case LSM6DS_RATE_12_5_HZ:
    Serial.println("12.5 Hz");
    break;
  case LSM6DS_RATE_26_HZ:
    Serial.println("26 Hz");
    break;
  case LSM6DS_RATE_52_HZ:
    Serial.println("52 Hz");
    break;
  case LSM6DS_RATE_104_HZ:
    Serial.println("104 Hz");
    break;
  case LSM6DS_RATE_208_HZ:
    Serial.println("208 Hz");
    break;
  case LSM6DS_RATE_416_HZ:
    Serial.println("416 Hz");
    break;
  case LSM6DS_RATE_833_HZ:
    Serial.println("833 Hz");
    break;
  case LSM6DS_RATE_1_66K_HZ:
    Serial.println("1.66 KHz");
    break;
  case LSM6DS_RATE_3_33K_HZ:
    Serial.println("3.33 KHz");
    break;
  case LSM6DS_RATE_6_66K_HZ:
    Serial.println("6.66 KHz");
    break;
  }

  ism330dhcx.configInt1(false, false, true); // accelerometer DRDY on INT1
  ism330dhcx.configInt2(false, true, false); // gyro DRDY on INT2














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
  servoposition++;
  armservo.write(servoposition);
}

void armdown(){
  servoposition--;
  armservo.write(servoposition);
}









void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
  


    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temp;
    ism330dhcx.getEvent(&accel, &gyro, &temp);

    int acldata = accel.acceleration.x;
    int tempdata = bmp.temperature;
    long presdata = bmp.pressure / 100.0;
    int altdata = bmp.readAltitude(SEALEVELPRESSURE_HPA);
    String Acel = "acel"+ acldata;
    String Temp = "temp"+ tempdata;
    String Pres = "pres"+ presdata;
    String Alti = "alti"+ altdata;



    //Serial.print(accel.acceleration.x);
    //Serial.print(accel.acceleration.y);
    Serial.print(Acel);
    Serial.print("\n");

    Serial.print(Temp);
    Serial.print("\n");
    Serial.print(Pres);
    Serial.print("\n");
    Serial.print(Alti);
    Serial.print("\n");


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

