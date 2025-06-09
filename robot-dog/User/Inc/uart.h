/*
 * uart.h
 *
 *  Created on: Jun 5, 2025
 *      Author: vermilion9312
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"
#include <stdbool.h>
#include <stdlib.h>

#define BUFFER_SIZE 100

typedef struct _Uart Uart;

struct _Uart {
	UART_HandleTypeDef* huart;
	void (* transmit)(Uart*);
	bool (* receive)(Uart*);
	uint8_t tx_buffer[BUFFER_SIZE];
	uint8_t rx_buffer[BUFFER_SIZE];
};

Uart* new_Uart(UART_HandleTypeDef *huart);

#endif /* INC_UART_H_ */
