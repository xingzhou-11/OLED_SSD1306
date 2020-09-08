#include "OLED_SSD1306.h"
#include "ASCII_8X16.h"

uint8_t Init_Data[] = {
	0xAE, 0x00, 0x10, 0x40, 0xB0, 0x81, 0xA1, 0xA6, 
	0xA8, 0x3F, 0xC8, 0xD3, 0x00, 0xD5, 0x80, 0xD9, 
	0xDA, 0x12, 0xDB, 0x30,	0x8D, 0x10, 0xAF
	};

//OLED初始化
void OLED_Init()
{	
	for(uint8_t i=0; i<25; i++)
	{
		HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x00, I2C_MEMADD_SIZE_8BIT, Init_Data+i, 1, 0x100);
		HAL_Delay(100);
	}
}

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

//打开OLED
void OLED_open()
{
	OLED_Write_Order(0xA4);
	OLED_Write_Order(0xAE);
}

//关闭OLED
void OLED_close()
{
	OLED_Write_Order(0xA5);
	OLED_Write_Order(0xAF);
}

//指定位置显示字符
void OLED_Display(uint8_t String)
{
	uint8_t  Data = String - '0';
	for(uint8_t i=0; i<16; i++)
		OLED_Write_Data(ASCII_8_16[Data][i]);
}

//指定位置显示字符串
//Page_Add		页地址
//Column_Add	列地址	范围：00h ~ 1Fh
void OLED_Display_String(uint8_t Page_Add, uint8_t Column_Add, char *pString, uint8_t Lingth)
{
	OLED_Write_Order(0xB0 + Page_Add);
	OLED_Write_Order(0x00);
	OLED_Write_Order(0x10);
	
	for(uint8_t j=0; j<=Lingth; j++)
	{
		OLED_Display( pString[j]);
	}
}