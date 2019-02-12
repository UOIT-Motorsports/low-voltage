#include <Wire.h> // I2C library, required for MLX90614
#include <SparkFunMLX90614.h> // SparkFunMLX90614 Arduino library

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


void setup() {
  
  // put your setup code here, to run once:
 Serial.begin(2000000); // Initialize Serial to log output

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

 }

void loop() {

//unsigned long start = micros();
// Call to your function
TempSensors();
// Compute the time it took
//unsigned long end = milli();
//unsigned long delta = end - start;
//Serial.println(delta);

  

}

 void TempSensors(){

if(therm1.read()){
  double Temp1 = therm1.object();
  Serial.print(String(Temp1)+ "   ");
}

if(therm2.read()){
   double Temp2 = therm2.object();
  Serial.print(String(Temp2) + "   ");
}

if(therm3.read()){
  double Temp3 = therm3.object();
  Serial.print( String(Temp3)+ "   ");
}

if(therm4.read()){
  double Temp4 = therm4.object();
  Serial.print(String(Temp4)+ "   ");
}

if(therm5.read()){
  double Temp5 = therm5.object();
  Serial.print(String(Temp5)+ "   ");
}

if(therm6.read()){
  double Temp6 = therm6.object();
  Serial.print(String(Temp6)+ "   ");
}

if(therm7.read()){
  double Temp7 = therm7.object();
  Serial.print(String(Temp7)+ "   ");
}

if(therm8.read()){
  double Temp8 = therm8.object();
  Serial.print( String(Temp8)+ "   ");
}

if(therm9.read()){
  double Temp9 = therm9.object();
  Serial.print(String(Temp9)+ "   ");
}

if(therm10.read()){
  double Temp10 = therm10.object();
  Serial.print(String(Temp10)+ "   ");
}

if(therm11.read()){
  double Temp11 = therm11.object();
  Serial.print(String(Temp11)+ "   ");
}

if(therm12.read()){
  double Temp12 = therm12.object();
  Serial.println(String(Temp12)+ "   ");
}

}


