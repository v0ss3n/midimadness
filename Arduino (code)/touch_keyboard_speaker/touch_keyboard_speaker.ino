/*
  Touch Range to PWM Range

  Maps capacitance on touch pin T2 to an audible tone frequency. You first need 
  to figure out what the touch value range is by touching/squeezing/stretching and releasing 
  the touch pin and reading the values in the serial monitor. Change 
  the threshold accordingly.
  
  Connect + of the speaker to pin D7
  Connect - of the speaker to GND
  Connect a touch sensor to pin T1, T2, T3, T4, T5, T6 (with an alligator clip for example)

  made 18 Oct 2024
  by Michelle Vossen

  This example code is in the public domain.

  https://v0ss3n.github.io/projects/education/wearables 
*/

#include "pitches.h"

int speaker_pin = D7;  // Pin the LED is attached to

// variables for storing the touch pins, values and thresholds. change threshold if needed
int touch_pins[] = { T1, T2, T3, T4, T5, T6 };  // Pin that we're going to touch
int touchValues[] = { 0, 0, 0, 0, 0, 0 };
int thresholds[] = { 100000, 100000, 100000, 100000, 100000, 100000 };
int pitches[] = { NOTE_A3, NOTE_B3, NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3 };

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  // initialize LED_pin as an output
  pinMode(speaker_pin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("Touch values:");
  for (int i = 0; i < 6; i++) {
    touchValues[i] = touchRead(touch_pins[i]);
    Serial.println(touchValues[i]);
    if (touchValues[i] > thresholds[i]) {
      Serial.print("Pin touched: ");
      Serial.println(touch_pins[i]);

      tone(speaker_pin, pitches[i]);
      Serial.print("Pitches number: ");
      Serial.println(pitches[i]);
      delay(50);
      noTone(speaker_pin);
    }
  }

  delay(50);
}
