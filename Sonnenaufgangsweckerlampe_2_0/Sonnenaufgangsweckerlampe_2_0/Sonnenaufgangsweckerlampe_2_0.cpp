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
			aus(1,3);
			aus(2,1);
		}
		if(debounce(&PIND,2))
		{
			Wan=0;
			PORTC &= ~(1<<PC5);
		}
		if (debounce(&PIND,PD4))
		{
			menu();
			aus(1,3);
			aus(2,1);
		}
	}
	
	return 0;
}
