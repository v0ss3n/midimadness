---
layout: post
title: "Building the PCB"
permalink: "/building-the-pcb/"
---

## MIDI Madness Maker V1
Congratulations with your MIDI Madness Maker DIY kit! Let's get it up and running. Follow the steps below for a sucessfull build. 

![]({{ site.baseurl }}/assets/images/overview.jpg)


## Step 1. Check your Diy Kit
### Bill of Materials

Make sure your kit comes with the following components:
- 1x PCB Midi Madness Maker
- 1x ESP32S3
- 1x Bluetooth Antenna (rectangle compoent with wire attached)
- 4x Resistors
- 1x Voltage Regulator L780SCV
- 1x 100kΩ potentiometer
- 1x audio jack Thonkiconn type
- 1x audio jack flat pcb type
- 1x 8Ω speaker
- 1x slide switch
- 1x Led

## Step 2. Building the DIY Kit
### Instructions

Now that we know everything is complete in our diy it, we can start with soldering in the components. For this we recommend putting components in the board by type instead of all at once before soldering, this prevents the board from getting overcrowded. When soldering DIY Kits, we start with the smallest components first. 

### Follow the instructions below together with the interactive BOM, so you can find the location of where to put the components on the PCB: https://v0ss3n.github.io/midimadness/midimadnessmaker-ibom.html


### **RESISTORS**

In your kit you find 4 different types of resistors, they are colour coded with bands to show what value the resistor is. 

- R4:  1 x 470Ω (Brown - Black - Black - Purple - Gold) 
- R1:  1 x 100Ω (Brown - Black - Black - Black - Brown)
- R2 + R3: 2 x 47Ω (Brown - Gold - Black - Purple - Yellow) 

### **LED**

Next we solder in the LED, be mindful of the polarity of the led! 
the negative side (SHORT LEG) needs to be inserted in the SQUARE PAD! 
the long side of the led will be in the round pas.

### **PIN HEADERS**

The pin headers are there to keep the ESP32 in place so you can take the microcontroller in and out if needed. If you want to make sure the pin headers are not wiggeling, use some tape to keep the headers in place and adjust accordingly after soldering a few pins first.

### **ON/OFF SWITCH**

Solder the switch in the location of the PCB, wiggle the switch a bit back and forth to place it inside the holes of the pcb. 

### **AUDIO EN MIDI JACK**

In the kit you find 2 audio jacks
MIDI_TR_S1     Aaudio jack (flat type)                   midi output 
Speaker_in1    Audio output jack (thonkiconn type        audio output

### **POTENTIOMETER**

Solder the potentiometer at the location where the pcb shows the text "E_textile_tuner_1" If the potentiometer is struggeling to fit in the holes bend them over a bit with your hands to make it fit in the spot. Solder all the pads on the bottom (also the potentiometer mounting pads)

### **POWER BARREL JACK**

The barrel jack is used for powering the kit via external power sources that are not USB. You can use a 9V battery to power the kit externally and we will show you examples about this later. 

### **VOLTAGE REGULATOR**

The Voltage Regulator is a later addition to the first iteration of the diy kit, because we wanted to power the board over 9V battery. Our microcontroller is only able to handle 5V maximum, so therefore we use the Voltage Regulator to step down the 9V -> 5V. 

The voltage regulator is type L780SCV and we place it on the location where the Diode was supposted to be soldered in on location D1. Position the regulator with the flat side towards the microcontroller. The outter two legs should now be soldered each in a round pad on the PCB, and the middle leg of the regulator is soldered to the outside of the potentiometer next door.

![]({{ site.baseurl }}/assets/images/midi-regulator.jpg)

### **SPEAKER & BLUETOOTH ANTENNA**

Solder the speaker to the pads on the PCB, the black wire is connected to the swquare pad, the red wire to the circular pad. You can stick the speaker to the front side or the pack side of the Midi Madness Maker. The Bluetooth antenna can be added later when using Bluetooth functions. The ESP32 Bluetooth is already onboard but the antenna amplifies the signal so you can have more distance between source and reciever. 

### **ESP32**
The ESP32S3's orientation is important: the USB-C port should face **away** from the pcb board.

### **DONE!**

Do not power the diy kit just yet! Check the bottom of your pcb for any blobs of solder that can use a bit more, make sure solder points are not connected that should not be and if any clips or components leads might be touching eachoter or stick out. 

![]({{ site.baseurl }}/assets/images/midi-final-solder.jpg)


## Step 3. Testing the DIY kit
### Power

Before we test our diy kit, make sure that you ONLY power the kit via one of the power options! Either use the USB connector on the ESP32, OR use the external 9V power supply option, not both at the same time! 

When the microcontroler is in the board, connect the usb-c cable and power the kit using a wall wart usb block or your computer. The LED on the ESP32 should blink or be lit to indicate the board is powered. 

**Power options for the MIDI MADNESS MAKER**
- Power over USB (5V) directly on the ESP32.
- Power over 9V battery using the external DC Barrel jack Connector
- Power over USB using an external powerbank


## END OF THE BUILD GUIDE

-> Go to the "SOFTWARE SETUP" to upload your first code onto the board! 
