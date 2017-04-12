void playStartUpSound() {
  int length = 7;
  int notes[] ={NOTE_DS6,NOTE_DS5,NOTE_AS5,NOTE_GS5,NOTE_DS5,NOTE_DS6,NOTE_AS5};
  int dLay = 125;
  int delayScaling[] = {3,1,2,2,2,2,4};
  while(playXP){
    currentMillis = millis();
    if(previousMillis == 0 || currentMillis - previousMillis >= dLay * delayScaling[startupIterator]){
      previousMillis = currentMillis;
      startupIterator++; 
      noNewTone(HORN_PIN);
      playXP = startupIterator < length ? true : false;
      if(playXP){
         NewTone(HORN_PIN, notes[startupIterator]);
      }
    }
  }
}

void playHornParallelized() {
  int length = 12;
  int dLay = 100;
  int notes[] = {NOTE_G5,NOTE_E5,NOTE_C5,NOTE_C5,NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5,NOTE_G5,NOTE_G5,NOTE_E5};
  int delayScaling[] = {1,1,2,2,1,1,1,1,2,2,2,2};
  currentMillis = millis();
  if(previousMillis == 0 || currentMillis - previousMillis >= dLay * delayScaling[hornIterator]){
    previousMillis = currentMillis;
    hornIterator++;    
    noNewTone(HORN_PIN);     
    playHorn = hornIterator < length ? true : false;
    if(playHorn){
      NewTone(HORN_PIN, notes[hornIterator]);
    }
    else {
      hornIterator = -1;
    }
  }
}

