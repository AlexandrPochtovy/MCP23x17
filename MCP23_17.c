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

MCP_Connect_Status MCP23_17_Init(I2C_Connection *_i2c, MCP23_type *dev, uint8_t *pbuffer) {
	if (_i2c->i2cStatus == I2C_Bus_Free) {
		switch (dev->step) {
		case 0:
			dev->status = MCP_Init;
			_i2c->addr = dev->addr;
			_i2c->reg = MCP23017_IODIRA;
			_i2c->len = MCP23017_CFG_LENGHT;
			_i2c->mode = I2C_MODE_WRITE;
			_i2c->rxtxp = pbuffer;
			_i2c->rxtxp[0] = MCP23017_IODIR_ALL_INPUT;	//reg 0x00 IODIRA 	RW set all pins portA as output
			_i2c->rxtxp[1] = MCP23017_IODIR_ALL_OUTPUT;	//reg 0x01 IODIRB 	RW set all pins portB as input
			_i2c->rxtxp[2] = MCP23017_IPOL_ALL_NORMAL;	//reg 0x02 IPOLA 		RW set all pins portA normal polarity
			_i2c->rxtxp[3] = MCP23017_IPOL_ALL_NORMAL;	//reg 0x03 IPOLB		RW set all pins portB normal polarity
			_i2c->rxtxp[4] = 0x00;	//reg 0x04 GPINTENA	RW disable interrupts for all pins portA
			_i2c->rxtxp[5] = 0x00;	//reg 0x05 GPINTENA	RW disable interrupts for all pins portB
			_i2c->rxtxp[6] = 0x00;	//reg 0x06 DEFVALA	RW default value of port A pins
			_i2c->rxtxp[7] = 0x00;	//reg 0x07 DEFVALB	RW default value of port B pins
			_i2c->rxtxp[8] = 0x00;	//reg 0x08 INTCONA	RW compare value for interrupt port A
			_i2c->rxtxp[9] = 0x00;	//reg 0x09 INTCONB	RW compare value for interrupt port B
			_i2c->rxtxp[10] = 0x00;	//reg 0x0A IOCONA		RW setup byte
			_i2c->rxtxp[11] = 0x00;	//reg 0x0B IOCONB		RW setup byte
			_i2c->rxtxp[12] = 0xFF;	//reg 0x0C GPPUA		RW setup pull-up port A pins disabled for output
			_i2c->rxtxp[13] = 0x00;	//reg 0x0D GPPUB		RW setup pull-up port B pins enabled for input
			_i2c->rxtxp[14] = 0x00;	//reg 0x0E INTFA		R interrupt flag register port A
			_i2c->rxtxp[15] = 0x00;	//reg 0x0F INTFB		R interrupt flag register port B
			_i2c->rxtxp[16] = 0x00;	//reg 0x10 INTCAPA	R interrupt flag register port A
			_i2c->rxtxp[17] = 0x00;	//reg 0x11 INTCAPB	R interrupt flag register port B
			_i2c->rxtxp[18] = 0x00;	//reg 0x12 GPIOA		RW main port data register port A
			_i2c->rxtxp[19] = 0x00;	//reg 0x13 GPIOB		RW main port data register port B
			_i2c->rxtxp[20] = 0x00;	//reg 0x14 OLATA		RW output port data register port A
			_i2c->rxtxp[21] = 0x00;	//reg 0x15 OLATB		RW output port data register port B;
			dev->step = 1;
			I2C_Start_IRQ(_i2c);

			break;
		case 1:
			dev->status = MCP_OK;
			dev->step=0;
			return MCP_Connect_Complite;
			break;
		default:
			dev->step = 0;
			break;
		}
	}
	return MCP_Connect_Processing;
}

MCP_Connect_Status MCP23_17_ReadPortA(I2C_Connection *_i2c, MCP23_type *dev, uint8_t *pbuffer) {
	if (_i2c->i2cStatus == I2C_Bus_Free) {
		switch (dev->step) {
		case 0:
			_i2c->addr = dev->addr;
			_i2c->mode = I2C_MODE_READ;
			_i2c->rxtxp = pbuffer;
			_i2c->reg = MCP23017_GPIOA;
			_i2c->len = MCP23017_PORT_LENGHT;
			dev->step = 1;
			I2C_Start_IRQ(_i2c);
			break;
		case 1:
			dev->data.portA = _i2c->rxtxp[0];
			dev->status = MCP_OK;
			dev->step = 0;
			return MCP_Connect_Complite;
			break;
		default:
			dev->step = 0;
			break;
		}
	}
	return MCP_Connect_Processing;
}

MCP_Connect_Status MCP23_17_WritePortA(I2C_Connection *_i2c, MCP23_type *dev, uint8_t *pbuffer, uint8_t value) {
	if (_i2c->i2cStatus == I2C_Bus_Free) {
		switch (dev->step) {
		case 0:
			_i2c->addr = dev->addr;
			_i2c->reg = MCP23017_OLATA;
			_i2c->len = MCP23017_PORT_LENGHT;
			_i2c->mode = I2C_MODE_WRITE;
			_i2c->rxtxp = pbuffer;
			*_i2c->rxtxp = value;
			dev->step = 1;
			I2C_Start_IRQ(_i2c);
			break;
		case 1:
			dev->status = MCP_OK;
			dev->step = 0;
			return MCP_Connect_Complite;
		default:
			dev->step = 0;
			break;
		}
	}
	return MCP_Connect_Processing;
}

MCP_Connect_Status MCP23_17_ReadPortB(I2C_Connection *_i2c, MCP23_type *dev, uint8_t *pbuffer) {
	if (_i2c->i2cStatus == I2C_Bus_Free) {
		switch (dev->step) {
		case 0:
			_i2c->addr = dev->addr;
			_i2c->mode = I2C_MODE_READ;
			_i2c->rxtxp = pbuffer;
			_i2c->reg = MCP23017_GPIOB;
			_i2c->len = MCP23017_PORT_LENGHT;
			dev->step = 1;
			I2C_Start_IRQ(_i2c);
			break;
		case 1:
			dev->data.portB = _i2c->rxtxp[0];
			dev->status = MCP_OK;
			dev->step = 0;
			return MCP_Connect_Complite;
			break;
		default:
			dev->step = 0;
			break;
		}
	}
	return MCP_Connect_Processing;
}

MCP_Connect_Status MCP23_17_WritePortB(I2C_Connection *_i2c, MCP23_type *dev, uint8_t *pbuffer, uint8_t value) {
	if (_i2c->i2cStatus == I2C_Bus_Free) {
		switch (dev->step) {
		case 0:
			_i2c->addr = dev->addr;
			_i2c->reg = MCP23017_OLATB;
			_i2c->len = MCP23017_PORT_LENGHT;
			_i2c->mode = I2C_MODE_WRITE;
			_i2c->rxtxp = pbuffer;
			*_i2c->rxtxp = value;
			dev->step = 1;
			I2C_Start_IRQ(_i2c);
			break;
		case 1:
			dev->status = MCP_OK;
			dev->step = 0;
			return MCP_Connect_Complite;
		default:
			dev->step = 0;
			break;
		}
	}
	return MCP_Connect_Processing;
}
