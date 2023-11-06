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
LIBS:ESP32-S3
LIBS:ESP32-T7S3-MultiFunctionUniversalTurnout-cache
LIBS:ESP32-T7S3-MultiFunctionUniversalTurnout-rescue
LIBS:USBLC6-2SC6
LIBS:esp32_s3_wroom
LIBS:gct_usb4105
LIBS:ESP32_mini
LIBS:ap63205
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 7
Title "ESP32 S3 Multifunction Board Universal Turnout"
Date ""
Rev "1.0"
Comp "Deepwoods Software"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L +3.3V #PWR04
U 1 1 62ADE9FC
P 4000 2500
F 0 "#PWR04" H 4000 2350 50  0001 C CNN
F 1 "+3.3V" H 4000 2640 50  0000 C CNN
F 2 "" H 4000 2500 50  0001 C CNN
F 3 "" H 4000 2500 50  0001 C CNN
	1    4000 2500
	1    0    0    -1  
$EndComp
Text HLabel 8425 2800 0    60   Output ~ 0
CAN_TX
Text HLabel 8425 2700 0    60   Input ~ 0
CAN_RX
Text HLabel 3350 4000 0    60   Input ~ 0
SCL
Text HLabel 3950 3900 0    60   BiDi ~ 0
SDA
Text HLabel 9475 3150 2    60   Output ~ 0
GPIO21(LEDS3)
Text HLabel 9475 4000 2    60   Output ~ 0
GPIO1(LEDS4)
Text HLabel 8425 3600 0    60   Output ~ 0
GPIO18(LEDS2)
Text HLabel 8425 3700 0    60   Output ~ 0
GPIO17(LEDS1)
Text HLabel 8425 4800 0    60   Input ~ 0
GPIO16(Buttons4)
Text HLabel 8425 3800 0    60   Input ~ 0
GPIO38(Buttons1)
Text HLabel 9475 3800 2    60   Input ~ 0
GPIO6(Buttons2)
Text HLabel 8425 3000 0    60   Input ~ 0
GPIO10(Points4)
Text HLabel 9475 3500 2    60   Output ~ 0
GPIO11(Motor2)
Text HLabel 8425 2900 0    60   Output ~ 0
GPIO9(Motor1)
Text HLabel 9475 3600 2    60   Input ~ 0
GPIO44/TXD(OD1)
Text HLabel 8425 4300 0    60   Input ~ 0
GPIO48(OD2)
Text HLabel 8425 4000 0    60   Input ~ 0
GPIO45(OD3)
Text HLabel 9475 3900 2    60   Input ~ 0
GPIO7(OD4)
Text HLabel 8425 4600 0    60   Output ~ 0
GPIO8(Motor3)
Text HLabel 9475 3700 2    60   Output ~ 0
GPIO43/RXD(Motor4)
Text HLabel 8425 4700 0    60   Input ~ 0
GPIO12(Points1)
Text HLabel 8425 4400 0    60   Input ~ 0
GPIO13(Points2)
Text HLabel 8425 4500 0    60   Input ~ 0
GPIO14(Points3)
Text HLabel 8425 3900 0    60   Input ~ 0
GPIO46(Buttons3)
$Comp
L R R203
U 1 1 62AF751C
P 4050 3750
F 0 "R203" V 4130 3750 50  0000 C CNN
F 1 "2.4K" V 4050 3750 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 3980 3750 50  0001 C CNN
F 3 "" H 4050 3750 50  0001 C CNN
F 4 "71-RC0402FR-072K4L" V 4050 3750 60  0001 C CNN "Mouser Part Number"
	1    4050 3750
	1    0    0    -1  
$EndComp
$Comp
L R R206
U 1 1 62AF7569
P 3600 3850
F 0 "R206" V 3680 3850 50  0000 C CNN
F 1 "2.4K" V 3600 3850 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 3530 3850 50  0001 C CNN
F 3 "" H 3600 3850 50  0001 C CNN
F 4 "71-RC0402FR-072K4L" V 3600 3850 60  0001 C CNN "Mouser Part Number"
	1    3600 3850
	-1   0    0    1   
$EndComp
Text Label 3850 3150 3    60   ~ 0
GPIO15(Act1)
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
Text Label 8425 4200 2    60   ~ 0
GPIO15(Act1)
$Comp
L R R3
U 1 1 63051DF1
P 4150 2650
F 0 "R3" V 4230 2650 50  0000 C CNN
F 1 "270" V 4150 2650 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 4080 2650 50  0001 C CNN
F 3 "" H 4150 2650 50  0001 C CNN
F 4 "754-RR0510P-271D" V 4150 2650 60  0001 C CNN "Mouser Part Number"
	1    4150 2650
	1    0    0    -1  
$EndComp
$Comp
L LED D4
U 1 1 63051FA7
P 4150 3000
F 0 "D4" H 4150 3100 50  0000 C CNN
F 1 "ACT2" H 4150 2900 50  0000 C CNN
F 2 "LEDs:LED_0402" H 4150 3000 50  0001 C CNN
F 3 "" H 4150 3000 50  0001 C CNN
F 4 "710-150040SS73220" H 4150 3000 60  0001 C CNN "Mouser Part Number"
	1    4150 3000
	0    -1   -1   0   
$EndComp
Text Label 4150 3150 3    60   ~ 0
GPIO0(Act2)
Text Label 8425 2500 2    60   ~ 0
GPIO0(Act2)
$Comp
L +3.3V #PWR05
U 1 1 63E6C883
P 3650 3575
F 0 "#PWR05" H 3650 3425 50  0001 C CNN
F 1 "+3.3V" H 3650 3715 50  0000 C CNN
F 2 "" H 3650 3575 50  0001 C CNN
F 3 "" H 3650 3575 50  0001 C CNN
	1    3650 3575
	1    0    0    -1  
$EndComp
$Comp
L TTGO-T7_S3-V1.1 U201
U 1 1 63E6D166
P 8925 2400
F 0 "U201" H 9200 450 50  0000 C CNN
F 1 "TTGO-T7_S3-V1.1" H 9025 -275 50  0000 C CNN
F 2 "ESP32_mini:ESP32_mini" H 9075 2500 50  0001 C CNN
F 3 "" H 9075 2500 50  0001 C CNN
	1    8925 2400
	1    0    0    -1  
$EndComp
Text Label 4150 3900 0    60   ~ 0
GPIO2/SDA
Text Label 3875 4000 0    60   ~ 0
GPIO3/SCL
Text Label 8425 2600 2    60   ~ 0
GPIO2/SDA
Text Label 8425 4900 2    60   ~ 0
GPIO3/SCL
$Comp
L +5V #PWR06
U 1 1 63E738C3
P 9600 2375
F 0 "#PWR06" H 9600 2225 50  0001 C CNN
F 1 "+5V" H 9600 2515 50  0000 C CNN
F 2 "" H 9600 2375 50  0001 C CNN
F 3 "" H 9600 2375 50  0001 C CNN
	1    9600 2375
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR07
U 1 1 63E738FB
P 9925 2500
F 0 "#PWR07" H 9925 2350 50  0001 C CNN
F 1 "+3V3" H 9925 2640 50  0000 C CNN
F 2 "" H 9925 2500 50  0001 C CNN
F 3 "" H 9925 2500 50  0001 C CNN
	1    9925 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 63E73935
P 9600 2900
F 0 "#PWR08" H 9600 2650 50  0001 C CNN
F 1 "GND" H 9600 2750 50  0000 C CNN
F 2 "" H 9600 2900 50  0001 C CNN
F 3 "" H 9600 2900 50  0001 C CNN
	1    9600 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 2800 3850 2850
Wire Wire Line
	3600 3700 3600 3600
Wire Wire Line
	3600 3600 4050 3600
Connection ~ 4050 3900
Connection ~ 3600 4000
Wire Wire Line
	4150 2800 4150 2850
Wire Wire Line
	3850 2500 4150 2500
Connection ~ 4000 2500
Wire Wire Line
	3650 3575 3650 3600
Connection ~ 3650 3600
Wire Wire Line
	3950 3900 4150 3900
Wire Wire Line
	3350 4000 3875 4000
Wire Wire Line
	9600 2375 9600 2500
Wire Wire Line
	9600 2500 9475 2500
Wire Wire Line
	9475 2600 9925 2600
Wire Wire Line
	9925 2600 9925 2500
Wire Wire Line
	9475 2900 9600 2900
Wire Wire Line
	9475 2700 9475 2900
Connection ~ 9475 2800
$EndSCHEMATC
