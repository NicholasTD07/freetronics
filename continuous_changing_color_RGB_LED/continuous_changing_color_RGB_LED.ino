int leds[] = {5, 6, 9};
// RGB pins.
// Change this according to your own hardware setting.

void setup() {
  for(int thisLed = 0; thisLed < 3; thisLed++) {
    pinMode(leds[thisLed], OUTPUT);
    analogWrite(leds[thisLed], randomColor());
  }
}

static const int K_COLOR_MIN = 0;
static const int K_COLOR_MAX = 255;

// Generate random color value from K_COLOR_MIN, to K_COLOR_MAX.
int randomColor() {
  return random(K_COLOR_MIN, K_COLOR_MAX);
}

void loop() {
}
