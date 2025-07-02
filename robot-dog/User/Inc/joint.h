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
#include "pwm.h"

typedef enum {
	HIP,
	THIGH,
	KNEE
} JointType;



typedef struct _Joint Joint;

struct _Joint {
	PWM* pwm;
	void (* set_angle)(Joint*, uint8_t);
	uint8_t current_angle;
};

Joint* new_Joint(TIM_TypeDef* tim_typedefm, uint16_t ccr_min, uint16_t ccr_max);

#endif /* INC_JOINT_H_ */
