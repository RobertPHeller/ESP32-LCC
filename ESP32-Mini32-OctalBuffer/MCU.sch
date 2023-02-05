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
LIBS:ESP32_mini
LIBS:ap63205
LIBS:tbd62x83a
LIBS:ESP32-Mini32-OctalBuffer-cache
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
L TTGO-T7_S3-V1.1 U201
U 1 1 63E00230
P 5225 3075
F 0 "U201" H 5500 1125 50  0000 C CNN
F 1 "TTGO-T7_S3-V1.1" H 5325 400 50  0000 C CNN
F 2 "ESP32_mini:ESP32_mini" H 5375 3175 50  0001 C CNN
F 3 "" H 5375 3175 50  0001 C CNN
	1    5225 3075
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR04
U 1 1 63E00378
P 5875 3175
F 0 "#PWR04" H 5875 3025 50  0001 C CNN
F 1 "+5V" H 5875 3315 50  0000 C CNN
F 2 "" H 5875 3175 50  0001 C CNN
F 3 "" H 5875 3175 50  0001 C CNN
	1    5875 3175
	1    0    0    -1  
$EndComp
Wire Wire Line
	5775 3175 5875 3175
$Comp
L +3V3 #PWR05
U 1 1 63E00399
P 6000 3275
F 0 "#PWR05" H 6000 3125 50  0001 C CNN
F 1 "+3V3" H 6000 3415 50  0000 C CNN
F 2 "" H 6000 3275 50  0001 C CNN
F 3 "" H 6000 3275 50  0001 C CNN
	1    6000 3275
	1    0    0    -1  
$EndComp
Wire Wire Line
	5775 3275 6000 3275
$Comp
L GND #PWR06
U 1 1 63E003B3
P 6225 3575
F 0 "#PWR06" H 6225 3325 50  0001 C CNN
F 1 "GND" H 6225 3425 50  0000 C CNN
F 2 "" H 6225 3575 50  0001 C CNN
F 3 "" H 6225 3575 50  0001 C CNN
	1    6225 3575
	1    0    0    -1  
$EndComp
Wire Wire Line
	6225 3575 5775 3575
Wire Wire Line
	5775 3475 6225 3475
Wire Wire Line
	6225 3375 6225 3575
Wire Wire Line
	5775 3375 6225 3375
Connection ~ 6225 3475
Text HLabel 5775 4175 2    60   Output ~ 0
GPIO11/Buffer1
Text HLabel 4725 5375 0    60   Output ~ 0
GPIO12/Buffer2
Text HLabel 4725 5075 0    60   Output ~ 0
GPIO13/Buffer3
Text HLabel 4725 5175 0    60   Output ~ 0
GPIO14/Buffer4
Text HLabel 4725 4875 0    60   Output ~ 0
GPIO15/Buffer5
Text HLabel 4725 5475 0    60   Output ~ 0
GPIO16/Buffer6
Text HLabel 4725 4375 0    60   Output ~ 0
GPIO17/Buffer7
Text HLabel 4725 4275 0    60   Output ~ 0
GPIO18/Buffer8
Text HLabel 4725 3375 0    60   Input ~ 0
CAN_RX
Text HLabel 4725 3475 0    60   Output ~ 0
CAN_TX
$EndSCHEMATC
