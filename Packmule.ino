#include "includes.h"
NewPing sonar[NUM_OF_PINGS] = {
  NewPing(PING_PIN_ECHO_LEFT, PING_PIN_ECHO_LEFT, MAX_DISTANCE),  
  NewPing(PING_PIN_TRIG_CENTER, PING_PIN_ECHO_CENTER, MAX_DISTANCE),
  NewPing(PING_PIN_ECHO_RIGHT, PING_PIN_ECHO_RIGHT, MAX_DISTANCE)
};
unsigned long pingTimer[NUM_OF_PINGS];
unsigned int cm[NUM_OF_PINGS];
uint8_t currentSensor = 0;
Sabertooth ST(128, Serial1); // Address 128, and use Serial1 as the serial port.
int hornIterator = -1, startupIterator = -1, previousDir = 0, tries = 0;
unsigned long previousMillis = 0, currentMillis = 0;
String buffer = "";
bool stringComplete = false, playHorn = false, manualMode = true, playXP = true;
void setup() 
{
  manualMode = false;
  Serial1.begin(9600); // Sabertooth serial line
  Serial2.begin(9600); // HM-10 serial line  
  Serial.begin(9600); // Serial monitor line
  ST.autobaud();
  pinMode(HORN_PIN, OUTPUT);
  pinMode(RECEIVER_FL, INPUT);
  ST.drive(0);
  ST.turn(0);  
  // playStartUpSound();
  pingTimer[0] = millis() + 75; // First ping start in ms.
  for (uint8_t i = 1; i < NUM_OF_PINGS; i++){
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
  }
}
void loop()
{ 
  processSerialInput();
  if(!manualMode) {
    // probably want to reinitialize pings here
    //followUser();
    checkPings();   
  }
  else {    
    // probably want to nullify pings here
  }
  if(playHorn) {
    playHornParallelized(); // Parallelized implementation of horn method
  }
}

