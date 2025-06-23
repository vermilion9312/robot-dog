/*
 * output.h
 *
 *  Created on: Jun 20, 2025
 *      Author: vermi
 */

#ifndef INC_OUTPUT_H_
#define INC_OUTPUT_H_

#include "gpio_config.h"

typedef struct _Output Output;

struct _Output {
	GPIO_Config gpio_config;
	bool state;

	void (* turn_on)(Output*);
	void (* turn_off)(Output*);
	void (* toggle)(Output*);
	bool (* is_on)(Output*);
};

Output* new_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif /* INC_OUTPUT_H_ */
