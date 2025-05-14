
#include <ESP8266Wifi.h>
#include <WifiClientSecure.h>
#include <PubSubClient.h>
#include <Arduino.h>
#include <ArduinoJson.h>
//  Bibliotecas necessárias para a configuração da conexão wifi e deserialização em JSON

/* Configurações WiFi local */
const char* ssid = "ALLEMAO";
const char* password = "31102015";

/* Configurações da conexão MQTT Broker criadas no HiveMQ */
const char* mqtt_server = "9d096fb5e02340b5a3421119c1e77daa.s1.eu.hivemq.cloud";
const char* mqtt_username = "mackenzie";
const char* mqtt_password = "Broker123";
const int mqtt_port = 8883;

/* Inicialização do WiFi */
WiFiClientSecure espClient;

/* MQTT Client initialization using Wifi Connection */
PubSubClient client(espClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

/************* Connect to WiFi ***********/
void setup_wifi() {
  delay(10);
  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("\nWiFi connected\nIP address: ");
  Serial.println(WiFi.localIP());
}

/************* Connect to MQTT Broker ***********/
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "UNO_R3_Wifi";   // Create a random client ID
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");

      client.subscribe("/led_state");   // subscribe the topics here

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");   // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

/***** Call back Method for Receiving MQTT messages and Switching LED ****/

void callback(char* topic, byte* payload, unsigned int length) {
  String incommingMessage = "";
  for (int i = 0; i < length; i++) incommingMessage+=(char)payload[i];

  Serial.println("Message arrived ["+String(topic)+"]"+incommingMessage);

  //--- check the incomming message
    if( strcmp(topic,"/led_state") == 0){
     //if (incommingMessage.equals("1")) digitalWrite(led, HIGH);   // Turn the LED on
     if (incommingMessage.equals("1")) Serial.println("Hello from PC");   // Turn the LED on 
  }
}

/**** Method for Publishing MQTT Messages **********/
void publishMessage(const char* topic, String payload , boolean retained){
  if (client.publish(topic, payload.c_str(), true))
      Serial.println("Message publised ["+String(topic)+"]: "+payload);
}


/**** Application Initialisation Function******/
void setup() {

  //dht.setup(DHTpin, DHTesp::DHT11); //Set up DHT11 sensor
  //pinMode(led, OUTPUT); //set up LED
  Serial.begin(9600);
  while (!Serial) delay(1);
  setup_wifi();

  espClient.setInsecure();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

/******** Main Function *************/
void loop() {

  if (!client.connected()) reconnect(); // check if client is connected
  client.loop();

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    DynamicJsonDocument doc(1024);
    DeserializationError err = deserializeJson(doc, input);
    char mqtt_message[128];
    if (!err) {
      // Successfully parsed
      int temperatura = doc["temperatura"];
      char temperaturaStr[10];
      itoa(temperatura,temperaturaStr,10);
      publishMessage("/temperatura", temperaturaStr, true);

      int umidade = doc["umidade"];
      char umidadeStr[10];
      itoa(umidade,umidadeStr,10);
      publishMessage("/umidade", umidadeStr, true);

      int nivel = doc["nivel"];
      char nivelStr[10];
      itoa(nivel,nivelStr,10);
      publishMessage("/nivel", nivelStr, true);
    }
  }
}

