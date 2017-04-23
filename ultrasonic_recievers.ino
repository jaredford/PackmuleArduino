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
      Serial2.print("Hard Left");
      //Serial.println("hard left");
      break;
    case DIRECTION_SLIGHT_LEFT:
      ST.turn(-15);
      ST.drive(20);
      Serial2.print("Left");
      //Serial.println("left");
      break;
    case DIRECTION_FORWARD:
      ST.turn(0);
      ST.drive(60);
      Serial2.print("Forward");
      //Serial.println("forward");
      break;
    case DIRECTION_SLIGHT_RIGHT:
      ST.turn(15);
      ST.drive(20);
      Serial2.print("Right");
      //Serial.println("right");
      break;
    case DIRECTION_RIGHT:
      ST.turn(30);
      ST.drive(0);
      Serial2.print("Hard Right");
      //Serial.println("hard right");
      break;
    case -1: // We only want to fall into this case if several consecutive errors have occurred
      ST.turn(0);
      ST.drive(0);
      if(errorCleared){
        Serial2.print("User Lost");
        errorCleared = false;
      }
      Serial.println("error"); 
      break;
     default:
        successCount++;
        //Serial.println("Adding Success");
        break;
  }
  Serial.print(l);
  Serial.print(" ");
  Serial.print(fl);
  Serial.print(" ");
  Serial.print(fc);
  Serial.print(" ");
  Serial.print(fr);
  Serial.print(" ");
  Serial.print(r);
  Serial.println();
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
    direction = DIRECTION_FORWARD;
  }
  if (fr > max){
    max = fr;
    direction = DIRECTION_SLIGHT_RIGHT;
  }
  if(r > max) {
    max = r;
    direction = DIRECTION_RIGHT;
  }
  if (max < 100){
    errors++;
    successCount = 0;
    if(errors > 5){
      return -1;
    }
    return previousDir;
  }
  clearErrors();
  if(successCount > 10){
    successCount = 11;// Preventing integer from getting too large
    Serial2.print(" ");
    previousDir = direction;
    return direction; 
  }
  return 's';
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
  errors = 0;
  if(!errorCleared){
        Serial2.print("");
        errorCleared = true;
    }
}

