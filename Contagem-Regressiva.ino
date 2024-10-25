int digitPins[] = {6, 9, 10, 11};
int segmentPins[] = {2, 3, 4, 5, A0, 7, 8};

int button1 = 12;
int button2 = 13;
int ledPins[] = {A1, A2, A3, A4, A5};

int times[][2] = {{0, 5}, {0, 30}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}, {20, 0}, {30, 0}, {40, 0}, {50, 0}, {59, 59}};
int timeIndex = 0;
int currentMinutes = 0, currentSeconds = 0;
bool counting = false;
bool timeReachedZero = false;

unsigned long lastUpdateTime = 0;
const int updateInterval = 1000;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
  }
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  setTime(times[timeIndex][0], times[timeIndex][1]);
}

void loop() {
  if (digitalRead(button2) == LOW) {
    delay(200);
    if (!counting) {
      timeIndex = (timeIndex + 1) % 17;
      setTime(times[timeIndex][0], times[timeIndex][1]);
    } else {
      counting = false;
    }
  }

  if (digitalRead(button1) == LOW) {
    delay(200);
    if (!counting && !timeReachedZero) {
      counting = true;
    } else {
      counting = false;
    }
  }

  if (counting) {
    if (millis() - lastUpdateTime >= updateInterval) {
      lastUpdateTime = millis();
      countdown();
    }
  }

  if (currentMinutes == 0 && currentSeconds == 0 && counting) {
    counting = false;
    timeReachedZero = true;
  }

  if (timeReachedZero) {
    blinkLeds();
    displayDash();
  } else {
    displayTime(currentMinutes, currentSeconds);
  }
}

void setTime(int minutes, int seconds) {
  currentMinutes = minutes;
  currentSeconds = seconds;
}

void countdown() {
  if (currentSeconds == 0) {
    if (currentMinutes > 0) {
      currentMinutes--;
      currentSeconds = 59;
    }
  } else {
    currentSeconds--;
  }
}

void displayTime(int minutes, int seconds) {
  int digits[] = {minutes / 10, minutes % 10, seconds / 10, seconds % 10};

  for (int i = 0; i < 4; i++) {
    lightNumber(digits[i]);
    switchDigit(i);
    delay(5);
    clearDigits();
  }
}

void clearDigits() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], HIGH);
  }
}

void blinkLeds() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(100);
    digitalWrite(ledPins[i], LOW);
  }
}

void displayDash() {
  for (int i = 0; i < 4; i++) {
    lightNumber(10);
    switchDigit(i);
    delay(5);
    clearDigits();
  }
}

void lightNumber(int number) {
  const byte segmentMap[11][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1}, // 9
    {0, 0, 0, 0, 0, 0, 1}  // '-'
  };
  
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], segmentMap[number][i]);
  }
}

void switchDigit(int digit) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], i == digit ? LOW : HIGH);
  }
}
