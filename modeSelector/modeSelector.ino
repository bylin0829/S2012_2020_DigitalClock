#define keyEventInterval 300

const int threshold = 300;
const int key[] = {0, 1, 2};
const int KEY_COUNT = 3;
bool mutex = false;
bool debounce_state = false;
unsigned long debounce = millis();
enum keyPad {
  BREAK = -1,
  ENTER = 0,
  UP = 1,
  DOWN = 2
};

void setup() {
  Serial.begin(9600);

}

void loop() {
  switch (keyEvent()) {
    case ENTER:
      Serial.println("ENTER");
      break;
    case UP:
      break;
    case DOWN:
      break;
    case BREAK:
      break;
  }
  delay(200);
}

int keyEvent() {
  if (debounce_state = false) {
    debounce = millis();
  }
  for (int i = 0; i < KEY_COUNT; i ++ ) {
    if ((analogRead(i) > threshold) && !mutex) {
      debounce_state = true; // stop update timer
      if (millis() - debounce > keyEventInterval) {
        mutex = true;
        debounce_state = false;
        return i;
      }
    }
  }
  IsKeyReleased();
  return -1;
}

void IsKeyReleased() {
  for (int i = 0; i < KEY_COUNT; i++) {
    if (analogRead(i) > threshold) {
      return;
    }
  }
  mutex = false;
}
