---
layout: post
title: "Sending MIDI wirelessly"
permalink: "/midi-bluetooth/"
---


### Using garageband
You can use this code example for various keyboards or drums, but you will probably need to change the MIDI notes sent (check the charts below). CC doesn't always have an effect.


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


## Links

- <https://midi.guide/>