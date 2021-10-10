#include <MPL3115.h>

uint8_t MPL3115_Initialise(MPL3115 * dev, I2C_HandleTypeDef * i2cHandle)
{
	uint8_t status, settings;

	dev -> i2cHandle = i2cHandle;

	MPL3115_REG_CTRL1_VALUE REGISTER_CONTROL_1 =
	{
			.SBYS = SBYS_Enabled,
			.OST = OST_DISABLED,
			.AZEN = RST_DISABLED,
			.OS = OS_Ratio_128,
			.Res = Res,
			.ALT = ALT_DISABLED
	};

	status = MPL3115_WriteRegister (dev, MPL3115_CTRL_REG1, &REGISTER_CONTROL_1.byte);

	settings = 0x07;
	status = MPL3115_WriteRegister (dev, MPL3115_PT_DATA_CFG, &settings);

	status = MPL3115_WriteRegister (dev, MPL3115_CTRL_REG1, &REGISTER_CONTROL_1.byte);

	return status;
}

HAL_StatusTypeDef MPL3115_ReadTemperature(MPL3115 * dev)
{
	enum{OUT_T_MSB, OUT_T_LSB};
	uint8_t OUT_T[2], status;
	int16_t t;

	status = MPL3115_ReadRegisters (dev, MPL3115_OUT_T_MSB, OUT_T, sizeof(OUT_T));

	t = OUT_T[OUT_T_MSB];

	t <<= 8;
	t |= OUT_T[OUT_T_LSB];
	t >>= 4;

	if (t & 0x800)
	{
		t |= 0xF000;
	}

	float temp = t;
	temp /= 16.0;

	dev -> temperature = temp;

	return status;
}

HAL_StatusTypeDef MPL3115_ReadPressure(MPL3115 * dev)
{
	enum{OUT_P_MSB, OUT_P_CSB, OUT_P_LSB};
	uint8_t OUT_P[3], status;
	uint32_t pressure;

	status = MPL3115_ReadRegisters (dev, MPL3115_OUT_P_MSB, OUT_P, sizeof(OUT_P));

	pressure = OUT_P[OUT_P_MSB];
	pressure <<= 8;
	pressure |= OUT_P[OUT_P_CSB];
	pressure <<= 8;
	pressure |= OUT_P[OUT_P_LSB];
	pressure >>= 4;

	float baro = (pressure / 4.0);
	baro = baro / 100;
	dev -> pressure = baro;

	return status;
}

HAL_StatusTypeDef MPL3115_ReadRegister(MPL3115 * dev, uint8_t reg, uint8_t * data)
{
	return HAL_I2C_Mem_Read(dev -> i2cHandle, MPL3115_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef MPL3115_ReadRegisters(MPL3115 * dev, uint8_t reg, uint8_t * data, uint8_t len)
{
	return HAL_I2C_Mem_Read(dev -> i2cHandle, MPL3115_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}

HAL_StatusTypeDef MPL3115_WriteRegister(MPL3115 * dev, uint8_t reg, uint8_t * data)
{
	return HAL_I2C_Mem_Write(dev -> i2cHandle, MPL3115_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}
