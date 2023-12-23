# FogDMX
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
- Two switches and one push button
- 1 Female and one Male XLR socket
- 1 Female MIDI-socket (Connection to fog machine, if your machine uses another type of connector or a hard wired remote, pick up a matching socket or route the wires directly in the enclosure)
- 3D printer (If you don't have one, you can use a lunch box or semilar)
- Some wires
- Heatshrink
- Hot Glue
- 5V power supply (if your fog machine doesn't output 5V on its own, machines with wireless remotes often do that)

#### Materials used by me (which should work and are non-affiliate links)
- https://www.amazon.de/dp/B0097AU5OU?psc=1&ref=ppx_yo2ov_dt_b_product_details
- https://www.amazon.de/dp/B0785B3BS8?psc=1&ref=ppx_yo2ov_dt_b_product_details
- https://www.amazon.de/dp/B07FNGCSZQ?ref=ppx_yo2ov_dt_b_product_details&th=1
- https://www.amazon.de/dp/B078S8SGW2?ref=ppx_yo2ov_dt_b_product_details&th=1
- https://www.amazon.de/dp/B099YM8WC3?psc=1&ref=ppx_yo2ov_dt_b_product_details
- https://www.thomann.de/de/amphenol_ac3fdz.htm
- https://www.thomann.de/de/amphenol_ac3mmdz.htm
- https://www.thomann.de/de/rean_nys_325.htm

## So, how to build this?
