#include <SoftwareSerial.h>

const int AnalogX = A0;
const int AnalogY = A1;
const int ButtonPin = 2;
int ButtonState = 0;
int XPos = 0;
int YPos = 0;
String message;
const int head_TX = 10;
const int head_RX = 11;
const int SET_Pin_h = 12;
const int body_TX = 8;
const int body_RX = 9;
const int SET_Pin_b = 13;

SoftwareSerial HC12_H(head_TX, head_RX); // TX, RX
SoftwareSerial HC12_B(body_TX, body_RX);

void setup() {
  pinMode(ButtonPin, INPUT_PULLUP);
  digitalWrite(ButtonPin, HIGH);

  Serial.begin(9600); // Serial monitor

  HC12_H.begin(9600);   // HC-12 serial communication
  HC12_B.begin(9600);

  pinMode(SET_Pin_h, OUTPUT);     // SET pin
  digitalWrite(SET_Pin_h, LOW);

  HC12_H.print("AT+FU3");    // Set module to FU3 mode (default mode)
  delay(100);
  HC12_H.print("AT+C0A00");  // Set frequency to 433.4 MHz (400+04)
  delay(100);
  HC12_H.print("AT+SAVE");   // Save the configuration
  delay(100);

  digitalWrite(SET_Pin_h, HIGH);

  pinMode(SET_Pin_b, OUTPUT);     // SET pin
  digitalWrite(SET_Pin_b, LOW);

  HC12_B.print("AT+FU3");    // Set module to FU3 mode (default mode)
  delay(100);
  HC12_B.print("AT+DEFAULT");  // Set frequency to 433.4 MHz (400+04)
  delay(100);
  HC12_B.print("AT+SAVE");   // Save the configuration
  delay(100);

  digitalWrite(SET_Pin_b, HIGH);
}

void loop() {
  XPos = analogRead(AnalogX);
  YPos = analogRead(AnalogY);
  ButtonState = digitalRead(ButtonPin);
  
  if (XPos > 1000) {
    message = "1";
  }
  else if (XPos < 24) {
    message = "2";
  }
  else if (YPos > 1000) {
    message = "3";
  }
  else if (YPos < 24) {
    message = "4";
  }
  else if (ButtonState == 0) {
    message = "S";
  }
  else {
    message = "0";
  }
  
  HC12_H.println(message);
  Serial.println("Sent message (H): " + message);
}
