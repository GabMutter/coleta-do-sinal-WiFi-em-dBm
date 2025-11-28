#include <WiFi.h>
#include "AdafruitIO_WiFi.h"

// ----------- CONFIGURAÇÕES DO WIFI ----------
const char* WIFI_SSID = "nome_da_sua_rede";
const char* WIFI_PASS = "sua_senha";

// ----------- CONFIGURAÇÕES DO ADAFRUIT IO ----------
#define IO_USERNAME  "username_io.adafruit"
#define IO_KEY       "key_do_io.adafruit"

// Objeto principal do Adafruit IO
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Feed onde vamos enviar o dBm
AdafruitIO_Feed *dbmFeed = io.feed("grafico");

void setup() {
  Serial.begin(115200);
  Serial.println("Inicializando...");

  io.connect();

  Serial.print("Conectando ao Adafruit IO");
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("Conectado ao Adafruit IO!");
}

void loop() {

  // Mantém a conexão viva
  io.run();

  // Lê o nível do sinal Wi-Fi (em dBm)
  int dbm = WiFi.RSSI();

  Serial.print("Enviando dBm: ");
  Serial.println(dbm);

  // Envia o valor para o feed chamado "grafico"
  dbmFeed->save(dbm);

  delay(3000); // Envia a cada 3s
}
