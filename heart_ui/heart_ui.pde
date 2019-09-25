import controlP5.*; //import ControlP5 library
import processing.serial.*;

Serial port;

ControlP5 cp5; //create ControlP5 object
PFont font;

void setup(){ //same as arduino program

  size(300, 550);
  
  printArray(Serial.list());
  
  port = new Serial(this, "COM9", 9600);

  cp5 = new ControlP5(this);
  
  cp5.addButton("rest") 
    .setPosition(100, 50) 
    .setSize(120, 70)    
  ;   

  cp5.addButton("old")   
    .setPosition(100, 150) 
    .setSize(120, 70)  
  ;

  cp5.addButton("excercising")   
    .setPosition(100, 250)
    .setSize(120, 70)     
  ;
  
  cp5.addButton("cold")   
    .setPosition(100, 350) 
    .setSize(120, 70)   
  ;
  
  cp5.addButton("warm")  
    .setPosition(100, 450)  
    .setSize(120, 70)     
  ;
}

void draw(){  //same as loop in arduino

  background(150, 0 , 150); 
  
  //lets give title to our window
  fill(0, 255, 0);         
  text("HEART CONTROL", 80, 30);  
}


void rest(){
  port.write(0);
}

void old(){
  port.write(1);
}

void excercising(){
  port.write(2);
}

void cold(){
  port.write(3);
}

void warm(){
  port.write(4);
}
