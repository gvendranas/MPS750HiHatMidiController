# MPS750HiHatMidiController
This project uses an Arduino Leonardo board to convert MPS750 HiHat Controller analog output to MIDI data. This Arduino sketch is intented to be used with Arduino Leonardo only because this specific HW provides a MIDI output through USB right out of the box, without the need of any kind of bootloader update.
The aim of it is because there is not backwards compatibility between MPS750X HiHat Pad and MPS450 Drum Module, so if you buy a MPS750X HiHat Pad you won't be able to use its build-in controller to change hihat opening status although you will be able to trigger hihat sounds. 
On the other side I wanted to use MPS450 drum module just as a MIDI interface and use Logic Pro X's Drummer as sound generator.
Thus, you can connect your drum module to the computer as usual and connect the hihat controller through a separate PC's USB input and let Drummer do the job. 
The downside of this approach is that hihat hit and hihat opening status are not reported in sync so if you are a good drummer :) or you want to be very expressive with the hihat, you will have to buy a drum module that can handle MPS750X HiHat Pad otherwise that is going to sound weird or just innacurate.
I reverse engineered MPS750X HiHat Pad controller and the connection is:
6.3mm stereo jack
Tip: hihat output. This can be used to sense hihat opening status. I mapped it to Arduino Leonardo A0 pin.
Ring: 5V
Sleeve: GND.

Please do the hack at your own risk. I am not risponsible for any damage caused to your HW or SW.
