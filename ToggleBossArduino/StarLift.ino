struct StarLift
{
  int x;
  int y;
  float extend;
  bool extending;
};

struct StarLiftCharacter
{
  float x;
  float y;
  float xs;
  float ys;
  int walkDuty;
};

bool starLiftStarGrabbed;
int starLiftStarY;
int starLiftSpikesY;
int maxStarLiftCharacters = 1;
StarLiftCharacter starChars[10];
StarLift starLift[3];
int starLiftStarBonusTimer = 0;
StarLiftCharacter starLiftBonusStar;


void GenStar() {
  int starRand = random(3);
  int spikeRand = random(3);
  if (spikeRand == starRand) {
    spikeRand++;
    if (spikeRand > 2) {
      spikeRand = 0;
    }
  }
  starLiftStarY = starRand * 21 + 3;
  starLiftSpikesY = spikeRand * 21 + 3;
}

void UpdateStarLift() {
  if (initScene) {
    gameOver = false;
    for (int i = 0; i < maxStarLiftCharacters; i++) {
      starChars[i].xs = 1;
    }
    score = 0;
    starLift[0].x = 25;
    starLift[0].y = 58;
    starLift[1].x = 54;
    starLift[1].y = 37;
    starLift[2].x = 83;
    starLift[2].y = 58;
    initScene = false;
    sceneTimer = 2000;
    GenerateCharacters();
    GenStar();
  }
  display.clear();
  for (int i = 0; i < 3; i++) {
    if (toggles[i] == 1) {
      starLift[i].extend += (float)delta / 200;
      starLift[i].extending = true;
      if (starLift[i].extend > 1) {
        starLift[i].extend = 1;
        starLift[i].extending = false;
      }
    } else {
      starLift[i].extend -= (float)delta / 200;
      starLift[i].extending = true;
      if (starLift[i].extend < 0) {
        starLift[i].extend = 0;
        starLift[i].extending = false;
      }
    }
    display.drawXbm( starLift[i].x, starLift[i].y - ( starLift[i].extend * 21), 19, 21, IMG_StarLift);
  }
  display.drawXbm(0, 0, 128, 64, IMG_StarLiftBackground);
  for (int i = 0; i < maxStarLiftCharacters; i++) {
    starChars[i].walkDuty += delta * 5;
    if (starChars[i].x + starChars[i].xs > display.getWidth()) {
      starChars[i].x = -12;
      starLiftStarGrabbed = false;
    }
    if (starChars[i].x + starChars[i].xs > display.getWidth() - 15 && starChars[i].y - 4 < starLiftStarY && starChars[i].y + 4 > starLiftStarY && starLiftStarGrabbed == false) {
      if (starChars[i].xs < 4) {
        starChars[i].xs += .06;
      }
      starLiftBonusStar.x = 115;
      starLiftBonusStar.y = starLiftStarY;
      starLiftStarBonusTimer = 500;
      GenStar();
      score++;
      starLiftStarGrabbed = true;
    }
    if (starChars[i].x + starChars[i].xs > display.getWidth() - 15 && starChars[i].y - 4 < starLiftSpikesY && starChars[i].y + 4 > starLiftSpikesY && starLiftStarGrabbed == false) {
      gameOver = true;
    }
    bool onLift = false;
    for (int r = 0; r < 3; r++) {
      if (starChars[i].x > starLift[r].x && starChars[i].x < starLift[r].x + 19 - 12) {
        if (starChars[i].y + 13 < starLift[r].y - ( starLift[r].extend * 21) && (starChars[i].y + 13 > starLift[r].y - 25)) {
          starChars[i].y += ((float)delta / 10);
          if (starChars[i].y + 13 > starLift[r].y - ( starLift[r].extend * 21)) {
            starChars[i].y = starLift[r].y - ( starLift[r].extend * 21) - 13;
          }
          onLift = true;
        }
        if (starLift[r].extending) {
          if (starChars[i].y + 9 < starLift[r].y - ( starLift[r].extend * 21) && starChars[i].y + 13 >= starLift[r].y - ( starLift[r].extend * 21)) {

            starChars[i].y = starLift[r].y - 15 - ( starLift[r].extend * 21);
            onLift = true;
          }
        }
      }
    }
    if (!onLift && gameOver != true) {
      starChars[i].x += starChars[i].xs * ((float)delta / 20);
    }

    if (starChars[i].walkDuty > 1000) {
      starChars[i].walkDuty = 0;
    }
    if (gameOver) {
      if (blinkTimer % 100 > 50) {
        display.drawXbm(starChars[i].x, starChars[i].y, 12, 13, IMG_StarLiftWalk1);
      }

    } else {
      if (starChars[i].walkDuty > 500) {
        display.drawXbm(starChars[i].x, starChars[i].y, 12, 13, IMG_StarLiftWalk1);
      } else {
        display.drawXbm(starChars[i].x, starChars[i].y, 12, 13, IMG_StarLiftWalk2);
      }
    }
    if (starLiftStarGrabbed) {
      if (blinkTimer % 100 > 50) {
        display.drawXbm(110, starLiftStarY, 15, 11, IMG_StarLiftStar);
      }
    } else {
      display.drawXbm(110, starLiftStarY, 15, 11, IMG_StarLiftStar);
      display.drawXbm(110, starLiftSpikesY + 2, 15, 11, IMG_StarLiftSpikes);
    }

  }
  blinkTimer += delta;
  if (blinkTimer > 1000) {
    blinkTimer = 0;
  }
  if (!gameOver) {
    sceneTimer = 4000;
  }

  if (starLiftStarBonusTimer > 0) {
    starLiftStarBonusTimer -= delta;
    starLiftBonusStar.x /= 1.1;
    starLiftBonusStar.y /= 1.1;
    display.drawXbm(starLiftBonusStar.x, starLiftBonusStar.y, 15, 11, IMG_StarLiftStar);
  }

  display.setFont(ArialMT_Plain_10);
  display.drawString(4, 0, String(score));

  if (sceneTimer < 3000) {
    display.clear();
    display.drawXbm(scx - 16, scy - 5, 15, 11, IMG_StarLiftStar);
    display.drawString(scx + 2, scy - 5, "x " + String(score));
  }
  display.display();
}

void GenerateCharacters() {

  for (int i = 0; i < maxStarLiftCharacters; i++) {
    int startInt = 0; //random(6);
    if (startInt == 0) {
      starChars[i].x = 0;
      starChars[i].y = 2;
      starChars[i].xs = 1;
    }
  }
}
