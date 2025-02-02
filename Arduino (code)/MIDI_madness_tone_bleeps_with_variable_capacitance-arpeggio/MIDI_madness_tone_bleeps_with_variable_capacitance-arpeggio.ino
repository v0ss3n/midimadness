/*
  Touch Range to tones
  Plays a tone when a touch pin is touched and modulates the pitch based on detected capacitance. 
  The harder you squeeze/stretch/press your touch sensor, the more modulation.
  If you touch multiple touch sensors, the pitch is alternated. Arpeggio!
  Connect a touch sensor to pin T1, T2, T3, T4, T5, T6, T7, T8 (with an alligator clip for example)

  made 2 Feb 2025
  by Michelle Vossen

  This example code is in the public domain.

  https://v0ss3n.github.io/midimadness
*/

#include "pitches.h"

// constants and variables

// pins
int speaker_pin = D7;  // Pin the speaker is attached to
int analog_pin = A10;  // Pin the variable sensor is attached to
int touch_pins[] = { T1, T2, T3, T4, T5, T6, T7, T8 };  // Pins that we're going to touch

// variables for storing the touch values and thresholds. change threshold if needed
int touchValues[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int thresholds[] = { 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000 };

// You can change the notes played, check out pitches.h for all options
int pitches[] = { NOTE_A3, NOTE_B3, NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_F4, NOTE_A4 };

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  // initialize speaker_pin as an output
  pinMode(speaker_pin, OUTPUT);
}

void loop() {
  Serial.println("Touch values:");

  bool isToneActive = false;  // Track if a tone is currently active
  int activePitches[8];  // Array to store active pitches
  int touchCount = 0;  // Number of active touch inputs

  for (int i = 0; i < 8; i++) {
    touchValues[i] = touchRead(touch_pins[i]);
    Serial.print("Pin ");
    Serial.print(touch_pins[i]);
    Serial.print(": ");
    Serial.println(touchValues[i]);

    if (touchValues[i] > thresholds[i]) {
      Serial.print("Pin touched: ");
      Serial.println(touch_pins[i]);
      
      int pitch = pitches[i]; // Get base pitch from array
      
      // Constrain touch value for useful pitch modulation
      touchValues[i] = constrain(touchValues[i], 50000, 200000);
      
      // Map the touch sensor input (50000-200000) to pitch adjustment (-100 to +100)
      int pitchAdjustment = map(touchValues[i], 50000, 200000, -100, 100);
      pitch += pitchAdjustment; // Adjust pitch
      
      activePitches[touchCount] = pitch; // Store active pitch
      touchCount++;  // Count active touches
      isToneActive = true;  // Mark tone as active
    }
  }

  if (isToneActive && touchCount > 0) {
    for (int j = 0; j < touchCount; j++) {
      tone(speaker_pin, activePitches[j]);
      Serial.print("Arpeggiating Pitch: ");
      Serial.println(activePitches[j]);
      delay(200); // Delay to create arpeggiation effect
    }
  } else {
    noTone(speaker_pin);  // Stop tone if no touch is detected
  }

  delay(20);  // Small delay for stability
}

