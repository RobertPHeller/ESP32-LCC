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
Sheet 5 5
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
L Screw_Terminal_01x02 J601
U 1 1 63D93419
P 1475 2325
F 0 "J601" H 1475 2425 50  0000 C CNN
F 1 "- 12-15 +" H 1475 2125 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_PT-3.5mm_2pol" H 1475 2325 50  0001 C CNN
F 3 "" H 1475 2325 50  0001 C CNN
	1    1475 2325
	-1   0    0    -1  
$EndComp
$Comp
L CP1 C601
U 1 1 63D9341A
P 1925 2400
F 0 "C601" H 1950 2500 50  0000 L CNN
F 1 "4700uf 25V" H 1950 2300 50  0000 L CNN
F 2 "BigSMDCaps:EEEFK0J133SM" H 1925 2400 50  0001 C CNN
F 3 "" H 1925 2400 50  0001 C CNN
F 4 "667-EEE-FK1E472SM " H 1925 2400 60  0001 C CNN "Mouser Part Number"
	1    1925 2400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 63D9341B
P 1925 2725
F 0 "#PWR013" H 1925 2475 50  0001 C CNN
F 1 "GND" H 1925 2575 50  0000 C CNN
F 2 "" H 1925 2725 50  0001 C CNN
F 3 "" H 1925 2725 50  0001 C CNN
	1    1925 2725
	1    0    0    -1  
$EndComp
$Comp
L TC4427 U601
U 2 1 63D9341C
P 3025 1800
F 0 "U601" H 3025 1500 60  0000 C CNN
F 1 "TC4427" H 3025 2100 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 3025 1800 60  0001 C CNN
F 3 "" H 3025 1800 60  0000 C CNN
F 4 "579-TC1427COA" H 3025 1800 60  0001 C CNN "Mouser Part Number"
	2    3025 1800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 63D9341D
P 2975 2150
F 0 "#PWR014" H 2975 1900 50  0001 C CNN
F 1 "GND" H 2975 2000 50  0000 C CNN
F 2 "" H 2975 2150 50  0001 C CNN
F 3 "" H 2975 2150 50  0001 C CNN
	1    2975 2150
	1    0    0    -1  
$EndComp
$Comp
L CP1 C602
U 1 1 63D9341F
P 3800 2200
F 0 "C602" H 3825 2300 50  0000 L CNN
F 1 "2200uF 25V" H 3825 2100 50  0000 L CNN
F 2 "BigSMDCaps:EEEFK0J682AV" H 3800 2200 50  0001 C CNN
F 3 "" H 3800 2200 50  0001 C CNN
F 4 "667-EEV-FK1E222V" H 3800 2200 60  0001 C CNN "Mouser Part Number"
	1    3800 2200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 63D93420
P 3800 2550
F 0 "#PWR015" H 3800 2300 50  0001 C CNN
F 1 "GND" H 3800 2400 50  0000 C CNN
F 2 "" H 3800 2550 50  0001 C CNN
F 3 "" H 3800 2550 50  0001 C CNN
	1    3800 2550
	1    0    0    -1  
$EndComp
$Comp
L TC4427 U601
U 1 1 63D93421
P 3075 3550
F 0 "U601" H 3075 3250 60  0000 C CNN
F 1 "TC4427" H 3075 3850 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 3075 3550 60  0001 C CNN
F 3 "" H 3075 3550 60  0000 C CNN
F 4 "579-TC1427COA" H 3075 3550 60  0001 C CNN "Mouser Part Number"
	1    3075 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 63D93422
P 3025 3900
F 0 "#PWR016" H 3025 3650 50  0001 C CNN
F 1 "GND" H 3025 3750 50  0000 C CNN
F 2 "" H 3025 3900 50  0001 C CNN
F 3 "" H 3025 3900 50  0001 C CNN
	1    3025 3900
	1    0    0    -1  
$EndComp
$Comp
L CP1 C603
U 1 1 63D93424
P 3950 3925
F 0 "C603" H 3975 4025 50  0000 L CNN
F 1 "2200uF 25V" H 3975 3825 50  0000 L CNN
F 2 "BigSMDCaps:EEEFK0J682AV" H 3950 3925 50  0001 C CNN
F 3 "" H 3950 3925 50  0001 C CNN
F 4 "667-EEV-FK1E222V " H 3950 3925 60  0001 C CNN "Mouser Part Number"
	1    3950 3925
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 63D93425
P 3950 4275
F 0 "#PWR017" H 3950 4025 50  0001 C CNN
F 1 "GND" H 3950 4125 50  0000 C CNN
F 2 "" H 3950 4275 50  0001 C CNN
F 3 "" H 3950 4275 50  0001 C CNN
	1    3950 4275
	1    0    0    -1  
$EndComp
$Comp
L TC4427 U603
U 2 1 63D93426
P 5450 1775
F 0 "U603" H 5450 1475 60  0000 C CNN
F 1 "TC4427" H 5450 2075 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 5450 1775 60  0001 C CNN
F 3 "" H 5450 1775 60  0000 C CNN
F 4 "579-TC1427COA" H 5450 1775 60  0001 C CNN "Mouser Part Number"
	2    5450 1775
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR018
U 1 1 63D93427
P 5400 2125
F 0 "#PWR018" H 5400 1875 50  0001 C CNN
F 1 "GND" H 5400 1975 50  0000 C CNN
F 2 "" H 5400 2125 50  0001 C CNN
F 3 "" H 5400 2125 50  0001 C CNN
	1    5400 2125
	1    0    0    -1  
$EndComp
$Comp
L CP1 C606
U 1 1 63D93429
P 6250 2175
F 0 "C606" H 6275 2275 50  0000 L CNN
F 1 "2200uF 25V" H 6275 2075 50  0000 L CNN
F 2 "BigSMDCaps:EEEFK0J682AV" H 6250 2175 50  0001 C CNN
F 3 "" H 6250 2175 50  0001 C CNN
F 4 "667-EEV-FK1E222V " H 6250 2175 60  0001 C CNN "Mouser Part Number"
	1    6250 2175
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 63D9342A
P 6250 2500
F 0 "#PWR019" H 6250 2250 50  0001 C CNN
F 1 "GND" H 6250 2350 50  0000 C CNN
F 2 "" H 6250 2500 50  0001 C CNN
F 3 "" H 6250 2500 50  0001 C CNN
	1    6250 2500
	1    0    0    -1  
$EndComp
$Comp
L TC4427 U602
U 2 1 63D9342B
P 3100 5075
F 0 "U602" H 3100 4775 60  0000 C CNN
F 1 "TC4427" H 3100 5375 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 3100 5075 60  0001 C CNN
F 3 "" H 3100 5075 60  0000 C CNN
F 4 "579-TC1427COA" H 3100 5075 60  0001 C CNN "Mouser Part Number"
	2    3100 5075
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 63D9342C
P 3050 5425
F 0 "#PWR020" H 3050 5175 50  0001 C CNN
F 1 "GND" H 3050 5275 50  0000 C CNN
F 2 "" H 3050 5425 50  0001 C CNN
F 3 "" H 3050 5425 50  0001 C CNN
	1    3050 5425
	1    0    0    -1  
$EndComp
$Comp
L CP1 C604
U 1 1 63D9342E
P 3950 5400
F 0 "C604" H 3975 5500 50  0000 L CNN
F 1 "2200uF 25V" H 3975 5300 50  0000 L CNN
F 2 "BigSMDCaps:EEEFK0J682AV" H 3950 5400 50  0001 C CNN
F 3 "" H 3950 5400 50  0001 C CNN
F 4 "667-EEV-FK1E222V " H 3950 5400 60  0001 C CNN "Mouser Part Number"
	1    3950 5400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR021
U 1 1 63D9342F
P 3950 5800
F 0 "#PWR021" H 3950 5550 50  0001 C CNN
F 1 "GND" H 3950 5650 50  0000 C CNN
F 2 "" H 3950 5800 50  0001 C CNN
F 3 "" H 3950 5800 50  0001 C CNN
	1    3950 5800
	1    0    0    -1  
$EndComp
$Comp
L TC4427 U602
U 1 1 63D93430
P 3075 6475
F 0 "U602" H 3075 6175 60  0000 C CNN
F 1 "TC4427" H 3075 6775 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 3075 6475 60  0001 C CNN
F 3 "" H 3075 6475 60  0000 C CNN
F 4 "579-TC1427COA" H 3075 6475 60  0001 C CNN "Mouser Part Number"
	1    3075 6475
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR022
U 1 1 63D93431
P 3025 6825
F 0 "#PWR022" H 3025 6575 50  0001 C CNN
F 1 "GND" H 3025 6675 50  0000 C CNN
F 2 "" H 3025 6825 50  0001 C CNN
F 3 "" H 3025 6825 50  0001 C CNN
	1    3025 6825
	1    0    0    -1  
$EndComp
$Comp
L CP1 C605
U 1 1 63D93433
P 4025 6850
F 0 "C605" H 4050 6950 50  0000 L CNN
F 1 "2200uF 25V" H 4050 6750 50  0000 L CNN
F 2 "BigSMDCaps:EEEFK0J682AV" H 4025 6850 50  0001 C CNN
F 3 "" H 4025 6850 50  0001 C CNN
F 4 "667-EEV-FK1E222V " H 4025 6850 60  0001 C CNN "Mouser Part Number"
	1    4025 6850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 63D93434
P 4025 7225
F 0 "#PWR023" H 4025 6975 50  0001 C CNN
F 1 "GND" H 4025 7075 50  0000 C CNN
F 2 "" H 4025 7225 50  0001 C CNN
F 3 "" H 4025 7225 50  0001 C CNN
	1    4025 7225
	1    0    0    -1  
$EndComp
$Comp
L TC4427 U603
U 1 1 63D93435
P 5500 3400
F 0 "U603" H 5500 3100 60  0000 C CNN
F 1 "TC4427" H 5500 3700 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 5500 3400 60  0001 C CNN
F 3 "" H 5500 3400 60  0000 C CNN
F 4 "579-TC1427COA" H 5500 3400 60  0001 C CNN "Mouser Part Number"
	1    5500 3400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR024
U 1 1 63D93436
P 5450 3750
F 0 "#PWR024" H 5450 3500 50  0001 C CNN
F 1 "GND" H 5450 3600 50  0000 C CNN
F 2 "" H 5450 3750 50  0001 C CNN
F 3 "" H 5450 3750 50  0001 C CNN
	1    5450 3750
	1    0    0    -1  
$EndComp
$Comp
L CP1 C607
U 1 1 63D93438
P 6400 3825
F 0 "C607" H 6425 3925 50  0000 L CNN
F 1 "2200uF 25V" H 6425 3725 50  0000 L CNN
F 2 "BigSMDCaps:EEEFK0J682AV" H 6400 3825 50  0001 C CNN
F 3 "" H 6400 3825 50  0001 C CNN
F 4 "667-EEV-FK1E222V " H 6400 3825 60  0001 C CNN "Mouser Part Number"
	1    6400 3825
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR025
U 1 1 63D93439
P 6400 4100
F 0 "#PWR025" H 6400 3850 50  0001 C CNN
F 1 "GND" H 6400 3950 50  0000 C CNN
F 2 "" H 6400 4100 50  0001 C CNN
F 3 "" H 6400 4100 50  0001 C CNN
	1    6400 4100
	1    0    0    -1  
$EndComp
$Comp
L TC4427 U604
U 2 1 63D9343A
P 5525 4925
F 0 "U604" H 5525 4625 60  0000 C CNN
F 1 "TC4427" H 5525 5225 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 5525 4925 60  0001 C CNN
F 3 "" H 5525 4925 60  0000 C CNN
F 4 "579-TC1427COA" H 5525 4925 60  0001 C CNN "Mouser Part Number"
	2    5525 4925
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR026
U 1 1 63D9343B
P 5475 5275
F 0 "#PWR026" H 5475 5025 50  0001 C CNN
F 1 "GND" H 5475 5125 50  0000 C CNN
F 2 "" H 5475 5275 50  0001 C CNN
F 3 "" H 5475 5275 50  0001 C CNN
	1    5475 5275
	1    0    0    -1  
$EndComp
$Comp
L CP1 C608
U 1 1 63D9343D
P 6425 5275
F 0 "C608" H 6450 5375 50  0000 L CNN
F 1 "2200uF 25V" H 6450 5175 50  0000 L CNN
F 2 "BigSMDCaps:EEEFK0J682AV" H 6425 5275 50  0001 C CNN
F 3 "" H 6425 5275 50  0001 C CNN
F 4 "667-EEV-FK1E222V " H 6425 5275 60  0001 C CNN "Mouser Part Number"
	1    6425 5275
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR027
U 1 1 63D9343E
P 6425 5625
F 0 "#PWR027" H 6425 5375 50  0001 C CNN
F 1 "GND" H 6425 5475 50  0000 C CNN
F 2 "" H 6425 5625 50  0001 C CNN
F 3 "" H 6425 5625 50  0001 C CNN
	1    6425 5625
	1    0    0    -1  
$EndComp
$Comp
L TC4427 U604
U 1 1 63D9343F
P 5500 6325
F 0 "U604" H 5500 6025 60  0000 C CNN
F 1 "TC4427" H 5500 6625 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 5500 6325 60  0001 C CNN
F 3 "" H 5500 6325 60  0000 C CNN
F 4 "579-TC1427COA" H 5500 6325 60  0001 C CNN "Mouser Part Number"
	1    5500 6325
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR028
U 1 1 63D93440
P 5450 6675
F 0 "#PWR028" H 5450 6425 50  0001 C CNN
F 1 "GND" H 5450 6525 50  0000 C CNN
F 2 "" H 5450 6675 50  0001 C CNN
F 3 "" H 5450 6675 50  0001 C CNN
	1    5450 6675
	1    0    0    -1  
$EndComp
$Comp
L CP1 C609
U 1 1 63D93442
P 6500 6750
F 0 "C609" H 6525 6850 50  0000 L CNN
F 1 "2200uF 25V" H 6525 6650 50  0000 L CNN
F 2 "BigSMDCaps:EEEFK0J682AV" H 6500 6750 50  0001 C CNN
F 3 "" H 6500 6750 50  0001 C CNN
F 4 "667-EEV-FK1E222V " H 6500 6750 60  0001 C CNN "Mouser Part Number"
	1    6500 6750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR029
U 1 1 63D93443
P 6500 7075
F 0 "#PWR029" H 6500 6825 50  0001 C CNN
F 1 "GND" H 6500 6925 50  0000 C CNN
F 2 "" H 6500 7075 50  0001 C CNN
F 3 "" H 6500 7075 50  0001 C CNN
	1    6500 7075
	1    0    0    -1  
$EndComp
Wire Wire Line
	1675 2325 1675 2250
Wire Wire Line
	1675 2250 2000 2250
Wire Wire Line
	1675 2425 1675 2575
Wire Wire Line
	1675 2575 1925 2575
Wire Wire Line
	1925 2550 1925 2725
Connection ~ 1925 2575
Wire Wire Line
	2000 1375 5400 1375
Wire Wire Line
	2975 1375 2975 1650
Wire Wire Line
	2000 2250 2000 1375
Connection ~ 1925 2250
Wire Wire Line
	2975 2000 2975 2150
Wire Wire Line
	3800 2350 3800 2550
Wire Wire Line
	3025 3400 3025 3125
Wire Wire Line
	3025 3125 2325 3125
Wire Wire Line
	3025 3750 3025 3900
Wire Wire Line
	3375 3550 3450 3550
Wire Wire Line
	3950 3550 3950 3775
Wire Wire Line
	3950 4075 3950 4275
Wire Wire Line
	5400 1375 5400 1625
Wire Wire Line
	5400 1975 5400 2125
Wire Wire Line
	3050 4650 3050 4925
Wire Wire Line
	3050 5275 3050 5425
Wire Wire Line
	3400 5075 3475 5075
Wire Wire Line
	3950 5050 3950 5250
Wire Wire Line
	3950 5550 3950 5800
Wire Wire Line
	3025 6325 3025 6050
Wire Wire Line
	3025 6675 3025 6825
Wire Wire Line
	3375 6475 3450 6475
Wire Wire Line
	4025 6450 4025 6700
Wire Wire Line
	4025 7000 4025 7225
Wire Wire Line
	5450 3250 5450 2975
Wire Wire Line
	5450 2975 4775 2975
Wire Wire Line
	5450 3600 5450 3750
Wire Wire Line
	5800 3400 5875 3400
Wire Wire Line
	6400 3400 6400 3675
Wire Wire Line
	6400 3975 6400 4100
Wire Wire Line
	5475 4500 5475 4775
Wire Wire Line
	4775 4500 5475 4500
Wire Wire Line
	5475 5125 5475 5275
Wire Wire Line
	5825 4925 5900 4925
Wire Wire Line
	6425 4900 6425 5125
Wire Wire Line
	6425 5425 6425 5625
Wire Wire Line
	5450 6175 5450 5900
Wire Wire Line
	5450 6525 5450 6675
Wire Wire Line
	5800 6325 5875 6325
Wire Wire Line
	6500 6375 6500 6600
Wire Wire Line
	6500 6900 6500 7075
Connection ~ 2975 1375
Wire Wire Line
	2325 1375 2325 6050
Wire Wire Line
	2325 1375 2400 1375
Connection ~ 2400 1375
Wire Wire Line
	4775 1375 4775 5900
Connection ~ 4775 1375
Connection ~ 4775 4500
Connection ~ 4775 2975
Wire Wire Line
	4775 5900 5450 5900
Connection ~ 2325 3125
Wire Wire Line
	2325 4650 3050 4650
Connection ~ 2325 4650
Wire Wire Line
	2325 6050 3025 6050
Text HLabel 2775 1800 0    60   Input ~ 0
Motor_1
Text HLabel 2825 3550 0    60   Input ~ 0
Motor_2
Text HLabel 2850 5075 0    60   Input ~ 0
Motor_3
Text HLabel 2825 6475 0    60   Input ~ 0
Motor_4
Text HLabel 5250 6325 0    60   Input ~ 0
Motor_8
Text HLabel 5275 4925 0    60   Input ~ 0
Motor_7
Text HLabel 5250 3400 0    60   Input ~ 0
Motor_6
Text HLabel 5200 1775 0    60   Input ~ 0
Motor_5
Text GLabel 2000 1375 0    60   Input ~ 0
MotorPower
$Comp
L Screw_Terminal_01x03 J602
U 1 1 63D935B4
P 4025 1825
F 0 "J602" H 4025 2025 50  0000 C CNN
F 1 "Motor 1" H 4025 1625 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_PT-3.5mm_3pol" H 4025 1825 50  0001 C CNN
F 3 "" H 4025 1825 50  0001 C CNN
	1    4025 1825
	1    0    0    -1  
$EndComp
$Comp
L D_ALT D601
U 1 1 63D936BB
P 3575 1725
F 0 "D601" H 3575 1825 50  0000 C CNN
F 1 "S2A" H 3575 1625 50  0000 C CNN
F 2 "Rectifiers:DIOM5336X245N" H 3575 1725 50  0001 C CNN
F 3 "" H 3575 1725 50  0001 C CNN
F 4 "512-S2A" H 3575 1725 60  0001 C CNN "Mouser Part Number"
	1    3575 1725
	-1   0    0    1   
$EndComp
$Comp
L D_ALT D602
U 1 1 63D94334
P 3575 1925
F 0 "D602" H 3575 2025 50  0000 C CNN
F 1 "S2A" H 3575 1825 50  0000 C CNN
F 2 "Rectifiers:DIOM5336X245N" H 3575 1925 50  0001 C CNN
F 3 "" H 3575 1925 50  0001 C CNN
F 4 "512-S2A" H 3575 1925 60  0001 C CNN "Mouser Part Number"
	1    3575 1925
	1    0    0    -1  
$EndComp
Wire Wire Line
	3325 1725 3325 1925
Wire Wire Line
	3325 1725 3425 1725
Wire Wire Line
	3325 1925 3425 1925
Wire Wire Line
	3325 1800 3325 1800
Wire Wire Line
	3725 1925 3825 1925
Wire Wire Line
	3725 1725 3825 1725
Wire Wire Line
	3800 2050 3800 1825
Wire Wire Line
	3800 1825 3825 1825
Wire Wire Line
	6250 2325 6250 2500
$Comp
L Screw_Terminal_01x03 J606
U 1 1 63D94DC7
P 6500 1775
F 0 "J606" H 6500 1975 50  0000 C CNN
F 1 "Motor 5" H 6500 1575 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_PT-3.5mm_3pol" H 6500 1775 50  0001 C CNN
F 3 "" H 6500 1775 50  0001 C CNN
	1    6500 1775
	1    0    0    -1  
$EndComp
$Comp
L D_ALT D609
U 1 1 63D94E72
P 5975 1675
F 0 "D609" H 5975 1775 50  0000 C CNN
F 1 "S2A" H 5975 1575 50  0000 C CNN
F 2 "Rectifiers:DIOM5336X245N" H 5975 1675 50  0001 C CNN
F 3 "" H 5975 1675 50  0001 C CNN
F 4 "512-S2A" H 5975 1675 60  0001 C CNN "Mouser Part Number"
	1    5975 1675
	-1   0    0    1   
$EndComp
$Comp
L D_ALT D610
U 1 1 63D94F3F
P 5975 1875
F 0 "D610" H 5975 1975 50  0000 C CNN
F 1 "S2A" H 5975 1775 50  0000 C CNN
F 2 "Rectifiers:DIOM5336X245N" H 5975 1875 50  0001 C CNN
F 3 "" H 5975 1875 50  0001 C CNN
F 4 "512-S2A" H 5975 1875 60  0001 C CNN "Mouser Part Number"
	1    5975 1875
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 1675 5750 1875
Wire Wire Line
	5750 1675 5825 1675
Wire Wire Line
	5750 1875 5825 1875
Connection ~ 5750 1775
Wire Wire Line
	6125 1675 6300 1675
Wire Wire Line
	6125 1875 6300 1875
Wire Wire Line
	6300 1775 6250 1775
Wire Wire Line
	6250 1775 6250 2025
$Comp
L Screw_Terminal_01x03 J603
U 1 1 63D95AE8
P 4225 3550
F 0 "J603" H 4225 3750 50  0000 C CNN
F 1 "Motor 2" H 4225 3350 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_PT-3.5mm_3pol" H 4225 3550 50  0001 C CNN
F 3 "" H 4225 3550 50  0001 C CNN
	1    4225 3550
	1    0    0    -1  
$EndComp
$Comp
L D_ALT D603
U 1 1 63D95C29
P 3700 3450
F 0 "D603" H 3700 3550 50  0000 C CNN
F 1 "S2A" H 3700 3350 50  0000 C CNN
F 2 "Rectifiers:DIOM5336X245N" H 3700 3450 50  0001 C CNN
F 3 "" H 3700 3450 50  0001 C CNN
F 4 "512-S2A" H 3700 3450 60  0001 C CNN "Mouser Part Number"
	1    3700 3450
	-1   0    0    1   
$EndComp
$Comp
L D_ALT D604
U 1 1 63D95CFC
P 3700 3650
F 0 "D604" H 3700 3750 50  0000 C CNN
F 1 "S2A" H 3700 3550 50  0000 C CNN
F 2 "Rectifiers:DIOM5336X245N" H 3700 3650 50  0001 C CNN
F 3 "" H 3700 3650 50  0001 C CNN
F 4 "512-S2A" H 3700 3650 60  0001 C CNN "Mouser Part Number"
	1    3700 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4025 3550 3950 3550
Wire Wire Line
	3450 3450 3450 3650
Wire Wire Line
	3450 3450 3550 3450
Wire Wire Line
	3450 3650 3550 3650
Connection ~ 3450 3550
Wire Wire Line
	3850 3450 4025 3450
Wire Wire Line
	3850 3650 4025 3650
$Comp
L Screw_Terminal_01x03 J607
U 1 1 63D97C0A
P 6625 3400
F 0 "J607" H 6625 3600 50  0000 C CNN
F 1 "Motor 6" H 6625 3200 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_PT-3.5mm_3pol" H 6625 3400 50  0001 C CNN
F 3 "" H 6625 3400 50  0001 C CNN
	1    6625 3400
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x03 J608
U 1 1 63D97CC0
P 6675 4900
F 0 "J608" H 6675 5100 50  0000 C CNN
F 1 "Motor 7" H 6675 4700 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_PT-3.5mm_3pol" H 6675 4900 50  0001 C CNN
F 3 "" H 6675 4900 50  0001 C CNN
	1    6675 4900
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x03 J609
U 1 1 63D97D65
P 6750 6375
F 0 "J609" H 6750 6575 50  0000 C CNN
F 1 "Motor 8" H 6750 6175 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_PT-3.5mm_3pol" H 6750 6375 50  0001 C CNN
F 3 "" H 6750 6375 50  0001 C CNN
	1    6750 6375
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x03 J605
U 1 1 63D97E11
P 4300 6450
F 0 "J605" H 4300 6650 50  0000 C CNN
F 1 "Motor 4" H 4300 6250 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_PT-3.5mm_3pol" H 4300 6450 50  0001 C CNN
F 3 "" H 4300 6450 50  0001 C CNN
	1    4300 6450
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x03 J604
U 1 1 63D97ED4
P 4300 5050
F 0 "J604" H 4300 5250 50  0000 C CNN
F 1 "Motor 3" H 4300 4850 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_PT-3.5mm_3pol" H 4300 5050 50  0001 C CNN
F 3 "" H 4300 5050 50  0001 C CNN
	1    4300 5050
	1    0    0    -1  
$EndComp
$Comp
L D_ALT D611
U 1 1 63D98440
P 6200 3300
F 0 "D611" H 6200 3400 50  0000 C CNN
F 1 "S2A" H 6200 3200 50  0000 C CNN
F 2 "Rectifiers:DIOM5336X245N" H 6200 3300 50  0001 C CNN
F 3 "" H 6200 3300 50  0001 C CNN
F 4 "512-S2A" H 6200 3300 60  0001 C CNN "Mouser Part Number"
	1    6200 3300
	-1   0    0    1   
$EndComp
$Comp
L D_ALT D612
U 1 1 63D98505
P 6200 3500
F 0 "D612" H 6200 3600 50  0000 C CNN
F 1 "S2A" H 6200 3400 50  0000 C CNN
F 2 "Rectifiers:DIOM5336X245N" H 6200 3500 50  0001 C CNN
F 3 "" H 6200 3500 50  0001 C CNN
F 4 "512-S2A" H 6200 3500 60  0001 C CNN "Mouser Part Number"
	1    6200 3500
	1    0    0    -1  
$EndComp
$Comp
L D_ALT D613
U 1 1 63D985DD
P 6200 4800
F 0 "D613" H 6200 4900 50  0000 C CNN
F 1 "S2A" H 6200 4700 50  0000 C CNN
F 2 "Rectifiers:DIOM5336X245N" H 6200 4800 50  0001 C CNN
F 3 "" H 6200 4800 50  0001 C CNN
F 4 "512-S2A" H 6200 4800 60  0001 C CNN "Mouser Part Number"
	1    6200 4800
	-1   0    0    1   
$EndComp
$Comp
L D_ALT D615
U 1 1 63D986B0
P 6275 6275
F 0 "D615" H 6275 6375 50  0000 C CNN
F 1 "S2A" H 6275 6175 50  0000 C CNN
F 2 "Rectifiers:DIOM5336X245N" H 6275 6275 50  0001 C CNN
F 3 "" H 6275 6275 50  0001 C CNN
F 4 "512-S2A" H 6275 6275 60  0001 C CNN "Mouser Part Number"
	1    6275 6275
	-1   0    0    1   
$EndComp
$Comp
L D_ALT D607
U 1 1 63D98774
P 3775 6350
F 0 "D607" H 3775 6450 50  0000 C CNN
F 1 "S2A" H 3775 6250 50  0000 C CNN
F 2 "Rectifiers:DIOM5336X245N" H 3775 6350 50  0001 C CNN
F 3 "" H 3775 6350 50  0001 C CNN
F 4 "512-S2A" H 3775 6350 60  0001 C CNN "Mouser Part Number"
	1    3775 6350
	-1   0    0    1   
$EndComp
$Comp
L D_ALT D605
U 1 1 63D9885B
P 3700 4950
F 0 "D605" H 3700 5050 50  0000 C CNN
F 1 "S2A" H 3700 4850 50  0000 C CNN
F 2 "Rectifiers:DIOM5336X245N" H 3700 4950 50  0001 C CNN
F 3 "" H 3700 4950 50  0001 C CNN
F 4 "512-S2A" H 3700 4950 60  0001 C CNN "Mouser Part Number"
	1    3700 4950
	-1   0    0    1   
$EndComp
$Comp
L D_ALT D614
U 1 1 63D9891D
P 6200 5000
F 0 "D614" H 6200 5100 50  0000 C CNN
F 1 "S2A" H 6200 4900 50  0000 C CNN
F 2 "Rectifiers:DIOM5336X245N" H 6200 5000 50  0001 C CNN
F 3 "" H 6200 5000 50  0001 C CNN
F 4 "512-S2A" H 6200 5000 60  0001 C CNN "Mouser Part Number"
	1    6200 5000
	1    0    0    -1  
$EndComp
$Comp
L D_ALT D616
U 1 1 63D989FA
P 6275 6475
F 0 "D616" H 6275 6575 50  0000 C CNN
F 1 "S2A" H 6275 6375 50  0000 C CNN
F 2 "Rectifiers:DIOM5336X245N" H 6275 6475 50  0001 C CNN
F 3 "" H 6275 6475 50  0001 C CNN
F 4 "512-S2A" H 6275 6475 60  0001 C CNN "Mouser Part Number"
	1    6275 6475
	1    0    0    -1  
$EndComp
$Comp
L D_ALT D608
U 1 1 63D98AA2
P 3775 6550
F 0 "D608" H 3775 6650 50  0000 C CNN
F 1 "S2A" H 3775 6450 50  0000 C CNN
F 2 "Rectifiers:DIOM5336X245N" H 3775 6550 50  0001 C CNN
F 3 "" H 3775 6550 50  0001 C CNN
F 4 "512-S2A" H 3775 6550 60  0001 C CNN "Mouser Part Number"
	1    3775 6550
	1    0    0    -1  
$EndComp
$Comp
L D_ALT D606
U 1 1 63D98B7B
P 3700 5150
F 0 "D606" H 3700 5250 50  0000 C CNN
F 1 "S2A" H 3700 5050 50  0000 C CNN
F 2 "Rectifiers:DIOM5336X245N" H 3700 5150 50  0001 C CNN
F 3 "" H 3700 5150 50  0001 C CNN
F 4 "512-S2A" H 3700 5150 60  0001 C CNN "Mouser Part Number"
	1    3700 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6425 3400 6400 3400
Wire Wire Line
	6350 3300 6425 3300
Wire Wire Line
	6350 3500 6425 3500
Wire Wire Line
	5875 3300 5875 3500
Wire Wire Line
	5875 3300 6050 3300
Wire Wire Line
	5875 3500 6050 3500
Connection ~ 5875 3400
Wire Wire Line
	6475 4800 6350 4800
Wire Wire Line
	6475 4900 6425 4900
Wire Wire Line
	6475 5000 6350 5000
Wire Wire Line
	5900 5000 6050 5000
Wire Wire Line
	5900 4800 5900 5000
Wire Wire Line
	5900 4800 6050 4800
Connection ~ 5900 4925
Wire Wire Line
	5875 6275 5875 6475
Wire Wire Line
	5875 6275 6125 6275
Wire Wire Line
	5875 6475 6125 6475
Connection ~ 5875 6325
Wire Wire Line
	6425 6275 6550 6275
Wire Wire Line
	6500 6375 6550 6375
Wire Wire Line
	6425 6475 6550 6475
Wire Wire Line
	3925 6550 4100 6550
Wire Wire Line
	4025 6450 4100 6450
Wire Wire Line
	3925 6350 4100 6350
Wire Wire Line
	3625 6350 3450 6350
Wire Wire Line
	3450 6350 3450 6550
Wire Wire Line
	3450 6550 3625 6550
Connection ~ 3450 6475
Wire Wire Line
	3475 4950 3475 5150
Wire Wire Line
	3475 5150 3550 5150
Wire Wire Line
	3550 4950 3475 4950
Connection ~ 3475 5075
Wire Wire Line
	3850 4950 4100 4950
Wire Wire Line
	3850 5150 4100 5150
Wire Wire Line
	3950 5050 4100 5050
Connection ~ 3325 1800
$EndSCHEMATC