#include "ssd1963_headerfile.h"


//=============================================================================
// Write command to SSD1963
//=============================================================================
void SSD1963_WriteCommand(uint16_t regsiter)
{
	LCD_REG = regsiter;
}
//=============================================================================
// Write data to SSD1963
//=============================================================================
void SSD1963_WriteData(uint16_t data)
{
	LCD_RAM = data;
}
//=============================================================================
// 
//=============================================================================
void SSD1963_Init (void)
{
	volatile unsigned int dly;

	SSD1963_WriteCommand(SSD1963_SOFT_RESET);
	
	// REFclk = crystal = 10MHz
	SSD1963_WriteCommand(SSD1963_SET_PLL_MN);
	SSD1963_WriteData(0x3c);	// PLLclk = REFclk * 60 (800MHz)
	//SSD1963_WriteData(0x28);	// PLLclk = REFclk * 30 (300MHz)
	//SSD1963_WriteData(0x02);	// SYSclk = PLLclk / 3  (100MHz)
	SSD1963_WriteData(0x02);	// SYSclk = PLLclk / 3  (200MHz)
	SSD1963_WriteData(0x54);  // dummy

	SSD1963_WriteCommand(SSD1963_SET_PLL);
	SSD1963_WriteData(0x01);
 
	for(dly = 0; dly < 100000; dly++);

	SSD1963_WriteCommand(SSD1963_SET_PLL);
	SSD1963_WriteData(0x03);
	
	SSD1963_WriteCommand(0x01);  // soft reset
	
	//Set LSHIFT freq, i.e. the DCLK with PLL freq 120MHz set previously
	//Typical DCLK for AT070TN94 is 46MHz
	//46MHz = 200MHz*(LCDC_FPR+1)/2^20
	//LCDC_FPR = 241171 (0x170A2)
	SSD1963_WriteCommand(SSD1963_SET_LSHIFT_FREQ); 
	SSD1963_WriteData(0x03);
	SSD1963_WriteData(0xAE);
	SSD1963_WriteData(0x13);

  //Set panel mode, varies from individual manufacturer
	SSD1963_WriteCommand(SSD1963_SET_LCD_MODE); 
	SSD1963_WriteData(0x0C);//24-Bit //(0x0C); //18-Bit			
	SSD1963_WriteData(0x00);			
	SSD1963_WriteData((TFT_WIDTH-1)>>8);
	SSD1963_WriteData((TFT_WIDTH-1) & 0xFF);
	SSD1963_WriteData((TFT_HEIGHT-1)>>8);
	SSD1963_WriteData((TFT_HEIGHT-1) & 0xFF);
	SSD1963_WriteData(0x00);
	
	//Set horizontal period
	SSD1963_WriteCommand(SSD1963_SET_HORI_PERIOD);
	SSD1963_WriteData((TFT_HSYNC_PERIOD-1)>>8);
	SSD1963_WriteData((TFT_HSYNC_PERIOD-1) & 0xFF);
	SSD1963_WriteData((TFT_HSYNC_PULSE + TFT_HSYNC_BACK_PORCH-1)>>8);
	SSD1963_WriteData((TFT_HSYNC_PULSE + TFT_HSYNC_BACK_PORCH) & 0xFF);
	SSD1963_WriteData(TFT_HSYNC_PULSE-1);
	SSD1963_WriteData(0x00);			
	SSD1963_WriteData(0x00);
	SSD1963_WriteData(0x00);

	//Set vertical period
	SSD1963_WriteCommand(SSD1963_SET_VERT_PERIOD); 		
	SSD1963_WriteData((TFT_VSYNC_PERIOD-1)>>8);
	SSD1963_WriteData((TFT_VSYNC_PERIOD-1) & 0xFF);
	SSD1963_WriteData((TFT_VSYNC_PULSE + TFT_VSYNC_BACK_PORCH-1)>>8);
	SSD1963_WriteData((TFT_VSYNC_PULSE + TFT_VSYNC_BACK_PORCH-1) & 0xFF);
	SSD1963_WriteData(TFT_VSYNC_PULSE-1);
	SSD1963_WriteData(0x00);			
	SSD1963_WriteData(0x00);
	
	//Set pixel data interface
	SSD1963_WriteCommand(SSD1963_SET_PIXEL_DATA_INTERFACE);
	SSD1963_WriteData(SSD1963_PDI_16BIT565);
	
	// set address mode
	SSD1963_WriteCommand(SSD1963_SET_ADDRESS_MODE);
	SSD1963_WriteData(0x4E);

  // setting PWM for LED backlight
	SSD1963_WriteCommand(SSD1963_SET_PWM_CONF);
	SSD1963_WriteData(0x12);
	SSD1963_WriteData(0xFF);   // Set 0xFF for full and 0x00 for off
	SSD1963_WriteData(0x01);
	SSD1963_WriteData(0x00);
	SSD1963_WriteData(0x00);
	SSD1963_WriteData(0x00);
	
	// GPIO0,1,2,3 is output
	SSD1963_WriteCommand(SSD1963_SET_GPIO_CONF);
	SSD1963_WriteData(0x0F);
	SSD1963_WriteData(0x01);
	
	// set GPIO0 , 1 , 2, 3 = 1
	SSD1963_WriteCommand(SSD1963_SET_GPIO_VALUE);
	SSD1963_WriteData(0x0F);
	
	//SET display on
	SSD1963_ClearScreen(0);
	SSD1963_WriteCommand(SSD1963_SET_DISPLAY_ON);		
	
	// exit sleep mode
	SSD1963_WriteCommand(SSD1963_EXIT_SLEEP_MODE);
}
//=============================================================================
//
//=============================================================================
void SSD1963_SetArea(unsigned int sx, unsigned int ex, unsigned int sy, unsigned int ey)
{
	SSD1963_WriteCommand(SSD1963_SET_COLUMN_ADDRESS);	
	SSD1963_WriteData((sx >> 8) & 0xFF);
	SSD1963_WriteData((sx >> 0) & 0xFF);
	SSD1963_WriteData((ex >> 8) & 0xFF);
	SSD1963_WriteData((ex >> 0) & 0xFF);

	SSD1963_WriteCommand(SSD1963_SET_PAGE_ADDRESS);	
	SSD1963_WriteData((sy >> 8) & 0xFF);
	SSD1963_WriteData((sy >> 0) & 0xFF);
	SSD1963_WriteData((ey >> 8) & 0xFF);
	SSD1963_WriteData((ey >> 0) & 0xFF);
}
//=============================================================================
// Fill area of specified color
//=============================================================================
/*void SSD1963_FillArea(unsigned int sx, unsigned int ex, unsigned int sy, unsigned int ey, int color)
{
int i;
SSD1963_SetArea(sx, ex, sy, ey);
SSD1963_WriteCommand(SSD1963_WRITE_MEMORY_START);
for(i = 0; i < ((ex-sx+1)*(ey-sy+1)); i++)
	{
	SendData(color);
	}
}*/
//=============================================================================
// Fills whole screen specified color
//=============================================================================
void SSD1963_ClearScreen(uint16_t color)
{
	unsigned int x,y;
	SSD1963_SetArea(0, TFT_WIDTH-1 , 0, TFT_HEIGHT-1);
	SSD1963_WriteCommand(0x2c);
	for(x=0;x<TFT_WIDTH;x++)
		{
					for(y= 0;y<TFT_HEIGHT;y++)
									{
										SSD1963_WriteData(color);
									}
		}
}
//=============================================================================
//
//=============================================================================
void GLCD_SetPixel(uint16_t x, uint16_t y, uint16_t color)
{
	SSD1963_SetArea(x, x, y, y);
	SSD1963_WriteCommand(0x2c);
	SSD1963_WriteData(color);
	//SSD1963_WriteCommand(0x0);
}
//=============================================================================
/*******************************************************************************
 Display_Str: Display String   Input: X¡Y, Color, Mode, String  
*******************************************************************************/
/*
void Display_Str(unsigned short x0, unsigned short y0, unsigned long Color,uint16_t Bl_Color,char *s)
{ 
  signed short i, j, b,ii=0; 
  while (*s!=0) {
    unsigned const short *scanline=Char_Dot+((*s-0x22)*8);
    for(i=0;i<8;++i)
		{
      if((*s==0x20)||(*s==0x21)) b=0x0000;
      else b=scanline[i];
      if((*s==0x21)&&(i==4)) break;
      for(j=0;j<14;++j)
			{
        if(b&4) 
				{
          GLCD_SetPixel(TFT_WIDTH+8-x0-i,14+y0-j,Color);
        }
				else
				{
					GLCD_SetPixel(TFT_WIDTH+8-x0-i,14+y0-j,Bl_Color);
				}
        b>>=1;				
      }
			++ii;
    }
    if(*s==0x21) x0 +=4;       
    else  x0 += 8;             
    ++s;                           
  }
}
*/

void LCD_Show_Image(uint16_t x0,uint16_t y0, const uint16_t *code)
{
	uint32_t cnt_x = 0;	
	uint16_t w = *(code++);
	uint16_t h = *(code++);
		SSD1963_SetArea(x0, x0+w-1, y0, y0+h-1);
		SSD1963_WriteCommand(0x2c);
		for(cnt_x=0;cnt_x< h*w ;cnt_x++)
		//for(cnt_x=h*w-1;cnt_x>=0 ;cnt_x--)
		{			
				SSD1963_WriteData(*(code++));			
		}	
}

void LCD_Show_Image2(uint16_t x0,uint16_t y0, const unsigned char *code)
{
	uint32_t cnt_x = 0;	
	uint16_t w = *(code++);
	uint16_t h = *(code++);
		SSD1963_SetArea(x0, x0+w-1, y0, y0+h-1);
		SSD1963_WriteCommand(0x2c);
		for(cnt_x=0;cnt_x< h*w ;cnt_x++)
		{			
				SSD1963_WriteData(*(code++));			
		}	
}

void lcd_draw_vertical_line(uint16_t x0,uint16_t y0,uint16_t len,uint16_t w,uint16_t color)
{
	uint32_t cnt_x = 0;			
		SSD1963_SetArea(x0, x0+w-1, y0, y0+len-1);
		SSD1963_WriteCommand(0x2c);
		for(cnt_x=0;cnt_x< len*w ;cnt_x++)
		{			
				SSD1963_WriteData(color);			
		}	
}

void lcd_draw_horizental_line(uint16_t x0,uint16_t y0,uint16_t len,uint16_t w,uint16_t color)
{
	uint32_t cnt_x = 0;			
		SSD1963_SetArea(x0, x0+len-1, y0, y0+w-1);
		SSD1963_WriteCommand(0x2c);
		for(cnt_x=0;cnt_x< len*w ;cnt_x++)
		{			
				SSD1963_WriteData(color);			
		}	
}

void lcd_draw_rect(uint16_t x0,uint16_t y0,uint16_t d_x,uint16_t d_y,uint16_t w,uint16_t color)
{
	lcd_draw_vertical_line(x0,y0,d_y,w,color);
	lcd_draw_vertical_line(x0+d_x,y0,d_y,w,color);	
	lcd_draw_horizental_line(x0,y0,d_x,w,color);
	lcd_draw_horizental_line(x0,y0+d_y,d_x+w,w,color);
}
/*
uint8_t lcd_put_str(uint16_t x,uint16_t y,char * s,uint16_t fg_color,uint16_t bg_color)
{	
uint8_t font_height;
uint8_t first_ch;
uint8_t ch_number_in_font;
uint8_t ch_width;
uint16_t start_addr;
uint16_t lc_cnt=0;
uint8_t lc_temp;
uint8_t lc_cnt2=0;
uint8_t lc_cnt3=0;
uint8_t ch_num_in_str=strlen(s);
font_height = arial[1];
first_ch = arial[2];
ch_number_in_font = arial[3];	
	for(lc_cnt3=ch_num_in_str-1;lc_cnt3>=0;lc_cnt3--)
	{		
		if(*(s+lc_cnt3) < first_ch || *(s+lc_cnt3) > first_ch + ch_number_in_font) return 0;
		
		ch_width= arial[4 + *(s+lc_cnt3) - first_ch];
		start_addr = 4 + (uint16_t)ch_number_in_font;	
		for(lc_cnt=0;lc_cnt<*(s+lc_cnt3) - first_ch;lc_cnt++)
		{
			lc_temp = ((arial[4 +lc_cnt] - 1)/8)+1;	
			start_addr += (uint16_t)(font_height)*lc_temp;
		}
		
		SSD1963_SetArea(x,x+ch_width-1,y,y+font_height-1);
		SSD1963_WriteCommand(0x2c);	
		lc_temp = ((arial[4 + *(s+lc_cnt3) - first_ch] - 1)/8)+1;	
		for(lc_cnt=0;lc_cnt<font_height;lc_cnt++)
		{
			for(lc_cnt2=0;lc_cnt2<ch_width;lc_cnt2++)
			{
				if(arial[start_addr + lc_cnt * lc_temp + lc_cnt2/8] & (1 << (lc_cnt2 % 8))) 
				{
					SSD1963_WriteData(fg_color);
				}
				else
				{			
					SSD1963_WriteData(bg_color);			
				}
			}
		}
		x += ch_width;		
	}
}
*/
uint16_t str_whidth(char * s,const unsigned char * font)
{
uint8_t first_ch;
uint8_t ch_number_in_font;
uint8_t ch_width;
uint16_t start_addr;
uint16_t lc_cnt=0;
uint8_t lc_temp;
uint8_t lc_cnt2=0;
uint8_t lc_cnt3=0;
uint8_t ch_num_in_str=strlen(s);
first_ch = font[2];
ch_number_in_font = font[3];	
uint16_t lc_width=0;
	while(*s != 0)
	{		
		ch_width= font[4 + *(s+lc_cnt3) - first_ch];
		s++;
		lc_width += ch_width;		
	}
	return lc_width;
}

uint8_t lcd_put_str2(uint16_t x,uint16_t y,char * s,uint16_t fg_color,uint16_t bg_color,const unsigned char * font)
{	
uint8_t font_height;
uint8_t first_ch;
uint8_t ch_number_in_font;
uint8_t ch_width;
uint16_t start_addr;
uint16_t lc_cnt=0;
uint8_t lc_temp;
uint8_t lc_cnt2=0;
uint8_t lc_cnt3=0;
uint8_t ch_num_in_str=strlen(s);
font_height = font[1];
first_ch = font[2];
ch_number_in_font = font[3];	
	//for(lc_cnt3=ch_num_in_str-1;lc_cnt3>=0;lc_cnt3--)
	for(lc_cnt3=0;lc_cnt3<ch_num_in_str;lc_cnt3++)
	{		
		if(*(s+lc_cnt3) < first_ch || *(s+lc_cnt3) > first_ch + ch_number_in_font) return 0;
		
		ch_width= font[4 + *(s+lc_cnt3) - first_ch];
		start_addr = 4 + (uint16_t)ch_number_in_font;	
		for(lc_cnt=0;lc_cnt<*(s+lc_cnt3) - first_ch;lc_cnt++)
		{
			lc_temp = ((font[4 +lc_cnt] - 1)/8)+1;	
			start_addr += (uint16_t)(font_height)*lc_temp;
		}
		
		SSD1963_SetArea(x,x+ch_width-1,y,y+font_height-1);
		SSD1963_WriteCommand(0x2c);	
		lc_temp = ((font[4 + *(s+lc_cnt3) - first_ch] - 1)/8)+1;	
		for(lc_cnt=0;lc_cnt<font_height;lc_cnt++)
		{
			for(lc_cnt2=0;lc_cnt2<ch_width;lc_cnt2++)
			//for(lc_cnt2=ch_width-1;lc_cnt2>=0;lc_cnt2--)
			{
				//if( calibri[start_addr + lc_cnt * lc_temp + lc_cnt2/8] & (1 << (lc_cnt2 % 8)) )
				if( font[start_addr + lc_cnt * lc_temp + (ch_width-1-lc_cnt2)/8] & (1 << ((ch_width-1-lc_cnt2 )% 8)) )				
				{
					SSD1963_WriteData(fg_color);
				}
				else
				{			
					SSD1963_WriteData(bg_color);			
				}
			}
		}
		x += ch_width;		
	}
}



