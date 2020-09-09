#include "RTClib.h"

RTC_DS3231 rtc;

unsigned long lasttime = millis();

byte LEDs[] = {
  B11111110,
  B11111101,
  B11111011,
  B11110111,
};
byte numbers[] = {
  B00111111,  //0
  B00000110,  //1
  B01011011,  //2
  B01001111,  //3
  B01100110,  //4
  B01101101,  //5
  B01111101,  //6
  B00000111,  //7
  B01111111,  //8
  B01101111   //9
};
byte dot = B10000000; //.

unsigned long startTime = millis();
void setup() {
  Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  regInit();

}

void loop() {
  byte currentTime[4];
  setTime(currentTime);

  for (int n = 0; n < 4; n++) {
    setNum(n, currentTime[n]);
    if (n == 1) {
      setDot(currentTime[n]);
    }
    delay(1);
  }
}

void regInit() {
  DDRD = B11111111; //Set IO output
  DDRB = B11111111; //Set IO output
}

void setNum(byte leds, byte n) {
  PORTB |= B00111100; //Clear LED
  PORTB &= ~(B00000100 << leds); //Set LED
  //LED bits 0~7 equals PD2~7 + PB0~1
  PORTD &= B00000011; //clear
  PORTD |= (numbers[n] & B00111111) << 2; //set PD2~7
  PORTB &= ~B00000011; //clear
  PORTB |= (numbers[n] & ~B00111111) >> 6; //set PB0~1
}

void setDot(byte n) {
  //LED bits 0~7 equals PD2~7 + PB0~1
  PORTD &= B00000011; //clear
  PORTD |= (numbers[n] | dot & B00111111) << 2; //set PD2~7
  PORTB &= ~B00000011; //clear
  PORTB |= (numbers[n] | dot & ~B00111111) >> 6; //set PB0~1
}

void setTime(byte *data) {
  //Get the current time according to the RTC model.
  DateTime now = rtc.now();

  *(data + 0) = now.hour() / 10;
  *(data + 1) = now.hour() % 10;
  *(data + 2) = now.minute() / 10;
  *(data + 3) = now.minute() % 10;
}
