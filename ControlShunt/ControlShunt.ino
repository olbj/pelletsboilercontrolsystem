/**************************************************************************************
  PID Adaptive radiator temperature control system
  
  Version 4.0 21-12-27
  
  Code made by Olof Björkqvist (olof@bjorkqvist.nu)
  Code sources: PID Example codes for DallasTemperature and AutoPID libraries
  
  Copyright (C) 2021  Olof Björkqvist <olof@bjorkqvist.nu>

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
**************************************************************************************/

#include <OneWire.h>
#include <DallasTemperature.h>
#include <AFMotor.h>
#include <AutoPID.h>


// Section Variables
// ****************
const double radiatorinTempMin=17, radiatoroutTempMax=80, outsideTempMin=-24, outsideTempManual=-5;

double setPoint = 50, outputVal = 0; //Setpoint temperature
double radiatoroutTempManual=55; // Manual radiator temperature setpoint for debug purpose
double radiatorinTemp = 20, radiatoroutTemp = 30, outsideTemp = -10; //21-12-26 outsideTemp not implemented

double kCurve=0, mCurve=0; // 21-12-26 Temperature curve not implemented
// 21-12-27 Stable and conservative values double Kp = 6.0, Ki = 0.6, Kd = 3.0;
double Kp = 10.0, Ki = 0.3, Kd = 6.0;
const double output_min=0, output_max=230;
const int temp_read_delay=800;
unsigned long lastTempUpdate; //tracks clock time of last temp update

// arrays to hold device addresses
//DeviceAddress radiatorinTempSensor, radiatoroutTempSensor, outsideTempSensor;
DeviceAddress radiatorinTempSensor = { 0x28, 0xBD, 0x20, 0x7A, 0x05, 0x00, 0x00, 0x2D }; //Yellow
DeviceAddress radiatoroutTempSensor = { 0x28, 0x17, 0xC1, 0x47, 0x05, 0x00, 0x00, 0x7C }; //Green
DeviceAddress outsideTempSensor = { 0x28, 0xEF, 0xEA, 0x46, 0x05, 0x00, 0x00, 0xA8 }; //Red
// Section Variables end

// Section Temperature sensors (assmuing three sensors atatched)
// *************************************************************
// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
#define TEMPERATURE_PRECISION 9 // Lower resolution
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
//Section Temperature Sensors End

// Section Motor Shield
// ********************
AF_DCMotor motor(1);
// Section Motor Shield end

// Section PID init
// *****************
AutoPID myPID(&radiatoroutTemp, &setPoint, &outputVal, output_min, output_max, Kp, Ki, Kd);
// Section PID init end

void setup(void)
{
  Serial.begin(9600);
  
  // Section Temperature sensors
  // ***************************
  // start serial port
  Serial.println("Dallas Temperature IC Control Library Setup");

  // Section Temperature sensors
  // ***************************
  // Start up the library
  sensors.begin();
  sensors.setResolution(radiatorinTempSensor, TEMPERATURE_PRECISION);
  sensors.setResolution(radiatoroutTempSensor, TEMPERATURE_PRECISION);
  sensors.setResolution(outsideTempSensor, TEMPERATURE_PRECISION);
  // Section Temperature sensors end

  // Section Motor Shield
  // ********************
  Serial.println("Motor test!");
  // turn on motor
  motor.setSpeed(128);
  motor.run(BACKWARD); //Make shure that the polarity is correct.
  // Section Motor Shield end

  // Section PID
  // ***********
  //if temperature is more than 4 degrees below or above setpoint, OUTPUT will be set to min or max respectively
  myPID.setBangBang(40);
  //set PID update interval to 4000ms
  myPID.setTimeStep(4000);
  // Section PID end

// setup end
}

void loop(void)
{
    // Read temperature sensors if after specified delay
    if ((millis() - lastTempUpdate) > temp_read_delay) {
    radiatoroutTemp = sensors.getTempC(radiatoroutTempSensor); //get temp reading
    lastTempUpdate = millis();
    sensors.requestTemperatures(); //request reading for next time
  }
  
  int sensorValue = analogRead(A2);
  //radiatoroutTemp = sensorValue*(85.0-20.0) / 1023.0+20.0;
  //Kp = sensorValue* 50.0 / 1023.0 +0.0;
  //Ki = sensorValue* 2.0 / 1023.0 +0.0;
  //Kd = sensorValue* 10.0 / 1023.0 +0.0;
  //myPID.setGains(Kp, Ki, Kd);
  setPoint = radiatoroutTempManual; //Manual setpoint specified in definition
  myPID.run();
  motor.setSpeed(outputVal);
  
  Serial.print("Output from PID: Setpoint=");
  Serial.print(radiatoroutTempManual);
  Serial.print("°C Value=");
  Serial.print(radiatoroutTemp);
  Serial.print("°C Output=");
  Serial.print(outputVal);
  Serial.print(" Target=");
  Serial.print(myPID.atSetPoint(2));
  Serial.print(" Kp=");
  Serial.print(Kp);
  Serial.print(" Ki=");
  Serial.print(Ki);
  Serial.print(" Kd=");
  Serial.print(Kd);
  Serial.println();

// loop end
}





// ****************
// Functions section
// *****************

// function to print a device address (from tester example in DallasTemperature examples)
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
