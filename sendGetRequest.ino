#include <SoftwareSerial.h>

// SoftwareSerial object for communication with SIM900
SoftwareSerial SIM900(2, 3); // RX, TX

void setup() {
  Serial.begin(19200); // Serial monitor
  SIM900.begin(19200); // SIM900 module
  delay(1000);
  testGetRequestMTN();
  

  // Add any additional code here if needed
}

void loop() {
  // Add your main program logic here if needed
}

void testGetRequestMTN(){
  sendCommand("AT");
  sendCommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  sendCommand("AT+SAPBR=3,1,\"APN\",\"internet.mtn\"");//change this apn value for the SIM card
  sendCommand("AT+SAPBR=1,1");
  sendCommand("AT+HTTPINIT");
  sendCommand("AT+HTTPPARA=\"CID\",1");
  sendCommand("AT+HTTPPARA=\"URL\",\"http://google.com/\""); //Change the URL from google.com to the server you want to reach
  sendCommand("AT+HTTPACTION=0");
  delay(9000);
  sendCommand("AT+HTTPREAD");
  sendCommand("AT+HTTPTERM");
}



void sendCommand(const char* command) {
  SIM900.println(command);
  // delay(1000);
  ShowSerialData();
}

void ShowSerialData() {
  Serial.println("Show serial data:");
  while (SIM900.available()) {
    char c = SIM900.read();
    Serial.write(c);
  }
  Serial.println("");
  delay(1000);
}
