#include <MAG3110.h>

uint8_t MAG3310_Initialise(I2C_HandleTypeDef * i2cHandle)
{
	uint8_t status, settings;

	HAL_I2C_Mem_Read(i2cHandle, MAG3110_I2C_ADDR, MAG3110_WHO_I_AM, I2C_MEMADD_SIZE_8BIT, &status, sizeof(status), HAL_MAX_DELAY);

	if(MAG3110_I_AM != status)
	{
		while(1)
		{

		}
	}

	settings = 0x80;
	HAL_I2C_Mem_Write(i2cHandle, MAG3110_I2C_ADDR, 0x11, I2C_MEMADD_SIZE_8BIT, &settings, sizeof(settings), HAL_MAX_DELAY);
	settings = 0x01;
	HAL_I2C_Mem_Write(i2cHandle, MAG3110_I2C_ADDR, 0x10, I2C_MEMADD_SIZE_8BIT, &settings, sizeof(settings), HAL_MAX_DELAY);

	return status;
}

int read_x(I2C_HandleTypeDef * i2cHandle)
{
	int x;
	uint8_t status;

	HAL_I2C_Mem_Read(i2cHandle, MAG3110_I2C_ADDR, 0x01, I2C_MEMADD_SIZE_8BIT, &status, sizeof(status), HAL_MAX_DELAY);
	x = (status << 8);
	HAL_I2C_Mem_Read(i2cHandle, MAG3110_I2C_ADDR, 0x02, I2C_MEMADD_SIZE_8BIT, &status, sizeof(status), HAL_MAX_DELAY);
	x |= status;

	return x;
}

int read_y(I2C_HandleTypeDef * i2cHandle)
{
	int y = 0;
	uint8_t status;

	HAL_I2C_Mem_Read(i2cHandle, MAG3110_I2C_ADDR, 0x03, I2C_MEMADD_SIZE_8BIT, &status, sizeof(status), HAL_MAX_DELAY);
	y = (status << 8);
	HAL_I2C_Mem_Read(i2cHandle, MAG3110_I2C_ADDR, 0x04, I2C_MEMADD_SIZE_8BIT, &status, sizeof(status), HAL_MAX_DELAY);
	y |= status;

	return y;
}

int read_z(I2C_HandleTypeDef * i2cHandle)
{
	int z = 0;
	uint8_t status;

	HAL_I2C_Mem_Read(i2cHandle, MAG3110_I2C_ADDR, 0x05, I2C_MEMADD_SIZE_8BIT, &status, sizeof(status), HAL_MAX_DELAY);
	z = (status << 8);
	HAL_I2C_Mem_Read(i2cHandle, MAG3110_I2C_ADDR, 0x06, I2C_MEMADD_SIZE_8BIT, &status, sizeof(status), HAL_MAX_DELAY);
	z |= status;

	return z;
}
