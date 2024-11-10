#include <WiFiManager.h>        // Library WiFiManager
#include <PubSubClient.h>       // Library MQTT
#include <Wire.h>               // I2C untuk RTC
//#include <Adafruit_Sensor.h>    // Sesuaikan jika ada sensor spesifik untuk tegangan dan arus
//#include <Adafruit_BME280.h>    // Contoh jika ada sensor tegangan (ganti sesuai sensor kamu)

#include "DHT.h"

//********//
#define DHTPIN 15      // Pin data sensor DHT22 terhubung ke GPIO 15 ESP32
#define DHTTYPE DHT22  // DHT22 (AM2302)
#define VOLTAGE_PIN 34 // Pin potensiometer untuk tegangan terhubung ke GPIO 34 (A0)
#define CURRENT_PIN 35  // Pin potensiometer untuk arus terhubung ke GPIO 35 (A1)
#define RELAY_AC 32 // Pin relay untuk AC terhubung ke GPIO32
#define RELAY_LAMP 33 // Pin relay untuk lampu ruangan terhubung ke GPIO33

// Inisialisasi sensor DHT
DHT dht(DHTPIN, DHTTYPE);

// Inisialisasi RTC
RTC_DS1307 rtc;

// Fungsi untuk mengonversi nilai potensiometer ke volt (0 - 5V)
float convertPotToVoltage(int potValue) {
  return (potValue / 4095.0) * 5.0; // Mengubah nilai potensiometer ke volt
}

// Fungsi untuk mengonversi nilai potensiometer ke arus (0 - 5A)
float convertPotToCurrent(int potValue) {
  return (potValue / 4095.0) * 5.0; // Mengubah nilai potensiometer ke arus (misalnya 0 - 5A)
}

// Fungsi untuk menghitung kWh
float calculateKWH(float voltage, float current) {
  // Menghitung kWh dengan rumus: (Voltage * Current) * Time
  // Di sini kita anggap waktu = 1 jam (1 kWh = 1 Volt * 1 Ampere * 1 jam)
  return (voltage * current); // kWh = Volt * Ampere
}

//*******//

//// Pin untuk pengukuran
//const int voltagePin = 34;      // Pin untuk mengukur tegangan (sesuaikan pin)
//const int currentPin = 35;      // Pin untuk mengukur arus (sesuaikan pin)

// MQTT broker dan topic
const char* mqtt_server = "broker.mqtt.cool"; 
const char* topic_voltage = "sensor/voltage";
const char* topic_current = "sensor/current";
const char* topic_battery = "sensor/battery";

// Inisialisasi WiFi dan MQTT
WiFiClient espClient;
PubSubClient client(espClient);
WiFiManager wifiManager;

//// Fungsi untuk membaca sensor tegangan
//float readVoltage() {
//  int analogValue = analogRead(voltagePin);
//  float voltage = analogValue * (3.3 / 4096.0) * 11;  // Sesuaikan faktor kalibrasi sensor tegangan
//  return voltage;
//}
//
//// Fungsi untuk membaca sensor arus
//float readCurrent() {
//  int analogValue = analogRead(currentPin);
//  float current = analogValue * (3.3 / 4096.0) * 5;   // Sesuaikan dengan sensor arus yang dipakai
//  return current;
//}

// Fungsi untuk menghubungkan ke broker MQTT
void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32Client")) {
      // Jika terkoneksi, subscribe ke topik yang diperlukan
      client.subscribe("sensor/#");
    } else {
      delay(5000);  // Tunggu 5 detik sebelum mencoba lagi
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println(F("Sensor Monitoring!"));

  // Memulai sensor DHT
  dht.begin();

  // Memulai RTC
  Wire.begin();
  rtc.begin();

  // mengatur pin relay sebagai output
  pinMode(RELAY_AC, OUTPUT);
  pinMode(RELAY_LAMP, OUTPUT);

  //Matikan relay pada awalnya
  digitalWrite(RELAY_AC, HIGH);
  digitalWrite(RELAY_LAMP, HIGH);

  // Inisialisasi WiFiManager dan PubSubClient
  wifiManager.autoConnect("ESP32_AP");

  if (!wifiManager.autoConnect("ESP32_AP")) {
    Serial.println("Failed to connect to WiFi");
  } else {
    Serial.println("WiFi connected successfully");
    Serial.println("IP Address: ");
    Serial.println(WiFi.localIP());
  }
  
  client.setServer(mqtt_server, 1883);
}

void loop() {
  // Hubungkan ulang ke broker jika tidak terhubung
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Membaca kelembaban
  float humidity = dht.readHumidity();
  // Membaca suhu dalam Celsius
  float temperature = dht.readTemperature();

  // Membaca potensiometer untuk tegangan dan arus
  int voltagePotValue = analogRead(VOLTAGE_PIN);   // Baca nilai potensiometer tegangan
  int currentPotValue = analogRead(CURRENT_PIN);    // Baca nilai potensiometer arus

  // Mengonversi potensiometer ke nilai volt dan arus
  float voltage = convertPotToVoltage(voltagePotValue); // Konversi ke Volt
  float current = convertPotToCurrent(currentPotValue);   // Konversi ke Ampere

  // Menghitung kWh
  float kWh = calculateKWH(voltage, current);

  // Mengambil waktu dari RTC
  DateTime now = rtc.now();

  // Periksa apakah ada pembacaan yang gagal dari DHT22
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Pengaturan relay untuk AC berdasarkan suhu
  if (temperature < 16) {
    digitalWrite(RELAY_AC, LOW);  // Matikan AC (relay OFF)
    Serial.println(F("AC/LED OFF (Suhu < 16°C)"));
  } else if (temperature >= 27) {
    digitalWrite(RELAY_AC, HIGH);   // Nyalakan AC (relay ON)
    Serial.println(F("AC/LED ON (Suhu >= 27°C)"));
  }

  // Pengaturan relay untuk lampu berdasarkan waktu (antara jam 15:00 sampai 16:00)
  if (now.hour() >= 17 && now.hour() < 6) {
    digitalWrite(RELAY_LAMP, LOW);  // Nyalakan lampu (relay ON)
    Serial.println(F("Lampu Ruangan ON (Jam >= 17:00 dan < 6:00)"));
  } else {
    digitalWrite(RELAY_LAMP, HIGH); // Matikan lampu di luar jam 15:00 - 16:00 (relay OFF)
    Serial.println(F("Lampu Ruangan OFF (Di luar waktu 17:00 - 6:00)"));
  }

  // Cetak hasil pembacaan ke Serial Monitor
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperature);
  Serial.println(F("°C"));

  // Cetak pembacaan tegangan dan arus
  Serial.print(F("Voltage: "));
  Serial.print(voltage, 2); // Tampilkan 2 angka desimal
  Serial.print(F(" V, Current: "));
  Serial.print(current, 2); // Tampilkan 2 angka desimal
  Serial.print(F(" A, Estimated KWH: "));
  Serial.print(kWh, 2); // Tampilkan 2 angka desimal
  Serial.println(F(" kWh"));

  // Baca data tegangan, arus, dan baterai RTC
//  float voltage = readVoltage();
//  float current = readCurrent();
//  float batteryVoltage = 3.7;  // Ganti dengan pembacaan RTC jika ada

  // Kirim data ke broker MQTT
  client.publish(topic_voltage, String(voltage).c_str());
  client.publish(topic_current, String(current).c_str());
  client.publish(topic_current, String(kWh).c_str());
  client.publish(topic_battery, String(temperature).c_str());

  delay(4000);  // Kirim setiap 5 detik

  
}