/*
 * joint.c
 *
 *  Created on: Jun 4, 2025
 *      Author: vermilion9312
 */


#include "joint.h"

#define tt 30

static void set_angle(Joint* this, uint8_t angle)
{
    if (angle > 180) angle = 180;

    uint16_t ccr_min = this->pwm_range.ccr_min;
    uint16_t ccr_max = this->pwm_range.ccr_max;

    this->tim_typedef->CCR1 = ccr_min + ((ccr_max - ccr_min) * angle) / 180;

}

static void set_angle2(Joint* this, uint8_t angle)
{
    if (angle > 180) angle = 180;

    uint16_t ccr_min = this->pwm_range.ccr_min;
    uint16_t ccr_max = this->pwm_range.ccr_max;

    this->tim_typedef->CCR2 = ccr_min + ((ccr_max - ccr_min) * angle) / 180;

}

void set_angle_smooth(Joint* joint, uint8_t target_angle)
{
    if (target_angle > 180) target_angle = 180;

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

void set_angle_smooth2(Joint* joint, uint8_t target_angle)
{
    if (target_angle > 180) target_angle = 180;

    uint8_t current_angle = joint->current_angle;

    if (current_angle == target_angle)
        return;

    int8_t step = (target_angle > current_angle) ? 1 : -1;

    for (uint8_t angle = current_angle; angle != target_angle; angle += step)
    {
        set_angle2(joint, angle);
        HAL_Delay(tt);  // 너무 빠르면 5ms~ 너무 느리면 20ms
    }

    set_angle2(joint, target_angle);  // 마지막 보정
    joint->current_angle = target_angle;
}

Joint* new_Joint(TIM_TypeDef* tim_typedefm, uint16_t ccr_min, uint16_t ccr_max)
{
	Joint* this = malloc(sizeof(Joint));

	this->tim_typedef       = tim_typedefm;
	this->pwm_range.ccr_min = ccr_min;
	this->pwm_range.ccr_max = ccr_max;
	this->set_angle         = set_angle_smooth;
	this->set_angle2         = set_angle_smooth2;
	this->current_angle = 0;

	return this;
}
