#include <SPI.h>
#include <LoRa.h>

const int csPin = 7;          // LoRa radio chip select
const int resetPin = 6;       // LoRa radio reset
const int irqPin = 1;         // change for your board; must be a hardware interrupt pin

void setup() {
  Serial.begin(115200);                   // initialize serial
  while (!Serial);

  Serial.println("LoRa Receiver");
  delay(1000);

  LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin
  delay(1000);

  //while (!LoRa.begin(868E6)) {
  while (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    delay(1000);
  }
  Serial.println("Works now.");
  delay(1000);
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
