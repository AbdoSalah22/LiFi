#ifndef GPTM_H
#define GPTM_H

#include "GPIO.h"

#define TIMER0      0x00
#define TIMER1      0x01
#define TIMER2      0x02
#define TIMER3      0x03
#define TIMER4      0x04
#define TIMER5      0x05

#define TA_DISABLE     0x00
#define TA_ENABLE      0x01

#define WIDTH16     0x04
#define WIDTH32     0x00

#define ONESHOT     0x01
#define PERIODIC    0x02
#define CAPTURE     0x03
#define CAPTURE_A   0x07

#define UPCOUNT     0x10
#define DOWNCOUNT   0x00

#define POSITIVE_EDGE   0x00
#define NEGATIVE_EDGE   0x04
#define BOTH_EDGES      0x0c

void TIMERA_init(uint32 timer, uint32 width, uint32 mode, uint32 direction, uint32 edge);
void TIMER1A_DELAY_MICRO(int time);

#endif //GPTM_H