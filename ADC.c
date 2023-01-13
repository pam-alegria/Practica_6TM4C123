#include "lib/include.h"

/*
 * ADC.c
 *
 *  Created on: 04/01/2023
 *      Author: Pamela Alegria Lopez
 */

extern void Configura_Reg_ADC0(void)
{
    /*
Usando el modulo 0 y 1 , configurar la tarjeta a la frecuencia asignada, para adquirir 6 señales analógicas a una velocidad de 1 millón de muestras por segundo, por los canales asignados  y guardar los valores en un arreglo para ser enviados con un botones  externos asociado al gpio D a través del protocolo de comunicación asíncrona a una velocidad de 115200 todo esto usando interrupciones.
a) 1,3,4,5,11,9- 55Mhz- 115200 -sec 2 ,sec 1
b) 2,4,6,7,10,1- 30MHZ -57600 -sec3, sec1
c),3,5,7,4,2,8 70 MHZ 9600, -sec2, sec3, sec1
d),11,9,6,7,4,2 33MHZ 19200 -sec3,sec0,sec2
e)1,5,7,11,6,8 80MHZ 4800 -sec0 ,sec3
la captura será en Matlab en 6 graficas.
    */
     //Pag 396 para inicializar el modulo de reloj del adc RCGCADC
    SYSCTL->RCGCADC = (1<<0); 
    //Pag 382 (RGCGPIO) Puertos base habilitación del reloj
    //                     F     E      D       C      B     A
    SYSCTL->RCGCGPIO |= (1<<5)|(1<<4)|(1<<3)|(0<<2)|(0<<1)|(1<<0);
    //Pag 760 (GPIODIR) Habilta los pines como I/O un cero para entrada y un uno para salida
    GPIOE->DIR = (0<<1); //PE5 y PE4
    GPIOD->DIR = (0<<3) | (0<<1);
    //(GPIOAFSEL) pag.770 Enable alternate función para que el modulo analógico tenga control de esos pines
    GPIOE->AFSEL =  (1<<1);
    GPIOD->AFSEL =  (1<<3) | (1<<1);
    //(GPIODEN) pag.781 desabilita el modo digital
    GPIOE->DEN = (0<<1);
    GPIOD->DEN = (0<<3) | (0<<1);
    //Pag 787 GPIOPCTL registro combinado con el GPIOAFSEL y la tabla pag 1808
    GPIOE->PCTL = GPIOE->PCTL & (0xFFFFFF0F);
    GPIOD->PCTL = GPIOD->PCTL & (0xFFFF0F0F);
    //(GPIOAMSEL) pag.786 habilitar analogico
    GPIOE->AMSEL = (1<<1);
    GPIOD->AMSEL = (1<<3) | (1<<1);
    //Pag 1159 El registro (ADCPC) establece la velocidad de conversión por segundo
    ADC0->PC = 0x7;//1Mksps
    //Pag 1099 Este registro (ADCSSPRI) configura la prioridad de los secuenciadores
    ADC0->SSPRI = 0x1203;
    //Pag 1077 (ADCACTSS) Este registro controla la activación de los secuenciadores
    ADC0->ACTSS  =   (0<<3) | (0<<2) | (0<<1) | (0<<0);
    //Pag 1091 Este registro (ADCEMUX) selecciona el evento que activa la conversión (trigger)
    ADC0->EMUX  = (0x0<<4);
    //Pag 1129 Este registro (ADCSSMUX2) define las entradas analógicas con el canal y secuenciador seleccionado
    ADC0->SSMUX1 = (2<<0) | (4<<4) | (6<<8);
    //pag 868 Este registro (ADCSSCTL2), configura el bit de control de muestreo y la interrupción
    ADC0->SSCTL1 = (1<<1) | (1<<2) | (1<<5) | (1<<6) | (1<<8) | (1<<9);
    /* Enable ADC Interrupt */
    ADC0->IM |= (0<<1); /* Unmask ADC0 sequence 2 interrupt pag 1082*/
    //NVIC_PRI4_R = (NVIC_PRI4_R & 0xFFFFFF00) | 0x00000020;
    //NVIC_EN0_R = 0x00010000;
    //Pag 1077 (ADCACTSS) Este registro controla la activación de los secuenciadores
    ADC0->ACTSS = (0<<3) | (0<<2) | (1<<1) | (0<<0);
    //ADC0->PSSI |= (1<<1);
}

extern void Configura_Reg_ADC1(void)
{
    /*
    */
     //Pag 396 para inicializar el modulo de reloj del adc RCGCADC
    SYSCTL->RCGCADC |= (1<<1); 
    //Pag 382 (RGCGPIO) Puertos base habilitación del reloj
    //                     F     E      D       C      B     A
    SYSCTL->RCGCGPIO |= (1<<5)|(1<<4)|(1<<3)|(0<<2)|(1<<1)|(1<<0);
    //Pag 760 (GPIODIR) Habilta los pines como I/O un cero para entrada y un uno para salida
    GPIOE->DIR = (0<<2); 
    GPIOD->DIR = (0<<0);
    GPIOB->DIR = (0<<4);
    //(GPIOAFSEL) pag.770 Enable alternate función para que el modulo analógico tenga control de esos pines
    GPIOE->AFSEL = (0<<2); 
    GPIOD->AFSEL = (0<<0);
    GPIOB->AFSEL = (0<<4);
    //(GPIODEN) pag.781 desabilita el modo digital
    GPIOE->DEN = (0<<2); 
    GPIOD->DEN = (0<<0);
    GPIOB->DEN = (0<<4);
    //Pag 787 GPIOPCTL registro combinado con el GPIOAFSEL y la tabla pag 1808
    GPIOE->PCTL = GPIOE->PCTL & (0xFFFFF0FF);
    GPIOD->PCTL = GPIOD->PCTL & (0xFFFFFFF0);
    GPIOB->PCTL = GPIOB->PCTL & (0xFFF0FFFF);
    //(GPIOAMSEL) pag.786 habilitar analogico
    GPIOE->AMSEL = (1<<2); 
    GPIOD->AMSEL = (1<<0);
    GPIOB->AMSEL = (1<<4);
    //Pag 1159 El registro (ADCPC) establece la velocidad de conversión por segundo
    ADC1->PC = 0x7;//250ksps
    //Pag 1099 Este registro (ADCSSPRI) configura la prioridad de los secuenciadores
    ADC1->SSPRI = 0x1203;
    //Pag 1077 (ADCACTSS) Este registro controla la activación de los secuenciadores
    ADC1->ACTSS  =   (0<<3) | (0<<2) | (0<<1) | (0<<0);
    //Pag 1091 Este registro (ADCEMUX) selecciona el evento que activa la conversión (trigger)
    ADC1->EMUX  = (0x0<<4) | (0x0<<8) | (0x0<<12);
    //Pag 1129 Este registro (ADCSSMUX2) define las entradas analógicas con el canal y secuenciador seleccionado
    ADC1->SSMUX1 = (7<<0);
    ADC1->SSMUX3 = (10<<0); 
    ADC1->SSMUX2 = (1<<0);
    //pag 868 Este registro (ADCSSCTL2), configura el bit de control de muestreo y la interrupción
    ADC1->SSCTL2 = (1<<1) | (1<<2);
    ADC1->SSCTL1 = (1<<1) | (1<<2);
    ADC1->SSCTL3 = (1<<1) | (1<<2);
    /* Enable ADC Interrupt */
    ADC1->IM |= (0<<2); /* Unmask ADC0 sequence 2 interrupt pag 1082*/
    ADC1->IM |= (0<<1);
    ADC1->IM |= (0<<3);
    //NVIC_PRI4_R = (NVIC_PRI4_R & 0xFFFFFF00) | 0x00000020;
    //NVIC_EN0_R = 0x00010000;
    //Pag 1077 (ADCACTSS) Este registro controla la activación de los secuenciadores
    ADC1->ACTSS = (1<<3) | (1<<2) | (1<<1) | (0<<0);
    //ADC1->PSSI |= (1<<2) | (1<<1) | (1<<3);
}

extern void ADC0_InSeq1(uint16_t *Result){

    //ADC Processor Sample Sequence Initiate (ADCPSSI)
       ADC0->PSSI = (1<<1);
       while((ADC0->RIS & (1<<1))==0){}; // espera al convertidor
       Result[0] = ADC0->SSFIFO1&0xFFF; //  Leer  el resultado almacenado en la pila2
       Result[1] = ADC0->SSFIFO1&0xFFF;
       Result[2] = ADC0->SSFIFO1&0xFFF;
       //printChar('A');
       ADC0->ISC = 0x0002;  //Conversion finalizada

}

extern void ADC1_InSeq1(uint16_t *Result){

    //ADC Processor Sample Sequence Initiate (ADCPSSI)
       ADC1->PSSI = (1<<1);
       while((ADC1->RIS&(1<<1))==0){}; // espera al convertidor
       Result[3] = ADC1->SSFIFO1&0xFFF;
       //printChar('A');
       ADC1->ISC = 0x0002;  //Conversion finalizada

}

extern void ADC1_InSeq3(uint16_t *Result){

    //ADC Processor Sample Sequence Initiate (ADCPSSI)
       ADC1->PSSI = (1<<3);
       while((ADC1->RIS&(1<<3))==0){}; // espera al convertidor
       Result[4] = ADC1->SSFIFO3&0xFFF;
       //printChar('A');
       ADC1->ISC = 0x0008;  //Conversion finalizada

}

extern void ADC1_InSeq2(uint16_t *Result){

    //ADC Processor Sample Sequence Initiate (ADCPSSI)
       ADC1->PSSI = (1<<2);
       while((ADC1->RIS&(1<<2))==0){}; // espera al convertidor
       Result[5] = ADC1->SSFIFO2&0xFFF;
       //printChar('A');
       ADC1->ISC = 0x0004;  //Conversion finalizada

}