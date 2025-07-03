/*
 * pwm.c
 *
 *  Created on: Jul 2, 2025
 *      Author: LeeJooHo
 */


#include "pwm.h"

static void set_ccr(PWM* this, uint32_t ccr)
{
	__HAL_TIM_SET_COMPARE(this->htim, this->Channel, ccr);
}

static void set_duty(PWM* this, float duty)
{
	if (duty < 0.0f) duty = 0.0f;
	if (duty > 1.0f) duty = 1.0f;

	uint32_t range = (uint32_t)(this->ccr_max - this->ccr_min);
	uint32_t ccr_value = this->ccr_min + (uint32_t)(range * duty);

	set_ccr(this, ccr_value);
}


PWM* new_PWM(TIM_HandleTypeDef *htim, uint32_t Channel, uint16_t ccr_min, uint16_t ccr_max)
{
	PWM* this = malloc(sizeof(PWM));

	this->htim    = htim;
	this->Channel = Channel;
	this->ccr_min = ccr_min;
	this->ccr_max = ccr_max;

	this->set_ccr  = set_ccr;
	this->set_duty = set_duty;

	return this;
}
