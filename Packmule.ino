#include "includes.h"
NewPing sonar(PING_PIN_TRIG, PING_PIN_ECHO, MAX_DISTANCE);
NewPing sonar_cn(PING_PIN_TRIG_CN, PING_PIN_ECHO_CN, MAX_DISTANCE);
Sabertooth ST(128, Serial1); // Address 128, and use Serial1 as the serial port.
int hornIterator = -1, startupIterator = -1;
unsigned long previousMillis = 0, currentMillis = 0, pingTimer, pingTimer_cn;
String buffer = "";
bool stringComplete = false, playHorn = false, manualMode = true, playXP = true;
void setup() 
{  
  pingTimer = millis();
  pingTimer_cn = millis();
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
}
void loop()
{ 
  processSerialInput();
  if(!manualMode) {
    followUser();
    /*
    if (millis() >= pingTimer) {   // pingSpeed milliseconds since last ping, do another ping.
    pingTimer += PING_SPEED;      // Set the next ping time.
    sonar.ping_timer(echoCheck); // Send out the ping, calls "echoCheck" function every 24uS where you can check the ping status.
    }
    */
    /*if (millis() >= pingTimer_cn) {   // pingSpeed milliseconds since last ping, do another ping.
      pingTimer_cn += PING_SPEED;      // Set the next ping time.
      sonar_cn.ping_timer(echoCheckChina); // Send out the ping, calls "echoCheck" function every 24uS where you can check the ping status.
    }
    */
    
  }
  if(playHorn) {
    playHornParallelized(); // Parallelized implementation of horn method
  }
}

