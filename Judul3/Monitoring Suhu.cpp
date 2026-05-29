#define BLYNK_TEMPLATE_ID "//id template"
#define BLYNK_TEMPLATE_NAME "//nama template"
#define BLYNK_AUTH_TOKEN "//auth token"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials
char ssid[] = "//nama wifi";
char pass[] = "//password wifi";

#define DHTPIN D4 // Pin DHT terhubung ke D4 (GPIO2)
#define DHTTYPE DHT11 // atau DHT22 kalau Anda pakai DHT22

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor() {
float h = dht.readHumidity();
float t = dht.readTemperature();

if (isnan(h) || isnan(t)) {
Serial.println("Failed to read from DHT sensor!");
return;
}

Serial.print("Temperature: ");


Serial.print(t);
Serial.print(" °C, Humidity: ");
Serial.print(h);
Serial.println(" %");

Blynk.virtualWrite(V0, t); // Kirim suhu ke Virtual Pin V0
Blynk.virtualWrite(V1, h); // Kirim kelembaban ke Virtual Pin V1
}

BLYNK_CONNECTED() {

Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");

Blynk.setProperty(V3, "onImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");

Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");

}

void setup() {
Serial.begin(115200);
Blynk.begin(auth, ssid, pass);
dht.begin();
timer.setInterval(2000L, sendSensor); // Kirim data tiap 2 detik
}

void loop() {
Blynk.run();
timer.run();
}