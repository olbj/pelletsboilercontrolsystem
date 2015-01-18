/*

  HelloWorld.pde
  
  LiquidCrystal 16x2 example

  m2tklib = Mini Interative Interface Toolkit Library
  
  Copyright (C) 2011  olikraus@gmail.com

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
*/

#include <LiquidCrystal.h>
#include "M2tk.h"
#include "utility/m2ghlc.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

M2_LABEL(hello_world_label, NULL, "Hello World!");
M2tk m2(&hello_world_label, NULL, NULL, m2_gh_lc);

void setup() {
  m2_SetLiquidCrystal(&lcd, 16, 2);
}

void loop() {
  m2.draw();
  delay(500);
}


