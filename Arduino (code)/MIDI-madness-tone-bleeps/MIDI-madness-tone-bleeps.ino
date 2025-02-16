/*
  Touch Range to tones
  Plays a tone when a touch pin is touched.
  Connect a touch sensor to pin T1, T2, T3, T4, T5, T6, T7, T8 (with an alligator clip for example)

  made 2 Feb 2025
  by Michelle Vossen

  This example code is licensed under CC BY-NC-SA 4.0. See https://creativecommons.org/licenses/by-nc-sa/4.0/ for more information. 

  https://v0ss3n.github.io/midimadness
*/

#include "pitches.h"
#include "driver/touch_sensor.h"

// constants and variables

// pins
int speaker_pin = D7;  // Pin the speaker is attached to
int touch_pins[] = { T1, T2, T3, T4, T5, T6, T7, T8 };  // Pins that we're going to touch

// variables for storing the touch values and thresholds. change threshold if needed
int touchValues[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int thresholds[] = { 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000 };

// You can change the notes played, check out pitches.h for all options
int pitches[] = { NOTE_A3, NOTE_B3, NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_F4, NOTE_A4 };

// Store last read values to detect freezing
uint32_t lastTouchValues[8] = { 0 };

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  // initialize speaker_pin as an output
  pinMode(speaker_pin, OUTPUT);
}

void loop() {
  int samePins = 0;

  Serial.println("Touch values:");

  bool isToneActive = false;  // Track if a tone is currently active

  for (int i = 0; i < 8; i++) {
    touchValues[i] = touchRead(touch_pins[i]);
    Serial.print("Pin ");
    Serial.print(touch_pins[i]);
    Serial.print(": ");
    Serial.println(touchValues[i]);

    if (touchValues[i] == lastTouchValues[i]) {
      samePins++;
    }
    lastTouchValues[i] = touchValues[i];

    if (touchValues[i] > thresholds[i]) {
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

  // All of the pins returned the same value, which means probably something is frozen.
  if (samePins == 8) {
    Serial.println("Restarting touch pad...");
    touch_pad_fsm_start();
  }
  delay(10);  // Small delay for stability
}
