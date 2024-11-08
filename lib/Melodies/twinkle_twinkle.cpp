#include "Melodies.h"

void playMelodyTwinkle(int buzzerPin) {
  int length = 42; // Número correcto de notas en la melodía

  // Twinkle Twinkle Little Star
  char notes[] = "ccggaag ffeeddc ggffeed ggffeed ccggaag ffeeddc "; // Un espacio representa un silencio
  int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4,
                  1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4,
                  1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
  int tempo = 300;

  // Función para reproducir un tono
  auto playTone = [&](int tone, int duration) {
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
      digitalWrite(buzzerPin, HIGH);
      delayMicroseconds(tone);
      digitalWrite(buzzerPin, LOW);
      delayMicroseconds(tone);
    }
  };

  // Función para reproducir una nota
  auto playNote = [&](char note, int duration) {
    char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
    int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
    
    // Reproducir el tono correspondiente al nombre de la nota
    for (int i = 0; i < 8; i++) {
      if (names[i] == note) {
        playTone(tones[i], duration);
      }
    }
  };

  // Función para reproducir la melodía
  auto playTwinkleTwinkle = [&]() {
    for (int i = 0; i < length; i++) {
      if (notes[i] == ' ') {
        delay(beats[i] * tempo); // Silencio
      } else {
        playNote(notes[i], beats[i] * tempo);
      }
      
      // Pausa entre notas
      delay(tempo / 2); 
    }
  };

  // Reproducir la melodía
  playTwinkleTwinkle();
}