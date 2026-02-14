// Abstraction layer for handling various types of screens
// See Settings.h for enabling the screen of your choice
#ifndef DISPLAY_HAL_H
#define DISPLAY_HAL_H

String get_features_str();
String getChipModel();
void screen_setup();
void display_boot();
void display_info_i(const String& message);
void display_mining_results_i(const String& hashrate, const String& accepted_shares, const String& total_shares, const String& uptime, const String& node, 
                              const String& difficulty, const String& sharerate, const String& ping, const String& accept_rate);

// Abstraction layer: custom fonts, images, etc.
#if defined(DISPLAY_SSD1306)
  #include "DisplayHal_SSD1306.h"
#endif

#if defined(DISPLAY_16X2)
  #include "DisplayHal_16X2.h"
#endif

#if defined(DISPLAY_ST7735)
  #include "DisplayHal_ST3375.h"
#endif

String get_features_str() {
  String features_str = "OTA ";
  #if defined(USE_LAN)
    features_str += "LAN ";
  #endif
  #if defined(LED_BLINKING)
    features_str += "Blink ";
  #endif
  #if defined(SERIAL_PRINTING)
    features_str += "Serial ";
  #endif
  #if defined(WEB_DASHBOARD)
    features_str += "Webserver ";
  #endif
  #if defined(DISPLAY_16X2)
    features_str += "LCD16X2 ";
  #endif
  #if defined(DISPLAY_SSD1306)
    features_str += "SSD1306 ";
  #endif
  #if defined(DISPLAY_ST7735)
    features_str += "ST7735 ";
  #endif
  #if defined(USE_INTERNAL_SENSOR)
    features_str += "Int. sensor ";
  #endif
  #if defined(USE_DS18B20)
    features_str += "DS18B20 ";
  #endif
  #if defined(USE_DHT)
    features_str += "DHT ";
  #endif
  #if defined(USE_HSU07M)
    features_str += "HSU07M ";
  #endif
  return features_str;
}

String getChipModel() {
  #if CONFIG_IDF_TARGET_ESP32S2
    return String("ESP32-S2");
  #elif CONFIG_IDF_TARGET_ESP32S3
    return String("ESP32-S3");
  #elif CONFIG_IDF_TARGET_ESP32C2
    return String("ESP32-C2");
  #elif CONFIG_IDF_TARGET_ESP32C3
    return String("ESP32-C3");
  #elif CONFIG_IDF_TARGET_ESP32C6
    return String("ESP32-C6");
  #elif CONFIG_IDF_TARGET_ESP32H2
    return String("ESP32-H2");
  #elif CONFIG_IDF_TARGET_ESP32C5
    return String("ESP32-C5");
  #elif CONFIG_IDF_TARGET_ESP32P4
    return String("ESP32-P4");
  #else
    return String("ESP32");
  #endif
}
    
void display_info(const String& message) {
  #if defined(ESP32) && CORE == 2
    Serial.println("Displaying info on queue: " + message);
    DisplayData dataToSend;
    dataToSend.message = message;
    xQueueSend(displayQueue, &dataToSend, 0);
    vTaskDelay(pdMS_TO_TICKS(1));
  #else
    Serial.println("Displaying info");
    display_info_i(message);
  #endif
}

void display_mining_results(const String& hashrate, const String& accepted_shares, const String& total_shares, const String& uptime, const String& node, 
                            const String& difficulty, const String& sharerate, const String& ping, const String& accept_rate) {
  #if defined(ESP32) && CORE == 2
    Serial.println("Displaying mining results on queue");
    DisplayData dataToSend;
    dataToSend.hashrate = hashrate;
    dataToSend.accepted_shares = accepted_shares;
    dataToSend.total_shares = total_shares;
    dataToSend.uptime = uptime;
    dataToSend.node = node;
    dataToSend.difficulty = difficulty;
    dataToSend.sharerate = sharerate;
    dataToSend.ping = ping;
    dataToSend.accept_rate = accept_rate;

    xQueueSend(displayQueue, &dataToSend, 0);
    vTaskDelay(pdMS_TO_TICKS(1));
  #else
    Serial.println("Displaying mining results");
    display_mining_results_i(hashrate, accepted_shares, total_shares, uptime, node, difficulty, sharerate, ping, accept_rate);
  #endif
}

#endif