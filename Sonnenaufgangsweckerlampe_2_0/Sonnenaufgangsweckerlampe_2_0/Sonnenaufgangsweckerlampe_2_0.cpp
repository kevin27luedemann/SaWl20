#include "definitionen.h"
#include "LCD.h"
#include "ADC.h"
#include "einstellungen.h"
#include "zeit.h"
#include "menue.h"

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

void ausgabe(uint8_t pos){
	char Buffer[20];
	lcd_clear();
	lcd_home();
	if (pos==0 || pos==1)
	{
		switch (WochenTag)
		{
			case 0:
			lcd_string("So ");
			break;
			
			case 1:
			lcd_string("Mo ");
			break;
			
			case 2:
			lcd_string("Di ");
			break;
			
			case 3:
			lcd_string("Mi ");
			break;
			
			case 4:
			lcd_string("Do ");
			break;
			
			case 5:
			lcd_string("Fr ");
			break;
			
			case 6:
			lcd_string("Sa ");
			break;
			
			default:
			break;
		}

		
		itoa( Stunden, Buffer, 10 );
		lcd_string(Buffer);
		
		itoa( Minuten, Buffer, 10);
		lcd_string(":");
		lcd_string(Buffer);
		
		itoa(Sekunden, Buffer,10);
		lcd_string(":");
		lcd_string(Buffer);
	}
	
	if (pos==2)
	{
		itoa(WStunden, Buffer, 10 );
		lcd_string(Buffer);
		
		itoa(WMinuten, Buffer, 10);
		lcd_string(":");
		lcd_string(Buffer);
		
		lcd_setcursor(0,2);
	}
	lcd_setcursor(0,2);
	
	if (pos==1)
	{
		//Temperatur ausgeben
		dtostrf(tempera,2,2,Buffer);
		lcd_string(Buffer);
		lcd_data(0b11011111); //°
		lcd_data(0b01000011); //C
	}
}