/*
 * joint.h
 *
 *  Created on: Jun 4, 2025
 *      Author: vermi
 */

#ifndef INC_JOINT_H_
#define INC_JOINT_H_

#include "main.h"
#include "stm32f103xb.h"

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
	TIM_TypeDef* tim_typedef;
	PWM_Range pwm_range;
	void (* set_angle)(Joint*, uint8_t);
};

Joint* new_Joint(void);

#endif /* INC_JOINT_H_ */
