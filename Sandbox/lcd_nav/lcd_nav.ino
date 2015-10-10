/*
 * lcd_nav.ino - Example code using the menu system library
 *
 * This example shows using the menu system with a 16x2 LCD display
 * (controled over serial).
 *
 * Copyright (c) 2015 arduino-menusystem
 * Licensed under the MIT license (see LICENSE)
 */

#include <MenuSystem.h>
#include <LiquidCrystal.h>

// Menu variables
MenuSystem ms;
Menu mm("ROOT Menu Title");
MenuItem mm_mi1("1.1");
MenuItem mm_mi2("1.2");
MenuItem mm_mi3("1.3");
Menu mu1("Menu 3");
MenuItem mu1_mi1("3.1");
MenuItem mu1_mi2("3.2");
MenuItem mu1_mi3("3.3");
MenuItem mu1_mi4("3.4");
MenuItem mm_mi4("1.4");
Menu mu2("Menu 4");
MenuItem mu2_mi1("4.1");
MenuItem mu2_mi2("4.2");
MenuItem mu2_mi3("4.3");
MenuItem mu2_mi4("4.4");


// Button variables
int lcd_key= 0;
int last_lcd_key = 0;
int adc_key_in= 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

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

/*
The LCD circuit:
 * LCD RS pin to digital pin 8
 * LCD Enable pin to digital pin 9
 * LCD D4 pin to digital pin 4
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 7
 * LCD R/W pin to ground
 */
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8     ,     9 ,      4 ,      5 ,      6 ,      7 );

// Menu callback function
// In this example all menu items use the same callback.

void on_1_1_selected(MenuItem* p_menu_item)
{
  lcd.setCursor(0,1);
  lcd.print("1.1 Selected  ");
  delay(1500); // so we can look the result on the LCD
}

void on_1_2_selected(MenuItem* p_menu_item)
{
  lcd.setCursor(0,1);
  lcd.print("1.2 Selected  ");
  delay(1500); // so we can look the result on the LCD
}

void on_1_3_selected(MenuItem* p_menu_item)
{
  lcd.setCursor(0,1);
  lcd.print("1.3 Selected  ");
  delay(1500); // so we can look the result on the LCD
}

void on_3_1_selected(MenuItem* p_menu_item)
{
  lcd.setCursor(0,1);
  lcd.print("3.1 Selected  ");
  delay(1500); // so we can look the result on the LCD
}

void on_3_2_selected(MenuItem* p_menu_item)
{
  lcd.setCursor(0,1);
  lcd.print("3.2 Selected  ");
  delay(1500); // so we can look the result on the LCD
}

void on_3_3_selected(MenuItem* p_menu_item)
{
  lcd.setCursor(0,1);
  lcd.print("3.3 Selected  ");
  delay(1500); // so we can look the result on the LCD
}

void on_3_4_selected(MenuItem* p_menu_item)
{
  lcd.setCursor(0,1);
  lcd.print("3.4 Selected  ");
  delay(1500); // so we can look the result on the LCD
}

void on_1_4_selected(MenuItem* p_menu_item)
{
  lcd.setCursor(0,1);
  lcd.print("1.4 Selected  ");
  delay(1500); // so we can look the result on the LCD
}

void on_4_1_selected(MenuItem* p_menu_item)
{
  lcd.setCursor(0,1);
  lcd.print("4.1 Selected  ");
  delay(1500); // so we can look the result on the LCD
}

void on_4_2_selected(MenuItem* p_menu_item)
{
  lcd.setCursor(0,1);
  lcd.print("4.2 Selected  ");
  delay(1500); // so we can look the result on the LCD
}

void on_4_3_selected(MenuItem* p_menu_item)
{
  lcd.setCursor(0,1);
  lcd.print("4.3 Selected  ");
  delay(1500); // so we can look the result on the LCD
}

void on_4_4_selected(MenuItem* p_menu_item)
{
  lcd.setCursor(0,1);
  lcd.print("4.4 Selected  ");
  delay(1500); // so we can look the result on the LCD
}

// Standard arduino functions

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  serialPrintHelp();
  Serial.println("Setting up the menu.");
  // Menu setup
  /*
  Menu Structure:
   -Item1
   -Item2
   -Item3
   --Item1
   
   */
  mm.add_item(&mm_mi1, &on_1_1_selected);
  mm.add_item(&mm_mi2, &on_1_2_selected);
  mm.add_item(&mm_mi3, &on_1_3_selected);
  mm.add_menu(&mu1);
  mu1.add_item(&mu1_mi1, &on_3_1_selected);
  mu1.add_item(&mu1_mi2, &on_3_2_selected);
  mu1.add_item(&mu1_mi3, &on_3_3_selected);
  mu1.add_item(&mu1_mi4, &on_3_4_selected);
  mm.add_item(&mm_mi4, &on_1_4_selected);
  mm.add_menu(&mu2);
  mu2.add_item(&mu2_mi1, &on_4_1_selected);
  mu2.add_item(&mu2_mi2, &on_4_2_selected);
  mu2.add_item(&mu2_mi3, &on_4_3_selected);
  mu2.add_item(&mu2_mi4, &on_4_4_selected);
  ms.set_root_menu(&mm);
  Serial.println("Menu setted.");
  displayMenu();
}

void loop()
{
  // Handle serial commands
  serialHandler();

  // Wait for two seconds so the output is viewable
  //delay(2000);
}

void displayMenu() {
  lcd.clear();
  lcd.setCursor(0,0);
  // Display the menu
  Menu const* cp_menu = ms.get_current_menu();

  //lcd.print("Current menu name: ");
  lcd.print(cp_menu->get_name());
  
  lcd.setCursor(0,1);
  
  lcd.print(cp_menu->get_selected()->get_name());
}

void selectMenu() {
  if (1 == 1) {
  //if((inChar = Serial.read())>0) {
  //switch (adc_key_in) {
    lcd_key = read_LCD_buttons();// read the buttons
    switch (lcd_key)// depending on which button was pushed, we perform an action
    {
    case btnLEFT: // Previus item
      if (lcd_key != last_lcd_key) {
      ms.prev();
      displayMenu(); }
      last_lcd_key=lcd_key;
      break;
    case btnRIGHT: // Next item
      if (lcd_key != last_lcd_key) {
      ms.next();
      displayMenu(); }
      last_lcd_key=lcd_key;
      break;
    case btnUP: // Back presed
      if (lcd_key != last_lcd_key) {
      ms.back();
      displayMenu(); }
      last_lcd_key=lcd_key;
      break;
    case btnSELECT: // Select presed
      if (lcd_key != last_lcd_key) {
      ms.select();
      displayMenu(); }
      last_lcd_key=lcd_key;
      break;
    case btnDOWN: // Display help
      if (lcd_key != last_lcd_key) {
      ms.select()
      //serialPrintHelp(); 
      }
      last_lcd_key=lcd_key;
      break;
      case btnNONE: // No Button
      last_lcd_key=lcd_key;
      break;
      default:
      break;
    }
  }
}

/*void serialHandler() {
  char inChar;
  if((inChar = Serial.read())>0) {
    switch (inChar) {
    case 'w': // Previus item
      ms.prev();
      displayMenu();
      break;
    case 's': // Next item
      ms.next();
      displayMenu();
      break;
    case 'a': // Back presed
      ms.back();
      displayMenu();
      break;
    case 'd': // Select presed
      ms.select();
      displayMenu();
      break;
    case '?':
    case 'h': // Display help
      serialPrintHelp();
      break;
    default:
      break;
    }
  }
}*/

void serialPrintHelp() {
  Serial.println("***************");
  Serial.println("w: go to previus item (up)");
  Serial.println("s: go to next item (down)");
  Serial.println("a: go back (right)");
  Serial.println("d: select \"selected\" item");
  Serial.println("?: print this help");
  Serial.println("h: print this help");
  Serial.println("***************");

}

