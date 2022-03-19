#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Ultrasonic.h>

#define trigPin D1
#define echoPin D2

Ultrasonic ultrasonic(trigPin, echoPin);
long durata, cm;
long now = millis();
long lastMeasure = 0;

const String host = "10.11.137.86";
const char* ssid = "martino";
const char* password = "12345678";

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
    if(!Client)
    
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    durata = pulseIn(echoPin, HIGH);
    cm = 0.03431 * durata / 2; // per i pollici la formula è durata / 148;
    Serial.print("Distanza = " + String(cm) + " cm\n");
    delay(1000);
}