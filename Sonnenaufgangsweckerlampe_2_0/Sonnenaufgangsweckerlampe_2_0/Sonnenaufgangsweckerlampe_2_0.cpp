#include "definitionen.h"
#include "LCD.h"
#include "ADC.h"
#include "einstellungen.h"
#include "zeit.h"
#include "menue.h"
#include "ausgabe.h"

ISR(TIMER1_OVF_vect){
	TCNT1H = 0b11110001;
	TCNT1L = 0b11110000;
	Sekunden++;
}

int main(void)
{
	init();
	
	while(1)
	{
		if (Sekunden!=sektemp)
		{
			zeit();
			ausgabe(1);
		}
		if(debounce(&PIND,2))
		{
			Wan=0;
			PORTC &= ~(1<<PC5);
		}
	}
	
	return 0;
}
