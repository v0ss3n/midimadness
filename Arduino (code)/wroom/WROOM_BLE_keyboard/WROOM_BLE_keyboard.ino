/*
  Touch pins to MIDI notes

  Plays a MIDI note when a touch pin is touched

  Based on which keyboard you select in Garageband you may need to adjust notes. CC messages probably don't do anything for Drums
  
  to figure out what the touch value range is by touching/squeezing/stretching and releasing 
  the touch pin and reading the values in the serial monitor. Change 
  the threshold accordingly.
  
  Connect a touch sensor to touch pins
  Connect a variable sensor to pin 34

  made 2 Feb 2025
  by Michelle Vossen

  This example code is in the public domain.

  https://v0ss3n.github.io/midimadness
*/

#include <BLEMIDI_Transport.h>       //BLE MIDI Transport library
#include <hardware/BLEMIDI_ESP32.h>  //BLE ESP32 library

BLEMIDI_CREATE_INSTANCE("MyWROOMSynth", MIDI);  //make instance of BLEMIDI. Give this a recognizable name! Like your name? Alter ego?

// constants and variables
int midiNote;
int lastAnalogNote = -1;  // Store last played note

// pins
int analog_pin = 34;                                    // Pin the variable sensor is attached to
int touch_pins[] = { T4, T5, T6, T7, T8, T9 };  // Pins that we're going to touch

// variables for storing the touch values and thresholds
int touchValues[] = { 0, 0, 0, 0, 0, 0};
int thresholds[] = { 40, 40, 40, 40, 40, 40 };
bool noteActive[] = { false, false, false, false, false, false };  // Track active notes

// MIDI note range; change according to your device and wishes.
int midiNotes[] = { 36, 37, 38, 39, 40, 41 };

void setup() {
  Serial.begin(115200);
  MIDI.begin();  //start MIDI
}

void loop() {
  
  Serial.println("Touch values:");

  for (int i = 0; i < 6; i++) {
    touchValues[i] = touchRead(touch_pins[i]);
    Serial.println(touchValues[i]);

    if (touchValues[i] < thresholds[i]) {
      if (!noteActive[i]) {  // Only send NoteOn if note was not previously active
        MIDI.sendNoteOn(midiNotes[i], 127, 1);
        noteActive[i] = true;
      }

    } else {
      if (noteActive[i]) {  // Only send NoteOff if note was previously active
        MIDI.sendNoteOff(midiNotes[i], 0, 1);
        noteActive[i] = false;
      }
    }
  }


  int analogValue = analogRead(analog_pin);
  Serial.println("Analog value:");
  Serial.println(analogValue);

  int newMidiNote = map(analogValue, 1500, 4095, 0, 127);

  if (analogValue > 1500 && newMidiNote != lastAnalogNote) {
    MIDI.sendNoteOn(newMidiNote, 127, 1);
    if (lastAnalogNote != -1) MIDI.sendNoteOff(lastAnalogNote, 0, 1);  // Stop last note
    lastAnalogNote = newMidiNote;
  } else if (analogValue <= 1500 && lastAnalogNote != -1) {
    MIDI.sendNoteOff(lastAnalogNote, 0, 1);
    lastAnalogNote = -1;
  }

  delay(20);
}
