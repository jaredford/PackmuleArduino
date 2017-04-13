void checkPings() {
  for (uint8_t i = 0; i < NUM_OF_PINGS; i++) {
    if (millis() >= pingTimer[i]) {
      pingTimer[i] += PING_INTERVAL * NUM_OF_PINGS;
      if (i == 0 && currentSensor == (NUM_OF_PINGS - 1)){
        oneSensorCycle(); // Do something with results.
      }     
      sonar[currentSensor].timer_stop();      
      currentSensor = i;
      cm[currentSensor] = 0;
      sonar[currentSensor].ping_timer(echoCheck);
    }
  }
}
void echoCheck() {
  if (sonar[currentSensor].check_timer())
      cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;      
}
void oneSensorCycle() { // Do something with the results.
  for (uint8_t i = 0; i < NUM_OF_PINGS; i++) {
    Serial.print(i);
    Serial.print("=");
    Serial.print(cm[i]);
  }
  Serial.println();
}
