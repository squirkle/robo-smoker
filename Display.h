#include "Arduino.h"
#include <LiquidCrystal.h>

class Display {
  private:
    LiquidCrystal lcd;
    double* target;
    double* pit;
  public:
    Display(int, int, int, int, int, int, double*, double*);
    void writeTarget();
    void writePit();
    void update();
};

Display::Display (int a, int b, int c, int d, int e, int f, double* p, double* t) : lcd(a,b,c,d,e,f) {
  target = t;
  pit = p;
  lcd.begin(16, 2);
  lcd.print("Target: ");
  lcd.setCursor(0, 1);
  lcd.print("Pit: ");
}

void Display::writeTarget() {
  lcd.setCursor(8, 0);
  lcd.print(int(*target));
  lcd.print((char)223);
  lcd.print('F');
}

void Display::writePit() {
  lcd.setCursor(5, 1);
  lcd.print(*pit);
  lcd.print((char)223);
  lcd.print('F');
}

void Display::update() {
  writeTarget();
  writePit();
}
