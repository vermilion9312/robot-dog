/*
 * input.h
 *
 *  Created on: Jun 20, 2025
 *      Author: vermi
 */

#ifndef INC_INPUT_H_
#define INC_INPUT_H_

#include "gpio_config.h"

typedef enum {
	NOMAL_OPEN,
	NOMAL_CLOSE
} InputType;

typedef struct _Input Input;

struct _Input {
	GPIO_Config gpio_config;
	bool last_state;
	bool state;

	void (* update)(Input*, InputType);
	bool (* is_detected)(Input*);
	bool (* is_pressed)(Input*);
	bool (* on_rising_edge)(Input*);
	bool (* on_falling_edge)(Input*);
};

Input* new_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif /* INC_INPUT_H_ */
