# ESP32-S3-MultiFunctionOpenMRNIDF

This is the firmware for various ESP32S3-based "MultiFunction" LCC Node 
boards.
Boards this software will work for include:

- [ESP32-S3-MultiFunction](https://github.com/RobertPHeller/ESP32-LCC/tree/master/ESP32-S3-MultiFunction) original S3-MultiFunction board using a "bare"
  ESP32-S3FN8 chip.
- [ESP32-T7S3-MultiFunction](https://github.com/RobertPHeller/ESP32-LCC/tree/master/ESP32-T7S3-MultiFunction) A version of the original S3-MultiFunction board
  using a TTGO-T7S3 module.
- [ESP32-T7S3-MultiFunctionUniversalTurnout](https://github.com/RobertPHeller/ESP32-LCC/tree/master/ESP32-T7S3-MultiFunctionUniversalTurnout) A version of the 
  T7S3-MultiFunction board using a daughter board for the turnout driver
  allowing four different turnout types (Stall Motor, Single Coil, 
  Twin Coil, and Servo).
- This code will also work on a breadboard version using a ESP32S3 DevKit 
  board.

There are configuration options to adjust how the code is compiled for 
different hardware options.

