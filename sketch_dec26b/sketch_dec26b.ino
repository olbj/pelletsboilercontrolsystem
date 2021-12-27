#include <Servo.h>
#include <AFMotor.h>

int MotorSpeed = 254;


AF_DCMotor motor(3);
void setup() {
Serial.begin(9600); // set up Serial library at 9600 bps
Serial.println("Motor test!");
// turn on motor
motor.setSpeed(MotorSpeed);
motor.run(RELEASE);
}

void loop() {
motor.run(FORWARD);
motor.setSpeed(MotorSpeed);

Serial.println("Enter motor speed! ");        //Prompt User for input
while (Serial.available()==0){}             // wait for user input
MotorSpeed = Serial.parseInt(SKIP_ALL, '\n');                    //Read user input and hold it in a variable
 
// Print well formatted output
Serial.print("Motor Speed ");                 
Serial.print(MotorSpeed);
Serial.println(" of 255.");

}
