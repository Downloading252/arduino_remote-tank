#include <SoftwareSerial.h>

const int RX = 10;
const int TX = 11;
SoftwareSerial HC12(RX, TX);

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);
  Serial.println("Receiver setup complete");
}

void loop() {
  if (HC12.available()) {
    String message = HC12.readStringUntil('\n');
    message.trim();
    Serial.print("Message received: '");
    Serial.print(message);
    Serial.println("'");
  } else {
    Serial.println("No message received");
  }
  delay(500);
}
