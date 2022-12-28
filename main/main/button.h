#ifndef BUTTON_H_
#define BUTTON_H_
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "stdio.h"
#define tbi(port,bit) port ^= (1 << bit);
#define cbi(port,bit) port &= ~(1 << bit);
#define sbi(port,bit) port |= (1 << bit);
#define  button_start PB0
#define  button_up PB1
#define  button_dowm PB2

void Speed_up(unsigned int, unsigned int);
void Speed_down(unsigned int, unsigned int);
void On_Off(unsigned int);
#endif /* BUTTON_H_ */