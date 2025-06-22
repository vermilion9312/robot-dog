/*
 * gpio_config.h
 *
 *  Created on: Jun 20, 2025
 *      Author: vermi
 */

#ifndef INC_GPIO_CONFIG_H_
#define INC_GPIO_CONFIG_H_

#include <stdlib.h>
#include <stdbool.h>
#include "main.h"

typedef struct {
	GPIO_TypeDef* GPIOx;
	uint16_t      GPIO_Pin;
} GPIO_Config;

#endif /* INC_GPIO_CONFIG_H_ */
