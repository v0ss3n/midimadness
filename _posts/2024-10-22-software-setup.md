---
layout: post
title: "Software setup"
permalink: "/software-setup/"
---

## Setting up the Arduino IDE
In these examples we're using a [Seeed Studio XIAO ESP32S3](https://wiki.seeedstudio.com/xiao_esp32s3_getting_started/). Their wiki is a great place to get started and acquainted with all of the possibilities this tiny development board has to offer. But first, we need to install some drivers. For both Mac and Windows, you can get them [here](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads) (CP210x VCP Mac OSX Driver or CP210x Windows Drivers). For Mac, it can also work to just follow the steps below and then upload something to your ESP32 for the first time; there should be a prompt to install some drivers at some point.

![](https://files.seeedstudio.com/wiki/SeeedStudio-XIAO-ESP32S3/img/2.jpg)

For a quick start, follow these steps in the Arduino IDE (assuming you have it installed already; if not, download the latest stable version and launch it):

1. Navigate to ```File > Preferences```, and paste this URL in the 'Additional Boards Manager URLs': <https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json>
2. Now, navigate to ```Tools > Board > Boards Manager...```, type the keyword "esp32" in the search box, download the latest version by Espressif Systems and install it.
3. Plug in your board and select the board and port from the dropdown menu in the top left of the interface. Click on 'Select other board and port' and look for the XIAO_ESP32S3. 

![]({{ site.baseurl }}/assets/images/arduino-ide-board.png)

That should be it! Now you can start uploading the example code or write your own. For some code you need to install additional libraries, but you'll see that in the code. 

### Boot mode
One thing to keep in mind with ESP32 is that sometimes they're suddenly in the wrong mode for programming. You can get back to boot mode by unplugging the board, then pressing and holding down the boot button (has a B next to it) on the board, then plugging it back in. Now it should work again :-)

## Code examples
You can find the code examples in the [Arduino (Code) folder](https://github.com/v0ss3n/midimadness/tree/main/Arduino%20(code)) in the menu to the left. 

<!-- ## Touch keyboard
The touch range example sounds like this:

<div class="videowrapper"><video width="480" height="360" controls>
  <source src="{{ site.baseurl }}/assets/videos/touch-range-sound.mp4" type="video/mp4"></video>
</div>

You can also connect something conductive, like a conductive spool knitted sample. Now the interaction is way more interesting!

<div class="videowrapper"><video width="480" height="360" autoplay loop muted>
  <source src="{{ site.baseurl }}/assets\videos\keyboard-glove.mp4" type="video/mp4"></video>
</div> -->

### Libraries
Some code examples need libraries - they're at the top of the code so check it out there! For the BLE example you need to make a modification; click [here](https://v0ss3n.github.io/midimadness/midi-bluetooth/) for more on that.

![](https://www.researchgate.net/publication/305311624/figure/download/tbl1/AS:614279237603340@1523466991268/Each-MIDI-number-corresponds-to-an-octave-listed-in-the-left-column-and-a-note-listed-on.png)


