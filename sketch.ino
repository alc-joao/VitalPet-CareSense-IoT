#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "DHTesp.h"

#define DHT_PIN 15
#define PIR_PIN 13

#define LED_GREEN 2
#define LED_RED 4

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* serverUrl =
  "https://vital-pet-care-sense-dashboard.vercel.app/api/iot";

DHTesp dht;

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  dht.setup(DHT_PIN, DHTesp::DHT22);

  WiFi.begin(ssid, password);

  Serial.print("Conectando ao WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!");
}

void loop() {
  TempAndHumidity dados = dht.getTempAndHumidity();

  float temperatura = dados.temperature;
  float umidade = dados.humidity;

  bool presenca = digitalRead(PIR_PIN) == HIGH;

  bool alerta =
    temperatura >= 30 ||
    umidade <= 35 ||
    presenca;

  if (alerta) {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
  } else {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
  }

  Serial.println("===== VitalPet CareSense =====");

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println(" %");

  Serial.print("Presença: ");
  Serial.println(presenca ? "Detectada" : "Não detectada");

  Serial.print("Status: ");
  Serial.println(alerta ? "ALERTA" : "SEGURO");

  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;
    http.begin(client, serverUrl);
    http.addHeader("Content-Type", "application/json");

    String json = "{";
    json += "\"temperatura\":" + String(temperatura, 1) + ",";
    json += "\"umidade\":" + String(umidade, 1) + ",";
    json += "\"presenca\":" + String(presenca ? "true" : "false");
    json += "}";

    int responseCode = http.POST(json);

    Serial.print("JSON enviado: ");
    Serial.println(json);

    Serial.print("HTTP Response: ");
    Serial.println(responseCode);

    http.end();
  }

  Serial.println("--------------------------------");
  delay(700);
}