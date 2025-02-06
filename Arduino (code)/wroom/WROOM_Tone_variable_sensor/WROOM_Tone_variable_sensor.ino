/*
  Touch Range to tones

  Connect a variable sensor to pin 34
  Connect speaker to pin 26

  made 2 Feb 2025
  by Michelle Vossen

  This example code is in the public domain.

  https://v0ss3n.github.io/midimadness
*/

#include "pitches.h"

// constants and variables

// pins
int analog_pin = 34;   // Pin the variable sensor is attached to
int speaker_pin = 26;  // Pin the speaker is attached to

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  // initialize speaker_pin as an output
  pinMode(speaker_pin, OUTPUT);
}

void loop() {
  int analogValue = analogRead(analog_pin);
  Serial.println("Analog value:");
  Serial.println(analogValue);
  if (analogValue > 1500) {                                  // set the threshold however you need!!
    int tonePlayed = map(analogValue, 1500, 4095, 31, 880);  // Check pitches.h for the note values
    tone(speaker_pin, tonePlayed);
  }


  else {
    noTone(speaker_pin);  // Stop tone if no touch is detected
  }

  delay(20);  // Small delay for stability
}
