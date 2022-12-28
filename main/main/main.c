#define F_CPU 8000000UL
#include <main.h>
#include "stdio.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>

unsigned int Speed = 0;
unsigned int CountT2 = 0;
unsigned int Temp = 1500;
void main(void)
{	
	
	// Port LCD
	DDRA  |= (1<<DDA7) | (1<<DDA6) | (1<<DDA5) | (1<<DDA4) | (1<<DDA3) | (1<<DDA2) | (0<<DDA1) | (0<<DDA0);
	PORTA |= (0<<PINA7) | (0<<PINA6) | (0<<PINA5) | (0<<PINA4) | (0<<PINA3) | (0<<PINA2) | (0<<PINA1) | (0<<PINA0);
	
	// Port Button
	DDRB = 0x00;
	
	// Port Motor DC
	DDRD=(0<<DDD7) | (0<<DDD6) | (1<<DDD5) | (0<<DDD4) | (1<<DDD3) | (0<<DDD2) | (1<<DDD1) | (0<<DDD0);
	PORTD= 0x00;
	
	// khai bao timer2 mode Normal chia 1024
	ASSR=0<<AS2;
	TCCR2 |= (1<<CS22) | (1<<CS21) | (1<<CS20);
	TCNT2 = 0x06;
	OCR2=0x00;
	
	// khai bao fast pwm cua timer 1  co tran ICR1 chu ki m?i sung là 2ms
	TCCR1A |=(1<<COM1A1)  | (1<<WGM11) | (0<<WGM10);
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS10);
	TCNT1H=0x00;
	TCNT1L=0x00;
	ICR1H=0x3E;
	ICR1L=0x7F;
	OCR1AH=0x00;
	OCR1AL=0x00;
	TIMSK|= (1<<TOIE2) | (1<<TOIE0);
	MCUCSR=(0<<ISC2);
	GIFR=(0<<INTF1) | (1<<INTF0) | (0<<INTF2);
	sei();

	while (1)
	{
		//
	}
}
ISR(TIMER2_OVF_vect)
{
	TCCR2=(0<<CS22) | (0<<CS21) | (0<<CS20);
	if(CountT2 >=5)
	{
		CountT2=0;
		
		if(((PINB & (1 << button_up)) == 0) && (PORTD == (1 << PIND1)))
		{
			_delay_ms(5);
			if(((PINB & (1 << button_up)) == 0) && (PORTD == (1 << PIND1)))
			{
				while(((PINB & (1 << button_up)) == 0) && (PORTD == (1 << PIND1)));
				Speed += Temp;
				if(Speed>=15999) Speed=15999;
			}
		}
		else if(((PINB & (1 << button_dowm)) == 0) && (PORTD == (1 << PIND1)))
		{
			if(Speed >= 1500)
			{
				_delay_ms(5);
				if(((PINB & (1 << button_dowm)) == 0) && (PORTD == (1 << PIND1)))
				{
					while(((PINB & (1 << button_dowm)) == 0) && (PORTD == (1 << PIND1)));
					Speed -= Temp;
					if(Speed <= 500) Speed = 1500;
				}
			}
			else Speed = 1500;
			
		}
		else if((PINB & (1 << button_start)) == 0)
		{
			_delay_ms(5);
			if((PINB & (1 << button_start)) == 0)
			{
				while((PINB & (1 << button_start)) == 0);
				tbi(PORTD, 1);
				if(PORTD == (0 << PIND1)){
					Speed = 0;
				}
				else{
					Speed = 1500;
				}
			}
		}
		/***
		On_Off(Speed);
		Speed_up(Speed, Temp);
		Speed_down(Speed, Temp);
		***/
		OCR1AH= Speed >>8 ;
		OCR1AL= Speed && 0xFF ;
		
		
	}
	CountT2++;
	TCNT2=0x00;
	TCCR2=(1<<CS22) | (1<<CS21) | (1<<CS20);
}