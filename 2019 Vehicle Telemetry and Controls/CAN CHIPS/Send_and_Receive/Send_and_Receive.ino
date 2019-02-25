// RECV EXAMPLE OF SERIAL CAN MODULE
// unsigned char recv(unsigned long *id, uchar *buf);
// SUPPORT: joney.sui@longan-labs.cc
#include <Serial_CAN_Module.h>
#include <SoftwareSerial.h>

Serial_CAN chip1;
Serial_CAN chip2;


#define chip1_tx  2           // tx of serial can module connect to D2
#define chip1_rx  3           // rx of serial can module connect to D3
#define chip2_tx  4           // tx of serial can module connect to D2
#define chip2_rx  5 

void setup()
{
    Serial.begin(9600);
    chip1.begin(chip1_tx, chip1_rx, 9600);      // tx, rx
    chip2.begin(chip2_tx, chip2_rx, 9600);      // tx, rx
    Serial.println("begin");
}

unsigned long id1 = 0;
unsigned long id2 = 0;
unsigned char dta1[8];
unsigned char dta2[8];
unsigned char dta3[8] = {1, 2, 3, 4, 5, 6, 7, 8};
unsigned char dta4[8] = {0, 2, 0, 4, 0, 6, 0, 0};

// send(unsigned long id, byte ext, byte rtrBit, byte len, const byte *buf);
void loop()
{
//CHIP1();

chip1.send(0x55, 0, 0, 8, dta3);   // SEND TO ID:0X55

//CHIP2();

chip2.send(0x70, 0, 0, 8, dta4);


}

void CHIP1(){
  
 if(chip1.recv(&id1, dta1) && id1 == 68)
    {
        Serial.print("GET DATA FROM ID: ");
        Serial.println(id1);
        for(int i=0; i<8; i++)
        {
            Serial.print("0x");
            Serial.print(dta1[i],HEX);
            Serial.print('\t');
        }
        Serial.println();
    }
  
}

void CHIP2(){
  
 if(chip2.recv(&id2, dta2) && id2 == 51)
    {
        Serial.print("GET DATA FROM ID: ");
        Serial.println(id2);
        for(int i=0; i<8; i++)
        {
            Serial.print("0x");
            Serial.print(dta2[i],HEX);
            Serial.print('\t');
        }
        Serial.println();
    }
  
}
// END FILE
