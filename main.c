#include "lib/include.h"

int main(void)
{
    initTimer0();
    initADC0();

    // Main loop
    while(1)
    {
        uint32_t adcValue1 = readADC0();
        uint32_t adcValue2 = readADC0();
    }
}