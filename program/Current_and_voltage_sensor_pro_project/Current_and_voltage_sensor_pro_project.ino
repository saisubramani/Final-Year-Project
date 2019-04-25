double sensorValue=0;
double sensorValue1=0;
int crosscount=0;
int climbhill=0;
double VmaxD=0;
double VeffD;
double Veff;
#define CURRENT_SENSOR A2  // Define Analog input pin that sensor is attached
 float amplitude_current;      // Float amplitude current
float effective_value;       // Float effective current

void setup() {
  pinMode(A0,INPUT);
  
Serial.begin(9600);
 pins_init();
}
void loop() {
sensorValue1=sensorValue;
delay(100);
sensorValue = analogRead(A0);
if (sensorValue>sensorValue1 && sensorValue>511){
  climbhill=1;
  VmaxD=sensorValue;
  }
if (sensorValue<sensorValue1 && climbhill==1){
  climbhill=0;
  VmaxD=sensorValue1;
  VeffD=VmaxD/sqrt(2);
  Veff=(((VeffD-420.76)/-90.24)*-210.2)+210.2;
  
  
  VmaxD=0;}
//current program
int sensor_max;
    sensor_max = getMaxValue();
    
    
    //the VCC on the Arduino interface of the sensor is 5v
    
    amplitude_current=(float)(sensor_max-512)/1024*5/100*1000000; // for 5A mode,you need to modify this with 20 A and 30A mode;
    effective_value=amplitude_current/1.414;
    
    //for minimum current=1/1024*5/185*1000000/1.414=18.7(mA)
    //Only sinusoidal alternating current
    
    
    
    //Only one number after the decimal point
   delay(580);
    Serial.println("Voltage");
  Serial.println(Veff);
    Serial.println("The effective value of the current is(in A)");
    Serial.println(effective_value/1000,1);
}
void pins_init()
{
    pinMode(CURRENT_SENSOR, INPUT);
}
/*Function: Sample for 1000ms and get the maximum value from the S pin*/
 
int getMaxValue()
{
    int sensorValue;    //value read from the sensor
    int sensorMax = 0;
    uint32_t start_time = millis();
    while((millis()-start_time) < 1000) //sample for 1000ms
    {
        sensorValue = analogRead(CURRENT_SENSOR);
        if (sensorValue > sensorMax)
        {
            /*record the maximum sensor value*/
            
            sensorMax = sensorValue;
        }
    }
    return sensorMax;

}
