#include <WiFi.h>
#include <ThingerESP32.h>
#include <DHT.h>

// Pinos dos sensores
const int ldrPin = 36;   // Pino analógico do LDR (A0 no ESP32)
const int potPin = 35;   // Pino analógico do Potenciômetro
const int dhtPin = 4;    // Pino do sensor DHT (Temperatura e Umidade)

// Configurações de WiFi
const char* ssid = "Wokwi-GUEST";         // Substitua pelo nome da sua rede WiFi
const char* password = "";    // Substitua pela senha do WiFi

// Insira as credenciais do dispositivo configurado na plataforma:
#define USERNAME "nina-rebello"           // Seu nome de usuário na plataforma thinger.io
#define DEVICE_ID "weather_station"          // Device ID criado na plataforma
#define DEVICE_CREDENTIAL "fiap24"  // Credencial do device criada na plataforma

// Configurações do Thinger.io
ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

// Configuração do Sensor DHT
#define DHT_TYPE DHT22  // Ou DHT11, se você estiver usando o DHT11
DHT dht(dhtPin, DHT_TYPE);  // Inicializa o sensor DHT

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Conectar ao WiFi
  Serial.print("Conectando-se à rede WiFi...");
  thing.add_wifi(ssid, password);
  delay(5000);
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Conectado ao WiFi!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  }

  // Iniciar o sensor DHT
  dht.begin();
  delay(2000); // Aguarda o sensor estabilizar

  // Define os recursos para monitorar no Thinger.io
  thing["light_level"] >> [](pson & out){
    int ldrValue = analogRead(ldrPin);
    String luzNivel;
    if (ldrValue <= 1000) {
      luzNivel = "Muito Baixa";
    } else if (ldrValue <= 2000) {
      luzNivel = "Baixa";
    } else if (ldrValue <= 3000) {
      luzNivel = "Moderada";
    } else {
      luzNivel = "Alta";
    }
    out["value"] = luzNivel;
  };

  thing["wind_speed"] >> [](pson & out){
    int potValue = analogRead(potPin);
    float velocidadeVento = map(potValue, 0, 4095, 0, 100);
    out["value"] = velocidadeVento;
  };

  thing["temperature"] >> [](pson & out){
    float temperature = dht.readTemperature();
    out["value"] = temperature;
  };

  thing["humidity"] >> [](pson & out){
    float humidity = dht.readHumidity();
    out["value"] = humidity;
  };
}

void loop() {
  thing.handle();  // Mantém a conexão com o Thinger.io

  // Leitura dos sensores
  int ldrValue = analogRead(ldrPin);
  int potValue = analogRead(potPin);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Exibe os dados no Serial Monitor
  Serial.print("Intensidade da Luz: ");
  if (ldrValue <= 1000) Serial.println("Muito Baixa");
  else if (ldrValue <= 2000) Serial.println("Baixa");
  else if (ldrValue <= 3000) Serial.println("Moderada");
  else Serial.println("Alta");

  Serial.print("Velocidade do Vento: ");
  Serial.print(map(potValue, 0, 4095, 0, 100));
  Serial.println(" km/h");

  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Umidade: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(5000);  // Intervalo de 5 segundos
}
