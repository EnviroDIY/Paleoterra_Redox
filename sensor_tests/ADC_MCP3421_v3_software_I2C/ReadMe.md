# Docs on ADC_MCP3421_v3_software_I2C.ino


#### From: Sander Smit <info@paleoterra.nl>
Date: Wed, Oct 4, 2017 at 4:43 AM
Subject: Re: Active redox probe order
To: Beth Fisher <fisherba@umn.edu>

Attached my Arduino sketch as I already pasted into an email before
(but probably easier to use the attached file when starting to test).
I'm using software I2C because it allows to slow down I2C
communications if long cable or cable in wet soil may make this
necessary. See https://playground.arduino.cc/Main/SoftwareI2CLibrary
and use ``#define I2C_SLOWMODE 1` to slow down the I2C comms.

The active probes have 5 wires:
- green: I2C SDA
- yellow: I2C SCL
- white: Vdd (supply between 4V and 6V)
- brown: GND
- gray: reference

To use the example sketch I attached directly:
- download and install the SoftwareI2CLibrary to your Arduino
  environment
- connect the probe to an Arduino:
  * green to D2
  * yellow to D3
  * white to 5. [UPDATE from 2017-11-06 email: 3.3V would be best for Mayfly I2C lines]
  * brown to GND
  * gray to 3.3V
* redox socket on the probe to 3.3V (or any potential between 1.5V
  and 5V to get different readings)
- supply power and check the serial monitor

The I2C wires need a pullup resistor to Vdd. I've not added this to
the probes as some boards already have a pullup and it would waste
power if these resistors are added twice. Typically insert 10kOhm
between SDA and Vdd and also 10kOhm between SCL and Vdd.

The reference wire connects to the reference electrode. On the
Mayfly, the reference electrode should also be connected to a voltage
between 1.5 and 3.3V.

During initial testing of the probe to Mayfly, it is easiest to leave
the reference electrode out of the setup. Just connect the gray wire
to somewhere between 1.5 and 3.3V.

Instead of a Pt redox sensor, I've made the test probe with a small
socket that accepts 0.5mm diameter wire. This will make it (I hope)
easier to test the Mayfly connections and programming. If the socket
connects to the same potential as the reference wire, 0V should be
read from the sensor. (Actually, I found around 1mV, a small offset
mostly because I've abused the internal board for my own testing
earlier on). Lower / higher voltages to the socket should yield
negative/positive values. The max. difference between reference and
redox potential the sensor can read is 2V. Both reference wire and
redox socket should never be connected to voltages below or above the
power supply limits.

I think this would be all the info you need, but I may have forgotten
(a) part(s), let me know, feel free to ask !!

Met vriendelijke groet,

Sander Smit

Paleo Terra - Mariotteplein 41 - 1098 NX Amsterdam
paleoterra@xs4all.nl - 06-81640550



#### Mon, Nov 6, 2017 at 4:03 AM, Sander Smit <info@paleoterra.nl> wrote:

As soon as you get readable numbers, the I2C is working fine. If
hardware I2C works, just use hardware I2C. Ideally, you test
the I2C with your hardware at e.g. 200kHz, and then run it in the
field at e.g. 50kHz in the field. Often if a cable is in a wet
environment, communications are more difficult.

To slow down I2C you can use Wire.setClock()
https://www.arduino.cc/en/Reference/WireSetClock
or fine tune manually using TWBR, see internet forums and/or your
Atmel chip datasheet for details.

Only if you need to slow down I2C below the slowest hardware option
(30 kHz?), you may need software I2C.



When touching nothing, anything may happen to the readings.
Electromagnetic noise in your house easily imposes a few volt on the
input socket. Move you hand away from the socket while touching
nothing, and the readings will change. The ADC chip is indeed limited
between -2048 and +2048 mV, and outputs one of those when input goes
beyond a limit.


Stabilizing the probe should take a few seconds. 4.52 mV with the
socket connected to the same potential as the reference is not bad.
Probably I already damaged the input circuitry a little when I used
the internal PCB for testing. Also, electromagnetic noise generates an
offset voltage. Part of the trick of moving the measuring electronics
into the redox probes (going from analog to digital probes) is to
move the opamp and ADC into the soil, where far less electromagnetic
noise is present. You would have to use a real probe and reference
electrode in a redox buffer solution to get close the this setup.

For a fresh AA battery, 1550 - 1650 mV is a reasonable reading, and
negative if you connect in opposite way.


The mayfly main part is powered at 3.3V, so Anthony is correct
that input voltages shouldn't go above 3.3V (or 3.8V, 0.5V above Vcc
is normally possible). I don't think 5V on I2C lines will fry the
Mayfly immediately because current is limited, but it is not healthy
for the uC either.

So you should power my probes at 3.3V. They will work fine at that
voltage. To measure redox, you will then need to connect the
reference electrode to somewhere between 1 and 2V.
