#include <Arduino.h>
#include <FastLED.h>

// variables
const int MAX_BRIGTHNESS = 240;
const int NIGHT_BRIGTHNESS = 20;

const int DAY_TRESHOLD = 350;
const int NIGHT_TRESHOLD = 60;

int brightness = MAX_BRIGTHNESS;
bool isActive = false;
bool overwritten = false;

struct CRGB lastCRGB = CRGB::DarkMagenta;

uint8_t rainbowHue = 0;

///////////////
// BRIGTHNESS functions
///////////////

// Det Brigthness to value between min and max Brigthness
void setBrightness(int _brightness) {
  if (_brightness >= NIGHT_BRIGTHNESS and _brightness <= MAX_BRIGTHNESS) {
    brightness = _brightness;
    FastLED.setBrightness( brightness );
    FastLED.show();
  }
}

// Increases brightness by 10
void increaseBrightness() {
  setBrightness(brightness + 10);
}

// Decreases brightness by 10
void decreaseBrightness() {
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

// Set solid colour BLACK
void setLedOff(int num_leds, CRGB leds[]){
  setLedColour(num_leds, leds, CRGB::Black);
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
	// Serial.println(light);


  if (light < (DAY_TRESHOLD + 20) && light > (DAY_TRESHOLD - 20) || light < (NIGHT_TRESHOLD + 20) && light > (NIGHT_TRESHOLD - 20)) {
		return isActive;
  } else {
    if (light < NIGHT_TRESHOLD) {
      // Serial.println("NIGHT");
      setBrightness(NIGHT_BRIGTHNESS);
    } else {
      // Serial.println("DAY");
      setBrightness(MAX_BRIGTHNESS);
    }
		isActive = light < DAY_TRESHOLD;
    return isActive;
  }
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

void moveEffect(int num_leds, CRGB leds[], int movingEffect){
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
    case 4:   // Slow
      setCerrylon(num_leds, leds, 60);
      break;
    case 5:   // Slow
      setCerrylon(num_leds, leds, 60);
      break;
  }
}
