#include <ESP8266HTTPClient.h>

#include <EEPROM.h>
#include <ESP8266WiFi.h>`
#include <PubSubClient.h>



 
// Connect to the WiFi
const char* ssid = "sujithkumar";
const char* password = "sujith7916";
const char* mqtt_server = "test.mosquitto.org";
 
WiFiClient espClient;
PubSubClient client(espClient);

//unsigned long time;
//char message_buff[100];
int value = 0;
char msg1[50];

 
 
void callback(char* topic, byte* payload, unsigned int length) 
{
  
  Serial.print("Messageved in topic: ");
  Serial.println(topic);
  Serial.print("Message ");
  for(int i = 0; i < length; i++) 
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}


void reconnect() {
while (!client.connected()) 
{
  Serial.print("Attempting MQTT connection...");
  if (client.connect("ESP8266 Client"))
  {
    Serial.println("connected");
    client.publish("machine/state","5,855,5,-172,1500");
  } 
  else 
  {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println(" try again in 5 seconds");
  // Wait 5 seconds before retrying
    delay(5000);
  }
 }
}
 
void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print(WiFi.localIP());
  Serial.println("/");

 client.setServer(mqtt_server, 1883);
 client.setCallback(callback);
 
 
}
 
void loop()
{
  //msg1[50]=" i am published TOPIC";
 if(!client.connected())
 {
  reconnect();
 }
client.loop(); 
//client.publish("SENSOR/DATA", msg1);

}
