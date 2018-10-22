# Instructions for Physically Connections, including Reference Electrode


---------- Forwarded message ----------  
From: Sander Smit <info@paleoterra.nl>  
Date: Mon, Nov 6, 2017 at 11:14 AM  
Subject: Reference electrode connections  
To: Beth Fisher <fisherba@umn.edu>  


Hi Beth,

See attached [wiring diagram, AO4.jpg]; probably need to rotate.

From left to right:

Connect two resistors in series from 3.3V to GND. E.g. 10kOhm each.
Halfway the resistors the potential is 1.65V.

20 kOhm over 3.3V draws 165 uA. Using 100kOhm resistors brings the
current down to 16.5 uA.

Probably best to stabilize the 1.65V using a capacitor between the
1.65V and GND. E.g. 10 uF, or 1uF.

Connect the reference electrode (inner core of coax) to the 1.65V.

Also connect the 1.65V to the gray wire(s) of the redox probe(s).
The 1.65V is fed into the redox probe ADC (analog to digital
converter) as the ADC reference voltage.

If both the reference and redox electrodes are in a cup of water, the
redox probe should produce a more or less stable output. If you add
kitchen salt to the water, the output probably changes a bit, but
should also become more stable. Higher EC of the water gives more
stable readings.

Any voltage the redox probe outputs is with respect to the ADC
reference voltage. So if the redox probe reads 0.5V, this means the
potential of the redox electrode is at 0.5V above 1.65V (as seen by
the datalogger)

The reference electrode also being connected to the 1.65V, the above
translates to the redox potential being 0.5V above the reference
electrode potential.

The reference electrode potential is at a know chemical potential
(e.g. 201 mV versus the Standard Hydrogen Electrode at 25 Celcius).

So a reading of 500 mV implicates the redox electrode is at 701 mV
vs. SHE

If this works in a cup of water, move the probes into houseplant
earth (or perhaps the garden). Hopefully a bit lower redox potential,
depending on how well aerated the houseplant soil is. I often test in
umbrella grass in swampy earth. Should produce day and night
oscillations because the roots release oxygen during the day and
consume oxygen during the night.


Met vriendelijke groet,

Sander Smit

Paleo Terra - Mariotteplein 41 - 1098 NX Amsterdam
paleoterra@xs4all.nl - 06-81640550
