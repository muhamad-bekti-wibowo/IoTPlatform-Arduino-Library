# IoTPlatform Arduino Library

Arduino library untuk koneksi mudah ke IoT Platform dengan WebSocket support untuk ESP32/ESP8266.

**Library ini menggunakan Blynk-style API!** Sangat mudah - pakai macro seperti `IOT_WIFI()`, `IOT_CONNECT()`, dan `IOT_WRITE()`.

## 📦 Fitur

- ✅ **Blynk-Style Macros** - API yang familiar dan mudah
- ✅ Koneksi WebSocket otomatis ke IoT Platform
- ✅ Auto-reconnect jika koneksi terputus
- ✅ Heartbeat/keepalive mechanism
- ✅ Support ESP32 dan ESP8266
- ✅ Kirim data dengan `IOT.write("key", value)`
- ✅ Terima data dengan callback `IOT_WRITE(pin)`

## 🚀 Instalasi

### Via Arduino IDE

1. Download library ini sebagai ZIP dari GitHub (klik tombol hijau "Code" → "Download ZIP")
2. Buka Arduino IDE
3. Pilih **Sketch** → **Include Library** → **Add .ZIP Library**
4. Pilih file ZIP yang sudah di-download
5. Restart Arduino IDE

### Via Git

```bash
cd ~/Documents/Arduino/libraries
git clone https://github.com/muhamad-bekti-wibowo/IoTPlatform-Arduino-Library.git
```

## 📝 Quick Start - Super Simple!

```cpp
#include <IoTPlatformSimple.h>

// Setup WiFi (cukup 1 baris!)
IOT_WIFI("WIFI_SSID", "WIFI_PASSWORD");

// Callback untuk menerima data dari dashboard
IOT_WRITE(led) {
    // 'value' otomatis tersedia
    int ledState = atoi(value);
    digitalWrite(LED_PIN, ledState);
    Serial.print("LED: ");
    Serial.println(ledState);
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    
    // Koneksi ke IoT Platform (1 baris!)
    IOT_CONNECT("mbektiw.my.id", "YOUR_DEVICE_TOKEN");
}

void loop() {
    IOT_LOOP();  // Jaga koneksi tetap hidup
    
    // Kirim data - sangat mudah!
    IOT.write("temperature", 25.5);
    IOT.write("humidity", 60);
    IOT.write("status", "online");
    
    delay(5000);  // Kirim setiap 5 detik
}
```

**Itu saja!** Hanya perlu:
- `IOT_WIFI()` - Setup WiFi
- `IOT_CONNECT()` - Koneksi ke platform
- `IOT_LOOP()` - Di dalam loop()
- `IOT.write()` - Kirim data
- `IOT_WRITE()` - Terima data (callback)

## 📚 Dokumentasi API

### Setup Macros

#### `IOT_WIFI(ssid, password)`

Setup WiFi credentials. Panggil **sebelum** `setup()`.

**Contoh:**
```cpp
IOT_WIFI("MyWiFi", "mypassword123");
```

#### `IOT_CONNECT(server, token)`

Koneksi ke IoT Platform. Panggil di dalam `setup()`.

**Parameter:**
- `server` - Server IoT Platform (gunakan `"mbektiw.my.id"`)
- `token` - Device token dari dashboard

**Contoh:**
```cpp
void setup() {
    IOT_CONNECT("mbektiw.my.id", "abc123def456");
}
```

### Loop Macro

#### `IOT_LOOP()`

Jaga koneksi tetap hidup. Panggil di dalam `loop()`.

**Contoh:**
```cpp
void loop() {
    IOT_LOOP();
    // code Anda...
}
```

### Kirim Data

#### `IOT.write(pin, value)`

Kirim data ke IoT Platform. Support berbagai tipe data.

**Parameter:**
- `pin` - Nama data/sensor (String)
- `value` - Nilai data (String, int, float, double)

**Contoh:**
```cpp
// Kirim String
IOT.write("status", "running");

// Kirim Integer
IOT.write("counter", 42);

// Kirim Float/Decimal
IOT.write("temperature", 25.5);
IOT.write("voltage", 3.3);
```

### Terima Data (Callbacks)

#### `IOT_WRITE(pin)`

Callback untuk menerima data STRING dari dashboard. Variable `value` otomatis tersedia.

**Contoh:**
```cpp
IOT_WRITE(led) {
    // 'value' berisi data yang dikirim dari dashboard
    Serial.print("Received: ");
    Serial.println(value);
    
    if (strcmp(value, "ON") == 0) {
        digitalWrite(LED_PIN, HIGH);
    } else {
        digitalWrite(LED_PIN, LOW);
    }
}
```

#### `IOT_WRITE_NUM(pin)`

Callback untuk menerima data NUMERIC dari dashboard. Variable `value` otomatis tersedia sebagai integer.

**Contoh:**
```cpp
IOT_WRITE_NUM(brightness) {
    // 'value' sudah dalam bentuk integer
    analogWrite(LED_PIN, value);
    Serial.print("Brightness: ");
    Serial.println(value);
}
```

### Helper Macros

Untuk convert value di dalam callback:

- `IOT_PARAM_STRING` - Convert ke String
- `IOT_PARAM_INT` - Ambil sebagai int
- `IOT_PARAM_FLOAT` - Convert ke float

**Contoh:**
```cpp
IOT_WRITE(temperature) {
    float temp = IOT_PARAM_FLOAT;
    Serial.print("Temperature: ");
    Serial.println(temp);
}
```

## 💡 Contoh Lengkap - Sensor Suhu & LED Control

```cpp
#include <IoTPlatformSimple.h>

#define LED_PIN 2
#define TEMP_SENSOR A0

// Setup WiFi
IOT_WIFI("MyWiFi", "password123");

// Callback untuk kontrol LED dari dashboard
IOT_WRITE(led) {
    if (strcmp(value, "ON") == 0) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("LED ON");
    } else {
        digitalWrite(LED_PIN, LOW);
        Serial.println("LED OFF");
    }
}

// Callback untuk brightness control
IOT_WRITE_NUM(brightness) {
    analogWrite(LED_PIN, value);
    Serial.print("Brightness: ");
    Serial.println(value);
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    
    // Koneksi ke IoT Platform
    IOT_CONNECT("mbektiw.my.id", "your-device-token-here");
    
    Serial.println("IoT Platform Ready!");
}

void loop() {
    IOT_LOOP();
    
    // Baca sensor
    float temperature = analogRead(TEMP_SENSOR) * 0.1;
    
    // Kirim ke IoT Platform
    IOT.write("temperature", temperature);
    IOT.write("status", "online");
    
    delay(5000);  // Update setiap 5 detik
}
```

## 🔧 Dependencies

Library ini membutuhkan 2 library tambahan (install via Arduino Library Manager):

1. **ArduinoJson** (v6.x atau lebih baru)
   - Buka **Tools** → **Manage Libraries**
   - Search "ArduinoJson" 
   - Install versi terbaru

2. **WebSockets** by Markus Sattler
   - Di Library Manager, search "WebSockets"
   - Pilih yang by "Markus Sattler"
   - Install

## 🌐 Cara Mendapatkan Device Token

1. Buka https://mbektiw.my.id/iot
2. Login atau buat akun baru
3. Klik tombol **"+ Add Device"**
4. Isi nama device (contoh: "ESP32 Sensor")
5. Pilih tipe device (ESP32/ESP8266)
6. **Copy token** yang muncul
7. Paste token tersebut di code Arduino Anda

## 📱 Monitoring & Control

### Monitoring Data
Setelah device terkoneksi dan mengirim data:
1. Buka dashboard di https://mbektiw.my.id/iot
2. Lihat device Anda di daftar "My Devices"
3. Klik device untuk melihat data real-time
4. Data akan update otomatis

### Kontrol Device dari Dashboard
Untuk mengontrol device (LED, relay, dll):
1. Gunakan callback `IOT_WRITE(pin)` di code Arduino
2. Kirim data dari dashboard web
3. Callback akan otomatis dipanggil
4. Device akan merespon sesuai code Anda

## 📋 API Reference Lengkap

### Setup (dipanggil sekali)
```cpp
IOT_WIFI("ssid", "password")      // Set WiFi credentials
IOT_CONNECT("server", "token")    // Koneksi ke platform
```

### Loop (dipanggil terus-menerus)
```cpp
IOT_LOOP()                        // Jaga koneksi
```

### Kirim Data
```cpp
IOT.write("pin", value)           // Kirim data (String/int/float)
```

### Terima Data (Callbacks)
```cpp
IOT_WRITE(pin) { ... }            // Callback untuk String
IOT_WRITE_NUM(pin) { ... }        // Callback untuk Numeric
```

### Helper Functions
```cpp
IOT.connected()                   // Cek status koneksi
IOT.reconnect()                   // Reconnect manual
```

## ❓ Troubleshooting

### Device tidak terkoneksi?
- Pastikan WiFi SSID dan password benar
- Pastikan device token benar (copy dari dashboard)
- Cek Serial Monitor untuk pesan error
- Pastikan server adalah `"mbektiw.my.id"` (tanpa http/ws)

### Data tidak muncul di dashboard?
- Pastikan `IOT_LOOP()` dipanggil di dalam `loop()`
- Cek koneksi internet
- Pastikan delay tidak terlalu pendek (minimal 1 detik)

### Callback tidak jalan?
- Pastikan callback `IOT_WRITE()` ditulis **sebelum** `setup()`
- Pastikan nama pin sama dengan yang dikirim dari dashboard
- Cek Serial Monitor untuk debug

### WiFi sering disconnect?
- Library sudah auto-reconnect, tunggu beberapa detik
- Pastikan sinyal WiFi cukup kuat
- Cek apakah router stabil

## 📄 License

MIT License - bebas digunakan untuk project apapun!

## 🤝 Contributing

Ada ide atau menemukan bug? Silakan buat issue atau pull request di GitHub!

## 📧 Support

Jika ada pertanyaan atau masalah:
- Buat issue di GitHub repository ini
- Atau hubungi via email: mbektiwibowo@gmail.com

---

**Dibuat dengan ❤️ untuk komunitas IoT Indonesia**
