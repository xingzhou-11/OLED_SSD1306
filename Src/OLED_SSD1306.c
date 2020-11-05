#include "OLED_SSD1306.h"
#include "ASCII.h"

uint8_t Init_Data[] = {
	0xAE, 0x00, 0x10, 0x40, 0xB0, 0x81, 0xA1, 0xA4,
	0xA6, 0xA8, 0x3F, 0xC8, 0xD3, 0x00, 0xD5, 0x80, 
	0xD9, 0xDA, 0x12, 0xDB, 0x30, 0x8D, 0x10, 0xAF
	};

//向OLED进行写命令操作
void OLED_Write_Order(uint8_t Order)
{
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x00, I2C_MEMADD_SIZE_8BIT, &Order, 1, 0x100);
}

//向OLED进行写数据操作
void OLED_Write_Data(uint8_t Data)
{
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x40, I2C_MEMADD_SIZE_8BIT, &Data, 1, 0x100);
}

//OLED初始化
void OLED_Init()
{	
	for(uint8_t i=0; i<24; i++)
	{
		HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x00, I2C_MEMADD_SIZE_8BIT, Init_Data+i, 1, 0x100);
		HAL_Delay(100);
	}
}

//清屏
void OLED_clear(void)
{
	for(uint8_t i=0; i<8; i++)
	{
		OLED_Write_Order(0xB0+i);
		OLED_Write_Order(0x00);
		OLED_Write_Order(0x10);
		for (uint8_t j=0; j<128; j++)
		{
			OLED_Write_Data(0);
		}
		
	}
}

//打开OLED
//0x8D VCC电源设置
//0x14 DCDC ON
//0xA4 打开整个显示
//0xAF 开启显示
void OLED_open(void)
{
	OLED_Write_Order(0x8D);
	OLED_Write_Order(0x14);
	OLED_Write_Order(0xA4);
	OLED_Write_Order(0xAF);
}

//关闭OLED
void OLED_close(void)
{
	OLED_Write_Order(0x8D);
	OLED_Write_Order(0x10);
	OLED_Write_Order(0xA5);
	OLED_Write_Order(0xAE);
}

//指定位置显示字符
// x		页地址	范围：1 ~ 7
// y		列地址	
// Single	字符
void OLED_Display_Single(uint8_t x, uint8_t y, char Single)
{
	y = y + 2;
	OLED_Write_Order(0xB0 + x);
	OLED_Write_Order(y/16 + 0x10);
	OLED_Write_Order(y%16 + 0x00);
	
	Single = Single - '0';
	for(uint8_t i=0; i<=16; i++)
	{
		OLED_Write_Data( ASCII_8x16[Single][i]);
	}
}

//指定位置显示字符串
// void OLED_Display_String(uint8_t x, uint8_t y, char *pString, uint8_t Lngth)
// {
	
// }