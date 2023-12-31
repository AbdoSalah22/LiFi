#ifndef GPIO_H
#define GPIO_H

#include "../INC/tm4c123gh6pm.h"
#include "../INC/types.h"

#define PORTA 'A'
#define PORTB 'B'
#define PORTC 'C'
#define PORTD 'D'
#define PORTE 'E'
#define PORTF 'F'

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

#define DIGITAL 1
#define ANALOG 0

#define UP 1
#define DOWN 0

#define INPUT 0
#define OUTPUT 1

void GPIO_init(uint8 port, uint32 pin, uint32 dtype, uint32 io);
void GPIO_setPin(uint8 port, uint32 pin);
void GPIO_clearPin(uint8 port, int pin);
void GPIO_togglePin(uint8 port, uint32 pin);
uint8 GPIO_readPin(uint8 port, uint32 pin);

void GPIO_writePort(uint8 port, uint32 value);
uint32 GPIO_readPort(uint8 port);


#endif //GPIO_H