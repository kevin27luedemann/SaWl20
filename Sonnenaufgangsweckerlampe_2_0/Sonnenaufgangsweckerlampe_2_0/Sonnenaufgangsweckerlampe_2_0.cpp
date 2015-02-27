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
			if (displaystat)
			{
				aus(1,3);
				aus(2,1);
				displayoff++;
			}
			if (displayoff>=120)
			{
				displaystat=false;
				displayoff=0;
				PORTC &= ~(1<<PC2); //Display ausschalten
			}
			
		}
		if(debounce(&PIND,2))
		{
			Wan=0;
			lichteinaus(0);
		}
		if (debounce(&PIND,PD4))
		{
			if (!displaystat)
			{
				PORTC |= (1<<PC2); //display einsschalten
				displaystat=true;
			}
			else
			{
				menu();
				aus(1,3);
				aus(2,1);
			}
			
		}
		if (debounce(&PIND,PD3))
		{
			switch (lampenstaerke)
			{
				case 1:
					lichteinaus(1);
					break;
					
				case 2:
					lichteinaus(5);
					break;
					
				case 3:
					lichteinaus(4);
					break;
					
				default:
					break;
			}
			if ( PORTC& (1<<PC3) )
			{
				lichteinaus(0);
			}
		}
	}
	
	return 0;
}
