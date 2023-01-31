EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:sn65hvd233-ht
LIBS:ap63205
LIBS:esp32_devboards
LIBS:tc442x
LIBS:ESP32-S3DK-OctalTwinCoil-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 3375 1525 3350 4925
U 63D925A6
F0 "MCU" 60
F1 "MCU.sch" 60
F2 "CAN_RX" I L 3375 2400 60 
F3 "CAN_TX" O L 3375 2200 60 
F4 "GPIO6/Motor1" O R 6725 2025 60 
F5 "GPIO7/Motor2" O R 6725 2125 60 
F6 "GPIO15/Motor3" O R 6725 2225 60 
F7 "GPIO16/Motor4" O R 6725 2325 60 
F8 "GPIO8/Motor5" O R 6725 2425 60 
F9 "GPIO3/Motor6" O R 6725 2525 60 
F10 "GPIO46/Motor7" O R 6725 2625 60 
F11 "GPIO9/Motor8" O R 6725 2725 60 
$EndSheet
$Sheet
S 600  1800 2300 1950
U 63D925A7
F0 "CAN Transciver" 60
F1 "CAN_Transciver.sch" 60
F2 "CAN_TX" I R 2900 2200 60 
F3 "CAN_RX" O R 2900 2400 60 
$EndSheet
$Sheet
S 600  4200 2325 1825
U 63D925A8
F0 "Power Supply" 60
F1 "PowerSupply.sch" 60
$EndSheet
$Sheet
S 7225 1850 2725 2075
U 63D925A9
F0 "Octal Twin Coil Switch Machine" 60
F1 "8TwinCoilSM.sch" 60
F2 "Motor_1" I L 7225 2025 60 
F3 "Motor_2" I L 7225 2125 60 
F4 "Motor_3" I L 7225 2225 60 
F5 "Motor_4" I L 7225 2325 60 
F6 "Motor_8" I L 7225 2725 60 
F7 "Motor_7" I L 7225 2625 60 
F8 "Motor_6" I L 7225 2525 60 
F9 "Motor_5" I L 7225 2425 60 
$EndSheet
Wire Wire Line
	7225 2025 6725 2025
Wire Wire Line
	6725 2125 7225 2125
Wire Wire Line
	7225 2225 6725 2225
Wire Wire Line
	6725 2325 7225 2325
Wire Wire Line
	7225 2425 6725 2425
Wire Wire Line
	6725 2525 7225 2525
Wire Wire Line
	7225 2625 6725 2625
Wire Wire Line
	6725 2725 7225 2725
Wire Wire Line
	2900 2200 3375 2200
Wire Wire Line
	3375 2400 2900 2400
$EndSCHEMATC
