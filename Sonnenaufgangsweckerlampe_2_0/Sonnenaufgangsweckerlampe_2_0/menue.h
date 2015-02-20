/*
 * menue.h
 *
 * Created: 05.02.2015 07:21:44
 *  Author: Lüdemann
 */ 


#ifndef MENUE_H_
#define MENUE_H_

uint8_t menu(){
	uint8_t pos = 0;
	bool stop = true;
	while (!debounce(&PIND,PD4))
	{
		switch (pos)
		{
			case 0:
				//Weckzeit anzeigen und einstellen mit PD2
				aus(1,5);
				aus(2,0);
				lcd_string("Werktags");
				while(stop)
				{
					//Zeitabfrage mit einbauen
					if (debounce(&PIND,PD2))
					{
						einst(4);
						lcd_string("Werktags");
					}
					if (debounce(&PIND,PD4))
					{
						return 1;
					}
					if (debounce(&PIND,PD3))
					{
						stop= false;
					}
				}
				stop=true;
				pos++;
				break;
			
			case 1:
				//Weckzeit anzeigen und einstellen am Wochenende 
				//Jetzt noch nicht vollsteandig implmentiert
				aus(1,5);
				aus(2,0);
				lcd_string("Wohenende nein");
				while (stop)
				{
					if (debounce(&PIND,PD2))
					{
						//Einstellungen hinzu
					}
					if (debounce(&PIND,PD4))
					{
						return 1;
					}
					if (debounce(&PIND,PD3))
					{
						stop= false;
					}
				}
				stop=true;
				pos++;
				break;
			
			case 2:
				//Kallender einstellen
				//Jetzt noch nicht implementiert
				aus(1,2);
				aus(2,0);
				lcd_string("Kellender nein");
				while (!debounce(&PIND,PD3))
				{
					if (debounce(&PIND,PD2))
					{
						//Einstellungen hinzu
					}
					if (debounce(&PIND,PD4))
					{
						return 1;
					}
				}
				pos++;
				break;
			
			case 3:
				//Zeit einstellen ohnen Sekunden
				aus(1,3);
				aus(2,0);
				lcd_string("Zeit");
				while (!debounce(&PIND,PD3))
				{
					if (debounce(&PIND,PD2))
					{
						einst(0);
					}
					if (debounce(&PIND,PD4))
					{
						return 1;
					}
				}
				pos++;
				break;
			
			default:
				break;
		}
		pos=0;
	}
return 0;
}



#endif /* MENUE_H_ */