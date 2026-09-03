#include <Arduino.h>
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

String classificarAmbiente(
  float temperatura,
  float umidade,
  bool presenca
) {
  if (temperatura >= 33 && presenca) {
    return "CRITICO";
  }

  if (temperatura >= 30 || umidade < 35) {
    return "ATENCAO";
  }

  return "SEGURO";
}

void configurarLeds(const String& status) {
  if (status == "SEGURO") {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
  } else {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);
  }
}

void conectarWiFi() {
  WiFi.begin(ssid, password);

  Serial.print("Conectando ao WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void enviarDados(
  float temperatura,
  float umidade,
  bool presenca
) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi desconectado. Tentando reconectar...");
    conectarWiFi();
    return;
  }

  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient http;

  http.begin(client, serverUrl);
  http.addHeader("Content-Type", "application/json");

  String json = "{";
  json += "\"temperatura\":" + String(temperatura, 1) + ",";
  json += "\"umidade\":" + String(umidade, 1) + ",";
  json += "\"presenca\":";
  json += presenca ? "true" : "false";
  json += "}";

  Serial.println();
  Serial.println("Enviando dados para o VitalPet Dashboard...");
  Serial.print("Payload: ");
  Serial.println(json);

  int responseCode = http.POST(json);

  Serial.print("HTTP Response: ");
  Serial.println(responseCode);

  if (responseCode > 0) {
    String response = http.getString();

    Serial.print("Resposta da API: ");
    Serial.println(response);
  } else {
    Serial.println("Falha na comunicação com a API.");
  }

  http.end();
}

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  dht.setup(DHT_PIN, DHTesp::DHT22);

  conectarWiFi();

  Serial.println();
  Serial.println("=================================");
  Serial.println("   VitalPet CareSense IoT");
  Serial.println("=================================");
}

void loop() {
  TempAndHumidity dados = dht.getTempAndHumidity();

  float temperatura = dados.temperature;
  float umidade = dados.humidity;
  bool presenca = digitalRead(PIR_PIN) == HIGH;

  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("Erro ao realizar leitura do DHT22.");
    delay(3000);
    return;
  }

  String status =
    classificarAmbiente(
      temperatura,
      umidade,
      presenca
    );

  configurarLeds(status);

  Serial.println();
  Serial.println("===== Leitura CareSense =====");

  Serial.print("Temperatura: ");
  Serial.print(temperatura, 1);
  Serial.println(" °C");

  Serial.print("Umidade: ");
  Serial.print(umidade, 1);
  Serial.println(" %");

  Serial.print("Presença do pet: ");
  Serial.println(
    presenca
      ? "DETECTADA"
      : "NÃO DETECTADA"
  );

  Serial.print("Classificação local: ");
  Serial.println(status);

  enviarDados(
    temperatura,
    umidade,
    presenca
  );

  Serial.println("=================================");

  delay(5000);
}
