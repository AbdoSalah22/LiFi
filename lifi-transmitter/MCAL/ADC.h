#ifndef ADC_H
#define ADC_H

#include "GPIO.h"

#define ADC0    0
#define ADC1    1

#define SS3     3
#define SS2     2
#define SS1     1
#define SS0     0

#define SS3_ENABLE      0x08
#define SS2_ENABLE      0x04
#define SS1_ENABLE      0x02
#define SS0_ENABLE      0x01

void ADC_init(uint32 adc, uint32 port, uint32 pin, uint32 ss);
uint32 ADC_Read(uint32 adc);

#endif //ADC_H