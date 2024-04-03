/*********
  Cheni Kapugama 2024 Electro Jam
*********/

// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>

// Replace with your network credentials
const char* ssid = "vodaguest";
const char* password = "J89SCKMYNBGUEST";

#define DHTPIN 4 //Temperature Sensor
#define DHTTYPE DHT11 //Sensor Type
DHT dht(DHTPIN, DHTTYPE);

// Set LED GPIO
String testValue = "gyat";
const int ledPin = 2;
// Stores LED state
String ledState;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String Temperature() { 
  float temp = dht.readTemperature();
  if (isnan(temp)) {    
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(temp); 
    return String(temp);
  }
}

String Humididty() { 
  float humid = dht.readHumidity();
  if (isnan(humid)) {    
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(humid); 
    return String(humid);
  }
}

// Replaces placeholder with LED state value
String processor(const String& var){
  Serial.println(var);
  if(var == "TEMP") { 
    return Temperature();
  }
  return String();
}


void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  //Route to javascript file
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/script.js", "text/javascript");
  });


  // Route to set GPIO to HIGH
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to set GPIO to LOW
  server.on("/temp", HTTP_GET, [](AsyncWebServerRequest *request){  
    request->send_P(200, "text/plain", Temperature().c_str());
    Serial.println(Temperature().c_str());
  });

  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){ 
    request->send_P(200, "text/plain", Humididty().c_str());
    Serial.println(Humididty().c_str());
  });

  
  // Start server
  server.begin();
}
 
void loop(){
  
}