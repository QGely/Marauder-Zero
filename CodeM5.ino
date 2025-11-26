#include <WiFi.h>

const char* ssid     = "M5TAB5";
const char* password = "password1234";
WiFiServer server(4210);

const int MAX_CLIENTS = 5;
WiFiClient clients[MAX_CLIENTS];

void setup() {
    Serial.begin(115200);

    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    Serial.println("AP started");
    Serial.print("IP: ");
    Serial.println(WiFi.softAPIP());

    server.begin();

    delay(500);
}

void loop() {
    // --- Accepter de nouveaux clients ---
    WiFiClient newClient = server.available();
    if (newClient) {
        bool added = false;
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (!clients[i] || !clients[i].connected()) {
                clients[i] = newClient;
                Serial.print("Nouveau client connecté sur slot ");
                Serial.println(i);
                added = true;
                break;
            }
        }
        if (!added) {
            Serial.println("Serveur complet : client rejeté");
            newClient.stop();
        }
    }

    // --- Lecture série → envoyer aux clients ---
    if (Serial.available()) {
        String line = Serial.readStringUntil('\n');
        line.trim();
        if (line.length() > 0) {
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (clients[i] && clients[i].connected()) {
                    clients[i].println(line);
                }
            }
        }
    }

    // --- Lecture clients → envoyer vers série ---
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] && clients[i].connected() && clients[i].available()) {
            String line = clients[i].readStringUntil('\n');
            line.trim();
            if (line.length() > 0) {
                Serial.println(line); // renvoi vers Python
            }
        }
    }
}
