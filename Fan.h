#include "Arduino.h"

class Fan {
  private:
    int pin;
    int minPower;
  public:
    Fan(int p, int x);
    void powerTo(int);
};

Fan::Fan (int p, int x) {
  pin = p;
  minPower = x;
}

void Fan::powerTo(int output) {
  int normalizedOutput = output == 0 ? 0 : map(output, 0, 255, minPower, 255);
  // int normalizedOutput = output; //(output < minPower) ? 0 : output;
  analogWrite(pin, normalizedOutput);
}
