 #include <ESP8266HTTPClient.h>

#include <EEPROM.h>
#include <ESP8266WiFi.h>`
#include <PubSubClient.h>



// Connect to the WiFi
const char* ssid = "Janardhan";
const char* password = "two39185zero";
const char* mqtt_server = "192.168.1.3";
 
WiFiClient espClient;
PubSubClient client(espClient);


int value = 0;
char msg[20];

 
 
void callback(char* topic, byte* payload, unsigned int length) 
{
  
  Serial.print("Command from MQTT broker is : [");
  String device = topic;
  Serial.println(device);
  String dev = device.substring(4,7);
  String pin = device.substring(6,7);
  Serial.println("device:"+dev);
  Serial.println("pin:"+pin);
  switch(dev.toInt())
  {
    case 001:
      Serial.println("device:"+dev);
      condition(dev,payload);
      //client.publish("str1","")
      break;
    case 002:
      Serial.println("device:"+dev);
      condition(dev,payload);
      break;
    case 003:
     Serial.println("device:"+dev);
      condition(dev,payload);
      break;  
  }
}

void condition(String dev,byte* payload)
{
  String str1="TEST/"+dev+"/ACK";
  int p =(char)payload[0]-'0';
  
  // if MQTT comes a 0 turn off LED on D2
  if(p==0) 
  {
     //digitalWrite(LED_PIN, LOW); 
     Serial.println(str1);
    Serial.println(" Turn Off LED! " );
    client.publish("str1","LED OFF");
  } 
  // if MQTT comes a 1, turn on LED on pin D2
  if(p==1)
  {
     //digitalWrite(LED_PIN, HIGH); 
     Serial.println(str1);
    Serial.println(" Turn On LED! " );
    client.publish("str1","LED ON");
  }
}
void reconnect() {
 // Loop until we're reconnected
 while (!client.connected()) 
 {
  Serial.print("Attempting MQTT connection...");
 // Attempt to connect
  if (client.connect("ESP8266 Client")) 
  {
    Serial.println("connected");
    client.subscribe("TEST/+/DATA");
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
  //String mystr;
  //int lightRead = analogRead(lightPinIn);
  //mystr=String(lightRead);
  //delay(500);

  
 if (!client.connected()) {
  reconnect();
 }
 client.loop();
 
 //Serial.println(mystr);
 // snprintf (msg, 20, "%d", lightRead);
  //client.publish("SENSOR/001", msg);

}
