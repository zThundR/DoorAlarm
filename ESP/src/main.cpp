#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Ultrasonic.h>

#define trigPin D1
#define echoPin D2

Ultrasonic ultrasonic(trigPin, echoPin);
long durata, cm;


void setup()
{
    Serial.begin(9600);
    /*Serial.println();

    WiFi.begin("martino", "12345678");

    Serial.print("Tentativo di Connessione");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    Serial.print("Connesso, indirizzo IP: ");
    Serial.println(WiFi.localIP());*/

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    digitalWrite(trigPin, LOW);
}

void loop() {
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    unsigned long time = pulseIn(echoPin, HIGH);
    cm = 0.03438 * time / 2;

    Serial.println("Distanza: " + String(cm) + " cm");
    delay(500);
}