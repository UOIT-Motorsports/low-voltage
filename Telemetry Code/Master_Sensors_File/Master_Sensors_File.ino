#include <Wire.h> // I2C library, required for MLX90614
#include <SparkFunMLX90614.h> // SparkFunMLX90614 Arduino library


#include <I2Cdev.h>



//#include "I2Cdev.h"
//#include "MPU6050.h"
#include <SPI.h>
#include <SD.h>
#include "RTClib.h"

//#include "MPU6050_6Axis_MotionApps20.h"


//MPU6050 mpu;  




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



//Accel/Gyro
/**

// MPU control/status vars
bool dmpReady = true;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}


**/

void setup() {
   Serial.begin(57600);
 Serial.println ("Starting...");
//GYRO/ACCEL
/**
 // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        
        TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize serial communication
    // (115200 chosen because it is required for Teapot Demo output, but it's
    // really up to you depending on your project)
  
    while (!Serial); // wait for Leonardo enumeration, others continue immediately

      // initialize device
    Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();

    // verify connection
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    // load and configure the DMP
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(41);
    mpu.setYGyroOffset(42);
    mpu.setZGyroOffset(96);
    
    mpu.setXAccelOffset(-3067);
    mpu.setYAccelOffset(-4550);
    mpu.setZAccelOffset(6809); 
    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }

 *//
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


}

void loop() {

//unsigned long start = millis();
// Call function
DataLogger();
SteeringAngle();
Displacement();
TempSensors();
//MPU6050();




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
   
 sensorValue = analogRead(A7);
 
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


int SBL = analogRead(A5);
int BL = map (SBL,0,1023,200,0);
datastring = (datastring + String(BL) + "  ");


int SBR = analogRead(A6);
 
int BR = map (SBR,0,1023,0,200);
datastring = (datastring + String(BR) + "  ");
  
}
/*
void MPU6050(){
// if programming failed, don't try to do anything
    if (!dmpReady) return;

    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize) {
        // other program behavior stuff here
        // .
        // .
        // .
        // if you are really paranoid you can frequently test in between other
        // stuff to see if mpuInterrupt is true, and if so, "break;" from the
        // while() loop to immediately process the MPU data
        // .
        // .
        // .
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 2048) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;



             OUTPUT_READABLE_YAWPITCHROLL
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            Serial.print("ypr\t");
            Serial.print((ypr[0] * 180/M_PI) + 60);
            Serial.print("\t");
            Serial.print(ypr[1] * 180/M_PI);
            Serial.print("\t");
            Serial.println(ypr[2] * 180/M_PI);
        


//2  : 16.384
//4  : 8.192
//8  : 4.096
//16 : 2.048

       
            // display initial world-frame acceleration, adjusted to remove gravity
            // and rotated based on known orientation from quaternion
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetAccel(&aa, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
            mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);



            datastring = (datastring + String(aaWorld.x/8192.0) + "  " + String(aaWorld.y/8192.0) + "  " + String(aaWorld.z/8192.0) + "  " );
            Serial.print(aaWorld.x/8192.0);
            Serial.print("  ");
            Serial.print(aaWorld.y/8192.0);
            Serial.print("  ");

            float Gz = (aaWorld.z/8192.0);
            Serial.print(Gz);


            datastring = (datastring + String(aaWorld.x/8192.0 * 9.81) + "  " + String(aaWorld.y/8192.0 * 9.81) + "  " + String(aaWorld.z/8192.0 * 9.81) + "  ");
           
            Serial.print("  ");
            Serial.print(aaWorld.x/8192.0 * 9.81);
            Serial.print("  ");
            Serial.print(aaWorld.y/8192.0 * 9.81);
            Serial.print("  ");
            Serial.println((aaWorld.z/8192.0) *9.81);
    
    
     
    }
}
  
*/

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
