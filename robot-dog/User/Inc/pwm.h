/*
 * pwm.h
 *
 *  Created on: Jul 2, 2025
 *      Author: LeeJooHo
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

#include "stm32f1xx_hal.h"
#include <stdlib.h>


typedef struct _PWM PWM;

struct _PWM {
	TIM_HandleTypeDef *htim;
	uint32_t           Channel;
	uint16_t           ccr_min;
	uint16_t           ccr_max;

	void (* set_ccr)(PWM*, uint32_t);
	void (* set_duty)(PWM*, float);
};

PWM* new_PWM(TIM_HandleTypeDef *htim, uint32_t Channel, uint16_t ccr_min, uint16_t ccr_max);

#endif /* INC_PWM_H_ */
