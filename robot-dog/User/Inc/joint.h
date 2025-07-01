/*
 * joint.h
 *
 *  Created on: Jun 4, 2025
 *      Author: vermilion9312
 */

#ifndef INC_JOINT_H_
#define INC_JOINT_H_

#include "main.h"
#include "stm32f103xb.h"
#include <stdlib.h>

typedef enum {
	HIP,
	THIGH,
	KNEE
} JointType;

typedef struct {
	uint16_t ccr_min;
	uint16_t ccr_max;
} PWM_Range;


typedef struct _Joint Joint;

struct _Joint {
	TIM_HandleTypeDef *htim;
	uint32_t Channel;
	TIM_TypeDef* tim_typedef;
	PWM_Range pwm_range;
	void (* set_angle)(Joint*, uint8_t);
	void (* set_angle2)(Joint*, uint8_t);
	uint8_t current_angle;
};

Joint* new_Joint(TIM_TypeDef* tim_typedefm, uint16_t ccr_min, uint16_t ccr_max);

#endif /* INC_JOINT_H_ */
