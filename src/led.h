#include <Arduino.h>
#include <FastLED.h>

extern bool isActive;

void setCerrylon(int num_leds, CRGB leds[]);
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

void setRainbow(int num_leds, CRGB leds[], int hue);
void setStaticRainbow(int num_leds, CRGB leds[]);
