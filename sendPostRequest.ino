#include <SoftwareSerial.h>

// SoftwareSerial object for communication with gprsShield
SoftwareSerial gprsShield(7, 8); // RX, TX

void testPostRequest(String jsonToSend){
  //Example format of JSON:
  // String jsonToSend="{\"uploadedAt\":\"2023-06-26T20:18:22.826Z\",\"data\":[{\"unit\":\"C\",\"reading\":31}]}";
  

  sendCommand("AT");
  ShowSerialData();
  sendCommand("AT+CIPSHUT");
  ShowSerialData();
  delay(500);
  sendCommand("AT+SAPBR=0,1");
  delay(2000);
  
  ShowSerialData();
  sendCommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  ShowSerialData();
  sendCommand("AT+SAPBR=3,1,\"APN\",\"internet.apn\"");
  ShowSerialData();
  sendCommand("AT+SAPBR=1,1");
  delay(2000);
  ShowSerialData();
  sendCommand("AT+HTTPINIT");
  delay(1000);
  ShowSerialData();
  sendCommand("AT+HTTPPARA=\"CID\",1");
  ShowSerialData();
  sendCommand("AT+HTTPPARA=\"URL\",\"http://example.com/data\"");
  ShowSerialData();
  sendCommand("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
  ShowSerialData();
  sendCommand(("AT+HTTPDATA=" + String(jsonToSend.length()) + ",20000").c_str());
  delay(6000);
  SIM900.println(jsonToSend);
  delay(16000);
  ShowSerialData();
  sendCommand("AT+HTTPACTION=1");
  delay(20000);
  ShowSerialData();
  sendCommand("AT+HTTPREAD");
  ShowSerialData();
  sendCommand("AT+HTTPTERM");
  ShowSerialData();
  sendCommand("AT+CIPSHUT");
  ShowSerialData();
}

void sendCommand(const char* command) {
  Serial.print("C: ");
  Serial.println(command);
  gprsShield.println(command);
  delay(1000);
}

String ShowSerialData() {
 
  String response="";
  while (gprsShield.available()) {
    response = gprsShield.readString();
    Serial.println("Res from gprsShield:");
    Serial.println(response);
  }
  return response;
  // delay(1000);
}

void setup() {
  int baudRate = 9600;
  Serial.begin(baudRate); // Serial monitor
  gprsShield.begin(baudRate); // GSM module
  // delay(1000);
  String jsonToSend="{\"uploadedAt\":\"2023-06-26T20:18:22.826Z\",\"data\":[{\"unit\":\"C\",\"reading\":31}]}";
  //please give some time for the SIM card to register on the network before running this command
  delay(7000);
  testPostRequest(jsonToSend);

}

void loop() {
  
  
}
