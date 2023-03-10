EESchema Schematic File Version 2
LIBS:ESP32-D0WD-V3-MultiFunction-rescue
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
LIBS:ESP32-D0WD-V3
LIBS:W25Q32JVSSIQ
LIBS:umh3n
LIBS:lm2574n-5
LIBS:tc442x
LIBS:4814p-2
LIBS:pca9685
LIBS:tbd62x83a
LIBS:sn65hvd233-ht
LIBS:mechanical
LIBS:graphic_symbols
LIBS:ESP32-D0WD-V3-MultiFunction-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 8
Title "ESP32 Multifunction Board"
Date ""
Rev "1.0"
Comp "Deepwoods Software"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ESP32-D0WD-V3 U201
U 1 1 62ACDF68
P 4850 3200
F 0 "U201" H 5600 2950 50  0000 L CNN
F 1 "ESP32-D0WD-V3" H 5400 3300 50  0000 L CNN
F 2 "ESP32-D0WD-V3:QFN35P500X500X90-49N-D" H 6500 3700 50  0001 L CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf" H 6500 3600 50  0001 L CNN
F 4 "WiFi Development Tools (802.11) SMD IC WiFi Dual Core BT Combo" H 6500 3500 50  0001 L CNN "Description"
F 5 "0.9" H 6500 3400 50  0001 L CNN "Height"
F 6 "Espressif Systems" H 6500 3100 50  0001 L CNN "Manufacturer_Name"
F 7 "ESP32-D0WD-V3" H 6500 3000 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "356-ESP32-D0WD-V3 " H 4850 3200 60  0001 C CNN "Mouser Part Number"
	1    4850 3200
	1    0    0    -1  
$EndComp
$Comp
L W25Q32JVSSIQ U202
U 1 1 62ACEC4E
P 7100 3800
F 0 "U202" H 7900 3700 50  0000 L CNN
F 1 "W25Q32JVSSIQ" H 7500 3500 50  0000 L CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 8450 3900 50  0001 L CNN
F 3 "https://componentsearchengine.com//W25Q32JVSSIQ.pdf" H 8450 3800 50  0001 L CNN
F 4 "NOR Flash spiFlash, 32M-bit, DTR, 4Kb Uniform Sector" H 8450 3700 50  0001 L CNN "Description"
F 5 "2.16" H 8450 3600 50  0001 L CNN "Height"
F 6 "454-W25Q32JVSSIQ" H 8450 3500 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=454-W25Q32JVSSIQ" H 8450 3400 50  0001 L CNN "Mouser2 Price/Stock"
F 8 "Winbond" H 8450 3300 50  0001 L CNN "Manufacturer_Name"
F 9 "W25Q32JVSSIQ" H 8450 3200 50  0001 L CNN "Manufacturer_Part_Number"
	1    7100 3800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR02
U 1 1 62ACEDF1
P 8850 3450
F 0 "#PWR02" H 8850 3300 50  0001 C CNN
F 1 "+3.3V" H 8850 3590 50  0000 C CNN
F 2 "" H 8850 3450 50  0001 C CNN
F 3 "" H 8850 3450 50  0001 C CNN
	1    8850 3450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 62ACEE0B
P 7000 4400
F 0 "#PWR03" H 7000 4150 50  0001 C CNN
F 1 "GND" H 7000 4250 50  0000 C CNN
F 2 "" H 7000 4400 50  0001 C CNN
F 3 "" H 7000 4400 50  0001 C CNN
	1    7000 4400
	1    0    0    -1  
$EndComp
$Comp
L Conn_02x03_Odd_Even J201
U 1 1 62ADE271
P 7350 2700
F 0 "J201" H 7400 2900 50  0000 C CNN
F 1 "Programming Header" H 7400 2500 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03_Pitch2.54mm" H 7350 2700 50  0001 C CNN
F 3 "" H 7350 2700 50  0001 C CNN
F 4 "523-G800LQ593032HR " H 7350 2700 60  0001 C CNN "Mouser Part Number"
	1    7350 2700
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR04
U 1 1 62ADE314
P 7150 2500
F 0 "#PWR04" H 7150 2350 50  0001 C CNN
F 1 "+3.3V" H 7150 2640 50  0000 C CNN
F 2 "" H 7150 2500 50  0001 C CNN
F 3 "" H 7150 2500 50  0001 C CNN
	1    7150 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 62ADE33C
P 7650 3000
F 0 "#PWR05" H 7650 2750 50  0001 C CNN
F 1 "GND" H 7650 2850 50  0000 C CNN
F 2 "" H 7650 3000 50  0001 C CNN
F 3 "" H 7650 3000 50  0001 C CNN
	1    7650 3000
	1    0    0    -1  
$EndComp
Text Label 7650 2600 0    60   ~ 0
BOOTMODE
Text Label 7650 2700 0    60   ~ 0
RESET
Text Label 7150 2700 2    60   ~ 0
TX
Text Label 7150 2800 2    60   ~ 0
RX
Text Label 6050 5500 3    60   ~ 0
BOOTMODE
Text Label 4700 4000 2    60   ~ 0
RESET
$Comp
L R R205
U 1 1 62ADE572
P 6150 2250
F 0 "R205" V 6230 2250 50  0000 C CNN
F 1 "49.9" V 6150 2250 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 6080 2250 50  0001 C CNN
F 3 "" H 6150 2250 50  0001 C CNN
F 4 "791-RMC1/16SK49R9FTH" V 6150 2250 60  0001 C CNN "Mouser Part Number"
	1    6150 2250
	1    0    0    -1  
$EndComp
$Comp
L R R204
U 1 1 62ADE5AD
P 6050 2250
F 0 "R204" V 6130 2250 50  0000 C CNN
F 1 "49.9" V 6050 2250 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 5980 2250 50  0001 C CNN
F 3 "" H 6050 2250 50  0001 C CNN
F 4 "791-RMC1/16SK49R9FTH" V 6050 2250 60  0001 C CNN "Mouser Part Number"
	1    6050 2250
	1    0    0    -1  
$EndComp
Text Label 6150 2100 0    60   ~ 0
RX
Text Label 6050 2100 0    60   ~ 0
TX
$Comp
L C_Small C209
U 1 1 62ADE84E
P 3650 4150
F 0 "C209" H 3660 4220 50  0000 L CNN
F 1 "1uf" H 3660 4070 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 3650 4150 50  0001 C CNN
F 3 "" H 3650 4150 50  0001 C CNN
F 4 "80-C0402C101K8RAUTO" H 3650 4150 60  0001 C CNN "Mouser Part Number"
	1    3650 4150
	1    0    0    -1  
$EndComp
$Comp
L R R201
U 1 1 62ADE899
P 3650 3750
F 0 "R201" V 3730 3750 50  0000 C CNN
F 1 "10K" V 3650 3750 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 3580 3750 50  0001 C CNN
F 3 "" H 3650 3750 50  0001 C CNN
F 4 "603-RC0402JR-1310KL" V 3650 3750 60  0001 C CNN "Mouser Part Number"
	1    3650 3750
	1    0    0    -1  
$EndComp
$Comp
L SW_Push SW201
U 1 1 62ADE8F6
P 3350 4000
F 0 "SW201" H 3400 4100 50  0000 L CNN
F 1 "RESET" H 3350 3940 50  0000 C CNN
F 2 "PTS647SN70SMTR2LFS:PTS647SM38SMTR2LFS" H 3350 4200 50  0001 C CNN
F 3 "" H 3350 4200 50  0001 C CNN
F 4 "611-PTS647SN70SMTR2L" H 3350 4000 60  0001 C CNN "Mouser Part Number"
	1    3350 4000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 62ADE9D0
P 3650 4350
F 0 "#PWR06" H 3650 4100 50  0001 C CNN
F 1 "GND" H 3650 4200 50  0000 C CNN
F 2 "" H 3650 4350 50  0001 C CNN
F 3 "" H 3650 4350 50  0001 C CNN
	1    3650 4350
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR07
U 1 1 62ADE9FC
P 3650 3550
F 0 "#PWR07" H 3650 3400 50  0001 C CNN
F 1 "+3.3V" H 3650 3690 50  0000 C CNN
F 2 "" H 3650 3550 50  0001 C CNN
F 3 "" H 3650 3550 50  0001 C CNN
	1    3650 3550
	1    0    0    -1  
$EndComp
$Comp
L C_Small C217
U 1 1 62ADEDFF
P 7200 4600
F 0 "C217" H 7210 4670 50  0000 L CNN
F 1 "1uf" H 7210 4520 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 7200 4600 50  0001 C CNN
F 3 "" H 7200 4600 50  0001 C CNN
F 4 "80-C0402C101K8RAUTO" H 7200 4600 60  0001 C CNN "Mouser Part Number"
	1    7200 4600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 62ADF002
P 7200 4800
F 0 "#PWR08" H 7200 4550 50  0001 C CNN
F 1 "GND" H 7200 4650 50  0000 C CNN
F 2 "" H 7200 4800 50  0001 C CNN
F 3 "" H 7200 4800 50  0001 C CNN
	1    7200 4800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR09
U 1 1 62ADF05E
P 7400 4500
F 0 "#PWR09" H 7400 4350 50  0001 C CNN
F 1 "+3.3V" H 7400 4640 50  0000 C CNN
F 2 "" H 7400 4500 50  0001 C CNN
F 3 "" H 7400 4500 50  0001 C CNN
	1    7400 4500
	0    1    1    0   
$EndComp
$Comp
L L_Small L201
U 1 1 62ADF39A
P 4500 3000
F 0 "L201" H 4530 3040 50  0000 L CNN
F 1 "2.0nH" H 4530 2960 50  0000 L CNN
F 2 "Inductors_SMD:L_0402" H 4500 3000 50  0001 C CNN
F 3 "" H 4500 3000 50  0001 C CNN
F 4 "810-MLG1005S2N0ST000 " H 4500 3000 60  0001 C CNN "Mouser Part Number"
	1    4500 3000
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR010
U 1 1 62ADF452
P 4500 2800
F 0 "#PWR010" H 4500 2650 50  0001 C CNN
F 1 "+3.3V" H 4500 2940 50  0000 C CNN
F 2 "" H 4500 2800 50  0001 C CNN
F 3 "" H 4500 2800 50  0001 C CNN
	1    4500 2800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR011
U 1 1 62ADF83F
P 6950 3300
F 0 "#PWR011" H 6950 3150 50  0001 C CNN
F 1 "+3.3V" H 6950 3440 50  0000 C CNN
F 2 "" H 6950 3300 50  0001 C CNN
F 3 "" H 6950 3300 50  0001 C CNN
	1    6950 3300
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR012
U 1 1 62ADF90D
P 5850 2150
F 0 "#PWR012" H 5850 2000 50  0001 C CNN
F 1 "+3.3V" H 5850 2290 50  0000 C CNN
F 2 "" H 5850 2150 50  0001 C CNN
F 3 "" H 5850 2150 50  0001 C CNN
	1    5850 2150
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR013
U 1 1 62ADFA0F
P 5650 5650
F 0 "#PWR013" H 5650 5500 50  0001 C CNN
F 1 "+3.3V" H 5650 5790 50  0000 C CNN
F 2 "" H 5650 5650 50  0001 C CNN
F 3 "" H 5650 5650 50  0001 C CNN
	1    5650 5650
	-1   0    0    1   
$EndComp
Text Label 4500 3400 0    60   ~ 0
VDD3P3
$Comp
L GND #PWR014
U 1 1 62ADFAEA
P 5250 2400
F 0 "#PWR014" H 5250 2150 50  0001 C CNN
F 1 "GND" H 5250 2250 50  0000 C CNN
F 2 "" H 5250 2400 50  0001 C CNN
F 3 "" H 5250 2400 50  0001 C CNN
	1    5250 2400
	-1   0    0    1   
$EndComp
$Comp
L Crystal_GND24 Y201
U 1 1 62ADFBBB
P 5650 1550
F 0 "Y201" H 5450 1450 50  0000 L CNN
F 1 "40 Mhz +/- 10 ppm" H 5100 1400 50  0000 L CNN
F 2 "FA_20H:FA20_H" H 5650 1550 50  0001 C CNN
F 3 "https://www.mouser.com/datasheet/2/137/FA_20H_en-1062154.pdf" H 5650 1550 50  0001 C CNN
F 4 "732-FA-20H40MF10Z-W3 " H 5650 1550 60  0001 C CNN "Mouser Part Number"
	1    5650 1550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8850 3450 8850 3800
Wire Wire Line
	8850 3800 8600 3800
Wire Wire Line
	7000 4400 7000 4100
Wire Wire Line
	7000 4100 7100 4100
Wire Wire Line
	7100 3800 6900 3800
Wire Wire Line
	6900 3800 6900 4000
Wire Wire Line
	6900 4000 6650 4000
Wire Wire Line
	6650 3800 6800 3800
Wire Wire Line
	6800 3800 6800 3900
Wire Wire Line
	6800 3900 7100 3900
Wire Wire Line
	7100 4000 6950 4000
Wire Wire Line
	6950 4000 6950 4100
Wire Wire Line
	6950 4100 6650 4100
Wire Wire Line
	8600 4100 9000 4100
Wire Wire Line
	9000 4100 9000 3500
Wire Wire Line
	9000 3500 6900 3500
Wire Wire Line
	6900 3500 6900 3700
Wire Wire Line
	6900 3700 6650 3700
Wire Wire Line
	8600 4000 8850 4000
Wire Wire Line
	8850 4000 8850 4300
Wire Wire Line
	8850 4300 6750 4300
Wire Wire Line
	6750 4300 6750 3900
Wire Wire Line
	6750 3900 6650 3900
Wire Wire Line
	6650 4200 7150 4200
Wire Wire Line
	7150 4200 7150 4400
Wire Wire Line
	7150 4400 8900 4400
Wire Wire Line
	8900 4400 8900 3900
Wire Wire Line
	8900 3900 8600 3900
Wire Wire Line
	7650 2800 7650 3000
Wire Wire Line
	7150 2600 7150 2500
Wire Wire Line
	6050 5500 6050 5400
Wire Wire Line
	3550 4000 4850 4000
Wire Wire Line
	6150 2400 6150 2500
Wire Wire Line
	6050 2400 6050 2500
Wire Wire Line
	3650 3900 3650 4050
Connection ~ 3650 4000
Wire Wire Line
	3650 3550 3650 3600
Wire Wire Line
	3650 4250 3650 4350
Wire Wire Line
	3150 4350 3150 4000
Wire Wire Line
	6650 4400 6750 4400
Wire Wire Line
	6750 4400 6750 4500
Wire Wire Line
	6750 4500 7400 4500
Wire Wire Line
	7200 4700 7200 4800
Connection ~ 7200 4500
Wire Wire Line
	4850 3400 4850 3500
Wire Wire Line
	4850 3400 4500 3400
Wire Wire Line
	4500 3400 4500 3100
Wire Wire Line
	4500 2800 4500 2900
Wire Wire Line
	4850 3200 4850 2800
Wire Wire Line
	4850 2800 4500 2800
Wire Wire Line
	5850 2150 5850 2500
Wire Wire Line
	5850 2250 5550 2250
Wire Wire Line
	5550 2250 5550 2500
Wire Wire Line
	6650 3300 6950 3300
Connection ~ 5850 2250
Wire Wire Line
	5650 5400 5650 5650
Wire Wire Line
	5250 2500 5250 2400
Wire Wire Line
	5750 2500 5750 1800
Wire Wire Line
	5750 1800 5900 1800
Wire Wire Line
	5900 1800 5900 1450
Wire Wire Line
	5900 1550 5800 1550
Wire Wire Line
	5650 2500 5650 1950
Wire Wire Line
	5650 1950 5400 1950
Wire Wire Line
	5400 1950 5400 1450
Wire Wire Line
	5400 1550 5500 1550
$Comp
L GND #PWR015
U 1 1 62ADFE89
P 5650 1800
F 0 "#PWR015" H 5650 1550 50  0001 C CNN
F 1 "GND" H 5650 1650 50  0000 C CNN
F 2 "" H 5650 1800 50  0001 C CNN
F 3 "" H 5650 1800 50  0001 C CNN
	1    5650 1800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 62ADFF0A
P 5650 1250
F 0 "#PWR016" H 5650 1000 50  0001 C CNN
F 1 "GND" H 5650 1100 50  0000 C CNN
F 2 "" H 5650 1250 50  0001 C CNN
F 3 "" H 5650 1250 50  0001 C CNN
	1    5650 1250
	-1   0    0    1   
$EndComp
Wire Wire Line
	5650 1250 5650 1350
Wire Wire Line
	5650 1800 5650 1750
$Comp
L C_Small C216
U 1 1 62AE05B0
P 5900 1350
F 0 "C216" H 5910 1420 50  0000 L CNN
F 1 "22pf" H 5910 1270 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 5900 1350 50  0001 C CNN
F 3 "" H 5900 1350 50  0001 C CNN
F 4 "187-CL05C220JB5NNND" H 5900 1350 60  0001 C CNN "Mouser Part Number"
	1    5900 1350
	1    0    0    -1  
$EndComp
$Comp
L C_Small C215
U 1 1 62AE061F
P 5400 1350
F 0 "C215" H 5410 1420 50  0000 L CNN
F 1 "22pf" H 5410 1270 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 5400 1350 50  0001 C CNN
F 3 "" H 5400 1350 50  0001 C CNN
F 4 "187-CL05C220JB5NNND" H 5400 1350 60  0001 C CNN "Mouser Part Number"
	1    5400 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 1250 5900 1250
Connection ~ 5650 1250
Connection ~ 5900 1550
Connection ~ 5400 1550
$Comp
L R R202
U 1 1 62AE0E64
P 4950 2000
F 0 "R202" V 5030 2000 50  0000 C CNN
F 1 "20K" V 4950 2000 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 4880 2000 50  0001 C CNN
F 3 "" H 4950 2000 50  0001 C CNN
F 4 "791-RMC10K203FTH " V 4950 2000 60  0001 C CNN "Mouser Part Number"
	1    4950 2000
	0    1    1    0   
$EndComp
$Comp
L C_Small C214
U 1 1 62AE0ED0
P 4950 2150
F 0 "C214" H 4960 2220 50  0000 L CNN
F 1 "3nf" H 4960 2070 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 4950 2150 50  0001 C CNN
F 3 "" H 4950 2150 50  0001 C CNN
F 4 "81-GRM1557U1A302JA1D" H 4950 2150 60  0001 C CNN "Mouser Part Number"
	1    4950 2150
	0    1    1    0   
$EndComp
$Comp
L C_Small C213
U 1 1 62AE0F24
P 4550 2100
F 0 "C213" H 4560 2170 50  0000 L CNN
F 1 "10nf" H 4560 2020 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 4550 2100 50  0001 C CNN
F 3 "" H 4550 2100 50  0001 C CNN
F 4 "81-GRM155R61E103KA1D" H 4550 2100 60  0001 C CNN "Mouser Part Number"
	1    4550 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 2000 5450 2500
Wire Wire Line
	5100 2000 5450 2000
Wire Wire Line
	5050 2150 5150 2150
Wire Wire Line
	5150 2150 5150 2000
Connection ~ 5150 2000
Wire Wire Line
	4550 2000 4800 2000
Wire Wire Line
	4850 2150 4750 2150
Wire Wire Line
	4750 2000 4750 2200
Connection ~ 4750 2000
Wire Wire Line
	5350 2200 5350 2500
Wire Wire Line
	4750 2200 5350 2200
Connection ~ 4750 2150
$Comp
L GND #PWR017
U 1 1 62AE1348
P 4550 2300
F 0 "#PWR017" H 4550 2050 50  0001 C CNN
F 1 "GND" H 4550 2150 50  0000 C CNN
F 2 "" H 4550 2300 50  0001 C CNN
F 3 "" H 4550 2300 50  0001 C CNN
	1    4550 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 2200 4550 2300
$Comp
L C_Small C201
U 1 1 62AE1EFE
P 1800 2750
F 0 "C201" H 1810 2820 50  0000 L CNN
F 1 "10uf" H 1810 2670 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 1800 2750 50  0001 C CNN
F 3 "" H 1800 2750 50  0001 C CNN
F 4 "187-CL21A106MQFNNNE" H 1800 2750 60  0001 C CNN "Mouser Part Number"
	1    1800 2750
	1    0    0    -1  
$EndComp
$Comp
L C_Small C202
U 1 1 62AE1F43
P 2050 2750
F 0 "C202" H 2060 2820 50  0000 L CNN
F 1 "10uf" H 2060 2670 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 2050 2750 50  0001 C CNN
F 3 "" H 2050 2750 50  0001 C CNN
F 4 "187-CL21A106MQFNNNE" H 2050 2750 60  0001 C CNN "Mouser Part Number"
	1    2050 2750
	1    0    0    -1  
$EndComp
$Comp
L C_Small C203
U 1 1 62AE1F8A
P 2300 2750
F 0 "C203" H 2310 2820 50  0000 L CNN
F 1 "1uf" H 2310 2670 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 2300 2750 50  0001 C CNN
F 3 "" H 2300 2750 50  0001 C CNN
F 4 "80-C0402C101K8RAUTO" H 2300 2750 60  0001 C CNN "Mouser Part Number"
	1    2300 2750
	1    0    0    -1  
$EndComp
$Comp
L C_Small C205
U 1 1 62AE1FC9
P 2550 2750
F 0 "C205" H 2560 2820 50  0000 L CNN
F 1 "100nf" H 2560 2670 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 2550 2750 50  0001 C CNN
F 3 "" H 2550 2750 50  0001 C CNN
F 4 "710-885012105001" H 2550 2750 60  0001 C CNN "Mouser Part Number"
	1    2550 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 2650 2550 2650
Connection ~ 2300 2650
Connection ~ 2050 2650
Wire Wire Line
	1800 2850 2550 2850
Connection ~ 2300 2850
Connection ~ 2050 2850
$Comp
L GND #PWR018
U 1 1 62AE22DB
P 2550 3000
F 0 "#PWR018" H 2550 2750 50  0001 C CNN
F 1 "GND" H 2550 2850 50  0000 C CNN
F 2 "" H 2550 3000 50  0001 C CNN
F 3 "" H 2550 3000 50  0001 C CNN
	1    2550 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 2850 2550 3000
Text Label 1800 2650 0    60   ~ 0
VDD3P3
$Comp
L C_Small C204
U 1 1 62AE27E3
P 2350 2050
F 0 "C204" H 2360 2120 50  0000 L CNN
F 1 "100nf" H 2360 1970 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 2350 2050 50  0001 C CNN
F 3 "" H 2350 2050 50  0001 C CNN
F 4 "710-885012105001" H 2350 2050 60  0001 C CNN "Mouser Part Number"
	1    2350 2050
	1    0    0    -1  
$EndComp
$Comp
L C_Small C206
U 1 1 62AE282C
P 2950 2050
F 0 "C206" H 2960 2120 50  0000 L CNN
F 1 "1uf" H 2960 1970 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 2950 2050 50  0001 C CNN
F 3 "" H 2950 2050 50  0001 C CNN
F 4 "80-C0402C101K8RAUTO" H 2950 2050 60  0001 C CNN "Mouser Part Number"
	1    2950 2050
	1    0    0    -1  
$EndComp
$Comp
L C_Small C207
U 1 1 62AE2871
P 3150 2050
F 0 "C207" H 3160 2120 50  0000 L CNN
F 1 "100pf" H 3160 1970 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 3150 2050 50  0001 C CNN
F 3 "" H 3150 2050 50  0001 C CNN
F 4 "80-C0402C101K3RAUTO" H 3150 2050 60  0001 C CNN "Mouser Part Number"
	1    3150 2050
	1    0    0    -1  
$EndComp
$Comp
L C_Small C208
U 1 1 62AE28D1
P 3600 2050
F 0 "C208" H 3610 2120 50  0000 L CNN
F 1 "100nf" H 3610 1970 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 3600 2050 50  0001 C CNN
F 3 "" H 3600 2050 50  0001 C CNN
F 4 "710-885012105001" H 3600 2050 60  0001 C CNN "Mouser Part Number"
	1    3600 2050
	1    0    0    -1  
$EndComp
$Comp
L C_Small C210
U 1 1 62AE291A
P 3950 2050
F 0 "C210" H 3960 2120 50  0000 L CNN
F 1 "100nf" H 3960 1970 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 3950 2050 50  0001 C CNN
F 3 "" H 3950 2050 50  0001 C CNN
F 4 "710-885012105001" H 3950 2050 60  0001 C CNN "Mouser Part Number"
	1    3950 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 1950 3950 1950
Connection ~ 3600 1950
Connection ~ 3150 1950
Connection ~ 2950 1950
Wire Wire Line
	2350 2150 3950 2150
Connection ~ 3600 2150
Connection ~ 3150 2150
Connection ~ 2950 2150
$Comp
L +3.3V #PWR019
U 1 1 62AE2D8F
P 2350 1850
F 0 "#PWR019" H 2350 1700 50  0001 C CNN
F 1 "+3.3V" H 2350 1990 50  0000 C CNN
F 2 "" H 2350 1850 50  0001 C CNN
F 3 "" H 2350 1850 50  0001 C CNN
	1    2350 1850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 62AE2DD9
P 2350 2250
F 0 "#PWR020" H 2350 2000 50  0001 C CNN
F 1 "GND" H 2350 2100 50  0000 C CNN
F 2 "" H 2350 2250 50  0001 C CNN
F 3 "" H 2350 2250 50  0001 C CNN
	1    2350 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 1850 2350 1950
Wire Wire Line
	2350 2250 2350 2150
Text Notes 1800 3000 0    60   ~ 0
Pins 3,4
Text Notes 2350 2250 0    60   ~ 0
Pin 1
Text Notes 2950 2250 0    60   ~ 0
Pins 43, 46
Text Notes 3600 2250 0    60   ~ 0
Pin 19
Text Notes 4000 2250 0    60   ~ 0
Pin 37
Text HLabel 6650 3600 2    60   Output ~ 0
CAN_TX
Text HLabel 6150 5400 3    60   Input ~ 0
CAN_RX
Text HLabel 6250 2500 1    60   Input ~ 0
SCL
Text HLabel 5950 2500 1    60   BiDi ~ 0
SDA
Text HLabel 6650 3200 2    60   Output ~ 0
GPIO19(LEDS3)
Text HLabel 6650 3400 2    60   Output ~ 0
GPIO23(LEDS4)
Text HLabel 6650 3500 2    60   Output ~ 0
GPIO18(LEDS2)
Text HLabel 6650 4300 2    60   Output ~ 0
GPIO17(LEDS1)
Text HLabel 6650 4500 2    60   Input ~ 0
GPIO16(Buttons4)
Text HLabel 6050 5400 3    60   Input ~ 0
GPIO0(Buttons1)
Text HLabel 4850 3800 0    60   Input ~ 0
GPIO38(Buttons2)
Text HLabel 5350 5400 3    60   Input ~ 0
GPIO27(Points4)
Text HLabel 5250 5400 3    60   Output ~ 0
GPIO26(Motor2)
Text HLabel 4850 4500 0    60   Output ~ 0
GPIO25(Motor1)
Text HLabel 4850 4100 0    60   Input ~ 0
GPIO34(OD1)
Text HLabel 4850 4200 0    60   Input ~ 0
GPIO35(OD2)
Text HLabel 4850 3600 0    60   Input ~ 0
GPIO36(OD3)
Text HLabel 4850 3900 0    60   Input ~ 0
GPIO39(OD4)
Text HLabel 4850 4300 0    60   Output ~ 0
GPIO32(Motor3)
Text HLabel 4850 4400 0    60   Output ~ 0
GPIO33(Motor4)
Text HLabel 5550 5400 3    60   Input ~ 0
GPIO12(Points1)
Text HLabel 5750 5400 3    60   Input ~ 0
GPIO13(Points2)
Text HLabel 5450 5400 3    60   Input ~ 0
GPIO14(Points3)
Text HLabel 4850 3700 0    60   Input ~ 0
GPIO37(Buttons3)
Wire Wire Line
	3650 4350 3150 4350
$Comp
L R R203
U 1 1 62AF751C
P 5950 1900
F 0 "R203" V 6030 1900 50  0000 C CNN
F 1 "2.4K" V 5950 1900 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 5880 1900 50  0001 C CNN
F 3 "" H 5950 1900 50  0001 C CNN
F 4 "71-CRCW06032K40JNEAC" V 5950 1900 60  0001 C CNN "Mouser Part Number"
	1    5950 1900
	1    0    0    -1  
$EndComp
$Comp
L R R206
U 1 1 62AF7569
P 6250 1900
F 0 "R206" V 6330 1900 50  0000 C CNN
F 1 "2.4K" V 6250 1900 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 6180 1900 50  0001 C CNN
F 3 "" H 6250 1900 50  0001 C CNN
F 4 "71-CRCW06032K40JNEAC" V 6250 1900 60  0001 C CNN "Mouser Part Number"
	1    6250 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 2050 6250 2500
Wire Wire Line
	5950 2050 5950 2500
Wire Wire Line
	5950 1750 6250 1750
$Comp
L +3.3V #PWR021
U 1 1 62AF7843
P 6250 1600
F 0 "#PWR021" H 6250 1450 50  0001 C CNN
F 1 "+3.3V" H 6250 1740 50  0000 C CNN
F 2 "" H 6250 1600 50  0001 C CNN
F 3 "" H 6250 1600 50  0001 C CNN
	1    6250 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 1750 6250 1600
NoConn ~ 4850 3300
Text Label 3850 3150 0    60   ~ 0
GPIO15(Act1)
Text Label 3450 3150 2    60   ~ 0
GPIO2(Act2)
$Comp
L LED D2
U 1 1 62B4BF99
P 3850 3000
F 0 "D2" H 3850 3100 50  0000 C CNN
F 1 "ACT1" H 3850 2900 50  0000 C CNN
F 2 "LEDs:LED_0402" H 3850 3000 50  0001 C CNN
F 3 "" H 3850 3000 50  0001 C CNN
F 4 "710-150040GS73220" H 3850 3000 60  0001 C CNN "Mouser Part Number"
	1    3850 3000
	0    -1   -1   0   
$EndComp
$Comp
L LED D1
U 1 1 62B4C0B5
P 3450 3000
F 0 "D1" H 3450 3100 50  0000 C CNN
F 1 "ACT2" H 3450 2900 50  0000 C CNN
F 2 "LEDs:LED_0402" H 3450 3000 50  0001 C CNN
F 3 "" H 3450 3000 50  0001 C CNN
F 4 "710-150040SS73220" H 3450 3000 60  0001 C CNN "Mouser Part Number"
	1    3450 3000
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 62B4C14F
P 3850 2650
F 0 "R2" V 3930 2650 50  0000 C CNN
F 1 "270" V 3850 2650 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 3780 2650 50  0001 C CNN
F 3 "" H 3850 2650 50  0001 C CNN
F 4 "754-RR0510P-271D" V 3850 2650 60  0001 C CNN "Mouser Part Number"
	1    3850 2650
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 62B4C210
P 3450 2650
F 0 "R1" V 3530 2650 50  0000 C CNN
F 1 "270" V 3450 2650 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 3380 2650 50  0001 C CNN
F 3 "" H 3450 2650 50  0001 C CNN
F 4 "754-RR0510P-271D" V 3450 2650 60  0001 C CNN "Mouser Part Number"
	1    3450 2650
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR022
U 1 1 62B4C263
P 3650 2400
F 0 "#PWR022" H 3650 2250 50  0001 C CNN
F 1 "+3.3V" H 3650 2540 50  0000 C CNN
F 2 "" H 3650 2400 50  0001 C CNN
F 3 "" H 3650 2400 50  0001 C CNN
	1    3650 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 2500 3450 2500
Wire Wire Line
	3650 2400 3650 2500
Connection ~ 3650 2500
Wire Wire Line
	3850 2800 3850 2850
Wire Wire Line
	3450 2800 3450 2850
Text Label 5950 5400 3    60   ~ 0
GPIO2(Act2)
Text Label 5850 5400 3    60   ~ 0
GPIO15(Act1)
$EndSCHEMATC
