#include <Arduino.h>
#include <MIDI.h>

#define TX 43

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

// MIDI note values for one octave (C4 to B4)
const uint8_t midiNotes[8] = {60, 61, 62, 63, 64, 65, 66, 67};

// Touch thresholds
uint32_t thresholds[8] = {160000, 160000, 160000, 160000, 160000, 160000, 160000, 160000};

// Touch pins
const uint8_t touchPins[8] = {T1, T2, T3, T4, T5, T6, T7, T8};

// Analog sensor pin
const int sensorPin = A10;
int sensorValue;

// State tracking for notes
bool noteOnStates[8] = {false};

// Timestamp tracking for each note
unsigned long lastNoteSendTime[8] = {0};
const uint32_t noteInterval = 50;  // Interval for sending repeated "Note On" messages

// Freeze detection for touch pins
unsigned long lastValidReadTime[8] = {0};
const uint32_t freezeTimeout = 2000;  // Time in ms before detecting a freeze for a pin

// System-wide timeout detection
unsigned long lastSystemValidTime = 0;
const uint32_t systemTimeout = 5000; // Time in ms before restarting system

void setup() {
  // Initialize serial for debugging
  Serial.begin(115200);

  // Start the MIDI communication
  Serial1.begin(115200, SERIAL_8N1, -1, TX);

  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.println("Touch-MIDI Controller Initialized");

  // Initialize timestamps
  unsigned long now = millis();
  for (int i = 0; i < 8; i++) {
    lastValidReadTime[i] = now;
  }
  lastSystemValidTime = now;
}

void loop() {
  bool systemFrozen = true;

  for (int i = 0; i < 8; i++) {
    // Read the touch value for the pin
    uint32_t touchValue = touchRead(touchPins[i]);
    // Debugging output
    Serial.print("TouchPin ");
    Serial.print(touchPins[i]);
    Serial.print(": ");
    Serial.println(touchValue);

    // Check if the touch value is in a valid range (not frozen)
    if (touchValue < 900000) {  // Valid value
      lastValidReadTime[i] = millis();  // Update last valid time
      systemFrozen = false;  // System is not frozen

      // Check if touch value exceeds the threshold
      if (touchValue > thresholds[i]) {
        unsigned long currentTime = millis();

        // Send "Note On" message at regular intervals
        if (currentTime - lastNoteSendTime[i] >= noteInterval) {
          MIDI.sendNoteOn(midiNotes[i], 127, 1);  // Note On, velocity 127, channel 1
          lastNoteSendTime[i] = currentTime;

          // Send MIDI CC messages for touch intensity
          sensorValue = analogRead(sensorPin);
          sensorValue = map(sensorValue, 0, 4095, 0, 127);
          MIDI.sendControlChange(43, sensorValue, 1);  // CC 43, mapped value, channel 1
          Serial.print("CC value: ");
          Serial.println(sensorValue);
        }

        noteOnStates[i] = true;  // Note is "on"
      } else {
        // Send "Note Off" if the touch value drops below the threshold
        if (noteOnStates[i]) {
          MIDI.sendNoteOff(midiNotes[i], 0, 1);  // Note Off, velocity 0, channel 1
          noteOnStates[i] = false;
          Serial.print("Note Off: ");
          Serial.println(midiNotes[i]);
        }
      }
    } else {
      // If the pin has been frozen for too long, handle recovery
      if (millis() - lastValidReadTime[i] > freezeTimeout) {
        Serial.print("TouchPin ");
        Serial.print(touchPins[i]);
        Serial.println(" is frozen! Attempting recovery...");
        // Force system restart for full recovery
        ESP.restart();
      }
    }
  }

  // Check if the entire system is frozen
  if (systemFrozen && millis() - lastSystemValidTime > systemTimeout) {
    Serial.println("System frozen! Restarting...");
    delay(100);  // Flush serial output
    ESP.restart();  // Restart microcontroller
  }

  // Update the last valid system time
  if (!systemFrozen) {
    lastSystemValidTime = millis();
  }

  // Small delay to prevent excessive polling
  delay(10);
}
