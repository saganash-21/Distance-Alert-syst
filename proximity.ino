// === Ultrasonic sensor pins ===
const int trigPin = 7;
const int echoPin = 6;

// === Shift register pins ===
const int dataPin = 8;   // DS (Pin 14)
const int latchPin = 9;  // ST_CP (Pin 12)
const int clockPin = 10; // SH_CP (Pin 11)

// === Buzzer and Mute button ===
const int buzzerPin = 5;
const int muteButtonPin = 11;

bool isMuted = false;

// === LED ZONE bitmasks ===
const byte RED_ZONE    = 0b00010001;   // LEDs 1 & 5 (red)
const byte YELLOW_ZONE = 0b00100010;   // LEDs 2 & 6 (yellow)
const byte BLUE_ZONE   = 0b01000100;   // LEDs 3 & 7 (blue)
const byte WHITE_ZONE  = 0b10001000;   // LEDs 4 & 8 (white)

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  pinMode(buzzerPin, OUTPUT);
  pinMode(muteButtonPin, INPUT);  // external pull-down resistor, so no internal pull-up
}

void loop() {
  handleMuteButton();

  int distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  printSerialBar(distance);  // Visual feedback in Serial Monitor

  byte pattern = 0b00000000;
  int beepDelay = -1;

  // Determine LED pattern and beep rate based on distance zones
  if (distance <= 30) {
    pattern = RED_ZONE;
    beepDelay = 100;
  } else if (distance <= 45) {
    pattern = YELLOW_ZONE;
    beepDelay = 250;
  } else if (distance <= 60) {
    pattern = BLUE_ZONE;
    beepDelay = 500;
  } else if (distance <= 80) {
    pattern = WHITE_ZONE;
    beepDelay = 800;
  } else {
    pattern = 0b00000000;
    beepDelay = -1;
  }

  // Output LED pattern to shift register
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, pattern);
  digitalWrite(latchPin, HIGH);

  // Buzzer sound (short beep, pause depends on zone)
  if (beepDelay > 0 && !isMuted) {
    digitalWrite(buzzerPin, HIGH);
    delay(15);  // short beep duration
    digitalWrite(buzzerPin, LOW);
    delay(beepDelay - 15);
  } else {
    digitalWrite(buzzerPin, LOW);
    delay(100);
  }
}

// --- Function to get distance in cm from ultrasonic sensor ---
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 25000);  // Timeout 25ms (~4.3m max)
  int distance = duration * 0.034 / 2;

  if (distance == 0 || distance > 400) return 999;  // Invalid distance
  return distance;
}

// --- Handle mute button with rising edge detection and debounce ---
void handleMuteButton() {
  static bool lastState = LOW;  // Button idle state LOW because of pull-down resistor
  bool currentState = digitalRead(muteButtonPin);

  if (lastState == LOW && currentState == HIGH) {  // Rising edge: button pressed
    isMuted = !isMuted;
    Serial.print("Mute: ");
    Serial.println(isMuted ? "ON" : "OFF");
    delay(300); // debounce delay
  }
  lastState = currentState;
}

// --- Print a simple serial bar graph for distance feedback ---
void printSerialBar(int distance) {
  int level = map(distance, 10, 80, 20, 1);
  level = constrain(level, 1, 20);

  Serial.print("[");
  for (int i = 0; i < 20; i++) {
    Serial.print(i < level ? "#" : "-");
  }
  Serial.println("]");
}
