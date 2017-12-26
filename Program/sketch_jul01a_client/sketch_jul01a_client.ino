#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define TOMBOL_PIN D2 // Pin Push Button - pin D3
#define LED_PIN 16 // Pin LED - pin D0

const char* namaAP = "EB_INSTRUMENTS"; //nama target AP
const char* passAP = "1234567890";  //password wifi
const char* host = "http://192.168.4.1";  //default ip ESP8266
String stringTombol = "0";
boolean stateTombol;

HTTPClient http;

void setup() {
  Serial.begin(9600);
  delay(10);
  Serial.print("CONNECTING TO AP: ");
  Serial.println(namaAP);
  WiFi.mode(WIFI_STA);
  WiFi.begin(namaAP, passAP);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".......");
    delay(500);
  }
  Serial.println("CONNECTED...");

  pinMode(TOMBOL_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, false);

}
void loop() {
  stateTombol = digitalRead(TOMBOL_PIN);

  if (stateTombol == 1)
    stringTombol = "1";
  else
    stringTombol = "0";

  if (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LED_PIN, true);
    WiFi.mode(WIFI_STA);
    WiFi.begin(namaAP, passAP);
    delay(500);
    Serial.print(".......");
    delay(500);
  }
  else
  {
    http.begin("192.168.4.1", 80, "/tombol/" + stringTombol);
    int httpCode1 = http.GET(); //get value
    delay(100);
    Serial.println(stringTombol);
    //Serial.println(httpCode1);
    Serial.println("");
    digitalWrite(LED_PIN, false);
  }
}
