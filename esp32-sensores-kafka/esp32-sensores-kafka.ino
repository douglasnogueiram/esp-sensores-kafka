#include <WiFi.h>
#include <HTTPClient.h>
#include <heltec.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include "therm.h"
#include "rain.h"
#include "connect.h"
#include "elastic.h"
#include "clock.h"
#include "wifi.h"
#include "ok.h"
#include "error.h"
#include "cavalier.h"
#include <ezTime.h>


//Setup de conexão Wi-Fi
const char* ssid = "SSID";
const char* password =  "PASS"; //

#define WIFI_RETRY_DELAY 500
#define MAX_WIFI_INIT_RETRY 50


//Setup ElasticSearch
//String serverName = "http://192.168.15.20:9200/sensores/_doc/"; //Endpoint do Elasticsearch
String serverName = "http://192.168.15.20:8082/topics/sensores"; //Endpoint do Elasticsearch
//String serverName = "https://reqres.in/api/users";

//Setup do sensor DHT22
#define DHTPIN 22
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

int resultadoLeituraSensor;



//Estrutura para registro do sensor de temperatura e umidade

typedef struct {
  float umidade;
  float temperaturaCelsius;
  String redeWifi;
  String ip;
  String macAddress;
  String timeStamp;

} Sensor;

//Inicializa variáveis
Sensor sensor;


void setup() {

  //Inicializa display
  Heltec.begin(true, false, true);

  //Inicializa sensor DHT
  dht.begin();

  Serial.begin(115200);

  telaBoasVindas("Bem-vindo!!!", 3000);

  //Inicializa variáveis do sensor
  sensor.umidade = 0;
  sensor.temperaturaCelsius = 0;
  sensor.redeWifi = ssid;
  sensor.ip = "";
  sensor.macAddress = "";
  sensor.timeStamp = "";


  if (wifiConnect() == WL_CONNECTED) {
    //enviarMensagemTela("Conectado!", "IP:", sensor.ip, 2000, true);
    enviarMensagemSignal ("Conectado a:", sensor.ip, ssid, 3000);

    //Sincronização do NTC
    waitForSync();
    //Define timezone para NTC
    Timezone brasil;
    brasil.setLocation("America/Sao_Paulo");
    Serial.println("Hora de Brasília: " + brasil.dateTime());


  }

}




void loop() {


  for (int tempo = 5; tempo > 0; tempo--) {

    enviarMensagemTempo (tempo, 1000);

  }


  //Inicializa a conexão Wi-Fi
  if (WiFi.status() == WL_CONNECTED) {

    resultadoLeituraSensor = obtemDadosSensor();

    if ( resultadoLeituraSensor == 0) {
      enviaDadosHttp(sensor);
    }
    else {
      enviarMensagemErroLeituraSensor(3000);
    }

  } else {

    Serial.println("Error in WiFi connection");

  }

  enviarMensagemSignal ("Conectado a:", sensor.ip, ssid, 3000);

}




String registraSensor(Sensor sensor) {

  //Define o buffer do objeto json e o cria
  DynamicJsonDocument doc(2048);

  doc["umidade"] = sensor.umidade;
  doc["temperatura"] = sensor.temperaturaCelsius;
  doc["redeWiFi"] = sensor.redeWifi;
  doc["ip"] = sensor.ip;
  doc["macAddress"] = sensor.macAddress;
  doc["timeStamp"] = sensor.timeStamp;


  String json;
  serializeJson(doc, json);

  return json;

}


void enviaDadosHttp(Sensor sensor) {

  HTTPClient http;

  http.begin(serverName);  //Specify destination for HTTP request

  String httpRequestData = "{\"records\": [{\"value\": " +  registraSensor(sensor) + "}]}";
  Serial.println(httpRequestData);

  http.addHeader("Content-Type", "application/vnd.kafka.json.v2+json");             //Specify content-type header
  http.addHeader("Content-Length", String(httpRequestData.length()));
  int httpResponseCode = http.POST(httpRequestData);   //Send the actual POST request

  if (httpResponseCode > 0) {

    String response = http.getString();                       //Get the response to the request

    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer

    //enviarMensagemTela("POST API", "", "Elasticsearch", 1000, false);
    //enviarMensagemTela(String(httpResponseCode), "Response code", "", 2000, false);

    if (httpResponseCode == 200) {
      enviarMensagemPostagem(httpResponseCode, 2000, true);
      Serial.println("Sucesso: " + String(httpResponseCode));
    } else {
      enviarMensagemPostagem(httpResponseCode, 2000, false);
      Serial.println("Erro: " + String(httpResponseCode));
    }


  } else {

    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
    enviarMensagemPostagem(httpResponseCode, 2000, false);

  }

  http.end();  //Free resources

}


void telaBoasVindas(String mensagem, int tempoExibicao) {

  Heltec.display->setContrast(255);
  Heltec.display->clear();


  Heltec.display->drawXbm(30, 0, cavalier_width, cavalier_height, cavalier_bits);

  Heltec.display->display();
  delay(tempoExibicao);

  Heltec.display->clear();
  Heltec.display->display();

  Heltec.display->setFont(ArialMT_Plain_24);
  Heltec.display->drawString(0, 25, mensagem);

  Heltec.display->display();

  delay(tempoExibicao);

  Heltec.display->clear();
  Heltec.display->display();

}


void enviarMensagemTela (String mensagemGrande, String mensagemMedia, String mensagemPequena, int tempoExibicao, boolean manterTela) {

  Heltec.display->setContrast(255);
  Heltec.display->clear();

  Heltec.display->setFont(ArialMT_Plain_24);
  Heltec.display->drawString(0, 0, mensagemGrande);

  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(0, 25, mensagemMedia);

  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 45, mensagemPequena);

  Heltec.display->display();


  if (!manterTela) {

    delay(tempoExibicao);

    Heltec.display->clear();
    Heltec.display->display();

  }
}



void enviarMensagemSensor (float temperatura, float umidade, int tempoExibicao) {

  Heltec.display->setContrast(255);
  Heltec.display->clear();

  Heltec.display->drawXbm(0, 0, therm_width, therm_height, therm_bits);

  Heltec.display->setFont(ArialMT_Plain_10);
  //Heltec.display->drawString(15, 56, "Temperatura");

  Heltec.display->setFont(ArialMT_Plain_24);
  Heltec.display->drawString(60, 12, String(temperatura));

  Heltec.display->setFont(ArialMT_Plain_24);
  Heltec.display->drawString(70, 35, "°C");

  Heltec.display->display();
  delay(tempoExibicao);

  Heltec.display->clear();

  Heltec.display->drawXbm(0, 0, rain_width, rain_height, rain_bits);

  Heltec.display->setFont(ArialMT_Plain_10);
  //Heltec.display->drawString(0, 56, "Umidade");

  Heltec.display->setFont(ArialMT_Plain_24);
  Heltec.display->drawString(64, 12, String(umidade));

  Heltec.display->setFont(ArialMT_Plain_24);
  Heltec.display->drawString(80, 35, "%");

  Heltec.display->display();
  delay(tempoExibicao);

  Heltec.display->clear();
  Heltec.display->display();
}


void enviarMensagemPostagem (int responseCode, int tempoExibicao, boolean sucesso) {

  Timezone brasil;
  brasil.setLocation("America/Sao_Paulo");

  Heltec.display->setContrast(255);
  Heltec.display->clear();


  Heltec.display->drawXbm(5, 5, elastic_width, elastic_height, elastic_bits);

  Heltec.display->display();
  delay(tempoExibicao);

  Heltec.display->clear();
  Heltec.display->display();


  if (sucesso) {
    Heltec.display->drawXbm(0, 0, ok_width, ok_height, ok_bits);

    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->drawString(55, 5, "Response code:");

    Heltec.display->setFont(ArialMT_Plain_24);
    Heltec.display->drawString(55, 20, String(responseCode));

    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->drawString(5, 52, "Registrado em: " + brasil.dateTime("H:i:s"));

    Heltec.display->display();
    delay(tempoExibicao);

  } else {

    Heltec.display->drawXbm(0, 0, error_width, error_height, error_bits);

    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->drawString(55, 5, "Response code:");

    Heltec.display->setFont(ArialMT_Plain_24);
    Heltec.display->drawString(55, 20, String(responseCode));

    Heltec.display->setFont(ArialMT_Plain_10);
    //Define timezone para NTC
    Heltec.display->drawString(8, 52, "Registrado em: " + brasil.dateTime("H:i:s"));

    Heltec.display->display();
    delay(tempoExibicao);


  }

  Heltec.display->clear();
  Heltec.display->display();
}


void enviarMensagemTempo (int segundos, int tempoExibicao) {

  Heltec.display->setContrast(255);
  Heltec.display->clear();


  Heltec.display->drawXbm(0, 12, clock_width, clock_height, clock_bits);

  Heltec.display->setFont(ArialMT_Plain_24);
  Heltec.display->drawString(75, 15, String(segundos) + "s");

  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(51, 50, "próxima medição");

  Heltec.display->display();
  delay(tempoExibicao);

  Heltec.display->clear();
  Heltec.display->display();
}


void enviarMensagemErroLeituraSensor (int tempoExibicao) {

  Heltec.display->setContrast(255);
  Heltec.display->clear();


  Heltec.display->drawXbm(0, 10, error_width, error_height, error_bits);


  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(55, 10, "Erro!");

  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(55, 32, "Leitura sensor");

  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(55, 42, "DHT pino " + String(DHTPIN));

  Heltec.display->display();
  delay(tempoExibicao);
}


void enviarMensagemSignal (String mensagemGrande, String ip, String ssid, int tempoExibicao) {

  Heltec.display->setContrast(255);
  Heltec.display->clear();
  Heltec.display->display();

  Heltec.display->drawXbm(0, 0, wifi_width, wifi_height, wifi_bits);

  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(35, 5, mensagemGrande);

  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 35, "IP: " + ip);

  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 50, "Rede: " + ssid);

  Heltec.display->display();
  delay(tempoExibicao);

  Heltec.display->clear();
  Heltec.display->display();
}



int wifiConnect() {
  int retries = 0;

  Serial.println("Connecting to WiFi AP..........");
  enviarMensagemTela("Conectando...", "", "", 2000, true);


  WiFi.begin(ssid, password);

  // check the status of WiFi connection to be WL_CONNECTED
  while ((WiFi.status() != WL_CONNECTED) && (retries < MAX_WIFI_INIT_RETRY)) {
    retries++;
    delay(WIFI_RETRY_DELAY);
    String progressbar = "";
    Serial.print("#");
    progressbar = progressbar + "#";
    enviarMensagemTela("Conectando...", "", progressbar, 2000, true);


    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("Connetted to ");
      Serial.print(ssid);
      Serial.print("--- IP: ");
      Serial.println(WiFi.localIP());

      sensor.redeWifi = ssid;
      sensor.ip = WiFi.localIP().toString();
      sensor.macAddress = WiFi.macAddress();

    } else if (WiFi.status() != WL_CONNECTED && retries >= MAX_WIFI_INIT_RETRY) {
      Serial.print("Error connecting to: ");
      Serial.println(ssid);
    }

  }
  Serial.println("");
  return WiFi.status(); // return the WiFi connection status
}



int obtemDadosSensor() {

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return -1;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  sensor.umidade = h;
  sensor.temperaturaCelsius = t;

  //Define timezone para NTC
  Timezone brasil;
  brasil.setLocation("America/Sao_Paulo");
  Serial.println("Hora Brasília: " + brasil.dateTime());

  sensor.timeStamp = brasil.dateTime(RFC3339_EXT);

  enviarMensagemSensor (t, h, 2000);

  //enviarMensagemTela(String(t) + "°C", "Temperatura", "", 2000, false);
  //enviarMensagemTela(String(h) + "%", "Umidade", "", 2000, false);

  return 0;

}
