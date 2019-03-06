/****************************************************************************
CAN Read Demo for the SparkFun CAN Bus Shield. 

Written by Stephen McCoy. 
Original tutorial available here: http://www.instructables.com/id/CAN-Bus-Sniffing-and-Broadcasting-with-Arduino
Used with permission 2016. License CC By SA. 

Distributed as-is; no warranty is given.
*************************************************************************/
#include <Serial_CAN_Module.h>
#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>

//********************************Setup Loop*********************************//
int MessageLength;
void setup() {
  Serial.begin(9600); // For debug use
  Serial.println("CAN Read - Testing receival of CAN Bus message");  
  
  
  if(Canbus.init(CANSPEED_500))  //Initialise MCP2515 CAN controller at the specified speed
    Serial.println("CAN Init ok");
  else
    Serial.println("Can't init CAN");
    
  
}

//********************************Main Loop*********************************//

void loop(){
 
//VoltageRequest();
//InternalTemps();
//ExternalTemps();

recieve (); 


}


void recieve(){


  tCAN message;
if (mcp2515_check_message()) 
  {
    if (mcp2515_get_message(&message)) 
  {
        if(message.id == 0x55){  //uncomment when you want to filter            
               Serial.print("ID: ");
               Serial.print(message.id,HEX);
               Serial.print(", ");
               Serial.print("Data: ");

//External temps 
            if(message.data[1] == 0x1B){
                
           uint16_t value = (((message.data[2])*256)+(message.data[3]));
           float intemp = value/10.00;
           Serial.print(intemp);
           Serial.print(", ");


            uint16_t value2 = (((message.data[4])*256)+(message.data[5]));
           float extemp = value2/10.00;
           Serial.print(extemp);
             }
//Min Cell Voltage
if(message.data[1] == 0x17){
                
           uint16_t value = (((message.data[3])*256)+(message.data[2]));
           float minvolt = value/1000.00;
           Serial.print(minvolt);
           Serial.print(", ");
}
//Max Cell Voltage 
if(message.data[1] == 0x16){
                
           uint16_t value = (((message.data[3])*256)+(message.data[2]));
           float maxvolt = value/1000.00;
           Serial.print(maxvolt);
           Serial.print(", ");
    } 
if(message.data[1] == 0x14){
                
           uint16_t value = ((((message.data[5]*256)+ message.data[4])*256 +(message.data[3]))*256 + message.data[2]);
           float totalvolt = value/2000.00;
           Serial.print(totalvolt);
           Serial.print(", ");
    }    
   Serial.println(" ");                   
  } 

//__________________________________________________________________________________________________________________________________________________________________________________________________________________

//__________________________________________________________________________________________________________________________________________________________________________________________________________________

if(message.id == 0x56){  //uncomment when you want to filter            
               Serial.print("ID: ");
               Serial.print(message.id,HEX);
               Serial.print(", ");
               Serial.print("Data: ");

//External temps 
            if(message.data[1] == 0x1B){
                
           uint16_t value = (((message.data[2])*256)+(message.data[3]));
           float intemp = value/10.00;
           Serial.print(intemp);
           Serial.print(", ");


            uint16_t value2 = (((message.data[4])*256)+(message.data[5]));
           float extemp = value2/10.00;
           Serial.print(extemp);
             }
//Min Cell Voltage
if(message.data[1] == 0x17){
                
           uint16_t value = (((message.data[3])*256)+(message.data[2]));
           float minvolt = value/1000.00;
           Serial.print(minvolt);
           Serial.print(", ");
}
//Max Cell Voltage 
if(message.data[1] == 0x16){
                
           uint16_t value = (((message.data[3])*256)+(message.data[2]));
           float maxvolt = value/1000.00;
           Serial.print(maxvolt);
           Serial.print(", ");
    } 
if(message.data[1] == 0x14){
                
           uint16_t value = ((((message.data[5]*256)+ message.data[4])*256 +(message.data[3]))*256 + message.data[2]);
           float totalvolt = value/2000.00;
           Serial.print(totalvolt);
           Serial.print(", ");
    }    
   Serial.println(" ");                   
  } 

//__________________________________________________________________________________________________________________________________________________________________________________________________________________

//__________________________________________________________________________________________________________________________________________________________________________________________________________________

if(message.id == 0x57){  //uncomment when you want to filter            
               Serial.print("ID: ");
               Serial.print(message.id,HEX);
               Serial.print(", ");
               Serial.print("Data: ");

//External temps 
            if(message.data[1] == 0x1B){
                
           uint16_t value = (((message.data[2])*256)+(message.data[3]));
           float intemp = value/10.00;
           Serial.print(intemp);
           Serial.print(", ");


            uint16_t value2 = (((message.data[4])*256)+(message.data[5]));
           float extemp = value2/10.00;
           Serial.print(extemp);
             }
//Min Cell Voltage
if(message.data[1] == 0x17){
                
           uint16_t value = (((message.data[3])*256)+(message.data[2]));
           float minvolt = value/1000.00;
           Serial.print(minvolt);
           Serial.print(", ");
}
//Max Cell Voltage 
if(message.data[1] == 0x16){
                
           uint16_t value = (((message.data[3])*256)+(message.data[2]));
           float maxvolt = value/1000.00;
           Serial.print(maxvolt);
           Serial.print(", ");
    } 
if(message.data[1] == 0x14){
                
           uint16_t value = ((((message.data[5]*256)+ message.data[4])*256 +(message.data[3]))*256 + message.data[2]);
           float totalvolt = value/2000.00;
           Serial.print(totalvolt);
           Serial.print(", ");
    }    
   Serial.println(" ");                   
  } 

//__________________________________________________________________________________________________________________________________________________________________________________________________________________

//__________________________________________________________________________________________________________________________________________________________________________________________________________________

   
 }}}
