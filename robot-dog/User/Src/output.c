/*
 * output.c
 *
 *  Created on: Jun 20, 2025
 *      Author: vermi
 */

#ifndef SRC_OUTPUT_C_
#define SRC_OUTPUT_C_

#include "output.h"

typedef struct _Output Output;

static void turn_on(Output* this)
{
	HAL_GPIO_WritePin(this->gpio_config.GPIOx, this->gpio_config.GPIO_Pin, GPIO_PIN_SET);
	this->state = true;
}

static void turn_off(Output* this)
{
	HAL_GPIO_WritePin(this->gpio_config.GPIOx, this->gpio_config.GPIO_Pin, GPIO_PIN_RESET);
	this->state = false;
}

static void toggle(Output* this)
{
	this->state ? this->turn_off(this) : this->turn_on(this);
}

static bool is_on(Output* this)
{
	return this->state;
}

static void test(Output* this)
{

}

Output* new_Output(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	Output* this = malloc(sizeof(Output));
	if (!this) return NULL;

	this->gpio_config.GPIOx    = GPIOx;
	this->gpio_config.GPIO_Pin = GPIO_Pin;
	this->state                = false;

	this->turn_on  = turn_on;
	this->turn_off = turn_off;
	this->toggle   = toggle;
	this->is_on    = is_on;

	this->turn_off(this);

	return this;
}

#endif /* SRC_OUTPUT_C_ */
