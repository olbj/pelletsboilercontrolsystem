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
#define btnRIGHT	0
#define btnUP			1
#define btnDOWN		2
#define btnLEFT		3
#define btnSELECT	4
#define btnNONE		5

//Define the menu array
const int maxrows = 3;
const int maxcolumns = 4;
const int maxdepth = 5;
int menu_var = 0;
int menu_array[] = {0, 0, 0};
//int variable_array[maxrows][maxcolumns];
int variable_array[maxrows][maxcolumns][maxdepth];
float multiplier_array[maxrows][maxcolumns][maxdepth];

char* title_array[maxrows][maxcolumns][maxdepth];
boolean menu_choice = false;

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
  Serial.print("MenuSketch Started");
  Serial.println();
  lcd.begin(16, 2);// start the library
  lcd.setCursor(0, 0);
  lcd.print("Push the buttons"); // print a simple message
  for (int y=0; y<maxrows; y++)
    for (int x=0; x<maxcolumns; x++)
      for (int z=0; z<maxcolumns; z++)
      {
        title_array[y][x][z] = "-";
        multiplier_array[y][x][z] = 0;
        Serial.print("Title: ");
        Serial.print(y);
        Serial.print(".");
        Serial.print(x);
        Serial.print(".");
        Serial.print(z);
        Serial.print("=");
        Serial.print(title_array[y][x][z]);
        Serial.println();
      }
  title_array[0][0][0] = "Operation Mode";
  title_array[0][1][0] = "Auto, Man, Off";
  multiplier_array[0][1][0] = 1;
  //variable_array[0][1][0] = RunMode;
  title_array[1][0][0] = "Information Mode";
  title_array[1][1][0] = "Temperatures";
  title_array[1][2][0] = "Pellets";
  title_array[1][3][0] = "PID";
  title_array[2][0][0] = "Setup Mode";
  title_array[2][1][0] = "Temp. curve";
  title_array[2][1][1] = "T-min outside";
  multiplier_array[2][1][1] = 1;
  //variable_array[2][1][1] = TempOutsideMin;
  title_array[2][1][2] = "T-max radiator";
  multiplier_array[2][1][2] = 1;
  //variable_array[2][1][2] = TempRadOutMax;
  title_array[2][1][3] = "T-min radiator";
  multiplier_array[2][1][3] = 1;
  //variable_array[2][1][3] = TempRadOutMin;
  title_array[2][1][4] = "T-manual";
  multiplier_array[2][1][4] = 1;
  //variable_array[2][1][4] = TempManual;
  title_array[2][2][0] = "PID conservative";
  title_array[2][2][1] = "consKp";
  multiplier_array[2][2][1] = 1.0/100.0;
  title_array[2][2][2] = "consKi";
  multiplier_array[2][2][2] = 1.0/100.0;
  title_array[2][2][3] = "consKd";
  multiplier_array[2][2][3] = 1.0/100.0;
  title_array[2][3][0] = "PID aggresive";
  title_array[2][3][1] = "aggKp";
  multiplier_array[2][3][1] = 1.0/100.0;
  title_array[2][3][2] = "aggKi";
  multiplier_array[2][3][2] = 1.0/100.0;
  title_array[2][3][3] = "aggKd";
  multiplier_array[2][3][3] = 1.0/100.0;
       for (int y=0; y<maxrows; y++)
    for (int x=0; x<maxcolumns; x++)
      for (int z=0; z<maxcolumns; z++)
      {
        Serial.print("Title: ");
        Serial.print(y);
        Serial.print(".");
        Serial.print(x);
        Serial.print(".");
        Serial.print(z);
        Serial.print("=");
        Serial.print(title_array[y][x][z]);
        Serial.println();
     }
}

void UpdateSetup()
{
  Serial.print("Updates setup ...  ");
  Serial.print(menu_choice);
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
  int x = 0;
  int y = 0;
  int z = 0;
  Serial.print("Start of loop:");
    Serial.print(menu_array[0]);
    Serial.print(".");
    Serial.print(menu_array[1]);
    Serial.print(".");
    Serial.print(menu_array[2]);
    Serial.println();
  /*lcd.setCursor(9, 1); // move cursor to second line "1" and 9 spaces over
  lcd.print(millis() / 1000); // display seconds elapsed since power-up
  lcd.setCursor(0, 1); // move to the begining of the second line*/
  lcd_key = read_LCD_buttons();// read the buttons
    switch (lcd_key)
    {
      case btnUP:
      {
        //lcd.print("UP    ");
        if (lcd_key != last_lcd_key)
        y=1;
      }
      break;
      case btnDOWN:
      {
        //lcd.print("DOWN  ");
        if (lcd_key != last_lcd_key)
        y=-1;
      }
      break;
      case btnRIGHT:
      {
        //lcd.print("RIGHT ");
        if (lcd_key != last_lcd_key)
        x=1;
      }
      break;
      case btnLEFT:
      {
        //lcd.print("LEFT  ");
        if (lcd_key != last_lcd_key)
        x=-1;
      }
      break;
      case btnSELECT:
      {
        //lcd.print("SELECT");
        if (lcd_key != last_lcd_key)
        {
          menu_choice = !menu_choice;
          if (menu_choice == false) UpdateSetup();
          if (menu_array[2] > 0) menu_array[2] = 0;
        }
      }
      break;
      case btnNONE:
      {
        //lcd.print("NONE  ");
      }
      break;
    }
    if (menu_choice == false)
    {
      if (menu_array[1] + x < maxcolumns && menu_array[1] + x >= 0 && 
      title_array[menu_array[0]][menu_array[1]+x][menu_array[2]] != "-") 
      menu_array[1] += x;
      if (y != 0 && menu_array[0] + y < maxrows && menu_array[0] + y >= 0) 
      {
        menu_array[0] += y;
        menu_array[1]=0;
      }
    }
    else
    {
      if (multiplier_array[menu_array[0]][menu_array[1]][menu_array[2]] == 0)
      {
        if (menu_array[2]  + x < maxdepth && menu_array[2]  + x >= 0 &&
        title_array[menu_array[0]][menu_array[1]][menu_array[2]+x] != "-") 
        {
          menu_array[2] += x;
          //menu_choice = !menu_choice;
        }
      }
      else
      {
        if (menu_array[2]  + x < maxdepth && menu_array[2]  + x >= 0 && 
        title_array[menu_array[0]][menu_array[1]][menu_array[2]+x] != "-") 
        menu_array[2] += x;
        variable_array[menu_array[0]][menu_array[1]][menu_array[2]] += y;
      }

    }
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    //lcd.print("Menu: "); // print a simple message
    lcd.print(variable_array[menu_array[0]][menu_array[1]][menu_array[2]]);
    lcd.setCursor(4, 1);
    lcd.print(menu_array[0]);
    lcd.print(".");
    lcd.print(menu_array[1]);
    lcd.print(".");
    lcd.print(menu_array[2]);
    lcd.print("-");
    if (menu_choice == true)
      lcd.print(1);
    else
    lcd.print(0);
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(title_array[menu_array[0]][menu_array[1]][menu_array[2]]);
    last_lcd_key = lcd_key; 
    
    // delay(1999);
}
