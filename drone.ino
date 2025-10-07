//importing librarys
#include <Wire.h>
#include <ESP32Servo.h>
#include "SparkFun_BNO08x_Arduino_Library.h"
BNO08x myIMU;

unsigned long startTime;


float previousMillis = 0;

float speed = 1050;

float roll = 0;
float pitch = 0;
float yaw = 0;

float y_fin_angle = 0;
float y_integral = 0.0;
float y_previousError = 0.0;

float x_fin_angle = 0;
float x_integral = 0.0;
float x_previousError = 0.0;
    
float kp = 0.0;
float ki = 0.0;
float kd = 0.0 ;


float dt = 0.001;



// motor objects
Servo right;
Servo left;
Servo rightb;
Servo leftb;

//seting pins
const int pinright = 5;
const int pinleft = 2;
const int pinrightb = 13;
const int pinleftb = 14;

#define BNO08X_INT  -1
#define BNO08X_RST  -1


//functions for useing brusless motors
void right_speed(int us) {
  right.writeMicroseconds(us);
}

void left_speed(int us) {
  left.writeMicroseconds(us);
}

void rightb_speed(int us) {
  rightb.writeMicroseconds(us);
}

void leftb_speed(int us) {
  leftb.writeMicroseconds(us);
}






//seting bno08x adress

#define BNO08X_ADDR 0x4B

void setup() {
  Serial.print("start");
  delay(10000);
  //starting serial monitor
  Serial.begin(115200);
  
  while(!Serial) delay(10);
  
  Serial.println();
  Serial.println("BNO08x Read Example");

  //seting ı2c pins
  Wire.begin(21 , 22);

  //founing bno08x  
  if (myIMU.begin(BNO08X_ADDR, Wire, BNO08X_INT, BNO08X_RST) == false) {
    Serial.println("BNO08x not detected at default I2C address. Check your jumpers and the hookup guide. Freezing...");
    while (1)
      ;
  }
  Serial.println("BNO08x found!");

  

  setReports();

  Serial.println("Reading events");





  //seting pwn
  right.setPeriodHertz(50);
  right.attach(pinright, 1000, 2000);
  left.setPeriodHertz(50);
  left.attach(pinleft, 1000, 2000);
  rightb.setPeriodHertz(50);
  rightb.attach(pinrightb, 1000, 2000);
  leftb.setPeriodHertz(50);
  leftb.attach(pinleftb, 1000, 2000);

  //calibrateing esc
  right_speed(1000);
  left_speed(1000);
  rightb_speed(1000);
  leftb_speed(1000);

  delay(2000);
  
  startTime = millis();
}

//function for getting datas
void setReports(void) {
  Serial.println("Setting desired reports");
  if (myIMU.enableRotationVector() == true) {
    Serial.println(F("Rotation vector enabled"));
    Serial.println(F("Output in form roll, pitch, yaw"));
  } else {
    Serial.println("Could not enable rotation vector");
  }1400;

float roll = 0;
}

void loop() {


//test mode

   /* 
  if (millis() - startTime > 10000) {
    Serial.println("finished");
    while (true) {
      // dur, hiçbir şey yapma
    }}
    */



  float currentMillis = millis();
  dt = (currentMillis - previousMillis); // saniye cinsinden
  previousMillis = currentMillis;
  dt = dt * 0.001;

 

  
  if (myIMU.wasReset()) {
    Serial.print("sensor was reset ");
    setReports();
  }

  //resding sensor
  if (myIMU.getSensorEvent() == true) {

    
    if (myIMU.getSensorEventID() == SENSOR_REPORTID_ROTATION_VECTOR) {

    roll = (myIMU.getRoll()) * 180.0 / PI; // Convert roll to degrees
    pitch = (myIMU.getPitch()) * 180.0 / PI; // Convert pitch to degrees
    yaw = (myIMU.getYaw()) * 180.0 / PI; // Convert yaw / heading to degrees

    //Serial.print(roll, 1);
    //Serial.print(F(","));
    //Serial.print(pitch, 1);
    //Serial.print(F(","));
    //Serial.print(yaw, 1);

    //Serial.println();

    
    }
  }



  





  float x_error = x_fin_angle - roll;
  x_integral += x_error * dt;
  float x_derivative = (x_error - x_previousError) / dt;
  float x_output = kp * x_error + ki * x_integral + kd * x_derivative;
  x_previousError = x_error;
    
    
    
    
    
    
    
    
    
  float y_error = y_fin_angle - pitch;
  y_integral += y_error * dt;
  float y_derivative = (y_error - y_previousError) / dt;
  float y_output = kp * y_error + ki * y_integral + kd * y_derivative;
  y_previousError = y_error;
  

  right_speed((int)(speed + (+ x_output + y_output)/2));
  left_speed((int)(speed + (- x_output + y_output)/2));
  rightb_speed((int)(speed + (+ x_output - y_output)/2));
  leftb_speed((int)(speed + (- x_output - y_output)/2));





  //Serial.print((int)(speed + (+ x_output + y_output)/2));
  //Serial.println((int)(speed + (- x_output + y_output)/2));//
  //Serial.print((int)(speed + (+ x_output - y_output)/2));
  //Serial.println((int)(speed + (- x_output - y_output)/2));//

  //Serial.println(dt , 3);
  //Serial.println();
  
  
}
