#include "lib/include.h"

/*
 * ADC.c
 *
 *  Created on: 04/01/2023
 *      Author: Pamela Alegria Lopez
 */

void initADC0(void)
{
    // Enable the clock for ADC0
    SYSCTL->RCGCADC |= (1 << 0);
    // Wait for the peripheral to be ready
    while(!(SYSCTL->PRADC & (1 << 0)));

    // Configure ADC0 as a sequencer
    ADC0->EMUX = (ADC0->EMUX & ~(0xF000)) | 0x5000;
    ADC0->SSPRI = 0x0123;
    ADC0->ACTSS |= (1 << 3);
    ADC0->IM |= (1 << 3);
    ADC0->SSMUX3 = (ADC0->SSMUX3 & ~(0xF << 0)) | (0x0 << 0);
    ADC0->SSMUX3 = (ADC0->SSMUX3 & ~(0xF << 4)) | (0x1 << 4);
    ADC0->SSCTL3 = (ADC0->SSCTL3 & ~(0x3 << 0)) | (0x1 << 0);
    ADC0->SSCTL3 = (ADC0->SSCTL3 & ~(0x3 << 2)) | (0x1 << 2);
    ADC0->ACTSS |= (1 << 3);

    // Enable the Timer0 trigger for the ADC0 sequencer
    ADC0->TSSEL = (ADC0->TSSEL & ~(0x3 << 0)) | (0x5 << 0);
}
