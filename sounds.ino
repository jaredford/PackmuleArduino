void honk() {
  int length = 1;
  int dLay = 300;
  int notes[] = {NOTE_C6};
  int delayScaling[] = {1};
  currentMillis = millis();
  if(previousMillis == 0 || currentMillis - previousMillis >= dLay * delayScaling[hornIterator]){
    previousMillis = currentMillis;
    hornIterator++;    
    noNewTone(HORN_PIN);     
    shouldHonk = hornIterator < length ? true : false;
    if(shouldHonk){
      NewTone(HORN_PIN, notes[hornIterator]);
    }
    else {
      hornIterator = -1;
    }
  }
}

void playBackupTone() {
  int dLay = 500;  
  currentMillis = millis();
  if(firstBeep) {
    previousMillis = 0;
    firstBeep = false;
    silence = false;
  }
  if(previousMillis == 0 || currentMillis - previousMillis >= dLay){
    previousMillis = currentMillis;
    if(silence){
      noNewTone(HORN_PIN);
    }
    else {
      NewTone(HORN_PIN, NOTE_G7);
    }
    silence = !silence;
  }
}

void playStartup() {
  int length = 12;
  int dLay = 100;
  int notes[] = {NOTE_G5,NOTE_E5,NOTE_C5,NOTE_C5,NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5,NOTE_G5,NOTE_G5,NOTE_E5};
  int delayScaling[] = {1,1,2,2,1,1,1,1,2,2,2,2};
  currentMillis = millis();
  if(previousMillis == 0 || currentMillis - previousMillis >= dLay * delayScaling[hornIterator]){
    previousMillis = currentMillis;
    hornIterator++;    
    noNewTone(HORN_PIN);     
    shouldPlayStartup = hornIterator < length ? true : false;
    if(shouldPlayStartup){
      NewTone(HORN_PIN, notes[hornIterator]);
    }
    else {
      hornIterator = -1;
    }
  }
}

