#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
#define MAX_DEVICES 1

#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    3

// HARDWARE SPI
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// SOFTWARE SPI
//MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Global variables
const char msg[] = "o";
uint8_t	currAnim = 0;
const uint8_t MAX_ANIM = 1;

// Sprite Definition
const uint8_t F_ROCKET = 2;
const uint8_t W_ROCKET = 11;
const uint8_t PROGMEM rocket[F_ROCKET * W_ROCKET] = { //rocket
  0x18, 0x24, 0x42, 0x81, 0x99, 0x18, 0x99, 0x18, 0xa5, 0x5a, 0x81,
  0x18, 0x24, 0x42, 0x81, 0x18, 0x99, 0x18, 0x99, 0x24, 0x42, 0x99,
};

// Sprite Definitions
const uint8_t F_SPRITE1 = 1;
const uint8_t W_SPRITE1 = 4;
const uint8_t PROGMEM sprite1[F_SPRITE1 * W_SPRITE1] = {
  2, 7, 2, 2,
};

const uint8_t F_SPRITE2 = 1;
const uint8_t W_SPRITE2 = 5;
const uint8_t PROGMEM sprite2[F_SPRITE2 * W_SPRITE2] = {
  4, 31, 14, 4, 4,
};

struct {
  const uint8_t *data;
  uint8_t width;
  uint8_t frames;
} sprite[] = {
  { sprite1, W_SPRITE1, F_SPRITE1 },
  { sprite2, W_SPRITE2, F_SPRITE2 },
};

void setup(void) {
  P.begin();
  P.setSpeed(100);
  P.displayText(msg, PA_CENTER, P.getSpeed(), 1000, PA_SPRITE, PA_SPRITE);
  P.setSpriteData(sprite1, W_SPRITE1, F_SPRITE1, sprite1, W_SPRITE1, F_SPRITE1);
}

void loop(void) {
  if (P.displayAnimate()) {
    if (currAnim == MAX_ANIM) {
      currAnim = 0;
    } else {
      currAnim++;
    }

    P.setSpriteData(sprite[currAnim].data, sprite[currAnim].width, sprite[currAnim].frames,
      sprite[currAnim].data, sprite[currAnim].width, sprite[currAnim].frames);

    P.displayReset();
  }
}
