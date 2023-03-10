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
LIBS:lm2574n-5
LIBS:ESP32-S3
LIBS:USBLC6-2SC6
LIBS:4814p-2
LIBS:tc442x
LIBS:pca9685
LIBS:tbd62x83a
LIBS:mechanical
LIBS:gct_usb4105
LIBS:ESP32-S3-MegaMultiFunction-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 11
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
F2 "CAN_TX" O L 3375 1875 60 
F3 "CAN_RX" I L 3375 2075 60 
F4 "Points1" I R 6725 1900 60 
F5 "Points2" I R 6725 1975 60 
F6 "Points3" I R 6725 2050 60 
F7 "Points4" I R 6725 2125 60 
F8 "Points5" I R 6725 2700 60 
F9 "Points6" I R 6725 2775 60 
F10 "Points7" I R 6725 2850 60 
F11 "Points8" I R 6725 2925 60 
F12 "Motor1" O R 6725 1600 60 
F13 "Motor2" O R 6725 1675 60 
F14 "Motor3" O R 6725 1750 60 
F15 "Motor4" O R 6725 1825 60 
F16 "Motor5" O R 6725 2400 60 
F17 "Motor6" O R 6725 2475 60 
F18 "Motor7" O R 6725 2550 60 
F19 "Motor8" O R 6725 2625 60 
F20 "LED1" O L 3375 2675 60 
F21 "LED2" O L 3375 2750 60 
F22 "LED3" O L 3375 2825 60 
F23 "LED4" O L 3375 2900 60 
F24 "LED5" O L 3375 2975 60 
F25 "LED6" O L 3375 3050 60 
F26 "LED7" O L 3375 3125 60 
F27 "LED8" O L 3375 3200 60 
F28 "OD1" I R 6725 3225 60 
F29 "OD2" I R 6725 3300 60 
F30 "OD3" I R 6725 3375 60 
F31 "OD4" I R 6725 3450 60 
F32 "OD5" I R 6725 3525 60 
F33 "OD6" I R 6725 3600 60 
F34 "OD7" I R 6725 3675 60 
F35 "OD8" I R 6725 3750 60 
F36 "Button1" I L 3375 3550 60 
F37 "Button2" I L 3375 3625 60 
F38 "Button3" I L 3375 3700 60 
F39 "Button4" I L 3375 3775 60 
F40 "Button5" I L 3375 3850 60 
F41 "Button6" I L 3375 3925 60 
F42 "Button7" I L 3375 4000 60 
F43 "Button8" I L 3375 4075 60 
F44 "Line1" B R 6725 3975 60 
F45 "Line2" B R 6725 4050 60 
F46 "Line3" B R 6725 4125 60 
F47 "Line4" B R 6725 4200 60 
F48 "Line5" B R 6725 4275 60 
F49 "Line6" B R 6725 4350 60 
F50 "Line7" B R 6725 4425 60 
F51 "Line8" B R 6725 4500 60 
F52 "SDA" B L 3375 4875 60 
F53 "SCL" O L 3375 4800 60 
$EndSheet
$Sheet
S 625  1475 2225 975 
U 632C7FE7
F0 "CAN Transciver" 60
F1 "CanTransciver.sch" 60
F2 "CAN_TX" I R 2850 1875 60 
F3 "CAN_RX" O R 2850 2075 60 
$EndSheet
$Sheet
S 3325 6675 3200 925 
U 632C8003
F0 "Power Supply" 60
F1 "PowerSupply.sch" 60
$EndSheet
$Sheet
S 6825 1525 1750 650 
U 63438DF9
F0 "Stall Motors 1" 60
F1 "StallMotors1.sch" 60
F2 "Points1" O L 6825 1900 60 
F3 "Points2" O L 6825 1975 60 
F4 "Points3" O L 6825 2050 60 
F5 "Points4" O L 6825 2125 60 
F6 "Motor1" I L 6825 1600 60 
F7 "Motor2" I L 6825 1675 60 
F8 "Motor3" I L 6825 1750 60 
F9 "Motor4" I L 6825 1825 60 
$EndSheet
$Sheet
S 6825 2350 1750 725 
U 63439454
F0 "Stall Motors 2" 60
F1 "StallMotors2.sch" 60
F2 "Points5" O L 6825 2700 60 
F3 "Points6" O L 6825 2775 60 
F4 "Points7" O L 6825 2850 60 
F5 "Points8" O L 6825 2925 60 
F6 "Motor5" I L 6825 2400 60 
F7 "Motor6" I L 6825 2475 60 
F8 "Motor7" I L 6825 2550 60 
F9 "Motor8" I L 6825 2625 60 
$EndSheet
$Sheet
S 650  2600 2600 650 
U 6344EFFD
F0 "LED/Drivers" 60
F1 "LEDDrivers.sch" 60
F2 "LED1" I R 3250 2675 60 
F3 "LED2" I R 3250 2750 60 
F4 "LED3" I R 3250 2825 60 
F5 "LED4" I R 3250 2900 60 
F6 "LED5" I R 3250 2975 60 
F7 "LED6" I R 3250 3050 60 
F8 "LED7" I R 3250 3125 60 
F9 "LED8" I R 3250 3200 60 
$EndSheet
$Sheet
S 650  3425 2625 775 
U 63452970
F0 "Buttons" 60
F1 "Buttons.sch" 60
F2 "Button1" O R 3275 3550 60 
F3 "Button2" O R 3275 3625 60 
F4 "Button3" O R 3275 3700 60 
F5 "Button4" O R 3275 3775 60 
F6 "Button5" O R 3275 3850 60 
F7 "Button6" O R 3275 3925 60 
F8 "Button7" O R 3275 4000 60 
F9 "Button8" O R 3275 4075 60 
$EndSheet
$Sheet
S 6825 3175 1700 625 
U 634539A9
F0 "Occupancy Detectors" 60
F1 "OccupancyDetectors.sch" 60
F2 "OD1" O L 6825 3225 60 
F3 "OD2" O L 6825 3300 60 
F4 "OD3" O L 6825 3375 60 
F5 "OD4" O L 6825 3450 60 
F6 "OD5" O L 6825 3525 60 
F7 "OD6" O L 6825 3600 60 
F8 "OD7" O L 6825 3675 60 
F9 "OD8" O L 6825 3750 60 
$EndSheet
Wire Wire Line
	3375 1875 2850 1875
Wire Wire Line
	2850 2075 3375 2075
Wire Wire Line
	6825 2925 6725 2925
Wire Wire Line
	6825 2850 6725 2850
Wire Wire Line
	6825 2775 6725 2775
Wire Wire Line
	6725 2700 6825 2700
Wire Wire Line
	6825 2625 6725 2625
Wire Wire Line
	6725 2550 6825 2550
Wire Wire Line
	6825 2475 6725 2475
Wire Wire Line
	6725 2400 6825 2400
Wire Wire Line
	6825 2125 6725 2125
Wire Wire Line
	6725 2050 6825 2050
Wire Wire Line
	6825 1975 6725 1975
Wire Wire Line
	6725 1900 6825 1900
Wire Wire Line
	6825 1825 6725 1825
Wire Wire Line
	6725 1750 6825 1750
Wire Wire Line
	6825 1675 6725 1675
Wire Wire Line
	6725 1600 6825 1600
Text Label 6725 3975 0    60   ~ 0
Line1
Text Label 6725 4050 0    60   ~ 0
Line2
Text Label 6725 4125 0    60   ~ 0
Line3
Text Label 6725 4200 0    60   ~ 0
Line4
Text Label 6725 4275 0    60   ~ 0
Line5
Text Label 6725 4350 0    60   ~ 0
Line6
Text Label 6725 4425 0    60   ~ 0
Line7
Text Label 6725 4500 0    60   ~ 0
Line8
Text Label 7850 4725 3    60   ~ 0
Line2
Text Label 7750 4725 3    60   ~ 0
Line4
Text Label 7550 4725 3    60   ~ 0
Line6
Text Label 7450 4725 3    60   ~ 0
Line8
$Comp
L Conn_02x05_Odd_Even J101
U 1 1 63454AF0
P 7650 4525
F 0 "J101" H 7700 4825 50  0000 C CNN
F 1 "Conn_02x05_Odd_Even" H 7700 4225 50  0000 C CNN
F 2 "Connectors:IDC_Header_Straight_10pins" H 7650 4525 50  0001 C CNN
F 3 "" H 7650 4525 50  0001 C CNN
	1    7650 4525
	0    -1   -1   0   
$EndComp
Text Label 7450 4225 1    60   ~ 0
Line7
Text Label 7550 4225 1    60   ~ 0
Line5
Text Label 7750 4225 1    60   ~ 0
Line3
Text Label 7850 4225 1    60   ~ 0
Line1
$Comp
L +3V3 #PWR01
U 1 1 634595B8
P 7650 4225
F 0 "#PWR01" H 7650 4075 50  0001 C CNN
F 1 "+3V3" H 7650 4365 50  0000 C CNN
F 2 "" H 7650 4225 50  0001 C CNN
F 3 "" H 7650 4225 50  0001 C CNN
	1    7650 4225
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 63459772
P 7650 4725
F 0 "#PWR02" H 7650 4475 50  0001 C CNN
F 1 "GND" H 7650 4575 50  0000 C CNN
F 2 "" H 7650 4725 50  0001 C CNN
F 3 "" H 7650 4725 50  0001 C CNN
	1    7650 4725
	1    0    0    -1  
$EndComp
$Sheet
S 650  4425 2075 800 
U 6345B2AE
F0 "Signal Drivers 1" 60
F1 "SignalDrivers1.sch" 60
F2 "SCL" I R 2725 4675 60 
F3 "SDA" B R 2725 4750 60 
$EndSheet
$Sheet
S 650  5425 2125 900 
U 6345D47C
F0 "Signal Drivers 2" 60
F1 "SignalDrivers2.sch" 60
F2 "SCL" I R 2775 5600 60 
F3 "SDA" B R 2775 5675 60 
$EndSheet
Wire Wire Line
	6825 3750 6725 3750
Wire Wire Line
	6725 3675 6825 3675
Wire Wire Line
	6825 3600 6725 3600
Wire Wire Line
	6725 3525 6825 3525
Wire Wire Line
	6825 3450 6725 3450
Wire Wire Line
	6725 3375 6825 3375
Wire Wire Line
	6825 3300 6725 3300
Wire Wire Line
	6725 3225 6825 3225
Wire Wire Line
	3375 2675 3250 2675
Wire Wire Line
	3250 2750 3375 2750
Wire Wire Line
	3375 2825 3250 2825
Wire Wire Line
	3250 2900 3375 2900
Wire Wire Line
	3375 2975 3250 2975
Wire Wire Line
	3250 3050 3375 3050
Wire Wire Line
	3375 3125 3250 3125
Wire Wire Line
	3250 3200 3375 3200
Wire Wire Line
	3375 3550 3275 3550
Wire Wire Line
	3275 3625 3375 3625
Wire Wire Line
	3375 3700 3275 3700
Wire Wire Line
	3275 3775 3375 3775
Wire Wire Line
	3375 3850 3275 3850
Wire Wire Line
	3275 3925 3375 3925
Wire Wire Line
	3375 4000 3275 4000
Wire Wire Line
	3275 4075 3375 4075
Wire Wire Line
	3375 4800 3050 4800
Wire Wire Line
	3050 4675 3050 5600
Wire Wire Line
	3050 4675 2725 4675
Wire Wire Line
	2725 4750 3000 4750
Wire Wire Line
	3000 4750 3000 5675
Wire Wire Line
	3000 4875 3375 4875
Wire Wire Line
	3050 5600 2775 5600
Connection ~ 3050 4800
Wire Wire Line
	3000 5675 2775 5675
Connection ~ 3000 4875
$Comp
L Mounting_Hole MK101
U 1 1 6348304F
P 925 6800
F 0 "MK101" H 925 7000 50  0001 C CNN
F 1 "Mounting_Hole" H 925 6925 50  0001 C CNN
F 2 "Mounting_Holes:MountingHole_3.5mm" H 925 6800 50  0001 C CNN
F 3 "" H 925 6800 50  0001 C CNN
	1    925  6800
	1    0    0    -1  
$EndComp
$Comp
L Mounting_Hole MK102
U 1 1 63483886
P 1300 6850
F 0 "MK102" H 1300 7050 50  0001 C CNN
F 1 "Mounting_Hole" H 1300 6975 50  0001 C CNN
F 2 "Mounting_Holes:MountingHole_3.5mm" H 1300 6850 50  0001 C CNN
F 3 "" H 1300 6850 50  0001 C CNN
	1    1300 6850
	1    0    0    -1  
$EndComp
$Comp
L Mounting_Hole MK103
U 1 1 63483AE0
P 1575 6850
F 0 "MK103" H 1575 7050 50  0001 C CNN
F 1 "Mounting_Hole" H 1575 6975 50  0001 C CNN
F 2 "Mounting_Holes:MountingHole_3.5mm" H 1575 6850 50  0001 C CNN
F 3 "" H 1575 6850 50  0001 C CNN
	1    1575 6850
	1    0    0    -1  
$EndComp
$Comp
L Mounting_Hole MK104
U 1 1 63483D3A
P 1850 6800
F 0 "MK104" H 1850 7000 50  0001 C CNN
F 1 "Mounting_Hole" H 1850 6925 50  0001 C CNN
F 2 "Mounting_Holes:MountingHole_3.5mm" H 1850 6800 50  0001 C CNN
F 3 "" H 1850 6800 50  0001 C CNN
	1    1850 6800
	1    0    0    -1  
$EndComp
$Comp
L Mounting_Hole FD101
U 1 1 63483F94
P 850 7325
F 0 "FD101" H 850 7525 50  0001 C CNN
F 1 "Fiduial" H 850 7450 50  0001 C CNN
F 2 "Fiducials:Fiducial_Modern_SilkscreenTop" H 850 7325 50  0001 C CNN
F 3 "" H 850 7325 50  0001 C CNN
	1    850  7325
	1    0    0    -1  
$EndComp
$Comp
L Mounting_Hole FD102
U 1 1 634847CB
P 1250 7375
F 0 "FD102" H 1250 7575 50  0001 C CNN
F 1 "Fiduial" H 1250 7500 50  0001 C CNN
F 2 "Fiducials:Fiducial_Modern_SilkscreenTop" H 1250 7375 50  0001 C CNN
F 3 "" H 1250 7375 50  0001 C CNN
	1    1250 7375
	1    0    0    -1  
$EndComp
$Comp
L Mounting_Hole FD103
U 1 1 63484A25
P 1675 7400
F 0 "FD103" H 1675 7600 50  0001 C CNN
F 1 "Fiduial" H 1675 7525 50  0001 C CNN
F 2 "Fiducials:Fiducial_Modern_SilkscreenTop" H 1675 7400 50  0001 C CNN
F 3 "" H 1675 7400 50  0001 C CNN
	1    1675 7400
	1    0    0    -1  
$EndComp
$EndSCHEMATC
