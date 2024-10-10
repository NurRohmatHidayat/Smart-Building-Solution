#include "DHT.h"
#include <Wire.h>
#include <RTClib.h>

// Definisi pin dan tipe sensor
#define DHTPIN 15      // Pin data sensor DHT22 terhubung ke GPIO 15 ESP32
#define DHTTYPE DHT22  // DHT22 (AM2302)
#define VOLTAGE_PIN 34 // Pin potensiometer untuk tegangan terhubung ke GPIO 34 (A0)
#define CURRENT_PIN 35  // Pin potensiometer untuk arus terhubung ke GPIO 35 (A1)

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

void setup() {
  // Memulai komunikasi serial
  Serial.begin(115200);
  Serial.println(F("Sensor Monitoring!"));

  // Memulai sensor DHT
  dht.begin();

  // Memulai RTC
  Wire.begin();
  rtc.begin();
}

void loop() {
  // Tunggu beberapa detik di antara pembacaan sensor
  delay(2000);

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

  // Cetak waktu dari RTC
  Serial.print(F("Current Time: "));
  Serial.print(now.hour(), DEC);
  Serial.print(F(":"));
  Serial.print(now.minute(), DEC);
  Serial.print(F(":"));
  Serial.print(now.second(), DEC);
  Serial.print(F(" Date: "));
  Serial.print(now.day(), DEC);
  Serial.print(F("/"));
  Serial.print(now.month(), DEC);
  Serial.print(F("/"));
  Serial.println(now.year(), DEC);
}