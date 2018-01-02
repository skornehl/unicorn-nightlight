void setLedColour(int num_leds, CRGB leds[], CRGB colour);
void increaseBrightness();
void decreaseBrightness();
void setLedOff(int num_leds, CRGB leds[]);
bool isNight();
void setAutoMode(bool autoMode);

void increaseRed(int num_leds, CRGB leds[], int modifier);
void increaseGreen(int num_leds, CRGB leds[], int modifier);
void increaseBlue(int num_leds, CRGB leds[], int modifier);
void setStaticRainbow(int num_leds, CRGB leds[], uint8_t start, uint8_t end);
void setPinkGradient(int num_leds, CRGB leds[]);

void moveEffect(int num_leds, CRGB leds[], int movingEffect);
