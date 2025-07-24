#include <Arduino.h>
#include <Arduino_GFX_Library.h>

// Пины RGB-подключения Waveshare ESP32‑S3 Touch LCD 7" v1.1
#define PIN_DE    40
#define PIN_VSYNC 41
#define PIN_HSYNC 39
#define PIN_PCLK  42

#define PIN_R0 45
#define PIN_R1 48
#define PIN_R2 47
#define PIN_R3 21
#define PIN_R4 14

#define PIN_G0 5
#define PIN_G1 6
#define PIN_G2 7
#define PIN_G3 15
#define PIN_G4 16
#define PIN_G5 4

#define PIN_B0 8
#define PIN_B1 3
#define PIN_B2 46
#define PIN_B3 9
#define PIN_B4 1

#define GFX_BL 2  // Пин подсветки, по умолчанию — GPIO2

// Создаем RGB-панель и дисплей
Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
  PIN_DE, PIN_VSYNC, PIN_HSYNC, PIN_PCLK,
  PIN_R0, PIN_R1, PIN_R2, PIN_R3, PIN_R4,
  PIN_G0, PIN_G1, PIN_G2, PIN_G3, PIN_G4, PIN_G5,
  PIN_B0, PIN_B1, PIN_B2, PIN_B3, PIN_B4,
  0, 8, 4, 8,   // HSYNC: polarity, front, pulse, back
  0, 8, 4, 8,   // VSYNC: polarity, front, pulse, back
  1, 16000000   // PCLK: idle low, 16 MHz
);

// rotation = 0, 1, 2, 3
Arduino_RGB_Display *gfx = new Arduino_RGB_Display(800, 480, rgbpanel, 1 /* rotation */, true /* auto flush */);

void setup() {
  Serial.begin(115200);
  if (!psramInit()) {
    Serial.println("❌ PSRAM инициализация не удалась!");
    while (1);
  } else {
    Serial.println("✅ PSRAM успешно инициализирован!");
    Serial.printf("Доступно PSRAM: %u байт\n", ESP.getPsramSize());
  }
  Serial.println("Init RGB Display...");

  if (!gfx->begin()) {
    Serial.println("Display init FAILED!");
    while (true);
  }

  gfx->fillScreen(RGB565_BLACK);

  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH); // включаем подсветку

  gfx->setCursor(100, 200);
  gfx->setTextColor(RGB565_YELLOW);
  gfx->setTextSize(3);
  gfx->println("Привет, ST7262!");
}

void loop() {
  // выводим "Hello" случайным цветом и координатами
  gfx->setCursor(random(800), random(480));
  gfx->setTextColor(random(0xFFFF), random(0xFFFF));
  gfx->setTextSize(2);
  gfx->println("Hello!");
  delay(1000);
}