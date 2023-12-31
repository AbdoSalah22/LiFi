#include "GPIO.h"

void GPIO_init(uint8 port, uint32 pin, uint32 dtype, uint32 io)
{
  switch (port)
  {
  case 'A':
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
    while ((SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R0) == 0)
      ;

    GPIO_PORTA_LOCK_R = 0x4C4F434B;
    GPIO_PORTA_CR_R |= 1 << pin;
    GPIO_PORTA_DIR_R |= io << pin;

    if (dtype){
      GPIO_PORTA_DEN_R |= 1 << pin;
    }
    break;

  case 'B':
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
    while ((SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R1) == 0)
      ;

    GPIO_PORTB_LOCK_R = 0x4C4F434B;
    GPIO_PORTB_CR_R |= 1 << pin;
    GPIO_PORTB_DIR_R |= io << pin;

    if (dtype){
      GPIO_PORTB_DEN_R |= 1 << pin;
    }
    break;

  case 'C':
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;
    while ((SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R2) == 0)
      ;

    GPIO_PORTC_LOCK_R = 0x4C4F434B;
    GPIO_PORTC_CR_R |= 1 << pin;
    GPIO_PORTC_DIR_R |= io << pin;

    if (dtype){
      GPIO_PORTC_DEN_R |= 1 << pin;
    }
    break;

  case 'D':
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;
    while ((SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R3) == 0)
      ;

    GPIO_PORTD_LOCK_R = 0x4C4F434B;
    GPIO_PORTD_CR_R |= 1 << pin;
    GPIO_PORTD_DIR_R |= io << pin;

    if (dtype){
      GPIO_PORTD_DEN_R |= 1 << pin;
    }
    break;

  case 'E':
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
    while ((SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R4) == 0)
      ;

    GPIO_PORTE_LOCK_R = 0x4C4F434B;
    GPIO_PORTE_CR_R |= 1 << pin;
    GPIO_PORTE_DIR_R |= io << pin;

    if (dtype){
      GPIO_PORTE_DEN_R |= 1 << pin;
    }
    break;

  case 'F':
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
    while ((SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R5) == 0)
      ;

    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |= 1 << pin;
    GPIO_PORTF_DIR_R |= io << pin;

    if (dtype){
      GPIO_PORTF_DEN_R |= 1 << pin;
    }
    break;

  }
}

void GPIO_setPin(uint8 port, uint32 pin)
{
  switch (port)
  {
  case 'A':
    (GPIO_PORTA_DATA_R |= 1 << pin);
  case 'B':
    (GPIO_PORTB_DATA_R |= 1 << pin);
  case 'C':
    (GPIO_PORTC_DATA_R |= 1 << pin);
  case 'D':
    (GPIO_PORTD_DATA_R |= 1 << pin);
  case 'E':
    (GPIO_PORTE_DATA_R |= 1 << pin);
  case 'F':
    (GPIO_PORTF_DATA_R |= 1 << pin);
  }
}

void GPIO_clearPin(uint8 port, int pin)
{
  switch (port)
  {
  case 'A':
    (GPIO_PORTA_DATA_R &= ~(1 << pin));
    break;
  case 'B':
    (GPIO_PORTB_DATA_R &= ~(1 << pin));
    break;
  case 'C':
    (GPIO_PORTC_DATA_R &= ~(1 << pin));
    break;
  case 'D':
    (GPIO_PORTD_DATA_R &= ~(1 << pin));
    break;
  case 'E':
    (GPIO_PORTE_DATA_R &= ~(1 << pin));
    break;
  case 'F':
    (GPIO_PORTF_DATA_R &= ~(1 << pin));
    break;
  }
}

void GPIO_togglePin(uint8 port, uint32 pin)
{
  switch (port)
  {
  case 'A':
    (GPIO_PORTA_DATA_R ^= 1 << pin);
    break;
  case 'B':
    (GPIO_PORTB_DATA_R ^= 1 << pin);
    break;
  case 'C':
    (GPIO_PORTC_DATA_R ^= 1 << pin);
    break;
  case 'D':
    (GPIO_PORTD_DATA_R ^= 1 << pin);
    break;
  case 'E':
    (GPIO_PORTE_DATA_R ^= 1 << pin);
    break;
  case 'F':
    (GPIO_PORTF_DATA_R ^= 1 << pin);
    break;
  }
}

uint8 GPIO_readPin(uint8 port, uint32 pin)
{
  switch (port)
  {
  case 'A':
    return ((GPIO_PORTA_DATA_R >> pin) & 1);
    break;
  case 'B':
    return ((GPIO_PORTB_DATA_R >> pin) & 1);
    break;
  case 'C':
    return ((GPIO_PORTC_DATA_R >> pin) & 1);
    break;
  case 'D':
    return ((GPIO_PORTD_DATA_R >> pin) & 1);
    break;
  case 'E':
    return ((GPIO_PORTE_DATA_R >> pin) & 1);
    break;
  case 'F':
    return ((GPIO_PORTF_DATA_R >> pin) & 1);
    break;
  }
  return 0;
}

void GPIO_writePort(uint8 port, uint32 value)
{
  switch (port)
  {
  case 0:
    GPIO_PORTA_DATA_R = value;
    break;
  case 1:
    GPIO_PORTB_DATA_R = value;
    break;
  case 2:
    GPIO_PORTC_DATA_R = value;
    break;
  case 3:
    GPIO_PORTD_DATA_R = value;
    break;
  case 4:
    GPIO_PORTE_DATA_R = value;
    break;
  case 5:
    GPIO_PORTF_DATA_R = value;
    break;
  }
}

uint32 GPIO_readPort(uint8 port)
{
  switch (port)
  {
  case 'A':
    return GPIO_PORTA_DATA_R;
    break;
  case 'B':
    return GPIO_PORTB_DATA_R;
    break;
  case 'C':
    return GPIO_PORTC_DATA_R;
    break;
  case 'D':
    return GPIO_PORTD_DATA_R;
    break;
  case 'E':
    return GPIO_PORTE_DATA_R;
    break;
  case 'F':
    return GPIO_PORTF_DATA_R;
    break;
  }
  return 0;
}
