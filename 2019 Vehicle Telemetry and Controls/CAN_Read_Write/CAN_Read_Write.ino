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
 
//send1();

recieve55(); 
delay(1000);


//send2();

//recieve70(); 

}

void recieve55(){
  tCAN message;
if (mcp2515_check_message()) 
  {
    if (mcp2515_get_message(&message)) 
  {
 
        if(message.id == 0x55)  //uncomment when you want to filter
             {
               
               Serial.print("ID: ");
               Serial.print(message.id,HEX);
               Serial.print(", ");
               Serial.print("Data: ");
             //  Serial.print(message.header.length,DEC);
               for(int i=0;i<message.header.length;i++) 
                { 
                  Serial.print(message.data[i],HEX);
                  Serial.print(" ");
                }
               Serial.println("");
             }
           if(message.id == 0x70)  //uncomment when you want to filter
             {
               
               Serial.print("ID: ");
               Serial.print(message.id,HEX);
               Serial.print(", ");
               Serial.print("Data: ");
             //  Serial.print(message.header.length,DEC);
               for(int i=0;i<message.header.length;i++) 
                { 
                  Serial.print(message.data[i],HEX);
                  Serial.print(" ");
                }
               Serial.println("");
             }
           
}}
}

void recieve70(){
  tCAN message;
if (mcp2515_check_message()) 
  {
    if (mcp2515_get_message(&message)) 
  {
  
        if(message.id == 0x70)  //uncomment when you want to filter
             {
               
               Serial.print("ID: ");
               Serial.print(message.id,HEX);
               Serial.print(", ");
               Serial.print("Data: ");
             //  Serial.print(message.header.length,DEC);
               for(int i=0;i<message.header.length;i++) 
                { 
                  Serial.print(message.data[i],HEX);
                  Serial.print(" ");
                }
               Serial.println("");
             }
            
           }}

}


void send1()
{
  tCAN message;
 message.id = 0x44;//formatted in HEX
        message.header.rtr = 0;
        message.header.length = MessageLength; //formatted in DEC
  message.data[0] = 0x08;
  message.data[1] = 0x01;
  message.data[2] = 0x1B;
  message.data[3] = 0x05; //formatted in HEX
  message.data[4] = 0X55;
  message.data[5] = 0X48;
  message.data[6] = 0X69;
  message.data[7] = 0X11;
  

mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
mcp2515_send_message(&message);

Serial.println("Message1 Sent");
}



void send2()
{
  tCAN message;
 message.id = 0x33;//formatted in HEX
        message.header.rtr = 0;
        message.header.length = MessageLength; //formatted in DEC
  message.data[0] = 0x01;
  message.data[1] = 0x01;
  message.data[2] = 0x1A;
  message.data[3] = 0x55; //formatted in HEX
  message.data[4] = 0X55;
  message.data[5] = 0X00;
  message.data[6] = 0X00;
  message.data[7] = 0X11;
  

mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
mcp2515_send_message(&message);

Serial.println("Message2 Sent");
}
