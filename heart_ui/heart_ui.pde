import controlP5.*; //import ControlP5 library
import processing.serial.*;

Serial port;

ControlP5 cp5; //create ControlP5 object
PFont font;

final int borderTop = 50;
final int borderSide = 25;
final int screenWidth = 300;
final int screenHeight = 650;
final int nl = 10;
String modeStr = "PICK A PORT";

ArrayList<Button> portButtons;
ArrayList<Button> controlButtons;

String f1 = "";
String fv = "";

void setup(){ //same as arduino program
  portButtons = new ArrayList<Button>();
  controlButtons = new ArrayList<Button>();
  
  size(300, 550);
  printArray(Serial.list());

  cp5 = new ControlP5(this);
  //addPortButtons();
  addButtons();
  
  String portName = "/dev/cu.usbmodem145101";
  port = new Serial(this, portName, 9600);
}

void addPortButtons() {
  for (int i = 0; i < Serial.list().length; i++) {
    Button button = cp5.addButton(Serial.list()[i]);
    button.setPosition(25, borderTop + i * 50);
    button.setSize(screenWidth - 2 * borderSide, 40);
    portButtons.add(button);
  }
}

void addButtons() {
  String[] nameList = {"rest", "old", "exercising", "cold", "warm"};
  
  for (int i = 0; i < nameList.length; i++) {
    Button button = cp5.addButton(nameList[i]);
    button.setPosition(25, borderTop + i * 50);
    button.setSize(screenWidth - 2 * borderSide, 40);
    button.setColorBackground(color(225, 28, 34));
    button.setColorForeground(color(168, 20, 25));
    
    //button.hide();
    controlButtons.add(button);
  }
}

void update() {
}

void barDraw(float value, int x, int y) {
 int barWidth = 20;
 float changeRate = 0.5;
 rectMode(CORNERS);
 rect(x, y - value * changeRate, x + barWidth, y);
}

void draw(){  //same as loop in arduino

  background(255, 255 , 255); 
  
  textAlign(CENTER, BOTTOM);
  //text("HEART CONTROL", screenWidth / 2, 30);  
  
  while(port.available() > 0){
    String myString = port.readStringUntil(nl);
    if(myString != null){
      String[] values = myString.split("=");
      if (values.length >= 2) {
        if (values[0].equals( "f1")) {
          f1 = values[1];
          //text(values[1], screenWidth / 2, 30);
        }
        if (values[0].equals( "fv")) {
          //text(values[1], screenWidth / 2, 60);
          fv = values[1];
        }
      }
    }
  }
  barDraw(float(f1), 50, 400);
  barDraw(float(fv), 100, 400);
  fill(0, 0, 0);
  textSize(15);
  text("blood flow to body: " + f1.toString(), screenWidth / 2, 400);
  text("blood flow into ventricles: " + fv.toString(), screenWidth / 2, 430);
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
