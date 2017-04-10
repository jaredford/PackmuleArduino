void followUser(){
  //int fl = takeSamples(50);// we probably need to sample this as we get some inconsistent results from the receivers
  //if(fl > 20){ 
  int l, fl, fc, fr, r;
  l = analogRead(RECEIVER_L);
  fl = analogRead(RECEIVER_FL);
  fc = analogRead(RECEIVER_FC);
  fr = analogRead(RECEIVER_FR);
  r = analogRead(RECEIVER_R);
  int dir = getDirection(l, fl, fc, fr, r);
  switch(dir){
    case DIRECTION_LEFT:
      smoothTurnTo(-30);
      Serial.println("hard left");
      break;
    case DIRECTION_SLIGHT_LEFT:
      smoothTurnTo(-15);
      Serial.println("left");
      break;
    case DIRECTION_NONE:
      smoothTurnTo(0);
      Serial.println("none");
      break;
    case DIRECTION_SLIGHT_RIGHT:
      smoothTurnTo(15);
      Serial.println("right");
      break;
    case DIRECTION_RIGHT:
      smoothTurnTo(30);
      Serial.println("hard right");
      break;   
  }
  previousDir = dir;
  /*
  Serial.print(l);
  Serial.print(" ");
  Serial.print(fl);
  Serial.print(" ");
  Serial.print(fc);
  Serial.print(" ");
  Serial.print(fr);
  Serial.print(" ");
  Serial.print(r);
  Serial.print(" \n");
  */  
}
void smoothTurnTo(int dir) {
  if (dir == previousDir)
    return;
  if (dir < previousDir) {
    for (int i = previousDir - 1; i >= dir; i--){
      ST.turn(i);
    }
  }
  else {
    for (int i = previousDir  + 1; i <= dir; i++){
      ST.turn(i);
    }
  }
}
int getDirection(int l, int fl, int fc, int fr, int r) {
  int max = 0, direction = DIRECTION_LEFT;
  if(l > max){
    max = l;
  }
  if(fl > max) {
    max = fl;
    direction = DIRECTION_SLIGHT_LEFT;
  }
  if(fc > max){
    max = fc;
    direction = DIRECTION_NONE;
  }
  if (fr > max){
    max = fr;
    direction = DIRECTION_SLIGHT_RIGHT;
  }
  if(r > max) {
    max = r;
    direction = DIRECTION_RIGHT;
  }
  if (max < 50)
    return DIRECTION_NONE;
  return direction;
}
int takeSamples(int numberOfSamples) {
  unsigned long fl = 0, fr = 0, temp;
  for(int i = 0; i < numberOfSamples; i++) {
    temp = analogRead(RECEIVER_FL);
    if (fl < temp){
      fl = temp;
    }
  }
  return fl;
}

