#include <SoftwareSerial.h>

const int AnalogX_H = A0;
const int AnalogY_H = A1;
const int AnalogX_B = A2;
const int AnalogY_B = A3;
const int ButtonPin = 2;
int ButtonState = 0;
int XPos_H = 0;
int YPos_H = 0;
int XPos_B = 0;
int YPos_B = 0;
String messageH;
String messageB;
const int head_TX = 10;
const int head_RX = 11;
const int SET_Pin_h = 12;
const int SET_Pin_b = 13;
const int body_TX = 8;
const int body_RX = 9;
const int THRESHOLD_HIGH = 800;
const int THRESHOLD_LOW = 200;


SoftwareSerial HC12_H(head_TX, head_RX); 
SoftwareSerial HC12_B(body_TX, body_RX);

void setup() {
  pinMode(ButtonPin, INPUT_PULLUP);
  digitalWrite(ButtonPin, HIGH);

  Serial.begin(9600); 

  HC12_H.begin(9600);   
  HC12_B.begin(9600);

  pinMode(SET_Pin_h, OUTPUT);    
  digitalWrite(SET_Pin_h, LOW);
  pinMode(SET_Pin_b, OUTPUT);    
  digitalWrite(SET_Pin_b, LOW);

  HC12_H.print("AT+FU3");
  delay(100);
  HC12_H.print("AT+C001"); // example channel 01 (433.5 MHz)
  delay(100);
  HC12_H.print("AT+SAVE");   // Save the configuration
  delay(100);

  HC12_B.print("AT+FU3");
  delay(100);
  HC12_B.print("AT+C010"); // example channel 01 (433.5 MHz)
  delay(100);
  HC12_B.print("AT+SAVE");   // Save the configuration
  delay(100);


  digitalWrite(SET_Pin_h, HIGH);
  digitalWrite(SET_Pin_b, HIGH);

}

void loop() {
  XPos_H = analogRead(AnalogX_H);
  YPos_H = analogRead(AnalogY_H);
  XPos_B = analogRead(AnalogX_B);
  YPos_B = analogRead(AnalogY_B);
  ButtonState = digitalRead(ButtonPin);
  
  if (XPos_H > THRESHOLD_HIGH) {
    messageH = "1";
  }
  else if (XPos_H < THRESHOLD_LOW) {
    messageH = "2";
  }
  else if (YPos_H > THRESHOLD_HIGH) {
    messageH = "3";
  }
  else if (YPos_H < THRESHOLD_LOW) {
    messageH = "4";
  }
  else if (ButtonState == 0) {
    messageH = "S";
  }
  else {
    messageH = "0";
  }


  if (XPos_B > THRESHOLD_HIGH) {
    messageB = "1";
  }
  else if (XPos_B < THRESHOLD_LOW) {
    messageB = "2";
  }
  else if (YPos_B > THRESHOLD_HIGH) {
    messageB = "3";
  }
  else if (YPos_B < THRESHOLD_LOW) {
    messageB = "4";
  }
  else {
    messageB = "0";
  }
  
HC12_H.println(messageH);
HC12_B.println(messageB);

  
  Serial.println("Sent messageH: " + messageH + "      Sent messageB: " + messageB);
}
