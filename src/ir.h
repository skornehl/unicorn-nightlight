#include <IRremoteESP8266.h>
#include <IRrecv.h>

#define TIMEOUT 15U

extern IRrecv irrecv;
extern uint64_t lastcode;

void irSetup();
int getIrCode();
void serialPrintUint64ln(uint64_t _value);
