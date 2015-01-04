/********************************************************
 * PID Adaptive radiator control system
 * Code modified by Olof Björkqvist (olof@bjorkqvist.nu)
 * 
 ********************************************************/

// Define pins and other constands
const int valvecontrolPin = 9;
const int tempsimPin = 0;
const int delaytime = 1000;

//Define Variables we'll be connecting to. TempRadOutSet is the radiator temp setpoint
double TempRadOutSet;
int tempsimval;

// PID variabler
double error, lasterror = 0.0, sumerror, derror, PIDvalue;
double kp = 7;
double ki = 0.0001;
double kd = 0.2;
int output = 0;

// Tempcurve: TempRadOutSet=kCurve*TempOutside+mCurve
// TempOutsideStart=Temperature when the heating system valve is opened
double TempOutsideStart=17, TempRadOutMax=60, TempOutsideMin=-25;
double kCurve=0, mCurve=0;
double TempOutside, TempRadIn, TempRadOut, TempTapwaterOut;

void setup()
{
  //initialize the variables we're linked to
  // ### analogRead shall be updated to radoutThermomether when the code is merged.
  kCurve=(TempRadOutMax-TempOutsideStart)/(TempOutsideMin-TempOutsideStart);
  mCurve=TempRadOutMax-kCurve*TempOutsideMin;

  //Open valvecontrole-pin for output
  pinMode(valvecontrolPin, OUTPUT);

  //Debug temperatures

  TempOutside=-5;
  TempRadOut=27;
  TempRadIn=25;
  TempTapwaterOut=55;
  TempRadOutSet=40;
  Serial.begin(9600);          //  setup serial


}

void loop()
{
  tempsimval = analogRead(tempsimPin);
  TempRadOut = tempsimval*(TempRadOutMax-TempOutsideStart)/1023+TempOutsideStart;
  TempRadOutSet = kCurve*TempOutside+mCurve;

  Serial.println(tempsimval);
  Serial.println(TempRadOut);

  delay(delaytime);
  
// Calculater error, sum of error over time och derror.

  error = TempRadOutSet - TempRadOut;
  sumerror += (error * delaytime);
  derror = (error - lasterror) / delaytime;

  PIDvalue = kp * error + ki * sumerror + kd * derror ;
  output += PIDvalue;

  Serial.println(output);
  
  // Check if output is within limits
    if (output > 255)
    {
      output = 255;
    }
    
    if (output < 0)
    {
      output = 0;
    }

  Serial.println(output);

// Send result to valve
  analogWrite(valvecontrolPin, output);
  
}
