/****************************************************************************
CAN Read Demo for the SparkFun CAN Bus Shield. 

Written by Stephen McCoy. 
Original tutorial available here: http://www.instructables.com/id/CAN-Bus-Sniffing-and-Broadcasting-with-Arduino
Used with permission 2016. License CC By SA. 

Distributed as-is; no warranty is given.
*************************************************************************/

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
 
 
recievecheck(); 




}

void recievecheck()
{
  tCAN message;
if (mcp2515_check_message()) 
  {
    if (mcp2515_get_message(&message)) 
  {
        if(message.id == 0xFF)  //uncomment when you want to filter
             {
               
               Serial.print("Master Id: ");
               Serial.print(message.id,HEX);
                Serial.println(message.data[0],HEX);
              // check for my id:
              if(message.data[0] == 0x56) { // yay me
                Serial.print("got my id, new array length for send: ");
                Serial.println(message.data[1]);
                MessageLength = message.data[1];
                send56();
              }
             }
           }}
}




void send56()
{
  tCAN message;
 message.id = 0x56; //formatted in HEX
        message.header.rtr = 0;
        message.header.length = MessageLength; //formatted in DEC
  message.data[0] = 1;
  message.data[1] = 2;
  message.data[2] = 3;
  message.data[3] = 4; //formatted in HEX
  message.data[4] = 5;
  message.data[5] = 6;
  message.data[6] = 7;
  message.data[7] = 8;

mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
mcp2515_send_message(&message);

Serial.println("Message Sent");
}
/*
 
 void recv2()
{
 tCAN message;
if (mcp2515_check_message()) 
  {
    if (mcp2515_get_message(&message)) 
  {
        
          if(message.id == 0x57 )   
               {
               Serial.print("ID: ");
               Serial.print(message.id,HEX);
               Serial.print(", ");
               Serial.print("Data: ");
               Serial.print(message.header.length,DEC);
               Serial.print(" ");
               for(int i=0;i<message.header.length;i++) 
                { 
                  Serial.print(message.data[i],HEX);
                  Serial.print(" ");
                }
               Serial.println("");
            
               }
           }}
}
*/
