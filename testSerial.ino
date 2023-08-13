#include <SoftwareSerial.h>

// Enter commands in the serial monitor and send them to the GSM modules and view the response

SoftwareSerial SIM900(2, 3);
// SoftwareSerial SIM900(7, 8);


void setup() {
  SIM900.begin(9600);
  Serial.begin(9600);
  Serial.println("Enter command");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    Serial.println("C: " + command);
    sendCommand(command);
    delay(2000);
  }

  // Check if a complete line of response is available
  if (SIM900.available()) {
    
    String response = SIM900.readString();
    Serial.println("Response: " + response);
    
    // sendResponse(response);
  }
}

void sendCommand(String command) {
  
  SIM900.println(command);
  
  
}
