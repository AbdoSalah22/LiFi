#include "INC/tm4c123gh6pm.h"
#include "INC/delay.h"
#include "HAL/BT.h"
#include "HAL/LED.h"
#include "HAL/ULTRASONIC.h"
#include "MCAL/ADC.h"
#include "MCAL/GPTM.h"
#include <stdio.h>

volatile uint32 distance, flameValue;
volatile uint8 state = 0;

void PortA_Init(void);
void PortB_Init(void);
void SWITCH_init(void);
void PortA_Handler(void);
void PortF_Handler(void);


int main() {
    LED_init();
    SWITCH_init();
    ADC_init(ADC0, PORTE, PIN3, SS3);   //Enable ADC0 and Port E connected to analog flame sensor
    PortB_Init();
    PortA_Init();
    HC05_init();
    TIMERA_init(TIMER0, WIDTH16, CAPTURE_A, UPCOUNT, BOTH_EDGES);

    while (1) {
      if(state){
        GPIO_PORTA_IM_R |= (1 << 2);   // Enable interrupt on PA2
        
        flameValue = ADC_Read(ADC0);
        //printf("Flame: %d\n", flameValue);
        if (flameValue < 512){
            BT_WriteStr("FLAME!\n");
            blueOn();
            delayMs(20);
            blueOff();
        }
        delayMs(500);

        distance = ultrasonicDistance();
        //printf("Sonic: %d\n", distance);
        if(distance < 15){
            BT_WriteStr("SONIC!\n");
            blueOn();
            delayMs(40);
            blueOff();
        }
        delayMs(500);   
      }
        else{
        GPIO_PORTA_IM_R &= ~(1 << 2);   // Disable interrupt on PA2
        __asm("   wfi");
        }
      
    }
}


//Custom initialization of port A pin 2 for magnetic sensor and enable interrupts manually
void PortA_Init(void){
    // Enable clock to Port A
    SYSCTL_RCGCGPIO_R |= (1 << 0);

    // Configure PA2 as input for the sensor
    GPIO_PORTA_DIR_R &= ~(1 << 2);
    GPIO_PORTA_DEN_R |= (1 << 2);

    // Enable interrupts on PA2
    GPIO_PORTA_IS_R &= ~(1 << 2);  // Set PA2 as edge-sensitive
    GPIO_PORTA_IBE_R &= ~(1 << 2); // Set PA2 as single edge
    GPIO_PORTA_IEV_R &= ~(1 << 2); // Set PA2 to trigger on falling edge
    GPIO_PORTA_ICR_R = (1 << 2);   // Clear any existing interrupt
    GPIO_PORTA_IM_R |= (1 << 2);   // Enable interrupt on PA2

    // Set the interrupt priority for Port A (adjust as needed)
    NVIC_PRI0_R = (NVIC_PRI0_R & 0xFFFFFF00) | 0x00000040;

    // Enable the interrupt for Port A
    NVIC_EN0_R |= (1 << 0);
}


//Custom initialization of port B to use ultrasonic sensor
void PortB_Init(void){
    // Port B for Trigger and Echo
    SYSCTL_RCGCGPIO_R |= 2;      /* enable clock to PORTB */

    GPIO_PORTB_DIR_R &= ~0x40;   /* make PB6 an input pin */
    GPIO_PORTB_DEN_R |= 0x40;    /* make PB6 as a digital pin */
    GPIO_PORTB_AFSEL_R |= 0x40;  /* use PB6 alternate function */
    GPIO_PORTB_PCTL_R &= ~0x0F000000;  /* configure PB6 for T0CCP0 */
    GPIO_PORTB_PCTL_R |= 0x07000000;

    GPIO_PORTB_DIR_R |= 0x80;   /* set PB7 as a digital output pin */
    GPIO_PORTB_DEN_R |= 0x80;   /* make PB7 as a digital pin */
}


// Custom initialization of PF0 and PF4 with interrupts
void SWITCH_init(void) {
    // Enable the clock to Port F
    SYSCTL_RCGCGPIO_R |= 0x20;

    // Allow time for clock to stabilize
    while ((SYSCTL_PRGPIO_R & 0x20) == 0) {}

    GPIO_PORTF_DIR_R &= ~0x11;
    GPIO_PORTF_DEN_R |= 0x11;
    
    // Enable internal pull-up for PF4 and PF0
    GPIO_PORTF_PUR_R |= 0x11;

    // Configure PF4 and PF0 to trigger interrupts on both edges
    GPIO_PORTF_IS_R &= ~0x11;      // Edge-sensitive
    GPIO_PORTF_IBE_R |= 0x11;      // Both edges trigger
    GPIO_PORTF_ICR_R = 0x11;       // Clear existing interrupts
    GPIO_PORTF_IM_R |= 0x11;       // Enable interrupts on PF4 and PF0

    // Set the interrupt priority (adjust as needed)
    NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF00FFFF) | 0x00A00000;

    // Enable Port F interrupt in NVIC
    NVIC_EN0_R |= 0x40000000;
}


//ISR for port A
void PortA_Handler(void) {
    // Check if the interrupt is triggered by the specific pin (e.g., PA2)
    if (GPIO_PORTA_MIS_R & (1 << 2)) {
        // Clear the interrupt flag
        GPIO_PORTA_ICR_R = (1 << 2);

        GPIO_PORTF_DATA_R ^= (1 << 2);
        delayMs(80);
        GPIO_PORTF_DATA_R &= ~(1 << 2);        
        BT_WriteStr("MAGNET!\n");
    }
}


//ISR for Port F
void PortF_Handler(void) {
    // Check if the interrupt is triggered by switch SW1 (PF4)
    if (GPIO_PORTF_MIS_R & 0x10) {
        GPIO_PORTF_ICR_R = 0x10;
        //SysCtlDelay(4000000); // Adjust as needed for your system clock
        //GPIO_PORTF_DATA_R ^= 0x08;
        state = 1;
    }

    // Check if the interrupt is triggered by switch SW2 (PF0)
    else if (GPIO_PORTF_MIS_R & 0x01) {
        GPIO_PORTF_ICR_R = 0x01;
        //SysCtlDelay(4000000); // Adjust as needed for your system clock
        //GPIO_PORTF_DATA_R ^= 0x02;
        state = 0;
    }
}