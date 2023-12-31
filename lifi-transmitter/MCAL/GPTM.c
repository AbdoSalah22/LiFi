#include "GPTM.h"


void TIMERA_init(uint32 timer, uint32 width, uint32 mode, uint32 direction, uint32 edge){
    switch(timer){
        case 0:
        SYSCTL_RCGCTIMER_R |= 0x01;
        TIMER0_CTL_R &= TA_DISABLE;
        TIMER0_CFG_R = width;
        TIMER0_TAMR_R = mode;
        TIMER0_TAMR_R |= direction;
        TIMER0_CTL_R |= edge;
        TIMER0_CTL_R |= TA_ENABLE;
        break;

        default:
        //other cases to be implemented
        break;
    }
}


void TIMER1A_DELAY_MILLI(int time) {
    int i;
    SYSCTL_RCGCTIMER_R |= 2; /* enable clock to Timer Block 1 */
    TIMER1_CTL_R = 0; /* disable Timer before initialization */
    TIMER1_CFG_R = 0x04; /* 16-bit option */
    TIMER1_TAMR_R = 0x02; /* periodic mode and down-counter */
    TIMER1_TAILR_R = 16 - 1; /* TimerA interval load value reg */
    TIMER1_ICR_R = 0x1; /* clear the TimerA timeout flag */
    TIMER1_CTL_R |= 0x01; /* enable Timer A after initialization */

    for (i = 0; i < time; i++) {
        while ((TIMER1_RIS_R & 0x1) == 0) ; /* wait for TimerA timeout flag */
        TIMER1_ICR_R = 0x1; /* clear the TimerA timeout flag */
    }
}