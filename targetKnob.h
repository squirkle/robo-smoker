#include "Arduino.h"

class TargetKnob {
  private:
    int pin;
    int roundUp(int numToRound, int multiple) {
      if (multiple == 0) {
        return numToRound;
      }

      int remainder = numToRound % multiple;
      if (remainder == 0) {
        return numToRound;
      }
      return numToRound + multiple - remainder;
    }
  public:
    TargetKnob(int);
    double getTarget();
};

TargetKnob::TargetKnob (int p) {
  pin = p;
}

double TargetKnob::getTarget() {
  return roundUp(int(map(analogRead(pin), 0, 1023, 300, 125)), 5);
}
