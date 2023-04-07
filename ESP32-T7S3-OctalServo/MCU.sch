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
LIBS:74xgxx
LIBS:ESP32_mini
LIBS:ESP32-T7S3-OctalServo-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
Title "ESP32 S3 Multifunction Board Universal Turnout"
Date ""
Rev "1.0"
Comp "Deepwoods Software"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 8425 2800 0    60   Output ~ 0
CAN_TX
Text HLabel 8425 2700 0    60   Input ~ 0
CAN_RX
$Comp
L TTGO-T7_S3-V1.1 U201
U 1 1 64307086
P 8925 2400
F 0 "U201" H 9200 450 50  0000 C CNN
F 1 "TTGO-T7_S3-V1.1" H 9025 -275 50  0000 C CNN
F 2 "ESP32_mini:ESP32_mini" H 9075 2500 50  0001 C CNN
F 3 "" H 9075 2500 50  0001 C CNN
	1    8925 2400
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR09
U 1 1 64307087
P 9600 2375
F 0 "#PWR09" H 9600 2225 50  0001 C CNN
F 1 "+5V" H 9600 2515 50  0000 C CNN
F 2 "" H 9600 2375 50  0001 C CNN
F 3 "" H 9600 2375 50  0001 C CNN
	1    9600 2375
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR010
U 1 1 64307088
P 9925 2500
F 0 "#PWR010" H 9925 2350 50  0001 C CNN
F 1 "+3V3" H 9925 2640 50  0000 C CNN
F 2 "" H 9925 2500 50  0001 C CNN
F 3 "" H 9925 2500 50  0001 C CNN
	1    9925 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 64307089
P 9600 2900
F 0 "#PWR011" H 9600 2650 50  0001 C CNN
F 1 "GND" H 9600 2750 50  0000 C CNN
F 2 "" H 9600 2900 50  0001 C CNN
F 3 "" H 9600 2900 50  0001 C CNN
	1    9600 2900
	1    0    0    -1  
$EndComp
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
Wire Wire Line
	8425 4900 8425 4900
Text HLabel 9475 3500 2    60   Output ~ 0
Servo0
Text HLabel 8425 4700 0    60   Output ~ 0
Servo1
Text HLabel 8425 4400 0    60   Output ~ 0
Servo2
Text HLabel 8425 4500 0    60   Output ~ 0
Servo3
Text HLabel 8425 4200 0    60   Output ~ 0
Servo4
Text HLabel 8425 4800 0    60   Output ~ 0
Servo5
Text HLabel 8425 3700 0    60   Output ~ 0
Servo6
Text HLabel 8425 3600 0    60   Output ~ 0
Servo7
NoConn ~ 8425 4900
NoConn ~ 8425 4600
NoConn ~ 8425 4300
NoConn ~ 8425 4100
NoConn ~ 8425 4000
NoConn ~ 8425 3900
NoConn ~ 8425 3800
NoConn ~ 8425 3500
NoConn ~ 8425 3400
NoConn ~ 8425 3300
NoConn ~ 8425 2900
NoConn ~ 8425 3000
NoConn ~ 8425 3100
NoConn ~ 8425 3200
NoConn ~ 9475 3000
NoConn ~ 9475 3150
NoConn ~ 9475 3600
NoConn ~ 9475 3700
NoConn ~ 9475 3800
NoConn ~ 9475 3900
NoConn ~ 9475 4000
NoConn ~ 9475 4100
NoConn ~ 8425 2500
NoConn ~ 8425 2600
$EndSCHEMATC
