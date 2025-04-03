/*
  Touch pins to MIDI notes: Volca Sample 

  Plays a MIDI note when a touch pin is touched and modulates it based on the capacitance of that pin. 
  
  to figure out what the touch value range is by touching/squeezing/stretching and releasing 
  the touch pin and reading the values in the serial monitor. Change 
  the threshold accordingly.
  
  Connect a touch sensor to pin T1, T2, T3, T4, T5, T6, T7, T8
  Connect a variable sensor to pin A10

  made 2 Feb 2025
  by Michelle Vossen

  This example code is licensed under CC BY-NC-SA 4.0. See https://creativecommons.org/licenses/by-nc-sa/4.0/ for more information. 

  https://v0ss3n.github.io/midimadness
*/

#include <MIDI.h>
#include "driver/touch_sensor.h"

#define TX 43

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

// MIDI note values for one octave (C4 to B4)
const uint8_t midiNotes[8] = { 60, 61, 62, 63, 64, 65, 66, 67 };

// Touch thresholds (default is 170000 now but can change from sensor to sensor)
uint32_t thresholds[8] = { 170000, 170000, 170000, 170000, 170000, 170000, 170000, 170000 };

// Touch pins
const uint8_t touchPins[8] = { T1, T2, T3, T4, T5, T6, T7, T8 };

// MIDI channels on Volca
const int channels[] = { 1, 2, 3, 4, 5, 6, 7, 8 };

// Analog sensor pin
const int sensorPin = A10;
int sensorValue;

// State tracking to prevent repeated MIDI note sending
bool noteOnStates[8] = { false };

// Function to map touch values to MIDI CC range (0-127)
uint8_t mapToCC(uint32_t value) {
  value = constrain(value, thresholds[0], 500000);   // Constrain 
  return map(value, thresholds[0], 500000, 0, 127);  // Map from threshold to the max that you want
}

uint8_t lastSensorValues[8] = { 0 };  // Stores last sensor value for each pin

int note = 20;
int velocity = 100;

// Store last read values to detect freezing
uint32_t lastTouchValues[8] = { 0 };

void setup() {
  // Initialize serial for debugging
  Serial.begin(115200);

  // Start the MIDI communication
  Serial1.begin(115200, SERIAL_8N1, -1, TX);

  MIDI.begin();
}
// Add an active flag for each sensor
bool isNoteActive[] = { false, false, false, false, false, false, false, false, false, false };

void loop() {
  int samePins = 0;

  for (int i = 0; i < 8; i++) {
    // Read the touch value for the pin
    uint32_t touchValue = touchRead(touchPins[i]);
    touchValue = constrain(touchValue, 0, 500000);
    // Read and map the sensor value
    sensorValue = analogRead(sensorPin);
    sensorValue = map(sensorValue, 0, 4095, 0, 127);

    // Map touch value for CC messages
    uint8_t ccValue = mapToCC(touchValue);

    MIDI.sendControlChange(44, ccValue, channels[i]);  // 44 is pitch eg intensity


    // if (sensorValue != lastSensorValues[i]) {
    //   MIDI.sendControlChange(43, sensorValue, channels[i]);  // 43 is speed
    //   lastSensorValues[i] = sensorValue;                     // Store last sensor value
    // }

    // Print touch pin values
    Serial.print("TouchPins:\t");
    for (int i = 0; i < 8; i++) {
      Serial.print("T");
      Serial.print(touchPins[i]);
      Serial.print(": ");
      Serial.print(touchRead(touchPins[i]));
      Serial.print("\t");  // Tab for spacing
    }

    // Print the sensor value at the end of the row
    int sensorValue = analogRead(sensorPin);
    Serial.print("| SensorValue:\t");
    Serial.print(sensorValue);
    Serial.print("| ccValue:\t");
    Serial.println(ccValue);


    if (touchValue == lastTouchValues[i]) {
      samePins++;
    }
    lastTouchValues[i] = touchValue;

    // Check if touch value exceeds the threshold
    if (touchValue > thresholds[i]) {
      // First time touch is detected (Note On)
      if (!noteOnStates[i]) {
        MIDI.sendNoteOn(midiNotes[i], 127, channels[i]);  // Send Note On
        noteOnStates[i] = true;
        Serial.print("Note On: ");
        Serial.println(midiNotes[i]);
      }



    } else if (noteOnStates[i]) {
      // If touch is released, send Note Off
      MIDI.sendNoteOff(midiNotes[i], 0, channels[i]);
      noteOnStates[i] = false;
      Serial.print("Note Off: ");
      Serial.println(midiNotes[i]);
    }
  }



  // All of the pins returned the same value, which means probably something is frozen.
  if (samePins == 8) {
    Serial.println("Restarting touch pad...");
    touch_pad_fsm_start();
  }

  // Small delay to prevent excessive polling
  delay(20);
}
