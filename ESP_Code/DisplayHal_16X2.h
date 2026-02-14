#ifndef DISPLAY_HAL_16X2_H
#define DISPLAY_HAL_16X2_H

static byte duco_logo[] = {0x1E, 0x01, 0x1D, 0x05, 0x1D, 0x01, 0x1E, 0x00};
static byte check_mark[] = {0x00, 0x00, 0x00, 0x01, 0x02,0x14, 0x08, 0x00};
static byte kh[] = {0x08, 0x0A, 0x0C, 0x0A, 0x00, 0x0A, 0x0E, 0x0A};
static byte msec[] = {0x0A, 0x15, 0x11, 0x06, 0x08, 0x04, 0x02, 0x0C};

void screen_setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, duco_logo);
  lcd.createChar(1, check_mark);
  lcd.createChar(2, kh);
  lcd.createChar(3, msec);
  lcd.home();
  lcd.clear();
}

void display_boot() {
  lcd.clear();
  #if defined(ESP8266)
    lcd.print("ESP8266 ");
  #elif defined(CONFIG_FREERTOS_UNICORE)
    lcd.print("ESP32S2 ");
  #else
    lcd.print("ESP32 ");
  #endif
  #if defined(ESP8266)
    lcd.print(String(ESP.getCpuFreqMHz()).c_str());
  #else
    lcd.print(String(getCpuFrequencyMhz()).c_str());
  #endif
  lcd.print(" MHz");

  lcd.setCursor(0, 1);
  lcd.print(__DATE__);
}

void display_info_i(const String& message) {
	lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(0);
  lcd.print(" Duino-Coin ");
  lcd.print(SOFTWARE_VERSION);
  lcd.setCursor(0, 1);
  lcd.print(message);
}

void display_mining_results_i(const String& hashrate, const String& accepted_shares, const String& total_shares, const String& uptime, const String& node, 
                                const String& difficulty, const String& sharerate, const String& ping, const String& accept_rate) {
	lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(hashrate);
  lcd.setCursor(4,0);
  lcd.write(2); // kh

  lcd.setCursor(7, 0);
  lcd.print(difficulty);
  lcd.print(" diff");

  lcd.setCursor(0, 1);
  lcd.write(1); // checkmark
  lcd.print(accepted_shares);

  lcd.setCursor(7, 1);
  lcd.print(ping);
  lcd.write(3); // ms

  lcd.setCursor(12, 1);
  lcd.print(sharerate);
  lcd.print("s");
}

#endif