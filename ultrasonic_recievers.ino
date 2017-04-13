void followUser(){
  // Variables to hold sensor readings
  int l, fl, fc, fr, r;
  
  // Read from all the sensors
  l = analogRead(RECEIVER_L);
  fl = analogRead(RECEIVER_FL);
  fc = analogRead(RECEIVER_FC);
  fr = analogRead(RECEIVER_FR);
  r = analogRead(RECEIVER_R);
  
  int dir = getDirection(l, fl, fc, fr, r);
  switch(dir){
    case DIRECTION_LEFT:
      ST.turn(-30);
      ST.drive(0);
      Serial.println("hard left");
      clearErrors();
      previousDir = dir;
      break;
    case DIRECTION_SLIGHT_LEFT:
      ST.turn(-15);
      ST.drive(10);
      Serial.println("left");
      clearErrors();
      previousDir = dir;
      break;
    case DIRECTION_NONE:
      ST.turn(0);
      ST.drive(20);
      Serial.println("none");
      clearErrors();
      previousDir = dir;
      break;
    case DIRECTION_SLIGHT_RIGHT:
      ST.turn(15);
      ST.drive(10);
      Serial.println("right");
      clearErrors();
      previousDir = dir;
      break;
    case DIRECTION_RIGHT:
      ST.turn(30);
      ST.drive(0);
      Serial.println("hard right");
      clearErrors();
      previousDir = dir;
      break;
    case -1: // We only want to fall into this case if several consecutive errors have occurred
      ST.turn(0);
      ST.drive(0);
      if(errorCleared){
        Serial2.write("User not found");
        errorCleared = false;
      }
      Serial.println("error"); 
      break;  
  }
/*  Serial.print(l);
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
// Function to smooth the turning process (needs work.. potential delay issues)
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
// Function to determine where the user is
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
  if (max < 15){
    errors++;
    if(errors > 10){
      return -1;
    }
    return previousDir;
  }
  errors = 0;
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
void clearErrors(){
  if(!errorCleared){
        Serial2.write("");
        errorCleared = true;
    }
}

