
//Code used to interface 2003 M/Y GM N body/LA1 PCM with 2004 M/Y 4t65e transaxle.  Code monitors four high/low signals (A/B/C/P) from transmission range switch to determine manual valve position
//then manipulates ground state of PCM pin 17 and 22 to simulate corresponding transmission fluid pressure switch signals.  Pin 17 spliced in breakout harness @ C102; Pin 22 added to vehicle harness.
//N channel MOSFETs used on both input and output.

int trsAState = 0;
int trsAlastState = 0;
int trsBState = 0;
int trsBlastState = 0;
int trsCState = 0;
int trsClastState = 0;
int trsPState = 0;
int trsPlastState = 0;
int UThreshold = 100;
int LThreshold = 20;

void setup() {
  Serial.begin(9600);
  // define four analog pins to watch high/low on transmission range switch signals A/B/C/P (5v board power loop is grounded by MOSFETs gated by TRS voltage):
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  //define two digital pins as output; these will drive MOSFETs to switch ground for PCM ckts 17 and 22:
  pinMode(2, OUTPUT);  //PCM ckt 17
  pinMode(4, OUTPUT);  //PCM ckt 22

}

void loop() {
  // Check input states (0-1023 values correspond 0-5 VDC) 
  int trsAState = analogRead(A1);
  int trsBState = analogRead(A2);
  int trsCState = analogRead(A3);
  int trsPState = analogRead(A4);

//kak this into serial monitor for debugging purposes
  Serial.println("TRS A: ");
  Serial.println(trsAState);
  Serial.println("TRS B: ");
  Serial.println(trsBState);
  Serial.println("TRS C: ");
  Serial.println(trsCState);
  Serial.println("TRS P: ");
  Serial.println(trsPState);

  //check for state change:
  if(trsAState != trsAlastState || trsBState != trsBlastState || trsCState != trsClastState || trsPState != trsPlastState)
  {

    //set pins back low
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    
    //set state history:
    int trsAlastState = trsAState;
    int trsBlastState = trsBState;
    int trsClastState = trsCState;
    int trsPlastState = trsPState;

    //check for park position:
    if(trsAState > UThreshold && trsBState < LThreshold && trsCState > UThreshold && trsPState > UThreshold)
    {
      digitalWrite(4, HIGH);
      digitalWrite(2, LOW);
      Serial.println("Park position");
    }
  
    //check for reverse position:
    if(trsAState > UThreshold && trsBState > UThreshold && trsCState > UThreshold && trsPState < LThreshold)
    {
      digitalWrite(4, HIGH);
      digitalWrite(2, LOW);
      Serial.println("Reverse position");
    }
  
    //check for neutral position:
    if(trsAState < LThreshold && trsBState > UThreshold && trsCState > UThreshold && trsPState > UThreshold)
    {
      digitalWrite(4, HIGH);
      digitalWrite(2, LOW);
      Serial.println("Neutral position");
    }
  
    //check for D4 position:
    if(trsAState < LThreshold && trsBState > UThreshold && trsCState > UThreshold && trsPState < LThreshold)
    {
      digitalWrite(4, HIGH);
      digitalWrite(2, LOW);
      //uncomment for debug Serial.println("Drive position");
    }
  
    //check for D3 position:
    //if(trsAState > UThreshold && trsBState > UThreshold && trsCState > UThreshold && trsPState > UThreshold)
    //{
    //}
  
    //check for D2 position:
    if(trsAState > UThreshold && trsBState < LThreshold && trsCState > UThreshold && trsPState < LThreshold)
    {
      digitalWrite(2, HIGH);
      digitalWrite(4, LOW);
      //uncomment for debug Serial.println("D2 position");
    }
  
    //check for D1 position:
    if(trsAState < LThreshold && trsBState < LThreshold && trsCState > UThreshold && trsPState > UThreshold)
    {
      digitalWrite(2, HIGH);
      digitalWrite(4, HIGH);
      //uncomment for debug Serial.println("D1 position");
    }
  }
}
