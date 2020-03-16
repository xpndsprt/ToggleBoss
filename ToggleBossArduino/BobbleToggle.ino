struct BobTogBobble
{
  int x;
  int y;
  int suby;
  int color;
  bool falling = true;
};

struct BobTogToRemove
{
  int x;
  int y;
};
int spd=0;
int columnToRemove[9];
int bobTogToRemoveIndex;
BobTogToRemove bobTogToRemove[100];
int BobTogMatrix[9][9];
BobTogBobble CurrentBobbles[3];
int bobTogDeltaDrop = 100;
void AddBobbles() {

  spd+=1;
  int off = random(6);
  for (int i = 0; i < 3; i++) {
    CurrentBobbles[i].x = i + off; //off+i;
    CurrentBobbles[i].y = -1;
    CurrentBobbles[i].falling = true;
    CurrentBobbles[i].suby = 0;
    CurrentBobbles[i].color = random(2);
  }
}

void UpdateBobTog() {

  if (initScene) {
    AddBobbles();
    spd=0;
    for (int xx = 0; xx < 9; xx++) {
      for (int yy = 0; yy < 9; yy++) {
        BobTogMatrix[xx][yy] = -1;
      }
    }
    initScene = false;
  }

  display.clear();

  display.drawXbm(0, 0, 128, 64, IMG_BobTogBackground);
  if (!gameOver) {
    
  } else {

    display.clear();
    display.drawXbm(scx - 12, scy - 3, 8, 8, IMG_BobTogWhite);
    display.drawString(scx + 2, scy - 5, "x " + String(score));

    display.display();
    return;
  }
  int offx = 30;
  int offy = 0;

  bobTogDeltaDrop -= delta * (2+(spd/8));
  if (spd>20){
    spd=20;
  }
  bool allFell = true;
  for (int i = 0; i < 3; i++) {
    if (toggleEvents[i] == 1 && CurrentBobbles[i].falling) {
      if (CurrentBobbles[i].color == 1) {
        CurrentBobbles[i].color = 0;
      } else {
        CurrentBobbles[i].color = 1;
      }
    }
    if (CurrentBobbles[i].falling) {
      allFell = false;

      if (bobTogDeltaDrop < 0 ) {

        CurrentBobbles[i].suby++;
        if (CurrentBobbles[i].suby > 9) {
          CurrentBobbles[i].suby = 0;
          CurrentBobbles[i].y++;
          //||
          if (CurrentBobbles[i].y > 5 ) {

            CurrentBobbles[i].falling = false;
            BobTogMatrix[CurrentBobbles[i].x][CurrentBobbles[i].y] = CurrentBobbles[i].color;
            CheckLines(CurrentBobbles[i].x, CurrentBobbles[i].y);
          }
          if (BobTogMatrix[CurrentBobbles[i].x][CurrentBobbles[i].y + 1] != -1) {
            CurrentBobbles[i].falling = false;
            if (CurrentBobbles[i].y < 1) {
              gameOver = true;
            }
            BobTogMatrix[CurrentBobbles[i].x][CurrentBobbles[i].y] = CurrentBobbles[i].color;

          }
        }
      }
    }

    if (CurrentBobbles[i].color == 0) {
      display.drawXbm((CurrentBobbles[i].x * 9) + offx, (CurrentBobbles[i].y * 9) + offy + CurrentBobbles[i].suby, 8, 8, IMG_BobTogBlack);
    } else {
      display.drawXbm((CurrentBobbles[i].x * 9) + offx, (CurrentBobbles[i].y * 9) + offy + CurrentBobbles[i].suby, 8, 8, IMG_BobTogWhite);
    }

  }
  if (bobTogDeltaDrop < 0) {
    bobTogDeltaDrop = 100;
  }
  for (int xm = 0; xm < 8; xm++) {
    for (int ym = 0; ym < 7; ym++) {
      if (BobTogMatrix[xm][ym] != -1) {
        if (BobTogMatrix[xm][ym] == 0) {
          display.drawXbm((xm * 9) + offx, (ym * 9) + offy , 8, 8, IMG_BobTogBlack);
        } else {
          display.drawXbm((xm * 9) + offx, (ym * 9) + offy , 8, 8, IMG_BobTogWhite);
        }
      }
    }
  }
bool scored=false;
  display.drawString(7, 8, String(score));
  display.drawString(108, 8, String(spd));
  if (allFell) {
    bobTogToRemoveIndex = 0;
    for (int i = 0; i < 3; i++) {
      CheckLines(CurrentBobbles[i].x, CurrentBobbles[i].y);
    }
    if (bobTogToRemoveIndex>0){
    
      delay(200);
    }
    for (int i = 0; i < 9; i++) {
      columnToRemove[i] == 0;
    }
    
    for (int i = 0; i < bobTogToRemoveIndex; i++) {
      scored=true;
      BobTogMatrix[bobTogToRemove[i].x][bobTogToRemove[i].y] = -1;
      display.setColor(BLACK);
      display.fillRect((bobTogToRemove[i].x * 9) + offx, (bobTogToRemove[i].y * 9) + offy , 8, 8);
      display.setColor(WHITE);
      display.drawXbm((bobTogToRemove[i].x * 9) + offx, (bobTogToRemove[i].y * 9) + offy , 8, 8, IMG_BobTogHit);
      display.display();  
      delay(100);
      columnToRemove[bobTogToRemove[i].x] = 1;
      score++;
    }
    
    for (int i = 0; i < 8; i++) {
     
      if (columnToRemove[i] == 1) {
        
        for (int ii = 6; ii > 1; ii--) {

          if (BobTogMatrix[i][ii] == -1 ) {
            for (int iii = ii; iii > 1; iii--) {
              BobTogMatrix[i][iii] = BobTogMatrix[i][iii - 1];
            }
            BobTogMatrix[i][0] = -1;
          }

        }
      }
      
    }

    AddBobbles();
  }
  display.display();
  delay(5);
  if (scored){
    delay(300);
  }
  if (gameOver!=true){
    sceneTimer = 3000;
  }
}

void CheckLines(int x, int y) {
  int color = BobTogMatrix[x][y];
  //check horisontal;
  int lx = x;
  int hx = x;
  int totHorisontal = 0;
  while (lx >= 0 && BobTogMatrix[lx][y] == color) {
    lx--;
    totHorisontal++;
  }
  while (hx < 8 && BobTogMatrix[hx][y] == color) {
    hx++;
    totHorisontal++;
  }
  if (totHorisontal > 4) {
    for (int i = lx + 1; i < hx; i++) {

      bobTogToRemove[bobTogToRemoveIndex].x = i;
      bobTogToRemove[bobTogToRemoveIndex].y = y;
      bobTogToRemoveIndex++;
    }
  }


}
