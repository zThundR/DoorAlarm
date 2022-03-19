#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Ultrasonic.h>

#define trigPin D1
#define echoPin D2

Ultrasonic ultrasonic(trigPin, echoPin);
long durata, cm;
long secondo = millis();
long ultimaMisura = 0;

const String host = "10.11.137.86";
const char* ssid = "martino";
const char* password = "12345678";
WiFiClient espClient;

void wifi() {
    delay(10);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    wifi();
}

void loop() {
    if(espClient.connect(host, 8123)) {
        while(espClient.connected()) {
            if(espClient.available()) {
                secondo = millis();
                int cmlock = 0;
                int cnt = 0;
                do {
                    if (millis() > (secondo + 1000 * cnt)) {
                        digitalWrite(trigPin, LOW);
                        delayMicroseconds(2);
                        digitalWrite(trigPin, HIGH);
                        delayMicroseconds(10);
                        digitalWrite(trigPin, LOW);
                        durata = pulseIn(echoPin, HIGH);
                        cm = 0.03431 * durata / 2; // per i pollici la formula è durata / 148;
                        Serial.print("Distanza = " + String(cm) + " cm\n");

                        if (cnt == 0)
                            cmlock = cm;

                        if((cm > cmlock - 5)&&(cm < cmlock + 5))
                            cnt++;
                        else
                            break;
                    }
                } while (cnt > 10);


                if (cnt > 10) {
                    espClient.print("Rilevato movimento.");
                }
            }
        }
    }
}