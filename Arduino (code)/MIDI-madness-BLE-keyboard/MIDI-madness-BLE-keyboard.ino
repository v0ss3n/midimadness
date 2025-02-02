/*
  Touch pins to MIDI notes

  Plays a MIDI note when a touch pin is touched and modulates it based on the capacitance of that pin. 

  Based on which keyboard you select in Garageband you may need to adjust notes. CC messages probably don't do anything for Drums
  
  to figure out what the touch value range is by touching/squeezing/stretching and releasing 
  the touch pin and reading the values in the serial monitor. Change 
  the threshold accordingly.
  
  Connect a touch sensor to pin T1, T2, T3, T4, T5, T6, T7, T8
  Connect a variable sensor to pin A10

  made 2 Feb 2025
  by Michelle Vossen

  This example code is in the public domain.

  https://v0ss3n.github.io/midimadness
*/

#include <BLEMIDI_Transport.h>       //BLE MIDI Transport library
#include <hardware/BLEMIDI_ESP32.h>  //BLE ESP32 library

BLEMIDI_CREATE_INSTANCE("MySynth", MIDI);  //make instance of BLEMIDI. Give this a recognizable name! Like your name? Alter ego?

// constants and variables
int midiNote;

// pins
int analog_pin = A10;                                   // Pin the variable sensor is attached to
int touch_pins[] = { T1, T2, T3, T4, T5, T6, T7, T8 };  // Pins that we're going to touch

// variables for storing the touch values and thresholds
int touchValues[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int thresholds[] = { 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000 };

// MIDI note range (36-43 for T1-T8); change according to your device and wishes.
int midiNotes[] = { 36, 37, 38, 39, 40, 41, 42, 43 };

void setup() {
  Serial.begin(115200);
  MIDI.begin();  //start MIDI
}

void loop() {
  Serial.println("Touch values:");

// You can send the note continuously with a delay in between when you touch and hold.
  for (int i = 0; i < 8; i++) {
    touchValues[i] = touchRead(touch_pins[i]);
    Serial.println(touchValues[i]);

    if (touchValues[i] > thresholds[i]) {
      Serial.print("Pin touched: ");
      Serial.println(touch_pins[i]);

      // Constrain touch value for MIDI modulation. MIDI mod is CC 1. You can also try out other CC messages but I think Garageband may only support 1, 7 and 10. Different apps will have different CC input :)e
      touchValues[i] = constrain(touchValues[i], 50000, 200000);
      int midiModulation = map(touchValues[i], 50000, 200000, 0, 127);

      MIDI.sendNoteOn(midiNotes[i], midiModulation, 1);
      // MIDI.sendControlChange(10, midiModulation, 1); // Pan

      delay(10);
      MIDI.sendNoteOff(midiNotes[i], 0, 1);
    }
  }

// Alternatively, you can send the note once when you touch and hold, and then modulate, which is a bit more intuitive
  // for (int i = 0; i < 8; i++) {
  //   touchValues[i] = touchRead(touch_pins[i]);
  //   Serial.println(touchValues[i]);

  //   if (touchValues[i] > thresholds[i]) {
  //     if (!noteActive[i]) { // Only send NoteOn if note was not previously active
  //       MIDI.sendNoteOn(midiNotes[i], 127, 1);
  //       noteActive[i] = true;
  //     }
      
  //     // Constrain touch value for MIDI modulation
  //     touchValues[i] = constrain(touchValues[i], 50000, 200000);
  //     int midiModulation = map(touchValues[i], 50000, 200000, 0, 127);
      
  //     MIDI.sendControlChange(1, midiModulation, 1); // Modulate active note
  //   } else {
  //     if (noteActive[i]) { // Only send NoteOff if note was previously active
  //       MIDI.sendNoteOff(midiNotes[i], 0, 1);
  //       noteActive[i] = false;
  //     }
  //   }
  // }


  // Read analog sensor and map to MIDI CC 7 (volume)
  int analogValue = analogRead(analog_pin);
  if (analogValue > 1500) {
    int midiVolume = map(analogValue, 1500, 4095, 0, 127);
    MIDI.sendControlChange(7, midiVolume, 1);

    // You can also use just the variable sensor to send notes:
    //   midiNote = map(analogValue, 1500, 4095, 60, 80);  // read analog pin and remap value to range of 60 to 80
    //   MIDI.sendNoteOn(midiNote, 127, 1);       // send MIDI note based on variable sensor value
  }

  delay(10);
}

