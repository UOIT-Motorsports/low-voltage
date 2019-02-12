#include <Wire.h> // I2C library, required for MLX90614
#include <SparkFunMLX90614.h> // SparkFunMLX90614 Arduino library
#include <SPI.h>
#include <SD.h>
#include "RTClib.h"
RTC_PCF8523 rtc;

    


const int chipSelect = 10;
File logfile;
IRTherm therm1;
double x;
double y;
double Temp1;
String Time;

void setup() {
  
  // put your setup code here, to run once:
 Serial.begin(57600); // Initialize Serial to log output
 


  therm1.begin(0x5B); // Initialize thermal IR sensor
  therm1.setUnit(TEMP_C);


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

  // create a new file
char filename[] = "LOGGER00.txt";
for (uint8_t i = 0; i < 100; i++) {
filename[6] = i/10 + '0';
filename[7] = i%10 + '0';
if (! SD.exists(filename)) {
// only open a new file if it doesn't exist
logfile = SD.open(filename, FILE_WRITE);
break; // leave the loop!
}
}
}

 

void loop() {
  


data();
datalogger();


}
 void data() {
  
if(therm1.read()){
  Temp1 = therm1.object();
 
}

  
Serial.print("    ");
y = map (analogRead(A1),0,1023,0,345);


Serial.print("    ");
x = map (analogRead(A2),0,1023,0,345);

 
 }

void datalogger(){


DateTime now = rtc.now();  
 Time = ("(" +String(now.year()) + "/" + String(now.month()) + "/" + String( now.day()) + ") " +  String (now.hour())  + ":" + String(now.minute())  +":" + String (now.second()));
  
// make a string for assembling the data to log:
  String dataString = ( Time + ", " + String(x) +", " + String(y) + ", " + Temp1);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.


  // if the file is available, write to it:
  if (logfile) {
    logfile.println(dataString);
    logfile.close();
    // print to the serial port too:
     Serial.println(dataString);

  }
  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }

}


