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
    case 0:
      ST.turn(-30);
      Serial.println("hard left");
      break;
    case 1:
      ST.turn(-15);
      Serial.println("left");
      break;
    case 2:
      ST.turn(0);
      Serial.println("none");
      break;
    case 3:
      ST.turn(15);
      Serial.println("right");
      break;
    case 4:
      ST.turn(30);
      Serial.println("hard right");
      break;   
  }
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
int getDirection(int l, int fl, int fc, int fr, int r) {
  int max = 0, direction = 0;
  if(l > max){
    max = l;
  }
  if(fl > max) {
    max = fl;
    direction = 1;
  }
  if(fc > max){
    max = fc;
    direction = 2;
  }
  if (fr > max){
    max = fr;
    direction = 3;
  }
  if(r > max) {
    max = r;
    direction = 4;
  }
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

