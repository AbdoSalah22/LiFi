#ifndef LED_H
#define LED_H

#include "../MCAL/GPIO.h"

#define RED_LED PIN1
#define BLUE_LED PIN2
#define GREEN_LED PIN3


void LED_init(void);

void toggleRed(void);
void toggleBlue(void);
void toggleGreen(void);

void redOn(void);
void blueOn(void);
void greenOn(void);
void whiteOn(void);

void redOff(void);
void blueOff(void);
void greenOff(void);
void whiteOff(void);


#endif //LED_H