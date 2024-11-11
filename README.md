<img src="Dokumentasi/POSTER GT.png">

# GriyaTech
## Smart-Building-System-Berbasis IoT

Proyek ini bertujuan untuk mengembangkan sistem automasi cerdas berbasis IoT untuk Smart Building, menggunakan komponen utama seperti ESP32, RTC, dan berbagai sensor. ESP32 bertindak sebagai mikroprosesor utama yang mengontrol komunikasi antar sensor dan perangkat, memungkinkan pemantauan dan pengontrolan secara real-time melalui jaringan Wi-Fi. Sistem ini dilengkapi dengan RTC (Real-Time Clock) untuk menjaga sinkronisasi waktu, serta sensor suhu DHT11 yang digunakan untuk mengoptimalkan pengaturan suhu dan kelembaban di dalam gedung.

Untuk memantau konsumsi energi, digunakan sensor arus ACS712 dan sensor tegangan ZMPT101B yang secara akurat mengukur penggunaan listrik dan tegangan pada berbagai perangkat. Selain itu, Relay SPDT (3A 3,3V) berfungsi sebagai saklar otomatis yang memungkinkan pengendalian perangkat elektronik seperti lampu dan sistem pendingin. 

Dengan bantuan teknologi IoT, seluruh data dari sensor-sensor ini dikirimkan ke platform cloud, memungkinkan pemilik gedung untuk memantau penggunaan energi dan kondisi lingkungan secara langsung dari aplikasi mobile. Sistem ini dirancang untuk meningkatkan efisiensi energi, kenyamanan, serta keamanan penghuni gedung dengan mengotomatiskan berbagai fungsi dan memberikan kendali yang lebih fleksibel.

## Support By :
>- Dosen Pengampu : Akhmad Hendriawan ST., MT. (NIP.197501272002121003)
>- Mata kuliah : IoT dan Jaringan Sensor
>- Program Studi : D4 Teknik Elektronika
>- Politeknik Elektronika Negeri Surabaya<br>

## Team Member :
|      NRP      |       Nama      |    Jobdesk    |   Akun |
| :-----------:|:----------------:| :------------:| :-----:|
| 2122600003    | Raditya Giananta  | Hardware Developer       | [Radit](https://github.com/Raditya-G)
| 2122600006    | Nataratungga Xina T         |   UI/UX Designer | [Ratu](https://github.com/nataratungga)
| 2122600007    | Bisma Arya Putra         |    Programmer      | [Bisma](https://github.com/Bismaap)
| 2122600012    | Nur Rohmat Hidayat                | Project Manager | [Rohmat](https://github.com/NurRohmatHidayat)
| 2122600020    | Ezar Prasetya               | UI/UX Designer     | [Ezar](https://github.com/EzarPrasetya)
| 2122600030    | Ziyad Nur Muhammad               | 3D Designer     |[Ziyad](https://github.com/Yadnur)

#### Preview Video

https://github.com/user-attachments/assets/8750dca7-19aa-41fc-97a8-4954fc9a0d99

## Daftar Isi
- [Komponen Yang Digunakan](#Komponen-Yang-Digunakan)
- [Wiring Plan](#Wiring-Plan)
- [Hardware](#Hardware)
- [Desain 3D](#Desain-3D)
- [Program ESP32](#Program-ESP32)
- [Program Design UI/UX](#Pogram-Design-UI/UX)

 
## Komponen Yang Digunakan
1. **Hardware**<br>
    a. ESP32<br>
    b. Shield PCB<br>
    c. RTC<br>
    d. Sensor Suhu DHT11<br>
    e. Sensor Arus ACS712<br>
    f. Sensor Tegangan (ZMPT101B)<br>
    g. Relay SPDT (3A 3,3V)<br>

2. **Software**<br>
    a. Arduino ide<br>
    b. KiCad<br>
    c. Inventor<br>
    d. Visual Studio Code (VSC)<br>
    e. Eagle<br>

3. **Alat**<br>
    a. Solder<br>
    b. Timah solder<br>
    c. Kabel jumper<br>
    d. Breadboard<br>
    e. Obeng<br>
 
## Wiring Plan
>- First Floor Plan
>- <img src="Assets/First Floor Plan.jpg" width = 400>
>- Second Floor Plan
>- <img src="Assets/Second Floor Plan.jpg" width = 400>

## Link YouTube 
https://youtu.be/4Z63st0WbLA

## [Hardware](https://github.com/NurRohmatHidayat/Smart-Building-Solution/tree/main/Hardware)

Berikut ini adalah hasil skematik rangkaian Smart Building System IoT menggunakan software KiCad.
<img src="Dokumentasi/Smart Building SCH.png" width = 700>

Berikut ini adalah hasil 3D dari  rangkaian Smart Building System IoT menggunakan software KiCad.
<img src="Dokumentasi/Smart Building Board.png" width = 700>

Berikut ini adalah hasil 3D dari  rangkaian Smart Building System IoT menggunakan software KiCad.
<img src="Dokumentasi/Smart Building 3D Board.jpg" width = 700>


## [Desain 3D](https://github.com/NurRohmatHidayat/Smart-Building-Solution/tree/main/Desain%203D)

## Preview Video 3D Design

https://github.com/user-attachments/assets/e34dfbfa-0edd-4161-8904-f4dbc712b04a

Berikut adalah Link Thingivers Design 3D. Asset 3D bisa didownload pada link [Thingivers](https://www.thingiverse.com/thing:6796394)

## Block Diagram
Berikut adalah alur block diagram untuk mengirim data sensor dari publisher ke database
<img src="Dokumentasi/block diagram.png" width = 400>

## Program ESP32

Program utama dari projek ini :
- [Arduino dengan C](https://github.com/NurRohmatHidayat/Smart-Building-Solution/tree/main/Program%20ESP32/Smart%20Building/Smart%20Building/src)

Berikut adalah video demontrasi prototype hardware. 

https://github.com/user-attachments/assets/7abacf07-8daf-47ce-86e2-667d23beedc0

Simulasi ini kami menggunakan ESP32 untuk mengontrol sensor dan modul yang terhubung di breadboard. Simulasi dilakukan menggunakan Wokwi, yang memudahkan pengujian rangkaian secara virtual sebelum implementasi fisik. Rangkaian melibatkan sensor DHT11, modul relay, LED indikator, potensiometer, dan RTC untuk sinkronisasi waktu.

Relay digunakan untuk mengontrol perangkat eksternal, sementara LED menunjukkan status sistem. Simulasi ini membantu dalam debugging dan memastikan komunikasi antar komponen berjalan baik. Meskipun Wokwi tidak menyediakan semua komponen, platform ini sangat berguna untuk pengujian dan visualisasi fungsi dasar rangkaian, membantu mengidentifikasi masalah sebelum produksi fisik.


Berikut adalah video demontrasi alat menggunakan wokwi. Klik link [Video Simulasi Software](https://youtu.be/oXDYyiHHBaU "Video Simulasi Software")

## [Alur Komunikasi]

Pada proyek ini, ESP32 menggunakan Wi-Fi Manager untuk mempermudah proses koneksi ke jaringan Wi-Fi. Wi-Fi Manager memungkinkan pengguna untuk memilih dan menghubungkan ESP32 ke jaringan internet tanpa harus mengubah kode sumber setiap kali ada perubahan pada jaringan.
Berikut tampilan pada wifi manager untuk menghubungkan ESP32 ke jaringan internet
<img src="Dokumentasi/wifi manager.png">

Setelah ESP32 terhubung ke internet, modul ini akan mengirim data secara berkala ke broker MQTT (dalam hal ini menggunakan broker Cool MQTT). Broker MQTT berfungsi sebagai perantara yang memungkinkan ESP32 mengirim data ke sistem lain dalam arsitektur ini.
berikut tampilan broker.mqtt.cool yang menerima data sensor dari publisher ESP32
<img src="Dokumentasi/broker mqtt cool.jpg">

Node-RED digunakan sebagai back end untuk proyek web kami, yang berfungsi mengelola aliran data dan pemrosesannya. Data yang ditampilkan pada antarmuka web berasal dari broker MQTT di mqtt.cool, di mana Node-RED berlangganan ke topik yang relevan, memproses data sesuai kebutuhan, dan menyajikannya ke front end. Pengaturan ini memungkinkan penanganan data secara real-time dan integrasi yang efisien dengan platform web kami.

Berikut adalah alur dari program Node Red yang berfungsi untuk menerima data mqtt.cool kemudian disimpan pada database Mysql.
<img src="Dokumentasi/Node Red.png">

Berikut ini adalah program untuk Back-end Smart Building System IoT menggunakan Node-RED [Node-RED](https://github.com/NurRohmatHidayat/Smart-Building-Solution/tree/main/UI/UX%20Designer)

Berikut ini adalah program untuk WEB Smart Building System IoT menggunakan bahasa HTML [Program](https://github.com/NurRohmatHidayat/Smart-Building-Solution/tree/main/UI/UX%20Designer/node-red)
