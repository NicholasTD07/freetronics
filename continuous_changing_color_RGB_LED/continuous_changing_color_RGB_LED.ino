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

void updateAllColorsOnLED() {
  for(int index = 0; index < 3; index++) {
    updateLedAtIndex(index);
  }
}

void updateLedAtIndex(int index) {
  if (needsIncreaseValueAtIndex(index)) {
    increaseLedCurrentValueAtIndex(index);
  } else {
    decreaseLedCurrentValueAtIndex(index);
  }
}

bool currentColorsAreCloseToTargetColors() {
  for (int index = 0; index < 3; index++) {
    if (colorsAreNotClose(currentValues[index], targetValues[index])) {
      return false;
    }
  }
  return true;
}

static const int kMultiple = 2;
static const int kChangeStep = 1;

/*
  Returns false if currentValue is not in the range of
  [targetValue - kMultiple * kChangeStep, targetValue + kMultiple * kChangeStep]

*/
bool colorsAreNotClose(int currentValue, int targetValue) {
  if (currentValue < targetValue - kMultiple * kChangeStep) {
    return false;
  } else if (currentValue > targetValue + kMultiple * kChangeStep) {
    return false;
  }
  return true;
}

void makeNewTargetColors() {
  for (int index = 0; index < 3; index++) {
    targetValues[index] = randomColor();
  }
}

static const int kDelayTime = 30; // ms
void delayForAShortTime() {
  delay(kDelayTime);
}

void setLed(int ledPin, int color) {
  analogWrite(ledPin, color);    
}
