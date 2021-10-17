#include <MAG3110.h>

uint8_t MAG3310_Initialise(I2C_HandleTypeDef * i2cHandle)
{
	uint8_t status;

	HAL_I2C_Mem_Read(i2cHandle, MAG3110_I2C_ADDR, MAG3110_WHO_I_AM, I2C_MEMADD_SIZE_8BIT, &status, 1, HAL_MAX_DELAY);

	if(MAG3110_I_AM == status)
	{
		while(1)
		{

		}
	}

	return status;
}
