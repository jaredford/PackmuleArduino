void processSerialInput() {
   while (Serial2.available()) {
    // get the new byte:
    char inChar = (char)Serial2.read();
    if (inChar == '\n') {
      stringComplete = true;
    }
    else {
    // else add it to the inputString:
      buffer += inChar;
    }
  }
  if(stringComplete){
    switch (buffer[0]) {
      case 'h':
        playHorn = true;
        stringComplete = false;
        Serial.print("playing horn sound\n");
        hornIterator = -1;
        break;
      case '?':
        Serial2.write(manualMode ? "m" : "a");
        Serial.print("?????????????????????");
        break;
      case 'm':
        manualMode = true;
        Serial.print("m");
        break;
      case 'a':
        manualMode = false;
        Serial.print("a");
        break;
      default:
        stringComplete = false;
        if(manualMode){
          Serial.print(buffer +'\n');
          int speed = buffer.substring(0,3).toInt() - 127;
          int direction = buffer.substring(3).toInt() - 127;
          ST.drive(speed);
          ST.turn(direction);
        }
        else 
          Serial.print("Nice try lol\n");
        break;        
    }
    buffer = "";
  }
}
