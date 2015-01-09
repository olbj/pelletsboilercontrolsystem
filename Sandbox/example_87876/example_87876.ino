// 87876 LCD Shield för Arduino
// 16x2 tecken och knappar
// Kjell & Company 

// include the library code:
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);   // initialize the library with the numbers of the interface pins

void setup() {
  lcd.begin(16, 2);                      // set up the LCD's number of columns and rows
  lcd.clear();                           // Clear LCD
  lcd.setCursor(0,0);                    // Set cursor to x=0 and y=0
  lcd.print("LCD Key Shield");           // Print text on LCD
  lcd.setCursor(0,1);
  lcd.print("Olof Bjorkqvist");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press any Key:");
}

void loop() { 
  int x;
  x = analogRead (0);                  // Read the analog value for buttons
  if (x < 100) {                       // Right button is pressed
    lcd.setCursor(0,0);
    lcd.print (x); 
    lcd.setCursor(0,1);
    lcd.print ("Right "); 
  }
  else if (x < 200) {                  // Up button is pressed
    lcd.setCursor(0,0);
    lcd.print (x); 
    lcd.setCursor(0,1);
    lcd.print ("Up    ");
  }
  else if (x < 400){                   // Down button is pressed
    lcd.setCursor(0,0);
    lcd.print (x); 
    lcd.setCursor(0,1);
    lcd.print ("Down  "); 
  }
  else if (x < 600){                   // Left button is pressed
    lcd.setCursor(0,0);
    lcd.print (x); 
    lcd.setCursor(0,1);
    lcd.print ("Left  ");
  }
  else if (x < 800){                   // Select button is pressed
    lcd.setCursor(0,0);
    lcd.print (x); 
    lcd.setCursor(0,1);
    lcd.print ("Select"); }
}
