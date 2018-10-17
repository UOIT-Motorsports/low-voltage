#include <Wire.h> // I2C library, required for MLX90614
#include <SparkFunMLX90614.h> // SparkFunMLX90614 Arduino library


#include <I2Cdev.h>



//#include "I2Cdev.h"
//#include "MPU6050.h"
#include <SPI.h>
#include <SD.h>
#include "RTClib.h"





//DataLogger
RTC_PCF8523 rtc;
char filename[] = "LOGGER00.txt";
const int chipSelect = 10;
File logfile;
String Time;
String datastring;


//IR Sensors
IRTherm therm1;
IRTherm therm2;
IRTherm therm3;
IRTherm therm4;
IRTherm therm5;
IRTherm therm6;
IRTherm therm7;
IRTherm therm8;
IRTherm therm9;
IRTherm therm10;
IRTherm therm11;
IRTherm therm12;

//Analog Sensors

int sensorValue = 0;
int angle = 0;

int x = 0;
int button = 0;
void setup() {
   Serial.begin(2000000);
 Serial.println ("Starting...");


// IR Thermometer
   therm1.begin(0x50); // Initialize thermal IR sensor
   therm1.setUnit(TEMP_C); 
   
   therm2.begin(0x51); // Initialize thermal IR sensor
   therm2.setUnit(TEMP_C);
   
   therm3.begin(0x52); // Initialize thermal IR sensor
   therm3.setUnit(TEMP_C); 
   
   therm4.begin(0x53); // Initialize thermal IR sensor
   therm4.setUnit(TEMP_C);
   
   therm5.begin(0x54); // Initialize thermal IR sensor
   therm5.setUnit(TEMP_C); 
   
   therm6.begin(0x55); // Initialize thermal IR sensor
   therm6.setUnit(TEMP_C);

   therm7.begin(0x56); // Initialize thermal IR sensor
   therm7.setUnit(TEMP_C); 
   
   therm8.begin(0x57); // Initialize thermal IR sensor
   therm8.setUnit(TEMP_C); 
   
   therm9.begin(0x58); // Initialize thermal IR sensor
   therm9.setUnit(TEMP_C); 
   
   therm10.begin(0x59); // Initialize thermal IR sensor
   therm10.setUnit(TEMP_C); 
   
   therm11.begin(0x5A); // Initialize thermal IR sensor
   therm11.setUnit(TEMP_C);  

   therm12.begin(0x5B); // Initialize thermal IR sensor
   therm12.setUnit(TEMP_C); 

//Steering Angle
int sensorValue;

//DataLogger
Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

  // create a new file 

for (uint8_t i = 0; i < 100; i++) {
filename[6] = i/10 + '0';
filename[7] = i%10 + '0';
if (! SD.exists(filename)) {
// only open a new file if it doesn't exist
logfile = SD.open(filename, FILE_WRITE);
 logfile.println ("        Time   |   Steering Angle | Braking | Throttle | FL Disp | FR Disp | BL Disp | BR Disp | Temp 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | Accerometer | Gforce");
break; // leave the loop!
}
}
Serial.println(filename);
 pinMode(13, OUTPUT);
 pinMode(2, INPUT);
   digitalWrite(13,LOW);
Serial.println("Push Button to Start");
while (digitalRead(2) == LOW) {}
digitalWrite(13,HIGH);
}

void loop() {
 

DataLogger();
SteeringAngle();
Displacement();
TempSensors();





}

void DataLogger(){


DateTime now = rtc.now();  

 Time = ("(" +String(now.year()) + "/" + String(now.month()) + "/" + String( now.day()) + ") " +  String (now.hour())  + ":" + String(now.minute())  +":" + String (now.second()));
  
// make a string for assembling the data to log:
  datastring = (Time+ "   " + datastring);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
logfile = SD.open(filename, FILE_WRITE);


  // if the file is available, write to it:
 if (logfile) {
  
    logfile.println(datastring);
   logfile.close();
    // print to the serial port too:
     Serial.println(datastring);

 }
  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening file");
 }
datastring = String ("");
  
}


void SteeringAngle(){
   
 sensorValue = analogRead(A1);
 
int wheel = map (sensorValue,0,1023,0,345);
datastring = (datastring + String(wheel) + "  ");


int sensorValue1 = analogRead(A2);
 
int brake = map (sensorValue1,0,1023,0,345);
datastring = (datastring + String(brake) + "  ");


  
}

void Displacement(){
   
int SFL = analogRead(A3);
 
int FL = map (SFL,0,1023,200,0);
datastring = (datastring + String(FL) + "  ");

int SFR = analogRead(A4);
 
int FR = map (SFR,0,1023,200,0);
datastring = (datastring + String(FR) + "  ");

/*
int SBL = analogRead(A5);
int BL = map (SBL,0,1023,200,0);
datastring = (datastring + String(BL) + "  ");


int SBR = analogRead(A6);
 
int BR = map (SBR,0,1023,0,200);
datastring = (datastring + String(BR) + "  ");
  */
}


void TempSensors(){
 

if(therm1.read()){
  double Temp1 = therm1.object();
  datastring = (datastring + String(Temp1) + "  ");
}
if(therm2.read()){
   double Temp2 = therm2.object();
  datastring = (datastring + String(Temp2) + "  ");
}

if(therm3.read()){
  double Temp3 = therm3.object();
  datastring = (datastring + String(Temp3) + "  ");
}
if(therm4.read()){
  double Temp4 = therm4.object();
  datastring = (datastring + String(Temp4) + "  ");
}

if(therm5.read()){
  double Temp5 = therm5.object();
  datastring = (datastring + String(Temp5) + "  ");
}

if(therm6.read()){
  double Temp6 = therm6.object();
  datastring = (datastring + String(Temp6) + "  ");
}

if(therm7.read()){
  double Temp7 = therm7.object();
  datastring = (datastring + String(Temp7) + "  ");
}

if(therm8.read()){
  double Temp8 = therm8.object();
  datastring = (datastring + String(Temp8) + "  ");
}

if(therm9.read()){
  double Temp9 = therm9.object();
  datastring = (datastring + String(Temp9) + "  ");
}

if(therm10.read()){
  double Temp10 = therm10.object();
  datastring = (datastring + String(Temp10) + "  ");
}

if(therm11.read()){
  double Temp11 = therm11.object();
  datastring = (datastring + String(Temp11) + "  ");
}

if(therm12.read()){
  double Temp12 = therm12.object();
  datastring = (datastring + String(Temp12) + "  ");
}
}
