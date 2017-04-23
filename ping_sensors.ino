void checkIR() {
  if(analogRead(IR_LEFT) > IR_THRESHOLD) {
    if(leftObstacle >= IR_SUCCESS_THRESHOLD) {
      ST.drive(-20);
      ST.turn(15);
      delay(1000);
      //Serial.println("left");
      ST.drive(40);
      ST.turn(0);
      delay(1500);
      ST.drive(0);
      ST.turn(0);
      leftObstacle = -1;
    }
    leftObstacle++;
  }
  else {
    leftObstacle = 0;
  }
  if(analogRead(IR_CENTER) > IR_THRESHOLD) {
    if(centerObstacle >= IR_SUCCESS_THRESHOLD) {
      ST.drive(-20);
      ST.turn(0);
      delay(1000);
      recoverFromCenterObstacle();
      //Serial.println("center");
      ST.drive(0);
      ST.turn(0);
      centerObstacle = -1;
    }
    centerObstacle++;
  }
  else {
    centerObstacle = 0;
  }
  if(analogRead(IR_RIGHT) > IR_THRESHOLD) {
    if(rightObstacle >= IR_SUCCESS_THRESHOLD) {
      ST.drive(-20);
      ST.turn(-15);
      delay(1000);    
      //Serial.println("right");
      ST.drive(40);
      ST.turn(0);
      delay(1500);
      ST.drive(0);
      ST.turn(0);
      rightObstacle = -1;
    }
    rightObstacle++;
  }
  else {
    rightObstacle = 0;
  }
  
  Serial.print(analogRead(IR_LEFT));
  Serial.print(" ");
  Serial.print(analogRead(IR_CENTER));
  Serial.print(" ");
  Serial.print(analogRead(IR_RIGHT));
  Serial.println();
}
void recoverFromCenterObstacle() {
    if(analogRead(RECEIVER_FL) >= analogRead(RECEIVER_FR)) {
      ST.drive(0);
      ST.turn(-15);
    }
    else {
      ST.drive(0);
      ST.turn(15);
    }
    delay(1000);
    ST.drive(20);
    ST.turn(0);
    delay(500);
}

