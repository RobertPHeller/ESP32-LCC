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
Sheet 2 5
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
L ESP32_S3-DEVKIT U301
U 1 1 63D930F7
P 5000 3275
F 0 "U301" H 5000 3275 60  0000 C CNN
F 1 "ESP32_S3-DEVKIT" H 5000 3825 60  0000 C CNN
F 2 "ESP32-Boards:ESP32-S3-Devkit-C" H 5000 3275 60  0001 C CNN
F 3 "" H 5000 3275 60  0000 C CNN
	1    5000 3275
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR01
U 1 1 63D930F8
P 4450 3825
F 0 "#PWR01" H 4450 3675 50  0001 C CNN
F 1 "+5V" H 4450 3965 50  0000 C CNN
F 2 "" H 4450 3825 50  0001 C CNN
F 3 "" H 4450 3825 50  0001 C CNN
	1    4450 3825
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR02
U 1 1 63D930F9
P 4550 3950
F 0 "#PWR02" H 4550 3700 50  0001 C CNN
F 1 "GND" H 4550 3800 50  0000 C CNN
F 2 "" H 4550 3950 50  0001 C CNN
F 3 "" H 4550 3950 50  0001 C CNN
	1    4550 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 63D930FA
P 5450 3950
F 0 "#PWR03" H 5450 3700 50  0001 C CNN
F 1 "GND" H 5450 3800 50  0000 C CNN
F 2 "" H 5450 3950 50  0001 C CNN
F 3 "" H 5450 3950 50  0001 C CNN
	1    5450 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 63D930FB
P 5525 2825
F 0 "#PWR04" H 5525 2575 50  0001 C CNN
F 1 "GND" H 5525 2675 50  0000 C CNN
F 2 "" H 5525 2825 50  0001 C CNN
F 3 "" H 5525 2825 50  0001 C CNN
	1    5525 2825
	0    -1   -1   0   
$EndComp
Text HLabel 4450 2975 0    39   Input ~ 0
CAN_RX
Text HLabel 4450 3025 0    39   Output ~ 0
CAN_TX
Wire Wire Line
	4450 2975 4550 2975
Wire Wire Line
	4450 3025 4550 3025
Wire Wire Line
	5525 2825 5450 2825
Wire Wire Line
	5450 3825 5450 3950
Connection ~ 5450 3875
Wire Wire Line
	4550 3825 4450 3825
Wire Wire Line
	4550 3875 4550 3950
Text HLabel 4450 3075 0    39   Output ~ 0
GPIO6/Motor1
Text HLabel 4450 3125 0    39   Output ~ 0
GPIO7/Motor2
Text HLabel 4450 3175 0    39   Output ~ 0
GPIO15/Motor3
Text HLabel 4450 3225 0    39   Output ~ 0
GPIO16/Motor4
Text HLabel 4450 3375 0    39   Output ~ 0
GPIO8/Motor5
Text HLabel 4450 3425 0    39   Output ~ 0
GPIO3/Motor6
Text HLabel 4450 3475 0    39   Output ~ 0
GPIO46/Motor7
Text HLabel 4450 3525 0    39   Output ~ 0
GPIO9/Motor8
Wire Wire Line
	4550 3075 4450 3075
Wire Wire Line
	4550 3125 4450 3125
Wire Wire Line
	4550 3175 4450 3175
Wire Wire Line
	4550 3225 4450 3225
Wire Wire Line
	4550 3375 4450 3375
Wire Wire Line
	4550 3425 4450 3425
Wire Wire Line
	4550 3475 4450 3475
Wire Wire Line
	4550 3525 4450 3525
NoConn ~ 4550 2925
NoConn ~ 4550 3275
NoConn ~ 4550 3325
NoConn ~ 4550 3575
NoConn ~ 4550 3625
NoConn ~ 4550 3675
NoConn ~ 4550 3725
NoConn ~ 4550 3775
NoConn ~ 5450 3775
NoConn ~ 5450 3725
NoConn ~ 5450 3675
NoConn ~ 5450 3625
NoConn ~ 5450 3575
NoConn ~ 5450 2875
NoConn ~ 5450 2925
NoConn ~ 5450 2975
NoConn ~ 5450 3025
NoConn ~ 5450 3075
NoConn ~ 5450 3125
NoConn ~ 5450 3175
NoConn ~ 5450 3225
NoConn ~ 5450 3275
NoConn ~ 5450 3325
NoConn ~ 5450 3375
NoConn ~ 5450 3425
NoConn ~ 5450 3475
NoConn ~ 5450 3525
$Comp
L +3V3 #PWR05
U 1 1 63D930FC
P 4550 2750
F 0 "#PWR05" H 4550 2600 50  0001 C CNN
F 1 "+3V3" H 4550 2890 50  0000 C CNN
F 2 "" H 4550 2750 50  0001 C CNN
F 3 "" H 4550 2750 50  0001 C CNN
	1    4550 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 2750 4550 2875
Connection ~ 4550 2825
$EndSCHEMATC
