# FogDMX
Software and instructions for building a custom DMX controller for fog machines

First, I'm not a programmer. My code will be janky and unoptimised, but it should work.

Well, hello. Since you are here, you are probably looking for a cheap and easy way to upgrade your generic fog machine to use DMX and to have an variable output. So was I. As I found out, there is no affordable product out there to do that. So I decided to try programming Arduino and a few weeks later, the project was finished.


## What can this do?
This project is essentially two things: An DMX interface to controll a fog machine via DMX, OR a manual remote with an variable output.

## What's included here?
Included are the code, a list of materials and 3D-Models for an enclosure fitting my switches and my potentiometer. You can modify the 3D model to match your components.

## Materials:
- Arduino Uno or semilar (I used a Nano)
- The Arduino-IDE on your computer
- A MAX-485-board
- A Relay
- A TM1637 based 4 digit 7-segment-display
- 1 Female and one Male XLR socket
- 1 Female MIDI-socket (Connection to fog machine, if your machine uses another type of connector or a hard wired remote, pick up a matching socket or route the wires directly in the enclosure)
- 3D printer (If you don't have one, you can use a lunch box or semilar)
- Some wires
- Heatshrink
- Hot Glue

## So, how to build this?
