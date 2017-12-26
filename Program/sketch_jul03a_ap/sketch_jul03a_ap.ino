#include <ESP8266WiFi.h>
#include <DFPlayer_Mini_Mp3.h>
#include <SoftwareSerial.h>

#define SYSTEM_LED 16 // Pin LED - pin D0 - 16
#define LED_PIN D2 // 

const char namaAP[] = "EB_INSTRUMENTS";
const char passAP[] = "1234567890";  //Set wifi password
//const char WiFiSec[] = "" //Set AP np password
WiFiServer server(80);

boolean tombolClient = 0;

void setup() {
  pinMode(SYSTEM_LED, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
  mp3_set_serial (Serial); //set softwareSerial for DFPlayer-mini mp3 module
  delay(10);
  mp3_reset();  //soft-Reset module DFPlayer
  delay(10);  //wait 1ms for mp3 module to set volume
  mp3_set_volume (80);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(namaAP, passAP);
  server.begin();
}

void loop() {
  digitalWrite(SYSTEM_LED, false);
  WiFiClient client = server.available();   // If client is connected
  if (!client) {
    return;
  }
  //Read client request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  if (req.indexOf("/tombol/0") != -1)
  {
    tombolClient = 0;
    digitalWrite(LED_PIN, true);             //led dihdupkan
    Serial.println("Tombol Client Mati");
    for (byte a = 0; a < 2; a++)
      mp3_play ();
    delay(6000);
    digitalWrite(LED_PIN, false);             //led dimatikan
    mp3_stop();
  }
  else if (req.indexOf("/tombol/1") != -1)
  {
    tombolClient = 1;
    Serial.println("Tombol Client Hidup");

  }
  client.flush();
}

