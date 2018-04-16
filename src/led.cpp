#include <Arduino.h>
#include <FastLED.h>

#define qsuba(x, b)  ((x>b)?x-b:0)
CRGBPalette16 currentPalette;
TBlendType currentBlending = LINEARBLEND;

// variables
const int MAX_BRIGTHNESS = 240;
const int NIGHT_BRIGTHNESS = 20;

const int DAY_TRESHOLD = 250;
const int NIGHT_TRESHOLD = 30;

int brightness = MAX_BRIGTHNESS;
bool isActive = false;
bool overwritten = false;

struct CRGB lastCRGB = CRGB::Black;

uint8_t rainbowHue = 0;

///////////////
// BRIGTHNESS functions
///////////////

// Det Brigthness to value between min and max Brigthness
void setBrightness(int _brightness) {
  if (_brightness >= NIGHT_BRIGTHNESS and _brightness <= MAX_BRIGTHNESS) {
    //Serial.println(_brightness);
    brightness = _brightness;
    FastLED.setBrightness( brightness );
    FastLED.show();
  }
}

// Increases brightness by 10
void increaseBrightness() {
  overwritten = true;
  setBrightness(brightness + 10);
}

// Decreases brightness by 10
void decreaseBrightness() {
  overwritten = true;
  setBrightness(brightness - 10);
}

///////////////
// COLOUR functions
///////////////

// Set solid colour
void setLedColour(int num_leds, CRGB leds[], CRGB colour){
  lastCRGB = colour;
  fill_solid(leds, num_leds, colour);
  FastLED.show();
}

void setLastLedColour(int num_leds, CRGB leds[]){
  setLedColour(num_leds, leds, lastCRGB);
}

// Set solid colour BLACK
void setLedOff(int num_leds, CRGB leds[]){
  fill_solid(leds, num_leds, CRGB::Black);
  FastLED.show();
}

///////////////
// MISC functions
///////////////

// Fading
void fadeall(int num_leds, CRGB leds[]) {
	for(int i = 0; i < num_leds; i++) {
		leds[i].nscale8(190);
	}
}

// Decides if dark enough to aut enable light
bool isNight() {
  int light = analogRead(0);
	//Serial.println(light);

  if (overwritten) {
    return true;
  } else if (light < (DAY_TRESHOLD + 20) && light > (DAY_TRESHOLD - 20) || light < (NIGHT_TRESHOLD + 20) && light > (NIGHT_TRESHOLD - 20)) {
		return isActive;
  }  else {
    if (light < NIGHT_TRESHOLD) {
      //Serial.println("NIGHT");
      setBrightness(NIGHT_BRIGTHNESS);
    } else {
      //Serial.println("DAY");
      setBrightness(MAX_BRIGTHNESS);
    }
		isActive = light < DAY_TRESHOLD;
    return isActive;
  }
}

void setAutoMode(bool autoMode){
  overwritten = !autoMode;
}

///////////////
// EFFECT functions
///////////////

void increaseRed(int num_leds, CRGB leds[], int modifier){
  lastCRGB.red = lastCRGB.red + modifier;
  setLedColour(num_leds, leds, lastCRGB);
}

void increaseBlue(int num_leds, CRGB leds[], int modifier){
  lastCRGB.blue = lastCRGB.blue + modifier;
  setLedColour(num_leds, leds, lastCRGB);
}

void increaseGreen(int num_leds, CRGB leds[], int modifier){
  lastCRGB.green = lastCRGB.green + modifier;
  setLedColour(num_leds, leds, lastCRGB);
}

void setStaticRainbow(int num_leds, CRGB leds[], uint8_t start, uint8_t end){
  fill_rainbow(leds, num_leds, start, end);
}

void setRainbow(int num_leds, CRGB leds[], uint8_t hue){
  fill_rainbow(leds, num_leds, hue, 5);
}

void setPinkGradient(int num_leds, CRGB leds[]){
  fill_gradient_RGB(leds, num_leds, CRGB::Red, CRGB::DarkMagenta);
}


// Cerrylon effect
void setCerrylon(int num_leds, CRGB leds[], int delayMS) {
	static uint8_t hue = 0;
	// First slide the led in one direction
	for(int i = 0; i < num_leds; i++) {
		// Set the i'th led to red
		leds[i] = CHSV(hue++, 255, 255);
		FastLED.show();
		fadeall(num_leds, leds);
		// Wait a little bit before we loop around and do it again
		delay(delayMS);
	}

	// Now go in the other direction.
	for(int i = (num_leds)-1; i >= 0; i--) {
		// Set the i'th led to red
		leds[i] = CHSV(hue++, 255, 255);
		// Show the leds
		FastLED.show();
		fadeall(num_leds, leds);
		// Wait a little bit before we loop around and do it again
		delay(delayMS);
	}
}

// Copied from https://github.com/atuline/FastLED-Demos
void rainbow_beat(int num_leds, CRGB leds[]) {
  uint8_t beatA = beatsin8(17, 0, 255);                        // Starting hue
  uint8_t beatB = beatsin8(13, 0, 255);
  fill_rainbow(leds, num_leds, (beatA+beatB)/2, 8);            // Use FastLED's fill_rainbow routine.
}

// Copied from https://github.com/atuline/FastLED-Demos
void dot_beat(int num_leds, CRGB leds[]) {
  int8_t fadeval = 224;
  uint8_t bpm = 15;
  uint8_t inner = beatsin8(bpm, num_leds/4, num_leds/4*3);    // Move 1/4 to 3/4
  uint8_t outer = beatsin8(bpm, 0, num_leds-1);               // Move entire length
  uint8_t middle = beatsin8(bpm, num_leds/3, num_leds/3*2);   // Move 1/3 to 2/3

  leds[middle] = CRGB::Red;
  leds[inner] = CRGB::DarkMagenta;
  leds[outer] = CRGB::Aqua;

  nscale8(leds, num_leds, fadeval);                             // Fade the entire array. Or for just a few LED's, use  nscale8(&leds[2], 5, fadeval);

}

void flash(int num_leds, CRGB leds[]) {
  // Turn the LED on, then pause
  setLedColour(num_leds, leds, CRGB::DarkMagenta);
  delay(500);
  // Now turn the LED off, then pause
  setLedOff(num_leds, leds);
  delay(500);
}

// Copied from https://github.com/atuline/FastLED-Demos
void mover(int num_leds, CRGB leds[]) {
  int thisfade = 190;
  int thisdelay = 100;
  uint8_t secondHand = (millis() / 1000) % 15;
  static uint8_t lastSecond = 99;
  if (lastSecond != secondHand) {
    lastSecond = secondHand;
    switch(secondHand) {
      case  0: thisdelay=20; thisfade=240; break;
      case  5: thisdelay=50; thisfade=128; break;
      case 10: thisdelay=100; thisfade=64; break;
      case 15: break;
    }
  }
  static uint8_t hue = 0;
  for (int i = 0; i < num_leds; i++) {
    leds[i] += CHSV(hue, 255, 255);
    leds[(i+5) % num_leds] += CHSV(hue+85, 255, 255);
    leds[(i+10) % num_leds] += CHSV(hue+170, 255, 255);
    show_at_max_brightness_for_power();
    fadeToBlackBy(leds, num_leds, thisfade);
    delay(thisdelay);
  }
}

void fade(int num_leds, CRGB leds[], int hue) {
  rainbowHue = rainbowHue + hue;
  fill_solid(leds, num_leds, CHSV(rainbowHue, 255, 255));
  FastLED.show();
}

// copied from https://github.com/Simplify/arduino-led-strip/blob/master/arduino-led-strip.ino
void twinkle(int num_leds, CRGB leds[], int max_leds, boolean random_color) {
  int amount = 1;
  int temp_leds[max_leds];
  memset(leds, 0, num_leds * 3);
  memset(temp_leds, 0, max_leds * 2);
  for (int i = 0; i < max_leds; i++) {
    leds[temp_leds[i]] = CRGB::Black;
    int random_led = random(num_leds);
    temp_leds[i] = random_led;
    if (random_color) {
      leds[random_led] = CHSV(random(0, 255), random(200, 255), random(0, 255)); // I prefer high saturation
    } else {
      leds[random_led] = CRGB::Red;
    }
    FastLED.show();
    delay(110);
  }
}

// copied from https://github.com/Simplify/arduino-led-strip/blob/master/arduino-led-strip.ino
void fire(int num_leds, CRGB leds[]) {
  int r = 156;
  int g = 52;
  int b = 0;
  memset(leds, 0, num_leds * 3);
  for (int x = 0; x < num_leds; x++) {
    int flicker = random(0, 150);
    int r1 = r - flicker;
    int g1 = g - flicker;
    int b1 = b - flicker;
    if (g1 < 0) g1 = 0;
    if (r1 < 0) r1 = 0;
    if (b1 < 0) b1 = 0;
    leds[x].r = r1;
    leds[x].g = g1;
    leds[x].b = b1;
  }
  FastLED.show();
  delay(random(100, 250));
}

void bars(int num_leds, CRGB leds[]) {
  for (int i = 0; i < num_leds; i++) {
    leds[i] = CHSV(random(0, 255), random(200, 255), random(0, 255));
    FastLED.show();
    FastLED.delay(300);
  }
}

void applause(int num_leds, CRGB leds[]) {                                                 // This is the heart of this program. Sure is short. . . and fast.
  static uint16_t lastPixel = 0;
  fadeToBlackBy( leds, num_leds, 32);
  leds[lastPixel] = CHSV(random8(HUE_BLUE,HUE_PURPLE),255,255);
  lastPixel = random16(num_leds);
  leds[lastPixel] = CRGB::White;
  FastLED.show();
  FastLED.delay(30);
}

// copied from https://gist.github.com/kriegsman/841c8cd66ed40c6ecaae
void moveEffect(int num_leds, CRGB leds[], int movingEffect) {
  lastCRGB = CRGB::Black;
  switch (movingEffect) {
    case 1:   // Quick
      setCerrylon(num_leds, leds, 40);
      break;
    case 2:   // Slow
      setCerrylon(num_leds, leds, 60);
      break;
    case 3:   // DIY2
      setRainbow(num_leds, leds, rainbowHue++);
      break;
    case 4:   // DIY4
      rainbow_beat(num_leds, leds);
      break;
    case 5:   // DIY5
      dot_beat(num_leds, leds);
      break;
    case 6:   // DIY6
      mover(num_leds, leds);
      break;
    case 7:   // FLASH
      applause(num_leds, leds);
      break;
    case 8:   // JUMP3
      twinkle(num_leds, leds, 10, true);
      break;
    case 9:   // JUMP7
      fire(num_leds, leds);
      break;
    case 10:   // FADE3
      bars(num_leds, leds);
      break;
    case 11:   // FADE7
      //applause(num_leds, leds);
      break;

    case 12:   // DIY1
      setStaticRainbow(num_leds, leds, 100, 30);
      break;
    case 13:   // FADE3
      setPinkGradient(num_leds, leds);
      break;
    case 14:   // FADE7
      fade(num_leds, leds, 7);
      break;
  }
}
