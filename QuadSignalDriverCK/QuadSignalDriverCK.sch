EESchema Schematic File Version 2
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
LIBS:QuadSignalDriverCK-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "21 oct 2017"
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
P 1650 850
F 0 "J0" H 2400 1100 60  0000 C CNN
F 1 "RPi_GPIO" H 2400 1000 60  0000 C CNN
F 2 "RPi_Hat:Pin_Header_Straight_2x20" H 1650 850 60  0001 C CNN
F 3 "" H 1650 850 60  0000 C CNN
	1    1650 850 
	1    0    0    -1  
$EndComp
$Comp
L MCP23017 U1
U 1 1 59E8A499
P 6200 2000
F 0 "U1" H 6050 2150 60  0000 C CNN
F 1 "MCP23017" H 6200 2000 60  0000 C CNN
F 2 "~" H 6200 2000 60  0000 C CNN
F 3 "~" H 6200 2000 60  0000 C CNN
	1    6200 2000
	1    0    0    -1  
$EndComp
$Comp
L MPQ2222A Q1
U 1 1 59E8A4B8
P 1800 3950
F 0 "Q1" H 1800 3802 40  0000 R CNN
F 1 "MPQ2222A" H 1800 4100 40  0000 R CNN
F 2 "TO116" H 1700 4052 29  0000 C CNN
F 3 "~" H 1800 3950 60  0000 C CNN
	1    1800 3950
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 59E8A4C7
P 1350 3950
F 0 "R1" V 1430 3950 40  0000 C CNN
F 1 "1K Ohms" V 1357 3951 40  0000 C CNN
F 2 "~" V 1280 3950 30  0000 C CNN
F 3 "~" H 1350 3950 30  0000 C CNN
	1    1350 3950
	0    -1   -1   0   
$EndComp
$Comp
L R R5
U 1 1 59E8A4D6
P 2150 3750
F 0 "R5" V 2230 3750 40  0000 C CNN
F 1 "150 Ohms" V 2157 3751 40  0000 C CNN
F 2 "~" V 2080 3750 30  0000 C CNN
F 3 "~" H 2150 3750 30  0000 C CNN
	1    2150 3750
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR01
U 1 1 59E8A4E7
P 1900 4200
F 0 "#PWR01" H 1900 4200 30  0001 C CNN
F 1 "GND" H 1900 4130 30  0001 C CNN
F 2 "" H 1900 4200 60  0000 C CNN
F 3 "" H 1900 4200 60  0000 C CNN
	1    1900 4200
	1    0    0    -1  
$EndComp
$Comp
L MPQ2222A Q1
U 2 1 59E8A508
P 1800 4600
F 0 "Q1" H 1800 4452 40  0000 R CNN
F 1 "MPQ2222A" H 1800 4750 40  0000 R CNN
F 2 "TO116" H 1700 4702 29  0000 C CNN
F 3 "~" H 1800 4600 60  0000 C CNN
	2    1800 4600
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 59E8A50E
P 1350 4600
F 0 "R2" V 1430 4600 40  0000 C CNN
F 1 "1K Ohms" V 1357 4601 40  0000 C CNN
F 2 "~" V 1280 4600 30  0000 C CNN
F 3 "~" H 1350 4600 30  0000 C CNN
	1    1350 4600
	0    -1   -1   0   
$EndComp
$Comp
L R R6
U 1 1 59E8A514
P 2150 4400
F 0 "R6" V 2230 4400 40  0000 C CNN
F 1 "150 Ohms" V 2157 4401 40  0000 C CNN
F 2 "~" V 2080 4400 30  0000 C CNN
F 3 "~" H 2150 4400 30  0000 C CNN
	1    2150 4400
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR02
U 1 1 59E8A51A
P 1900 4850
F 0 "#PWR02" H 1900 4850 30  0001 C CNN
F 1 "GND" H 1900 4780 30  0001 C CNN
F 2 "" H 1900 4850 60  0000 C CNN
F 3 "" H 1900 4850 60  0000 C CNN
	1    1900 4850
	1    0    0    -1  
$EndComp
$Comp
L MPQ2222A Q1
U 3 1 59E8A521
P 1800 5250
F 0 "Q1" H 1800 5102 40  0000 R CNN
F 1 "MPQ2222A" H 1800 5400 40  0000 R CNN
F 2 "TO116" H 1700 5352 29  0000 C CNN
F 3 "~" H 1800 5250 60  0000 C CNN
	3    1800 5250
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 59E8A527
P 1350 5250
F 0 "R3" V 1430 5250 40  0000 C CNN
F 1 "1K Ohms" V 1357 5251 40  0000 C CNN
F 2 "~" V 1280 5250 30  0000 C CNN
F 3 "~" H 1350 5250 30  0000 C CNN
	1    1350 5250
	0    -1   -1   0   
$EndComp
$Comp
L R R7
U 1 1 59E8A52D
P 2150 5050
F 0 "R7" V 2230 5050 40  0000 C CNN
F 1 "150 Ohms" V 2157 5051 40  0000 C CNN
F 2 "~" V 2080 5050 30  0000 C CNN
F 3 "~" H 2150 5050 30  0000 C CNN
	1    2150 5050
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR03
U 1 1 59E8A533
P 1900 5500
F 0 "#PWR03" H 1900 5500 30  0001 C CNN
F 1 "GND" H 1900 5430 30  0001 C CNN
F 2 "" H 1900 5500 60  0000 C CNN
F 3 "" H 1900 5500 60  0000 C CNN
	1    1900 5500
	1    0    0    -1  
$EndComp
$Comp
L MPQ2222A Q1
U 4 1 59E8A53A
P 1800 5900
F 0 "Q1" H 1800 5752 40  0000 R CNN
F 1 "MPQ2222A" H 1800 6050 40  0000 R CNN
F 2 "TO116" H 1700 6002 29  0000 C CNN
F 3 "~" H 1800 5900 60  0000 C CNN
	4    1800 5900
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 59E8A540
P 1350 5900
F 0 "R4" V 1430 5900 40  0000 C CNN
F 1 "1K Ohms" V 1357 5901 40  0000 C CNN
F 2 "~" V 1280 5900 30  0000 C CNN
F 3 "~" H 1350 5900 30  0000 C CNN
	1    1350 5900
	0    -1   -1   0   
$EndComp
$Comp
L R R8
U 1 1 59E8A546
P 2150 5700
F 0 "R8" V 2230 5700 40  0000 C CNN
F 1 "150 Ohms" V 2157 5701 40  0000 C CNN
F 2 "~" V 2080 5700 30  0000 C CNN
F 3 "~" H 2150 5700 30  0000 C CNN
	1    2150 5700
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR04
U 1 1 59E8A54C
P 1900 6150
F 0 "#PWR04" H 1900 6150 30  0001 C CNN
F 1 "GND" H 1900 6080 30  0001 C CNN
F 2 "" H 1900 6150 60  0000 C CNN
F 3 "" H 1900 6150 60  0000 C CNN
	1    1900 6150
	1    0    0    -1  
$EndComp
$Comp
L MPQ2222A Q2
U 1 1 59E8A58F
P 3450 3950
F 0 "Q2" H 3450 3802 40  0000 R CNN
F 1 "MPQ2222A" H 3450 4100 40  0000 R CNN
F 2 "TO116" H 3350 4052 29  0000 C CNN
F 3 "~" H 3450 3950 60  0000 C CNN
	1    3450 3950
	1    0    0    -1  
$EndComp
$Comp
L R R9
U 1 1 59E8A595
P 3000 3950
F 0 "R9" V 3080 3950 40  0000 C CNN
F 1 "1K Ohms" V 3007 3951 40  0000 C CNN
F 2 "~" V 2930 3950 30  0000 C CNN
F 3 "~" H 3000 3950 30  0000 C CNN
	1    3000 3950
	0    -1   -1   0   
$EndComp
$Comp
L R R13
U 1 1 59E8A59B
P 3800 3750
F 0 "R13" V 3880 3750 40  0000 C CNN
F 1 "150 Ohms" V 3807 3751 40  0000 C CNN
F 2 "~" V 3730 3750 30  0000 C CNN
F 3 "~" H 3800 3750 30  0000 C CNN
	1    3800 3750
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR05
U 1 1 59E8A5A1
P 3550 4200
F 0 "#PWR05" H 3550 4200 30  0001 C CNN
F 1 "GND" H 3550 4130 30  0001 C CNN
F 2 "" H 3550 4200 60  0000 C CNN
F 3 "" H 3550 4200 60  0000 C CNN
	1    3550 4200
	1    0    0    -1  
$EndComp
$Comp
L MPQ2222A Q2
U 2 1 59E8A5A8
P 3450 4600
F 0 "Q2" H 3450 4452 40  0000 R CNN
F 1 "MPQ2222A" H 3450 4750 40  0000 R CNN
F 2 "TO116" H 3350 4702 29  0000 C CNN
F 3 "~" H 3450 4600 60  0000 C CNN
	2    3450 4600
	1    0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 59E8A5AE
P 3000 4600
F 0 "R10" V 3080 4600 40  0000 C CNN
F 1 "1K Ohms" V 3007 4601 40  0000 C CNN
F 2 "~" V 2930 4600 30  0000 C CNN
F 3 "~" H 3000 4600 30  0000 C CNN
	1    3000 4600
	0    -1   -1   0   
$EndComp
$Comp
L R R14
U 1 1 59E8A5B4
P 3800 4400
F 0 "R14" V 3880 4400 40  0000 C CNN
F 1 "150 Ohms" V 3807 4401 40  0000 C CNN
F 2 "~" V 3730 4400 30  0000 C CNN
F 3 "~" H 3800 4400 30  0000 C CNN
	1    3800 4400
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR06
U 1 1 59E8A5BA
P 3550 4850
F 0 "#PWR06" H 3550 4850 30  0001 C CNN
F 1 "GND" H 3550 4780 30  0001 C CNN
F 2 "" H 3550 4850 60  0000 C CNN
F 3 "" H 3550 4850 60  0000 C CNN
	1    3550 4850
	1    0    0    -1  
$EndComp
$Comp
L MPQ2222A Q2
U 3 1 59E8A5C1
P 3450 5250
F 0 "Q2" H 3450 5102 40  0000 R CNN
F 1 "MPQ2222A" H 3450 5400 40  0000 R CNN
F 2 "TO116" H 3350 5352 29  0000 C CNN
F 3 "~" H 3450 5250 60  0000 C CNN
	3    3450 5250
	1    0    0    -1  
$EndComp
$Comp
L R R11
U 1 1 59E8A5C7
P 3000 5250
F 0 "R11" V 3080 5250 40  0000 C CNN
F 1 "1K Ohms" V 3007 5251 40  0000 C CNN
F 2 "~" V 2930 5250 30  0000 C CNN
F 3 "~" H 3000 5250 30  0000 C CNN
	1    3000 5250
	0    -1   -1   0   
$EndComp
$Comp
L R R15
U 1 1 59E8A5CD
P 3800 5050
F 0 "R15" V 3880 5050 40  0000 C CNN
F 1 "150 Ohms" V 3807 5051 40  0000 C CNN
F 2 "~" V 3730 5050 30  0000 C CNN
F 3 "~" H 3800 5050 30  0000 C CNN
	1    3800 5050
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR07
U 1 1 59E8A5D3
P 3550 5500
F 0 "#PWR07" H 3550 5500 30  0001 C CNN
F 1 "GND" H 3550 5430 30  0001 C CNN
F 2 "" H 3550 5500 60  0000 C CNN
F 3 "" H 3550 5500 60  0000 C CNN
	1    3550 5500
	1    0    0    -1  
$EndComp
$Comp
L MPQ2222A Q2
U 4 1 59E8A5DA
P 3450 5900
F 0 "Q2" H 3450 5752 40  0000 R CNN
F 1 "MPQ2222A" H 3450 6050 40  0000 R CNN
F 2 "TO116" H 3350 6002 29  0000 C CNN
F 3 "~" H 3450 5900 60  0000 C CNN
	4    3450 5900
	1    0    0    -1  
$EndComp
$Comp
L R R12
U 1 1 59E8A5E0
P 3000 5900
F 0 "R12" V 3080 5900 40  0000 C CNN
F 1 "1k Ohms" V 3007 5901 40  0000 C CNN
F 2 "~" V 2930 5900 30  0000 C CNN
F 3 "~" H 3000 5900 30  0000 C CNN
	1    3000 5900
	0    -1   -1   0   
$EndComp
$Comp
L R R16
U 1 1 59E8A5E6
P 3800 5700
F 0 "R16" V 3880 5700 40  0000 C CNN
F 1 "150 Ohms" V 3807 5701 40  0000 C CNN
F 2 "~" V 3730 5700 30  0000 C CNN
F 3 "~" H 3800 5700 30  0000 C CNN
	1    3800 5700
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR08
U 1 1 59E8A5EC
P 3550 6150
F 0 "#PWR08" H 3550 6150 30  0001 C CNN
F 1 "GND" H 3550 6080 30  0001 C CNN
F 2 "" H 3550 6150 60  0000 C CNN
F 3 "" H 3550 6150 60  0000 C CNN
	1    3550 6150
	1    0    0    -1  
$EndComp
$Comp
L MPQ2222A Q3
U 1 1 59E8A5F3
P 5150 4000
F 0 "Q3" H 5150 3852 40  0000 R CNN
F 1 "MPQ2222A" H 5150 4150 40  0000 R CNN
F 2 "TO116" H 5050 4102 29  0000 C CNN
F 3 "~" H 5150 4000 60  0000 C CNN
	1    5150 4000
	1    0    0    -1  
$EndComp
$Comp
L R R17
U 1 1 59E8A5F9
P 4700 4000
F 0 "R17" V 4780 4000 40  0000 C CNN
F 1 "1K Ohms" V 4707 4001 40  0000 C CNN
F 2 "~" V 4630 4000 30  0000 C CNN
F 3 "~" H 4700 4000 30  0000 C CNN
	1    4700 4000
	0    -1   -1   0   
$EndComp
$Comp
L R R21
U 1 1 59E8A5FF
P 5500 3800
F 0 "R21" V 5580 3800 40  0000 C CNN
F 1 "150 Ohms" V 5507 3801 40  0000 C CNN
F 2 "~" V 5430 3800 30  0000 C CNN
F 3 "~" H 5500 3800 30  0000 C CNN
	1    5500 3800
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR09
U 1 1 59E8A605
P 5250 4250
F 0 "#PWR09" H 5250 4250 30  0001 C CNN
F 1 "GND" H 5250 4180 30  0001 C CNN
F 2 "" H 5250 4250 60  0000 C CNN
F 3 "" H 5250 4250 60  0000 C CNN
	1    5250 4250
	1    0    0    -1  
$EndComp
$Comp
L MPQ2222A Q3
U 2 1 59E8A60C
P 5150 4650
F 0 "Q3" H 5150 4502 40  0000 R CNN
F 1 "MPQ2222A" H 5150 4800 40  0000 R CNN
F 2 "TO116" H 5050 4752 29  0000 C CNN
F 3 "~" H 5150 4650 60  0000 C CNN
	2    5150 4650
	1    0    0    -1  
$EndComp
$Comp
L R R18
U 1 1 59E8A612
P 4700 4650
F 0 "R18" V 4780 4650 40  0000 C CNN
F 1 "1K Ohms" V 4707 4651 40  0000 C CNN
F 2 "~" V 4630 4650 30  0000 C CNN
F 3 "~" H 4700 4650 30  0000 C CNN
	1    4700 4650
	0    -1   -1   0   
$EndComp
$Comp
L R R22
U 1 1 59E8A618
P 5500 4450
F 0 "R22" V 5580 4450 40  0000 C CNN
F 1 "150 Ohms" V 5507 4451 40  0000 C CNN
F 2 "~" V 5430 4450 30  0000 C CNN
F 3 "~" H 5500 4450 30  0000 C CNN
	1    5500 4450
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR010
U 1 1 59E8A61E
P 5250 4900
F 0 "#PWR010" H 5250 4900 30  0001 C CNN
F 1 "GND" H 5250 4830 30  0001 C CNN
F 2 "" H 5250 4900 60  0000 C CNN
F 3 "" H 5250 4900 60  0000 C CNN
	1    5250 4900
	1    0    0    -1  
$EndComp
$Comp
L MPQ2222A Q3
U 3 1 59E8A625
P 5150 5300
F 0 "Q3" H 5150 5152 40  0000 R CNN
F 1 "MPQ2222A" H 5150 5450 40  0000 R CNN
F 2 "TO116" H 5050 5402 29  0000 C CNN
F 3 "~" H 5150 5300 60  0000 C CNN
	3    5150 5300
	1    0    0    -1  
$EndComp
$Comp
L R R19
U 1 1 59E8A62B
P 4700 5300
F 0 "R19" V 4780 5300 40  0000 C CNN
F 1 "1K Ohms" V 4707 5301 40  0000 C CNN
F 2 "~" V 4630 5300 30  0000 C CNN
F 3 "~" H 4700 5300 30  0000 C CNN
	1    4700 5300
	0    -1   -1   0   
$EndComp
$Comp
L R R23
U 1 1 59E8A631
P 5500 5100
F 0 "R23" V 5580 5100 40  0000 C CNN
F 1 "150 Ohms" V 5507 5101 40  0000 C CNN
F 2 "~" V 5430 5100 30  0000 C CNN
F 3 "~" H 5500 5100 30  0000 C CNN
	1    5500 5100
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR011
U 1 1 59E8A637
P 5250 5550
F 0 "#PWR011" H 5250 5550 30  0001 C CNN
F 1 "GND" H 5250 5480 30  0001 C CNN
F 2 "" H 5250 5550 60  0000 C CNN
F 3 "" H 5250 5550 60  0000 C CNN
	1    5250 5550
	1    0    0    -1  
$EndComp
$Comp
L MPQ2222A Q3
U 4 1 59E8A63E
P 5150 5950
F 0 "Q3" H 5150 5802 40  0000 R CNN
F 1 "MPQ2222A" H 5150 6100 40  0000 R CNN
F 2 "TO116" H 5050 6052 29  0000 C CNN
F 3 "~" H 5150 5950 60  0000 C CNN
	4    5150 5950
	1    0    0    -1  
$EndComp
$Comp
L R R20
U 1 1 59E8A644
P 4700 5950
F 0 "R20" V 4780 5950 40  0000 C CNN
F 1 "1K Ohms" V 4707 5951 40  0000 C CNN
F 2 "~" V 4630 5950 30  0000 C CNN
F 3 "~" H 4700 5950 30  0000 C CNN
	1    4700 5950
	0    -1   -1   0   
$EndComp
$Comp
L R R24
U 1 1 59E8A64A
P 5500 5750
F 0 "R24" V 5580 5750 40  0000 C CNN
F 1 "150 Ohms" V 5507 5751 40  0000 C CNN
F 2 "~" V 5430 5750 30  0000 C CNN
F 3 "~" H 5500 5750 30  0000 C CNN
	1    5500 5750
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR012
U 1 1 59E8A650
P 5250 6200
F 0 "#PWR012" H 5250 6200 30  0001 C CNN
F 1 "GND" H 5250 6130 30  0001 C CNN
F 2 "" H 5250 6200 60  0000 C CNN
F 3 "" H 5250 6200 60  0000 C CNN
	1    5250 6200
	1    0    0    -1  
$EndComp
$Comp
L MPQ2222A Q4
U 1 1 59E8A657
P 6800 4000
F 0 "Q4" H 6800 3852 40  0000 R CNN
F 1 "MPQ2222A" H 6800 4150 40  0000 R CNN
F 2 "TO116" H 6700 4102 29  0000 C CNN
F 3 "~" H 6800 4000 60  0000 C CNN
	1    6800 4000
	1    0    0    -1  
$EndComp
$Comp
L R R25
U 1 1 59E8A65D
P 6350 4000
F 0 "R25" V 6430 4000 40  0000 C CNN
F 1 "1K Ohms" V 6357 4001 40  0000 C CNN
F 2 "~" V 6280 4000 30  0000 C CNN
F 3 "~" H 6350 4000 30  0000 C CNN
	1    6350 4000
	0    -1   -1   0   
$EndComp
$Comp
L R R29
U 1 1 59E8A663
P 7150 3800
F 0 "R29" V 7230 3800 40  0000 C CNN
F 1 "150 Ohms" V 7157 3801 40  0000 C CNN
F 2 "~" V 7080 3800 30  0000 C CNN
F 3 "~" H 7150 3800 30  0000 C CNN
	1    7150 3800
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR013
U 1 1 59E8A669
P 6900 4250
F 0 "#PWR013" H 6900 4250 30  0001 C CNN
F 1 "GND" H 6900 4180 30  0001 C CNN
F 2 "" H 6900 4250 60  0000 C CNN
F 3 "" H 6900 4250 60  0000 C CNN
	1    6900 4250
	1    0    0    -1  
$EndComp
$Comp
L MPQ2222A Q4
U 2 1 59E8A670
P 6800 4650
F 0 "Q4" H 6800 4502 40  0000 R CNN
F 1 "MPQ2222A" H 6800 4800 40  0000 R CNN
F 2 "TO116" H 6700 4752 29  0000 C CNN
F 3 "~" H 6800 4650 60  0000 C CNN
	2    6800 4650
	1    0    0    -1  
$EndComp
$Comp
L R R26
U 1 1 59E8A676
P 6350 4650
F 0 "R26" V 6430 4650 40  0000 C CNN
F 1 "1K Ohms" V 6357 4651 40  0000 C CNN
F 2 "~" V 6280 4650 30  0000 C CNN
F 3 "~" H 6350 4650 30  0000 C CNN
	1    6350 4650
	0    -1   -1   0   
$EndComp
$Comp
L R R30
U 1 1 59E8A67C
P 7150 4450
F 0 "R30" V 7230 4450 40  0000 C CNN
F 1 "150 Ohms" V 7157 4451 40  0000 C CNN
F 2 "~" V 7080 4450 30  0000 C CNN
F 3 "~" H 7150 4450 30  0000 C CNN
	1    7150 4450
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR014
U 1 1 59E8A682
P 6900 4900
F 0 "#PWR014" H 6900 4900 30  0001 C CNN
F 1 "GND" H 6900 4830 30  0001 C CNN
F 2 "" H 6900 4900 60  0000 C CNN
F 3 "" H 6900 4900 60  0000 C CNN
	1    6900 4900
	1    0    0    -1  
$EndComp
$Comp
L MPQ2222A Q4
U 3 1 59E8A689
P 6800 5300
F 0 "Q4" H 6800 5152 40  0000 R CNN
F 1 "MPQ2222A" H 6800 5450 40  0000 R CNN
F 2 "TO116" H 6700 5402 29  0000 C CNN
F 3 "~" H 6800 5300 60  0000 C CNN
	3    6800 5300
	1    0    0    -1  
$EndComp
$Comp
L R R27
U 1 1 59E8A68F
P 6350 5300
F 0 "R27" V 6430 5300 40  0000 C CNN
F 1 "1K Ohms" V 6357 5301 40  0000 C CNN
F 2 "~" V 6280 5300 30  0000 C CNN
F 3 "~" H 6350 5300 30  0000 C CNN
	1    6350 5300
	0    -1   -1   0   
$EndComp
$Comp
L R R31
U 1 1 59E8A695
P 7150 5100
F 0 "R31" V 7230 5100 40  0000 C CNN
F 1 "150 Ohms" V 7157 5101 40  0000 C CNN
F 2 "~" V 7080 5100 30  0000 C CNN
F 3 "~" H 7150 5100 30  0000 C CNN
	1    7150 5100
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR015
U 1 1 59E8A69B
P 6900 5550
F 0 "#PWR015" H 6900 5550 30  0001 C CNN
F 1 "GND" H 6900 5480 30  0001 C CNN
F 2 "" H 6900 5550 60  0000 C CNN
F 3 "" H 6900 5550 60  0000 C CNN
	1    6900 5550
	1    0    0    -1  
$EndComp
$Comp
L MPQ2222A Q4
U 4 1 59E8A6A2
P 6800 5950
F 0 "Q4" H 6800 5802 40  0000 R CNN
F 1 "MPQ2222A" H 6800 6100 40  0000 R CNN
F 2 "TO116" H 6700 6052 29  0000 C CNN
F 3 "~" H 6800 5950 60  0000 C CNN
	4    6800 5950
	1    0    0    -1  
$EndComp
$Comp
L R R28
U 1 1 59E8A6A8
P 6350 5950
F 0 "R28" V 6430 5950 40  0000 C CNN
F 1 "1K Ohms" V 6357 5951 40  0000 C CNN
F 2 "~" V 6280 5950 30  0000 C CNN
F 3 "~" H 6350 5950 30  0000 C CNN
	1    6350 5950
	0    -1   -1   0   
$EndComp
$Comp
L R R32
U 1 1 59E8A6AE
P 7150 5750
F 0 "R32" V 7230 5750 40  0000 C CNN
F 1 "150 Ohms" V 7157 5751 40  0000 C CNN
F 2 "~" V 7080 5750 30  0000 C CNN
F 3 "~" H 7150 5750 30  0000 C CNN
	1    7150 5750
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR016
U 1 1 59E8A6B4
P 6900 6200
F 0 "#PWR016" H 6900 6200 30  0001 C CNN
F 1 "GND" H 6900 6130 30  0001 C CNN
F 2 "" H 6900 6200 60  0000 C CNN
F 3 "" H 6900 6200 60  0000 C CNN
	1    6900 6200
	1    0    0    -1  
$EndComp
$Comp
L CONN_3X2 J1
U 1 1 59E8A7B3
P 4100 1600
F 0 "J1" H 4150 1750 50  0000 C CNN
F 1 "Address Jumper" V 4100 1650 40  0000 C CNN
F 2 "~" H 4100 1600 60  0000 C CNN
F 3 "~" H 4100 1600 60  0000 C CNN
	1    4100 1600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 59E8A82B
P 3700 1750
F 0 "#PWR017" H 3700 1750 30  0001 C CNN
F 1 "GND" H 3700 1680 30  0001 C CNN
F 2 "" H 3700 1750 60  0000 C CNN
F 3 "" H 3700 1750 60  0000 C CNN
	1    3700 1750
	1    0    0    -1  
$EndComp
$Comp
L RR4 RR1
U 1 1 59E8A9EF
P 4300 1050
F 0 "RR1" H 4350 1350 70  0000 C CNN
F 1 "10K Ohms" V 4300 1100 70  0000 C CNN
F 2 "~" H 4300 800 60  0000 C CNN
F 3 "~" H 4300 800 60  0000 C CNN
	1    4300 1050
	-1   0    0    -1  
$EndComp
$Comp
L VDD #PWR018
U 1 1 59E8AA92
P 6200 700
F 0 "#PWR018" H 6200 800 30  0001 C CNN
F 1 "VDD" H 6200 810 30  0000 C CNN
F 2 "" H 6200 700 60  0000 C CNN
F 3 "" H 6200 700 60  0000 C CNN
	1    6200 700 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 59E8AAC7
P 6100 3350
F 0 "#PWR019" H 6100 3350 30  0001 C CNN
F 1 "GND" H 6100 3280 30  0001 C CNN
F 2 "" H 6100 3350 60  0000 C CNN
F 3 "" H 6100 3350 60  0000 C CNN
	1    6100 3350
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR020
U 1 1 59E8AAFD
P 1300 700
F 0 "#PWR020" H 1300 800 30  0001 C CNN
F 1 "VDD" H 1300 810 30  0000 C CNN
F 2 "" H 1300 700 60  0000 C CNN
F 3 "" H 1300 700 60  0000 C CNN
	1    1300 700 
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR021
U 1 1 59E8AB0C
P 1300 1600
F 0 "#PWR021" H 1300 1700 30  0001 C CNN
F 1 "VDD" H 1300 1710 30  0000 C CNN
F 2 "" H 1300 1600 60  0000 C CNN
F 3 "" H 1300 1600 60  0000 C CNN
	1    1300 1600
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR022
U 1 1 59E8AB6D
P 3350 700
F 0 "#PWR022" H 3350 790 20  0001 C CNN
F 1 "+5V" H 3350 790 30  0000 C CNN
F 2 "" H 3350 700 60  0000 C CNN
F 3 "" H 3350 700 60  0000 C CNN
	1    3350 700 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 59E8ABD5
P 1300 1300
F 0 "#PWR023" H 1300 1300 30  0001 C CNN
F 1 "GND" H 1300 1230 30  0001 C CNN
F 2 "" H 1300 1300 60  0000 C CNN
F 3 "" H 1300 1300 60  0000 C CNN
	1    1300 1300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR024
U 1 1 59E8ABEE
P 1300 2100
F 0 "#PWR024" H 1300 2100 30  0001 C CNN
F 1 "GND" H 1300 2030 30  0001 C CNN
F 2 "" H 1300 2100 60  0000 C CNN
F 3 "" H 1300 2100 60  0000 C CNN
	1    1300 2100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR025
U 1 1 59E8ABFD
P 3450 1100
F 0 "#PWR025" H 3450 1100 30  0001 C CNN
F 1 "GND" H 3450 1030 30  0001 C CNN
F 2 "" H 3450 1100 60  0000 C CNN
F 3 "" H 3450 1100 60  0000 C CNN
	1    3450 1100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR026
U 1 1 59E8AC0C
P 3450 1500
F 0 "#PWR026" H 3450 1500 30  0001 C CNN
F 1 "GND" H 3450 1430 30  0001 C CNN
F 2 "" H 3450 1500 60  0000 C CNN
F 3 "" H 3450 1500 60  0000 C CNN
	1    3450 1500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR027
U 1 1 59E8AC1B
P 3450 1800
F 0 "#PWR027" H 3450 1800 30  0001 C CNN
F 1 "GND" H 3450 1730 30  0001 C CNN
F 2 "" H 3450 1800 60  0000 C CNN
F 3 "" H 3450 1800 60  0000 C CNN
	1    3450 1800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR028
U 1 1 59E8AC2A
P 3450 2300
F 0 "#PWR028" H 3450 2300 30  0001 C CNN
F 1 "GND" H 3450 2230 30  0001 C CNN
F 2 "" H 3450 2300 60  0000 C CNN
F 3 "" H 3450 2300 60  0000 C CNN
	1    3450 2300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR029
U 1 1 59E8AC39
P 3450 2500
F 0 "#PWR029" H 3450 2500 30  0001 C CNN
F 1 "GND" H 3450 2430 30  0001 C CNN
F 2 "" H 3450 2500 60  0000 C CNN
F 3 "" H 3450 2500 60  0000 C CNN
	1    3450 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR030
U 1 1 59E8AC48
P 1300 2800
F 0 "#PWR030" H 1300 2800 30  0001 C CNN
F 1 "GND" H 1300 2730 30  0001 C CNN
F 2 "" H 1300 2800 60  0000 C CNN
F 3 "" H 1300 2800 60  0000 C CNN
	1    1300 2800
	1    0    0    -1  
$EndComp
Text GLabel 1450 950  0    47   Input ~ 0
SDA
Text GLabel 1450 1050 0    47   Input ~ 0
SCL
Text GLabel 5500 1200 0    47   Input ~ 0
SCL
Text GLabel 5500 1300 0    47   Input ~ 0
SDA
Text GLabel 6850 1150 2    47   Input ~ 0
GP0.7
Text GLabel 6850 1250 2    47   Input ~ 0
GP0.6
Text GLabel 6850 1350 2    47   Input ~ 0
GP0.5
Text GLabel 6850 1450 2    47   Input ~ 0
GP0.4
Text GLabel 6850 1550 2    47   Input ~ 0
GP0.3
Text GLabel 6850 1650 2    47   Input ~ 0
GP0.2
Text GLabel 6850 1750 2    47   Input ~ 0
GP0.1
Text GLabel 6850 1850 2    47   Input ~ 0
GP0.0
Text GLabel 6850 2200 2    47   Input ~ 0
GP1.7
Text GLabel 6850 2300 2    47   Input ~ 0
GP1.6
Text GLabel 6850 2400 2    47   Input ~ 0
GP1.5
Text GLabel 6850 2500 2    47   Input ~ 0
GP1.4
Text GLabel 6850 2600 2    47   Input ~ 0
GP1.3
Text GLabel 6850 2700 2    47   Input ~ 0
GP1.2
Text GLabel 6850 2800 2    47   Input ~ 0
GP1.1
Text GLabel 6850 2900 2    47   Input ~ 0
GP1.0
Text GLabel 1900 3600 0    47   Input ~ 0
H2-L
Text GLabel 1900 4300 0    47   Input ~ 0
H1-G
Text GLabel 1900 4950 0    47   Input ~ 0
H2-R
Text GLabel 1900 5600 0    47   Input ~ 0
H1-Y
Text GLabel 3550 3650 0    47   Input ~ 0
H2-Y
Text GLabel 3550 4300 0    47   Input ~ 0
H1-R
Text GLabel 3550 4950 0    47   Input ~ 0
H2-G
Text GLabel 3550 5600 0    47   Input ~ 0
H1-L
Text GLabel 5250 3700 0    47   Input ~ 0
H4-L
Text GLabel 6900 3700 0    47   Input ~ 0
H4-Y
Text GLabel 6900 5650 0    47   Input ~ 0
H3-L
Text GLabel 5250 5650 0    47   Input ~ 0
H3-Y
Text GLabel 5250 5000 0    47   Input ~ 0
H4-R
Text GLabel 5250 4350 0    47   Input ~ 0
H3-G
Text GLabel 6900 5000 0    47   Input ~ 0
H4-G
Text GLabel 6900 4350 0    47   Input ~ 0
H3-R
Text GLabel 1100 3950 0    47   Input ~ 0
GP0.4
Text GLabel 1100 5250 0    47   Input ~ 0
GP0.5
Text GLabel 2750 3950 0    47   Input ~ 0
GP0.6
Text GLabel 2750 5250 0    47   Input ~ 0
GP0.7
Text GLabel 2750 5900 0    47   Input ~ 0
GP0.0
Text GLabel 2750 4600 0    47   Input ~ 0
GP0.1
Text GLabel 1100 4600 0    47   Input ~ 0
GP0.3
Text GLabel 1100 5900 0    47   Input ~ 0
GP0.2
Text GLabel 4450 4000 0    47   Input ~ 0
GP1.4
Text GLabel 4450 4650 0    47   Input ~ 0
GP1.3
Text GLabel 4450 5300 0    47   Input ~ 0
GP1.5
Text GLabel 4450 5950 0    47   Input ~ 0
GP1.2
Text GLabel 6100 4000 0    47   Input ~ 0
GP1.6
Text GLabel 6100 4650 0    47   Input ~ 0
GP1.1
Text GLabel 6100 5300 0    47   Input ~ 0
GP1.7
Text GLabel 6100 5950 0    47   Input ~ 0
GP1.0
$Comp
L CONN_5 T1
U 1 1 59E8B093
P 10650 1350
F 0 "T1" V 10600 1350 50  0000 C CNN
F 1 "H1" V 10700 1350 50  0000 C CNN
F 2 "~" H 10650 1350 60  0000 C CNN
F 3 "~" H 10650 1350 60  0000 C CNN
	1    10650 1350
	1    0    0    -1  
$EndComp
$Comp
L CONN_5 T2
U 1 1 59E8B0A2
P 10650 2600
F 0 "T2" V 10600 2600 50  0000 C CNN
F 1 "H2" V 10700 2600 50  0000 C CNN
F 2 "~" H 10650 2600 60  0000 C CNN
F 3 "~" H 10650 2600 60  0000 C CNN
	1    10650 2600
	1    0    0    -1  
$EndComp
$Comp
L CONN_5 T3
U 1 1 59E8B0B1
P 10650 3700
F 0 "T3" V 10600 3700 50  0000 C CNN
F 1 "H3" V 10700 3700 50  0000 C CNN
F 2 "~" H 10650 3700 60  0000 C CNN
F 3 "~" H 10650 3700 60  0000 C CNN
	1    10650 3700
	1    0    0    -1  
$EndComp
$Comp
L CONN_5 T4
U 1 1 59E8B0C0
P 10650 4800
F 0 "T4" V 10600 4800 50  0000 C CNN
F 1 "H4" V 10700 4800 50  0000 C CNN
F 2 "~" H 10650 4800 60  0000 C CNN
F 3 "~" H 10650 4800 60  0000 C CNN
	1    10650 4800
	1    0    0    -1  
$EndComp
Text GLabel 10250 1150 0    47   Input ~ 0
Common
Text GLabel 10250 1250 0    47   Input ~ 0
H2-L
Text GLabel 10250 1350 0    47   Input ~ 0
H1-G
Text GLabel 10250 1450 0    47   Input ~ 0
H2-R
Text GLabel 10250 1550 0    47   Input ~ 0
H1-Y
Text GLabel 10250 2400 0    47   Input ~ 0
H2-Y
Text GLabel 10250 2500 0    47   Input ~ 0
H1-R
Text GLabel 10250 2600 0    47   Input ~ 0
H2-G
Text GLabel 10250 2700 0    47   Input ~ 0
H1-L
Text GLabel 10250 2800 0    47   Input ~ 0
Common
Text GLabel 10250 3500 0    47   Input ~ 0
Common
Text GLabel 10250 5000 0    47   Input ~ 0
Common
Text GLabel 10250 3600 0    47   Input ~ 0
H4-L
Text GLabel 10250 3700 0    47   Input ~ 0
H3-G
Text GLabel 10250 3800 0    47   Input ~ 0
H4-R
Text GLabel 10250 3900 0    47   Input ~ 0
H3-Y
Text GLabel 10250 4600 0    47   Input ~ 0
H4-Y
Text GLabel 10250 4700 0    47   Input ~ 0
H3-R
Text GLabel 10250 4800 0    47   Input ~ 0
H4-G
Text GLabel 10250 4900 0    47   Input ~ 0
H3-L
$Comp
L C C1
U 1 1 59E8B377
P 4200 2750
F 0 "C1" H 4200 2850 40  0000 L CNN
F 1 ".1 uf" H 4206 2665 40  0000 L CNN
F 2 "~" H 4238 2600 30  0000 C CNN
F 3 "~" H 4200 2750 60  0000 C CNN
	1    4200 2750
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR031
U 1 1 59E8B392
P 4200 2450
F 0 "#PWR031" H 4200 2550 30  0001 C CNN
F 1 "VDD" H 4200 2560 30  0000 C CNN
F 2 "" H 4200 2450 60  0000 C CNN
F 3 "" H 4200 2450 60  0000 C CNN
	1    4200 2450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR032
U 1 1 59E8B426
P 4200 3100
F 0 "#PWR032" H 4200 3100 30  0001 C CNN
F 1 "GND" H 4200 3030 30  0001 C CNN
F 2 "" H 4200 3100 60  0000 C CNN
F 3 "" H 4200 3100 60  0000 C CNN
	1    4200 3100
	1    0    0    -1  
$EndComp
$Comp
L CP1 C2
U 1 1 59EB5FAA
P 4650 2750
F 0 "C2" H 4700 2850 50  0000 L CNN
F 1 "10 uf, 50V" H 4700 2650 50  0000 L CNN
F 2 "~" H 4650 2750 60  0000 C CNN
F 3 "~" H 4650 2750 60  0000 C CNN
	1    4650 2750
	1    0    0    -1  
$EndComp
$Comp
L CP1 C3
U 1 1 59EB5FB9
P 8550 2900
F 0 "C3" H 8600 3000 50  0000 L CNN
F 1 "15 uf, 50V" H 8600 2800 50  0000 L CNN
F 2 "~" H 8550 2900 60  0000 C CNN
F 3 "~" H 8550 2900 60  0000 C CNN
	1    8550 2900
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR033
U 1 1 59EB60F2
P 8550 2650
F 0 "#PWR033" H 8550 2740 20  0001 C CNN
F 1 "+5V" H 8550 2740 30  0000 C CNN
F 2 "" H 8550 2650 60  0000 C CNN
F 3 "" H 8550 2650 60  0000 C CNN
	1    8550 2650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR034
U 1 1 59EB6101
P 8550 3150
F 0 "#PWR034" H 8550 3150 30  0001 C CNN
F 1 "GND" H 8550 3080 30  0001 C CNN
F 2 "" H 8550 3150 60  0000 C CNN
F 3 "" H 8550 3150 60  0000 C CNN
	1    8550 3150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR035
U 1 1 59EB7505
P 10250 1050
F 0 "#PWR035" H 10250 1050 30  0001 C CNN
F 1 "GND" H 10250 980 30  0001 C CNN
F 2 "" H 10250 1050 60  0000 C CNN
F 3 "" H 10250 1050 60  0000 C CNN
	1    10250 1050
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR036
U 1 1 59EB7514
P 10250 2900
F 0 "#PWR036" H 10250 2900 30  0001 C CNN
F 1 "GND" H 10250 2830 30  0001 C CNN
F 2 "" H 10250 2900 60  0000 C CNN
F 3 "" H 10250 2900 60  0000 C CNN
	1    10250 2900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR037
U 1 1 59EB7523
P 10250 3400
F 0 "#PWR037" H 10250 3400 30  0001 C CNN
F 1 "GND" H 10250 3330 30  0001 C CNN
F 2 "" H 10250 3400 60  0000 C CNN
F 3 "" H 10250 3400 60  0000 C CNN
	1    10250 3400
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR038
U 1 1 59EB7532
P 10250 5100
F 0 "#PWR038" H 10250 5100 30  0001 C CNN
F 1 "GND" H 10250 5030 30  0001 C CNN
F 2 "" H 10250 5100 60  0000 C CNN
F 3 "" H 10250 5100 60  0000 C CNN
	1    10250 5100
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR039
U 1 1 59EB754E
P 2400 3650
F 0 "#PWR039" H 2400 3740 20  0001 C CNN
F 1 "+5V" H 2400 3740 30  0000 C CNN
F 2 "" H 2400 3650 60  0000 C CNN
F 3 "" H 2400 3650 60  0000 C CNN
	1    2400 3650
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR040
U 1 1 59EB755D
P 2400 4300
F 0 "#PWR040" H 2400 4390 20  0001 C CNN
F 1 "+5V" H 2400 4390 30  0000 C CNN
F 2 "" H 2400 4300 60  0000 C CNN
F 3 "" H 2400 4300 60  0000 C CNN
	1    2400 4300
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR041
U 1 1 59EB756C
P 2400 4950
F 0 "#PWR041" H 2400 5040 20  0001 C CNN
F 1 "+5V" H 2400 5040 30  0000 C CNN
F 2 "" H 2400 4950 60  0000 C CNN
F 3 "" H 2400 4950 60  0000 C CNN
	1    2400 4950
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR042
U 1 1 59EB757B
P 2400 5600
F 0 "#PWR042" H 2400 5690 20  0001 C CNN
F 1 "+5V" H 2400 5690 30  0000 C CNN
F 2 "" H 2400 5600 60  0000 C CNN
F 3 "" H 2400 5600 60  0000 C CNN
	1    2400 5600
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR043
U 1 1 59EB77FE
P 7400 3700
F 0 "#PWR043" H 7400 3790 20  0001 C CNN
F 1 "+5V" H 7400 3790 30  0000 C CNN
F 2 "" H 7400 3700 60  0000 C CNN
F 3 "" H 7400 3700 60  0000 C CNN
	1    7400 3700
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR044
U 1 1 59EB780D
P 7400 4350
F 0 "#PWR044" H 7400 4440 20  0001 C CNN
F 1 "+5V" H 7400 4440 30  0000 C CNN
F 2 "" H 7400 4350 60  0000 C CNN
F 3 "" H 7400 4350 60  0000 C CNN
	1    7400 4350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR045
U 1 1 59EB781C
P 7400 5000
F 0 "#PWR045" H 7400 5090 20  0001 C CNN
F 1 "+5V" H 7400 5090 30  0000 C CNN
F 2 "" H 7400 5000 60  0000 C CNN
F 3 "" H 7400 5000 60  0000 C CNN
	1    7400 5000
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR046
U 1 1 59EB7849
P 5750 4950
F 0 "#PWR046" H 5750 5040 20  0001 C CNN
F 1 "+5V" H 5750 5040 30  0000 C CNN
F 2 "" H 5750 4950 60  0000 C CNN
F 3 "" H 5750 4950 60  0000 C CNN
	1    5750 4950
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR047
U 1 1 59EB7858
P 7400 5650
F 0 "#PWR047" H 7400 5740 20  0001 C CNN
F 1 "+5V" H 7400 5740 30  0000 C CNN
F 2 "" H 7400 5650 60  0000 C CNN
F 3 "" H 7400 5650 60  0000 C CNN
	1    7400 5650
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR048
U 1 1 59EB7867
P 5750 5650
F 0 "#PWR048" H 5750 5740 20  0001 C CNN
F 1 "+5V" H 5750 5740 30  0000 C CNN
F 2 "" H 5750 5650 60  0000 C CNN
F 3 "" H 5750 5650 60  0000 C CNN
	1    5750 5650
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR049
U 1 1 59EB7876
P 5750 4350
F 0 "#PWR049" H 5750 4440 20  0001 C CNN
F 1 "+5V" H 5750 4440 30  0000 C CNN
F 2 "" H 5750 4350 60  0000 C CNN
F 3 "" H 5750 4350 60  0000 C CNN
	1    5750 4350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR050
U 1 1 59EB7885
P 5750 3700
F 0 "#PWR050" H 5750 3790 20  0001 C CNN
F 1 "+5V" H 5750 3790 30  0000 C CNN
F 2 "" H 5750 3700 60  0000 C CNN
F 3 "" H 5750 3700 60  0000 C CNN
	1    5750 3700
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR051
U 1 1 59EB78A3
P 4050 3650
F 0 "#PWR051" H 4050 3740 20  0001 C CNN
F 1 "+5V" H 4050 3740 30  0000 C CNN
F 2 "" H 4050 3650 60  0000 C CNN
F 3 "" H 4050 3650 60  0000 C CNN
	1    4050 3650
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR052
U 1 1 59EB78B2
P 4050 4300
F 0 "#PWR052" H 4050 4390 20  0001 C CNN
F 1 "+5V" H 4050 4390 30  0000 C CNN
F 2 "" H 4050 4300 60  0000 C CNN
F 3 "" H 4050 4300 60  0000 C CNN
	1    4050 4300
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR053
U 1 1 59EB78C1
P 4050 4950
F 0 "#PWR053" H 4050 5040 20  0001 C CNN
F 1 "+5V" H 4050 5040 30  0000 C CNN
F 2 "" H 4050 4950 60  0000 C CNN
F 3 "" H 4050 4950 60  0000 C CNN
	1    4050 4950
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR054
U 1 1 59EB78D0
P 4050 5600
F 0 "#PWR054" H 4050 5690 20  0001 C CNN
F 1 "+5V" H 4050 5690 30  0000 C CNN
F 2 "" H 4050 5600 60  0000 C CNN
F 3 "" H 4050 5600 60  0000 C CNN
	1    4050 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 4150 1900 4200
Wire Wire Line
	1900 4800 1900 4850
Wire Wire Line
	1900 5450 1900 5500
Wire Wire Line
	1900 6100 1900 6150
Wire Wire Line
	3550 4150 3550 4200
Wire Wire Line
	3550 4800 3550 4850
Wire Wire Line
	3550 5450 3550 5500
Wire Wire Line
	3550 6100 3550 6150
Wire Wire Line
	5250 4200 5250 4250
Wire Wire Line
	5250 4850 5250 4900
Wire Wire Line
	5250 5500 5250 5550
Wire Wire Line
	5250 6150 5250 6200
Wire Wire Line
	6900 4200 6900 4250
Wire Wire Line
	6900 4850 6900 4900
Wire Wire Line
	6900 5500 6900 5550
Wire Wire Line
	6900 6150 6900 6200
Wire Wire Line
	4500 1450 5500 1450
Wire Wire Line
	4500 1550 5500 1550
Wire Wire Line
	4500 1650 5500 1650
Wire Wire Line
	3700 1450 3700 1750
Connection ~ 3700 1550
Connection ~ 3700 1650
Wire Wire Line
	4650 850  6100 850 
Wire Wire Line
	6100 850  6100 800 
Wire Wire Line
	6100 800  6200 800 
Wire Wire Line
	4650 950  5100 950 
Wire Wire Line
	5100 950  5100 2450
Wire Wire Line
	5100 2450 5500 2450
Wire Wire Line
	4650 1050 5000 1050
Wire Wire Line
	5000 1050 5000 1450
Connection ~ 5000 1450
Wire Wire Line
	4650 1150 4900 1150
Wire Wire Line
	4900 1150 4900 1550
Connection ~ 4900 1550
Wire Wire Line
	4650 1250 4800 1250
Wire Wire Line
	4800 1250 4800 1650
Connection ~ 4800 1650
Wire Wire Line
	6200 800  6200 700 
Wire Wire Line
	6100 3350 6100 3250
Wire Wire Line
	1300 1600 1300 1650
Wire Wire Line
	1300 1650 1450 1650
Wire Wire Line
	1300 700  1300 850 
Wire Wire Line
	1300 850  1450 850 
Wire Wire Line
	3350 700  3350 950 
Connection ~ 3350 850 
Wire Wire Line
	3450 2500 3450 2450
Wire Wire Line
	3450 2450 3350 2450
Wire Wire Line
	3450 2300 3450 2250
Wire Wire Line
	3450 2250 3350 2250
Wire Wire Line
	1300 2800 1300 2750
Wire Wire Line
	1300 2750 1450 2750
Wire Wire Line
	1300 2100 1300 2050
Wire Wire Line
	1300 2050 1450 2050
Wire Wire Line
	1300 1300 1300 1250
Wire Wire Line
	1300 1250 1450 1250
Wire Wire Line
	3450 1800 3450 1750
Wire Wire Line
	3450 1750 3350 1750
Wire Wire Line
	3450 1500 3450 1450
Wire Wire Line
	3450 1450 3350 1450
Wire Wire Line
	3450 1100 3450 1050
Wire Wire Line
	3450 1050 3350 1050
Wire Wire Line
	10250 1050 10250 1150
Wire Wire Line
	10250 2800 10250 2900
Wire Wire Line
	10250 5100 10250 5000
Wire Wire Line
	10250 3400 10250 3500
Wire Wire Line
	4200 2550 4200 2450
Wire Wire Line
	4200 2950 4200 3100
Wire Wire Line
	4650 2550 4200 2550
Wire Wire Line
	4650 2950 4200 2950
Wire Wire Line
	8550 2650 8550 2700
Wire Wire Line
	8550 3100 8550 3150
Wire Wire Line
	2400 5600 2400 5700
Wire Wire Line
	1900 5600 1900 5700
Wire Wire Line
	2400 4950 2400 5050
Wire Wire Line
	1900 4950 1900 5050
Wire Wire Line
	2400 4300 2400 4400
Wire Wire Line
	1900 4300 1900 4400
Wire Wire Line
	2400 3650 2400 3750
Wire Wire Line
	1900 3600 1900 3750
Wire Wire Line
	3550 3650 3550 3750
Wire Wire Line
	4050 3650 4050 3750
Wire Wire Line
	5250 3700 5250 3800
Wire Wire Line
	5250 4350 5250 4450
Wire Wire Line
	4050 4300 4050 4400
Wire Wire Line
	3550 4300 3550 4400
Wire Wire Line
	4050 4950 4050 5050
Wire Wire Line
	3550 4950 3550 5050
Wire Wire Line
	3550 5600 3550 5700
Wire Wire Line
	4050 5600 4050 5700
Wire Wire Line
	5250 5650 5250 5750
Wire Wire Line
	5250 5000 5250 5100
Wire Wire Line
	5750 3700 5750 3800
Wire Wire Line
	6900 3700 6900 3800
Wire Wire Line
	7400 3700 7400 3800
Wire Wire Line
	7400 4350 7400 4450
Wire Wire Line
	6900 4350 6900 4450
Wire Wire Line
	5750 4350 5750 4450
Wire Wire Line
	5750 4950 5750 5100
Wire Wire Line
	6900 5000 6900 5100
Wire Wire Line
	7400 5000 7400 5100
Wire Wire Line
	7400 5650 7400 5750
Wire Wire Line
	6900 5650 6900 5750
Wire Wire Line
	5750 5650 5750 5750
$EndSCHEMATC