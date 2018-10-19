EESchema Schematic File Version 2
LIBS:RPiHalfSiding-cache
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
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
LIBS:tc442x
LIBS:MCP23xxx
LIBS:uln2803a
LIBS:w_device
LIBS:74lv125AN
LIBS:RPiHalfSiding-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 3
Title ""
Date "8 oct 2018"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RPi_GPIO J0
U 1 1 5516AE26
P 1450 1350
F 0 "J0" H 2200 1600 60  0000 C CNN
F 1 "RPi_GPIO" H 2200 1500 60  0000 C CNN
F 2 "RPi_Hat:Pin_Header_Straight_2x20" H 1450 1350 60  0001 C CNN
F 3 "" H 1450 1350 60  0000 C CNN
	1    1450 1350
	1    0    0    -1  
$EndComp
$Sheet
S 4250 1450 1900 1600
U 5BBB66EB
F0 "Signals" 50
F1 "Signals.sch" 50
F2 "SCL" I L 4250 1600 60 
F3 "SDA" B L 4250 1800 60 
$EndSheet
$Sheet
S 1250 4300 1900 1650
U 5BBB671A
F0 "Sensors" 50
F1 "Sensors.sch" 50
F2 "Occupancy" O L 1250 4500 60 
F3 "TX" I L 1250 4700 60 
F4 "RX" O L 1250 4900 60 
F5 "East (Points) Occ" O L 1250 5100 60 
F6 "West Main (Frog Normal) Occ" O L 1250 5300 60 
F7 "West Diverg (Frog Reversed) Occ" O L 1250 5450 60 
$EndSheet
$Comp
L +3.3V #PWR01
U 1 1 5BBB8308
P 1050 1250
F 0 "#PWR01" H 1050 1210 30  0001 C CNN
F 1 "+3.3V" H 1050 1360 30  0000 C CNN
F 2 "" H 1050 1250 60  0000 C CNN
F 3 "" H 1050 1250 60  0000 C CNN
	1    1050 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 1250 1050 2150
Wire Wire Line
	1050 1350 1250 1350
Wire Wire Line
	1050 2150 1250 2150
Connection ~ 1050 1350
$Comp
L +5V #PWR02
U 1 1 5BBB856D
P 3250 1100
F 0 "#PWR02" H 3250 1190 20  0001 C CNN
F 1 "+5V" H 3250 1190 30  0000 C CNN
F 2 "" H 3250 1100 60  0000 C CNN
F 3 "" H 3250 1100 60  0000 C CNN
	1    3250 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 1100 3250 1450
Wire Wire Line
	3250 1450 3150 1450
Wire Wire Line
	3150 1350 3250 1350
Connection ~ 3250 1350
$Comp
L GND #PWR03
U 1 1 5BBB87CE
P 3300 3550
F 0 "#PWR03" H 3300 3550 30  0001 C CNN
F 1 "GND" H 3300 3480 30  0001 C CNN
F 2 "" H 3300 3550 60  0000 C CNN
F 3 "" H 3300 3550 60  0000 C CNN
	1    3300 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 1550 3300 3550
Wire Wire Line
	3300 2950 3150 2950
Wire Wire Line
	3300 2750 3150 2750
Connection ~ 3300 2950
Wire Wire Line
	3300 2250 3150 2250
Connection ~ 3300 2750
Wire Wire Line
	3150 1950 3300 1950
Connection ~ 3300 2250
Wire Wire Line
	3150 1550 3300 1550
Connection ~ 3300 1950
Wire Wire Line
	1250 1750 1100 1750
Wire Wire Line
	1100 1750 1100 3500
Wire Wire Line
	1100 2550 1250 2550
Wire Wire Line
	1100 3250 1250 3250
Connection ~ 1100 2550
Wire Wire Line
	1100 3500 3300 3500
Connection ~ 3300 3500
Connection ~ 1100 3250
Text Label 850  1450 2    28   ~ 0
SDA
Text Label 850  1550 2    28   ~ 0
SCL
Wire Wire Line
	1250 1450 850  1450
Wire Wire Line
	1250 1550 850  1550
Text Label 4050 1600 2    28   ~ 0
SCL
Text Label 4050 1800 2    28   ~ 0
SDA
Wire Wire Line
	4250 1600 4050 1600
Wire Wire Line
	4250 1800 4050 1800
$Comp
L TC4428 U4
U 1 1 5BBB9CF8
P 4850 4250
F 0 "U4" H 4850 3950 60  0000 C CNN
F 1 "TC4428" H 4850 4550 60  0000 C CNN
F 2 "~" H 4850 4250 60  0000 C CNN
F 3 "~" H 4850 4250 60  0000 C CNN
	1    4850 4250
	1    0    0    -1  
$EndComp
$Comp
L TC4428 U4
U 2 1 5BBB9D0D
P 4850 5100
F 0 "U4" H 4850 4800 60  0000 C CNN
F 1 "TC4428" H 4850 5400 60  0000 C CNN
F 2 "~" H 4850 5100 60  0000 C CNN
F 3 "~" H 4850 5100 60  0000 C CNN
	2    4850 5100
	1    0    0    -1  
$EndComp
$Comp
L TC4428 U5
U 1 1 5BBB9D22
P 4850 5950
F 0 "U5" H 4850 5650 60  0000 C CNN
F 1 "TC4428" H 4850 6250 60  0000 C CNN
F 2 "~" H 4850 5950 60  0000 C CNN
F 3 "~" H 4850 5950 60  0000 C CNN
	1    4850 5950
	1    0    0    -1  
$EndComp
$Comp
L TC4428 U5
U 2 1 5BBB9D37
P 4850 6800
F 0 "U5" H 4850 6500 60  0000 C CNN
F 1 "TC4428" H 4850 7100 60  0000 C CNN
F 2 "~" H 4850 6800 60  0000 C CNN
F 3 "~" H 4850 6800 60  0000 C CNN
	2    4850 6800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5BBB9ED6
P 4800 5500
F 0 "#PWR04" H 4800 5500 30  0001 C CNN
F 1 "GND" H 4800 5430 30  0001 C CNN
F 2 "" H 4800 5500 60  0000 C CNN
F 3 "" H 4800 5500 60  0000 C CNN
	1    4800 5500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 5BBBA1C7
P 4800 7200
F 0 "#PWR05" H 4800 7200 30  0001 C CNN
F 1 "GND" H 4800 7130 30  0001 C CNN
F 2 "" H 4800 7200 60  0000 C CNN
F 3 "" H 4800 7200 60  0000 C CNN
	1    4800 7200
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR06
U 1 1 5BBBA404
P 4800 3850
F 0 "#PWR06" H 4800 3800 20  0001 C CNN
F 1 "+12V" H 4800 3950 30  0000 C CNN
F 2 "" H 4800 3850 60  0000 C CNN
F 3 "" H 4800 3850 60  0000 C CNN
	1    4800 3850
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR07
U 1 1 5BBBA781
P 4800 5700
F 0 "#PWR07" H 4800 5650 20  0001 C CNN
F 1 "+12V" H 4800 5800 30  0000 C CNN
F 2 "" H 4800 5700 60  0000 C CNN
F 3 "" H 4800 5700 60  0000 C CNN
	1    4800 5700
	1    0    0    -1  
$EndComp
Text Label 950  1850 2    28   ~ 0
M0_Control
Text Label 3400 1850 0    28   ~ 0
M1_Control
Wire Wire Line
	3400 1850 3150 1850
Wire Wire Line
	950  1850 1250 1850
Text Label 4350 4250 2    28   ~ 0
M0_Control
Text Label 4350 5950 2    28   ~ 0
M1_Control
Wire Wire Line
	4350 4250 4600 4250
Wire Wire Line
	4600 4250 4600 5100
Wire Wire Line
	4350 5950 4600 5950
Wire Wire Line
	4600 5950 4600 6800
Wire Wire Line
	4800 7000 4800 7200
Wire Wire Line
	4800 5300 4800 5500
Wire Wire Line
	4800 5700 4800 5800
Wire Wire Line
	4800 3850 4800 4100
$Comp
L CONN_2 T3
U 1 1 5BBBC297
P 5800 3600
F 0 "T3" V 5750 3600 40  0000 C CNN
F 1 "12 to 15V" V 5850 3600 40  0000 C CNN
F 2 "~" H 5800 3600 60  0000 C CNN
F 3 "~" H 5800 3600 60  0000 C CNN
	1    5800 3600
	1    0    0    -1  
$EndComp
$Comp
L CONN_5 T4
U 1 1 5BBBC349
P 6700 4450
F 0 "T4" V 6650 4450 50  0000 C CNN
F 1 "Motor 0" V 6750 4450 50  0000 C CNN
F 2 "~" H 6700 4450 60  0000 C CNN
F 3 "~" H 6700 4450 60  0000 C CNN
	1    6700 4450
	1    0    0    -1  
$EndComp
$Comp
L CONN_5 T5
U 1 1 5BBBC57A
P 6750 6150
F 0 "T5" V 6700 6150 50  0000 C CNN
F 1 "Motor 1" V 6800 6150 50  0000 C CNN
F 2 "~" H 6750 6150 60  0000 C CNN
F 3 "~" H 6750 6150 60  0000 C CNN
	1    6750 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 4250 6300 4250
Wire Wire Line
	6300 4350 5350 4350
Wire Wire Line
	5350 4350 5350 5100
Wire Wire Line
	5350 5100 5250 5100
Wire Wire Line
	6350 5950 5250 5950
Wire Wire Line
	6350 6050 5350 6050
Wire Wire Line
	5350 6050 5350 6800
Wire Wire Line
	5350 6800 5250 6800
$Comp
L +12V #PWR08
U 1 1 5BBBC91A
P 5450 3400
F 0 "#PWR08" H 5450 3350 20  0001 C CNN
F 1 "+12V" H 5450 3500 30  0000 C CNN
F 2 "" H 5450 3400 60  0000 C CNN
F 3 "" H 5450 3400 60  0000 C CNN
	1    5450 3400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 5BBBC92F
P 5450 3800
F 0 "#PWR09" H 5450 3800 30  0001 C CNN
F 1 "GND" H 5450 3730 30  0001 C CNN
F 2 "" H 5450 3800 60  0000 C CNN
F 3 "" H 5450 3800 60  0000 C CNN
	1    5450 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 3500 5450 3400
Wire Wire Line
	5450 3700 5450 3800
$Comp
L GND #PWR010
U 1 1 5BBBCAC7
P 6200 4550
F 0 "#PWR010" H 6200 4550 30  0001 C CNN
F 1 "GND" H 6200 4480 30  0001 C CNN
F 2 "" H 6200 4550 60  0000 C CNN
F 3 "" H 6200 4550 60  0000 C CNN
	1    6200 4550
	0    1    1    0   
$EndComp
$Comp
L GND #PWR011
U 1 1 5BBBCCAA
P 6200 6250
F 0 "#PWR011" H 6200 6250 30  0001 C CNN
F 1 "GND" H 6200 6180 30  0001 C CNN
F 2 "" H 6200 6250 60  0000 C CNN
F 3 "" H 6200 6250 60  0000 C CNN
	1    6200 6250
	0    1    1    0   
$EndComp
Wire Wire Line
	6350 6250 6200 6250
Wire Wire Line
	6300 4550 6200 4550
$Comp
L 74HC00 U6
U 1 1 5BBBD0F2
P 8350 3750
F 0 "U6" H 8350 3800 60  0000 C CNN
F 1 "74HC00" H 8350 3650 60  0000 C CNN
F 2 "~" H 8350 3750 60  0000 C CNN
F 3 "~" H 8350 3750 60  0000 C CNN
	1    8350 3750
	1    0    0    -1  
$EndComp
$Comp
L 74HC00 U6
U 2 1 5BBBD125
P 8350 4600
F 0 "U6" H 8350 4650 60  0000 C CNN
F 1 "74HC00" H 8350 4500 60  0000 C CNN
F 2 "~" H 8350 4600 60  0000 C CNN
F 3 "~" H 8350 4600 60  0000 C CNN
	2    8350 4600
	1    0    0    -1  
$EndComp
$Comp
L 74HC00 U6
U 3 1 5BBBD13A
P 8350 5700
F 0 "U6" H 8350 5750 60  0000 C CNN
F 1 "74HC00" H 8350 5600 60  0000 C CNN
F 2 "~" H 8350 5700 60  0000 C CNN
F 3 "~" H 8350 5700 60  0000 C CNN
	3    8350 5700
	1    0    0    -1  
$EndComp
$Comp
L 74HC00 U6
U 4 1 5BBBD14F
P 8350 6350
F 0 "U6" H 8350 6400 60  0000 C CNN
F 1 "74HC00" H 8350 6250 60  0000 C CNN
F 2 "~" H 8350 6350 60  0000 C CNN
F 3 "~" H 8350 6350 60  0000 C CNN
	4    8350 6350
	1    0    0    -1  
$EndComp
$Comp
L R-SIL_4 R2
U 1 1 5BBBD29B
P 7500 3250
F 0 "R2" H 7500 3500 50  0000 C CNN
F 1 "10K Ohms" H 7500 3450 50  0000 C CNN
F 2 "" H 7500 3250 60  0000 C CNN
F 3 "" H 7500 3250 60  0000 C CNN
	1    7500 3250
	0    -1   -1   0   
$EndComp
$Comp
L +3.3V #PWR012
U 1 1 5BBBD347
P 7500 2800
F 0 "#PWR012" H 7500 2760 30  0001 C CNN
F 1 "+3.3V" H 7500 2910 30  0000 C CNN
F 2 "" H 7500 2800 60  0000 C CNN
F 3 "" H 7500 2800 60  0000 C CNN
	1    7500 2800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR013
U 1 1 5BBBD362
P 8150 3350
F 0 "#PWR013" H 8150 3310 30  0001 C CNN
F 1 "+3.3V" H 8150 3460 30  0000 C CNN
F 2 "" H 8150 3350 60  0000 C CNN
F 3 "" H 8150 3350 60  0000 C CNN
	1    8150 3350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 5BBBD72B
P 8150 6800
F 0 "#PWR014" H 8150 6800 30  0001 C CNN
F 1 "GND" H 8150 6730 30  0001 C CNN
F 2 "" H 8150 6800 60  0000 C CNN
F 3 "" H 8150 6800 60  0000 C CNN
	1    8150 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 6550 8150 6800
Wire Wire Line
	8150 3350 8150 3550
Wire Wire Line
	7500 2950 7500 2800
Wire Wire Line
	7650 3550 7650 3650
Wire Wire Line
	6100 3650 7750 3650
Wire Wire Line
	7550 3550 7550 4700
Wire Wire Line
	7550 4700 7750 4700
Wire Wire Line
	7750 5600 7450 5600
Wire Wire Line
	7450 5600 7450 3550
Wire Wire Line
	7350 3550 7350 6450
Wire Wire Line
	7350 6450 7750 6450
Wire Wire Line
	7750 6250 7750 6050
Wire Wire Line
	7750 6050 8950 6050
Wire Wire Line
	8950 6050 8950 5700
Wire Wire Line
	8950 6350 9000 6350
Wire Wire Line
	9000 6350 9000 6000
Wire Wire Line
	9000 6000 7750 6000
Wire Wire Line
	7750 6000 7750 5800
Wire Wire Line
	8950 4600 8950 4100
Wire Wire Line
	8950 4100 7750 4100
Wire Wire Line
	7750 4100 7750 3850
Wire Wire Line
	8950 3750 9200 3750
Wire Wire Line
	9050 3750 9050 4300
Wire Wire Line
	9050 4300 7750 4300
Wire Wire Line
	7750 4300 7750 4500
Wire Wire Line
	6100 3650 6100 4450
Wire Wire Line
	6100 4450 6300 4450
Connection ~ 7650 3650
Wire Wire Line
	6300 4650 6300 4850
Wire Wire Line
	6300 4850 7650 4850
Wire Wire Line
	7650 4850 7650 4700
Connection ~ 7650 4700
Wire Wire Line
	7450 5500 6200 5500
Wire Wire Line
	6200 5500 6200 6150
Wire Wire Line
	6200 6150 6350 6150
Connection ~ 7450 5500
Wire Wire Line
	7600 6450 7600 6600
Wire Wire Line
	7600 6600 6350 6600
Wire Wire Line
	6350 6600 6350 6350
Connection ~ 7600 6450
Text Label 950  1950 2    28   ~ 0
M0_Sense
Text Label 950  2050 2    28   ~ 0
M1_Sense
Wire Wire Line
	950  1950 1250 1950
Wire Wire Line
	950  2050 1250 2050
Text Label 9200 3750 0    28   ~ 0
M0_Sense
Connection ~ 9050 3750
Text Label 9200 5700 0    28   ~ 0
M1_Sense
Wire Wire Line
	8950 5700 9200 5700
Text Label 3400 1650 0    28   ~ 0
TX
Text Label 3400 1750 0    28   ~ 0
RX
Wire Wire Line
	3150 1650 3400 1650
Wire Wire Line
	3150 1750 3400 1750
Text Label 1150 4700 2    28   ~ 0
TX
Text Label 1150 4900 2    28   ~ 0
RX
Wire Wire Line
	1150 4700 1250 4700
Wire Wire Line
	1150 4900 1250 4900
Text Label 3400 2050 0    28   ~ 0
Occupancy
Text Label 1100 4500 2    28   ~ 0
Occupancy
Wire Wire Line
	1100 4500 1250 4500
Wire Wire Line
	3150 2050 3400 2050
Wire Wire Line
	3400 2150 3150 2150
Text Label 1150 5100 2    28   ~ 0
East (Points) Occ
Text Label 1150 5300 2    28   ~ 0
West Main (Frog Normal) Occ
Text Label 1150 5450 2    28   ~ 0
West Diverg (Frog Reversed) Occ
Wire Wire Line
	1150 5100 1250 5100
Wire Wire Line
	1150 5300 1250 5300
Wire Wire Line
	1150 5450 1250 5450
Text Label 3400 2150 0    28   ~ 0
East (Points) Occ
Text Label 3400 2350 0    28   ~ 0
West Main (Frog Normal) Occ
Wire Wire Line
	3400 2350 3150 2350
Text Label 1200 1650 2    28   ~ 0
West Diverg (Frog Reversed) Occ
Wire Wire Line
	1200 1650 1250 1650
NoConn ~ 1250 2250
NoConn ~ 1250 2350
NoConn ~ 1250 2450
NoConn ~ 1250 2650
NoConn ~ 1250 2750
NoConn ~ 1250 2850
NoConn ~ 1250 2950
NoConn ~ 1250 3050
NoConn ~ 1250 3150
NoConn ~ 3150 3250
NoConn ~ 3150 3150
NoConn ~ 3150 3050
NoConn ~ 3150 2850
NoConn ~ 3150 2650
NoConn ~ 3150 2550
NoConn ~ 3150 2450
$Comp
L C C13
U 1 1 5BBBE9AA
P 9100 3150
F 0 "C13" H 9100 3250 40  0000 L CNN
F 1 ".1 uf" H 9106 3065 40  0000 L CNN
F 2 "~" H 9138 3000 30  0000 C CNN
F 3 "~" H 9100 3150 60  0000 C CNN
	1    9100 3150
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR015
U 1 1 5BBBE9FC
P 9100 2800
F 0 "#PWR015" H 9100 2760 30  0001 C CNN
F 1 "+3.3V" H 9100 2910 30  0000 C CNN
F 2 "" H 9100 2800 60  0000 C CNN
F 3 "" H 9100 2800 60  0000 C CNN
	1    9100 2800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 5BBBEA23
P 9100 3450
F 0 "#PWR016" H 9100 3450 30  0001 C CNN
F 1 "GND" H 9100 3380 30  0001 C CNN
F 2 "" H 9100 3450 60  0000 C CNN
F 3 "" H 9100 3450 60  0000 C CNN
	1    9100 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 2800 9100 2950
Wire Wire Line
	9100 3350 9100 3450
$EndSCHEMATC