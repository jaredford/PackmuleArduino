#include "includes.h"
Sabertooth ST(128, Serial1); // Address 128, and use Serial1 as the serial port.
int hornIterator = -1, toneIterator = -1, previousDir = 0, tries = 0, errors = 0, successCount = 0;
int leftObstacle = 0, centerObstacle = 0, rightObstacle = 0;
unsigned long previousMillis = 0, currentMillis = 0;
String buffer = "", lastTurn = "";
bool stringComplete = false, shouldPlayStartup = false, manualMode = true, shouldHonk = false, shouldPlayBackupTone = false, errorSent = false, errorCleared = false, emergencyStopEngaged = false, firstBeep = true, silence = false;;
void setup() 
{
  Serial1.begin(9600); // Sabertooth serial line
  Serial2.begin(9600); // HM-10 serial line
  Serial.begin(9600); // Serial monitor line
  ST.autobaud();
  pinMode(HORN_PIN, OUTPUT);
  pinMode(RECEIVER_FL, INPUT);
  ST.drive(0);
  ST.turn(0); 
  shouldPlayStartup = true;
}
void loop()
{ 
  processSerialInput();
  if(manualMode){
    emergencyStopEngaged = false;
  }
  if(!manualMode && !emergencyStopEngaged) {
    if(successCount > 10){
      //checkIR();
    }
    followUser();       
  }
  if(shouldPlayStartup) {
    playStartup();
  }
  else if(shouldPlayBackupTone) {
    playBackupTone();
    shouldHonk = false;
  }
  else if(shouldHonk){
    honk();
  }
}

