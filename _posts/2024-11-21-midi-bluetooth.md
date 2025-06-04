---
layout: post
title: "Sending MIDI wirelessly to phone apps"
permalink: "/midi-bluetooth/"
---

There are multiple ways to turn your MIDI Madness Maker into a Bluetooth MIDI keyboard! The code used for the different examples is the same (MIDI-madness-BLE-keyboard.ino). Here the focus is on sending MIDI to your computer wirelessly. 

## Libraries (this part you only need to do once)
You need to start by installing the BLE-MIDI library by Lathoub. **Make sure you do NOT install the other suggested libraries**; if you have additional BLE libraries compilation may fail so uninstall those if you have them :)

To make it work with ESP32, you need to change line 116 in `BLEMIDI_ESP32.h` (`Arduino/libraries/BLE-MIDI/src/hardware/BLEMIDI_ESP32.h`). Add `.c_str()` at the end of the line, so it looks like this: `std::string rxValue = characteristic->getValue().c_str();`. What you can also do is just replace the entire BLE-MIDI library with this [BLE-MIDI folder]({{ site.baseurl }}/assets/BLE-MIDI.zip), there it's already implemented (just unzip into your Arduino/libraries folder).

### MidiMadnessMaker library by Bart Jakobs
Programming genius Bart Jakobs made a nice library to use with the MIDI Madness Maker that sends MIDI notes and CC info wirelessly to your phone apps. [Check it out here](https://github.com/bartjakobs/MidiMadnessMaker); there is also a code example. 

Alternatively, you can use the BLE keyboard code in the Arduino (Code) folder.

---

# MIDI to Garageband/SynprezFM 
This example is based on a tutorial by Rico Kanthatham which you can find [here](https://caramel-adjustment-1d3.notion.site/Fabricademy-Electronic-Music-Xiao-ESP32C3-BLE-MIDI-Controller-1389bb27ac9880fbaa47e46e3878080e).

## Apps
- Android: download MIDI BLE Connect & SynprezFM II. Connect to your device via the BLE app and then go to SynprezFM
- Apple: download Garageband; go to gears > advanced > bluetooth midi devices

### Using garageband
You can use the BLE keyboard code example for various keyboards, drums and other instruments, but you may want to change the MIDI notes sent (check the charts below). MIDI CC doesn't always have an effect.

MIDI CC: <https://rfwilmut.net/notes/GBcontrol.html>
MIDI map for Garageband drums (via <https://gist.github.com/igolopolosov/8193f8d3da522969244dda318f21d3fa>)

via Reddit:

```
CC 1 (Modulation Wheel) -> Tremolo (Electric Piano)

CC 7 (Channel Volume) -> Channel Volume

CC 10 (Pan)-> Pan (Channel) 
```

```
MIDI  Note    Drum Sound
====  ====    ==========
36    C2      Bass Drum 1
37    C#2     Side Stick
38    D2      Acoustic Snare
39    Eb2     Hand Clap
40    E2      Electric Snare
41    F2      Low Floor Tom
42    F#2     Closed Hi Hat
43    G2      Mid Floor Tom
44    Ab2     Pedal Hi-Hat
45    A2      High Floor Tom
46    Bb2     Open Hi-Hat
47    B2      Low-Mid Tom
48    C3      Hi Mid Tom
49    C#3     Crash Cymbal 1
50    D3      High Tom / Maracase
51    Eb3     Ride Cymbal 1
52    E3      Flat Snare / Accent Drum
53    F3      Bass Drum 2

After this point drums are completely situational

54    F#3     Splash Cymbal
55    G3      Cowbell
56    Ab3     Tabourine
57    A3      Vibraslap
58    Bb3     Anything
59    B3      Vibraslap 2
```

![](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fd29rinwu2hi5i3.cloudfront.net%2Farticle_media%2Fd494a425-3e9d-4d04-8d75-3e25a6e1a188%2F01_fig_1_drum_maps.jpg&f=1&nofb=1&ipt=3c5fbea86e7a55ed9a0b866002e9ebb5df15402833d33c23f633298ab87ffe8f&ipo=images)

![](https://www.researchgate.net/publication/305311624/figure/download/tbl1/AS:614279237603340@1523466991268/Each-MIDI-number-corresponds-to-an-octave-listed-in-the-left-column-and-a-note-listed-on.png)


## Links
- <https://midi.city/>
- <https://midi.guide/>

## Examples

<blockquote class="instagram-media" data-instgrm-permalink="https://www.instagram.com/reel/DF8WQ_gom9K/?utm_source=ig_embed&amp;utm_campaign=loading" data-instgrm-version="14" style=" background:#FFF; border:0; border-radius:3px; box-shadow:0 0 1px 0 rgba(0,0,0,0.5),0 1px 10px 0 rgba(0,0,0,0.15); margin: 1px; max-width:540px; min-width:326px; padding:0; width:99.375%; width:-webkit-calc(100% - 2px); width:calc(100% - 2px);"><div style="padding:16px;"> <a href="https://www.instagram.com/reel/DF8WQ_gom9K/?utm_source=ig_embed&amp;utm_campaign=loading" style=" background:#FFFFFF; line-height:0; padding:0 0; text-align:center; text-decoration:none; width:100%;" target="_blank"> <div style=" display: flex; flex-direction: row; align-items: center;"> <div style="background-color: #F4F4F4; border-radius: 50%; flex-grow: 0; height: 40px; margin-right: 14px; width: 40px;"></div> <div style="display: flex; flex-direction: column; flex-grow: 1; justify-content: center;"> <div style=" background-color: #F4F4F4; border-radius: 4px; flex-grow: 0; height: 14px; margin-bottom: 6px; width: 100px;"></div> <div style=" background-color: #F4F4F4; border-radius: 4px; flex-grow: 0; height: 14px; width: 60px;"></div></div></div><div style="padding: 19% 0;"></div> <div style="display:block; height:50px; margin:0 auto 12px; width:50px;"><svg width="50px" height="50px" viewBox="0 0 60 60" version="1.1" xmlns="https://www.w3.org/2000/svg" xmlns:xlink="https://www.w3.org/1999/xlink"><g stroke="none" stroke-width="1" fill="none" fill-rule="evenodd"><g transform="translate(-511.000000, -20.000000)" fill="#000000"><g><path d="M556.869,30.41 C554.814,30.41 553.148,32.076 553.148,34.131 C553.148,36.186 554.814,37.852 556.869,37.852 C558.924,37.852 560.59,36.186 560.59,34.131 C560.59,32.076 558.924,30.41 556.869,30.41 M541,60.657 C535.114,60.657 530.342,55.887 530.342,50 C530.342,44.114 535.114,39.342 541,39.342 C546.887,39.342 551.658,44.114 551.658,50 C551.658,55.887 546.887,60.657 541,60.657 M541,33.886 C532.1,33.886 524.886,41.1 524.886,50 C524.886,58.899 532.1,66.113 541,66.113 C549.9,66.113 557.115,58.899 557.115,50 C557.115,41.1 549.9,33.886 541,33.886 M565.378,62.101 C565.244,65.022 564.756,66.606 564.346,67.663 C563.803,69.06 563.154,70.057 562.106,71.106 C561.058,72.155 560.06,72.803 558.662,73.347 C557.607,73.757 556.021,74.244 553.102,74.378 C549.944,74.521 548.997,74.552 541,74.552 C533.003,74.552 532.056,74.521 528.898,74.378 C525.979,74.244 524.393,73.757 523.338,73.347 C521.94,72.803 520.942,72.155 519.894,71.106 C518.846,70.057 518.197,69.06 517.654,67.663 C517.244,66.606 516.755,65.022 516.623,62.101 C516.479,58.943 516.448,57.996 516.448,50 C516.448,42.003 516.479,41.056 516.623,37.899 C516.755,34.978 517.244,33.391 517.654,32.338 C518.197,30.938 518.846,29.942 519.894,28.894 C520.942,27.846 521.94,27.196 523.338,26.654 C524.393,26.244 525.979,25.756 528.898,25.623 C532.057,25.479 533.004,25.448 541,25.448 C548.997,25.448 549.943,25.479 553.102,25.623 C556.021,25.756 557.607,26.244 558.662,26.654 C560.06,27.196 561.058,27.846 562.106,28.894 C563.154,29.942 563.803,30.938 564.346,32.338 C564.756,33.391 565.244,34.978 565.378,37.899 C565.522,41.056 565.552,42.003 565.552,50 C565.552,57.996 565.522,58.943 565.378,62.101 M570.82,37.631 C570.674,34.438 570.167,32.258 569.425,30.349 C568.659,28.377 567.633,26.702 565.965,25.035 C564.297,23.368 562.623,22.342 560.652,21.575 C558.743,20.834 556.562,20.326 553.369,20.18 C550.169,20.033 549.148,20 541,20 C532.853,20 531.831,20.033 528.631,20.18 C525.438,20.326 523.257,20.834 521.349,21.575 C519.376,22.342 517.703,23.368 516.035,25.035 C514.368,26.702 513.342,28.377 512.574,30.349 C511.834,32.258 511.326,34.438 511.181,37.631 C511.035,40.831 511,41.851 511,50 C511,58.147 511.035,59.17 511.181,62.369 C511.326,65.562 511.834,67.743 512.574,69.651 C513.342,71.625 514.368,73.296 516.035,74.965 C517.703,76.634 519.376,77.658 521.349,78.425 C523.257,79.167 525.438,79.673 528.631,79.82 C531.831,79.965 532.853,80.001 541,80.001 C549.148,80.001 550.169,79.965 553.369,79.82 C556.562,79.673 558.743,79.167 560.652,78.425 C562.623,77.658 564.297,76.634 565.965,74.965 C567.633,73.296 568.659,71.625 569.425,69.651 C570.167,67.743 570.674,65.562 570.82,62.369 C570.966,59.17 571,58.147 571,50 C571,41.851 570.966,40.831 570.82,37.631"></path></g></g></g></svg></div><div style="padding-top: 8px;"> <div style=" color:#3897f0; font-family:Arial,sans-serif; font-size:14px; font-style:normal; font-weight:550; line-height:18px;">View this post on Instagram</div></div><div style="padding: 12.5% 0;"></div> <div style="display: flex; flex-direction: row; margin-bottom: 14px; align-items: center;"><div> <div style="background-color: #F4F4F4; border-radius: 50%; height: 12.5px; width: 12.5px; transform: translateX(0px) translateY(7px);"></div> <div style="background-color: #F4F4F4; height: 12.5px; transform: rotate(-45deg) translateX(3px) translateY(1px); width: 12.5px; flex-grow: 0; margin-right: 14px; margin-left: 2px;"></div> <div style="background-color: #F4F4F4; border-radius: 50%; height: 12.5px; width: 12.5px; transform: translateX(9px) translateY(-18px);"></div></div><div style="margin-left: 8px;"> <div style=" background-color: #F4F4F4; border-radius: 50%; flex-grow: 0; height: 20px; width: 20px;"></div> <div style=" width: 0; height: 0; border-top: 2px solid transparent; border-left: 6px solid #f4f4f4; border-bottom: 2px solid transparent; transform: translateX(16px) translateY(-4px) rotate(30deg)"></div></div><div style="margin-left: auto;"> <div style=" width: 0px; border-top: 8px solid #F4F4F4; border-right: 8px solid transparent; transform: translateY(16px);"></div> <div style=" background-color: #F4F4F4; flex-grow: 0; height: 12px; width: 16px; transform: translateY(-4px);"></div> <div style=" width: 0; height: 0; border-top: 8px solid #F4F4F4; border-left: 8px solid transparent; transform: translateY(-4px) translateX(8px);"></div></div></div> <div style="display: flex; flex-direction: column; flex-grow: 1; justify-content: center; margin-bottom: 24px;"> <div style=" background-color: #F4F4F4; border-radius: 4px; flex-grow: 0; height: 14px; margin-bottom: 6px; width: 224px;"></div> <div style=" background-color: #F4F4F4; border-radius: 4px; flex-grow: 0; height: 14px; width: 144px;"></div></div></a><p style=" color:#c9c8cd; font-family:Arial,sans-serif; font-size:14px; line-height:17px; margin-bottom:0; margin-top:8px; overflow:hidden; padding:8px 0 7px; text-align:center; text-overflow:ellipsis; white-space:nowrap;"><a href="https://www.instagram.com/reel/DF8WQ_gom9K/?utm_source=ig_embed&amp;utm_campaign=loading" style=" color:#c9c8cd; font-family:Arial,sans-serif; font-size:14px; font-style:normal; font-weight:normal; line-height:17px; text-decoration:none;" target="_blank">A post shared by Acid Solder Club (@acidsolderclub)</a></p></div></blockquote>
<script async src="//www.instagram.com/embed.js"></script>