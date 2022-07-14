/*********************************************************************************
   Original author: Alexandr Pochtovy<alex.mail.prime@gmail.com>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 * 	MCP23_17.c
 *  Created on: 12 jan 2021
 */

#include "MCP23_17.h"

uint8_t MCP23_17_Init(I2C_Connection *_i2c, MCP23_t *dev) {
	if (_i2c->status == PORT_FREE) {
		switch (dev->step) {
		case 0:
			dev->status = INIT;
			_i2c->addr = dev->addr;
			_i2c->reg = MCP23017_IODIRA;
			_i2c->len = MCP23017_CFG_LENGHT;
			_i2c->mode = I2C_MODE_WRITE;
			uint8_t cfg[] = {
					MCP23017_IODIR_ALL_INPUT,	//reg 0x00 IODIRA 	RW set all pins portA as output
					MCP23017_IODIR_ALL_OUTPUT,	//reg 0x01 IODIRB 	RW set all pins portB as input
					MCP23017_IPOL_ALL_NORMAL,	//reg 0x02 IPOLA 		RW set all pins portA normal polarity
					MCP23017_IPOL_ALL_NORMAL,	//reg 0x03 IPOLB		RW set all pins portB normal polarity
					0x00,	//reg 0x04 GPINTENA	RW disable interrupts for all pins portA
					0x00,	//reg 0x05 GPINTENA	RW disable interrupts for all pins portB
					0x00,	//reg 0x06 DEFVALA	RW default value of port A pins
					0x00,	//reg 0x07 DEFVALB	RW default value of port B pins
					0x00,	//reg 0x08 INTCONA	RW compare value for interrupt port A
					0x00,	//reg 0x09 INTCONB	RW compare value for interrupt port B
					0x00,	//reg 0x0A IOCONA		RW setup byte
					0x00,	//reg 0x0B IOCONB		RW setup byte
					0xFF,	//reg 0x0C GPPUA		RW setup pull-up port A pins disabled for output
					0x00,	//reg 0x0D GPPUB		RW setup pull-up port B pins enabled for input
					0x00,	//reg 0x0E INTFA		R interrupt flag register port A
					0x00,	//reg 0x0F INTFB		R interrupt flag register port B
					0x00,	//reg 0x10 INTCAPA	R interrupt flag register port A
					0x00,	//reg 0x11 INTCAPB	R interrupt flag register port B
					0x00,	//reg 0x12 GPIOA		RW main port data register port A
					0x00,	//reg 0x13 GPIOB		RW main port data register port B
					0x00,	//reg 0x14 OLATA		RW output port data register port A
					0x00,	//reg 0x15 OLATB		RW output port data register port B;
			};
			PutMulti(&_i2c->buffer, cfg, sizeof(cfg));
			dev->step = 1;
			I2C_Start_IRQ(_i2c);
			break;
		case 1:
			dev->status = OK;
			dev->step=0;
			return 1;
			break;
		default:
			dev->step = 0;
			break;
		}
	}
	return 0;
}

uint8_t MCP23_17_ReadPortA(I2C_Connection *_i2c, MCP23_t *dev) {
	if (_i2c->status == PORT_FREE) {
		switch (dev->step) {
		case 0:
			_i2c->addr = dev->addr;
			_i2c->mode = I2C_MODE_READ;
			_i2c->reg = MCP23017_GPIOA;
			_i2c->len = MCP23017_PORT_LENGHT;
			dev->step = 1;
			I2C_Start_IRQ(_i2c);
			break;
		case 1:
			GetOne(&_i2c->buffer, &dev->data.portA);
			dev->status = OK;
			dev->step = 0;
			return 1;
			break;
		default:
			dev->step = 0;
			break;
		}
	}
	return 0;
}

uint8_t MCP23_17_WritePortA(I2C_Connection *_i2c, MCP23_t *dev, uint8_t value) {
	if (_i2c->status == PORT_FREE) {
		switch (dev->step) {
		case 0:
			_i2c->addr = dev->addr;
			_i2c->reg = MCP23017_OLATA;
			_i2c->len = MCP23017_PORT_LENGHT;
			_i2c->mode = I2C_MODE_WRITE;
			PutOne(&_i2c->buffer, value);
			dev->step = 1;
			I2C_Start_IRQ(_i2c);
			break;
		case 1:
			dev->status = OK;
			dev->step = 0;
			return 1;
		default:
			dev->step = 0;
			break;
		}
	}
	return 0;
}

uint8_t MCP23_17_ReadPortB(I2C_Connection *_i2c, MCP23_t *dev) {
	if (_i2c->status == PORT_FREE) {
		switch (dev->step) {
		case 0:
			_i2c->addr = dev->addr;
			_i2c->mode = I2C_MODE_READ;
			_i2c->reg = MCP23017_GPIOB;
			_i2c->len = MCP23017_PORT_LENGHT;
			dev->step = 1;
			I2C_Start_IRQ(_i2c);
			break;
		case 1:
			GetOne(&_i2c->buffer, &dev->data.portB);
			dev->status = OK;
			dev->step = 0;
			return 1;
			break;
		default:
			dev->step = 0;
			break;
		}
	}
	return 0;
}

uint8_t MCP23_17_WritePortB(I2C_Connection *_i2c, MCP23_t *dev, uint8_t value) {
	if (_i2c->status == PORT_FREE) {
		switch (dev->step) {
		case 0:
			_i2c->addr = dev->addr;
			_i2c->reg = MCP23017_OLATB;
			_i2c->len = MCP23017_PORT_LENGHT;
			_i2c->mode = I2C_MODE_WRITE;
			PutOne(&_i2c->buffer, value);
			dev->step = 1;
			I2C_Start_IRQ(_i2c);
			break;
		case 1:
			dev->status = OK;
			dev->step = 0;
			return 1;
		default:
			dev->step = 0;
			break;
		}
	}
	return 0;
}
