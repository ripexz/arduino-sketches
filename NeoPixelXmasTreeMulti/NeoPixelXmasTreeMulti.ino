// Adapted from NeoPixel library strandtest example and
// https://learn.adafruit.com/multi-tasking-the-arduino-part-3?view=all

#include <Adafruit_NeoPixel.h>

// Pattern types supported:
enum  pattern { NONE, RAINBOW_CYCLE, THEATER_CHASE, COLOR_WIPE, SCANNER, FADE };
// Patern directions supported:
enum  direction { FORWARD, REVERSE };

// NeoPattern Class - derived from the Adafruit_NeoPixel class
class NeoPatterns : public Adafruit_NeoPixel {
  public:

  // Member Variables:
  pattern  ActivePattern;  // which pattern is running
  direction Direction;     // direction to run the pattern

  unsigned long Interval;   // milliseconds between updates
  unsigned long lastUpdate; // last update of position

  uint32_t Color1, Color2;  // What colors are in use
  uint16_t TotalSteps;  // total number of steps in the pattern
  uint16_t Index;  // current step within the pattern

  void (*OnComplete)();  // Callback on completion of pattern

  // Constructor - calls base-class constructor to initialize strip
  NeoPatterns(uint16_t pixels, uint8_t pin, uint8_t type, void (*callback)())
  :Adafruit_NeoPixel(pixels, pin, type) {
    OnComplete = callback;
  }

  // Update the pattern
  void Update() {
    if((millis() - lastUpdate) > Interval) { // time to update
      lastUpdate = millis();
      switch(ActivePattern) {
        case RAINBOW_CYCLE:
          RainbowCycleUpdate();
          break;
        case THEATER_CHASE:
          TheaterChaseUpdate();
          break;
        case COLOR_WIPE:
          ColorWipeUpdate();
          break;
        case SCANNER:
          ScannerUpdate();
          break;
        case FADE:
          FadeUpdate();
          break;
        default:
          break;
      }
    }
  }

  // Increment the Index and reset at the end
  void Increment() {
    if (Direction == FORWARD) {
      Index++;
      if (Index >= TotalSteps) {
        Index = 0;
        if (OnComplete != NULL) {
          OnComplete(); // call the comlpetion callback
        }
      }
    } else { // Direction == REVERSE
      --Index;
      if (Index <= 0) {
        Index = TotalSteps-1;
        if (OnComplete != NULL) {
          OnComplete(); // call the comlpetion callback
        }
      }
    }
  }

  // Reverse pattern direction
  void Reverse() {
    if (Direction == FORWARD) {
      Direction = REVERSE;
      Index = TotalSteps-1;
    } else {
      Direction = FORWARD;
      Index = 0;
    }
  }

  // Initialize for a RainbowCycle
  void RainbowCycle(uint8_t interval, direction dir = FORWARD) {
    ActivePattern = RAINBOW_CYCLE;
    Interval = interval;
    TotalSteps = 255;
    Index = 0;
    Direction = dir;
  }

  // Update the Rainbow Cycle Pattern
  void RainbowCycleUpdate() {
    for(int i=0; i< numPixels(); i++) {
      setPixelColor(i, Wheel(((i * 256 / numPixels()) + Index) & 255));
    }
    show();
    Increment();
  }

  // Initialize for a Theater Chase
  void TheaterChase(uint32_t color1, uint32_t color2, uint8_t interval, direction dir = FORWARD) {
    ActivePattern = THEATER_CHASE;
    Interval = interval;
    TotalSteps = numPixels();
    Color1 = color1;
    Color2 = color2;
    Index = 0;
    Direction = dir;
  }

  // Update the Theater Chase Pattern
  void TheaterChaseUpdate() {
    for(int i=0; i< numPixels(); i++) {
      if ((i + Index) % 3 == 0) {
        setPixelColor(i, Color1);
      } else {
        setPixelColor(i, Color2);
      }
    }
    show();
    Increment();
  }

  // Initialize for a ColorWipe
  void ColorWipe(uint32_t color, uint8_t interval, direction dir = FORWARD) {
    ActivePattern = COLOR_WIPE;
    Interval = interval;
    TotalSteps = numPixels();
    Color1 = color;
    Index = 0;
    Direction = dir;
  }

  // Update the Color Wipe Pattern
  void ColorWipeUpdate() {
    setPixelColor(Index, Color1);
    show();
    Increment();
  }

  // Initialize for a SCANNNER
  void Scanner(uint32_t color1, uint8_t interval) {
    ActivePattern = SCANNER;
    Interval = interval;
    TotalSteps = (numPixels() - 1) * 2;
    Color1 = color1;
    Index = 0;
  }

  // Update the Scanner Pattern
  void ScannerUpdate() {
    for (int i = 0; i < numPixels(); i++) {
      if (i == Index) { // Scan Pixel to the right
        setPixelColor(i, Color1);
      } else if (i == TotalSteps - Index) { // Scan Pixel to the left
        setPixelColor(i, Color1);
      } else { // Fading tail
        setPixelColor(i, DimColor(getPixelColor(i)));
      }
    }
    show();
    Increment();
  }

  // Initialize for a Fade
  void Fade(uint32_t color1, uint32_t color2, uint16_t steps, uint8_t interval, direction dir = FORWARD) {
    ActivePattern = FADE;
    Interval = interval;
    TotalSteps = steps;
    Color1 = color1;
    Color2 = color2;
    Index = 0;
    Direction = dir;
  }

  // Update the Fade Pattern
  void FadeUpdate() {
    // Calculate linear interpolation between Color1 and Color2
    // Optimise order of operations to minimize truncation error
    uint8_t red = ((Red(Color1) * (TotalSteps - Index)) + (Red(Color2) * Index)) / TotalSteps;
    uint8_t green = ((Green(Color1) * (TotalSteps - Index)) + (Green(Color2) * Index)) / TotalSteps;
    uint8_t blue = ((Blue(Color1) * (TotalSteps - Index)) + (Blue(Color2) * Index)) / TotalSteps;

    ColorSet(Color(red, green, blue));
    show();
    Increment();
  }

  // Calculate 50% dimmed version of a color (used by ScannerUpdate)
  uint32_t DimColor(uint32_t color) {
    // Shift R, G and B components one bit to the right
    uint32_t dimColor = Color(Red(color) >> 1, Green(color) >> 1, Blue(color) >> 1);
    return dimColor;
  }

  // Set all pixels to a color (synchronously)
  void ColorSet(uint32_t color) {
    for (int i = 0; i < numPixels(); i++) {
      setPixelColor(i, color);
    }
    show();
  }

  // Returns the Red component of a 32-bit color
  uint8_t Red(uint32_t color) {
    return (color >> 16) & 0xFF;
  }

  // Returns the Green component of a 32-bit color
  uint8_t Green(uint32_t color) {
    return (color >> 8) & 0xFF;
  }

  // Returns the Blue component of a 32-bit color
  uint8_t Blue(uint32_t color) {
    return color & 0xFF;
  }

  // Input a value 0 to 255 to get a color value.
  // The colours are a transition r - g - b - back to r.
  uint32_t Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if(WheelPos < 85) {
      return Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } else if (WheelPos < 170) {
      WheelPos -= 85;
      return Color(0, WheelPos * 3, 255 - WheelPos * 3);
    } else {
      WheelPos -= 170;
      return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
  }
};

void stripComplete();

#define LED_PIN   D5
#define LED_COUNT 16
#define BTN_PIN   D7

NeoPatterns strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800, &stripComplete);

int buttonState = HIGH;
int lastButtonState = LOW;

int currentMode = 0;

bool cycling = false;
unsigned long lastCycleStart = 0;
unsigned long cyclingDelay = 10000;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 100;

// Initialize everything and prepare to start
void setup() {
  pinMode(BTN_PIN, INPUT_PULLUP);
  strip.begin();
  strip.show();
  strip.setBrightness(50);
  strip.Scanner(strip.Color(255,0,0), 50);
}

// Main loop
void loop() {
  bool updated = updateMode(digitalRead(BTN_PIN));
  strip.Update();

  if (updated) {
    cycling = false;
    switch (currentMode) {
      case 0:
        setScanner();
        break;
      case 1:
        setRainbow(10); // fast rainbow
        break;
      case 2:
        setWiper();
        break;
      case 3:
        setTheaterChase();
        break;
      case 4:
        setFade(strip.Color(255, 0, 0), strip.Color(0, 255, 0)); // fade between red and green
        break;
      case 5:
        setRainbow(50); // slow rainbow
        break;
      case 6:
        // cycle through all modes (except slow rainbow),
        // starting with wiper so it doesn't look like it's back at the start
        cycling = true;
        lastCycleStart = millis();
        setWiper();
        break;
    }
  }
}

// update current mode (debounced), returns true if mode has changed
bool updateMode(int input) {
  bool modeChanged = false;
  if (input != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (input != buttonState) {
      buttonState = input;

      if (buttonState == LOW) {
        if (currentMode >= 6) {
          currentMode = 0;
        } else {
          currentMode++;
        }
        modeChanged = true;
      }
    }
  }

  lastButtonState = input;
  return modeChanged;
}

void setScanner() {
  strip.ActivePattern = SCANNER;
  strip.Direction = FORWARD;
  strip.Interval = 55;
  strip.TotalSteps = (strip.numPixels() - 1) * 2;
}

void setRainbow(long interval) {
  strip.ActivePattern = RAINBOW_CYCLE;
  strip.Direction = FORWARD;
  strip.TotalSteps = 255;
  strip.Interval = interval;
}

void setWiper() {
  strip.ActivePattern = COLOR_WIPE;
  strip.Direction = FORWARD;
  strip.Color1 = strip.Color(0, 0, 255);
  strip.TotalSteps = strip.numPixels();
  strip.Interval = 50;
  strip.Index = 0;
}

void setTheaterChase() {
  strip.ActivePattern = THEATER_CHASE;
  strip.Direction = FORWARD;
  strip.Color1 = strip.Color(0, 255, 255);
  strip.Color2 = strip.Color(0, 0, 0);
  strip.TotalSteps = strip.numPixels() * 2;
  strip.Interval = 100;
  strip.Index = 0;
}

void setFade(uint32_t colour1, uint32_t colour2) {
  strip.ActivePattern = FADE;
  strip.Direction = FORWARD;
  strip.TotalSteps = 255;
  strip.Color1 = colour1;
  strip.Color2 = colour2;
  strip.Interval = 10;
  strip.Index = 0;
}

//------------------------------------------------------------
//Completion Routines - get called on completion of a pattern
//------------------------------------------------------------

void stripComplete() {
  uint32_t temp = strip.Color1;
  bool cycle = false;

  if (cycling && (millis() - lastCycleStart) > cyclingDelay) {
    lastCycleStart = millis();
    cycle = true;
  }

  switch (strip.ActivePattern) {
    case THEATER_CHASE:
      if (cycle) {
        setFade(strip.Color(255, 0, 0), strip.Color(0, 255, 0));
        break;
      }
      strip.Reverse();
    case SCANNER:
      if (cycle) {
        setRainbow(10);
        break;
      }
    case COLOR_WIPE:
      // randomise next colour
      strip.Color1 = strip.Wheel(random(255));
      if (cycle) { // should only affect wiper
        setTheaterChase();
        break;
      }
      break;
    case FADE:
      if (cycle) {
        setScanner();
        break;
      }
      // swap colours
      strip.Color1 = strip.Color2;
      strip.Color2 = temp;
      break;
    case RAINBOW_CYCLE:
      if (cycle) {
        setWiper();
        break;
      }
    default:
      break;
  }
}
