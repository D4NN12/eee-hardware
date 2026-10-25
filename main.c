#include <stdint.h> // Standard C integers (built into the compiler, never fails)

/* 1. Define the exact physical memory addresses on the STM32F446RE chip */
#define RCC_AHB1ENR   (*(volatile uint32_t *)0x40023830) // Clock Enable Register
#define GPIOA_MODER   (*(volatile uint32_t *)0x40020000) // Pin Mode Register
#define GPIOA_BSRR    (*(volatile uint32_t *)0x40020018) // Pin Output Set/Reset Register

void delay_cycles(volatile uint32_t count) {
    while(count--) {
        __asm("nop");
    }
}

int main(void) {
    // 1. Turn on the clock for GPIO Port A (Bit 0)
    RCC_AHB1ENR |= (1 << 0);

    // 2. Set Pin PA5 as an Output (Bits 11:10 = 01)
    GPIOA_MODER &= ~(0x3 << 10);
    GPIOA_MODER |=  (0x1 << 10);

    // 3. Blink Forever
    while (1) {
        GPIOA_BSRR = (1 << 5);        // Set PA5 HIGH (LED ON)
        delay_cycles(400000);

        GPIOA_BSRR = (1 << (5 + 16)); // Set PA5 LOW (LED OFF)
        delay_cycles(400000);
    }
}
