/*
 * config.h - File konfigurasi untuk mbektiw.my.id
 * 
 * Pisahkan konfigurasi dari kode utama untuk memudahkan setup
 */

#ifndef CONFIG_H
#define CONFIG_H

// ============================================
// KONFIGURASI WiFi
// ============================================
// Ganti dengan kredensial WiFi Anda
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// Timeout WiFi (detik)
#define WIFI_TIMEOUT 30

// ============================================
// KONFIGURASI IoT Platform
// ============================================
// Server mbektiw.my.id
// Gunakan wss:// untuk HTTPS atau ws:// untuk HTTP
#define IOT_SERVER "wss://mbektiw.my.id/ws"

// Token autentikasi device Anda
#define IOT_TOKEN "07def4099b1e6402310360508eb62eb6b619c4c30adfc516c8f8a27a7d99fda5"

// ============================================
// KONFIGURASI PIN
// ============================================
#define LED_BUILTIN_PIN 2    // LED built-in ESP32
#define LED_EXTERNAL_PIN 5   // LED eksternal (PWM capable)
#define SENSOR_PIN 34        // Pin sensor analog
#define BUTTON_PIN 0         // Pin button (BOOT button)

// ============================================
// KONFIGURASI SENSOR
// ============================================
// Interval pengiriman data sensor (milliseconds)
#define SENSOR_INTERVAL 5000  // 5 detik

// Simulasi atau sensor asli
#define USE_REAL_SENSOR false  // Set true jika pakai sensor asli

// Jika pakai DHT22
#define DHT_PIN 4
#define DHT_TYPE DHT22

// Jika pakai DS18B20
#define ONE_WIRE_BUS 4

// ============================================
// KONFIGURASI VIRTUAL PIN
// ============================================
// Pin untuk widget di dashboard
#define VPIN_TERMINAL "V0"      // Terminal
#define VPIN_SENSOR "V1"        // Sensor analog
#define VPIN_TEMPERATURE "V2"   // Suhu
#define VPIN_HUMIDITY "V3"      // Kelembaban
#define VPIN_PWM_DISPLAY "V4"   // Display PWM value
#define DPIN_LED_SWITCH "D2"    // Switch LED
#define DPIN_PWM_SLIDER "D5"    // Slider PWM

// ============================================
// KONFIGURASI DEBUG
// ============================================
#define DEBUG_MODE true         // Set false untuk disable debug
#define SERIAL_BAUD 115200      // Baud rate serial monitor

// ============================================
// KONFIGURASI LANJUTAN
// ============================================
#define AUTO_RECONNECT true     // Auto reconnect jika terputus
#define RECONNECT_DELAY 5000    // Delay sebelum reconnect (ms)
#define HEARTBEAT_INTERVAL 30000 // Interval heartbeat (ms)

#endif
