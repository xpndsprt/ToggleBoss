//******************************************
// libs
//******************************************
#include <Wire.h>  
#include "SH1106.h"

//******************************************
// textures
//******************************************
#include "images.h"

//******************************************
// display and toggles
//******************************************
SH1106  display(0x3c, 0, 2, GEOMETRY_128_64); //display def
int oldMillis; //helper for time between frames
int delta; //time between frames
int toggles[3]; //1 for toggle up
int toggleEvents[3]; //one frame events when toggles are switched
int scx; //center of screen
int scy; //center of screen
int octalSum;
//******************************************
// scene controller
//******************************************
int scene =0;
int sceneTimer = 10000;
bool initScene;
int score;
bool gameOver;
int blinkTimer;
int SelectGame_GameSelected=-1;
void setup() {
  pinMode(14, INPUT_PULLUP); 
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  digitalWrite(14, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  display.init();
  initScene = true;
  oldMillis = millis();
  scx = display.getWidth() / 2;
  scy = display.getHeight() / 2;
  
}

void loop() {

  delta = millis() - oldMillis;
  sceneTimer -= delta;

  if (sceneTimer < 0) {
    sceneTimer = 10000;
    gameOver=false;
    score=0;
    initScene = true;
    scene++;
    if (SelectGame_GameSelected!=-1){
      scene =2+SelectGame_GameSelected;
      SelectGame_GameSelected=-1;
    }else if (scene > 2) {
      scene = 0;
    }
    
  }

  oldMillis = millis();
  
  UpdateInput();
  if (scene==0)
      UpdateToggleBossIntro();
  if (scene==1)
      UpdateSelectGame();
  if (scene==2)
      UpdateStarLift();
  if (scene==3)
      UpdateBobTog();
  
  delay(1);
}

void UpdateInput(){

  for (int i=0;i<3;i++){
    toggleEvents[i]=0;
  }
  
  if (toggles[0]!=digitalRead(13)){
    toggleEvents[0]=1;
  }

  if (toggles[1]!=digitalRead(12)){
    toggleEvents[1]=1;
  }
  
  if (toggles[2]!=digitalRead(14)){
    toggleEvents[2]=1;
  }
  
  toggles[0]=digitalRead(13);
  toggles[1]=digitalRead(12);
  toggles[2]=digitalRead(14);
  
  octalSum=toggles[0]+(toggles[1]*2)+(toggles[2]*4);
}
