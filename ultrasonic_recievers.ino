void followUser(){
  int fl = analogRead(RECEIVER_FL);
  int fr = analogRead(RECEIVER_FR);  
  Serial.print("Left: ");
  Serial.println(fl);  
  Serial.print("Right:");
  Serial.println(fr);
}

