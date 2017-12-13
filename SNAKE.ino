#include <LiquidCrystal.h>
#include "LedControl.h" 
LedControl lc = LedControl(12, 13, 10, 1); //(DIN, CLK, CS, Amount of MAX7219)
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int ledA4 = A4; //led pentru alimentarea display-ului
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int joyPinX = A0; 
int joyPinY = A1;
int button = 8; //butonul de start
int moveX = 0; //deplasarea pe X
int moveY = 0; // deplasarea pe Y
String direction ;
bool alive = 0; 
int snakeX[64], snakeY[64]; //dimensiunea maxima a sarpelui
int snakeSize = 0;
int foodX = 0, foodY = 0;
int score = 0;
int highscore = 0;
int speed = 500; //
bool food = 0; //verifica daca exista mancare sau nu
bool state = 0; //folosit pentru a face obiectul care trebuie mancat sa clipeasca
int previousTime = 0, currentTime;
int previousTime2 = 0, currentTime2;
bool onScreen = 0; //verifica daca exista ceva pe display
int mod;//folosit pentru afisare
int previousTimeOnScreen = 0, currentTimeOnScreen;
void setup() {
  
  lc.shutdown(0, false); 
  lc.setIntensity(0, 8); 
  lc.clearDisplay(0); 
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(joyPinX, INPUT);
  pinMode(joyPinY, INPUT);
  pinMode(ledA4, OUTPUT);
  pinMode(button, INPUT);
  analogWrite(ledA4, 120);
  digitalWrite(button, HIGH);
}
void loop() {
  if (alive == 0){ 
      if (score == 0)
        displayStart();
      else
        displayOver();
      if (is_button_pressed(button) == 1)
        newGame(); 
    }
  else{
      displayFood();
      currentTime = millis(); 
      if(currentTime-previousTime >= speed-10*score){
          previousTime=currentTime;
          lcd.clear();
          lc.clearDisplay(0);
          moveY = analogRead(joyPinX);
          moveX = analogRead(joyPinY);
          if (moveY >= 530 && direction != "left") 
              direction = "right";
          else if (moveY <= 450 && direction != "right") 
              direction = "left";
          else if (moveX >= 530 && direction != "down") 
              direction = "up";
          else if (moveX <= 450 && direction != "up") 
              direction = "down";
          move(direction);
          food = checkFood(foodX, foodY);
          if (food == 1){
              food = 0;
              generateNewFood();
          }
          if (checkHitSnake())
              gameOver();
          else{
              displaySnake();
              lcd.print("Score:");
              lcd.print(score);
              lcd.setCursor(0,1);
              lcd.print("Viteza:");
              lcd.print(speed-10*score);
              
          }
     }
  }
}
void move(String direction){
  int i;
  for (i = snakeSize-1 ; i > 0 ; i--){
      snakeX[i] = snakeX[i-1];
      snakeY[i] = snakeY[i-1];
  }
  if (direction == "up"){
      if(snakeY[0] == 0)
          snakeY[0] = 7;
      else
          snakeY[0]--;
  } 
  else if (direction == "down"){
      if(snakeY[0] == 7)
          snakeY[0] = 0;
      else
          snakeY[0]++;
  }
  else if (direction == "left"){
      if(snakeX[0] == 0)
          snakeX[0] = 7;
      else 
          snakeX[0]--;
  }
  else{
      if(snakeX[0] == 7)
          snakeX[0] = 0;
      else 
          snakeX[0]++;
  }
}
bool checkFood(int foodX,int foodY){
  if (snakeX[0] == foodX && snakeY[0] == foodY){
      score++;
      snakeSize++;
      return 1;
  }
  return 0;
}

bool isSnake(int x,int y){
  for (int i = 0; i < snakeSize; i++)
      if (snakeX[i] == x && snakeY[i] == y)
          return true;
  return false; 
}
void generateNewFood(){
  foodX = random(0, 7);
  foodY = random(0, 7);
  while (isSnake(foodX,foodY)){
      foodX = random(0, 7);
      foodY = random(0, 7);
  }
}
bool checkHitSnake(){
   for (int i = 1; i < snakeSize; i++) 
       if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
           return true;
   return false;
}
void displaySnake(){
  for (int i = 0; i < snakeSize; i++)
      lc.setLed(0, snakeX[i], snakeY[i], true);
}
void displayFood(){
  currentTime2 = millis();
  if (currentTime2-previousTime2 >= 200){
      state = !state;
      lc.setLed(0, foodX, foodY, state); 
      previousTime2 = currentTime2;
  }
}
void newGame(){
  for (int i = 0; i < 64; i++){
      snakeX[i] = -1;
      snakeY[i] = -1;
  }
  snakeSize = 1;
  snakeX[0] = 4;
  snakeY[0] = 4;
  direction = "up";
  generateNewFood();
  alive = 1;
  score = 0;
}
void gameOver(){
  alive = 0;
  mod = 1;
  lcd.clear();
  if(score > highscore)
      highscore = score;
  for (int i = 0; i < 8; i++) 
      for (int j = 0; j<8; j++) {
           lc.setLed(0, i, j, true);
           delay(25);
           lc.setLed(0, i, j, false);
       }
 }
bool is_button_pressed(int button_pin) {
  static int lastButtonState = LOW;
  static int buttonState;
  static long int lastDebounceTime = 0;
  static long int debounceDelay = 50;
  int reading = digitalRead(button_pin);
  bool isPressed = false;
  if (reading != lastButtonState) {
   lastDebounceTime = millis();
   }
  if ((millis() - lastDebounceTime) > debounceDelay) {
      if (reading != buttonState) {
          buttonState = reading;
          if (buttonState == HIGH) {
              isPressed = true;
          }
      }
  }
  lastButtonState = reading;
  return isPressed;
}
void displayStart() {  
    if (!onScreen){
        lcd.print("Press the button");
        lcd.setCursor(3, 1);
        lcd.print("for start!");
        onScreen = 1;
    }
}
void displayOver() {  
   currentTimeOnScreen = millis();
   if (currentTimeOnScreen-previousTimeOnScreen >= 2500){ 
       lcd.clear();
       previousTimeOnScreen=currentTimeOnScreen;
       if (mod == 1){
           lcd.setCursor(3, 0);
           lcd.print("Game Over!");
           lcd.setCursor(4, 1);
           lcd.print("score:");
           lcd.print(score);
           mod = 2;
       }
       else if (mod == 3){ 
           lcd.print("Press the button");
           lcd.setCursor(3, 1);
           lcd.print("for start!");
           mod = 1;   
       }
       else{
           lcd.setCursor(2, 0);
           lcd.print("Highscore:");
           lcd.print(highscore);
           mod = 3;
       }
   }    
}
