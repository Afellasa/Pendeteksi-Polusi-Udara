#include "MQ135.h"
#define ANALOGPIN A1
MQ135 gasSensor = MQ135(ANALOGPIN);
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //float rs = gasSensor.getResistance();
  //Serial.print("Rs_Mq135: ");
  //Serial.print(rs);
  //Serial.println(" Ohm");
  float rzero = gasSensor.getRZero();
  Serial.print("Ro_Mq135: ");
  Serial.print(rzero);
  Serial.println(" Ohm");
  delay(5000);
}
