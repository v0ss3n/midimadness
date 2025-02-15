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
#define TX 43

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

// MIDI note values for one octave (C4 to B4)
const uint8_t midiNotes[8] = { 60, 61, 62, 63, 64, 65, 66, 67 };

// Touch thresholds (default is 100000 now but can change from sensor to sensor)
uint32_t thresholds[8] = { 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000 };

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
  return map(value, thresholds[0], 500000, 0, 127);  // Map from threshold to the max that you want
}

int note = 20;
int velocity = 100;

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
  for (int i = 0; i < 8; i++) {
    // Read the touch value for the pin
    uint32_t touchValue = touchRead(touchPins[i]);
    touchValue = constrain(touchValue, 0, 500000);

    // Debugging output
    Serial.print("TouchPin ");
    Serial.print(touchPins[i]);
    Serial.print(": ");
    Serial.println(touchValue);
    Serial.print("Sensor value: ");
      sensorValue = analogRead(sensorPin);

    Serial.println(sensorValue);
    // Check if touch value exceeds the threshold
    if (touchValue > thresholds[i]) {
      // If note is not already on, send a Note On message
      MIDI.sendNoteOn(midiNotes[i], 127, channels[i]);  // Note On, velocity 127, channel 1
      noteOnStates[i] = true;
      Serial.print("Note On: ");
      Serial.println(midiNotes[i]);
      sensorValue = analogRead(sensorPin);
      sensorValue = map(sensorValue, 0, 4095, 0, 127);

      // Send MIDI CC messages for touch intensity
      uint8_t ccValue = mapToCC(touchValue);
      // MIDI.sendControlChange(42, ccValue, channels[i]);  // CC 40, mapped value, channel 1
      MIDI.sendControlChange(44, sensorValue, channels[i]);  // CC 40, mapped value, channel 1

      MIDI.sendControlChange(41, ccValue, channels[i]);  // CC 41, mapped value, channel 1
      Serial.print("CC value: ");
      Serial.println(ccValue);
      delay(100);
      MIDI.sendNoteOff(midiNotes[i], 0, channels[i]);  // Note Off, velocity 0, channel 1
      noteOnStates[i] = false;
      Serial.print("Note Off: ");
      Serial.println(midiNotes[i]);
    }
  }


  // Small delay to prevent excessive polling
  delay(10);
}
