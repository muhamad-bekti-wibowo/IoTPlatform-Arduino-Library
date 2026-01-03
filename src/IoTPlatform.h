/*
 * IoTPlatformSimple.h - Blynk-style Simple API for IoT Platform
 * 
 * This wrapper makes IoTPlatform as easy to use as Blynk!
 * Just 2 lines for setup, 2 lines for each widget callback.
 * 
 * Author: IoT Platform Team
 * Version: 2.0.1 - Fixed typedef conflict
 */

#ifndef IOT_PLATFORM_SIMPLE_H
#define IOT_PLATFORM_SIMPLE_H

#include "IoTPlatform.h"
#include <WiFi.h>
#include <map>

// ============================================
// GLOBAL INSTANCE - Access from anywhere
// ============================================
class IoTPlatformSimple;
extern IoTPlatformSimple IOT;

// ============================================
// CALLBACK TYPES (renamed to avoid conflict)
// ============================================
typedef void (*IoTWriteCallback)(const char* value);
typedef void (*IoTNumericCallbackSimple)(int value);

// ============================================
// SIMPLIFIED IoT PLATFORM CLASS
// ============================================
class IoTPlatformSimple {
private:
    IoTPlatform _iot;
    String _server;
    String _token;
    String _ssid;
    String _password;
    
    // Callback registries
    std::map<String, IoTWriteCallback> _stringCallbacks;
    std::map<String, IoTNumericCallbackSimple> _numericCallbacks;
    
    // Internal handlers
    static void _handleMessage(const char* pin, const char* value) {
        String pinStr = String(pin);
        if (IOT._stringCallbacks.find(pinStr) != IOT._stringCallbacks.end()) {
            IOT._stringCallbacks[pinStr](value);
        }
    }
    
    static void _handleNumeric(const char* pin, int value) {
        String pinStr = String(pin);
        if (IOT._numericCallbacks.find(pinStr) != IOT._numericCallbacks.end()) {
            IOT._numericCallbacks[pinStr](value);
        }
    }

public:
    // Current pin and value for macro access
    const char* _currentValue;
    int _currentIntValue;
    
    IoTPlatformSimple() : _currentValue(""), _currentIntValue(0) {}
    
    // ============================================
    // SETUP FUNCTIONS
    // ============================================
    
    // Set WiFi credentials
    void setWiFi(const char* ssid, const char* password) {
        _ssid = String(ssid);
        _password = String(password);
    }
    
    // Connect to WiFi
    bool connectWiFi() {
        if (_ssid.length() == 0) {
            Serial.println("[WiFi] Error: WiFi credentials not set!");
            Serial.println("[WiFi] Use: IOT_WIFI(\"SSID\", \"password\")");
            return false;
        }
        
        Serial.println("\n[WiFi] Connecting...");
        Serial.print("[WiFi] SSID: ");
        Serial.println(_ssid);
        
        WiFi.begin(_ssid.c_str(), _password.c_str());
        
        int attempts = 0;
        while (WiFi.status() != WL_CONNECTED && attempts < 30) {
            delay(500);
            Serial.print(".");
            attempts++;
        }
        
        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("\n[WiFi] ✓ Connected!");
            Serial.print("[WiFi] IP: ");
            Serial.println(WiFi.localIP());
            return true;
        } else {
            Serial.println("\n[WiFi] ✗ Failed!");
            return false;
        }
    }
    
    // Set server and token
    void setServer(const char* server, const char* token) {
        _server = String(server);
        _token = String(token);
    }
    
    // Connect to IoT Platform
    bool connect() {
        if (_server.length() == 0 || _token.length() == 0) {
            Serial.println("[IoT] Error: Server/token not set!");
            Serial.println("[IoT] Use: IOT_CONNECT(\"server\", \"token\")");
            return false;
        }
        
        // Auto-connect WiFi if not connected
        if (WiFi.status() != WL_CONNECTED) {
            if (!connectWiFi()) {
                return false;
            }
        }
        
        Serial.println("\n[IoT] Connecting to platform...");
        Serial.print("[IoT] Server: ");
        Serial.println(_server);
        
        // Build full URL
        String fullUrl = _server;
        if (!fullUrl.startsWith("ws://") && !fullUrl.startsWith("wss://")) {
            fullUrl = "ws://" + fullUrl;
        }
        if (!fullUrl.endsWith("/ws")) {
            fullUrl += "/iot/ws";
        }
        
        if (_iot.begin(fullUrl.c_str(), _token.c_str())) {
            Serial.println("[IoT] ✓ Connected!");
            
            // Set up internal callbacks
            _iot.onMessage(_handleMessage);
            _iot.onNumeric(_handleNumeric);
            
            return true;
        } else {
            Serial.println("[IoT] ✗ Connection failed!");
            return false;
        }
    }
    
    // ============================================
    // CALLBACK REGISTRATION
    // ============================================
    
    void registerStringCallback(const char* pin, IoTWriteCallback callback) {
        _stringCallbacks[String(pin)] = callback;
    }
    
    void registerNumericCallback(const char* pin, IoTNumericCallbackSimple callback) {
        _numericCallbacks[String(pin)] = callback;
    }
    
    // ============================================
    // WRITE FUNCTIONS (Send data to platform)
    // ============================================
    
    void write(const char* pin, const char* value) {
        _iot.write(pin, value);
    }
    
    void write(const char* pin, String value) {
        _iot.write(pin, value.c_str());
    }
    
    void write(const char* pin, int value) {
        _iot.write(pin, value);
    }
    
    void write(const char* pin, float value) {
        _iot.write(pin, value);
    }
    
    void write(const char* pin, double value) {
        _iot.write(pin, (float)value);
    }
    
    // ============================================
    // LOOP & STATUS
    // ============================================
    
    void loop() {
        _iot.loop();
    }
    
    bool connected() {
        return _iot.connected();
    }
    
    void reconnect() {
        _iot.reconnect();
    }
};

// Global instance
IoTPlatformSimple IOT;

// ============================================
// BLYNK-STYLE MACROS
// ============================================

// Setup macros
#define IOT_WIFI(ssid, password) \
    IOT.setWiFi(ssid, password)

#define IOT_CONNECT(server, token) \
    IOT.setServer(server, token); \
    IOT.connect()

#define IOT_BEGIN() \
    IOT.connect()

// Callback macros for STRING values
#define IOT_WRITE(pin) \
    void iot_callback_##pin(const char* value); \
    bool iot_register_##pin __attribute__((unused)) = []() { \
        IOT.registerStringCallback(#pin, iot_callback_##pin); \
        return true; \
    }(); \
    void iot_callback_##pin(const char* value)

// Callback macros for NUMERIC values
#define IOT_WRITE_NUM(pin) \
    void iot_callback_num_##pin(int value); \
    bool iot_register_num_##pin __attribute__((unused)) = []() { \
        IOT.registerNumericCallback(#pin, iot_callback_num_##pin); \
        return true; \
    }(); \
    void iot_callback_num_##pin(int value)

// Parameter access macros
#define IOT_PARAM_STRING String(value)
#define IOT_PARAM_INT (value)
#define IOT_PARAM_FLOAT atof(value)

// Loop macro
#define IOT_LOOP() IOT.loop()

#endif