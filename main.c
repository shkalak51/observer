/*===================================================================================
 * NAME : project observer
 * TEAM : sangsan high school, 3-3, someones
 * Version : v1
 * Copyright : demo
 * Description : anti dark templer proect
 * ===================================================================================
 *
 *
 * ftp 223.26.138.2
 * id rta111
 * pw rtadaw11
 * project folder : observer(rta111.dothome.co.kr/observer)
 * Apache 2.2
 * db : MySQL 5.7
 * db hostname : localhost
 * mysql management : http://rta111.dothome.co.kr/phpmyadmin *
 */




#include <SPI.h>
#include <WiFi.h>
#include <string.h>

char ssid[] = "iptime33";      //  your network SSID (name)
char pass[] = "77341782";   // your network password
char server[] = "rta111.dothome.co.kr/observer";
char url[50] = "rta111.dothome.co.kr";

int keyIndex = 0;                 // your network key Index number (needed only for WEP)
int speed2 = 5;
int dir2 = 4;
int delay_time = 1000;


int pir = 2;               // choose the input pin (for PIR sensor)
int val = 0;                    // variable for reading the pin status

//int humidity_value = analogRead(A0);
//int water_left = analogRead(A5);

char comd_temp[20]; // string for incoming serial data
int stringPos = 0; // string index counter
boolean startRead = false;

int status = WL_IDLE_STATUS;
WiFiClient client;
//dcmotersart
boolean toggle = true;

void setup() {
  // start serial port
  Serial.begin(9600);      // initialize serial communication
  pinMode(2, INPUT);      // set the LED pin mode

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);       // don't continue
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(delay_time);
  }
  printWifiStatus();                       // you're connected now, so print out the status
}
//setup END

void loop() {


  val = digitalRead(inputPin);  // read input value
    if (val == HIGH) {            // check if the input is HIGH
      int k = 1;  // int on
    } else {
      int k = 0; // int off
    }

    if (k==1){
    	 //post date to server
    	postData();
    	client.flush();
    }
   delay(delay_time);
} //loop END




void printWifiStatus() {

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();

  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.println();
}//printWifiStatus END

void postData() {

  // If there's a successful connection, send the HTTP POST request
  if (client.connect(server, 8080)) {
    Serial.println("Send Data to DB Connecting...");
    Serial.print("URL : ");
    Serial.println(server);

//    String Data ;
//    Data = "humi=" ;
//    Data = Data + humidity_value ;
//    Data = Data + "&water=" ;
//    Data = Data + humidity_value;


    if (client.connected()) {
// post method
//       client.println("POST /ardu_db.php HTTP/1.1");
//       client.print("HOST:" );
//       client.println(server);
//       client.println("Content-Type: application/x-www-form-urlencoded");
//       client.print("Content-Length: ");
//       client.println(Data.length());
//       client.println();
//       client.print(Data);
//
//       Serial.println("POST /ardu_db.php HTTP/1.1");
//       Serial.print("HOST:" );
//       Serial.println(server);
//       Serial.println("Content-Type: application/x-www-form-urlencoded");
//       Serial.print("Content-Length: ");
//       Serial.println(Data.length());
//       Serial.println();
//       Serial.println(Data);
//       Serial.println();

          client.print("GET /ardu_db.php?");
          client.print("pir sensor =");
          client.print(k);
          client.println(" HTTP/1.1");
          client.print("HOST: ");
          client.println(server);
          client.println("Connection: close");
          client.println();

          Serial.print("GET /ardu_db.php?");
          Serial.print("pir sensor =");
          Serial.print(k);
          Serial.println(" HTTP/1.1");
          Serial.print("HOST: ");
          Serial.println(server);
          Serial.println("Connection: close");
          Serial.println();

          client.stop();
 //     delay(delay_time);
    }
  }
  else {
    // If you couldn't make a connection:
    Serial.println("Send Data to DB Connection failed");
    Serial.println("Disconnecting.");
     Serial.println();
    client.stop();
  //  delay(delay_time);
  }
}
