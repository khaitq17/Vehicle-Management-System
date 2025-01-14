#ifndef I2C_H
#define I2C_H

#include "stm32f10x_i2c.h"

typedef enum {
    Error = 0,
    Success = !Error
} Status;

void I2C_Config(void);
Status I2C_Write(uint8_t Address, const uint8_t *pData, uint8_t length);
Status I2C_Read(uint8_t Address, uint8_t *pData, uint8_t length);

#endif
