/********************************************************************************
*
*  Copyright (C) 2017 	NEXTCHIP Inc. All rights reserved.
*  Module		:  The decoder's motion detection header file
*  Description	:  Now, Not used
*  Author		:
*  Date         :
*  Version		: Version 2.0
*
********************************************************************************
*  History      :
*
*
********************************************************************************/
#ifndef _MOTION_H_
#define _MOTION_H_

#include <linux/types.h>

/********************************************************************
 *  define and enum
 ********************************************************************/

/********************************************************************
 *  structure
 ********************************************************************/
typedef struct _nvp6134_motion_area_ {
    u_int8_t ch;
    u_int8_t blockset[24];
} nvp6134_motion_area;

typedef struct _nvp6134_motion_sens_ {
    u_int8_t ch;
    /*
     *
     *  MOD_TSEN_x
     *  : Motion Temporal Sensitivity. ( x = channel number )
     *  The value ( the sum of the motion block ) bases on which it is determined
     *  whether motion is generated or not
     *  ( 0 -> 255 The greater the number, the less sensitive it gets)
     *
     */
    u_int8_t temporal_sens;
    /*
     *
     *  MOD_PSEN_x
     *  : Motion Pixel Sensitivity. Register that determines how much data input in
     *  the Motion block is used to search for motion
     *  ( x = channel number )
     *  0 : bypass
     *  1 : 1/2
     *  2 : 1/4
     *  3 : 1/8
     *
     */
    u_int8_t pixel_sens;

    /*
     *
     * Can't find description.
     *   ( 0 -> 255 The greater the number, the less sensitive it gets)
     *
     */
    u_int8_t brightness_sens;
} nvp6134_motion_sens;

typedef struct _nvp6134_motion_data_ {
    u_int8_t mode; // 1 - hold , 0 - real time
    u_int8_t motion;
} nvp6134_motion_data;

typedef struct _nvp6134_motion_display_ {
    u_int8_t ch;
    u_int8_t display;
} nvp6134_motion_display;

/********************************************************************
 *  external api
 ********************************************************************/
extern void nvp6134_motion_init(unsigned char ch, unsigned char onoff);
extern void nvp6134_get_motion_ch(nvp6134_motion_data*);
extern void nvp6134_motion_set_display(nvp6134_motion_display*);
extern void nvp6134_motion_sensitivity(nvp6134_motion_sens*);
extern void nvp6134_motion_area_mask(nvp6134_motion_area* ma);

#endif	// end of _MOTION_H_
