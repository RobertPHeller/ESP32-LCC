# ESP32-LCC

This is a collection of Model Railroad open hardware and open source projects,
using LCC /  OpenMRNIDF, for the ESP32 family of MCUs

These projects were created using Kicad 2013.06.11
(https://launchpad.net/kicad) under CentOS 6 and Kicad 4.0.7 under Ubuntu
18.04. Each subdirectory is one project, and contains a schematic and PCB
design or contains a program for one (or more) projects. There is also
software for the boards using OpenMRNIDF (C++ library for OpenLCB/LCC) for these
projects.

There is a README in each project dir.


1. [ESP32-16LedDriver](https://github.com/RobertPHeller/RPi-RRCircuits/tree/master/ESP32-16LedDriver)

    > 16 on/off LED Driver board using a MCP23017.

1. [ESP32-16PWMLedDriver](https://github.com/RobertPHeller/RPi-RRCircuits/tree/master/ESP32-16PWMLedDriver)

    > 16 LED PWM driver board using a PCA9685.

1. [ESP32-16xDCCOD](https://github.com/RobertPHeller/RPi-RRCircuits/tree/master/ESP32-16xDCCOD)

    > Backplane for up to 16 DCCOD_SMD's using a ESP32 MCU.  Meant as a thought 
    > experiment to see what this would cost, etc.

1. [ESP32-D0WD-V3-MultiFunctionOpenMRNIDF](https://github.com/RobertPHeller/RPi-RRCircuits/tree/master/ESP32-D0WD-V3-MultiFunctionOpenMRNIDF)

    > 

1. [ESP32-HalfSiding](https://github.com/RobertPHeller/RPi-RRCircuits/tree/master/ESP32-HalfSiding)

    > First draft of a ESP32 HalfSiding node using a MCP23017 on/off signal lamps.

1. [ESP32-MultiFunction](https://github.com/RobertPHeller/RPi-RRCircuits/tree/master/ESP32-MultiFunction)

    > This is a circuit board that supports an ESP32 Dev Kit board or TTGO-T1 board
    > to manage a range of possible interlocking plants or other model railroad
    > situations. It contains four stall motor drivers with point sense, four CT
    > Coil type occupancy detectors, four Schmitt-Trigger inputs (for push buttons),
    > four driver outputs, and 16 PWM LED drivers.

1. [ESP32-PWMHalfSiding](https://github.com/RobertPHeller/RPi-RRCircuits/tree/master/ESP32-PWMHalfSiding)

    > This is a circuit board that supports an ESP32 Dev Kit board or TTGO-T1 board 
    > to manage one half (one end) of a siding.  This board can also be used to 
    > manage two bi-directional single track ABS blocks or one bi-directional dual 
    > track ABS block.  There are other trackwork cases this board can handle as 
    > well.  

1. [ESP32-PWMHalfSidingSMD](https://github.com/RobertPHeller/RPi-RRCircuits/tree/master/ESP32-PWMHalfSidingSMD)

    > This is a circuit board that supports an ESP32 Dev Kit board or TTGO-T1 board 
    > to manage one half (one end) of a siding.  This board can also be used to 
    > manage two bi-directional single track ABS blocks or one bi-directional dual 
    > track ABS block.  There are other trackwork cases this board can handle as 
    > well.  

1. [ESP32-S3-MultiFunction](https://github.com/RobertPHeller/RPi-RRCircuits/tree/master/ESP32-S3-MultiFunction)

    > This is a LCC node circuit board that is based around an Espressif ESP32-S3FN8
    > MCU to manage and operate a collection of model railroad sensors and
    > actuators. 

1. [ESP32-S3-MultiFunctionOpenMRNIDF](https://github.com/RobertPHeller/RPi-RRCircuits/tree/master/ESP32-S3-MultiFunctionOpenMRNIDF)

    > 

1. [ESP32_mini_KiCad_Library](https://github.com/RobertPHeller/RPi-RRCircuits/tree/master/ESP32_mini_KiCad_Library)

    > KiCad symbol and footprint for the ESP32 Mini, the ESP32 clone of the Wemos D1 mini with more pins and more power!
    > There is some info on the boards [here](https://www.reddit.com/r/esp8266/comments/a93raj/wemos_ttgo_mini_d1_esp32/). It seems to be a Wemos clone, but is def. not made by them. I really like the boards for the small size and cheap price while giving me the power of an ESP32 and much more IO compared to the Wemos D1 mini.

1. [ESP32ABSBoard](https://github.com/RobertPHeller/RPi-RRCircuits/tree/master/ESP32ABSBoard)

    > ESP32 ABS (Automatic Block Signal) board.  Very simple board: one block 
    > detector, 8 LED drivers.

1. [ESP32BaseBoard](https://github.com/RobertPHeller/RPi-RRCircuits/tree/master/ESP32BaseBoard)

    > ESP32 Base board.  Base starting point for a ESP32 node.

1. [ESP32MRNSketches](https://github.com/RobertPHeller/RPi-RRCircuits/tree/master/ESP32MRNSketches)

    > ESP32 Arduino / OpenMRNLite sketches for the ESP32 boards.

1. [ESP32QuadOCDect](https://github.com/RobertPHeller/RPi-RRCircuits/tree/master/ESP32QuadOCDect)

    > ESP32 Quad Occupancy Detector node.

1. [ESP32QuadSMCSense](https://github.com/RobertPHeller/RPi-RRCircuits/tree/master/ESP32QuadSMCSense)

    > ESP32 Quad Stall Motor w/ sense node.

1. [OpenMRNIDF](https://github.com/RobertPHeller/RPi-RRCircuits/tree/master/OpenMRNIDF)

    > This is an exported version of the OpenMRN library for the ESP32 which is
    > usable as an ESP-IDF component.

