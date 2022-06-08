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

 * 	MCP23_17.h
 *  Created on: 12 jan 2021
 */

#ifndef INC_MCP23017_H_
#define INC_MCP23017_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "I2C_Master/MyI2C.h"
//============================================================================================
#ifndef MCP23017_ADDRESS
#define MCP23017_ADDRESS		(uint8_t)0x40
#endif
//	registers map	============================================================================
#define MCP23017_IODIRA 	(uint8_t)0x00
#define MCP23017_IODIRB 	(uint8_t)0x01
#define MCP23017_IPOLA 		(uint8_t)0x02
#define MCP23017_IPOLB 		(uint8_t)0x03
#define MCP23017_GPINTENA (uint8_t)0x04
#define MCP23017_GPINTENB (uint8_t)0x05
#define MCP23017_DEFVALA 	(uint8_t)0x06
#define MCP23017_DEFVALB 	(uint8_t)0x07
#define MCP23017_INTCONA 	(uint8_t)0x08
#define MCP23017_INTCONB 	(uint8_t)0x09
#define MCP23017_IOCONA 	(uint8_t)0x0A
#define MCP23017_IOCONB 	(uint8_t)0x0B
#define MCP23017_GPPUA 		(uint8_t)0x0C
#define MCP23017_GPPUB 		(uint8_t)0x0D
#define MCP23017_INTFA 		(uint8_t)0x0E
#define MCP23017_INTFB 		(uint8_t)0x0F
#define MCP23017_INTCAPA 	(uint8_t)0x10
#define MCP23017_INTCAPB 	(uint8_t)0x11
#define MCP23017_GPIOA 		(uint8_t)0x12
#define MCP23017_GPIOB 		(uint8_t)0x13
#define MCP23017_OLATA		(uint8_t)0x14
#define MCP23017_OLATB		(uint8_t)0x15
// I/O Direction Default state: MCP23017_IODIR_ALL_INPUT	===============================================
#define MCP23017_IODIR_ALL_OUTPUT	(uint8_t)0x00
#define MCP23017_IODIR_ALL_INPUT	(uint8_t)0xFF
#define MCP23017_IODIR_IO0_INPUT	(uint8_t)0x01
#define MCP23017_IODIR_IO1_INPUT	(uint8_t)0x02
#define MCP23017_IODIR_IO2_INPUT	(uint8_t)0x04
#define MCP23017_IODIR_IO3_INPUT	(uint8_t)0x08
#define MCP23017_IODIR_IO4_INPUT	(uint8_t)0x10
#define MCP23017_IODIR_IO5_INPUT	(uint8_t)0x20
#define MCP23017_IODIR_IO6_INPUT	(uint8_t)0x40
#define MCP23017_IODIR_IO7_INPUT	(uint8_t)0x80
// Input Polarity Default state: MCP23017_IPOL_ALL_NORMAL	==============================================
#define MCP23017_IPOL_ALL_NORMAL		(uint8_t)0x00
#define MCP23017_IPOL_ALL_INVERTED	(uint8_t)0xFF
#define MCP23017_IPOL_IO0_INVERTED	(uint8_t)0x01
#define MCP23017_IPOL_IO1_INVERTED	(uint8_t)0x02
#define MCP23017_IPOL_IO2_INVERTED	(uint8_t)0x04
#define MCP23017_IPOL_IO3_INVERTED	(uint8_t)0x08
#define MCP23017_IPOL_IO4_INVERTED	(uint8_t)0x10
#define MCP23017_IPOL_IO5_INVERTED	(uint8_t)0x20
#define MCP23017_IPOL_IO6_INVERTED	(uint8_t)0x40
#define MCP23017_IPOL_IO7_INVERTED	(uint8_t)0x80
// Pull-Up Resistor Default state: MCP23017_GPPU_ALL_DISABLED	=========================================
#define MCP23017_GPPU_ALL_DISABLED	(uint8_t)0x00
#define MCP23017_GPPU_ALL_ENABLED		(uint8_t)0xFF
#define MCP23017_GPPU_IO0_ENABLED		(uint8_t)0x01
#define MCP23017_GPPU_IO1_ENABLED		(uint8_t)0x02
#define MCP23017_GPPU_IO2_ENABLED		(uint8_t)0x04
#define MCP23017_GPPU_IO3_ENABLED		(uint8_t)0x08
#define MCP23017_GPPU_IO4_ENABLED		(uint8_t)0x10
#define MCP23017_GPPU_IO5_ENABLED		(uint8_t)0x20
#define MCP23017_GPPU_IO6_ENABLED		(uint8_t)0x40
#define MCP23017_GPPU_IO7_ENABLED		(uint8_t)0x80
//	Bit definition pins for PORT A	================================================
#define MCP23017_GPA0		(uint8_t)0x01
#define MCP23017_GPA1		(uint8_t)0x02
#define MCP23017_GPA2		(uint8_t)0x04
#define MCP23_17_GPA3		(uint8_t)0x08
#define MCP23017_GPA4		(uint8_t)0x10
#define MCP23017_GPA5		(uint8_t)0x20
#define MCP23017_GPA6		(uint8_t)0x40 
#define MCP23017_GPA7		(uint8_t)0x80
//	Bit definition pins for PORT B	================================================
#define MCP23017_GPB0		(uint8_t)0x01
#define MCP23017_GPB1		(uint8_t)0x02
#define MCP23017_GPB2		(uint8_t)0x04
#define MCP23_17_GPB3		(uint8_t)0x08
#define MCP23017_GPB4		(uint8_t)0x10
#define MCP23017_GPB5		(uint8_t)0x20
#define MCP23017_GPB6		(uint8_t)0x40 
#define MCP23017_GPB7		(uint8_t)0x80
//======================================================================
#define MCP23017_CFG_LENGHT		(uint8_t)22
#define MCP23017_PORT_LENGHT	(uint8_t)1
//=======================================================================
typedef struct MCP23_port_type_t {
		uint8_t portA;
		uint8_t portB;
} MCP23_port_type;

/* состояние процесса обмена данными с устройством как с отдельным элементом сети
 * 	применяется для отображения состояния процесса работы с устройством для главного кода
 */
typedef enum MCP_status_t {//состояние устройства
	MCP_Init,		//устройство не настроено
	MCP_OK,		//устройство готово к опросу
	MCP_Faulth	//устройство неисправно
} MCP_status;

/*	состояние обмена данными с устройством, использовать для завершения функции работы с устройством */
typedef enum MCP_Connect_Status_t {
	MCP_Connect_Processing, //выполняется работа с устройством: обмен данными, обработка результатов
	MCP_Connect_Complite	//работа с устройством завершена, данные считаны/записаны корректно
} MCP_Connect_Status;

typedef struct MCP23_type_t {
		uint8_t addr;
		uint8_t step;
		MCP_status status;
		MCP23_port_type data;
} MCP23_type;
//function	==================================================================
MCP_Connect_Status MCP23_17_Init(I2C_Connection *_i2c, MCP23_type *dev, uint8_t *pbuffer);
MCP_Connect_Status MCP23_17_ReadPortA(I2C_Connection *_i2c, MCP23_type *dev, uint8_t *pbuffer);
MCP_Connect_Status MCP23_17_ReadPortB(I2C_Connection *_i2c, MCP23_type *dev, uint8_t *pbuffer);
MCP_Connect_Status MCP23_17_WritePortA(I2C_Connection *_i2c, MCP23_type *dev, uint8_t *pbuffer, uint8_t value);
MCP_Connect_Status MCP23_17_WritePortB(I2C_Connection *_i2c, MCP23_type *dev, uint8_t *pbuffer, uint8_t value);

#ifdef __cplusplus
}
#endif

#endif /* INC_MCP23_17_H_ */
