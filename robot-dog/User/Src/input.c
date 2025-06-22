/*
 * input.c
 *
 *  Created on: Jun 20, 2025
 *      Author: vermi
 */

#include "input.h"

static void update(Input* this, InputType input_type)
{
	this->last_state = this->state;

	if (input_type == NOMAL_OPEN)
	{
		this->state = !HAL_GPIO_ReadPin(this->gpio_config.GPIOx, this->gpio_config.GPIO_Pin);
		return;
	}

	if (input_type == NOMAL_CLOSE)
	{
		this->state = HAL_GPIO_ReadPin(this->gpio_config.GPIOx, this->gpio_config.GPIO_Pin);
	}
}

static bool is_on(Input* this)
{
	return this->state;
}

static bool on_rising_edge(Input* this)
{
	if (!this->last_state && this->state)
	{
		return true;
	}

	return false;
}

static bool on_falling_edge(Input* this)
{
	if (this->last_state && !this->state)
	{
		return true;
	}

	return false;
}

Input* new_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	Input* this = malloc(sizeof(Input));

	this->gpio_config.GPIOx    = GPIOx;
	this->gpio_config.GPIO_Pin = GPIO_Pin;
	this->last_state           = false;
	this->state                = false;

	this->update          = update;
	this->is_detected     = is_on;
	this->is_pressed      = is_on;
	this->on_rising_edge  = on_rising_edge;
	this->on_falling_edge = on_falling_edge;

	return this;
}



