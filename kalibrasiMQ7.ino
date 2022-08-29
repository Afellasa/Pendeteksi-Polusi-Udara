int RL_mq7 = 1000;
#define MQ7 A0

void setup()
{
 Serial.begin(9600);
}

void loop()
{
 int sensorvalue_mq7 = analogRead(MQ7); 
 //int ubah = map(sensorvalue_mq7, 0, 4095, 0, 1023);
 float VRL_mq7= sensorvalue_mq7*5.00/1024; 
 Serial.print("VRL_mq7 : ");
 Serial.print(VRL_mq7);
 Serial.println(" volt");

 float Rs_mq7 = ( 5.00 * RL_mq7 / VRL_mq7 ) - RL_mq7;
 Serial.print("Rs_mq7 : ");
 Serial.print(Rs_mq7);
 Serial.println(" Ohm");

 float Ro_mq7 = Rs_mq7/27;
 Serial.print("Ro_mq7 : ");
 Serial.print(Ro_mq7);
 Serial.println(" Ohm");
 delay (5000); 
}
 
 
