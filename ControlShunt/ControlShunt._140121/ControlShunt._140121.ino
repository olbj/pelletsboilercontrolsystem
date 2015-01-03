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

//Define Variables we'll be connecting to. TempRadOutSet is the radiator temp setpoint
double TempRadOutSet, Input, Output;

//Define the aggressive and conservative Tuning Parameters
double aggKp=4, aggKi=0.2, aggKd=1;
double consKp=1, consKi=0.05, consKd=0.25;
// Tempcurve: TempRadOutSet=kCurve*TempOutside+mCurve
double TempRadOutMin=15, TempRadOutMax=60, TempOutsideMin=-25;
double kCurve=0, mCurve=0;
double TempOutside, TempRadIn, TempRadOut, TempTapwaterOut;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &TempRadOutSet, consKp, consKi, consKd, DIRECT);

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

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  Input = TempRadOut;
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
  analogWrite(3,Output);
}
