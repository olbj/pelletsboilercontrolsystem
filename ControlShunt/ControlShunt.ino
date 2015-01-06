/********************************************************
 * PID Adaptive radiator control system
 * Code modified by Olof Björkqvist (olof@bjorkqvist.nu)
 * Code sorce from PID Example code for adptive control
 * One of the benefits of the PID library is that you can
 * change the tuning parameters at any time.  this can be
 * helpful if we want the controller to be agressive at some
 * times, and conservative at others.   in the example below
 * we set the controller to use Conservative Tuning Parameters
 * when we're near TempRadOutSet and more agressive Tuning
 * Parameters when we're farther away.
 * 
 ********************************************************/

#include <PID_v1.h>

// Define pins and other constands
const int ValveControlPin = 9;
const int TempsimPin = 0;
const int DelayTime = 10;

//Define Variables we'll be connecting to. TempRadOutSet is the radiator temp setpoint
double TempRadOutSet, Input, Output;
int SetValve = 0;

// Debug variables
int TempsimVal;
long Iteration=0;

//Define the aggressive and conservative Tuning Parameters
double aggKp=4, aggKi=0.2, aggKd=1;
double consKp=1, consKi=0.05, consKd=0.25;
double kCurve=0, mCurve=0;

// Define Temperature variables. 
// TempRadOutMin = T,ie and defines outside temeparture when valve opens.
double TempOutside, TempRadIn, TempRadOut, TempTapwaterOut;
double TempRadOutMin=15, TempRadOutMax=60, TempOutsideMin=-25;

//Specify the links and initial tuning parameters
PID myPID(&TempRadOut, &Output, &TempRadOutSet, consKp, consKi, consKd, DIRECT);

void setup()
{
  //initialize the variables we're linked to
  // ### analogRead shall be updated to radoutThermomether when the code is merged.
  Input = 15;
  kCurve=(TempRadOutMax-TempRadOutMin)/(TempOutsideMin-TempRadOutMin);
  mCurve=TempRadOutMax-kCurve*TempOutsideMin;
  TempOutside=-5;
  TempRadOut=27;
  TempRadIn=25;
  TempTapwaterOut=55;
  TempRadOutSet=40;

  // Open ValveControPin for input
  pinMode(ValveControlPin, OUTPUT);

  //turn the PID on
  myPID.SetMode(AUTOMATIC);

  //Open serial print for debug printing
  Serial.begin(9600);
  delay(500); //Delay in order to avoid PID crash.
}

void loop()
{
  //First phase: Set up the debug variables. TempRadOut is simulated by pin 0
  TempsimVal = analogRead(TempsimPin);
  TempRadOut = TempsimVal/1023*(TempRadOutMax-TempRadOutMin)+TempRadOutMin
  Iteration += 1;
  delay(DelayTime)
  //Debug variables ended

  Input = TempRadOut;
  //Tempcurve: TempRadOutSet=kCurve*TempOutside+mCurve
  TempRadOutSet = kCurve*TempOutside+mCurve;
  
  double gap = abs(TempRadOutSet-Input); //distance away from TempRadOutSet
  if(gap<5)
  {  //we're close to TempRadOutSet, use conservative tuning parameters
    myPID.SetTunings(consKp, consKi, consKd);
  }
  else
  {
     //we're far from TempRadOutSet, use aggressive tuning parameters
     myPID.SetTunings(aggKp, aggKi, aggKd);
  }
  
  myPID.Compute();
  SetValve = int (Output+0.5);
  analogWrite(ValveControlPin,SetValve);

  //Debug printing
  Serial.print("Iteration");
  Serial.print("\t");
  Serial.print("TempsimVal");
  Serial.print("\t");
  Serial.print("TempRadOut");
  Serial.print("\t");
  Serial.print("TempRadOutSet");
  Serial.print("\t");
  Serial.print("Output");
  Serial.print("\t");
  Serial.print("SetValve");
  Serial.println(" ");
  Serial.print(Iteration);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(TempsimVal);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(TempRadOut);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(TempRadOutSet);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(Output);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(SetValve);
  Serial.println(" ");
}
