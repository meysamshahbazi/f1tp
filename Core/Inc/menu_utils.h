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
#define GEAR_DEC_Y 165

#define GEAR_INC_X 200
#define GEAR_INC_Y 15


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
#define ZOOMOUT_Y 30

#define ZOOMIN_X 708
#define ZOOMIN_Y 30

#define FOUCOSP_X 620
#define FOUCOSP_Y 150

#define FOUCOSN_X 708
#define FOUCOSN_Y 150

#define LIGHTUP_X 620
#define LIGHTUP_Y 270

#define LIGHTDOWN_X 708
#define LIGHTDOWN_Y 270

#define FLIPV_X 620
#define FLIPV_Y 390


#define FLIPH_X 708
#define FLIPH_Y 390



uint8_t inRegion(uint16_t x,uint16_t y,uint16_t x0,uint16_t y0, uint16_t dx,uint16_t dy);

void drawMainMenu();

void putTexts();





#endif /* INC_MENU_UTILS_H_ */
