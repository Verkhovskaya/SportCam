#include <ESP8266WiFi.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

WiFiServer server(80); //Initialize the server on Port 80
  // 85 clockwise 0.25Hz
  // 92 counter clockwise 0.25
  // Centered at 88?
  
void setup() {
  pinMode(D8, OUTPUT); //GPIO16 is an OUTPUT pin;
  myservo.attach(D8);  // attaches the servo on pin 8 to the servo object
  myservo.write(89);                  // sets the servo position according to the scaled value
 
  WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint
  WiFi.softAP("Hello_IoT", "12345678"); // Provide the (SSID, password); .
  server.begin(); // Start the HTTP Server
  
  Serial.begin(115200); //Start communication between the ESP8266-12E and the monitor window
  IPAddress HTTPS_ServerIP= WiFi.softAPIP(); // Obtain the IP of the Server
  Serial.print("Server IP is: "); // Print the IP to the monitor window
  Serial.println(HTTPS_ServerIP);
  
  pinMode(LED_BUILTIN, OUTPUT); //GPIO16 is an OUTPUT pin;
  digitalWrite(LED_BUILTIN, LOW); //Initial state is ON
}

void loop() {
  WiFiClient client = server.available();
if (!client) {
return;
}
//Looking under the hood
Serial.println("Somebody has connected :)");

String request = client.readStringUntil('\r');
Serial.println(request);

if (request.indexOf("/RIGHT") != -1) {
  Serial.println("RIGHT");
  myservo.write(87);                  // sets the servo position according to the scaled value
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("RIGHT");
  delay(30);
  myservo.write(89);                  // sets the servo position according to the scaled value
  digitalWrite(LED_BUILTIN, LOW);
 }
if (request.indexOf("/LEFT") != -1) {
  Serial.println("LEFT");
  myservo.write(92);                  // sets the servo position according to the scaled value
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("LEFT");
  delay(30);
  myservo.write(89);                  // sets the servo position according to the scaled value
  digitalWrite(LED_BUILTIN, LOW);
 }
}
