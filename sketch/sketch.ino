int LED_VERMELHO = 19;
int LED_VERDE = 18;

#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "123";
const char* password = "ABC*";

const char* serverName = "https://jsonplaceholder.typicode.com/todos/1";


void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 

  Serial.println("\nConectado com Sucesso");
}


void loop() {
  if (WiFi.status() == WL_CONNECTED) {

    if(client) {
      client->setInsecure();

      HTTPClient https;

       if(https.begin(*client, serverName)) {
          int httpCode = https.GET();

          if(httpCode == 200) {
          digitalWrite(LED_VERDE, HIGH);
          digitalWrite(LED_VERMELHO, LOW);
        } else {
          digitalWrite(LED_VERMELHO, HIGH);
          digitalWrite(LED_VERDE, LOW);
        }
        https.end();
       }
    }
  } else {
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_VERDE, LOW);
  }

  delay(15000);
}