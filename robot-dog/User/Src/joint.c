/*
 * joint.c
 *
 *  Created on: Jun 4, 2025
 *      Author: vermilion9312
 */


#include "joint.h"

static void set_angle(Joint* this, uint8_t angle)
{
    if (angle > 180) angle = 180;

    uint16_t ccr_min = this->pwm_range.ccr_min;
    uint16_t ccr_max = this->pwm_range.ccr_max;

    this->tim_typedef->CCR1 = ccr_min + ((ccr_max - ccr_min) * angle) / 180;
}

Joint* new_Joint(TIM_TypeDef* tim_typedefm, uint16_t ccr_min, uint16_t ccr_max)
{
	Joint* this = malloc(sizeof(Joint));

	this->tim_typedef       = tim_typedefm;
	this->pwm_range.ccr_min = ccr_min;
	this->pwm_range.ccr_max = ccr_max;
	this->set_angle         = set_angle;

	return this;
}
