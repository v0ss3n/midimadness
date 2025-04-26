---
layout: post
title: "Sending MIDI wirelessly to your computer"
permalink: "/midi-bluetooth/"
---

There are multiple ways to turn your MIDI Madness Maker into a Bluetooth MIDI keyboard! The code used for the different examples is the same (MIDI-madness-BLE-keyboard.ino). Here the focus is on sending MIDI wirelessly to computers. 

## Libraries (this part you only need to do once)
You need to start by installing the BLE-MIDI library by Lathoub. **Make sure you do NOT install the other suggested libraries**; if you have additional BLE libraries compilation may fail so uninstall those if you have them :)

To make it work with ESP32, you need to change line 116 in `BLEMIDI_ESP32.h` (`Arduino/libraries/BLE-MIDI/src/hardware/BLEMIDI_ESP32.h`). Add `.c_str()` at the end of the line, so it looks like this: `std::string rxValue = characteristic->getValue().c_str();`. What you can also do is just replace the entire BLE-MIDI library with this [BLE-MIDI folder](../assets/BLE-MIDI.zip), there it's already implemented (just unzip into your Arduino/libraries folder).

### MidiMadnessMaker library by Bart Jakobs
Programming genius Bart Jakobs also made a nice library to use with the MIDI Madness Maker that sends MIDI notes and CC info wirelessly to your phone apps. [Check it out here](https://github.com/bartjakobs/MidiMadnessMaker); there is also a code example. 

Alternatively, you can use the BLE keyboard code in the Arduino (Code) folder.

---

# Sending MIDI wirelessly to your computer
Usually you need to connect a MIDI keyboard via USB when you want to connect it to your computer, but you can also do this wirelessly! With this functionality, you can send MIDI to browser-based apps like [https://midi.city/](midi.city) (works best on Chrome/Safari). Make sure Bluetooth is turned on.

Steps (Windows)
1. Install [BLE-MIDI Connect](https://apps.microsoft.com/detail/9nvmlzttwwvl). You can download the free trial, it has no restrictions (but if you will use it a lot, you can buy it, since it's only the price of a cup of coffee and the developers deserve coffee). This software is used to connect to the BLE device. You need to log in with a Microsoft account to download it.

    ![]({{ site.baseurl }}/assets/images/blemidiconnect.png) 

2. Install [LoopMIDI](https://www.tobias-erichsen.de/software/loopmidi.html). This software is used to connect the BLE device to a virtual port, so that (web) apps on your computer can easily recognize it as a MIDI keyboard.

    ![]({{ site.baseurl }}/assets/images/loopmidi.png)

Steps (Mac)
Audio MIDI setup (pre installed on Mac): enable Bluetooth MIDI in the audio/MIDI setup

Now you can go to <midi.city> or other web-based MIDI keyboards that allow external keyboards to be connected and control it with the MIDI Madness Maker! 

![]({{ site.baseurl }}/assets/images/midicity.png) 

This also works with Ableton. In Ableton select your MIDI device (loopMIDI port) here:

![]({{ site.baseurl }}/assets/images/ableton.png) 

## Links
- <https://midi.city/>
- <https://midi.guide/>

