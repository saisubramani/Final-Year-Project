double Vm = 0;
double VmPrevious = 0;
double DVmax = 0;
int crosscount=0;
int climbhill=0;
double DVrms;
double Vrms;
double VmY = 0;
double VmPreviousY = 0;
double DVmaxY = 0;
int crosscountY=0;
int climbhillY=0;
double DVrmsY;
double VrmsY;
double VmB = 0;
double VmPreviousB = 0;
double DVmaxB = 0;
int crosscountB=0;
int climbhillB=0;
double DVrmsB;
double VrmsB;





void RPHASE()
{
  VmPrevious = Vm;
  delay(5000);
  Vm = analogRead(A0);
  if (Vm >VmPrevious && Vm>511)
  {
    climbhill = 0;
    DVmax = Vm;
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

void YPHASE()
{
  VmPreviousY = VmY;
  delay(5000);
  VmY = analogRead(A1);
  if (VmY >VmPreviousY && VmY>511)
  {
    climbhillY = 0;
    DVmaxY = VmY;
  }
  if (VmY < VmPreviousY && climbhillY ==1)
  {
    climbhillY = 0;
    DVmaxY = VmPreviousY;
    DVrmsY = DVmaxY/sqrt(2);
    VrmsY=(((DVrmsY-420.76)/-90.24)*-210.2)+210.2;
    Serial.println("Y_PHASE-VOLATGE:");
    Serial.println(VrmsY);
    DVmaxY = 0;
  }  
}


void BPHASE()
{
  VmPreviousB = VmB;
  delay(5000);
  Vm = analogRead(A2);
  if (VmB >VmPreviousB && VmB>511)
  {
    climbhillB = 0;
    DVmaxB = VmB;
  }
  if (VmB < VmPreviousB && climbhillB ==1)
  {
    climbhillB = 0;
    DVmaxB = VmPreviousB;
    DVrmsB = DVmaxB/sqrt(2);
    VrmsB=(((DVrmsB-420.76)/-90.24)*-210.2)+210.2;
    Serial.println("B_PHASE-VOLATGE:");
     Serial.println(VrmsB);
    DVmaxB = 0;
  }  
}


void setup() 
{
  Serial.begin(9600);
  Serial.println("CALCULATING VOLTAGE");
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  void RPHASE();
  void YPHASE();
  void BPHASE();
  
}

void loop()
{
 RPHASE();
 YPHASE();
 BPHASE();
}
