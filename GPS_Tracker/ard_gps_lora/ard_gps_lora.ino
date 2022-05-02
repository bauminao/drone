// GPS
#include <NMEAGPS.h>

#define RX_PIN 7
#define TX_PIN 8

#include <GPSport.h>
#include <Streamers.h>

// LoRa
#include <SPI.h>              // include libraries
#include <LoRa.h>

static NMEAGPS  gps;
static gps_fix  fix;

const int csPin = 10;          // LoRa radio chip select
const int resetPin = 3;       // LoRa radio reset
const int irqPin = 1;         // change for your board; must be a hardware interrupt pin

String outgoing;              // outgoing message

byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0xBB;     // address of this device
byte destination = 0xFF;      // destination to send to
long lastSendTime = 0;        // last send time
int interval = 2000;          // interval between sends

void sendMessage(String outgoing) {
  LoRa.beginPacket();                   // start packet
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(outgoing.length());        // add payload length
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it
  msgCount++;                           // increment message ID
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;          // if there's no packet, return

  // read packet header bytes:
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length

  String incoming = "";

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }

  if (incomingLength != incoming.length()) {   // check length for error
    Serial.println("error: message length does not match length");
    return;                             // skip rest of function
  }

  // if the recipient isn't this device or broadcast,
  if (recipient != localAddress && recipient != 0xFF) {
    Serial.println("This message is not for me.");
    return;                             // skip rest of function
  }

  // if message is for this device, or broadcast, print details:
  Serial.println("Received from: 0x" + String(sender, HEX));
  Serial.println("Sent to: 0x" + String(recipient, HEX));
  Serial.println("Message ID: " + String(incomingMsgId));
  Serial.println("Message length: " + String(incomingLength));
  Serial.println("Message: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();
}

void trace_data( Print & outs, const NMEAGPS &gps, const gps_fix &fix)
{
  outs << fix;
}

static void doSomeWork()
{
  // Print all the things!
  //trace_data( Serial, gps, fix );
  trace_all( Serial, gps, fix );
  Serial.println("");
  String message = "Sending GPS data here!";
  Serial.println("Sending " + message);
  sendMessage(message);

  // parse for a packet, and call onReceive with the result:
  onReceive(LoRa.parsePacket());

} // doSomeWork


static void GPSloop()
{
  while (gps.available( gpsPort )) {
    fix = gps.read();
    doSomeWork();
  }
} // GPSloop

void setup()
{
  Serial.begin(115200);                   // initialize serial
  while (!Serial);

  Serial.print( F("NMEA.INO: started\n") );
  Serial.print( F("  fix object size = ") );
  Serial.println( sizeof(gps.fix()) );
  Serial.print( F("  gps object size = ") );
  Serial.println( sizeof(gps) );
  Serial.println( F("Looking for GPS device on " GPS_PORT_NAME) );

  #ifndef NMEAGPS_RECOGNIZE_ALL
    #error You must define NMEAGPS_RECOGNIZE_ALL in NMEAGPS_cfg.h!
  #endif

  #ifdef NMEAGPS_INTERRUPT_PROCESSING
    #error You must *NOT* define NMEAGPS_INTERRUPT_PROCESSING in NMEAGPS_cfg.h!
  #endif

  #if !defined( NMEAGPS_PARSE_GGA ) & !defined( NMEAGPS_PARSE_GLL ) & \
      !defined( NMEAGPS_PARSE_GSA ) & !defined( NMEAGPS_PARSE_GSV ) & \
      !defined( NMEAGPS_PARSE_RMC ) & !defined( NMEAGPS_PARSE_VTG ) & \
      !defined( NMEAGPS_PARSE_ZDA ) & !defined( NMEAGPS_PARSE_GST )

    Serial.println( F("\nWARNING: No NMEA sentences are enabled: no fix data will be displayed.") );

  #else
    if (gps.merging == NMEAGPS::NO_MERGING) {
      Serial.print  ( F("\nWARNING: displaying data from ") );
      Serial.print  ( gps.string_for( LAST_SENTENCE_IN_INTERVAL ) );
      Serial.print  ( F(" sentences ONLY, and only if ") );
      Serial.print  ( gps.string_for( LAST_SENTENCE_IN_INTERVAL ) );
      Serial.println( F(" is enabled.\n"
                            "  Other sentences may be parsed, but their data will not be displayed.") );
    }
  #endif

  Serial.print  ( F("\nGPS quiet time is assumed to begin after a ") );
  Serial.print  ( gps.string_for( LAST_SENTENCE_IN_INTERVAL ) );
  Serial.println( F(" sentence is received.\n"));

  //trace_header( Serial );
  Serial.flush();

  gpsPort.begin( 9600 );

  LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin

  //while (!LoRa.begin(868E6)) {             // initialize ratio at 868 MHz
  while (!LoRa.begin(915E6)) {             // initialize ratio at 915 MHz
    Serial.println("LoRa init failed. Check your connections.");
    delay(1000);
  }
  Serial.println("LoRa init succeeded.");
}

//--------------------------

void loop()
{
  GPSloop();
}
