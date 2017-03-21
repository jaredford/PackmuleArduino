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
