#ifndef UART_UART_H_
#define UART_UART_H_

extern void Configurar_UART2(void);
extern char readChar(void);
extern void printChar(char c);
extern void printString(char* string);
extern int readString(char delimitador, char *string);
extern void invertirString(char *string, int i);
extern void agregarNumeros(char *string, char *num, int i);


#endif /* UART_UART_H_ */