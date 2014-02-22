#include "Fan.h"
#include "PauseButton.h"
#include "Thermistor.h"
#include "Display.h"
#include "TargetKnob.h"
#include "PID_v1.h"
#include <LiquidCrystal.h>

// Specify the links and initial tuning parameters
double thermTemp, output, targetTemp;
// recos for PID from heatermeter are 3, .1, 15
PID pid(&thermTemp, &output, &targetTemp, 2, .1, 20, DIRECT);

Display display(12, 11, 5, 4, 3, 2, &thermTemp, &targetTemp);
Thermistor therm(A0, 2.4723753e-4, 2.3402251e-4, 1.3879768e-7, 10000);
PauseButton pauseButton(6);
Fan fan(7, 115);
TargetKnob targetKnob(A1);

void setup() {
  // turn the PID on
  pid.SetMode(AUTOMATIC);
}

void loop() {
  // Get our current temp and target temp, then recompute PID output
  targetTemp = targetKnob.getTarget();
  thermTemp = therm.getTempF();
  display.update();

  if (pauseButton.isPaused() == true) {
    fan.powerTo(0);
    return;
  } else {
    pid.Compute();
    fan.powerTo(output);
  }

  delay(50);
}
