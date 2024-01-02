#include "SYSTICK.h"

//#define NVIC_ST_CTRL_COUNT      0x00010000  // Count Flag
//#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
//#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt Enable
//#define NVIC_ST_CTRL_ENABLE     0x00000001  // Enable


void SysTickDisable(void) {
    NVIC_ST_CTRL_R &= ~(NVIC_ST_CTRL_ENABLE);
}

void SysTickEnable(void) {
    NVIC_ST_CTRL_R |= NVIC_ST_CTRL_ENABLE;
}

void SysTickClkSrc(void){
    NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC;
    // Should be modified to enable application to choose any clock source
}

void SysTickInterruptDisable(void) {
    NVIC_ST_CTRL_R &= ~(NVIC_ST_CTRL_INTEN);
}

void SysTickInterruptEnable(void) {
    NVIC_ST_CTRL_R |= (NVIC_ST_CTRL_INTEN);
}

uint32 SysTickPeriodGet(void) {
    return NVIC_ST_RELOAD_R;
}

void SysTickPeriodSet(uint32 msDelay) {
    NVIC_ST_RELOAD_R = msDelay * (uint32)(FREQUENCY/1000) - 1;
}

uint32 SysTickValueGet(void) {
    return NVIC_ST_CURRENT_R;
}

uint8 SysTick_Is_Time_out(void) {
    return (NVIC_ST_CTRL_R & (NVIC_ST_CTRL_COUNT)) != 0;  // Check if the COUNTFLAG is set
}

void SysTick_delayMs(uint32 ms) {
    SysTickDisable();
    SysTickPeriodSet(ms);
    SysTickClkSrc();
    SysTickEnable();
    while (!SysTick_Is_Time_out()) {}
}
