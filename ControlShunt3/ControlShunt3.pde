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
color grey = color(230,230,230);
float[] tempHistory = new float[1000*7/8-1000/16+1];



void setup() {

  //println(Serial.list()); // prints the active COM-port list
  String arduinoPort = Serial.list()[3]; //Update this according to listning in consol
  
  port = new Serial(this, arduinoPort, 115200);
  
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
  smooth();
  PFont font;
  font = createFont("Arial",8,true); // Arial, 16 point, anti-aliasing on
  stroke(black);
  fill(0);
  textFont(font);
 
  // Draw the grading lines on left side with every 5 line longer
    strokeWeight(0);
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
  float ypoint;
  if (mousePressed){
    mouseclick();
  }
  /*//draw graph
 stroke(0);
 fill(255,255,255);
 rect(90,80,100,100);
 for (int index = 0; index<xb-xa; index++)
 { 
 if(index == xb-xa)
 tempHistory[index] = tempC;
 else
 tempHistory[index] = tempHistory[index + 1];
 point(90 + index, 180 - tempHistory[index]); 
 }*/
  

  strokeWeight(4);
  ypoint = ya+(yb-ya)/2+10*sin(n/5);
  //println(ypoint);
  for (int index = 0; index<xb-xa+1; index++) { //<>//
    println(index);
    if (index == xb-xa) {
      tempHistory[index] = ypoint;
      println("ypoint set");}
    else {
      stroke(255,255,255);
      point (xa+index, tempHistory[index]);
      tempHistory[index] = tempHistory[index + 1];
    }
    println(tempHistory[index]);
  stroke(green);
  point (xa+index, tempHistory[index]);
  }
  noStroke();
  n++;
  //println("Stroke ended");
}

void mouseclick(){
  int delaytime=500;
   if (mousePressed && mouseX<xa+2.5*xbox && mouseX>xa && mouseY<ya/4+ybox && mouseY>ya/4 ){ //Mode start
     if (k == 0){
       fill(255, 91, 91);
       k=1;}
       else{
       fill(255, 255, 255);
       k=0;}
       noStroke();
       rect(xa, ya/4, 2.5*xbox, ybox);
  delay(delaytime);
 }//Mode end
  if (mousePressed && mouseX<xa+xboxdiff+xbox && mouseX>xa+xboxdiff && mouseY<ya/4+ybox && mouseY>ya/4 ){ //Trad- xa+xboxdiff, ya/4, xbox, ybox
     if (k == 0){
       fill(255, 91, 91);
       k=1;}
       else{
       fill(255, 255, 255);
       k=0;}
       noStroke();
       rect(xa+xboxdiff, ya/4, xbox, ybox);
  delay(delaytime);
 }
  if (mousePressed && mouseX<xa+xboxdiff+xbox+xbox && mouseX>xa+xboxdiff+xbox && mouseY<ya/4+ybox && mouseY>ya/4 ){ //Trad+
     if (k == 0){
       fill(255, 91, 91);
       k=1;}
       else{
       fill(255, 255, 255);
       k=0;}
       noStroke();
       rect(xa+xboxdiff+xbox, ya/4, xbox, ybox);
  delay(delaytime);
 }
  if (mousePressed && mouseX<xa+2*xboxdiff+xbox && mouseX>xa+2*xboxdiff && mouseY<ya/4+ybox && mouseY>ya/4 ){ //Tout-
     if (k == 0){
       fill(255, 91, 91);
       k=1;}
       else{
       fill(255, 255, 255);
       k=0;}
       noStroke();
       rect(xa+2*xboxdiff, ya/4, xbox, ybox);
  delay(delaytime);
 }
  if (mousePressed && mouseX<xa+2*xboxdiff+xbox+xbox && mouseX>xa+2*xboxdiff+xbox && mouseY<ya/4+ybox && mouseY>ya/4 ){ //Tout+
     if (k == 0){
       fill(255, 91, 91);
       k=1;}
       else{
       fill(255, 255, 255);
       k=0;}
       noStroke();
       rect(xa+2*xboxdiff+xbox, ya/4, xbox, ybox);
  delay(delaytime);
 }
  if (mousePressed && mouseX<xa+3*xboxdiff+xbox && mouseX>xa+3*xboxdiff && mouseY<ya/4+ybox && mouseY>ya/4 ){ //P-
     if (k == 0){
       fill(255, 91, 91);
       k=1;}
       else{
       fill(255, 255, 255);
       k=0;}
       noStroke();
       rect(xa+3*xboxdiff, ya/4, xbox, ybox);
  delay(delaytime);
 }
  if (mousePressed && mouseX<xa+3*xboxdiff+xbox+xbox && mouseX>xa+3*xboxdiff+xbox && mouseY<ya/4+ybox && mouseY>ya/4 ){ //P+
     if (k == 0){
       fill(255, 91, 91);
       k=1;}
       else{
       fill(255, 255, 255);
       k=0;}
       noStroke();
       rect(xa+3*xboxdiff+xbox, ya/4, xbox, ybox);
  delay(delaytime);
 }
  if (mousePressed && mouseX<xa+4*xboxdiff+xbox && mouseX>xa+4*xboxdiff && mouseY<ya/4+ybox && mouseY>ya/4 ){ //I-
     if (k == 0){
       fill(255, 91, 91);
       k=1;}
       else{
       fill(255, 255, 255);
       k=0;}
       noStroke();
       rect(xa+4*xboxdiff, ya/4, xbox, ybox);
  delay(delaytime);
 }
  if (mousePressed && mouseX<xa+4*xboxdiff+xbox+xbox && mouseX>xa+4*xboxdiff+xbox && mouseY<ya/4+ybox && mouseY>ya/4 ){ //I+
     if (k == 0){
       fill(255, 91, 91);
       k=1;}
       else{
       fill(255, 255, 255);
       k=0;}
       noStroke();
       rect(xa+4*xboxdiff+xbox, ya/4, xbox, ybox);
  delay(delaytime);
 }
  if (mousePressed && mouseX<xa+5*xboxdiff+xbox && mouseX>xa+5*xboxdiff && mouseY<ya/4+ybox && mouseY>ya/4 ){ //D-
     if (k == 0){
       fill(255, 91, 91);
       k=1;}
       else{
       fill(255, 255, 255);
       k=0;}
       noStroke();
       rect(xa+5*xboxdiff, ya/4, xbox, ybox);
  delay(delaytime);
 }
  if (mousePressed && mouseX<xa+5*xboxdiff+xbox+xbox && mouseX>xa+5*xboxdiff+xbox && mouseY<ya/4+ybox && mouseY>ya/4 ){ //D+
     if (k == 0){
       fill(255, 91, 91);
       k=1;}
       else{
       fill(255, 255, 255);
       k=0;}
       noStroke();
       rect(xa+5*xboxdiff+xbox, ya/4, xbox, ybox);
  delay(delaytime);
 }
}