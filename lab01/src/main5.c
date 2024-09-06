#include "stm32f0xx.h"
extern void autotest();
extern void internal_clock();
void initb();
void initc();
void setn(int, int);
uint16_t readpin (uint16_t);
void buttons(void);

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
    /*
    setn(8,2093); //test it out
    */
   for (;;);
}

void initb () {
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; //Enabling the RCC clock for Port B
    GPIOB->MODER &= ~0x0000F00F;//Although the default is input for the pins, this line will make sure to set the input for pins 0,4,8,9,10,11
    GPIOB->MODER |= 0x00005500;//Setting output for pins 8-11 while keeping 0 and 4 as inputs.
}

void initc() {
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN; //Enabling the RCC clock for Port C
    GPIOC->MODER &= ~0x0000FF00; //Sets the input from 0-7 (will set the rest as either pull down or output pins)
    GPIOC->MODER |= 0x00005500; //Setting output for pins 4-7
    GPIOC->PUPDR &= 0x000000FF; //Pull down for pins 0-3
    GPIOC->PUPDR |= 0x000000FF; //Setting pins 0-3 for pull down
}
void setn(int pinNum, int pinValue) {//pinNum used to access the pins on the microcontroller and pinValue will either turn that pin on or off
    if (pinValue != 0) {//anything other than 0 would turn the pin on.
        GPIOB->BSRR = (1 << pinNum);//1 << pinNum will access the pin on the microcontroller through the bit mask 
    } else {
        GPIOB->BRR = (1 << pinNum);
    }
}
uint16_t readpin (uint16_t pinNum) {
    uint16_t pin = (1 << pinNum);//using uint16_t to read the 16 bits (basically the 16 pins)
    if (GPIOB->IDR & pin) {//IDR used to find the state of the pin. Basically this if statement is saying that if the pin state is high (1 << pinNum)
        return 1;
    } else {//low pin state (0 << pinNum)
        return 0;
    }
}