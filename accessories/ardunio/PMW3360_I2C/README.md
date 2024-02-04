# PMW3360 I2C Interface

Implementation of [SunjunKim's PMW3360 library](https://github.com/SunjunKim/PMW3360) to send the data over I2C (acting as an I2C target sending mouse data to the controller).

The code is designed for Arduino style microcontrollers and tested on an Osoyoo ATmega32U4 Pro Micro (5v) (https://osoyoo.com/2018/06/25/osoyoo-pro-micro-board/).

The PMW3360 breakout board used was the JACK Enterprises PMW3360 Motion Sensor board (https://www.tindie.com/products/jkicklighter/pmw3360-motion-sensor/)

## Pin connections

| Pro micro | Moonlander 			|
|===========|=======================|
| SDA (2) 	| SDA (ribbon cable 10) |
| SCL (3) 	| SCL (ribbon cable 9) 	|
| RAW 		| 5v (ribbon cable 16) 	|
| GND		| gnd (ribbon cable 1) 	|

| Pro micro | PMW3360 module		|
|===========|=======================|
| (NONE) 	| RS					|
| GND		| GD					|
| (NONE)	| MT					|
| 10		| SS (Slave select)		|
| 15		| SC (SPI Clock)		|
| 16		| MO (MOSI)				|
| 14		| MI (MISO)				|
| VCC		| VI					|