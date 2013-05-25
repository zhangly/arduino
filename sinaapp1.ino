/*
 Yeelink sensor client power switch example
 */
#include <SPI.h>
#include <Ethernet.h>
#include <math.h>

byte buff[2];

// for yeelink api
#define APIKEY         "d52d8f609727aa82011b161ecbd45a52" // replace your yeelink api key here
#define DEVICEID       3016 // replace your device ID
#define SENSORID       4228 // replace your sensor ID --LED

// assign a MAC address for the ethernet controller.
byte mac[] = { 0x00, 0x1D, 0x72, 0x82, 0x35, 0x9D};
// initialize the library instance:
EthernetClient client;
char server[] = "weibosou.sinaapp.com"; 

unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
boolean lastConnected = false;                 // state of the connection last time through the main loop
const unsigned long postingInterval = 20*1000; // delay between 2 datapoints, 30s
String returnValue = ""; 
boolean ResponseBegin = false;

void setup() {
  pinMode(13, OUTPUT);

  // start serial port:
  Serial.begin(9600);
  // start the Ethernet connection with DHCP:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    for(;;)
      ;
  }
  else {
    Serial.println("Ethernet configuration OK");
  }
}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:

  if (client.available()) {
    char c = client.read();
    Serial.print(c);
      if (c == '{')
        ResponseBegin = true;
      else if (c == '}')
        ResponseBegin = false;

      if (ResponseBegin)
        returnValue += c;   
  }
  if (returnValue.length() !=0 && (ResponseBegin == false))
  {
    Serial.println(returnValue);
    
    if (returnValue.charAt(returnValue.length() - 1) == '1') {
      Serial.println("turn on the LED"); 
      digitalWrite(13, HIGH);

    } 
      else if(returnValue.charAt(returnValue.length() - 1) == '0') {
      Serial.println("turn off the LED"); 
      digitalWrite(13, LOW);
    }
     returnValue = "";
  }
  // if there's no net connection, but there was one last time
  // through the loop, then stop the client:
  if (!client.connected() && lastConnected) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }
  
  // if you're not connected, and ten seconds have passed since
  // your last connection, then connect again and send data:
  if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
    // read sensor data, replace with your code
    //int sensorReading = readLightSensor();
    Serial.print("sinaapp.com:");
    int a0 = analogRead(5);
    int a1 = analogRead(1);
    int vol = a1 * (5.0 / 1023.0*100); 
    sendData(a0,vol);
  }
  // store the state of the connection for next time through
  // the loop:
  lastConnected = client.connected();
}


// this method makes a HTTP connection to the server:
void sendData(int a0,int a1) {
  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.print("GET /index.php?c=aloe&a=post2yeelink");
    client.print("&a0=");
    client.print(a0);
    client.print("&a1=");
    client.print(a1);

    client.println(" HTTP/1.1");
    client.print("Host:");
    client.println(server);
    client.print("Accept: *");
    client.print("/");
    client.println("*");
    client.println("Content-Length: 0");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Connection: close");
    client.println();
  }
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }
   // note the time that the connection was made or attempted:
  lastConnectionTime = millis();
} 



