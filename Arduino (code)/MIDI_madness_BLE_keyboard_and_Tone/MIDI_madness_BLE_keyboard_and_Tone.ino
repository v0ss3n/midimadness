/*
  Touch pins to MIDI notes

  Plays a MIDI note when a touch pin is touched and modulates it based on the capacitance of that pin. Modulates volume based on analog pin 10.
  If there is no device connected via Bluetooth, defaults to using local tone bleeps.

  Based on which keyboard you select in Garageband you may need to adjust notes. CC messages probably don't do anything for Drums
  
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

#include "pitches.h"
#include <BLEMIDI_Transport.h>  //BLE MIDI Transport library
#include <BLEDevice.h>
#include <hardware/BLEMIDI_ESP32.h>  //BLE ESP32 library
#include "driver/touch_sensor.h"

BLEMIDI_CREATE_INSTANCE("MySynth", MIDI);  //make instance of BLEMIDI. Give this a recognizable name! Like your name? Alter ego?
bool isConnected = false;

// constants and variables
int midiNote;

// pins
int speaker_pin = D7;                                   // Pin the speaker is attached to
int analog_pin = A10;                                   // Pin the variable sensor is attached to
int touch_pins[] = { T1, T2, T3, T4, T5, T6, T7, T8 };  // Pins that we're going to touch

// variables for storing the touch values and thresholds
int touchValues[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int thresholds[] = { 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000 };
bool noteActive[] = { false, false, false, false, false, false, false, false };  // Track active notes

// You can change the notes played, check out pitches.h for all options
int pitches[] = { NOTE_A3, NOTE_B3, NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A4 };

// MIDI note range (36-43 for T1-T8); change according to your device and wishes.
int midiNotes[] = { 36, 37, 38, 39, 40, 41, 42, 43 };

// Store last read values to detect freezing
uint32_t lastTouchValues[8] = { 0 };

void setup() {
  Serial.begin(115200);
  // initialize speaker_pin as an output
  pinMode(speaker_pin, OUTPUT);

  MIDI.begin();  //start MIDI

  BLEMIDI.setHandleConnected([]() {
    Serial.println("---------CONNECTED---------");
    isConnected = true;
  });

  BLEMIDI.setHandleDisconnected([]() {
    Serial.println("---------NOT CONNECTED---------");
    isConnected = false;
  });
}


void loop() {
  int samePins = 0;
  Serial.println("Touch values:");

  bool isToneActive = false;  // Track if a tone is currently active
  int totalPitch = 0;         // Sum of active pitches
  int touchCount = 0;         // Number of active touch inputs

  for (int i = 0; i < 8; i++) {
    touchValues[i] = touchRead(touch_pins[i]);
    Serial.println(touchValues[i]);

    if (touchValues[i] == lastTouchValues[i]) {
      samePins++;
    }
    lastTouchValues[i] = touchValues[i];

    if (touchValues[i] > thresholds[i]) {
      if (!noteActive[i]) {  // Only send NoteOn if note was not previously active
        MIDI.sendNoteOn(midiNotes[i], 127, 1);
        noteActive[i] = true;
      }

      // Constrain touch value for MIDI modulation
      touchValues[i] = constrain(touchValues[i], 150000, 300000);
      int midiModulation = map(touchValues[i], 150000, 300000, 0, 127);
      MIDI.sendControlChange(1, midiModulation, 1);  // Modulate active note


      int pitch = pitches[i];  // Get base pitch from array

      // Map the touch sensor input (50000-200000) to pitch adjustment. change according to the detected capacitance and the pitch change that you want.
      int pitchAdjustment = map(touchValues[i], 50000, 200000, 0, 200);
      pitch += pitchAdjustment;  // Adjust pitch

      totalPitch += pitch;  // Sum pitches
      touchCount++;         // Count active touches
      isToneActive = true;  // Mark tone as active

    } else {
      if (noteActive[i]) {  // Only send NoteOff if note was previously active
        MIDI.sendNoteOff(midiNotes[i], 0, 1);
        noteActive[i] = false;
      }
    }
  }

  if (!isConnected) {
    if (isToneActive && touchCount > 0) {
      int averagedPitch = totalPitch / touchCount;
      tone(speaker_pin, averagedPitch);
      Serial.print("Local tone active. Average Pitch: ");
      Serial.println(averagedPitch);
    } else {
      noTone(speaker_pin);
    }
  } else {
    noTone(speaker_pin);  // Mute speaker if BLE MIDI is connected
  }


  // Read analog sensor and map to MIDI CC 7 (volume)
  int analogValue = analogRead(analog_pin);
  if (analogValue > 1500) {
    int midiVolume = map(analogValue, 1500, 4095, 50, 127);
    MIDI.sendControlChange(7, midiVolume, 1);
  }

  // All of the pins returned the same value, which means probably something is frozen.
  if (samePins == 8) {
    Serial.println("Restarting touch pad...");
    touch_pad_fsm_start();
  }

  delay(10);
}

