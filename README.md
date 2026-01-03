# IoTPlatform Arduino Library

Arduino library untuk koneksi mudah ke IoT Platform dengan WebSocket support untuk ESP32/ESP8266.

## 📦 Fitur

- ✅ Koneksi WebSocket otomatis ke IoT Platform
- ✅ Auto-reconnect jika koneksi terputus
- ✅ Heartbeat/keepalive mechanism
- ✅ Mudah kirim dan terima data JSON
- ✅ Support ESP32 dan ESP8266
- ✅ API sederhana seperti Blynk

## 🚀 Instalasi

### Via Arduino IDE

1. Download library ini sebagai ZIP
2. Buka Arduino IDE
3. Pilih **Sketch** → **Include Library** → **Add .ZIP Library**
4. Pilih file ZIP yang sudah di-download
5. Restart Arduino IDE

### Via Git

```bash
cd ~/Documents/Arduino/libraries
git clone https://github.com/YOUR_USERNAME/IoTPlatform-Arduino-Library.git
```

## 📝 Quick Start

### Simple Example

```cpp
#include <IoTPlatformSimple.h>

IoTPlatformSimple iot;

void setup() {
    Serial.begin(115200);
    
    // Koneksi ke WiFi dan IoT Platform
    iot.begin("WIFI_SSID", "WIFI_PASSWORD", "YOUR_DEVICE_TOKEN");
}

void loop() {
    iot.loop();
    
    // Kirim data
    iot.write("temperature", 25.5);
    iot.write("humidity", 60);
    
    delay(5000);
}
```

### Dengan Callback untuk Menerima Data

```cpp
#include <IoTPlatform.h>

IoTPlatform iot;

void onDataReceived(String key, String value) {
    Serial.println("Received: " + key + " = " + value);
    
    if (key == "led") {
        digitalWrite(LED_PIN, value == "1" ? HIGH : LOW);
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    
    iot.begin("WIFI_SSID", "WIFI_PASSWORD", "YOUR_DEVICE_TOKEN");
    iot.onDataReceived(onDataReceived);
}

void loop() {
    iot.loop();
}
```

## 📚 Dokumentasi

### Fungsi Utama

#### `begin(ssid, password, token)`
Inisialisasi koneksi WiFi dan WebSocket ke IoT Platform.

#### `loop()`
Harus dipanggil di dalam `loop()` untuk menjaga koneksi tetap hidup.

#### `write(key, value)`
Kirim data ke IoT Platform. Support String, int, float.

```cpp
iot.write("sensor1", "active");
iot.write("temperature", 25);
iot.write("voltage", 3.3);
```

#### `onDataReceived(callback)`
Set callback function untuk menerima data dari platform.

```cpp
void onDataReceived(String key, String value) {
    // Handle data
}
```

## 🔧 Dependencies

Library ini membutuhkan:
- **ArduinoJson** (v6.x atau lebih baru)
- **WebSockets** by Markus Sattler (untuk ESP32/ESP8266)

Install via Arduino Library Manager:
1. Buka **Tools** → **Manage Libraries**
2. Search "ArduinoJson" dan install
3. Search "WebSockets" dan install

## 💡 Examples

Library ini dilengkapi dengan beberapa contoh:

- **simple_example.ino** - Contoh paling sederhana untuk memulai
- **mbektiw_example.ino** - Contoh lengkap dengan custom server
- **direct_websocket_example.ino** - Contoh koneksi WebSocket langsung

## 🌐 IoT Platform

Untuk menggunakan library ini, Anda perlu:

1. Akses ke IoT Platform di https://mbektiw.my.id/iot
2. Buat akun dan device baru
3. Copy device token
4. Gunakan token tersebut di code Arduino

## 📄 License

MIT License - bebas digunakan untuk project apapun!

## 🤝 Contributing

Contributions welcome! Silakan buat issue atau pull request.

## 📧 Support

Jika ada pertanyaan atau masalah, silakan buat issue di GitHub repository ini.
