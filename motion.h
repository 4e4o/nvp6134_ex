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
    u_int8_t sens;
} nvp6134_motion_sens;

typedef struct _nvp6134_motion_data_ {
    u_int8_t mode; // 1 - hold , 0 -real time
    u_int8_t motion;
} nvp6134_motion_data;

/********************************************************************
 *  external api
 ********************************************************************/
extern void nvp6134_motion_init(unsigned char ch, unsigned char onoff);
extern void nvp6134_get_motion_ch(nvp6134_motion_data*);
extern void nvp6134_motion_display(unsigned char ch, unsigned char onoff);
extern void nvp6134_motion_sensitivity(nvp6134_motion_sens*);
extern void nvp6134_motion_area_mask(nvp6134_motion_area* ma);

#endif	// end of _MOTION_H_
