#include "includes.h"
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(PING_PIN_TRIG, PING_PIN_ECHO, MAX_DISTANCE);
NewPing sonar_cn(PING_PIN_TRIG_CN, PING_PIN_ECHO_CN, MAX_DISTANCE);
int hornIterator = -1, startupIterator = -1;
unsigned long previousMillis = 0, currentMillis = 0, pingTimer, pingTimer_cn;
Sabertooth ST(128, Serial1); // Address 128, and use Serial1 as the serial port.
String buffer = "";
bool stringComplete = false, playHorn = false, manualMode = true, playXP = true;
unsigned int pingSpeed = 50; // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
void setup() 
{  
  pingTimer = millis();
  pingTimer_cn = millis();
  manualMode = true;
  Serial1.begin(9600); // Sabertooth serial line
  Serial2.begin(9600); // HM-10 serial line  
  Serial.begin(9600); // Serial monitor line
  ST.autobaud();
  pinMode(hornPin, OUTPUT);
  ST.drive(0);
  ST.turn(0);  
  // playStartUpSound();
}
void loop()
{ 
  processSerialInput();
  if(playHorn) {
    playHornParallelized(); // Parallelized implementation of horn method
  }
  if (millis() >= pingTimer) {   // pingSpeed milliseconds since last ping, do another ping.
    pingTimer += pingSpeed;      // Set the next ping time.
    sonar.ping_timer(echoCheck); // Send out the ping, calls "echoCheck" function every 24uS where you can check the ping status.
  }
  if (millis() >= pingTimer_cn) {   // pingSpeed milliseconds since last ping, do another ping.
    pingTimer_cn += pingSpeed;      // Set the next ping time.
    sonar_cn.ping_timer(echoCheckChina); // Send out the ping, calls "echoCheck" function every 24uS where you can check the ping status.
  }
}

