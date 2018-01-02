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
int x,xtext,y,n,j,k,val,val1,mousedown,tid,fan, valold;
int trad,tout;
float p,i,d;
int count1,count2,count,counting, energytab;
int xdisp,ydisp,xa,xb,ya,yb,xbox,ybox,xboxdiff;
String boxtext, runmode;

color red = color(255,0,0); // PID-signal
color green = color(0,255,0); //Ttap-out
color blue   = color(0,0,255); //Trad-out
color yellow = color(255,255,0); //
color black  = color(0,0,0); //Trad-set
color lightred  = color(255,50,50); //
color lightgreen  = color(120,255,120); //
color lightblue  = color(0,255,255); //Trad-in
color lightyellow = color(255,255,120); //
color grey = color(230,230,230);
/*create a matrix that holds all data
0 - TempOutside
1 - TempRadIn
2 - TempRadOut
3 - TempTapwaterOut
4 - TempRadOutSet
5 - SetValve*/
float[][] PelletsData = new float[1000*7/8-1000/16+2][6];


float[] tempHistory = new float[1000*7/8-1000/16+2];

//==============================================================================================================================================

void setup() {

  println(Serial.list()); // prints the active COM-port list
  String arduinoPort = Serial.list()[3]; //Update this according to listning in consol
  
  port = new Serial(this, arduinoPort, 115200);
  
 //default values for the control system
  trad=42;
  tout=5;
  p=3;
  i=1;
  d=1;
  runmode = "Auto";
  
  //fill(0); //<>//
  xdisp=1000;
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
  stroke(grey);
  strokeWeight(1);
  fill(255,255,255);
  rect(xa, ya/4, 2.5*xbox, ybox);    // Draw the Mode-box
  rect(xa+xboxdiff, ya/4, xbox, ybox);    // Draw the Set Trad-
  rect(xa+xboxdiff+xbox, ya/4, xbox, ybox);    // Draw the Set Trad+
  rect(xa+2*xboxdiff, ya/4, xbox, ybox);    // Draw the Set Tout-
  rect(xa+2*xboxdiff+xbox, ya/4, xbox, ybox);    // Draw the Set Tout+
  rect(xa+3*xboxdiff, ya/4, xbox, ybox);    // Draw the Set P-
  rect(xa+3*xboxdiff+xbox, ya/4, xbox, ybox);    // Draw the Set P+
  rect(xa+4*xboxdiff, ya/4, xbox, ybox);    // Draw the Set I-
  rect(xa+4*xboxdiff+xbox, ya/4, xbox, ybox);    // Draw the Set I+
  rect(xa+5*xboxdiff, ya/4, xbox, ybox);    // Draw the Set D-
  rect(xa+5*xboxdiff+xbox, ya/4, xbox, ybox);    // Draw the Set D+
  smooth();
  PFont font;
  font = createFont("Arial",8,true); // Arial, 16 point, anti-aliasing on
  stroke(black);
  fill(0);
  textFont(font);
 
  // Draw the grading lines on left side with every 5 line longer
    strokeWeight(0);
    for(y=yb ; y>ya ; y=y-(yb-ya)/100) {
      if ( n == 5*k) { x=5; }
      else { x=0; }
    line(xa-5-x, y, xa-5+5, y); // Draw the line
    n++;
    if ( n == 5*(k+1)) {k++;}
    }
    n=0;
    k=0;
    y=0;
    for(x=xa ; x<xb ; x=x+(xb-xa)/100) {
      if ( n == 5*k) { y=5; }
      else { y=0; }
    line(x, yb-0, x, yb+5+y); // Draw the line
    n++;
    if ( n == 5*(k+1)) {k++;}
    }
    
  fill(0);
  textSize(14);
  n = 0;
  k = 0;
  for(y=yb ; y>=ya ; y=y-(yb-ya)/120) {
    if ( n == 5*k) {text(n-20, xa/2, y+5);}// Draw the 0 at the bottom under the line
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
    restorebox();
    n=0;
    k=0;
}// end setup()

//==============================================================================================================================================

void draw() {
  delay(100);
  float ypoint=0;
  float oldpoint=0;
  float newpoint=0;
  int index=0, val=0;
  if (mousePressed){
    mouseclick();
  }
restoregraph();
 /*Collect data the PelletsData-array
0 - TempOutside
1 - TempRadIn
2 - TempRadOut
3 - TempTapwaterOut
4 - TempRadOutSet
5 - SetValve*/
 ypoint = yb-getpoint(0)*(yb-ya)/255;
 val = k;
 for (k=0; k<6; k++){
   switch(k){
     case 0: //TempOutside
       stroke(black);
       break;
     case 1: //TempRadIn
       stroke(red);
       break;
     case 2: //TempRadOut
       stroke(green);
       break;
     case 3: //TempTapwaterOut
       stroke(blue);
       break;
     case 4: //TempRadOutSet
       stroke(yellow);
       break;
     case 5: //SetValve 0 - 255
       stroke(lightblue);
       break;
   }

  newpoint = ypoint;
  for (index = 0; index<xb-xa+1; index++){
    oldpoint=PelletsData[index+1][k];
    PelletsData[index+1][k] = newpoint;
    newpoint = oldpoint;
  }
  PelletsData[0][j] = ypoint;
  strokeWeight(3);
  fill(black);
  for (index = 1; index<xb-xa; index++){
    if (PelletsData[index][k] > 0 ){
      point (xa+index, PelletsData[index][k]);
    }
  }
  }
  n++;
  //println(n);
  index =0;
}

//==============================================================================================================================================

void mouseclick(){
  int delaytime=500;
   if (mousePressed && mouseX<xa+2.5*xbox && mouseX>xa && mouseY<ya/4+ybox && mouseY>ya/4 ){ //Mode start //<>//
     if (runmode == "Auto"){
       runmode= "Radtemp";}
       else if (runmode =="Radtemp"){
         runmode = "Outtemp";}
       else if (runmode =="Outtemp"){
         runmode = "Off";}
       else {
         runmode = "Auto";}
  delay(delaytime); //<>//
 }//Mode end
  if (mousePressed && mouseX<xa+xboxdiff+xbox && mouseX>xa+xboxdiff && mouseY<ya/4+ybox && mouseY>ya/4 ){ //Trad- xa+xboxdiff, ya/4, xbox, ybox
       trad--;
  delay(delaytime);
 }
  if (mousePressed && mouseX<xa+xboxdiff+xbox+xbox && mouseX>xa+xboxdiff+xbox && mouseY<ya/4+ybox && mouseY>ya/4 ){ //Trad+
       trad++;
  delay(delaytime);
 }
  if (mousePressed && mouseX<xa+2*xboxdiff+xbox && mouseX>xa+2*xboxdiff && mouseY<ya/4+ybox && mouseY>ya/4 ){ //Tout-
       tout--;
  delay(delaytime);
 }
  if (mousePressed && mouseX<xa+2*xboxdiff+xbox+xbox && mouseX>xa+2*xboxdiff+xbox && mouseY<ya/4+ybox && mouseY>ya/4 ){ //Tout+
       tout++;
  delay(delaytime);
 }
  if (mousePressed && mouseX<xa+3*xboxdiff+xbox && mouseX>xa+3*xboxdiff && mouseY<ya/4+ybox && mouseY>ya/4 ){ //P-
       p=p-0.1;
  delay(delaytime);
 }
  if (mousePressed && mouseX<xa+3*xboxdiff+xbox+xbox && mouseX>xa+3*xboxdiff+xbox && mouseY<ya/4+ybox && mouseY>ya/4 ){ //P+
       p=p+0.1;
  delay(delaytime);
 }
  if (mousePressed && mouseX<xa+4*xboxdiff+xbox && mouseX>xa+4*xboxdiff && mouseY<ya/4+ybox && mouseY>ya/4 ){ //I-
       i=i-0.1;
   delay(delaytime);
 }
  if (mousePressed && mouseX<xa+4*xboxdiff+xbox+xbox && mouseX>xa+4*xboxdiff+xbox && mouseY<ya/4+ybox && mouseY>ya/4 ){ //I+
       i=i+0.1;
   delay(delaytime);
 }
  if (mousePressed && mouseX<xa+5*xboxdiff+xbox && mouseX>xa+5*xboxdiff && mouseY<ya/4+ybox && mouseY>ya/4 ){ //D-
       d=d-0.1;
  delay(delaytime);
 }
  if (mousePressed && mouseX<xa+5*xboxdiff+xbox+xbox && mouseX>xa+5*xboxdiff+xbox && mouseY<ya/4+ybox && mouseY>ya/4 ){ //D+
       d=d+0.1;
  delay(delaytime);
 }
 restorebox();
}

//==============================================================================================================================================

void restorebox(){
  stroke(grey);
  strokeWeight(1);
  //noFill();
  fill(255,255,255);
  rect(xa, ya/4, 2.5*xbox, ybox);    // Draw the Mode-box
  rect(xa+xboxdiff, ya/4, xbox, ybox);    // Draw the Set Trad-
  rect(xa+xboxdiff+xbox, ya/4, xbox, ybox);    // Draw the Set Trad+
  rect(xa+2*xboxdiff, ya/4, xbox, ybox);    // Draw the Set Tout-
  rect(xa+2*xboxdiff+xbox, ya/4, xbox, ybox);    // Draw the Set Tout+
  rect(xa+3*xboxdiff, ya/4, xbox, ybox);    // Draw the Set P-
  rect(xa+3*xboxdiff+xbox, ya/4, xbox, ybox);    // Draw the Set P+
  rect(xa+4*xboxdiff, ya/4, xbox, ybox);    // Draw the Set I-
  rect(xa+4*xboxdiff+xbox, ya/4, xbox, ybox);    // Draw the Set I+
  rect(xa+5*xboxdiff, ya/4, xbox, ybox);    // Draw the Set D-
  rect(xa+5*xboxdiff+xbox, ya/4, xbox, ybox);    // Draw the Set D+
  stroke(black);
  strokeWeight(2);
  noFill();
  rect(xa, ya/4, 2.5*xbox, ybox);
  rect(xa+xboxdiff, ya/4, 2*xbox, ybox);
  rect(xa+2*xboxdiff, ya/4, 2*xbox, ybox);
  rect(xa+3*xboxdiff, ya/4, 2*xbox, ybox);
  rect(xa+4*xboxdiff, ya/4, 2*xbox, ybox);  
  rect(xa+5*xboxdiff, ya/4, 2*xbox, ybox);
  fill(0);
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
  textSize(14);
  textAlign(CENTER);
  text(runmode, xa+0*xboxdiff+50, ya/4+ybox/2+5);
  textAlign(LEFT);
  text(nf(trad,2), xa+1*xboxdiff+32, ya/4+ybox/2+5);// Draw the T1 + text
  text(nf(tout,2), xa+2*xboxdiff+32, ya/4+ybox/2+5);// Draw the T1 + text
  text(nf(p,1,1), xa+3*xboxdiff+32, ya/4+ybox/2+5);// Draw the T1 + text
  text(nf(i,1,1), xa+4*xboxdiff+32, ya/4+ybox/2+5);// Draw the T1 + text
  text(nf(d,1,1), xa+5*xboxdiff+32, ya/4+ybox/2+5);// Draw the T1 + text
}

//==============================================================================================================================================

void restoregraph(){
  stroke(black);
  strokeWeight(1);
  fill(255,255,255);
  rect(xa, ya, xb-xa, yb-ya);
}

//==============================================================================================================================================

int getpoint(int gety){
  if (port.available() > 0) {
    k=port.read();
    gety = port.read();
    println(k);
    println(gety);
  } 
  return gety;   
}

//==============================================================================================================================================

void givedata(){
}