# SIM900 GET & POST request using arduino microcontroller
How to send a GET and POST request with AT commands using the SIM900 GSM/GPRS module and the Arduino UNO. This is useful for retrieving data from the Web and sending data to a web server for Internet of Things(IOT) or embedded systems projects. Could work with other GSM modules that are operated by AT commands such as SIM800L, SIM808 etc. This tutorial uses 2G (GSM) connection. I would be glad if you can update it for 3G and 4G networks, it's a pity 😒 we have to be using 2G networks for projects in 2023.

This tutorial assumes you are using an arduino uno but it should work for other arduino boards. If you are using a raspberry pi microcontroller do **NOT** connect the raspberry pi directly to the SIM900. The SIM900 uses 5V logic level and the raspberry pi uses 3.3V logic level.
For raspberry Pi users see the raspberry Pi section below.

Components:
* [Arduino Uno microcontroller](https://store.arduino.cc/products/arduino-uno-rev3) - for running the commands
* Serial cable for arduino Uno - for connecting the arduino to your pc
* Power supply for SIM900. Recommended is a 5V power supply that can provide 2A, but 9V 1A, or 12V 1A also works.
* Registered SIM card with a data plan - for accessing the internet

![Picture of a SIM card for illustration purposes](https://github.com/RDjarbeng/SIM900-GET-POST-Request/assets/57795443/ca85a718-33f3-4004-9a33-f0abff9242e7)
* SIM900 GSM/GPRS module
  
![image](https://github.com/RDjarbeng/SIM900-GET-POST-Request/assets/57795443/b578b016-4e7f-448a-a0a3-1699ee9bebec)



### Connection diagram
If you need help connecting the SIM900 to the arduino you can check out this tutorial:
[Guide to SIM900 GSM GPRS Shield with Arduino](https://randomnerdtutorials.com/sim900-gsm-gprs-shield-arduino/)

Here's the connection diagram anyway.
![Screenshot 2023-07-12 125158](https://github.com/RDjarbeng/SIM900-GET-POST-Request/assets/57795443/bbf424af-4986-4639-b86d-9e80ec885289)

From my experience, the second connection of the ground cable to the pin on the SIM900 coloured yellow away from the RX,TX, did not make a difference in the behaviour.

**The following sections provide a breakdown of the code by sections but you can skip to the full code below if you prefer.**

###  Setup
To use the SIM900 GSM module with an Arduino Uno, you first need to import the SoftwareSerial library and define a SoftwareSerial object for communication with the module. Here's an example:

```
#include <SoftwareSerial.h>

// SoftwareSerial object for communication with SIM900
SoftwareSerial SIM900(2, 3); // RX, TX
```

In this example, we set the RX pin to digital pin 2 and the TX pin to digital pin 3. You can adjust these pin assignments based on your specific setup. <br>

Next, there are two utility functions provided in the code that simplify sending commands to the SIM900 module and displaying the response. However, if you prefer, you can directly send data to the module using SIM900.println("command");, replacing "command" with the AT command you want to send. <br>

The utility functions are as follows
```
void sendCommand(const char* command) {
  SIM900.println(command);
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
```
The sendCommand function takes a command as input and sends it to the SIM900 module using SIM900.println(command). After sending the command, it calls the ShowSerialData function to display the response received from the module.

The ShowSerialData function reads the response from the SIM900 module using SIM900.available() and SIM900.read(). It then writes each character of the response to the Serial monitor using Serial.write(c). Finally, it adds a delay of 1 second (delay(1000)) to allow for easier reading of the displayed data.

Please note that these utility functions are provided to assist in displaying the results of commands in a structured manner. If you prefer, you can directly send commands to the SIM900 module using SIM900.println("command");. The choice between using the utility functions or direct command sending depends on your preference and the level of detail you want in displaying the response.

# Connecting to the internet
![UncappedSpeedRoaringPowaaahGIF](https://github.com/RDjarbeng/SIM900-GET-POST-Request/assets/57795443/ba2e8c01-9aa1-41e4-b8a6-9dc96cad629c)

## GET request - Retrieving data from the internet 

This code snippet demonstrates how to perform a GET request using the GPRS connection of the SIM900 GSM module. It utilizes various AT commands to establish the connection and send the request.


```

void testGetRequest() {
  sendCommand("AT"); // Check if the module is responsive
  sendCommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\""); // Set the connection type to GPRS
  sendCommand("AT+SAPBR=3,1,\"APN\",\"internet.mtn\""); // Set the Access Point Name (APN) for the network provider
  sendCommand("AT+SAPBR=1,1"); // Open the GPRS context
  sendCommand("AT+HTTPINIT"); // Initialize the HTTP service
  sendCommand("AT+HTTPPARA=\"CID\",1"); // Set the HTTP context identifier
  sendCommand("AT+HTTPPARA=\"URL\",\"http://google.com/\""); // Set the URL for the server
  sendCommand("AT+HTTPACTION=0"); // Initiate the HTTP GET request
  delay(9000); // Wait for the response (adjust the delay as needed)
  sendCommand("AT+HTTPREAD"); // Read the HTTP response
  sendCommand("AT+HTTPTERM"); // Terminate the HTTP service
}
```
#### Explanation of AT commands:
> The backslash \ is used as an escape character so that the quotes " used in the command are not mistaken for the code for the Arduino

1. **AT**: This command checks the responsiveness of the SIM900 module. Expected response: "OK" if the module is responsive.
2. **AT+SAPBR=3,1,\"Contype\",\"GPRS\"**: Sets the connection type to GPRS. Expected response: "OK" if the command is successful.
3. **AT+SAPBR=3,1,\"APN\",\"internet.mtn\"**: Sets the Access Point Name (APN) for the GPRS connection. Please change the "internet.mtn" to the appropriate APN for your network provider. Expected response: "OK" if the command is successful.
4. **AT+SAPBR=1,1**: Opens the GPRS context to establish the connection. Expected response: "OK" if the connection is successfully established.
 
> Note: This command **AT+SAPBR=1,1** may fail when running it a second time and show "ERROR" but the GET request can still work.
5. **AT+HTTPINIT**: Initializes the HTTP service on the SIM900 module. Expected response: "OK" if the initialization is successful.
6. **AT+HTTPPARA=\"CID\",1**: Sets the HTTP context identifier to 1. Expected response: "OK" if the parameter is set successfully.
7. **AT+HTTPPARA=\"URL\",\"http://google.com/\"**: Sets the URL for the server. Replace "http://google.com/" with the actual URL of the server you want to send the GET request to. Expected response: "OK" if the URL is set successfully.
8. **AT+HTTPACTION=0**: Initiates the HTTP GET request. Expected response: "OK" followed by the HTTP response code (e.g., "+HTTPACTION:0,200") if the request is successful.
9. **delay(9000)**: Waits for the response from the server. Adjust the delay time as per your requirements.
10. **AT+HTTPREAD**: Reads the HTTP response from the server. Expected response: The response data from the server.
11. **AT+HTTPTERM**: Terminates the HTTP service on the SIM900 module. Expected response: "OK" if the termination is successful.

Please note that the APN and URL for the server are provided as hardcoded values in this code snippet. It is recommended to make them variables so that users can easily modify them without having to locate them in the code.



## POST request - Sending data to the internet

## Full arduino code 

## Raspberry Pi- Note for raspberry pi users
>  It is not recommended to connect the SIM900 board directly to the RX and TX (UART) pins of the raspberry Pi, because the SIM900 uses a 5V logic level and the raspberry Pi uses 3.3V. Connecting them directly could damage the Pi. You may have to use a voltage level shifter. Unfortunately, I don't know any recommended level shifters, if you do let me know; submit a PR or open an issue to get my attention. Or contact me on LinkedIn or Social media.

#### This page is still in development - 27 June, 2023 - RD
