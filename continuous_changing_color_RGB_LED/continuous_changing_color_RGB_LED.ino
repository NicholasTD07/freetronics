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

static const int kColorValueMin = 0;
static const int kColorValueMax = 255;

// Generate random color value from K_COLOR_MIN, to K_COLOR_MAX.
int randomColor() {
  return random(kColorValueMin, kColorValueMax);
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

bool needsIncreaseValueAtIndex(int index) {
  return currentValues[index] < targetValues[index];
}

static const int kChangeStep = 1;
// This line is moved up
// from the top of function `colorsAreNotClose`.

void increaseLedCurrentValueAtIndex(int index) {
  currentValues[index] += kChangeStep;
  checkCurrentValueAtIndex(index);
  setLed(ledPins[index], currentValues[index]);
}

void decreaseLedCurrentValueAtIndex(int index) {
  currentValues[index] -= kChangeStep;
  checkCurrentValueAtIndex(index);
  setLed(ledPins[index], currentValues[index]);
}

void checkCurrentValueAtIndex(int index) {
  if (currentValues[index] < kColorValueMin) {
    currentValues[index] = kColorValueMin;
  } else if (currentValues[index] > kColorValueMax) {
    currentValues[index] = kColorValueMax;    
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
