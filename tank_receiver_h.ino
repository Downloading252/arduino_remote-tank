#include <NeoSWSerial.h>
#include <ServoTimer2.h>
#include <Stepper.h>

String message;
int ServoPin = 9;
int ServoPos = 90;
int MapServoPos = map(ServoPos, 0, 180, 750, 1800);
const int stepsPerRevolution = 200;

ServoTimer2 Servo;
NeoSWSerial HC12(10, 11);
Stepper myStepper(stepsPerRevolution, 2, 3, 4, 5);

// Add variables for non-blocking delay
unsigned long previousMillis6 = 0;
unsigned long previousMillis7 = 0;
const long interval = 1000; // 1 second
bool isHigh6 = false;
bool isHigh7 = false;

void setup() {
  Serial.begin(9600); // Serial monitor
  HC12.begin(9600);   // HC-12 serial communication
  delay(100);         // Allow HC-12 to initialize

  pinMode(12, OUTPUT);     // SET pin
  digitalWrite(12, LOW);

  HC12.print("AT+FU3");    // Set module to FU3 mode (default mode)
  delay(100);
  HC12.print("AT+C0A00");  // Set frequency to 433.4 MHz (400+04)
  delay(100);
  HC12.print("AT+SAVE");   // Save the configuration
  delay(100);

  digitalWrite(12, HIGH);

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  pinMode(ServoPin, OUTPUT);
  Servo.attach(ServoPin);
  Serial.println("Setup complete");
  Servo.write(MapServoPos);

  myStepper.setSpeed(60);
}

void loop() {
  unsigned long currentMillis = millis(); // Get the current time

  if (HC12.available()) {
    message = HC12.readStringUntil('\n');
    message.trim(); // Remove leading/trailing whitespace
    Serial.println(message);

    if (message == "1") {
      ServoPos += 5;
      if (ServoPos > 180) {
        ServoPos = 180;
      }
    } else if (message == "2") {
      ServoPos -= 5;
      if (ServoPos < 0) {
        ServoPos = 0;
      }
    } else if (message == "3") {
      myStepper.step(5);
    } else if (message == "4") {
      myStepper.step(-5);
    } else if (message == "S") {
      digitalWrite(6, HIGH);
      isHigh6 = true;
      previousMillis6 = currentMillis; // Record the time when pin 6 was set HIGH
    }

    MapServoPos = map(ServoPos, 0, 180, 750, 1800);
    Servo.write(MapServoPos);
  }

  // Check if pin 6 has been HIGH for the interval duration and set it LOW
  if (isHigh6 && (currentMillis - previousMillis6 >= interval)) {
    digitalWrite(7, HIGH);
    isHigh7 = true;
    previousMillis7 = currentMillis; // Record the time when pin 7 was set HIGH
    isHigh6 = false;
  }

  // Check if pin 7 has been HIGH for the interval duration and set it LOW
  if (isHigh7 && (currentMillis - previousMillis7 >= interval)) {
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    isHigh7 = false;
  }
}
