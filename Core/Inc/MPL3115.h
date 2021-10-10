#ifndef __MPL3115_H
#define __MPL3115_H

#include "stm32l4xx_hal.h"

#define MPL3115_I2C_ADDR (0xC0)

#define MPL3115_CTRL_REG1 (0x26)
#define MPL3115_PT_DATA_CFG (0x13)

#define MPL3115_STATUS (0x00)

#define MPL3115_OUT_P_MSB (0x01)
#define MPL3115_OUT_P_CSB (0x02)
#define MPL3115_OUT_P_LSB (0x03)

#define MPL3115_OUT_T_MSB (0x04)
#define MPL3115_OUT_T_LSB (0x05)


typedef enum {
	SBYS_DISABLED = 0b0,
	SBYS_Enabled = 0b1
}SBYS_Type;

typedef enum {
	OST_DISABLED = 0b0,
	OST_Enabled = 0b1
} OST_Type;

typedef enum {
	RST_DISABLED = 0b0,
	RST_Enabled = 0b1
} RST_Type;

typedef enum {
	OS_Ratio_1 = 0b000,
	OS_Ratio_2 = 0b001,
	OS_Ratio_4 = 0b010,
	OS_Ratio_8 = 0b011,
	OS_Ratio_16 = 0b100,
	OS_Ratio_32 = 0b101,
	OS_Ratio_64 = 0b110,
	OS_Ratio_128 = 0b111
} OS_Type;

typedef enum {
	Res = 0b0
} Res_Type;
typedef enum {
	ALT_DISABLED = 0b0,
	ALT_Enabled = 0b1
} ALT_Type;

typedef union
{
	struct
	{
		SBYS_Type SBYS :1;
		OST_Type OST:1;
		RST_Type AZEN :1;
		OS_Type OS :3;
		Res_Type Res :1;
		ALT_Type ALT :1;
	};
	uint8_t byte;
} MPL3115_REG_CTRL1_VALUE;

typedef struct
{
	I2C_HandleTypeDef * i2cHandle;

	float temperature;
	float pressure;

} MPL3115;

uint8_t MPL3115_Initialise (MPL3115 * dev, I2C_HandleTypeDef * i2cHandle);

HAL_StatusTypeDef MPL3115_ReadTemperature (MPL3115 * dev);
HAL_StatusTypeDef MPL3115_ReadPressure (MPL3115 * dev);

HAL_StatusTypeDef MPL3115_ReadRegister (MPL3115 * dev, uint8_t reg, uint8_t * data);
HAL_StatusTypeDef MPL3115_ReadRegisters (MPL3115 * dev, uint8_t reg, uint8_t * data, uint8_t len);

HAL_StatusTypeDef MPL3115_WriteRegister (MPL3115 * dev, uint8_t reg, uint8_t * data);

#endif
