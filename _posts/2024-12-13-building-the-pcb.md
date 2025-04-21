---
layout: post
title: "Building the PCB"
permalink: "/building-the-pcb/"
---

## MIDI Madness Maker V1
Congratulations with your MIDI Madness Maker DIY kit! Let's get it up and running. Follow the steps below for a successful build. 

![]({{ site.baseurl }}/assets/images/midimadnessmaker.jpg)


If you have never soldered before, and want to know the basics, we can recommend to take a look at the [Adafruit Guide To Excellent Soldering](https://learn.adafruit.com/adafruit-guide-excellent-soldering/tools).

<!-- ![]({{ site.baseurl }}/assets/images/soldering.jpg) -->
![]({{ site.baseurl }}/assets/images/soldering 2.jpg)



## Step 1. Check your DIY Kit
### Bill of Materials

Make sure your kit comes with the following components:
- 1x PCB MIDI Madness Maker
- 1x ESP32S3
- 2x Female pin headers
- 1x Bluetooth Antenna (rectangle compoent with wire attached)
- 4x Resistors
- 1x Voltage Regulator L780SCV
- 1x 100kΩ potentiometer
- 1x Audio jack Thonkiconn type
- 1x Audio jack flat pcb type
- 1x Power barrel jack
- 1x 8Ω speaker
- 1x Slide switch
- 1x LED

![]({{ site.baseurl }}/assets/images/overview.jpg)

(in this overview, pretend that the diode is a voltage regulator and imagine there also being 2x female pin headers).

## Step 2. Building the DIY Kit
### Instructions

Now that we know everything is complete in our DIY kit, we can start with soldering the components. For this we recommend putting components in the board one by one and by type, instead of all at once before soldering. This prevents the board from getting overcrowded. When soldering DIY Kits, we start with the smallest components first. 

### Follow the instructions below together with the interactive BOM (Bill Of Materials), so you can find the location of where to put the components on the PCB:

<https://v0ss3n.github.io/midimadness/midimadnessmaker-ibom.html>

Please note that D1 has been replaced with a voltage regulator. More on that later!


### **Resistors**

In your kit you find 4 different types of resistors, they are colour coded with bands to show what value the resistor is. Make sure you place the correct value on the correct spot. Resistors don't have a polarity, so they don't have a 'direction' and orientation doesn't matter.

- R4:  1 x 470Ω (Brown - Black - Black - Purple - Gold) 
- R1:  1 x 100Ω (Brown - Black - Black - Black - Brown)
- R2 + R3: 2 x 47Ω (Brown - Gold - Black - Purple - Yellow) 

![](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fcdn.sparkfun.com%2Fassets%2Fc%2F4%2Fa%2F9%2Fd%2F515c7a2bce395f653d000002.png&f=1&nofb=1&ipt=834234895d55fdb660b796d7437e6f0a7b9580b7915eb13cd50f23b5fad88d82)

### **LED**

Next we solder in the LED. Be mindful of the polarity of the LED! The negative side (SHORT LEG) needs to be inserted in the SQUARE PAD! The long side of the LED will be in the round pad. Here, orientation matters.

![](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fengineeringtutorial.com%2Fwp-content%2Fuploads%2F2016%2F07%2Fengineeringtutorial.com_light-emitting-diode-theory.png&f=1&nofb=1&ipt=dd60512a5665043dbfd28237ba533847518c912229ac4c739eedc6678a0f8099)

### **Pin Headers**

The pin headers are there to keep the ESP32 in place so you can take the microcontroller in and out if needed. If you want to make sure the pin headers are not wiggling, plug the ESP32S3 into the headers before soldering. That way the pin headers will be parallel. 

![](https://einstronic.com/wp-content/uploads/2021/08/Header-Pin-Connector-Female-1x07-1.jpg)

### **Switch**

Solder the switch in the location of the PCB, wiggle the switch a bit back and forth to place it inside the holes of the pcb. It's a tight fit :)

![](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fwww.e-wireless.gr%2Fimages%2Fthumbnails%2F978%2F800%2Fdetailed%2F27%2FDZD002641-1-800x800.jpg&f=1&nofb=1&ipt=b4e2e40844eca9c758ecfc1d75c11c7f81abb2a985dd4008ea56f6998c22572a)

### **Audio and MIDI Jack**

In the kit you find 2 audio jacks:
- MIDI_TR_S1: Audio jack (flat type) for MIDI output 

![](https://mm.digikey.com/Volume0/opasdata/d220001/medias/images/868/SJ1-3523N.jpg)

- Speaker_in1: Audio output jack (thonkiconn type) for audio output

![](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fstore.synthrotek.com%2Fassets%2Fimages%2F3point5InlineThonkiconnJack.jpg&f=1&nofb=1&ipt=9e34ffa6689598cb900341abe0d2a78d7dcedbed168f3dedfe0f64d1f9a3bc7a)

The footprint on the board will tell you which one goes where.

### **Potentiometer**

Solder the potentiometer (knob) at the location where the pcb shows the text "E_textile_tuner_1" If the potentiometer is struggling to fit in the holes bend them over a bit with your hands to make it fit in the spot. Solder all the pads (also the potentiometer mounting pads). 

![](https://mm.digikey.com/Volume0/opasdata/d220001/derivates/2/002/703/MFG_PTV09A%28640x640%29.jpg)

### **Power Barrel Jack**

The barrel jack is used for powering the kit via external power sources that are not USB. You can use a 9V battery to power the kit externally. Only power it externally when you're not plugged in with USB cable! Because the voltage regulator replaces the diode, there is no longer a component forcing the correct direction of current. 

![](https://mm.digikey.com/Volume0/opasdata/d220001/medias/images/322/MFG_DCJ200-10-A-K1-K.jpg)

### **Voltage Regulator**

The Voltage Regulator is a later addition to the first iteration of the DIY kit, because we wanted to power the board via 9V battery. Our microcontroller is only able to handle 5V maximum, so therefore we use the Voltage Regulator to step down the 9V to 5V. 

![](https://external-content.duckduckgo.com/iu/?u=http%3A%2F%2Fimg1.findic.com%2Fl7805cv-lqh79iwS-nqQd1DdEZ.jpg&f=1&nofb=1&ipt=09f2032b5704363f02a28078949b79d27367e25dc592a43ab85a6b1905bb8dc3)

The voltage regulator is type L780SCV and we place it on the location where the diode was supposted to be soldered in on location D1. Position the regulator with the flat side towards the microcontroller. The outer two legs should now be soldered each in a round pad on the PCB, and the middle leg of the regulator is soldered to the outside of the potentiometer next to it.

![]({{ site.baseurl }}/assets/images/midi-regulator.jpg)

Now, you need to do some hacking: we need to create a little bridge between the side of the potentiometer mounting pad where we soldered the middle leg to, and the ground pin of the potentiometer. We can do this on the other side of the PCB. The connection you need to make is indicated with red in the image below. Use a piece of resistor leg that you cut off for this.

![]({{ site.baseurl }}/assets/images/bridge.jpg)


### **Speaker and Bluetooth Antenna**

Solder the speaker to the pads on the PCB, the black wire is connected to the square pad, the red wire to the circular pad. Strip the wires so they're easier to solder. You can stick the speaker to the front or back side of the MIDI Madness Maker. 

![](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fae01.alicdn.com%2Fkf%2FHTB1yiIDHVXXXXbQXFXXq6xXFXXXE%2F8ohm-1W-Mini-Speaker-Module-for-Phone-MP4-Navigator-PSP-Black-14-x-20mm.jpg&f=1&nofb=1&ipt=16fcb5d6e4bbfb98ecbdd93e3c0ee7f8e06c4fa465a5e0aca5f03ff87ad0fe55&ipo=images)

The Bluetooth antenna can be added later when using Bluetooth functions. The ESP32 Bluetooth is already onboard but the antenna amplifies the signal so you can have more distance between source and receiver. You can clip it to the ESP32 as is done in the image below.

![](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Flinuxgizmos.com%2Ffiles%2FXIAO-ESP32S3-antenna.jpg&f=1&nofb=1&ipt=97e8a728b4a2616daf0ea2c6ae17333e1a193b844df70d17996747aeb6198d8e)

### **ESP32 Microcontroller**
The ESP32S3's orientation is important: the USB-C port should face **away** from the pcb board.

### **DONE!**

Do not power the DIY kit just yet! Check the bottom of your pcb for any blobs of solder that could use a bit more love, make sure solder points that should not be connected, are not accidentally connected, and if any clips or components leads might be touching each other or sticking out make sure to trim them. 

![]({{ site.baseurl }}/assets/images/midi-final-solder.jpg)


## Step 3. Testing the DIY kit
### Power

Before we test our DIY kit, make sure that you ONLY power the kit via one of the power options! Either use the USB connector on the ESP32, OR use the external 9V power supply option, not both at the same time! 

When the microcontroller is in the board, connect the usb-c cable and power the kit using a usb block or your computer. The LED on the ESP32 should blink or be lit to indicate the board is powered. 

**Power options for the MIDI MADNESS MAKER**
-  Power over USB (5V) directly on the ESP32.
This is the easiest option, connect a USB-C cable from the microcontroller to your laptop or USB power block

- Power over 9V battery using the external DC Barrel jack Connector
  You can use a 9V battery or 9V adapter to power the MIDI madness maker on the bottom side, this is not recommended to do during prototyping though, the regulator get's warm when used and using a power block is not as safe as over USB for prototyping. You can use these methods, when you have stabilized your setup and you are looking for ways to power externally that are not over USB.

![]({{ site.baseurl }}/assets/images/midi-power.jpg)


- Power over USB using an external powerbank.
  You can use a powerbank to power the MIDI Madness Maker! This is a great option for when you want to implement the kit into a garment or object and you don't like to work with single use batteries. 

## END OF THE BUILD GUIDE

-> Go to the "SOFTWARE SETUP" page on this website, to upload your first code onto the board! 
