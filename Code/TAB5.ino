#include <WiFi.h>

const char *ssid = "TAB5";
const char *password = "password";

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_AP);
  bool apStarted = WiFi.softAP(ssid, password);
  
  if (apStarted) {
    Serial.println("Point d'accès lancé !");
    Serial.print("SSID : ");
    Serial.println(ssid);
    Serial.print("IP : ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("Échec de création du point d'accès");
  }
}

void loop() {
  // Votre logique ici (ex. serveur web, gestion clients, etc.)
}