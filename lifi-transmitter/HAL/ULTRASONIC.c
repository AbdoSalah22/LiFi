#include "ULTRASONIC.h"

uint32 ultrasonicDistance(void) {
    int lastEdge, thisEdge, distance;

    // Give 10us trigger pulse
    GPIO_PORTB_DATA_R &= ~(1 << 7);
    TIMER1A_DELAY_MILLI(10);
    GPIO_PORTB_DATA_R |= (1 << 7);
    TIMER1A_DELAY_MILLI(10);
    GPIO_PORTB_DATA_R &= ~(1 << 7);

    while (1) {
        TIMER0_ICR_R = 4;
        while ((TIMER0_RIS_R & 4) == 0);
        if (GPIO_readPin(PORTB, PIN6))
        {
            lastEdge = TIMER0_TAR_R;
            TIMER0_ICR_R = 4;
            while ((TIMER0_RIS_R & 4) == 0);
            thisEdge = TIMER0_TAR_R;

            distance = ((thisEdge - lastEdge) * 10625) / 10000000;
            return distance;
        }
    }
}
