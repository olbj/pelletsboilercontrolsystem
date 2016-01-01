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
const int maxrows = 4;
const int maxcolumns = 3;
int menu_var = 0;
int menu_array[] = {0, 0};
int variable_array[maxrows+1][maxcolumns+1];
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

int MenuMove(int x, int y, boolean z)
{
  Serial.print("Enter MenuMove");
  Serial.println();
  Serial.print("maxcolumns: ");
  Serial.print(maxcolumns);
  Serial.print("   maxrows: ");
  Serial.print(maxrows);
  Serial.println();

  if (z == false && x != 0 && menu_array[1] + x >= 0 && menu_array[1] + x <= maxcolumns) menu_array[1] += x;
  if (z == false && y != 0 && menu_array[0] + y >= 0 && menu_array[0] + y <= maxrows) 
  {
    menu_array[0] += y;
    menu_array[1] = 0;
  }
  Serial.print("OldArray: ");
  Serial.print(menu_array[0]);
  Serial.print(".");
  Serial.print(menu_array[1]);
  Serial.print("=");
  Serial.print(variable_array[menu_array[0]][menu_array[1]]);
  Serial.println();
  if (z == true) variable_array[menu_array[0]][menu_array[1]] += x + y;
  Serial.println();
  Serial.print("NewArray: ");
  Serial.print(menu_array[0]);
  Serial.print(".");
  Serial.print(menu_array[1]);
  Serial.print("=");
  Serial.print(variable_array[menu_array[0]][menu_array[1]]);
  Serial.println();

}

void setup()
{
  Serial.begin(9600);
  Serial.print("MenuSketch Started");
  Serial.println();
  lcd.begin(16, 2);// start the library
  lcd.setCursor(0, 0);
  lcd.print("Push the buttons"); // print a simple message
}

void loop()
{
  lcd.setCursor(9, 1); // move cursor to second line "1" and 9 spaces over
  lcd.print(millis() / 1000); // display seconds elapsed since power-up
  lcd.setCursor(0, 1); // move to the begining of the second line
  lcd_key = read_LCD_buttons();// read the buttons
  switch (lcd_key)// depending on which button was pushed, we perform an action
  {
    case btnUP:
      {
        lcd.print("UP    ");
        if (lcd_key != last_lcd_key)
        {
          MenuMove(0, 1, menu_choice);
        }
        last_lcd_key = lcd_key;
      }
      break;
    case btnDOWN:
      {
        lcd.print("DOWN  ");
        if (lcd_key != last_lcd_key)
        {
          MenuMove(0, -1, menu_choice);
        }
        last_lcd_key = lcd_key;
      }
      break;
    case btnRIGHT:
      {
        lcd.print("RIGHT ");
        if (lcd_key != last_lcd_key)
        {
          MenuMove(1, 0, menu_choice);
        }
        last_lcd_key = lcd_key;
      }
      break;
    case btnLEFT:
      {
        lcd.print("LEFT  ");
        if (lcd_key != last_lcd_key)
        {
          MenuMove(-1, 0, menu_choice);
        }
        last_lcd_key = lcd_key;
      }
      break;
    case btnSELECT:
      {
        lcd.print("SELECT");
        if (lcd_key != last_lcd_key)
        {
          menu_choice = !menu_choice;
        }
        last_lcd_key = lcd_key;
      }
      break;
    case btnNONE:
      {
        lcd.setCursor(0, 0);
        lcd.print("Menu: "); // print a simple message
        lcd.print(menu_array[0]);
        lcd.print(".");
        lcd.print(menu_array[1]);
        lcd.print(" ");
        if (menu_choice == true)
          lcd.print(1);
        else
          lcd.print(0);
        lcd.print ("     ");
        lcd.setCursor(12, 0);
        lcd.print(variable_array[menu_array[0]][menu_array[1]]);
        lcd.setCursor(0, 1);
        lcd.print("NONE   ");
        last_lcd_key = lcd_key;
        // delay(1999);
      }
      break;
  }
  /*
  switch (lcd_key)// depending on which button was pushed, we perform an action
  {
  	case btnRIGHT:
  	{
  		lcd.print("RIGHT ");
  		if (lcd_key != last_lcd_key)
  		{
  		Serial.print("Right button pressed");
  		Serial.println();
  		Serial.print("New button pressed. Previous menu: ");
  		Serial.print(menu_array[0]);
  		Serial.print(".");
  		Serial.print(menu_array[1]);
  		Serial.print("   :");
  		Serial.println();
  		Serial.print(menu_choice[menu_array[0]][menu_array[1]]);
  			switch (menu_array[0])
  			{
  				case 0: //Menu 0.1-3
  				Serial.print("Menu 0.1-3");
  				Serial.println();
  				{
  					switch (menu_array[1])
  					{
  						case 0: {
  							Serial.print("Menu 0.0");
  							Serial.println();
  							new_menu_array[0]+=1;
  							if (new_menu_array[0]>2) 	new_menu_array[0]=0;
  							}
  							break;
  						case 1: {
  							Serial.print("Menu 0.1");
  							Serial.println();
  							new_menu_array[0]+=1;
  							if (new_menu_array[0]>2) 	new_menu_array[0]=0;
  							}
  							break;
  						case 2: {
  							Serial.print("Menu 0.2");
  							Serial.println();
  							new_menu_array[0]+=1;
  							if (new_menu_array[0]>2) 	new_menu_array[0]=0;
  							}
  							break;
  					}
  				}
  				break;
  				case 1: //Menu 1.1-3
  				Serial.print("Menu 1.1-3");
  				Serial.println();
  				{
  					switch (menu_array[1])
  					{
  						case 0: {
  							Serial.print("Menu 1.0");
  							Serial.println();
  							new_menu_array[0]+=1;
  							if (new_menu_array[0]>2) 	new_menu_array[0]=0;
  							}
  							break;
  						case 1: {
  							Serial.print("Menu 1.1");
  							Serial.println();
  							new_menu_array[0]+=1;
  							if (new_menu_array[0]>2) 	new_menu_array[0]=0;
  							}
  							break;
  						case 2: {
  							Serial.print("Menu 1.2");
  							Serial.println();
  							new_menu_array[0]+=1;
  							if (new_menu_array[0]>2) 	new_menu_array[0]=0;
  							}
  							break;
  					}
  				}
  				break;
  				case 2: //Menu 2.1-3
  				Serial.print("Menu 2.1-3");
  				Serial.println();
  				{
  					switch (menu_array[1])
  					{
  						case 0: {
  							Serial.print("Menu 2.0");
  							Serial.println();
  							new_menu_array[0]+=1;
  							if (new_menu_array[0]>2) 	new_menu_array[0]=0;
  							}
  							break;
  						case 1: {
  							Serial.print("Menu 2.1");
  							Serial.println();
  							new_menu_array[0]+=1;
  							if (new_menu_array[0]>2) 	new_menu_array[0]=0;
  							}
  							break;
  						case 2: {
  							Serial.print("Menu 2.2");
  							Serial.println();
  							new_menu_array[0]+=1;
  							if (new_menu_array[0]>2) 	new_menu_array[0]=0;
  							}
  							break;
  					}
  				}
  				break;
  			}
  		}
  		last_lcd_key=lcd_key;
  	}
  	break;
  	case btnLEFT:
  	{
  		lcd.print("LEFT ");
  		if (lcd_key != last_lcd_key)
  		{
  			switch (menu_array[0])
  			{
  				case 0: //Menu 0.1-3
  				{
  					switch (menu_array[1])
  					{
  						case 0: {
  							menu_array[0]-=1;
  							if (menu_array[0]<0) 	menu_array[0]=2;
  							}
  							break;
  						case 1: {
  							menu_array[0]-=1;
  							if (menu_array[0]<0) 	menu_array[0]=2;
  							}
  							break;
  						case 2: {
  							menu_array[0]-=1;
  							if (menu_array[0]<0) 	menu_array[0]=2;
  							}
  							break;
  					}
  				}
  				break;
  				case 1: //Menu 1.1-3
  				{
  					switch (menu_array[1])
  					{
  						case 0: {
  							menu_array[0]-=1;
  							if (menu_array[0]<0) 	menu_array[0]=2;
  							}
  							break;
  						case 1: {
  							menu_array[0]-=1;
  							if (menu_array[0]<0) 	menu_array[0]=2;
  							}
  							break;
  						case 2: {
  							menu_array[0]-=1;
  							if (menu_array[0]<0) 	menu_array[0]=2;
  							}
  							break;
  					}
  				}
  				break;
  				case 2: //Menu 2.1-3
  				{
  					switch (menu_array[1])
  					{
  						case 0: {
  							menu_array[0]-=1;
  							if (menu_array[0]<0) 	menu_array[0]=2;
  							}
  							break;
  						case 1: {
  							menu_array[0]-=1;
  							if (menu_array[0]<0) 	menu_array[0]=2;
  							}
  							break;
  						case 2: {
  							menu_array[0]-=1;
  							if (menu_array[0]<0) 	menu_array[0]=2;
  							}
  							break;
  					}
  				}
  				break;
  			}
  		}
  		last_lcd_key=lcd_key;
  	}
  	break;
  	case btnUP:
  	{
  		lcd.print("UP    ");
  		if (lcd_key != last_lcd_key)
  		{
  			switch (menu_array[0])
  			{
  				case 0: //Menu 0.1-3
  				{
  					switch (menu_array[1])
  					{
  						case 0: {
  							menu_array[1]-=1;
  							if (menu_array[1]<0) 	menu_array[1]=2;
  							}
  							break;
  						case 1: {
  							menu_array[1]-=1;
  							if (menu_array[1]<0) 	menu_array[1]=2;
  							}
  							break;
  						case 2: {
  							menu_array[1]-=1;
  							if (menu_array[1]<0) 	menu_array[1]=2;
  							}
  							break;
  					}
  				}
  				break;
  				case 1: //Menu 1.1-3
  				{
  					switch (menu_array[1])
  					{
  						case 0: {
  							menu_array[1]-=1;
  							if (menu_array[1]<0) 	menu_array[1]=2;
  							}
  							break;
  						case 1: {
  							menu_array[1]-=1;
  							if (menu_array[1]<0) 	menu_array[1]=2;
  							}
  							break;
  						case 2: {
  							menu_array[1]-=1;
  							if (menu_array[1]<0) 	menu_array[1]=2;
  							}
  							break;
  					}
  				}
  				break;
  				case 2: //Menu 2.1-3
  				{
  					switch (menu_array[1])
  					{
  						case 0: {
  							menu_array[1]-=1;
  							if (menu_array[1]<0) 	menu_array[1]=2;
  							}
  							break;
  						case 1: {
  							menu_array[1]-=1;
  							if (menu_array[1]<0) 	menu_array[1]=2;
  							}
  							break;
  						case 2: {
  							menu_array[1]-=1;
  							if (menu_array[1]<0 ) 	menu_array[1]=2;
  							}
  							break;
  					}
  				}
  				break;
  			}
  		}
  		last_lcd_key=lcd_key;
  	}
  	break;
  	case btnDOWN:
  	{
  		lcd.print("DOWN  ");
  		if (lcd_key != last_lcd_key)
  		{
  			switch (menu_array[0])
  			{
  				case 0: //Menu 0.1-3
  				{
  					switch (menu_array[1])
  					{
  						case 0: {
  							menu_array[1]+=1;
  							if (menu_array[1]>2 ) 	menu_array[1]=0;
  							}
  						break;
  						case 1: {
  							menu_array[1]+=1;
  							if (menu_array[1]>2 ) 	menu_array[1]=0;
  							}
  						break;
  						case 2: {
  							menu_array[1]+=1;
  							if (menu_array[1]>2 ) 	menu_array[1]=0;
  							}
  						break;
  					}
  				}
  				break;
  				case 1: //Menu 1.1-3
  				{
  					switch (menu_array[1])
  					{
  						case 0: {
  							menu_array[1]+=1;
  							if (menu_array[1]>2 ) 	menu_array[1]=0;
  							}
  						break;
  						case 1: {
  							menu_array[1]+=1;
  							if (menu_array[1]>2 ) 	menu_array[1]=0;
  							}
  						break;
  						case 2: {
  							menu_array[1]+=1;
  							if (menu_array[1]>2 ) 	menu_array[1]=0;
  							}
  						break;
  					}
  				}
  				break;
  				case 2: //Menu 2.1-3
  				{
  					switch (menu_array[1])
  					{
  						case 0: {
  							menu_array[1]+=1;
  							if (menu_array[1]>2 ) 	menu_array[1]=0;
  							}
  						break;
  						case 1: {
  							menu_array[1]+=1;
  							if (menu_array[1]>2 ) 	menu_array[1]=0;
  							}
  						break;
  						case 2: {
  							menu_array[1]+=1;
  							if (menu_array[1]>2 ) 	menu_array[1]=0;
  							}
  						break;
  					}
  				}
  				break;
  			}
  		}
  		last_lcd_key=lcd_key;
  	}
  	break;
  	case btnSELECT:
  	{
  		lcd.print("SELECT");
  		if (lcd_key != last_lcd_key)
  		{
  			switch (menu_array[0])
  			{
  				case 0: //Menu 0.1-3
  				{
  					switch (menu_array[1])
  					{
  						case 0:
  							{
  							menu_choice[menu_array[0]][menu_array[1]] = !menu_choice[menu_array[0]][menu_array[1]];
  							Serial.print(menu_choice[menu_array[0]][menu_array[1]]);
  							Serial.println();
  							}
  						break;
  						case 1:
  							{
  							menu_choice[menu_array[0]][menu_array[1]] = !menu_choice[menu_array[0]][menu_array[1]];
  							Serial.print(menu_choice[menu_array[0]][menu_array[1]]);
  							Serial.println();
  							}
  						break;
  						case 2:
  							{
  							menu_choice[menu_array[0]][menu_array[1]] = !menu_choice[menu_array[0]][menu_array[1]];
  							Serial.print(menu_choice[menu_array[0]][menu_array[1]]);
  							Serial.println();
  							}
  						break;
  					}
  				}
  				break;
  				case 1: //Menu 1.1-3
  				{
  					switch (menu_array[1])
  					{
  						case 0:
  							{
  							menu_choice[menu_array[0]][menu_array[1]] = !menu_choice[menu_array[0]][menu_array[1]];
  							Serial.print(menu_choice[menu_array[0]][menu_array[1]]);
  							Serial.println();
  							}
  						break;
  						case 1:
  							{
  							menu_choice[menu_array[0]][menu_array[1]] = !menu_choice[menu_array[0]][menu_array[1]];
  							Serial.print(menu_choice[menu_array[0]][menu_array[1]]);
  							Serial.println();
  							}
  						break;
  						case 2:
  							{
  							menu_choice[menu_array[0]][menu_array[1]] = !menu_choice[menu_array[0]][menu_array[1]];
  							Serial.print(menu_choice[menu_array[0]][menu_array[1]]);
  							Serial.println();
  							}
  						break;
  					}
  				}
  				break;
  				case 2: //Menu 2.1-3
  				{
  					switch (menu_array[1])
  					{
  						case 0:
  							{
  							menu_choice[menu_array[0]][menu_array[1]] = !menu_choice[menu_array[0]][menu_array[1]];
  							Serial.print(menu_choice[menu_array[0]][menu_array[1]]);
  							Serial.println();
  							}
  						break;
  						case 1:
  							{
  							menu_choice[menu_array[0]][menu_array[1]] = !menu_choice[menu_array[0]][menu_array[1]];
  							Serial.print(menu_choice[menu_array[0]][menu_array[1]]);
  							Serial.println();
  							}
  						break;
  						case 2:
  							{
  							menu_choice[menu_array[0]][menu_array[1]] = !menu_choice[menu_array[0]][menu_array[1]];
  							Serial.print(menu_choice[menu_array[0]][menu_array[1]]);
  							Serial.println();
  							}
  						break;
  					}
  				}
  				break;
  			}
  		}
  		last_lcd_key=lcd_key;
  	}


  	break;
  	case btnNONE:
  	{
  		menu_array[0]=new_menu_array[0];
  		menu_array[1]=new_menu_array[1];
  		lcd.setCursor(0,0);
  		lcd.print("Menu: "); // print a simple message
  		lcd.print(menu_array[0]);
  		lcd.print(".");
  		lcd.print(menu_array[1]);
  		lcd.print(" ");
  		lcd.print(menu_choice[menu_array[0]][menu_array[1]]);
  		lcd.print("                ");
  		lcd.setCursor(0,1);
  		lcd.print("NONE   ");
  		last_lcd_key=lcd_key;
  		// delay(1999);
  	}
  	break;
  }
  */
}
