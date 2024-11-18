#include <WiFi.h>
#include <ThingerESP32.h>
#include <DHT.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Pinos dos sensores
const int ldrPin = 36;   // Pino analógico do LDR (A0 no ESP32)
const int potPin = 35;   // Pino analógico do Potenciômetro
const int dhtPin = 4;    // Pino do sensor DHT (Temperatura e Umidade)

// Configurações de WiFi
const char* ssid = "Wokwi-GUEST";         // rede WiFi
const char* password = "";                // senha do WiFi

// Configurações do Thinger.io
#define USERNAME "nina-rebello"           // nome de usuário na plataforma thinger.io
#define DEVICE_ID "weather_station"       // Device ID criado na plataforma
#define DEVICE_CREDENTIAL "fiap24"        // Credencial do device criada na plataforma
ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

// Configurações do Broker MQTT
const char* BROKER_MQTT = "74.179.84.66"; // URL ou IP do broker MQTT
int BROKER_PORT = 1883;                   // Porta do Broker MQTT (padrão 1883)
const char* mqttUser = "gs2024";          // Usuário do Broker
const char* mqttPassword = "q1w2e3r4";    // Senha do Broker
#define TOPICO_SUBSCRIBE "GS_2TDSPK"      // Tópico MQTT de escuta
#define TOPICO_PUBLISH   "GS_2TDSPK"      // Tópico MQTT de envio
#define SENSOR_ID "weather_station"       // Identificação do sensor para MQTT

// Cliente WiFi e MQTT
WiFiClient espClient; 
PubSubClient MQTT(espClient);

// Configuração do Sensor DHT
#define DHT_TYPE DHT22 
DHT dht(dhtPin, DHT_TYPE);  // Inicializa o sensor DHT

// Função: inicializa parâmetros de conexão MQTT
void initMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  
  while (!MQTT.connected()) {
    Serial.println("Conectando ao Broker MQTT...");
    if (MQTT.connect(SENSOR_ID, mqttUser, mqttPassword)) {
      Serial.println("Conectado ao Broker MQTT!");
    } else {
      Serial.print("Falha na conexão MQTT. Código de erro: ");
      Serial.println(MQTT.state());
      delay(2000);
    }
  }
}

// Função: verifica conexões WiFi e MQTT, reconectando se necessário
void verificaConexoesWiFiEMQTT() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi desconectado. Reconectando...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.println("\nReconectado ao WiFi!");
  }
  
  if (!MQTT.connected()) {
    Serial.println("MQTT desconectado. Reconectando...");
    initMQTT();
  }
}

// Função: classifica a intensidade da luz com base no valor do LDR
String classificaIntensidadeLuz(int ldrValue) {
  if (ldrValue <= 1000) return "Muito Baixa";
  else if (ldrValue <= 2000) return "Baixa";
  else if (ldrValue <= 3000) return "Moderada";
  else return "Alta";
}

// Função: envia dados ao Broker MQTT em formato JSON
void enviaEstadoOutputMQTT(int ldrValue, float windSpeed, float temperature, float humidity) {
  // Cria um objeto JSON
  DynamicJsonDocument jsonDoc(256);

  jsonDoc["Luz"] = classificaIntensidadeLuz(ldrValue);
  jsonDoc["Vento"] = windSpeed;
  jsonDoc["Temperatura"] = temperature;
  jsonDoc["Umidade"] = humidity;

  // Serializa o objeto JSON em um buffer
  char jsonBuffer[256];
  serializeJson(jsonDoc, jsonBuffer);

  // Envia o JSON ao tópico MQTT
  if (MQTT.connected()) {
    MQTT.publish(TOPICO_PUBLISH, jsonBuffer);
    Serial.println("Informação enviada ao Broker MQTT:");
    Serial.println(jsonBuffer);
  } else {
    Serial.println("Falha ao enviar mensagem. MQTT desconectado.");
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Conectar ao WiFi
  Serial.print("Conectando-se à rede WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConectado ao WiFi!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Inicializar MQTT
  initMQTT();

  // Iniciar o sensor DHT
  dht.begin();
  delay(2000); // Aguarda o sensor estabilizar

  // Recursos do Thinger.io
    thing["light_level"] = [](pson &in, pson &out) {
        int ldrValue = analogRead(ldrPin);
        out["value"] = classificaIntensidadeLuz(ldrValue);
    };

    thing["wind_speed"] = [](pson &in, pson &out) {
        int potValue = analogRead(potPin);
        float windSpeed = map(potValue, 0, 4095, 0, 100);
        out["value"] = windSpeed;
    };

    thing["temperature"] = [](pson &in, pson &out) {
        float temperature = dht.readTemperature();
        out["value"] = temperature;
    };

    thing["humidity"] = [](pson &in, pson &out) {
        float humidity = dht.readHumidity();
        out["value"] = humidity;
    };

    // Envio para bucket
    thing["send_to_bucket"] = [](pson &in, pson &out) {
        pson data;
        int ldrValue = analogRead(ldrPin);
        data["Luz"] = classificaIntensidadeLuz(ldrValue);
        data["Temperatura"] = dht.readTemperature();
        data["Umidade"] = dht.readHumidity();
        data["Velocidade do Vento"] = map(analogRead(potPin), 0, 4095, 0, 100);

        thing.write_bucket("weather_station_data", data);
        out = data;  // Opcionalmente, enviar o mesmo conjunto de dados na resposta
    };
}

void loop() {
  thing.handle(); // Mantém a conexão com o Thinger.io
  verificaConexoesWiFiEMQTT(); // Garante que WiFi e MQTT estejam conectados

  // Leitura dos sensores
  int ldrValue = analogRead(ldrPin);
  int potValue = analogRead(potPin);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Classificar a intensidade da luz
  String intensidadeLuz = classificaIntensidadeLuz(ldrValue);

  // Velocidade do vento
  float windSpeed = map(potValue, 0, 4095, 0, 100);

  // Envia os dados para o Broker MQTT
  enviaEstadoOutputMQTT(ldrValue, windSpeed, temperature, humidity);

  // Exibe os dados no Serial Monitor
  Serial.println("Dados enviados:");
  Serial.print("Luz: "); Serial.println(intensidadeLuz);
  Serial.print("Vento: "); Serial.print(windSpeed); Serial.println(" km/h");
  Serial.print("Temperatura: "); Serial.print(temperature); Serial.println(" °C");
  Serial.print("Umidade: "); Serial.print(humidity); Serial.println(" %");

  delay(5000); // Intervalo de 5 segundos
}
