/*Configurar el timer 0 y timer 1 en modo de 32bits para hacer la siguiente rutina
una función que active  el convertidor analógico digital y muestre dos señal de cierta frecuencia y amplitud definida.
y las guarde en dos arreglos  de tamaño 1024 y la envié por el protocolo de comunicación asíncrono para ser procesadas 
y regresadas al microcontrolador en valores binarios las cuales modificaran el ancho de pulso y reconstruirán la señal 
enviada a un transistor o opam.
a) 3khz, amplitud de salida -10 a 10
b) 2khz , -5 a 5
c)10khz, -1 a 1
d)1khz -9 a 9
e)20khz -3.3 a 3.3*/

#include "lib/include.h"

void initTimer0(void)

{
    // Enable the clock for Timer0
    SYSCTL->RCGCTIMER |= (1 << 0);
    // Wait for the peripheral to be ready
    while(!(SYSCTL->PRTIMER & (1 << 0)));

    // Configure Timer0 as a 32-bit timer
    TIMER0->CFG = 0x00000004;

    // Set the prescaler for Timer0 to achieve a 2 kHz frequency
    TIMER0->TAMR = (TIMER0->TAMR & ~(0x00000003)) | 0x00000002;
    TIMER0->TAPR = 15999;

    // Set the initial value for Timer0
    TIMER0->TAILR = 0x00000000;

    // Enable Timer0
    TIMER0->CTL |= 0x00000001;
}
