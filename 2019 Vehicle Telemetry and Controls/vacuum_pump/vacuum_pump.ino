/*
 * COde for Vacuum Pump
 * Analog Input = inHg
 *  625 = 0 
 *  430 = -10
 *  325 = -15
 *  220 = -20
 * 
 * RELAY
 * Positive on Relay goes to Pin 2
 * Negative on Relay goes to GND
 * 
 * SENSOR WIRES
 * WHITE = A2
 * BLUE = GROUND
 * BROWN = 5V
 */
void setup() {
  // put your setup code here, to run once:
pinMode(2, OUTPUT);
Serial.begin(9600);
}

void loop() {

  
  // put your main code here, to run repeatedly:
int D = analogRead(A2);
Serial.println(D);


if (D >= 430){
analogWrite(2,255);

}

if (D <= 220){
analogWrite(2,0);

}
}
