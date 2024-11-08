#include "Melodies.h"

void alarmTone(int buzzerPin) {
  int duration = 200;
  int toneFrequency = 300;

  tone(buzzerPin, toneFrequency);
  delay(duration);
  noTone(buzzerPin);
  delay(duration);
}
