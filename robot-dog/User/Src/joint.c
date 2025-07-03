/*
 * joint.c
 *
 *  Created on: Jun 4, 2025
 *      Author: vermilion9312
 */


#include "joint.h"

#define tt 20

static void set_angle(Joint* this, float angle)
{
	if (angle < 0.0f  ) angle = 0.0f;
    if (angle > 180.0f) angle = 180.0f;

    uint16_t ccr_min = this->pwm->ccr_min;
    uint16_t ccr_max = this->pwm->ccr_max;

    uint32_t range = (uint32_t)(ccr_max - ccr_min);
    float ratio = angle / 180.0f;
    uint32_t ccr_value = ccr_min + (uint32_t)(range * ratio);

    this->pwm->set_ccr(this->pwm, ccr_value);
}

void set_angle_smooth(Joint* joint, float target_angle)
{
    if (target_angle > 180.0f) target_angle = 180.0f;

    uint8_t current_angle = joint->current_angle;

    if (current_angle == target_angle)
        return;

    int8_t step = (target_angle > current_angle) ? 1 : -1;

    for (uint8_t angle = current_angle; angle != target_angle; angle += step)
    {
        set_angle(joint, angle);
        HAL_Delay(tt);  // 너무 빠르면 5ms~ 너무 느리면 20ms
    }

    set_angle(joint, target_angle);  // 마지막 보정
    joint->current_angle = target_angle;
}

Joint* new_Joint(PWM* pwm)
{
	Joint* this = malloc(sizeof(Joint));

	this->pwm = pwm;
	this->set_angle         = set_angle_smooth;

	this->current_angle = 0;

	return this;
}
