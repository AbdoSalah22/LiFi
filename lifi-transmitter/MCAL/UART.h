#ifndef UART_H
#define UART_H

#include "GPIO.h"

#define CLKSPEED 16000000

#define UART0   0
#define UART1   1
#define UART2   2
#define UART3   3
#define UART4   4
#define UART5   5
#define UART6   6
#define UART7   7

#define FIFO_ENABLE     0x10
#define PARITY_ENABLE   0x02
#define FIFO_DISABLE     0x00
#define PARITY_DISABLE   0x00

#define WLEN_5          0x00
#define WLEN_6          0x20
#define WLEN_7          0x40
#define WLEN_8          0x60

void UART_init(uint32 uart, uint32 baud_rate, uint32 wlen, uint32 fifo, uint32 parity);

#endif //UART_H