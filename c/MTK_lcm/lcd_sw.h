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
 *    lcd_sw.h
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *   This file is intends for LCD driver.
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
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
#include "lcd_if.h"

#ifndef _LCD_SW_H
#define _LCD_SW_H

#if (defined(MT6218B) || defined(MT6219) || defined(MT6217)||defined(MT6226)||defined(MT6227))
	#define LCD_CMD_DMA_MODE
	#define LCD_18BIT_MODE

	#define LCD_DUMMYADDR   				0x90000000

	#define LCD_HX8306A_CTRL_ADDR		LCD_PARALLEL0_A0_LOW_ADDR
	#define LCD_HX8306A_DATA_ADDR		LCD_PARALLEL0_A0_HIGH_ADDR
	#define MAIN_LCD_CMD_ADDR			LCD_HX8306A_CTRL_ADDR
	#define MAIN_LCD_DATA_ADDR			LCD_HX8306A_DATA_ADDR
	#define MAIN_LCD_OUTPUT_FORMAT	LCM_18BIT_18_BPP_RGB666_1
#endif


/***********************S1D15G00********************************/
/*HIMAX, 262K Color LCD, Parallel Interface, Pxtel development board*/
#if (defined(MT6218B) || defined(MT6219) || defined(MT6217)||defined(MT6226)||defined(MT6227))
	#ifdef LCD_CMD_DMA_MODE
		#define LCD_SEND_DMA_CMD(n) \
		{\
			while (LCD_IS_RUNNING) {};\
			DISABLE_LCD_TRANSFER_COMPLETE_INT;\
			DISABLE_ALL_LCD_LAYER_WINDOW;\
			SET_LCD_ROI_CTRL_NUMBER_OF_CMD(n);\
			ENABLE_LCD_ROI_CTRL_CMD_FIRST;\
			SET_LCD_ROI_WINDOW_SIZE(0,0);\
			START_LCD_TRANSFER;\
			while (LCD_IS_RUNNING) {};\
		}
		#define LCD_CtrlWrite_HX8306A(_data) \
		{\
			SET_LCD_CMD_PARAMETER(0,LCD_CMD,(((_data & 0xFF00)<<2)|(_data&0xFF)<<1));\
			LCD_SEND_DMA_CMD(1);\
		}\

		#define LCD_DataWrite_HX8306A(_data) \
		{\
			SET_LCD_CMD_PARAMETER(0,LCD_DATA,(((_data & 0xFF00)<<2)|(_data&0xFF)<<1));\
			LCD_SEND_DMA_CMD(1);\
		}
		#define LCD_RAMWrite_HX8306A(_data)
	#else
		#define LCD_delay_HX8306A()

		#define LCD_CtrlWrite_HX8306A(_data)  \
		{\
			*(volatile kal_uint32 *) LCD_HX8306A_CTRL_ADDR= ((_data & 0xFF00)<<2)|((_data & 0xFF)<<1);\
			LCD_delay_HX8306A();\
		}\
		#define LCD_DataWrite_HX8306A(_data)  \
		{\
			*(volatile kal_uint32 *) LCD_HX8306A_DATA_ADDR= ((_data & 0xFF00)<<2)|((_data & 0xFF)<<1);\
			LCD_delay_HX8306A();\
		}
	#endif /* LCD_CMD_DMA_MODE */

	#define LCD_DataRead_HX8306A	(*(volatile kal_uint32 *)LCD_HX8306A_DATA_ADDR);
#endif
#endif   /*_LCD_SW_H*/


