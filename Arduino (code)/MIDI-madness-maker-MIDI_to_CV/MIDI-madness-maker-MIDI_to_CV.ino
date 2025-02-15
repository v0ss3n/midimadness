/*
  Touch pins to MIDI to CV
  Used with Majella MIDI to CV module

  Plays a MIDI note when a touch pin is touched and modulates it based on the capacitance of that pin. 
  
  to figure out what the touch value range is by touching/squeezing/stretching and releasing 
  the touch pin and reading the values in the serial monitor. Change 
  the threshold accordingly.
  
  Connect a touch sensor to pin T1, T2, T3, T4, T5, T6, T7, T8
  Connect a variable sensor to pin A10

  made 2 Feb 2025
  by Michelle Vossen & ChatGPT to figure out why ESP touch pins freeze sometimes.

  This example code is licensed under CC BY-NC-SA 4.0. See https://creativecommons.org/licenses/by-nc-sa/4.0/ for more information. 

  https://v0ss3n.github.io/midimadness
*/

#include <MIDI.h>

#define TX 43


MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);


// MIDI note values
const uint8_t midiNotes[9] = { 60, 61, 62, 63, 64, 65, 66, 67, 68 };

// Touch thresholds (default is 100000 but can be changed for individual sensors)
int thresholds[] = { 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000 };

// Touch pins
int touchPins[] = { T1, T2, T3, T4, T5, T6, T7, T8 };  // Pins that we're going to touch

// variables for storing the touch values and thresholds. change threshold if needed
int touchValues[] = { 0, 0, 0, 0, 0, 0, 0, 0 };




// State tracking to prevent repeated MIDI note sending
bool noteOnStates[9] = { false };

// Function to map touch values to MIDI CC range (0-127)
uint8_t mapToCC(uint32_t value) {
  return map(value, thresholds[0], 300000, 0, 127);  // Map from threshold to a max of 300000
}

void setup() {
  // Initialize serial for debugging
  Serial.begin(115200);

  // Start the MIDI communication
  Serial1.begin(115200, SERIAL_8N1, -1, TX);

  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.println("Touch-MIDI Controller Initialized");
}

void loop() {
  // for (int i = 60; i < 100; i++) {
  //   MIDI.sendNoteOn(i, 60, 1);  // Note On, velocity 127, channel 1
  //   MIDI.sendNoteOn(i-20, i, 2);  // Note On, velocity 127, channel 1
  //   delay(50);
  //   MIDI.sendNoteOff(i, 60, 1);  // Note Off, velocity 0, channel 1
  //   MIDI.sendNoteOff(i-20, i, 2);  // Note Off, velocity 0, channel 1
  //   delay(100);
  // }


  for (int i = 0; i < 8; i++) {
    // Read the touch value for the pin
    uint32_t touchValue = touchRead(touchPins[i]);
    touchValue = constrain(touchValue, 0, 300000);
    // Debugging output
    Serial.print("TouchPin ");
    Serial.print(touchPins[i]);
    Serial.print(": ");
    Serial.println(touchValue);

    // Check if touch value exceeds the threshold
    if (touchValue > thresholds[i]) {
      // If note is not already on, send a Note On message
      MIDI.sendNoteOn(midiNotes[i], 127, 1);  // Note On, velocity 127, channel 1
      noteOnStates[i] = true;
      Serial.print("Note On: ");
      Serial.println(midiNotes[i]);

      // Send MIDI CC messages for touch intensity
      uint8_t ccValue = mapToCC(touchValue);
      MIDI.sendControlChange(71, ccValue, 1);  // CC 40, mapped value, channel 1
      MIDI.sendControlChange(74, ccValue, 1);  // CC 40, mapped value, channel 1
      MIDI.sendControlChange(1, ccValue, 1);   // CC 40, mapped value, channel 1
      // PitchWheelChange(touchValue, 0, 300000, -8000, 8000));
      // MIDI.sendControlChange(41, ccValue, 1);  // CC 41, mapped value, channel 1
      Serial.print("CC value: ");
      Serial.println(ccValue);
      // delay(100);
    }
    if (touchValue < thresholds[i]) {

      MIDI.sendNoteOff(midiNotes[i], 0, 1);  // Note Off, velocity 0, channel 1
      noteOnStates[i] = false;
      Serial.print("Note Off: ");
      Serial.println(midiNotes[i]);
    }
  }


  // Small delay to prevent excessive polling
  delay(10);
}
