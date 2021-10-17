#ifndef INC_MAG3110_H_
#define INC_MAG3110_H_

#include "stm32l4xx_hal.h"

#define MAG3110_I2C_ADDR (0x1C)

#define MAG3110_WHO_I_AM (0x07)
#define MAG3110_I_AM (0xC4)

uint8_t MAG3310_Initialise(I2C_HandleTypeDef * i2cHandle);

#endif
