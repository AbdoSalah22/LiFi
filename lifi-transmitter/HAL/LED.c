#include "LED.h"


void LED_init(void){
    GPIO_init(PORTF, PIN1, DIGITAL, OUTPUT);
    GPIO_init(PORTF, PIN2, DIGITAL, OUTPUT);
    GPIO_init(PORTF, PIN3, DIGITAL, OUTPUT);
}


void toggleRed(void){
    GPIO_togglePin(PORTF, RED_LED);
}

void toggleBlue(void){
    GPIO_togglePin(PORTF, BLUE_LED);
}

void toggleGreen(void){
    GPIO_togglePin(PORTF, GREEN_LED);
}


void redOn(void){
    GPIO_setPin(PORTF, RED_LED);
}

void blueOn(void){
    GPIO_setPin(PORTF, BLUE_LED);
}

void greenOn(void){
    GPIO_setPin(PORTF, GREEN_LED);
}

void whiteOn(void){
    redOn();
    blueOn();
    greenOn();
}


void redOff(void){
    GPIO_clearPin(PORTF, RED_LED);
}

void blueOff(void){
    GPIO_clearPin(PORTF, BLUE_LED);
}

void greenOff(void){
    GPIO_clearPin(PORTF, GREEN_LED);
}

void whiteOff(void){
    redOff();
    blueOff();
    greenOff();
}
