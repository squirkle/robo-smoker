#include "Arduino.h"

class Thermistor {
  private:
    int pin, seriesResistance, NUMSAMPLES;
    double A, B, C;
  public:
    Thermistor(int, double, double, double, int);
    double getTempK ();
    double getTempC ();
    double getTempF ();
    float getAnalogReading ();
};

Thermistor::Thermistor(int p, double a, double b, double c, int r) {
  pin = p;
  A = a;
  B = b;
  C = c;
  seriesResistance = r;

  NUMSAMPLES = 10;
}

float Thermistor::getAnalogReading () {
  uint8_t i;
  int samples[NUMSAMPLES];
  float analogReading;

  // take N samples in a row, with a slight delay
  for (i = 0; i < NUMSAMPLES; i++) {
    samples[i] = analogRead(pin);
    delay(10);
  }

  // average all the samples out
  analogReading = 0;
  for (i = 0; i < NUMSAMPLES; i++) {
     analogReading += samples[i];
  }
  analogReading /= NUMSAMPLES;

  // convert the value to resistance
  analogReading = 1023 / analogReading - 1;
  analogReading = seriesResistance / analogReading;

  return analogReading;
}

double Thermistor::getTempK () {
  // Thermistor voltage divider resistance
  long R = getAnalogReading();

  // ln(R)
  float lnR = log(R);

  // T = Temp in Kelvins
  double T = 1 / (A + (B * lnR) + (C * lnR * lnR * lnR));

  return T;
}

double Thermistor::getTempC () {
  return getTempK() - 273.15;
}

double Thermistor::getTempF () {
  return (getTempC() * 1.8) + 32;
}

