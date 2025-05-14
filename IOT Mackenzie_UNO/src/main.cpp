#include <DHT.h> // Biblioteca do sensor DHT by Adafruit

#include <ArduinoJson.h>

#define DHTPIN 2      // Pino digital conectado ao sensor DHT11
#define DHTTYPE DHT11   // Tipo do sensor DHT (DHT11)
#define LEDPIN 6      // Pino digital conectado ao LED
#define BOIAPIN 10    // Pino digital conectado ao sensor de boia

DHT dht(DHTPIN, DHTTYPE);


unsigned long startTime;
unsigned long endTime;
unsigned long ledResponseTime;
unsigned long dhtResponseTime;
unsigned long boiaResponseTime;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(LEDPIN, OUTPUT); // Define o pino do LED como saída
  pinMode(BOIAPIN, INPUT_PULLUP); // Define o pino da boia como entrada com resistor de pull-up interno
}

void loop() {
  DynamicJsonDocument doc(1024);
  // Configura a estutura em JSON


  delay(2500); // Espera 2,5 segundos

  // Mede o tempo de resposta do DHT11
  startTime = micros();
  // Lê a umidade (em %)
  float h = dht.readHumidity();
  // Lê a temperatura como Celsius (o padrão)
  float t = dht.readTemperature();
  endTime = micros();
  dhtResponseTime = endTime - startTime;

  // Mede o tempo de resposta do sensor de boia
  startTime = micros();
  // Lê o estado do sensor de boia
  int boiaEstado = digitalRead(BOIAPIN);
  endTime = micros();
  boiaResponseTime = endTime - startTime;
  
  // Se o sensor de boia estiver fechado (nível LOW devido ao pull-up), acende o LED
  startTime = micros();
  if (boiaEstado == LOW) {
    digitalWrite(LEDPIN, HIGH); // Acende o LED
  } else {
    digitalWrite(LEDPIN, LOW);  // Apaga o LED
  }
  endTime = micros();
  ledResponseTime = endTime - startTime;

  // Formatação do objeto da mensagem em JSON
  doc["umidade"] = h;
  doc["temperatura"] = t;
  doc["nivel"] = boiaEstado;

  doc["leitura dht"] = dhtResponseTime; 
  doc["leitura boia"] = boiaResponseTime; 
  doc["leitura led"] = ledResponseTime; 

  serializeJson(doc, Serial);
  Serial.println(); //Adiciona uma quebra de documento
}