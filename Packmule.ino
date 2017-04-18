#include "includes.h"
uint8_t currentSensor = 0;
Sabertooth ST(128, Serial1); // Address 128, and use Serial1 as the serial port.
int hornIterator = -1, startupIterator = -1, previousDir = 0, tries = 0, errors = 0, successCount = 0;
unsigned long previousMillis = 0, currentMillis = 0;
String buffer = "";
bool stringComplete = false, shouldPlayHorn = false, manualMode = true, playXP = true, errorSent = false, errorCleared = false, emergencyStopEngaged = false;
void setup() 
{
  manualMode = true;
  Serial1.begin(9600); // Sabertooth serial line
  Serial2.begin(9600); // HM-10 serial line
  Serial.begin(9600); // Serial monitor line
  ST.autobaud();
  pinMode(HORN_PIN, OUTPUT);
  pinMode(RECEIVER_FL, INPUT);
  ST.drive(0);
  ST.turn(0);  
  // playStartUpSound();
}
void loop()
{ 
  processSerialInput();
  irTest();
  if(!manualMode && !emergencyStopEngaged) {
    // probably want to reinitialize pings here
    //followUser();
       
  }
  if(shouldPlayHorn) {
    playHorn(); // Parallelized implementation of horn method
  }
}

