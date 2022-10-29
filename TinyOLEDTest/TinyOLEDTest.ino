#include <TinyWireM.h> // https://github.com/adafruit/TinyWireM
#define TINY4KOLED_QUICK_BEGIN
#include <Tiny4kOLED.h> // https://github.com/datacute/Tiny4kOLED

void setup() {
  oled.begin(64, 32, sizeof(tiny4koled_init_64x32), tiny4koled_init_64x32);
  oled.clear();
  oled.on();
  oled.switchRenderFrame();
}

void loop() {
  oled.clear();
  oled.setFont(FONT8X16);
  oled.setCursor(0, 0);
  oled.print(F("Hello"));
  oled.setCursor(0, 2);
  oled.print(F("World"));
  delay(2000);
  oled.switchFrame();

  oled.clear();
  oled.setFont(FONT6X8);
  oled.setCursor(0, 0);
  oled.print(F("ABCDEFG"));
  oled.setCursor(0, 1);
  oled.print(F("hijklmn"));
  oled.setCursor(0, 2);
  oled.print(F("0123456"));
  oled.setCursor(0, 3);
  oled.print(F("789-;:!"));
  delay(2000);
  oled.switchFrame();
}
