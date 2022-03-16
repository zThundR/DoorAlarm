#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Ultrasonic.h>
Ultrasonic ultrasonic(D2, D3);

void setup()
{
    Serial.begin(115200);
    Serial.println();

    WiFi.begin("martino", "12345678");

    Serial.print("Tentativo di Connessione");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    Serial.print("Connesso, indirizzo IP: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    Serial.println("Numero: ");
    Serial.println(ultrasonic.Ranging(CM));
    delay(100);
}