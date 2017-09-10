/*************************************************************** 
* This code is a UI for PelletsControlSystem3
* Copyright (C) 2017  Olof Björkqvist olof@bjorkqvist.nu
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* 
****************************************************************/

import processing.serial.*; //import the Serial library

Serial port; // Create object from Serial class
int x,y,n,k,val,val1,mousedown,tid,fan, valold;
int count1,count2,count,counting, energytab;
int xdisp,ydisp,xa,xb,ya,yb,xbox,ybox,xboxdiff;

color red = color(255,0,0); // PID-signal
color green = color(0,255,0); //Ttap-out
color blue   = color(0,0,255); //Trad-out
color yellow = color(255,255,0); //
color black  = color(0,0,0); //Trad-set
color lightred  = color(255,50,50); //
color lightgreen  = color(120,255,120); //
color lightblue  = color(0,255,255); //Trad-in
color lightyellow = color(255,255,120); //



void setup() {

  println(Serial.list()); // prints the active COM-port list
  String arduinoPort = Serial.list()[3]; //Update this according to listning in consol
  
  port = new Serial(this, arduinoPort, 115200);
  
  //fill(0);
  xdisp=1000; //<>//
  ydisp=800;
  xa=xdisp/16;
  xb=xdisp*7/8;
  //xb=xa+100*int(xb-xa)/100;
  ya=xdisp/8;
  yb=ydisp*15/16;
  yb=ya+100*int((yb-ya)/100);
  xbox=40;
  ybox=40;
  xboxdiff=150;
  
  size(1000, 800); // UI-size
  rect(xa, ya, xb-xa, yb-ya);  // Draw the graph window
    // Ritar upp boxar
  rect(xa, ya/4, 2.5*xbox, ybox);    // Draw the Mode-box
  rect(xa+xboxdiff, ya/4, xbox, ybox);    // Draw the Set Tout-box
  rect(xa+xboxdiff+xbox, ya/4, xbox, ybox);    // Draw the Set Tout-box
  rect(xa+2*xboxdiff, ya/4, xbox, ybox);    // Draw the Set Tout-box
  rect(xa+2*xboxdiff+xbox, ya/4, xbox, ybox);    // Draw the Set Tout-box
  rect(xa+3*xboxdiff, ya/4, xbox, ybox);    // Draw the Set Tout-box
  rect(xa+3*xboxdiff+xbox, ya/4, xbox, ybox);    // Draw the Set Tout-box
  rect(xa+4*xboxdiff, ya/4, xbox, ybox);    // Draw the Set Tout-box
  rect(xa+4*xboxdiff+xbox, ya/4, xbox, ybox);    // Draw the Set Tout-box
  rect(xa+5*xboxdiff, ya/4, xbox, ybox);    // Draw the Set Tout-box
  rect(xa+5*xboxdiff+xbox, ya/4, xbox, ybox);    // Draw the Set Tout-box
  //rect(xa+150, ya/4+ybox, 2*xbox, ybox);    // Draw the Set Tout-box
  smooth();
  PFont font;
  font = createFont("Arial",8,true); // Arial, 16 point, anti-aliasing on
  fill(0);
  textFont(font);
 
  // Draw the grading lines on left side with every 5 line longer
    for(y=yb ; y>ya ; y=y-(yb-ya)/100) {
      if ( n == 5*k) { x=10; }
      else { x=0; }
    line(xa-5-x, y, xa-5+10, y); // Draw the line
    n++;
    if ( n == 5*(k+1)) {k++;}
    }
    n=0;
    k=0;
    y=0;
    for(x=xa ; x<xb ; x=x+(xb-xa)/100) {
      if ( n == 5*k) { y=10; }
      else { y=0; }
    line(x, yb-5, x, yb+5+y); // Draw the line
    n++;
    if ( n == 5*(k+1)) {k++;}
    }
    
  fill(0);
  textSize(14);
  n = 0;
  k = 0;
  for(y=yb ; y>=ya ; y=y-(yb-ya)/100) {
    if ( n == 5*k) {text(n, xa/2, y+5);}// Draw the 0 at the bottom under the line
    n++;
    if ( n == 5*(k+1)) {k++;}
  }
    textSize(14);
    text("Temp (°C)", xa/2, ya-10);// Draw the Start text
    text("Tid 1 sek/pixel", xdisp/12, yb+30);// Draw the Tid text  
    text("5 pixlar/sträck", xdisp/4, yb+30);// Draw the Tid text
    text("25 pixlar/längre sträck", xdisp*3/4, yb+30);// Draw the Tid text
    text("Mode:", xa, ya/8+10);// Draw the T1 text
    text("Set Trad:", xa+xboxdiff, ya/8+10);// Draw the T1 text
    text("Set Tout:", xa+2*xboxdiff, ya/8+10);// Draw the T1 text
    text("Set P:", xa+3*xboxdiff, ya/8+10);// Draw the T1 text
    text("Set I:", xa+4*xboxdiff, ya/8+10);// Draw the T1 text
    text("Set D:", xa+5*xboxdiff, ya/8+10);// Draw the T1 text
    textSize(10);
    text("-", xa+1*xboxdiff+4, ya/8+25);// Draw the T1 + text
    text("-", xa+2*xboxdiff+4, ya/8+25);// Draw the T1 + text
    text("-", xa+3*xboxdiff+4, ya/8+25);// Draw the T1 + text
    text("-", xa+4*xboxdiff+4, ya/8+25);// Draw the T1 + text
    text("-", xa+5*xboxdiff+4, ya/8+25);// Draw the T1 + text
    text("+", xa+1*xboxdiff+70, ya/8+25);// Draw the T1 + text
    text("+", xa+2*xboxdiff+70, ya/8+25);// Draw the T1 + text
    text("+", xa+3*xboxdiff+70, ya/8+25);// Draw the T1 + text
    text("+", xa+4*xboxdiff+70, ya/8+25);// Draw the T1 + text
    text("+", xa+5*xboxdiff+70, ya/8+25);// Draw the T1 + text
    n=0;
}// end setup()

void draw() {
  stroke(green);
  strokeWeight(4);
  point (xa+n, yb-0.3*pow(n,1.3));
  noStroke();
  n++;
  println("Stroke ended");
}