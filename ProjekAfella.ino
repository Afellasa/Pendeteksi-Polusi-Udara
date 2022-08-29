#include <LoRa.h>
#include <SPI.h>
#define MQ7 A0
#include "MQ135.h"
#define ANALOGPIN A1

int led=6;
int counter = 0;
MQ135 gasSensor = MQ135(ANALOGPIN);
int RL_mq7 = 1000;
float Ro_mq7 =  1078.43 ; // tergantung kalibrasi 
float CO, ppm;

void setup()
{
 Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSyncWord(0xA5);
  LoRa.setTxPower(20);
  Serial.println("LoRa Initializing OK!");
}


 

void mq135(){
  ppm = gasSensor.getPPM();
  Serial.print("CO2 : ");
  Serial.print(ppm);
  Serial.println(" ppm");
 }

void mq7(){
 int sensorvalue_mq7 = analogRead(MQ7); 
 //int u_mq7 = map(sensorvalue_mq7, 0, 4095, 0, 1023);
 float VRL_mq7= sensorvalue_mq7*5.00/1024;  
 //Serial.print("VRL : ");
 //Serial.print(VRL);
 //Serial.println(" volt");

 float Rs_mq7 = ( 5.00 * RL_mq7 / VRL_mq7 ) - RL_mq7;
 //Serial.print("Rs : ");
 //Serial.print(Rs);
 //Serial.println(" Ohm");
 
 float x_mq7 = Rs_mq7/Ro_mq7;
 CO = 107.26*pow(x_mq7,-1.494);
 Serial.print("CO : ");
 Serial.print(CO);
 Serial.println(" ppm");
  }

void loop()
{ 
  mq135();
  mq7();
      Serial.print("Sending packet: ");
      Serial.println(counter);
      LoRa.beginPacket();
      digitalWrite(led, HIGH);
      LoRa.print(ppm);
      LoRa.print(",");
      LoRa.print(CO);
      LoRa.endPacket();
       //mq135();
       //mq7(); 
       counter++;
       delay(1000);
       digitalWrite(led, LOW);
       delay(9000);
}
