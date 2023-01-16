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
LIBS:ESP32-OctalServo-cache
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
L ESP32_DEVKIT_C U201
U 1 1 63C440B3
P 5200 3150
F 0 "U201" H 5200 3150 60  0000 C CNN
F 1 "ESP32_DEVKIT_C" H 5200 3700 60  0000 C CNN
F 2 "ESP32Boards:ESP32-Devkit-C" H 5200 3150 60  0001 C CNN
F 3 "" H 5200 3150 60  0000 C CNN
	1    5200 3150
	1    0    0    -1  
$EndComp
$Comp
L TTGO-T1 U202
U 1 1 63C440CB
P 5225 4500
F 0 "U202" H 5225 4500 60  0000 C CNN
F 1 "TTGO-T1" H 5225 5050 60  0000 C CNN
F 2 "ESP32Boards:TIGO-T1" H 5225 4500 60  0001 C CNN
F 3 "" H 5225 4500 60  0000 C CNN
	1    5225 4500
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR02
U 1 1 63C44252
P 4700 2700
F 0 "#PWR02" H 4700 2550 50  0001 C CNN
F 1 "+3V3" H 4700 2840 50  0000 C CNN
F 2 "" H 4700 2700 50  0001 C CNN
F 3 "" H 4700 2700 50  0001 C CNN
	1    4700 2700
	0    -1   -1   0   
$EndComp
$Comp
L +3V3 #PWR03
U 1 1 63C44288
P 4700 4050
F 0 "#PWR03" H 4700 3900 50  0001 C CNN
F 1 "+3V3" H 4700 4190 50  0000 C CNN
F 2 "" H 4700 4050 50  0001 C CNN
F 3 "" H 4700 4050 50  0001 C CNN
	1    4700 4050
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR04
U 1 1 63C4429B
P 4675 3600
F 0 "#PWR04" H 4675 3450 50  0001 C CNN
F 1 "+5V" H 4675 3740 50  0000 C CNN
F 2 "" H 4675 3600 50  0001 C CNN
F 3 "" H 4675 3600 50  0001 C CNN
	1    4675 3600
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR05
U 1 1 63C442D1
P 5725 4350
F 0 "#PWR05" H 5725 4200 50  0001 C CNN
F 1 "+5V" H 5725 4490 50  0000 C CNN
F 2 "" H 5725 4350 50  0001 C CNN
F 3 "" H 5725 4350 50  0001 C CNN
	1    5725 4350
	0    1    1    0   
$EndComp
$Comp
L GND #PWR06
U 1 1 63C44300
P 4700 4700
F 0 "#PWR06" H 4700 4450 50  0001 C CNN
F 1 "GND" H 4700 4550 50  0000 C CNN
F 2 "" H 4700 4700 50  0001 C CNN
F 3 "" H 4700 4700 50  0001 C CNN
	1    4700 4700
	0    1    1    0   
$EndComp
$Comp
L GND #PWR07
U 1 1 63C44322
P 4675 3350
F 0 "#PWR07" H 4675 3100 50  0001 C CNN
F 1 "GND" H 4675 3200 50  0000 C CNN
F 2 "" H 4675 3350 50  0001 C CNN
F 3 "" H 4675 3350 50  0001 C CNN
	1    4675 3350
	0    1    1    0   
$EndComp
$Comp
L GND #PWR08
U 1 1 63C44341
P 5725 2700
F 0 "#PWR08" H 5725 2450 50  0001 C CNN
F 1 "GND" H 5725 2550 50  0000 C CNN
F 2 "" H 5725 2700 50  0001 C CNN
F 3 "" H 5725 2700 50  0001 C CNN
	1    5725 2700
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR09
U 1 1 63C44366
P 5725 3000
F 0 "#PWR09" H 5725 2750 50  0001 C CNN
F 1 "GND" H 5725 2850 50  0000 C CNN
F 2 "" H 5725 3000 50  0001 C CNN
F 3 "" H 5725 3000 50  0001 C CNN
	1    5725 3000
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR010
U 1 1 63C44377
P 5775 4050
F 0 "#PWR010" H 5775 3800 50  0001 C CNN
F 1 "GND" H 5775 3900 50  0000 C CNN
F 2 "" H 5775 4050 50  0001 C CNN
F 3 "" H 5775 4050 50  0001 C CNN
	1    5775 4050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4700 2700 4750 2700
Wire Wire Line
	4675 3350 4750 3350
Wire Wire Line
	4675 3600 4750 3600
Wire Wire Line
	5650 2700 5725 2700
Wire Wire Line
	5650 3000 5725 3000
Wire Wire Line
	4700 4050 4775 4050
Wire Wire Line
	5675 4050 5775 4050
Wire Wire Line
	5675 4350 5725 4350
Wire Wire Line
	4700 4700 4775 4700
Text Label 4775 4100 2    39   ~ 0
EN
Text Label 4750 2750 2    39   ~ 0
EN
Text Label 4750 2800 2    39   ~ 0
VP
Text Label 4775 4150 2    39   ~ 0
VP
Text Label 4775 4200 2    39   ~ 0
VN
Text Label 4750 2850 2    39   ~ 0
VN
Text Label 4750 2900 2    39   ~ 0
34
Text Label 4775 4250 2    39   ~ 0
34
Text Label 4775 4300 2    39   ~ 0
35
Text Label 4750 2950 2    39   ~ 0
35
Text Label 4750 3000 2    39   ~ 0
32
Text Label 4775 4350 2    39   ~ 0
32
Text Label 4775 4400 2    39   ~ 0
33
Text Label 4750 3050 2    39   ~ 0
33
Text Label 4750 3100 2    39   ~ 0
25
Text Label 4775 4450 2    39   ~ 0
25
Text Label 4775 4500 2    39   ~ 0
26
Text Label 4750 3150 2    39   ~ 0
26
Text Label 4750 3200 2    39   ~ 0
27
Text Label 4750 3250 2    39   ~ 0
14
Text Label 4750 3300 2    39   ~ 0
12
Text Label 4750 3400 2    39   ~ 0
13
Text Label 4750 3450 2    39   ~ 0
D2
Text Label 4750 3500 2    39   ~ 0
D3
Text Label 4750 3550 2    39   ~ 0
CMD
Text Label 4775 4550 2    39   ~ 0
27
Text Label 4775 4600 2    39   ~ 0
14
Text Label 4775 4650 2    39   ~ 0
12
Text Label 4775 4750 2    39   ~ 0
13
Text Label 4775 4800 2    39   ~ 0
D2
Text Label 4775 4850 2    39   ~ 0
D3
Text Label 4775 4900 2    39   ~ 0
CMD
Text Label 5675 4900 0    39   ~ 0
D0
Text Label 5675 4850 0    39   ~ 0
D1
Text Label 5675 4800 0    39   ~ 0
15
Text Label 5675 4750 0    39   ~ 0
2
Text Label 5675 4700 0    39   ~ 0
0
Text Label 5675 4650 0    39   ~ 0
4
Text Label 5675 4600 0    39   ~ 0
16
Text Label 5675 4550 0    39   ~ 0
17
Text Label 5675 4500 0    39   ~ 0
5
Text Label 5675 4400 0    39   ~ 0
19
Text Label 5675 4300 0    39   ~ 0
21
Text Label 5675 4250 0    39   ~ 0
RX
Text Label 5675 4200 0    39   ~ 0
TX
Text Label 5675 4150 0    39   ~ 0
22
Text Label 5675 4100 0    39   ~ 0
23
Text Label 5650 3600 0    39   ~ 0
CLK
Text Label 5650 3550 0    39   ~ 0
D0
Text Label 5650 3500 0    39   ~ 0
D1
Text Label 5650 3450 0    39   ~ 0
15
Text Label 5650 3400 0    39   ~ 0
2
Text Label 5650 3350 0    39   ~ 0
0
Text Label 5650 3300 0    39   ~ 0
4
Text Label 5650 3250 0    39   ~ 0
16
Text Label 5650 3200 0    39   ~ 0
17
Text Label 5650 3150 0    39   ~ 0
5
Text Label 5650 3100 0    39   ~ 0
18
Text Label 5650 3050 0    39   ~ 0
19
Text Label 5650 2950 0    39   ~ 0
21
Text Label 5650 2900 0    39   ~ 0
RX
Text Label 5650 2850 0    39   ~ 0
TX
Text Label 5650 2800 0    39   ~ 0
22
Text Label 5650 2750 0    39   ~ 0
23
Text HLabel 5800 4500 2    39   Output ~ 0
CAN_TX
Text HLabel 5800 4650 2    39   Output ~ 0
CAN_RX
Text HLabel 4575 4650 0    39   Output ~ 0
Servo0
Text HLabel 4575 4750 0    39   Output ~ 0
Servo1
Text HLabel 4575 4600 0    39   Output ~ 0
Servo2
Text HLabel 5800 4800 2    39   Output ~ 0
Servo3
Text HLabel 5800 4600 2    39   Output ~ 0
Servo4
Text HLabel 5800 4550 2    39   Output ~ 0
Servo5
Text HLabel 5800 4450 2    39   Output ~ 0
Servo6
Text HLabel 5800 4400 2    39   Output ~ 0
Servo7
Wire Wire Line
	4775 4650 4575 4650
Wire Wire Line
	5800 4500 5675 4500
Wire Wire Line
	5800 4650 5675 4650
Wire Wire Line
	4775 4750 4575 4750
Wire Wire Line
	4775 4600 4575 4600
Wire Wire Line
	5800 4800 5675 4800
Wire Wire Line
	5800 4600 5675 4600
Wire Wire Line
	5800 4550 5675 4550
Text Label 5675 4450 0    39   ~ 0
18
Wire Wire Line
	5800 4450 5675 4450
Wire Wire Line
	5800 4400 5675 4400
$EndSCHEMATC
