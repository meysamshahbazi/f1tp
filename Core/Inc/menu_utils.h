/*
 * menu_utils.h
 *
 *  Created on: Apr 29, 2021
 *      Author: meysam
 */

#ifndef INC_MENU_UTILS_H_
#define INC_MENU_UTILS_H_

#include "ssd1963_headerfile.h"
#include "tp.h"



#define GEAR_X 5
#define GEAR_Y 5
#define GEAR_DEC_X 200
#define GEAR_DEC_Y 150

#define GEAR_INC_X 200
#define GEAR_INC_Y 30


#define REEL_X 5
#define REEL_Y 245
#define CAMERA_X 390
#define CAMERA_Y 90

#define LEFT_X 315
#define LEFT_Y 135

#define RIGHT_X 525
#define RIGHT_Y 135
#define UP_X 420
#define UP_Y 15

#define DOWN_X 420
#define DOWN_Y 225

#define TWO_X 200
#define TWO_Y 250

#define THREE_X 200
#define THREE_Y 320

#define FOUR_X 200
#define FOUR_Y 390

#define SWIP_UP_X 320
#define SWIP_UP_Y 320

#define SWIP_DOWN_X 500
#define SWIP_DOWN_Y 320

#define SWIP_LEFT_RIGHT_X 410
#define SWIP_LEFT_RIGHT_Y 320



#define ZOONOUT_X 620
#define ZOOMOUT_Y 20

#define ZOOMIN_X 708
#define ZOOMIN_Y 20

#define FOUCOSP_X 620
#define FOUCOSP_Y 140

#define FOUCOSN_X 708
#define FOUCOSN_Y 140

#define LIGHTUP_X 620
#define LIGHTUP_Y 260

#define LIGHTDOWN_X 708
#define LIGHTDOWN_Y 260

#define FLIPV_X 620
#define FLIPV_Y 380


#define FLIPH_X 708
#define FLIPH_Y 380

#define DEFLT_GEAR_COLOR
#define PRESS_GEAR_COLOR
#define DEFLT_INC_COLOR
#define PRESS_INC_COLOR
#define DEFLT_DEC_COLOR
#define PRESS_DEC_COLOR
#define DEFLT_REEL_COLOR
#define PRESS_REEL_COLOR
#define DEFLT_2_COLOR
#define PRESS_2_COLOR
#define DEFLT_3_COLOR
#define PRESS_3_COLOR
#define DEFLT_4_COLOR
#define PRESS_4_COLOR
#define DEFLT_UP_COLOR
#define PRESS_UP_COLOR
#define DEFLT_DOWN_COLOR
#define PRESS_DOWN_COLOR
#define DEFLT_RIGHT_COLOR
#define PRESS_RIGHT_COLOR
#define DEFLT_LEFT_COLOR
#define PRESS_LEFT_COLOR
#define DEFLT_SWIP_UP_COLOR
#define PRESS_SWIP_UP_COLOR
#define DEFLT_SWIP_DOWN_COLOR
#define PRESS_SWIP_DOWN_COLOR
#define DEFLT_SWIP_LR_COLOR
#define PRESS_SWIP_LR_COLOR
#define DEFLT_ZOOMIN_COLOR
#define PRESS_ZOOMIN_COLOR
#define DEFLT_ZOOMOUT_COLOR
#define PRESS_ZOOMOUT_COLOR
#define DEFLT_FOCUSP_COLOR
#define PRESS_FOCUSP_COLOR
#define DEFLT_FOCUSN_COLOR
#define PRESS_FOCUSN_COLOR


#define DEFLT_LIGHT_UP_COLOR
#define PRESS_LIGHT_UP_COLOR

#define DEFLT_LIGHT_DOWN_COLOR
#define PRESS_LIGHT_DOWN_COLOR

#define DEFLT_FLIPV_COLOR
#define PRESS_FLIPV_COLOR

#define DEFLT_FLIPH_COLOR
#define PRESS_FLIPH_COLOR


uint8_t inRegion(uint16_t x,uint16_t y,uint16_t x0,uint16_t y0, uint16_t dx,uint16_t dy);

void drawMainMenu();

void putTexts();





#endif /* INC_MENU_UTILS_H_ */
