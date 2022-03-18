#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Ultrasonic.h>

#define trigPin D1
#define echoPin D2

Ultrasonic ultrasonic(trigPin, echoPin);
long durata, cm, cm2;

const String host = "10.11.137.86";


void setup()
{
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.println();

    WiFi.begin("martino", "12345678");

    Serial.print("Tentativo di Connessione");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
}

void loop() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    durata = pulseIn(echoPin, HIGH);
    cm = 0.03431 * durata / 2; // per i pollici la formula è durata / 148;
    Serial.print("Distanza = " + String(cm) + " cm\n");
    delay(1000);


    WiFiClient client;
    Serial.println("[Connession a ...]" + String(host));

    if(client.connect (host, 8123)) {
        Serial.println("Connesso");
    } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
    }
}