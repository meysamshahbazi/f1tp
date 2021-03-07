//--------------------------------------------
// Modified by: Sadegh Mohammadi
// http://sadmonew.blogfa.com
// 1391/03/28
//--------------------------------------------
//=============================================================================
#include "stm32f1xx_hal.h"
#include "string.h"
#ifndef  ssd1963_gaurd
#define  ssd1963_gaurd
//=============================================================================
// Configuration
//=============================================================================

#define LCD_RAM    *(__IO uint16_t *) ((uint32_t)0x60020000)    	//µØÖ·¼Ä´æÆ÷
#define LCD_REG    *(__IO uint16_t *) ((uint32_t)0x60000000)	 	//Ö¸Áî¼Ä´æÆ÷

//===================
#define TFT_FPS 30ULL
#define TFT_WIDTH				800ULL
#define TFT_HSYNC_BACK_PORCH	88ULL
#define TFT_HSYNC_FRONT_PORCH	40ULL
#define TFT_HSYNC_PULSE			1ULL
	
#define TFT_HEIGHT				480ULL
#define TFT_VSYNC_BACK_PORCH	3ULL
#define TFT_VSYNC_FRONT_PORCH	3ULL
#define TFT_VSYNC_PULSE			3ULL


#define	TFT_HSYNC_PERIOD	(TFT_HSYNC_PULSE + TFT_HSYNC_BACK_PORCH + TFT_WIDTH  + TFT_HSYNC_FRONT_PORCH)
#define	TFT_VSYNC_PERIOD	(TFT_VSYNC_PULSE + TFT_VSYNC_BACK_PORCH + TFT_HEIGHT + TFT_VSYNC_FRONT_PORCH)
#define TFT_PCLK	(TFT_HSYNC_PERIOD * TFT_VSYNC_PERIOD * TFT_FPS)
#define LCD_FPR		((TFT_PCLK * 1048576)/100000000)

//=============================================================================
// SSD1963 commands
//=============================================================================
#define SSD1963_NOP						0x00
#define SSD1963_SOFT_RESET  			0x01
#define SSD1963_GET_POWER_MODE 			0x0A
#define SSD1963_GET_ADDRESS_MODE		0x0B
#define SSD1963_GET_DISPLAY_MODE		0x0D
#define SSD1963_GET_TEAR_EFFECT_STATUS 	0x0E
#define SSD1963_ENTER_SLEEP_MODE		0x10
#define SSD1963_EXIT_SLEEP_MODE			0x11
#define SSD1963_ENTER_PARTIAL_MODE		0x12
#define SSD1963_ENTER_NORMAL_MODE		0x13
#define SSD1963_EXIT_INVERT_MODE		0x20
#define SSD1963_ENTER_INVERT_MODE		0x21
#define SSD1963_SET_GAMMA_CURVE			0x26
#define SSD1963_SET_DISPLAY_OFF			0x28
#define SSD1963_SET_DISPLAY_ON			0x29
#define SSD1963_SET_COLUMN_ADDRESS		0x2A
#define SSD1963_SET_PAGE_ADDRESS		0x2B
#define SSD1963_WRITE_MEMORY_START		0x2C
#define SSD1963_READ_MEMORY_START		0x2E
#define SSD1963_SET_PARTIAL_AREA		0x30
#define SSD1963_SET_SCROLL_AREA			0x33
#define SSD1963_SET_TEAR_OFF			0x34
#define SSD1963_SET_REAR_ON				0x35
#define SSD1963_SET_ADDRESS_MODE		0x36
#define SSD1963_SET_SCROLL_START		0x37
#define SSD1963_EXIT_IDLE_MODE			0x38
#define SSD1963_ENTER_IDLE_MODE			0x39
#define SSD1963_SET_PIXEL_FORMAT		0x3A
#define SSD1963_WRITE_MEMORY_CONTINUE	0x3C
#define SSD1963_READ_MEMORY_CONTINUE	0x3E
#define SSD1963_SET_TEAR_SCANLINE		0x44
#define SSD1963_GET_SCANLINE			0x45
#define SSD1963_READ_DDB				0xA1
#define SSD1963_SET_LCD_MODE			0xB0
#define SSD1963_GET_LCD_MODE			0xB1
#define SSD1963_SET_HORI_PERIOD			0xB4
#define SSD1963_GET_HORI_PERIOD			0xB5
#define SSD1963_SET_VERT_PERIOD			0xB6
#define SSD1963_GET_VERT_PERIOD			0xB7
#define SSD1963_SET_GPIO_CONF			0xB8
#define SSD1963_GET_GPIO_CONF			0xB9
#define SSD1963_SET_GPIO_VALUE			0xBA
#define SSD1963_GET_GPIO_STATUS			0xBB
#define SSD1963_SET_POST_PROC			0xBC
#define SSD1963_GET_POST_PROC			0xBD
#define SSD1963_SET_PWM_CONF			0xBE
#define SSD1963_GET_PWM_CONF			0xBF
#define SSD1963_GET_LCD_GEN0			0xC0
#define SSD1963_SET_LCD_GEN0			0xC1
#define SSD1963_GET_LCD_GEN1			0xC2
#define SSD1963_SET_LCD_GEN1			0xC3
#define SSD1963_GET_LCD_GEN2			0xC4
#define SSD1963_SET_LCD_GEN2			0xC5
#define SSD1963_GET_LCD_GEN3			0xC6
#define SSD1963_SET_LCD_GEN3			0xC7
#define SSD1963_SET_GPIO0_ROP			0xC8
#define SSD1963_GET_GPIO0_ROP			0xC9
#define SSD1963_SET_GPIO1_ROP			0xCA
#define SSD1963_GET_GPIO1_ROP			0xCB
#define SSD1963_SET_GPIO2_ROP			0xCC
#define SSD1963_GET_GPIO2_ROP			0xCD
#define SSD1963_SET_GPIO3_ROP			0xCE
#define SSD1963_GET_GPIO3_ROP			0xCF
#define SSD1963_SET_DBC_CONF			0xD0
#define SSD1963_GET_DBC_CONF			0xD1
#define SSD1963_SET_DBC_TH				0xD4
#define SSD1963_GET_DBC_TH				0xD5
#define SSD1963_SET_PLL					0xE0
#define SSD1963_SET_PLL_MN				0xE2
#define SSD1963_GET_PLL_MN				0xE3
#define SSD1963_GET_PLL_STATUS			0xE4
#define SSD1963_SET_DEEP_SLEEP			0xE5
#define SSD1963_SET_LSHIFT_FREQ			0xE6
#define SSD1963_GET_LSHIFT_FREQ			0xE7
#define SSD1963_SET_PIXEL_DATA_INTERFACE 0xF0
	#define SSD1963_PDI_8BIT			0
	#define SSD1963_PDI_12BIT			1
	#define SSD1963_PDI_16BIT			2
	#define SSD1963_PDI_16BIT565		3
	#define SSD1963_PDI_18BIT			4
	#define SSD1963_PDI_24BIT			5
	#define SSD1963_PDI_9BIT			6
#define SSD1963_GET_PIXEL_DATA_INTERFACE 0xF1


//-----------------color----------------------------------
#define RED	  0XF800
#define GREEN 0xF81F //0X07E0
#define GREEN1 0x07C0
#define BLUE  0xFFE0 //0X001F  
#define BRED  0XF81F
#define GRED  0XFFE0
#define GBLUE 0X07FF
#define WHITE 0XFFFF 
#define BLACK 0X0000 
#define BROWN 0XBC40 
#define BRRED 0XFC07 
#define GRAY  0X8430 
#define LGRAY 0XC618 
#define YELOW 0x07FF
//----------------------------------------------------
/*
#define RED				0xf800  	
#define GREEN			0x7e0
#define BLUE	  	0x1f
#define BLACK			0x00
#define WHITE			0xffff
#define GRAY			0xc618
*/

// Translates a 24-bit RGB color to RGB565
#define TRANSLATE24BIT_TO_RGB565(c)    ((((c) & 0x00ff0000) >> 19) |               \
                                 ((((c) & 0x0000ff00) >> 5) & 0x000007e0) | \
                                 ((((c) & 0x000000ff) << 8) & 0x0000f800))

// Define a basic set of 24bit colors, based on the standard "websafe" set BGR
#define COLOR24_AQUA	0xFFFF00 //0x00FFFF rgb
#define COLOR24_BLUE 	0xFF0000 	
#define COLOR24_TORGU 0xE8A200
#define COLOR24_GREY	0x808080 // TODO: cahnge format from rgb to bgr
#define COLOR24_NAVY 	0x000080 	
#define COLOR24_SILVER 	0xC0C0C0
#define COLOR24_BLACK 	0x000000 	
#define COLOR24_GREEN 	0x008000 	
#define COLOR24_OLIVE 	0x808000 	
#define COLOR24_TEAL 	0x008080
#define COLOR24_LIME 	0x00FF00 	
#define COLOR24_PURPLE 	0x800080 	
#define COLOR24_WHITE 	0xFFFFFF
#define COLOR24_FUCHSIA	0xFF00FF 	
#define COLOR24_MAROON	0x800000 	
#define COLOR24_RED 	0xFF0000
#define COLOR24_YELLOW 	0xFFFF00

// Create a set of RGB565 colors that can be used directly within code
#define COLOR_AQUA TRANSLATE24BIT_TO_RGB565(COLOR24_AQUA)
#define COLOR_GREY	TRANSLATE24BIT_TO_RGB565(COLOR24_GREY)
#define COLOR_NAVY	TRANSLATE24BIT_TO_RGB565(COLOR24_NAVY) 	
#define COLOR_SILVER 	TRANSLATE24BIT_TO_RGB565(COLOR24_SILVER)
#define COLOR_BLACK 	TRANSLATE24BIT_TO_RGB565(COLOR24_BLACK) 	
#define COLOR_GREEN 	TRANSLATE24BIT_TO_RGB565(COLOR24_GREEN) 	
#define COLOR_OLIVE 	TRANSLATE24BIT_TO_RGB565(COLOR24_OLIVE) 	
#define COLOR_TEAL 		TRANSLATE24BIT_TO_RGB565(COLOR24_TEAL)
#define COLOR_BLUE 		TRANSLATE24BIT_TO_RGB565(COLOR24_BLUE) 	
#define COLOR_LIME 		TRANSLATE24BIT_TO_RGB565(COLOR24_LIME) 	
#define COLOR_PURPLE 	TRANSLATE24BIT_TO_RGB565(COLOR24_PURPLE) 	
#define COLOR_WHITE 	TRANSLATE24BIT_TO_RGB565(COLOR24_WHITE)
#define COLOR_FUCHSIA	TRANSLATE24BIT_TO_RGB565(COLOR24_FUCHSIA) 	
#define COLOR_MAROON	TRANSLATE24BIT_TO_RGB565(COLOR24_MAROON)	
#define COLOR_RED 		TRANSLATE24BIT_TO_RGB565(COLOR24_RED)
#define COLOR_YELLOW 	TRANSLATE24BIT_TO_RGB565(COLOR24_YELLOW)
#define COLOR_TORGU TRANSLATE24BIT_TO_RGB565(COLOR24_TORGU)

void SSD1963_ClearScreen(uint16_t color);
void SSD1963_WriteCommand(uint16_t regsiter);
void SSD1963_WriteData(uint16_t data);
void SSD1963_Init (void);
void SSD1963_SetArea(unsigned int sx, unsigned int ex, unsigned int sy, unsigned int ey);
//void SSD1963_ClearScreen(unsigned long color);
void GLCD_SetPixel(uint16_t x, uint16_t y, uint16_t color);
//void Display_Str(unsigned short x0, unsigned short y0, unsigned long Color,uint16_t Bl_Color,char *s);
void LCD_Show_Image(uint16_t x0,uint16_t y0, const uint16_t *code);
void LCD_Show_Image2(uint16_t x0,uint16_t y0, const unsigned char *code);

void lcd_draw_vertical_line(uint16_t x0,uint16_t y0,uint16_t len,uint16_t w,uint16_t color);
void lcd_draw_horizental_line(uint16_t x0,uint16_t y0,uint16_t len,uint16_t w,uint16_t color);
void lcd_draw_rect(uint16_t x0,uint16_t y0,uint16_t d_x,uint16_t d_y,uint16_t w,uint16_t color);
//uint8_t lcd_put_str(uint16_t x,uint16_t y,char * s,uint16_t fg_color,uint16_t bg_color);
uint8_t lcd_put_str2(uint16_t x,uint16_t y,char * s,uint16_t fg_color,uint16_t bg_color,const unsigned char * font);
uint16_t str_whidth(char * s,const unsigned char * font);
#endif
