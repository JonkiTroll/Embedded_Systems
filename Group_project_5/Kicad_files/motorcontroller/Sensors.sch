EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
Title "RC Tank - Sensor connectors"
Date "2021-11-02"
Rev "V0.1"
Comp "Reykjavik university"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_01x03 J4
U 1 1 617E2FE4
P 1100 1550
F 0 "J4" H 1018 1225 50  0000 C CNN
F 1 "Conn_01x03" H 1018 1316 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 1100 1550 50  0001 C CNN
F 3 "~" H 1100 1550 50  0001 C CNN
	1    1100 1550
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J5
U 1 1 617E3BDB
P 1100 2150
F 0 "J5" H 1018 1825 50  0000 C CNN
F 1 "Conn_01x03" H 1018 1916 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 1100 2150 50  0001 C CNN
F 3 "~" H 1100 2150 50  0001 C CNN
	1    1100 2150
	-1   0    0    1   
$EndComp
Text GLabel 1400 1450 2    50   Input ~ 0
Distance_sensor_1_out
Text GLabel 1400 2050 2    50   Input ~ 0
Distance_sensor_2_out
$Comp
L power:GND #PWR0116
U 1 1 617E54BA
P 1500 1550
F 0 "#PWR0116" H 1500 1300 50  0001 C CNN
F 1 "GND" V 1505 1422 50  0000 R CNN
F 2 "" H 1500 1550 50  0001 C CNN
F 3 "" H 1500 1550 50  0001 C CNN
	1    1500 1550
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 617E59AF
P 1500 2150
F 0 "#PWR0117" H 1500 1900 50  0001 C CNN
F 1 "GND" V 1505 2022 50  0000 R CNN
F 2 "" H 1500 2150 50  0001 C CNN
F 3 "" H 1500 2150 50  0001 C CNN
	1    1500 2150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1500 2150 1300 2150
Wire Wire Line
	1400 2050 1300 2050
Wire Wire Line
	1500 2250 1300 2250
Wire Wire Line
	1500 1550 1300 1550
Wire Wire Line
	1400 1450 1300 1450
Wire Notes Line
	500  2650 2450 2650
Text Notes 500  600  0    50   ~ 0
Distance sensors - Flying fish MH-sensor series\n
Wire Notes Line
	2450 4200 500  4200
Wire Notes Line
	2450 500  2450 4200
Text Notes 550  2800 0    50   ~ 0
Inertial measurement unit - ICM20948
Wire Wire Line
	1500 1650 1300 1650
$Comp
L power:+3V3 #PWR0114
U 1 1 618FAFAD
P 1500 1650
F 0 "#PWR0114" H 1500 1500 50  0001 C CNN
F 1 "+3V3" V 1515 1778 50  0000 L CNN
F 2 "" H 1500 1650 50  0001 C CNN
F 3 "" H 1500 1650 50  0001 C CNN
	1    1500 1650
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR0115
U 1 1 618FBA1B
P 1500 2250
F 0 "#PWR0115" H 1500 2100 50  0001 C CNN
F 1 "+3V3" V 1515 2378 50  0000 L CNN
F 2 "" H 1500 2250 50  0001 C CNN
F 3 "" H 1500 2250 50  0001 C CNN
	1    1500 2250
	0    1    1    0   
$EndComp
$EndSCHEMATC
