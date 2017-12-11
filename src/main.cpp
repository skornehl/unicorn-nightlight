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

uint64_t lastCode = 1;

#define DATA_PIN 3
#define CLOCK_PIN 2

#define NUM_LEDS 8

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
	Serial.begin(115200);
	LEDS.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RBG>(leds,NUM_LEDS);
	LEDS.setBrightness(84);
	irSetup();
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
			break;
		case (uint64_t) 16712445: 						// Off
			setLedOff(NUM_LEDS, leds);
			break;

		// Reihe 2
		case (uint64_t) 16718565: 						// Red
			setLedColour(NUM_LEDS, leds, CRGB::Red);
			break;
		case (uint64_t) 16751205: 						// Green
			setLedColour(NUM_LEDS, leds, CRGB::Green);
			break;
		case (uint64_t) 16753245: 						// Blue
			setLedColour(NUM_LEDS, leds, CRGB::Blue);
			break;
		case (uint64_t) 16720605: 						// White
			setLedColour(NUM_LEDS, leds, CRGB::White);
			break;

		// Reihe 3
		case (uint64_t) 16722645: 						// OrangeRed
			setLedColour(NUM_LEDS, leds, CRGB::OrangeRed);
			break;
		case (uint64_t) 16755285: 					// DarkOliveGreen
			setLedColour(NUM_LEDS, leds, CRGB::DarkOliveGreen);
			break;
		case (uint64_t) 16749165: 					// DarkBlue
			setLedColour(NUM_LEDS, leds, CRGB::DarkBlue);
			break;
		case (uint64_t) 16716525: 					// LightPink
			setLedColour(NUM_LEDS, leds, CRGB::LightPink);
			break;

		// Reihe 4
		case (uint64_t) 16714485: 						// Orange
			setLedColour(NUM_LEDS, leds, CRGB::Orange);
			break;
		case (uint64_t) 16747125: 					// LightSkyBlue
			setLedColour(NUM_LEDS, leds, CRGB::LightSkyBlue);
			break;
		case (uint64_t) 16757325: 					// Purple
			setLedColour(NUM_LEDS, leds, CRGB::Purple);
			break;
		case (uint64_t) 16724685: 					// HotPink
			setLedColour(NUM_LEDS, leds, CRGB::HotPink);
			break;

		// Reihe 5
		case (uint64_t) 16726215: 						// DarkOrange
			setLedColour(NUM_LEDS, leds, CRGB::DarkOrange);
			break;
		case (uint64_t) 16758855: 					// RoyalBlue
			setLedColour(NUM_LEDS, leds, CRGB::RoyalBlue);
			break;
		case (uint64_t) 16742535: 					// DarkMagenta
			setLedColour(NUM_LEDS, leds, CRGB::DarkMagenta);
			break;
		case (uint64_t) 16775175: 					// Cyan
			setLedColour(NUM_LEDS, leds, CRGB::Cyan);
			break;

		// Reihe 6
		case (uint64_t) 16718055: 						// Yellow
			setLedColour(NUM_LEDS, leds, CRGB::Yellow);
			break;
		case (uint64_t) 16750695: 					// MediumBlue
			setLedColour(NUM_LEDS, leds, CRGB::MediumBlue);
			break;
		case (uint64_t) 16734375: 					// DarkOrchid
			setLedColour(NUM_LEDS, leds, CRGB::DarkOrchid);
			break;
		case (uint64_t) 16767015: 					// MediumAquamarine
			setLedColour(NUM_LEDS, leds, CRGB::MediumAquamarine);
			break;

		// Reihe 7
		case (uint64_t) 16722135: 						// Red-Up
			increaseRed(NUM_LEDS, leds, 5);
			break;
		case (uint64_t) 16754775: 					// Green-Up
			increaseBlue(NUM_LEDS, leds, 5);
			break;
		case (uint64_t) 16738455: 					// Blue-Up
			increaseGreen(NUM_LEDS, leds, 5);
			break;
		case (uint64_t) 16771095: 					// Quick
			setCerrylon(NUM_LEDS, leds);
			break;

  }
  if (code > 0 and code != 7 and code != 21) {
    lastCode = code;
  }
}

void loop() {
	if (isNight()) {
		matchRemote(getIrCode());
	} else {
		setLedOff(NUM_LEDS, leds);
	}
	FastLED.delay(1000/30);
}
