#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <Arduino.h>
#include <FastLED.h>
// #include <IRremoteESP8266.h>
// #include <IRrecv.h>
// #include <IRutils.h>
#include <limits.h>

// Own classes
#include <led.h>
#include <ir.h>

#define DATA_PIN 3
#define CLOCK_PIN 2

#define NUM_LEDS 8

int movingEffect = 0;
int movingEffectPlayPause = 0;

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
	Serial.begin(115200);
	LEDS.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RBG>(leds,NUM_LEDS);
	set_max_power_in_volts_and_milliamps(5, 500);               // FastLED Power management set at 5V, 500mA
	irSetup();

	// Initial colour
	setLedColour(NUM_LEDS, leds, CRGB::DarkMagenta);
}

void matchRemote(uint64_t code){

  switch (code) {
		// Reihe 1
    case (uint64_t) 16726725: 						// Increase Brigthness
      decreaseBrightness();
     break;
    case (uint64_t) 16759365: 						// Decrease Brigthness
      increaseBrightness();
      break;
		case (uint64_t) 16745085: 						// Pause
			if(movingEffect == 0){
				movingEffect = movingEffectPlayPause;
			} else {
				movingEffectPlayPause = movingEffect;
				movingEffect = 0;
			}
			break;
		case (uint64_t) 16712445: 						// Off
			setLedOff(NUM_LEDS, leds);
			movingEffect = 0;
			break;

		// Reihe 2
		case (uint64_t) 16718565: 						// Red
			setLedColour(NUM_LEDS, leds, CRGB::Red);
			movingEffect = 0;
			break;
		case (uint64_t) 16751205: 						// Green
			setLedColour(NUM_LEDS, leds, CRGB::Green);
			movingEffect = 0;
			break;
		case (uint64_t) 16753245: 						// Blue
			setLedColour(NUM_LEDS, leds, CRGB::Blue);
			movingEffect = 0;
			break;
		case (uint64_t) 16720605: 						// White
			setLedColour(NUM_LEDS, leds, CRGB::White);
			movingEffect = 0;
			break;

		// Reihe 3
		case (uint64_t) 16722645: 						// OrangeRed
			setLedColour(NUM_LEDS, leds, CRGB::OrangeRed);
			movingEffect = 0;
			break;
		case (uint64_t) 16755285: 					// DarkOliveGreen
			setLedColour(NUM_LEDS, leds, CRGB::DarkOliveGreen);
			movingEffect = 0;
			break;
		case (uint64_t) 16749165: 					// DarkBlue
			setLedColour(NUM_LEDS, leds, CRGB::DarkBlue);
			movingEffect = 0;
			break;
		case (uint64_t) 16716525: 					// LightPink
			setLedColour(NUM_LEDS, leds, CRGB::LightPink);
			movingEffect = 0;
			break;

		// Reihe 4
		case (uint64_t) 16714485: 						// Orange
			setLedColour(NUM_LEDS, leds, CRGB::Orange);
			movingEffect = 0;
			break;
		case (uint64_t) 16747125: 					// LightSkyBlue
			setLedColour(NUM_LEDS, leds, CRGB::LightSkyBlue);
			movingEffect = 0;
			break;
		case (uint64_t) 16757325: 					// Purple
			setLedColour(NUM_LEDS, leds, CRGB::Purple);
			movingEffect = 0;
			break;
		case (uint64_t) 16724685: 					// HotPink
			setLedColour(NUM_LEDS, leds, CRGB::HotPink);
			movingEffect = 0;
			break;

		// Reihe 5
		case (uint64_t) 16726215: 						// DarkOrange
			setLedColour(NUM_LEDS, leds, CRGB::DarkOrange);
			movingEffect = 0;
			break;
		case (uint64_t) 16758855: 					// RoyalBlue
			setLedColour(NUM_LEDS, leds, CRGB::RoyalBlue);
			movingEffect = 0;
			break;
		case (uint64_t) 16742535: 					// DarkMagenta
			setLedColour(NUM_LEDS, leds, CRGB::DarkMagenta);
			movingEffect = 0;
			break;
		case (uint64_t) 16775175: 					// Cyan
			setLedColour(NUM_LEDS, leds, CRGB::Cyan);
			movingEffect = 0;
			break;

		// Reihe 6
		case (uint64_t) 16718055: 						// Yellow
			setLedColour(NUM_LEDS, leds, CRGB::Yellow);
			movingEffect = 0;
			break;
		case (uint64_t) 16750695: 					// MediumBlue
			setLedColour(NUM_LEDS, leds, CRGB::MediumBlue);
			movingEffect = 0;
			break;
		case (uint64_t) 16734375: 					// DarkOrchid
			setLedColour(NUM_LEDS, leds, CRGB::DarkOrchid);
			movingEffect = 0;
			break;
		case (uint64_t) 16767015: 					// MediumAquamarine
			setLedColour(NUM_LEDS, leds, CRGB::MediumAquamarine);
			movingEffect = 0;
			break;

		// Reihe 7
		case (uint64_t) 16722135: 						// Red-Up
			increaseRed(NUM_LEDS, leds, 5);
			movingEffect = 0;
			break;
		case (uint64_t) 16754775: 					// Green-Up
			increaseBlue(NUM_LEDS, leds, 5);
			movingEffect = 0;
			break;
		case (uint64_t) 16738455: 					// Blue-Up
			increaseGreen(NUM_LEDS, leds, 5);
			movingEffect = 0;
			break;
		case (uint64_t) 16771095: 					// Quick
			movingEffect = 1;
			break;

		// Reihe 8
		case (uint64_t) 16713975: 						// Red-down
			increaseRed(NUM_LEDS, leds, 5);
			movingEffect = 0;
			break;
		case (uint64_t) 16746615: 					// Green-down
			increaseBlue(NUM_LEDS, leds, 5);
			movingEffect = 0;
			break;
		case (uint64_t) 16730295: 					// Blue-down
			increaseGreen(NUM_LEDS, leds, 5);
			movingEffect = 0;
			break;
		case (uint64_t) 16762935: 					// Slow
			movingEffect = 2;
			break;

		// Reihe 6
		case (uint64_t) 16724175: 					// DIY1
			setStaticRainbow(NUM_LEDS, leds, 0, 30);
			movingEffect = 0;
			break;
		case (uint64_t) 16756815: 					// DIY2
			movingEffect = 3;
			break;
		case (uint64_t) 16740495: 					// DIY3
			setPinkGradient(NUM_LEDS, leds);
			movingEffect = 0;
			break;
		case (uint64_t) 16773135: 					// AUTO
			movingEffect = random(1, 7);
			break;

		// Reihe 7
		case (uint64_t) 16716015: 					// DIY4
			movingEffect = 4;
			break;
		case (uint64_t) 16748655: 					// DIY5
			movingEffect = 5;
			break;
		case (uint64_t) 16732335: 					// DIY6
			movingEffect = 6;
			break;
		case (uint64_t) 16764975: 					// FLASH
			movingEffect = 7;
			break;

		// Reihe 8
		case (uint64_t) 16720095: 					// JUMP3
			movingEffect = 8;
			break;
		case (uint64_t) 16752735: 					// JUMP7
			movingEffect = 9;
			break;
		case (uint64_t) 16736415: 					// FADE3
			movingEffect = 10;
			break;
		case (uint64_t) 16769055: 					// FADE3
			movingEffect = 11;
			break;
		}
}

void loop() {
	if (isNight()) {
		matchRemote(getIrCode());
		moveEffect(NUM_LEDS, leds, movingEffect);
	} else {
		setLedOff(NUM_LEDS, leds);
	}
	FastLED.delay(1000/30);
}
