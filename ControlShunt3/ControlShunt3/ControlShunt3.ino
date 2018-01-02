/********************************************************
 PID Adaptive radiator temperature control system
 Code modified by Olof Björkqvist (olof@bjorkqvist.nu)
 Code sorce from PID Example code for adptive control
 Code source http://milesburton.com/Main_Page?title=Dallas_Temperature_Control_Library

    Copyright (C) 2015  Olof Björkqvist <olof@bjorkqvist.nu>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ********************************************************/

#include <PID_v1.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Define pins and other constands
const int ValveControlPin = 12;
const int TempsimPin = 0;
const int DelayTime = 10;

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
#define TEMPERATURE_PRECISION 9

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
DeviceAddress radiatorinThermometer, radiatoroutThermometer, tapwaterThermometer, outsideThermometer;

//Define Variables we'll be connecting to. TempRadOutSet is the radiator temp setpoint
double TempRadOutSet, Input, Output, LastOutput;
int SetValve = 0;

// Debug variables
int TempsimVal;
long Iteration=0;

//Define the aggressive and conservative Tuning Parameters
//double aggKp=4, aggKi=0.2, aggKd=1;
//double consKp=1, consKi=0.05, consKd=0.25;
//double aggKp=40, aggKi=2, aggKd=10;
double aggKp=2.5, aggKi=1, aggKd=5;
double consKp=0.5, consKi=0.15, consKd=0.40;

//double consKp=10, consKi=0.5, consKd=2.5;
double kCurve=0, mCurve=0;

// Define Temperature variables. 
// TempRadOutMin = T,ie and defines outside temeparture when valve opens.
double TempOutside, TempRadIn, TempRadOut, TempTapwaterOut;
double TempRadOutMin=17, TempRadOutMax=80, TempOutsideMin=-24, TempOutsideManual=-5, TempRadManual=45;

//Specify the links and initial tuning parameters
PID myPID(&TempRadOut, &Output, &TempRadOutSet, consKp, consKi, consKd, DIRECT);

//Specify operation mode: RunMode=0: Automatic, RunMode=1: Manual, RunMode=2: Off
int RunMode=1;

void setup()
{
  //Open serial print for debug printing
  Serial.begin(115200);
  delay(500); //Delay in order to avoid PID crash.

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
  // 17-01-11 Debug setting for PID regulator. Remove when finished
  aggKp = consKp;
  aggKi = consKi;
  aggKd = consKd;

  //Serial.print("Input data");
  //Serial.println();
  //Serial.print("RunMode: ");
  //Serial.print(RunMode);
  //Serial.println();
  //Serial.print("Input: ");
  //Serial.print(Input);
  //Serial.println();
  //Serial.print("kCurve: ");
  //Serial.print(kCurve);
  //Serial.println();
  //Serial.print("mCurve: ");
  //Serial.print(mCurve);
  //Serial.println();
  //Serial.print("TempOutside: ");
  //Serial.print(TempOutside);
  //Serial.println();
  //Serial.print("TempRadOut: ");
  //Serial.print(TempRadOut);
  //Serial.println();
  //Serial.print("TempRadIn: ");
  //Serial.print(TempRadIn);
  //Serial.println();
  //Serial.print("TempTapwaterOut: ");
  //Serial.print(TempTapwaterOut);
  //Serial.println();
  //Serial.print("TempRadOutSet: ");
  //Serial.print(TempRadOutSet);
  //Serial.println();
  //Serial.println();
  delay(5000); 
  
  // Start up the library
  sensors.begin();

  // locate devices on the bus
  //Serial.print("Locating devices...");
  //Serial.print("Found ");
  //Serial.print(sensors.getDeviceCount(), DEC);
  //Serial.println(" devices.");

  // report parasite power requirements
  //Serial.print("Parasite power is: "); 
  /*if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");*/

  // assign address manually.  the addresses below will beed to be changed
  // to valid device addresses on your bus.  device address can be retrieved
  // by using either oneWire.search(deviceAddress) or individually via
  // sensors.getAddress(deviceAddress, index)
  //insideThermometer = { 0x28, 0x1D, 0x39, 0x31, 0x2, 0x0, 0x0, 0xF0 };
  //outsideThermometer   = { 0x28, 0x3F, 0x1C, 0x31, 0x2, 0x0, 0x0, 0x2 };

  // search for devices on the bus and assign based on an index.  ideally,
  // you would do this to initially discover addresses on the bus and then 
  // use those addresses and manually assign them (see above) once you know 
  // the devices on your bus (and assuming they don't change).
  // 
  // method 1: by index
  /*if (!sensors.getAddress(radiatorinThermometer, 0)) Serial.println("Unable to find address for Device 0"); 
  if (!sensors.getAddress(radiatoroutThermometer, 1)) Serial.println("Unable to find address for Device 0"); 
  if (!sensors.getAddress(tapwaterThermometer, 2)) Serial.println("Unable to find address for Device 0"); 
  if (!sensors.getAddress(outsideThermometer, 3)) Serial.println("Unable to find address for Device 1"); */

  // method 2: search()
  // search() looks for the next device. Returns 1 if a new address has been
  // returned. A zero might mean that the bus is shorted, there are no devices, 
  // or you have already retrieved all of them.  It might be a good idea to 
  // check the CRC to make sure you didn't get garbage.  The order is 
  // deterministic. You will always get the same devices in the same order
  //
  // Must be called before search()
  //oneWire.reset_search();
  // assigns the first address found to insideThermometer
  //if (!oneWire.search(insideThermometer)) Serial.println("Unable to find address for insideThermometer");
  // assigns the seconds address found to outsideThermometer
  //if (!oneWire.search(outsideThermometer)) Serial.println("Unable to find address for outsideThermometer");

  // show the addresses we found on the bus
  //Serial.print("Device 0 Address: ");
  printAddress(radiatorinThermometer);
  //Serial.println();

  //Serial.print("Device 1 Address: ");
  printAddress(radiatoroutThermometer);
  //Serial.println();

  //Serial.print("Device 2 Address: ");
  printAddress(tapwaterThermometer);
  //Serial.println();

  //Serial.print("Device 3 Address: ");
  printAddress(outsideThermometer);
  //Serial.println();

  // set the resolution to 9 bit
  sensors.setResolution(radiatorinThermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(radiatoroutThermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(tapwaterThermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(outsideThermometer, TEMPERATURE_PRECISION);

  //Serial.print("Device 0 Resolution: ");
  //Serial.print(sensors.getResolution(radiatorinThermometer), DEC); 
  //Serial.println();

  //Serial.print("Device 1 Resolution: ");
  //Serial.print(sensors.getResolution(radiatoroutThermometer), DEC); 
  //Serial.println();

  //Serial.print("Device 2 Resolution: ");
  //Serial.print(sensors.getResolution(tapwaterThermometer), DEC); 
  //Serial.println();

  //Serial.print("Device 3 Resolution: ");
  //Serial.print(sensors.getResolution(outsideThermometer), DEC); 
  //Serial.println();

  // Open ValveControPin for input
  pinMode(ValveControlPin, OUTPUT);

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    /*if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);*/
  }
}

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  //Serial.print("Temp C: ");
  //Serial.print(tempC);
  //Serial.print(" Temp F: ");
  //Serial.print(DallasTemperature::toFahrenheit(tempC));
}

// function to print a device's resolution
void printResolution(DeviceAddress deviceAddress)
{
  //Serial.print("Resolution: ");
  //Serial.print(sensors.getResolution(deviceAddress));
  //Serial.println();    
}

// main function to print information about a device
void printData(DeviceAddress deviceAddress)
{
  //Serial.print("Device Address: ");
  printAddress(deviceAddress);
  //Serial.print(" ");
  printTemperature(deviceAddress);
  //Serial.println();
}


void loop()
{
  switch (RunMode) {
  case 4:
    //Serial.print("Entering valve exercise mode");
    //Serial.println();
    break:
  case 3:
    //Serial.print("Switching off");
    //Serial.println();
    TempOutside=50;
    TempRadOutSet = int (kCurve*TempOutside+mCurve+0.5);
    break; 
  case 2:
    //Serial.print("Manaul Temp outside set mode");
    //Serial.println();
    TempOutside=TempOutsideManual;
    TempRadOutSet = int (kCurve*TempOutside+mCurve+0.5);
    break; 
  case 1:
    //Serial.print("Entering Temp radout set mode");
    //Serial.println();
    TempRadOutSet=TempRadManual;
    break; 
  case 0:
    //Serial.print("Entering automatic operation mode");
    //Serial.println();
    TempOutside=sensors.getTempC(outsideThermometer);
    TempRadOutSet = int (kCurve*TempOutside+mCurve+0.5);
    break; 
  }

  sensors.requestTemperatures();
  
  Iteration += 1;
  delay(DelayTime);
    
  TempRadOut=int (sensors.getTempC(radiatoroutThermometer)+0.5);
  Input = TempRadOut;
  //Tempcurve: TempRadOutSet=kCurve*TempOutside+mCurve

  
  double gap = abs(TempRadOutSet-Input); //distance away from TempRadOutSet
  if(gap<99)
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
//   SetValve += int(Output - LastOutput + 0.5);
   if(SetValve > 255) SetValve = 255;
   if(SetValve < 0) SetValve = 0;
   //LastOutput = Output;
   analogWrite(ValveControlPin,SetValve);

  //Debug printing
  //delay(20);
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  /*Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");*/

  // print the device information
  /*printData(radiatorinThermometer);
  printData(radiatoroutThermometer);
  printData(tapwaterThermometer);
  printData(outsideThermometer);
  Serial.print("Iteration: ");
  Serial.print(Iteration);
  Serial.println();
  Serial.print("TempsimVal: ");
  Serial.print(TempsimVal);
  Serial.println();*/
  //Serial.print("TempRadOut: ");
  //Serial.print(TempRadOut);
  //Serial.println();
  /*Serial.print("TempOutside: ");
  Serial.print(TempOutside);
  Serial.println();*/
  //Serial.print("TempRadOutSet: ");
  //Serial.print(TempRadOutSet);
  //Serial.println();
  //Serial.print("Output: ");
  //Serial.print(Output);
  //Serial.println();
  //Serial.print("Output - LastOutput: ");
  //Serial.print(Output-LastOutput);
  //Serial.println();
  //Serial.print("SetValve: ");
  //Serial.print(SetValve);
  //Serial.println();
  //Serial.println();
  LastOutput = Output;

  //Write to serial port
  Serial.write(0); //Tempoutside
  int temp;
  temp = TempRadOut*255.0/120.0+0.5;
  Serial.write(temp); //Temperature outside
  Serial.write(1); //Temp radin
  temp = 37.0*255.0/120.0+0.5;
  Serial.write(temp); //Temp radin
  Serial.write(2); //Temp radout
  temp = 40.0*255.0/120.0+0.5;
  Serial.write(temp); //Temp radout
  Serial.write(3); //Temp tapwater
  temp = 55.0*255.0/120.0+0.5;
  Serial.write(temp); //Temp tapwater
  Serial.write(4); //Temp radset
  temp = TempRadOutSet*255.0/120.0+0.5;
  Serial.write(temp); //Temp radset
  Serial.write(5); //Temp radset
  temp = (20.0+ SetValve/255.0*100.0)*255.0/120.0+0.5;
  Serial.write(temp); //Temp radset
  //delay(100);
}
