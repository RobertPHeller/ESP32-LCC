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
L +3V3 #PWR02
U 1 1 63C44252
P 6450 2850
F 0 "#PWR02" H 6450 2700 50  0001 C CNN
F 1 "+3V3" H 6450 2990 50  0000 C CNN
F 2 "" H 6450 2850 50  0001 C CNN
F 3 "" H 6450 2850 50  0001 C CNN
	1    6450 2850
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR04
U 1 1 63C4429B
P 6350 3850
F 0 "#PWR04" H 6350 3700 50  0001 C CNN
F 1 "+5V" H 6350 3990 50  0000 C CNN
F 2 "" H 6350 3850 50  0001 C CNN
F 3 "" H 6350 3850 50  0001 C CNN
	1    6350 3850
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR07
U 1 1 63C44322
P 6150 3900
F 0 "#PWR07" H 6150 3650 50  0001 C CNN
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
Text Label 6450 2950 2    39   ~ 0
EN
Text Label 6450 3800 2    39   ~ 0
14
Text Label 6450 3700 2    39   ~ 0
12
Text Label 6450 3750 2    39   ~ 0
13
Text Label 6450 3250 2    39   ~ 0
16
Text Label 6450 3300 2    39   ~ 0
17
Text Label 7350 3800 0    39   ~ 0
19
Text Label 7350 3700 0    39   ~ 0
21
Text Label 6450 3200 2    39   ~ 0
15
Text Label 7350 3050 0    39   ~ 0
2
Text Label 6450 3000 2    39   ~ 0
4
Text Label 6450 3050 2    39   ~ 0
5
Text Label 7350 2950 0    39   ~ 0
RX
Text Label 7350 2900 0    39   ~ 0
TX
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
Text Label 6450 3350 2    39   ~ 0
18
$Comp
L ESP32_S3-DEVKIT U?
U 1 1 63C5BDB7
P 6900 3300
F 0 "U?" H 6900 3300 60  0000 C CNN
F 1 "ESP32_S3-DEVKIT" H 6900 3850 60  0000 C CNN
F 2 "ESP32-Boards:ESP32-S3-Devkit-C" H 6900 3300 60  0000 C CNN
F 3 "" H 6900 3300 60  0000 C CNN
	1    6900 3300
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR?
U 1 1 63C5BEEA
P 6450 2900
F 0 "#PWR?" H 6450 2750 50  0001 C CNN
F 1 "+3V3" H 6450 3040 50  0000 C CNN
F 2 "" H 6450 2900 50  0001 C CNN
F 3 "" H 6450 2900 50  0001 C CNN
	1    6450 2900
	0    -1   -1   0   
$EndComp
Text Label 6450 3100 2    39   ~ 0
6
Text Label 6450 3150 2    39   ~ 0
7
Text Label 6450 3650 2    39   ~ 0
11
Text Label 6450 3400 2    39   ~ 0
8
Text Label 6450 3450 2    39   ~ 0
3
Text Label 6450 3500 2    39   ~ 0
46
Text Label 6450 3550 2    39   ~ 0
9
Text Label 6450 3600 2    39   ~ 0
10
Text Label 7350 3750 0    39   ~ 0
20
Text Label 7350 3650 0    39   ~ 0
47
Text Label 7350 3600 0    39   ~ 0
48
Text Label 7350 3550 0    39   ~ 0
45
Text Label 7350 3500 0    39   ~ 0
40
Text Label 7350 3450 0    39   ~ 0
35
Text Label 7350 3400 0    39   ~ 0
36
Text Label 7350 3350 0    39   ~ 0
37
Text Label 7350 3300 0    39   ~ 0
38
Text Label 7350 3250 0    39   ~ 0
39
Text Label 7350 3200 0    39   ~ 0
40
Text Label 7350 3150 0    39   ~ 0
41
Text Label 7350 3100 0    39   ~ 0
42
Text Label 7350 3000 0    39   ~ 0
1
$Comp
L GND #PWR?
U 1 1 63C5C45F
P 7450 2850
F 0 "#PWR?" H 7450 2600 50  0001 C CNN
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
$EndSCHEMATC
