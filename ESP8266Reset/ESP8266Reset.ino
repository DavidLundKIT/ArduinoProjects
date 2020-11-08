#include <SoftwareSerial.h>

#include "WiFiEsp.h"

int cnt=10;
 
void setup() {
  Serial.begin(115200);
}
 
void loop() {
 
  Serial.println(cnt);
 
  if(cnt==0){
    Serial.println("Reset..");
    WiFi.restart();
  }
 
  cnt--;
  delay(1000);
}
