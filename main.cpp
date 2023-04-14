//Design in Arduino (IDE)

#include <M5Core2.h>
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

//Function Prototypes
void starter();
void questionnaire();
void ButtonGame();
void GoodBye();
void Medium();
void Emergency();

//Function for analysing whether the touch point falls into the 
//area of the rectangules and which one in the questionnaire
bool area(int x, int y, int w, int l, TouchPoint_t pos){
  if(pos.x > x && pos.x < x+w && pos.y > y && pos.y < y+l )
    return 1;
  return 0;
 }

//Setup Function where Bluetooth is turned on, M5 is initiated, 
//the screen is fully black
void setup() {
  SerialBT.begin("M5Stack");
  M5.begin(); //Init M5Core2.
  M5.Lcd.fillScreen(BLACK); // Set the screen background.
}

//The main menu is called and upon touch getting detected
//the questionnaire function is called
void loop() {
  starter();
  if (M5.Touch.ispressed()) {
    M5.Lcd.fillScreen(BLACK);
    questionnaire();
  }
 }

//The main menu is called where directions are given
void starter() {
  M5.Lcd.setCursor(0, 100);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("Welcome!");
  M5.Lcd.setCursor(0, 160);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("Touch the Screen to Start.");
}

//first function questionnaire, 5 rectangles from 1 to 5 
//are created and user is prompted to select one
void questionnaire() {
  int rate = 0;
  M5.update();
//Rectangules are drawn with red sides
  M5.Lcd.drawRect(0, 120, 64, 60, RED); // (x, y, width, length, color)
  M5.Lcd.drawRect(64, 120, 64, 60, RED);
  M5.Lcd.drawRect(128, 120, 64, 60, RED);
  M5.Lcd.drawRect(192, 120, 64, 60, RED);
  M5.Lcd.drawRect(256, 120, 64, 60, RED);
//Question printed
  M5.Lcd.setCursor(0, 80);
  M5.Lcd.println("How are you feeling?");

//Rectangular areas are numbered from 1 to 5
  M5.Lcd.setCursor(32, 150); //0, 120
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("1");
  M5.Lcd.setCursor(96, 150); //64, 120
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("2");
  M5.Lcd.setCursor(160, 150); //128, 120
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("3");
  M5.Lcd.setCursor(224, 150); //192, 120
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("4");
  M5.Lcd.setCursor(288, 150); //256, 120
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("5");
  delay(4000);
// Stores the touch coordinates in pos1
  TouchPoint_t pos1 = M5.Touch.getPressPoint();
//Checking whether touch point is in any of these areas
  if (area(0, 120, 64, 60, pos1)==true) {
    rate=1;
  }
  if (area(64, 120, 64, 60, pos1)== true) {
    rate=2;
  }
  if (area(128, 120, 64, 60, pos1)==true) {
    rate=3;
  }
  if (area(192, 120, 64, 60, pos1)==true) {
    rate=4;
  }
  if (area(256, 120, 64, 60, pos1)==true) {
    rate=5; }
//less than 4 more than 0 call Button Game
  if (rate<4 && rate >0){
    M5.Lcd.fillScreen(BLACK); 
    ButtonGame();
    }
//In other cases print goodbye message and come
//back to the main menu
  else{
  GoodBye();
  }
}

//Button game is initiated using the location of 3 buttons 
//on the lower part of touch screen 10 random instructions 
//for pressing one of three buttons will be constructed in a for loop
void ButtonGame(){
 int Guess = 0;
 int ctr = 0;
 int i = 0;
 M5.Lcd.setTextColor(WHITE);
 M5.Lcd.setTextSize(2);
 for (i ; i < 10; i++){
  Guess=(int)random(1,4);
  M5.update();
  delay(1000);

// first case where the left button is prompted to be pressed
  if ((int)Guess== 1){
    M5.Lcd.setCursor(0, 80);
    M5.Lcd.println("Press the Left Button.");
    delay(2000);
    TouchPoint_t pos= M5.Touch.getPressPoint(); 
    if(pos.y > 240 && pos.x < 109){
      M5.Lcd.setCursor(0, 110);
      M5.Lcd.println("Left Button Pressed.");
      ctr++; 
    } 
    else{
      M5.Lcd.println("Failed to press the button.");
      }
    delay(1000);
  }
//second case where the middle button is prompted to be pressed
  if ((int)Guess==2){
    M5.Lcd.setCursor(0, 80);
    M5.Lcd.println("Press the Middle Button.");
    delay(2000);    
    TouchPoint_t pos= M5.Touch.getPressPoint(); 
    if(pos.y > 240 && pos.x > 109 && pos.x < 218){
      M5.Lcd.setCursor(0, 110);
      M5.Lcd.println("Middle Button Pressed.");
      ctr++;  
    }
    else{
      M5.Lcd.println("Failed to press the button");
      }
    delay(1000);
  }
// third case where the right button is prompted to be pressed
  if ((int)Guess==3){
    M5.Lcd.setCursor(0, 80);
    M5.Lcd.println("Press the Right Button");
    delay(2000);
    TouchPoint_t pos= M5.Touch.getPressPoint(); 
    if(pos.y > 240 && pos.x > 218){ 
      M5.Lcd.setCursor(0, 110);
      M5.Lcd.println("Right Button Pressed.");
      ctr++;
    }
    else{
      M5.Lcd.println("Failed to press the button");
      }
    delay(1000);
  }
  M5.Lcd.fillScreen(BLACK); 
 } 
//end of the button game function
//if ctr is 8, 9 or 10, Goodbye function is called
//if ctr is 5, 6 or 7, function medium is called
//if ctr is 1, 2, 3 or 4, function emergency is called
 if(ctr>7){
  GoodBye();
 }
 else if(ctr>4){
  M5.Lcd.fillScreen(BLACK); 
  Medium();
  }
 else{
  M5.Lcd.fillScreen(BLACK); 
  Emergency();
  }
}

//Goodbye messages are printed on the screen
void GoodBye(){
  M5.Lcd.fillScreen(BLACK); 
  M5.Lcd.setCursor(0, 100);  
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("You are doing great!");
  M5.Lcd.println("Have a good day!");
  delay(5000);
  M5.Lcd.fillScreen(BLACK); 
  }

//Medium function will send the text through bluetooth to the Phone
//and print the other messages on M5Stack's screen
void Medium(){
  SerialBT.println("Would you like to do meditation?");
  SerialBT.println("link: https://www.youtube.com/watch?v=inpok4MKVLM");
  M5.Lcd.setTextColor(RED);
  M5.Lcd.println("Take Deep Breaths...");
  M5.Lcd.println("Check Your Phone");
  delay(5000);
  M5.Lcd.fillScreen(BLACK); 
  }
//Emergency function will send the text through bluetooth to the Phone
//and print the other messages on M5Stack's screen
void Emergency(){
  SerialBT.println("Please call the emergency contact."); 
  M5.Lcd.setTextColor(RED);
  M5.Lcd.println("It's Going to Get Better..");
  M5.Lcd.println("Check Your Phone"); 
  delay(5000);
  M5.Lcd.fillScreen(BLACK); 
  }