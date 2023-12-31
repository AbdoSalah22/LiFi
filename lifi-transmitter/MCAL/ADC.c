#include "ADC.h"


void ADC_init(uint32 adc, uint32 port, uint32 pin, uint32 ss){
    switch (adc)
    {
    case 0:
        SYSCTL_RCGCADC_R |= 0x01;

        switch(port){
            case 'E':
                SYSCTL_RCGCGPIO_R |= 0x10;
                GPIO_PORTE_AFSEL_R |= (1 << pin);
                GPIO_PORTE_DEN_R &= ~(1 << pin);
                GPIO_PORTE_AMSEL_R |= (1 << pin);
                break;
        }

        switch(ss){
            case 3:
            ADC0_ACTSS_R &= ~SS3_ENABLE;
            ADC0_EMUX_R &= ~0xF000;
            ADC0_SSMUX3_R = 0;
            ADC0_SSCTL3_R |= (1<<1)|(1<<2);
            ADC0_ACTSS_R |= SS3_ENABLE;
            break;
        }
    break;
    
    default:
        //other cases to be implemented
        break;
    }
}


uint32 ADC_Read(uint32 adc) {
    switch (adc)
    {
    case 0:
        // Trigger ADC conversion
        ADC0_PSSI_R = 0x8;
        while ((ADC0_RIS_R & 0x8) == 0) {}
        uint32 result = ADC0_SSFIFO3_R;
        ADC0_ISC_R = 0x8;
        return result;
    break;
    
    default:
        //other cases to be implemented
    break;
    }
}