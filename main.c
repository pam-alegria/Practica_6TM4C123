#include "lib/include.h"

int main(void)
{
    Configurar_PLL(_40MHZ);  //Confiuracion de velocidad de reloj
    Configura_Reg_ADC0();
    Configurar_UART0();
    Configura_Reg_PWM1();
    initTimer0();

    // Main loop
    while(1)
    {

        while ((ADC0->RIS & 0x1) == 0)
        {
        }

        // Read the ADC result for channel 0
        uint32_t adcResult0 = ADC0->SSFIFO0 & 0xFFF;

        // Clear the ADC interrupt flag for channel 0
        ADC0->ISC = 0x1;

        // Start the ADC conversion for channel 1
        ADC0->PSSI |= 0x2;

        while ((ADC0->RIS & 0x2) == 0)
        {
        }

        // Read the ADC result for channel 1
        uint32_t adcResult1 = ADC0->SSFIFO1 & 0xFFF;
        // Clear the ADC interrupt flag for channel 1
        ADC0->ISC = 0x2;

        // Process the ADC results for both channels here


    }
}