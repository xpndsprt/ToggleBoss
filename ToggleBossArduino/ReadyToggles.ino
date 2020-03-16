float toggleUpCycle;

bool UpdateTogglesUp() {

  toggleUpCycle += delta*2;
  if (toggleUpCycle > 1000) {
    toggleUpCycle = 0;
  }

  if (toggles[0]==1){
    display.drawXbm(scx - 11 - 30, 0, 22, 37, IMG_ToggleUp);
  }else{
    display.drawXbm(scx - 11 - 30, 0, 22, 37, IMG_ToggleDown);
  }
  if (toggles[1]==1){
    display.drawXbm(scx - 11, 0, 22, 37, IMG_ToggleUp);
  }else{
    display.drawXbm(scx - 11, 0, 22, 37, IMG_ToggleDown);
  }
  if (toggles[2]==1){
    display.drawXbm(scx - 11 + 30, 0, 22, 37, IMG_ToggleUp);
  }else{
    display.drawXbm(scx - 11 + 30, 0, 22, 37, IMG_ToggleDown); 
  }

  int shift = 10 - (toggleUpCycle / 100);
  display.drawXbm(scx - 9 - 30, 50 + shift, 18, 37, IMG_ToggleUpArrow);
  display.drawXbm(scx - 9, 50 + shift, 18, 37, IMG_ToggleUpArrow);
  display.drawXbm(scx - 9 + 30, 50 + shift, 18, 37, IMG_ToggleUpArrow);
  display.display();
  if (octalSum == 7) {
    return true;
  } else {
    return false;
  }
}

bool UpdateTogglesDown() {
  toggleUpCycle += delta*2;
  if (toggleUpCycle > 1000) {
    toggleUpCycle = 0;
  }

  
  if (toggles[0]==1){
    display.drawXbm(scx - 11 - 30, 0, 22, 37, IMG_ToggleUp);
  }else{
    display.drawXbm(scx - 11 - 30, 0, 22, 37, IMG_ToggleDown);
  }
  if (toggles[1]==1){
    display.drawXbm(scx - 11, 0, 22, 37, IMG_ToggleUp);
  }else{
    display.drawXbm(scx - 11, 0, 22, 37, IMG_ToggleDown);
  }
  if (toggles[2]==1){
    display.drawXbm(scx - 11 + 30, 0, 22, 37, IMG_ToggleUp);
  }else{
    display.drawXbm(scx - 11 + 30, 0, 22, 37, IMG_ToggleDown); 
  }
  int shift = (toggleUpCycle / 100)-5;
  display.drawXbm(scx - 9 - 30, 50+shift, 18, 37, IMG_ToggleDownArrow);
  display.drawXbm(scx - 9, 50+shift, 18, 37, IMG_ToggleDownArrow);
  display.drawXbm(scx - 9 + 30, 50+shift, 18, 37, IMG_ToggleDownArrow);
  display.display();
  if (octalSum == 0) {
    return true;
  } else {
    return false;
  }
}
