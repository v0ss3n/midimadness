/*
  Touch Range to tones
  Plays a tone when a touch pin is touched.
  Connect a touch sensor to pin T1, T2, T3, T4, T5, T6, T7, T8 (with an alligator clip for example)

  made 2 Feb 2025
  by Michelle Vossen

  This example code is in the public domain.

  https://v0ss3n.github.io/midimadness
*/

#include "pitches.h"

// constants and variables

// pins
int speaker_pin = 26;  // Pin the speaker is attached to
int touch_pins[] = { T4, T5, T6, T7, T8, T9 };  // Pins that we're going to touch

// variables for storing the touch values and thresholds. change threshold if needed
int touchValues[] = { 0, 0, 0, 0, 0, 0};
int thresholds[] = { 40, 40, 40, 40, 40, 40 };

// You can change the notes played, check out pitches.h for all options
int pitches[] = { NOTE_A3, NOTE_B3, NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3 };

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  // initialize speaker_pin as an output
  pinMode(speaker_pin, OUTPUT);
}

void loop() {
  Serial.println("Touch values:");

  bool isToneActive = false;  // Track if a tone is currently active

  for (int i = 0; i < 6; i++) { // change number if you have more or less pins
    touchValues[i] = touchRead(touch_pins[i]);
    Serial.print("Pin ");
    Serial.print(touch_pins[i]);
    Serial.print(": ");
    Serial.println(touchValues[i]);

    if (touchValues[i] < thresholds[i]) {
      Serial.print("Pin touched: ");
      Serial.println(touch_pins[i]);
      tone(speaker_pin, pitches[i]);
      isToneActive = true;  // Mark tone as active
      break;  // Exit loop once a touch is detected to prevent overriding
    }
  }

  if (!isToneActive) {
    noTone(speaker_pin);  // Stop tone if no touch is detected
  }

  delay(10);  // Small delay for stability
}
