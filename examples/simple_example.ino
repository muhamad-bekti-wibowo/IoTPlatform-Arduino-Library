/*
 * Simple IoT Platform Example - Blynk Style!
 * 
 * This example shows how SIMPLE it is to use IoTPlatform
 * Just like Blynk - only a few lines of code!
 * 
 * Total code: ~40 lines (vs 220 lines in old version)
 */

#include "IoTPlatformSimple.h"

// ============================================
// KONFIGURASI - GANTI DENGAN MILIK ANDA
// ============================================
#define WIFI_SSID     "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#define IOT_SERVER    "mbektiw.my.id"
#define IOT_TOKEN     "07def4099b1e6402310360508eb62eb6b619c4c30adfc516c8f8a27a7d99fda5"

// Pin definitions
#define LED_PIN       2
#define SENSOR_PIN    34

// ============================================
// SETUP - HANYA 3 BARIS! 🎉
// ============================================
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  // Setup IoT Platform - Super simple!
  IOT_WIFI(WIFI_SSID, WIFI_PASSWORD);
  IOT_CONNECT(IOT_SERVER, IOT_TOKEN);
  
  // Send welcome message
  IOT.write("V0", "ESP32 connected! Type 'help' for commands");
}

// ============================================
// LOOP - HANYA 1 BARIS! 🎉
// ============================================
void loop() {
  IOT_LOOP();
  
  // Send sensor data every 5 seconds
  static unsigned long lastSend = 0;
  if (millis() - lastSend > 5000) {
    lastSend = millis();
    
    // Read sensor
    int sensorValue = analogRead(SENSOR_PIN);
    float temperature = 20.0 + (random(0, 150) / 10.0);
    float humidity = 40.0 + (random(0, 400) / 10.0);
    
    // Send to platform - 1 line per value!
    IOT.write("V1", sensorValue);
    IOT.write("V2", temperature);
    IOT.write("V3", humidity);
    
    Serial.println("Sensor data sent!");
  }
}

// ============================================
// CALLBACKS - 2 BARIS PER WIDGET! 🎉
// ============================================

// LED Control via Switch (D2) - NUMERIC
IOT_WRITE_NUM(D2) {
  digitalWrite(LED_PIN, value);
  IOT.write("V0", value ? "LED ON" : "LED OFF");
}

// Terminal Commands (V0) - STRING
IOT_WRITE(V0) {
  String cmd = IOT_PARAM_STRING;
  cmd.toLowerCase();
  cmd.trim();
  
  if (cmd == "led on" || cmd == "on") {
    digitalWrite(LED_PIN, HIGH);
    IOT.write("V0", "✓ LED ON");
    IOT.write("D2", 1);
  }
  else if (cmd == "led off" || cmd == "off") {
    digitalWrite(LED_PIN, LOW);
    IOT.write("V0", "✓ LED OFF");
    IOT.write("D2", 0);
  }
  else if (cmd == "status") {
    String status = "IP: " + WiFi.localIP().toString() + 
                   " | Uptime: " + String(millis()/1000) + "s";
    IOT.write("V0", status);
  }
  else if (cmd == "help") {
    IOT.write("V0", "Commands: led on/off, status, help");
  }
  else {
    IOT.write("V0", "Unknown: " + cmd);
  }
}

// PWM Slider (D5) - NUMERIC
IOT_WRITE_NUM(D5) {
  int pwm = map(value, 0, 100, 0, 255);
  analogWrite(LED_PIN, pwm);
  IOT.write("V0", "PWM: " + String(value) + "%");
}
