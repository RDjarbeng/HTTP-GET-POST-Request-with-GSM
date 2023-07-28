#include <SoftwareSerial.h>

// SoftwareSerial object for communication with SIM900
SoftwareSerial gprsShield(2, 3); // RX, TX

void setup() {
  int baudRate=19200 // change the baud rate for your GSM modem eg: 9600, 115200
  Serial.begin(baudRate); // Serial monitor
  gprsShield.begin(baudRate); // gprsShield module
  delay(1000);
  sendGetRequest();
  

  // Add any additional code here if needed
}

void loop() {
  // Add your main program logic here if needed
}

void sendGetRequest(){
  sendCommand("AT"); //expected value OK
  sendCommand("AT+CIPSHUT"); //expected value OK
  sendCommand("AT+SAPBR=0,1"); //expected value OK
  sendCommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");// open GPRS context establish GPRS connection
  sendCommand("AT+SAPBR=3,1,\"APN\",\"internet.mtn\"");//change this apn value for the SIM card
  sendCommand("AT+SAPBR=1,1");//open GPRS context bearer
  sendCommand("AT+HTTPINIT");//initiate HTTP request
  sendCommand("AT+HTTPPARA=\"CID\",1");//set parameters for http session
  sendCommand("AT+HTTPPARA=\"URL\",\"http://google.com/\""); //Change the URL from google.com to the server you want to reach
  sendCommand("AT+HTTPACTION=0");//send http request to specified URL, GET session start
  delay(9000); //wait for response for 9 seconds, reduce or increase based on your need
  sendCommand("AT+HTTPREAD");// read results of request, normally contains status code 200 if successful
  sendCommand("AT+HTTPTERM");//close http connection
  sendCommand("AT+CIPSHUT");//close or turn off network connection
  sendCommand("AT+SAPBR=0,1");// close GPRS context bearer
  

}



void sendCommand(const char* command) {
  gprsShield.println(command);
  // delay(1000); //uncomment this delay if you need to wait a while
  ShowSerialData();
}

void ShowSerialData() {
  Serial.println("Show serial data:");
  while (gprsShield.available()) {
    char c = gprsShield.read();
    Serial.write(c);
  }
  Serial.println("");
  delay(1000);
}
