#include <Arduino.h>
#include <FastLED.h>

extern bool isActive;

void setLedColour(int num_leds, CRGB leds[], CRGB colour);
void setBrightness(int brightness);
void increaseBrightness();
void decreaseBrightness();
void setLedOff(int num_leds, CRGB leds[]);
void fadeall(int num_leds, CRGB leds[]);
bool isNight();

void increaseRed(int num_leds, CRGB leds[], int modifier);
void increaseGreen(int num_leds, CRGB leds[], int modifier);
void increaseBlue(int num_leds, CRGB leds[], int modifier);

void moveEffect(int num_leds, CRGB leds[], int movingEffect);

void setRainbow(int num_leds, CRGB leds[], uint8_t hue);
void setStaticRainbow(int num_leds, CRGB leds[], uint8_t start, uint8_t end);
void setPinkGradient(int num_leds, CRGB leds[]);
