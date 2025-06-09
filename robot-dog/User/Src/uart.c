/*
 * uart.c
 *
 *  Created on: Jun 5, 2025
 *      Author: vermilion9312
 */


#include "uart.h"

static void transmit(Uart* this)
{
	HAL_UART_Transmit_IT(this->huart, this->tx_buffer, sizeof(this->tx_buffer));
}

static bool receive(Uart* this)
{
	if (HAL_UARTEx_ReceiveToIdle_IT(this->huart, this->rx_buffer, sizeof(this->rx_buffer)) == HAL_OK)
	{
		return true;
	}

	return false;
}

Uart* new_Uart(UART_HandleTypeDef *huart)
{
	Uart* this = calloc(1, sizeof(Uart));

	this->huart    = huart;
	this->transmit = transmit;
	this->receive  = receive;

	return this;
}



