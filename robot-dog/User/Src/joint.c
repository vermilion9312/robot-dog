/*
 * joint.c
 *
 *  Created on: Jun 4, 2025
 *      Author: vermi
 */


#include "joint.h"

static void set_angle(Joint* this, uint8_t angle)
{
    if (angle > 180) angle = 180;  // 범위 제한

    uint16_t ccr_min = this->pwm_range.ccr_min;
    uint16_t ccr_max = this->pwm_range.ccr_max;

    // 보간 계산: angle 0~180 → ccr_min~ccr_max
//    this->ccr_value = ccr_min + ((ccr_max - ccr_min) * angle) / 180;

    this->tim_typedef->CCR1 = ccr_min + ((ccr_max - ccr_min) * angle) / 180;
}

static Joint joint = {
		TIM1, { .ccr_min = 280, .ccr_max = 1250 }, set_angle
};

Joint* new_Joint(void)
{
	return &joint;
}
