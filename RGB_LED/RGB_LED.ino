#include <FastLED.h>

#define NUM_LEDS 20
#define DATA_PIN 14
#define BRIGHTNESS 32

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );

}

void loop() {
  leds[0] = CRGB::Red;
  leds[1] = CRGB::Blue;
  leds[2] = CRGB::Green;

  FastLED.show();
}
