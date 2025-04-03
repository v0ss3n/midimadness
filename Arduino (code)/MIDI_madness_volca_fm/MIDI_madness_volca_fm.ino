/*
  Touch pins to MIDI notes: Volca FM 

  Plays a MIDI note when a touch pin is touched and modulates it based on the capacitance of that pin. Also uses variable sensor input for extra fun.
  MIDI guide for Volca FM: https://midi.guide/d/korg/volca-fm/
  
  to figure out what the touch value range is by touching/squeezing/stretching and releasing 
  the touch pin and reading the values in the serial monitor. Change 
  the threshold accordingly.
  
  Connect a touch sensor to pin T1, T2, T3, T4, T5, T6, T7, T8
  Connect a variable sensor to pin A10

  made 2 Feb 2025
  by Michelle Vossen
  With special thanks to Bart Jakobs for figuring out how to stop touch pins from freezing!! Check out https://github.com/bartjakobs/MidiMadnessMaker/tree/main

  https://v0ss3n.github.io/midimadness
*/

#include <MIDI.h>
#include "driver/touch_sensor.h"

#define TX 43

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

// MIDI note values for one octave (C4 to B4)
const uint8_t midiNotes[8] = { 60, 61, 62, 63, 64, 65, 66, 67 };

// Touch thresholds
uint32_t thresholds[8] = { 150000, 150000, 150000, 150000, 150000, 150000, 150000, 150000 };

// Touch pins
const uint8_t touchPins[8] = { T1, T2, T3, T4, T5, T6, T7, T8 };

// Function to map touch values to MIDI CC range (0-127)
uint8_t mapToCC(uint32_t value) {
  return map(value, thresholds[0], 400000, 0, 127);
}

// Analog sensor pin
const int sensorPin = A10;
int sensorValue;

// State tracking for notes
bool noteOnStates[8] = { false };

// Timestamp tracking for each note
unsigned long lastNoteSendTime[8] = { 0 };
const uint32_t noteInterval = 50;  // Interval for sending repeated "Note On" messages

// Store last read values to detect freezing
uint32_t lastTouchValues[8] = { 0 };

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, -1, TX);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.println("Touch-MIDI Controller Initialized");
}

void loop() {
  int samePins = 0;

  for (int i = 0; i < 8; i++) {
    uint32_t touchValue = touchRead(touchPins[i]);
    Serial.print("TouchPin ");
    Serial.print(touchPins[i]);
    Serial.print(": ");
    Serial.println(touchValue);

    if (touchValue == lastTouchValues[i]) {
      samePins++;
    }
    lastTouchValues[i] = touchValue;

    if (touchValue > thresholds[i]) {
      if (!noteOnStates[i]) {
        MIDI.sendNoteOn(midiNotes[i], 127, 1);
        noteOnStates[i] = true;
        Serial.print("Note On: ");
        Serial.println(midiNotes[i]);
      }

      uint8_t ccValue = mapToCC(touchValue);
      MIDI.sendControlChange(48, ccValue, 1);
      Serial.print("CC value: ");
      Serial.println(ccValue);

      sensorValue = analogRead(sensorPin);
      sensorValue = map(sensorValue, 0, 4095, 0, 127);
      Serial.print("Sensor value: ");

      Serial.println(sensorValue);
      // Send MIDI CC messages for analogsensorValue;
      MIDI.sendControlChange(45, sensorValue, 1);  // CC 45 is carrier decay, mapped value, channel 1


    } else {
      if (noteOnStates[i]) {
        MIDI.sendNoteOff(midiNotes[i], 127, 1);
        noteOnStates[i] = false;
        Serial.print("Note Off: ");
        Serial.println(midiNotes[i]);
      }
    }
  }

  // All of the pins returned the same value, which means probably something is frozen.
  if (samePins == 8) {
    Serial.println("Restarting touch pad...");
    touch_pad_fsm_start();
  }

  delay(10);
}
