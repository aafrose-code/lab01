#include "stm32f0xx.h"
extern void autotest();
extern void internal_clock();
void initb();
void initc();
void buttons(void);
void keypad(void);

int main(void) {
    autotest();
    initb();
    initc();
    /*while (1) {
        buttons();
    }*/
    /*while (1) {
        keypad();
    }*/
   for (;;);
}

void initb () {
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; //Enabling the RCC clock for Port B
    GPIOB->MODER &= ~0x0000F00F;//Although the default is input for the pins, this line will make sure to set the input for pins 0,4,8,9,10,11
    GPIOB->MODER |= 0x00005500;//Setting output for pins 8-11 while keeping 0 and 4 as inputs.
}
