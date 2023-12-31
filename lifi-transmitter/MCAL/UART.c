#include "UART.h"


void UART_init(uint32 uart, uint32 baud_rate, uint32 wlen, uint32 fifo, uint32 parity){
    float32 full_baud_rate = (float)CLKSPEED / (16 * baud_rate);
    uint32 int_baud_rate = (uint16)full_baud_rate;
    uint32 frac_baud_rate_int = (uint8)((full_baud_rate - int_baud_rate) * 64 + 0.5);
    switch(uart){
        case 5:
        SYSCTL_RCGCUART_R |= 0x20;
        SYSCTL_RCGCGPIO_R |= 0x10;

        UART5_CTL_R &= ~0x01;
        UART5_IBRD_R = int_baud_rate;
        UART5_FBRD_R = frac_baud_rate_int;
        UART5_CC_R = 0x00;

        if (fifo) UART5_LCRH_R |= fifo;
        if (parity) UART5_LCRH_R |= parity;
        UART5_LCRH_R |= wlen;

        // enable UART5 module, Rx and Tx
        UART5_CTL_R = 0x301;

        // GPIO configuration for PE4/Rx and PE5/Tx
        SYSCTL_RCGCGPIO_R |= 0x10;
        GPIO_PORTE_DEN_R = 0x30;
        GPIO_PORTE_AFSEL_R = 0x30;
        GPIO_PORTE_AMSEL_R = 0;
        GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0xFF00FFFF) | 0x00110000; // configure PE4 and PE5 for UART
        break;

        default:
        //other cases to be implemented
        break;
    }

}
