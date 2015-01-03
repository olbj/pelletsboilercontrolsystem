/*
 Fade
 
 This example shows how to fade an LED on pin 9
 using the analogWrite() function.
 
 This example code is in the public domain.
 */

int led = 9;           // the pin that the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 0;    // how many points to fade the LED by

int counter = 3;
const int buttonPin = 2;
int buttonState = 0;
int lastButtonState = 0;     // previous state of the button


// the setup routine runs once when you press reset:
void setup()  { 
  // declare pin 9 to be an output:
  pinMode(buttonPin, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
} 

// the loop routine runs over and over again forever:
void loop()  {
   buttonState = digitalRead(buttonPin);
   //Handle input
   if (buttonState != lastButtonState) {
   if(buttonState == HIGH)
   {
    counter++;
    //Reset count if over max mode number
    if(counter == 6)
      {
        counter = 1;
      }
    Serial.println("Button Pressed");
    Serial.print("number of button pushes:  ");
    Serial.println(counter);
    }
   } 
   lastButtonState = buttonState;
  //Change brightness
  if(counter == 1)
  {
     brightness = 0;
  }
  else if(counter == 2)
  {
     brightness = 64;
  }
  else if(counter == 3)
  {
     brightness = 128;
  }
  else if(counter == 4)
  {
     brightness = 196;
  }
  else if(counter == 5)
  {
     brightness = 255;
  }
  
  // set the brightness of pin 9:
  analogWrite(led, brightness);
}
