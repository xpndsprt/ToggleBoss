void UpdateToggleBossIntro() {

  if (initScene){
    initScene=false;
    sceneTimer=2000;
  }
 
  display.clear();
  
  if (sceneTimer < 200) {
    if (UpdateTogglesUp()){
      sceneTimer=0;
    }else{
      sceneTimer=200;
    }
  }else{
    display.drawXbm(0,0,128,64,IMG_ToggleBossLogo);
  }

  display.display();
}
