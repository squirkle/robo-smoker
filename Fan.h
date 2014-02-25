#include "Arduino.h"

class Fan {
  private:
    int pin;
  public:
    Fan(int p, int min, int maxMulti);
    int minPower;
    int maxPower;
    void powerTo(int);
};

Fan::Fan (int p, int min, int maxMulti) {
  pin = p;
  minPower = min;
  maxPower = ((255 - minPower) * maxMulti) + minPower;
}

void Fan::powerTo(int output) {
  int normalizedOutput = output < minPower ? 0 : output;
  analogWrite(pin, normalizedOutput);
}
