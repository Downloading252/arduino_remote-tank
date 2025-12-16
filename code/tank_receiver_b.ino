#include <X113647Stepper.h>

const int stepsPerRevolution = 2048;
float Move = stepsPerRevolution / 100 ;

X113647Stepper right(stepsPerRevolution, 2, 3, 4, 5);
X113647Stepper left(stepsPerRevolution, 6, 7, 8, 9);

const int trigPin = 15;
const int echoPin = 14;

#define HC12 Serial1  // Mega’s Serial1 on pins 18 (TX1) and 19 (RX1)

float duration = 0;
float distance = 0;
String message = "";

unsigned long lastUltrasonicTime = 0;
const unsigned long ultrasonicInterval = 50;

String serialBuffer = "";
const int SET_Pin = 10;


void setup() {
  Serial.begin(9600);
  HC12.begin(9600);
  Serial.println("Receiver setup complete");

  right.setSpeed(60);
  left.setSpeed(60);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(SET_Pin, OUTPUT);    
  digitalWrite(SET_Pin, LOW);
  HC12.print("AT+FU3");
  delay(100);
  HC12.print("AT+C010"); // example channel 01 (433.5 MHz)
  delay(100);
  HC12.print("AT+SAVE");   // Save the configuration
  delay(100);
  digitalWrite(SET_Pin, HIGH);
}

void loop() {
  // --- Ultrasonic sensor every 50ms ---
  if (millis() - lastUltrasonicTime >= ultrasonicInterval) {
    lastUltrasonicTime = millis();

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH, 10000);  // 10ms timeout
    if (duration > 0) {
      distance = (duration * 0.0343) / 2;
    } else {
      distance = 0;
    }

    Serial.print("Distance: ");
    Serial.println(distance);
  }

  // --- HC-12 message reception ---
  while (HC12.available()) {
    char c = HC12.read();

    // Optional debug
    // Serial.print("Char: "); Serial.println(c);

    if (c == '\n') {
      serialBuffer.trim();
      if (serialBuffer.length() > 0) {
        message = serialBuffer;
        Serial.print("Received: ");
        Serial.println(message);
      }
      serialBuffer = "";
    } else if (isPrintable(c)) {
      serialBuffer += c;
    }
  }

  // --- Motor control logic ---
  if (distance > 15 || distance == 0) {  // Move if clear or no reading
    if (message == "1") {
      right.step(Move);
      left.step(-Move);
    } else if (message == "2") {
      right.step(-Move);
      left.step(Move);
    } else if (message == "3") {
      right.step(-Move);
      left.step(-Move);
    } else if (message == "4") {
      right.step(Move);
      left.step(Move);
    }
    Serial.println("not stuck");
  } else {  // Obstacle detected
    if (message == "2") {
      right.step(-Move);
      left.step(Move);
    } else if (message == "3") {
      right.step(-Move);
      left.step(-Move);
    } else if (message == "4") {
      right.step(Move);
      left.step(Move);
    }
    Serial.println("stuck");
  }
}
