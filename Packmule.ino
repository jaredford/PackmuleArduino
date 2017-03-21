#include <NewTone.h>
#include "includes.h"
#define PING_PIN_TRIG 7
#define PING_PIN_ECHO 6
#define PING_PIN_TRIG_CN 5
#define PING_PIN_ECHO_CN 4
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
  Serial2.begin(9600); // HC-05 serial line  
  Serial.begin(9600); // Serial monitor line
  ST.autobaud();
  pinMode(hornPin, OUTPUT);
  ST.drive(0);
  ST.turn(0);  
  // playStartUpSound();
}
void sonarTest() {
  Serial.print(sonar.ping_cm()) + "cm";
}
void echoCheck() { // Timer2 interrupt calls this function every 24uS where you can check the ping status.
  // Don't do anything here!
  if (sonar.check_timer()) { // This is how you check to see if the ping was received.
    // Here's where you can add code.
    int dist = sonar.ping_result / US_ROUNDTRIP_CM;
    Serial.println("USA:");
    Serial.println(dist);
  }
}
void echoCheckChina() {  
  if(sonar_cn.check_timer()){
    int dist2 = sonar_cn.ping_result / US_ROUNDTRIP_CM;
    Serial.println("China:");
    Serial.println(dist2);
  }
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

