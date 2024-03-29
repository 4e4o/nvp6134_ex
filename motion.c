/********************************************************************************
*
*  Copyright (C) 2017 	NEXTCHIP Inc. All rights reserved.
*  Module		: The decoder's motion detection module
*  Description	: Now, Not used
*  Author		:
*  Date         :
*  Version		: Version 2.0
*
********************************************************************************
*  History      :
*
*
********************************************************************************/
#include <linux/string.h>
#include <linux/delay.h>

#include "common.h"
#include "video.h"
#include "motion.h"

extern unsigned int nvp6134_iic_addr[4];
extern unsigned int nvp6134_cnt;


//0x00+(ch%4)*0x07  bit0 motion onoff						default 0x0D
//0x01+(ch%4)*0x07  motion时域敏感度						default 0x60
//0x02+(ch%4)*0x07  motion空域敏感度						default 0x23
//0x03+(ch%4)*0x07  motion亮度敏感度，值越大越不灵敏		default 0x00
//0x04+(ch%4)*0x07  										default 0x00
//0x05+(ch%4)*0x07  sum_white								default 0xa0
//0x06+(ch%4)*0x07  sum_black								default 0xa0
void nvp6134_motion_init(unsigned char ch, unsigned char onoff)
{
	unsigned char ch_onoff = 0;
	
	gpio_i2c_write(nvp6134_iic_addr[ch/4], 0xFF, 0x02);
	ch_onoff = gpio_i2c_read(nvp6134_iic_addr[ch/4], 0x00+(ch%4)*0x07);
	if(onoff == 1)
	{
		CLE_BIT(ch_onoff, 0);
		gpio_i2c_write(nvp6134_iic_addr[ch/4], 0x00+(ch%4)*0x07, ch_onoff);
	}
	else
	{
		SET_BIT(ch_onoff, 0);
		gpio_i2c_write(nvp6134_iic_addr[ch/4], 0x00+(ch%4)*0x07, ch_onoff);
	}
	
	printk("nvp6134 ch[%d] motion %s setted...\n", ch, onoff==1?"ON":"OFF");
}

//获取发生motion的通道
void nvp6134_get_motion_ch(nvp6134_motion_data* data)
{
	int i;
	u_int8_t read_register = 0xA9;

	// hold mode
	if (data->mode == 1)
		read_register = 0xB1;

	data->motion = 0;

	for(i = 0 ; i < nvp6134_cnt ; i++) {
		gpio_i2c_write(nvp6134_iic_addr[i], 0xFF, 0x00);
		data->motion |= (gpio_i2c_read(nvp6134_iic_addr[i], read_register) & 0x0F) << (4 * i);
	}
}

//打开motion pic显示。现场画面会显示马赛克块，用于调试motion，正常使用时候请关闭.
void nvp6134_motion_set_display(nvp6134_motion_display* data)
{
	unsigned char ch_disp = 0;
	
	gpio_i2c_write(nvp6134_iic_addr[data->ch / 4], 0xFF, 0x02);
	ch_disp = gpio_i2c_read(nvp6134_iic_addr[data->ch / 4], 0x00 + (data->ch % 4) * 0x07);
	if(data->display == 1)
	{
		SET_BIT(ch_disp, 2);
		SET_BIT(ch_disp, 3);
	}
	else
	{
		CLE_BIT(ch_disp, 2);
		CLE_BIT(ch_disp, 3);
	}
	gpio_i2c_write(nvp6134_iic_addr[data->ch / 4], 0x00 + (data->ch % 4) * 0x07, ch_disp);
}

void nvp6134_motion_sensitivity(nvp6134_motion_sens *sens)
{
	//0x01+(ch%4)*0x07  motion时域敏感度						default 0x60
	gpio_i2c_write(nvp6134_iic_addr[sens->ch / 4], 0xFF, 0x02);
	gpio_i2c_write(nvp6134_iic_addr[sens->ch / 4], 0x01 + (sens->ch % 4) * 0x07, sens->temporal_sens);

	//0x02+(ch%4)*0x07  motion空域敏感度						default 0x23
	gpio_i2c_write(nvp6134_iic_addr[sens->ch / 4], 0xFF, 0x02);
	gpio_i2c_write(nvp6134_iic_addr[sens->ch / 4], 0x02 + (sens->ch % 4) * 0x07, sens->pixel_sens);

	//0x03+(ch%4)*0x07  motion亮度敏感度，值越大越不灵敏		default 0x00
	gpio_i2c_write(nvp6134_iic_addr[sens->ch / 4], 0xFF, 0x02);
	gpio_i2c_write(nvp6134_iic_addr[sens->ch / 4], 0x03 + (sens->ch % 4) * 0x07, sens->brightness_sens);
}

/*******************************************************************************
motion block setting...192个块，每个寄存器8个bit，每个bit控制1个block.
0x40~0x57  ch1
0x58~0x6F  ch2
0x70~0x87  ch3
0x88~0x9F  ch4
*******************************************************************************/
void nvp6134_motion_area_mask(nvp6134_motion_area* ma)
{
	int bcnt;

	gpio_i2c_write(nvp6134_iic_addr[ma->ch / 4], 0xFF, 0x02);

	for(bcnt = 0 ; bcnt < sizeof(ma->blockset) ; bcnt++) {
		gpio_i2c_write(nvp6134_iic_addr[ma->ch / 4], 0x40 + (ma->ch % 4) * 0x18 + bcnt, ma->blockset[bcnt]);
	}
}

/*******************************************************************************
*	End of file
*******************************************************************************/
