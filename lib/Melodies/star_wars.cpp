#include "Melodies.h"

const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;

void music_wars(int buzzerPin) {
  
  // Sección 1
  tone(buzzerPin, a, 500);
  noTone(buzzerPin);
  delay(500);
  tone(buzzerPin, a, 500);
  noTone(buzzerPin);
  delay(500);
  tone(buzzerPin, a, 500);
  noTone(buzzerPin);
  delay(500);
  tone(buzzerPin, f, 350);
  noTone(buzzerPin);
  delay(350);
  tone(buzzerPin, cH, 150);
  noTone(buzzerPin);
  delay(150);
  tone(buzzerPin, a, 500);
  noTone(buzzerPin);
  delay(500);
  tone(buzzerPin, f, 350);
  noTone(buzzerPin);
  delay(350);
  tone(buzzerPin, cH, 150);
  noTone(buzzerPin);
  delay(150);
  tone(buzzerPin, a, 650);
  noTone(buzzerPin);
  delay(650);

  // Sección 2
  tone(buzzerPin, eH, 500);
  noTone(buzzerPin);
  delay(500);
  tone(buzzerPin, eH, 500);
  noTone(buzzerPin);
  delay(500);
  tone(buzzerPin, eH, 500);
  noTone(buzzerPin);
  delay(500);
  tone(buzzerPin, fH, 350);
  noTone(buzzerPin);
  delay(350);
  tone(buzzerPin, cH, 150);
  noTone(buzzerPin);
  delay(150);
  tone(buzzerPin, gS, 500);
  noTone(buzzerPin);
  delay(500);
  tone(buzzerPin, f, 350);
  noTone(buzzerPin);
  delay(350);
  tone(buzzerPin, cH, 150);
  noTone(buzzerPin);
  delay(150);
  tone(buzzerPin, a, 650);
  noTone(buzzerPin);
  delay(650);

  // Sección 3
  tone(buzzerPin, aH, 500);
  noTone(buzzerPin);
  delay(500);
  tone(buzzerPin, a, 300);
  noTone(buzzerPin);
  delay(300);
  tone(buzzerPin, a, 150);
  noTone(buzzerPin);
  delay(150);
  tone(buzzerPin, aH, 500);
  noTone(buzzerPin);
  delay(500);
  tone(buzzerPin, gSH, 325);
  noTone(buzzerPin);
  delay(325);
  tone(buzzerPin, gH, 175);
  noTone(buzzerPin);
  delay(175);
  tone(buzzerPin, fSH, 125);
  noTone(buzzerPin);
  delay(125);
  tone(buzzerPin, fH, 125);
  noTone(buzzerPin);
  delay(125);
  tone(buzzerPin, fSH, 250);
  noTone(buzzerPin);
  delay(250);

  delay(325);

  tone(buzzerPin, aS, 250);
  noTone(buzzerPin);
  delay(250);
  tone(buzzerPin, dSH, 500);
  noTone(buzzerPin);
  delay(500);
  tone(buzzerPin, dH, 325);
  noTone(buzzerPin);
  delay(325);
  tone(buzzerPin, cSH, 175);
  noTone(buzzerPin);
  delay(175);
  tone(buzzerPin, cH, 125);
  noTone(buzzerPin);
  delay(125);
  tone(buzzerPin, b, 125);
  noTone(buzzerPin);
  delay(125);
  tone(buzzerPin, cH, 250);
  noTone(buzzerPin);
  delay(250);

  delay(350);

  tone(buzzerPin, f, 250);
  noTone(buzzerPin);
  delay(250);
  tone(buzzerPin, gS, 500);
  noTone(buzzerPin);
  delay(500);
  tone(buzzerPin, f, 350);
  noTone(buzzerPin);
  delay(350);
  tone(buzzerPin, a, 125);
  noTone(buzzerPin);
  delay(125);
  tone(buzzerPin, cH, 500);
  noTone(buzzerPin);
  delay(500);
  tone(buzzerPin, a, 375);
  noTone(buzzerPin);
  delay(375);
  tone(buzzerPin, cH, 125);
  noTone(buzzerPin);
  delay(125);
  tone(buzzerPin, eH, 650);
  noTone(buzzerPin);
  delay(650);

  delay(500);

  tone(buzzerPin, aH, 500);
  noTone(buzzerPin);
  delay(500);
  tone(buzzerPin, a, 300);
  noTone(buzzerPin);
 
}
