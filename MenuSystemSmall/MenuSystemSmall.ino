//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

/*******************************************************

This program will test the LCD panel and the buttons
Mark Bramwell, July 2010
Program  modified to build a menu sysem by Olof Björkqvist
olof@bjorkqvist.nu
2016

********************************************************/

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key = 0;
int last_lcd_key = 0;
int adc_key_in = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
int c[2]; //cursor position.


//Define the menu array
const byte rows = 5; //Max row in menu systems
const byte size[rows] = {2, 2, 3, 4, 6}; //Max columns in rows
char row0[2]; //Operations mode
byte row1[2]; //Information mode
byte row2[3]; //Setup mode
byte row3[4]; //Temperature setup
byte row4[6]; //PID setup

// read the buttons
int read_LCD_buttons()
{
  adc_key_in = analogRead(0);// read the value from the sensor
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  // For V1.1 us this threshold
  /*
  if (adc_key_in < 50)return btnRIGHT;
  if (adc_key_in < 250)return btnUP;
  if (adc_key_in < 450)return btnDOWN;
  if (adc_key_in < 650)return btnLEFT;
  if (adc_key_in < 850)return btnSELECT;
  */
  // For V1.0 comment the other threshold and use the one below:

  if (adc_key_in < 50)return btnRIGHT;
  if (adc_key_in < 195)return btnUP;
  if (adc_key_in < 380)return btnDOWN;
  if (adc_key_in < 555)return btnLEFT;
  if (adc_key_in < 790)return btnSELECT;



  return btnNONE;// when all others fail, return this...
}

void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.print("MenuSystemSmall Started: ");
  Serial.println();
  lcd.begin(16, 2);// start the library
  lcd.setCursor(0, 0);
  lcd.print("Push the buttons"); // print a simple message
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("                "); // print a simple message
  lcd.setCursor(0, 1);
  lcd.print("Row   Column");
  
}

void UpdateSetup()
{
  Serial.print("Updates setup ...  ");
  Serial.println();
  /*
    RunMode         =      variable_array[0][1][0] *int(multiplier_array[0][1][0]);
    TempOutsideMin  =float(variable_array[2][1][1]) *   multiplier_array[2][1][1]
    TempRadOutMax   =float(variable_array[2][1][2]) *   multiplier_array[2][1][2];
    TempRadOutMin   =float(variable_array[2][1][3]) *   multiplier_array[2][1][3];
    TempManual      =float(variable_array[2][1][4]) *   multiplier_array[2][1][4];
    consKp          =float(variable_array[2][2][1]) *   multiplier_array[2][2][1];
    consKi          =float(variable_array[2][2][2]) *   multiplier_array[2][2][2];
    consKd          =float(variable_array[2][2][3]) *   multiplier_array[2][2][3];
    aggKp           =float(variable_array[2][3][1]) *   multiplier_array[2][3][1];
    aggKi           =float(variable_array[2][3][2]) *   multiplier_array[2][3][2];
    aggKd           =float(variable_array[2][3][3]) *   multiplier_array[2][3][3];*/
}

void loop()
{
  int x = 0; //column
  int y = 0; //row
  int z = 0; //height
  int setting = 0;
  //Serial.print("Start of loop: ");
  //Serial.println();

  lcd_key = read_LCD_buttons();// read the buttons
  lcd.setCursor(0, 0);
  switch (lcd_key)
  {
    case btnUP:
      {
        lcd.print("UP    ");
        if (lcd_key != last_lcd_key)
          y = 1;
      }
      break;
    case btnDOWN:
      {
        lcd.print("DOWN  ");
        if (lcd_key != last_lcd_key)
          y = -1;
      }
      break;
    case btnRIGHT:
      {
        lcd.print("RIGHT ");
        if (lcd_key != last_lcd_key)
          { x = 1;
            Serial.println();
            Serial.print(x);
            Serial.print(": ");
            Serial.print(c[1]);
          }
      }
      break;
    case btnLEFT:
      {
        lcd.print("LEFT  ");
        if (lcd_key != last_lcd_key)
          { x = -1;
            Serial.println();
            Serial.print(x);
            Serial.print(": ");
            Serial.print(c[1]);
          }
      }
      break;
    case btnSELECT:
      {
        lcd.print("SELECT");
        if (lcd_key != last_lcd_key)
        {
          //menu_choice = !menu_choice;
          //if (menu_choice == false) UpdateSetup();
          //if (menu_array[2] > 0) menu_array[2] = 0;
        }
      }
      break;
    case btnNONE:
      {
        lcd.print("NONE  ");
      }
      break;
  } //end of lcd_key switch

  // First, is it possible to change row?
  if (y != 0 && c[0]+y >= 0 &&  c[0]+y <= rows -1) 
  {  
    c[0] += y; 
    c[1]=0;
  }
  // Second, is it possible to change column?
  if (c[1]+x >= 0 && c[1]+x <= size[c[0]]) c[1] += x; 

  // Debug print to LCD display
  lcd.setCursor(4, 1);
  lcd.print(c[0]);
  lcd.setCursor(13, 1);
  lcd.print(c[1]);

  last_lcd_key = lcd_key;

  // delay(1999);
}
