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
  drawScreen(1.32, "Low");
  delay(1000);

  drawScreen(4.20, "Moderate");
  delay(1000);

  drawScreen(7.6912, "High");
  delay(1000);

  drawScreen(9.00, "V.High");
  delay(1000);

  drawScreen(11.32, "Extreme");
  delay(1000);
}

void drawScreen(float value, String rating) {
  oled.clear();
  oled.setFont(FONT8X16);
  oled.setCursor(0, 0);
  oled.print(value);
  oled.setCursor(0, 2);
  oled.print(rating);
  oled.switchFrame();
}
