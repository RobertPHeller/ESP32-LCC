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
LIBS:ESP32-C3FN4
LIBS:USBLC6-2SC6
LIBS:sn65hvd233-ht
LIBS:lm2574n-5
LIBS:DRV8873HPWPR
LIBS:mcp9701at
LIBS:MCP9700T-E_LT
LIBS:ina180b
LIBS:mechanical
LIBS:ESP32-C3-Booster-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 6
Title "Pocket Beagle DCC Command Station (SMD version)"
Date "2021-04-09"
Rev "A"
Comp "Deepwoods Software"
Comment1 "Power Supplies"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CP1 C401
U 1 1 630A5C09
P 4650 3450
F 0 "C401" H 4700 3550 50  0000 L CNN
F 1 "220 uf 25V" V 4500 3250 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_8x10" H 4650 3450 60  0001 C CNN
F 3 "~" H 4650 3450 60  0000 C CNN
F 4 "647-UUX2A220MNL6GS" H 4650 3450 60  0001 C CNN "Mouser Part Number"
	1    4650 3450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR040
U 1 1 630A5C0A
P 5500 4050
F 0 "#PWR040" H 5500 4050 30  0001 C CNN
F 1 "GND" H 5500 3980 30  0001 C CNN
F 2 "" H 5500 4050 60  0000 C CNN
F 3 "" H 5500 4050 60  0000 C CNN
	1    5500 4050
	1    0    0    -1  
$EndComp
$Comp
L CP1 C403
U 1 1 630A5C0B
P 6550 3550
F 0 "C403" H 6600 3650 50  0000 L CNN
F 1 "22 uf 100V" H 6600 3450 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_8x10" H 6550 3550 60  0001 C CNN
F 3 "~" H 6550 3550 60  0000 C CNN
F 4 "647-UWT1E221MNL1GS" H 6550 3550 60  0001 C CNN "Mouser Part Number"
	1    6550 3550
	1    0    0    -1  
$EndComp
Text HLabel 4300 3250 0    60   Output ~ 0
3.3V Out
Text HLabel 8350 2800 2    60   Input ~ 0
Power Input
$Comp
L L L401
U 1 1 630A5C0C
P 5150 3550
F 0 "L401" V 5100 3550 50  0000 C CNN
F 1 "330 mh" V 5225 3550 50  0000 C CNN
F 2 "SRN1060:SRN1060" H 5150 3550 50  0001 C CNN
F 3 "" H 5150 3550 50  0001 C CNN
F 4 "652-SRN1060-331M" V 5150 3550 60  0001 C CNN "Mouser Part Number"
	1    5150 3550
	0    1    1    0   
$EndComp
$Comp
L D_Schottky D401
U 1 1 630A5C0D
P 5500 3750
F 0 "D401" H 5500 3850 50  0000 C CNN
F 1 "CMSH1-60" H 5500 3650 50  0000 C CNN
F 2 "Diodes_SMD:D_SMA" H 5500 3750 50  0001 C CNN
F 3 "" H 5500 3750 50  0001 C CNN
F 4 "610-CMSH1-60TR13" H 5500 3750 60  0001 C CNN "Mouser Part Number"
	1    5500 3750
	0    1    1    0   
$EndComp
$Comp
L TEST_1P TP401
U 1 1 630A5C1D
P 4400 3050
F 0 "TP401" H 4400 3320 50  0000 C CNN
F 1 "3.3V" H 4400 3250 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Big" H 4600 3050 50  0001 C CNN
F 3 "" H 4600 3050 50  0001 C CNN
	1    4400 3050
	1    0    0    -1  
$EndComp
$Comp
L LM2574HVM-5.0 U401
U 1 1 630A5C20
P 5850 3450
F 0 "U401" H 5850 3500 60  0000 C CNN
F 1 "LM2574HVM-3.3" H 5850 3600 21  0000 C CNN
F 2 "SOIC_Wide:SOIC-14_7.4x8.7mm_Pitch1.27mm" H 5850 3450 60  0001 C CNN
F 3 "" H 5850 3450 60  0000 C CNN
F 4 "926-LM2574MX33NOPB" H 5850 3450 60  0001 C CNN "Mouser Part Number"
	1    5850 3450
	1    0    0    -1  
$EndComp
$Comp
L LF120_TO220 U402
U 1 1 630A5C21
P 9750 3300
F 0 "U402" H 9600 3425 50  0000 C CNN
F 1 "LF120_TO220" H 9750 3425 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:TO-252-2" H 9750 3525 50  0001 C CIN
F 3 "" H 9750 3250 50  0001 C CNN
F 4 "511-LF120ABDT-TR" H 9750 3300 60  0001 C CNN "Mouser Part Number"
	1    9750 3300
	1    0    0    -1  
$EndComp
$Comp
L C_Small C405
U 1 1 630A5C22
P 9250 3500
F 0 "C405" H 9260 3570 50  0000 L CNN
F 1 "10 nf" H 9260 3420 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 9250 3500 50  0001 C CNN
F 3 "" H 9250 3500 50  0001 C CNN
F 4 "791-1206B103K500CT" H 9250 3500 60  0001 C CNN "Mouser Part Number"
	1    9250 3500
	1    0    0    -1  
$EndComp
$Comp
L CP1_Small C406
U 1 1 630A5C23
P 10200 3450
F 0 "C406" H 10210 3520 50  0000 L CNN
F 1 "10 uf" H 10210 3370 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_5x5.3" H 10200 3450 50  0001 C CNN
F 3 "" H 10200 3450 50  0001 C CNN
F 4 "710-865230542002" H 10200 3450 60  0001 C CNN "Mouser Part Number"
	1    10200 3450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR041
U 1 1 630A5C24
P 9750 3800
F 0 "#PWR041" H 9750 3550 50  0001 C CNN
F 1 "GND" H 9750 3650 50  0000 C CNN
F 2 "" H 9750 3800 50  0001 C CNN
F 3 "" H 9750 3800 50  0001 C CNN
	1    9750 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 3250 4900 3550
Wire Wire Line
	4300 3250 5550 3250
Connection ~ 4900 3250
Wire Wire Line
	5800 3800 6550 3800
Connection ~ 5900 3800
Connection ~ 5800 3800
Wire Wire Line
	6150 3350 7150 3350
Wire Wire Line
	6550 3800 6550 3700
Connection ~ 6000 3800
Wire Wire Line
	5300 3550 5550 3550
Connection ~ 5500 3550
Wire Wire Line
	5800 3950 5800 3800
Wire Wire Line
	4650 3950 5800 3950
Wire Wire Line
	5500 3900 5500 4050
Wire Wire Line
	4650 3950 4650 3600
Connection ~ 5500 3950
Connection ~ 4650 3250
Connection ~ 6550 3350
Wire Wire Line
	4650 3300 4650 3250
Wire Wire Line
	6550 3400 6550 3350
Wire Wire Line
	4900 3550 5000 3550
Wire Wire Line
	5500 3600 5500 3550
Wire Wire Line
	4400 3050 4400 3250
Connection ~ 4400 3250
Wire Wire Line
	9250 3300 9250 3400
Wire Wire Line
	9250 3600 10200 3600
Wire Wire Line
	10050 3300 10400 3300
Wire Wire Line
	10200 3300 10200 3350
Wire Wire Line
	10200 3600 10200 3550
Connection ~ 9750 3600
Wire Wire Line
	9750 3800 9750 3600
Connection ~ 9250 3300
Text HLabel 10400 3300 2    60   Output ~ 0
12V
Connection ~ 10200 3300
NoConn ~ 5750 3100
NoConn ~ 5800 3100
NoConn ~ 5850 3100
NoConn ~ 5900 3100
NoConn ~ 5950 3100
NoConn ~ 6000 3100
NoConn ~ 6150 3450
NoConn ~ 6150 3550
Wire Wire Line
	7450 3300 9450 3300
Wire Wire Line
	8350 2800 8350 3300
$Comp
L D_Schottky D403
U 1 1 630AA312
P 7300 3350
F 0 "D403" H 7300 3450 50  0000 C CNN
F 1 "DFLS240" H 7300 3250 50  0000 C CNN
F 2 "Diodes_SMD:D_PowerDI-123" H 7300 3350 50  0001 C CNN
F 3 "" H 7300 3350 50  0001 C CNN
F 4 "621-DFLS240-7" H 7300 3350 60  0001 C CNN "Mouser Part Number"
	1    7300 3350
	1    0    0    -1  
$EndComp
$Comp
L D_Schottky D402
U 1 1 630AA381
P 7300 3050
F 0 "D402" H 7300 3150 50  0000 C CNN
F 1 "DFLS240" H 7300 2950 50  0000 C CNN
F 2 "Diodes_SMD:D_PowerDI-123" H 7300 3050 50  0001 C CNN
F 3 "" H 7300 3050 50  0001 C CNN
F 4 "621-DFLS240-7" H 7300 3050 60  0001 C CNN "Mouser Part Number"
	1    7300 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 3300 7450 3350
Connection ~ 8350 3300
Wire Wire Line
	7150 3350 7150 3050
$Comp
L VBUS #PWR042
U 1 1 630AA49C
P 7450 2750
F 0 "#PWR042" H 7450 2600 50  0001 C CNN
F 1 "VBUS" H 7450 2900 50  0000 C CNN
F 2 "" H 7450 2750 50  0001 C CNN
F 3 "" H 7450 2750 50  0001 C CNN
	1    7450 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 2750 7450 3050
$EndSCHEMATC