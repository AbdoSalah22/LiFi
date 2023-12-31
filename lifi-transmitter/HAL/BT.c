#include "BT.h"


void HC05_init(void) {
    UART_init(UART5, 9600, WLEN_8, FIFO_DISABLE, PARITY_DISABLE);
}


char BT_Read(void)
{
    char data;

    // wait until Rx buffer not full
    while ((UART5_FR_R & (1 << 4)) != 0);

    data = UART5_DR_R;
    return (unsigned char)data;
}

void BT_Write(unsigned char data)
{
    // wait until Tx buffer not full
    while ((UART5_FR_R & (1 << 5)) != 0);

    // buffer full, append a byte
    UART5_DR_R = data;
}

void BT_WriteStr(char *str)
{
    while (*str) {
        BT_Write(*(str++));
    }
}