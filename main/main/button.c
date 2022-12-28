#include <button.h>

void Speed_up(unsigned int Speed, unsigned int Temp )
{
	if((PINB & (1 << button_up)) == 0)
	{
		_delay_ms(5);
		if((PINB & (1 << button_up)) == 0)
		{
			while((PINB & (1 << button_up)) == 0);
			Speed += Temp;
			if(Speed>=15999) Speed=15999;
		}
	}
}

void Speed_down(unsigned int Speed, unsigned int Temp )
{
	if((PINB & (1 << button_dowm)) == 0)
	{
		if(Speed >= 1500)
		{
			_delay_ms(5);
			if((PINB & (1 << button_dowm)) == 0)
			{
				while((PINB & (1 << button_dowm)) == 0);
				Speed -= Temp;
				if(Speed <= 500) Speed = 1500;
			}
		}
		else Speed = 1500;
	}
}

void On_Off(unsigned int Speed)
{
	if((PINB & (1 << button_start)) == 0)
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
}
