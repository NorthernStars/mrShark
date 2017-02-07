mrShark
=======

Mixed-Reality Robot Firmware

Install Instructions
====================
Import project from git into Eclipse.
Compile it using the AVR plugin for Eclipse or with avr-gcc.
Use included scripts to set fuses and programm microcontroller or use AVR plugin.

Configuration
=============
You can configure the firmware inside headers/config.h in projects source folder.

Build Level
-----------
Normally the firmware is build with maximum available functions. This requires the most resources (currently ~7,6kB flash and 0,53kB RAM). You can uncomment the defines CFG_CODE_LEVEL_AVG or CFG_CODE_LEVEL_MIN to disable some functions. With that the firmware maybe will fit onto smaller microcontrollers.

Marker
------
If you don't use a LED-Marker you can comment out the define CFG_EXTERNAL_MARKER to disable LED-Marker functions. But this saves only a few bytes of flash and RAM.

BOT-ID
------
Although you can set the robtos ID via IR-interface, you can also configre it using the define CFG_BOT_ID.
Hint: It's not recommended to change the ID via programming the robot.

Other Things
------------
You can set the define CFG_SHOW_CONTROL_TRAFFIC to TRUE to show the transmission activity of the infrared interface on the status LED.
You can also comment out the defines CFG_SUART_TX and CFG_SUART_RX to disable software UART interface. Be aware that the debug interface uses the software UART. So we recommend not to change this.

config.h define details
-----------------------
General options can be used to configure the robots main behaviour

| Define 							| Default Value | Comment |
| --------------------------------- | ------------- | ------- |
| CFG_CODE_LEVEL_AVG				| disabled		| uncomment to disable rgb-leds, motor fault functions and monitoring. Only basic debugging interface |
| CFG_CODE_LEVEL_MIN				| disabled		| uncomment to also disbale debugging interface |
| |
| CFG_BOT_ID						| 0 			| robot ID, use IR prototcol to manipulate it | 
| CFG_SHOW_CONTROL_TRAFFIC			| FALSE 		| set TRUE to show IR traffic activity on green status LED |
| CFG_SUART_TX						| enabled		| uncomment to enable software uart tx |
| CFG_SUART_RX						| enabled		| uncomment to enable software uart rx |
| 
| CFG_EXTERNAL_MARKER				| enabled		| uncomment to enable external marker pcb |
| CFG_EXTERNAL_MARKER_POSITION_LED	| enabled		| uncomment to enable external marker position leds |
|  |


Power saving options
| Define 							| Default Value | Comment |
| --------------------------------- | ------------- | ------- |
| CFG_POWER_DOWN_I2C				| FALSE 		| set TRUE to disable I²C/TWI interface |
| CFG_POWER_DOWN_TIMER0				| FALSE 		| set TRUE to disable internal timer 0 |
| CFG_POWER_DOWN_TIMER1				| FALSE 		| set TRUE to disbale internal timer 1 |
| CFG_POWER_DOWN_TIMER2				| FALSE 		| set TRUE to disable internal timer 2 |
| CFG_POWER_DOWN_SPI				| TRUE 			| set TRUE to disbale SPI interface |
| CFG_POWER_DOWN_UART				| FALSE 		| set TRUE to disable UART interface |
| CFG_POWER_DOWN_ADC				| TRUE 			| set TRUE to disable internal ADC |

Boot Process
============
After switching on the mrShark, it will initiate all needed systems. The first thing you'll see is that the robots rgb LED turns into red. After that a motor test is performed and the robot drives foreward and backward while the rgb LEDs are orange. If the robot is booted successfully, it's lighted up green for some seconds.

If you use the LED marker, the boot process is animated using the marker leds. If booting is done, the robot shows it's ID on the LED marker (using a hamming code).
