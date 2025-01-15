# FogDMX
First, I'm not a programmer. My code will be janky and unoptimised, but it should work.

Well, hello. Since you are here, you are probably looking for a cheap and easy way to upgrade your generic fog machine to use DMX and to have an variable output. So was I. As I found out, there is no affordable product out there to do that. So I decided to try programming Arduino and a few weeks later, the project was finished.

## Version 2.0 coming soon
Notable features include support for a pwm-controlled fan (it will always use two dmx-channels) and the `nd` when no DMX-signal is detected will flash now.


## What can this do?
This project is essentially two things: An DMX interface to controll a fog machine via DMX, OR a manual remote with an variable output. 
A fixture profile for Daslight is available (Manufacturer: `_Generic`  profile name: `FogDMX 2.0`)


## Tested hardware & Disclaimer
The project is tested on an `ADJ VF 1300`, but as long as your fog machine is triggered using low voltage signals to a control board inside the machine, everything should be fine. If it doesn't and the wires in the remote are as thick as normal power cables, STOP IMMEDIATELY! This probably means that your fogger uses high voltage to trigger, which means that you will take a lot more risk when doing this.
I am not responsible for any damage that might happen when you do this. Just think yourself and stop if you are not comfortable with what you are doing at any point.




## What's included here?
Included are the code, a list of materials and 3D-Models for an enclosure fitting my switches and my potentiometer. You can modify the [3D model](https://www.tinkercad.com/things/fHhk7ptpsdN-fogdmx-case) to match your components.



## Materials (non-affiliate links):
- [Arduino Uno or semilar (I used a Nano)](https://www.amazon.de/dp/B0097AU5OU?psc=1)
- The Arduino-IDE on your computer
- [A MAX-485-board](https://www.amazon.de/dp/B0785B3BS8?psc=1)
- [A Relay](https://www.amazon.de/dp/B07FNGCSZQ)
- [A TM1637 based 4 digit 7-segment-display](https://www.amazon.de/dp/B078S8SGW2)
- [Two switches and one push button](https://www.amazon.de/dp/B099YM8WC3)
- 1 potentiometer
- [1 Female](https://www.thomann.de/de/amphenol_ac3fdz.htm) and [1 Male](https://www.thomann.de/de/amphenol_ac3mmdz.htm) XLR socket
- [1 Female MIDI-socket](https://www.thomann.de/de/rean_nys_325.htm) (Connection to fog machine, if your machine uses another type of connector or a hard wired remote, pick up a matching socket or route the wires directly in the enclosure)
- 3D printer (If you don't have one, you can use a lunch box or semilar) [3D model](https://www.tinkercad.com/things/fHhk7ptpsdN-fogdmx-case)
- Some wires
- Heatshrink
- Hot Glue
- 5V power supply (if your fog machine doesn't output 5V on its own, machines with wireless remotes often do that)



## So, how to build this?
- First, download the arduino sketch and open it in Arduino IDE. Then, use the library manager to install `TM1637 Driver (by AKJ, Version 2.1.2)` and `DMXSerial (by Matthias Hertel, Version 1.5.3)`
- Now take a look at the values on top. If you want, you can modify these to fit your needs. What these values do is explained next to them and under **tuning**. **WARNING!** If you modify these values, your fog machine might not respond or the following instructions might not name the right connections to make anymore. If you are unsure about this, try the default values first.
- Now plug in your Arduino and upload the sketch. This way, you will be able to test as you solder up or plug in the connections.


### The time has come to connect up your components.
You can use dupont-connectors, however for reliability-reasons I wouldn't reccoment them in the final assembly. Soldering is not that hard and it WILL be a nightmare to diagnose one loose connection (naturally right when the machine needs to work)

- I would reccomend starting with the signal wires, as positive and ground connections need to be grouped together later.
- First solder your wires to the individual componets and make connections to the arduino last, ideally after figuring out the placement of all components in your case.

#### But what goes where?
- Display: 	`CLK -> Pin 3`		`DIO -> Pin 4`		`GND -> GND`		`VCC -> +5V`
- Relais: 	`IN -> Pin 5`		`GND -> GND`		`VCC -> +5V`
- MAX-485:	`GND -> GND + DE`		  `VCC -> +5V`		`B -> DMX-Pin 2	A -> DMX-Pin 3`	  	`R0 -> D0/RX (Through a switch)`
- Push-Button:	Connect between Pin 6 and GND
- Switch:				Connect between Pin 7 and GND
- Pot:					Connect between A0 and GND, ensuring the far left position gives the least resistance
- DMX-Out: 			Can just be connected to the corresponding pins on DMX-In
- MIDI-In:			Bit complicated. Grap a multimeter and figure out, where ground, +5V and the trigger pin are, when connected to your fog machine. Then connect GND to GND, +5V to +5V and the trigger through the normally open contacts of the relay to GND. If you do this the wrong way around (through normally closed), don't panic as this is fixable in software (will just take a few minutes)


### Now, TEST!
Connect you new controller to your fog machine and DMX-controller and test everything. If all went right, you should now have a fully functioning DMX-controlled fog machine!
**Don't forget to glue down everything in the enclosure with hot glue (and maybe cable-manage better than me)**



# How to use the controller
Start it by connecting to power, either through the fog machine or, if you want to test without fog, by using a USB power bank. The controller will start and greet you with `HI`, then it will display the current mode. This is a good time to rotate the external switch to match up with the legend on the box. If you missed the mode, no problem! Just switch modes, the newly selected mode will be displayed.
### d512 - DMX-mode
Your controller now listens for a DMX-signal and displays the channel it is listening on. To change the channel, press the push-button and rotate the pot. The channel shown in the display will be set once you let go of the push-button. In order to start on a specific channel every time, check out **Tuning**.

### bUtn - Manual mode
Your controller displays the current pot value in the display (range same as DMX-channel, `0-255`). When you press the push-button, your fog machine will fire as if that DMX-value was set via DMX. You CAN rotate the pot while firing, just mind that because of my poor programming skills, the rate at which the pot is polled (asked for its value) is proportional to its value. The lower the value, the longer it will take for a change to be registerd while firing.


# Tuning
Since the sketch allows for customization, I will mention the tuning that might be done. Nothing here can break your stuff, however it can absolutely result in the remote not functioning. Just reupload the original sketch and you should be fine! Speaking of, any time you change a value, you will need to reupload the sketch to your arduino. Since the serial connection (and the Nano has only one) is used by the DMX-Input, you can't simply upload, as the same interface is used for USB-communication. This is where that switch in `R0 -> D0/RX` comes into play. Flipping it off shuts off the DMX-connection, allowing you to upload your sketch. Just remember to flip it back on afterwards, else you can't get a DMX-signal, no matter how hard you try.


#### Timings
On top of the sketch, you can adjust a few timings: How long the signal (to the fog machine) is on and the minimum and maximum time the signal is switched off, essentially allowing you to adjust the range available.
In terms of timing (how long the signal is on), lower = better. Turn this number down and test if your fog machine still responds every time you hear the relais. Keep going until it doesn't anymore and then back off slightly, to get a reliable setting. **NOTE:** With a mechanical relay, there is a limit to how fast you can go. For my relay, it was ~7ms. 
If your fog machine doesn't respond every time on default settings, increase the number until it responds every time and then add a few ms to be safe.
The range adjustment should need no explanation. `min` is the offtime for minimal output and `max` the offtime for maximal output of fog.


#### DMX-related settings
On top there are also two DMX-related settings: The default channel and the minimal DMX-value required to turn the output on. There isn't much more to it.


#### Pot-range
In lines `110 to 112` and `125 to 127` you can see how the pot input (which can be between 0 and 1023) is mapped to the required range of values.
```
        if(pot_val >= 15 && pot_val <= 700){pot_val=map(pot_val, 15, 700,1,64);}
        else if(pot_val < 15){pot_val = 1;}
        else if(pot_val > 700){pot_val = 64;}
```
**This is to map the pot for DMX-channel selection**, where `15` is the minimal value and `700` the maximal value. You can also change the range of channels available for manual selection, where `1` is minimum and `64` is maximum. Depending on your pot, you might change these values to allow for full use of the rotation of your pot or to make channel selection easier or make more channels available.


#### Inverting relay
Whereever the software writes to the relay, `digitalWrite(out,X)` is used. X is the value written. Just swap 1's with 0's and the other way around.


## Known bugs - Fixes much appreciated :-)
- DMX-signal detection doesn't work right. When a DMX-signal is present, all is fine. When it is lost, the controller switches between having a DMX-signal and not having one periodically, even when nothing is connected to the DMX-ports.
- Program essentially stops when waiting, which can delay responses by up to 1s (default values). Async waits would be a solution, however I can't program that.

## Features I'm too dumb to program - pls send help
- Support for a pixel-based display. I've looked into it, but couldn't find a library that would allow me to print simple text as that's all thats needed (right now)
- Timer function
- Support for a PWM-out to control a fan through a second DMX-channel. The fan should turn off when no fog is triggered and turn on at the set value when the DMX-command for fog is recieved, however before the actual fog is triggered (to allow it to spin up, the delay should be configurable).
