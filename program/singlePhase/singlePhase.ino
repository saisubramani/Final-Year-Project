double Vm = 0;
double VmPrevious = 0;
double DVmax = 0;
int crosscount=0;
int climbhill=0;
double DVrms;
double Vrms;
void RPHASE();




void setup() 
{
  Serial.begin(9600);
  Serial.println("CALCULATING VOLTAGE");  

}

void loop() 
{
  Serial.println("loop");
  VmPrevious = Vm;
  delay(500);
  Vm = analogRead(A0);
  Serial.println(Vm);
  if (Vm > VmPrevious && Vm>511)
  {
    climbhill = 0;
    DVmax = Vm;
    Serial.println("DVmax");
  }
  if (Vm < VmPrevious && climbhill ==1)
  {
    climbhill = 0;
    DVmax = VmPrevious;
    DVrms = DVmax/sqrt(2);
    Vrms=(((DVrms-420.76)/-90.24)*-210.2)+210.2;
    Serial.println("R_PHASE-VOLATGE:");
    Serial.println(Vrms);
    DVmax = 0;
  } 
}
