/*
 * MPS750HiHatMidiController.ino
 *
 * This program is used to convert analog output of Millenium MPS-750X Hi-Hat Pad
 * to a MIDI CC value of "modulation wheel" (MIDI CC 1) so we can use it in Logic Pro X's Drummer to
 * control whether hi-hat is opened o closed.
 * 
 * Connection:
 * 6.3mm stereo jack
 * Tip: hi-hat output
 * Ring: 5V
 * Sleeve: GND
 *
 * Created: 12/13/2022 20:00:08 PM
 * Author: Gilles Vendranas Rullier
 * GitHub: gvendranas
 */ 

// Importing MIDI over USB library
#include "MIDIUSB.h"

// MIDI Constants
#define MIDI_CHANNEL 9 // Your MPS module MIDI channelbeing used -1
#define MIDI_MIN_VALUE 0
#define MIDI_MAX_VALUE 127
#define MIDI_CC 1 // This is modulation wheel MIDI CC used for Drummer to control hi-hat opening
                  // Set Input Mapping as: "GM + ModWheel controls HiHat opening level" on Drum Kit Designer

// Analog constants
// These constats could change depending on components used for an specific batch, 
// depending on "range" potentiometer configuration under the hi-hat and as well as environmental condition.
// I suggest checking your device's specific range by reading hi-hat output value with a simple analogRead sketch.
#define MIN_ANALOG_VALUE 8
#define MAX_ANALOG_VALUE 589

// Other constants
#define PULL_PERIOD_IN_MS 20 // 20 ms is accurate enough and we do not overload MIDI channel
#define ANALOG_READ_PORT A0 // Set desired analog input

// Create a variable to store analog value read at ANALOG_READ_PORT
int sensorValue = 0;
// Variable to store analog read scaled to MIDI CC value range.
char midiValue = 0;

// Function used to send CC value throug MIDI over USB
// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).
void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void setup() {
  // Initializing serial interface with MIDI baud rate
  Serial.begin(115200);
}

void loop() {
  // We read analog port ANALOG_READ_PORT and store value in sensorValue
  sensorValue = analogRead(ANALOG_READ_PORT);
  // We scale up the reading from port A0 to 127
  midiValue = map(sensorValue, MIN_ANALOG_VALUE, MAX_ANALOG_VALUE, MIDI_MIN_VALUE, MIDI_MAX_VALUE);
  // We send scalued value throug MIDI port MIDI_PORT as CC value MIDI_CC
  controlChange(MIDI_CHANNEL, MIDI_CC, midiValue);
  delay(PULL_PERIOD_IN_MS);
}
