#include "OLED_SSD1306.h"

void OLED_Init()
{
    HAL_GPIO_WritePin(GPIOB, SDA, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, SCL, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, SDA, GPIO_PIN_RESET);

    HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, 0x7A, uint8_t *pData, uint16_t Size, uint32_t Timeout);

}