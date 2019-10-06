#include "CPutil.h"

const int ledPin = 13;
const int buttonPin = 12;

Led led(ledPin);
Button button(buttonPin);

void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  static int prevButtonCount = 0;
  int buttonCount = getButtonPresses();

  if (buttonCount != prevButtonCount)
    blinkLed(buttonCount * 2);

  prevButtonCount = buttonCount;
}

int blinkLed(int amount) {
  // in order not to block, need to check if it should blink currently
  static MSTimer timer;
  static bool ledOn = false;
  static int blinks_remaining = amount;
  while (amount > 0) {
    // keep track of how many blinks are left in the current cycle
    if (timer.done() && blinks_remaining > 0) {
      timer.set(500);
      amount -= 1;
      if (ledOn) {
        led.off();
        ledOn = false;
      } else {
        led.on();
        ledOn = true;
      }
    }
  }
}

int getButtonPresses() {
  static int count = 0;
  if (button.wasPushed()) {
    count += 1;
  }
  return count;
}
