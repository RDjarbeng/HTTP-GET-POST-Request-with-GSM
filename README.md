# SIM900 GET & POST request using arduino microcontroller
How to send a GET and POST request with AT commands using the SIM900 GSM/GPRS module and the Arduino UNO. This is useful for retrieving data from the Web and sending data to a web server for Internet of Things(IOT) or embedded systems projects. Could work with other GSM modules that are operated by AT commands such as SIM800L, SIM808 etc. This tutorial uses 2G (GSM) connection. I would be glad if you can update it for 3G and 4G networks, it's a pity 😒 we have to be using 2G networks for projects in 2023.

For raspberry Pi users see the raspberry Pi section below.

Components:
* [Arduino Uno microcontroller](https://store.arduino.cc/products/arduino-uno-rev3)
* Power supply for SIM900. Recommended is a 5V power supply that can provide 2A, but 9V 1A, or 12V 1A also works.
* Registered SIM card with some data plan

![Picture of a SIM card for illustration purposes](https://github.com/RDjarbeng/SIM900-GET-POST-Request/assets/57795443/ca85a718-33f3-4004-9a33-f0abff9242e7)
* SIM900 GSM/GPRS module
  
![image](https://github.com/RDjarbeng/SIM900-GET-POST-Request/assets/57795443/b578b016-4e7f-448a-a0a3-1699ee9bebec)



## Connection diagram
If you need help connecting the SIM900 to the arduino you can check out this tutorial:
[Guide to SIM900 GSM GPRS Shield with Arduino](https://randomnerdtutorials.com/sim900-gsm-gprs-shield-arduino/)

# Connecting to the internet
![UncappedSpeedRoaringPowaaahGIF](https://github.com/RDjarbeng/SIM900-GET-POST-Request/assets/57795443/ba2e8c01-9aa1-41e4-b8a6-9dc96cad629c)

## GET request - Retrieving data from the internet 
This code performs a get request using the GPRS connection
```
void testGetRequestMTN(){
  sendCommand("AT");
  sendCommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  sendCommand("AT+SAPBR=3,1,\"APN\",\"internet.mtn\"");
  sendCommand("AT+SAPBR=1,1");
  sendCommand("AT+HTTPINIT");
  sendCommand("AT+HTTPPARA=\"CID\",1");
  sendCommand("AT+HTTPPARA=\"URL\",\"http://google.com/\""); //replace google.com with the link to your server 
  sendCommand("AT+HTTPACTION=0");
  delay(9000);
  sendCommand("AT+HTTPREAD");
  sendCommand("AT+HTTPTERM");
}
```

## POST request - Sending data to the internet

## Full arduino code 

## Raspberry Pi- Note for raspberry pi users
>  It is not recommended to connect the SIM900 board directly to the RX and TX (UART) pins of the raspberry Pi, because the SIM900 uses a 5V logic level and the raspberry Pi uses 3.3V. Connecting them directly could damage the Pi. You may have to use a voltage level shifter. Unfortunately, I don't know any recommended level shifters, if you do let me know; submit a PR or open an issue to get my attention. Or contact me on LinkedIn or Social media.

#### This page is still in development - 27 June, 2023 - RD
