#include <WiFiManager.h>        // Library WiFiManager
#include <PubSubClient.h>       // Library MQTT
#include <Wire.h>               // I2C untuk RTC
#include <RTClib.h>
#include <EduIntro.h>
#include <ZMPT101B.h>
#include <ACS712.h>
 
#define RELAY_AC 25 
#define RELAY_LAMP 26 

// Inisialisasi sensor DHT
DHT11 dht11(19);

// Inisialisasi RTC
RTC_DS1307 rtc;


// Fungsi untuk menghitung kWh
float calculateKWH(float voltage, float current) {
  return (voltage * current); 
}


// MQTT broker dan topic
const char* mqtt_server = "broker.mqtt.cool"; 

// Inisialisasi WiFi dan MQTT
WiFiClient espClient;
PubSubClient client(espClient);
WiFiManager wifiManager;

// Fungsi untuk menghubungkan ke broker MQTT
void reconnect() {
  if (!client.connected()) {
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
  float humidity = 0;
  float temperature = 0;
  dht11.update();
  // Membaca kelembaban
  humidity = dht11.readHumidity();
  // Membaca suhu dalam Celsius
  temperature = dht11.readCelsius();

  ///////////////////////////////////TEGANGAN////////////////////////////
  float sum = 0;
  for (int i = 0; i < 500; i++) {
    int adcValue2 = analogRead(34);  // Baca nilai ADC
    float voltage = (adcValue2 * 3.3) / 4095;  // Konversi ke tegangan
    float centeredVoltage = voltage - (3.3 / 2); // Pusatkan di sekitar 0
    sum += centeredVoltage * centeredVoltage;
    delay(1);  // Beri jeda kecil antara sampel
  }
  // Hitung nilai RMS
  float rmsVoltage = sqrt(sum / 500);
  float volt = rmsVoltage / 0.00127045; // Konversi ke tegangan AC menggunakan faktor kalibrasi
  float U = (volt <= 120) ? 0 : volt;
  ///////////////////////////////////////////////////////////////////////


  //////////////////////////////ARUS////////////////////////////////////////////
   int adcValue_1 = analogRead(33);
  // Mengonversi nilai ADC ke tegangan
  float arus = (adcValue_1 * 3.3) / 4095;
  // Menghitung arus dalam ampere
  // Sensitivitas untuk ACS712-20A adalah 100mV/A (0.1 V per ampere)
  float sensitivity = (20.0 == 5) ? 0.185 : (20.0 == 20) ? 0.1 : 0.066;
  float I = (arus - 1.2) / sensitivity;
  ///////////////////////////////////////////////////////////////////////////////

  // Menghitung kWh
  float kWh = calculateKWH(U, I);

  // Mengambil waktu dari RTC
  DateTime now = rtc.now();

  // Periksa apakah ada pembacaan yang gagal dari DHT22
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Pengaturan relay untuk AC berdasarkan suhu
  if (temperature < 30) {
    digitalWrite(RELAY_AC, LOW);  
    Serial.println(F("AC/LED OFF (Suhu < 30°C)"));
  } else if (temperature >= 30) {
    digitalWrite(RELAY_AC, HIGH);   
    Serial.println(F("AC/LED ON (Suhu >= 30°C)"));
  }

  // Pengaturan relay untuk lampu berdasarkan waktu 
  if  (now.hour() >= 8 && now.hour() < 20){
    digitalWrite(RELAY_LAMP, LOW);  
    Serial.println(F("Lampu Ruangan OFF "));
  } else {
    digitalWrite(RELAY_LAMP, HIGH); 
    Serial.println(F("Lampu Ruangan ON "));
  }


//////////////////////////////BATERY//////////////////////////////////////////
  int adcValue = analogRead(32); // Ganti dengan pin yang digunakan
  float voltageOut = adcValue * 3.3 / 4095.0;
  float batteryVoltage = voltageOut * 9.2; // Pembalik dari pembagi tegangan
  float batteryPercentage = (batteryVoltage - 3.0) / (4.2 - 3.0) * 100.0;
  if (batteryPercentage > 1000.0) {
    batteryPercentage = 100.0;
} else if (batteryPercentage < 0.0) {
    batteryPercentage = 0.0;
}
  float Vbaterai = batteryPercentage;
///////////////////////////////////////////////////////////////////////////////////

//////////////// Cetak hasil pembacaan ke Serial Monitor//////////////////////////
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperature);
  Serial.println(F("°C"));

  // Cetak pembacaan tegangan dan arus
  Serial.print(F("Voltage: "));
  Serial.print(U, 2); 
  Serial.print(F(" V, Current: "));
  Serial.print(I, 2);
  Serial.print(F(" A, Estimated KWH: "));
  Serial.print(kWh, 2); 
  Serial.println(F(" kWh"));  
  Serial.print(F("Battery: "));
  Serial.print(Vbaterai, 2); 


String dataMessage ="tegangan:" + String(U) + "," + 
                    "arus:" + String(I) + "," + 
                    "daya:" + String(kWh) + "," + 
                    "suhu:" + String(temperature) + "," + 
                    "baterai:" + String(Vbaterai);
  // Kirim data ke broker MQTT
  client.publish("sensor", dataMessage.c_str());

  delay(2000);  // Kirim setiap 2 detik
  
}