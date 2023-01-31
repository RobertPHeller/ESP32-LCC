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
LIBS:74lv125AN
LIBS:ESP32-S3DK-OctalServo-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L +3V3 #PWR07
U 1 1 63C44252
P 6450 2850
F 0 "#PWR07" H 6450 2700 50  0001 C CNN
F 1 "+3V3" H 6450 2990 50  0000 C CNN
F 2 "" H 6450 2850 50  0001 C CNN
F 3 "" H 6450 2850 50  0001 C CNN
	1    6450 2850
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR08
U 1 1 63C4429B
P 6350 3850
F 0 "#PWR08" H 6350 3700 50  0001 C CNN
F 1 "+5V" H 6350 3990 50  0000 C CNN
F 2 "" H 6350 3850 50  0001 C CNN
F 3 "" H 6350 3850 50  0001 C CNN
	1    6350 3850
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR09
U 1 1 63C44322
P 6150 3900
F 0 "#PWR09" H 6150 3650 50  0001 C CNN
F 1 "GND" H 6150 3750 50  0000 C CNN
F 2 "" H 6150 3900 50  0001 C CNN
F 3 "" H 6150 3900 50  0001 C CNN
	1    6150 3900
	0    1    1    0   
$EndComp
$Comp
L GND #PWR010
U 1 1 63C44377
P 7600 3900
F 0 "#PWR010" H 7600 3650 50  0001 C CNN
F 1 "GND" H 7600 3750 50  0000 C CNN
F 2 "" H 7600 3900 50  0001 C CNN
F 3 "" H 7600 3900 50  0001 C CNN
	1    7600 3900
	0    -1   -1   0   
$EndComp
Text HLabel 6325 3050 0    39   Output ~ 0
CAN_TX
Text HLabel 6325 3000 0    39   Input ~ 0
CAN_RX
Text HLabel 6350 3650 0    39   Output ~ 0
Servo0
Text HLabel 6350 3700 0    39   Output ~ 0
Servo1
Text HLabel 6350 3750 0    39   Output ~ 0
Servo2
Text HLabel 6350 3800 0    39   Output ~ 0
Servo3
Text HLabel 6325 3200 0    39   Output ~ 0
Servo4
Text HLabel 6325 3250 0    39   Output ~ 0
Servo5
Text HLabel 6325 3300 0    39   Output ~ 0
Servo6
Text HLabel 6325 3350 0    39   Output ~ 0
Servo7
$Comp
L ESP32_S3-DEVKIT U201
U 1 1 63C5BDB7
P 6900 3300
F 0 "U201" H 6900 3300 60  0000 C CNN
F 1 "ESP32_S3-DEVKIT" H 6900 3850 60  0000 C CNN
F 2 "ESP32-Boards:ESP32-S3-Devkit-C" H 6900 3300 60  0001 C CNN
F 3 "" H 6900 3300 60  0000 C CNN
	1    6900 3300
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR011
U 1 1 63C5BEEA
P 6450 2900
F 0 "#PWR011" H 6450 2750 50  0001 C CNN
F 1 "+3V3" H 6450 3040 50  0000 C CNN
F 2 "" H 6450 2900 50  0001 C CNN
F 3 "" H 6450 2900 50  0001 C CNN
	1    6450 2900
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR012
U 1 1 63C5C45F
P 7450 2850
F 0 "#PWR012" H 7450 2600 50  0001 C CNN
F 1 "GND" H 7450 2700 50  0000 C CNN
F 2 "" H 7450 2850 50  0001 C CNN
F 3 "" H 7450 2850 50  0001 C CNN
	1    7450 2850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7450 2850 7350 2850
Wire Wire Line
	7350 3900 7600 3900
Wire Wire Line
	7350 3850 7350 3900
Wire Wire Line
	6450 3900 6150 3900
Wire Wire Line
	6450 3850 6350 3850
Wire Wire Line
	6450 3350 6325 3350
Wire Wire Line
	6450 3300 6325 3300
Wire Wire Line
	6450 3250 6325 3250
Wire Wire Line
	6450 3200 6325 3200
Wire Wire Line
	6450 3800 6350 3800
Wire Wire Line
	6450 3750 6350 3750
Wire Wire Line
	6450 3700 6350 3700
Wire Wire Line
	6450 3650 6350 3650
Wire Wire Line
	6450 3050 6325 3050
Wire Wire Line
	6450 3000 6325 3000
NoConn ~ 7350 2900
NoConn ~ 7350 2950
NoConn ~ 7350 3000
NoConn ~ 7350 3050
NoConn ~ 7350 3100
NoConn ~ 7350 3150
NoConn ~ 7350 3200
NoConn ~ 7350 3250
NoConn ~ 7350 3300
NoConn ~ 7350 3350
NoConn ~ 7350 3400
NoConn ~ 7350 3450
NoConn ~ 7350 3500
NoConn ~ 7350 3550
NoConn ~ 7350 3600
NoConn ~ 7350 3650
NoConn ~ 7350 3700
NoConn ~ 7350 3750
NoConn ~ 7350 3800
NoConn ~ 6450 2950
NoConn ~ 6450 3100
NoConn ~ 6450 3150
NoConn ~ 6450 3400
NoConn ~ 6450 3450
NoConn ~ 6450 3500
NoConn ~ 6450 3550
NoConn ~ 6450 3600
$EndSCHEMATC
