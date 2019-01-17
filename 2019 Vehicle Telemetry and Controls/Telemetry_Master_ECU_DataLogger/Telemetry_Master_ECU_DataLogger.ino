#include <Wire.h> // I2C library, required for MLX90614
#include <I2Cdev.h>
#include <SPI.h>
#include <SD.h>
#include "RTClib.h"
#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>

//DataLogger
RTC_PCF8523 rtc;
char filename[] = "LOGGER00.txt";
const int chipSelect = 10;
File logfile;
String datastring;

//********************************Setup Loop*********************************//
int MessageLength;
void setup() {
  Serial.begin(9600); // For debug use
  Serial.println("CAN Read - Testing receival of CAN Bus message");  
  
  
  if(Canbus.init(CANSPEED_500))  //Initialise MCP2515 CAN controller at the specified speed
    Serial.println("CAN Init ok");
  else
    Serial.println("Can't init CAN");
    
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
 //logfile.println ("        Time   |   Steering Angle | Braking | Throttle | FL Disp | FR Disp | BL Disp | BR Disp | Temp 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | Accerometer | Gforce");
break; // leave the loop!
}
}
Serial.println(filename);
Serial.println("READY");
delay(1000);
}

//********************************Main Loop*********************************//

void loop(){
 
DataLogger();
 
recievecheck(); 
delay(500);
}

void recievecheck()
{
  tCAN message;
if (mcp2515_check_message()) 
  {
    if (mcp2515_get_message(&message)) 
  {
       datastring = ("ID: " + String (message.id,HEX)+ ", Data: " + String(message.header.length,DEC));

       
               Serial.print("ID: ");
               Serial.print(message.id,DEC);
               Serial.print(", ");
               Serial.print("Data: ");
               Serial.print(message.header.length,DEC); 
               for(int i=0;i<message.header.length;i++) 
                { 
                  datastring = (datastring + " " + String(message.data[i],HEX));
                  Serial.print(message.data[i],HEX);
                 Serial.print(" ");
                }
               Serial.println("");
             
  }}      

}


void DataLogger(){

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
