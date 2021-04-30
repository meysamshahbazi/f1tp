/*
 * menu_utils.c
 *
 *  Created on: Apr 29, 2021
 *      Author: meysam
 */

#include "menu_utils.h"
#include "myplot.h"







void drawMainMenu() {
	SSD1963_ClearScreen(COLOR_BLACK);

	myPlot(GEAR_X,GEAR_Y,COLOR_GRAY,COLOR_WHITE, gear_ch);
	myPlot(GEAR_DEC_X,GEAR_DEC_Y,COLOR_SILVER,BLACK, dec_ch);
	myPlot(GEAR_INC_X,GEAR_INC_Y,COLOR_SILVER,BLACK, inc_ch);

	myPlot(REEL_X,REEL_Y,COLOR_GREEN,BLACK, reel_ch);

	myPlot(TWO_X,TWO_Y,COLOR_BLUE,BLACK, two_ch);
	myPlot(THREE_X,THREE_Y,COLOR_BLUE,BLACK, three_ch);
	myPlot(FOUR_X,FOUR_Y,COLOR_BLUE,BLACK, four_ch);

	myPlot(CAMERA_X,CAMERA_Y,COLOR_NAVY,BLACK, camera_ch);
	myPlot(LEFT_X,LEFT_Y,COLOR_PURPLE,BLACK, left_ch);
	myPlot(RIGHT_X,RIGHT_Y,COLOR_PURPLE,BLACK, right_ch);
	myPlot(UP_X,UP_Y,COLOR_PURPLE,BLACK, up_ch);
	myPlot(DOWN_X,DOWN_Y,COLOR_PURPLE,BLACK, down_ch);

	myPlot(SWIP_UP_X,SWIP_UP_Y,COLOR_YELLOW,BLACK, swip_up_ch);
	myPlot(SWIP_DOWN_X,SWIP_DOWN_Y,COLOR_YELLOW,BLACK, swip_down_ch);
	myPlot(SWIP_LEFT_RIGHT_X,SWIP_LEFT_RIGHT_Y,COLOR_YELLOW,BLACK, swip_left_right_ch);


	myPlot(ZOOMIN_X,ZOOMIN_Y,COLOR_LIME,BLACK, zoomin_ch);
	myPlot(ZOONOUT_X,ZOOMOUT_Y,COLOR_LIME,BLACK, zoomout_ch);

	myPlot(LIGHTUP_X,LIGHTUP_Y,COLOR_LIME,BLACK, lightup_ch);
	myPlot(LIGHTDOWN_X,LIGHTDOWN_Y,COLOR_LIME,BLACK, lightdown_ch);

	myPlot(FLIPH_X,FLIPH_Y,COLOR_LIME,BLACK, fliph_ch);
	myPlot(FLIPV_X,FLIPV_Y,COLOR_LIME,BLACK, flipv_ch);

	myPlot(FOUCOSN_X,FOUCOSN_Y,COLOR_LIME,BLACK, focusn_ch);
	myPlot(FOUCOSP_X,FOUCOSP_Y,COLOR_LIME,BLACK, focusp_ch);


	lcd_draw_vertical_line(300,1,480,1,WHITE);
	lcd_draw_vertical_line(600,1,480,1,WHITE);

	lcd_draw_horizental_line(1,240,300,1,WHITE);
	lcd_draw_horizental_line(300,300,300,1,WHITE);
	lcd_draw_horizental_line(600,120,200,1,WHITE);
	lcd_draw_horizental_line(600,240,200,1,WHITE);
	lcd_draw_horizental_line(600,240,200,1,WHITE);
	lcd_draw_horizental_line(600,360,200,1,WHITE);


}



