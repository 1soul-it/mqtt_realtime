//note: tetrakhir sy tambahakn untuk proram eeprome

#include <WiFi.h>
#include <PubSubClient.h>
//#include "DHT.h"

#define DHT11PIN 0
#define LED 2
#define LER 13
#define LEL 15
#define LEC 14
//#define DHTTYPE DHT11

//DHT dht(DHT11PIN, DHTTYPE);

//Enter your wifi credentials
const char* ssid = "untan";  
const char* password =  "";

//Enter your mqtt server configurations
const char* mqttServer = "mqtt.eclipseprojects.io";    //Enter Your mqttServer address
const int mqttPort = 1883;       //Port number
const char* mqttUser = "mqtt"; //User
const char* mqttPassword = "123"; //Password

 
WiFiClient espClient;
PubSubClient client(espClient);


void setup() {
  delay(1000);
//  dht.begin();
  pinMode(LED,OUTPUT);
  pinMode(LER,OUTPUT);
  pinMode(LEL,OUTPUT);
  pinMode(LEC,OUTPUT);
//  digitalWrite(LEC, LOW);
  Serial.begin(115200); 
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.print("Connected to WiFi :");
  Serial.println(WiFi.SSID());
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(MQTTcallback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP8266", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.println(client.state());  //If you get state 5: mismatch in configuration
      delay(2000);
 
    }
  }
 
  client.publish("Esp32/sensor", "Hello from ESP8266");
  client.subscribe("Esp32/sensor");
//  client.subscribe("esp/test2");
//  client.subscribe("esp/test3");
//  client.subscribe("esp/test4");
  
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
//      client.publish("outTopic","hello world");
      client.publish("Esp32/Sensor", "Hello from ESP8266");
      // ... and resubscribe
      client.subscribe("Esp32/sensor");
//      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

 
void MQTTcallback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");

  String message;
  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];  //Conver *byte to String
  }
   Serial.print(message);
  if(message == "#on") {digitalWrite(LED,HIGH);}   //LED on  
  if(message == "#off") {digitalWrite(LED,LOW);} //LED off
  if(message == "#ch2On") {digitalWrite(LER,HIGH);}   //LED on  
  if(message == "#ch2Off") {digitalWrite(LER,LOW);} //LED off
  if(message == "#ch3On") {digitalWrite(LEL,HIGH);}   //LED on  
  if(message == "#ch3Off") {digitalWrite(LEL,LOW);} //LED off
  if(message == "#ch4On") {digitalWrite(LEC,LOW);}   //LED on  
  if(message == "#ch4Off") {digitalWrite(LEC,HIGH);} //LED off
  
  
 
  Serial.println();
  Serial.println("-----------------------");  
}
 
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  
  client.loop();

  delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
//  float h = dht.readHumidity();
   float h = 10;
  // Read temperature as Celsius (the default)
//  float t = dht.readTemperature();
  float t = 20;
  // Read temperature as Fahrenheit (isFahrenheit = true)
//  float f = dht.readTemperature(true);
   float f = 30;
  Serial.println(h);
    client.publish("sensor/dht11/suhu",String(t).c_str());
    client.publish("sensor/dht11/humidity",String(f).c_str());
    client.publish("sensor/moisture/kelembabantanah",String(h).c_str()); 
  // Check if any reads failed and exit early (to try again).
//  if (isnan(h) || isnan(t) || isnan(f)) {
//    Serial.println(F("Failed to read from DHT sensor!"));
//    return;
//  }else{   
//    /*
//     * Publish the measured data:
//     * temperature [°C] -> rundebugrepeat/test/dht11/temp_celsius
//     * temperature [°K] -> rundebugrepeat/test/dht11/temp_fahrenheit
//     * humidity [%] -> rundebugrepeat/test/dht11/humidity
//     */
//    client.publish("sensor/dht11/temp_c",String(t).c_str());
//    client.publish("sensor/dht11/temp_f",String(f).c_str());
//    client.publish("sensor/dht11/humidity",String(h).c_str());  
//  }

}
