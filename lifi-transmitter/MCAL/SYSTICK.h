#ifndef SYSTICK_H
#define SYSTICK_H

#include "GPIO.h"

#define FREQUENCY 16000000

void SysTickDisable(void);
void SysTickEnable(void);
void SysTickClkSrc(void);
void SysTickInterruptDisable(void);
void SysTickInterruptEnable(void);
uint32 SysTickPeriodGet(void);
void SysTickPeriodSet(uint32 msDelay);
uint32 SysTickValueGet(void);
uint8 SysTick_Is_Time_out(void);
void SysTick_delayMs(uint32 ms);

#endif  // SYSTICK_H
