/*
 * myplot.h
 *
 *  Created on: Apr 29, 2021
 *      Author: meysam
 */

#ifndef INC_MYPLOT_H_
#define INC_MYPLOT_H_
#include "ssd1963_headerfile.h"

extern const unsigned char gear_ch[];
extern const unsigned char dec_ch[];

extern const unsigned char inc_ch[];
extern const unsigned char reel_ch[];
extern const unsigned char two_ch[];
extern const unsigned char three_ch[];
extern const unsigned char four_ch[];
extern const unsigned char camera_ch[];
extern const unsigned char down_ch[];
extern const unsigned char up_ch[];
extern const unsigned char left_ch[];
extern const unsigned char right_ch[];
extern const unsigned char swip_down_ch[];
extern const unsigned char swip_up_ch[];
extern const unsigned char swip_left_right_ch[];
extern const unsigned char focusp_ch[];
extern const unsigned char focusn_ch[];
extern const unsigned char zoomout_ch[];
extern const unsigned char zoomin_ch[];
extern const unsigned char lightdown_ch[];
extern const unsigned char lightup_ch[];
extern const unsigned char fliph_ch[];
extern const unsigned char flipv_ch[];


void myPlot(uint16_t x,uint16_t y,uint16_t fg_color,uint16_t bg_color,const unsigned char * img_ch);





#endif /* INC_MYPLOT_H_ */
