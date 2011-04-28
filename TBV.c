#include <stdint.h>
//la costante TBV viene reimpostata sul contatore come una somma in modo da non avere dei tempi persi
//(il contatore è di tipo free running)

void TBV(uint32_t cost)
{
        uint32_t reg = *(volatile uint32_t *)0xE000E014;
        reg |= cost;
        *(volatile uint32_t *)0xE000E014 = reg;
        return;
}