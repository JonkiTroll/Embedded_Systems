EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 3
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
L Connector:Raspberry_Pi_2_3 J1
U 1 1 617BBBFE
P 3100 5250
F 0 "J1" H 2559 6731 50  0000 C CNN
F 1 "Raspberry_Pi_2_3" H 2392 6640 50  0000 C CNN
F 2 "Module:Raspberry_Pi_Zero_Socketed_THT_FaceDown_MountingHoles" H 3100 5250 50  0001 C CNN
F 3 "https://www.raspberrypi.org/documentation/hardware/raspberrypi/schematics/rpi_SCH_3bplus_1p0_reduced.pdf" H 3100 5250 50  0001 C CNN
	1    3100 5250
	1    0    0    -1  
$EndComp
$Comp
L MCU_Module:Arduino_Nano_Every J2
U 1 1 617BD8CB
P 6650 2500
F 0 "J2" H 6299 1411 50  0000 C CNN
F 1 "Arduino_Nano_Every" H 6103 1320 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 6650 2500 50  0001 C CIN
F 3 "https://content.arduino.cc/assets/NANOEveryV3.0_sch.pdf" H 6650 2500 50  0001 C CNN
	1    6650 2500
	1    0    0    -1  
$EndComp
$Sheet
S 6750 4700 1200 1050
U 617C40A3
F0 "Sensors" 50
F1 "Sensors.sch" 50
$EndSheet
$Sheet
S 8750 4700 1200 1050
U 617C4343
F0 "Motor&Power" 50
F1 "Motor&Power.sch" 50
$EndSheet
$Comp
L power:GND #PWR0101
U 1 1 617CFA4A
P 6650 3600
F 0 "#PWR0101" H 6650 3350 50  0001 C CNN
F 1 "GND" H 6655 3427 50  0000 C CNN
F 2 "" H 6650 3600 50  0001 C CNN
F 3 "" H 6650 3600 50  0001 C CNN
	1    6650 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 617D6462
P 9100 3650
F 0 "#PWR0102" H 9100 3400 50  0001 C CNN
F 1 "GND" H 9105 3477 50  0000 C CNN
F 2 "" H 9100 3650 50  0001 C CNN
F 3 "" H 9100 3650 50  0001 C CNN
	1    9100 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 3500 6650 3600
Wire Wire Line
	9100 3500 9100 3650
$Comp
L Simulation_SPICE:DIODE D3
U 1 1 617ED91B
P 6000 1400
F 0 "D3" V 6046 1320 50  0000 R CNN
F 1 "DIODE" V 5955 1320 50  0000 R CNN
F 2 "Diode_THT:D_A-405_P10.16mm_Horizontal" H 6000 1400 50  0001 C CNN
F 3 "~" H 6000 1400 50  0001 C CNN
F 4 "Y" H 6000 1400 50  0001 L CNN "Spice_Netlist_Enabled"
F 5 "D" H 6000 1400 50  0001 L CNN "Spice_Primitive"
	1    6000 1400
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 617FB7F9
P 6550 1450
F 0 "#PWR0103" H 6550 1300 50  0001 C CNN
F 1 "+5V" H 6565 1623 50  0000 C CNN
F 2 "" H 6550 1450 50  0001 C CNN
F 3 "" H 6550 1450 50  0001 C CNN
	1    6550 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 1700 8600 1700
Wire Wire Line
	8500 1550 8500 1700
Wire Wire Line
	8400 1800 8600 1800
Wire Wire Line
	8400 1200 8400 1800
Wire Wire Line
	6000 1700 6150 1700
Wire Wire Line
	6000 1550 6000 1700
Wire Wire Line
	5900 1800 6150 1800
$Comp
L power:+5V #PWR0104
U 1 1 61802F8C
P 9000 1450
F 0 "#PWR0104" H 9000 1300 50  0001 C CNN
F 1 "+5V" H 9015 1623 50  0000 C CNN
F 2 "" H 9000 1450 50  0001 C CNN
F 3 "" H 9000 1450 50  0001 C CNN
	1    9000 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 4350 2300 4350
$Comp
L USER:Logic_Level_Shifter U1
U 1 1 617AEF73
P 4000 1550
F 0 "U1" H 4000 1975 50  0000 C CNN
F 1 "Logic_Level_Shifter" H 4000 1884 50  0000 C CNN
F 2 "USER:Logic_level_converter_breakout" H 4000 2000 50  0001 C CNN
F 3 "" H 4000 2000 50  0001 C CNN
	1    4000 1550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 617BE070
P 2900 1700
F 0 "#PWR0105" H 2900 1450 50  0001 C CNN
F 1 "GND" H 2905 1527 50  0000 C CNN
F 2 "" H 2900 1700 50  0001 C CNN
F 3 "" H 2900 1700 50  0001 C CNN
	1    2900 1700
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0106
U 1 1 617BEE2D
P 2900 1450
F 0 "#PWR0106" H 2900 1300 50  0001 C CNN
F 1 "+3V3" H 2915 1623 50  0000 C CNN
F 2 "" H 2900 1450 50  0001 C CNN
F 3 "" H 2900 1450 50  0001 C CNN
	1    2900 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 1450 2900 1550
Wire Wire Line
	2900 1550 3650 1550
Wire Wire Line
	3650 1650 2900 1650
Wire Wire Line
	2900 1650 2900 1700
$Comp
L power:+5V #PWR0108
U 1 1 617C137D
P 5000 1450
F 0 "#PWR0108" H 5000 1300 50  0001 C CNN
F 1 "+5V" H 5015 1623 50  0000 C CNN
F 2 "" H 5000 1450 50  0001 C CNN
F 3 "" H 5000 1450 50  0001 C CNN
	1    5000 1450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0109
U 1 1 617C5BFF
P 2900 3800
F 0 "#PWR0109" H 2900 3650 50  0001 C CNN
F 1 "+5V" H 2915 3973 50  0000 C CNN
F 2 "" H 2900 3800 50  0001 C CNN
F 3 "" H 2900 3800 50  0001 C CNN
	1    2900 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 3800 2900 3900
Wire Wire Line
	3000 3950 3000 3900
Wire Wire Line
	3000 3900 2900 3900
Connection ~ 2900 3900
Wire Wire Line
	2900 3900 2900 3950
$Comp
L power:+3V3 #PWR0110
U 1 1 617C789D
P 3200 3800
F 0 "#PWR0110" H 3200 3650 50  0001 C CNN
F 1 "+3V3" H 3215 3973 50  0000 C CNN
F 2 "" H 3200 3800 50  0001 C CNN
F 3 "" H 3200 3800 50  0001 C CNN
	1    3200 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 3800 3200 3900
$Comp
L power:GND #PWR0111
U 1 1 617C9647
P 2700 6750
F 0 "#PWR0111" H 2700 6500 50  0001 C CNN
F 1 "GND" H 2705 6577 50  0000 C CNN
F 2 "" H 2700 6750 50  0001 C CNN
F 3 "" H 2700 6750 50  0001 C CNN
	1    2700 6750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 6550 2700 6700
Wire Wire Line
	3400 6550 3400 6700
Wire Wire Line
	3400 6700 3300 6700
Connection ~ 2700 6700
Wire Wire Line
	2700 6700 2700 6750
Wire Wire Line
	2800 6550 2800 6700
Connection ~ 2800 6700
Wire Wire Line
	2800 6700 2700 6700
Wire Wire Line
	2900 6550 2900 6700
Connection ~ 2900 6700
Wire Wire Line
	2900 6700 2800 6700
Wire Wire Line
	3000 6550 3000 6700
Connection ~ 3000 6700
Wire Wire Line
	3000 6700 2900 6700
Wire Wire Line
	3100 6550 3100 6700
Connection ~ 3100 6700
Wire Wire Line
	3100 6700 3000 6700
Wire Wire Line
	3200 6550 3200 6700
Connection ~ 3200 6700
Wire Wire Line
	3200 6700 3100 6700
Wire Wire Line
	3300 6550 3300 6700
Connection ~ 3300 6700
Wire Wire Line
	3300 6700 3200 6700
Wire Wire Line
	6550 1450 6550 1500
Wire Wire Line
	9000 1450 9000 1500
Text GLabel 6050 3000 0    50   Input ~ 0
PWM_Pin_0_Left
Text GLabel 6050 3100 0    50   Input ~ 0
PWM_Pin_1_Left
Text GLabel 8550 3100 0    50   Input ~ 0
PWM_Pin_0_Right
Text GLabel 8550 3000 0    50   Input ~ 0
PWM_Pin_1_Right
Wire Wire Line
	8550 3100 8600 3100
Wire Wire Line
	8550 3000 8600 3000
$Comp
L MCU_Module:Arduino_Nano_Every J3
U 1 1 617D645C
P 9100 2500
F 0 "J3" H 8749 1411 50  0000 C CNN
F 1 "Arduino_Nano_Every" H 8583 1320 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 9100 2500 50  0001 C CIN
F 3 "https://content.arduino.cc/assets/NANOEveryV3.0_sch.pdf" H 9100 2500 50  0001 C CNN
	1    9100 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 3100 6050 3100
Wire Wire Line
	6150 3000 6050 3000
Text GLabel 8500 1950 0    50   Input ~ 0
Encoder_A_Right
Text GLabel 8500 2050 0    50   Input ~ 0
Encoder_B_Right
Wire Wire Line
	4350 1350 4800 1350
Wire Wire Line
	4900 1200 4900 1450
Wire Wire Line
	4350 1450 4900 1450
Wire Wire Line
	3050 1450 3050 1200
Wire Wire Line
	3050 1200 1750 1200
Wire Wire Line
	1750 1200 1750 4350
Wire Wire Line
	3050 1450 3650 1450
Wire Wire Line
	3150 1350 3150 1100
Wire Wire Line
	3150 1100 1650 1100
Wire Wire Line
	1650 1100 1650 4450
Wire Wire Line
	1650 4450 2300 4450
Wire Wire Line
	3150 1350 3650 1350
$Comp
L Simulation_SPICE:DIODE D5
U 1 1 61841D8B
P 8500 1400
F 0 "D5" V 8546 1320 50  0000 R CNN
F 1 "DIODE" V 8455 1320 50  0000 R CNN
F 2 "Diode_THT:D_A-405_P10.16mm_Horizontal" H 8500 1400 50  0001 C CNN
F 3 "~" H 8500 1400 50  0001 C CNN
F 4 "Y" H 8500 1400 50  0001 L CNN "Spice_Netlist_Enabled"
F 5 "D" H 8500 1400 50  0001 L CNN "Spice_Primitive"
	1    8500 1400
	0    -1   -1   0   
$EndComp
$Comp
L Simulation_SPICE:DIODE D1
U 1 1 61848CB8
P 4600 1750
F 0 "D1" H 4646 1862 50  0000 R CNN
F 1 "DIODE" H 4732 1961 50  0000 R CNN
F 2 "Diode_THT:D_A-405_P10.16mm_Horizontal" H 4600 1750 50  0001 C CNN
F 3 "~" H 4600 1750 50  0001 C CNN
F 4 "Y" H 4600 1750 50  0001 L CNN "Spice_Netlist_Enabled"
F 5 "D" H 4600 1750 50  0001 L CNN "Spice_Primitive"
	1    4600 1750
	-1   0    0    1   
$EndComp
Wire Wire Line
	4450 1750 4350 1750
Text GLabel 4850 1750 2    50   Input ~ 0
FLT
Wire Wire Line
	4850 1750 4750 1750
Text GLabel 3500 1750 0    50   Input ~ 0
FLT_pi
Wire Wire Line
	3650 1750 3500 1750
Text GLabel 2150 5650 0    50   Input ~ 0
FLT_pi
Wire Wire Line
	2300 5650 2150 5650
$Comp
L Switch:SW_DIP_x02 SW1
U 1 1 61880A02
P 5500 1300
F 0 "SW1" H 5500 1667 50  0000 C CNN
F 1 "SW_DIP_x02" H 5500 1576 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_DIP_SPSTx02_Slide_6.7x6.64mm_W6.73mm_P2.54mm_LowProfile_JPin" H 5500 1300 50  0001 C CNN
F 3 "~" H 5500 1300 50  0001 C CNN
	1    5500 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 1200 5100 1200
Wire Wire Line
	5200 1300 5100 1300
Wire Wire Line
	5100 1300 5100 1200
Connection ~ 5100 1200
Wire Wire Line
	5100 1200 5200 1200
Wire Wire Line
	5800 1200 8400 1200
Wire Wire Line
	5800 1300 5900 1300
Wire Wire Line
	5900 1300 5900 1800
Wire Wire Line
	5000 1450 5000 1550
Wire Wire Line
	5000 1550 4350 1550
Wire Wire Line
	4800 900  6000 900 
Wire Wire Line
	6000 900  6000 1250
Connection ~ 6000 900 
Wire Wire Line
	6000 900  8500 900 
Wire Wire Line
	8500 900  8500 1250
Wire Wire Line
	4800 900  4800 1350
Text GLabel 2150 5450 0    50   Input ~ 0
Distance_sensor_1_out
Text GLabel 2150 5550 0    50   Input ~ 0
Distance_sensor_2_out
Wire Wire Line
	2150 5450 2300 5450
Wire Wire Line
	2150 5550 2300 5550
Wire Wire Line
	3300 3950 3300 3900
Wire Wire Line
	3300 3900 3200 3900
Connection ~ 3200 3900
Wire Wire Line
	3200 3900 3200 3950
$Comp
L power:GND #PWR0107
U 1 1 617C0292
P 5150 1700
F 0 "#PWR0107" H 5150 1450 50  0001 C CNN
F 1 "GND" H 5155 1527 50  0000 C CNN
F 2 "" H 5150 1700 50  0001 C CNN
F 3 "" H 5150 1700 50  0001 C CNN
	1    5150 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 1650 5150 1700
Wire Wire Line
	4350 1650 5150 1650
Text GLabel 6050 2050 0    50   Input ~ 0
Encoder_B_Left
Text GLabel 6050 1950 0    50   Input ~ 0
Encoder_A_Left
Wire Wire Line
	6150 2200 6050 2200
Wire Wire Line
	5750 2200 5700 2200
Wire Wire Line
	5300 2200 5300 2300
Wire Wire Line
	5400 2200 5300 2200
$Comp
L power:GND #PWR0112
U 1 1 61891951
P 5300 2300
F 0 "#PWR0112" H 5300 2050 50  0001 C CNN
F 1 "GND" H 5305 2127 50  0000 C CNN
F 2 "" H 5300 2300 50  0001 C CNN
F 3 "" H 5300 2300 50  0001 C CNN
	1    5300 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 61886934
P 5900 2200
F 0 "D2" H 5893 2102 50  0000 C CNN
F 1 "LED" H 5893 2011 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm" H 5900 2200 50  0001 C CNN
F 3 "~" H 5900 2200 50  0001 C CNN
	1    5900 2200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 6188B115
P 5550 2200
F 0 "R1" V 5658 2200 50  0000 C CNN
F 1 "470" V 5749 2200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 5480 2200 50  0001 C CNN
F 3 "~" H 5550 2200 50  0001 C CNN
	1    5550 2200
	0    1    1    0   
$EndComp
Wire Wire Line
	6050 2050 6150 2050
Wire Wire Line
	6150 2050 6150 2100
Wire Wire Line
	6050 1950 6150 1950
Wire Wire Line
	6150 1950 6150 2000
Wire Wire Line
	8600 2200 8500 2200
Wire Wire Line
	8200 2200 8150 2200
Wire Wire Line
	7750 2200 7750 2300
Wire Wire Line
	7850 2200 7750 2200
$Comp
L power:GND #PWR0113
U 1 1 618BFE69
P 7750 2300
F 0 "#PWR0113" H 7750 2050 50  0001 C CNN
F 1 "GND" H 7755 2127 50  0000 C CNN
F 2 "" H 7750 2300 50  0001 C CNN
F 3 "" H 7750 2300 50  0001 C CNN
	1    7750 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D4
U 1 1 618BFE6F
P 8350 2200
F 0 "D4" H 8343 2102 50  0000 C CNN
F 1 "LED" H 8343 2011 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm" H 8350 2200 50  0001 C CNN
F 3 "~" H 8350 2200 50  0001 C CNN
	1    8350 2200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 618BFE75
P 8000 2200
F 0 "R2" V 8108 2200 50  0000 C CNN
F 1 "470" V 8199 2200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7930 2200 50  0001 C CNN
F 3 "~" H 8000 2200 50  0001 C CNN
	1    8000 2200
	0    1    1    0   
$EndComp
Wire Wire Line
	8500 1950 8600 1950
Wire Wire Line
	8600 1950 8600 2000
Wire Wire Line
	8500 2050 8600 2050
Wire Wire Line
	8600 2050 8600 2100
$EndSCHEMATC
