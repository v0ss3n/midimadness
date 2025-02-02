#include <Arduino.h>

#include <MIDI.h>

#define TX 43



MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

// MIDI note values for one octave (C4 to B4)
const uint8_t midiNotes[8] = { 60, 61, 62, 63, 64, 65, 66, 67 };

// Touch thresholds (default is 160000)
uint32_t thresholds[8] = { 160000, 160000, 160000, 160000, 160000, 160000, 160000, 160000 };

// Touch pins
const uint8_t touchPins[8] = { T1, T2, T3, T4, T5, T6, T7, T8 };

// Analog sensor pin
const int sensorPin = A10;
int sensorValue;

// State tracking to prevent repeated MIDI note sending
bool noteOnStates[8] = { false };

// Function to map touch values to MIDI CC range (0-127)
uint8_t mapToCC(uint32_t value) {
  return map(value, thresholds[0], 500000, 0, 127);  // Map from threshold to an arbitrary max of 40000
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
  for (int i = 0; i < 8; i++) {
    // Read the touch value for the pin
    uint32_t touchValue = touchRead(touchPins[i]);
    touchValue = constrain(touchValue, 0, 500000);

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
      sensorValue = analogRead(sensorPin);
      sensorValue = map(sensorValue, 0, 4095, 0, 127);
      Serial.print("Sensor value: ");

      Serial.println(sensorValue);
      // Send MIDI CC messages for touch intensity
      uint8_t ccValue = mapToCC(touchValue);
      // MIDI.sendControlChange(43, ccValue, 1);  // CC 40, mapped value, channel 1
      MIDI.sendControlChange(43, sensorValue, 1);  // CC 40, mapped value, channel 1

      // MIDI.sendControlChange(41, ccValue, 1);  // CC 41, mapped value, channel 1
      Serial.print("CC value: ");
      Serial.println(ccValue);
      delay(100);
      MIDI.sendNoteOff(midiNotes[i], 0, 1);  // Note Off, velocity 0, channel 1
      noteOnStates[i] = false;
      Serial.print("Note Off: ");
      Serial.println(midiNotes[i]);
    }
  }


  // Small delay to prevent excessive polling
  delay(10);
}
