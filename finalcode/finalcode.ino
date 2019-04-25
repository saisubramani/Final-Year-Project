#include <ESP8266HTTPClient.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>`
#include <PubSubClient.h>
 
// Connect to the WiFi
const char* ssid = "sujithkumar";
const char* password = "sujith7916";
const char* mqtt_server = "broker.mqttdashboard.com";
//const char* mqtt_server = "test.mosquitto.org";

String value="";
int count = 0 ;

String mystring,Data,motor_status;

char data[30] = "";
char statu[5]="";

char msg_buffer[20];
WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) 
{
  
  //Serial.print("Message received in topic: ");
  //Serial.println(topic);
  //Serial.print("Message ");
  
  if(String(topic) == "machine/status")
  {
    //Serial.println("status");
    for(int i =0 ;i<length;i++)
    {
      statu[i] = (char)payload[i];
    }
    motor_status = String(statu)+'\n';
    for(int i =0;i<motor_status.length();i++)
    {
      Serial.write(statu[i]);    
    }
    delay(500);
    Serial.println();
  }

  else if(String(topic) == "machine/set")
  {
    for(int i = 0; i < length; i++) 
    {
      data[i] = (char)payload[i]; 
      count += 1;
    }
    mystring = String(data)+'\n';
    Serial.print("machineset:");
    Serial.println(mystring);

 // sending limit data to Arduino UNO

    for(int i =0; i<mystring.length();i++)
     {
      Serial.write(data[i]);      
      }
      Serial.println();
  }
  // sending data to Arduino UNO  
}


void reconnect()
{
while (!client.connected()) 
{
  Serial.print("Attempting MQTT connection...");
  if (client.connect("ESP8266 Client"))
  {
    Serial.println("connected");
    
    client.subscribe("machine/set");
    client.subscribe("machine/status");
    Serial.println("subscribed");
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
  // read the data(current,voltage) from arduino uno
  if(Serial.available() )
  {
    Data = Serial.readStringUntil('\n');
  }

  // read the data(current,voltage) from arduino uno
  if(!client.connected())
  {
    reconnect();
  }
  client.loop();
  
  Data.toCharArray(msg_buffer,Data.length()+1);
  client.publish("machine/data",msg_buffer);
   
  delay(2000);

}
