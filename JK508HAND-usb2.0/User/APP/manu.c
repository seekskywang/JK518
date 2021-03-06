/**
  ******************************************************************************
  * @file    sysytem.c
  * @author  fire
  * @version V1.0
  * @date    2018-04-29
  * @brief   手持多路温度测试仪功能设置界面
  ******************************************************************************
   ******************************************************************************
  */

#include "./led/bsp_led.h"
#include "./lcd/bsp_lcd.h"
#include "./key/bsp_key.h"
#include "./beep/bsp_beep.h"
#include "./tim/bsp_basic_tim.h"
#include "jk508.h"

extern union 
{
   unsigned char FLAG_VAL6;
   struct 
   {
       unsigned char  TC:4;    //热电偶类型
       unsigned char  FT:1;    //分选/比较
       unsigned char  BP:1;    //讯响
       unsigned char  UT:2;	   //单位
   }BIT_FLAG;
}FLAG6;

extern union 
{
   unsigned char FLAG_VAL7;
   struct 
   {
       unsigned char  FN:2;    //字体
       unsigned char  SP:2;    //速度
       unsigned char  BD:3;    //波特
       unsigned char  LG:1;	   //语言
   }BIT_FLAG;
}FLAG7;

char rangename[10][10]={"  20m#"," 200m#\0","    2#","   20#","  200#",
						"   2k#","  20k#"," 200k#","  AUTO"
						,"   NOM",};
char rangenum[8][4]={"[0]","[1]","[2]","[3]","[4]",
											"[5]","[6]","[7]"};
/*
uint8_t ASCII53x108_d[1024]={
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0xFF,0x0F,0x00,0x00,0x80,0xFF,0xFF,0xFF,0xFF,0x0F,0x00,0x00,0x80,0xFF,0xFF,0xFF,0xFF,0x0F,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0x0F,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0x0F,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0x0F,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0x0F,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0x0F,0x00,
		0x00,0xE0,0xFF,0xFF,0xFF,0xFF,0x0F,0x00,0x00,0xE0,0xFF,0xFF,0xFF,0xFF,0x0F,0x00,0x00,0xE0,0xFF,0x01,0x00,0x00,0x00,0x00,0x00,0xE0,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x3F,0x00,0x00,0x00,0x00,0x00,
		0x00,0xFC,0x9F,0xFF,0x3F,0x00,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x00,0xFE,0xFF,0xFF,0xFF,0x0F,0x00,0x00,0x00,0xFE,0xFF,0xFF,0xFF,0x1F,0x00,0x00,0x00,0xFE,0xFF,0xFF,0xFF,0x7F,0x00,0x00,0x00,0xFE,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFE,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x03,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0x00,0x00,0xFF,0xFF,0x01,0xFC,0xFF,0x0F,0x00,0x80,0xFF,0x7F,0x00,0xF0,0xFF,0x0F,0x00,0x80,0xFF,0x1F,0x00,0xE0,0xFF,0x1F,0x00,0x80,0xFF,0x0F,0x00,0xC0,0xFF,0x1F,0x00,0x80,0xFF,0x07,0x00,0x80,0xFF,0x3F,0x00,0x00,0xFF,0x03,0x00,0x00,0xFF,0x3F,0x00,
		0x00,0x00,0x00,0x00,0x00,0xFE,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x7F,0x00,0x00,0xF8,0x00,0x00,0x00,0xF8,0x7F,0x00,0x80,0xFF,0x00,0x00,0x00,0xFC,0x7F,0x00,0xE0,0xFF,0x00,0x00,0x00,0xFC,0x7F,0x00,
		0xE0,0xFF,0x01,0x00,0x00,0xFC,0x7F,0x00,0xE0,0xFF,0x01,0x00,0x00,0xFE,0x3F,0x00,0xE0,0xFF,0x01,0x00,0x00,0xFE,0x3F,0x00,0xE0,0xFF,0x03,0x00,0x00,0xFF,0x3F,0x00,0xC0,0xFF,0x07,0x00,0x80,0xFF,0x3F,0x00,0xC0,0xFF,0x07,0x00,0x80,0xFF,0x1F,0x00,0xC0,0xFF,0x0F,0x00,0xC0,0xFF,0x1F,0x00,0x80,0xFF,0x1F,0x00,0xF0,0xFF,0x1F,0x00,0x80,0xFF,0x3F,0x00,0xF8,0xFF,0x0F,0x00,0x00,0xFF,0xFF,0x00,0xFE,0xFF,0x0F,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0x00,0x00,0xFE,0xFF,0xFF,0xFF,0xFF,0x03,0x00,0x00,0xFE,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x00,0xF8,0xFF,0xFF,0xFF,0x7F,0x00,0x00,0x00,0xF0,0xFF,0xFF,0xFF,0x3F,0x00,0x00,
		0x00,0xC0,0xFF,0xFF,0xFF,0x1F,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x07,0x00,0x00,0x00,0x00,0xFE,0xFF,0xFF,0x01,0x00,0x00,0x00,0x00,0xF8,0xFF,0x7F,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	};
*/
void page_measure( u32 rm)
{
// char name[9]={0};
	u8 u8range=0;

	/*初始化后默认使用前景层*/
	LCD_SetLayer(LCD_FOREGROUND_LAYER); 
	/*默认设置不透明	，该函数参数为不透明度，范围 0-0xff ，0为全透明，0xff为不透明*/
    LCD_SetTransparency(0xFF);
	LCD_Clear(LCD_COLOR_BACK);
	/*经过LCD_SetLayer(LCD_FOREGROUND_LAYER)函数后，
	以下液晶操作都在前景层刷新，除非重新调用过LCD_SetLayer函数设置背景层*/

	DrawMenu();
	Drawhomemenu();
//	DrawUnit();
//	LCD_SetColors(LCD_COLOR_BACK,LCD_COLOR_BACK);
//	LCD_SetColors(LCD_COLOR_BACK,LCD_COLOR_RED);
//	LCD_DrawFullRect(3,250,635,150);
	LCD_SetColors(LCD_COLOR_GREY,LCD_COLOR_BACK);
	LCD_DrawFullRect(1,160,637,2);
	LCD_DrawFullRect(1,400,637,2);
	LCD_DrawFullRect(1,162,2,240);
	LCD_DrawFullRect(636,162,2,240);
	LCD_SetTextColor(LCD_COLOR_HLT);
	LCD_SetBackColor(LCD_COLOR_BACK);
	if(LANG == chs)
	{
		LCD_DisplayStringLine(0,10, "<       >");
		LCD_DisplayStringLine(5,30, "测量显示");
		//LCD_DisplayStringLine(0,30, "<测量显示>");
		LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);	
		LCD_SetBackColor(LCD_COLOR_BACK);
		LCD_DisplayStringLine(50,10,"触发");
		LCD_DisplayStringLine(90,10,"量程");
		LCD_DisplayStringLine(130,10,"模式");
		LCD_DisplayStringLine(50,350,"速度");
		LCD_DisplayStringLine(90,350,"比较");
		LCD_DisplayStringLine(130,350,"讯响");
//		LCD_DisplayStringLine(170,10,"电阻率");
		LCD_DisplayStringLine(170,10,"电阻率");
		LCD_DisplayStringLine(170,10+80,"(@)");
		LCD_DisplayStringLine(210,10,"电导率");
		LCD_DisplayStringLine(210,10+80,"(k)");
//		LCD_DisplayStringLine(320,360,"定时");
	}else{
		LCD_DisplayStringLine(3,10, "<MEASURE DISP>");
		
		LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);	
		LCD_SetBackColor(LCD_COLOR_BACK);
		LCD_DisplayStringLine(50,10,"TRIGGER");
		LCD_DisplayStringLine(90,10,"RANGE");
		LCD_DisplayStringLine(127,10,"MODE");
		LCD_DisplayStringLine(170,10,"RESI(@)");
		LCD_DisplayStringLine(210,10,"COND(k)");
	}
	
	
	
	//LCD_SetTextColor(LCD_COLOR_RED);
	//LCD_DisplayStringLine_L(285,580,"NG");
	LCD_SetTextColor(LCD_COLOR_GREEN);
	LCD_DisplayStringLine_L(285,580,"GD");
	LCD_SetTextColor(LCD_COLOR_YELLOW);
	//LCD_DisplayStringLine_L(335,585,"K");
//	DISP_TEMP_L(340,570,"m",0);
	DISP_TEMP_L(340,605,"#",0);


	if(LANG == chs)
		DrawInstruction("触发器设置");
	else
		DrawInstruction("Set TRIGGER");
	RESISTIVITY=4569.333;
	CONDUXTIVITY=342.4532;
	Rfocus_off(RESISTIVITY);
    Cfocus_off(CONDUXTIVITY);
	
	
	
	
	
	page_flag = manus;
	op_flag = set_trigg;
	bit_flag = 1;
	Disp_main();
}


void Disp_main(void)
{
	u8 u8range=0;
	
	
	if(op_flag == set_trigg)
	{
		focus_on1();
	}else{
		focus_off1();
	}
	if(TRIGGER == 0){
		if(LANG == chs)
			LCD_DisplayStringLine(50,150,"内部");
		else
			LCD_DisplayStringLine(50,150,"INTERNAL");
		}
	else{
		if(LANG == chs)
			LCD_DisplayStringLine(50,150,"手动");//"手动"
		else
			LCD_DisplayStringLine(50,150,"MAN");//EXTERNAL
	}
	
	if(op_flag == set_range)
	{
		focus_on1();
	}else{
		focus_off1();
	}
	if(RANGE > 9) RANGE = 0;
	u8range=RANGE;
	LCD_DisplayStringLine(90,150,rangenum[Range]);
	LCD_DisplayStringLine(90,198,rangename[u8range]);
	
	if(op_flag == set_mode)
	{
		focus_on1();
	}else{
		focus_off1();
	}
	if(LANG == chs)
	{
		if(MODE == 0){
			LCD_DisplayStringLine(130,150,"大电流");
		}
	}else{
		if(MODE == 0){
	//		DISP_CNL_S(127,150,"o");
			LCD_DisplayStringLine(127,150,"H-CUR");
		//	LCD_DisplayStringLine(130,195,"爵");
		}
	}
	
	if(op_flag == set_spd)
	{
		focus_on1();
	}else{
		focus_off1();
	}
	if(SPEED == fast)
	{
		if(LANG == chs)
		{
			LCD_DisplayStringLine(50,500,"快速");
		}else{
			LCD_DisplayStringLine(50,500,"FAST");
		}
	}else if(SPEED == moderate){
		if(LANG == chs)
		{
			LCD_DisplayStringLine(50,500,"中速");
		}else{
			LCD_DisplayStringLine(50,500,"MED");
		}
	}else if(SPEED == slow){
		if(LANG == chs)
		{
			LCD_DisplayStringLine(50,500,"慢速");
		}else{
			LCD_DisplayStringLine(50,500,"SLOW");
		}
	}
	
	if(op_flag == set_filter)
	{
		focus_on1();
	}else{
		focus_off1();
	}
	if(FILTER == ft_off){
		if(LANG == chs)
		{
			LCD_DisplayStringLine(90,500,"关闭");
		}else{
			LCD_DisplayStringLine(90,500,"OFF");
		}
	}else{
		if(LANG == chs)
		{
			LCD_DisplayStringLine(90,500,"打开");
		}else{
			LCD_DisplayStringLine(90,500,"ON");
		}
	}
	
	if(op_flag == set_beep)
	{
		focus_on1();
	}else{
		focus_off1();
	}
	if(BEEP == beep_off){
		if(LANG == chs)
		{
			LCD_DisplayStringLine(130,500,"关闭");
		}else{
			LCD_DisplayStringLine(130,500,"OFF");
		}
	}else{
		if(LANG == chs)
		{
			LCD_DisplayStringLine(130,500,"打开");
		}else{
			LCD_DisplayStringLine(130,500,"ON");
		}
	}
}

void Disp_main_button(void)
{
	if(op_sw == op_off)
	{
		switch(op_flag)
		{
			case set_trigg:
			{
				DrawMenu();//重绘菜单栏
				LCD_SetTextColor(LCD_COLOR_YELLOW);
				LCD_SetBackColor(LCD_COLOR_BLACK);
				if(LANG == chs)
				{
					LCD_DisplayStringLine(445,35,"内部");
					LCD_DisplayStringLine(445,157,"手动");
				}else{
					LCD_DisplayStringLine(445,35,"INTERNAL");
					LCD_DisplayStringLine(445,157,"MAN");
				}
				op_sw = op_on;
			}break;
			case set_range:
			{
				DrawMenu();//重绘菜单栏
				LCD_SetTextColor(LCD_COLOR_YELLOW);
				LCD_SetBackColor(LCD_COLOR_BLACK);
				if(LANG == chs)
				{
					LCD_DisplayStringLine(445,35,"自动");					
					LCD_DisplayStringLine(445,157,"保持");
					LCD_DisplayStringLine(445,292,"标称");
					
				}else{
					LCD_DisplayStringLine(445,35,"AUTO");					
					LCD_DisplayStringLine(445,157,"HOLD");
					LCD_DisplayStringLine(445,292,"NOM");
				}
				LCD_DisplayStringLine(450,435,"+");
					LCD_DisplayStringLine(450,568,"-");
				op_sw = op_on;
			}break;
			case set_mode:
			{
				DrawMenu();//重绘菜单栏
				LCD_SetTextColor(LCD_COLOR_YELLOW);
				LCD_SetBackColor(LCD_COLOR_BLACK);
			if(LANG == chs)
			{
			//	DISP_CNL_S(445,48,"o");
				LCD_DisplayStringLine(445,10,"大电流");

			}else{
				LCD_DisplayStringLine(445,20,"H-CUR");

			}
				op_sw = op_on;
			}break;	
			case set_filter:
			{
				DrawMenu();//重绘菜单栏
				LCD_SetTextColor(LCD_COLOR_YELLOW);
				LCD_SetBackColor(LCD_COLOR_BLACK);
				if(LANG == chs)
				{
					LCD_DisplayStringLine(445,35,"打开");
					LCD_DisplayStringLine(445,157,"关闭");
				}else{
					LCD_DisplayStringLine(445,35,"ON");
					LCD_DisplayStringLine(445,157,"OFF");
				}
				op_sw = op_on;
			}break;
			case set_beep:
			{
				DrawMenu();//重绘菜单栏
				LCD_SetTextColor(LCD_COLOR_YELLOW);
				LCD_SetBackColor(LCD_COLOR_BLACK);
				if(LANG == chs)
				{
					LCD_DisplayStringLine(445,35,"打开");
					LCD_DisplayStringLine(445,157,"关闭");
				}else{
					LCD_DisplayStringLine(445,35,"ON");
					LCD_DisplayStringLine(445,157,"OFF");
				}
				op_sw = op_on;
			}break;
			case set_spd:
			{
				DrawMenu();//重绘菜单栏
				LCD_SetTextColor(LCD_COLOR_YELLOW);
				LCD_SetBackColor(LCD_COLOR_BLACK);
				if(LANG == chs)
				{
					LCD_DisplayStringLine(445,35,"快速");
					LCD_DisplayStringLine(445,157,"中速");
					LCD_DisplayStringLine(445,292,"慢速");
				}else{
					LCD_DisplayStringLine(445,35,"FAST");
					LCD_DisplayStringLine(445,157,"MED");
					LCD_DisplayStringLine(445,292,"SLOW");
				}
				op_sw = op_on;
			}break;
		}
	}
}