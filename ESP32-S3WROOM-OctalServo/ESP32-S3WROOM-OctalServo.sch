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
LIBS:esp32_devboards
LIBS:lm2574n-5
LIBS:ap63205
LIBS:esp32_s3_wroom
LIBS:USBLC6-2SC6
LIBS:gct_usb4105
LIBS:ESP32-S3WROOM-OctalServo-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 4
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
U 632C7FD0
F0 "MCU" 60
F1 "MCU.sch" 60
F2 "CAN_TX" O L 3375 2200 60 
F3 "CAN_RX" I L 3375 2400 60 
F4 "Servo0" O R 6725 3125 60 
F5 "Servo1" O R 6725 3500 60 
F6 "Servo2" O R 6725 3975 60 
F7 "Servo3" O R 6725 4375 60 
F8 "Servo4" O R 6725 4750 60 
F9 "Servo5" O R 6725 5075 60 
F10 "Servo6" O R 6725 5400 60 
F11 "Servo7" O R 6725 5750 60 
$EndSheet
$Sheet
S 600  1800 2300 1950
U 632C7FE7
F0 "CAN Transciver" 60
F1 "CanTransciver.sch" 60
F2 "CAN_TX" I R 2900 2200 60 
F3 "CAN_RX" O R 2900 2400 60 
$EndSheet
$Sheet
S 600  4200 2325 1825
U 632C8003
F0 "Power Supply" 60
F1 "PowerSupply.sch" 60
$EndSheet
$Comp
L Screw_Terminal_01x02 J101
U 1 1 63C46065
P 7125 6275
F 0 "J101" H 7125 6375 50  0000 C CNN
F 1 "+ 5V Servo -" H 7125 6075 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_PT-3.5mm_2pol" H 7125 6275 50  0001 C CNN
F 3 "" H 7125 6275 50  0001 C CNN
	1    7125 6275
	0    1    1    0   
$EndComp
$Comp
L Conn_01x03_Male J109
U 1 1 63C46616
P 7525 5850
F 0 "J109" H 7525 6050 50  0000 C CNN
F 1 "Servo 8" H 7525 5650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 7525 5850 50  0001 C CNN
F 3 "" H 7525 5850 50  0001 C CNN
	1    7525 5850
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x03_Male J108
U 1 1 63C48526
P 7525 5500
F 0 "J108" H 7525 5700 50  0000 C CNN
F 1 "Servo 7" H 7525 5300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 7525 5500 50  0001 C CNN
F 3 "" H 7525 5500 50  0001 C CNN
	1    7525 5500
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x03_Male J107
U 1 1 63C485CA
P 7525 5175
F 0 "J107" H 7525 5375 50  0000 C CNN
F 1 "Servo 6" H 7525 4975 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 7525 5175 50  0001 C CNN
F 3 "" H 7525 5175 50  0001 C CNN
	1    7525 5175
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x03_Male J106
U 1 1 63C48686
P 7525 4850
F 0 "J106" H 7525 5050 50  0000 C CNN
F 1 "Servo 5" H 7525 4650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 7525 4850 50  0001 C CNN
F 3 "" H 7525 4850 50  0001 C CNN
	1    7525 4850
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x03_Male J105
U 1 1 63C48A09
P 7525 4475
F 0 "J105" H 7525 4675 50  0000 C CNN
F 1 "Servo 4" H 7525 4275 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 7525 4475 50  0001 C CNN
F 3 "" H 7525 4475 50  0001 C CNN
	1    7525 4475
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x03_Male J104
U 1 1 63C48AF3
P 7525 4075
F 0 "J104" H 7525 4275 50  0000 C CNN
F 1 "Servo 3" H 7525 3875 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 7525 4075 50  0001 C CNN
F 3 "" H 7525 4075 50  0001 C CNN
	1    7525 4075
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x03_Male J103
U 1 1 63C4A471
P 7525 3600
F 0 "J103" H 7525 3800 50  0000 C CNN
F 1 "Servo 2" H 7525 3400 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 7525 3600 50  0001 C CNN
F 3 "" H 7525 3600 50  0001 C CNN
	1    7525 3600
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x03_Male J102
U 1 1 63C4A517
P 7525 3225
F 0 "J102" H 7525 3425 50  0000 C CNN
F 1 "Servo 1" H 7525 3025 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 7525 3225 50  0001 C CNN
F 3 "" H 7525 3225 50  0001 C CNN
	1    7525 3225
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 63C4DD29
P 7275 6150
F 0 "#PWR01" H 7275 5900 50  0001 C CNN
F 1 "GND" H 7275 6000 50  0000 C CNN
F 2 "" H 7275 6150 50  0001 C CNN
F 3 "" H 7275 6150 50  0001 C CNN
	1    7275 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6725 3500 7325 3500
Wire Wire Line
	6725 3975 7325 3975
Wire Wire Line
	6725 4375 7325 4375
Wire Wire Line
	6725 4750 7325 4750
Wire Wire Line
	6725 5075 7325 5075
Wire Wire Line
	6725 5400 7325 5400
Wire Wire Line
	6725 5750 7325 5750
Wire Wire Line
	7125 3225 7125 6075
Wire Wire Line
	7125 5850 7325 5850
Wire Wire Line
	7125 5500 7325 5500
Connection ~ 7125 5850
Wire Wire Line
	7125 5175 7325 5175
Connection ~ 7125 5500
Wire Wire Line
	7325 4850 7125 4850
Connection ~ 7125 5175
Wire Wire Line
	7325 4475 7125 4475
Connection ~ 7125 4850
Wire Wire Line
	7325 4075 7125 4075
Connection ~ 7125 4475
Wire Wire Line
	7125 3600 7325 3600
Connection ~ 7125 4075
Wire Wire Line
	7125 3225 7325 3225
Connection ~ 7125 3600
Wire Wire Line
	7325 5950 7025 5950
Wire Wire Line
	7025 3325 7025 6075
Wire Wire Line
	7275 6150 7275 5950
Connection ~ 7275 5950
Wire Wire Line
	7325 5600 7025 5600
Connection ~ 7025 5950
Wire Wire Line
	7025 5275 7325 5275
Connection ~ 7025 5600
Wire Wire Line
	7025 4950 7325 4950
Connection ~ 7025 5275
Wire Wire Line
	7025 4575 7325 4575
Connection ~ 7025 4950
Wire Wire Line
	7025 4175 7325 4175
Connection ~ 7025 4575
Wire Wire Line
	7025 3700 7325 3700
Connection ~ 7025 4175
Wire Wire Line
	7025 3325 7325 3325
Connection ~ 7025 3700
Wire Wire Line
	7325 3125 6725 3125
Wire Wire Line
	3375 2200 2900 2200
Wire Wire Line
	2900 2400 3375 2400
$EndSCHEMATC
