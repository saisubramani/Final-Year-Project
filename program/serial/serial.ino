#include <SoftwareSerial.h>
SoftwareSerial sw(2, 3); // RX, TX
void setup()
{
  Serial.begin(115200);
  Serial.println("Interfacfing arduino with nodemcu");
  sw.begin(115200);

}   
void loop() 
{
  Serial.println("Sending data to nodemcu");
  int current=analogRead(A0);
  //int voltage=analogRead(A1);
  
  //Serial.println("current :" +String(current));
  //Serial.println("voltage :"+String(voltage));

  Serial.println();
  //String RPM = "1500";
  //String temp = "45.25";
  //String vib = "1.5";
  //String cur = String(current);
  //String vol =String(voltage);
  //Serial.print(temp,vol,cur,vib,RPM);
  //sw.print(temp+","+vol+","+vib+","+cur+","+RPM);
  //sw.print("voltage:"+String(voltage));
  sw.print("35.2,236,5,1450,-2");
  sw.println();
  delay(5000);
}
