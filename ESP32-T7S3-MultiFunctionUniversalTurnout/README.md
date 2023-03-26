# ESP32-T7S3-MultiFunctionUniversalTurnout

This is a LCC node circuit board that is based around an Lily Go TTGO-T7S3
(Mini32) board to manage and operate a collection of model railroad sensors and
actuators. 

The board contains these I/O sections:

- Four occupancy detectors. CT Coil type sensors, so they won't work with DC
systems without an AC bias.
- Four turnout drivers with point sense.  These are on a daughter board.  There
are four daughter board types: one for stall motors (Tortoise and the like),
one for single-coil motors (Kato), one for twin-coil motors (Atlas, Peco), and
one for servos.
- Four Schmitt Trigger inputs, meant for push buttons.
- Four Buffered outputs, by default for Panel LEDS, but with drop in
resistors, can also drive relays or other loads.
- Sixteen PWM Led drivers. These are meant to light (LED) lamps in signal
heads.

The board connects to a LCC network and utilizes the Event Transport Protocol
in its operation. It also uses a CDI to describe its configuration. It can be
configured with JMRI or other available LCC configuration tools.

The board draws about 100ma, plus load. There are 16 signal lamp outputs that
have 1.5K Ohm load resistors, this means about 8ma per LED. If all lamps are
on at full brightness, this comes to 128ma, although turning all 16 signal
lamps on full at a time is not likely to be prototypical, since most signal
aspects only light one lamp per head. There is a terminal block to optionally
supply external power for the signal lamps, as a way to reduce the load on the
LCC power bus. The buffered output section uses an external power source, so
does not add any load to the LCC power bus.

This board is a multi-purpose board that can be used in a number of
situations, including (but not limited to): one end of a siding, a yard or
terminal throat, ABS, and interlocking plants.</p>


## Firmware

The firmware for this board is [ESP32-S3-MultiFunctionOpenMRNIDF](https://github.com/RobertPHeller/ESP32-LCC/tree/master/ESP32-S3-MultiFunctionOpenMRNIDF).

## Kit booket

There is LaTeX source for the kit booklet in [KitBooklet](https://github.com/RobertPHeller/ESP32-LCC/tree/master/ESP32-T7S3-MultiFunctionUniversalTurnout/KitBooklet).
