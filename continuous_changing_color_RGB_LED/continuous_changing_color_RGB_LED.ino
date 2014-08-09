int ledPins[] = {5, 6, 9};
// RGB pins.
// Change this according to your own hardware setting.

int currentValues[3];
int targetValues[3];

void setup() {
  for(int index = 0; index < 3; index++) {
    pinMode(ledPins[index], OUTPUT);

    int currentValue = randomColor();
    setLed(ledPins[index], currentValue);

    currentValues[index] = currentValue;
    targetValues[index] = randomColor();
  }
}

static const int K_COLOR_MIN = 0;
static const int K_COLOR_MAX = 255;

// Generate random color value from K_COLOR_MIN, to K_COLOR_MAX.
int randomColor() {
  return random(K_COLOR_MIN, K_COLOR_MAX);
}

void loop() {
  updateAllColorsOnLED(); // Change all three LEDs' color values
  
  // Test current colors match target color
  if (currentColorsAreCloseToTargetColors()) {
    makeNewTargetColors();
  }

  delayForAShortTime();
}

void updateAllColorsOnLED() { }

bool currentColorsAreCloseToTargetColors() { }

void makeNewTargetColors() { }

void delayForAShortTime() { }

void setLed(int ledPin, int color) {
  analogWrite(ledPin, color);    
}
