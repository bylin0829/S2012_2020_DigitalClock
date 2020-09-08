#define M 0
#define Inc 1
#define Dec 2

const int threahold = 300;
const byte modeCount = 4;

unsigned long myTime;
byte mode = 1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  checkMode();
  modeAction();
  delay(500);
}

void checkMode() {
  if (analogRead(M) > threahold) {
    if (millis() - myTime > 500) {
      mode = mode << 1;
      myTime = millis();

      if (mode > (1 << (modeCount - 1))) {
        //init mode
        mode = 1;
      }
    }
  }
  else {
    myTime = millis();
  }
}

void modeAction() {
  switch (mode) {
    case 1:
      mode_idle();
      break;
    case 2:
      mode_clock();
      break;
    case 4:
      mode_timer();
      break;
    case 8:
      mode_count();
      break;
  }
}

void mode_idle() {
  Serial.println("idle");
}
void mode_clock() {
  Serial.println("clock");
}
void mode_timer() {
  Serial.println("timer");
}
void mode_count() {
  Serial.println("count");
}
