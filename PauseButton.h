#include "Arduino.h"

class PauseButton {
  private:
    int pin, lastState;
    bool paused;
  public:
    PauseButton(int);
    bool isPaused ();
};

PauseButton::PauseButton (int p) {
  pin = p;
  pinMode(pin, INPUT);
  paused = true;
  lastState = 0;
}

bool PauseButton::isPaused () {
  int state = digitalRead(pin);
  
  // if the button is depressed and we were not depressed on the last cycle, change state
  if (state == HIGH && lastState == 0) {
    lastState = 1;
    paused = !paused;
  }

  if (state == LOW) {
    lastState = 0;
  }
  return paused;
}
