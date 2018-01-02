#include <Arduino.h>
#include <IRutils.h>

#include <IRremoteESP8266.h>
#include <IRrecv.h>

#define RECV_PIN 14

IRrecv irrecv(RECV_PIN);
decode_results results;
uint64_t lastResult = 0;

void irSetup() {
  irrecv.enableIRIn();  // Start the receiver
}

// Special output function with breakline at the end
void serialPrintUint64ln(uint64_t _value){
  serialPrintUint64(_value);
  Serial.println("");
}

uint64_t getIrCode() {
  if (irrecv.decode(&results)) {
    Serial.print("Got IR Code: ");
    serialPrintUint64ln(results.value);
    irrecv.resume();
    if (results.value > 99999999){
      results.value = lastResult;
    }
    lastResult = results.value;
    return (results.value);
  }
}
