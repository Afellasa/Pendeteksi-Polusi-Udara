
//BOARD MANAGER ESP32 1.0.2
//LIBRARY MANAGER LORA SANDEEP MISTRY 0.8.0
//GND   GND
//3.3V  VCC
//D5    NSS
//D23   MOSI
//D19   MISO
//D18   SCK
//D14   RST
//D2    DIO0


#include <LoRa.h>
#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>
 
#define ss 5
#define rst 14
#define dio0 2
//"RumahNikita";
//"1WeKKEadyTKlGZ29EgqO5ndZSwjMpSRdcjJImvAltuCsQJE1pHJUclXmWzXrRTd";

const char* ssid = "Afella";
const char* password = "afella18";
const char* mqttServer = "20.184.13.157";
const int mqttPort = 1883;
const char* mqttUser= "fellaso";
const char* mqttPassword = "password";

IPAddress ip; 
WiFiClient espClient;
PubSubClient client(espClient);

int ide = 1;
String sensor ;
String LoRaData;
//int rssimu;
 
void setup() 
{
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Receiver");
 
  LoRa.setPins(ss, rst, dio0);    //setup LoRa transceiver module
 
  while (!LoRa.begin(433E6))     //433E6 - Asia, 866E6 - Europe, 915E6 - North America
  {
    Serial.println("gagal maneh asu");
    delay(500);
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  
  client.setServer(mqttServer, 1883);
  client.connect("esp1",mqttUser,mqttPassword);
  while (!client.connected()) {
  Serial.println("Connecting to MQTT...");
  Serial.println(client.state());
  }
  Serial.println("terkoneksi");
  ip = WiFi.localIP();
  Serial.println(ip);
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");
}
 
void loop() 
{
    int packetSize = LoRa.parsePacket(); 
    String LoRaData = "";// try to parse packet
  if (packetSize) 
  {
    
    Serial.print("Received packet '");
 
    while (LoRa.available())              // read packet
    {
      LoRaData = LoRa.readString();
      Serial.println(LoRaData); 
      
    }
    //Serial.print("' with RSSI ");         // print RSSI of packet
    //Serial.println(LoRa.packetRssi());
    float rssimu = LoRa.packetRssi();
    float snr = LoRa.packetSnr();
      //Serial.println(LoRa.packetRssi());
      sensor = (String)ide;
      sensor+=",";
      sensor+= (String)LoRaData;
      sensor+=",";
      sensor+= (String)rssimu;
      sensor+=",";
      sensor+= (String)snr;
      client.publish("/loraku", (char*)sensor.c_str());
      Serial.println((char*)sensor.c_str());
      Serial.println("Kirim sukses");
  client.loop();
    
  }
  
  //terima();
  //kirim()
}
