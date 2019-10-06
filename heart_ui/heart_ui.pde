import controlP5.*; //import ControlP5 library
import processing.serial.*;

Serial port;
PImage oldpic;
PImage restpic;
PImage exerpic;
PImage coldpic;
PImage warmpic;

ControlP5 cp5; //create ControlP5 object
PFont font;

final int borderTop = 50;
final int borderSide = 25;
final int screenWidth = 800;
final int screenHeight = 700;
final int nl = 10;
String modeStr = "PICK A PORT";

ArrayList<Button> portButtons;
ArrayList<Button> controlButtons;

String f1 = "";
String fv = "";
String Vlv = "";

void setup(){ //same as arduino program
  portButtons = new ArrayList<Button>();
  controlButtons = new ArrayList<Button>();
  
  size(800, 700);
  printArray(Serial.list());

  cp5 = new ControlP5(this);
  addButtons();
  
  String portName = "/dev/cu.usbmodem145101";
  port = new Serial(this, portName, 9600);
}


void addButtons() {
  String[] nameList = {"rest", "old", "exercising", "cold", "warm"};

  int w = (screenWidth - borderTop*2) / nameList.length;
  
  for (int i = 0; i < nameList.length; i++) {
    Button button = cp5.addButton(nameList[i]);
    button.setPosition(borderTop + i * w , 50);
    button.setSize(w - 10, 40);
    button.setColorBackground(color(225, 28, 34));
    button.setColorForeground(color(168, 20, 25));
    
    //button.hide();
    controlButtons.add(button);
  }
}

void update() {
}

void drawBar(float value, int x, int y) {
 int barWidth = 40;
 float changeRate = 0.08;
 rectMode(CORNERS);
 fill(120, 120, 255);
 rect(x - barWidth/2, y - value * changeRate, x + barWidth/2, y);
}

void drawArrow(int width, int height, int x, int y) {
  beginShape();
  vertex(x + width/2, y);
  vertex(x, y - height/2);
  vertex(x, y - height/4);
  vertex(x - width/2, y - height/4);
  vertex(x - width/2, y + height/4);
  vertex(x, y + height/4);
  vertex(x, y + height/2);
  vertex(x + width/2, y);
  endShape();
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
        if (values[0].equals( "Vlv")) {
          //text(values[1], screenWidth / 2, 60);
          Vlv = values[1];
        }
      }
    }
  }
  fill(0, 0, 0);
  textSize(15);
  text("blood flow into ventricles", screenWidth / 4, 300);
  text("blood flow to body", screenWidth * 3 / 4, 300);
  text(fv, screenWidth / 4, 350);
  text(f1, screenWidth * 3 / 4, 350);
  drawBar(float(fv), screenWidth / 4, 500);
  drawBar(float(f1), screenWidth * 3 / 4, 500);
  
  // Circle
  double dVlv = float(Vlv);
  int diameter = (int) (Math.sqrt(dVlv)*15);
  fill(255,120, 120);
  ellipse(screenWidth / 2, 400, diameter, diameter);
  
  fill(80, 80, 80);
  drawArrow(40, 30, screenWidth * 3 / 8 - 20, 400);
  drawArrow(40, 30, screenWidth * 5 / 8 + 20, 400);
  //text("blood flow to body: " + f1.toString(), screenWidth / 2, 400);
  //text("blood flow into ventricles: " + fv.toString(), screenWidth / 2, 430);
  oldpic = loadImage("koshi_magari_smile_obaasan.png","png");
  restpic = loadImage("suwaru.png","png");
  exerpic = loadImage("rest.png","png");
  coldpic = loadImage("cold.png","png");
  warmpic = loadImage("hot.png","png");

  image(oldpic,width/4,height/4-60,100,130);
  image(restpic,50,height/4-60,100,130);
  image(exerpic,width/2-40,height/4-60,100,130);
  image(coldpic,width*3/4-100,height/4-60,100,130);
  image(warmpic,width-170,height/4-60,100,130);

}

void rest(){
  port.write(0);
}

void old(){
  port.write(1);
}

void exercising(){
  port.write(2);
}

void cold(){
  port.write(3);
}

void warm(){
  port.write(4);
}
