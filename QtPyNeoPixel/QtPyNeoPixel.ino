// Built-in neopixel test for Adafruit QtPy M0
#include <Adafruit_NeoPixel.h>

// create a pixel strand with 1 pixel on PIN_NEOPIXEL
Adafruit_NeoPixel pixels(1, PIN_NEOPIXEL);

void setup() {
  pixels.begin();  // initialize the pixel
  pixels.setBrightness(25);
}

void showColor(int r, int g, int b) {
  pixels.setPixelColor(0, pixels.Color(r, g, b));
  pixels.show();
  delay(1000);
}

void loop() {
  showColor(255, 0, 0);
  showColor(255, 255, 0);
  showColor(0, 255, 0);
  showColor(0, 255, 255);
  showColor(0, 0, 255);
  showColor(255, 0, 255);

  // turn off the pixel
  pixels.clear();
  pixels.show();

  delay(1000);
}
