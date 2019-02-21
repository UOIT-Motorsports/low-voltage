// SEND EXAMPLE OF SERIAL CAN MODULE
// unsigned char send(unsigned long id, uchar ext, uchar rtrBit, uchar len, const uchar *buf);
// SUPPORT: joney.sui@longan-labs.cc
#include <Serial_CAN_Module.h>
#include <SoftwareSerial.h>

Serial_CAN can;
Serial_CAN can2;

#define can_tx1  2           // tx of serial can module connect to D2
#define can_rx1  3           // rx of serial can module connect to D3
#define can_tx2  4           // tx of serial can module connect to D2
#define can_rx2  5           // rx of serial can module connect to D3


void setup()
{
    Serial.begin(9600);
    can.begin(can_tx1, can_rx2, 9600);      // tx, rx
    can2.begin(can_tx1, can_rx2, 9600);      // tx, rx
    Serial.println("begin");
}

unsigned char dta1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
unsigned char dta2[8] = {0, 2, 0, 4, 0, 6, 0, 0};

// send(unsigned long id, byte ext, byte rtrBit, byte len, const byte *buf);
void loop()
{
    can.send(0x55, 0, 0, 8, dta1);   // SEND TO ID:0X55
    can2.send(0x70, 0, 0, 8, dta2);   // SEND TO ID:0X55
    delay(100);
    
}

// END FILE
