/* Temp/Humidity Server - ESP8266 Webserver that gathers data from DHT11 Sensor.

   Thanks to DHT Server from Adafruit Industries for inspiring this code

*/
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#define DHTTYPE DHT11
#define DHTPIN  5

const char* wifiName = "vanderkoff";
const char* password = "Shadow00";

ESP8266WebServer server(80);
 
// Initialize DHT sensor 

DHT dht(DHTPIN, DHTTYPE, 11); 

// global variables

float humidity, temp; 
String webString="";     // used for the web pages
unsigned long previousMillis = 0;         // variable for the asynchronous delay
const long interval = 10000;              // 10 second interval to read sensor

// handlers for each web page
 
void handle_root() {
  server.send(200, "text/plain", "Hello from the weather esp8266, read from /temp or /hum");
  delay(100);
}

void handle_temp() {
    gettemperature();       
    webString = String((int)temp)+" C";   
    server.send(200, "text/plain", webString);  
}

void handle_hum() {
    gettemperature();           
    webString = String((int)humidity);
    server.send(200, "text/plain", webString); 
}
 
void setup(void)
{
  // Initializing serial terminal and sensor
  Serial.begin(115200);  
  dht.begin();        

  // Connect to WiFi network
  WiFi.begin(wifiName, password);
  Serial.print("\n\r \n\rTrying to connect");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting...");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(wifiName);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Creates pages displaying temperature and humidity and call respective handlers
  
  server.on("/", handle_root);
  server.on("/temp", handle_temp);
  server.on("/hum", handle_hum);
  
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void)
{
  server.handleClient();
} 

void gettemperature() {
  // implementing an asynchronous delay based upon Blink Without Delay code
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   

    // Reading temperature 
    humidity = dht.readHumidity();          // Read humidity percentage
    temp = dht.convertFtoC(dht.readTemperature(true));     // Read temperature in C
    // Check for failed reads
    if (isnan(humidity) || isnan(temp)) {
      Serial.println("DHT Sensor failed to read.");
      return;
    }
  }
}

