/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

/*****************************************************************************
 *
 * Filename:
 * ---------
 *    lcd.c
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *   This Module defines the LCD driver.
 *
 * Author:
 * -------
 * -------
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
#include "drv_comm.h"
#include "reg_base.h"
#include "lcd_sw_inc.h"
#include "lcd_sw.h"
#include "lcd_hw.h"
/*Serial interface*/
#include "lcd_if.h"

extern void GPIO_ModeSetup(kal_uint16 pin, kal_uint16 conf_dada);
extern void GPIO_WriteIO(char data, char port);
extern void PWM2_level(kal_uint8 level);

kal_bool  lcd_assert_fail=KAL_FALSE;

/* default value for Himax HX8306A */
kal_uint16 lcd_power_ctrl_shadow1,lcd_power_ctrl_shadow3,lcd_power_ctrl_shadow4;

#ifdef DUAL_LCD

	#ifndef COLOR_SUBLCD
		const kal_uint8 SubLCDSetArray[]=
		{
			0x01,	// 0000 0001
			0x02,	// 0000 0010
			0x04,	// 0000 0100
			0x08,	// 0000 1000
			0x10,	// 0001 0000
			0x20,	// 0010 0000
			0x40,	// 0100 0000
			0x80	// 1000 0000
		};

		const kal_uint8 SubLCDReSetArray[]=
		{
			0xFE,	// 1111 1110
			0xFD,	// 1111 1101
			0xFB,	// 1111 1011
			0xF7,	// 1111 0111
			0xEF,	// 1110 1111
			0xDF,	// 1101 1111
			0xBF,	// 1011 1111
			0x7F	// 0111 1111
		};
	#endif
#endif

void LCD_Delay(kal_uint32 delay_count)
{
	volatile kal_uint32 delay;
	for (delay =0;delay <(delay_count);delay++)	{}
}

void spi_ini(void)
{
}

#if (defined(MT6218B)||defined(MT6219)||defined(MT6217)||defined(MT6226)||defined(MT6227))
void init_lcd_interface(void)
{

	REG_LCD_ROI_CTRL=0;
	CLEAR_LCD_CTRL_RESET_PIN;
   #if (defined(MT6219)||defined(MT6226)||defined(MT6227))
   	SET_LCD_PARALLEL_CE2WR_SETUP_TIME((kal_uint32)1);
   	SET_LCD_PARALLEL_CE2WR_HOLD_TIME(1);
   	SET_LCD_PARALLEL_CE2RD_SETUP_TIME(1);
   	SET_LCD_PARALLEL_WRITE_WAIT_STATE(2);
   	SET_LCD_PARALLEL_READ_LATENCY_TIME(2);
   	SET_LCD_ROI_CTRL_CMD_LATENCY(2);

      #if (defined(MT6226)||defined(MT6227))
      	#if (defined(LCD_18BIT_MODE))
		GPIO_ModeSetup(55, 1);
		*((volatile unsigned short *) 0x801201B0) |= 0x4000;
		*((volatile unsigned short *) 0x801201D0) |= 0x0001;

   	SET_LCD_PARALLEL_18BIT_DATA_BUS;
   		#endif
   	SET_LCD_PARALLEL_GAMMA_R_TABLE(LCD_PARALLEL_GAMMA_DISABLE);
   	SET_LCD_PARALLEL_GAMMA_G_TABLE(LCD_PARALLEL_GAMMA_DISABLE);
   	SET_LCD_PARALLEL_GAMMA_B_TABLE(LCD_PARALLEL_GAMMA_DISABLE);
      #endif

      #if (defined(MT6219))
   	DISABLE_LCD_PARALLEL_SYNC;
      #endif
   #endif

	SET_LCD_CTRL_RESET_PIN;
}	/* init_lcd_interface() */
#endif /* MT6217, MT6218B, MT6219 */

void LCD_EnterSleep_HX8306A(void)
{
	lcd_power_ctrl_shadow1 |= 0x02;
	lcd_power_ctrl_shadow3 &= ~0x10;
	lcd_power_ctrl_shadow4 &= ~0x2000;
	#if (defined(LCD_CMD_DMA_MODE))
		#if (defined(LCD_8BIT_MODE))
		#elif (defined(LCD_9BIT_MODE))
		#elif (defined(LCD_16BIT_MODE))
		#elif (defined(LCD_18BIT_MODE))
			SET_LCD_CMD_PARAMETER(0,LCD_CMD,((0x0007&0xFF00)<<2)|((0x0007&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(1,LCD_DATA,((0x0036&0xFF00)<<2)|((0x0036&0xFF)<<1));
			LCD_SEND_DMA_CMD(2);
			LCD_Delay(0x1000);
			SET_LCD_CMD_PARAMETER(0,LCD_CMD,((0x0007&0xFF00)<<2)|((0x0007&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(1,LCD_DATA,((0x0026&0xFF00)<<2)|((0x0026&0xFF)<<1));
			LCD_SEND_DMA_CMD(2);
			SET_LCD_CMD_PARAMETER(0,LCD_CMD,((0x0007&0xFF00)<<2)|((0x0007&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(1,LCD_DATA,((0x0004&0xFF00)<<2)|((0x0004&0xFF)<<1));
			LCD_SEND_DMA_CMD(2);
			LCD_Delay(0x1000);
			SET_LCD_CMD_PARAMETER(0,LCD_CMD,((0x0010&0xFF00)<<2)|((0x0010&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(1,LCD_DATA,((lcd_power_ctrl_shadow1&0xFF00)<<2)|((lcd_power_ctrl_shadow1&0xFF)<<1));
			LCD_SEND_DMA_CMD(2);
			LCD_Delay(0x8000);
			SET_LCD_CMD_PARAMETER(0,LCD_CMD,((0x0012&0xFF00)<<2)|((0x0012&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(1,LCD_DATA,((lcd_power_ctrl_shadow3&0xFF00)<<2)|((lcd_power_ctrl_shadow3&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(2,LCD_CMD,((0x0013&0xFF00)<<2)|((0x0013&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(3,LCD_DATA,((lcd_power_ctrl_shadow4&0xFF00)<<2)|((lcd_power_ctrl_shadow4&0xFF)<<1));
			LCD_SEND_DMA_CMD(4);
			LCD_Delay(0x1000);
		#endif
	#else
		LCD_CtrlWrite_HX8306A(0x0007);
		LCD_DataWrite_HX8306A(0x0036);
		LCD_Delay(0x1000);
		LCD_CtrlWrite_HX8306A(0x0007);
		LCD_DataWrite_HX8306A(0x0026);
		LCD_CtrlWrite_HX8306A(0x0007);
		LCD_DataWrite_HX8306A(0x0004);
		LCD_Delay(0x1000);
		LCD_CtrlWrite_HX8306A(0x0010);
		LCD_DataWrite_HX8306A(lcd_power_ctrl_shadow1);
		LCD_Delay(0x8000);
		LCD_CtrlWrite_HX8306A(0x0012);
		LCD_DataWrite_HX8306A(lcd_power_ctrl_shadow3);
		LCD_CtrlWrite_HX8306A(0x0013);
		LCD_DataWrite_HX8306A(lcd_power_ctrl_shadow4);
		LCD_Delay(0x1000);
	#endif
}

void LCD_ExitSleep_HX8306A(void)
{
	lcd_power_ctrl_shadow1 &= ~0x2;
	lcd_power_ctrl_shadow3 |= 0x10;
	lcd_power_ctrl_shadow4 |= 0x2000;
	#if (defined(LCD_CMD_DMA_MODE))
		#if (defined(LCD_8BIT_MODE))
		#elif (defined(LCD_9BIT_MODE))
		#elif (defined(LCD_16BIT_MODE))
		#elif (defined(LCD_18BIT_MODE))
			SET_LCD_CMD_PARAMETER(0,LCD_CMD,((0x0012&0xFF00)<<2)|((0x0012&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(1,LCD_DATA,((lcd_power_ctrl_shadow3&0xFF00)<<2)|((lcd_power_ctrl_shadow3&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(2,LCD_CMD,((0x0013&0xFF00)<<2)|((0x0013&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(3,LCD_DATA,((lcd_power_ctrl_shadow4&0xFF00)<<2)|((lcd_power_ctrl_shadow4&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(4,LCD_CMD,((0x0010&0xFF00)<<2)|((0x0010&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(5,LCD_DATA,((lcd_power_ctrl_shadow1&0xFF00)<<2)|((lcd_power_ctrl_shadow1&0xFF)<<1));
			LCD_SEND_DMA_CMD(6);

			SET_LCD_CMD_PARAMETER(0,LCD_CMD,((0x0007&0xFF00)<<2)|((0x0007&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(1,LCD_DATA,((0x0005&0xFF00)<<2)|((0x0005&0xFF)<<1));
			LCD_SEND_DMA_CMD(2);
			LCD_Delay(0x1000);
			SET_LCD_CMD_PARAMETER(0,LCD_CMD,((0x0007&0xFF00)<<2)|((0x0007&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(1,LCD_DATA,((0x0025&0xFF00)<<2)|((0x0025&0xFF)<<1));
			LCD_SEND_DMA_CMD(2);
			SET_LCD_CMD_PARAMETER(0,LCD_CMD,((0x0007&0xFF00)<<2)|((0x0007&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(1,LCD_DATA,((0x0027&0xFF00)<<2)|((0x0027&0xFF)<<1));
			LCD_SEND_DMA_CMD(2);
			LCD_Delay(0x1000);
			SET_LCD_CMD_PARAMETER(0,LCD_CMD,((0x0007&0xFF00)<<2)|((0x0007&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(1,LCD_DATA,((0x0037&0xFF00)<<2)|((0x0037&0xFF)<<1));
			LCD_SEND_DMA_CMD(2);
			LCD_Delay(0x1000);
		#endif
	#else
		LCD_CtrlWrite_HX8306A(0x0010);
		LCD_DataWrite_HX8306A(lcd_power_ctrl_shadow1);
		LCD_CtrlWrite_HX8306A(0x0012);
		LCD_DataWrite_HX8306A(lcd_power_ctrl_shadow3);
		LCD_CtrlWrite_HX8306A(0x0013);
		LCD_DataWrite_HX8306A(lcd_power_ctrl_shadow4);
		LCD_CtrlWrite_HX8306A(0x0007);
		LCD_DataWrite_HX8306A(0x0005);
		LCD_Delay(0x1000);
		LCD_CtrlWrite_HX8306A(0x0007);
		LCD_DataWrite_HX8306A(0x0025);
		LCD_CtrlWrite_HX8306A(0x0007);
		LCD_DataWrite_HX8306A(0x0027);
		LCD_Delay(0x1000);
		LCD_CtrlWrite_HX8306A(0x0007);
		LCD_DataWrite_HX8306A(0x0037);
		LCD_Delay(0x1000);
	#endif
}

void LCD_Partial_On_HX8306A(kal_uint16 start_page,kal_uint16 end_page)
{
	#if (defined(LCD_CMD_DMA_MODE))
		#if (defined(LCD_8BIT_MODE))
		#elif (defined(LCD_9BIT_MODE))
		#elif (defined(LCD_16BIT_MODE))
		#elif (defined(LCD_18BIT_MODE))
			SET_LCD_CMD_PARAMETER(0,LCD_CMD,((0x0042&0xFF00)<<2)|((0x0042&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(1,LCD_DATA,((end_page&0xFF)<<10)|((start_page&0xFF)<<1));
			LCD_SEND_DMA_CMD(2);
		#endif
	#else
		LCD_CtrlWrite_HX8306A(0x0042);
		LCD_DataWrite_HX8306A((start_page&0xFF)|((end_page&0xFF)<<8));
	#endif
}

void LCD_Partial_Off_HX8306A(void)
{
	#if (defined(LCD_CMD_DMA_MODE))
		#if (defined(LCD_8BIT_MODE))
		#elif (defined(LCD_9BIT_MODE))
		#elif (defined(LCD_16BIT_MODE))
		#elif (defined(LCD_18BIT_MODE))
			SET_LCD_CMD_PARAMETER(0,LCD_CMD,((0x0042&0xFF00)<<2)|((0x0042&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(1,LCD_DATA,((0xDB00&0xFF00)<<2)|((0xDB00&0xFF)<<1));
			LCD_SEND_DMA_CMD(2);
		#endif
	#else
		LCD_CtrlWrite_HX8306A(0x0042);
		LCD_DataWrite_HX8306A(0xDB00);
	#endif
}

kal_uint8 LCD_Partial_line_HX8306A(void)
{
	return 1;		/* partial display in 1 line alignment */
}


void LCD_blockClear_HX8306A(kal_uint16 x1,kal_uint16 y1,kal_uint16 x2,kal_uint16 y2,kal_uint16 data)
{
	kal_uint16 LCD_x;
	kal_uint16 LCD_y;
	kal_uint8 r_color,g_color,b_color;

	r_color=(data&0xF800)>>10;	/* transfer to RGB666 */
	g_color=(data>>5)&0x3F;
	b_color=((data)&0x1F)<<1;
	#if (defined(LCD_CMD_DMA_MODE))
		#if (defined(LCD_8BIT_MODE))
		#elif (defined(LCD_9BIT_MODE))
		#elif (defined(LCD_16BIT_MODE))
		#elif (defined(LCD_18BIT_MODE))
			SET_LCD_CMD_PARAMETER(0,LCD_CMD,((0x0044&0xFF00)<<2)|((0x0044&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(1,LCD_DATA,((x2&0xFF)<<10)|((x1&0xFF)<<1));

			SET_LCD_CMD_PARAMETER(2,LCD_CMD,((0x0045&0xFF00)<<2)|((0x0045&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(3,LCD_DATA,((y2&0xFF)<<10)|((y1&0xFF)<<1));

			SET_LCD_CMD_PARAMETER(4,LCD_CMD,((0x0021&0xFF00)<<2)|((0x0021&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(5,LCD_DATA,((y1&0xFF)<<10)|((x1&0xFF)<<1));

			SET_LCD_CMD_PARAMETER(6,LCD_CMD,((0x0022&0xFF00)<<2)|((0x0022&0xFF)<<1));

			LCD_SEND_DMA_CMD(7);
		#endif
	#else
		LCD_CtrlWrite_HX8306A(0x0044);
		LCD_DataWrite_HX8306A((((x2&0xFF)<<8)|(x1&0xFF)));
		LCD_CtrlWrite_HX8306A(0x0045);
		LCD_DataWrite_HX8306A((((y2&0xFF)<<8)|(y1&0xFF)));
		LCD_CtrlWrite_HX8306A(0x0021);
		LCD_DataWrite_HX8306A((((y1&0xFF)<<8)|(x1&0xFF)));
		LCD_CtrlWrite_HX8306A(0x0022);
	#endif

	for(LCD_y=y1;LCD_y<=y2;LCD_y++)
	{
		for(LCD_x=x1;LCD_x<=x2;LCD_x++)
		{
		#if (defined(LCD_8BIT_MODE))
			*((volatile unsigned char *) LCD_HX8306A_DATA_ADDR)=(kal_uint8)((data&0xFF00)>>8);
			*((volatile unsigned char *) LCD_HX8306A_DATA_ADDR)=(kal_uint8)(data&0xFF);
		#elif (defined(LCD_16BIT_MODE))
			*((volatile unsigned short *) LCD_HX8306A_DATA_ADDR)=data;
		#elif (defined(LCD_18BIT_MODE))
			*((volatile unsigned int *) LCD_HX8306A_DATA_ADDR)=(r_color<<12)|(g_color<<6)|b_color;
//				*((volatile unsigned int *) LCD_HX8306A_DATA_ADDR)=(kal_uint16) data;
		#elif (defined(LCD_9BIT_MODE))
			*((volatile unsigned short *) LCD_HX8306A_DATA_ADDR)=(r_color<<6)|(g_color>>3);
			*((volatile unsigned short *) LCD_HX8306A_DATA_ADDR)=((g_color&0x07)<<6)|b_color;
		#endif
		}
	}
}

void LCD_ClearAll_HX8306A(kal_uint16 data)
{
   LCD_blockClear_HX8306A(0,0,LCD_WIDTH-1,LCD_HEIGHT-1,data);
}

void LCD_set_reg(kal_uint16 reg_index, kal_uint16 reg_data)
{
	LCD_CtrlWrite_HX8306A(reg_index);
	LCD_DataWrite_HX8306A(reg_data);
}

void LCD_Init_HX8306A(kal_uint32 bkground, void **buf_addr)
{
	volatile kal_uint32 i;
	kal_uint16 background = (kal_uint16)bkground;
	kal_uint16 read_data;

	CLEAR_LCD_CTRL_RESET_PIN;
	LCD_Delay(0x1000);
	SET_LCD_CTRL_RESET_PIN;
	LCD_Delay(0x1000);

	LCD_set_reg(0x0000,0x0001);
	LCD_Delay(0x200);				/* delay 10ms */

	LCD_set_reg(0x0001,0x011B);
	LCD_set_reg(0x0002,0x0700);
	LCD_set_reg(0x0003,0x1030);
//	LCD_set_reg(0x0003,0x1210);
	LCD_set_reg(0x0004,0x0000);
	LCD_set_reg(0x0005,0x0000);
//	LCD_set_reg(0x0007,0x0003);
	LCD_set_reg(0x0007,0x0007);
	LCD_set_reg(0x0008,0x0202);
	LCD_set_reg(0x0009,0x0000);
	LCD_set_reg(0x000B,0x0008);
	LCD_set_reg(0x000C,0x0003);
	LCD_set_reg(0x0040,0x0000);
	LCD_set_reg(0x0041,0x00EF);
	LCD_set_reg(0x0042,0xDB00);
	LCD_set_reg(0x0043,0xDB00);
	LCD_set_reg(0x0044,0xAF00);
	LCD_set_reg(0x0045,0xDB00);

	LCD_set_reg(0x0010,0x0000);
	LCD_set_reg(0x0011,0x0000);
	LCD_set_reg(0x0012,0x0000);
	LCD_set_reg(0x0013,0x0000);
	LCD_set_reg(0x0011,0x0000);
	LCD_set_reg(0x0013,0x1517);
	LCD_set_reg(0x0012,0x0008);
	LCD_set_reg(0x0010,0x0040);
	LCD_set_reg(0x0011,0x0000);
	LCD_set_reg(0x0010,0x0054);
	LCD_set_reg(0x0012,0x0012);
	LCD_Delay(0x800);
	LCD_set_reg(0x0010,0x4040);
	LCD_Delay(0x800);
	LCD_set_reg(0x0013,0x300E);
	LCD_Delay(0x800);
	LCD_set_reg(0x0010,0x2140);
	LCD_Delay(0x800);

	LCD_set_reg(0x0030,0x0000);
	LCD_set_reg(0x0031,0x0207);
	LCD_set_reg(0x0032,0x0000);
	LCD_set_reg(0x0033,0x0401);
	LCD_set_reg(0x0034,0x0707);
	LCD_set_reg(0x0035,0x0005);
	LCD_set_reg(0x0036,0x0707);
	LCD_set_reg(0x0037,0x0000);
	LCD_set_reg(0x0038,0x0000);
	LCD_set_reg(0x0039,0x0000);

	LCD_set_reg(0x0007,0x0005);
	LCD_Delay(0x800);
	LCD_set_reg(0x0007,0x0025);
	LCD_set_reg(0x0007,0x0027);
	LCD_Delay(0x800);
	LCD_set_reg(0x0007,0x0037);
	LCD_Delay(0x800);

	LCD_ClearAll_HX8306A(0xFFFF);

	lcd_power_ctrl_shadow1=0x2140;
	lcd_power_ctrl_shadow3=0x0012;
	lcd_power_ctrl_shadow4=0x300E;
	
	LCD_Delay(0x80000);
	/* turn on backlight */
//	*((volatile unsigned short *) 0x80120150) &= 0xF3FF;
//	*((volatile unsigned short *) 0x80120000) |= 0x20;
//	*((volatile unsigned short *) 0x801200C0) |= 0x20;
}

void LCD_PWRON_HX8306A(kal_bool on)
{
}

void LCD_SetContrast_HX8306A(kal_uint8 level)
{
}

void LCD_ON_HX8306A(kal_bool on)
{
}

void LCD_BlockWrite_HX8306A(kal_uint16 startx,kal_uint16 starty,kal_uint16 endx,kal_uint16 endy)
{
   kal_uint16 roi_width;
   kal_uint16 x,y;

	while (LCD_IS_RUNNING){};

//   ASSERT(lcd_assert_fail==KAL_FALSE);
   lcd_assert_fail = KAL_TRUE;

	#ifdef LCD_CMD_DMA_MODE
		#if (defined(LCD_8BIT_MODE))
		#elif (defined(LCD_9BIT_MODE))
		#elif (defined(LCD_16BIT_MODE))
		#elif (defined(LCD_18BIT_MODE))
			SET_LCD_CMD_PARAMETER(0,LCD_CMD,((0x0044&0xFF00)<<2)|((0x0044&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(1,LCD_DATA,((endx&0xFF)<<10)|((startx&0xFF)<<1));

			SET_LCD_CMD_PARAMETER(2,LCD_CMD,((0x0045&0xFF00)<<2)|((0x0045&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(3,LCD_DATA,((endy&0xFF)<<10)|((starty&0xFF)<<1));

			SET_LCD_CMD_PARAMETER(4,LCD_CMD,((0x0021&0xFF00)<<2)|((0x0021&0xFF)<<1));
			SET_LCD_CMD_PARAMETER(5,LCD_DATA,((starty&0xFF)<<10)|((startx&0xFF)<<1));

			SET_LCD_CMD_PARAMETER(6,LCD_CMD,((0x0022&0xFF00)<<2)|((0x0022&0xFF)<<1));
		#endif
		ENABLE_LCD_TRANSFER_COMPLETE_INT;
		ENABLE_LCD_ROI_CTRL_CMD_FIRST;
		SET_LCD_ROI_CTRL_NUMBER_OF_CMD(7);
		START_LCD_TRANSFER;
	#else
		LCD_CtrlWrite_HX8306A(0x0044);
		LCD_DataWrite_HX8306A((((endx&0xFF)<<8)|(startx&0xFF)));
		LCD_CtrlWrite_HX8306A(0x0045);
		LCD_DataWrite_HX8306A((((endy&0xFF)<<8)|(starty&0xFF)));
		LCD_CtrlWrite_HX8306A(0x0021);
		LCD_DataWrite_HX8306A((((starty&0xFF)<<8)|(startx&0xFF)));
		LCD_CtrlWrite_HX8306A(0x0022);

		DISABLE_LCD_TRANSFER_COMPLETE_INT;
		DISABLE_LCD_ROI_CTRL_CMD_FIRST;
		START_LCD_TRANSFER;
	#endif /* MT6218B, MT6219 */

   lcd_assert_fail = KAL_FALSE;
}

void LCD_Size_HX8306A(kal_uint16 *out_LCD_width,kal_uint16 *out_LCD_height)
{
   	*out_LCD_width = LCD_WIDTH;
   	*out_LCD_height = LCD_HEIGHT;
}

/*Engineering mode*/
kal_uint8 LCD_GetParm_HX8306A(lcd_func_type type)
{
   switch(type)
   {
      case lcd_Bais_func:
         return 1;
      case lcd_Contrast_func:
         return 1;
      case lcd_LineRate_func:
         return 4;
      case lcd_Temperature_Compensation_func:
         return 4;
      default:
         ASSERT(0);
         return 100;
   }
}

void LCD_SetBias_HX8306A(kal_uint8 *bias)
{

}

void LCD_Contrast_HX8306A(kal_uint8 *contrast)
{
}

void LCD_LineRate_HX8306A(kal_uint8 *linerate)
{
}

void LCD_Temp_Compensate_HX8306A(kal_uint8 *compensate)
{
}

/*===================The above is LCD dependent==========*/
#if ( (defined(MT6205B)) || (defined(MT6218)) )
void LCD_memcpy(void *dst /*s1*/, const void *src /*s2*/, kal_uint16 size)
{
   #ifdef LCD_DMAENABLE
      kal_uint32 srcaddr=(kal_uint32)src;
      kal_uint32 dstaddr=(kal_uint32)dst;
      kal_uint16 size_MSB = (kal_uint16)(size >> 9);
      kal_uint16 size_LSB = (kal_uint16)(size & 0x01ff);

      ASSERT(lcd_assert_fail==KAL_FALSE);
      lcd_assert_fail = KAL_TRUE;
      ASSERT(DRV_Reg(LCD_REFR)==0x00);
      if(size_MSB)
      {
         DRV_WriteReg(LCD_MSBSRC,(kal_uint16)(srcaddr >> 16));
         DRV_WriteReg(LCD_LSBSRC,(kal_uint16)srcaddr);

         DRV_WriteReg(LCD_REFR,0x0000);
         DRV_WriteReg(LCD_MSBDST,(kal_uint16)(dstaddr >> 16));
         DRV_WriteReg(LCD_LSBDST,(kal_uint16)(dstaddr));

         DRV_WriteReg(LCD_CADDRSET,512);
         DRV_WriteReg(LCD_PADDRSET,size_MSB);
         DRV_WriteReg(LCD_CHOP,0);

         DRV_WriteReg(LCD_PCON,LCD_PCON_DINC);

         DRV_WriteReg(LCD_START,LCD_START_BIT);
         while(DRV_Reg(LCD_GSTA)&LCD_GSTA_PRUN);
         DRV_WriteReg(LCD_START,LCD_STOP_BIT);
      }

      if (size_LSB)
      {
         srcaddr = (srcaddr + size - size_LSB);
         dstaddr = (dstaddr + size - size_LSB);

         DRV_WriteReg(LCD_MSBSRC,(kal_uint16)(srcaddr >> 16));
         DRV_WriteReg(LCD_LSBSRC,(kal_uint16)srcaddr);

         DRV_WriteReg(LCD_REFR,0x0000);
         DRV_WriteReg(LCD_MSBDST,(kal_uint16)(dstaddr >> 16));
         DRV_WriteReg(LCD_LSBDST,(kal_uint16)(dstaddr));

         DRV_WriteReg(LCD_CADDRSET,size_LSB);
         DRV_WriteReg(LCD_PADDRSET,1);
         DRV_WriteReg(LCD_CHOP,0);

         DRV_WriteReg(LCD_PCON,LCD_PCON_DINC);

         DRV_WriteReg(LCD_START,LCD_START_BIT);
         while(DRV_Reg(LCD_GSTA)&LCD_GSTA_PRUN);
         DRV_WriteReg(LCD_START,LCD_STOP_BIT);
      }

      lcd_assert_fail = KAL_FALSE;
   #else /*!LCD_DMAENABLE*/
      kal_mem_cpy(dst,src,size);
   #endif   /*LCD_DMAENABLE*/
}
#else /*!(MT6205B,MT6218)*/
void LCD_memcpy(void *dst /*s1*/, const void *src /*s2*/, kal_uint16 size)
{
   kal_mem_cpy(dst,src,size);
}
#endif   /*(MT6205B,MT6218)*/

LCD_Funcs LCD_func_HX8306A = {
   LCD_Init_HX8306A,
   LCD_PWRON_HX8306A,
   LCD_SetContrast_HX8306A,
   LCD_ON_HX8306A,
   LCD_BlockWrite_HX8306A,
   LCD_Size_HX8306A,
   LCD_EnterSleep_HX8306A,
   LCD_ExitSleep_HX8306A,
   LCD_Partial_On_HX8306A,
   LCD_Partial_Off_HX8306A,
   LCD_Partial_line_HX8306A,
   /*Engineering mode*/
   LCD_GetParm_HX8306A,
   LCD_SetBias_HX8306A,
   LCD_Contrast_HX8306A,
   LCD_LineRate_HX8306A,
   LCD_Temp_Compensate_HX8306A
};

void LCD_FunConfig(void)
{
   MainLCD = &LCD_func_HX8306A;
}


