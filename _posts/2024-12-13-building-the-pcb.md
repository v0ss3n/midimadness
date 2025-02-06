---
layout: post
title: "Building the PCB"
permalink: "/building-the-pcb/"
---

## MIDI Madness Maker V1
Congratulations with your MIDI Madness Maker DIY kit! Let's get it up and running. 

1. Check if your kit has all of the components. If not: let us know and we'll get it sorted.
2. Soldering the kit and testing connections
3. Programming and testing the board
4. Attaching your own sensors!

## 1. Check your kit
### Bill of Materials
Your kit comes with the following components:
- 1x PCB
- 1x ESP32S3 with 2x male headers, 2x female headers and Bluetooth antenna
- 2x 47Ω resistors
- 1x 470Ω resistor
- 1x 100Ω resistor
- 1x 1N4001 diode
- 1x LED
- 1x 100kΩ potentiometer
- 1x MIDI jack
- 1x slide switch
- 1x power barrel jack
- 1x 8Ω speaker
- 1x speaker mono jack

<!-- nog toevoegen aan kitjes
- 47 ohm x2
- 100 ohm x1
- female headers x2 -->


Not included but very useful are the following:

Power options
- 3x AA batteries and a battery pack to barrel jack. We have some available during the workshop.
- 3.7V LiPo battery: you can solder this directly to the ESP32S3 board; the ESP has an onboard battery charging circuit, so you can charge the battery while the ESP is connected via USB. The downside is that you can't turn it off if you solder the LiPO battery directly to the ESP. Please note that you cannot solder to the exposed battery pads on the PCB as they are not connected to the ESP32.  
- 5V power block. We have some available during the workshop.
- USB-C to USB-A or USB-C cable. We have some available during the workshop.

Connection options
- 3mm nuts and bolts: you can choose to clip alligator clips to the touch legs, or cut them in half and solder them directly to the pads. You can however also use 3mm nuts and bolts to clip alligator wires without soldering. This is a more stable connection. We have some available during the workshop.
- Wire and alligators are available during the workshop!

Audio options
- Audio cable and external speaker or mixer: there is an on-board speaker but if you want real volume, you can connect the MIDI Madness maker to an external speaker or mixer!


### !!! Pay attention !!!
- Do not power the PCB via the power jack with more than 5.5V. There is no on-board voltage regulator. We will implement this in the next version of the board.
- Do not power the PCB via the power jack while also powering it via USB!

## 2. Soldering instructions
Find out where goes what component in the interative BOM. [You can find the interactive BOM here (opens in a new tab)](../../../midimadness/midimadnessmaker-ibom.html){:target="_blank"}

**BEFORE YOU START! Please pay attention to the following:**
- The two 47Ω resistors going to the MIDI jack need to cross each other, because we made a mistake there. :)
- Be mindful of the orientation of the diodes (LED and power diode) and the speaker. The square pad means that it's ground, so make sure to connect the short leg (-) of the LED there. The stripe of the power diode matches with the stripe on the PCB silkscreen. 
- The ESP32S3's orientation: the USB-C port should face **away** from the board.

## 3. Programming and testing the board
This is where the magic is gonna start! We have a couple of options for you to explore. [You can find all of the example code here.](https://github.com/v0ss3n/midimadness/tree/main/Arduino%20(code))

Local bleeps
- Using tone()
- Using libraries (like Mozzi)

MIDI Madness: wired
- Sending to a MIDI-to-CV module for use in your modular synth set-up!
- Sending to a MIDI instrument with MIDI input functionality (example: Korg Volca series)

MIDI Madness: wireless via Bluetooth
- Sending to your phone using BLE (Bluetooth Low Energy). [Special shout-out to Rico Kanthatham for demonstrating and documenting this here!](https://caramel-adjustment-1d3.notion.site/Fabricademy-Electronic-Music-Xiao-ESP32C3-BLE-MIDI-Controller-1389bb27ac9880fbaa47e46e3878080e)

