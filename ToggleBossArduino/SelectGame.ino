struct GamePress
{
  int x;
  float extend;// 0-1;
  int w = 25;
};

GamePress SelectGame_presses[3];
int SelectGame_AnimationTime;

int SelectGame_GameIconOffset[3];
void UpdateSelectGame() {

  if (initScene) {
    for (int i = 0; i < 3; i++) {
      SelectGame_presses[i].extend = 0;
      SelectGame_GameIconOffset[i] = 0;
    }
    SelectGame_GameSelected = -1;
    initScene = false;
    SelectGame_presses[0].x = scx - 35 - 16 + 4;
    SelectGame_presses[1].x = scx - 16 + 4;
    SelectGame_presses[2].x = scx + 35 - 16 + 4;
    sceneTimer = 2000;
  }
  display.clear();
  SelectGame_AnimationTime += delta;
  if (SelectGame_AnimationTime > 1000) {
    SelectGame_AnimationTime = 0;
  }
  display.drawXbm( 0, 15, 128, 49, IMG_SelectGameHouse);
  for (int i = 0; i < 3; i++) {

    if ( (toggles[i] == 0 && SelectGame_GameSelected == -1) || (SelectGame_GameSelected == i) ) {
      SelectGame_presses[i].extend += (float)delta / 1000;
      if (SelectGame_presses[i].extend > 1) {
        SelectGame_presses[i].extend = 1;
      }
    } else {
      SelectGame_presses[i].extend -= (float)delta / 2000;
      if (SelectGame_presses[i].extend < 0) {
        SelectGame_presses[i].extend = 0;
      }
    }
    if (SelectGame_presses[i].extend > .8 && SelectGame_GameSelected == -1 ) {
      SelectGame_GameSelected = i;
    }
    if (SelectGame_GameSelected == i) {
      SelectGame_GameIconOffset[i] += 1;
    } else {

    }

    display.drawXbm( SelectGame_presses[i].x, 0 + SelectGame_presses[i].extend * 38 + 15 + 7 - 38, 25, 38, IMG_SelectGamePress);

    if (i == 0) {
      if (SelectGame_AnimationTime > 500) {
        display.drawXbm( SelectGame_presses[i].x + 7, 48 - SelectGame_GameIconOffset[i]-1, 12, 13, IMG_StarLiftWalk1);
      } else {
        display.drawXbm( SelectGame_presses[i].x + 7, 48 - SelectGame_GameIconOffset[i]-1, 12, 13, IMG_StarLiftWalk2);
      }
    }
    if (i == 1) {
      if (SelectGame_AnimationTime > 500) {
        display.drawXbm( SelectGame_presses[i].x + 9, 48 - SelectGame_GameIconOffset[i]+1, 8, 8, IMG_BobTogBlack);
      } else {
        display.drawXbm( SelectGame_presses[i].x + 9, 48 - SelectGame_GameIconOffset[i]-1, 8, 8, IMG_BobTogWhite);
      }
    }
    if (i == 2) {
      if (SelectGame_AnimationTime > 500) {
        display.drawXbm( SelectGame_presses[i].x + 5, 48 - SelectGame_GameIconOffset[i], 14, 12, IMG_Char1_Walk2);
      } else {
        display.drawXbm( SelectGame_presses[i].x + 5, 48 - SelectGame_GameIconOffset[i], 14, 12, IMG_Char1_Walk1);
      }
    }

  }
  display.setColor(BLACK);
  display.fillRect( 0, 0, 128, 15);
  display.setColor(WHITE);
  display.drawXbm( 0, 0, 128, 15, IMG_SelectGameHeader);
  if (SelectGame_GameSelected == -1) {
    sceneTimer = 1000;
  }

  display.display();

}
