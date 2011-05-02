#include <stdint.h>

void TBV(uint32_t cost)
{
        uint32_t reg = *(volatile uint32_t *)0xE000E014;
        reg |= cost;
        *(volatile uint32_t *)0xE000E014 = reg;
        return;
}